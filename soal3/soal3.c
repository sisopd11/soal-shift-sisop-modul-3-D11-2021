#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>

char fileList[2048][PATH_MAX];
pthread_t tid[500];

void getFileExt(char* fileName, char *exten)
{
    char *ext = strchr(fileName, '.');
    if (ext == NULL) {
        strcpy(exten,"Unknown");
    } 
    else if (ext == fileName){
        strcpy(exten,"Hidden");
    }
    else
    {
        strcpy(exten,ext+1);
    }
}

bool checkExistAndRegFile(char *basePath)
{
    struct stat buffer;
    int exist = stat(basePath,&buffer);
    if(exist == 0)
    {
        if( S_ISREG(buffer.st_mode) ) return true;
        else return false;
    }
    else  
        return false;
}

void *moveFile( void *arg )
{
    char basePath[PATH_MAX];
    strcpy(basePath,(char *) arg);

    if(checkExistAndRegFile(basePath))
    {
        //printf("%s\n",(char*)arg);
        const char *p="/";
        char *a,*b;
        char fullPath[PATH_MAX];
        strcpy(fullPath,(char *) arg);

        char fileName[100];

        for( a=strtok_r(fullPath,p,&b) ; a!=NULL ; a=strtok_r(NULL,p,&b) ) {
            memset(fileName,0,sizeof(fileName));
            strcpy(fileName,a);
        }

        char ext[PATH_MAX];
        getFileExt(fileName,ext);

        if(strcmp(ext,"Hidden") != 0 && strcmp(ext,"Unknown") != 0)
        {
            for(int i = 0; i<strlen(ext); i++)
            {
                ext[i] = tolower(ext[i]);
            }
        }
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd() error");
            return (void *) 0;
        }

        char destinationDir[PATH_MAX];
        sprintf(destinationDir,"%s/%s",cwd,ext);
        mkdir(destinationDir,0777);
        char destination[PATH_MAX];
        sprintf(destination,"%s/%s/%s",cwd,ext,fileName);
	//same as move 
        rename(basePath,destination);
        return (void *) 1;
    }
    else return (void *) 0;
}
//template modul2 cek file in directory
int listFilesRecursively(char *basePath, int *fileCount)
{
    char path[PATH_MAX];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return 0;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            char fullPath[PATH_MAX];
            sprintf(fullPath,"%s/%s",basePath,dp->d_name);
            //printf("%s\n", fullPath);
            if(checkExistAndRegFile(fullPath))
            {
                sprintf(fileList[*fileCount],"%s",fullPath);
                *fileCount += 1;
            }
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path,fileCount);
        }
    }

    closedir(dir);
    return 1;
}


int main(int argc,char* argv[])
{

    char baseDir[PATH_MAX];

    if(strcmp(argv[1],"-f")==0) 
    {
	int i=2;

		while(argv[i]!=NULL)
		{
		    pthread_create( &(tid[i-2]), NULL, moveFile, (void*) argv[i]);
		    i++;
		}

		for (int j=0;j<(i-2);j++)
		{
		    long cek;
		    void *ptr;
		    pthread_join( tid[j], &ptr);
		    cek = (long) ptr;
		    if(cek) printf("File %d : Berhasil Dikategorikan\n", j+1);
		    else printf("File %d : Sad, gagal :(\n", j+1);
		}
        
        return 0;
    }
   else if(!strcmp(argv[1],"*"))
    {
	int count_file=0;
        getcwd(baseDir,sizeof(baseDir));
	int cekFile = listFilesRecursively(baseDir, &count_file);
    	for(int i = 0; i<count_file; i++)
    	 {
        	pthread_create( &(tid[i]), NULL, moveFile, (void*) fileList[i]);
   	 }

   	 for (int i = 0; i < count_file; i++)
    	{
        	void *ptr;
        	pthread_join( tid[i], &ptr);
    	}

    }

    else if(strcmp(argv[1],"-d")==0) 
    {
	int cekFile,count_file = 0;
        strcpy(baseDir,argv[2]);
	cekFile = listFilesRecursively(baseDir, &count_file);
    	for(int i = 0; i<count_file; i++)
    	{
        	pthread_create( &(tid[i]), NULL, moveFile, (void*) fileList[i]);
   	}

   	for (int i = 0; i < count_file; i++)
    	{
        	void *ptr;
        	pthread_join( tid[i], &ptr);
    	}

	if(!cekFile)
    	{
		printf("Yah, gagal disimpan :(\n");
		return 0;
    	}
	else
	{
		
    		printf("Direktori sukses disimpan!\n");
    	}
    }

    return 0;
}

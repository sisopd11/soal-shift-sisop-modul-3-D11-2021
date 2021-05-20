#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdbool.h>


pthread_t tid[500];
char fileList[500][500];

char toLower(char* str)
{
	 for(int i = 0; i<strlen(str); i++)
            {
                if(str[i]>64 && str[i]<91)
		    str[i]+=32;
            }
}

char getFileExt(char*fileName,char*extension)
{
    //char *stop = getFilename(extension);
    char *ext = strchr(fileName, '.');
    if (ext == NULL) {
        strcpy(extension,"Unknown");
    } 
    else if (ext == fileName){
        strcpy(extension,"Hidden");
    }
    else
    {
        strcpy(extension,ext+1);
    }
}

bool checkFile(char *basePath)
{
    struct stat buffer;
    int exist = stat(basePath,&buffer);
    if(exist == 0)
    {
        if(S_ISREG(buffer.st_mode)) 
           return true;
        else 
	   return false;
    }
    else  
        return false;
}

void *moveFile(void *arg)
{
    char basePath[PATH_MAX];
    strcpy(basePath,(char *) arg);

    if(checkFile(basePath))
    {
        char *i,*b;
        char fullPath[PATH_MAX];
        strcpy(fullPath,(char *) arg);

        char fileName[100];

        for(i=strtok_r(fullPath,"/",&b); i!=NULL; i=strtok_r(NULL,"/",&b)) 
	{
            memset(fileName,0,sizeof(fileName));
            strcpy(fileName,i);
        }

        char ext[PATH_MAX];
        getFileExt(fileName,ext);

        if(strcmp(ext,"Hidden") != 0 && strcmp(ext,"Unknown") != 0)
        {
            toLower(ext);
        }
        char workDir[PATH_MAX];
        if (getcwd(workDir, sizeof(workDir)) == NULL)
	{
            perror("getcwd() error");
            return (void *) 0;
        }

       
        char destDir[PATH_MAX];
        sprintf(destDir,"%s/%s",workDir,ext);
        
        mkdir(destDir,0777);

        char destination[PATH_MAX];
        sprintf(destination,"%s/%s/%s",workDir,ext,fileName);
       
        rename(basePath,destination);
        
        return (void *) 1;
    }

    else return (void *) 0;
}
//template modul2, cek file in directory
int listFilesRecursively(char *basePath, int *count)
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
            if(checkFile(fullPath))
            {
                sprintf(fileList[*count],"%s",fullPath);
                *count = *count + 1;
            }
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path,count);
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
		    pthread_create(&(tid[i-2]), NULL, moveFile, (void*) argv[i]);
		    i++;
		}

		for (int j=0;j<(i-2);j++)
		{
		    long cek;
		    void *ptr;
		    pthread_join( tid[j], &ptr);
		    cek = (long) ptr;
		    if(cek) 
			printf("File %d : Berhasil Dikategorikan\n", j+1);
		    else 
			printf("File %d : Sad, gagal :(\n", j+1);
		}
        
        return 0;
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
    else if(strcmp(argv[1],"*")==0)
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

    return 0;
}

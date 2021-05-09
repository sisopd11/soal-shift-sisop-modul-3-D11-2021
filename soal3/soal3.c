#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>

pthread_t tid[500];
char *workDir;
char *tempDir;
int currentInd;

char* getFilename(char str[]);
char* getExtension(char str[]);


void moveFile(char src[], char dst[])
{
	FILE *file1;
	FILE *file2;
	int charr;

	file1 = fopen(src,"r");
	file2 = fopen(dst,"w");

	if(!file1)
	{
		fclose(file2);
		return ;
	}
	if(!file2)
	{
		return ;
	}
	while((charr=fgetc(file1)) != EOF)
	{
		fputc(charr,file2);
	}

	fclose(file1);
	fclose(file2);

	remove(src);
	return ;
}


void* categories(void *arg)
{
	pthread_t id=pthread_self();
	int i;
	char *extension;
	char destination[500];
	char path[500];
	extension = getExtension((char *)arg);

	if(extension == NULL)
	{
		strcpy(destination, "Unknown");
	}
	else
	{
		strcpy(destination, extension);
		for(i=0;i<strlen(destination);i++)
		{
			if(destination[i]>64 && destination[i]<91)
			{
				destination[i]+=32;
			}
		}
	}

	if(mkdir(destination,0777) == -1);

	snprintf(path,500,"%s/%s/%s",workDir,destination,getFilename((char *)arg));
	moveFile((char *)arg, path);
	return NULL;
}


int main(int argc, char **argv)
{
	char buffer[1000];
	workDir = getcwd(buffer,1000);
	int i=2,j,cek,cek2;

	if(strcmp(argv[1],"-f")==0)
	{
		
		while (argv[i] != NULL)
		{
			pthread_create(&(tid[i-2]),NULL,&categories,(void *)argv[i]);
			i++;
		}
		for(j=0;j<(i-2);j++)
		{
			cek2 = pthread_join(tid[j],NULL);
			if(cek2==0)
			{
				printf("File %d : Berhasil di kategorikan\n", j+1);
			}
			else
			{
				printf("File %d : Gagal, sad :(\n",j+1);
			}		
		}
	}
	if(strcmp(argv[1],"-d")==0)
	{
	}
	if(strcmp(argv[1],"-*")==0)
	{
	}
   return 0;
}

char* getFilename(char str[])
{
	char* stop;
	char* final;
	stop = strchr(str,'/');
	if(stop == NULL)
	{
		return str;
	}
	while(stop != NULL)
	{
		final = stop+1;
		stop = strchr(stop+1,'/');
	}
	return final;
}

char* getExtension(char str[])
{
	char* stop = getFilename(str);
	char* final = strchr(stop,'.');
	if(final == NULL)
	{
		return NULL;
	}
	else
	{
		return (final+1);
	}
}

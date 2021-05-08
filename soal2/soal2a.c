#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/ipc.h>

// declaration
int res = 0;
int (*value)[10];
int matrixA[4][3], matrixB[3][6]; // array
pthread_t thread, thread2, thread3; // create thread


// first matrix function
void *input_matrixA(void *arg) {
   matrixA[0][0]=1; 
   matrixA[0][1]=1; 
   matrixA[0][2]=1;

   matrixA[1][0]=1; 
   matrixA[1][1]=2; 
   matrixA[1][2]=1;

   matrixA[2][0]=1; 
   matrixA[2][1]=1; 
   matrixA[2][2]=3;
   
   matrixA[3][0]=4; 
   matrixA[3][1]=1; 
   matrixA[3][2]=1;
   return NULL;
}

// second matrix function
void *input_matrixB(void *arg){ 
   matrixB[0][0]=1; 
   matrixB[0][1]=2; 
   matrixB[0][2]=3; 
   matrixB[0][3]=4; 
   matrixB[0][4]=1; 
   matrixB[0][5]=2; 

   matrixB[1][0]=2; 
   matrixB[1][1]=3; 
   matrixB[1][2]=4; 
   matrixB[1][3]=1; 
   matrixB[1][4]=2; 
   matrixB[1][5]=3; 

   matrixB[2][0]=3; 
   matrixB[2][1]=4; 
   matrixB[2][2]=1;
   matrixB[2][3]=2; 
   matrixB[2][4]=3; 
   matrixB[2][5]=4; 
   return NULL;
}

// matrix multiplication function
void *multiply(void *arg){
   for(int i = 0; i < 4; i++) {
      for(int j = 0;j < 6; j++) {
         for(int k = 0; k < 3; k++) {
            res+=matrixA[i][k] * matrixB[k][j]; // multiplication
         }
         value[i][j]= res; // set the final matrix value as result
         res = 0; // result equal to 0 for recount
      }
   }
   return NULL;
}

int main(){
   // template shared memory 
   key_t key = 1908;
   int shmid = shmget(key, sizeof(value), IPC_CREAT | 0666); //
   value = shmat(shmid, 0, 0);

   pthread_create(&thread, NULL, input_matrixA, NULL); // create thread1 for matrixA
   pthread_join(thread,NULL);

   pthread_create(&thread2, NULL, input_matrixB, NULL); // create thread2 for matrixB
   pthread_join(thread2,NULL);

   for(int i = 0; i < 4; i++){ // set 4 rows
      for(int j = 0; j < 6; j++){ // set 5 columns
         value[i][j] = 0;
      }
      pthread_create(&thread3, NULL, multiply, NULL); // create thread3 for the final matrix
      pthread_join(thread3,NULL);
   }

   // print the final matrix
   printf("Matrix: \n");
   for(int i = 0; i < 4; i++){ // set 4 rows
      for(int j = 0;j < 6;j++){  // set 5 columns
         printf("%d\t", value[i][j]); // print the number with a tab
      }
      printf("\n");
   }
}

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <stdlib.h>

// declaration
int res = 0;
int (*value)[10];
int matrixA[4][3], matrixB[3][6]; // array
pthread_t thread, thread2, thread3; // create thread


// first matrix function
void *input_matrixA(void *arg) {
   printf("Matrix A:\n");
   int i, k;
   for(i = 0; i < 4; i++) {
      for(k = 0; k < 3; k++) {
         scanf("%d", &matrixA[i][k]);
      }
   }
}

// second matrix function
void *input_matrixB(void *arg) { 
   printf("Matrix B:\n");
   int k, j;
   for(k = 0; k < 3; k++) {
      for(j = 0; j < 6; j++) {
         scanf("%d", &matrixB[k][j]);
      }
   }
}

// matrix multiplication function
void *multiply(void *arg) {
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

   for(int i = 0; i < 4; i++) { // set 4 rows
      for(int j = 0; j < 6; j++) { // set 6 columns
         value[i][j] = 0;
      }
      pthread_create(&thread3, NULL, multiply, NULL); // create thread3 for the final matrix
      pthread_join(thread3,NULL);
   }

   // print the final matrix
   printf("The Final Matrix: \n");
   for(int i = 0; i < 4; i++) { // set 4 rows
      for(int j = 0;j < 6;j++) {  // set 6 columns
         printf("%d\t", value[i][j]); // print the number with a tab
      }
      printf("\n");
   }
}

/*
4 1 4
2 1 3
4 2 2
1 1 4
Matrix B:
2 1 3 2 0 3
1 4 4 0 0 2
1 1 0 1 2 1
Final Matrix:
13	12	16	12	8	18	
8	9	10	7	6	11	
12	14	20	10	4	18	
7	9	7	6	8	9	
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

//deklarasi
int (*value)[10], matrix[4][6];
unsigned long int fact_result[4][6];
pthread_t thread, thread2;

// new matrix function
void *input_matrix(void *arg) {
   printf("New Matrix:\n");
   int i, j;
   for(i = 0; i < 4; i++) {
      for(j = 0; j < 6; j++) {
         scanf("%d", &matrix[i][j]);
      }
   }
}

// basic factorial function
unsigned long long fact(int num) {
    unsigned long int result = 1;
    for (int i = 1; i <= num; i++) {
        result *= i;
    }
    return result;
}

// modified factorial function
void *factorial(void *argument) {
    unsigned long int result;
    int *arg = (int *)argument;

    int a = arg[0],
        b = arg[1];

    if (a >= b) {
        result = fact(a) / fact(a - b);
    } else if (a < b) {
        result = fact(a);
    } else if (a == 0 || b == 0) {
        result = 0;
    }

    fact_result[arg[2]][arg[3]] = result;
    return NULL;
    
}


void main() {
    //shared memory template
    key_t key = 1908;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
    
    // print shared matrix from soal2a.c (final matrix)
    printf("Shared Matrix: \n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0;j < 6; j++) {
            printf("%d\t", value[i][j]);
        }
        printf("\n");
    }

    pthread_create(&thread, NULL, input_matrix, NULL); // create thread for new matrix
    pthread_join(thread,NULL);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            int arguments[4];
            arguments[0] = (*value)[10];
            arguments[1] = matrix[i][j];
            arguments[2] = i;
            arguments[3] = j;

            pthread_create(&thread, NULL, factorial, &arguments);// create thread for factorial
            pthread_join(thread, NULL); // create thread for factorial
        }
    }

    // print the result matrix
    printf("Result:\n");
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            printf("%ld ", fact_result[i][j]);
        }
        printf("\n");
    }
}
/*
Shared Matrix:
14 2 3 8 8 10
7 4 8 5 14 9
9 2 13 5 11 2
8 7 10 4 10 8
New Matrix:
14 2 3 8 8 10
7 4 8 5 14 9
9 2 13 5 11 2
8 7 10 4 10 8
*/

/*
Shared Matrix: 
6	6	6	6	6	6	
12	12	12	12	12	12	
6	6	6	6	6	6	
18	18	18	18	18	18	
New Matrix:
1 1 1 1 1 1
2 2 2 2 2 2
3 3 3 3 3 3
4 4 4 4 4 4
Result:
12 12 12 12 12 12 
132 132 132 132 132 132 
1320 1320 1320 1320 1320 1320 
11880 11880 11880 11880 11880 11880
*/
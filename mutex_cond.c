#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t *co = NULL;

int n, global = 0;
void *sample(void *arg){

    int k = (int)*(int*) arg;

    for (int c=0; c < 5; c++)
    {
        pthread_mutex_lock(&m);
        if (k!= global)
            pthread_cond_wait(&co[k], &m);

        printf("%d ", k);

        if (global >= n-1)
            global = 0;
        else
            global++;
        pthread_cond_signal(&co[global]);
        
        pthread_mutex_unlock(&m);
    }
    return NULL;
}


int main(int argc, char* argv[]){
    printf("Enter the number of Threads: ");
    scanf("%d", &n);

    pthread_t *t = (pthread_t *)malloc(sizeof(pthread_t)*n);
    co = (pthread_cond_t *)malloc(sizeof(pthread_cond_t)*n);

    for (int i=0; i<n; i++){
        pthread_cond_init(&co[i], NULL);
    }

    int arr[n];

    for (int i=0; i<n; i++){
        arr[i] = i;
        pthread_create(&t[i], NULL, sample, &arr[i]);
    }
    for (int j=0; j<n; j++){
        pthread_join(t[j], NULL);
    }

    free(co);
    free(t);
    printf("\n");
    return 0;
}

#include"new_matrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

typedef struct{
    int worker_id;
    matrix* matrix;
    INT64*  result;
} wargs;

static int free_worker_id;
BOOL sone_free;
pthread_mutex_t alock;
pthread_mutex_t cond_lock;
pthread_cond_t cond_free_worker;

void* run_det(void* args){
    int my_id = ((wargs*)args)->worker_id;
    matrix* m = ((wargs*)args)->matrix;
    INT64* ret = ((wargs*)args)->result;
    //do stuff
    *ret = determinant(m);
    pthread_mutex_lock(&cond_lock);
    sone_free = TRUE;
    free_worker_id = my_id;
    pthread_cond_signal(&cond_free_worker);
    pthread_mutex_unlock(&cond_lock);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    if(argc != 4){
        exit(1);
    }
    int workers = atoi(argv[1]);
    int matrix_size = atoi(argv[2]);
    int matrix_num = atoi(argv[3]);
    double start;
    double end;
    double time;
    matrix mlist[matrix_num];
    INT64 retlist[matrix_num];
    pthread_t threads[workers];
    pthread_attr_t attr;
    wargs args[workers];
    pthread_mutex_init(&alock, NULL);
    pthread_mutex_init(&cond_lock, NULL);
    pthread_cond_init(&cond_free_worker, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(int i = 0; i < matrix_num; i ++){
        mlist[i].size = matrix_size;
        init_rand_matrix(&mlist[i]);
    }
    start = (double) clock();
    sone_free = FALSE;
    for(int i = 0; i < workers; i++){
        args[i].worker_id = i;
        args[i].matrix = &mlist[i];
        args[i].result = &retlist[i];
        pthread_create(&threads[i], &attr, run_det, &args[i]);
    }
    for(int i = workers; i < matrix_num; i++){
        //allocate worker
        pthread_mutex_lock(&cond_lock);
        while(!sone_free){
            pthread_cond_wait(&cond_free_worker, &cond_lock);
        }
        pthread_create(&threads[free_worker_id], &attr, run_det, &args[free_worker_id]);
        sone_free = FALSE;
        pthread_mutex_unlock(&cond_lock);
    }
    for(int i = 0; i < workers; i++){
        pthread_join(threads[i], NULL);
    }
    end = (double) clock();  
    for(int i = 0; i < matrix_num; i++){
        destory_matrix(&mlist[i]);
    }

    time = (end - start) / CLOCKS_PER_SEC;
    printf("runtime : %lf s\n", time);
    for(int i = 0; i < matrix_num; i++){
        printf("%lld ", retlist[i]);
    }
    printf("\n");

    return 0;
}
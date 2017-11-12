#include"new_matrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>
#include<string.h>

void init_rand_matrix(matrix* m){
    static BOOL first = TRUE;
    if(first){
        first = FALSE;
        srand(time(NULL));
    }
    UINT64 square = pow(m->size, 2);
    m->field = (UINT64*) malloc(sizeof(UINT64) * square);
    assert(m->field);
    UINT64 index;
    for(index = 0; index < square; index++){
        m->field[index] = rand() % RAND_SIZE;
    }
}

void destory_matrix(matrix* m){
    assert(m->field);
    free(m->field);
}

void print_matrix(matrix* m){
    UINT64 index;
    UINT32 eol = m->size - 1;
    UINT64 square = pow(m->size, 2);
    for(index = 0; index < square; index++){
        if((index % m->size) == 0){
            printf("");
            printf("%4llu ", m->field[index]);
        }else if((index % m->size) == eol){
            printf("%4llu", m->field[index]);
            printf("\n");

        }else{
            printf("%4llu ", m->field[index]);
        }
    }
    printf("\n");
}

void calculate_determinant(matrix* m, BOOL* occupying, UINT32 col, INT64 ret, INT64* sum){
//void calculate_determinant(matrix* m, BOOL* occupying, UINT32 col, INT64 ret, INT64* sum, UINT32 ivn){
    UINT32 last = m->size;
    if(col == last){
        *sum += ret;
        return;
    }
    UINT32 the_choice;
    UINT32 inverse_num = 0;
    UINT32 tmp = 0;
    INT64 before = ret;
    for(the_choice = 0; the_choice < last; the_choice++){
        ret = before;
        if(occupying[the_choice] == TRUE){
            tmp ++;
            continue;
        }else{
            occupying[the_choice] = TRUE;
        }
        ///do stuff
        inverse_num = the_choice - tmp;
        if((inverse_num % 2)){
            ret = 0 - ret;
        }
        ret *= m->field[col * m->size + the_choice];
        calculate_determinant(m, occupying, col + 1, ret, sum);
        occupying[the_choice] = FALSE;
    }
}

INT64 determinant(matrix* m){
    UINT32 len = m->size;
    BOOL* occupying = (BOOL*) malloc(sizeof(UINT64) * len);
    assert(occupying);
    memset(occupying, 0, sizeof(UINT64) * len);
    //occupying[len] = NO_CHOICE;
    // UINT32 col = 0;
    // UINT32 inverse_num = 0;
    // UINT32 choice;
    INT64 ret = 0;
    calculate_determinant(m, occupying, 0, 1, &ret);
    // printf("%lld\n", ret);
    free(occupying);
    return ret;
}

// int main(int argc, char* argv[]){
//     matrix m;
//     if(argc != 2){
//         exit(1);
//     }
//     m.size = atoi(argv[1]);
//     init_rand_matrix(&m);
//     print_matrix(&m);
//     determinant(&m);
//     return 0;
// }
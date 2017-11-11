#ifndef NEW_MATRIX_H
#define NEW_MATRIX_H

typedef unsigned long long UINT64;
typedef unsigned int UINT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;
typedef long long INT64;
typedef int INT32;
typedef short INT16;
typedef char INT8;
typedef char BOOL;

#define TRUE 0x1
#define FALSE 0x0
#define RAND_SIZE 10
//#define NO_CHOICE -1;

typedef struct{
    UINT32 size;
    UINT64* field;
}matrix;

void init_rand_matrix(matrix* m);
void print_matrix(matrix* m);
INT64 determinant(matrix* m);
void calculate_determinant(matrix* m, BOOL* occupying, UINT32 col, INT64 ret, INT64* sum);
//void calculate_determinant(matrix* m, BOOL* occupying, UINT32 col, INT64 ret, INT64* sum, UINT32 ivn);

#endif
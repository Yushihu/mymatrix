#ifndef MYMATRIX_H
#define MYMATRIX_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define NUMGROW(num) ((num) = (num) + 64)
#define MAX_MATRIX_SIZE     64;


typedef struct{
    int numerator;
    int denominator;
}fraction;

typedef struct{
    int len;
    int count;
    unsigned int* list; 
}prime;

typedef struct{
    fraction* field;
    unsigned int size;
}matrix;
int myitoa(int num, char* buff);
int fractostring(const fraction* f, char* buff);
void insert_prime(prime* p, int pnum);
void init_prime_list(prime* p);
void destory_prime_list(prime* p);
void next_prime(prime* p);
void simplest_fraction(prime* plist, fraction* f);
void init_matrix(matrix* src);
void destory_matrix(matrix* src);
void print_matrix(matrix* src);
void print_fraction(const fraction* f);
int fraction2int(const fraction* f);
fraction fraction_reciprocal(const fraction* f);
fraction fraction_mutiplication(const fraction* f1, const fraction* f2);
fraction fraction_division(const fraction* f1, const fraction* f2);
fraction fraction_addition(const fraction* f1, const fraction* f2);
fraction fraction_subtraction(const fraction* f1, const fraction* f2);
fraction* get_faction_from_matrix(const matrix* src, unsigned int b, unsigned int a);
int determinant(const matrix* src);
void swap_lines(matrix* m, int s1, int s2);

#endif
#include"mymatrix.h"
#include<stdlib.h>
extern prime mp;

int main(int argc, char* argv[]){
    if(argc != 2)
        return 1;
    int arr[10];
    int i = 0;
    char buff[32] = {0};
    srand(time(NULL));
    init_prime_list(&mp);
    //unsigned int n = atoi(argv[1]);
    unsigned int n = 3;
    unsigned long start = time(NULL);
    matrix m1, m2;
    m1.size = atoi(argv[1]);
    // m1.size = 3;
    m2.size = n;
    init_matrix(&m1);
    print_matrix(&m1);
    int result;
    // fraction f1;
    // f1.numerator = atoi(argv[1]);
    // f1.denominator = atoi(argv[2]);
    // fraction f2;
    // f2.numerator = atoi(argv[3]);
    // f2.denominator = atoi(argv[4]);
    // fraction res;
    // res = fraction_addition(&f1, &f2);
    // print_fraction(&res);
    // printf("\n");
    // res = fraction_subtraction(&f1, &f2);
    // print_fraction(&res);
    // printf("\n");
    // res = fraction_mutiplication(&f1, &f2);
    // print_fraction(&res);
    // printf("\n");
    // res = fraction_division(&f1, &f2);    
    // print_fraction(&res);
    // printf("\n");
    // simplest_fraction(&mp, &f1);
    // print_fraction(&f1);
    // printf("\n");
    // print_fraction(&f1);
    // printf("\n");
    result = determinant(&m1);
    printf("%d\n",mp.count);
    // for(int i = 0; i < 1000000; i ++){
    //     next_prime(&mp);
    // }
    // for(int i = 0; i < 1000000; i ++){
    //     printf("%d ", mp.list[i]);
    // }
    // printf("\n");
    destory_matrix(&m1);
    destory_prime_list(&mp);
    return 0;
}
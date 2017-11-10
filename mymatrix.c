#include"mymatrix.h"
prime mp;
int myitoa(int src_num, char* buff){
    int flag;
    int num = abs(src_num);
    int begin;
    if(src_num < 0){
        flag = -1;
        begin = 0;
    }else{
        flag = 1;
        begin = -1;
    }
    if(num < 10){
        buff[0] = (char) num + 0x30;
        buff[1] = '\0';
        return 1;
    }
    int tmp = 1;
    int digit;
    int size = 0;
    while(tmp <= num){
        tmp *= 10;
        size ++;
    }
    if(flag == -1){
        size ++;
    }
    int i = size - 1;
    for(; i > begin; i --){
        digit = num % 10;
        buff[i] = (char) digit + 0x30;
        num /= 10;
    }
    if(flag == -1){
        buff[0] = '-';
    }
    buff[size] = '\0';
    return size;
}
void insert_prime(prime* p, int pnum){
    assert(p->list);
    if(p->count == p->len){
        unsigned int* new = (unsigned int*) malloc(sizeof(int) * NUMGROW(p->len));
        assert(new);
        memcpy(new, p->list, (p->len - 64) * sizeof(int));
        free(p->list);
        p->list = new;
    }
    int left = 0;
    int right = p->count - 1;
    int position;
    while(left <= right){
        position = (left + right) / 2;
        if(p->list[position] > pnum){
            right = position - 1;
        }else if(p->list[position] < pnum){
            left = position + 1;
        }else{
            return;
        }
    }
    if(p->list[position] < pnum){
        position += 1;
    }
    int end = p->count;
    for(; position != end; end--){
        p->list[end] = p->list[end - 1];
    }
    p->list[position] = pnum;
    p->count += 1;
}

void init_prime_list(prime* p){
    p->list = (unsigned int*) malloc(sizeof(int) * 64);
    assert(p->list);
    p->len = 64;
    p->list[0] = 2;
    p->list[1] = 3;
    p->count = 2;
}

void destory_prime_list(prime* p){
    assert(p->list);
    p->count = 0;
    p->list = 0;
    free(p->list);
}

void next_prime(prime* p){
    unsigned int last_prime = p->list[p->count - 1];
    unsigned int cur = last_prime + 2;
    int i = 0;
    while(pow(p->list[i], 2) <= cur){
        if((cur % p->list[i]) == 0){
            cur += 2;
            i = 0;
        }else{
            i++;
        }
    }
    insert_prime(p, cur);
}

void simplest_fraction(prime* plist, fraction* f){
    int flag;
    if(f->numerator * f->denominator < 0){
        flag = -1;
    }else{
        flag = 1;
    }
    int numerator = abs(f->numerator);
    int denominator = abs(f->denominator);
    int i = 0;
    unsigned int min = numerator < denominator ? numerator : denominator;
    while(plist->list[i] <= min){
        if((numerator % plist->list[i]) == 0){
            if((denominator % plist->list[i]) == 0){
                numerator /= plist->list[i];
                denominator /= plist->list[i];
                i = 0;
                continue;
            }
        }
        i ++;
        if(i == plist->count){
            next_prime(plist);
        }
    }
    f->numerator = flag * numerator;
    f->denominator = denominator;
}

void init_matrix(matrix* src){
    unsigned long int square = pow(src->size, 2);
    src->field = (fraction*) malloc(square * sizeof(fraction));
    int i;
    for(i = 0; i < square; i++){
        src->field[i].numerator = rand() % 10;
        src->field[i].denominator = 1;
    }
}

void destory_matrix(matrix* src){
    if(src->field != NULL){
        free(src->field);
    }
}

void print_matrix(matrix* src){
    int i;
    int max_size = 0;
    int tmp;
    char format[16] = {0};
    char buff[32] = {0};
    unsigned long int square = pow(src->size, 2);
    unsigned int end = src->size - 1;
    for(i = 0; i < square; i++){
        tmp = fractostring(&src->field[i], buff);
        max_size = (max_size > tmp? max_size: tmp);
    }
    format[0] = '%';
    i = myitoa(max_size, format + 1);
    format[i + 1] = 's';
    format[i + 2] = ' ';
    format[i + 3] = '\0';
    for(i = 0; i < square; i++){
        if(i % src->size == 0){
            printf("|");
            fractostring(&src->field[i], buff);
            printf(format, buff);
        }else if(i % src->size == end){
            fractostring(&src->field[i], buff);
            printf(format, buff);
            printf("|\n");
        }else{
            fractostring(&src->field[i], buff);
            printf(format, buff);
        }
    }
}

int fractostring(const fraction* f, char* buff){
    assert(buff);
    int size = 0;
    if(f->numerator == 0){
        size = 1;
        buff[0] = '0';
        buff[1] = '\0';
        return size;
    }else if(f->denominator == 1){
        size = myitoa(f->numerator, buff);
        return size;
    }
    size = myitoa(f->numerator, buff);
    buff[size] = '/';
    size += myitoa(f->denominator, buff + size + 1);
    size += 1;
    return size;
}

void print_fraction(const fraction* f){
    printf("%d/%d", f->numerator, f->denominator);
}

int fraction2int(const fraction* f){
    return f->numerator / f->denominator;
}

fraction fraction_reciprocal(const fraction* f){
    fraction ret;
    ret.numerator = f->denominator;
    ret.denominator = f->numerator;
    return ret;
}

fraction fraction_mutiplication(const fraction* f1, const fraction* f2){
    fraction ret;
    fraction tmp1;
    fraction tmp2;
    tmp1.numerator = f2->numerator;
    tmp1.denominator = f1->denominator;
    simplest_fraction(&mp, &tmp1);
    tmp2.numerator = f1->numerator;
    tmp2.denominator = f2->denominator;
    simplest_fraction(&mp, &tmp2);
    ret.numerator = tmp1.numerator * tmp2.numerator;
    ret.denominator = tmp1.denominator * tmp2.denominator;
    return ret;
}

fraction fraction_division(const fraction* f1, const fraction* f2){
    fraction ret;
    fraction divisor = fraction_reciprocal(f2);
    ret = fraction_mutiplication(f1, &divisor);
    return ret;
}

fraction fraction_addition(const fraction* f1, const fraction* f2){
    fraction ret;
    ret.numerator = f1->numerator * f2->denominator + f2->numerator * f1->denominator;
    ret.denominator = f1->denominator * f2->denominator;
    simplest_fraction(&mp, &ret);
    return ret;
}

fraction fraction_subtraction(const fraction* f1, const fraction* f2){
    fraction ret;
    ret.numerator = f1->numerator * f2->denominator - f2->numerator * f1->denominator;
    ret.denominator = f1->denominator * f2->denominator;
    simplest_fraction(&mp, &ret);
    return ret;
}

fraction* get_faction_from_matrix(const matrix* src, unsigned int b, unsigned int a){
    if(a >= src->size || b >= src->size){
        return NULL;
    }
    return &(src->field[b * src->size + a]);
}

int determinant(const matrix* src){
    matrix tmp;
    unsigned long int square = pow(src->size, 2);
    tmp.size = src->size;
    tmp.field = (fraction*) malloc(sizeof(fraction) * square);
    assert(tmp.field);
    memcpy(tmp.field, src->field, sizeof(fraction) * square);
    int a = 0;
    int b = 0;
    int k = 0;
    fraction ratio;
    fraction delta;
    fraction* arg1;
    fraction* arg2;
    fraction* arg3;
    fraction* target;
    print_matrix(&tmp);
    for(; b < tmp.size - 1; b++){
        arg1 = get_faction_from_matrix(&tmp, b, b);
        if(arg1->numerator == 0){
            int i;
            fraction* ftmp;
            for(i = b + 1; i < tmp.size; i++){
                ftmp = get_faction_from_matrix(&tmp, i, b);
                if(ftmp->numerator != 0){
                    swap_lines(&tmp, b, i);
                    break;
                }
                if(i == tmp.size){
                    return 0;
                }
            }
        }
        for(a = b + 1; a < tmp.size; a++){
            arg2 = get_faction_from_matrix(&tmp, a, b);
            ratio = fraction_division(arg2, arg1);
            print_fraction(&ratio);
            printf("\n");
            for(k = 0; k < tmp.size; k++){
                target = get_faction_from_matrix(&tmp, a, k);
                arg3 = get_faction_from_matrix(&tmp, b, k);
                delta = fraction_mutiplication(arg3, &ratio);
                *target = fraction_subtraction(target, &delta);
            }
            print_matrix(&tmp);
            printf("\n");
        }
    }
    print_matrix(&tmp);
    return 0;
}

void swap_lines(matrix* m, int s1, int s2){
    fraction* tmp = (fraction*) malloc(sizeof(fraction) * m->size);
    assert(tmp);
    fraction* arg1 = get_faction_from_matrix(m, s1, 0);
    fraction* arg2 = get_faction_from_matrix(m, s2, 0);
    memcpy(tmp, arg1, sizeof(fraction) * m->size);
    memcpy(arg1, arg2, sizeof(fraction) * m->size);
    memcpy(arg2, tmp, sizeof(fraction) * m->size);
    free(tmp);
}
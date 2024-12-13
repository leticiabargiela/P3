#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h>

#include "my_lib.h"

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)
#define DEFAULT_STACK_LEN 10

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "error sintaxis; uso: ./reader <nombre_pila>\n");
        return -1;
    }

    struct my_stack *stack = my_stack_read(argv[1]);
    if (stack == NULL) {
        printf("pila %s no existe\n", argv[1]);
        return 0;
    }

    struct my_stack_node *ptr = stack->top;
    int len = my_stack_len(stack);
    int limite = min(len, DEFAULT_STACK_LEN);
    printf("stack length: %d\n", len);

    int min_val = 0, max_val = 0;
    long sum = 0;
    int cont = 0;
    while (ptr != NULL && cont < limite) {
        int value = *(int *)ptr->data;
        printf("%d\n", value);
        sum += value;
        if(cont == 0){
            min_val = value;
            max_val = value;
        } else {
            min_val = min(min_val, value);
            max_val = max(max_val, value);
        }
        ptr = ptr->next;
        cont++;
    }

    int avg = sum / len;
    printf("\nitems: %d; sum: %ld; min: %d; max: %d; average: %d\n", len, sum, min_val, max_val, avg);
    my_stack_purge(stack);

    return 0;
}
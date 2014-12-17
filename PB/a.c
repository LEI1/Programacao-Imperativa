#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LINE_LENGTH 100000
#define INT_MAX 1000


char *str_dup(const char *s)
{
    char *result = (char *) malloc(strlen(s) + 1);
    strcpy(result, s);
    return result;
}

int str_readline(FILE *f, char *s)//USADO NA strings_read(FILE *f, char **a)
{
    int result = EOF;
    char *p = fgets(s, INT_MAX, f);
    if (p != NULL)
    {
        result = (int) strlen(s);
        if (result > 0 && s[result-1] == '\n')
            s[--result] = '\0';
    }
    return result;
}

int strings_read(FILE *f, char **a)//READS THE STRINGS
{
    int result = 0;
    char line[MAX_LINE_LENGTH];
    while (str_readline(f, line) != EOF)
        a[result++] = str_dup(line);
    return result;
}


int strings_copy(char **a, int n, char **b)
{
    if (n < 0)
        n = 0;
    memmove(b, a, n * sizeof(char*));
    return n;
}

int strings_merge(char **a, int n, char **b, int m, char **c)
{
    int result = 0;
    int i = 0;
    int j = 0;
    while (i < n && j < m)
    {
        if (strcmp(a[i], b[j]) <= 0)
            c[result++] = a[i++];
        else
            c[result++] = b[j++];
    }
    result += strings_copy(a + i, n - i, c+result);
    result += strings_copy(b + j, m - j, c+result);
    return result;
}

void strings_msort_i(char **a, int n, char **b)
{
    if (n > 1)
    {
        int m = n / 2;
        strings_msort_i(a, m, b);
        strings_msort_i(a+m, n-m, b);
        strings_merge(a, m, a+m, n-m, b);
        strings_copy(b, n, a);
    }
}

 int strings_count_while_greated_and_equal(char **a, int n, char *x)
 {
         int result = 0;
         while (result < n && strcmp(x, a[result]) == 0){
                 result++;
         }
         return result;
 }

 int garrafas(char **a, int n, char **b, int x)
 {

         int result = 0,
                 i = 0
         ;
         while ( i < n)
         {
             
                 int tmp = strings_count_while_greated_and_equal(a + i , n - i, a[i]);
                 if( tmp >= x )
                    b[result++] = a[i];
                 i += tmp;
         }
         return result;
 }

/////////////////////////////////////////MAIN

int main(int argc, char *argv[]){
    
    int x = 0;
    
    char *a[100000];
    char *ordenado[100000];
    char *tmp_arr[100000];
    FILE *f = fopen( argv[1], "r" );
    
    int a_len = strings_read(f, a);
    
    strings_msort_i(a, a_len, ordenado);//ordenar garrafas
    scanf("%d", &x);//ler garrafas
    int tmp_size = garrafas(ordenado, a_len, tmp_arr, x);
    printf("%d\n",  tmp_size);
    
    for(int i = 0; i < tmp_size; i++){
        printf("%s\n", tmp_arr[i]);
    }
}


#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct{
    const char *departure;
    const char *destination;
} Flights;

Flights _Flights(char *departure, char *destination){
    Flights F;
    F.departure = departure;
    F.destination = destination;
    return F;
}

char *str_dup(const char *s)
{
    char *result = (char *) malloc(strlen(s) + 1);
    strcpy(result, s);
    return result;
}

int flights_read(FILE *f, Flights *a)
{
    int result = 0;
    char departure[64];
    char destination[64];
    while (fscanf(f, "%s%s", departure, destination) != EOF)
        a[result++] = _Flights( str_dup(departure), str_dup(destination) );
    return result;
}


int direct_exists(Flights *a, int n,  Flights b){
    for(int i = 0; i < n; i++){
        //printf("%s->%s|%s->%s\n", a[i].departure, a[i].destination, b.departure,  b.destination);
        if( strcmp(a[i].departure, b.departure) == 0 && strcmp(a[i].destination, b.destination) == 0){
            return 1;
        }
    }
    return 0;
}

int check_links(Flights *a, int n, Flights b){
    
//    char origem_a_encontrar[64] = b.departure;
//    char destino_a_encontrar[64] = b.destination;
    int quantas_ligacoes = 0;
    for(int i = 0; i < n; i++){
        if( strcmp(a[i].departure, b.departure) == 0){
            for(int j = 0; j < n; j++){
                if( strcmp(a[i].destination, a[j].departure) == 0 && strcmp(a[j].destination, b.destination) == 0 ){
                    quantas_ligacoes++;
                }
            }
        }
    }
    return quantas_ligacoes;
    
}

int main(int argc, char *argv[]){
    
    //FILE *f = fopen("flights.txt", "r");//teste
    FILE *f = fopen(argv[1], "r");
    
    Flights flights_list[1000];
    
    int n_flights_list = flights_read(f, flights_list);
    
    char origem[64],
         destino[64]
    ;
//    for(int i = 0; i < 100; i++){
//        printf("%s-->%s\n", flights_list[i].departure, flights_list[i].destination);
//    }
    Flights input_console[1000];

    int input_count = 0;
    
    while( scanf("%s%s", origem, destino) != EOF ){
        
        input_console[input_count++] = _Flights(str_dup(origem), str_dup(destino));
//        printf("%s %s\n", input_console[input_count-1].departure, input_console[input_count-1].destination);
        
    }
    
//    input_console[0] = _Flights("porto", "athens");
//    input_console[1] = _Flights("faro", "berlin");
//    input_console[2] = _Flights("faro", "madrid");
//    input_console[3] = _Flights("porto", "london");
//    input_console[4] = _Flights("faro", "dublin");
    
    //input_count = 5;

    for(int i = 0; i < input_count; i++){
        int d = direct_exists(flights_list, n_flights_list, input_console[i]);
        int l = check_links(flights_list, n_flights_list, input_console[i]);
        printf("%d ", d);
        printf("%d\n", l);
    }
    
    return 0;
}






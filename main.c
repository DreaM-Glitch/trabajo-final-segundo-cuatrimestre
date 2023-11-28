
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <windows.h>
#include"pacientes.h"


#define ROJO 12
#define VERDE 10
#define AMARILLO 14
#define MAGENTA 13
#define CYAN 11
#define BLANCO 15





int main()
{
    char salir='a';
    while(salir!='s')
    {
        system("cls");
        inicio();
        printf("\nIngrese s para salir del programa: ");
        fflush(stdin);
        scanf("%c",&salir);
    }
    printf("\n");
    puts("========================================================================================================================");
    printf("\t\t\t\t\t HASTA LA PROXIMA, QUE TENGA BUEN DIA \n");
    puts("========================================================================================================================");
    printf("\n");

}

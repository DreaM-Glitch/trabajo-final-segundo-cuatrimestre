

//#include <stdlib.h>
#include <stdio.h>
//#include "string.h"
#include <windows.h>
#include"pacientes.h"

///CONSTANTES
#define ROJO 12
#define VERDE 10
#define AMARILLO 14
#define MAGENTA 13
#define CYAN 11
#define BLANCO 15

void inicio()
{
    system("cls");
    int menu;
    char eleccion='v';
    while(eleccion=='v')
    {
        system("cls");
        menu=menuPrincipal();
        printf("Para volver atras presione 'v' en caso contrario presione cualquier letra: ");
        fflush(stdin);
        scanf("%c",&eleccion);

    }
    opciones(menu);

}
void opciones(int menu)
{
    int validacion=0;
    int validos;
    int ingreso=0;
    char eleccion='s';
    nodoarbol* arbol;
    fila filita;
    transporte ambulancia;
    arbol=inicarbol();
    celdaHospital arregloHospital[20];


    switch(menu)

    {
    case 1:
        printf("cargando, por favor espere...\n");
        Sleep(1200);
        system("cls");
        arbol = pasarArchivoArbol(arbol);
        inorden(arbol);
        break;

    case 2:
        system("cls");
        validos=agregarPacientes(arregloHospital,10);
        recorreArreglo(arregloHospital,validos);

        break;
    case 3:
        crearFila(&filita);
        while(eleccion=='s'){
                ingreso=0;
             while(ingreso!=3){
            printf("\nIngrese 0 para cargar o 1 para retirar ambulancias,presione 3 para salir: ");
            fflush(stdin);
            scanf("%i",&ingreso);
            if(ingreso==1){
                    eliminarPrimerNodo(&filita);

            }
            if(ingreso==0){
                    ambulancia=cargarAmbulancia();
                    insertarFila(&filita,ambulancia);
            }
        }

        printf("\nIngrese s para continuar");
        fflush(stdin);
        scanf("%c",&eleccion);

        }
        mostrarAmbulancias(&filita);

        break;
    case 4:


        break;



    }

}
int menuPrincipal()
{

    int opcion;
    int flag=0;

    while(flag==0)
    {
printf("\n");
    puts("========================================================================================================================");
        printf("\t\t\t\t    BIENVENIDO AL HOSPITAL TRINIDA DE MAR DEL PLATA\n");
        printf("\t\t\t\t\t|1. Ver Pacientes Atendidos           |\n");
        printf("\t\t\t\t\t|2. Cargar Paciente Atendido\t      |\n");
        printf("\t\t\t\t\t|3. Control de Ambulancias\t      |\n");

        printf("\t\t\t\t\t|4. Salir\t\t              |\n");
        printf("\n");
    puts("========================================================================================================================");
        fflush(stdin);
        scanf("%i",&opcion);
        if(opcion==1 || opcion==2 || opcion==3 || opcion==4)
        {
            flag=1;
        }


        else
        {
            printf("Ese numero no se encuentra disponible, ingrese uno de los disponibles en el menu");
        }

    }


}

nodoarbol* inicarbol()
{
    return NULL;
}


nodoarbol* crearnodo(Registro pacientes)
{
    nodoarbol* aux=(nodoarbol*)malloc(sizeof(nodoarbol));
    aux->paciente.idPaciente=pacientes.idPaciente;
    aux->paciente.idRegistro=pacientes.idRegistro;
    strcpy(aux->paciente.nombrePaciente, pacientes.nombrePaciente);
    strcpy(aux->paciente.apellido,pacientes.apellido);
    strcpy(aux->paciente.diagnostico, pacientes.diagnostico);
    aux->paciente.fechaantencion=pacientes.fechaantencion;
    strcpy(aux->paciente.nombredoctor,pacientes.nombredoctor);
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}


nodoarbol* InsertarNodo(nodoarbol* arbol,nodoarbol* aux)
{

    if (arbol==NULL)
    {
        arbol=aux;

    }
    else
    {

        if (aux->paciente.idPaciente<arbol->paciente.idPaciente)
        {
            arbol->izq=InsertarNodo(arbol->izq,aux);
        }
        else
        {
            arbol->der=InsertarNodo(arbol->der,aux);
        }


    }
    return arbol;
}

void inorden(nodoarbol* arbol)
{
    if(arbol!=NULL)
    {

        inorden(arbol->izq);
        escribir(arbol);
        inorden(arbol->der);
    }
}



void escribir(nodo* aux)
{
    puts("\n------------------------------------------------------------");
    printf("ID DEL PACIENTE: %i", aux->paciente.idPaciente);
    printf("\nID DEL REGISTRO: %i", aux->paciente.idRegistro);
    printf("\nNOMBRE DEL PACIENTE: %s", aux->paciente.nombrePaciente);
    printf("\nAPELIDO DEL PACIENTE: %s",aux->paciente.apellido);
    printf("\nDIAGNOSTICO DEL PACIENTE: %s", aux->paciente.diagnostico);
    printf("\nFECHA DE ATENCION DEL PACIENTE: %i",aux->paciente.fechaantencion);
    printf("\nNOMBRE DEL DOCTOR: %s",aux->paciente.nombredoctor);
    puts("\n------------------------------------------------------------\n");

}


int agregarEspecialidad(celdaHospital arreglo[],char especialidad[],int idEspecialidad, int validos)
{

    strcpy(arreglo[validos].especialidaMedica,especialidad);

    arreglo[validos].idEspecialidad=idEspecialidad;

    validos++;

    return validos;
}

int buscarEspecialidad(celdaHospital arreglo[],char especialidad[],int validos)
{
    int rta=-1;
    int i=0;

    for(i=0; i<validos; i++)
    {
        if (strcmpi(arreglo[validos].especialidaMedica,especialidad)==0)
        {
            rta=i;

        }
        i++;

    }

    return rta;

}




int alta(celdaHospital arreglo[],int validos, Registro paciente, int idEspecialidad, char especialidad[])
{
    nodoarbol*aux=crearnodo(paciente);

    int pos=buscarEspecialidad(arreglo,especialidad,validos);
    if (pos==-1)
    {
        validos=agregarEspecialidad(arreglo,especialidad,idEspecialidad,validos);
        pos = validos -1;

    }

    arreglo[pos].lista=agregarPrincipio(arreglo[pos].lista,aux);


    return validos;
}



int agregarPacientes(celdaHospital arreglo[], int dimension)
{
    int idEspecialidad;
    int validacion=0;
    Registro paciente;
    especialidad especialidades;
    char especialidad[30];
    char eleccion = 's';
    int validos = 0;

    while(eleccion=='s' && validos<dimension)
    {
        validacion=0;
        do{
        printf("\n Ingrese el ID de la especialidad: ");
        fflush(stdin);
        scanf("%i", &idEspecialidad);
        }while(idEspecialidad<0 || idEspecialidad> 10000000);


        while (validacion==0)
        {

            mostrarEspecialidades();
            printf("\nIngrese la especialidad a atenderse: ");
            fflush(stdin);
            gets(especialidad);
            validacion=comprobarEspecialidad(especialidad);
            if(validacion==0)
            {
                printf("\nPor favor ingrese una especialidad adecuada");
                system("cls");
            }
        }


        arreglo[validos].lista=inicLista();
        paciente=cargaDePacientes(especialidad);
        validos=alta(arreglo,validos,paciente,idEspecialidad,especialidad);
        printf("\nDesea agregar otro paciente: ");
        fflush(stdin);
        scanf("%c",&eleccion);
    }
    return validos;
}



Registro cargaDePacientes(char especialidad[])
{
    Registro paciente;
    int validacion=0;
    int pos;
    pos=retornarPosEspecialidad(especialidad);

    do
    {
        printf("\nIngrese la id del paciente: ");
        fflush(stdin);
        scanf("%i", &paciente.idPaciente);
    }
    while (paciente.idPaciente<0 || paciente.idPaciente>1000000);

    do
    {
        printf("Ingrese la id del registro: ");
        fflush(stdin);
        scanf("%i", &paciente.idRegistro);
    }
    while (paciente.idRegistro<0 || paciente.idPaciente>1000000);


    printf("Ingrese el nombre del paciente: ");
    fflush(stdin);
    gets(paciente.nombrePaciente);

    printf("Ingrese el apellido del paciente: ");
    fflush(stdin);
    gets(paciente.apellido);

    printf("Ingrese el diagnostico del paciente: ");
    fflush(stdin);
    gets(paciente.diagnostico);

    do
    {
        printf("Ingrese la fecha de la antencion del paciente: ");
        fflush(stdin);
        scanf("%i", &paciente.fechaantencion);
    }
    while (paciente.fechaantencion<1 || paciente.fechaantencion>31);

    while(validacion==0)
    {

        switch(pos)
        {
        case 1:
            mostrarPediatras();
            printf("\nIngrese el nombre del doctor: ");
            fflush(stdin);
            gets(paciente.nombredoctor);
            validacion=comprobarPediatria(paciente.nombredoctor);

            break;
        case 2:
            mostrarTraumatologos();
            printf("\nIngrese el nombre del doctor: ");
            fflush(stdin);
            gets(paciente.nombredoctor);
            validacion=comprobarTraumatologia(paciente.nombredoctor);

            break;
        case 3:
            mostrarCardiologos();
            printf("\nIngrese el nombre del doctor: ");
            fflush(stdin);
            gets(paciente.nombredoctor);
            validacion=comprobarCardiologia(paciente.nombredoctor);

            break;
        case 4:
            mostrarDermatologos();
            printf("\nIngrese el nombre del doctor: ");
            fflush(stdin);
            gets(paciente.nombredoctor);
            validacion=comprobarDermatologia(paciente.nombredoctor);

            break;
        case 5:
            mostrarOftalmologos();
            printf("\nIngrese el nombre del doctor: ");
            fflush(stdin);
            gets(paciente.nombredoctor);
            validacion=comprobarOftalmologia(paciente.nombredoctor);

            break;
        case 6:

            mostrarOncologos();
            printf("\nIngrese el nombre del doctor: ");
            fflush(stdin);
            gets(paciente.nombredoctor);
            validacion=comprobarOncologia(paciente.nombredoctor);

            break;
        case 7:
             mostrarUrologos();
            printf("\nIngrese el nombre del doctor: ");
            fflush(stdin);
            gets(paciente.nombredoctor);

            validacion=comprobarUrologia(paciente.nombredoctor);
            break;

        }
        if(validacion==0)
        {
            printf("\nPor favor ingrese un nombre apto para su doctor\n\n");

        }
    }


    return paciente;
}

int retornarPosEspecialidad(char especialidadMedic[])
{
    FILE *archi;
    int i=1;
    int contador;
    especialidad especialidades;

    archi = fopen("archivoEspecialidad.bin", "rb");

    if(archi!=NULL)
    {
        while(fread(&especialidades,sizeof(especialidades),1,archi)==1)
        {
            if (strcmpi(especialidades.nombreEspecialidad,especialidadMedic)==0)
            {

                contador=i;
            }
            else
            {
                i++;
            }

        }

    }
    return contador;

}



nodo* inicLista()
{
    return NULL;
}


nodo* crearNodolista(Registro paciente)
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));
    aux->paciente.idPaciente=paciente.idPaciente;
    aux->paciente.idRegistro=paciente.idRegistro;
    strcpy(aux->paciente.nombrePaciente, paciente.nombrePaciente);
    strcpy(aux->paciente.apellido,paciente.apellido);
    strcpy(aux->paciente.diagnostico, paciente.diagnostico);
    aux->paciente.fechaantencion=paciente.fechaantencion;
    strcpy(aux->paciente.nombredoctor,paciente.nombredoctor);
    aux->siguiente == NULL;
    return aux;
}


nodo* agregarPrincipio(nodo* lista, nodo* aux)
{
    if(lista==NULL)
    {
        lista = aux;
    }
    else
    {
        aux->siguiente = lista;
        lista = aux;
    }
    return lista;
}


///FUNCIONES PARA FILAS
void crearFila(fila* fila)
{
    fila->inicio = iniclista2();
    fila->fin = iniclista2();
}

int filaVacia(fila *fila)
{
    return fila->inicio==NULL;
}


nodo2*crearNodoFila(transporte ambulancias)
{
    nodo2* aux= (nodo2*)malloc(sizeof(nodo2));
    strcpy(aux->ambulancia.conductor,ambulancias.conductor);

    aux->ambulancia.idAmbulancia=ambulancias.idAmbulancia;
    aux->siguiente=NULL;
    return aux;
}


void insertarFila (fila *fila, transporte ambulancia)
{
    nodo2* aux=crearNodoFila(ambulancia);


    if (fila->inicio==NULL)
    {
        fila->inicio = aux;
        fila->fin=aux;
    }
    else
    {
        fila->fin->siguiente=aux;
        fila->fin=aux;
    }
}

transporte frente(fila* fila )
{
    if(filaVacia(fila))
    {
        puts("Underflow");
        exit(1);
    }
    return fila->inicio->ambulancia;
}

void eliminarPrimerNodo(fila* fila)
{
    if(fila->inicio)
    {
nodo2* aux = fila->inicio;
    fila->inicio = fila->inicio->siguiente;
    free(aux);
    if(!fila->inicio){
        fila->fin=NULL;
    }
    }


}


transporte cargarAmbulancia()
{
    transporte ambulancia;

    printf("Ingrese el nombre del conductor: ");
    fflush(stdin);
    gets(ambulancia.conductor);
    do{
        printf("ingrese el id de identificacion de la ambulancia: ");
        fflush(stdin);
        scanf("%i",&ambulancia.idAmbulancia);
    }while(ambulancia.idAmbulancia<0 || ambulancia.idAmbulancia>100000000);

return ambulancia;
}

void mostrarAmbulancias(fila* filita){

recorreYmostrar(filita->inicio);
}

void recorreYmostrar(nodo2*lista){


    while(lista!=NULL){

    printf("\nEl id de su ambulancia es: %i",lista->ambulancia.idAmbulancia);
    printf("\nEl nombre del chofer es: %s",lista->ambulancia.conductor);
    lista=lista->siguiente;

    }


}


nodo2* iniclista2(){
return NULL;
}
nodo2* agregarPrincipio2(nodo2* lista, nodo2* aux)
{
    if(lista==NULL)
    {
        lista = aux;
    }
    else
    {
        aux->siguiente = lista;
        lista = aux;
    }
    return lista;
}


void recorreArreglo(celdaHospital arregloHospital[],int validos)
{
    int i=0;

    for(i=0; i<validos; i++)
    {

        pasarListaArchivo(arregloHospital[i].lista);


    }

}


void pasarListaArchivo(nodo* lista)
{
    FILE *archi;
    Registro paciente;
    archi=fopen("registroPacientes.bin","ab");

    if(archi!=NULL)
    {
        while(lista!=NULL)
        {


            paciente=lista->paciente;
            fwrite(&paciente,sizeof(Registro),1,archi);
            lista=lista->siguiente;
        }


        fclose(archi);
    }
    else
    {
        printf("el archivo no existe.\n");
    }
}


nodoarbol* pasarArchivoArbol(nodoarbol* arbol)
{
    FILE *archi;
    nodoarbol* aux;
    Registro paciente;
    archi = fopen("registroPacientes.bin", "rb");

    if (archi != NULL)
    {

        while (fread(&paciente, sizeof(Registro), 1, archi) == 1)
        {
            aux = crearnodo(paciente);
            arbol = InsertarNodo(arbol, aux);

        }

        fclose(archi);

        return arbol;

    }
    else
    {
        printf("El archivo no existe.\n");
        return NULL;  // Si el archivo no existe, devolvemos NULL
    }

}


 void color(int color)
 {
 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleTextAttribute(hConsole, color);
 }


doctores nombreMedicos()
{

    FILE* archi=fopen("archivoMedicos.bin","ab");
    doctores doc;
    char eleccion='s';
    if(archi!=NULL)
    {
        printf("Ingrese s si desea cargar el nombre de un medico al archivo: ");
        fflush(stdin);
        scanf("%c", &eleccion);
        while(eleccion=='s')
        {
            printf("Ingrese el nombre del medico: ");
            fflush(stdin);
            gets(doc.nombre);

            fwrite(&doc,sizeof(doctores),1,archi);

            printf("Ingrese s si desea cargar otro doctor: ");
            fflush(stdin);
            scanf("%c", &eleccion);
        }
    }
    fclose(archi);
}


void nombreEspecialidad()
{
    FILE* archi=fopen("archivoEspecialidad.bin","ab");
    char eleccion='s';
    especialidad espe;
    if(archi!=NULL)
    {
        printf("Ingrese s si desea cargar una especialidad al archivo: ");
        fflush(stdin);
        scanf("%c", &eleccion);
        while(eleccion=='s')
        {
            printf("Ingrese el nombre de la especialidad: ");
            fflush(stdin);
            gets(espe.nombreEspecialidad);

            fwrite(&espe,sizeof(especialidad),1,archi);

            printf("Ingrese s si desea cargar otra especialidad: ");
            fflush(stdin);
            scanf("%c", &eleccion);
        }
    }
    fclose(archi);
}


void mostrarEspecialidades()
{
    FILE *archi;
    especialidad especialidades;
    archi = fopen("archivoEspecialidad.bin", "rb");

    if(archi!=NULL)
    {
        printf("---------------ESPECIALIDADES---------------\n");

        while(fread(&especialidades,sizeof(especialidades),1,archi)==1)
        {
            printf("\t\t%s\n",especialidades.nombreEspecialidad);
        }


        fclose(archi);
    }

}
int comprobarEspecialidad(char especialidadMedic[])
{
    FILE *archi;
    especialidad especialidades;
    int validacion=0;
    archi = fopen("archivoEspecialidad.bin", "rb");

    if(archi!=NULL)
    {
        while(fread(&especialidades,sizeof(especialidades),1,archi)==1)
        {
            if (strcmpi(especialidades.nombreEspecialidad,especialidadMedic)==0)
            {

                validacion=1;
            }

        }


        fclose(archi);
    }
    return validacion;


}
int comprobarPediatria(char nombredoctor[])
{
    doctores doctor;
    int validacion=0;
    FILE *archi=fopen("archivoPediatras.bin","rb");
    if(archi!=NULL)
    {
        while((fread(&doctor,sizeof(doctores),1,archi)==1))
        {
            if(strcmpi(doctor.nombre,nombredoctor)==0)
            {
                validacion=1;
            }
        }

        fclose(archi);

    }


    return validacion;
}

int comprobarTraumatologia(char nombredoctor[])
{
    doctores doctor;
    int validacion=0;
    FILE *archi=fopen("archivoTraumatologos.bin","rb");
    if(archi!=NULL)
    {
        while((fread(&doctor,sizeof(doctores),1,archi)==1) && (validacion==0))
        {
            if(strcmpi(doctor.nombre,nombredoctor)==0)
            {
                validacion=1;
            }
        }



        fclose(archi);

    }


    return validacion;
}

int comprobarCardiologia(char nombredoctor[])
{
    doctores doctor;
    int validacion=0;
    FILE *archi=fopen("archivoCardiologos.bin","rb");
    if(archi!=NULL)
    {
        while((fread(&doctor,sizeof(doctores),1,archi)==1) && (validacion==0))
        {
            if(strcmpi(doctor.nombre,nombredoctor)==0)
            {
                validacion=1;
            }
        }



        fclose(archi);

    }


    return validacion;
}

int comprobarDermatologia(char nombredoctor[])
{
    doctores doctor;
    int validacion=0;
    FILE *archi=fopen("archivoDermatologos.bin","rb");
    if(archi!=NULL)
    {
        while((fread(&doctor,sizeof(doctores),1,archi)==1) && (validacion==0))
        {
            if(strcmpi(doctor.nombre,nombredoctor)==0)
            {
                validacion=1;
            }
        }



        fclose(archi);

    }


    return validacion;
}

int comprobarOftalmologia(char nombredoctor[])
{
    doctores doctor;
    int validacion=0;
    FILE *archi=fopen("archivoOftalmologos.bin","rb");
    if(archi!=NULL)
    {
        while((fread(&doctor,sizeof(doctores),1,archi)==1) && (validacion==0))
        {
            if(strcmpi(doctor.nombre,nombredoctor)==0)
            {
                validacion=1;
            }
        }



        fclose(archi);

    }


    return validacion;
}
int comprobarUrologia(char nombredoctor[])
{
    doctores doctor;
    int validacion=0;
    FILE *archi=fopen("archivoUrologos.bin","rb");
    if(archi!=NULL)
    {
        while((fread(&doctor,sizeof(doctores),1,archi)==1) && (validacion==0))
        {
            if(strcmpi(doctor.nombre,nombredoctor)==0)
            {
                validacion=1;
            }
        }



        fclose(archi);

    }


    return validacion;
}

int comprobarOncologia(char nombredoctor[])
{
    doctores doctor;
    int validacion=0;
    FILE *archi=fopen("archivoOncologos.bin","rb");
    if(archi!=NULL)
    {
        while((fread(&doctor,sizeof(doctores),1,archi)==1) && (validacion==0))
        {
            if(strcmpi(doctor.nombre,nombredoctor)==0)
            {
                validacion=1;
            }
        }



        fclose(archi);

    }



    return validacion;
}

void mostrarPediatras()
{
    FILE* archi=fopen("archivoPediatras.bin","rb");
    doctores doc;

    if(archi!=NULL)
    {
        printf("---------------PEDIATRAS---------------\n");
        while(fread(&doc,sizeof(doctores),1,archi)==1)
        {
            printf("\t\t%s\n",doc.nombre);
        }
        fclose(archi);
    }
}

void mostrarTraumatologos()
{
    FILE* archi=fopen("archivoTraumatologos.bin","rb");

    doctores doc;

    if(archi!=NULL)
    {
        printf("---------------TRAUMATOLOGOS---------------\n");
        while(fread(&doc,sizeof(doctores),1,archi)==1)
        {
            printf("\t\t%s\n",doc.nombre);
        }
        fclose(archi);
    }
}

void mostrarCardiologos()
{
    FILE* archi=fopen("archivoCardiologos.bin","rb");

    doctores doc;

    if(archi!=NULL)
    {
        printf("---------------CARDIOLOGOS---------------\n");
        while(fread(&doc,sizeof(doctores),1,archi)==1)
        {
            printf("\t\t%s\n",doc.nombre);
        }
        fclose(archi);
    }
}

void mostrarOftalmologos()
{
    FILE* archi=fopen("archivoOftalmologos.bin","rb");

    doctores doc;

    if(archi!=NULL)
    {
        printf("---------------OFTALMOLOGOS---------------\n");
        while(fread(&doc,sizeof(doctores),1,archi)==1)
        {
            printf("\t\t%s\n",doc.nombre);
        }
        fclose(archi);
    }
}



void mostrarOncologos()
{
    FILE* archi=fopen("archivoOncologos.bin","rb");

    doctores doc;

    if(archi!=NULL)
    {
        printf("---------------ONCOLOGOS---------------\n");
        while(fread(&doc,sizeof(doctores),1,archi)==1)
        {
            printf("\t\t%s\n",doc.nombre);
        }
        fclose(archi);
    }
}

void mostrarUrologos()
{
    FILE* archi=fopen("archivoUrologos.bin","rb");

    doctores doc;

    if(archi!=NULL)
    {
        printf("---------------UROLOGOS---------------\n");
        while(fread(&doc,sizeof(doctores),1,archi)==1)
        {
            printf("\t\t%s\n",doc.nombre);
        }
        fclose(archi);
    }
}

void mostrarDermatologos()
{
    FILE* archi=fopen("archivoDermatologos.bin","rb");

    doctores doc;

    if(archi!=NULL)
    {
        printf("---------------DERMATOLOGOS---------------\n");
        while(fread(&doc,sizeof(doctores),1,archi)==1)
        {
            printf("\t\t%s\n",doc.nombre);
        }
        fclose(archi);
    }
}

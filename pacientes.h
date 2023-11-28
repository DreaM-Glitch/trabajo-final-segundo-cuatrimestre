#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED

typedef struct
{
    int idAmbulancia;
    char conductor[30];

} transporte;

typedef struct
{
    int idPaciente;
    int idRegistro;
    char nombrePaciente[30];
    char apellido[30];
    char diagnostico[30];
    int fechaantencion;
    char nombredoctor[30];
} Registro;

typedef struct
{
    Registro paciente;
    struct nodoarbol* izq;
    struct nodoarbol* der;
} nodoarbol;



typedef struct
{
    Registro paciente;
    struct nodo* siguiente;
} nodo;

typedef struct
{
    nodo* lista;
    int idEspecialidad;
    char especialidaMedica[30];
} celdaHospital;

typedef struct
{
    transporte ambulancia;
    struct nodo2* siguiente;
} nodo2;

typedef struct
{
    nodo2* inicio;
    nodo2* fin;
} fila;

typedef struct
{
    char nombre[30];
} doctores;

typedef struct
{
    char nombreEspecialidad[30];
} especialidad;

///PROTOTIPADO DE FUNCIONES DE ARBOL
nodoarbol* inicarbol();
nodoarbol* crearnodo(Registro paciente);
nodoarbol* InsertarNodo(nodoarbol *arbol,nodoarbol* aux);
nodoarbol* pasarArchivoArbol(nodoarbol* arbol);
void inorden(nodoarbol* arbol);

///PROTOTIPADO FUNCIONES LISTA
nodo* inicLista();
nodo* agregarPrincipio(nodo* lista, nodo* aux);
void escribir(nodo* aux);


///PROTOTIPADO DE FUNCIONES TIPO INT
int agregarEspecialidad(celdaHospital arreglo[],char especialidad[],int idRegistro, int validos);
int buscarEspecialidad(celdaHospital arreglo[],char especialidad[],int validos);
int comprobarEspecialidad(char especialidad[]);
int comprobarPediatria(char nombredoctor[]);
int comprobarTraumatologia(char nombredoctor[]);
int comprobarCardiologia(char nombredoctor[]);
int comprobarDermatologia(char nombredoctor[]);
int comprobarOftalmologia(char nombredoctor[]);
int comprobarUrologia(char nombredoctor[]);
int comprobarOncologia(char nombredoctor[]);
int menuPrincipal();


///PROTOTIPADO DE FUNCIONES TIPO VOID
void inicio();
void opciones(int menu);
void color(int color);
void escribir(nodo* aux);
void mostrarEspecialidades();
void mostrarPediatras();
void nombreEspecialidad();
void mostrarPediatras();
void mostrarDermatologos();
void mostrarUrologos();
void mostrarOncologos();
void mostrarOftalmologos();
void mostrarCardiologos();
void mostrarTraumatologos();
///PROTOTIPADO DE FUNCIONES TIPO REGISTRO
Registro cargaDePacientes(char especialidad[]);
///FUNCIONES FILA
transporte cargarAmbulancia();
void eliminarPrimerNodo(fila *fila);
transporte frente(fila *fila );
void insertarFila (fila *fila, transporte ambulancia);
nodo2*crearNodoFila(transporte ambulancia);
int filaVacia(fila *fila);
void crearFila(fila *fila);
void mostrarAmbulancias(fila* filita);
void recorreYmostrar(nodo2* lista);
nodo2* iniclista2();
nodo2* agregarPrincipio2(nodo2* lista, nodo2* aux);
#endif // PACIENTES_H_INCLUDED

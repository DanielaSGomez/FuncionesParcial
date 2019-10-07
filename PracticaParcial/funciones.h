#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
typedef struct{
    int dia, mes, anio;
}eFecha;

typedef struct{
    int id;
    char descripcion[51];
    float importe;
}eMenues;

 typedef struct{
    int id;
    char descripcion[51];
 }eSector;

typedef struct{
    int legajo;
    char apellido[51];
    char nombre[51];
    char sexo;
    float salario;
    eFecha ingreso;
    int idSector;
    int isEmpty;
}eEmpleado;

typedef struct{
    int id;
    int idEmpleado;
    int idMenu;
    eFecha fecha;
    int isEmpty;
}eAlmuerzo;

//FUNCIONES DE EMPLEADO---------------------------------------------------------------------------------------------------------
int initEmpleados(eEmpleado emp[], int tam);
int buscarLugarEmpleado(eEmpleado emp[], int tam);
int buscarIdEmpleado(eEmpleado emp[], int tam, int legajo);
void mostrarUnEmpleado(eEmpleado emp, eSector sec[],int tamSec);
void listarEmpleados(eEmpleado emp[],int tam, eSector sec[], int tamSec);
int addEmpleados(eEmpleado emp[], int tam, eSector sec[], int tamSec);
int borrarEmpleado(eEmpleado emp[], int tam, eSector sec[], int tamSec);
int modifyEmpleado(eEmpleado emp[], int tam, eSector sec[], int tamSec);
int orderEmpleadosDescendente(eEmpleado emp[], int tam, eSector sec[], int tamSec);
eEmpleado getEmpleado(eEmpleado emp[], int tam, eSector sec[], int tamSec);

//FUNCIONES DE SECTORES---------------------------------------------------------------------------------------------------------
void listarSectores(eSector s[], int tam);
void mostrarSectores(eSector s[], int tam, int idSector, char cadena[]);
eSector getSector(eSector s[], int tam);

//FUNCIONES DE FECHAS-----------------------------------------------------------------------------------------------------------
eFecha getFecha(void);

//FUNCIONES DE MENUS------------------------------------------------------------------------------------------------------------
void listarMenues(eMenues m[], int tam);
void mostrarMenues(eMenues m[], int tam, int idMenu, char cadena[]);
eMenues getMenus(eMenues m[], int tam);
int totalYPromediosImportesMenu(eMenues men[], int tam);

//FUNCIONES DE ALMUERZOS--------------------------------------------------------------------------------------------------------
int initAlmuerzos(eAlmuerzo alm[], int tam);
int buscarLugarAlmuerzo(eAlmuerzo alm[], int tam);
int buscarIdAlmuerzo(eAlmuerzo alm[], int tam, int id);
int addAlmuerzo(eAlmuerzo alm[], int tam, eEmpleado emp[], int tamE, eSector sec[], int tamSec, eMenues men[], int tamM);
void mostrarUnAlmuerzo(eAlmuerzo alm, eEmpleado emp[], int tamE,eMenues menu[], int tamM);
void listarAlmuerzos(eAlmuerzo alm[], int tam, eEmpleado emp[], int tamE,eMenues men[], int tamM);

//SUBMENUDEINFORMES-------------------------------------------------------------------------------------------------------------
int submenuInformes(eEmpleado emp[], int tam, eAlmuerzo alm[], int tamA, eSector sec[], int tamSec, eMenues men[], int tamM);


#endif // FUNCIONES_H_INCLUDED

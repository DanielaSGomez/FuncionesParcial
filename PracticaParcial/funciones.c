#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "input.h"
#include "funciones.h"
#define LIBRE 0
#define OCUPADO 1


//FUNCIONES DE EMPLEADO----------------------------------------------------------------------------------------------------------
//generar id automaticamente
static int getLegajo()
{
    static int legajo = 0;
    legajo++;
    return legajo;
}

//FUNCION INICIALIZAR ARRAY EN LIBRE
int initEmpleados(eEmpleado emp[], int tam)
{
    int i;
    int retorno = -1;

    for(i=0; i<tam; i++)
    {
        emp[i].isEmpty= LIBRE; //LIBRE DEFINIDO COMO ENTERO 1 OCUPADO DEFINIDO COMO ENTERO 0
        retorno = 0;
    }
    return retorno;
}

//FUNCION BUSCAR LUGAR LIBRE PARA NUEVO ALTA

int buscarLugarEmpleado(eEmpleado emp[], int tam)
{
    int i;
    int retorno = -1;

    for(i=0; i<tam; i++)
    {
        if(emp[i].isEmpty == LIBRE)
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

//FUNCION BUSCAR SI EXISTE EL ELEMENTO SEGUN EL ID
int buscarIdEmpleado(eEmpleado emp[], int tam, int legajo)
{
    int i;
    int retorno = -1;

    for(i=0; i<tam; i++)
    {
        if(emp[i].isEmpty == OCUPADO && emp[i].legajo == legajo)
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

void mostrarUnEmpleado(eEmpleado emp, eSector sec[],int tamSec)
{
    char descripcion[51];
    int i;

    for(i=0;i<tamSec;i++)
    {
        if(emp.idSector == sec[i].id)
        {
            strcpy(descripcion,sec[i].descripcion);
            break;
        }
    }

    if(emp.isEmpty == OCUPADO)
    {
        printf("\n%d\t%s\t\t%s\t\t%d/%d/%d\t\t%s",emp.legajo,emp.apellido,emp.nombre,emp.ingreso.dia,emp.ingreso.mes,emp.ingreso.anio,descripcion);
    }
}

void listarEmpleados(eEmpleado emp[],int tam, eSector sec[], int tamSec)
{
    int i;

    printf("LEGAJO\tAPELLIDO\tNOMBRE\t\tFECHA \t\tSECTOR");

    for(i=0;i<tam;i++)
    {
        if(emp[i].isEmpty == OCUPADO)
        {
            mostrarUnEmpleado(emp[i], sec,tamSec);
        }
    }
}



//int buscarNombre(eEmpleado vec[], int tam)
//{
//    eEmpleado auxEmpleado;
//    int esta=-1;
//
//    printf("Ingrese Nombre: ");
//    scanf("%s",auxEmpleado.nombre);
//    auxEmpleado.nombre[0]=toupper(auxEmpleado.nombre[0]);
//
//    for(int i=0;i<tam;i++)
//    {
//        if(strcmp(auxEmpleado.nombre,vec[i].nombre)==0)
//        {
//            esta=i;
//            break;
//        }
//    }
//    return esta;
//}

//void buscarSexo(eEmpleado vec[], int tam, eSector sectores[], int tamSec)
//{
//    eEmpleado auxEmpleado;
//
//    printf("Ingrese sexo: ");
//    fflush(stdin);
//    scanf("%c",&auxEmpleado.sexo);
//
//    for(int i=0;i<tam;i++)
//    {
//        if(vec[i].sexo==auxEmpleado.sexo)
//        {
//            mostrarEmpleado(vec[i],sectores,TAMSEC);
//            system("pause");
//        }
//    }
//}

int addEmpleados(eEmpleado emp[], int tam, eSector sec[], int tamSec)
{
    int i;
    int retorno = -1;
    eSector auxSector;
     i = buscarLugarEmpleado(emp,tam);

    if(i == -1)
    {
        printf("\nNo hay lugar!!");
    }
    else
    {
        emp[i].legajo = getLegajo();
        myFgets(emp[i].apellido,51,"Ingrese apellido:");
        myFgets(emp[i].nombre,51,"Ingrese nombre:");
        getSex(emp[i].sexo);
        emp[i].salario = getValidFloat("Ingrese salario: ","Error",0,999999999);
        emp[i].ingreso = getFecha();
        auxSector= getSector(sec,tamSec);
        emp[i].idSector = auxSector.id;
        emp[i].isEmpty = OCUPADO;
        printf("\nSe dio de alta el registro...");
        retorno = 0;
    }
    return retorno;
}

eEmpleado getEmpleado(eEmpleado emp[], int tam, eSector sec[], int tamSec)
{
    int i;
    int idEmpleado;
    eEmpleado empElegido;
    empElegido.legajo = -1;

    do{
            listarEmpleados(emp,tam,sec,tamSec);
            idEmpleado = getValidInt("\nElija un empleado: ",1,tam);

            for(i=0;i<tam;i++)
            {
                if(emp[i].legajo == idEmpleado)
                {
                    empElegido = emp[i];

                }
            }
            if(empElegido.legajo == -1)
            {
                printf("\nOpcion invalida no existe");
            }

    }while(empElegido.legajo == -1);

    return empElegido;
}


int borrarEmpleado(eEmpleado emp[], int tam, eSector sec[], int tamSec)
{
    int legajo;
    int idBuscar;
    int i;
    char respuesta;
    int retorno = -1;

    printf("---------------------BAJA EMPLEADOS---------------------\n");

    for(i=0;i<tam;i++)
    {
        mostrarUnEmpleado(emp[i],sec,tamSec);
    }
     legajo = getValidInt("\nIngrese el legajo del empleado a eliminar: ",1,tam);

    idBuscar = buscarIdEmpleado(emp,tam,legajo);

    if(idBuscar != -1 && emp[i].isEmpty != LIBRE)
    {
       respuesta = getChar("\nSeguro que desea eliminar el registro?(s/n)");

       if(respuesta == 's' || respuesta == 'S')
       {
           emp[idBuscar].isEmpty = LIBRE;
           printf("\nEmpleado eliminado");
           retorno = 0;
       }
       else
       {
        printf("No se elimino el registro.");
       }
    }
    else
    {
        printf("No se encontro el registro!");
    }
    return retorno;
}

int modifyEmpleado(eEmpleado emp[], int tam, eSector sec[], int tamSec)
{
    int legajo;
    int idBuscar;
    int i;
    char respuesta;
    int retorno = -1;
    int opcSubmenu;
    char auxApellido[51];
    char auxNombre[51];
    char auxSexo = 'x';
    eSector auxSector;
    float auxSalario;
    eFecha auxFecha;

    printf("\n-------------------MODIFICACION DE DATOS DE EMPLEADO------------------");

    for(i=0;i<tam;i++)
    {
        mostrarUnEmpleado(emp[i],sec,tamSec);
    }

    legajo = getValidInt("\nIngrese el legajo a modificar",1,tam);
    idBuscar = buscarIdEmpleado(emp,tam,legajo);

    if(idBuscar != -1 && emp[idBuscar].isEmpty != LIBRE)
    {

        respuesta = getChar("\nEsta seguro que desea modificar el registro?(s/n)");

        if(respuesta == 's' || respuesta == 'S')
        {
            do{
                opcSubmenu = getValidInt("\nDigite una opcion: \n1)Modificar apellido\n2)Modificar nombre\n3)Modificar Sexo\n4)Modificar Salario\n5)Modificar Fecha Ingreso\n6)Modificar Sector\n7)Volver",1,7);

                switch(opcSubmenu)
                {
                case 1:
                    myFgets(auxApellido,51,"Ingrese apellido:");
                    strcpy(emp[idBuscar].apellido,auxApellido);
                    break;
                case 2:
                    myFgets(auxNombre,51,"Ingrese nombre:");
                    strcpy(emp[idBuscar].nombre,auxNombre);
                    break;
                case 3:
                    getSex(auxSexo);
                    emp[idBuscar].sexo = auxSexo;
                    break;
                case 4:
                    auxSalario= getValidFloat("Ingrese salario: ","Error",1,999999999);
                    emp[idBuscar].salario = auxSalario;
                    break;
                case 5:
                    auxFecha = getFecha();
                    emp[idBuscar].ingreso =  auxFecha;
                    break;
                case 6:
                   auxSector = getSector(sec,tamSec);
                    emp[idBuscar].idSector = auxSector.id;
                    break;
                case 7:
                    printf("\nVolviendo al menu de empleados....\n");
                    break;
                default:
                    printf("\nOpcion invalida");
                }
            }while(opcSubmenu != 7);

            retorno = 0;
        }
        else
        {
            printf("\nSe cancelo la modificacion...");
        }
    }
    else
    {
        printf("\nEl legajo no existe...");
    }

    return retorno;
}

int orderEmpleadosDescendente(eEmpleado emp[], int tam, eSector sec[], int tamSec)
{
    int i;
    int j;
    eEmpleado aux;

    printf("\nOrdenando en orden ascendente.....\n");

    for(i=0;i<tam-1;i++)
    {
        for(j = i+1; j<tam;j++)
        {
            if(strcmp(emp[j].apellido,emp[i].apellido)<0)
            {
                aux = emp[i];
                emp[i] = emp[j];
                emp[j] = aux;
            }

            if(strcmp(emp[j].apellido,emp[i].apellido)==0&& strcmp(emp[j].nombre,emp[i].nombre)<0)
            {
                aux = emp[i];
                emp[i] = emp[j];
                emp[j] = aux;
            }
        }
    }

    listarEmpleados(emp,tam,sec,tamSec);
    return 0;
}


//void harcodeEmpleado(eEmpleado vec[], int tam)
//{
//    eEmpleado hardcode[]=
//    {
//        {80, "Juan", 'm', 30000,1,{12,3,2000}, 4},
//        {81, "Ana", 'f', 28000,1, {2,7,2010},1},
//        {82, "Jorge", 'm', 28000,1,{14,5,2013},1},
//        {83, "Alberto", 'm', 35000,1, {2,9,2010},2},
//        {84, "Sonia", 'f', 39000,1, {12,3,2012},2},
//        {85, "Miguel", 'm', 29700,1, {28,7,2009},2},
//        {86, "Adrian", 'm', 43200,1, {11,1,2016}, 3},
//        {34, "Carolina", 'f', 32300,1, {19,10,2004},3},
//        {76, "Diego", 'm', 35000,0, {23,6,2010}, 2},
//        {35, "Mirta", 'f', 30000,1, {2,7,2009},1},
//        {45, "Ximena", 'f', 35000,1, {2,9,1995},2},
//        {89, "Ailen", 'f', 39000,1, {12,3,1996},2},
//        {69, "Silvia", 'f', 43200,1, {11,1,2017}, 3},
//        {32, "Brisa", 'f', 32300,0, {19,10,2003},3},
//        {72, "Juan Carlos", 'm', 35000,0, {23,6,2011}, 2}
//    };
//
//
//    for(int i=0; i<tam; i++)
//    {
//        vec[i]=hardcode[i];
//    }
//}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNCIONES DE SECTORES----------------------------------------------------------------------------------------------------------
void listarSectores(eSector s[], int tam)
{

    printf(" ID   Descripcion\n");
    printf("-------------------\n");

    for(int i=0; i<tam; i++)
    {
        if(s[i].id>0)
        {
            printf(" %d   %s\n",s[i].id,s[i].descripcion);
        }

    }
    printf("---------------------\n");
}


void mostrarSectores(eSector s[], int tam, int idSector, char cadena[])
{
    int i;

    for(i=0; i<tam; i++)
    {
        if(s[i].id == idSector)
        {
            strcpy(cadena,s[i].descripcion);
        }
    }
}


eSector getSector(eSector s[], int tam)
{
    int i;
    int idSector;
    eSector sElegido;//guarda la estructura elegida por el usuario
    sElegido.id = -1;

    do
    {
      listarSectores(s,tam);

      idSector = getValidInt("\nElija un sector: ",1,tam);

      for(i=0;i<tam;i++)
      {
          if(s[i].id == idSector)
          {
              sElegido = s[i];//retorno toda la estructura elegida
          }
      }

      if(sElegido.id == -1)
      {
          printf("El sector elegido no existe...");
      }

    }while(sElegido.id == -1);

    return sElegido;

}

//FUNCIONES DE FECHA-------------------------------------------------------------------------------------------------------------
eFecha getFecha(void)
{
   eFecha putFecha;
   putFecha.dia= getValidInt("Dia", 1, 31);
   putFecha.mes= getValidInt("Mes", 1, 12);
   putFecha.anio= getValidInt("Anio", 1900, 2019);

   return putFecha;
}

//FUNCIONES DE MENU
void listarMenues(eMenues m[], int tam)
{
    int i;

    printf(" ID   Descripcion    Importe\n");
    printf("-----------------------------\n");
    printf("\n\n");

    for(i=0; i<tam; i++)
    {
        if(m[i].id !=0)
        {
            printf(" %d   %s    $%f\n",m[i].id,m[i].descripcion,m[i].importe);
    }
        }

    printf("-----------------------------\n");
}

void mostrarMenues(eMenues m[], int tam, int idMenu, char cadena[])
{
    int i;

    for(i=0; i<tam; i++)
    {
        if(m[i].id == idMenu && m[i].id>0)
        {
            strcpy(cadena,m[i].descripcion);
        }
    }
}

eMenues getMenus(eMenues m[], int tam)
{
    int i;
    int idMenu;
    eMenues mElegido;//guarda la estructura elegida por el usuario
    mElegido.id = -1;

do
    {
      listarMenues(m,tam);

      idMenu = getValidInt("\nElija un menu: ",1,tam);

      for(i=0;i<tam;i++)
      {
          if(m[i].id == idMenu)
          {
              mElegido = m[i];//retorno toda la estructura elegida
          }
      }

      if(mElegido.id == -1)
      {
          printf("El menu elegido no existe...");
      }

    }while(mElegido.id == -1);

    return mElegido;





}

int totalYPromediosImportesMenu(eMenues men[], int tam)
{
    int total =0;
    int cantMenus = 0;
    float promImportes;
    int cantMayorp=0;
    int i;

    for(i=0;i<tam;i++)
    {
        if(men[i].id>0&&men[i].importe>0)
        {
            total = total + men[i].importe;
            cantMenus++;
        }
    }

    promImportes = total/cantMenus;

    for(i=0;i<tam;i++)
    {
        if(men[i].id>0&&men[i].importe>0&&men[i].importe>promImportes)
        {
            cantMayorp++;
        }
    }

    printf("\n--------------------------------------------------------------------------------");
    printf("\n   TOTAL IMPORTES    |     PROMEDIO IMPORTES    | MENUS QUE SUPERAN EL PROMEDIO |");
    printf("\n--------------------------------------------------------------------------------");
    printf("\n%17d %20f %20d",total,promImportes,cantMenus);

    return 0;
}

//FUNCIONES DE ALMUERZOS---------------------------------------------------------------------------------------------------------
//generar id automaticamente
static int getCodigoAlm()
{
    static int cod = 0;
    cod++;
    return cod;
}

//FUNCION INICIALIZAR ARRAY EN LIBRE
int initAlmuerzos(eAlmuerzo alm[], int tam)
{
    int i;
    int retorno = -1;

    for(i=0; i<tam; i++)
    {
        alm[i].isEmpty= LIBRE; //LIBRE DEFINIDO COMO ENTERO 1 OCUPADO DEFINIDO COMO ENTERO 0
        retorno = 0;
    }
    return retorno;
}

//FUNCION BUSCAR LUGAR LIBRE PARA NUEVO ALTA

int buscarLugarAlmuerzo(eAlmuerzo alm[], int tam)
{
    int i;
    int retorno = -1;

    for(i=0; i<tam; i++)
    {
        if(alm[i].isEmpty == LIBRE)
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

//FUNCION BUSCAR SI EXISTE EL ELEMENTO SEGUN EL ID
int buscarIdAlmuerzo(eAlmuerzo alm[], int tam, int id)
{
    int i;
    int retorno = -1;

    for(i=0; i<tam; i++)
    {
        if(alm[i].isEmpty == OCUPADO && alm[i].id == id)
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

int addAlmuerzo(eAlmuerzo alm[], int tam, eEmpleado emp[], int tamE, eSector sec[], int tamSec, eMenues men[], int tamM)
{
    int i;
    //int id;
    //int idMenu;
    //eFecha auxfecha;
    eEmpleado auxEmpleado;
    eMenues auxMenu;
    int retorno = -1;

    printf("---------------ALTA ALMUERZOS---------------");

    i= buscarLugarAlmuerzo(alm,tam);

    if(i==-1)
    {
        printf("No hay lugar....\n");
    }
    else
    {
        alm[i].id = getCodigoAlm();
        auxEmpleado = getEmpleado(emp,tamE,sec,tamSec);
        alm[i].idEmpleado = auxEmpleado.legajo;
        auxMenu = getMenus(men,tamM);
        alm[i].idMenu = auxMenu.id;
        alm[i].fecha = getFecha();
        alm[i].isEmpty = OCUPADO;

        printf("\nSe completo el regstro de almuerzo...");
        retorno = 0;

    }

    return retorno;
}

void mostrarUnAlmuerzo(eAlmuerzo alm, eEmpleado emp[], int tamE,eMenues menu[], int tamM)
{
    char apellidoAux[51];
    char nombreAux[51];
    char menuDesc[51];
    float auxImporte;
    //int flag =0;
    int i,j;

    for(i=0;i<tamE;i++)
    {
        if(emp[i].legajo == alm.idEmpleado && emp[i].isEmpty == OCUPADO)
        {
            strcpy(apellidoAux,emp[i].apellido);
            strcpy(nombreAux,emp[i].nombre);
            break;
        }
    }

    for(j=0;j<tamM;j++)
    {
        if(menu[j].id == alm.idMenu)
        {
            strcpy(menuDesc,menu[j].descripcion);
            auxImporte = menu[j].importe;
            break;
        }
    }

    printf("%d   %d       %s       %s         %s       $%f     %d/%d/%d",alm.id,alm.idEmpleado,apellidoAux,nombreAux,menuDesc, auxImporte,alm.fecha.dia,alm.fecha.mes,alm.fecha.anio);

}

void listarAlmuerzos(eAlmuerzo alm[], int tam, eEmpleado emp[], int tamE,eMenues men[], int tamM)
{
    int i;
    int flag=0;

    printf("------------------LISTADO DE ALMUERZOS REGISTRADOS------------------\n");
    printf("--------------------------------------------------------------------\n");
    printf("ID LEGAJO  APELLIDO  NOMBRE    MENU    IMPORTE  FECHA\n");

    for(i=0;i<tam;i++)
    {
        if(alm[i].isEmpty == OCUPADO)
        {
            mostrarUnAlmuerzo(alm[i],emp,tamE,men,tamM);
            flag=1;
        }
    }

    if(flag==0)
    {
        printf("\nNo hay almuerzos registrados...");
    }

}




//FUNCIONES DE INFORMES---------------------------------------------------------------------------------------------------------


int submenuInformes(eEmpleado emp[], int tam, eAlmuerzo alm[], int tamA, eSector sec[], int tamSec, eMenues men[], int tamM)
{
    char resp = 'x';
    int opSub;

    do{
        system("cls");
        printf("----------------------SUBMENU DE INFORMES-----------------------\n");
        printf("Digite una opcion: \n");
        printf("\n1)Total, promedio y cantidad de menues que superan el promedio de importes.");
        printf("\n2)Total y promedio de los importes, y cuantos menues NO superan ese promedio.");
        printf("\n3)La cantidad de menues que fueron consumidos por al menos 5 (cinco) empleados.");
        printf("\n4)La cantidad de menues que fueron consumidos por menos de 5 (cinco) empleados.");
        printf("\n5)Todos los menues cuyo importe sea menor o igual a $125.");
        printf("\n6)Todos los menues cuyo importe sea mayor a $125.");
        printf("\n7)Todos los empleados que consumieron un menu determinado.");
        printf("\n8)Todos los menues consumidos por un empleado determinado.");
        printf("\n9)Todos los almuerzos consumidos en una fecha determinada.");
        printf("\n10)Todos los empleados que consumieron un almuerzo en una fecha determinada.");

       opSub = getValidInt("Su opcion: ",1,10);

       switch(opSub)
       {
       case 1:
           totalYPromediosImportesMenu(men,tamM);
        break;
       case 2:
        break;
       case 3:
        break;
       case 4:
        break;
       case 5:
        break;
       case 6:
        break;
       case 7:
        break;
       case 8:
        break;
       case 9:
        break;
       case 10:
        break;
       default:
        printf("\nOpcion invalida....");
       }

        resp = getChar("\nDesea continuar?(s/n)");
    }while(resp == 's' && resp == 'S');

 return 0;

}


//void informeEmpPorSector(eEmpleado empleados[],int tam, eSector sector[],int tamSec)
//{
//    for(int i=0;i<tamSec;i++)
//    {
//        printf("\n\n*** Sector %s ***\n\n",sector[i].descripcion);
//        printf("%5s %12s %12s %8s %10s %12s %10s\n", "Legajo", "Nombre", "Apellido", "Sexo", "Sueldo", "Fecha Ing", "Sector");
//        printf("%5s %12s %12s %8s %10s %12s %10s\n", "------", "------", "--------", "----", "------", "---------", "------");
//
//        for(int j=0;j<tam;j++)
//        {
//            if(empleados[j].idSector==sector[i].id && empleados[j].estado==OCUPADO)
//            {
//                mostrarEmpleado(empleados[j],sector,TAMSEC);
//            }
//        }
//    }
//}
//
//void altaSector(eSector sector[],int tamSec)
//{
//    int indiceSectorVacio;
//
//    system("cls");
//    printf("** Sectores dados de alta **\n");
//    mostrarSectores(sector,TAMSEC);
//
//    indiceSectorVacio=buscarSectorVacio(sector,tamSec);
//
//    for(int i=0;i<tamSec;i++)
//    {
//        if(indiceSectorVacio>-1)
//        {
//            sector[indiceSectorVacio].id=indiceSectorVacio+1;
//
//            printf("Ingrese el nombre del sector que desea dar de ALTA: ");
//            fflush(stdin);
//            scanf("%s",sector[indiceSectorVacio].descripcion);
//            break;
//        }
//        else
//        {
//            printf("No hay espacio para agregar mas sectores..!!");
//            break;
//        }
//    }
//}
//
//int buscarSectorVacio(eSector sector[],int tamSec)
//{
//    int indiceVacio = -1;
//
//    for(int i=0;i<tamSec;i++)
//    {
//        if(sector[i].id==0)
//        {
//            indiceVacio=i;
//            break;
//        }
//    }
//    return indiceVacio;
//}
//
//void informeCantEmpPorSector(eEmpleado empleados[],int tam, eSector sector[],int tamSec)
//{
//    int contador;
//
//    system("cls");
//
//    printf("*** Cantidad de empleados ***\n\n");
//
//    for(int i=0;i<tamSec;i++)
//    {
//        contador=0;
//
//        for(int j=0;j<tam;j++)
//        {
//            if(empleados[j].idSector==sector[i].id && empleados[j].estado==OCUPADO)
//            {
//                contador++;
//            }
//        }
//        printf("Sector %s: %d \n",sector[i].descripcion,contador);
//    }
//}
//
//void informeMaxSueldoEmpPorSector(eEmpleado empleados[],int tam, eSector sector[],int tamSec)
//{
//    int flagAux=0;
//    int indiceMax;
//    float max;
//
//    system("cls");
//
//    printf("*** Empleados por sector con mayor sueldo ***\n\n");
//
//    for(int i=0;i<tamSec;i++)
//    {
//        printf("Sector %s: \n",sector[i].descripcion);
//        max=0;
//        indiceMax=0;
//
//        for(int j=0;j<tam;j++)
//        {
//            if(empleados[j].idSector==sector[i].id && empleados[j].estado==OCUPADO && (flagAux==0 || empleados[j].sueldo>max))
//            {
//                max=empleados[j].sueldo;
//                indiceMax=j;
//                flagAux=1;
//            }
//        }
//        mostrarEmpleado(empleados[indiceMax],sector,TAMSEC);
//    }
//}
//
//void informePromedioSueldosPorSector(eEmpleado empleados[],int tam, eSector sector[],int tamSec)
//{
//    int contador;
//    float acumulador;
//    float promedio=0;
//
//    for(int i=0;i<tamSec;i++)
//    {
//        contador=0;
//        acumulador=0;
//        printf("\n\n*** Sector %s ***\n\n",sector[i].descripcion);
//
//        for(int j=0;j<tam;j++)
//        {
//            if(empleados[j].idSector==sector[i].id && empleados[j].estado==OCUPADO)
//            {
//                contador++;
//                acumulador+=empleados[j].sueldo;
//            }
//        }
//        promedio=acumulador/contador;
//        printf("Promedio sueldos: %.2f\n",promedio);
//    }
//}
//
//void hardCodearComidas(eComida comidas[],int tamCom)
//{
//    eComida vecAux[]={
//                    {1,"Milanesa"},
//                    {2,"Fideos"},
//                    {3,"Sopa"},
//                    {4,"Guiso"},
//                    {5,"Lasagna"},
//                    };
//
//    for(int i=0;i<tamCom;i++)
//    {
//        comidas[i]=vecAux[i];
//    }
//}
//
//void hardCodearAlmuerzos(eAlmuerzo almuerzos[],int tamAlm)
//{
//    eAlmuerzo vecAux[]={
//                    {100,1001,1,{25,4,2019}},
//                    {101,1234,2,{25,4,2019}},
//                    {102,1245,3,{25,4,2019}},
//                    {103,1543,4,{25,4,2019}},
//                    {104,1800,1,{25,4,2019}},
//                    {105,1224,2,{25,4,2019}},
//                    {106,1654,3,{25,4,2019}},
//                    {107,1684,4,{25,4,2019}},
//                    {108,1859,1,{25,4,2019}},
//                    {109,1001,2,{26,4,2019}},
//                    {110,1234,1,{26,4,2019}},
//                    {111,1245,4,{26,4,2019}},
//                    {112,1224,3,{26,4,2019}},
//                    {113,1654,2,{26,4,2019}},
//                    {114,1684,3,{26,4,2019}},
//                    {115,1859,4,{26,4,2019}},
//                    };
//
//    for(int i=0;i<tamAlm;i++)
//    {
//        almuerzos[i]=vecAux[i];
//    }
//}
//
//void mostrarAlmuerzo(eAlmuerzo almuerzo,eEmpleado empleados[],int tam,eComida comidas[],int tamCom)
//{
//    char nombreEmpleado[51];
//    char apellidoEmpleado[51];
//    char nombreComida[21];
//    int indiceCoincideIDEmp;
//    int indiceCoincideIDCom;
//
//    strcpy(nombreEmpleado,"");
//    strcpy(apellidoEmpleado,"");
//    strcpy(nombreComida,"");
//
//    indiceCoincideIDEmp=obtenerAlmuerzoEmpleado(almuerzo,empleados,TAMEMP,nombreEmpleado,apellidoEmpleado);
//    indiceCoincideIDCom=obtenerAlmuerzoComida(almuerzo,comidas,TAMCOM,nombreComida);
//
//    if(indiceCoincideIDEmp && indiceCoincideIDCom)
//    {
//        printf("%d %14s %15s %10s %7.02d/%02d/%4d\n",almuerzo.id,nombreEmpleado,apellidoEmpleado,nombreComida,almuerzo.fecha.dia,almuerzo.fecha.mes,almuerzo.fecha.anno);
//    }
//    else
//    {
//        printf("Empleado sin almuerzo..!!");
//    }
//}
//
//void mostrarAlmuerzos(eAlmuerzo almuerzos[], int tamAlm , eEmpleado empleados[], int tam, eComida comidas[], int tamCom)
//{
//    system("cls");
//
//    printf("*** Almuerzos ***\n\n");
//    printf("%s %15s %15s %10s %12s \n","ID","NOMBRE","APELLIDO","COMIDA","FECHA");
//    printf("%s %15s %15s %10s %12s \n","--","------","--------","------","-----");
//
//    for(int i=0;i<tamAlm;i++)
//    {
//        mostrarAlmuerzo(almuerzos[i],empleados,TAMEMP,comidas,TAMCOM);
//    }
//}
//
//void mostrarComidas(eComida comidas[], int tamCom)
//{
//    system("cls");
//    printf("*** COMIDAS ***\n\n");
//
//    for(int i=0;i<tamCom;i++)
//    {
//        if(comidas[i].id>0)
//        {
//            printf("%d %4s\n",comidas[i].id, comidas[i].descripcion);
//        }
//    }
//}
//
//int obtenerAlmuerzoEmpleado(eAlmuerzo almuerzo, eEmpleado empleados[], int tam, char nombreEmp[], char apellidoEmp[])
//{
//    int esta=-1;
//
//    for(int j=0;j<tam;j++)
//    {
//        if(almuerzo.legajoEmp==empleados[j].legajo && empleados[j].estado==OCUPADO)
//        {
//            strcpy(nombreEmp,empleados[j].nombre);
//            strcpy(apellidoEmp,empleados[j].apellido);
//            esta=1;
//        }
//    }
//    return esta;
//}
//
//int obtenerAlmuerzoComida(eAlmuerzo almuerzo, eComida comidas[], int tamCom, char nombreCom[])
//{
//    int esta=-1;
//
//    for(int j=0;j<tamCom;j++)
//    {
//        if(almuerzo.idComida==comidas[j].id)
//        {
//            strcpy(nombreCom,comidas[j].descripcion);
//            esta=1;
//        }
//    }
//    return esta;
//}
//
//void informeAlmuerzosPorPersona(eAlmuerzo almuerzos[], int tamAlm , eEmpleado empleados[], int tam, eComida comidas[], int tamCom)
//{
//    system("cls");
//    printf("*** Almuerzos por persona***\n");
//
//    for(int i=0;i<tam;i++)
//    {
//        if(empleados[i].estado==OCUPADO)
//        {
//            printf("\nNombre  Apellido\n");
//            printf("%s %s\n",empleados[i].nombre,empleados[i].apellido);
//
//            for(int j=0;j<tamAlm;j++)
//            {
//                for(int k=0;k<tamCom;k++)
//                {
//                    if(almuerzos[j].legajoEmp==empleados[i].legajo && almuerzos[j].idComida==comidas[k].id)
//                    {
//                        //Revisar bien que pasa aca cuando imprime todo
//                        printf("Comida: %s\n",comidas[k].descripcion);
//                    }
//                }
//            }
//        }
//    }
//}
//
//void informeComidaPorPersona(eAlmuerzo almuerzos[], int tamAlm , eEmpleado empleados[], int tam, eComida comidas[], int tamCom)
//{
//    int indiceEmpleado;
//
//    for(int i=0;i<tamCom;i++)
//    {
//        printf("\nComida: %s\n\n",comidas[i].descripcion);
//        for(int j=0;j<tamAlm;j++)
//        {
//            if(almuerzos[j].idComida==comidas[i].id)
//            {
//                indiceEmpleado=obtenerLegajoEmpAlmuerzo(almuerzos[j],empleados,TAMEMP);
//                printf("%s %s\n",empleados[indiceEmpleado].nombre,empleados[indiceEmpleado].apellido);
//            }
//        }
//    }
//}
//
//int obtenerLegajoEmpAlmuerzo(eAlmuerzo almuerzo,eEmpleado empleados[],int tam)
//{
//    int indice;
//
//    for(int i=0;i<tam;i++)
//    {
//        if(almuerzo.legajoEmp==empleados[i].legajo)
//        {
//            indice=i;
//            break;
//        }
//    }
//
//    return indice;
//}

//
//void almuerzosXemp(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    int legajo;
//    int flag = 0;
//
//    system("cls");
//
//    mostrarEmpleados(x,tam,sec,tamSec);
//
//    printf("Ingrese el legajo  a buscar: ");
//    scanf("%d",&legajo);
//
//    printf("\n\n");
//
//    printf("ALMUERZOS DEL EMPLEADO %d\n",legajo);
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        if(alm[i].idEmpleado == legajo && alm[i].ocupado == OCUPADO)
//        {
//            for(int k=0; k<tamCom; k++)
//            {
//                if(alm[i].idComida == com[k].id)
//                {
//                    printf("%d %10s\n",alm[i].id,com[k].descripcion);
//                    flag = 1;
//
//
//
//
//                }
//            }
//        }
//    }
//
//
//
//    if(flag == 0)
//    {
//        printf("Este empleado no tiene ningun almuerzo registrado\n");
//    }
//
//}
//
//
//
//void almuerzosXfecha(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//
//    int flag = 0;
//    eFecha fecha;
//
//    system("cls");
//
//    printf("Ingrese fecha de ingreso dd/mm/aaaa: ");
//    scanf("%d %d %d", &fecha.dia, &fecha.mes, &fecha.anio);
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        for(int j=0; j<tam; j++)
//        {
//            if(compararFechas(alm[i].fecha,fecha) && alm[i].idEmpleado == x[j].legajo && x[j].ocupado == OCUPADO && alm[i].ocupado == OCUPADO)
//            {
//
//
//                flag = 1;
//                mostrarAlmuerzo(alm[i],x,tam,com,tamCom);
//                break;
//
//
//            }
//        }
//    }
//
//    if(flag == 0)
//    {
//        printf("Ningun empleado almorzo este dia\n");
//    }
//
//
//}
//
//
//
//void almuerzosXdescrip(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    char descrip[20];
//    int flag = 0;
//
//    system("cls");
//
//    listarComidas(com,tamCom);
//
//    printf("Ingrese la comida a buscar: ");
//    fflush(stdin);
//    gets(descrip);
//
//    printf("\n\n");
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        for(int j=0; j<tam; j++)
//        {
//            for(int k=0; k<tamCom; k++)
//            {
//                if(x[j].ocupado == OCUPADO && x[j].legajo == alm[i].idEmpleado && alm[i].ocupado == OCUPADO && stricmp(com[k].descripcion,descrip)==0 && com[k].id == alm[i].idComida)
//                {
//                    flag = 1;
//                    mostrarEmpleado(x[j],sec,tamSec);
//                }
//            }
//        }
//    }
//
//
//    if(flag == 0)
//    {
//        printf("Nadie almorzo esta comida\n");
//    }
//
//}
//
//
//
//void almuerzosXmismaFecha(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm)
//{
//    int flag = 0;
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        //alm[i].fecha.dia == alm[i].fecha.dia && alm[i].fecha.mes == alm[i].fecha.mes && alm[i].fecha.anio == alm[i].fecha.anio
//        if(compararFechas(alm[i].fecha, alm[i].fecha))
//        {
//            for(int j=0; j<tam; j++)
//            {
//                if(x[j].ocupado == OCUPADO && x[j].legajo == alm[i].idEmpleado && alm[i].ocupado == OCUPADO)
//                {
//                    mostrarAlmuerzo(alm[j],x,tam,com,tamCom);
//                    flag = 1;
//                }
//            }
//        }
//    }
//
//
//    if(flag == 0)
//    {
//        printf("Nadie almorzo la misma fecha\n");
//    }
//
//}
//
//
//void almuerzosXsector(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    int sector;
//    int flag = 0;
//
//    listarSectores(sec,tamSec);
//
//    printf("Ingrese ID Sector:");
//    scanf("%d",&sector);
//
//
//    for(int i=0; i<tam; i++)
//    {
//        if(x[i].sector == sector && x[i].ocupado == OCUPADO)
//        {
//            for(int j=0; j<tamAlm; j++)
//            {
//                if(alm[j].idEmpleado == x[i].legajo && alm[i].ocupado == OCUPADO)
//                {
//                    for(int k=0; k<tamCom; k++)
//                    {
//                        if(alm[j].idComida == com[k].id)
//                        {
//                            printf("%s %s %0d/%0d/%d\n",x[i].nombre,com[k].descripcion,alm[j].fecha);
//                            flag = 1;
//                            break;
//                        }
//                    }
//
//
//
//
//                }
//            }
//        }
//    }
//
//
//
//    if(flag == 0)
//    {
//        printf("Nadie en este sector almorzo\n");
//    }
//}
//
//
//
//void almuerzosMasComido2(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    int cont[tamCom];
//    int flag = 0;
//    int mayor;
//
//    for(int i=0; i<tamCom; i++)
//    {
//        cont[i] = 0;
//
//        for(int j=0; j<tamAlm; j++)
//        {
//            if(com[i].id == alm[j].idComida && alm[i].ocupado == OCUPADO)
//            {
//                for(int k=0; k<tam; k++)
//                {
//                    if(x[k].ocupado == OCUPADO && x[k].legajo == alm[j].idEmpleado)
//                    {
//                        cont[i]++;
//
//
//
//
//                    }
//                }
//            }
//        }
//    }
//
//
//    for(int i=0; i<tamCom; i++)
//    {
//        if(flag == 0 || cont[i]>mayor)
//        {
//            mayor =  cont[i];
//
//            flag = 1;
//        }
//    }
//
//
//    printf("Comida mas pedida por los empleados:\n");
//
//
//    for(int i=0; i<tamCom; i++)
//    {
//        if(cont[i] == mayor)
//        {
//            printf("%s\n",com[i].descripcion);
//        }
//    }
//}
//
//
//
//void almuerzosEmpMasPerdedor(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    int flag=0;
//    int menor=0;
//
//
//    for(int i=0; i<tam; i++)
//    {
//        for(int j=0; j<tamAlm; j++)
//        {
//
//
//            if(x[i].legajo == alm[j].idEmpleado && x[i].ocupado == OCUPADO && alm[j].ocupado == OCUPADO && (x[i].sueldo < menor || flag == 0))
//            {
//                for(int k=0; k<tamCom; k++)
//                {
//                    if(alm[j].idComida == com[k].id)
//                    {
//                        menor = x[i].sueldo;
//                        flag = 1;
//                    }
//                }
//            }
//        }
//    }
//
//
//
//    for(int i=0; i<tam; i++)
//    {
//        for(int j=0; j<tamAlm; j++)
//        {
//            if(x[i].sueldo == menor && x[i].ocupado == OCUPADO && x[i].legajo == alm[j].idEmpleado && alm[j].ocupado == OCUPADO)
//            {
//                mostrarAlmuerzo(alm[j],x,tam,com,tamCom);
//            }
//        }
//    }
//}
//
//
//
//void empleadosQueNoAlmorzaron(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    int flag;
//
//    for(int i=0; i<tam; i++)
//    {
//        flag = 0;
//
//        for(int j=0; j<tamAlm; j++)
//        {
//            if(x[i].legajo == alm[j].idEmpleado && x[i].ocupado == 1 && alm[j].ocupado == OCUPADO)
//            {
//                for(int k=0; k<tamCom; k++)
//                {
//                    if(com[k].id == alm[j].idComida)
//                    {
//                        flag = 1;
//                        break;
//                    }
//                }
//            }
//        }
//
//
//        if(flag == 0 && x[i].ocupado == OCUPADO)
//        {
//            printf("Empleados que no almorzaron\n");
//
//            mostrarEmpleado(x[i],sec,tamSec);
//
//
//        }
//
//    }
//
//
//    if(flag == 1)
//    {
//        printf("Todos los empleados almorzaron\n");
//    }
//
//}
//
//
//
//void AlmuerzosMasComidosXmujeres(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    int mayor;
//    int flag=0;
//    int mujeres[tamCom];
//
//
//    for(int i=0; i<tamCom; i++)
//    {
//        mujeres[i] = 0;
//
//
//        for(int j=0; j<tamAlm; j++)
//        {
//            if(com[i].id == alm[j].idComida && alm[j].ocupado == OCUPADO)
//            {
//                for(int k=0; k<tam; k++)
//                {
//                    if(x[k].ocupado == OCUPADO && x[k].sexo == 'f' && x[k].legajo == alm[j].idEmpleado)
//                    {
//                        mujeres[i]++;
//                    }
//                }
//
//            }
//        }
//    }
//
//
//    for(int i=0; i<tamCom; i++)
//    {
//        if(mujeres[i] > mayor || flag == 0)
//        {
//            mayor = mujeres[i];
//
//            flag = 1;
//        }
//    }
//
//
//    printf("Almuerzos + comidos por Mujeres:\n");
//
//
//    for(int i=0; i<tam; i++)
//    {
//        if(mujeres[i] == mayor)
//        {
//            printf("%s\n",com[i].descripcion);
//        }
//    }
//}
//
//
//
//void AlmuerzosXhombres(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    int flag = 0;
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        for(int j=0; j<tam; j++)
//        {
//            if(x[j].legajo == alm[i].idEmpleado && x[j].ocupado == OCUPADO && x[j].sexo == 'm' && alm[i].ocupado == OCUPADO)
//            {
//                for(int k=0; k<tamCom; k++)
//                {
//                    if(com[k].id == alm[i].idComida)
//                    {
//                        mostrarAlmuerzo(alm[i],x,tam,com,tamCom);
//                        flag = 1;
//                    }
//                }
//            }
//        }
//    }
//
//    if(flag == 0)
//    {
//        printf("No hay almuerzos registrados\n");
//    }
//}
//
//
//
//void importesEmpleado(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    float total = 0;
//    int flag = 0;
//    int legajo;
//
//
//    mostrarEmpleados(x,tam,sec,tamSec);
//
//
//    printf("Ingrese el legajo a buscar el importe: ");
//    scanf("%d",&legajo);
//
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        if(alm[i].idEmpleado == legajo && alm[i].ocupado == OCUPADO)
//        {
//            for(int j=0; j<tamCom; j++)
//            {
//                if(alm[i].idComida == com[j].id)
//                {
//                    total+=com[j].precio;
//                    flag = 1;
//                    break;
//                }
//            }
//        }
//    }
//
//
//    if(flag == 0)
//    {
//        printf("Este empleado no ha almorzado nada\n");
//    }
//    else
//    {
//        printf("Importe total: %.2f\n",total);
//    }
//}
//
//
//
//void totalXfecha(eEmpleado x[], int tam, eComida com[], int tamCom, eAlmuerzo alm[], int tamAlm, eSector sec[], int tamSec)
//{
//    float total = 0;
//    int flag = 0;
//
//    eFecha fecha;
//
//    printf("Ingrese fecha aa/mm/aaaa: ");
//    scanf("%d %d %d",&fecha.dia,&fecha.mes,&fecha.anio);
//
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        if(compararFechas(alm[i].fecha,fecha))
//        {
//            for(int j=0; j<tam; j++)
//            {
//                if(x[j].ocupado == OCUPADO && x[j].legajo == alm[i].idEmpleado && alm[i].ocupado == OCUPADO)
//                {
//                    for(int k=0; k<tamCom; k++)
//                    {
//                        if(com[k].id == alm[i].idComida)
//                        {
//                            total+=com[k].precio;
//                            flag = 1;
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//
//    if(flag == 0)
//    {
//        printf("No hay importes acumulados en esta fecha\n");
//    }
//    else
//    {
//        printf("Total recaudado en la fecha %0d/%0d/%d: %.2f\n",fecha.dia,fecha.mes,fecha.anio,total);
//    }
//}
//
//void contadorComida(eEmpleado x[], int tam, eSector sec[], int tamSec, eAlmuerzo alm[], int tamAlm, eComida com[], int tamCom)
//{
//    int cont[tamCom];
//
//
//    for(int i=0; i<tamCom; i++)
//    {
//        cont[i] = 0;
//
//
//        for(int j=0; j<tamAlm; j++)
//        {
//            if(com[i].id == alm[j].idComida && alm[j].ocupado == 1)
//            {
//                cont[i]++;
//            }
//        }
//
//
//        printf("Comida: %s  Cantidad: %d\n",com[i].descripcion,cont[i]);
//    }
//}
//
//
//
//void almuerzoXcomida(eEmpleado x[], int tam, eSector sec[], int tamSec, eAlmuerzo alm[], int tamAlm, eComida com[], int tamCom)
//{
//    int flag = 0;
//    int id;
//
//
//    listarComidas(com,tamCom);
//    printf("\n\n");
//    printf("Ingrese ID Comida: ");
//    scanf("%d",&id);
//
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        for(int j=0; j<tam; j++)
//        {
//            if(x[j].ocupado == OCUPADO && alm[i].idEmpleado == x[j].legajo && alm[i].ocupado == OCUPADO && alm[i].idComida == id)
//            {
//                flag = 1;
//                mostrarAlmuerzo(alm[i],x,tam,com,tamCom);
//                break;
//            }
//        }
//    }
//
//
//    if(flag == 0)
//    {
//        printf("Nadie almorzo esta comida\n");
//    }
//}
//
//
//
//void almuerzosXmujeres(eEmpleado x[], int tam, eSector sec[], int tamSec, eAlmuerzo alm[], int tamAlm, eComida com[], int tamCom)
//{
//    int id;
//    int flag = 0;
//
//
//    listarComidas(com,tamCom);
//    printf("\n\n");
//    printf("Ingrese ID Comida: ");
//    scanf("%d",&id);
//
//
//    for(int i=0; i<tamAlm; i++)
//    {
//        for(int j=0; j<tam; j++)
//        {
//            if(x[j].ocupado == OCUPADO && x[j].legajo == alm[i].idEmpleado && alm[i].ocupado == OCUPADO && x[j].sexo == 'f' && alm[i].idComida == id)
//            {
//                mostrarAlmuerzo(alm[i],x,tam,com,tamCom);
//                flag = 1;
//            }
//        }
//    }
//
//
//    if(flag == 0)
//    {
//        printf("Nadie almorzo de este sector\n");
//    }
//}
//
//
//
//void almuerzoMasComidoXsector(eEmpleado x[], int tam, eSector sec[], int tamSec, eAlmuerzo alm[], int tamAlm, eComida com[], int tamCom)
//{
//    int sector[tamCom];
//    int idSector;
//    int flag = 0;
//    int mayor;
//
//
//    listarSectores(sec,tamSec);
//    printf("\n\n");
//    printf("Ingrese Sector: ");
//    scanf("%d",&idSector);
//
//
//    for(int i = 0; i<tamCom; i++)
//    {
//        sector[i] = 0;
//
//
//        for(int j=0; j<tamAlm; j++)
//        {
//            if(alm[j].ocupado == OCUPADO && alm[j].idComida == com[i].id)
//            {
//                for(int k=0; k<tam; k++)
//                {
//                    if(x[k].ocupado == OCUPADO && x[k].sector == idSector && x[k].legajo == alm[j].idEmpleado)
//                    {
//                        sector[i]++;
//                    }
//                }
//            }
//        }
//    }
//
//
//    for(int i=0; i<tamCom; i++)
//    {
//        if(sector[i] > mayor || flag == 0)
//        {
//            mayor = sector[i];
//            flag = 1;
//        }
//    }
//
//
//    for(int i=0; i<tamCom; i++)
//    {
//        if(sector[i] == mayor)
//        {
//            printf("%s\n",com[i].descripcion);
//        }
//    }
//}


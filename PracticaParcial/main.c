#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "funciones.h"
#define CANTEMP 5
#define CANTSEC 5
#define CANTMENU 5
#define CANTALM 20

int main()
{
    system("COLOR F5");
    eEmpleado unEmpleado[CANTEMP];
    eMenues menues[CANTMENU] = {{1,"Ensalada",60.50},{2,"Milanesa",150.50},{3,"Hamburguesa",100.00}};
    eSector sectores[CANTSEC] = {{1,"RRHH"},{2,"Laboratorio"},{3,"Gerencia"}};
    initEmpleados(unEmpleado,CANTEMP);
    eAlmuerzo almuerzo[CANTALM];
    initAlmuerzos(almuerzo,CANTALM);
    int flag = 0;
    int flagB = 0;
    int op_menu;
    printf("\t-----------------------------------------ABM EMPLEADOS/ALMUERZOS----------------------------------------");

    do{
            printf("\nDigite una opcion: ");
            printf("\n1)Dar de alta empleado.\n2)Eliminar empleado.\n3)Mostrar todos empleados\n4)Modificar empleado\n5)Ordenar empleados\n6)Añadir almuerzo\n7)Mostrar almuerzos\n8)Informes\n9)Salir.");
            scanf("%d",&op_menu);

            switch(op_menu){
            case 1:
                system("cls");
                addEmpleados(unEmpleado,CANTEMP,sectores,CANTSEC);
                flag = 1;
                break;
            case 2:
                if(flag == 0)
                {
                    printf("\nDebe ingresar un registro primero");
                }
                else
                {
                    borrarEmpleado(unEmpleado,CANTEMP,sectores,CANTSEC);
                }

                break;
            case 3:
                if(flag == 0)
                {
                    printf("\nDebe ingresar un registro primero");
                }
                else
                {
                    listarEmpleados(unEmpleado,CANTEMP,sectores,CANTSEC);
                }

                break;
            case 4:
                if(flag == 0)
                {
                    printf("\nDebe ingresar un registro primero");
                }
                else
                {
                    modifyEmpleado(unEmpleado,CANTEMP,sectores,CANTSEC);
                }

                break;
            case 5:
                if(flag == 0)
                {
                    printf("\nDebe ingresar un registro primero");
                }
                else
                {
                    orderEmpleadosDescendente(unEmpleado,CANTEMP,sectores,CANTSEC);
                }
                break;
            case 6:
                addAlmuerzo(almuerzo,CANTALM,unEmpleado,CANTEMP,sectores,CANTSEC,menues,CANTMENU);
                flagB = 1;
                break;
            case 7:
                if(flagB == 0)
                {
                    printf("\nDebe ingresar un registro primero");
                }
                else
                {
                    listarAlmuerzos(almuerzo,CANTALM,unEmpleado,CANTEMP,menues,CANTMENU);
                }
                break;
            case 8:
                submenuInformes(unEmpleado,CANTEMP,almuerzo,CANTALM,sectores,CANTSEC,menues,CANTMENU);
                break;
            default:
                printf("\nOpcion invalida....");
            }
    }while(op_menu!=9);




    return 0;
}

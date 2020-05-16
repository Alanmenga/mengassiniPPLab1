#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datawarehouse.h"


#define TAM 5
#define TAMTIPOS 4
#define TAMCOLORES 5
#define CANTHARDCODE 3

typedef struct
{
    int dia;
    int mes;
    int anio;
} eFecha;

typedef struct
{
    int id;//Comienza en 1000
    char descripcion[20];

}eTipo;

typedef struct
{
    int id;//Comienza en 10000
    char nombreColor[20];
}eColor;

typedef struct
{
    int id;
    char marca[20];
    int idTipo;//Validar
    int idColor;//Validar
    int cilindrada;
    int isEmpty;
}eMoto;

typedef struct
{
    int id;//Comienza en 20000
    char descripcion[25];
    int precio;

}eServicio;

typedef struct
{
    int id;//Autoincremental
    int idBicicleta;//Debe existir
    int idServicio;//Debe existir
    eFecha fecha;//Validar dia, mes y año
    int isEmpty;
}eTrabajo;


char menu();
void inicializarMotos(eMoto vec[],int tam);

int buscarLibre(eMoto vec[], int tam);
int altaEmpleado(int idx,eMoto motos[], int tamMotos,eTipo tipos[], int tamTipos,eColor colores[],int tamColores);
void listarTipos(eTipo tipos[],int tamTipos);
void listarColores(eColor colores[],int tamColores);
void hardcodearMotos(eMoto motos[],int cant);

int cargarDescripcionTipo(char descripcion[],int id,eTipo tipos[],int tamTipos);
int cargarDescripcionColor(char descripcion[],int id,eColor colores[],int tamColores);

void mostrarMoto(eMoto moto,eTipo tipos[],int tamTipos,eColor colores[],int tamColores);
void mostrarMotos(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores);

void bajaMoto(eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores);
int buscarMoto(int id,eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores);

void modificarMoto(eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores);



int main()
{
    char seguir='s';
    char confirma;

    eMoto lista[TAM];
    inicializarMotos(lista,TAM);

    hardcodearMotos(lista,CANTHARDCODE);

    int proximoIdMoto=1;

    eTipo tipos[TAMTIPOS]={{1000,"Enduro"},{1001,"Chopera"},{1002,"Scooter"},{1003,"Ciclomotor"}};
    eColor colores[TAMCOLORES]={{10000,"Gris"},{10001,"Negro"},{10002,"Blanco"},{10003,"Azul"},{10004,"Rojo"}};

    do
    {
        switch(menu())
        {
            case 'a':
            {

                if(altaEmpleado(proximoIdMoto,lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES)==1)
                {
                    proximoIdMoto++;
                }
                break;
            }
            case 'b':
            {
                modificarMoto(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES);
                break;
            }
            case 'c':
            {
                bajaMoto(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES);
                break;
            }
            case 'd':
            {
                mostrarMotos(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES);
                break;
            }
            case 'e':
            {
                printf("Listar Tipos\n");
                break;
            }
            case 'f':
            {
                printf("Listar Colores\n");
                break;
            }
            case 'g':
            {
                printf("Listar Servicios\n");
                break;
            }
            case 'h':
            {
                printf("Alta Trabajo\n");
                break;
            }
            case 'i':
            {
                printf("Listar Trabajos\n");
                break;
            }
            case 'j':
            {
                printf("Confirma salir de gestion de empleados?(s/n): ");
                fflush(stdin);
                scanf("%c", &confirma);
                if(confirma=='s')
                {
                    seguir='n';
                }
                break;
            }
        }
        system("pause");
    }
    while(seguir=='s');
    return 0;
}

char menu()
{
    char opcion;
    system("cls");
    printf("*****Menu de Opciones*****\n");
    printf("a- Alta Moto\n");
    printf("b- Modificar Moto\n");
    printf("c- Baja Moto\n");
    printf("d- Listar Motos\n");
    printf("e- Listar Tipos\n");
    printf("f- Listar Colores\n");
    printf("g- Listar Servicios\n");
    printf("h- Alta Trabajo\n");
    printf("i- Listar Trabajos\n");
    printf("j- Salir\n\n");
    printf("Ingrese numero de opcion: ");
    fflush(stdin);
    scanf("%c",&opcion);

    return opcion;
}

void inicializarMotos(eMoto vec[],int tam)
{
    for(int i=0; i<tam; i++)
    {
        vec[i].isEmpty=1;
    }
}

int buscarLibre(eMoto vec[], int tam)
{
    int indice=-1;
    for(int i=0; i<tam; i++)
    {
        if (vec[i].isEmpty==1)//==(vec[i].isEmpty)
        {
            indice=i;
            break;
        }
    }
    return indice;
}

int altaEmpleado(int idx,eMoto moto[], int tamMotos,eTipo tipos[], int tamTipos,eColor colores[],int tamColores)
{
    int retorno=0;
    int indice=buscarLibre(moto,tamMotos);
    eMoto auxMoto;
    system("cls");
    printf("******Alta Motos******\n");
    if (indice==-1)
    {
        printf("Sistema Completo\n\n");
    }
    else
    {
            auxMoto.id=idx;
            printf("Ingrese marca: ");
            fflush(stdin);
            gets(auxMoto.marca);

            listarTipos(tipos,tamTipos);
            printf("Ingrese el tipo: ");
            scanf("%d",&auxMoto.idTipo);

            listarColores(colores,tamColores);
            printf("Ingrese el color: ");
            scanf("%d",&auxMoto.idColor);

            printf("Ingrese cilindrada(50-125-500-600-750): ");
            scanf("%d",&auxMoto.cilindrada);

            auxMoto.isEmpty=0;
            moto[indice]=auxMoto;//Copio al vector al empleado nuevo
            retorno=1;
    }
    return retorno;
}

void listarTipos(eTipo tipos[],int tamTipos)
{
    printf("****** Listado de Tipos *****\n\n");
    printf("  id     Descripcion \n");
    for(int i=0; i<tamTipos; i++)
    {
            printf("    %d    %10s\n",tipos[i].id,tipos[i].descripcion);
    }
    printf("\n\n");
}

void listarColores(eColor colores[],int tamColores)
{
    printf("****** Listado de Colores *****\n\n");
    printf("  id     Descripcion \n");
    for(int i=0; i<tamColores; i++)
    {
            printf("    %d    %10s\n",colores[i].id,colores[i].nombreColor);
    }
    printf("\n\n");
}


int cargarDescripcionTipo(char descripcion[],int id,eTipo tipos[],int tamTipos)
{
    int retorno=0;
    for(int i=0;i<tamTipos;i++)
    {
        if(tipos[i].id==id)
        {
            strcpy(descripcion,tipos[i].descripcion);
            retorno=1;
        }
    }
    return retorno;
}

int cargarDescripcionColor(char descripcion[],int id,eColor colores[],int tamColores)
{
    int retorno=0;
    for(int i=0;i<tamColores;i++)
    {
        if(colores[i].id==id)
        {
            strcpy(descripcion,colores[i].nombreColor);
            retorno=1;
        }
    }
    return retorno;
}

//void mostrarEmpleado(eEmpleado emp,eSector sectores[],int tamsec)
void mostrarMoto(eMoto moto,eTipo tipos[],int tamTipos,eColor colores[],int tamColores)
{
    char descripcionTipo[20];
    char descripcionColor[20];
    //cargarDescripcionSector(descripcion,emp.idSector,sectores,tamsec);
    cargarDescripcionTipo(descripcionTipo,moto.idTipo,tipos,tamTipos);
    cargarDescripcionColor(descripcionColor,moto.idColor,colores,tamColores);
    printf("  %d   %10s   %10s    %10s    %d \n", moto.id,moto.marca,descripcionTipo,descripcionColor,moto.cilindrada);
}



void mostrarMotos(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores)
{
    int flag=0;
    system("cls");
    printf("****** Listado de Motos *****\n\n");
    printf("  id        Marca      Tipo      Color      Cilindrada  \n");
    for(int i=0; i<tamMotos; i++)
    {
        if(motos[i].isEmpty==0)
        {
            mostrarMoto(motos[i],tipos,tamTipos,colores,tamColores);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("\n******No hay motos que listar******\n");
    }
}

void hardcodearMotos(eMoto motos[],int cant)
{
    for(int i=0;i<cant;i++)
    {
        motos[i].id=ids[i];
        strcpy(motos[i].marca,marcas[i]);
        motos[i].idTipo=idsTipos[i];
        motos[i].idColor=idsColores[i];
        motos[i].cilindrada=cilindradas[i];
        motos[i].isEmpty=0;
    }
}

int buscarMoto(int id,eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores)
{
    int indice=-1;
    for(int i=0; i<tamMotos; i++)
    {
        if (moto[i].id==id && moto[i].isEmpty==0)//==(moto[i].isEmpty)
        {
            indice=i;
            break;
        }
    }
    return indice;
}


void bajaMoto(eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores)
{
    int id;
    int existe;
    char confirma;
    system("cls");
    printf("******Baja Moto******\n");
    printf("Ingrese id: ");
    scanf("%d",&id);
    existe=buscarMoto(id,moto,tamMotos,tipos,tamTipos,colores,tamColores);
    if(existe==-1)
    {
        printf("No existe moto con este id: %d\n",id);
    }
    else
    {
        mostrarMoto(moto[existe],tipos,tamTipos,colores,tamColores);
        printf("\n Confirma Baja?(s/n): ");
        fflush(stdin);
        scanf("%c",&confirma);
        if(confirma=='s')
        {
            moto[existe].isEmpty=1;
            printf("Se ha realizado la baja con exito.\n\n");
        }
        else
        {
            printf("Se ha cancelado la operacion;");
        }
    }
}

void modificarMoto(eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores)
{
    int id;
    int existe;
    int opcion;
    int nuevoIdColor;
    int nuevaCilindrada;
    system("cls");
    printf("******Modificar Moto******\n");
    printf("Ingrese id: ");
    scanf("%d",&id);
    existe=buscarMoto(id,moto,tamMotos,tipos,tamTipos,colores,tamColores);
    if(existe==-1)
    {
        printf("No existe moto con este id: %d\n",id);
    }
    else
    {
        mostrarMoto(moto[existe],tipos,tamTipos,colores,tamColores);

        printf("Que dato desea modificar? \n");
        printf("1-Cilindrada\n ");
        printf("2-Color\n");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                {
                    printf("Ingrese nueva cilindrada: ");
                    scanf("%d",&nuevaCilindrada);
                    moto[existe].cilindrada=nuevaCilindrada;
                    printf("Se ha actualizado la cilindrada con exito.");
                    break;
                }
            case 2:
                {
                    listarColores(colores,tamColores);
                    printf("Ingrese el nuevo color: ");
                    scanf("%d",&nuevoIdColor);
                    moto[existe].idColor=nuevoIdColor;
                    printf("Se ha actualizado el color con exito.");
                    break;
                }
            default:
                {
                    printf("Opcion Incorrecta.");
                    break;
                }
        }

    }
}


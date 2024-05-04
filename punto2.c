#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//estructura tarea
struct Tarea{
    int TareaID;//Numerico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 - 100
}typedef Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}TNodo;

TNodo *crearTarea(int id, char *descripcion, int duracion);
TNodo *crearLista();
void insertarLista(TNodo **cabeza, int id, char *descripcion, int duracion);
void imprimirLista(TNodo *cabeza);
TNodo *tranferirTareasRealizadas(TNodo **cabeza, int id);
void LimpiarTarea(TNodo **cabeza);

int main()
{
    TNodo *lista = crearLista();
    int id = 1000;
    int id2;
    char des[100];
    int dura;
    char respuesta;

    do
    {   
        printf("Ingrese la descripcion de la tarea: ");
        scanf("%s", des);
        printf("\nIngrese la duracion de la tarea (10 - 100): ");
        scanf("%d",&dura);
        insertarLista(&lista,id,des,dura);
        printf("\n¿Desea ingresar otra tarea? (s/n): ");
        getchar(); // Limpiar buffer del teclado
        scanf("%c", &respuesta);
        printf("\n");
        id ++;
    }while(respuesta == 's' || respuesta == 'S');
    printf("\nTareas pendientes:\n\n");
    imprimirLista(lista);

    //PUNTO 2: 
    
    printf("\nIngrese el ID de la tarea que desea marcar como realizada: ");
    scanf("%d",&id2);
    printf("\nID ingresado: %d\n",id2);
    printf("\nTareas realizadas:\n\n");
    TNodo *tareasRalizadas = tranferirTareasRealizadas(&lista,id2);
    imprimirLista(tareasRalizadas);



    //liberar memoria de la lista
    LimpiarTarea(&lista);

    return 0;
}

TNodo *crearTarea(int id, char *descripcion, int duracion)
{
    TNodo *nuevaTarea = (TNodo *)malloc(sizeof(TNodo));
    nuevaTarea->T.TareaID = id;
    nuevaTarea->T.Descripcion = strdup(descripcion);
    nuevaTarea->T.Duracion = duracion;
    nuevaTarea->Siguiente = NULL;
    return nuevaTarea;
}

TNodo *crearLista()
{
    return NULL;
}

void insertarLista(TNodo **cabeza, int id, char *descripcion, int duracion)
{
    TNodo *nuevo = crearTarea(id,descripcion,duracion);
 
    nuevo->Siguiente = *cabeza;
    *cabeza = nuevo;
}

void imprimirLista(TNodo *cabeza)
{
    TNodo *actual = cabeza;
    while(actual != NULL)
    {
        printf("TareaID: %d | Descripcion: %s | Duracion: %d\n",actual->T.TareaID,actual->T.Descripcion,actual->T.Duracion);
        actual = actual->Siguiente;
    }
}

void LimpiarTarea(TNodo **cabeza)
{
    TNodo *temp;
    while(*cabeza != NULL)
    {
        temp = *cabeza;
        *cabeza = temp->Siguiente;
        free(temp);
    }
}

TNodo *tranferirTareasRealizadas(TNodo **cabeza, int id)
{
    TNodo *listaTranferidas = NULL;
    TNodo *prev = NULL;
    TNodo *tem = *cabeza;

    while(tem !=NULL)
    {
        if(tem->T.TareaID == id)
        {
            if(prev == NULL)
            {
                *cabeza = tem->Siguiente;
            }else{
                prev->Siguiente = tem->Siguiente;
            }
            insertarLista(&listaTranferidas,tem->T.TareaID,tem->T.Descripcion,tem->T.Duracion);
            tem = (prev == NULL) ? *cabeza : prev->Siguiente;
        }
        else{
            prev = tem;
            tem = tem->Siguiente;
        }
    }

    return listaTranferidas;

    
}

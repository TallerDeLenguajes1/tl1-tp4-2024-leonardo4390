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
void LimpiarTarea(TNodo **cabeza);
int main()
{
    TNodo *lista = crearLista();
    int id = 1000;
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
    printf("\nTareas pendientes:\n");
    imprimirLista(lista);

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

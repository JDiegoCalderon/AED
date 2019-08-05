//Practica 1->Algoritmos y estructura de datos
//
//Arbol Binario de B�squeda
//
//Juan Diego Calderon Mosqueda
//

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0


typedef struct _nodo {
   int dato;
   struct _nodo *derecho;
   struct _nodo *izquierdo;
} tipoNodo;


typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;

//Funciones con �rboles
//Insertar en �rbol ordenado
void Insertar(Arbol *a, int dat);

//Borrar un elemento:
void Borrar(Arbol *a, int dat);

//Funci�n de b�squeda
int Buscar(Arbol a, int dat);

//Comprobar si el �rbol est� vac�o
int Vacio(Arbol r);

//Comprobar si es un nodo hoja
int EsHoja(pNodo r);

//Contar n�mero de nodos
int NumeroNodos(Arbol a, int* c);

//Calcular la altura de un �rbol
int AlturaArbol(Arbol a, int* altura);

//Calcular altura de un dato
int Altura(Arbol a, int dat);

//Aplicar una funci�n a cada elemento del �rbol:
void InOrden(Arbol, void (*func)(int*));
void PreOrden(Arbol, void (*func)(int*));
void PostOrden(Arbol, void (*func)(int*));

void Podar(Arbol *a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);

void Mostrar(int *d);

int main(int argc, char* argv[])
{
   Arbol ArbolInt=NULL;
   int altura;
   int nnodos;

//Inserci�n de nodos en �rbol:
   Insertar(&ArbolInt, 10);
   Insertar(&ArbolInt, 5);
   Insertar(&ArbolInt, 12);
   Insertar(&ArbolInt, 4);
   Insertar(&ArbolInt, 7);
   Insertar(&ArbolInt, 3);
   Insertar(&ArbolInt, 6);
   Insertar(&ArbolInt, 9);
   Insertar(&ArbolInt, 8);
   Insertar(&ArbolInt, 11);
   Insertar(&ArbolInt, 14);
   Insertar(&ArbolInt, 13);
   Insertar(&ArbolInt, 2);
   Insertar(&ArbolInt, 1);
   Insertar(&ArbolInt, 15);
   Insertar(&ArbolInt, 10);
   Insertar(&ArbolInt, 17);
   Insertar(&ArbolInt, 18);
   Insertar(&ArbolInt, 16);

   printf("Altura de arbol %d\n", AlturaArbol(ArbolInt, &altura));

   //Mostrar el �rbol en tres ordenes distintos:
   printf("InOrden: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   printf("PreOrden: ");
   PreOrden(ArbolInt, Mostrar);
   printf("\n");
   printf("PostOrden: ");
   PostOrden(ArbolInt, Mostrar);
   printf("\n");

   //Borraremos algunos elementos:
   printf("N nodos: %d\n", NumeroNodos(ArbolInt, &nnodos));
   Borrar(&ArbolInt, 5);
   printf("Borrar 5: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 8);
   printf("Borrar 8: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 15);
   printf("Borrar 15: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 245);
   printf("Borrar 245: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 4);
   printf("Borrar 4: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 17);
   printf("Borrar 17: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");

//Veamos algunos par�metros
   printf("N nodos: %d\n", NumeroNodos(ArbolInt, &nnodos));
   printf("Altura de 1 %d\n", Altura(ArbolInt, 1));
   printf("Altura de 10 %d\n", Altura(ArbolInt, 10));
   printf("Altura de arbol %d\n", AlturaArbol(ArbolInt, &altura));

//Liberar memoria asociada al �rbol:
   Podar(&ArbolInt);
   system("PAUSE");
   return 0;
}

//Poda: borrar todos los nodos a partir de uno, incluido */
void Podar(Arbol *a)
{
//postorden
   if(*a) {
      Podar(&(*a)->izquierdo); //Podar izquierdo
      Podar(&(*a)->derecho);   //Podar derecho
      free(*a);                //Eliminar nodo
      *a = NULL;
   }
}

//Insertar un dato en el �rbol Binario
void Insertar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual = *a;

//Buscar el dato en el �rbol, manteniendo un puntero al nodo padre
   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat < actual->dato) actual = actual->izquierdo;
      else if(dat > actual->dato) actual = actual->derecho;
   }

   if(!Vacio(actual)) return;
//Si padre es NULL, entonces el �rbol estaba vac�o, el nuevo nodo ser� el nodo raiz
   if(Vacio(padre)) {
      *a = (Arbol)malloc(sizeof(tipoNodo));
      (*a)->dato = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
   }
//Si el dato es menor que el que contiene el nodo padre, lo insertamos en la rama izquierda
   else if(dat < padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->izquierdo = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
   }
//Si el dato es mayor que el que contiene el nodo padre, lo insertamos en la rama derecha
   else if(dat > padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->derecho = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
  }
}

//Eliminar un elemento de un �rbol binario
void Borrar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual;
   pNodo nodo;
   int aux;

   actual = *a;
   while(!Vacio(actual)) {
      if(dat == actual->dato) { //Si el valor est� en el nodo actual
         if(EsHoja(actual)) { //Y si adem�s es un nodo hoja: lo borramos
            if(padre)
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            free(actual);
            actual = NULL;
            return;
         }
         else { //Si el valor est� en el nodo actual, pero no es hoja
            padre = actual;
            //Buscar nodo m�s izquierdo de rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            //buscar nodo m�s derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            //Intercambiar valores de no a borrar u nodo encontrado
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else {
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
}

//Recorrido de �rbol en inorden
void InOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) InOrden(a->izquierdo, func);
   func(&(a->dato));
   if(a->derecho) InOrden(a->derecho, func);
}

//Recorrido de �rbol en preorden
void PreOrden(Arbol a, void (*func)(int*))
{
   func(&a->dato);
   if(a->izquierdo) PreOrden(a->izquierdo, func);
   if(a->derecho) PreOrden(a->derecho, func);
}

//Recorrido de �rbol en postorden
void PostOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) PostOrden(a->izquierdo, func);
   if(a->derecho) PostOrden(a->derecho, func);
   func(&a->dato);
}

//Buscar un valor en el �rbol
int Buscar(Arbol a, int dat)
{
   pNodo actual = a;


   while(!Vacio(actual)) {
      if(dat == actual->dato) return TRUE;
      else if(dat < actual->dato) actual = actual->izquierdo;
      else if(dat > actual->dato) actual = actual->derecho;
   }
   return FALSE;
}

//Calcular la altura del nodo que contiene el dato dat
int Altura(Arbol a, int dat)
{
   int altura = 0;
   pNodo actual = a;


   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura;
      else {
         altura++;
         if(dat < actual->dato) actual = actual->izquierdo;
         else if(dat > actual->dato) actual = actual->derecho;
      }
   }
   return -1;
}

//Contar el n�mero de nodos
int NumeroNodos(Arbol a, int *contador)
{
   *contador = 0;

   auxContador(a, contador);
   return *contador;
}

//Funci�n auxiliar para contar nodos
void auxContador(Arbol nodo, int *c)
{
   (*c)++;//Otro nodo
   if(nodo->izquierdo) auxContador(nodo->izquierdo, c);
   if(nodo->derecho)   auxContador(nodo->derecho, c);
}

//Calcular la altura del �rbol, que es la altura del nodo de mayor altura
int AlturaArbol(Arbol a, int *altura)
{
   *altura = 0;

   auxAltura(a, 0, altura);
   return *altura;
}

//Funci�n auxiliar para calcular altura
void auxAltura(pNodo nodo, int a, int *altura)
{

   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1, altura);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1, altura);
   //Proceso, si es un nodo hoja, y su altura es mayor que la actual del �rbol, actualizamos la altura actual del �rbol
   if(EsHoja(nodo) && a > *altura) *altura = a;
}

//Comprobar si un �rbol es vac�o */
int Vacio(Arbol r)
{
   return r==NULL;
}

//Comprobar si un nodo es hoja */
int EsHoja(pNodo r)
{
   return !r->derecho && !r->izquierdo;
}

//Funci�n de prueba para recorridos del �rbol */
void Mostrar(int *d)
{
   printf("%d, ", *d);
}


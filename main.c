#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
	// Se crea la lista
	Lista lista = crea_lista();
	
	printf("La lista tiene %lu elementos\n", longitud(lista));

	// Se insertan datos de prueba
	inserta_datos_de_prueba(lista);
	// Se remueve un elemento de la lista
	Elemento *borrado = quita_elemento(lista, 0);
	if (borrado != NULL){
		free(borrado->valor);
		free(borrado);
	}
	printf("La lista tiene %lu elementos:\n", longitud(lista));
	
	// Se remueve un elemento que no existe en la lista
	quita_elemento(lista, longitud(lista));
	printf("La lista tiene %lu elementos \n", longitud(lista));

	//Se imprime la lista antes de ordenar
	imprime_lista_int(lista);
	ordena_lista(lista, &cmp_int);

	//Se imprime la lista después de ordenar
	imprime_lista_int(lista);

	//Se libera la memoria ocupada
	borra_lista(lista);
	
}

void inserta_datos_de_prueba(Lista lista){
	srand(time(NULL));
	int *num_a_insertar;
	int indice;
	for (indice = 0; indice < 20; ++indice) {
		num_a_insertar = malloc(sizeof(int));
		*num_a_insertar = rand() % 100;
		inserta_elemento(lista, num_a_insertar);
	};
}

// Función que compara dos valores de "Elementos" de una lista ligada.
/*Compara 2 'Elemento' que contienen como valor un 'int'*/
int cmp_int(const void* a, const void* b){
	Elemento* e1 = (Elemento*) a;
	Elemento* e2 = (Elemento*) b;
	int val1 = *((int*)e1->valor);
	int val2 = *((int*)e2->valor);
	return val1 - val2;
}

/*Función que ordena una lista usando una función comparadora*/
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){
	size_t nitems = longitud(lista);
	if(nitems <= 1)
		return;
	int i;
	size_t size = sizeof(Elemento);
	Elemento *pos_actual = *lista;
	Elemento array[nitems];
	for(i = 0; i < nitems; i++){
		array[i] = *pos_actual;
		pos_actual = pos_actual->siguiente;
	}
	qsort(array, nitems, size, cmp);	
	pos_actual = *lista;
	for(i = 0; i < nitems; i++){
		pos_actual->valor = array[i].valor;
		pos_actual = pos_actual->siguiente;
	}
}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista lista){
	Elemento *pos_actual = *lista;
	Elemento *auxiliar = pos_actual;
	while(pos_actual != NULL){
		free(pos_actual->valor);
		pos_actual = pos_actual->siguiente;
		free(auxiliar);		
		auxiliar = pos_actual;
	}
	free(lista);
}

/*Remueve un elemento de una lista en una posición dada */
//Si la posición no coincide con ningún elemento se regresa NULL
//considerando que el primer elemento de una lista esta en la posicion 0
Elemento *quita_elemento(Lista lista, size_t posicion){
	int tam_lista = longitud(lista);
	if(posicion < 0 || posicion > tam_lista-1){
		return NULL;
	}
	int pos = 0;
	Elemento *pos_actual = *lista;
	do{
		if(posicion == 0){
			Elemento *borrado = *lista;
			*lista = (*lista)->siguiente;
			return borrado;
		}
		else if(pos == posicion-1){
			Elemento *borr = pos_actual->siguiente;
			pos_actual->siguiente = pos_actual->siguiente->siguiente;
			return borr;
		}
		pos_actual = pos_actual->siguiente;
		pos++;
	}while(pos_actual != NULL);
	//debido al guardia del inicio esta linea es inalcanzable
	return NULL;
}

/*Imprime los elementos de la lista como enteros */
void imprime_lista_int(Lista lista){
	Elemento *pos_actual = *lista;
	while(pos_actual != NULL){
		printf("%d ", *((int*)(pos_actual->valor)));
		pos_actual = pos_actual->siguiente;
	}
	printf("\n");
}

/*Crea una lista vacía */
Lista crea_lista(){
	Lista lista = malloc(sizeof(Lista));
	return lista;
}

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista. Para no recorrer toda la lista
se inserta al inicio de la misma*/ 
int inserta_elemento(Lista lista, void *valor){
	Elemento* nuevo_el = malloc(sizeof(Elemento));
	nuevo_el->valor = valor;
	nuevo_el->siguiente = *lista;
	*lista = nuevo_el;
	return longitud(lista) + 1;
}

/*Regresa el número de elementos en la lista */
size_t longitud(Lista lista){
	int tam = 0;
	Elemento *pos_actual = *lista;
	while(pos_actual != NULL){
		pos_actual = pos_actual->siguiente;
		tam++;
	}
	return tam;
}
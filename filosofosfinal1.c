#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//cantidad de comida en cada plato
//comida es global
int comida;
struct filosofo
{
	char * nombre;
	int cantcomida;
	struct  tenedor * ten1;
	struct  tenedor * ten2;
};
struct tenedor
{
	//0 significa que el tenedoo esta desocupado y 1 ocupado
	int estado;
};

void * comer(void * h1){
	
}

int main()
{
	//N = numero de fiilosofos
    int N = 6;
    int i;

    //lista de tenedores
    struct tenedor * ten1[N+1];

    //lista de N filosofos
    struct filosofo * fil1[N];

    //incializamos los tenedores
    for (i = 0; i < N+1; i++){
        ten1[i]=(struct tenedor *) malloc (sizeof(struct tenedor));
        //todos los tenedores desocupados
        ten1[i]->estado=0;
    }

    //inicializamos todos los filosofos
    for (i = 0; i < N; i++){
        fil1[i]=(struct filosofo *) malloc (sizeof(struct filosofo));
        fil1[i]->nombre= "filosofo";
        fil1[i]->cantcomida = comida;
	    fil1[i]->ten1 = ten1[i];
	    fil1[i]->ten2 = ten1[i+1];
    }
    fil1[N+1]->ten2 = ten1[0];
	pthread_t a[N];
    for (i = 0; i < N; i++) {
    pthread_create(&a[i], NULL, comer, (void*) fil1[i]);
    }

    for (i = 0; i < N; i++) pthread_join(a[i], NULL);


	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//cantidad de comida en cada plato
int comida = 6;
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
	struct filosofo * fil;
	fil = (struct filosofo*) h1;
	printf("%s %s \n" , fil->nombre, "esta pensando");
	while(fil->cantcomida>0){
		//si los 2 tenedores estan libres el filosofo puede comer
		if(fil->ten1->estado == 0 && fil->ten2->estado == 0){
			printf("%s %s \n" , fil->nombre, "tiene hambre");

			//el filosofo agarra los tenedores
			fil->ten1->estado = fil->ten2->estado = 1;
			printf("%s %s \n" , fil->nombre, "agarro los 2 tenedores");
			while (fil->cantcomida > 0)
			{
				fil->cantcomida--;
				printf("%s %s \n" , fil->nombre, "esta comiendo");
			}
			
		}
		else{
			printf("%s %s \n" , fil->nombre, "no puede comer");
		}
	}
	//el filosofo termina de comer y libera un tenedor
	fil->ten1->estado = fil->ten2->estado = 0;
	printf("%s %s \n" , fil->nombre, "termino de comer");
}

int main()
{
	//creamos los hilos
	pthread_t thread1,  thread2, thread3, thread4, thread5;

	struct tenedor * ten1 = (struct tenedor *) malloc (sizeof(struct tenedor));
	struct tenedor * ten2 = (struct tenedor *) malloc (sizeof(struct tenedor));
	struct tenedor * ten3 = (struct tenedor *) malloc (sizeof(struct tenedor));
	struct tenedor * ten4 = (struct tenedor *) malloc (sizeof(struct tenedor));
	struct tenedor * ten5 = (struct tenedor *) malloc (sizeof(struct tenedor));

	struct filosofo * fil1 = (struct filosofo *) malloc (sizeof(struct filosofo));
	struct filosofo * fil2 = (struct filosofo *) malloc (sizeof(struct filosofo));
	struct filosofo * fil3 = (struct filosofo *) malloc (sizeof(struct filosofo));
	struct filosofo * fil4 = (struct filosofo *) malloc (sizeof(struct filosofo));
	struct filosofo * fil5 = (struct filosofo *) malloc (sizeof(struct filosofo));

	//todos los tenedores desocupados
	ten1->estado = ten2->estado = ten3->estado = ten4->estado = ten5->estado = 0;
	fil1->nombre = "fil1";
	fil1->cantcomida = comida;
	fil1->ten1 = ten1;
	fil1->ten2 = ten2;

	fil2->nombre = "fil2";
	fil2->cantcomida = comida;
	fil2->ten1 = ten2;
	fil2->ten2 = ten3;

	fil3->nombre = "fil3";
	fil3->cantcomida = comida;
	fil3->ten1 = ten3;
	fil3->ten2 = ten4;

	fil4->nombre = "fil4";
	fil4->cantcomida = comida;
	fil4->ten1 = ten4;
	fil4->ten2 = ten5;

	fil5->nombre = "fil5";
	fil5->cantcomida = comida;
	fil5->ten1 = ten5;
	fil5->ten2 = ten1;
	
	int iret1, iret2, iret3, iret4, iret5;
	iret1 = pthread_create( &thread1, NULL, comer, (void*) fil1);
	iret2 = pthread_create( &thread2, NULL, comer, (void*) fil2);
	iret3 = pthread_create( &thread3, NULL, comer, (void*) fil3);
	iret4 = pthread_create( &thread4, NULL, comer, (void*) fil4);
	iret5 = pthread_create( &thread5, NULL, comer, (void*) fil5);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	pthread_join(thread5, NULL);

	printf("Thread 1 returns: %d\n", iret1);
	printf("Thread 2 returns: %d\n", iret2);
	printf("Thread 3 returns: %d\n", iret3);
	printf("Thread 4 returns: %d\n", iret4);
	printf("Thread 5 returns: %d\n", iret5);
	return 0;
}
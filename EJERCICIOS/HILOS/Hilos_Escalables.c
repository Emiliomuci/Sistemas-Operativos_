//El algortimo debe de ser escalavable, debe de funcionar para cualqueir numero de hilos
	//Crear 7 hilos vivos, y cuando se meta un caracter con getchar, y con se al intro, cada uno de los hilos creados, mueren en el orden ivnerso a su creación.
	
	//He nacido. Soy el hilo 1 con ID 2312413243
	
	//Getchar
	
	//EL hilo numero 7 con ID  e234242 es acabado
	//Osea el ultimo hilo que se ha creado es el primero en morir
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h> 
#include <semaphore.h>
#include <pthread.h>
#define NUMEROHILOS 7

void* hilosEscalables (void* arg){
	int id = *(int*) arg;
printf("He nacido, soy el hilo %d con ID %d\n", id + 1, pthread_self());

return NULL;	
}


int main(int argc, char **argv)
{
	pthread_t hilo[NUMEROHILOS];
	int ids[NUMEROHILOS];
	
	for (int i = 0; i < NUMEROHILOS; i++)
	{
		ids[i] = i;
			pthread_create(&hilo[i],NULL, hilosEscalables, &ids[i]);
			pthread_join(hilo[i], NULL);
	}
	
	printf("Presiona lo que sea en el teclado: \n");
	getchar();
	
	for (int i = NUMEROHILOS - 1; i >= 0; i --)
	{
		pthread_cancel(hilo[i]);
		pthread_join(hilo[i],NULL);
		
		printf("El hilo numero %d con ID %d \n", i + 1, hilo[i]);

	}
	
	char texto[100];
	
	printf("Escribe un texto\n");
	scanf("%s",texto);
	
	int inversa = strlen(texto);
	int contadorVocales = 0;
	for (int i = inversa - 1; i >= 0; i--)
	{
		char letra = texto[i];
		printf("%c", texto[i]);
		
		
		letra = tolower(letra);
		if(letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u'){
			contadorVocales++;
		}
		
		
	}
	printf("\nVocales: %d\n", contadorVocales);

	
	
	
	
	return 0;
}


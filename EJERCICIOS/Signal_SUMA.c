

#include <stdio.h>
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
static int *num1;
static int *num2;
static int *division;
int operacion;
int activo = 1;
	int tuberia[2];


void insultar (int sig){
	printf("Estas bien menso\n");
	exit(1);

}

void term (int sig){
	printf("Se termina perro\n");
	exit(0);
}
void divide (){
	while(activo){
	printf("1.- Escribe tus dos números: \n");
	        fflush(stdout);

	scanf("%d", num1);
	
	printf("2.- Escribe tus dos números: \n");
		scanf("%d", num2);
	        fflush(stdout);
	        
	
	if(*num2 == 0){
		raise (SIGFPE);
		return;
	}
		*division = *num1 / *num2;

		printf("Resultado: %d\n", *division );


}
}



int main(int argc, char **argv)
{
	pid_t pid;
	
	num1 = mmap(NULL, sizeof *num1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	num2 = mmap(NULL, sizeof *num2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	division = mmap(NULL, sizeof *division, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	printf("PID %d", getpid());
	
	
	if( signal(SIGFPE, insultar) ==SIG_ERR){
		perror("error SIGFPE");
		return -1;
		
	}
   /* if(signal(SIGUSR1, handle_usr1_signal) == SIG_ERR){
		perror("error SIGUSR1");
		return -1;
	}*/
	if (signal(SIGTERM, term)== SIG_ERR){
		perror("error SIGTERM");
		return -1;
		
	}
	
	
	
	if(pipe(tuberia)== -1){
		perror("Invalid tuberia");
		return -1;
	}
	
	
	pid = fork();
	if(pid < 0 ){
		perror("Invalid fork");
		return -1;
	}
	
	else if (pid == 0){
				close(tuberia[0]);

	
	
	
		divide();
			write(tuberia[1], division, sizeof(int));

		
		
				close(tuberia[1]);

	}
	else{
				close(tuberia[1]);
				wait(NULL);
				
int resultadoDivision;

		read(tuberia[0], &resultadoDivision, sizeof(int));
		
		
		
		printf("\nPADRE RESULTADO: %d", resultadoDivision);
		
				close(tuberia[0]);

		
	}
	
	
	
	
	return 0;
}


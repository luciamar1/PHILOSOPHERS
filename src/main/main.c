#include "philosophers.h"

void *f_hilo(void *arg) 
{
	printf("%s\n", (char *) arg);
    return NULL;
}

int main(int argc, char **argv)
{
	int fork;
	pthread_t thread_id;
	int creacion = pthread_create(&thread_id, NULL, f_hilo, fork);
	if (creacion)
		printf("error\n");
	 int espera = pthread_join(thread_id, NULL);
    if (espera) {
        fprintf(stderr, "Error al esperar al hilo\n");
        return 1;
    }
	return(0);
}

// Programa para utilizaçao de threads e sinais

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define NUMBER_OF_ITERATIONS 10

void first_handler(int process_signo)
{
	printf("Processo imune a interrupcao do teclado.\n");
}

void second_handler(int process_signo)
{
	printf("O processo recebeu um alarme. Mas nao sera encerrado.\n");
}

int number_one = 0, number_two = 0;

void *first_task(void *argument_first_task)
{
	int *integer_pointer = (int*)argument_first_task;
	int counter;

	for(counter = 0; counter < NUMBER_OF_ITERATIONS; counter ++)
	{
		printf("Executando tarefa 1...\n");
		(*integer_pointer)++;
		sleep(5);
	}

	pthread_exit(NULL);
}

void *second_task(void *argument_second_task)
{
	int *integer_pointer = (int*)argument_second_task;
	int counter;

	for(counter = 0; counter < NUMBER_OF_ITERATIONS; counter ++)
	{
		printf("Executando tarefa 2...\n");
		(*integer_pointer)++;
		sleep(5);
	}

	pthread_exit(NULL);
}

void calculate_total(const int first_number, const int second_number)
{
	int total = 0;
	total = first_number + second_number;

	printf("Tarefa 1: %d. Tarefa 2: %d. Total: %d.\n",first_number, second_number, total);
}

int main()
{
	pthread_t thread_one, thread_two;

	signal(SIGINT, first_handler);
	signal(SIGALRM, second_handler);

	printf("Bem vindo ao programa de multithread.\n");
	printf("Eu sou o processo principal. Minha identificacao: %d.\n", getpid());

	printf("Criando threads...\n");

	pthread_create(&thread_one, NULL, &first_task, &number_one);
	pthread_create(&thread_two, NULL, &second_task, &number_two);

	pthread_join(thread_one, NULL);
	pthread_join(thread_two, NULL);

	printf("\n");
	printf("Threads finalizadas. Imprimindo valores contidos nas variaveis globais...\n");

	calculate_total(number_one, number_two);

	printf("Obrigado por utilizar o programa.\n");

	return 0;
}

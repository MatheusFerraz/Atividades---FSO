#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

int value_one = 4, value_two = 5, value_three = 9, value_four = 8, result_one = 0, result_two = 0;

void *first_task()
{
	int first_value = value_one;
	int second_value = value_two;

	printf("Executando primeira tarefa...\n");

	result_one = first_value + second_value;

	sleep(3);

	pthread_exit(NULL);
}

void *second_task()
{
	int first_value = value_three;
	int second_value = value_four;

	printf("Executando segunda tarefa...\n");

	result_two = first_value + second_value;

	sleep(3);

	pthread_exit(NULL);	
}

void print_calculations_result(int first_result, int second_result)
{
	printf("Resultado para o primeiro calculo: %d.\n", result_one);
	printf("Resultado para o segundo calculo: %d.\n", result_two);
}

int main()
{
	int main_pid = getpid();
	pthread_t thread_one, thread_two;

	printf("Eu sou a Main. Meu PID: %d.\n", main_pid);
	printf("Criando e atribuindo atividades as threads...\n");

	pthread_create(&thread_one, NULL, &first_task, NULL);
	pthread_create(&thread_two, NULL, &second_task, NULL);

	pthread_join(thread_one, NULL);
	pthread_join(thread_two, NULL);

	print_calculations_result(result_one, result_two);

	putchar('\n');

	return 0;
}
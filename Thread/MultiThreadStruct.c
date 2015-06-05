#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUMBER_OF_STUDENTS 2

struct Student
{
	int student_id;
	char student_name[40];
	float student_average;
};

void *first_task(void *argument_one)
{
	int counter;
	Student *student_pointer;
	student_pointer = (Student*)argument_one;

	for(counter = 0; counter < NUMBER_OF_STUDENTS; counter ++)
	{
		printf("Informacoes do Aluno [%d] do Vetor 1: \n",counter + 1);
		printf("Numero de Identificacao: %d.\n",student_pointer[counter].student_id);
		printf("Nome do Aluno: %s.\n",student_pointer[counter].student_name);
		printf("Media do Aluno: %f.\n",student_pointer[counter].student_average);
		sleep(2);
	}

	pthread_exit(NULL);
}

void *second_task(void *argument_two)
{
	int counter;
	Student *student_pointer;
	student_pointer = (Student*)argument_two;

	for(counter = 0; counter < NUMBER_OF_STUDENTS; counter ++)
	{
		printf("Informacoes do Aluno [%d] do Vetor 2: \n", counter + 1);
		printf("Numero de Identificacao: %d.\n", student_pointer[counter].student_id);
		printf("Nome do Aluno: %s.\n",student_pointer[counter].student_name);
		printf("Media do Aluno: %f.\n",student_pointer[counter].student_average);
		sleep(2);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	Student *vector_one, *vector_two;
	pthread_t thread_one, thread_two;
	int counter_main;
	pid_t main_pid = getpid();

	vector_one = (Student*)calloc(NUMBER_OF_STUDENTS,sizeof(Student));
	vector_two = (Student*)calloc(NUMBER_OF_STUDENTS,sizeof(Student));

	printf("Eu sou a main. Meu pid: %d.\n",main_pid);

	for(counter_main = 0; counter_main < NUMBER_OF_STUDENTS; counter_main ++)
	{
		printf("Insira as informacoes do aluno [%d] do vetor 1.\n",counter_main + 1);
		printf("Numero de identificacao do aluno [%d]: \n",counter_main + 1);
		scanf("%d",&vector_one[counter_main].student_id);
		printf("Nome do aluno [%d]: \n",counter_main + 1);
		scanf(" %40[^\n]",vector_one[counter_main].student_name);
		printf("Media do aluno [%d]: \n", counter_main + 1);
		scanf("%f",&vector_one[counter_main].student_average);
	}

	for(counter_main = 0; counter_main < NUMBER_OF_STUDENTS; counter_main ++)
	{
		printf("Insira as informacoes do aluno [%d] do vetor 2.\n",counter_main + 1);
		printf("Numero de identificacao do aluno [%d]: \n",counter_main + 1);
		scanf("%d",&vector_two[counter_main].student_id);
		printf("Nome do aluno [%d]: \n",counter_main + 1);
		scanf(" %40[^\n]",vector_two[counter_main].student_name);
		printf("Media do aluno [%d]: \n", counter_main + 1);
		scanf("%f",&vector_two[counter_main].student_average);
	}

	printf("Criando threads e delegando impressao...\n");

	pthread_create(&thread_one, NULL, &first_task, vector_one);
	pthread_create(&thread_two, NULL, &second_task, vector_two);

	pthread_join(thread_one, NULL);
	pthread_join(thread_two, NULL);

	printf("Finalizando execucao do programa. Eu sou a main.\n");

	return 0;
}

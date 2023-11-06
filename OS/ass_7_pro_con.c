#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>		
#include <semaphore.h>		
#define BUFFER_SIZE 5

sem_t full,empty;		
pthread_mutex_t mutex;		
int array[BUFFER_SIZE];		

int in=0;		
int out=0;		

void *producer(void *data)		
{
	int i,num,id;
	id=(int)data;
	for(i=0;i < 3;i++)		
	{
		
		sem_wait(&empty);		
		pthread_mutex_lock(&mutex);	
		
		num=id;			
		array[in]=num;			
		printf("\n\t Producer =%d produced value = %d stored at location=%d ",id,array[in],in);
		in=(in+1)%BUFFER_SIZE;		

		pthread_mutex_unlock(&mutex);	
		sem_post(&full);		
		sleep(2);
	}
}

void *consumer(void *data)	
{
	int i,num,r;
	do	
	{
		sem_wait(&full);	
		pthread_mutex_lock(&mutex);		

		num=array[out];				
		printf("\n\t\t\t Consumer consumed value = %d from location=%d",num,out);
		out=(out+1)%BUFFER_SIZE;		

		pthread_mutex_unlock(&mutex);		
		sem_post(&empty);			
		sleep(3);
		sem_getvalue(&empty,&r);

	}while(r!=BUFFER_SIZE);
}

int main()		
{
	pthread_t tid[4],tid1;	
	int i;
	sem_init(&full,0,0);	
	sem_init(&empty,0,5);

	for(i=0;i<4;i++)
	pthread_create(&tid[i],NULL,producer,(void *)i); 
	pthread_create(&tid1,NULL,consumer,NULL); 

	for(i=0;i<4;i++)
	pthread_join(tid[i],NULL);
	pthread_join(tid1,NULL);

	return 0;
}

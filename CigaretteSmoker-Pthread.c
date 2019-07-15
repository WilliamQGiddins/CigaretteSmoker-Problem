//William Giddins Lab 6 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>


pthread_mutex_t lock; 
pthread_mutex_t t_p;
pthread_mutex_t m_p;
pthread_mutex_t t_m;
pthread_mutex_t ag;

int randnum;

void *agent(void *arg){   //Agent thread that distributes the items 
	
	for(int i=0;i<100;i++){
		pthread_mutex_lock(&lock);
		printf("In agent \n");
		randnum=rand() % (3 + 1 - 1) + 1;	//chooses what items to distribute
		if( randnum == 1){
				
				pthread_mutex_unlock(&t_p);
		}
				else if (randnum == 2){
					pthread_mutex_unlock(&t_m);
				}
				     else{
					 pthread_mutex_unlock(&m_p);
				     }
				pthread_mutex_unlock(&lock);
				pthread_mutex_lock(&ag);
	}	
return NULL;
}


void *smoker1(void *arg){	//Smoker 1 thread that needs tobacco and paper
	for(int i=0;i<100;i++){
				pthread_mutex_lock(&t_p);
				pthread_mutex_lock(&lock);
				printf("Smoker 1 Smoked \n");
				pthread_mutex_unlock(&ag);
				pthread_mutex_unlock(&lock);
				
	}

return NULL;
}

void *smoker2(void *arg){	//Smoker 2 thread that needs tobacco and matches
	for(int i=0;i<100;i++){
				pthread_mutex_lock(&t_m);
				pthread_mutex_lock(&lock);
				printf("Smoker 2 Smoked \n");
				pthread_mutex_unlock(&ag);
				pthread_mutex_unlock(&lock);
				
	}
return NULL;
}

void *smoker3(void *arg){      //Smoker 3 thread that needs matches and paper
	for(int i=0;i<100;i++){
				pthread_mutex_lock(&m_p);
				pthread_mutex_lock(&lock);
				printf("Smoker 3 Smoked \n");
				pthread_mutex_unlock(&ag);
				pthread_mutex_unlock(&lock);
				
	}
return NULL;
}



int main (int argc, char* argv[]){
					//creation of mutex's to keep smokers and agent from entering critical regions simulatenously
	pthread_mutex_init(&lock, NULL); 
	pthread_mutex_init(&t_p, NULL);
	pthread_mutex_init(&m_p, NULL);
	pthread_mutex_init(&t_m, NULL);
	pthread_mutex_init(&ag, NULL);
	
	pthread_t t0,t1,t2,t3;		
					//creation of Smoker and Agent threads
	pthread_create(&t0, NULL, agent, NULL);
	pthread_create(&t1, NULL, smoker1, NULL);
	pthread_create(&t2, NULL, smoker2, NULL);
	pthread_create(&t3, NULL, smoker3, NULL);
	
	pthread_join(t0,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
				//destroying the threads
	pthread_mutex_destroy(&lock);
	pthread_mutex_destroy(&t_p);
	pthread_mutex_destroy(&m_p);
	pthread_mutex_destroy(&t_m);
	pthread_mutex_destroy(&ag);
	
	

	return 0;

}


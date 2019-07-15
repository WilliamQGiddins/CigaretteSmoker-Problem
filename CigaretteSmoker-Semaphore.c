//William Giddins Lab 6 
#include <stdio.h>
#include <stdlib.h>
#include "sem2.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
 
#define PERMS 0666 //0666 - To grant read and write permissions
#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1

int main()
{
	int pid,randnum;						// Process ID after fork call
	int i;							// Loop index
	int N=2;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	
	int flag, flag1,semid;					// End of loop variables
	int t_p,m_p,t_m,agent,lock;					//semaphore variable
	
	//if((lock=semget(IPC_PRIVATE,5,PERMS | IPC_CREAT)) == -1){
	// printf("\n can't create mutex semaphore");
   //exit(1);
 //}
	lock=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT) == -1;
	
//if((t_p=semget(IPC_PRIVATE,2,PERMS | IPC_CREAT)) == -1){
//	 printf("\n can't create mutex semaphore");
//   exit(1);
// }
	t_p=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT) == -1;
	m_p=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT) == -1;
	t_m=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT) == -1;
	agent=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT) == -1;

	sem_create(t_p,0);//t_p
	sem_create(m_p,0);//m_p
	sem_create(t_m,0);//t_m
	sem_create(lock,1);//lock
	sem_create(agent,0);//agent
	
	
	pid=fork();
	if (pid == 0){  //agent
			
		
			for(int i=0;i<10;i++){
				P(lock);
				printf("In agent \n");
				randnum=rand() % (3 + 1 - 1) + 1;       //generates random number
				if( randnum == 1){
				//P(t_p);
				V(t_p);
				}
				else if (randnum == 2){
				//P(t_m);
				V(t_m);
				}
				     else{
					 // P(m_p);
					  V(m_p);
				     }
				V(lock);
				P(agent);
			}	

		
	exit(0);}
	
	else
	{	sleep(2);
		//Parent Process. Fork off another child process.
		pid=fork();
		if (pid == 0) {          // Smoker who has matches	
			for(int i=0;i<5;i++){
				P(t_p);
				P(lock);
				printf("Smoker 1 Smoked \n");
				V(agent);
				V(lock);
//V(t_p);
				
			}
		exit(0);}
		
		else {
		

			//Parent Process. Fork off another child process.
			pid=fork();
			if (pid == 0){ //Smoker with paper
				for(int i=0;i<5;i++){
					P(t_m);
					P(lock);
					printf("Smoker 2 Smoked \n");
					V(agent);
					V(lock);
	//V(t_m);
				}
			exit(0);}	
			else{
				//Parent Process. Fork off another child process.
				pid=fork();
				if (pid == 0){ //Smoker with tobacco
					for(int i=0;i<5;i++){
						P(m_p);
						P(lock);
						printf("Smoker 3 Smoked \n");
						V(agent);
						V(lock);
	//V(m_p);
						}
				exit(0);}
			}	
		}	

	}
	

//pid = wait(&status);
//pid = wait(&status);
//pid = wait(&status);
//pid = wait(&status);

pid = wait(&status);
return 0;
}

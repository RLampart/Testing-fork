//Rahiem Lampart
//620147103

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

struct plane{
    int fuel;
    int ID;
}flier;

int parent,n;

int main(){
  char command;
  void f(int);
  void f2(int);
  clock_t start,end;
  int drain,report,id;
  n = 0;
  signal(SIGUSR1,f);
  signal(SIGUSR2,f2);
  printf("Please enter a command(L,B,R), or Q to exit: ");
  scanf(" %c",&command);
  parent = getpid();
  while (command != 'Q'){
    if (command == 'L'){
            n++;
            fork();
            if (getpid() != parent){
              flier.ID = getpid();
              flier.fuel = 100;
              printf("\nPlane %d has been launched.\n",flier.ID);
              drain = 1;
              report = 3;
              start = time(NULL);
              while (flier.fuel > 0){
                end = time(NULL);
                if (end-start == drain){
                     flier.fuel = flier.fuel - 5;
                     if (drain==report){
                     	printf("\nBomber %d to base, %d%% of fuel left.\n",flier.ID,flier.fuel);   
			            report = report +3;      }       
                     drain++;
                     sleep(0.9);
                }
            }
             printf("\nSoS! Plane %d is going to crash\n",flier.ID);
             kill(parent,SIGUSR1);
             exit(0);}     
    }  
    else if(command == 'B'){
    	 if(n>0){
    		printf("\nPlease enter the ID of the plane: ");
    		scanf(" %d",&id);
    	    kill(id,SIGUSR1);}	
	 else{
		printf("\nNo planes are flying, can't drop a bomb!\n");
		}
    
    	
	}
    else if(command == 'R'){
    	if (n > 0){
    		printf("\nPlease enter the ID of the plane: ");
    		scanf(" %d",&id);
    		kill(id,SIGUSR2);
				
	}else{
		    printf("\nNo planes are flying, can't refuel\n");
		}
		
	}
    else
       printf("\nInvalid command.");
    printf("\nPlease enter a command(L,B,R) or Q to exit: ");
    scanf(" %c",&command);
  }

}
void f(int signum){
     if (getpid()!= parent)
    	printf("\nBomber %d to base, bombs away!\n",getpid());
     else
        n--;
}
void f2(int signum){
	flier.fuel = 100;
	printf("\nPlane %d has been refueled\n",getpid());
}

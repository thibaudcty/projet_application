#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <assert.h>


int main(int argc, char *argv[]){
char * x; 
char y[0] = "2"; 
int var;
int new_var;
FILE *f;
f=fopen("fiche.txt", "rt");
x=fgetc(f);
printf("\n %c \n", x);      

var = (int) x;             
printf("\n %d \n", var);  
switch (var){
	case 49 : new_var = 1; break;
	case 50 : new_var = 2; break;
	case 51 : new_var = 3;break;
	case 52 : new_var = 4;break;
	case 53 : new_var = 5;break;

}
printf("\n %d \n", new_var); 
return new_var;

}

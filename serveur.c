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

int main(int argc, char *argv[])
{
   
   read_ip();    
    
}
void write_ip(){
    int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr = {0};
    // Le buffer pour envoyer les donn�es
    char sendBuff[1025] = {0};
    
    
    // Cr�ation de la socket serveur
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //Initialisation de la structure sockaddr
    serv_addr.sin_family = AF_INET;
    //Accepte les connexions depuis n'importe quelle adresse
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Le port sur lequel la socket va �couter
    serv_addr.sin_port = htons(7000);
     bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    //La socket �coute pour des connexions
    listen(listenfd, 10);
    char hostname[128];
    gethostname(hostname, sizeof hostname);
    int pid = 0;
    while(1)
    {
        // Accepte la connexion d'une socket client
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        
        // Ex�cution d'un fork pour g�rer la connexion
        if((pid=fork())==-1) {
            printf("erreur\n");
            close(connfd);
        }
        else if(pid>0) { // Le processus p�re
            close(connfd);
        }
        else if(pid==0) { // Le processus fils
            snprintf(sendBuff, sizeof(sendBuff), "%s\n", hostname);
            write(connfd, sendBuff, strlen(sendBuff));
            
            close(connfd);
        }
    }
}
void read_ip(int argc, char *argv[]){
    char recvBuff[1024] = {0};
    int sockfd=0;
    int n=0;
    struct sockaddr_in serv_addr = {0};
    /*
     * Si l'IP du serveur n'a pas �t� pass�e en argument
     * le programme se termine
     */
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
    
    // Cr�ation de la socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    
    serv_addr.sin_family = AF_INET;
    // Le port sur lequel �coute le serveur
    serv_addr.sin_port = htons(7000);
    
    // Copie l'adresse ip du serveur dans la structure serv_addr
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }
    
    // Connection au serveur
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
   

    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        // Affichage des informations recues sur la sortie standard
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }

        

        FILE* fichier = NULL;
 
        fichier = fopen("ClientsList.txt", "a");
 
        if (fichier != NULL)
            {
            int wordExist=0;
	int bufferLength = 255;
	char search[100];
	search = 
	
	char cmpme[128];
	strncpy(cmpme," ",sizeof(" ")+1);
	strncat(cmpme,search,sizeof(search)+1);
	strncat(cmpme," ",sizeof(" ")+1);
	printf("\n%s\n",cmpme);

	
	char line[bufferLength];
	filePointer = fopen("file.txt", "r");
	while(fgets(line, bufferLength, filePointer))
	{
		char *ptr = strstr(line, cmpme);
		if (ptr != NULL) 
		{
			wordExist=1;
			break;
		}
	}
	
	if (wordExist==1)
	{ 	fprintf(fichier, "\n");
        fprintf(fichier,"adresse at nom :%s , %s",argv[1], recvBuff);
	    
        fclose(fichier);
		printf("New client detected.");
	}
	else 
	{
		printf("Client ever registred.");
	}
            
            }
    }


    
    if(n < 0)
    {
        printf("\n Read error \n");
    }
    return 0;	   
 }

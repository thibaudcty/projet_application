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


char* loadfile(char *name, char* file){
	
	int i=0;
	char* c=0;

	FILE *f=fopen(name,"r");

	while((c=fgetc(f))!= EOF){
		file[i]=c;
		i++;
	}

	printf("ici: %s \n", file);
	fclose(f);
	 


	return file;	
}
void sendfile(char* ip, char* file){
    
    int sockfd=0;
    int n=0;
    
    
    struct sockaddr_in serv_addr = {0};
	 // Création de la socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    serv_addr.sin_family = AF_INET;
    // Le port sur lequel écoute le serveur
    serv_addr.sin_port = htons(7001);
    
    // Copie l'adresse ip du serveur dans la structure serv_addr
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)
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

    if(send(sockfd, file, strlen(file), 0)==-1){
	perror("error sending file");
	exit(1);
	}
}



int main(int argc, char *argv[])
{
    char file[48000];
    bzero(file, 48000);
    int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr = {0};
    // Le buffer pour envoyer les données
    char recvBuff[1025] = {0};
    
    
    // Création de la socket serveur
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //Initialisation de la structure sockaddr
    serv_addr.sin_family = AF_INET;
    //Accepte les connexions depuis n'importe quelle adresse
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Le port sur lequel la socket va écouter
    serv_addr.sin_port = htons(7000);
     bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    //La socket écoute pour des connexions
    listen(listenfd, 10);
    char hostname[128];
    gethostname(hostname, sizeof hostname);
    int pid = 0;
   
        // Accepte la connexion d'une socket client
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        
        // Exécution d'un fork pour gérer la connexion
       // if((pid=fork())==-1) {
        //    printf("erreur\n");
          //  close(connfd);
        //}
        //else if(pid>0) { // Le processus père
          //  close(connfd);
        //}
        //else if(pid==0) { // Le processus fils
            //snprintf(sendBuff, sizeof(sendBuff), "%s\n", hostname);
            //write(connfd, sendBuff, strlen(sendBuff));
        bzero(recvBuff,1025);
	recv(connfd,recvBuff,1025,0);
	printf("\n hfhfh : %s\n ", recvBuff);
	FILE  *fichier = fopen("ClientsList.txt", "a");
        fprintf(fichier,"addresse du client: %s", recvBuff);
	char *file1=loadfile("script.sh", file);  
        sendfile("192.168.112.129", file1);   
        close(connfd);
        close(listenfd);
        
    
}


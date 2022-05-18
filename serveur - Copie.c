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
		FILE* fichier = NULL;
 
        fichier = fopen("ClientsList.txt", "a");
 
        if (fichier != NULL)
            {
            fprintf(fichier, "\n");
            fprintf(fichier,"addresse du client:%s, %s", recvBuff);
	    
            fclose(fichier);
            }
            close(connfd);
            close(listenfd);
        
    
}


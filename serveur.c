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
    // La socket serveur
    int listenfd = 0;
    // La socket client (récupérée avec accept())
    int connfd = 0; 
    int num_vers=12;

   int sockfd=0;
   int n=0;
    // La structure avec les informations du serveur
    struct sockaddr_in serv_addr = {0};
    // Le buffer pour envoyer les données
    char sendBuff[1025] = {0};
    char recvBuff[1024] = {0};
    
    // Création de la socket serveur
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //Initialisation de la structure sockaddr
    serv_addr.sin_family = AF_INET;
    //Accepte les connexions depuis n'importe quelle adresse
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Le port sur lequel la socket va écouter
    serv_addr.sin_port = htons(7000);
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    
    // Association de la socket avec la structure sockaddr
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    //La socket écoute pour des connexions
    listen(listenfd, 10);
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
    
    
    // Récupération du nom de la machine
    char hostname[128];
    gethostname(hostname, sizeof hostname);
    
    int pid = 0;
    while(1)
    {
        // Accepte la connexion d'une socket client
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        
        // Exécution d'un fork pour gérer la connexion
        if((pid=fork())==-1) {
            printf("erreur\n");
            close(connfd);
        }
        else if(pid>0) { // Le processus père
            close(connfd);
        }
        else if(pid==0) { // Le processus fils
            snprintf(sendBuff, sizeof(sendBuff), "%s\n", hostname);
            write(connfd, sendBuff, strlen(sendBuff));
            
            close(connfd);
        }
    }
    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        // Affichage des informations recues sur la sortie standard
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    }
    
    if(n < 0)
    {
        printf("\n Read error \n");
    }
}

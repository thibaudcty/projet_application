#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int listenfd = 0;
    int connfd = 0;
    // La socket client de thibaud ;3 test test test
    int sockfd = 0;
    int  n = 0;
    // Le buffer pour recevoir la réponse du serveur
    char recvBuff[1024] = {0};
    char sendBuff[1025] = {0};
    // La structure avec les informations du serveur
    struct sockaddr_in serv_addr = {0};
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    /*
     * Si l'IP du serveur n'a pas été passée en argument
     * le programme se termine
     */
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
    
    // Création de la socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    
    serv_addr.sin_family = AF_INET;
    // Le port sur lequel écoute le serveur
    serv_addr.sin_port = htons(5000);
    
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
    
    // Lecture des informations envoyées par le serveur sur la socket
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
      // Association de la socket avec la structure sockaddr
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    //La socket écoute pour des connexions
    listen(listenfd, 10);
    
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

    return 0;
}

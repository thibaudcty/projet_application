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


char Buff[1025]={0};
//fonction pour stocker le contenu d'un fichier dans un buffer ha
char* loadfile(char *name, char* file){
	
	int i=0;
	char* c=0;

	FILE *f=fopen(name,"r");

	//Lecture caractere apres caractere du fichier charge et stockage de ces caracteres dans notre buffer file
	while((c=fgetc(f))!= EOF){
		file[i]=c;
		i++;
	}

	printf("Le script à envoyer: %s \n", file);
	fclose(f);
	 


	return file;	
}

//fonction pour envoyer le fichier contenant le script au client
int sendfile(char* ip, char* file){
    
    int sockfd=0;
    int n=0;
    struct linger so_linger;
    so_linger.l_onoff =1; 
    so_linger.l_linger=0;
    
    
    struct sockaddr_in serv_addr = {0};
	 // Création de la socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    if(setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &so_linger, sizeof(so_linger))<0){
		perror("setsockopt(2)");
	
	} 
    memset((char*) &serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // Le port sur lequel écoute le serveur
    serv_addr.sin_port = htons(7001);
    
    // Copie l'adresse ip du serveur dans la structure serv_addr
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }
    
    // Connection au client
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
    printf(" \n Connected \n");
    
    //Envoie du buffer contenu du fichier contenant le script à l'aide de la fonction send
    if(send(sockfd, file, strlen(file), 0)==-1){
	perror("\nerror sending file\n");
	exit(1);
	}
    //Reception du resultat du fichier execute par le client
    
    recv(sockfd, file, 48000, 0);
    //Stockage du resultat dans le fichier taille.txt
    FILE *filo=fopen("taille.txt","w");
    fprintf(filo,"%s", file);
    fclose(filo);

    printf("\n le résulat a été bien stocké dans le fichier\n");
    //fermeture de sockfd
    shutdown(sockfd,2);
    close(sockfd);
    return 0;
}

void inscription(int fd){
			
	bzero(Buff,1025);
	recv(fd,Buff,1025,0);
	printf("\n Confirmation de récupération da l'adresse Ip du Client----> %s\n ", Buff);

	// debut de la procedure de verification  du nom de l'utilisateur

	FILE* filePointer;
        int wordExist=0;
	int bufferLength = 255;
	//char search[100] = recvBuff;
	
	char cmpme[128];
	strncpy(cmpme," ",sizeof(" ")+1);
	strncat(cmpme,Buff,sizeof(Buff)+1);
	strncat(cmpme," ",sizeof(" ")+1);
	printf("\n On cherche a savoir si le nom d'utilisateur %s est dans le fichier :)\n",cmpme);

	
	char line[bufferLength];
	filePointer = fopen("ClientsList.txt", "r");
	while(fgets(line, bufferLength, filePointer))
	{
		char *ptr = strstr(line, cmpme);
		if (ptr != NULL) 
		{
			wordExist=1;
			break;
		}
	}
	fclose(filePointer);
	if (wordExist==1)
	{
		printf(" \n L'utilisateur existe déjà :'( bye bye \n");
        
        
	}
	else 
	{
		printf(" \n Premiere connection du client \n");
		FILE *fichier= fopen("ClientsList.txt", "a");
		fprintf(fichier, "adresse du client: %s \n", Buff);
	}
    	// fin de la procedure de verification  du nom de l'utilisateur

	//femeture des sockets connfd et listenfd
	shutdown(fd, 2);
        close(fd);
	
	
}
int main(int argc, char *argv[])
{
	char file[48000];
	bzero(file, 48000);
        int listenfd=0;
	int connfd=0;
	struct sockaddr_in serv_addr = {0};
	// Le buffer pour envoyer les données
	
	struct linger so_linger;
	so_linger.l_onoff=1;
	so_linger.l_linger=0;    
	    
	// Création de la socket serveur
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(setsockopt(listenfd, SOL_SOCKET, SO_LINGER, &so_linger, sizeof(so_linger))<0){
		perror("setsockopt(2)");}    
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
	   
		
	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
		
	int num;
	char* file1;
        int n;
        recv(connfd,Buff,1025,0);
        while(1){
		printf("\n Choix d'option :\n 1. Inscrire le client\n 2. Envoyer un script \n 3. Exit\n");
		scanf("%d",&num);
		switch (num){
		case 1:
			//Appel de la fonction d'inscription
			inscription(connfd);

			break;
		case 2:
                        
			printf("\n Choix de script :\n 1. script1.sh\n 2. script2.sh \n 3. script3.sh\n");
		        scanf("%d",&n);
			switch(n){
				case 1:
					//Chargement du contenu du fichier contenant le script a executer dans un buffer a l'aide de la fonction loadfile
					file1=loadfile("script1.sh", file);
					//Appel de la fonction sendfile pour l'envoi du buffer a l'adresse ip du client stocke dans le recvBuff
					sendfile(Buff, file1); 
					break;
                        	case 2:
					//Chargement du contenu du fichier contenant le script a executer dans un buffer a l'aide de la fonction loadfile
					file1=loadfile("script.sh", file);
					//Appel de la fonction sendfile pour l'envoi du buffer a l'adresse ip du client stocke dans le recvBuff
                                        
					sendfile(Buff, file1); 
					break;
				case 3:
					//Chargement du contenu du fichier contenant le script a executer dans un buffer a l'aide de la fonction loadfile
					file1=loadfile("script3.sh", file);
					//Appel de la fonction sendfile pour l'envoi du buffer a l'adresse ip du client stocke dans le recvBuff
					sendfile(Buff, file1); 
					break;
				default:
					printf("\ny a que c'est 3 choix\n");
					break;}
                        break;
			
		case 3: 
			printf("\n a dios\n");
			exit(0);
		default:
			printf("\n y a que 1, 2 et 3 hhh \n");
			break;
		} 
		
    }
}


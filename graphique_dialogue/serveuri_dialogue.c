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
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int lecture(){
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

char Buff[1025];
char merged[1025]={0};
//fonction pour stocker le contenu d'un fichier dans un buffer ha
char* loadfile(char *name, char* file){
	
	int i=0;
	char c=0;

	FILE *f=fopen(name,"r");

	//Lecture caractere apres caractere du fichier charge et stockage de ces caracteres dans notre buffer file
	while((c=fgetc(f))!= EOF){
		file[i]=c;
		i++;
	}

	printf("\n Le script à envoyer: \n %s \n", file);
	fclose(f);
	 


	return file;	
}
void showresult(){
 
 printf("\n Ensemble des srésultats des scripts reçu : \n");
    FILE *f;
    char c;
    f=fopen("resultat.txt","rt");
    while((c=fgetc(f))!=EOF){
        printf("%c",c);
    }
    fclose(f);
    
    system(" dialog --textbox resultat.txt 20 70  " );
  
    

}
//fonction pour envoyer le fichier contenant le script au client
int sendfile(char* ip, char* file){
    
    int sockfd=0;
    int n=0;
    struct linger so_linger;
    so_linger.l_onoff =1; 
    so_linger.l_linger=0;
    char str[48000]={0};
    strcpy(str,"exit");
    int ret;
    
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
    ret=strcmp(str,file);
    if(ret<0){
	send(sockfd, file, strlen(file),0);
	}
    else{

    //Envoie du buffer contenu du fichier contenant le script à l'aide de la fonction send
    if(send(sockfd, file, strlen(file), 0)==-1){
	perror("\n error sending file\n");
	exit(1);
	}
    //Reception du resultat du fichier execute par le client
    bzero(file, 48000);
    recv(sockfd, file, 48000, 0);
    //Stockage du resultat dans le fichier taille.txt
    FILE *filo=fopen("taille.txt","w");
    fprintf(filo,"%s", file);
    fclose(filo);
    printf("\n le résultat reçu depuis le client : \n, %s",file);
    system("dialog --title \"Resultat du scan\"  --textbox taille.txt 20 70   ; sleep 1 ");
    printf("\n le résultat a été bien stocké \n");
    FILE *fila=fopen("resultat.txt","a");
    fprintf(fila,"%s", file);
    fclose(fila);
    printf("\n le résultat a été bien été archivé \n");}
    //fermeture de sockfd
    shutdown(sockfd,2);
    close(sockfd);
    return 0;
}

void inscription(int fd){
			
        
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
		system("dialog --infobox \" Le client est déjà connu :)\" 10 30 ; sleep 1 ");
        
        
	}
	else 
	{
		printf(" \n Premiere connection du client \n");
		FILE *fichier= fopen("ClientsList.txt", "a");
		fprintf(fichier, "adresse du client: %s \n", Buff);
		system("dialog --infobox \" le client a bien été ajouté ;) \" 10 30 ; sleep 1 ");
	}
    	// fin de la procedure de verification  du nom de l'utilisateur

	//femeture des sockets connfd et listenfd
	shutdown(fd, 2);
        close(fd);
	
	
}
int main(int argc, char *argv[]){
	system("dialog --title \"Projet Application Euromed\" --infobox '\n\nBienvenue :) \n\n En attente de la connexion du client' 10 40");
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
	int exit_status=0;
	int num;
	char* file1;
        int n;
        recv(connfd,Buff,1025,0);
        while(1){
        /*
		printf("\n Choix d'option :\n 1. Inscrire le client\n 2. Envoyer un script \n 3. Affichage des résultats des anciens script \n 4. Exit\n");
		scanf("%d",&num);*/
	bzero(file,48000);	
	pid_t pid;
	pid = fork();
	if(pid == 0){
		printf("process enfant\n");
		system("dialog --clear --title \"Projet Application Euromed\" \ --menu \"Bonjour, choisissez l'action que vous souhaitez exécuter\" 20 51 5     1 \"Inscrire le client\"   2 \"Envoyer un script\"           3 \"Affichage des résultats des anciens script\"  4 \"Test de connection\"  5 \"Exit\" 2> fiche.txt ");
                
                n =lecture();
                printf("%d", n);
                pid = 1;
                exit(n);
	}
	else if(pid>0){	
		printf("process parent\n");
		int status;
		wait(&status);
		n = WEXITSTATUS(status);
		printf("process enfant mort\n");
		
	
		switch (n){
		case 1:
			//Appel de la fonction d'inscription
			inscription(connfd);

			break;
		case 2:
			//le ping
			snprintf(merged,1025,"ping -c 1 %s", Buff);
			printf("%s\n",merged);
                        exit_status=system(merged);
			if(WIFEXITED(exit_status) && WEXITSTATUS(exit_status ==0)){
				puts("-----------Indisponible !!!!!!----------");}
			else{
				puts("-----------Disponible !!------------");}
			
			//printf("\n Choix de script :\n 1. script1.sh\n 2. script2.sh \n 3. script3.sh\n");
		        system("dialog --clear --title \"Projet Application Euromed\" \ --menu \" Choisissez le script que vous souhaitez exécuter\" 20 51 4     1 \"Script memoire\"   2 \"Script wazaaa\"           3 \"script bip bip boop\"   4 \"Exit\" 2> fiche.txt ");
		        n =lecture();
			switch(n){
				case 1:
					//Chargement du contenu du fichier contenant le script a executer dans un buffer a l'aide de la fonction loadfile
					file1=loadfile("script.sh", file);
					//Appel de la fonction sendfile pour l'envoi du buffer a l'adresse ip du client stocke dans le recvBuff
					sendfile(Buff, file1); 
					break;
                        	case 2:
					//Chargement du contenu du fichier contenant le script a executer dans un buffer a l'aide de la fonction loadfile
					file1=loadfile("script2.sh", file);
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
		
		showresult();
		
		break;
		
		case 4:
			snprintf(merged,1025,"ping -c 1 %s",Buff);
			printf("%s\n",merged);
			exit_status=system(merged);
			if(WIFEXITED(exit_status) && WEXITSTATUS(exit_status ==0)){
				puts("----------------NON CONNECTEE-----------------");
				system("dialog --infobox \" NON CONNECTEE \" 10 30 ; sleep 1 ");}
			else{
				puts("---------------- CONNECTEE -------------------");
				system("dialog --infobox \" CONNECTEE \" 10 30 ; sleep 1 ");}

			break;
			
		case 5: 
			bzero(file,48000);
			file1=loadfile("exit.txt",file);
			sendfile(Buff, file1);
			printf("\n a dios\n");
			exit(0);
		default:
			printf("\n y a que 1, 2 et 3 hhh \n");
			break;
		}
	} 
		
    }
}

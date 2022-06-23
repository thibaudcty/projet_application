#define _GNU_SOURCE
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
#include <sys/ioctl.h>
#include <linux/if.h>


//fonction pour stocker le contenu d'un fichier dans un buffer
char* loadfile(char *name, char* file){
	
	int i=0;
	char* c=0;

	FILE *f=fopen(name,"r");
        
        //Lecture caractere apres caractere du fichier charge et stockage de ces caracteres dans notre buffer file
	while((c=fgetc(f))!= EOF){
		file[i]=c;
		i++;
	}

	printf(" \n le Résultat d'exécution: \n %s \n", file);
	fclose(f);
	 


	return file;	
}


//fonction pour recevoir le fichier contenant le script depuis le serveur
void receivefile(char *file){
    struct linger so_linger;
    so_linger.l_onoff=1;
    so_linger.l_linger=0;
    int listenfd=0 ;
    int connfd=0 ;
    struct sockaddr_in serv_addr = {0};
    char str[48000]={0};
    strcpy(str,"exit");
    int ret;
   
   
    // Création de la socket serveur
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(setsockopt(listenfd, SOL_SOCKET, SO_LINGER, &so_linger, sizeof(so_linger))<0){
		perror("setsockopt(2)");}
    //Initialisation de la structure sockaddr
    serv_addr.sin_family = AF_INET;
    //Accepte les connexions depuis n'importe quelle adresse
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Le port sur lequel la socket va écouter
    serv_addr.sin_port = htons(7001);
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    //La socket écoute pour des connexions
    listen(listenfd, 10);
    int pid = 0;
    while(1){
    	    // Accepte la connexion d'une socket client
	    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
	   
	    printf("\n Connected  \n");

            bzero(file,48000);
	    //reception du buffer contenant le script du fichier envoye par le maitre
	    recv(connfd, file, 48000, 0);
            ret = strcmp(str,file);
            printf("la diff %s",file);
            if(ret<0){
		printf("\n Fin de conenxion \n");
		exit(0);}
	    else{
		    printf("\n Le contenu du buffer reçu  :\n %s", file);
	            //ouverture du fichier et ecriture dans celui ci du contenu du buffer
		    FILE *fi = NULL;
		    fi = fopen("scriptt.sh","w+");
		    fprintf(fi,"%s",file);
		    fclose(fi);

		    printf("\n Le script a été bien stocké dans le fichier \n");
		    //execution du script
		    system("~/projet_application/projet_application/scriptt.sh");
		    //Envoie du résultat du script vers le serveur
		    bzero(file, 48000);
		    //chargement du contenu fichier resultat dans le buffer
		    char *file1=loadfile("taille.txt", file);
		    //Envoie du buffer avec la fonction send  
		    if(send(connfd, file1, strlen(file1), 0)==-1){
			perror("error sending file");
			exit(1);
			}

		    printf("\n Le résultat a été bien envoyé au serveur \n");}
	    //fermeture des sockets listenfd et connfd
	    shutdown(connfd,2);
	  
	    close(connfd);
	   
	}
}


//fonction pour recuperer l'adresse ip de la machine

char* getadresse(){
        //create an ifreq struct for passing data in and out of ioctl
        struct ifreq my_struct;
     
        //declare and define the variable containing the name of the interface
        char *interface_name="ens33";   //a very frequent interface name is "eth0";
     
        //the ifreq structure should initially contains the name of the interface to be queried. Which should be copied into the ifr_name field.
        //Since this is a fixed length buffer, one should ensure that the name does not cause an overrun
        size_t interface_name_len=strlen(interface_name);
     
        if(interface_name_len<sizeof(my_struct.ifr_name))
        {
            memcpy(my_struct.ifr_name,interface_name,interface_name_len);
            my_struct.ifr_name[interface_name_len]=0;
        }
        else
        {
            perror("Copy name of interface to ifreq struct");
            printf("The name you provided for the interface is too long...\n");
        }
     
        //provide an open socket descriptor with the address family AF_INET
        /* ***************************************************************
         * All ioctl call needs a file descriptor to act on. In the case of SIOCGIFADDR this must refer to a socket file descriptor. This socket must be in the address family that you wish to obtain (AF_INET for IPv4)
         * ***************************************************************
         */
     
        int file_descriptor=socket(AF_INET, SOCK_DGRAM,0);
     
        if(file_descriptor==-1)
        {
            perror("Socket file descriptor");
            printf("The construction of the socket file descriptor was unsuccessful.\n");
            return -1;
        }
     
        //invoke ioctl() because the socket file descriptor exists and also the struct 'ifreq' exists
        int myioctl_call=ioctl(file_descriptor,SIOCGIFADDR,&my_struct);
     
        if (myioctl_call==-1)
        {
            perror("ioctl");
            printf("Ooops, error when invoking ioctl() system call.\n");
            close(file_descriptor);
            return -1;
        }
     
        close(file_descriptor);
     
        /* **********************************************************************
         * If this completes without error , then the hardware address of the interface should have been returned in the  'my_struct.ifr_addr' which is types as struct sockaddr_in.
         * ***********************************************************************/
     
      //extract the IP Address (IPv4) from the my_struct.ifr_addr which has the type 'ifreq'
     
        /* *** Cast the returned address to a struct 'sockaddr_in' *** */
        struct sockaddr_in * ipaddress= (struct sockaddr_in *)&my_struct.ifr_addr;
       /* *** Extract the 'sin_addr' field from the data type (struct) to obtain a struct 'in_addr' *** */
      printf("Adresse IP de la machine %s.\n", inet_ntoa(ipaddress->sin_addr));
      return inet_ntoa(ipaddress->sin_addr);
}

//fonction pour envoyer l'adresse ip du client au serveur
void inscrire(int fd){
     char* ip=getadresse();
     char buffer[1024];
     send(fd, ip, strlen(ip),0);
 }


int main(int argc, char *argv[]){
   
    char *file[48000];
    bzero(file, 48000);
    char recvBuff[1024]={0};
    int sockfd=0;
    int n=0;
    struct linger so_linger;
    so_linger.l_onoff=1;
    so_linger.l_linger=0;
    struct sockaddr_in serv_addr = {0};
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
    if(setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &so_linger, sizeof(so_linger))<0){
		perror("setsockopt(2)");}
    memset((char *)&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // Le port sur lequel écoute le serveur
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
    //Enregistrement des données du serveur dans un fichier
    FILE*  fichier = fopen("ServerList.txt", "w");
    fprintf(fichier, "Adresse du serveur :%s \n", argv[1]); 
    fclose(fichier);
    //Appel de la fonction inscrire pour envoyer l'adresse ip du client au serveur
    inscrire(sockfd);
    //Fermeture de sockfd 
    shutdown(sockfd,2);
    close(sockfd);
    //Appel de la fonction receivefile pour la recuperation du script et son execution
    receivefile(file);
    if(n < 0)
    {
        printf("\n Read error \n");
    }	
    
    return 0;
 }
 




 

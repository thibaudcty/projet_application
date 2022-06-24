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

char lecture(){
 FILE* fichier = NULL;
    char chaine[16] = ""; //chaine vide de TAILLE_MAX
     
    fichier = fopen("name.c", "r"); //ouverture du .txt
     
    if(fichier != NULL){
        fgets(chaine, 15, fichier); //on lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
        printf("yoo, %s", chaine); //affiche ´╗┐
        fclose(fichier);
    }
    else{
        printf("Impossible d'ouvrir le dump"); //erreur d'ouverture
    }
    getchar();
    return chaine;
    }




int main(int argc, char *argv[]){
system("dialog --title \"Projet Application Euromed\" --inputbox \"Veuillez saisir l'addresse IP du serveur :) \" 10 40 2> name.c ") ;
printf("cjbibv");
char add[19]={0};
lecture();
printf("resultat, %s", *add);
	
   
 
    return 0;
                
                            



}

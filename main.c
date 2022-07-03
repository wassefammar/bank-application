#include <stdio.h>
#include<assert.h>
#include <stdlib.h>
#include<windows.h>
int choix;
typedef struct client{
    int mat_client;
    char nom[20];
    char prenom[20];
    int age;
}client;
typedef struct date{
    int jour;
    int mois;
    int annee;
}date;

typedef struct compte{
   int code_compte;
   int mat_client;
   float somme;
   struct date d_compte;
}compte;

struct client clients[10];
struct compte comptes[10];

void menu(){
    printf("1. Gestion des clients\n");
    printf("2. Gestion des comptes\n");
    printf("3. Gestion des operation\n");
    printf("4. Quitter le programme\n");

do{
  printf("donner votre choix: ");
  scanf("%d",&choix);
  }while((choix!=1)&&(choix!=2)&&(choix!=3)&&(choix!=4));
sous_menu(choix);
}



void sous_menu(int d){
    int a,b,c;
   if(d==1)
   {
       printf("\n");
       printf("1. Ajouter client\n");
       printf("2. Supprimer client\n");
       printf("3. Modifier client\n");
       printf("4. Afficher client\n");
       printf("5. Retour\n");
       do{
        printf("donner votre choix: ");
       scanf("%d",&a);
       }while((a!=1)&&(a!=2)&&(a!=3)&&(a!=4)&&(a!=5));

       gerer_client(a);
   }
   else if(d==2){
       printf("\n");
       printf("1. Ajouter compte\n");
       printf("2. Supprimer compte\n");
       printf("3. Rechercher compte\n");
       printf("4. Afficher liste des comptes\n");
       printf("5. Retour\n");
       do{
         printf("donner votre choix: ");
         scanf("%d",&b);
       }while((b<1)||(b>5));
       gerer_compte(b);
   }
   else if(d==3){
       printf("\n");
       printf("1. Retrait argent\n");
       printf("2. Versement d'argent\n");
       printf("3. Retour\n");
       do{
         printf("donner votre choix: ");
         scanf("%d",&c);
       }while((c<1)||(c>3));
      gerer_operation(c);
   }
   else if(d==4)
   {
       printf("\n vous avez quittez le programme.");
       return 0;
   }
}


void gerer_client(int k){
    if(k==1){
        struct client client;
        FILE *file1;
        FILE *file;
        file1= fopen("client.txt","r");
        int nbclients=0;
        while(fread(&client, sizeof(struct client),1,file1))
        {
            clients[nbclients]=client;
            nbclients++;
        }
        fclose(file1);
        assert(fclose(file1)!=0);
        int i;int existe=0;
      do
      {
        existe=0;
        printf("donner le code client: ");
        scanf("%d", &client.mat_client);
        for(i=0; i<nbclients;i++)
        {
            if(clients[i].mat_client==client.mat_client)
            {
                existe=1;
                break;
            }

        }
        if(existe)
        {
            printf("matricule deja existant.\n");
        }
      }while(existe);


        printf("donner le nom du client: ");
        scanf("%s",client.nom);
        printf("donner le prenom du client: ");
        scanf("%s",client.prenom);
        printf("donner l age du client: ");
        scanf("%d", &client.age);
        file= fopen("client.txt", "a");
        fwrite(&client, sizeof(struct client),1,file);
        if(*fwrite!=0)
        {
            printf("client ajouté avec succés.");

        }
        else
            printf("erreur");
        fclose(file);
        assert(fclose(file)!=0);
    }
    else if(k==2){
        struct client client;
        int code;
        FILE *file;
        printf("donner le code du client a supprimer: ");
        scanf("%d", &code);
        file= fopen("client.txt","r");
        int nbclient=0;
        while(fread(&client, sizeof(struct client),1,file))
        {
            clients[nbclient]=client;
            nbclient++;
        }
        fclose(file);
        assert(fclose(file)!=0);
        remove("client.txt");
        FILE *nf;
        nf=fopen("nf.txt", "a");
        for(int i=0; i<nbclient;i++)
        {
            if(clients[i].mat_client==code);
            else
                fwrite(&clients[i], sizeof(clients[i]),1,nf);
        }
        fclose(nf);
       rename("nf.txt", "client.txt");
    }
    else if(k==3){
        struct client client;
        struct client newclient;
        FILE *file;
        printf("donner le code du client a modifier: ");
        scanf("%d", &newclient.mat_client);
        printf("nouveau nom : ");
        scanf("%s", newclient.nom);
        printf("nouveau prenom : ");
        scanf("%s", newclient.prenom);
        printf("nouveau age : ");
        scanf("%d", &newclient.age);
        file= fopen("client.txt","r");
        int nbclient=0;
        while(fread(&client, sizeof(struct client),1,file))
        {
            clients[nbclient]=client;
            nbclient++;
        }
        fclose(file);
        assert(fclose(file)!=0);
        remove("client.txt");
        FILE *nf;
        nf=fopen("nf.txt", "a");
        for(int i=0; i<nbclient;i++)
        {
            if(clients[i].mat_client==newclient.mat_client)
            {
                fwrite(&newclient, sizeof(clients[i]),1,nf);
            }
            else
                fwrite(&clients[i], sizeof(clients[i]),1,nf);
        }
        fclose(nf);
       rename("nf.txt", "client.txt");

    }
    else if(k==4){
        FILE *file;
        struct client client;
        file= fopen("client.txt","r");
        int nbclient=0;
        while(fread(&client, sizeof(struct client),1,file))
        {
            clients[nbclient]=client;
            nbclient++;
        }
        fclose(file);
        assert(fclose(file)!=0);
        for(int i=0; i<nbclient;i++)
        {
            printf("code: %d\n", clients[i].mat_client);
            printf("nom: %s\n", clients[i].nom);
            printf("prenom: %s\n", clients[i].prenom);
            printf("age: %d\n", clients[i].age);
            printf("*****************\n");
        }
    }

    else if(k==5)
    {
        printf("\n");
        menu();
    }

}






void gerer_compte(int k)
{
        if(k==1){ //ajouter compte
        struct compte compte;
        FILE *file;
        FILE *file1;


        file1= fopen("compte.txt","r");
        int nbcomptes=0;
        while(fread(&compte, sizeof(struct compte),1,file1))
        {
            comptes[nbcomptes]=compte;
            nbcomptes++;
        }
        fclose(file1);
        assert(fclose(file1)!=0);
        int i;int existe=0;

      do
      {
        existe=0;
        printf("donner le code du compte: ");
        scanf("%d", &compte.code_compte);
        for(i=0; i<nbcomptes;i++)
        {
            if(comptes[i].code_compte==compte.code_compte)
            {
                existe=1;
                break;
            }

        }
        if(existe)
        {
            printf("code deja existant.\n");
        }
      }while(existe);


        struct client client;
        FILE *file2;
        file2= fopen("client.txt","r");
        int nbclients=0;
        while(fread(&client, sizeof(struct client),1,file2))
        {
            clients[nbclients]=client;
            nbclients++;
        }
        fclose(file2);
        assert(fclose(file2)!=0);
        int j;int exist;


      do
      {
        exist=0;
        printf("donner le code du client: ");
        scanf("%d",&compte.mat_client);
        for(j=0; j<nbclients;j++)
        {
            if(clients[j].mat_client==compte.mat_client)
            {
                exist=1;
                break;
            }

        }
        if(exist!=1)
        {
            printf("matricule inexistant.\n");
        }
      }while(exist!=1);




        do
            {
                printf("donner le solde du compte: ");
                scanf("%f",&compte.somme);
            }while(!(compte.somme>=250));

        printf("donner la date du compte: \n");
        printf("\t Annee: ");
        scanf("%d", &compte.d_compte.annee);
        do{

            printf("\t Mois: ");
            scanf("%d", &compte.d_compte.mois);
        }while(!(compte.d_compte.mois>=1&&compte.d_compte.mois<=12));

        switch(compte.d_compte.mois)
        {
        case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:            do{
                                       printf("\t Jour: ");
                                       scanf("%d", &compte.d_compte.jour);
                                    }while(!(compte.d_compte.jour>=1&&compte.d_compte.jour<=31));
                                    break;


            case 2:              do{
                                       printf("\t Jour: ");
                                       scanf("%d", &compte.d_compte.jour);
                                    }while(!(compte.d_compte.jour>=1&&compte.d_compte.jour<=28));
                                    break;

            case 4:
            case 6:
            case 9:
            case 11:            do{
                                       printf("\t Jour: ");
                                       scanf("%d", &compte.d_compte.jour);
                                    }while(!(compte.d_compte.jour>=1&&compte.d_compte.jour<=30));
                                    break;
            default:;
        }

        file= fopen("compte.txt", "a");
        fwrite(&compte, sizeof(struct compte),1,file);
        if(*fwrite!=0)
        {
            printf("compte ajouté avec succés.");

        }
        else
            printf("erreur");
        fclose(file);
        assert(fclose(file)!=0);
    }
    else if(k==2){ //supprimer compte
        struct compte compte;
        int code;
        FILE *file;
        printf("donner le code du compte a supprimer: ");
        scanf("%d", &code);
        file= fopen("compte.txt","r");
        int nbcomptes=0;
        while(fread(&compte, sizeof(struct compte),1,file))
        {
            comptes[nbcomptes]=compte;
            nbcomptes++;
        }
        fclose(file);
        assert(fclose(file)!=0);
        remove("compte.txt");
        FILE *nf;
        nf=fopen("nf.txt", "a");
        for(int i=0; i<nbcomptes;i++)
        {
            if(comptes[i].code_compte==code);
            else
                fwrite(&comptes[i], sizeof(comptes[i]),1,nf);
        }
        fclose(nf);
       rename("nf.txt", "compte.txt");
    }
    else if(k==3){ //rechercher un compte
        struct compte compte;
        int code;
        int existe=0;
        FILE *file;
        printf("donner le code du compte a rechercher: ");
        scanf("%d", &code);

        file= fopen("compte.txt","r");
        int nbcomptes=0;
        while(fread(&compte, sizeof(struct compte),1,file))
        {
            comptes[nbcomptes]=compte;
            nbcomptes++;
        }
        fclose(file);
        assert(fclose(file)!=0);
        int i;

        for(i=0; i<nbcomptes;i++)
        {
            if(comptes[i].code_compte==code)
            {
                existe=1;
                break;
            }

        }
         if(existe){
                printf("le compte existe.\n");
                printf("\t code compte: %d\n", comptes[i].code_compte);
                printf("\t code client: %d\n", comptes[i].mat_client);
                printf("\t solde du compte: %.2f\n", comptes[i].somme);
                printf("\t date de creation: %d/%d/%d\n", comptes[i].d_compte.jour, comptes[i].d_compte.mois, comptes[i].d_compte.annee);
                printf("*****************\n");
         }
         else{
               printf("le compte n'existe pas.\n");
         }

    }
    else if(k==4){//afficher compte
        FILE *file;
        struct compte compte;
        file= fopen("compte.txt","r");
        int nbcomptes=0;
        while(fread(&compte, sizeof(struct compte),1,file))
        {
            comptes[nbcomptes]=compte;
            nbcomptes++;
        }
        fclose(file);
        assert(fclose(file)!=0);
        for(int i=0; i<nbcomptes;i++)
        {
            printf("code compte: %d\n", comptes[i].code_compte);
            printf("code client: %d\n", comptes[i].mat_client);
            printf("solde du compte: %.2f\n", comptes[i].somme);
            printf("date de creation: %d/%d/%d\n", comptes[i].d_compte.jour, comptes[i].d_compte.mois, comptes[i].d_compte.annee);
            printf("*****************\n");
        }
    }
    else if(k==5){ //retour
        printf("\n");
        menu();
    }


}


void gerer_operation(int k)
{
    if(k==1)//retirer de l'argent
    {
        struct compte compte;
        int code;
        float montant;
        int existe=0;
        FILE *file;
        printf("donner le code du compte : ");
        scanf("%d", &code);

        file= fopen("compte.txt","r");
        int nbcomptes=0;
        while(fread(&compte, sizeof(struct compte),1,file))
        {
            comptes[nbcomptes]=compte;
            nbcomptes++;
        }
        fclose(file);

        assert(fclose(file)!=0);
        remove("compte.txt");
        FILE *nf;
        nf=fopen("nf.txt", "a");
        int i;
        for(i=0; i<nbcomptes;i++)
        {
            if(comptes[i].code_compte==code)
            {
                existe=1;
                break;
            }

        }
         if(existe){
                do
                {
                    printf("\t donner le montant a retirer: ");
                    scanf("%f", &montant);
                    if(montant>500){
                        printf("\t\t le retrait ne doit pas passer 500dt. \n");
                    }
                    else if(montant>comptes[i].somme)
                    {
                        printf("\t\t le solde est insuffisant. \n");
                    }
                }while(montant>500 || montant>comptes[i].somme);
                comptes[i].somme-=montant;
                for(int j=0; j<nbcomptes;j++)
                      {
                            fwrite(&comptes[j], sizeof(comptes[j]),1,nf);
                      }
                printf("montant retire avec sucees.\n");

         }
         else{
               printf("le compte n'existe pas.\n");
             }

        fclose(nf);
        rename("nf.txt", "compte.txt");
        printf("code compte: %d\n", comptes[i].code_compte);
        printf("code client: %d\n", comptes[i].mat_client);
        printf("solde du compte: %.2f\n", comptes[i].somme);
        printf("date de creation: %d/%d/%d\n", comptes[i].d_compte.jour, comptes[i].d_compte.mois, comptes[i].d_compte.annee);
        printf("*****************\n");
    }
    else if(k==2)//Versement d'argent
    {
      int option=0;
      printf("1. Versement espece\n");
      printf("2. Versement d'un autre compte\n");
      printf("3. Retour\n");
      do
      {
          printf("donner l'option: ");
          scanf("%d", &option);

      }while(option<1 || option>3);

      if(option==1)
      {//Versement espece

        struct compte compte;
        int code;
        float montant;
        int existe=0;
        FILE *file;
        printf("donner le code du compte : ");
        scanf("%d", &code);

        file= fopen("compte.txt","r");
        int nbcomptes=0;
        while(fread(&compte, sizeof(struct compte),1,file))
        {
            comptes[nbcomptes]=compte;
            nbcomptes++;
        }
        fclose(file);

        assert(fclose(file)!=0);
        remove("compte.txt");
        FILE *nf;
        nf=fopen("nf.txt", "a");
        int i;
        for(i=0; i<nbcomptes;i++)
        {
            if(comptes[i].code_compte==code)
            {
                existe=1;
                break;
            }

        }
         if(existe){
                do
                {
                    printf("\t donner le montant a ajouter: ");
                    scanf("%f", &montant);

                }while(montant<0);
                comptes[i].somme+=montant;
                for(int j=0; j<nbcomptes;j++)
                      {
                            fwrite(&comptes[j], sizeof(comptes[j]),1,nf);
                      }
                printf("montant ajoute avec sucees.\n");

                printf("code compte: %d\n", comptes[i].code_compte);
                printf("code client: %d\n", comptes[i].mat_client);
                printf("solde du compte: %.2f\n", comptes[i].somme);
                printf("date de creation: %d/%d/%d\n", comptes[i].d_compte.jour, comptes[i].d_compte.mois, comptes[i].d_compte.annee);
                printf("*****************\n");

         }
         else{
               printf("le compte n'existe pas.\n");
             }

        fclose(nf);
        rename("nf.txt", "compte.txt");

      }

      else if(option==2)
      {// Versement d'apres un autre compte
        struct compte compte;
        int code1, code2;
        float montant;
        int existe1=0;
        int existe2=0;
        FILE *file;
        printf("donner le code du compte a recharger: ");
        scanf("%d", &code1);
        do
        {
          printf("donner le code du compte d'ou vous voulez recharger: ");
          scanf("%d", &code2);
          if(code2==code1){
            printf("Desole c est le meme compte! \n");
          }
        }while(code2==code1);

        file= fopen("compte.txt","r");
        int nbcomptes=0;
        while(fread(&compte, sizeof(struct compte),1,file))
        {
            comptes[nbcomptes]=compte;
            nbcomptes++;
        }
        fclose(file);

        assert(fclose(file)!=0);
        remove("compte.txt");
        FILE *nf;
        nf=fopen("nf.txt", "a");
        int i,j;
        for(i=0; i<nbcomptes;i++)
        {
            if(comptes[i].code_compte==code1)
            {
                existe1=1;
                break;
            }

        }
         for(j=0; j<nbcomptes;j++)
        {
            if(comptes[j].code_compte==code2)
            {
                existe2=1;
                break;
            }

        }
         if(existe1 && existe2){
                do
                {
                    printf("\t donner le montant a ajouter: ");
                    scanf("%f", &montant);
                    if(montant>comptes[j].somme)
                    {
                        printf("\t\t le solde est insuffisant. \n");
                    }
                }while(montant<0 || montant>comptes[j].somme);
                comptes[i].somme+=montant;
                comptes[j].somme-=montant;
                for( j=0; j<nbcomptes;j++)
                      {
                            fwrite(&comptes[j], sizeof(comptes[j]),1,nf);
                      }
                printf("montant ajoute avec sucees.\n");

                printf("code compte: %d\n", comptes[i].code_compte);
                printf("code client: %d\n", comptes[i].mat_client);
                printf("solde du compte: %.2f\n", comptes[i].somme);
                printf("date de creation: %d/%d/%d\n", comptes[i].d_compte.jour, comptes[i].d_compte.mois, comptes[i].d_compte.annee);
                printf("*****************\n");

         }
         else{
               printf("l'un des deux comptes n'existe pas.\n");
             }

        fclose(nf);
        rename("nf.txt", "compte.txt");
      }
      else if(option==3)
      {//retour
          printf("\n");
          sous_menu(3);

      }

    }
    else if(k==3)//retour
    {
        printf("\n");
       menu();
    }


}

int main()
{
    menu();

}

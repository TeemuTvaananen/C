#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//funktiot



void lueRoskat(void){

   // Tyhjennet��n puskuri
   while( fgetc(stdin) != '\n');
}

void kaantaja(FILE *tiedosto, char* keyword);

int main()
{
    //tarvittavat muuttujat
    FILE * tiedosto;
    const char * nimi = {"testitiedosto.txt"};
   char avainsana[50];


   printf("Syota kaannettava sana > \n"); //kysyt��n k�ytt�j�lt� sanaa
   scanf("%s", avainsana); // otetaan sy�te
   lueRoskat(); // puskurin tyhjennys

   tiedosto = fopen(nimi, "r"); // avataan tiedosto luettavaksi

   if(tiedosto == NULL){ // virheen tarkistus
    printf("Virhe tiedoston avaamisessa");
    return 0;
   }

   kaantaja(tiedosto, avainsana); // laitetaan sy�tetty sana ja tiedosto kaantaja- nimisen funktion k�sittelyyn

fclose(tiedosto); //suljetaan tiedosto k�sittelyn j�lkeen
   return 0;
}


void kaantaja(FILE * tiedosto,char* keyword){

    char * tulos;  //tiedostosta avainsanaa vastaava rivi jota etsit��n
    char * suomeksi; //suomeksi tulostettava sana
    char * englanniksi; //englanniksi tulostettava sana
   char rivi[100]; // tiedostosta skannattava rivi
   const char * erottaja = ";";  // sanat erottava merkki tiedostossa

//k�ynnistet��n silmukka ja l�hdet��n k�ym��n tiedosta rivi rivilt� l�pi
do{

       tulos = strstr(rivi, keyword); // t�ss� verrataan skannattavaa rivi� sy�tettyyn avainsanaan

       if(tulos != NULL ){ // jos rivilt� l�ytyy vastaavuus sy�tteeseen, silmukka lopetetaan
        break;
       }
   }
while(fscanf(tiedosto, "%s", rivi) != EOF);


if(tulos == NULL){ // jos tiedostosta ei l�ydy sanaa mit� haetaan niin tulostetaan virheilmoitus
    printf("sanaa %s ei loytynyt sanakirjasta", keyword);
}else{

 suomeksi = strtok(rivi, erottaja);  //t�ss� otetaan l�ydetyn rivin suomenkielinen "token" ja laitetaan se muuttujaan
 englanniksi = strtok(NULL, erottaja); //t�ss� otetaan l�ydetyn rivin j�lkimm�inen "token" ja laitetaan se muuttujaan

    if(strcmp(englanniksi, keyword)== 0){ // jos sy�tetty sana on englannin kielell�

            printf("%s", suomeksi);  // k��nnet��n sana suomeksi

    } else{
        printf("%s", englanniksi); // muutoin k��nnet��n sana englanniksi
    }

}
return;
} //funktion loppu



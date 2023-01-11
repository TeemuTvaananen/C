#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//funktiot



void lueRoskat(void){

   // Tyhjennetään puskuri
   while( fgetc(stdin) != '\n');
}

void kaantaja(FILE *tiedosto, char* keyword);

int main()
{
    //tarvittavat muuttujat
    FILE * tiedosto;
    const char * nimi = {"testitiedosto.txt"};
   char avainsana[50];


   printf("Syota kaannettava sana > \n"); //kysytään käyttäjältä sanaa
   scanf("%s", avainsana); // otetaan syöte
   lueRoskat(); // puskurin tyhjennys

   tiedosto = fopen(nimi, "r"); // avataan tiedosto luettavaksi

   if(tiedosto == NULL){ // virheen tarkistus
    printf("Virhe tiedoston avaamisessa");
    return 0;
   }

   kaantaja(tiedosto, avainsana); // laitetaan syötetty sana ja tiedosto kaantaja- nimisen funktion käsittelyyn

fclose(tiedosto); //suljetaan tiedosto käsittelyn jälkeen
   return 0;
}


void kaantaja(FILE * tiedosto,char* keyword){

    char * tulos;  //tiedostosta avainsanaa vastaava rivi jota etsitään
    char * suomeksi; //suomeksi tulostettava sana
    char * englanniksi; //englanniksi tulostettava sana
   char rivi[100]; // tiedostosta skannattava rivi
   const char * erottaja = ";";  // sanat erottava merkki tiedostossa

//käynnistetään silmukka ja lähdetään käymään tiedosta rivi riviltä läpi
do{

       tulos = strstr(rivi, keyword); // tässä verrataan skannattavaa riviä syötettyyn avainsanaan

       if(tulos != NULL ){ // jos riviltä löytyy vastaavuus syötteeseen, silmukka lopetetaan
        break;
       }
   }
while(fscanf(tiedosto, "%s", rivi) != EOF);


if(tulos == NULL){ // jos tiedostosta ei löydy sanaa mitä haetaan niin tulostetaan virheilmoitus
    printf("sanaa %s ei loytynyt sanakirjasta", keyword);
}else{

 suomeksi = strtok(rivi, erottaja);  //tässä otetaan löydetyn rivin suomenkielinen "token" ja laitetaan se muuttujaan
 englanniksi = strtok(NULL, erottaja); //tässä otetaan löydetyn rivin jälkimmäinen "token" ja laitetaan se muuttujaan

    if(strcmp(englanniksi, keyword)== 0){ // jos syötetty sana on englannin kielellä

            printf("%s", suomeksi);  // käännetään sana suomeksi

    } else{
        printf("%s", englanniksi); // muutoin käännetään sana englanniksi
    }

}
return;
} //funktion loppu



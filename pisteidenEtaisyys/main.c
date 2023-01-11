#include <stdio.h>
#include <stdlib.h>
#include <math.h> // tätä tarvitaan pow ja sqrt funktioiden käyttöön
#define MAKSIMI 10

//tietueen määrittely
typedef struct{
int x;
int y;
}piste_t;

//tehtävän toteuttamiseen tarvittavat funktiot
int lueKokonaisluku(void);
void lueRoskat(void);
piste_t koordinaatin_luku(int n);
double linnuntieLaskuri(piste_t p1, piste_t p2);
double laskeTieMutkitellen(piste_t * taulukko);

int main()
{
    int i;
    double linnuntie = 0;
    double mutkitellen = 0;

    piste_t taulukko[MAKSIMI];

    for(i = 0; i<5; i++){
        taulukko[i] = koordinaatin_luku(i);
    }
    /*selvitetään vaaditut tiedot eli suorien muodostaman ketjun pituus
    sekä ensimmäisen ja viimeisen pisteen välinen matka käyttämällä funktioita*/

    mutkitellen = laskeTieMutkitellen(taulukko);
    linnuntie = linnuntieLaskuri(taulukko[0], taulukko[4]);

//tulostetaan tulokset
    printf("\nEtaisyys mutkitellen on %.3lf\n", mutkitellen);
    printf("Alku ja loppupisteiden valinen etaisyys on %.3lf", linnuntie);

}
//koordinaattien lukemiseen käytetty funktio
piste_t koordinaatin_luku(int n){

piste_t temp;

printf("\nAnna %d. X koordinaatti > ", n+1);
temp.x = lueKokonaisluku();

printf("Anna %d. Y koordinaatti > ", n+1);
temp.y = lueKokonaisluku();
return temp;
}

//suorien muodostaman ketjun pituuteen käytetty funktio
double laskeTieMutkitellen(piste_t * taulukko){
double tulos = 0;
for(int i = 0; i < 4; i++){
        tulos += linnuntieLaskuri(taulukko[i], taulukko[i+1]);
    }

return tulos;
}

//alku- ja loppupisteen välimatkan selvittämiseen käytetty funktio
double linnuntieLaskuri(piste_t p1, piste_t p2){
double etaisyys ;
etaisyys  = sqrt( (pow( (p2.x- p1.x), 2) ) + (pow ( (p2.y- p1.y), 2) ) ); //kaava saatu tehtävänannosta valmiina
return etaisyys;
}


//apuohjelmat: saatu moodlesta
int lueKokonaisluku(void){
   int luku = 0;
   char mki =' ';
   int status = 0;

   while (((status = scanf("%d%c", &luku, &mki)) == 0)  || (2 == status && mki != '\n')){
      lueRoskat();
      printf("Et syottanyt kokonaislukua > ");
   }
   return luku;
}


void lueRoskat(void){
   // Tyhjennetään puskuri
   while( fgetc(stdin) != '\n');
}

/* Ohjelma, jonka ideana on kuvata karkeasti pankkiautomaatin perustoimintoja ja sen tarjoamia alaohjelmia käyttäjälle.
Omassa ohjelmassani näitä ovat pin koodin syöttäminen, nosto, talletus ja saldon katsominen.
Ohjelmaan on viimeisimpänä lisätty rahojen jakamisalgoritmi nosto toimintoa varten joka
siis tulostaa vain 20e ja 50e seteleitä. Algoritmi on totetettu myös niin, että se antaa
aina mahdollisimman suuria seteleitä. Lisäsin myös ominaisuudet suurimman kertanoston(1000e)
tarkistamiseen ja myös siihen, että nosto on pienimmillään 20 tai 40 euroa ja myös kymmenellä
jaoillinen tasaluku.

Tässä viimeisimmässä versiossa muokkasin ohjelmaan uudenlaisen pin-koodin
ja käyttäjätunnuksen kysymiseen tarkoitetun funktion main funktioon ja tein päävalikolle oman
funktion.

Oikea pin-koodi on: 6660.
Aloitussaldo on: 3000 euroa.

Ohjelma toteutettiin Ohjelmointi 1 kurssin kotityönä Oulun Yliopistossa syyslukukaudella 2022
Tekijä Teemu Väänänen
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int saldonTarkistaminen(int tilin_saldo);
int talletaRahaa(int tilin_saldo);
int nostaRahaa(int tilin_saldo);
void rahojenJako(int nosto);
void navigointi(int tilin_saldo);

//apuohjelmat: otettu sivulta https://moodle.oulu.fi/course/view.php?id=12425&section=2
int lueKokonaisluku(void);
void lueRoskat(void);


/* Tässä funktiossa katsotaan käyttäjän tilinumero ja pin-koodi. Molemmat näistä tiedoista otetaan tiedostosta 12345.acc ja ne löytyvät merkkijonoina tiedoston kahdelta ensimmäisiltä riveiltä. Näiden syötteiden oikeudellisuudet tarkastetaan myös käyttämällä hyväksi kahta eriä do-while toistorakennetta (yksi tiedostolle ja yksi pin-koodille).
Pin koodi luetaan tiedostosta vastaavaan merkkijonoon ja sen jälkeen tätä merkkijonoa verrataan käyttäjän syötteeseen käyttämällä strcmp funktiota.
Jos vertaus onnistuu, niin luetaan tiedostosta saldon määrä ja viedään saldo navigointifunktioon, jossa se annetaan myös parametreiksi muille funktioille.
 Annoin myös käyttäjälle yhteensä 3 yritystä laittaa sekä käyttäjätunnuksen, että
pin koodin oikein.

Jos syötteet eivät menneet oikein niin ohjelma lopetettiin.

*/
 int main(){
    char tilinumero[50] = {'\0'};
    FILE * tiedosto;
    int kate = 0;
    int tulos;
    char PinKoodi[5] = { '\0' };
    char pinTarkistus[5] = { '\0' };
    int avaamis_yritykset = 3;
    int pin_yritykset = 3;

    do{
    printf("Syota tilinumerosi> ");
        fgets(tilinumero, 50, stdin);
            if (tilinumero[strlen(tilinumero)-1] == '\n')
                {
                tilinumero[strlen(tilinumero)-1] = '\0'; }
                else{
                    lueRoskat(); }

                    strcat(tilinumero, ".acc");
                    tiedosto = fopen(tilinumero, "r");

                if(tiedosto == NULL){
                        avaamis_yritykset--;

                        if(avaamis_yritykset == 0){

                        printf("\n**Liian monta virheellista yritysta**\n");
                        printf("Automaatti sulkeutuu\n");
                        exit(EXIT_FAILURE);
                        }
                else{
                        printf("\n**On tapahtunut virhe tilin avaamisessa**\n");
                        printf("Yrita uudelleen, %d yritysta jaljella.\n\n", avaamis_yritykset);
                        }
                        }
                        }while(tiedosto == NULL && avaamis_yritykset > 0);

                            fgets(pinTarkistus, 5 , tiedosto);

            do{
                    printf("\nSyota pinkoodi > ");
                fgets(PinKoodi, 5 , stdin);

                if(PinKoodi[strlen(PinKoodi) - 1] == '\n'){
                   PinKoodi[strlen(PinKoodi) - 1] = '\0'; }

                   else {
                        lueRoskat(); }

                    if((pinTarkistus[strlen(pinTarkistus) - 1]) == '\n'){
                        pinTarkistus[strlen(pinTarkistus) - 1] = '\0'; }

                        if((tulos = strcmp(PinKoodi, pinTarkistus)) == 0){
                            fscanf(tiedosto, "%d", &kate);
                            navigointi(kate);
                            break;  }

                            else {
                                pin_yritykset--;

                                if(pin_yritykset == 0){
                                    printf("\n**Syotit virheellisen pin koodin liian monta kertaa**\n");
                                    printf("Automaatti suljetaan");
                                    fclose(tiedosto);
                                    exit(EXIT_FAILURE);}

                                printf("\n**Vaara pinkoodi, yrita uudelleen.**\n");
                                printf("%d yritysta jaljella\n", pin_yritykset);
                                }

            } while(1);

fclose(tiedosto);
return 0;
}

    /* Tätä funktiota käytetään navigointiin pankkiautomaatin sisäisissä toiminnoissa. Ensimmäisenä tulostetaan tervetuliaislausahdus käyttäjälle
    valikon kanssa. Nyt käyttjän on mahdollista valita mitä haluaa tehdä. Vaihtoehtoja on 4 kpl.
    Jos käyttäjä syöttää muuta kuin annetut vaihtoehdot niin tulostetaan virheilmoitus.
    Funktio saa parametrina tilin saldon main-funktiosta, jossa se luetaan tiedostosta.*/
    void navigointi(int tilin_saldo){
    int
    Kayttajan_valinta,
    lopetus = 4;

    printf("\n***Tervetuloa kayttamaan Teemun pankkiautomaattia.***\n");


        while(Kayttajan_valinta != lopetus)
        {
        printf("\nValitse toiminto");
        printf("\n1: Katso saldo");
        printf("\n2: Talleta rahaa");
        printf("\n3: Nosta rahaa");
        printf("\n4:Lopeta automaatin kaytto\n");
     Kayttajan_valinta =lueKokonaisluku();


        switch(Kayttajan_valinta)
        {
        case 1:
            saldonTarkistaminen(tilin_saldo);

            break;
        case 2:
           tilin_saldo = talletaRahaa(tilin_saldo);

            break;
        case 3:
          tilin_saldo = nostaRahaa(tilin_saldo);
            break;

        case 4:
           printf("\n*** Kiitos kun kaytit Teemun pankkiautomaattia*** \n");
               return;
           break;
        default:
            printf("\n**Virheellinen syote**");
            break;
        }
        }

}

/* Tätä funktiota käytetään tulostamaan käyttäjälle tilin saldon. Se saa parametrina tilin saldon ja palauttaa sen myös navigointifunktioon.*/
int saldonTarkistaminen( int tilin_saldo)
{
printf("\n*** Saldosi on %d euroa*** \n", tilin_saldo);

return tilin_saldo;
}

/* Tässä funktiossa tapahtuu rahojen tallettaminen tilille. Ensin käyttäjältä kysytään talletuksen määrää ja luetaan se käyttämällä lueKokonaisluku-funktiota.
Sen jälkeen katsotaan, että talletus on tasaluku eli kymmenellä jaollinen. Näin ollen esimerkiksi 37 euroa ei kelpaa. Jos syöte ei kelpaa, kehotetaan syöttämään summa uudelleen.
Sitten katsotaan, että onhan talletus pienenmpi kuin 1000 euroa eli suurin sallittu kertatalletus.
Viimeisenä tarkistetaan, että talletus on suurempi kuin minimitalletus eli 20 euroa.
Kun näistä päästään läpi niin tilin saldoa päivitetään ja tulostetaan päivitetty saldo.
Funktio saa parametrina tilin saldon ja palauttaa päivitetyn version siitä navigointifunktioon. */
int talletaRahaa(int tilin_saldo){
int talletus;

printf("\nPaljonko haluat tallettaa rahaa?\n");
talletus = lueKokonaisluku();

        if(talletus%10 != 0){
            do{
                printf("**Voit tallettaa vain tasalukuja, jotka ovat kymmenella jaollisia**\n");
                printf("\nSyota tallennettava summa uudelleen\n");
                talletus = lueKokonaisluku();
                }
                while(talletus%10 != 0);
                }

if(talletus > 1000){ printf("\n**Voit tallettaa kerrallaan vain 1000 euroa**\n");
                    printf("Palaat paavalikkoon\n"); }

                    else if(talletus < 20) {
                        printf("\n**Talletuksen on oltava vahintaan 20 euroa**\n");
                        printf("\nPalaat paalvalikkoon\n");
                    }//else if

    else {tilin_saldo += talletus;

    printf("\n*** Saldosi on talletuksen jalkeen %d euroa*** \n", tilin_saldo);

    }
return tilin_saldo;
}

/*Tässä funktiossa tapahtuu rahojen nostaminen tililtä.'
Ensin katsotaan, että onhan nostettu summa pienimmillään 20 tai 40 euroa ja kymmenellä jaollinen. Jos ei ole, niin pyydetään nostettavaa summaa uudelleen.
Sen jälkeen tarkastetaan, että onhan nosto pienempi kuin 1000 euroa, eli suurin sallittu kertanosto.
Tämän jälkeen tarkastetaan, että tilillä on katetta nostamiseen. Jos katetta ei ole, niin käyttäjä palautetaan päävalikkoon.
Kun on tarkistettu nämä kohdat niin mennään rahojen jakamiseen käytettyyn funktioon, tullaan sieltä pois ja vähennetään nosto tilin saldosta ja palataan päävalikkoon.
Funktio saa parametrina tilin saldon ja palauttaa päivitetyn version siitä navigointifunktioon.*/
int nostaRahaa(int tilin_saldo){
    int nosto, valikko;


    printf("\nPaljonko haluat nostaa rahaa?\n");
    nosto = lueKokonaisluku();


    if ((nosto < 40 && nosto != 20) || (nosto % 10) != 0){

            while((nosto < 40 && nosto != 20) || (nosto % 10) != 0){
                printf("\n**Pienimmat mahdolliset nostot automaatista ovat 20e ja 40e ja luvun on oltava kymmenella jaollinen**\n");
                printf("\nAnna nostettava summa uudelleen ");
                nosto = lueKokonaisluku();
        }
    }
        if(nosto > 1000){
                    printf("\n**Suurin kertanosto on 1000 euroa**\n");
                    printf("\nPalaat paavalikkoon\n");  }

            else if(nosto > tilin_saldo){
                        printf("\n**Tilillasi ei ole riittavasti katetta nostoon**\n");
                        printf("\nPalaat paavalikkoon\n");  }


                    else{
                            rahojenJako(nosto);
                            tilin_saldo-=nosto;
                            printf("\n***Saldosi on noston jalkeen %d euroa***\n", tilin_saldo);    }
 return tilin_saldo;
}

/* Tätä funktiota käytän jakamaan rahat seteleiksi oikealla tavalla käyttäjän nostaessa rahaa.
Ensin funktiossa katsotaan onko nostettava summa jaollinen viidelläkymmenellä. Jos on, tulostetaan vain viisikymppisiä.

Seuraavaksi katsotaan sitä skenaariota, jos nosto on jaollinen kahdellakymmenellä, mutta ei viidelläkymmenellä eli vaikka 160 euroa.
Tällöin vähennetään nostettavaa summaa ja sitä mukaa kasvatetaan kahden kymmenen euron setelien määrää. Kun vähentämisen myötä löytyy summa, joka on jaollinen
viidelläkymmenellä niin laitetaan viiden kymmenen euron setelien määräksi loppu summa jaettuna viidelläkymmenellä.

Sitten on vielä summat jotka eivät ole jaollisia kummallakaan setelin määrällä eli kahdellakymmenellä tai viidelläkymmenellä. Esimerkkinä 130 euroa
Tässä tapauksessa lähdetään myös vähentämään summaa. Kun löytyy kahdellakymmenellä jaollinen summa, niin kasvatetaan kahdenkymmenen euron setelien määrää. Kun löytyy viidellä-
kymmenellä jaollinen summa niin katkaistaan silmukka, jossa vähennetään summaa, ja jaetaan jäljelle jäänyt summa viidelläkymmenellä, mistä saadaan viidenkymmenen euron setelien määrä.

Funktio saa parametrina noston nostaRahaa funktiosta.*/
void rahojenJako(int nosto){

    int viiskymppiset = 0,
    kakskymppiset = 0;

 if (nosto % 50 == 0 ){
    viiskymppiset = nosto / 50;
        printf("\nTulostuu %d kpl 50 e setelia", viiskymppiset); }

else if(nosto % 50 != 0 && nosto % 20 == 0){

        while (1)
            {  nosto --;
                kakskymppiset ++;

        if(nosto % 100 == 0 ){
                viiskymppiset = nosto / 50;
                        break; }
            }
            printf("\nTulostuu %d kpl 20e setelia ja %d kpl 50e setelia", kakskymppiset / 20 , viiskymppiset);
    }

else if(nosto % 50 != 0 && nosto % 20 != 0){

            while(1){
                nosto--;

        if(nosto % 20 == 0){
                kakskymppiset ++; }

        else if(nosto % 50 == 0){
                viiskymppiset = nosto / 50;
                break;}
                    }

printf("\nTulostuu %d kpl 20e setelia ja %d kpl 50e setelia", kakskymppiset, viiskymppiset);
}
return;
}

/* Tämä funktio tyhjentää puskurin.
Otettu Moodlesta annetuista apuohjelmista.
Ei parametreja, ei paluuarvoa.*/

void lueRoskat(void){
   while( fgetc(stdin) != '\n');
}

/* Tämä funktio lukee kokonaisluvun ja tulostaa myös virheilmoituksen käyttäjälle, jos syöte on virheellinen.
Ei saa parametreja, mutta paluuarvona on muuttuja nimeltä luku.
*/
int lueKokonaisluku(void){
   int luku = 0;
   char mki =' ';
   int status = 0;
   while (((status = scanf("%d%c", &luku, &mki)) == 0)  || (2 == status && mki != '\n')){
      lueRoskat();
      printf("\n**Virheellinen syote**");
      printf("\nYrita uudelleen! > ");
   }
   return luku;
}

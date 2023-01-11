/* Ohjelma, jonka ideana on kuvata karkeasti pankkiautomaatin perustoimintoja ja sen tarjoamia alaohjelmia k�ytt�j�lle.
Omassa ohjelmassani n�it� ovat pin koodin sy�tt�minen, nosto, talletus ja saldon katsominen.
Ohjelmaan on viimeisimp�n� lis�tty rahojen jakamisalgoritmi nosto toimintoa varten joka
siis tulostaa vain 20e ja 50e seteleit�. Algoritmi on totetettu my�s niin, ett� se antaa
aina mahdollisimman suuria seteleit�. Lis�sin my�s ominaisuudet suurimman kertanoston(1000e)
tarkistamiseen ja my�s siihen, ett� nosto on pienimmill��n 20 tai 40 euroa ja my�s kymmenell�
jaoillinen tasaluku.

T�ss� viimeisimm�ss� versiossa muokkasin ohjelmaan uudenlaisen pin-koodin
ja k�ytt�j�tunnuksen kysymiseen tarkoitetun funktion main funktioon ja tein p��valikolle oman
funktion.

Oikea pin-koodi on: 6660.
Aloitussaldo on: 3000 euroa.

Ohjelma toteutettiin Ohjelmointi 1 kurssin kotity�n� Oulun Yliopistossa syyslukukaudella 2022
Tekij� Teemu V��n�nen
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


/* T�ss� funktiossa katsotaan k�ytt�j�n tilinumero ja pin-koodi. Molemmat n�ist� tiedoista otetaan tiedostosta 12345.acc ja ne l�ytyv�t merkkijonoina tiedoston kahdelta ensimm�isilt� riveilt�. N�iden sy�tteiden oikeudellisuudet tarkastetaan my�s k�ytt�m�ll� hyv�ksi kahta eri� do-while toistorakennetta (yksi tiedostolle ja yksi pin-koodille).
Pin koodi luetaan tiedostosta vastaavaan merkkijonoon ja sen j�lkeen t�t� merkkijonoa verrataan k�ytt�j�n sy�tteeseen k�ytt�m�ll� strcmp funktiota.
Jos vertaus onnistuu, niin luetaan tiedostosta saldon m��r� ja vied��n saldo navigointifunktioon, jossa se annetaan my�s parametreiksi muille funktioille.
 Annoin my�s k�ytt�j�lle yhteens� 3 yrityst� laittaa sek� k�ytt�j�tunnuksen, ett�
pin koodin oikein.

Jos sy�tteet eiv�t menneet oikein niin ohjelma lopetettiin.

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

    /* T�t� funktiota k�ytet��n navigointiin pankkiautomaatin sis�isiss� toiminnoissa. Ensimm�isen� tulostetaan tervetuliaislausahdus k�ytt�j�lle
    valikon kanssa. Nyt k�yttj�n on mahdollista valita mit� haluaa tehd�. Vaihtoehtoja on 4 kpl.
    Jos k�ytt�j� sy�tt�� muuta kuin annetut vaihtoehdot niin tulostetaan virheilmoitus.
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

/* T�t� funktiota k�ytet��n tulostamaan k�ytt�j�lle tilin saldon. Se saa parametrina tilin saldon ja palauttaa sen my�s navigointifunktioon.*/
int saldonTarkistaminen( int tilin_saldo)
{
printf("\n*** Saldosi on %d euroa*** \n", tilin_saldo);

return tilin_saldo;
}

/* T�ss� funktiossa tapahtuu rahojen tallettaminen tilille. Ensin k�ytt�j�lt� kysyt��n talletuksen m��r�� ja luetaan se k�ytt�m�ll� lueKokonaisluku-funktiota.
Sen j�lkeen katsotaan, ett� talletus on tasaluku eli kymmenell� jaollinen. N�in ollen esimerkiksi 37 euroa ei kelpaa. Jos sy�te ei kelpaa, kehotetaan sy�tt�m��n summa uudelleen.
Sitten katsotaan, ett� onhan talletus pienenmpi kuin 1000 euroa eli suurin sallittu kertatalletus.
Viimeisen� tarkistetaan, ett� talletus on suurempi kuin minimitalletus eli 20 euroa.
Kun n�ist� p��st��n l�pi niin tilin saldoa p�ivitet��n ja tulostetaan p�ivitetty saldo.
Funktio saa parametrina tilin saldon ja palauttaa p�ivitetyn version siit� navigointifunktioon. */
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

/*T�ss� funktiossa tapahtuu rahojen nostaminen tililt�.'
Ensin katsotaan, ett� onhan nostettu summa pienimmill��n 20 tai 40 euroa ja kymmenell� jaollinen. Jos ei ole, niin pyydet��n nostettavaa summaa uudelleen.
Sen j�lkeen tarkastetaan, ett� onhan nosto pienempi kuin 1000 euroa, eli suurin sallittu kertanosto.
T�m�n j�lkeen tarkastetaan, ett� tilill� on katetta nostamiseen. Jos katetta ei ole, niin k�ytt�j� palautetaan p��valikkoon.
Kun on tarkistettu n�m� kohdat niin menn��n rahojen jakamiseen k�ytettyyn funktioon, tullaan sielt� pois ja v�hennet��n nosto tilin saldosta ja palataan p��valikkoon.
Funktio saa parametrina tilin saldon ja palauttaa p�ivitetyn version siit� navigointifunktioon.*/
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

/* T�t� funktiota k�yt�n jakamaan rahat seteleiksi oikealla tavalla k�ytt�j�n nostaessa rahaa.
Ensin funktiossa katsotaan onko nostettava summa jaollinen viidell�kymmenell�. Jos on, tulostetaan vain viisikymppisi�.

Seuraavaksi katsotaan sit� skenaariota, jos nosto on jaollinen kahdellakymmenell�, mutta ei viidell�kymmenell� eli vaikka 160 euroa.
T�ll�in v�hennet��n nostettavaa summaa ja sit� mukaa kasvatetaan kahden kymmenen euron setelien m��r��. Kun v�hent�misen my�t� l�ytyy summa, joka on jaollinen
viidell�kymmenell� niin laitetaan viiden kymmenen euron setelien m��r�ksi loppu summa jaettuna viidell�kymmenell�.

Sitten on viel� summat jotka eiv�t ole jaollisia kummallakaan setelin m��r�ll� eli kahdellakymmenell� tai viidell�kymmenell�. Esimerkkin� 130 euroa
T�ss� tapauksessa l�hdet��n my�s v�hent�m��n summaa. Kun l�ytyy kahdellakymmenell� jaollinen summa, niin kasvatetaan kahdenkymmenen euron setelien m��r��. Kun l�ytyy viidell�-
kymmenell� jaollinen summa niin katkaistaan silmukka, jossa v�hennet��n summaa, ja jaetaan j�ljelle j��nyt summa viidell�kymmenell�, mist� saadaan viidenkymmenen euron setelien m��r�.

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

/* T�m� funktio tyhjent�� puskurin.
Otettu Moodlesta annetuista apuohjelmista.
Ei parametreja, ei paluuarvoa.*/

void lueRoskat(void){
   while( fgetc(stdin) != '\n');
}

/* T�m� funktio lukee kokonaisluvun ja tulostaa my�s virheilmoituksen k�ytt�j�lle, jos sy�te on virheellinen.
Ei saa parametreja, mutta paluuarvona on muuttuja nimelt� luku.
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

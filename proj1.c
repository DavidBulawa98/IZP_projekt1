#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define RADEK 42
#define ZNAK 100
#define VELIKOST_VYSTUP_POLE 128

/**
 * Funkce pro nacteni ze souboru do pole.
 * @param pole Pole do ktereho budu nacitat
 */
void NactiPole(char pole[RADEK][ZNAK]){
	char nactenyZnak = 'a'; //Priradim si promenou s hodnotou jinou nez '\0'
    //Radek
	int j = 0;
    //Znak
	int i = 0;
	while (i < 42 && nactenyZnak != EOF){
		i = 0;
        //Dokud nenacte line separator nebo EOF
		while((nactenyZnak = getchar())!= 10 && (nactenyZnak != EOF)){
			pole[j][i] = toupper((int)nactenyZnak);
			i++;
		}
		j++;
	}
	pole[j][i] = EOF;
}

/**
 * Funkce, ktera prevadi argument na velke pismena.
 * @param argument Prevadeny argument.
 */
void argumentNaVelke(char argument[ZNAK]){
    for (unsigned  int i = 0; i < strlen(argument); ++i) {
       argument[i] = toupper(argument[i]);
    }
}

/**
 * Funkce pro vypsani vysledku, pokud uz nebyl nalezen.
 * @param pole Pole vysledku
 * @param citacVysledku Promenna podle ktere se pro adresu v poli nachazi znak na virtualni klavesnici.
 */
void vypsani(char pole[],int citacVysledku){
    if(citacVysledku >= 1) {
        printf("Enable: %s\n", pole);
    }else{
        printf("Not found\n");
    }
}

/**
 * Algoritmus pro razeni pole.
 * Cyklus porovnava 2 sousedni prvky, popr. je prohodi. Dokud nedojede na konec.
 * Pote opakuje dokud neni pole serazene.
 * @param razenePole Pole, ktere chceme seradit.
 */
void bubbleSort(char razenePole[VELIKOST_VYSTUP_POLE]){
    int temp;
    for(unsigned int i = 1; i < strlen(razenePole); i++)
    {
        for(unsigned int j = 0; j < strlen(razenePole) - i; j++)
        {
            if((int)razenePole[j]>=(int)razenePole[j + 1])
            {
                temp = razenePole[j];
                razenePole[j] = razenePole[j+1];
                razenePole[j+1] = temp;
            }
        }
    }
}

/**
 * Funkce vypocita dostupne znaky na virtualni klavesnici.
 * @param pole Pole ulozenych znaku ze souboru
 * @param vstup Porovnavany argument
 * @param poleVysledku Pristupne znaky na virualni klavesnici
 */
void vypocetZnaku(char pole[RADEK][ZNAK], char vstup[ZNAK],char poleVysledku[VELIKOST_VYSTUP_POLE]){
    //Porovnavany radek
    int j = 0;
    //Cita pocet zapsanych hodnot do enable, pouziti v funkci vypsani, rozhoduje mezi Enable a Not Found
    int citacVysledku = 0;
    //Cita pocet porovnani, vcetne duplicit pouziva se pro urceni nalezeni, Found:
    int pocetPorovnani = 0;
    //Adresa radku porovnavaneho znaku, pro pozdejsi vypsani Found: "radek"
    int adresaRadku;
    //Cyklus prochazejici po radku pole
    while(j <= RADEK){
        //Porovnani zda se argument primo nerovna radku
        if(strcmp(vstup,pole[j]) == 0){
            adresaRadku = j;
            pocetPorovnani++;
            break;
        }else if(strncmp(vstup, pole[j],strlen(vstup)) == 0){
            //Citac cyklu porovnavani duplicit
            unsigned int k = 0;
            //Urcuje zda byla nalezena duplicita
            bool nalezenaDuplicita = false;
            //Cyklus porovnavajici zda uz prvek v poli vysledku je(kontroluje duplicitu)
            while(k < strlen(poleVysledku)) {
                if(poleVysledku[k] == pole[j][strlen(vstup)]){
                    nalezenaDuplicita = true;
                    break;
                }
                k++;
            }
            pocetPorovnani++;
            adresaRadku = j;
            //Pokud nebyla duplicita nalezena, ulozi do pole vysledku
            if(nalezenaDuplicita == false) {
                poleVysledku[citacVysledku] = pole[j][strlen(vstup)];
                citacVysledku++;
            }
        }
        j++;
    }
    //Pokud je porovnani pouze 1, muzeme vypsat cely radek
    if(pocetPorovnani == 1){
        printf("Found: %s\n", pole[adresaRadku]);
    }else {
        bubbleSort(poleVysledku);
        vypsani(poleVysledku, citacVysledku);
    }
}

/**
 * Funkce vypocita dostupne znaky na virtualni klavesnici v pripade, ze neni zadan zadny argument.
 * @param pole Pole ulozenych znaku ze souboru.
 * @param poleVysledku Pristupne znaky na virualni klavesnici
 */
void vypisZnakyNullArgv(char pole[RADEK][ZNAK],char poleVysledku[VELIKOST_VYSTUP_POLE]) {
    //Porovnavany radek
	int j = 0;
    //Cita pocet zapsanych hodnot do enable, pouziti v funkci vypsani, rozhoduje mezi Enable a Not Found
    int citacVysledku = 0;
    //Cyklus prochazejici po radku pole
	while (j <= RADEK && pole[j][0] != '\0') {
        //Citac cyklu porovnavani duplicit
        unsigned int k = 0;
        //Urcuje zda byla nalezena duplicita
        bool nalezenaDuplicita = false;
        //Cyklus porovnavajici zda uz prvek v poli vysledku je(kontroluje duplicitu)
        while (k < strlen(poleVysledku)) {
            if (poleVysledku[k] == pole[j][0]) {
                nalezenaDuplicita = true;
                break;
            }
            k++;
        }
        if(nalezenaDuplicita == false){
            poleVysledku[citacVysledku] = pole[j][0];
            citacVysledku++;
        }
        j++;
	}
    bubbleSort(poleVysledku);
    //Vypis vysledku
    if(poleVysledku[0] != '\0'){
        printf("Enable: %s\n",poleVysledku);
    }else{
        printf("Soubor je prazdny\n");
    }
}

int main(int argc, char *argv[]){
    if(argc <= 2) {
        char arr[RADEK][ZNAK];
        char vysledky[VELIKOST_VYSTUP_POLE];
        NactiPole(arr);
        if (argv[1] == NULL) {
            vypisZnakyNullArgv(arr, vysledky);
        } else {
            argumentNaVelke(argv[1]);
            vypocetZnaku(arr, argv[1], vysledky);
        }
    }else{
        printf("Prilis mnoho argumentu\n");
    }
}


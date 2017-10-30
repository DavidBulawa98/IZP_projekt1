#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
void NactiPole(char pole[42][100]){
	char nactenyZnak = 'a'; //Priradim si promenou s hodnotou jinou nez '\0'
	int j = 0; //radek
	int i = 0; //znak
	while (i < 42 && nactenyZnak != EOF){
		i = 0;
		while((nactenyZnak = getchar())!= 10 && (nactenyZnak != EOF)){
			pole[j][i] = toupper((int)nactenyZnak);
			i++;
		}
		j++;
	}
	pole[j][i] = EOF;
}
void argumentNaVelke(char argument[100]){
    for (unsigned  int i = 0; i < strlen(argument); ++i) {
       argument[i] = toupper(argument[i]);
    }
}
void vypsani(char pole[],int citacVysledku){
    if(citacVysledku >= 1) {
        printf("Enable: %s\n", pole);
    }else{
        printf("Not found\n");
        }
    }
void bubbleSort(char razenePole[26]){
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

void vypisZnaky(char pole[42][100], char vstup[100],char poleVysledku[26]){
    int j = 0;
    int citacVysledku = 0;
    int pocetPorovnani = 0;
    int adresaRadku;
    while(j <= 42){
        if(strcmp(vstup,pole[j]) == 0){
            adresaRadku = j;
            pocetPorovnani++;
            break;
        }else if(strncmp(vstup, pole[j],strlen(vstup)) == 0){
            unsigned int k = 0;
            bool nalezenaDuplicita = false;
            while(k < strlen(poleVysledku)) {
                if(poleVysledku[k] == pole[j][strlen(vstup)]){
                    nalezenaDuplicita = true;
                    break;
                }
                k++;
            }
            pocetPorovnani++;
            adresaRadku = j;
            if(nalezenaDuplicita == false) {
                poleVysledku[citacVysledku] = pole[j][strlen(vstup)];
                citacVysledku++;
            }
        }
        j++;
    }
    if(pocetPorovnani == 1){
        printf("Found: %s\n", pole[adresaRadku]);
    }else {
        bubbleSort(poleVysledku);
        vypsani(poleVysledku, citacVysledku);
    }
}
void vypisZnakyNullArgv(char pole[42][100],char poleVysledku[26]) {
	int j = 0; //radek
    int citacVysledku = 0;
	while (j < 42 && pole[j][0] != '\0') {
        unsigned int k = 0;
        bool nalezenaDuplicita = false;
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
    if(poleVysledku[0] != '\0'){
        printf("Enable: %s\n",poleVysledku);
    }else{
        printf("Soubor je prazdny\n");
    }
}

int main(int argc, char *argv[]){
    (void)argc;
	char arr[42][100];
	char vysledky[26];
    NactiPole(arr);
    //char vysl[33];
	if(argv[1] == NULL){
		vypisZnakyNullArgv(arr,vysledky);
	}else{
        argumentNaVelke(argv[1]);
		vypisZnaky(arr,argv[1],vysledky);
	}

}


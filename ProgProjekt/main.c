#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funkcije.h"

int main() {
    Lik igrac;
    igrac.ime = (char*)calloc(IME_MAX, sizeof(char));
    char novo_ime[IME_MAX];

    if (igrac.ime == NULL) {
        perror("Greska memorije.");
        return;
    }

    igrac.level = 1;
    igrac.zdravlje = 100;
    igrac.snaga = 10;
    igrac.bodovi = 0;

    srand((unsigned)time(NULL));
    static enum Izbor izbor;

    printf("\t\t-----FERIT RPG-----\n\nUnesite ime svog lika: ");
    scanf("%24[^\n]", igrac.ime);
    getchar();

    do {
        system("cls");
        ispisi_izbornik();

        if (scanf("%d", &izbor) != 1) {
            printf("\nUnesite broj!\n");
            while (getchar() != '\n');
            continue;
        }

        int slot = 0;
        switch (izbor) {
            system("cls");
        case ZAPOCNI_IGRU:
            start(&igrac);
            break;
        case PRIKAZI_STANJE:
            prikazi_stanje(&igrac);
            break;
        case TRENIRAJ:
            treniraj(&igrac);
            break;
        case SPREMI_LIKA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);

            if (slot >= 1 && slot <= BROJ_LIKOVA) {
                spremi_lika(&igrac, slot - 1);
            }
            else {
                printf("Neispravan broj slota.\n");
            }
            break;
        case UCITAJ_LIKA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);

            if (slot >= 1 && slot <= BROJ_LIKOVA) {
                ucitaj_lika(&igrac, slot - 1);
            }
            else {
                printf("Neispravan broj slota.\n");
            }
            break;
        case IZBRISI_LIKA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);
            while (getchar() != '\n');
            if (slot >= 1 && slot <= BROJ_LIKOVA) {
                izbrisi_lika(slot - 1);
            }
            else {
                printf("Neispravan broj slota.\n");
            }
            break;
        case PRIKAZI_SVE_LIKOVE:
            prikazi_sve_likove();
            break;
        case SORTIRAJ_LIKOVE:
            sortiranje_likova();
            break;
        case NAPRAVI_NOVOG_LIKA:
            napravi_novog_lika(&igrac);
            break;
        case PRETRAZI_SLOT:
            printf("Unesite ime lika za pretragu: ");
            scanf("%24s", novo_ime);
            getchar();

            Lik likovi[BROJ_LIKOVA];
            int broj_likova = ucitaj_sve_likove(likovi);

            qsort(likovi, broj_likova, sizeof(Lik), usporedi_imena);

            Lik* trazeni_lik = pretrazi_lika(likovi, broj_likova, novo_ime);
            if (trazeni_lik != NULL) {
                printf("\nTrazeni lik: %s\nLevel: %d\nZdravlje: %d\nSnaga: %d\nBodovi: %d\n", trazeni_lik->ime, trazeni_lik->level, trazeni_lik->zdravlje, trazeni_lik->snaga, trazeni_lik->bodovi);
            }
            else {
                printf("\nLik nije pronaden.\n");
            }

            for (int i = 0; i < BROJ_LIKOVA; i++) {
                free(likovi[i].ime);
            }
            break;
        case PREIMENUJ_LIKA:
            printf("Unesite broj slota (1, 2 ili 3): ");
            scanf("%d", &slot);

            if (slot >= 1 && slot <= BROJ_LIKOVA) {
                printf("Unesite novo ime: ");
                scanf("%24s", novo_ime);
                getchar();

                promjeni_ime(slot - 1, novo_ime);
            }
            else {
                printf("\nNeispravan broj slota.\n");
            }
            break;
        case IZLAZ:
            logo();
            break;
        default:
            printf("\nTaj izbor ne postoji!\n");
            break;
        }
        system("pause");
    } while (izbor != IZLAZ); 

    free(igrac.ime);
    return 0;
}
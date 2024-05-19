#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funkcije.h"

int main() {
    Lik igrac = { "Lorem", 1, 100, 10, 0 };

    srand((unsigned)time(NULL));
    static enum Izbor izbor;

    printf("\t\t-----FERIT RPG-----\n\nUnesite ime svog lika: ");
    scanf("%24[^\n]", igrac.ime);
    getchar();

    do {
        system("cls");
        ispisiIzbornik();
        printf("\n\t\t\t\t\tOdabirem: ");

        if (scanf("%d", &izbor) != 1) {
            printf("\nUnesite broj!\n");
            while (getchar() != '\n');
            continue;
        }

        int slot;
        switch (izbor) {
            system("cls");
        case ZAPOCNI_IGRU:
            zapocniIgru(&igrac);
            break;
        case PRIKAZI_STANJE:
            prikaziStanje(&igrac);
            break;
        case TRENIRAJ:
            treniraj(&igrac);
            break;
        case SPREMI_LIKA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);
            if (slot >= 1 && slot <= 3) {
                spremiLika(&igrac, slot - 1);
            }
            else {
                printf("Neispravan broj slota.\n");
            }
            break;
        case UCITAJ_LIKA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);
            if (slot >= 1 && slot <= 3) {
                ucitajLika(&igrac, slot - 1);
            }
            else {
                printf("Neispravan broj slota.\n");
            }
            break;
        case IZBRISI_LIKA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);
            if (slot >= 1 && slot <= 3) {
                izbrisiLika(slot - 1);
            }
            else {
                printf("Neispravan broj slota.\n");
            }
            break;
        case PRIKAZI_SVE_LIKOVE:
            prikaziSveLikove();
            break;
        case SORTIRAJ_LIKOVE:
            sortirajLikove();
            break;
        case NAPRAVI_NOVOG_LIKA:
            napraviNovogLika(&igrac);
            break;
        case PRETRAZI_SLOT:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);
            pretraziSlot(slot - 1);
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

    return 0;
}
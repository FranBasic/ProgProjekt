#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

#define greska printf("Doslo je do greske!\n")


void ispisiIzbornik() {
    printf("\n\tODABERI POTEZ:\n");
    printf("1. Borba\n");
    printf("2. Stanje\n");
    printf("3. Trening\n");
    printf("4. Spremi lika\n");
    printf("5. Ucitaj lika\n");
    printf("6. Izlaz iz igre\n");
}


void zapocniIgru(const Lik* const lik) {

    if (lik == NULL) {
        printf("Greska ucitavanja lika.\n");
        return;
    }

    printf("\n-------------------\nUlazis u FERIT u potrazi za suparnikom...\n");

    Neprijatelj neprijatelji[] = { {"Kostur Bivseg Studenta", 1, 30, 5}, {"Grdosija Mrchella", 2, 40, 10}, {"Carobnjak Shoyo", 3, 50, 15} };
    int brojNeprijatelja = sizeof(neprijatelji) / sizeof(neprijatelji[0]);

    int indeks = rand() % brojNeprijatelja;
    Neprijatelj* neprijatelj = &neprijatelji[indeks];

    printf("Uh Oh! Izazvao te %s, level %d!\n", neprijatelj->ime, neprijatelj->level);
    napadniNeprijatelja(lik, neprijatelj);
}

void prikaziStanje(const Lik* const lik) {

    if (lik == NULL) {
        printf("Greska ucitavanja lika.\n");
        return;
    }

    printf("\n-------------------\n*** Stanje lika ***\n");
    printf("Ime: %s\n", lik->ime);
    printf("Level: %d\n", lik->level);
    printf("Zdravlje: %d\n", lik->zdravlje);
    printf("Snaga: %d\n", lik->snaga);
    printf("Bodovi: %d\n-------------------\n", lik->bodovi);
}

void napadniNeprijatelja(Lik* const lik, Neprijatelj* const neprijatelj) {

    printf("\nUlazis u borbenu poziciju...\n");

    if (lik == NULL || neprijatelj == NULL) {
        obradiGresku();
        return;
    }


    while (lik->zdravlje > 0 && neprijatelj->zdravlje > 0) {
        neprijatelj->zdravlje -= lik->snaga;
        lik->zdravlje -= neprijatelj->snaga;
    }

    if (lik->zdravlje > 0) {
        printf("Uspijeh!\n%s je porazen! Osvojio si +", neprijatelj->ime);
        
        switch (neprijatelj->level) {
            case 1:
                printf("10 bodova!\n-------------------\n\n");
                lik->bodovi += 10;
                break;
            case 2:
                printf("15 bodova!\n-------------------\n\n");
                lik->bodovi += 15;
                break;
            case 3:
                printf("20 bodova!\n-------------------\n\n");
                lik->bodovi += 20;
                break;
            default:
                break;
        }

        if (lik->bodovi >= 50) {
            lik->level++;
            lik->bodovi -= 50;
            printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n$$Cestitam! Postigli ste %d. lvl!$$\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", lik->level);
        }
    }
    else {
        lik->zdravlje = 0;
        printf("Sramota! >:(\n%s te porazio. Vise srece sljedeci put!\n-------------------\n", neprijatelj->ime);
    }
}

void treniraj(const Lik* const lik) {
    printf("\nSto zelis trenirati?\n");
    printf("1. Zdravlje\n");
    printf("2. Snagu\n");
    printf("3. Nista, mlahonja sam");

    int izbor;
    printf("\n\t\t\t\t\tOdabirem: ");
    scanf("%d", &izbor);

    switch (izbor) {
    case 1:
        trenirajZdravlje(lik);
        break;
    case 2:
        trenirajSnagu(lik);
        break;
    case 3:
        break;
    default:
        printf("Mozes odabrati samo 1 za Zdravlje ili 2 za Snagu!\n");
        break;
    }
}


void trenirajZdravlje(Lik* const lik) {
    lik->zdravlje += 25;
    printf("\nMalo si odrijemao. Tvoje se zdravlje povecalo za +10\n");
}

void trenirajSnagu(Lik* const lik) {
    int maxSnaga = lik->level * 5;

    if (lik->snaga < maxSnaga) {
        lik->snaga += 1;
        printf("\nDigao si 300 u benchu, snaga ti je povecana za +1\n");
    }
    else {
        printf("\nVec si dostigao maksimalnu snagu za ovaj level!\n");
    }
}


void spremiHeroja(const Lik* const lik) {
    FILE* file;
    file = fopen("lik.txt", "w");

    if (file == NULL) {
        printf("Greska pri otvaranju datoteke za pisanje.\n");
        return;
    }

    fprintf(file, "%s\n%d\n%d\n%d\n%d\n", lik->ime, lik->level, lik->zdravlje, lik->bodovi, lik->snaga);

    fclose(file);

    printf("Lik je uspjesno spremljen.\n");
}

void ucitajLika(Lik* lik) {
    FILE* file;
    file = fopen("lik.txt", "r");

    if (file == NULL) {
        printf("Greska pri otvaranju datoteke za citanje.\n");
        return;
    }

    fscanf(file, "%s%d%d%d%d", lik->ime, &lik->level, &lik->zdravlje, &lik->bodovi, &lik->snaga);

    fclose(file);

    printf("%s je uspjesno ucitan.\n", lik->ime);
}


void obradiGresku() {
    greska;
}
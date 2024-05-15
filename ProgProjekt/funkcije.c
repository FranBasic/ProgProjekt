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
    printf("6. Izbrisi lika\n");
    printf("7. Prikazi sve likove\n");
    printf("8. Sortiraj likove\n");
    printf("9. Kreiraj Novog lika\n");
    printf("10. Izlaz iz igre\n");
}

void createNewCharacter(Lik* lik) {

    //lik = [ "Bezimeni", 1, 100, 10, 0 ];

    printf("Unesite ime svog lika: ");
    scanf("%24[^\n]", lik->ime);
    getchar();
    //lik->level = 1;
    //lik->zdravlje = 100;
    //lik->snaga = 10;
    //lik->bodovi = 0;
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
    lik->zdravlje += 50;
    printf("\nMalo si odrijemao. Tvoje se zdravlje povecalo za +50\n");
}


void trenirajSnagu(Lik* const lik) {
    int maxSnaga = lik->level * 5;

    if (lik->snaga < (maxSnaga + 10)) {
        lik->snaga += 1;
        printf("\nDigao si 300 u benchu, snaga ti je povecana za +1\n");
    }
    else {
        printf("\nVec si dostigao maksimalnu snagu za ovaj level!\n");
    }
}

void spremiHeroja(const Lik* const lik, int slot) {
    FILE* file = fopen("likovi.txt", "r+b");
    if (file == NULL) {
        file = fopen("likovi.txt", "w+b");
        if (file == NULL) {
            printf("Greska pri otvaranju datoteke za pisanje.\n");
            return;
        }
    }

    Lik* temp = (Lik*)calloc(1, sizeof(Lik));
    if (temp == NULL) {
        perror("Greska pri alokaciji memorije.\n");
        fclose(file);
        return;
    }

    memcpy(temp, lik, sizeof(Lik));

    fseek(file, slot * sizeof(Lik), SEEK_SET);
    fwrite(temp, sizeof(Lik), 1, file);

    free(temp);

    fclose(file);
    printf("Lik je uspjesno spremljen u spremnik %d.\n", slot + 1);
}

void ucitajLika(Lik* lik, int slot) {
    FILE* file = fopen("likovi.txt", "rb");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke za citanje.\n");
        return;
    }

    fseek(file, slot * sizeof(Lik), SEEK_SET);

    Lik temp;
    size_t bytesRead = fread(&temp, sizeof(Lik), 1, file);
    if (bytesRead != 1 || temp.ime[0] == '\0') {
        printf("Prazan slot.\n");
    }
    else {
        *lik = temp;
        printf("%s je uspjesno ucitan iz spremnika %d.\n", lik->ime, slot + 1);
    }

    fclose(file);
}

void napraviNovogLika(Lik* lik) {
    if (lik == NULL) {
        printf("Greska pri kreiranju lika.\n");
        return;
    }

    printf("\n-------------------\n*** Kreiranje novog lika ***\n");
    printf("Unesite ime: ");
    getchar();  // To consume any leftover newline character
    scanf("%24[^\n]", lik->ime);

    // Set default values for the new character
    lik->level = 1;
    lik->zdravlje = 100;
    lik->snaga = 10;
    lik->bodovi = 0;

    printf("\n%s je uspjesno kreiran!\n", lik->ime);

}

void izbrisiLika(int slot) {
    FILE* file = fopen("likovi.txt", "r+b");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke za pisanje.\n");
        return;
    }

    Lik prazniLik = { "", 0, 0, 0, 0 };
    fseek(file, slot * sizeof(Lik), SEEK_SET);
    fwrite(&prazniLik, sizeof(Lik), 1, file);

    fclose(file);
    printf("Slot %d je izbrisan.\n", slot + 1);
}

void prikaziSveLikove() {
    FILE* file = fopen("likovi.txt", "rb");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke za citanje.\n");
        return;
    }

    Lik lik;
    for (int i = 0; i < 3; ++i) {
        fseek(file, i * sizeof(Lik), SEEK_SET);
        fread(&lik, sizeof(Lik), 1, file);
        if (lik.ime[0] != '\0') {
            printf("\n*** Spremnik %d ***\n", i + 1);
            printf("Ime: %s\n", lik.ime);
            printf("Level: %d\n", lik.level);
            printf("Zdravlje: %d\n", lik.zdravlje);
            printf("Snaga: %d\n", lik.snaga);
            printf("Bodovi: %d\n", lik.bodovi);
        }
        else {
            printf("\nSpremnik %d je prazan.\n", i + 1);
        }
    }

    fclose(file);
}

int compareByLevel(const void* a, const void* b) {
    Lik* likA = (Lik*)a;
    Lik* likB = (Lik*)b;
    return likB->level - likA->level;
}

void sortirajLikove() {
    FILE* file = fopen("likovi.txt", "rb+");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke za citanje.\n");
        return;
    }

    Lik likovi[3];
    for (int i = 0; i < 3; ++i) {
        fseek(file, i * sizeof(Lik), SEEK_SET);
        fread(&likovi[i], sizeof(Lik), 1, file);
    }

    qsort(likovi, 3, sizeof(Lik), compareByLevel);

    for (int i = 0; i < 3; ++i) {
        fseek(file, i * sizeof(Lik), SEEK_SET);
        fwrite(&likovi[i], sizeof(Lik), 1, file);
    }

    fclose(file);
    printf("Likovi su uspjesno sortirani prema levelu.\n");
}

void obradiGresku() {
    greska;
}
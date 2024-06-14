#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

void ispisi_izbornik() {
    printf("\n\tODABERI POTEZ:\n");
    printf("1. Borba\n");
    printf("2. Stanje\n");
    printf("3. Trening\n");
    printf("4. Spremi lika\n");
    printf("5. Ucitaj slot\n");
    printf("6. Izbrisi slot\n");
    printf("7. Napravi novog lika\n");
    printf("8. Pretrazi slot\n");
    printf("9. Prikazi sve slotove\n");
    printf("10. Sortiraj likove\n");
    printf("11. Izlaz iz igre\n");
    printf("\n\t\t\t\t\tOdabirem: ");
}

void start(const Lik* const lik) {
    if (lik == NULL) {
        perror("Greska ucitavanja lika.\n");
        return;
    }

    printf("\n-------------------\nUlazis u FERIT u potrazi za suparnikom...\n");

    Neprijatelj neprijatelji[] = {
        {"Kostur Bivseg Studenta", 1, 30, 5},
        {"Grdosija Mrchella", 2, 40, 10},
        {"Carobnjak Shoyo", 3, 50, 15}
    };

    int broj_neprijatelja = sizeof(neprijatelji) / sizeof(neprijatelji[0]);
    int indeks = rand() % broj_neprijatelja;
    Neprijatelj* neprijatelj = &neprijatelji[indeks];

    printf("Uh Oh! Izazvao te %s, level %d!\n", neprijatelj->ime, neprijatelj->level);
    napadni_neprijatelja(lik, neprijatelj);
}

void napadni_neprijatelja(Lik* const lik, Neprijatelj* const neprijatelj) {
    printf("\nUlazis u borbenu poziciju...\n");

    if (lik == NULL || neprijatelj == NULL) {
        perror("Greska kod napadanja.\n");
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
            printf("20 bodova!\n-------------------\n\n");
            lik->bodovi += 20;
            break;
        case 2:
            printf("30 bodova!\n-------------------\n\n");
            lik->bodovi += 30;
            break;
        case 3:
            printf("40 bodova!\n-------------------\n\n");
            lik->bodovi += 40;
            break;
        default:
            break;
        }

        if (lik->bodovi >= 100) {
            lik->level++;
            lik->bodovi -= 100;
            printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n$$ Cestitam! Postigli ste %d. lvl! $$\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", lik->level);
        }
    }
    else {
        lik->zdravlje = 0;
        printf("Sramota! >:(\n%s te porazio. Vise srece sljedeci put!\n-------------------\n", neprijatelj->ime);
    }
}

void prikazi_stanje(const Lik* const lik) {
    if (lik == NULL) {
        perror("Greska ucitavanja lika.\n");
        return;
    }

    printf("\n-------------------\n*** Stanje lika ***\n");
    printf("Ime: %s\n", lik->ime);
    printf("Level: %d\n", lik->level);
    printf("Zdravlje: %d\n", lik->zdravlje);
    printf("Snaga: %d\n", lik->snaga);
    printf("Bodovi: %d\n-------------------\n", lik->bodovi);
}

void treniraj(const Lik* const lik) {
    printf("\nSta zelis trenirati?\n");
    printf("1. Zdravlje\n");
    printf("2. Snagu\n");
    printf("3. Nista, mlahonja sam");

    printf("\n\t\t\t\t\tOdabirem: ");

    if (scanf("%d", &izbor2) == 1) {
        while (getchar() != '\n');
    }
    else {
        printf("Unesi broj!\n");
        return;
    }

    switch (izbor2) {
    case ZDRAVLJE:
        treniraj_zdravlje(lik);
        break;
    case SNAGA:
        treniraj_snagu(lik);
        break;
    case IZLAZ_TRENING:
        break;
    default:
        printf("Mozes odabrati samo 1 za Zdravlje ili 2 za Snagu!\n");
        break;
    }
}

void treniraj_zdravlje(Lik* const lik) {
    if (lik == NULL) {
        perror("Greska kod treniranja.\n");
        return;
    }

    int oporavak = (MAX_ZDRAVLJE / 4);

    if (lik->zdravlje < MAX_ZDRAVLJE) {
        lik->zdravlje += oporavak;
        if (lik->zdravlje > MAX_ZDRAVLJE) {
            lik->zdravlje = MAX_ZDRAVLJE;
        }
        printf("\nMalo si odrijemao. Tvoje se zdravlje povecalo za +%d\n", oporavak);
    }
    else {
        lik->snaga -= 1;
        printf("\nProveo si cijeli dan u krevetu, snaga ti je pala za -1\n");

        if (lik->snaga < MIN_SNAGA){
            lik->snaga = MIN_SNAGA;
        }
    }
}

void treniraj_snagu(Lik* const lik) {
    if (lik == NULL) {
        printf("Greska kod treniranja.\n");
        return;
    }

    if (lik->snaga < MAX_SNAGA) {
        lik->snaga += 1;
        printf("\nDigao si 300 u benchu, snaga ti je povecana za +1\n");
    }
    else {
        printf("\nVec si dostigao maksimalnu snagu (%d) za level %d!\n", MAX_SNAGA, lik->level);
    }
}

void spremi_lika(Lik* const lik, int slot) {
    char* filename;

    if (slot == 0) {
        filename = "slot1.txt";
    }
    else if (slot == 1) {
        filename = "slot2.txt";
    }
    else {
        filename = "slot3.txt";
    }

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Greska prilikom otvaranja datoteke za spremanje.\n");
        return;
    }

    fwrite(lik->ime, sizeof(char), IME_MAX, file);
    fwrite(&lik->level, sizeof(int), 1, file);
    fwrite(&lik->zdravlje, sizeof(int), 1, file);
    fwrite(&lik->snaga, sizeof(int), 1, file);
    fwrite(&lik->bodovi, sizeof(int), 1, file);

    fclose(file);
    printf("Lik je uspjesno spremljen u slot %d.\n", slot + 1);
}

void ucitaj_lika(Lik* lik, int slot) {
    char* filename;
    if (slot == 0) {
        filename = "slot1.txt";
    }
    else if (slot == 1) {
        filename = "slot2.txt";
    }
    else {
        filename = "slot3.txt";
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Greska prilikom otvaranja datoteke - ucitavanje lika.\n");
        return;
    }

    fread(lik->ime, sizeof(char), IME_MAX, file);
    fread(&lik->level, sizeof(int), 1, file);
    fread(&lik->zdravlje, sizeof(int), 1, file);
    fread(&lik->snaga, sizeof(int), 1, file);
    fread(&lik->bodovi, sizeof(int), 1, file);

    fclose(file);

    printf("%s je uspjesno ucitan iz slota %d.\n", lik->ime, slot + 1);
}

void izbrisi_lika(int slot) {
    char da = 0;
    printf("Zelite li izbrisati lika u slotu %d?\nD za da ili N za ne\n", slot + 1);

    while(1){
        scanf(" %c", &da);
        while (getchar() != '\n');

        if (da == 'd' || da == 'D') {
            char* filename;
            if (slot == 0) {
                filename = "slot1.txt";
            }
            else if (slot == 1) {
                filename = "slot2.txt";
            }
            else {
                filename = "slot3.txt";
            }

            remove(filename);

            printf("Slotu %d je izbrisan.\n", slot + 1);
            return;
        }
        else if (da == 'n' || da == 'N') {
            printf("Brisanje lika je otkazano.\n");
            return;
        }
        else {
            printf("Neispravan unos.\nD za da ili N za ne\n");
        }
    }
}

void napravi_novog_lika(Lik* lik) {
    if (lik == NULL) {
        perror("Greska kod pravljenja lika.\n");
        return;
    }

    free(lik->ime);
    lik->ime = (char*)calloc(IME_MAX, sizeof(char));
    if (lik->ime == NULL) {
        perror("Greska memorije - pravljenje novog lika.");
        return;
    }

    lik->level = 1;
    lik->zdravlje = 100;
    lik->snaga = 10;
    lik->bodovi = 0;

    printf("\n-------------------\n*** Kreiranje novog lika ***\n");
    printf("Unesite ime: ");
    getchar();
    scanf("%24[^\n]", lik->ime);
    getchar();

    printf("\n%s je uspjesno kreiran!\n", lik->ime);
}

void pretrazi_slot_og(int slot) {
    char* filename;
    if (slot == 0) {
        filename = "slot1.txt";
    }
    else if (slot == 1) {
        filename = "slot2.txt";
    }
    else if (slot == 2) {
        filename = "slot3.txt";
    }
    else {
        printf("Krivi unos.\n");
        return;
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("\nSlot %d ne postoji.\n", slot + 1);
        return;
    }

    Lik temp;
    temp.ime = (char*)calloc(IME_MAX, sizeof(char));
    if (temp.ime == NULL) {
        perror("Greska memorije - pretrazivanje slota.");
        return;
    }

    fread(temp.ime, sizeof(char), IME_MAX, file);
    fread(&temp.level, sizeof(int), 1, file);
    fread(&temp.zdravlje, sizeof(int), 1, file);
    fread(&temp.snaga, sizeof(int), 1, file);
    fread(&temp.bodovi, sizeof(int), 1, file);

    fclose(file);

    printf("\n-------------------\n*** Slot %d ***\n", slot + 1);
    printf("Ime: %s\n", temp.ime);
    printf("Level: %d\n", temp.level);
    printf("Zdravlje: %d\n", temp.zdravlje);
    printf("Snaga: %d\n", temp.snaga);
    printf("Bodovi: %d\n", temp.bodovi);

    free(temp.ime);
}

void prikazi_sve_likove() {
    Lik likovi[BROJ_LIKOVA];

    for (int i = 0; i < BROJ_LIKOVA; i++) {
        likovi[i].ime = (char*)calloc(IME_MAX, sizeof(char));
        if (likovi[i].ime == NULL) {
            perror("Greska memorije - inicijalizacija lika.");
            return;
        }
        pretrazi_slot_og(i, &likovi[i]);
    }
}

void sortiranje_likova() {
    Lik likovi[BROJ_LIKOVA];

    for (int i = 0; i < BROJ_LIKOVA; i++) {
        likovi[i].ime = (char*)calloc(IME_MAX, sizeof(char));
        if (likovi[i].ime == NULL) {
            perror("Greska memorije - inicijalizacija lika.");
            return;
        }
        pretrazi_slot_sort(i, &likovi[i]);
    }

    sortiraj_likove(likovi, BROJ_LIKOVA);

    printf("\n-------------------\n*** Likovi sortirani po levelu ***\n");
    for (int i = 0; i < BROJ_LIKOVA; i++) {
        if (likovi[i].level > 0) {
            printf("Level: %d, Ime: %s\n", likovi[i].level, likovi[i].ime);
        }
        free(likovi[i].ime);
    }
}
void pretrazi_slot_sort(int slot, Lik* lik) {
    char* filename;
    if (slot == 0) {
        filename = "slot1.txt";
    }
    else if (slot == 1) {
        filename = "slot2.txt";
    }
    else if (slot == 2) {
        filename = "slot3.txt";
    }
    else {
        printf("Krivi unos.\n");
        return;
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Slot %d ne postoji.\n", slot + 1);
        return;
    }

    fread(lik->ime, sizeof(char), IME_MAX, file);
    fread(&lik->level, sizeof(int), 1, file);
    fread(&lik->zdravlje, sizeof(int), 1, file);
    fread(&lik->snaga, sizeof(int), 1, file);
    fread(&lik->bodovi, sizeof(int), 1, file);

    fclose(file);
}
void sortiraj_likove(Lik* likovi, int broj_likova) {
    qsort(likovi, broj_likova, sizeof(Lik), usporedi_levele);
}
int usporedi_levele(const void* a, const void* b) {
    Lik* lik1 = (Lik*)a;
    Lik* lik2 = (Lik*)b;
    return (lik2->level - lik1->level);
}

void logo() {
    blue
    printf("                         ########                      \n");
    printf("                      ####  ||  ####                   \n");
    printf("                  ####      ||      ####               \n");
    printf("                ###         ||         ####            \n");
    printf("            #####==         ||         ==####          \n");
    printf("        #####   ||  ===     ||     ===  ||  #####      \n");
    printf("      ###       ||     ===  "); red printf("##"); blue printf("  ===     ||      ###\n");
    printf("   ###          ||        ");red printf("####"); blue printf("==        ||         ### \n");
    printf("   ##===        ||     "); red printf("#######"); blue printf("  ==      ||      ====## \n");
    printf("   ##    ===    || "); red printf("###########"); blue printf("     ==   ||   ===    ## \n");
    printf("   ##       === "); red printf("##############"); blue printf("        = ## =        ## \n");
    printf("   ##          ="); red printf("#### "); reset printf("IZLAZ"); red printf(" ###"); blue printf("        ####=         ## \n");
    printf("   ##       === "); red printf("##############"); blue printf("     ####### ===      ## \n");
    printf("   ##   ===     "); red printf("##### "); reset printf("IZ"); red printf(" #####"); blue printf("  ##########    ===   ## \n");
    printf("   ##==         "); red printf("##############"); blue printf("############        ==## \n");
    printf("   ##==         "); red printf("###########"); blue printf(" ##############        ==## \n");
    printf("   ##   ===     "); red printf("########    "); blue printf("#### "); reset printf("IGRE"); blue printf(" ####    ===   ## \n");
    printf("   ##       === "); red printf("#####"); blue printf("       ############## ==       ## \n");
    printf("   ##         =="); red printf("##"); blue printf("=         ##############=         ## \n");
    printf("   ##      ===  ||  ==      ########### || ===      ## \n");
    printf("   ##   ===     ||    ===   ########    ||    ===   ## \n");
    printf("   ##===        ||       == #####       ||       ===## \n");
    printf("   ###          ||        ==###==       ||         ### \n");
    printf("      ####      ||    ====  ||   ==     ||     ####    \n");
    printf("          ###   || ===      ||     ===  ||  ###        \n");
    printf("             ####==         ||        ==####           \n");
    printf("                ####        ||       ####              \n");
    printf("                    ###     ||    ###                  \n");
    printf("                       ###########                     \n"); reset
    printf("      Fran Basic          "); blue printf("#####"); reset printf("            SR-1        \n");
}
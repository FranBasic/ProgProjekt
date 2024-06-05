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
    printf("7. Kreiraj lika\n");
    printf("8. Pretrazi slot\n");
    printf("9. Prikazi sve slotove\n");
    printf("10. Sortiraj likove\n");
    printf("11. Izlaz iz igre\n");
}

void zapocni_igru(const Lik* const lik) {
    if (lik == NULL) {
        printf("Greska ucitavanja lika.\n");
        return;
    }

    printf("\n-------------------\nUlazis u FERIT u potrazi za suparnikom...\n");

    Neprijatelj neprijatelji[] = { {"Kostur Bivseg Studenta", 1, 30, 5}, {"Grdosija Mrchella", 2, 40, 10}, {"Carobnjak Shoyo", 3, 50, 15} };
    int broj_neprijatelja = sizeof(neprijatelji) / sizeof(neprijatelji[0]);

    int indeks = rand() % broj_neprijatelja;
    Neprijatelj* neprijatelj = &neprijatelji[indeks];

    printf("Uh Oh! Izazvao te %s, level %d!\n", neprijatelj->ime, neprijatelj->level);
    napadni_neprijatelja(lik, neprijatelj);
}

void napadni_neprijatelja(Lik* const lik, Neprijatelj* const neprijatelj) {
    printf("\nUlazis u borbenu poziciju...\n");

    if (lik == NULL || neprijatelj == NULL) {
        printf("Greska kod napadanja.\n");
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
            lik->bodovi += 20;
            break;
        case 2:
            printf("15 bodova!\n-------------------\n\n");
            lik->bodovi += 30;
            break;
        case 3:
            printf("20 bodova!\n-------------------\n\n");
            lik->bodovi += 40;
            break;
        default:
            break;
        }

        if (lik->bodovi >= 100) {
            lik->level++;
            lik->bodovi -= 100;
            printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n$$Cestitam! Postigli ste %d. lvl!$$\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", lik->level);
        }
    }
    else {
        lik->zdravlje = 0;
        printf("Sramota! >:(\n%s te porazio. Vise srece sljedeci put!\n-------------------\n", neprijatelj->ime);
    }
}

void prikazi_stanje(const Lik* const lik) {
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

void treniraj(const Lik* const lik) {
    printf("\nSto zelis trenirati?\n");
    printf("1. Zdravlje\n");
    printf("2. Snagu\n");
    printf("3. Nista, mlahonja sam");

    //static enum Izbor2 izbor2;

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
    default:                                     //pogresan unos nakon tocnog unosa ponovi radnju tocnog unosa
        printf("Mozes odabrati samo 1 za Zdravlje ili 2 za Snagu!\n");
        break;
    }
}

void treniraj_zdravlje(Lik* const lik) {
    int oporavak = (MAX_ZDRAVLJE / 4);

    if (lik->zdravlje < MAX_ZDRAVLJE) {
        lik->zdravlje += oporavak;
        if (lik->zdravlje > MAX_ZDRAVLJE) {
            lik->zdravlje = MAX_ZDRAVLJE;
        }
        printf("\nMalo si odrijemao. Tvoje se zdravlje povecalo za +%d\n", oporavak);
    }
    else {
        lik->snaga -= 2;
        printf("\nProveo si cijeli dan u krevetu, snaga ti je pala za -2\n");

        if (lik->snaga < MIN_SNAGA){
            lik->snaga = MIN_SNAGA;
        }
    }
}

void treniraj_snagu(Lik* const lik) {
    if (lik->snaga < MAX_SNAGA) {
        lik->snaga += 1;
        printf("\nDigao si 300 u benchu, snaga ti je povecana za +1\n");
    }
    else {
        printf("\nVec si dostigao maksimalnu snagu (%d) za level %d!\n", MAX_SNAGA, lik->level);
    }
}

void spremi_lika(const Lik* const lik, int slot) {
    FILE* file = fopen("likovi.txt", "r+b");
    if (file == NULL) {
        file = fopen("likovi.txt", "w+b");
        if (file == NULL) {
            perror("Greska pri otvaranju datoteke - spremanje lika.\n");
            return;
        }
    }

    Lik* temp = (Lik*)calloc(1, sizeof(Lik));
    if (temp == NULL) {
        perror("Greska pri alokaciji memorije - spremanje lika.\n");
        fclose(file);
        return;
    }

    memcpy(temp, lik, sizeof(Lik));

    fseek(file, slot * sizeof(Lik), SEEK_SET);
    fwrite(temp, sizeof(Lik), 1, file);

    free(temp);

    fclose(file);
    printf("%s je uspjesno spremljen u slot %d.\n",lik->ime, slot + 1);
}

void ucitaj_lika(Lik* lik, int slot) {
    FILE* file = fopen("likovi.txt", "rb");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke za citanje - ucitavanje lika.\n");
        return;
    }

    fseek(file, slot * sizeof(Lik), SEEK_SET);

    Lik temp;
    size_t bytes_read = fread(&temp, sizeof(Lik), 1, file);
    if (bytes_read != 1 || temp.ime[0] == '\0') {
        printf("Prazan slot.\n");
    }
    else {
        *lik = temp;
        printf("%s je uspjesno ucitan iz slota %d.\n", lik->ime, slot + 1);
    }

    fclose(file);
}

void izbrisi_lika(int slot) {
    char da = 0;
    printf("Zelite li izbrisati lika u slotu %d?\nD za da ili N za ne\n", slot + 1);

    while(1){
        scanf(" %c", &da);

        while (getchar() != '\n');

        if (da == 'd' || da == 'D') {
            FILE* file = fopen("likovi.txt", "r+b");
            if (file == NULL) {
                perror("Greska pri otvaranju datoteke - brisanje lika.\n");
                return;
            }

            Lik prazni_lik = { "", 0, 0, 0, 0 };
            fseek(file, slot * sizeof(Lik), SEEK_SET);
            fwrite(&prazni_lik, sizeof(Lik), 1, file);

            fclose(file);
            printf("Lik u slotu %d je izbrisan.\n", slot + 1);
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
        printf("Greska pri kreiranju lika.\n");
        return;
    }

    printf("\n-------------------\n*** Kreiranje novog lika ***\n");
    printf("Unesite ime: ");
    getchar();
    scanf("%24[^\n]", lik->ime);

    lik->level = 1;
    lik->zdravlje = 100;
    lik->snaga = 10;
    lik->bodovi = 0;

    printf("\n%s je uspjesno kreiran!\n", lik->ime);
}

void pretrazi_slot(int slot) {
    if (slot < 0 || slot >= BROJ_LIKOVA) {
        printf("Neispravan broj slota.\n");
        return;
    }

    FILE* file = fopen("likovi.txt", "rb");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke - pretrazivanje slota.\n");
        return;
    }

    fseek(file, slot * sizeof(Lik), SEEK_SET);

    Lik lik;
    size_t trazeni_lik = fread(&lik, sizeof(Lik), 1, file);
    if (trazeni_lik != 1 || lik.ime[0] == '\0') {
        printf("Prazan slot.\n");
    }
    else {
        printf("\n*** Slot %d ***\n", slot + 1);
        printf("Ime: %s\n", lik.ime);
        printf("Level: %d\n", lik.level);
        printf("Zdravlje: %d\n", lik.zdravlje);
        printf("Snaga: %d\n", lik.snaga);
        printf("Bodovi: %d\n", lik.bodovi);
    }

    fclose(file);
}

void prikazi_sve_likove() {
    FILE* file = fopen("likovi.txt", "rb");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke - prikazivanje svih slotova.\n");
        return;
    }

    Lik lik;
    for (int i = 0; i < BROJ_LIKOVA; ++i) {
        fseek(file, i * sizeof(Lik), SEEK_SET);
        fread(&lik, sizeof(Lik), 1, file);
        if (lik.ime[0] != '\0') {
            printf("\n-------------------\n*** Slot %d ***\n", i + 1);
            printf("Ime: %s\n", lik.ime);
            printf("Level: %d\n", lik.level);
            printf("Zdravlje: %d\n", lik.zdravlje);
            printf("Snaga: %d\n", lik.snaga);
            printf("Bodovi: %d\n", lik.bodovi);
        }
        else {
            printf("\n-------------------\nSlot %d je prazan.\n", i + 1);
        }
    }

    fclose(file);
}

int usporedi_levele(const void* a, const void* b) {
    Lik* lik_A = (Lik*)a;
    Lik* lik_B = (Lik*)b;
    return lik_B->level - lik_A->level;
}

void sortiraj_likove() {
    FILE* file = fopen("likovi.txt", "rb+");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke - sortiranje.\n");
        return;
    }

    Lik likovi[BROJ_LIKOVA];
    for (int i = 0; i < BROJ_LIKOVA; ++i) {
        fseek(file, i * sizeof(Lik), SEEK_SET);
        fread(&likovi[i], sizeof(Lik), 1, file);
    }

    qsort(likovi, BROJ_LIKOVA, sizeof(Lik), usporedi_levele);

    for (int i = 0; i < BROJ_LIKOVA; ++i) {
        fseek(file, i * sizeof(Lik), SEEK_SET);
        fwrite(&likovi[i], sizeof(Lik), 1, file);
    }

    fclose(file);
    printf("Likovi su uspjesno sortirani prema levelu.\n");
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
    printf("   ##   ===     "); red printf("########    "); blue printf("## "); reset printf("PROGRAMA"); blue printf(" ##    ===   ## \n");
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
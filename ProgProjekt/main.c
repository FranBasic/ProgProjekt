#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funkcije.h"

#define NASLOV() printf("\t\t-----NASLOV IGRE-----\n\n")

int main() {
    srand((unsigned)time(NULL));

    Lik igrac = { "Lorem", 1, 100, 10, 0 };

    static enum Izbor izbor;

    NASLOV();

    printf("Unesite ime svog lika: ");
    scanf("%19[^\n]", igrac.ime);
    getchar();

    do {
        ispisiIzbornik();
        printf("\n\t\t\t\t\tOdabirem: ");

        if (scanf("%d", &izbor) != 1) {
            printf("\nUnesite broj!\n");
            while (getchar() != '\n');
            continue;
        }

        int slot;
        switch (izbor) {
        case ZAPOCNI_IGRU:                     //snake case za enum?
            zapocniIgru(&igrac);
            break;
        case PRIKAZI_STANJE:
            prikaziStanje(&igrac);
            break;
        case TRENIRAJ:
            treniraj(&igrac);
            break;
        case SPREMI_HEROJA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);
            if (slot >= 1 && slot <= 3) {
                spremiLika(&igrac, slot - 1);
            }
            else {
                printf("Neispravan broj spremnika.\n");
            }
            break;
        case UCITAJ_LIKA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);
            if (slot >= 1 && slot <= 3) {
                ucitajLika(&igrac, slot - 1);
            }
            else {
                printf("Neispravan broj spremnika.\n");
            }
            break;
        case IZBRISI_LIKA:
            printf("Unesite broj slota ( 1, 2 ili 3 ): ");
            scanf("%d", &slot);
            if (slot >= 1 && slot <= 3) {
                izbrisiLika(slot - 1);
            }
            else {
                printf("Neispravan broj spremnika.\n");
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
            printf("Izlaz!\n");
            break;
        default:
            printf("Taj izbor ne postoji!\n");
            break;
        }
    } while (izbor != IZLAZ);


    return 0;
}

  //........................: = : .......................  \n\
  //......................:*##### * : ...................  \n\
  //...................-####+:#:+####-:..................  \n\
  //...............:+*##*-:...#....-*##*+:...............  \n\
  //............-*###*:.......#.......:+###*-............  \n\
  //.........-#####*=:........#........:=*#####-.........  \n\
  //.....:+###*=:.+:.-++-.....#.....-++-..+:.-*###+:.....  \n\
  //..-*###+:.....+:.....=*=..#..=*=:.....+:....:+###*-..  \n\
  //:###+.........+:........-###=.........+:........+###-  \n\
  //:##==+=.......+:......-+###-++-.......+:......-++=*#-  \n\
  //:#*:...-*+....+:...=*######...:-*+....+:...+*-...:*#-  \n\
  //:#*:......:**-+:+##########.......-*+:*-**:......:*#-  \n\
  //:#*-........-+#############........:-##*-........:*#-  \n\
  //:#*:.....=*=:.*############.....:+####*::=*+:....:*#-  \n\
  //:#*:..+#-.....*############..:*#######*:....:**..:*#-  \n\
  //:###+:........*#######################*:.......:+###-  \n\
  //:##=++-.......*#########*=############*:......-++=##-  \n\
  //:#*:...=#-....*######*:...############*:...-#=...:*#-  \n\
  //:#*:......=*=-*##*+:......############*-=*=......:*#-  \n\
  //:#*:........-*##=.........#############*-........:*#-  \n\
  //:#*:.....-*+::+:.=*=......#########=:.+::+#-.....:*#-  \n\
  //:#*:..-*=.....+:....=*+:..#####*=.....+:....=*-:.:*#-  \n\
  //:##*+-........+:.......-++##+-........+:.......-+*##-  \n\
  //:###*=........+:.......=*=#=*=........+:.......=*###-  \n\
  //...=####=:....+:...:+*-...#...-*+:....+:....=####=...  \n\
  //......-+###+-:+:-++-......#......-++-:+:-+###*-......  \n\
  //.........:=####*:.........#.........:*####=:.........  \n\
  //.............=####+:......#......:+####=.............  \n\
  //................-+###+-...#...-+###+-................  \n\
  //...................:=###*+#+*###=:...................  \n\
  //.......................-*####-.......................  \n\
  //..........................:..........................  \n\
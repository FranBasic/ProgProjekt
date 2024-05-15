#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funkcije.h"

#define NASLOV() printf("\t\t-----NASLOV IGRE-----\n\n")

int main() {
    srand((unsigned)time(NULL));

    Lik igrac = { "Bezimeni", 1, 100, 10, 0 };

    static enum Izbor izbor;

    NASLOV();

    printf("Unesite ime svog lika: ");
    scanf("%19[^\n]", igrac.ime);
    getchar();

    do {
        ispisiIzbornik();
        printf("\n\t\t\t\t\tOdabirem: ");

        if (scanf("%d", &izbor) != 1) {
            printf("Unesite broj!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (izbor) { 
        case ZAPOCNI_IGRU:
            zapocniIgru(&igrac);
            break;
        case PRIKAZI_STANJE:
            prikaziStanje(&igrac);
            break;
        case TRENIRAJ:
            treniraj(&igrac);
            break;
        case SPREMI_HEROJA:
            spremiHeroja(&igrac);
            break;
        case UCITAJ_LIKA:
            ucitajLika(&igrac);
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
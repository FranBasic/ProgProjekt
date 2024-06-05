#define _CRT_SECURE_NO_WARNINGS

#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define ime_max 25
#define MAX_SNAGA (lik->level * 5) + 10
#define MIN_SNAGA 0
#define MAX_ZDRAVLJE 200
#define BROJ_LIKOVA 3

#define red printf("\033[1;31m");
#define blue printf("\033[0;34m");
#define reset printf("\033[0m");

static enum Izbor izbor;
static enum Izbor2 izbor2;

typedef struct {
    char ime[ime_max];
    int level;
    int zdravlje;
    int snaga;
    int bodovi;
} Lik;

typedef struct {
    char ime[ime_max];
    int level;
    int zdravlje;
    int snaga;
} Neprijatelj;

enum Izbor {
    ZAPOCNI_IGRU = 1,
    PRIKAZI_STANJE,
    TRENIRAJ,
    SPREMI_LIKA,
    UCITAJ_LIKA,
    IZBRISI_LIKA,
    NAPRAVI_NOVOG_LIKA,
    PRETRAZI_SLOT,
    PRIKAZI_SVE_LIKOVE,
    SORTIRAJ_LIKOVE,
    IZLAZ
};

enum Izbor2 {
    ZDRAVLJE = 1,
    SNAGA,
    IZLAZ_TRENING
};

void ispisi_izbornik();
void zapocni_igru(const Lik* const lik);
void napadni_neprijatelja(const Lik* const lik, Neprijatelj* const neprijatelj);
void prikazi_stanje(const Lik* const lik);
void treniraj(const Lik* const lik);
void treniraj_zdravlje(Lik* const lik);
void treniraj_snagu(Lik* const lik);
void spremi_lika(const Lik* const lik, int slot);
void ucitaj_lika(Lik* lik, int slot);
void napravi_novog_lika(Lik* lik);
void izbrisi_lika(int slot);
void pretrazi_slot(int slot);
void prikazi_sve_likove();
void sortiraj_likove();
void logo();

#endif
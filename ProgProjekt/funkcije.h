#define _CRT_SECURE_NO_WARNINGS

#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define IME_MAX 25
#define MAX_SNAGA (lik->level * 5) + 10
#define MIN_SNAGA 0
#define MAX_ZDRAVLJE 200
#define BROJ_LIKOVA 3

#define red printf("\033[1;31m");
#define blue printf("\033[0;34m");
#define reset printf("\033[0m");

extern int jedan;

typedef struct {
    char* ime;
    int level;
    int zdravlje;
    int snaga;
    int bodovi;
} Lik;

typedef struct {
    char ime[IME_MAX];
    int level;
    int zdravlje;
    int snaga;
} Neprijatelj;

enum Izbor {
    ZAPOCNI_IGRU = 1,
    PRIKAZI_STANJE,
    TRENIRAJ,
    SPREMI_LIKA,
    UCITAJ_LIKA,//5
    IZBRISI_LIKA,
    NAPRAVI_NOVOG_LIKA,
    PRETRAZI_SLOT,
    PRIKAZI_SVE_LIKOVE,
    SORTIRAJ_LIKOVE,//10
    PREIMENUJ_LIKA,
    IZLAZ
};

enum Izbor2 {
    ZDRAVLJE = 1,
    SNAGA,
    IZLAZ_TRENING
};

void ispisi_izbornik();
void start(const Lik* const lik);
void napadni_neprijatelja(const Lik* const lik, Neprijatelj* const neprijatelj);
void prikazi_stanje(const Lik* const lik);
void treniraj(const Lik* const lik);
void treniraj_zdravlje(Lik* const lik);
void treniraj_snagu(Lik* const lik);
void spremi_lika(Lik* const lik, int slot);
void ucitaj_lika(Lik* lik, int slot);
void napravi_novog_lika(Lik* lik);
void izbrisi_lika(int slot);
void pretrazi_slot_sort(int slot, Lik* lik);
void pretrazi_slot_og(int slot);
void prikazi_sve_likove();
void promjeni_ime(int slot, const char* novo_ime);
void sortiraj_likove(Lik* likovi, int broj_likova);
void sortiranje_likova();
int usporedi_levele(const void* a, const void* b);
void logo();

int usporedi_imena(const void*, const void* b);
Lik* pretrazi_lika(Lik* likovi, int broj_likova, const char* ime);
int ucitaj_sve_likove(Lik* likovi);

#endif
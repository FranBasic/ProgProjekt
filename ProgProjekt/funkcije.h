#define _CRT_SECURE_NO_WARNINGS

#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define imeMax 25

typedef struct {
    char ime[imeMax];
    int level;
    int zdravlje;
    int snaga;
    int bodovi;
} Lik;

typedef struct {
    char ime[imeMax];
    int level;
    int zdravlje;
    int snaga;
} Neprijatelj;

enum Izbor {
    ZAPOCNI_IGRU = 1,
    PRIKAZI_STANJE,
    TRENIRAJ,
    SPREMI_HEROJA,
    UCITAJ_LIKA,
    IZBRISI_LIKA,
    PRIKAZI_SVE_LIKOVE,
    SORTIRAJ_LIKOVE,
    NAPRAVI_NOVOG_LIKA,
    IZLAZ
};                                 //poredati izbore

void ispisiIzbornik();
void napraviNovogLika(Lik* lik);
void zapocniIgru(const Lik* const lik);
void prikaziStanje(const Lik* const lik);
void treniraj(const Lik* const lik);
void trenirajZdravlje(Lik* const lik);
void trenirajSnagu(Lik* const lik);
void napadniNeprijatelja(const Lik* const lik, Neprijatelj* const neprijatelj);
void spremiHeroja(const Lik* const lik, int slot);
void ucitajLika(Lik* lik, int slot);
void izbrisiLika(int slot);
void prikaziSveLikove();
void sortirajLikove();

#endif
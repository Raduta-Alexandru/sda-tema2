#ifndef _HOME_ALEXANDRU_FACULTATE_SDA_TEME_TEMA2_CHECKER_STRUCTURI_H_
#define _HOME_ALEXANDRU_FACULTATE_SDA_TEME_TEMA2_CHECKER_STRUCTURI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct satelit {
    int freq;
    char* nume;
} TSatelit;

typedef int (*TComparaSateliti)(TSatelit*, TSatelit*);

typedef struct nodSatelit {
    TSatelit* info;
    struct nodSatelit* left;
    struct nodSatelit* right;
} TNodSatelit, *TArbSatelit;

typedef struct satelitHeap {
    int numMax, numSateliti;
    TArbSatelit* vectSatelite;
    TComparaSateliti comp;
} TSatelitHeap;

typedef struct nodPQueue {
    TArbSatelit arb;
    int nivel;
    struct nodPQueue* urm;
} TCelulaPQeueu, *TPQueue;

TSatelit* alocSatelit(int freq, char* nume);

void distrugeSatelit(TSatelit* satelit);

int compSateliti(TSatelit* satelit1, TSatelit* satelit2);

TSatelitHeap* alocHeap(int numMax, TComparaSateliti funcComp);

void distrugeHeap(TSatelitHeap **heap);

void pushUp(TSatelitHeap* heap, int poz);

void pushDown(TSatelitHeap* heap, int poz);

void inserareHeap(TSatelitHeap* heap, TArbSatelit nod);

TArbSatelit eliminareHeap(TSatelitHeap* heap);

TArbSatelit alocNodArb(TSatelit* satelit);

TArbSatelit creazaArbore(FILE* input);

void eliberareArbore(TArbSatelit* arb);

TPQueue alocaNodPQueue(TArbSatelit arb, int nivel);

void inserarePQueue(TPQueue* queue, TPQueue celula);

void afisarePQueue(TPQueue* queue, FILE* output);

void eliberarePQueue(TPQueue* queue);

void parcurgereLatimeArbore(TArbSatelit radacine, TPQueue* queue, int nivel);

void afisareArboreNivel(TArbSatelit radacina, FILE* output);

int apartineSubarbore(TArbSatelit arb, char* nume);

TArbSatelit apartineSubarboreVect(TArbSatelit arb, char** sateliti, int numSat);

TArbSatelit gasesteNod(TArbSatelit arb, char* nume);

void extindeArbore(TArbSatelit arb, FILE* input);

void task1(FILE* input, FILE* output);
void task2(FILE* input, FILE* output);
void task3(FILE* input, FILE* output);
void task4(FILE* input, FILE* output);
void task5(FILE* input, FILE* output);

#endif  // _HOME_ALEXANDRU_FACULTATE_SDA_TEME_TEMA2_CHECKER_STRUCTURI_H_

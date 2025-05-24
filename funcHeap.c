#include "./structuri.h"

TSatelitHeap* alocHeap(int numMax, TComparaSateliti funcComp) {
    // aloc heapul
    TSatelitHeap* heap = malloc(sizeof(TSatelitHeap));
    // verific ca alocarea a functionat
    if (heap == NULL) {
        return NULL;
    }
    // aloc vectorul de arbori
    heap->vectSatelite = calloc(numMax, sizeof(TArbSatelit));
    // verific alocarea
    if (heap->vectSatelite == NULL) {
        free(heap);
        return NULL;
    }
    // imi atribui datele
    heap->numMax = numMax;
    heap->numSateliti = 0;
    heap->comp = funcComp;
    return heap;
}

void distrugeHeap(TSatelitHeap **heap) {
    free((*heap)->vectSatelite);
    free(*heap);
    *heap = NULL;
}

void pushUp(TSatelitHeap* heap, int poz) {
    // imi iau pozitia parintelui
    int parinte = (poz - 1) / 2;
    // cat timp nu este radacina si parintele > copil
    while ((poz != 0) &&
    (heap->comp(heap->vectSatelite[parinte]->info,
    heap->vectSatelite[poz]->info) > 0)) {
        // fac interschimbare intre tata si copil
        TArbSatelit aux = heap->vectSatelite[parinte];
        heap->vectSatelite[parinte] = heap->vectSatelite[poz];
        heap->vectSatelite[poz] = aux;
        // actualizez poz si parinte
        poz = parinte;
        parinte = (poz - 1) / 2;
    }
}

void pushDown(TSatelitHeap* heap, int poz) {
    // imi iau numarul de sateliti
    int numElemHeap = heap->numSateliti;
    // imi iau index pentru fiu stanga si fiu dreapta
    int stanga = 2 * poz + 1;
    int dreapta = stanga + 1;
    // verific daca mai exista un fiu in stanga
    while (stanga < numElemHeap) {
        int s = stanga;
        // verific daca mai exista un fiu in dreapta care este si mai mic
        if ((dreapta < numElemHeap) &&
        (heap->comp(heap->vectSatelite[s]->info,
        heap->vectSatelite[dreapta]->info) > 0)) {
            s = dreapta;
        }
        // verific daca trebuie interschimbati sau nu
        if (heap->comp(heap->vectSatelite[poz]->info,
            heap->vectSatelite[s]->info) <= 0) {
            break;
        } else {
            // ii interschimb
            TArbSatelit aux = heap->vectSatelite[poz];
            heap->vectSatelite[poz] = heap->vectSatelite[s];
            heap->vectSatelite[s] = aux;
            // actualizez poz si index pentru stanga si dreapta
            poz = s;
            stanga = 2 * poz + 1;
            dreapta = stanga + 1;
        }
    }
}

void inserareHeap(TSatelitHeap* heap, TArbSatelit nod) {
    // adaug nodul in heap
    heap->vectSatelite[heap->numSateliti] = nod;
    // incrementez numarul de sateliti
    heap->numSateliti++;
    // ordonez heapul
    pushUp(heap, heap->numSateliti - 1);
}

TArbSatelit eliminareHeap(TSatelitHeap* heap) {
    // imi iau cel mai mic element
    TArbSatelit elemMinim = heap->vectSatelite[0];
    // imi scad numarul de sateliti
    heap->numSateliti--;
    // pun ultimul satelit pe prima pozitie
    heap->vectSatelite[0] = heap->vectSatelite[heap->numSateliti];
    // ordonez heapul
    pushDown(heap, 0);
    return elemMinim;
}

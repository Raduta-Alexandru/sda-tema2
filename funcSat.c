#include "./structuri.h"

TSatelit* alocSatelit(int freq, char* nume) {
    // imi aloc spatiu pentru un satelit
    TSatelit* aux = malloc(sizeof(TSatelit));
    // verific ca a functionat alocarea
    if (aux == NULL) {
        return NULL;
    }
    // ii dau satelitului informatile
    aux->freq = freq;
    aux->nume = nume;
    return aux;
}

void distrugeSatelit(TSatelit* satelit) {
    // eliberez numele
    free(satelit->nume);
    free(satelit);
}

int compSateliti(TSatelit* satelit1, TSatelit* satelit2) {
    // imi iau satelitii
    TSatelit sat1 = *satelit1;
    TSatelit sat2 = *satelit2;
    // verific daca au frecvente diferite
    if (sat1.freq != sat2.freq) {
        return sat1.freq - sat2.freq;
    }
    // daca au frecventa egala, compar numele
    return strcmp(sat1.nume, sat2.nume);
}

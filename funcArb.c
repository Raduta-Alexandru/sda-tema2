#include "./structuri.h"

TArbSatelit alocNodArb(TSatelit* satelit) {
    TNodSatelit* aux = malloc(sizeof(TNodSatelit));
    // verific daca a functionat alocarea
    if (aux == NULL) {
        return NULL;
    }
    // ii dau nodului informatile
    aux->info = satelit;
    aux->left = NULL;
    aux->right = NULL;
    return aux;
}

TArbSatelit creazaArbore(FILE* input) {
    char linie[100];
    // imi iau numarul de sateliti
    fgets(linie, 100, input);
    int numarSateliti = atoi(linie);
    // imi aloc heapul
    TSatelitHeap* heap = alocHeap(numarSateliti, compSateliti);
    for (int i = 0; i < numarSateliti; i++) {
        // imi iau satelitul la care am ajuns
        fgets(linie, 100, input);
        // elimin \n
        if (strstr(linie, "\n")) {
            linie[strlen(linie) - 1] = '\0';
        }
        // imi iau pozitia unde incepe numele satelitului
        char* inceputNume = strstr(linie, " ") + 1;
        // imi iau frecventa satelitului
        int freq = atoi(linie);
        // copiez numele satelitului
        char* nume = strdup(inceputNume);
        // aloc satelitul
        TSatelit* sat = alocSatelit(freq, nume);
        // aloc nodul din arbore
        TArbSatelit nodSat = alocNodArb(sat);
        // adaug in heap
        inserareHeap(heap, nodSat);
    }
    while (heap->numSateliti != 1) {
        // imi scot fiul stang si drept
        TArbSatelit fiuStang = eliminareHeap(heap);
        TArbSatelit fiuDrept = eliminareHeap(heap);
        // imi calculez frecventa totala
        int freqParinte = fiuStang->info->freq + fiuDrept->info->freq;
        // imi iau numele din stanga
        char* numeStang = fiuStang->info->nume;
        // imi iau numele din dreapta
        char* numeDrept = fiuDrept->info->nume;
        // imi iau lungimea numelui total
        int lenNumeParinte = strlen(numeStang) + strlen(numeDrept);
        // aloc spatiu pentru nume si pentru terminator
        char* numeParinte = malloc(lenNumeParinte + 1);
        // pun la inceput numele din stanga
        strncpy(numeParinte, numeStang, strlen(numeStang));
        // pun numele drept de unde se termina numele stang
        strncpy(numeParinte + strlen(numeStang), numeDrept, strlen(numeDrept));
        // adaug '\0'
        numeParinte[lenNumeParinte] = '\0';
        TSatelit* satParinte = alocSatelit(freqParinte, numeParinte);
        TArbSatelit nodParinte = alocNodArb(satParinte);
        nodParinte->left = fiuStang;
        fiuStang->right = fiuDrept;
        inserareHeap(heap, nodParinte);
    }
    // arborele final este cel care a ramas la final in heap
    TArbSatelit arboreFinal = heap->vectSatelite[0];
    // imi eliberez heapul
    distrugeHeap(&heap);
    return arboreFinal;
}

void eliberareArbore(TArbSatelit* arb) {
    if (*arb == NULL) {
        return;
    }
    // eliberez recursiv
    eliberareArbore(&(*arb)->left);
    eliberareArbore(&(*arb)->right);
    // eliberez satelitii
    distrugeSatelit((*arb)->info);
    free(*arb);
    arb = NULL;
}

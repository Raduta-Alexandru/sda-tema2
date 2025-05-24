#include "./structuri.h"

void parcurgereLatimeArbore(TArbSatelit radacina, TPQueue* queue, int nivel) {
    // implementez parcurgerea SRD doar ca in loc sa afisez pun in queue
    if (radacina == NULL) {
        return;
    }
    // creez o variabila pentru a parcurge fratii
    TArbSatelit copil = radacina->left;
    // parcurg recursiv toti copiii
    while (copil) {
        parcurgereLatimeArbore(copil, queue, nivel + 1);
        copil = copil->right;
    }
    // adaug in queue nodul curent
    TPQueue aux = alocaNodPQueue(radacina, nivel);
    inserarePQueue(queue, aux);
}

void afisareArboreNivel(TArbSatelit radacina, FILE* output) {
    // imi fac o coada
    TPQueue* coadaParcurgere = malloc(sizeof(TPQueue));
    // verific daca a mers alocarea
    if (coadaParcurgere == NULL) {
        return;
    }
    // o initializez goala
    *coadaParcurgere = NULL;
    // parcurg in latime si adaug progresiv in coada
    parcurgereLatimeArbore(radacina, coadaParcurgere, 0);
    // afisez coada
    afisarePQueue(coadaParcurgere, output);
    // eliberez coada
    eliberarePQueue(coadaParcurgere);
}

int apartineSubarbore(TArbSatelit arb, char* nume) {
    // daca se ajunge pe NULL nu a fost gasit
    if (arb == NULL) {
        return 0;
    }
    // daca il gasesc returnez 1
    if (strcmp(arb->info->nume, nume) == 0) {
        return 1;
    }
    // altfel parcurg toti copiii pana cand ii gasesc un subarbore care
    // contine nodul cautat sau pana cand ii parcurg pe toti
    int apartineFrati = 0;
    arb = arb->left;
    while (arb && !apartineFrati) {
        apartineFrati = apartineSubarbore(arb, nume);
        arb = arb->right;
    }
    return apartineFrati;
}

TArbSatelit apartineSubarboreVect(TArbSatelit arb,
    char** sateliti, int numSat) {
    // vad cati copii are subarborele la care am ajuns
    int nrCopii = 0;
    // pentru toate parcurgerile voi folosi aux
    TArbSatelit aux = arb->left;
    if (aux) {
        nrCopii++;
        aux = aux->right;
    }
    while (aux) {
        nrCopii++;
        aux = aux->right;
    }
    // aloc un vector in care sa salvez cati din vectorul
    // de sateliti apartin fiecarui subarbore
    int* nrSateliti = calloc(nrCopii, sizeof(int));
    if (nrSateliti == NULL) {
        perror("Eroare la alocarea nrSateliti\n");
        return NULL;
    }
    for (int i = 0; i < numSat; i++) {
        // verific in care subarbore apartine
        aux = arb->left;
        // tin o variabila sa stiu la al catelea subarbore sunt
        int idCopil = 0;
        // cat timp mai sunt la un copil verific daca ii apartine lui
        while (aux) {
            // daca da, incrementez numarul de copii ai subarborelui
            // si trec la urmatorul copil
            if (apartineSubarbore(aux, sateliti[i])) {
                nrSateliti[idCopil]++;
                break;
            }
            idCopil++;
            aux = aux->right;
        }
    }
    // parcurg vectorul in care tin minte cati sateliti apartine fiecarui copil
    // daca unui subarbore ii apartine fiecare, continui recursiv
    // altfel inseamna ca am gasit parintele comun
    aux = arb->left;
    for (int i = 0; i < nrCopii; i++) {
        if (nrSateliti[i] == numSat) {
            // eliberez vectorul alocat
            free(nrSateliti);
            // intru in recursivitate
            return apartineSubarboreVect(aux, sateliti, numSat);
        }
        aux = aux->right;
    }
    // eliberez vectorul alocat si intorc parinitele comun
    free(nrSateliti);
    return arb;
}

TArbSatelit gasesteNod(TArbSatelit arb, char* nume) {
    // cand ajung la NULL opresc recursivitatea
    if (arb == NULL) {
        return NULL;
    }
    // daca am gasit nodul il returnez
    if (!strcmp(arb->info->nume, nume)) {
        return arb;
    }
    // pornesc recursivitatea pentru fiecare fiu
    TArbSatelit aux = arb->left;
    while (aux) {
        TArbSatelit gasit = gasesteNod(aux, nume);
        if (gasit) return gasit;
        aux = aux->right;
    }
    // daca nu gaseste nimic
    return NULL;
}

void extindeArbore(TArbSatelit arb, FILE* input) {
    // citesc cati arbori multicai o sa fie adaugati
    char linie[1001];
    fgets(linie, 1001, input);
    int nrArbAdaugati = atoi(linie);
    for (int i = 0; i < nrArbAdaugati; i++) {
        // imi iau legatura arborelui multicai de arborele binar
        fgets(linie, 1001, input);
        // elimin \n
        if (strstr(linie, "\n")) {
            linie[strlen(linie) - 1] = '\0';
        }
        TArbSatelit legaturaArbore = gasesteNod(arb, linie);
        // imi fac radacina arborelui multicai
        fgets(linie, 1001, input);
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
        // aloc radacina multicai
        TArbSatelit radacinaMulticai = alocNodArb(sat);
        // leg radacina de nodul de legatura
        TArbSatelit aux = legaturaArbore->left;
        // daca nu exista primul fiu, fac radacina primul fiu
        if (!aux) {
            legaturaArbore->left = radacinaMulticai;
        } else {
            // parcurg fratii, pana cand il gasesc pe ultimul
            while (aux->right) {
                aux = aux->right;
            }
            // moment in cara adaug radacina
            aux->right = radacinaMulticai;
        }
        // citesc numarul de noduri parinte din arborele multicai
        fgets(linie, 1001, input);
        int nrParintiArbMulticai = atoi(linie);
        for (int j = 0; j < nrParintiArbMulticai; j++) {
            // citesc numele parintelui
            fgets(linie, 1001, input);
            // elimin \n
            if (strstr(linie, "\n")) {
                linie[strlen(linie) - 1] = '\0';
            }
            // gasesc parintele
            TArbSatelit parinte = gasesteNod(legaturaArbore, linie);
            // citesc numarul de copii
            fgets(linie, 1001, input);
            int nrCopiiParinte = atoi(linie);
            for (int k = 0; k < nrCopiiParinte; k++) {
                // citesc copilul
                fgets(linie, 1001, input);
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
                // aloc nodul pentru copil
                TArbSatelit nodCopil = alocNodArb(sat);
                // leg copilul de parinte
                TArbSatelit aux = parinte->left;
                // daca nu exista primul fiu, fac copilul primul fiu
                if (!aux) {
                    parinte->left = nodCopil;
                } else {
                    // parcurg fratii, pana cand il gasesc pe ultimul
                    while (aux->right) {
                        aux = aux->right;
                    }
                    // moment in cara adaug copilul
                    aux->right = nodCopil;
                }
            }
        }
    }
}
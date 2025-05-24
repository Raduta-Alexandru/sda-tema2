#include "./structuri.h"

void task1(FILE* input, FILE* output) {
    // imi fac arborele
    TArbSatelit arbSat = creazaArbore(input);
    // afisez arborele in latime
    afisareArboreNivel(arbSat, output);
    // imi eliberez arborele
    eliberareArbore(&arbSat);
}

void task2(FILE* input, FILE* output) {
    // imi fac arborele
    TArbSatelit arbSat = creazaArbore(input);
    char linie[1001];
    // citesc numarul de codificari
    fgets(linie, 1001, input);
    // imi iau numarul de codificari
    int numCodificari = atoi(linie);
    // parcurg codificarile
    for (int i = 0; i < numCodificari; i++) {
        // iau codificarea
        fgets(linie, 1001, input);
        // incep din radacina
        TArbSatelit aux = arbSat;
        // pana la nu mai am drumuri
        for (int j = 0; linie[j] != '\n'; j++) {
            // trebuie sa merg cu un nivel mai jos
            aux = aux->left;
            // dar daca e 1 trebuia sa merg in dreapta, deci merg la frate
            if (linie[j] == '1') {
                aux = aux->right;
            }
            // afisez cand ajung la o frunza
            if (aux->left == NULL) {
                fprintf(output, "%s ", aux->info->nume);
                // resetez pentru a parcurge de la inceput
                aux = arbSat;
            }
        }
        fprintf(output, "\n");
    }
    eliberareArbore(&arbSat);
}

void task3(FILE* input, FILE* output) {
    // imi fac arborele
    TArbSatelit arbSat = creazaArbore(input);
    char linie[100];
    // citesc numarul de sateliti
    fgets(linie, 100, input);
    // imi iau numarul de sateliti
    int numSateliti = atoi(linie);
    // parcurg satelitii
    for (int i = 0; i < numSateliti; i++) {
        // imi iau numele satelitului
        fgets(linie, 100, input);
        // elimin \n din nume
        *strchr(linie, '\n') = '\0';
        // incep din varf
        TArbSatelit aux = arbSat;
        while (aux != NULL) {
            // merg pe fiul din stanga
            aux = aux->left;
            // verific daca satelitul cautat este in subarborele stang
            if (apartineSubarbore(aux, linie)) {
                fprintf(output, "0");
            } else {
                // daca nu este inseamna ca e descendent fiului drept
                fprintf(output, "1");
                aux = aux->right;
            }
            // daca am ajuns la destinatie iesim din while
            if (strcmp(aux->info->nume, linie) == 0) {
                break;
            }
        }
    }
    eliberareArbore(&arbSat);
}

void task4(FILE* input, FILE* output) {
    // imi fac arborele
    TArbSatelit arbSat = creazaArbore(input);
    char linie[16];
    // citesc satelitii pentru care trebuie sa gasesc parinitele comun
    fgets(linie, 16, input);
    int numSat = atoi(linie);
    // aloc un vector in care sa imi pastrez numele lor
    char** sateliti = malloc(numSat * sizeof(char*));
    if (sateliti == NULL) {
        perror("Eroare la alocarea numelor de sateliti\n");
        return;
    }
    for (int i = 0; i < numSat; i++) {
        // citesc satelitul la care am ajuns
        fgets(linie, 16, input);
        // elimin \n din nume
        *strchr(linie, '\n') = '\0';
        sateliti[i] = strdup(linie);
    }
    TArbSatelit parinteComun = apartineSubarboreVect(arbSat, sateliti, numSat);
    fprintf(output, "%s", parinteComun->info->nume);
    for (int i = 0; i < numSat; i++) {
        free(sateliti[i]);
    }
    free(sateliti);
    eliberareArbore(&arbSat);
}

void task5(FILE* input, FILE* output) {
    // imi fac arborele
    TArbSatelit arbSat = creazaArbore(input);
    // extind arborele
    extindeArbore(arbSat, input);
    // imi fac coada pe niveluri
    TPQueue* coadaParcurgere = malloc(sizeof(TPQueue));
    // verific daca a mers alocarea
    if (coadaParcurgere == NULL) {
        return;
    }
    // o initializez goala
    *coadaParcurgere = NULL;
    // parcurg in latime si adaug progresiv in coada
    parcurgereLatimeArbore(arbSat, coadaParcurgere, 0);
    // imi iau cele doua noduri intre care trebuie sa gasesc drum
    char linie[1001];
    fgets(linie, 1001, input);
    // imi iau primul nod
    char* numeNod1 = strtok(linie, " \n");
    // imi iau al doilea nod
    char* numeNod2 = strtok(NULL, " \n");
    // aloc un vector de lungime doi ca sa pot sa gasesc parintele comun
    char** satelitiCautati = malloc(2 * sizeof(char*));
    satelitiCautati[0] = numeNod1;
    satelitiCautati[1] = numeNod2;
    TArbSatelit parinteComun = apartineSubarboreVect(arbSat,
    satelitiCautati, 2);
    // eliberez vectorul
    free(satelitiCautati);
    int nivelParinte = 0, nivelNod1 = 0, nivelNod2 = 0;
    // imi iau nivelul pentru parinte si pentru cele doua noduri
    TPQueue aux = *coadaParcurgere;
    TArbSatelit nod1 = gasesteNod(arbSat, numeNod1);
    TArbSatelit nod2 = gasesteNod(arbSat, numeNod2);
    aux = *coadaParcurgere;
    while (aux) {
        if (aux->arb == parinteComun) {
            nivelParinte = aux->nivel;
        }
        if (aux->arb == nod1) {
            nivelNod1 = aux->nivel;
        }
        if (aux->arb == nod2) {
            nivelNod2 = aux->nivel;
        }
        aux = aux->urm;
    }
    // distanta dintre cele doua noduri este suma distantelor intre ele
    // si cel mai adanc stramos comun
    fprintf(output, "%d\n", (nivelNod1 - nivelParinte)
    + (nivelNod2 - nivelParinte));
    eliberarePQueue(coadaParcurgere);
    eliberareArbore(&arbSat);
}

int main(int argc, char *argv[]) {
    // verific daca am numar bun de argumente
    if (argc != 4) {
        perror("Numar gresit de argumente\n");
        return 1;
    }
    // deschid fisierul de input
    FILE* input = fopen(argv[2], "r");
    // deschid fisierul de output
    FILE* output = fopen(argv[3], "w");
    // vad ce task trebuie rulat
    if (strcmp(argv[1], "-c1") == 0) {
        task1(input, output);
    } else if (strcmp(argv[1], "-c2") == 0) {
        task2(input, output);
    } else if (strcmp(argv[1], "-c3") == 0) {
        task3(input, output);
    } else if (strcmp(argv[1], "-c4") == 0) {
        task4(input, output);
    } else if (strcmp(argv[1], "-c5") == 0) {
        task5(input, output);
    } else {
        // daca nu a fost dat un task valid
        perror("Wrong parameter used\n");
    }
    // inchid fisierele de input si output
    fclose(input);
    fclose(output);
    return 0;
}

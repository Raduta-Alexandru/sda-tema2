#include "./structuri.h"

TPQueue alocaNodPQueue(TArbSatelit arb, int nivel) {
    TCelulaPQeueu* aux = malloc(sizeof(TCelulaPQeueu));
    // verific daca a functionat alocarea
    if (aux == NULL) {
        return NULL;
    }
    // completez campurile
    aux->arb = arb;
    aux->nivel = nivel;
    aux->urm = NULL;
    return aux;
}

void inserarePQueue(TPQueue* queue, TPQueue celula) {
    // imi creez ceva sa parcurg si sa retin anterior
    TPQueue p = *queue, prec = NULL;
    // cat timp pot sa parcurg
    while (p) {
        // parcurg pana ajung la ceva care are un nivel mai mare
        if (p->nivel > celula->nivel) {
            break;
        }
        prec = p;
        p = p->urm;
    }
    // daca nu am prec, inseamna ca m-am oprit la inceput (era goala coada)
    if (prec == NULL) {
        // fac celula inceput de coada
        celula->urm = p;
        *queue = celula;
    } else {
        // altfel o introduc intre prec si p
        prec->urm = celula;
        celula->urm = p;
    }
}

void afisarePQueue(TPQueue* queue, FILE* output) {
    // imi fac o variabila ca sa stiu cand cobor un nivel
    int nivelActual = 0;
    // si o variabila pentru inceput de rand
    int inceputRand = 1;
    TPQueue p = *queue;
    // parcurg lista
    while (p) {
        // cand vad ca am coborat un nivel incrementez nivelul
        if (p->nivel > nivelActual) {
            nivelActual++;
            // si trec la urmatorul rand in output
            fprintf(output, "\n");
            inceputRand = 1;
        }
        // daca e inceput de rand nu printez spatiu inaintea numelui
        if (inceputRand == 1) {
            fprintf(output, "%d-%s", p->arb->info->freq, p->arb->info->nume);
            inceputRand = 0;
        } else {
        // altfel pritez nodul la care am ajuns cu spatiu inainte
        fprintf(output, " %d-%s", p->arb->info->freq, p->arb->info->nume);
        }
        p = p->urm;
    }
    fprintf(output, "\n");
}

void eliberarePQueue(TPQueue* queue) {
    TPQueue p = *queue;
    // cat timp am ce sa eliberez
    while (p) {
        // salvez unde am ajuns
        TPQueue aux = p;
        // trec la urmatorul
        p = p->urm;
        // si eliberez
        free(aux);
    }
    free(queue);
}

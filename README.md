# RADUTA Alexandru - 315CB - Structuri de Date si Algoritmi - Tema 2

## Scopul temei

Tema 2 SDA are ca scop implementarea unei retele de sateliti interconectati intre ei intr-o forma de arbore binar. Tema incepe de la definirea urmatoarelor structuri :
- `typedef struct satelit {int freq; char* nume;} TSatelit;`
- `typedef struct nodSatelit {TSatelit* info; struct nodSatelit* left; struct nodSatelit* right;} TNodSatelit, *TArbSatelit;`
- `typedef struct satelitHeap { int numMax, numSateliti; TArbSatelit* vectSatelite; TComparaSateliti comp;} TSatelitHeap;`

Tema doreste sa fie implementate urmatoarele functii pentru a face o retea utila de sateliti :

1. **Constructia si afisarea arborelui**
2. **Urmarirea unei codificari pentru a gasi un satelit**
3. **Determinarea unei codificari pentru un satelit**
4. **Gasirea parintelui comun pentru o serie de sateliti**
5. **Exitinderea arborelui si gasirea distantei intre doua noduri**

Tema foloseste concepetele de : *Heap* si *Arbore multicai*.

## Implementare Main

Functia incepe prin a isi lua parametri cu care lucreaza, adica taskul care trebuie rulat, fisierul de intrare si fisierul de iesire, deschide cele doua fisiere, iar dupa aceea ruleaza taskul care este cerut de rulare.

## Implementare functii legate de sateliti

- `TSatelit* alocSatelit(int freq, char* nume)`
Functia aloca spatiu pentru un satelit, ii da parametri ceruti, si returneaza pointer catre satelitul alocat.
- `void distrugeSatelit(TSatelit* satelit)`
Functia elibereaza mai intai numele, si dupa aceea elibereaza si satelitul.
- `int compSateliti(TSatelit* satelit1, TSatelit* satelit2)`
Functia ia cei doi sateliti, si mai intai compara dupa frecventa, si dupa dupa nume.


## Implementare functii legate de heap

- `TSatelitHeap* alocHeap(int numMax, TComparaSateliti funcComp)`
Functia aloca spatiu pentru heap, dupa care ii aloca vectorul, si ii adauga parametri pentru numarul maxim de elemente, numarul actual de sateliti si functia de comparatie, si la final returneaza pointer catre heap.
- `void distrugeHeap(TSatelitHeap **heap)`
Functia elibereaza vectorul si dupa aceea si heapul, setandul ca NULL.
- `void pushUp(TSatelitHeap* heap, int poz)`
Functia impinge elementul adaugat in sus pana cand isi gaseste pozitia astfel incat sa se respecte regulile pentru MIN-HEAP.
- `void pushDown(TSatelitHeap* heap, int poz)`
Functia impinge elementul care a fost pus la inceput in urma eliminarii din heap in jos pana cand isi gaseste pozitia astfel incat sa se respecte regulile pentru MIN-HEAP.
- `void inserareHeap(TSatelitHeap* heap, TArbSatelit nod)`
Functia insereaza in heap un element nou la final, iar apoi folosing functia de pushUp ii gaseste locul potrivit.
- `TArbSatelit eliminareHeap(TSatelitHeap* heap)`
Functia returneaza primul element din heap, iar apoi muta la inceput ultimul elemnt, urmand sa ii gaseasca locul potrivit folosind functia pushDown.

## Implementare functii legate de constructia arborelui

- `TArbSatelit alocNodArb(TSatelit* satelit)`
Functia aloca spatiu pentru un nod, iar apoi ii da informatile, si returneaza pointer catre nod.
- `TArbSatelit creazaArbore(FILE* input)`
Functia citeste mai intai numarul de sateliti pe care urmeaza sa ii citeasca, iar apoi intra intr-un for in care citeste cate un satelit, il aloca, creaza un nod pentru el, si insereaza nodul in heap. Dupa ce citeste toti satelitii, incepe sa creeze arborele. Ia pe rand din heap primele doua noduri, le aloca un satelit cu frecventa suma si numele concatenat si le aloca un nod parinte, pe care il introduce in heap. Procesul se repeta pana cand in heap mai ramane un singur nod, acela fiind radacina arborelui, urmand sa il returneze.
- `void eliberareArbore(TArbSatelit* arb)`
Functia se apeleaza apeleaza recursiv in adancine, iar apoi elibereaza satelitul si dupa nodul in sine.

## Implementare structura si functii pentru coada de prioritati

Pentru a putea sa fac afisarea in latime am folosit o coada de prioritati, declarata astfel:
- `typedef struct nodPQueue { TArbSatelit arb; int nivel; struct nodPQueue* urm;} TCelulaPQeueu, *TPQueue;`
- `TPQueue alocaNodPQueue(TArbSatelit arb, int nivel)`
Functia aloca un nod de lista de prioritati, si ii da parametri dati prin functie si returneaza pointer catre nod.
- `void inserarePQueue(TPQueue* queue, TPQueue celula)`
Functia parcurge coada pana cand gaseste un element care are nivelul mai mare ca elementul care trebuie inserat, sau pana la final. Elementul este dupa aceea inserat inaintea elementului gasit, sau daca nu e gasit, la final cozii / la inceput, daca e coada goala.
- `void afisarePQueue(TPQueue* queue, FILE* output)`
Functia parcurge lista, si scrie la ecran fiecare element, si verifica sa treaca la urmatorul rand cand creste nivelul.
- `void eliberarePQueue(TPQueue* queue)`
Functia parcurge coada, eliberand fiecare element din coada, iar apoi coada in sine.

## Implementare functii auxiliare pentru taskuri

- `void parcurgereLatimeArbore(TArbSatelit radacine, TPQueue* queue, int nivel)`
Functia parcurge recursiv in ordine SDR arborele, iar apoi adaug in coada nodul curent, tinand cont de nivel(cand apelez functia in jos adaug 1 la nivel).
- `void afisareArboreNivel(TArbSatelit radacina, FILE* output)`
Functia aloca o coada de prioritati, dupa care incepe sa o umple folosind functia parcuregereLatimeArbore, apoi o afiseaza cu functia afisarePQueue si o elibereaza.
- `int apartineSubarbore(TArbSatelit arb, char* nume)`
Functia mai intai verifica daca a ajuns la NULL, caz in care se intoarce din recursivitate. Daca nodul la care a ajuns are satelitul cautat returneaza 1, semn ca apartine. Atfel, parcurge recursiv toti copiii pana cand gaseste un copil care il contine. Daca nu gaseste returneaza 0, adica satelitul nu apartine subarborelui.
- `TArbSatelit apartineSubarboreVect(TArbSatelit arb, char** sateliti, int numSat)`
Functia numara cati copii are nodul pe care il analizam, iar apoi aloca un vector pentru a salva cati dintre satelitii cautati apartin fiecarui subarbore copil. Parcurge lista de sateliti cautati, si fiecaruia gaseste copil care il contine, notand asta in vectorul alocat. Dupa aceea parcurge in paralel copii si vectorul alocat. Daca in vector exista un element egal cu numarul de sateliti cautati, adica un copil detine toti satelitii, se intra in recursivitate. Altfel inseamna ca unii sunt la un copil, alti la alt copil etc, deci parintele comun este arb, pe care il returneaza.
- `TArbSatelit gasesteNod(TArbSatelit arb, char* nume)`
Functia parcurge recursiv arborele pana cand ajunge pe NULL, sau pana cand gaseste nodul cautat.
- `void extindeArbore(TArbSatelit arb, FILE* input)`
Functia citeste mai intai cati arbori trebuie cititi, iar apoi pentru fiecare gaseste nodul de legatura si radacina, pe care le leaga intre ele. Apoi citeste cati parinti o sa fie in arborele multicai, iar pentru fiecare il gaseste, si citeste cati copii are, fiecare copil fiind alocat si legat de parinte.

## Implementare functii pentru taskuri

- `void task1(FILE* input, FILE* output)`
Functia creaza arborele folosind functia creazaArbore, il afiseaza folosind functia afisareArboreNivel si il elibereaza folosind functia elibereareArboreNivel.
- `void task2(FILE* input, FILE* output)`
Functia creaza arborele folosind functia creazaArbore, iar apoi citeste numarul de codificari, si intra intr-un for. In for citeste codificarea, si citeste din codificare pas cu pas, parcurgand arborele, pana cand ajunge la o frunza, moment in care o afiseaza si reseteaza parcurgerea inapoi la radacina. La final elibereaza arborele folosind eliberareArbore.
- `void task3(FILE* input, FILE* output)`
Functia creaza arborele folosind functia creazaArbore, iar apoi citeste numarul de sateliti si intra intr-un for. In for citeste numele satelitului, iar apoi parcurge arborele, facand stanga sau dreapta in functie de raspunsul functiei apartineSubarbore, afisand 0 sau 1 in functie de pasul facut. Se opreste cand gaseste o frunza, sau cand gaseste satelitul cu numele cautat. La final elibereaza arborele folosind eliberareArbore.
- `void task4(FILE* input, FILE* output)`
Functia creaza arborele folosind functia creazaArbore, iar apoi citeste numarul de sateliti, aloca un vector pentru a stoca satelitii, pe care il umple cu numele pe care le citeste din input. Gaseste parintele comun folosind functia apartineSubarboreVect, il afiseaza, iar la final elibereaza fiecare nume alocat, vectorul in sine si arborele folosind functia eliberareArbore.
- `void task5(FILE* input, FILE* output)`
Functia creaza arborele folosind functia creazaArbore, iar apoi il extinde cu functia extindeAtbore. Functia isi face o coada pe nivel, pentru a stii ce nivel are fiecare nod. Citeste numele celor 2 noduri pentru care se cauta distanta, iar apoi le gaseste cel mai adanc stramos comun, deoarece distanta dintre cele doua noduri este suma distantelor dintre parintele comun si cele doua noduri. Parcuge coada pentru a lua nivelul pentru fiecare, iar apoi afiseaza distanta, dupa care elibereaza coada si arborele.

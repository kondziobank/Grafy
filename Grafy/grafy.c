#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funkcja pozwala uzytkownikowi wprowadzic wiersze macierzy sasiedztwa
// zwraca wskaznik na macierz sasiedztwa
// do parametru n_wierzcholkow zapisuje liczbe wierzcholkow nowego grafu
int **wprowadzMacierzSasiedztwa(int *n_wierzcholkow);

// generuje przykladowy graf acykliczny - zwraca wskaznik na zaalokowana pamiec
int **przykladowyGraf(int n_wierzcholkow);

// funkcja tworzaca tabele krawedzi na podstawie macierzy sasiedztwa
// zwraca wskaznik na tabele krawedzi, a do parametru n_krawedzi zapisuje liczbe krawedzi
int **utworzTabeleKrawedzi(int **macierz, int n_wierzcholkow, int *n_krawedzi);

// struktura reprezentujaca krawedz w liscie nastepnikow
typedef struct krawedz_t {

    int wierzcholek;
    struct krawedz_t *nastepny;
} krawedz_t;

// funkcja tworzaca liste nastepnikow, zwraca wskaznik na utworzona liste
krawedz_t **utworzListeNastepnikow(int **macierz, int n_wierzcholkow);

// wyswietla macierz sasiedztwa
void wyswietlMacierz(int **macierz, int n_wierzcholkow);

// wyswietla tabele krawedzi
void wyswietlTabele(int **tabela, int n_wierzcholkow, int n_krawedzi);

// wyswietla liste nastepnikow
void wyswietlListe(krawedz_t **lista, int n_wierzcholkow);

// przechodzenie grafu wszerz za pomoca macierzy sasiedztwa
void BFS_macierz(int **macierz, int n_wierzcholkow);

// przechodzenie grafu wszerz za pomoca tabeli krawedzi
void BFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi);

// przechodzenie grafu wszerz za pomoca listy nastepnikow
void BFS_lista(krawedz_t **lista, int n_wierzcholkow);

// przechodzenie grafu wglab za pomoca macierzy sasiedztwa
void DFS_macierz(int **macierz, int n_wierzcholkow);

// przechodzenie grafu wglab za pomoca macierzy sasiedztwa - funkcja wewnetrzna
void rek_DFS_macierz(int **macierz, int n_wierzcholkow, int s, int *odwiedzony);

// przechodzenie grafu wglab za pomoca tabeli krawedzi
void DFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi);

// przechodzenie grafu wglab za pomoca tabeli krawedzi - funkcja wewnetrzna
void rek_DFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi, int s,
                    int *odwiedzony);

// przechodzenie grafu wglab za pomoca listy nastepnikow
void DFS_lista(krawedz_t **lista, int n_wierzcholkow);

// przechodzenie grafu wglab za pomoca listy nastepnikow - funkcja wewnetrzna
void rek_DFS_lista(krawedz_t **lista, int n_wierzcholkow, int s, int *odwiedzony);

// sortowanie topologiczne grafu wszerz za pomoca macierzy sasiedztwa
void sortowanie_BFS_macierz(int **macierz, int n_wierzcholkow);

// sortowanie topologiczne grafu wszerz za pomoca tabeli krawedzi
void sortowanie_BFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi);

// sortowanie topologiczne grafu wszerz za pomoca listy nastepnikow
void sortowanie_BFS_lista(krawedz_t **lista, int n_wierzcholkow);

// sortowanie topologiczne grafu wglab za pomoca macierzy sasiedztwa
void sortowanie_DFS_macierz(int **macierz, int n_wierzcholkow);

// sortowanie topologiczne grafu wglab za pomoca macierzy sasiedztwa - funkcja wewnetrzna
void rek_sortowanie_DFS_macierz(int **macierz, int n_wierzcholkow, int s, int *odwiedzony,
                                krawedz_t *stos);

// sortowanie topologiczne grafu wglab za pomoca tabeli krawedzi
void sortowanie_DFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi);

// sortowanie topologiczne grafu wglab za pomoca tabeli krawedzi - funkcja wewnetrzna
void rek_sortowanie_DFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi, int s,
                               int *odwiedzony, krawedz_t *stos);

// sortowanie topologiczne grafu wglab za pomoca listy nastepnikow
void sortowanie_DFS_lista(krawedz_t **lista, int n_wierzcholkow);

// sortowanie topologiczne grafu wglab za pomoca listy nastepnikow - funkcja wewnetrzna
void rek_sortowanie_DFS_lista(krawedz_t **lista, int n_wierzcholkow, int s,
                              int *odwiedzony, krawedz_t *stos);

//cykl Eulera
void DFS_Euler(int **tabela, int n_wierzcholkow, int n_krawedzi);

// cykl Eulera - funkcja wewnętrzna
void rek_DFS_Euler(int **tabela, int n_wierzcholkow, int n_krawedzi, int s,
                    int *odwiedzony);

void DFS_Hamilton(int **tabela, int n_wierzcholkow, int n_krawedzi);

void rek_DFS_Hamilton(int **tabela, int n_wierzcholkow, int n_krawedzi, int s,
                    int *odwiedzony);

int main() {

    // TWORZENIE GRAFU
    int n_wierzcholkow = 5, n_krawedzi = 0;
    int **macierz;     // macierz sasiedztwa
    int **tabela;      // tabela krawedzi
    krawedz_t **lista; // lista nastepnikow

    int wybor;
    printf(" 1 - wygeneruj graf automatycznie\n");
    printf(" 2 - wprowadz wlasny graf\n ");
    scanf("%d", &wybor);

    if (wybor == 1)
        macierz = przykladowyGraf(n_wierzcholkow);
    else
        macierz = wprowadzMacierzSasiedztwa(&n_wierzcholkow);

    tabela = utworzTabeleKrawedzi(macierz, n_wierzcholkow, &n_krawedzi);
    lista = utworzListeNastepnikow(macierz, n_wierzcholkow);

    // WYSWIETLANIE GRAFU
    wyswietlMacierz(macierz, n_wierzcholkow);
    wyswietlTabele(tabela, n_wierzcholkow, n_krawedzi);
    wyswietlListe(lista, n_wierzcholkow);
	


        BFS_macierz(macierz, n_wierzcholkow);

        BFS_tabela(tabela, n_wierzcholkow, n_krawedzi);

        BFS_lista(lista, n_wierzcholkow);

        DFS_macierz(macierz, n_wierzcholkow);

        DFS_tabela(tabela, n_wierzcholkow, n_krawedzi);

        DFS_lista(lista, n_wierzcholkow);

        sortowanie_BFS_macierz(macierz, n_wierzcholkow);

        sortowanie_BFS_tabela(tabela, n_wierzcholkow, n_krawedzi);

        sortowanie_BFS_lista(lista, n_wierzcholkow);

        sortowanie_DFS_macierz(macierz, n_wierzcholkow);

        sortowanie_DFS_tabela(tabela, n_wierzcholkow, n_krawedzi);

        sortowanie_DFS_lista(lista, n_wierzcholkow);

        DFS_Euler(tabela, n_wierzcholkow, n_krawedzi);

        DFS_Hamilton(tabela, n_wierzcholkow, n_krawedzi);

    // ZWALNIANIE PAMIECI
    for (int i = 0; i < n_wierzcholkow; i++) {

        free(macierz[i]);
        free(tabela[i]);
        krawedz_t *it = lista[i];
        while (it != NULL) {

            krawedz_t *t = it->nastepny;
            free(it);
            it = t;
        }
    }

    free(macierz);
    free(tabela);
    free(lista);

    return 0;
}

// Funkcja pozwala uzytkownikowi wprowadzic wiersze macierzy sasiedztwa
// zwraca wskaznik na macierz sasiedztwa
// do parametru n_wierzcholkow zapisuje liczbe wierzcholkow nowego grafu
int **wprowadzMacierzSasiedztwa(int *n_wierzcholkow) {

    int n;
    printf("Podaj liczbe wierzcholkow: ");
    scanf("%d", &n);
    printf("Wprowadz macierz sasiedztwa:\n");

    int **macierz;
    macierz = malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++) {

        macierz[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
            scanf("%d", &macierz[i][j]);
    }
    printf("\n");
    *n_wierzcholkow = n;

    return macierz;
}

// generuje przykladowy graf acykliczny - zwraca wskaznik na zaalokowana pamiec
int **przykladowyGraf(int n_wierzcholkow) {

    int **macierz;
    macierz = malloc(sizeof(int *) * n_wierzcholkow);

    for (int i = 0; i < n_wierzcholkow; i++) {
        macierz[i] = malloc(sizeof(int) * n_wierzcholkow);

        for (int j = 0; j <= i; j++)
            macierz[i][j] = 0;

        for (int j = i + 1; j < n_wierzcholkow; j++)
            macierz[i][j] = 1;
    }

    srand(time(NULL));
    for (int i = 0; i < 10000 * n_wierzcholkow; i++) {

        int x = rand() % n_wierzcholkow;
        int y, t;
        do {
            y = rand() % n_wierzcholkow;
        } while (x == y);

        for (int j = 0; j < n_wierzcholkow; j++) {

            if (j == x || j == y)
                continue;

            t = macierz[j][x];
            macierz[j][x] = macierz[j][y];
            macierz[j][y] = macierz[j][x];

            t = macierz[x][j];
            macierz[x][j] = macierz[y][j];
            macierz[y][j] = macierz[x][j];
        }
    }

    return macierz;
}

// funkcja tworzaca tabele krawedzi na podstawie macierzy sasiedztwa
// zwraca wskaznik na tabele krawedzi, a do parametru n_krawedzi zapisuje liczbe
// krawedzi
int **utworzTabeleKrawedzi(int **macierz, int n_wierzcholkow, int *n_krawedzi) {

    // zliczanie krawedzi
    int n = 0;
    for (int i = 0; i < n_wierzcholkow; i++)
        for (int j = 0; j < n_wierzcholkow; j++)
            if (macierz[i][j])
                n++;

    // alokacja pamieci
    int **tabela = malloc(sizeof(int *) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++) {

        tabela[i] = malloc(sizeof(int *) * n);
        for (int j = 0; j < n; j++)
            tabela[i][j] = 0;
    }

    // tworzenie tabeli krawedzi na podstawie listy sasiedztwa
    int krawedz = 0;
    for (int i = 0; i < n_wierzcholkow; i++)
        for (int j = 0; j < n_wierzcholkow; j++)
            if (macierz[i][j]) {
                tabela[i][krawedz] = 1;
                tabela[j][krawedz] = -1;
                krawedz++;
            }

    *n_krawedzi = n;
    return tabela;
}

// funkcja tworzaca liste nastepnikow, zwraca wskaznik na utworzona liste
krawedz_t **utworzListeNastepnikow(int **macierz, int n_wierzcholkow) {

    // alokacja pamieci
    krawedz_t **lista = malloc(sizeof(krawedz_t *) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        lista[i] = NULL;

    // tworzenie listy nastepnikow na podstawie macierzy sasiedztwa
    for (int i = 0; i < n_wierzcholkow; i++) {

        krawedz_t *ostatni;
        for (int j = 0; j < n_wierzcholkow; j++)
            if (macierz[i][j]) {

                if (lista[i] == NULL) {
                    lista[i] = malloc(sizeof(krawedz_t));
                    ostatni = lista[i];
                } else {
                    ostatni->nastepny = malloc(sizeof(krawedz_t));
                    ostatni = ostatni->nastepny;
                }
                ostatni->wierzcholek = j;
                ostatni->nastepny = NULL;
            }
    }

    return lista;
}

// wyswietla macierz sasiedztwa
void wyswietlMacierz(int **macierz, int n_wierzcholkow) {

    printf(" MACIERZ SASIEDZTWA\n\n      ");
    for (int i = 0; i < n_wierzcholkow; i++)
        printf("%d ", i);
    printf("\n\n");
    for (int i = 0; i < n_wierzcholkow; i++) {
        printf("  %d   ", i);
        for (int j = 0; j < n_wierzcholkow; j++)
            printf("%d ", macierz[i][j]);
        printf("\n");
    }
    printf("\n");
}

// wyswietla tabele krawedzi
void wyswietlTabele(int **tabela, int n_wierzcholkow, int n_krawedzi) {

    printf(" TABELA_KRAWEDZI\n\n");
    for (int i = 0; i < n_wierzcholkow; i++) {
        printf("  %d  ", i);
        for (int j = 0; j < n_krawedzi; j++)
            if (tabela[i][j] == 0)
                printf(" 0");
            else if (tabela[i][j] == 1)
                printf(" +");
            else
                printf(" -");
        printf("\n");
    }
    printf("\n");
}

// wyswietla liste nastepnikow
void wyswietlListe(krawedz_t **lista, int n_wierzcholkow) {

    printf(" LISTA NASTEPNIKOW\n\n");
    for (int i = 0; i < n_wierzcholkow; i++) {
        printf("  %d: ", i);
        krawedz_t *it = lista[i];
        while (it != NULL) {
            printf("%d ", it->wierzcholek);
            it = it->nastepny;
        }
        printf("\n");
    }
   printf("\n");
}

// przechodzenie grafu wszerz
void BFS_macierz(int **macierz, int n_wierzcholkow) {

    printf(" PRZECHODZENIE GRAFU WSZERZ - macierz sasiedztwa\n\n  ");
    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;

    for (int s = 0; s < n_wierzcholkow; s++)
        if (odwiedzony[s] == 0) {

            krawedz_t *kolejka = malloc(sizeof(krawedz_t));
            kolejka->wierzcholek = s;
            kolejka->nastepny = NULL;

            while (kolejka != NULL) {

                int wierzcholek = kolejka->wierzcholek;
                krawedz_t *t = kolejka->nastepny;
                free(kolejka);
                kolejka = t;

                if (odwiedzony[wierzcholek] == 1)
                    continue;

                printf("%d ", wierzcholek);
                odwiedzony[wierzcholek] = 1;

                for (int i = 0; i < n_wierzcholkow; i++)
                    if (macierz[wierzcholek][i] && odwiedzony[i] == 0) {

                        if (odwiedzony[i])
                            continue;

                        krawedz_t *ostatni;
                        if (kolejka == NULL) {
                            kolejka = malloc(sizeof(krawedz_t *));
                            ostatni = kolejka;
                        } else {

                            ostatni = kolejka;
                            while (ostatni->nastepny != NULL)
                                ostatni = ostatni->nastepny;
                            ostatni->nastepny = malloc(sizeof(krawedz_t *));
                            ostatni = ostatni->nastepny;
                        }

                        ostatni->wierzcholek = i;
                        ostatni->nastepny = NULL;
                    }
            }
        }

    printf("\n\n");
    free(odwiedzony);
}

// przechodzenie grafu wszerz za pomoca tabeli krawedzi
void BFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi) {

    printf(" PRZECHODZENIE GRAFU WSZERZ - tabela krawedzi\n\n  ");
    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;

    for (int s = 0; s < n_wierzcholkow; s++)
        if (odwiedzony[s] == 0) {

            krawedz_t *kolejka = malloc(sizeof(krawedz_t));
            kolejka->wierzcholek = s;
            kolejka->nastepny = NULL;

            while (kolejka != NULL) {

                int wierzcholek = kolejka->wierzcholek;
                krawedz_t *t = kolejka->nastepny;
                free(kolejka);
                kolejka = t;

                if (odwiedzony[wierzcholek] == 1)
                    continue;

                printf("%d ", wierzcholek);
                odwiedzony[wierzcholek] = 1;

                for (int i = 0; i < n_krawedzi; i++)
                    if (tabela[wierzcholek][i] == 1) {

                        int docelowy = -1;
                        for (int j = 0; docelowy == -1; j++)
                            if (tabela[j][i] == -1)
                                docelowy = j;

                        if (odwiedzony[docelowy])
                            continue;

                        krawedz_t *ostatni;
                        if (kolejka == NULL) {
                            kolejka = malloc(sizeof(krawedz_t *));
                            ostatni = kolejka;
                        } else {

                            ostatni = kolejka;
                            while (ostatni->nastepny != NULL)
                                ostatni = ostatni->nastepny;
                            ostatni->nastepny = malloc(sizeof(krawedz_t *));
                            ostatni = ostatni->nastepny;
                        }

                        ostatni->wierzcholek = docelowy;
                        ostatni->nastepny = NULL;
                    }
            }
        }
    printf("\n\n");
    free(odwiedzony);
}

// przechodzenie grafu wszerz za pomoca listy nastepnikow
void BFS_lista(krawedz_t **lista, int n_wierzcholkow) {

    printf(" PRZECHODZENIE GRAFU WSZERZ - lista nastepnikow\n\n  ");
    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;

    for (int s = 0; s < n_wierzcholkow; s++)
        if (odwiedzony[s] == 0) {

            krawedz_t *kolejka = malloc(sizeof(krawedz_t));
            kolejka->wierzcholek = s;
            kolejka->nastepny = NULL;

            while (kolejka != NULL) {

                int wierzcholek = kolejka->wierzcholek;
                krawedz_t *t = kolejka->nastepny;
                free(kolejka);
                kolejka = t;

                if (odwiedzony[wierzcholek] == 1)
                    continue;

                printf("%d ", wierzcholek);
                odwiedzony[wierzcholek] = 1;

                krawedz_t *it = lista[wierzcholek];
                while (it != NULL) {

                    if (odwiedzony[it->wierzcholek]) {
                        it = it->nastepny;
                        continue;
                    }

                    krawedz_t *ostatni;
                    if (kolejka == NULL) {
                        kolejka = malloc(sizeof(krawedz_t *));
                        ostatni = kolejka;
                    } else {

                        ostatni = kolejka;
                        while (ostatni->nastepny != NULL)
                            ostatni = ostatni->nastepny;
                        ostatni->nastepny = malloc(sizeof(krawedz_t *));
                        ostatni = ostatni->nastepny;
                    }

                    ostatni->wierzcholek = it->wierzcholek;
                    ostatni->nastepny = NULL;

                    it = it->nastepny;
                }
            }
        }
    printf("\n\n");
    free(odwiedzony);
}

// przechodzenie grafu wglab za pomoca macierzy sasiedztwa
void DFS_macierz(int **macierz, int n_wierzcholkow) {

    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;
    printf(" PRZECHODZENIE GRAFU WGLAB - macierz sasiedztwa\n\n  ");
    for (int i = 0; i < n_wierzcholkow; i++)
        if (odwiedzony[i] == 0)
            rek_DFS_macierz(macierz, n_wierzcholkow, i, odwiedzony);
    printf("\n\n");
    free(odwiedzony);
}

// przechodzenie grafu wglab za pomoca macierzy sasiedztwa - funkcja wewnetrzna
void rek_DFS_macierz(int **macierz, int n_wierzcholkow, int s, int *odwiedzony) {

    printf("%d ", s);
    odwiedzony[s] = 1;

    for (int i = 0; i < n_wierzcholkow; i++)
        if (macierz[s][i] && odwiedzony[i] == 0)
            rek_DFS_macierz(macierz, n_wierzcholkow, i, odwiedzony);
}

// przechodzenie grafu wglab za pomoca tabeli krawedzi
void DFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi) {

    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;
    printf(" PRZECHODZENIE GRAFU WGLAB - tabela krawedzi\n\n  ");
    for (int i = 0; i < n_wierzcholkow; i++)
        if (odwiedzony[i] == 0)
            rek_DFS_tabela(tabela, n_wierzcholkow, n_krawedzi, i, odwiedzony);
    printf("\n\n");
    free(odwiedzony);
}

// przechodzenie grafu wglab za pomoca tabeli krawedzi - funkcja wewnetrzna
void rek_DFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi, int s,
                    int *odwiedzony) {
    printf("%d ", s);
    odwiedzony[s] = 1;

    for (int i = 0; i < n_wierzcholkow; i++)
        if (tabela[s][i] == 1) {

            int docelowy = -1;
            for (int j = 0; docelowy == -1; j++)
                if (tabela[j][i] == -1)
                    docelowy = j;

            if (odwiedzony[docelowy] == 0)
                rek_DFS_tabela(tabela, n_wierzcholkow, n_krawedzi, docelowy, odwiedzony);
        }
}

// przechodzenie grafu wglab za pomoca listy nastepnikow
void DFS_lista(krawedz_t **lista, int n_wierzcholkow) {

    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;
    printf(" PRZECHODZENIE GRAFU WGLAB - lista nastepnikow\n\n  ");
    for (int i = 0; i < n_wierzcholkow; i++)
        if (odwiedzony[i] == 0)
            rek_DFS_lista(lista, n_wierzcholkow, i, odwiedzony);
    printf("\n\n");
    free(odwiedzony);
}

// przechodzenie grafu wglab za pomoca listy nastepnikow - funkcja wewnetrzna
void rek_DFS_lista(krawedz_t **lista, int n_wierzcholkow, int s, int *odwiedzony) {

    printf("%d ", s);
    odwiedzony[s] = 1;

    krawedz_t *it = lista[s];
    while (it != NULL) {

        if (odwiedzony[it->wierzcholek] == 0)
            rek_DFS_lista(lista, n_wierzcholkow, it->wierzcholek, odwiedzony);

        it = it->nastepny;
    }
}

// sortowanie topologiczne grafu wszerz za pomoca macierzy sasiedztwa
void sortowanie_BFS_macierz(int **macierz, int n_wierzcholkow) {

    printf(" SORTOWANIE TOPOLOGICZNE WSZERZ - macierz sasiedztwa\n\n  ");
    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;

    int n_odwiedzonych = 0;
    while (n_odwiedzonych < n_wierzcholkow) {

        int s = 0;
        for (int i = 0; i < n_wierzcholkow; i++) {

            if (odwiedzony[i] == 1)
                continue;

            int wejsciowy = 1;
            for (int j = 0; j < n_wierzcholkow; j++)
                if (macierz[j][i] == 1 && odwiedzony[j] == 0) {
                    wejsciowy = 0;
                    break;
                }

            if (wejsciowy == 1) {
                s = i;
                break;
            }
        }

        printf("%d ", s);
        odwiedzony[s] = 1;
        n_odwiedzonych++;
    }

    printf("\n\n");
    free(odwiedzony);
}

// sortowanie topologiczne grafu wszerz za pomoca tabeli krawedzi
void sortowanie_BFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi) {

    printf(" SORTOWANIE TOPOLOGICZNE WSZERZ - tabela krawedzi\n\n  ");
    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;

    int n_odwiedzonych = 0;
    while (n_odwiedzonych < n_wierzcholkow) {

        int s = 0;
        for (int i = 0; i < n_wierzcholkow; i++) {

            if (odwiedzony[i] == 1)
                continue;

            int wejsciowy = 1;
            for (int j = 0; j < n_krawedzi && wejsciowy == 1; j++)
                if (tabela[i][j] == -1) {

                    for (int k = 0; k < n_wierzcholkow; k++)
                        if (tabela[k][j] == 1 && odwiedzony[k] == 0) {
                            wejsciowy = 0;
                            break;
                        }
                }

            if (wejsciowy == 1) {
                s = i;
                break;
            }
        }

        printf("%d ", s);
        odwiedzony[s] = 1;
        n_odwiedzonych++;
    }

    printf("\n\n");
    free(odwiedzony);
}

// sortowanie topologiczne grafu wszerz za pomoca listy nastepnikow
void sortowanie_BFS_lista(krawedz_t **lista, int n_wierzcholkow) {

    printf(" SORTOWANIE TOPOLOGICZNE WSZERZ - lista nastepnikow\n\n  ");
    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;

    int n_odwiedzonych = 0;
    while (n_odwiedzonych < n_wierzcholkow) {

        int s = 0;
        for (int i = 0; i < n_wierzcholkow; i++) {

            if (odwiedzony[i] == 1)
                continue;

            int wejsciowy = 1;
            for (int j = 0; j < n_wierzcholkow && wejsciowy == 1; j++) {

                if (odwiedzony[j] == 1)
                    continue;

                krawedz_t *it = lista[j];
                while (it != NULL) {

                    if (it->wierzcholek == i) {
                        wejsciowy = 0;
                        break;
                    }
                    it = it->nastepny;
                }
            }

            if (wejsciowy == 1) {
                s = i;
                break;
            }
        }

        printf("%d ", s);
        odwiedzony[s] = 1;
        n_odwiedzonych++;
    }

    printf("\n\n");
    free(odwiedzony);
}

// sortowanie topologiczne grafu wglab za pomoca macierzy sasiedztwa
void sortowanie_DFS_macierz(int **macierz, int n_wierzcholkow) {

    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;
    printf(" SORTOWANIE GRAFU WGLAB - macierz sasiedztwa\n\n  ");

    krawedz_t stos;
    stos.nastepny = NULL;
    for (int i = 0; i < n_wierzcholkow; i++)
        if (odwiedzony[i] == 0)
            rek_sortowanie_DFS_macierz(macierz, n_wierzcholkow, i, odwiedzony, &stos);

    krawedz_t *it = stos.nastepny;
    while (it != NULL) {
        printf("%d ", it->wierzcholek);
        krawedz_t *t = it->nastepny;
        free(it);
        it = t;
    }

    printf("\n\n");
    free(odwiedzony);
}

// sortowanie topologiczne grafu wglab za pomoca macierzy sasiedztwa - funkcja
// wewnetrzna
void rek_sortowanie_DFS_macierz(int **macierz, int n_wierzcholkow, int s, int *odwiedzony,
                                krawedz_t *stos) {

    odwiedzony[s] = 1;
    for (int i = 0; i < n_wierzcholkow; i++)
        if (macierz[s][i] && odwiedzony[i] == 0)
            rek_sortowanie_DFS_macierz(macierz, n_wierzcholkow, i, odwiedzony, stos);

    odwiedzony[s] = 2;
    krawedz_t *t = stos->nastepny;
    stos->nastepny = malloc(sizeof(krawedz_t));
    stos->nastepny->wierzcholek = s;
    stos->nastepny->nastepny = t;
}

// sortowanie topologiczne grafu wglab za pomoca tabeli krawedzi
void sortowanie_DFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi) {

    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;
    printf(" SORTOWANIE GRAFU WGLAB - tabela krawedzi\n\n  ");

    krawedz_t stos;
    stos.nastepny = NULL;
    for (int i = 0; i < n_wierzcholkow; i++)
        if (odwiedzony[i] == 0)
            rek_sortowanie_DFS_tabela(tabela, n_wierzcholkow, n_krawedzi, i, odwiedzony,
                                      &stos);

    krawedz_t *it = stos.nastepny;
    while (it != NULL) {
        printf("%d ", it->wierzcholek);
        krawedz_t *t = it->nastepny;
        free(it);
        it = t;
    }

    printf("\n\n");
    free(odwiedzony);
}

// sortowanie topologiczne grafu wglab za pomoca tabeli krawedzi - funkcja wewnetrzna
void rek_sortowanie_DFS_tabela(int **tabela, int n_wierzcholkow, int n_krawedzi, int s,
                               int *odwiedzony, krawedz_t *stos) {

    odwiedzony[s] = 1;
    for (int i = 0; i < n_krawedzi; i++)
        if (tabela[s][i] == 1) {

            int docelowy = -1;
            for (int j = 0; docelowy == -1; j++)
                if (tabela[j][i] == -1)
                    docelowy = j;

            if (odwiedzony[docelowy] == 0)
                rek_sortowanie_DFS_tabela(tabela, n_wierzcholkow, n_krawedzi, docelowy,
                                          odwiedzony, stos);
        }

    odwiedzony[s] = 2;
    krawedz_t *t = stos->nastepny;
    stos->nastepny = malloc(sizeof(krawedz_t));
    stos->nastepny->wierzcholek = s;
    stos->nastepny->nastepny = t;
}

// sortowanie topologiczne grafu wglab za pomoca listy nastepnikow
void sortowanie_DFS_lista(krawedz_t **lista, int n_wierzcholkow) {

    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;
    printf(" SORTOWANIE GRAFU WGLAB - lista nastepnikow\n\n  ");

    krawedz_t stos;
    stos.nastepny = NULL;
    for (int i = 0; i < n_wierzcholkow; i++)
        if (odwiedzony[i] == 0)
            rek_sortowanie_DFS_lista(lista, n_wierzcholkow, i, odwiedzony, &stos);

    krawedz_t *it = stos.nastepny;
    while (it != NULL) {
        printf("%d ", it->wierzcholek);
        krawedz_t *t = it->nastepny;
        free(it);
        it = t;
    }

    printf("\n\n");
    free(odwiedzony);
}

// sortowanie topologiczne grafu wglab za pomoca listy nastepnikow - funkcja wewnetrzna
void rek_sortowanie_DFS_lista(krawedz_t **lista, int n_wierzcholkow, int s,
                              int *odwiedzony, krawedz_t *stos) {

    odwiedzony[s] = 1;

    krawedz_t *it = lista[s];
    while (it != NULL) {

        if (odwiedzony[it->wierzcholek] == 0)
            rek_sortowanie_DFS_lista(lista, n_wierzcholkow, it->wierzcholek, odwiedzony,
                                     stos);

        it = it->nastepny;
    }

    odwiedzony[s] = 2;
    krawedz_t *t = stos->nastepny;
    stos->nastepny = malloc(sizeof(krawedz_t));
    stos->nastepny->wierzcholek = s;
    stos->nastepny->nastepny = t;
}

// Euler
void DFS_Euler(int **tabela, int n_wierzcholkow, int n_krawedzi) {

    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;
    printf(" Cykl Eulera\n\n  ");
    for (int i = 0; i < n_wierzcholkow; i++)
        if (odwiedzony[i] == 0)
            rek_DFS_Euler(tabela, n_wierzcholkow, n_krawedzi, i, odwiedzony);
    printf("\n\n");
    free(odwiedzony);
}

// Euler - wewn
void rek_DFS_Euler(int **tabela, int n_wierzcholkow, int n_krawedzi, int s,
                    int *odwiedzony) {
    printf("%d ", s);
    odwiedzony[s] = 1;

    for (int i = 0; i < n_wierzcholkow; i++)
        if (tabela[s][i] == 1) {

            int docelowy = -1;
            for (int j = 0; docelowy == -1; j++)
                if (tabela[j][i] == -1)
                    docelowy = j;

            if (odwiedzony[docelowy] == 0)
                rek_DFS_Euler(tabela, n_wierzcholkow, n_krawedzi, docelowy, odwiedzony);
        }
}

// Hamilton
void DFS_Hamilton(int **tabela, int n_wierzcholkow, int n_krawedzi) {

    int *odwiedzony = malloc(sizeof(int) * n_wierzcholkow);
    for (int i = 0; i < n_wierzcholkow; i++)
        odwiedzony[i] = 0;
    printf(" Cykl Hamiltona\n\n  ");
    for (int i = 0; i < n_wierzcholkow; i++)
        if (odwiedzony[i] == 0)
            rek_DFS_Hamilton(tabela, n_wierzcholkow, n_krawedzi, i, odwiedzony);
    printf("\n\n");
    free(odwiedzony);
}

// Hamilton - wewn
void rek_DFS_Hamilton(int **tabela, int n_wierzcholkow, int n_krawedzi, int s,
                    int *odwiedzony) {
                        
    odwiedzony[s] = 1;

    for (int i = 0; i < n_wierzcholkow; i++)
        if (tabela[s][i] == 1) {

            int docelowy = -1;
            for (int j = 0; docelowy == -1; j++)
                if (tabela[j][i] == -1)
                    docelowy = j;

            if (odwiedzony[docelowy] == 0)
                rek_DFS_Hamilton(tabela, n_wierzcholkow, n_krawedzi, docelowy, odwiedzony);
        }
    printf("%d ", s);
}
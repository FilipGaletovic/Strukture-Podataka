#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

struct Osoba;
typedef struct Osoba* pozicija;

typedef struct Osoba {
    char ime[MAX];
    char prez[MAX];
    int god;
    pozicija next;
} osoba;

pozicija kreirajosobu();
void unospocetak(pozicija);
void unoskraj(pozicija);
void ispis(pozicija);
pozicija pretrazi(pozicija, char[MAX]);
void brisi(pozicija, char[MAX]);
void izbrisilistu(pozicija);
void dodaj_ispred(pozicija, char[MAX]);
void dodaj_iza(pozicija, char[MAX]);
void sort_po_prezimenu(pozicija);
void upisi_u_datoteku(pozicija, const char*);
void ucitaj_iz_datoteke(pozicija, const char*);

int main() {
    int izbor;
    char prezime[MAX];
    pozicija head = (pozicija)malloc(sizeof(osoba));
    if (head == NULL) {
        printf("Error allocating memory \n");
        return -1;
    }
    head->next = NULL;

    do {
        printf("\n\nIzaberi opciju:\n");
        printf("1 - Dodaj novi element na pocetak liste\n");
        printf("2 - Ispis liste\n");
        printf("3 - Dodaj novi element na kraj liste\n");
        printf("4 - Pronadji element po prezimenu\n");
        printf("5 - Obrisi element\n");
        printf("6 - Dodaj element iza odredjenog elementa\n");
        printf("7 - Dodaj element ispred odredjenog elementa\n");
        printf("8 - Sortiraj listu po prezimenu\n");
        printf("9 - Upisi listu u datoteku i citaj iz nje\n");
        printf("10 - Kraj programa\n");

        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            unospocetak(head);
            break;
        case 2:
            ispis(head);
            break;
        case 3:
            unoskraj(head);
            break;
        case 4:
            printf("Unesi prezime: ");
            scanf("%s", prezime);
            if (pozicija trazeno = pretrazi(head, prezime)){
            
                printf("Ime: %s, Prezime: %s, Godina: %d\n", trazeno->ime, trazeno->prez, trazeno->god);
            }
            else {
                printf("Nema elementa\n");
            }
            break;
        case 5:
            printf("Unesi prezime osobe koju zelis izbrisati: ");
            scanf("%s", prezime);
            brisi(head, prezime);
            break;
        case 6:
            printf("Unesi prezime osobe iza koje unosimo novu osobu: ");
            scanf("%s", prezime);
            dodaj_iza(head, prezime);
            break;
        case 7:
            printf("Unesi prezime osobe ispred koje unosimo novu osobu: ");
            scanf("%s", prezime);
            dodaj_ispred(head, prezime);
            break;
        case 8:
            sort_po_prezimenu(head);
            break;
        case 9:
            upisi_u_datoteku(head, "osobe.txt");
            izbrisilistu(head);  
            ucitaj_iz_datoteke(head, "osobe.txt");
            break;
        case 10:
            izbrisilistu(head);
            break;
        default:
            printf("Greska\n");
            break;
        }
    } while (izbor != 10);

    free(head);
    return 0;
}

pozicija kreirajosobu() {
    pozicija os = (pozicija)malloc(sizeof(osoba));
    if (!os) return NULL;
    printf("Unesi ime: ");
    scanf("%s", os->ime);
    printf("Unesi prezime: ");
    scanf("%s", os->prez);
    printf("Unesi godinu: ");
    scanf("%d", &os->god);
    os->next = NULL;
    return os;
}

void dodaj_ispred(pozicija head, char prezime[MAX]) {
    pozicija nova_osoba = kreirajosobu();
    pozicija temp = head;
    while (temp->next != NULL && strcmp(temp->next->prez, prezime) != 0) {
        temp = temp->next;
    }
    if (temp->next != NULL) {
        nova_osoba->next = temp->next;
        temp->next = nova_osoba;
    }
    else {
        printf("Nije pronadjen element s prezimenom %s\n", prezime);
        free(nova_osoba);
    }
}

void dodaj_iza(pozicija head, char prezime[MAX]) {
    pozicija nova_osoba = kreirajosobu();
    pozicija trazena = pretrazi(head, prezime);
    if (trazena != NULL) {
        nova_osoba->next = trazena->next;
        trazena->next = nova_osoba;
    }
    else {
        printf("Nije pronadjen element s prezimenom %s\n", prezime);
        free(nova_osoba);
    }
}

void unospocetak(pozicija head) {
    pozicija novi = kreirajosobu();
    novi->next = head->next;
    head->next = novi;
}

void unoskraj(pozicija head) {
    pozicija novi = kreirajosobu();
    pozicija zadnji = head;
    while (zadnji->next != NULL) {
        zadnji = zadnji->next;
    }
    zadnji->next = novi;
}

void ispis(pozicija head) {
    pozicija temp = head->next;
    while (temp != NULL) {
        printf("Ime: %s, Prezime: %s, Godina: %d\n", temp->ime, temp->prez, temp->god);
        temp = temp->next;
    }
}

pozicija pretrazi(pozicija head, char prezime[MAX]) {
    pozicija temp = head->next;
    while (temp != NULL) {
        if (strcmp(temp->prez, prezime) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void brisi(pozicija head, char prezime[MAX]) {
    pozicija temp = head;
    while (temp->next != NULL && strcmp(temp->next->prez, prezime) != 0) {
        temp = temp->next;
    }
    if (temp->next != NULL) {
        pozicija za_brisanje = temp->next;
        temp->next = za_brisanje->next;
        free(za_brisanje);
    }
    else {
        printf("Nema osobe s prezimenom %s\n", prezime);
    }
}

void izbrisilistu(pozicija head) {
    pozicija temp;
    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
}

void sort_po_prezimenu(pozicija head) {
    pozicija i, j, prev_i, prev_j, temp;
    for (i = head->next; i != NULL && i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->prez, j->prez) > 0) {
                char temp_ime[MAX], temp_prez[MAX];
                int temp_god;
                strcpy(temp_ime, i->ime);
                strcpy(temp_prez, i->prez);
                temp_god = i->god;

                strcpy(i->ime, j->ime);
                strcpy(i->prez, j->prez);
                i->god = j->god;

                strcpy(j->ime, temp_ime);
                strcpy(j->prez, temp_prez);
                j->god = temp_god;
            }
        }
    }
}

void upisi_u_datoteku(pozicija head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Greska pri otvaranju datoteke\n");
        return;
    }
    pozicija temp = head->next;
    while (temp) {
        fprintf(fp, "%s %s %d\n", temp->ime, temp->prez, temp->god);
        temp = temp->next;
    }
    fclose(fp);
}

void ucitaj_iz_datoteke(pozicija head, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Greska pri otvaranju datoteke\n");
        return;
    }

    pozicija current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    char ime[MAX], prez[MAX];
    int god;
    while (fscanf(fp, "%s %s %d", ime, prez, &god) == 3) {
        pozicija nova_osoba = (pozicija)malloc(sizeof(osoba));
        strcpy(nova_osoba->ime, ime);
        strcpy(nova_osoba->prez, prez);
        nova_osoba->god = god;
        nova_osoba->next = NULL;

        current->next = nova_osoba;
        current = current->next;
    }

    fclose(fp);
}

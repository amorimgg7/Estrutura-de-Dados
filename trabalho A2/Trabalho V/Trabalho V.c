#include <stdio.h>
#include <stdlib.h>

struct noGrafo {
    int info;
    struct noGrafo *proxNo;
    struct noArco *arcos;
};
typedef struct noGrafo *PtrNoGrafo;

struct noArco {
    int peso;
    struct noGrafo *no;
    struct noArco *proxArco;
};
typedef struct noArco *PtrNoArco;

// Insere um nó p no grafo g
void insertnode(PtrNoGrafo *g, PtrNoGrafo p) {
    p->proxNo = *g;
    *g = p;
}

// Inclui um arco de peso p de no1 até no2
void joinwtInfo(PtrNoGrafo g, int no1, int no2, int p) {
    PtrNoGrafo ptr1 = NULL, ptr2 = NULL;
    PtrNoGrafo temp = g;

    // Encontrar os nós no1 e no2
    while (temp != NULL) {
        if (temp->info == no1) {
            ptr1 = temp;
        }
        if (temp->info == no2) {
            ptr2 = temp;
        }
        temp = temp->proxNo;
    }

    if (ptr1 != NULL && ptr2 != NULL) {
        PtrNoArco novoArco = (PtrNoArco)malloc(sizeof(struct noArco));
        novoArco->peso = p;
        novoArco->no = ptr2;
        novoArco->proxArco = ptr1->arcos;
        ptr1->arcos = novoArco;
    }
}

// Verifica se no1 e no2 são adjacentes
int adjacent(PtrNoGrafo g, int no1, int no2) {
    PtrNoGrafo temp = g;

    // Encontrar o nó no1
    while (temp != NULL) {
        if (temp->info == no1) {
            PtrNoArco arco = temp->arcos;
            // Verificar se existe um arco de no1 para no2
            while (arco != NULL) {
                if (arco->no->info == no2) {
                    return 1;
                }
                arco = arco->proxArco;
            }
        }
        temp = temp->proxNo;
    }
    return 0;
}

// Mostra todos os nós do grafo, seus arcos e o peso de cada arco
void mostraGrafo(PtrNoGrafo g) {
    PtrNoGrafo p;
    PtrNoArco a;
    p = g;
    while (p != NULL) {
        printf("Adjacentes de %d:\n", p->info);
        a = p->arcos;
        while (a != NULL) {
            printf("\t%d (%d)\n", a->no->info, a->peso);
            a = a->proxArco;
        }
        p = p->proxNo;
    }
}

int main(void) {
    PtrNoGrafo g = NULL;

    // Criando nós do grafo
    PtrNoGrafo no1 = (PtrNoGrafo)malloc(sizeof(struct noGrafo));
    no1->info = 1;
    no1->arcos = NULL;
    insertnode(&g, no1);

    PtrNoGrafo no2 = (PtrNoGrafo)malloc(sizeof(struct noGrafo));
    no2->info = 2;
    no2->arcos = NULL;
    insertnode(&g, no2);

    PtrNoGrafo no3 = (PtrNoGrafo)malloc(sizeof(struct noGrafo));
    no3->info = 3;
    no3->arcos = NULL;
    insertnode(&g, no3);

    // Criando arcos entre os nós
    joinwtInfo(g, 1, 2, 10);
    joinwtInfo(g, 2, 3, 20);
    joinwtInfo(g, 3, 1, 30);

    // Mostrando o grafo
    mostraGrafo(g);

    // Verificando adjacências
    printf("Adjacente 1 -> 2: %d\n", adjacent(g, 1, 2)); // Deve retornar 1
    printf("Adjacente 1 -> 3: %d\n", adjacent(g, 1, 3)); // Deve retornar 0
    printf("Adjacente 3 -> 1: %d\n", adjacent(g, 3, 1)); // Deve retornar 1

    return 0;
}

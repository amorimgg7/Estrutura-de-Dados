/*
Grupo composto por 6 pessoas:
    - Gabriel Gomes Amorim          -   1230121318
    - Christopher Chaider           -   1230116675
    - Lygia Menezes de Lima         -   1230210137
    - Camilla Carolina              -   1230102765
    - Matheus de Souza da Fonseca   -   1230114114
    - Bruno Verduc Martins Costa    -   1230106373
*/


#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void Cabecalho(const char *titulo) {
    char str[60];
    int num_spaces = 5;
    char spaces[11];
    for(int i = 0; i < num_spaces; i++) {
        spaces[i] = ' ';
    }
    spaces[num_spaces] = '\0';
    sprintf(str, "%s%s", spaces, titulo);
    system(CLEAR);
    printf("/");
    for(int i = 0; i < 60; i++) {
        printf("¨");
    }
    printf("\\\n");
    printf("%s\n", str);
    printf("\\");
    for(int i = 0; i < 60; i++) {
        printf("_");
    }
    printf("/\n");
}

void Rodape(bool pause) {
    printf("\\");
    for (int i = 0; i < 60; i++) {
        printf("_");
    }
    printf("/\n");
    if (pause) {
        system("pause");
    }
}



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

// Insere um nó p no grafo g em ordem crescente
void insertnode(PtrNoGrafo *g, PtrNoGrafo p) {
    if (*g == NULL || (*g)->info > p->info) {
        p->proxNo = *g;
        *g = p;
    } else {
        PtrNoGrafo current = *g;
        while (current->proxNo != NULL && current->proxNo->info < p->info) {
            current = current->proxNo;
        }
        p->proxNo = current->proxNo;
        current->proxNo = p;
    }
}

// Inclui um arco de peso p de no1 até no2
void joinwtInfo(PtrNoGrafo g, int x1, int x2, int p) {
    PtrNoGrafo ptr1 = NULL, ptr2 = NULL;
    PtrNoGrafo temp = g;

    // Encontrar os nós x1 e x2
    while (temp != NULL) {
        if (temp->info == x1) {
            ptr1 = temp;
        }
        if (temp->info == x2) {
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
int inAdjacent(PtrNoGrafo g, int x1, int x2) {
    PtrNoGrafo temp = g;

    // Encontrar o nó x1
    while (temp != NULL) {
        if (temp->info == x1) {
            PtrNoArco arco = temp->arcos;
            // Verificar se existe um arco de x1 para x2
            while (arco != NULL) {
                if (arco->no->info == x2) {
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
    setlocale(LC_ALL, "Portuguese");
    Cabecalho("Representação do Grafo");
    // Criando nós do grafo (de 0 a 7)
    for (int i = 0; i < 8; i++) {
        PtrNoGrafo no = (PtrNoGrafo)malloc(sizeof(struct noGrafo));
        no->info = i;
        no->arcos = NULL;
        insertnode(&g, no);
    }

    // Criando arcos entre os nós conforme a imagem
    joinwtInfo(g, 0, 3, 2);
    joinwtInfo(g, 1, 0, 1);
    joinwtInfo(g, 1, 2, 3);
    joinwtInfo(g, 3, 0, 2);
    joinwtInfo(g, 3, 4, 2);
    joinwtInfo(g, 3, 2, 4);
    joinwtInfo(g, 4, 4, 1);
    joinwtInfo(g, 5, 6, 3);
    //joinwtInfo(g, 5, 6, 80);
    //joinwtInfo(g, 6, 7, 90);

    // Mostrando o grafo
    mostraGrafo(g);

    // Verificando adjacências
    ////printf("Adjacente 0 -> 1: %d\n", adjacent(g, 0, 1)); // Deve retornar 1
    ////printf("Adjacente 0 -> 3: %d\n", adjacent(g, 0, 3)); // Deve retornar 0
    ////printf("Adjacente 5 -> 6: %d\n", adjacent(g, 5, 6)); // Deve retornar 1
Rodape(false);
    return 0;
}

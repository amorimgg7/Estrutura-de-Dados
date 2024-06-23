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

// Insere um no p no grafo g
void insertnode(PtrNoGrafo *g, PtrNoGrafo p) {
	// Escreva o codigo da funcao
}

// Inclui um arco de peso p de no1 ate no2
void joinwtInfo(PtrNoGrafo g, int no1, int no2, int p) {
	// Escreva o codigo da funcao
}

// Verifica se no1 e no2 sao adjacentes
int adjacent(PtrNoGrafo g, int no1, int no2) {
	// Escreva o codigo da funcao
}

// Mostra todos os nos do grafo, seus arcos e o peso de cada arco
void mostraGrafo(PtrNoGrafo g) {
	PtrNoGrafo p;
	PtrNoArco a;
	p = g;
	while (p != NULL) {
		printf("Adjacentes de %d:\n", p->info);
		a = p->arcos;
		while (a != NULL) {
			printf("\t%d (%d)", a->no->info, a->peso);
			a = a->proxArco;
		}
		printf("\n");
		p = p->proxNo;
	}
}

 int main(void) {
	 PtrNoGrafo g;
	 // Coloque aqui o codigo ou a chamada da funcao que monta o grafo
	 mostraGrafo(g);
}
 

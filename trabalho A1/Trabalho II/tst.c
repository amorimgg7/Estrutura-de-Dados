#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 5
#define TAM_PLACA 8

typedef struct {
    char placa[TAM_PLACA];
    int vezes_movido;
} Carro;

typedef struct {
    Carro carros[MAX_CARROS];
    int contador_manobras_total;
    int topo;
} Estacionamento;

Estacionamento* criarEstacionamento() {
    Estacionamento* est = (Estacionamento*)malloc(sizeof(Estacionamento));
    est->topo = -1;
    est->contador_manobras_total = 0;
    return est;
}

void empilhar(Estacionamento* est, char placa[]) {
    if (est->topo < MAX_CARROS - 1) {
        for (int i = est->topo; i >= 0; i--) {
            est->carros[i + 1] = est->carros[i];
            est->carros[i + 1].vezes_movido++;
        }
        strcpy(est->carros[0].placa, placa);
        est->carros[0].vezes_movido = 0;
        est->topo++;
        printf("Carro %s entrou no estacionamento.\n", placa);
    } else {
        printf("Não há vaga para o carro %s.\n", placa);
    }
}

void desempilhar(Estacionamento* est, char placa[]) {
    int i, index = -1;
    for (i = 0; i <= est->topo; i++) {
        if (strcmp(est->carros[i].placa, placa) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        est->contador_manobras_total += est->carros[index].vezes_movido;
        for (i = index; i < est->topo; i++) {
            strcpy(est->carros[i].placa, est->carros[i + 1].placa);
            est->carros[i].vezes_movido = est->carros[i + 1].vezes_movido - 1;
        }
        est->topo--;
        printf("Carro %s saiu do estacionamento após %d manobras.\n", placa, est->carros[index].vezes_movido);
    } else {
        printf("Carro %s não está no estacionamento.\n", placa);
    }
}

void mostrarEstacionamento(Estacionamento* est) {
    printf("\nCarros no estacionamento:\n");
    for (int i = 0; i <= est->topo; i++) {
        printf("%d: %s (Movido %d vezes)\n", i+1, est->carros[i].placa, est->carros[i].vezes_movido);
    }
    printf("\n");
}

void processarEntradaSaida(Estacionamento* est, char acao, char placa[]) {
    if (acao == 'E') {
        empilhar(est, placa);
    } else if (acao == 'S') {
        desempilhar(est, placa);
    }
}

int main() {
    Estacionamento* est = criarEstacionamento();

    char acao;
    char placa[TAM_PLACA];

    do {
        printf("Digite a ação (E para entrada, S para saída, Q para sair): ");
        scanf(" %c", &acao);

        if (acao != 'Q') {
            printf("Digite a placa do carro: ");
            scanf("%s", placa);
        }

        if (acao == 'E' || acao == 'S') {
            processarEntradaSaida(est, acao, placa);
            mostrarEstacionamento(est);
        } else if (acao != 'Q') {
            printf("Ação inválida.\n");
        }

    } while (acao != 'Q');

    printf("\nRelatório de movimentação de carros:\n");
    for (int i = 0; i <= est->topo; i++) {
        printf("Carro %s: Movido %d vezes\n", est->carros[i].placa, est->carros[i].vezes_movido);
    }
    printf("Total de manobras: %d\n", est->contador_manobras_total);

    free(est);
    return 0;
}

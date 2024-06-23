/*
Grupo composto por 6 pessoas:
    - Gabriel Gomes Amorim    -   123121318
    - Christopher Chaider - 1230116675
    - Lygia Menezes de Lima - 1230210137
    - Camilla Carolina - 1230102765
    - Matheus de Souza da Fonseca - 1230114114
    - Bruno Verduc Martins Costa - 1230106373
*/
# include <locale.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <stdbool.h>
# include <stdio.h>
# ifdef _WIN32
# define CLEAR "cls"
# else
# define CLEAR "clear"
# endif
# define MAX_CARROS 5
# define TAM_PLACA 8

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
        //Rodape(true);
    } else {
        printf("Não há vaga para o carro %s.\n", placa);
        Rodape(true);
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
            est->carros[i].vezes_movido = est->carros[i + 1].vezes_movido + 1;
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
    setlocale(LC_ALL, "Portuguese");
    Estacionamento* est = criarEstacionamento();
    char acao;
    char placa[TAM_PLACA];
    do {/*
Grupo composto por 6 pessoas:
    - Gabriel Gomes Amorim    -   123121318
    - Christopher Chaider - 1230116675
    - Lygia Menezes de Lima - 1230210137
    \-
    \-
    \-
*/
# include <locale.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <stdbool.h>
# include <stdio.h>
# ifdef _WIN32
# define CLEAR "cls"
# else
# define CLEAR "clear"
# endif
# define MAX_CARROS 5
# define TAM_PLACA 8

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
        //Rodape(true);
    } else {
        printf("Não há vaga para o carro %s.\n", placa);
        Rodape(true);
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

        for (i = index; i < est->topo; i++) {
            strcpy(est->carros[i].placa, est->carros[i + 1].placa);
            est->carros[i].vezes_movido = est->carros[i + 1].vezes_movido + 1;
        }
        est->contador_manobras_total += est->carros[index].vezes_movido;
        est->topo--;
        printf("Carro %s saiu do estacionamento após %d manobras.\n", placa, est->carros[index].vezes_movido);
    } else {
        printf("Carro %s não está no estacionamento.\n", placa);
    }
}

void mostrarEstacionamento(Estacionamento* est) {
    printf("\nCarros no estacionamento:\n");
    est->contador_manobras_total = 0;
    for (int i = 0; i <= est->topo; i++) {
        printf("%d: %s (Movido %d vezes)\n", i+1, est->carros[i].placa, est->carros[i].vezes_movido);
        est->contador_manobras_total += est->carros[i].vezes_movido;
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
    setlocale(LC_ALL, "Portuguese");
    Estacionamento* est = criarEstacionamento();
    char acao;
    char placa[TAM_PLACA];
    do {
        Cabecalho("ENTRADA E SAIDA DE VEICULOS");
        mostrarEstacionamento(est);
        Rodape(false);
        printf("Digite a ação (E para entrada, S para saída, Q para sair): ");
        scanf(" %c", &acao);
        if (acao != 'Q') {
            printf("Digite a placa do carro: ");
            scanf("%s", placa);

            if (strlen(placa) > 7) {
                printf("Placa inválida. Por favor, digite uma placa com até 7 caracteres.\n");
                Rodape(true);
                continue;
            }
        }
        if (acao == 'E' || acao == 'S') {
            processarEntradaSaida(est, acao, placa);
        } else if (acao != 'Q') {
            printf("Ação inválida.\n");
        }
    } while (acao != 'Q');
    Cabecalho("Entrada e Saída de Veículos");
    printf("\nRelatório de movimentação de carros:\n");
    for (int i = 0; i <= est->topo; i++) {
        printf("Carro %s: Movido %d vezes\n", est->carros[i].placa, est->carros[i].vezes_movido);
    }
    printf("Total de manobras: %d\n", est->contador_manobras_total);
    Rodape(false);
    free(est);
    return 0;
}
        Cabecalho("ENTRADA E SAIDA DE VEICULOS");
        mostrarEstacionamento(est);
        Rodape(false);
        printf("Digite a ação (E para entrada, S para saída, Q para sair): ");
        scanf(" %c", &acao);
        if (acao != 'Q') {
            printf("Digite a placa do carro: ");
            scanf("%s", placa);

            if (strlen(placa) > 7) {
                printf("Placa inválida. Por favor, digite uma placa com até 7 caracteres.\n");
                Rodape(true);
                continue;
            }
        }
        if (acao == 'E' || acao == 'S') {
            processarEntradaSaida(est, acao, placa);
        } else if (acao != 'Q') {
            printf("Ação inválida.\n");
        }
    } while (acao != 'Q');
    Cabecalho("Entrada e Saída de Veículos");
    printf("\nRelatório de movimentação de carros:\n");
    for (int i = 0; i <= est->topo; i++) {
        printf("Carro %s: Movido %d vezes\n", est->carros[i].placa, est->carros[i].vezes_movido);
    }
    printf("Total de manobras: %d\n", est->contador_manobras_total);
    Rodape(false);
    free(est);
    return 0;
}

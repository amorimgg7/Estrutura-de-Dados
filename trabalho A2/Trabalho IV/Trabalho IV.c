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
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define TAM_HASH 100
#define MAX_NOME 20

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

typedef enum {Reservada, Variavel, Constante, Fim} TipoToken;
char *str_TipoToken[] = {"Reservada", "Variavel", "Constante", "Fim"};
typedef enum {Inteiro, Real, Caractere, String}  TipoIdentificador;
char *str_TipoIdentificador[] = {"Inteiro", "Real", "Caractere", "String"};

typedef struct LineNode {
    int valor;
    struct LineNode *next;
} LineNode;

typedef struct Symbol {
    char nome[MAX_NOME + 1];
    LineNode *valores;
    struct Symbol *next;
} Symbol;

Symbol *hashTable[TAM_HASH];

unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TAM_HASH;
}

void initHashTable() {
    for (int i = 0; i < TAM_HASH; i++) {
        hashTable[i] = NULL;
    }
}

void insereLinha(LineNode **valores, int valor) {
    LineNode *newNode = (LineNode *)malloc(sizeof(LineNode));
    newNode->valor = valor;
    newNode->next = *valores;
    *valores = newNode;
}

void insereTabela(Symbol **table, const char *nome, int valor) {
    unsigned int index = hash(nome);
    Symbol *entry = table[index];

    while (entry != NULL) {
        if (strcmp(entry->nome, nome) == 0) {
            insereLinha(&entry->valores, valor);
            return;
        }
        entry = entry->next;
    }

    Symbol *newEntry = (Symbol *)malloc(sizeof(Symbol));
    strncpy(newEntry->nome, nome, MAX_NOME);
    newEntry->nome[MAX_NOME] = '\0';
    newEntry->valores = NULL;
    insereLinha(&newEntry->valores, valor);
    newEntry->next = table[index];
    table[index] = newEntry;
}

void imprimeTabela(Symbol **table) {
    Cabecalho("Tabela Salva");
    for (int i = 0; i < TAM_HASH; i++) {
        Symbol *entry = table[i];
        while (entry != NULL) {
            printf("%s -> ", entry->nome);
            LineNode *valor = entry->valores;
            while (valor != NULL) {
                printf("%d", valor->valor);
                if (valor->next != NULL) {
                    printf(", ");
                }
                valor = valor->next;
            }
            printf("\n");
            entry = entry->next;
        }
    }
    Rodape(true);
}

void adicionarToken() {
    char nome[MAX_NOME + 1];
    char buffer[100];
    int valor;
    printf("Digite o nome do token (max %d letras): ", MAX_NOME);
    scanf("%99s", buffer);

    if (strlen(buffer) > MAX_NOME) {
    printf("Erro: Nome do token excede o limite de %d caracteres.\n", MAX_NOME);
    return;
    }

    strncpy(nome, buffer, MAX_NOME);
    nome[MAX_NOME] = '\0';

    printf("Digite o valor numérico: ");
    scanf("%d", &valor);
    insereTabela(hashTable, nome, valor);
}

int main(void) {
    initHashTable();
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    do {
        Cabecalho("Menu");
        printf("1. Adicionar token\n");
        printf("2. Mostrar tabela\n");
        printf("3. Sair\n");
        Rodape(false);
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarToken();
                break;
            case 2:
                imprimeTabela(hashTable);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}

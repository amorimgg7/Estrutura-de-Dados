
/*  Gabriel Gomes Amorim  -   1230121318    */

#include <locale.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para utilizar a função isdigit
#include <time.h>  // Para gerar números aleatórios

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define TABLE_SIZE 7
#define NAME_SIZE 50

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
        printf("-");
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

typedef struct Node {
    int code;
    char name[NAME_SIZE];
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

// Função hash aleatória
int randomHashFunction(int code) {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios
    return rand() % TABLE_SIZE; // Gera um índice aleatório entre 0 e TABLE_SIZE-1
}

// Função para inserir elemento na tabela hash usando a função hash aleatória
void insertElement(int code, char* name) {
    int index = randomHashFunction(code);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->code = code;
    strcpy(newNode->name, name);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Função para exibir todos os elementos da tabela hash
void displayTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        printf("Index %d: ", i);
        while (current != NULL) {
            printf("-> (%d - %s) ", current->code, current->name);
            current = current->next;
        }
        printf("\n");
    }
}

// Função para liberar memória alocada para a tabela hash
void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

// Função para verificar se a string contém apenas números
bool isNumeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    int choice;
    int code;
    char name[NAME_SIZE];
    char input[NAME_SIZE]; // Buffer para entrada de usuário

    // Inicializa a tabela hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    do {
        Cabecalho("Menu");
        printf("1. Inserir um elemento\n");
        printf("2. Exibir todos os elementos\n");
        printf("3. Sair\n");
        Rodape(false);
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Cabecalho("Insira o codigo do usuario");
                Rodape(false);
                scanf("%s", input);

                if (!isNumeric(input)) {
                    Cabecalho("Por favor, digite um numero para o codigo do usuario");
                    Rodape(true);
                    break;
                }

                code = atoi(input);

                Cabecalho("Insira o nome do usuario");
                Rodape(false);
                scanf("%s", name);
                insertElement(code, name);
                break;
            case 2:
                Cabecalho("Elementos cadastrados");
                displayTable();
                Rodape(true);
                break;
            case 3:
                freeTable();
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (choice != 3);

    return 0;
}

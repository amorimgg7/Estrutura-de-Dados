
/*  Gabriel Gomes Amorim  -   1230121318    */

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
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



// Estrutura para um nó da lista encadeada
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um nó no início da lista
void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Função para inserir um nó na posição especificada (0-indexed)
void insertAtPosition(Node** head, int data, int position) {
    if (position == 0) {
        insertAtHead(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Posicao invalida\n");
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Função para remover o penúltimo nó da lista
void removePenultimate(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("A lista nao possui penultimo elemento\n");
        return;
    }
    Node* temp = *head;
    while (temp->next->next != NULL && temp->next->next->next != NULL) {
        temp = temp->next;
    }
    Node* penultimate = temp->next;
    temp->next = penultimate->next;
    free(penultimate);
}

// Função para buscar um valor na lista
void search(Node* head, int value) {
    Node* temp = head;
    int position = 0;
    while (temp != NULL) {
        if (temp->data == value) {
            printf("Valor %d encontrado na posicao %d\n", value, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Valor %d não encontrado na lista\n", value);
}

// Função para imprimir a lista
void printList(Node* head) {
    Node* temp = head;
    int position = 0;
    while (temp != NULL) {
        printf("Posicao %d: %d\n", position, temp->data);
        temp = temp->next;
        position++;
    }
}

// Função para liberar a memória da lista
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Função para gerar valores aleatórios e adicioná-los à lista
void generateRandomValues(Node** head, int count) {
    for (int i = 0; i < count; i++) {
        int randomValue = rand() % 100; // Valores aleatórios entre 0 e 99
        insertAtHead(head, randomValue);
    }
    Cabecalho("Valores aleatorios adicionados");
    //printf("Lista após adicionar %d valores aleatórios:\n", count);
    printList(*head);
    Rodape(true);
}

// Função para adicionar um valor fornecido pelo usuário na segunda posição
void addUserValue(Node** head) {
    int userValue;
    Cabecalho("");
    printf("Digite um valor para adicionar na segunda posicao: \n");
    Rodape(false);
    scanf("%d", &userValue);
    insertAtPosition(head, userValue, 1);
    Cabecalho("Lista apos adicionar a segunda posicao");
    //printf("Lista após adicionar o valor %d na segunda posição:\n", userValue);
    printList(*head);
    Rodape(true);
}

// Função para remover o penúltimo elemento da lista e imprimir a lista
void removePenultimateAndPrint(Node** head) {
    removePenultimate(head);
    Cabecalho("Lista apos remover da penultima posicao");
    //printf("Lista após remover o penúltimo elemento:\n");
    printList(*head);
    Rodape(true);
}

// Função para buscar um valor na lista
void searchValue(Node* head) {
    int searchValue;
    Cabecalho("Digite um valor para buscar na lista");
    Rodape(false);
    scanf("%d", &searchValue);
    Cabecalho("Valor resultado");
    search(head, searchValue);
    Rodape(true);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    Node* head = NULL;
    int option;
    srand(time(NULL));

    do {
        Cabecalho("Menu");
        printf("1. Adicionar 5 valores aleatorios a lista\n");
        printf("2. Adicionar um valor na segunda posicao\n");
        printf("3. Remover o penultimo elemento\n");
        printf("4. Buscar um valor na lista\n");
        printf("5. Sair\n");
        Rodape(false);
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                generateRandomValues(&head, 5);
                break;
            case 2:
                addUserValue(&head);
                break;
            case 3:
                removePenultimateAndPrint(&head);
                break;
            case 4:
                searchValue(head);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida, tente novamente.\n");
        }
    } while (option != 5);

    freeList(head);
    return 5;
}

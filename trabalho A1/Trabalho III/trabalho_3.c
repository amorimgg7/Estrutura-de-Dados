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
# define MAX_PALAVRA 15

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


    for(int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");


    printf("%s\n", str);


    for(int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");
}

void pressioneQualquerTeclaParaContinuar() {
    printf("Pressione qualquer tecla para continuar...\n");
    fflush(stdout);  // Garante que a mensagem seja impressa antes de esperar entrada
    getchar();  // Espera pelo usuário pressionar uma tecla
    getchar();  // Para consumir o newline deixado pelo enter
}

void Rodape(bool pause) {
    for (int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");
    if (pause) {
        #ifdef _WIN32
            system("pause");
        #else
            pressioneQualquerTeclaParaContinuar();
        #endif
    }
}

typedef struct NoArvore {
    char palavra[MAX_PALAVRA + 1];
    int frequencia;
    struct NoArvore *esquerda, *direita;
} NoArvore;

void inserirNaArvore(NoArvore **raiz, char palavra[]) {
    if (*raiz == NULL) {
        *raiz = (NoArvore *)malloc(sizeof(NoArvore));
        strcpy((*raiz)->palavra, palavra);
        (*raiz)->frequencia = 1;
        (*raiz)->esquerda = (*raiz)->direita = NULL;
    } else {
        int comparacao = strcmp(palavra, (*raiz)->palavra);
        if (comparacao < 0) {
            inserirNaArvore(&((*raiz)->esquerda), palavra);
        } else if (comparacao > 0) {
            inserirNaArvore(&((*raiz)->direita), palavra);
        } else {
            (*raiz)->frequencia++;
        }
    }
}

void emOrdem(NoArvore *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf(" - %s (%d)\n", raiz->palavra, raiz->frequencia);
        emOrdem(raiz->direita);
    }
}

void liberarArvore(NoArvore *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    NoArvore *raiz = NULL;
    char palavra[MAX_PALAVRA + 1];
    int opcao;
    do {
    Cabecalho("MENU DE OPÇÕES");
    printf("[1] Adicionar uma palavra\n");  // Mudança no texto do menu
    printf("[2] Mostrar palavras e frequências\n");  // Mudança no texto do menu
    printf("[0] Sair\n");
    Rodape(false);
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); // Consumir o newline deixado pelo scanf
    switch(opcao) {
        case 1:
            Cabecalho("DIGITE UMA PALAVRA");
            Rodape(false);
            printf("Digite a palavra (max %d caracteres): ", MAX_PALAVRA);
            scanf("%s", palavra);
            getchar(); // Consumir o newline deixado pelo scanf
            inserirNaArvore(&raiz, palavra);
            break;
        case 2:
            Cabecalho("LISTA DE PALAVRAS E FREQUENCIAS");
            emOrdem(raiz);
            Rodape(true);
            break;
        case 0:
            printf("\aSaindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
            Rodape(true);
    }
} while (opcao != 0);
    return 0;
}

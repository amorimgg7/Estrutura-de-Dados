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

void Cabecalho(const char *titulo) {
    char str[60]; // Ajuste o tamanho conforme necessário
    int num_spaces = 5;

    // Adicionando espaços antes do título
    char spaces[11]; // Espacos e um caractere nulo
    for(int i = 0; i < num_spaces; i++) {
        spaces[i] = ' ';
    }
    spaces[num_spaces] = '\0'; // Adicionando o caractere nulo

    // Formatar a string com os espaços e o título
    sprintf(str, "%s%s", spaces, titulo);

    system(CLEAR);

    // Imprimir a linha superior do cabeçalho
    for(int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");

    // Imprimir a string formatada com os espaços e o título
    printf("%s\n", str);

    // Imprimir a linha inferior do cabeçalho
    for(int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");
}

void Rodape(bool pause) {
    for (int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");
    if (pause) {
        system("pause");
    }
}

struct noLista {
	int info;
	struct noLista *proximo;
};
typedef struct noLista *PtrLista;

void adicionarInicio(PtrLista *lista, int valor) {
    PtrLista p;
    p = malloc(sizeof(struct noLista));
    if (p == NULL) {
        printf("Memoria insuficiente.\n");
        exit(0);
    }
    p->info = valor;

    if (*lista == NULL) { // Se a lista está vazia
        p->proximo = p;
        *lista = p;
    } else { // A lista não está vazia
        p->proximo = (*lista)->proximo;
        (*lista)->proximo = p;
    }
}

void adicionarFim(PtrLista *lista, int valor) {
    PtrLista p;
    p = malloc(sizeof(struct noLista));
    if (p == NULL) {
        printf("Memoria insuficiente.\n");
        exit(0);
    }
    p->info = valor;
    if (*lista == NULL) { // Se a lista está vazia
        p->proximo = p;
        *lista = p;
    } else { // A lista não está vazia
        p->proximo = (*lista)->proximo;
        (*lista)->proximo = p;
        *lista = p;
    }
}

void adicionarPosicao(PtrLista *lista, int valor, int posicao) {
    PtrLista p, atual;
    int i;

    p = malloc(sizeof(struct noLista));
    if (p == NULL) {
        printf("Memoria insuficiente.\n");
        exit(0);
    }
    p->info = valor;

    if (*lista == NULL) { // Se a lista está vazia
        if (posicao != 0) {
            printf("Posicao invalida.\n");
            free(p);
            return;
        }
        p->proximo = p;
        *lista = p;
    } else {
        atual = *lista;

        // Inserção no início da lista (posição 0)
        if (posicao == 0) {
            p->proximo = (*lista)->proximo;
            (*lista)->proximo = p;
            *lista = p; // Atualiza a referência de *lista para o novo nó
        } else {
            for (i = 0; i < posicao - 1; i++) {
                atual = atual->proximo;
                // Se atual voltar ao início, a posição é inválida
                if (atual == *lista) {
                    printf("Posicao invalida.\n");
                    free(p);
                    return;
                }
            }
            p->proximo = atual->proximo;
            atual->proximo = p;
        }
    }
}

void listarTudo(PtrLista lista) {
	PtrLista p;
	printf("Conteudo da lista:");
	if (lista!=NULL) {
		p = lista;
		int count = 0;
		do {
			p = p->proximo;
			count++;
            printf("\n[%d] - ", count);
			printf("%d", p->info);
		} while(p!=lista);
	}
	printf("\n");
}

void mostrarPosicao(PtrLista lista, int posicao) {
    PtrLista atual = lista;
    int i;

    if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    for (i = 0; i < posicao; i++) {
        atual = atual->proximo;
        // Se atual voltar ao início, a posição é inválida
        if (atual == lista) {
            //printf("Posicao invalida.\n");
            i = lista;  // Define i como a própria lista
            printf("Elemento na posicao atual: %d\n", atual->info);
            return;
        }
    }
    printf("Elemento na posicao %d: %d\n", posicao, atual->info);
}

int removeInicio(PtrLista *lista) {
	PtrLista p;
	int valor;
	if (*lista==NULL) {
		printf("Erro: lista vazia.\n");
		return -1;
	}
	p = (*lista)->proximo;
	valor = p->info;
	if (p != p->proximo) // Se tem mais de um item na lista
		(*lista)->proximo = p->proximo;
	else // Se tem somente um item na lista
		*lista = NULL;
	free(p);
	return valor;
}

int removeFim(PtrLista *lista) {
    PtrLista p, prev;
    int valor;

    if (*lista == NULL) {
        printf("Erro: lista vazia.\n");
        return -1;
    }

    p = *lista;

    if (p->proximo == p) { // Se tem somente um item na lista
        valor = p->info;
        free(p);
        *lista = NULL;
    } else { // Se tem mais de um item na lista
        prev = p;
        while (prev->proximo != *lista) { // Encontrar o penúltimo nó
            prev = prev->proximo;
        }
        valor = (*lista)->info;
        prev->proximo = (*lista)->proximo; // O penúltimo nó aponta para o primeiro nó
        free(*lista);
        *lista = prev; // Atualiza o ponteiro da lista para o penúltimo nó, que agora é o último
    }

    return valor;
}

void removerPosicao(PtrLista *lista, int posicao) {
    PtrLista atual, anterior;
    int i, tamanho = 0;

    if (*lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    atual = *lista;

    // Calcula o tamanho da lista
    do {
        tamanho++;
        atual = atual->proximo;
    } while (atual != *lista);

    atual = *lista;

    // Se a lista tem apenas um elemento
    if (atual->proximo == atual) {
        if (posicao == 0) {
            free(atual);
            *lista = NULL;
        } else {
            printf("Posicao invalida.\n");
        }
        return;
    }

    // Remoção do início da lista (posição 0)
    if (posicao == 0) {
        // Encontra o último nó para atualizar o ponteiro circular
        while (atual->proximo != *lista) {
            atual = atual->proximo;
        }
        PtrLista temp = (*lista)->proximo;
        atual->proximo = temp;
        free(*lista);
        *lista = temp;

    }
    else if (posicao == tamanho) { // Verifica se é o último elemento
        removeFim(lista);

    }
        else {
        anterior = atual;
        for (i = 0; i < posicao; i++) {
            anterior = atual;
            atual = atual->proximo;
            // Se atual voltar ao início, a posição é inválida
            if (atual == *lista) {
                printf("Posicao invalida.\n");
                return;
            }
        }
        anterior->proximo = atual->proximo;
        free(atual);
    }
}

void limparLista(PtrLista *lista) {
    if (*lista == NULL) {
        return; // A lista já está vazia
    }

    PtrLista atual = (*lista)->proximo; // Começa no primeiro nó
    PtrLista proximo;

    while (atual != *lista) { // Percorre até o último nó
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    // Finalmente, libera o último nó
    free(*lista);

    // Lista os elementos antes de definir a lista como vazia
    listarTudo(*lista);

    *lista = NULL; // Define a lista como vazia
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    PtrLista lista=NULL, p;
	int posicao;
	int valor;
    int opcao;

    do {
        //system(CLEAR); // Limpa a tela antes de exibir o menu
        Cabecalho("MENU DE OPÇÕES");
        printf("[1] Adicionar no início da Lista\n");
        printf("[2] Adicionar no final da Lista\n");
        printf("[3] Adicionar em um ponto expecífico da Lista\n");
        printf("[4] Listar todos os elementos da lista\n");
        printf("[5] Listar um elemento expecífico da lista\n");
        printf("[6] Excluir do início da Lista\n");
        printf("[7] Excluir do final da Lista\n");
        printf("[8] Excluir de um ponto Expecífico da Lista\n");
        printf("[9] Liberar os elementos e mostrar a lista vazia\n");
        printf("[0] Sair\n");
        Rodape(false);
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                Cabecalho("Adicionar no início da Lista");
                listarTudo(lista);
                Rodape(false);
                printf("\nInforme um valor: ");
				scanf("%d", &valor);
				adicionarInicio(&lista, valor);
                break;
            case 2:
                Cabecalho("Adicionar no final da Lista");
                listarTudo(lista);
                Rodape(false);
                printf("\nInforme um valor: ");
                scanf("%d", &valor);
                adicionarFim(&lista, valor);
                break;
            case 3:
                Cabecalho("Adicionar em um ponto expecífico da Lista");
                listarTudo(lista);
                Rodape(false);
                posicao = 0;
                printf("\nPosição: ");
                scanf("%d", &posicao);
                printf("\nInforme um valor: ");
                scanf("%d", &valor);
                adicionarPosicao(&lista, valor, posicao);
                break;
            case 4:
                Cabecalho("Listar todos os elementos da lista");
                listarTudo(lista);
                Rodape(false);
                break;
            case 5:
                Cabecalho("Listar um elemento expecífico da lista");
                listarTudo(lista);
                Rodape(false);
                printf("\nPosição: ");
                scanf("%d", &posicao);
                mostrarPosicao(lista, posicao);

                break;
            case 6:
                Cabecalho("Excluir do início da Lista");
                //CHAME AQUI A FUNÇÃO
                printf("Item removido do Início!\n");
                Rodape(false);
                removeInicio(&lista);
                break;
            case 7:
                Cabecalho("Item removido do Fim!");
                printf("Item removido!\n");
                Rodape(false);
                removeFim(&lista);
                break;
            case 8:
                Cabecalho("Excluir de um ponto Expecífico da Lista");
                listarTudo(lista);
                Rodape(false);
                posicao = 0;
                printf("\nPosição: ");
                scanf("%d", &posicao);
                removerPosicao(&lista, posicao);
                break;
            case 9:
                Cabecalho("Liberar os elementos e mostrar a lista vazia");
                limparLista(&lista);
                printf("A seguinte lista foi limpa!\n");
                Rodape(false);
                break;
            case 0:
                printf("\aSaindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

        // Espera por uma entrada do usuário antes de limpar a tela e exibir o menu novamente
        printf("\nPressione ENTER para continuar...");
        while (getchar() != '\n');
        getchar(); // Aguarda a entrada do usuário
    } while (opcao != 0);

    return 0;
}

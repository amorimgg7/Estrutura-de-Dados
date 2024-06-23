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
    char str[60]; // Ajuste o tamanho conforme necess�rio
    int num_spaces = 5;

    // Adicionando espa�os antes do t�tulo
    char spaces[11]; // Espacos e um caractere nulo
    for(int i = 0; i < num_spaces; i++) {
        spaces[i] = ' ';
    }
    spaces[num_spaces] = '\0'; // Adicionando o caractere nulo

    // Formatar a string com os espa�os e o t�tulo
    sprintf(str, "%s%s", spaces, titulo);

    system(CLEAR);

    // Imprimir a linha superior do cabe�alho
    for(int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");

    // Imprimir a string formatada com os espa�os e o t�tulo
    printf("%s\n", str);

    // Imprimir a linha inferior do cabe�alho
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

    if (*lista == NULL) { // Se a lista est� vazia
        p->proximo = p;
        *lista = p;
    } else { // A lista n�o est� vazia
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
    if (*lista == NULL) { // Se a lista est� vazia
        p->proximo = p;
        *lista = p;
    } else { // A lista n�o est� vazia
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

    if (*lista == NULL) { // Se a lista est� vazia
        if (posicao != 0) {
            printf("Posicao invalida.\n");
            free(p);
            return;
        }
        p->proximo = p;
        *lista = p;
    } else {
        atual = *lista;

        // Inser��o no in�cio da lista (posi��o 0)
        if (posicao == 0) {
            p->proximo = (*lista)->proximo;
            (*lista)->proximo = p;
            *lista = p; // Atualiza a refer�ncia de *lista para o novo n�
        } else {
            for (i = 0; i < posicao - 1; i++) {
                atual = atual->proximo;
                // Se atual voltar ao in�cio, a posi��o � inv�lida
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
        // Se atual voltar ao in�cio, a posi��o � inv�lida
        if (atual == lista) {
            //printf("Posicao invalida.\n");
            i = lista;  // Define i como a pr�pria lista
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
        while (prev->proximo != *lista) { // Encontrar o pen�ltimo n�
            prev = prev->proximo;
        }
        valor = (*lista)->info;
        prev->proximo = (*lista)->proximo; // O pen�ltimo n� aponta para o primeiro n�
        free(*lista);
        *lista = prev; // Atualiza o ponteiro da lista para o pen�ltimo n�, que agora � o �ltimo
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

    // Remo��o do in�cio da lista (posi��o 0)
    if (posicao == 0) {
        // Encontra o �ltimo n� para atualizar o ponteiro circular
        while (atual->proximo != *lista) {
            atual = atual->proximo;
        }
        PtrLista temp = (*lista)->proximo;
        atual->proximo = temp;
        free(*lista);
        *lista = temp;

    }
    else if (posicao == tamanho) { // Verifica se � o �ltimo elemento
        removeFim(lista);

    }
        else {
        anterior = atual;
        for (i = 0; i < posicao; i++) {
            anterior = atual;
            atual = atual->proximo;
            // Se atual voltar ao in�cio, a posi��o � inv�lida
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
        return; // A lista j� est� vazia
    }

    PtrLista atual = (*lista)->proximo; // Come�a no primeiro n�
    PtrLista proximo;

    while (atual != *lista) { // Percorre at� o �ltimo n�
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    // Finalmente, libera o �ltimo n�
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
        Cabecalho("MENU DE OP��ES");
        printf("[1] Adicionar no in�cio da Lista\n");
        printf("[2] Adicionar no final da Lista\n");
        printf("[3] Adicionar em um ponto expec�fico da Lista\n");
        printf("[4] Listar todos os elementos da lista\n");
        printf("[5] Listar um elemento expec�fico da lista\n");
        printf("[6] Excluir do in�cio da Lista\n");
        printf("[7] Excluir do final da Lista\n");
        printf("[8] Excluir de um ponto Expec�fico da Lista\n");
        printf("[9] Liberar os elementos e mostrar a lista vazia\n");
        printf("[0] Sair\n");
        Rodape(false);
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                Cabecalho("Adicionar no in�cio da Lista");
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
                Cabecalho("Adicionar em um ponto expec�fico da Lista");
                listarTudo(lista);
                Rodape(false);
                posicao = 0;
                printf("\nPosi��o: ");
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
                Cabecalho("Listar um elemento expec�fico da lista");
                listarTudo(lista);
                Rodape(false);
                printf("\nPosi��o: ");
                scanf("%d", &posicao);
                mostrarPosicao(lista, posicao);

                break;
            case 6:
                Cabecalho("Excluir do in�cio da Lista");
                //CHAME AQUI A FUN��O
                printf("Item removido do In�cio!\n");
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
                Cabecalho("Excluir de um ponto Expec�fico da Lista");
                listarTudo(lista);
                Rodape(false);
                posicao = 0;
                printf("\nPosi��o: ");
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

        // Espera por uma entrada do usu�rio antes de limpar a tela e exibir o menu novamente
        printf("\nPressione ENTER para continuar...");
        while (getchar() != '\n');
        getchar(); // Aguarda a entrada do usu�rio
    } while (opcao != 0);

    return 0;
}

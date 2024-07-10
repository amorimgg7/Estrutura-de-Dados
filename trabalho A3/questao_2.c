

/*  Gabriel Gomes Amorim  -   1230121318    */


#include <locale.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define MAX_NAME_LEN 100

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

typedef struct TreeNode {
    int user_code;
    char user_name[MAX_NAME_LEN];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* create_node(int user_code, char* user_name) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->user_code = user_code;
    strcpy(new_node->user_name, user_name);
    new_node->left = new_node->right = NULL;
    return new_node;
}

TreeNode* insert(TreeNode* root, int user_code, char* user_name) {
    if (root == NULL) {
        return create_node(user_code, user_name);
    }
    if (user_code <= root->user_code) {
        root->left = insert(root->left, user_code, user_name);
    } else {
        root->right = insert(root->right, user_code, user_name);
    }
    return root;
}

TreeNode* search(TreeNode* root, int user_code) {
    if (root == NULL || root->user_code == user_code) {
        return root;
    }
    if (user_code < root->user_code) {
        return search(root->left, user_code);
    } else {
        return search(root->right, user_code);
    }
}

TreeNode* find_min(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode* remove_node(TreeNode* root, int user_code) {
    if (root == NULL) {
        Cabecalho("Usuario nao encontrado para remocao");
        Rodape(true);
        return root;
    }
    if (user_code < root->user_code) {
        root->left = remove_node(root->left, user_code);
    } else if (user_code > root->user_code) {
        root->right = remove_node(root->right, user_code);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            Cabecalho("Usuario removido com sucesso");
            Rodape(true);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            Cabecalho("Usuario removido com sucesso");
            Rodape(true);
            return temp;
        }
        TreeNode* temp = find_min(root->right);
        root->user_code = temp->user_code;
        strcpy(root->user_name, temp->user_name);
        root->right = remove_node(root->right, temp->user_code);
        Cabecalho("Usuario removido com sucesso");
        Rodape(true);
    }
    return root;
}


void display(TreeNode* root) {
    if (root != NULL) {
        display(root->left);
        printf("%d - %s\n", root->user_code, root->user_name);
        display(root->right);
    }
}

void display_all(TreeNode* root) {
    Cabecalho("Lista de usuarios cadastrados");
    display(root);
    Rodape(true);
}

void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    TreeNode* root = NULL;
    int choice, user_code;
    char user_name[MAX_NAME_LEN];

    do {
        Cabecalho("Menu");
        printf("1. Inserir um no na arvore\n");
        printf("2. Buscar na arvore\n");
        printf("3. Remover um no da arvore\n");
        printf("4. Exibir a arvore\n");
        printf("5. Sair\n");
        Rodape(false);
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Cabecalho("Insira o codigo do usuario");
                Rodape(false);
                scanf("%d", &user_code);
                Cabecalho("Insira o nome do usuario");
                Rodape(false);
                scanf("%s", user_name);
                root = insert(root, user_code, user_name);
                break;
            case 2:
                Cabecalho("Insira o codigo do usuario para busca");
                Rodape(false);
                scanf("%d", &user_code);
                TreeNode* result = search(root, user_code);
                if (result != NULL) {
                    Cabecalho("Usuario retornado pelo codigo informado");
                    printf(" - %s\n", result->user_name);
                    Rodape(true);
                } else {
                    Cabecalho("Usuario nao encontrado");
                    Rodape(true);
                }
                break;
            case 3:
                Cabecalho("Insira o codigo do usuario para remocao");
                Rodape(false);
                scanf("%d", &user_code);
                root = remove_node(root, user_code);
                break;
            case 4:
                display_all(root);
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 5);

    free_tree(root);
    return 0;
}

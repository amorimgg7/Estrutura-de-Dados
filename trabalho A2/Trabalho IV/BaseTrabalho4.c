#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 100
#define MAX_NOME 20

typedef enum {Reservada, Variavel, Constante, Fim} TipoToken;
char *str_TipoToken[] = {"Reservada", "Variavel", "Constante", "Fim"};
typedef enum {Inteiro, Real, Caractere, String}  TipoIdentificador;
char *str_TipoIdentificador[] = {"Inteiro", "Real", "Caractere", "String"};

void pegaToken(TipoToken *token, TipoIdentificador *id, char *nome, int *linha);

int main(void) {
	TipoToken token;
	TipoIdentificador id;
	char nome[MAX_NOME+1];
	int linha;
	pegaToken(&token, &id, nome, &linha);
	while (token != Fim) {
		printf("Token: %s\nId: %s\nNome: %s\nLinha: %d\n\n",str_TipoToken[token], str_TipoIdentificador[id], nome, linha);
		pegaToken(&token, &id, nome, &linha);
	}
	return 0;
}

void pegaToken(TipoToken *token, TipoIdentificador *id, char *nome, int *linha) {
	static int pos=1;
	switch (pos) {
		case 1:
			*token = Reservada;
			*id = String;
			strcpy(nome, "program");
			*linha = 1;
			break;
		case 2:
			*token = Variavel;
			*id = String;
			strcpy(nome, "calcula");
			*linha = 1;
			break;
		case 3:
			*token = Reservada;
			*id = String;
			strcpy(nome, ";");
			*linha = 1;
			break;
		case 4:
			*token = Reservada;
			*id = String;
			strcpy(nome, "var");
			*linha = 2;
			break;
		case 5:
			*token = Variavel;
			*id = Inteiro;
			strcpy(nome, "i");
			*linha = 3;
			break;
		case 6:
			*token = Reservada;
			*id = String;
			strcpy(nome, ",");
			*linha = 3;
			break;
		case 7:
			*token = Variavel;
			*id = Inteiro;
			strcpy(nome, "n");
			*linha = 3;
			break;
		case 8:
			*token = Reservada;
			*id = String;
			strcpy(nome, ":");
			*linha = 3;
			break;
		case 9:
			*token = Reservada;
			*id = String;
			strcpy(nome, "integer");
			*linha = 3;
			break;
		case 10:
			*token = Reservada;
			*id = String;
			strcpy(nome, ";");
			*linha = 3;
			break;
		case 11:
			*token = Reservada;
			*id = String;
			strcpy(nome, "begin");
			*linha = 4;
			break;
		case 12:
			*token = Variavel;
			*id = Inteiro;
			strcpy(nome, "n");
			*linha = 5;
			break;
		case 13:
			*token = Reservada;
			*id = String;
			strcpy(nome, ":=");
			*linha = 5;
			break;
		case 14:
			*token = Constante;
			*id = Inteiro;
			strcpy(nome, "0");
			*linha = 5;
			break;
		case 15:
			*token = Reservada;
			*id = String;
			strcpy(nome, ";");
			*linha = 5;
			break;
		case 16:
			*token = Reservada;
			*id = String;
			strcpy(nome, "for");
			*linha = 6;
			break;
		case 17:
			*token = Variavel;
			*id = Inteiro;
			strcpy(nome, "i");
			*linha = 6;
			break;
		case 18:
			*token = Reservada;
			*id = String;
			strcpy(nome, ":=");
			*linha = 6;
			break;
		case 19:
			*token = Constante;
			*id = Inteiro;
			strcpy(nome, "1");
			*linha = 6;
			break;
		case 20:
			*token = Reservada;
			*id = String;
			strcpy(nome, "to");
			*linha = 6;
			break;
		case 21:
			*token = Constante;
			*id = Inteiro;
			strcpy(nome, "10");
			*linha = 6;
			break;
		case 22:
			*token = Reservada;
			*id = String;
			strcpy(nome, "do");
			*linha = 6;
			break;
		case 23:
			*token = Variavel;
			*id = Inteiro;
			strcpy(nome, "n");
			*linha = 7;
			break;
		case 24:
			*token = Reservada;
			*id = String;
			strcpy(nome, ":=");
			*linha = 7;
			break;
		case 25:
			*token = Variavel;
			*id = Inteiro;
			strcpy(nome, "n");
			*linha = 7;
			break;
		case 26:
			*token = Reservada;
			*id = String;
			strcpy(nome, "+");
			*linha = 7;
			break;
		case 27:
			*token = Variavel;
			*id = Inteiro;
			strcpy(nome, "i");
			*linha = 7;
			break;
		case 28:
			*token = Reservada;
			*id = String;
			strcpy(nome, "*");
			*linha = 7;
			break;
		case 29:
			*token = Constante;
			*id = Inteiro;
			strcpy(nome, "10");
			*linha = 7;
			break;

		case 30:
			*token = Reservada;
			*id = String;
			strcpy(nome, ";");
			*linha = 7;
			break;
		case 31:
			*token = Reservada;
			*id = String;
			strcpy(nome, "end");
			*linha = 8;
			break;
		case 32:
			*token = Reservada;
			*id = String;
			strcpy(nome, ".");
			*linha = 8;
			break;
		default:
			*token = Fim;
	}
	pos++;
}

#ifndef FUNCOES_H
#define FUCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>


#define ERROR_FILE_MSG "Nao foi possivel abrir o arquivo!\n"
#define INVALID_OPTION "Opcao invalida! Tente novamente!\n"
#define MAT_SIZE 9

enum boolean { FALSO = 0, VERDADEIRO = 1 };

/* Prototipos */
FILE *carregar(char quadro[9][9]);
FILE *carregue_continue_jogo(char quadro[9][9], char *nome_arquivo);
void carregue_novo_jogo(char quadro[9][9], char *nome_arquivo);
FILE *crie_arquivo_binario(char quadro[9][9]);
int e_valido(const char quadro[9][9], int x, int y, int valor);
int determinar_quadrante(int x, int y);
int e_valido_na_coluna(const char quadro[9][9], int coluna, int valor);
int e_valido_no_quadro3x3(const char quadro[9][9], int x, int y, int valor);
int e_valido_na_linha(const char quadro[9][9], int linha, int valor);
int existe_campo_vazio(const char quadro[9][9]);
void imprime(const char quadro[9][9]);
void jogar();
void resolver(FILE *, char quadro[9][9]);
void resolver_um_passo(char quadro[9][9]);
void salvar_jogada_bin(FILE *fb, char quadro[9][9]);


/* Funcoes auxiliares */
int fim_x(int quadr);
int fim_y(int quadr);
int le_opcao();
void gen_random(char *s, const int len);
int ini_x(int quadr);
int ini_y(int quadr);
void menu();
void menu_arquivo();


/* Funcoes adicionais */

int backtracking( char quadro[9][9]);
int backtracking_otimizado(char quadro[9][9]);
int retorna_coluna_vazia(char quadro[9][9], int *linha_vazia, int *coluna_vazia);


#endif // FUNCOES_H

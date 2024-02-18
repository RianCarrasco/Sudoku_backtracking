#include "funcoes.h"

/* -----------------------------------------------------------------------------
 * -----------------------------------------------------------------------------
 * MAIN
 * /////////////////////////////////////////////////////////////////////////////
 */
int main()
{
    int i = 5;
    int escolha = 0;
    printf("GOSTARIA DE VER OS AVISOS ?\n");
    printf("1-SIM\n9-NAO");
    scanf(" %d",&escolha);
    while(escolha == 1)
    {
        system("cls");
        puts("AVISOS IMPORTANTES!!");
        Sleep(3000);
        system("cls");
        puts("OS VALORES DESSE SUDOKU ACEITAM APENAS VALORES DE 1 A 9 TANTO LINHA,COLUNA E VALOR\n");
        Sleep(5000);
        system("cls");
        puts("AO INFORMAR O NOME DO SEU ARQUIVO BINARIO NA OPCAO 'CARREGAR JOGO' -> 'NOVO JOGO' CASO VOCE JA\n"
             "TENHA UM SAVE COM ESSE NOME VOCE IRA SOBRE-ESCREVER O MESMO, ENTAO TOME CUIDADO !!");
        Sleep(8000);
        system("cls");
        puts("ESSE PROGRAMA USA FUNCOES DA BIBLIOTECA 'windows.h', ENTAO ALGUMAS COISAS PODEM NAO FUNCIONAR\nCORRETAMENTE EM OUTRAS PLATAFORMAS");
        Sleep(8000);
        system("cls");
        puts("PARA O PROGRAMA FUNCIONAR DE MANEIRA CORRETA AO SAIR DO PROGRAMA USE A OPCAO '9-FINALIZAR'");
        Sleep(7000);
        system("cls");
        printf("REVER AVISOS ?\n1-SIM\n9-NAO");
        scanf("%d",&escolha);
        if(escolha == 1)
        {
            continue;
        }
        puts("BOM JOGO!!");
        Sleep(2000);

    }
    system("cls");
    printf("CARREGANDO");
    while(i != 0)
    {
     printf(".");
     i--;
     Sleep(500);
    }
    puts("");
    system("cls");
    jogar();

    return 0;
}

/* -----------------------------------------------------------------------------
 * CARREGAR
 * Inicializa o SUDOKU a partir de um novo jogo ou estado de jogo anterior
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

FILE *carregar(char quadro[9][9])
{
    int opcao;
    char nome_arquivo[254];
    menu_arquivo();
    opcao = le_opcao();

    switch (opcao)
    {

    // carregar novo sudoku
    case 1:
        printf("Informe o nome do seu arquivo texto\n");
        printf("Exemplo:\n01.txt\n02.txt\nnomeaquivo.txt\n");
        scanf("%s", nome_arquivo); // Guardando o nome do arquivo TXT
        carregue_novo_jogo(quadro, nome_arquivo);
        break;

    // continuar jogo
    case 2:
        printf("Informe o nome de um arquivo BINARIO existente:\n");
        puts("Exemplo: \narquivo.dat \narq.dat \na.dat\n");
        scanf("%s", nome_arquivo); // Guardando o nome do arquivo ninario, c
        return carregue_continue_jogo(quadro, nome_arquivo);
        break;

    // retornar ao menu anterior
    case 9:
        break;

    default:
        break;
    }
}

void carregue_novo_jogo(char quadro[9][9], char *nome_arquivo)
{
    FILE *novo;
    int i, j;
    novo = fopen(nome_arquivo, "r"); // Abrindo o arquivo TXT fornecido pelo usuario
    if (novo == NULL)
    {
        puts(ERROR_FILE_MSG);
        jogar();
    }
    for (i = 0; i <= 8; i++)
    {
        for (j = 0; j <= 8; j++)
        {
            fscanf(novo, "%d",&quadro[i][j]); // Guardando as informações do arquivo TXT na matriz
        }
    }
    fclose(novo); // fechando o arquivo texto pois ele não será mai util
}

FILE *carregue_continue_jogo(char quadro[9][9], char *nome_arquivo)
{

    FILE *arq_bin =
        fopen(nome_arquivo,"r+b"); // Crindo/ abrindo um arquivo binario para leitura e escrita

    if (!arq_bin)
    {
        puts(ERROR_FILE_MSG);
        jogar();
    }
    fseek(arq_bin, sizeof(int) * 3,SEEK_SET); // Deslocando o ponteito 4 byts pra frente
    fread(quadro, sizeof(char), 9 * 9,arq_bin); // Depois de deslocado, é armazenado retirado um SAVE já
    // pronto fornecido pelo usuario
    // fclose(le);
    return arq_bin;
}
/* -----------------------------------------------------------------------------
 * CRIAR ARQUIVO BINARIO
 * Criar arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE *crie_arquivo_binario(char quadro[9][9])
{
    char nome_arq[255];
    int jogadas = 0;
    puts("Informe o nome do seu aquivo binario\n");
    puts("Exemplo: \narquivo.dat \narq.dat \na.dat\n");
    scanf(" %s", nome_arq);

    FILE *abre_bin = fopen(nome_arq, "w+b");

    if (abre_bin == NULL) //! abre_bin
    {
        printf(ERROR_FILE_MSG);
        jogar();
    }
    fseek(abre_bin, 0, SEEK_SET);
    fwrite(&jogadas, sizeof(int), 1,abre_bin); // escreve a quantidade de jogadas já feita, como o arquivo
    // acabou de ser criado a quantidade de jogadas é 0
    return abre_bin;
}

/* -----------------------------------------------------------------------------
 * DETERMINAR QUADRANTE
 * Dado as posicoes x e y, determina o quadrante do quadro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int determinar_quadrante(int x, int y)
{
    if (x < 3 && y < 3)
        return 1;
    else if (x < 3 && y < 6)
        return 2;
    else if (x < 3 && y <= 8)
        return 3;
    else if (x < 6 && y < 3)
        return 4;
    else if (x < 6 && y < 6)
        return 5;
    else if (x < 6 && y <= 8)
        return 6;
    else if (x <= 8 && y < 3)
        return 7;
    else if (x <= 8 && y < 6)
        return 8;
    else
        return 9;
}

/* -----------------------------------------------------------------------------
 * E VALIDO
 * Determina se um valor na posicao x e y e valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
/* -----------------------------------------------------------------------------
 * E VALIDO
 * Determina se um valor na posicao x e y e valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int e_valido(const char quadro[9][9], int x, int y, int valor)
{

    if (!e_valido_na_coluna(quadro, y, valor))
        return FALSO;
    if (!e_valido_na_linha(quadro, x, valor))
        return FALSO;
    if (!e_valido_no_quadro3x3(quadro, x, y, valor))
        return FALSO;

    return VERDADEIRO;
}

/* -----------------------------------------------------------------------------
 * E VALIDO NA COLUNA
 * Verifica se um valor na coluna y e valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int e_valido_na_coluna(const char quadro[9][9], int coluna, int valor)
{
    int i;
    for (i = 0; i <= 8; i++)
        if (quadro[i][coluna] ==
                valor) // A verificação é travada em uma coluna e percorrida na mesma
            return FALSO;  // Retorna falso pois foi encontrado um valor já existente
    // na coluna
    return VERDADEIRO; // Retorna verdadeiro pois o valor não existe nessa coluna
}

/* -----------------------------------------------------------------------------
 * E VALIDO NA LINHA
 * Verifica se um valor na linha x e valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int e_valido_na_linha(const char quadro[9][9], int linha, int valor)
{
    int i;
    for (i = 0; i <= 8; i++)
        if (quadro[linha][i] ==
                valor) // A verificação é travada em uma linha e percorrida na mesma
            return FALSO;  // Retorna falso pois foi encontrado um valor já existente
    // na coluna
    return VERDADEIRO; // Retorna verdadeiro pois o valor não existe nessa coluna
}

/* -----------------------------------------------------------------------------
 * E VALIDO NO QUADRO 3X3
 * Verifica se um valor e valido no quadrante da posicao x, y
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int e_valido_no_quadro3x3(const char quadro[9][9], int x, int y, int valor)
{
    int quadrante = determinar_quadrante(x, y);
    int i, j;
    for (i = ini_x(quadrante); i <= fim_x(quadrante); i++)
    {
        for (j = ini_y(quadrante); j <= fim_y(quadrante); j++)
        {
            if (quadro[i][j] == valor)
            {
                return FALSO;
            }
        }
    }
    return VERDADEIRO;
}

/* -----------------------------------------------------------------------------
 * EXISTE CAMPO VAZIO
 * Verifica se existe um campo não preenchido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int existe_campo_vazio(const char quadro[9][9])
{
    int i, j;

    for (i = 0; i <= 8; i++)
    {
        for (j = 0; j <= 8; j++)
        {
            if (quadro[i][j] == 0)
                return VERDADEIRO;
        }
    }
    return FALSO;
}

/* -----------------------------------------------------------------------------
 * IMPRIMIR
 * Imprime o quadro inteiro do sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void imprime(const char quadro[9][9])
{
    int i, j;

    //	puts("~~~~~~~~ SUDOKU ~~~~~~~~");
    puts("    1 2 3   4 5 6   7 8 9");
    for (i = 0; i <= 8; i++)
    {
        if (i % 3 == 0)
            puts("  -------------------------");
        for (j = 0; j <= 8; j++)
        {

            if (j == 0)
                printf("%d | ", i + 1);
            else if (j % 3 == 0)
                printf("| ");

            if (quadro[i][j] == 0)
                printf("- ");
            else
                printf("%d ", quadro[i][j]);
        }
        puts("|");
    }
    puts("  -------------------------");
}

/* -----------------------------------------------------------------------------
 * JOGAR
 * Realiza toda a logica do jogo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void jogar()
{
    int opcao, linha_vazia = 0, coluna_vazia = 0;
    int linha_int, coluna_int, valor_int, escolha = -1;
    int jogadas;
    char quadro[9][9] = {0} /* {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0,
                      0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0,
                      0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0,
                      0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0,
                      0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}}*/
                        ;
    char quadro_aux[9][9];

    FILE *fb = NULL;

    opcao = 0;

    while (opcao != 9)
    {
        // imprime na tela o quadro atual
        imprime(quadro);

        // apresenta um menu com as opcoes
        menu();
        opcao = le_opcao();

        switch (opcao)
        {

        // carregar sudoku
        case 1:
            fb = carregar(quadro);

            if (fb == NULL)
            {
                fb = crie_arquivo_binario(quadro);
            }
            break;

        // preencher quadro com um valor
        case 2:
            do
            {
                printf("Entre com a posicao e o valor (linha, coluna, valor): ");
                fflush(stdin);
                scanf(" %d %d %d", &linha_int, &coluna_int, &valor_int);

                if (linha_int >= 1 && linha_int <= 9 && coluna_int >= 1 &&
                        coluna_int <= 9 && valor_int >= 1 && valor_int <= 9 &&
                        e_valido(quadro, linha_int - 1, coluna_int - 1, valor_int))
                {
                    memcpy(quadro_aux, quadro, sizeof(char) * 9 * 9);
                    quadro_aux[linha_int - 1][coluna_int - 1] = valor_int;
                    if (backtracking_otimizado(quadro_aux))
                    {
                        puts("SUA JOGADA FOI EXCELENTE!!\n");
                        quadro[linha_int - 1][coluna_int - 1] = valor_int;
                        salvar_jogada_bin(fb, quadro);
                        break;
                    }
                    else
                    {
                        puts("SUA JOGADA FOI VALIDA MAS INFELIZMENTE NAO VAI PODER SER SALVA POIS NAO FOI UMA BOA JOGADA :(\n");
                        puts("QUER TENTAR FAZER MELHOR ? \n1-SIM\n9-NAO");
                        scanf("%*c%d", &escolha);
                    }

                }
                else
                {
                    puts("Opcao invalida, deseja tentar novamente ?\n");
                    printf("1-Tentar novamente\n9-SAIR\n");
                    scanf("%*c%d", &escolha);
                }
            }
            while (escolha != 9);
            break;

        // resolver 1 passo
        case 3:
            resolver_um_passo(quadro);
            salvar_jogada_bin(fb, quadro);
            puts("Um passo resolvido!");
            break;

        // resolver o sudoku
        case 4:
             resolver(fb, quadro);
            // backtracking(quadro);
            //backtracking_otimizado(quadro);
            fseek(fb, 0, SEEK_SET);
            fread(&jogadas, sizeof(int), 1, fb);
            printf("Quatidade de jogadas: %d\n", jogadas);
            break;

        case 9:
            puts("Programa finalizado ..");
            salvar_jogada_bin(fb, quadro);
            fclose(fb);
            break;

        default:
            puts(INVALID_OPTION);
            break;
        }
    }
}
/* -----------------------------------------------------------------------------
 * RESOLVER
 * Resolve o sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void resolver(FILE *fb, char quadro[9][9])
{

    // enquanto houver posicoes vazias no quadro
    while (existe_campo_vazio(quadro))
    {
        resolver_um_passo(quadro);
        salvar_jogada_bin(fb, quadro);
    }
}

/* -----------------------------------------------------------------------------
 * RESOLVER UM PASSO
 * Preenche apenas um campo vazio
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int retorna_coluna_vazia(char quadro[9][9], int *linha, int *coluna)
{
    for (*linha = 0; *linha < 9; (*linha)++)
    {
        for (*coluna = 0; *coluna < 9; (*coluna)++)
        {
            if (quadro[*linha][*coluna] == 0)
            {
                return VERDADEIRO; // Encontrou posição vazia
            }
        }
    }
    return FALSO; // Não há mais posições vazias
}

int backtracking_otimizado(char quadro[9][9])
{
    int linha, coluna;

    if (retorna_coluna_vazia(quadro, &linha, &coluna) == FALSO)
    {
        // Não há mais posições vazias, Sudoku resolvido
        return VERDADEIRO;
    }

    for (int numero = 1; numero <= 9; numero++)
    {
        if (e_valido(quadro, linha, coluna, numero))
        {
            quadro[linha][coluna] = numero;

            if (backtracking_otimizado(quadro) == VERDADEIRO)
            {
                return VERDADEIRO; // Sudoku resolvido
            }

            quadro[linha][coluna] =0; // Desfaz a atribuição e tenta com o próximo número
        }
    }

    return FALSO; // Não há solução para a configuração atual
}

int backtracking(char quadro[9][9])
{
    int linha, coluna, semaforo = -1, i;
    // Encontrar a próxima célula vazia
    for (linha = 0; linha <= 8; linha++)
    {
        for (coluna = 0; coluna <= 8; coluna++)
        {
            if (quadro[linha][coluna] == 0)
            {
                semaforo = 0;
                break;
            }
        }
        if (semaforo !=
                -1) // para o primeiro for pois já foi encintrado uma célula vazia
        {
            break;
        }
    }

    // Se não há mais células vazias, o Sudoku está resolvido
    if (semaforo == -1)
    {
        return VERDADEIRO;
    }

    for (int i = 1; i <= 9; i++)
    {
        if (e_valido(quadro, linha, coluna, i))
        {
            quadro[linha][coluna] = i;
            if (backtracking(quadro))
            {
                return VERDADEIRO;
            }
            quadro[linha][coluna] = 0;
        }
    }
    return FALSO;
}
void resolver_um_passo(char quadro[9][9])
{

    srand(time(NULL));
    int linha_aleatoria = rand() % 9;
    int coluna_aleatoria = rand() % 9;
    int contador = 0, i, j, voltas = 0;
    char aux[9][9];
    memcpy(aux, quadro, sizeof(char) * 9 * 9);

    while (quadro[linha_aleatoria][coluna_aleatoria] != 0 && i != -1)
    {
        if (linha_aleatoria == 8 && coluna_aleatoria == 8)
        {
            linha_aleatoria = 0;
            coluna_aleatoria = 0;
        }
        else if (coluna_aleatoria == 8)
        {
            linha_aleatoria++;
            contador++;
            coluna_aleatoria = 0;
        }
        else
        {
            coluna_aleatoria++;
        }
        if (contador == 9)
        {
            // puts("Nao a mais passos a resolver!!\n");
            i = -1;
        }
    }
    contador = 0;
    for (i = 1; i <= 9; i++)
    {
        if (e_valido(aux, linha_aleatoria, coluna_aleatoria, i))
        {
            aux[linha_aleatoria][coluna_aleatoria] = i;
            if (backtracking(aux) == VERDADEIRO)
            {
                quadro[linha_aleatoria][coluna_aleatoria] = i;
                memcpy(aux, quadro, sizeof(char) * 9 * 9);
                //printf("De primeira\n");
                contador = 1;
                break;
            }
        }
    }
    if (contador == 0)
    {
        retorna_coluna_vazia(quadro, &linha_aleatoria, &coluna_aleatoria);
        for (i = 1; i <= 9; i++)
        {
            // printf("[%d]-[%d]\n",linha_aleatoria,coluna_aleatoria);
            if (e_valido(aux, linha_aleatoria, coluna_aleatoria, i))
            {
                aux[linha_aleatoria][coluna_aleatoria] = i;
                if (backtracking(aux) == VERDADEIRO)
                {
                    quadro[linha_aleatoria][coluna_aleatoria] = i;
                    memcpy(aux, quadro, sizeof(char) * 9 * 9);
                    //printf("De segunda\n");
                    break;
                }
            }
        }
    }
}

/* -----------------------------------------------------------------------------
 * SALVAR JOGADA BINARIO
 * Salva o estado atual do quadro no arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void salvar_jogada_bin(FILE *fb, char quadro[9][9])
{
    int jogadas;
    if (fb != NULL)
    {
        fseek(fb, sizeof(int) * 3, SEEK_SET);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                fprintf(fb, "%c", quadro[i][j]);
            }
        }
        fseek(fb, 0, SEEK_SET);
        fread(&jogadas, sizeof(int), 1, fb);
        jogadas++;
        //printf("Quatidade de jogadas: %d\n", jogadas);
        fseek(fb, 0, SEEK_SET);
        fwrite(&jogadas, sizeof(int), 1, fb);
        // fclose(fb);

    }
    else
    {
        printf(ERROR_FILE_MSG);
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 							FUNCOES AUXILIARES
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/* -----------------------------------------------------------------------------
 * FIM X
 * Indice final da linha para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int fim_x(int quadr)
{
    switch (quadr)
    {
    case 1:
    case 2:
    case 3:
        return 2;

    case 4:
    case 5:
    case 6:
        return 5;

    default:
        return 8;
    }
}

/* -----------------------------------------------------------------------------
 * FIM Y
 * Indice final da coluna para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int fim_y(int quadr)
{
    switch (quadr)
    {
    case 1:
    case 4:
    case 7:
        return 2;

    case 2:
    case 5:
    case 8:
        return 5;

    default:
        return 8;
    }
}

/* -----------------------------------------------------------------------------
 * GEN_RANDOM
 * Gera uma cadeira de caracteres randomica de tamanho len
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void gen_random(char *s, const int len)
{
    srand(time(NULL));
    static const char alphanum[] = "0123456789"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";
    int i;

    for (i = 0; i < len; ++i)
    {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

/* -----------------------------------------------------------------------------
 * INI X
 * Indice inicial da linha para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int ini_x(int quadr)
{
    switch (quadr)
    {
    case 1:
    case 2:
    case 3:
        return 0;

    case 4:
    case 5:
    case 6:
        return 3;

    default:
        return 6;
    }
}

/* -----------------------------------------------------------------------------
 * INI Y
 * Indice inicial da coluna para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int ini_y(int quadr)
{
    switch (quadr)
    {
    case 1:
    case 4:
    case 7:
        return 0;

    case 2:
    case 5:
    case 8:
        return 3;

    default:
        return 6; // modificado
    }
}

/*Abre o aquivo p/ leitura  */

/* -----------------------------------------------------------------------------
 * LE OPCAO
 * Imprime a mensagem a faz a leitura da opcao
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int le_opcao()
{
    int opcao;

    printf("Opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

/* -----------------------------------------------------------------------------
 * MENU
 * Imprime o menu de opcoes
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu()
{
    puts("\n~~~~~~~~ SUDOKU ~~~~~~~~");
    puts("[1] - Carregar jogo");
    puts("[2] - Jogar");
    puts("[3] - Resolver um passo");
    puts("[4] - Resolver");
    puts("[9] - Finalizar");
    puts("--------");
}

/* -----------------------------------------------------------------------------
 * MENU ARQUIVO
 * Imprime o menu de opcoes do arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu_arquivo()
{
    puts("\n~~~~~ MENU ARQUIVO ~~~~~");
    puts("[1] - Novo jogo");
    puts("[2] - Continuar jogo");
    puts("[9] - Retornar ao menu anterior");
    puts("--------");
}

#include "imm.h"
#include <string.h>
#include <stdio.h>
#include "matriz.h"
#include "stack.h"
#include <stdbool.h>

struct Img
{
    TMat2D *data;
};

Img *img_create(int linha, int coluna)
{
    if (linha < 0 || coluna < 0)
        return NULL;
    Img *img;
    img = (Img *)malloc(sizeof(Img));
    if (img == NULL)
        return NULL;
    img->data = mat2D_create(linha, coluna);
    return img;
}

int openImage(char *file) // chamada genérica para abrir qualquer imagem
{

    if (verificatxtimm(file) == TXT) // chama função verifica para fazer a chamada da imagem especifica
    {
        if (openImagetxt(file) == SUCCESS)
        {
            return SUCCESS;
        }
    }
    else if (verificatxtimm(file) == IMM)
    {
        if (openImageimm(file) == SUCCESS)
        {
            return SUCCESS;
        }
    }
    else
        return INVALID_FILE;
}

Img *lerImage(char *file) // chamada genérica para ler qualquer imagem;
{
    Img *img;
    if (verificatxtimm(file) == TXT) // chama função verifica para fazer a chamada da imagem especifica
    {
        img = lerImageTXT(file);
    }
    else
    {
        img = lerImageIMM(file);
    }
}

Img *lerImageTXT(char *arquivotxt)
{
    FILE *arq;
    arq = fopen(arquivotxt, "r"); // abre aqrquivo para leitura;
    if (arq == NULL)
    {
        return NULL;
    }
    return lerImagetxt(arq);
    fclose(arq);
}

Img *lerImagetxt(FILE *arq) // lê uma imagem txt
{
    int i = 0, linha, coluna;
    int dados;
    int retorno[2];                 //retorno da função que obtém linha e coluna do arquivo;
    get_linha_coluna(arq, retorno); // obtém linha e coluna do arquivo;
    linha = retorno[0];
    coluna = retorno[1];
    Img *img = img_create(linha, coluna); //cria uma img para armazenar os dados;

    rewind(arq); // para ter certeza que está no começo do arquivo;
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            fscanf(arq, "%d", &dados);                                   // lê os dados do arquivo armazanendo-os em dados;
            if (mat2D_set_value(img->data, i, j, (int)dados) != SUCCESS) // seta os valores na img->matriz criada;
            {
                return NULL;
            }
        }
    }
    return img;
}

Img *lerImageIMM(char *arquivoimm)
{
    FILE *arq;
    arq = fopen(arquivoimm, "rb"); // abre arquivo binário para leitura
    if (arq == NULL)
    {
        return NULL;
    }
    return lerImageimm(arq);
    fclose(arq);
}

Img *lerImageimm(FILE *arq) // lê imagem imm/binária;
{
    int i = 0, linha, coluna;
    int dados;

    fread(&linha, sizeof(int), 1, arq);   // lê primeiro argumento que no caso é a qtd de linha da matriz a ser criada;
    fread(&coluna, sizeof(int), 1, arq);  // lê segundo argumento que no caso é a qtd de coluna da matriz a ser criada;
    Img *img = img_create(linha, coluna); // cria e aloca a imagem com essas dimensões;

    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            fread(&dados, sizeof(int), 1, arq);                     //lê os dados do arquivo armazanendo-os em dados;
            if (mat2D_set_value(img->data, i, j, dados) != SUCCESS) // seta os valores na img->matriz criada;
            {
                return NULL;
            }
        }
    }
    return img;
}

int liberaImage(Img *arquivo) //libera a imagem
{
    if (arquivo == NULL)
    {
        return INVALID_FILE;
    }
    free(arquivo->data);
    free(arquivo);
    return SUCCESS;
}

int openImagetxt(char *arquivotxt) // abre imagem txt
{
    Img *img = lerImageTXT(arquivotxt); //lê a imagem;
    exibirMatriz(img->data);            //exibi a imagem em forma de matriz;
    liberaImage(img);                   // libera a imagem;
    return SUCCESS;
}

int openImageimm(char *arquivoimm) //abre imagem imm
{
    Img *img = lerImageIMM(arquivoimm); //lê a imagem;
    exibirMatriz(img->data);            //exibi a imagem em forma de matriz;
    liberaImage(img);                   // libera a imagem;
    return SUCCESS;
}

int convertTXTIMM(char *arquivotxt, char *arquivoimm)
{
    Img *img = lerImageTXT(arquivotxt); //lê a imagem txt;
    FILE *arq;
    arq = fopen(arquivoimm, "wb"); // cria/abre arquivo binário para escrita
    if (arq == NULL)
        return INVALID_FILE;
    if (convertTxtImm(img, arq) == SUCCESS)
        return SUCCESS;
    fclose(arq);
    liberaImage(img);
}

int convertTxtImm(Img *img, FILE *arq) // convert imagem txt em imm
{
    int lin, col;
    int dados;
    if (mat2D_get_lincol(img->data, &lin, &col) != SUCCESS) // obtém qtd de linhas e colunas da img txt
        return INVALID_FILE;
    fwrite(&lin, sizeof(int), 1, arq); //escreve a qtd de linhas lidas na imagem txt
    fwrite(&col, sizeof(int), 1, arq); //escreve a qtd de colunas lidas na imagem txt
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (mat2D_get_value(img->data, i, j, &dados) == SUCCESS) // lê dados da img->matriz txt e armazena-os em dados;
                fwrite(&dados, sizeof(int), 1, arq);                 // escreve dados no arquivo binário aberto/criado;
        }
    }
    return SUCCESS;
}

int segmentIMAGE(int thr, char *arq_entrada, char *arq_saida)
{
    int lin, col;
    Img *img = lerImage(arq_entrada);                       // lê a imagem entrada
    if (mat2D_get_lincol(img->data, &lin, &col) != SUCCESS) // obtém qtd de linhas e colunas da img entrada
        return INVALID_FILE;
    Img *img_saida = img_create(lin, col); //cria e aloca uma img saída com qtd de linhas e colunas da img entrada
    if (segmentImage(thr, img, img_saida) == SUCCESS)
    {
        if (imagemParaArquivo(img_saida, arq_saida) == SUCCESS) // chama função que transforma a img saida em um arquivo;
            return SUCCESS;
    }
    else
        return INVALID_FILE;
    liberaImage(img);
    liberaImage(img_saida);
}

int segmentImage(int thr, Img *img, Img *img_saida) // segmenta qualquer imagem
{
    int lin, col;
    int dados;
    if (mat2D_get_lincol(img->data, &lin, &col) != SUCCESS) // obtém qtd de linhas e colunas da img entrada
        return INVALID_FILE;
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (mat2D_get_value(img->data, i, j, &dados) == SUCCESS)
                ;                                                 // obtém valores da img->matriz entrada e amarzena-os em dados
            mat2D_set_value(img_saida->data, i, j, dados >= thr); // seta 1/0(T/F) de dados>=thr na matriz img->matriz saida
        }
    }
    return SUCCESS;
}

int compCONEXO(char *arquivo_entrada, char *arquivo_saida)
{
    int lin, col;
    Img *im = lerImage(arquivo_entrada);                   // lê imagem enrtada
    if (mat2D_get_lincol(im->data, &lin, &col) != SUCCESS) // obtém qtd de linhas e colunas da img entrada
        return INVALID_FILE;
    Img *im_rot = img_create(lin, col); // cria e aloca uma img->matriz para img saída com qtd de linhas e colunas da img entrada com todos os valores em 0;
    if (compConexo(im, im_rot) == SUCCESS)
    {
        if (imagemParaArquivo(im_rot, arquivo_saida) == SUCCESS) // chama função que transforma a img saida em um arquivo;
        {
            return SUCCESS;
        }
        else
            return INVALID_FILE;
    }
    liberaImage(im);
    liberaImage(im_rot);
}

int compConexo(Img *im, Img *im_rot) //conexo da img entrada;
{
    int lin, col;
    int dadosim;
    int dadosrot;
    int label = 1;                                         //label para diferenciar objetos;
    Stack *stack = create_stack();                         // cria e aloca uma pilha
    struct Ponto p, p_atual, a;                            // cria pontos
    if (mat2D_get_lincol(im->data, &lin, &col) != SUCCESS) // obtém qtd de linhas e colunas da img entrada
        return INVALID_FILE;

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        { // percorre toda a imagem em busca de um pixel foreground (valor 1)
            p.x = i;
            p.y = j;
            mat2D_get_value(im->data, p.x, p.y, &dadosim);      // obtém valores da img->matriz entrada e amarzena-os em dadosim
            mat2D_get_value(im_rot->data, p.x, p.y, &dadosrot); // obtém valores da img->matriz saida e amarzena-os em dadosrot
            if ((dadosim == 1) && (dadosrot == 0))              // compará os dois
            {
                mat2D_set_value(im_rot->data, p.x, p.y, label); // atribui o label a posição (i,j) da img->matriz saida
                stack_push(stack, p);                           // inclui na lista de busca dos vizinhos
                while (stack_size(stack) != 0)                  //enquanto a lista nao for fazia
                {                                               // busca o próximo ponto da lista
                    stack_find(stack, &p_atual);                //pega elemento da pillha
                    stack_pop(stack);                           //desempilha
                    for (int d = 0; d < 4; d++)                 // for para andar por 4 vizinhos do ponto atual
                    {
                        a.x = p.x;
                        a.y = p.y;
                        p.x = p_atual.x - (d == 0) + (d == 1);              //d == 0 irá verificar vizinho de baixo      / d == 1 irá verificar vizinho de cima
                        p.y = p_atual.y - (d == 2) + (d == 3);              //  d == 2 irá verificar vizinho da esquerda / d == 3 irá verificar vizinho da direita
                        mat2D_get_value(im->data, p.x, p.y, &dadosim);      // obtém valores da img->matriz entrada e amarzena-os em dadosim
                        mat2D_get_value(im_rot->data, p.x, p.y, &dadosrot); //obtém valores da img->matriz saida e amarzena-os em dadosrot
                        if ((dadosim == 1) && (dadosrot == 0))              // verifica se os pontos não são 1 e não foi rotulado
                        {
                            mat2D_set_value(im_rot->data, p.x, p.y, label); // atribui o label a posição (i,j) da img->matriz saida
                            stack_push(stack, p);                           // empilha para verificar vizinhos posteriormente
                        }
                        p.x = a.x;
                        p.y = a.y;
                    } //for
                }     // while
                label++;
            }          // if
        }              //for
    }                  // for
    stack_free(stack); //libera a pilha
    return SUCCESS;
}

int LABIRINTO(char *arquivo_entrada, char *arquivo_saida) // resolve um labirinto
{
    int lin, col;
    Img *mapa1 = lerImage(arquivo_entrada);                   // lê img entrada;
    if (mat2D_get_lincol(mapa1->data, &lin, &col) != SUCCESS) // obtém qtd de linhas e colunas da img entrada
        return INVALID_FILE;
    Img *mapa2 = img_create(lin, col);
    if (labirinto(mapa1, mapa2) == SUCCESS)
    {
        if (imagemParaArquivo(mapa1, arquivo_saida) == SUCCESS) // transforma img->matriz entrada em um arquivo saida
            return SUCCESS;
    }
    else if (labirinto(mapa1, mapa2) == MAP_SEM_SAIDA)
        return MAP_SEM_SAIDA;
    liberaImage(mapa1);
    liberaImage(mapa2);
}

int labirinto(Img *mapa1, Img *mapa2) // resolve um labirinto
{
    int lin, col;
    int valmap;
    int valmap2;
    bool mapa_sem_saida;
    Stack *stack = create_stack();      //cria e aloca uma pilha
    struct Ponto p, p_atual, a, inicio; // cria pontos
    inicio.x = -1;
    if (mat2D_get_lincol(mapa1->data, &lin, &col) != SUCCESS) // obtém qtd de linhas e colunas da img entrada
        return INVALID_FILE;

    for (int i = 0; i < lin; i++)
    {
        mat2D_get_value(mapa1->data, i, 0, &valmap);
        if (valmap == 1) // se esse valor for 1 será o ponto de inicio.
        {
            inicio.x = i;
            inicio.y = 0;
            break;
        } //if
        mat2D_get_value(mapa1->data, i, col - 1, &valmap);
        if (valmap == 1) // se esse valor for 1 será o ponto de inicio.
        {
            inicio.x = i;
            inicio.y = col - 1;
            break;
        } //if
    }     //for
    if(inicio.x == -1){
        for (int j = 0; j < col; j++)
        {
            mat2D_get_value(mapa1->data, 0, j, &valmap);
            if (valmap == 1) // se esse valor for 1 será o ponto de inicio.
            {
                inicio.x = 0;
                inicio.y = j;
                break;
            } //if
            mat2D_get_value(mapa1->data, lin - 1, j, &valmap);
            if (valmap == 1) // se esse valor for 1 será o ponto de inicio.
            {
                inicio.x = lin - 1;
                inicio.y = j;
                break;
            } //if
        }     //for
    }         //if

    p_atual = inicio;

    while (true)
    {
        mat2D_get_value(mapa1->data, p_atual.x, p_atual.y, &valmap); // obtém valores da img->matriz entrada e amarzena-os em dadosim
        if (
            (p_atual.x != inicio.x || p_atual.y != inicio.y) &&
            valmap == 1 &&
            (p_atual.x == 0 || p_atual.y == 0 || p_atual.x == lin - 1 || p_atual.y == col - 1)) // verifica condição de vitória,se o ponto atual for diferente
                                                                                                // de inicio, ser 1 e estar na borda.
        {
            stack_push(stack, p_atual); // adiciona o ultimo ponto na pilha
            break;
        }

        for (int d = 0; d < 4; d++) // for para andar por 4 vizinhos do ponto atual
        {
            p.x = p_atual.x - (d == 0) + (d == 1); //d == 0 irá verificar vizinho de baixo      / d == 1 irá verificar vizinho de cima
            p.y = p_atual.y - (d == 2) + (d == 3); //  d == 2 irá verificar vizinho da esquerda / d == 3 irá verificar vizinho da direita

            if (p.x < 0 || p.x >= lin || p.y < 0 || p.y >= col) // verifica se é um ponto válido se está nos limite da matriz
                continue;
            mat2D_get_value(mapa1->data, p.x, p.y, &valmap);  // obtém valores da img->matriz entrada e amarzena-os em valmap
            mat2D_get_value(mapa2->data, p.x, p.y, &valmap2); // obtém valores da img->matriz entrada e amarzena-os em valmap2
            if ((valmap == 1) && (valmap2 == 0))              // verifica se não passou por esse caminho comparando os mapas
            {
                mat2D_set_value(mapa2->data, p_atual.x, p_atual.y, 1); // atribui 1 a posição atual da img->matriz saida
                stack_push(stack, p_atual);                            // empilha esse ponto;
                p_atual = p;                                           // pega o próximo;
                break;
            }           //if
            if (d == 3) // retornar marcando o caminho
            {
                mat2D_set_value(mapa2->data, p_atual.x, p_atual.y, 3); // atribui 3 a posição atual da img->matriz saida
                if (stack_size(stack) == 0)                            //se a lista tiver vaiza mapa sem saída
                {
                    mapa_sem_saida = true;
                    break;
                }                            //if
                stack_find(stack, &p_atual); // pega o ponto anterior
                stack_pop(stack);            // desempilha ele
            }                                //if
        }                                    //for
        if (mapa_sem_saida)                  // se for sem saída sair do while;
            break;
    } //while

    while (stack_size(stack) != 0) // enquanto a pilha nao tiver vazia desempilha tudo
    {
        stack_find(stack, &p_atual); // desempilha os pontos
        stack_pop(stack);
        mat2D_set_value(mapa1->data, p_atual.x, p_atual.y, 2); // seta 2 nas posições dos pontos desempilhados na img->matriz entrada
    }                                                          //while
    stack_free(stack);                                         //libera pilha
    return SUCCESS;
    if (mapa_sem_saida) // retorna erro para mapa sem saida
        return MAP_SEM_SAIDA;
    else
        return INVALID_FILE;
}

int imagemParaArquivo(Img *img, char *arquivo) // transforma a img em um arquivo
{

    int lin, col;

    char tipoAbertura[3] = {'w', '\0', '\0'}; // tipo de abertura de escrita padrão para txt
    if (verificatxtimm(arquivo) == IMM)       // verifica arquivo se for imm altera modo de abertura do arquivo para escrita em binário
    {
        tipoAbertura[1] = 'b';
    }

    FILE *arq;
    arq = fopen(arquivo, tipoAbertura); // abre arquivo para escrita
    if (arq == NULL)
    {
        return INVALID_FILE;
    }

    if (mat2D_get_lincol(img->data, &lin, &col) != SUCCESS) // obtém qtd de linhas e colunas da img->matriz
    {
        return INVALID_FILE;
    }

    int dados;
    if (verificatxtimm(arquivo) == TXT) //se arquivo for txt
    {                                   //TXT
        for (int i = 0; i < lin; i++)
        {
            for (int j = 0; j < col; j++)
            {
                mat2D_get_value(img->data, i, j, &dados); // obtém valores da img->matriz e amarzena-os em dados
                if (j == col - 1)                         // verifica se é o último elemento
                {
                    fprintf(arq, "%d\0", dados); // escreve dados no arquivo
                }
                else
                {
                    fprintf(arq, "%d\t", dados); // escreve dados no arquivo
                }
            }
            if (i != lin - 1) // quebra de linha
                fprintf(arq, "\n");
        }
    }
    else                                   // se for IMM
    {                                      //IMM
        fwrite(&lin, sizeof(int), 1, arq); // escreve qtd de linhas da img->matriz
        fwrite(&col, sizeof(int), 1, arq); // escreve qtd de colunas da img->matriz
        for (int i = 0; i < lin; i++)
        {
            for (int j = 0; j < col; j++)
            {
                mat2D_get_value(img->data, i, j, &dados); // obtém valores da img->matriz e amarzena-os em dados
                fwrite(&dados, sizeof(int), 1, arq);      // escreve dados no arquivo
            }
        }
    }
    return SUCCESS;
}

int verificatxtimm(char *arquivo) // verifica arquivo é txt ou imm
{
    char txt[5] = ".txt";
    char imm[5] = ".imm";
    int tam = strlen(arquivo);
    for (int i = 0; i < tam; i++)
    {
        if (txt[0] == arquivo[i] && txt[1] == arquivo[i + 1] && txt[2] == arquivo[i + 2] && txt[3] == arquivo[i + 3]) // verifica os 4 últimos elementos da string do arquivo
        {                                                                                                             //com a string ".txt"
            return TXT;
        }
        if (imm[0] == arquivo[i] && imm[1] == arquivo[i + 1] && imm[2] == arquivo[i + 2] && imm[3] == arquivo[i + 3]) // verifica os 4 últimos elementos da string do arquivo
        {                                                                                                             // com a string ".imm"
            return IMM;
        }
    }
    return INVALID_FILE;
}

void get_linha_coluna(FILE *arq, int *retorno) // obtém qtd de linhas e colunas do arquivo
{
    char c;
    int linha = 1, coluna = 1;
    while ((c = fgetc(arq)) != EOF) // le cada caracter até fim do arquivo
    {
        if (linha == 1 && (c == '\t' || c == ' ')) //acrescenta coluna lendo a primeira linha a cada tabulação
        {
            coluna++;
        }
        else if (c == '\n') // acrescebta linha a cada quebra de linha encontrada;
        {
            linha++;
        }
        else
        {
            continue;
        }
    }
    // retorna linha e coluna em um vetor de inteiros
    retorno[0] = linha;
    retorno[1] = coluna;
}

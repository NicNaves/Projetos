/**
 * Programa: Processador de imagens
 * Alunos: Nícolas Naves e Luiz Filipe Silveira
 *
 * Intruções:
 * Este aquivo pode ser compilado utilizando GNU Compiler Collection no sistema operacional Linux.
 * 1- Inicial certifique-se de colocar o arquivo no diretório escolhido
 * 2- Abra o terminal pelo comando Crtl + Alt T
 * 3- Utilize o comando "cd Diretório" para navegar ao diretório especificado
 * 4- Verifique o arquivo no diretório utilizando o comando "ls" (se necessário)
 * 5- Digite o comando: gcc -std=c11 trabalhonicluiz.c -o trabalhonicluiz.exe
 * 6- O arquivo executável foi gerado; Utilize o comando ./trabalhonicluiz.exe para executá-lo
 * 7- Utilize o programa
 *
 * 
 *
 * @file trabalhonicluiz.c
 * @brief Processador de imagens com várias funções (consultar o menu abaixo)
 * 
 *
 * O programa exibe um menu com diversas opções para processar imagens: carrega uma imagem de fundo,
 * recorta, gera uma imagem negativa, imprime um histograma, oculta e revela imagens e textos em outras imagens.
 * 
 * == Carregar imagens em formato .ppm ==
 *
 * Opções do Menu:
 * 1 - carregar uma imagem de fundo
 * 2 - recortar parte da imagem de fundo
 * 3 - inverter a imagem de fundo
 * 4 - imprimir o histograma de brilho médio
 * 5 - realizar um chromakey com a imagem de fundo
 * 6 - ocultar uma imagem na imagem de fundo
 * 7 - revelar a imagem oculta inserida em uma imagem
 * 8 - inserir texto na imagem de fundo
 * 9 - recuperar texto inserido em uma imagem
 * 0 - sair
 *
 * @author Nícolas Naves e Luiz Filipe Silveira
 * @date 02/12/19
 * @bugs 
 *  Nenhum registrado até o momento */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pmn.h"


void criarhistograma(unsigned char freq[])// serve apenas para criar o histograma
{
  printf("   Histograma   \n");
    printf("----------------\n");
    for(unsigned int i = 0; i <= 255; i++){// vai até o valor maximo da imagem que é 255
     printf("  %3u\t%3d\n", i, freq[i]);
     printf("----------------\n");
    }
return;
}
void contar_a_frequencia(unsigned char numeros[], int tamanho,
    unsigned char frequencia[])
{

    // Primeiro inicializa o arranjo de frequência
    for(unsigned int i = 0; i < 256; i++)
     frequencia[i] = 0;

    // Varre nums e constrói o arranjo de frequência
    for(unsigned int i = 0; i < tamanho; i++)
     frequencia[ numeros[i] ]++;

   return;
}//fim contar_a_frequencia







void carregaImagem(char (*nome) [70]) 
{
    unsigned int cols = 0;
    unsigned int linhas = 0;
    unsigned int valormax = 0;
     

    printf("Digite um caminho para a imagem: ");
    scanf("%s", *nome);
    FILE * fp = fopen( *nome, "r" );

  /* Verifica se o arquivo de fato foi aberto, solicita nova abertura no menu */
    if (fp == NULL){
     fprintf(stderr, "\nA imagem %s não pode ser carregada\n", *nome);
     printf("Digite um novo caminho para a imagem.\n");
     scanf("%s", *nome);
    return;
    }//fim if

  // Lê as dimensões da imagem
    unsigned int formato = leia_cabecalho(fp, &linhas, &cols, &valormax);

  // Confirma o formato da imagem
    if (formato == PNM_P3) {
    } else {
    printf("\nO arquivo %s não está no formato PPM P3.\n", *nome);
    return;
    }//fim if

  // Aloca espaço para caber a imagem
    unsigned char img[linhas][cols][3];
   

    if (leia_imagem(fp, linhas, cols, valormax, img))
     printf("\n\nA imagem %s foi carregada com sucesso.\n\n", *nome);
    else
     printf("O arquivo %s está corrompido.\n", *nome);

  // Fechar o arquivo, pois a imagem já foi lida
    fclose(fp);


  return;
}
//fim carregaImagem
























void recorta (char(*nome) [70]) // CASE 2
{ 
  unsigned int linhas, linha2 = 0; // iniciar as linhas
  unsigned int cols, cols2 = 0; // iniciar as colunas
  unsigned int valormax = 0; // valor maximo
  char arqfoto[] = "nome"; //arranjo de caracteres que armazena o nome da ft a ser usada
  int m,n;//variaveis para pegar os valores que eu quero dentro da matriz
  printf("Digite o nome do aquivo que deseja abrir: ");
  scanf("%s", *nome);
  

  FILE * fp = fopen( *nome, "r" );//nome do aquivo+ modo leitura
  //Verifica se o arquivo de fato foi aberto 
  if (fp == NULL){
     fprintf(stderr, "\nA imagem %s não pode ser carregada\n", *nome);
     printf("Tente novamente!\n");
    return;
  }
 // Lê as dimensões da imagem
  int formato = leia_cabecalho(fp, &linhas, &cols, &valormax);//ler as dimensões da imagem.
 //ver as dimensões dela
  if (formato == PNM_P3) {
    printf("O arquivo %s está no formato PPM P3, com os seguintes atributos:\n", *nome);
    printf("- largura: %d\n", cols);
    printf("- altura:  %d\n", linhas);
    printf("- cor máxima: %d\n\n", valormax);
  }// fim if
   else {
    printf("O arquivo %s não está no formato PPM P3.\n", *nome);
}// fim else
  //alocar espaço
  unsigned char img[linhas][cols][3];  
  leia_imagem(fp, linhas, cols, valormax, img);
  fclose(fp);// fechar a imagem lida

 printf("digite a coordenada x do ponto de corte: ");
    scanf("%d", &m);
 printf("digite a coordenada y do ponto de corte: ");
    scanf("%d", &n);
 printf("digite a altura do retângulo de corte: ");
    scanf("%d", &linha2);
 printf("digite a largura do retângulo de corte: ");
    scanf("%d", &cols2);
  
// Aloca espaço para caber a imagem
  unsigned char recortada[linha2][cols2][3];
 for (int i = 0;   i < linha2 ; i++){// andar com as linhas até chegar no ponto máximo
	 for (int j = 0;  j < cols2; j++){ // andar com as colunas até chegar na coluna máxima que
	  for (int k = 0; k < 3; k++){// andar com a imagem
	    recortada [i][j][k] = img [i+n][j+m][k];
          }  		
	 }//fim for
	}//fim for
  printf("\ndigite o nome para a imagem de saída: ");//nome do arquivo digitado pelo usuario
    scanf("%s", arqfoto);
  if (escreve_imagem( arqfoto, linha2, cols2, valormax, recortada) == false)// escrever a imagem invertida
    printf("A imagem %s não está no formato PPM P3\n", arqfoto);
  else
    printf("Um recorte foi salvo em %s.\n\n", arqfoto);


return;
}//fim recorta




















// inverte

void inverte (char (*nome) [70]) // CASE 3
{
	
  unsigned int linhas = 0; // iniciar as linhas
  unsigned int cols = 0; // iniciar as colunas
  unsigned int valormax = 0; // valor maximo
  char arqfoto[70] ; //arranjo de caracteres que armazena o nome da ft a ser usada
  
  printf("Digite o nome do aquivo que deseja abrir: ");
  scanf("%s", *nome);
  
  FILE * fp = fopen( *nome, "r" );//nome do aquivo+ modo leitura

  //Verifica se o arquivo de fato foi aberto 
  if (fp == NULL){
     fprintf(stderr, "\nA imagem %s não pode ser carregada\n", *nome);
     printf("Tente novamente!\n");
    return;
  }
  // Lê as dimensões da imagem
  int formato = leia_cabecalho(fp, &linhas, &cols, &valormax);//abre o arquivo e guarda o valor de linhas, colunas e valor max

//ver as dimensões dela
  if (formato == PNM_P3) {
    printf("O arquivo %s está no formato PPM P3, com os seguintes atributos:\n", *nome);
    printf("- largura: %d\n", cols);
    printf("- altura:  %d\n", linhas);
    printf("- cor máxima: %d\n\n", valormax);
  } else {
    printf("O arquivo %s não está no formato PPM P3.\n", *nome);
  }
  
// Aloca espaço para caber a imagem
  unsigned char img[linhas][cols][3];
  unsigned char invertida[linhas][cols][3]; 

  if (leia_imagem(fp, linhas, cols, valormax, img)) //leia imagem recebe os valores da imagem - leia_imagem se encontra no ppm.h
    printf("Imagem %s lida.\n\n", *nome);
  else
    printf("O arquivo %s está corrompido.\n", *nome);

  // Fecha o arquivo, pois a imagem foi lida
  fclose(fp);

 char arq_invert[] = "nome";

unsigned int linha, coluna,bit;
 for(linha = 0; linha < linhas; ++linha)
   for(coluna = 0; coluna < cols; ++coluna)
     for(bit = 0; bit < 3; ++bit)
        invertida[linha][coluna][bit] = 255 - img[linha][coluna][bit];

  //nome do arquivo digitado pelo usuario
  printf("Digite o nome do arquivo para salvar: ");
  scanf("%s", arq_invert);

  if (escreve_imagem( arq_invert, linhas, cols, valormax, invertida) == false)// escrever a imagem invertida
    printf("A imagem %s não está no formato PPM P3\n", arq_invert);
  else
    printf("A imagem %s foi escrita.\n\n", arq_invert);
  

return;







}//fim inverte







//imprimir histograma 
void histograma(char(*nome)[70])
{
 unsigned int linhas = 0; // iniciar as linhas
 unsigned int cols = 0; // iniciar as colunas
 unsigned int valormax = 0; // valor maximo
 unsigned char brilho = '\0';// zerar as posições
 printf("Digite o nome do aquivo que deseja abrir: ");
  scanf("%s", *nome);
 
 FILE * fp = fopen( *nome, "r" );//nome do aquivo+ modo leitura

 if (fp == NULL){
     fprintf(stderr, "\nA imagem %s não pode ser carregada\n", *nome);
     printf("Tente novamente!\n");
    return;
  }
 //ler as dimensões
 leia_cabecalho(fp, &linhas, &cols, &valormax);//abre o arquivo e guarda o valor de linhas, colunas e valor max
 // Aloca espaço para caber a imagem
  unsigned char img[linhas][cols][3];
  if (leia_imagem(fp, linhas, cols, valormax, img)){ //leia imagem recebe os valores da imagem - leia_imagem se encontra no ppm.h
    printf("Imagem %s lida.\n\n", *nome);
  }else{
    printf("O arquivo %s está corrompido.\n", *nome);
}
    fclose(fp);
  // Determina um tamanho do arranjo de frequencia
    unsigned char frequencia[linhas * cols];
    for (int i = 0; i < linhas; i++)
    for (int j = 0; j < cols; j++){
     brilho = (img [i][j][0] + img [i][j][1] + img [i][j][2])/3;
     frequencia[brilho]++;
     }//fim for
    criarhistograma(frequencia);
return;
}

//chromaley
void chromakey(char (*nome) [70]) 
{
  unsigned int cols, cols2 = 0;
  unsigned int linhas, linhas2 = 0;
  unsigned int valormax, valormax2 = 0;
  unsigned char corpix1, corpix2, corpix3, brilho;
  char nomefrente [70];
  char arqfoto[70];
  unsigned int i, j, k = 0; 
  
  printf("Digite o nome da imagem que ficará atrás: ");
  scanf("%s", *nome);
 
  FILE * fp = fopen( *nome, "r" );//nome do aquivo+ modo leitura

 if (fp == NULL){
     fprintf(stderr, "\nA imagem %s não pode ser carregada\n", *nome);
     printf("Tente novamente!\n");
    return;
  }
 //ler as dimensões
 leia_cabecalho(fp, &linhas, &cols, &valormax);//abre o arquivo e guarda o valor de linhas, colunas e valor max
 // Aloca espaço para caber a imagem
  unsigned char img[linhas][cols][3];
  if (leia_imagem(fp, linhas, cols, valormax, img)){ //leia imagem recebe os valores da imagem - leia_imagem se encontra no ppm.h
    printf("Imagem %s lida.\n\n", *nome);
  }else{
    printf("O arquivo %s está corrompido.\n", *nome);
}
    fclose(fp);
  // Carrega a imagem de frente
    printf("Digite um caminho para a imagem de frente: ");
    scanf("%s", nomefrente);

    FILE * fp2 = fopen( nomefrente, "r" );

 if (fpfrente == NULL){
     fprintf(stderr, "\nA imagem %s não pode ser carregada\n", *nomefrente);
     printf("Tente novamente!\n");
    return;
  }

  // Lê as dimensões da imagem
    leia_cabecalho(fpfrente, &linhas2, &cols2, &valormax2);

  // Aloca espaço para caber a imagem
    unsigned char img2[linhas2][cols2][3];
    if (leia_imagem(fp2, linhas2, cols2, valormax2, img2))
    printf("Imagem %s lida.\n\n", nomefrente);
    else
    printf("O arquivo %s está corrompido.\n", nomefrente);

  //ajusta as imagens para ter o mesmo tamanho se a da frente for maior
    if (linhas2 > linhas)
    linhas2 = linhas;
    if (cols2 > cols)
    cols2 = cols;

    fclose(fp);//fecha arquivo

    // aplicando chroma key 
    brilho = (img2[0][0][0] + img2[0][0][1] + img2[0][0][2])/3; //define o brilho
    corpix1 = img2[0][0][0]; //recebe a cor do primeiro pixel
    corpix2 = img2[0][0][1]; //recebe a cor do segundo pixel
    corpix3 = img2[0][0][2]; //recebe a cor do terceiro pixel

    for (int i = 0; i < linhas2; i++)
     for (int j = 0; j < cols2; j++){
       if (((img2[i][j][0] + img2[i][j][1] + img2[i][j][2])/3) != brilho){ //se o brilho for diferente
    if (img2[i][j][0] != corpix1)  //compara cada pixel 
    img [i][j][0] = img2 [i][j][0];
    if (img2[i][j][1] != corpix2)
    img [i][j][1] = img2 [i][j][1];
    if (img2[i][j][2] != corpix3)
    img [i][j][2] = img2 [i][j][2];
       }else{
       }//fim else
      }//fim for
 
    printf("digite o nome para a imagem resultante: ");
    scanf("%s", nome_do_arq);

    if (escreve_imagem( nome_do_arq, linhas, cols, valormax, img) == false)
    printf("\nA imagem %s não está no formato PPM P3\n", nome_do_arq);
    else
    printf("\nUm chroma key da imagem de fundo com a imagem foi salvo em: %s\n\n", nome_do_arq);

  return;
}




void menu ()
{
    char nome[70];
    int opcao = 10;
    while(opcao !=0){
       switch (opcao) {

       	case 0:
       		return;

        case 1:
	    carregaImagem(&nome);
	    getchar();
	    printf("\n\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
            opcao = 10;
            break;
          
        case 2:
            recorta(&nome);
	    getchar();
	    printf("\n\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
  	    opcao = 10;
            break;

        case 3:
            inverte(&nome);
	    getchar();
	    printf("\n\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
            opcao = 10;
            break;

        case 4:
            histograma(&nome);
	    getchar();
	    printf("\n\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
            opcao = 10;
            break;

        case 5:
            chromakey(&nome);
	    getchar();
	    printf("\n\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
            opcao = 10;
            break;

        case 6:
            //ocultaImagem(&nome);
	    getchar();
	    printf("\n\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
            opcao = 10;
            break;

        case 7:
            //revelaImagem(&nome);
	    getchar();
	    printf("\n\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
            opcao = 10;
            break;

        case 8:	
	    getchar();
            //ocultaTexto(&nome);
		getchar();
	    printf("\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
            opcao = 10;
            break;

        case 9:
            //revelaTexto();
	    getchar();
	    printf("\n\nDigite uma tecla para voltar ao menu principal:");
	    getchar();
            opcao = 10;
            break;
        
        case 10:
            printf("\n\n");
    printf("****************************************************\n");
    printf("*   P R O C E S S A D O R   D E   I M A G E N S    *\n");
    printf("****************************************************\n");
    printf("\n");
    printf("Opções:\n");
    printf("\n");
    printf("1 - carregar uma imagem de fundo\n");
    printf("2 - recortar parte da imagem de fundo\n");
    printf("3 - inverte a imagem de fundo\n");
    printf("4 - imprimir o histograma de brilho médio\n");
    printf("5 - realizar um chromakey com a imagem de fundo\n");
    printf("6 - ocultar uma imagem na imagem de fundo\n");
    printf("7 - revelar a imagem oculta inserida em uma imagem\n");
    printf("8 - inserir texto na imagem de fundo\n");
    printf("9 - recuperar texto inserido em uma imagem\n");
    printf("0 - sair\n");
    printf("\n");

    printf("Digite uma opção: ");
    scanf("%u", &opcao);
    printf("\n");
    break; 
    	default:
	        printf("Digite uma opção válida!");
	        return menu();
        }//fim switch case
    }//fim while
}//fim menu

int main(){
    menu();
return 0;
}

#ifndef imm_h
#define imm_h
#include "matriz.h"
#include <stdio.h> // FILE
#define SUCCESS 0
#define TXT 1
#define IMM 2
#define INVALID_FILE -1
#define MAP_SEM_SAIDA -4

typedef struct Img Img;

Img *lerImageTXT(char *arquivotxt);
Img *lerImagetxt(FILE *arq);
Img *lerImageIMM(char *arquivoimm);
Img *lerImageimm(FILE *arq);
int liberaImage(Img *arquivo);
int openImagetxt(char *arquivotxt);
int openImageimm(char *arquivoimm);
int convertTXTIMM(char *arquivotxt, char *arquivoimm);
int convertTxtImm(Img *img, FILE *arq);
int segmentIMAGE(int thr, char *arq_entrada, char *arq_saida);
int segmentImage(int thr, Img *img, Img *img_saida);
int compCONEXO(char *arquivoimm, char *arquivoSaida);
int compConexo(Img *im, Img* im_rot);
int LABIRINTO(char *arquivotxt, char *arquivoSaida);
int labirinto(Img *mapa1, Img *mapa2);
void get_linha_coluna(FILE *arq, int *retorno);
int verificatxtimm(char *arquivo);
int openImage(char *file);
int imagemParaArquivo(Img *img, char *arquivo);

#endif

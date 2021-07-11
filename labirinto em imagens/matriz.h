#ifndef matriz_h
#define matriz_h
#include <stdlib.h>

typedef struct TMat2D TMat2D;

TMat2D *mat2D_create(int nrows, int ncolumns);
int mat2D_free(TMat2D *mat);
int mat2D_set_value(TMat2D *mat, int i, int j, int val);
int mat2D_get_value(TMat2D *mat, int i, int j, int *val);
int mat2D_get_lincol(TMat2D *mat, int *lin, int *col);
int mat2D_multiplicaescalar(TMat2D *mat, TMat2D **mat3, int x);
int mat2D_somalinhas(TMat2D *mat, int **vet);
int mat2D_somacols(TMat2D *mat, int **vet);
void exibirMatriz(TMat2D *mat);

#endif
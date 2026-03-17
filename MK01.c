//
// Created by lftgr on 07/03/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mover(int mat1[4][4], int num) {

    int linha_mov=-1, coluna_mov=-1, linha_zero=-1, coluna_zero=-1;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (mat1[i][j]==num){
            linha_mov=i; coluna_mov=j;
            }
            else if (mat1[i][j]==0){
            linha_zero=i; coluna_zero=j;
            }
        }
    }
    if (abs(linha_mov - linha_zero) + abs(coluna_mov - coluna_zero)==1) {
        mat1[linha_zero][coluna_zero]=num;
        mat1[linha_mov][coluna_mov]=0;
        return 1;
    }
    else {
        return 0;
    }

}

void embaralhar(int mat2[4][4]) {

    int jogadas_validas=0, num_aleatorio;

    while (jogadas_validas<150) {
        num_aleatorio= (rand()%15)+1;
        if (mover(mat2, num_aleatorio)==1) {
            jogadas_validas++;
        }
    }
}

int verificar(int mat3[4][4]) {

    int cont=1, num_corretos=0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (mat3[i][j]==cont) {
                num_corretos++;
            }
        cont++;
        }
    }
    if (num_corretos==15) {
        return 1;
    }
    else {
        return 0;
    }
}

int main () {

    srand(time(NULL));

    int matriz[4][4]={
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,0}
    };

    int num_mov=-1, vitoria=0;



    printf("A matriz deve ficar assim:\n");
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    embaralhar(matriz);

    printf("A matriz esta assim:\n");
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    while (vitoria==0) {

        printf("Qual numero voce deseja trocar de lugar? ");
        scanf("%d", &num_mov);

        if (mover(matriz, num_mov)==1) {
            printf("\nA matriz esta assim:\n");
            for (int i=0; i<4; i++) {
                for (int j=0; j<4; j++) {
                    printf("%2d ", matriz[i][j]);
                }
                printf("\n");
            }
            if (verificar(matriz)==1) {
                printf("Parabens pela Vitoria!\n");
                vitoria=1;
            }
        }
        else {
            printf("Numero invalido.\n");
        }
    }


    return 0;
}
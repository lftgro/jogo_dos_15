#include "raylib.h"
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


int main() {

    srand(time(NULL));


    int tamanho_peca = 150;

    InitWindow(tamanho_peca * 4, tamanho_peca * 4, "Jogo dos 15 - Luis Grochowicz");

    SetTargetFPS(60);

    int matriz[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    int vitoria = 0;

    embaralhar(matriz);

    while (!WindowShouldClose()) {

        if (vitoria == 0) {

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                int mouse_x = GetMouseX();
                int mouse_y = GetMouseY();

                int coluna_clicada = mouse_x / tamanho_peca;
                int linha_clicada = mouse_y / tamanho_peca;
                int num_clicado = matriz[linha_clicada][coluna_clicada];

                if (num_clicado != 0) {
                    mover(matriz, num_clicado);
                }

                if (verificar(matriz) == 1) {
                    vitoria = 1;
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {

                if (matriz[i][j] != 0) {

                    int pos_x = j * tamanho_peca;
                    int pos_y = i * tamanho_peca;

                    DrawRectangle(pos_x + 2, pos_y + 2, tamanho_peca - 4, tamanho_peca - 4, DARKBLUE);

                    char texto_num[3];
                    sprintf(texto_num, "%d", matriz[i][j]);

                    DrawText(texto_num, pos_x + 50, pos_y + 50, 60, WHITE);
                }
            }
        }

        if (vitoria == 1) {
            DrawRectangle(0, 220, 600, 150, LIME);
            DrawText("VOCE VENCEU!", 70, 270, 60, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
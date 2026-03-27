##
## Created by lftgr on 11/03/2026.
##

import random
import os
import time

C_VERDE = "\033[32m"   # Para números corretos
C_VERMELHO = "\033[31m" # Para o espaço vazio (0)
C_CIANO = "\033[36m"   # Para a moldura/título
C_AMARELO = "\033[33m" # Para vitória
C_RESET = "\033[0m"    # Para voltar à cor padrão do terminal

def mover(mat1, num):

    linha_mov = -1
    coluna_mov = -1
    linha_zero = -1
    coluna_zero = -1

    for i in range(4):
        for j in range(4):

            if mat1[i][j] == num:
                linha_mov = i
                coluna_mov = j
            elif mat1[i][j] == 0:
                linha_zero = i
                coluna_zero = j

    if abs(linha_mov - linha_zero) + abs(coluna_mov - coluna_zero) == 1:
        mat1[linha_zero][coluna_zero] = num
        mat1[linha_mov][coluna_mov] = 0

        return True

    else:
        return False

def embaralhar(mat2, esc):

    opcoes = [11,7,0]
    tentativas = 0
    num_ant = -1

    dificuldade = opcoes[esc-1] if 0 <= (esc-1) < len(opcoes) else 11

    while verificar(mat2)>dificuldade and tentativas<1000:
        num_aleatorio = random.randint(1,15)
        if num_ant != num_aleatorio:
            if mover(mat2, num_aleatorio):
                exibir(mat2)

                num_ant = num_aleatorio

                time.sleep(0.2)

            tentativas+=1


def verificar(mat3):

    cont=1
    num_corretos = 0

    for i in range(4):
        for j in range(4):

            if mat3[i][j] == cont:
                num_corretos+=1

            cont+=1

    return num_corretos

def exibir(mat4):

    cont=1
    os.system('cls')

    print(f"{C_CIANO}========== JOGO DOS 15 =========={C_RESET}\n")

    for linha in mat4:
        print("         ", end="|")
        for num in linha:
            if num == 0:
                print(f"{C_VERMELHO}{num:2d}{C_RESET}", end=" ")
            elif num == cont:
                print(f"{C_VERDE}{num:2d}{C_RESET}", end=" ")
            else:
                print(f"{num:2d}", end=" ")
            cont+=1
        print("|")
    print(f"\n{C_CIANO}================================={C_RESET}")


def main():

    matriz = [
        [1,2,3,4],
        [5,6,7,8],
        [9,10,11,12],
        [13,14,15,0]
    ]

    vitoria=False
    movimentos=0

    exibir(matriz)

    print("Escolha a dificuldade:")
    print("1 - Baixa (4 números fora do lugar)")
    print("2 - Média (8 números forado lugar)")
    print("3 - Alta (Mais difícil)") ## Máximo de números possíveis fora do lugar em até no max 1000 movimentos

    while True:
        try:
            escolha = int(input("Digite o número da opção: "))
            break
        except ValueError:
            input(f"{C_VERMELHO}Erro! Digite apenas números. (Pressione Enter){C_RESET}")

    embaralhar(matriz, escolha)
    exibir(matriz)

    tempo_inicial=time.time()

    while vitoria==False:

        try:
            num_escolhido=int(input("Informe o numero que deseja mover: "))
            if mover(matriz,num_escolhido ) == True:

                exibir(matriz)
                movimentos+=1
                print(f"\nMovimentos realizados: {movimentos}")

                if verificar(matriz) == 15:
                    tempo_final=time.time()
                    duracao=tempo_final-tempo_inicial
                    minutos = int(duracao // 60)
                    segundos = int(duracao % 60)

                    exibir(matriz)
                    print(f"\n{C_AMARELO}Parabéns! Você venceu!{C_RESET}\n")
                    print("Total de movimentos: ", movimentos)
                    print(f"Tempo final: {minutos:02d}:{segundos:02d}")
                    vitoria=True

            else:
                print(f"\n{C_VERMELHO}Número inválido. Tente novamente.{C_RESET}\n")

        except ValueError:
            input(f"{C_VERMELHO}Entrada inválida! Use apenas números. (Pressione Enter){C_RESET}")
            continue


main()
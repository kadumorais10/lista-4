#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100  // Altura da imagem
#define M 100  // Largura da imagem

// Função para gerar uma imagem de entrada pseudoaleatória
void gerar_imagem(unsigned char imagem[N][M]) {
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    // Preenche a imagem com valores aleatórios entre 0 e 255
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            imagem[i][j] = rand() % 256;
        }
    }
}

// Função para calcular o LBP
void calcular_lbp(unsigned char imagem[N][M], unsigned char lbp_imagem[N][M]) {
    // Desloca a janela 3x3 sobre cada pixel da imagem (exceto as bordas)
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < M - 1; j++) {
            unsigned char centro = imagem[i][j];
            unsigned char binario = 0;

            // Comparação dos 8 vizinhos em sentido horário (0, 1, 2, 3, 4, 5, 6, 7)
            int k = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue;  // Pular o pixel central

                    int vizinho_i = i + di;
                    int vizinho_j = j + dj;
                    unsigned char vizinho = imagem[vizinho_i][vizinho_j];

                    // Se o vizinho for maior ou igual ao centro, coloca 1; caso contrário, 0
                    if (vizinho >= centro) {
                        binario |= (1 << (7 - k));  // Define o bit correspondente
                    }

                    k++;
                }
            }

            lbp_imagem[i][j] = binario;  // Atribui o valor binário calculado
        }
    }
}

// Função para calcular o histograma da imagem LBP
void calcular_histograma(unsigned char lbp_imagem[N][M], int histograma[256]) {
    // Inicializa o histograma com zeros
    for (int i = 0; i < 256; i++) {
        histograma[i] = 0;
    }

    // Contagem das ocorrências dos valores LBP
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            unsigned char valor = lbp_imagem[i][j];
            histograma[valor]++;
        }
    }
}

// Função para imprimir a imagem LBP e o histograma (apenas para fins de depuração)
void imprimir_resultados(unsigned char lbp_imagem[N][M], int histograma[256]) {
    // Imprimir a imagem LBP (apenas para visualização)
    printf("Imagem LBP:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%3d ", lbp_imagem[i][j]);
        }
        printf("\n");
    }

    // Imprimir o histograma
    printf("\nHistograma LBP:\n");
    for (int i = 0; i < 256; i++) {
        if (histograma[i] > 0) {
            printf("Valor %3d: %d ocorrências\n", i, histograma[i]);
        }
    }
}

int main() {
    unsigned char imagem[N][M];
    unsigned char lbp_imagem[N][M];
    int histograma[256];

    // Gerar a imagem de entrada
    gerar_imagem(imagem);

    // Calcular a imagem LBP
    calcular_lbp(imagem, lbp_imagem);

    // Calcular o histograma da imagem LBP
    calcular_histograma(lbp_imagem, histograma);

    // Exibir resultados
    imprimir_resultados(lbp_imagem, histograma);

    return 0;
}

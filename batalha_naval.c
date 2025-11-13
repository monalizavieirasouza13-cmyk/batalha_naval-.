#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5
#define NAVIOS 3

#define AGUA '~'
#define NAVIO 'N'
#define TIRO_AGUA 'O'
#define TIRO_ACERTO 'X'
#define NEVOA '.'

void inicializar(char real[TAM][TAM], char visivel[TAM][TAM]);
void posicionarNavios(char real[TAM][TAM]);
void exibir(const char visivel[TAM][TAM], int acertos, int tentativas);
int lerCoordenada(const char *label);
int atirar(char real[TAM][TAM], char visivel[TAM][TAM], int linha, int coluna);

int main(void) {
    char real[TAM][TAM];
    char visivel[TAM][TAM];
    int linha, coluna, tentativas = 0, acertos = 0;

    srand((unsigned)time(NULL));
    inicializar(real, visivel);
    posicionarNavios(real);

    puts("=== JOGO DE BATALHA NAVAL ===\n");

    while (acertos < NAVIOS) {
        exibir(visivel, acertos, tentativas);

        linha  = lerCoordenada("linha");
        coluna = lerCoordenada("coluna");

        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            puts("Coordenada inválida!\n");
            continue;
        }

        tentativas++;
        if (atirar(real, visivel, linha, coluna)) {
            acertos++;
            puts("🎯 Acertou!\n");
        } else {
            puts("💦 Água!\n");
        }
    }

    exibir(visivel, acertos, tentativas);
    printf("Parabéns! Você afundou todos os navios em %d tentativas.\n", tentativas);
    return 0;
}

void inicializar(char real[TAM][TAM], char visivel[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            real[i][j] = AGUA;
            visivel[i][j] = NEVOA;
        }
    }
}

void posicionarNavios(char real[TAM][TAM]) {
    int colocados = 0;
    while (colocados < NAVIOS) {
        int l = rand() % TAM;
        int c = rand() % TAM;
        if (real[l][c] == AGUA) {
            real[l][c] = NAVIO;
            colocados++;
        }
    }
}

void exibir(const char visivel[TAM][TAM], int acertos, int tentativas) {
    printf("Acertos: %d/%d | Tentativas: %d\n", acertos, NAVIOS, tentativas);
    printf("   ");
    for (int j = 0; j < TAM; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d: ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", visivel[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int lerCoordenada(const char *label) {
    int x;
    printf("Digite %s (0-%d): ", label, TAM - 1);
    if (scanf("%d", &x) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return -1;
    }
    return x;
}

int atirar(char real[TAM][TAM], char visivel[TAM][TAM], int linha, int coluna) {
    if (visivel[linha][coluna] == TIRO_ACERTO || visivel[linha][coluna] == TIRO_AGUA) {
        puts("⚠️ Você já tentou essa posição!");
        return 0;
    }

    if (real[linha][coluna] == NAVIO) {
        visivel[linha][coluna] = TIRO_ACERTO;
        real[linha][coluna] = TIRO_ACERTO;
        return 1;
    } else {
        visivel[linha][coluna] = TIRO_AGUA;
        real[linha][coluna] = TIRO_AGUA;
        return 0;
    }
}

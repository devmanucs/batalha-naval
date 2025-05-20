#include <stdio.h>

/**
 * Batalha Naval - Nível Novato
 * Oceanic Games - Implementação do tabuleiro básico com posicionamento de navios
 * 
 * Este programa cria um tabuleiro 10x10 e posiciona dois navios de tamanho 3:
 * - Um navio na posição horizontal
 * - Um navio na posição vertical
 * 
 * Legenda do tabuleiro:
 * 0 - Água
 * 3 - Navio
 */

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

/**
 * Função para inicializar o tabuleiro com água (valor 0)
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * Função para verificar se é possível posicionar um navio em determinada coordenada
 * Retorna 1 se for possível, 0 caso contrário
 */
int validarPosicaoNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                        int linhaInicial, int colunaInicial, 
                        int ehHorizontal) {
    
    // Verificar se as coordenadas iniciais estão dentro do tabuleiro
    if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO || 
        colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
        return 0;
    }
    
    // Verificar se o navio cabe no tabuleiro a partir da posição inicial
    if (ehHorizontal) {
        if (colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return 0;
        }
        
        // Verificar se as posições estão livres
        for (int j = colunaInicial; j < colunaInicial + TAMANHO_NAVIO; j++) {
            if (tabuleiro[linhaInicial][j] != AGUA) {
                return 0; // Já existe um navio aqui
            }
        }
    } else {
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return 0;
        }
        
        // Verificar se as posições estão livres
        for (int i = linhaInicial; i < linhaInicial + TAMANHO_NAVIO; i++) {
            if (tabuleiro[i][colunaInicial] != AGUA) {
                return 0; // Já existe um navio aqui
            }
        }
    }
    
    return 1; // Posição válida
}

/**
 * Função para posicionar um navio no tabuleiro
 * Retorna 1 se o navio foi posicionado com sucesso, 0 caso contrário
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                   int linhaInicial, int colunaInicial, 
                   int ehHorizontal) {
    
    // Validar se é possível posicionar o navio
    if (!validarPosicaoNavio(tabuleiro, linhaInicial, colunaInicial, ehHorizontal)) {
        return 0;
    }
    
    // Posicionar o navio
    if (ehHorizontal) {
        for (int j = colunaInicial; j < colunaInicial + TAMANHO_NAVIO; j++) {
            tabuleiro[linhaInicial][j] = NAVIO;
        }
    } else {
        for (int i = linhaInicial; i < linhaInicial + TAMANHO_NAVIO; i++) {
            tabuleiro[i][colunaInicial] = NAVIO;
        }
    }
    
    return 1;
}

/**
 * Função para exibir o tabuleiro no console
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n  ");
    // Imprimir cabeçalho das colunas
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    // Imprimir linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Coordenadas iniciais dos navios
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 3;
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 7;
    
    // Inicializar tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Posicionar navio horizontal
    int sucessoHorizontal = posicionarNavio(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal, 1);
    if (!sucessoHorizontal) {
        printf("Erro ao posicionar o navio horizontal! Coordenadas inválidas.\n");
        return 1;
    }
    
    // Posicionar navio vertical
    int sucessoVertical = posicionarNavio(tabuleiro, linhaNavioVertical, colunaNavioVertical, 0);
    if (!sucessoVertical) {
        printf("Erro ao posicionar o navio vertical! Coordenadas inválidas ou sobreposição.\n");
        return 1;
    }
    
    // Exibir tabuleiro com os navios posicionados
    printf("Batalha Naval - Oceanic Games\n");
    printf("Legenda: 0 = Agua, 3 = Navio\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
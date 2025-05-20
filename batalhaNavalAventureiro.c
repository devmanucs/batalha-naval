#include <stdio.h>

/**
 * Batalha Naval - Nível Aventureiro
 * Oceanic Games - Implementação do tabuleiro com posicionamento de navios
 * horizontal, vertical e diagonal
 * 
 * Este programa cria um tabuleiro 10x10 e posiciona quatro navios de tamanho 3:
 * - Dois navios na posição horizontal ou vertical
 * - Dois navios na posição diagonal
 * 
 * Legenda do tabuleiro:
 * 0 - Água
 * 3 - Navio
 */

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Constantes para identificar a direção do navio
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL_DESC 2  // Diagonal descendente (de cima para baixo, esquerda para direita)
#define DIAGONAL_ASC 3   // Diagonal ascendente (de baixo para cima, esquerda para direita)

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
 * @param tabuleiro - O tabuleiro do jogo
 * @param linhaInicial - Linha inicial do navio
 * @param colunaInicial - Coluna inicial do navio
 * @param direcao - Direção do navio (HORIZONTAL, VERTICAL, DIAGONAL_DESC, DIAGONAL_ASC)
 */
int validarPosicaoNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                        int linhaInicial, int colunaInicial, 
                        int direcao) {
    
    // Verificar se as coordenadas iniciais estão dentro do tabuleiro
    if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO || 
        colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
        return 0;
    }
    
    // Verificar se o navio cabe no tabuleiro e se as posições estão livres
    // com base na direção do navio
    switch (direcao) {
        case HORIZONTAL:
            // Verificar se o navio cabe horizontalmente
            if (colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            
            // Verificar se as posições estão livres
            for (int j = colunaInicial; j < colunaInicial + TAMANHO_NAVIO; j++) {
                if (tabuleiro[linhaInicial][j] != AGUA) {
                    return 0; // Já existe um navio aqui
                }
            }
            break;
            
        case VERTICAL:
            // Verificar se o navio cabe verticalmente
            if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            
            // Verificar se as posições estão livres
            for (int i = linhaInicial; i < linhaInicial + TAMANHO_NAVIO; i++) {
                if (tabuleiro[i][colunaInicial] != AGUA) {
                    return 0; // Já existe um navio aqui
                }
            }
            break;
            
        case DIAGONAL_DESC:
            // Verificar se o navio cabe na diagonal descendente
            if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
                colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            
            // Verificar se as posições estão livres
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (tabuleiro[linhaInicial + i][colunaInicial + i] != AGUA) {
                    return 0; // Já existe um navio aqui
                }
            }
            break;
            
        case DIAGONAL_ASC:
            // Verificar se o navio cabe na diagonal ascendente
            if (linhaInicial - (TAMANHO_NAVIO - 1) < 0 || 
                colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            
            // Verificar se as posições estão livres
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (tabuleiro[linhaInicial - i][colunaInicial + i] != AGUA) {
                    return 0; // Já existe um navio aqui
                }
            }
            break;
            
        default:
            // Direção inválida
            return 0;
    }
    
    return 1; // Posição válida
}

/**
 * Função para posicionar um navio no tabuleiro
 * Retorna 1 se o navio foi posicionado com sucesso, 0 caso contrário
 * @param tabuleiro - O tabuleiro do jogo
 * @param linhaInicial - Linha inicial do navio
 * @param colunaInicial - Coluna inicial do navio
 * @param direcao - Direção do navio (HORIZONTAL, VERTICAL, DIAGONAL_DESC, DIAGONAL_ASC)
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                   int linhaInicial, int colunaInicial, 
                   int direcao) {
    
    // Validar se é possível posicionar o navio
    if (!validarPosicaoNavio(tabuleiro, linhaInicial, colunaInicial, direcao)) {
        return 0;
    }
    
    // Posicionar o navio com base na direção
    switch (direcao) {
        case HORIZONTAL:
            for (int j = colunaInicial; j < colunaInicial + TAMANHO_NAVIO; j++) {
                tabuleiro[linhaInicial][j] = NAVIO;
            }
            break;
            
        case VERTICAL:
            for (int i = linhaInicial; i < linhaInicial + TAMANHO_NAVIO; i++) {
                tabuleiro[i][colunaInicial] = NAVIO;
            }
            break;
            
        case DIAGONAL_DESC:
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
            }
            break;
            
        case DIAGONAL_ASC:
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial - i][colunaInicial + i] = NAVIO;
            }
            break;
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
    // Navios horizontal e vertical
    int linhaNavioHorizontal = 1;
    int colunaNavioHorizontal = 3;
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 8;
    
    // Navios diagonais
    int linhaDiagonalDesc = 3;
    int colunaDiagonalDesc = 1;
    int linhaDiagonalAsc = 7;
    int colunaDiagonalAsc = 2;
    
    // Inicializar tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Flag para monitorar o sucesso das operações de posicionamento
    int sucesso = 1;
    
    // Posicionar navio horizontal
    sucesso = posicionarNavio(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal, HORIZONTAL);
    if (!sucesso) {
        printf("Erro ao posicionar o navio horizontal! Coordenadas inválidas.\n");
        return 1;
    }
    
    // Posicionar navio vertical
    sucesso = posicionarNavio(tabuleiro, linhaNavioVertical, colunaNavioVertical, VERTICAL);
    if (!sucesso) {
        printf("Erro ao posicionar o navio vertical! Coordenadas inválidas ou sobreposição.\n");
        return 1;
    }
    
    // Posicionar navio diagonal descendente
    sucesso = posicionarNavio(tabuleiro, linhaDiagonalDesc, colunaDiagonalDesc, DIAGONAL_DESC);
    if (!sucesso) {
        printf("Erro ao posicionar o navio diagonal descendente! Coordenadas inválidas ou sobreposição.\n");
        return 1;
    }
    
    // Posicionar navio diagonal ascendente
    sucesso = posicionarNavio(tabuleiro, linhaDiagonalAsc, colunaDiagonalAsc, DIAGONAL_ASC);
    if (!sucesso) {
        printf("Erro ao posicionar o navio diagonal ascendente! Coordenadas inválidas ou sobreposição.\n");
        return 1;
    }
    
    // Exibir tabuleiro com todos os navios posicionados
    printf("Batalha Naval - Oceanic Games\n");
    printf("Legenda: 0 = Agua 3 = Navio\n");
    printf("Posicionamento de navios: 2 retilieos e 2 diagonais\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
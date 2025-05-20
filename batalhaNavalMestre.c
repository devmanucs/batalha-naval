#include <stdio.h>

/**
 * Batalha Naval - Nível Mestre (Finalizado)
 * Oceanic Games - Implementação completa com habilidades especiais
 * 
 * Este programa cria um tabuleiro 10x10, posiciona quatro navios em diferentes
 * direções e implementa três habilidades especiais com áreas de efeito distintas:
 * - Cone: Expande-se para baixo a partir do ponto de origem
 * - Cruz: Forma uma cruz centrada no ponto de origem
 * - Octaedro: Forma um losango (vista frontal de um octaedro)
 * 
 * Legenda do tabuleiro:
 * 0 - Água
 * 3 - Navio
 * 5 - Área afetada por habilidade
 * 8 - Navio afetado por habilidade
 */

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Tamanho da matriz de habilidade (5x5)

// Valores para o tabuleiro
#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5
#define NAVIO_AFETADO 8

// Direções dos navios
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL_DESC 2
#define DIAGONAL_ASC 3

// Tipos de habilidades
#define HABILIDADE_CONE 0
#define HABILIDADE_CRUZ 1
#define HABILIDADE_OCTAEDRO 2

// Cores para exibição (ANSI escape codes)
#define COR_AGUA "\x1B[34m"       // Azul para água
#define COR_NAVIO "\x1B[33m"      // Amarelo para navio
#define COR_HABILIDADE "\x1B[35m" // Magenta para área de habilidade
#define COR_AFETADO "\x1B[31m"    // Vermelho para navio afetado
#define COR_RESET "\x1B[0m"       // Resetar cor

/**
 * Inicializa o tabuleiro com água (valor 0)
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * Verifica se é possível posicionar um navio nas coordenadas especificadas
 * Retorna 1 se possível, 0 caso contrário
 */
int validarPosicaoNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                        int linhaInicial, int colunaInicial, 
                        int direcao) {
    
    // Verifica limites do tabuleiro
    if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO || 
        colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
        return 0;
    }
    
    // Verifica posição baseado na direção
    switch (direcao) {
        case HORIZONTAL:
            if (colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
            for (int j = colunaInicial; j < colunaInicial + TAMANHO_NAVIO; j++) {
                if (tabuleiro[linhaInicial][j] != AGUA) return 0;
            }
            break;
            
        case VERTICAL:
            if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
            for (int i = linhaInicial; i < linhaInicial + TAMANHO_NAVIO; i++) {
                if (tabuleiro[i][colunaInicial] != AGUA) return 0;
            }
            break;
            
        case DIAGONAL_DESC:
            if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
                colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (tabuleiro[linhaInicial + i][colunaInicial + i] != AGUA) return 0;
            }
            break;
            
        case DIAGONAL_ASC:
            if (linhaInicial - (TAMANHO_NAVIO - 1) < 0 || 
                colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (tabuleiro[linhaInicial - i][colunaInicial + i] != AGUA) return 0;
            }
            break;
            
        default:
            return 0;
    }
    
    return 1;
}

/**
 * Posiciona um navio no tabuleiro na direção especificada
 * Retorna 1 se bem sucedido, 0 caso contrário
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                   int linhaInicial, int colunaInicial, 
                   int direcao) {
    
    if (!validarPosicaoNavio(tabuleiro, linhaInicial, colunaInicial, direcao)) {
        return 0;
    }
    
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
 * Cria a matriz de habilidade do tipo Cone
 * Formato: expande-se para baixo a partir do ponto de origem (topo)
 */
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Padrão do cone: cada linha aumenta a largura
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        int largura = (i * 2) + 1;
        int inicio = (TAMANHO_HABILIDADE - largura) / 2;
        
        for (int j = inicio; j < inicio + largura && j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 1;
        }
    }
}

/**
 * Cria a matriz de habilidade do tipo Cruz
 * Formato: linhas horizontal e vertical centradas
 */
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    int centro = TAMANHO_HABILIDADE / 2;
    
    // Linha horizontal
    for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
        habilidade[centro][j] = 1;
    }
    
    // Linha vertical
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        habilidade[i][centro] = 1;
    }
}

/**
 * Cria a matriz de habilidade do tipo Octaedro (losango)
 * Formato: diamante centrado
 */
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    int centro = TAMANHO_HABILIDADE / 2;
    
    // Cria padrão de losango
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        int distancia = (i > centro) ? (i - centro) : (centro - i);
        int largura = TAMANHO_HABILIDADE - (distancia * 2);
        
        if (largura > 0) {
            int inicio = (TAMANHO_HABILIDADE - largura) / 2;
            
            for (int j = inicio; j < inicio + largura; j++) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * Aplica uma habilidade ao tabuleiro a partir das coordenadas de origem
 */
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                     int linhaOrigem, int colunaOrigem) {
    
    int centro = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linhaTab = linhaOrigem - centro + i;
            int colunaTab = colunaOrigem - centro + j;
            
            // Verifica limites do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO &&
                colunaTab >= 0 && colunaTab < TAMANHO_TABULEIRO) {
                
                // Aplica efeito apenas onde a habilidade está ativa
                if (habilidade[i][j] == 1) {
                    if (tabuleiro[linhaTab][colunaTab] == NAVIO) {
                        tabuleiro[linhaTab][colunaTab] = NAVIO_AFETADO;
                    } 
                    else if (tabuleiro[linhaTab][colunaTab] == AGUA) {
                        tabuleiro[linhaTab][colunaTab] = AREA_HABILIDADE;
                    }
                }
            }
        }
    }
}

/**
 * Exibe uma matriz de habilidade para visualização
 */
void exibirMatrizHabilidade(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                          const char* nomeHabilidade) {
    printf("\nMatriz da habilidade %s (%dx%d):\n", nomeHabilidade, 
          TAMANHO_HABILIDADE, TAMANHO_HABILIDADE);
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

/**
 * Exibe o tabuleiro com cores para melhor visualização
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n  ");
    // Cabeçalho das colunas
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d", j);
    }
    printf("\n");
    
    // Linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d", i); // Número da linha
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Aplica cores baseadas no conteúdo da célula
            switch (tabuleiro[i][j]) {
                case AGUA:
                    printf(COR_AGUA " 0" COR_RESET);
                    break;
                case NAVIO:
                    printf(COR_NAVIO " 3" COR_RESET);
                    break;
                case AREA_HABILIDADE:
                    printf(COR_HABILIDADE " 5" COR_RESET);
                    break;
                case NAVIO_AFETADO:
                    printf(COR_AFETADO " 8" COR_RESET);
                    break;
                default:
                    printf(" ?");
            }
        }
        printf("\n");
    }
}

/**
 * Copia o conteúdo de um tabuleiro para outro
 */
void copiarTabuleiro(int origem[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int destino[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            destino[i][j] = origem[i][j];
        }
    }
}

int main() {
    // Tabuleiros
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tabuleiroHabilidade[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Matrizes de habilidades
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Posições dos navios
    int navios[4][3] = {
        {1, 3, HORIZONTAL},  // Navio horizontal
        {5, 8, VERTICAL},     // Navio vertical
        {3, 1, DIAGONAL_DESC}, // Navio diagonal descendente
        {7, 2, DIAGONAL_ASC}   // Navio diagonal ascendente
    };
    
    // Origens das habilidades
    int origensHabilidades[3][2] = {
        {2, 4},  // Cone
        {5, 5},  // Cruz
        {8, 7}   // Octaedro
    };
    
    // Inicializa tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona os navios
    for (int i = 0; i < 4; i++) {
        if (!posicionarNavio(tabuleiro, navios[i][0], navios[i][1], navios[i][2])) {
            printf("Erro ao posicionar navio %d! Verifique as coordenadas.\n", i+1);
            return 1;
        }
    }
    
    // Cria as habilidades
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);
    
    // Exibe informações iniciais
    printf("Batalha Naval - Oceanic Games (Nível Mestre)\n");
    printf("Legenda:\n");
    printf(COR_AGUA "0 = Agua" COR_RESET ", ");
    printf(COR_NAVIO "3 = Navio" COR_RESET ", ");
    printf(COR_HABILIDADE "5 = Area de Habilidade" COR_RESET ", ");
    printf(COR_AFETADO "8 = Navio Afetado\n\n" COR_RESET);
    
    // Exibe tabuleiro inicial
    printf("Tabuleiro inicial com quatro navios:\n");
    exibirTabuleiro(tabuleiro);
    
    // Exibe matrizes de habilidades
    exibirMatrizHabilidade(habilidadeCone, "Cone");
    exibirMatrizHabilidade(habilidadeCruz, "Cruz");
    exibirMatrizHabilidade(habilidadeOctaedro, "Octaedro");
    
    // Aplica e exibe cada habilidade separadamente
    
    // Habilidade Cone
    copiarTabuleiro(tabuleiro, tabuleiroHabilidade);
    aplicarHabilidade(tabuleiroHabilidade, habilidadeCone, origensHabilidades[0][0], origensHabilidades[0][1]);
    printf("\n\nTabuleiro com habilidade CONE aplicada (origem: %d,%d):", 
          origensHabilidades[0][0], origensHabilidades[0][1]);
    exibirTabuleiro(tabuleiroHabilidade);
    
    // Habilidade Cruz
    copiarTabuleiro(tabuleiro, tabuleiroHabilidade);
    aplicarHabilidade(tabuleiroHabilidade, habilidadeCruz, origensHabilidades[1][0], origensHabilidades[1][1]);
    printf("\n\nTabuleiro com habilidade CRUZ aplicada (origem: %d,%d):", 
          origensHabilidades[1][0], origensHabilidades[1][1]);
    exibirTabuleiro(tabuleiroHabilidade);
    
    // Habilidade Octaedro
    copiarTabuleiro(tabuleiro, tabuleiroHabilidade);
    aplicarHabilidade(tabuleiroHabilidade, habilidadeOctaedro, origensHabilidades[2][0], origensHabilidades[2][1]);
    printf("\n\nTabuleiro com habilidade OCTAEDRO aplicada (origem: %d,%d):", 
          origensHabilidades[2][0], origensHabilidades[2][1]);
    exibirTabuleiro(tabuleiroHabilidade);
    
    return 0;
}
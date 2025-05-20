# Batalha Naval

Projeto de implementação do clássico jogo Batalha Naval em linguagem C, desenvolvido para fins de estudo e prática de lógica de programação, manipulação de arrays e estruturas de repetição.

## Sobre o Projeto

Este repositório contém três versões do jogo:

- **batalhaNaval.c**: Versão Novato  
  Implementa um tabuleiro 10x10 com posicionamento de dois navios de tamanho 3, sendo um na horizontal e outro na vertical.

- **batalhaNavalAventureiro.c**: Versão Aventureiro  
  Expande a lógica para permitir o posicionamento de quatro navios de tamanho 3, incluindo navios em posições diagonais (ascendente e descendente), além das posições horizontal e vertical.

- **batalhaNavalMestre.c**: Versão Mestre  
  Adiciona habilidades especiais ao jogo, permitindo visualizar áreas de efeito no tabuleiro. São implementadas três habilidades: Cone, Cruz e Octaedro (losango), cada uma com uma matriz de área de efeito distinta. O programa exibe o tabuleiro com os navios e as áreas afetadas por cada habilidade, utilizando diferentes valores e cores para facilitar a visualização.

## Funcionalidades

- Criação e exibição de um tabuleiro 10x10.
- Posicionamento de navios de tamanho 3 em diferentes direções.
- Validação de posições para evitar sobreposição e garantir que os navios estejam dentro dos limites do tabuleiro.
- Impressão do tabuleiro no console, com legenda para fácil visualização.
- **[Mestre] Implementação de habilidades especiais com áreas de efeito (Cone, Cruz e Octaedro), sobrepondo matrizes de habilidade ao tabuleiro e exibindo as áreas afetadas.**

## Legenda do Tabuleiro

- `0` - Água
- `3` - Navio
- `5` - Área afetada por habilidade (exclusivo da versão Mestre)
- `8` - Navio afetado por habilidade (exclusivo da versão Mestre)

## Como Executar

1. **Clone o repositório** (ou copie os arquivos para sua máquina):
   git clone <https://github.com/devmanucs/batalha-naval.git>

2. **Compile o arquivo desejado** usando um compilador C.

## Estrutura dos Arquivos

- `batalhaNaval.c` — Versão básica do jogo.
- `batalhaNavalAventureiro.c` — Versão com posicionamento diagonal.
- `batalhaNavalMestre.c` — Versão com habilidades especiais e áreas de efeito.
- `README.md` — Este arquivo de documentação.

## Objetivos de Aprendizagem

- Praticar lógica de programação e controle de fluxo.
- Trabalhar com arrays bidimensionais.
- Implementar funções para modularização do código.
- Exercitar validação de dados e tratamento de erros.
- **[Mestre] Aplicar matrizes de áreas de efeito e sobreposição dinâmica no tabuleiro.**

## Contribuição

Sinta-se à vontade para sugerir melhorias, abrir issues ou enviar pull requests!

## Licença

Este projeto é livre para fins de estudo e aprendizado.

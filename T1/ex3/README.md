# Análise do Programa: Gerenciamento de Estoque de Produtos

Esta tarefa descreve a implementação de um programa em C responsável por cadastrar as quantidades e valores em estoques de produtos.

## Implementação

### 1. Estrutura do Código

O programa é modularizado em dois arquivos principais: `main.c` (que contém a lógica principal do programa) e `product.c` (que implementa as funções de manipulação dos produtos e do estoque).

### 2. Estrutura de Dados

A estrutura de dados central do projeto é uma `struct Product`, que representa um único produto no estoque. Para gerenciar uma coleção de produtos de tamanho dinâmico, foi utilizado um **array dinâmico de ponteiros**.

 Cada elemento do array `$stock$` é um ponteiro para uma `$struct Product$`, que por sua vez é alocada de forma independente na memória *heap*. Essa estratégia possibilita que tenhamos uma estrutura de dados composta por varios `$struct Product$` que podem ser criados separadamente e ainda removidos da memória quando inutilizados. 

### 3. Análise das Funções

* `stock_create(int n)`: Esta função é responsável por alocar o array de ponteiros que servirá como o contêiner do estoque. A função recebe um inteiro `n` e aloca espaço para `$n$` ponteiros para `$Product$`. É o primeiro passo para a alocação do array dinâmico.
* `product_create()`: Aloca dinamicamente a memória para uma única `$struct Product$`. Essa função isola a lógica de alocação de um produto individual, tornando o código mais legível e reutilizável.
* `product_ask_info(Product *p)`: Interage com o usuário para preencher os dados de um produto (`nome`, `preço`, `quantidade`).
* `product_print_info(Product* p)`: Exibe as informações detalhadas de um produto, incluindo seu valor total individual (`preço * quantidade`).
* `stock_get_total(Product **stock, int n)`: Percorre o array de produtos para somar o valor total de cada item, retornando o valor total do estoque.
* `product_free_all(Product **stock, int n)`: Implementa a liberação de memória.


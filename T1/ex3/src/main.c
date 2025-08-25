#include <stdio.h>
#include <stdlib.h>
#include <product.h>

int main()
{
    // Para contornar o problema de /n implícitos não desejados, usamos um buffer e depois atoi para inteiro
    // Esse problema surge ao usar fgets seguido de scanf

    char buff[10];
    printf("How many products to register? ");
    fgets(buff, 10, stdin);
    printf("\n");
    
    int n = atoi(buff);
    
    Product **stock = stock_create(n); // Gera vetor de ponteiros

    // Laço que itera sobre todo o vetor
    for (int i = 0; i < n; i++)
    {
        // Cria e armazena informações na estrutura
        stock[i] = product_create();
        product_ask_info(stock[i]);
    }

    // Laço que itera sobre todo o vetor
    for (int i = 0; i < n; i++)
    {
        product_print_info(stock[i]);
    }
    
    float total_stock = stock_get_total(stock, n); // Calcula o valor do estoque inteiro

    printf("Total value on stock: %.2f\n", total_stock);

    product_free_all(stock, n); // Libera a memória
    
    return 0;
}
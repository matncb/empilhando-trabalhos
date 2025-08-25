#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <product.h>

// Cria o vetor de ponteiros
Product **stock_create(int n)
{
    Product **stock = (Product **) malloc(n * sizeof(Product*));

    if (stock == NULL)
    {
        printf("Memory allocation error.\n");
        exit(1);
    }
    
    return stock;
}

// Cria um produto
Product *product_create()
{
    Product *p = (Product *) malloc(sizeof(Product));

    if (p == NULL)
    {
        printf("Memory allocation error.\n");
        exit(1);
    }
    
    return p;
}

// Pede ao usuário os valores para serem armazenados
void product_ask_info(Product *p)
{
    printf("Enter with name: ");
    fgets(p->name, sizeof(p->name), stdin);

    printf("Enter with price: ");
    char buff[20];
    fgets(buff, 20, stdin);
    p->price = atof(buff);

    printf("Enter with quantity: ");
    fgets(buff, 10, stdin);
    p->quantity = atoi(buff);

    printf("\n");

    return;
}

// Printa valores armazenados
void product_print_info(Product* p)
{
    printf("\n----------------------------\n");
    printf("Name: %s", p->name);
    printf("Price: %.2f\n", p->price);
    printf("Quantity: %d\n", p->quantity);
    printf("Total product value %.2f\n", (float) p->price * p->quantity);
    printf("----------------------------\n");

    return;
}

// Calcula valor total do estoque
float stock_get_total(Product **stock, int n)
{
    float value = 0.;
    for (int i = 0; i < n; i++)
    {
        value += stock[i]->price * stock[i]->quantity;
    }

    return value;
}

// Libera toda a memória alocada
void product_free_all(Product **stock, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(stock[i]);
    }

    free(stock);

    return ;
}
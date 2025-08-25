#ifndef _PRODUCT_H
#define _PRODUCT_H

// Define o struct
typedef struct _Product {
    char name[50];
    float price;
    int quantity;
} Product;


void product_print_info(Product *p);
Product **stock_create(int n);
Product *product_create();
void product_ask_info(Product *p);
void product_free_all(Product **stock, int n);

float stock_get_total(Product **stock, int n);

#endif
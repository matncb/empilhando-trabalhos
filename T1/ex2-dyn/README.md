### **Relatório de Implementação: Gerenciamento de Dados de Pessoas**

#### **1. Introdução**

Este código-fonte implementa uma solução para o cadastro de dados de N pessoas, com o valor de N definido pelo usuário em tempo de execução. A solução utiliza alocação dinâmica de memória para gerenciar a quantidade de dados.

---

#### **2. Estrutura do Projeto**

O projeto está organizado em três arquivos:

* `person.h`: Arquivo de cabeçalho que define a estrutura `_Person` e declara os protótipos de todas as funções públicas. Ele serve como a interface do módulo de pessoas.
* `person.c`: Contém a implementação de todas as funções declaradas em `person.h`. Inclui as lógicas de alocação de memória, coleta de dados, impressão e liberação de memória.
* `main.c`: É responsável por interagir com o usuário, coordenar as chamadas das funções do módulo `person.c`.

---

#### **3. Pontos da Implementação**


* **Alocação Dinâmica (`malloc`)**: A implementação utiliza um array de ponteiros (`Person **people`) alocado dinamicamente para armazenar os endereços de cada estrutura de pessoa. Cada estrutura individual também é alocada dinamicamente.

* **Gerenciamento de Memória**: O programa aloca e **libera** toda a memória utilizada. A função `person_free_all` garante que a memória de cada estrutura e, posteriormente, a do array de ponteiros seja liberada.

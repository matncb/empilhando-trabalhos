## Gerenciador de Pessoas em C

### Descrição do Projeto

Essa é a versão sem alocação dinâmica de [Gerenciamento de Dados de Pessoas](../ex2-dyn/README.md).

### Estrutura dos Arquivos

O projeto é organizado em três arquivos:

  * `main.c`: Contém a função principal (`main`) onde a lógica de entrada e saída de dados é executada.
  * `person.h`: Arquivo de cabeçalho que define a estrutura `Person` e os protótipos de funções relacionadas a ela.
  * `person.c`: Arquivo de implementação que contém a definição das funções declaradas em `person.h`.

Esta versão, diferentemente da dinâmica, não tem as interfaces de `Person`, pois os dados são recebidos diretamente na função principal. Como estamos tratando os dados de forma estática, não temos acesso a memória de cada estrutura de Person.

Utilizamos apenas a função `person_print_info()` para simplificar a exportação dos dados na tela.


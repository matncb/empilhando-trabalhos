## TRABALHO 1

O projeto tem um site que pode ser acessado em [Pages](https://matncb.github.io/empilhando-trabalhos/T1/)
Este repositório está hospedado no github e pode ser acessado em [Github](https://github.com/matncb/empilhando-trabalhos/tree/master/T1)

## Organização

O trabalho é organizado em 3 exercícios e 5 diretórios distintos. Para os exercícios 1 e 3, existe apenas uma pasta para cada. Como o exercício 2 pedia diversas variações, fizemos diretórios específicos. Dentro de cada diretório existe um arquivo `README.md`, contendo a ideia geral usada para a elaboração do código-fonte.

Os arquivos `README.md` são:

 * [Exercício 1]
    * [Fibonacci](ex1-fibonacci/README.md)
    * [Fatorial](ex1-factorial/README.md)
 * [Exercício 2]
     * [Dinâmico](ex2-dyn/README.md)
     * [Estático](ex2-static/README.md)
        * [Caso específico para 3 Pessoas](ex2-3_people/README.md)
 * [Exercício 3]
       * [Exercício 3](ex3/README.md)

**Observação**: Para o exercício 2, recomenda-se ler o caso dinâmico primeiro, já que os outros são explicados com base em modificações nesse projeto. O caso específico foi feito apenas por questão de completude com o enuncidado da questão, mas, em sua essência, difere muito pouco com relação ao caso geral estático.


## Execução

Para compilação de qualquer dos exercícios, deve-se entrar na pasta do exercício e executar o comando `make`.
Os arquivos serão compilados nas respetivas pastas `./build` de cada exercício. Cada programa poderá ser executado utilizando `./build/main`.

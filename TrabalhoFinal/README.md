# Trabalho Final - Sistema de Recomendação Musical

## Descrição

Sistema de recomendação musical que utiliza três TADs (Tipos Abstratos de Dados):
- **Grafo**: Representa conexões entre pessoas baseadas em similaridade musical
- **Queue (Fila)**: Gerencia recomendações musicais
- **Tree (Árvore)**: Organiza pessoas por tamanho de playlist

## Estrutura do Projeto

```
TrabalhoFinal/
├── data/
│   ├── names.csv      # Arquivo CSV com nomes de pessoas
│   └── songs.csv      # Arquivo CSV com músicas e artistas
├── includes/          # Headers dos TADs
├── src/              # Implementações dos TADs
├── build/            # Arquivos compilados (gerado)
└── Makefile          # Arquivo de build

```

## Arquivos de Dados CSV

### names.csv
Arquivo simples com um nome por linha:
```
Ana
Bruno
Carla
...
```

### songs.csv
Arquivo com formato: `nome_da_música,artista`
```
Bohemian Rhapsody,Queen
Stairway to Heaven,Led Zeppelin
...
```

## Compilação e Execução

```bash
# Compilar
make

# Executar
./build/main

# Limpar arquivos compilados
make clean
```

## Funcionalidades

1. **Carregamento de Dados**: Lê nomes e músicas de arquivos CSV externos
2. **Criação de Pessoas**: Gera pessoas aleatórias com playlists
3. **Cálculo de Similaridade**: Usa o grafo para calcular similaridades baseadas em músicas em comum
4. **Organização em Árvore**: Organiza pessoas por tamanho de playlist
5. **Sistema de Recomendações**: Usa fila (Queue) para gerenciar recomendações
6. **Exportação**: Exporta a matriz de adjacência do grafo para `graph.csv`

## TADs Utilizados

### Grafo (Graph)
- Representa conexões entre pessoas
- Calcula similaridade baseada em músicas em comum
- Exporta matriz de adjacência

### Queue (Fila)
- Gerencia recomendações musicais
- Implementação circular estática

### Tree (Árvore Binária de Busca)
- Organiza pessoas por tamanho de playlist
- Permite busca e ordenação eficiente

## Adicionando Mais Dados

Para adicionar mais nomes, edite `data/names.csv` e adicione um nome por linha.

Para adicionar mais músicas, edite `data/songs.csv` no formato:
```
Nome da Música,Artista
```

O sistema carregará automaticamente todos os dados dos arquivos CSV na inicialização.


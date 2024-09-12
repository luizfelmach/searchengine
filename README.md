# searchengine

```cpp
// Indexador
// Retorna a tabela de indices.
// Essa tabela contém o mapeamento de cada palavra dizendo em quais
// documentos essa palavra aparece.
//
// Algo como: map<string, set<string>>
//                 |            |
//                 |_ Palavra   |
//                              |_ Conjunto de Documentos. Importante que
//                                                         seja conjunto para não
//                                                         haver documentos repetidos.

Tabela indexador(Tabela stopwords, Colecao pages) {

    Tabela indices   // Acho que essa Tabela pode ser uma TST

    for page in pages {
        for palavra in page {

            palavra = TOLOWER(palavra);

            if (busca(stopwords, palavra) != NULL) continue // Ignora stopwords

            Tabela docs = busca(indices, palavra) // <-- Essa tabela acho que pode ser uma RedBlackTree
                                                  // A redblack permite que não tenha chaves repetidas e
                                                  // a iteração sobre o documentos é mais simples que uma tabela
                                                  // hash e uma TST

            if (!docs) {
                docs = new Tabela
            }

            insere(docs, page, NULL) // Qualquer coisa no value
                                     // Tem que ser garantido que na tabela nao vai ter chaves repetidas.
                                     // Ponto importante !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            insere(indices, palavra, docs)
        }
    }

    return indices
}
```

```cpp
// Dado um grafo, armazena as relacoes entre as paginas

struct Vertex {
    int out      // Numero de saidas de um vertice
    Colecao in   // Conexoes que chegam nesse nó
    double PR    // Page Rank atual
    double PR_LAST // Page Rank passado
}

Tabela relacionamento_entre_paginas(FILE grafo.txt) {

    Tabela vertices // Acho que essa tabela pode ser uma TST

    for line in grafo.txt {

        String page = read()
        int saidas = read()

        Vertex v = busca(vertices, page)

        if (!vertex) {
            v = Vertex(saidas, []) // Cria um vertice com saidas e nenhuma entrada para ele.
            insere(vertices, page, v)
        } else {
            v->out = saidas
        }

        for 0...saidas {
            String w = read()

            Vertex adj = busca(vertices, w)

            if (!adj) {
                adj = Vertex(0, [])
                insere(adj->in, page)
                insere(vertices, w, adj)
            } else {
                insere(adj->in, page)
            }
        }
    }

    return vertices
}
```

```cpp
// Calcula o page rank para cada vertice na tabela do grafo.
// Eh por referencia, entao quando terminar de rodar os valores estarão atualizados dentro da estrutura.

void calcula_page_rank(Colecao pages, Tabela vertices) {

    int n = size(pages)

    for page in pages { // Page é uma string
        Vertex v = busca(vertices, page) // Procura o vertice associado a essa pagina
        v->PR_LAST = 1 / n
        v->PR = INF // Faz com que o primeiro erro seja infinito
    }

    double EPS = 10e-6

    while (1) {
        double ERRO = 0

        for page in pages {
            Vertex v = busca(vertices, page)
            recalculaPR(v)
            ERRO += abs(v->PR - v->PR_LAST)
        }

        ERRO /= n

        if (ERRO < EPS) break

        for page in pages {
            Vertex v = busca(vertices, page)
            v->PR_LAST = v->PR
        }
    }
}

void recalculaPR(Vertex v) {
    int n = size(vertices)
    double res = (1 - alpha) / n

    for w in v->in {
        res += w->PR_LAST / w->out
    }

    res *= alpha

    if (v->out == 0) res += alpha * v->PR_LAST

    v->PR = res
}
```

```cpp
// Algoritmo para buscar documentos em comum dado uma entrada de termos
// e uma tabela de indices.

Colecao documentos_relevantes(Tabela indices, Colecao Termos) {
    Tabela tabela_freqs // Acho que pode ser uma RBTree
    Colecao docs_relevantes = []

    Tabela tabela_docs = busca(indices, termos[0])

    if (!tabela_docs) return docs_relevantes


    TreeIT it = iterador(tabela_docs) // Faz a iteraçao na arvore usando uma stack
                                      // Muito eficiente

    for [doc, _] in it { // Ignora value
        insere(tabela_freqs, doc, 1) // o 1 aqui precisa ser alocado ou fazer cast para void *
    }

    free(it) // Importante desalocar o iterador

    for i = 1...size(Termos) {
        Tabela tabela_docs = busca(indices, termos[i])

        if (!tabela_docs) return docs_relevantes

        TreeIT it = iterador(tabela_docs)

        // Nao insere mais na tabela, so aumenta a frequencia
        for [doc, _] in it {
            int * freq = busca(tabelas_freq, doc)
            if (freq != NULL) freq++;
        }

        free(it)
    }


    TreeIT it = iterador(tabela_freqs)

    for [doc, freq] in it { // par chave valor
        if (freq == size(Termos)) {
            insere(docs_relevates, doc)
        }
    }

    free(it)

    return docs_relevante
}
```

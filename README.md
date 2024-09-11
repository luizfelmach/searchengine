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

Tabela indexador(Colecao SW, Colecao pages) {

    Tabela indices   // Acho que essa Tabela pode ser uma TST
    Tabela stopwords // Essa também

    for stopword in SW {
        insere(stopwords, TOLOWER(stopword), NULL) // Qualquer coisa no value
    }

    for page in pages {
        for palavra in page {

            palavra = TOLOWER(palavra);

            if (busca(stopwords, page) != NULL) continue // Ignora stopwords

            Tabela docs = busca(indices, palavra) // <-- Essa tabela acho que pode ser uma RedBlackTree

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
    double PRK_1 // Page Rank passado
}

Tabela relacionamento_entre_paginas(FILE grafo.txt) {

    Tabela vertices

    for line in grafo.txt {

        String page = read()
        int saidas = read()

        Vertex v = busca(vertices, page)

        if (!vertex) {
            v = Vertex(saidas, [])
            insere(vertices, page, v)
        } else {
            v->out = saidas
        }

        for 0...saidas {
            String w = read()

            Vertex adj = busca(vertices, w)

            if (!adj) {
                insere(adj->in, page)
            } else {
                adj = Vertex(0, [])
                insere(adj->in, page)
                insere(vertices, w, adj)
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
        v->PR_K_1 = 1 / n
        v->PR = INF // Faz com que o primeiro erro seja infinito
    }

    double EPS = 10e-6

    while (1) {
        double ERRO = 0

        for page in pages {
            Vertex v = busca(vertices, page)
            recalculaPR(v, vertices, n)
            ERRO += abs(v->PR - v->PRK_1)
        }

        ERRO /= n

        if (ERRO < EPS) break

        for page in pages {
            Vertex v = busca(vertices, page)
            v->PRK_1 = v->PR
        }
    }
}

void recalculaPR(Vertex v, Tabela vertices) {
    int n = size(vertices)
    double res = (1 - alpha) / n

    for w in v->in {
        Vertex adj = busca(vertices, w)
        res += adj->PR_K1 / adj->out
    }

    res *= alpha

    if (v->out == 0) res += alpha * v->PRK_1

    v->PR = res
}

```

```cpp
// Algoritmo para buscar documentos em comum dado uma entrada de termos
// e uma tabela de indices.

//   !!!!!!!!!!!!!!!!!! Em construção ainda. Precisa melhorar algumas coisas.

Colecao documentos_relevantes(Tabela indices, Colecao Termos) {
    Tabela tabela_freqs
    Colecao docs_relevantes = []

    Tabela tabela_docs = busca(indices, termos[0])

    if (!tabela_docs) return docs_relevantes

    Colecao docs = traverse(tabela_docs); // Retorna um vetor com chave/valor

    for [doc, _] in docs { // Ignora value
        insere(tabela_freqs, doc, 1)
    }

    for i = 1...size(Termos) {
        Tabela tabela_docs = busca(indices, termos[i])

        if (!tabela_docs) return docs_relevantes

        Colecao docs = traverse(tabela_docs)

        // Nao insere mais na tabela, so aumenta a frequencia
        for doc in docs {
            int * freq = busca(tabelas_freq, doc)
            if (freq != NULL) freq++;
        }
    }

    Colecao freqs = traverse(tabela_freqs)

    for [doc, freq] in freqs { // par chave valor
        if (freq == size(Termos)) {
            insere(docs_relevates, doc)
        }
    }

    return docs_relevante
}
```

# searchengine

```cpp
// Indexador
// Retorna a tabela de indices.
// Essa tabela contém o mapeamento de cada palavra dizendo em quais
// documentos essa palavra aparece.

Tabela indexador(Colecao SW, Pages pages) {

    Tabela indices
    Tabela stopwords

    for stopword in SW {
        insere(stopwords, TOLOWER(stopword), NULL) // Qualquer coisa no value
    }

    for page in pages {
        for palavra in page {

            palavra = TOLOWER(palavra);

            if (busca(stopwords, page) != NULL) continue // Ignora stopwords

            Tabela docs = busca(indices, palavra)

            if (!docs) {
                docs = new Tabela
            }

            String *page = busca(docs, page)

            if (!page) {
                insere(docs, page, NULL) // Qualquer coisa no value
            }

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

    Tabela relacionamento

    for line in grafo {

        String page = read()
        int saidas = read()

        Vertex v = busca(relacionamento, page)

        if (!vertex) {
            v = Vertex(saidas, [])
            insere(relacionamento, page, v)
        } else {
            v->out = saidas
        }

        for 0...saidas {
            String w = read()

            Vertex adj = busca(relacionamento, w)

            if (!adj) {
                insere(adj->in, page)
            } else {
                adj = Vertex(0, [])
                insere(adj->in, page)
                insere(relacionamento, w, adj)
            }
        }
    }

    return relacionamento
}

```

```cpp
// Algoritmo para buscar documentos em comum dado uma entrada de termos
// e uma tabela de indices.

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

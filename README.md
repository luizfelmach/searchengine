# searchengine

Search Engine

```

// Algoritmo para buscar documentos em comum dado uma entrada de termos e uma tabela de indices.

struct {
    int n                   // Quantidade de termos
    Colecao docs_relevantes // Documentos Relevantes
} Context;

void traverse_docs_relevantes(Node n, Context ctx) {
    String doc = key(n)
    int freq = value(n)

    if (freq == ctx.n) {
        insere(ctx.docs_relevantes, doc)
    }
}


Colecao documentos_relevantes(Tabela indices, Colecao Termos) {
    Tabela tabela_freq
    Colecao docs_relevantes = []

    Colecao docs = busca(indices, termos[0])

    if (!docs) return docs_relevantes

    for doc in docs {
        insere(tabela_freq, doc, 1)
    }

    for i = 1...size(Termos) {
        Colecao docs = busca(indices, termos[i])

        if (!docs) return docs_relevantes

        // Nao insere mais na tabela, so aumenta a frequencia
        for doc in docs {
            int * freq = busca(tabelas_freq, doc)
            if (freq != NULL) freq++;
        }
    }

    Context ctx = {size(Termos), docs_relevantes}

    traverse(tabela_freq, traverse_docs_relevantes, ctx)

    return docs_relevante
}
```

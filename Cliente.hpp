#ifndef CLIENTE_H
#define CLIENTE_H

// Estrutura para os nós da lista encadeada de ações
struct NodoAcao {
    int idAcao;
    NodoAcao* proximo;
};

class Cliente {
private:
    int id;
    NodoAcao* head; // Início da lista encadeada
    int tamanho;    // Quantidade de ações na carteira

public:
    Cliente();
    ~Cliente();

    // Inicializa o cliente com seu ID
    void inicializar(int id);

    // Adiciona uma ação à carteira (Operação B)
    void adicionarAcao(int idAcao);

    // Remove uma ação da carteira (Operação V)
    void removerAcao(int idAcao);

    // Getters
    int getId() const;
    NodoAcao* getCarteira() const; // Para percorrer na hora da consulta Q
    int getTamanhoCarteira() const;
};

#endif
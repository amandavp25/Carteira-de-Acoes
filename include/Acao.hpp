#ifndef ACAO_H
#define ACAO_H

#include <string>

class Acao {
private:
    int id;
    int w;
    double* historico; // Vetor dinâmico para os preços
    int contagem;      // Total de preços recebidos até agora
    int indiceAtual;   // Ponteiro para a posição no vetor circular

    // Função auxiliar para obter o retorno elementar r_i 
    double obterRetornoElementar(int i) const;
    
public:
    // Construtor e Destrutor
    Acao();
    ~Acao();

    // Inicializa a ação com ID e o tamanho da janela w
    void inicializar(int id, int w);

    // Adiciona uma nova cotação usando lógica de vetor circular
    void adicionarPreco(double preco);

    // Retorna o preço p_i onde p_{w-1} é o mais recente
    double obterPrecoOrdenado(int i) const;

    // Funções para cálculo das métricas 
    double calcularRET() const;
    double calcularAVGRET() const;
    double calcularSTAB() const;
    double calcularCONS() const;

    // Getters básicos
    int getId() const;
    bool temCotacoesSuficientes() const;

};

#endif

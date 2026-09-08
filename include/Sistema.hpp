#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "Acao.hpp"
#include "Cliente.hpp"
#include <string>

// Estrutura auxiliar para o ranking global
struct ItemRanking {
    int idAcao;
    double pontos;
};

class Sistema {
private:
    Acao** acoes;       // Array de ponteiros para as ações
    Cliente** clientes; // Array de ponteiros para os clientes
    int nAcoes;         // N total de ações
    int nClientes;      // u total de clientes
    int w;              // Janela de cotações

    // Algoritmo de ordenação (Selection Sort)
    // Ordena por pontos (descrescente) e ID (crescente) para desempate
    void ordenarRanking(ItemRanking* arr, int tamanho);

public:
    Sistema(int nA, int nC, int janela);
    ~Sistema();

    // Comandos
    void registrarPreco(int idAcao, double preco); // Comando P
    void comprarAcao(int idCliente, int idAcao);   // Comando B
    void venderAcao(int idCliente, int idAcao);    // Comando V
    
    // Executa a consulta Q e imprime os resultados
    void consultar(int idQ, int idC, int n, int m, std::string* metrs, double* pesos);
};

#endif

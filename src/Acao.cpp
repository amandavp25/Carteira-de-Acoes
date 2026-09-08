#include "Acao.hpp"
#include <cmath>

Acao::Acao() : id(-1), w(0), historico(nullptr), contagem(0), indiceAtual(0) {}

Acao::~Acao() {
    if (historico != nullptr) {
        delete[] historico; 
    }
}

void Acao::inicializar(int id, int w) {
    this->id = id;
    this->w = w;
    if (this->historico != nullptr) {
        delete[] this->historico; // Limpa se já existir
    }
    this->historico = new double[w];
    this->contagem = 0;
    this->indiceAtual = 0;
}

void Acao::adicionarPreco(double preco) {
    historico[indiceAtual] = preco;
    indiceAtual = (indiceAtual + 1) % w; // Lógica de vetor circular
    if (contagem < w) contagem++;
}

int Acao::getId() const { return id; }

bool Acao::temCotacoesSuficientes() const { return contagem == w; }

// Retorna p_i onde p_{w-1} é o mais recente
double Acao::obterPrecoOrdenado(int i) const {
    // Mapeia o índice lógico (0 a w-1) para a posição real no vetor circular
    int pos = (indiceAtual - contagem + i + w) % w;
    return historico[pos];
}

//Retorno elementar: r_i = (p_i / p_i-1) - 1
double Acao::obterRetornoElementar(int i) const {
    double p_atual = obterPrecoOrdenado(i);
    double p_anterior = obterPrecoOrdenado(i - 1);
    if (p_anterior == 0.0) return 0.0;
    return (p_atual / p_anterior) - 1.0; // Fórmula r_i 
}

// Métrica RET: (p_{w-1} / p_0) - 1 
double Acao::calcularRET() const {
    if (!temCotacoesSuficientes()) return 0.0;
    return (obterPrecoOrdenado(w - 1) / obterPrecoOrdenado(0)) - 1.0;
}

// Métrica AVGRET: Média dos retornos elementares 
double Acao::calcularAVGRET() const {
    if (!temCotacoesSuficientes()) return 0.0;
    double soma = 0;
    for (int i = 1; i < w; i++) {
        soma += obterRetornoElementar(i);
    }
    return soma / (w - 1);
}

// Métrica STAB: 1 / (1 + VOL_w) 
double Acao::calcularSTAB() const {
    if (!temCotacoesSuficientes()) return 0.0;
    double media = calcularAVGRET();
    double somaVar = 0;
    for (int i = 1; i < w; i++) {
        double r_i = obterRetornoElementar(i);
        somaVar += std::pow(r_i - media, 2);
    }
    double vol = std::sqrt(somaVar / (w - 1));
    return 1.0 / (1.0 + vol);
}

// Métrica CONS: Proporção de retornos positivos 
double Acao::calcularCONS() const {
    if (!temCotacoesSuficientes()) return 0.0;
    int positivos = 0;
    for (int i = 1; i < w; i++) {
        if (obterRetornoElementar(i) > 0) positivos++;
    }
    return (double)positivos / (w - 1);
}

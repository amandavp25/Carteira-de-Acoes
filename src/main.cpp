#include <iostream>
#include <string>
#include <chrono>
#include "Sistema.hpp"

using namespace std;

int main() {
    char comando;
    int w, nAcoes = 0, nClientes = 0;
    Sistema* sistema = nullptr;

    try{
        // 1. Processa a linha global de métricas (M)
        if (cin >> comando && comando == 'M') {
            cin >> w;
            
            // Lê as métricas disponíveis até o fim da linha
            string lixo; 
            getline(cin, lixo); // Consome o restante da linha M
        }

        while (cin >> comando) {
            if (comando == 'A') {
                int idAcao;
                cin >> idAcao;
                // Como os IDs são de 0 a N-1, o maior ID define a contagem
                if (idAcao >= nAcoes) nAcoes = idAcao + 1;
            } else if (comando == 'U') {
                int idCli;
                cin >> idCli;
                if (idCli >= nClientes) nClientes = idCli + 1;
            } else {
                // Quando encontrar P, B, V ou Q, as declarações A e U acabaram.
                // Instanciamos o sistema agora.
                if (sistema == nullptr) {
                    sistema = new Sistema(nAcoes, nClientes, w);
                }
                if (comando == 'P') {
                    int idA;
                    double preco;
                    cin >> idA >> preco;
                    auto inicio = std::chrono::steady_clock::now();
                    sistema->registrarPreco(idA, preco); 
                    auto fim = std::chrono::steady_clock::now();
                    auto tempo_us = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio).count();
                    std::cerr << "TEMPO_P: " << tempo_us << " us" << std::endl;
                } 
                else if (comando == 'B') {
                    int idC, idA;
                    cin >> idC >> idA;
                    auto inicio = std::chrono::steady_clock::now();
                    sistema->comprarAcao(idC, idA); 
                    auto fim = std::chrono::steady_clock::now();
                    auto tempo_us = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio).count();
                    std::cerr << "TEMPO_BCV: " << tempo_us << " us" << std::endl;
                } 
                else if (comando == 'V') {
                    int idC, idA;
                    cin >> idC >> idA;
                    auto inicio = std::chrono::steady_clock::now();
                    sistema->venderAcao(idC, idA); 
                    auto fim = std::chrono::steady_clock::now();
                    auto tempo_us = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio).count();
                    std::cerr << "TEMPO_BCV: " << tempo_us << " us" << std::endl;
                } 
                else if (comando == 'Q') {
                    int idQ, idC, n, m;
                    cin >> idQ >> idC >> n >> m;
                    
                    string* nomes = new string[m];
                    double* pesos = new double[m];
                    
                    for (int i = 0; i < m; i++) {
                        cin >> nomes[i] >> pesos[i]; 
                    }

                    auto inicio = std::chrono::steady_clock::now();
                    
                    sistema->consultar(idQ, idC, n, m, nomes, pesos);

                    auto fim = std::chrono::steady_clock::now();
                    std::chrono::duration<double, std::milli> tempo_ms = fim - inicio;

                    std::cerr << "TEMPO_Q: " << tempo_ms.count() << " ms" << std::endl;
                    
                    delete[] nomes;
                    delete[] pesos;
                }
                else {
                    // Ignora o resto da linha caso venha um comando lixo que não é M, A, U, P, B, V, Q
                    string lixo;
                    getline(cin, lixo);
                }
            }
        }
    }
    catch (const std::bad_alloc& e) {
        // Captura falhas do operador 'new' (Falta de Memória)
        std::cerr << "Erro Critico: Falha na alocacao de memoria (std::bad_alloc) - " << e.what() << std::endl;
        
        // Libera a memória que já conseguiu ser alocada antes do erro para não deixar vazamento
        if (sistema != nullptr) {
            delete sistema;
        }
        return 1; // Retorna 1 indicando que o programa terminou com erro
    } 
    catch (const std::exception& e) {
        // Captura genérica para outros erros da biblioteca padrão C++
        std::cerr << "Erro Inesperado: " << e.what() << std::endl;
        if (sistema != nullptr) {
            delete sistema;
        }
        return 1;
    }

    if (sistema != nullptr) {
        delete sistema;
    }

    return 0;
}
#include "Sistema.hpp"
#include <iostream>
#include <iomanip>

Sistema::Sistema(int nA, int nC, int janela) : nAcoes(nA), nClientes(nC), w(janela) {
    acoes = new Acao*[nAcoes];
    for (int i = 0; i < nAcoes; i++) {
        acoes[i] = new Acao();
        acoes[i]->inicializar(i, w);
    }
    clientes = new Cliente*[nClientes];
    for (int i = 0; i < nClientes; i++) {
        clientes[i] = new Cliente();
        clientes[i]->inicializar(i);
    }
}

Sistema::~Sistema() {
    for (int i = 0; i < nAcoes; i++) delete acoes[i];
    for (int i = 0; i < nClientes; i++) delete clientes[i];
    delete[] acoes;
    delete[] clientes;
}

void Sistema::ordenarRanking(ItemRanking* arr, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int indexMelhor = i;
        for (int j = i + 1; j < tamanho; j++) {
            // Critério 1: Maior pontuação 
            if (arr[j].pontos > arr[indexMelhor].pontos) {
                indexMelhor = j;
            } 
            // Critério 2: Menor ID em caso de empate 
            else if (arr[j].pontos == arr[indexMelhor].pontos) {
                if (arr[j].idAcao < arr[indexMelhor].idAcao) {
                    indexMelhor = j;
                }
            }
        }
        ItemRanking temp = arr[i];
        arr[i] = arr[indexMelhor];
        arr[indexMelhor] = temp;
    }
}

void Sistema::registrarPreco(int idAcao, double preco) {
    if (idAcao >= 0 && idAcao < nAcoes) {
        acoes[idAcao]->adicionarPreco(preco);
    }
}

void Sistema::comprarAcao(int idC, int idA) { 
    if (idC >= 0 && idC < nClientes && idA >= 0 && idA < nAcoes) {
        clientes[idC]->adicionarAcao(idA);
    }
}

void Sistema::venderAcao(int idC, int idA) { 
    if (idC >= 0 && idC < nClientes && idA >= 0 && idA < nAcoes) {
        clientes[idC]->removerAcao(idA);
    }
}

void Sistema::consultar(int idQ, int idC, int n, int m, std::string* metrs, double* pesos) {
    ItemRanking* rankingGlobal = new ItemRanking[nAcoes];
    for (int i = 0; i < nAcoes; i++) {
        rankingGlobal[i].idAcao = i;
        rankingGlobal[i].pontos = 0.0;
    }

    // Processa cada métrica da consulta para gerar a pontuação global
    for (int k = 0; k < m; k++) {
        ItemRanking* tempMetrica = new ItemRanking[nAcoes];
        for (int i = 0; i < nAcoes; i++) {
            tempMetrica[i].idAcao = i;
            if (metrs[k] == "RET") tempMetrica[i].pontos = acoes[i]->calcularRET();
            else if (metrs[k] == "AVGRET") tempMetrica[i].pontos = acoes[i]->calcularAVGRET();
            else if (metrs[k] == "STAB") tempMetrica[i].pontos = acoes[i]->calcularSTAB();
            else if (metrs[k] == "CONS") tempMetrica[i].pontos = acoes[i]->calcularCONS();
        }

        // Ordena ações por esta métrica específica
        ordenarRanking(tempMetrica, nAcoes);

        // Atribui pontos: (N - posição) * peso
        for (int i = 0; i < nAcoes; i++) {
            int id = tempMetrica[i].idAcao;
            rankingGlobal[id].pontos += (double)(nAcoes - i) * pesos[k];
        }
        delete[] tempMetrica;
    }

    // Ordenação final do ranking global por pontuação acumulada
    ItemRanking* rankingFinal = new ItemRanking[nAcoes];
    for(int i=0; i<nAcoes; i++) rankingFinal[i] = rankingGlobal[i];
    ordenarRanking(rankingFinal, nAcoes);

    // Filtragem local: Projeta o ranking sobre a carteira do cliente
    Cliente* cli = clientes[idC];
    int tamCarteira = cli->getTamanhoCarteira();
    
    ItemRanking* carteiraFiltrada = new ItemRanking[tamCarteira];
    int count = 0;
    for (int i = 0; i < nAcoes; i++) {
        int idA = rankingFinal[i].idAcao;
        // Verifica se a ação está na lista ligada do cliente
        NodoAcao* atual = cli->getCarteira();
        while (atual != nullptr) {
            if (atual->idAcao == idA) {
                carteiraFiltrada[count++] = rankingFinal[i];
                break;
            }
            atual = atual->proximo;
        }
    }

    // Impressão dos resultados R <idQ> <tipo> <pos> <idAcao> <pontos>
    std::cout << std::fixed << std::setprecision(2);
    int mostrar = (n < tamCarteira) ? n : tamCarteira; // Se n > carteira, mostra o que tem 

    // Melhores (M)
    for (int i = 0; i < mostrar; i++) {
        std::cout << "R " << idQ << " M " << i << " " << carteiraFiltrada[i].idAcao 
                  << " " << carteiraFiltrada[i].pontos << std::endl;
    }

    // Piores (P) - do fim para o começo
    for (int i = 0; i < mostrar; i++) {
        int idx = tamCarteira - 1 - i;
        std::cout << "R " << idQ << " P " << i << " " << carteiraFiltrada[idx].idAcao 
                  << " " << carteiraFiltrada[idx].pontos << std::endl;
    }

    delete[] rankingGlobal;
    delete[] rankingFinal;
    delete[] carteiraFiltrada;
}
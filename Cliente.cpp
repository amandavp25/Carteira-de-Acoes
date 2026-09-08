#include "Cliente.hpp"

Cliente::Cliente() : id(-1), head(nullptr), tamanho(0) {}

Cliente::~Cliente() {
    NodoAcao* atual = head;
    while (atual != nullptr) {
        NodoAcao* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}

void Cliente::inicializar(int id) {
    this->id = id;
    this->head = nullptr;
    this->tamanho = 0;
}

void Cliente::adicionarAcao(int idAcao) {
    // Cria um novo nó e insere no início da lista
    NodoAcao* novo = new NodoAcao;
    novo->idAcao = idAcao;
    novo->proximo = head;
    head = novo;
    tamanho++;
}

void Cliente::removerAcao(int idAcao) {
    NodoAcao* atual = head;
    NodoAcao* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->idAcao == idAcao) {
            if (anterior == nullptr) {
                // Remover o primeiro elemento
                head = atual->proximo;
            } else {
                // Remover elemento do meio ou fim
                anterior->proximo = atual->proximo;
            }
            delete atual;
            tamanho--;
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

int Cliente::getId() const { return id; }

NodoAcao* Cliente::getCarteira() const { return head; }

int Cliente::getTamanhoCarteira() const { return tamanho; }
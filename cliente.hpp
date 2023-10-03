#pragma once

#include <string>
using std::string;

struct Cliente {
    string senha;
    double saldo;
    long numero_conta;
    
    constexpr inline bool operator==(const Cliente & cliente) {
        return this->numero_conta == cliente.numero_conta &&
               this->senha == cliente.senha; 
    }

    void operator=(const Cliente & cliente) {
        this->numero_conta = cliente.numero_conta;
        this->senha = cliente.senha;
        this->saldo = cliente.saldo; 
    }
};
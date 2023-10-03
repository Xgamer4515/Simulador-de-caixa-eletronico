#include "cliente.hpp"
#include "menu.hpp"
#include <iostream>
#include <fstream>
#include <limits>
using std::cin;
using std::endl;
using std::cout;
using std::cerr;
using std::fixed;
using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::streamsize;
using std::numeric_limits;

/**************************** INTERFASE PRIVADA ****************************/

inline void limpar_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void verificar_escolha(int &opcao) {
    while (cin.fail() || opcao < 1 || opcao > 6) {
        cerr << "Opção inválida. Tente Novamente: ";
        limpar_buffer();
        cin >> opcao;
    }
}

void ler_cliente(Cliente & cliente) {
    cout << "Número da conta: ";
    cin >> cliente.numero_conta;

    while (cin.fail() && cliente.numero_conta < 0) {
        cout << "Digite um número de conta válido: ";
        limpar_buffer();
        cin >> cliente.numero_conta;
    }

    cout << "Senha: ";
    cin >> cliente.senha;
}

void abrir_arquivo(ofstream &fout, const char str[]) {
    fout.open(str, ios_base::binary | ios_base::out | ios_base::app);
    if (!fout.is_open()) {
        cerr << "Erro ao abrir arquivo\n";
        return;
    }
}

void abrir_arquivo(ifstream &fin, const char str[]) {
    fin.open(str, ios_base::binary | ios_base::in);
    if (!fin.is_open()) {
        cerr << "Erro ao abrir arquivo\n";
        return;
    }
}

void imprimir_cliente_arquivo(ofstream & fout, Cliente &cliente) {
    fout.write(reinterpret_cast<const char *>(&cliente), sizeof(Cliente));
}

bool cliente_existe(Cliente &cliente) {
    ifstream scan("clientes.dat", ios_base::binary | ios_base::in);
    if (!scan.is_open()) {
        cerr << "Erro ao abrir arquivo\n";
        return false;
    }

    if (scan.peek() == EOF) {
        cerr << "Nenhum cliente cadastrado\n";
        return false;
    }

    Cliente cliente_temp;
    while (scan.read(reinterpret_cast<char *>(&cliente_temp), sizeof(Cliente))) {
        if (cliente_temp == cliente) {
            cliente = cliente_temp;
            return true;
        }
    }

    return false;
}

inline void validar_saque(Cliente &cliente, double valor, bool &saque_realizado) {
    if (cliente.saldo >= valor) {
        cliente.saldo -= valor;
        saque_realizado = true;
    }
}

/******************** IMPLEMENTAÇÃO DA INTERFASE PÚBLICA *******************/

void menu() {
    LimparTela();
    cout << "======== Caixa Eletrônico =======\n\n";
    cout << "1) Cadastrar cliente\n";
    cout << "2) Verificar Saldo\n";
    cout << "3) Alterar Senha\n";
    cout << "4) Depósito\n";
    cout << "5) Saque\n";
    cout << "6) Sair\n\n";
    cout << "Sua escolha: ";
}

void cadastrar_cliente() {
    LimparTela();
    cout << "======= Cadastrar cliente =======\n\n";

    Cliente cliente;
    ler_cliente(cliente);

    ofstream print;
    abrir_arquivo(print, "clientes.dat");
    imprimir_cliente_arquivo(print, cliente);

    print.close();
}

void verificar_saldo() {
    LimparTela();
    cout << "======== Verificar Saldo ========\n\n";

    Cliente cliente;
    ler_cliente(cliente);

    ofstream print;
    abrir_arquivo(print, "clientes.dat");

    if (cliente_existe(cliente)) {
        cout.precision(2);
        cout << fixed;
        cout << "Saldo R$" << cliente.saldo << endl;
    } else {
        cout << "Cliente não encontrado.\n";
    }

    Sleep();
}

void deposito() {
    LimparTela();
    cout << "======== Depósito ========\n\n";

    Cliente cliente;
    ler_cliente(cliente);

    cout << "Valor: ";
    double valor;
    cin >> valor;

    while (cin.fail() && valor < 1) {
        cout << "Digite um valor válido: ";
        limpar_buffer();
        cin >> valor;
    }

    ofstream print;
    abrir_arquivo(print, "temp.dat");

    ifstream scan;
    abrir_arquivo(scan, "clientes.dat");

    if (scan.peek() == EOF) {
        cout << "Nenhum cliente cadastrado\n";
        print.close();
        scan.close();
        remove("temp.dat");
        return;
    }

    Cliente cliente_arquivo;
    bool cliente_encontrado = false;

    while (scan.read(reinterpret_cast<char *>(&cliente_arquivo), sizeof(Cliente))) {
        if (cliente_arquivo == cliente) {
            cliente_arquivo.saldo += valor;
            cliente_encontrado = true;
        }

        imprimir_cliente_arquivo(print, cliente_arquivo);
    }

    print.close();
    scan.close();

    if (cliente_encontrado) {
        remove("clientes.dat");
        rename("temp.dat", "clientes.dat");
        cout << "Depósito realizado com sucesso!\n";
    } else {
        remove("temp.dat");
        cout << "O cliente não foi encontrado!\n";
    }

    Sleep();
}

void saque() {
    LimparTela();
    cout << "======== Saque ========\n\n";

    Cliente cliente;
    ler_cliente(cliente);

    cout << "Valor: ";
    double valor;
    cin >> valor;

    while (cin.fail() && valor < 1) {
        cout << "Digite um valor válido: ";
        limpar_buffer();
        cin >> valor;
    }

    ofstream print;
    abrir_arquivo(print, "temp.dat");

    ifstream scan;
    abrir_arquivo(scan, "clientes.dat");

    if (scan.peek() == EOF) {
        cout << "Nenhum cliente cadastrado\n";
        print.close();
        scan.close();
        remove("temp.dat");
        return;
    }

    Cliente cliente_arquivo;
    bool cliente_encontrado = false;
    bool saque_realizado = false;

    while (scan.read(reinterpret_cast<char *>(&cliente_arquivo), sizeof(Cliente))) {
        if (cliente_arquivo == cliente) {
            validar_saque(cliente_arquivo, valor, saque_realizado);
            cliente_encontrado = true;
        }

        imprimir_cliente_arquivo(print, cliente_arquivo);
    }

    print.close();
    scan.close();

    if (cliente_encontrado) {
        if (!saque_realizado) {
            cout << "Saldo insuficiente\n";
            remove("temp.dat");
            Sleep();
            return;
        }

        remove("clientes.dat");
        rename("temp.dat", "clientes.dat");
        cout << "Saque realizado com sucesso!\n";
    } else {
        remove("temp.dat");
        cout << "O cliente não foi encontrado!\n";
    }

    Sleep();
}

void alterar_senha() {
    LimparTela();
    cout << "======== Alterar senha ========\n\n";

    Cliente cliente = {};

    cout << "Número da conta: ";
    cin >> cliente.numero_conta;

    while (cin.fail() && cliente.numero_conta < 1) {
        cout << "Digite um valor válido: ";
        limpar_buffer();
        cin >> cliente.numero_conta;
    }

    cout << "Senha antiga: ";
    cin >> cliente.senha;

    cout << "Senha nova: ";
    string senha;
    cin >> senha;

    ofstream print;
    abrir_arquivo(print, "temp.dat");

    ifstream scan;
    abrir_arquivo(scan, "clientes.dat");

    if (scan.peek() == EOF) {
        cout << "Nenhum cliente cadastrado\n";
        print.close();
        scan.close();
        remove("temp.dat");
        return;
    }

    Cliente cliente_arquivo;
    bool cliente_encontrado = false;

    while (scan.read(reinterpret_cast<char *>(&cliente_arquivo), sizeof(Cliente))) {
        if (cliente_arquivo == cliente) {
            cliente_arquivo.senha = senha;
            cliente_encontrado = true;
        }

        imprimir_cliente_arquivo(print, cliente_arquivo);
    }

    print.close();
    scan.close();

    if (cliente_encontrado) {
        remove("clientes.dat");
        rename("temp.dat", "clientes.dat");
        cout << "A senha foi alterada com sucesso!\n";
    } else {
        remove("temp.dat");
        cout << "O cliente não foi encontrado!\n";
    }

    Sleep();
}
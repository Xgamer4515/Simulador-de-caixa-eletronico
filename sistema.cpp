#include <iostream>
#include "menu.hpp"
using std::cin;

int main() {
#ifdef _WIN32
    ConfigurarAcentuacaoConsole();
#endif

    void (*opcoes[])(void) = { nullptr, cadastrar_cliente, verificar_saldo, alterar_senha, deposito, saque };

    menu();
    int escolha;
    cin >> escolha;
    verificar_escolha(escolha);

    while(escolha != Sair) {
        opcoes[escolha]();

        menu();
        cin >> escolha;
        verificar_escolha(escolha);
    }
}
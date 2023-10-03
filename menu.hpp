// menu.hpp
#pragma once

#include <chrono>
#include <thread>
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

inline void ConfigurarAcentuacaoConsole() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
} 
#endif

inline void LimparTela() {
#ifdef _WIN32
    system("cls");
#else
    systema("clear");
#endif
} 

inline void Sleep() {
    sleep_for(milliseconds(2000));
}

enum { Sair = 6 };

void menu();
void cadastrar_cliente();
void verificar_escolha(int&);
void verificar_saldo();
void deposito();
void saque();
void alterar_senha();
# Simulador de caixa eletrônico

Este é um simples programa de caixa eletrônico em C++ que permite realizar operações bancárias como cadastrar clientes, verificar saldo, alterar senha, fazer depósitos e saques.

## Funcionalidades

- Suporte ao Português: O programa está configurado para exibir mensagens em português.
- Cadastrar Cliente: Permite cadastrar novos clientes com número da conta, senha e saldo inicial.
- Verificar Saldo: Permite aos clientes verificar seus saldos, exigindo o número da conta e a senha.
- Alterar Senha: Oferece a funcionalidade de alterar a senha de um cliente existente, solicitando o número da conta, a senha antiga e a nova senha.
- Depósito: Possibilita realizar depósitos em contas existentes, solicitando o número da conta e o valor a ser depositado.
- Saque: Permite realizar saques de contas existentes, exigindo o número da conta e o valor a ser sacado.
- Sair: Encerra o programa.

## Pré requisitos

- Compilador C++ (por exemplo, GCC ou g++) com suporte ao C++11 ou posterior.
- Sistema operacional: Windows, Unix/Linux, ou macOS

## Compilação e Execução 

1. Abra um terminal ou prompt de comando.
2. Navegue até o diretório onde o código-fonte está localizado.
3. Compile o programa com o seguinte comando:
   ```
   g++ *.cpp -o caixa_eletronico
   ```
4. Execute o programa
   ```
   .\caixa_eletronico.exe
   ```

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests para melhorias, correções de bugs ou adição de novas funcionalidades.

## Licença

Este programa é distribuído sob a [Licença MIT](LICENSE).   

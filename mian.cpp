#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// Função para editar uma linha do vetor
void editarLinha(vector<string>& linhas, int indice, const string& novoConteudo) {
    if (indice >= 0 && indice < (int)linhas.size()) {
        linhas[indice] = novoConteudo;
    } else {
        cout << "Índice inválido!" << endl;
    }
}

// Função para remover uma linha do vetor
void removerLinha(vector<string>& linhas, int indice) {
    if (indice >= 0 && indice < (int)linhas.size()) {
        linhas.erase(linhas.begin() + indice);
    } else {
        cout << "Índice inválido!" << endl;
    }
}

void sistema_de_leitura() {
    vector<string> linhas; // vetor para armazenar tarefas
    string n; // para adicionar elementos

    // 1) Adicionando elementos pelo usuário
    ofstream tarefas("tarefas.txt", ios::app); // abre para adicionar sem apagar
    while (true) {
        cout << "Escreva seu lembrete ou \"parar\" para finalizar: ";
        cin >> n;
        if (n == "parar") break;
        linhas.push_back(n);
        tarefas << n << "\n"; // já salva no arquivo
    }
    tarefas.close();

    // 2) Lendo o arquivo para atualizar o vetor
    ifstream lendo("tarefas.txt");
    string linha;
    linhas.clear(); // limpa para ler o que está no arquivo
    while (getline(lendo, linha)) {
        linhas.push_back(linha);
    }
    lendo.close();

    // 3) Interação para editar ou remover linhas
    string acao;
    while (true) {
        cout << "Deseja remover ou editar algum elemento? (sim/nao): ";
        cin >> acao;
        if (acao == "nao") break;

        if (acao == "sim") {
            int indice;
            cout << "Qual linha deseja alterar? (começa do 0): ";
            cin >> indice;

            cout << "Digite 'remover' para apagar ou 'editar' para modificar: ";
            string escolha;
            cin >> escolha;

            if (escolha == "remover") {
                removerLinha(linhas, indice);
            } else if (escolha == "editar") {
                cin.ignore(); // limpa o buffer do teclado
                string novoTexto;
                cout << "Digite o novo texto: ";
                getline(cin, novoTexto);
                editarLinha(linhas, indice, novoTexto);
            } else {
                cout << "Opção inválida!" << endl;
            }

            // 4) Reescreve o arquivo com as alterações
            ofstream saida("tarefas.txt", ios::trunc);
            for (const auto& l : linhas) {
                saida << l << "\n";
            }
            saida.close();
        }
    }
}

int main() {
    sistema_de_leitura();
    return 0;
}

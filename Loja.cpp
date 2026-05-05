#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct Produto {
    int id;
    int quantidade;
    string nome;
    double preco;
    bool excluido;
};

Produto produtos[1000000];
int contagem = 0;

void Menu() {
    cout << "\033[36m+----------------------------------------+\033[0m" << endl;
    cout << "\033[36m|              MENU PRINCIPAL            |\033[0m" << endl;
    cout << "\033[36m+----------------------------------------+\033[0m" << endl;
    cout << "\033[36m|\033[0m 1. Cadastrar instrumentos no estoque   \033[36m|\033[0m" << endl;
    cout << "\033[36m|\033[0m 2. Listar todos os instrumentos        \033[36m|\033[0m" << endl;
    cout << "\033[36m|\033[0m 3. Atualizar informacoes de um item    \033[36m|\033[0m" << endl;
    cout << "\033[36m|\033[0m 4. Remover um instrumento do estoque   \033[36m|\033[0m" << endl;
    cout << "\033[36m|\033[0m 5. Simular uma venda                   \033[36m|\033[0m" << endl;
    cout << "\033[36m|\033[0m 6. Salvar dados no arquivo             \033[36m|\033[0m" << endl;
    cout << "\033[36m|\033[0m 7. Mostrar equipe                      \033[36m|\033[0m" << endl;
    cout << "\033[36m|\033[0m 0. Sair                                \033[36m|\033[0m" << endl;
    cout << "\033[36m+----------------------------------------+\033[0m" << endl;
}

void Cadastrar() {
    int opcao = 1;
    while (opcao == 1) {
        cin.ignore();
        cout << "\033[36m\nNome: \033[0m";
        getline(cin, produtos[contagem].nome);

        cout << "\033[36m\nId: \033[0m";
        cin >> produtos[contagem].id;

        cout << "\033[36m\nQuantidade: \033[0m";
        cin >> produtos[contagem].quantidade;

        cout << "\033[36m\nPreco: \033[0m";
        cin >> produtos[contagem].preco;

        produtos[contagem].excluido = false;
        contagem++;

        cout << "\n";
        cout << "\033[33mInstrumento cadastrado com sucesso!\n\033[0m";
        cout << "\033[36m----------------------------------------\n\033[0m";
        cout << "\033[36mDeseja cadastrar outro instrumento? (\033[32m1: Sim\033[36m, \033[31m2: Nao\033[36m): \033[0m";
        cin >> opcao;
    }
    cout << "\033[34m----------------------------------------\n\033[0m";
}

void Listar() {
    cout << "-------------- Instrumentos -------------\n";
    for (int i = 0; i < contagem; i++) {
        if (!produtos[i].excluido) {
            cout << "id: " << produtos[i].id << endl;
            cout << "nome: " << produtos[i].nome << endl;
            cout << "quantidade: " << produtos[i].quantidade << endl;
            cout << "preco: R$ " << fixed << setprecision(2) << produtos[i].preco << endl;
            cout << "+----------------------------------------+\n";
        }
    }
}

void Atualizar() {
    int buscaId;
    cout << "Digite o ID do instrumento que deseja atualizar: ";
    cin >> buscaId;

    for (int i = 0; i < contagem; i++) {
        if (produtos[i].id == buscaId && !produtos[i].excluido) {
            cin.ignore();
            cout << "Novo nome: ";
            getline(cin, produtos[i].nome);
            cout << "Nova quantidade: ";
            cin >> produtos[i].quantidade;
            cout << "Novo preco: ";
            cin >> produtos[i].preco;
            cout << "\033[33mInstrumento atualizado com sucesso!\033[0m\n";
            cout << "----------------------------------------\n\n";
            return;
        }
    }

    cout << "Instrumento com ID " << buscaId << " não encontrado.\n";
    cout << "----------------------------------------\n\n";
}

void Remover() {
    int buscaId, opcao;
    cout << "Digite o ID do instrumento que deseja remover: ";
    cin >> buscaId;
    cout << "\n";

    for (int i = 0; i < contagem; i++) {
        if (produtos[i].id == buscaId && !produtos[i].excluido) {
            cout << "Deseja:\n1. Remover o produto inteiro\n2. Remover parte da quantidade\n";
            cin >> opcao;
            cout << "\n";

            if (opcao == 1) {
                produtos[i].excluido = true;
                cout << "\033[33mProduto removido com sucesso.\033[0m\n";
            } else if (opcao == 2) {
                int qtd;
                cout << "Digite a quantidade a ser removida: ";
                cin >> qtd;
                if (qtd > 0 && qtd <= produtos[i].quantidade) {
                    produtos[i].quantidade -= qtd;
                    cout << "\033[33mQuantidade removida com sucesso.\033[0m\n";
                } else {
                    cout << "\033[31mQuantidade inválida.\033[0m\n";
                }
            } else {
                cout << "\033[31mOpção inválida.\033[0m\n";
            }
            return;
        }
    }

    cout << "Produto não encontrado.\n";
    cout << "----------------------------------------\n\n";
}

void SimularVenda() {
    int buscaId;
    cout << "Digite o ID do produto que deseja vender: ";
    cin >> buscaId;

    for (int i = 0; i < contagem; i++) {
        if (produtos[i].id == buscaId && !produtos[i].excluido) {
            int quantidadeVenda;
            cout << "Quantidade a vender: ";
            cin >> quantidadeVenda;

            if (quantidadeVenda <= 0) {
                cout << "Quantidade invalida.\n";
                return;
            }

            if (quantidadeVenda > produtos[i].quantidade) {
                cout << "Quantidade insuficiente em estoque.\n";
                return;
            }

            produtos[i].quantidade -= quantidadeVenda;
            double total = quantidadeVenda * produtos[i].preco;
            cout << "\033[33mVenda realizada com sucesso!\033[0m\n";
            cout << "Valor total: R$ " << fixed << setprecision(2) << total << endl;
            cout << "Quantidade restante em estoque: " << produtos[i].quantidade << endl;
            cout << "----------------------------------------\n\n";
            return;
        }
    }
    cout << "Produto nao encontrado.\n";
    cout << "----------------------------------------\n\n";
}

void Salvar() {
    ofstream arquivo("Loja.txt");

    for (int i = 0; i < contagem; i++) {
        if (!produtos[i].excluido) {
            arquivo << "id: " << produtos[i].id << "\n";
            arquivo << "nome: " << produtos[i].nome << "\n";
            arquivo << "quantidade: " << produtos[i].quantidade << "\n";
            arquivo << "preco: " << fixed << setprecision(2) << produtos[i].preco << "\n";
            arquivo << "-----------------------------------\n";
        }
    }

    arquivo.close();
    cout << "\033[33mDados salvos com sucesso!\033[0m\n";
    cout << "----------------------------------------\n\n";
}

int strToInt(const string& s) {
    string trimmed = s;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

    int num = 0;
    bool negativo = false;
    int i = 0;

    if (trimmed.empty()) return 0;

    if (trimmed[0] == '-') {
        negativo = true;
        i = 1;
    }

    for (; i < (int)trimmed.size(); i++) {
        if (trimmed[i] < '0' || trimmed[i] > '9')
            break;
        num = num * 10 + (trimmed[i] - '0');
    }

    return negativo ? -num : num;
}

double strToDouble(const string& s) {
    string trimmed = s;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

    double num = 0.0, frac = 0.0;
    bool negativo = false, decimal = false;
    double divisor = 10.0;
    int i = 0;

    if (trimmed.empty()) return 0.0;

    if (trimmed[0] == '-') {
        negativo = true;
        i = 1;
    }

    for (; i < (int)trimmed.size(); i++) {
        if (trimmed[i] == '.') {
            decimal = true;
            continue;
        }

        if (trimmed[i] < '0' || trimmed[i] > '9')
            break;

        if (!decimal) {
            num = num * 10 + (trimmed[i] - '0');
        } else {
            frac += (trimmed[i] - '0') / divisor;
            divisor *= 10;
        }
    }

    num += frac;
    return negativo ? -num : num;
}

void CarregarDoArquivo() {
    ifstream arquivo("Loja.txt");
    string linha;
    Produto temp;

    while (getline(arquivo, linha)) {
        if (linha.rfind("id:", 0) == 0) {
            temp.id = strToInt(linha.substr(linha.find(":") + 1));
        } else {
            continue;
        }

        if (!getline(arquivo, linha) || linha.rfind("nome:", 0) != 0)
            continue;
        temp.nome = linha.substr(linha.find(":") + 1);

        if (!getline(arquivo, linha) || linha.rfind("quantidade:", 0) != 0)
            continue;
        temp.quantidade = strToInt(linha.substr(linha.find(":") + 1));

        if (!getline(arquivo, linha) || linha.rfind("preco:", 0) != 0)
            continue;
        temp.preco = strToDouble(linha.substr(linha.find(":") + 1));

        getline(arquivo, linha); // linha separadora
        temp.excluido = false;
        produtos[contagem++] = temp;
    }

    arquivo.close();
}

void Equipe() {
    cout << "Enzo Dias Venancio Guimaraes Nunes - 2328\n";
    cout << "Joao Pedro Ramos Garcia - 820\n";
    cout << "Lucas Alberto Silva e Barros - 2293\n";
    cout << "Marcus Vinicius Duarte - 2296\n\n";
    cout << "----------------------------------------\n\n";
}

int main() {
    CarregarDoArquivo();

    int opcao;
    while (true) {
        Menu();
        cin >> opcao;
        cout << endl;

        if (opcao == 1) Cadastrar();
        else if (opcao == 2) Listar();
        else if (opcao == 3) Atualizar();
        else if (opcao == 4) Remover();
        else if (opcao == 5) SimularVenda();
        else if (opcao == 6) Salvar();
        else if (opcao == 7) Equipe();
        else if (opcao == 0) break;
        else cout << "Opção inválida.\n";
    }

    Salvar();
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;


struct Alunos {
    int matricula;
    string nome;
    int idade;
    string turma;
    Alunos *proximo;
};

// INICIO DA LISTA
Alunos *listaAlunos = NULL;


// BUSCAR ALUNO PELA MATRICULA
Alunos* buscarAluno(int matricula) {

    Alunos *atual = listaAlunos;

    while (atual != NULL) {

        if (atual->matricula == matricula) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}


// EXIBIR DADOS DO ALUNO
void exibirDadosAluno(Alunos *aluno) {

    cout << "\nMatricula: " << aluno->matricula << endl;
    cout << "Nome: " << aluno->nome << endl;
    cout << "Idade: " << aluno->idade << endl;
    cout << "Turma: " << aluno->turma << endl;
}


// CADASTRAR ALUNO
void cadastrarAluno() {

    Alunos *novo = new Alunos;

    cout << "\n=== CADASTRAR ALUNO ===" << endl;

    cout << "Matricula: ";
    cin >> novo->matricula;

    if (buscarAluno(novo->matricula) != NULL) {
        cout << "Matricula ja cadastrada!" << endl;
        delete novo;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nome: ";
    getline(cin, novo->nome);

    cout << "Idade: ";
    cin >> novo->idade;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Turma: ";
    getline(cin, novo->turma);

    novo->proximo = NULL;

    // INSERIR NO FINAL DA LISTA

    if (listaAlunos == NULL) {

        listaAlunos = novo;

    } else {

        Alunos *atual = listaAlunos;

        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }

        atual->proximo = novo;
    }

    cout << "\nAluno cadastrado com sucesso!" << endl;
}


// CONSULTAR ALUNO
void consultarAluno() {

    cout << "\n=== CONSULTAR ALUNO ===" << endl;

    int matricula;

    cout << "Matricula: ";
    cin >> matricula;

    Alunos *aluno = buscarAluno(matricula);

    if (aluno == NULL) {
        cout << "Aluno nao encontrado!" << endl;
        return;
    }

    exibirDadosAluno(aluno);
}


// LISTAR TODOS OS ALUNOS
void listarAlunos() {

    cout << "\n=== ALUNOS CADASTRADOS ===" << endl;

    if (listaAlunos == NULL) {
        cout << "Nenhum aluno cadastrado." << endl;
        return;
    }

    Alunos *atual = listaAlunos;

    int total = 0;

    while (atual != NULL) {

        cout << "\n------------------------" << endl;

        exibirDadosAluno(atual);

        atual = atual->proximo;
        total++;
    }

    cout << "\nTotal de alunos: " << total << endl;
}

// EXPORTAR ALUNOS PARA ARQUIVO TXT
void exportarAlunos() {

    cout << "\n=== EXPORTAR ALUNOS ===" << endl;

    if (listaAlunos == NULL) {
        cout << "Nenhum aluno cadastrado para exportar!" << endl;
        return;
    }

    ofstream arquivo("alunos.txt");

    if (!arquivo.is_open()) {
        cout << "Erro ao criar o arquivo!" << endl;
        return;
    }

    Alunos *atual = listaAlunos;
    
    arquivo << "       LISTA DE ALUNOS" << endl;
   
    while (atual != NULL) {

        arquivo << "\nMatricula: " << atual->matricula << endl;
        arquivo << "Nome: " << atual->nome << endl;
        arquivo << "Idade: " << atual->idade << endl;
        arquivo << "Turma: " << atual->turma << endl;

        arquivo << "-----------------------------------" << endl;

        atual = atual->proximo;
    }

    arquivo.close();

    cout << "Alunos exportados com sucesso!" << endl;
    cout << "Arquivo criado: alunos.txt" << endl;
}


// EXPORTAR ALUNOS PARA ARQUIVO BINARIO
void exportarAlunosBinario() {

    cout << "\n=== EXPORTAR ALUNOS (BINARIO) ===" << endl;

    if (listaAlunos == NULL) {
        cout << "Nenhum aluno cadastrado para exportar!" << endl;
        return;
    }

    ofstream arquivo("alunos.bin", ios::binary);

    if (!arquivo.is_open()) {
        cout << "Erro ao criar o arquivo!" << endl;
        return;
    }

    Alunos *atual = listaAlunos;

    while (atual != NULL) {

        // matricula
        arquivo.write((char*)&atual->matricula, sizeof(int));

        // nome (tamanho + texto)
        int tamNome = atual->nome.size();
        arquivo.write((char*)&tamNome, sizeof(int));
        arquivo.write(atual->nome.c_str(), tamNome);

        // idade
        arquivo.write((char*)&atual->idade, sizeof(int));

        // turma (tamanho + texto)
        int tamTurma = atual->turma.size();
        arquivo.write((char*)&tamTurma, sizeof(int));
        arquivo.write(atual->turma.c_str(), tamTurma);

        atual = atual->proximo;
    }

    arquivo.close();

    cout << "Alunos exportados com sucesso!" << endl;
    cout << "Arquivo criado: alunos.bin" << endl;
}


// EXIBIR MENU
void exibirMenu() {

    cout << "\n===================================" << endl;
    cout << "       SISTEMA DE GESTAO" << endl;
    cout << "===================================" << endl;

    cout << "1 - Cadastrar aluno" << endl;
    cout << "2 - Consultar aluno" << endl;
    cout << "3 - Listar todos os alunos" << endl;
    cout << "4 - Exportar alunos para TXT" << endl;
    cout << "5 - Exportar alunos para BIN"<< endl;
    cout << "0 - Sair" << endl;

    cout << "===================================" << endl;
}




// PROGRAMA PRINCIPAL
int main() {

    int opcao;

    do {

        exibirMenu();

        cout << "Escolha uma opcao: ";
        cin >> opcao;
        
        system("cls");

        switch (opcao) {

            case 1:
                cadastrarAluno();
                system("cls");
                break;

            case 2:
                consultarAluno();
                break;

            case 3:
                listarAlunos();
                break;
                
            case 4:
                exportarAlunos();
                break;
                
            case 5:
                exportarAlunosBinario();
                break;

            case 0:
                cout << "\nEncerrando o sistema..." << endl;
                break;

            default:
                cout << "\nOpcao invalida!" << endl;
        }


    } while (opcao != 0);

    return 0;
}
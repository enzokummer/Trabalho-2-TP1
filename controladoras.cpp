#include "controladoras.h"
#include "dominios.h"
#include "entidades.h"
#include "comandos.h"
#include "sqlite3.h"

using namespace std;

// AUTENTICACAO

bool CntrIAAutenticacao::autenticar(CPF *cpf) {
    string logIn = "********* Bem-vindo de volta! *********";
    string pedeCPF = "CPF:";
    string pedeSenha = "Senha:";
    string deuErro = "Formato inserido está incorreto. Por favor, tente novamente! (Digite qualquer botão)";

    string campo1, campo2;

    Senha senha;

    while(true) {
        CLR_SCR; // LIMPA A TELA
        cout << logIn << endl;
        cout << pedeCPF << " ";
        cin >> campo1;
        cout << pedeSenha << " ";
        cin >> campo2;

        try {
            cpf->setValor(campo1);
            senha.setValor(campo2);
            break;
        } catch (invalid_argument &exp) {
            CLR_SCR;
            cout << deuErro << endl;
            getchar();
        }
    }
    return (cntrISAutenticacao->autenticar(*cpf, senha));
}

bool CntrISAutenticacao::autenticar(const CPF& cpf, const Senha& senha){
    sqlite3* db;
    int rc = sqlite_open("database.db", &db);
    if(rc){
        cerr<<"Erro na comunicação com o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    string senhaReal;
    string numCpf = cpf.getValor();

    if(readSenha(db,numCpf,senhaReal)){
        return (senhaReal == senha.getValor());
    }
}
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

//Serviço Investimentos - Títulos --------------

bool ControladoraServicoTitulos::criar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    createTitulo(db, titulo.getcodigo().getValor(), titulo.getemissor().getValor(), titulo.getsetor().getValor(), titulo.getemissao().getValor(), titulo.getvencimento().getValor(), titulo.getvalor().getValor(), "cpfprovisorio"); //consertar isso
    endConnection(db);
};

bool ControladoraServicoTitulos::recuperar(Titulo* titulo) {
    sqlite3* db = startConnection("database.db");
    readTitulo(db, titulo->getcodigo().getValor());
    endConnection(db);
};

bool ControladoraServicoTitulos::atualizar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    updateTitulo(db, titulo.getcodigo().getValor(), titulo.getemissor().getValor(), titulo.getsetor().getValor(), titulo.getemissao().getValor(), titulo.getvencimento().getValor(), titulo.getvalor().getValor());
    endConnection(db);
};

bool ControladoraServicoTitulos::excluir(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    deleteTitulo(db, titulo.getcodigo().getValor());
    endConnection(db);
};

bool ControladoraServicoTitulos::listar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    
    endConnection(db);
};

//Serviço Investimentos - Pagamentos --------------

bool ControladoraServicoPagamentos::criar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    createPagamento(db, stoi(pagamento.getcodigo().getValor()), pagamento.getdata().getValor(), stoi(pagamento.getpercentual().getValor()), pagamento.getestado().getValor(), "Codigo temporario"); //corrigir isso
    endConnection(db);
};

bool ControladoraServicoPagamentos::recuperar(Pagamento* pagamento) {
    sqlite3* db = startConnection("database.db");
    readPagamento(db, stoi(pagamento->getcodigo().getValor()));
    endConnection(db);
};

bool ControladoraServicoPagamentos::atualizar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    updatePagamento(db, stoi(pagamento.getcodigo().getValor()), pagamento.getdata().getValor(), stoi(pagamento.getpercentual().getValor()), pagamento.getestado().getValor());
    endConnection(db);
};

bool ControladoraServicoPagamentos::excluir(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    deletePagamento(db, stoi(pagamento.getcodigo().getValor()));
    endConnection(db);
};

bool ControladoraServicoPagamentos::listar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    
    endConnection(db);
};
#include <iostream>
#include "dominios.h"
#include "entidades.h"
#include "testes.h"
#include "comandos.h"

using namespace std;

int main(){
 try {
        sqlite3* db = startConnection("database.db");
        createTbAcc(db);
        createTablebTtl(db);
        createTablePaym(db);

        if (createConta(db, "12345678901", "Fulano silva", "123456")) {
            cout << "Sucesso - Criar Conta" << endl;
        } else {
            cout << "Falha - Criar Conta" << endl;
        }

        vector<string> conta;
        if (readConta(db, "12345678901", conta)) {
            cout << "Sucesso - Ler Conta: " << conta[1] << endl;
        } else {
            cout << "Falha - Ler Conta" << endl;
        }

        if (updateConta(db, "12345678901", "Novo Nome", "654321")) {
            cout << "Sucesso - Atualizar Conta" << endl;
        } else {
            cout << "Falha - Atualizar Conta" << endl;
        }

        if (deleteConta(db, "12345678901")) {
            cout << "Sucesso - Excluir Conta" << endl;
        } else {
            cout << "Falha - Excluir Conta" << endl;
        }

        endConnection(db);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    cout << endl << "TESTES DOS DOMINIOS" << endl;

    TUCodPagamento testeA;

    if(testeA.run() == true) {
        cout << "Sucesso - Codigo de Pagamento" << endl;
    }else {
        cout << "Falha - Codigo de Pagamento" << endl;
    }

    TUCodTitulo testeB;

    if(testeB.run() == true) {
        cout << "Sucesso - Codigo de Titulo" << endl;
    }else {
        cout << "Falha - Codigo de Titulo" << endl;
    }

    TUCPF testeC;

    if(testeC.run() == true) {
        cout << "Sucesso - CPF" << endl;
    }else {
        cout << "Falha - CPF" << endl;
    }

    TUData testeD;

    if(testeD.run() == true) {
        cout << "Sucesso - Data" << endl;
    }else {
        cout << "Falha - Data" << endl;
    }

    TUDinheiro testeE;

    if(testeE.run() == true) {
        cout << "Sucesso - Dinheiro" << endl;
    }else {
        cout << "Falha - Dinheiro" << endl;
    }

    TUEstado testeF;

    if(testeF.run() == true) {
        cout << "Sucesso - Estado" << endl;
    }else {
        cout << "Falha - Estado" << endl;
    }

    TUNome testeG;

    if(testeG.run() == true) {
        cout << "Sucesso - Nome" << endl;
    }else {
        cout << "Falha - Nome" << endl;
    }

    TUPercentual testeH;

    if(testeH.run() == true) {
        cout << "Sucesso - Percentual" << endl;
    }else {
        cout << "Falha - Percentual" << endl;
    }

    TUSenha testeI;

    if(testeI.run() == true) {
        cout << "Sucesso - Senha" << endl;
    }else {
        cout << "Falha - Senha" << endl;
    }

    TUSetor testeJ;

    if(testeJ.run() == true) {
        cout << "Sucesso - Setor" << endl;
    }else {
        cout << "Falha - Setor" << endl;
    }

    cout << endl << "TESTES DAS ENTIDADES" << endl;

    TUConta testeK;

    if(testeK.run() == true) {
        cout << "Sucesso - Conta" << endl;
    }else {
        cout << "Falha - Conta" << endl;
    }

    TUTitulo testeL;

    if(testeL.run() == true) {
        cout << "Sucesso - Titulo" << endl;
    }else {
        cout << "Falha - Titulo" << endl;
    }

    TUPagamento testeM;

    if(testeM.run() == true) {
        cout << "Sucesso - Pagamento" << endl;
    }else {
        cout << "Falha - Pagamento" << endl;
    }

    return 0;
}

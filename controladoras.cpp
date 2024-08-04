#include "controladoras.h"
#include "comandos.h"

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

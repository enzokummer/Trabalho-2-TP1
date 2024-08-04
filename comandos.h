#ifndef COMANDOS_H
#define COMANDOS_H

#include "./includes/sqlite3.h"
#include <string>
#include "dominios.h"
#include "entidades.h"

sqlite3* startConnection(const std::string& dbFile);
void endConnection(sqlite3* db);

// Criar tabelas
void createTbAcc(sqlite3* db);
void createTablebTtl(sqlite3* db);
void createTablePaym(sqlite3* db);

class ContaSQL {
private:
    sqlite3* db;
public:
    ContaSQL(sqlite3* db) : db(db) {}

    bool create(const Conta& conta);
    bool read(const std::string& cpf, Conta& conta);
    bool update(const Conta& conta);
    bool deleteConta(const std::string& cpf);
};

class TituloSQL {
private:
    sqlite3* db;
public:
    TituloSQL(sqlite3* db) : db(db) {}

    bool create(const Titulo& titulo);
    bool read(const std::string& codigo, Titulo& titulo);
    bool update(const Titulo& titulo);
    bool deleteTitulo(const std::string& codigo);
};

class PagamentoSQL {
private:
    sqlite3* db;
public:
    PagamentoSQL(sqlite3* db) : db(db) {}

    bool create(const Pagamento& pagamento);
    bool read(int codigo, Pagamento& pagamento);
    bool update(const Pagamento& pagamento);
    bool deletePagamento(int codigo);
};

#endif 

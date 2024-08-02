#include "comandos.h"
#include <iostream>

sqlite3* startConnection(const std::string& filename) {
    sqlite3* db;
    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc) {
        throw std::runtime_error("Erro ao conectar: " + std::string(sqlite3_errmsg(db)));
    }
    return db;
}

void endConnection(sqlite3* db) {
    if (sqlite3_close(db) != SQLITE_OK) {
        throw std::runtime_error("Erro ao encerrar a conexão:  " + std::string(sqlite3_errmsg(db)));
    }
}

void createTbAcc(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS Conta ("
                      "CPF VARCHAR(11) PRIMARY KEY, "
                      "Nome VARCHAR(50) NOT NULL, "
                      "Senha VARCHAR(20) NOT NULL);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        throw std::runtime_error("Erro ao criar tabela 'Conta': " + std::string(errMsg));
    }
}

void createTablebTtl(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS Titulo ("
                      "Codigo INT PRIMARY KEY, "
                      "Emissor VARCHAR(50) NOT NULL, "
                      "Setor VARCHAR(50) NOT NULL, "
                      "Emissao DATE NOT NULL, "
                      "Vencimento DATE NOT NULL, "
                      "Valor VARCHAR(100) NOT NULL, "
                      "CPF_Conta VARCHAR(11) NOT NULL, "
                      "FOREIGN KEY (CPF_Conta) REFERENCES Conta(CPF));";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        throw std::runtime_error("Erro ao criar tabela 'Titulo': " + std::string(errMsg));
    }
}

void createTablePaym(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS Pagamento ("
                      "Codigo INT PRIMARY KEY, "
                      "Data DATE NOT NULL, "
                      "Percentual INT NOT NULL, "
                      "Estado VARCHAR(50) NOT NULL, "
                      "Codigo_Titulo INT NOT NULL, "
                      "FOREIGN KEY (Codigo_Titulo) REFERENCES Titulo(Codigo));";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        throw std::runtime_error("Erro ao criar tabela 'Pagamento': " + std::string(errMsg));
    }
}

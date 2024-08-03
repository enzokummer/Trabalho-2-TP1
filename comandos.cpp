#include "comandos.h"
#include <iostream>

sqlite3* startConnection(const std::string& dbFile) {
    sqlite3* db;
    int rc = sqlite3_open(dbFile.c_str(), &db);
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

bool createConta(sqlite3* db, const std::string& cpf, const std::string& nome, const std::string& senha) {
    std::string sql = "INSERT INTO Conta (CPF, Nome, Senha) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, cpf.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nome.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, senha.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool readConta(sqlite3* db, const std::string& cpf, std::vector<std::string>& conta) {
    std::string sql = "SELECT * FROM Conta WHERE CPF = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, cpf.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        conta.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        conta.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        conta.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    } else {
        std::cerr << "Conta not found" << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool updateConta(sqlite3* db, const std::string& cpf, const std::string& nome, const std::string& senha) {
    std::string sql = "UPDATE Conta SET Nome = ?, Senha = ? WHERE CPF = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, senha.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, cpf.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool deleteConta(sqlite3* db, const std::string& cpf) {
    std::string sql = "DELETE FROM Conta WHERE CPF = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, cpf.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}
#include "comandos.h"
#include <iostream>

// Conexão e desconexão com o sqlite

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

// Criar as tabelas

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

// CRUD conta

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

bool readSenha(sqlite3* db, const std::string& cpf, std::string& senha) {
    std::string sql = "SELECT senha FROM Conta WHERE CPF = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, cpf.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        senha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
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

//CRUD titulo

bool createTitulo(sqlite3* db, int codigo, const std::string& emissor, 
    const std::string& setor, const std::string& emissao, 
    const std::string& vencimento, const std::string& valor, 
    const std::string& cpfConta) {
    std::string sql = "INSERT INTO Titulo (Codigo, Emissor, Setor, Emissao, Vencimento, Valor, CPF_Conta) VALUES (?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt, 1, codigo);
    sqlite3_bind_text(stmt, 2, emissor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, setor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, emissao.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, vencimento.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, valor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, cpfConta.c_str(), -1, SQLITE_STATIC);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool readTitulo(sqlite3* db, int codigo, std::vector<std::string>& result) {
    std::string sql = "SELECT * FROM Titulo WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt, 1, codigo);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result.push_back(std::to_string(sqlite3_column_int(stmt, 0)));
        result.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))); // Emissor
        result.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))); // Setor
        result.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))); // Emissao
        result.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))); // Vencimento
        result.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))); // Valor
        result.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))); // CPF_Conta
        sqlite3_finalize(stmt);
        return true;
    } else {
        sqlite3_finalize(stmt);
        return false;
    }
}

bool updateTitulo(sqlite3* db, int codigo, const std::string& emissor, 
    const std::string& setor, const std::string& emissao, 
    const std::string& vencimento, const std::string& valor) {
    std::string sql = "UPDATE Titulo SET Emissor = ?, Setor = ?, Emissao = ?, Vencimento = ?, Valor = ? WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt, 1, emissor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, setor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, emissao.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, vencimento.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, valor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, codigo);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool deleteTitulo(sqlite3* db, int codigo) {
    std::string sql = "DELETE FROM Titulo WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt, 1, codigo);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

//CRUD pagamento

bool createPagamento(sqlite3* db, int codigo, const std::string& data, int percentual, const std::string& estado, int codigoTitulo) {
    std::string sql = "INSERT INTO Pagamento (Codigo, Data, Percentual, Estado, Codigo_Titulo) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, codigo);
    sqlite3_bind_text(stmt, 2, data.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, percentual);
    sqlite3_bind_text(stmt, 4, estado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, codigoTitulo);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool readPagamento(sqlite3* db, int codigo, std::vector<std::string>& pagamentoData) {
    std::string sql = "SELECT * FROM Pagamento WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, codigo);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        pagamentoData.push_back(std::to_string(sqlite3_column_int(stmt, 0)));
        pagamentoData.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        pagamentoData.push_back(std::to_string(sqlite3_column_int(stmt, 2)));
        pagamentoData.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        pagamentoData.push_back(std::to_string(sqlite3_column_int(stmt, 4)));
    } else {
        std::cerr << "Não existe um pagamento com esse codigo: " << codigo << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool updatePagamento(sqlite3* db, int codigo, const std::string& data, int percentual, const std::string& estado) {
    std::string sql = "UPDATE Pagamento SET Data = ?, Percentual = ?, Estado = ? WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, data.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, percentual);
    sqlite3_bind_text(stmt, 3, estado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, codigo);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool deletePagamento(sqlite3* db, int codigo) {
    std::string sql = "DELETE FROM Pagamento WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, codigo);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}
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
                      "Codigo_Titulo VARCHAR(20) NOT NULL, "
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
        std::cerr << "Conta nao encontrada" << std::endl;
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

bool createTitulo(sqlite3* db, const std::string& codigo, const std::string& emissor, const std::string& setor, const std::string& emissao, const std::string& vencimento, const std::string& valor, const std::string& cpfConta) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Titulo (Codigo, Emissor, Setor, Emissao, Vencimento, Valor, CPF_Conta) VALUES (?, ?, ?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar a declaração: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, emissor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, setor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, emissao.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, vencimento.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, valor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, cpfConta.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao criar título: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool readTitulo(sqlite3* db, const std::string& codigo) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM Titulo WHERE Codigo = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar a declaração: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::cout << "Código: " << sqlite3_column_text(stmt, 0) << std::endl;
        std::cout << "Emissor: " << sqlite3_column_text(stmt, 1) << std::endl;
        std::cout << "Setor: " << sqlite3_column_text(stmt, 2) << std::endl;
        std::cout << "Emissão: " << sqlite3_column_text(stmt, 3) << std::endl;
        std::cout << "Vencimento: " << sqlite3_column_text(stmt, 4) << std::endl;
        std::cout << "Valor: " << sqlite3_column_text(stmt, 5) << std::endl;
        std::cout << "CPF Conta: " << sqlite3_column_text(stmt, 6) << std::endl;
    } else {
        std::cerr << "Título não encontrado." << std::endl;
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_ROW;
}

bool updateTitulo(sqlite3* db, const std::string& codigo, const std::string& emissor, const std::string& setor, const std::string& emissao, const std::string& vencimento, const std::string& valor) {
    sqlite3_stmt* stmt;
    const char* sql = "UPDATE Titulo SET Emissor = ?, Setor = ?, Emissao = ?, Vencimento = ?, Valor = ? WHERE Codigo = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar a declaração: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, emissor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, setor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, emissao.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, vencimento.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, valor.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, codigo.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao atualizar título: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool deleteTitulo(sqlite3* db, const std::string& codigo) {

    std::string sqlCheck = "SELECT COUNT(*) FROM Pagamento WHERE Codigo_Titulo = ?;";
    sqlite3_stmt* stmtCheck;
    if (sqlite3_prepare_v2(db, sqlCheck.c_str(), -1, &stmtCheck, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmtCheck, 1, codigo.c_str(), -1, SQLITE_STATIC);
    int step = sqlite3_step(stmtCheck);
    int count = sqlite3_column_int(stmtCheck, 0);
    sqlite3_finalize(stmtCheck);

    if (count > 0) {
        return false;
    }

    std::string sql = "DELETE FROM Titulo WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

//CRUD pagamento

bool createPagamento(sqlite3* db, int codigo, const std::string& data, int percentual, const std::string& estado, const std::string& codigoTitulo) {
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
    sqlite3_bind_text(stmt, 5, codigoTitulo.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool readPagamento(sqlite3* db, int codigo) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT * FROM Pagamento WHERE Codigo = ?";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, codigo);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "Codigo: " << sqlite3_column_int(stmt, 0) << std::endl; 
            std::cout << "Data: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)) << std::endl; 
            std::cout << "Percentual: " << sqlite3_column_int(stmt, 2) << std::endl; 
            std::cout << "Estado: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)) << std::endl; 
            std::cout << "Codigo Titulo: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)) << std::endl; 
            sqlite3_finalize(stmt);
            return true;
        }

        sqlite3_finalize(stmt);
    }

    return false;
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
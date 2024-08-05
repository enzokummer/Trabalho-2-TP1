#include "comandos.h"
#include <stdexcept>
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
                      "CPF VARCHAR(14) PRIMARY KEY, " 
                      "Nome VARCHAR(50) NOT NULL, "
                      "Senha VARCHAR(20) NOT NULL);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        throw std::runtime_error("Erro ao criar tabela 'Conta': " + std::string(errMsg));
    }
}

void createTablebTtl(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS Titulo ("
                      "Codigo VARCHAR(20) PRIMARY KEY, "
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

bool ContaSQL::create(const Conta& conta) {
    std::string sql = "INSERT INTO Conta (CPF, Nome, Senha) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, conta.getcpf().getValor().c_str(), -1, SQLITE_STATIC);  // CPF com pontos e traço
    sqlite3_bind_text(stmt, 2, conta.getnome().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, conta.getsenha().getValor().c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool ContaSQL::read(const std::string& cpf, Conta& conta) {
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
        CPF cpfObj;
        cpfObj.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        conta.setcpf(cpfObj);

        Nome nome;
        nome.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        conta.setnome(nome);

        Senha senha;
        senha.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        conta.setsenha(senha);
        sqlite3_finalize(stmt);
        return true;
    }

    std::cerr << "Conta não encontrada" << std::endl;
    sqlite3_finalize(stmt);
    return false;
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

bool ContaSQL::update(const Conta& conta) {
    std::string sql = "UPDATE Conta SET Nome = ?, Senha = ? WHERE CPF = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, conta.getnome().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, conta.getsenha().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, conta.getcpf().getValor().c_str(), -1, SQLITE_STATIC);  // CPF com pontos e traço

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool ContaSQL::deleteConta(const std::string& cpf) {
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

bool TituloSQL::create(const Titulo& titulo) {
    std::string sql = "INSERT INTO Titulo (Codigo, Emissor, Setor, Emissao, Vencimento, Valor, CPF_Conta) VALUES (?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, titulo.getcodigo().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, titulo.getemissor().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, titulo.getsetor().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, titulo.getemissao().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, titulo.getvencimento().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, titulo.getvalor().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, titulo.getcpfConta().getValor().c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool TituloSQL::read(const std::string& codigo, Titulo& titulo) {
    std::string sql = "SELECT * FROM Titulo WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        CodTitulo codTitulo;
        codTitulo.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        titulo.setcodigo(codTitulo);

        Nome emissor;
        emissor.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        titulo.setemissor(emissor);

        Setor setor;
        setor.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        titulo.setsetor(setor);

        Data emissao;
        emissao.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        titulo.setemissao(emissao);

        Data vencimento;
        vencimento.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        titulo.setvencimento(vencimento);

        Dinheiro valor;
        valor.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        titulo.setvalor(valor);

        CPF cpfConta;
        cpfConta.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        titulo.setcpfConta(cpfConta);
    } else {
        std::cerr << "Título não encontrado." << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool TituloSQL::update(const Titulo& titulo) {
    std::string sql = "UPDATE Titulo SET Emissor = ?, Setor = ?, Emissao = ?, Vencimento = ?, Valor = ? WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, titulo.getemissor().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, titulo.getsetor().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, titulo.getemissao().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, titulo.getvencimento().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, titulo.getvalor().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, titulo.getcodigo().getValor().c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool TituloSQL::deleteTitulo(const std::string& codigo) {
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

bool PagamentoSQL::create(const Pagamento& pagamento) {
    std::string sql = "INSERT INTO Pagamento (Codigo, Data, Percentual, Estado, Codigo_Titulo) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, std::stoi(pagamento.getcodigo().getValor()));
    sqlite3_bind_text(stmt, 2, pagamento.getdata().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, std::stoi(pagamento.getpercentual().getValor()));
    sqlite3_bind_text(stmt, 4, pagamento.getestado().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, pagamento.getcodigoTitulo().getValor().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool PagamentoSQL::read(int codigo, Pagamento& pagamento) {
    std::string sql = "SELECT * FROM Pagamento WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, codigo);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        CodPagamento codPagamento;
        codPagamento.setValor(std::to_string(sqlite3_column_int(stmt, 0)));
        pagamento.setcodigo(codPagamento);

        Data data;
        data.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        pagamento.setdata(data);

        Percentual percentual;
        percentual.setValor(std::to_string(sqlite3_column_int(stmt, 2)));
        pagamento.setpercentual(percentual);

        Estado estado;
        estado.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        pagamento.setestado(estado);

        CodTitulo codTitulo;
        codTitulo.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        pagamento.setcodigoTitulo(codTitulo);
    } else {
        std::cerr << "Pagamento não encontrado." << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool PagamentoSQL::update(const Pagamento& pagamento) {
    std::string sql = "UPDATE Pagamento SET Data = ?, Percentual = ?, Estado = ? WHERE Codigo = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, pagamento.getdata().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, std::stoi(pagamento.getpercentual().getValor()));
    sqlite3_bind_text(stmt, 3, pagamento.getestado().getValor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, std::stoi(pagamento.getcodigo().getValor()));

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool PagamentoSQL::deletePagamento(int codigo) {
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

std::vector<Titulo> TituloSQL::listar(const std::string& cpfConta) {
    std::vector<Titulo> titulos;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT * FROM Titulo WHERE CPF_Conta = ?;";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, cpfConta.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Titulo titulo;
            CodTitulo codigo;
            codigo.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            titulo.setcodigo(codigo);

            Nome emissor;
            emissor.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            titulo.setemissor(emissor);

            Setor setor;
            setor.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            titulo.setsetor(setor);

            Data emissao;
            emissao.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            titulo.setemissao(emissao);

            Data vencimento;
            vencimento.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            titulo.setvencimento(vencimento);

            Dinheiro valor;
            valor.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            titulo.setvalor(valor);

            CPF cpf;
            cpf.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
            titulo.setcpfConta(cpf);

            titulos.push_back(titulo);
        }

        sqlite3_finalize(stmt);
    }

    return titulos;
}

std::vector<Pagamento> PagamentoSQL::listar(const std::string& codigoTitulo) {
    std::vector<Pagamento> pagamentos;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT * FROM Pagamento WHERE Codigo_Titulo = ?;";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, codigoTitulo.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Pagamento pagamento;
            CodPagamento codigo;
            codigo.setValor(std::to_string(sqlite3_column_int(stmt, 0)));
            pagamento.setcodigo(codigo);

            Data data;
            data.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            pagamento.setdata(data);

            Percentual percentual;
            percentual.setValor(std::to_string(sqlite3_column_int(stmt, 2)));
            pagamento.setpercentual(percentual);

            Estado estado;
            estado.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            pagamento.setestado(estado);

            CodTitulo codTitulo;
            codTitulo.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            pagamento.setcodigoTitulo(codTitulo);

            pagamentos.push_back(pagamento);
        }

        sqlite3_finalize(stmt);
    }

    return pagamentos;
}

//COMANDOS SQL PARA MANUSEIO DO BANCO DE DADOS!

#ifndef COMANDOS_H
#define COMANDOS_H
#include "./includes/sqlite3.h"
#include <string>
#include <stdexcept>
#include <vector>

//Criar tabelas
void createTbAcc(sqlite3* db);
void createTablebTtl(sqlite3* db);
void createTablePaym(sqlite3* db);
//Conectar ao banco
sqlite3* startConnection(const std::string& dbFile);
// Comandos Conta
bool createConta(sqlite3* db, const std::string& cpf, const std::string& nome, const std::string& senha);
bool readConta(sqlite3* db, const std::string& cpf, std::vector<std::string>& conta);
bool readSenha(sqlite3* db, const std::string& cpf, std::string& senha);
bool updateConta(sqlite3* db, const std::string& cpf, const std::string& nome, const std::string& senha);
bool deleteConta(sqlite3* db, const std::string& cpf);
// Comandos Titulo
bool createTitulo(sqlite3* db, const std::string& codigo, const std::string& emissor, const std::string& setor, const std::string& emissao, const std::string& vencimento, const std::string& valor, const std::string& cpfConta);
bool readTitulo(sqlite3* db, const std::string& codigo);
bool updateTitulo(sqlite3* db, const std::string& codigo, const std::string& emissor, const std::string& setor, const std::string& emissao, const std::string& vencimento, const std::string& valor);
bool deleteTitulo(sqlite3* db, const std::string& codigoTitulo);
// Comandos Pagamento
bool createPagamento(sqlite3* db, int codigo, const std::string& data, int percentual, const std::string& estado, const std::string& codigoTitulo);
bool readPagamento(sqlite3* db, int codigo);
bool updatePagamento(sqlite3* db, int codigo, const std::string& data, int percentual, const std::string& estado);
bool deletePagamento(sqlite3* db, int codigo);
// Encerrar conexão
void endConnection(sqlite3* db);

#endif // COMANDOS_H 



//COMANDOS SQL PARA MANUSEIO DO BANCO DE DADOS!
#ifndef COMANDOS_H
#define COMANDOS_H
#include <sqlite3.h>
#include <string>
#include <stdexcept>

void createTbAcc(sqlite3* db);

void createTablebTtl(sqlite3* db);


void createTablePaym(sqlite3* db);


sqlite3* startConnection(const std::string& dbFile);


void endConnection(sqlite3* db);

#endif 

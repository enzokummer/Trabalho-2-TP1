#include "controladoras.h"
#include "comandos.h"

bool ControladoraServicoTitulos::criar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    createTitulo(db, titulo.getcodigo().getValor(), titulo.getemissor().getValor(), titulo.getsetor().getValor(), titulo.getemissao().getValor(), titulo.getvencimento().getValor(), titulo.getvalor().getValor(), "cpfprovisorio"); //consertar isso
    endConnection(db);
};
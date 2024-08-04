#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "dominios.h"
#include "entidades.h"
#include <stdexcept>

using namespace std;

class IAAutenticacao{

};

class IAConta{

};

class ISConta{

};

class IAInvestimento{

};

class ISInvestimentoTitulos {
    public:
        virtual bool criar(Titulo) = 0;
        virtual bool recuperar(Titulo*) = 0;
        virtual bool atualizar(Titulo) = 0;
        virtual bool excluir(Titulo) = 0;
        virtual bool listar(Titulo) = 0;
        virtual ~ISInvestimentoTitulos() {};
};

class ISInvestimentoPagamentos {
    public:
        virtual bool criar(Pagamento) = 0;
        virtual bool recuperar(Pagamento*) = 0;
        virtual bool atualizar(Pagamento) = 0;
        virtual bool excluir(Pagamento) = 0;
        virtual bool listar(Pagamento) = 0;
        virtual ~ISInvestimentoPagamentos() {};
};

#endif // INTERFACES_H_INCLUDED

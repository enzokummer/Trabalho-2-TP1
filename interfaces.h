#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "dominios.h"
#include "entidades.h"
#include <stdexcept>

using namespace std;

class IAAutenticacao{

};

class ISAutenticacao {

};

class IAConta{

};

class ISConta{

};

class ISInvestimentoTitulos {
    public:
        virtual bool criar(Titulo) = 0;
        virtual bool recuperar(Titulo*) = 0;
        virtual bool atualizar(Titulo) = 0;
        virtual bool excluir(string) = 0;
        virtual bool listar(Titulo) = 0;
        virtual ~ISInvestimentoTitulos() {};
};

class ISInvestimentoPagamentos {
    public:
        virtual bool criar(Pagamento) = 0;
        virtual bool recuperar(Pagamento*) = 0;
        virtual bool atualizar(Pagamento) = 0;
        virtual bool excluir(string) = 0;
        virtual bool listar(Pagamento) = 0;
        virtual ~ISInvestimentoPagamentos() {};
};

class IAInvestimentos {
    public:
        virtual void setControladoraServicoTitulos(ISInvestimentoTitulos*) = 0;
        virtual void setControladoraServicoPagamentos(ISInvestimentoPagamentos*) = 0;
        virtual bool executarTitulos(CPF) = 0;
        virtual bool executarPagamentos(CPF) = 0;
        virtual ~IAInvestimentos() {};
};

#endif // INTERFACES_H_INCLUDED

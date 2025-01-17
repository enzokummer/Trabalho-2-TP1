#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "dominios.h"
#include "entidades.h"
#include <stdexcept>
#include <vector>

using namespace std;
class ISConta{
    public:
        virtual bool cadastrar(const Conta&) = 0;
        virtual Conta visualizar(const CPF&) = 0;
        virtual bool editar(const Conta&) = 0;
        virtual bool descadastrar(const CPF&) = 0;
        virtual ~ISConta(){}
};
class IAConta{
    public:
        virtual bool executar(CPF) = 0;
        virtual bool cadastrar() = 0;
        virtual void setCntrISConta(ISConta*) = 0;
        virtual ~IAConta(){}
};

class ISAutenticacao{
    public:
        virtual bool autenticar(const CPF&, const Senha&) = 0; // método por meio do qual é solicitado serviço
        virtual ~ISAutenticacao(){}
};

class IAAutenticacao{
    public:
        virtual bool autenticar(CPF*) = 0;                        // M�todo por meio do qual � solicitado servi�o.
        virtual void setCntrISAutenticacao(ISAutenticacao*) = 0;     // M�todo por meio do qual � estabelecida liga��o (link) com a controladora na camada de servi�o.
        virtual ~IAAutenticacao(){}                                  // Método destrutor virtual
};

class ISInvestimentoTitulos {
    public:
        virtual bool criar(Titulo) = 0;
        virtual bool recuperar(Titulo*) = 0;
        virtual bool atualizar(Titulo) = 0;
        virtual bool excluir(string) = 0;
        virtual bool listar(vector<Titulo>*, CPF) = 0;
        virtual ~ISInvestimentoTitulos() {};
};

class ISInvestimentoPagamentos {
    public:
        virtual bool criar(Pagamento) = 0;
        virtual bool recuperar(Pagamento*) = 0;
        virtual bool atualizar(Pagamento) = 0;
        virtual bool excluir(string) = 0;
        virtual bool listar(vector<Pagamento>*, CodTitulo) = 0;
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

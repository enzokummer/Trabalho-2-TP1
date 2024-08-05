#ifndef CONTROLADORAS_H_INCLUDED
#define CONTROLADORAS_H_INCLUDED

#include "interfaces.h"
#include "dominios.h"

#include <stdexcept>
#include <iostream>

#define CLR_SCR system("cls");
using namespace std;

class CntrIAAutenticacao: public IAAutenticacao {
    private:
        ISAutenticacao *cntrISAutenticacao;
    public:
        bool autenticar(CPF*);
        void setCntrISAutenticacao(ISAutenticacao*);
};

void inline CntrIAAutenticacao::setCntrISAutenticacao(ISAutenticacao* cntrISAutenticacao) {
    this->cntrISAutenticacao = cntrISAutenticacao;
}

class CntrISAutenticacao: public ISAutenticacao {
    public:
        bool autenticar(const CPF&, const Senha&);
};

/////////////////////

class ControladoraApresentacaoTitulos {
    private:
        ISInvestimentoTitulos* controladoraServico;
    public:
        void setControladoraServico(ISInvestimentoTitulos*);
        bool criar(const CPF&);
        bool recuperar(const CPF&);
        bool atualizar(const CPF&);
        bool excluir(const CPF&);
        bool listar(const CPF&);
};

class ControladoraApresentacaoPagamentos {
    private:
        ISInvestimentoPagamentos* controladoraServico;
    public:
        void setControladoraServico(ISInvestimentoPagamentos*);
        bool criar();
        bool recuperar();
        bool atualizar();
        bool excluir();
        bool listar();
};

class ControladoraApresentacaoInvestimentos:public IAInvestimentos {
    private:
        ISInvestimentoTitulos* controladoraServicoTitulos;
        ISInvestimentoPagamentos* controladoraServicoPagamentos;
        ControladoraApresentacaoPagamentos* controladoraApresentacaoPagamentos;
        ControladoraApresentacaoTitulos* controladoraApresentacaoTitulos;
    public:
        void setControladoraServicoTitulos(ISInvestimentoTitulos*);
        void setControladoraServicoPagamentos(ISInvestimentoPagamentos*);
        void setControladoraApresentacaoTitulos(ControladoraApresentacaoTitulos*);
        void setControladoraApresentacaoPagamentos(ControladoraApresentacaoPagamentos*);
        bool executarTitulos(CPF);
        bool executarPagamentos(CPF);
};

//////////////////////

class ControladoraServicoTitulos:public ISInvestimentoTitulos {
    private:

    public:
        bool criar(Titulo);
        bool recuperar(Titulo*);
        bool atualizar(Titulo);
        bool excluir(string);
        bool listar(vector<Titulo>*, CPF);
}; 

class ControladoraServicoPagamentos:public ISInvestimentoPagamentos {
    private:

    public:
        bool criar(Pagamento);
        bool recuperar(Pagamento*);
        bool atualizar(Pagamento);
        bool excluir(string);
        bool listar(Pagamento);
};

#endif // CONTROLADORAS_H_INCLUDED
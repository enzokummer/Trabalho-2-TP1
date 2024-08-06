#ifndef CONTROLADORAS_H_INCLUDED
#define CONTROLADORAS_H_INCLUDED

#include "interfaces.h"
#include "dominios.h"

#include <stdexcept>
#include <iostream>

#define CLR_SCR system("cls");
using namespace std;


// AUTENTICACAO
// FEITO POR ENZO KUMMER

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

// TITULOS E PAGAMENTOS
// Feito por Pedro de Paula

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
        bool verificaEmissao(Data, Data);
        bool verificaVencimento(Data, Data);
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
        bool listar(vector<Pagamento>*, CodTitulo);
};

// CONTAS
// Feito por Dagoberto

class CntrISConta: public ISConta {
    private:
        ISConta *CntrISConta;
    public:
        bool cadastrar(const Conta&);
        Conta visualizar(const CPF&);
        bool editar(const Conta&);
        bool descadastrar(const CPF&);
};

class CntrIAConta: public IAConta {
    private:
        ISConta *cntrISConta;
        void visualizar(CPF);
        void editar(CPF);
        bool descadastrar(CPF);
        
    public:
        bool executar(CPF);
        void cadastrar();
        void setCntrISConta(ISConta* CntrISConta);
        
};

void inline CntrIAConta::setCntrISConta(ISConta *cntrISConta) {
    this->cntrISConta = cntrISConta;
}


class CntrAControle {
    private:
        CPF cpf;
        IAAutenticacao *cntrAAutenticacao;
        IAConta *cntrAConta;
        //IATeste *cntrATeste;
    public:
        void executar();
        void executar(CPF*);
        void setCntrAAutenticacao(IAAutenticacao*);
        void setCntrAConta(IAConta*);
        //void setCntrATeste(IATeste*);
};

void inline CntrAControle::setCntrAAutenticacao(IAAutenticacao* cntr) {
    cntrAAutenticacao = cntr;
}

void inline CntrAControle::setCntrAConta(IAConta* cntr) {
    cntrAConta = cntr;
}


#endif // CONTROLADORAS_H_INCLUDED


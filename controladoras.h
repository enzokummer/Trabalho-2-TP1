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

class ControladoraServicoTitulos:public ISInvestimentoTitulos {
    private:

    public:
        bool criar(Titulo);
        bool recuperar(Titulo*);
        bool atualizar(Titulo);
        bool excluir(Titulo);
        bool listar(Titulo);
}; 

class ControladoraServicoPagamentos:public ISInvestimentoPagamentos {
    private:

    public:
        bool criar(Pagamento);
        bool recuperar(Pagamento*);
        bool atualizar(Pagamento);
        bool excluir(Pagamento);
        bool listar(Pagamento);
};

// CONTAS
// Feito por Dagoberto

class CntrISConta: public ISConta {
    private:
        ISConta *CntrISConta;
    public:
        bool cadastrar(const Conta&) override;
        Conta visualizar(const CPF&) override;
        bool editar(const Conta&) override;
        bool descadastrar(const CPF&) override ;
};

class CntrIAConta: public IAConta {
    private:
        ISConta *cntrISConta;
        void visualizar(CPF);
        void editar(CPF);
        bool descadastrar(CPF);
        
    public:
        bool executar(CPF) override;
        void cadastrar() override ;
        void setCntrISConta(ISConta* CntrISConta) override;
        
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


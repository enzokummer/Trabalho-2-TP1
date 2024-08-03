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
        bool autenticar(Matricula*);
        void setCntrISAutenticacao(ISAutenticacao*);
};

void inline CntrIAAutenticacao::setCntrISAutenticacao(ISAutenticacao* cntrISAutenticacao) {
    this->cntrISAutenticacao = cntrISAutenticacao;
}

class CntrISAutenticacao: public ISAutenticacao {
    public:
        bool autenticar(const Matricula&, const Senha&);
};

#endif // CONTROLADORAS_H_INCLUDED

#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "dominios.h"
#include <stdexcept>

using namespace std;

class IAAutenticacao{
    public:
        virtual bool autenticar(Matricula*) = 0                        // Método por meio do qual é solicitado serviço.
        virtual void setCntrLNAutenticacao(ILNAutenticacao *) = 0;      // Método por meio do qual é estabelecida ligação (link) com a controladora na camada de serviço.
        virtual ~IUAutenticacao(){}
};

class ISAutenticacao{
    public:
        virtual bool autenticar(const Matricula&, const Senha&) = 0;
        virtual ~ISAutenticacao(){}
};

class IAConta{

};

class ISConta{

};

class IAInvestimento{

};

class ISInvestimento{

};
#endif // INTERFACES_H_INCLUDED

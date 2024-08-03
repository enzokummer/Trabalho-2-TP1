#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "dominios.h"
#include <stdexcept>

using namespace std;

class IAAutenticacao{
    public:
        virtual bool autenticar(Matricula*) = 0                        // M�todo por meio do qual � solicitado servi�o.
        virtual void setCntrISAutenticacao(ISAutenticacao*) = 0;     // M�todo por meio do qual � estabelecida liga��o (link) com a controladora na camada de servi�o.
        virtual ~IAAutenticacao(){}                                  // Método destrutor virtual
};

class ISAutenticacao{
    public:
        virtual bool autenticar(const Matricula&, const Senha&) = 0; // método por meio do qual é solicitado serviço
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

#include "interfaces.h"

class ControladoraServicoTitulos:public ISInvestimento {
    private:
        
    public:
        bool criar(Titulo);
        virtual bool recuperar(Titulo*);
        virtual bool atualizar(Titulo);
        virtual bool excluir(Titulo);
        virtual bool listar(Titulo);
};
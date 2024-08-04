#include "interfaces.h"

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
        bool criar(Pagamento) = 0;
        bool recuperar(Pagamento*) = 0;
        bool atualizar(Pagamento) = 0;
        bool excluir(Pagamento) = 0;
        bool listar(Pagamento) = 0;
};
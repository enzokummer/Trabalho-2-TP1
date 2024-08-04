#include <iostream>
#include "dominios.h"
#include "entidades.h"
#include "testes.h"
#include "comandos.h"
#include "controladoras.h"

using namespace std;

int main() {
    ControladoraServicoTitulos controladora;
    Titulo titulo;

    CodTitulo codigo;
    codigo.setValor("CDB12345678");

    Nome emissor;
    emissor.setValor("Joao Cleber");

    Setor setor;
    setor.setValor("Agricultura");

    Data emissao;
    emissao.setValor("12-12-2012");

    Data vencimento;
    vencimento.setValor("13-12-2012");

    Dinheiro valor;
    valor.setValor("1.000,00");

    titulo.setcodigo(codigo);
    titulo.setemissao(emissao);
    titulo.setemissor(emissor);
    titulo.setsetor(setor);
    titulo.setvalor(valor);
    titulo.setvencimento(vencimento);
    
    controladora.criar(titulo);
    controladora.recuperar(&titulo);

    emissor.setValor("Cleitin Jeferson");
    titulo.setemissor(emissor);
    cout << titulo.getemissor().getValor();
    controladora.atualizar(titulo);
    controladora.recuperar(&titulo);

    controladora.excluir(titulo);

    /////////////////////////

    ControladoraServicoPagamentos controladora2;
    Pagamento pagamento;

    CodPagamento codigo2;
    codigo2.setValor("12345678");

    Data data;
    data.setValor("12-12-2085");

    Percentual percentual;
    percentual.setValor("82");

    Estado estado;
    estado.setValor("Inadimplente");

    pagamento.setcodigo(codigo2);
    pagamento.setdata(data);
    pagamento.setestado(estado);
    pagamento.setpercentual(percentual);

    controladora2.criar(pagamento);
    controladora2.recuperar(&pagamento);

    estado.setValor("Previsto");
    pagamento.setestado(estado);
    controladora2.atualizar(pagamento);
    controladora2.recuperar(&pagamento);

    controladora2.excluir(pagamento);

    return 0;
}
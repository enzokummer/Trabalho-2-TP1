#include <iostream>
#include "dominios.h"
#include "entidades.h"
#include "testes.h"
#include "comandos.h"
#include "controladoras.h"
#include "interfaces.h"


using namespace std;

int main() {
    /*
    sqlite3* db = startConnection("database.db");
    createTbAcc(db);
    createTablebTtl(db);
    createTablePaym(db);
    endConnection(db);
    */

    ControladoraServicoTitulos controladoraServicoTitulos;
    ControladoraServicoPagamentos controladoraServicoPagamentos;
    ControladoraApresentacaoInvestimentos controladoraApresentacaoInvestimentos;
    ControladoraApresentacaoTitulos controladoraApresentacaoTitulos;
    ControladoraApresentacaoPagamentos controladoraApresentacaoPagamentos;

    controladoraApresentacaoInvestimentos.setControladoraApresentacaoTitulos(&controladoraApresentacaoTitulos);
    controladoraApresentacaoInvestimentos.setControladoraApresentacaoPagamentos(&controladoraApresentacaoPagamentos);
    controladoraApresentacaoInvestimentos.setControladoraServicoPagamentos(&controladoraServicoPagamentos);
    controladoraApresentacaoInvestimentos.setControladoraServicoTitulos(&controladoraServicoTitulos);

    CPF cpf;
    cpf.setValor("059.814.151-00");

    while (true) {
        if (!controladoraApresentacaoInvestimentos.executarTitulos(cpf)) {
            break;
        }
    }

    while (true) {
        if (!controladoraApresentacaoInvestimentos.executarPagamentos(cpf)) {
            break;
        }
    }

    /*Titulo titulo;

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
    
    CPF cpf_conta;
    cpf_conta.setValor("006.599.720-42");

    titulo.setcodigo(codigo);
    titulo.setemissao(emissao);
    titulo.setemissor(emissor);
    titulo.setsetor(setor);
    titulo.setvalor(valor);
    titulo.setvencimento(vencimento);
    titulo.setcpfConta(cpf_conta);

    controladora.criar(titulo);
    controladora.recuperar(&titulo);
    cout << "Titulo:\n Codigo: " << titulo.getcodigo().getValor() << endl << " Emissor: " << titulo.getemissor().getValor() << endl << " Emissao: " << titulo.getemissao().getValor() << endl << " Setor: " << titulo.getsetor().getValor() << endl << endl; //fiquei com preguiça de pôr todos

    emissor.setValor("Cleitin Jeferson");
    setor.setValor("Energia");
    titulo.setemissor(emissor);
    titulo.setsetor(setor);
    controladora.atualizar(titulo);
    controladora.recuperar(&titulo);
    cout << "Titulo:\n Codigo: " << titulo.getcodigo().getValor() << endl << " Emissor: " << titulo.getemissor().getValor() << endl << " Emissao: " << titulo.getemissao().getValor() << endl << " Setor: " << titulo.getsetor().getValor() << endl << endl;

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

    CodTitulo codigoTitulo;
    codigoTitulo.setValor("CDB12345678");

    pagamento.setcodigo(codigo2);
    pagamento.setdata(data);
    pagamento.setestado(estado);
    pagamento.setpercentual(percentual);
    pagamento.setcodigoTitulo(codigoTitulo);

    controladora2.criar(pagamento);
    controladora2.recuperar(&pagamento);
    cout << "Pagamento:\n Codigo: " << pagamento.getcodigo().getValor() << endl << " Data: " << pagamento.getdata().getValor() << endl << " Estado: " << pagamento.getestado().getValor() << endl << " Percentual: " << pagamento.getpercentual().getValor() << endl << endl;

    estado.setValor("Previsto");
    pagamento.setestado(estado);
    percentual.setValor("100");
    pagamento.setpercentual(percentual);
    controladora2.atualizar(pagamento);
    controladora2.recuperar(&pagamento);
    cout << "Pagamento:\n Codigo: " << pagamento.getcodigo().getValor() << endl << " Data: " << pagamento.getdata().getValor() << endl << " Estado: " << pagamento.getestado().getValor() << endl << " Percentual: " << pagamento.getpercentual().getValor() << endl << endl;

    controladora2.excluir(pagamento);
    */
    return 0;
}
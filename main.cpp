#include <iostream>
#include "dominios.h"
#include "entidades.h"
#include "testes.h"
#include "comandos.h"
#include "controladoras.h"
#include <ctime>

using namespace std;
// Função pra pegar a data e hora do sistema

std::string getDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    char date[11];
    snprintf(date, sizeof(date), "%04d-%02d-%02d", year, month, day);
    return std::string(date);
}

bool testDeleteTituloWithPayments(TituloSQL& tituloSQL, PagamentoSQL& pagamentoSQL, ContaSQL& contaSQL) {
    Conta conta;
    CPF cpf;
    cpf.setValor("123.456.789-01");
    conta.setcpf(cpf);
    Nome nome;
    nome.setValor("Test User");
    conta.setnome(nome);
    Senha senha;
    senha.setValor("123456");
    conta.setsenha(senha);

    if (!contaSQL.create(conta)) {
        cerr << "Erro ao criar conta." << endl;
        return false;
    }

    Titulo titulo;
    CodTitulo codTitulo;
    codTitulo.setValor("CDB12345678");
    titulo.setcodigo(codTitulo);
    Nome emissor;
    emissor.setValor("Banco X");
    titulo.setemissor(emissor);
    Setor setor;
    setor.setValor("Energia");
    titulo.setsetor(setor);
    Data emissao;
    emissao.setValor("2023-01-01");
    titulo.setemissao(emissao);
    Data vencimento;
    vencimento.setValor("2025-01-01");
    titulo.setvencimento(vencimento);
    Dinheiro valor;
    valor.setValor("100000");
    titulo.setvalor(valor);
    titulo.setcpfConta(cpf);

    if (!tituloSQL.create(titulo)) {
        cerr << "Erro ao criar título." << endl;
        return false;
    }

    Pagamento pagamento;
    CodPagamento codPagamento;
    codPagamento.setValor("00000001");
    pagamento.setcodigo(codPagamento);
    Data data;
    data.setValor("2024-01-01");
    pagamento.setdata(data);
    Percentual percentual;
    percentual.setValor("50");
    pagamento.setpercentual(percentual);
    Estado estado;
    estado.setValor("Liquidado");
    pagamento.setestado(estado);
    pagamento.setcodigoTitulo(codTitulo);

    if (!pagamentoSQL.create(pagamento)) {
        cerr << "Erro ao criar pagamento." << endl;
        return false;
    }

    if (tituloSQL.deleteTitulo("CDB12345678")) {
        cerr << "Erro: Título deletado indevidamente apesar de ter pagamento associado." << endl;
        return false;
    }

    if (!pagamentoSQL.deletePagamento(1)) {
        cerr << "Erro ao deletar pagamento." << endl;
        return false;
    }

    if (!tituloSQL.deleteTitulo("CDB12345678")) {
        cerr << "Erro ao deletar título que não tem mais pagamentos associados." << endl;
        return false;
    }

    return true;
}

int main() {
    sqlite3* db = startConnection("database.db");
    createTbAcc(db);
    createTablebTtl(db);
    createTablePaym(db);
    endConnection(db);

    // Criar instâncias das controladoras
    CntrAControle* apresentacao = new CntrAControle();
    CntrIAAutenticacao* autenticacao = new CntrIAAutenticacao();
    CntrISAutenticacao* servAutenticacao = new CntrISAutenticacao();
    CntrIAConta* aprConta = new CntrIAConta();
    CntrISConta* servConta = new CntrISConta();
    
    ControladoraServicoTitulos controladoraServicoTitulos;
    ControladoraServicoPagamentos controladoraServicoPagamentos;
    ControladoraApresentacaoInvestimentos controladoraApresentacaoInvestimentos;
    ControladoraApresentacaoTitulos controladoraApresentacaoTitulos;
    ControladoraApresentacaoPagamentos controladoraApresentacaoPagamentos;
    
    // Configurar dependências
    controladoraApresentacaoInvestimentos.setControladoraApresentacaoTitulos(&controladoraApresentacaoTitulos);
    controladoraApresentacaoInvestimentos.setControladoraApresentacaoPagamentos(&controladoraApresentacaoPagamentos);
    controladoraApresentacaoInvestimentos.setControladoraServicoPagamentos(&controladoraServicoPagamentos);
    controladoraApresentacaoInvestimentos.setControladoraServicoTitulos(&controladoraServicoTitulos);
    

    aprConta->setCntrISConta(servConta);
    autenticacao->setCntrISAutenticacao(servAutenticacao);
    apresentacao->setCntrAAutenticacao(autenticacao);
    apresentacao->setCntrAConta(aprConta);
    apresentacao->setCntrAInvestimentos(&controladoraApresentacaoInvestimentos);
    
    // Chamar o método executar da controladora principal
    apresentacao->executar();

    // Limpar a memória
    delete apresentacao;
    delete autenticacao;
    delete servAutenticacao;
    delete aprConta;

    return 0;
}

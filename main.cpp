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

    /*cout << endl << "TESTES DO BANCO" << endl;
    
    try {
        sqlite3* db = startConnection("database.db");
        createTbAcc(db);
        createTablebTtl(db);
        createTablePaym(db);

        ContaSQL contaSQL(db);
        TituloSQL tituloSQL(db);
        PagamentoSQL pagamentoSQL(db);

        contaSQL.deleteConta("123.456.789-01");
        tituloSQL.deleteTitulo("CDB12345678");
        pagamentoSQL.deletePagamento(1);

        Conta conta;
        CPF cpf;
        cpf.setValor("123.456.789-01");
        conta.setcpf(cpf);
        Nome nome;
        nome.setValor("Fulano Silva");
        conta.setnome(nome);
        Senha senha;
        senha.setValor("123456");
        conta.setsenha(senha);

        if (contaSQL.create(conta)) {
            cout << "Sucesso - Criar Conta" << endl;
        } else {
            cout << "Falha - Criar Conta" << endl;
        }

        Conta contaLida;
        if (contaSQL.read("123.456.789-01", contaLida)) {
            cout << "Sucesso - Ler Conta: " << contaLida.getnome().getValor() << endl;
            cout << "CPF Lido: " << contaLida.getcpf().getValor() << endl;
        } else {
            cout << "Falha - Ler Conta" << endl;
        }

        Nome novoNome;
        novoNome.setValor("Novo Nome");
        contaLida.setnome(novoNome);
        Senha novaSenha;
        novaSenha.setValor("456198");
        contaLida.setsenha(novaSenha);

        if (contaSQL.update(contaLida)) {
            cout << "Sucesso - Atualizar Conta" << endl;
        } else {
            cout << "Falha - Atualizar Conta" << endl;
        }

        if (contaSQL.deleteConta("123.456.789-01")) {
            cout << "Sucesso - Excluir Conta" << endl;
        } else {
            cout << "Falha - Excluir Conta" << endl;
        }

        std::string currentDate = getDate();

        Titulo titulo;
        CodTitulo codTitulo;
        codTitulo.setValor("CDB12345678");
        titulo.setcodigo(codTitulo);
        Nome emissor;
        emissor.setValor("Emissor Teste");
        titulo.setemissor(emissor);
        Setor setor;
        setor.setValor("Agricultura");
        titulo.setsetor(setor);
        Data emissao;
        emissao.setValor(currentDate);
        titulo.setemissao(emissao);
        Data vencimento;
        vencimento.setValor("2025-01-01");
        titulo.setvencimento(vencimento);
        Dinheiro valor;
        valor.setValor("1000,00");
        titulo.setvalor(valor);
        titulo.setcpfConta(cpf);

        if (tituloSQL.create(titulo)) {
            cout << "Sucesso - Criar Titulo" << endl;
        } else {
            cout << "Falha - Criar Titulo" << endl;
        }

        Titulo tituloLido;
        if (tituloSQL.read("CDB12345678", tituloLido)) {
            cout << "Sucesso - Ler Titulo" << endl;
        } else {
            cout << "Falha - Ler Titulo" << endl;
        } 

        Nome novoEmissor;
        novoEmissor.setValor("Emissor Atualizado");
        tituloLido.setemissor(novoEmissor);
        Setor novoSetor;
        novoSetor.setValor("Financas");
        tituloLido.setsetor(novoSetor);
        Dinheiro novoValor;
        novoValor.setValor("2.000,00");
        tituloLido.setvalor(novoValor);

        if (tituloSQL.update(tituloLido)) {
            cout << "Sucesso - Atualizar Titulo" << endl;
        } else {
            cout << "Falha - Atualizar Titulo" << endl;
        }

        if (tituloSQL.deleteTitulo("CDB12345678")) {
            cout << "Sucesso - Deletar Titulo" << endl;
        } else {
            cout << "Falha ao deletar título!" << endl;
        }

        if (testDeleteTituloWithPayments(tituloSQL, pagamentoSQL, contaSQL)) {
            cout << "Sucesso - Não deletar título com pagamento associado" << endl;
        } else {
            cout << "Falha - Não deletar título com pagamento associado" << endl;
        }

        Pagamento pagamento;
        CodPagamento codPagamento;
        codPagamento.setValor("00000001");
        pagamento.setcodigo(codPagamento);
        Data data;
        data.setValor(currentDate);
        pagamento.setdata(data);
        Percentual percentual;
        percentual.setValor("100");
        pagamento.setpercentual(percentual);
        Estado estado;
        estado.setValor("Previsto");
        pagamento.setestado(estado);
        pagamento.setcodigoTitulo(codTitulo);

        if (pagamentoSQL.create(pagamento)) {
            cout << "Sucesso - Criar Pagamento" << endl;
        } else {
            cout << "Falha - Criar Pagamento" << endl;
        }

        Pagamento pagamentoLido;
        if (pagamentoSQL.read(1, pagamentoLido)) {
            cout << "Sucesso - Ler Pagamento" << endl;
        } else {
            cout << "Falha - Ler Pagamento" << endl;
        }

        Estado novoEstado;
        novoEstado.setValor("Liquidado");
        pagamentoLido.setestado(novoEstado);
        Percentual novoPercentual;
        novoPercentual.setValor("80");
        pagamentoLido.setpercentual(novoPercentual);

        if (pagamentoSQL.update(pagamentoLido)) {
            cout << "Sucesso - Atualizar Pagamento" << endl;
        } else {
            cout << "Falha - Atualizar Pagamento" << endl;
        }

        if (pagamentoSQL.deletePagamento(1)) {
            cout << "Sucesso - Deletar Pagamento" << endl;
        } else {
            cout << "Falha - Deletar Pagamento" << endl;
        }

        endConnection(db);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    cout << endl << "TESTES DOS DOMINIOS" << endl;

    TUCodPagamento testeA;

    if(testeA.run() == true) {
        cout << "Sucesso - Codigo de Pagamento" << endl;
    }else {
        cout << "Falha - Codigo de Pagamento" << endl;
    }

    TUCodTitulo testeB;

    if(testeB.run() == true) {
        cout << "Sucesso - Codigo de Titulo" << endl;
    }else {
        cout << "Falha - Codigo de Titulo" << endl;
    }

    TUCPF testeC;

    if(testeC.run() == true) {
        cout << "Sucesso - CPF" << endl;
    }else {
        cout << "Falha - CPF" << endl;
    }

    TUData testeD;

    if(testeD.run() == true) {
        cout << "Sucesso - Data" << endl;
    }else {
        cout << "Falha - Data" << endl;
    }

    TUDinheiro testeE;

    if(testeE.run() == true) {
        cout << "Sucesso - Dinheiro" << endl;
    }else {
        cout << "Falha - Dinheiro" << endl;
    }

    TUEstado testeF;

    if(testeF.run() == true) {
        cout << "Sucesso - Estado" << endl;
    }else {
        cout << "Falha - Estado" << endl;
    }

    TUNome testeG;

    if(testeG.run() == true) {
        cout << "Sucesso - Nome" << endl;
    }else {
        cout << "Falha - Nome" << endl;
    }

    TUPercentual testeH;

    if(testeH.run() == true) {
        cout << "Sucesso - Percentual" << endl;
    }else {
        cout << "Falha - Percentual" << endl;
    }

    TUSenha testeI;

    if(testeI.run() == true) {
        cout << "Sucesso - Senha" << endl;
    }else {
        cout << "Falha - Senha" << endl;
    }

    TUSetor testeJ;

    if(testeJ.run() == true) {
        cout << "Sucesso - Setor" << endl;
    }else {
        cout << "Falha - Setor" << endl;
    }

    cout << endl << "TESTES DAS ENTIDADES" << endl;

    TUConta testeK;

    if(testeK.run() == true) {
        cout << "Sucesso - Conta" << endl;
    }else {
        cout << "Falha - Conta" << endl;
    }

    TUTitulo testeL;

    if(testeL.run() == true) {
        cout << "Sucesso - Titulo" << endl;
    }else {
        cout << "Falha - Titulo" << endl;
    }

    TUPagamento testeM;

    if(testeM.run() == true) {
        cout << "Sucesso - Pagamento" << endl;
    }else {
        cout << "Falha - Pagamento" << endl;
    }
    */
    getchar();
    system("cls");
     // Criar instâncias das controladoras
    CntrAControle* apresentacao = new CntrAControle();
    CntrIAAutenticacao* autenticacao = new CntrIAAutenticacao();
    CntrISAutenticacao* servAutenticacao = new CntrISAutenticacao();
    CntrIAConta* aprConta = new CntrIAConta();
    CntrISConta* servConta = new CntrISConta();
    /*
    ControladoraServicoTitulos controladoraServicoTitulos;
    ControladoraServicoPagamentos controladoraServicoPagamentos;
    ControladoraApresentacaoInvestimentos controladoraApresentacaoInvestimentos;
    ControladoraApresentacaoTitulos controladoraApresentacaoTitulos;
    ControladoraApresentacaoPagamentos controladoraApresentacaoPagamentos;
    
    // Configurar dependências
    controladoraApresentacaoInvestimentos.setControladoraApresentacaoTitulos(&controladoraApresentacaoTitulos);
    controladoraApresentacaoInvestimentos.setControladoraApresentacaoPagamentos(&controladoraApresentacaoPagamentos);
    controladoraApresentacaoInvestimentos.setControladoraServicoPagamentos(&controladoraServicoPagamentos);
    controladoraApresentacaoInvestimentos.setControladoraServicoTitulos(&controladoraServicoTitulos);*/
    aprConta->setCntrISConta(servConta);
    autenticacao->setCntrISAutenticacao(servAutenticacao);
    apresentacao->setCntrAAutenticacao(autenticacao);
    apresentacao->setCntrAConta(aprConta);

    
    // Chamar o método executar da controladora principal
    apresentacao->executar();

    // Limpar a memória
    delete apresentacao;
    delete autenticacao;
    delete servAutenticacao;
    delete aprConta;

    return 0;
}

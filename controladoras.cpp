#include "controladoras.h"
#include "dominios.h"
#include "entidades.h"
#include "comandos.h"
#include "sqlite3.h"
#include "interfaces.h"

using namespace std;

// AUTENTICACAO
/*
bool CntrIAAutenticacao::autenticar(CPF *cpf) {
    string logIn = "********* Bem-vindo de volta! *********";
    string pedeCPF = "CPF:";
    string pedeSenha = "Senha:";
    string deuErro = "Formato inserido está incorreto. Por favor, tente novamente! (Digite qualquer botão)";

    string campo1, campo2;

    Senha senha;

    while(true) {
        CLR_SCR; // LIMPA A TELA
        cout << logIn << endl;
        cout << pedeCPF << " ";
        cin >> campo1;
        cout << pedeSenha << " ";
        cin >> campo2;

        try {
            cpf->setValor(campo1);
            senha.setValor(campo2);
            break;
        } catch (invalid_argument &exp) {
            CLR_SCR;
            cout << deuErro << endl;
            getchar();
        }
    }
    return (cntrISAutenticacao->autenticar(*cpf, senha));
}

bool CntrISAutenticacao::autenticar(const CPF& cpf, const Senha& senha){
    sqlite3* db;
    int rc = sqlite_open("database.db", &db);
    if(rc){
        cerr<<"Erro na comunicação com o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    string senhaReal;
    string numCpf = cpf.getValor();

    if(readSenha(db,numCpf,senhaReal)){
        return (senhaReal == senha.getValor());
    }
}
*/
//Apresentação Investimentos -------------------

void ControladoraApresentacaoInvestimentos::setControladoraApresentacaoPagamentos(ControladoraApresentacaoPagamentos* controladora) {
    this->controladoraApresentacaoPagamentos = controladora;
}

void ControladoraApresentacaoInvestimentos::setControladoraApresentacaoTitulos(ControladoraApresentacaoTitulos* controladora) {
    this->controladoraApresentacaoTitulos = controladora;
}

void ControladoraApresentacaoInvestimentos::setControladoraServicoTitulos(ISInvestimentoTitulos* controladora) {
    this->controladoraServicoTitulos = controladora;
}

void ControladoraApresentacaoInvestimentos::setControladoraServicoPagamentos(ISInvestimentoPagamentos* controladora) {
    this->controladoraServicoPagamentos = controladora;
}

bool ControladoraApresentacaoInvestimentos::executarTitulos(CPF cpf) {
    this->controladoraApresentacaoTitulos->setControladoraServico(this->controladoraServicoTitulos);
    char input;
    cout << "Digite o numero da acao que deseja realizar em Titulos: \n1. Criar\n2. Recuperar\n3. Atualizar\n4. Excluir\n5. Listar\n6. Voltar" << endl;
    cin >> input;
    switch (input) {
        case '1':
            return controladoraApresentacaoTitulos->criar(cpf);
            break;
        case '2':
            return controladoraApresentacaoTitulos->recuperar(cpf);
            break;
        case '3':
            return controladoraApresentacaoTitulos->atualizar(cpf);
            break;
        case '4':
            return controladoraApresentacaoTitulos->excluir(cpf);
            break;/*
        case '5':
            return controladoraApresentacaoTitulos->listar();
            break;*/
        case '6':
            return false;
            break;
        default:
            cout << "\nComando invalido. Selecione um comando listado a seguir." << endl << endl;
            return true;
            break;
    }
}

bool ControladoraApresentacaoInvestimentos::executarPagamentos(CPF cpf) {
    //this->controladoraApresentacaoPagamentos->setControladoraServico(this->controladoraServicoPagamentos);
    char input;
    cout << "Digite o número da ação que deseja realizar em Pagamentos: \n1. Criar\n2. Recuperar\n3. Atualizar\n4. Excluir\n5. Listar\n6. Voltar" << endl;
    cin >> input;
    switch (input) {/*
        case '1':
            return controladoraApresentacaoPagamentos->criar(cpf);
            break;
        case '2':
            return controladoraApresentacaoPagamentos->recuperar(cpf);
            break;
        case '3':
            return controladoraApresentacaoPagamentos->atualizar(cpf);
            break;
        case '4':
            return controladoraApresentacaoPagamentos->excluir(cpf);
            break;
        case '5':
            return controladoraApresentacaoPagamentos->listar();
            break;
        case '6':
            //<-sair
            break;*/
        default:
            //<-mensagem de erro
            //<-recarregar tela
            return false;
            break;
    }
}

//Apresentacao Investimentos Titulos

void ControladoraApresentacaoTitulos::setControladoraServico(ISInvestimentoTitulos* controladora) {
    this->controladoraServico = controladora;
}

bool ControladoraApresentacaoTitulos::criar(const CPF& cpf) {
    string input;
    Titulo titulo;

    cout << "Para criar um titulo, preencha os dados a seguir.\n\nDigite o codigo." << endl;
    cin >> input;
    CodTitulo codigo;
    codigo.setValor(input);
    input = "";
    cin.ignore(256, '\n');

    cout << "\nDigite o emissor." << endl;
    getline(cin, input);
    Nome emissor;
    emissor.setValor(input);
    input = "";

    cout << "\nDigite o setor." << endl;
    cin >> input;
    Setor setor;
    setor.setValor(input);
    input = "";

    //emissao
    cout << "\nDigite a data de emissao." << endl;
    cin >> input;
    Data emissao;
    emissao.setValor(input);
    input = "";

    //vencimento
    cout << "\nDigite a data de vencimento." << endl;
    cin >> input;
    Data vencimento;
    vencimento.setValor(input);
    input = "";

    //valor
    cout << "\nDigite o valor." << endl;
    cin >> input;
    Dinheiro valor;
    valor.setValor(input);
    input = "";

    titulo.setcodigo(codigo);
    titulo.setemissor(emissor);
    titulo.setsetor(setor);
    titulo.setemissao(emissao);
    titulo.setvencimento(vencimento);
    titulo.setvalor(valor);
    titulo.setcpfConta(cpf);

    if (controladoraServico->criar(titulo)) {
        cout << "\nTitulo criado com sucesso." << endl << endl;
        return true;
    }
    cout << "\nFalha ao criar titulo." << endl << endl;
    return false;
}

bool ControladoraApresentacaoTitulos::recuperar(const CPF& cpf) {
    Titulo titulo;
    CodTitulo codigo;
    string input;

    cout << "\nDigite o codigo do titulo que deseja ler." << endl;
    cin >> input;
    codigo.setValor(input);
    titulo.setcodigo(codigo);

    if (controladoraServico->recuperar(&titulo)) {
        cout << "\nTitulo Lido:\n Codigo: " << titulo.getcodigo().getValor() << endl << " Emissor: " << titulo.getemissor().getValor() << endl 
        << " Setor: " << titulo.getsetor().getValor() << endl << " Emissao: " << titulo.getemissao().getValor() << endl << " Vencimento: "
        << titulo.getvencimento().getValor() << endl << " Valor: " << titulo.getvalor().getValor() << endl << endl;
        return true;
    } else {
        cout << "\nFalha ao ler titulo." << endl << endl;
        return false;
    }
}

bool ControladoraApresentacaoTitulos::atualizar(const CPF& cpf) {
    Titulo titulo;
    CodTitulo codigo;
    string input;

    cout << "\nDigite o codigo do titulo que deseja atualizar." << endl;
    cin >> input;
    codigo.setValor(input);
    titulo.setcodigo(codigo);
    input = "";
    cin.ignore(256, '\n');

    cout << "\nDigite o novo valor do Emissor. Digite 0 para manter o valor atual." << endl;
    getline(cin, input);
    if (input != "0") {
        Nome emissor;
        emissor.setValor(input);
        titulo.setemissor(emissor);
    }
    input = "";

    cout << "\nDigite o novo valor do Setor. Digite 0 para manter o valor atual." << endl;
    cin >> input;
    if (input != "0") {
        Setor setor;
        setor.setValor(input);
        titulo.setsetor(setor);
    }
    input = "";

    cout << "\nDigite o novo valor da Emissao. Digite 0 para manter o valor atual." << endl;
    cin >> input;
    if (input != "0") {
        Data emissao;
        emissao.setValor(input);
        titulo.setemissao(emissao);
    }
    input = "";

    cout << "\nDigite o novo valor do Vencimento. Digite 0 para manter o valor atual." << endl;
    cin >> input;
    if (input != "0") {
        Data vencimento;
        vencimento.setValor(input);
        titulo.setvencimento(vencimento);
    }
    input = "";

    cout << "\nDigite o novo valor do Valor. Digite 0 para manter o valor atual." << endl;
    cin >> input;
    if (input != "0") {
        Dinheiro valor;
        valor.setValor(input);
        titulo.setvalor(valor);
    }
    input = "";

    if (this->controladoraServico->atualizar(titulo)) {
        cout << "\nTitulo atualizado com sucesso." << endl << endl;
        return true;
    }
    cout << "\nFalha ao atualizar titulo." << endl << endl;
    return false;
}

bool ControladoraApresentacaoTitulos::excluir(const CPF& cpf) {
    CodTitulo codigo;
    string input;
    bool confirmacao;

    cout << "\nDigite o codigo do titulo que deseja excluir" << endl;
    cin >> input;
    codigo.setValor(input);

    cout << "\nO titulo de codigo " << codigo.getValor() << " sera excluido permantentemente, deseja prosseguir? Digite 1 para confirmar e 0 para cancelar." << endl;
    cin >> confirmacao;
    if (confirmacao) {
        if (this->controladoraServico->excluir(codigo.getValor())) {
            cout << "\nTitulo exlcuido com sucesso." << endl << endl;
            return true;
        }
        cout << "\nFalha ao excluir titulo." << endl << endl;
        return false;
    }
    cout << "\nExclusao cancelada." << endl << endl;
    return false;
}

//Serviço Investimentos - Títulos --------------

bool ControladoraServicoTitulos::criar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    if (comandos.create(titulo)) {
        endConnection(db);
        return true;
    } else {
        endConnection(db);
        return false;
    }
};

bool ControladoraServicoTitulos::recuperar(Titulo* titulo) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    if (comandos.read(titulo->getcodigo().getValor(), *titulo)) {
        endConnection(db);
        return true;
    } else {
        endConnection(db);
        return false;
    }
};

bool ControladoraServicoTitulos::atualizar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    if (comandos.update(titulo)) {
        endConnection(db);
        return true;
    }
    endConnection(db);
    return false;
};

bool ControladoraServicoTitulos::excluir(string codigo) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    if (comandos.deleteTitulo(codigo)) {
        endConnection(db);
        return true;
    } 
    endConnection(db);
    return false;
    
    
};

bool ControladoraServicoTitulos::listar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    
    endConnection(db);
};

//Serviço Investimentos - Pagamentos --------------

bool ControladoraServicoPagamentos::criar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    comandos.create(pagamento);
    endConnection(db);
};

bool ControladoraServicoPagamentos::recuperar(Pagamento* pagamento) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    comandos.read(stoi(pagamento->getcodigo().getValor()), *pagamento);
    endConnection(db);
};

bool ControladoraServicoPagamentos::atualizar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    comandos.update(pagamento);
    endConnection(db);
};

bool ControladoraServicoPagamentos::excluir(string codigo) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    comandos.deletePagamento(stoi(codigo));
    endConnection(db);
};

bool ControladoraServicoPagamentos::listar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    
    endConnection(db);
};
#include "controladoras.h"
#include "dominios.h"
#include "entidades.h"
#include "comandos.h"
#include "sqlite3.h"
#include <vector>

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
    int rc = sqlite3_open("database.db", &db);
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
            break;
        case '5':
            return controladoraApresentacaoTitulos->listar(cpf);
            break;
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
    this->controladoraApresentacaoPagamentos->setControladoraServico(this->controladoraServicoPagamentos);
    char input;
    cout << "Digite o numero da acao que deseja realizar em Pagamentos: \n1. Criar\n2. Recuperar\n3. Atualizar\n4. Excluir\n5. Listar\n6. Voltar" << endl;
    cin >> input;
    switch (input) {
        case '1':
            return controladoraApresentacaoPagamentos->criar();
            break;
        case '2':
            return controladoraApresentacaoPagamentos->recuperar();
            break;
        case '3':
            return controladoraApresentacaoPagamentos->atualizar();
            break;
        case '4':
            return controladoraApresentacaoPagamentos->excluir();
            break;
        case '5':
            return controladoraApresentacaoPagamentos->listar();
            break;
        case '6':
            return false;
            break;
        default:
            cout << "\nComando invalido. Selecione um comando listado a seguir." << endl << endl;
            return true;
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

    cout << "Para criar um Titulo, preencha os dados a seguir.\n\nDigite o codigo." << endl;
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
    } else {
        cout << "\nFalha ao criar Titulo." << endl << endl;
    }
    return true;
}

bool ControladoraApresentacaoTitulos::recuperar(const CPF& cpf) {
    Titulo titulo;
    CodTitulo codigo;
    string input;

    cout << "\nDigite o codigo do Titulo que deseja ler." << endl;
    cin >> input;
    codigo.setValor(input);
    titulo.setcodigo(codigo);

    if (controladoraServico->recuperar(&titulo)) {
        cout << "\nTitulo Lido:\n Codigo: " << titulo.getcodigo().getValor() << endl << " Emissor: " << titulo.getemissor().getValor() << endl 
        << " Setor: " << titulo.getsetor().getValor() << endl << " Emissao: " << titulo.getemissao().getValor() << endl << " Vencimento: "
        << titulo.getvencimento().getValor() << endl << " Valor: " << titulo.getvalor().getValor() << endl << endl;
    } else {
        cout << "\nFalha ao ler Titulo." << endl << endl;
    }
    return true;
}

bool ControladoraApresentacaoTitulos::atualizar(const CPF& cpf) {
    Titulo titulo;
    CodTitulo codigo;
    string input;

    cout << "\nDigite o codigo do Titulo que deseja atualizar." << endl;
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
    } else {
        cout << "\nFalha ao atualizar Titulo." << endl << endl;
    }
    return true;
}

bool ControladoraApresentacaoTitulos::excluir(const CPF& cpf) {
    CodTitulo codigo;
    string input;
    bool confirmacao;

    cout << "\nDigite o codigo do Titulo que deseja excluir" << endl;
    cin >> input;
    codigo.setValor(input);

    cout << "\nO Titulo de codigo " << codigo.getValor() << " sera excluido permantentemente, deseja prosseguir? Digite 1 para confirmar e 0 para cancelar." << endl;
    cin >> confirmacao;
    if (confirmacao) {
        if (this->controladoraServico->excluir(codigo.getValor())) {
            cout << "\nTitulo exlcuido com sucesso." << endl << endl;
        }
        cout << "\nFalha ao excluir Titulo." << endl << endl;
    } else {
        cout << "\nExclusao cancelada." << endl << endl;
    }
    return true;
}

bool ControladoraApresentacaoTitulos::listar(const CPF& cpf_conta) {
    vector<Titulo> titulos;

    cout << "Listando todos os Titulos associados a conta." << endl << endl;
    if (this->controladoraServico->listar(&titulos, cpf_conta)) {
        for (Titulo titulo : titulos) {
            cout << "Codigo: " << titulo.getcodigo().getValor() << endl << " Emissor: " << titulo.getemissor().getValor() << endl 
            << " Setor: " << titulo.getsetor().getValor() << endl << " Emissao: " << titulo.getemissao().getValor() << endl << " Vencimento: "
            << titulo.getvencimento().getValor() << endl << " Valor: " << titulo.getvalor().getValor() << endl << endl;
        }
    } else {
        cout << "Falha ao listar Titulos/Nao ha Titulos a serem listados." << endl << endl;
    }
    return true;
}

//Apresentacao Investimentos Pagamentos

void ControladoraApresentacaoPagamentos::setControladoraServico(ISInvestimentoPagamentos* controladora) {
    this->controladoraServico = controladora;
}

bool ControladoraApresentacaoPagamentos::verificaEmissao(Data emissao, Data data_pagamento) {
    int ano_emissao, mes_emissao, dia_emissao, ano_data, mes_data, dia_data;
    string aux_emissao, aux_data;
    for (int i = 0; i<2; i++) {
        aux_emissao += emissao.getValor()[i];
        aux_data += data_pagamento.getValor()[i];
    }
    dia_emissao = stoi(aux_emissao);
    dia_data = stoi(aux_data);

    aux_emissao = "";
    aux_data = "";
    for (int i = 3; i<5; i++) {
        aux_emissao += emissao.getValor()[i];
        aux_data += data_pagamento.getValor()[i];
    }
    mes_emissao = stoi(aux_emissao);
    mes_data = stoi(aux_data);

    aux_emissao = "";
    aux_data = "";
    for (int i = 6; i<10; i++) {
        aux_emissao += emissao.getValor()[i];
        aux_data += data_pagamento.getValor()[i];
    }
    ano_emissao = stoi(aux_emissao);
    ano_data = stoi(aux_data);

    if (ano_data > ano_emissao) {
        return false;
    } else if (mes_data > mes_emissao) {
        return false;
    } else if (dia_data > dia_emissao) {
        return false;
    }
    return true;
}

bool ControladoraApresentacaoPagamentos::verificaVencimento(Data vencimento, Data data_pagamento) {
    int ano_vencimento, mes_vencimento, dia_vencimento, ano_data, mes_data, dia_data;
    string aux_vencimento, aux_data;
    for (int i = 0; i<2; i++) {
        aux_vencimento += vencimento.getValor()[i];
        aux_data += data_pagamento.getValor()[i];
    }
    dia_vencimento = stoi(aux_vencimento);
    dia_data = stoi(aux_data);

    aux_vencimento = "";
    aux_data = "";
    for (int i = 3; i<5; i++) {
        aux_vencimento += vencimento.getValor()[i];
        aux_data += data_pagamento.getValor()[i];
    }
    mes_vencimento = stoi(aux_vencimento);
    mes_data = stoi(aux_data);

    aux_vencimento = "";
    aux_data = "";
    for (int i = 6; i<10; i++) {
        aux_vencimento += vencimento.getValor()[i];
        aux_data += data_pagamento.getValor()[i];
    }
    ano_vencimento = stoi(aux_vencimento);
    ano_data = stoi(aux_data);

    if (ano_data < ano_vencimento) {
        return false;
    } else if (mes_data < mes_vencimento) {
        return false;
    } else if (dia_data < dia_vencimento) {
        return false;
    }
    return true;
}

bool ControladoraApresentacaoPagamentos::criar() {
    Titulo titulo;
    Pagamento pagamento;
    string input;

    cout << "\nPara criar um Pagamento, preencha os dados a seguir.\n\nDigite o codigo do Titulo ao qual sera associado o pagamento." << endl;
    cin >> input;
    CodTitulo codigo_titulo;
    codigo_titulo.setValor(input);
    titulo.setcodigo(codigo_titulo);
    input = "";

    //verifica se o titulo existe
    ControladoraServicoTitulos controladora;
    if (!controladora.recuperar(&titulo)) {
        cout << "Erro. Titulo nao existe." << endl << endl;
        return true;
    }

    cout << "\nDigite o codigo do Pagamento." << endl;
    cin >> input;
    CodPagamento codigo;
    codigo.setValor(input);
    input = "";

    cout << "\nDigite a data." << endl;
    cin >> input;
    Data data;
    data.setValor(input);
    input = "";

    //verifica se a data é posterior à data de emissão e anterior à data de vencimento
    if (!verificaEmissao(titulo.getemissao(), data) or !verificaVencimento(titulo.getvencimento(), data)) {
        cout << "Erro. Data nao pode ser anterior a Emissao nem posterior ao Vencimento." << endl << endl;
        return true;
    }

    cout << "\nDigite o percentual." << endl;
    cin >> input;
    Percentual percentual;
    percentual.setValor(input);
    input = "";
    
    cout << "\nDigite o estado." << endl;
    cin >> input;
    Estado estado;
    estado.setValor(input);
    input = "";

    pagamento.setcodigoTitulo(codigo_titulo);
    pagamento.setcodigo(codigo);
    pagamento.setdata(data);
    pagamento.setestado(estado);
    pagamento.setpercentual(percentual);

    if (this->controladoraServico->criar(pagamento)) {
        cout << "\nPagamento criado com sucesso." << endl << endl;
    } else {
        cout << "\nFalha ao criar pagamento." << endl << endl;
    }
    return true;
}

bool ControladoraApresentacaoPagamentos::recuperar() {
    Pagamento pagamento;
    string input;

    cout << "\nDigite o codigo do Pagamento que deseja ler." << endl;
    cin >> input;
    CodPagamento codigo;
    codigo.setValor(input);
    pagamento.setcodigo(codigo);
    
    if (this->controladoraServico->recuperar(&pagamento)) {
        cout << "\nPagamento Lido:\n Codigo: " << pagamento.getcodigo().getValor() << "\n Data: " << pagamento.getdata().getValor()
        << "\n Estado: " << pagamento.getestado().getValor() << "\n Percentual: " << pagamento.getpercentual().getValor() << endl << endl;
    } else {
        cout << "Falha ao ler Pagamento.";
    }
    return true;
}

bool ControladoraApresentacaoPagamentos::excluir() {
    string input;
    CodPagamento codigo;

    cout << "\nDigite o codigo do Pagamento que deseja excluir." << endl << endl;
    cin >> input;
    codigo.setValor(input);

    if (this->controladoraServico->excluir(codigo.getValor())) {
        cout << "\nPagamento excluido com sucesso." << endl << endl;
    } else {
        cout << "\nFalha ao excluir pagamenot." << endl << endl;
    }
    return true;
}

bool ControladoraApresentacaoPagamentos::atualizar() {
    Pagamento pagamento;
    CodPagamento codigo;
    string input;

    cout << "\nDigite o codigo do Pagamento que deseja atualizar." << endl << endl;
    cin >> input;
    codigo.setValor(input);
    pagamento.setcodigo(codigo);
    input = "";

    cout << "\nDigite o novo valor da Data. Digite 0 para manter o valor atual." << endl;
    cin >> input;
    if (input != "0") {
        Data data;
        data.setValor(input);
        pagamento.setdata(data);
    }
    input = "";

    cout << "\nDigite o novo valor do Estado. Digite 0 para manter o valor atual." << endl;
    cin >> input;
    if (input != "0") {
        Estado estado;
        estado.setValor(input);
        pagamento.setestado(estado);
    }
    input = "";

    cout << "\nDigite o novo valor do Percentual. Digite 0 para manter o valor atual." << endl;
    cin >> input;
    if (input != "0") {
        Percentual percentual;
        percentual.setValor(input);
        pagamento.setpercentual(percentual);
    }
    input = "";

    if (this->controladoraServico->atualizar(pagamento)) {
        cout << "\nPagamento atualizado com sucesso." << endl << endl;
    } else {
        cout << "\nFalha ao atualizar Pagamento." << endl << endl;
    }
    return true;
}

bool ControladoraApresentacaoPagamentos::listar() {
    vector<Pagamento> pagamentos;
    CodTitulo codigoDoTitulo;
    string input;

    cout << "\nDigite o codigo do Titulo cujos Pagamentos serao listados." << endl;
    cin >> input;
    codigoDoTitulo.setValor(input);
    
    cout << "\nListando todos os Pagamentos associados ao Titulo de codigo " << codigoDoTitulo.getValor() << endl << endl;
    if (this->controladoraServico->listar(&pagamentos, codigoDoTitulo)) {
        for (const Pagamento& pagamento : pagamentos) {
            cout << "Codigo: " << pagamento.getcodigo().getValor() << "\n Data: " << pagamento.getdata().getValor()
            << "\n Estado: " << pagamento.getestado().getValor() << "\n Percentual: " << pagamento.getpercentual().getValor() << endl << endl;
        }
    } else {
        cout << "Falha ao listar Pagamentos/Nao ha Pagamentos a serem listados." << endl << endl;
    }
    return true;
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

bool ControladoraServicoTitulos::listar(vector<Titulo>* titulos, CPF cpf_conta) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    *titulos = comandos.listar(cpf_conta.getValor());
    endConnection(db);
    return !titulos->empty();
};

//Serviço Investimentos - Pagamentos --------------

bool ControladoraServicoPagamentos::criar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    if (comandos.create(pagamento)) {
        endConnection(db);
        return true;
    }
    endConnection(db);
    return false;
};

bool ControladoraServicoPagamentos::recuperar(Pagamento* pagamento) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    if (comandos.read(stoi(pagamento->getcodigo().getValor()), *pagamento)) {
        endConnection(db);
        return true;
    }
    endConnection(db);
    return false;
};

bool ControladoraServicoPagamentos::atualizar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    if (comandos.update(pagamento)) {
        endConnection(db);
        return true;
    }
    endConnection(db);
    return true;
};

bool ControladoraServicoPagamentos::excluir(string codigo) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    if (comandos.deletePagamento(stoi(codigo))) {
        endConnection(db);
        return true;
    }
    endConnection(db);
    return false;  
};

bool ControladoraServicoPagamentos::listar(vector<Pagamento>* pagamentos, CodTitulo codigo) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    *pagamentos = comandos.listar(codigo.getValor());
    if (!pagamentos->empty()) {
        endConnection(db);
        return true;
    }
    endConnection(db);
    return false;
};
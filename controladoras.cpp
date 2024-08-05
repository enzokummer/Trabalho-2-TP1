#include "controladoras.h"
#include "dominios.h"
#include "entidades.h"
#include "comandos.h"
#include "sqlite3.h"

using namespace std;
//conta

bool CntrIAConta::executar(CPF cpf) {

    std::string texto1 = "Selecione um dos serviços: ";
    std::string texto2 = "1 - Visualizar dados.";
    std::string texto3 = "2 - Editar dados.";
    std::string texto4 = "3 - Descadastrar conta.";
    std::string texto5 = "4 - Retornar.";

    int campo;

    bool apresentar = true;

    while (apresentar) {

        CLR_SCR;

        std::cout << texto1 << std::endl;
        std::cout << texto2 << std::endl;
        std::cout << texto3 << std::endl;
        std::cout << texto4 << std::endl;
        std::cout << texto5 << std::endl;

        campo = getchar() - 48;

        switch (campo) {
            case 1:
                visualizar(cpf);
                break;
            case 2:
                editar(cpf);
                break;
            case 3:
                if (descadastrar(cpf)) {
                    std::cout << "Conta descadastrada com sucesso." << std::endl;
                    getchar();
                    return false;
                }
                break;
            case 4:
                apresentar = false;
                break;
        }
    }
    return true;
}

void CntrIAConta::cadastrar() {

    std::string texto1 = "Complete com os seus dados: ";
    std::string texto2 = "Nome:";
    std::string texto3 = "CPF:";
    std::string texto4 = "Senha:";
    std::string texto6 = "Dados em formato inválido. Pressione qualquer tecla para continuar.";
    std::string texto7 = "Conta cadastrada com sucesso. Pressione qualquer tecla para continuar.";
    std::string texto8 = "Falha ao realizar o cadastramento. Pressione qualquer tecla para continuar.";

    std::string campo1, campo2, campo3;

    Nome nome;
    CPF cpf;
    Senha senha;

    CLR_SCR;

    std::cout << texto1 << std::endl;
    std::cout << texto2 << " ";
    std::cin >> campo1;
    std::cout << texto3 << " ";
    std::cin >> campo2;
    std::cout << texto4 << " ";
    std::cin >> campo3;

    try {
        nome.setValor(campo1);
        cpf.setValor(campo2);
        senha.setValor(campo3);
    }
    catch (std::invalid_argument &excecao) {
        std::cout << texto6 << std::endl;
        getchar();
        return;
    }

    Conta conta;
    conta.setnome(nome);
    conta.setcpf(cpf);
    conta.setsenha(senha);

    if (cntrISConta->cadastrar(conta)) {
            std::cout << texto7 << std::endl;
            getchar();
            return;
        }
    
    std::cout << texto8 << std::endl;
    getchar();
}

void CntrIAConta::visualizar(CPF cpf) {

    Conta conta = cntrISConta->visualizar(cpf);

    CLR_SCR;

    std::string texto1 = "Aqui estão os seus dados atuais: ";
    std::string texto2 = "Nome: ";
    std::string texto3 = "CPF: ";
    std::string texto4 = "Senha: ";
    std::string texto6 = "Digite qualquer tecla para continuar.";

    std::cout << texto1 << std::endl;
    std::cout << texto2 << conta.getnome().getValor() << std::endl;
    std::cout << texto3 << conta.getcpf().getValor() << std::endl;
    std::cout << texto4 << conta.getsenha().getValor() << std::endl;
    std::cout << texto6 << std::endl;
    getchar();
}

void CntrIAConta::editar(CPF cpf) {

    Nome nome;
    Senha senha;
    Conta conta = cntrISConta->visualizar(cpf);

    std::string texto1 = "Aqui estão os seus dados atuais: ";
    std::string texto2 = "Nome: ";
    std::string texto3 = "CPF: ";
    std::string texto4 = "Senha: ";
    std::string texto6 = "Insira seus novos dados: ";
    std::string texto7 = "Dados inválidos. Tente novamente.";
    std::string texto8 = "1 - Inserir novamente.";
    std::string texto9 = "2 - Retornar.";
    std::string texto10 = "Dados atualizados com sucesso.";
    std::string texto11 = "Falha ao editar dados.";
    std::string texto12 = "Digite qualquer tecla para retornar.";

    int campo;
    std::string campo1, campo2;
    bool apresentar = true;

    while (apresentar) {
        try {
            CLR_SCR;

            std::cout << texto1 << std::endl;
            std::cout << texto2 << conta.getnome().getValor() << std::endl;
            std::cout << texto3 << conta.getcpf().getValor() << std::endl;
            std::cout << texto4 << conta.getsenha().getValor() << std::endl;
            std::cout << texto6 << std::endl;
            std::cout << texto2 << "";
            std::cin >> campo1;
            std::cout << texto4 << "";
            std::cin >> campo2;

            nome.setValor(campo1);
            senha.setValor(campo2);
            conta.setnome(nome);
            conta.setsenha(senha);

            apresentar = false;
        }
        catch (std::invalid_argument &excecao) {
            std::cout << texto7 << std::endl;
            std::cout << texto8 << std::endl;
            std::cout << texto9 << std::endl;
            campo = getchar() - 48;
            if (campo == 2) {
                return;
            }
            getchar();
        }
    }
    if (cntrISConta->editar(conta)) {
        std::cout << texto10 << std::endl;
    } else {
        std::cout << texto11 << std::endl;
    }
    std::cout << texto12 << std::endl;
    getchar();
}

bool CntrIAConta::descadastrar(CPF cpf) {

    std::string texto1 = "Tem certeza que deseja descadastrar a conta?";
    std::string texto2 = "1 - Sim.";
    std::string texto3 = "2 - Não.";
    std::string texto4 = "Falha na exclusão. Tente novamente.";
    std::string texto5 = "Descadastramento cancelado.";

    int campo;

    Conta conta = cntrISConta->visualizar(cpf);

    CLR_SCR;

    std::cout << texto1 << std::endl;
    std::cout << texto2 << std::endl;
    std::cout << texto3 << std::endl;

    campo = getchar() - 48;

    switch (campo) {
        case 1:
            if (cntrISConta->descadastrar(cpf)) {
                return true;
            } else {
                std::cout << texto4 << std::endl;
                getchar();
                return false;
            }
        case 2:
            std::cout << texto5 << std::endl;
            getchar();
            return false;
    }
    return false;
}

bool CntrISConta::cadastrar(const Conta& conta) {
    sqlite3* db = startConnection("database.db");
    ContaSQL comandos(db);
    comandos.create(conta);
    endConnection(db);
}

Conta CntrISConta::visualizar(const CPF& cpf) {
    sqlite3* db = startConnection("database.db");
    ContaSQL comandos(db);
    Conta contaLida;

    comandos.read(cpf.getValor(),contaLida);
    endConnection(db);
}

bool CntrISConta::editar(const Conta& conta) {
    sqlite3* db = startConnection("database.db");
    ContaSQL comandos(db);
    comandos.update(conta);
    endConnection(db);
}

bool CntrISConta::descadastrar(const CPF &cpf) { 
    sqlite3* db = startConnection("database.db");
    ContaSQL comandos(db);
    comandos.deleteConta(cpf.getValor());
    endConnection(db);
}

// APRESENTACAO

void CntrAControle::executar(){ // MENU NAO LOGADO
    int opcao;
    CPF* cpfUser = new CPF();

    cout << "*************************************************" << endl;
    cout << "Bem vindo ao Sistema de monitoração de pagamentos e vencimentos de títulos de renda fixa!" << endl;
    cout << "Por favor, selecione a opção desejada" << endl;
    cout << "1. Criar Conta" << endl;
    cout << "2. Acessar Conta" << endl;
    cout << "3. Sair" << endl;

    cin >> opcao;
    
    CntrIAAutenticacao* aprAuth;
    CntrISAutenticacao* servAuth;
    CntrIAConta* aprConta;
    CntrISConta* servConta;
    switch (opcao) {
        case 1: //criar conta
            aprConta = new CntrIAConta();
            servConta = new CntrISConta();
            aprConta->setCntrISConta(servConta);

            aprConta->cadastrar();
            break;
        case 2: //login conta
            aprAuth = new CntrIAAutenticacao();
            servAuth = new CntrISAutenticacao();
            
            aprAuth->setCntrISAutenticacao(servAuth);
            cout << "Eu irei agora chamar o método autenticar" << endl;
            
            
            if(aprAuth->autenticar(cpfUser)){
                executar(cpfUser);
            };

            break;
        case 3: 
            //SAIR!
            cout << "Até logo!" << endl;
            break;
        default:
            cout << "Expressão errada." << endl;
            
    }   
}

void CntrAControle::executar(CPF* cpfUser){ //MENU LOGADO
    int opcao;
    cout << "Login foi realizado com sucesso! \nSelecione a opção que deseja acessar:" << endl;
    cout << "1. Contas" << endl;
    cout << "2. Investimentos" << endl;
    cout << "3. Menu Inicial" << endl;
    cin >> opcao;
    CntrIAConta* aprConta;
    CntrISConta* servConta;
    switch(opcao){
        case 1:
            aprConta = new CntrIAConta();
            servConta = new CntrISConta();
            aprConta->setCntrISConta(servConta);

            aprConta->executar(*cpfUser);
        case 2:
            cout << "investimentos!!!" << endl;
    };
}
// AUTENTICACAO

bool CntrIAAutenticacao::autenticar(CPF *cpf) {
    string logIn = "********* Tela de Log-In *********";
    string pedeCPF = "CPF:";
    string pedeSenha = "Senha:";
    string deuErro = "Formato inserido está incorreto. Por favor, tente novamente! (Digite qualquer tecla)";

    string campo1, campo2;

    Senha senha;

    while(true) {
//        CLR_SCR; // LIMPA A TELA
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
//            CLR_SCR;
            cout << deuErro << endl;
            getchar(); // espera o usuário
        }
    }
    return (cntrISAutenticacao->autenticar(*cpf, senha));
}

bool CntrISAutenticacao::autenticar(const CPF& cpf, const Senha& senha){
    /*sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    if(rc){
        cerr<<"Erro na comunicação com o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    string senhaReal;
    string numCpf = cpf.getValor();

    if(readSenha(db,numCpf,senhaReal)){
        return (senhaReal == senha.getValor());
    }*/
   Conta conta1;
   Conta conta2;

   conta1.setcpf(cpf);
   conta1.setsenha(senha);

   sqlite3* db = startConnection("database.db");
   ContaSQL comandos(db);
   comandos.read(cpf.getValor(), conta2);

   cout << "Banco de dados foi acessado" << endl;

   return (conta1.getsenha().getValor() == conta2.getsenha().getValor());

}
//Serviço Investimentos - Títulos --------------

bool ControladoraServicoTitulos::criar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    comandos.create(titulo);
    endConnection(db);
};

bool ControladoraServicoTitulos::recuperar(Titulo* titulo) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    comandos.read(titulo->getcodigo().getValor(), *titulo);
    endConnection(db);
};

bool ControladoraServicoTitulos::atualizar(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    comandos.update(titulo);
    endConnection(db);
};

bool ControladoraServicoTitulos::excluir(Titulo titulo) {
    sqlite3* db = startConnection("database.db");
    TituloSQL comandos(db);
    comandos.deleteTitulo(titulo.getcodigo().getValor());
    endConnection(db);
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

bool ControladoraServicoPagamentos::excluir(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    PagamentoSQL comandos(db);
    comandos.deletePagamento(stoi(pagamento.getcodigo().getValor()));
    endConnection(db);
};

bool ControladoraServicoPagamentos::listar(Pagamento pagamento) {
    sqlite3* db = startConnection("database.db");
    
    endConnection(db);
};


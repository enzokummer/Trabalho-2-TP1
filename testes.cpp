#include "testes.h"
//TESTES DOS DOMINIOS
bool TUdominios::run() {
    setUp();
    testarCenarioValido();
    testarCenarioInvalido();
    tearDown();
    return state;
}

void TUCodPagamento::setUp() {
    codigo = new CodPagamento();
    state = sucesso;
}

void TUCodPagamento::testarCenarioValido() {
    try {
        codigo->setValor(valorValido);
        if (codigo->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUCodPagamento::testarCenarioInvalido() {
    try {
        codigo->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (codigo->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUCodPagamento::tearDown() {
    delete codigo;
}

void TUCodTitulo::setUp() {
    codigo = new CodTitulo();
    state = sucesso;
}

void TUCodTitulo::testarCenarioValido() {
    try {
        codigo->setValor(valorValido);
        if (codigo->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUCodTitulo::testarCenarioInvalido() {
    try {
        codigo->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (codigo->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUCodTitulo::tearDown() {
    delete codigo;
}

void TUCPF::setUp() {
    cpf = new CPF();
    state = sucesso;
}

void TUCPF::testarCenarioValido() {
    try {
        cpf->setValor(valorValido);
        if (cpf->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUCPF::testarCenarioInvalido() {
    try {
        cpf->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (cpf->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUCPF::tearDown() {
    delete cpf;
}

void TUData::setUp() {
    data = new Data();
    state = sucesso;
}

void TUData::testarCenarioValido() {
    try {
        data->setValor(valorValido);
        if (data->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUData::testarCenarioInvalido() {
    try {
        data->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (data->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUData::tearDown() {
    delete data;
}

void TUDinheiro::setUp() {
    dinheiro = new Dinheiro();
    state = sucesso;
}

void TUDinheiro::testarCenarioValido() {
    try {
        dinheiro->setValor(valorValido);
        if (dinheiro->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUDinheiro::testarCenarioInvalido() {
    try {
        dinheiro->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (dinheiro->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUDinheiro::tearDown() {
    delete dinheiro;
}

void TUEstado::setUp() {
    estado = new Estado();
    state = sucesso;
}

void TUEstado::testarCenarioValido() {
    try {
        estado->setValor(valorValido);
        if (estado->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUEstado::testarCenarioInvalido() {
    try {
        estado->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (estado->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUEstado::tearDown() {
    delete estado;
}

void TUNome::setUp() {
    nome = new Nome();
    state = sucesso;
}

void TUNome::testarCenarioValido() {
    try {
        nome->setValor(valorValido);
        if (nome->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUNome::testarCenarioInvalido() {
    try {
        nome->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (nome->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUNome::tearDown() {
    delete nome;
}

void TUPercentual::setUp() {
    percentual = new Percentual();
    state = sucesso;
}

void TUPercentual::testarCenarioValido() {
    try {
        percentual->setValor(valorValido);
        if (percentual->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUPercentual::testarCenarioInvalido() {
    try {
        percentual->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (percentual->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUPercentual::tearDown() {
    delete percentual;
}

void TUSenha::setUp() {
    senha = new Senha();
    state = sucesso;
}

void TUSenha::testarCenarioValido() {
    try {
        senha->setValor(valorValido);
        if (senha->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUSenha::testarCenarioInvalido() {
    try {
        senha->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (senha->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUSenha::tearDown() {
    delete senha;
}

void TUSetor::setUp() {
    setor = new Setor();
    state = sucesso;
}

void TUSetor::testarCenarioValido() {
    try {
        setor->setValor(valorValido);
        if (setor->getValor() != valorValido) {
            state = falha;
        }
    }
    catch (invalid_argument &excecao) {
        state = falha;
    }
}

void TUSetor::testarCenarioInvalido() {
    try {
        setor->setValor(valorInvalido);
        state = falha;
    }
    catch (invalid_argument &excecao) {
        if (setor->getValor() == valorInvalido) {
            state = falha;
        }
    }
}

void TUSetor::tearDown() {
    delete setor;
}

//TESTES ENTIDADES ------------------------------------------------------------------------
bool TUEntidades::run() {
    setUp();
    testarCenarioValido();
    tearDown();
    return state;
}

void TUConta::setUp() {
    conta = new Conta();
    state = sucesso;
}

void TUConta::testarCenarioValido() {
    CPF cpf;
    cpf.setValor(valorValidoCPF);
    conta->setcpf(cpf);
    if (conta->getcpf().getValor() != valorValidoCPF) {
        state = falha;
    }

    Nome nome;
    nome.setValor(valorValidoNome);
    conta->setnome(nome);
    if (conta->getnome().getValor() != valorValidoNome) {
        state = falha;
    }

    Senha senha;
    senha.setValor(valorValidoSenha);
    conta->setsenha(senha);
    if (conta->getsenha().getValor() != valorValidoSenha) {
        state = falha;
    }
}

void TUConta::tearDown() {
    delete conta;
}

void TUTitulo::setUp() {
    titulo = new Titulo();
    state = sucesso;
}

void TUTitulo::testarCenarioValido() {
    CodTitulo codigo;
    codigo.setValor(valorValidoCodTitulo);
    titulo->setcodigo(codigo);
    if (titulo->getcodigo().getValor() != valorValidoCodTitulo) {
        state = falha;
    }

    Nome emissor;
    emissor.setValor(valorValidoNome);
    titulo->setemissor(emissor);
    if (titulo->getemissor().getValor() != valorValidoNome) {
        state = falha;
    }

    Setor setor;
    setor.setValor(valorValidoSetor);
    titulo->setsetor(setor);
    if (titulo->getsetor().getValor() != valorValidoSetor) {
        state = falha;
    }

    Data emissao;
    emissao.setValor(valorValidoData);
    titulo->setemissao(emissao);
    if (titulo->getemissao().getValor() != valorValidoData) {
        state = falha;
    }

    Data vencimento;
    vencimento.setValor(valorValidoData);
    titulo->setvencimento(vencimento);
    if (titulo->getvencimento().getValor() != valorValidoData) {
        state = falha;
    }

    Dinheiro valor;
    valor.setValor(valorValidoDinheiro);
    titulo->setvalor(valor);
    if (titulo->getvalor().getValor() != valorValidoDinheiro) {
        state = falha;
    }
}

void TUTitulo::tearDown() {
    delete titulo;
}

void TUPagamento::setUp() {
    pagamento = new Pagamento();
    state = sucesso;
}

void TUPagamento::testarCenarioValido() {
    CodPagamento codigo;
    codigo.setValor(valorValidoCodPagamento);
    pagamento->setcodigo(codigo);
    if (pagamento->getcodigo().getValor() != valorValidoCodPagamento) {
        state = falha;
    }

    Data data;
    data.setValor(valorValidoData);
    pagamento->setdata(data);
    if (pagamento->getdata().getValor() != valorValidoData) {
        state = falha;
    }

    Percentual percentual;
    percentual.setValor(valorValidoPercentual);
    pagamento->setpercentual(percentual);
    if (pagamento->getpercentual().getValor() != valorValidoPercentual) {
        state = falha;
    }

    Estado estado;
    estado.setValor(valorValidoEstado);
    pagamento->setestado(estado);
    if (pagamento->getestado().getValor() != valorValidoEstado) {
        state = falha;
    }
}

void TUPagamento::tearDown() {
    delete pagamento;
}

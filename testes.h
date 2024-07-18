
#ifndef TESTES_H
#define TESTES_H

#include "dominios.h"
#include "entidades.h"

class TUdominios {
protected:
    virtual void setUp() = 0;
    virtual void tearDown() = 0;
    virtual void testarCenarioValido() = 0;
    virtual void testarCenarioInvalido() = 0;
    bool state;
public:
    virtual ~TUdominios() {}
    const static bool sucesso = true;
    const static bool falha = false;
    bool run();
};

class TUCodPagamento : public TUdominios {
private:
    const string valorValido = "12345678";
    const string valorInvalido = "01234567";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    CodPagamento *codigo;
};

class TUCodTitulo : public TUdominios {
private:
    const string valorValido = "CDB12345678";
    const string valorInvalido = "01234567";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    CodTitulo *codigo;
};

class TUCPF : public TUdominios {
private:
    const string valorValido = "190.559.370-88";
    const string valorInvalido = "190.559.370.88";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    CPF *cpf;
};

class TUData : public TUdominios {
private:
    const string valorValido = "21-04-2004";
    const string valorInvalido = "21-04-2101";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    Data *data;
};

class TUDinheiro : public TUdominios {
private:
    const string valorValido = "30.000,00";
    const string valorInvalido = "30000";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    Dinheiro *dinheiro;
};

class TUEstado : public TUdominios {
private:
    const string valorValido = "Previsto";
    const string valorInvalido = "Preuvistou";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    Estado *estado;
};

class TUNome : public TUdominios {
private:
    const string valorValido = "Andre";
    const string valorInvalido = "Marcos Paulinhogamer";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    Nome *nome;
};

class TUPercentual : public TUdominios {
private:
    const string valorValido = "80";
    const string valorInvalido = "101";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    Percentual *percentual;
};

class TUSenha : public TUdominios {
private:
    const string valorValido = "789543";
    const string valorInvalido = "123456";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    Senha *senha;
};

class TUSetor : public TUdominios {
private:
    const string valorValido = "Agricultura";
    const string valorInvalido = "Agroehpop";
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    void testarCenarioInvalido() override;
    Setor *setor;
};

//TESTES ENTIDADES
class TUEntidades {
protected:
    virtual void setUp() = 0;
    virtual void tearDown() = 0;
    virtual void testarCenarioValido() =0;
    const string valorValidoCodPagamento = "12345678";
    const string valorValidoCodTitulo = "CDB12345678";
    const string valorValidoCPF = "190.559.370-88";
    const string valorValidoData = "21-04-2004";
    const string valorValidoDinheiro = "30.000,00";
    const string valorValidoEstado = "Previsto";
    const string valorValidoNome = "Andre";
    const string valorValidoPercentual = "99";
    const string valorValidoSenha = "354612";
    const string valorValidoSetor = "Agricultura";
    bool state;
public:
    const bool sucesso = true;
    const bool falha = false;
    bool run();
};

class TUConta : public TUEntidades {
private:
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    Conta *conta;
};

class TUTitulo : public TUEntidades {
private:
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    Titulo *titulo;
};

class TUPagamento : public TUEntidades {
private:
    void setUp() override;
    void tearDown() override;
    void testarCenarioValido() override;
    Pagamento *pagamento;
};
#endif //TESTES_H

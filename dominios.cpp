
#include "dominios.h"

void Dominios::setValor(string valor){
    validar(valor);
    this->valor = valor;
}

//Validando Codigo de Pagamento
void CodPagamento::validar(string valor) {
    char primeiroDigito = valor[0];
    size_t tamanhoCodigo = valor.length();
    //Verifica se o primeiro digito eh zero e se o codigo tem 8 digitos.
    if (primeiroDigito == '0'){
        throw invalid_argument("Codigo invalido: primeiro digito = 0");
    }
    if(tamanhoCodigo != 8) {
        throw invalid_argument("Codigo invalido: tamanho incorreto");
    }
}

//Validando Codigo de Titulo
void CodTitulo::validar(string valor){
    size_t tamanhoCodigo = valor.length();
    string sigla = valor.substr(0,3);
    //Verifica se o codigo possui uma das siglas aleatorias
    //se nao tiver, recebe a classificacao invalida.
    string siglaValida = (sigla != "CDB" && sigla != "CRA" && sigla != "CRI"
                          && sigla != "LCA" && sigla != "LCI" && sigla != "DEB")
                           ? "invalida" : "valida";
    //Verifica se ha caractere invalido
    for(int i=0; i<tamanhoCodigo; i++) {
        if (isdigit(valor[i]) == 0 && isalpha(valor[i] == 0)) {
            throw invalid_argument("Codigo invalido: caracetre invalido detectado");
        }
    }
    if (siglaValida == "invalida") {
        throw invalid_argument("Codigo invalido: sigla incorreta");
    }
    if (tamanhoCodigo != 11) {
        throw invalid_argument("Codigo invalido: tamanho incorreto");
    }
}

//Validando o CPF
void CPF::validar(string valor) {
    // Regex para validar o formato do CPF
    std::regex regex(R"(\d{3}\.\d{3}\.\d{3}-\d{2})");

    // Verifica se o formato ta certo
    if (!std::regex_match(valor, regex)) {
        throw invalid_argument("CPF invalido: Nao segue o formato XXX.XXX.XXX-CC");
    }

    // Limpando o valor
    string digitos;
    for (char c : valor) {
        if (isdigit(c)) {
            digitos += c;
        }
    }

    // Verificando se os digitos sao iguais
    if (std::all_of(digitos.begin(), digitos.end(), [&](char c){ return c == digitos[0]; })) {
        throw invalid_argument("CPF invalido: Todos os digitos sao iguais");
    }

    // Calculando os digitos verificadores
    auto calcDigito = [](const string& d, int tam) {
        int soma = 0;
        for (int i = 0; i < tam; i++) {
            soma += (d[i] - '0') * (tam + 1 - i);
        }
        int resto = soma % 11;
        return resto < 2 ? 0 : 11 - resto;
    };

    int digito1 = calcDigito(digitos, 9);
    int digito2 = calcDigito(digitos, 10);

    // Verificando se os digitos calculados s�o iguais aos do CPF
    if (digito1 != (digitos[9] - '0') || digito2 != (digitos[10] - '0')) {
        throw invalid_argument("CPF invalido: Digitos verificadores incorretos");
    }
}

//Verifica se eh bissexto
bool Data::isBissexto(string valor){
    string subs;
    subs = valor.substr(7);
    int ano = stoi(subs);

    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        return true;
    } else {
        return false;
    }
}
//Validando a data
void Data::validar(string valor){
    int diasMes = 0;

    //Separando a data
    int dia = stoi(valor.substr(0,2));
    int mes = stoi(valor.substr(3,2));
    int ano = stoi(valor.substr(6,4));

    //Separando separadores
    string sep1 = valor.substr(2,1);
    string sep2 = valor.substr(5,1);

    //Definindo os dias do mes
    if (mes == 2 && isBissexto(valor))
        diasMes = 29;
    else if (mes == 2)
        diasMes = 28;
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        diasMes = 30;
    else
        diasMes = 31;

    if((dia < 00 || dia > diasMes) //Verificando os dias
       ||(mes < 01 || mes >12) //Verificando os meses
       ||(ano < 2000 || ano > 2100) //Verificando os anos
       ||(sep1 != "-" || sep2 != "-")){ //Verificando os hifens
        throw invalid_argument("Data invalida.");
    };
}

//Validando Dinheiro
void Dinheiro::validar(string valor){
    //Regex para validar o formato da quantia
    std::regex regex("^([0-9]{1,3}(\\.[0-9]{3})*|[0-9]+),[0-9]{2}$");

    //Verifica se o formato ta certo
    if (!std::regex_match(valor, regex)) {
        throw invalid_argument("Dinheiro invalido.");
    }

    //Tira os pontos e troca virgula por ponto pra usar o double
    std::string quantiaSemPontos = valor;
    quantiaSemPontos.erase(remove(quantiaSemPontos.begin(), quantiaSemPontos.end(), '.'), quantiaSemPontos.end());
    std::replace(quantiaSemPontos.begin(), quantiaSemPontos.end(), ',', '.');

    // Converte a string para float
    double quantia = std::stof(quantiaSemPontos);

    if(quantia < 0.0 || quantia > 1000000.0){
        throw invalid_argument("Dinheiro invalido.");
    }
}

//Verifica se o Estado eh um dos 3 estados validos.
void Estado::validar(string valor){
    string estados[3] = {"Previsto","Liquidado",
    "Inadimplente"};

    bool valida = false;

    //Itera sobre a lista e compara com o valor de entrada
    for (const string &estado : estados){
        if (estado == valor){
            valida = true;
            break;
        }
    }
    if(!valida) {
        throw invalid_argument("Estado invalido.");
    }
}

//Verifica se o Nome atende os requisitos
void Nome::validar(string valor){
    size_t tamanhoNome = valor.length();
    int quantosNomes = 1;
    int posEspaco;

    //Descobre quantos termos tem o nome e salva posicao do espaco ' '.
    //Tambem verifica se todos os caracteres sao validos.
    for (size_t i=0; i<tamanhoNome; i++){
        if(valor[i] == ' '){
            quantosNomes++;
            posEspaco = i;
        }
        if(isalpha(valor[i]) == 0 && valor[i] != ' '){
            throw invalid_argument("Nome com caractere invalido.");
        }
    }

    //Verifica se excedeu o numero maximo de nomes.
    if(quantosNomes > 2) {
        throw invalid_argument("Numero maximo de nomes (2) excedido.");
    }

    //Salva o tamanho dos termos em caso de nome composto.
    size_t tamNome1, tamNome2;
    string nome1, nome2;
    if(quantosNomes == 2){
        nome1 = valor.substr(0, posEspaco);
        nome2 = valor.substr(posEspaco + 1);

        tamNome1 = nome1.length();
        tamNome2 = nome2.length();
    }

    //Verifica se os termos tem a quantidade correta de caracteres
    if((quantosNomes == 1 && (tamanhoNome > 10 || tamanhoNome < 3))
        || (quantosNomes == 2 && (tamNome1 > 10 || tamNome1 < 3 || tamNome2 > 10 || tamNome2 < 3))){
        throw invalid_argument("Numero maximo de caracteres por nome excedido.");
    }

    //Verifica se algum dos termos comeca com letra maiuscula
    if((!isupper(valor[0]) && quantosNomes == 1)
        ||(quantosNomes == 2 && (!isupper(nome1[0]) || !isupper(nome2[0])))) {
        throw invalid_argument("Nome invalido: algum(ns) dos termo(s) nao comeca com letra maiuscula");
    }


}

//Verifica se o Percentual ta entre 0 e 100
void Percentual::validar(string valor){
    int percentual = stoi(valor);
    if(percentual > 100 || percentual < 0) {
        throw invalid_argument("Percentual invalido.");
    }
}

//Validando a senha
void Senha::validar(string valor){
    //Verifica se o primeiro digito eh zero
    if(valor[0] == '0') {
        throw invalid_argument("Senha invalida: primeiro digito tem que ser diferente de zero");
    }

    size_t tamanhoSenha = valor.length();
    //Verifica tamanho da senha
    if(tamanhoSenha != 6) {
        throw invalid_argument("Senha invalida: senha deve ter 6 digitos");
    }

    for(size_t i=0; i<tamanhoSenha; i++){
        //Verifica se a senha eh numerica
        if(isdigit(valor[i]) == 0) {
            throw invalid_argument("Senha invalida: caracter nao numerico identificado");
        }
    }

    //Verifica se a senha eh sequencial
    string senhasInvalidas[8] = {"123456","234567","345678",
    "456789","987654","876543","765432","654321"};
    for(size_t i=0; i<8; i++){
        if(valor == senhasInvalidas[i]) {
            throw invalid_argument("Senha invalida: senha sequencial identificada");
        }
    }

    //Verifica se ha digito duplicado
    int count[10] = {0};
    for (char c : valor){
        int digito = c - '0';
        if(count[digito] > 0) {
            throw invalid_argument("Senha invalida: digito duplicado identificado");
        }
        count[digito]++;
    }

}

//Verifica se o Setor eh um dos 10 setores validos.
void Setor::validar(string valor){
    string setores[10] = {"Agricultura","Construcao Civil",
    "Energia","Financas","Imobiliario","Papel e celulose",
    "Pecuaria","Quimica e petroquimica","Metalurgia e siderurgia",
    "Mineracao"};
    bool valida = false;

    //Itera sobre a lista e compara com o valor de entrada
    for (const string &setor : setores){
        if (setor == valor){
            valida = true;
            break;
        }
    }
    if(!valida) {
        throw invalid_argument("Setor invalido.");
    }
}

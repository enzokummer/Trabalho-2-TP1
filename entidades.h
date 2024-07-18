
#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "dominios.h"

//ENTIDADE CONTA -----------------------------------------------------------------
/**
* @brief Classe concreta, que contem as informacoes sobre os dados pessoais da conta.
*/
class Conta {
private:
    /**
    * @brief Sao as informacoes da conta, que incluem CPF, Senha, e Nome.
    */
    CPF cpf;
    Nome nome;
    Senha senha;
public:
    //CPF
    void setcpf(const CPF&);
    CPF getcpf() const;
    //Nome
    void setnome(const Nome&);
    Nome getnome() const;
    //Senha
    void setsenha(const Senha&);
    Senha getsenha() const;
};
//set CPF
inline void Conta::setcpf(const CPF &cpf){
    this->cpf = cpf;
}
//get CPF
inline CPF Conta::getcpf() const{
    return cpf;
}
//set Nome
inline void Conta::setnome(const Nome &nome){
    this->nome = nome;
}
//get Nome
inline Nome Conta::getnome() const{
    return nome;
}
//set Senha
inline void Conta::setsenha(const Senha &senha){
    this->senha = senha;
}
//get Senha
inline Senha Conta::getsenha() const{
    return senha;
}


//ENTIDADE TITULO -------------------------------------------------------------------
/**
* @brief Classe concreta Titulo, que contem as informacoes sobre os Titulos da conta.
*/
class Titulo {
private:
    /**
    *@brief Sao os dados sobre  movimentacao e emissoes de titulos da conta.
    Ele incluem Codigo, Emissor, Setor, Emissao, Vencimento e Valor.
    */
    CodTitulo codigo;
    Nome emissor;
    Setor setor;
    Data emissao;
    Data vencimento;
    Dinheiro valor;
public:
    //Codigo de Titulo
    void setcodigo(const CodTitulo&);
    CodTitulo getcodigo() const;
    //Nome do emissor
    void setemissor(const Nome&);
    Nome getemissor() const;
    //Setor
    void setsetor(const Setor&);
    Setor getsetor() const;
    //Data de emissao
    void setemissao(const Data&);
    Data getemissao() const;
    //Data de vencimento
    void setvencimento(const Data&);
    Data getvencimento() const;
    //Valor(Dinheiro)
    void setvalor(const Dinheiro&);
    Dinheiro getvalor() const;
};
//set Codigo de Titulo
inline void Titulo::setcodigo(const CodTitulo &codigo){
    this->codigo = codigo;
}
//get Codigo de Titulo
inline CodTitulo Titulo::getcodigo() const{
    return codigo;
}
//set Nome do Emissor
inline void Titulo::setemissor(const Nome &emissor){
    this->emissor = emissor;
}
//get Nome do Emissor
inline Nome Titulo::getemissor() const{
    return emissor;
}
//set Setor
inline void Titulo::setsetor(const Setor &setor){
    this->setor = setor;
}
//get Setor
inline Setor Titulo::getsetor() const{
    return setor;
}
//set Data de Emissao
inline void Titulo::setemissao(const Data &emissao){
    this->emissao = emissao;
}
//get Data de Emissao
inline Data Titulo::getemissao() const{
    return emissao;
}
//set Data de Vencimento
inline void Titulo::setvencimento(const Data &vencimento){
    this->vencimento = vencimento;
}
//get Data de Vencimento
inline Data Titulo::getvencimento() const{
    return vencimento;
}
//set Valor(Dinheiro)
inline void Titulo::setvalor(const Dinheiro &valor){
    this->valor = valor;
}
//get Valor(Dinheiro)
inline Dinheiro Titulo::getvalor() const{
    return valor;
}


//ENTIDADE PAGAMENTO --------------------------------------------------------------
/**
* @brief Classe concreta, que contem as informacoes sobre os pagamentos realizados pela conta.
*/
class Pagamento {
private:
    /**
    * @brief Trata-se dos dados dos pagamentos realizados.
    Incluem Codigdo de pagamento, Data, Percentual e Estado.
    */
    CodPagamento codigo;
    Data data;
    Percentual percentual;
    Estado estado;
public:
    //CodPagamento
    void setcodigo(const CodPagamento&);
    CodPagamento getcodigo() const;
    //Data
    void setdata(const Data&);
    Data getdata() const;
    //Percentual
    void setpercentual(const Percentual&);
    Percentual getpercentual() const;
    //Estado
    void setestado(const Estado&);
    Estado getestado() const;
};
//set Codigo de Pagamento
inline void Pagamento::setcodigo(const CodPagamento &codigo){
    this->codigo = codigo;
}
//get Codigo de Pagamento
inline CodPagamento Pagamento::getcodigo() const{
    return codigo;
}
//set Data
inline void Pagamento::setdata(const Data &data){
    this->data = data;
}
//get Data
inline Data Pagamento::getdata() const{
    return data;
}
//set Percentual
inline void Pagamento::setpercentual(const Percentual &percentual){
    this->percentual = percentual;
}
//get Percentual
inline Percentual Pagamento::getpercentual() const{
    return percentual;
}
//set Estado
inline void Pagamento::setestado(const Estado &estado){
    this->estado = estado;
}
//get Estado
inline Estado Pagamento::getestado() const{
    return estado;
}

#endif //ENTIDADES_H

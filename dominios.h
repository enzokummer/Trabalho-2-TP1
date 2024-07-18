
#ifndef DOMINIOS_H_INCLUDED
#define DOMINIOS_H_INCLUDED

#include <string>
#include <stdexcept>
#include <regex>
#include <iostream>
#include <ctype.h>
#include <stdio.h>

using namespace std;
/**
 * @brief Classe abstrata para representar os dominios de valores das classes.
 *
 * Esta classe define a interface comum para todas as classes que representam um dominio de valores.
 * Ela fornece metodos para definir e obter o valor do dominio.
 * Todos os metodos fornecidos sao herdados pelas classes do tipo Dominio, com cada uma
 * delas implementando o seu padrao de validacao.
 */
class Dominios {
private:
    string valor;
     /**
        * @brief O valor do objeto do dominio desejado.
        *
        * O valor que o objeto vai receber, que pode varia de acordo com o dominio desejado.
        */
protected:
    /**
         * @brief Verifica se um valor e valido para o dominio.
         * @param valor O valor a ser verificado.
         *
         * Este metodo deve ser implementado pelas classes filhas para verificar se um valor e valido para o dominio.
         * Se o valor nao for valido, o metodo deve lancar uma excecao.
         */
    virtual void validar(string) = 0;
public:
    /**
         * @brief Destrutor virtual da classe Dominios.
         *
         * Este destrutor virtual permite que as classes filhas tenham seus proprios destrutores.
         */
    virtual ~Dominios(){}
    /**
         * @brief Define o valor do domiinio.
         * @param valor O valor a ser definido.
         * @throw invalid_argument Se o valor nAo for valido para o dominio.
         *
         * Este m&todo define o valor do dominio. Ele chama o metodo "verificaValor" para verificar se o valor e valido.
         * Se o valor nao for valido, o metodo lanca uma excecao do tipo "invalid_argument".
         */
    void setValor(string);
    /**
         * @brief Retorna o valor do dominio.
         * @return O valor do dominio.
         *
         * Este metodo retorna o valor do dominio.
         */
    string getValor() const;
};

inline string Dominios::getValor() const{
    return valor;
}
/**
* @brief Classe concreta CodPagamento. Herda metodos da classe abstrata Dominios.
*/
class CodPagamento : public Dominios {
private:
    /**
    * @brief Responsavel pela validacao do valor do objeto.
    */
    void validar(string) override;
};
/**
* @brief Classe concreta CodTitulo. Herda metodos da classe abstrata Dominios.
*/
class CodTitulo : public Dominios {
private:
    /**
    * @brief Responsavel pela validacao do valor do objeto.
    */
    void validar(string) override;
};
/**
* @brief Classe concreta CPF. Herda metodos da classe abstrata Dominios.
*/
class CPF : public Dominios {
private:
    /**
    * @brief Responsavel pela validacao do valor do objeto.
    */
    void validar(string) override;
};
/**
* @brief Classe concreta Data. Herda metodos da classe abstrata Dominios.
*/
class Data : public Dominios {
private:
    bool isBissexto(string);
    void validar(string) override;
};
/**
* @brief Classe concreta Dinheiro. Herda metodos da classe abstrata Dominios.
*/
class Dinheiro : public Dominios {
private:
    void validar(string) override;
};
/**
* @brief Classe concreta Estado. Herda metodos da classe abstrata Dominios.
*/
class Estado : public Dominios {
private:
    void validar(string) override;
};
/**
* @brief Classe concreta Nome. Herda metodos da classe abstrata Dominios.
*/
class Nome : public Dominios {
private:
    void validar(string) override;
};
/**
* @brief Classe concreta Percentual. Herda metodos da classe abstrata Dominios.
*/
class Percentual : public Dominios {
private:
    void validar(string) override;
};
/**
* @brief Classe concreta Senha. Herda metodos da classe abstrata Dominios.
*/
class Senha : public Dominios {
private:
    void validar(string) override;
};
/**
* @brief Classe concreta Setor. Herda metodos da classe abstrata Dominios.
*/
class Setor : public Dominios {
private:
    void validar(string) override;
};
#endif // DOMINIOS_H_INCLUDED

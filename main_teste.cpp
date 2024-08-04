#include <iostream>
#include "dominios.h"
#include "entidades.h"
#include "testes.h"
#include "comandos.h"
#include "controladoras.h"

using namespace std;

int main() {
    ControladoraServicoTitulos controladora;
    Titulo titulo;
    string a;

    cin >> a;
    CodTitulo codigo;
    codigo.setValor(a);

    cin >> a;
    Nome emissor;
    emissor.setValor(a);

    cin >> a;
    Setor setor;
    setor.setValor(a);

    cin >> a;
    Data emissao;
    emissao.setValor(a);

    cin >> a;
    Data vencimento;
    vencimento.setValor(a);

    cin >> a;
    Dinheiro valor;
    valor.setValor(a);

    titulo.setcodigo(codigo);
    titulo.setemissao(emissao);
    titulo.setemissor(emissor);
    titulo.setsetor(setor);
    titulo.setvalor(valor);
    titulo.setvencimento(vencimento);
    
    controladora.criar(titulo);

    return 0;
}
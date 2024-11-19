#pragma once 

#include <iostream>
#include <string>

using namespace std;

class Itens{
  private:
    int quantidade;
    

  public:
    Itens(int quantidade):
    quantidade{quantidade}{}

    int getQuantidade(){
      return quantidade;
    }

    void utilizarItem(){
        quantidade -= 1;
    }

    void recuperarItens(int numero){
      quantidade = numero;
    }

};
#pragma once 

#include <iostream>
#include <unistd.h> //Para "sleep"
#include <string>

using namespace std;

class Ataque{
  private:
    int power;
    int chance;
    string atributo;

  public:
    Ataque(int power, int chance, string atributo):
    power{power}, chance{chance}, atributo{atributo}{}

    int getPower(){
      return power;
    }

    int getChance(){
      return chance*100/127;      
    }

    string getAtributo(){
      return atributo;      
    }

    int Dano(int rand, int atributoAtaque, int atributoDefesa){
      if(rand%126 > chance){
        cout << "E errou!" << endl;
        sleep(1);
        return 0;
      }
      else if(rand%127 == 0){
        cout << "E acertou criticamente!" << endl;
        sleep(1);
        return (((((22*atributoAtaque*power)/atributoDefesa)/50)+2)+rand%11)*1.5;
      }
      else{
        cout << "E acertou!" << endl;
        sleep(1);
        return ((((22*atributoAtaque*power)/atributoDefesa)/50)+2)+rand%11;
      }
    }

};
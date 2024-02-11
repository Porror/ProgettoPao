#include "error.h"

Error::Error(const unsigned int& c):code(c) {}

std::string Error::correspondingString()const{
    if(code==0)return "Tentativo di accesso a container vuoto";
    if(code==1)return "Valore non ammesso";
    if(code==2)return "Valore oltre i limiti";
    if(code==3)return "Errore nell'apertura del file";
    if(code==4)return "Errore nella formattazione del file";

    return "Errore non riconosciuto";
}

int Error::getCode()const{
    return code;
}

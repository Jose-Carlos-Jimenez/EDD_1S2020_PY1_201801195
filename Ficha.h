#ifndef FICHA_H
#define FICHA_H

#include <string>

using namespace std;

class ficha
{
public:
    char letra;
    int puntos;
    ficha():letra(0), puntos(0){};
    ficha(char l, int p):letra(l), puntos(p){};
    string getDatos();
};

string ficha::getDatos()
{
    string dato;
    dato += letra;
    dato += ", ";
    dato += to_string(puntos);
    dato += "pts";
    return dato;
}


#endif // FICHA_H

#ifndef CASILLA_H
#define CASILLA_H
#include <string>
using namespace std;
class Casilla
{
public:
    bool doble;
    bool triple;
    int x, y;
    string letra;
    int valor;
    Casilla():doble(0), triple(0),x(-1), y(-1),letra("-"), valor(0){};
};

#endif // CASILLA_H

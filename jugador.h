#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <listadoblementeenlazada.h>
#include <Ficha.h>
#include <fstream>

using namespace std;


class Jugador
{
public:
    Jugador(string n):nombre(n),puntos(134){};
    string nombre;
    ListaDoblementeEnlazada<ficha> *fichasDisponibles;
    int puntos;
    Jugador()
    {
        this->nombre = "";
        puntos = 0;
        this->fichasDisponibles = new ListaDoblementeEnlazada<ficha>();
    }
    template<typename charT, typename traits>
    friend std::basic_ostream<charT, traits> &
    operator<< (std::basic_ostream<charT, traits> &lhs, Jugador const &rhs) {
        return lhs << rhs.nombre << ','<< ' ' << rhs.puntos;
    }
    void getFichas()
    {
        string ruta = "/home/jose/ReportesEDD/fichas_"+ this->nombre +".dot";
        ofstream file;
        file.open(ruta);
        file << this->fichasDisponibles->getGraph();
        file.close();
        string instruccion = "dot " + ruta + " -o /home/jose/ReportesEDD/fichas_" +nombre + ".png -Tpng";
        system(instruccion.c_str());
        string archivo = "xdg-open /home/jose/ReportesEDD/fichas_"+ this->nombre +".png";
        system(archivo.c_str());
    }
};

#endif // JUGADOR_H

#ifndef COLA_H
#define COLA_H

#include <string>
template <class T>
class NodoCola
{
public:
    NodoCola* siguiente;
    T elemento;
    NodoCola(T x)
    {
        elemento = x;
        siguiente = 0;
    }

};

template <class T>
class Cola
{
public:

    NodoCola<T>* frente;
    NodoCola<T>* final;
    Cola()
    {
        size = 0;
        frente = final = 0;
    };
    int size;
    void borrarCola();
    void insertar(T elemento);
    T quitar();
    T frenteCola() const;
    bool colaVacia() const;
    std::string graph();
    T getAt(int);
    ~Cola()
    {
        Cola<T>::borrarCola();
    }
};

template <class T>
void Cola<T>:: insertar(T elemento)
{
    size++;
    NodoCola<T>* nuevo;
    nuevo = new NodoCola<T>(elemento);
    if(colaVacia())
    {
        frente = nuevo;
    }
    else
    {
        final->siguiente = nuevo;
    }
    final = nuevo;
}

template <class T>
void Cola<T> :: borrarCola()
{
    for (;frente != 0;)
    {
        NodoCola<T>* a;
        a = frente;
        frente = frente -> siguiente;
        delete a;
    }
    final = 0;
}

template <class T>
T Cola<T> :: quitar()
{

     if (colaVacia())
     throw "Cola vacía, no se puede extraer.";
     T aux = frente -> elemento;
     NodoCola<T>* a = frente;
     frente = frente -> siguiente;
     size--;
     delete a;
     return aux;
}

template <class T>
T Cola<T> :: frenteCola()const
{
    if (colaVacia())
    throw "Cola vacía";
    return frente -> elemento;
}

template <class T>
T Cola<T>::getAt(int n)
{
    NodoCola<T> *tmp1 = frente;
    if(n == 0)
    {
        frente = tmp1->siguiente;
        size--;
        return tmp1->elemento;
    }
    NodoCola<T> *tmp2;
    for(int i = 0; i < n - 1; i++)
    {
        tmp1 = tmp1->siguiente;
    }
    tmp2 = tmp1->siguiente;
    tmp1->siguiente = tmp2->siguiente;
    size--;
    return tmp2->elemento;
}


template <class T>
bool Cola<T> :: colaVacia() const
{
    return frente == 0;
}

template <class T>
std::string Cola<T>::graph()
{
    std::string graphviz = "digraph{\n\tnode[shape=box]\n";
    graphviz.append("\t\n\tcolor= green;\n\tgraph[bgcolor = black];node[style = dashed color = yellow fontcolor = white]edge[color = red fontcolor = white]");
    NodoCola<T> *tmp = frente;
    int cont= 0;
    while(tmp != NULL)
    {
        graphviz +="\n\t\"";
        graphviz +=tmp->elemento.letra;
        graphviz +=std::to_string(cont);
        graphviz +="\"[label=\"" ;
        graphviz+=tmp->elemento.getDatos();
        graphviz +="\"];";
        tmp = tmp->siguiente;
        cont++;
    }

    tmp = frente;
    cont = 0;
    while(tmp->siguiente != NULL)
    {
        graphviz +="\n\t\"";
        graphviz +=tmp->elemento.letra ;
        graphviz +=std::to_string(cont);
        graphviz +="\" -> \"";
        graphviz +=tmp->siguiente->elemento.letra;
        graphviz +=std::to_string(cont+1);
        graphviz +="\"";
        tmp = tmp->siguiente;
        cont++;
    }
    graphviz.append("\n}");
    return graphviz;
}

#endif // COLA_H

#define MATRIZDISPERSA_H

#include <iostream>
#include <Ficha.h>

using namespace std;

/*Nodo ortogonal perteneciente a la matriz dispersa*/
template <class T>
struct NodoOrtogonal
{
    int x, y;
    T dato;
    NodoOrtogonal* arriba;
    NodoOrtogonal* abajo;
    NodoOrtogonal* izquierda;
    NodoOrtogonal* derecha;
    NodoOrtogonal(){};
    NodoOrtogonal(T dato, int x, int y)
    {
        this->dato = dato;
        this->x = x;
        this->y = y;
        arriba = abajo = izquierda = derecha = NULL;
    }

    string getId()
    {
        return "X" + to_string(x) + "Y" + to_string(y);
    }
};

/*Lista vertical la cual servirá para los nodos que llevaran datos.*/
template <class T>
struct ListaVertical
{
    NodoOrtogonal<T>* primero;
    NodoOrtogonal<T>* ultimo;
    ListaVertical()
    {
        primero = ultimo = NULL;
    }

    void insertar(NodoOrtogonal<T>* insertar)
    {
        if(this->estaVacia())
        {
            primero = ultimo = insertar;
        }
        else
        {
          if(insertar->y < primero->y)
          {
              insertarFrente(insertar);
          }
          else if(insertar->y > ultimo->y)
          {
              insertarFin(insertar);
          }
          else
          {
              insertarMedio(insertar);
          }
        }
    }

    void eliminar(int y)
    {
        if(!estaVacia())
        {
            if(this->ultimo == this->primero)
            {
                this->ultimo = this->primero = NULL;
            }
            else if(y == primero->y)
            {
                primero = primero->abajo;
            }
            else if(y == ultimo->y)
            {
                ultimo = ultimo->arriba;
            }
            else
            {
                NodoOrtogonal<T> *tmp1 = primero;
                NodoOrtogonal<T> *tmp2;
                while(tmp1->y  != y)
                {
                    tmp1 = tmp1->abajo;
                }
                tmp2 = tmp1->arriba;
                tmp2->abajo = tmp1->abajo;
                tmp1->abajo->arriba = tmp2;
                delete tmp1;
            }
        }
    }

    bool existe(int x, int y)
    {
        NodoOrtogonal<T> *tmp = this->primero;
        while (tmp != NULL)
        {
            if(tmp->x == x && tmp->y == y)
            {
                return  true;
            }
            tmp = tmp->abajo;
        }
        return  false;
    }

    bool estaVacia()
    {
        return primero == NULL;
    }

    void insertarFrente(NodoOrtogonal<T>* inserta)
    {
        primero->arriba= inserta;
        inserta->abajo = primero;
        primero = primero->arriba;
    }

    void insertarFin(NodoOrtogonal<T> *inserta)
    {
        ultimo->abajo = inserta;
        inserta->arriba = ultimo;
        ultimo = ultimo->abajo;
    }

    void insertarMedio(NodoOrtogonal<T> *inserta)
    {
        NodoOrtogonal<T>* temp1;
        NodoOrtogonal<T>* temp2;
        temp1 = primero;
        while(temp1->y < inserta->y)
        {
            temp1 = temp1->abajo;
        }
        temp2 = temp1->arriba;
        temp2->abajo = inserta;
        temp1->arriba = inserta;
        inserta->arriba = temp2;
        inserta->abajo = temp1;
    }

    void recorrer()
    {
        if(!estaVacia())
        {
            NodoOrtogonal<T> * temporal = primero;
            while (temporal != NULL)
            {
                cout << "y: " + to_string(temporal->y) << endl;
                temporal = temporal->abajo;
            }
        }
    }
};

/*Lista Horizontal de la matriz*/
template <class T>
struct ListaHorizontal
{
    NodoOrtogonal<T>* primero;
    NodoOrtogonal<T>* ultimo;
    ListaHorizontal()
    {
        primero = ultimo = NULL;
    }

    void insertar(NodoOrtogonal<T>* insertar)
    {
        if(this->estaVacia())
        {
            primero = ultimo = insertar;
        }
        else
        {
          if(insertar->x < primero->x)
          {
              insertarFrente(insertar);
          }
          else if(insertar->x > ultimo->x)
          {
              insertarFin(insertar);
          }
          else
          {
              insertarMedio(insertar);
          }
        }
    }

    void eliminar(int x)
    {
        if(!estaVacia())
        {
            if(this->primero == this->ultimo)
            {
                primero = ultimo = NULL;
            }
            else if(x == primero->x)
            {
                primero = primero->derecha;
            }
            else if(x == ultimo->y)
            {
                ultimo = ultimo->izquierda;
            }
            else
            {
                NodoOrtogonal<T> *tmp1 = primero;
                NodoOrtogonal<T> *tmp2;
                while(tmp1->y  != x)
                {
                    tmp1 = tmp1->derecha;
                }
                tmp2 = tmp1->izquierda;
                tmp2->derecha = tmp1->derecha;
                tmp1->izquierda->derecha = tmp2;
                delete tmp1;
            }
        }
    }

    bool estaVacia()
    {
        return primero == NULL;
    }

    void insertarFrente(NodoOrtogonal<T>* inserta)
    {
        primero->izquierda= inserta;
        inserta->derecha = primero;
        primero = primero->izquierda;
    }

    void insertarFin(NodoOrtogonal<T> *inserta)
    {
        ultimo->derecha = inserta;
        inserta->izquierda = ultimo;
        ultimo = ultimo->derecha;
    }

    void insertarMedio(NodoOrtogonal<T> *inserta)
    {
        NodoOrtogonal<T>* temp1;
        NodoOrtogonal<T>* temp2;
        temp1 = primero;
        while(temp1->x < inserta->x)
        {
            temp1 = temp1->derecha;
        }
        temp2 = temp1->izquierda;
        temp2->derecha = inserta;
        temp1->izquierda = inserta;
        inserta->izquierda = temp2;
        inserta->derecha = temp1;
    }

    void recorrer()
    {
        if(!estaVacia())
        {
            NodoOrtogonal<T> * temporal = primero;
            while (temporal != NULL)
            {
                cout << "x: " + to_string(temporal->x) << endl;
                temporal = temporal->derecha;
            }
        }
    }


};

/*Nodo que será cabecera, es decir llevará las coordenadas x.*/
template <class T>
struct NodoCabecera
{
public:
    int x;
    NodoCabecera *siguiente;
    NodoCabecera *anterior;
    ListaVertical<T>* columna;

    NodoCabecera(int x)
    {
        this->x = x;
        columna = new ListaVertical<T>();
        siguiente = NULL;
        anterior = NULL;
    }
};

/*Lista que llevará las coordenadas en X.*/
template <class T>
struct Cabeceras
{
    NodoCabecera<T>* primero;
    NodoCabecera<T>* ultimo;

    Cabeceras()
    {
        primero = ultimo = NULL;
    }

    void insertar(NodoCabecera<T>* insertar)
    {
        if(this->estaVacia())
        {
            primero = ultimo = insertar;
        }
        else
        {
          if(insertar->x < primero->x)
          {
              insertarFrente(insertar);
          }
          else if(insertar->x > ultimo->x)
          {
              insertarFin(insertar);
          }
          else
          {
              insertarMedio(insertar);
          }
        }
    }

    bool estaVacia()
    {
        return primero == NULL;
    }

    void insertarFrente(NodoCabecera<T>* inserta)
    {
        primero->anterior= inserta;
        inserta->siguiente = primero;
        primero = primero->anterior;
    }

    void insertarFin(NodoCabecera<T> *inserta)
    {
        ultimo->siguiente= inserta;
        inserta->anterior = ultimo;
        ultimo = ultimo->siguiente;
    }

    void insertarMedio(NodoCabecera<T> *inserta)
    {
        NodoCabecera<T>* temp1;
        NodoCabecera<T>* temp2;
        temp1 = primero;
        while(temp1->x < inserta->x)
        {
            temp1 = temp1->siguiente;
        }
        temp2 = temp1->anterior;
        temp2->siguiente = inserta;
        temp1->anterior = inserta;
        inserta->anterior = temp2;
        inserta->siguiente = temp1;
    }

    void recorrer()
    {
        if(!estaVacia())
        {
            NodoCabecera<T> * temporal = primero;
            while (temporal != NULL)
            {
                cout << "x: " + to_string(temporal->x) << endl;
                temporal = temporal->siguiente;
            }
        }
    }

    bool existe(int x)
    {
        if(estaVacia())
        {
            return false;
        }
        else
        {
            NodoCabecera<T>* temporal = primero;
            while(temporal != NULL)
            {
                if(temporal->x == x)
                {
                    return true;
                }
                temporal = temporal->siguiente;
            }
            return false;
        }
    }

    NodoCabecera<T>* busqueda(int x)
    {
        if(existe(x))
        {
            NodoCabecera<T>* temporal = primero;
            while (temporal->x != x)
            {
                temporal = temporal->siguiente;
            }
            return temporal;
        }
        else
        {
            cout<< "No existe";
            return (new NodoCabecera<T>(-1));
        }
    }

};

/*Nodo que será en las coordenadas X*/
template <class T>
struct NodoLateral
{
    int y;
    NodoLateral *siguiente;
    NodoLateral *anterior;
    ListaHorizontal<T>* fila;

    NodoLateral(int y)
    {
        this->y = y;
        fila = new ListaHorizontal<T>();
        siguiente = NULL;
        anterior = NULL;
    }
};

/*Lista que llevará a los nodos que representan las coordenadas */
template <class T>
struct Laterales
{
    NodoLateral<T>* primero;
    NodoLateral<T>* ultimo;

    Laterales()
    {
        primero = ultimo = NULL;
    }

    void insertar(NodoLateral<T>* insertar)
    {
        if(this->estaVacia())
        {
            primero = ultimo = insertar;
        }
        else
        {
          if(insertar->y < primero->y)
          {
              insertarFrente(insertar);
          }
          else if(insertar->y > ultimo->y)
          {
              insertarFin(insertar);
          }
          else
          {
              insertarMedio(insertar);
          }
        }
    }

    bool estaVacia()
    {
        return primero == NULL;
    }

    void insertarFrente(NodoLateral<T>* inserta)
    {
        primero->anterior= inserta;
        inserta->siguiente = primero;
        primero = primero->anterior;
    }

    void insertarFin(NodoLateral<T> *inserta)
    {
        ultimo->siguiente= inserta;
        inserta->anterior = ultimo;
        ultimo = ultimo->siguiente;
    }

    void insertarMedio(NodoLateral<T> *inserta)
    {
        NodoLateral<T>* temp1;
        NodoLateral<T>* temp2;
        temp1 = primero;
        while(temp1->y < inserta->y)
        {
            temp1 = temp1->siguiente;
        }
        temp2 = temp1->anterior;
        temp2->siguiente = inserta;
        temp1->anterior = inserta;
        inserta->anterior = temp2;
        inserta->siguiente = temp1;
    }

    void recorrer()
    {
        if(!estaVacia())
        {
            NodoLateral<T> * temporal = primero;
            while (temporal != NULL)
            {
                cout << "y: " + to_string(temporal->y) << endl;
                temporal = temporal->siguiente;
            }
        }
    }

    bool existe(int y)
    {
        if(estaVacia())
        {
            cout<< "No existe" << endl;
            return false;
        }
        else
        {
            NodoLateral<T>* temporal = primero;
            while(temporal != NULL)
            {
                if(temporal->y == y)
                {
                    cout<< "Existe" << endl;
                    return true;
                }
                temporal = temporal->siguiente;
            }
            cout<< "No existe" << endl;
            return false;
        }
    }

    NodoLateral<T>* busqueda(int y)
    {
        if(existe(y))
        {
            NodoLateral<T>* temporal = primero;
            while (temporal->y != y)
            {
                temporal = temporal->siguiente;
            }
            return temporal;
        }
        else
        {
            cout<< "No existe";
            return (new NodoLateral<T>(-1));
        }
    }

};

/*>>>>>>>>>>>>>>>>>>>>>>>>>>MATRIZ<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
template <class T>
struct MatrizDispersa
{
    Cabeceras<T>* c;
    Laterales<T>* l;
    int dimension;
    MatrizDispersa()
    {
        c = new Cabeceras<T>();
        l = new Laterales<T>();
    }

    T obtener(int x, int y)
    {
        NodoCabecera<T> *s = c->busqueda(x);
        NodoOrtogonal<T> *aux = s->columna->primero;
        while(aux->y < y)
        {
            aux = aux->abajo;
        }
        return aux->dato;
    }

    void insertar(int x, int y, T insertar)
    {
        NodoOrtogonal<T>*insercion = new NodoOrtogonal<T>(insertar, x, y);
        if(c->existe(x) == false)
        {
            c->insertar(new NodoCabecera<T>(x));
        }
        if(l->existe(y) == false)
        {
            l->insertar(new NodoLateral<T>(y));
        }
        NodoCabecera<T> * Ctemporal = c->busqueda(x);
        NodoLateral<T> * Ltemporal = l->busqueda(y);
        Ctemporal->columna->insertar(insercion);
        Ltemporal->fila->insertar(insercion);
    }

    void eliminar(int x, int y)
    {
        if(c->existe(x))
        {
            NodoCabecera<T> *aux = c->busqueda(x);
            aux->columna->eliminar(y);
            if(aux->columna->estaVacia())
            {
                if(c->ultimo == c->primero)
                {
                    c->ultimo = c->primero = NULL;
                }
                else if(aux == c->primero)
                {
                    if(aux->siguiente)
                    {
                        c->primero = c->primero->siguiente;
                    }
                    else
                    {
                        c->primero = c->ultimo =  NULL;
                    }
                }
                else if(aux == c->ultimo)
                {
                    if(aux->anterior)
                    {
                        c->ultimo =c->ultimo->anterior;
                    }
                    else
                    {
                        c->ultimo = c->primero = NULL;
                    }
                }
                else
                {
                    aux->anterior->siguiente = aux->siguiente;
                    aux->siguiente->anterior = aux->anterior;
                }
            }

        }
        if(l->existe(y))
        {
            NodoLateral<T> *aux = l->busqueda(y);
            aux->fila->eliminar(y);
            if(aux->fila->estaVacia())
            {
                if(l->ultimo == l->primero)
                {
                    l->ultimo = l->primero = NULL;
                }
                else if(aux == l->primero)
                {
                    if(aux->siguiente)
                    {
                        l->primero = l->primero->siguiente;

                    }
                    else
                    {
                        l->primero = l->ultimo = NULL;
                    }
                }
                else if(aux == l->ultimo)
                {
                    if(aux->anterior)
                    {
                        l->ultimo =l->ultimo->anterior;
                    }
                    else
                    {
                        l->ultimo = l->primero = NULL;
                    }
                }
                else
                {
                    aux->anterior->siguiente = aux->siguiente;
                    aux->siguiente->anterior = aux->anterior;
                    delete aux;
                }
            }
        }
    }

    void llenar(int x, int y)
    {
        for(int i = 0; i < y; i++)
        {
            for(int j = 0; j < x; j++)
            {
                insertar(j, i, 0);
            }
        }
    }

    string graphMatrix()
    {
        string graphviz= "digraph{\n\trankdir=TB;\n\tnode[shape=rectangle, height=0.5, width=0.5];\n\tgraph[nodesep=0.5];";
        graphviz.append("color= green;graph[bgcolor = black];node[style = dashed color = yellow fontcolor = white]edge[color = red fontcolor = white]");
        /*DECLARANDO CABECERAS HORIZONTALES Y VERTICALES.*/
        NodoCabecera<T> *auxX = c->primero;
        while(auxX != NULL)
        {
            if(auxX->columna->primero)
            {
                graphviz +="\n\t\"X";
                graphviz +=to_string(auxX->x);
                graphviz +="\"[label=";
                graphviz +="\"X";
                graphviz +=to_string(auxX->x);
                graphviz +="\" group=";
                graphviz +=to_string(auxX->x);
                graphviz +=" color=red];";
            }
            auxX = auxX->siguiente;
        }
        NodoLateral<T> *auxY = l->primero;
        while(auxY != NULL)
        {
            if(auxY != NULL)
            {
                graphviz +="\n\t\"Y";
                graphviz +=to_string(auxY->y);
                graphviz +="\"[label=";
                graphviz +="\"Y";
                graphviz +=to_string(auxY->y);
                graphviz +="\" group=0 color=red];";
            }
            auxY = auxY->siguiente;
        }
        /*DECLARANDO EL NODO PARA QUE REPRESENTA A LOS EJES*/
        graphviz += "\n\t\"0\"[label=\"Y/X\" group=0];";

        /*AHORA DECLARAREMOS LAS CONEXIONES ENTRE LOS NODOS X y LOS Y y EL EJE DE COORDENADAS*/
        //En X:
        auxX = c->primero;
        graphviz +="\n\t\"0\" -> \"X";
        graphviz += to_string(auxX->x);
        graphviz +="\";";
        while(auxX->siguiente != NULL)
        {
            graphviz+= "\n\t\"X";
            graphviz += to_string(auxX->x);
            graphviz +="\" -> ";
            graphviz+= "\"X";
            graphviz += to_string(auxX->siguiente->x);
            graphviz+= "\";";
            auxX = auxX->siguiente;
        }
        //En Y:
        auxY = l->primero;
        graphviz +="\n\t\"0\" -> \"Y";
        graphviz += to_string(auxY->y);
        graphviz +="\";";
        while(auxY->siguiente != NULL)
        {
            graphviz+= "\n\t\"Y";
            graphviz += to_string(auxY->y);
            graphviz +="\" -> ";
            graphviz+= "\"Y";
            graphviz += to_string(auxY->siguiente->y);
            graphviz+= "\";";
            auxY = auxY->siguiente;
        }
        graphviz+="\n\t{rank=same; \"0\";";
        auxX = c->primero;
        while(auxX != NULL)
        {
            graphviz +="\"X";
            graphviz +=to_string(auxX->x);
            graphviz +="\";";
            auxX = auxX->siguiente;
        }
        graphviz+="}";

        /*DECLARANDO LOS NODOS QUE CONTIENEN DATOS*/
        auxX= c->primero;
        while(auxX != NULL)
        {
            NodoOrtogonal<T> *nodoOrt = auxX->columna->primero;
            while(nodoOrt != NULL)
            {
                graphviz +="\n\t\"";
                graphviz += nodoOrt->getId();
                graphviz +="\" [label=\"";
                graphviz +=nodoOrt->dato.letra;
                graphviz +="\" group=";
                graphviz +=to_string(nodoOrt->x);
                graphviz +="];";
                nodoOrt = nodoOrt->abajo;
            }
            auxX = auxX->siguiente;
        }

        /*DECLARANDO LOS NODOS QUE TIENEN CONEXIÓN CON CADA CABECERA*/
        auxX = c->primero;
        while(auxX != NULL)
        {
            graphviz +="\n\t\"X";
            graphviz += to_string(auxX->x);
            graphviz +="\" -> \"";
            graphviz += auxX->columna->primero->getId();
            graphviz +="\";";
            auxX = auxX->siguiente;
        }

        auxY = l->primero;
        while(auxY != NULL)
        {
            graphviz +="\n\t\"Y";
            graphviz += to_string(auxY->y);
            graphviz +="\" -> \"";
            graphviz += auxY->fila->primero->getId();
            graphviz +="\";";
            auxY = auxY->siguiente;
        }
        /*DECLARANDO LAS CONEXIONES DE LOS NODOS CON DATOS*/
        auxX = c->primero;
        while(auxX != NULL)
        {
            NodoOrtogonal<T> *auxNodo = auxX->columna->primero;
            while(auxNodo != NULL)
            {
                if(auxNodo->abajo)
                {
                    graphviz += "\n\t\"";
                    graphviz += auxNodo->getId();
                    graphviz += "\" -> ";
                    graphviz += auxNodo->abajo->getId();
                    graphviz += "[dir=both];";
                }
                auxNodo = auxNodo->abajo;
            }
            auxX = auxX->siguiente;
        }

        auxY = l->primero;
        while(auxY != NULL)
        {
            NodoOrtogonal<T> *auxNodo = auxY->fila->primero;
            while(auxNodo != NULL)
            {
                if(auxNodo->derecha)
                {
                    graphviz += "\n\t\"";
                    graphviz += auxNodo->getId();
                    graphviz += "\" -> ";
                    graphviz += auxNodo->derecha->getId();
                    graphviz += "[dir=both];";
                }
                auxNodo = auxNodo->derecha;
            }
            auxY = auxY->siguiente;
        }

        /*DECLARANDO LOS RANGOS*/
        auxY = l->primero;

        while(auxY != NULL)
        {
            graphviz +="\n\t{rank=same;";
            graphviz +="\"Y";
            graphviz +=to_string(auxY->y);
            graphviz +="\";";
            NodoOrtogonal<T> *auxNodo = auxY->fila->primero;
            while(auxNodo != NULL)
            {
                graphviz +="\"";
                graphviz +=auxNodo->getId();
                graphviz +="\";";
                auxNodo = auxNodo->derecha;
            }
            graphviz +="}";
            auxY = auxY->siguiente;
        }

        graphviz += "\n}";
        return graphviz;
    }
};

#ifndef LISTADOBLEMENTEENLAZADA_H
#define LISTADOBLEMENTEENLAZADA_H

#include <string>
using namespace std;

template <class T>
class NodeLD
{

public:
    /*Atributes*/
    T data;
    NodeLD<T> *next;
    NodeLD<T> *previous;
    int position;

    /*Constructor*/
    NodeLD():next(0), previous(0){};
    NodeLD(T data):next(0),previous(0){this->data = data;};

    /*Methods*/
    T getData();

};

template<class T>
class ListaDoblementeEnlazada
{
public:
    /*Atributes*/
    int lenght;
    NodeLD<T> *head;
    NodeLD<T> *tail;

    /*Constructor*/
    ListaDoblementeEnlazada();

    /*Methods*/
    bool isEmpty();
    void vaciar();
    void insertFirst(T);
    void insertLast(T);
    void insertAt(T,int);
    void deleteFirst();
    void deleteLast();
    string getGraph();
    NodeLD<T> * getNode(int);
};

template <class T>
void ListaDoblementeEnlazada<T>::vaciar()
{
    this->head = 0;
    this->tail = 0;
    lenght = 0;
}

template <class T>
string ListaDoblementeEnlazada<T>::getGraph()
{

    string graph = "digraph D{\n\tnode[shape=LR]\n\trankdir=LR";
    graph.append("\n\tcolor= green;\n\tgraph[bgcolor = black];\n\tnode[style = dashed color = yellow fontcolor = white]\n\tedge[color = red fontcolor = white];");

    if(head != NULL && tail != NULL)
    {
        NodeLD<T> *aux = head;
        int cont = 0;
        while(aux != NULL)
        {
            graph += "\n\t\"";
            graph +=aux->data.letra;
            graph += to_string(cont);
            graph += "\"[label =\"";
            graph +=aux->data.getDatos();
            graph +="\"];";
            cont++;
            aux = aux->previous;
        }
        aux = head;
        cont = 0;
        while(aux->previous != NULL)
        {
            if(aux)
            {
                graph += "\n\t\"";
                graph +=aux->data.letra;
                graph +=to_string(cont);
                graph += "\" -> \"";
                graph += aux->previous->data.letra;
                graph += to_string(cont + 1);
                graph += "\" [dir = both];";
                cont++;
                aux = aux->previous;
            }
        }
    }
    graph+= "\n}";
    return graph;
}

/*Constructor*/
template <class T> ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada()
{
    lenght = 0;
}

/*Verify if list is empty*/
template <class T> bool ListaDoblementeEnlazada<T>::isEmpty()
{
    return this->lenght==0;
}

/*Insert on head of the list*/
template <class T> void ListaDoblementeEnlazada<T>::insertFirst(T value)
{
    NodeLD<T> *newData = new NodeLD<T>(value);
    if(this->isEmpty())
    {
        tail = newData;
        head = newData;
        tail->previous = 0;
        head->next = 0;
    }
    else
    {
        newData->previous = head;
        head->next = newData;
        head = newData;
    }
    lenght++;
}

/*Insert at tail the new node*/
template <class T> void ListaDoblementeEnlazada<T>::insertLast(T value)
{
    NodeLD<T> *newData = new NodeLD<T>(value);
    if(isEmpty())
    {
        head = newData;
    }
    else
    {
        tail->previous = newData;
        newData->next = tail;
    }
    tail = newData;
    lenght++;
    newData->position = lenght;
}

/*Delete a node at the first position*/
template <class T> void ListaDoblementeEnlazada<T>::deleteFirst()
{
    if(!isEmpty())
    {
        NodeLD<T> *tmp = this->head;
        if(head == tail)
        {
            tail = 0;
        }
        else
        {
            head->next->previous = 0;
        }
        head = head->next;
        tmp->next = 0;
        lenght--;
        delete tmp;
    }
}

/*Delete a node at the last position*/
template <class T> void ListaDoblementeEnlazada<T>::deleteLast()
{
    if(!isEmpty())
    {
        NodeLD<T> *tmp = tail;
        if(tail == head)
        {
            head = 0;
        }
        else
        {
            tail->previous->next = 0;
        }
        tail = tail->previous;
        tmp->previous = 0;
        lenght--;
        delete tmp;
    }
}

/*Get a node at n position*/
template <class T> NodeLD<T> * ListaDoblementeEnlazada<T>::getNode(int n)
{
    if(!isEmpty())
    {
        NodeLD<T> *temp = head;
        for(int i = 0 ; i< n ; i++)
        {
            temp = temp->next;
        }
        return  temp;
    }
    return 0;
}

/*Insert a node at n position*/
template <class T> void ListaDoblementeEnlazada<T>::insertAt(T value,int n)
{
    NodeLD<T> *newData = new NodeLD<T>(value);
    NodeLD<T> *aux = getNode(n);
    newData->previous = aux;
    newData->next = aux;
    if(aux->previous == 0)
    {
        head = newData;
    }
    else
    {
        aux->previous->next = newData;
    }
    aux->previous = newData;
}

template <class T>
T NodeLD<T>::getData()
{
    return this->data;
}
#endif // LISTADOBLEMENTEENLAZADA_H

/*IMPORTACIÓN DE LIBRERIAS*/
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <iostream>

/*IMPORTACIÓN DE CLASES PROPIAS*/
#include <arbol.h>
#include <cola.h>
#include <listacirculardoble.h>
#include <matrizdispersa.h>
#include <Casilla.h>
#include <listadoblementeenlazada.h>

using namespace std;

void printMenu()
{
    int heigth, width, start_y, start_x;
    heigth = 23;
    width = 78;
    start_x = 0;
    start_y = 0;
    WINDOW *win = newwin(heigth, width, start_y, start_x);
    refresh();
    box(win,0,0);
    mvwprintw(win, 1, 1, "Proyecto 1, Estructuras de datos, USAC.");
    mvwprintw(win, 3, 1, "1. Jugar.");
    mvwprintw(win, 4, 1, "2. Cargar archivo.");
    mvwprintw(win, 5, 1, "3. Reportes.");
    mvwprintw(win, 6, 1, "4. Añadir jugador.");
    mvwprintw(win, 7, 1, "5. Salir.");
    wrefresh(win);
}

void jsonOpen(QString filename, ListaCircularDoble<string> *diccionario, MatrizDispersa<Casilla> *matriz, string* archivo){
    *archivo = filename.toStdString();
    matriz = new MatrizDispersa<Casilla>();
    diccionario = new ListaCircularDoble<string>();
    matriz->c = new Cabeceras<Casilla>();
    matriz->l = new Laterales<Casilla>();
    QFile file;//Abro un archivo
    QString val;//Creo un valor
    file.setFileName(filename);//Le asigno la ruta
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = d.object();
    matriz->dimension = jsonObject.value(QStringLiteral("dimension")).toInt();
    QJsonObject casillas = jsonObject["casillas"].toObject();
    QJsonArray jsonArray3 = casillas["dobles"].toArray();
    QJsonArray jsonArray4 = casillas["triples"].toArray();//Leer las casillas

    foreach (const QJsonValue & value, jsonArray3) {
        QJsonObject obj = value.toObject();
        Casilla *nueva = new Casilla();
        QJsonArray arrayEvento = obj["dobles"].toArray();//Leer cuales son dobles
        nueva->doble = true;
        nueva->triple = false;
        nueva->x = obj.value(QStringLiteral("x")).toInt();
        nueva->y = obj.value(QStringLiteral("y")).toInt();
        matriz->insertar(nueva->x,nueva->y, *nueva);
    }

    foreach (const QJsonValue & value, jsonArray4) {
        QJsonObject obj = value.toObject();
        QJsonArray arrayEvento = obj["triples"].toArray();//Leer cuales son triples
        Casilla *nueva = new Casilla();
        nueva->doble = false;
        nueva->triple = true;
        nueva->x = obj.value(QStringLiteral("x")).toInt();
        nueva->y = obj.value(QStringLiteral("y")).toInt();
        matriz->insertar(nueva->x,nueva->y, *nueva);
    }

    QJsonArray jsonArray5 = jsonObject["diccionario"].toArray();//Leer las palabras en el diccionario
    qDebug()<< "DICCIONARIO";
    foreach (const QJsonValue & value, jsonArray5) {
        QJsonObject obj = value.toObject();//Lo vuelve un objeto
        QJsonObject palabra = obj["palabra"].toObject();//La palabra la vuelve un objeto
        diccionario->insertarNodo(obj.value(QStringLiteral("palabra")).toString().toStdString());
    }
    return;
}

void jsonRead(QString filename, ListaCircularDoble<string> *diccionario, MatrizDispersa<Casilla> *matriz ){
    QFile file;//Abro un archivo
    QString val;//Creo un valor
    file.setFileName(filename);//Le asigno la ruta
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = d.object();
    matriz->dimension = jsonObject.value(QStringLiteral("dimension")).toInt();
    QJsonObject casillas = jsonObject["casillas"].toObject();
    QJsonArray jsonArray3 = casillas["dobles"].toArray();
    QJsonArray jsonArray4 = casillas["triples"].toArray();//Leer las casillas

    foreach (const QJsonValue & value, jsonArray3) {
        QJsonObject obj = value.toObject();
        Casilla *nueva = new Casilla();
        QJsonArray arrayEvento = obj["dobles"].toArray();//Leer cuales son dobles
        nueva->doble = true;
        nueva->triple = false;
        nueva->x = obj.value(QStringLiteral("x")).toInt();
        nueva->y = obj.value(QStringLiteral("y")).toInt();
        matriz->insertar(nueva->x,nueva->y, *nueva);
    }

    foreach (const QJsonValue & value, jsonArray4) {
        QJsonObject obj = value.toObject();
        QJsonArray arrayEvento = obj["triples"].toArray();//Leer cuales son triples
        Casilla *nueva = new Casilla();
        nueva->doble = false;
        nueva->triple = true;
        nueva->x = obj.value(QStringLiteral("x")).toInt();
        nueva->y = obj.value(QStringLiteral("y")).toInt();
        matriz->insertar(nueva->x,nueva->y, *nueva);
    }

    QJsonArray jsonArray5 = jsonObject["diccionario"].toArray();//Leer las palabras en el diccionario
    foreach (const QJsonValue & value, jsonArray5) {
        QJsonObject obj = value.toObject();//Lo vuelve un objeto
        QJsonObject palabra = obj["palabra"].toObject();//La palabra la vuelve un objeto
        diccionario->insertarNodo(obj.value(QStringLiteral("palabra")).toString().toStdString());
    }
    return;
}

void getFile(ListaCircularDoble<string> *diccionario, MatrizDispersa<Casilla> *matriz, string* pathfile)
{
    int heigth, width, start_y, start_x;
    heigth = 23;
    width = 78;
    start_x = 0;
    start_y = 0;
    WINDOW *win = newwin(heigth, width, start_y, start_x);
    refresh();
    box(win,0,0);
    mvwprintw(win, 1, 1, "Ingrese la ruta del archivo:");
    wrefresh(win);
    string route;
    nocbreak();
    echo();
    move(3,1);
    int ch = getch();
    while ( ch != '\n' )
    {
        route.push_back( ch );
        ch = getch();
        if(ch == 127)
        {
            route.erase(route.length());
        }
    }
    *pathfile= route;
    QString path = QString(route.c_str());
    jsonOpen(path, diccionario, matriz, pathfile);
    clear();
    printMenu();
}


void fillQueue(Cola<ficha> *colaJuego)
{
    Cola<ficha> *cola = new Cola<ficha>();
    for(int i = 1; i <= 95; i++ )
    {
        ficha *nueva = new ficha();
        if(i <= 12)
        {
            nueva->letra = 'a';
            nueva->puntos = 1;
        }
        else if(i <= 24)
        {
            nueva->letra = 'e';
            nueva->puntos = 1;
        }
        else if(i <= 33)
        {
            nueva->letra = 'o';
            nueva->puntos = 1;
        }
        else if(i <= 39)
        {
            nueva->letra = 'i';
            nueva->puntos = 1;
        }
        else if(i <= 45)
        {
            nueva->letra = 's';
            nueva->puntos = 1;
        }
        else if(i <= 50)
        {
            nueva->letra = 'n';
            nueva->puntos = 1;
        }
        else if(i <= 54)
        {
            nueva->letra = 'l';
            nueva->puntos = 1;
        }
        else if(i <= 59)
        {
            nueva->letra = 'r';
            nueva->puntos = 1;
        }
        else if(i <= 64)
        {
            nueva->letra = 'u';
            nueva->puntos = 1;
        }
        else if(i <= 68)
        {
            nueva->letra = 'a';
            nueva->puntos = 1;
        }
        else if(i <= 73)
        {
            nueva->letra = 'd';
            nueva->puntos = 2;
        }
        else if(i <= 75)
        {
            nueva->letra = 'g';
            nueva->puntos = 2;
        }
        else if(i <= 79)
        {
            nueva->letra = 'c';
            nueva->puntos = 3;
        }
        else if(i <= 81)
        {
            nueva->letra = 'b';
            nueva->puntos = 3;
        }
        else if(i <= 83)
        {
            nueva->letra = 'm';
            nueva->puntos = 3;
        }
        else if(i <= 85)
        {
            nueva->letra = 'p';
            nueva->puntos = 3;
        }
        else if(i <= 87)
        {
            nueva->letra = 'h';
            nueva->puntos = 4;
        }
        else if(i == 88 )
        {
            nueva->letra = 'f';
            nueva->puntos = 4;
        }
        else if(i == 89 )
        {
            nueva->letra = 'v';
            nueva->puntos = 4;
        }
        else if(i == 90 )
        {
            nueva->letra = 'y';
            nueva->puntos = 4;
        }
        else if(i == 91 )
        {
            nueva->letra = 'q';
            nueva->puntos = 5;
        }
        else if(i == 92 )
        {
            nueva->letra = 'j';
            nueva->puntos = 8;
        }
        else if(i == 93 )
        {
            nueva->letra = (char)164;
            nueva->puntos = 8;
        }
        else if(i == 94 )
        {
            nueva->letra = 'x';
            nueva->puntos = 8;
        }
        else if(i == 95 )
        {
            nueva->letra = 'z';
            nueva->puntos = 10;
        }
        cola->insertar(*nueva);
    }

    while (cola->size > 0)
    {
        int cont;
        srand(time(NULL));
        cont = rand()%cola->size;
        ficha randomica = cola->getAt(cont);
        colaJuego->insertar(randomica);
    }
}

void addPlayers(Arbol * arbol)
{
    int heigth, width, start_y, start_x;
    heigth = 23;
    width = 78;
    start_x = 0;
    start_y = 0;
    WINDOW *win = newwin(heigth, width, start_y, start_x);
    refresh();
    box(win,0,0);
    mvwprintw(win, 1, 1, "Ingrese el nombre del jugador:");
    wrefresh(win);
    string nombre;
    nocbreak();
    echo();
    move(3,1);
    int ch = getch();
    while ( ch != '\n' )
    {
        nombre.push_back( ch );
        ch = getch();
        if(ch == 127)
        {
            nombre.erase(nombre.length());
        }
    }
    arbol->insertar(arbol->raiz, nombre);
    clear();
    printMenu();
}

void report()
{
    int heigth, width, start_y, start_x;
    heigth = 23;
    width = 78;
    start_x = 0;
    start_y = 0;
    WINDOW *win = newwin(heigth, width, start_y, start_x);
    refresh();
    box(win,0,0);
    mvwprintw(win, 3, 2, "1. Diccionario.");
    mvwprintw(win, 4, 2, "2. Matriz.");
    mvwprintw(win, 5, 2, "3. Cola.");
    mvwprintw(win, 6, 2, "4. Arbol.");
    mvwprintw(win, 7, 2, "5. Arbol preorder.");
    mvwprintw(win, 8, 2, "6. Arbol inorder.");
    mvwprintw(win, 9, 2, "7. Arbol posorder.");
    mvwprintw(win, 10, 2, "8. Regresar.");
    wrefresh(win);
}

void generarArbol(Arbol *arbol)
{
    string ruta = "/home/jose/ReportesEDD/a.dot";
    ofstream file;
    file.open(ruta);
    string grafo = arbol->graphTree(arbol->raiz);
    file << grafo ;
    file.close();
    system("dot /home/jose/ReportesEDD/a.dot -o /home/jose/ReportesEDD/a.png -Tpng");
    system("xdg-open /home/jose/ReportesEDD/a.png");
}

void generarTablero(MatrizDispersa<Casilla> *matriz)
{
    string ruta = "/home/jose/ReportesEDD/Tablero.dot";
    ofstream file;
    file.open(ruta);
    file << matriz->graphMatrix();
    system("dot /home/jose/ReportesEDD/Tablero.dot -o /home/jose/ReportesEDD/Tablero.png -Tpng");

    system("xdg-open /home/jose/ReportesEDD/Tablero.png");
    file.close();
}

void getReport(ListaCircularDoble<string> *diccionario, MatrizDispersa<Casilla> *matriz,
               Cola<ficha>* cola, Arbol *arbol)
{
    bool reportando = true;
    while(reportando)
    {
        report();
        char c = getch();
        if(c == '1')
        {
            string ruta = "/home/jose/ReportesEDD/Diccionario.txt";
            ofstream file;
            file.open(ruta);
            file << diccionario->graphviz();
            system("dot /home/jose/ReportesEDD/Diccionario.txt -o /home/jose/ReportesEDD/Diccionario.png -Tpng");
            system("xdg-open /home/jose/ReportesEDD/Diccionario.png");
            file.close();
        }
        else if(c == '2')
        {
            generarTablero(matriz);
        }
        else if(c == '3')
        {
            string ruta = "/home/jose/ReportesEDD/Cola.txt";
            ofstream file;
            file.open(ruta);
            file << cola->graph();
            system("dot /home/jose/ReportesEDD/Cola.txt -o /home/jose/ReportesEDD/Cola.png -Tpng");
            system("xdg-open /home/jose/ReportesEDD/Cola.png");
            file.close();
        }
        else if(c == '4')
        {
            generarArbol(arbol);
        }
        else if(c == '5')
        {
            string grafo = arbol->graphPreOrder(arbol->raiz);
            string ruta = "/home/jose/ReportesEDD/Arbol_PREORDER.txt";
            ofstream file;
            file.open(ruta);
            file << grafo;
            file.close();
            system("dot /home/jose/ReportesEDD/Arbol_PREORDER.txt -o /home/jose/ReportesEDD/Arbol_PREORDER.png -Tpng");
            system("xdg-open /home/jose/ReportesEDD/Arbol_PREORDER.png");
        }

        else if(c == '6')
        {
            string grafo = arbol->graphInOrder(arbol->raiz);
            string ruta = "/home/jose/ReportesEDD/Arbol_INORDER.txt";
            ofstream file;
            file.open(ruta);
            file << grafo;
            file.close();
            system("dot /home/jose/ReportesEDD/Arbol_INORDER.txt -o /home/jose/ReportesEDD/Arbol_INORDER.png -Tpng");
            system("xdg-open /home/jose/ReportesEDD/Arbol_INORDER.png");
        }

        else if(c == '7')
        {
            string ruta = "/home/jose/ReportesEDD/Arbol_POSORDER.dot";
            ofstream file;
            file.open(ruta);
            file << arbol->graphPosOrder(arbol->raiz);
            file.close();
            system("dot /home/jose/ReportesEDD/Arbol_POSORDER.dot -o /home/jose/ReportesEDD/Arbol_POSORDER.png -Tpng");
            system("xdg-open /home/jose/ReportesEDD/Arbol_POSORDER.png");
        }
        else if(c == '8')
        {
            reportando = false;
        }
    }
};

bool estaen(Jugador j, char letra)
{
    NodeLD<ficha> *tmp = j.fichasDisponibles->head;
    while (tmp != NULL)
    {
        if(tmp->data.letra == letra)
        {
            return  true;
        }
        tmp = tmp->previous;
    }
    return  false;
}

bool sameX(Cola <Casilla> *aux)
{
    NodoCola<Casilla> *tmp = aux->frente->siguiente;
    int val = aux->frente->elemento.x;
    bool iguales = true;
    while(tmp != NULL)
    {
        if(val != tmp->elemento.x)
        {
            iguales = false;
        }
        val = tmp->elemento.x;
        tmp = tmp->siguiente;
    }
    return  iguales;
}

bool sameY(Cola <Casilla> *aux)
{
    NodoCola<Casilla> *tmp = aux->frente->siguiente;
    int val = aux->frente->elemento.y;
    bool iguales = true;
    while(tmp != NULL)
    {
        if(val != tmp->elemento.y)
        {
            iguales = false;
        }
        val = tmp->elemento.y;
        tmp = tmp->siguiente;
    }
    return  iguales;
}

bool getTurno(Jugador *p, Cola<ficha>* fichas, MatrizDispersa<Casilla>* tablero, ListaCircularDoble<string> *diccionario)
{
    clear();
    int heigth, width, start_y, start_x;
    heigth = 23;
    width = 78;
    start_x = 0;
    start_y = 0;
    WINDOW *win = newwin(heigth, width, start_y, start_x);
    refresh();
    box(win,0,0);
    string mensaje = "Es el turno de " + p->nombre;
    mvwprintw(win, 1, 1, mensaje.c_str());
    mvwprintw(win, 3, 1, "1. Hacer jugada.");
    mvwprintw(win, 4, 1, "2. Cambiar fichas.");
    mvwprintw(win, 5, 1, "3. Rendirse.");
    wrefresh(win);

    noecho();
    cbreak();
    char opcion = getch();
    if(opcion == '1')
    {
        Cola<Casilla> *colaTurno = new Cola<Casilla>();

        //Preguntar por piezas a colocar
        bool sigueTurno = true;
        while(sigueTurno)
        {
            clear();
            clear();
            clear();
            clear();
            int heigth, width, start_y, start_x;
            heigth = 23;
            width = 78;
            start_x = 0;
            start_y = 0;
            WINDOW *win = newwin(heigth, width, start_y, start_x);
            refresh();
            box(win,0,0);
            cbreak();
            noecho();
            mvwprintw(win, 1, 1, "Presione \"ESC\" para salir otra tecla para continuar ingresando datos.");
            wrefresh(win);
            char escape= getch();
            if(escape == 27)sigueTurno = false;
            if(sigueTurno)
            {
                mvwprintw(win, 3, 1, "LETRA: ");
                mvwprintw(win, 4, 1, "X: ");
                mvwprintw(win, 5, 1, "Y: ");
                wrefresh(win);
                char letra = getch();
                string let = "";
                let+= letra;
                mvwprintw(win,3,8, let.c_str());
                wrefresh(win);
                string coordenadaX;
                bool ingresando = true;
                while(ingresando)
                {
                    char l = getch();
                    if(l== 9)
                    {

                        break;
                    }
                    coordenadaX+= l;
                }

                string equis = "";
                equis+=coordenadaX;
                mvwprintw(win, 4, 4, equis.c_str());
                wrefresh(win);
                string coordenadaY;
                while (ingresando) {
                    char l = getch();
                    if(l == 9)
                    {
                        break;
                    }
                    coordenadaY += l;
                }
                string ye = "";
                ye+= coordenadaY;
                mvwprintw(win, 5,4,ye.c_str());
                wrefresh(win);
                Casilla *aux = new Casilla();
                aux->x = atoi(coordenadaX.c_str());
                aux->y = atoi(coordenadaY.c_str());
                aux->letra = letra;
                //Si existe en sus opciones ponerla, si no nel.
                if(estaen(*p,letra))
                {
                   //Quitar de la lista
                    NodeLD<ficha> *tmp = p->fichasDisponibles->head;
                    NodeLD<ficha> *tmp2;
                    while(aux->letra[0] != tmp->data.letra)
                    {
                        aux->valor = tmp->data.puntos;
                        tmp = tmp->previous;
                    }
                    if(tmp == p->fichasDisponibles->head)
                    {
                        colaTurno->insertar(*aux);
                        p->fichasDisponibles->head = p->fichasDisponibles->head->previous;
                    }
                    else if(tmp == p->fichasDisponibles->tail)
                    {
                        colaTurno->insertar(*aux);
                        p->fichasDisponibles->tail = p->fichasDisponibles->tail->next;
                    }
                    else
                    {
                        colaTurno->insertar(*aux);
                        tmp2 = tmp->previous;
                        tmp2->next = tmp->next;
                        tmp->next->previous = tmp2;
                        delete tmp;
                    }
                    p->getFichas();
                    if(tablero->c->busqueda(aux->x)->columna->existe(aux->x, aux->y))
                    {
                        NodoOrtogonal<Casilla> *tmp = tablero->c->busqueda(aux->x)->columna->primero;
                        while(tmp->x != aux->x && tmp->y != aux->y && tmp != NULL)
                        {
                            tmp = tmp->abajo;
                        }
                        if(tmp->dato.letra == "-")
                        {
                            tmp->dato.letra = aux->letra;
                            tmp->dato.valor = aux->valor;
                        }
                        else {
                            ficha *recuperada = new ficha(aux->letra[0], aux->valor);
                            p->fichasDisponibles->insertLast(*recuperada);
                        }
                    }
                    else
                    {
                        tablero->insertar(aux->x,aux->y,*aux);
                    }

                    /*CARGAR PANTALLA DE NUEVO*/
                    generarTablero(tablero);
                }

                else
                {
                    cbreak();
                    move(10,10);
                    mvwprintw(win,10,10,"No cuenta con esa letra, seleccione otra");
                    mvwprintw(win,11,10,"Presione una tecla para continuar");
                    wrefresh(win);
                    getch();
                }
            }
        }


        /*VALIDAR LA LETRA*/
        //Ver que se forme una palabra válida
        bool lexemaValido = false;
        if(sameX(colaTurno))
        {
            mvwprintw(win,10,10,"Ingrese Yo");
            move(10,21);
            wrefresh(win);
            string Yo;
            bool ingresando = true;
            while(ingresando)
            {
                char l = getch();
                if(l== 9)
                {

                    break;
                }
                Yo+= l;
            }
            mvwprintw(win,10,21,Yo.c_str());
            mvwprintw(win,11,10,"Ingrese Yf");
            wrefresh(win);
            move(10,21);
            string Yf;
            ingresando = true;
            while(ingresando)
            {
                char l = getch();
                if(l== 9)
                {

                    break;
                }
                Yf+= l;
            }
            mvwprintw(win,11,21,Yf.c_str());
            wrefresh(win);
            //OBTENGO LAS COORDENADAS
            int yinit = atoi(Yo.c_str());
            int yfinal = atoi(Yf.c_str());
            //OBTENGO LA LISTA EN DONDE ESTA;
            NodoOrtogonal<Casilla> * auxiliar = tablero->c->busqueda(colaTurno->frente->elemento.x)->columna->primero;
            string palabra;
            while (auxiliar) {
                if(auxiliar->y >= yinit && auxiliar->y <= yfinal)
                {
                    palabra += auxiliar->dato.letra;
                }
                auxiliar = auxiliar->abajo;
            }

            NodoLCD<string> *diccAux = diccionario->head;
            while (diccAux->sig != diccionario->head) {
                if(diccAux->dato == palabra)
                {
                    lexemaValido= true;
                }
                diccAux = diccAux->sig;
            }
        }
        else if(sameY(colaTurno))
        {
            //¿Forma una palabra en esa columna? Debe incluir todas las posiciones que tenemos.
            mvwprintw(win,10,10,"Ingrese Xo");
            move(10,21);
            string Xo;
            bool ingresando = true;
            while(ingresando)
            {
                char l = getch();
                if(l== 9)
                {

                    break;
                }
                Xo+= l;
            }
            mvwprintw(win,10,21,Xo.c_str());
            mvwprintw(win,11,10,"Ingrese Yf");
            wrefresh(win);
            move(10,21);
            string Xf;
            ingresando = true;
            while(ingresando)
            {
                char l = getch();
                if(l== 9)
                {

                    break;
                }
                Xf+= l;
            }
            mvwprintw(win,11,21,Xf.c_str());
            wrefresh(win);
            //OBTENGO LAS COORDENADAS
            int yinit = atoi(Xo.c_str());
            int yfinal = atoi(Xf.c_str());
            //OBTENGO LA LISTA EN DONDE ESTA;
            NodoOrtogonal<Casilla> * auxiliar = tablero->l->busqueda(colaTurno->frente->elemento.y)->fila->primero;
            string palabra;
            while (auxiliar) {
                if(auxiliar->y >= yinit && auxiliar->y <= yfinal)
                {
                    palabra += auxiliar->dato.letra;
                }
                auxiliar = auxiliar->derecha;
            }

            NodoLCD<string> *diccAux = diccionario->head;
            while (diccAux->sig != diccionario->head) {
                if(diccAux->dato == palabra)
                {
                    lexemaValido= true;
                }
                diccAux = diccAux->sig;
            }
        }
        else
        {
            lexemaValido = false;
        }

        /*SUMAR LOS PUNTOS O REGRESAR LAS FICHAS A LA COLA*/
        if(lexemaValido)
        {

        }
        else
        {
            while(!colaTurno->colaVacia())
            {
                Casilla actual = colaTurno->quitar();
                tablero->eliminar(actual.x, actual.y);
                ficha *regresada = new ficha();
                regresada->letra = actual.valor;
                regresada->puntos = actual.letra[0];
                p->fichasDisponibles->insertLast(*regresada);
            }
        }

        /*RELLENAR LAS FICHAS DEL JUGADOR*/

        while(p->fichasDisponibles->lenght <= 7)
        {
            p->fichasDisponibles->insertLast(fichas->quitar());
        }
        //Colocarlas
        //Verificar que formen una palabra
        //Calcular puntaje y sumarselo al jugador
        //Rellenar fichas del jugador
        return true;
    }
    else if( opcion == '2')
    {
        //Agregar a la cola las fichas que tenga el jugador
        NodeLD<ficha> *tmp = p->fichasDisponibles->head;
        while (tmp != 0)
        {
            fichas->insertar(tmp->data);
            tmp = tmp->previous;
        }
        p->fichasDisponibles->vaciar();
        //Desencolar nuevas para su repertorio
        for(int i= 0; i < 7; i++)
        {
            p->fichasDisponibles->insertLast(fichas->quitar());
        }
        p->getFichas();
        return true;
    }
    else if(opcion == '3')
    {
        return false;
    }
    clear();
    heigth = 23;
    width = 78;
    start_x = 0;
    start_y = 0;
    refresh();
    box(win,0,0);
    mensaje = "Es el turno de " + p->nombre;
    mvwprintw(win, 1, 1, mensaje.c_str());
    mvwprintw(win, 3, 1, "1. Hacer jugada.");
    mvwprintw(win, 4, 1, "2. Cambiar fichas.");
    mvwprintw(win, 5, 1, "3. Rendirse.");
    wrefresh(win);

    return true;
}

void hacerPartida(Jugador *p1, Jugador *p2, MatrizDispersa<Casilla>* tablero, int inicio, Cola<ficha>* fichas, ListaCircularDoble<string> * diccionario)
{
    bool jugando = true;
    p1->getFichas();
    p2->getFichas();
    while(jugando)
    {
        generarTablero(tablero);
        if(inicio == 0)
        {
            jugando = getTurno(p1, fichas,tablero, diccionario);
            inicio = 1;
        }
        else
        {
            jugando = getTurno(p2,fichas,tablero, diccionario);
            inicio = 0;
        }
    }
}

void startPlay(Arbol *arbol, MatrizDispersa<Casilla> *tablero, Cola<ficha> *fichas, ListaCircularDoble<string> *diccionario)
{
    bool play = true;
    while(play)
    {
        Jugador *p1;
        Jugador *p2;
        generarArbol(arbol);//Mostrar jugadores
        clear();
        int heigth, width, start_y, start_x;
        heigth = 23;
        width = 78;
        start_x = 0;
        start_y = 0;
        WINDOW *win = newwin(heigth, width, start_y, start_x);
        refresh();
        box(win,0,0);
        mvwprintw(win, 1, 1, "Ingrese el nombre del jugador 1:");
        wrefresh(win);
        string nombre1;
        nocbreak();
        echo();
        move(3,1);
        int ch = getch();
        while ( ch != '\n' )
        {
            nombre1.push_back( ch );
            ch = getch();
            if(ch == 127)
            {
                nombre1.erase(nombre1.length());
            }
        }
        if(arbol->existe(arbol->raiz,nombre1))
        {
            p1 = arbol->buscar(arbol->raiz, nombre1);
            for(int i = 0; i < 7; i++)
            {
                p1->fichasDisponibles->insertLast(fichas->quitar());
            }
        }
        else
        {
            system("clear");
            cout << "El jugador no existe por favor cree uno." << endl;
            cout << "Presione una tecla para continuar" << endl;
            getch();
            play = false;
            break;
        }
        /*---VERIFICAR QUE EXISTA, SI EXISTE OBTENER, SI NO NOTIFICAR Y REGRESAR A MENU----*/

        refresh();
        box(win,0,0);
        mvwprintw(win, 1, 1, "Ingrese el nombre del jugador 2:");
        wrefresh(win);
        string nombre2;
        nocbreak();
        echo();
        move(3,1);
        ch = getch();
        while ( ch != '\n' )
        {
            nombre2.push_back( ch );
            ch = getch();
            if(ch == 127)
            {
                nombre2.erase(nombre2.length());
            }
        }
        if(arbol->existe(arbol->raiz,nombre2))
        {
            p2 = arbol->buscar(arbol->raiz, nombre2);
            for(int i = 0; i < 7; i++)
            {
                p2->fichasDisponibles->insertLast(fichas->quitar());
            }
        }
        else
        {
            system("clear");
            cout << "El jugador no existe por favor cree uno." << endl;
            cout << "Presione una tecla para continuar" << endl;
            getch();
            play = false;
            break;
        }
        if(p1 != NULL && p2 != NULL)/*------------INICIAR LA PARTIDA DENTRO DE ESTE IF---------------*/
        {
            bool jugando = true;
            while (jugando)
            {
                int heigth, width, start_y, start_x;
                heigth = 23;
                width = 78;
                start_x = 0;
                start_y = 0;
                WINDOW *win = newwin(heigth, width, start_y, start_x);
                refresh();
                box(win,0,0);
                mvwprintw(win, 3, 2, "1. Jugar.");
                mvwprintw(win, 4, 2, "2. Abandonar partida.");
                wrefresh(win);
                noecho();
                cbreak();
                char opcion = getch();
                if(opcion == '1')
                {
                    srand(time(NULL));
                    int random= 0;
                    random = rand()%2;
                    hacerPartida(p1,p2,tablero,random,fichas, diccionario);
                }
                else if(opcion == '2')
                {
                    system("clear");
                    break;
                }
                else
                {
                    wclear(win);
                }

            }

        }
        break;
        clear();
    }
}

int main()
{
    ListaCircularDoble<string> *diccionario = new  ListaCircularDoble<string>();
    MatrizDispersa<Casilla> *matriz = new  MatrizDispersa<Casilla>();
    Cola<ficha> *colaJuego = new  Cola<ficha>();
    Arbol *arbol = new Arbol();
    fillQueue(colaJuego);
    string archivo;

    initscr();
    bool play = true;
    while(play)
    {
        noecho();
        cbreak();
        clear();
        printMenu();
        char option = getch();        
        if(option == '1')
        {//Jugar
            jsonRead(archivo.c_str(),diccionario,matriz);
            startPlay(arbol, matriz, colaJuego, diccionario);
        }
        else if( option == '2')
        {//Cargar archivo JSON
            getFile(diccionario, matriz, &archivo);
        }
        else if( option == '3')
        {//Reportes
            getReport(diccionario,matriz,colaJuego,arbol);
        }
        else if(option == '4')
        {//Agregar nuevos jugadores
            addPlayers(arbol);
        }
        else if( option == '5')
        {//Salir
            clear();
            play = false;
        }
        clear();
        printMenu();
    }
    endwin();


    return 0;
}

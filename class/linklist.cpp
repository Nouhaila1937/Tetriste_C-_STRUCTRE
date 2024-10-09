#include "node.cpp"
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;
Sound sound_del;
int scor;
class linkedlist
{
public: 
    node *head;
    node *tail;
    int nombe_node;

    linkedlist()
    {
        head = NULL;
        tail = NULL;
        nombe_node = 0;
        scor = 0;
    }

    //===================
    void remplir()
    {
        node *node_creat;
        node_creat = new node;
        this->head = node_creat;

        for (int i = 0; i < 5; i++)
        {

            node_creat->data = *generer_Piece();

            if (i != 4)
            {

                node_creat->next = new node; // allocation dynamique pour supprimer la valeur null apres l'affictation
                node_creat = node_creat->next;
            }

            nombe_node++;
        }

        node_creat->next = head;
        tail = node_creat;
    }

    //======================
    Piece *generer_Piece()
    {

        char letters[] = {'L', 'R', 'C', 'T'};
        int index = rand() % 4;
        int y = rand() % 4 + 1;
        char letter = letters[index];
        Piece *p = new Piece;
        p->forme = letter;
        p->couleur = y;
        return p;
    }

    //=======================================
    void affiche(RenderWindow *window, Piece *pg, Text timeText, Sprite *bg /*, Sprite iconC*/, Sprite sc, Text sctext)
    {
        node *temp;
        temp = head;
        int siz = 20;
        sctext.setString(to_string(scor));

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(*bg);
        window->draw(timeText);
        // window->draw(iconC);
        window->draw(sc);
        window->draw(sctext);
        switch (pg->forme)
        {
        case 'C':
            window->draw(pg->creat_circle(25, 130));
            break;

        case 'T':
            window->draw(pg->creat_triangle(25, 130));
            break;

        case 'R':
            window->draw(pg->creat_square(25, 130));
            break;

        case 'L':
            window->draw(pg->creat_diamond(25, 130));
            break;
        }
        siz = 20;
        for (int i = 0; i < nombe_node; i++)
        {

            Piece p;
            p = temp->data;
            switch (p.forme)
            {
            case 'C':
                // circle
                window->draw(p.creat_circle(siz));
                break;
            case 'T':
                // triangle
                window->draw(p.creat_triangle(siz));
                break;
            case 'L':
                window->draw(p.creat_diamond(siz));
                break;
            case 'R':

                window->draw(p.creat_square(siz));
                break;
            }
            siz += 120;
            temp = temp->next;
        }
        window->display();
    }

    //========================
    // void insertdebut(Piece p)
    // {
    //     node *new_node = new node;
    //     new_node->data = p;
    //     new_node->next = head;
    //     tail->next = new_node;
    //     head = new_node;
    //     nombe_node++;
    // }

    //========================
    // void insertfin(Piece p)
    // {
    //     node *new_node = new node;
    //     new_node->data = p;
    //     new_node->next = head;
    //     tail->next = new_node;
    //     tail = new_node;
    //     nombe_node++;
    // }

    //========================
void insertdebut(Piece p)
    {
        node *new_node = new node;
        new_node->data = p;
        if(nombe_node != 0){
            
            new_node->next = head;
            tail->next = new_node;
            head = new_node;

        }else{

            head=new_node;
            head->next=new_node;
            tail=new_node;
            tail->next=new_node;

        }

        nombe_node++;
        
    }

    //========================
    void insertfin(Piece p)
    {
        node *new_node = new node;
        new_node->data = p;

        if(nombe_node != 0){
            
            new_node->next = head;
            tail->next = new_node;
            tail = new_node;

        }else{

            head=new_node;
            head->next=new_node;
            tail=new_node;
            tail->next=new_node;

        }

        nombe_node++;
    }

    //---------------------------
    void supprimer_par_coul()
    {
        node *temp;
        node *prev;
        temp = head;
        int cl = head->data.couleur;
        do
        {

            if (cl == temp->next->data.couleur && cl == temp->next->next->data.couleur)
            {

                node *node_next;
                node_next = temp->next->next->next;

                if (temp == head)
                {

                    head = node_next;
                    tail->next = head;
                    nombe_node -= 3;
                    scor+=2;
                    break;
                }

                if (temp->next->next == tail)
                {

                    prev->next = head;
                    tail = prev;
                    nombe_node -= 3;
                    scor+=2;
                    break;
                }
            }

            prev = temp;
            temp = temp->next;
            cl = temp->data.couleur;
        } while (temp != head);
    }

    void supprimer_par_forme()
    {
        node *temp;
        node *prev;
        temp = head;
        int form = head->data.forme;
        do
        {

            if (form == temp->next->data.forme && form == temp->next->next->data.forme)
            {

                node *node_next;
                node_next = temp->next->next->next;

                if (temp == head)
                {

                    head = node_next;
                    tail->next = head;
                    nombe_node -= 3;
                    scor+=2;
                    break;
                }

                if (temp->next->next == tail)
                {

                    prev->next = head;
                    tail = prev;
                    nombe_node -= 3;
                    scor+=2;
                    break;
                }
            }

            prev = temp;
            temp = temp->next;
            form = temp->data.forme;
        } while (temp != head);
    }
}; 
class linkedlistcolor
{
    linkedlist l[4];
    node *head;
    int n;

public:
    void insertPiece(node *p)
    {
        int index = 0; // Initialiser ? -1 pour indiquer qu'aucune couleurorrespondante n'a ?t? trouv?e
        int i = 1;
        switch (p->data.couleur)
        {
        // Comparer les cha?nes de caract?res ASCII pour d?terminer l'index
        case 1:
            index = 0;
            break; // Rouge
        case 2:
            index = 1;
            break;
        case 3:
            index = 2;
            break;
        case 4:
            index = 3;
            break;
        default:
            return;
        }
        // Ins?rer la pi?ce dans la liste correspondante
        if (l[index].head == NULL)
        {

            l[index].head = p;
            l[index].tail = p;
            l[index].nombe_node++;
        }

        if (l[index].head != NULL)
        {

            node *last = l[index].tail;
            last->next_f = p;
            p->prev_forme = last;
            p->next_f = l[index].head;
            l[index].tail = p;
            l[index].nombe_node++;
        }
    }

    void creatlistcolor(linkedlist *existingList)
    {

        node *temp = existingList->head;
        this->head = existingList->head;
        this->n = existingList->nombe_node;
        do
        {

            insertPiece(temp);
            temp = temp->next;

        } while (temp != existingList->head);
    }

    void shiftLeftForColor(int i, linkedlist *h)
    {

        if (l[i].head != NULL && l[i].head->next_f != NULL)
        { // Assurez-vous qu'il y a plus d'un ?l?ment

            node *last = l[i].tail;
            node *lis = l[i].head;
            Piece ld = l[i].head->data;

            for (int j = 0; j < l[i].nombe_node - 2; j++)
            {

                node *next = lis->next_f;

                lis->data = next->data;

                lis = lis->next_f;
            }

            last->data = ld;
        }
        // h->supprimer_par_coul();
        // h->supprimer_par_forme();
    }
};

class linkedlistforme
{

    linkedlist l[4];
    node *head;
    int n;

public:
    void insertPiece(node *p)
    {
        int index;
        int i = 1;

        switch (p->data.forme)
        {
        case 'C':
            index = 0;
            break;
        case 'T':
            index = 1;
            break;
        case 'L':
            index = 2;
            break;
        case 'R':
            index = 3;
            break;
        default:
            return; // Formee non reconnue, ne faire rien
        }

        if (l[index].head == NULL)
        {

            l[index].head = p;
            l[index].tail = p;
            l[index].nombe_node++;
        }

        if (l[index].head != NULL)
        {

            node *last = l[index].tail;
            last->next_f = p;
            p->prev_forme = last;
            p->next_f = l[index].head;
            l[index].tail = p;
            l[index].nombe_node++;
        }
    }

    //=================================
    void creatlistformee(linkedlist *existingList)
    {

        node *temp = existingList->head;
        this->head = existingList->head;
        this->n = existingList->nombe_node;
        do
        {

            insertPiece(temp);
            temp = temp->next;

        } while (temp != existingList->head);
    }

    //==================================
    void shiftLeftForShapes(int i, linkedlist *h)
    {

        if (l[i].head != NULL && l[i].head->next_f != NULL)
        { // Assurez-vous qu'il y a plus d'un ?l?ment
            node *last = l[i].tail;
            node *lis = l[i].head;
            Piece ld = l[i].head->data;
            for (int j = 0; j < l[i].nombe_node - 2; j++)
            {
                node *next = lis->next_f;

                lis->data = next->data;

                lis = lis->next_f;
            }

            last->data = ld;
        }
        // h->supprimer_par_coul();
        // h->supprimer_par_forme();
    }
};

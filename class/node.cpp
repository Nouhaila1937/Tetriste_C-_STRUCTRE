#include<iostream>
#include "piece.cpp"

class node
{

public:
    Piece data;
    node *next;
    node *prev_forme; // le node qui a le meme forme
    node *next_f;     //  le node qui a le meme couleur node()

    node()
    {
        next = NULL;
        prev_forme = NULL; //  this return the adresse of the objet
        next_f = NULL;
    }
};
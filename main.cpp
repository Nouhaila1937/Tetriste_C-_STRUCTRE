#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include "class/linklist.cpp"
#include <fstream>

using namespace sf;
using namespace std;

int getClickedShapeIndex(RenderWindow &window)
{
    int sectionWidth = window.getSize().x / 8; // Largeur de chaque section

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f worldPos = window.mapPixelToCoords(mousePos);

                    // Calculer l'index de la section cliquée en fonction de sa position en x
                    int clickedSectionIndex = worldPos.x / sectionWidth;
                    return clickedSectionIndex;
                }
            }
        }
    }
    return -1; // Si aucun clic n'est détecté ou si la fenêtre est fermée
}

char return_lett(linkedlist l, int clickedShapeIndex)
{

    node *p;
    p = l.head;
    if (clickedShapeIndex == 0)
    {
        return p->data.forme;
    }
    else
    {

        for (int i = 0; i < clickedShapeIndex; i++)
        {
            p = p->next;
        }

        return p->data.forme;
    }
}

int return_index(char let)
{

    int index;

    switch (let)
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
        return -1; // Formee non reconnue, ne faire rien
    }
    return index;
}

int return_color(linkedlist l, int clickedShapeIndex)
{

    node *p;
    p = l.head;
    if (clickedShapeIndex == 0)
    {
        return p->data.couleur;
    }
    else
    {
        for (int i = 0; i < clickedShapeIndex; i++)
        {
            p = p->next;
        }

        return p->data.couleur;
    }
}

int return_index_color(char color)
{

    int index;
    switch (color)
    {
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
        return -1;
    }
    return index;
}
bool shiftByColor = false;
bool shiftByShape = false;

void handleShiftChoice(int choice)
{
    switch (choice)
    {
    case 1:
        shiftByColor = true;
        shiftByShape = false;
        cout << "Shift choice: Color" << endl;
        break;
    case 2:
        shiftByColor = false;
        shiftByShape = true;
        cout << "Shift choice: Shape" << endl;
        break;
    default:
        cout << "Invalid choice" << endl;
        break;
    }
}
// Fonction pour sauvegarder le score dans un fichier
void saveScore(int score)
{
    ofstream file("score.txt", ios::app); // Ouvrir le fichier en mode append
    if (file.is_open())
    {
        file << score << "\n"; // Ajouter un saut de ligne après chaque score pour les séparer
        file.close();
        cout << "Score sauvegardé avec succès.\n";
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier pour l'écriture.\n";
    }
}

// Fonction pour charger le score à partir d'un fichier
int loadScore()
{
    ifstream file("score.txt");
    int score = 0;
    int highestScore = 0;

    if (file.is_open())
    {
        while (file >> score)
        {
            // Compare le score actuel avec le plus grand score trouvé jusqu'à présent
            if (score > highestScore)
            {
                highestScore = score;
            }
        }
        file.close();
        cout << "Score le plus élevé chargé avec succès.\n";
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier pour la lecture.\n";
    }
    return highestScore;
}

int main()

{
    srand(time(0));
    linkedlist l = linkedlist();
    bool ch_l = 0, ch_r = 0;
    Piece *p;
    // scor=0;
    RenderWindow window(VideoMode(1000, 600), "SFML Formes Aléatoires");
    l.remplir();
    char t, lett;
    int i, col, index;
    p = l.generer_Piece();

    //===================== audio ========================
    // SoundBuffer dele;
    // if (!dele.loadFromFile("audio/delete.wav"))
    // {
    //     cout << "error";
    // }
    // sound_del.setBuffer(dele);

    //=====================================================

    // Création de la fenêtre sans spécifier les paramètres de contexte
    //
    SoundBuffer buffer;
    if (!buffer.loadFromFile("audio/start.wav"))
    {
        cout << "error";
    }
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // Charger la police spécifique
    Font font;
    if (!font.loadFromFile("font-family/BIG.otf"))
    {
        cerr << "Erreur lors du chargement de la police." << endl;
        return 1;
    }

    Font font2;
    if (!font2.loadFromFile("font-family/ARC.TTF"))
    {
        cerr << "Erreur lors du chargement de la police." << endl;
        return 1;
    }

    // Charger l'image de fond
    Texture backgroundTexture;
    Texture backgroundTextur2;
    Texture game_over;
    Texture game_scro;
    Vector2u windowSize = window.getSize();

    //======================= image start ===================
    if (!backgroundTexture.loadFromFile("image/start.jpg"))
    {
        std::cerr << "Erreur lors du chargement de l'image de fond." << std::endl;
        return -1;
    }

    Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(float(windowSize.x) / backgroundTexture.getSize().x, float(windowSize.y) / backgroundTexture.getSize().y);

    //=======================================================

    //======================= image game over ===================
    if (!game_over.loadFromFile("image/game_over.jpg"))
    {
        cerr << "Erreur lors du chargement de l'image de fond." << endl;
        return -1;
    }

    Sprite gameO(game_over);
    gameO.setScale(float(windowSize.x) / game_over.getSize().x, float(windowSize.y) / game_over.getSize().y);

    //=======================================================

    Sprite Sc(game_scro);

    //=======================================================

    //===================== image of game= ==================
    if (!backgroundTextur2.loadFromFile("image/bg2.jpg"))
    {
        std::cerr << "Erreur lors du chargement de l'image de fond." << std::endl;
        return -1;
    }
    Sprite backgrounG(backgroundTextur2);
    backgrounG.setScale(float(windowSize.x) / backgroundTextur2.getSize().x, float(windowSize.y) / backgroundTextur2.getSize().y);

    //=======================================================

    //====================== test scoll ========================
    Text ScolTex;
    ScolTex.setFont(font2);
    ScolTex.setCharacterSize(25);
    ScolTex.setFillColor(Color::White);
    ScolTex.setPosition(320, 43);

    //========================================================

    // Texte pour afficher le temps
    Text timeText;
    timeText.setFont(font2);
    timeText.setCharacterSize(25);
    timeText.setFillColor(Color::White);
    timeText.setPosition(652, 43); // Position en haut à gauche de la fenêtre

    // Initialisation du Clock
    Clock gameClock;
    int remainingSeconds = 60; // Démarre à 1 minute

    bool gameStarted = false;

    // Déclaration et initialisation des textes pour les options de menu
    Text playText;
    playText.setFont(font); // Utiliser la police chargée
    playText.setString("Jouer");
    playText.setCharacterSize(90);
    playText.setFillColor(Color::White);
    playText.setPosition(410, 250);

    Text quitText;
    quitText.setFont(font); // Utiliser la police chargée
    quitText.setString("Quitter");
    quitText.setCharacterSize(90);
    quitText.setFillColor(Color::Cyan);
    quitText.setPosition(380, 330);

    // Déclaration et initialisation du titre
    // Text Titre;
    // Titre.setFont(font); // Utiliser la police chargée
    // Titre.setString("Tetriste");
    // Titre.setCharacterSize(130);
    // Titre.setFillColor(Color::White);
    // Titre.setPosition(280, 100);

    // Création des rectangles pour les boutons
    RectangleShape colorButton(Vector2f(200, 50));
    colorButton.setPosition(50, 50);
    colorButton.setFillColor(Color::Blue);

    RectangleShape shapeButton(Vector2f(200, 50));
    shapeButton.setPosition(50, 150);
    shapeButton.setFillColor(Color::Red);
    // Boucle du menu
    while (!gameStarted && window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f worldPos = window.mapPixelToCoords(mousePos);
                    // Obtenir l'index de la forme cliquée
                    int clickedShapeIndex = getClickedShapeIndex(window);
                    // Afficher un message dans la console en fonction de la forme cliquée
                    // Appeler la fonction de décalage avec l'index obtenu

                    if (playText.getGlobalBounds().contains(worldPos))
                    {
                        // L'utilisateur a cliqué sur "Jouer"
                        cout << "Lancement du jeu..." << endl;
                        gameStarted = true;
                    }
                    else if (quitText.getGlobalBounds().contains(worldPos))
                    {
                        // L'utilisateur a cliqué sur "Quitter"
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite); // Dessiner l'image de fond en premier
        // window.draw(Titre);
        window.draw(playText);
        window.draw(quitText);
        window.display();
    }

    // Si le jeu a commencé, afficher les formes
    if (gameStarted)
    {

        // Boucle principale du jeu
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
                else if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        Vector2i mousePos = Mouse::getPosition(window);
                        Vector2f worldPos = window.mapPixelToCoords(mousePos);

                        // Obtenir l'index de la forme cliquée
                        int clickedShapeIndex = getClickedShapeIndex(window);

                        // Si la touche 's' est pressée, faire quelque chose
                        if (Keyboard::isKeyPressed(Keyboard::S))
                        {
                            switch (clickedShapeIndex)
                            {
                            case 0:
                                lett = return_lett(l, clickedShapeIndex);
                                index = return_index(lett);
                                break;
                            case 1:
                                lett = return_lett(l, clickedShapeIndex);
                                index = return_index(lett);
                                break;
                            case 2:
                                lett = return_lett(l, clickedShapeIndex);
                                index = return_index(lett);
                                break;
                            case 3:
                                lett = return_lett(l, clickedShapeIndex);
                                index = return_index(lett);
                                break;
                            case 4:
                                lett = return_lett(l, clickedShapeIndex);
                                index = return_index(lett);
                                break;
                            case 5:
                                lett = return_lett(l, clickedShapeIndex);
                                index = return_index(lett);
                                break;
                            case 6:
                                lett = return_lett(l, clickedShapeIndex);
                                index = return_index(lett);
                                break;
                            case 7:
                                lett = return_lett(l, clickedShapeIndex);
                                index = return_index(lett);
                                break;
                            }
                            linkedlistforme List;
                            List.creatlistformee(&l);
                            List.shiftLeftForShapes(index, &l);
                        }
                        // Sinon, si la touche 'c' est pressée, faire autre chose
                        else if (Keyboard::isKeyPressed(Keyboard::C))
                        {

                            switch (clickedShapeIndex)
                            {
                            case 0:
                                col = return_color(l, clickedShapeIndex);
                                i = return_index_color(col);
                                break;
                            case 1:
                                col = return_color(l, clickedShapeIndex);
                                i = return_index_color(col);
                                break;
                            case 2:
                                col = return_color(l, clickedShapeIndex);
                                i = return_index_color(col);
                                break;
                            case 3:
                                col = return_color(l, clickedShapeIndex);
                                i = return_index_color(col);
                                break;
                            case 4:
                                col = return_color(l, clickedShapeIndex);
                                i = return_index_color(col);
                                break;
                            case 5:
                                col = return_color(l, clickedShapeIndex);
                                i = return_index_color(col);
                                break;
                            case 6:
                                col = return_color(l, clickedShapeIndex);
                                i = return_index_color(col);
                                break;
                            case 7:
                                col = return_color(l, clickedShapeIndex);
                                i = return_index_color(col);
                                break;
                            }
                            linkedlistcolor colorList;
                            colorList.creatlistcolor(&l);
                            colorList.shiftLeftForColor(i, &l);
                        }
                    }
                }
                else if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::R)
                    {
                        ch_r = 1;
                    }
                    else if (event.key.code == Keyboard::L)
                    {
                        ch_l = 1;
                    }
                }
            }

            // Décrémente le temps toutes les secondes
            if (gameClock.getElapsedTime().asSeconds() >= 1)
            {
                gameClock.restart();
                remainingSeconds--;
                // Ajout de 10 points au score lorsque le temps est écoulé à 0:30
                if (remainingSeconds == 54)
                {
                    scor += 30;
                }
                if (scor == 32)
                {
                    remainingSeconds += 10;
                }
            }

            // Mettre à jour le texte pour afficher le temps écoulé

            int minutes = remainingSeconds / 60;
            int seconds = remainingSeconds % 60;
            string timeString = to_string(minutes) + " " + (seconds < 10 ? "0" : " ") + to_string(seconds);
            timeText.setString(timeString);

            // Dans la boucle principale du jeu, après avoir affiché les formes
            // Vérifiez si le nombre total de pièces atteint 8
            if (l.nombe_node >= 10 || remainingSeconds == 0)
            {
                // Affichage de l'écran "Game Over"
                window.clear();
                SoundBuffer buffer;
                if (!buffer.loadFromFile("audio/game_over.wav"))
                {
                    cout << "error";
                }
                Sound sound;
                sound.setBuffer(buffer);
                sound.play();

                // Affichage de l'écran "Game Over" dans la fenêtre existante
                window.draw(gameO);
                // Exemple d'appel à saveScore
                saveScore(scor);

                // Exemple d'appel à loadScore
                int loadedScore = loadScore();
                //  cout << "Score chargé : " << loadedScore << endl;

                ScolTex.setPosition(538, 420); // Position du texte du score
                ScolTex.setString(to_string(loadedScore));
                ScolTex.setFillColor(sf::Color(33, 239, 128)); // RGB pour une couleur rose

                window.draw(ScolTex);
                window.display();

                // Attendre un peu avant de fermer la fenêtre
                sf::sleep(sf::seconds(5));

                // Fermer la fenêtre du jeu
                window.close();
                break; // Sortir de la boucle du jeu
            }

            // Affichage des formes générées
            l.affiche(&window, p, timeText, &backgrounG, /*iconCl ,*/ Sc, ScolTex);

            // Gestion des déplacements des formes
            if (ch_r)
            {
                cout << "right" << endl;
                l.insertfin(*p);
                p = l.generer_Piece();
                ch_r = 0;
                l.supprimer_par_coul();
                l.supprimer_par_forme();
            }
            if (ch_l)
            {
                cout << "left" << endl;
                l.insertdebut(*p);
                p = l.generer_Piece();
                ch_l = 0;
                l.supprimer_par_coul();
                l.supprimer_par_forme();
            }

            window.display();
        }
    }

    return 0;
}

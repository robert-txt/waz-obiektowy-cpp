#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Snake.hpp"

class Game
{
    public:
        Game();
        virtual ~Game();

        //Szerokosc i wysokosc okna.
        static const int Height = 600;
        static const int Width = 800;

        void Run(); // Uruchomienie gry.
        void HandleInputs(); // Pobranie klawiszy
        bool Update(); // Uaktualnianie stanu gry
        void Draw(); // Rysowwanie na ekranie

    private:
        static const sf::Time TimePerFrame;
        sf::RenderWindow gWindow;
        Snake snake;
        sf::RectangleShape food;
};


#endif // GAME_H_INCLUDED


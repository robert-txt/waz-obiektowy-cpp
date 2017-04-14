#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>//2.0
#include <vector>

enum class Directions
{
    LEFT, RIGHT, UP, DOWN
};

class Snake
{
    public:
        Snake();
        virtual ~Snake();
        void Draw(sf::RenderWindow &window);
        bool Update();
        void HandleInputs();
        bool FoodColision(sf::RectangleShape food);
        bool isFoodOnBody(sf::FloatRect fR);

        static const int Height = 20;
        static const int Width = 20;
    private:
        //wektor czesci weza
        std::vector<sf::RectangleShape> nodes;
        Directions direction;
        void Move();
        void Grow();
        bool OwnColision() const;
        void PlaySound();
};

#endif // SNAKE_H


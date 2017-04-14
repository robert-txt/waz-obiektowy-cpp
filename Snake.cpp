#include "Snake.hpp"
#include <SFML/Audio.hpp>

Snake::Snake() : direction(Directions::DOWN)
{
    nodes.push_back(sf::RectangleShape(sf::Vector2f(Snake::Height, Snake::Width)));
    nodes[0].setPosition(100, 100);
}

void Snake::Move()
{
    for(int i = nodes.size()-1; i > 0; --i)
    {
        nodes[i].setPosition(nodes[i-1].getPosition());
    }
    switch(direction)
    {
        case Directions::UP:
            nodes[0].move(0, -Snake::Width);
        break;

        case Directions::DOWN:
            nodes[0].move(0, Snake::Width);
        break;

        case Directions::LEFT:
            nodes[0].move(-Snake::Height, 0);
        break;

        case Directions::RIGHT:
            nodes[0].move(Snake::Height, 0);
        break;
    }
}

void Snake::HandleInputs()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != Directions::DOWN)
    {
        direction = Directions::UP;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != Directions::UP)
    {
        direction = Directions::DOWN;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != Directions::LEFT)
    {
        direction = Directions::RIGHT;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != Directions::RIGHT)
    {
        direction = Directions::LEFT;
    }
}

bool Snake::Update()
{
    if(OwnColision())
    {
        return false;
    }
    Move();
    return true;
}

void Snake::Draw(sf::RenderWindow &window)
{
    for(auto node : nodes)
    {
        window.draw(node);
    }

}

void Snake::Grow()
{
    //dodawanie elementu do konca weza
    nodes.push_back(sf::RectangleShape(sf::Vector2f(Snake::Height,Snake::Width)));
}

// jesli glowa natrafi na jedzenie to waz urosnie
bool Snake::FoodColision(sf::RectangleShape food)
{
    sf::RectangleShape head = nodes[0];
    sf::FloatRect head_pos = head.getGlobalBounds();
    sf::FloatRect _food = food.getGlobalBounds();
    if(head_pos.intersects(_food))
    {
        Grow();
        PlaySound();
        return true;
    }
    return false;
}

//czy jedzenie nie lezy na wezu
bool Snake::isFoodOnBody(sf::FloatRect fR)
{
    for(auto &node : nodes)
    {
        sf::FloatRect tmp = node.getGlobalBounds();
        if(tmp == fR)
        return true;
    }
    return false;
}

bool Snake::OwnColision() const
{
    sf::RectangleShape head = nodes[0];
    sf::FloatRect head_pos = head.getGlobalBounds();
    sf::FloatRect tmp;
    for(int i = nodes.size()-1; i > 0; --i)
    {
        tmp = nodes[i].getGlobalBounds();
        if(head_pos.intersects(tmp))
        {
            return true;
        }
    }
    return false;
}

void Snake::PlaySound()
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile("eat.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
}

Snake::~Snake()
{

}

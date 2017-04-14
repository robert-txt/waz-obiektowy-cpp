#include "Game.hpp"
#include <random>
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

Game::Game() :
    gWindow(sf::VideoMode(Game::Width, Game::Height), "Snake")
{
    gWindow.setFramerateLimit(60);
    //Ustawianie parametrow weza
    food.setSize(sf::Vector2f(20, 20));
    food.setPosition(400, 400);
    food.setFillColor(sf::Color::Green);
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(gWindow.isOpen())
    {

        sf::Time delta = clock.restart();
        timeSinceLastUpdate += delta;

        HandleInputs();
        while (timeSinceLastUpdate > Game::TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            Update();
        }

        Draw();
    }
}

void Game::HandleInputs()
{
    sf::Event event;
    while(gWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            gWindow.close();
        }
    }
    snake.HandleInputs();
}

bool Game::Update()
{
    //jesli zjadl jedzenie
    if(snake.FoodColision(food))
    {
        sf::Vector2f movement;
        sf::RectangleShape tmp(sf::Vector2f(Snake::Width, Snake::Height));
        std::default_random_engine engine; // inicjowanie liczb pseudolosowych
        engine.seed(time(NULL)); //jakis ziarno do losowania
        do
        {
            //losowanie z rozkladu jednostajnego wspolrzednych tak, zeby nie wyjechaly za ekran
            std::uniform_int_distribution<int> x(0, Game::Width/Snake::Width-1);
            std::uniform_int_distribution<int> y(0, Game::Height/Snake::Height-1);
            movement.x = x(engine) * 20;
            movement.y = y(engine) * 20;
            //pomocniczej zmiennej tmp przypisujemy wylosowane wspolrzdne
            //i w warunku petli sprawdzamy czy aby te wylosowane wspolrzedne nie przecinaja z wezem
            tmp.setPosition(movement);
        } while(snake.isFoodOnBody(tmp.getGlobalBounds()));
        //przypisujemy nowa pozycje
        food.setPosition(movement);
    }
    //jezli snake.Update zwraca true, to game.Update tez zwraca true.
    return(snake.Update()) ? true : false;
}

void Game::Draw()
{
    gWindow.clear();
    snake.Draw(gWindow);
    gWindow.draw(food);
    gWindow.display();
}

Game::~Game()
{

}

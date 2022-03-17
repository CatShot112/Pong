#include <SFML/Graphics.hpp>

#ifdef _DEBUG
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif

int main(int argc, char* argv[]) {
    sf::RenderWindow Window(sf::VideoMode(800, 600), "Pong");
    Window.setVerticalSyncEnabled(false);
    Window.setFramerateLimit(60);
    
    sf::RectangleShape Player1(sf::Vector2f(20, 100));
    sf::RectangleShape Player2(sf::Vector2f(20, 100));
    Player1.setOrigin(10, 50);
    Player2.setOrigin(10, 50);
    Player1.setPosition(10, 300);
    Player2.setPosition(790, 300);
    
    sf::RectangleShape Ball(sf::Vector2f(20, 20));
    Ball.setOrigin(10, 10);
    Ball.setPosition(400.0f, 400.0f);
    
    sf::Font Font;
    Font.loadFromFile("data/Pong.ttf");
    
    sf::Text Score("", Font);
    Score.setCharacterSize(64);
    Score.setOrigin(94, 0);
    Score.setPosition(400, 0);
    
    float ballX = 3;
    float ballY = 5;
    float p1Speed = 1;
    float p2Speed = 1;
    float currentSpeed = 1;
    
    unsigned int Player1Score = 0;
    unsigned int Player2Score = 0;
    
    char score[128] = { 0 };
    
    while (Window.isOpen()) {
        sf::Event Event;
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                Window.close();
        }
    
        Ball.move(ballX * currentSpeed, ballY * currentSpeed);
    
        // Player 1 scored.
        if (Ball.getPosition().x + 10 >= 800) {
            Player1Score++;
            p1Speed += 0.05f;
            currentSpeed = p2Speed;
            Ball.setPosition(400.0f, 300.0f);
        }
        // Player 2 scored.
        else if (Ball.getPosition().x - 10 <= 0) {
            Player2Score++;
            p2Speed += 0.05f;
            currentSpeed = p1Speed;
            Ball.setPosition(400.0f, 300.0f);
        }
    
        // Bounce ball top/bottom.
        if (Ball.getPosition().y + 10 >= 600 || Ball.getPosition().y - 10 <= 0)
            ballY = -ballY;

        // Bounce ball from player 1.
        if (Ball.getGlobalBounds().intersects(Player1.getGlobalBounds())) {
            ballX = -ballX;
            currentSpeed = p2Speed;
        }
        // Bounce ball from player 2.
        else if (Ball.getGlobalBounds().intersects(Player2.getGlobalBounds())) {
            ballX = -ballX;
            currentSpeed = p1Speed;
        }
    
        // Player 1 input.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            Player1.move(0, -4 * p1Speed);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            Player1.move(0, 4 * p1Speed);
    
        // Player 2 input.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            Player2.move(0, -4 * p2Speed);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            Player2.move(0, 4 * p2Speed);
    
        // Player 1 bounds limit.
        if (Player1.getPosition().y + 50 >= 600)
            Player1.setPosition(10, 550);
        else if (Player1.getPosition().y - 50 <= 0)
            Player1.setPosition(10, 50);
    
        // Player 2 bounds limit.
        if (Player2.getPosition().y + 50 >= 600)
            Player2.setPosition(790, 550);
        else if (Player2.getPosition().y - 50 <= 0)
            Player2.setPosition(790, 50);
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            Window.close();
    
        // Update score.
        if (Player1Score < 10)
            sprintf_s(score, "  %d | %d", Player1Score, Player2Score);
        else
            sprintf_s(score, " %d | %d", Player1Score, Player2Score);

        Score.setString(score);
    
        Window.clear();
    
        Window.draw(Player1);
        Window.draw(Player2);
        Window.draw(Ball);
        Window.draw(Score);
    
        Window.display();
    }

    return 0;
}

#include <SFML/Graphics.hpp>

int main() {
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
    Font.loadFromFile("Pong.ttf");
    
    sf::Text Score("", Font);
    Score.setCharacterSize(64);
    Score.setOrigin(94, 0);
    Score.setPosition(400, 0);
    
    float ballX = 3;
    float ballY = 5;
    float speed = 1;
    
    unsigned int Player1Score = 0;
    unsigned int Player2Score = 0;
    
    char score[128] = { 0 };
    
    while (Window.isOpen()) {
        sf::Event Event;
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) Window.close();
        }
    
        Ball.move(ballX * ballSpeed, ballY * ballSpeed);
    
        if (Ball.getPosition().x + 10 >= 800) {
            Player1Score++;
            speed += 0.05f;
            Ball.setPosition(400.0f, 300.0f);
        }
        else if (Ball.getPosition().x - 10 <= 0) {
            Player2core++;
            speed += 0.05f;
            Ball.setPosition(400.0f, 300.0f);
        }
    
        if (Ball.getPosition().y + 10 >= 600 || Ball.getPosition().y - 10 <= 0) ballY = -ballY;
        if (Ball.getGlobalBounds().intersects(Player1.getGlobalBounds()) || Ball.getGlobalBounds().intersects(Player2getGlobalBounds())) ballX = -ballX;
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) Player1.move(0, -4 * speed);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) Player1.move(0, 4 * speed);
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Player2.move(0, -4 * speed);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Player2.move(0, 4 * speed);
    
        if (Player1.getPosition().y + 50 >= 600) Player1.setPosition(10, 550);
        else if (Player1.getPosition().y - 50 <= 0) Player1.setPosition(10, 50);
    
        if (Player2.getPosition().y + 50 >= 600) Player2.setPosition(790, 550);
        else if (Player2.getPosition().y - 50 <= 0) Player2.setPosition(790, 50);
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Window.close();
    
        if (Player1Score < 10) sprintf_s(score, "  %d | %d", Player1Score, Player2Score);
        else sprintf_s(score, " %d | %d", Player1Score, Player2Score);
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

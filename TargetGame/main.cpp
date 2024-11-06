#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// g++ -o main main.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

// cd Desktop/Beginner/TargetGame/TargetGame

using namespace sf;
using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_LENGTH 480

int main () {
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_LENGTH), "Target Game");
    window.setFramerateLimit(60);
    
    CircleShape hoop; // define hoop
    int dir = 0;
    hoop.setRadius(50.f);
    hoop.setFillColor(Color::Black);
    hoop.setOutlineThickness(2.f);
    hoop.setOutlineColor(Color::Blue);
    hoop.setPosition(Vector2f(0.f, 20.f));
    
    CircleShape ball;
    bool isShot = false;
    ball.setRadius(20.f);
    ball.setFillColor(Color::Red);
    ball.setPosition(Vector2f(0.f, SCREEN_LENGTH - ball.getRadius()*3));
    
    while (window.isOpen()) {
        
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        
        // Update
        //Update Hoop
        if(hoop.getPosition().x <= 0) {
            dir = 1;
        } else if (hoop.getPosition().x + hoop.getRadius()*2 >= SCREEN_WIDTH){
            dir = 0;
        }
        
        if (dir == 0) {
            hoop.move(-5.f, 0.f);
        } else {
            hoop.move(5.f, 0.f);
        }
        
        //UpdateBall
        if (Mouse::isButtonPressed(Mouse::Left)) {
            isShot = true;
        }
        if (!isShot) {
            ball.setPosition(Mouse::getPosition(window).x, ball.getPosition().y);
        } else {
            ball.move(0, -5.f);
        }
        
        // Collision ball
        if (ball.getPosition().y <= 0 || ball.getGlobalBounds().intersects(hoop.getGlobalBounds())) {
            isShot = false;
            ball.setPosition(ball.getPosition().x, SCREEN_LENGTH - ball.getRadius()*3);
        }
        
       
        
        window.clear(Color::White);
        
        //Draw
        window.draw(hoop);
        window.draw(ball);
        window.display();
    }
    
    return 0;
}

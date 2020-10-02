#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// #include <SFML/RectangleShape.hpp>

using namespace std;

bool checkCollision(sf::RectangleShape shape1, sf::RectangleShape shape2)
{
	sf::FloatRect rect1 = shape1.getGlobalBounds();
	sf::FloatRect rect2 = shape2.getGlobalBounds();

	if (rect1.intersects(rect2))
		return true;
	else
		return false;
}

sf::RectangleShape createPaddle()
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(20, 100));
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(5);
	
	return rectangle;
}

sf::RectangleShape createBall()
{
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(20,20));
	ball.setOutlineColor(sf::Color::White);
	ball.setOutlineThickness(5);

	return ball;
}

int main()
{
    	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Clone");

	sf::RectangleShape player = createPaddle();
	player.setPosition(10,250);

	sf::RectangleShape opponent = createPaddle();
	opponent.setPosition(770,250);

	int ballPosY = rand() % 580;

	sf::RectangleShape ball = createBall();
	ball.setPosition(390,float(ballPosY));

	int ballVelX = 1;
	int ballVelY = 1;

    	// run the program as long as the window is open
    	while (window.isOpen())
    	{
		window.clear();
		window.draw(player);
		window.draw(opponent);
		window.draw(ball);
		window.display();
	        // check all the window's events that were triggered since the last iteration of the loop
        	sf::Event event;
        	while (window.pollEvent(event))
        	{
        	    // "close requested" event: we close the window
	        	if (event.type == sf::Event::Closed)
		 		window.close();
				
			if ((event.key.code == sf::Keyboard::W) && (player.getPosition().y > 0))
				player.move(0.f, -5.f);

			if ((event.key.code == sf::Keyboard::S) && (player.getPosition().y < 500))
				player.move(0.f, 5.f);
        	}

		ball.move(float(ballVelX), float(ballVelY));
		if ((opponent.getPosition().y > 0) || (ballVelY > 0))
			opponent.move(0.f, float(ballVelY));
		if ((opponent.getPosition().y < 500) || (ballVelY < 0))
			opponent.move(0.f, float(ballVelY));
		// player.move(0.f, float(ballVelY));

		if (checkCollision(player, ball))
		{
			ballVelX *= -1;
			ballVelY *= -1;
		}

		else if (checkCollision(opponent, ball))
		{
			ballVelX *= -1;
			ballVelY *= -1;
		}

		if ((ball.getPosition().x < 0) || (ball.getPosition().x > 780))
		{
			ball.setPosition(390,290);
			ballPosY = rand() % 580;
			ball.setPosition(390,float(ballPosY));
			ballVelX *= -1;
			ballVelY *= -1;
		} 

		if ((ball.getPosition().y < 20) || (ball.getPosition().y > 580))
			ballVelY *= -1;
    	}

    	return 0;
}

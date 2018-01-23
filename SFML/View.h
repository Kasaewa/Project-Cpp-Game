#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void getplayercoordinateforview(float x, float y) { 
	float tempX = x; float tempY = y;

	//if (x < 200) tempX = 200;
	//if (y < 240) tempY = 240;
	//if (y > 554) tempY = 554;	

	view.setCenter(tempX + 100, tempY);

}


void viewmap(float time) { 


	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view.move(0.1*time, 0);
		}
	
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view.move(-0.1*time, 0);
	}
	
	/*else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		view.move(0, 0)
	}
	*/
}



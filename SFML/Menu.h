#include "SFML/Graphics.hpp"

void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("image/111.png");
	
	menuTexture3.loadFromFile("image/333.png");
	
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	
	menu3.setPosition(100, 150);

	
	while (isMenu)
	{
		menu1.setColor(Color::White);
		
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(139, 69, 19));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color(210, 105, 30)); menuNum = 1; }
		
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color(210, 105, 30)); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		
		window.draw(menu1);
		
		window.draw(menu3);

		window.display();
	}
	
}
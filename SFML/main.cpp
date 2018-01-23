#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "map.h"
#include "Menu.h"
#include <sstream>
#include "mission.h"


using namespace sf;
using namespace std;

int ground = 400;
float offsetX = 0; 
float offsetY = 300;
//bool showMissionText = true;


class PLAYER {

public:
	float dx, dy;
	FloatRect rect;
	String File;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	Image image;
	Texture texture;
	int playerScore, health;
	bool life;

	Image map_image;
	Texture map;
	Sprite maps;
	

	

	PLAYER(String F, float X, float Y, float w, float h)
	{
		
		File = F;
		rect.width = w; rect.height = h;
		image.loadFromFile(File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		rect.left = X; rect.top = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dx = dy = 0;
		currentFrame = 0;
		playerScore = 0, health = 100; 
		life = true;
	}


	void update(float time, String * TileMap)
	{
		rect.left += dx * time;
		Collision(0,TileMap);

		if (!onGround) dy = dy + 0.0005*time;
		rect.top += dy*time;
		onGround = false;
		Collision(1, TileMap);

		currentFrame += 0.005*time;
		if (rect.top > ground) { rect.top = ground; dy = 0; onGround = true; }

		if (currentFrame > 4) currentFrame -= 4;
		if (dx > 0) sprite.setTextureRect(IntRect(56 * int(currentFrame), 0, 56, 75));
		if (dx < 0) sprite.setTextureRect(IntRect(56 * int(currentFrame) + 56, 0, -56, 75));
		

		sprite.setPosition(rect.left - offsetX, rect.top);
		
		dx = 0;
		if (health <= 0) { life = false; dx = dy = 0; }

	}
	
	void Collision(int num, String * TileMap)
	{

		for (int i = rect.top / 32; i<(rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j<(rect.left + rect.width) / 32; j++)
			{
				if ((TileMap[i][j] == 'B') || (TileMap[i][j] == '0'))
				{
					if (dy>0 && num == 1)
					{
						rect.top = i * 32 - rect.height;  dy = 0;   onGround = true;
					}
					if (dy<0 && num == 1)
					{
						rect.top = i * 32 + 32;   dy = 0;
					}
					if (dx>0 && num == 0)
					{
						rect.left = j * 32 - rect.width;
					}
					if (dx<0 && num == 0)
					{
						rect.left = j * 32 + 32;
					}
				}
				if (TileMap[i][j] == 's') {
					playerScore++;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'h') {
					health += 20;
					TileMap[i][j] = ' ';
				}

			
			}
		cout << "gracz " << rect.left << " " << rect.top << endl;
	}

	void draw(String * TileMap,RenderWindow *w) {
		
		map_image.loadFromFile("map.png");
		map.loadFromImage(map_image);
		maps.setTexture(map);
		
		for (int i = 0; i < Heigh; i++)
			for (int j = 0; j < Width; j++)
			{
				if (TileMap[i][j] == 'B') maps.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0') maps.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == ' ') maps.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's') maps.setTextureRect(IntRect(96, 0, 32, 32));
				if (TileMap[i][j] == 'h') maps.setTextureRect(IntRect(128, 0, 32, 32));
				if (TileMap[i][j] == 'T') maps.setTextureRect(IntRect(160, 0, 32, 32));
				if (TileMap[i][j] == 'L') maps.setTextureRect(IntRect(192, 0, 32, 32));
				if (TileMap[i][j] == 'K') maps.setTextureRect(IntRect(224, 0, 32, 32));
				if (TileMap[i][j] == 'Y') maps.setTextureRect(IntRect(256, 0, 32, 32));
				if (TileMap[i][j] == 'U') maps.setTextureRect(IntRect(288, 0, 32, 32));
				if (TileMap[i][j] == 'I') maps.setTextureRect(IntRect(320, 0, 32, 32));

				maps.setPosition(j * 32 - offsetX, i * 32);
				w->draw(maps);
			}
	}
	
	float getplayercoordinateX() {
		return rect.left;
	}
	float getplayercoordinateY() {
		return rect.top;
	}
};

class ENEMY
{

public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	bool life;
	

	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 32, 32);

		dx = 0.05;
		currentFrame = 0;
		life = true;
	}

	void update(float time, String *TileMap)
	{
		rect.left += dx * time;

		Collision(TileMap);


		currentFrame += time * 0.005;
		if (currentFrame > 2) currentFrame -= 2;

		sprite.setTextureRect(IntRect(18 * int(currentFrame), 0, 16, 16));
		if (!life) sprite.setTextureRect(IntRect(58, 0, 16, 16));


		sprite.setPosition(rect.left - offsetX, rect.top);

	}


	void Collision(String *TileMap)
	{

		for (int i = rect.top / 32; i<(rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j<(rect.left + rect.width) / 32; j++)
				if ((TileMap[i][j] == 'B') || (TileMap[i][j] == '0'))
				{
					if (dx>0)
					{
						rect.left = j * 32 - rect.width; dx *= -1;
					}
					else if (dx<0)
					{
						rect.left = j * 32 + 32;  dx *= -1;
					}
				}
		cout << "idzie x i y " << rect.left << " " << rect.top << endl;
	}

};



int main()
{
	RenderWindow window(VideoMode(600, 600), "Game");
	menu(window);
	
	
	Texture tileSet;
	tileSet.loadFromFile("tileset.png");
	ENEMY  enemy;
	enemy.set(tileSet, 19 * 32, 13*32);

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 15);
	Text text1("", font, 15);
	Text text2("", font, 65);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text2.setStyle(sf::Text::Bold | sf::Text::Underlined);


	bool showMissionText = true;
	float currentFrame = 0;
	PLAYER p("spire.png", 40, 100, 56, 75);

	
	Clock clock;

	randomMapGenerate(TileMap1);
	randomMapGenerate(TileMap2);


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return false; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return true; }

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		std::ostringstream playerScoreString;
		playerScoreString << p.playerScore;
		std::ostringstream playerHealthString;
		playerHealthString << p.health;
		text.setString("Zebrano:" + playerScoreString.str());
		text.setPosition(500, 35);

		text1.setString("Zdrowie:" + playerHealthString.str());
		text1.setPosition(500, 55);

		window.clear(Color(128, 106, 89));
		
		//wyjasnic

		
		if (p.rect.left > 300) offsetX = p.rect.left - 600 / 2;

		if ((getCurrentMission(p.getplayercoordinateX())) == 0) //LEVEL 1
		{
			p.update(time, TileMap1);
			p.draw(TileMap1, &window);
			enemy.update(time, TileMap1);
		}

		if ((getCurrentMission(p.getplayercoordinateX())) >= 1) // LEVEL 2
		{
			p.update(time, TileMap2);
			p.draw(TileMap2, &window);
			//enemy.update(time, TileMap2);
		}
		

		if (p.rect.intersects(enemy.rect))
		{
			if (enemy.life) {
				if (p.dy>0) { enemy.dx = 0; p.dy = -0.2; enemy.life = false; }
				else { p.health -= 40, enemy.dx *= -1; };
			}
		}
		if (p.life)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{p.dx = -0.1;}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{p.dx = 0.1;}

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{if (p.onGround) { p.dy = -0.4; p.onGround = false;}}
		}



		if (p.life == false)
		{
			text1.setString("Game over");
			text1.setPosition(100, 250);
			window.draw(text2);
		}

		window.draw(enemy.sprite);
		window.draw(p.sprite);
		window.draw(text);
		window.draw(text1);
		window.display();
	}

	return 0;
}
#include <SFML\Graphics.hpp>
int getCurrentMission(int x)//ф-ция номера миссия, которая меняет номер миссии, в зависимости от координаты игрока Х (сюда будем передавать эту координату)
{
	int mission = 0;
	if ((x > 0) && (x < 1110)) { mission = 0;  } //знакомим игрока с игрой
	if ((x >= 1110)) { mission = 1; }
	//if (x>700) { mission = 2; }//2ой
	//if (x>2200) { mission = 3; }//и тд

	return mission;//ф-ция возвращает номер миссии
}




std::string getTextMission(int currentMission) {

	std::string missionText = "";//текст миссии и его инициализация

	switch (currentMission)//принимается номер миссии и в зависимости от него переменной missionText присваивается различный текст
	{
	case 0: missionText = "\n blabla и \n blabla"; break;
	case 1: missionText = "\nMission 1\n\nblabla\n blabla\n blabla \nblabla\n blabla"; break;
	//case 2: missionText = "\nMission 2\n blabla\n blabla\n blabla "; break;
	//case 3: missionText = "\nblabla \nblabla"; break;
	}

	return missionText;//ф-ция возвращает текст
}; 

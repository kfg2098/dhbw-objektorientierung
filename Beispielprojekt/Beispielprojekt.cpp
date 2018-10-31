#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Planet.h"
#include "Vektor2d.h"

#include <cstdint>
#include <memory>
#include <cassert>
#include <cinttypes>
#include <forward_list>
#include <algorithm>
#include <ctime>
using namespace std;
// Simulationsgeschwindigkeit
const double DT = 100.0;

int windowheight =900;
int windowwidth = 1600;
int pos_kontrolle_y(int i);
int pos_kontrolle_x(int i);

//---------------------------------------------------------------------------------

class GameWindow : public Gosu::Window
{
//-----------------------Globale Variablen----------------
	double x = 0;
	double y = 0;
	bool space = false;
	bool hoch = false;
	bool runter = false;
	bool rechts = false;
	bool links = false;
	int pos_p1_x = 0;
	int pos_p1_y = 0;
	int pos_p2_x = 1600;
	int pos_p2_y = 900;
	const int speed = 5;

//-------------------------------------------------------
public:
	Gosu::Image bild, bild_hg;
	//Gosu::Font font;
	GameWindow()
		: Window(windowwidth, windowheight)
		, bild("Kack.png"), bild_hg("Hintergrund.png")
		//,font(20)
		
	{
		set_caption("Keller is coming!");

	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	
	
	void draw() override
	{
		bild.draw_rot(pos_p1_x+bild.width()/2, pos_p1_y+bild.height()/2, 0.0,
			0,//Rotationswinkel
			0.5, 0.5, //Position der "Mitte" in realtiv zu x,y -->0|0 ist oben links 0.5|0.5 ist mitte des Bildes
			0.5,0.4 //Verh�ltnis zum Kleiner machen 0.4= 40% des Urspr�nglichen
		);

		bild_hg.draw_rot(0, 0, -10, 0, 0, 0);
		

		
	};

	

	


	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		x = input().mouse_x();
		y = input().mouse_y();

		//Tastenabfrage
		if (input().down(Gosu::ButtonName::KB_ESCAPE))//schlie�t, wenn ESC gedr�ckt wurde
		{ 
			close();
		}
		//Steuerung Spieler Dozent
		if (input().down(Gosu::ButtonName::KB_UP))
		{
			pos_p1_y = pos_p1_y - speed;
			pos_kontrolle_y(pos_p1_y);
		}
		if (input().down(Gosu::ButtonName::KB_DOWN))
		{
			pos_p1_y = pos_p1_y + speed;
			pos_kontrolle_y(pos_p1_y);
		}
		if (input().down(Gosu::ButtonName::KB_LEFT))
		{
			pos_p1_x = pos_p1_x - speed;
			pos_kontrolle_x(pos_p1_x);
		}
		if (input().down(Gosu::ButtonName::KB_RIGHT))
		{
			pos_p1_x = pos_p1_x + speed;
			pos_kontrolle_x(pos_p1_x);
		}
		//Steuerung Spieler Student
		if (input().down(Gosu::ButtonName::KB_UP))
		{
			pos_p2_y = pos_p2_y - speed;
			pos_kontrolle_y(pos_p2_y);
		}
		if (input().down(Gosu::ButtonName::KB_DOWN))
		{
			pos_p2_y = pos_p2_y + speed;
			pos_kontrolle_y(pos_p2_y);
		}
		if (input().down(Gosu::ButtonName::KB_LEFT))
		{
			pos_p2_x = pos_p2_x - speed;
			pos_kontrolle_x(pos_p2_x);
		}
		if (input().down(Gosu::ButtonName::KB_RIGHT))
		{
			pos_p2_x = pos_p2_x + speed;
			pos_kontrolle_x(pos_p2_x);
		}
		//
		/*
		space = input().down(Gosu::KB_SPACE); //Abfrage ob Space gedr�ckt ist, wenn ja siehe draw Methode
		hoch = input().down(Gosu::KB_UP);
		runter = input().down(Gosu::KB_DOWN);
		rechts = input().down(Gosu::KB_RIGHT);
		links = input().down(Gosu::KB_K); //LEFT*/
		
	};
	
};




// C++ Hauptprogramm
int main()
{
	
	
	
	GameWindow window;
	window.show();
}

//Postitionskontrolle
int pos_kontrolle_x(int i) {
	if (i < 0) {
		i = i + 5;
		return i;
	}
	if (i > 1600) {
		i = i - 5;
		return i;
	}
}
int pos_kontrolle_y(int i) {
	if (i < 0) {
		i = i + 5;
		return i;
	}
	if (i > 900) {
		i = i - 5;
		return i;
	}
	else { return i; }
}
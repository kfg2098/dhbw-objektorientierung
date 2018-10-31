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

const int windowheight = 900;
const int windowwidth = 1600;

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(windowwidth, windowheight)
		,bild("Hintergrund.png") 
		
	{
		set_caption("Keller is coming!");

	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	
	
	void draw() override
	{
		bild.draw_rot(0, 0,	0.0,	//X y z Position
			0,					//Rotationswinkel in Grad
			0, 0);			//Position der Mitte reativ zu x,y

		

		if (space)
		{
			graphics().draw_line(				//Linie zeichnen funktion
			 60, 80, Gosu::Color::BLUE,		//Startpunkt der Linie mit Farbe
			200, 100, Gosu::Color::YELLOW,	//Endpunkt der Linie mit Farbe--> Farbverlauf
			0.0
			);
		}

		if (hoch)
		{
			graphics().draw_rect(200, 200, 200, 200, Gosu::Color::BLUE,-0.5);
		}

		if (runter)
		{
			graphics().draw_rect(200, 200, 200, 200, Gosu::Color::GREEN, 0.0);
		}
	};

	

	double x = 0;
	double y = 0;
	bool space = false;
	bool hoch = false;
	bool runter = false;
	bool rechts = false;
	bool links = false;


	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		x = input().mouse_x();
		y = input().mouse_y();

		//Tastenabfrage
		if (input().down(Gosu::ButtonName::KB_ESCAPE))//schließt, wenn ESC gedrückt wurde
		{ 
			close();
		}

		space = input().down(Gosu::KB_SPACE); //Abfrage ob Space gedrückt ist, wenn ja siehe draw Methode
		hoch = input().down(Gosu::KB_UP);
		runter = input().down(Gosu::KB_DOWN);
		rechts = input().down(Gosu::KB_RIGHT);
		links = input().down(Gosu::KB_K); //LEFT
		
	};
	
};



// C++ Hauptprogramm
int main()
{
	
	
	
	GameWindow window;
	window.show();
}

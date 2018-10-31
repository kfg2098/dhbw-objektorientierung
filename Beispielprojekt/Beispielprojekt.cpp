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

int windowheight = 720;
int windowwidth = 1280;

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(windowwidth, windowheight)
		,bild("Kack.png")
		
	{
		set_caption("Keller is coming!");

	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	
	
	void draw() override
	{
		bild.draw_rot(x+bild.width()/2, y+bild.height()/2, 0.0,
			y-x,//Rotationswinkel
			0.5, 0.5, //Position der "Mitte" in realtiv zu x,y -->0|0 ist oben links 0.5|0.5 ist mitte des Bildes
			0.5,0.4 //Verhältnis zum Kleiner machen 0.4= 40% des Ursprünglichen
		);

		graphics().draw_rect(0, 0, windowwidth, windowheight, Gosu::Color::WHITE, -1); //HG
		
		/*
		graphics().draw_line(				//Linie zeichnen funktion
			10, 20, Gosu::Color::RED,		//Startpunkt der Linie mit Farbe
			200, 100, Gosu::Color::GREEN,	//Endpunkt der Linie mit Farbe--> Farbverlauf
			0.0
		);
		*/

		//graphics().draw_triangle(30,x,Gosu::Color::GREEN,y,100, Gosu::Color::RED,x,y, Gosu::Color::BLUE,0.0);
		//graphics().draw_quad(100, 100, Gosu::Color::BLUE,100, 200, Gosu::Color::YELLOW,300, 300, Gosu::Color::CYAN,300,400,Gosu::Color::RED,0.0);
		//graphics().draw_rect(400,300,y,y,Gosu::Color::CYAN,0.0);
		

		Gosu::Graphics::draw_line(0, 20, Gosu::Color::RED,1280, 20, Gosu::Color::GREEN,0.0);

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
		links = input().down(Gosu::KB_LEFT);
		
	};
	
};



// C++ Hauptprogramm
int main()
{
	
	
	
	GameWindow window;
	window.show();
}

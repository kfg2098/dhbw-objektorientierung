#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>


#include <cstdint>
#include <memory>
#include <cassert>
#include <cinttypes>
#include <forward_list>
#include <algorithm>
#include <ctime>

#include <cstdlib>//für songwiederagbe
#pragma once
#include <Gosu/Fwd.hpp>
#include <Gosu/IO.hpp>
#include <Gosu/Platform.hpp>
#include <Gosu/Audio.hpp>



using namespace std;


//Fenstergröße
int windowheight =900;
int windowwidth = 1600;

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
	int pos_p1_x = 36;
	int pos_p1_y = 56;
	int pos_p2_x = 1545;
	int pos_p2_y = 835;
	const int speed = 5;
	int leben_p1 = 200;
	int leben_p2 = 200;
	bool start = true;

//-------------------------------------------------------
public:
	Gosu::Image bild, bild_hg,buch,oberschmidt,student;
	//Gosu::Font font;
	Gosu::Song song;
	GameWindow()
		: Window(windowwidth, windowheight)
		, bild("Kack.png"), bild_hg("Hintergrund.png"), oberschmidt("Oberschmidt.png"), song("song.mp3"), student("student.png")
		//,font(20)
		
		
	{
		set_caption("Lern oder stirb!");

	}

	
	void draw() override
	{
		student.draw_rot(pos_p1_x, pos_p1_y, 0.0,
			0,//Rotationswinkel
			0.5, 0.5, //Position der "Mitte" in realtiv zu x,y -->0|0 ist oben links 0.5|0.5 ist mitte des Bildes
			0.1,0.1 //Verhältnis zum Kleiner machen 0.4= 40% des Ursprünglichen
		);
		oberschmidt.draw_rot(pos_p2_x, pos_p2_y, 0.0,
			0,//Rotationswinkel
			0.5, 0.5, //Position der "Mitte" in realtiv zu x,y -->0|0 ist oben links 0.5|0.5 ist mitte des Bildes
			0.5, 0.4 //Verhältnis zum Kleiner machen 0.4= 40% des Ursprünglichen
		);

		bild_hg.draw_rot(0, 0, -10, 0, 0, 0); //Hintergrund Zpos -10 als unterstes Bild
		
		//Lebensanzeige Student
		Gosu::Graphics::draw_rect(400, 20, 200, 30, Gosu::Color::GRAY, -2);
		Gosu::Graphics::draw_rect(400, 20, leben_p1, 30, Gosu::Color::GREEN, -1);
		//Lebensanzeige Dozent
		Gosu::Graphics::draw_rect(1250, 20, -200, 30, Gosu::Color::GRAY, -2);
		Gosu::Graphics::draw_rect(1250, 20, -leben_p2, 30, Gosu::Color::GREEN, -1);
		
	};



	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		x = input().mouse_x();
		y = input().mouse_y();

		
		
		//Song bei Start abspielen
		if (start) {
			song.play();
			start = false;
		}
		//Tastenabfrage
		if (input().down(Gosu::ButtonName::KB_ESCAPE))//schließt und stoppt Song, wenn ESC gedrückt wurde
		{ 
			song.stop();
			close();
		}
		//Steuerung Spieler1 Student (Controller 0)
		if (input().down(Gosu::ButtonName::GP_0_UP) && (pos_p1_y >= 56) ||input().down(Gosu::ButtonName::KB_W)&&(pos_p1_y>=56))
		{
			pos_p1_y = pos_p1_y - speed;
			
		}
		if (input().down(Gosu::ButtonName::GP_0_DOWN) && (pos_p1_y <= 843)||input().down(Gosu::ButtonName::KB_S) && (pos_p1_y <=843))
		{
			pos_p1_y = pos_p1_y + speed;
			
		}
		if (input().down(Gosu::ButtonName::GP_0_LEFT) && (pos_p1_x >= 36)||input().down(Gosu::ButtonName::KB_A) && (pos_p1_x >= 36))
		{
			pos_p1_x = pos_p1_x - speed;
			
		}
		if (input().down(Gosu::ButtonName::GP_0_RIGHT) && (pos_p1_x <= 764)||input().down(Gosu::ButtonName::KB_D) && (pos_p1_x <= 764))
		{
			pos_p1_x = pos_p1_x + speed;
			
		}
		//Steuerung Spieler2 Dozent (Controller 1)
		if (input().down(Gosu::ButtonName::GP_1_UP)&&(pos_p2_y>=65)|| input().down(Gosu::ButtonName::KB_UP) && (pos_p2_y >= 65))
		{
			pos_p2_y = pos_p2_y - speed;
			
		}
		if (input().down(Gosu::ButtonName::GP_1_DOWN)&&(pos_p2_y<=830)|| input().down(Gosu::ButtonName::KB_DOWN) && (pos_p2_y <= 830))
		{
			pos_p2_y = pos_p2_y + speed;
			
		}
		if (input().down(Gosu::ButtonName::GP_1_LEFT)&&(pos_p2_x>=855)|| input().down(Gosu::ButtonName::KB_LEFT) && (pos_p2_x >= 855))
		{
			pos_p2_x = pos_p2_x - speed;
			
		}
		if (input().down(Gosu::ButtonName::GP_1_RIGHT)&&(pos_p2_x<=1545)|| input().down(Gosu::ButtonName::KB_RIGHT) && (pos_p2_x <= 1545))
		{
			pos_p2_x = pos_p2_x + speed;
			
		}
		
		
	};

};



// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}

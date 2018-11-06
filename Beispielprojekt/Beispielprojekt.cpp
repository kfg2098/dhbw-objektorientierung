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

//Prjektil 
struct Projektil {
	int pos_pro_x;
	int pos_pro_y;
	double abstand;
	double abstand_d;
};

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
	int warten = 0;
	vector<Projektil>projektile_s;
	vector<Projektil>projektile_d;

//-------------------------------------------------------
public:
	Gosu::Image bild, bild_hg,buch,oberschmidt,student,winner_d,winner_s;
	//Gosu::Font font;
	Gosu::Song song;
	Gosu::Sample sample,laser;
	GameWindow()
		: Window(windowwidth, windowheight)
		, bild("Kack.png"), bild_hg("Hintergrund.png"), oberschmidt("Oberschmidt.png"), song("song.mp3"), student("student.png"),sample("gun.wav"), laser("Lasergun.wav"),winner_s("Winner_Student.png"),winner_d("Winner_Dozent.png")
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
		
		//Projektil Student
		for (auto& p : projektile_s)
		{
			Gosu::Graphics::draw_rect(p.pos_pro_x, p.pos_pro_y, 20, 20, Gosu::Color::RED, 0);
			p.pos_pro_x = p.pos_pro_x + 1.5*speed;
		}

		//Projektil Student
		for (auto& p : projektile_d)
		{
			Gosu::Graphics::draw_rect(p.pos_pro_x, p.pos_pro_y, 20, 20, Gosu::Color::RED, 0);
			p.pos_pro_x = p.pos_pro_x - 1.5*speed;
		}
	};



	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
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
		if ((input().down(Gosu::ButtonName::GP_0_UP)||input().down(Gosu::ButtonName::KB_W))&&(pos_p1_y>=56))
		{
			pos_p1_y = pos_p1_y - speed;
			
		}
		if ((input().down(Gosu::ButtonName::GP_0_DOWN)||input().down(Gosu::ButtonName::KB_S)) && (pos_p1_y <=843))
		{
			pos_p1_y = pos_p1_y + speed;
			
		}
		if ((input().down(Gosu::ButtonName::GP_0_LEFT)||input().down(Gosu::ButtonName::KB_A)) && (pos_p1_x >= 36))
		{
			pos_p1_x = pos_p1_x - speed;
			
		}
		if ((input().down(Gosu::ButtonName::GP_0_RIGHT)||input().down(Gosu::ButtonName::KB_D)) && (pos_p1_x <= 764))
		{
			pos_p1_x = pos_p1_x + speed;
			
		}
		//Steuerung Spieler2 Dozent (Controller 1)
		if ((input().down(Gosu::ButtonName::GP_1_UP)|| input().down(Gosu::ButtonName::KB_UP)) && (pos_p2_y >= 65))
		{
			pos_p2_y = pos_p2_y - speed;
			
		}
		if ((input().down(Gosu::ButtonName::GP_1_DOWN)|| input().down(Gosu::ButtonName::KB_DOWN)) && (pos_p2_y <= 830))
		{
			pos_p2_y = pos_p2_y + speed;
			
		}
		if ((input().down(Gosu::ButtonName::GP_1_LEFT)|| input().down(Gosu::ButtonName::KB_LEFT)) && (pos_p2_x >= 855))
		{
			pos_p2_x = pos_p2_x - speed;
			
		}
		if ((input().down(Gosu::ButtonName::GP_1_RIGHT)|| input().down(Gosu::ButtonName::KB_RIGHT)) && (pos_p2_x <= 1545))
		{
			pos_p2_x = pos_p2_x + speed;
			
		}
		
		
		
		bool test = false;
		int anzahl = 0;
		for (auto& p : projektile_s)
		{
			test = false;
			p.abstand = Gosu::distance(pos_p1_x, pos_p1_y, p.pos_pro_x, p.pos_pro_y);
			if (p.abstand > 300)
			{
				test = true;
			}
		}
		for (auto& p : projektile_s)
		{
			anzahl = anzahl + 1;
		}

		if (input().down(Gosu::ButtonName::KB_SPACE) && (test || anzahl == 0))
		{
			laser.play(); //Gun Sound
			Projektil projektilx;
			projektilx.pos_pro_x = pos_p1_x;
			projektilx.pos_pro_y = pos_p1_y;
			projektile_s.push_back(projektilx);
		}


		//Dozent Schuss
		bool test1 = false;
		int anzahl1 = 0;
		for (auto& p : projektile_d)
		{
			test1 = false;
			p.abstand_d = Gosu::distance(pos_p2_x, pos_p2_y, p.pos_pro_x, p.pos_pro_y);
			if (p.abstand_d > 300)
			{
				test1 = true;
			}
		}
		for (auto& p : projektile_d)
		{
			anzahl1 = anzahl1 + 1;
		}

		if (input().down(Gosu::ButtonName::KB_RIGHT_CONTROL) && (test1 || anzahl1 == 0))
		{
			sample.play(); //Gun Sound
			Projektil projektilx;
			projektilx.pos_pro_x = pos_p2_x;
			projektilx.pos_pro_y = pos_p2_y;
			projektile_d.push_back(projektilx);
		}
	};

};



// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}

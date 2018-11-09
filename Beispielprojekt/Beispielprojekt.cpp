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

//Projektil 
struct Projektil {
	int pos_pro_x;
	int pos_pro_y;
	double abstand_s;
	double abstand_d;
	double abstand_f;
	double abstand_w;
	double abstand_b;//Barrikade, Abstand für Student
	double abstand_b2; //Abstand für Dozent
};


//---------------------------------------------------------------------------------

class GameWindow : public Gosu::Window
{
//-----------------------Globale Variablen----------------
	int pos_p1_x = 36;//Startpostition Student
	int pos_p1_y = 56;
	int pos_p2_x = 1545;//Startposition Dozent
	int pos_p2_y = 835;
	const int speed = 7; //Geschwindigkeit
	int leben_p1 = 200;//Leben
	int leben_p2 = 200;
	bool start = true;
	bool gameover = false;
	bool win_dozent = false;
	bool win_student = false;
	int warten = 0;
	vector<Projektil>projektile_s;
	vector<Projektil>projektile_d;
	int t_y_pos = 0; //für Barierre
	bool runter = true;
//-------------------------------------------------------
public:
	Gosu::Image bild, bild_hg,buch,oberschmidt,student,winner_d,winner_s,feuer1,buch1, tuer;
	//Gosu::Font font;
	Gosu::Song song,gerry,queen;
	Gosu::Sample sample,laser,blaster;

	

	GameWindow()
		: Window(windowwidth, windowheight)
		, bild("Kack.png"), bild_hg("Hintergrund.png"), oberschmidt("Oberschmidt.png"), student("student.png"), winner_s("Winner_Student.png"), winner_d("Winner_Dozent.png"), feuer1("Feuer1.png"), buch1("Buch1.png"), tuer("tuer.png")  //Konstruktor Bilder
		, song("song.mp3"),sample("gun.wav"), laser("Lasergun.wav"),blaster("Blaster.wav"),gerry("Gerry.wav"),queen("Queen.wav")//Konstruktor Sound
		
	{
		set_caption("Die Welt ist nicht gleichverteilt, sonst waere sie gerecht!"); //Spieltitel
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

		tuer.draw_rot(600, 810, -5, 0, 0, 0,0.1,0.1);//Teleporter für Student
		tuer.draw_rot(850, 0, -5, 0, 0, 0, 0.1, 0.1);//Teleporter für Dozent
		
		
		
		//Lebensanzeige Student
		Gosu::Graphics::draw_rect(400, 20, 200, 30, Gosu::Color::GRAY, -2);
		if (leben_p1 < 50) {
			Gosu::Graphics::draw_rect(400, 20, leben_p1, 30, Gosu::Color::RED, -1);
		}
		else {
			Gosu::Graphics::draw_rect(400, 20, leben_p1, 30, Gosu::Color::GREEN, -1);
		}
		//Lebensanzeige Dozent
		Gosu::Graphics::draw_rect(1250, 20, -200, 30, Gosu::Color::GRAY, -2);
		if (leben_p2 < 50) {
			Gosu::Graphics::draw_rect(1250, 20, -leben_p2, 30, Gosu::Color::RED, -1);
		}
		else {
			Gosu::Graphics::draw_rect(1250, 20, -leben_p2, 30, Gosu::Color::GREEN, -1);
		}

		//Barriere in der Mitte
		Gosu::Graphics::draw_rect(775, t_y_pos, 50, 120, Gosu::Color::BLACK, 2);
		
		//Projektil Student
		for (auto& p : projektile_s)
		{
			feuer1.draw_rot(p.pos_pro_x+20, p.pos_pro_y+30, 1,180,0,0,0.25,0.25);
			p.pos_pro_x = p.pos_pro_x + 2.5*speed;
		}

		//Projektil Dozent
		for (auto& p : projektile_d)
		{
			buch1.draw_rot(p.pos_pro_x-40, p.pos_pro_y-10, 1, 0, 0, 0, 0.1, 0.1);
			p.pos_pro_x = p.pos_pro_x - 2.5*speed;
		}
		//Spiel Ende 
		if (gameover) {
			if (win_dozent) {
				winner_d.draw_rot(0, 0, 10, 0, 0, 0);//Dozent ist Gewinner Bild
				
			}
			if (win_student) {
				winner_s.draw_rot(0, 0, 10, 0, 0, 0);//Sutdent ist Gewinner Bild
			}
		}
	};



	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//Song bei Start abspielen
		if (start) {
			song.set_volume(0.27);
			song.play();
			start = false;
		}
		//Tastenabfrage zur Beendigung
		if (input().down(Gosu::ButtonName::KB_ESCAPE)||input().down(Gosu::ButtonName::GP_0_BUTTON_0)|| input().down(Gosu::ButtonName::GP_1_BUTTON_0))//schließt und stoppt Song, wenn ESC gedrückt wurde
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
		
		//Barriere Bewegung
		if (t_y_pos > 780)
		{
			runter = false;
		}
		if (t_y_pos < 0)
		{
			runter = true;
		}
		if (runter)
		{
			t_y_pos = (t_y_pos + speed*0.5);
		}		
		if (!runter)
		{
			t_y_pos = (t_y_pos - speed*0.5);
		}

		//Türteleporter
		if ((638<=pos_p1_x) && (pos_p1_x<=659) && (826<=pos_p1_y) && (pos_p1_y<=856)) {
			pos_p1_x = Gosu::random(20, 750);
			pos_p1_y = Gosu::random(20, 850);
		}
		//Dozent Tür
		if ((pos_p2_x >= 880) && (pos_p2_x <= 908)&& (pos_p2_y >= 58)&&(pos_p2_y<=79)) {
			pos_p2_x = Gosu::random(850, 1580);
			pos_p2_y = Gosu::random(20, 850);
		}
		

		//Schuss Student
		bool test = false;
		int anzahl = 0;
		for (auto& p : projektile_s)
		{
			test = false;
			p.abstand_s = Gosu::distance(pos_p1_x, pos_p1_y, p.pos_pro_x, p.pos_pro_y);//Neues Projektil erst bei bestimmten Abstand erstellen
			if (p.abstand_s > 400)
			{
				test = true;
			}
		}
		for (auto& p : projektile_s)
		{
			anzahl = anzahl + 1;
		}

		if (((input().down(Gosu::ButtonName::KB_SPACE)||input().down(Gosu::ButtonName::GP_0_BUTTON_2))&& (test || anzahl == 0))&& !gameover)//Neues Projektil wird erstellt
		{
			
			laser.play(0.27); //Gun Sound
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
			p.abstand_d = Gosu::distance(pos_p2_x, pos_p2_y, p.pos_pro_x, p.pos_pro_y);//Abstandsabfrage
			if (p.abstand_d > 400)
			{
				test1 = true;
			}
		}
		for (auto& p : projektile_d)
		{
			anzahl1 = anzahl1 + 1;
		}

		if (((input().down(Gosu::ButtonName::KB_RIGHT_CONTROL)||input().down(Gosu::ButtonName::GP_1_BUTTON_2) )&& (test1 || anzahl1 == 0))&& !gameover)//Neues Projektil
		{
			blaster.play(0.27); //Gun Sound
			Projektil projektilx;
			projektilx.pos_pro_x = pos_p2_x;
			projektilx.pos_pro_y = pos_p2_y;
			projektile_d.push_back(projektilx);
		}
		//Hit Student auf Dozent
		int counter = 0;
		for (auto& p : projektile_s)
		{
			p.abstand_f = Gosu::distance(pos_p2_x, pos_p2_y, p.pos_pro_x, p.pos_pro_y);//Hit wenn Abstand gering wird
			if (p.abstand_f < 60)
			{
				projektile_s.erase(projektile_s.begin() + counter);
				if (leben_p2 >= 20)//Leben wird bei Treffer abgezogen
				{
					leben_p2 = leben_p2 - 10;
				}
				else if (leben_p2 >= 10)
				{
					leben_p2 = leben_p2 - 10;
					gameover = true;
					win_student = true;
					queen.set_volume(0.5);
					queen.play();
					projektile_d.clear();//Alle bestehende Projektile löschen
					projektile_s.clear();

		
				}
			}

			if (p.pos_pro_x > 1580)//Projektil wird nach Bildrand gelöscht
			{
				projektile_s.erase(projektile_s.begin() + counter);
			}

			counter = counter + 1;
		}
		//Hit Dozent auf Student
		counter = 0;
		for (auto& p : projektile_d)
		{
			p.abstand_f = Gosu::distance(pos_p1_x, pos_p1_y, p.pos_pro_x, p.pos_pro_y);//Hitabfrage
			if (p.abstand_f < 60)
			{
				projektile_d.erase(projektile_d.begin() + counter);
				if (leben_p1 >= 20)//Lebensabfrage
				{
					leben_p1 = leben_p1 - 10;
				}
				else if (leben_p1 >= 10)
				{
					leben_p1 = leben_p1 - 10;
					gameover = true;
					win_dozent = true;
					gerry.set_volume(1.0);
					gerry.play();
					projektile_d.clear();//Alle bestehenden Projektile löschen
					projektile_s.clear();

					if (input().down(Gosu::ButtonName::KB_G))
					{
						int main();
					}
					
				}
			}

			if (p.pos_pro_x < 20)//Ortabfrage
			{
				projektile_d.erase(projektile_d.begin() + counter);
			}

			counter = counter + 1;
		}

		//Hit Abfrage für Barriere
		//Student
		counter = 0;
		for (auto& p : projektile_s)
		{
			if((p.pos_pro_x>=775)&&(p.pos_pro_y>=t_y_pos)&&(p.pos_pro_y<=t_y_pos+120))
			{
				projektile_s.erase(projektile_s.begin() + counter);
			}
			counter = counter + 1;
		}
		
		//Dozent
		counter = 0;
		for (auto& p : projektile_d)
		{
			if ((p.pos_pro_x <= 825) && (p.pos_pro_y >= t_y_pos) && (p.pos_pro_y <= t_y_pos + 120))
			{
				projektile_d.erase(projektile_d.begin() + counter);
			}
			counter = counter + 1;
		}

		//Game restart mit Taste R
		if (gameover && (input().down(Gosu::ButtonName::KB_R)||input().down(Gosu::ButtonName::GP_0_BUTTON_1)||input().down(Gosu::ButtonName::GP_1_BUTTON_1))) {
			gameover = false;
			start = true;
			win_dozent = false;
			win_student = false;
			leben_p1 = 200;
			leben_p2 = 200;
		}
	};

};


// C++ Hauptprogramm
int main()
{
	char s;
	cout << "Dies ist ein Projekt fuer das Fach Informatik." << endl;
	cout << "Es wird nicht beabsichtig dargestellte Personen blosszustellen!" << endl;
	cout << endl;
	cout << "Credits:" << endl;//Consolen Text
	cout << "Youtube: Gerald Oberschmidt: https://www.youtube.com/watch?v=f-HZZT5TkPo&t=51s" << endl;
	cout << "https://www.karlsruhe.dhbw.de/fileadmin/user_upload/images/content/Bilder-Adressverwaltung/Oberschmidt-Gerald-Prof.jpg" << endl;
	cout << endl;
	Gosu::sleep(3000);
	cout << "Steuerung:" << endl;
	cout << "	Student:" << endl;
	cout << "		Bewegung:	W/S/A/D (Tastatur),Joystick (Gamepad)" << endl;
	cout << "		Schuss:		Leertaste (Tastatur),Button 3 oder X (Gamepad)" << endl;
	cout << "	Dozent:" << endl;
	cout << "		Bewegung:	Pfeiltasten (Tastatur),Joystick (Gamepad)" << endl;
	cout << "		Schuss:		rechte Strg (Tastatur),Button 3 oder X (Gamepad)" << endl;
	cout << "	Spiel erneut starten:	R (Tastatur),Button 2 oder B (Gamepad)" << endl;
	cout << "	Beenden:	ESC (Tastatur), Button 1 oder A (Gamepad)" << endl;
	cout << endl;
	cout << "Um das Spiel zu starten bitte [s] druecken." << endl;
	cin >> s;
	if (s == 's') {
		cout << "Lade Spiel..." << endl;
		GameWindow window;
		window.show();
	}
}

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <iostream>
#include <stack>
#include <conio.h>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#include"operacje_na_plikach.h"
#include"sturktury.h"
#include "choose_menu.h"

// rysowanie menu choose
void draw_choose_window(ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly, ALLEGRO_FONT *tekst_posredni)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_bitmap(guziczki[0],0,0,NULL);;
	//al_draw_filled_rectangle(90.0,180.0,770.0,280.0,al_map_rgba(20,20,20,100));
	al_draw_filled_rectangle(200.0,200.0,660.0,350.0,al_map_rgb(253,211,3));
	al_draw_filled_rectangle(200.0,400.0,660.0,550.0,al_map_rgb(253,211,3));
	//al_draw_filled_rectangle(618.0,537.0,818.0,606.0,al_map_rgb(253,211,3));
	al_draw_text(tekst_posredni,al_map_rgb(0,0,0),430,230, ALLEGRO_ALIGN_CENTRE, "new game");
	al_draw_text(tekst_posredni,al_map_rgb(0,0,0),430,430, ALLEGRO_ALIGN_CENTRE, "load game");
	//al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,548, ALLEGRO_ALIGN_CENTRE, "cancel");
	al_draw_text(naglowek,al_map_rgb(253,211,3),430,18, ALLEGRO_ALIGN_CENTRE, "# Choose game #");
}


// obsluga menu choose
int choose_window(Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki,
				ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly, ALLEGRO_FONT *tekst_posredni)
{
	draw_choose_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
	al_flip_display();
	ALLEGRO_EVENT klik;
	bool pom = false;
	while (!pom)
	{
		al_wait_for_event(kolejeczka,&klik);
		draw_choose_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
		if (klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if ((klik.mouse.x >= 200)&&(klik.mouse.x <=660) &&(klik.mouse.y>=200)&&(klik.mouse.y<=350))
			{
				al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,230, ALLEGRO_ALIGN_CENTRE, "new game");
				al_flip_display();
				al_rest(0.15);
				board_reset(gracz1,szachownica,pion,biale_pionki,czarne_pionki,biale_damki,czarne_damki);
				if (sterujaca == 12)
				{
					sterujaca = 1;
					return 1;
				}
				else if (sterujaca == 13)
				{
					sterujaca = 2;
					return 2;
				}
			}
			else if ((klik.mouse.x >= 200)&&(klik.mouse.x <=660) &&(klik.mouse.y>=400)&&(klik.mouse.y<=550))
			{
				al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,430, ALLEGRO_ALIGN_CENTRE, "load game");
				al_flip_display();
				al_rest(0.15);
				if (sterujaca == 12)
				{
					sterujaca = 10;
					return 10;
				}
				else if (sterujaca == 13)
				{
					sterujaca = 11;
					return 11;
				}
			}
		}
	}
	return 0;
}
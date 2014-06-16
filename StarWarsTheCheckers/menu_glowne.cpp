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
#include "menu_glowne.h"

// tworzenie menu glownego
void main_menu_display (ALLEGRO_BITMAP **guziczki)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_bitmap(guziczki[0],0.0,0.0,NULL);
	al_draw_bitmap(guziczki[1],95.0,35.0,NULL);
	al_draw_bitmap(guziczki[2],162.0,240.0,NULL);
	al_draw_bitmap(guziczki[3],93.0,313.0,NULL);
	al_draw_bitmap(guziczki[4],188.0,386.0,NULL);
	al_draw_bitmap(guziczki[5],251.0,459.0,NULL);
	al_draw_bitmap(guziczki[6],220.0,532.0,NULL);

	al_flip_display();
}

// dzialanie menu glownego
void main_menu_execute (ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki)
{
	
	ALLEGRO_EVENT klik;
	main_menu_display(guziczki);
	//al_flip_display();
	bool pom = false;
	int pom2 = 0;
	while (!pom)
	{
		al_wait_for_event(kolejeczka, &klik);	
		if (klik.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			if ((klik.mouse.y >= 240)&&(klik.mouse.y < 300) && (pom2 != 1))
			{
				pom2=1;
				guziczki[2]=al_load_bitmap("obrazy/slajdy/single_player2.png");
				main_menu_display(guziczki);
				guziczki[2]=al_load_bitmap("obrazy/slajdy/single_player1.png");
			}
			else if ((klik.mouse.y >= 300)&&(klik.mouse.y < 373) && (pom2 != 2))
			{
				pom2=2;
				guziczki[3]=al_load_bitmap("obrazy/slajdy/pvp2.png");
				main_menu_display(guziczki);
				guziczki[3]=al_load_bitmap("obrazy/slajdy/pvp1.png");
			}
			else if ((klik.mouse.y >= 373)&&(klik.mouse.y < 446) && (pom2 != 3))
			{
				pom2=3;
				guziczki[4]=al_load_bitmap("obrazy/slajdy/online_game2.png");
				main_menu_display(guziczki);
				guziczki[4]=al_load_bitmap("obrazy/slajdy/online_game1.png");
			}
			else if ((klik.mouse.y >= 446)&&(klik.mouse.y < 516) && (pom2 != 4))
			{
				pom2=4;
				guziczki[5]=al_load_bitmap("obrazy/slajdy/options2.png");
				main_menu_display(guziczki);
				guziczki[5]=al_load_bitmap("obrazy/slajdy/options1.png");
			}
			else if ((klik.mouse.y >= 516)&&(klik.mouse.y < 592) && (pom2 != 5))
			{
				pom2=5;
				guziczki[6]=al_load_bitmap("obrazy/slajdy/quit_game2.png");
				main_menu_display(guziczki);
				guziczki[6]=al_load_bitmap("obrazy/slajdy/quit_game1.png");
			}
			else if (((klik.mouse.y >=592)|| (klik.mouse.y <240)) && (pom2 != 0))
			{
				pom2 = 0;
				main_menu_display(guziczki);
			}
		}
		else if (klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (klik.mouse.button & 1)
			{
				if ((klik.mouse.y >= 240)&&(klik.mouse.y < 300))
				{
					sterujaca = 12;
					break;
				}
				else if ((klik.mouse.y >= 300)&&(klik.mouse.y < 373))
				{
					sterujaca = 13;
					break;
				}
				else if ((klik.mouse.y >= 373)&&(klik.mouse.y < 446))
				{
					//sterujaca = 3;
					//break;
				}
				else if ((klik.mouse.y >= 446)&&(klik.mouse.y < 516))
				{
					//sterujaca = 4;
					//break;
				}
				else if ((klik.mouse.y >= 516)&&(klik.mouse.y < 592))
				{
					sterujaca = -1;
					break;
				}
				else if (((klik.mouse.y >=592)|| (klik.mouse.y <240)))
				{
					;
				}
			}
		}
		else if (klik.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					sterujaca = -1;
					break;
				}
	}
}
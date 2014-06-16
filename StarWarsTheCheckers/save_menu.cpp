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
#include "save_menu.h"


// rysowanie menu save
void draw_save_window(ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly, ALLEGRO_FONT *tekst_posredni)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_bitmap(guziczki[0],0,0,NULL);
	al_draw_bitmap(guziczki[1],200,350,NULL);
	al_draw_filled_rectangle(90.0,180.0,770.0,280.0,al_map_rgba(20,20,20,100));
	al_draw_filled_rectangle(618.0,337.0,818.0,406.0,al_map_rgb(253,211,3));
	al_draw_filled_rectangle(618.0,437.0,818.0,506.0,al_map_rgb(253,211,3));
	al_draw_filled_rectangle(618.0,537.0,818.0,606.0,al_map_rgb(253,211,3));
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,348, ALLEGRO_ALIGN_CENTRE, "save");
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,448, ALLEGRO_ALIGN_CENTRE, "clear");
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,548, ALLEGRO_ALIGN_CENTRE, "cancel");
	al_draw_text(naglowek,al_map_rgb(253,211,3),430,18, ALLEGRO_ALIGN_CENTRE, "# Save game #");
}

// obsluga menu save
int save_window(Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki,
				ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly, ALLEGRO_FONT *tekst_posredni)
{
	draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
	al_flip_display();
	ALLEGRO_EVENT klik;

	bool pom = false;
	draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
	int counter = 1;
	char *str;
	str = (char*)malloc(counter*sizeof(char));
	str[0] = ' ';
	while (!pom)
	{
		al_wait_for_event(kolejeczka,&klik);
		draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
		if (klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 537)&&(klik.mouse.y <= 606))
			{
				al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,548, ALLEGRO_ALIGN_CENTRE, "cancel");
				al_flip_display();
				al_rest(0.3);
				if (sterujaca == 6)
					{
						sterujaca = 1;
						return 1;
					}
					else if (sterujaca == 7)
					{
						sterujaca = 2;
						return 2;
					}
			}
			else if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 437)&&(klik.mouse.y <= 506))
			{
				while (counter>1)
				{
					counter--;
					str[counter-1]='\0';
					//str[counter-2]='\0';
					str = (char*)realloc(str, counter*sizeof(char));
				}
				al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,448, ALLEGRO_ALIGN_CENTRE, "clear");
				al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
				al_flip_display();
				al_rest(0.15);
				al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,448, ALLEGRO_ALIGN_CENTRE, "clear");
				al_flip_display();

			}
			else if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 337)&&(klik.mouse.y <= 406))
			{
				
				if (counter <= 2)
				{
					
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_draw_text(tekst_zwykly,al_map_rgb(253,111,120),430,270, ALLEGRO_ALIGN_CENTRE, "filename is too short");
					al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,348, ALLEGRO_ALIGN_CENTRE, "save");
					al_flip_display();
					al_rest(0.15);
					draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_draw_text(tekst_zwykly,al_map_rgb(253,111,120),430,270, ALLEGRO_ALIGN_CENTRE, "filename is too short");
					al_flip_display();
					continue;
				}
				else
				{
					counter = counter +5;
					str = (char*)realloc(str, counter*sizeof(char));
					str[counter-6]='.';
					str[counter-5]='s';
					str[counter-4]='w';
					str[counter-3]='c';
					str[counter-2]='s';
					str[counter-1]='\0';
					draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
					al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,348, ALLEGRO_ALIGN_CENTRE, "save");
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_flip_display();
					al_rest(0.15);
					draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_draw_text(tekst_zwykly,al_map_rgb(111,253,120),430,270, ALLEGRO_ALIGN_CENTRE, "game saved");
					al_flip_display();
					al_rest(0.7);
				
					save_game(counter, str,gracz1,gracz2,szachownica,pion,sterujaca,biale_pionki,czarne_pionki,biale_damki,czarne_damki);
					while (counter>1)
					{
						counter--;
						str[counter-1]='\0';
						//str[counter-2]='\0';
						str = (char*)realloc(str, counter*sizeof(char));
					}
					draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
					al_flip_display();
					if (sterujaca == 6)
					{
						sterujaca = 1;
						return 1;
					}
					else if (sterujaca == 7)
					{
						sterujaca = 2;
						return 2;
					}
				}
				//al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,448, ALLEGRO_ALIGN_CENTRE, "save");
			}
		}
		else if(klik.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (klik.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				sterujaca = -1;
				return -1;
			}
			if (klik.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
			{
				if (counter>1)
				{
					counter--;
					str[counter-1]='\0';
					//str[counter-2]='\0';
					str = (char*)realloc(str, counter*sizeof(char));
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_flip_display();
					continue;
				}
			}
			if((((al_keycode_to_name(klik.keyboard.keycode)[0] >= 65)&&(al_keycode_to_name(klik.keyboard.keycode)[0] <= 90))||((al_keycode_to_name(klik.keyboard.keycode)[0] >= 48)&&(al_keycode_to_name(klik.keyboard.keycode)[0] <= 57)))&&(al_keycode_to_name(klik.keyboard.keycode)[1] == 0))
			{
				char *cr;
				cr = (char*)malloc(2*sizeof(char));
				cr[0] = al_keycode_to_name(klik.keyboard.keycode)[0];
				cr[1]='\0';
				cr[0] = tolower(cr[0]);
				counter++;
				str = (char*)realloc(str, counter*sizeof(char));
				str[counter-2]=cr[0];
				str[counter-1]='\0';
				al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
				al_flip_display();
			}
		}
	}
	al_rest(5.0);
	return 1;
}
#ifndef load_menu_h
#define load_menu_h
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

// rysowanie menu load
void draw_load_window (int *wysokosc, string *nazwy, ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly);

// obsluga menu load
int load_window (Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki,
				 ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly);






#endif
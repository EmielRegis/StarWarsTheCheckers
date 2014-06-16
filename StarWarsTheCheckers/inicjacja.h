#ifndef inicjacja_h
#define inicjacja_h

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
#include "sturktury.h"



// tworzenie szachownicy pol
Pole_s **tworzenie_szachownicy(ALLEGRO_BITMAP *pb, ALLEGRO_BITMAP *pcz, ALLEGRO_BITMAP **guziki);

// tworzenie listy figur
Pion_s *tworzenie_listy_figur(Gracz_s gracz1, Pole_s **szachownica, int &biale_pionki, int &czarne_pionki);



#endif inicjacja_h
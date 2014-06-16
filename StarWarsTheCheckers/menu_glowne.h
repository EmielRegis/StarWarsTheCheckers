#ifndef menu_glowne_h
#define menu_glowne_h
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


// tworzenie menu glownego
void main_menu_display (ALLEGRO_BITMAP **guziczki);

// dzialanie menu glownego
void main_menu_execute (ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki);




#endif
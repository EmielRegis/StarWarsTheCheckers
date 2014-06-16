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
#include "inicjacja.h"
#include "mechanika_gracza.h"
#include "mechanika_komputera.h"
#include "menu_glowne.h";
#include "operacje_na_plikach.h";
#include "load_menu.h"
#include "save_menu.h"
#include "choose_menu.h"



// definicja rozmiaru okna
const int dlugosc_okna = 860, szerokosc_okna = 640;

// tablica - szachownica pol
Pole_s **pole;

// tablica - lista figur
Pion_s *figura;


// licznik ruchow bez bicia
unsigned bez_bicia;

// licznik figur 
int liczba_bialych;
int liczba_czarnych;
int liczba_bialych_damek;
int liczba_czarnych_damek;

// warunek zakonczenia rozgrywki
bool czy_koniec (int biale, int czarne, int biale_damki, int czarne_damki, ALLEGRO_DISPLAY *&okienko,bool wwyjscie)
{
	bool koniec= wwyjscie;
	if (biale <= 0)
	{
		koniec = true;
		al_show_native_message_box( okienko,"Koniec","Gra zostala zakoczona","Zwyciestwo odniosla druzyna Czarnych",NULL, ALLEGRO_MESSAGEBOX_YES_NO);
	}
	else if (czarne <= 0)
	{
		koniec = true;
		al_show_native_message_box( okienko,"Koniec","Gra zostala zakonczona","Zwyciestwo odniosla druzyna Bialych",NULL, ALLEGRO_MESSAGEBOX_YES_NO);
	}
	else if ((biale == 1) && (czarne==1) &&(biale_damki==1)&&(czarne_damki==1))
	{
		koniec = true;
		al_show_native_message_box( okienko,"Koniec","Gra zostala zakonczona","Remis",NULL, ALLEGRO_MESSAGEBOX_YES_NO);

	}
	return koniec;

}




int  main()
{
	// ustawienie losowosci
	srand(time(0));

	// inicjalizacja modulow allegro
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();

	// zmienna do wyjscia z programu
	bool wyjscie = false;

	// zmienna sterujaca stanem programu
	int zmienna_steruj¹ca = 0;

	// ustawienia okna glownego
	ALLEGRO_DISPLAY *okno = al_create_display(dlugosc_okna, szerokosc_okna);
	ALLEGRO_BITMAP *ikona = al_load_bitmap("obrazy/ikona/ikona.jpg");
	ALLEGRO_BITMAP *firma = al_load_bitmap("obrazy/slajdy/firma.jpg");
	ALLEGRO_BITMAP *lightsaber = al_load_bitmap("obrazy/slajdy/red.png");
	al_set_display_icon(okno, ikona);
	al_set_new_display_flags(ALLEGRO_GENERATE_EXPOSE_EVENTS);
	al_set_window_title(okno, "Warcaby v0.01");
	al_clear_to_color(al_map_rgb_f(0.0,0.0,0.0));
	al_draw_bitmap(firma,110.0,0.0,NULL);
	al_flip_display();
	al_rest(1.7);

	// ustawienia czcionek
	ALLEGRO_FONT *sw_font_h = al_load_ttf_font("Czcionki/Starjedi.ttf",69,NULL);
	ALLEGRO_FONT *sw_font_r = al_load_ttf_font("Czcionki/Starjedi.ttf",27,NULL);
	ALLEGRO_FONT *sw_font_m = al_load_ttf_font("Czcionki/Starjedi.ttf",51,NULL);
	ALLEGRO_COLOR sw_bialy = al_map_rgb(255,255,255);
	ALLEGRO_COLOR sw_czarny = al_map_rgb(0,0,0);
	ALLEGRO_COLOR sw_zloty = al_map_rgb(253,211,2);

	// ustatwienia dzwieku
	al_reserve_samples(2);
	ALLEGRO_SAMPLE *podklad = al_load_sample("dzwieki/muzyka/starwars.wav");
	ALLEGRO_SAMPLE_INSTANCE *instancja = al_create_sample_instance(podklad);
	al_set_sample_instance_playmode(instancja, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(instancja, al_get_default_mixer());
	al_play_sample_instance(instancja);
	
	// ladowanie bitmap
	ALLEGRO_BITMAP *tytulowy = al_load_bitmap("obrazy/slajdy/tytulowy.jpg");
	ALLEGRO_BITMAP *przyciski[5];
	przyciski[0] = al_load_bitmap("obrazy/slajdy/star_background.jpg");
	przyciski[1] = al_load_bitmap("obrazy/slajdy/small_logo2.png");
	przyciski[2] = al_load_bitmap("obrazy/slajdy/sound_on.png");
	przyciski[3] = al_load_bitmap("obrazy/slajdy/save1.png");
	przyciski[4] = al_load_bitmap("obrazy/slajdy/return1.png");
	ALLEGRO_BITMAP *przyciski2[7];
	przyciski2[0] = al_load_bitmap("obrazy/slajdy/star_background.jpg");
	przyciski2[1] = al_load_bitmap("obrazy/slajdy/main_menu.png");
	przyciski2[2] = al_load_bitmap("obrazy/slajdy/single_player1.png");
	przyciski2[3] = al_load_bitmap("obrazy/slajdy/pvp1.png");
	przyciski2[4] = al_load_bitmap("obrazy/slajdy/online_game1.png");
	przyciski2[5] = al_load_bitmap("obrazy/slajdy/options1.png");
	przyciski2[6] = al_load_bitmap("obrazy/slajdy/quit_game1.png");
	al_clear_to_color(al_map_rgb_f(0.0,0.0,0.0));
	al_draw_bitmap(tytulowy,110.0,0.0,NULL);
	al_flip_display();
	al_rest(2.3);
	ALLEGRO_BITMAP *pole_biale = al_load_bitmap("obrazy/tekstury/metal.jpg");
	ALLEGRO_BITMAP *pole_czarne = al_load_bitmap("obrazy/tekstury/forcefield.jpg");
	/*ALLEGRO_BITMAP *r2d2 = al_load_bitmap("obrazy/bohaterowie/r2d22.png");
	ALLEGRO_BITMAP *stormtrooper = al_load_bitmap("obrazy/bohaterowie/stormtrooper.png");
	ALLEGRO_BITMAP *darthvader = al_load_bitmap("obrazy/bohaterowie/darthvader1.png");
	ALLEGRO_BITMAP *masteryoda = al_load_bitmap("obrazy/bohaterowie/masteryoda2.png");
	ALLEGRO_BITMAP *emperor = al_load_bitmap("obrazy/bohaterowie/emperor.png");
	ALLEGRO_BITMAP *hansolo = al_load_bitmap("obrazy/bohaterowie/hansolo.png");*/

	// tworzenie kolejki eventow
	ALLEGRO_EVENT_QUEUE *kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_mouse_event_source());
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	al_register_event_source(kolejka, al_get_display_event_source(okno));

	// ustawienia graczy
	Gracz_s gracz_1, gracz_2;
	gracz_1.kolor_gracza = czarny;
	gracz_1.nr_gracza = 1;
	gracz_1.stan = w_trakcie_gry;
	gracz_2.kolor_gracza = zamiana(gracz_1.kolor_gracza);
	gracz_2.nr_gracza = 2;
	gracz_2.stan = w_trakcie_gry;

	// inicjalizacja planszy i figur
	pole = tworzenie_szachownicy(pole_biale, pole_czarne, przyciski);
	figura = tworzenie_listy_figur(gracz_1, pole, liczba_bialych, liczba_czarnych);
	//ALLEGRO_PATH *path = NULL;
	//path = al_get_path(ALLEGRO_RESOURCES_PATH);
	//ALLEGRO_FILECHOOSER *otwieracz = NULL;
	//otwieracz = al_create_native_file_dialog(NULL,"otwieracz","*.*",ALLEGRO_FILECHOOSER_SAVE);
	//bool xyz = false;
	//al_show_native_file_dialog(al_get_current_display(), otwieracz);
	//al_flip_display();

	// menu glowne
	main_menu:
	main_menu_execute(kolejka,zmienna_steruj¹ca,przyciski2);
	goto control_panel;


	// modul sterujacy
	control_panel:
	switch (zmienna_steruj¹ca)
	{
	case -1:
		goto the_end;
		break;
	case 0:
		goto main_menu;
		break;
	case 1:
		//board_reset(gracz_1,pole,figura,liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek);
		goto single_player;	
		break;
	case 2: 
		//board_reset(gracz_1,pole,figura,liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek);
		goto multi_player;
		break;
	case 3:
		goto online_game;
		break;
	case 4:
		goto options;
		break;
	case 5:
		goto g_load;
		break;
	case 6:
		goto g_save;
		break;
	case 7:
		goto g_save;
		break;
	case 8:
		goto g_save;
		break;
	case 9:
		goto g_save;
		break;
		case 10:
		goto g_load;
		break;
	case 11:
		goto g_load;
		break;
	case 12:
		goto new_or_load;
		break;
	case 13:
		goto new_or_load;
		break;
	}


	// wybieranie nowej lub wczytanej gry
new_or_load:
	choose_window(gracz_1,gracz_2,pole,figura,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek,kolejka,zmienna_steruj¹ca,przyciski,sw_font_h,sw_font_r,sw_font_m);
	goto control_panel;
	

	// ladowanie ustawien
	g_load:
	//save_game(gracz_1,gracz_2,pole,figura,zmienna_steruj¹ca,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek);
	load_window(gracz_1,gracz_2,pole,figura,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek, kolejka,zmienna_steruj¹ca,przyciski,sw_font_h,sw_font_r);
	goto control_panel;


	// zapisywanie ustawien
	g_save:
	save_window(gracz_1,gracz_2,pole,figura,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek,kolejka,zmienna_steruj¹ca,przyciski,sw_font_h,sw_font_r,sw_font_m);
	goto control_panel;


	// tryb dla jednego gracza
	single_player:
	odswiezenie_grafika(pole,figura,gracz_1.nr_gracza,przyciski);
	zmienna_steruj¹ca =1;
	while (!wyjscie)
	{
		if (!wyjscie)
		{
			wyjscie =tura(gracz_1, gracz_2,pole,figura,kolejka, liczba_bialych, liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, zmienna_steruj¹ca, przyciski);
		if (wyjscie == false)
		{
			wyjscie=czy_koniec(liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek,okno,wyjscie);
		}
		}
		if (!wyjscie)
		{
		 wyjscie = tura_kompa2 (pole,figura, gracz_2, liczba_bialych, liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, przyciski);
		 wyjscie=czy_koniec(liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, okno,wyjscie);
		 //wyjscie=false;
		}
	}
	wyjscie = false;
	//save_game(gracz_1,gracz_2,pole,figura,zmienna_steruj¹ca,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek);
	goto control_panel;


	//tryb dla dwoch graczy
	multi_player:
	odswiezenie_grafika(pole,figura,gracz_1.nr_gracza,przyciski);
	zmienna_steruj¹ca=2;
	while (!wyjscie)
	{
		if (!wyjscie)
		{
		wyjscie =tura(gracz_1, gracz_2,pole,figura,kolejka, liczba_bialych, liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, zmienna_steruj¹ca, przyciski);
		if (wyjscie == false)
		{
			wyjscie=czy_koniec(liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek,okno,wyjscie);
		}
		}
		if (!wyjscie)
		{
		 wyjscie = tura(gracz_2, gracz_1,pole,figura,kolejka, liczba_bialych, liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, zmienna_steruj¹ca, przyciski);
		 if (wyjscie == false)
		{
			wyjscie=czy_koniec(liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek,okno,wyjscie);
		}
		 //wyjscie=false;
		}
	}
	wyjscie = false;
	goto control_panel;


	// tryb internetowy
	online_game:
	goto control_panel;


	// opcje gry
	options:
	goto control_panel;


	// z gry
	the_end:
	al_rest(1.0);


    return 0;
}
 
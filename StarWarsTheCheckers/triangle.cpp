#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
int main()
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    ALLEGRO_KEYBOARD_STATE klawiatura;
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *okno = al_create_display(400,300);
    al_set_window_title( okno,"Allegro5 - Prymitywy");
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(okno));
    ALLEGRO_EVENT event;
    while(!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))
    {
        al_get_next_event(event_queue, &event);if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { return 0; }
        al_get_keyboard_state(&klawiatura);
        al_clear_to_color(al_map_rgb(150,150,150)); //t�o
        al_draw_line( 10, 15, 80, 90, al_map_rgba( 0, 255, 0, 128), 4);
        al_draw_triangle(100, 15, 150, 25, 125, 80, al_map_rgb(255, 0, 0), 8);
        al_draw_filled_triangle(190, 15, 250, 76, 175, 80, al_map_rgb(0,0,255));
        al_draw_rectangle(250,10,300, 60,al_map_rgba(255,255,0,128),2);
        al_draw_filled_rectangle(280, 20,350, 80,al_map_rgba(0,0,0,100));
        al_draw_rounded_rectangle( 50,100,100,150,12,12,al_map_rgb(0,255,255),5);
        al_draw_filled_rounded_rectangle(110, 90,150,154, 12, 20,al_map_rgb(128,0,255));
        al_draw_circle(200,120, 30, al_map_rgb( 0,128, 0), 20);
        al_draw_filled_circle(250,120, 34, al_map_rgba(200,28, 0,60));
        al_flip_display();
        al_rest(0.005);//pauza
    }
    al_destroy_display(okno);
    return 0;
}
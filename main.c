#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include<time.h>
ALLEGRO_FONT *font;
ALLEGRO_COLOR black;
ALLEGRO_COLOR white;
ALLEGRO_BITMAP *background = NULL;
void number_of_players(){
  /* added */
  
  
  black = al_map_rgb(0, 0, 0);
  white = al_map_rgb(255, 255, 255);
  al_clear_to_color(white);
  
  al_draw_bitmap(background,0,0,0);
  al_draw_text(font,black,63,200,0,"Select Number of Players");
  al_draw_filled_circle(250,330, 48,black);
  al_draw_text(font,white,228,300,0,"23");
  al_draw_filled_circle(400,330, 48,black);
  al_draw_text(font,white,365,300,0,"524");
  al_draw_filled_circle(550,330, 48,black);
  al_draw_text(font,white,504,300,0,"4531");                                     
  al_flip_display();
}
int inBound(int x1,int y1, int x2, int y2, int x3, int y3){
  if(x3>=x1 && x3<= x2 && y3>=y1 && y3<= y2 )  
    return 1;
  return 0;
}
int main(){
  al_init();
  ALLEGRO_DISPLAY *display;
  black = al_map_rgb(0, 0, 0);
  white = al_map_rgb(255, 255, 255);
  if (!al_init()) {
      printf("Could not init Allegro.\n");
      return 0;
  }
  al_init_ttf_addon();
  al_init_image_addon();
  background = al_load_bitmap("background.jpg");
  al_init_primitives_addon();
  font = al_load_ttf_font("Penguin.ttf", 40, 0);
  al_install_mouse();
  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  al_register_event_source(queue, al_get_mouse_event_source());
  display = al_create_display(800, 490);
  if (!display) {
      printf("Error creating display\n");
      return 0;
     }
  if (!font) {
      printf("Error creating font\n");
      return 0;
     }
  ALLEGRO_EVENT event;
  int n_of_players = 0, x, y;
  while(n_of_players == 0){
    if(al_is_event_queue_empty(queue)){
      number_of_players();
    }
    al_wait_for_event(queue, &event);
    if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){  
      if(inBound(210,290, 290,370,event.mouse.x,event.mouse.y))
        n_of_players = 2;
      else if(inBound(360,290, 440,370,event.mouse.x,event.mouse.y))
        n_of_players = 3;
      else if(inBound(510,290, 590,370,event.mouse.x,event.mouse.y))
        n_of_players = 4;  
    }
  }
  printf("%d\n",n_of_players);
  al_destroy_bitmap(background);
  al_destroy_event_queue(queue);
  al_destroy_font(font);
  al_destroy_display(display);
  al_uninstall_mouse();
  return 0;
}
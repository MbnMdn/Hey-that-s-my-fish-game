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
void number_of_players(){
  black = al_map_rgb(0, 0, 0);
  white = al_map_rgb(255, 255, 255);
  al_clear_to_color(white);
  al_draw_text(font,black,280,200,0,"Select Number of Players");
  al_draw_filled_rectangle(220,300, 290,350,black);
  al_draw_text(font,white,248,310,0,"2");
  al_draw_filled_rectangle(370,300, 440,350,black);
  al_draw_text(font,white,398,310,0,"3");
  al_draw_filled_rectangle(520,300, 590,350,black);
  al_draw_text(font,white,548,310,0,"4");                                     
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
  al_init_primitives_addon();
  font = al_load_ttf_font("tahoma.ttf", 20, 0);
  al_install_mouse();
  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  al_register_event_source(queue, al_get_mouse_event_source());
  display = al_create_display(800, 600);
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
      if(inBound(220,300, 290,350,event.mouse.x,event.mouse.y))
        n_of_players = 2;
      else if(inBound(370,300, 440,350,event.mouse.x,event.mouse.y))
        n_of_players = 3;
      else if(inBound(520,300, 590,350,event.mouse.x,event.mouse.y))
        n_of_players = 4;  
    }
  }
  printf("%d\n",n_of_players);
  al_destroy_event_queue(queue);
  al_destroy_font(font);
  al_destroy_display(display);
  al_uninstall_mouse();
  return 0;
}
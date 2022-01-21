#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include<time.h>
#include<math.h>
ALLEGRO_FONT *font;
ALLEGRO_COLOR black;
ALLEGRO_COLOR white;
ALLEGRO_COLOR blue;
ALLEGRO_BITMAP *background = NULL;
void number_of_players(){
	  
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
void draw_map(){
	blue = al_map_rgb(173, 207, 212);
	al_clear_to_color(blue);
	int f_or_e[8][8]={0},i,j,x = 75/2+130,y = 0, line = 1, num_of_tile[3];
	num_of_tile[2] = 10;
	num_of_tile[1] = 20;
	num_of_tile[0] = 30;
	ALLEGRO_BITMAP *fish3, *fish2, *fish1, *fish;
	fish3 = al_load_bitmap("3d.png");
	fish2 = al_load_bitmap("2d.png");
	fish1 = al_load_bitmap("1d.png");
	srand(time(NULL));
	int number_of_fish ,k;
	for(i = 1;i<9;i++){
		for(j = 1;j<9;j++){
			number_of_fish = rand()%3;
			switch(number_of_fish){
				case 0:
					fish = fish1;
				break;
				case 1:
					fish = fish2;
				break;
				case 2:
					fish = fish3;
				break;
			}
			if(num_of_tile[number_of_fish] != 0){
				al_draw_bitmap(fish, x, y, 0);
				x += 65;
				num_of_tile[number_of_fish]--;
			}
			else
				j--;
			if(line % 2 != 0 && j == 7){
				j++;
			}
		}
		line++;
		if(line % 2 == 0)
			x = 136;
		else
			x = 75/2 + 133;
		y += 75*(1 - 1/(2*(sqrt(3)))) + 4;
	}
	al_flip_display();
	al_rest(60);
	
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
	draw_map();
	printf("%d\n",n_of_players);
	al_destroy_event_queue(queue);
	al_destroy_font(font);
	al_destroy_display(display);
	al_uninstall_mouse();
	return 0;
}

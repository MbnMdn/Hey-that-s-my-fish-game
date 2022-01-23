#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
ALLEGRO_FONT *font;
ALLEGRO_COLOR black;
ALLEGRO_COLOR white;
ALLEGRO_COLOR blue;
ALLEGRO_BITMAP *background = NULL;
void number_of_players();
int full_or_empty(int f_or_e[8][8], int x, int y, int i);
void location_of_p(int n_of_players,int f_or_e[8][8]);
void draw_map();
int inBound(int x1,int y1, int x2, int y2, int x3, int y3);
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
	int f_or_e[8][8]={0};
	while(n_of_players == 0){
		number_of_players();
		al_flip_display();
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
	int m,g;
	location_of_p(n_of_players,f_or_e);
	al_flip_display();
	al_destroy_event_queue(queue);
	al_destroy_font(font);
	al_destroy_display(display);
	al_uninstall_mouse();
	return 0;
}
void location_of_p(int n_of_players,int f_or_e[8][8]){
	int n_of_png, all_png, i;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_mouse_event_source());
	ALLEGRO_EVENT event;
	ALLEGRO_BITMAP *p1, *p2, *p3, *p4;
	p4 = al_load_bitmap("red.png");
	p3 = al_load_bitmap("yellow.png");
	p2 = al_load_bitmap("blue.png");
	p1 = al_load_bitmap("pink.png");
	switch(n_of_players){
		case 2:
			n_of_png = 4;
			break;
		case 3:
			n_of_png = 3;
			break;
		case 4:
			n_of_png = 2;
			break;
	}
	all_png = n_of_players * n_of_png;
	i=1;
	while(all_png){
			if(i > n_of_players)
				i = 1;
			if(al_is_event_queue_empty(queue)){
			al_flip_display();
			}
			al_wait_for_event(queue, &event);
			if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
				if((inBound(136, 0, 136+8*65, 8*(75*(1 - 1/(2*(sqrt(3)))) + 4), event.mouse.x, event.mouse.y))&&full_or_empty(f_or_e, event.mouse.x, event.mouse.y, i)){
					double x1, y1 = event.mouse.y/(37.7952755906 * 1.5);
					if((int)y1 % 2 == 0)
							x1 = ((int)((event.mouse.x - 75/2 - 133)/65)) * 65  + 75/2 + 100 + 65/2;
					else
							x1 = ((int)((event.mouse.x - 136)/65)) * 65  + 106 + 65/2;
					y1 = ((int)y1) * (37.7952755906 * 1.5) + (37.7952755906 * 0.2);
					switch(i){
						case 1:
						al_draw_bitmap(p1, x1, y1, 1);
						break;
						case 2:
						al_draw_bitmap(p2,  x1, y1, 1);
						break;
						case 3:
						al_draw_bitmap(p3,  x1, y1, 1);
						break;
						case 4:
						al_draw_bitmap(p4,  x1, y1, 1);
						break;
					}
					all_png--;
					i++;
				}
			}
	}
}
int full_or_empty(int f_or_e[8][8], int x, int y, int i){
	int x1, y1 = y/(37.7952755906 * 1.5);
	if(y1 % 2 == 0)
		x1 = (x - 75/2 - 133)/65;
	else
		x1 = (x - 136)/65;
	if(f_or_e[x1][y1] == 0){
		f_or_e[x1][y1] = i;
		return 1;
	}
	else
		return 0;
}
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
	
}
int inBound(int x1,int y1, int x2, int y2, int x3, int y3){
	if(x3>=x1 && x3<= x2 && y3>=y1 && y3<= y2 )	
		return 1;
	return 0;
}

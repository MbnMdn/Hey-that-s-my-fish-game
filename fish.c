#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
ALLEGRO_FONT *font;
ALLEGRO_FONT *font_cheri;
ALLEGRO_FONT *font_cheri_empty;
ALLEGRO_COLOR black;
ALLEGRO_COLOR white;
ALLEGRO_COLOR blue;
void game_name();
void start_page();
void how_to_play();
void number_of_players();
int full_or_empty(int f_or_e[8][8], int x, int y, int i);
int location_of_p(int n_of_players,int f_or_e[8][8], int hazf[4]);
void draw_map(int mahi[8][8]);
int inBound(int x1,int y1, int x2, int y2, int x3, int y3);
int possible(int f_or_e[8][8], int x, int y,int x4, int y4);
void movement(int f_or_e[8][8], int x1, int y1,int x2, int y2, int i, int mahi[8][8], int kashi[4], int score[4]);
void finish_and_delete(int f_or_e[8][8], int mahi[8][8], int kashi[4], int score[4], int hazf[4]);
int number;
//------------------------------------------------------------------------------------------------------
int main(){
	al_init();
	ALLEGRO_DISPLAY *display;
	black = al_map_rgb(0, 0, 0);
	white = al_map_rgb(255, 255, 255);
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
    font = al_load_ttf_font("Penguin.ttf", 40, 0);
	font_cheri = al_load_ttf_font("cheri.ttf", 55, 0);
	font_cheri_empty = al_load_ttf_font("cheri_empty.ttf", 25, 0);
	al_install_mouse();
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_mouse_event_source());
	display = al_create_display(900, 490);
	ALLEGRO_EVENT event;
	int n_of_players = 0, x, y, f_or_e[8][8]={0};
	while(n_of_players == 0){
		game_name();
		al_flip_display();
		al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && inBound(0,0,900,490,event.mouse.x,event.mouse.y)) 
		do{
		start_page();	
		al_flip_display();
	    al_wait_for_event(queue, &event);	
		}
		while (event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP );
		
		if( inBound(100,70,340,120,event.mouse.x,event.mouse.y)){
	    	    do{
     	         	number_of_players();	
		    	    al_flip_display();
	                al_wait_for_event(queue, &event);
	            }
            	while (event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP );
     	    	if     (inBound(220,290,300,370,event.mouse.x,event.mouse.y)){
     	    		    n_of_players = 2;
			    	    number = 2; 
				    }
			    	    
			    else if(inBound(400,290,480,370,event.mouse.x,event.mouse.y)){
			    	    n_of_players = 3;
				        number = 3; 
				   }
				        
		    	else if(inBound(600,290,680,370,event.mouse.x,event.mouse.y)){
		    	    	n_of_players = 4;
						number = 4; 	
				   }
			         	
			      
		}
		else if(inBound(430,70,770,120,event.mouse.x,event.mouse.y)){
		    	do{
     	         	how_to_play();	
		    	    al_flip_display();
	                al_wait_for_event(queue, &event);
	            }
            	while (event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP );
			    if (inBound(20,400,340,470,event.mouse.x,event.mouse.y)){
			    	 do{
     	         	number_of_players();	
		    	    al_flip_display();
	                al_wait_for_event(queue, &event);
	            }
            	while (event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP );

     	    	if     (inBound(220,290,300,370,event.mouse.x,event.mouse.y))
			    	    n_of_players = 2;
			    else if(inBound(400,290,480,370,event.mouse.x,event.mouse.y))
				        n_of_players = 3;
		    	else if(inBound(600,290,680,370,event.mouse.x,event.mouse.y))
			         	n_of_players = 4;	
			     
			    	
				}
		}
	}
	int mahi[8][8] = {0}, kashi[4] = {0}, score[4] = {0}, all_png, i = 1, x1, y1, x2, y2, done, hazf[4] = {10}, s;
	draw_map(mahi);
	all_png = location_of_p(n_of_players,f_or_e, hazf);
	al_flush_event_queue(queue);
	while(done != n_of_players){
		if(i > n_of_players)
				i = 1;
		if(hazf[i-1] == 0){
			i++;
			continue;
		}
		do{
			al_wait_for_event(queue, &event);
			x1 = event.mouse.x;
			y1 = event.mouse.y;
		}while(event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP);
		do{
			al_wait_for_event(queue, &event);
			x2 = event.mouse.x;
			y2 = event.mouse.y;
		}while(event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP);
		y = y1/(37.79 * 1.5);
		if(y % 2 == 0)
			x = (x1 - 75/2 - 133)/65;
		else
			x = (x1 - 136)/65;
		int x4, y4 = y2/(37.79 * 1.5);
		if(y4 % 2 == 0)
			x4 = (x2 - 75/2 - 133)/65;
		else
			x4 = (x2 - 136)/65;
		if((inBound(136, 0, 136+8*65, 8*(75*(1 - 1/(2*(sqrt(3)))) + 4), x2, y2)) && (inBound(136, 0, 136+8*65, 8*(75*(1 - 1/(2*(sqrt(3)))) + 4), x1, y1)) && (f_or_e[x][y] == i)){
			if(possible( f_or_e, x, y, x4, y4) == 1){
				movement(f_or_e, x1, y1, x2, y2, i, mahi, kashi, score);
				finish_and_delete(f_or_e, mahi, kashi, score, hazf);
				al_flip_display();
				i++;
			}
		}
		done = 0;
		for(s = 0;s<n_of_players;s++)
			if(hazf[s] == 0)
				done++;
	}
	al_flip_display();
	al_destroy_event_queue(queue);
	al_destroy_font(font);
	al_destroy_display(display);
	al_uninstall_mouse();
	return 0;
}
//------------------------------------------------------------------------------------------------------
int location_of_p(int n_of_players,int f_or_e[8][8], int hazf[4]){
	int n_of_png, i, all, all_png;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_mouse_event_source());
	ALLEGRO_EVENT event;
	ALLEGRO_BITMAP *p1, *p2, *p3, *p4 ;
	p4 = al_load_bitmap("green.png");
	p3 = al_load_bitmap("yellow.png");
	p2 = al_load_bitmap("blue.png");
	p1 = al_load_bitmap("pink.png");
	
	switch(n_of_players){
		case 2:
			n_of_png = 4;
			hazf[0] = 4, hazf[1] = 4;
			break;
		case 3:
			n_of_png = 3;
			hazf[0] = 3, hazf[1] = 3, hazf[2] = 3;
			break;
		case 4:
			n_of_png = 2;
			hazf[0] = 2, hazf[1] = 2, hazf[2] = 2, hazf[3] = 2;
			break;
	}
	all_png = n_of_players * n_of_png ;
	all = all_png;
	i=1;
	do{
			if(i > n_of_players)
				i = 1;
			if(al_is_event_queue_empty(queue)){
			al_flip_display();
			}
			al_wait_for_event(queue, &event);
			
			if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){ 
				if(!inBound(625,  0,700, 58,event.mouse.x, event.mouse.y)    //1
			    && !inBound(625,115,700,170,event.mouse.x, event.mouse.y)    
			    && !inBound(625,230,700,285,event.mouse.x, event.mouse.y)
			    && !inBound(625,340,700,400,event.mouse.x, event.mouse.y)
			    
				&& !inBound(630,115,700,178,event.mouse.x, event.mouse.y)    //2
				&& !inBound(630,230,700,293,event.mouse.x, event.mouse.y)
				&& !inBound(630,343,700,408,event.mouse.x, event.mouse.y)
				   )
			    
				if((inBound(136, 0, 136+8*65, 8*(75*(1 - 1/(2*(sqrt(3)))) + 4), event.mouse.x, event.mouse.y))&&full_or_empty(f_or_e, event.mouse.x, event.mouse.y, i)){
					double x1, y1 = event.mouse.y/(37.79 * 1.5);
					if((int)y1 % 2 == 0)
							x1 = ((int)((event.mouse.x - 75/2 - 133)/65)) * 65  + 75/2 + 106 + 65/2;
					else
							x1 = ((int)((event.mouse.x - 136)/65)) * 65  + 112 + 65/2;
					y1 = ((int)y1) * (37.79 * 1.5) + (37.79 * 0.2) + 5;
                
 if(n_of_players==4){
    	ALLEGRO_BITMAP *pink4, *blue4, *yellow4, *green4, *empty4 ;
    	ALLEGRO_BITMAP *pink_score, *blue_score, *yellow_score, *green_score; 
    	pink4        = al_load_bitmap("pink4.png");
    	blue4        = al_load_bitmap("blue4.png");
	    yellow4      = al_load_bitmap("yellow4.png");
    	green4       = al_load_bitmap("green4.png");
    	empty4       = al_load_bitmap("empty4.png");
        pink_score   = al_load_bitmap("pink_score.png");
        blue_score   = al_load_bitmap("blue_score.png");
        yellow_score = al_load_bitmap("yellow_score.png");
        green_score  = al_load_bitmap("green_score.png");
        
        al_draw_bitmap(empty4,550,0,0);
			     	
					switch(i){
						case 1:
						al_draw_bitmap(blue4,550,0,0);
						al_draw_bitmap(pink_score,25,50,0);
						break;
						case 2:
						al_draw_bitmap(yellow4,550,0,0);
						al_draw_bitmap(blue_score,25,150,0);
						break;
						case 3:
						al_draw_bitmap(green4,550,0,0);
						al_draw_bitmap(yellow_score,25,250,0);
						break;
						case 4:
						al_draw_bitmap(pink4,550,0,0);
						al_draw_bitmap(green_score,25,350,0);
						break;
					}
 }
 
 if(n_of_players==3){
    	ALLEGRO_BITMAP *pink3, *blue3, *yellow3, *empty3;
    	ALLEGRO_BITMAP *pink_score, *blue_score, *yellow_score;
    	pink3        = al_load_bitmap("pink3.png");
    	blue3        = al_load_bitmap("blue3.png");
	    yellow3      = al_load_bitmap("yellow3.png");
    	empty3       = al_load_bitmap("empty3.png");
    	pink_score   = al_load_bitmap("pink_score.png");
        blue_score   = al_load_bitmap("blue_score.png");
        yellow_score = al_load_bitmap("yellow_score.png");
    	
	    al_draw_bitmap(empty3,622,50,0);
			     	
					switch(i){
						case 1:
						al_draw_bitmap(blue3,622,50,0);	
						al_draw_bitmap(pink_score,25,100,0);
						break;
						case 2:
						al_draw_bitmap(yellow3,622,50,0);
						al_draw_bitmap(blue_score,25,200,0);
						break;
						case 3:
						al_draw_bitmap(pink3,622,50,0);
						al_draw_bitmap(yellow_score,25,300,0);
						break;
					}
 }
 
 if(n_of_players==2){
    	ALLEGRO_BITMAP *pink2, *blue2,  *empty2, *pink_score, *blue_score;
    	pink2        = al_load_bitmap("pink2.png");
    	blue2        = al_load_bitmap("blue2.png");
    	empty2       = al_load_bitmap("empty2.png");
    	pink_score   = al_load_bitmap("pink_score.png");
        blue_score   = al_load_bitmap("blue_score.png");
    
		al_draw_bitmap(empty2,672,100,0);
			     	
					switch(i){
						case 1:
						al_draw_bitmap(blue2,672,100,0);
						al_draw_bitmap(pink_score,25,150,0);	
						break;
						case 2:
						al_draw_bitmap(pink2,672,100,0);
						al_draw_bitmap(blue_score,25,250,0);
						break;
					}
 }
 
					switch(i){
						case 1:
						al_draw_bitmap(p1,  x1, y1, 0);
						break;
						case 2:
						al_draw_bitmap(p2,  x1, y1, 0);
						break;
						case 3:
						al_draw_bitmap(p3,  x1, y1, 0);
						break;
						case 4:
						al_draw_bitmap(p4,  x1, y1, 0);
						break;
					}
					all_png--;
					i++;
				}
			}
			al_flip_display();
	}while(all_png);
	return all;
}
//------------------------------------------------------------------------------------------------------
int full_or_empty(int f_or_e[8][8], int x, int y, int i){
	int x1, y1 = y/(37.79 * 1.5);
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
//------------------------------------------------------------------------------------------------------
void number_of_players(){
  black = al_map_rgb(0, 0, 0);
  ALLEGRO_BITMAP *background;
  background = al_load_bitmap("background.jpg"); 
  al_draw_bitmap(background,0,0,0);
  al_draw_text(font,black,115,200,0,"Select Number of Players");
  al_draw_filled_circle(260,330, 48,black);
  al_draw_text(font,white,238,300,0,"23");
  al_draw_filled_circle(450,330, 48,black);
  al_draw_text(font,white,415,300,0,"524");
  al_draw_filled_circle(640,330, 48,black);
  al_draw_text(font,white,594,300,0,"4531");                                     
}
//------------------------------------------------------------------------------------------------------
void draw_map(int mahi[8][8]){
	blue = al_map_rgb(173, 207, 212);
	al_clear_to_color(blue);
	ALLEGRO_BITMAP  *fish_line, *pink4, *pink3, *pink2, *pink_score, *blue_score, *yellow_score, *green_score; ;
	fish_line    = al_load_bitmap("fish_line.png");
	pink4        = al_load_bitmap("pink4.png");
	pink3        = al_load_bitmap("pink3.png");
	pink2        = al_load_bitmap("pink2.png");
	pink_score   = al_load_bitmap("pink_score.png");
    blue_score   = al_load_bitmap("blue_score.png");
    yellow_score = al_load_bitmap("yellow_score.png");
    green_score  = al_load_bitmap("green_score.png");
	al_draw_bitmap(fish_line,700,0,1);
	al_draw_bitmap(fish_line,800,0,0);

	 if(number==4){
	 	al_draw_bitmap(pink4,550,0,0);
	 	al_draw_bitmap(pink_score,25,50,0);
		al_draw_bitmap(blue_score,25,150,0);
		al_draw_bitmap(yellow_score,25,250,0);
		al_draw_bitmap(green_score,25,350,0);
     }
	 
	  if(number==3){
	 	al_draw_bitmap(pink3,622,50,0);
	 	al_draw_bitmap(pink_score,25,100,0);
		al_draw_bitmap(blue_score,25,200,0);
		al_draw_bitmap(yellow_score,25,300,0);
	 }
	 
	  if(number==2){
	 	al_draw_bitmap(pink2,672,100,0);
	 	al_draw_bitmap(pink_score,25,150,0);
		al_draw_bitmap(blue_score,25,250,0);
	 }
	
	int i,j,x = 75/2+130,y = 0, line = 1, num_of_tile[3];
	num_of_tile[2] = 10;
	num_of_tile[1] = 20;
	num_of_tile[0] = 30;
    // 0=1 tile - 1=2 tiles - 2=3 tiles 
	ALLEGRO_BITMAP *fish3, *fish2, *fish1, *fish;
	fish3 = al_load_bitmap("3d.png");
	fish2 = al_load_bitmap("2d.png");
	fish1 = al_load_bitmap("1d.png");
	srand(time(NULL));
	int number_of_fish;
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
				mahi[j-1][i-1] = number_of_fish + 1;
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
//------------------------------------------------------------------------------------------------------
int inBound(int x1,int y1, int x2, int y2, int x3, int y3){
	if(x3>=x1 && x3<= x2 && y3>=y1 && y3<= y2 )	
		return 1;
	return 0;
}
//------------------------------------------------------------------------------------------------------
void game_name(){
  ALLEGRO_BITMAP *welcome;
  welcome = al_load_bitmap("welcome.jpeg"); 
  al_draw_bitmap(welcome,0,0,0);
  al_draw_text(font_cheri,white,188,90,0,"hey that's my fish!");
  al_draw_text(font_cheri_empty,white,355,170,0,"click to enter");
}
//------------------------------------------------------------------------------------------------------
void start_page(){
  ALLEGRO_BITMAP *start;
  start = al_load_bitmap("start.jpeg"); 
  al_draw_bitmap(start,0,0,0);
}
//------------------------------------------------------------------------------------------------------
void how_to_play(){
  ALLEGRO_BITMAP *how;
  how = al_load_bitmap("how.png"); 
  al_draw_bitmap(how,0,0,0);
}
//-------------------------------------------------------------------------------------------------------
int possible(int f_or_e[8][8], int x, int y,int x4, int y4){
	int x3, y3;
	x3 = x;
	y3 = y;
	if(!(x4>=0 && x4<=7) || !(y4>=0 && y4<=7))
		return 0;
	if(f_or_e[x4][y4] != 0)
		return 3;
	do{//bala rast
		if(y3 % 2 == 0){
			if((x3 == x4) && (y3 == y4)){
				return 1;
			}
			else{
				x3++;
				y3--;
			}
		}
		else{
			if((x3 == x4) && (y3 == y4))
				return 1;
			else{
				y3--;
			}
		}
	}while((f_or_e[x3][y3] == 0) && (x3>=0 && x3<= 7 && y3>=0 && y3<= 7));
	x3 = x;
	y3 = y;
	do{//bala chap
		if(y3 % 2 == 0){
			if((x3 == x4) && (y3 == y4))
				return 1;
			else{
				y3--;
			}
		}
		else{
			if((x3 == x4) && (y3 == y4))
				return 1;
			else{
				x3--;
				y3--;
			}
		}
	}while((f_or_e[x3][y3] == 0) && (x3>=0 && x3<= 7 && y3>=0 && y3<= 7));
	x3 = x;
	y3 = y;
	do{//paen chap
		if(y3 % 2 == 0){
			if((x3 == x4) && (y3 == y4))
				return 1;
			else{
				y3++;
			}
		}
		else{
			if((x3 == x4) && (y3 == y4))
				return 1;
			else{
				x3--;
				y3++;
			}
		}
	}while((f_or_e[x3][y3] == 0) && (x3>=0 && x3<= 7 && y3>=0 && y3<= 7));
	x3 = x;
	y3 = y;
	do{//paen rast
		if(y3 % 2 == 0){
			if((x3 == x4) && (y3 == y4))
				return 1;
			else{
				x3++;
				y3++;
			}
		}
		else{
			if((x3 == x4) && (y3 == y4))
				return 1;
			else{
				y3++;
			}
		}
	}while((f_or_e[x3][y3] == 0) && (x3>=0 && x3<= 7 && y3>=0 && y3<= 7));
	x3 = x;
	y3 = y;
	do{//chap
		if((x3 == x4) && (y3 == y4))
				return 1;
		else{
				x3++;
			}
	}while((f_or_e[x3][y3] == 0) && (x3>=0 && x3<= 7 && y3>=0 && y3<= 7));
	x3 = x;
	y3 = y;
	do{//rast
		if((x3 == x4) && (y3 == y4))
				return 1;
		else{
				x3--;
			}
	}while((f_or_e[x3][y3] == 0) && (x3>=0 && x3<= 7 && y3>=0 && y3<= 7));
	return 0;
}
//-------------------------------------------------------------------------------------------------------
void movement(int f_or_e[8][8], int x1, int y1,int x2, int y2, int i, int mahi[8][8], int kashi[4], int score[4]){
	ALLEGRO_BITMAP *removed = al_load_bitmap("empty67.png");
	ALLEGRO_BITMAP *p1, *p2, *p3, *p4 ;
	p4 = al_load_bitmap("green.png");
	p3 = al_load_bitmap("yellow.png");
	p2 = al_load_bitmap("blue.png");
	p1 = al_load_bitmap("pink.png");
	int a, b = y1/(37.79 * 1.5), n, m;
	if(b % 2 == 0)
		a = (x1 - 75/2 - 133)/65;
	else
		a = (x1 - 136)/65;
	double a2, b2 = y2/(37.79 * 1.5), a1, b1 = b * (75*(1 - 1/(2*(sqrt(3)))) + 4) - 0.9;
	if(b % 2 == 0)
		a1 = 75/2 + 131.5 + (a * 65);
	else
		a1 = 135.5 + (a * 65);
	if((int)b2 % 2 == 0){
		a2 = ((int)((x2 - 75/2 - 133)/65)) * 65  + 75/2 + 106 + 65/2;
		n = (x2 - 75/2 - 133)/65;
	}
	else{
		a2 = ((int)((x2 - 136)/65)) * 65  + 112 + 65/2;
		n = (x2 - 136)/65;
	}
	m = y2/(37.79 * 1.5);
	b2 = ((int)b2) * (37.79 * 1.5) + (37.79 * 0.2) +5;
	score[i-1] += mahi[a][b];
	kashi[i-1]++;
	al_draw_bitmap(removed, a1, b1, 0);
	switch(i){
		case 1:
		al_draw_bitmap(p1,  a2, b2, 0);
		break;
		case 2:
		al_draw_bitmap(p2,  a2, b2, 0);
		break;
		case 3:
		al_draw_bitmap(p3,  a2, b2, 0);
		break;
		case 4:
		al_draw_bitmap(p4,  a2, b2, 0);
		break;
	}
	f_or_e[n][m] = i;
	f_or_e[a][b] = 5;
}
//-------------------------------------------------------------------------------------------------------
void finish_and_delete(int f_or_e[8][8], int mahi[8][8], int kashi[4], int score[4], int hazf[4]){
	int f, u, count, count2 = 0;
		for(f=0;f<8;f++){
			for(u=0;u<8;u++){
					count = 0;
					if((f_or_e[f][u] !=0) && (f_or_e[f][u] !=5)){
					if((u == 0) || (u == 7))
						count +=2;
					if(u % 2 == 0){
						if((f == 0) || (f == 6))
							count++;
						if(possible( f_or_e, f, u, f+1, u-1) == 3)
							count++;
						if(possible( f_or_e, f, u, f+1, u+1) == 3)
							count++;
					}
					else{
						if((f == 0) || (f == 7)){
							count +=3;
							if(u == 7)
								count--;
						}
						if(possible( f_or_e, f, u, f-1, u-1) == 3)
							count++;
						if(possible( f_or_e, f, u, f-1, u+1) == 3)
							count++;
					}
					if(possible( f_or_e, f, u, f+1, u) == 3)
						count++;
					if(possible( f_or_e, f, u, f-1, u) == 3)
						count++;
					if(possible( f_or_e, f, u, f, u-1) == 3)
						count++;
					if(possible( f_or_e, f, u, f, u+1) == 3)
						count++;
					if(count == 6){
						ALLEGRO_BITMAP *removed = al_load_bitmap("empty67.png");
						count2++;
						int m1, m2 = u * (75*(1 - 1/(2*(sqrt(3)))) + 4) - 0.9;
						if(u % 2 == 0)
							m1 = 75/2 + 131.5 + (f * 65);
						else
							m1 = 135.5 + (f * 65);
						al_draw_bitmap(removed,  m1, m2, 0);
						score[f_or_e[f][u]-1] += mahi[f][u];
						kashi[f_or_e[f][u]-1]++;
						hazf[f_or_e[f][u]-1]--;
						f_or_e[f][u] = 5;
						al_flip_display();
					}
					}
				}
			}
		}

/*
THIS GAME IS BEING MADE USING POINTERS AND LINKED LIST AND NCURSES
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define width 60 
#define height 20
#define empty ' '
#define bound '#'

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define x_off 3
#define y_off 3


typedef struct {
	int xco;
	int yco;
} Position;

typedef struct snake_node {
	Position pos;
	struct snake_node* next;//Points to next snake_node of same type struct

} snake_node;

Position food_pos(snake_node* head) {
	Position food;

	int v=0;//not possible
	while(!v) {

		food.xco=rand() % (width-2) + (x_off+1);
		food.yco=rand() % (height-2) + (y_off+1);

		v=1;//assumption
		snake_node* temp=head;
		while(temp != NULL) {//not pointing to null
			if(temp->pos.xco==food.xco && temp->pos.yco==food.yco) {// if food generating on snake
				v=0;
				break;
			}
			temp=temp->next;
		}
	}
	return food;
}


void gameBox(snake_node* head, Position food) { //using ncurses function
	//top and bottom
	for(int i=0; i<width; i++) {
		mvaddch(y_off,x_off+i,bound);//y,x,char - top
		mvaddch(y_off+height-1,x_off+i,bound);//bottom
	}
	//left and right
	for(int i=0; i<height; i++) {
		mvaddch(y_off+i,x_off,bound);//left
		mvaddch(y_off+i,x_off+width-1,bound);//right
	}

	//Food
	mvaddch(food.yco,food.xco,'*');

	//Snake
	snake_node* tempo = head;
	while(tempo != NULL) {
		if(tempo == head) {
			mvaddch(tempo->pos.yco,tempo->pos.xco,'0'); // Snake head
		}
		else {
			mvaddch(tempo->pos.yco,tempo->pos.xco,'o'); // Snake body
		}
		tempo=tempo->next;
	}
}


snake_node* addNode(int x, int y) { //when food eaten, new node needs to be created
	snake_node* newNode=malloc(sizeof(snake_node));//memory allocated for 1snakeNode of the size snakeNode to the newNode
	newNode->pos.xco=x;
	newNode->pos.yco=y;
	newNode->next=NULL;
	return newNode;
}

snake_node* addHead(snake_node* head, int direction) { //to change pos of head when change directions
	snake_node* newHead=malloc(sizeof(snake_node));
	newHead->pos.xco=head->pos.xco;
	newHead->pos.yco=head->pos.yco;
	switch(direction) {
	case UP:
		newHead->pos.yco--;
		break;
	case DOWN:
		newHead->pos.yco++;
		break;
	case LEFT:
		newHead->pos.xco--;
		break;
	case RIGHT:
		newHead->pos.xco++;
		break;

	}
	newHead->next=head;//pointer pointing to next segment after new position of head is old position of head
	return newHead;
}


int ateFood(snake_node* head, Position food) {
	if(head->pos.xco==food.xco && head->pos.yco==food.yco) {
		return 1;
	}
	else {
		return 0;
	}

}


int checkCollision(snake_node* head) {
	if(head->pos.xco<=x_off || head->pos.xco >= x_off+width-1 || head->pos.yco<=y_off || head->pos.yco >= y_off+height-1) {
		return 1;//wall collision
	}
	snake_node* temp=head->next;
	while(temp != NULL) {
		if(head->pos.xco==temp->pos.xco && head->pos.yco==temp->pos.yco) {
			return 1;//with self
		}
		temp=temp->next;
	}
	return 0;
}


void removeTail(snake_node* head) {
	if(!head || !head->next) { //no node present
		return;//return nothing
	}
	snake_node* tempo = head;
	//to go to 2nd last node
	while(tempo->next->next) { //go on till there is last node
		tempo=tempo->next;//tempo becomes 2nd last node
	}
	//remove or free the last node and point newTail to NULL
	free(tempo->next);//the link is gone which points to some other node
	tempo->next=NULL;//the address is null
}

int selectLevel() {
	erase();
	mvprintw(y_off + height/2 - 2, x_off + width/2 - 8, "Select Level:");
	mvprintw(y_off + height/2, x_off + width/2 - 8, "1. Beginner");
	mvprintw(y_off + height/2 + 1, x_off + width/2 - 8, "2. Classic");
	mvprintw(y_off + height/2 + 2, x_off + width/2 - 8, "3. Expert");
	mvprintw(y_off + height/2 + 3, x_off + width/2 - 8, "4. Insane");
	mvprintw(y_off + height/2 + 5, x_off + width/2 - 8, "Press 1-4 to choose.");
	refresh();

	int ch;
	do {
		ch = getch();
	} while (ch != '1' && ch != '2' && ch != '3' && ch != '4');

	return ch - '0'; // returns 1,2,3,4
}

int speeed(int level) {
	switch(level) {
	case 1:
		return 220; //slow
	case 2:
		return 140; //medium(current speed)
	case 3:
		return 80;  //fast
	case 4:
		return 60;  //very fast
	default:
		return 140; //if none
	}
}

void show_instructions() {
	erase();
	int row = y_off + 2;
	int col = x_off + 5;
	mvprintw(row++, col, "=== SNAKE GAME INSTRUCTIONS ===");
	mvprintw(row++, col, " ");
	mvprintw(row++, col, "Controls:");
	mvprintw(row++, col, "  Arrow Keys : Move the snake");
	mvprintw(row++, col, "          q  : Quit the game");
	mvprintw(row++, col, " ");
	mvprintw(row++, col, "Objective:");
	mvprintw(row++, col, "  Eat the '*' food to grow longer.");
	mvprintw(row++, col, "  Avoid running into walls or yourself.");
	mvprintw(row++, col, " ");
	mvprintw(row++, col, "Levels:");
	mvprintw(row++, col, "  Choose your speed at the start:");
	mvprintw(row++, col, "    1 - Beginner   2 - Classic   3 - Expert   4 - Insane");
	mvprintw(row++, col, " ");
	mvprintw(row++, col, "Press any key to start...");
	refresh();
	getch();
}

int main() {
	//head pointer is pointing to struct snakeNode
	//-> operator is used to access members inside a category(struct)
	srand(time(0));
	initscr();//Initialize screen
	cbreak();
	noecho();//no multiple keys
	keypad(stdscr, TRUE);//arrow keys enable

	show_instructions();//so that nodelay does not interfere with getch

	nodelay(stdscr, TRUE);//no delay btw key press
	curs_set(0);//hides cursor

	int again=1;//play again
	while(again) {


		int level = selectLevel();
		int speed = speeed(level);

		//Game_Variables
		int score=0;
		int gameOver=0;//false
		int direction=UP;

		//Initialize snake
		snake_node* head = addNode(x_off+width/2, y_off+height/2);

		//Position of food
		Position food = food_pos(head);

		mvprintw(y_off + height/2 - 5, x_off + width/2 - 5, "GAME START!");
		refresh();
		napms(2000);

		while(!gameOver) {

			int ch=getch();
			switch(ch) {
			case KEY_UP:
				if(direction != DOWN) {
					direction=UP;
				}
				break;
			case KEY_DOWN:
				if(direction != UP) {
					direction=DOWN;
				}
				break;
			case KEY_LEFT:
				if(direction != RIGHT) {
					direction=LEFT;
				}
				break;
			case KEY_RIGHT:
				if(direction != LEFT) {
					direction=RIGHT;
				}
				break;
			case 'p':
				gameOver=1;//true
				break;
			}

			//to move snake
			head=addHead(head,direction);

			if(ateFood(head,food)) {
				score++;
				food=food_pos(head);
			}
			else {
				removeTail(head);
			}

			if(checkCollision(head)) {
				gameOver=1;
			}

			erase();//for smooth animation

			//GameBoard
			gameBox(head,food);

			mvprintw(1,width,"Score: %d",score);//row,column,text

			refresh();//make screen changes visible
			napms(speed);

		}

		mvprintw(y_off + height/2 - 1, x_off + width/2 - 5, "GAME OVER!");//centre
		mvprintw(y_off + height/2, x_off + width/2 - 5, "Score: %d",score);
		refresh();
		napms(500);//0.5sec

		mvprintw(y_off + height/2 - 1, x_off + width/2 - 5, "Play Again? (y/n): ");
		refresh();

		int ch;
		do {
			ch=getch();
		} while(ch != 'y' && ch != 'n');

		if(ch=='y') {
			again=1;
			erase();
			//free memory
			while(head) { //untill no node present
				snake_node* temp=head;//save current node
				head=head->next;//moves to next node
				free(temp);//frees previous node
			}

		}
		else {
			again=0;
		}

	}

	endwin();
	return 0;
}

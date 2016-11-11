#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
	#define clear system("cls")
#else
	#define clear system("clear")
#endif

typedef struct{
	char secretWord[8];
	char knownWord[8];
	char usedLetters[26];
	int mistakes;
	int tries;
	char stickman[7][22];
} Game;

void draw_stickman(Game *game);
void reset_game(Game *game);

int main(void)
{	
	Game game = {
		"",	// secretWord
		"",	// knownWord
		"",	// usedLetters
		0,	// mistakes
		0,	// tries
		{ 
			{ "   ________         "  },
			{ "   |      |         "  },
			{ "   |                "  },
			{ "   |                "  },
			{ "   |                "  },
			{ "   |                "  },
			{ "--------------------"  }
		}
	};
	
	/* Should make the program read theses
	   from a file */
	char words[][8] = {
		"green",
		"yellow",
		"purple",
		"windows",
		"linux",
		"apple"
	};
	
	int right;
	char c;
	
	int inWord;
	
	int menu=1;
	int play=0;
	int players=0;
	
	while (menu) {
		clear;
		
		printf("MENU:\n");
		printf("1 Player\n");
		printf("2 Players\n");
		
		printf("Players: ");
		scanf("%d", &players);
		getchar();
		
		switch (players) {
	
			case 1:
				srand( time(NULL) );
	
				int w = rand()%5;
	
				strcpy( game.secretWord, &words[w][8] );
			
				play=1;
				menu = 0;
			break;
		
			case 2:
				printf("\nType word: ");
				fgets(game.secretWord, sizeof(game.secretWord), stdin);
				
				if (game.secretWord[strlen(game.secretWord)-1] == '\n')
					game.secretWord[strlen(game.secretWord)-1] = '\0';
			
				play=1;
				menu = 0;
			break;
		
			default:
				printf("\nChoice doesnt exist!");
			
				getchar();
			break;
		}
		
		while(play) {
			start:
			
			clear;
			
			draw_stickman(&game);
			
			printf("\n\t");
			
			for (int i=0; i < strlen(game.secretWord); ++i) {
				if (game.knownWord[i] == '\0') {
					putchar('_');
				} else {
					printf( "%c", game.knownWord[i] );
				}
			}
			
			putchar('\n');
			putchar('\n');
			
			printf("Used Letters:\n\t");
			for (int i=0; ( i < strlen(game.usedLetters) ) && (game.usedLetters[i] != '\0'); ++i ) {
				inWord = 0;
				
				for (int j=0; j < sizeof(game.knownWord); ++j) {
					if (game.usedLetters[i] == game.knownWord[j]) {
						inWord = 1;
						break;
					}
				}
				
				if (!inWord) {
					printf("%c ", game.usedLetters[i]);
				}
			}
			putchar('\n');
			putchar('\n');
			
			
			if (game.mistakes == 6) {
				printf("Game Over...\n");
				printf("The word was: %s\n", game.secretWord);
				printf("Continue?(y/n) ");
				scanf("%c", &c);
				getchar();
			
				if (c == 'y') {
					reset_game(&game);
					
					menu=1;
					play=0;
					break;
				} else {
					clear;
					break;
				}
			} else if ( strcmp(game.secretWord, game.knownWord) == 0 ) {
				printf("\nWon the game!\n");
				
				printf("\nContinue?(y/n) ");
				scanf("%c", &c);
				getchar();
			
				if (c == 'y') {
					reset_game(&game);
					
					menu=1;
					play=0;
					break;
				} else {
					clear;
					break;
				}
			}
			
			printf("Type a letter: ");
			scanf("%c", &c);
			getchar();
			
			if ( !isalpha(c) ) {
				printf("Use only a-z(A-z)");
			
				getchar();
			
				continue;
			}
			
			c = tolower(c);
			
			for ( int i=0; i < 26; ++i) {
				if ( game.usedLetters[i] == c ) {
					printf("Already guessed that letter!");
				
					getchar();
				
					goto start;		// Should find a way to remove this
				}
			}
			
			game.usedLetters[game.tries] = c;
			++game.tries;
			
			right = 0;
			
			/* Check for mistakes */
			for ( int pos=0; pos < strlen(game.secretWord); ++pos ) {
				if( c == game.secretWord[pos] ) {
					game.knownWord[pos] = c;
					right = 1;
				}
			}
			
			if (!right) {
				printf("Wrong Letter!");
			
				game.mistakes++;	
			
				getchar();
			}
		}
	}

	return 0;
}

void draw_stickman(Game *game)
{
	/* Add parts to the stickman */
	switch(game->mistakes) {
		case 1:
			game->stickman[2][10] = 'O';
		break;
		
		case 2:
			game->stickman[3][10] = '|';
		break;
		
		case 3:
			game->stickman[3][9] = '/';
		break;
		
		case 4:
			game->stickman[3][11] = '\\';
		break;
		
		case 5:
			game->stickman[4][9] = '/';
		break;
		
		case 6:
			game->stickman[4][11] = '\\';
		break;
	}
	
	/* Actually draw the picture */
	for (int i=0; i<7; ++i) {
		for (int j=0; j<22; ++j) {
			putchar(game->stickman[i][j]);
		}
		putchar('\n');
	}
}

void reset_game(Game *game)
{
	game->mistakes = 0;
	game->tries = 0;

	game->stickman[2][10] = ' ';			
	game->stickman[3][10] = ' ';
	game->stickman[3][ 9] = ' ';
	game->stickman[3][11] = ' ';
	game->stickman[4][ 9] = ' ';
	game->stickman[4][11] = ' ';

	memset( game->secretWord, '\0', sizeof(game->secretWord) );
	memset( game->knownWord, '\0', sizeof(game->knownWord) );
	memset( game->usedLetters, '\0', sizeof(game->usedLetters) );
}



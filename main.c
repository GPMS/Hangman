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

void draw_stickman(char stickman[][22], int miss);

int main(void)
{
	char stickman[7][22] = {
				{ "   ________         "  },
				{ "   |      |         "  },
				{ "   |                "  },
				{ "   |                "  },
				{ "   |                "  },
				{ "   |                "  },
				{ "--------------------"  }	
	};
	char words[][8] = {
		"green",
		"yellow",
		"purple",
		"windows",
		"linux",
		"apple"
	};
	
	char secretWord[20];
	memset( secretWord, '\0', sizeof(secretWord) );
	
	char knownWord[20];
	memset( knownWord, '\0', sizeof(knownWord) );

	char usedLetters[26];
	memset( usedLetters, '\0', sizeof(usedLetters) );
	
	int mistakes=0;
	int right;
	int tries=0;
	char c;
	
	int menu=1;
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
	
				strcpy( secretWord, &words[w][8] );
			
				menu = 0;
			break;
		
			case 2:
				printf("\nType word: ");
				fgets(secretWord, sizeof(secretWord), stdin);
				
				if (secretWord[strlen(secretWord)-1] == '\n') {
					
					secretWord[strlen(secretWord)-1] = '\0';
				}
			
				menu = 0;
			break;
		
			default:
				printf("\nChoice doesnt exist!\n");
			
				getchar();
				getchar();
			break;
		}
	}
	
	while(1) {
		start:
		
		clear;
		
		draw_stickman(stickman, mistakes);
		
		printf("\n\t");
		
		for (int i=0; i < strlen(secretWord); ++i) {
			if (knownWord[i] == '\0') {
				putchar('_');
			} else {
				printf( "%c", knownWord[i] );
			}
		}
		
		putchar('\n');
		putchar('\n');
		
		printf("Used Letters:\n\t");
		for (int i=0; i < strlen(usedLetters); ++i ) {
			if (usedLetters[i] != '\0') {
				printf("%c ", usedLetters[i]);
			}
		}
		putchar('\n');
		putchar('\n');
		
		
		if (mistakes == 6) {
			printf("Game Over...\n\n");
			printf("Continue?(s/n) ");
			scanf("%c", &c);
			getchar();
			
			if (c == 's') {
				mistakes = 0;
				
				/* Reset stickman */
				stickman[2][10] = ' ';			
				stickman[3][10] = ' ';
				stickman[3][ 9] = ' ';
				stickman[3][11] = ' ';
				stickman[4][ 9] = ' ';
				stickman[4][11] = ' ';
				
				continue;	// ignore the rest and start over
			} else {
				system("clear");
				break;
			}
		} else if ( strcmp(secretWord, knownWord) == 0 ) {
			printf("\nWon the game!");
			
			getchar();
			
			system("clear");
			
			break;
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
			if ( usedLetters[i] == c ) {
				printf("Already guessed that letter!");
				
				getchar();
				
				goto start;
			}
		}
		
		usedLetters[tries] = c;
		++tries;
		
		right = 0;
		
		for ( int pos=0; pos < strlen(secretWord); ++pos ) {
			if( c == secretWord[pos] ) {
				knownWord[pos] = c;
				right = 1;
			}
		}
		
		if (!right) {
			printf("Wrong Letter!");
			
			mistakes++;	
			
			getchar();
		}
	}

	return 0;
}

void draw_stickman(char stickman[][22], int mistakes)
{
	switch(mistakes) {
		case 1:
			stickman[2][10] = 'O';
		break;
		
		case 2:
			stickman[3][10] = '|';
		break;
		
		case 3:
			stickman[3][9] = '/';
		break;
		
		case 4:
			stickman[3][11] = '\\';
		break;
		
		case 5:
			stickman[4][9] = '/';
		break;
		
		case 6:
			stickman[4][11] = '\\';
		break;
	}
	
	for (int i=0; i<7; ++i) {
		for (int j=0; j<22; ++j) {
			putchar(stickman[i][j]);
		}
		putchar('\n');
	}
}

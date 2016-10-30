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
	
				strcpy( secretWord, &words[w][8] );
			
				play=1;
				menu = 0;
			break;
		
			case 2:
				printf("\nType word: ");
				fgets(secretWord, sizeof(secretWord), stdin);
				
				if (secretWord[strlen(secretWord)-1] == '\n')
					secretWord[strlen(secretWord)-1] = '\0';
			
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
			for (int i=0; ( i < strlen(usedLetters) ) && (usedLetters[i] != '\0'); ++i ) {
				inWord = 0;
				
				for (int j=0; j < sizeof(knownWord); ++j) {
					if (usedLetters[i] == knownWord[j]) {
						inWord = 1;
						break;
					}
				}
				
				if (!inWord) {
					printf("%c ", usedLetters[i]);
				}
			}
			putchar('\n');
			putchar('\n');
			
			
			if (mistakes == 6) {
				printf("Game Over...\n");
				printf("The word was: %s\n", secretWord);
				printf("Continue?(s/n) ");
				scanf("%c", &c);
				getchar();
			
				if (c == 's') {
					mistakes = 0;
					tries = 0;
				
					/* Reset stickman */
					stickman[2][10] = ' ';			
					stickman[3][10] = ' ';
					stickman[3][ 9] = ' ';
					stickman[3][11] = ' ';
					stickman[4][ 9] = ' ';
					stickman[4][11] = ' ';
					
					/* Reset variables */
					memset( secretWord, '\0', sizeof(secretWord) );
					memset( knownWord, '\0', sizeof(knownWord) );
					memset( usedLetters, '\0', sizeof(usedLetters) );
				
					menu=1;
					play=0;
					break;
				} else {
					clear;
					break;
				}
			} else if ( strcmp(secretWord, knownWord) == 0 ) {
				printf("\nWon the game!\n");
				
				printf("\nContinue?(s/n) ");
				scanf("%c", &c);
				getchar();
			
				if (c == 's') {
					mistakes = 0;
					tries = 0;
					
					/* Reset stickman */
					stickman[2][10] = ' ';
					stickman[3][10] = ' ';
					stickman[3][ 9] = ' ';
					stickman[3][11] = ' ';
					stickman[4][ 9] = ' ';
					stickman[4][11] = ' ';
					
					/* Reset variables */
					memset( secretWord, '\0', sizeof(secretWord) );
					memset( knownWord, '\0', sizeof(knownWord) );
					memset( usedLetters, '\0', sizeof(usedLetters) );
					
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
				if ( usedLetters[i] == c ) {
					printf("Already guessed that letter!");
				
					getchar();
				
					goto start;		// Should find a way to remove this
				}
			}
			
			usedLetters[tries] = c;
			++tries;
			
			right = 0;
			
			/* Check for mistakes */
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
	}

	return 0;
}

void draw_stickman(char stickman[][22], int mistakes)
{
	/* Add parts to the stickman */
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
	
	/* Actually draw the picture */
	for (int i=0; i<7; ++i) {
		for (int j=0; j<22; ++j) {
			putchar(stickman[i][j]);
		}
		putchar('\n');
	}
}

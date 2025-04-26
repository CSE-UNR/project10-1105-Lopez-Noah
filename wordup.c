// Author: Noah Lopez
// Date: 4/26/25
// Purpose: Project 10 

#include <stdio.h>

#define WORD_LEN 5
#define MAX_GUESSES 6


char to_lower(char c);
void read_word(char *word);
int is_valid_guess(char *guess);
int is_alpha(char c);
int strings_equal(char *a, char *b);
void evaluate_guess(char *guess, char *answer, char *result, char *hint);
void print_guesses(char guesses[][WORD_LEN + 1], char results[][WORD_LEN + 1], char hints[][WORD_LEN + 1], int count);

int main() {
	char answer[WORD_LEN + 1];
	read_word(answer);
	if (answer[0] == '\0') return 1; 

	char guesses[MAX_GUESSES][WORD_LEN + 1];
	char results[MAX_GUESSES][WORD_LEN + 1];
	char hints[MAX_GUESSES][WORD_LEN + 1];

	int guess_count = 0;
	int won = 0;

	while (guess_count < MAX_GUESSES && !won) {
	char input[100];

	if (guess_count == MAX_GUESSES - 1) {
		printf("Final Guess: ");
	} else {
	printf("GUESS %d! Enter your guess: ", guess_count + 1);
        }
    
	fgets(input, 100, stdin);

	int valid = is_valid_guess(input);
	if (!valid) {
	printf("Invalid guess. Please enter exactly 5 letters.\n");
	} else {

	char guess[WORD_LEN + 1];
	for (int i = 0; i < WORD_LEN; i++) {
		guess[i] = to_lower(input[i]);
	}
	guess[WORD_LEN] = '\0';

	for (int i = 0; i <= WORD_LEN; i++) {
		guesses[guess_count][i] = guess[i];
	}

	evaluate_guess(guess, answer, results[guess_count], hints[guess_count]);

	printf("================================\n");

	if (strings_equal(guess, answer)) {
		printf("		%s\n", results[guess_count]);
                printf("	You won in %d guesses!\n", guess_count + 1);
                printf("		GOATED!\n");
                won = 1;
                break;
	} else {
	print_guesses(guesses, results, hints, guess_count + 1);
	}

	guess_count++;
	}
    }

	if (!won) {
		printf("You lost, Better luck next time!");
        	printf("\n");
    }

	return 0;
}


char to_lower(char c) {
	if (c >= 'A' && c <= 'Z') {
		return c + 32;
	}
	return c;
}


int is_alpha(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


void read_word(char *word) {
	FILE *file = fopen("word.txt", "r");
	if (file == NULL) {
	printf("Error: Could not open mystery.txt\n");
	word[0] = '\0';
	return;
	}

	char line[100];
	if (fgets(line, 100, file) != NULL) {
		for (int i = 0; i < WORD_LEN; i++) {
			word[i] = to_lower(line[i]);
        }
	word[WORD_LEN] = '\0';
    } else {
	word[0] = '\0';
    }

	fclose(file);
}


int is_valid_guess(char *guess) {
	int len = 0;
	while (guess[len] != '\n' && guess[len] != '\0') {
		if (!is_alpha(guess[len])) {
			return 0;
        }
	len++;
    }
	return len == WORD_LEN;
}


int strings_equal(char *a, char *b) {
	for (int i = 0; i < WORD_LEN; i++) {
		if (a[i] != b[i]) {
			return 0;
			}
		}
	return 1;
}


void evaluate_guess(char *guess, char *answer, char *result, char *hint) {
	for (int i = 0; i < WORD_LEN; i++) {
		result[i] = guess[i]; 
		hint[i] = ' ';        
		}
	for (int i = 0; i < WORD_LEN; i++) {
		if (guess[i] == answer[i]) {
			if (guess[i] >= 'a' && guess[i] <= 'z') {
				result[i] = guess[i] - 32; 
			} else {
		result[i] = guess[i]; 
			}
		}
	}

    
	for (int i = 0; i < WORD_LEN; i++) {
		if (guess[i] != answer[i]) {
			int already_matched = 0;
	for (int j = 0; j < WORD_LEN; j++) {
	if (guess[j] == answer[j] && guess[j] == guess[i]) {
		already_matched = 1;
		break;
		}
	}

            
	if (!already_matched) {
		for (int j = 0; j < WORD_LEN; j++) {
			if (i != j && guess[i] == answer[j]) {
				hint[i] = '^';
				break;
					}
				}
			}
		}
	}
	result[WORD_LEN] = '\0';
	hint[WORD_LEN] = '\0';
}


void print_guesses(char guesses[][WORD_LEN + 1], char results[][WORD_LEN + 1], char hints[][WORD_LEN + 1], int count) {
	for (int i = 0; i < count; i++) {
		printf("%s\n", results[i]);
	int show_hint = 0;
	for (int j = 0; j < WORD_LEN; j++) {
		if (hints[i][j] == '^') {
		show_hint = 1;
                break;
		}
	}

	if (show_hint) {
		printf("%s\n", hints[i]);
	}
	printf("\n");
	}
}


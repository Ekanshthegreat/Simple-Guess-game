/*  Author: Ekansh Chawla  
    For university Assignment 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define NUM_DIGITS 6
#define NUM_POSSIBLE_DIGITS 10

// Function to generate a random sequence
void generateRandomSequence(int answer[]) {
    unsigned int seed;
    char input[20];
    int fail = 0;

    while (1) {
        if (!fail){
            printf("Enter the integer value of the seed for the game: ");
        }
        else{
            printf("Please enter an integer to be the seed for the game: ");
        }

        // Read user input as a string
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            exit(EXIT_FAILURE);
        }

        // Attempt to convert the input to an unsigned integer
        if (sscanf(input, "%u", &seed) == 1) {
            srand(seed);
            break;
        } else {
            printf("Try again you made an error\n");
            fail = 1;
        }
    }

    printf("For each turn enter 6 digits 0 <= digit <= 9 \nSpaces or tabs in your response will be ignored.\n");

    for (int i = 0; i < NUM_DIGITS; i++) {
        answer[i] = rand() % NUM_POSSIBLE_DIGITS;
    }
}

// Function to validate user input
bool isValidGuess(const char* guess) {
    int count_digits = 0;
    bool invalid_character = false;


    for (int i = 0; guess[i] != '\0'; i++) {
        if (isdigit(guess[i])) {
            count_digits++;
        } else if (guess[i] != ' ' && guess[i] != '\t') {
            invalid_character = true;
            break;
        }
    }

    // Check for extra digits
    if (count_digits != NUM_DIGITS) {
    }

    if (invalid_character) {
        printf("ERROR: ");
        if (invalid_character) {
            
            printf("ERROR: A character in your guess was not a digit or a white space\n");
        }
        return false;
    }

    return true;
}

// Function to read user input for guess
// Function to read user input for guess
void readGuess(char guess[NUM_DIGITS]) {
    bool validGuess = false;
    int guessIndex = 0;
    int counter = 0;

    while (!validGuess && guessIndex < NUM_DIGITS) {
        if (counter == 0) {
            printf("\nEnter your guess, 6 digits\n");
        } else {
            printf("You need to enter %d more digits to complete your guess\n", NUM_DIGITS - counter);
        } 

        char inputChar = getchar();

        while (inputChar != '\n' && inputChar != EOF) {
            // Ignore spaces and tabs
            if (inputChar == ' ' || inputChar == '\t') {
                inputChar = getchar();
                continue;
            }

            // Check if input character is a digit
            if (isdigit(inputChar)) {
                guess[guessIndex++] = inputChar;
                counter++;

                if (counter == NUM_DIGITS) {
                    validGuess = true;
                    counter = 0;
                    break;
                }
            } else {
                // If a non-digit character is encountered, reset the index
                printf("ERROR: A character in your guess was not a digit.\n");
                guessIndex = 0;
                counter = 0;
                break;
            }

            inputChar = getchar();
        }

        while (inputChar != '\n' && inputChar != EOF) {
            inputChar = getchar();
        }
    }
}


// Function to check for exact and partial matches
void checkMatches(const int answer[], const char *guess, int* exact_matches, int* partial_matches) {
    *exact_matches = 0;
    *partial_matches = 0;

    // Arrays to keep track of paired digits
    bool isPairedAnswer[NUM_DIGITS] = {false};
    bool isPairedGuess[NUM_DIGITS] = {false};

    // Check for exact matches
    for (int i = 0; i < NUM_DIGITS; i++) {
        if (answer[i] == guess[i] - '0') {
            (*exact_matches)++;
            isPairedAnswer[i] = true;
            isPairedGuess[i] = true;
        }
    }

    // Check for partial matches
    for (int i = 0; i < NUM_DIGITS; i++) {
        if (!isPairedGuess[i]) {
            for (int j = 0; j < NUM_DIGITS; j++) {
                if (!isPairedAnswer[j] && answer[j] == guess[i] - '0') {
                    (*partial_matches)++;
                    isPairedAnswer[j] = true;
                    isPairedGuess[i] = true;
                    break;
                }
            }
        }
    }
}

// Function to display game history
void displayGameHistory(const char history[][NUM_DIGITS], const int exact_matches[], const int partial_matches[], int num_guesses) {
    for (int i = 0; i < num_guesses; i++) {
        printf("Guess %d: ", i + 1);
        for (int j = 0; j < NUM_DIGITS; j++) {
            printf("%c ", history[i][j]);
        }
        printf("- %d correct, %d partially correct\n", exact_matches[i], partial_matches[i]);
    }
}

int main() {
    int answer[NUM_DIGITS];
    generateRandomSequence(answer);

    char guess[NUM_DIGITS + 1];
    char history[100][NUM_DIGITS];
    int exact_matches[100], partial_matches[100];
    int num_guesses = 0;

    while (1) {
        displayGameHistory(history, exact_matches, partial_matches, num_guesses);
        readGuess(guess);

        if (isValidGuess(guess)) {
            checkMatches(answer, guess, &exact_matches[num_guesses], &partial_matches[num_guesses]);
            
            strncpy(history[num_guesses], guess, NUM_DIGITS);
            history[num_guesses][NUM_DIGITS] = '\0';

            num_guesses++;

            if (exact_matches[num_guesses-1] == NUM_DIGITS) {
                printf("YOU DID IT!!\n");                
                
                
                
                break;
            }
        }
    }
                
    displayGameHistory(history, exact_matches, partial_matches, num_guesses);

    return 0;
}




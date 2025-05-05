#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20
#define MAX_WORDS 100

void displayHangman(int tries) {
    printf("\n");
    printf(" +---+\n");
    printf(" |   |\n");
    printf(" %c   |\n", (tries >= 1 ? 'O' : ' '));
    printf("%c%c%c  |\n", (tries >= 3 ? '/' : ' '), 
                         (tries >= 2 ? '|' : ' '), 
                         (tries >= 4 ? '\\' : ' '));
    printf("%c %c  |\n", (tries >= 5 ? '/' : ' '), 
                        (tries >= 6 ? '\\' : ' '));
    printf("     |\n");
    printf(" =======\n\n");
}

// Funcție pentru citirea cuvintelor din fișier
int readWords(const char *filename, char words[][MAX_WORD_LENGTH]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului cuvinte.txt\n");
        exit(1);
    }

    int count = 0;
    while (count < MAX_WORDS && fscanf(file, "%19s", words[count]) == 1) {
        count++;
    }

    fclose(file);
    return count;
}

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount = readWords("cuvinte.txt", words);
    
    srand(time(0));
    const char* secretWord = words[rand() % wordCount];
    int wordLength = strlen(secretWord);
    char guessed[MAX_WORD_LENGTH];
    int lettersGuessed[26] = {0};
    
    for (int i = 0; i < wordLength; i++) {
        guessed[i] = '_';
    }
    guessed[wordLength] = '\0';

    int tries = 0;
    int guessedCorrectly = 0;
    char guess;

    printf("Bine ai venit la Hangman!\n");
    printf("Cuvântul are %d litere.\n", wordLength);

    while (tries < MAX_TRIES && guessedCorrectly < wordLength) {
        displayHangman(tries);
        printf("Cuvânt: %s\n", guessed);
        printf("Litere încercate: ");
        
        for (int i = 0; i < 26; i++) {
            if (lettersGuessed[i]) {
                printf("%c ", 'a' + i);
            }
        }
        printf("\n");
        
        printf("Introdu o literă: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("Te rog introdu doar litere!\n");
            continue;
        }
        
        if (lettersGuessed[guess - 'a']) {
            printf("Ai încercat deja această literă!\n");
            continue;
        }
        
        lettersGuessed[guess - 'a'] = 1;

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (secretWord[i] == guess && guessed[i] == '_') {
                guessed[i] = guess;
                guessedCorrectly++;
                found = 1;
            }
        }

        if (!found) {
            tries++;
            printf("Litera '%c' nu este în cuvânt. Mai ai %d încercări.\n", 
                  guess, MAX_TRIES - tries);
        }
    }

    displayHangman(tries);

    if (guessedCorrectly == wordLength) {
        printf("\nFelicitări! Ai ghicit cuvântul: %s\n", secretWord);
    } else {
        printf("\nAi pierdut! Cuvântul corect era: %s\n", secretWord);
    }

    return 0;
}

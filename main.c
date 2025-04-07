#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRIES 6

void displayHangman(int tries) {
printf("\n");
printf(" +---+\n");
printf(" | |\n");
printf(" %c |\n", (tries >= 1 ? 'O' : ' '));
printf("%c%c%c |\n", (tries >= 3 ? '/' : ' '), (tries >= 2 ? '|' : ' '), (tries >= 4 ? '\\' : ' '));
printf("%c %c |\n", (tries >= 5 ? '/' : ' '), (tries >= 6 ? '\\' : ' '));
printf(" |\n");
printf("=====\n\n");
}

int main() {
const char* secretWord = "hangman"; // Poți schimba cu alt cuvânt
int wordLength = strlen(secretWord);
char guessed[wordLength + 1];

for (int i = 0; i < wordLength; i++) {
guessed[i] = '_';
}
guessed[wordLength] = '\0';

int tries = 0;
int guessedCorrectly = 0;
char guess;

printf("Bine ai venit la Hangman!\n");

while (tries < MAX_TRIES && guessedCorrectly < wordLength) {
displayHangman(tries);
printf("Cuvântul: %s\n", guessed);
printf("Ghicește o literă: ");
scanf(" %c", &guess);

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
printf("Greșit! Încercări rămase: %d\n", MAX_TRIES - tries);
}
}

displayHangman(tries);

if (guessedCorrectly == wordLength) {
printf("Felicitări! Ai ghicit cuvântul: %s\n", secretWord);
} else {
printf("Ai pierdut! Cuvântul era: %s\n", secretWord);
}

return 0;
}

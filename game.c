#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for working with strings (strcmp)
#include <time.h>   // for generating numbers

#define WORDS 15
#define DICE 100

char *lowerCase(char *original); // works as expected => tested
char *upperCase(char *original); // works as expected => tested
int generateRandom(char *game);  // works as expected => tested
int replay(char *game);          // works as expected => tested
void diceGame();                 // works as expected => tested
int verifyChNumber(char *ch);    // works as expected => tested
void rules(char *game, int n);   // works as expected => tested
void hangmanPrint(int tries);    // works as expected => tested
char lowerL(char c);             // works as expected => tested
int verifyWin(int n, char *word);
void hangman(int n);
void printWord(char *word, int len); // works as expected => tested
char *extractWord(int len);          // works as expected => tested

// invalid numbers of characters => return 1;
// invalid game choice => return 2;
// invalid number => return 3;
int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        // not enough or too many arguments
        printf("\nUsage ./game game number[optional].\n");
        printf("Not enought or too many arguments.\n\n");
        return 1;
    }
    // timer init for random generation
    srand(time(NULL)); // Initialization, should only be called once.
    // game type
    char *game = argv[1];
    game = lowerCase(game);
    // printf("%s\n",game);
    if (argc == 2)
    {
        // can play hangman and dices must check wich one
        if (strcmp(game, "hangman") == 0)
        {
            // play hangman with a random number of letteres
            int letters = generateRandom(game);
            hangman(letters);
            // printf("\n%d\n\n", letters); // printf("\nRandom hangman\n\n");
        }
        else if (strcmp(game, "dice") == 0)
        {
            // play dices;
            // printf("\nDice\n\n");
            diceGame();
        }
        else
        {
            printf("\nNothing\n\n");
            return 2;
        }
    }
    else if (argc == 3)
    {
        // can play only hangman

        if (strcmp(game, "hangman") == 0)
        {
            // the user has imputed hangman
            int letters = 0;
            char *ch = argv[2];
            letters = verifyChNumber(ch);
            if (letters < 5 || letters > 12)
            {
                printf("Usage ./game game number[optional].\n");
                printf("Not a valid number of letters try grather than 4 and lower than 13\n");
                return 3;
            }
            if (letters >= 5 && letters <= 12)
            {
                hangman(letters);
            }
            // printf("%d", letters);
        }
        else
        {
            // did not chose the hangman so it is a bad input
            printf("Usage ./game game number[optional].\n");
            printf("Ex.: ./game hangman 7.\n");
            return 2;
        }
    }
    return 0;
}

void hangman(int n)
{

    int again = 1;
    char *word = (char *)malloc(sizeof(char) * n);
    char *c = (char *)calloc(n, sizeof(char));
    char guess;
    while (again == 1)
    {
        int try = 6;
        rules("hangman", n);
        word = extractWord(n);
        // printf("%s",word);
        int *say = (int *)calloc(32, sizeof(int));
        while (try != 0)
        {
            int exists = 2;
            guess = getchar();
            fflush(stdin);
            getchar();
            guess = lowerL(guess);
            int num = guess - 'a';
            if (say[num] == 1)
            {
                printf("you already sayed this!\n");
                exists = 2;
            }
            else
            {
                for (int i = 0; i < n; i++)
                {

                    // putchar(guess);
                    // putchar(word[i]);

                    if (word[i] == guess)
                    {
                        say[num] = 1;
                        c[i] = guess;
                        exists = 1;
                    }
                }
            }
            if (exists == 2)
            {
                try--;
            }
            if (verifyWin(n, c))
            {
                printf("You won! Congratulations!\n");
                break;
            }
            if (try != 0)
            {
                printf("Your games look like that:\n");
                hangmanPrint(try);
                printWord(c, n);
                printf("What's your next guess?\n");
            }
        }
        hangmanPrint(try);
        free(say);

        again = replay("hangman");
        // printf("%d\n", again);
    }
    free(word);
    free(c);
}

int verifyWin(int n, char *word)
{
    int complete = 0;
    for (int i = 0; i < n; i++)
    {
        if (word[i])
        {
            complete++;
        }
    }
    if (complete == n)
    {
        return 1;
    }
    return 0;
}

void printWord(char *word, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (word[i])
        {
            printf("%c ", word[i]);
        }
        else
        {
            printf("- ");
        }
    }
}
char *extractWord(int len)
{
    FILE *input = NULL;
    switch (len)
    {
    case 5:
        input = fopen("5.txt", "r");
        break;
    case 6:
        input = fopen("6.txt", "r");
        break;
    case 7:
        input = fopen("7.txt", "r");
        break;
    case 8:
        input = fopen("8.txt", "r");
        break;
    case 9:
        input = fopen("9.txt", "r");
        break;
    case 10:
        input = fopen("10.txt", "r");
        break;
    case 11:
        input = fopen("11.txt", "r");
        break;
    case 12:
        input = fopen("12.txt", "r");
        break;
    default:
        printf("Something wrong");
        break;
    }
    if (input == NULL)
    {
        printf("The state could not ben opened!\n");
        fclose(input);
        return "";
    }
    int r = rand() % WORDS;
    // printf("\t%d\t", r);
    int n = 0;
    char *word = (char *)malloc(sizeof(char) * (len));
    while (n == r)
    {
        fgets(word, len + 1, input);
        // printf("\t%d\t", len);
        // printf("%s", word);
        n++;
    }
    fclose(input);
    return word;
}

void hangmanPrint(int tries)
{
    FILE *input = fopen("pose0.txt", "r");
    switch (tries)
    {
    case 6:
        input = fopen("pose0.txt", "r");
        break;
    case 5:
        input = fopen("pose1.txt", "r");
        break;
    case 4:
        input = fopen("pose2.txt", "r");
        break;
    case 3:
        input = fopen("pose3.txt", "r");
        break;
    case 2:
        input = fopen("pose4.txt", "r");
        break;
    case 1:
        input = fopen("pose5.txt", "r");
        break;
    case 0:
        input = fopen("pose6.txt", "r");
        break;
    default:
        printf("Something wrong");
        break;
    }
    if (input == NULL)
    {
        printf("The state could not ben opened!\n");
        fclose(input);
        return;
    }
    char *word = (char *)malloc(sizeof(char) * 8);
    while (fgets(word, sizeof(word), input))
    {
        printf("%s", word);
    }
    free(word);
    fclose(input);
}

// verify if the argument from the user is a correct number of letters
int verifyChNumber(char *ch)
{
    int letters = 0;
    if (!strcmp(ch, "5") || !strcmp(ch, "6") || !strcmp(ch, "7") || !strcmp(ch, "8") || !strcmp(ch, "9") || !strcmp(ch, "10") || !strcmp(ch, "11") || !strcmp(ch, "12"))
    {
        if (!strcmp(ch, "10") || !strcmp(ch, "11") || !strcmp(ch, "12"))
        {
            letters = (ch[0] - (int)'0') + (ch[1] - (int)'0') * 10;
        }
        else
        {
            letters = (int)ch[0] - (int)'0';
        }
    }
    return letters;
}

// change the string into lowercase
char *lowerCase(char *original)
{

    int chars = strlen(original);
    // printf("len: %d of the %s\n",chars, original);
    for (int i = 0; i < chars; i++)
    {
        if (original[i] >= 'A' && original[i] <= 'Z')
        {
            // uppercase
            original[i] = original[i] + ('a' - 'A');
        }
    }
    return original;
}

// change a string into uppercase
char *upperCase(char *original)
{

    int chars = strlen(original);
    // printf("len: %d of the %s\n",chars, original);
    for (int i = 0; i < chars; i++)
    {
        if (original[i] >= 'A' && original[i] <= 'Z')
        {
            // uppercase
            original[i] = original[i] - ('a' - 'A');
        }
    }
    return original;
}

// generate a number between 0 and 12
int generateRandom(char *game)
{
    int min = 0;
    int max;
    int r = 0;
    if (strcmp(game, "hangman") == 0)
    {
        min = 5;
        max = 12;
        r = rand() % max; // Returns a pseudo-random integer between 0 and max - 1;
        if (r + min > 12)
        {
            min = 0;
        }
    }
    else if (strcmp(game, "dice") == 0)
    {
        max = DICE;
        r = rand() % max;
    }
    return (r + min);
}

void rules(char *game, int n)
{
    // n -> represents number of ties for dice and number of letters for hangman
    if (strcmp(game, "dice") == 0)
    {
        // Rules for dicegame
        printf("\nWelcome to dices game\n\n");
        printf("Rules: \n1. You have %d tries to guess a number generatetautomaticaly.\n", n);
        printf("2. The number you have to quess is between 0 and %d.\n", DICE);
        printf("3. Each time you try you will get a hint if the number is bigger or smaller.\n");
        printf("4.Remember the numbers are generated automaticaly and may differ each game");
        printf("\nGOODLUCK!\n");
        printf("\nYour first number is? :");
    }
    else if (strcmp(game, "hangman") == 0)
    {
        // Rules for hangman
        printf("\nHangman\n\n");
        printf("Rules: \n1. You have 6 tries to guess a word chosen automatically.\n");
        printf("2. The word has %d letters.\n", n);
        printf("3. Each time you answer correctly the world will be fulfilled.\n");
        printf("4. You are allowed only to guess letters.\n");
        printf("5. Each wrong answer will cost you 1 try.\n");
        printf("\nGOODLUCK!\n");
        printf("Your word looks like that: ");
        for (int i = 0; i < n; i++)
        {
            printf("_ ");
        }
        printf("What is your first guess?: ");
    }
}

void diceGame()
{
    int number, try, guess, min, max;
    char *game = "dice";

    // generate the number to guess

    // printf("\n%d\n\n",number);

    int again = 1;
    while (again == 1)
    {
        number = generateRandom(game);
        try = 6;
        rules("dice", try);
        min = 0;
        max = DICE;
        // printf("%d\n",number);
        do
        {
            do
            {
                scanf("%d", &guess);
            } while (guess < 0 || guess > DICE);

            try--;

            if (guess > number)
            {
                printf("\nThe number is lower than %d. You have left %d tries\n", guess, try);
                if (guess <= max)
                {
                    max = guess;
                    printf("\nYour new interval is %d - %d\n", min, max);
                }
                else
                {
                    printf("Your number is bigger than max interval number. Your interval remain the same.\n %d - %d\n", min, max);
                }
            }
            else if (guess < number)
            {
                printf("\nThe number is higher than %d. You have left %d tries\n", guess, try);
                if (guess >= min)
                {
                    min = guess;
                    printf("\nYour new interval is %d - %d\n", min, max);
                }
                else
                {
                    printf("Your number is lower than min interval number. Your interval remain the same.\n %d - %d\n", min, max);
                }
            }
            else if (guess == number)
            {
                printf("You win! Congrats!!!\n");
                break;
            }
            else
            {
                printf("Try a valid number.\n");
                // continue;
            }
            if (try != 0)
            {
                printf("Your next guess is?: ");
            }
            else
            {
                printf("Sorry you lost. You should try again sometime!\n");
                printf("The number was %d\n", number);
            }

        } while (try != 0);
        again = replay("dice");
    }
}

char lowerL(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        c += ('a' - 'A');
        // putchar(c);
    }
    return c;
}

int replay(char *game)
{
    printf("\nDo you want to play again? [Y/N]: ");
    char ans;
    if (strcmp(game, "dice") == 0)
    { // get the last char
        getchar();
        fflush(stdin);
        ans = getchar(); // get the real char
    }
    else
    {
        ans = getchar(); // get the real char
        fflush(stdin);
        getchar();
    }
    int r = 0;
    // scanf("%c", &answ);
    // putchar(ans);

    ans = lowerL(ans);
    if (ans == 'y')
    {
        r = 1;
    }
    else if (ans == 'n')
    {
        printf("\nWe hope you had a goodtime! Thanks for playing!\n");
        printf("Play again sometime");
        r = 0;
    }
    return r;
}
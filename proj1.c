#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Created by Vladislav Pastushenko
// xpastu04
// 16.11.2019

// Realized premium tast 
// If you will add flag '-p', the search will be carried out with premium tasks condition
// Example:
// ***
// $ ./proj1 -p 12 <list.txt
// ***
// (review the function "searchingPremium")

// Function "makeList"
// -------------------
// It gets array "strings[][64]" with strings with maximum length 64, read all words in "stdin"
// and puts it to "strings" in correct format.
// Also, it controls format of getting data (stdin): add data to "stderr" and returns -1 if there were any format errors.
// If there weren't errors returns 1. 
// If end of file returns 0. 
int makeContact(char contact[])
{
    memset(contact, 0, strlen(contact));
    char word[99]; // "word" - current word, that is read in a file
    if (scanf("%s", word) == -1) {
        return 0;
    }

    // Control that the contact begin with a name (letter word)
    if (atoi(word) != 0) {
        fprintf(stderr, "The name haven't to contain numerals\n");
        return -1;
    }

    while (atoi(word) == 0)
    {
        //
        // Control that the name don't contain any integers
        //
        for (unsigned i = 0; i < strlen(word); i++) {
            if (word[i] >= '0' && word[i] <= '9') {
                fprintf(stderr, "There haven't to be integers in name\n");
                return -1;
            }
        }

        sprintf(contact, "%s%s ", contact, word); // Put a word on a string

        scanf("%s", word); // Get a next word
    }

    //
    // Control that the length of a contact number contain more than 9 symbols ("123456789" format)
    //
    if (strlen(word) < 9) {
        fprintf(stderr, "Number have to contain minimum 9 numerals\n");
        return -1;
    }

    //
    // Control that the contact number don't contain any letters
    //
    for (unsigned i = 0; i < strlen(word); i++) {
        if (!((word[i] >= '0' && word[i] <= '9') || word[i] == '+')) {
            fprintf(stderr, "There haven't to be letters in a contact number\n");
            return -1;
        }
    }

    sprintf(contact, "%s\b, %s\n", contact, word);

    return 1;
}


// Function "searching"
// -------------------
// Function looks for matches of the contact and parameter.
// Parameter "param" have to contain figures which will be 'keys' for the search.
// Each digit has its own characters. 1 (1), 2 (2abc), 3 (3def), 4 (4ghi), 5 (5jkl), 6 (6mno), 7 (7pqrs), 8 (8tuv), 9 (9wxyz), 0 (0+)
// Function tries to find the continuous sequence of symbols in the contact, which is corresponds to continuous sequence of keys in parametr. 
// Returns 1 if it was found, 0 if not, and -1 if argument contains any symbol, that isn't digit
int searching(char* contact, char* param)
{
    for (unsigned i = 0; i < strlen(param); i++) {
        if (!(param[i] >= '0' || param[i] <= '9'))
        {
            fprintf(stderr, "You have to write only integers in parametr\n");
            return -1;
        }
    }

    char stringToInt[64] = "";

    for (unsigned i = 0; i < strlen(contact); i++) {
        char c = contact[i];

        if ((c >= 'a' && c <= 'c') || (c >= 'A' && c <= 'C') || (c == '2'))
            sprintf(stringToInt, "%s%s", stringToInt, "2");

        else if ((c >= 'd' && c <= 'f') || (c >= 'D' && c <= 'F') || (c == '3'))
            sprintf(stringToInt, "%s%s", stringToInt, "3");

        else if ((c >= 'g' && c <= 'i') || (c >= 'G' && c <= 'I') || (c == '4'))
            sprintf(stringToInt, "%s%s", stringToInt, "4");

        else if ((c >= 'j' && c <= 'l') || (c >= 'J' && c <= 'L') || (c == '5'))
            sprintf(stringToInt, "%s%s", stringToInt, "5");

        else if ((c >= 'm' && c <= 'o') || (c >= 'M' && c <= 'O') || (c == '6'))
            sprintf(stringToInt, "%s%s", stringToInt, "6");

        else if ((c >= 'p' && c <= 's') || (c >= 'P' && c <= 'S') || (c == '7'))
            sprintf(stringToInt, "%s%s", stringToInt, "7");

        else if ((c >= 't' && c <= 'v') || (c >= 'T' && c <= 'V') || (c == '8'))
            sprintf(stringToInt, "%s%s", stringToInt, "8");

        else if ((c >= 'w' && c <= 'z') || (c >= 'W' && c <= 'Z') || (c == '9'))
            sprintf(stringToInt, "%s%s", stringToInt, "9");

        else if ((c == '0') || (c == '+'))
            sprintf(stringToInt, "%s%s", stringToInt, "0");

        else if (c == '1')
            sprintf(stringToInt, "%s%s", stringToInt, "1");

        else if (c == '\0') break;
    }

    if (strstr(stringToInt, param) != NULL)
        return 1;

    else return 0;

}

// Function "searchingPremium"
// -------------------
// Function looks for matches of the contact and parameter.
// Parameter "param" have to contain figures which will be 'keys' for the search.
// Each digit has its own characters. 1 (1), 2 (2abc), 3 (3def), 4 (4ghi), 5 (5jkl), 6 (6mno), 7 (7pqrs), 8 (8tuv), 9 (9wxyz), 0 (0+)
// Function tries to find the sequence of symbols in the contact, which is corresponds to sequence of keys in parametr.
// The difference with function "searching" is that function "searchingPremium" can search discontinuous sequence of symbols.
// Returns 1 if it was found, 0 if not, and -1 if argument contains any symbol, that isn't digit
int searchingPremium(char* contact, char* param)
{
    int n = 0;
    for (unsigned c = 0; c < strlen(contact); c++) {
        if (param[n] == '1') {
            if (contact[c] == '1') {
                n++;
                continue;
            }
        }

        else if (param[n] == '2') {
            if ((contact[c] >= 'a' && contact[c] <= 'c') || (contact[c] >= 'A' && contact[c] <= 'C') || (contact[c] == '2')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '3') {
            if ((contact[c] >= 'd' && contact[c] <= 'f') || (contact[c] >= 'D' && contact[c] <= 'F') || (contact[c] == '3')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '4') {
            if ((contact[c] >= 'g' && contact[c] <= 'i') || (contact[c] >= 'G' && contact[c] <= 'I') || (contact[c] == '4')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '5') {
            if ((contact[c] >= 'j' && contact[c] <= 'l') || (contact[c] >= 'J' && contact[c] <= 'L') || (contact[c] == '5')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '6') {
            if ((contact[c] >= 'm' && contact[c] <= 'v') || (contact[c] >= 'M' && contact[c] <= 'V') || (contact[c] == '6')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '7') {
            if ((contact[c] >= 'p' && contact[c] <= 's') || (contact[c] >= 'P' && contact[c] <= 'S') || (contact[c] == '7')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '8') {
            if ((contact[c] >= 't' && contact[c] <= 'v') || (contact[c] >= 'T' && contact[c] <= 'V') || (contact[c] == '8')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '9') {
            if ((contact[c] >= 'w' && contact[c] <= 'z') || (contact[c] >= 'W' && contact[c] <= 'Z') || (contact[c] == '9')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '0') {
            if ((contact[c] == '+') || (contact[c] == '0')) {
                n++;
                continue;
            }
        }

        else if (param[n] == '\0') return 1;

        //
        // Control that the parametr contains only integers
        //
        else {
            fprintf(stderr, "You have to write only integers in parametr\n");
            return -1;
        }
    }

    if (param[n] == '\0') return 1; // This condition will be met if the last key in parameter will match with the last symbol in a contact 

    return 0;
}

int (*search) (char* contact, char* param);

int main(int argc, char* argv[])
{

    //
    // Control a quantity of arguments
    //
    if (argc > 3) {
        fprintf(stderr, "There have to be maximum two argument\n");
        return 1;
    }
    //



    //
    // Print whole list if there are no arguments
    //
    else if (argc == 1) {
        char contact[64];
        for (int i = makeContact(contact); i != 0; i = makeContact(contact))
        {
            if (i == -1) return 1;
            printf("%s", contact);
        }
    }
    //



    else if (argc == 2 || argc == 3)
    {
        char* param;

        //
        // If user put only parameter the search will be carried out with the function "searching"
        //
        if (argc == 2) {

            if (strcmp(argv[1], "-p") == 0) {
                fprintf(stderr, "Missing argument 2 with parameter\n");
                return 1;
            }

            search = searching;
            param = argv[1]; // Variable "param" contains the argument with parametrs or searching
        }
        //


        //
        // If user put only parameter the search will be carried out with the function "searchingPremium" for premium task
        //
        else if (argc == 3) {
            param = argv[2]; // Variable "param" contains the argument with parametrs or searching

            if (strcmp(argv[1], "-p") == 0) {
                search = searchingPremium;
            }
            else {
                fprintf(stderr, "Use less arguments or use flag '-p' as a first argument.\nFlag '-p' will change ordinary searching to premium searching\n");
                return 1;
            }
        }
        //




        bool notFound = true;

        //Check every contact in the contact list
        char contact[64];
        for (int i = makeContact(contact); i != 0; i = makeContact(contact))
        {
            if (i == -1) return 1; // Finish the program if found format mistakes

            int searchResult = search(contact, param);

            if (searchResult == -1) return 1;  // Finish the program if found mistakes in parameter
            else if (searchResult == 1) {
                printf("%s", contact);
                notFound = false;
            }

        }

        //
        // If haven't found nothing, and haven't changed "notFound" from false to true, print "Not found"
        //
        if (notFound) {
            printf("Not found\n");
            return 0;
        }
    }

    return 0;
}
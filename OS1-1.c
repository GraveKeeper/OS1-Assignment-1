// If you are not compiling with the gcc option --std=gnu99, then
// uncomment the following line, or you might get a compiler warning
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
 * Assignment 1
Reads a CSV file with movie data that is provided to the program as an argument
Processes the data in the file to create structs to hold data for each movie
Creates a linked list of all these structs
Gives user choices to ask questions about the movies in the data
Prints out the data about the movies per user choice
 */
// File information -> files will have no whitespace and the first line will be the header
// title - move name (string)
// year - 4 digit value between 1900 and 2021 (int)
// language - languages of release (string list) maybe use substring ?
// rating - value between {1-10} can be int or double

struct movie
{
    char* title;
    int year;
    char* language;
    double rating;
    struct movie *next;
};

/* Parse the current line which is space delimited and create a
*  movie struct
*/
struct movie *createMovie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;

    // The token for Title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy((char *) currMovie->title, token);

    // The token for Year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = atoi(token);

    // The token for Language
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->language = (char*)calloc(strlen(token) + 1, sizeof(char));
    strcpy((char *) currMovie->language, token);

    // The token for Rating
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = strtod((token) , NULL);
    //strcpy((double) currMovie->rating, token);

    // Set the next node to NULL in the newly created Movies entry
    currMovie->next = NULL;
    return currMovie;
}

/*
* Return a linked list of Movies by parsing data from
* each line of the specified file.
*/

struct movie* processFile(char *filePath)
{
    // print message saying file was processed
    printf("File Processed\n");
    fflush(stdout);
    FILE *movieFile = fopen(filePath, "r");

    if(movieFile == NULL){
        printf("broken");
    }

    char *currLine = NULL;
    size_t len = 0;
    size_t nread;
    char *token;
    int movNum = -1;
    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        // Get a new Movie node corresponding to the current line
        struct movie *newNode = createMovie(currLine);
        // Is this the first node in the linked list?
        movNum++;
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    printf("File processed,%s and parsed data for %d movies\n\n", filePath, movNum);
    free(currLine);
    fclose(movieFile);
    return head;
}

/*
* Print data for the given movies
*/
void printMovie(struct movie* aMovie){
    printf("%s, %d ,%s, %1f\n", aMovie->title,
           aMovie->year,
           aMovie->language,
           aMovie->rating);
}
/*
* Print the linked list of movies
*/
void printMovieList(struct movie *list)
{
    while (list != NULL)
    {
        printMovie(list);
        list = list->next;
    }
}

void sRating(struct movie *list)
{
    printf("");
    Node * currentNode = firstNode;
    int year, wanted_year;

    while (currentNode->nextNode != 0)
    {

        year = currrentNode->year;
        if (wanted_uear = year)
        {
            // print out something
        }

        currentNode = currentNode->nextNode;
    }
}

void sLanguage(struct movie *list)
{
    char* movieLang;
    printf("\nWhat language would you like to see: ");
    scanf("%s", movieLang);

    struct movie *currentNode = list;
    while (currentNode->next != NULL)
    {
        *movieLang = *currentNode->language;
        if (strcmp(movieLang, language)==0)
            printMovie(currentNode);
        currentNode = currentNode -> next;
    }
}
/*
*   Process the file provided as an argument to the program to
*   create a linked list of student structs and print out the list.
*   Compile the program as follows:
*       gcc --std=gnu99 -o students main.c
*/

// list options and prompt user for choice
void optionList()
{
    printf("1. Show movies released in a specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit program\n\n");
}


// properly check input and give valid response
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies_sample_1.csv\n");
        return EXIT_FAILURE;
    }
    struct movie *list = processFile(argv[1]);
    printMovieList(list);

    int uChoice = 0;
    int sYear;
    bool validIn = true;
    while(true)
    {
        optionList();
        scanf("%d", uChoice);
        optionList();
        if(uChoice == 1) {
            printf("\nWhat year would you like to see: ");
            scanf("%d", &sYear);
            validyear = check_input(list, sYear);
            if(validyear == true)
            {
                printMYear(list, sYear);
            }
            else
                printf("No movie information for the entered year\n\n", sYear);
        }
        else if(uChoice == 2)
            sRating(list);
        else if(uChoice == 3)
            sLanguage(list);
        else if(uChoice == 4)
            break;
        else
            printf("\nError: please enter a valid option or type 4 to exit\n");
    }
    return EXIT_SUCCESS;
}
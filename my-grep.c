/*Made By: Joona Manninen
18.7.2023*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 2048

// Custom getline function that dynamically allocates memory for the line
// and returns the length of the line
size_t my_getline(char **line, size_t *buffersize, FILE *stream)
{
    int c;
    size_t i = 0;

    if (*line == NULL)
    {
        *buffersize = MAX_LINE_LENGTH;
        *line = (char *)malloc(*buffersize);
    }

    // Read characters from the stream until end of file or newline character
    while ((c = getc(stream)) != EOF && c != '\n')
    {
        (*line)[i++] = c;

        // If the line exceeds the current buffer size, reallocate more memory
        if (i == *buffersize)
        {
            *buffersize *= 2;
            *line = (char *)realloc(*line, *buffersize);
        }
    }

    // Add a newline character to the line if it's not empty or ends with newline
    if (i > 0 || c == '\n')
    {
        (*line)[i++] = '\n';
    }

    // Add null terminator to the line
    (*line)[i] = '\0';

    return i;
}

int main(int argc, char *argv[])
{
    // Check if a search term is provided
    if (argc < 2)
    {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    // Get the search term
    char *searchTerm = argv[1];

    // Check if the search term is an empty string
    int emptySearchTerm = (strlen(searchTerm) == 0);

    // Check if at least one file is specified
    if (argc < 3)
    {
        // If no file specified, read from standard input
        char *line = NULL;
        size_t buffersize = 0;
        size_t linelen;

        // Read each line from standard input and search for the search term
        while ((linelen = my_getline(&line, &buffersize, stdin)) != -1)
        {
            if (emptySearchTerm || strstr(line, searchTerm) != NULL)
            {
                // Print the line if it contains the search term
                printf("%s", line);
            }
        }

        free(line);
        exit(0);
    }

    // Iterate through each file
    for (int i = 2; i < argc; i++)
    {
        // Open the file
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            printf("my-grep: cannot open file\n");
            exit(1);
        }

        // Read and search each line from the file
        char *line = NULL;
        size_t buffersize = 0;
        size_t linelen;

        // Read each line from the file and search for the search term
        while ((linelen = my_getline(&line, &buffersize, file)) > 0)
        {
            if (emptySearchTerm || strstr(line, searchTerm) != NULL)
            {
                // Print the line if it contains the search term
                printf("%s", line);
            }
        }

        free(line);
        fclose(file);
    }

    return 0;
}

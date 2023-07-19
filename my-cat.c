/*Made By: Joona Manninen
18.7.2023*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // Check if at least one file is specified
    if (argc < 2)
    {
        exit(0);
    }

    // Iterate through each file
    for (int i = 1; i < argc; i++)
    {
        // Open the file
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            printf("my-cat: cannot open file\n");
            exit(1);
        }

        // Read and print the contents line by line
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            printf("%s", buffer);
        }

        // Close the file
        fclose(file);
    }

    return 0;
}

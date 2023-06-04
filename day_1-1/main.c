#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 8


int main(int argc, char **argv)
{
    FILE *file;
    char *filename = argv[1];
    char line[MAX_LINE_LENGTH];

    int total_calories;
    int highest_calories;

    if (argc == 1)
    {
        printf("Missing path to the inventory file...\n");
        return EXIT_SUCCESS;
    }

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open '%s'\n", filename);
        return EXIT_FAILURE;
    }

    total_calories = 0;
    while(fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        if (strcmp(line, "\n") == 0)
        {
            if (total_calories > highest_calories)
                highest_calories = total_calories;

            total_calories = 0;
            continue;
        }

        total_calories += atoi(line);
    }

    fclose(file);

    printf("Highest Calories: %d\n", highest_calories);

    return EXIT_SUCCESS;
}

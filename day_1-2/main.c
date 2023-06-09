#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 8
#define HIGHEST_CALORIES_LEN 3


void count_calories(FILE *inventory, int *calories_list);
void add_to_highest_calories(int calories_to_add, int *calories_list);
void display_result(int *arr);

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Missing path to the inventory file...\n");
        return EXIT_SUCCESS;
    }

    FILE *file;
    char *filename = argv[1];

    int highest_calories[3] = {0, 0, 0};

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open '%s'\n", filename);
        return EXIT_FAILURE;
    }

    count_calories(file, highest_calories);

    fclose(file);

    display_result(highest_calories);

    return EXIT_SUCCESS;
}

void count_calories(FILE *inventory, int *calories_list)
{
    char line[MAX_LINE_LENGTH];
    int total_calories = 0;

    while(fgets(line, MAX_LINE_LENGTH, inventory) != NULL)
    {
        if (strcmp(line, "\n") == 0)
        {
            add_to_highest_calories(total_calories, calories_list);
            total_calories = 0;
            continue;
        }

        total_calories += atoi(line);
    }

}

void add_to_highest_calories(int calories_to_add, int *calories_list)
{
    int i, j;
    for (i = 0; i < HIGHEST_CALORIES_LEN; i++)
    {
        if (calories_to_add > calories_list[i])
        {
            // loop through the array backwards and shift elements to the right
            for(j = HIGHEST_CALORIES_LEN-1; j > i; j--)
            {
                if (calories_list[j-1] != 0)
                    calories_list[j] = calories_list[j-1];
            }

            calories_list[i] = calories_to_add;
            break;
        }
    }
}

void display_result(int *calories_list)
{
    int i;
    int total = 0;

    printf("Highest Calories:\n");
    for (i = 0; i < 3; i++)
    {
        total += calories_list[i];
        printf("  %d. %d Calories\n", i+1, calories_list[i]);
    }

    printf("Total: %d Calories\n", total);
}

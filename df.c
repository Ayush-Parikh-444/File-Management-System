#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILES 100

// Define a struct to represent a file item
struct FileItem 
{
    char name[100];
    char date[20];
    int size;
    char file_type[10];
};

// Comparison function for qsort to sort by file name
int compareFileItemsByName(const void *a, const void *b) 
{
    struct FileItem *fileA = (struct FileItem *)a;
    struct FileItem *fileB = (struct FileItem *)b;
    return strcmp(fileA->name, fileB->name);
}

// Comparison function for qsort to sort by file date
int compareFileItemsByDate(const void *a, const void *b) 
{
    struct FileItem *fileA = (struct FileItem *)a;
    struct FileItem *fileB = (struct FileItem *)b;
    return strcmp(fileA->date, fileB->date);
}

void displayFiles(struct FileItem files[], int count) 
{
    if (count == 0) 
    {
        printf("No files in the list.\n");
    } else 
    {
        printf("%-20s %-15s %-10s %-10s\n", "Name", "Date", "Size", "Type");
        for (int i = 0; i < count; i++) 
        {
            printf("%-20s %-15s %-10d %-10s\n", files[i].name, files[i].date, files[i].size, files[i].file_type);
        }
    }
}

bool isValidDateFormat(const char *date) 
{
    // Validate if the date has the format "YYYY-MM-DD"
    if (strlen(date) != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++) 
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] < '0' || date[i] > '9')
            return false;
    }

    return true;
}

int main() 
{
    struct FileItem files[MAX_FILES];
    int count = 0;

    while (1) 
    {
        printf("\nOptions:\n");
        printf("1. Add File\n");
        printf("2. List Files\n");
        printf("3. Sort by Name\n");
        printf("4. Sort by Date (YYYY-MM-DD)\n");
        printf("5. Quit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                if (count < MAX_FILES) 
                {
                    printf("Enter file name: ");
                    scanf("%s", files[count].name);

                    // Prompt for the date until a valid format is provided
                    do 
                    {
                        printf("Enter file date (YYYY-MM-DD): ");
                        scanf("%s", files[count].date);
                    } while (!isValidDateFormat(files[count].date));

                    printf("Enter file size: ");
                    scanf("%d", &files[count].size);
                    printf("Enter file type: ");
                    scanf("%s", files[count].file_type);
                    count++;
                } 
                else 
                {
                    printf("Maximum file limit reached.\n");
                }
                break;
            case 2:
                displayFiles(files, count);
                break;
            case 3:
                qsort(files, count, sizeof(struct FileItem), compareFileItemsByName);
                break;
            case 4:
                qsort(files, count, sizeof(struct FileItem), compareFileItemsByDate);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
 
    return 0;
}
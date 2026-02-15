#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

// Function to compare two strings for binary search
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Function to perform binary search
int binary_search(char **names, int size, const char *target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(names[mid], target);
        
        if (cmp == 0) {
            return mid; // Name found, return index
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Name not found
}

int main() {
    FILE *file = fopen("names.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    // Count how many names are in the file
    int count = 0;
    char buffer[MAX_NAME_LENGTH];
    while (fgets(buffer, MAX_NAME_LENGTH, file) != NULL) {
        count++;
    }

    // Go back to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Dynamically allocate memory for the names
    char **names = (char **)malloc(count * sizeof(char *));
    if (names == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    // Read names from the file and store them in the dynamically allocated array
    for (int i = 0; i < count; i++) {
        names[i] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
        if (names[i] == NULL) {
            printf("Error: Memory allocation failed.\n");
            fclose(file);
            return 1;
        }
        fgets(names[i], MAX_NAME_LENGTH, file);
        // Remove newline character if present
        names[i][strcspn(names[i], "\n")] = '\0';
    }

    fclose(file);

    // Sort the list of names using binary search-friendly sorting
    qsort(names, count, sizeof(char *), compare);

    // Ask the user for a name to search for
    char target[MAX_NAME_LENGTH];
    printf("Enter the name to search: ");
    fgets(target, MAX_NAME_LENGTH, stdin);
    target[strcspn(target, "\n")] = '\0'; // Remove the newline character

    // Perform binary search
    int index = binary_search(names, count, target);

    if (index != -1) {
        printf("Name '%s' found at index %d.\n", target, index);
    } else {
        printf("Name '%s' not found in the list.\n", target);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < count; i++) {
        free(names[i]);
    }
    free(names);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

// Function to perform Binary Search
int binarySearch(char **names, int count, char *target) {
    int low = 0;
    int high = count - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int res = strcmp(names[mid], target);

        if (res == 0)
            return mid; // Found
        if (res < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // Not found
}

int main() {
    FILE *file = fopen("names.txt", "r");
    if (!file) {
        printf("Error: Could not open names.txt\n");
        return 1;
    }

    char **names = NULL;
    char buffer[MAX_NAME_LEN];
    int count = 0;

    // 1. Dynamically load names from file into memory
    while (fgets(buffer, MAX_NAME_LEN, file)) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = 0;

        names = realloc(names, sizeof(char *) * (count + 1));
        names[count] = malloc(strlen(buffer) + 1);
        strcpy(names[count], buffer);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("The file is empty.\n");
        return 0;
    }

    // Note: Data must be sorted for Binary Search. 
    // In a real scenario, you'd use qsort() here if the file isn't pre-sorted.

    // 2. User Input
    char searchName[MAX_NAME_LEN];
    printf("Enter the name to search for: ");
    scanf("%99s", searchName);

    // 3. Search logic
    int index = binarySearch(names, count, searchName);

    if (index != -1) {
        printf("Match found! '%s' is at index %d.\n", names[index], index);
    } else {
        printf("Name not found in the list.\n");
    }

    // 4. Cleanup memory
    for (int i = 0; i < count; i++) {
        free(names[i]);
    }
    free(names);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

// Binary search for a string inside a sorted array of strings
int binary_search(char **names, int size, const char *target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(names[mid], target);

        if (cmp == 0)
            return mid;  // Found
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Not found
}

int main() {
    FILE *fp = fopen("names.txt", "r");
    if (!fp) {
        printf("Error: Could not open names.txt\n");
        return 1;
    }

    int count;
    fscanf(fp, "%d", &count);  // First line: number of names

    // Allocate array of char* pointers
    char **names = malloc(count * sizeof(char *));
    if (!names) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Read names from file
    for (int i = 0; i < count; i++) {
        names[i] = malloc(MAX_NAME_LEN);
        fscanf(fp, "%s", names[i]);
    }
    fclose(fp);

    // Ask user for a name to search
    char target[MAX_NAME_LEN];
    printf("Enter a name to search: ");
    scanf("%s", target);

    // Perform binary search
    int index = binary_search(names, count, target);

    if (index >= 0)
        printf("Name '%s' found at index %d\n", target, index);
    else
        printf("Name '%s' not found\n", target);

    // Free memory
    for (int i = 0; i < count; i++)
        free(names[i]);
    free(names);

    return 0;
}

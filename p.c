#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open the input file
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }
    
    // Open a temporary file for writing
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(inputFile);
        return 1;
    }
    
    // Skip the first line in the input file
    long int res = ftell(tempFile);
    fseek(inputFile, 0L, SEEK_END);
    printf("Before.  %ld\n",res);
    int lineNumber = 1;
    char line[1000];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        if (lineNumber > 1) {
            fputs(line, tempFile);
        }
        lineNumber++;
    }
    
    // Close the input and temporary files
    fclose(inputFile);
    fclose(tempFile);
    
    // Remove the input file
    if (remove("input.txt") != 0) {
        printf("Error removing input file.\n");
        return 1;
    }
    
    // Rename the temporary file to the input file
    if (rename("temp.txt", "input.txt") != 0) {
        printf("Error renaming temporary file.\n");
        return 1;
    }
    tempFile = fopen("temp.txt", "r");
    fseek(inputFile, 0L, SEEK_END);
  
    // calculating the size of the file
    res = ftell(tempFile); 
    printf("Line removed successfully.  %ld\n",res);
    
    return 0;
}


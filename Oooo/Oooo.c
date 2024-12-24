#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main() {
    FILE* inputFile = fopen("lab4-test-file.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL) {
        perror("Error opening input.txt");
        return 1;
    }

    if (outputFile == NULL) {
        perror("Error opening output.txt");
        fclose(inputFile);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    char lineBuffer[BUFFER_SIZE * 2] = "";
    int countO = 0, counto = 0, lineNumber = 1;

    while (!feof(inputFile)) {
        size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile);

        for (size_t i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                fprintf(outputFile, "Line %d: O: %d, o: %d\n", lineNumber, countO, counto);

                countO = 0;
                counto = 0;
                lineNumber++;
            }
            else {
                if (buffer[i] == 'O') countO++;
                else if (buffer[i] == 'o') counto++;
            }
        }
    }

    if (countO || counto)
        fprintf(outputFile, "Line %d: O: %d, o: %d\n", lineNumber, countO, counto);

    fclose(inputFile);
    fclose(outputFile);

    outputFile = fopen("output.txt", "r");
    if (outputFile == NULL) {
        perror("Error reopening output.txt");
        return 1;
    }

    printf("Contents of output.txt:\n");
    while (fgets(buffer, BUFFER_SIZE, outputFile) != NULL) {
        printf("%s", buffer);
    }

    fclose(outputFile);

    return 0;
}

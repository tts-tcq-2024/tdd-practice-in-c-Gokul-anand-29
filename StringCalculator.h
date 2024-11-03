#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int stringToInteger(const char* str) {
    return atoi(str);
}

static int isValidNumber(int number) {
    return (number <= 1000) ? number : 0;
}

static void accumulateNegatives(int number, char* negatives) {
    if (number < 0) {
        snprintf(negatives + strlen(negatives), 256 - strlen(negatives), "%d ", number);
    }
}

static int sumNumbers(const char* input, const char* delimiters, char* negatives) {
    int sum = 0;
    char* inputCopy = strdup(input);  
    char* token = strtok(inputCopy, delimiters);
    while (token != NULL) {
        int number = stringToInteger(token); 
        accumulateNegatives(number, negatives); 
        sum += isValidNumber(number); 
        token = strtok(NULL, delimiters); 
    }
    free(inputCopy);
    
    if (strlen(negatives) > 0) {
        negatives[strlen(negatives) - 1] = '\0';
        exit(EXIT_FAILURE); 
    }
    return sum;
}

static const char* extractCustomDelimiter(const char* input, char* delimiters) {
    if (input[0] == '/' && input[1] == '/') {
        // Custom delimiter found, get the delimiter character after "//" and before "\n"
        delimiters[0] = input[2];  
        delimiters[1] = '\n';     
        delimiters[2] = '\0';    
        return strchr(input, '\n') + 1; 
    }
    strcpy(delimiters, ",\n");
    return input; 
}

static int add(const char* input) {
    if (input == NULL || *input == '\0') {
        return 0;
    }
    char delimiters[3];  
    char negatives[256] = {0};  
    const char* numbersPart = extractCustomDelimiter(input, delimiters);
    return sumNumbers(numbersPart, delimiters, negatives);
}

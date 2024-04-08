#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    SEMI,
    OPEN_PAREN,
    CLOSE_PAREN,
} TypeSeparator;

typedef enum {
    INT,
    FLOAT,
    CHAR,
    STRING,
} TypeLiteral;

typedef enum {
    EXIT,
} TypeKeyword;

typedef struct {
    TypeKeyword type;
} TokenKeyword;

typedef struct {
    TypeLiteral type;
    char *value;
} TokenLiteral;

typedef struct {
    TypeSeparator type;
} TokenSeparator;

TokenLiteral * generate_number(FILE *file, char current) {
    TokenLiteral * token = malloc(sizeof(TokenLiteral));
    token->type = INT;
    char *value = malloc(sizeof(char) * 8);
    int value_index = 0;
    while (isdigit(current) && current != EOF) {
        
        value[value_index++] = current;
        // printf("Value: %s\n", value);
        current = fgetc(file);
    }
    value[value_index] = '\0';
    token->value = value;
    // free(token->value);
    return (token);
}

TokenKeyword * generate_keyword(FILE *file, char current) {
    TokenKeyword * token = malloc(sizeof(TokenKeyword));
    char * keyword = malloc(sizeof(char) * 8);
    int keyword_index = 0;
    while (isalpha(current) && current != EOF) {
        keyword[keyword_index++] = current;
    }
    return (token);
}

void lexer(FILE *file) {
    char current = fgetc(file);
    while (current != EOF) {
        if (current == ';')
        {
            printf("SEMI\n");
        }
        else if (current == '(')
        {
            printf("OPEN_PAREN\n");
        }
        else if (current == ')')
        {
            printf("CLOSE_PAREN\n");
        } else if(isalpha(current)){
            printf("ALPHA %c\n", current);
        } else if(isdigit(current)){
            TokenLiteral *test_token = generate_number(file, current);
            printf("Test Token: %s\n", test_token->value);
        }
        
        current = fgetc(file);
    }
}

int main() {
    FILE *file;
    file = fopen("test.unn", "r");

    // printf("%c", current);
    lexer(file);
}
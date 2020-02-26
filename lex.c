#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// max amount of tokens
#define TOKEN_MAX 5000

// token struct
typedef struct token
{
    char content[12]; // token name
    int type;   // identifies the type
} token;

// max 41 chars
// returns the correct error message depending on int passed
void error(int type)
{
    char msg[41];
    switch(type)
    {
        case 0:
            strcpy(msg, "Variable does not start with letter");  
            break;
        case 1:
            strcpy(msg, "Number is too long");
            break;
        case 2:
            strcpy(msg, "Name is too long");
            break;
        case 3:
            strcpy(msg, "Invalid syntax");
            break;
        default:
            strcpy(msg, "Unknown error");
    }

    fprintf(stderr, "%s", msg);
    exit(1);
}


// compares string to identify if token type is a reserved word, returns 1 if true
int check_reserved(token *tokenArray, int index)
{   
    int i;
    int flag = 0;

    // array of reserved words
    char *reserved[14] = 
    {
        "const", 
        "var", 
        "procedure", 
        "call", 
        "begin", 
        "end", 
        "if", 
        "then", 
        "else", 
        "while", 
        "do", 
        "read",
        "write", 
        "odd"
    };

    // checks which reserved word was used, if any. assigns type
    for (i = 0; i < 14; i++)
    {
        if (!strcmp(tokenArray[index].content, reserved[i]))
            {
                flag = 1;
                switch (i)
                {
                    case 0:
                        tokenArray[index].type = 28;
                        break;
                    
                    case 1:
                        tokenArray[index].type = 29;
                        break; 
                    
                    case 2:
                        tokenArray[index].type = 30;
                        break;

                    case 3:
                        tokenArray[index].type = 27;
                        break; 

                    case 4:
                        tokenArray[index].type = 21;
                        break;

                    case 5:
                        tokenArray[index].type = 22;
                        break;
                    
                    case 6:
                        tokenArray[index].type = 23;
                        break;
                    
                    case 7:
                        tokenArray[index].type = 24;
                        break;
                    
                    case 8:
                        tokenArray[index].type = 33;
                        break;
                    
                    case 9:
                        tokenArray[index].type = 25;
                        break;
                    
                    case 10:
                        tokenArray[index].type = 26;
                        break;

                    case 11:
                        tokenArray[index].type = 32;
                        break;
                    
                    case 12:
                        tokenArray[index].type = 31;
                        break;
                    
                    case 13:
                        tokenArray[index].type = 8;
                        break;
                }
            }  
    }

    return flag;
}


char alpha_token(token *tokenArray, char c, FILE *ifp, int *index)
{
    int i;
    int flag = 0;
    int last;
    tokenArray[*index].content[0] = c;
    
    // fills token content while checking for errors
    for(i = 1; i < 12; i ++)
    {
        c = fgetc(ifp);
        if (isspace(c) || (c == EOF) || (!isdigit(c) && !isalpha(c)))
        {
            ungetc(c, ifp); // decrements file pointer to previous position
            last = i;
            break;
        }

        tokenArray[*index].content[i] = c;
        last = i;
    }

    // makes sure the last char is '\0'
    tokenArray[*index].content[last] = '\0';

    c = fgetc(ifp);
    // checks if current char is alpha || number for long variable name error
    if (isalpha(c) || isdigit(c))
        error(2);
    
    flag = check_reserved(tokenArray, *index);
    
    // if it is not a reserved word
    if (!flag)
        tokenArray[*index].type = 2;

    // increments index before next funtion call
    *index = *index + 1;

    return c;
}

char comment(FILE *ifp, char c)
{
    c = fgetc(ifp);
    while(c != EOF)
    {
        if (c == '*')
        {
            c = fgetc(ifp);
            if (c == '/' || c == EOF)
                return c;
            else 
                ungetc(c, ifp);
        }

        c = fgetc(ifp);
    }

    return c;
}

char sym_token(token *tokenArray, char c, FILE *ifp, int *index)
{   
    int comment_flag = 0;
    switch(c)
    {
        case '+':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 4;
           break;
        
        case '-':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 5;
           break;
        
        case '*':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 6;
           break;
        
        case '/':
           if((c = fgetc(ifp)) == '*') // case with comments
           {
               c = comment(ifp, c);
               printf("%c",c);
               comment_flag = 1;
           }
           else
           {
           ungetc(c, ifp);     
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 7;
           }
           break;
        
        case '(':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 15;
           break;
        
        case ')':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 16;
           break;
        
        case '=':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 9;
           break;
        
        case ',':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 17;
           break;
        
        case '.':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 19;
           break;

        case '<':
           tokenArray[*index].content[0] = c;
           if ((c = fgetc(ifp)) == '=')
            {
                tokenArray[*index].content[1] = c;
                tokenArray[*index].content[2] = '\0'; 
                tokenArray[*index].type = 12;
            }
            else
            {
                ungetc(c, ifp);
                tokenArray[*index].content[1] = '\0'; 
                tokenArray[*index].type = 11;
            }
            break;
        
        case '>':
           tokenArray[*index].content[0] = c;
           if ((c = fgetc(ifp)) == '=')
            {
                tokenArray[*index].content[1] = c;
                tokenArray[*index].content[2] = '\0'; 
                tokenArray[*index].type = 14;
            }
            else
            {
                ungetc(c, ifp);
                tokenArray[*index].content[1] = '\0'; 
                tokenArray[*index].type = 13;
            }
            break;
        
        case ';':
           tokenArray[*index].content[0] = c;
           tokenArray[*index].content[1] = '\0'; 
           tokenArray[*index].type = 18;
           break;
        
        case ':':
           tokenArray[*index].content[0] = c;
           if ((c = fgetc(ifp)) == '=')
            {
                tokenArray[*index].content[1] = c;
                tokenArray[*index].content[2] = '\0'; 
                tokenArray[*index].type = 20;
            }
            else
            {
                ungetc(c, ifp);
                tokenArray[*index].content[1] = '\0'; 
                error(3);
            }
            break;
    }

    // gets new c to return
    c = fgetc(ifp);

    // increments index
    if (comment_flag == 0)
        *index = *index + 1;
        
    return c;
}

char num_token(token *tokenArray, char c, FILE *ifp, int *index)
{
    int i;
    int last;
    tokenArray[*index].content[0] = c;
    
    // fills token content while checking for errors
    for(i = 1; i < 5; i ++)
    {
        c = fgetc(ifp);
        if (isspace(c) || (c == EOF) || (!isdigit(c)))
        {
            ungetc(c, ifp); // decrements file pointer to previous position
            last = i;
            break;
        }

        tokenArray[*index].content[i] = c;
        last = i;
    }

    // makes sure the last char is '\0'
    tokenArray[*index].content[last] = '\0';

    c = fgetc(ifp);
    // checks if current char is alpha || number for long variable name error
    if (isdigit(c))
        error(2);  
    if (isalpha(c))
        error(3);  

    tokenArray[*index].type = 3;

    // increments index
    *index = *index + 1;
    return c; 
}

// prints from input file
void print_source(FILE *ifp, FILE *ofp)
{
    char c;
    rewind(ifp); // so file pointer can point to start of file
    
    c = fgetc(ifp);
    while(c != EOF)
    {
        fprintf(ofp, "%c", c);
        c = fgetc(ifp);
    }
    
}

// formats and prints tokens from tokenArray to output file
void print_table(token *tokenArray, FILE *ofp, int index)
{
    int i;

    fprintf(ofp, "\n\nLexeme Table:\n");
    fprintf(ofp, "%s\t\t%s\n", "lexeme", "token type");
    // index still stores the last number index used
    for (i = 0; i < index; i++)
    {
        fprintf(ofp, "%s\t\t%d\n", tokenArray[i].content, tokenArray[i].type);
    }

}

// formats and prints tokens from tokenArray to output file
void print_list(token *tokenArray, FILE *ofp, int index)
{
    int i;

    fprintf(ofp, "\n\nLexeme List:\n"); 
    for (i = 0; i < index; i++) 
    {
        fprintf(ofp, "%d ", tokenArray[i].type);
        if (tokenArray[i].type == 2 || tokenArray[i].type == 3) // if num or var state which
            fprintf(ofp, "%s ", tokenArray[i].content);
        
        if (((i + 1) % 80) == 0) // controls lenght of output
            fprintf(ofp, "\n");
    }
}


int main(void)
{
    int i;
    FILE *ifp, *ofp;
    char input_file_name[21];
    char output_file_name[21];
    int comment_stat = 0; // states if inside a comment
    char c; // char to be used to read input
    char temp; // either at c or one char ahead
    char *buffer = calloc(1, sizeof(char) * 12);

    // array of tokens
    token *tokenArray = malloc(sizeof(token) * TOKEN_MAX);
    int index = 0;

    // change these values depending on file names
    strcpy(input_file_name, "input.txt");
    strcpy(output_file_name, "output.txt");

    // attempts to open input-file to read from and output-file to write to
    if ((ifp = fopen(input_file_name,"r")) == NULL)
    {
        fprintf(stderr, "Could not open %s in \"read_input\".\n",input_file_name);
        exit(0);
    }
    if ((ofp = fopen(output_file_name,"w")) == NULL)
    {
        fprintf(stderr, "Could not open %s in \"Main\".\n",output_file_name);
        exit(0);
    }

    // loop to get chars from input and to decide the prosedure
    c = fgetc(ifp);
    while (c != EOF)
    {
        // continues loop is c is space
        if (isspace(c))
        {
            c = fgetc(ifp);
            continue;
        }

        // case that c is a number
        else if (isdigit(c))
        {
            c = num_token(tokenArray, c, ifp, &index);
        }
        
        // case that c is a letter
        else if (isalpha(c))
        {
            c = alpha_token(tokenArray, c, ifp, &index);
        }
        
        // case that c is a symbol
        else 
        {
            c = sym_token(tokenArray, c, ifp, &index);
        }
        // for debugging
        //fprintf(ofp, "%s | %d\n index = %d\n\n", tokenArray[index - 1].content, tokenArray[index - 1].type, index);
    }

    print_source(ifp, ofp);
    print_table(tokenArray, ofp, index);
    print_list(tokenArray, ofp, index);

}
// Diego Rodrigues
// P-Machine - 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constant values 
#define MAX_STACK_HEIGHT 40
#define MAX_CODE_LENGTH  200
#define MAX_LEXI_LEVELS  3
#define REGISTERS_AMOUNT 8

// Instructions struct
typedef struct instruction
{
    int op; 
    int r;  
    int l;  
    int m;
}instruction;

// Reads input.txt file and stores in code struct array
// returns the number of lines read
int read_input(instruction *code, char *file_name)
{
    int lines;
    int flag = 1;
    FILE* ifp = NULL;

    // attempts to open file, exit if unable
    if ((ifp = fopen(file_name,"r")) == NULL)
    {
        fprintf(stderr, "Could not open %s in \"read_input\".\n",file_name);
        exit(0);
    }

    // loops through file and stores instructions in correct index
    for (lines = 0; feof(ifp) == 0; lines++)
    {
        fscanf(ifp, "%d", &code[lines].op);
        fscanf(ifp, "%d", &code[lines].r);
        fscanf(ifp, "%d", &code[lines].l);
        fscanf(ifp, "%d", &code[lines].m);
    }

    fclose(ifp);
    ifp = NULL;

    return lines;
}

// prints code in PL-0 to an output file
void print_code(instruction *code, int lines, char *file_name)
{
    int i;
    FILE *ifp = NULL;

    // attempts to open file, creates one if DNE, exit if fails
    if ((ifp = fopen(file_name,"w")) == NULL)
    {
        fprintf(stderr, "Could not open %s in \"print_code\".\n",file_name);
        exit(0);
    }

    // converts code[] to assembly based on op
    fprintf(ifp,"%s\t%s\t%s\t%s\t%s\n", "Line", "OP", "R","L","M");
    for (i = 0; i < lines; i++)
    {
        switch(code[i].op)
        {
            case 1:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "LIT", code[i].r, code[i].l, code[i].m);
                break;
            case 2:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "RTN", code[i].r, code[i].l, code[i].m);
                break;
            case 3:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "LOD", code[i].r, code[i].l, code[i].m);
                break;
            case 4:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "STO", code[i].r, code[i].l, code[i].m);
                break;
            case 5:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "CAL", code[i].r, code[i].l, code[i].m);
                break;
            case 6:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "INC", code[i].r, code[i].l, code[i].m);
                break;
            case 7:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "JMP", code[i].r, code[i].l, code[i].m);
                break;
            case 8:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "JPC", code[i].r, code[i].l, code[i].m);
                break;
            case 9:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "SIO", code[i].r, code[i].l, code[i].m);
                break;
            case 10:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "SIO", code[i].r, code[i].l, code[i].m);
                break;
            case 11:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "SIO", code[i].r, code[i].l, code[i].m);
                break;
            case 12:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "NEG", code[i].r, code[i].l, code[i].m);
                break;
            case 13:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "ADD", code[i].r, code[i].l, code[i].m);
                break;
            case 14:
                fprintf(ifp,"%d\t%s\t%d\t%d\t%d\n", i, "SUB", code[i].r, code[i].l, code[i].m);
                break;
            case 15:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "MUL", code[i].r, code[i].l, code[i].m);
                break;
            case 16:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "DIV", code[i].r, code[i].l, code[i].m);
                break;
            case 17:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "ODD", code[i].r, code[i].l, code[i].m);
                break;
            case 18:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "MOD", code[i].r, code[i].l, code[i].m);
                break;
            case 19:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "EQL", code[i].r, code[i].l, code[i].m);
                break;
            case 20:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "NEQ", code[i].r, code[i].l, code[i].m);
                break;
            case 21:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "LSS", code[i].r, code[i].l, code[i].m);
                break;
            case 22:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "LEQ", code[i].r, code[i].l, code[i].m);
                break;
            case 23:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "GTR", code[i].r, code[i].l, code[i].m);
                break;
            case 24:
                fprintf(ifp,"%d\t\t%s\t%d\t%d\t%d\n", i, "GEQ", code[i].r, code[i].l, code[i].m);
                break;
        }
    }

    // flusing out buffer to prevent weird behavior
    fflush(ifp);
    fclose(ifp);
    ifp = NULL;
}

// finds variable in a different activation record L levels down
int base(int l, int bp, int *stack)
{
    int b1;
    b1 = bp;

    while(l > 0)
    {
        b1 = stack[b1 + 1];
        l--;
    }

    return b1;
}


// fetches instructions from code and places in instruction register
// program counter is incremented to fetch next instructions
// returns PC before incrementation
int fetch(int *pc, instruction *code, instruction *ir)
{
   int prev_PC;
   ir->op = code[*pc].op;
   ir->r = code[*pc].r;
   ir->l = code[*pc].l;
   ir->m = code[*pc].m;

   prev_PC = *pc;
   *pc = *pc + 1;

   return prev_PC;
}

// prints data (used for after execution)
// Array of "|" here, delete for better peformance
void print(int *stack, FILE *ifp, int *R, int *SP, int *PC, int *BP, instruction *ir, char *op, int prev_PC, int *brakets)
{
    int i;
    fprintf(ifp, "\t\t\t\t%s\t%s\t%s\t%s\n","pc","bp","sp","registers");
    fprintf(ifp,"%d %s %d %d %d \t\t\t", prev_PC, op, ir->r, ir->l, ir->m);
    fprintf(ifp, "%d\t%d\t%d\t", *PC, *BP, *SP);
    for (i = 0; i < REGISTERS_AMOUNT; i++)
        fprintf(ifp, "%d%c",R[i], (i == (REGISTERS_AMOUNT - 1)? '\n' : ' '));
    
    // prints stack
    fprintf(ifp, "Stack: ");
    for (i = 1; i <= *SP; i++)
    {
        fprintf(ifp, "%d%c", stack[i], (i == *SP)? '\n' : ' ');
        if (brakets[i] == 1 && (i != *SP))
            fprintf(ifp, "| ");
    }       
    
    // adding \n for file readability
    fprintf(ifp, "\n");
}

// i == r, j == l, k == m
void execute(instruction *ir, int *R, int *SP, int *PC, int *BP, int *stack, int *halt, int prev_PC, FILE *ifp, int *brakets)
{
    switch(ir->op)
    {
        // LIT
        case 1:
            R[ir->r] = ir->m;
            print(stack, ifp, R, SP, PC, BP, ir, "LIT", prev_PC, brakets);
            break;
        
        // RTN
        case 2:
            brakets[*BP - 1] = 0;
            *SP = *BP - 1;
            *BP = stack[*SP + 3];
            *PC = stack[*SP + 4];
            print(stack, ifp, R, SP, PC, BP, ir, "RTN", prev_PC, brakets);
            break;
        
        // LOD 
        case 3:
            R[ir->r] = stack[base(ir->l, *BP, stack) + ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "LOD", prev_PC, brakets);
            break;
        
        // STO
        case 4:
            stack[base(ir->l, *BP, stack) + ir->m] = R[ir->r];
            print(stack, ifp, R, SP, PC, BP, ir, "STO", prev_PC, brakets);
            break;
        
        // CAL
        case 5:
            stack[*SP + 1] = 0;
            stack[*SP + 2] = base(ir->l, *BP, stack);
            stack[*SP + 3] = *BP;
            stack[*SP + 4] = *PC;
            *BP = *SP + 1;
            *PC = ir->m;
            brakets[*SP] = 1;
            print(stack, ifp, R, SP, PC, BP, ir, "CAL", prev_PC, brakets);
            break;
        
        // INC
        case 6:
            *SP = *SP + ir->m;
            print(stack, ifp, R, SP, PC, BP, ir, "INC", prev_PC, brakets);
            break;
        
        // JMP
        case 7:
            *PC = ir->m;
            print(stack, ifp, R, SP, PC, BP, ir, "JMP", prev_PC, brakets);
            break;

        // JPC
        case 8:
            if (R[ir->r] == 0)
                *PC = ir->m;
            print(stack, ifp, R, SP, PC, BP, ir, "JPC", prev_PC, brakets);
            break;
        
        // SIO
        case 9:
            printf("%d\n", R[ir->r]);
            print(stack, ifp, R, SP, PC, BP, ir, "SIO", prev_PC, brakets);
            break;
        
        // SIO
        case 10:
            printf("Insert integer: ");
            scanf("%d\n", &R[ir->r]);
            print(stack, ifp, R, SP, PC, BP, ir, "SIO", prev_PC, brakets);
            break;
        
        // SIO
        case 11:
            *halt = 1;
            print(stack, ifp, R, SP, PC, BP, ir, "SIO", prev_PC, brakets);
            break;

        // NEG
        case 12:
            R[ir->r] = -R[ir->r];
            print(stack, ifp, R, SP, PC, BP, ir, "NEG", prev_PC, brakets);
            break;
        
        // ADD
        case 13:
            R[ir->r] = R[ir->l] + R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "ADD", prev_PC, brakets);
            break;
        
        // SUB
        case 14:
            R[ir->r] = R[ir->l] - R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "SUB", prev_PC, brakets);
            break;
        
        // MUL
        case 15:
            R[ir->r] = R[ir->l] * R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "MUL", prev_PC, brakets);
            break;
        
        // DIV
        case 16:
            R[ir->r] = R[ir->l] / R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "DIV", prev_PC, brakets);
            break;

        // ODD
        case 17:
            R[ir->r] = R[ir->r] % 2;
            print(stack, ifp, R, SP, PC, BP, ir, "ODD", prev_PC, brakets);
            break;
        
        // MOD
        case 18:
            R[ir->r] = R[ir->l] % R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "MOD", prev_PC, brakets);
            break;

        // EQL
        case 19:
            R[ir->r] = R[ir->l] == R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "EQL", prev_PC, brakets);
            break;

        // NEQ
        case 20:
            R[ir->r] = R[ir->l] != R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "NEQ", prev_PC, brakets);
            break;

        // LSS
        case 21:
            R[ir->r] = R[ir->l] < R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "LSS", prev_PC, brakets);
            break;
        
        // LEQ
        case 22:
            R[ir->r] = R[ir->l] <= R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "LEQ", prev_PC, brakets);
            break;
        
        // GTR
        case 23:
            R[ir->r] = R[ir->l] > R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "GRT", prev_PC, brakets);
            break;
        
        // GEQ
        case 24:
            R[ir->r] = R[ir->l] >= R[ir->m];
            print(stack, ifp, R, SP, PC, BP, ir, "GEQ", prev_PC, brakets);
            break;
    }
}

// prints to file the full stack
void print_stack(int *stack, FILE *ifp)
{
    int i;
    for (i = 1; i < MAX_STACK_HEIGHT; i++)
        fprintf(ifp, "%d ", stack[i]);
    
    fprintf(ifp,"\n");
}

// prints to file the initial values of the variables before fetching 
void print_init(int *stack, FILE *ifp, int *R, int *SP, int *PC, int *BP)
{
    int i;
    fprintf(ifp, "\t\t\t\t%s\t%s\t%s\t%s\n","pc","bp","sp","registers");
    fprintf(ifp, "Initial Values:\t\t\t%d\t%d\t%d\t", *PC, *BP, *SP);
    
    for(i = 0; i < REGISTERS_AMOUNT; i++)
        fprintf(ifp, "%d ", R[i]);
    fprintf(ifp, "\nStack: ");

    print_stack(stack, ifp);
    // adding \n for file readability
    fprintf(ifp, "\n");
}



int main(void)
{
    int i = 0;
    FILE *file;
    int lines;
    int prev_PC; 

    // Initial values for PM/0 CPU registers & halt
    int SP = 0, PC = 0, halt = 0, BP = 1;

    // registers 
    int *R = calloc(1, sizeof(int) * 8);

    // data to be used by PM/0
    int *stack = calloc(1, sizeof(int) * MAX_CODE_LENGTH);

    // this is for presentation only, a waste of memmory if not needed
    int *brackets = calloc(1, sizeof(int) * MAX_STACK_HEIGHT);

    // stores the input file instructions
    instruction *code = calloc(1, sizeof(int) * MAX_CODE_LENGTH);

    // struction register IR
    instruction IR;

    char input_file_name[21];
    strcpy(input_file_name, "input.txt");

    char output_file_name[21];
    strcpy(output_file_name, "output.txt");

    lines = read_input(code, input_file_name);
    print_code(code, lines, output_file_name);

    // attempts to open file to write
    if ((file = fopen(output_file_name,"a")) == NULL)
    {
        fprintf(stderr, "Could not open %s in \"Main\".\n",output_file_name);
        exit(0);
    }

    print_init(stack, file, R, &SP, &PC, &BP);
    while(halt == 0)
    {
        prev_PC = fetch(&PC, code, &IR);
        execute(&IR, R, &SP, &PC, &BP, stack, &halt, prev_PC, file, brackets);
        i++;
    }

    // closing files and freeing mem
    fclose(file);
    free(R);
    free(code);
    free(brackets);

    return 0;
}
/*******
 * Project 01: Binary calculator
 * COSC 208, Introduction to Computer Systems, Spring 2021
 *******/

#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 8
#define MAX_FORMULA_LEN (1 + MAX_DIGITS + 1 + 1 + MAX_DIGITS)

int valid = 1;
int invalid = 0;

//Storage of operands, operations, and modifiers.
char right[MAX_DIGITS + 1];
char left[MAX_DIGITS + 1];
char result[MAX_DIGITS + 1];

char operator = 'n';
char rightMod = 'n';
char leftMod = 'n';

//Stores the new modifier for each side of the equation in the correct variable.
int store(char *mod, char new, int index)
{
    if(*mod != 'n') 
    {
        printf ("\nInvalid Binary Formula: Too many modifiers in operand!\n");
        return 0;
    }
    else 
    {
        if(index == 0)
        {
            *mod = new;
        }
        else
        {
            printf ("\nInvalid Binary Formula: Poor operand modifier placement!\n");
            return 0;
        }
                    
    }
    return 1;
}

//Parses through a given formula, seperating the opperands, modifiers, and operators.
//Ensurses that the formula given is valid.
int parse(char formula[]) 
{
   int length = strlen(formula);
   int leftIndex = 0;
   int rightIndex = 0;

    // Ensures that the user's formula will not be too long
    if(length > MAX_FORMULA_LEN)
    {
        printf ("\nInvalid Binary Formula: Formula too long!\n"); 
        return invalid;
    }

    //Parses through the formula.
    //Stores relevent variables and checks for validity.
    for(int x = 0; x < length; x++)  //If see '-' check behind 1 to find operator.
    {
        //Makes sure that no invalid characters are contained in the formula.
        if(formula[x] == ' ' || (formula[x] != '0' && formula[x] != '1' && formula[x] != '|' && formula[x] != '&' && formula[x] != '+' && formula[x] != '~' && formula[x] != '-' && formula[x] != '^')) 
        {
            printf ("\nInvalid Binary Formula: Invalid character!\n"); 
            return invalid;
        }
        //Ensures that an operator is used within the formula.
        else if((operator != '|' && operator != '&' && operator != '+' && operator != '^') && x == length - 1) 
        { 
            printf ("\nInvalid Binary Formula: No operator present!\n");
            return invalid;
        }
        //Ensures that the formula does not contain two operators.
        else if(formula[x] == '|' || formula[x] == '&' || formula[x] == '+' || formula[x] == '^')
        {   
            if(operator != 'n' && x != 0 && rightMod != 'n') 
            { 
                printf ("\nInvalid Binary Formula: Too many operators!\n");
                return invalid;
            }
            else 
            {
                operator = formula[x];
            }
        }
        //Stores the left and right operands in seperate variables.
        //Makes sure that the operands don't contain too many characters.
        else if ((formula[x] == '0' || formula[x] == '1')) 
        {
            if(operator == 'n')
            { 
                if(leftIndex >= MAX_DIGITS) //Ensures that the left opperand is in range.
                {
                    printf("\nInvalid Binary Formula: The left operand is too large!\n");
                    return invalid;  
                }
                else
                {
                    left[leftIndex] = formula[x]; 
                    leftIndex++;
                }
            }
            else 
            {
                if(rightIndex >= MAX_DIGITS) //Ensures that the right opperand is in range.
                {
                    printf("\nInvalid Binary Formula: The right operand is too large!\n");
                    return invalid;  
                }
                else
                {
                    right[rightIndex] = formula[x];
                    rightIndex++; 
                }
            }
        }
        //Ensures that there isn't more than one modifier per operand.
        else if(formula[x] == '-' || formula[x] ==  '~') 
        {
            /*Stores the new modifers in their given position, 
            based on the side of the equation they are found on.*/
            if(operator == 'n') 
            {
                if (store(&leftMod, formula[x], leftIndex) == 0)
                {
                    return invalid;
                }
            }
            else
            {
                if(store(&rightMod, formula[x], rightIndex) == 0)
                {
                    return invalid;
                }
            }
        }
    }
    return valid;
}

//Adds zero's to the given operand until there are 8 digits.
void zeroExtend(char number[])
{
    int length = strlen(number) - 1;

    //Makes sure the operand isn't already larger than 8 digits
    if(strlen(number) > MAX_DIGITS)
    {
        printf("\nInvalid Binary Formula: Operand is too large!3\n");
        return;
    }

    //Add's zeros to the end of the given operand until there are 8 digits.
    for(int x = MAX_DIGITS - 1; x >= 0; x--)
    {
        if(length >= 0)
        {
            number[x] = number[length];
            length--;
        }
        else
        {
            number[x] = '0';
        }
    }
}

/*vvvvvvvvvvvvvvvvvvvvvvOPERATOR FUNCTIONSvvvvvvvvvvvvvvvvvvvvv*/
//Preforms addition between the two given operands.
void add(char leftOp[], char rightOp[])
{
    int carryOut = 0;

    for(int x = strlen(leftOp) - 1; x >= 0; x--)
    {
        if(leftOp[x] == '1' && rightOp[x] == '1' && carryOut == 1)
        {
            result[x] = '1';
            carryOut = 1;
        }
        else if((leftOp[x] == '1' && rightOp[x] == '1' && carryOut == 0) 
            || (leftOp[x] == '1' && rightOp[x] == '0' && carryOut == 1) 
            || (leftOp[x] == '0' && rightOp[x] == '1' && carryOut == 1))
        {
            result[x] = '0';
            carryOut = 1;
        }
        else if((leftOp[x] == '1' && rightOp[x] == '0' && carryOut == 0) 
            || (leftOp[x] == '0' && rightOp[x] == '1' && carryOut == 0) 
            || (leftOp[x] == '0' && rightOp[x] == '0' && carryOut == 1))
        {
            result[x] = '1';
            carryOut = 0;
        }
        else
        {
            result[x] = '0';
            carryOut = 0;
        }
    }
}

//Compares the two operands using the bitwise or function.
void bitWiseOr(char leftOp[], char rightOp[])
{
    for(int x = strlen(leftOp) - 1; x >= 0; x--)
        {
            if(rightOp[x] == '1' || leftOp[x] == '1')
            {
                result[x] = '1';
            }
            else
            {
                result[x] = '0';
            }
        }
}

//Compares the two operands using the bitwise and function.
void bitWiseAnd(char leftOp[], char rightOp[])
{
    for(int x = strlen(leftOp) - 1; x >= 0; x--)
    {
        if(rightOp[x] == '1' && leftOp[x] == '1')
        {
            result[x] = '1';
        }
        else
        {
            result[x] = '0';
        }
    }
}

//Compares the two operands using the bitwise xor function.
void bitWiseXor(char leftOp[], char rightOp[])
{
    for(int x = strlen(leftOp) - 1; x >= 0; x--)
    {
        if(rightOp[x] == '1' && leftOp[x] == '1')
        {
            result[x] = '0';
        }
        else if (rightOp[x] == '1' || leftOp[x] == '1')
        {
            result[x] = '1';
        }
        else
        {
            result[x] = '0';
        }
    }
}
/*^^^^^^^^^^^^^^^^^^^^^^OPERATOR FUNCTIONS^^^^^^^^^^^^^^^^^^^^^^^^^^*/


/*vvvvvvvvvvvvvvvvvvvvvvvMODIFIER FUNCTIONSvvvvvvvvvvvvvvvvvvvvvvv*/
//Flips the bits of the given operand.
void bitwiseNot(char operand[])
{
    for(int x = 0; x < strlen(operand); x++)
    {
        if(operand[x] == '0')
        {
            operand[x] = '1';
        }
        else
        {
            operand[x] = '0';
        }
    }
}

//Negates the given operand (flipping the bits adding one).
void negate(char operand[])
{
    int add = 1;
    
    //Flips the given operand's bits
    bitwiseNot(operand);

    //Adds 1 to complete the negation.
    for(int y = strlen(operand) - 1; y >= 0; y--)
    {
        if(add == 1 && operand[y] == '1' && y != 0)
        {
            operand[y] = '0';
            add = 1;
        }
        else if((add == 1 && operand[y] == '0') || (add == 0 && operand[y] == '1'))
        {
            operand[y] = '1';
            add = 0;
        }
        else
        {
            operand[y] = '0';
        }
    }
}
/*^^^^^^^^^^^^^^^^^^^MODIFIER FUNCTIONS^^^^^^^^^^^^^^^^^^^^*/

//Alters the given operand based on the given modifier.
void applyModifier(char number[], char mod)
{
    //Exits function if there is no modifer present
    if(mod == 'n')
    {
        return;
    }

    //Applys the negation modifier to the given operand.
    if(mod == '-')
    {
        negate(number);
    }

    //Applys the bitwise not modifier to the given operand.
    if(mod == '~')
    {
        bitwiseNot(number);
    }
}

//Calculates the result of the two operands based on the operator.
void applyOperator(operator)
{
    //Compares the two operands using the bitwise and function and calculates the result.
    if (operator == '&')
    {
        bitWiseAnd(left, right);
    }

    //Compares the two operands using the bitwise or function and calculates the result.
    if (operator == '|')
    {
        bitWiseOr(left, right);
    }

    //Compares the two operands using the bitwise xor function and calculates the result.
    if(operator == '^')
    {
        bitWiseXor(left, right);
    }

    //Adds the two operands together depending on the operator.
    if(operator == '+' || operator == '-')
    {
        if(operator == '-')
        {
            negate(right);
        }
        add(left, right);
    }
}

//Alerts the user whether or not there was over or underflow in the calculation.
void checkFlow(char leftOp[], char rightOp[])
{
    if(operator == '+')
    {
        if(leftOp[0] == '0' && rightOp[0] == '0' && result[0] == '1')
        {
            printf("Overflow! \n");
        }
        else if(leftOp[0] == '1' && rightOp[0] == '1' && result[0] == '0')
        {
            printf("Underflow! \n");
        }
    }
}

//Calculates the result of the two given operands.
void calculate()
{
    zeroExtend(right);
    zeroExtend(left);
        
    //Prints output only if formula is valid.
    if(leftMod == 'n' && rightMod == 'n')
    {
        printf("%s%c%s\n",left,operator,right);   
    }
    else if(rightMod == 'n')
    {
        printf("%c%s%c%s\n", leftMod,left,operator,right); 
    }
    else if(leftMod == 'n')
    {   
        printf("%s%c%c%s\n", left,operator,rightMod,right);   
    }
    else
    {
        printf("%c%s%c%c%s\n", leftMod,left,operator,rightMod,right); 
    }

    applyModifier(left, leftMod);
    applyModifier(right, rightMod);

    printf("%s%c%s\n",left,operator,right);

    applyOperator(operator);

    printf("%s\n", result);

    checkFlow(left, right);
}

int main(int argc, char *argv[]) 
{
    memset(right, '\0', sizeof(right));
    memset(left, '\0', sizeof(left));
    memset(result, '\0', sizeof(result));

    if (argc != 2) 
    {
        printf("\nProvide a single, valid binary formula (without spaces)\n");
        return 1;
    }

    char formula_str[MAX_FORMULA_LEN];
    strcpy(formula_str, argv[1]);
    
    //Makes sure that the opperands are only acted on if the formula is valid.
    if(parse(formula_str) == valid)
    {
        calculate();
    }
    else
    {
        printf("Calculation could not be made.\n\n");
    }
}
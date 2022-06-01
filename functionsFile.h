#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int variableCounter = 0; // counts the number of variables
int bracketCounter = 0;  // counts the number of brackets
int typeIdentifier = 0;  // 0 = int, 1 = float, 2 = char, 3 = string
int registerNumber = 0;  // counts the number of registers
int labelNumber = 0;     // counts the number of labels

struct variableContainer
{
    int identifier; // Each variable should have a unique identifier
    int type;       // 0 = int, 1 = float, 2 = char, 3 = string
    int intValue;
    float floatValue;
    char charValue;
    char* stringValue;
    int boolValue;
} variables[100];

// -------------------------------- Variable Functions --------------------------------
// Function to check if variable is already declared
int checkVariableExistence(int id)
{
    int i;
    for (i = 0; i < variableCounter; i++)
    {
        if (variables[i].identifier == id)
        {
            return 1;
        }
    }

    return 0;
}

// Function to print variables
void printVariables()
{
    int i;
    printf("printing variables\n");
    for (i = 0; i < variableCounter; i++)
    {
        printf("ID: %d, with Type: %d\n", variables[i].identifier, variables[i].type);
    }
    printf("Finished Printing\n\n");
}

// Function to append variable to array
void appendVariable(int id, int type, int intValue, float floatValue, char charValue, char* stringValue, int boolValue)
{
    if (checkVariableExistence(id) == 0)
    { // if variable is not declared

        variables[variableCounter].identifier = id;
        variables[variableCounter].type = type;
        variables[variableCounter].intValue = intValue;
        variables[variableCounter].floatValue = floatValue;
        variables[variableCounter].charValue = charValue;
        variables[variableCounter].stringValue = stringValue;
        variables[variableCounter].boolValue = boolValue;
        variableCounter++;
    }

    else // if variable is already declared
    {
        printf("Variable already declared\n");
        exit(1);
    }
}


// Function to check variable type
int checkVariableType(int id)
{
    int i;
    for (i = 0; i < variableCounter; i++)
    {
        if (variables[i].identifier == id)
        {
            return variables[i].type;
        }
    }
    return -1;
}

// Function that checks assignment compatibility
int checkAssignmentCompatibility(int id, int mathElementType)
{
    int varType = checkVariableType(id); // variable type

    printf("mathElementType: %d and varType: %d\n", mathElementType, varType);
    printf("ID: %d\n", id);

    if (varType == -1 || mathElementType == -1)
    {
        printf("Variable not declared\n");
        exit(1);
    }

    else if (varType == mathElementType)
    {
        printf("Variable type and math element type are compatible\n");
        return 1;
    }

    else
    {
        printf("Type mismatch\n");
        exit(1);
    }
}

// Function to get variable value
int getINTVariableValue(int id)
{
    int i;
    int gotAnID = -1;

    for (i = 0; i < variableCounter; i++) //
    {
        if (variables[i].identifier == id)
        {
            gotAnID = 1;
            printf("Returning Variable Value: %d\n", variables[i].intValue);
            return variables[i].intValue;
        }
    }

    if(gotAnID == -1)
    {
        printf("Returning INT CONSTANT Value: %d\n", id);
        return id;
    }
}

float getFLOATVariableValue(int id)
{
    int i;
    int gotAnID = -1;
    
    for (i = 0; i < variableCounter; i++)
    {
        if (variables[i].identifier == id)
        {
            gotAnID = 1;
            printf("Returning Variable Value: %d\n", variables[i].intValue);
            return variables[i].floatValue;
        }
    }

    if(gotAnID == -1)
    {
        printf("Returning FLOAT CONSTANT Value: %d\n", id);
        return (float)id;
    }
}

char getCHARVariableValue(int id)
{
    int i;
    for (i = 0; i < variableCounter; i++)
    {
        if (variables[i].identifier == id)
        {
            return variables[i].charValue;
        }
    }
    return '\0';
}

char* getSTRINGVariableValue(int id)
{
    int i;
    for (i = 0; i < variableCounter; i++)
    {
        if (variables[i].identifier == id)
        {
            return variables[i].stringValue;
        }
    }
    return NULL;
}

int getBOOLVariableValue(int id)
{
    int i;
    for (i = 0; i < variableCounter; i++)
    {
        if (variables[i].identifier == id)
        {
            return variables[i].boolValue;
        }
    }

    return -1;
}



// Function to check for valid exit
void checkExit()
{
    if (bracketCounter == 0)
    {
        printf("EXITING PROGRAM...\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Invalid exit\n");
        exit(EXIT_FAILURE);
    }
}



// -------------------------------- Quadruple Functions --------------------------------
// Function to allocate a variable in a register
void allocateRegister(int id)
{
    printf("MOV R%d, VariableID: %d\n", registerNumber++, id);
}

// Function to allocate a variable in a register
void allocateINTValueToRegisterWithID(int id, int value)
{
    printf("MOV ID:%d, Value: %d\n MOV R%d, ID%d\n", id, value, registerNumber++, id);
}

void allocateFLOATValueToRegisterWithID(int id, float value)
{
    printf("MOV ID:%d, Value: %f\n MOV R%d, ID%d\n", id, value, registerNumber++, id);
}

void allocateCHARValueToRegisterWithID(int id, char value)
{
    printf("MOV ID:%d, Value: %c\n MOV R%d, ID%d\n", id, value, registerNumber++, id);
}

void allocateSTRINGValueToRegisterWithID(int id, char *value)
{
    printf("MOV ID:%d, Value: %s\n MOV R%d, ID%d\n", id, value, registerNumber++, id);
}

void allocateBOOLValueToRegisterWithID (int id, int value)
{
    if(value == 1) //TRUE
    printf("MOV ID:%d, Value: %d, TRUE\n MOV R%d, ID%d\n", id, value, registerNumber++, id);

    else           //FALSE
    printf("MOV ID:%d, Value: %d, FALSE\n MOV R%d, ID%d\n", id, value, registerNumber++, id);
}

void addINTTwoRegisters(int a, int b)
{
    if(a == -1 || b == -1)
    {
        printf("Invalid Addition\n");
        exit(1);
    }
    registerNumber++;
    printf("MOV R%d, %d\n MOV R%d, %d\n ADD R%d, R%d, R%d\n R%d = %d\n\n", 10, a, 11, b, registerNumber, 10, 11, registerNumber, a + b);
    // R10,R11 are used for Arithmetic operations
}

void addFLOATTwoRegisters(float a, float b)
{
    if(a == -1.0 || b == -1.0)
    {
        printf("Invalid Addition\n");
        exit(1);
    }
    registerNumber++;
    printf("MOV R%d, %f\n MOV R%d, %f\n ADD R%d, R%d, R%d\n R%d = %f\n\n", 10, a, 11, b, registerNumber, 10, 11, registerNumber, a + b);
    // R10,R11 are used for Arithmetic operations
}

void subINTTwoRegisters(int a, int b)
{
    if(a == -1 || b == -1)
    {
        printf("Invalid Subtraction\n");
        exit(1);
    }
    registerNumber++;
    printf("MOV R%d, %d\n MOV R%d, %d\n SUB R%d, R%d, R%d\n R%d = %d\n\n", 10, a, 11, b, registerNumber, 10, 11, registerNumber, a - b);
    // R10,R11 are used for Arithmetic operations
}

void subFLOATTwoRegisters(float a, float b)
{
    if(a == -1.0 || b == -1.0)
    {
        printf("Invalid Subtraction\n");
        exit(1);
    }
    registerNumber++;
    printf("MOV R%d, %f\n MOV R%d, %f\n SUB R%d, R%d, R%d\n R%d = %f\n\n", 10, a, 11, b, registerNumber, 10, 11, registerNumber, a - b);
    // R10,R11 are used for Arithmetic operations
}

void mulINTTwoRegisters(int a, int b)
{
    if(a == -1 || b == -1)
    {
        printf("Invalid Multiplication\n");
        exit(1);
    }
    registerNumber++;
    printf("MOV R%d, %d\n MOV R%d, %d\n MUL R%d, R%d, R%d\n R%d = %d\n\n", 10, a, 11, b, registerNumber, 10, 11, registerNumber, a * b);
    // R10,R11 are used for Arithmetic operations
}

void mulFLOATTwoRegisters(float a, float b)
{
    if(a == -1.0 || b == -1.0)
    {
        printf("Invalid Multiplication\n");
        exit(1);
    }
    registerNumber++;
    printf("MOV R%d, %f\n MOV R%d, %f\n MUL R%d, R%d, R%d\n R%d = %f\n\n", 10, a, 11, b, registerNumber, 10, 11, registerNumber, a * b);
    // R10,R11 are used for Arithmetic operations
}

void divINTTwoRegisters(int a, int b)
{
    if(a == -1 || b == -1)
    {
        printf("Invalid Division\n");
        exit(1);
    }
    registerNumber++;
    printf("MOV R%d, %d\n MOV R%d, %d\n DIV R%d, R%d, R%d\n R%d = %d\n\n", 10, a, 11, b, registerNumber, 10, 11, registerNumber, a / b);
    // R10,R11 are used for Arithmetic operations
}

void divFLOATTwoRegisters(float a, float b)
{
    if(a == -1.0 || b == -1.0)
    {
        printf("Invalid Division\n");
        exit(1);
    }
    registerNumber++;
    printf("MOV R%d, %f\n MOV R%d, %f\n DIV R%d, R%d, R%d\n R%d = %f\n\n", 10, a, 11, b, registerNumber, 10, 11, registerNumber, a / b);
    // R10,R11 are used for Arithmetic operations
}

// Function to allocate a Label
void allocateLabel()
{
    printf("LABEL L%d\n", labelNumber);
}

void ifStatementBegin()
{
    allocateLabel();
    printf("JMP L%d\n", labelNumber);
}

void ifStatementEnd()
{
    printf("END L%d\n", labelNumber);
    labelNumber++;
}

void ifStatementElse()
{
    printf("JMP END%d\n", labelNumber);
    printf("LABEL L%d\n", labelNumber);
}

void loopInitial()
{
    allocateLabel();
    printf("LOOP L%d\n", labelNumber);
}

void loopEnd()
{
    printf("END L%d\n", labelNumber);
    labelNumber++;
}

//Function that checks for the condition
void checkCondition(char* symbol, int firstComparater, int secondComparater)
{
    if(symbol == ">=")
    {
        printf("CMP T,Value1: %d,Value2: %d\n", firstComparater, secondComparater);      
        printf("JNeg T,end \n");
    }

    else if(symbol == "<=")
    {
        printf("CMP T,Value1: %d,Value2: %d\n", firstComparater, secondComparater);      
        printf("JPos T,end \n");
    }

    else if(symbol == ">")
    {
        printf("CMP T,Value1: %d,Value2: %d\n", firstComparater, secondComparater);      
        printf("JZ T,end \n");
    }

    else if(symbol == "<")
    {
        printf("CMP T,Value1: %d,Value2: %d\n", firstComparater, secondComparater);      
        printf("JNZ T,end \n");
    }

    else if(symbol == "==")
    {
        printf("CMP T,Value1: %d,Value2: %d\n", firstComparater, secondComparater);      
        printf("JE T,end \n");
    }

    else if(symbol == "!=")
    {
        printf("CMP T,Value1: %d,Value2: %d\n", firstComparater, secondComparater);      
        printf("JNE T,end \n");
    }

    
}

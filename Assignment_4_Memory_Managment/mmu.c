/*
Author:
Kurt Newcomb

Date:
5/23/2020

Class:
CST-221

Assignment:
Memory Management

Description-
	Write a C program that takes a decimal number between 0 and 4095 as input from a user that performs the following operations on the input:
		a.	Display the number as a 32-bit binary number displaying each binary digit as a 1 or 0 (with the least significant bit on right) on the console. 
		b.	Display the number as a 32-bit hexadecimal number on the console. 
		c.	Transform the input by shifting the number 16 bits to the left, then mask out (AND) the bottom 16 bits, and finally add (OR) the hex number 0x07FF to produce the final resultant number. Display the final result in binary, hexadecimal, and decimal to the console.
		d.	Write your program in a modular fashion to eliminate redundant code.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Declare variables and 32 bit binary array.
int i;
int j;
int x;
int finalResult;
unsigned int decimalValue;
unsigned int transformationResult;
unsigned int leftShiftResult;
unsigned int maskedBottomResult;
char binaryArray[32];
char hexArray[100];



// Function to read input from console and clear input buffer.
void* scanUserInput(){
	scanf("%d", &decimalValue);
	while ((getchar()) != '\n'){

	}
}

// Function for part A.
// Function to convert a decimal between 0 and 4095 to binary
char* convertDecToBin(int valueToConvert){
    static char tempArray[32];
    if (valueToConvert >= 0 && valueToConvert < 4096){
		unsigned int mask = 1 << 31;
		for (i = 0; i < 8; i++){
			for (j = 0; j < 4; j++){
				char c = (valueToConvert & mask) == 0 ? '0' : '1';
				tempArray[x++] = c;
				mask >>= 1;
			}
		}
	}
    return tempArray;
}

// Function for part B.
// Function to convert from decimal to hexadecimal
char* convertDecToHex(int valueToConvert){
    long quotient, remainder;
    int j = 0;
    static char tempArray[32];
    quotient = valueToConvert;
    while (quotient != 0)
    {
        remainder = quotient % 16;               
        if (remainder < 10){
            tempArray[j++] = 48 + remainder;        
        }  
        else {
            tempArray[j++] = 55 + remainder;      
            quotient = quotient / 16;            
        }
    }
    return tempArray;
}

//Function for Part C.
//Shift 16 bits to the left
//Add the hex number 0x07FF to produce the final resultant number
int transformNumber(int valueToConvert){
    int resultValue;
	leftShiftResult = valueToConvert << 16;
	maskedBottomResult = leftShiftResult & valueToConvert;
	unsigned int addition = 0x07FF;
	resultValue = maskedBottomResult | addition;	
    return resultValue;
}



//Main function for obvious stuff :D
int main (void){
    // Part A. - Print a decimal input value in binary
    printf("Enter a value: (between 0-4095)\n");
    scanUserInput();
    printf("You entered a decimal value of: %d\n", decimalValue);
    strcpy(binaryArray, convertDecToBin(decimalValue));
    printf("The Binary form of the value you entered is: %s\n", binaryArray);
    
	// Part B. - Convert the decimal value to hexadecimal
    strcpy(hexArray, convertDecToHex(decimalValue));
    printf("The Hexadecimal form of the value you entered is: %s\n", hexArray);
    
	// Part C. - Do some stuff to the decimal value
    finalResult = transformNumber(decimalValue);
    printf("The result of shifting the value you entered 16 bits to the left is: %d\n", leftShiftResult);
    printf("After masking out the bottom 16 bits: %d\n", maskedBottomResult);
    printf("After adding 0x07FF (OR): %d\n", finalResult);
	
	
	return 0;
}
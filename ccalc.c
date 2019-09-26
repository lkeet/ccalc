// C header files
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

// Binary related functions header file - includes definition for binary_t types
#include "binary.h"

// Version 
static const char version[] = "1.1";

// Global static string constants for calculator buttons
static const char add[] = "+";
static const char sub[] = "-";
static const char mul[] = "x";
static const char dvd[] = "/";
static const char mod[] = "mod";
static const char ept[] = "^";
static const char squ[] = "sqrt";
static const char b10[] = "base10";
static const char bin[] = "binary";
static const char hel[] = "?";
static const char qui[] = "quit";

// Global static string constant for error cmdline error message
static const char err[] = "\aIllegal expression. Run program with %s to view help.";

// Performs operations listed below 
	// Operation Key
	// 1: Addition
	// 2: Subtraction
	// 3: Multiplication
	// 4: Division
	// 5: Modulus
	// 6: Exponent
double calc_basic_operation(double val1, double val2, int operation) {
	double return_val;
	switch (operation) {
		case 1: 
			return_val = val1 + val2;
			break;
		case 2:	
			return_val = val1 - val2;
			break;
		case 3: 
			return_val = val1 * val2;
			break;
		case 4: 
			return_val = val1 / val2;	
			break;
		case 5:
			return_val = fmod(val1, val2);
			break;
		case 6:
			return_val = pow(val1, val2);
			break;
	}
	return return_val;
}

// Prompts the user for two values then returns the result returned by the basic calc function
double basic_operation(int operation) {
	double val1, val2;
	for (int i = 1; i <= 2; i++) {
		printf("Please enter value %d: ", i);
		if (i == 1) {		
			scanf("%lf", &val1);
		}
		else {
			scanf("%lf", &val2);
		}
	}	
	return calc_basic_operation(val1, val2, operation);
}

// Returns the square root of an entered value
double square_root() {
	double val;
	printf("Please enter the value you wish to square root: ");
	scanf("%lf", &val);
	return sqrt(val);
}

// Prompts the user for a binary string to be converted to base10 then returns the result as a binary_t type
binary_t base10_handler() {
	binary_t return_struct;
	char val[16];
	printf("Please enter the binary string you wish to convert to base10: ");
	scanf("%s", val);
	strcpy(return_struct.binary, val);
	return return_struct;
}

// Prompts the user for an integer to be converted to binary then returns the result as a binary_t type
binary_t binary_handler() {
	int val;
	printf("Please enter the base10 integer you wish to convert to binary: ");
	scanf("%d", &val);
	return convert(val);
}

// Shows the help text 
// welcome parameter for proper formatting when shown as the "welcome screen" 
// param for determing whether the help text has been displayed from calling the help param on program execution 
void help_text(bool welcome, bool param) {
	printf(".... C Calculator Version: %s ....\n", version);
	printf("....     Written by lkeet      ....\n");
	if (!param) {
		printf("Expressions can be calculated upon program execution. Run this program with %s as a parameter to view the syntax.\n", hel);
	}
	printf("Operations:\n  [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s]\n  [%s] [%s]\n", add, sub, mul, dvd, mod, ept, squ, b10, bin, hel, qui);
	if (param) {
		printf("Syntax:\n  Basic Operations: value[1] [operation] value[2] (example: 43.5 %s 34)\n  %s/%s/%s: [operation] value (example: %s 64)\n", add, squ, b10, bin, squ);
	}
	printf("Legend:\n  %s : Addition\n  %s : Subtraction\n  %s : Multiplication\n  %s : Division\n  %s : Modulus\n  %s : Exponent\n  %s : Square Root\n  %s : Binary to Base10 Converter\n  %s : Base10 to Binary Converter\n  %s : Show Help Text\n  %s : Exit Program\n", add, sub, mul, dvd, mod, ept, squ, b10, bin, hel, qui);
	if (welcome) {
		printf("\n");
	}
}

// Recursive function for selecting the desired operation, iteration parameter increments to show the current calculation
void select_operation(int iteration) {
	char operation[10];
	printf("Calculation[%d]: Please enter the operation you wish to use: ", iteration);
	scanf("%s", operation);
	if (strcmp(operation, add) == 0) {
		printf("The sum: %lf\n", basic_operation(1));
	}
	else if (strcmp(operation, sub) == 0) {
		printf("The difference: %lf\n", basic_operation(2));
	}
	else if (strcmp(operation, mul) == 0) {
		printf("The product: %lf\n", basic_operation(3));
	}
	else if (strcmp(operation, dvd) == 0) {
		printf("The quotient: %lf\n", basic_operation(4));
	}
	else if (strcmp(operation, mod) == 0) {
		printf("The modulus: %lf\n", basic_operation(5));
	}
	else if (strcmp(operation, ept) == 0) {
		printf("The power: %lf\n", basic_operation(6));
	}
	else if (strcmp(operation, squ) == 0) {
		printf("The square root: %lf\n", square_root());
	}
	else if (strcmp(operation, b10) == 0) {
		printf("The base10 conversion: %d\n", base10(base10_handler()));
	}
	else if (strcmp(operation, bin) == 0) {
		printf("The binary conversion: %s\n", binary_handler().binary);	
	}
	else if (strcmp(operation, hel) == 0) {
		help_text(false, false);
	}
	else if (strcmp(operation, qui) == 0) {
		exit(0);
	}
	else {
		printf("\aUnrecognised Operation.\n");
	}
	printf("\n");
	select_operation(iteration + 1);
}

// Function for handling calculations from expressions parsed through argv[]
void handle_cmd_args(int argc, char* argv[]) {
	double val1, val2;
	// Checks for amount of expressions for value assignment
	if (argc > 3) {
		sscanf(argv[1], "%lf", &val1);
		sscanf(argv[3], "%lf", &val2);
	}
	// When square root is chosen as the operation
	else if (strcmp(argv[1], squ) == 0) {
		sscanf(argv[2], "%lf", &val1);
	}	
	else if (strcmp(argv[1], bin) == 0) {
		sscanf(argv[2], "%lf", &val1);
	}
	if (strcmp(argv[2], add) == 0) {
		printf("%lf", calc_basic_operation(val1, val2, 1));
	} 
	else if (strcmp(argv[2], sub) == 0) {
		printf("%lf", calc_basic_operation(val1, val2, 2));
	} 
	else if (strcmp(argv[2], mul) == 0) {
		printf("%lf", calc_basic_operation(val1, val2, 3));
	} 
	else if (strcmp(argv[2], dvd) == 0) {
		printf("%lf", calc_basic_operation(val1, val2, 4));
	} 
	else if (strcmp(argv[2], mod) == 0) {
		printf("%lf", calc_basic_operation(val1, val2, 5));
	}
	else if (strcmp(argv[2], ept) == 0) {
		printf("%lf", calc_basic_operation(val1, val2, 6));
	}
	else if (strcmp(argv[1], squ) == 0) {
		printf("%lf", sqrt(val1));
	}
	else if (strcmp(argv[1], b10) == 0) {
		binary_t val;
		strcpy(val.binary, argv[2]);
		// Error checking for determining if the entered binary is valid
		if (base10(val) > -1) {
			printf("%d", base10(val));
		}
		else {
			printf("\aThe string you entered is invalid.");
		}
	}
	else if (strcmp(argv[1], bin) == 0) {
		int val = val1;
		print_binary(convert(val));
	}
	else {
		printf(err, hel);
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	// Runs standard calculator program
	if (argc < 2) {
		help_text(true, false); // Welcome screen
		select_operation(1); // Calls recursive function with 1 as the first iteration
	}
	// Runs argument handler when an expression is parsed on program call
	else if (argc < 5) {
		// Checks for help parameter
		if (strcmp(argv[1], hel) == 0) {
			help_text(false, true);
		}
		else if (argc > 2) {
			handle_cmd_args(argc, argv);
		}
		else {
			printf(err, hel);
			printf("\n");
		}
	}
	else {
		printf(err, hel);
		printf("\n");
	}
	return 0;
}
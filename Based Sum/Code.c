#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Function "Power" calculates the power of a base raised to a power (base^power)
int Power(int base, int power){
    int start = 1;
    for (int i = 0; i < power; i++){
        start *= base;
    }
    return start;
}



// Function "check_correct_base" defines input bases are correct 
// (regarding to given conditionals in task) or not
// Also this function check for compliance of digits of number to its base
// numbers[] is a string of numbers; base[] is an array of number of base for each number; n is total number of numbers
int check_correct_base(char numbers[], int base[], int n){
    int end = 0; // Keeps track of the starting point for each number in the string
    char number[40000]; // Temporary storage for each number

    // for-loop iterates all numbers
    for (int i = 0; i < n; i++){
        sscanf(numbers + end, "%s", number); // Extract number from string of numbers
        end += strlen(number) + 1; // Update end position to the next number

        // for-loop iterates all digits of each number
        for (int j = 0; j < strlen(number); j++){
            if (number[j] == '\n') {
                break; // Ignore the last symbol '\n' of string if it exists
            }
            if (base[i] == 2){
                if (number[j] < 48 | number[j] > 49){
                    return 1; // Return the error if there is not only 0 and 1 in binary number
                }
            } else if (base[i] == 8){
                if (number[j] < 48 | number[j] > 55){
                    return 1; // Return the error if there is not only from 0 to 7 in octal number
                }
            } else if (base[i] == 10){
                if (number[j] < 48 | number[j] > 57){
                    return 1; // Return the error if there is not only from 0 to 9 in decimal number
                }
            } else if (base[i] == 16){
                if (number[j] < 48 | number[j] > 70 | (number[j] > 57 & number[j] < 65)){
                    return 1; // Return the error if there is not only from 0 to F in hexadecimal number
                }
            } else{
                return 1; // Return the error if there is different base from 2, 8, 10 or 16
            }
        }
    }

    return 0; // Return 0 if all numbers and bases are correct
}



// Function "convert_to_dec" converts a number of base (2, 8, 10, 16) to decimal
// a[] is a number as a string; base is a number of base of the number; len is a number od digits in number
int convert_to_dec(char a[], int base, int len){
    int tot = 0; // a variable for storing the result

    // for-loop iterate every digit in the string a
    for (int i = 0; i < strlen(a); i++){
        if (a[i] < 48 | a[i] > 70 | (a[i] > 57 & a[i] < 65)){
            break; // Avoid elements of string that shouldn't be there
        }
        // Convert binary to decimal
        if (base == 2){
            tot += ((int)a[i] - 48) * Power(2, len - 1- i);
        // Convert octal to decimal
        } else if (base == 8){
            tot += ((int)a[i] - 48) * Power(8, len - 1- i);
        // Convert decimal to decimal
        } else if (base == 10){
            tot += ((int)a[i] - 48) * Power(10, len - 1- i);
        // Convert hexadecimal to decimal
        } else if (base == 16){
            if ((48 <= (int)a[i]) & ((int)a[i] <= 57)){
                tot += ((int)a[i] - 48) * Power(16, len - 1- i);
            } else{
                tot += ((int)a[i] - 55) * Power(16, len - 1- i);
            }
        }


    }
    return tot; // Return the decimal value of number
}



// Function "find_sum" calculates the sum of numbers with special condition
// n is total number of numbers; numbers[40000] is the string of numbers; bases[40000] is tha string of numbers' bases
int find_sum(int n, char numbers[40000], int bases[40000]){

    int sum = 0;
    // Due to consequence "-10" to even elements and "+10" to odd ones, it will effect on sum only if there is odd number of numbers
    // Because other even numbers we can separete on pairs, so "-10" and "+10" will give zero
    if (n % 2 == 1){
        sum = -10;
    }
    int i = 0;
    char* number = strtok(numbers, " "); // Split the numbers by space
    int len = strlen(number); // len is the number of digits of current number

    // While-loop iterates all numbers in string numbers
    while (number != NULL){
        len = strlen(number); // len is the number of digits of current number
        if (i == (n - 1)){
            len -= 1;
        }

        // Add the result of converted number
        sum += convert_to_dec(number, bases[i], len);
        i++;
        number = strtok(NULL, " "); // Get the next number
    }

   return sum; 
}


int main(){

    // Open input and output files
    FILE* file = fopen("input.txt", "r");
    FILE* file_out = fopen("output.txt", "w");


    // Read the number of inputs (N)
    char a[40000];
    fgets(a, sizeof(a), file);
    int N = atoi(a); // Convert the string to an integer
    // Check if N between 1 and 40 as it was in task condition
    if (N < 1 | N > 40){
        fprintf(file_out, "Invalid inputs\n");
        fclose(file);
        fclose(file_out);
        return 0;
    }

    // Read the space-separated numbers
    char S[40000];
    fgets(S, sizeof(S), file);

    // Read the array of bases
    char A[40000];
    fgets(A, sizeof(A), file);
    int bases[N]; // An array for bases
    int i = 0;
    char* part = strtok(A, " ");
    // While-loop goes through the line A and divides it by space then collect int bases in array
    while (part != NULL){
        bases[i] = atoi(part);
        i++;
        part = strtok(NULL, " ");
    }


    // Create a copy of S (string of numbers)
    char S1[40000];
    strcpy(S1, S);
    // Validate the correct bases
    int check = check_correct_base(S1, bases, N);

    // If checking returns the error then print "Invalid inputs\n" in output and close files
    if (check == 1) {
        fprintf(file_out, "Invalid inputs\n");
        fclose(file);
        fclose(file_out);
        return 0;
    }


    // If checking doesn't return the error then print the sum of numbers in output and close files
    int sum = find_sum(N, S, bases);
    fprintf(file_out, "%d\n", sum);
    fclose(file);
    fclose(file_out);



    return 0;
}
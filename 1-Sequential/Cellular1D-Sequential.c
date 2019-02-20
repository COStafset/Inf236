/*
Copyright (c) 2019 Christian Stafset

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>

    int main(int argc, char ** argv) {
        if (argc == 4) {
			char rules[8];
			int iterations;
			iterations = atoi(argv[3]);
			char * in = NULL;
			char * newArray = NULL;
			int numChars;
			
			FILE * csvOut = fopen("set.csv", "a");
			  
			//open input
			FILE * input = fopen(argv[2], "r");
			fscanf(input, "%i\n", &numChars);
			
			in = malloc(sizeof(char) * numChars);
			newArray = malloc(sizeof(char) * numChars);
			if (input) {				    
				fread(in, 1, numChars, input);
				fclose(input);
			}
			
			//prints input
			int i;
			for (i = 0; i < numChars; i++) {
				if (in[i] == '1') {
					printf("\x1B[47m \x1B[0m");
				}
				else {
					printf(" ");
				}
				fprintf(csvOut, "%c", in[i]);
				if (i != numChars-1) {
					fprintf(csvOut, ",");
				}
			}
			printf("\n");
			fprintf(csvOut, "\n");
			
			//open ruleset
			FILE * rulesFile = fopen(argv[1], "r");

			//if succeed
			if (rulesFile) {
				//read rules into the array
				for (i = 0; i < 8; i++) {
					fscanf(rulesFile, "%*c%*c%*c %c\n", &rules[i]);
				}
				fclose(rulesFile);
			}
			
			int j;
			int inputNum;
			for (j = 0; j < iterations; j++) {
				for (i = 0; i < numChars; i++) {
					if (i == 0) {
					
						inputNum = ((in[numChars-1] - '0') << 2) + ((in[0] - '0') << 1) + (in[1] - '0');
						newArray[i] = rules[inputNum];
					
					}
					
					else if (i == numChars - 1) {
						
						inputNum = ((in[i-1] - '0') << 2) + ((in[i] - '0') << 1) + (in[0] - '0');
						
						
						newArray[i] = rules[inputNum];
					}
					else {
						inputNum = ((in[i-1] - '0') << 2) + ((in[i] - '0') << 1) + (in[i+1] - '0');
						
						newArray[i] = rules[inputNum];
					}					
				}
				for (i = 0; i < numChars; i++) {
					if (newArray[i] == '1') {
						printf("\x1B[47m \x1B[0m");
					}
					else {
						printf(" ");
					}
					fprintf(csvOut, "%c", newArray[i]);
					if (i != numChars-1) {
						fprintf(csvOut, ",");
					}
				}
				printf("\n");
				fprintf(csvOut, "\n");
				free(in);
				in = newArray;
				newArray = malloc(sizeof(char) * numChars);
			}
		}
	}
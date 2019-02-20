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
#include <unistd.h>

int main (int argc, char ** argv) {

	if (argc == 4) {
	
		FILE * rulesFile = fopen(argv[1], "r");
		FILE * inputFile = fopen(argv[2], "r");
		int t;
		t = atoi(argv[3]);
		int n;
		char ** input;
		char * rules;
		char ** result;
		
		int false = 0;
		
		int i;
		int j;
		int k;
		
		if (inputFile && rulesFile) {
		
			fscanf(inputFile, "%i\n", &n);
			input = malloc(n * sizeof(char*));
			result = malloc(n * sizeof(char*));
			
			for (i = 0; i < n; i++) {
				input[i] = malloc(n * sizeof(char));
				result[i] = malloc(n * sizeof(char));
			}
			
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					fscanf(inputFile, "%c", &input[i][j]);
				}
				if (i != n-1) {
					fscanf(inputFile, "%*c");
				}
			}
			fclose(inputFile);
			
			rules = malloc(512 * sizeof(char));
			
			for (i = 0; i < 512; i++) {
				fscanf(rulesFile, "%*c%*c%*c%*c%*c%*c%*c%*c%*c %c\n", &rules[i]);
			}
			fclose(rulesFile);
			
			fprintf(stderr, "have read rules and input\n");
			for (k = 0; k < t; k++) {
				for (i = 0; i < n; i++) {
					for (j = 0; j < n; j++) {
						int ruleNum = 0;
						
						int iPlus = i+1;
						int iMinus = i-1;
						
						int jPlus = j+1;
						int jMinus = j-1;
						
						if (i == 0) {
							iMinus = n-1;
						}
						if (j == 0) {
							jMinus = n-1;
						}
						if (i == n-1) {
							iPlus = 0;
						}
						if (j == n-1) {
							jPlus = 0;
						}
						
						if (input[iMinus][jMinus] == '1') {
							ruleNum += 256;
						}
						if (input[iMinus][j] == '1') {
							ruleNum += 128;
						}
						if (input[iMinus][jPlus] == '1') {
							ruleNum += 64;
						}
						if (input[i][jMinus] == '1') {
							ruleNum += 32;
						}
						if (input[i][j] == '1') {
							ruleNum += 16;
						}
						if (input[i][jPlus] == '1') {
							ruleNum += 8;
						}
						if (input[iPlus][jMinus] == '1') {
							ruleNum += 4;
						}
						if (input[iPlus][j] == '1') {
							ruleNum += 2;
						}
						if (input[iPlus][jPlus] == '1') {
							ruleNum += 1;
						}
						
						result[i][j] = rules[ruleNum];
						if (result[i][j] == '1') {
							printf("*");
						}
						else {
							printf(" ");
						}
						
					}
					printf("\n");
				}
				printf("\033[2J");   // Clean the screen
  				printf("\033[1;1H"); // Set the cursor to 1:1 position
  				usleep(100000);
				input = result;
			}
		}
		else {
			fprintf(stderr, "nope\n");
		}
	}		
}


	


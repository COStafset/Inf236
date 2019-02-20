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
#include <mpi.h>
#include <time.h>

    int main(int argc, char ** argv) {
    	clock_t begin = clock();
        if (argc == 4) {
			int sendCount;
			int numProcesses;
			int myRank;
			char rules[8];
			int iterations;
			iterations = atoi(argv[3]);
			char * in = NULL;
			int numChars;
			
			
			
			MPI_Init(&argc, &argv);
			MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
			MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
			
			
			// put input here
			FILE * input = fopen(argv[2], "r");
			if (!(fscanf(input, "%i\n", &numChars))) {
				fprintf(stderr, "bad");
			}
			
			if (myRank == 0) {
				in = malloc(sizeof(char) * numChars);
				//if successful
				if (input) {				    
					if (!(fread(in, sizeof(char), numChars, input))) {
						fprintf(stderr, "bad");
					}
				}
			}
			
			fclose(input);
			
  
			sendCount = numChars / numProcesses;
			//open ruleset
			FILE * rulesFile = fopen(argv[1], "r");

			//if successful
			if (rulesFile) {
				int i;
				for (i = 0; i < 8; i++) {
					if (!(fscanf(rulesFile, "%*c%*c%*c %c\n", &rules[i]))) {
						fprintf(stderr, "bad");
					}
				}
				fclose(rulesFile);
			}
			
			int i;
			

			char subArray[sendCount];
			MPI_Scatter(in, sendCount, MPI_CHAR, subArray, sendCount, MPI_CHAR, 0, MPI_COMM_WORLD);
			
			/*if (myRank == 0) {
				for (i = 0; i < numChars; i++) {
					if (in[i] == '1') {
						printf("\x1B[47m \x1B[0m");
					}
					else {
						printf(" ");
					}
				}
				printf("\n");
			}*/
		
			int processAbove;
			int processBelow;
			if (myRank == numProcesses - 1) {
				processAbove = 0;
			}
			else {
				processAbove = myRank + 1;
			}
			
			if (myRank == 0) {
				processBelow = numProcesses - 1;
			}
			else {
				processBelow = myRank - 1;
			}
			
			
			
			char * newArray = NULL;
			newArray = malloc(sizeof(char) * sendCount);
			
			char * result = NULL;
			if (myRank == 0) {
				result = malloc(sizeof(char) * numChars);
			}
			
			int j;
			for (j = 0; j < iterations; j++) {
				for (i = 0; i < sendCount; i++) {
					if (i == 0) {
						char prevChar;
						if (myRank % 2 == 0) {	
							MPI_Send(&subArray[sendCount-1], 1, MPI_CHAR, processAbove, 0, MPI_COMM_WORLD);
							MPI_Recv(&prevChar, 1, MPI_CHAR, processBelow, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						}
						else {							
							MPI_Recv(&prevChar, 1, MPI_CHAR, processBelow, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							MPI_Send(&subArray[sendCount-1], 1, MPI_CHAR, processAbove, 0, MPI_COMM_WORLD);
						}
						
						int input = 0;
						if (prevChar == '1') {
							input += 4;
						}
						if (subArray[0] == '1') {
							input += 2;
						}
						if (subArray[1] == '1') {
							input += 1;
						}
						
						newArray[i] = rules[input];
					}
					
					else if (i == sendCount - 1) {
						char lastChar;
						if (myRank % 2 == 0) {
							MPI_Send(&subArray[0], 1, MPI_CHAR, processBelow, 0, MPI_COMM_WORLD);
							MPI_Recv(&lastChar, 1, MPI_CHAR, processAbove, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						}
						else {								
							MPI_Recv(&lastChar, 1, MPI_CHAR, processAbove, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							MPI_Send(&subArray[0], 1, MPI_CHAR, processBelow, 0, MPI_COMM_WORLD);
						}
						
						int input = 0;
						if (subArray[i-1] == '1') {
							input += 4;
						}
						if (subArray[i] == '1') {
							input += 2;
						}
						if (lastChar == '1') {
							input += 1;
						}
						newArray[i] = rules[input];
					}
					else {
						int input = 0;
						if (subArray[i-1] == '1') {
							input += 4;
						}
						if (subArray[i] == '1') {
							input += 2;
						}
						if (subArray[i+1] == '1') {
							input += 1;
						}
						newArray[i] = rules[input];
					}
				}
			
				
				MPI_Gather(newArray, sendCount, MPI_CHAR, result, sendCount, MPI_CHAR, 0, MPI_COMM_WORLD);
				
				/*if (myRank == 0) {
					
					for (i = 0; i < numChars; i++) {
						if (result[i] == '1') {
						printf("\x1B[47m \x1B[0m");
						}
						else {
							printf(" ");
						}
					}		
					printf("\n");
					fprintf(stderr, "%i", j);
				}*/
				if (j != iterations - 1) {
					MPI_Scatter(result, sendCount, MPI_CHAR, subArray, sendCount, MPI_CHAR, 0, MPI_COMM_WORLD);
				}
				
			}
			
			MPI_Finalize();
			if (myRank == 0) {
				clock_t end = clock();
				double timeSpent = (double)(end-begin) / CLOCKS_PER_SEC;
				fprintf(stderr, "Time spent: %f", timeSpent);
			}
		}
	}

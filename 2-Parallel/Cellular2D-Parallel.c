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
#include <unistd.h>
#include <time.h>

int main (int argc, char ** argv) {
	clock_t begin = clock();
	if (argc == 4) {
		
		int myRank;
		int numProcesses;
		
		int i;
		int j;
		
		MPI_Init(&argc, &argv);
		MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
		MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
		
		int processBefore;
		int processAfter;
		if (myRank == 0) {
			processBefore = numProcesses - 1;
		}
		else {
			processBefore = myRank - 1;
		}
		if (myRank == numProcesses - 1) {
			processAfter = 0;
		}
		else {
			processAfter = myRank + 1;
		}
		
		
		FILE * rulesFile = fopen(argv[1], "r");
		FILE * inputFile = fopen(argv[2], "r");
		
		if (rulesFile && inputFile) {
		
			int iterations;
			iterations = atoi(argv[3]);
			
			int n;
			int ok = fscanf(inputFile, "%i\n", &n);
			if (!ok) {
			
			}
			
			char * input;
			input = malloc(n*n*sizeof(char));
			if (myRank != 0) {
				free(input);
			}
			int curIndex = 0;
			if (myRank == 0) {
				for (i = 0; i < n*n+n-1; i++) {
					char c;
					ok = fscanf(inputFile, "%c", &c);
					if (c != '\n') {
						input[curIndex] = c;
						curIndex++;
					}
				}
				fclose(inputFile);
				/*
				for (i = 0; i < n*n; i++) {
					printf("%c", input[i]);
					if ((i+1) % n == 0) {
						printf("\n");
					}
				}
				*/
			}
			
			char rules[512];
			for (i = 0; i < 512; i++) {
				ok = fscanf(rulesFile, "%*c%*c%*c%*c%*c%*c%*c%*c%*c %c\n", &rules[i]);
			}
			fclose(rulesFile);
			
			int sendCount = (n * n) / numProcesses;
			char * subArray;
			subArray = malloc(sendCount*sizeof(char));
			
			char * result = NULL;
			if (myRank == 0) {
				result = malloc(n*n*sizeof(char));
			}
			
			char * newArray = malloc(sendCount * sizeof(char));
			
			for (i = 0; i < iterations; i++) {
			
				MPI_Scatter(input, sendCount, MPI_CHAR, subArray, sendCount, MPI_CHAR, 0, MPI_COMM_WORLD);
				
				
				for (j = 0; j < sendCount; j++) {
				
					char aboveLeft;
					char above;
					char aboveRight;
					char left;
					char centre;
					char right;
					char belowLeft;
					char below;
					char belowRight;
					
					//above left
					if (j % n == 0 || j <= n) {
						if (myRank % 2 == 0) {
							if (processAfter != -1) {
								MPI_Send(&subArray[sendCount-n+j-1], 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD);
							}
							if (processBefore != -1) {
								MPI_Recv(&aboveLeft, 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								aboveLeft = '0';
							}
						}
						else {
							if (processBefore != -1) {
								MPI_Recv(&aboveLeft, 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								aboveLeft = '0';
							}
							if (processAfter != -1) {
								MPI_Send(&subArray[sendCount-n+j-1], 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD);
							}
						}
					}
					else if (j % n != 0 && j > n) {
						aboveLeft = subArray[j-n-1];
					}
					else {
						aboveLeft = '0';
					}
					
					//above
					if (j < n) {
						if (myRank % 2 == 0) {
							if (processAfter != -1) {
								MPI_Send(&subArray[sendCount-n+j], 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD);
							}
							if (processBefore != -1) {
								MPI_Recv(&above, 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								above = '0';
							}
						}
						else {
							if (processBefore != -1) {
								MPI_Recv(&above, 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								above = '0';
							}
							if (processAfter != -1) {
								MPI_Send(&subArray[sendCount-n+j], 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD);
							}
						}
					}
					else if (j >= n) {
						above = subArray[j-n];
					}
					else {
						above = '0';
					}
					
					//above right
					if (j % n == n - 1 || j < n - 1) {
						if (myRank % 2 == 0) {
							if (processAfter != -1) {
								MPI_Send(&subArray[sendCount-n+j+1], 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD);
							}
							if (processBefore != -1) {
								MPI_Recv(&aboveRight, 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								aboveRight = '0';
							}
						}
						else {
							if (processBefore != -1) {
								MPI_Recv(&aboveRight, 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								aboveRight = '0';
							}
							if (processAfter != -1) {
								MPI_Send(&subArray[sendCount-n+j+1], 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD);
							}
						}
					}
					else if (j % n != n - 1 && j >= n-1) {
						aboveRight = subArray[j-n+1];
					}
					else {
						aboveRight = '0';
					}
					
					//left
					if (j % n == 0 && j+n-1 < sendCount) {
						left = subArray[j+n-1];
					}
					else if (j % n != 0) {
						left = subArray[j-1];
					}
					else {
						left = '0';
					}
					
					centre = subArray[j];
					
					//right
					if (j % n == n-1 && j-n+1 >= 0) {
						right = subArray[j-n+1];
					}
					else if (j != sendCount - 1) {
						right = subArray[j+1];
					}
					else {
						right = '0';
					}
					
					//below left node
					if (j % n == 0 || j > sendCount - n) {
						if (myRank % 2 == 0) {
							if (processBefore != -1) {
								MPI_Send(&subArray[j-sendCount+n-1], 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD);
							}
							if (processAfter != -1) {
								MPI_Recv(&belowLeft, 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								belowLeft = '0';
							}
						}
						else {
							if (processAfter != -1) {
								MPI_Recv(&belowLeft, 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								belowLeft = '0';
							}
							if (processBefore != -1) {
								MPI_Send(&subArray[j-sendCount+n-1], 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD);
							}
						}
					}
					else if (j % n != 0 && j <= sendCount - n) {
						belowLeft = subArray[j+n-1];
					}
					else {
						belowLeft = '0';
					}
					
					//below node
					if (j > sendCount - n) {
						if (myRank % 2 == 0) {
							if (processBefore != -1) {
								MPI_Send(&subArray[sendCount+n-j], 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD);
							}
							if (processAfter != -1) {
								MPI_Recv(&below, 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								below = '0';
							}
						}
						else {
							if (processAfter != -1) {
								MPI_Recv(&below, 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								below = '0';
							}
							if (processBefore != -1) {
								MPI_Send(&subArray[sendCount+n-j], 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD);
							}
						}
					}
					else if (j <= sendCount - n) {
						below = subArray[j+n];
					}
					else {
						below = '0';
					}
					
					//below right node
					if (j % n == sendCount - 1 || j > sendCount - n) {
						if (myRank % 2 == 0) {
							if (processBefore != -1) {
								MPI_Send(&subArray[sendCount+n-j+1], 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD);
							}
							if (processAfter != -1) {
								MPI_Recv(&belowRight, 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								belowRight= '0';
							}
						}
						else {
							if (processAfter != -1) {
								MPI_Recv(&belowRight, 1, MPI_CHAR, processAfter, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							}
							else {
								belowRight = '0';
							}
							if (processBefore != -1) {
								MPI_Send(&subArray[sendCount+n-j+1], 1, MPI_CHAR, processBefore, 0, MPI_COMM_WORLD);
							}
						}
					}
					else if (j % n != sendCount - 1 && j <= sendCount - n) {
						belowRight = subArray[j+n+1];
					}
					else {
						belowRight = '0';
					}
					
					int ruleNum = 0;
					
					if (aboveLeft == '1') {
						ruleNum += 256;
					}
					if (above == '1') {
						ruleNum += 128;
					}
					if (aboveRight == '1') {
						ruleNum += 64;
					}
					if (left == '1') {
						ruleNum += 32;
					}
					if (centre == '1') {
						ruleNum += 16;
					}
					if (right == '1') {
						ruleNum += 8;
					}
					if (belowLeft == '1') {
						ruleNum += 4;
					}
					if (below == '1') {
						ruleNum += 2;
					}
					if (belowRight == '1') {
						ruleNum += 1;
					}
					
					//if (myRank == 0) {
					//	fprintf(stderr, "al%c a%c ar%c l%c c%c r%c bl%c b%c br%c %i\n", aboveLeft, above, aboveRight, left, centre, right, belowLeft, below, belowRight, ruleNum);
					//}
					newArray[j] = rules[ruleNum];
					//newArray[j] = subArray[j];
				
				}
				
				//fprintf(stderr, "got here");
				
				//fprintf(stderr, "%i got here\n", myRank);
				/*
				char * result = NULL;
				if (myRank == 0) {
					result = malloc(n*n*sizeof(char));
				}*/
				
				MPI_Gather(newArray, sendCount, MPI_CHAR, result, sendCount, MPI_CHAR, 0, MPI_COMM_WORLD);
				/*
				if (myRank == 0) {
					//printf("printing...\n");
					for (j = 0; j < n*n; j++) {
						if (result[j] == '1') {
							printf("*");
						}
						else {
							printf(" ");
						}
						if ((j+1) % n == 0) {
							printf("\n");
						}
					}
					printf("\033[2J");   // Clean the screen
					printf("\033[1;1H"); // Set the cursor to 1:1 position
					usleep(100000);
				}
				*/
				
				input = result;			
			
			}
		
		}
		else {
			fprintf(stderr, "Error reading files");
		}	
		
		MPI_Finalize();
		if (myRank == 0) {
			clock_t end = clock();
			double timeSpent = (double)(end-begin) / CLOCKS_PER_SEC;
			fprintf(stderr, "Time spent: %f\n", timeSpent);
		}
	}
}
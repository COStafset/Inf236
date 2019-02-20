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
#include <time.h>

int main (int argc, char ** argv) {
	
	long * nums[11];
	
	int i;
	int j;
	int k;
	long num = 1024;
	
	srand(time(NULL));
	
	for (i = 0; i < 7; i++) {
		char filename[25];
		sprintf(filename, "config%li.txt", num);
		FILE * output = fopen(filename, "w");
		fprintf(output, "%li\n", num);
		for (j = 0; j < num; j++) {
			for (k = 0; k < num; k++) {
				int randNum = rand() % 2;
				fprintf(output, "%i", randNum);
			}
			fprintf(output, "\n");
		}
		fclose(output);
		num *= 2;
	}
	
}

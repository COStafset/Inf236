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
	
	FILE * out = fopen("rules.txt", "w");
	
	srand(time(NULL));
	
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	int o;
	int p;
	int q;
	for (i = 0; i < 512; i++) {
		int temp = i;
		char rule[10];
		//subtract from temp as much as you can outputting ones as necessary
		if (temp >= 256) {
			rule[0] = '1';
			temp = temp - 256;
		}
		else {
			rule[0] = '0';
		}
		if (temp >= 128) {
			rule[1] = '1';
			temp = temp - 128;
		}
		else {
			rule[1] = '0';
		}
		if (temp >= 64) {
			rule[2] = '1';
			temp = temp - 64;
		}
		else {
			rule[2] = '0';
		}
		if (temp >= 32) {
			rule[3] = '1';
			temp = temp - 32;
		}
		else {
			rule[3] = '0';
		}
		if (temp >= 16) {
			rule[4] = '1';
			temp = temp - 16;
		}
		else {
			rule[4] = '0';
		}
		if (temp >= 8) {
			rule[5] = '1';
			temp = temp - 8;
		}
		else {
			rule[5] = '0';
		}
		if (temp >= 4) {
			rule[6] = '1';
			temp = temp - 4;
		}
		else {
			rule[6] = '0';
		}
		if (temp >= 2) {
			rule[7] = '1';
			temp = temp - 2;
		}
		else {
			rule[7] = '0';
		}
		if (temp >= 1) {
			rule[8] = '1';
			temp = temp - 1;
		}
		else {
			rule[8] = '0';
		}
		int num = rand() % 2;
		rule[9] = num + '0';
		fprintf(out, "%c%c%c%c%c%c%c%c%c %c\n", rule[0], rule[1], rule[2], rule[3], rule[4], rule[5], rule[6], rule[7], rule[8], rule[9]);
		
	}
	fclose(out);
}

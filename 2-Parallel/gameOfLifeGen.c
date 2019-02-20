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

int main (int argc, char ** argv) {
	
	FILE * out = fopen("gameOfLife.txt", "w");
	
	int i;
	for (i = 0; i < 512; i++) {
		int alive = 0;
		int numNeighbours = 0;
		int temp = i;
		char rule[10];
		//subtract from temp as much as you can outputting ones as necessary
		if (temp >= 256) {
			rule[0] = '1';
			temp = temp - 256;
			numNeighbours++;
		}
		else {
			rule[0] = '0';
		}
		if (temp >= 128) {
			rule[1] = '1';
			temp = temp - 128;
			numNeighbours++;
		}
		else {
			rule[1] = '0';
		}
		if (temp >= 64) {
			rule[2] = '1';
			temp = temp - 64;
			numNeighbours++;
		}
		else {
			rule[2] = '0';
		}
		if (temp >= 32) {
			rule[3] = '1';
			temp = temp - 32;
			numNeighbours++;
		}
		else {
			rule[3] = '0';
		}
		if (temp >= 16) {
			rule[4] = '1';
			temp = temp - 16;
			
			alive = 1;
		}
		else {
			rule[4] = '0';
		}
		if (temp >= 8) {
			rule[5] = '1';
			temp = temp - 8;
			numNeighbours++;
		}
		else {
			rule[5] = '0';
		}
		if (temp >= 4) {
			rule[6] = '1';
			temp = temp - 4;
			numNeighbours++;
		}
		else {
			rule[6] = '0';
		}
		if (temp >= 2) {
			rule[7] = '1';
			temp = temp - 2;
			numNeighbours++;
		}
		else {
			rule[7] = '0';
		}
		if (temp >= 1) {
			rule[8] = '1';
			temp = temp - 1;
			numNeighbours++;
		}
		else {
			rule[8] = '0';
		}
		
			
		//live cell with < 2 neighbours dies
		//live cell with 2 or 3 neighbours continues to live
		//live cell with > 3 neighbours dies
		//dead cell with == 3 neighbours comes to life
		
		char num = '0';
		if (alive) {
			if (numNeighbours == 2 || numNeighbours == 3) {
				num = '1';
			}
			else if (numNeighbours < 2 || numNeighbours > 3) {
				num = '0';
			}
		}
		else {
			if (numNeighbours == 3) {
				num = '1';
			}
			else {
				num = '0';
			}
		}
		
		fprintf(out, "%c%c%c%c%c%c%c%c%c %c\n", rule[0], rule[1], rule[2], rule[3], rule[4], rule[5], rule[6], rule[7], rule[8], num);
		
	}
	fclose(out);
}

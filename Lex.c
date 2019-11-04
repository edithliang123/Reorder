#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include<assert.h>
#include<string.h>
#define MAX_STRING_LENGTH 200

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	char* input[1000];
	char* temp;
	int record[1000];

	int lines = 0;

	// check command line for correct number of arguments 
	if (argc != 3) {
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// open input file for reading 
	if ((in = fopen(argv[1], "r")) == NULL) {
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// open output file for writing 
	if ((out = fopen(argv[2], "w")) == NULL) {
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	temp = calloc(MAX_STRING_LENGTH + 1, sizeof(char));
	assert(temp != NULL);

	while (fgets(temp, MAX_STRING_LENGTH, in) != NULL) {
		input[lines] = calloc(MAX_STRING_LENGTH + 1, sizeof(char));
		assert(input[lines] != NULL);
		strcpy(input[lines], temp);
		lines++;
	}
	List A = newList();
	for (int i = 0; i < lines; i++) {
		append(A, i);
		record[i] = i;
	}
	moveFront(A);
	moveNext(A);
	int count = 0;
	int count2 = 0;
	int compare = record[0];
	int cursor = index(A);
	int element = get(A);
	for (int i = 1; i < lines; i++) {
		while (count < cursor) {
			if (strcmp(input[cursor], input[compare]) < 0) {
				count2++;
			}
			count++;
			compare = record[count];
		}
		if (count2 != 0) {
			delete(A);
			moveFront(A);
			if (count2 == cursor) {
				insertBefore(A, element);
			}
			else {
				for (int x = 0; x < cursor - count2; x++) {
					moveNext(A);
				}
				insertBefore(A, element);
			}
			moveFront(A);
			for (int z = 0; z < lines; z++) {
				record[z] = get(A);
				moveNext(A);
			}
		}
		if (i != lines - 1) {
			moveFront(A);
			for (int j = 0; j < i + 1; j++) {
				moveNext(A);
			}
			count = 0;
			count2 = 0;
			compare = record[0];
			cursor = index(A);
			element = get(A);
		}
	}

	for (int ii = 0; ii < lines; ii++) {
		if (ii == 1) {
			fprintf(out, "\n");
		}
		fprintf(out, "%s", input[record[ii]]);
	}

	for (int jj = 0; jj < lines; jj++) {
		free(input[jj]);
	}
	free(temp);
	freeList(&A);
	// close input and output files 
	fclose(in);
	fclose(out);

	return 0;
}







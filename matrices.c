#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "matrices.h"

int* matrix_multiply(int* A, int* B, int* dimA, int* dimB ) {
	if (dimA[1] != dimB[0]) return NULL;
	int* Z = (int*)calloc(dimA[0] * dimB[1], sizeof(int));
	for (int a = 0; a < dimA[0]; a++) {
		for (int b = 0; b < dimB[1]; b++) {
			for (int i = 0; i < dimA[1]; i++) {
				Z[a * dimB[1] + b] += A[a*dimA[1]+i] * B[i*dimB[1]+b];
			}
		}
	}
	return Z;
}

void print2x2(int* matrix, int length, int pitch) {
	for (int i = 0; i < length / pitch; i++) {
		for (int j = 0; j < pitch; j++) {
			printf("%d ", matrix[i * pitch + j]);
		}
		printf("\n");
	}
}


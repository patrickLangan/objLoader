#include <stdio.h>
#include <stdlib.h>

struct vertex {
	float x;
	float y;
	float z;
};

struct face {
	int a;
	int b;
	int c;
};

int main (int argc, char **argv)
{
	FILE *file;
	unsigned int vertexNum;
	unsigned int faceNum;
	struct vertex *vertexArray;
	struct face *faceArray;
	unsigned int i;


	file = fopen ("out.bin", "r");

	fread (&vertexNum, sizeof(int), 1, file);
	vertexArray = malloc (vertexNum * sizeof(vertexArray[0]));
	fread (vertexArray, sizeof(vertexArray[0]), vertexNum, file);

	fread (&faceNum, sizeof(int), 1, file);
	faceArray = malloc (faceNum * sizeof(faceArray[0]));
	fread (faceArray, sizeof(faceArray[0]), faceNum, file);

	fclose (file);


	for (i = 0; i < vertexNum; i++) {
		printf ("%f, ", vertexArray[i].x);
		printf ("%f, ", vertexArray[i].y);
		printf ("%f\n", vertexArray[i].z);
	}

	for (i = 0; i < faceNum; i++) {
		printf ("%d, ", faceArray[i].a);
		printf ("%d, ", faceArray[i].b);
		printf ("%d\n", faceArray[i].c);
	}

	return 0;
}

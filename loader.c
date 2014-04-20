#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	FILE *file;
	unsigned int vertexNum;
	unsigned int faceNum;
	float *vertices;
	int *faces;
	unsigned int i;


	if (argc != 2)
		return 1;

	file = fopen (argv[1], "r");

	fread (&vertexNum, sizeof(int), 1, file);
	vertices = malloc (vertexNum * 3 * sizeof(float));
	fread (vertices, sizeof(float), vertexNum * 3, file);

	fread (&faceNum, sizeof(int), 1, file);
	faces = malloc (faceNum * 3 * sizeof(int));
	fread (faces, sizeof(int), faceNum * 3, file);

	fclose (file);


	for (i = 0; i < vertexNum; i++) {
		printf ("%f, ", vertices[(i * 3) + 0]);
		printf ("%f, ", vertices[(i * 3) + 1]);
		printf ("%f\n", vertices[(i * 3) + 2]);
	}

	for (i = 0; i < faceNum; i++) {
		printf ("%d, ", faces[(i * 3) + 0]);
		printf ("%d, ", faces[(i * 3) + 1]);
		printf ("%d\n", faces[(i * 3) + 2]);
	}

	return 0;
}

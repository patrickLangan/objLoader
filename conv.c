#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Add error checking

int main (int argc, char **argv)
{
	FILE *file;
	char line[255];
	unsigned int i = 0;
	unsigned int vertNum = 0;
	unsigned int faceNum = 0;
	float *vertices;
	int *faces;


	if (argc != 2)
		return 1;

	file = fopen (argv[1], "r");

	//Getting the number of vertices and faces
	while (fgets (line, 255, file)) {
		if (line[0] == 'v')
			vertNum += 1;
		if (line[0] == 'f')
			faceNum += 1;
	}

	vertices = malloc (vertNum * 3 * sizeof(float));
	faces = malloc (faceNum * 3 * sizeof(int));

	fseek (file, 0, SEEK_SET);


	//Reading the file into the vertex and face arrays
	while (fgets (line, 255, file)) {
		char *split;
		if (line[0] == 'v') {
			split = strtok (line, " ");
			split = strtok (NULL, " ");
			vertices[i] = atof (split);
			split = strtok (NULL, " ");
			vertices[i + 1] = atof (split);
			split = strtok (NULL, " ");
			vertices[i + 2] = atof (split);
			i += 3;
		} else if (line[0] == 'f') {
			i = 0;
			break;
		}
	}
	do {
		char *split;
		if (line[0] == 'f') {
			split = strtok (line, " ");
			split = strtok (NULL, " ");
			faces[i] = atoi (split) - 1;
			split = strtok (NULL, " ");
			faces[i + 1] = atoi (split) - 1;
			split = strtok (NULL, " ");
			faces[i + 2] = atoi (split) - 1;
			i += 3;
		}
	} while (fgets (line, 255, file));

	fclose (file);


	//Writing the vertex and face arrays to a binary file
	file = fopen ("out.bin", "w");

	fwrite (&vertNum, sizeof(int), 1, file);
	fwrite (vertices, sizeof(float), vertNum * 3, file);

	fwrite (&faceNum, sizeof(int), 1, file);
	fwrite (faces, sizeof(int), faceNum * 3, file);

	fclose (file);


	free (vertices);
	free (faces);

	return 0;
}

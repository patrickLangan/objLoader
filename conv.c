#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char line[255];
	unsigned int i = 0;
	unsigned int vertNum = 0;
	unsigned int faceNum = 0;
	struct vertex *vertices;
	struct face *faces;


	file = fopen ("test.obj", "r");

	//Getting number of vertices and faces
	while (fgets (line, 255, file)) {
		if (line[0] == 'v')
			vertNum += 1;
		if (line[0] == 'f')
			faceNum += 1;
	}

	vertices = malloc (vertNum * sizeof(vertices[0]));
	faces = malloc (faceNum * sizeof(faces[0]));

	fseek (file, 0, SEEK_SET);


	//Reading the file into the vertex and face arrays
	while (fgets (line, 255, file)) {
		char *split;
		if (line[0] == 'v') {
			split = strtok (line, " ");
			split = strtok (NULL, " ");
			vertices[i].x = atof (split);
			split = strtok (NULL, " ");
			vertices[i].y = atof (split);
			split = strtok (NULL, " ");
			vertices[i].z = atof (split);
			i++;
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
			faces[i].a = atoi (split);
			split = strtok (NULL, " ");
			faces[i].b = atoi (split);
			split = strtok (NULL, " ");
			faces[i].c = atoi (split);
			i++;
		}
	} while (fgets (line, 255, file));

	fclose (file);


	//Writing the vertex and face arrays to a binary file
	file = fopen ("out.bin", "w");

	fwrite (&vertNum, sizeof(int), 1, file);
	fwrite (vertices, sizeof(vertices[0]), vertNum, file);

	fwrite (&faceNum, sizeof(int), 1, file);
	fwrite (faces, sizeof(faces[0]), faceNum, file);

	fclose (file);


	free (vertices);
	free (faces);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
	FILE *file;
	char line[255];
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int vertexNumber = 0;
	unsigned int faceNumber = 0;
	float *vertexArray;
	int *faceArray;

	file = fopen ("test.obj", "r");

	while (fgets (line, 255, file)) {
		if (line[0] == 'v')
			vertexNumber += 1;
		if (line[0] == 'f')
			faceNumber += 1;
	}

	vertexArray = malloc (vertexNumber * 3 * sizeof(float));
	faceArray = malloc (faceNumber * 3 * sizeof(int));

	fseek (file, 0, SEEK_SET);

	while (fgets (line, 255, file)) {
		if (line[0] == 'v' || line[0] == 'f') {
			char *split;

			split = strtok (line, " ");
			split = strtok (NULL, " ");

			while (split) {
				if (line[0] == 'v') {
					vertexArray[i] = atof (split);
					i++;
				} else {
					faceArray[j] = atoi (split);
					j++;
				}
				split = strtok (NULL, " ");
			}
		}
	}

	fclose (file);

	file = fopen ("out.bin", "w");
	fwrite (vertexArray, sizeof(float), vertexNumber * 3, file);
	fclose (file);

	free (vertexArray);
	free (faceArray);

	return 0;
}

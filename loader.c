#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	FILE *file;
	unsigned int length;
	float *array;
	unsigned int i;

	file = fopen ("out.bin", "r");

	fseek (file, 0, SEEK_END);
	length = ftell (file);
	fseek (file, 0, SEEK_SET);

	array = malloc (length);

	fread (array, 1, length, file);

	fclose (file);

	for (i = 0; i < length / sizeof(float); i++)
		printf ("%f\n", array[i]);

	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_POINTS 15


typedef struct _student {
	char ime[50];
	char prezime[50];
	double points;
} Student;

int broj_redaka_file()
{
	int counter = 0;
	char buffer[MAX_LINE] = { 0 };

	FILE* fPointer = NULL;
	fPointer = fopen("students.txt", "r");
	if (!fPointer) {
		printf("File not opened!\n");
		return -1;
	}

	while (!feof(fPointer)) {
		fgets(buffer, MAX_LINE, fPointer);
		counter++;
	}

	fclose(fPointer);

	return counter;
}

int main()
{
	int i = 0, broj_redaka = 0;
	broj_redaka = broj_redaka_file();

	if (broj_redaka > 0)
	{
		FILE* fP = NULL;
		fP = fopen("students.txt", "r");
		if (!fP) {
			printf("File not opened!\n");
			return -1;
		}

		Student* stud = NULL;
		stud = (Student*)malloc(broj_redaka * sizeof(Student));
		if (stud == NULL) {
			printf("Malloc error!\n");
			return 0;
		}

		for (i = 0; i < broj_redaka; i++) {
			if (fscanf(fP, " %s %s %lf ", stud[i].ime, stud[i].prezime, &stud[i].points) != 3)
				return 0;
		}

		for (i = 0; i < broj_redaka; i++) {
			printf("%s %s %.2lf %.2lf\%\n", stud[i].ime, stud[i].prezime, stud[i].points, stud[i].points / MAX_POINTS * 100);
		}

		fclose(fP);
		free(stud);
	}

	return 0;
}

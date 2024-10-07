#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ERROR 1
#define MAX 1024
int NumberOfRows(char FileName);

int main() {
	int number_of_rows = 0;
	number_of_rows = NumberOfRows("Studenti.txt");

	return 0;
}
int NumberOfRows(const char *FileName){

	FILE* file = NULL;
	file = fopen("", "r");
	char buffer[MAX];
	if (file == NULL) {
		printf("Ne moze se otvoriti file");
		return ERROR;
	}
	while (!feof(file)) {
		fgets();
		number_of_rows++;
	}
}
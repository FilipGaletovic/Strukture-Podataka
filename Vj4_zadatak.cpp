#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

struct Polinom;
typedef struct Polinom* position;

typedef struct Polinom {
	int coeff;
	int exp;
	position next;
}polinom;

void insertAfter(position, int);
position newElement(int, int);
void readFunction(position, const char);

int main() {

	position head = (position)malloc(sizeof(polinom));
	head->next = NULL;

	return 0;
}

position newElement(int c, int e) {
	position newElement = (position)malloc(sizeof(polinom));
	if (!newElement)
		printf("Memorija nije alocirana");
	newElement->next = NULL;
	newElement->coeff = c;
	newElement->exp = e;

	return newElement;

}

void readFunction(position head, const char filename) {
	FILE* fp = fopen(filename, "r");
	int c, e, num2read;
	char buffer;
	position temp = head->next;
	fgets(buffer, MAX_LINE, filename);
	while (strlen(buffer) > 0) {
		int status = sscanf(buffer, " %d %d %n", &c, &e, &num2read, filename);
		if (status == 2) {
			position nE = newElement(c, e);
			temp->next = nE;
		}
		temp = temp->next;
		buffer + num2read;
	}
}



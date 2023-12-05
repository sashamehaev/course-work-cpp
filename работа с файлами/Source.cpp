#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#define FNAME_STUDENTS "./students.dat"
#define FNAME_BOOKS "./books.dat"
const char PR_R[] = "rb";	//������� �������� ��������� ����� �� ������
const char PR_S[] = "r+b";	//������� �������� ����� �� ������ � ������
const char PR_W[] = "wb";	//������� �������� ����� �� ������
const char PR_A[] = "ab";	//������� �������� ����� �� ����������
using namespace std;

void AddBook(const char* fileName);
void AddStudent(const char* fileName);
void ShowStudents(const char* fileName);
void ShowBooks(const char* fileName);

typedef struct {
	int id;
	char name[255];
	char surname[255];

} students;

typedef struct {
	int id;
	char name[255];

} books;

int main() {
	setlocale(LC_ALL, "ru");
	char filenameStudents[40] = FNAME_STUDENTS;
	char filenameBooks[40] = FNAME_BOOKS;
	
	int var = 0;

	for (; ;) {
		printf("  1 - �������� ���� ������\n");
		printf("  2 - �������� � ���� ������ \n");
		printf("  3 - �������� ���� ������ \n");
		printf("  4 - ������ ����� �������� \n");
		printf("  5 - ������� ����� � �������� \n");
		printf("  8 - ����� �� ���������\n");

		scanf("%i", &var);
		switch (var) {
			case 1:
				char res;

				//������� �����
				if (fopen(filenameStudents, PR_R)) {
					printf(" ���� �� ���������� ");
					printf(filenameStudents);
					printf(" ��� ������ ������.\n");
					printf(" ������ ���� � ����� ������? [Y/N] ");
					while ((res = getchar()) == '\n');
					if (res == 'Y' || res == 'y' || res == '�' || res == '�') {
						printf(" ������� ��� ������������ �����: ");
						scanf("%s", filenameStudents);
					}
				}

				if (!fopen(filenameStudents, PR_W)) {
					printf("\n ������ �������� ����� ��� ������\n");
					break;
				}

				if (fopen(filenameBooks, PR_R)) {
					printf(" ���� � ������� ");
					printf(filenameBooks);
					printf(" ��� ������ ������.\n");
					printf(" ������ ���� � ����� ������? [Y/N] ");
					while ((res = getchar()) == '\n');
					if (res == 'Y' || res == 'y' || res == '�' || res == '�') {
						printf(" ������� ��� ������������ �����: ");
						scanf("%s", filenameBooks);
					}
				}

				if (!fopen(filenameBooks, PR_W)) {
					printf("\n ������ �������� ����� ��� ������\n");
					break;
				}
		
				break;

			case 2:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					int var = 0;
					printf("\n    �������� �������: \n");
					printf("  1 - �������� \n");
					printf("  2 - ����� \n");
					printf("  3 - ��������� ����� \n");
					printf("  ������� ��� �������� ->");
					scanf("%i", &var);
					if (var == 1) {
						AddStudent(filenameStudents);
						break;
					}
					else if (var == 2) {
						AddBook(filenameBooks);
						break;
					}
					else if (var == 3) {
						break;
					}
					else break;

					break;
				}
				printf("\n ������ �������� ����� ��� ������ � ������\n");
				break;
			case 3:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					int var = 0;
					printf("\n    �������� �������: \n");
					printf("  1 - �������� \n");
					printf("  2 - ����� \n");
					printf("  3 - ��������� ����� \n");
					printf("  ������� ��� �������� ->");
					scanf("%i", &var);
					if (var == 1) {
						ShowStudents(filenameStudents);
						break;
					}
					else if (var == 2) {
						ShowBooks(filenameBooks);
						break;
					}
					else if (var == 3) {
						break;
					}
					else break;
						
					break;
				}
				printf("\n ������ �������� ����� ��� ������ � ������\n");
				break;
			/*case 4:
				if (!fopen(filenameStudents, PR_R)) {
					printf("\n ������ �������� ����� ��� ������\n");
					break;
				}
				if (!fopen(filenameResult, PR_W)) {
					printf("\n ������ �������� ����� ��� ������\n");
					break;
				}
			case 5:
				if (!fopen(filenameResult, PR_R)) {
					printf("\n ������ �������� ����� ��� ������\n");
					break;
				}*/

			case 8: return 0;

			default:
				break;
		}
	}
}

void ShowStudents(const char* fileName) {
	int i = 0;
	FILE* filenameStudents;
	filenameStudents = fopen(fileName, PR_R);
	students student;

	while (fread(&student, sizeof(student), 1, filenameStudents) > 0) {
		printf("\n|%15s|%15s|%15d|", student.surname, student.name, student.id);
	}
	printf("\n");
	for (i = 1; i <= 49; i++)
		printf("-");
	printf("\n");
	fclose(filenameStudents);
	return;
}

void ShowBooks(const char* fileName) {
	int i = 0;
	FILE* filenameBooks;
	filenameBooks = fopen(fileName, PR_R);
	books book;

	while (fread(&book, sizeof(book), 1, filenameBooks) > 0) {
		printf("\n|%15s|%15d|", book.name, book.id);
	}
	printf("\n");
	for (i = 1; i <= 33; i++)
		printf("-");
	printf("\n");
	fclose(filenameBooks);
	return;
}

void AddStudent(const char* fileName) {
	int i = 0;
	FILE* writeData;
	FILE* readData;
	char res;
	students student;
	int studentId = 0;
	
	do {
		//������� ���� �� ������
		readData = fopen(fileName, PR_R);

		//�������� ������ � �����, ����� ����� id ���������� �������
		while (fread(&student, sizeof(student), 1, readData) > 0) { 
			cout << "����� � ����" << endl;
			studentId = student.id;
			studentId++;
		}

		//������, ���� ���� ������
		if (studentId == 0) { 
			cout << "����� �� ����" << endl;
			studentId++;
			student.id = studentId;
		}
		//��������� ���� �� ������
		fclose(readData); 

		//���������� id, ��������� � �����, � ����������� ������
		student.id = studentId; 
		
		printf("\n ���? ");
		scanf("%s", student.name);  

		printf("\n �������? ");
		scanf("%s", student.surname); 

		//��������� ���� �� ������
		writeData = fopen(fileName, PR_A);

		//���������� � ���� ��������� ������
		fwrite(&student, sizeof(student), 1, writeData); 
		fclose(writeData);

		printf("\n ����������?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == '�');
	printf("\n");

	return;
}

void AddBook(const char* fileName) {
	int i = 0;
	FILE* writeData;
	FILE* readData;
	char res;
	books book;
	int bookId = 0;

	do {
		//������� ���� �� ������
		readData = fopen(fileName, PR_R);

		//�������� ������ � �����, ����� ����� id ���������� �������
		while (fread(&book, sizeof(book), 1, readData) > 0) {
			cout << "����� � ����" << endl;
			bookId = book.id;
			bookId++;
		}

		//������, ���� ���� ������
		if (bookId == 0) {
			cout << "����� �� ����" << endl;
			bookId++;
			book.id = bookId;
		}
		//��������� ���� �� ������
		fclose(readData);

		//���������� id, ��������� � �����, � ����������� ������
		book.id = bookId;

		printf("\n �������� �����? ");
		scanf("%s", book.name);

		//��������� ���� �� ������
		writeData = fopen(fileName, PR_A);

		//���������� � ���� ��������� ������
		fwrite(&book, sizeof(book), 1, writeData);
		fclose(writeData);

		printf("\n ����������?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == '�');
	printf("\n");

	return;
}

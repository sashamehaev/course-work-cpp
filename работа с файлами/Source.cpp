#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>
#define FNAME_STUDENTS "./students.dat"
#define FNAME_BOOKS "./books.dat"
const char PR_R[] = "rb";	//������� �������� ��������� ����� �� ������
const char PR_S[] = "r+b";	//������� �������� ����� �� ������ � ������
const char PR_W[] = "wb";	//������� �������� ����� �� ������
const char PR_A[] = "ab";	//������� �������� ����� �� ����������

void AddBook (const char* filenameBooks);
void AddStudent (const char* filenameStudents);
void ShowStudents (const char* filenameStudents);
void ShowBooks (const char* filenameBooks);
void ShowLibrary (const char* filenameStudents);
void DeleteBook (const char* filenameBooks);
void DeleteStudent (const char* filenameStudents);
void GetBook (const char* filenameStudents, const char* filenameBooks);
//void TakeBook (const char* filenameStudents);

typedef struct {
	int id;
	char name[255];

} books;

typedef struct {
	int id;
	char name[255];
	char surname[255];
	int booksCount;
	books book[31];

} students;

int main() {
	setlocale(LC_ALL, "ru");
	char filenameStudents[255] = FNAME_STUDENTS;
	char filenameBooks[255] = FNAME_BOOKS;
	
	int var = 0;

	while (true) {
		printf("\n  1 - �������� ���� ������");
		printf("\n  2 - �������� � ���� ������");
		printf("\n  3 - �������� ���� ������");
		printf("\n  4 - ������� ����� � ��������");
		printf("\n  6 - ������ ����� ��������");
		printf("\n  7 - ������� �����");
		printf("\n  8 - ������� ��������");
		printf("\n  9 - ����������� ����������");
		printf("\n  12 - ����� �� ���������\n");
		printf("\n ������� ��� ��������:");
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
					printf("  3 - ������ ����� \n");
					printf("  4 - ��������� ����� \n");
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
				if (fopen(filenameStudents, PR_R) && fopen(filenameBooks, PR_R)) {
					int var = 0;
					printf("\n    �������� �������: \n");
					printf("  1 - �������� \n");
					printf("  2 - ����� \n");
					printf("  4 - ��������� ����� \n");
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
					else if (var == 4) {
						break;
					}
					else break;
						
					break;
				}

				printf("\n ������ �������� ����� ��� ������ � ������\n");
				break;
			/*case 4:
				if (fopen(filenameStudents, PR_R)) {
					TakeBook(filenameStudents);
					break;
				}*/

				printf("\n ������ �������� ����� ��� ������\n");
				break;
			case 5:

				break;
			case 6:
				if (fopen(filenameStudents, PR_R) && fopen(filenameBooks, PR_R)) {
					GetBook(filenameStudents, filenameBooks);
					break;
				}

				printf("\n ������ �������� ����� ��� ������ � ������\n");
				break;
			case 7:
				if (fopen(filenameBooks, PR_R)) {
					DeleteBook(filenameBooks);
					break;
				}

				printf("\n ������ �������� ����� ��� ������\n");
				break;
			case 8:
				if (fopen(filenameStudents, PR_R)) {
					DeleteStudent(filenameStudents);
					break;
				}

				printf("\n ������ �������� ����� ��� ������\n");
				break;
			case 9:
				if (fopen(filenameStudents, PR_R)) {
					ShowLibrary(filenameStudents);
					break;
				}

				printf("\n ������ �������� ����� ��� ������\n");
				break;

			case 12: return 0;

			default:
				break;
		}
	}
}

//������� ��������� �� ����
void ShowStudents(const char* filenameStudents) {
	FILE* studentsDb = fopen(filenameStudents, PR_R);
	students student;

	//��������� ��� ������� �� ����������
	for (int i = 1; i <= 49; i++)
		printf("-");
	printf("\n|%15s|%15s|%15s|\n", "Id", "���", "�������");
	for (int i = 1; i <= 49; i++)
		printf("-");
	//������ ���������
	while (fread(&student, sizeof(student), 1, studentsDb) > 0)
		printf("\n|%15i|%15s|%15s|", student.id, student.name, student.surname);
	printf("\n");
	for (int i = 1; i <= 49; i++)
		printf("-");
	printf("\n");

	fclose(studentsDb);
	return;
}

//������� ��� ����� � ����
void ShowBooks(const char* filenameBooks) {
	FILE* booksDb = fopen(filenameBooks, PR_R);
	books book;

	//��������� ��� ������� � �������
	for (int i = 1; i <= 33; i++)
		printf("-");
	printf("\n|%15s|%15s|\n", "Id", "�������� �����");
	for (int i = 1; i <= 33; i++)
		printf("-");
	//������ ����
	while (fread(&book, sizeof(book), 1, booksDb) > 0)
		printf("\n|%15i|%15s|", book.id, book.name);
	printf("\n");
	for (int i = 1; i <= 33; i++)
		printf("-");
	printf("\n");

	fclose(booksDb);
	return;
}

//�������� �������� � ���� ������
void AddStudent(const char* filenameStudents) {
	int i = 0;
	FILE* studentsDb;
	students student;
	
	char res;
	do {
		//������� ���� �� ������
		studentsDb = fopen(filenameStudents, PR_R);

		//�������� ������ � �����, ����� ����� id ���������� �������
		int studentId = 0;
		while (fread(&student, sizeof(student), 1, studentsDb) > 0) {
			studentId = student.id;
			studentId++;
		}

		//������, ���� ���� ������
		if (studentId == 0) { 
			studentId++;
			student.id = studentId;
		}
		fclose(studentsDb);

		//�������� id, ��������� � �����, � ������
		student.id = studentId; 
		
		printf("\n ���? ");
		scanf("%s", student.name);  

		printf("\n �������? ");
		scanf("%s", student.surname); 

		studentsDb = fopen(filenameStudents, PR_A);
		student.booksCount = 0;
		//�������� � ���� ������
		fwrite(&student, sizeof(student), 1, studentsDb);
		fclose(studentsDb);

		printf("\n ����������?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == '�');

	return;
}

//�������� ����� � ���� ������
void AddBook(const char* filenameBooks) {
	FILE* writeData;
	FILE* booksDb;
	books book;

	char res;
	do {
		//������� ���� �� ������
		booksDb = fopen(filenameBooks, PR_R);

		//�������� ������ � �����, ����� ����� id ���������� �������
		int bookId = 0;
		while (fread(&book, sizeof(book), 1, booksDb) > 0) {
			bookId = book.id;
			bookId++;
		}

		//������, ���� ���� ������
		if (bookId == 0) {
			bookId++;
			book.id = bookId;
		}
		//��������� ���� �� ������
		fclose(booksDb);

		//Id, ������� ������ � �����, �������� � ������
		book.id = bookId;

		printf("\n �������� �����? ");
		scanf("%s", book.name);

		//������� ���� �� ������
		booksDb = fopen(filenameBooks, PR_A);
		//�������� � ���� ������
		fwrite(&book, sizeof(book), 1, booksDb);
		fclose(booksDb);

		printf("\n ����������?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == '�');

	return;
}

//������� ���������� ����� �� ����
void DeleteBook(const char* fileName) {
	int booksCount = 0;
	FILE* booksDb = fopen(fileName, PR_R);
	books book;

	//���������� ���� � ����
	while (fread(&book, sizeof(book), 1, booksDb) > 0)
		booksCount++;
	rewind(booksDb);

	//������ ���� �� ���� � ������
	books* booksArr = new books[booksCount];
	for (int i = 0; fread(&book, sizeof(book), 1, booksDb) > 0; i++) {
		booksArr[i].id = book.id;
		memcpy(booksArr[i].name, book.name, sizeof(book.name));
	}

	int id = 0;
	bool notFound = true;
	while (notFound) {
		printf("\n������� id �����: ");
		scanf("%i", &id);
		for (int i = 0; i < booksCount; i++) {
			if (booksArr[i].id == id) {
				notFound = false;
				break;
			}
		}
		if (notFound) {
			printf("����� �� �������\n");
			return;
		}
		else {
			printf("����� ������� �������\n");
		}
	}

	//���������� ���� ����� �������� ���������� �� 1
	booksCount--;
	//������ � ����� ������ ����, ����� ���������� � ��������
	books* newBooksArr = new books[booksCount];
	for (int i = 0; i < booksCount; i++) {
		newBooksArr[i].id = booksArr[i].id;
		memcpy(newBooksArr[i].name, booksArr[i].name, sizeof(book.name));
		if (booksArr[i].id == id) {
			for (int j = i; j < booksCount; j++) {
				newBooksArr[j].id = booksArr[j + 1].id;
				memcpy(newBooksArr[j].name, booksArr[j + 1].name, sizeof(book.name));
			}
			break;
		}
	}
	delete[] booksArr;

	//������� ����� ��� ������ � ���� ���� ����, ����� ���������� � ��������
	booksDb = fopen(fileName, PR_W);
	for (int i = 0; i < booksCount; i++)
		fwrite(&newBooksArr[i], sizeof(newBooksArr[i]), 1, booksDb);

	fclose(booksDb);
	delete[] newBooksArr;
}

//������� ����������� �������� �� ����
void DeleteStudent(const char* filenameStudents) {
	FILE* studentsDb = fopen(filenameStudents, PR_R);
	students student;

	//���������� ��������� � ����
	int studentsCount = 0;
	while (fread(&student, sizeof(student), 1, studentsDb) > 0)
		studentsCount++;
	rewind(studentsDb);

	//������ ��������� �� ���� � ������
	/*
	���������� �������� 2 �������, ������ ���, ��� �������� �������� �� 
	�������� ����� ��������� ����� �� ����� �������.
	��� ������ �������� � ������ ����������
	��� ����� ���������� ������� ����� ����� ���������� ���������.
	*/ 
	students* studentsArr = new students[studentsCount];
	for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
		studentsArr[i].id = student.id;
		memcpy(studentsArr[i].name, student.name, sizeof(student.name));
		memcpy(studentsArr[i].surname, student.surname, sizeof(student.surname));
		studentsArr[i].booksCount = student.booksCount;

		//��� ������� �������� �������� ������ ����, ������������� ���
		for (int j = 0; j < student.booksCount; j++) {
			studentsArr[i].book[j].id = student.book[j].id;
			memcpy(studentsArr[i].book[j].name, student.book[j].name, sizeof(student.book[j].name));
		}
	}

	int id = 0;
	bool notFind = true;
	while (notFind) {
		printf("\n������� id ��������: ");
		scanf("%i", &id);
		for (int i = 0; i < studentsCount; i++) {
			if (studentsArr[i].id == id) {
				notFind = false;
				printf("������� ������� ������\n");
				break;
			}
		}
		if (notFind) {
			printf("������� �� ������\n");
			return;
		}
	}

	//���������� ��������� ���������� �� 1 ����� �������� �� ����
	studentsCount--;
	//� ����� ������ �������� ���������, ����� ����������� �������� �� ����
	students* newStudentsArr = new students[studentsCount];
	for (int i = 0; i < studentsCount; i++) {
		newStudentsArr[i].id = studentsArr[i].id;
		memcpy(newStudentsArr[i].name, studentsArr[i].name, sizeof(student.name));
		memcpy(newStudentsArr[i].surname, studentsArr[i].surname, sizeof(student.surname));
		//����� ���������� ����, ������ ���������
		newStudentsArr[i].booksCount = studentsArr[i].booksCount;
		//��� ������� �������� �������� ������ ����, ������ ��
		for (int j = 0; j < studentsArr[i].booksCount; j++) {
			newStudentsArr[i].book[j].id = studentsArr[i].book[j].id;
			memcpy(newStudentsArr[i].book[j].name, studentsArr[i].book[j].name, sizeof(studentsArr[i].book[j].name));
		}

		//�������, ��� ������� ������ �������, �������� ����� �������
		if (studentsArr[i].id == id) {
			for (int j = i; j < studentsCount; j++) {
				//���������� ��������� ����� � �������, ����� �������� ���� ���������, ����� ����������� � ��������
				newStudentsArr[j].id = studentsArr[j + 1].id;
				newStudentsArr[j].booksCount = studentsArr[j + 1].booksCount;
				memcpy(newStudentsArr[j].name, studentsArr[j + 1].name, sizeof(student.name));
				memcpy(newStudentsArr[j].surname, studentsArr[j + 1].surname, sizeof(student.surname));
				for (int k = 0; k < newStudentsArr[j].booksCount; k++) {
					newStudentsArr[j].book[k].id = studentsArr[j + 1].book[k].id;
					memcpy(newStudentsArr[j].book[k].name, studentsArr[j + 1].book[k].name, sizeof(studentsArr[j + 1].book[k].name));
				}
			}
			break;
		}
	}
	delete[] studentsArr;
	fclose(studentsDb);

	//������� �����
	studentsDb = fopen(filenameStudents, PR_W);
	//������ � ���� ������ ������ ���������
	for (int i = 0; i < studentsCount; i++)
		fwrite(&newStudentsArr[i], sizeof(newStudentsArr[i]), 1, studentsDb);

	fclose(studentsDb);
	delete[] newStudentsArr;
}

void GetBook(const char* filenameStudents, const char* filenameBooks) {
	FILE* studentsDb;
	studentsDb = fopen(filenameStudents, PR_R);
	students student;

	FILE* booksDb;
	booksDb = fopen(filenameBooks, PR_R);
	books book;

	int studentsCount = 0;
	int booksCount = 0;
	//���������� ��������� �� ����
	while (fread(&student, sizeof(student), 1, studentsDb)) {
		studentsCount++;
	}
	//���������� ���� �� ����
	while (fread(&book, sizeof(book), 1, booksDb)) {
		booksCount++;
	}
	rewind(booksDb);
	rewind(studentsDb);

	//�������� � ������ �����, ���������� �� ����
	books* booksArr = new books[booksCount];
	for (int i = 0; fread(&book, sizeof(book), 1, booksDb) > 0; i++) {
		booksArr[i].id = book.id;
		memcpy(booksArr[i].name, book.name, sizeof(book.name));
	}

	//�������� � ������ ���������, ���������� �� ����
	students* studentsArr = new students[studentsCount];
	for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
		studentsArr[i].id = student.id;
		studentsArr[i].booksCount = student.booksCount;
		memcpy(studentsArr[i].name, student.name, sizeof(student.name));
		memcpy(studentsArr[i].surname, student.surname, sizeof(student.surname));
		//��� ������� �������� �������� �����, ������������� ���
		for (int j = 0; j < student.booksCount; j++) {
			studentsArr[i].book[j].id = student.book[j].id;
			memcpy(studentsArr[i].book[j].name, student.book[j].name, sizeof(student.book[j].name));
		}
	}

	int studentId = 0;
	bool studentNotFound = true;
	while (studentNotFound) {
		printf("\n������� id ��������: ");
		scanf("%i", &studentId);
		for (int i = 0; i < studentsCount; i++) {
			if (studentsArr[i].id == studentId) {
				studentNotFound = false;
				break;
			}
		}
		if (studentNotFound) {
			printf("������� �� ������\n");
			return;
		}
	}

	int bookId = 0;
	bool bookNotFound = true;
	while (bookNotFound) {
		printf("\n������� id �����: ");
		scanf("%i", &bookId);
		for (int i = 0; i < booksCount; i++) {
			if (booksArr[i].id == bookId) {
				bookNotFound = false;
				break;
			}
		}
		if (bookNotFound) {
			printf("����� �� �������\n");
			return;
		}
	}

	//�������� � ������ ��������� ����� ��� ���������� ��������
	for (int i = 0; i < studentsCount; i++) {
		if (studentId == studentsArr[i].id) {
			for (int j = 0; j < booksCount; j++) {
				if (bookId == booksArr[j].id) {
					//���������� ����, ������������� ����������� ��������
					int numberOfBooks = 0;
					numberOfBooks = studentsArr[i].booksCount;
					studentsArr[i].book[numberOfBooks].id = booksArr[j].id;
					memcpy(studentsArr[i].book[numberOfBooks].name, booksArr[j].name, sizeof(booksArr[j].name));
					studentsArr[i].booksCount = studentsArr[i].booksCount + 1;
				}
			}
		}
	}
	fclose(studentsDb);

	//�������� ��� ���������� ������ �� ����
	studentsDb = fopen(filenameStudents, PR_W);
	//������������ ��������� � ����, � ������ ����, ��� ���� ������ ����� ����������� ��������
	for (int i = 0; i < studentsCount; i++)
		fwrite(&studentsArr[i], sizeof(studentsArr[i]), 1, studentsDb);
	printf("������� ������� �����");

	delete[] booksArr;
	delete[] studentsArr;
	fclose(studentsDb);
	fclose(booksDb);
}

//������� ���� ��������� � ������ ����, ������� ����������� ������� ��������
void ShowLibrary(const char* filenameStudents) {
	int studentsCount = 0;
	FILE* studentsDb;
	studentsDb = fopen(filenameStudents, PR_R);
	students student;

	for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
		//��������� � ����������� � ��������
		printf("\n�������: \n");
		for (int j = 1; j <= 49; j++)
			printf("-");
		printf("\n|%15s|%15s|%15s|\n", "id", "���", "�������");
		for (int j = 1; j <= 49; j++)
			printf("-");
		printf("\n");
		//������ � ������� � ��������
		printf("|%15i|%15s|%15s|\n", student.id, student.name, student.surname);
		for (int j = 1; j <= 49; j++)
			printf("-");
		printf("\n\n");

		//��������� ��� ������ ����, ������� ���� �������
		printf("���� �����: \n");
		for (int j = 1; j <= 33; j++)
			printf("-");
		printf("\n|%15s|%15s|\n", "id", "name");
		for (int j = 1; j <= 33; j++)
			printf("-");
		//������ ����, ������� ���� �������
		for (int j = 0; j < student.booksCount; j++)
			printf("\n|%15i|%15s|", student.book[j].id, student.book[j].name);
		printf("\n");
		for (int j = 1; j <= 33; j++)
			printf("-");
		printf("\n\n");
	}
	
	fclose(studentsDb);
	return;
}

//void TakeBook (const char* filenameStudents) {
//	FILE* studentsDb = fopen(filenameStudents, PR_R);
//	students student;
//
//	int studentsCount = 0;
//	while (fread(&student, sizeof(student), 1, studentsDb))
//		studentsCount++;
//	rewind(studentsDb);
//
//	students* studentsArr = new students[studentsCount];
//	for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
//		studentsArr[i].id = student.id;
//		memcpy(studentsArr[i].name, student.name, sizeof(student.name));
//		memcpy(studentsArr[i].surname, student.surname, sizeof(student.surname));
//		studentsArr[i].booksCount = student.booksCount;
//		for (int j = 0; j < student.booksCount; j++) {
//			studentsArr[i].book[j].id = student.book[j].id;
//			memcpy(studentsArr[i].book[j].name, student.book[j].name, sizeof(student.book[j].name));
//		}
//	}
//
//	int studentId = 0;
//	bool studentWasFound = false;
//	while (!studentWasFound) {
//		printf("\n������� id ��������: ");
//		scanf("%i", &studentId);
//		for (int i = 0; i < studentsCount; i++) {
//			if (studentsArr[i].id == studentId) {
//				studentWasFound = true;
//				break;
//			}
//		}
//		if (!studentWasFound) {
//			printf("������� �� ������\n");
//			return;
//		}
//	}
//
//	int bookId = 0;
//	bool bookWasFound = false;
//	while (!bookWasFound) {
//		printf("\n������� id �����: ");
//		scanf("%i", &bookId);
//		for (int i = 0; i < studentsCount; i++) {
//			for (int j = 0; j < studentsArr[i].booksCount; j++) {
//				if (studentsArr[i].book[j].id == bookId) {
//					bookWasFound = true;
//					break;
//				}
//			}
//			if (!bookWasFound) {
//				printf("����� �� �������\n");
//				return;
//			}
//		}
//	}
//
//	for (int i = 0; i < studentsCount; i++) {
//		if (studentWasFound) {
//			if (bookWasFound) {
//				for (int j = 0; j < studentsArr[i].booksCount; j++) {
//					studentsArr[i].book[j].id = s
//				}
//			}
//			else break;
//		}
//		else break;
//	}
//
//	fclose(studentsDb);
//	return;
//}
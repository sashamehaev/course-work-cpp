#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>
#define FNAME_STUDENTS "./students.dat"
#define FNAME_BOOKS "./books.dat"
#define FNAME_LIBRARY "./library.dat"
const char PR_R[] = "rb";	//признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";	//признак открытия файла на чтение и запись
const char PR_W[] = "wb";	//признак открытия файла на запись
const char PR_A[] = "ab";	//признак открытия файла на добавление

void AddBook(const char* fileName);
void AddStudent(const char* fileName);
void ShowStudents(const char* fileName);
void ShowBooks(const char* fileName);
//void ShowLibrary(const char* fileName);
void FindStudent(const char* fileName);
void FindBook(const char* fileName);
void DeleteBook(const char* fileName);
void DeleteStudent(const char* fileName);
void GetBook(const char* filenameStudents, const char* filenameBooks, const char* filenameLibrary);

typedef struct {
	int id;
	char name[255];

} books;

typedef struct {
	int id;
	char name[255];
	char surname[255];
	books book[31];
	int numberOfBooks;

} students;

//typedef struct {
//	int studentId;
//	int bookId;
//	char studentName[255];
//	char studentSurname[255];
//	char bookName[255];
//
//} library;

int main() {
	setlocale(LC_ALL, "ru");
	char filenameStudents[255] = FNAME_STUDENTS;
	char filenameBooks[255] = FNAME_BOOKS;
	char filenameLibrary[255] = FNAME_LIBRARY;
	
	int var = 0;

	for (; ;) {
		printf("\n  1 - Создание базы данных");
		printf("\n  2 - Записать в базу данных");
		printf("\n  3 - Просмотр базы данных");
		printf("\n  4 - Найти студента");
		printf("\n  5 - Найти книгу");
		printf("\n  6 - Выдать книгу студенту");
		printf("\n  7 - Удалить книгу");
		printf("\n  8 - Удалить студента");
		printf("\n  12 - Выход из программы\n");
		printf("\n Введите вид действия:");
		scanf("%i", &var);
		switch (var) {
			case 1:
				char res;

				//Создаем файлы
				if (fopen(filenameStudents, PR_R)) {
					printf(" Файл со студентами ");
					printf(filenameStudents);
					printf(" был создан раньше.\n");
					printf(" Создаём файл с новым именем? [Y/N] ");
					while ((res = getchar()) == '\n');
					if (res == 'Y' || res == 'y' || res == 'Н' || res == 'н') {
						printf(" Задайте имя создаваемого файла: ");
						scanf("%s", filenameStudents);
					}
				}

				if (!fopen(filenameStudents, PR_W)) {
					printf("\n Ошибка открытия файла для записи\n");
					break;
				}

				if (fopen(filenameBooks, PR_R)) {
					printf(" Файл с книгами ");
					printf(filenameBooks);
					printf(" был создан раньше.\n");
					printf(" Создаём файл с новым именем? [Y/N] ");
					while ((res = getchar()) == '\n');
					if (res == 'Y' || res == 'y' || res == 'Н' || res == 'н') {
						printf(" Задайте имя создаваемого файла: ");
						scanf("%s", filenameBooks);
					}
				}

				if (!fopen(filenameBooks, PR_W)) {
					printf("\n Ошибка открытия файла для записи\n");
					break;
				}

				if (fopen(filenameLibrary, PR_R)) {
					printf(" Файл с книгами ");
					printf(filenameLibrary);
					printf(" был создан раньше.\n");
					printf(" Создаём файл с новым именем? [Y/N] ");
					while ((res = getchar()) == '\n');
					if (res == 'Y' || res == 'y' || res == 'Н' || res == 'н') {
						printf(" Задайте имя создаваемого файла: ");
						scanf("%s", filenameLibrary);
					}
				}

				if (!fopen(filenameLibrary, PR_W)) {
					printf("\n Ошибка открытия файла для записи\n");
					break;
				}
		
				break;

			case 2:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					int var = 0;
					printf("\n    Выберите таблицу: \n");
					printf("  1 - Студенты \n");
					printf("  2 - Книги \n");
					printf("  3 - Выдать книгу \n");
					printf("  4 - Вернуться назад \n");
					printf("  Введите вид действия ->");
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
						//GetBook(filenameStudents, filenameBooks, filenameLibrary);
						break;
					}
					else break;

					break;
				}
				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			case 3:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					int var = 0;
					printf("\n    Выберите таблицу: \n");
					printf("  1 - Студенты \n");
					printf("  2 - Книги \n");
					printf("  3 - Библиотека \n");
					printf("  4 - Вернуться назад \n");
					printf("  Введите вид действия ->");
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
						//ShowLibrary(filenameLibrary);
						break;
					}
					else if (var == 4) {
						break;
					}
					else break;
						
					break;
				}
				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			case 4:
				if (fopen(filenameStudents, PR_R)) {
					FindStudent(filenameStudents);
					break;
				}

				printf("\n Ошибка открытия файла для чтения\n");
				break;
			case 5:
				if (fopen(filenameBooks, PR_R)) {
					FindBook(filenameBooks);
					break;
				}

				printf("\n Ошибка открытия файла для чтения\n");
				break;
			case 6:
				if (fopen(filenameStudents, PR_R) && fopen(filenameBooks, PR_R)) {
					GetBook(filenameStudents, filenameBooks, filenameLibrary);
					break;
				}

				printf("\n Ошибка открытия файла для чтения\n");
				break;
			case 7:
				if (fopen(filenameBooks, PR_R)) {
					DeleteBook(filenameBooks);
					break;
				}

				printf("\n Ошибка открытия файла для чтения\n");
				break;
			case 8:
				if (fopen(filenameStudents, PR_R)) {
					DeleteStudent(filenameStudents);
					break;
				}

				printf("\n Ошибка открытия файла для чтения\n");
				break;

			case 12: return 0;

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
	for (i = 1; i <= 49; i++)
		printf("-");
	printf("\n|%15s|%15s|%15s|\n", "Фамилия", "Имя", "id");
	for (i = 1; i <= 49; i++)
		printf("-");
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
	for (i = 1; i <= 33; i++)
		printf("-");
	printf("\n|%15s|%15s|\n", "name", "id");
	for (i = 1; i <= 33; i++)
		printf("-");
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

//void ShowLibrary(const char* fileName) {
//	int i = 0;
//	FILE* filenameLibrary;
//	filenameLibrary = fopen(fileName, PR_R);
//	library studentLibrary;
//
//	while (fread(&studentLibrary, sizeof(studentLibrary), 1, filenameLibrary) > 0) {
//		printf("\n|%15d|%15s|%15s|%15d|%15s|", studentLibrary.studentId, studentLibrary.studentName, studentLibrary.studentSurname, studentLibrary.bookId, studentLibrary.bookName);
//	}
//	printf("\n");
//	for (i = 1; i <= 33; i++)
//		printf("-");
//	printf("\n");
//	fclose(filenameLibrary);
//	return;
//}

void AddStudent(const char* fileName) {
	int i = 0;
	FILE* writeData;
	FILE* readData;
	char res;
	students student;
	int studentId = 0;
	
	do {
		//Открыть файл на чтение
		readData = fopen(fileName, PR_R);

		//пройтись циклом в файле, чтобы найти id последнего объекта
		while (fread(&student, sizeof(student), 1, readData) > 0) { 
			studentId = student.id;
			studentId++;
		}

		//Случай, если файл пустой
		if (studentId == 0) { 
			studentId++;
			student.id = studentId;
		}
		//Закрываем файл на чтение
		fclose(readData); 

		//записываем id, найденный в файле, в создаваемый обЪект
		student.id = studentId; 
		
		printf("\n Имя? ");
		scanf("%s", student.name);  

		printf("\n Фамилия? ");
		scanf("%s", student.surname); 

		//Открываем файл на запись
		writeData = fopen(fileName, PR_A);
		student.numberOfBooks = 0;
		//записываем в файл созданный объект
		fwrite(&student, sizeof(student), 1, writeData); 
		fclose(writeData);

		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');

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
		//Открыть файл на чтение
		readData = fopen(fileName, PR_R);

		//пройтись циклом в файле, чтобы найти id последнего объекта
		while (fread(&book, sizeof(book), 1, readData) > 0) {
			bookId = book.id;
			bookId++;
		}

		//Случай, если файл пустой
		if (bookId == 0) {
			bookId++;
			book.id = bookId;
		}
		//Закрываем файл на чтение
		fclose(readData);

		//Id, который нашли в файле, записываем в создаваемый объект
		book.id = bookId;

		printf("\n Название книги? ");
		scanf("%s", book.name);

		//Открыть файл на запись
		writeData = fopen(fileName, PR_A);

		//Записать в файл созданный объект
		fwrite(&book, sizeof(book), 1, writeData);
		fclose(writeData);

		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');

	return;
}

void FindStudent(const char* fileName) {
	int i = 0;
	int id = 0;
	FILE* readData;
	readData = fopen(fileName, PR_R);
	students student;

	printf("Введите id студента: ");
	scanf("%i", &id);

	while (fread(&student, sizeof(student), 1, readData) > 0) {
		if (id == student.id) {
			printf("\n|%15s|%15s|", student.name, student.surname);
		}
	}
	printf("\n");
	for (i = 1; i <= 33; i++)
		printf("-");
	printf("\n");
	fclose(readData);

	return;
}

void FindBook(const char* fileName) {
	int i = 0;
	int id = 0;
	FILE* readData;
	readData = fopen(fileName, PR_R);
	books book;

	printf("Введите id книги: ");
	scanf("%i", &id);

	while (fread(&book, sizeof(book), 1, readData) > 0) {
		if (id == book.id) {
			printf("\n|%15s|", book.name);
		}
	}
	printf("\n");
	for (i = 1; i <= 17; i++)
		printf("-");
	printf("\n");
	fclose(readData);

	return;
}

void GetBook(const char* filenameStudents, const char* filenameBooks, const char* filenameLibrary) {
	FILE* studentsDb;
	studentsDb = fopen(filenameStudents, PR_R);
	students student;

	FILE* booksDb;
	booksDb = fopen(filenameBooks, PR_R);
	books book;

	int studentsCount = 0;
	int booksCount = 0;

	while (fread(&student, sizeof(student), 1, studentsDb)) {
		studentsCount++;
	}
	while (fread(&book, sizeof(book), 1, booksDb)) {
		booksCount++;
	}
	rewind(booksDb);
	rewind(studentsDb);

	students* studentsArr = new students[studentsCount];
	for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
		studentsArr[i].id = student.id;
		student.numberOfBooks;
		studentsArr[i].numberOfBooks++;
		memcpy(studentsArr[i].name, student.name, sizeof(student.name));
		memcpy(studentsArr[i].surname, student.surname, sizeof(student.surname));
	}

	books* booksArr = new books[booksCount];
	for (int i = 0; fread(&book, sizeof(book), 1, booksDb) > 0; i++) {
		booksArr[i].id = book.id;
		memcpy(booksArr[i].name, book.name, sizeof(book.name));
	}

	delete[] booksArr;
	delete[] studentsArr;

	fclose(studentsDb);
	fclose(booksDb);
}

void DeleteBook(const char* fileName) {
	int id = 0;
	int size = 0;
	FILE* booksDb = fopen(fileName, PR_R);
	books book;

	while (fread(&book, sizeof(book), 1, booksDb) > 0) {
		size++;
	}
	rewind(booksDb);

	books* arr = new books[size];
	for (int i = 0; fread(&book, sizeof(book), 1, booksDb) > 0; i++) {
		arr[i].id = book.id;
		memcpy(arr[i].name, book.name, sizeof(book.name));
	}

	bool notFind = true;
	while (notFind) {
		printf("\nВведите id книги: ");
		scanf("%i", &id);
		for (int i = 0; i < size; i++) {
			if (arr[i].id == id) {
				notFind = false;
				break;
			}
		}
		if (notFind) {
			printf("Книга не найдена\n");
		}
		else {
			printf("Книга успешно удалена\n");
		}
	}

	size--;
	books* newArr = new books[size];
	for (int i = 0; i < size; i++) {
		newArr[i].id = arr[i].id;
		memcpy(newArr[i].name, arr[i].name, sizeof(book.name));
		if (arr[i].id == id) {
			for (int j = i; j < size; j++) {
				newArr[j].id = arr[j + 1].id;
				memcpy(newArr[j].name, arr[j + 1].name, sizeof(book.name));
			}
			break;
		}
	}
	delete[] arr;
	arr = newArr;
	fclose(booksDb);

	booksDb = fopen(fileName, PR_W);
	for (int i = 0; i < size; i++) {
		fwrite(&arr[i], sizeof(arr[i]), 1, booksDb);
	}

	fclose(booksDb);
	delete[] arr;
}

void DeleteStudent(const char* fileName) {
	int id = 0;
	int size = 0;
	FILE* studentsDb = fopen(fileName, PR_R);
	students student;

	while (fread(&student, sizeof(student), 1, studentsDb) > 0) {
		size++;
	}
	rewind(studentsDb);

	students* arr = new students[size];
	for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
		arr[i].id = student.id;
		memcpy(arr[i].name, student.name, sizeof(student.name));
		memcpy(arr[i].surname, student.surname, sizeof(student.surname));
	}

	bool notFind = true;
	while (notFind) {
		printf("\nВведите id студента: ");
		scanf("%i", &id);
		for (int i = 0; i < size; i++) {
			if (arr[i].id == id) {
				notFind = false;
				break;
			}
		}
		if (notFind) {
			printf("Студент не найден\n");
		}
		else {
			printf("Студент успешно удален\n");
		}
	}

	size--;
	students* newArr = new students[size];
	for (int i = 0; i < size; i++) {
		newArr[i].id = arr[i].id;
		memcpy(newArr[i].name, arr[i].name, sizeof(student.name));
		memcpy(newArr[i].surname, arr[i].surname, sizeof(student.surname));
		if (arr[i].id == id) {
			for (int j = i; j < size; j++) {
				newArr[j].id = arr[j + 1].id;
				memcpy(newArr[j].name, arr[j + 1].name, sizeof(student.name));
				memcpy(newArr[j].surname, arr[j + 1].surname, sizeof(student.surname));
			}
			break;
		}
	}
	delete[] arr;
	arr = newArr;
	fclose(studentsDb);

	studentsDb = fopen(fileName, PR_W);
	for (int i = 0; i < size; i++) {
		fwrite(&arr[i], sizeof(arr[i]), 1, studentsDb);
	}

	fclose(studentsDb);
	delete[] arr;
}

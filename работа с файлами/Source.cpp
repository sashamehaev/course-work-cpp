#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#define FNAME_STUDENTS "./students.dat"
#define FNAME_BOOKS "./books.dat"
#define FNAME_LIBRARY "./library.dat"
const char PR_R[] = "rb";	//признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";	//признак открытия файла на чтение и запись
const char PR_W[] = "wb";	//признак открытия файла на запись
const char PR_A[] = "ab";	//признак открытия файла на добавление
using namespace std;

void AddBook(const char* fileName);
void AddStudent(const char* fileName);
void ShowStudents(const char* fileName);
void ShowBooks(const char* fileName);
void ShowLibrary(const char* fileName);
void FindStudent(const char* fileName);
void FindBook(const char* fileName);
void DeleteBook(const char* fileName);
void GetBook(const char* filenameStudents, const char* filenameBooks, const char* filenameLibrary);

typedef struct {
	int id;
	char name[255];
	char surname[255];

} students;

typedef struct {
	int id;
	char name[255];

} books;

typedef struct {
	int studentId;
	int bookId;
	char studentName[255];
	char studentSurname[255];
	char bookName[255];

} library;

int main() {
	setlocale(LC_ALL, "ru");
	char filenameStudents[255] = FNAME_STUDENTS;
	char filenameBooks[255] = FNAME_BOOKS;
	char filenameLibrary[255] = FNAME_LIBRARY;
	
	int var = 0;

	for (; ;) {
		printf("  1 - Создание базы данных\n");
		printf("  2 - Записать в базу данных \n");
		printf("  3 - Просмотр базы данных \n");
		printf("  4 - Найти студента \n");
		printf("  5 - Найти книгу \n");
		printf("  6 - Выдать книгу студенту \n");
		printf("  7 - Удалить книгу \n");
		printf("  8 - Выход из программы\n");

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
						GetBook(filenameStudents, filenameBooks, filenameLibrary);
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
						ShowLibrary(filenameLibrary);
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

void ShowLibrary(const char* fileName) {
	int i = 0;
	FILE* filenameLibrary;
	filenameLibrary = fopen(fileName, PR_R);
	library studentLibrary;

	while (fread(&studentLibrary, sizeof(studentLibrary), 1, filenameLibrary) > 0) {
		printf("\n|%15d|%15s|%15s|%15d|%15s|", studentLibrary.studentId, studentLibrary.studentName, studentLibrary.studentSurname, studentLibrary.bookId, studentLibrary.bookName);
	}
	printf("\n");
	for (i = 1; i <= 33; i++)
		printf("-");
	printf("\n");
	fclose(filenameLibrary);
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
		//Открыть файл на чтение
		readData = fopen(fileName, PR_R);

		//пройтись циклом в файле, чтобы найти id последнего объекта
		while (fread(&student, sizeof(student), 1, readData) > 0) { 
			cout << "зашли в цикл" << endl;
			studentId = student.id;
			studentId++;
		}

		//Случай, если файл пустой
		if (studentId == 0) { 
			cout << "зашли не туда" << endl;
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

		//записываем в файл созданный объект
		fwrite(&student, sizeof(student), 1, writeData); 
		fclose(writeData);

		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');
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
		//Открыть файл на чтение
		readData = fopen(fileName, PR_R);

		//пройтись циклом в файле, чтобы найти id последнего объекта
		while (fread(&book, sizeof(book), 1, readData) > 0) {
			cout << "зашли в цикл" << endl;
			bookId = book.id;
			bookId++;
		}

		//Случай, если файл пустой
		if (bookId == 0) {
			cout << "зашли не туда" << endl;
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
	printf("\n");

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
	string studentSurname;
	string bookName;
	int bookId = 0;
	int studentId = 0;
	int i = 0;

	FILE* studentsDb;
	studentsDb = fopen(filenameStudents, PR_R);
	students student;

	FILE* booksDb;
	booksDb = fopen(filenameBooks, PR_R);
	books book;

	FILE* libraryDb;
	libraryDb = fopen(filenameLibrary, PR_A);
	library studentBooks;

	printf("Введите id студента: ");
	scanf("%i", &studentId);

	while (fread(&student, sizeof(student), 1, studentsDb) > 0) {
		if (studentId == student.id) {
			studentBooks.studentId = student.id;
			memcpy(studentBooks.studentName, student.name, sizeof(student.name));
			memcpy(studentBooks.studentSurname, student.surname, sizeof(student.surname));
		}
	}

	printf("Введите id книги: ");
	scanf("%i", &bookId);

	while (fread(&book, sizeof(book), 1, booksDb) > 0) {
		if (bookId == book.id) {
			studentBooks.bookId = book.id;
			/*memcpy(studentBooks.bookName, book.name, sizeof(book.name));*/
		}
	}

	fwrite(&studentBooks, sizeof(studentBooks), 1, libraryDb);

	fclose(studentsDb);
	fclose(booksDb);
	fclose(libraryDb);
}

void DeleteBook(const char* fileName) {
	int id = 0;
	FILE* readData = fopen(fileName, PR_R);
	books book;
	int size = 0;
	while (fread(&book, sizeof(book), 1, readData) > 0) {
		size++;
	}

	books* arr = new books[size];
	rewind(readData);

	for (int i = 0; fread(&book, sizeof(book), 1, readData) > 0; i++) {
		arr[i].id = book.id;
		memcpy(arr[i].name, book.name, sizeof(book.name));
	}

	for (int i = 0; i < size; i++) {
		printf("\n|%15d|%15s|", arr[i].id, arr[i].name);
	}

	delete[] arr;

	///*printf("Введите id книги: ");
	//scanf("%i", &id);*/

	//while (fread(&book, sizeof(book), 1, readData) > 0) {
	//	
	//	arr[i].id = book.id;
	//	int sizeArr = strlen(arr[i].name);
	//	//memcpy(arr[i].name, book.name, sizeof(book.name));
	//	cout << typeid(arr[i].name).name() << endl;
	//	i++;
	//}

	//int sizeArr = sizeof(arr);
	//int sizeStruct = sizeof(books);
	//int sizeBook = sizeof(book);
	//int sizeBookName = sizeof(book.name);


	//for (int j = 0; j < size; j++) {
	//	printf("\n|%15d|%15s|", arr[j].id, arr[j].name);
	//}

	////rewind(readData);

	///*while (fread(&book, sizeof(book), 1, readData) > 0) {
	//	arr[i].id = book.id;
	//	memcpy(arr[i].name, book.name, sizeof(book.name));
	//	i++;
	//}*/

	//int index = 2;
	//delete[] arr;
	//size--;
	//books* newArr = new books[size];
	////i = 0;

	//delete[] newArr;
	/*readData = fopen(fileName, PR_R);
	while (fread(&book, sizeof(book), 1, readData) > 0) {
		newArr[i].id = arr[i].id;
		memcpy(newArr[i].name, book.name, sizeof(book.name));
		i++;

		if (i == index) {
			for (int j = index; j < size; j++) {
				newArr[j].id = arr[j + 1].id;
				memcpy(newArr[j].name, arr[j + 1].name, sizeof(book.name));

			}
			break;
		}
	}
	fclose(readData)*/;

	/*for (int i = 0; i < size; i++) {
		newArr[i].id = arr[i].id;
		memcpy(newArr[i].name, book.name, sizeof(book.name));

		if (i == index) {
			for (int j = index; j < size; j++) {
				newArr[j].id = arr[j + 1].id;
				memcpy(newArr[j].name, arr[j+1].name, sizeof(book.name));

			}
			break;
		}
	}*/

	/*delete[] arr;
	arr = newArr;

	for (int j = 0; j < size; j++) {
		cout << arr[j].id << endl;
		cout << arr[j].name << endl;
	}

	delete[] arr;*/
	fclose(readData);

	return;
}

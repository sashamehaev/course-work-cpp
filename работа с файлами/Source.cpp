#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>
#define FNAME_STUDENTS "./students.dat"
#define FNAME_BOOKS "./books.dat"
const char PR_R[] = "rb";	//признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";	//признак открытия файла на чтение и запись
const char PR_W[] = "wb";	//признак открытия файла на запись
const char PR_A[] = "ab";	//признак открытия файла на добавление

void AddBook(const char* filenameBooks);
void AddStudent(const char* filenameStudents);
void ShowStudents(const char* filenameStudents);
void ShowBooks(const char* filenameBooks);
void ShowLibrary(const char* filenameStudents);
void DeleteBook(const char* filenameBooks);
void DeleteStudent(const char* filenameStudents);
void GetBook(const char* filenameStudents, const char* filenameBooks);
void TakeBook(const char* filenameStudents);

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
	
	while (true) {
		printf("\n  1 - Записать в базу данных");
		printf("\n  2 - Просмотреть базу данных");
		printf("\n  3 - Удалить из базы данных");
		printf("\n  4 - Библиотека");
		printf("\n  11 - Создание базы данных");
		printf("\n  12 - Выход из программы\n");
		printf("\n Введите номер действия:");
		int var = 0;
		scanf("%i", &var);
		switch (var) {
			case 1:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					bool falseAnswer = false;
					do {
						printf("\n\tВыберите таблицу:\n");
						printf("1 - Студенты\n");
						printf("2 - Книги\n");
						printf("3 - Вернуться назад\n");
						printf("\nВведите вид действия ->");
						int var = 0;
						scanf("%i", &var);
						if (var == 1) {
							AddStudent(filenameStudents);
							break;
						}
						else if (var == 2) {
							AddBook(filenameBooks);
							break;
						}
						else if (var == 3) break;
						else {
							printf("\nОшибка! Неверный вариант ответа\n");
							falseAnswer = true;
						}
					} while (falseAnswer);
					break;
				}

				printf("\nОшибка открытия файла для записи\n");
				break;
			case 2:
				if (fopen(filenameStudents, PR_R) && fopen(filenameBooks, PR_R)) {
					int var = 0;
					bool falseAnswer = false;
					do {
						printf("\n\tВыберите таблицу:\n");
						printf("1 - Студенты\n");
						printf("2 - Книги\n");
						printf("3 - Вернуться назад\n");
						printf("\nВведите вид действия ->");
						scanf("%i", &var);
						if (var == 1) {
							ShowStudents(filenameStudents);
							break;
						}
						else if (var == 2) {
							ShowBooks(filenameBooks);
							break;
						}
						else if (var == 3) break;
						else {
							printf("\nОшибка! Неверный вариант ответа\n");
							falseAnswer = true;
						}
					} while (falseAnswer);
					break;
				}

				printf("\nОшибка открытия файла для чтения\n");
				break;
			case 3:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					int var = 0;
					bool falseAnswer = false;
					do {
						printf("\n\tВыберите таблицу:\n");
						printf("1 - Студенты\n");
						printf("2 - Книги\n");
						printf("3 - Вернуться назад\n");
						printf("\nВведите вид действия ->");
						scanf("%i", &var);
						if (var == 1) {
							DeleteStudent(filenameStudents);
							break;
						}
						else if (var == 2) {
							DeleteBook(filenameBooks);
							break;
						}
						else if (var == 3) break;
						else {
							printf("\nОшибка! Неверный вариант ответа\n");
							falseAnswer = true;
						}
					} while (falseAnswer);
					break;
				}

				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			case 4:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					int var = 0;
					bool falseAnswer = false;
					do {
						printf("\n\tВыберите действие:\n");
						printf("1 - Выдать книгу студенту\n");
						printf("2 - Забрать книгу у студента\n");
						printf("3 - Просмотреть библиотеку\n");
						printf("\nВведите вид действия ->");
						scanf("%i", &var);
						if (var == 1) {
							GetBook(filenameStudents, filenameBooks);
							break;
						}
						else if (var == 2) {
							TakeBook(filenameStudents);
							break;
						}
						else if (var == 3) {
							ShowLibrary(filenameStudents);
							break;
						}	
						else {
							printf("\nОшибка! Неверный вариант ответа\n");
							falseAnswer = true;
						}
					} while (falseAnswer);
					break;
				}

				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			case 11:
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

				break;
			case 12: return 0;

			default:
				break;
		}
	}
}

//Вывести всех студентов в базы
void ShowStudents(const char* filenameStudents) {
	FILE* studentsDb = fopen(filenameStudents, PR_R);
	students student;

	//Заголовок для таблицы со студентами
	for (int i = 1; i <= 49; i++)
		printf("-");
	printf("\n|%15s|%15s|%15s|\n", "Id", "Имя", "Фамилия");
	for (int i = 1; i <= 49; i++)
		printf("-");

	//Список студентов
	while (fread(&student, sizeof(student), 1, studentsDb) > 0)
		printf("\n|%15i|%15s|%15s|", student.id, student.name, student.surname);
	printf("\n");
	for (int i = 1; i <= 49; i++)
		printf("-");
	printf("\n");

	fclose(studentsDb);
	return;
}

//Вывести все книги в базе
void ShowBooks(const char* filenameBooks) {
	FILE* booksDb = fopen(filenameBooks, PR_R);
	books book;

	//Заголовок для таблицы с книгами
	for (int i = 1; i <= 33; i++)
		printf("-");
	printf("\n|%15s|%15s|\n", "Id", "Название книги");
	for (int i = 1; i <= 33; i++)
		printf("-");

	//Список книг
	while (fread(&book, sizeof(book), 1, booksDb) > 0)
		printf("\n|%15i|%15s|", book.id, book.name);
	printf("\n");
	for (int i = 1; i <= 33; i++)
		printf("-");
	printf("\n");

	fclose(booksDb);
	return;
}

//Записать студента в базу данных
void AddStudent(const char* filenameStudents) {
	students student;
	
	char res;
	do {
		//Открыть файл на чтение
		FILE* studentsDb = fopen(filenameStudents, PR_R);

		int studentId = 0;
		//Пройтись циклом в файле, чтобы найти id последнего студента
		while (fread(&student, sizeof(student), 1, studentsDb) > 0) {
			studentId = student.id;
			studentId++;
		}

		//Если в базе еще нет студентов, для первого студента id будет равен 1
		if (studentId == 0) { 
			studentId++;
		}
		fclose(studentsDb);

		student.id = studentId; 
		printf("\n Имя? ");
		scanf("%s", student.name);  
		printf("\n Фамилия? ");
		scanf("%s", student.surname); 
		//При добавлении студента в базу данных, у него нет книг
		student.booksCount = 0;

		//Запись студента в базу
		studentsDb = fopen(filenameStudents, PR_A);
		fwrite(&student, sizeof(student), 1, studentsDb);
		fclose(studentsDb);

		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');

	return;
}

//Записать книгу в базу данных
void AddBook(const char* filenameBooks) {
	books book;

	char res;
	do {
		//Открыть файл на чтение
		FILE* booksDb = fopen(filenameBooks, PR_R);

		//Пройтись циклом в файле, чтобы найти id последней книги
		int bookId = 0;
		while (fread(&book, sizeof(book), 1, booksDb) > 0) {
			bookId = book.id;
			bookId++;
		}

		//Если в базе нет книг, id первой книги равен 1
		if (bookId == 0)
			bookId++;
		fclose(booksDb);

		book.id = bookId;
		printf("\n Название книги? ");
		scanf("%s", book.name);

		//Записать в файл объект
		booksDb = fopen(filenameBooks, PR_A);
		fwrite(&book, sizeof(book), 1, booksDb);
		fclose(booksDb);

		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');

	return;
}

//Удалить конкретную книгу из базы
void DeleteBook(const char* fileName) {
	books book;

	char res;
	do {
		FILE* booksDb = fopen(fileName, PR_R);
		//Количество книг в базе
		int booksCount = 0;
		while (fread(&book, sizeof(book), 1, booksDb) > 0)
			booksCount++;
		rewind(booksDb);

		//Запись книг из базы в массив
		books* booksArr = new books[booksCount];
		for (int i = 0; fread(&book, sizeof(book), 1, booksDb) > 0; i++) {
			booksArr[i].id = book.id;
			memcpy(booksArr[i].name, book.name, sizeof(book.name));
		}

		int id = 0;
		bool bookWasFound = false;
		while (!bookWasFound) {
			printf("\nВведите id книги: ");
			scanf("%i", &id);
			for (int i = 0; i < booksCount; i++) {
				if (booksArr[i].id == id) {
					bookWasFound = true;
					break;
				}
			}
			if (!bookWasFound) {
				printf("Книга не найдена\n");
				return;
			}
			else {
				printf("Книга успешно удалена\n");
			}
		}

		//Количество книг после удаления уменьшится на 1
		booksCount--;
		//Запись в новый массив книг, кроме подлежащей к удалению
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

		//Очистка файла для записи в него всех книг, кроме подлежащей к удалению
		booksDb = fopen(fileName, PR_W);
		for (int i = 0; i < booksCount; i++)
			fwrite(&newBooksArr[i], sizeof(newBooksArr[i]), 1, booksDb);

		delete[] newBooksArr;
		fclose(booksDb);
		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');

	return;
}

//Удалить конкретного студента из базы
void DeleteStudent(const char* filenameStudents) {
	students student;

	char res;
	do {
		FILE* studentsDb = fopen(filenameStudents, PR_R);
		//Количество студентов в базе
		int studentsCount = 0;
		while (fread(&student, sizeof(student), 1, studentsDb) > 0)
			studentsCount++;
		rewind(studentsDb);

		//Запись студентов из базы в массив 
		students* studentsArr = new students[studentsCount];
		for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
			studentsArr[i].id = student.id;
			memcpy(studentsArr[i].name, student.name, sizeof(student.name));
			memcpy(studentsArr[i].surname, student.surname, sizeof(student.surname));
			studentsArr[i].booksCount = student.booksCount;

			//Для каждого студента записать список книг, принадлежащих ему
			for (int j = 0; j < student.booksCount; j++) {
				studentsArr[i].book[j].id = student.book[j].id;
				memcpy(studentsArr[i].book[j].name, student.book[j].name, sizeof(student.book[j].name));
			}
		}
		
		int id = 0;
		bool studentWasFound = false;
		while (!studentWasFound) {
			printf("\nВведите id студента: ");
			scanf("%i", &id);
			for (int i = 0; i < studentsCount; i++) {
				if (studentsArr[i].id == id) {
					studentWasFound = true;
					printf("Студент успешно удален\n");
					break;
				}
			}
			if (!studentWasFound) {
				printf("Студент не найден\n");
				return;
			}
		}

		//Количество студентов уменьшится на 1 после удаления из базы
		studentsCount--;
		//В новый массив записать студентов, кроме подлежащего удалению из базы
		students* newStudentsArr = new students[studentsCount];
		for (int i = 0; i < studentsCount; i++) {
			newStudentsArr[i].id = studentsArr[i].id;
			memcpy(newStudentsArr[i].name, studentsArr[i].name, sizeof(student.name));
			memcpy(newStudentsArr[i].surname, studentsArr[i].surname, sizeof(student.surname));
			//Найти количество книг, взятых студентом
			newStudentsArr[i].booksCount = studentsArr[i].booksCount;
			//Для каждого студента записать список книг, взятых им
			for (int j = 0; j < studentsArr[i].booksCount; j++) {
				newStudentsArr[i].book[j].id = studentsArr[i].book[j].id;
				memcpy(newStudentsArr[i].book[j].name, studentsArr[i].book[j].name, sizeof(studentsArr[i].book[j].name));
			}

			//Условие, при которым найден студент, которого нужно удалить
			if (newStudentsArr[i].id == id) {
				for (int j = i; j < studentsCount; j++) {
					//Необходимо совершить сдвиг в массиве, чтобы записать всех студентов, кроме подлежащего к удалению
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

		//Очистка файла
		studentsDb = fopen(filenameStudents, PR_W);
		//Запись в файл нового списка студентов
		for (int i = 0; i < studentsCount; i++)
			fwrite(&newStudentsArr[i], sizeof(newStudentsArr[i]), 1, studentsDb);

		fclose(studentsDb);
		delete[] newStudentsArr;
		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');

	return;
}

void GetBook(const char* filenameStudents, const char* filenameBooks) {
	students student;
	books book;

	char res;
	do {
		FILE* studentsDb = fopen(filenameStudents, PR_R);
		FILE* booksDb = fopen(filenameBooks, PR_R);

		int studentsCount = 0;
		int booksCount = 0;
		//Количество студентов из базы
		while (fread(&student, sizeof(student), 1, studentsDb)) {
			studentsCount++;
		}
		//Количество книг из базы
		while (fread(&book, sizeof(book), 1, booksDb)) {
			booksCount++;
		}
		rewind(booksDb);
		rewind(studentsDb);

		//Записать в массив книги, полученные из базы
		books* booksArr = new books[booksCount];
		for (int i = 0; fread(&book, sizeof(book), 1, booksDb) > 0; i++) {
			booksArr[i].id = book.id;
			memcpy(booksArr[i].name, book.name, sizeof(book.name));
		}

		//Записать в массив студентов, полученных из базы
		students* studentsArr = new students[studentsCount];
		for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
			studentsArr[i].id = student.id;
			studentsArr[i].booksCount = student.booksCount;
			memcpy(studentsArr[i].name, student.name, sizeof(student.name));
			memcpy(studentsArr[i].surname, student.surname, sizeof(student.surname));
			//Для каждого студента записать книги, принадлежащие ему
			for (int j = 0; j < student.booksCount; j++) {
				studentsArr[i].book[j].id = student.book[j].id;
				memcpy(studentsArr[i].book[j].name, student.book[j].name, sizeof(student.book[j].name));
			}
		}

		//Проверка, есть ли студент в базе данных
		int studentId = 0;
		bool studentNotFound = true;
		while (studentNotFound) {
			printf("\nВведите id студента: ");
			scanf("%i", &studentId);
			for (int i = 0; i < studentsCount; i++) {
				if (studentsArr[i].id == studentId) {
					studentNotFound = false;
					break;
				}
			}
			if (studentNotFound) {
				printf("Студент не найден\n");
			}
		}

		//Проверка, есть ли книга в базе данных
		int bookId = 0;
		bool bookNotFound = true;
		while (bookNotFound) {
			printf("\nВведите id книги: ");
			scanf("%i", &bookId);
			for (int i = 0; i < booksCount; i++) {
				if (booksArr[i].id == bookId) {
					bookNotFound = false;
					break;
				}
			}
			//Книга не найдена, функция запускается заново
			if (bookNotFound) {
				printf("Книга не найдена\n");
				printf("\n Продолжать?[Y/N]");
				while ((res = getchar()) == '\n');
			}
			//Книга найдена, цикл продолжает работу
			else {
				//id начинается с 1, индексация массива с 0
				int studentIndex = studentId - 1;
				//Если у студента нет книг, то выходим из цикла и продолжаем запись в файл
				if (studentsArr[studentIndex].booksCount == 0) {
					break;
				}

				//Проверка, есть ли у студента конкретная книга
				for (int i = 0; i < studentsArr[studentIndex].booksCount; i++) {
					//У студента найдена точно такая же книга, пользователь снова должен ввести id книги
					if (studentsArr[studentIndex].book[i].id == bookId) {
						bookNotFound = true;
						printf("Такая книга уже есть у студента\n");
						break;
					}
				}
			}
		}

		//Записать в массив найденную книгу для найденного студента
		for (int i = 0; i < studentsCount; i++) {
			if (studentId == studentsArr[i].id) {
				for (int j = 0; j < booksCount; j++) {
					if (bookId == booksArr[j].id) {
						//Количество книг, принадлежащих конкретному студенту
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

		//Очистить все предыдущие записи из базы
		studentsDb = fopen(filenameStudents, PR_W);
		//Перезаписать студентов в базу, с учетом того, что была выдана книга конкретному студенту
		for (int i = 0; i < studentsCount; i++)
			fwrite(&studentsArr[i], sizeof(studentsArr[i]), 1, studentsDb);
		printf("Студент получил книгу\n");

		delete[] booksArr;
		delete[] studentsArr;
		fclose(studentsDb);
		fclose(booksDb);

		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');

	return;
}

//Забрать книгу у студента
void TakeBook(const char* filenameStudents) {
	students student;

	char res;
	do {
		FILE* studentsDb = fopen(filenameStudents, PR_R);
		//Найти количество студентов в базе
		int studentsCount = 0;
		while (fread(&student, sizeof(student), 1, studentsDb))
			studentsCount++;
		rewind(studentsDb);

		//Запись из файла в массив студентов из базы
		students* studentsArr = new students[studentsCount];
		for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
			studentsArr[i].id = student.id;
			memcpy(studentsArr[i].name, student.name, sizeof(student.name));
			memcpy(studentsArr[i].surname, student.surname, sizeof(student.surname));
			studentsArr[i].booksCount = student.booksCount;
			for (int j = 0; j < student.booksCount; j++) {
				studentsArr[i].book[j].id = student.book[j].id;
				memcpy(studentsArr[i].book[j].name, student.book[j].name, sizeof(student.book[j].name));
			}
		}

		//Проверить, есть ли студент в базе
		int studentId = 0;
		bool studentWasFound = false;
		while (!studentWasFound) {
			printf("\nВведите id студента: ");
			scanf("%i", &studentId);
			for (int i = 0; i < studentsCount; i++) {
				if (studentsArr[i].id == studentId) {
					studentWasFound = true;
					break;
				}
			}
			if (!studentWasFound) {
				printf("Студент не найден\n");
				return;
			}
		}

		//Проверить, есть ли конкретная книга у конкретного студента
		int bookId = 0;
		bool bookWasFound = false;
		while (!bookWasFound) {
			printf("\nВведите id книги: ");
			scanf("%i", &bookId);
			for (int i = 0; i < studentsCount; i++) {
				for (int j = 0; j < studentsArr[i].booksCount; j++) {
					if (studentsArr[i].book[j].id == bookId) {
						bookWasFound = true;
						break;
					}
				}
				if (!bookWasFound) {
					printf("Книга не найдена\n");
					return;
				}
			}
		}

		students* newStudentsArr = new students[studentsCount];
		for (int i = 0; i < studentsCount; i++) {
			//Записываем в новый массив найденного студента
			if (studentsArr[i].id == studentId) {
				newStudentsArr[i].id = studentsArr[i].id;
				//Количество книг у студента уменьшится на 1
				newStudentsArr[i].booksCount = studentsArr[i].booksCount - 1;
				memcpy(newStudentsArr[i].name, studentsArr[i].name, sizeof(studentsArr[i].name));
				memcpy(newStudentsArr[i].surname, studentsArr[i].surname, sizeof(studentsArr[i].surname));
				for (int j = 0; j < newStudentsArr[i].booksCount; j++) {
					newStudentsArr[i].book[j].id = studentsArr[i].book[j].id;
					memcpy(newStudentsArr[i].book[j].name, studentsArr[i].book[j].name, sizeof(studentsArr[i].book[j].name));
					//Книга, подлежащая удалению найдена
					if (studentsArr[i].book[j].id == bookId) {
						for (int k = j; k < newStudentsArr[i].booksCount; k++) {
							newStudentsArr[i].book[j].id = studentsArr[i].book[k + 1].id;
							memcpy(newStudentsArr[i].book[j].name, studentsArr[i].book[k + 1].name, sizeof(studentsArr[i].book[k + 1].name));
						}
						break;
					}
				}
			}
			//Записываем в новый массив студентов, кроме найденного
			else {
				newStudentsArr[i].id = studentsArr[i].id;
				newStudentsArr[i].booksCount = studentsArr[i].booksCount;
				memcpy(newStudentsArr[i].name, studentsArr[i].name, sizeof(studentsArr[i].name));
				memcpy(newStudentsArr[i].surname, studentsArr[i].surname, sizeof(studentsArr[i].surname));
				for (int j = 0; j < newStudentsArr[i].booksCount; j++) {
					newStudentsArr[i].book[j].id = studentsArr[i].book[j].id;
					memcpy(newStudentsArr[i].book[j].name, studentsArr[i].book[j].name, sizeof(studentsArr[i].book[j].name));
				}
			}
		}

		//Очистить все предыдущие записи из базы
		studentsDb = fopen(filenameStudents, PR_W);
		//Перезаписать студентов в базу, с учетом того, что была выдана книга конкретному студенту
		for (int i = 0; i < studentsCount; i++)
			fwrite(&newStudentsArr[i], sizeof(newStudentsArr[i]), 1, studentsDb);
		printf("Студент вернул книгу\n");

		delete[] newStudentsArr;
		delete[] studentsArr;
		fclose(studentsDb);

		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');
	
	return;
}

//Вывести всех студентов и список книг, которые принадлежат каждому студенту
void ShowLibrary(const char* filenameStudents) {
	int studentsCount = 0;
	FILE* studentsDb;
	studentsDb = fopen(filenameStudents, PR_R);
	students student;

	for (int i = 0; fread(&student, sizeof(student), 1, studentsDb) > 0; i++) {
		//Заголовок с информацией о студенте
		printf("\nСтудент: \n");
		for (int j = 1; j <= 49; j++)
			printf("-");
		printf("\n|%15s|%15s|%15s|\n", "id", "Имя", "Фамилия");
		for (int j = 1; j <= 49; j++)
			printf("-");
		printf("\n");
		//Строка с данными о студенте
		printf("|%15i|%15s|%15s|\n", student.id, student.name, student.surname);
		for (int j = 1; j <= 49; j++)
			printf("-");
		printf("\n\n");

		//Заголовок для списка книг, которые взял студент
		printf("Взял книги: \n");
		for (int j = 1; j <= 33; j++)
			printf("-");
		printf("\n|%15s|%15s|\n", "id", "name");
		for (int j = 1; j <= 33; j++)
			printf("-");
		//Список книг, которые взял студент
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
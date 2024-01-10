#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>
#define FNAME_STUDENTS "./students.dat"
#define FNAME_BOOKS "./books.dat"
//признак открытия бинарного файла на чтение
const char PR_R[] = "rb";
//признак открытия файла на чтение и запись
const char PR_S[] = "r+b";
//признак открытия файла на запись
const char PR_W[] = "wb";
//признак открытия файла на добавление
const char PR_A[] = "ab";	

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
		printf("\n  1 - Создать базу данных");
		printf("\n  2 - Записать в базу данных");
		printf("\n  3 - Просмотреть базу данных");
		printf("\n  4 - Удалить из базы данных");
		printf("\n  5 - Библиотека");
		printf("\n  6 - Удалить базу данных");
		printf("\n  7 - Выход из программы\n");
		printf("\n Введите номер действия:");
		int var = 0;
		char res;
		scanf("%i", &var);
		switch (var) {
			case 1:
				printf("Создать базу данных? [Y/N]\n");
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					printf("\nБаза данных уже создана!\n");
					break;
				}
				while ((res = getchar()) == '\n');
				if (res == 'Y' || res == 'y') {
					FILE* studentsDb = fopen(filenameStudents, PR_W);
					FILE* booksDb = fopen(filenameBooks, PR_W);
					fclose(studentsDb);
					fclose(booksDb);
					printf("\nБаза данных готова к работе\n");
					break;
				}
				break;
			case 2:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					printf("\n\tВыберите таблицу:\n");
					printf("1 - Студенты\n");
					printf("2 - Книги\n");
					printf("3 - Вернуться назад\n");
					printf("\nВведите вид действия ->");
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
	
					break;
				}
				
				printf("\nОшибка открытия файла для записи\n");
				break;
			case 3:
				if (fopen(filenameStudents, PR_R) && fopen(filenameBooks, PR_R)) {
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

					break;
				}

				printf("\nОшибка открытия файла для чтения\n");
				break;
			case 4:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					printf("\n\tВыберите таблицу:\n");
					printf("1 - Удалить студента\n");
					printf("2 - Удалить книгу\n");
					printf("3 - Удалить всех студентов\n");
					printf("4 - Удалить все книги\n");
					printf("5 - Вернуться назад\n");
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
					else if (var == 3) {
						FILE* studentsDb = fopen(filenameStudents, PR_W);
						fclose(studentsDb);
						printf("\nВсе студенты удалены\n");
						break;
					}
					else if (var == 4) {
						FILE* booksDb = fopen(filenameBooks, PR_W);
						fclose(booksDb);
						printf("\nВсе книги удалены\n");
						break;
					}
					else if (var == 5) break;
						
					break;
				}

				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			case 5:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					printf("\n\tВыберите действие:\n");
					printf("1 - Выдать книгу студенту\n");
					printf("2 - Забрать книгу у студента\n");
					printf("3 - Просмотреть библиотеку\n");
					printf("4 - Вернуться назад\n");
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
					else if (var == 4) break;

					break;
				}

				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			case 6:
				if (fopen(filenameStudents, PR_S) && fopen(filenameBooks, PR_S)) {
					printf("\nВнимание! Все данные будут безвозвратно удалены\n");
					printf("Продолжить? [Y/N]\n");
					while ((res = getchar()) == '\n');
					if (res == 'Y' || res == 'y') {
						FILE* studentsDb = fopen(filenameStudents, PR_W);
						FILE* booksDb = fopen(filenameBooks, PR_W);
						fclose(studentsDb);
						fclose(booksDb);
						printf("\nБаза данных удалена\n");
						break;
					}
				}
				printf("\nОшибка открытия файла\n");
				break;
			
			case 7: return 0;

			default:
				break;
		}
	}
}

//Вывести всех студентов из базы
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

		//Запись студента в базу данных
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

		//Записать книгу в базу данных
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
		//Поиск количества книг в базе
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

		//Проверка, есть ли книга в базе данных
		int bookId = 0;
		bool bookWasFound = false;
		while (!bookWasFound) {
			printf("\nВведите id книги: ");
			scanf("%i", &bookId);
			for (int i = 0; i < booksCount; i++) {
				if (booksArr[i].id == bookId) {
					bookWasFound = true;
					break;
				}
			}
			if (!bookWasFound) {
				printf("Книга не найдена\n");
				fclose(booksDb);
				return;
			}
		}

		//Количество книг после удаления уменьшится на 1
		booksCount--;
		//Запись в новый массив книг, кроме той, которую нужно удалить
		books* newBooksArr = new books[booksCount];
		for (int i = 0; i < booksCount; i++) {
			newBooksArr[i].id = booksArr[i].id;
			memcpy(newBooksArr[i].name, booksArr[i].name, sizeof(book.name));
			if (booksArr[i].id == bookId) {
				//После того, как будет найдена нужная книга, необходимо сдвинуть все элементы массива
				for (int j = i; j < booksCount; j++) {
					newBooksArr[j].id = booksArr[j + 1].id;
					memcpy(newBooksArr[j].name, booksArr[j + 1].name, sizeof(book.name));
				}
				break;
			}
		}
		delete[] booksArr;

		//Необходимо очистить файл, чтобы записать в него все книги из массива
		booksDb = fopen(fileName, PR_W);
		for (int i = 0; i < booksCount; i++)
			fwrite(&newBooksArr[i], sizeof(newBooksArr[i]), 1, booksDb);

		delete[] newBooksArr;
		fclose(booksDb);
		printf("Книга успешно удалена\n");
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
		//Поиск количества студентов в базе
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
		
		//Проверка, есть ли студент в базе данных
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
				fclose(studentsDb);
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
			//Количество книг, взятых студентом
			newStudentsArr[i].booksCount = studentsArr[i].booksCount;
			//Для каждого студента записать список книг, взятых им
			for (int j = 0; j < studentsArr[i].booksCount; j++) {
				newStudentsArr[i].book[j].id = studentsArr[i].book[j].id;
				memcpy(newStudentsArr[i].book[j].name, studentsArr[i].book[j].name, sizeof(studentsArr[i].book[j].name));
			}

			//Студент, которого нужно удалить найден
			if (newStudentsArr[i].id == studentId) {
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

		//Необходимо очистить файл, чтобы записать в него всех студентов из массива
		studentsDb = fopen(filenameStudents, PR_W);
		for (int i = 0; i < studentsCount; i++)
			fwrite(&newStudentsArr[i], sizeof(newStudentsArr[i]), 1, studentsDb);		

		fclose(studentsDb);
		delete[] newStudentsArr;
		printf("Студент успешно удален\n");
		printf("\n Продолжать?[Y/N]");
		while ((res = getchar()) == '\n');
	} while (res == 'Y' || res == 'y' || res == 'H' || res == 'н');

	return;
}

//Выдать книгу студенту
void GetBook(const char* filenameStudents, const char* filenameBooks) {
	students student;
	books book;

	char res;
	do {
		FILE* studentsDb = fopen(filenameStudents, PR_R);
		FILE* booksDb = fopen(filenameBooks, PR_R);

		//Количество студентов из базы
		int studentsCount = 0;
		while (fread(&student, sizeof(student), 1, studentsDb)) {
			studentsCount++;
		}
		//Количество книг из базы
		int booksCount = 0;
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
		bool studentWasFound = true;
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
				fclose(studentsDb);
				fclose(booksDb);
				return;
			}
		}

		//Проверка, есть ли книга в базе данных
		int bookId = 0;
		bool bookWasFound = false;
		while (!bookWasFound) {
			printf("\nВведите id книги: ");
			scanf("%i", &bookId);
			for (int i = 0; i < booksCount; i++) {
				if (booksArr[i].id == bookId) {
					bookWasFound = true;
					break;
				}
			}
			if (!bookWasFound) {
				printf("Книга не найдена в базе\n");
				fclose(studentsDb);
				fclose(booksDb);
				return;
			}
			//Книга найдена
			else {
				//id начинается с 1, индексация массива с 0
				int studentIndex = studentId - 1;
				//Если у студента нет книг, то необходимо выйти из цикла и продолжить запись в базу
				if (studentsArr[studentIndex].booksCount == 0) {
					break;
				}

				//Проверка, есть ли у студента книга, подлежащая выдаче
				for (int i = 0; i < studentsArr[studentIndex].booksCount; i++) {
					if (studentsArr[studentIndex].book[i].id == bookId) {
						printf("Такая книга уже есть у студента\n");
						fclose(studentsDb);
						fclose(booksDb);
						return;
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
						int studentBooksCount = studentsArr[i].booksCount;
						studentsArr[i].book[studentBooksCount].id = booksArr[j].id;
						memcpy(studentsArr[i].book[studentBooksCount].name, booksArr[j].name, sizeof(booksArr[j].name));
						studentsArr[i].booksCount = studentsArr[i].booksCount + 1;
					}
				}
			}
		}
		fclose(studentsDb);

		//Перезаписать студентов в базу, с учетом того, что была выдана книга конкретному студенту
		studentsDb = fopen(filenameStudents, PR_W);
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
		//Количество студентов в базе
		int studentsCount = 0;
		while (fread(&student, sizeof(student), 1, studentsDb))
			studentsCount++;
		rewind(studentsDb);

		//Запись в массив студентов из базы
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
				fclose(studentsDb);
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
					printf("Такой книги нет у студента\n");
					fclose(studentsDb);
					return;
				}
			}
		}

		students* newStudentsArr = new students[studentsCount];
		for (int i = 0; i < studentsCount; i++) {
			//Запись в новый массив найденного студента
			if (studentsArr[i].id == studentId) {
				newStudentsArr[i].id = studentsArr[i].id;
				//Количество книг у студента уменьшится на 1
				newStudentsArr[i].booksCount = studentsArr[i].booksCount - 1;
				memcpy(newStudentsArr[i].name, studentsArr[i].name, sizeof(studentsArr[i].name));
				memcpy(newStudentsArr[i].surname, studentsArr[i].surname, sizeof(studentsArr[i].surname));
				for (int j = 0; j < newStudentsArr[i].booksCount; j++) {
					newStudentsArr[i].book[j].id = studentsArr[i].book[j].id;
					memcpy(newStudentsArr[i].book[j].name, studentsArr[i].book[j].name, sizeof(studentsArr[i].book[j].name));
					//Книга, подлежащая удалению, найдена
					if (studentsArr[i].book[j].id == bookId) {
						for (int k = j; k < newStudentsArr[i].booksCount; k++) {
							newStudentsArr[i].book[j].id = studentsArr[i].book[k + 1].id;
							memcpy(newStudentsArr[i].book[j].name, studentsArr[i].book[k + 1].name, sizeof(studentsArr[i].book[k + 1].name));
						}
						break;
					}
				}
			}

			//Запись в новый массив, кроме найденного студента
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

		//Перезаписать студентов в базу, с учетом того, что конкретный студент вернул книгу
		studentsDb = fopen(filenameStudents, PR_W);
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
	FILE* studentsDb = fopen(filenameStudents, PR_R);
	students student;

	if (fread(&student, sizeof(student), 1, studentsDb) == 0) {
		printf("\nВ базе нет студентов\n");
		fclose(studentsDb);
		return;
	}
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
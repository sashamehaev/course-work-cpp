#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include "sqlite3.h"

void CreateDatabase();
void CreateBooksTable();
void CreateStudentsTable();
void CreateStudentsBooksTable();
void AddBook();
void AddStudent();
void ShowBooks();
void ShowStudents();
void DeleteStudent();
void DeleteBook();
void GetBook();
void TakeBook();
void ShowStudentBooks();
void DropDatabase();
void ShowLibrary();

int main() {
    setlocale(LC_ALL, "ru");
    
    while (true) {
        std::cout << "1 - Создать базу данных\n";
        std::cout << "2 - Записать в базу данных\n";
        std::cout << "3 - Просмотреть базу данных\n";
        std::cout << "4 - Удалить из базы данных\n";
        std::cout << "5 - Библиотека\n";
        std::cout << "6 - Очистить базу данных\n";
        std::cout << "7 - Выход из программы\n";
        std::cout << "\n Введите номер действия:";
        int user_choice = 0;
        std::cin >> user_choice;
        if (user_choice == 1) {
            while (true) {
                CreateDatabase();
                break;
            }
        }
        else if (user_choice == 2) {
            while (true) {
                std::cout << "\n Выберите таблицу:\n";
                std::cout << "1 - Студенты\n";
                std::cout << "2 - Книги\n";
                std::cout << "3 - Вернуться назад\n";
                std::cout << "\nВведите вид действия ->\n";
                std::cin >> user_choice;
                if (user_choice == 1) {
                    AddStudent();
                    break;
                }
                else if (user_choice == 2) {
                    AddBook();
                    break;
                }
                else if (user_choice == 3) {

                    break;
                }
                break;
            }
        }
        else if (user_choice == 3) {
            while (true) {
                std::cout << "\n Выберите таблицу:\n";
                std::cout << "1 - Студенты\n";
                std::cout << "2 - Книги\n";
                std::cout << "3 - Вернуться назад\n";
                std::cout << "\nВведите вид действия ->\n";
                std::cin >> user_choice;
                if (user_choice == 1) {
                    std::cout << "\nСписок студентов:\n" << std::endl;
                    ShowStudents();
                    break;
                }
                else if (user_choice == 2) {
                    std::cout << "\nСписок книг:\n" << std::endl;
                    ShowBooks();
                    break;
                }
                else if (user_choice == 3) {

                    break;
                }
                break;
            }
        }
        else if (user_choice == 4) {
            while (true) {
                std::cout << "\n Выберите таблицу:\n";
                std::cout << "1 - Студенты\n";
                std::cout << "2 - Книги\n";
                std::cout << "3 - Вернуться назад\n";
                std::cout << "\nВведите вид действия ->\n";
                std::cin >> user_choice;
                if (user_choice == 1) {
                    DeleteStudent();
                    break;
                }
                else if (user_choice == 2) {
                    DeleteBook();
                    break;
                }
                else if (user_choice == 3) {

                    break;
                }
                break;
            }
        }
        else if (user_choice == 5) {
            while (true) {
                std::cout << "\n Выберите действие:\n";
                std::cout << "1 - Выдать книгу студенту\n";
                std::cout << "2 - Забрать книгу у студента\n";
                std::cout << "3 - Посмотреть, какие книги взял студент\n";
                std::cout << "4 - Посмотреть всех студентов, которые получили книги\n";
                std::cout << "5 - Вернуться назад\n";
                std::cout << "\nВведите вид действия ->\n";
                std::cin >> user_choice;
                if (user_choice == 1) {
                    GetBook();
                    break;
                }
                else if (user_choice == 2) {
                    TakeBook();
                    break;
                }
                else if (user_choice == 3) {
                    ShowStudentBooks();
                    break;
                }
                else if (user_choice == 4) {
                    ShowLibrary();
                    break;
                }
                else if (user_choice == 5) {

                    break;
                }
                break;
            }
        }
        else if (user_choice == 6) {
            while (true) {
                DropDatabase();
                break;
            }
        }
        else if (user_choice == 7) {
            return 0;
        }
    }

    return 0;
}

//Создать таблицу "книги"
void CreateBooksTable() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "book_name TEXT NOT NULL, "
        "book_author_name TEXT NOT NULL, "
        "book_author_surname TEXT NOT NULL "
        ");";

    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (rc == SQLITE_OK) {
        std::cout << "Таблица books создана успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return;
}

//Создать базу данных
void CreateDatabase() {
    const char* db = "library.sqlite";
    std::ifstream file(db);
    if (file.is_open() == 1) {
        std::cout << "База данных уже создана" << std::endl;
        file.close();
        return;
    }
    CreateBooksTable();
    CreateStudentsTable();
    CreateStudentsBooksTable();
    return;
};

//Добавить книгу в таблицу "книги"
void AddBook() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string book_name;
    std::cout << "Введите название книги: ";
    std::cin >> book_name;

    std::string book_author_name;
    std::cout << "Введите имя автора книги: ";
    std::cin >> book_author_name;

    std::string book_author_surname;
    std::cout << "Введите фамилию автора книги: ";
    std::cin >> book_author_surname;

    std::string sql = 
        "INSERT INTO books (book_name, book_author_name, book_author_surname) "
        "VALUES('" + book_name + "', '" + book_author_name + "', '" + book_author_surname + "'); ";

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc == SQLITE_OK) {
        std::cout << "Запись добавлена успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return;
}

//Вывести все записи из таблицы "книги"
void ShowBooks() {
    sqlite3* db;
    int rc;
    char** result;
    int rows;
    int columns;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql = "SELECT * FROM books;";
    rc = sqlite3_get_table(db, sql, &result, &rows, &columns, &errMsg);


    if (rc == SQLITE_OK) {
        int j = columns;
        for (int i = 0; i < rows; i++) {
            std::cout << "id: " << result[j] << std::endl;
            j++;
            std::cout << "Название книги: " << result[j] << std::endl;
            j++;
            std::cout << "Имя автора: " << result[j] << std::endl;
            j++;
            std::cout << "Фамилия автора: " << result[j] << "\n" << std::endl;
            j++;
        }
    }
    else {
        std::cerr << "Ошибка: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_free_table(result);
    sqlite3_close(db);

    return;
}

//Создать таблицу "студенты"
void CreateStudentsTable() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "student_name TEXT NOT NULL, "
        "student_surname TEXT NOT NULL "
        ");";

    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (rc == SQLITE_OK) {
        std::cout << "Таблица students создана успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return;
}

//Добавить студента в таблицу "студенты"
void AddStudent() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string student_name;
    std::cout << "Введите имя студента: ";
    std::cin >> student_name;

    std::string student_surname;
    std::cout << "Введите фамилию студента: ";
    std::cin >> student_surname;

    std::string sql = "INSERT INTO students (student_name, student_surname) VALUES ('" + student_name + "', '" + student_surname + "');";

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc == SQLITE_OK) {
        std::cout << "Запись добавлена успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return;
}

//Вывести все записи из таблицы "студенты"
void ShowStudents() {
    sqlite3* db;
    int rc;
    char** result;
    int rows;
    int columns;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql = "SELECT * FROM students;";
    rc = sqlite3_get_table(db, sql, &result, &rows, &columns, &errMsg);


    if (rc == SQLITE_OK) {
        int j = columns;
        for (int i = 0; i < rows; i++) {
            std::cout << "id: " << result[j] << std::endl;
            j++;
            std::cout << "Имя студента: " << result[j] << std::endl;
            j++;
            std::cout << "Фамилия студента: " << result[j] << "\n" << std::endl;
            j++;
        }
    }
    else {
        std::cerr << "Ошибка: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_free_table(result);
    sqlite3_close(db);

    return;
}

//Удалить студента по id из таблицы "студенты"
void DeleteStudent() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string student_id;
    std::cout << "Введите id студента, которого нужно удалить: ";
    std::cin >> student_id;

    std::string sql = "DELETE FROM students WHERE id = " + student_id + ";";

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc == SQLITE_OK) {
        std::cout << "Запись удалена успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return;
}

//Удалить книгу по id из таблицы "книги"
void DeleteBook() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string book_id;
    std::cout << "Введите id книги, которую нужно удалить: ";
    std::cin >> book_id;

    std::string sql = "DELETE FROM books WHERE id = " + book_id + ";";

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc == SQLITE_OK) {
        std::cout << "Запись удалена успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return;
}

//Создаем промежуточную таблицу, чтобы связать студентов и книги
void CreateStudentsBooksTable() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS students_books ("
        "student_id INTEGER, "
        "book_id INTEGER, "
        "PRIMARY KEY (student_id, book_id), "
        "FOREIGN KEY (student_id) REFERENCES students(id), "
        "FOREIGN KEY (book_id) REFERENCES books(id) "
        ");";

    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (rc == SQLITE_OK) {
        std::cout << "Таблица students_books создана успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return;
}

//Выдать книгу студенту
void GetBook() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string student_id;
    std::cout << "Введите id студента, который пришел получать книгу: ";
    std::cin >> student_id;

    std::string book_id;
    std::cout << "Введите id книги, которую получит студент: ";
    std::cin >> book_id;

std::string sql = "INSERT INTO students_books (student_id, book_id) VALUES(" + student_id + ", " + book_id + ");";

int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

if (rc == SQLITE_OK) {
    std::cout << "Запись добавлена успешно!" << std::endl;
}
else {
    std::cerr << "Ошибка SQL: " << errMsg << std::endl;
    sqlite3_free(errMsg);
}

sqlite3_close(db);
return;
}

//Забрать книгу у студента
void TakeBook() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string student_id;
    std::cout << "Введите id студента, который пришел возвращать книгу: ";
    std::cin >> student_id;

    std::string book_id;
    std::cout << "Введите id книги, которую возвращает студент: ";
    std::cin >> book_id;

    std::string sql = "DELETE FROM students_books WHERE student_id = " + student_id + " AND book_id = " + book_id + ";";

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc == SQLITE_OK) {
        std::cout << "Запись удалена успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return;
}

//Посмотреть, какие книги взял студент
void ShowStudentBooks() {
    sqlite3* db;
    int rc;
    char** result;
    int rows;
    int columns;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    std::string student_id;
    std::cout << "Введите id студента: ";
    std::cin >> student_id;

    std::string sql =
        "SELECT "
        "    students.student_name, "
        "    students.student_surname, "
        "    books.id, "
        "    books.book_name, "
        "    books.book_author_name, "
        "    books.book_author_surname "
        "FROM students "
        "JOIN students_books ON students.id = students_books.student_id "
        "JOIN books ON students_books.book_id = books.id "
        "WHERE students.id = " + student_id + ";";

    rc = sqlite3_get_table(db, sql.c_str(), &result, &rows, &columns, &errMsg);


    if (rc == SQLITE_OK) {
        std::cout << "Имя студента: " << result[columns] << std::endl; //значение из колонки student_name
        std::cout << "Фамилия студента: " << result[columns + 1] << std::endl; //значение из колонки student_surname

        std::cout << "\nКниги, которые взял студент" << std::endl;
        for (int i = columns + 2; i <= columns * (rows + 1); i = i + 3) {
            std::cout << "id книги: " << result[i] << std::endl; //значение из колонки book.id
            i++;
            std::cout << "Название книги: " << result[i] << std::endl; //значение из колонки book_name
            i++;
            std::cout << "Имя автора книги: " << result[i] << std::endl; //значение из колонки book_author_name
            i++;
            std::cout << "Фамилия автора книги: " << result[i] << "\n" << std::endl; //значение из колонки book_author_surname
        }
    }
    else {
        std::cerr << "Ошибка: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_free_table(result);
    sqlite3_close(db);
    return;
}

//Удалить файл базы данных
void DropDatabase() {
    const char* db = "library.sqlite";
    if (std::remove(db) == 0) {
        std::cout << "База данных: " << db << " удалена" << std::endl;
    }
    else {
        std::cerr << "Не удалось удалить базу данных: " << db << " .Файл не найден" << std::endl;
    }
    return;
}

//Посмотреть всех студентов, которые получили книги
void ShowLibrary() {
    sqlite3* db;
    int rc;
    char** result;
    int rows;
    int columns;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql =
        "SELECT "
        "    students.id, "
        "    students.student_name, "
        "    students.student_surname, "
        "    books.id, "
        "    books.book_name, "
        "    books.book_author_name, "
        "    books.book_author_surname "
        "FROM students "
        "JOIN students_books ON students.id = students_books.student_id "
        "JOIN books ON students_books.book_id = books.id;";

    rc = sqlite3_get_table(db, sql, &result, &rows, &columns, &errMsg);


    if (rc == SQLITE_OK) {
        std::cout << rows << " строк" << std::endl;
        std::cout << columns << " колонок" << std::endl;
        int j = columns;
        for (int i = 0; i < rows; i++) {
            std::cout << "id студента: " << result[j] << std::endl;
            j++;
            std::cout << "Имя студента: " << result[j] << std::endl;
            j++;
            std::cout << "Фамилия студента: " << result[j] << std::endl;
            j++;
            std::cout << "id книги: " << result[j] << std::endl;
            j++;
            std::cout << "Название книги: " << result[j] << std::endl;
            j++;
            std::cout << "Имя автора книги: " << result[j] << std::endl;
            j++;
            std::cout << "Фамилия автора книги: " << result[j] << "\n" << std::endl;
            j++;
        }
    }
    else {
        std::cerr << "Ошибка: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_free_table(result);
    sqlite3_close(db);
    return;
}
#include <iostream>
#include <string>
#include "sqlite3.h"

void CreateDatabase();
void CreateBooksTable();
void CreateStudentsTable();
void AddBook();
void AddStudent();
void ShowBooks();
void ShowStudents();
void DeleteStudent();
void DeleteBook();

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

        }
        else if (user_choice == 6) {

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

    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
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
    CreateBooksTable();
    CreateStudentsTable();
    return;
};

//Добавить книгу в таблицу "книги"
void AddBook() {
    sqlite3* db;
    char* errMsg = nullptr;

    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
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
    std::string sql = "INSERT INTO books (book_name, book_author_name, book_author_surname) VALUES ('" + book_name + "', '" + book_author_name + "', '" + book_author_surname + "');";

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

    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
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

    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
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

    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
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

    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
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

    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
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

    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
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
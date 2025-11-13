#include <iostream>
#include <string>
#include "sqlite3.h"

void CreateDatabase();
void CreateBooksTable();
void AddBook();
void ShowBooks();

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
void CreateBooksTable() {
    sqlite3* db;
    char* errMsg = nullptr;

    // 1. Открываем базу данных (файл создастся, если его нет)
    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // 2. Формируем SQL‑запрос на создание таблицы
    const char* sql =
        "CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "book_name TEXT NOT NULL, "
        "book_author_name TEXT NOT NULL, "
        "book_author_surname TEXT NOT NULL "
        ");";

    // 3. Выполняем запрос
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    // 4. Проверяем результат
    if (rc == SQLITE_OK) {
        std::cout << "Таблица books создана успешно!" << std::endl;
    }
    else {
        std::cerr << "Ошибка SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);  // обязательно освобождаем память
    }

    // 5. Закрываем соединение с БД
    sqlite3_close(db);
    return;
}

void CreateDatabase() {
    CreateBooksTable();
    
    return;
};

void AddBook() {
    sqlite3* db;
    char* errMsg = nullptr;

    // Открываем базу данных
    if (sqlite3_open("library.sqlite3", &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // SQL‑запрос на добавление записи
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

    // Закрываем БД
    sqlite3_close(db);
    return;
}

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
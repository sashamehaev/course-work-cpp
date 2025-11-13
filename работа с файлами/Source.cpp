#include <iostream>
#include "sqlite3.h"

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
                sqlite3* db;
                char* errMsg = nullptr;

                // Открываем БД (файл создастся, если его нет)
                int rc = sqlite3_open("library.db", &db);
                if (rc != SQLITE_OK) {
                    std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
                    return 1;
                }

                std::cout << "БД открыта успешно!" << std::endl;
                sqlite3_close(db);
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

                    break;
                }
                else if (user_choice == 3) {

                    break;
                }
                break;
            }
        }
        else if (user_choice == 3) {

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
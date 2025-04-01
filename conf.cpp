#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cstdlib>

void show_help(const std::string& program_name) {
    std::cout << R"(
Usage: " << program_name << R"( [--help] <file_path> <search_pattern> <replace_text>
Replace text in a file using C++ regex engine

Arguments:
  file_path     Path to target file
  search_pattern Text pattern to search (regex compatible)
  replace_text  Replacement text (regex compatible)

Example:
  )" << program_name << R"( /etc/conf.conf 'web=1' 'web=2'

Note:
  - Use quotes for arguments with special characters
  - Backup file before replacement
  - This program uses C++ regex engine

by Коновалов Денис where.adm@gmail.com
---------------------------------------

Использование: )" << program_name << R"( <файл> <что заменить> <на что заменить>
Замена текста в файле с использованием регулярных выражений C++

Аргументы:
  файл         Путь к целевому файлу
  шаблон       Шаблон для поиска (совместим с регулярными выражениями)
  заменить     Текст замены (совместим с регулярными выраженияниями)

Пример:
  )" << program_name << R"( /etc/conf.conf 'web=1' 'web=2'

Примечания:
  - Используйте кавычки для аргументов со спецсимволами
  - Сделайте резервную копию файла перед заменой
  - Программа использует regex engine C++
by Коновалов Денис where.adm@gmail.com
)";
}

void change_text(const std::string& file_path, const std::string& search_pattern, const std::string& replace_text) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Файл " << file_path << " не найден!" << std::endl;
        std::exit(2);
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    try {
        std::regex pattern(search_pattern);
        std::string new_content = std::regex_replace(content, pattern, replace_text);

        std::ofstream out_file(file_path);
        if (!out_file.is_open()) {
            std::cerr << "Ошибка: Не удалось открыть файл для записи!" << std::endl;
            std::exit(3);
        }

        out_file << new_content;
        out_file.close();

        std::cout << "Замена успешно выполнена в файле " << file_path << std::endl;
    } catch (const std::regex_error& e) {
        std::cerr << "Ошибка регулярного выражения: " << e.what() << std::endl;
        std::exit(5);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        std::exit(3);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        show_help(argv[0]);
        return 0;
    }

    if (argc != 4) {
        std::cerr << "Ошибка: Неверное количество аргументов!" << std::endl;
        show_help(argv[0]);
        return 1;
    }

    change_text(argv[1], argv[2], argv[3]);
    return 0;
}

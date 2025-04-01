#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <filesystem>
#include <regex>
#include <algorithm>

namespace fs = std::filesystem;

const std::string VERSION = "1.0";
const std::string AUTHOR = "Коновалов Денис Александрович. where.adm@gmail.com";

void print_help() {
    std::cout << "conf - утилита для изменения параметров в конфигурационных файлах\n\n"
              << "Использование:\n"
              << "  conf /path/to/file.conf \"old_param:new_param\"\n"
              << "  conf /path/to/file.conf \"param1:value1\" \"param2:value2\"\n"
              << "  conf /path/to/file.conf \"old1:new1\"; \"old2:new2\"\n\n"
              << "Опции:\n"
              << "  --help    - показать эту справку\n"
              << "  --version - показать версию программы\n\n"
              << "Пример:\n"
              << "  conf /etc/nginx.conf \"worker_processes:2\" \"worker_processes:4\"\n\n"
              << "Создатель - " << AUTHOR << std::endl;
}

void print_version() {
    std::cout << "conf version " << VERSION << std::endl;
}

std::vector<std::pair<std::string, std::string>> parse_replacements(const std::vector<std::string>& args) {
    std::vector<std::pair<std::string, std::string>> replacements;
    
    for (const auto& arg : args) {
        size_t semicolon_pos = 0;
        size_t start_pos = 0;
        
        while ((semicolon_pos = arg.find(';', start_pos)) != std::string::npos) {
            std::string part = arg.substr(start_pos, semicolon_pos - start_pos);
            start_pos = semicolon_pos + 1;
            
            // Trim whitespace
            part.erase(part.begin(), std::find_if(part.begin(), part.end(), [](int ch) { return !std::isspace(ch); }));
            part.erase(std::find_if(part.rbegin(), part.rend(), [](int ch) { return !std::isspace(ch); }).base(), part.end());
            
            if (part.empty()) continue;
            
            size_t colon_pos = part.find(':');
            if (colon_pos == std::string::npos) {
                std::cerr << "Ошибка: некорректный формат замены '" << part << "'" << std::endl;
                return {};
            }
            
            std::string old_val = part.substr(0, colon_pos);
            std::string new_val = part.substr(colon_pos + 1);
            
            // Trim whitespace from values
            old_val.erase(old_val.begin(), std::find_if(old_val.begin(), old_val.end(), [](int ch) { return !std::isspace(ch); }));
            old_val.erase(std::find_if(old_val.rbegin(), old_val.rend(), [](int ch) { return !std::isspace(ch); }).base(), old_val.end());
            
            new_val.erase(new_val.begin(), std::find_if(new_val.begin(), new_val.end(), [](int ch) { return !std::isspace(ch); }));
            new_val.erase(std::find_if(new_val.rbegin(), new_val.rend(), [](int ch) { return !std::isspace(ch); }).base(), new_val.end());
            
            replacements.emplace_back(old_val, new_val);
            
            if (semicolon_pos == std::string::npos) break;
        }
        
        // Process the last part after semicolon (or the only part if no semicolon)
        if (start_pos < arg.size()) {
            std::string part = arg.substr(start_pos);
            
            // Trim whitespace
            part.erase(part.begin(), std::find_if(part.begin(), part.end(), [](int ch) { return !std::isspace(ch); }));
            part.erase(std::find_if(part.rbegin(), part.rend(), [](int ch) { return !std::isspace(ch); }).base(), part.end());
            
            if (part.empty()) continue;
            
            size_t colon_pos = part.find(':');
            if (colon_pos == std::string::npos) {
                std::cerr << "Ошибка: некорректный формат замены '" << part << "'" << std::endl;
                return {};
            }
            
            std::string old_val = part.substr(0, colon_pos);
            std::string new_val = part.substr(colon_pos + 1);
            
            // Trim whitespace from values
            old_val.erase(old_val.begin(), std::find_if(old_val.begin(), old_val.end(), [](int ch) { return !std::isspace(ch); }));
            old_val.erase(std::find_if(old_val.rbegin(), old_val.rend(), [](int ch) { return !std::isspace(ch); }).base(), old_val.end());
            
            new_val.erase(new_val.begin(), std::find_if(new_val.begin(), new_val.end(), [](int ch) { return !std::isspace(ch); }));
            new_val.erase(std::find_if(new_val.rbegin(), new_val.rend(), [](int ch) { return !std::isspace(ch); }).base(), new_val.end());
            
            replacements.emplace_back(old_val, new_val);
        }
    }
    
    return replacements;
}

bool process_replacements(const std::string& file_path, const std::vector<std::pair<std::string, std::string>>& replacements) {
    // Проверка существования файла
    if (!fs::exists(file_path)) {
        std::cerr << "Ошибка: файл '" << file_path << "' не существует" << std::endl;
        return false;
    }
    
    // Проверка прав на запись
    std::ofstream test_write(file_path, std::ios::app);
    if (!test_write) {
        std::cerr << "Ошибка: нет прав на запись в файл '" << file_path << "'" << std::endl;
        return false;
    }
    test_write.close();
    
    // Создание backup копии
    std::string backup_path = file_path + ".bak";
    try {
        fs::copy_file(file_path, backup_path, fs::copy_options::overwrite_existing);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при создании backup файла: " << e.what() << std::endl;
        return false;
    }
    
    // Чтение и обработка файла
    std::vector<std::string> lines;
    try {
        std::ifstream in_file(file_path);
        if (!in_file) {
            std::cerr << "Ошибка: не удалось открыть файл '" << file_path << "' для чтения" << std::endl;
            return false;
        }
        
        std::string line;
        while (std::getline(in_file, line)) {
            lines.push_back(line);
        }
        in_file.close();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при чтении файла: " << e.what() << std::endl;
        return false;
    }
    
    bool modified = false;
    for (auto& line : lines) {
        // Пропускаем комментарии
        if (line.empty() || line.find_first_not_of(" \t") == std::string::npos || 
            line[line.find_first_not_of(" \t")] == '#') {
            continue;
        }
        
        for (const auto& [old_val, new_val] : replacements) {
            // Ищем точное совпадение (с учетом пробелов вокруг)
            std::regex pattern("(^|\\s)" + std::regex_replace(old_val, std::regex("([\\[\\]\\(\\)\\{\\}\\.\\*\\+\\?\\^\\$\\\\\\|])"), "\\$1") + "(\\s|$)");
            
            std::string new_line = std::regex_replace(line, pattern, "$1" + new_val + "$2");
            if (new_line != line) {
                line = new_line;
                modified = true;
            }
        }
    }
    
    if (!modified) {
        std::cerr << "Предупреждение: не было сделано ни одной замены" << std::endl;
        return true;
    }
    
    // Запись измененного файла
    try {
        std::ofstream out_file(file_path);
        if (!out_file) {
            std::cerr << "Ошибка: не удалось открыть файл '" << file_path << "' для записи" << std::endl;
            return false;
        }
        
        for (const auto& line : lines) {
            out_file << line << '\n';
        }
        out_file.close();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при записи файла: " << e.what() << std::endl;
        return false;
    }
    
    return true;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }
    
    std::vector<std::string> args(argv + 1, argv + argc);
    
    if (std::find(args.begin(), args.end(), "--help") != args.end()) {
        print_help();
        return 0;
    }
    
    if (std::find(args.begin(), args.end(), "--version") != args.end()) {
        print_version();
        return 0;
    }
    
    std::string file_path = args[0];
    std::vector<std::string> replacement_args(args.begin() + 1, args.end());
    
    auto replacements = parse_replacements(replacement_args);
    if (replacements.empty()) {
        return 1;
    }
    
    if (!process_replacements(file_path, replacements)) {
        return 1;
    }
    
    return 0;
}

#!/usr/bin/env python3
import sys
import re
import os

def show_help():
    help_text = f"""
Usage: {sys.argv[0]} [--help] <file_path> <search_text> <replace_text>
Replace text in a file using Python's re module

Arguments:
  file_path     Path to target file
  search_text   Text pattern to search (regex compatible)
  replace_text  Replacement text (regex compatible)

Example:
  {sys.argv[0]} /etc/conf.conf 'web=1' 'web=2'

Note:
  - Use quotes for arguments with special characters
  - Backup file before replacement
  - This script uses Python's regex engine

by Коновалов Денис where.adm@gmail.com
---------------------------------------

Использование: {sys.argv[0]} <файл> <что заменить> <на что заменить>
Замена текста в файле с использованием модуля re Python

Аргументы:
  файл         Путь к целевому файлу
  искать       Шаблон для поиска (совместим с регулярными выражениями)
  заменить     Текст замены (совместим с регулярными выраженияниями)

Пример:
  {sys.argv[0]} /etc/conf.conf 'web=1' 'web=2'

Примечания:
  - Используйте кавычки для аргументов со спецсимволами
  - Сделайте резервную копию файла перед заменой
  - Скрипт использует regex engine Python
by Коновалов Денис where.adm@gmail.com
"""
    print(help_text)

def change_text(file_path, search_pattern, replace_text):
    if not os.path.isfile(file_path):
        print(f"Ошибка: Файл {file_path} не найден!", file=sys.stderr)
        sys.exit(2)
    
    try:
        with open(file_path, 'r') as file:
            content = file.read()
        
        try:
            new_content = re.sub(search_pattern, replace_text, content)
        except re.error as e:
            print(f"Ошибка регулярного выражения: {e}", file=sys.stderr)
            sys.exit(5)
        
        with open(file_path, 'w') as file:
            file.write(new_content)
        
        print(f"Замена успешно выполнена в файле {file_path}")
    except IOError as e:
        print(f"Ошибка ввода-вывода: {e.strerror}", file=sys.stderr)
        sys.exit(3)
    except Exception as e:
        print(f"Ошибка: {str(e)}", file=sys.stderr)
        sys.exit(3)

if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == "--help":
        show_help()
        sys.exit(0)
    
    if len(sys.argv) != 4:
        print("Ошибка: Неверное количество аргументов!", file=sys.stderr)
        show_help()
        sys.exit(1)
    
    change_text(sys.argv[1], sys.argv[2], sys.argv[3])

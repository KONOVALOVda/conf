#!/usr/bin/env python3
import sys
import os
import shutil
import re

VERSION = "1.0"
AUTHOR = "Коновалов Денис Александрович. where.adm@gmail.com"

def print_help():
    print("""conf - утилита для изменения параметров в конфигурационных файлах

Использование:
  conf /path/to/file.conf "old_param:new_param"
  conf /path/to/file.conf "param1:value1" "param2:value2"
  conf /path/to/file.conf "old1:new1"; "old2:new2"

Опции:
  --help    - показать эту справку
  --version - показать версию программы

Пример:
  conf /etc/nginx.conf "worker_processes:2" "worker_processes:4"

Создатель - """ + AUTHOR)

def print_version():
    print(f"conf version {VERSION}")

def process_replacements(file_path, replacements):
    # Проверка существования файла
    if not os.path.isfile(file_path):
        print(f"Ошибка: файл '{file_path}' не существует", file=sys.stderr)
        return False
    
    # Проверка прав на запись
    if not os.access(file_path, os.W_OK):
        print(f"Ошибка: нет прав на запись в файл '{file_path}'", file=sys.stderr)
        return False
    
    # Создание backup копии
    backup_path = file_path + ".bak"
    try:
        shutil.copy2(file_path, backup_path)
    except IOError as e:
        print(f"Ошибка при создании backup файла: {e}", file=sys.stderr)
        return False
    
    # Чтение и обработка файла
    try:
        with open(file_path, 'r') as f:
            lines = f.readlines()
        
        modified = False
        new_lines = []
        
        for line in lines:
            new_line = line
            # Пропускаем комментарии
            if not line.strip().startswith('#'):
                for old, new in replacements:
                    # Ищем точное совпадение (с учетом пробелов вокруг)
                    pattern = re.compile(r'(^|\s)' + re.escape(old) + r'(\s|$)')
                    if pattern.search(new_line):
                        new_line = pattern.sub(r'\1' + new + r'\2', new_line)
                        modified = True
            new_lines.append(new_line)
        
        if not modified:
            print("Предупреждение: не было сделано ни одной замены", file=sys.stderr)
            return True
        
        # Запись измененного файла
        with open(file_path, 'w') as f:
            f.writelines(new_lines)
            
    except IOError as e:
        print(f"Ошибка при обработке файла: {e}", file=sys.stderr)
        return False
    
    return True

def parse_replacements(args):
    replacements = []
    for arg in args:
        # Поддержка разделения через точку с запятой
        parts = arg.split(';')
        for part in parts:
            part = part.strip()
            if not part:
                continue
            if ':' not in part:
                print(f"Ошибка: некорректный формат замены '{part}'", file=sys.stderr)
                return None
            old, new = part.split(':', 1)
            replacements.append((old.strip(), new.strip()))
    return replacements

def main():
    if len(sys.argv) == 1 or '--help' in sys.argv:
        print_help()
        return
    
    if '--version' in sys.argv:
        print_version()
        return
    
    file_path = sys.argv[1]
    if not os.path.isfile(file_path):
        print(f"Ошибка: файл '{file_path}' не существует", file=sys.stderr)
        sys.exit(1)
    
    replacements = parse_replacements(sys.argv[2:])
    if replacements is None:
        sys.exit(1)
    
    if not replacements:
        print("Ошибка: не указаны замены", file=sys.stderr)
        sys.exit(1)
    
    if not process_replacements(file_path, replacements):
        sys.exit(1)

if __name__ == "__main__":
    main()

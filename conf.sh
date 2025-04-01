#!/bin/bash

function show_help() {
    help_text=$(cat <<EOF
Usage: $0 [--help] <file_path> <search_text> <replace_text>
Replace text in a file using sed

Arguments:
  file_path     Path to target file
  search_text   Text pattern to search (sed compatible)
  replace_text  Replacement text (sed compatible)

Example:
  $0 /etc/conf.conf 'web=1' 'web=2'

Note:
  - Use single quotes for arguments with special characters
  - Backup file before replacement
  - Delimiter | is used to avoid conflicts with /
by Konovalov Denis where.adm@gmail.com
---------------------------------------
Использование: $0 <файл> <что заменить> <на что заменить>
Замена текста в файле происходит с помощью sed

Аргументы:
  файл         Путь к целевому файлу
  искать       Шаблон для поиска (синтаксис sed)
  заменить     Текст замены (синтаксис sed)

Пример:
  conf /etc/conf.conf 'web=1' 'web=2'

Примечания:
  - Используйте одинарные кавычки для спецсимволов
  - Сделайте бэкап файла перед заменой
  - Разделитель | используется для избежания конфликтов с /
by Коновалов Денис where.adm@gmail.com
EOF
)
    echo "$help_text"
}

function change_text() {
    local file="$1"
    local search="$2"
    local replace="$3"
    
    [ ! -f "$file" ] && { echo "Error: File $file not found!" >&2; exit 2; }
    
    sed -i "s|${search}|${replace}|g" "$file" || {
        echo "Error: Replacement failed!" >&2
        exit 3
    }
    
    echo "Replacement successful in $file"
}

# Main script
[ "$1" == "--help" ] && { show_help; exit 0; }
[ $# -ne 3 ] && { echo "Error: Invalid arguments count!" >&2; show_help; exit 1; }

change_text "$1" "$2" "$3"

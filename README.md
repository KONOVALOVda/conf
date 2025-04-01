# conf - Утилита для редактирования конфигурационных файлов

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green.svg)

Простая утилита для безопасного редактирования конфигурационных файлов в Linux с поддержкой резервного копирования и множественных замен. Доступны реализации на Python и C++.

## 📌 Особенности

✔️ Поиск и замена параметров одной командой  
✔️ Автоматическое создание `.bak`-копий  
✔️ Поддержка множественных замен в одном вызове  
✔️ Игнорирование комментариев (строк с `#`)  
✔️ Проверка прав доступа к файлам  
✔️ Две реализации: Python 3.x и C++17  

## 🚀 Установка

### Требования
- Для Python версии: Python 3.x
- Для C++ версии: компилятор с поддержкой C++17 (g++/clang++)

### Сборка и установка
```bash
# Клонировать репозиторий
git clone https://github.com/KONOVALOVda/conf.git
cd conf

# Вариант 1: Использование Python версии
chmod +x conf.py
sudo cp conf.py /usr/local/bin/conf

# Вариант 2: Сборка и установка C++ версии
make
sudo make install
```

🛠 Использование
Базовый синтаксис

## 🛠 Использование

### Базовый синтаксис

Одичноное изменение
```bash
conf /путь/к/файлу.conf "старое_значение:новое_значение"
```


Массовое изменение
```bash
conf /путь/к/файлу.conf "param1:value1" "param2:value2"
conf /путь/к/файлу.conf "old1:new1"; "old2:new2"

```


Получение справки:
```bash
conf --help
conf --version
```

# conf - утилита для простого редактирования конфигурационных файлов

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green.svg)

Простая утилита для простого и безопасного редактирования конфигурационных файлов в Linux с поддержкой резервного копирования и множественных замен. Доступны реализации на Python и C++.

## 📌 Особенности

✔️ Поиск и замена параметров одной командой  
✔️ Автоматическое создание `.bak`-копий  
✔️ Поддержка множественных замен в одном вызове  
✔️ Игнорирование комментариев (строк с `#`)  
✔️ Проверка прав доступа к файлам  
✔️ Две реализации: Python 3.x и C++17  

## 🚀 Установка

### версия BASH

```bash
#после скачивания conf.sh
mv ./conf.sh ./conf
sudo chmod +x conf
sudo cp conf /usr/local/bin/
```

## 🛠 Использование

Если вы сделали установку (как указано выше) -

```bash
conf /путь/к/файлу.conf "старое_значение" "новое_значение"
```

Если не сделали установку, то простой запуск скрипта -


```bash
bash /путь/к/скрипту/conf.sh /путь/к/файлу.conf "старое_значение" "новое_значение"
```


Получение справки:
```bash
conf --help
./conf.sh --help
```

## версии PYTHON
- Для Python версии: Python 3.x

### Сборка и установка
```bash
# Клонировать репозиторий
git clone https://github.com/KONOVALOVda/conf.git
cd conf

# Вариант 1: Использование Python версии
chmod +x conf.py
sudo cp conf.py /usr/local/bin/conf
```

## 🛠 Использование

Если вы сделали установку (как указано выше) -

```bash
conf /путь/к/файлу.conf "старое_значение" "новое_значение"
```

Если не сделали установку, то простой запуск скрипта -


```bash
bash /путь/к/скрипту/conf.py /путь/к/файлу.conf "старое_значение" "новое_значение"
```


Получение справки:
```bash
conf --help
./conf.py --help
```

## версии C++
!ВЕРСИЯ ЕЩЕ В ДОРАБОТКЕ!

- Для C++ версии: компилятор с поддержкой C++17 (g++/clang++)

### Сборка и установка
```bash
# Клонировать репозиторий
git clone https://github.com/KONOVALOVda/conf.git
cd conf
make
sudo make install
```

## 🛠 Использование

### Базовый синтаксис PYTHON\C++

Одичноное изменение
```bash
conf /путь/к/файлу.conf "старое_значение:новое_значение"
```


Получение справки:
```bash
conf --help
conf --version
```

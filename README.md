# conf - утилита для простого редактирования конфигурационных файлов

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green.svg)

Простая утилита для простого и безопасного редактирования конфигурационных файлов в Linux с поддержкой резервного копирования и множественных замен. Доступны реализации на Python и C++.

## 📌 Особенности

✔️ Поиск и замена параметров одной командой  
✔️ Игнорирование комментариев (строк с `#`)  
✔️ Проверка прав доступа к файлам  
✔️ Три реализации: BASH, Python 3.x и C++17  

### версия BASH

## 🚀 Установка BASH версии

```bash
git clone https://github.com/KONOVALOVda/conf.git
cd conf
mv ./conf.sh ./conf
sudo chmod +x conf
sudo cp conf /usr/local/bin/
```

## 🛠 Использование BASH версии

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

## 🚀 Установка PYTHON версии

```bash
# Клонировать репозиторий
git clone https://github.com/KONOVALOVda/conf.git
cd conf

chmod +x conf.py
sudo cp conf.py /usr/local/bin/conf
```

## 🛠 Использование PYTHON версии

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

- Для C++ версии: компилятор с поддержкой C++17 (g++/clang++)

## 🚀 Установка C++ версии


```bash
# Клонировать репозиторий
git clone https://github.com/KONOVALOVda/conf.git
cd conf
g++ -std=c++11 -o confcpp conf.cpp
chmod +x confcpp
sudo cp confcpp /usr/local/bin/conf
conf --help
```

## 🛠 Использование C++ версии

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


## Если у вас есть вопросы или предложения по улучшению, пожалуйста, обращайтесь!

### by Коновалов Денис Александрович - where.adm@mail.ru

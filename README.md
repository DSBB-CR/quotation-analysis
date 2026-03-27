# quotation-analysis

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Bash](https://img.shields.io/badge/Shell-Bash-green.svg)](https://www.gnu.org/software/bash/)
[![curl](https://img.shields.io/badge/curl-libcurl-orange.svg)](https://curl.se/)

> Простой и элегантный инструмент для просмотра актуальных курсов валют от Центрального Банка России

## ✨ Особенности

- 🚀 **Быстрый доступ** к официальным курсам валют ЦБ РФ
- 🎨 **Цветное оформление** для удобного чтения
- 🇷🇺 Поддержка **русского языка** (Windows-1251 → UTF-8)
- 🔄 **Автоматическое обновление** данных
- 📊 **Красивый табличный вывод**

## 📋 Требования

- **Linux** / **macOS** / **WSL**
- **C++17** компилятор (g++ или clang++)
- **libcurl** библиотека
- **iconv** библиотека
- **Bash** 4.0+

### Установка зависимостей

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install g++ libcurl4-openssl-dev libiconv-hook-dev
```

#### Компиляция
```bash
g++ main.cpp -o programm -lcurl -liconv
clang++ main.cpp -o programm -lcurl -liconv
```
#### Примеры выполнения
- вывод курсов долларов и евро от Центрального Банка России

```bash
chmod +x ressault.sh
./ressault.sh
```

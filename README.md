# Генератор документации C/C++

## Суть проекта

Консольное приложение для автоматической генерации HTML-документации из исходного кода C/C++. Анализирует файлы (.cpp, .h), извлекает комментарии с тегами @param, @return, @brief и создаёт статический сайт.

## Сторонние библиотеки

- C++17 Standard Library (std::filesystem)
- Boost.Filesystem (опционально)

## Сборка и запуск

```bash
# Конфигурация
cmake -S . -B build -G "MinGW Makefiles"

# Сборка
cmake --build build

# Запуск
.\build\bin\DoxygenLite.exe .\src
```

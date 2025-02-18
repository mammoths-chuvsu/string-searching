# Библиотека алгоритмов поиска подстрок

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

Библиотека предоставляет реализацию различных алгоритмов поиска подстрок в тексте с возможностью сравнения их производительности. 
Поддерживается гибкая настройка через аргументы командной строки, выбор алгоритмов и детальный вывод результатов.

## Содержание
- [Основные возможности](#основные-возможности)
- [Установка и запуск](#установка-и-запуск)
- [Документация](#документация)
  - [Сравнение алгоритмов](#сравнение-алгоритмов)
  - [Архитектура](#архитектура)
- [Лицензия](#лицензия)

---

## Основные возможности
- **10+ алгоритмов** поиска подстрок, включая:
  - Наивный алгоритм (Brute Force)
  - Кнута-Морриса-Пратта (KMP)
  - Бойера-Мура (Boyer-Moore)
  - Ахо-Корасик (Aho-Corasick)
  - Суффиксные деревья и массивы
- **Сравнение алгоритмов** по времени выполнения, памяти и другим параметрам.
- **Модульная архитектура** для легкого добавления новых алгоритмов.

---

## Установка и запуск

Зависимости для сборки: 

- Компилятор с поддержкой C++20
- CMake ≥ 3.20

Чтобы собрать и запустить симулятор, откройте терминал и выполните следующие команды:
```bash 
cmake -Ssimulator/ -Bbuild/simulator 
cmake --build build/simulator
./simulator/bin/run-simulator --help
```

Чтобы собрать пакет с библиотекой string-searching, выполните следующее:
```bash 
cmake -S. -Bbuild/string-searching
cmake --build build/string-searching
```
После этого можно использовать библиотеку через `find_package(string-searching)` в CMake внутри вашего проекта.

Для генерации документации используется **Doxygen**:

```bash
doxygen docs/doxygen.config
```

Документация появится в `docs/html`.

---

## Документация

### Сравнение алгоритмов
Полная таблица с асимптотикой, описанием и рекомендациями доступна в [отдельном файле](docs\algorithms.md).
Ключевые параметры:

- Временная сложность (средняя и худшая)
- Требования к памяти
- Поддержка множественных паттернов

### Архитектура
Описание компонентов библиотеки и их взаимодействия — в [документации по архитектуре](docs\arhcitecture.md).
Основные модули:

- `BaseSubstringSearcher` - базовый класс для алгоритмов.
- `ArgumentParser` — обработка аргументов.
- `AlgorithmsCreator` — фабрика алгоритмов.
- `Simulator` — экспериментальное окружение.

---

## Лицензия

Проект распространяется под лицензией MIT. Подробнее см. [LICENSE](LICENSE).
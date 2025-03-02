# Инструкция по добавлению пользовательского алгоритма в симулятор

Чтобы добавить свой алгоритм в симулятор, выполните следующие шаги:

## 1. Создание наследника `BaseSubstringSearcher`

В файлах (имя выберите свое) `include/string-searching/my_substring_searcher.hpp` и `src/my_substring_searcher.cpp` создайте класс наследник `BaseSubstringSearcher` (находится в файле `include/string-searching/base_substring_searcher.hpp`), реализующий ваш алгоритм.

## 2. Изменение файла `algorithms_creator.cpp`

- Перейдите в файл `simulator/src/algorithms_creator.cpp`.
- В методе `CreateAlgorithms`, внутри инициализации переменной `factory_map`, добавьте следующую запись:
```cpp
  {"algorithm name", []() { return std::make_unique<MyAlgorithm>(); }
```

- Убедитесь, что вы добавили директиву `#include` для вашего заголовочного файла.

## 3. Обновление тестового файла `simulator_benchmark_test.cpp`

- Перейдите в файл `simulator/tests/src/simulator_benchmark_test.cpp`.
- В методе `SetUp()`, добавьте ваш алгоритм в список тестируемых алгоритмов, чтобы включить ваш алгоритм в процесс тестирования.

## 4. Изменение тестового сценария в `simulator_benchmark_test.py`

- Откройте файл `simulator/tests/src/simulator_benchmark_test.py`.
- Добавьте название вашего алгоритма в список `ALGORITHMS`. Это необходимо для автоматического тестирования и бенчмаркинга вашего алгоритма.

## 5. Обновление тестового файла `basic_substring_test.cpp`

- Откройте файл `tests/unit/src/basic_substring_test.cpp`.
- В шаблонные параметры определения типа `Algorithms` добавьте свой класс.

## 6. Стиль кода

- Убедитесь, что ваш код соответствует стилевым рекомендациям Google. Это включает соблюдение стандартов форматирования, соглашений о наименованиях и других аспектов, указанных в [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

Следуя этим шагам, вы сможете интегрировать свой алгоритм и обеспечить его корректное тестирование и бенчмаркинг в системе симулятора. Соблюдайте требования к стилю кода для поддержания читаемости и поддержки кода на высоком уровне.
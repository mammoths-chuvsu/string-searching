# string-searching

## Сравнение алгоритмов

- $|\Sigma| = \sigma$­ — размер алфавита
- $|text| = t$ — длина текста
- $|pattern| = p$ — длина паттерна
- $a$ — размер ответа (кол-во пар)
- $m$ — суммарная длина всех паттернов

| Название                                                               |  Среднее             |  Худшее                                      | Препроцессинг    |  Дополнительная память    |  Кол-во поисковых шаблонов    |  Порядок сравнения    |  Описание                                                                                                                                                                                                                                                                                                                           |
|------------------------------------------------------------------------|----------------------|----------------------------------------------|------------------|---------------------------|-------------------------------|-----------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Наивный алгоритм  (Brute Force algorithm)                              | $O(p \cdot (t - p))$ | $O(t^2)$                                   |                  | $O(1)$                  | Single                        | Прямой                | Если $p$ достаточно мало по сравнению с $t$, то асимптотика будет близкой к $O(t)$, что позволяет использовать его на практике в случаях, когда паттерн много меньше текста (например, Ctrl+F в браузерах)                                                                                               |
| Поиск подстроки в строке с помощью Z-функции                           | $O(t)$               | $O(t)$                                     | $O(p+t)$     | $O(p)$                  | Single                        | Прямой                | Использует Z-функцию                                                                                                                                                                                                                                                                                                                                    |
| Алгоритм Рабина-Карпа  (Karp-Rabin algorithm)                          | $O(p+t)$         | $O(pt)$                                   | $O(p)$         | $O(1)$                  | Single / Finite               | Прямой                | Данный алгоритм использует хэширование, что снижает скорость в среднем. Можно модифицировать для поиска нескольких паттернов                                                                                                                                                                                                        |
| Алгоритм Кнута-Морриса-Пратта  (Knuth-Morris-Pratt algorith)           | $O(p+t)$         | $O(p+t)$                                 | $O(p)$         | $O(p)$                  | Single                        | Прямой                | Использует  префикс-функцию                                                                                                                                                                                                                                                                                                         |
| Алгоритм Колусси  (Colussi algorithm)                                  | $O(t)$             | $O(t)$                                     | $O(p)$         | $O(p)$                  | Single                        | Прямой / Обратный     | Оптимизация  Алгоритма Кнута-Морриса-Пратта использует как прямой, так и обратный обход                                                                                                                                                                                                                                             |
| Алгоритм Ахо-Корасик  (Aho–Corasick string matching algorithm)         | $O(m+t+a)$     | $O(t)$                                     | $O(m)$         | $O(m\sigma)$                | Finite                        | Прямой                | Строит конечный автомат. Можно хранить таблицу переходов как индексный массив (array), а можно как Красно-черное дерево. В последнем случае уменьшится расход памяти, но ухудшится асимптотика                                                                                                                                      |
| Алгоритм Shift-Or                                                      | $O(t)$             | $O(t\cdot\frac{n}{w})$, где $w$ — размер машинного слова | $O(p+\sigma)$     | $O(p+\sigma)$              | Single                        | Прямой                | Использует тот факт, что в современных процессорах битовые сдвиг и или являются атомарными. Эффективен, если $p\le w$. Иначе деградирует и по памяти, и по сложности                                                                                                                                                                  |
| Алгоритм Бойера-Мура  (Boyer-Moore algorithm)                          | $O(t)$             | $O(pt)$                                   | $O(p+\sigma)$     | $O(p+\sigma)$              | Single                        | Обратный              | Считается наиболее быстрым из алгоритмов общего назначения. Использует эвристики. Существует большое количество оптимизаций                                                                                                                                                                                                      |
| Поиск подстроки в строке с помощью суффиксного массива  (Suffix array) | $O(p\log t)$    | $O(p\log t)$                            | $O(t)$         | $O(t)$                  | Single                        | Прямой                | Использует Суффиксный массив. Если использовать  Largest common prefix (lcp), то можно уменьшить асимптотику до $O(p+\log t)$. Суффиксный массив можно строить стандартными способами или  алгоритмом Карккайнена-Сандерса. Асимптотика приведена для построения суффиксного массива с помощью алгоритма Карккайнена-Сандерса |
| Поиск подстроки в строке с помощью суффиксного дерева  (Suffix tree)   | $O(p)$             | $O(p)$                                     | $O(t)$         | $O(t)$                  | Single                        | Прямой                | Позволяет выполнять поиск подстроки в строке за линейное время                                                                                                                                                                                                                                                                      |

## Архитектура библиотеки и среды исполнения

![Архитектура](docs/images/architecture.png)

Пользователь запускает программу с аргументами командной строки.\
Создается объект `ArgumentParser`, который разбирает аргументы командной строки.\
Вызывается метод `GetAlgorithms` класса `ArgumentParser`, который создает и возвращает вектор алгоритмов.\
Вызывается метод `GetSubstring` класса `ArgumentParser`, который возвращает подстроку для поиска.\
Вектор алгоритмов передается в конструктор `Simulator`.\
Вызывается метод `Run`, принимающий искомую подстроку, класса `Simulator`.

Для каждого алгоритма в векторе `algorithms_`:
- Вызывается метод `Contains` для поиска подстроки.
- Результаты (время выполнения, успешность поиска) записываются.
- Результаты сравниваются и выводятся пользователю.

Некоторые алгоритмы могут использовать общие структуры данных, такие как `PolynomialHashFunction`, `SuffixArray` или `SuffixTree`. Эти структуры создаются и управляются внутри соответствующих алгоритмов.

## Задание 

https://classroom.github.com/a/j7Pxe7D5

Вам предстоит реализовать алгоритм сжатия Барроуза-Уилера. Данный алгоритм прост в реализации, не защищен патентами, а также превосходит по качеству сжатия gzip и PKZIP. Данный алгоритм лежит в основе Unix утилиты по сжатию данных bzip2.

Алгоритм сжатия данных Барроуза-Уилера состоит из трех частей, которые выполняются последовательно:
1. _Преобразование Барроуза-Уилера._ На вход подается текстовый файл на английском языке. Входной файл преобразуется в текстовый файл, в котором есть последовательности с одинаковыми символами, встречающимися несколько раз подряд.
2. _Перемещение к началу._ Текстовый файл с последовательностями одинаковых символов преобразуется в текстовый файл, в котором определенные символы встречаются чаще других.
3. _Алгоритм сжатия Хаффмана._ К текстовому файлу, в котором определенные символы встречаются чаще других, применяется алгоритм сжатия, который заменяет часто встречающиеся символы на короткие кодовые слова, а редкие символы в длинные кодовые слова.

Третий этап, на котором непосредственно происходит сжатие, является эффективным, так как после первого и второго этапа получается текстовый файл, в котором определенные символы встречаются намного чаще других. Для того, чтобы декодировать текстовый файл, необходимо произвести действия алгоритма в обратном порядке: применить декомпрессию Хаффмана, произвести перемещение к началу и произвести обратное преобразование Барроуза-Уилера. Вам необходимо эффективно реализовать преобразование Барроуза-Уилера и алгоритм перемещения к началу. 

**Алгоритм сжатия/декомпрессии Хаффмана реализовывать не требуется**. Вы воспользуетесь уже готовым решением.

### Алгоритм перемещения к началу
Основная идея алгоритма перемещения к началу заключается в поддержании упорядоченной последовательности символов алфавита и последовательном символьном чтении входного текста. Как только прочитан символ входного текста, определяется позиция, на которой встречается данный символ. Далее прочитанный символ перемещается в начало символьной цепочки. Позиция следующего входного символа уже определяется с использованием модифицированной цепочки символов. 

Рассмотрим пример, где в качестве начальной упорядоченной цепочки символов рассматривается алфавит из 6-ти символов: A, B, C, D, E, F. Требуется закодировать входную строку CAAABCCCACCF. Изначальная упорядоченная цепочка будет обновляться шаг за шагом, когда новый входной символ будет размещен в начале цепочки.

move-to-front | in | out
------------- | -- | ---
 A B C D E F | C | 2 
 C A B D E F | A | 1
 A C B D E F | A | 0
 A C B D E F | A | 0
 A C B D E F | B | 2
 B A C D E F | C | 2
 C B A D E F | C | 0
 C B A D E F | C | 0
 C B A D E F | A | 2
 A C B D E F | C | 1
 C A B D E F | C | 0
 C A B D E F | F | 5
 F C A B D E  

Отметим, что если один и тот же символ встречается во входной строке много раз, то значения в колонке _out_ будут небольшими целыми числами. Очень высокая частота некоторых символов будет идеальным сценарием для алгоритма сжатия Хаффмана.

Далее в качестве примера будет рассматриваться текстовый файл _abra.txt_:
```
$ cat abra.txt
ABRACADABRA!
```

#### Перемещение к началу, этап кодирования.
Вам предстоит работать с расширенной ASCII таблицей, состоящей из 256 символов. Инициализируйте стартовую последовательность символов, поставив на _i-е_ место _i-й_ символ из расширенной ASCII таблицы. Далее, получив на вход 8-ми битный символ с, напечатайте индекс считанного символа с в текущей последовательности, а потом переместите символ c с его текущего места в начало последовательности.
```
$ moveToFront.out -e abra.txt abra.out
```

#### Перемещение к началу, этап декодирования.
Инициализируйте стартовую последовательность символов, поставив на _i-е_ место _i-й_ символ из расширенной ASCII таблицы. Прочитайте 8-ми битный символ _с_, преобразуйте его в число от 0 до 255, напечатайте _с-й_ символ из последовательности, а потом переместите в последовательности _с-й_ символ в начало. Проверьте, что после декодирования, полученная строка совпадает с исходной строкой.
```
$ moveToFront.out -d abra.out
ABRACADABRA!
```

Вам предлагается реализовать класс _MoveToFront_, где каждый из методов соответствует этапу алгоритма перемещения к началу.
```cpp
struct MoveToFront
{
   // Этап кодирования
   void encode(std::istream& input, std::ostream& output);
   
   // Этап декодирования
   void decode(std::istream& input, std::ostream& output);
};
```
_Сложность._ Если _R_ мощность алфавита, а _N_ количество символов во входном файле, то по времени алгоритм перемещения к началу должен работать за _O(R * N)_ и за _O(R + N)_ по памяти.

### Суффиксный массив
Для того, чтобы эффективно реализовать преобразование Барроуза-Уилера необходимо воспользоваться суффиксным массивом — лексикографически отсортированным массивом всех суффиксов строки. Например, рассмотрим строку "ABRACADABRA!". В таблице ниже представлены 12 суффиксов рассматриваемой строки. Далее представлены отсортированные суффиксы.

 i |     Original Suffixes    |    Sorted Suffixes      | index[i]
-- | ----------------------- | ----------------------- | --------
 0 | A B R A C A D A B R A ! | ! A B R A C A D A B R A | 11
 1 | B R A C A D A B R A ! A | A ! A B R A C A D A B R | 10
 2 | R A C A D A B R A ! A B | A B R A ! A B R A C A D | 7
 3 | A C A D A B R A ! A B R | A B R A C A D A B R A ! | 0
 4 | C A D A B R A ! A B R A | A C A D A B R A ! A B R | 3
 5 | A D A B R A ! A B R A C | A D A B R A ! A B R A C | 5
 6 | D A B R A ! A B R A C A | B R A ! A B R A C A D A | 8
 7 | A B R A ! A B R A C A D | B R A C A D A B R A ! A | 1
 8 | B R A ! A B R A C A D A | C A D A B R A ! A B R A | 4
 9 | R A ! A B R A C A D A B | D A B R A ! A B R A C A | 6
10 | A ! A B R A C A D A B R | R A ! A B R A C A D A B | 9
11 | ! A B R A C A D A B R A | R A C A D A B R A ! A B | 2

Значение _i-го_ элемента массива _index[i]_ соответствует позиции суффикса в исходном массиве, который встречается на _i-м_ месте в отсортированном массиве. Это значит, что если _index[11] = 2_, то суффикс, который в отсортированном массиве находится на _11-м_ месте, в исходном массиве находится на _2-м_ месте.

Вам необходимо реализовать суффиксный массив, реализовав класс _CircularSuffixArray_:
```cpp
struct CircularSuffixArray
{
   // Ctor
   CircularSuffixArray(const std::string& input);
  
   // Returns size of the input string
   size_t size() const;

   // Returns index of suffix from original array
   size_t operator[](size_t n) const;
};
```

_Сложность._ Конструктор за время _O(N * log N)_, метод size и оператор [ ] за константное время. По памяти за _O(R + N)_.

### Преобразование Барроуза-Уилера.
Основная цель преобразования Барроуза-Уилера заключается в том, чтобы преобразовать входные данные так, чтобы последующий алгоритм сжатия отработал эффективно. Алгоритм переставляет символы входного сообщения так, чтобы получить последовательности повторяющихся символов, но при условии, что преобразованные входные данные можно привести к изначальному виду.

#### Преобразование Барроуза-Уилера, этап кодирования
Преобразование Барроуза-Уилера строки _s_ длины _N_ определяется следующим образом: рассмотрим результат сортировки всех суффиксов строки _s_. Преобразование Барроуза-Уилера это последний столбец в отсортированном массиве суффиксов _t[]_, которому предшествует индекс строки, соответствующей изначальной строке в отсортированном массиве. Рассмотрим пример со строкой "ABRACADABRA!":

 i |   Original Suffixes     |    Sorted Suffixes     | t |    index[i]
-- | ----------------------- |  ----------------------| - | --------
 0 |  A B R A C A D A B R A ! |  ! A B R A C A D A B R | A  | 11
 1 |  B R A C A D A B R A ! A |  A ! A B R A C A D A B | R  | 10
 2 |  R A C A D A B R A ! A B |  A B R A ! A B R A C A | D  | 7
*3 |  A C A D A B R A ! A B R |  A B R A C A D A B R A | !  | *0
 4 |  C A D A B R A ! A B R A |  A C A D A B R A ! A B | R  | 3
 5 |  A D A B R A ! A B R A C |  A D A B R A ! A B R A | C  | 5
 6 |  D A B R A ! A B R A C A |  B R A ! A B R A C A D | A  | 8
 7 |  A B R A ! A B R A C A D |  B R A C A D A B R A ! | A  | 1
 8 |  B R A ! A B R A C A D A |  C A D A B R A ! A B R | A  | 4
 9 |  R A ! A B R A C A D A B |  D A B R A ! A B R A C | A  | 6
10 |  A ! A B R A C A D A B R |  R A ! A B R A C A D A | B  | 9
11 |   ! A B R A C A D A B R A |  R A C A D A B R A ! A | B  | 2

В столбце _t[]_ выделены результаты преобразование Барроуза-Уилера. Так как исходная строка "ABRACADABRA!" оказалась на _3-й_ строке, то требуемый индекс равен _3_.

Рассмотрим результат преобразование Барроуза-Уилера:
```
3
ARD!RCAAAABB
```
Заметим, что в получившейся строке 4 раза повторяется символ A и 2 раза повторяется символ B. Эти подпоследовательности делают получившуюся строку удобной для сжатия.

#### Преобразование Барроуза-Уилера, этап декодирования
Нам необходимо совершить обратное преобразование и трансформировать закодированную строку в исходную. Если _j-й_ исходный суффикс является _i-м_ суффиксом в отсортированном массиве мы считаем, что значение _next[i]_ это строка в отсортированном массиве, где встречается _(j+1)-й_ суффикс исходного массива. Например, если _first_ это строка, где располагается исходная входная строка, то _next[first]_ это индекс сортированного массива суффиксов, где встречается первый суффикс исходной строки (исходная строка, сдвинутая на 1 символ влево); _next[next[first]]_ - индекс отсортированного массива суффиксов, где встречается второй суффикс исходной строки, и так далее.

Декодирование строки при помощи массива _t[]_,  массива _next[]_ и индекса _first_. Использую массив _t[]_ мы сможем определить, какие символы располагаются в первом столбце отсортированных суффиксов, так как это те же символы из массива _t[]_, только отсортированные.

 i |  Sorted Suffixes       | t | next
-- | ---------------------- | - | ----
 0 | ! ? ? ? ? ? ? ? ? ? ?  | A |  3
 1 | A ? ? ? ? ? ? ? ? ? ?  | R |  0
 2 | A ? ? ? ? ? ? ? ? ? ?  | D |  6
*3 | A ? ? ? ? ? ? ? ? ? ?  | ! |  7
 4 | A ? ? ? ? ? ? ? ? ? ?  | R |  8
 5 | A ? ? ? ? ? ? ? ? ? ?  | C |  9
 6 | B ? ? ? ? ? ? ? ? ? ?  | A |  10
 7 | B ? ? ? ? ? ? ? ? ? ?  | A |  11
 8 | C ? ? ? ? ? ? ? ? ? ?  | A |  5
 9 | D ? ? ? ? ? ? ? ? ? ?  | A |  2
10 | R ? ? ? ? ? ? ? ? ? ?  | B |  1
11 | R ? ? ? ? ? ? ? ? ? ?  | B |  4

Далее, используя массив _next[]_ и индекс _first_ можно восстановить исходную строку, так как первый символ _i-го_ исходного суффикса является _i-м_ символов исходной строки. В рассматриваемом примере индекс _first_ равен _3_, что значит, что исходная строка в отсортированном массиве суффиксов встречается под _3-м_ индексом. Мы можем сделать вывод, что первый символ исходной строки равен _‘А’_, а последний _‘!’_. Заметим, что _next[first] = 7_, что значит, что следующий по порядку суффикс (исходная строка, сдвинутая на _1_ символ влево) встречается под _7-м_ индексом. Это значит, что второй символ исходной строки это _‘B’_. Далее, _next[next[first]] = 11_, поэтому _3-й_ символ исходной строки равен _‘R’_.

Формирование массива _next[]_ на основе массива _t[]_ и индекса _first_. Легко определить элемент _next[]_ для символа, который встречается в исходной строке только один раз. Рассмотрим суффикс, который начинается с символа _‘C’_. Просматривая первую колонку, мы замечаем его на _8-й_ строчке отсортированного массива суффиксов. Следующий суффикс после данного (в исходном массиве) имеет символ _‘C’_ в конце. Это верно для _5-й_ строчки, поэтому _next[8] = 5_. Аналогично можно определить значение _next[]_ для символов _‘D’_ и _‘!’_, _next[9] = 2_ и _next[0] = 3_.

 i  |    Sorted Suffixes     | t   |   next
--  | ---------------------- | -   |  ----
 0  |  ! ? ? ? ? ? ? ? ? ? ? | A   |     3
 1  |  A ? ? ? ? ? ? ? ? ? ? | R   |
 2  |  A ? ? ? ? ? ? ? ? ? ? | D   |
*3  |  A ? ? ? ? ? ? ? ? ? ? | !   |
 4  |  A ? ? ? ? ? ? ? ? ? ? | R   |
 5  |  A ? ? ? ? ? ? ? ? ? ? | C   |
 6  |  B ? ? ? ? ? ? ? ? ? ? | A   |
 7  |  B ? ? ? ? ? ? ? ? ? ? | A   |
 8  |  C ? ? ? ? ? ? ? ? ? ? | A   |     5
 9  |  D ? ? ? ? ? ? ? ? ? ? | A   |    2
10  |  R ? ? ? ? ? ? ? ? ? ? | B   |
11  |  R ? ? ? ? ? ? ? ? ? ? | B   |

Однако, если символ встречается с исходной строке несколько раз, то однозначно определить значение _next[]_ не получается. Однако, есть правило, которое позволяет справиться с неоднозначностью: eсли строки _i_ и _j_ в отсортированном массиве начинаются с одного символа и _i < j_, то _next[i] < next[j]_.

Например, если рассмотреть символ _‘R’_, то можно заметить, что он встречается на первом месте в строках _10_ и _11_. На последнем месте данный символ встречается в строках с индексами _1_ и _4_. Так как _10 < 11_, то _next[10] = 1_ и _next[11] = 4_.

Почему данное правило работает? Так как суффиксы отсортированы, то получается, что лексикографически суффикс под индексом _10_ меньше, чем суффикс под индексом _11_. Поэтому неизвестные символы из суффикса под индексом _10_ должны быть лексикографически меньше неизвестных символов суффикса под индексом _11_. Кроме этого, мы знаем, что из 2-х суффиксов, заканчивающихся на _‘R’_ (суффиксы с индексами _1_ и _4_), суффикс _1_ лексикографически меньше суффикса _4_. Но неизвестные символы из суффиксов _10_ и _11_ это те самые неизвестные символы из суффиксов _1_ и _4_. Поэтому и получается, что _next[10] = 1_ и _next[11] = 4_.

Реализуйте преобразование Барроуза-Уилера:
```cpp
struct BWT
{
   // Преобразование Барроуза-Уилера, этап кодирования
   void transform(std::istream& input, std::ostream& output);
   
   // Обратное преобразование Барроуза-Уилера, этап декодирования
   void inverseTransform(std::istream& input, std::ostream& output);
};
```

_Сложность._ Преобразование и обратное преобразование за _O(N + R)_ по времени и за _O(N + R)_ по памяти.

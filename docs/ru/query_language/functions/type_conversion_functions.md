# Функции преобразования типов

## Общие проблемы преобразования чисел {#numeric-conversion-issues}

При преобразовании значения из одного типа в другой необходимо помнить, что в общем случае это небезопасная операция, которая может привести к потере данных. Потеря данных может произойти при попытке сконвертировать тип данных значения от большего к меньшему или при конвертировании между различными классами типов данных.

Поведение ClickHouse при конвертировании похоже на [поведение C++ программ](https://en.cppreference.com/w/cpp/language/implicit_conversion).

## toInt(8|16|32|64)

Преобразует входное значение к типу [Int](../../data_types/int_uint.md). Семейство функций включает:

* `toInt8(expr)` — возвращает значение типа `Int8`.
* `toInt16(expr)` — возвращает значение типа `Int16`.
* `toInt32(expr)` — возвращает значение типа `Int32`.
* `toInt64(expr)` — возвращает значение типа `Int64`.

**Параметры**

- `expr` — [выражение](../syntax.md#syntax-expressions) возвращающее число или строку с десятичным представление числа. Бинарное, восьмеричное и шестнадцатеричное представление числа не поддержаны. Ведущие нули обрезаются.

**Возвращаемое значение**

Целое число типа `Int8`, `Int16`, `Int32` или `Int64`.

Функции используют [округление к нулю](https://en.wikipedia.org/wiki/Rounding#Rounding_towards_zero), т.е. обрезают дробную часть числа.

Поведение функций для аргументов [NaN и Inf](../../data_types/float.md#data_type-float-nan-inf) не определено. При использовании функций помните о возможных проблемах при [преобразовании чисел](#numeric-conversion-issues).

**Пример**

```sql
SELECT toInt64(nan), toInt32(32), toInt16('16'), toInt8(8.8)
```
```text
┌─────────toInt64(nan)─┬─toInt32(32)─┬─toInt16('16')─┬─toInt8(8.8)─┐
│ -9223372036854775808 │          32 │            16 │           8 │
└──────────────────────┴─────────────┴───────────────┴─────────────┘
```

## toInt(8|16|32|64)OrZero

Принимает аргумент типа String и пытается его распарсить в Int(8|16|32|64). Если не удалось - возвращает 0.

**Пример**

```sql
select toInt64OrZero('123123'), toInt8OrZero('123qwe123')
```
```text
┌─toInt64OrZero('123123')─┬─toInt8OrZero('123qwe123')─┐
│                  123123 │                         0 │
└─────────────────────────┴───────────────────────────┘
```


## toInt(8|16|32|64)OrNull

Принимает аргумент типа String и пытается его распарсить в Int(8|16|32|64). Если не удалось - возвращает NULL.

**Пример**

```sql
select toInt64OrNull('123123'), toInt8OrNull('123qwe123')
```
```text
┌─toInt64OrNull('123123')─┬─toInt8OrNull('123qwe123')─┐
│                  123123 │                      ᴺᵁᴸᴸ │
└─────────────────────────┴───────────────────────────┘
```


## toUInt(8|16|32|64)

Преобраует входное значение к типу [UInt](../../data_types/int_uint.md). Семейство функций включает:

* `toUInt8(expr)` — возвращает значение типа `UInt8`.
* `toUInt16(expr)` — возвращает значение типа `UInt16`.
* `toUInt32(expr)` — возвращает значение типа `UInt32`.
* `toUInt64(expr)` — возвращает значение типа `UInt64`.

**Параметры**

- `expr` — [выражение](../syntax.md#syntax-expressions) возвращающее число или строку с десятичным представление числа. Бинарное, восьмеричное и шестнадцатеричное представление числа не поддержаны. Ведущие нули обрезаются.

**Возвращаемое значение**

Целое число типа `UInt8`, `UInt16`, `UInt32` или `UInt64`.

Функции используют [округление к нулю](https://en.wikipedia.org/wiki/Rounding#Rounding_towards_zero), т.е. обрезают дробную часть числа.

Поведение функций для аргументов [NaN и Inf](../../data_types/float.md#data_type-float-nan-inf) не определено. Если передать строку, содержащую отрицательное число, например `'-32'`, ClickHouse генерирует исключение. При использовании функций помните о возможных проблемах при [преобразовании чисел](#numeric-conversion-issues).

**Пример**

```sql
SELECT toUInt64(nan), toUInt32(-32), toUInt16('16'), toUInt8(8.8)
```
```text
┌───────toUInt64(nan)─┬─toUInt32(-32)─┬─toUInt16('16')─┬─toUInt8(8.8)─┐
│ 9223372036854775808 │    4294967264 │             16 │            8 │
└─────────────────────┴───────────────┴────────────────┴──────────────┘
```

## toUInt(8|16|32|64)OrZero

## toUInt(8|16|32|64)OrNull

## toFloat(32|64)

## toFloat(32|64)OrZero

## toFloat(32|64)OrNull

## toDate

## toDateOrZero

## toDateOrNull

## toDateTime

## toDateTimeOrZero

## toDateTimeOrNull

## toDecimal(32|64|128)

Преобразует `value` к типу данных [Decimal](../../data_types/decimal.md) с точностью `S`. `value` может быть числом или строкой. Параметр `S` (scale) задаёт число десятичных знаков.

- `toDecimal32(value, S)`
- `toDecimal64(value, S)`
- `toDecimal128(value, S)`

## toDecimal(32|64|128)OrNull

Преобразует входную строку в значение с типом данных [Nullable (Decimal (P, S))](../../data_types/decimal.md). Семейство функций включает в себя:

- `toDecimal32OrNull(expr, S)` — Возвращает значение типа `Nullable(Decimal32(S))`.
- `toDecimal64OrNull(expr, S)` — Возвращает значение типа `Nullable(Decimal64(S))`.
- `toDecimal128OrNull(expr, S)` — Возвращает значение типа `Nullable(Decimal128(S))`.

Эти функции следует использовать вместо функций `toDecimal*()`, если при ошибке обработки входного значения вы хотите получать `NULL` вместо исключения.

**Параметры**

- `expr` — [выражение](../syntax.md#syntax-expressions), возвращающее значение типа [String](../../data_types/string.md). ClickHouse ожидает текстовое представление десятичного числа. Например, `'1.111'`.
- `S` — количество десятичных знаков в результирующем значении.

**Возвращаемое значение**

Значение типа `Nullable(Decimal(P,S))`. Значение содержит:

- Число с `S` десятичными знаками, если ClickHouse распознал число во входной строке.
- `NULL`, если ClickHouse не смог распознать число во входной строке или входное число содержит больше чем `S` десятичных знаков.

**Примеры**

```sql
SELECT toDecimal32OrNull(toString(-1.111), 5) AS val, toTypeName(val)
```

```text
┌──────val─┬─toTypeName(toDecimal32OrNull(toString(-1.111), 5))─┐
│ -1.11100 │ Nullable(Decimal(9, 5))                            │
└──────────┴────────────────────────────────────────────────────┘
```

```sql
SELECT toDecimal32OrNull(toString(-1.111), 2) AS val, toTypeName(val)
```

```text
┌──val─┬─toTypeName(toDecimal32OrNull(toString(-1.111), 2))─┐
│ ᴺᵁᴸᴸ │ Nullable(Decimal(9, 2))                            │
└──────┴────────────────────────────────────────────────────┘
```

## toDecimal(32|64|128)OrZero

Преобразует тип входного значения в [Decimal (P, S)](../../data_types/decimal.md). Семейство функций включает в себя:

- `toDecimal32OrZero( expr, S)` — возвращает значение типа `Decimal32(S)`.
- `toDecimal64OrZero( expr, S)` — возвращает значение типа `Decimal64(S)`.
- `toDecimal128OrZero( expr, S)` — возвращает значение типа `Decimal128(S)`.

Эти функции следует использовать вместо функций `toDecimal*()`, если при ошибке обработки входного значения вы хотите получать `0` вместо исключения.

**Параметры**

- `expr` — [выражение](../syntax.md#syntax-expressions), возвращающее значение типа [String](../../data_types/string.md). ClickHouse ожидает текстовое представление десятичного числа. Например, `'1.111'`.
- `S` — количество десятичных знаков в результирующем значении.

**Возвращаемое значение**

Значение типа `Nullable(Decimal(P,S))`. `P` равно числовой части имени функции. Например, для функции `toDecimal32OrZero`, `P = 32`. Значение содержит:

- Число с `S` десятичными знаками, если ClickHouse распознал число во входной строке.
- 0 c `S` десятичными знаками, если ClickHouse не смог распознать число во входной строке или входное число содержит больше чем `S` десятичных знаков.

**Пример**

```sql
SELECT toDecimal32OrZero(toString(-1.111), 5) AS val, toTypeName(val)
```

```text
┌──────val─┬─toTypeName(toDecimal32OrZero(toString(-1.111), 5))─┐
│ -1.11100 │ Decimal(9, 5)                                      │
└──────────┴────────────────────────────────────────────────────┘
```

```sql
SELECT toDecimal32OrZero(toString(-1.111), 2) AS val, toTypeName(val)
```

```text
┌──val─┬─toTypeName(toDecimal32OrZero(toString(-1.111), 2))─┐
│ 0.00 │ Decimal(9, 2)                                      │
└──────┴────────────────────────────────────────────────────┘
```

## toString

Функции преобразования между числами, строками (но не фиксированными строками), датами и датами-с-временем.
Все эти функции принимают один аргумент.

При преобразовании в строку или из строки, производится форматирование или парсинг значения по тем же правилам, что и для формата TabSeparated (и почти всех остальных текстовых форматов). Если распарсить строку не удаётся - кидается исключение и выполнение запроса прерывается.

При преобразовании даты в число или наоборот, дате соответствует число дней от начала unix эпохи.
При преобразовании даты-с-временем в число или наоборот, дате-с-временем соответствует число секунд от начала unix эпохи.

Форматы даты и даты-с-временем для функций toDate/toDateTime определены следующим образом:

```text
YYYY-MM-DD
YYYY-MM-DD hh:mm:ss
```

В качестве исключения, если делается преобразование из числа типа UInt32, Int32, UInt64, Int64 в Date, и если число больше или равно 65536, то число рассматривается как unix timestamp (а не как число дней) и округляется до даты. Это позволяет поддержать распространённый случай, когда пишут toDate(unix_timestamp), что иначе было бы ошибкой и требовало бы написания более громоздкого toDate(toDateTime(unix_timestamp))

Преобразование между датой и датой-с-временем производится естественным образом: добавлением нулевого времени или отбрасыванием времени.

Преобразование между числовыми типами производится по тем же правилам, что и присваивание между разными числовыми типами в C++.

Дополнительно, функция toString от аргумента типа DateTime может принимать второй аргумент String - имя тайм-зоны. Пример: `Asia/Yekaterinburg` В этом случае, форматирование времени производится согласно указанной тайм-зоне.

```sql
SELECT
    now() AS now_local,
    toString(now(), 'Asia/Yekaterinburg') AS now_yekat
```

```text
┌───────────now_local─┬─now_yekat───────────┐
│ 2016-06-15 00:11:21 │ 2016-06-15 02:11:21 │
└─────────────────────┴─────────────────────┘
```

Также смотрите функцию `toUnixTimestamp`.

## toFixedString(s, N)

Преобразует аргумент типа String в тип FixedString(N) (строку фиксированной длины N). N должно быть константой.
Если строка имеет меньше байт, чем N, то она дополняется нулевыми байтами справа. Если строка имеет больше байт, чем N - кидается исключение.

## toStringCutToZero(s)

Принимает аргумент типа String или FixedString. Возвращает String, вырезая содержимое строки до первого найденного нулевого байта.

Пример:

```sql
SELECT toFixedString('foo', 8) AS s, toStringCutToZero(s) AS s_cut
```

```text
┌─s─────────────┬─s_cut─┐
│ foo\0\0\0\0\0 │ foo   │
└───────────────┴───────┘
```

```sql
SELECT toFixedString('foo\0bar', 8) AS s, toStringCutToZero(s) AS s_cut
```

```text
┌─s──────────┬─s_cut─┐
│ foo\0bar\0 │ foo   │
└────────────┴───────┘
```

## reinterpretAsUInt(8|16|32|64)

## reinterpretAsInt(8|16|32|64)

## reinterpretAsFloat(32|64)

## reinterpretAsDate

## reinterpretAsDateTime

Функции принимают строку и интерпретируют байты, расположенные в начале строки, как число в host order (little endian). Если строка имеет недостаточную длину, то функции работают так, как будто строка дополнена необходимым количеством нулевых байт. Если строка длиннее, чем нужно, то лишние байты игнорируются. Дата интерпретируется, как число дней с начала unix-эпохи, а дата-с-временем - как число секунд с начала unix-эпохи.

## reinterpretAsString {#type_conversion_functions-reinterpretAsString}
Функция принимает число или дату или дату-с-временем и возвращает строку, содержащую байты, представляющие соответствующее значение в host order (little endian). При этом, отбрасываются нулевые байты с конца. Например, значение 255 типа UInt32 будет строкой длины 1 байт.

## CAST(x, t) {#type_conversion_function-cast}
Преобразует x в тип данных t.
Поддерживается также синтаксис CAST(x AS t).

Пример:

```sql
SELECT
    '2016-06-15 23:00:00' AS timestamp,
    CAST(timestamp AS DateTime) AS datetime,
    CAST(timestamp AS Date) AS date,
    CAST(timestamp, 'String') AS string,
    CAST(timestamp, 'FixedString(22)') AS fixed_string
```

```text
┌─timestamp───────────┬────────────datetime─┬───────date─┬─string──────────────┬─fixed_string──────────────┐
│ 2016-06-15 23:00:00 │ 2016-06-15 23:00:00 │ 2016-06-15 │ 2016-06-15 23:00:00 │ 2016-06-15 23:00:00\0\0\0 │
└─────────────────────┴─────────────────────┴────────────┴─────────────────────┴───────────────────────────┘
```

Преобразование в FixedString(N) работает только для аргументов типа String или FixedString(N).

Поддержано преобразование к типу [Nullable](../../data_types/nullable.md) и обратно. Пример:

```sql
SELECT toTypeName(x) FROM t_null
```
```text
┌─toTypeName(x)─┐
│ Int8          │
│ Int8          │
└───────────────┘
```
```sql
SELECT toTypeName(CAST(x, 'Nullable(UInt16)')) FROM t_null
```
```text
┌─toTypeName(CAST(x, 'Nullable(UInt16)'))─┐
│ Nullable(UInt16)                        │
│ Nullable(UInt16)                        │
└─────────────────────────────────────────┘
```

## toInterval(Year|Quarter|Month|Week|Day|Hour|Minute|Second) {#function-tointerval}

Приводит аргумент из числового типа данных к типу данных [IntervalType](../../data_types/special_data_types/interval.md).

**Синтксис**

```sql
toIntervalSecond(number)
toIntervalMinute(number)
toIntervalHour(number)
toIntervalDay(number)
toIntervalWeek(number)
toIntervalMonth(number)
toIntervalQuarter(number)
toIntervalYear(number)
```

**Параметры**

- `number` — длительность интервала. Положительное целое число.

**Возвращаемые значения**

- Значение с типом данных `Interval`.

**Пример**

```sql
WITH
    toDate('2019-01-01') AS date,
    INTERVAL 1 WEEK AS interval_week,
    toIntervalWeek(1) AS interval_to_week
SELECT
    date + interval_week,
    date + interval_to_week
```

```text
┌─plus(date, interval_week)─┬─plus(date, interval_to_week)─┐
│                2019-01-08 │                   2019-01-08 │
└───────────────────────────┴──────────────────────────────┘
```


[Оригинальная статья](https://clickhouse.yandex/docs/ru/query_language/functions/type_conversion_functions/) <!--hide-->

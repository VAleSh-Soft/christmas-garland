## Christmas garland 1.2

- [Описание](#описание)
- [Настройки в файле setting.h](#настройки-в-файле-settingh)
  - [Периферия](#периферия)
  - [Вывод отладочной информации](#вывод-отладочной-информации)
  - [Настройка FastLED](#настройка-fastled)
  - [Настройки EEPROM](#настройки-eeprom)
  - [Настройки вершины](#настройки-вершины)
  - [Прочие настройки](#прочие-настройки)
- [Онлайн настройка модуля под гирлянду](#онлайн-настройка-модуля-под-гирлянду)
  - [Настройка порядка вывода цветов в чипе светодиодов гирлянды](#настройка-порядка-вывода-цветов-в-чипе-светодиодов-гирлянды)
  - [Настройка количества светодиодов в гирлянде](#настройка-количества-светодиодов-в-гирлянде)
  - [Настройка вершины елки](#настройка-вершины-елки)
  - [Настройка цвета заливки фона](#настройка-цвета-заливки-фона)
- [Управление гирляндой кнопками](#управление-гирляндой-кнопками)
  - [Одна кнопка](#одна-кнопка)
  - [Две кнопки](#две-кнопки)
  - [Три кнопки](#три-кнопки)
  - [Четыре кнопки](#четыре-кнопки)
- [Использованные сторонние библиотеки](#использованные-сторонние-библиотеки)


### Описание

Модуль управления елочной гирляндой из адресных светодиодов, построенный на **Arduino Uno/Nano/Pro mini** на **ATmega328p**. Имеет большое количество эффектов в сочетании с множеством цветовых палитр.

За основу взят скетч [notamesh4.2](https://mysku.club/blog/aliexpress/68990.html), переделанный в меру моих хотелок. В частности, было удалено управление с помощью IR-пульта и аналоговой клавиатуры, удалены большая часть режимов настроек, расширен перечень сохраняемых в **EEPROM** параметров, добавлены кое-какие настройки. Набор эффектов и вообще механизм управления эффектами практически не затрагивался.

Файлы с исходными кодами перенесены в папку **src**, настройки программы перенесены из скетча в файл **setting.h**

Количество светодиодов в гирлянде ограничено объемом памяти МК, **ATmega328p** спокойно переваривает `256` штук, больше не пробовал (для теста подключал вместо гирлянды матрицу `8х32` ))

Модуль может иметь до 4 тактовых кнопок для управления работой гирлянды и до двух индикаторных светодиодов.

Видео демонстрации эффектов модуля: [youtube](https://youtu.be/299cCPMu3Tw), [rutube](http://out.arduino.ru/?redirect=https%3A%2F%2Frutube.ru%2Fvideo%2Fprivate%2F4467796d90fffbb4f78e8630fc9bed80%2F%3Fp%3D0S5jsiOV8fFwqVBnTwjcwQ&baseU=https%3A%2F%2Fforum.arduino.ru%2F)

### Настройки в файле setting.h

#### Периферия

`#define LED_ON 0` - индикаторные светодиоды (0 - светодиоды не используются, максимум 2 светодиода);

`#define BUTTONS_NUM 3` - Количество кнопок подключенных к модулю (0 - кнопок нет, максимум 4 кнопки);

#### Вывод отладочной информации

`#define LOG_ON 0` - включить отладочный вывод через Serial  
- 1 - включить лог;
- 0 - выключить;

`#define SERIAL_BAUDRATE 115200` - скорость работы Serial;

#### Настройка FastLED

`#define MAX_LEDS 100` - максимально возможное количество светодиодов  в гирлянде; на **ATmega328p** проверена работа гирлянды размером до 320 светодиодов, большее количество возможно (и скорее всего) будет приводить к зависанию программы из-за нехватки динамической памяти; однако, следует помнить, что при таком количестве светодиодов во избежание падения напряжения нужно дублировать питание гирлянды через каждые 50-100 светодиодов; в противном случае может иметь место слишком тусклое свечение гирлянды;

`#define CAN_CHANGE_NUMLEDS 1` - разрешение изменения количества светодиодов в гирлянде:
- 0 - не разрешено, размер гирлянды определяется макросом `MAX_LEDS`; 
- 1 - можно регулировать количество светодиодов в гирлянде, в этом случае макрос `MAX_LEDS` определяет максимальный размер гирлянды; подробнее см. [здесь](#настройка-количества-светодиодов));

`#define CHIPSET WS2812B` - тип микросхемы светодиодов в гирлянде;

`#define EORDER GRB` - очередность вывода цветов в чипе; строка задает параметр **EOrder**, используемый для инициализации гирлянды, без возможности изменения; закомментируйте эту строку, если хотите иметь возможность настройки модуля под конкретную гирлянду (об этой настройке см. [здесь](#настройка-порядка-вывода-цветов-в-чипе-светодиодов-гирлянды));

`#define POWER_V 5` - напряжение питания светодиодов в вольтах, обычно 5 вольт;

`#define POWER_I 2000` - максимальный потребляемый гирляндой ток в миллиамперах, позволяет ограничить потребляемую мощность гирлянды возможностями блока питания; возможно, это продлит срок службы вашего блока питания )); если ограничение по потребляемому току не нужно, задайте `POWER_I` равным `0` или закомментируйте эту строку; ограничение потребляемой гирляндой мощности применяется, если заданы оба параметра - `POWER_V` и `POWER_I`;

#### Настройки EEPROM

`#define SAVE_EEPROM` 1 - сохранять настройки запуска в EEPROM 
- 0 - ничего не  хранить; 
- 1 - хранить стартовый режим, длину гирлянды, задержку, яркость, очередность цветов в чипе, настройки вершины, цвет заливки фона и расширенные настройки (состояние блеска, фона, свечей (включено/не включено));

#### Настройки вершины

`#define TOP_POSITION 2` - позиция вершины елки 
- 0 - не определена;
- 1 - вершина в начале гирлянды;
- 2 - вершина в конце гирлянды; 

параметр используется только эффектом огня для определения направления движения пламени; для всех остальных эффектов вершина всегда находится в конце гирлянды.

Далее следуют несколько настроек вершины, если вы решите ее выделять на гирлянде отдельно.

`#define TOP_LENGTH 8` - максимальное количество светодиодов, выделенных под вершину елки; если задать больше нуля, то появляется возможность онлайн настройки параметров вершины на модуле (см. [ниже](#настройка-вершины-елки));

`#define TOP_COLOR CRGB::Red` - цвет выделения вершины;

`#define TOP_EFFECT 1` - 0 - просто залить цветом, 1 - случайное переливание, 2- переливание сверху вниз 3- переливание снизу вверх

`#define TOP_DELAY 150` - задержка эффекта в милисекундах; определяет скорость переливания светодиодов вершины;

`#define TOP_FADING 10` - затухание; определяет скорость угасания светодиодов вершины;

#### Прочие настройки

Далее следуют настройки пинов для подключения гирлянды и периферии, настройки эффектов и настройки команд, прописанных на кнопках управления. Параметров много, все они подробно расписаны в комментариях (спасибо автору исходного скетча), поэтому отдельно описывать их не буду.

### Онлайн настройка модуля под гирлянду

Все онлайн настройки гирлянды доступны только при условии, что включено сохранение параметров в **EEPROM**.

```
#define SAVE_EEPROM 1
```

#### Настройка порядка вывода цветов в чипе светодиодов гирлянды

Параметр **EORDER** используется при инициализации гирлянды и определяет, в какой последовательности будут отправляться данные в чипы гирлянды - **RGB**, **GRB** или как-то еще. Неправильно выбранная настройка приведет к искажению цветовой гаммы гирлянды. В итоге скорее всего будет не так красиво, как было задумано ))

Исходный скетч позволял использовать варианты **RGB** и **GRB**, что казалось достаточным, т.к. это самые распространенные типы. Однако, жизнь более разнообразна, чем иногда кажется ))

Как оказалось, подобные гирлянды на чипе **WS2812b** могут быть не только **GRB**, но и **RGB**, и даже **BGR**

![alt text](doc/ws2812b.jpg)

что заставило пересмотреть принцип настройки и сохранения данного параметра гирлянды.

В текущей реализации **EORDER** может быть настроен двумя способами:

- можно жестко задать его без возможности изменения (например, если гирлянда к модулю припаяна и ее замена не предполагается); для этого используется макрос `#define EORDER GRB`, однако, это предполагает, что вы точно знаете, какое значение нужно использовать;
- или (если модуль использует хотя бы одну кнопку), можно настроить этот параметр для конкретной гирлянды, вообще не зная заранее, что гирлянде требуется; порядок действий следующий:
   * закомментировать строку `#define EORDER` и прошить модуль (если это еще не сделано);
   * при включении питания модуля удерживать нажатой кнопку №1;
   * гирлянда включится в режиме настроки очередности цветов - первые три светодиода загорятся разными цветами; порядок следования цветов при старте настройки будет соответствовать реальному **EOrder** гирлянды;
   * нажимая кнопку №1, нужно добиться правильной очередности цветов - **Red** (красный) - **Green** (зеленый) - **Blue** (синий); очередность будет сохранена в **EEPROM**;

Для применения настроек нужно выключить и снова включить модуль;

*Изменение **EORDER** в этом случае реализовано не инициализацией гирлянды соответствующим значением, а подменой очередности следования байтов перед их выводом (см. функцию `CRGB set_new_eorder(CRGB _col);` в файле **function.h**)*

#### Настройка количества светодиодов в гирлянде

Если модуль использует хотя бы две кнопки и задан макрос `#define CAN_CHANGE_NUMLEDS 1`, появляется возможность регулирования размера гирлянды. Однако, делается это не как у автора оригинального скетча, чтобы не нагружать кнопки дополнительным функционалом, который едва ли будет использоваться, поэтому вход в этот режим выполняется при включении питания модуля с зажатой кнопкой. Порядок действий следующий:

 * при включении питания модуля удерживать нажатой кнопку №2; гирлянда включится в режиме настройки количества светодиодов - будут светиться цветом заливки фона (по умолчанию - голубым) все уже заданные светодиоды;
 * для настройки используются первая кнопка (для увеличения) и последняя кнопка (для уменьшения); последняя кнопка - это вторая, если их две, третья, если их три и т.д.;
 * при одиночном клике количество изменяется на одну единицу, при удержании кнопки нажатой - на `10` единиц; количество светодиодом может быть в диапазоне от `1` до `MAX_LEDS`; новое количество будет сохранено в **EEPROM**;
 * дополнительно: если модуль использует более двух кнопок, кликом второй кнопки меняется цвет заливки фона гирлянды;

Для применения настроек нужно выключить и снова включить модуль;

Если модуль использует менее двух кнопок, то длина гирлянды будет равна величине, заданной макросом `#define MAX_LEDS` в файле **setting.h**.

#### Настройка вершины елки

Если макрос `#define TOP_LENGTH` имеет значение более нуля, и модуль использует хотя бы три кнопки, появляется возможность настройки вершины елки (последние светодиоды гирлянды). Порядок действий следующий:

 * при включении питания модуля удерживать нажатой кнопку №3;
 * гирлянда включится в режиме настройки вершины - включится заданное количество светодиодов (по умолчанию `TOP_LENGTH`) в конце гирлянды; цвет свечения определяется макросом `#define TOP_COLOR`; остальные светодиоды будут светиться цветом заливки фона (по умолчанию - голубым);
 * для настройки используются первая кнопка (для увеличения) и последняя кнопка (для уменьшения); последняя кнопка - третья, если их три или четвертая, если их четыре; количество светодиодов может меняться от `0` до `TOP_LENGTH`;
 * клик кнопкой №2 определяет тип заполнения вершины - заливка, переливание сверху/снизу или случайное мерцание;
 * длинный клик (удержание нажатой около половины секунды) второй кнопкой меняет цвет заливки вершины; возможные значения - цвета радуги и белый цвет;
 * если модуль использует четыре кнопки, удержание нажатой третьей кнопки увеличивает или уменьшает величину затухания огоньков вершины; эта настройка работает только если задана не сплошная заливка вершины цветом;
 * так же, если модуль использует четыре кнопки, удержание первой и  четвертой кнопок ускоряет или замедляет анимацию вершины; настройка так же работает только если задана не сплошная заливка вершины;

Для применения настроек нужно выключить и снова включить модуль;

Настройки будут сохранены в **EEPROM**.

Если модуль использует менее трех кнопок, то настройки вершины определяются макросами в разделе [Настройки вершины](#настройки-вершины) в файле **setting.h**.

#### Настройка цвета заливки фона

Фон гирлянды может заливаться слабым свечением вместо черного цвета. Доступны три варианта: бледно-голубой (по умолчанию), бледно-зеленый, бледно-красный. Отдельного интерфейса настройки цвета нет, однако смена цвета заливки возможна, если доступен [интерфейс](#настройка-количества-светодиодов-в-гирлянде) настройки количества светодиодов в гирлянде, и модуль использует не менее трех кнопок; в этом случае клик второй кнопкой меняет цвет заливки фона;

Заданная настройка сохраняется в **EEPROM**.

Если ни один из двух перечисленных вариантов не доступен, используется цвет заливки фона по умолчанию - бледно-голубой;

### Управление гирляндой кнопками

По умолчанию (и по моему усмотрению) кнопкам заданы управляющие команды в зависимости от количества используемых кнопок (см. строку `#define BUTTONS_NUM`).

#### Одна кнопка

- одиночный клик - переключить на следующий эффект;
- двойной клик - включить/выключить блестки;
- удержание кнопки нажатой - увеличение яркости гирлянды; при достижении максимума яркость сбрасывается на минимум и снова начинает увеличиваться;

#### Две кнопки

- Кнопка №1
  - одиночный клик - переключить на следующий эффект;
  - двойной клик - включить/выключить свечки (см. строку `#define CANDLE_KOL`);
  - удержание кнопки нажатой - увеличение яркости гирлянды;
- Кнопка №2
  - одиночный клик - переключить на предыдущий эффект;
  - двойной клик - включить/выключить блестки;
  - удержание кнопки нажатой - уменьшение яркости гирлянды;

#### Три кнопки

- Кнопка №1
  - одиночный клик - переключить на следующий эффект;
  - удержание кнопки нажатой - увеличение яркости гирлянды;
- Кнопка №2
  - одиночный клик - включить/выключить блестки;
  - двойной клик - включить/выключить свечки (см. строку `#define CANDLE_KOL`);
  - удержание кнопки нажатой - включение/выключение гирлянды;
- Кнопка №3
  - одиночный клик - переключить на предыдущий эффект;
  - удержание кнопки нажатой - уменьшение яркости гирлянды;

#### Четыре кнопки

- Кнопка №1
  - одиночный клик - переключить на следующий эффект;
  - удержание кнопки нажатой - увеличение яркости гирлянды;
- Кнопка №2
  - одиночный клик - включить/выключить блестки;
  - удержание кнопки нажатой - включение/выключение гирлянды;
- Кнопка №3
  - одиночный клик - включить/выключить свечки (см. строку `#define CANDLE_KOL`);
  - удержание кнопки нажатой - включить/выключить заполнение фона;
- Кнопка №4
  - одиночный клик - переключить на предыдущий эффект;
  - удержание кнопки нажатой - уменьшение яркости гирлянды;

Если вас не устраивает этот набор команд, можете изменить их по своему усмотрению в разделе **набор команд на кнопках** в файле **setting.h**.

### Использованные сторонние библиотеки

FastLED.h - https://github.com/FastLED/FastLED <br>
shButton.h - https://github.com/VAleSh-Soft/shButton <br>

******************************************************
******************************************************

Если возникнут вопросы, пишите на valesh-soft@yandex.ru
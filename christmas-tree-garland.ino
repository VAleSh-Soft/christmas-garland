// ==== Подключенная периферия =======================
#define LED_ON 0 // Количество светодиодов (0- светодиоды не используются, максимум 2 светодиода
#define KEY_ON 3 // Количество кнопок подключенных к библиотеке shButton (0- библиотека отключена, максимум 4 кнопки)

#define LOG_ON 0 // Включить лог  1 - включить лог

// ==== Настройка FastLED ============================

#define MAX_LEDS 104 // Максимальное количество светодиодов,  очень влияет на память

#define COLOR_ORDER_PIN 7 // Пин для переключателя очередности цвета светодиодов  RGB или GRB
#define CHIPSET WS2812B   // Тип микросхемы светодиодов в гирлянде

#define LED_DATA_PIN 6 // Номер пина куда подключена гирлянда
// #define LED_CLK_PIN 11 // Номер пина для подключения линии тактирования, применяется для светодиодов WS2801, APA102 и т.д.
// ЕСЛИ НЕ ИСПОЛЬЗУЕТСЯ ЗАКОМЕНТИРОВАТЬ

#define POWER_V 5   // напряжение блока питания в Вольтах
#define POWER_I 500 // Ток блока питания в миллиАмперах

// ==== Настройка Светодиодов ========================
#define LED1_PIN 26 // Номер пина, куда подключен 1 светодиод
#define LED2_PIN 25 // Номер пина, куда подключен 2 светодиод

// Команды связанные со светодиодами
#define LED1_On digitalWrite(LED1_PIN, HIGH);       // Включить светодиод 1
#define LED1_Off digitalWrite(LED1_PIN, LOW);       // Выключить светодиод 1
#define LED1_FleshH(x) Led1_flesh = 4 * x;          // Мигнуть быстро x раз 1 светодиодом    (1-15)
#define LED1_Flesh(x) Led1_flesh = 64 + (8 * x);    // Мигнуть x раз 1 светодиодом           (1-7)
#define LED1_FleshL(x) Led1_flesh = 128 + (16 * x); // Мигнуть медленно x раз 1 светодиодом  (1-7)
#define LED2_On digitalWrite(LED2_PIN, HIGH);       // Включить светодиод 2
#define LED2_Off digitalWrite(LED2_PIN, LOW);       // Выключить светодиод 2
#define LED2_FleshH(x) Led2_flesh = 4 * x;          // Мигнуть быстро x раз 2 светодиодом    (1-15)
#define LED2_Flesh(x) Led2_flesh = 64 + 8 * x;      // Мигнуть x раз 2 светодиодом           (1-7)
#define LED2_FleshL(x) Led2_flesh = 128 + 16 * x;   // Мигнуть медленно x раз 2 светодиодом  (1-7)

// ==== Параметры кнопок =============================

//  Максимальное количество кнопок 4

#define BTN1_PIN 3 // Номер пина, куда подключена кнопка 1
#define BTN2_PIN 4 // Номер пина, куда подключена кнопка 2
#define BTN3_PIN 5 // Номер пина, куда подключена кнопка 3
#define BTN4_PIN 9 // Номер пина, куда подключена кнопка 4
// кнопки замыкаются на землю, используется внутренняя подтяжка МК

// Команды связанные с действиями кнопки, менять не надо, просто используем
#define BTN1_1 1000       // кнопка 1 клик
#define BTN1_2 1001       // кнопка 1 два клика
#define BTN1_3 1002       // кнопка 1 три клика
#define BTN1_4 1003       // кнопка 1 четыре клика
#define BTN1_PRESS 1005   // кнопка 1 удержание
#define BTN1_1_PRESS 1006 // кнопка 1 один клик + удержание
#define BTN1_2_PRESS 1007 // кнопка 1 два клика + удержание
#define BTN1_3_PRESS 1008 // кнопка 1 три клика + удержание
#define BTN2_1 1100       // кнопка 2 клик
#define BTN2_2 1101       // кнопка 2 два клика
#define BTN2_3 1102       // кнопка 2 три клика
#define BTN2_4 1103       // кнопка 2 четыре клика
#define BTN2_PRESS 1105   // кнопка 2 удержание
#define BTN2_1_PRESS 1106 // кнопка 2 один клик + удержание
#define BTN2_2_PRESS 1107 // кнопка 2 два клика + удержание
#define BTN2_3_PRESS 1108 // кнопка 2 три клика + удержание
#define BTN3_1 1200       // кнопка 3 клик
#define BTN3_2 1201       // кнопка 3 два клика
#define BTN3_3 1202       // кнопка 3 три клика
#define BTN3_4 1203       // кнопка 3 четыре клика
#define BTN3_PRESS 1205   // кнопка 3 удержание
#define BTN3_1_PRESS 1206 // кнопка 3 один клик + удержание
#define BTN3_2_PRESS 1207 // кнопка 3 два клика + удержание
#define BTN3_3_PRESS 1208 // кнопка 3 три клика + удержание
#define BTN4_1 1300       // кнопка 4 клик
#define BTN4_2 1301       // кнопка 4 два клика
#define BTN4_3 1302       // кнопка 4 три клика
#define BTN4_4 1303       // кнопка 4 четыре клика
#define BTN4_PRESS 1305   // кнопка 4 удержание
#define BTN4_1_PRESS 1306 // кнопка 4 один клик + удержание
#define BTN4_2_PRESS 1307 // кнопка 4 два клика + удержание
#define BTN4_3_PRESS 1308 // кнопка 4 три клика + удержание

// ==== Настройка скорости лога ======================
#define SERIAL_BAUDRATE 115200 // Or 115200.

// ==== Настройка эффектов ===========================
//

#define BLACKSTART 1 // Первый запуск делать с черного экрана 0- начинать с эффекта, 1- начинать с черного экрана

#define GLITER_ON 1 // Включить блеск 0 - блеск отключен, 1- блеск включен

#define CANDLE_KOL 5 // если больше 0 то будут включена имитация свечей, число задает через какое расстояние друг от друга располагать свечи
#define CANDLE_ON 0  // Если включена имитация свечей то 1 = при запуске она будет включена, 0 = при запуске она будет выключена

#define CANDLE_40 1 // Управление 40 эффектом (свечи)   1 = при запуске она будет включена по варианту efimova1969, иначе при запуске она будет включена по моему варианту

#define BACKGR_ON 1 // Включить заполнение черного цвета фоном

#define DEMO_MODE 4 // Режим при включении
                    // 0 - последняя запущенная программа
                    // 1 - демо режим с последовательным перебором эффектов
                    // 2 - демо режим с случайным перебором эффектов
                    // 3 - демо режим с последовательным перебором выбранных эффектов
                    // 4 - демо режим с случайным перебором выбранных эффектов

#define MY_MODE 0, 1, 2, 4, 5, 9, 10, 11, 14, 16, 17, 18, 19, 21, 22, 28, 30, 32, 34, 36, 37, 38
// Выбранные эффекты пишутся номера через запятую,
//  можно писать и одинаковые что актуально в демо 3
//  Если закомментировать, то демо 3 и 4 отключаются

#define DEMO_TIME 40 // Время отображение эффекта в демо режиме в секундах

#define CHANGE_ON 1    // Включить плавную смену эффектов
#define CHANGE_SPARK 1 // Эффект смены 0 - без эффекта,
                       // 1 - искры (бенгальский огонь)
                       // 2 - яркий свет
                       // 3 - метеорит,
                       // 4 - случайный эффект (из 1-3)
#define CHANGE_TIME 5  // Время в секундах, за которое произойдет плавная смена эффектов

#define DIRECT_TIME 20   // Через сколько секунд менять направление если 0 - не меняем
#define PALETTE_TIME 40  // Через сколько секунд менять палитру если 0 - не меняем
#define PALETTE_SPEED 20 // скорость перехода с одной палитры в другую (1- 48)

#define DEV_NOISE16 100 // если Зависает на 22 и 37 режимах, то уменьшаем число

#define SAVE_EEPROM 0 // Сохранять настройки запуска в EEPROM
                      // 0 - ничего не  хранить
                      // 1 - хранить стартовый режим, длина гирлянды, скорости и расширенные настройки (очередность цвета,состояние блеска, фон свечей)
                      // 2 - хранить стартовый режим, длина гирлянды, скорости

#define TOP_POSITION 2      // Позиция вершины елки (используется только в эффекте огня)
                            // 0 - не определена 1 - Вершина в начале гирлянды 2 - Вершина в конце гирлянды
#define TOP_LENGTH 0        // Выделять вершину цветом 0 - не выделять, больше 0  сколько светодиодов выделять в вершине
#define TOP_COLOR CRGB::Red // Цвет выделения вершины
#define TOP_EFFECT 2        // 0 - Просто залить цветом, 1 - случайное переливание, 2- переливание сверху вниз 3- переливание снизу вверх
#define TOP_DELAY 150       // Задержка эффекта в милисекундах
#define TOP_FADING 5        // Затухание

// ==== эффект бегущий огонь из 80-90 годов ==========
#define RUNNING_FIRE 0 // 1 Включить эффекты бегущего огня, начинаются с 43 команды
                       // Программы бегущего огня
                       // описание параметров
                       // первое число - кол-во ячеек в программе (от 1 до 8) показывает сколько шагов в эффекте
                       // второе число - разрядность эффекта      (от 1 до 8) показывает сколько светодиодов используется в эффекте
                       // остальные числа это программа, количество этих чисел задается в первом числе, один байт один шаг

#define PROG_0 8, 8, 0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001 // 8 шагов, 8 светодиодов, 1 шаг горит 8 светодиод, 2 шаг горит 7 светодиод, 3 шаг горит 6 светодиод, ... , 8 шаг горит 1 светодиод
#define PROG_1 7, 7, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001             // 7 шагов, 7 светодиодов, 1 шаг горит 7 светодиод, 2 шаг горит 6 светодиод, 3 шаг горит 5 светодиод, ... , 7 шаг горит 1 светодиод
#define PROG_2 6, 6, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001
#define PROG_3 5, 5, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001
#define PROG_4 4, 4, 0b00001000, 0b00000100, 0b00000010, 0b00000001
#define PROG_5 3, 3, 0b00000100, 0b00000010, 0b00000001                                                             // 3 шага, 3 светодиода, 1 шаг горит 3 светодиод, 2 шаг горит 2 светодиод, 3 шаг горит 1 светодиод
#define PROG_6 8, 8, 0b11100000, 0b01110000, 0b00111000, 0b00011100, 0b00001110, 0b00000111, 0b10000011, 0b11000001 // 8 шагов, 8 светодиодов, 1 шаг горят 8,7,6 светодиоды, 2 шаг горят 7,6,5 светодиоды, 3 шаг горят 6,5,4 светодиоды, ... , 8 шаг горят 1,8,7 светодиоды
#define PROG_7 8, 8, 0b11100100, 0b01110010, 0b00111001, 0b10011100, 0b01001110, 0b00100111, 0b10010011, 0b11001001 // 8 шагов, 8 светодиодов, 1 шаг горят 8,7,6,3 светодиоды, 2 шаг горят 7,6,5,2 светодиоды, 3 шаг горят 6,5,4,1 светодиоды, ... , 8 шаг горят 1,8,7,4 светодиоды
#define PROG_8 8, 8, 0b11110110, 0b01111011, 0b10111101, 0b11011110, 0b01101111, 0b10110111, 0b11011011, 0b11101101 // 8 шагов, 8 светодиодов, 1 шаг горят все светодиоды кроме 4 и 1, 2 шаг горят все светодиоды кроме 3 и 8, 3 шаг горят все светодиоды кроме 2 и 7, ... , 8 шаг горят все светодиоды кроме 5 и 2
#define PROG_9 6, 6, 0b00111000, 0b00011100, 0b00001110, 0b00000111, 0b00100011, 0b00110001

#define PROG_RUN_FIRE PROG_0, PROG_1, PROG_2, PROG_3, PROG_4, PROG_5, PROG_6, PROG_7, PROG_8, PROG_9 // Все программы эффектов бегущего огня через запятую

// ==== Все команды которые обрабатывает скетч =======

/*
 * формат такой:
 * #define Command_XXXX   YYYYY
 *   где Command_XXXX - код команды, это лучше не менять
 *       YYYYY        - код обработчика (это либо число получаемое при нажатии
 *                      кнопки пульта, либо значение соответствующее нажатой
 *                      кнопке аналоговой клавиатуры, это мы определили выше
 *                      как значения KEY_0, KEY_1, KEY_2 и подобные либо
 *                      значение соответствующее нажатой кнопке библиотеки
 *                      shButton, это мы определили выше как значения BTN_1,
 *                      BTN_2, BTN_3, BTN_4 и BTN_PRESS, либо Значение 0 если
 *                      команда не используется)
 *                      Если команда не используется то тогда надо YYYYY
 *                      заменить на 0 или закомментировать строку
 *
 * Пример:
 *   #define Command_Brightness_plus   BTN1_1 - установить обработку команды
 *                                             "Увеличить максимальную яркость"
 *                                             на нажатие кнопки BTN1
 *   #define Command_Brightness_minus  BTN1_2 - установить обработку команды
 *                                             "Уменьшить максимальную яркость"
 *                                             на двойное нажатие кнопки BTN1
 */

// ==== набор команд на кнопках ======================

// ---- для одной кнопки (BTN1) ----------------------
#if KEY_ON == 1

#define Command_Next_mode_Demo BTN1_1        // Следующий эффект. Оставляет демонстрационный режим
#define Command_Glitter BTN1_2               // Включить/выключить сверкание
#define Command_Brightness_plus_R BTN1_PRESS // Увеличить максимальную яркость, при достижения максимума начать с минимума
#endif

// ---- для двух кнопок (BTN1, BTN2) -----------------
#if KEY_ON == 2

#define Command_Previous_mode_Demo BTN1_1   // Предыдущий эффект. Оставляет демонстрационный режим
#define Command_Glitter BTN1_2              // Включить/выключить сверкание
#define Command_Brightness_minus BTN1_PRESS // Уменьшить максимальную яркость и остановится если достигли минимума

#define Command_Next_mode_Demo BTN2_1      // Следующий эффект. Оставляет демонстрационный режим
#define Command_Candle BTN2_2              // Включить/выключить свечки
#define Command_Brightness_plus BTN2_PRESS // Увеличить максимальную яркость и остановится если достигли максимума
#endif

// ---- для трех кнопок (BTN1, BTN2, BTN3) -----------
#if KEY_ON == 3

#define Command_Previous_mode_Demo BTN1_1   // Предыдущий эффект. Оставляет демонстрационный режим
#define Command_Brightness_minus BTN1_PRESS // Уменьшить максимальную яркость и остановится если достигли минимума

#define Command_Glitter BTN2_1 // Включить/выключить сверкание
#define Command_Candle BTN2_2  // Включить/выключить свечки

#define Command_Next_mode_Demo BTN3_1      // Следующий эффект. Оставляет демонстрационный режим
#define Command_Brightness_plus BTN3_PRESS // Увеличить максимальную яркость и остановится если достигли максимума
#endif

// ---- для четырех кнопок (BTN1, BTN2, BTN3,  BTN4) -
#if KEY_ON == 4

#endif

// ==== Переменные ===================================

// Установить флаг OFF
#define SetOff(x)  \
  {                \
    if (x < 100)   \
      x = x + 100; \
  }
// Установить флаг ON
#define SetOn(x)   \
  {                \
    if (x >= 100)  \
      x = x - 100; \
  }
// Проверка флага OFF
#define TestOff(x) (x >= 100)
// Вернуть значение без флага
#define GetOff(x) ((x < 100) ? x : x - 100)
// Цифровой макрос беззнакового вычитания; если результат меньше 0, то присвоить 0; в противном случае присваивается фиксированное значение
#define qsubd(x, b) ((x > b) ? wavebright : 0)
// Беззнаковый макрос вычитания. если результат меньше 0, то присвоить 0
#define qsuba(x, b) ((x > b) ? x - b : 0)

#include <FastLED.h> // https://github.com/FastLED/FastLED

#if SAVE_EEPROM > 0
#include <EEPROM.h> // This is included with base install
#endif

#if KEY_ON > 0
#include <shButton.h> // https://github.com/VAleSh-Soft/shButton
shButton btn1(BTN1_PIN);
#if KEY_ON > 1
shButton btn2(BTN2_PIN);
#endif
#if KEY_ON > 2
shButton btn3(BTN3_PIN);
#endif
#if KEY_ON > 3
shButton btn4(BTN4_PIN);
#endif
#endif

#if LED_ON > 0
uint8_t Led1_flesh = 0x0; // Управление мигания светодиодом 1
#if LED_ON > 1
uint8_t Led2_flesh = 0; // Управление мигания светодиодом 2
#endif
#endif

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#if (KEY_ON > 0)
uint8_t IR_New_Mode = 0;   // Выбор эффекта
uint32_t IR_Time_Mode = 0; // время последнего нажатия
#endif

#if MAX_LEDS < 255
uint8_t NUM_LEDS; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити
uint8_t KolLed;
#else
uint16_t NUM_LEDS; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити
uint16_t KolLed;
#endif

uint8_t max_bright = 255; // Определение общей яркости; возможно изменение на лету

struct CRGB leds[MAX_LEDS]; // инициализация массива светодиодов

CRGBPalette16 gCurrentPalette; // Использование палитры вместо прямых назначений CHSV или CRGB.
CRGBPalette16 gTargetPalette;  // Поддержка плавной смены палитры
CRGB solid = CRGB::Black;      // Цвет закраски

extern const TProgmemRGBGradientPalettePtr gGradientPalettes[]; // для фиксированных палитр в gradient_palettes.h.

extern const uint8_t gGradientPaletteCount; // Общее количество фиксированных палитр
uint8_t gCurrentPaletteNumber = 0;          // Текущий номер палитры из списка палитр.
uint8_t currentPatternIndex = 0;            // Порядковый номер текущего шаблона
uint32_t demo_time = 0;                     // время демо режима

TBlendType currentBlending = LINEARBLEND; // NOBLEND или LINEARBLEND

// Индексы настроек в EEPROM
#define STARTMODE 0 // Расположение в EEPROM номера режима с которого будет старт (байт)
#define STRANDLEN 1 // Расположение в EEPROM длины гирлянды (2 байта)
#define STRANDEL 3  // Расположение в EEPROM задержки (байт)
#define EXTFLAG 4   // Расположение в EEPROM расширенных флагов
#define ISINIT 5    // Расположение в EEPROM байта корректности записи

#define INITVAL 0x55     // Это значение проверяем в бите корректности EEPROM
#define INITMODE 0       // с этого режима будет старт, по умолчанию 0 (старт с - с черного цвета)
#define INITLEN MAX_LEDS // Размер гирлянды при старте
#define INITDEL 0        // размер задержки при старте в миллисекундах

uint16_t meshdelay; // Timer for the notamesh. Works with INITDEL.

uint8_t ledMode = 0; // номер текущего режима
#if CHANGE_ON == 1
uint8_t newMode = 0; // номер нового режима
#if MAX_LEDS < 255
uint8_t StepMode = MAX_LEDS; // Текущий шаг перехода от нового режима к старому
#else
uint16_t StepMode = MAX_LEDS; // Текущий шаг перехода от нового режима к старому
#endif
#endif

uint8_t demorun = DEMO_MODE;
#if RUNNING_FIRE > 0
#define maxMode 122 // Maximum number of modes.
#else
#define maxMode 42 // Maximum number of modes.
#endif

uint8_t Protocol = 0; // Temporary variables to save latest IR input
uint32_t Command = 0;

// ==== Общие переменные =============================
uint8_t allfreq = 32; // Меняет частоту. Переменная для эффектов one_sin_pal и two_sin.
uint8_t bgclr = 0;    // Общий цвет фона. Переменная для эффектов matrix_pal и one_sin_pal.
uint8_t bgbri = 0;    // Общая фоновая яркость. Переменная для эффектов matrix_pal и one_sin_pal.

// Структура хранения расширенных настроек
#pragma pack(push, 1)
typedef union
{
  struct
  {
    bool RedGreen : 1;   // Очередность  Цветов  RGB
    bool Glitter : 1;    // Флаг включения блеска
    bool Background : 1; // Флаг включения заполнения фона
    bool Candle : 1;     // Флаг включения свечей
    bool DemoRand : 1;   // Флаг случайный перебор эффектов
    bool rezerv0 : 1;    // Зарезервировано
    bool rezerv1 : 1;    // Зарезервировано
    bool rezerv2 : 1;    // Зарезервировано
  };
  unsigned char Byte;
} ExtendedFlags;
#pragma pack(pop)

ExtendedFlags ExtFlag; // Флаги расширенных настроек

#define glitter ExtFlag.Glitter
#define background ExtFlag.Background
#define candle ExtFlag.Candle

uint8_t palchg = 3;       // Управление палитрой  3 - менять палитру автоматически иначе нет
uint8_t startindex = 0;   // С какого цвета начинать. Переменная для эффектов one_sin_pal.
uint8_t thisbeat;         // Переменная для эффектов juggle_pal.
uint8_t thiscutoff = 192; // Если яркость ниже этой, то яркость = 0. Переменная для эффектов one_sin_pal и two_sin.
uint16_t thisdelay = 0;   // Задержка delay
uint8_t thisdiff = 1;     // Шаг изменения палитры. Переменная для эффектов confetti_pal, juggle_pal и rainbow_march.
int8_t thisdir = 1;       // Направление движения эффекта. принимает значение -1 или 1.
uint8_t thisfade = 224;   // Скорость затухания. Переменная для эффектов confetti_pal и juggle_pal.
uint8_t thishue = 0;      // Оттенок Переменная для эффектов two_sin.
uint8_t thisindex = 0;    // Указатель ан элемент палитры
uint8_t thisinc = 1;      // Изменение начального цвета после каждого прохода. Переменная для эффектов confetti_pal и one_sin_pal.
int thisphase = 0;        // Изменение фазы. Переменная для эффектов one_sin_pal, plasma и two_sin.
uint8_t thisrot = 1;      // Измение скорости вращения волны. В настоящее время 0.
int8_t thisspeed = 4;     // Изменение стандартной скорости
uint8_t wavebright = 255; // Вы можете изменить яркость волн / полос, катящихся по экрану.

#ifdef MY_MODE
const PROGMEM uint8_t my_mode[] = {MY_MODE};   // массив выбранных режимов
const uint8_t my_mode_count = sizeof(my_mode); // колличество выбрано режимов
uint8_t cur_my_mode = 0;                       // Указатель на текущий режим
#endif

#if CHANGE_SPARK == 4
uint8_t rand_spark = 0;
#endif

long summ = 0;

void strobe_mode(uint8_t newMode, bool mc);
void bootme();
void meshwait();
void getirl();
void demo_check();

// ==== Функции отображения ==========================

// Функции поддержки
#include "src/addings.h"

// Эффекты
#include "src/confetti_pal.h"
#include "src/gradient_palettes.h"
#include "src/juggle_pal.h"
#include "src/matrix_pal.h"
#include "src/noise16_pal.h"
#include "src/noise8_pal.h"
#include "src/one_sin_pal.h"
#include "src/plasma.h"
#include "src/rainbow_march.h"
#include "src/rainbow_beat.h"
#include "src/serendipitous_pal.h"
#include "src/three_sin_pal.h"
#include "src/two_sin.h"
#include "src/blendwave.h"
#include "src/fire.h"
#include "src/candles.h"
#include "src/colorwave.h"
#include "src/getirl.h"

#if RUNNING_FIRE == 1
#include "src/running_fire.h"
#endif

// ===================================================

void setup()
{
  pinMode(COLOR_ORDER_PIN, INPUT_PULLUP);

#if KEY_ON > 0
  btn1.setVirtualClickOn(true);
  btn1.setLongClickMode(LCM_CLICKSERIES);
#if KEY_ON > 1
  btn2.setVirtualClickOn(true);
  btn2.setLongClickMode(LCM_CLICKSERIES);
#endif
#if KEY_ON > 2
  btn3.setVirtualClickOn(true);
  btn3.setLongClickMode(LCM_CLICKSERIES);
#endif
#if KEY_ON > 3
  btn4.setVirtualClickOn(true);
  btn4.setLongClickMode(LCM_CLICKSERIES);
#endif
#endif

#if LED_ON > 0
  pinMode(LED1_PIN, OUTPUT); // пин первого светодиода
#if LED_ON > 1
  pinMode(LED2_PIN, OUTPUT); // пин второго светодиода
#endif
  LED1_On; // Включим светодиод
#endif

#if LOG_ON == 1
  Serial.begin(SERIAL_BAUDRATE); // Setup serial baud rate

  Serial.println(F(" "));
  Serial.println(F("---SETTING UP---"));

#endif

#if SAVE_EEPROM > 0

#if !defined(__AVR__)
  EEPROM.begin(ISINIT + 1);
#endif
  ledMode = EEPROM.read(STARTMODE);  // Расположение в EEPROM номера режима с которого будет старт (байт)
  NUM_LEDS = EEPROM.read(STRANDLEN); // Расположение в EEPROM длины гирлянды (2 байта)
#if MAX_LEDS < 255
  if (EEPROM.read(STRANDLEN + 1)) // Почемуто светодиодов болше чем размер переменной
    NUM_LEDS = MAX_LEDS;          // Need to ensure NUM_LEDS < MAX_LEDS elsewhere.
#else
  NUM_LEDS += (uint16_t)EEPROM.read(STRANDLEN + 1) << 8; // Need to ensure NUM_LEDS < MAX_LEDS elsewhere.
#endif
  meshdelay = EEPROM.read(STRANDEL); // Расположение в EEPROM задержки (байт)

#if SAVE_EEPROM == 1
  ExtFlag.Byte = EEPROM.read(EXTFLAG); // Прочитаем расширенные настройки
#else
  ExtFlag.RedGreen = digitalRead(COLOR_ORDER_PIN) ? 1 : 0;
  // if (COLOR_ORDER == RGB)
  //   ExtFlag.RedGreen = 1;
  // else
  //   ExtFlag.RedGreen = 0;
  ExtFlag.Glitter = GLITER_ON;    // Флаг включения блеска
  ExtFlag.Background = BACKGR_ON; // Флаг включения заполнения фона
  ExtFlag.Candle = CANDLE_ON;     // Флаг включения свечей
#endif

  if ((EEPROM.read(ISINIT) != INITVAL) || // проверка правильности в EEPROM байта корректности записи
      (NUM_LEDS > MAX_LEDS) ||
      ((ledMode > maxMode) && (ledMode != 100)))
  {                                    // Не корректен
    EEPROM.write(STARTMODE, INITMODE); // сохраним в EEPROM номера режима с которого будет старт (байт)
#if MAX_LEDS < 255
    EEPROM.write(STRANDLEN, INITLEN); // сохраним в EEPROM длины гирлянды (2 байта)
#else
    EEPROM.write(STRANDLEN, (uint16_t)(INITLEN) & 0x00ff);
    EEPROM.write(STRANDLEN + 1, (uint16_t)(INITLEN) >> 8);
#endif
    EEPROM.write(STRANDEL, INITDEL); // сохраним в EPROM задержку (байт)

    ExtFlag.RedGreen = digitalRead(COLOR_ORDER_PIN) ? 1 : 0;
    // if (COLOR_ORDER == RGB)
    //   ExtFlag.RedGreen = 1;
    // else
    //   ExtFlag.RedGreen = 0;
    ExtFlag.Glitter = GLITER_ON;         // Флаг включения блеска
    ExtFlag.Background = BACKGR_ON;      // Флаг включения заполнения фона
    ExtFlag.Candle = CANDLE_ON;          // Флаг включения свечей
    EEPROM.write(EXTFLAG, ExtFlag.Byte); // сохраним в EPROM расширенные настройки

    EEPROM.write(ISINIT, INITVAL); // сохраним в EEPROM байта корректности записи
#if !defined(__AVR__)
    EEPROM.commit();
#endif

    ledMode = INITMODE;
    NUM_LEDS = INITLEN;
    meshdelay = INITDEL;
  }
#else
  // ExtFlag.RedGreen = digitalRead(COLOR_ORDER_PIN) ? 1 : 0;
  ExtFlag.RedGreen = 0;
  // if (COLOR_ORDER == RGB)
  //   ExtFlag.RedGreen = 1;
  // else
  //   ExtFlag.RedGreen = 0;
  ExtFlag.Glitter = GLITER_ON;    // Флаг включения блеска
  ExtFlag.Background = BACKGR_ON; // Флаг включения заполнения фона
  ExtFlag.Candle = CANDLE_ON;     // Флаг включения свечей

#ifdef MY_MODE
  switch (demorun)
  {
  case 3:
    ledMode = pgm_read_byte(my_mode + cur_my_mode);
    break; // демо 3
  case 4:
    ledMode = pgm_read_byte(my_mode + random8(my_mode_count));
    break; // демо 4
  case 1:
  case 2:
    ledMode = INITMODE;
    break;
  }
#else
  ledMode = INITMODE;
#endif
  NUM_LEDS = MAX_LEDS;
  meshdelay = INITDEL;
#endif

  if (NUM_LEDS < (TOP_LENGTH + 1))
  {
    NUM_LEDS = (TOP_LENGTH + 1); // Проверка
  }

  LEDS.setBrightness(max_bright);

  if (ExtFlag.RedGreen)
  {
#if LED_CLK_PIN
    LEDS.addLeds<CHIPSET, LED_DATA_PIN, LED_CLK_PIN, RGB>(leds, MAX_LEDS);
#else
    LEDS.addLeds<CHIPSET, LED_DATA_PIN, RGB>(leds, MAX_LEDS); // Для светодиодов WS2812B
#endif
  }
  else
  {
#if LED_CLK_PIN
    LEDS.addLeds<CHIPSET, LED_DATA_PIN, LED_CLK_PIN, GRB>(leds, MAX_LEDS);
#else
    LEDS.addLeds<CHIPSET, LED_DATA_PIN, GRB>(leds, MAX_LEDS); // Для светодиодов WS2812B
#endif
  }

  LEDS.setMaxPowerInVoltsAndMilliamps(POWER_V, POWER_I); // Настройка блока питания

  random16_set_seed(4832); // Рандомайзер
  random16_add_entropy(analogRead(2));

#if LOG_ON == 1
  Serial.print(F("Initial delay: "));
  Serial.print(meshdelay * 100);
  Serial.println(F("ms delay."));
  Serial.print(F("Initial strand length: "));
  Serial.print(NUM_LEDS);
  Serial.println(F(" LEDs"));
  Serial.println(F("EXTEND Setup"));
  if (ExtFlag.RedGreen)
    Serial.println(F("RGB LEDS"));
  else
    Serial.println(F("GRB LEDS"));
  if (ExtFlag.Glitter)
    Serial.println(F("Glitter On"));
  else
    Serial.println(F("Glitter Off"));
  if (ExtFlag.Background)
    Serial.println(F("Background On"));
  else
    Serial.println(F("Background Off"));
  if (ExtFlag.Candle)
    Serial.println(F("Candle On"));
  else
    Serial.println(F("Candle Off"));
#endif

#if BLACKSTART == 1
  solid = CRGB::Black; // Запуск с пустого поля
#if CHANGE_ON == 1
  newMode = ledMode;
  StepMode = 1;
#endif
  ledMode = 255;
#endif

  gCurrentPalette = gGradientPalettes[0];
  gTargetPalette = gGradientPalettes[0];
  strobe_mode(ledMode, 1); // инициализация первой последовательности
#if LOG_ON == 1
  if (DEMO_MODE)
  {
    Serial.print(F("DEMO MODE "));
    Serial.println(DEMO_MODE);
  }
  Serial.println(F("---SETUP COMPLETE---"));
#endif

  LED1_Off; // Выключим светодиод
}

void loop()
{

#if (KEY_ON > 0)
  getirl(); // Обработка команд с пульта и аналоговых кнопок
#endif

  demo_check(); // Работа если включен демонстрационный режим

  EVERY_N_MILLISECONDS(50)
  { // Плавный переход от одной палитры в другую
#if CHANGE_ON == 1
    if (StepMode == MAX_LEDS)
#endif
      nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, PALETTE_SPEED);

#if LED_ON > 0 // Управление мигания светодиодом 1
    if (Led1_flesh > 0)
    { // Управление светодиодами
      Led1_flesh--;
      if (Led1_flesh >= 128)
      {
        if (Led1_flesh & 8)
          LED1_On;
        else
          LED1_Off;
        if (Led1_flesh == 128)
          Led1_flesh = 0;
      }
      else if (Led1_flesh >= 64)
      {
        if (Led1_flesh & 4)
          LED1_On;
        else
          LED1_Off;
        if (Led1_flesh == 64)
          Led1_flesh = 0;
      }
      else
      {
        if (Led1_flesh & 2)
          LED1_On;
        else
          LED1_Off;
      }
    }
#if LED_ON > 1 // Управление мигания светодиодом 2
    if (Led2_flesh > 0)
    { // Управление светодиодами
      Led2_flesh--;
      if (Led2_flesh >= 128)
      {
        if (Led2_flesh & 8)
          LED2_On;
        else
          LED2_Off;
        if (Led2_flesh == 128)
          Led2_flesh = 0;
      }
      else if (Led2_flesh >= 64)
      {
        if (Led2_flesh & 4)
          LED2_On;
        else
          LED2_Off;
        if (Led2_flesh == 64)
          Led2_flesh = 0;
      }
      else
      {
        if (Led2_flesh & 2)
          LED2_On;
        else
          LED2_Off;
      }
    }
#endif
#endif
  }

#if PALETTE_TIME > 0
  if ((palchg) && (demorun <= 100))
  {
    EVERY_N_SECONDS(PALETTE_TIME)
    { // Смена палитры
      if (palchg == 3)
      {
        if (gCurrentPaletteNumber < (gGradientPaletteCount - 1))
          gCurrentPaletteNumber++;
        else
          gCurrentPaletteNumber = 0;
#if LOG_ON == 1
        Serial.print(F("New Palette: "));
        Serial.println(gCurrentPaletteNumber);
#endif
      }
      gTargetPalette = gGradientPalettes[gCurrentPaletteNumber]; // We're just ensuring that the gTargetPalette WILL be assigned.
    }
  }
#endif

#if DIRECT_TIME > 0
  EVERY_N_SECONDS(DIRECT_TIME)
  { // Меняем направление
    thisdir = thisdir * -1;
  }
#endif

  EVERY_N_MILLIS_I(thistimer, thisdelay)
  {                                 // Sets the original delay time.
    thistimer.setPeriod(thisdelay); // This is how you update the delay value on the fly.
    KolLed = NUM_LEDS - TOP_LENGTH; // Выводим Эффект на все светодиоды
    strobe_mode(ledMode, 0);        // отобразить эффект;
#if CHANGE_ON == 1
    if ((StepMode < (NUM_LEDS - TOP_LENGTH)) && ((ledMode < 220) || (ledMode >= 230)))
    {                    // требуется наложить новый эффект
      KolLed = StepMode; // Выводим Эффект на все светодиоды
      if (StepMode > 10)
        strobe_mode(newMode, 0); // отобразить эффект;
#if CHANGE_SPARK == 4
      sparkler(rand_spark);
#else
      sparkler(CHANGE_SPARK); // бенгальский огонь
#endif
    }
#endif
  }

#if CHANGE_ON == 1 // Включена плавная смена эффектов
  if (StepMode < (NUM_LEDS - TOP_LENGTH))
  {                                                                         // есть шаги, исполняем
    uint16_t change_time = (1000L * CHANGE_TIME) / (NUM_LEDS - TOP_LENGTH); // время в мСек на каждый светодиод
    if (change_time < 20)
    {
      change_time = 20;
    }
    //        static uint8_t change_increment = (uint32_t)change_time * (NUM_LEDS-TOP_LENGTH) / (1000L *CHANGE_TIME)+1;
    EVERY_N_MILLISECONDS(change_time)
    { // Движение плавной смены эффектов
      //            if (StepMode > 10) StepMode += change_increment;
      //            else
      StepMode++;
      if (StepMode == 10)
      {
        strobe_mode(newMode, 1);
      }
      if (StepMode >= (NUM_LEDS - TOP_LENGTH))
      {
        ledMode = newMode;
        StepMode = MAX_LEDS - TOP_LENGTH;

#if LOG_ON == 1
        Serial.println(F("End SetMode"));
#endif
      }
      nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, PALETTE_SPEED);
    }
  }
#endif

#if TOP_LENGTH > 0
  top(); // Обработка конца гирлянды
#endif
  if (glitter)
  {
    addglitter(10); // блеск, если включен
  }
#if CANDLE_KOL > 0
  if (candle)
  {
    addcandle();
  }
#endif

  if (background)
  {
    addbackground(); // Включить заполнение черного цвета фоном
  }

  BtnHandler(); // Обработчик нажатий кнопок

#if ((KEY_ON > 0))
  if ((IR_Time_Mode > 0) && // Идет отчет времени
      ((millis() - IR_Time_Mode) >= 2000))
  { // И прошло больше 2 секунд
    IR_Time_Mode = 0;
    if (IR_New_Mode <= maxMode)
      SetMode(IR_New_Mode);
    IR_New_Mode = 0;
  }
#endif

  FastLED.show(); // Power managed display of LED's.
}

void strobe_mode(uint8_t mode, bool mc)
{ // mc stands for 'Mode Change', where mc = 0 is strobe the routine, while mc = 1 is change the routine

  if (mc)
  {
    fill_solid(leds, NUM_LEDS - TOP_LENGTH, CRGB(0, 0, 0)); // Clean up the array for the first time through. Don't show display though, so you may have a smooth transition.

#if LOG_ON == 1
    Serial.print(F("Mode: "));
    Serial.println(mode);
    Serial.println(millis());
#endif
#if PALETTE_TIME > 0
    if (palchg == 0)
      palchg = 3;
#else
    if (palchg == 0)
      palchg = 1;
#endif
  }

  switch (mode)
  { // First time through a new mode, so let's initialize the variables for a given display.
  case 0:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
    }
    blendwave();
    break;
  case 1:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
    }
    rainbow_beat();
    break;
  case 2:
    if (mc)
    {
      thisdelay = 10;
      allfreq = 2;
      thisspeed = 1;
      thatspeed = 2;
      thishue = 0;
      thathue = 128;
      thisdir = 1;
      thisrot = 1;
      thatrot = 1;
      thiscutoff = 128;
      thatcutoff = 192;
    }
    two_sin();
    break;
  case 3:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 4;
      bgclr = 0;
      bgbri = 0;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 4:
    if (mc)
    {
      thisdelay = 10;
    }
    noise8_pal();
    break;
  case 5:
    if (mc)
    {
      thisdelay = 10;
      allfreq = 4;
      thisspeed = -1;
      thatspeed = 0;
      thishue = 64;
      thathue = 192;
      thisdir = 1;
      thisrot = 0;
      thatrot = 0;
      thiscutoff = 64;
      thatcutoff = 192;
    }
    two_sin();
    break;
  case 6:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 10;
      bgclr = 64;
      bgbri = 4;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 7:
    if (mc)
    {
      thisdelay = 10;
      numdots = 2;
      thisfade = 16;
      thisbeat = 8;
      thisdiff = 64;
    }
    juggle_pal();
    break;
  case 8:
    if (mc)
    {
      thisdelay = 40;
      thisindex = 128;
      thisdir = 1;
      thisrot = 0;
      bgclr = 200;
      bgbri = 6;
    }
    matrix_pal();
    break;
  case 9:
    if (mc)
    {
      thisdelay = 10;
      allfreq = 6;
      thisspeed = 2;
      thatspeed = 3;
      thishue = 96;
      thathue = 224;
      thisdir = 1;
      thisrot = 0;
      thatrot = 0;
      thiscutoff = 64;
      thatcutoff = 64;
    }
    two_sin();
    break;
  case 10:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 16;
      bgclr = 0;
      bgbri = 0;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 11:
    if (mc)
    {
      thisdelay = 50;
      mul1 = 5;
      mul2 = 8;
      mul3 = 7;
    }
    three_sin_pal();
    break;
  case 12:
    if (mc)
    {
      thisdelay = 10;
    }
    serendipitous_pal();
    break;
  case 13:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 8;
      bgclr = 0;
      bgbri = 4;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 14:
    if (mc)
    {
      thisdelay = 10;
      allfreq = 20;
      thisspeed = 2;
      thatspeed = -1;
      thishue = 24;
      thathue = 180;
      thisdir = 1;
      thisrot = 0;
      thatrot = 1;
      thiscutoff = 64;
      thatcutoff = 128;
    }
    two_sin();
    break;
  case 15:
    if (mc)
    {
      thisdelay = 50;
      thisindex = 64;
      thisdir = -1;
      thisrot = 1;
      bgclr = 100;
      bgbri = 10;
    }
    matrix_pal();
    break;
  case 16:
    if (mc)
    {
      thisdelay = 10;
    }
    noise8_pal();
    break; // By: Andrew Tuline
  case 17:
    if (mc)
    {
      thisdelay = 10;
    }
    plasma(11, 23, 4, 18);
    break;
  case 18:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 10;
      thisspeed = 1;
      thatspeed = -2;
      thishue = 48;
      thathue = 160;
      thisdir = -1;
      thisrot = 1;
      thatrot = -1;
      thiscutoff = 128;
      thatcutoff = 192;
    }
    two_sin();
    break;
  case 19:
    if (mc)
    {
      thisdelay = 50;
      palchg = 0;
      thisdir = 1;
      thisrot = 1;
      thisdiff = 1;
    }
    rainbow_march();
    break;
  case 20:
    if (mc)
    {
      thisdelay = 10;
      mul1 = 6;
      mul2 = 9;
      mul3 = 11;
    }
    three_sin_pal();
    break;
  case 21:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
      thisdir = 1;
      thisrot = 2;
      thisdiff = 10;
    }
    rainbow_march();
    break;
  case 22:
    if (mc)
    {
      thisdelay = 20;
      palchg = 0;
      hxyinc = random16(1, 15);
      octaves = random16(1, 3);
      hue_octaves = random16(1, 5);
      hue_scale = random16(10, 50);
      x = random16();
      xscale = random16();
      hxy = random16();
      hue_time = random16();
      hue_speed = random16(1, 3);
      x_speed = random16(1, 30);
    }
    noise16_pal();
    break;
  case 23:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 6;
      bgclr = 0;
      bgbri = 0;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 24:
    if (mc)
    {
      thisdelay = 10;
    }
    plasma(23, 15, 6, 7);
    break;
  case 25:
    if (mc)
    {
      thisdelay = 20;
      thisinc = 1;
      thisfade = 2;
      thisdiff = 32;
    }
    confetti_pal();
    break;
  case 26:
    if (mc)
    {
      thisdelay = 10;
      thisspeed = 2;
      thatspeed = 3;
      thishue = 96;
      thathue = 224;
      thisdir = 1;
      thisrot = 1;
      thatrot = 2;
      thiscutoff = 128;
      thatcutoff = 64;
    }
    two_sin();
    break;
  case 27:
    if (mc)
    {
      thisdelay = 30;
      thisindex = 192;
      thisdir = -1;
      thisrot = 0;
      bgclr = 50;
      bgbri = 0;
    }
    matrix_pal();
    break;
  case 28:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 20;
      bgclr = 0;
      bgbri = 0;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 29:
    if (mc)
    {
      thisdelay = 20;
      thisinc = 2;
      thisfade = 8;
      thisdiff = 64;
    }
    confetti_pal();
    break;
  case 30:
    if (mc)
    {
      thisdelay = 10;
    }
    plasma(8, 7, 9, 13);
    break;
  case 31:
    if (mc)
    {
      thisdelay = 10;
      numdots = 4;
      thisfade = 32;
      thisbeat = 12;
      thisdiff = 20;
    }
    juggle_pal();
    break;
  case 32:
    if (mc)
    {
      thisdelay = 30;
      allfreq = 4;
      bgclr = 64;
      bgbri = 4;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 128;
      thisrot = 1;
      thisspeed = 8;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 33:
    if (mc)
    {
      thisdelay = 50;
      mul1 = 3;
      mul2 = 4;
      mul3 = 5;
    }
    three_sin_pal();
    break;
  case 34:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
      thisdir = -1;
      thisrot = 1;
      thisdiff = 5;
    }
    rainbow_march();
    break;
  case 35:
    if (mc)
    {
      thisdelay = 10;
    }
    plasma(11, 17, 20, 23);
    break;
  case 36:
    if (mc)
    {
      thisdelay = 20;
      thisinc = 1;
      thisfade = 1;
    }
    confetti_pal();
    break;
  case 37:
    if (mc)
    {
      thisdelay = 20;
      palchg = 0;
      octaves = 1;
      hue_octaves = 2;
      hxy = 6000;
      x = 5000;
      xscale = 3000;
      hue_scale = 50;
      hue_speed = 15;
      x_speed = 100;
    }
    noise16_pal();
    break;
  case 38:
    if (mc)
    {
      thisdelay = 10;
    }
    noise8_pal();
    break;
  case 39:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
    }
    fire();
    break;
  case 40:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
    }
    candles();
    break;
  case 41:
    if (mc)
    {
      thisdelay = 10;
    }
    colorwaves();
    break;
    //  case 42 .. 121: if(mc) {thisdelay=10; } running_fire(9,3,1); break;
  case 200:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    break; // Зажечь гирлянду длиной NUM_LEDS (регулировка длины гирлянды)
  case 201:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, meshdelay, CRGB(255, 255, 255));
    break; // Зажечь гирлянду длиной meshdelay
  case 220:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    leds[0] = CRGB::Red;
    break; // Зажечь гирлянду длиной NUM_LEDS (регулировка длины гирлянды)
  case 221:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    leds[0] = CRGB::Green;
    break; // Зажечь гирлянду длиной NUM_LEDS (регулировка длины гирлянды)
  case 255:
    if (mc)
    {
      palchg = 0;
    }
    fill_solid(leds, NUM_LEDS - TOP_LENGTH, solid);
    break; // Установить цвет
  default:
#if RUNNING_FIRE == 1
    if (mode >= 42 && mode < 122)
    {
      uint8_t mode_x = mode - 42;
      if (mc)
      {
        thisdelay = 10;
      }
      running_fire(mode_x >> 3, (mode_x >> 1) % 3, mode_x % 1);
    }
    else
#endif
      ledMode = 0;
    break; // нет такого режима принудительно ставим нулевой
  }

#if LOG_ON == 1
  if (mc)
  {
    if (palchg == 0)
      Serial.println(F("Change palette off"));
    else if (palchg == 1)
      Serial.println(F("Change palette Stop"));
    else if (palchg == 3)
      Serial.println(F("Change palette ON"));
  }
#endif
}

void demo_check()
{

  if ((demorun > 0) && (demorun <= 100))
  {
    if ((millis() - demo_time) >= (DEMO_TIME * 1000L))
    {                                                            // Наступило время смены эффекта
      demo_time = millis();                                      // Запомним время
      gCurrentPaletteNumber = random8(0, gGradientPaletteCount); // Случайно поменяем палитру
#if CHANGE_ON == 1
      switch (demorun)
      {
      case 2:
        newMode = random8(0, maxMode); // демо 2
        break;
#ifdef MY_MODE
      case 3:
        if (cur_my_mode >= (my_mode_count - 1))
          cur_my_mode = 0; // демо 3
        else
          cur_my_mode++;
        newMode = pgm_read_byte(my_mode + cur_my_mode);
        break;
      case 4:
        newMode = pgm_read_byte(my_mode + random8(my_mode_count)); // демо 4
        break;
#endif
      case 1:
        if (newMode >= maxMode)
          newMode = 0; // демо 1
        else
          newMode++;
        break;
      }
      StepMode = 1;
#if CHANGE_SPARK == 4
      rand_spark = random8(3) + 1;
#endif

#if LOG_ON == 1
      Serial.println(F("Start SetMode"));
#endif
#else
      gTargetPalette = gGradientPalettes[gCurrentPaletteNumber]; // Применим палитру
#if LOG_ON == 1
      Serial.print(F("New Palette: "));
      Serial.println(gCurrentPaletteNumber);
#endif
      switch (demorun)
      {
      case 2:
        ledMode = random8(0, maxMode); // демо 2
        break;
#ifdef MY_MODE
      case 3:
        if (cur_my_mode >= (my_mode_count - 1))
          cur_my_mode = 0; // демо 3
        else
          cur_my_mode++;
        ledMode = pgm_read_byte(my_mode + cur_my_mode);
        break;
      case 4:
        ledMode = pgm_read_byte(my_mode + random8(my_mode_count)); // демо 4
        break;
#endif
      case 1:
        if (ledMode >= maxMode)
          ledMode = 0; // демо 1
        else
          ledMode++;
        break;
      }
      strobe_mode(ledMode, 1); // Does NOT reset to 0.
#if CANDLE_KOL > 0
      PolCandle = random8(CANDLE_KOL);
#endif
#endif
    }
  }
}

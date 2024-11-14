#pragma once

/**
 * @brief файл с настройками программы
 *
 */

#include <FastLED.h>
#include "src/_eeprom.h"

// ==== Блок настроек прошивки =======================

// ---- Подключенная периферия ------------------

#define LED_ON 0      // Количество индикаторных светодиодов (0 - светодиоды не используются, максимум 2 светодиода)
#define BUTTONS_NUM 4 // Количество кнопок подключенных к модулю (0 - кнопок нет, максимум 4 кнопки)

// ---- Вывод отладочной информации -------------

#define LOG_ON 0               // Включить отладочный вывод через Serial;  1 - включить лог, 0 - выключить
#define SERIAL_BAUDRATE 115200 // скорость работы Serial

// ---- Настройка FastLED -----------------------

#define MAX_LEDS 256 // Максимальное количество светодиодов  в гирлянде, ограничивает количество светодиодов сверху (см. комментарий ниже); очень влияет на память

#define CAN_CHANGE_NUMLEDS 1 // Разрешение изменения количества светодиодов в гирлянде (0 - не разрешено, `numLeds = MAX_LEDS`, 1 - разрешено)

/*
 * Настройка количества светодиодов в гирлянде (доступно при использовании двух
 * и более кнопок):
 *   - при включении питания модуля удерживать нажатой кнопку №2;
 *   - гирлянда включится в режиме настройки количества светодиодов - будут
 *     светиться красным все заданные светодиоды;
 *   - для настройки используются первая кнопка (для увеличения) и последняя
 *     кнопка (для уменьшения);
 *   - при одиночном клике количество изменяется на одну единицу, при удержании
 *     кнопки нажатой - на 10 единиц; количество светодиодом может быть в
 *     диапазоне от 1 до MAX_LEDS; новое количество будет сохранено в EEPROM;
 *   - выключить и снова включить модуль для применения настроек;
 */

#define CHIPSET WS2812B // Тип микросхемы светодиодов в гирлянде

// #define EORDER GRB      // очередность цветов в чипе; закомментируйте, если хотите иметь возможность настройки модуля под конкретную гирлянду (см. комментарий ниже)

/*
 * Настройка очередности цветов в чипе (доступно при использовании хотя бы
 * одной кнопки):
 *   - закомментировать строку #define EORDER и прошить модуль (если это еще не
 *     сделано);
 *   - при включении питания модуля удерживать нажатой кнопку №1 (использование
 *     кнопок должно быть включено - см. строку #define BUTTONS_NUM);
 *   - гирлянда включится в режиме настроки очередности цветов - включатся
 *     первые три светодиода разными цветами;
 *   - нажимая кнопку №1, добиться правильной очередности цветов - Red (красный) -
 *     Green (зеленый) - Blue (синий); очередность будет сохранена в EEPROM;
 *   - выключить и снова включить модуль для применения настроек;
 */

#define POWER_V 5    // напряжение блока питания в вольтах
#define POWER_I 2000 // Ток блока питания в миллиамперах

// ---- Настройки EEPROM ------------------------

#define SAVE_EEPROM 1 // Сохранять настройки запуска в EEPROM
                      // 0 - ничего не  хранить
                      // 1 - хранить стартовый режим, длину гирлянды, задержку, яркость, очередность цветов в чипе, настройки вершины, и расширенные настройки (состояние блеска, фона, свечей)

#define EEPROM_INDEX_FOR_ISINIT 9     // Расположение в EEPROM байта корректности записи (1 байт)
#define EEPROM_INDEX_FOR_STARTMODE 10 // Расположение в EEPROM номера режима с которого будет старт (1 байт)
#define EEPROM_INDEX_FOR_STRANDLEN 11 // Расположение в EEPROM длины гирлянды (2 байта)
#define EEPROM_INDEX_FOR_STRANDEL 13  // Расположение в EEPROM задержки (1 байт)
#define EEPROM_INDEX_FOR_EXTFLAG 14   // Расположение в EEPROM расширенных флагов (1 байт)
#define EEPROM_INDEX_FOR_BRIGHT 15    // Расположение в EEPROM яркости гирлянды (1 байт)
#define EEPROM_INDEX_FOR_EORDER 16    // Расположение в EEPROM очередности цветов в чипе (1 байт)
#define EEPROM_INDEX_FOR_TOPLENGTH 17 // Расположение в EEPROM размера вершины (2 байта)
#define EEPROM_INDEX_FOR_TOPEFFECT 19 // Расположение в EEPROM типа заливки вершины (1 байт)
#define EEPROM_INDEX_FOR_TOPCOLOR 20  // Расположение в EEPROM индекса цвета заливки вершины (1 байт)

// ---- Настройки вершины -----------------------

#define TOP_POSITION 2      // Позиция вершины елки (используется только в эффекте огня для определения направления движения пламени; для всех остальных эффектов вершина всегда находится в конце гирлянды)
                            // 0 - не определена, 1 - Вершина в начале гирлянды, 2 - Вершина в конце гирлянды
#define TOP_LENGTH 8        // Максимальное количество светодиодов, выделенных под вершину елки; если больше нуля, то появляется возможность онлайн настройки этого количества на модуле (см. ниже);
#define TOP_COLOR CRGB::Red // Цвет выделения вершины
#define TOP_EFFECT 3        // 0 - Просто залить цветом, 1 - случайное переливание, 2- переливание сверху вниз, 3- переливание снизу вверх
#define TOP_DELAY 150       // Задержка эффекта в милисекундах
#define TOP_FADING 5        // Затухание

/*
 * Настройка вершины елки (доступно при использовании трех и более кнопок и
 * значении макроса #define TOP_LENGTH` больше нуля):
 *   - при включении питания модуля удерживать нажатой кнопку №3;
 *   - гирлянда включится в режиме настройки вершины - будет светиться только
 *     заданное количество светодиодов (по умолчанию `TOP_LENGTH`) в конце
 *     гирлянды; цвет свечения вершины определяется макросом
 *     `#define TOP_COLOR`; остальные светодиоды будут светиться слабым
 *     голубым цветом;
 *   - для настройки количества светодиодов вершины используются первая кнопка
 *     (для увеличения) и последняя кнопка (для уменьшения); количество
 *     светодиодом может быть в диапазоне от 0 до TOP_LENGTH;
 *   - клик второй кнопки определяет тип заполнения вершины - заливка,
 *     переливание или случайное мерцание;
 *   - если используются четыре кнопки, то клик третьей кнопкой меняет цвет
 *     заливки вершины; возможные значения - цвета радуги и белый цвет;
 *   - настройки будут сохранены в EEPROM;
 *   - выключить и снова включить модуль для применения настроек;
 */

// ---- Пины для подключения периферии ----------

#define LED_DATA_PIN 6 // Номер пина куда подключена гирлянда
// #define LED_CLK_PIN 11 // Номер пина для подключения линии тактирования, применяется для светодиодов с четырехпроводным подключение (WS2801, APA102 и т.д.)
// ЕСЛИ НЕ ИСПОЛЬЗУЕТСЯ ЗАКОМЕНТИРОВАТЬ

#define LED1_PIN A0 // Номер пина, куда подключен 1 светодиод
#define LED2_PIN A1 // Номер пина, куда подключен 2 светодиод

#define BTN1_PIN 3 // Номер пина, куда подключена кнопка 1
#define BTN2_PIN 4 // Номер пина, куда подключена кнопка 2
#define BTN3_PIN 5 // Номер пина, куда подключена кнопка 3
#define BTN4_PIN 9 // Номер пина, куда подключена кнопка 4
// кнопки замыкаются на землю, используется внутренняя подтяжка МК

// ---- Настройка эффектов ----------------------

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

#define MY_MODE 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 80, 90, 100, 110, 120
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
#define PALETTE_SPEED 20 // скорость перехода с одной палитры в другую (1-48)

#define DEV_NOISE16 100 // если Зависает на 22 и 37 режимах, то уменьшаем число

// ---- эффект бегущий огонь из 80-90 годов -----

#define RUNNING_FIRE 1 // 1 Включить эффекты бегущего огня,  42 .. 121 режимы

// ---- Программы бегущего огня ------------
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

// ---- Параметры кнопок ------------------------

#if BUTTONS_NUM
#include <shButton.h> // https://github.com/VAleSh-Soft/shButton
shButton btn1(BTN1_PIN);
#if BUTTONS_NUM > 1
shButton btn2(BTN2_PIN);
#endif
#if BUTTONS_NUM > 2
shButton btn3(BTN3_PIN);
#endif
#if BUTTONS_NUM > 3
shButton btn4(BTN4_PIN);
#endif
#endif

// Команды связанные с действиями кнопки, менять не надо, просто используем
#define BTN1_1 1000     // кнопка 1, клик
#define BTN1_2 1001     // кнопка 1, двойной клик
#define BTN1_PRESS 1005 // кнопка 1, удержание
#define BTN2_1 1100     // кнопка 2, клик
#define BTN2_2 1101     // кнопка 2, двойной клик
#define BTN2_PRESS 1105 // кнопка 2, удержание
#define BTN3_1 1200     // кнопка 3, клик
#define BTN3_2 1201     // кнопка 3, двойной клик
#define BTN3_PRESS 1205 // кнопка 3, удержание
#define BTN4_1 1300     // кнопка 4, клик
#define BTN4_2 1301     // кнопка 4, двойной клик
#define BTN4_PRESS 1305 // кнопка 4, удержание

// ---- Все команды которые обрабатывает скетч --

/*
 * формат такой:
 * #define Command_XXXX   YYYYY
 *   где Command_XXXX - код команды, это лучше не менять (см. файл getcommands.h)
 *       YYYYY        - код обработчика (значение соответствующее нажатой
 *                      кнопке библиотеки shButton, это мы определили выше как
 *                      значения BTN_1, BTN_2, BTN_3, BTN_4 и BTN_PRESS, либо
 *                      Значение 0, если команда не используется)
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

// ---- набор команд на кнопках -----------------

#if BUTTONS_NUM == 1
// ---- для одной кнопки (BTN1) -------------

#define Command_Next_mode_Demo BTN1_1        // Следующий эффект. Оставляет демонстрационный режим
#define Command_Glitter BTN1_2               // Включить/выключить сверкание
#define Command_Brightness_plus_R BTN1_PRESS // Увеличить максимальную яркость, при достижения максимума начать с минимума
#endif

#if BUTTONS_NUM == 2
// ---- для двух кнопок (BTN1, BTN2) --------

#define Command_Next_mode_Demo BTN1_1      // Следующий эффект. Оставляет демонстрационный режим
#define Command_Candle BTN1_2              // Включить/выключить свечки
#define Command_Brightness_plus BTN1_PRESS // Увеличить максимальную яркость и остановится если достигли максимума

#define Command_Previous_mode_Demo BTN2_1   // Предыдущий эффект. Оставляет демонстрационный режим
#define Command_Glitter BTN2_2              // Включить/выключить сверкание
#define Command_Brightness_minus BTN2_PRESS // Уменьшить максимальную яркость и остановится если достигли минимума
#endif

#if BUTTONS_NUM == 3
// ---- для трех кнопок (BTN1 .. BTN3) ------

#define Command_Next_mode_Demo BTN1_1      // Следующий эффект. Оставляет демонстрационный режим
#define Command_Brightness_plus BTN1_PRESS // Увеличить максимальную яркость и остановится если достигли максимума

#define Command_Glitter BTN2_1        // Включить/выключить сверкание
#define Command_Candle BTN2_2         // Включить/выключить свечки
#define Command_Start_Stop BTN2_PRESS // Включить/выключить гирлянду

#define Command_Previous_mode_Demo BTN3_1   // Предыдущий эффект. Оставляет демонстрационный режим
#define Command_Brightness_minus BTN3_PRESS // Уменьшить максимальную яркость и остановится если достигли минимума
#endif

#if BUTTONS_NUM > 3
// ---- для четырех кнопок (BTN1 .. BTN4) ---

#define Command_Next_mode_Demo BTN1_1      // Следующий эффект. Оставляет демонстрационный режим
#define Command_Brightness_plus BTN1_PRESS // Увеличить максимальную яркость и остановится если достигли максимума

#define Command_Glitter BTN2_1        // Включить/выключить сверкание
#define Command_Start_Stop BTN2_PRESS // Включить/выключить гирлянду

#define Command_Candle BTN3_1         // Включить/выключить свечки
#define Command_BackGround BTN3_PRESS // Включить/выключить заполнение фона

#define Command_Previous_mode_Demo BTN4_1   // Следующий эффект. Оставляет демонстрационный режим
#define Command_Brightness_minus BTN4_PRESS // Увеличить максимальную яркость и остановится если достигли максимума
#endif

// ==== Конец блока настроек =========================

#if LED_ON
// ==== Команды связанные со светодиодами ============
#define LED1_On digitalWrite(LED1_PIN, HIGH)      // Включить светодиод 1
#define LED1_Off digitalWrite(LED1_PIN, LOW)      // Выключить светодиод 1
#define LED1_FleshH(x) led1Flesh = 4 * x          // Мигнуть быстро x раз 1 светодиодом    (1-15)
#define LED1_Flesh(x) led1Flesh = 64 + (8 * x)    // Мигнуть x раз 1 светодиодом           (1-7)
#define LED1_FleshL(x) led1Flesh = 128 + (16 * x) // Мигнуть медленно x раз 1 светодиодом  (1-7)
#define LED2_On digitalWrite(LED2_PIN, HIGH)      // Включить светодиод 2
#define LED2_Off digitalWrite(LED2_PIN, LOW)      // Выключить светодиод 2
#define LED2_FleshH(x) led2Flesh = 4 * x          // Мигнуть быстро x раз 2 светодиодом    (1-15)
#define LED2_Flesh(x) led2Flesh = 64 + 8 * x      // Мигнуть x раз 2 светодиодом           (1-7)
#define LED2_FleshL(x) led2Flesh = 128 + 16 * x   // Мигнуть медленно x раз 2 светодиодом  (1-7)
#else
#define LED1_On
#define LED1_Off
#define LED1_FleshH(x)
#define LED1_Flesh(x)
#define LED1_FleshL(x)
#define LED2_On
#define LED2_Off
#define LED2_FleshH(x)
#define LED2_Flesh(x)
#define LED2_FleshL(x)
#endif

#if LOG_ON
// ==== макросы вывода в Serial ======================
#define CTG_PRINT(x) Serial.print(x)
#define CTG_PRINTLN(x) Serial.println(x)
#define CTG_PRINTLN_2(x, y) Serial.println(x, y)
#else
#define CTG_PRINT(x)
#define CTG_PRINTLN(x)
#define CTG_PRINTLN_2(x, y)
#endif

// ==== Переменные ===================================

// Установить флаг OFF
void setOff(uint8_t &x);
// Установить флаг ON
void setOn(uint8_t &x);

int qsubd(size_t x, size_t b);
int qsuba(size_t x, size_t b);

#if LED_ON > 0
uint8_t led1Flesh = 0; // Управление мигания светодиодом 1
#if LED_ON > 1
uint8_t led2Flesh = 0; // Управление мигания светодиодом 2
#endif
#endif

uint8_t protocol = 0;
uint32_t command = 0;

// ==== Общие переменные =============================

#if MAX_LEDS < 255
uint8_t numLeds; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити - не более MAX_LEDS
uint8_t kolLeds;
#else
uint16_t numLeds; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити - не более MAX_LEDS
uint16_t kolLeds;
#endif

#if TOP_LENGTH
#if TOP_LENGTH < 255
uint8_t topLength = TOP_LENGTH;
#else
uint16_t topLength = TOP_LENGTH;
#endif
uint8_t topEffect = TOP_EFFECT;
#endif

#if BUTTONS_NUM > 3
uint8_t topColor = 0;
#endif

uint8_t polCandle = 1; // Положение свечи

uint8_t maxBright = 255; // Определение общей яркости; возможно изменение на лету

struct CRGB leds[MAX_LEDS]; // инициализация массива светодиодов

CRGBPalette16 gCurrentPalette; // Использование палитры вместо прямых назначений CHSV или CRGB.
CRGBPalette16 gTargetPalette;  // Поддержка плавной смены палитры
CRGB solid = CRGB::Black;      // Цвет заливки

extern const TProgmemRGBGradientPalettePtr gGradientPalettes[]; // для фиксированных палитр в gradient_palettes.h.

extern const uint8_t gGradientPaletteCount; // Общее количество фиксированных палитр
uint8_t gCurrentPaletteNumber = 0;          // Текущий номер палитры из списка палитр.
uint8_t currentPatternIndex = 0;            // Порядковый номер текущего шаблона
uint32_t demo_time = 0;                     // время демо режима

TBlendType currentBlending = LINEARBLEND; // NOBLEND или LINEARBLEND

#define INITVAL 0x55     // Это значение проверяем в бите корректности EEPROM
#define INITMODE 0       // с этого режима будет старт, по умолчанию 0 (старт с - с черного цвета)
#define INITLEN MAX_LEDS // Размер гирлянды при старте
#define INITDEL 0        // размер задержки при старте в миллисекундах

uint16_t meshdelay; // Timer for the notamesh. Works with INITDEL.

uint8_t ledMode = 0; // номер текущего режима
#if CHANGE_ON == 1
uint8_t newMode = 0; // номер нового режима
#if MAX_LEDS < 255
uint8_t stepMode = MAX_LEDS; // Текущий шаг перехода от нового режима к старому
#else
uint16_t stepMode = MAX_LEDS; // Текущий шаг перехода от нового режима к старому
#endif
#endif

uint8_t demorun = DEMO_MODE;
#if RUNNING_FIRE > 0
#define MAX_MODE 122 // Maximum number of modes.
#else
#define MAX_MODE 42 // Maximum number of modes.
#endif

#ifndef EORDER
uint8_t eorder_index = 2; // сохраненная очередность цветов, если она не задана жестко макросом EORDER
#endif

uint8_t allfreq = 32; // Меняет частоту. Переменная для эффектов one_sin_pal и two_sin.
uint8_t bgclr = 0;    // Общий цвет фона. Переменная для эффектов matrix_pal и one_sin_pal.
uint8_t bgbri = 0;    // Общая фоновая яркость. Переменная для эффектов matrix_pal и one_sin_pal.

// Структура хранения расширенных настроек
#pragma pack(push, 1)
typedef union
{
  struct
  {
    bool Glitter : 1;    // Флаг включения блеска
    bool Background : 1; // Флаг включения заполнения фона
    bool Candle : 1;     // Флаг включения свечей
    bool rezerv0 : 1;    // Зарезервировано
    bool rezerv1 : 1;    // Зарезервировано
    bool rezerv2 : 1;    // Зарезервировано
    bool rezerv3 : 1;    // Зарезервировано
    bool rezerv4 : 1;    // Зарезервировано
  };
  unsigned char Byte;
} ExtendedFlags;
#pragma pack(pop)

ExtendedFlags extFlag; // Флаги расширенных настроек

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
uint8_t randSpark = 0;
#endif

long summ = 0;

// ===================================================

void setOff(uint8_t &x)
{
  if (x < 100)
    x += 100;
}

void setOn(uint8_t &x)
{
  if (x >= 100)
    x -= 100;
}

int qsubd(size_t x, size_t b)
{
  return ((x > b) ? wavebright : 0);
}

int qsuba(size_t x, size_t b)
{
  return ((x > b) ? x - b : 0);
}

// ===================================================

#if SAVE_EEPROM
// инициализация параметров, сохраненных в EEPROM
void eeprom_init()
{
  numLeds = read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN);
  ledMode = read_eeprom_8(EEPROM_INDEX_FOR_STARTMODE);

  // проверка правильности в EEPROM байта корректности записи
  if ((read_eeprom_8(EEPROM_INDEX_FOR_ISINIT) != INITVAL) ||
      (numLeds > MAX_LEDS) ||
      ((ledMode > MAX_MODE) && (ledMode != 100)))
  { // Не корректен
    write_eeprom_8(EEPROM_INDEX_FOR_STARTMODE, INITMODE);
#if MAX_LEDS < 255
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, INITLEN);
#else
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, (uint16_t)(INITLEN) & 0x00ff);
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, (uint16_t)(INITLEN) >> 8);
#endif
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDEL, INITDEL);

    extFlag.Glitter = GLITER_ON;
    extFlag.Background = BACKGR_ON;
    extFlag.Candle = CANDLE_ON;
    write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, extFlag.Byte);
#if !defined(EORDER)
    write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorder_index);
#endif
    write_eeprom_8(EEPROM_INDEX_FOR_ISINIT, INITVAL);

    ledMode = INITMODE;
    numLeds = INITLEN;
    meshdelay = INITDEL;
#if TOP_LENGTH
    write_eeprom_8(EEPROM_INDEX_FOR_TOPEFFECT, topEffect);
#if TOP_LENGTH < 255
    write_eeprom_8(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#else
    write_eeprom_16(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#endif
#if BUTTONS_NUM > 3
    write_eeprom_8(EEPROM_INDEX_FOR_TOPCOLOR, topColor);
#endif
#endif
  }
  else
  {
    extFlag.Byte = read_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG); // Прочитаем расширенные настройки

    maxBright = read_eeprom_8(EEPROM_INDEX_FOR_BRIGHT);
#if !defined(EORDER)
    eorder_index = read_eeprom_8(EEPROM_INDEX_FOR_EORDER);
    if (eorder_index > 5)
    {
      eorder_index = 0;
    }
#endif
    ledMode = read_eeprom_8(EEPROM_INDEX_FOR_STARTMODE);
    numLeds = read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN);
#if MAX_LEDS < 255
    if (read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1))
      // Если почему-то светодиодов больше чем размер переменной
      numLeds = MAX_LEDS;
#else
    numLeds += (uint16_t)read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1) << 8;
#endif
    if (numLeds > MAX_LEDS)
    {
      numLeds = MAX_LEDS;
    }

    meshdelay = read_eeprom_8(EEPROM_INDEX_FOR_STRANDEL);
#if TOP_LENGTH
    topEffect = read_eeprom_8(EEPROM_INDEX_FOR_TOPEFFECT);
    if (topEffect > 3)
    {
      topEffect = 0;
    }
#if TOP_LENGTH < 255
    topLength = read_eeprom_8(EEPROM_INDEX_FOR_TOPLENGTH);
#else
    write_eeprom_16(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#endif
    if (topLength > TOP_LENGTH)
    {
      topLength = TOP_LENGTH;
    }
#if BUTTONS_NUM > 3
    topColor = read_eeprom_8(EEPROM_INDEX_FOR_TOPCOLOR);
    if (topColor > 7)
    {
      topColor = 0;
    }
#endif
#endif
  }
}
#endif

#if TOP_LENGTH > 0
void top();
#endif
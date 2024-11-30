#pragma once

/**
 * @brief файл с настройками программы
 *
 */

#include <FastLED.h>
#if defined(ARDUINO_ARCH_ESP32)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif
#include "src/_eeprom.h"

// ==== Блок настроек прошивки =======================

// ---- Подключенная периферия ------------------

#define LED_ON 0 // Количество индикаторных светодиодов
/* 0 - светодиоды не используются;
 * максимум 2 светодиода; */

#define BUTTONS_NUM 4 // Количество кнопок подключенных к модулю (0 - кнопок нет, максимум 4 кнопки)

// ---- Вывод отладочной информации -------------

#define LOG_ON 0 // Включить отладочный вывод через Serial;
/* 0 - не использовать лог;
 * 1 - включить лог; */

#define SERIAL_BAUDRATE 115200 // скорость работы Serial

// ---- Настройка FastLED -----------------------

#define MAX_LEDS 256 // Максимальное количество светодиодов  в гирлянде, ограничивает количество светодиодов сверху (см. комментарий ниже); очень влияет на память

#define CAN_CHANGE_NUMLEDS 1 // Разрешение изменения количества светодиодов в гирлянде
/* 0 - не разрешено, `numLeds = MAX_LEDS`;
 * 1 - разрешено; */

/*
 * Настройка количества светодиодов в гирлянде (доступно при использовании двух
 * и более кнопок):
 *   - при включении питания модуля удерживать нажатой кнопку №2;
 *   - гирлянда включится в режиме настройки количества светодиодов - будут
 *     светиться все заданные светодиоды; цвет свечения - текущий цвет заливки
 *     фона;
 *   - для настройки используются первая кнопка (для увеличения) и последняя
 *     кнопка (для уменьшения);
 *   - при одиночном клике количество изменяется на одну единицу, при удержании
 *     кнопки нажатой - на 10 единиц; количество светодиодом может быть в
 *     диапазоне от 1 до MAX_LEDS; новое количество будет сохранено в EEPROM;
 *   - дополнительно: если модуль использует более двух кнопок, кликом второй
 *     кнопки меняется цвет заливки фона гирлянды;
 *   - выключить и снова включить модуль для применения настроек;
 */

#define CHIPSET WS2812B // Тип микросхемы светодиодов в гирлянде

// #define EORDER GRB // очередность цветов в чипе;
/* чаще всего используются RGB и GRB;
 * закомментируйте, если хотите иметь возможность настройки
 * модуля под конкретную гирлянду (см. комментарий ниже) */

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
 *   - дополнительно: если модуль использует более двух кнопок, кликом второй
 *     кнопки меняется цвет заливки фона гирлянды;
 *   - дополнительно: если модуль использует четыре кнопки, кликом третьей
 *     кнопки меняется цвет заливки фона гирлянды;
 *   - выключить и снова включить модуль для применения настроек;
 */

#define POWER_V 5 // напряжение блока питания в вольтах

#define POWER_I 2000 // Ток блока питания в миллиамперах; 
/* если ограничение не нужно, задайте POWER_I равным 0;
 * или вообще закомментируйте эту строку */

// ---- Настройки EEPROM ------------------------

#define SAVE_EEPROM 1 // Сохранять настройки запуска в EEPROM
/* 0 - ничего не  хранить;
 * 1 - хранить стартовый режим, длину гирлянды, задержку,
 *     яркость, очередность цветов в чипе, настройки
 *     вершины, цвета заливки фона и расширенные настройки
 *     (состояние * блеска, фона, свечей (включено/
 *     не включено)); */

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
#define EEPROM_INDEX_FOR_BGRCOLOR 21  // Расположение в EEPROM индекса цвета заливки фона (1 байт)

// ---- Настройки вершины -----------------------

#define TOP_POSITION 2 // Позиция вершины елки (используется только в эффекте
/* огня для определения направления движения пламени;
 * для всех остальных эффектов вершина всегда находится
 * в конце гирлянды);
 * 0 - не определена;
 * 1 - вершина в начале гирлянды;
 * 2 - вершина в конце гирлянды; */

#define TOP_LENGTH 8 // Максимальное количество светодиодов, выделенных под
/* вершину елки; если больше нуля, то появляется
 * возможность онлайн настройки этого количества на
 * модуле (см. ниже); */

#define TOP_COLOR CRGB::Red // Цвет заливки вершины

#define TOP_EFFECT 3 // Тип заливки вершины
/* 0 - Просто залить цветом;
 * 1 - случайное переливание;
 * 2- переливание сверху вниз;
 * 3- переливание снизу вверх; */

#define TOP_DELAY 150 // Задержка эффекта в милисекундах

#define TOP_FADING 5 // Затухание

/*
 * Настройка вершины елки (доступно при использовании трех и более кнопок и
 * значении макроса #define TOP_LENGTH` больше нуля):
 *   - при включении питания модуля удерживать нажатой кнопку №3;
 *   - гирлянда включится в режиме настройки вершины - будет светиться только
 *     заданное количество светодиодов (по умолчанию `TOP_LENGTH`) в конце
 *     гирлянды; цвет свечения вершины определяется макросом
 *     `#define TOP_COLOR`; остальные светодиоды будут светиться цветом заливки
 *     фона;
 *   - для настройки количества светодиодов вершины используются первая кнопка
 *     (для увеличения) и последняя кнопка (для уменьшения); количество
 *     светодиодом может быть в диапазоне от 0 до TOP_LENGTH;
 *   - клик второй кнопки определяет тип заполнения вершины - заливка,
 *     переливание или случайное мерцание;
 *   - длинный клик (удержание нажатой около секунды) второй кнопкой меняет
 *     цвет заливки вершины; возможные значения - цвета радуги и белый цвет;
 *   - дополнительно: если модуль использует четыре кнопки, кликом третьей
 *     кнопки меняется цвет заливки фона гирлянды;
 *   - настройки будут сохранены в EEPROM;
 *   - выключить и снова включить модуль для применения настроек;
 */

// ---- Пины для подключения периферии ----------

#define LED_DATA_PIN 6 // Номер пина куда подключена гирлянда

// #define LED_CLK_PIN 10 // Номер пина для подключения линии тактирования гирлянды
/* применяется для светодиодов с четырехпроводным
 * подключение (WS2801, APA102 и т.д.)
 * ЕСЛИ НЕ ИСПОЛЬЗУЕТСЯ - ЗАКОМЕНТИРОВАТЬ */

#define LED1_PIN A0 // Номер пина, куда подключен 1 светодиод
#define LED2_PIN A1 // Номер пина, куда подключен 2 светодиод

#define BTN1_PIN 3 // Номер пина, куда подключена кнопка 1
#define BTN2_PIN 4 // Номер пина, куда подключена кнопка 2
#define BTN3_PIN 5 // Номер пина, куда подключена кнопка 3
#define BTN4_PIN 9 // Номер пина, куда подключена кнопка 4
// кнопки замыкаются на землю, используется внутренняя подтяжка МК

// ---- Настройка эффектов ----------------------

#define BLACKSTART 1 // Первый запуск
/* 0 - начинать с эффекта;
 * 1 - начинать с черного экрана; */

#define GLITER_ON 1 // Включить блеск
/* 0 - блеск отключен;
 * 1 - блеск включен; */

#define CANDLE_KOL 5 // если больше 0, то будут включена имитация свечей;
/* число задает, через какое расстояние друг от друга
 * располагать свечи; */

#define CANDLE_ON 0 // Если включена имитация свечей то
/* 0 - при запуске она будет выключена;
 * 1 - при запуске она будет включена; */

#define CANDLE_40 1 // Управление 40 эффектом (свечи)
/* 1 - при запуске она будет включена по варианту
 * efimova1969, иначе при запуске она будет включена
 * по моему варианту */

#define BACKGR_ON 1 // Включить заполнение черного цвета фоном

#define DEMO_MODE 4 // Режим при включении
/* 0 - последняя запущенная программа;
 * 1 - демо режим с последовательным перебором эффектов;
 * 2 - демо режим с случайным перебором эффектов;
 * 3 - демо режим с последовательным перебором выбранных эффектов;
 * 4 - демо режим с случайным перебором выбранных эффектов; */

#define MY_MODE 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 80, 90, 100, 110, 120
/*
 * Выбранные эффекты; номера пишутся через запятую, можно писать и одинаковые
 * что актуально в демо 3; если закомментировать, то демо 3 и 4 отключаются;
 */

#define DEMO_TIME 40 // Время отображение эффекта в демо режиме в секундах

#define CHANGE_ON 1 // Включить плавную смену эффектов

#define CHANGE_SPARK 1 // Эффект смены
/* 0 - без эффекта;
 * 1 - искры (бенгальский огонь);
 * 2 - яркий свет;
 * 3 - метеорит;
 * 4 - случайный эффект (из 1-3); */

#define CHANGE_TIME 5 // Время в секундах, за которое произойдет плавная смена эффектов

#define DIRECT_TIME 20 // Через сколько секунд менять направление если 0 - не меняем

#define PALETTE_TIME 40 // Через сколько секунд менять палитру если 0 - не меняем

#define PALETTE_SPEED 20 // скорость перехода с одной палитры в другую (1-48)

#define DEV_NOISE16 100 // если Зависает на 22 и 37 режимах, то уменьшаем число

// ---- эффект бегущий огонь из 80-90 годов -----

#define RUNNING_FIRE 1 // 1 Включить эффекты бегущего огня,  42 .. 121 режимы

// ---- Программы бегущего огня ------------

/* описание параметров:
 * - первое число - кол-во ячеек в программе (от 1 до 8) показывает сколько
 *   шагов в эффекте;
 * - второе число - разрядность эффекта (от 1 до 8) показывает сколько
 *   светодиодов используется в эффекте;
 * - остальные числа это программа, количество этих чисел задается в первом
 *   числе, один байт один шаг; */

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
 *   где:
 *     Command_XXXX - код команды, это лучше не менять (см. файл getcommands.h)
 *     YYYYY        - код обработчика (значение соответствующее нажатой
 *                    кнопке библиотеки shButton, это мы определили выше как
 *                    значения BTN_1, BTN_2, BTN_3, BTN_4 и BTN_PRESS, либо
 *                    Значение 0, если команда не используется)
 *                    Если команда не используется то тогда надо YYYYY
 *                    заменить на 0 или закомментировать строку
 *
 * Пример:
 * #define Command_Brightness_plus   BTN1_1 - установить обработку команды
 *                                            "Увеличить максимальную яркость"
 *                                            на нажатие кнопки BTN1
 * #define Command_Brightness_minus  BTN1_2 - установить обработку команды
 *                                            "Уменьшить максимальную яркость"
 *                                            на двойное нажатие кнопки BTN1
 *
 * Доступные варианты команд см. в файле getcommands.h; аналогично можно 
 * добавлять свои команды
 */

// ---- набор команд на кнопках -----------------

#if BUTTONS_NUM == 1
// ---- для одной кнопки (BTN1) -------------

#define Command_Next_mode_Demo BTN1_1        // Следующий эффект. Оставляет демонстрационный режим
#define Command_Glitter BTN1_2               // Включить/выключить сверкание
#define Command_Brightness_plus_R BTN1_PRESS // Увеличить максимальную яркость, при достижения максимума начать с минимума

#elif BUTTONS_NUM == 2
// ---- для двух кнопок (BTN1, BTN2) --------

#define Command_Next_mode_Demo BTN1_1      // Следующий эффект. Оставляет демонстрационный режим
#define Command_Candle BTN1_2              // Включить/выключить свечки
#define Command_Brightness_plus BTN1_PRESS // Увеличить максимальную яркость и остановится если достигли максимума

#define Command_Previous_mode_Demo BTN2_1   // Предыдущий эффект. Оставляет демонстрационный режим
#define Command_Glitter BTN2_2              // Включить/выключить сверкание
#define Command_Brightness_minus BTN2_PRESS // Уменьшить максимальную яркость и остановится если достигли минимума
#elif BUTTONS_NUM == 3

// ---- для трех кнопок (BTN1 .. BTN3) ------

#define Command_Next_mode_Demo BTN1_1      // Следующий эффект. Оставляет демонстрационный режим
#define Command_Brightness_plus BTN1_PRESS // Увеличить максимальную яркость и остановится если достигли максимума

#define Command_Glitter BTN2_1        // Включить/выключить сверкание
#define Command_Candle BTN2_2         // Включить/выключить свечки
#define Command_Start_Stop BTN2_PRESS // Включить/выключить гирлянду

#define Command_Previous_mode_Demo BTN3_1   // Предыдущий эффект. Оставляет демонстрационный режим
#define Command_Brightness_minus BTN3_PRESS // Уменьшить максимальную яркость и остановится если достигли минимума
#elif BUTTONS_NUM > 3

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

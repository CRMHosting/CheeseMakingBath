// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA
// Программа для управления сыроварней - подключение к Датчику температуры и вывод данных в дисплей Nextion

#include <OneWire.h>                  // Подключаем библиотеку для взаимодействия с устройствами, работающими на шине и по протоколу 1-Wire
#include <DallasTemperature.h>        // Подключаем библиотеку с функциями для работы с DS18B20 (запросы, считывание и преобразование возвращаемых данных)

#define ONE_WIRE_BUS 2                // Указываем пин подключения data-вывода датчика температуры
#define term_power 4                  // Указываем пин подключения питания датчика температуры

// Таймер очередного считывания значений с датчика температуры
unsigned long tempReadTimer;

// Частота считывания температуры с датчика (сек)
int tempReadDuration = 4;

// Возможность считывать температуру в текущий момент
boolean tempReadEnable = true;

// Порт для пищалки
#define BEEPER 11

OneWire oneWire(ONE_WIRE_BUS);        // Сообщаем библиотеке об устройстве, работающем по протоколу 1-Wire
DallasTemperature sensors(&oneWire);  // Связываем функции библиотеки DallasTemperature с нашим 1-Wire устройством (DS18B20)

void setup(void)
{
  Serial.begin(9600); // Порт на Nextion будет 9600, но какой то глюк
  Serial.setTimeout(50); // Таймаут ожидания что все пришло
  sensors.begin();                // Запускаем библиотеку измерения температуры
  pinMode(term_power, OUTPUT);    // Определяем пин подключения питания датчика температуры

  // Лампочка на плате
  pinMode(LED_BUILTIN, OUTPUT);

  // Бипер
  pinMode(BEEPER, OUTPUT);
}


float temperature() { // Измеряем температуру 10 секунд
  digitalWrite(term_power, HIGH);                // Включаем питание датчика температуры
  delay(100);                                    // Задержка перед первым измерением 
  sensors.requestTemperatures();                 // Запрос на измерение температуры (1-й ошибочный)
  delay(500);                                    // Задержка перед поторным измерением
  sensors.requestTemperatures();                 // Запрос на измерение температуры (повторный)
  float t = float(sensors.getTempCByIndex(0));   // Получаем значение температуры
  digitalWrite(term_power, LOW);                 // Отключаем питание датчика температуры
//  delay(2000);                                   // Задержка, чтобы датчик не нагревался от частых измерений
  return(t);                                     // Возвращаем значение температуры в место вызова функции
}


void loop() {

  int frequency;

  if(millis() >= tempReadTimer + tempReadDuration * 1000 && tempReadEnable) {
      // Настало время считать данные с датчика и отправить их в Nextion

      //digitalWrite(LED_BUILTIN, HIGH);

      // Отправляем значение температуры в Nextion
      Serial.print("main.tIn.txt=\"");
      Serial.print(String(temperature()*10));
      Serial.print("\"");
      Serial.write(0xFF);
      Serial.write(0xFF);
      Serial.write(0xFF);
      //digitalWrite(LED_BUILTIN, LOW);

      // Обновляем таймер
      tempReadTimer = millis();

  }
  
  // Получаем управляющие сигналы
  if (Serial.available() > 0) {
      // Что то пришло на вход

      // Считываем данные из порта
      String code = Serial.readString();
      
      // Определяем управляющие коды
      if(code == "beepOn") {
          // Пришла команда биперу - гудеть
          digitalWrite(LED_BUILTIN, HIGH);
          //tone(BEEPER, 800,500);
          tone(BEEPER, 1000,500);
          // Запрещаем мерить температуру, пока гудит биппер
          tempReadEnable = false;
      } else if(code == "beepOff") {
          // Пришла команда биперу - выключиться
          digitalWrite(LED_BUILTIN, LOW);
          noTone(BEEPER);
          
          // Включаем возможность мерить температуру
          tempReadEnable = true;
      }
  
  }

}

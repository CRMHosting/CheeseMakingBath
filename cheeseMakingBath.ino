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
#define BEEPER_PIN 11

// Порт для pH-метра
#define pHSensorPin A0

#define pHTimerInterval 20
#define printInterval 800
#define ArrayLenth  40
int pHArray[ArrayLenth];
int pHArrayIndex=0;
#define pHOffset 0.39   // Коэффициент компенсации помех, является разницей между pH эталонного раствора (7.01pH) и тем, что фактически показывает прибор

OneWire oneWire(ONE_WIRE_BUS);        // Сообщаем библиотеке об устройстве, работающем по протоколу 1-Wire
DallasTemperature sensors(&oneWire);  // Связываем функции библиотеки DallasTemperature с нашим 1-Wire устройством (DS18B20)

void setup(void)
{
  Serial.begin(9600); // Порт на Nextion будет 4800, 9600 или 19200, какой то глюк
  Serial.setTimeout(50); // Таймаут ожидания что все пришло
  sensors.begin();                // Запускаем библиотеку измерения температуры
  pinMode(term_power, OUTPUT);    // Определяем пин подключения питания датчика температуры

  // Лампочка на плате
  pinMode(LED_BUILTIN, OUTPUT);

  // Бипер
  pinMode(BEEPER_PIN, OUTPUT);
  
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

  // Переменные для измерения pH
  static unsigned long pHTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;

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
      // Отправляем значение кислотности в Nextion
      Serial.print("main.pHIn.txt=\"");
      Serial.print(String(pHValue*100));
      Serial.print("\"");
      Serial.write(0xFF);
      Serial.write(0xFF);
      Serial.write(0xFF);
      //digitalWrite(LED_BUILTIN, LOW);

      // Обновляем таймер
      tempReadTimer = millis();

  }

  if(millis()-pHTime > pHTimerInterval)
  {
    pHArray[pHArrayIndex++]=analogRead(pHSensorPin);
    if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
    voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
    pHValue = 3.5*voltage+pHOffset;
    pHTime=millis();
    
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
          //tone(BEEPER_PIN, 800,500);
          tone(BEEPER_PIN, 1000,500);
          // Запрещаем мерить температуру, пока гудит биппер
          tempReadEnable = false;
      } else if(code == "beepOff") {
          // Пришла команда биперу - выключиться
          digitalWrite(LED_BUILTIN, LOW);
          noTone(BEEPER_PIN);
          
          // Включаем возможность мерить температуру
          tempReadEnable = true;
      }
  
  }

}

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

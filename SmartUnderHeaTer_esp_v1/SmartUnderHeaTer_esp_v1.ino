#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_DEVICE_NAME           "SmartUnderHeaTer"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"


// Закомментируйте это, чтобы отключить печать и сэкономить место
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <GyverNTC.h>
#include <string>
#include <EEPROM.h>

// Термистор на пине А0
// Сопротивление резистора 10 кОм
// Тепловой коэффициент 3380
GyverNTC therm(0, 10000, 3380);

char auth[] = BLYNK_AUTH_TOKEN;

// Ваши данные Wi-Fi.
// Установите пароль на "" для открытых сетей.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

// Пин реле
int pinRelay = D6;

// Интервал опроса датчиков в мс
int pollingTime = 5000;

// Скорость COM-порта
int baud = 115200;

int pwrValue;
int pinValue;

int tempValue;

// JSON значений питания для Алисы
String onJson = "{\"value\":true}";
String offJson = "{\"value\":false}";

// JSON целевой температуры для Алисы
String json1 = "{\"value\":";
String json2 = "}";

BlynkTimer timer;

// Светодиод
void LED()
{
  int i = 0;
  while (i < 3) {
    digitalWrite(LED_BUILTIN, 0);
    delay(100);
    digitalWrite(LED_BUILTIN, 1);
    delay(100);
    i++;
  }
}

// Питание
void Power()
{
  // Вкл и выкл термостата
  if (pwrValue == 0) {
    Blynk.virtualWrite(V1, offJson);
    Serial.println("Термостат выключен!");
    digitalWrite(pinRelay, 0);
    digitalWrite(LED_BUILTIN, 0);
    delay(300);
    digitalWrite(LED_BUILTIN, 1);
    pinValue = 0;
  } else {
    Blynk.virtualWrite(V1, onJson);
    Serial.println("Термостат включен!");
    pinValue = EEPROM.read(1);
    LED();
  }
}

// Логика работы термостата
void mainThermo()
{
  tempValue = therm.getTempAverage();
  Serial.println();
  
  if (pwrValue == 1) {
    if (tempValue < pinValue) {
      digitalWrite(pinRelay, 1);
      digitalWrite(LED_BUILTIN, 0);
      Serial.println("Нагревание...");
    } else {
      digitalWrite(pinRelay, 0);
      digitalWrite(LED_BUILTIN, 1);
      Serial.println("Остывание...");
    }
  }
  // Вывод показаний
  Serial.print("Температура на датчике: ");
  Serial.println(tempValue);
  Serial.print("Целевая температура: ");
  Serial.println(pinValue);

  String result = String(json1) + String(pinValue) + String(json2);
  Blynk.virtualWrite(V3, result);
}

// Эта функция будет вызываться каждый раз, когда
// записывается значение питания в Virtual Pin V0
BLYNK_WRITE(V0)
{
  pwrValue = param.asInt(); // Присвоение входящего значения с вывода V0 переменной
  Power();
  EEPROM.write(0, pwrValue);
  EEPROM.commit();
}

// Эта функция будет вызываться каждый раз, когда
// записывается значение температуры в Virtual Pin V2
BLYNK_WRITE(V2)
{
  pinValue = param.asInt(); // Присвоение входящего значения с вывода V2 переменной
  EEPROM.write(1, pinValue);
  EEPROM.commit();
  Serial.print("Значение целевой температуры изменено на: ");
  Serial.println(pinValue);
}

void setup()
{
  // Чтение данных из flash
  EEPROM.begin(3);
  pwrValue = EEPROM.read(0);

  // Настройки консоли отладки
  Serial.begin(baud);

  // Объявление пина реле
  pinMode(pinRelay, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  Blynk.begin(auth, ssid, pass);
  // Вы также можете указать сервер:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Проверка состояния питания
  Power();
  delay(3000);

  // Опрос датчиков
  mainThermo();
  timer.setInterval(pollingTime, mainThermo);
}

void loop()
{
  Blynk.run();
  timer.run();
}

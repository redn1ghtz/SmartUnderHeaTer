# SmartUnderHeaTer
* [Описание проекта](#chapter-0)
* [Схема](#chapter-1)
* [Настройка Blynk Cloud и прошивка](#chapter-2)
* [Основные и дополнительные настройки прошивки](#chapter-3)
* [URL управления устройством, доступный из интернета](#chapter-4)
* [Библиотеки других авторов, используемые в проекте](#chapter-5)

<a id="chapter-0"></a>
## Описание проекта
**SmartUnderHeaTer** - прошивка для ESP8266, позволяющая создать умный контроллер для электрических тёпых полов с поддержкой удалённого контроля. Есть возможность добавления в Умный Дом Яндекса через навык [Домовенок Кузя](https://alexstar.ru/).

<a id="chapter-1"></a>
## Схема
![SCHEME](https://github.com/redn1ghtz/SmartUnderHeaTer/blob/main/Pictures/SmartUnderHeaTer.png)
**Один вывод реле подключаем к 220v, второй к нагревателю и соединяем оставшийся свободный провод нагревателя с 220v!**

<a id="chapter-2"></a>
## Настройка Blynk Cloud и прошивка
1) Переходим на сайт [Blynk](https://blynk.io/), входим в аккаунт или регистрируемся.
2) После успешной авторизации переходим во вкладку "Шаблоны" и создаем новый с названием "SmartUnderHeaTer".
3) Во вкладке потоки данных делаем все, как на картинке ниже и применяем изменения:
![SETTINGS](https://github.com/redn1ghtz/SmartUnderHeaTer/blob/main/Pictures/blynkset.jpg)
4) Во вкладке "Поиск" создаем новое устройство из шаблона "SmartUnderHeaTer", также применяем изменения.
5) Скачиваем и устанавливаем библиотеки [Blynk C++ Library](https://github.com/blynkkk/blynk-library) и [GyverNTC](https://github.com/GyverLibs/GyverNTC) в Arduino IDE. Также, если у Вас не установлены платы ESP8266, то устанавливаем их в Arduino IDE (дополнительную информацию можно найти в Интернете).
6) На сайте **Blynk** в нашем новом устройстве выбираем "Информация об устройстве" и переносим TEMPLATE_ID, TEMPLATE_NAME и AUTH_TOKEN в скачанную прошивку (открываем и редактируем прошивку в Arduino IDE), вводим данные Wi-Fi соединения в соответствующее поле в прошивке, вместо "YourNetworkName" и "YourPassword". Меняем параметры сопротивления резистора и теплового коэффициента в зависимости от термистора. Пример на фото ниже:
![SETTINGS](https://github.com/redn1ghtz/SmartUnderHeaTer/blob/main/Pictures/Thermistor_set.png)
7) Прошиваемся в отредактированную прошивку и собираем всё по схеме.

<a id="chapter-3"></a>
## Основные и дополнительные настройки прошивки
* Настройка BLYNK_TEMPLATE_ID (заменить **TMPxxxxxx** на полученный ID на сайте **Blynk**), BLYNK_DEVICE_NAME (необязательный параметр) и BLYNK_AUTH_TOKEN (заменить **YourAuthToken** на полученный токен на сайте **Blynk**):
```c++
#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_DEVICE_NAME           "SmartUnderHeaTer"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"
```

* Настройка порта термистора, сопротивления резистора и теплового коэффициента:
```c++
// Термистор на пине А0
// Сопротивление резистора 10 кОм
// Тепловой коэффициент 3380
GyverNTC therm(0, 10000, 3380);
```
* Настройки соединения Wi-Fi (вместо **YourNetworkName** вводим имя сети, а вместо **YourPassword** пароль от этой же сети):
```c++
// Ваши данные Wi-Fi.
// Установите пароль на "" для открытых сетей.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
```
* Пин управления реле (можно изменить для удобства подключения):
```c++
// Пин реле
int pinRelay = D6;
```
* Интервал опроса датчиков в мс (можно снизить для разгрузки системы или увеличить для более точных значений):
```c++
// Интервал опроса датчиков в мс
int pollingTime = 5000;
```
* Скорость COM-порта для отладки:
```c++
// Скорость COM-порта
int baud = 115200;
```
___Остальные настройки не рекомендуется изменять неопытным пользователям! Иначе это может привести к неработоспособности прошивки!___

<a id="chapter-4"></a>
## URL управления устройством, доступный из интернета
**Вместо "YourAuthToken" в ссылке вставляем полученный AUTH_TOKEN в шаге 6 при настройке!**
1) https://blynk.cloud/external/api/get?token=YourAuthToken&V1 - возвращает статус питания нагревателя в формате json
2) https://blynk.cloud/external/api/update?token=YourAuthToken&V0=0 - **выключить** устройство
3) https://blynk.cloud/external/api/update?token=YourAuthToken&V0=1 - **включить** устройство
4) https://blynk.cloud/external/api/update?token=YourAuthToken&V2={value} - задание целевой температуры
5) https://blynk.cloud/external/api/get?token=YourAuthToken&V3 - возвращает значения целевой температуры в формате json
* Данные URL можно использовать в навыке [Домовенок Кузя](https://alexstar.ru/)

<a id="chapter-5"></a>
## Библиотеки других авторов, используемые в проекте
* [Blynk C++ Library](https://github.com/blynkkk/blynk-library)
* [GyverNTC](https://github.com/GyverLibs/GyverNTC)

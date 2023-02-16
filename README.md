# SmartUnderHeaTer

## Описание проекта
**SmartUnderHeaTer** - прошивка для ESP8266, позволяющая создать умный контроллер для электрических тёпых полов с поддержкой удалённого контроля. Есть возможность добавления в Умный Дом Яндекса через навык [Домовенок Кузя](https://alexstar.ru/).

### Схема
![SCHEME](https://github.com/redn1ghtz/SmartUnderHeaTer/blob/main/Pictures/SmartUnderHeaTer.png)
**Один вывод реле подключаем к 220v, второй к нагревателю и соединяем оставшийся свободный провод нагревателя с 220v!**

#### Настройка Blynk Cloud и прошивка
1) Переходим на сайт [Blynk](https://blynk.io/), входим в аккаунт или регистрируемся.
2) После успешной авторизации переходим во вкладку "Шаблоны" и создаем новый с названием "SmartUnderHeaTer".
3) Во вкладке потоки данных делаем все, как на картинке ниже и применяем изменения:
![SETTINGS](https://github.com/redn1ghtz/SmartUnderHeaTer/blob/main/Pictures/blynkset.jpg)
4) Во вкладке "Поиск" создаем новое устройство из шаблона "SmartUnderHeaTer", также применяем изменения.
5) Скачиваем и устанавливаем библиотеки [Blynk C++ Library](https://github.com/blynkkk/blynk-library) и [GyverNTC](https://github.com/GyverLibs/GyverNTC) в Arduino IDE. Также, если у Вас не установлены платы ESP8266, то устанавливаем их в Arduino IDE (дополнительную информацию можно найти в Интернете).
6) На сайте **Blynk** в нашем новом устройстве выбираем "Информация об устройстве" и переносим TEMPLATE_ID, TEMPLATE_NAME и AUTH_TOKEN в скачанную прошивку (открываем и редактируем прошивку в Arduino IDE), вводим данные Wi-Fi соединения в соответствующее поле в прошивке, вместо "YourNetworkName" и "YourPassword".
7) Прошиваемся в отредактированную прошивку и собираем всё по схеме.

##### URL управления устройством, доступный из интернета
**Вместо "YourAuthToken" в ссылке вставляем полученный AUTH_TOKEN в шаге 6 при настройке!**
1) https://blynk.cloud/external/api/get?token=YourAuthToken&V1 - возвращает статус питания нагревателя в формате json
2) https://blynk.cloud/external/api/update?token=YourAuthToken&V0=0 - **выключить** устройство
3) https://blynk.cloud/external/api/update?token=YourAuthToken&V0=1 - **включить** устройство
4) https://blynk.cloud/external/api/update?token=YourAuthToken&V2={value} - задание целевой температуры
5) https://blynk.cloud/external/api/get?token=YourAuthToken&V3 - возвращает значения целевой температуры в формате json
* Данные URL можно использовать в навыке [Домовенок Кузя](https://alexstar.ru/)

###### Библиотеки других авторов, используемые в проекте
* [Blynk C++ Library](https://github.com/blynkkk/blynk-library)
* [GyverNTC](https://github.com/GyverLibs/GyverNTC)

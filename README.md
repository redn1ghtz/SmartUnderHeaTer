# SmartUnderHeaTer

## Описание проекта
**SmartUnderHeaTer** - прошивка для ESP8266, позволяющая создать умный контроллер для электрических тёпых полов с поддержкой удалённого контроля. Есть возможность добавления в Умный Дом Яндекса через навык "Домовенок Кузя".

### Схема
![SCHEME](https://github.com/redn1ghtz/SmartUnderHeaTer/blob/main/Pictures/SmartUnderHeaTer.png)

#### Настройка Blynk Cloud
1) Переходим на сайт [Blynk](https://blynk.io/), входим в аккаунт или регистрируемся.
2) После успешной авторизации переходим во вкладку "Шаблоны" и создаем новый с названием "SmartUnderHeaTer".
3) Во вкладке потоки данных делаем все, как на картинке ниже:
![SETTINGS](https://github.com/redn1ghtz/SmartUnderHeaTer/blob/main/Pictures/blynk1.jpg)
4) Во вкладке "Поиск" создаем новое устройство из шаблона "SmartUnderHeaTer".
5) В нашем новом устройстве выбираем "Информация об устройстве" и переносим TEMPLATE_ID, TEMPLATE_NAME и AUTH_TOKEN в скачанную прошивку, вводим данные Wi-Fi соединения в соответствующее поле в прошивке, вместо "YourNetworkName" и "YourPassword".
6) Прошиваемся в отредактированную прошивку и собираем всё по схеме.

##### Библиотеки других авторов, используемые в проекте
* [Blynk C++ Library](https://github.com/blynkkk/blynk-library)
* [GyverNTC](https://github.com/GyverLibs/GyverNTC)

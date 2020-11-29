# CheeseMakingBath
### Общее описание
Контроллер для сыродельной ванны. Является дополниительным вспомогательным оборудованием, устанавливаемым помимо автоматики, использующейся в сыроварне.
Не подключается к исполнительым устройствам. Является средством сигнализации о возникновении тех или иных условий и ситуаций.

### Состав файлов
- Nextion - Папка с проектом для контактного дисплея Nextion
  - fonts - Папка с сгенеренными шрифтами для дисплея Nextion
  - images - Папка с графическими файлами, формирующими кнопки и всевозможные элементы в дисплее Nextion
    - buttons - Изображения разнообразных кнопок
    - headers - Изображения заголовков некоторых разделов
    - temperature - Разнообразные значки с температурой
    - other - Прочие графические изображения
  - chees.HMI - Проект для редактора Nextion Editor
  - chees.tft - Скомпилированный файл проекта для загрузки в дисплей Nextion
- cheeseMakingBath.ino - Скетч для управляющей платы для Arduino

### Схема подключения
![Демо-стенд](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/1606628371472.jpg)
![Как выглядит конечное устройство](https://github.com/CRMHosting/CheeseMakingBath/blob/master/docs/images/1606628371454.jpg)

### Используемые материалы и устройства
- [Цветной сенсорный дисплей Nextion Enhanced 3,5” / 480×320](https://amperka.ru/product/display-nextion-enhanced-nx4832k035) - 3 190р
- [Зуммер (Troyka-модуль)](https://amperka.ru/product/troyka-buzzer) - 200р
- [Breadboard Mini](https://amperka.ru/product/breadboard-mini-colored) - 190р
- Контроллер: подойдет любой, где есть пины RX и TX, например вот эта: [Iskra Nano Pro](https://amperka.ru/product/iskra-nano-pro) - 390р
- [Герметичный датчик температуры DS18B20](https://amperka.ru/product/sealed-temperature-sensor-ds18b20) - 240р
- Провода и всякие разъемчики

Альтернативы на Aliexpress позволят значимо сэкономить!

### Дополнительные ссылки
- [Trello](https://trello.com/b/lrTgKUwX/%D1%81%D1%8B%D1%80%D0%BE%D0%B4%D0%B5%D0%BB%D0%B8%D0%B5) со всем, что удалось найти и узнать по сыроделию
- [Сайт](http://cheesehead.ru/) по сыроделию
- [Форум](http://forumcheesehead.ru/) по сыроделию
- [Книга](https://eksmo.ru/book/sovremennoe-syrodelie-dlya-vsekh-ITD1092554/) по сыроделию

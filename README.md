# CheeseMakingBath
### Общее описание
Контроллер для сыродельной ванны. Является дополниительным вспомогательным оборудованием, устанавливаемым помимо автоматики, использующейся в сыроварне.
Не подключается к исполнительным устройствам. Является средством сигнализации о возникновении тех или иных условий и ситуаций. В частности в настоящий момент используется для помещения термо-щупа в ванну с молоком и отображения текущего значения температуры молока, а так же сигнализация о достижении пороговых значений пр инагреве и охлаждении молока. Плюс функции таймера.

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
![Схема подключения](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/Schema_bb.png)
![Демо-стенд](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/1606628371472.jpg)
![Как выглядит конечное устройство](https://github.com/CRMHosting/CheeseMakingBath/blob/master/docs/images/1606628371454.jpg)

### Скрины на экране
- **Главный экран** - Показывает текущую температуру среды, в которую опущен щуп. Есть возможность включить таймер, а также поставить программу нагрева или охлаждения до определенной температуры ![Главный экран Nextion](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/main-280x420.png)
- **Таймер** - Позволяет в пару касаний включить таймер на 30 секунд, 1, 2, 5, 10, 15, 20, 30 минут или 1 час ![Меню выбора таймера в Nextion](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/t-280x420.png) Когда таймер подойдет к нулю, то экран начинает мигать, а зуммер начинает пищщать. В целом его неплохо слышно из другой комнаты. Но если есть сильные посторонние звуки (музыка громко играет, телевизор и так далее), то можно и не услышать.
- **Нагрев** - Данный режим позволяет подать сигнал, когда термодатчик почувствует температуру, достигшую заданной или превышающую ее. В пару касаний можно установить предустановленную температуру ![Экран выбора температуры для нагревания Nextion](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/h-280x420.png)

или указать температуру самостоятельно. Выбор температуры вручную начинается от текущей температуры датчика до 99°С

![Экран указания температуры нагрева в ручном режиме в Nextion](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/h-c-280x420.png)

- **Охлаждение** - Режим схож с режимом **Нагрев**, только контроллер ожидает понижение температуры измеряемой среды. Можно указать или предустановленное значение, и тогда при достижении этой температуры будут подаваться звуковые сигналы и дисплей начнет мигать:

![Меню выбора температуры для охлаждения в Nextion](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/c-280x420.png)

Можно задать любое значение для температуры, начиная от текущей температуры, диагностируемой датчиком, до 4°С

![Меню выбора собственного значения температуры для охлаждения в Nextion](https://raw.githubusercontent.com/CRMHosting/CheeseMakingBath/master/docs/images/c-custom-280x420.png)

### Используемые материалы и устройства
- [Цветной сенсорный дисплей Nextion Enhanced 3,5” / 480×320](https://amperka.ru/product/display-nextion-enhanced-nx4832k035) - 3 190р
- [Зуммер (Troyka-модуль)](https://amperka.ru/product/troyka-buzzer) - 200р
- [Breadboard Mini](https://amperka.ru/product/breadboard-mini-colored) - 190р
- Контроллер: подойдет любой, где есть пины RX и TX, например вот эта: [Iskra Nano Pro](https://amperka.ru/product/iskra-nano-pro) - 390р
- [Герметичный датчик температуры DS18B20](https://amperka.ru/product/sealed-temperature-sensor-ds18b20) - 240р
- Провода и всякие разъемчики

*Цены на ноябрь 2020 года, курс доллара: 75.85р*

Альтернативы на Aliexpress позволят значимо сэкономить!

### Дополнительные ссылки
- [Trello](https://trello.com/b/lrTgKUwX/%D1%81%D1%8B%D1%80%D0%BE%D0%B4%D0%B5%D0%BB%D0%B8%D0%B5) со всем, что удалось найти и узнать по сыроделию
- [Сайт](http://cheesehead.ru/) по сыроделию
- [Форум](http://forumcheesehead.ru/) по сыроделию
- [Книга](https://eksmo.ru/book/sovremennoe-syrodelie-dlya-vsekh-ITD1092554/) по сыроделию

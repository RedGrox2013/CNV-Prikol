# CNV Prikol (мод на мини-игры)

Мод добавляет мини-игры в панель переговоров.

![CNV_Prikol](CNV_Prikol.png "Главное меню мода")
[![video](https://i.ytimg.com/vi/RqXKcPD1Qsc/hqdefault.jpg?sqp=-oaymwEcCPYBEIoBSFXyq4qpAw4IARUAAIhCGAFwAcABBg==&rs=AOn4CLDag9FJ2hAImwiv9Pp3cM9tXxCNfQ "Видео")](https://www.youtube.com/watch?v=RqXKcPD1Qsc)

В моде есть анимации, для того, чтобы музыка воспроизводилась, необходим мод [Prikol](https://www.youtube.com/watch?v=O9_V5AUnSss) или [SmachnayaBEBRA](https://www.youtube.com/watch?v=LRsF8qaEPvQ) (SmachnayaBEBRA включает в себя мод Prikol, по этому вам нужен только 1 из этих модов)

Для работы мода требуется [Spore ModAPI Launcher](https://davoonline.com/sporemodder/rob55rod/ModAPI/Public/) (кроме версии [v1.0](https://github.com/RedGrox2013/CNV-Prikol/releases/tag/v1.0) и более старых, они работают так)
___

## Как зайти в мини-игры

Зайти в мини-игры можно только на этапах "Цивилизация" и "Космос".

### На этапе "Цивилизация"

Зайди в панель переговоров с любой страной, пролистай вниз и найди кнопку ***"Давайте сыграем в игру..."***
![Civilization](Civilization.png)

### На этапе "Космос"

Зайди в панель переговоров > **дипломатия** > ***давайте сыграем в игру...***

![Space1](Space1.png)
![Space2](Space2.png)

___

## Новые действия

Кроме тех действий, которые и так были в Spore, этот мод добавляет новые действия! Вы можете использовать их в своих модах.

Список новых действий:

* `kOpenUrl`: открывает ссылку в браузере. Для того, чтобы указать ссылку, создайте *prop*-файл с ней и укажите, где этот файл находится. Пример: `kOpenUrl CNV_Prikol_URLs!FirstYouTubeChannel.prop`

Пока что всё💀

### Примеры использования новых действий

#### `kOpenUrl`

Вариант ответа в каком-либо диалоге:
```
response
    # Указываем расположение prop-файла
	action kOpenUrl My_URLs!Rickroll.prop
	text ModCreator!0x6CE82084
end
```
Содержимое файла Rickroll.prop.prop_t:
```
# Ссылка, которую мы хотим открыть
string8 url "https://www.youtube.com/watch?v=dQw4w9WgXcQ"

# Следующее действие, которое будет совершено после этого
uint32 nextAction hash(kCnvCommEvent~)

# ResourceKey для этого действия
key actionKey Prikol_diplomacy!ModCreator.cnv

# Если следующее действие из мода, указываем true, если из игры - false
bool nextActionIsCustom false
```

___

## Создатели

Мод сделали **RedGrox** (Дух Ияхо), **Алойчик** и [**Зеленоид**](https://www.youtube.com/channel/UCbJcB6MJciYAmjKKHpkgydA)

* [Основной канал](https://www.youtube.com/c/ДухИяхо)
* [Второй канал](https://www.youtube.com/c/КрутойДухИяхо2013)
* [Телеграм](https://t.me/SporeRedGroxMods)
* [spore.com](http://www.spore.com/view/myspore/RedGrox)

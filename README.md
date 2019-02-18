# SuperT - A game using Qt/QGraphicsView framework.

This game is a second iteration (or should I say tentative) to make a simple game. The motivation was to improve my understanding of Qt/QGraphics framework. Some of the design ideas were copied from this great book: http://www.gameprogrammingpatterns.com/

There is a ton of things to improve, ranging from design (maybe use composition in form of an EntityComponentSystem) and performance. I've ended up using SIGNAL/SLOTS from Qt and that wasn't on my plans, I've wanted to avoid using much of the Meta object features from Qt, but this feature simplifies a lot of the message broking between classes. Maybe on a further iteration I'll change this to a custom publish/subscriber solution.

Some performance degradation is happening when a lot of entities are displayed (on release, that does not seem too noticeable) maybe this might be related to QGraphicsScene management, another improvement oportunity is to build a custom scene management.

Also there is certanly some bugs here and there too, feel free to hunt them! 

I hope this code is useful to other people as an educational tool for making applications in C++ and Qt.

Some screens of the game:

-- MAIN MENU

![main](https://user-images.githubusercontent.com/2021800/48970696-9d9b6400-eff6-11e8-9fbe-219734181bea.png)

-- GAME PLAY

![main2](https://user-images.githubusercontent.com/2021800/48970702-a7bd6280-eff6-11e8-8985-bd48eddb1f26.png)

-- GAME OVER 

![main3](https://user-images.githubusercontent.com/2021800/48970706-aee47080-eff6-11e8-8d71-ce297ce73c9b.png)



MIT license.

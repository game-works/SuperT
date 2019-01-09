#include "spritepackcache.h"

#include <QFile>
#include <QTextStream>

void SpritePackCache::loadFromSpritePack(const QString &sprite_pack_path, const QString &sprite_map_path)
{
    QPixmap sprite_pack(sprite_pack_path);
    QFile file(sprite_map_path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList lst = line.split(" ");
            // tipical line: air_enemy_1 = 129 1667 128 32
            QString name = lst[0];
            int x = lst[2].toInt();
            int y = lst[3].toInt();
            int w = lst[4].toInt();
            int h = lst[5].toInt();
            QPixmap pix = sprite_pack.copy(x, y, w, h);
            QPixmapCache::insert(name.trimmed(), pix);
        }
    }
    file.close();
}



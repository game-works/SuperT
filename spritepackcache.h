#ifndef SPRITE_PACK_CACHE_H
#define SPRITE_PACK_CACHE_H

#include <QString>
#include <QPixmapCache>
#include <QMap>

//!
//! \brief The SpritePackCache class - this class reads a sprite pack caches it and provide means to access individual sprites inside this map
//! the underlying implementation is the actual QPixmapCache from Qt this class adds an helper method to load the sprite pack and caches it
//! under the QPixmapCache, it is importanto to note the size control of QPixmapCache
//!
//! references: https://github.com/nickgravelyn/SpriteSheetPacker
//!
class SpritePackCache : public QPixmapCache
{
public:
    //!
    //! \brief loadFromSpritePack - open the sprite pack image and extract each sprite adding it to the Qpixmacache alongside with the file name as key
    //! \param sprite_pack_path - the path to the sprite pack image file
    //! \param sprite_map_path - the path to the sprite pack map txt file
    //!
    static void loadFromSpritePack(const QString &sprite_pack_path, const QString &sprite_map_path);

private:

    SpritePackCache() = delete;
    ~SpritePackCache() = delete;

    Q_DISABLE_COPY(SpritePackCache)

};

#endif // SPRITE_PACK_CACHE_H

#ifndef TEXTURE_H
#define TEXTURE_H

#include <QPoint>
#include "basetexturemodule.h"

class Texture : public BaseTextureModule {
private:
    QPoint Pos;
public:
    Texture();
    Texture(BaseTextureModule _Base, QPoint _Pos);
    Texture(QString _Name, QPixmap _Texture, QPoint _Pos);
    Texture(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, QPoint _Pos);
    ~Texture();

    QPixmap& GetTexture() { return GetTextureContainer()[0][0]; }
    QPoint& GetPos() { return Pos; }

    Texture& SetPos(QPoint _Pos);
};

#endif // TEXTURE_H

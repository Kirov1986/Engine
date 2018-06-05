#include "texture.h"

Texture::Texture() : BaseTextureModule() {

}

Texture::Texture(BaseTextureModule _Base, QPoint _Pos) : BaseTextureModule(_Base.GetName(), _Base.GetTextureContainer()) {
    Pos = _Pos;
}

Texture::Texture(QString _Name, QPixmap _Texture, QPoint _Pos) : BaseTextureModule(_Name, _Texture) {
    Pos = _Pos;
}

Texture::Texture(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, QPoint _Pos) : BaseTextureModule(_Name, _TextureContainer) {
    Pos = _Pos;
}

Texture::~Texture() {

}

Texture& Texture::SetPos(QPoint _Pos) {
    Pos = _Pos;
    return *this;
}

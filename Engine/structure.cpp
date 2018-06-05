#include "structure.h"

Structure::Structure() {
    Name = "noname";
    State = 1;
}

Structure::Structure(BaseTextureModule _Base, QPoint _Pos) : BaseTextureModule(_Base.GetName(), _Base.GetTextureContainer(), _Base.GetMSecVector(), _Base.GetStateVector()) {
    Pos = _Pos;
    State = 1;
}

Structure::~Structure() {

}

QPixmap& Structure::GetTexture() {
    if (State == 1) return TextureContainer[0][0];
    else return TextureContainer[0][1];
}

Structure& Structure::SetState(bool _Val) {
    State = _Val;
    return *this;
}

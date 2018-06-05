#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <QPoint>
#include "basetexturemodule.h"

class Structure : public BaseTextureModule {
private:
    QPoint Pos;
    int Health;
    bool State;
public:
    Structure();
    Structure(BaseTextureModule _Base, QPoint _Pos);
    ~Structure();

    QPixmap& GetTexture();
    QPoint& GetPos() { return Pos; }

    Structure& SetState(bool _Val);
};

#endif // STRUCTURE_H

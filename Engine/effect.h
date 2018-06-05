#ifndef EFFECT_H
#define EFFECT_H

#include <QPoint>
#include <QTime>
#include "basetexturemodule.h"

class Effect : public BaseTextureModule {
private:
    QPoint Pos;
    double Angle;

    QTime TimePrevA;
    int MSecPerA, MSecGoneA, CurrentA;

    bool Deletable, Ready;
public:
    Effect();
    Effect(BaseTextureModule _Base, QPoint _Pos, double _Angle = 0);
    Effect(QString _Name, QVector<QPixmap> _TextureVector, int _MSecPerA, QPoint _Pos);
    Effect(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, int _MSecPerA, QPoint _Pos);
    ~Effect();

    QPixmap& GetAnimation();
    QPoint GetCenter();
    QPoint& GetPos() { return Pos; }
    double GetAngle() { return Angle; }
    bool IsDeletable() { return Deletable; }
    bool IsReady() { return Ready; }

    Effect& SetPos(const QPoint _Pos);
    Effect& SetAngle(const double _Angle);
    Effect& SetDeletable(const bool _Val);
};

#endif // EFFECT_H

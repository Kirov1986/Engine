#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QPoint>
#include <QPen>
#include <QTime>
#include "functions.h"
#include "character.h"

class Projectile {
private:
    QPointF Pos;
    QPoint PosModifier;
    QString TargetID;
    QPen Style;
    double MoveX, MoveY;
    int LifeDistance, Distance;
    int Damage, Speed, FlyEffect, ExEffect, ExRadius, Length;
    bool Ready;
public:
    Projectile();
    Projectile(QPoint _Pos, QPoint _Target, int _Damage, int _FlyEffect, int _ExEffect, int _ExRadius, int _Speed, int _Fault, QPen _Style, int _Length, int _LifeDistance, QString _TargetID = 0);
    ~Projectile();

    QPointF& GetPos() { return Pos; }
    QString& GetTargetID() { return TargetID; }
    QPen& GetStyle() { return Style; }
    int GetDamage() { return Damage; }
    int GetSpeed() { return Speed; }
    int GetFlyEffect() { return FlyEffect; }
    int GetExEffect() { return ExEffect; }
    int GetExRadius() { return ExRadius; }
    bool IsReady() { return Ready; }
    QPoint GetEndPos();

    Projectile& SetPos(const QPoint _Pos);
    Projectile& SetTargetID(const QString _TargetID);
    Projectile& SetDamage(const int _Damage);
    Projectile& SetSpeed(const int _Speed);
    Projectile& SetFlyEffect(const int _FlyEffect);
    Projectile& SetExEffect(const int _ExEffect);
    Projectile& SetExRadius(const int _ExRadius);
    Projectile& SetStyle(const QPen _Style);
    Projectile& SetLength(const int _Length);
    Projectile& SetReady(const bool _Val);

    Projectile& ChangePos(QVector<Character> &E);
};

#endif // PROJECTILE_H

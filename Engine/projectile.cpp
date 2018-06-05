#include "projectile.h"

Projectile::Projectile() {
    Pos.setX(0);
    Pos.setY(0);
    MoveX = 0;
    MoveY = 0;
    Length = 0;
    Distance = 0;
    LifeDistance = 0;
    Ready = 0;
}

Projectile::Projectile(QPoint _Pos, QPoint _Target, int _Damage, int _FlyEffect, int _ExEffect, int _ExRadius, int _Speed, int _Fault, QPen _Style, int _Length, int _LifeDistance, QString _TargetID) {
    Pos = _Pos;
    TargetID = _TargetID;
    Damage = _Damage;
    Speed = _Speed;
    FlyEffect = _FlyEffect;
    ExEffect = _ExEffect;
    ExRadius = _ExRadius;
    Style = _Style;
    Length = _Length;
    Distance = 0;
    LifeDistance = _LifeDistance;
    Ready = 0;

    double D = CountDistance(_Pos, _Target);
    double F = D / _Speed;
    MoveX = (_Target.x() - _Pos.x() + (_Fault - 2 * _Fault * double(qrand()) / RAND_MAX) * D / 100) / F;
    MoveY = (_Target.y() - _Pos.y() + (_Fault - 2 * _Fault * double(qrand()) / RAND_MAX) * D / 100) / F;

    F = MoveX / MoveY;
    PosModifier = QPoint((Length * F) / sqrt(1 + pow(F, 2)), Length / sqrt(1 + pow(F, 2))); if (MoveY < 0) PosModifier = -PosModifier;
}

Projectile::~Projectile() {

}

QPoint Projectile::GetEndPos() {
    return Pos.toPoint() + PosModifier;
}

Projectile& Projectile::SetPos(const QPoint _Pos) {
    Pos = _Pos;
    return *this;
}

Projectile& Projectile::SetTargetID(const QString _TargetID) {
    TargetID = _TargetID;
    return *this;
}

Projectile& Projectile::SetDamage(const int _Damage) {
    Damage = _Damage;
    return *this;
}

Projectile& Projectile::SetSpeed(const int _Speed) {
    Speed = _Speed;
    return *this;
}

Projectile& Projectile::SetFlyEffect(const int _FlyEffect) {
    FlyEffect = _FlyEffect;
    return *this;
}

Projectile& Projectile::SetExEffect(const int _ExEffect) {
    ExEffect = _ExEffect;
    return *this;
}

Projectile& Projectile::SetExRadius(const int _ExRadius) {
    ExRadius = _ExRadius;
    return *this;
}

Projectile& Projectile::SetStyle(const QPen _Style) {
    Style = _Style;
    return *this;
}

Projectile& Projectile::SetLength(const int _Length) {
    Length = _Length;
    return *this;
}

Projectile& Projectile::SetReady(const bool _Val) {
    Ready = _Val;
    return *this;
}

Projectile& Projectile::ChangePos(QVector<Character> &E) {
    Character T; bool Fl = 0;
    if (TargetID != "0") for (int i = 0; i < E.size(); i++) if (E[i].GetID() == TargetID) {
        T = E[i];
        Fl = 1;
        break;
    }
    if (Fl == 1) {
        double D = CountDistance(Pos.toPoint(), T.GetCenter());
        double F = D / Speed;
        MoveX = (T.GetCenter().x() - Pos.x()) / F;
        MoveY = (T.GetCenter().y() - Pos.y()) / F;
        F = MoveX / MoveY;
        PosModifier = QPoint((Length * F) / sqrt(1 + pow(F, 2)), Length / sqrt(1 + pow(F, 2))); if (MoveY < 0) PosModifier = -PosModifier;
    } else TargetID = "0";
    Pos.setX(Pos.x() + MoveX);
    Pos.setY(Pos.y() + MoveY);
    Distance += sqrt(pow(MoveX, 2) + pow(MoveY, 2));
    if (Distance >= LifeDistance) Ready = 1;
    return *this;
}

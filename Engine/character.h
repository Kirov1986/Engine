#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPointF>
#include <QPoint>
#include <QTime>
#include <qmath.h>
#include "basetexturemodule.h"
#include "functions.h"

class Character : public BaseTextureModule {
private:
    QString ID, TargetID;
    QVector<QString> TargetOfID;

    QPointF Pos;
    QPoint Destination, BodyPos, ShootPos;
    double Angle, BodyAngle;

    int Speed, Range, Health, MaxHealth, TakeDmgEffect, DeathEffect;

    QTime TimePrevA[2];
    int State[2], MSecPerA[2], MSecGoneA[2], CurrentA[2];

    QColor PColor;
    bool AutoGuide;
    int PThick, PLength, PLife;
    int Damage, FlyEffect, ExEffect, ExRadius, PSpeed, PFault;
    int MSecPerShot, MSecGone;
    QTime TimePrev;

    double MoveX, MoveY;
    bool Moving;
    bool Shooting;
    bool ChosenByPlayer;
    bool ChosenByEnemy;
    bool Hovered;

public:
    Character();
    Character(BaseTextureModule _Base, QPoint _Pos, int _Speed, int _Health, QString _ID);
    Character(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, QVector<int> _MSecVector, QVector<int> _StateVector, QPoint _Pos, int _Speed, int _Health, QString _ID);
    Character(const Character &C, QPointF _Pos, QString _ID);
    ~Character();

    QPixmap& GetAnimation(const int Val);
    QPoint GetCenter();
    QPoint GetBodyCenter();
    QPoint GetEndPos();
    QPoint GetShootPos();
    Character& GetTarget(QVector<Character> &Vector);
    Character& GetTargetOf(QVector<Character> &Vector, int i);
    bool IsInRange(QVector<Character> &Vector);
    bool IsReadyToShoot();

    QString& GetID() { return ID; }
    QString& GetTargetID() { return TargetID; }
    QVector<QString>& GetTargetOfID() { return TargetOfID; }
    QPointF& GetPos() { return Pos; }
    QPoint& GetDestination() { return Destination; }
    double GetAngle() { return Angle; }
    double GetBodyAngle() { return BodyAngle; }
    int GetSpeed() { return Speed; }
    int GetRange() { return Range; }
    int GetHealth() { return Health; }
    int GetMaxHealth() { return MaxHealth; }
    int GetTakeDmgEffect() { return TakeDmgEffect; }
    int GetDeathEffect() { return DeathEffect; }
    QColor& GetPColor() { return PColor; }
    bool& GetAutoGuide() { return AutoGuide; }
    int GetPThick() { return PThick; }
    int GetPLength() { return PLength; }
    int GetPLife() { return PLife; }
    int GetDamage() { return Damage; }
    int GetFlyEffect() { return FlyEffect; }
    int GetExEffect() { return ExEffect; }
    int GetExRadius() { return ExRadius; }
    int GetPSpeed() { return PSpeed; }
    int GetPFault() { return PFault; }
    bool IsMoving() { return Moving; }
    bool IsShooting() { return Shooting; }
    bool IsChosenByPlayer() { return ChosenByPlayer; }
    bool IsChosenByEnemy() { return ChosenByEnemy; }
    bool IsHovered() { return Hovered; }

    QSize GetTextureSize();
    QPoint GetTextureCenter();

    Character& SetTargetID(const QString _TargetID);
    Character& SetTargetOfID(const QVector<QString> _TargetOfID);
    Character& AddTargetOfID(const QString _TargetOfID);
    Character& DelTargetOfID(const QString _TargetOfID);
    Character& SetPos(const QPoint _Pos);
    Character& SetDestination(const QPoint _Destination);
    Character& SetBodyPos(const QPoint _BodyPos);
    Character& SetShootPos(const QPoint _ShootPos);
    Character& SetAngle(const double _Angle);
    Character& SetBodyAngle(const double _BodyAngle);
    Character& SetSpeed(const int _Speed);
    Character& SetRange(const int _Range);
    Character& SetHealth(const int _Health);
    Character& SetMaxHealth(const int _MaxHealth);
    Character& SetTakeDmgEffect(const int _TakeDmgEffect);
    Character& SetDeathEffect(const int _DeathEffect);
    Character& SetPColor(const QColor _PColor);
    Character& SetAutoGuide(const bool _Val);
    Character& SetPThick(const int _PThick);
    Character& SetPLength(const int _PLength);
    Character& SetPLife(const int _PLife);
    Character& SetDamage(const int _Damage);
    Character& SetFlyEffect(const int _FlyEffect);
    Character& SetExEffect(const int _ExEffect);
    Character& SetExRadius(const int _ExRadius);
    Character& SetPSpeed(const int _PSpeed);
    Character& SetPFault(const int _PFault);
    Character& SetShooting(const bool _Val);
    Character& SetMSecPerShot(const int _MSecPerShot);
    Character& SetChosenByPlayer(const bool _Val);
    Character& SetChosenByEnemy(const bool _Val);
    Character& SetHovered(const bool _Val);

    Character& ChangePos();
    Character& ChangeBodyAngle(QVector<Character> &Vector);
    Character& StopShooting();
};

#endif // CHARACTER_H

#include "character.h"

Character::Character() : BaseTextureModule() {

}

Character::Character(BaseTextureModule _Base, QPoint _Pos, int _Speed, int _Health, QString _ID) : BaseTextureModule(_Base.GetName(), _Base.GetTextureContainer(), _Base.GetMSecVector(), _Base.GetStateVector()) {
    Speed = _Speed;
    State[0] = 0;
    MSecPerA[0] = MSecVector[0];
    Pos = _Pos;
    MaxHealth = _Health;
    Health = MaxHealth;
    MSecGoneA[0] = 0;
    CurrentA[0] = 0;
    TimePrev = QTime::currentTime();
    MSecPerShot = 100;
    MSecGone = 0;
    Moving = 0;
    ChosenByPlayer = 0;
    ChosenByEnemy = 0;
    Hovered = 0;
    Range = 1000;
    ID = _ID;
    TargetID = "0";
}

Character::Character(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, QVector<int> _MSecVector, QVector<int> _StateVector, QPoint _Pos, int _Speed, int _Health, QString _ID) : BaseTextureModule(_Name, _TextureContainer, _MSecVector, _StateVector) {
    Speed = _Speed;
    State[0] = 0;
    MSecPerA[0] = MSecVector[0];
    Pos = _Pos;
    MaxHealth = _Health;
    Health = MaxHealth;
    MSecGoneA[0] = 0;
    CurrentA[0] = 0;
    TimePrev = QTime::currentTime();
    MSecPerShot = 100;
    MSecGone = 0;
    Moving = 0;
    ChosenByPlayer = 0;
    ChosenByEnemy = 0;
    Hovered = 0;
    Range = 1000;
    ID = _ID;
    TargetID = "0";
}

Character::Character(const Character &C, QPointF _Pos, QString _ID) : BaseTextureModule(C) {
    ID = _ID;
    TargetID = "0";

    Pos = _Pos;
    BodyPos = C.BodyPos;
    ShootPos = C.ShootPos;
    Angle = 0;
    BodyAngle = 0;

    Speed = C.Speed;
    Range = C.Range;
    State[0] = 0;
    State[1] = 0;
    MaxHealth = C.MaxHealth;
    Health = MaxHealth;
    TakeDmgEffect = C.TakeDmgEffect;
    DeathEffect = C.DeathEffect;

    MSecPerA[0] = MSecVector[0];
    MSecPerA[1] = MSecVector[2];
    MSecGoneA[0] = 0;
    MSecGoneA[1] = 0;
    CurrentA[0] = 0;
    CurrentA[1] = 0;
    TimePrevA[0] = QTime::currentTime();
    TimePrevA[1] = QTime::currentTime();

    PColor = C.PColor;
    AutoGuide = C.AutoGuide;
    PThick = C.PThick;
    PLength = C.PLength;
    PLife = C.PLife;
    Damage = C.Damage;
    FlyEffect = C.FlyEffect;
    ExEffect = C.ExEffect;
    ExRadius = C.ExRadius;
    PSpeed = C.PSpeed;
    PFault = C.PFault;
    MSecPerShot = C.MSecPerShot;
    MSecGone = 0;
    TimePrev = QTime::currentTime();

    Moving = 0;
    Shooting = 0;
    ChosenByPlayer = 0;
    ChosenByEnemy = 0;
    Hovered = 0;
}

Character::~Character() {

}

QPixmap& Character::GetAnimation(const int Val) {
    QTime Time = QTime::currentTime();
    int Temp;

    Temp = Time.msec() - TimePrevA[Val].msec();
    if (Time.second() > TimePrevA[Val].second()) Temp += (Time.second() - TimePrevA[Val].second()) * 1000;
    MSecGoneA[Val] += Temp;
    if (MSecGoneA[Val] >= MSecPerA[Val]) {
        ++CurrentA[Val];
        if (CurrentA[Val] == TextureContainer[State[Val] + 2 * Val].size()) CurrentA[Val] = 0;
        MSecGoneA[Val] = 0;
    }
    TimePrevA[Val] = Time;
    return TextureContainer[State[Val] + 2 * Val][CurrentA[Val]];
}

QPoint Character::GetCenter() {
    QSize Temp = TextureContainer[0][0].size();
    return QPoint(Pos.x() + Temp.width() / 2, Pos.y() + Temp.height() / 2);
}

QPoint Character::GetBodyCenter() {
    if (BodyPos.x() == 0 && BodyPos.y() == 0) return GetCenter();
    else return Rotate(BodyPos, QPoint(0, 0), Angle) + GetCenter();
}

QPoint Character::GetEndPos() {
    QSize Temp = TextureContainer[0][0].size();
    return QPoint(Pos.x() + Temp.width(), Pos.y() + Temp.height());
}

QPoint Character::GetShootPos() {
    return Rotate(ShootPos, QPoint(0, 0), BodyAngle) + GetBodyCenter();
}

Character& Character::GetTarget(QVector<Character> &Vector) {
    for (int i = 0; i < Vector.size(); i++) if (Vector[i].GetID() == TargetID) {
        return Vector[i];
        break;
    }
}

Character& Character::GetTargetOf(QVector<Character> &Vector, int i) {
    for (int j = 0; j < Vector.size(); j++) if (Vector[j].GetID() == TargetOfID[i]) {
        return Vector[j];
        break;
    }
}

bool Character::IsInRange(QVector<Character> &Vector) {
    bool Res = 0;
    for (int i = 0; i < Vector.size(); i++) if (CountDistance(Pos.toPoint(), Vector[i].Pos.toPoint()) < Vector[i].GetRange()) Res = 1;
    return Res;
}

bool Character::IsReadyToShoot() {
    QTime Time = QTime::currentTime();
    int Temp;
    bool Res = 0;

    Temp = Time.msec() - TimePrev.msec();
    if (Time.second() > TimePrev.second()) Temp += (Time.second() - TimePrev.second()) * 1000;
    if (Time.minute() > TimePrev.minute()) Temp += (Time.minute() - TimePrev.minute()) * 60000;
    if (Time.hour() > TimePrev.hour()) Temp += (Time.hour() - TimePrev.hour()) * 3600000;
    MSecGone += Temp;
    if (MSecGone >= MSecPerShot) {
        Res = 1;
        MSecGone = 0;
    }
    TimePrev = Time;
    return Res;
}

QSize Character::GetTextureSize() {
    return TextureContainer[0][0].size();
}

QPoint Character::GetTextureCenter() {
    QSize Temp = TextureContainer[0][0].size();
    return QPoint(Temp.width() / 2, Temp.height() / 2);
}

Character& Character::SetPos(const QPoint _Pos) {
    Pos = _Pos;
    return *this;
}

Character& Character::SetTargetID(const QString _TargetID) {
    TargetID = _TargetID;
    Shooting = 1;
    if (State[1] == 0) {
        State[1] = 1;
        MSecPerA[1] = MSecVector[3];
        MSecGoneA[1] = 0;
        CurrentA[1] = 0;
    }
    return *this;
}

Character& Character::SetTargetOfID(const QVector<QString> _TargetOfID) {
    TargetOfID = _TargetOfID;
    return *this;
}

Character& Character::AddTargetOfID(const QString _TargetOfID) {
    TargetOfID.push_back(_TargetOfID);
    return *this;
}

Character& Character::DelTargetOfID(const QString _TargetOfID) {
    TargetOfID.remove(TargetOfID.indexOf(_TargetOfID));
    return *this;
}

Character& Character::SetDestination(const QPoint _Destination) { if (_Destination != Pos) {
    int Distance, N;

    Destination = _Destination;
    Angle = CountAngle(Pos, Destination);

    Distance = CountDistance(Destination, Pos.toPoint());
    N = (Distance / Speed); if (N == 0) N = 1;
    MoveX = (Destination.x() - Pos.x()) / N;
    MoveY = (Destination.y() - Pos.y()) / N;

    if (State[0] == 0) {
        State[0] = 1;
        MSecPerA[0] = MSecVector[1];
        MSecGoneA[0] = 0;
        CurrentA[0] = 0;
    }
    Moving = 1;
    return *this;
}}

Character& Character::SetBodyPos(const QPoint _BodyPos) {
    BodyPos = _BodyPos;
    return *this;
}

Character& Character::SetShootPos(const QPoint _ShootPos) {
    ShootPos = _ShootPos;
    return *this;
}

Character& Character::SetAngle(const double _Angle) {
    Angle =_Angle;
    return *this;
}

Character& Character::SetBodyAngle(const double _BodyAngle) {
    BodyAngle = _BodyAngle;
    return *this;
}

Character& Character::SetShooting(const bool _Val) {
    Shooting = _Val;
    return *this;
}

Character& Character::SetSpeed(const int _Speed) {
    Speed = _Speed;
    return *this;
}

Character& Character::SetRange(const int _Range) {
    Range = _Range;
    return *this;
}

Character& Character::SetMaxHealth(const int _MaxHealth) {
    MaxHealth = _MaxHealth;
    return *this;
}

Character& Character::SetHealth(const int _Health) {
    Health = _Health;
    return *this;
}

Character& Character::SetTakeDmgEffect(const int _TakeDmgEffect){
    TakeDmgEffect = _TakeDmgEffect;
    return *this;
}

Character& Character::SetDeathEffect(const int _DeathEffect) {
    DeathEffect = _DeathEffect;
    return *this;
}

Character& Character::SetPColor(const QColor _PColor) {
    PColor = _PColor;
    return *this;
}

Character& Character::SetAutoGuide(const bool _Val) {
    AutoGuide = _Val;
    return *this;
}

Character& Character::SetPThick(const int _PThick) {
    PThick = _PThick;
    return *this;
}

Character& Character::SetPLength(const int _PLength) {
    PLength = _PLength;
    return *this;
}

Character& Character::SetPLife(const int _PLife) {
    PLife = _PLife;
    return *this;
}

Character& Character::SetDamage(const int _Damage) {
    Damage = _Damage;
    return *this;
}

Character& Character::SetFlyEffect(const int _FlyEffect) {
    FlyEffect = _FlyEffect;
    return *this;
}

Character& Character::SetExEffect(const int _ExEffect) {
    ExEffect = _ExEffect;
    return *this;
}

Character& Character::SetExRadius(const int _ExRadius) {
    ExRadius = _ExRadius;
    return *this;
}

Character& Character::SetPSpeed(const int _PSpeed) {
    PSpeed = _PSpeed;
    return *this;
}

Character& Character::SetPFault(const int _PFault) {
    PFault = _PFault;
    return *this;
}

Character& Character::SetMSecPerShot(const int _MSecPerShot) {
    MSecPerShot = _MSecPerShot;
    return *this;
}

Character& Character::SetChosenByPlayer(const bool _Val) {
    ChosenByPlayer = _Val;
    return *this;
}

Character& Character::SetChosenByEnemy(const bool _Val) {
    ChosenByEnemy = _Val;
    return *this;
}

Character& Character::SetHovered(const bool _Val) {
    Hovered = _Val;
    return *this;
}

Character& Character::ChangePos() {
    Pos.setX(Pos.x() + MoveX);
    Pos.setY(Pos.y() + MoveY);
    if ((MoveX < 0 && Pos.x() < Destination.x()) || (MoveX > 0 && Pos.x() > Destination.x()) || (MoveY < 0 && Pos.y() < Destination.y()) || (MoveY > 0 && Pos.y() > Destination.y())) {
        Pos = Destination;
        --State[0];
        MSecPerA[0] = MSecVector[0];
        MSecGoneA[0] = 0;
        CurrentA[0] = 0;
        Moving = 0;
    }
    return *this;
}

Character& Character::ChangeBodyAngle(QVector<Character> &Vector) {
    BodyAngle = CountAngle(GetBodyCenter(), GetTarget(Vector).GetCenter());
    return *this;
}

Character& Character::StopShooting() {
    Shooting = 0;
    State[1] = 0;
    MSecPerA[1] = MSecVector[2];
    MSecGoneA[1] = 0;
    CurrentA[1] = 0;
    return *this;
}

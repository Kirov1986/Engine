#include "effect.h"

Effect::Effect() : BaseTextureModule() {
    Name = "noname";
    Deletable = 1;
    Ready = 0;
}

Effect::Effect(BaseTextureModule _Base, QPoint _Pos, double _Angle) : BaseTextureModule(_Base.GetName(), _Base.GetTextureContainer(), _Base.GetMSecVector(), _Base.GetStateVector()) {
    TimePrevA = QTime::currentTime();
    MSecPerA = MSecVector[0];
    CurrentA = 0;
    MSecGoneA = 0;
    Pos = _Pos;
    Angle = _Angle;
    Deletable = 1;
    Ready = 0;
}

Effect::Effect(QString _Name, QVector<QPixmap> _TextureVector, int _MSecPerA, QPoint _Pos) : BaseTextureModule(_Name, _TextureVector, _MSecPerA) {
    TimePrevA = QTime::currentTime();
    MSecPerA = MSecVector[0];
    CurrentA = 0;
    MSecGoneA = 0;
    Pos = _Pos;
    Deletable = 1;
    Ready = 0;
}

Effect::Effect(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, int _MSecPerA, QPoint _Pos) : BaseTextureModule(_Name, _TextureContainer, _MSecPerA) {
    TimePrevA = QTime::currentTime();
    MSecPerA = MSecVector[0];
    CurrentA = 0;
    MSecGoneA = 0;
    Pos = _Pos;
    Deletable = 1;
    Ready = 0;
}

Effect::~Effect()
{

}

QPixmap& Effect::GetAnimation() {
    QTime Time = QTime::currentTime();
    int Temp;

    if (Deletable == 1 || CurrentA < TextureContainer[0].size() - 1) {
        Temp = Time.msec() - TimePrevA.msec();
        if (Time.second() > TimePrevA.second()) Temp += (Time.second() - TimePrevA.second()) * 1000;
        MSecGoneA += Temp;
        if (MSecGoneA >= MSecPerA) {
            ++CurrentA;
            if (CurrentA == TextureContainer[0].size()) {
                Ready = 1;
                --CurrentA;
            }
            MSecGoneA = 0;
        }
        TimePrevA = Time;
    }
    return TextureContainer[0][CurrentA];
}

QPoint Effect::GetCenter() {
    QSize Temp = TextureContainer[0][0].size();
    return QPoint(Pos.x() + Temp.width() / 2, Pos.y() + Temp.height() / 2);
}

Effect& Effect::SetPos(const QPoint _Pos) {
    Pos = _Pos;
    return *this;
}

Effect& Effect::SetAngle(const double _Angle) {
    Angle = _Angle;
    return *this;
}

Effect& Effect::SetDeletable(const bool _Val) {
    Deletable = _Val;
    return *this;
}

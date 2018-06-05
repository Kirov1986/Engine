#include "form.h"

Form::Form() {
    Visible = 1;
}

Form::~Form() {

}

QSize Form::GetTextureSize(int i) {
    return TextureContainer[0][i].size();
}

QPoint Form::GetEndPos() {
    QPoint Res;
    if (Dynamic == 0) {
        Res.setX(Pos.x() + GetTextureSize(0).width());
        Res.setY(Pos.y() + GetTextureSize(0).height());
    } else {
        Res.setX(Pos.x() + GetTextureSize(0).width() + Size * GetTextureSize(1).width() + GetTextureSize(2).width());
        Res.setY(Pos.y() + GetTextureSize(0).height());
    }
    return Res;
}

Form& Form::SetPos(const QPoint _Pos) {
    Pos = _Pos;
    return *this;
}

Form& Form::AddButton(const Button _B) {
    Buttons.push_back(_B);
    return *this;
}

Form& Form::SetSize(const int _Size) {
    Size = _Size;
    return *this;
}

Form& Form::SetDynamic(const bool _Val) {
    Dynamic = _Val;
    return *this;
}

Form& Form::SetVisible(const bool _Val) {
    Visible = _Val;
    return *this;
}

#include "button.h"

Button::Button() {
    State = 0;
    Visible = 1;
}

Button::~Button() {

}

QPixmap& Button::GetTexture() {
    return TextureContainer[0][State];
}

QPoint Button::GetEndPos() {
    return QPoint(Pos.x() + GetTextureSize().width(), Pos.y() + GetTextureSize().height());
}

Button& Button::SetPos(const QPoint _Pos) {
    Pos = _Pos;
    return *this;
}

Button& Button::SetState(const int _State) {
    State = _State;
    return *this;
}

Button& Button::SetOpenForm(const int _OpenForm) {
    OpenForm = _OpenForm;
    return *this;
}

Button& Button::SetVisible(const bool _Val) {
    Visible = _Val;
    return *this;
}

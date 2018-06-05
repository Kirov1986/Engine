#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QKeyEvent>
#include <QMouseEvent>
#include "functions.h"
#include "basetexturemodule.h"
#include "texture.h"
#include "character.h"
#include "projectile.h"
#include "effect.h"
#include "structure.h"
#include "form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void UpdateHub();
    void UpdatePos();
    void UpdateFPS();

signals:
    void UpdateHubSignal();

private:
    Ui::MainWindow *ui;

    QVector<BaseTextureModule> BaseTextures, BaseEffects;
    QVector<Character> BaseCharacters, Characters, Enemy;
    QVector<Texture> Map;
    QVector<Projectile> Projectiles;
    QVector<Effect> Effects;
    QVector<Form> UiForms;

    QSize ScreenSize, MapSize;
    QPoint ViewPoint;
    QPoint MousePoint, ChoosePoint;

    QTimer *UpdateTimer, *MoveTimer, *FPSTimer;
    int MapBlocks, FPSCounter, FPS, Key;
    int ID1, ID2, ID3, ID4;
    int N, M, K, i, j, l;
    int MouseMode;
    bool ShowFPS, ShowID, MapMovable;

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // MAINWINDOW_H

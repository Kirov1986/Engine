#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(UpdateHubSignal()), this, SLOT(UpdateHub()));
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    setMouseTracking(1);

    QFile Settings, HFile1;
    QTextStream TStream(&Settings);
    QTextStream TStreamH1(&HFile1);
    QString DirCharacters, DirTerrainTextures, DirEffects, DirUi;

    QVector<QPixmap> TempAnim;
    QVector<QVector<QPixmap> > TempContainer;
    QVector<int> TempMSec;
    QString Temp, TempToInt, TempDir;
    QColor TempColor;
    QSize TempSize;
    QPoint TempPoint;
    Button TempButton;

    ID1 = 65; ID2 = 65; ID3 = 48; ID4 = 48;

    Settings.setFileName("./../Config/ConfigFiles.txt");
    Settings.open(QIODevice::ReadOnly);
    DirCharacters = StreamRead(TStream);
    DirTerrainTextures = StreamRead(TStream);
    DirEffects = StreamRead(TStream);
    DirUi = StreamRead(TStream);
    Settings.close();

    Settings.setFileName(DirCharacters);
    Settings.open(QIODevice::ReadOnly);
    TempToInt = StreamRead(TStream); N = TempToInt.toInt();
    for (i = 0; i < N; i++) {
        BaseCharacters.push_back(Character());
        Temp = StreamRead(TStream);
        HFile1.setFileName(Temp);
        HFile1.open(QIODevice::ReadOnly);
        Temp = StreamRead(TStreamH1); BaseCharacters[i].SetName(Temp);
        TempToInt = StreamRead(TStreamH1); TempSize.setWidth(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); TempSize.setHeight(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetMaxHealth(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetSpeed(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetRange(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetTakeDmgEffect(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetDeathEffect(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetDamage(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetAutoGuide(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetFlyEffect(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetExEffect(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetExRadius(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetMSecPerShot(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetPSpeed(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetPFault(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); TempColor.setRed(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); TempColor.setGreen(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); TempColor.setBlue(TempToInt.toInt()); BaseCharacters[i].SetPColor(TempColor);
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetPThick(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetPLength(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); BaseCharacters[i].SetPLife(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); TempPoint.setX(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); TempPoint.setY(TempToInt.toInt()); BaseCharacters[i].SetBodyPos(TempPoint);
        TempToInt = StreamRead(TStreamH1); TempPoint.setX(TempToInt.toInt());
        TempToInt = StreamRead(TStreamH1); TempPoint.setY(TempToInt.toInt()); BaseCharacters[i].SetShootPos(TempPoint);
        TempToInt = StreamRead(TStreamH1); M = TempToInt.toInt();
        for (j = 0; j < M; j++) {
            TempToInt = StreamRead(TStreamH1); K = TempToInt.toInt();
            for (l = 0; l < K; l++) {
                TempDir = StreamRead(TStreamH1);
                TempAnim.push_back(QPixmap(TempDir));
            }
            TempContainer.push_back(TempAnim);
            TempToInt = StreamRead(TStreamH1);
            TempMSec.push_back(TempToInt.toInt());
            TempAnim.clear();
        }
        BaseCharacters[i].SetTextureContainer(TempContainer);
        BaseCharacters[i].SetMSecVector(TempMSec);
        BaseCharacters[i].SetTextureSize(TempSize);
        TempContainer.clear();
        TempMSec.clear();
        HFile1.close();
    }
    Settings.close();

    Settings.setFileName(DirTerrainTextures);
    Settings.open(QIODevice::ReadOnly);
    TempToInt = StreamRead(TStream); N = TempToInt.toInt();
    for (i = 0; i < N; i++) {
        TempDir = StreamRead(TStream);
        Temp = StreamRead(TStream);
        TempToInt = StreamRead(TStream); TempSize.setWidth(TempToInt.toInt());
        TempToInt = StreamRead(TStream); TempSize.setHeight(TempToInt.toInt());
        BaseTextures.push_back(BaseTextureModule(Temp, QPixmap(TempDir)));
        BaseTextures[i].SetTextureSize(TempSize);
    }
    Settings.close();

    Settings.setFileName(DirEffects);
    Settings.open(QIODevice::ReadOnly);
    TempToInt = StreamRead(TStream); N = TempToInt.toInt();
    for (i = 0; i < N; i++) {
        Temp = StreamRead(TStream);
        TempToInt = StreamRead(TStream); TempSize.setWidth(TempToInt.toInt());
        TempToInt = StreamRead(TStream); TempSize.setHeight(TempToInt.toInt());
        TempToInt = StreamRead(TStream); M = TempToInt.toInt();
        for (j = 0; j < M; j++) {
            TempDir = StreamRead(TStream);
            TempAnim.push_back(QPixmap(TempDir));
        }
        TempToInt = StreamRead(TStream);
        BaseEffects.push_back(BaseTextureModule(Temp, TempAnim, TempToInt.toInt()));
        BaseEffects[i].SetTextureSize(TempSize);
        TempAnim.clear();
    }
    Settings.close();

    Settings.setFileName(DirUi);
    Settings.open(QIODevice::ReadOnly);
    TempToInt = StreamRead(TStream); N = TempToInt.toInt();
    for (i = 0; i < N; i++) {
        UiForms.push_back(Form());
        Temp = StreamRead(TStream); UiForms[i].SetName(Temp);
        TempToInt = StreamRead(TStream); TempPoint.setX(TempToInt.toInt());
        TempToInt = StreamRead(TStream); TempPoint.setY(TempToInt.toInt()); UiForms[i].SetPos(TempPoint);
        TempToInt = StreamRead(TStream); UiForms[i].SetVisible(TempToInt.toInt());
        TempToInt = StreamRead(TStream); UiForms[i].SetDynamic(TempToInt.toInt());
        if (UiForms[i].IsDynamic() == 0) {
            TempDir = StreamRead(TStream);
            TempAnim.push_back(QPixmap(TempDir)); TempContainer.push_back(TempAnim);
            TempToInt = StreamRead(TStream); TempSize.setWidth(TempToInt.toInt());
            TempToInt = StreamRead(TStream); TempSize.setHeight(TempToInt.toInt());
            UiForms[i].SetTextureContainer(TempContainer);
            UiForms[i].SetTextureSize(TempSize);
            TempAnim.clear(); TempContainer.clear();
        } else {
            for (l = 0; l < 3; l++) {
                TempDir = StreamRead(TStream);
                TempAnim.push_back(QPixmap(TempDir));
            }
            TempContainer.push_back(TempAnim);
            TempToInt = StreamRead(TStream); UiForms[i].SetSize(TempToInt.toInt());
            UiForms[i].SetTextureContainer(TempContainer);
            TempAnim.clear(); TempContainer.clear();
        }
        TempToInt = StreamRead(TStream); M = TempToInt.toInt();
        for (j = 0; j < M; j++) {
            TempToInt = StreamRead(TStream); TempPoint.setX(TempToInt.toInt());
            TempToInt = StreamRead(TStream); TempPoint.setY(TempToInt.toInt()); TempButton.SetPos(TempPoint);
            TempToInt = StreamRead(TStream); TempSize.setWidth(TempToInt.toInt());
            TempToInt = StreamRead(TStream); TempSize.setHeight(TempToInt.toInt());
            TempToInt = StreamRead(TStream); TempButton.SetVisible(TempToInt.toInt());
            TempToInt = StreamRead(TStream); TempButton.SetOpenForm(TempToInt.toInt());
            TempToInt = StreamRead(TStream); K = TempToInt.toInt();
            for (l = 0; l < K; l++) {
                TempDir = StreamRead(TStream);
                TempAnim.push_back(QPixmap(TempDir));
            }
            TempContainer.push_back(TempAnim);
            TempButton.SetTextureContainer(TempContainer);
            TempButton.SetTextureSize(TempSize);
            UiForms[i].AddButton(TempButton);
            TempAnim.clear(); TempContainer.clear();
        }
    }
    Settings.close();

    Settings.setFileName("./../Maps/TestMap.txt");
    Settings.open(QIODevice::ReadOnly);
    TempToInt = StreamRead(TStream); MapBlocks = TempToInt.toInt();
    TempToInt = StreamRead(TStream); MapSize.setWidth(TempToInt.toInt());
    TempToInt = StreamRead(TStream); MapSize.setHeight(TempToInt.toInt());
    for (i = 0; i < MapBlocks; i++) {
        TempToInt = StreamRead(TStream); M = TempToInt.toInt();
        TempToInt = StreamRead(TStream); TempPoint.setX(TempToInt.toInt());
        TempToInt = StreamRead(TStream); TempPoint.setY(TempToInt.toInt());
        Map.push_back(Texture(BaseTextures[M], TempPoint));
    }
    Settings.close();
    MapMovable = 1;

    Characters.push_back(Character(BaseCharacters[0], QPoint(410, 450), GenerateID(ID1, ID2, ID3, ID4)));
    Characters.push_back(Character(BaseCharacters[0], QPoint(410, 650), GenerateID(ID1, ID2, ID3, ID4)));
    Characters.push_back(Character(BaseCharacters[1], QPoint(550, 450), GenerateID(ID1, ID2, ID3, ID4)));
    Characters.push_back(Character(BaseCharacters[1], QPoint(550, 650), GenerateID(ID1, ID2, ID3, ID4)));

    Enemy.push_back(Character(BaseCharacters[0], QPoint(1500, 500), GenerateID(ID1, ID2, ID3, ID4)));
    Enemy.push_back(Character(BaseCharacters[0], QPoint(1500, 1000), GenerateID(ID1, ID2, ID3, ID4)));
    Enemy.push_back(Character(BaseCharacters[0], QPoint(2000, 500), GenerateID(ID1, ID2, ID3, ID4)));
    Enemy.push_back(Character(BaseCharacters[0], QPoint(2000, 1000), GenerateID(ID1, ID2, ID3, ID4)));

    ScreenSize.setWidth(QApplication::desktop()->width());
    ScreenSize.setHeight(QApplication::desktop()->height());
    ViewPoint.setX(0);
    ViewPoint.setY(0);
    ChoosePoint.setX(-1);
    ChoosePoint.setY(-1);

    UpdateTimer = new QTimer(this);
    connect(UpdateTimer, SIGNAL(timeout()), this, SLOT(UpdateHub()));
    UpdateTimer->start(0);

    MoveTimer = new QTimer(this);
    connect(MoveTimer, SIGNAL(timeout()), this, SLOT(UpdatePos()));
    MoveTimer->start(20);

    FPSTimer = new QTimer(this);
    connect(FPSTimer, SIGNAL(timeout()), this, SLOT(UpdateFPS()));
    FPSTimer->start(1000);
    FPSCounter = 0; FPS = 0; ShowFPS = 1;

    ShowID = 0;
    MouseMode = 0;
    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete UpdateTimer;
    delete MoveTimer;
    delete FPSTimer;
}

void MainWindow::UpdateHub() {
    QPoint Point;
    if (MapMovable == 1) {
        if (ViewPoint.x() < 0) if (MousePoint.x() == 0) ViewPoint.setX(ViewPoint.x() + 8);
        if (ViewPoint.x() > ScreenSize.width() - MapSize.width()) if (MousePoint.x() == ScreenSize.width() - 1) ViewPoint.setX(ViewPoint.x() - 8);
        if (ViewPoint.y() < 0) if (MousePoint.y() == 0) ViewPoint.setY(ViewPoint.y() + 8);
        if (ViewPoint.y() > ScreenSize.height() - MapSize.height()) if (MousePoint.y() == ScreenSize.height() - 1) ViewPoint.setY(ViewPoint.y() - 8);
    }
    for (i = 0; i < Characters.size(); i++) {
        if (IsInRect(MousePoint, Characters[i].GetPos().toPoint() + ViewPoint, Characters[i].GetEndPos() + ViewPoint) == 1) Characters[i].SetHovered(1); else Characters[i].SetHovered(0);
        if (Characters[i].IsShooting() == 1 && Characters[i].IsReadyToShoot() == 1) {
            Projectiles.push_back(Projectile(Characters[i].GetShootPos(), Characters[i].GetTarget(Enemy).GetCenter(), Characters[i].GetDamage(), Characters[i].GetFlyEffect(), Characters[i].GetExEffect(), Characters[i].GetExRadius(), Characters[i].GetPSpeed(), Characters[i].GetPFault(), QPen(Characters[i].GetPColor(), Characters[i].GetPThick()), Characters[i].GetPLength(), Characters[i].GetPLife()));
            if (Characters[i].GetAutoGuide() == 1) Projectiles.last().SetTargetID(Characters[i].GetTargetID());
            Effects.push_back(Effect(BaseEffects[4], Characters[i].GetShootPos(), Characters[i].GetBodyAngle()));
        }
    }
    for (i = 0; i < Enemy.size(); i++) {
        if (IsInRect(MousePoint, Enemy[i].GetPos().toPoint() + ViewPoint, Enemy[i].GetEndPos() + ViewPoint) == 1) Enemy[i].SetHovered(1); else Enemy[i].SetHovered(0);
        if (Enemy[i].IsMoving() == 0) {
            do {
                Point.setX(Enemy[i].GetPos().x() + qrand() % 200 - 100);
            } while (Point.x() < 0);
            do {
                Point.setY(Enemy[i].GetPos().y() + qrand() % 200 - 100);
            } while (Point.y() < 0);
            Enemy[i].SetDestination(Point);
        }
        if (Enemy[i].GetHealth() <= 0) {
            for (j = 0; j < Characters.size(); j++) if (Characters[j].GetTargetID() == Enemy[i].GetID()) {
                Characters[j].SetTargetID("0");
                Characters[j].StopShooting();
            }
            if (Enemy[i].GetDeathEffect() != -1) Effects.push_back(Effect(BaseEffects[Enemy[i].GetDeathEffect()], Enemy[i].GetCenter(), Enemy[i].GetAngle()));
            Enemy.remove(i);
        }
    }
    for (i = 0; i < Projectiles.size(); i++) {
         for (j = 0; j < Enemy.size(); j++) if (IsInRect(Projectiles[i].GetEndPos(), Enemy[j].GetPos().toPoint(), Enemy[j].GetEndPos()) == 1) {
            if (Projectiles[i].GetExRadius() == 0) {
                Enemy[j].SetHealth(Enemy[j].GetHealth() - Projectiles[i].GetDamage());
                if (Enemy[j].GetTakeDmgEffect() != -1) Effects.push_back(Effect(BaseEffects[Enemy[j].GetTakeDmgEffect()], Projectiles[i].GetEndPos() - BaseEffects[Enemy[j].GetTakeDmgEffect()].GetTextureCenter()));
            } else for (l = 0; l < Enemy.size(); l++) if (CountDistance(Enemy[l].GetCenter(), Projectiles[i].GetEndPos()) < Projectiles[i].GetExRadius()) {
                if (l == j) {
                    Enemy[l].SetHealth(Enemy[l].GetHealth() - Projectiles[i].GetDamage());
                    if (Enemy[l].GetTakeDmgEffect() != -1) Effects.push_back(Effect(BaseEffects[Enemy[l].GetTakeDmgEffect()], Projectiles[i].GetEndPos() - BaseEffects[Enemy[l].GetTakeDmgEffect()].GetTextureCenter()));
                } else {
                    Enemy[l].SetHealth(Enemy[l].GetHealth() - Projectiles[i].GetDamage() * (1 - double(CountDistance(Enemy[l].GetCenter(), Projectiles[i].GetEndPos())) / Projectiles[i].GetExRadius()));
                    Point.setX(Enemy[l].GetPos().toPoint().x() + qrand() % Enemy[l].GetTextureSize().width());
                    Point.setY(Enemy[l].GetPos().toPoint().y() + qrand() % Enemy[l].GetTextureSize().height());
                    if (Enemy[l].GetTakeDmgEffect() != -1) Effects.push_back(Effect(BaseEffects[Enemy[l].GetTakeDmgEffect()], Point - BaseEffects[Enemy[l].GetTakeDmgEffect()].GetTextureCenter()));
                }
            }
            Projectiles[i].SetReady(1);
            break;
        }
    }
    for (i = 0; i < Projectiles.size(); i++) if (Projectiles[i].IsReady() == 1) {
        if (Projectiles[i].GetExEffect() != -1) Effects.push_back(Effect(BaseEffects[Projectiles[i].GetExEffect()], Projectiles[i].GetEndPos() - BaseEffects[Projectiles[i].GetExEffect()].GetTextureCenter()));
        Projectiles.remove(i);
    }
    for (i = 0; i < Effects.size(); i++) if (Effects[i].IsReady() == 1) Effects.remove(i);
    for (i = 0; i < UiForms.size(); i++) if (UiForms[i].IsVisible() == 1) {
        Point = UiForms[i].GetPos();
        Point.setY(ScreenSize.height() - Point.y());
        for (j = 0; j < UiForms[i].GetButtons().size(); j++) if (UiForms[i].GetButton(j).GetState() != 2 && UiForms[i].GetButton(j).IsVisible() == 1) {
            UiForms[i].GetButton(j).SetState(0);
            if (IsInRect(MousePoint, Point + UiForms[i].GetButton(j).GetPos(), Point + UiForms[i].GetButton(j).GetEndPos())) UiForms[i].GetButton(j).SetState(1);
        }
    }
    update();
}

void MainWindow::UpdatePos() {
    for (i = 0; i < Characters.size(); i++) {
        if (Characters[i].IsMoving() == 1) Characters[i].ChangePos();
        if (Characters[i].GetTargetID() != "0") Characters[i].ChangeBodyAngle(Enemy);
    }
    for (i = 0; i < Enemy.size(); i++) {
        if (Enemy[i].IsMoving() == 1) Enemy[i].ChangePos();
        if (Enemy[i].GetTargetID() != "0") Enemy[i].ChangeBodyAngle(Characters);
    }
    for (i = 0; i < Projectiles.size(); i++) {
        Projectiles[i].ChangePos(Enemy);
        if (Projectiles[i].GetFlyEffect() != -1) Effects.push_back(Effect(BaseEffects[Projectiles[i].GetFlyEffect()], Projectiles[i].GetPos().toPoint() - BaseEffects[Projectiles[i].GetFlyEffect()].GetTextureCenter()));
    }
}

void MainWindow::UpdateFPS() {
    FPS = FPSCounter;
    FPSCounter = 0;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter TerrainPinter(this);
    QPoint DrawPoint;

    for (i = 0; i < MapBlocks; i++) {
        DrawPoint = Map[i].GetPos() + ViewPoint;
        TerrainPinter.drawPixmap(DrawPoint.x(), DrawPoint.y(), Map[i].GetTexture());
    }
    for (i = 0; i < Enemy.size(); i++) {
        DrawPoint = Enemy[i].GetPos().toPoint() + ViewPoint;
        TerrainPinter.setPen(QPen(QColor(255, 0, 0), 2, Qt::SolidLine));
        bool Hovered = Enemy[i].IsHovered() == 1 && (ChoosePoint.x() == -1 || ChoosePoint.y() == -1 || CountDistance(MousePoint, ChoosePoint) < 40);
        if (Hovered == 1) TerrainPinter.drawRect(DrawPoint.x(), DrawPoint.y(), Enemy[i].GetTextureSize().width(), Enemy[i].GetTextureSize().height());
        if (Hovered == 1 || Enemy[i].IsInRange(Characters) == 1) {
            double HealthPersent = double(Enemy[i].GetHealth()) / Enemy[i].GetMaxHealth();
            TerrainPinter.fillRect(DrawPoint.x(), DrawPoint.y() - 15, Enemy[i].GetTextureSize().width() * HealthPersent, 10, QBrush(QColor(255, 0, 0)));
            TerrainPinter.setPen(QPen(QColor(73, 73, 73), 2, Qt::SolidLine));
            TerrainPinter.drawRect(DrawPoint.x(), DrawPoint.y() - 15, Enemy[i].GetTextureSize().width(), 10);
        }
        //TerrainPinter.drawPixmap(DrawPoint, Enemy[i].GetAnimation(0));
        TerrainPinter.save();
        TerrainPinter.translate(Enemy[i].GetCenter() + ViewPoint);
        TerrainPinter.rotate(Enemy[i].GetAngle());
        TerrainPinter.drawPixmap(-Enemy[i].GetTextureCenter(), Enemy[i].GetAnimation(0));
        TerrainPinter.restore();
        TerrainPinter.save();
        TerrainPinter.translate(Enemy[i].GetBodyCenter() + ViewPoint);
        if (Enemy[i].GetTargetID() != "0") TerrainPinter.rotate(Enemy[i].GetBodyAngle());
        else TerrainPinter.rotate(Enemy[i].GetAngle());
        TerrainPinter.drawPixmap(-Enemy[i].GetTextureCenter(), Enemy[i].GetAnimation(1));
        TerrainPinter.restore();
    }
    for (i = 0; i < Characters.size(); i++) {
        DrawPoint = Characters[i].GetPos().toPoint() + ViewPoint;
        TerrainPinter.setPen(QPen(QColor(0, 100, 255), 2, Qt::SolidLine));
        if (Characters[i].IsChosenByPlayer() == 1) TerrainPinter.drawRect(DrawPoint.x(), DrawPoint.y(), Characters[i].GetTextureSize().width(), Characters[i].GetTextureSize().height());
        if (Characters[i].IsChosenByPlayer() == 1 || (Characters[i].IsHovered() == 1 && (ChoosePoint.x() == -1 || ChoosePoint.y() == -1 || CountDistance(MousePoint, ChoosePoint) < 40))) {
            double HealthPersent = double(Characters[i].GetHealth()) / Characters[i].GetMaxHealth();
            TerrainPinter.fillRect(DrawPoint.x(), DrawPoint.y() - 15, Characters[i].GetTextureSize().width() * HealthPersent, 10, QBrush(QColor(230, 230, 230)));
            TerrainPinter.setPen(QPen(QColor(73, 73, 73), 2, Qt::SolidLine));
            TerrainPinter.drawRect(DrawPoint.x(), DrawPoint.y() - 15, Characters[i].GetTextureSize().width(), 10);
            if (ShowID == 1) {
                TerrainPinter.setPen(Qt::red);
                TerrainPinter.setFont(QFont("Terminal", 25));
                TerrainPinter.drawText(DrawPoint - QPoint(0, 45), Characters[i].GetID());
                TerrainPinter.drawText(DrawPoint - QPoint(0, 20), Characters[i].GetTargetID());
            }
        }
        TerrainPinter.save();
        TerrainPinter.translate(Characters[i].GetCenter() + ViewPoint);
        TerrainPinter.rotate(Characters[i].GetAngle());
        TerrainPinter.drawPixmap(-Characters[i].GetTextureCenter(), Characters[i].GetAnimation(0));
        TerrainPinter.restore();
        TerrainPinter.save();
        TerrainPinter.translate(Characters[i].GetBodyCenter() + ViewPoint);
        if (Characters[i].GetTargetID() != "0") TerrainPinter.rotate(Characters[i].GetBodyAngle());
        else TerrainPinter.rotate(Characters[i].GetAngle());
        TerrainPinter.drawPixmap(-Characters[i].GetTextureCenter(), Characters[i].GetAnimation(1));
        TerrainPinter.restore();
    }
    for (i = 0; i < Projectiles.size(); i++) {
        TerrainPinter.setPen(Projectiles[i].GetStyle());
        TerrainPinter.drawLine(Projectiles[i].GetPos() + ViewPoint, Projectiles[i].GetEndPos() + ViewPoint);
    }
    for (i = 0; i < Effects.size(); i++) {
        DrawPoint = Effects[i].GetPos() + ViewPoint;
        if (Effects[i].GetAngle() == 0) TerrainPinter.drawPixmap(DrawPoint.x(), DrawPoint.y(), Effects[i].GetAnimation());
        else {
            TerrainPinter.save();
            TerrainPinter.translate(Effects[i].GetPos() + ViewPoint);
            TerrainPinter.rotate(Effects[i].GetAngle());
            TerrainPinter.drawPixmap(-Effects[i].GetTextureCenter(), Effects[i].GetAnimation());
            TerrainPinter.restore();
        }
    }
    if (ChoosePoint.x() != -1 || ChoosePoint.y() != -1) if (CountDistance(MousePoint, ChoosePoint) > 40) {
        TerrainPinter.setPen(QPen(QColor(0, 100, 255), 3, Qt::SolidLine));
        TerrainPinter.drawRect(ChoosePoint.x(), ChoosePoint.y(), MousePoint.x() - ChoosePoint.x(), MousePoint.y() - ChoosePoint.y());
    }

    TerrainPinter.drawPixmap(0 + 10, ScreenSize.height() - 350 - 10, 350, 350, QPixmap("./../Maps/MapOverview.png"));
    TerrainPinter.setPen(QPen(QColor(230, 230, 230), 2, Qt::SolidLine));
    TerrainPinter.drawRect(10 - double(ViewPoint.x()) / MapSize.width() * 350, ScreenSize.height() - 360 - double(ViewPoint.y()) / MapSize.height() * 350, double(ScreenSize.width()) / MapSize.width() * 350, double(ScreenSize.height()) / MapSize.height() * 350);

    for (i = 0; i < UiForms.size(); i++) if (UiForms[i].IsVisible() == 1) {
        DrawPoint = UiForms[i].GetPos();
        DrawPoint.setY(ScreenSize.height() - DrawPoint.y());
        if (UiForms[i].IsDynamic() == 0) TerrainPinter.drawPixmap(DrawPoint, UiForms[i].GetTexture(0));
        else {
            TerrainPinter.drawPixmap(DrawPoint, UiForms[i].GetTexture(0));
            QPoint Override;
            Override.setX(UiForms[i].GetTextureSize(0).width());
            Override.setY(0);
            for (j = 0; j < UiForms[i].GetSize(); j++) {
                TerrainPinter.drawPixmap(DrawPoint + Override, UiForms[i].GetTexture(1));
                Override.setX(Override.x() + UiForms[i].GetTextureSize(1).width());
            }
            TerrainPinter.drawPixmap(DrawPoint + Override, UiForms[i].GetTexture(2));
        }
        for (j = 0; j < UiForms[i].GetButtons().size(); j++) if (UiForms[i].GetButton(j).IsVisible() == 1) TerrainPinter.drawPixmap(DrawPoint + UiForms[i].GetButton(j).GetPos(), UiForms[i].GetButton(j).GetTexture());
    }

    ++FPSCounter;
    if (ShowFPS == 1) {
        TerrainPinter.setPen(Qt::red);
        TerrainPinter.setFont(QFont("Terminal", 25));
        TerrainPinter.drawText(QPoint(15, 40), QString::number(FPS));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Up : ViewPoint.setY(ViewPoint.y() + 16); break;
    case Qt::Key_Down : ViewPoint.setY(ViewPoint.y() - 16); break;
    case Qt::Key_Left : ViewPoint.setX(ViewPoint.x() + 16); break;
    case Qt::Key_Right : ViewPoint.setX(ViewPoint.x() - 16); break;
    case Qt::Key_Escape : this->close(); break;
    case Qt::Key_F11 : ShowID = !ShowID; break;
    case Qt::Key_F12 : ShowFPS = !ShowFPS; break;
    case Qt::Key_Shift : Key = Qt::Key_Shift; break;
    default: QWidget::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *) {
    Key = -1;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    MousePoint.setX(event->x());
    MousePoint.setY(event->y());
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        ChoosePoint.setX(event->x());
        ChoosePoint.setY(event->y());
        MapMovable = 0;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        bool EnemyTargeted = 0;
        for (i = 0; i < Enemy.size(); i++) if (IsInRect(MousePoint, Enemy[i].GetPos().toPoint() + ViewPoint, Enemy[i].GetEndPos() + ViewPoint) == 1) {
            for (j = 0; j < Characters.size(); j++) if (Characters[j].IsChosenByPlayer() == 1) {
                if (Characters[j].GetTargetID() != "0") Characters[j].GetTarget(Enemy).DelTargetOfID(Characters[j].GetID());
                Characters[j].SetTargetID(Enemy[i].GetID());
                Characters[j].ChangeBodyAngle(Enemy);
                Enemy[i].AddTargetOfID(Characters[j].GetID());
                EnemyTargeted = 1;
            }
        }
        if (EnemyTargeted == 0) {
            bool Evoke = 0;
            for (i = 0; i < Characters.size(); i++) if (Characters[i].IsChosenByPlayer() == 1) {
                Characters[i].SetDestination(MousePoint - Characters[i].GetTextureCenter() - ViewPoint);
                Evoke = 1;
            }
            if (Evoke == 1) Effects.push_back(Effect(BaseEffects[1], MousePoint - BaseEffects[1].GetTextureCenter() - ViewPoint));
        }
    }
    if (event->button() == Qt::LeftButton) {
        bool AreaChoosed = 0;
        if (Key != Qt::Key_Shift) for (i = 0; i < Characters.size(); i++) Characters[i].SetChosenByPlayer(0);
        for (i = 0; i < Characters.size(); i++) {
            if (IsInRect(Characters[i].GetCenter() + ViewPoint, ChoosePoint, MousePoint) == 1) {
                Characters[i].SetChosenByPlayer(1);
                AreaChoosed = 1;
            }
            else if (AreaChoosed == 0) if (IsInRect(MousePoint, Characters[i].GetPos().toPoint() + ViewPoint, Characters[i].GetEndPos() + ViewPoint) == 1) {
                Characters[i].SetChosenByPlayer(1);
                break;
            }
        }
        QPoint Point;
        int T;
        for (i = 0; i < UiForms.size(); i++) if (UiForms[i].IsVisible() == 1) {
            Point = UiForms[i].GetPos();
            Point.setY(ScreenSize.height() - Point.y());
            T = -1;
            for (j = 0; j < UiForms[i].GetButtons().size(); j++) if (UiForms[i].GetButton(j).IsVisible() == 1) if (IsInRect(MousePoint, Point + UiForms[i].GetButton(j).GetPos(), Point + UiForms[i].GetButton(j).GetEndPos()) == 1) {
                T = j;
                break;
            }
            if (T != -1) for (j = 0; j < UiForms[i].GetButtons().size(); j++) if (UiForms[i].GetButton(j).IsVisible() == 1) {
                if (j == T) {
                    UiForms[i].GetButton(j).GetState() == 2 ? UiForms[i].GetButton(j).SetState(0) : UiForms[i].GetButton(j).SetState(2);
                    if (UiForms[i].GetButton(j).GetOpenForm() != -1) {
                        int O = UiForms[i].GetButton(j).GetOpenForm();
                        UiForms[O].SetVisible(!UiForms[O].IsVisible());
                    }
                } else {
                    UiForms[i].GetButton(j).SetState(0);
                    if (UiForms[i].GetButton(j).GetOpenForm() != -1) {
                        int O = UiForms[i].GetButton(j).GetOpenForm();
                        UiForms[O].SetVisible(0);
                    }
                }
            }
        }
        ChoosePoint.setX(-1);
        ChoosePoint.setY(-1);
        MapMovable = 1;
    }
}

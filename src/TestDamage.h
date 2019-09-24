#ifndef EFFECTS_TEST_DAMAGE_H
#define EFFECTS_TEST_DAMAGE_H

#include <kwineffects.h>

#include <QElapsedTimer>

class TestDamage : public KWin::Effect
{
    Q_OBJECT
public:
    ~TestDamage();
    TestDamage();
    static bool supported();
    static bool enabledByDefault();

    void postPaintWindow(KWin::EffectWindow *w);
    void drawWindow(KWin::EffectWindow *w, int mask, QRegion region, KWin::WindowPaintData &data);
    void prePaintScreen(KWin::ScreenPrePaintData &data, int time);
    void postPaintScreen();
private:
    QString testWindowCaption;
    bool damageGotten = false;
    QElapsedTimer timer;

public Q_SLOTS:
    void slotWindowClosed(KWin::EffectWindow *w);
    void slotWindowAdded(KWin::EffectWindow *w);
    void damaged(KWin::EffectWindow *w);

Q_SIGNALS:

};

#endif

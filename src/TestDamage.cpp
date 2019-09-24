#include "TestDamage.h"

#include <KGlobalAccel>
#include <KLocalizedString>
#include <kwindowsystem.h>
#include <kwinglplatform.h>
#include <kwinglutils.h>
#include <QAction>
#include <QFile>
#include <QMatrix4x4>
#include <QStandardPaths>
#include <QTimer>
#include <QtDebug>
#include <QProcessEnvironment>


KWIN_EFFECT_FACTORY_SUPPORTED_ENABLED(TestDamageFactory,
                                      TestDamage,
                                      "test_damage.json",
                                      return TestDamage::supported();
                                      , return TestDamage::enabledByDefault();)

TestDamage::TestDamage()
{
    testWindowCaption = QProcessEnvironment::systemEnvironment().value("TEST_DAMAGE_CAPTION", "glxgears");
    qDebug() << "Init test damage plugin for window" << testWindowCaption;

    connect(KWin::effects, SIGNAL(windowDamaged(KWin::EffectWindow *, QRect)), SLOT(damaged(KWin::EffectWindow *)));
    connect(KWin::effects, &KWin::EffectsHandler::windowClosed, this, &TestDamage::slotWindowClosed);
    connect(KWin::effects, &KWin::EffectsHandler::windowAdded, this, &TestDamage::slotWindowAdded);
}

TestDamage::~TestDamage()
{
}

bool TestDamage::supported()
{
    return true;
}

bool TestDamage::enabledByDefault()
{
    return true;
}

void TestDamage::drawWindow(KWin::EffectWindow *w,
                            int mask,
                            QRegion region,
                            KWin::WindowPaintData &data)
{
    //qDebug() << "Draw Window" << w->caption();

    if (testWindowCaption == w->caption()) {
        if (!damageGotten) {
            qDebug() << "drawWindow(): Drawing window" << w->caption() << "without previous damaged event!";
            qDebug() << "drawWindow():" << timer.nsecsElapsed() / (1000. * 1000.) << "ms since last damage";
        }

        damageGotten = false;
    }

    KWin::effects->drawWindow(w, mask, region, data);
}

void TestDamage::damaged(KWin::EffectWindow *w)
{
    if (testWindowCaption == w->caption()) {
        damageGotten = true;

        timer.restart();
    }
}

void TestDamage::postPaintWindow(KWin::EffectWindow *w)
{
    KWin::effects->postPaintWindow(w);
}

void TestDamage::slotWindowClosed(KWin::EffectWindow *w)
{
}

void TestDamage::slotWindowAdded(KWin::EffectWindow *w)
{
}

void TestDamage::prePaintScreen(KWin::ScreenPrePaintData &data, int time)
{
    KWin::effects->prePaintScreen(data, time);
}

void TestDamage::postPaintScreen()
{
    KWin::effects->postPaintScreen();
}

#include "TestDamage.moc"

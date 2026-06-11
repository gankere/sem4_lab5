#include <QTest>
#include <QWidget>
#include "domain.h"
#include "qtcanvaswidget.h"

class PainterTests : public QObject
{
   Q_OBJECT

private slots:
   void updateFactoryWithNullPointer() {
       Canvas canvas(10, 10);
       QtCanvasWidget* widget = new QtCanvasWidget(canvas);
       
       widget->updateFactory(nullptr);  // ← КРАШ здесь
       
       delete widget;
   }
};

QTEST_MAIN(PainterTests)
#include "test.moc"
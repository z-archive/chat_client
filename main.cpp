#include <TelepathyQt4/Debug>
#include <TelepathyQt4/Types>

#include <QApplication>
#include <QtGui>

#include "roster_window.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  Tp::registerTypes();
  Tp::enableDebug(true);
  Tp::enableWarnings(true);

  RosterWindow roster;
  roster.show();

  return app.exec();
}

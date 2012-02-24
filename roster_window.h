#ifndef _CHAT_CLIENT_ROSTER_WINDOW_H_
#define _CHAT_CLIENT_ROSTER_WINDOW_H_

#include <QWidget>

class QPushButton;
class DebugWindow;

class RosterWindow : public QWidget
{
  Q_OBJECT

public:
  RosterWindow(QWidget *parent= 0);
  virtual ~RosterWindow();

signals:
  void quit();
  void trace(const QString&);

protected:
  virtual void closeEvent(QCloseEvent*);

private slots:
  void accountManager();

private:
  void setupUi();

};

#endif /* _CHAT_CLIENT_ROSTER_WINDOW_H_ */

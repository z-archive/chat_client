#ifndef _CHAT_CLIENT_ROSTER_WINDOW_H_
#define _CHAT_CLIENT_ROSTER_WINDOW_H_

#include <QMainWindow>

class RosterWindow : public QMainWindow
{
  Q_OBJECT
public:
  RosterWindow(QWidget *parent= 0);
  virtual ~RosterWindow();

private slots:
  void accountManager();
  void debugWindow();
  
private:
  void setupUi();
};

#endif /* _CHAT_CLIENT_ROSTER_WINDOW_H_ */

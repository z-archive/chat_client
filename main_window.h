#ifndef _CHAT_CLIENT_MAIN_WINDOW_H_
#define _CHAT_CLIENT_MAIN_WINDOW_H_

#include <QWidget>

class QPushButton;
class DebugWindow;

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent= 0);
  virtual ~MainWindow();

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

#endif /* _CHAT_CLIENT_MAIN_WINDOW_H_ */

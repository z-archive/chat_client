#ifndef _CHAT_CLIENT_WINDOW_H_
#define _CHAT_CLIENT_WINDOW_H_

#include <QWidget>

class Window : public QWidget
{
  Q_OBJECT
public:
  Window(const QString& title);
  virtual ~Window();

signals:
  void quit();
  void trace(const QString&);
	     
protected:
  virtual void closeEvent(QCloseEvent*);
};

#endif /* _CHAT_CLIENT_WINDOW_H_ */

#ifndef _CHAT_CLIENT_ROSTER_WIDGET_H_
#define _CHAT_CLIENT_ROSTER_WIDGET_H_

#include <QWidget>

class QListWidget;

class RosterWidget : public QWidget
{
  Q_OBJECT
public:
  RosterWidget(QWidget *parent);
  virtual ~RosterWidget();

private:
  void setupUi();

private:
  QListWidget *m_contact_list;
};

#endif /* _CHAT_CLIENT_ROSTER_WIDGET_H_ */

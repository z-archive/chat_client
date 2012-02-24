#ifndef _CHAT_CLIENT_ROSTER_H_
#define _CHAT_CLIENT_ROSTER_H_

#include <QWidget>

class QListWidget;

class Roster : public QWidget
{
  Q_OBJECT
public:
  Roster(QWidget *parent);
  virtual ~Roster();

private:
  void setupUi();

private:
  QListWidget *m_contact_list;
};

#endif /* _CHAT_CLIENT_ROSTER_H_ */

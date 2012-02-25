#ifndef _CHAT_CLIENT_ACCOUNT_MODEL_H_
#define _CHAT_CLIENT_ACCOUNT_MODEL_H_

#include <QAbstractTableModel>
#include <TelepathyQt4/Types>

namespace Tp
{
class PendingOperation;
}

class AccountModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  enum EColumn
  {
    eValid,
    eEnabled,
    eDisplayName
  };

public:
  AccountModel(QObject *parent= 0);
  virtual ~AccountModel();
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role= Qt::DisplayRole) const;
  QVariant headerData(int section,
		      Qt::Orientation orientation= Qt::Horizontal,
		      int role= Qt::DisplayRole) const;

private slots:
  void onReady(Tp::PendingOperation*);
  void onNewAccount(const Tp::AccountPtr &account);
 
protected:
  Tp::AccountManagerPtr m_account_manager;
  QList<Tp::AccountPtr> m_account_list;
};

#endif /* _CHAT_CLIENT_ACCOUNT_MODEL_H_ */

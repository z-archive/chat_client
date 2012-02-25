#ifndef _CHAT_CLIENT_ACCOUNT_MODEL_H_
#define _CHAT_CLIENT_ACCOUNT_MODEL_H_

#include <QAbstractListModel>
#include <TelepathyQt4/Types>

namespace Tp
{
class PendingOperation;
}

class AccountModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum EColumn
  {
    eValid,
    eEnabled,
    eConnectionManager,
    eProtocolName,
    eDisplayName,
    eNickName,
    eConnectAutomatically,
    eAutomaticPresence,
    eCurrentPresence,
    eRequestedPresence,
    eChangingPresence,
    eConnectionStatus,
    eConnection,
    eColumnCount
  };

public:
  AccountModel(QObject *parent= 0);
  virtual ~AccountModel();

public:
  int rowCount(const QModelIndex &parent= QModelIndex()) const;
  int columnCount(const QModelIndex &parent= QModelIndex()) const;

public:
  QVariant data(const QModelIndex &index, int role= Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);

  bool becomeUpdate(Tp::PendingOperation *operation);
  static bool editable(int);

public:
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

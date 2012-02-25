#ifndef _CHAT_CLIENT_ACCOUNT_MANAGER_H_
#define _CHAT_CLIENT_ACCOUNT_MANAGER_H_

#include "window.h"

class AccountModel;

class AccountManager : public Window
{
  Q_OBJECT

public:
  AccountManager();
  virtual ~AccountManager();

private:
  void setupUi();
};

#endif /* _CHAT_CLIENT_ACCOUNT_MANAGER_H_ */

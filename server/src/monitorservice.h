#ifndef MONITORSERVICE_H
#define MONITORSERVICE_H

#include <muduo/net/TcpServer.h>
#include "db.h"

class MonitorService {
 public:
  virtual void onQuery(const muduo::net::TcpConnectionPtr&,
                       const MessagePtr& message, muduo::Timestamp) {}
 private:
  DB db_;
};

#endif

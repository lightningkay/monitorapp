#include "monitorserver.h"

using namespace muduo;
using namespace muduo::net;

void MonitorServer::onConnection(const TcpConnectionPtr& conn) {
  LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");
}

void MonitorServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf,
                              Timestamp) {
  buf->retrieveAll();
}

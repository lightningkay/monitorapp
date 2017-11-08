#ifndef MONITORSERVER_H
#define MONITORSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <boost/bind.hpp>


class MonitorServer
{
 public:
  MonitorServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress& listenAddr)
    : server_(loop, listenAddr, "MonitorServer")
  {
    server_.setConnectionCallback(
            boost::bind(&MonitorServer::onConnection,  this, _1));
    server_.setMessageCallback(
            boost::bind(&MonitorServer::onMessage, this, _1, _2, _3));
  }

  void start()
  {
    server_.start();
  }

 private:
  void onConnection(const muduo::net::TcpConnectionPtr& conn)
  {
    LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
  }

  void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp)
  {
      buf->retrieveAll();
  }

  muduo::net::TcpServer server_;
};
#endif

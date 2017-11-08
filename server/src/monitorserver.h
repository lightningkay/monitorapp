#ifndef MONITORSERVER_H
#define MONITORSERVER_H

#include "dispatcher.h"
#include "codec.h"
#include "monitorservice.h"

#include <muduo/net/TcpServer.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <boost/bind.hpp>
#include <query.pb.h>

class MonitorServer {
 public:
  MonitorServer(muduo::net::EventLoop* loop,
                const muduo::net::InetAddress& listenAddr)
      : server_(loop, listenAddr, "MonitorServer"),
        service_(),
        dispatcher_(
            boost::bind(&MonitorServer::onUnknownMessage, this, _1, _2, _3)),
        codec_(boost::bind(&ProtobufDispatcher::onProtobufMessage, &dispatcher_,
                           _1, _2, _3)) {
    dispatcher_.registerMessageCallback<bjut::Query>(
        boost::bind(&MonitorService::onQuery, &service_, _1, _2, _3));
    server_.setConnectionCallback(
        boost::bind(&MonitorServer::onConnection, this, _1));
    server_.setMessageCallback(
        boost::bind(&ProtobufCodec::onMessage, &codec_, _1, _2, _3));
  }

  void start() { server_.start(); }

 private:
  void onConnection(const muduo::net::TcpConnectionPtr& conn);

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf, muduo::Timestamp);

  void onUnknownMessage(const muduo::net::TcpConnectionPtr& conn,
                        const MessagePtr& message, muduo::Timestamp) {
    LOG_INFO << "onUnknownMessage: " << message->GetTypeName();
    conn->shutdown();
  }

  muduo::net::TcpServer server_;
  MonitorService service_;
  ProtobufDispatcher dispatcher_;
  ProtobufCodec codec_;
};
#endif

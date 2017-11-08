#include <iostream>
#include "monitorserver.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    return 0;
  }
  LOG_INFO << "pid = " << getpid();
  short port = static_cast<short>(atoi(argv[1]));
  muduo::net::EventLoop loop;
  muduo::net::InetAddress listenAddr(port);
  MonitorServer server(&loop, listenAddr);
  server.start();
  loop.loop();
  return 0;
}

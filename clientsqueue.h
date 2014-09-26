#ifndef CLIENTSQUEUE_H
#define CLIENTSQUEUE_H


#include <mutex>
#include <queue>

class ClientsQueue {
public:
    ClientsQueue();
    void push(int client);
    int pop();
    unsigned long getClientsNumber();
private:
    std::recursive_mutex _lock;
    std::queue<int> clients;
    unsigned long clientsNumber;
};

#endif // CLIENTSQUEUE_H

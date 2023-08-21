#include <SFML/Network.hpp>

#include <iostream>
#include <Windows.h>


using namespace std;
using namespace sf;

int main()
{
    UdpSocket socket;
    socket.bind(12346);
    socket.setBlocking(true);
    Packet packet;
    IpAddress ip;
    unsigned short port;
    socket.receive(packet,ip,port);
    cout << (char*)(packet.getData());

    return 0;
}
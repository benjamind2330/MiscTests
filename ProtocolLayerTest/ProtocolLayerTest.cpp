// ProtocolLayerTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "SimpleBuffer.hpp"
#include "BinaryArchive.hpp"
#include "RoutineLayer.hpp"
#include "Packet.hpp"
#include "ArgumentData.hpp"

const size_t PACKET_DEFAULT_SIZE = 512;


char SendMedium[PACKET_DEFAULT_SIZE];

void send(const Packet &packet)
{
    packet.write(SendMedium, PACKET_DEFAULT_SIZE);
}

void receive(Packet &packet)
{
    packet.read(SendMedium, PACKET_DEFAULT_SIZE);
}

void ITP(Packet &packet)
{
    std::cout << "ITP Keyword\n";

    RoutineLayerData routineData(5, 'c');

    packet.addLayer(
        std::bind(&RoutineLayerData::serialize, &routineData, std::placeholders::_1),
        std::bind(&RoutineLayerData::dataSize, &routineData));

    ArgumentData argsData;
    argsData.setCommand(4);

    packet.addLayer(
        std::bind(&ArgumentData::serialize, &argsData, std::placeholders::_1),
        std::bind(&ArgumentData::dataSize, &argsData));
}


void ITPRequestManager(Packet &packet)
{
    std::cout << "ITP Request Manager\n";
    ArgumentData argsData;
    packet.popLayer(std::bind(&ArgumentData::deserialize, &argsData, std::placeholders::_1));

    std::cout << "Dispatching request " << argsData.getcommand() << std::endl;
}

void FRoutine(Packet &packet)
{

    std::cout << "Routine\n";
    RoutineLayerData routineDataRecv;

    packet.popLayer(std::bind(&RoutineLayerData::deserialize, &routineDataRecv, std::placeholders::_1));

    std::cout << "Doing request " << routineDataRecv.get1() << " " << routineDataRecv.get2() << std::endl;
}


int main()
{
    Packet sendPacket(PACKET_DEFAULT_SIZE);

    ITP(sendPacket);


    send(sendPacket);

    // ---- Comm barrier


    Packet receivePacket(PACKET_DEFAULT_SIZE);
    receive(receivePacket);

    ITPRequestManager(receivePacket);
    FRoutine(receivePacket);
    

    std::getchar();
    return 0;
}


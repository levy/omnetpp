//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "StandardStart.h"

namespace phy {

Define_Module(StandardStart);

void StandardStart::initialize()
{
    bitrate = par("bitrate");
    cutthroughBitLength = par("cutthroughBitLength");
    cutthroughModule = dynamic_cast<StandardStart *>(getModuleByPath(par("cutthroughModule")));
    txEndTimer = new cMessage("TxEndTimer");
    rxEndTimer = new cMessage("RxEndTimer");
    cutthroughTimer = new cMessage("CutthroughTimer");
    gate("mediumIn")->setDeliverOnReceptionStart(true);
}

StandardStart::~StandardStart()
{
    cancelAndDelete(txEndTimer);
    cancelAndDelete(rxEndTimer);
    cancelAndDelete(cutthroughTimer);
    delete rxPacket;
}

void StandardStart::handleMessage(cMessage *message)
{
    if (message->arrivedOn("upperLayerIn"))
        receiveFromUpperLayer(check_and_cast<cPacket *>(message));
    else if (message->arrivedOn("mediumIn"))
        receiveFromMedium(check_and_cast<cPacket *>(message));
    else if (message == txEndTimer)
        endTx();
    else if (message == rxEndTimer)
        endRx();
    else if (message == cutthroughTimer)
        tryCutthrough();
    else
        throw cRuntimeError("Unknown message");
}

void StandardStart::receiveFromUpperLayer(cPacket *packet)
{
    startTx(packet);
}

void StandardStart::sendToUpperLayer(cPacket *packet)
{
    send(packet, gate("upperLayerOut"));
}

void StandardStart::receiveFromMedium(cPacket *packet)
{
    startRx(packet);
}

void StandardStart::sendToMedium(cPacket *packet)
{
    send(packet, gate("mediumOut"));
}

void StandardStart::startTx(cPacket *packet)
{
    if (txPacket != nullptr)
        throw cRuntimeError("Another packet is already being sent");
    packet->setDuration(calculateDuration(packet));
    scheduleTxEnd(packet);
    sendToMedium(packet);
    txPacket = packet;
}

void StandardStart::endTx()
{
    txPacket = nullptr;
}

void StandardStart::startRx(cPacket *packet)
{
    rxPacket = packet;
    rxCutthrough = false;
    if (cutthroughModule != nullptr)
        scheduleCutthroughStart(rxPacket);
    scheduleRxEnd(rxPacket);
}

void StandardStart::endRx()
{
    if (!rxCutthrough)
        sendToUpperLayer(rxPacket);
    rxPacket = nullptr;
    rxCutthrough = false;
}

void StandardStart::tryCutthrough()
{
    rxCutthrough = cutthroughModule->txPacket == nullptr;
    if (rxCutthrough) {
        EV_INFO << "Starting cutthrough: packetName = " << rxPacket->getName() << std::endl;
        cutthroughModule->startTx(rxPacket);
    }
}

simtime_t StandardStart::calculateDuration(cPacket *packet)
{
    return packet->getBitLength() / bitrate;
}

void StandardStart::scheduleTxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), txEndTimer);
}

void StandardStart::scheduleRxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), rxEndTimer);
}

void StandardStart::scheduleCutthroughStart(cPacket *packet)
{
    scheduleAt(simTime() + cutthroughBitLength / bitrate, cutthroughTimer);
}

} // namespace phy

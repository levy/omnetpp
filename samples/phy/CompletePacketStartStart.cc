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

#include "CompletePacketStartStart.h"

namespace phy {

Define_Module(CompletePacketStartStart);

void CompletePacketStartStart::initialize()
{
    bitrate = par("bitrate");
    cutthroughBitLength = par("cutthroughBitLength");
    cutthroughModule = dynamic_cast<CompletePacketStartStart *>(getModuleByPath(par("cutthroughModule")));
    txEndTimer = new cMessage("TxEndTimer");
    rxEndTimer = new cMessage("RxEndTimer");
    cutthroughTimer = new cMessage("CutthroughTimer");
    gate("mediumIn")->setDeliverOnReceptionStart(true);
}

CompletePacketStartStart::~CompletePacketStartStart()
{
    cancelAndDelete(txEndTimer);
    cancelAndDelete(rxEndTimer);
    cancelAndDelete(cutthroughTimer);
    delete rxPacket;
}

void CompletePacketStartStart::handleMessage(cMessage *message)
{
    if (message->arrivedOn("upperLayerIn"))
        receiveFromUpperLayer(check_and_cast<cPacket *>(message));
    else if (message->arrivedOn("mediumIn"))
        receiveFromMedium(message);
    else if (message == txEndTimer)
        endTx();
    else if (message == rxEndTimer)
        endRx();
    else if (message == cutthroughTimer)
        tryCutthrough();
    else
        throw cRuntimeError("Unknown message");
}

void CompletePacketStartStart::receiveFromUpperLayer(cPacket *packet)
{
    startTx(packet);
}

void CompletePacketStartStart::sendToUpperLayer(cPacket *packet)
{
    send(packet, gate("upperLayerOut"));
}

void CompletePacketStartStart::receiveCompletePacketAtStart(cPacket *packet)
{
    startRx(packet);
}

void CompletePacketStartStart::sendToMedium(cPacket *packet)
{
    sendCompletePacketAtStart(packet, gate("mediumOut"), packet->getDuration());
}

void CompletePacketStartStart::startTx(cPacket *packet)
{
    if (txPacket != nullptr)
        throw cRuntimeError("Another packet is already being sent");
    packet->setDuration(calculateDuration(packet));
    scheduleTxEnd(packet);
    sendToMedium(packet);
    txPacket = packet;
}

void CompletePacketStartStart::endTx()
{
    txPacket = nullptr;
}

void CompletePacketStartStart::startRx(cPacket *packet)
{
    rxPacket = packet;
    rxCutthrough = false;
    if (cutthroughModule != nullptr)
        scheduleCutthroughStart(rxPacket);
    scheduleRxEnd(rxPacket);
}

void CompletePacketStartStart::endRx()
{
    if (!rxCutthrough)
        sendToUpperLayer(rxPacket);
    rxPacket = nullptr;
    rxCutthrough = false;
}

void CompletePacketStartStart::tryCutthrough()
{
    rxCutthrough = cutthroughModule->txPacket == nullptr;
    if (rxCutthrough) {
        EV_INFO << "Starting cutthrough: packetName = " << rxPacket->getName() << std::endl;
        cutthroughModule->startTx(rxPacket);
    }
}

simtime_t CompletePacketStartStart::calculateDuration(cPacket *packet)
{
    return packet->getBitLength() / bitrate;
}

void CompletePacketStartStart::scheduleTxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), txEndTimer);
}

void CompletePacketStartStart::scheduleRxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), rxEndTimer);
}

void CompletePacketStartStart::scheduleCutthroughStart(cPacket *packet)
{
    scheduleAt(simTime() + cutthroughBitLength / bitrate, cutthroughTimer);
}

} // namespace phy

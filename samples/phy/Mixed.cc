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

#include "Mixed.h"

namespace phy {

Define_Module(Mixed);

void Mixed::initialize()
{
    bitrate = par("bitrate");
    txMiddleTimer = new cMessage("TxMiddleTimer");
    txEndTimer = new cMessage("TxEndTimer");
    rxEndTimer = new cMessage("RxEndTimer");
}

Mixed::~Mixed()
{
    cancelAndDelete(txMiddleTimer);
    cancelAndDelete(txEndTimer);
    cancelAndDelete(rxEndTimer);
    delete rxPacket;
}

void Mixed::handleMessage(cMessage *message)
{
    if (message->arrivedOn("upperLayerIn"))
        receiveFromUpperLayer(check_and_cast<cPacket *>(message));
    else if (message->arrivedOn("mediumIn"))
        receiveFromMedium(message);
    else if (message == txMiddleTimer)
        middleTx();
    else if (message == txEndTimer)
        endTx();
    else if (message == rxEndTimer)
        endRx();
    else
        throw cRuntimeError("Unknown message");
}

void Mixed::receiveFromUpperLayer(cPacket *packet)
{
    startTx(packet);
}

void Mixed::sendToUpperLayer(cPacket *packet)
{
    send(packet, gate("upperLayerOut"));
    gate("mediumIn")->setDeliverOnReceptionStart(uniform(0, 1) < 0.5);
}

void Mixed::receiveCompletePacketAtStart(cPacket *packet)
{
    if (rxEndTimer->isScheduled() && rxEndTimer->getArrivalTime() == simTime()) {
        cancelEvent(rxEndTimer);
        endRx();
    }
    rxPacket = packet;
    scheduleRxEnd(rxPacket);
}

void Mixed::receiveCompletePacketAtEnd(cPacket *packet)
{
    sendToUpperLayer(packet);
}

void Mixed::receivePacketStart(cPacket *packet)
{
    take(packet);
    rxPacket = packet;
}

void Mixed::receivePacketEnd(cPacket *packet)
{
    sendToUpperLayer(packet);
    rxPacket = nullptr;
}

void Mixed::receivePacketProgress(cPacket *packet, int bitPosition, simtime_t timePosition, int extraProcessableBitLength, simtime_t extraProcessableDuration)
{
    if (timePosition == packet->getDuration() / 2)
        EV_INFO << "Processing middle: packetName " << packet->getName() << std::endl;
    else
        throw cRuntimeError("Uknown progress");
}

void Mixed::startTx(cPacket *packet)
{
    packet->setDuration(calculateDuration(packet));
    if (txMode == PACKET_PROGRESS_START_END || txMode == PACKET_PROGRESS_START_MIDDLE_END) {
        if (txPacket != nullptr)
            abortTx();
        txPacket = packet;
        sendPacketStart(packet, gate("mediumOut"), packet->getDuration());
        scheduleTxEnd(packet);
        if (txMode == PACKET_PROGRESS_START_MIDDLE_END)
            scheduleTxMiddle(packet);
    }
    else {
        if (txPacket != nullptr)
            abortTx();
        scheduleTxEnd(packet);
        if (txMode == COMPLETE_PACKET_START)
            sendCompletePacketAtStart(packet, gate("mediumOut"), packet->getDuration());
        txPacket = packet;
    }
}

void Mixed::middleTx()
{
    sendPacketProgress(txPacket, gate("mediumOut"), txPacket->getDuration(), txPacket->getBitLength() / 2, txPacket->getDuration() / 2);
}

void Mixed::endTx()
{
    switch (txMode) {
        case COMPLETE_PACKET_START:
            txMode = COMPLETE_PACKET_END;
            break;
        case COMPLETE_PACKET_END:
            sendCompletePacketAtEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
            txMode = PACKET_PROGRESS_START_END;
            break;
        case PACKET_PROGRESS_START_END:
            sendPacketEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
            txMode = PACKET_PROGRESS_START_MIDDLE_END;
            break;
        case PACKET_PROGRESS_START_MIDDLE_END:
            sendPacketEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
            txMode = COMPLETE_PACKET_START;
            break;
    }
    txPacket = nullptr;
}

void Mixed::abortTx()
{
    EV_INFO << "Aborting packet: packetName = " << txPacket->getName() << std::endl;
    int bitLength = bitrate * (simTime() - txEndTimer->getSendingTime()).dbl();
    txPacket->setBitLength(bitLength);
    txPacket->setDuration(calculateDuration(txPacket));
    if (txMode == COMPLETE_PACKET_END) {
        cancelEvent(txEndTimer);
        sendCompletePacketAtEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
    }
    else if (txMode == PACKET_PROGRESS_START_END || txMode == PACKET_PROGRESS_START_MIDDLE_END) {
        if (txMode == PACKET_PROGRESS_START_MIDDLE_END)
            cancelEvent(txMiddleTimer);
        cancelEvent(txEndTimer);
        sendPacketEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
    }
    else
        throw cRuntimeError("Another packet is already being sent");
    txPacket = nullptr;
}

void Mixed::endRx()
{
    sendToUpperLayer(rxPacket);
    rxPacket = nullptr;
}

simtime_t Mixed::calculateDuration(cPacket *packet)
{
    return packet->getBitLength() / bitrate;
}

void Mixed::scheduleTxMiddle(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration() / 2, txMiddleTimer);
}

void Mixed::scheduleTxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), txEndTimer);
}

void Mixed::scheduleRxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), rxEndTimer);
}

} // namespace phy

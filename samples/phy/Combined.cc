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

#include "Combined.h"

namespace phy {

Define_Module(Combined);

void Combined::initialize()
{
    bitrate = par("bitrate");
    cutthroughBitLength = par("cutthroughBitLength");
    cutthroughModule = dynamic_cast<Combined *>(getModuleByPath(par("cutthroughModule")));
    preemptionEnabled = par("preemptionEnabled");
    txEndTimer = new cMessage("TxEndTimer");
    rxEndTimer = new cMessage("RxEndTimer");
    cutthroughStartTimer = new cMessage("CutthroughStartTimer");
    cutthroughEndTimer = new cMessage("CutthroughEndTimer");
    gate("mediumIn")->setDeliverOnReceptionStart(cutthroughModule != nullptr);
}

Combined::~Combined()
{
    cancelAndDelete(txEndTimer);
    cancelAndDelete(rxEndTimer);
    cancelAndDelete(cutthroughStartTimer);
    cancelAndDelete(cutthroughEndTimer);
    delete rxPacket;
}

void Combined::handleMessage(cMessage *message)
{
    if (message->arrivedOn("upperLayerIn"))
        receiveFromUpperLayer(check_and_cast<cPacket *>(message));
    else if (message->arrivedOn("mediumIn"))
        receiveFromMedium(message);
    else if (message == txEndTimer)
        endTx();
    else if (message == rxEndTimer)
        endRx();
    else if (message == cutthroughStartTimer)
        tryCutthrough();
    else if (message == cutthroughEndTimer)
        endCutthrough();
    else
        throw cRuntimeError("Unknown message");
}

void Combined::receiveFromUpperLayer(cPacket *packet)
{
    startTx(packet);
}

void Combined::sendToUpperLayer(cPacket *packet)
{
    send(packet, gate("upperLayerOut"));
}

void Combined::receiveCompletePacketAtStart(cPacket *packet)
{
    rxPacket = packet;
    if (cutthroughModule != nullptr)
        scheduleCutthroughStart(rxPacket);
    scheduleRxEnd(rxPacket);
}

void Combined::receiveCompletePacketAtEnd(cPacket *packet)
{
    if (cutthroughModule != nullptr)
        throw cRuntimeError("Invalid state");
    sendToUpperLayer(packet);
}

void Combined::receivePacketStart(cPacket *packet)
{
    take(packet);
    rxPacket = packet;
    if (cutthroughModule != nullptr)
        scheduleCutthroughStart(rxPacket);
}

void Combined::receivePacketEnd(cPacket *packet)
{
    if (cutthroughModule == nullptr)
        sendToUpperLayer(packet);
    else {
        cutthroughModule->cancelTxEnd();
        scheduleCutthroughEnd(packet);
    }
    rxPacket = nullptr;
}

void Combined::startTx(cPacket *packet)
{
    packet->setDuration(calculateDuration(packet));
    if (preemptionEnabled) {
        if (txPacket != nullptr)
            abortTx();
        txPacket = packet;
        sendPacketStart(packet, gate("mediumOut"), packet->getDuration());
        scheduleTxEnd(packet);
    }
    else {
        if (txPacket != nullptr)
            throw cRuntimeError("Another packet is already being sent");
        scheduleTxEnd(packet);
        sendCompletePacketAtStart(packet, gate("mediumOut"), packet->getDuration());
        txPacket = packet;
    }
}

void Combined::endTx()
{
    if (preemptionEnabled)
        sendPacketEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
    txPacket = nullptr;
}

void Combined::abortTx()
{
    EV_INFO << "Aborting packet: packetName = " << txPacket->getName() << std::endl;
    cancelEvent(txEndTimer);
    int bitLength = bitrate * (simTime() - txEndTimer->getSendingTime()).dbl();
    txPacket->setBitLength(bitLength);
    txPacket->setDuration(calculateDuration(txPacket));
    sendPacketEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
    txPacket = nullptr;
}

void Combined::endRx()
{
    if (cutthroughPacket == nullptr)
        sendToUpperLayer(rxPacket);
    else
        scheduleCutthroughEnd(rxPacket);
    rxPacket = nullptr;
}

void Combined::tryCutthrough()
{
    if (cutthroughModule->txPacket == nullptr) {
        cutthroughPacket = rxPacket;
        cutthroughModule->startTx(cutthroughPacket);
    }
}

void Combined::endCutthrough()
{
    cutthroughModule->endTx();
}

simtime_t Combined::calculateDuration(cPacket *packet)
{
    return packet->getBitLength() / bitrate;
}

void Combined::scheduleTxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), txEndTimer);
}

void Combined::scheduleRxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), rxEndTimer);
}

void Combined::scheduleCutthroughStart(cPacket *packet)
{
    scheduleAt(simTime() + cutthroughBitLength / bitrate, cutthroughStartTimer);
}

void Combined::scheduleCutthroughEnd(cPacket *packet)
{
    scheduleAt(simTime() + cutthroughBitLength / bitrate, cutthroughEndTimer);
}

void Combined::cancelTxEnd()
{
    cancelEvent(txEndTimer);
}

} // namespace phy

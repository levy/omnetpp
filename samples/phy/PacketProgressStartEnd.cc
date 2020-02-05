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

#include "PacketProgressStartEnd.h"

namespace phy {

Define_Module(PacketProgressStartEnd);

void PacketProgressStartEnd::initialize()
{
    bitrate = par("bitrate");
    cutthroughBitLength = par("cutthroughBitLength");
    cutthroughModule = dynamic_cast<PacketProgressStartEnd *>(getModuleByPath(par("cutthroughModule")));
    preemptionEnabled = par("preemptionEnabled");
    txEndTimer = new cMessage("TxEndTimer");
    cutthroughStartTimer = new cMessage("CutthroughStartTimer");
    cutthroughEndTimer = new cMessage("CutthroughEndTimer");
}

PacketProgressStartEnd::~PacketProgressStartEnd()
{
    cancelAndDelete(txEndTimer);
    cancelAndDelete(cutthroughStartTimer);
    cancelAndDelete(cutthroughEndTimer);
    delete rxPacket;
}

void PacketProgressStartEnd::handleMessage(cMessage *message)
{
    if (message->arrivedOn("upperLayerIn"))
        receiveFromUpperLayer(check_and_cast<cPacket *>(message));
    else if (message->arrivedOn("mediumIn"))
        receiveFromMedium(message);
    else if (message == txEndTimer)
        endTx();
    else if (message == cutthroughStartTimer)
        tryCutthrough();
    else if (message == cutthroughEndTimer)
        endCutthrough();
    else
        throw cRuntimeError("Unknown message");
}

void PacketProgressStartEnd::receiveFromUpperLayer(cPacket *packet)
{
    startTx(packet);
}

void PacketProgressStartEnd::sendToUpperLayer(cPacket *packet)
{
    send(packet, gate("upperLayerOut"));
}

void PacketProgressStartEnd::receivePacketStart(cPacket *packet)
{
    startRx(packet);
}

void PacketProgressStartEnd::receivePacketEnd(cPacket *packet)
{
    endRx(packet);
}

void PacketProgressStartEnd::startTx(cPacket *packet)
{
    if (txPacket != nullptr) {
        if (preemptionEnabled)
            abortTx();
        else
            throw cRuntimeError("Another packet is already being sent");
    }
    packet->setDuration(calculateDuration(txPacket));
    scheduleTxEnd(packet);
    sendPacketStart(packet, gate("mediumOut"), packet->getDuration());
    txPacket = packet;
}

void PacketProgressStartEnd::endTx()
{
    sendPacketEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
    txPacket = nullptr;
}

void PacketProgressStartEnd::abortTx()
{
    EV_INFO << "Aborting: packetName = " << txPacket->getName() << std::endl;
    cancelEvent(txEndTimer);
    int bitLength = bitrate * (simTime() - txEndTimer->getSendingTime()).dbl();
    txPacket->setBitLength(bitLength);
    txPacket->setDuration(calculateDuration(txPacket));
    sendPacketEnd(txPacket, gate("mediumOut"), txPacket->getDuration());
    txPacket = nullptr;
}

void PacketProgressStartEnd::startRx(cPacket *packet)
{
    take(packet);
    rxPacket = packet;
    if (cutthroughModule != nullptr)
        scheduleCutthroughStart(rxPacket);
}

void PacketProgressStartEnd::endRx(cPacket *packet)
{
    if (cutthroughPacket == nullptr)
        sendToUpperLayer(packet);
    else {
        cutthroughModule->cancelTxEnd();
        scheduleCutthroughEnd(packet);
    }
    rxPacket = nullptr;
}

void PacketProgressStartEnd::tryCutthrough()
{
    if (cutthroughModule->txPacket == nullptr) {
        EV_INFO << "Starting cutthrough: packetName = " << rxPacket->getName() << std::endl;
        cutthroughPacket = rxPacket;
        cutthroughModule->startTx(cutthroughPacket);
    }
}

void PacketProgressStartEnd::endCutthrough()
{
    cutthroughModule->endTx();
}

simtime_t PacketProgressStartEnd::calculateDuration(cPacket *packet)
{
    return packet->getBitLength() / bitrate;
}

void PacketProgressStartEnd::scheduleTxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), txEndTimer);
}

void PacketProgressStartEnd::scheduleCutthroughStart(cPacket *packet)
{
    scheduleAt(simTime() + cutthroughBitLength / bitrate, cutthroughStartTimer);
}

void PacketProgressStartEnd::scheduleCutthroughEnd(cPacket *packet)
{
    scheduleAt(simTime() + cutthroughBitLength / bitrate, cutthroughEndTimer);
}

void PacketProgressStartEnd::cancelTxEnd()
{
    cancelEvent(txEndTimer);
}

} // namespace phy

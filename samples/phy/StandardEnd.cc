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

#include "StandardEnd.h"

namespace phy {

Define_Module(StandardEnd);

void StandardEnd::initialize()
{
    bitrate = par("bitrate");
    txEndTimer = new cMessage("TxEndTimer");
    gate("mediumIn")->setDeliverOnReceptionStart(false);
}

StandardEnd::~StandardEnd()
{
    cancelAndDelete(txEndTimer);
}

void StandardEnd::handleMessage(cMessage *message)
{
    if (message->arrivedOn("upperLayerIn"))
        receiveFromUpperLayer(check_and_cast<cPacket *>(message));
    else if (message->arrivedOn("mediumIn"))
        receiveFromMedium(check_and_cast<cPacket *>(message));
    else if (message == txEndTimer)
        endTx();
    else
        throw cRuntimeError("Unknown message");
}

void StandardEnd::sendToUpperLayer(cPacket *packet)
{
    send(packet, gate("upperLayerOut"));
}

void StandardEnd::receiveFromUpperLayer(cPacket *packet)
{
    startTx(packet);
}

void StandardEnd::receiveFromMedium(cPacket *packet)
{
    endRx(packet);
}

void StandardEnd::sendToMedium(cPacket *packet)
{
    send(packet, gate("mediumOut"));
}

void StandardEnd::startTx(cPacket *packet)
{
    if (txPacket != nullptr)
        throw cRuntimeError("Another packet is already being sent");
    packet->setDuration(calculateDuration(packet));
    scheduleTxEnd(packet);
    sendToMedium(packet);
    txPacket = packet;
}

void StandardEnd::endTx()
{
    txPacket = nullptr;
}

void StandardEnd::endRx(cPacket *packet)
{
    sendToUpperLayer(packet);
}

simtime_t StandardEnd::calculateDuration(cPacket *packet)
{
    return packet->getBitLength() / bitrate;
}

void StandardEnd::scheduleTxEnd(cPacket *packet)
{
    scheduleAt(simTime() + packet->getDuration(), txEndTimer);
}

} // namespace phy

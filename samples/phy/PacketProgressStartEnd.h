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

#ifndef __PACKETPROGRESSSTARTEND_H
#define __PACKETPROGRESSSTARTEND_H

#include <omnetpp.h>

using namespace omnetpp;

namespace phy {

class PacketProgressStartEnd : public cSimpleModule
{
  protected:
    double bitrate = 0;
    int cutthroughBitLength = 0;
    PacketProgressStartEnd *cutthroughModule = nullptr;
    bool preemptionEnabled = false;

    cMessage *txEndTimer = nullptr;
    cMessage *cutthroughStartTimer = nullptr;
    cMessage *cutthroughEndTimer = nullptr;

    cPacket *txPacket = nullptr;
    cPacket *rxPacket = nullptr;
    cPacket *cutthroughPacket = nullptr;

  public:
    virtual ~PacketProgressStartEnd();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *message) override;

    virtual void receiveFromUpperLayer(cPacket *packet);
    virtual void sendToUpperLayer(cPacket *packet);

    virtual void receivePacketStart(cPacket *packet, cGate *gate, double datarate) override;
    virtual void receivePacketEnd(cPacket *packet, cGate *gate, double datarate) override;

    virtual void startTx(cPacket *packet);
    virtual void endTx();
    virtual void abortTx();

    virtual void startRx(cPacket *packet);
    virtual void endRx(cPacket *packet);

    virtual void tryCutthrough();
    virtual void endCutthrough();

    virtual simtime_t calculateDuration(cPacket *packet);

    virtual void scheduleTxEnd(cPacket *packet);
    virtual void scheduleCutthroughStart(cPacket *packet);
    virtual void scheduleCutthroughEnd(cPacket *packet);

    virtual void cancelTxEnd();
};

} // namespace phy

#endif // ifndef __PACKETPROGRESSSTARTEND_H


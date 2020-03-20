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

#ifndef __MIXED_H
#define __MIXED_H

#include <omnetpp.h>

using namespace omnetpp;

namespace phy {

class Mixed : public cSimpleModule
{
  protected:
    enum Mode {
        COMPLETE_PACKET_START,
        COMPLETE_PACKET_END,
        PACKET_PROGRESS_START_END,
        PACKET_PROGRESS_START_MIDDLE_END
    };

  protected:
    double bitrate = 0;

    cMessage *txMiddleTimer = nullptr;
    cMessage *txEndTimer = nullptr;
    cMessage *rxEndTimer = nullptr;

    Mode txMode = COMPLETE_PACKET_START;
    cPacket *txPacket = nullptr;
    cPacket *rxPacket = nullptr;

  public:
    virtual ~Mixed();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *message) override;

    virtual void receiveFromUpperLayer(cPacket *packet);
    virtual void sendToUpperLayer(cPacket *packet);

    virtual void receiveCompletePacketAtStart(cPacket *packet) override;
    virtual void receiveCompletePacketAtEnd(cPacket *packet) override;
    virtual void receivePacketStart(cPacket *packet) override;
    virtual void receivePacketEnd(cPacket *packet) override;
    virtual void receivePacketProgress(cPacket *packet, int bitPosition, simtime_t timePosition, int extraProcessableBitLength, simtime_t extraProcessableDuration) override;

    virtual void startTx(cPacket *packet);
    virtual void middleTx();
    virtual void endTx();
    virtual void abortTx();

    // NOTE: startRx is absent, because there's no single kind of event for it
    virtual void endRx();

    virtual simtime_t calculateDuration(cPacket *packet);

    virtual void scheduleTxMiddle(cPacket *packet);
    virtual void scheduleTxEnd(cPacket *packet);
    virtual void scheduleRxEnd(cPacket *packet);
};

} // namespace phy

#endif // ifndef __MIXED_H


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

#ifndef __COMPLETEPACKETSTARTEND_H
#define __COMPLETEPACKETSTARTEND_H

#include <omnetpp.h>

using namespace omnetpp;

namespace phy {

class CompletePacketStartEnd : public cPhyModule
{
  protected:
    double bitrate = 0;

    cMessage *txEndTimer = nullptr;

    cPacket *txPacket = nullptr;

  public:
    virtual ~CompletePacketStartEnd();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *message) override;

    virtual void receiveFromUpperLayer(cPacket *packet);
    virtual void sendToUpperLayer(cPacket *packet);

    virtual void receiveCompletePacketAtEnd(cPacket *packet) override;
    virtual void sendToMedium(cPacket *packet);

    virtual void startTx(cPacket *packet);
    virtual void endTx();

    virtual simtime_t calculateDuration(cPacket *packet);

    virtual void scheduleTxEnd(cPacket *packet);
};

} // namespace phy

#endif // ifndef __COMPLETEPACKETSTARTEND_H


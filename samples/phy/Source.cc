//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#include "Source.h"

namespace phy {

Define_Module(Source);

Source::~Source()
{
    cancelAndDelete(timer);
}

void Source::initialize()
{
    timer = new cMessage("Timer");
    scheduleTimer();
    WATCH(numPacket);
}

void Source::handleMessage(cMessage *message)
{
    if (message == timer) {
        std::string name = "data-" + std::to_string(numPacket);
        auto packet = new cPacket(nullptr, 0);
        packet->setName(name.c_str());
        packet->setBitLength(par("length"));
        send(packet, gate("out"));
        scheduleTimer();
        numPacket++;
        std::string text = "sent " + std::to_string(numPacket);
        getDisplayString().setTagArg("t", 0, text.c_str());
    }
    else
        throw cRuntimeError("Unknown message");
}

void Source::scheduleTimer()
{
    scheduleAt(simTime() + par("interval"), timer);
}

} // namespace phy


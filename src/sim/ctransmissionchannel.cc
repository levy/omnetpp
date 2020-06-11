//========================================================================
//  CTRANSMISSIONCHANNEL.CC - part of
//
//                 OMNeT++/OMNEST
//              Discrete System Simulation in C++
//
//========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 1992-2017 Andras Varga
  Copyright (C) 2006-2017 OpenSim Ltd.

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `license' for details on this and other legal matters.
*--------------------------------------------------------------*/

#include "omnetpp/ctransmissionchannel.h"
#include "omnetpp/cpacket.h"
#include "omnetpp/cmodule.h"
#include "omnetpp/cenvir.h"
#include "omnetpp/distrib.h"
#include "omnetpp/csimulation.h"
#include "omnetpp/globals.h"
#include "omnetpp/cgate.h"
#include "omnetpp/cexception.h"
#include "omnetpp/ctimestampedvalue.h"

#ifdef WITH_PARSIM
#include "omnetpp/ccommbuffer.h"
#endif

namespace omnetpp {

using std::ostream;

Register_Class(cTransmissionChannel);

simsignal_t cTransmissionChannel::channelBusySignal;
simsignal_t cTransmissionChannel::messageSentSignal;
simsignal_t cTransmissionChannel::messageDiscardedSignal;

cTransmissionChannel::cTransmissionChannel(const char *name) : cChannel(name)
{
    txFinishTime = -1;
    delay = 0;
    ber = 0;
    per = 0;
}

cTransmissionChannel::~cTransmissionChannel()
{
}

void cTransmissionChannel::finish()
{
    if (txFinishTime != -1 && mayHaveListeners(channelBusySignal)) {
        cTimestampedValue tmp(std::min(txFinishTime, simTime()), (intval_t)0);
        emit(channelBusySignal, &tmp);
    }
}

cTransmissionChannel *cTransmissionChannel::create(const char *name)
{
    return dynamic_cast<cTransmissionChannel *>(cChannelType::getDatarateChannelType()->create(name));
}

std::string cTransmissionChannel::str() const
{
    return cChannel::str();
}

void cTransmissionChannel::initialize()
{
    channelBusySignal = registerSignal("channelBusy");
    messageSentSignal = registerSignal("messageSent");
    messageDiscardedSignal = registerSignal("messageDiscarded");

    emit(channelBusySignal, 0);
}

void cTransmissionChannel::rereadPars()
{
    delay = par("delay");
    ber = par("ber");
    per = par("per");

    if (delay < SIMTIME_ZERO)
        throw cRuntimeError(this, "Negative delay %s", SIMTIME_STR(delay));
    if (ber < 0 || ber > 1)
        throw cRuntimeError(this, "Wrong bit error rate %g", ber);
    if (per < 0 || per > 1)
        throw cRuntimeError(this, "Wrong packet error rate %g", per);

    setFlag(FL_ISDISABLED, par("disabled"));
    setFlag(FL_DELAY_NONZERO, delay != SIMTIME_ZERO);
    setFlag(FL_BER_NONZERO, ber != 0);
    setFlag(FL_PER_NONZERO, per != 0);
}

void cTransmissionChannel::handleParameterChange(const char *)
{
    rereadPars();
}

void cTransmissionChannel::setDelay(double d)
{
    par("delay").setDoubleValue(d);
}

void cTransmissionChannel::setBitErrorRate(double d)
{
    par("ber").setDoubleValue(d);
}

void cTransmissionChannel::setPacketErrorRate(double d)
{
    par("per").setDoubleValue(d);
}

void cTransmissionChannel::setDisabled(bool d)
{
    par("disabled").setBoolValue(d);
}

simtime_t cTransmissionChannel::calculateDuration(cMessage *msg) const
{
    if (msg->isPacket())
        return ((cPacket *)msg)->getDuration();
    else
        return SIMTIME_ZERO;
}

void cTransmissionChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    // channel must be idle
    if (txFinishTime > t)
        throw cRuntimeError("Cannot send message (%s)%s on gate %s: Channel is currently "
                            "busy with an ongoing transmission -- please rewrite the sender "
                            "simple module to only send when the previous transmission has "
                            "already finished, using cGate::getTransmissionFinishTime(), scheduleAt(), "
                            "and possibly a cQueue for storing messages waiting to be transmitted",
                msg->getClassName(), msg->getFullName(), getFullPath().c_str());

    // message must not have its duration set already
    bool isPacket = msg->isPacket();
    if (isPacket && ((cPacket *)msg)->getDuration() == SIMTIME_ZERO)
        throw cRuntimeError(this, "Packet (%s)%s has no duration set",
                                  msg->getClassName(), msg->getName());

    // if channel is disabled, signal that message should be deleted
    if (flags & FL_ISDISABLED) {
        result.discard = true;
        cTimestampedValue tmp(t, msg);
        emit(messageDiscardedSignal, &tmp);
        return;
    }

    if (txFinishTime != -1 && mayHaveListeners(channelBusySignal)) {
        cTimestampedValue tmp(txFinishTime, (intval_t)0);
        emit(channelBusySignal, &tmp);
    }

    // duration modeling
    if (msg->isPacket()) {
        cPacket *pkt = (cPacket *)msg;
        simtime_t duration = pkt->getDuration();
        result.duration = duration;
        txFinishTime = t + (pkt->isTransmissionStart() ? duration : 0);
    }
    else {
        if (auto progress = dynamic_cast<cProgress *>(msg))
            result.duration = progress->getPacket()->getDuration() - progress->getTimePosition();
        txFinishTime = t;
    }

    // propagation delay modeling
    result.delay = delay;

    // bit error modeling
    if ((flags & (FL_BER_NONZERO | FL_PER_NONZERO)) && msg->isPacket()) {
        cPacket *pkt = (cPacket *)msg;
        if (flags & FL_BER_NONZERO)
            if (dblrand() < 1.0 - pow(1.0 - ber, (double)pkt->getBitLength()))
                pkt->setBitError(true);

        if (flags & FL_PER_NONZERO)
            if (dblrand() < per)
                pkt->setBitError(true);
    }

    // emit signals
    if (mayHaveListeners(messageSentSignal)) {
        MessageSentSignalValue tmp(t, msg, &result);
        emit(messageSentSignal, &tmp);
    }
    if (mayHaveListeners(channelBusySignal)) {
        cTimestampedValue tmp(t, (intval_t)1);
        emit(channelBusySignal, &tmp);
    }
}

void cTransmissionChannel::forceTransmissionFinishTime(simtime_t t)
{
    //TODO record this into the eventlog so that it can be visualized in the sequence chart
    txFinishTime = t;
}

}  // namespace omnetpp


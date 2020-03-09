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
    txStartTime = -1;
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

    bool disabled = par("disabled");
    if (disabled && !(flags & FL_ISDISABLED) && (txFinishTime != -1)) {
        cTimestampedValue tmp(txFinishTime, (intval_t)0);
        emit(channelBusySignal, &tmp);
        txFinishTime = simTime();
        inProgress = false;
    }
    setFlag(FL_ISDISABLED, disabled);

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
    cProgress *progress = nullptr;
    cPacket *pkt = nullptr;
    bool isStart = true;
    bool isEnd = true;
    simtime_t tStart = t;

    if (msg->isPacket()) {
        pkt = static_cast<cPacket *>(msg);
    }
    else {
        progress = dynamic_cast<cProgress *>(msg);
    }

    if (progress) {
        isStart = progress->getKind() == cProgress::PACKET_START;
        isEnd = progress->getKind() == cProgress::PACKET_END;
        if (isStart) {
            if (inProgress || txFinishTime > t)
                throw cRuntimeError("Cannot send message (%s)%s on gate %s: Channel is currently "
                                    "busy with an ongoing transmission -- please rewrite the sender "
                                    "simple module to only send when the previous transmission has "
                                    "already finished, using cGate::getTransmissionFinishTime(), scheduleAt(), "
                                    "and possibly a cQueue for storing messages waiting to be transmitted",
                        msg->getClassName(), msg->getFullName(), getFullPath().c_str());
        }
        else {
            if (!inProgress)
                throw cRuntimeError("Cannot send continued cProgress (%s)%s on gate %s: not in progress",
                        msg->getClassName(), msg->getFullName(), getFullPath().c_str());
            if (txFinishTime < t)
                throw cRuntimeError("Cannot send continued cProgress (%s)%s on gate %s: the previous cProgress was finished",
                        msg->getClassName(), msg->getFullName(), getFullPath().c_str());
        }
    }
    else {
        // channel must be idle
        if (inProgress || txFinishTime > t)
            throw cRuntimeError("Cannot send message (%s)%s on gate %s: Channel is currently "
                                "busy with an ongoing transmission -- please rewrite the sender "
                                "simple module to only send when the previous transmission has "
                                "already finished, using cGate::getTransmissionFinishTime(), scheduleAt(), "
                                "and possibly a cQueue for storing messages waiting to be transmitted",
                    msg->getClassName(), msg->getFullName(), getFullPath().c_str());
    }

    // message must not have its duration set already
    if (pkt != nullptr && pkt->getDuration() == SIMTIME_ZERO)
        throw cRuntimeError(this, "Packet (%s)%s has no duration set",
                                  pkt->getClassName(), pkt->getName());

    // if channel is disabled, signal that message should be deleted
    if (flags & FL_ISDISABLED) {
        result.discard = true;
        cTimestampedValue tmp(t, msg);
        emit(messageDiscardedSignal, &tmp);
        return;
    }

    if (isStart && txFinishTime != -1 && mayHaveListeners(channelBusySignal)) { //FIXME emit 0 only when doesn't have any current progress
        cTimestampedValue tmp(txFinishTime, (intval_t)0);
        emit(channelBusySignal, &tmp);
    }

    // duration modeling
    if (pkt != nullptr) {
        simtime_t duration = pkt->getDuration();
        result.duration = duration;
        simtime_t tEnd;
        if (pkt->isTransmissionStart()) {
            tStart = t;
        }
        else {
            tStart = t - duration;
            if (txFinishTime > tStart)
                throw cRuntimeError("Cannot send message (%s)%s on gate %s: Channel was currently "
                                    "busy with an ongoing transmission -- please rewrite the sender "
                                    "simple module to only send when the previous transmission has "
                                    "already finished, using cGate::getTransmissionFinishTime(), scheduleAt(), "
                                    "and possibly a cQueue for storing messages waiting to be transmitted",
                        msg->getClassName(), msg->getFullName(), getFullPath().c_str());
            txFinishTime = t;
        }
        tEnd = tStart + duration;
        txStartTime = tStart;
        txFinishTime = tEnd;
    }
    else if (progress) {
        simtime_t tPos = progress->getTimePosition();
        simtime_t duration = progress->getPacket()->getDuration();
        tStart = t - tPos;
        simtime_t tEnd = tStart + duration;
        if (!isStart && tStart != txStartTime)
            throw cRuntimeError("The tx start time changed between cProgress msg");
        if (duration < tPos)
            throw cRuntimeError("The timePosition in cProgress msg larger than contained entire cPacket duration");
        if (tEnd < t)
            throw cRuntimeError("The calculated tx finish time  smaller current time");
        result.duration = tEnd - t;
        txStartTime = tStart;
        txFinishTime = tEnd;
        inProgress = (progress->getKind() != cProgress::PACKET_END);
    }
    else {
        txStartTime = t;
        txFinishTime = t;
    }

    // propagation delay modeling
    result.delay = delay;

    // bit error modeling
    if (isEnd && (flags & (FL_BER_NONZERO | FL_PER_NONZERO)))
    {
        cPacket *epkt = (pkt != nullptr) ? pkt : (progress != nullptr) ? progress->getPacket() : nullptr;
        if (epkt) {
            if (flags & FL_BER_NONZERO)
                if (dblrand() < 1.0 - pow(1.0 - ber, (double)epkt->getBitLength()))
                    epkt->setBitError(true);
            if (flags & FL_PER_NONZERO)
                if (dblrand() < per)
                    epkt->setBitError(true);
        }
    }

    // emit signals
    if (mayHaveListeners(messageSentSignal)) {
        MessageSentSignalValue tmp(t, msg, &result);
        emit(messageSentSignal, &tmp);
    }
    if (isEnd && mayHaveListeners(channelBusySignal)) {
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


#ifndef ARRUS_CORE_DEVICES_PROBE_PROBEIMPLBASE_H
#define ARRUS_CORE_DEVICES_PROBE_PROBEIMPLBASE_H

#include "arrus/core/api/devices/probe/Probe.h"
#include "arrus/core/devices/us4r/Us4RBuffer.h"
#include "arrus/core/devices/UltrasoundDevice.h"

namespace arrus::devices {

class ProbeImplBase : public Probe, public UltrasoundDevice {
public:
    using Handle = std::unique_ptr<ProbeImplBase>;
    using RawHandle = ProbeImplBase *;
    using Probe::Probe;

    virtual
    std::tuple<Us4RBuffer::Handle, FrameChannelMapping::Handle>
    setTxRxSequence(const std::vector<TxRxParameters> &seq, const ops::us4r::TGCCurve &tgcSamples, uint16 rxBufferSize,
                    uint16 rxBatchSize, std::optional<float> sri, bool triggerSync) = 0;

    virtual void registerOutputBuffer(Us4ROutputBuffer *, const Us4RBuffer::Handle &, bool isTriggerSync) = 0;
    virtual void unregisterOutputBuffer(Us4ROutputBuffer *, const Us4RBuffer::Handle &) = 0;
};

}

#endif //ARRUS_CORE_DEVICES_PROBE_PROBEIMPLBASE_H

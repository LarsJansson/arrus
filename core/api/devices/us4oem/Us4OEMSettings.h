#ifndef ARRUS_CORE_API_DEVICES_US4OEMSETTINGS_H
#define ARRUS_CORE_API_DEVICES_US4OEMSETTINGS_H

#include <utility>
#include <vector>
#include <bitset>
#include <optional>

#include "arrus/core/api/common/types.h"

namespace arrus {

/**
 * Us4OEM settings.
 *
 * Contains all raw parameters used to configure module.
 */
class Us4OEMSettings {
public:
    /**
     * Us4OEM Settings constructor.
     *
     * Channel mapping: value[i] = j, where the i is the channel seen by the user, j is the physical channel
     * logiczny (index) -> fizyczny (wartosc)
     * Nie wszystkie kanaly musza byc przypisane: np. dla ultrasonix tylko kanaly 0-32 oraz 64-96 sa mapowane, dla pozostalych sa niekoreslne
     *
     *
     * @param activeChannelGroups determines which groups of channels should be
     *        'active'. When the 'channel is active', Us4OEM can transmit/receive
     *        a signal through this channel.
     *        If the size of the group is equal `n`, and the number of module's
     *        channels is `m`, `activeChannelGroups[0]` turns on/off channels
     *        `0,1,..,(n-1)`, `activeChannelGroups[1]` turns on/off channels
     *        `n,(n+1),..,(2n-1)`, and so on. The value `m' is always divisible
     *        by `n`. The array `activeChannelGroups` should have exactly
     *        `m/n` elements.
     * @param channelMapping channel permutation to apply on a given Us4OEM.
     * @param dtgcAttenuation
     * @param pgaGain
     * @param lnaGain
     * @param tgcSamples
     * @param lpfCutoff
     * @param activeTermination
     * @param tgcSamples tgc curve to apply, empty list means to turn off TGC
     */
    Us4OEMSettings(
            std::vector<ChannelIdx> channelMapping,
            BitMask activeChannelGroups,
            const std::optional<uint16> dtgcAttenuation,
            const uint16 pgaGain,
            const uint16 lnaGain,
            const uint32 lpfCutoff,
            const std::optional<uint16> activeTermination,
            TGCCurve tgcSamples
    ) : channelMapping(std::move(channelMapping)),
        activeChannelGroups(std::move(activeChannelGroups)),
        dtgcAttenuation(dtgcAttenuation), pgaGain(pgaGain), lnaGain(lnaGain),
        tgcSamples(std::move(tgcSamples)),
        lpfCutoff(lpfCutoff), activeTermination(activeTermination)
        {}

    [[nodiscard]] const std::vector<ChannelIdx> &getChannelMapping() const {
        return channelMapping;
    }

    [[nodiscard]] const BitMask &getActiveChannelGroups() const {
        return activeChannelGroups;
    }

    [[nodiscard]] std::optional<uint16> getDTGCAttenuation() const {
        return dtgcAttenuation;
    }

    [[nodiscard]] uint16 getPGAGain() const {
        return pgaGain;
    }

    [[nodiscard]] uint16 getLNAGain() const {
        return lnaGain;
    }

    [[nodiscard]] uint32 getLPFCutoff() const {
        return lpfCutoff;
    }

    [[nodiscard]] std::optional<uint16> getActiveTermination() const {
        return activeTermination;
    }

    [[nodiscard]] const TGCCurve &getTGCSamples() const {
        return tgcSamples;
    }

private:
    std::vector<ChannelIdx> channelMapping;
    BitMask activeChannelGroups;

    std::optional<uint8> dtgcAttenuation;
    uint8 pgaGain;
    uint8 lnaGain;

    TGCCurve tgcSamples;

    uint32 lpfCutoff;
    std::optional<uint16> activeTermination;
};

}

#endif //ARRUS_CORE_API_DEVICES_US4OEMSETTINGS_H

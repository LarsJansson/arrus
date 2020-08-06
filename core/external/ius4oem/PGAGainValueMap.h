#ifndef ARRUS_CORE_DEVICES_US4OEM_IMPL_MAPPERS_PGAGAINVALUEMAPPER_H
#define ARRUS_CORE_DEVICES_US4OEM_IMPL_MAPPERS_PGAGAINVALUEMAPPER_H

#include <unordered_map>
#include <set>

#include <ius4oem.h>

#include "arrus/core/api/common/types.h"

namespace arrus {

class PGAGainValueMap {

public:
    using PGAGainValueType = uint8;

    static PGAGainValueMap &getInstance() {
        static PGAGainValueMap instance;
        return instance;
    }

    us4r::afe58jd18::PGA_GAIN getEnumValue(const PGAGainValueType value) {
        return valueMap.at(value);
    }

    /**
     * Returns a sorted set of available values.
     */
    std::set<PGAGainValueType> getAvailableValues() const {
        std::set<PGAGainValueType> values;
        std::transform(std::begin(valueMap), std::end(valueMap),
                       std::inserter(values, std::end(values)),
                       [](auto &val) {
                           return val.first;
                       });
        return values;
    }

    PGAGainValueMap(PGAGainValueMap const &) = delete;

    void operator=(PGAGainValueMap const &) = delete;

    PGAGainValueMap(PGAGainValueMap const &&) = delete;

    void operator=(PGAGainValueMap const &&) = delete;

private:
    std::unordered_map<PGAGainValueType, us4r::afe58jd18::PGA_GAIN> valueMap;

    PGAGainValueMap() {
        valueMap.emplace(24, us4r::afe58jd18::PGA_GAIN::PGA_GAIN_24dB);
        valueMap.emplace(30, us4r::afe58jd18::PGA_GAIN::PGA_GAIN_30dB);
    }

};

}

#endif //ARRUS_CORE_DEVICES_US4OEM_IMPL_MAPPERS_PGAGAINVALUEMAPPER_H

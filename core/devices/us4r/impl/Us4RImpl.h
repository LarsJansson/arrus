#ifndef ARRUS_CORE_DEVICES_US4R_IMPL_US4RIMPL_H
#define ARRUS_CORE_DEVICES_US4R_IMPL_US4RIMPL_H

#include <unordered_map>
#include <utility>

#include "core/devices/us4r/Us4R.h"

namespace arrus {

class Us4RImpl : public Us4R {
public:
    using Us4OEMs = std::vector<Us4OEM::Handle>;

    Us4RImpl(const DeviceId &id, Us4OEMs us4oems)
             : Us4R(id), us4oems(std::move(us4oems)) {}

    Us4OEM::Handle &getUs4OEM(Ordinal ordinal) override {
        return us4oems.at(ordinal);
    }

private:
    Us4OEMs us4oems;
};

}

#endif //ARRUS_CORE_DEVICES_US4R_IMPL_US4RIMPL_H

#ifndef ARRUS_CORE_DEVICES_US4OEM_IMPL_IUS4OEMFACTORY_H
#define ARRUS_CORE_DEVICES_US4OEM_IMPL_IUS4OEMFACTORY_H

#include <memory>
#include <ius4oem.h>

namespace arrus {

using IUs4OEMHandle = std::unique_ptr<IUs4OEM>;

/**
 * A simple wrapper over GetUs4OEM method available in Us4.
 */

class IUs4OEMFactory {
public:
    virtual IUs4OEMHandle getIUs4OEM(unsigned index) = 0;
};


}
#endif //ARRUS_CORE_DEVICES_US4OEM_IMPL_IUS4OEMFACTORY_H

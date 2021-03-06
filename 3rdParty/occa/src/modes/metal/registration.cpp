#include <occa/defines.hpp>
#include <occa/modes/metal/registration.hpp>

namespace occa {
  namespace metal {
    modeInfo::modeInfo() {}

    bool modeInfo::init() {
#if OCCA_METAL_ENABLED
      // Only consider metal enabled if there is an available device
      return api::metal::getDeviceCount();
#else
      return false;
#endif
    }

    styling::section& modeInfo::getDescription() {
      static styling::section section("Metal");
      if (section.size() == 0) {
        int deviceCount = api::metal::getDeviceCount();
        for (int deviceId = 0; deviceId < deviceCount; ++deviceId) {
          api::metal::device_t device = api::metal::getDevice(deviceId);

          udim_t bytes = device.getMemorySize();
          std::string bytesStr = stringifyBytes(bytes);

          section
              .add("Device Name", device.getName())
              .add("Device ID"  , toString(deviceId))
              .add("Memory"     , bytesStr)
              .addDivider();
        }
        // Remove last divider
        section.groups.pop_back();
      }
      return section;
    }

    occa::mode<metal::modeInfo,
               metal::device> mode("Metal");
  }
}

#ifndef __LINUX_REGISTER_ACCESSOR__
#define __LINUX_REGISTER_ACCESSOR__
#include "registeraccessor.h"
#include "hid.h"

namespace pixart
{
    class Plp239RegAccr: public RegisterAccessor
    {
    private:
        HidDevice* mHidDevice;

        uint64_t mMaxBurstLength;

    public:
        Plp239RegAccr(HidDevice* hidDevice);
        virtual ~Plp239RegAccr();
        virtual void prepare();
        virtual byte readRegister(byte bank, byte address);
        virtual int readRegisters(byte* data, byte bank, byte startAddress,
                uint64_t length);
        virtual int burstReadRegister(byte* data, byte bank, byte address,
                uint64_t length);
        virtual void writeRegister(byte bank, byte address, byte value);
        virtual void writeRegisters(byte bank, byte startAddress, byte* values,
                uint64_t length);
        virtual void burstWriteRegister(byte bank, byte address, byte* values,
                uint64_t length);
    };
}

#endif //__LINUX_REGISTER_ACCESSOR__

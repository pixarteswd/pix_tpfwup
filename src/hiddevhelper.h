#ifndef __HID_DEV_HELPER__
#define __HID_DEV_HELPER__
#include "devhelper.h"
#include "hid.h"

namespace pixart
{
    class HidDevHelper: public DevHelper
    {
    private:
        HidDevice* mDev;
    public:
        HidDevHelper(HidDevice* dev);

        virtual int getBusType();
        virtual int getVid();
        virtual int getPid();
    };
}

#endif //__HID_DEV_HELPER__

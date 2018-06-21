#include "hiddevhelper.h"
#include "type.h"

using namespace pixart;

HidDevHelper::HidDevHelper(HidDevice* dev) :
        mDev(dev)
{
}

int HidDevHelper::getBusType()
{
    hidraw_devinfo info;
    bool res = mDev->getRawInfo(&info);
    if (res)
    {
        return info.bustype;
    }
    return -1;
}
int HidDevHelper::getVid()
{
    hidraw_devinfo info;
    bool res = mDev->getRawInfo(&info);
    if (res)
    {
        return info.vendor;
    }
    return -1;
}
int HidDevHelper::getPid()
{
    hidraw_devinfo info;
    bool res = mDev->getRawInfo(&info);
    if (res)
    {
        return info.product;
    }
    return -1;
}

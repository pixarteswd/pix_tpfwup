#ifndef __DEV_HELPER__
#define __DEV_HELPER__
namespace pixart
{
    class DevHelper
    {
    public:
        DevHelper() {};
        virtual ~DevHelper() {};
        virtual int getBusType() = 0;
        virtual int getVid() = 0;
        virtual int getPid() = 0;
    };
}
#endif //__DEV_HELPER__

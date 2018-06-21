#include "flashcontroller.h"

using namespace pixart;

FlashController::FlashController(RegisterAccessor * regAccessor)
{
    mRegAccessor = regAccessor;
}

FlashController::~FlashController()
{
}

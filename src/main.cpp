#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

#include "hid.h"
#include "hiddevhelper.h"
#include "plp239regaccr.h"
#include "plp239flashctrlr.h"
#include "plp239fwupdater.h"

using namespace std;
using namespace pixart;

#define TITLE       "Pixart Touchpad Utility"
#define VERSION      000001
#define VERSION_STR "v0.0.1"

int main(int argc, char **argv)
{
    printf("%s (%s)\n", TITLE, VERSION_STR);
    if (argc < 2)
    {
        printf("Please input HIDRAW path.\n");
        return 0;
    }
    char * path = argv[1];
    int res = 1;
    HidDevice hiddev;
    res = hiddev.open(path);
    if (!res)
    {
        printf("Failed to open hidraw interface.\n");
        return 0;
    }

    HidDevHelper devHelper(&hiddev);
    Plp239RegAccr regAccr(&hiddev);
    Plp239FwUpdater fwUpdater(&devHelper, &regAccr);

    if (argc > 2)
    {
        for (int i = 2; i < argc; ++i)
        {
            string param = argv[i];
            if (param == "reset_hw")
            {
                printf("=== Reset to HW Test Mode + ===\n");
                res = fwUpdater.reset(Plp239FwUpdater::ResetType::HwTestMode);
                printf("=== Reset to HW Test Mode - ===\n");
                break;
            }
            else if (param == "reset_re")
            {
                printf("=== Reset to Regular Mode + ===\n");
                res = fwUpdater.reset(Plp239FwUpdater::ResetType::Regular);
                printf("=== Reset to Regular Mode - ===\n");
                break;
            }
            else if (param == "show_rd")
            {
                shared_ptr<ReportDescriptor> rptDesc =
                        hiddev.getReportDescriptor();
                printf("%s", rptDesc->toString().c_str());
                break;
            }
            else if (param == "get_fwver")
            {
                int fwVer = fwUpdater.getFwVersion();
                printf("Firmware Version: %04x\n", fwVer);
                break;
            }
            else if (param == "update_fw")
            {
                if ((i + 1) >= argc)
                {
                    printf("Please provide firmware path.\n");
                    res = 0;
                    break;
                }
                string fwPath = argv[++i];
                res = fwUpdater.loadFwBin(fwPath.c_str());
                printf("Read firmware file, res = %d\n", res);

                fwUpdater.writeFirmware();
                fwUpdater.releaseFwBin();
                break;
            }
            else if (param == "update_hid")
            {
                if ((i + 1) >= argc)
                {
                    printf("Please provide hid descriptor file path.\n");
                    res = 0;
                    break;
                }
                string path = argv[++i];
                res = fwUpdater.loadHidDescFile(path.c_str());
                printf("Read firmware file, res = %d\n", res);

                fwUpdater.writeHidDesc();
                fwUpdater.releaseHidDescBin();
                break;
            }
            else if (param == "update_param")
            {
                if ((i + 1) >= argc)
                {
                    printf("Please provide parameter file path.\n");
                    res = 0;
                    break;
                }
                string path = argv[++i];
                bool res = fwUpdater.loadParameterFile(path.c_str());
                printf("Read parameter file, res = %d\n", res);

                fwUpdater.writeParameter();
                fwUpdater.releaseParameterBin();
                break;
            }
            else if (param == "up")
            {
                if ((i + 1) >= argc)
                {
                    printf("Please provide firmware file path.\n");
                    res = 0;
                    break;
                }

                printf("=== Reset to HW Mode ===\n");
                res = fwUpdater.reset(Plp239FwUpdater::ResetType::HwTestMode);
                if (!res)
                {
                    printf("\tReset failed.\n");
                    break;
                }
                printf("=== Start upgrade ===\n");
                string path = argv[i + 1];
                res = fwUpdater.loadUpgradeBin(path.c_str());
                printf("Read upgrade file, res = %d\n", res);
                if (!res)
                {
                    printf("\tFailed to read upgrade file.\n");
                    break;
                }
                res = fwUpdater.fullyUpgrade();
                if (!res)
                {
                    printf("\tFailed to upgrade.\n");
                    break;
                }
                printf("=== Reset to Regular Mode ===\n");
                res = fwUpdater.reset(Plp239FwUpdater::ResetType::Regular);
                if (!res)
                {
                    printf("\tReset failed.\n");
                    break;
                }
            }
        }
    }
    // release
    hiddev.close();
    return 1;
}


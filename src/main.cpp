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

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Please input HIDRAW path.\n");
        return 0;
    }
    char * path = argv[1];
    HidDevice hiddev;
    hiddev.open(path);

    HidDevHelper devHelper(&hiddev);
    Plp239RegAccr regAccr(&hiddev);
    Plp239FwUpdater fwUpdater(&devHelper, &regAccr);

    if (argc > 2)
    {
        for (int i = 2; i < argc; ++i)
        {
            string param = argv[i];
            //printf("param: %s", param);
            if (param == "reset_hw")
            {
                printf("=== Reset to HW Test Mode + ===\n");
                fwUpdater.reset(Plp239FwUpdater::ResetType::HwTestMode);
                printf("=== Reset to HW Test Mode - ===\n");
            }
            else if (param == "reset_re")
            {
                printf("=== Reset to Regular Mode + ===\n");
                fwUpdater.reset(Plp239FwUpdater::ResetType::Regular);
                printf("=== Reset to Regular Mode - ===\n");
            }
            else if (param == "show_rd")
            {
                shared_ptr<ReportDescriptor> rptDesc =
                        hiddev.getReportDescriptor();
                printf("%s", rptDesc->toString().c_str());
            }
            else if (param == "update_fw")
            {
                if ((i + 1) >= argc)
                {
                    printf("Please provide firmware path.\n");
                    break;
                }
                string fwPath = argv[i + 1];
                bool res = fwUpdater.loadFwBin(fwPath.c_str());
                printf("Read firmware file, res = %d\n", res);

                //////////////////
                //return 0;
                //////////////////

                fwUpdater.writeFirmware();
                fwUpdater.releaseFwBin();
            }
            else if (param == "update_hid")
            {
                if ((i + 1) >= argc)
                {
                    printf("Please provide hid descriptor file path.\n");
                    break;
                }
                string path = argv[i + 1];
                bool res = fwUpdater.loadHidDescFile(path.c_str());
                printf("Read firmware file, res = %d\n", res);

                //////////////////
                //return 0;
                //////////////////

                fwUpdater.writeHidDesc();
                fwUpdater.releaseHidDescBin();
            }
            else if (param == "update_param")
            {
                if ((i + 1) >= argc)
                {
                    printf("Please provide parameter file path.\n");
                    break;
                }
                string path = argv[i + 1];
                bool res = fwUpdater.loadParameterFile(path.c_str());
                printf("Read parameter file, res = %d\n", res);

                //////////////////
                //return 0;
                //////////////////
                fwUpdater.writeParameter();
                fwUpdater.releaseParameterBin();
            }
            else if (param == "up")
            {
                if ((i + 1) >= argc)
                {
                    printf("Please provide parameter file path.\n");
                    break;
                }

                printf("=== Reset to HW Test Mode ===\n");
                fwUpdater.reset(Plp239FwUpdater::ResetType::HwTestMode);
                printf("=== Start upgrade ===\n");
                string path = argv[i + 1];
                bool res = fwUpdater.loadUpgradeBin(path.c_str());
                printf("Read upgrade file, res = %d\n", res);
                fwUpdater.fullyUpgrade();
                printf("=== Reset to Regular Mode ===\n");
                fwUpdater.reset(Plp239FwUpdater::ResetType::Regular);

                return 0;
            }
        }
    }
    // release
    hiddev.close();
}


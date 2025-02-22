//  Copyright © 2022-2023 ChefKiss Inc. Licensed under the Thou Shalt Not Profit License version 1.0. See LICENSE for
//  details.

#include "kern_hwlibs.hpp"
#include "kern_nred.hpp"
#include "kern_patcherplus.hpp"
#include "kern_patches.hpp"
#include "kern_patterns.hpp"
#include <Headers/kern_api.hpp>

static const char *pathRadeonX5000HWLibs = "/System/Library/Extensions/AMDRadeonX5000HWServices.kext/Contents/PlugIns/"
                                           "AMDRadeonX5000HWLibs.kext/Contents/MacOS/AMDRadeonX5000HWLibs";

static KernelPatcher::KextInfo kextRadeonX5000HWLibs {"com.apple.kext.AMDRadeonX5000HWLibs", &pathRadeonX5000HWLibs, 1,
    {}, {}, KernelPatcher::KextInfo::Unloaded};

X5000HWLibs *X5000HWLibs::callback = nullptr;

void X5000HWLibs::init() {
    callback = this;
    lilu.onKextLoadForce(&kextRadeonX5000HWLibs);
}

bool X5000HWLibs::processKext(KernelPatcher &patcher, size_t id, mach_vm_address_t slide, size_t size) {
    if (kextRadeonX5000HWLibs.loadIndex == id) {
        NRed::callback->setRMMIOIfNecessary();

        CAILAsicCapsEntry *orgCapsTable = nullptr;
        CAILAsicCapsInitEntry *orgCapsInitTable = nullptr;
        CAILDeviceTypeEntry *orgDeviceTypeTable = nullptr;
        DeviceCapabilityEntry *orgDevCapTable = nullptr;

        SolveRequestPlus solveRequests[] = {
            {"__ZL15deviceTypeTable", orgDeviceTypeTable, kDeviceTypeTablePattern},
            {"__ZN11AMDFirmware14createFirmwareEPhjjPKc", this->orgCreateFirmware, kCreateFirmwarePattern},
            {"__ZN20AMDFirmwareDirectory11putFirmwareE16_AMD_DEVICE_TYPEP11AMDFirmware", this->orgPutFirmware,
                kPutFirmwarePattern},
            {"__ZL20CAIL_ASIC_CAPS_TABLE", orgCapsTable, kCailAsicCapsTableHWLibsPattern},
            {"_CAILAsicCapsInitTable", orgCapsInitTable, kCAILAsicCapsInitTablePattern},
            {"_DeviceCapabilityTbl", orgDevCapTable, kDeviceCapabilityTblPattern},
        };
        PANIC_COND(!SolveRequestPlus::solveAll(patcher, id, solveRequests, slide, size), "hwlibs",
            "Failed to resolve symbols");

        bool renoir = NRed::callback->chipType >= ChipType::Renoir;
        RouteRequestPlus requests[] = {
            {"__ZN35AMDRadeonX5000_AMDRadeonHWLibsX500025populateFirmwareDirectoryEv", wrapPopulateFirmwareDirectory,
                this->orgPopulateFirmwareDirectory},
            {"_smu_get_fw_constants", hwLibsNoop, kSmuGetFwConstantsPattern, kSmuGetFwConstantsMask},
            {"_smu_9_0_1_check_fw_status", hwLibsNoop, kSmu901CheckFwStatusPattern, kSmu901CheckFwStatusMask},
            {"_smu_9_0_1_unload_smu", hwLibsNoop, kSmu901UnloadSmuPattern, kSmu901UnloadSmuMask},
            {"_psp_cmd_km_submit", wrapPspCmdKmSubmit, this->orgPspCmdKmSubmit, kPspCmdKmSubmitPattern,
                kPspCmdKmSubmitMask, renoir},
            {"_update_sdma_power_gating", wrapUpdateSdmaPowerGating, this->orgUpdateSdmaPowerGating,
                kUpdateSdmaPowerGatingPattern, kUpdateSdmaPowerGatingMask},
        };
        PANIC_COND(!RouteRequestPlus::routeAll(patcher, id, requests, slide, size), "hwlibs",
            "Failed to route symbols");

        PANIC_COND(MachInfo::setKernelWriting(true, KernelPatcher::kernelWriteLock) != KERN_SUCCESS, "hwlibs",
            "Failed to enable kernel writing");
        *orgDeviceTypeTable = {.deviceId = NRed::callback->deviceId, .deviceType = 6};
        auto found = false;
        auto targetDeviceId = renoir && NRed::callback->deviceId != 0x1636 ? 0x1636 : NRed::callback->deviceId;
        while (orgCapsInitTable->deviceId != 0xFFFFFFFF) {
            if (orgCapsInitTable->familyId == AMDGPU_FAMILY_RAVEN && orgCapsInitTable->deviceId == targetDeviceId) {
                orgCapsInitTable->deviceId = NRed::callback->deviceId;
                orgCapsInitTable->revision = NRed::callback->revision;
                orgCapsInitTable->extRevision =
                    static_cast<uint64_t>(NRed::callback->enumRevision) + NRed::callback->revision;
                orgCapsInitTable->pciRevision = NRed::callback->pciRevision;
                *orgCapsTable = {
                    .familyId = AMDGPU_FAMILY_RAVEN,
                    .deviceId = NRed::callback->deviceId,
                    .revision = NRed::callback->revision,
                    .extRevision = static_cast<uint32_t>(NRed::callback->enumRevision) + NRed::callback->revision,
                    .pciRevision = NRed::callback->pciRevision,
                    .caps = orgCapsInitTable->caps,
                };
                found = true;
                break;
            }
            orgCapsInitTable++;
        }
        PANIC_COND(!found, "hwlibs", "Failed to find caps init table entry");
        found = false;
        while (orgDevCapTable->familyId) {
            if (orgDevCapTable->familyId == AMDGPU_FAMILY_RAVEN && orgDevCapTable->deviceId == targetDeviceId) {
                orgDevCapTable->deviceId = NRed::callback->deviceId;
                orgDevCapTable->extRevision =
                    static_cast<uint64_t>(NRed::callback->enumRevision) + NRed::callback->revision;
                orgDevCapTable->revision = DEVICE_CAP_ENTRY_REV_DONT_CARE;
                orgDevCapTable->enumRevision = DEVICE_CAP_ENTRY_REV_DONT_CARE;
                found = true;
                break;
            }
            orgDevCapTable++;
        }
        PANIC_COND(!found, "hwlibs", "Failed to find device capability table entry");
        MachInfo::setKernelWriting(false, KernelPatcher::kernelWriteLock);
        DBGLOG("hwlibs", "Applied DDI Caps patches");

        auto ventura = getKernelVersion() >= KernelVersion::Ventura;
        auto monterey = getKernelVersion() >= KernelVersion::Monterey;
        const LookupPatchPlus patches[] = {
            {&kextRadeonX5000HWLibs, kPspSwInitOriginal1, kPspSwInitPatched1, 1},
            {&kextRadeonX5000HWLibs, kPspSwInitOriginal2, kPspSwInitOriginalMask2, kPspSwInitPatched2,
                kPspSwInitPatchedMask2, 1},
            {&kextRadeonX5000HWLibs, kSmuInitFunctionPointerListOriginal, kSmuInitFunctionPointerListOriginalMask,
                kSmuInitFunctionPointerListPatched, kSmuInitFunctionPointerListPatchedMask, 1},
            {&kextRadeonX5000HWLibs, kFullAsicResetOriginal, kFullAsicResetPatched, 1},
            {&kextRadeonX5000HWLibs, kGcSwInitOriginal, kGcSwInitOriginalMask, kGcSwInitPatched, kGcSwInitPatchedMask,
                1},
            {&kextRadeonX5000HWLibs, kGcSetFwEntryInfoOriginal, kGcSetFwEntryInfoOriginalMask, kGcSetFwEntryInfoPatched,
                kGcSetFwEntryInfoPatchedMask, 1},
            {&kextRadeonX5000HWLibs, kCreatePowerTuneServicesOriginal1, kCreatePowerTuneServicesPatched1, 1, !monterey},
            {&kextRadeonX5000HWLibs, kCreatePowerTuneServicesMontereyOriginal1,
                kCreatePowerTuneServicesMontereyPatched1, 1, monterey},
            {&kextRadeonX5000HWLibs, kCreatePowerTuneServicesOriginal2, kCreatePowerTuneServicesMask2,
                kCreatePowerTuneServicesPatched2, 1},
            {&kextRadeonX5000HWLibs, kCailQueryAdapterInfoOriginal, kCailQueryAdapterInfoPatched, 1, ventura},
            {&kextRadeonX5000HWLibs, kSDMAInitFunctionPointerListOriginal, kSDMAInitFunctionPointerListPatched, 1,
                ventura},
        };
        PANIC_COND(!LookupPatchPlus::applyAll(patcher, patches, slide, size), "hwlibs", "Failed to apply patches: %d",
            patcher.getError());

        return true;
    }

    return false;
}

void X5000HWLibs::wrapPopulateFirmwareDirectory(void *that) {
    FunctionCast(wrapPopulateFirmwareDirectory, callback->orgPopulateFirmwareDirectory)(that);

    bool isRenoirDerivative = NRed::callback->chipType >= ChipType::Renoir;

    char filename[128] = {0};
    snprintf(filename, 128, "%s_vcn.bin", NRed::callback->getChipName());
    auto *targetFn = isRenoirDerivative ? "ativvaxy_nv.dat" : "ativvaxy_rv.dat";
    DBGLOG("wred", "%s => %s", filename, targetFn);

    auto &fwDesc = getFWDescByName(filename);
    auto *fwHeader = reinterpret_cast<const CommonFirmwareHeader *>(fwDesc.data);

    /** VCN 2.2, VCN 1.0 */
    auto *fw = callback->orgCreateFirmware(fwDesc.data + fwHeader->ucodeOff, fwHeader->ucodeSize,
        isRenoirDerivative ? 0x0202 : 0x0100, targetFn);
    PANIC_COND(!fw, "hwlibs", "Failed to create '%s' firmware", targetFn);
    DBGLOG("hwlibs", "Inserting %s!", targetFn);
    auto *fwDir = getMember<void *>(that, getKernelVersion() > KernelVersion::BigSur ? 0xB0 : 0xB8);
    PANIC_COND(!fwDir, "hwlibs", "Failed to get firmware directory");
    PANIC_COND(!callback->orgPutFirmware(fwDir, 6, fw), "hwlibs", "Failed to inject %s firmware", targetFn);
}

CAILResult X5000HWLibs::hwLibsNoop() { return kCAILResultSuccess; }

void X5000HWLibs::wrapUpdateSdmaPowerGating(void *cail, uint32_t mode) {
    FunctionCast(wrapUpdateSdmaPowerGating, callback->orgUpdateSdmaPowerGating)(cail, mode);
    switch (mode) {
        case 0:
            [[fallthrough]];
        case 3:
            NRed::callback->sendMsgToSmc(PPSMC_MSG_PowerUpSdma);
            break;
        case 2:
            NRed::callback->sendMsgToSmc(PPSMC_MSG_PowerDownSdma);
            break;
        default:
            break;
    }
}

CAILResult X5000HWLibs::wrapPspCmdKmSubmit(void *psp, void *ctx, void *param3, void *param4) {
    // Upstream patch: https://github.com/torvalds/linux/commit/f8f70c1371d304f42d4a1242d8abcbda807d0bed
    if (getMember<uint32_t>(ctx, 0x10) == 6) {
        DBGLOG("hwlibs", "Skipping MEC2 JT FW");
        return kCAILResultSuccess;
    }

    return FunctionCast(wrapPspCmdKmSubmit, callback->orgPspCmdKmSubmit)(psp, ctx, param3, param4);
}

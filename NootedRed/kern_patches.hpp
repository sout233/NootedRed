//  Copyright © 2022-2023 ChefKiss Inc. Licensed under the Thou Shalt Not Profit License version 1.0. See LICENSE for
//  details.

#pragma once
#include <Headers/kern_util.hpp>

/**
 * `AppleGraphicsDevicePolicy`
 * Symbols are stripped so function is unknown.
 * Changes frame-buffer count >= 2 check to >= 1.
 */
static const uint8_t kAGDPFBCountCheckOriginal[] = {0x02, 0x00, 0x00, 0x83, 0xF8, 0x02};
static const uint8_t kAGDPFBCountCheckPatched[] = {0x02, 0x00, 0x00, 0x83, 0xF8, 0x01};

/** Ditto */
static const uint8_t kAGDPFBCountCheckVenturaOriginal[] = {0x41, 0x83, 0xBE, 0x14, 0x02, 0x00, 0x00, 0x02};
static const uint8_t kAGDPFBCountCheckVenturaPatched[] = {0x41, 0x83, 0xBE, 0x14, 0x02, 0x00, 0x00, 0x01};

/**
 * `AppleGraphicsDevicePolicy::start`
 * Neutralise access to AGDP configuration by board identifier.
 */
static const uint8_t kAGDPBoardIDKeyOriginal[] = "board-id";
static const uint8_t kAGDPBoardIDKeyPatched[] = "applehax";

/**
 * `_gc_sw_init`
 * AMDRadeonX5000HWLibs.kext
 * Replace call to `_gc_get_hw_version` with constant (0x090400).
 */
static const uint8_t kGcSwInitOriginal[] = {0x0C, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x41, 0x89, 0xC7};
static const uint8_t kGcSwInitOriginalMask[] = {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF};
static const uint8_t kGcSwInitPatched[] = {0x00, 0xB8, 0x00, 0x04, 0x09, 0x00};
static const uint8_t kGcSwInitPatchedMask[] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

/**
 * `_gc_set_fw_entry_info`
 * AMDRadeonX5000HWLibs.kext
 * Replace call to `_gc_get_hw_version` with constant (0x090400).
 */
static const uint8_t kGcSetFwEntryInfoOriginal[] = {0xE8, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x41, 0x89, 0x00, 0x10,
    0x41, 0x89, 0x00, 0x00, 0x00};
static const uint8_t kGcSetFwEntryInfoMask[] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
    0xFF, 0x00, 0x00, 0x00};
static const uint8_t kGcSetFwEntryInfoPatched[] = {0xB8, 0x00, 0x04, 0x09, 0x00};

/**
 * `_psp_sw_init`
 * AMDRadeonX5000HWLibs.kext
 * Force major version switch case to always use case 0xB.
 */
static const uint8_t kPspSwInitOriginal1[] = {0x8B, 0x43, 0x0C, 0x83, 0xC0, 0xF7, 0x83, 0xF8, 0x04};
static const uint8_t kPspSwInitPatched1[] = {0xC7, 0xC0, 0x02, 0x00, 0x00, 0x00, 0x83, 0xF8, 0x04};

/**
 * `_psp_sw_init`
 * AMDRadeonX5000HWLibs.kext
 * Force minor & patch checks to always use case 0x0.
 */
static const uint8_t kPspSwInitOriginal2[] = {0x8B, 0x43, 0x10, 0x83, 0xF8, 0x05, 0x74, 0x00, 0x85, 0xC0, 0x75, 0x00,
    0x8B, 0x43, 0x14, 0x48, 0x83, 0xF8, 0x0D, 0x77, 0x00};
static const uint8_t kPspSwInitMask2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
static const uint8_t kPspSwInitPatched2[] = {0x66, 0x48, 0x90, 0x66, 0x48, 0x90, 0x48, 0x90, 0x48, 0x90, 0x48, 0x90,
    0x31, 0xC0, 0x90, 0x48, 0x83, 0xF8, 0x0D};

/**
 * `_smu_init_function_pointer_list`
 * AMDRadeonX5000HWLibs.kext
 * Replace call to `_smu_get_hw_version` with constant (0x1).
 */
static const uint8_t kSmuInitFunctionPointerListOriginal[] = {0xE8, 0x00, 0x00, 0x00, 0x00, 0x89, 0xC3, 0x41, 0x89,
    0x87, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kSmuInitFunctionPointerListMask[] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00};
static const uint8_t kSmuInitFunctionPointerListPatched[] = {0xB8, 0x01, 0x00, 0x00, 0x00};

/**
 * `_smu_9_0_1_full_asic_reset`
 * AMDRadeonX5000HWLibs.kext
 * Change SMC message from `0x3B` to `0x1E` as the original one is wrong for SMU 10/12.
 */
static const uint8_t kFullAsicResetOriginal[] = {0x8B, 0x56, 0x04, 0xBE, 0x3B, 0x00, 0x00, 0x00};
static const uint8_t kFullAsicResetPatched[] = {0x8B, 0x56, 0x04, 0xBE, 0x1E, 0x00, 0x00, 0x00};

/**
 * `AtiApplePowerTuneServices::createPowerTuneServices`
 * AMDRadeonX5000HWLibs.kext
 * Change switch statement case `0x8D` to `0x8E`.
 */
static const uint8_t kCreatePowerTuneServicesOriginal1[] = {0x41, 0x8B, 0x47, 0x18, 0x83, 0xC0, 0x88, 0x83, 0xF8, 0x17};
static const uint8_t kCreatePowerTuneServicesPatched1[] = {0x41, 0x8B, 0x47, 0x18, 0x83, 0xC0, 0x87, 0x83, 0xF8, 0x17};

/** Ditto */
static const uint8_t kCreatePowerTuneServicesMontereyOriginal1[] = {0xB8, 0x7E, 0xFF, 0xFF, 0xFF, 0x41, 0x03, 0x47,
    0x18, 0x83, 0xF8, 0x0F};
static const uint8_t kCreatePowerTuneServicesMontereyPatched1[] = {0xB8, 0x7D, 0xFF, 0xFF, 0xFF, 0x41, 0x03, 0x47, 0x18,
    0x83, 0xF8, 0x0F};

/**
 * `AtiApplePowerTuneServices::createPowerTuneServices`
 * AMDRadeonX5000HWLibs.kext
 * Remove revision check to always use Vega 10 PowerTune.
 */
static const uint8_t kCreatePowerTuneServicesOriginal2[] = {0x41, 0x8B, 0x47, 0x1C, 0x83, 0xF8, 0x13, 0x77, 0x00};
static const uint8_t kCreatePowerTuneServicesMask2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
static const uint8_t kCreatePowerTuneServicesPatched2[] = {0x41, 0x8B, 0x47, 0x1C, 0x66, 0x90, 0x66, 0x90, 0x90};

/**
 * `cailQueryAdapterInfo`
 * AMDRadeonX5000HWLibs.kext
 * Ventura added an explicit switch case for family ID.
 * Now we have to make the switch case 0x8D be 0x8E.
 */
static const uint8_t kCailQueryAdapterInfoOriginal[] = {0x83, 0xC0, 0x92, 0x83, 0xF8, 0x21};
static const uint8_t kCailQueryAdapterInfoPatched[] = {0x83, 0xC0, 0x91, 0x83, 0xF8, 0x21};

/**
 * `_sdma_init_function_pointer_list`
 * AMDRadeonX5000HWLibs.kext
 * Ventura removed the code for SDMA 4.1.x. Force use SDMA 4.0.
 */
static const uint8_t kSDMAInitFunctionPointerListOriginal[] = {0x81, 0xFB, 0x00, 0x00, 0x04, 0x00, 0x0F};
static const uint8_t kSDMAInitFunctionPointerListPatched[] = {0x39, 0xDB, 0x66, 0x90, 0x66, 0x90, 0x0F};

/**
 * `AMDRadeonX6000_AmdAsicInfoNavi::populateDeviceInfo`
 * AMDRadeonX6000.kext
 * Fix register read (0xD31 -> 0xD2F) and family ID (0x8F -> 0x8E).
 */
static const uint8_t kPopulateDeviceInfoOriginal[] {0xBE, 0x31, 0x0D, 0x00, 0x00, 0xFF, 0x90, 0x40, 0x01, 0x00, 0x00,
    0xC7, 0x43, 0x60, 0x8F, 0x00, 0x00, 0x00};
static const uint8_t kPopulateDeviceInfoPatched[] {0xBE, 0x2F, 0x0D, 0x00, 0x00, 0xFF, 0x90, 0x40, 0x01, 0x00, 0x00,
    0xC7, 0x43, 0x60, 0x8E, 0x00, 0x00, 0x00};

/**
 * `AmdAtomFwServices::initializeAtomDataTable`
 * AMDRadeonX6000Framebuffer.kext
 * Neutralise `AmdAtomVramInfo` creation null check.
 * We don't have this entry in our VBIOS.
 */
static const uint8_t kAmdAtomVramInfoNullCheckOriginal[] = {0x48, 0x89, 0x83, 0x90, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC0,
    0x0F, 0x84, 0x89, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x7B, 0x18};
static const uint8_t kAmdAtomVramInfoNullCheckPatched[] = {0x48, 0x89, 0x83, 0x90, 0x00, 0x00, 0x00, 0x66, 0x90, 0x66,
    0x90, 0x66, 0x90, 0x66, 0x90, 0x90, 0x48, 0x8B, 0x7B, 0x18};

/**
 * `AmdAtomFwServices::initializeAtomDataTable`
 * AMDRadeonX6000Framebuffer.kext
 * Neutralise `AmdAtomPspDirectory` creation null check.
 * We don't have this entry in our VBIOS.
 */
static const uint8_t kAmdAtomPspDirectoryNullCheckOriginal[] = {0x48, 0x89, 0x83, 0x88, 0x00, 0x00, 0x00, 0x48, 0x85,
    0xC0, 0x0F, 0x84, 0xA1, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x7B, 0x18};
static const uint8_t kAmdAtomPspDirectoryNullCheckPatched[] = {0x48, 0x89, 0x83, 0x88, 0x00, 0x00, 0x00, 0x66, 0x90,
    0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x90, 0x48, 0x8B, 0x7B, 0x18};

/**
 * `AmdAtomFwServices::getFirmwareInfo`
 * AMDRadeonX6000Framebuffer.kext
 * Neutralise `AmdAtomVramInfo` null check.
 */
static const uint8_t kGetFirmwareInfoNullCheckOriginal[] = {0x48, 0x83, 0xBB, 0x90, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x84,
    0x90, 0x00, 0x00, 0x00, 0x49, 0x89};
static const uint8_t kGetFirmwareInfoNullCheckPatched[] = {0x48, 0x83, 0xBB, 0x90, 0x00, 0x00, 0x00, 0x00, 0x66, 0x90,
    0x66, 0x90, 0x66, 0x90, 0x49, 0x89};

/**
 * `AMDRadeonX6000_AmdAgdcServices::getVendorInfo`
 * AMDRadeonX6000Framebuffer.kext
 * Tell AGDC that we're an iGPU.
 */
static const uint8_t kAgdcServicesGetVendorInfoOriginal[] = {0xC7, 0x00, 0x00, 0x00, 0x03, 0x00, 0x48, 0x00, 0x02, 0x10,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
static const uint8_t kAgdcServicesGetVendorInfoMask[] = {0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t kAgdcServicesGetVendorInfoPatched[] = {0xC7, 0x00, 0x00, 0x00, 0x03, 0x00, 0x48, 0x00, 0x02, 0x10,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00};

/**
 * `AMDRadeonX6000_AmdRadeonController::powerUp`
 * AMDRadeonX6000Framebuffer.kext
 * Remove new FB count condition so we can restore the original behaviour before Ventura.
 */
static const uint8_t kControllerPowerUpOriginal[] = {0x38, 0xC8, 0x0F, 0x42, 0xC8, 0x88, 0x8F, 0xBC, 0x00, 0x00, 0x00,
    0x72, 0x00};
static const uint8_t kControllerPowerUpOriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00};
static const uint8_t kControllerPowerUpReplace[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xEB, 0x00};
static const uint8_t kControllerPowerUpReplaceMask[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xFF, 0x00};

/**
 * `AMDRadeonX6000_AmdRadeonFramebuffer::validateDetailedTiming`
 * AMDRadeonX6000Framebuffer.kext
 * Remove new problematic Ventura pixel clock multiplier calculation which causes timing validation mishaps.
 */
static const uint8_t kValidateDetailedTimingOriginal[] = {0x66, 0x0F, 0x2E, 0xC1, 0x76, 0x06, 0xF2, 0x0F, 0x5E, 0xC1};
static const uint8_t kValidateDetailedTimingPatched[] = {0x66, 0x0F, 0x2E, 0xC1, 0x66, 0x90, 0xF2, 0x0F, 0x5E, 0xC1};

/**
 * `AMDRadeonX5000_AMDHardware::startHWEngines`
 * AMDRadeonX5000.kext
 * Make for loop run only once as we only have one SDMA engine.
 */
static const uint8_t kStartHWEnginesOriginal[] = {0x40, 0x83, 0xF0, 0x02};
static const uint8_t kStartHWEnginesMask[] = {0xF0, 0xFF, 0xF0, 0xFF};
static const uint8_t kStartHWEnginesPatched[] = {0x40, 0x83, 0xF0, 0x01};

/**
 * `Addr::Lib::Create`
 * AMDRadeonX5000.kext
 * The check inside was changed from `familyId - 0x8D < 2` to `familyId == 0x8D` in Ventura 13.4.
 * Change the 0x8D (AI) to 0x8E (RV).
 */
static const uint8_t kAddrLibCreateOriginal[] = {0x41, 0x81, 0x7D, 0x08, 0x8D, 0x00, 0x00, 0x00};
static const uint8_t kAddrLibCreatePatched[] = {0x41, 0x81, 0x7D, 0x08, 0x8E, 0x00, 0x00, 0x00};

/**
 * Mismatched `getGpuDebugPolicy` virtual calls.
 * AMDRadeonX6000.kext
 */
static const uint8_t kGetGpuDebugPolicyCallOriginal[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xC0, 0x03, 0x00, 0x00};
static const uint8_t kGetGpuDebugPolicyCallPatched[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xC8, 0x03, 0x00, 0x00};

/**
 * `AMDRadeonX6000_AMDHWChannel::submitCommandBuffer`
 * AMDRadeonX6000.kext
 * VTable Call to signalGPUWorkSubmitted.
 * Doesn't exist on X5000, but looks like it isn't necessary, so we just NO-OP it.
 */
static const uint8_t kHWChannelSubmitCommandBufferOriginal[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0x30, 0x02, 0x00, 0x00,
    0x48, 0x8B, 0x43};
static const uint8_t kHWChannelSubmitCommandBufferPatched[] = {0x48, 0x8B, 0x07, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90,
    0x48, 0x8B, 0x43};

/**
 * Mismatched `getScheduler` virtual calls.
 * AMDRadeonX6000.kext
 */
static const uint8_t kGetSchedulerCallOriginal[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xB8, 0x03, 0x00, 0x00};
static const uint8_t kGetSchedulerCallPatched[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xC0, 0x03, 0x00, 0x00};

/** Ditto */
static const uint8_t kGetSchedulerCallVenturaOriginal[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xB0, 0x03, 0x00, 0x00};
static const uint8_t kGetSchedulerCallVenturaPatched[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xB8, 0x03, 0x00, 0x00};

/**
 * Mismatched `isDeviceValid` virtual calls.
 * AMDRadeonX6000.kext
 */
static const uint8_t kIsDeviceValidCallOriginal[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xA0, 0x02, 0x00, 0x00};
static const uint8_t kIsDeviceValidCallPatched[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0x98, 0x02, 0x00, 0x00};

/**
 * Mismatched `isDevicePCITunnelled` virtual call.
 * `AMDRadeonX6000_AMDNavi10VideoContext::setSuspendResumeState`
 * AMDRadeonX6000.kext
 */
static const uint8_t kIsDevicePCITunnelledCallOriginal[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xB0, 0x02, 0x00, 0x00};
static const uint8_t kIsDevicePCITunnelledCallPatched[] = {0x48, 0x8B, 0x07, 0xFF, 0x90, 0xA8, 0x02, 0x00, 0x00};

/** VideoToolbox DRM model check */
static const char kVideoToolboxDRMModelOriginal[] = "MacPro5,1\0MacPro6,1\0IOService";

static const char kHwGvaId[] = "Mac-27AD2F918AE68F61";

/** AppleGVA model check */
static const char kAGVABoardIdOriginal[] = "board-id\0hw.model";
static const char kAGVABoardIdPatched[] = "hwgva-id";

static const char kCoreLSKDMSEPath[] = "/System/Library/PrivateFrameworks/CoreLSKDMSE.framework/Versions/A/CoreLSKDMSE";
static const char kCoreLSKDPath[] = "/System/Library/PrivateFrameworks/CoreLSKD.framework/Versions/A/CoreLSKD";

static const uint8_t kCoreLSKDOriginal[] = {0xC7, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x0F, 0xA2};
static const uint8_t kCoreLSKDPatched[] = {0xC7, 0xC0, 0xC3, 0x06, 0x03, 0x00, 0x66, 0x90};

/** AppleGVAHEVCEncoder model check */
static const uint8_t kHEVCEncBoardIdOriginal[] = "vendor8bit\0IOService\0board-id";
static const uint8_t kHEVCEncBoardIdPatched[] = "vendor8bit\0IOService\0hwgva-id";

/**
 * `VAAcceleratorInfo::identify`
 * AMDRadeonVADriver2.bundle
 * The device info identification fails, as the device id is not present in the function.
 * Patch fallback "error" value (0x12) to Navi 10 (0xC).
 */
static const uint8_t kVAAcceleratorInfoIdentifyOriginal[] = {0x85, 0xC0, 0x74, 0x00, 0xBB, 0x12, 0x00, 0x00, 0x00, 0x89,
    0xD8, 0x48, 0x83, 0xC4, 0x00};
static const uint8_t kVAAcceleratorInfoIdentifyOriginalMask[] = {0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
static const uint8_t kVAAcceleratorInfoIdentifyPatched[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C};
static const uint8_t kVAAcceleratorInfoIdentifyPatchedMask[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};

/** Ditto */
static const uint8_t kVAAcceleratorInfoIdentifyVenturaOriginal[] = {0x48, 0xC7, 0x45, 0xF0, 0x18, 0x01, 0x00, 0x00,
    0xBB, 0x0B, 0x00, 0x00, 0x00, 0x83, 0xFE, 0x01, 0x75, 0x00};
static const uint8_t kVAAcceleratorInfoIdentifyVenturaOriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
static const uint8_t kVAAcceleratorInfoIdentifyVenturaPatched[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x05};
static const uint8_t kVAAcceleratorInfoIdentifyVenturaPatchedMask[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xFF};

/**
 * `Vcn2DecCommand::writeUvdNoOp`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kWriteUvdNoOpOriginal[] = {0x48, 0x8B, 0x07, 0xBE, 0x3F, 0x05, 0x00, 0x00, 0xFF, 0x50, 0x20};
static const uint8_t kWriteUvdNoOpPatched[] = {0x48, 0x8B, 0x07, 0xBE, 0xFF, 0x81, 0x00, 0x00, 0xFF, 0x50, 0x20};

/**
 * `Vcn2DecCommand::writeUvdEngineStart`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kWriteUvdEngineStartOriginal[] = {0x48, 0x8B, 0x07, 0xBE, 0x06, 0x05, 0x00, 0x00, 0xFF, 0x50,
    0x20};
static const uint8_t kWriteUvdEngineStartPatched[] = {0x48, 0x8B, 0x07, 0xBE, 0xC6, 0x81, 0x00, 0x00, 0xFF, 0x50, 0x20};

/**
 * `Vcn2DecCommand::writeUvdGpcomVcpuCmd`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kWriteUvdGpcomVcpuCmdOriginal[] = {0x48, 0x8B, 0x07, 0xBE, 0x03, 0x05, 0x00, 0x00, 0xFF, 0x50,
    0x20};
static const uint8_t kWriteUvdGpcomVcpuCmdPatched[] = {0x48, 0x8B, 0x07, 0xBE, 0xC3, 0x81, 0x00, 0x00, 0xFF, 0x50,
    0x20};

/**
 * `Vcn2DecCommand::writeUvdGpcomVcpuData0`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kWriteUvdGpcomVcpuData0Original[] = {0x48, 0x8B, 0x07, 0xBE, 0x04, 0x05, 0x00, 0x00, 0xFF, 0x50,
    0x20};
static const uint8_t kWriteUvdGpcomVcpuData0Patched[] = {0x48, 0x8B, 0x07, 0xBE, 0xC4, 0x81, 0x00, 0x00, 0xFF, 0x50,
    0x20};

/**
 * `Vcn2DecCommand::writeUvdGpcomVcpuData1`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kWriteUvdGpcomVcpuData1Original[] = {0x48, 0x8B, 0x07, 0xBE, 0x05, 0x05, 0x00, 0x00, 0xFF, 0x50,
    0x20};
static const uint8_t kWriteUvdGpcomVcpuData1Patched[] = {0x48, 0x8B, 0x07, 0xBE, 0xC5, 0x81, 0x00, 0x00, 0xFF, 0x50,
    0x20};

/**
 * `Vcn2EncCommand::addEncodePacket`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kAddEncodePacketOriginal[] = {0xBE, 0x0F, 0x00, 0x00, 0x00, 0xBA, 0x2C, 0x00, 0x00, 0x00, 0xE8,
    0x00, 0x00, 0x00, 0x00};
static const uint8_t kAddEncodePacketMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00};
static const uint8_t kAddEncodePacketPatched[] = {0xBE, 0x0B, 0x00, 0x00, 0x00, 0xBA, 0x2C, 0x00, 0x00, 0x00, 0xE8,
    0x00, 0x00, 0x00, 0x00};

/**
 * `Vcn2EncCommand::addSliceHeaderPacket`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kAddSliceHeaderPacketOriginal[] = {0x00, 0x00, 0x00, 0xBE, 0x0B, 0x00, 0x00, 0x00, 0xBA, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kAddSliceHeaderPacketMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kAddSliceHeaderPacketPatched[] = {0x00, 0x00, 0x00, 0xBE, 0x0A, 0x00, 0x00, 0x00, 0xBA, 0xC0, 0x00,
    0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00};

/**
 * `Vcn2EncCommand::addIntraRefreshPacket`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kAddIntraRefreshPacketOriginal[] = {0x01, 0x00, 0x00, 0xBE, 0x10, 0x00, 0x00, 0x00, 0xBA, 0x0C,
    0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kAddIntraRefreshPacketMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kAddIntraRefreshPacketPatched[] = {0x01, 0x00, 0x00, 0xBE, 0x0C, 0x00, 0x00, 0x00, 0xBA, 0x0C,
    0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00};

/**
 * `Vcn2EncCommand::addContextBufferPacket`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kAddContextBufferPacketOriginal[] = {0x00, 0x00, 0x00, 0xBE, 0x11, 0x00, 0x00, 0x00, 0xBA, 0x58,
    0x02, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00};
static const uint8_t kAddContextBufferPacketMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00};
static const uint8_t kAddContextBufferPacketPatched[] = {0x00, 0x00, 0x00, 0xBE, 0x0D, 0x00, 0x00, 0x00, 0xBA, 0x58,
    0x02, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00};

/**
 * `Vcn2EncCommand::addBitstreamBufferPacket`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kAddBitstreamBufferPacketOriginal[] = {0xBE, 0x12, 0x00, 0x00, 0x00, 0xBA, 0x14, 0x00, 0x00, 0x00,
    0xE8, 0x00, 0x00, 0x00};
static const uint8_t kAddBitstreamBufferPacketMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x00, 0x00, 0x00};
static const uint8_t kAddBitstreamBufferPacketPatched[] = {0xBE, 0x0E, 0x00, 0x00, 0x00, 0xBA, 0x14, 0x00, 0x00, 0x00,
    0xE8, 0x00, 0x00, 0x00};

/**
 * `Vcn2EncCommand::addFeedbackBufferPacket`
 * AMDRadeonVADriver2.bundle
 */
static const uint8_t kAddFeedbackBufferPacketOriginal[] = {0xBE, 0x15, 0x00, 0x00, 0x00, 0xBA, 0x14, 0x00, 0x00, 0x00,
    0xE8, 0x00, 0x00, 0x00};
static const uint8_t kAddFeedbackBufferPacketMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00};
static const uint8_t kAddFeedbackBufferPacketPatched[] = {0xBE, 0x10, 0x00, 0x00, 0x00, 0xBA, 0x14, 0x00, 0x00, 0x00,
    0xE8, 0x00, 0x00, 0x00};

/**
 * `Vcn2EncCommand::addInputFormatPacket` and `Vcn2EncCommand::addOutputFormatPacket`
 * AMDRadeonVADriver2.bundle
 * VCN 1 does not have these packets, therefore we make these methods do nothing
 */
static const uint8_t kAddInputFormatPacketOriginal[] = {0x55, 0x48, 0x89, 0xE5, 0x48, 0x8D, 0x80, 0x84, 0x05, 0x00,
    0x00, 0xBE, 0x0C, 0x00, 0x00, 0x00, 0xBA, 0x1C, 0x00, 0x00, 0x00};
static const uint8_t kAddOutputFormatPacketOriginal[] = {0x55, 0x48, 0x89, 0xE5, 0x48, 0x8D, 0x80, 0xA0, 0x05, 0x00,
    0x00, 0xBE, 0x0D, 0x00, 0x00, 0x00, 0xBA, 0x10, 0x00, 0x00, 0x00};
static const uint8_t kAddFormatPacketMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t kRetZero[] = {0x48, 0xC7, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x90};

/**
 * `VAFactory::createGraphicsEngine`
 * AMDRadeonVADriver2.bundle
 * Force use GFX 9 variant of the graphics engines
 */
static const uint8_t kVAFactoryCreateGraphicsEngineOriginal[] = {0x48, 0x8B, 0x86, 0x60, 0x04, 0x00, 0x00, 0x8B, 0x40,
    0x0C, 0x83, 0xF8, 0x07, 0x77, 0x00};
static const uint8_t kVAFactoryCreateGraphicsEngineMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00};
static const uint8_t kVAFactoryCreateGraphicsEnginePatched[] = {0xC7, 0xC0, 0x04, 0x00, 0x00, 0x00, 0x66, 0x90, 0x66,
    0x90};

/** Ditto */
static const uint8_t kVAFactoryCreateGraphicsEngineAndBltVenturaOriginal[] = {0x48, 0x8B, 0x86, 0x60, 0x04, 0x00, 0x00,
    0x8B, 0x40, 0x0C, 0x8D, 0x48, 0xFF, 0x83, 0xF9, 0x02, 0x72, 0x00, 0x8D, 0x48, 0xFD, 0x83, 0xF9, 0x02};
static const uint8_t kVAFactoryCreateGraphicsEngineAndBltVenturaMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

/**
 * `VAFactory::create*VP`
 * AMDRadeonVADriver2.bundle
 * Force use GFX 9 variants of the video processors
 */
static const uint8_t kVAFactoryCreateVPOriginal[] = {0x83, 0xFE, 0x07, 0x77, 0x00, 0x89, 0xF0, 0x48, 0x8D, 0x0D, 0x00,
    0x00, 0x00, 0x00, 0x48, 0x63, 0x04, 0x81, 0x48, 0x01, 0xC8, 0xFF, 0xE0, 0xBF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00,
    0x00, 0x00, 0x00};
static const uint8_t kVAFactoryCreateVPMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00};
static const uint8_t kVAFactoryCreateVPPatched[] = {0xBE, 0x04, 0x00, 0x00, 0x00};

/** Ditto */
static const uint8_t kVAFactoryCreateVPVenturaOriginal[] = {0x8D, 0x46, 0xFF, 0x83, 0xF8, 0x02, 0x72, 0x00, 0x8D, 0x46,
    0xFD, 0x83, 0xF8, 0x02, 0x73, 0x00, 0xBF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kVAFactoryCreateVPVenturaOriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kVAFactoryCreateVPVenturaPatched[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEB};
static const uint8_t kVAFactoryCreateVPVenturaPatchedMask[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};

/**
 * `VAFactory::createImageBlt`
 * AMDRadeonVADriver2.bundle
 * Force use GFX 9 variant of the image blitter
 */
static const uint8_t kVAFactoryCreateImageBltOriginal[] = {0x48, 0x89, 0xF7, 0x48, 0x8B, 0x86, 0x60, 0x04, 0x00, 0x00,
    0x8B, 0x40, 0x0C, 0x48, 0x83, 0xF8, 0x07, 0x77, 0x00, 0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kVAFactoryCreateImageBltMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kVAFactoryCreateImageBltPatched[] = {0x48, 0x89, 0xF7, 0x48, 0xB8, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00};

/**
 * `VAAddrLibInterface::init`
 * AMDRadeonVADriver2.bundle
 * Remove check for Vega family ID (0x8D) to correctly utilise GFX 9 AddrLib
 */
static const uint8_t kVAAddrLibInterfaceInitOriginal[] = {0x74, 0x00, 0x41, 0x81, 0xFC, 0x8D, 0x00, 0x00, 0x00, 0x75,
    0x00, 0xB8, 0x0D, 0x00, 0x00, 0x00};
static const uint8_t kVAAddrLibInterfaceInitOriginalMask[] = {0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t kVAAddrLibInterfaceInitPatched[] = {0x00, 0x00, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90,
    0x90, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t kVAAddrLibInterfaceInitPatchedMask[] = {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00};

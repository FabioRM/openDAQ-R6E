#include <r6e_bridge_module/r6e_bridge_module_impl.h>
#include <r6e_bridge_module/r6e_bridge_impl.h>
#include <r6e_bridge_module/wav_writer_fb_impl.h>
#include <r6e_bridge_module/version.h>
#include <coretypes/version_info_factory.h>
#include <miniaudio/miniaudio.h>
#include <opendaq/custom_log.h>

#ifdef _WIN32
#include <combaseapi.h>
#endif


BEGIN_NAMESPACE_R6E_BRIDGE_MODULE

R6eBridgeModule::R6eBridgeModule(const ContextPtr& context)
    : Module("Audio device module",
            daq::VersionInfo(R6E_BRIDGE_MODULE_MAJOR_VERSION, R6E_BRIDGE_MODULE_MINOR_VERSION, R6E_BRIDGE_MODULE_PATCH_VERSION),
            context,
            "AudioDevice")
    , maContext(std::make_shared<MiniaudioContext>())
    , deviceIndex(0)
{
}

ListPtr<IDeviceInfo> R6eBridgeModule::onGetAvailableDevices()
{
    ma_result result;
    ma_device_info* pCaptureDeviceInfos;
    ma_uint32 captureDeviceCount;

#ifdef MA_WIN32
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
#endif

    std::scoped_lock lock(sync);

    result = ma_context_get_devices(maContext->getPtr(), nullptr, nullptr, &pCaptureDeviceInfos, &captureDeviceCount);
    if (result != MA_SUCCESS)
    {
        LOG_W("Miniaudio get devices failed: {}", ma_result_description(result));
        throw GeneralErrorException("Failed to retrieve device information");
    }

    auto availableDevices = List<IDeviceInfo>();
    for (size_t i = 0; i < captureDeviceCount; i++)
    {
        auto info = AudioDeviceImpl::CreateDeviceInfo(maContext, pCaptureDeviceInfos[i]);
        availableDevices.pushBack(info);
    }

#ifdef MA_WIN32
    CoUninitialize();
#endif

    return availableDevices;
}

DictPtr<IString, IDeviceType> R6eBridgeModule::onGetAvailableDeviceTypes()
{
    auto result = Dict<IString, IDeviceType>();

    auto deviceType = AudioDeviceImpl::createType();
    result.set(deviceType.getId(), deviceType);

    return result;
}

DevicePtr R6eBridgeModule::onCreateDevice(const StringPtr& connectionString,
                                            const ComponentPtr& parent,
                                            const PropertyObjectPtr& /*config*/)
{
    auto id = AudioDeviceImpl::getIdFromConnectionString(connectionString);

    std::scoped_lock lock(sync);

    std::string localId = fmt::format("miniaudiodev{}", deviceIndex++);

    auto devicePtr = createWithImplementation<IDevice, AudioDeviceImpl>(maContext, id, context, parent, StringPtr(localId));
    return devicePtr;
}

bool R6eBridgeModule::onAcceptsConnectionParameters(const StringPtr& connectionString, const PropertyObjectPtr& /*config*/)
{
    LOG_T("Connection string: {}", connectionString);
    std::string connStr = connectionString;
    auto found = connStr.find("miniaudio://");
    return (found == 0);
}

DictPtr<IString, IFunctionBlockType> R6eBridgeModule::onGetAvailableFunctionBlockTypes()
{
    auto types = Dict<IString, IFunctionBlockType>();

    auto type = WAVWriterFbImpl::CreateType();
    types.set(type.getId(), type);

    return types;
}

FunctionBlockPtr R6eBridgeModule::onCreateFunctionBlock(const StringPtr& id, const ComponentPtr& parent, const StringPtr& localId, const PropertyObjectPtr& config)
{
    if (id == WAVWriterFbImpl::CreateType().getId())
    {
        FunctionBlockPtr fb = createWithImplementation<IFunctionBlock, WAVWriterFbImpl>(context, parent, localId);
        return fb;
    }

    LOG_W("Function block \"{}\" not found", id);
    throw NotFoundException("Function block not found");
}

END_NAMESPACE_R6E_BRIDGE_MODULE

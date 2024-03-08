#include <testutils/testutils.h>
#include <r6e_bridge_module/module_dll.h>
#include <r6e_bridge_module/version.h>
#include <gmock/gmock.h>
#include <opendaq/module_ptr.h>
#include <opendaq/device_ptr.h>
#include <coretypes/common.h>
#include <opendaq/context_factory.h>
#include <opendaq/scheduler_factory.h>

using R6eBridgeModuleTest = testing::Test;
using namespace daq;

static ModulePtr CreateModule()
{
    ModulePtr module;
    createModule(&module, NullContext());
    return module;
}

TEST_F(R6eBridgeModuleTest, CreateModule)
{
    IModule* module = nullptr;
    ErrCode errCode = createModule(&module, NullContext());
    ASSERT_TRUE(OPENDAQ_SUCCEEDED(errCode));

    ASSERT_NE(module, nullptr);
    module->releaseRef();
}

TEST_F(R6eBridgeModuleTest, ModuleName)
{
    auto module = CreateModule();
    ASSERT_EQ(module.getName(), "r6e bridge module");
}

TEST_F(R6eBridgeModuleTest, VersionAvailable)
{
    auto module = CreateModule();
    ASSERT_TRUE(module.getVersionInfo().assigned());
}

TEST_F(R6eBridgeModuleTest, VersionCorrect)
{
    auto module = CreateModule();
    auto version = module.getVersionInfo();

    ASSERT_EQ(version.getMajor(), R6E_BRIDGE_MODULE_MAJOR_VERSION);
    ASSERT_EQ(version.getMinor(), R6E_BRIDGE_MODULE_MINOR_VERSION);
    ASSERT_EQ(version.getPatch(), R6E_BRIDGE_MODULE_PATCH_VERSION);
}

TEST_F(R6eBridgeModuleTest, EnumerateDevices)
{
    auto module = CreateModule();

    ListPtr<IDeviceInfo> deviceInfo;
    ASSERT_NO_THROW(deviceInfo = module.getAvailableDevices());
}

TEST_F(R6eBridgeModuleTest, AcceptsConnectionStringNull)
{
    auto module = CreateModule();
    ASSERT_THROW(module.acceptsConnectionParameters(nullptr), ArgumentNullException);
}

TEST_F(R6eBridgeModuleTest, AcceptsConnectionStringEmpty)
{
    auto module = CreateModule();

    bool accepts = true;
    ASSERT_NO_THROW(accepts = module.acceptsConnectionParameters(""));
    ASSERT_FALSE(accepts);
}

TEST_F(R6eBridgeModuleTest, AcceptsConnectionStringInvalid)
{
    auto module = CreateModule();

    bool accepts = true;
    ASSERT_NO_THROW(accepts = module.acceptsConnectionParameters("drfrfgt"));
    ASSERT_FALSE(accepts);
}

TEST_F(R6eBridgeModuleTest, AcceptsConnectionStringCorrect)
{
    auto module = CreateModule();

    ASSERT_TRUE(module.acceptsConnectionParameters("miniaudio://wasapi/...."));
}

TEST_F(R6eBridgeModuleTest, CreateDeviceConnectionStringNull)
{
    auto module = CreateModule();

    DevicePtr device;
    ASSERT_THROW(device = module.createDevice(nullptr, nullptr), ArgumentNullException);
}

TEST_F(R6eBridgeModuleTest, CreateDeviceConnectionStringEmpty)
{
    auto module = CreateModule();

    ASSERT_THROW(module.createDevice("", nullptr), InvalidParameterException);
}

TEST_F(R6eBridgeModuleTest, CreateDeviceConnectionStringInvalid)
{
    auto module = CreateModule();

    ASSERT_THROW(module.createDevice("fdfdfdfdde", nullptr), InvalidParameterException);
}

TEST_F(R6eBridgeModuleTest, CreateDeviceConnectionStringInvalidId)
{
    auto module = CreateModule();

    ASSERT_THROW(module.createDevice("daqref://devicett3axxr1", nullptr), InvalidParameterException);
}

TEST_F(R6eBridgeModuleTest, CreateDeviceConnectionStringCorrect)
{
    auto module = CreateModule();

    auto deviceInfoList = module.getAvailableDevices();

    if (deviceInfoList.getCount() > 0)
    {
        auto connectionString = deviceInfoList[0].getConnectionString();
        std::cout << connectionString << std::endl;
        DevicePtr device;
        ASSERT_NO_THROW(device = module.createDevice(connectionString, nullptr));
    }
}

TEST_F(R6eBridgeModuleTest, GetAvailableComponentTypes)
{
    const auto module = CreateModule();

    DictPtr<IString, IFunctionBlockType> functionBlockTypes;
    ASSERT_NO_THROW(functionBlockTypes = module.getAvailableFunctionBlockTypes());
    ASSERT_EQ(functionBlockTypes.getCount(), 1u);
    ASSERT_TRUE(functionBlockTypes.hasKey("r6e_bridge_module_wav_writer"));
    ASSERT_EQ(functionBlockTypes.get("r6e_bridge_module_wav_writer").getId(), "r6e_bridge_module_wav_writer");

    DictPtr<IString, IDeviceType> deviceTypes;
    ASSERT_NO_THROW(deviceTypes = module.getAvailableDeviceTypes());
    ASSERT_EQ(deviceTypes.getCount(), 1u);
    ASSERT_TRUE(deviceTypes.hasKey("miniaudio"));
    ASSERT_EQ(deviceTypes.get("miniaudio").getId(), "miniaudio");

    DictPtr<IString, IServerType> serverTypes;
    ASSERT_NO_THROW(serverTypes = module.getAvailableServerTypes());
    ASSERT_EQ(serverTypes.getCount(), 0u);
}

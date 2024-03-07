#define MA_COINIT_VALUE COINIT_APARTMENTTHREADED
#define MA_NO_NODE_GRAPH
#define MA_NO_RESOURCE_MANAGER
#define MINIAUDIO_IMPLEMENTATION
#include <r6e_bridge_module/miniaudio_utils.h>

BEGIN_NAMESPACE_R6E_BRIDGE_MODULE

MiniaudioContext::MiniaudioContext()
{
    if (ma_context_init(nullptr, 0, nullptr, &context) != MA_SUCCESS)
        throw std::runtime_error("Failed to initialize miniaudio context");
}

MiniaudioContext::~MiniaudioContext()
{
    ma_context_uninit(&context);
}

ma_context* MiniaudioContext::getPtr()
{
    return &context;
}


END_NAMESPACE_R6E_BRIDGE_MODULE

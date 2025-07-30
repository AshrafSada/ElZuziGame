#include "d3d11.h"
#include "GameRenderSystem.h"
#include <stdexcept>

GameRenderSystem::GameRenderSystem( )
{
    // device flags
    UINT deviceFlags{ };

#ifdef _DEBUG
    // Creates a device that supports the debug layer. using bitwise OR operator
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

    // feature level
    D3D_FEATURE_LEVEL featureLevel{ };

    // create a directX11 device
    HRESULT hr = D3D11CreateDevice(
        NULL, // Use default adapter
        D3D_DRIVER_TYPE_HARDWARE,  // Use hardware driver acceleration
        NULL, // No software rasterizer
        deviceFlags, // No creation flags
        NULL, // Default feature levels
        0, // Number of feature levels
        D3D11_SDK_VERSION, // SDK version
        &m_d3dDevice, // Output device
        &featureLevel, // Output feature level
        &m_deviceContext // Output device context
    );

    if (hr <= 0)
    {
        std::ignore = std::runtime_error( "D3D Device creation failed!" );
    }

    // we need to query DXGI device interface
    m_d3dDevice->QueryInterface( IID_PPV_ARGS( &m_dxGIDevice ) );

    // we need to get parent of DXGI Adapter representing the GPU device
    m_dxGIDevice->GetParent( IID_PPV_ARGS( &m_dxGIAdapter ) );

    // we need to get parent of DXGI Factory representing DXI object
    m_dxGIAdapter->GetParent( IID_PPV_ARGS( &m_dxGIFactory ) );
}

GameRenderSystem::~GameRenderSystem( )
{ }

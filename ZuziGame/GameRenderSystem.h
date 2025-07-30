#pragma once

#include "GameBase.h"
#include <wrl.h>

class GameRenderSystem : public GameBase
{
public:
    GameRenderSystem( );
    virtual ~GameRenderSystem( ) override;

private:
    // high-level rendering device using Direct3D
    Microsoft::WRL::ComPtr< ID3D11Device> m_d3dDevice{ };
    // rendering device context
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext{ };
    // hardware device bound to GPU
    Microsoft::WRL::ComPtr<IDXGIDevice> m_dxGIDevice{ };
    // represents the GPU device available on the OS
    Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxGIAdapter{ };
    // An IDXGIFactory interface implements methods for generating DXGI objects (which handle full screen transitions).
    Microsoft::WRL::ComPtr<IDXGIFactory> m_dxGIFactory{ };
};

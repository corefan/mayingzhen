#include "VulkanRender/stdafx.h"
#include "VulkanRender/Module.h"


#include "VulkanRender/VulkanTexture.hxx"
#include "VulkanRender/VulkanVertexBuffer.hxx"
#include "VulkanRender/VulkanIndexBuffer.hxx"
#include "VulkanRender/VulkanMapping.hxx"
#include "VulkanRender/VulkanVertexDeclaration.hxx"
#include "VulkanRender/VulkanShaderProgram.hxx"
#include "VulkanRender/VulkanRenderDevice.hxx"
#include "VulkanRender/VulkanConstantBuffer.hxx"
#include "VulkanRender/VulkanRenderState.hxx"
#include "VulkanRender/VulkanSamplerState.hxx"

using namespace ma;


void VulkanRenderModuleInit()
{
	VulkanRenderDevice* pDxRenderDevice = new VulkanRenderDevice();
	SetRenderDevice(pDxRenderDevice);
}


void VulkanRenderModuleShutdown()
{
	VulkanRenderDevice* pDxRenderDevice = (VulkanRenderDevice*)GetRenderDevice();
	SAFE_DELETE(pDxRenderDevice);
	SetRenderDevice(NULL);
}


extern "C" VULKAN_API bool dllStartPlugin()
{
	VulkanRenderModuleInit();

	return true;
}


extern "C" VULKAN_API bool dllStopPlugin()
{
	VulkanRenderModuleShutdown();

	return true;
}
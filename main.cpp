#include <GLFW/glfw3.h>
#include <webgpu/webgpu_cpp.h>

#include <iostream>

const uint32_t kWidth = 512;
const uint32_t kHeight = 512;

wgpu::Instance instance;
wgpu::Adapter adapter;
wgpu::Device device;

void GetAdapter(void (*callback)(wgpu::Adapter)) {
  instance.RequestAdapter(
      nullptr,
      [](WGPURequestAdapterStatus status, WGPUAdapter cAdapter,
         WGPUStringView message, void* userdata) {
        if (status != WGPURequestAdapterStatus_Success) {
          exit(0);
        }
        wgpu::Adapter adapter = wgpu::Adapter::Acquire(cAdapter);
        reinterpret_cast<void (*)(wgpu::Adapter)>(userdata)(adapter);
      },
      reinterpret_cast<void*>(callback));
}

void GetDevice(void (*callback)(wgpu::Device)) {
  adapter.RequestDevice(
      nullptr,
      [](WGPURequestDeviceStatus status, WGPUDevice cDevice,
         WGPUStringView message, void* userdata) {
        wgpu::Device device = wgpu::Device::Acquire(cDevice);
        reinterpret_cast<void (*)(wgpu::Device)>(userdata)(device);
      },
      reinterpret_cast<void*>(callback));
}

void Start() {
  if (!glfwInit()) {
    return;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window =
      glfwCreateWindow(kWidth, kHeight, "WebGPU window", nullptr, nullptr);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

int main() {
  instance = wgpu::CreateInstance();
  GetAdapter([](wgpu::Adapter a) {
    adapter = a;
    GetDevice([](wgpu::Device d) {
      device = d;
      Start();
    });
  });

  return 0;
}

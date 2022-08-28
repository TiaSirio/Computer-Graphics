// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include <limits>
#include <algorithm>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

class Assignment14 {
public:
    void run() {
        initWindow();
        initVulkan();
        initApp();
        mainLoop();
        cleanup();
    }

private:
    // place all the application variables here. As an example, here the one for the GLFW Window
    // and the Vulkan instances are already defined.

    struct QueueFamilyIndices {
        std::optional<uint32_t> aQueueWithGraphicsCapability;
        std::optional<uint32_t> aQueueWithPresentationCapability;

        bool isComplete() {
            return aQueueWithGraphicsCapability.has_value() && aQueueWithPresentationCapability.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    GLFWwindow* window;
    VkInstance instance;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkResult result;
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    VkPhysicalDeviceMemoryProperties vpdmp;
    QueueFamilyIndices indicesDevice;
    VkDevice logicalDevice;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    SwapChainSupportDetails swapChainSupport;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 14", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createCommandPool();
        createCommandBuffer();
        // Continue with:
        // Prsentation Surface Creation - DONE
        // Physical Device selection - DONE
        // Logical Device creation - DONE
        // Command Pool creation - DONE
        // Command Buffer creation - DONE

        //****** New!
        // Swap chain creation - DONE
        // Image view creation - DONE
    }

    void createImageViews() {
        swapChainImageViews.resize(swapChainImages.size());
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = swapChainImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = swapChainImageFormat;
            viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;
            VkImageView imageView;
            result = vkCreateImageView(logicalDevice, &viewInfo, nullptr, &imageView);
            if (result != VK_SUCCESS) {
                throw std::runtime_error("failed to create image view!");
            }
            std::cout << "\n\tImageView " << i << " created!";
            swapChainImageViews[i] = imageView;
        }
    }

    void createSwapChain() {
        swapChainSupport = querySwapChainSupport(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR SCcreateInfo{};
        SCcreateInfo.sType =
            VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        SCcreateInfo.surface = surface;
        SCcreateInfo.minImageCount = imageCount;
        SCcreateInfo.imageFormat = surfaceFormat.format;
        SCcreateInfo.imageColorSpace = surfaceFormat.colorSpace;
        SCcreateInfo.imageExtent = extent;
        SCcreateInfo.imageArrayLayers = 1;
        SCcreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        uint32_t queueFamilyIndices[] = { indicesDevice.aQueueWithGraphicsCapability.value(), indicesDevice.aQueueWithPresentationCapability.value() };
        if (indicesDevice.aQueueWithGraphicsCapability !=
            indicesDevice.aQueueWithPresentationCapability) {
            SCcreateInfo.imageSharingMode =
                VK_SHARING_MODE_CONCURRENT;
            SCcreateInfo.queueFamilyIndexCount = 2;
            SCcreateInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            SCcreateInfo.imageSharingMode =
                VK_SHARING_MODE_EXCLUSIVE;
            SCcreateInfo.queueFamilyIndexCount = 0;
            SCcreateInfo.pQueueFamilyIndices = nullptr;
        }

        SCcreateInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        SCcreateInfo.compositeAlpha =
            VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        SCcreateInfo.presentMode = presentMode;
        SCcreateInfo.clipped = VK_TRUE;
        SCcreateInfo.oldSwapchain = VK_NULL_HANDLE;
        result = vkCreateSwapchainKHR(logicalDevice, &SCcreateInfo, nullptr, &swapChain);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }
        std::cout << "\n\tSwapChain created!";
        vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, swapChainImages.data());
        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        }
        else {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;
        uint32_t formatCount;
        uint32_t presentModeCount;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        std::cout << "Capabilities:\n";
        std::cout << "\tMin image count: " << details.capabilities.minImageCount << "\n";
        std::cout << "\tMax image count: " << details.capabilities.maxImageCount << "\n";
        //std::cout << "\tCurrent extent: " << details.capabilities.currentExtent << "\n";
        //std::cout << "\tMin image extent: " << details.capabilities.minImageExtent << "\n";
        //std::cout << "\Max image extent: " << details.capabilities.maxImageExtent << "\n";
        std::cout << "\tMax image array layers: " << details.capabilities.maxImageArrayLayers << "\n";
        std::cout << "\tSupported transforms: " << details.capabilities.supportedTransforms << "\n";
        std::cout << "\tCurrent transforms: " << details.capabilities.currentTransform << "\n";
        std::cout << "\tSupported composite alpha: " << details.capabilities.supportedCompositeAlpha << "\n";
        std::cout << "\tSupported usage flags: " << details.capabilities.supportedUsageFlags << "\n";

        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
            std::cout << "\n\t Supported Formats: " << formatCount << "\n";
            for (int i = 0; i < formatCount; i++) {
                std::cout << "\t\tFormat: " << details.formats[i].format <<
                    ", Color Space:" << details.formats[i].colorSpace << "\n";
            }
        }

        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());

            std::cout << "\t Supported Modes: " << presentModeCount << "\n";
            for (int i = 0; i < presentModeCount; i++) {
                switch (details.presentModes[i]) {
                case VK_PRESENT_MODE_IMMEDIATE_KHR:
                    std::cout << "\t\tVK_PRESENT_MODE_IMMEDIATE_KHR\n";
                    break;
                case VK_PRESENT_MODE_MAILBOX_KHR:
                    std::cout << "\t\tVK_PRESENT_MODE_MAILBOX_KHR\n";
                    break;
                case VK_PRESENT_MODE_FIFO_KHR:
                    std::cout << "\t\tVK_PRESENT_MODE_FIFO_KHR\n";
                    break;
                case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
                    std::cout << "\t\tVK_PRESENT_MODE_FIFO_RELAXED_KHR\n";
                    break;
                }
            }
        }

        return details;
    }

    void createCommandBuffer() {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;
        result = vkAllocateCommandBuffers(logicalDevice, &allocInfo, &commandBuffer);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffer!");
        }
    }

    void createCommandPool() {
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = indicesDevice.aQueueWithGraphicsCapability.value();
        poolInfo.flags = 0; // Optional
        result = vkCreateCommandPool(logicalDevice, &poolInfo, nullptr, &commandPool);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    void createLogicalDevice() {
        indicesDevice = findQueueFamilies(physicalDevice);
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {
            indicesDevice.aQueueWithGraphicsCapability.value(),
            indicesDevice.aQueueWithPresentationCapability.value()
        };
        float queuePriority = 1.0f;

        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();
        createInfo.enabledLayerCount = 0;
        result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(logicalDevice, indicesDevice.aQueueWithGraphicsCapability.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(logicalDevice, indicesDevice.aQueueWithPresentationCapability.value(), 0, &presentQueue);
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t queueFamCount = -1;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamCount, nullptr);

        std::vector<VkQueueFamilyProperties> queues(queueFamCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamCount, queues.data());


        for (unsigned int i = 0; i < queueFamCount; i++) {
            //std::cout << "\n\t\QqueueCount = " << queues[i].queueCount << "; ";
            if ((queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
                //std::cout << " Graphics";
                indices.aQueueWithGraphicsCapability = i;
            }
            if ((queues[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0) {
                //std::cout << " Compute";
            }
            if ((queues[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) {
                //std::cout << " Transfer";
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            if (presentSupport) {
                //std::cout << " Presentation";
                indices.aQueueWithPresentationCapability = i;
            }
        }
        return indices;
    }

    void pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        result = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (result != VK_SUCCESS || deviceCount <= 0) {
            throw std::runtime_error("Failed to find GPUs with Vulkan Support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        result = vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Could not enumerate devices");
        }
        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);

        //checkDeviceProperties(device);

        //checkDeviceFeatures(device);

        //checkDeviceMemoryProperties(device);

        bool swapChainAdequate = false;
        swapChainSupport = querySwapChainSupport(device);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

        return indices.isComplete() && swapChainAdequate;

        //Get first supporting both a graphic and a presentation queue.

        //return true;
    }

    void checkDeviceProperties(VkPhysicalDevice device) {
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        std::cout << "\tAPI version: 0x" << std::hex << deviceProperties.apiVersion << "\n";
        std::cout << "\tDriver version: 0x" << std::hex << deviceProperties.driverVersion << "\n";
        std::cout << "\tVendor ID: 0x" << std::hex << deviceProperties.vendorID << "\n";
        std::cout << "\tDevice ID: 0x" << std::hex << deviceProperties.deviceID << "\n";
        std::cout << "\tPhysical Device Type: " << deviceProperties.deviceType << "\t";
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            std::cout << " (Discrete GPU)\n";
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
            std::cout << " (Integrated GPU)\n";
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
            std::cout << " (Virtual GPU)\n";
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
            std::cout << " (CPU)\n";
        std::cout << "\tDevice Name: " << deviceProperties.deviceName << "\n";
    }

    void checkDeviceFeatures(VkPhysicalDevice device) {
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        std::cout << "\n\tPhysical Device Features:\n";
        std::cout << "\t\tgeometryShader = " << deviceFeatures.geometryShader << "\n";
        std::cout << "\t\ttessellationShader = " << deviceFeatures.tessellationShader << "\n";
        std::cout << "\t\tmultiDrawIndirect = " << deviceFeatures.multiDrawIndirect << "\n";
        std::cout << "\t\twideLines = " << deviceFeatures.wideLines << "\n";
        std::cout << "\t\tlargePoints = " << deviceFeatures.largePoints << "\n";
        std::cout << "\t\tmultiViewport = " << deviceFeatures.multiViewport << "\n";
        std::cout << "\t\tocclusionQueryPrecise = " << deviceFeatures.occlusionQueryPrecise << "\n";
        std::cout << "\t\tpipelineStatisticsQuery = " << deviceFeatures.pipelineStatisticsQuery << "\n";
        std::cout << "\t\tshaderFloat64 = " << deviceFeatures.shaderFloat64 << "\n";
        std::cout << "\t\tshaderInt64 = " << deviceFeatures.shaderInt64 << "\n";
        std::cout << "\t\tshaderInt16 = " << deviceFeatures.shaderInt16 << "\n";
    }

    void checkDeviceMemoryProperties(VkPhysicalDevice device) {
        vkGetPhysicalDeviceMemoryProperties(device, &vpdmp);
        std::cout << "\n\tMemory Types: " << vpdmp.memoryTypeCount << "\n";
        for (unsigned int i = 0; i < vpdmp.memoryTypeCount; i++) {
            VkMemoryType vmt = vpdmp.memoryTypes[i];
        }
        std::cout << "\n\tMemory Heaps: " << vpdmp.memoryHeapCount << "\n";
        for (unsigned int i = 0; i < vpdmp.memoryHeapCount; i++) {
            VkMemoryHeap vmh = vpdmp.memoryHeaps[i];
        }

        for (unsigned int i = 0; i < vpdmp.memoryTypeCount; i++) {
            VkMemoryType vmt = vpdmp.memoryTypes[i];
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) != 0)
                std::cout << " DeviceLocal";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0)
                std::cout << " HostVisible";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) != 0)
                std::cout << " HostCoherent";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) != 0)
                std::cout << " HostCached";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) != 0)
                std::cout << " LazilyAllocated";
            std::cout << "\n";
        }

        for (unsigned int i = 0; i < vpdmp.memoryHeapCount; i++) {
            VkMemoryHeap vmh = vpdmp.memoryHeaps[i];
            std::cout << " size = " << std::hex << (unsigned long int)vmh.size;
            if ((vmh.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) != 0)
                std::cout << " DeviceLocal";
            std::cout << "\n";
        }
    }

    void createSurface() {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void createInstance() {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        //std::cout << "My extensions:\n";
        /*for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }*/

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Assignment 12";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;
        result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }


    void initApp() {
        // This will not be needed in this assignment!
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyCommandPool(logicalDevice, commandPool, nullptr);
        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            vkDestroyImageView(logicalDevice, swapChainImageViews[i], nullptr);
        }
        vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr);
        vkDestroyDevice(logicalDevice, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    Assignment14 app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
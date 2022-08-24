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

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

class Assignment13 {
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

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 13", nullptr, nullptr);
    }

    void initVulkan() {
		createInstance();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createCommandPool();
        createCommandBuffer();
		// Continue with:
		// Prsentation Surface Creation - DONE
		// Physical Device selection - DONE
		// Logical Device creation - DONE
		// Command Pool creation - DONE
		// Command Buffer creation - DONE
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
        std::cout << "\n\n\tCommand buffer created! (" << commandBuffer << ")";
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
        std::cout << "\n\n\tCommand pool created! (" << commandPool << ")";
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
        createInfo.enabledExtensionCount = 0;
        createInfo.ppEnabledExtensionNames = nullptr;
        createInfo.enabledLayerCount = 0;
        result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice);
        
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }
        std::cout << "\n\n\tLogical device created! (" << logicalDevice << ")";
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
            std::cout << "\n\tQueueCount = " << queues[i].queueCount << "; ";
            if ((queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
                std::cout << " Graphics";
                indices.aQueueWithGraphicsCapability = i;
            }
            if ((queues[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0)
                std::cout << " Compute";
            if ((queues[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0)
                std::cout << " Transfer";
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            if (presentSupport) {
                std::cout << " Presentation";
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
                std::cout << "\n\n\tPhysical device chosen! (" << physicalDevice << ")";
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);
        
        checkDeviceProperties(device);

        checkDeviceFeatures(device);

        checkDeviceMemoryProperties(device);

        return indices.isComplete();

        //Get first supporting both a graphic and a presentation queue.

        //return true;
    }

    void checkDeviceProperties(VkPhysicalDevice device) {
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        std::cout << "\n\tAPI version: 0x" << std::hex << deviceProperties.apiVersion << "\n";
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
        std::cout << "\n\n\tMemory Types: " << vpdmp.memoryTypeCount << "\n";
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
        std::cout << "\n\n\tPresentation surface created! (" << surface << ")";
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
        vkDestroyDevice(logicalDevice, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    Assignment13 app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
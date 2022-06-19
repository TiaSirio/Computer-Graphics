// This has been adapted from the Vulkan tutorial

#include "MyProject.hpp"

namespace utils {
	struct DescriptorPoolSize {
		int numberOfUniformBlocksInPool;
		int numberOfTexturesInPool;
		int numberOfSetsInPool;

		DescriptorPoolSize() : numberOfUniformBlocksInPool(0), numberOfTexturesInPool(0), numberOfSetsInPool(0) {};

		void addObject() {
			numberOfTexturesInPool++;
			numberOfUniformBlocksInPool++;
			numberOfSetsInPool++;
		}

		void addMultipleInstanceObject(int numberOfInstances) {
			for (int i = 0; i < numberOfInstances; i++) {
				numberOfTexturesInPool++;
				numberOfUniformBlocksInPool++;
				numberOfSetsInPool++;
			}
		}

		void addDescriptorSet() {
			numberOfUniformBlocksInPool++;
			numberOfSetsInPool++;
		}
	};

	DescriptorPoolSize descriptorPoolSize;

	void addObject() {
		descriptorPoolSize.addObject();
	}

	void addMultipleInstanceObject(int numberOfInstances) {
		descriptorPoolSize.addMultipleInstanceObject(numberOfInstances);
	}

	void addDescriptor() {
		descriptorPoolSize.addDescriptorSet();
	}
};

const std::string MODEL_PATH = "models/viking_room.obj";
const std::string TEXTURE_PATH = "textures/viking_room.png";

struct globalUniformBufferObject {
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};

struct UniformBufferObject {
	alignas(16) glm::mat4 model;
};


struct DescriptorSetLayoutObject {
	DescriptorSetLayout descriptorSetLayout;
	std::vector<uint32_t> set;
	std::vector<VkDescriptorType> vkDescriptorType;
	std::vector<VkShaderStageFlagBits> vkShaderStageFlagBits;
	std::vector<DescriptorSetElementType> descriptorSetElementType;
	uint64_t sizeOfUniformBufferObject;
	uint64_t sizeOfGlobalUniformBufferObject;

	DescriptorSetLayoutObject(std::vector<uint32_t> set, std::vector<VkDescriptorType> vkDescriptorType, std::vector<VkShaderStageFlagBits> vkShaderStageFlagBits) {
		this->set = set;
		this->vkDescriptorType = vkDescriptorType;
		this->vkShaderStageFlagBits = vkShaderStageFlagBits;
		getCorrectDescriptorSetElementType();
		sizeOfUniformBufferObject = sizeof(UniformBufferObject);
		sizeOfGlobalUniformBufferObject = sizeof(globalUniformBufferObject);
	}

	void getCorrectDescriptorSetElementType() {
		this->descriptorSetElementType.resize(set.size());
		for (int i = 0; i < vkDescriptorType.size(); i++) {
			if (vkDescriptorType[i] == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER) {
				this->descriptorSetElementType[i] = UNIFORM;
			}
			else if (vkDescriptorType[i] == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER) {
				this->descriptorSetElementType[i] = TEXTURE;
			}
			else {
				this->descriptorSetElementType[i] = UNIFORM;
			}
		}
	}

	void cleanup() {
		descriptorSetLayout.cleanup();
	}
};



struct Object {
	Model model;
	Texture texture;
	DescriptorSet descriptorSet;

	Object() {
		utils::addObject();
	}

	void cleanup() {
		descriptorSet.cleanup();
		texture.cleanup();
		model.cleanup();
	}
};

struct MultipleObject {
	Model model;
	Texture texture;
	std::vector<DescriptorSet> descriptorSets;
	int numberOfinstances;

	MultipleObject(int numberOfInstances) {
		numberOfinstances = numberOfInstances;
		utils::addMultipleInstanceObject(numberOfInstances);
	}

	void cleanup() {
		for (DescriptorSet descriptorSet : descriptorSets) {
			descriptorSet.cleanup();
		}
		texture.cleanup();
		model.cleanup();
	}
};

// MAIN ! 
class MyProject : public BaseProject {
	protected:
	// Here you list all the Vulkan objects you need:

	std::vector<uint32_t> set = {0,1};
	std::vector<VkDescriptorType> vkDescriptorType = { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER };
	std::vector<VkShaderStageFlagBits> vkShaderStageFlagBits = { VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_FRAGMENT_BIT };

	DescriptorSetLayoutObject descriptorSetLayoutObject = DescriptorSetLayoutObject(set, vkDescriptorType, vkShaderStageFlagBits);

	std::vector<uint32_t> set2 = {0};
	std::vector<VkDescriptorType> vkDescriptorType2 = { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER };
	std::vector<VkShaderStageFlagBits> vkShaderStageFlagBits2 = { VK_SHADER_STAGE_ALL_GRAPHICS };

	DescriptorSetLayoutObject descriptorSetLayoutGlobal = DescriptorSetLayoutObject(set2, vkDescriptorType2, vkShaderStageFlagBits2);

	// Pipelines [Shader couples]
	Pipeline P1;

	// Models, textures and Descriptors (values assigned to the uniforms)
	Object bodyObject;
	
	Object handleObject;

	MultipleObject wheelObject = MultipleObject(3);

	DescriptorSet DS_global;

	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, title and initial background
		windowWidth = 800;//1920;
		windowHeight = 600;//1080;
		windowTitle = "My Project";
		initialBackgroundColor = {1.0f, 1.0f, 0.0f, 1.0f};

		//Done for DS_global
		utils::addDescriptor();

		// Descriptor pool sizes
		uniformBlocksInPool = utils::descriptorPoolSize.numberOfUniformBlocksInPool;
		texturesInPool = utils::descriptorPoolSize.numberOfTexturesInPool;
		setsInPool = utils::descriptorPoolSize.numberOfSetsInPool;
	}





	void descriptorSetLayoutInit(DescriptorSetLayoutObject* descriptorSetLayoutObject) {
		std::vector<DescriptorSetLayoutBinding> elementOfDSL;
		elementOfDSL.resize(descriptorSetLayoutObject->set.size());
		for (int i = 0; i < descriptorSetLayoutObject->set.size(); i++) {
			elementOfDSL[i].binding = descriptorSetLayoutObject->set[i];
			elementOfDSL[i].type = descriptorSetLayoutObject->vkDescriptorType[i];
			elementOfDSL[i].flags = descriptorSetLayoutObject->vkShaderStageFlagBits[i];
		}
		descriptorSetLayoutObject->descriptorSetLayout.init(this, {elementOfDSL});
	}
	
	uint64_t getSizeForObject(DescriptorSetElementType descriptorSetElementType, bool isAnObject) {
		if (descriptorSetElementType == TEXTURE) {
			return 0;
		}
		else if (isAnObject) {
			return sizeof(UniformBufferObject);
		}
		else {
			return sizeof(globalUniformBufferObject);
		}
	}

	Texture* getPointerOfTexture(DescriptorSetElementType descriptorSetElementType, Object* object) {
		if (descriptorSetElementType == TEXTURE) {
			return &object->texture;
		}
		else {
			return nullptr;
		}
	}

	void objectInit(Object *object, std::string modelPath, std::string texturePath, DescriptorSetLayout descriptorSetLayout, DescriptorSetLayoutObject descriptorSetLayoutObject) {
		object->model.init(this, modelPath);
		object->texture.init(this, texturePath);
		std::vector<DescriptorSetElement> descriptorSetElements;
		descriptorSetElements.resize(descriptorSetLayoutObject.set.size());
		for (int i = 0; i < descriptorSetLayoutObject.set.size(); i++) {
			descriptorSetElements[i].binding = descriptorSetLayoutObject.set[i];
			descriptorSetElements[i].type = descriptorSetLayoutObject.descriptorSetElementType[i];
			descriptorSetElements[i].size = getSizeForObject(descriptorSetLayoutObject.descriptorSetElementType[i], true);
			descriptorSetElements[i].tex = getPointerOfTexture(descriptorSetLayoutObject.descriptorSetElementType[i], object);
		}
		object->descriptorSet.init(this, &descriptorSetLayout, {descriptorSetElements});
	}

	Texture* getPointerOfTextureForMultipleObject(DescriptorSetElementType descriptorSetElementType, MultipleObject* object) {
		if (descriptorSetElementType == TEXTURE) {
			return &object->texture;
		}
		else {
			return nullptr;
		}
	}

	void multipleInstanceObjectInit(MultipleObject* object, std::string modelPath, std::string texturePath, DescriptorSetLayout descriptorSetLayout, int numberOfInstances, DescriptorSetLayoutObject descriptorSetLayoutObject) {
		object->model.init(this, modelPath);
		object->texture.init(this, texturePath);
		object->descriptorSets.resize(numberOfInstances);
		std::vector<DescriptorSetElement> descriptorSetElements;
		descriptorSetElements.resize(descriptorSetLayoutObject.set.size());
		for (int i = 0; i < descriptorSetLayoutObject.set.size(); i++) {
			descriptorSetElements[i].binding = descriptorSetLayoutObject.set[i];
			descriptorSetElements[i].type = descriptorSetLayoutObject.descriptorSetElementType[i];
			descriptorSetElements[i].size = getSizeForObject(descriptorSetLayoutObject.descriptorSetElementType[i], true);
			descriptorSetElements[i].tex = getPointerOfTextureForMultipleObject(descriptorSetLayoutObject.descriptorSetElementType[i], object);
		}
		for (int i = 0; i < numberOfInstances; i++) {
			object->descriptorSets[i].init(this, &descriptorSetLayout, {descriptorSetElements});
		}
	}

	void descriptorSetInit(DescriptorSet *descriptorSet, DescriptorSetLayout descriptorSetLayout, DescriptorSetLayoutObject descriptorSetLayoutObject) {
		std::vector<DescriptorSetElement> descriptorSetElements;
		descriptorSetElements.resize(descriptorSetLayoutObject.set.size());
		for (int i = 0; i < descriptorSetLayoutObject.set.size(); i++) {
			descriptorSetElements[i].binding = descriptorSetLayoutObject.set[i];
			descriptorSetElements[i].type = descriptorSetLayoutObject.descriptorSetElementType[i];
			descriptorSetElements[i].size = getSizeForObject(descriptorSetLayoutObject.descriptorSetElementType[i], false);
			descriptorSetElements[i].tex = nullptr;
		}
		descriptorSet->init(this, &descriptorSetLayout, {descriptorSetElements});
	}





	// Here you load and setup all your Vulkan objects
	void localInit() {

		descriptorSetLayoutInit(&descriptorSetLayoutObject);

		descriptorSetLayoutInit(&descriptorSetLayoutGlobal);

		localPipelineInit();

		objectInit(&bodyObject, "models/SlotBody.obj", "textures/SlotBody.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);

		objectInit(&handleObject, "models/SlotHandle.obj", "textures/SlotHandle.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);

		multipleInstanceObjectInit(&wheelObject, "models/SlotWheel.obj", "textures/SlotWheel.png", descriptorSetLayoutObject.descriptorSetLayout, 3, descriptorSetLayoutObject);

		descriptorSetInit(&DS_global, descriptorSetLayoutGlobal.descriptorSetLayout, descriptorSetLayoutGlobal);
	}

	void localPipelineInit() {
		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", { &descriptorSetLayoutGlobal.descriptorSetLayout, &descriptorSetLayoutObject.descriptorSetLayout });
	}





	void localPipelineCleanup() {
		//Here clean all the pipelines.
		P1.cleanup();
	}

	void descriptorLayoutsCleanup() {
		descriptorSetLayoutGlobal.cleanup();
		descriptorSetLayoutObject.cleanup();
	}

	void descriptorsCleanup() {
		DS_global.cleanup();
	}

	void objectsCleanup() {
		bodyObject.cleanup();
		handleObject.cleanup();
		wheelObject.cleanup();
	}
	
	// Here you destroy all the objects you created!		
	void localCleanup() {

		objectsCleanup();

		descriptorsCleanup();

		localPipelineCleanup();

		descriptorLayoutsCleanup();
	}
	




	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures
	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
		drawSingleInstanceInGlobal(commandBuffer, currentImage, P1, DS_global, 0);

		drawSingleInstance(commandBuffer, currentImage, P1, bodyObject, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, handleObject, 1);

		drawMultipleInstance(commandBuffer, currentImage, P1, wheelObject, 1);
	}





	void drawSingleInstanceInGlobal(VkCommandBuffer commandBuffer, int currentImage,
		Pipeline pipeline, DescriptorSet descriptorSet, int setUsed) {
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipeline.graphicsPipeline);
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipeline.pipelineLayout, setUsed, 1, &descriptorSet.descriptorSets[currentImage],
			0, nullptr);
	}

	void drawSingleInstance(VkCommandBuffer commandBuffer, int currentImage,
		Pipeline pipeline, Object object, int setUsed) {
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipeline.graphicsPipeline);

		VkBuffer vertexBuffers[] = { object.model.vertexBuffer };
		// property .vertexBuffer of models, contains the VkBuffer handle to its vertex buffer
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		// property .indexBuffer of models, contains the VkBuffer handle to its index buffer
		vkCmdBindIndexBuffer(commandBuffer, object.model.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);

		// property .pipelineLayout of a pipeline contains its layout.
		// property .descriptorSets of a descriptor set contains its elements.
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipeline.pipelineLayout, setUsed, 1, &object.descriptorSet.descriptorSets[currentImage],
			0, nullptr);

		// property .indices.size() of models, contains the number of triangles * 3 of the mesh.
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(object.model.indices.size()), 1, 0, 0, 0);
	}

	void drawMultipleInstance(VkCommandBuffer commandBuffer, int currentImage,
		Pipeline pipeline, MultipleObject object, int setUsed) {
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipeline.graphicsPipeline);

		VkBuffer vertexBuffers[] = { object.model.vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, object.model.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);

		for (int i = 0; i < object.descriptorSets.size(); i++) {
			vkCmdBindDescriptorSets(commandBuffer,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				pipeline.pipelineLayout, setUsed, 1, &object.descriptorSets[i].descriptorSets[currentImage],
				0, nullptr);

			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(object.model.indices.size()), 1, 0, 0, 0);
		}
	}





	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>
			(currentTime - startTime).count();
		static float lastTime = 0.0f;
		float deltaT = time - lastTime;

		static int state = 0;		// 0 - everything is still.
									// 3 - three wheels are turning
									// 2 - two wheels are turning
									// 1 - one wheels is turning

		static float debounce = time;
		static float ang1 = 0.0f;
		static float ang2 = 0.0f;
		static float ang3 = 0.0f;

		if (glfwGetKey(window, GLFW_KEY_SPACE)) {
			if (time - debounce > 0.33) {
				debounce = time;
				if (state == 0) {
					state = 3;
				}
				else {
					state--;
				}
			}
		}

		if (state == 3) {
			ang3 += deltaT;
		}
		if (state >= 2) {
			ang2 += deltaT;
		}
		if (state >= 1) {
			ang1 += deltaT;
		}


		globalUniformBufferObject gubo{};
		UniformBufferObject ubo{};


		void* data;
		gubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		gubo.proj = glm::perspective(glm::radians(45.0f),
			swapChainExtent.width / (float)swapChainExtent.height,
			0.1f, 10.0f);
		gubo.proj[1][1] *= -1;

		vkMapMemory(device, DS_global.uniformBuffersMemory[0][currentImage], 0,
			sizeof(gubo), 0, &data);
		memcpy(data, &gubo, sizeof(gubo));
		vkUnmapMemory(device, DS_global.uniformBuffersMemory[0][currentImage]);

		// For the Slot Body
		ubo.model = glm::mat4(1.0f);
		updateObject(bodyObject, ubo, currentImage);

		// For the Slot Handle
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, 0.5f, -0.15f));
		updateObject(handleObject, ubo, currentImage);

		// For the Slot Wheel1
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.15f, 0.93f, -0.15f)) *
			glm::rotate(glm::mat4(1.0f),
				ang1 * glm::radians(90.0f),
				glm::vec3(1.0f, 0.0f, 0.0f));
		updateOneInstanceOfObject(wheelObject, ubo, currentImage, 0);

		// For the Slot Wheel2
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.93f, -0.15f)) *
			glm::rotate(glm::mat4(1.0f),
				ang2 * glm::radians(90.0f),
				glm::vec3(1.0f, 0.0f, 0.0f));
		updateOneInstanceOfObject(wheelObject, ubo, currentImage, 1);

		// For the Slot Wheel3
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.15f, 0.93f, -0.15f)) *
			glm::rotate(glm::mat4(1.0f),
				ang3 * glm::radians(90.0f),
				glm::vec3(1.0f, 0.0f, 0.0f));
		updateOneInstanceOfObject(wheelObject, ubo, currentImage, 2);

		handleInputCommands();

	}





	void updateObject(Object object, UniformBufferObject ubo, uint32_t currentImage) {
		void* data;
		vkMapMemory(device, object.descriptorSet.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, object.descriptorSet.uniformBuffersMemory[0][currentImage]);
	}

	void updateOneInstanceOfObject(MultipleObject object, UniformBufferObject ubo, uint32_t currentImage, int descriptorSetInstance) {
		void* data;
		vkMapMemory(device, object.descriptorSets[descriptorSetInstance].uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, object.descriptorSets[descriptorSetInstance].uniformBuffersMemory[0][currentImage]);
	}

	void handleInputCommands() {
		
	}
};

// This is the main: probably you do not need to touch this!
int main() {
    MyProject app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
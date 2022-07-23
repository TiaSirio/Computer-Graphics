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

struct GlobalUniformBufferObject {
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
	alignas(16) glm::vec3 eyePos;
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
		sizeOfGlobalUniformBufferObject = sizeof(GlobalUniformBufferObject);
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

static float lookYaw = 0.0f;
static float lookPitch = 0.0f;
static float lookRoll = 0.0f;

std::vector<int> doorOpenOrNot = { 0,0,0,0,0 };
//Gold and Copper key
std::vector<int> doorCouldBeOpened = { 0,0 };
std::vector<int> leverCouldBeUsed = { 0,0,0 };
std::vector<int> leverUsedOrNot = { 0,0,0 };
std::vector<int> keyTakenOrNot = { 0,0 };

static bool win = false;
static bool jump = false;
static bool jumpDown = false;

int checkCorrectDoor(float x, float y, int pixDoorX, int pixDoorY) {
	if (pixDoorX == 4 && pixDoorY == 3) {
		//Lever door - third lever
		return doorOpenOrNot[0];
	}
	else if (pixDoorX == 7 && pixDoorY == 8) {
		//Copper key (last door)
		return doorOpenOrNot[1];
	}
	else if (pixDoorX == 9 && pixDoorY == 3) {
		//Lever door - second lever
		return doorOpenOrNot[2];
	}
	else if (pixDoorX == 4 && pixDoorY == -2) {
		//Lever door - first lever (first door)
		return doorOpenOrNot[3];
	} else {
		//Gold key door
		return doorOpenOrNot[4];
	}
	//x = 12; y = 4
}

stbi_uc* map;
int mapWidth, mapHeight;
bool canStepPoint(float x, float y) {
	int correctDoor;
	//Posso usare anche ceil() e floor()
	int roundX = round(x);
	int roundY = round(y);
	float roundFirstDecimalX = round(x * 10.0) / 10.0;
	float roundFirstDecimalY = round(y * 10.0) / 10.0;
	int pixX = round(fmax(0.0f, fmin(mapWidth - 1, (x + 16.9) * mapWidth / 33.8)));
	int pixY = round(fmax(0.0f, fmin(mapHeight - 1, (y + 16.9) * mapHeight / 33.8)));
	int pix = (int)map[mapWidth * pixY + pixX];
	//std::cout << pixX << " " << pixY << " " << x << " " << y << " \t P = " << pix << "\n";
	//std::cout << x << " " << y << "\n";
	if (roundFirstDecimalX == 10 && roundFirstDecimalY == -8 && keyTakenOrNot[0] == 0) {
		//GoldKey
		keyTakenOrNot[0] = 1;
	}
	if (roundX == 12 && (roundFirstDecimalY >= 3.7 && roundFirstDecimalY <= 3.9) && keyTakenOrNot[0] == 1 && doorOpenOrNot[4] == 0) {
		//GoldKey
		doorCouldBeOpened[0] = 1;
	}
	else {
		doorCouldBeOpened[0] = 0;
	}
	if (roundFirstDecimalX == 15 && roundFirstDecimalY == 3 && keyTakenOrNot[1] == 0) {
		//CopperKey
		keyTakenOrNot[1] = 1;
	}
	if (roundX == 7 && (roundFirstDecimalY >= 8.1 && roundFirstDecimalY <= 8.4) && keyTakenOrNot[1] == 1 && doorOpenOrNot[1] == 0) {
		//CopperKey
		doorCouldBeOpened[1] = 1;
	}
	else {
		doorCouldBeOpened[1] = 0;
	}
	//x = 3.3, y = 1.5
	if ((roundFirstDecimalX >= 3 && roundFirstDecimalX <= 3.3) && (roundFirstDecimalY >= -1.5 && roundFirstDecimalY <= -1.1) && leverUsedOrNot[2] == 0 && doorOpenOrNot[3] == 0) {
		//First lever
		leverCouldBeUsed[2] = 1;
	}
	else {
		leverCouldBeUsed[2] = 0;
	}
	//x = 8.3, y = 3.5
	if ((roundFirstDecimalX >= 8 && roundFirstDecimalX <= 8.2) && (roundFirstDecimalY >= 3.5 && roundFirstDecimalY <= 3.9) && leverUsedOrNot[1] == 0 && doorOpenOrNot[2] == 0) {
		//Second lever
		leverCouldBeUsed[1] = 1;
	}
	else {
		leverCouldBeUsed[1] = 0;
	}
	//x = 2.5, y = 2.2
	if ((roundFirstDecimalX >= 1.9 && roundFirstDecimalX <= 2.5) && (roundFirstDecimalY >= 1.9 && roundFirstDecimalY <= 2.2) && leverUsedOrNot[0] == 0 && doorOpenOrNot[0] == 0) {
		//Third lever
		leverCouldBeUsed[0] = 1;
	}
	else {
		leverCouldBeUsed[0] = 0;
	}
	if (pix > 200) {
		//Function to check the closest door and check if open or not
		correctDoor = checkCorrectDoor(x, y, roundX, roundY);
		return correctDoor == 1;
	}
	//If the last door is open
	if (doorOpenOrNot[1] == 1) {
		//Check final area and set win to true if arrived
		if ((roundX == 7 && roundY == 8) || (roundX == 8 && roundY == 8)) {
			win = true;
			return pix >= 0;
		}
	}
	return pix > 90;
}

const float checkRadius = 0.1;
const int checkSteps = 12;
bool canStep(float x, float y) {
	for (int i = 0; i < checkSteps; i++) {
		if (!canStepPoint(x + cos(6.2832 * i / (float)checkSteps) * checkRadius,
			y + sin(6.2832 * i / (float)checkSteps) * checkRadius)) {
			return false;
		}
	}
	return true;
}

const std::string MODEL_PATH = "models/";
const std::string TEXTURE_PATH = "textures/";
bool first = true;

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

	Object floorObject;
	Object ceilingObject;

	Object wallEastObject;
	Object wallNorthObject;
	Object wallWestObject;
	Object wallSouthObject;

	Object goldKeyObject;
	Object copperKeyObject;

	Object goldKeyHoleObject;
	Object copperKeyHoleObject;

	Object doorBorders;
	MultipleObject doors = MultipleObject(5);

	MultipleObject levers = MultipleObject(3);


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





	// Here you load and setup all your Vulkan objects
	void localInit() {

		descriptorSetLayoutInit(&descriptorSetLayoutObject);

		descriptorSetLayoutInit(&descriptorSetLayoutGlobal);

		localPipelineInit();

		//Floor and ceiling
		objectInit(&floorObject, MODEL_PATH + "FloorAndCeiling/Floor.obj", TEXTURE_PATH + "Floor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);
		objectInit(&ceilingObject, MODEL_PATH + "FloorAndCeiling/Ceiling.obj", TEXTURE_PATH + "Ceiling.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);

		//Walls
		objectInit(&wallEastObject, MODEL_PATH + "Wall/WallEast.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);
		objectInit(&wallNorthObject, MODEL_PATH + "Wall/WallNorth.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);
		objectInit(&wallSouthObject, MODEL_PATH + "Wall/WallSouth.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);
		objectInit(&wallWestObject, MODEL_PATH + "Wall//WallWest.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);
		
		//Gold key
		objectInit(&goldKeyObject, MODEL_PATH + "Key/GoldKey.obj", TEXTURE_PATH + "GoldKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);
		objectInit(&goldKeyHoleObject, MODEL_PATH + "KeyHole/GoldKeyHole.obj", TEXTURE_PATH + "GoldKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);

		//Copper key
		objectInit(&copperKeyObject, MODEL_PATH + "Key/CopperKey.obj", TEXTURE_PATH + "CopperKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);
		objectInit(&copperKeyHoleObject, MODEL_PATH + "KeyHole/CopperKeyHole.obj", TEXTURE_PATH + "CopperKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);

		//Doors
		objectInit(&doorBorders, MODEL_PATH + "Door/DoorsBorder.obj", TEXTURE_PATH + "DoorBorder.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject);
		multipleInstanceObjectInit(&doors, MODEL_PATH + "Door/Door.obj", TEXTURE_PATH + "Door.png", descriptorSetLayoutObject.descriptorSetLayout, 5, descriptorSetLayoutObject);

		//Levers
		multipleInstanceObjectInit(&levers, MODEL_PATH + "Lever/Lever.obj", TEXTURE_PATH + "Levers.png", descriptorSetLayoutObject.descriptorSetLayout, 3, descriptorSetLayoutObject);


		descriptorSetInit(&DS_global, descriptorSetLayoutGlobal.descriptorSetLayout, descriptorSetLayoutGlobal);

		map = stbi_load((TEXTURE_PATH + "displ.png").c_str(),
			&mapWidth, &mapHeight,
			NULL, 1);
		if (!map) {
			std::cout << (TEXTURE_PATH + "displ.png").c_str() << "\n";
			throw std::runtime_error("failed to load map image!");
		}
		std::cout << "map -> size: " << mapWidth
			<< "x" << mapHeight << "\n";
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
		floorObject.cleanup();
		ceilingObject.cleanup();

		wallEastObject.cleanup();
		wallNorthObject.cleanup();
		wallSouthObject.cleanup();
		wallWestObject.cleanup();

		goldKeyObject.cleanup();
		goldKeyHoleObject.cleanup();

		copperKeyObject.cleanup();
		copperKeyHoleObject.cleanup();

		doorBorders.cleanup();
		doors.cleanup();

		levers.cleanup();
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

		drawSingleInstance(commandBuffer, currentImage, P1, floorObject, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, ceilingObject, 1);

		drawSingleInstance(commandBuffer, currentImage, P1, wallEastObject, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, wallNorthObject, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, wallSouthObject, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, wallWestObject, 1);

		drawSingleInstance(commandBuffer, currentImage, P1, goldKeyObject, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, goldKeyHoleObject, 1);

		drawSingleInstance(commandBuffer, currentImage, P1, copperKeyObject, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, copperKeyHoleObject, 1);

		drawSingleInstance(commandBuffer, currentImage, P1, doorBorders, 1);

		drawMultipleInstance(commandBuffer, currentImage, P1, doors, 1);

		drawMultipleInstance(commandBuffer, currentImage, P1, levers, 1);
	}





	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		glm::mat4 CamMat = glm::mat4(1);
		glm::vec3 CamPos = glm::vec3(0);

		glm::mat4 CharacterPos = updateCameraPosition(window);
		//EyePos
		CamPos = glm::vec3(CharacterPos * glm::vec4(0, 0, 0, 1));


		GlobalUniformBufferObject gubo{};
		UniformBufferObject ubo{};


		void* data;
		gubo.view = CharacterPos;
		//gubo.view = CamMat;//glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//gubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);
		gubo.proj = glm::perspective(glm::radians(90.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 50.0f);
		gubo.proj[1][1] *= -1;
		gubo.eyePos = CamPos;

		vkMapMemory(device, DS_global.uniformBuffersMemory[0][currentImage], 0,
			sizeof(gubo), 0, &data);
		memcpy(data, &gubo, sizeof(gubo));
		vkUnmapMemory(device, DS_global.uniformBuffersMemory[0][currentImage]);




		//Floor and ceiling
		ubo.model = glm::mat4(1.0f);
		updateObject(floorObject, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(ceilingObject, ubo, currentImage);


		//Walls
		ubo.model = glm::mat4(1.0f);
		updateObject(wallEastObject, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(wallNorthObject, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(wallSouthObject, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(wallWestObject, ubo, currentImage);


		//Gold key
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, keyTakenOrNot[0] * 1.01f, 0)) * ubo.model;
		updateObject(goldKeyObject, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(goldKeyHoleObject, ubo, currentImage);

		//bool test = checkCollision(CamPos, goldKeyObject.model.vertices);

		//Copper key
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, keyTakenOrNot[1] * 1.01f, 0)) * ubo.model;
		updateObject(copperKeyObject, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(copperKeyHoleObject, ubo, currentImage);


		//Door borders
		ubo.model = glm::mat4(1.0f);
		updateObject(doorBorders, ubo, currentImage);

		//door1
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[0] * 1.01f, 0)) * ubo.model;
		updateOneInstanceOfObject(doors, ubo, currentImage, 0);
		ubo.model = glm::mat4(1.0f) * glm::translate(glm::mat4(1.0f), glm::vec3(3, 0, 5));
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[1] * 1.01f, 0)) * ubo.model;
		//ubo.model = glm::mat4(1.0f);
		updateOneInstanceOfObject(doors, ubo, currentImage, 1);
		ubo.model = glm::mat4(1.0f);
		//ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(5, 0, 0))) * ubo.model;
		//ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(5, 0, 0)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[2] * 1.01f, 0)) * ubo.model;
		updateOneInstanceOfObject(doors, ubo, currentImage, 2);
		ubo.model = glm::mat4(1.0f);
		//ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5))) * ubo.model;
		//ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[3] * 1.01f, 0)) * ubo.model;
		updateOneInstanceOfObject(doors, ubo, currentImage, 3);
		ubo.model = glm::mat4(1.0f);
		//ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(8, 0, 1))) * ubo.model;
		//ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		//ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(8, 0, 0)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(8, 0, 1)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[4] * 1.01f, 0)) * ubo.model;
		updateOneInstanceOfObject(doors, ubo, currentImage, 4);

		//door2
		/*ubo.model = glm::mat4(1.0f);
		updateOneInstanceOfObject(doors, ubo, currentImage, 0);
		ubo.model = glm::mat4(1.0f) * glm::translate(glm::mat4(1.0f), glm::vec3(-3, 0, -5));
		updateOneInstanceOfObject(doors, ubo, currentImage, 1);
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(2, 0, -5))) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(2, 0, -5)) * ubo.model;
		updateOneInstanceOfObject(doors, ubo, currentImage, 2);
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5))) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5)) * ubo.model;
		updateOneInstanceOfObject(doors, ubo, currentImage, 3);
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(8, 0, -1))) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		//ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(8, 0, 0)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(8, 0, -1)) * ubo.model;
		updateOneInstanceOfObject(doors, ubo, currentImage, 4);*/

		//Levers
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::rotate(glm::mat4(1.0f), leverUsedOrNot[0] * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * ubo.model;
		updateOneInstanceOfObject(levers, ubo, currentImage, 0);
		ubo.model = glm::mat4(1.0f);
		//ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(5.8f, 0, 1.3f))) * ubo.model;
		//ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		//ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(5.8f, 0, 1.3f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(5.8f, 0, 1.3f)) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), leverUsedOrNot[1] * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * ubo.model;
		updateOneInstanceOfObject(levers, ubo, currentImage, 1);
		ubo.model = glm::mat4(1.0f);
		//ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0, -3.7f))) * ubo.model;
		//ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		//ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0, -3.7f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0, -3.7f)) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), leverUsedOrNot[2] * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * ubo.model;
		updateOneInstanceOfObject(levers, ubo, currentImage, 2);

		//bool test = checkCollision(CamPos, levers..model.vertices);
		//std::cout << test;
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
			return sizeof(GlobalUniformBufferObject);
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
		/*for (int i = 0; i < 1000; i++) {
			std::cout << descriptorSetLayoutObject.set.size();
		}*/
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

	glm::mat4 updateCameraPosition(GLFWwindow* window) {
		static glm::vec3 pos = glm::vec3(0.0f, 0.4f, 0.0f);
		if (first) {
			first = false;
			lookYaw += glm::radians(-45.0f);
		}
		static glm::vec3 size = glm::vec3(1, 1, 1);
		glm::vec3 ux = glm::vec3(1, 0, 0);
		glm::vec3 uy = glm::vec3(0, 1, 0);
		glm::vec3 uz = glm::vec3(0, 0, 1);
		static glm::quat quat = glm::quat(glm::vec3(0, 0, 0));
		static glm::mat4 quatMatrix = glm::mat4(quat);

		const float ROT_SPEED = glm::radians(90.0f);//glm::radians(60.0f);
		const float MOVE_SPEED = 2.0f;//0.75f;
		const float MOUSE_RES = 500.0f;

		static auto startTime = std::chrono::high_resolution_clock::now();
		static float lastTime = 0.0f;
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
		float deltaT = time - lastTime;
		lastTime = time;

		glm::vec3 oldPos = pos;


		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			lookYaw += deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			lookYaw -= deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) && lookPitch < 1) {
			lookPitch += deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) && lookPitch > -1) {
			lookPitch -= deltaT * ROT_SPEED;
		}


		glm::mat3 CamDir = glm::mat3(glm::rotate(glm::mat4(1.0f), lookYaw, glm::vec3(0.0f, 1.0f, 0.0f))) *
			glm::mat3(glm::rotate(glm::mat4(1.0f), lookPitch, glm::vec3(1.0f, 0.0f, 0.0f)));



		if (glfwGetKey(window, GLFW_KEY_A)) {
			pos -= MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(1, 0, 0, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			pos += MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(1, 0, 0, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			pos -= MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0, 0, 1, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			pos += MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0, 0, 1, 1)) * deltaT;
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) && !jump) {
			//pos += MOVE_SPEED * glm::vec3(0, 0.1f, 0) * deltaT;
			jump = true;
		}
		/*if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && pos.y >= 0.4) {
			pos -= MOVE_SPEED * glm::vec3(0, 1, 0) * deltaT;
		}*/

		if (pos.y < 0.4f)
		{
			pos.y = 0.4f;
			jump = false;
			jumpDown = false;
		}

		if (pos.y >= 0.9) {
			jumpDown = true;
		}

		if (jump) {
			if (pos.y <= 0.9 && !jumpDown) {
				pos += MOVE_SPEED * glm::vec3(0, 0.7f, 0) * deltaT;
			}
			else {
				pos -= MOVE_SPEED * glm::vec3(0, 0.7f, 0) * deltaT;
			}
		}

		//Slow down respective axes
		/*playerVelX *= exp(-friction * dt); // playerVelX *= (1 - friction * dt) for small dt
		playerVelY -= gravity * dt;*/

		if (!canStep(pos.x, pos.z)) {
			pos = oldPos;
		}

		openTheDoor();
		
		glm::mat4 out =
			glm::transpose(glm::mat4(CamDir)) *
			glm::translate(glm::mat4(1.0), -pos);
		return out;
	}

	void openTheDoor() {
		if (leverCouldBeUsed[2] == 1 && leverUsedOrNot[2] == 0) {
			if (glfwGetKey(window, GLFW_KEY_E)) {
				doorOpenOrNot[3] = 1;
				leverUsedOrNot[2] = 1;
			}
		}

		if (leverCouldBeUsed[1] == 1 && leverUsedOrNot[1] == 0) {
			if (glfwGetKey(window, GLFW_KEY_E)) {
				doorOpenOrNot[2] = 1;
				leverUsedOrNot[1] = 1;
			}
		}

		if (leverCouldBeUsed[0] == 1 && leverUsedOrNot[0] == 0) {
			if (glfwGetKey(window, GLFW_KEY_E)) {
				doorOpenOrNot[0] = 1;
				leverUsedOrNot[0] = 1;
			}
		}

		if (doorCouldBeOpened[0] == 1 && doorOpenOrNot[4] == 0) {
			if (glfwGetKey(window, GLFW_KEY_E)) {
				doorOpenOrNot[4] = 1;
			}
		}

		if (doorCouldBeOpened[1] == 1 && doorOpenOrNot[1] == 0) {
			if (glfwGetKey(window, GLFW_KEY_E)) {
				doorOpenOrNot[1] = 1;
			}
		}
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
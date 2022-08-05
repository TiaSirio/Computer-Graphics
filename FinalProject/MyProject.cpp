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
	alignas(16) glm::vec3 torchPos;
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

//Player
//static glm::vec3 pos = glm::vec3(0.0f, 0.5f, 0.0f);
static glm::vec3 pos = glm::vec3(500.0f, 199.5f, -495.0f);
static glm::vec3 oldPos = glm::vec3(500.0f, 199.5f, -495.0f);
static glm::vec3 savePos = glm::vec3(0);
//static float lookYaw = glm::radians(-45.0f);
static float lookYaw = 0.0f;
static float lookYawSaved = 0.0f;
static float lookPitch = 0.0f;
static float lookPitchSaved = 0.0f;
static float lookRoll = 0.0f;

static bool win = false;
static bool jump = false;
static bool jumpDown = false;

static glm::vec3 CamPos = glm::vec3(0);
static glm::mat3 CamDir = glm::mat3(0);
static glm::mat4 CharacterPos = glm::mat4(0);

int controllerPlugged = 0;

//Environment
static std::vector<int> doorOpenOrNot = { 0,0,0,0,0 };
static std::vector<int> userCouldPassThroughDoors = { 0,0,0,0,0 };
//Gold and Copper key
static std::vector<int> doorCouldBeOpened = { 0,0 };
static std::vector<int> leverCouldBeUsed = { 0,0,0 };
static std::vector<int> leverUsedOrNot = { 0,0,0 };
static std::vector<int> keyTakenOrNot = { 0,0 };
static float powerUpTakenOrNot = 0.0f;

static int rotatingPowerUp = 0;
static std::vector<float> slowlyOpenDoors = { 0.0f,0.0f,0.0f,0.0f,0.0f };

static glm::vec3 torchPos = glm::vec3(0.0f, 0.8f, -4.42f);
static glm::vec3 torchPosStatic = glm::vec3(0.0f, 0.8f, -4.42f);
static bool torchCouldBeTaken = false;
static bool torchTaken = false;


//Game input
static bool showTutorial = true;
/*const char* keyW;
const char* keyA;
const char* keyS;
const char* keyD;

const char* keyUp;
const char* keyDown;
const char* keyLeft;
const char* keyRight;

const char* keyE;
const char* keyP;
const char* keyT;

const char* keyF11;*/

static bool stateF11 = false;
static bool firstF11 = true;


//Controller
int axesCount;
const float* axes;

int buttonCount;
const unsigned char* buttons;

//Tutorial
static std::vector<int> tutorialElements = { 0,1,1,1,1,1,1 };
static std::vector<int> tutorialNextElements = { 0,1 };
static bool stateTutorial = false;
static bool firstTutorial = true;

static bool stateTutorialAgain = false;
static bool firstTutorialAgain = true;

static bool doneTutorialAgain = false;
static bool restartTutorialWithinIt = false;

static bool firstTimeDoingTheTutorial = true;

int checkCorrectDoor(float x, float y, int pixDoorX, int pixDoorY) {
	if (pixDoorX == 4 && pixDoorY == 3) {
		//Lever door - third lever
		//return doorOpenOrNot[0];
		return userCouldPassThroughDoors[0];
	}
	else if (pixDoorX == 7 && pixDoorY == 8) {
		//Copper key (last door)
		//return doorOpenOrNot[1];
		return userCouldPassThroughDoors[1];
	}
	else if (pixDoorX == 9 && pixDoorY == 3) {
		//Lever door - second lever
		//return doorOpenOrNot[2];
		return userCouldPassThroughDoors[2];
	}
	else if (pixDoorX == 4 && pixDoorY == -2) {
		//Lever door - first lever (first door)
		//return doorOpenOrNot[3];
		return userCouldPassThroughDoors[3];
	} else {
		//Gold key door
		//return doorOpenOrNot[4];
		return userCouldPassThroughDoors[4];
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
	//std::cout << pixX << " " << pixY << '\n';
	//std::cout << pixX << " " << pixY << " " << x << " " << y << " \t P = " << pix << "\n";
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
	if ((roundFirstDecimalX >= 6.4 && roundFirstDecimalX <= 7) && roundY == 8 && keyTakenOrNot[1] == 1 && doorOpenOrNot[1] == 0) {
		//CopperKey
		doorCouldBeOpened[1] = 1;
	}
	else {
		doorCouldBeOpened[1] = 0;
	}
	//x = 3.3, y = -1.5
	if ((roundFirstDecimalX >= 3 && roundFirstDecimalX <= 3.6) && (roundFirstDecimalY >= -1.5 && roundFirstDecimalY <= -1.1) && leverUsedOrNot[2] == 0 && doorOpenOrNot[3] == 0) {
		//First lever
		leverCouldBeUsed[2] = 1;
	}
	else {
		leverCouldBeUsed[2] = 0;
	}
	//x = 8.3, y = 3.5
	if ((roundFirstDecimalX >= 8.0 && roundFirstDecimalX <= 8.6) && (roundFirstDecimalY >= 3.5 && roundFirstDecimalY <= 3.9) && leverUsedOrNot[1] == 0 && doorOpenOrNot[2] == 0) {
		//Second lever
		leverCouldBeUsed[1] = 1;
	}
	else {
		leverCouldBeUsed[1] = 0;
	}
	//x = 2.5, y = 2.2
	if ((roundFirstDecimalX >= 1.9 && roundFirstDecimalX <= 2.5) && (roundFirstDecimalY >= 1.9 && roundFirstDecimalY <= 2.5) && leverUsedOrNot[0] == 0 && doorOpenOrNot[0] == 0) {
		//Third lever
		leverCouldBeUsed[0] = 1;
	}
	else {
		leverCouldBeUsed[0] = 0;
	}
	//x = -4.0, y = 12.0
	if ((roundFirstDecimalX >= -4.2 && roundFirstDecimalX <= -3.8) && (roundFirstDecimalY >= 11.8 && roundFirstDecimalY <= 12.2) && powerUpTakenOrNot == 0.0f) {
		powerUpTakenOrNot = 0.8f;
	}
	if (roundX == 0 && (roundFirstDecimalY >= -4.5 && roundFirstDecimalY <= -4.1)) {
		torchCouldBeTaken = true;
	}
	else {
		torchCouldBeTaken = false;
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
			if ((roundFirstDecimalX >= 8 && roundFirstDecimalX <= 9) && roundY == 8) {
				win = true;
			}
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

	Object powerUp;
	Object powerUpBase;

	//Object winningRoom;
	//Object winningRoomCeiling;
	//Object winningRoomFloor;

	Object torch;

	Object tutorial;
	Object interaction;
	Object movement;
	Object visual;
	Object windowTutorial;
	Object restart;
	Object tutorialAgain;
	Object next;
	Object end;

	//Controller
	Object interactionController;
	Object movementController;
	Object visualController;
	Object restartController;
	Object tutorialAgainController;
	Object nextController;
	Object endController;

	DescriptorSet DS_global;

	//Texts
	/*Pipeline P2;

	std::vector<uint32_t> set3 = { 0,1 };
	std::vector<VkDescriptorType> vkDescriptorType3 = { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER };
	std::vector<VkShaderStageFlagBits> vkShaderStageFlagBits3 = { VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_FRAGMENT_BIT };

	DescriptorSetLayoutObject descriptorSetLayoutText = DescriptorSetLayoutObject(set3, vkDescriptorType3, vkShaderStageFlagBits3);
	
	DescriptorSet DS_text;*/


	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, title and initial background
		windowWidth = 800;//1920;
		windowHeight = 600;//1080;
		windowTitle = "Labyrinth game";
		//initialBackgroundColor = {1.0f, 1.0f, 0.0f, 1.0f};
		initialBackgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };

		//Done for DS_global
		utils::addDescriptor();

		// Descriptor pool sizes
		uniformBlocksInPool = utils::descriptorPoolSize.numberOfUniformBlocksInPool;
		texturesInPool = utils::descriptorPoolSize.numberOfTexturesInPool;
		setsInPool = utils::descriptorPoolSize.numberOfSetsInPool;
	}

	void showTutorialInfo() {
		/*keyW = glfwGetKeyName(GLFW_KEY_W, 0);
		keyA = glfwGetKeyName(GLFW_KEY_A, 0);
		keyS = glfwGetKeyName(GLFW_KEY_S, 0);
		keyD = glfwGetKeyName(GLFW_KEY_D, 0);

		keyUp = glfwGetKeyName(GLFW_KEY_UP, 0);
		keyDown = glfwGetKeyName(GLFW_KEY_DOWN, 0);
		keyLeft = glfwGetKeyName(GLFW_KEY_LEFT, 0);
		keyRight = glfwGetKeyName(GLFW_KEY_RIGHT, 0);

		keyE = glfwGetKeyName(GLFW_KEY_E, 0);
		keyP = glfwGetKeyName(GLFW_KEY_P, 0);
		keyT = glfwGetKeyName(GLFW_KEY_T, 0);
		
		keyF11 = glfwGetKeyName(GLFW_KEY_F11, 0);

		std::cout << "\nTutorial:\n";
		std::cout << "\nMovement keys:" << "\n\t Move left: " << keyA << "\n\t Move right: " << keyD << "\n\t Move forward: " << keyW << "\n\t Move backward: " << keyS;
		std::cout << "\nVisual keys:" << "\n\t Look left: " << keyLeft << "\n\t Look right: " << keyRight << "\n\t Look forward: " << keyUp << "\n\t Look backward: " << keyDown;
		std::cout << "\nWindow keys:" << "\n\t FullScreen on and off: " << keyF11;
		std::cout << "\nOther keys:" << "\n\t Interact with object: " << keyE << "\n\t Restart game when ended: " << keyP << "\n\t See again the tutorial: " << keyT;*/

		std::cout << "\nTutorial:";
		std::cout << "\nMovement keys:" << "\n\t Move left: A" << "\n\t Move right: D" << "\n\t Move forward: W" << "\n\t Move backward: S";
		std::cout << "\nVisual keys:" << "\n\t Look left: Left" << "\n\t Look right: Right" << "\n\t Look forward: Top" << "\n\t Look backward: Bottom";
		std::cout << "\nWindow keys:" << "\n\t FullScreen on and off: F11";
		std::cout << "\nOther keys:" << "\n\t Interact with object: E" << "\n\t Restart game when ended: P" << "\n\t See again the tutorial: T\n";
	}

	// Here you load and setup all your Vulkan objects
	void localInit() {

		descriptorSetLayoutInit(&descriptorSetLayoutObject);

		descriptorSetLayoutInit(&descriptorSetLayoutGlobal);

		//descriptorSetLayoutInit(&descriptorSetLayoutText);

		localPipelineInit();

		//Floor and ceiling
		objectInit(&floorObject, MODEL_PATH + "FloorAndCeiling/Floor.obj", TEXTURE_PATH + "Floor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&ceilingObject, MODEL_PATH + "FloorAndCeiling/Ceiling.obj", TEXTURE_PATH + "Ceiling.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);

		//Walls
		objectInit(&wallEastObject, MODEL_PATH + "Wall/WallEast.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&wallNorthObject, MODEL_PATH + "Wall/WallNorth.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&wallSouthObject, MODEL_PATH + "Wall/WallSouth.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&wallWestObject, MODEL_PATH + "Wall//WallWest.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		
		//Gold key
		objectInit(&goldKeyObject, MODEL_PATH + "Key/GoldKey.obj", TEXTURE_PATH + "GoldKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&goldKeyHoleObject, MODEL_PATH + "KeyHole/GoldKeyHole.obj", TEXTURE_PATH + "GoldKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);

		//Copper key
		objectInit(&copperKeyObject, MODEL_PATH + "Key/CopperKey.obj", TEXTURE_PATH + "CopperKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&copperKeyHoleObject, MODEL_PATH + "KeyHole/CopperKeyHole.obj", TEXTURE_PATH + "CopperKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);

		//Doors
		objectInit(&doorBorders, MODEL_PATH + "Door/DoorsBorder.obj", TEXTURE_PATH + "DoorBorder.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		multipleInstanceObjectInit(&doors, MODEL_PATH + "Door/Door.obj", TEXTURE_PATH + "Door.png", descriptorSetLayoutObject.descriptorSetLayout, 5, descriptorSetLayoutObject, false);

		//Levers
		multipleInstanceObjectInit(&levers, MODEL_PATH + "Lever/Lever.obj", TEXTURE_PATH + "Levers.png", descriptorSetLayoutObject.descriptorSetLayout, 3, descriptorSetLayoutObject, false);

		//Power up
		objectInit(&powerUp, MODEL_PATH + "PowerUp/PowerUp.obj", TEXTURE_PATH + "GoldKeyColor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&powerUpBase, MODEL_PATH + "PowerUp/PowerUpBase.obj", TEXTURE_PATH + "Ceiling.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);

		//Winning room
		//objectInit(&winningRoom, MODEL_PATH + "WinningRoom/WinningRoom.obj", TEXTURE_PATH + "Walls.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		//objectInit(&winningRoomCeiling, MODEL_PATH + "WinningRoom/WinningRoomCeiling.obj", TEXTURE_PATH + "Ceiling.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		//objectInit(&winningRoomFloor, MODEL_PATH + "WinningRoom/WinningRoomFloor.obj", TEXTURE_PATH + "Floor.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);

		//Torch
		objectInit(&torch, MODEL_PATH + "Torch/Torch.obj", TEXTURE_PATH + "Torch.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);

		//Tutorial
		objectInit(&tutorial, MODEL_PATH + "Tutorial/Tutorial.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&interaction, MODEL_PATH + "Tutorial/Interaction.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&movement, MODEL_PATH + "Tutorial/Movement.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&visual, MODEL_PATH + "Tutorial/Visual.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&windowTutorial, MODEL_PATH + "Tutorial/Window.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&restart, MODEL_PATH + "Tutorial/Restart.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&tutorialAgain, MODEL_PATH + "Tutorial/TutorialAgain.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&next, MODEL_PATH + "Tutorial/Next.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&end, MODEL_PATH + "Tutorial/End.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);

		//Tutorial controller
		objectInit(&interactionController, MODEL_PATH + "Tutorial/InteractionController.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&movementController, MODEL_PATH + "Tutorial/MovementController.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&visualController, MODEL_PATH + "Tutorial/VisualController.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&restartController, MODEL_PATH + "Tutorial/RestartController.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&tutorialAgainController, MODEL_PATH + "Tutorial/TutorialAgainController.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&nextController, MODEL_PATH + "Tutorial/NextController.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);
		objectInit(&endController, MODEL_PATH + "Tutorial/EndController.obj", TEXTURE_PATH + "Tutorial.png", descriptorSetLayoutObject.descriptorSetLayout, descriptorSetLayoutObject, false);

		descriptorSetInit(&DS_global, descriptorSetLayoutGlobal.descriptorSetLayout, descriptorSetLayoutGlobal);

		//descriptorSetInit(&DS_text, descriptorSetLayoutText.descriptorSetLayout, descriptorSetLayoutText);

		map = stbi_load((TEXTURE_PATH + "displ.png").c_str(),
			&mapWidth, &mapHeight,
			NULL, 1);
		if (!map) {
			std::cout << (TEXTURE_PATH + "displ.png").c_str() << "\n";
			throw std::runtime_error("failed to load map image!");
		}
		std::cout << "map -> size: " << mapWidth
			<< "x" << mapHeight << "\n";

		showTutorialInfo();
	}

	void localPipelineInit() {
		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", { &descriptorSetLayoutGlobal.descriptorSetLayout, &descriptorSetLayoutObject.descriptorSetLayout }, false);
		//P2.init(this, "shaders/textVert.spv", "shaders/textFrag.spv", { &descriptorSetLayoutText.descriptorSetLayout }, true);
	}





	void localPipelineCleanup() {
		//Here clean all the pipelines.
		P1.cleanup();
		//P2.cleanup();
	}

	void descriptorLayoutsCleanup() {
		descriptorSetLayoutGlobal.cleanup();
		descriptorSetLayoutObject.cleanup();
		//descriptorSetLayoutText.cleanup();
	}

	void descriptorsCleanup() {
		DS_global.cleanup();
	}

	void objectsCleanup() {
		floorObject.cleanup();
		ceilingObject.cleanup();

		powerUp.cleanup();
		powerUpBase.cleanup();

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

		//winningRoom.cleanup();
		//winningRoomCeiling.cleanup();
		//winningRoomFloor.cleanup();

		torch.cleanup();

		tutorial.cleanup();
		interaction.cleanup();
		movement.cleanup();
		visual.cleanup();
		windowTutorial.cleanup();
		restart.cleanup();
		tutorialAgain.cleanup();
		next.cleanup();
		end.cleanup();

		interactionController.cleanup();
		movementController.cleanup();
		visualController.cleanup();
		restartController.cleanup();
		tutorialAgainController.cleanup();
		nextController.cleanup();
		endController.cleanup();
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

		drawSingleInstance(commandBuffer, currentImage, P1, powerUp, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, powerUpBase, 1);

		//drawSingleInstance(commandBuffer, currentImage, P1, winningRoom, 1);
		//drawSingleInstance(commandBuffer, currentImage, P1, winningRoomCeiling, 1);
		//drawSingleInstance(commandBuffer, currentImage, P1, winningRoomFloor, 1);

		drawSingleInstance(commandBuffer, currentImage, P1, torch, 1);

		drawSingleInstance(commandBuffer, currentImage, P1, tutorial, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, interaction, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, movement, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, visual, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, windowTutorial, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, restart, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, tutorialAgain, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, next, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, end, 1);

		drawSingleInstance(commandBuffer, currentImage, P1, interactionController, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, movementController, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, visualController, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, restartController, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, tutorialAgainController, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, nextController, 1);
		drawSingleInstance(commandBuffer, currentImage, P1, endController, 1);
	}





	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		if (firstTimeDoingTheTutorial || doneTutorialAgain) {
			manageTutorial();
		}

		seeTutorialAgain();

		restartTheGame();

		CharacterPos = updateCameraPosition(window);
		
		updateWindow();
		
		interctWithObjects();

		checkWinning();
		
		GlobalUniformBufferObject gubo{};
		UniformBufferObject ubo{};

		void* data;
		gubo.view = CharacterPos;
		gubo.proj = glm::perspective(glm::radians(90.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 50.0f);
		gubo.proj[1][1] *= -1;
		if (doneTutorialAgain) {
			gubo.torchPos = torchPosStatic;
		}
		else {
			gubo.torchPos = torchPos;
		}
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

		//Copper key
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, keyTakenOrNot[1] * 1.01f, 0)) * ubo.model;
		updateObject(copperKeyObject, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(copperKeyHoleObject, ubo, currentImage);





		//Door borders
		ubo.model = glm::mat4(1.0f);
		updateObject(doorBorders, ubo, currentImage);

		//Doors
		ubo.model = glm::mat4(1.0f);
		if (doorOpenOrNot[0] == 1 && slowlyOpenDoors[0] < 1.01f) {
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[0] * slowlyOpenDoors[0], 0)) * ubo.model;
			slowlyOpenDoors[0] += 0.001f;
		}
		else if (slowlyOpenDoors[0] >= 1.01f) {
			userCouldPassThroughDoors[0] = 1;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[0] * slowlyOpenDoors[0], 0)) * ubo.model;
		}
		if (userCouldPassThroughDoors[0] == 0 && slowlyOpenDoors[0] >= 0.95f) {
			userCouldPassThroughDoors[0] = 1;
		}
		updateOneInstanceOfObject(doors, ubo, currentImage, 0);
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(3, 0, 5)) * ubo.model;
		if (doorOpenOrNot[1] == 1 && slowlyOpenDoors[1] < 1.01f) {
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[1] * slowlyOpenDoors[1], 0)) * ubo.model;
			slowlyOpenDoors[1] += 0.001f;
		}
		else if (slowlyOpenDoors[1] >= 1.01f) {
			userCouldPassThroughDoors[1] = 1;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[1] * slowlyOpenDoors[1], 0)) * ubo.model;
		}
		if (userCouldPassThroughDoors[1] == 0 && slowlyOpenDoors[1] >= 0.95f) {
			userCouldPassThroughDoors[1] = 1;
		}
		updateOneInstanceOfObject(doors, ubo, currentImage, 1);
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(5, 0, 0)) * ubo.model;
		//Rotate on the correct axis
		ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(9.0f, 0.0f, 3.0f))) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(9.0f, 0.0f, 3.0f)) * ubo.model;
		if (doorOpenOrNot[2] == 1 && slowlyOpenDoors[2] < 1.01f) {
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[2] * slowlyOpenDoors[2], 0)) * ubo.model;
			slowlyOpenDoors[2] += 0.001f;
		}
		else if (slowlyOpenDoors[2] >= 1.01f) {
			userCouldPassThroughDoors[2] = 1;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[2] * slowlyOpenDoors[2], 0)) * ubo.model;
		}
		if (userCouldPassThroughDoors[2] == 0 && slowlyOpenDoors[2] >= 0.95f) {
			userCouldPassThroughDoors[2] = 1;
		}
		updateOneInstanceOfObject(doors, ubo, currentImage, 2);
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5)) * ubo.model;
		//Rotate on the correct axis
		ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, -2.0f))) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, -2.0f)) * ubo.model;
		if (doorOpenOrNot[3] == 1 && slowlyOpenDoors[3] < 1.01f) {
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[3] * slowlyOpenDoors[3], 0)) * ubo.model;
			slowlyOpenDoors[3] += 0.001f;
		}
		else if (slowlyOpenDoors[3] >= 1.01f) {
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[3] * slowlyOpenDoors[3], 0)) * ubo.model;
		}
		if (userCouldPassThroughDoors[3] == 0 && slowlyOpenDoors[3] >= 0.95f) {
			userCouldPassThroughDoors[3] = 1;
		}
		updateOneInstanceOfObject(doors, ubo, currentImage, 3);
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(8, 0, 1)) * ubo.model;
		//Rotate on the correct axis
		ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 0.0f, 4.0f))) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 0.0f, 4.0f)) * ubo.model;
		if (doorOpenOrNot[4] == 1 && slowlyOpenDoors[4] < 1.01f) {
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[4] * slowlyOpenDoors[4], 0)) * ubo.model;
			slowlyOpenDoors[4] += 0.001f;
		}
		else if (slowlyOpenDoors[4] >= 1.01f) {
			userCouldPassThroughDoors[4] = 1;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, doorOpenOrNot[4] * slowlyOpenDoors[4], 0)) * ubo.model;
		}
		if (userCouldPassThroughDoors[4] == 0 && slowlyOpenDoors[4] >= 0.95f) {
			userCouldPassThroughDoors[4] = 1;
		}
		updateOneInstanceOfObject(doors, ubo, currentImage, 4);





		//Levers
		ubo.model = glm::mat4(1.0f);
		if (leverUsedOrNot[0] == 1) {
			ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.5f, 2.2f))) * ubo.model;
			ubo.model = glm::rotate(glm::mat4(1.0f), leverUsedOrNot[0] * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * ubo.model;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.5f, 2.2f)) * ubo.model;
		}
		updateOneInstanceOfObject(levers, ubo, currentImage, 0);
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(5.8f, 0, 1.3f)) * ubo.model;
		//Rotate on the correct axis
		ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(8.3f, 0.5f, 3.5f))) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(8.3f, 0.5f, 3.5f)) * ubo.model;
		if (leverUsedOrNot[1] == 1) {
			ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(8.3f, 0.5f, 3.5f))) * ubo.model;
			ubo.model = glm::rotate(glm::mat4(1.0f), leverUsedOrNot[2] * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * ubo.model;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(8.3f, 0.5f, 3.5f)) * ubo.model;
		}
		/*if (leverUsedOrNot[1] == 0 &&) {
			ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(8.3f, 0.5f, 3.5f))) * ubo.model;
			ubo.model = glm::rotate(glm::mat4(1.0f), leverUsedOrNot[2] * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * ubo.model;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(8.3f, 0.5f, 3.5f)) * ubo.model;
		}*/
		updateOneInstanceOfObject(levers, ubo, currentImage, 1);
		ubo.model = glm::mat4(1.0f);
		//Rotate on the correct axis
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0, -3.7f)) * ubo.model;
		ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(3.3f, 0.5f, -1.5f))) * ubo.model;
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(3.3f, 0.5f, -1.5f)) * ubo.model;
		if (leverUsedOrNot[2] == 1) {
			ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(3.3f, 0.5f, -1.5f))) * ubo.model;
			ubo.model = glm::rotate(glm::mat4(1.0f), leverUsedOrNot[2] * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * ubo.model;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(3.3f, 0.5f, -1.5f)) * ubo.model;
		}
		updateOneInstanceOfObject(levers, ubo, currentImage, 2);





		//Power up
		ubo.model = glm::mat4(1.0f);
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, powerUpTakenOrNot * 10.0f, 0)) * ubo.model;
		//Rotate on the correct axis
		if (powerUpTakenOrNot == 0) {
			ubo.model = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.4f, 12.0f))) * ubo.model;
			ubo.model = glm::rotate(glm::mat4(1.0f), rotatingPowerUp * glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f)) * ubo.model;
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.4f, 12.0f)) * ubo.model;
			rotatingPowerUp++;
		}
		updateObject(powerUp, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(powerUpBase, ubo, currentImage);





		//Winning room
		/*ubo.model = glm::mat4(1.0f);
		updateObject(winningRoom, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(winningRoomCeiling, ubo, currentImage);
		ubo.model = glm::mat4(1.0f);
		updateObject(winningRoomFloor, ubo, currentImage);*/





		//Torch
		ubo.model = glm::mat4(1.0f);
		if (torchTaken) {
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 2.0f, 0)) * ubo.model;
		}
		updateObject(torch, ubo, currentImage);





		//Tutorial
		if (controllerPlugged == 1) {
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[0] * 100.0f, 0)) * ubo.model;
			updateObject(tutorial, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[1] * 100.0f, 0)) * ubo.model;
			updateObject(windowTutorial, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[2] * 100.0f, 0)) * ubo.model;
			updateObject(visualController, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[3] * 100.0f, 0)) * ubo.model;
			updateObject(movementController, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[4] * 100.0f, 0)) * ubo.model;
			updateObject(interactionController, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[5] * 100.0f, 0)) * ubo.model;
			updateObject(restartController, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[6] * 100.0f, 0)) * ubo.model;
			updateObject(tutorialAgainController, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialNextElements[0] * 100.0f, 0)) * ubo.model;
			updateObject(nextController, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialNextElements[1] * 100.0f, 0)) * ubo.model;
			updateObject(endController, ubo, currentImage);
		}
		else {
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[0] * 100.0f, 0)) * ubo.model;
			updateObject(tutorial, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[1] * 100.0f, 0)) * ubo.model;
			updateObject(windowTutorial, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[2] * 100.0f, 0)) * ubo.model;
			updateObject(visual, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[3] * 100.0f, 0)) * ubo.model;
			updateObject(movement, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[4] * 100.0f, 0)) * ubo.model;
			updateObject(interaction, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[5] * 100.0f, 0)) * ubo.model;
			updateObject(restart, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialElements[6] * 100.0f, 0)) * ubo.model;
			updateObject(tutorialAgain, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialNextElements[0] * 100.0f, 0)) * ubo.model;
			updateObject(next, ubo, currentImage);
			ubo.model = glm::mat4(1.0f);
			ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, tutorialNextElements[1] * 100.0f, 0)) * ubo.model;
			updateObject(end, ubo, currentImage);
		}
	}




	
	void manageTutorial() {
		if (controllerPlugged == 1) {
			if (buttons[2] == GLFW_PRESS)
			{
				stateTutorial = true;
			}
			else
			{
				stateTutorial = false;
				firstTutorial = true;
			}
			if (buttons[2] == GLFW_PRESS && firstTutorial) {
				if (firstTutorial) {
					firstTutorial = false;
				}
				if (tutorialElements[0] == 0) {
					tutorialElements[0] = 1;
					tutorialElements[1] = 0;
				}
				else if (tutorialElements[1] == 0) {
					tutorialElements[1] = 1;
					tutorialElements[2] = 0;
				}
				else if (tutorialElements[2] == 0) {
					tutorialElements[2] = 1;
					tutorialElements[3] = 0;
				}
				else if (tutorialElements[3] == 0) {
					tutorialElements[3] = 1;
					tutorialElements[4] = 0;
				}
				else if (tutorialElements[4] == 0) {
					tutorialElements[4] = 1;
					tutorialElements[5] = 0;
				}
				else if (tutorialElements[5] == 0) {
					tutorialElements[5] = 1;
					tutorialElements[6] = 0;
					tutorialNextElements[0] = 1;
					tutorialNextElements[1] = 0;
				}
				else if (tutorialElements[6] == 0) {
					tutorialElements[6] = 1;
					tutorialNextElements[1] = 1;
					if (doneTutorialAgain) {
						doneTutorialAgain = false;
						pos = savePos;
						oldPos = savePos;
						lookPitch = lookPitchSaved;
						lookYaw = lookYawSaved;
					}
					else {
						pos = glm::vec3(0.0f, 0.5f, 0.0f);
						oldPos = glm::vec3(0.0f, 0.5f, 0.0f);
						lookYaw = glm::radians(-45.0f);
						lookPitch = 0.0f;
					}
					firstTimeDoingTheTutorial = false;
				}
			}
		}
		else {
			int stateTutorialInt = glfwGetKey(window, GLFW_KEY_N);
			if (stateTutorialInt == GLFW_PRESS)
			{
				stateTutorial = true;
			}
			else
			{
				stateTutorial = false;
				firstTutorial = true;
			}
			if (glfwGetKey(window, GLFW_KEY_N) && firstTutorial) {
				if (firstTutorial) {
					firstTutorial = false;
				}
				if (tutorialElements[0] == 0) {
					tutorialElements[0] = 1;
					tutorialElements[1] = 0;
				}
				else if (tutorialElements[1] == 0) {
					tutorialElements[1] = 1;
					tutorialElements[2] = 0;
				}
				else if (tutorialElements[2] == 0) {
					tutorialElements[2] = 1;
					tutorialElements[3] = 0;
				}
				else if (tutorialElements[3] == 0) {
					tutorialElements[3] = 1;
					tutorialElements[4] = 0;
				}
				else if (tutorialElements[4] == 0) {
					tutorialElements[4] = 1;
					tutorialElements[5] = 0;
				}
				else if (tutorialElements[5] == 0) {
					tutorialElements[5] = 1;
					tutorialElements[6] = 0;
					tutorialNextElements[0] = 1;
					tutorialNextElements[1] = 0;
				}
				else if (tutorialElements[6] == 0) {
					tutorialElements[6] = 1;
					tutorialNextElements[1] = 1;
					if (doneTutorialAgain) {
						doneTutorialAgain = false;
						pos = savePos;
						oldPos = savePos;
						lookPitch = lookPitchSaved;
						lookYaw = lookYawSaved;
					}
					else {
						pos = glm::vec3(0.0f, 0.5f, 0.0f);
						oldPos = glm::vec3(0.0f, 0.5f, 0.0f);
						lookYaw = glm::radians(-45.0f);
						lookPitch = 0.0f;
					}
					firstTimeDoingTheTutorial = false;
				}
			}
		}
	}

	void seeTutorialAgain() {
		if (controllerPlugged == 1) {
			//Start
			if (buttons[9] == GLFW_PRESS)
			{
				stateTutorialAgain = true;
			}
			else
			{
				stateTutorialAgain = false;
				firstTutorialAgain = true;
			}
			if (buttons[9] == GLFW_PRESS && firstTutorialAgain) {
				if (firstTutorialAgain) {
					firstTutorialAgain = false;
				}
				doneTutorialAgain = true;
				tutorialElements = { 0,1,1,1,1,1,1 };
				tutorialNextElements = { 0,1 };
				if (pos.z <= -450.0f) {//-495.0f) {
					if (firstTimeDoingTheTutorial) {
						savePos = glm::vec3(0.0f, -0.5f, 0.0f);
						oldPos = glm::vec3(0.0f, 0.5f, 0.0f);
						lookYaw = glm::radians(-45.0f);
						lookPitch = 0.0f;
					}
				}
				else {
					savePos = pos;
					lookPitchSaved = lookPitch;
					lookYawSaved = lookYaw;
				}
				pos = glm::vec3(500.0f, 199.5f, -495.0f);
				oldPos = glm::vec3(500.0f, 199.5f, -495.0f);
				lookYaw = 0.0f;
				lookPitch = 0.0f;
			}
		}
		else {
			int stateTutorialAgainInt = glfwGetKey(window, GLFW_KEY_T);
			if (stateTutorialAgainInt == GLFW_PRESS)
			{
				stateTutorialAgain = true;
			}
			else
			{
				stateTutorialAgain = false;
				firstTutorialAgain = true;
			}
			if (glfwGetKey(window, GLFW_KEY_T) && firstTutorialAgain) {
				if (firstTutorialAgain) {
					firstTutorialAgain = false;
				}
				doneTutorialAgain = true;
				tutorialElements = { 0,1,1,1,1,1,1 };
				tutorialNextElements = { 0,1 };
				if (pos.z <= -450.0f) {//-495.0f) {
					if (firstTimeDoingTheTutorial) {
						savePos = glm::vec3(0.0f, -0.5f, 0.0f);
						oldPos = glm::vec3(0.0f, 0.5f, 0.0f);
						lookYaw = glm::radians(-45.0f);
						lookPitch = 0.0f;
					}
				}
				else {
					savePos = pos;
					lookPitchSaved = lookPitch;
					lookYawSaved = lookYaw;
				}
				pos = glm::vec3(500.0f, 199.5f, -495.0f);
				oldPos = glm::vec3(500.0f, 199.5f, -495.0f);
				lookYaw = 0.0f;
				lookPitch = 0.0f;
				//std::cout << "\n\n\n" << lookYawSaved;
			}
		}
	}
	
	void restartTheGame() {
		if (controllerPlugged == 1) {
			//Share
			if (buttons[8] == GLFW_PRESS) {
				resetAll();
			}
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_P)) {
				resetAll();
			}
		}
	}

	glm::mat4 updateCameraPosition(GLFWwindow* window) {
		const float ROT_SPEED = glm::radians(90.0f);
		//const float MOVE_SPEED = powerUpTakenOrNot + 1.2f;
		const float MOVE_SPEED = powerUpTakenOrNot + 2.0f;
		const float JUMP_SPEED = 2.0f;
		const float MOUSE_RES = 500.0f;

		static auto startTime = std::chrono::high_resolution_clock::now();
		static float lastTime = 0.0f;
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
		float deltaT = time - lastTime;
		lastTime = time;

		oldPos = pos;


		controllerPlugged = glfwJoystickPresent(GLFW_JOYSTICK_1);
		//std::cout << present;

		if (controllerPlugged == 1) {
			axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

			//std::cout << "\nLeft stick X Axis: " << axes[0];
			//std::cout << "\nLeft stick Y Axis: " << axes[1];
			//std::cout << "\nRight stick X Axis: " << axes[2];
			//std::cout << "\nRight stick Y Axis: " << axes[3];
			//std::cout << "\nL2: " << axes[4];
			//std::cout << "\nR2: " << axes[5];


			lookYaw -= (round(axes[2] * 10.0) / 10.0) / 100.0;
			//lookPitch -= (round(axes[3] * 10.0) / 10.0) / 100.0;

			if ((round(axes[0] * 10.0) / 10.0) < -0.3f) {
				pos -= MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
					glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(1, 0, 0, 1)) * deltaT;
			}
			if ((round(axes[0] * 10.0) / 10.0) > 0.3f) {
				pos += MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
					glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(1, 0, 0, 1)) * deltaT;
			}
			if ((round(axes[1] * 10.0) / 10.0) < -0.3f) {
				pos -= MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
					glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0, 0, 1, 1)) * deltaT;
			}
			if ((round(axes[1] * 10.0) / 10.0) > 0.3f) {
				pos += MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
					glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0, 0, 1, 1)) * deltaT;
			}


			buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
			/*if (buttons[0] == GLFW_PRESS) {
				//Square
				//std::cout << buttons[0];
			}
			if (buttons[1] == GLFW_PRESS) {
				//X
				//std::cout << buttons[1];
			}*/
			/*if (buttons[2] == GLFW_PRESS) {
				//Circle
				//std::cout << buttons[2];
			}
			if (buttons[3] == GLFW_PRESS) {
				//Triangle
				//std::cout << buttons[3];
			}*/


			if (buttons[1] == GLFW_PRESS && !jump) {
				jump = true;
			}

			if (pos.y < 0.5f)
			{
				pos.y = 0.5f;
				jump = false;
				jumpDown = false;
			}

			if (pos.y >= 0.85) {
				jumpDown = true;
			}

			if (jump) {
				if (pos.y <= 0.85 && !jumpDown) {
					pos += JUMP_SPEED * glm::vec3(0, 0.7f, 0) * deltaT;
				}
				else {
					pos -= JUMP_SPEED * glm::vec3(0, 0.7f, 0) * deltaT;
				}
			}
		}
		else {
			//View
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

			//Movement
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

			/*if (glfwGetKey(window, GLFW_KEY_SPACE)) {
				pos += MOVE_SPEED * glm::vec3(0, 1, 0) * deltaT;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
				pos -= MOVE_SPEED * glm::vec3(0, 1, 0) * deltaT;
			}*/

			//Jump
			if (glfwGetKey(window, GLFW_KEY_SPACE) && !jump) {
				jump = true;
			}

			if (pos.y < 0.5f)
			{
				pos.y = 0.5f;
				jump = false;
				jumpDown = false;
			}

			if (pos.y >= 0.85) {
				jumpDown = true;
			}

			if (jump) {
				if (pos.y <= 0.85 && !jumpDown) {
					pos += JUMP_SPEED * glm::vec3(0, 0.7f, 0) * deltaT;
				}
				else {
					pos -= JUMP_SPEED * glm::vec3(0, 0.7f, 0) * deltaT;
				}
			}
		}



		CamDir = glm::mat3(glm::rotate(glm::mat4(1.0f), lookYaw, glm::vec3(0.0f, 1.0f, 0.0f))) *
			glm::mat3(glm::rotate(glm::mat4(1.0f), lookPitch, glm::vec3(1.0f, 0.0f, 0.0f)));



		if (!canStep(pos.x, pos.z)) {
			pos = oldPos;
		}



		CamPos = pos;



		glm::mat4 out =
			glm::transpose(glm::mat4(CamDir)) *
			glm::translate(glm::mat4(1.0), -pos);
		return out;
	}

	void resetAll() {
		pos = glm::vec3(0.0f, 0.5f, 0.0f);
		lookYaw = glm::radians(-45.0f);
		lookPitch = 0.0f;
		lookRoll = 0.0f;

		win = false;
		jump = false;
		jumpDown = false;

		CamPos = glm::vec3(0);
		CamDir = glm::mat3(0);
		CharacterPos = glm::mat4(0);


		//Environment
		doorOpenOrNot = { 0,0,0,0,0 };
		userCouldPassThroughDoors = { 0,0,0,0,0 };
		//Gold and Copper key
		doorCouldBeOpened = { 0,0 };
		leverCouldBeUsed = { 0,0,0 };
		leverUsedOrNot = { 0,0,0 };
		keyTakenOrNot = { 0,0 };
		powerUpTakenOrNot = 0.0f;

		rotatingPowerUp = 0;
		slowlyOpenDoors = { 0.0f,0.0f,0.0f,0.0f,0.0f };

		torchPos = glm::vec3(0.0f, 0.8f, -4.42f);
		torchCouldBeTaken = false;
		torchTaken = false;
	}

	void checkWinning() {
		/*if (win) {
			pos = glm::vec3(-6.0f, 0.5f, 2.0f);
			std::cout << win;
		}*/
	}
	
	void updateWindow() {
		int stateF11Int = glfwGetKey(window, GLFW_KEY_F11);
		if (stateF11Int == GLFW_PRESS)
		{
			stateF11 = true;
		}
		else
		{
			stateF11 = false;
			firstF11 = true;
		}
		if (glfwGetKey(window, GLFW_KEY_F11) && firstF11) {
			if (firstF11) {
				firstF11 = false;
			}
			int maximized = glfwGetWindowAttrib(window, GLFW_MAXIMIZED);
			if (maximized == 0) {
				glfwMaximizeWindow(window);
			}
			else {
				glfwRestoreWindow(window);
			}
		}
	}

	void interctWithObjects() {
		openTheDoor();
		
		if (torchCouldBeTaken) {
			if (controllerPlugged == 1) {
				if (buttons[0] == GLFW_PRESS) {
					torchTaken = true;
				}
			}
			else {
				if (glfwGetKey(window, GLFW_KEY_E)) {
					torchTaken = true;
				}
			}
		}

		//std::cout << torchTaken;
		if (torchTaken) {
			torchPos = pos;
		}
	}

	void openTheDoor() {
		if (leverCouldBeUsed[2] == 1 && leverUsedOrNot[2] == 0) {
			if (controllerPlugged == 1) {
				if (buttons[0] == GLFW_PRESS) {
					doorOpenOrNot[3] = 1;
					leverUsedOrNot[2] = 1;
				}
			}
			else {
				if (glfwGetKey(window, GLFW_KEY_E)) {
					doorOpenOrNot[3] = 1;
					leverUsedOrNot[2] = 1;
				}
			}
		}

		if (leverCouldBeUsed[1] == 1 && leverUsedOrNot[1] == 0) {
			if (controllerPlugged == 1) {
				if (buttons[0] == GLFW_PRESS) {
					doorOpenOrNot[2] = 1;
					leverUsedOrNot[1] = 1;
				}
			}
			else {
				if (glfwGetKey(window, GLFW_KEY_E)) {
					doorOpenOrNot[2] = 1;
					leverUsedOrNot[1] = 1;
				}
			}
		}

		if (leverCouldBeUsed[0] == 1 && leverUsedOrNot[0] == 0) {
			if (controllerPlugged == 1) {
				if (buttons[0] == GLFW_PRESS) {
					doorOpenOrNot[0] = 1;
					leverUsedOrNot[0] = 1;
				}
			}
			else {
				if (glfwGetKey(window, GLFW_KEY_E)) {
					doorOpenOrNot[0] = 1;
					leverUsedOrNot[0] = 1;
				}
			}
		}

		if (doorCouldBeOpened[0] == 1 && doorOpenOrNot[4] == 0) {
			if (controllerPlugged == 1) {
				if (buttons[0] == GLFW_PRESS) {
					doorOpenOrNot[4] = 1;
				}
			}
			else {
				if (glfwGetKey(window, GLFW_KEY_E)) {
					doorOpenOrNot[4] = 1;
				}
			}
		}

		if (doorCouldBeOpened[1] == 1 && doorOpenOrNot[1] == 0) {
			if (controllerPlugged == 1) {
				if (buttons[0] == GLFW_PRESS) {
					doorOpenOrNot[1] = 1;
				}
			}
			else {
				if (glfwGetKey(window, GLFW_KEY_E)) {
					doorOpenOrNot[1] = 1;
				}
			}
		}
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

	void objectInit(Object *object, std::string modelPath, std::string texturePath, DescriptorSetLayout descriptorSetLayout, DescriptorSetLayoutObject descriptorSetLayoutObject, bool isAText) {
		object->model.init(this, modelPath, isAText);
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

	void multipleInstanceObjectInit(MultipleObject* object, std::string modelPath, std::string texturePath, DescriptorSetLayout descriptorSetLayout, int numberOfInstances, DescriptorSetLayoutObject descriptorSetLayoutObject, bool isAText) {
		object->model.init(this, modelPath, isAText);
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
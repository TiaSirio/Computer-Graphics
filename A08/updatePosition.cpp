// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
	static float yaw = 0.0f;
	static float pitch = 0.0f;
	static float roll = 0.0f;
	static glm::vec3 pos = glm::vec3(-3, 0, 2);
	static glm::vec3 size = glm::vec3(1, 1, 1);
	static auto startTime = std::chrono::high_resolution_clock::now();
	static float lastTime = 0.0f;
	glm::vec3 ux = glm::vec3(1, 0, 0);
	glm::vec3 uy = glm::vec3(0, 1, 0);
	glm::vec3 uz = glm::vec3(0, 0, 1);
	static glm::quat quat = glm::quat(glm::vec3(0, 0, 0));
	static glm::mat4 quatMatrix = glm::mat4(quat);

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	float deltaT = time - lastTime;
	lastTime = time;

	if (glfwGetKey(window, GLFW_KEY_A)) {
		pos += ux * glm::vec3(-1.0f, 0, 0) * deltaT;
		if (glfwGetKey(window, GLFW_KEY_W)) {
			yaw = 135.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_S)) {
			yaw = -135.0f;
		}
		else {
			yaw = 180.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			roll = 45.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			roll = -45.0f;
		}
		else {
			roll = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		pos += ux * glm::vec3(1.0f, 0, 0) * deltaT;
		if (glfwGetKey(window, GLFW_KEY_W)) {
			yaw = 45.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_S)) {
			yaw = -45.0f;
		}
		else {
			yaw = 0.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			roll = 45.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			roll = -45.0f;
		}
		else {
			roll = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_W)) {
		pos += uz * glm::vec3(0, 0, -1.0f) * deltaT;
		if (glfwGetKey(window, GLFW_KEY_A)) {
			yaw = 135.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_D)) {
			yaw = 45.0f;
		}
		else {
			yaw = 90.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			roll = 45.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			roll = -45.0f;
		}
		else {
			roll = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		pos += uz * glm::vec3(0, 0, 1.0f) * deltaT;
		if (glfwGetKey(window, GLFW_KEY_A)) {
			yaw = -135.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_D)) {
			yaw = -45.0f;
		}
		else {
			yaw = -90.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			roll = 45.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			roll = -45.0f;
		}
		else {
			roll = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		pos += uy * glm::vec3(0, 1.0f, 0) * deltaT;
		if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_D)) {
			roll = 45.0f;
		}
		else {
			roll = 90.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		if (pos[1] > 0.0f) {
			pos += uy * glm::vec3(0, -1.0f, 0) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_D)) {
			roll = -45.0f;
		}
		else {
			roll = -90.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_Q)) {
		pitch -= 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_E)) {
		pitch += 0.5f;
	}
	
	if (glfwGetKey(window, GLFW_KEY_M)) {
		size += glm::vec3(0.005f, 0.005f, 0.005f);
	}
	if (glfwGetKey(window, GLFW_KEY_N)) {
		if (size[0] >= 0.005f) {
			size -= glm::vec3(0.005f, 0.005f, 0.005f);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_R)) {
		yaw = 0.0f;
		pitch = 0.0f;
		roll = 0.0f;
		size = glm::vec3(1, 1, 1);
		pos = glm::vec3(-3, 0, 2);
	}

	quat = glm::quat(glm::vec3(0, glm::radians(yaw), 0)) *
		glm::quat(glm::vec3(glm::radians(pitch), 0, 0)) *
		glm::quat(glm::vec3(0, 0, glm::radians(roll)));

	quatMatrix = glm::mat4(quat);

	glm::mat4 out =
		glm::translate(glm::mat4(1.0), pos) *
		quatMatrix *
		glm::scale(glm::mat4(1.0), size);
	return out;

	/*glm::mat4 out =
		glm::translate(glm::mat4(1.0), pos) *
		glm::rotate(glm::mat4(1.0), glm::radians(yaw), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(pitch), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), glm::radians(roll), glm::vec3(0, 0, 1)) *
		glm::scale(glm::mat4(1.0), size);
	return out;*/
}


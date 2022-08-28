float w = 2.0f;
float n = -4.0f;
float f = 12.0f;

// Create a matrix for Isometric projection with the given aspect ration a
glm::mat4 PO1(float a) {
	glm::mat4 out = glm::mat4(1.0);

	//Orthogonal matrix + y pointing up
	//The first scale is to match the Vulkan convention
	/*out = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(-w, w, -(w / a), w / a, n, f);

	//Rotation on x-axis.
	out = out * rotate(glm::mat4(1.0), glm::radians(35.26f), glm::vec3(1, 0, 0));

	//Rotation on y-axis.
	out = out * rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(0, 1, 0));*/

	//Rotation on y-axis.
	out = rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(0, 1, 0)) * out;

	//Rotation on x-axis.
	out = rotate(glm::mat4(1.0), glm::radians(35.26f), glm::vec3(1, 0, 0)) * out;

	//Orthogonal matrix
	out = glm::ortho(-w, w, -(w / a), w / a, n, f) * out;

	//Y pointing up
	out = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * out;

	return out;
}





// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a) {
	glm::mat4 out = glm::mat4(1.0);

	//Orthogonal matrix
	/*out = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(-w, w, -(w / a), w / a, n, f);

	//Rotation on x-axis.
	out = out * rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(1, 0, 0));

	//Rotation on y-axis.
	out = out * rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(0, 1, 0));*/

	//Rotation on y-axis.
	out = rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(0, 1, 0)) * out;

	//Rotation on x-axis.
	out = rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(1, 0, 0)) * out;

	//Orthogonal matrix
	out = glm::ortho(-w, w, -(w / a), w / a, n, f) * out;

	//Y pointing up
	out = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * out;

	return out;
}





// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a) {
	glm::mat4 out = glm::mat4(1.0);

	//Orthogonal matrix
	/*out = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(-w, w, -(w / a), w / a, n, f);

	//Rotation on x-axis.
	out = out * rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(1, 0, 0));

	//Rotation on y-axis.
	out = out * rotate(glm::mat4(1.0), glm::radians(60.0f), glm::vec3(0, 1, 0));*/

	//Rotation on y-axis.
	out = rotate(glm::mat4(1.0), glm::radians(60.0f), glm::vec3(0, 1, 0)) * out;

	//Rotation on x-axis.
	out = rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3(1, 0, 0)) * out;
	//out = rotate(glm::mat4(1.0), glm::radians(30.0f), glm::vec3(1, 0, 0)) * out;

	//Orthogonal matrix
	out = glm::ortho(-w, w, -(w / a), w / a, n, f) * out;

	//Y pointing up
	out = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * out;

	return out;
}





// Create a matrix for Cabinet projection (alpha = 45)
// with the given aspect ration a
glm::mat4 PO4(float a) {
	glm::mat4 out = glm::mat4(1.0);

	//Orthogonal matrix
	out = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(-w, w, -(w / a), w / a, n, f);

	//Share on z-axis.
	out = out * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, -((0.5) * (sqrt(2)/2)), -((0.5) * (sqrt(2)/2)), 1, 0, 0, 0, 0, 1);

	return out;
}
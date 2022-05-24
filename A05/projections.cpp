float n = 0.1f;
float f = 9.9f;
float r = 0.0f;
float l = 0.0f;
float b = 0.0f;
float t = 0.0f;
float fovy = 0.0f;

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 90o
glm::mat4 PO1(float a) {
	fovy = glm::radians(90.0f);
	glm::mat4 out = glm::mat4(1.0);

	out = glm::perspective(fovy, a, n, f);
	out[1][1] *= -1;

	return out;
}





// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 120o
glm::mat4 PO2(float a) {
	fovy = glm::radians(120.0f);
	glm::mat4 out = glm::mat4(1.0);

	out = glm::perspective(fovy, a, n, f);
	out[1][1] *= -1;

	return out;
}





// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 30o
glm::mat4 PO3(float a) {
	fovy = glm::radians(30.0f);
	glm::mat4 out = glm::mat4(1.0);

	out = glm::perspective(fovy, a, n, f);
	out[1][1] *= -1;

	return out;
}





// Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view
// with a FovY = 90o. Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {
	fovy = glm::radians(90.0f);
	l = (-a) * n * (tan(fovy/2));
	b = (-n) * (tan(fovy/2));
	t = n * (tan(fovy/2));

	glm::mat4 out = glm::mat4(1.0);

	out = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::frustum(l, r, b, t, n, f);

	return out;
}
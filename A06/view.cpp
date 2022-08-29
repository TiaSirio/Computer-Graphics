 // Create a look in direction matrix
 // Pos    -> Position of the camera
 // Angs.x -> direction (alpha)
 // Angs.y -> elevation (beta)
 // Angs.z -> roll (rho)
glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {
	glm::mat4 out =
		glm::rotate(glm::mat4(1.0), -Angs.z, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0), -Angs.y, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), -Angs.x, glm::vec3(0, 1, 0)) *
		glm::translate(glm::mat4(1.0), -Pos);
	return out;
}





 // Create a look at matrix
 // Pos    -> Position of the camera (c)
 // aim    -> Posizion of the target (a)
 // Roll   -> roll (rho)
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {
	//First working method
	//glm::mat4 out = glm::lookAt(Pos, aim, glm::vec3(0, 1, 0));
	//Add Roll
	//out = glm::rotate(glm::mat4(1.0), -Roll, glm::vec3(0, 0, 1)) * out;





	//Second working method
	//U
	//glm::vec3 u = glm::vec3(0, 1, 0);

	//Vz
	//glm::vec3 vz_i = glm::normalize(Pos - aim);
	//glm::vec4 vz = glm::vec4(vz_i, 0);

	//Vx
	//glm::vec3 vx_i = glm::normalize(glm::cross(u, vz_i));
	//glm::vec4 vx = glm::vec4(vx_i, 0);

	//Vy
	//glm::vec3 vy_i = glm::cross(vz_i, vx_i);
	//glm::vec4 vy = glm::vec4(vy_i, 0);

	//Rc
	//glm::mat3 rc = glm::mat3(vx_i, vy_i, vz_i);

	//Mv
	//glm::mat4 out = glm::inverse(glm::mat4(vx, vy, vz, glm::vec4(Pos, 1)));
	//Add Roll
	//out = glm::rotate(glm::mat4(1.0), -Roll, glm::vec3(0, 0, 1)) * out;





	//Third working method
	//U (up vector)
	glm::vec3 u = glm::vec3(0, 1, 0);

	//Vz
	glm::vec3 vz = glm::normalize(Pos - aim);

	//Vx
	glm::vec3 vx = glm::normalize(glm::cross(u, vz));

	//Vy
	glm::vec3 vy = glm::cross(vz, vx);

	//Rc
	glm::mat3 rc = glm::mat3(vx, vy, vz);
	//(Rc)^T
	glm::mat3 rc_t = glm::transpose(rc);

	//Last column
	glm::vec3 rc_camera = -(rc_t) * Pos;

	//Mv
	glm::mat4 out{};
	out[0] = glm::vec4(rc_t[0], 0);
	out[1] = glm::vec4(rc_t[1], 0);
	out[2] = glm::vec4(rc_t[2], 0);
	out[3] = glm::vec4(rc_camera, 1);

	//Add Roll
	out = glm::rotate(glm::mat4(1.0), -Roll, glm::vec3(0, 0, 1)) * out;

	return out;
}




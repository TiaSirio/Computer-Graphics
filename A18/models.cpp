// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;
std::vector<Vertex> M3_vertices;
std::vector<Vertex> M4_vertices;

glm::vec3 surface_normal(glm::vec3 vector0, glm::vec3 vector1, glm::vec3 vector2) {
	glm::vec3 v1 = vector1 - vector0;
	glm::vec3 v2 = vector2 - vector0;
	glm::vec3 surfNormal = normalize(cross(v1, v2));
	return surfNormal;
}

void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

	float sizeCube = 1.0f;
	int arrayOfCube = 0;
	int arrayOfNormCube = 0;
	int startingOfNormCube = 0;
	M1_vertices.resize(3 * 4 * 6);

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices

	// Bottom face(y = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, -sizeCube);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Top face (y = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, sizeCube);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Back face  (z = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, -sizeCube);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Front face (z = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, sizeCube);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Right face (x = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, -sizeCube);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Left face (x = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, -sizeCube);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, sizeCube);
	arrayOfCube++;
	
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Resizes the indices array. Replace the values with the correct number of
	// indices (3 * number of triangles)
	int indicesCube = 0;
	int valueOfCubeIndices = 0;
	int startingOfFace = 0;
	//Two triangles per face
	M1_indices.resize(3 * 2 * 6);

	for (int i = 0; i < 6; i++) {
		startingOfFace = indicesCube;
		for (int j = 0; j < 6; j++) {
			//Take last two points
			if (j < 3) {
				M1_indices[valueOfCubeIndices] = indicesCube;
				indicesCube++;
			}
			//Plug the last two points with the correct last one
			else if (j == 5) {
				M1_indices[valueOfCubeIndices] = startingOfFace;
				indicesCube = startingOfFace + 4;
			}
			//For the first three value takes three points
			else {
				M1_indices[valueOfCubeIndices] = indicesCube - 1;
				indicesCube++;
			}
			valueOfCubeIndices++;
		}
	}





	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.
	int slicesCylinder = 36;
	float radiusCylinder = 1;
	float heightCylinder = 1;
	//Center of the cylinder
	float xCylinder = 0, yCylinder = 0, zCylinder = -2;
	float normCx, normCz;

	M2_vertices.resize(4 * ((slicesCylinder + 1) * 3));

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	M2_vertices[0].pos = glm::vec3(xCylinder, yCylinder + heightCylinder, zCylinder);
	//M2_vertices[0].norm = glm::vec3(0.0, 1.0, 0.0);

	for (int i = 0; i < slicesCylinder; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), yCylinder + heightCylinder, zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
		//M2_vertices[(i + 1)].norm = glm::vec3(0.0, 1.0, 0.0);
	}

	M2_vertices[(slicesCylinder + 1)].pos = glm::vec3(xCylinder, yCylinder - heightCylinder, zCylinder);
	//M2_vertices[(slicesCylinder + 1)].norm = glm::vec3(0.0, -1.0, 0.0);

	for (int i = slicesCylinder + 1; i < (2 * slicesCylinder) + 1; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), yCylinder - heightCylinder, zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
		//M2_vertices[(i + 1)].norm = glm::vec3(0.0, -1.0, 0.0);
	}


	//One full rotation for the upper part
	for (int i = (2 * slicesCylinder) + 1; i < (slicesCylinder * 3) + 1; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), yCylinder + heightCylinder, zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
		normCx = cos(((float)i / slicesCylinder) * (2.0 * M_PI));
		normCz = sin(((float)i / slicesCylinder) * (2.0 * M_PI));
		M2_vertices[(i + 1)].norm = glm::vec3(normCx, 0.0, normCz);
	}

	//One full rotation for the lower part
	for (int i = (slicesCylinder * 3) + 1; i < (slicesCylinder * 4) + 1; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), yCylinder - heightCylinder, zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
		normCx = cos(((float)i / slicesCylinder) * (2.0 * M_PI));
		normCz = sin(((float)i / slicesCylinder) * (2.0 * M_PI));
		M2_vertices[(i + 1)].norm = glm::vec3(normCx, 0.0, normCz);
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(3 * 2 * slicesCylinder * 2);

	int counterCylinder = 0;
	int counter2Cylinder = 0;

	glm::vec3 firstNormalVector, secondNormalVector, thirdNormalVector;
	int valueIfCylinder = 0;

	//Upper surface
	for (int i = 0; i < slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = 0;
		M2_indices[(i * 3) + 1] = i + 1;
		M2_indices[(i * 3) + 2] = ((i + 1) % slicesCylinder) + 1;

		firstNormalVector = M2_vertices[0].pos;
		secondNormalVector = M2_vertices[i + 1].pos;
		thirdNormalVector = M2_vertices[((i + 1) % slicesCylinder) + 1].pos;

		M2_vertices[0].norm = -surface_normal(firstNormalVector, secondNormalVector, thirdNormalVector);
		M2_vertices[i + 1].norm = -surface_normal(secondNormalVector, thirdNormalVector, firstNormalVector);
		M2_vertices[((i + 1) % slicesCylinder) + 1].norm = -surface_normal(thirdNormalVector, firstNormalVector, secondNormalVector);
	}

	counterCylinder = slicesCylinder + 1;

	//Lower surface
	for (int i = slicesCylinder; i < 2 * slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = slicesCylinder + 1;
		M2_indices[(i * 3) + 1] = counterCylinder + 1;
		if ((i + 1) == (2 * slicesCylinder)) {
			M2_indices[(i * 3) + 2] = ((counterCylinder + 1) % ((2 * slicesCylinder) + 1)) + slicesCylinder + 2;
			valueIfCylinder = ((counterCylinder + 1) % ((2 * slicesCylinder) + 1)) + slicesCylinder + 2;
		}
		else {
			M2_indices[(i * 3) + 2] = ((counterCylinder + 1) % ((2 * slicesCylinder) + 1)) + 1;
			valueIfCylinder = ((counterCylinder + 1) % ((2 * slicesCylinder) + 1)) + 1;
		}

		firstNormalVector = M2_vertices[slicesCylinder + 1].pos;
		secondNormalVector = M2_vertices[counterCylinder + 1].pos;
		thirdNormalVector = M2_vertices[valueIfCylinder].pos;

		M2_vertices[slicesCylinder + 1].norm = surface_normal(firstNormalVector, secondNormalVector, thirdNormalVector);
		M2_vertices[counterCylinder + 1].norm = surface_normal(secondNormalVector, thirdNormalVector, firstNormalVector);
		M2_vertices[valueIfCylinder].norm = surface_normal(thirdNormalVector, firstNormalVector, secondNormalVector);

		counterCylinder++;
	}
	
	counterCylinder = (2 * slicesCylinder) + 1;

	//Triangles of the cylinder
	for (int i = 2 * slicesCylinder; i < 3 * slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = counterCylinder + 1;
		if (counterCylinder != (3 * slicesCylinder)) {
			M2_indices[(i * 3) + 1] = counterCylinder + 1 + 1;
			valueIfCylinder = counterCylinder + 1 + 1;
		}
		else {
			M2_indices[(i * 3) + 1] = (2 * slicesCylinder) + 2;
			valueIfCylinder = (2 * slicesCylinder) + 2;
		}
		M2_indices[(i * 3) + 2] = slicesCylinder + counterCylinder + 1;

		/*firstNormalVector = M2_vertices[counterCylinder + 1].pos;
		secondNormalVector = M2_vertices[valueIfCylinder].pos;
		thirdNormalVector = M2_vertices[slicesCylinder + counterCylinder + 1].pos;

		M2_vertices[counterCylinder + 1].norm = surface_normal(firstNormalVector, secondNormalVector, thirdNormalVector);
		M2_vertices[valueIfCylinder].norm = surface_normal(secondNormalVector, thirdNormalVector, firstNormalVector);
		M2_vertices[slicesCylinder + counterCylinder + 1].norm = surface_normal(thirdNormalVector, firstNormalVector, secondNormalVector);*/

		counterCylinder++;
	}

	counterCylinder = (3 * slicesCylinder) + 1;
	counter2Cylinder = (2 * slicesCylinder) + 1;

	//Triangles of the cylinder
	for (int i = 3 * slicesCylinder; i < 4 * slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = counterCylinder + 1;
		if (counterCylinder == (4 * slicesCylinder)) {
			M2_indices[(i * 3) + 1] = (2 * slicesCylinder) + 2;
			valueIfCylinder = (2 * slicesCylinder) + 2;
		}
		else {
			M2_indices[(i * 3) + 1] = ((counterCylinder + 1) % ((4 * slicesCylinder) + 1)) + 1;
			valueIfCylinder = ((counterCylinder + 1) % ((4 * slicesCylinder) + 1)) + 1;
		}
		M2_indices[(i * 3) + 2] = (counter2Cylinder + 1) + 1;

		/*firstCyl = M2_vertices[counterCylinder + 1].pos;
		secondNormalVector = M2_vertices[valueIfCylinder].pos;
		thirdNormalVector = M2_vertices[(counter2Cylinder + 1) + 1].pos;

		M2_vertices[counterCylinder + 1].norm = (M2_vertices[counterCylinder + 1].norm + surface_normal(firstNormalVector, secondNormalVector, thirdNormalVector)) * 0.5f;
		M2_vertices[valueIfCylinder].norm = (M2_vertices[valueIfCylinder].norm + surface_normal(secondNormalVector, thirdNormalVector, firstNormalVector)) * 0.5f;
		M2_vertices[(counter2Cylinder + 1) + 1].norm = (M2_vertices[(counter2Cylinder + 1) + 1].norm + surface_normal(thirdNormalVector, firstNormalVector, secondNormalVector)) * 0.5f;*/

		counter2Cylinder++;
		counterCylinder++;
	}





	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	float xCircle, yCircle, zCircle, xAndyCircle;
	float radiusCircle = 2.0f;
	float stackCountCricle = 24.0f;
	float sectorCountCircle = 72.0f;
	float sectorStepCircle = 2 * M_PI / sectorCountCircle;
	float stackStepCircle = M_PI / stackCountCricle;
	float sectorAngleCircle, stackAngleCircle;
	int valueOfArrayCircle = 0;
	int valueOfSecondArrayCircle = 0;
	int currentStackCircle, nextStackCircle;
	float xNormCircle, yNormCircle, zNormCircle;

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	M3_vertices.resize(3 * stackCountCricle * sectorCountCircle * 2);

	for (int i = 0; i <= stackCountCricle; ++i)
	{
		//Starting from pi/2 to -pi/2
		stackAngleCircle = M_PI / 2 - i * stackStepCircle;
		//r * cos(theta)
		xAndyCircle = radiusCircle * cos(stackAngleCircle);
		//r * sin(theta)
		zCircle = radiusCircle * sin(stackAngleCircle);

		//Add (sectorCount+1) vertices per stack
		//First and last vertices have same position
		for (int j = 0; j <= sectorCountCircle; ++j)
		{
			//Starting from 0 to 2pi
			sectorAngleCircle = j * sectorStepCircle;
			
			//r * cos(theta) * cos(phi)
			xCircle = xAndyCircle * cos(sectorAngleCircle);
			// r * cos(u) * sin(v)
			yCircle = xAndyCircle * sin(sectorAngleCircle);
			M3_vertices[valueOfArrayCircle].pos = glm::vec3(xCircle, yCircle, zCircle);

			xNormCircle = xCircle / radiusCircle;
			yNormCircle = yCircle / radiusCircle;
			zNormCircle = zCircle / radiusCircle;
			M3_vertices[valueOfArrayCircle].norm = glm::vec3(xNormCircle, yNormCircle, zNormCircle);

			valueOfArrayCircle++;
		}
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M3_indices.resize(3 * stackCountCricle * 2 * sectorCountCircle);

	int valueIfCircle1, valueIfCircle2, valueIfCircle3;

	for (int i = 0; i < stackCountCricle; ++i)
	{
		//Beginning of current stack
		currentStackCircle = i * (sectorCountCircle + 1);
		//Beginning of next stack
		nextStackCircle = currentStackCircle + sectorCountCircle + 1;
		for (int j = 0; j < sectorCountCircle; ++j, ++currentStackCircle, ++nextStackCircle)
		{
			//Two triangles per sector excluding first and last stacks
			if (i != 0)
			{
				M3_indices[valueOfSecondArrayCircle] = currentStackCircle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = nextStackCircle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = currentStackCircle + 1;
				valueOfSecondArrayCircle++;
				//valueIfCircle1 = k1Circle;
				//valueIfCircle2 = k2Circle;
				//valueIfCircle3 = k1Circle + 1;
			}

			if (i != (stackCountCricle - 1))
			{
				M3_indices[valueOfSecondArrayCircle] = currentStackCircle + 1;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = nextStackCircle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = nextStackCircle + 1;
				valueOfSecondArrayCircle++;
				//valueIfCircle1 = k1Circle + 1;
				//valueIfCircle2 = k2Circle;
				//valueIfCircle3 = k2Circle + 1;
			}

			/*firstCyl = M3_vertices[valueIfCircle1].pos;
			secondCyl = M3_vertices[valueIfCircle2].pos;
			thirdCyl = M3_vertices[valueIfCircle3].pos;

			if (M3_vertices[valueIfCircle1].norm[0] == NULL) {
				M3_vertices[valueIfCircle1].norm = surface_normal(firstCyl, secondCyl, thirdCyl);
			}
			if (M3_vertices[valueIfCircle2].norm[0] == NULL) {
				M3_vertices[valueIfCircle2].norm = surface_normal(secondCyl, thirdCyl, firstCyl);
			}
			if (M3_vertices[valueIfCircle3].norm[0] == NULL) {
				M3_vertices[valueIfCircle3].norm = surface_normal(thirdCyl, firstCyl, secondCyl);
			}*/
		}
	}





	const int slicesSpring = 10;//32;
	const int stepSpring = 3;
	float internalSpringRadius = 0.24f;
	float roundsSpring = 3.0f;
	int valueOfArraySpring = 0;
	int valueOfSecondArraySpring = 0;
	float heightSpring = roundsSpring;
	float totalSpringRadius = 0.8f;
	bool firstIterationSpring = true;

	float temp = 0.0f;
	float uSpringValue = 0.0f;
	float vSpringValue = 0.0f;
	float intermediateValueForXY = 0.0f;
	int valueToStoreForSecondsurface;

	//Add two comodity vertices + vertices for the spring + different vertices for the two plain surfaces (done to have different normal vectors)
	M4_vertices.resize(3 * ((slicesSpring * (roundsSpring * 360 + stepSpring + slicesSpring))) + (3 * 2) + (3 * 2 * (slicesSpring + 1)));
	//Indices for double spring rotation and for double plain surface
	M4_indices.resize(2 * 3 * ((slicesSpring * ((roundsSpring * 360 + stepSpring + 1) + slicesSpring + 1)) / stepSpring) + (3 * 2 * (slicesSpring + 1)));

	for (int i = -slicesSpring; i <= roundsSpring * 360 + stepSpring; i += stepSpring)
	{
		if (i + stepSpring > (roundsSpring * 360 + stepSpring)) {
			valueToStoreForSecondsurface = i;
		}
		for (int j = 0; j < slicesSpring; j++)
		{
			temp = (float(i) / 360) + (float(j) / slicesSpring) * (stepSpring / 360);
			temp = glm::max(0.0f, glm::min(float(roundsSpring), temp));
			//u in [0, 2*n*pi)
			uSpringValue = temp * M_PI * 2;
			//v in [0, 2*pi)
			vSpringValue = float(j) / slicesSpring * M_PI * 2;
			//Intermediate value = R + (r * cos(v))
			intermediateValueForXY = totalSpringRadius + internalSpringRadius * cos(vSpringValue);
			if (firstIterationSpring) {
				M4_vertices[valueOfArraySpring].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / roundsSpring);
				valueOfArraySpring++;
				firstIterationSpring = false;
			}
			//x(u,v) = (R + (r * cos(v))) * cos(u)
			//y(u,v) = (R + (r * cos(v))) * sin(u)
			//z(u,v) = (r * sin(v)) + (h * temp)/rounds
			M4_vertices[valueOfArraySpring].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / roundsSpring);
			valueOfArraySpring++;
		}
	}

	M4_vertices[valueOfArraySpring].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / roundsSpring);

	int valueSpring1, valueSpring2, valueSpring3;
	int valueOfArrayForPlainSurfaces = valueOfArraySpring + 2;
	int firstValueOfArrayForPlainSurfaces = valueOfArrayForPlainSurfaces;
	int secondValueOfArrayForPlainSurfaces = 0;
	firstIterationSpring = true;



	//First plain surface
	//Created new points in order to have a distinct surface and have normal vectors pointing perpendicular to it
	for (int j = 0; j < slicesSpring; j++)
	{
		temp = (float(-slicesSpring) / 360) + (float(j) / slicesSpring) * (stepSpring / 360);
		temp = glm::max(0.0f, glm::min(float(roundsSpring), temp));
		uSpringValue = temp * M_PI * 2;
		vSpringValue = float(j) / slicesSpring * M_PI * 2;
		intermediateValueForXY = totalSpringRadius + internalSpringRadius * cos(vSpringValue);
		if (firstIterationSpring) {
			M4_vertices[valueOfArrayForPlainSurfaces].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / roundsSpring);
			valueOfArrayForPlainSurfaces++;
			firstIterationSpring = false;
		}
		M4_vertices[valueOfArrayForPlainSurfaces].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / roundsSpring);
		valueOfArrayForPlainSurfaces++;
	}

	for (int i = 0; i < slicesSpring; i++)
	{
		//Cycle keeping one value unchanged
		M4_indices[valueOfSecondArraySpring] = firstValueOfArrayForPlainSurfaces + i;
		valueOfSecondArraySpring++;
		M4_indices[valueOfSecondArraySpring] = firstValueOfArrayForPlainSurfaces;
		valueOfSecondArraySpring++;
		M4_indices[valueOfSecondArraySpring] = firstValueOfArrayForPlainSurfaces + i + 1;
		valueOfSecondArraySpring++;

		valueSpring1 = firstValueOfArrayForPlainSurfaces + i;
		valueSpring2 = firstValueOfArrayForPlainSurfaces;
		valueSpring3 = firstValueOfArrayForPlainSurfaces + i + 1;

		firstNormalVector = M4_vertices[valueSpring1].pos;
		secondNormalVector = M4_vertices[valueSpring2].pos;
		thirdNormalVector = M4_vertices[valueSpring3].pos;

		//M4_vertices[valueSpring1].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//M4_vertices[valueSpring2].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//M4_vertices[valueSpring3].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		M4_vertices[valueSpring1].norm = -surface_normal(firstNormalVector, secondNormalVector, thirdNormalVector);
		M4_vertices[valueSpring2].norm = -surface_normal(secondNormalVector, thirdNormalVector, firstNormalVector);
		M4_vertices[valueSpring3].norm = -surface_normal(thirdNormalVector, firstNormalVector, secondNormalVector);
	}

	valueOfArrayForPlainSurfaces++;
	secondValueOfArrayForPlainSurfaces = valueOfArrayForPlainSurfaces;
	firstIterationSpring = true;
	
	//Second plain surface
	//Created new points in order to have a distinct surface and have normal vectors pointing perpendicular to it
	for (int j = 0; j < slicesSpring; j++)
	{
		temp = (float(valueToStoreForSecondsurface) / 360) + (float(j) / slicesSpring) * (stepSpring / 360);
		temp = glm::max(0.0f, glm::min(float(roundsSpring), temp));
		uSpringValue = temp * M_PI * 2;
		vSpringValue = float(j) / slicesSpring * M_PI * 2;
		intermediateValueForXY = totalSpringRadius + internalSpringRadius * cos(vSpringValue);
		if (firstIterationSpring) {
			M4_vertices[valueOfArrayForPlainSurfaces].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / roundsSpring);
			valueOfArrayForPlainSurfaces++;
			firstIterationSpring = false;
		}
		M4_vertices[valueOfArrayForPlainSurfaces].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / roundsSpring);
		valueOfArrayForPlainSurfaces++;
	}

	for (int i = 0; i < slicesSpring; i++)
	{
		//Cycle keeping one value unchanged
		M4_indices[valueOfSecondArraySpring] = secondValueOfArrayForPlainSurfaces + i;
		valueOfSecondArraySpring++;
		M4_indices[valueOfSecondArraySpring] = secondValueOfArrayForPlainSurfaces;
		valueOfSecondArraySpring++;
		M4_indices[valueOfSecondArraySpring] = secondValueOfArrayForPlainSurfaces + i + 1;
		valueOfSecondArraySpring++;

		valueSpring1 = secondValueOfArrayForPlainSurfaces + i;
		valueSpring2 = secondValueOfArrayForPlainSurfaces;
		valueSpring3 = secondValueOfArrayForPlainSurfaces + i + 1;

		firstNormalVector = M4_vertices[valueSpring1].pos;
		secondNormalVector = M4_vertices[valueSpring2].pos;
		thirdNormalVector = M4_vertices[valueSpring3].pos;

		//M4_vertices[valueSpring1].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		//M4_vertices[valueSpring2].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		//M4_vertices[valueSpring3].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		M4_vertices[valueSpring1].norm = surface_normal(firstNormalVector, secondNormalVector, thirdNormalVector);
		M4_vertices[valueSpring2].norm = surface_normal(secondNormalVector, thirdNormalVector, firstNormalVector);
		M4_vertices[valueSpring3].norm = surface_normal(thirdNormalVector, firstNormalVector, secondNormalVector);
	}



	//First part of the spring
	//for (int i = 0; i < ((slices * ((rounds * 360 + step) + slices - 1)) / step) + 1; i++)
	for (int i = 0; i < ((slicesSpring * ((roundsSpring * 360 + stepSpring) + slicesSpring - 1)) / stepSpring) + 1; i++)
	{
		//Take two value in the actual turn
		M4_indices[valueOfSecondArraySpring] = i;
		valueOfSecondArraySpring++;
		//And one after a full turn
		M4_indices[valueOfSecondArraySpring] = i + slicesSpring;
		valueOfSecondArraySpring++;
		M4_indices[valueOfSecondArraySpring] = i + 1;
		valueOfSecondArraySpring++;

		valueSpring1 = i;
		valueSpring2 = i + slicesSpring;
		valueSpring3 = i + 1;

		firstNormalVector = M4_vertices[valueSpring1].pos;
		secondNormalVector = M4_vertices[valueSpring2].pos;
		thirdNormalVector = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = -surface_normal(firstNormalVector, secondNormalVector, thirdNormalVector);
		M4_vertices[valueSpring2].norm = -surface_normal(secondNormalVector, thirdNormalVector, firstNormalVector);
		M4_vertices[valueSpring3].norm = -surface_normal(thirdNormalVector, firstNormalVector, secondNormalVector);
	}

	//Second part of the spring
	//for (int i = 0; i < ((slices * ((rounds * 360 + step) + slices - 1)) / step); i++)
	for (int i = 0; i < ((slicesSpring * ((roundsSpring * 360 + stepSpring) + slicesSpring - 1)) / stepSpring); i++)
	{
		//Take two value after a full turn
		M4_indices[valueOfSecondArraySpring] = i + slicesSpring + 1;
		valueOfSecondArraySpring++;
		M4_indices[valueOfSecondArraySpring] = i + slicesSpring;
		valueOfSecondArraySpring++;
		//And one in the actual
		M4_indices[valueOfSecondArraySpring] = i + 1;
		valueOfSecondArraySpring++;

		valueSpring1 = i + slicesSpring + 1;
		valueSpring2 = i + slicesSpring;
		valueSpring3 = i + 1;

		firstNormalVector = M4_vertices[valueSpring1].pos;
		secondNormalVector = M4_vertices[valueSpring2].pos;
		thirdNormalVector = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = -surface_normal(firstNormalVector, secondNormalVector, thirdNormalVector);
		M4_vertices[valueSpring2].norm = -surface_normal(secondNormalVector, thirdNormalVector, firstNormalVector);
		M4_vertices[valueSpring3].norm = -surface_normal(thirdNormalVector, firstNormalVector, secondNormalVector);
	}
}
	
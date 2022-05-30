// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;


void makeModels() {
	//// M1 : Cube
	int arrayOfCube = 0;
	int arrayOfNormCube = 0;
	int startingOfNormCube = 0;
	float sizeCube = 2.0f;
	M1_vertices.resize(3 * 4 * 6 * 3 * 100);

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices

	// Front face (z = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 1 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 1 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 0.0);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 0.0);
	arrayOfCube++;

	// Top face (y = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 2 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 2 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 1 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 1 * (0.5) / 4);
	arrayOfCube++;

	// Back face  (z = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 3 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 3 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 2 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 2 * (0.5) / 4);
	arrayOfCube++;

	// Left face (x = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(0.0, 3 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 3 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 2 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(0.0, 2 * (0.5) / 4);
	arrayOfCube++;

	// Right face (x = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 3 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(3 * (0.5) / 4, 3 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(3 * (0.5) / 4, 2 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 2 * (0.5) / 4);
	arrayOfCube++;

	// Bottom face(y = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 4 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 4 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(sizeCube, -sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 3 * (0.5) / 4);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-sizeCube, -sizeCube, -sizeCube);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 3 * (0.5) / 4);
	arrayOfCube++;

	// Resizes the indices array. Replace the values with the correct number of
	// indices (3 * number of triangles)
	int indicesCube = 0;
	int valueOfCubeIndices = 0;
	int startingOfFace = 0;
	M1_indices.resize(3 * 2 * 6 * 3 * 100);

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
	float heightCylinder = 2;
	//Center
	float xCylinder = 0, yCylinder = 0, zCylinder = -1;
	//float lengthInvC = 1.0f / radiusCylinder;
	float xNormCylinder, zNormCylinder;
	float radiusUVCylinder = 1 * (0.5) / 4;

	M2_vertices.resize(4 * ((slicesCylinder + 1) * 3));

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	M2_vertices[0].pos = glm::vec3(xCylinder, yCylinder + heightCylinder, zCylinder);
	M2_vertices[0].norm = glm::vec3(0.0, 1.0, 0.0);
	M2_vertices[0].UV = glm::vec2(0.5 + (1 * (0.5) / 4), 1 * (0.5) / 4);

	for (int i = 0; i < slicesCylinder; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), yCylinder + heightCylinder, zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
		M2_vertices[(i + 1)].norm = glm::vec3(0.0, 1.0, 0.0);
		M2_vertices[(i + 1)].UV = glm::vec2((0.5 + (1 * (0.5) / 4)) + (1 * (0.5) / 4) * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), (0.5 / 4) + (1 * (0.5) / 4) * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
	}

	M2_vertices[(slicesCylinder + 1)].pos = glm::vec3(xCylinder, yCylinder - heightCylinder, zCylinder);
	M2_vertices[(slicesCylinder + 1)].norm = glm::vec3(0.0, -1.0, 0.0);
	M2_vertices[(slicesCylinder + 1)].UV = glm::vec2(0.5 + (3 * (0.5) / 4), 1 * (0.5) / 4);

	for (int i = slicesCylinder + 1; i < (2 * slicesCylinder) + 1; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), yCylinder - heightCylinder, zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
		M2_vertices[(i + 1)].norm = glm::vec3(0.0, -1.0, 0.0);
		M2_vertices[(i + 1)].UV = glm::vec2((0.5 + (3 * (0.5) / 4)) + (1 * (0.5) / 4) * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), (0.5 / 4) + (1 * (0.5) / 4) * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
	}

	float valueUVCylinder = 0.0f;

	//One full rotation for the upper part
	for (int i = (2 * slicesCylinder) + 1; i < (slicesCylinder * 3) + 2; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)), yCylinder + heightCylinder, zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)));
		xNormCylinder = radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI));
		zNormCylinder = radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI));
		M2_vertices[(i + 1)].norm = glm::vec3(xNormCylinder, 0.0, zNormCylinder);
		M2_vertices[(i + 1)].UV = glm::vec2(1.0f - float((valueUVCylinder / float(slicesCylinder)) / 2.0f), 0.5f / 2);
		valueUVCylinder++;
	}

	valueUVCylinder = 0;

	int valueOfCylinder = (slicesCylinder * 3) + 1;

	//One full rotation for the lower part
	for (int i = (slicesCylinder * 3) + 2; i < (slicesCylinder * 4) + 3; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(xCylinder + radiusCylinder * cos(((float)valueOfCylinder / slicesCylinder) * (2.0 * M_PI)), yCylinder - heightCylinder, zCylinder + radiusCylinder * sin(((float)valueOfCylinder / slicesCylinder) * (2.0 * M_PI)));
		xNormCylinder = radiusCylinder * cos(((float)valueOfCylinder / slicesCylinder) * (2.0 * M_PI));
		zNormCylinder = radiusCylinder * sin(((float)valueOfCylinder / slicesCylinder) * (2.0 * M_PI));
		M2_vertices[(i + 1)].norm = glm::vec3(xNormCylinder, 0.0, zNormCylinder);
		M2_vertices[(i + 1)].UV = glm::vec2(1.0f - float((valueUVCylinder / float(slicesCylinder)) / 2.0f), 0.5f);
		valueUVCylinder++;
		valueOfCylinder++;
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(3 * 2 * slicesCylinder * 2);

	int counterCylinder = 0;
	int counter2Cylinder = 0;

	for (int i = 0; i < slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = 0;
		M2_indices[(i * 3) + 1] = i + 1;
		M2_indices[(i * 3) + 2] = ((i + 1) % slicesCylinder) + 1;
	}

	counterCylinder = slicesCylinder + 1;

	for (int i = slicesCylinder; i < 2 * slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = slicesCylinder + 1;
		M2_indices[(i * 3) + 1] = counterCylinder + 1;
		if ((i + 1) == (2 * slicesCylinder)) {
			M2_indices[(i * 3) + 2] = ((counterCylinder + 1) % ((2 * slicesCylinder) + 1)) + slicesCylinder + 2;
		}
		else {
			M2_indices[(i * 3) + 2] = ((counterCylinder + 1) % ((2 * slicesCylinder) + 1)) + 1;
		}
		counterCylinder++;
	}

	counterCylinder = (2 * slicesCylinder) + 1;

	for (int i = 2 * slicesCylinder; i < (3 * slicesCylinder) + 1; i++) {
		M2_indices[(i * 3) + 0] = counterCylinder + 1;
		M2_indices[(i * 3) + 1] = counterCylinder + 1 + 1;
		//M2_indices[(i * 3) + 1] = (counter + 1) + 1;
		M2_indices[(i * 3) + 2] = (slicesCylinder + 1) + counterCylinder + 1;
		counterCylinder++;
	}

	counterCylinder = (3 * slicesCylinder) + 2;
	counter2Cylinder = (2 * slicesCylinder) + 1;

	for (int i = 3 * slicesCylinder; i < 4 * slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = counterCylinder + 1;
		M2_indices[(i * 3) + 1] = counterCylinder + 1 + 1;
		M2_indices[(i * 3) + 2] = (counter2Cylinder + 1) + 1;
		counter2Cylinder++;
		counterCylinder++;
	}

}
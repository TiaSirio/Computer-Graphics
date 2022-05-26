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
	//glm::vec3 v1 = vertexP[1] - vertexP[0];
	//glm::vec3 v2 = vertexP[2] - vertexP[0];
	glm::vec3 v1 = vector1 - vector0;
	glm::vec3 v2 = vector2 - vector0;
	glm::vec3 surfNormal = normalize(cross(v1, v2));
	//surfNormal *= glm::sign(glm::dot(surfNormal, vertexN[0] + vertexN[1] + vertexN[2]));
	return surfNormal;
}

void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

	float size = 1.0f;
	int arrayOfCube = 0;
	int arrayOfNorm = 0;
	int startingOfNorm = 0;
	M1_vertices.resize(3 * 4 * 6 * 3 * 100);

	//Riguardare correttezza vettori
	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices

	// Bottom face(y = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, -size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, -size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, -size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	arrayOfCube++;

	//M1_vertices[arrayOfCube - 1].norm = surface_normal(2, 0, 1);
	//M1_vertices[arrayOfCube - 2].norm = surface_normal(2, 0, 1);
	//M1_vertices[arrayOfCube - 3].norm = surface_normal(2, 0, 1);

	M1_vertices[arrayOfCube].pos = glm::vec3(-size, -size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Top face (y = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Back face  (z = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, -size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, -size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Front face (z = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, -size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, -size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Right face (x = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(size, -size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, -size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(size, size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	arrayOfCube++;

	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos);
	M1_vertices[arrayOfCube - 4].norm = surface_normal(M1_vertices[arrayOfCube - 4].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);

	M1_vertices[arrayOfCube - 1].norm = surface_normal(M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos);
	M1_vertices[arrayOfCube - 2].norm = surface_normal(M1_vertices[arrayOfCube - 2].pos, M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos);
	M1_vertices[arrayOfCube - 3].norm = surface_normal(M1_vertices[arrayOfCube - 3].pos, M1_vertices[arrayOfCube - 1].pos, M1_vertices[arrayOfCube - 2].pos);

	// Left face (x = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, -size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, -size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, size, -size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-size, size, size);
	//M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
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
	M1_indices.resize(3 * 2 * 6 * 3 * 100);

	for (int i = 0; i < 6; i++) {
		startingOfFace = indicesCube;
		for (int j = 0; j < 6; j++) {
			if (j < 3) {
				M1_indices[valueOfCubeIndices] = indicesCube;
				indicesCube++;
			}
			else if (j == 5) {
				M1_indices[valueOfCubeIndices] = startingOfFace;
				indicesCube = startingOfFace + 4;
			}
			else {
				M1_indices[valueOfCubeIndices] = indicesCube - 1;
				indicesCube++;
			}
			valueOfCubeIndices++;
		}
	}





	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.
	int NSlice = 36;
	float radius = 1;
	float height = 1;
	//Center
	float cx = 0, cy = 0, cz = -2;
	float lengthInvC = 1.0f / radius;
	float normCx, normCz;

	M2_vertices.resize(4 * ((NSlice + 1) * 3));

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	M2_vertices[0].pos = glm::vec3(cx, cy + height, cz);
	//M2_vertices[0].norm = glm::vec3(0.0, 1.0, 0.0);

	for (int i = 0; i < NSlice; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy + height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
		//M2_vertices[(i + 1)].norm = glm::vec3(0.0, 1.0, 0.0);
	}

	M2_vertices[(NSlice + 1)].pos = glm::vec3(cx, cy - height, cz);
	//M2_vertices[(NSlice + 1)].norm = glm::vec3(0.0, -1.0, 0.0);

	for (int i = NSlice + 1; i < (2 * NSlice) + 1; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy - height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
		//M2_vertices[(i + 1)].norm = glm::vec3(0.0, -1.0, 0.0);
	}



	for (int i = (2 * NSlice) + 1; i < (NSlice * 3) + 1; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy + height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
		//normCx = radius * cos(((float)i / NSlice) * (2.0 * M_PI));
		//normCz = radius * sin(((float)i / NSlice) * (2.0 * M_PI));
		normCx = cos(((float)i / NSlice) * (2.0 * M_PI));
		normCz = sin(((float)i / NSlice) * (2.0 * M_PI));
		M2_vertices[(i + 1)].norm = glm::vec3(normCx, 0.0, normCz);
	}

	for (int i = (NSlice * 3) + 1; i < (NSlice * 4) + 1; i++) {
		M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy - height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
		//normCx = radius * cos(((float)i / NSlice) * (2.0 * M_PI));
		//normCz = radius * sin(((float)i / NSlice) * (2.0 * M_PI));
		normCx = cos(((float)i / NSlice) * (2.0 * M_PI));
		normCz = sin(((float)i / NSlice) * (2.0 * M_PI));
		M2_vertices[(i + 1)].norm = glm::vec3(normCx, 0.0, normCz);
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(3 * 2 * NSlice * 2);

	int counter = 0;
	int counter2 = 0;

	glm::vec3 firstCyl, secondCyl, thirdCyl;
	int valueIfCyl = 0;

	for (int i = 0; i < NSlice; i++) {
		M2_indices[(i * 3) + 0] = 0;
		M2_indices[(i * 3) + 1] = i + 1;
		M2_indices[(i * 3) + 2] = ((i + 1) % NSlice) + 1;

		firstCyl = M2_vertices[0].pos;
		secondCyl = M2_vertices[i + 1].pos;
		thirdCyl = M2_vertices[((i + 1) % NSlice) + 1].pos;

		M2_vertices[0].norm = -surface_normal(firstCyl, secondCyl, thirdCyl);
		M2_vertices[i + 1].norm = -surface_normal(secondCyl, thirdCyl, firstCyl);
		M2_vertices[((i + 1) % NSlice) + 1].norm = -surface_normal(thirdCyl, firstCyl, secondCyl);
	}

	counter = NSlice + 1;

	for (int i = NSlice; i < 2 * NSlice; i++) {
		M2_indices[(i * 3) + 0] = NSlice + 1;
		M2_indices[(i * 3) + 1] = counter + 1;
		if ((i + 1) == (2 * NSlice)) {
			M2_indices[(i * 3) + 2] = ((counter + 1) % ((2 * NSlice) + 1)) + NSlice + 2;
			valueIfCyl = ((counter + 1) % ((2 * NSlice) + 1)) + NSlice + 2;
		}
		else {
			M2_indices[(i * 3) + 2] = ((counter + 1) % ((2 * NSlice) + 1)) + 1;
			valueIfCyl = ((counter + 1) % ((2 * NSlice) + 1)) + 1;
		}

		firstCyl = M2_vertices[NSlice + 1].pos;
		secondCyl = M2_vertices[counter + 1].pos;
		thirdCyl = M2_vertices[valueIfCyl].pos;

		M2_vertices[NSlice + 1].norm = surface_normal(firstCyl, secondCyl, thirdCyl);
		M2_vertices[counter + 1].norm = surface_normal(secondCyl, thirdCyl, firstCyl);
		M2_vertices[valueIfCyl].norm = surface_normal(thirdCyl, firstCyl, secondCyl);

		counter++;
	}
	
	counter = (2 * NSlice) + 1;

	for (int i = 2 * NSlice; i < 3 * NSlice; i++) {
		M2_indices[(i * 3) + 0] = counter + 1;
		if (counter != (3 * NSlice)) {
			M2_indices[(i * 3) + 1] = counter + 1 + 1;
			valueIfCyl = counter + 1 + 1;
		}
		else {
			M2_indices[(i * 3) + 1] = (2 * NSlice) + 2;
			valueIfCyl = (2 * NSlice) + 2;
		}
		M2_indices[(i * 3) + 2] = NSlice + counter + 1;

		//firstCyl = M2_vertices[counter + 1].pos;
		//secondCyl = M2_vertices[valueIfCyl].pos;
		//thirdCyl = M2_vertices[NSlice + counter + 1].pos;

		//M2_vertices[counter + 1].norm = surface_normal(firstCyl, secondCyl, thirdCyl);
		//M2_vertices[valueIfCyl].norm = surface_normal(secondCyl, thirdCyl, firstCyl);
		//M2_vertices[NSlice + counter + 1].norm = surface_normal(thirdCyl, firstCyl, secondCyl);

		counter++;
	}

	counter = (3 * NSlice) + 1;
	counter2 = (2 * NSlice) + 1;

	for (int i = 3 * NSlice; i < 4 * NSlice; i++) {
		M2_indices[(i * 3) + 0] = counter + 1;
		if (counter == (4 * NSlice)) {
			M2_indices[(i * 3) + 1] = (2 * NSlice) + 2;
			valueIfCyl = (2 * NSlice) + 2;
		}
		else {
			M2_indices[(i * 3) + 1] = ((counter + 1) % ((4 * NSlice) + 1)) + 1;
			valueIfCyl = ((counter + 1) % ((4 * NSlice) + 1)) + 1;
		}
		M2_indices[(i * 3) + 2] = (counter2 + 1) + 1;

		//firstCyl = M2_vertices[counter + 1].pos;
		//secondCyl = M2_vertices[valueIfCyl].pos;
		//thirdCyl = M2_vertices[(counter2 + 1) + 1].pos;

		//M2_vertices[counter + 1].norm = (M2_vertices[counter + 1].norm + surface_normal(firstCyl, secondCyl, thirdCyl)) * 0.5f;
		//M2_vertices[valueIfCyl].norm = (M2_vertices[valueIfCyl].norm + surface_normal(secondCyl, thirdCyl, firstCyl)) * 0.5f;
		//M2_vertices[(counter2 + 1) + 1].norm = (M2_vertices[(counter2 + 1) + 1].norm + surface_normal(thirdCyl, firstCyl, secondCyl)) * 0.5f;

		counter2++;
		counter++;
	}





	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	float xCircle, yCircle, zCircle, xyCircle;
	float radiusCircle = 2.0f;
	float stackCount = 24.0f;
	float sectorCount = 72.0f;
	float sectorStep = 2 * M_PI / sectorCount;
	float stackStep = M_PI / stackCount;
	float sectorAngle, stackAngle;
	int valueOfArrayCircle = 0;
	int valueOfSecondArrayCircle = 0;
	int k1Circle, k2Circle;
	float xNorm, yNorm, zNorm;
	float lengthInv = 1.0f / radiusCircle;

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	M3_vertices.resize(3 * stackCount * sectorCount * 2);

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xyCircle = radiusCircle * cos(stackAngle);             // r * cos(u)
		zCircle = radiusCircle * sin(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			xCircle = xyCircle * cos(sectorAngle);             // r * cos(u) * cos(v)
			yCircle = xyCircle * sin(sectorAngle);             // r * cos(u) * sin(v)
			M3_vertices[valueOfArrayCircle].pos = glm::vec3(xCircle, yCircle, zCircle);

			xNorm = xCircle * lengthInv;
			yNorm = yCircle * lengthInv;
			zNorm = zCircle * lengthInv;
			M3_vertices[valueOfArrayCircle].norm = glm::vec3(xNorm, yNorm, zNorm);

			valueOfArrayCircle++;
		}
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M3_indices.resize(3 * stackCount * 2 * sectorCount);

	int valueIfCircle1, valueIfCircle2, valueIfCircle3;

	for (int i = 0; i < stackCount; ++i)
	{
		k1Circle = i * (sectorCount + 1);     // beginning of current stack
		k2Circle = k1Circle + sectorCount + 1;      // beginning of next stack
		for (int j = 0; j < sectorCount; ++j, ++k1Circle, ++k2Circle)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				M3_indices[valueOfSecondArrayCircle] = k1Circle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = k2Circle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = k1Circle + 1;
				valueOfSecondArrayCircle++;
				//valueIfCircle1 = k1Circle;
				//valueIfCircle2 = k2Circle;
				//valueIfCircle3 = k1Circle + 1;
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				M3_indices[valueOfSecondArrayCircle] = k1Circle + 1;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = k2Circle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = k2Circle + 1;
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





	const int slices = 10;//32;
	const int step = 3;
	float internalSpringRadius = 0.24f;
	float rounds = 3.0f;
	int valueOfArray = 0;
	int valueOfSecondArray = 0;
	float heightSpring = rounds;
	float totalSpringRadius = 0.8f;
	bool firstIteration = true;

	float temp = 0.0f;
	float uSpringValue = 0.0f;
	float vSpringValue = 0.0f;
	float intermediateValueForXY = 0.0f;
	int valueToStoreForSecondsurface;

	M4_vertices.resize(3 * slices * (rounds * 360 + step + 2) * 3);
	M4_indices.resize(2 * 3 * ((slices * (rounds * 360 + step + slices)) / step) * slices * 3);

	for (int i = -slices; i <= rounds * 360 + step; i += step)
	{
		if (i + step > (rounds * 360 + step)) {
			valueToStoreForSecondsurface = i;
		}
		for (int j = 0; j < slices; j++)
		{
			temp = (float(i) / 360) + (float(j) / slices) * (step / 360);
			temp = glm::max(0.0f, glm::min(float(rounds), temp));
			uSpringValue = temp * M_PI * 2;
			vSpringValue = float(j) / slices * M_PI * 2;
			intermediateValueForXY = totalSpringRadius + internalSpringRadius * cos(vSpringValue);
			if (firstIteration) {
				M4_vertices[valueOfArray].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / rounds);
				valueOfArray++;
				firstIteration = false;
			}
			M4_vertices[valueOfArray].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / rounds);
			valueOfArray++;
		}
	}

	M4_vertices[valueOfArray].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / rounds);

	int valueSpring1, valueSpring2, valueSpring3;
	int valueOfArrayForPlainSurfaces = valueOfArray + 2;
	int firstValueOfArrayForPlainSurfaces = valueOfArrayForPlainSurfaces;
	int secondValueOfArrayForPlainSurfaces = 0;
	firstIteration = true;


	//First plain surface
	for (int j = 0; j < slices; j++)
	{
		temp = (float(-slices) / 360) + (float(j) / slices) * (step / 360);
		temp = glm::max(0.0f, glm::min(float(rounds), temp));
		uSpringValue = temp * M_PI * 2;
		vSpringValue = float(j) / slices * M_PI * 2;
		intermediateValueForXY = totalSpringRadius + internalSpringRadius * cos(vSpringValue);
		if (firstIteration) {
			M4_vertices[valueOfArrayForPlainSurfaces].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / rounds);
			valueOfArrayForPlainSurfaces++;
			firstIteration = false;
		}
		M4_vertices[valueOfArrayForPlainSurfaces].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / rounds);
		valueOfArrayForPlainSurfaces++;
	}

	for (int i = 0; i < slices; i++)
	{
		M4_indices[valueOfSecondArray] = firstValueOfArrayForPlainSurfaces + i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = firstValueOfArrayForPlainSurfaces;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = firstValueOfArrayForPlainSurfaces + i + 1;
		valueOfSecondArray++;

		valueSpring1 = firstValueOfArrayForPlainSurfaces + i;
		valueSpring2 = firstValueOfArrayForPlainSurfaces;
		valueSpring3 = firstValueOfArrayForPlainSurfaces + i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		//M4_vertices[valueSpring1].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//M4_vertices[valueSpring2].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//M4_vertices[valueSpring3].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		M4_vertices[valueSpring1].norm = -surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = -surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = -surface_normal(thirdCyl, firstCyl, secondCyl);
	}

	valueOfArrayForPlainSurfaces++;
	secondValueOfArrayForPlainSurfaces = valueOfArrayForPlainSurfaces;
	firstIteration = true;

	
	//Second plain surface
	for (int j = 0; j < slices; j++)
	{
		temp = (float(valueToStoreForSecondsurface) / 360) + (float(j) / slices) * (step / 360);
		temp = glm::max(0.0f, glm::min(float(rounds), temp));
		uSpringValue = temp * M_PI * 2;
		vSpringValue = float(j) / slices * M_PI * 2;
		intermediateValueForXY = totalSpringRadius + internalSpringRadius * cos(vSpringValue);
		if (firstIteration) {
			M4_vertices[valueOfArrayForPlainSurfaces].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / rounds);
			valueOfArrayForPlainSurfaces++;
			firstIteration = false;
		}
		M4_vertices[valueOfArrayForPlainSurfaces].pos = glm::vec3(intermediateValueForXY * cos(uSpringValue), intermediateValueForXY * sin(uSpringValue), internalSpringRadius * sin(vSpringValue) + heightSpring * temp / rounds);
		valueOfArrayForPlainSurfaces++;
	}

	for (int i = 0; i < slices; i++)
	{
		M4_indices[valueOfSecondArray] = secondValueOfArrayForPlainSurfaces + i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = secondValueOfArrayForPlainSurfaces;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = secondValueOfArrayForPlainSurfaces + i + 1;
		valueOfSecondArray++;

		valueSpring1 = secondValueOfArrayForPlainSurfaces + i;
		valueSpring2 = secondValueOfArrayForPlainSurfaces;
		valueSpring3 = secondValueOfArrayForPlainSurfaces + i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		//M4_vertices[valueSpring1].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		//M4_vertices[valueSpring2].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		//M4_vertices[valueSpring3].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		M4_vertices[valueSpring1].norm = surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = surface_normal(thirdCyl, firstCyl, secondCyl);
	}



	/*for (int i = 1; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = 0;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;

		valueSpring1 = i;
		valueSpring2 = 0;
		valueSpring3 = i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = surface_normal(thirdCyl, firstCyl, secondCyl);
	}*/


	//First part of the spring
	//for (int i = 0; i < ((slices * ((rounds * 360 + step) + slices - 1)) / step) + 1; i++)
	//Commented for, are valid for 10 slices
	for (int i = 0; i < ((slices * ((rounds * 360 + step) + slices - 1)) / step) + 1; i++)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;

		valueSpring1 = i;
		valueSpring2 = i + slices;
		valueSpring3 = i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = -surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = -surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = -surface_normal(thirdCyl, firstCyl, secondCyl);
	}


	//Second part of the spring
	//for (int i = 0; i < ((slices * ((rounds * 360 + step) + slices - 1)) / step); i++)
	for (int i = 0; i < ((slices * ((rounds * 360 + step) + slices - 1)) / step); i++)
	{
		M4_indices[valueOfSecondArray] = i + slices + 1;
		//std::cout << "\n\n";
		//std::cout << i + slices + 1;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;

		valueSpring1 = i + slices + 1;
		valueSpring2 = i + slices;
		valueSpring3 = i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = -surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = -surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = -surface_normal(thirdCyl, firstCyl, secondCyl);
	}
	//std::cout << "Test \n";
	//std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + slices + 1;
	//std::cout << valueOfArray;
	//std::cout << "\n";
	//std::cout << "Test \n";
	//std::cout << valueOfArray;

	/*for (int i = 1; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + slices + i;
		//std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << "\n";
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + slices + i + 1;
		valueOfSecondArray++;

		valueSpring1 = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		valueSpring2 = ((slices * (rounds * 360 + step + slices - 1)) / step) - slices + i;
		valueSpring3 = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = -surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = -surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = -surface_normal(thirdCyl, firstCyl, secondCyl);
	}*/
}
	
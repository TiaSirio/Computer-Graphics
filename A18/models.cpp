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

void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

	int arrayOfCube = 0;
	int arrayOfNorm = 0;
	int startingOfNorm = 0;
	M1_vertices.resize(3 * 4 * 6 * 3 * 100);

	//Riguardare correttezza vettori
	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices

	// Bottom face(y = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
	arrayOfCube++;

	// Top face (y = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	arrayOfCube++;

	// Back face  (z = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
	arrayOfCube++;

	// Front face (z = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
	arrayOfCube++;

	// Right face (x = 1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
	arrayOfCube++;

	// Left face (x = -1.0f)
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, 1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, -1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
	arrayOfCube++;
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f,  1.0f);
	M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
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
	M2_vertices[0].norm = glm::vec3(0.0, 1.0, 0.0);
	//M2_vertices[0] = cx;
	//M2_vertices[1] = cy + height;
	//M2_vertices[2] = cz;

	for (int i = 0; i < NSlice; i++) {
		//M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
		//M2_vertices[((i + 1) * 3) + 1] = cy + height; //y of the vertex
		//M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
		M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy + height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
		M2_vertices[(i + 1)].norm = glm::vec3(0.0, 1.0, 0.0);
	}

	//M2_vertices[((NSlice + 1) * 3) + 0] = cx;
	//M2_vertices[((NSlice + 1) * 3) + 1] = cy - height;
	//M2_vertices[((NSlice + 1) * 3) + 2] = cz;
	M2_vertices[(NSlice + 1)].pos = glm::vec3(cx, cy - height, cz);
	M2_vertices[(NSlice + 1)].norm = glm::vec3(0.0, -1.0, 0.0);

	for (int i = NSlice + 1; i < (2 * NSlice) + 1; i++) {
		//M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
		//M2_vertices[((i + 1) * 3) + 1] = cy - height; //y of the vertex
		//M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
		M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy - height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
		M2_vertices[(i + 1)].norm = glm::vec3(0.0, -1.0, 0.0);
	}



	for (int i = (2 * NSlice) + 1; i < (NSlice * 3) + 1; i++) {
		//M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
		//M2_vertices[((i + 1) * 3) + 1] = cy + height; //y of the vertex
		//M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
		M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy + height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
		normCx = radius * cos(((float)i / NSlice) * (2.0 * M_PI));
		normCz = radius * sin(((float)i / NSlice) * (2.0 * M_PI));
		M2_vertices[(i + 1)].norm = glm::vec3(normCx, 0.0, normCz);
	}

	for (int i = (NSlice * 3) + 1; i < (NSlice * 4) + 1; i++) {
		//M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
		//M2_vertices[((i + 1) * 3) + 1] = cy - height; //y of the vertex
		//M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
		M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy - height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
		normCx = radius * cos(((float)i / NSlice) * (2.0 * M_PI));
		normCz = radius * sin(((float)i / NSlice) * (2.0 * M_PI));
		M2_vertices[(i + 1)].norm = glm::vec3(normCx, 0.0, normCz);
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(3 * 2 * NSlice * 2);

	int counter = 0;
	int counter2 = 0;

	for (int i = 0; i < NSlice; i++) {
		M2_indices[(i * 3) + 0] = 0;
		M2_indices[(i * 3) + 1] = i + 1;
		M2_indices[(i * 3) + 2] = ((i + 1) % NSlice) + 1;
	}

	counter = NSlice + 1;

	for (int i = NSlice; i < 2 * NSlice; i++) {
		M2_indices[(i * 3) + 0] = NSlice + 1;
		M2_indices[(i * 3) + 1] = counter + 1;
		if ((i + 1) == (2 * NSlice)) {
			M2_indices[(i * 3) + 2] = ((counter + 1) % ((2 * NSlice) + 1)) + NSlice + 2;
		}
		else {
			M2_indices[(i * 3) + 2] = ((counter + 1) % ((2 * NSlice) + 1)) + 1;
		}
		counter++;
	}
	
	counter = (2 * NSlice) + 1;

	for (int i = 2 * NSlice; i < 3 * NSlice; i++) {
		M2_indices[(i * 3) + 0] = counter + 1;
		if (counter != (3 * NSlice)) {
			M2_indices[(i * 3) + 1] = counter + 1 + 1;
		}
		else {
			M2_indices[(i * 3) + 1] = (2 * NSlice) + 2;
		}
		M2_indices[(i * 3) + 2] = NSlice + counter + 1;
		counter++;
	}

	counter = (3 * NSlice) + 1;
	counter2 = (2 * NSlice) + 1;

	for (int i = 3 * NSlice; i < 4 * NSlice; i++) {
		M2_indices[(i * 3) + 0] = counter + 1;
		if (counter == (4 * NSlice)) {
			M2_indices[(i * 3) + 1] = (2 * NSlice) + 2;
		}
		else {
			M2_indices[(i * 3) + 1] = ((counter + 1) % ((4 * NSlice) + 1)) + 1;
		}
		M2_indices[(i * 3) + 2] = (counter2 + 1) + 1;
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
			//M3_vertices[(valueOfArrayCircle * 3) + 0] = xCircle;
			//M3_vertices[(valueOfArrayCircle * 3) + 1] = yCircle;
			//M3_vertices[(valueOfArrayCircle * 3) + 2] = zCircle;
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
			}
		}
	}





	//// M4 : Spring
	// Replace the code below, that creates a simple octahedron, with the one to create a spring.
	const int slices = 32;
	const int step = 3;
	float thickness = 0.24f;
	float rounds = 2.0f;
	int valueOfArray = 0;
	int valueOfSecondArray = 0;
	float heightSpring = rounds;
	float radiusSpring = 0.8f;
	bool firstIteration = true;
	bool lastIteration = false;

	float t = 0.0f;
	float a1 = 0.0f;
	float a2 = 0.0f;
	float d = 0.0f;

	M4_vertices.resize(3 * slices * (rounds * 360 + step + 2));
	M4_indices.resize(2 * 3 * ((slices * (rounds * 360 + step + slices - 2)) / step) * slices);


	/*
	for (int i = -slices; i <= rounds * 360 + step; i += step)
	{
		for (int j = 0; j < slices; j++)
		{
			t = float(i) / 360 + float(j) / slices * step / 360;
			if (float(rounds) <= t) {
				if (float(rounds) >= 0.0f) {
					t = float(rounds);
				}
				else {
					t = 0.0f;
				}
			}
			else {
				if (t >= 0.0f) {
					t = t;
				}
				else {
					t = 0.0f;
				}
			}
			a1 = t * M_PI * 2;
			a2 = float(j) / slices * M_PI * 2;
			d = radiusSpring + thickness * cos(a2);
			if (firstIteration) {
				//M4_vertices[0] = d * cos(a1);
				//M4_vertices[1] = d * sin(a1);
				//M4_vertices[2] = thickness * sin(a2) + heightSpring * t / rounds;
				M4_vertices[0].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
				M4_vertices[0].norm = glm::vec3(0.0, -1.0, 0.0);
				//M4_vertices[0].norm = glm::vec3(0.0, 1.0, 0.0);
				valueOfArray++;
				firstIteration = false;
			}
			//M4_vertices[(valueOfArray * 3) + 0] = d * cos(a1);
			//M4_vertices[(valueOfArray * 3) + 1] = d * sin(a1);
			//M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;
			M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
			//M4_vertices[valueOfArray].norm = glm::vec3(cos(a1), sin(a1), thickness * sin(a2));
			//M4_vertices[valueOfArray].norm = glm::vec3(d * cos(a2), d * sin(a2), sin(a2));
			M4_vertices[valueOfArray].norm = glm::vec3(cos(a1), sin(a1), thickness * sin(a2));
			valueOfArray++;
		}
	}

	//M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;
	M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
	M4_vertices[valueOfArray].norm = glm::vec3(0.0, 1.0, 0.0);
	//M4_vertices[valueOfArray].norm = glm::vec3(0.0, -1.0, 0.0);
	*/


	for (int i = -slices; i <= rounds * 360 + step; i += step)
	{
		if (i + step > rounds * 360 + step) {
			lastIteration = true;
		}
		for (int j = 0; j < slices; j++)
		{
			t = float(i) / 360 + float(j) / slices * step / 360;
			if (float(rounds) <= t) {
				if (float(rounds) >= 0.0f) {
					t = float(rounds);
				}
				else {
					t = 0.0f;
				}
			}
			else {
				if (t >= 0.0f) {
					t = t;
				}
				else {
					t = 0.0f;
				}
			}
			a1 = t * M_PI * 2;
			a2 = float(j) / slices * M_PI * 2;
			d = radiusSpring + thickness * cos(a2);
			if (firstIteration) {
				//M4_vertices[0] = d * cos(a1);
				//M4_vertices[1] = d * sin(a1);
				//M4_vertices[2] = thickness * sin(a2) + heightSpring * t / rounds;
				M4_vertices[0].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
				M4_vertices[0].norm = glm::vec3(0.0, -1.0, 0.0);
				//M4_vertices[0].norm = glm::vec3(0.0, 1.0, 0.0);
				valueOfArray++;
				firstIteration = false;
			}
			//M4_vertices[(valueOfArray * 3) + 0] = d * cos(a1);
			//M4_vertices[(valueOfArray * 3) + 1] = d * sin(a1);
			//M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;
			M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
			//M4_vertices[valueOfArray].norm = glm::vec3(cos(a1), sin(a1), thickness * sin(a2));
			//M4_vertices[valueOfArray].norm = glm::vec3(d * cos(a2), d * sin(a2), sin(a2));
			M4_vertices[valueOfArray].norm = glm::vec3(cos(a1), sin(a1), thickness * sin(a2));
			valueOfArray++;
		}
		firstIteration = false;
	}

	//M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;
	M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
	M4_vertices[valueOfArray].norm = glm::vec3(0.0, 1.0, 0.0);
	//M4_vertices[valueOfArray].norm = glm::vec3(0.0, -1.0, 0.0);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	for (int i = 1; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = 0;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 2)) / step); ++i)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 2)) / step) - 1; ++i)
	{
		M4_indices[valueOfSecondArray] = i + slices + 1;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	for (int i = 1; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 2)) / step) + i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = valueOfArray;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 2)) / step) + i + 1;
		valueOfSecondArray++;
	}

}
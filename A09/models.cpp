// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

void makeModels() {
	//// M1 : Cube
	// Replace the code below, that creates a simple square, with the one to create a cube.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)

	float sizeCube = 1.0f;

	M1_vertices.resize(3 * 4 * 6);

	//First vertex of M1
	M1_vertices[0] = -sizeCube;
	M1_vertices[1] = -sizeCube;
	M1_vertices[2] = -sizeCube;

	//Second vertex of M1
	M1_vertices[3] = -sizeCube;
	M1_vertices[4] = -sizeCube;
	M1_vertices[5] = sizeCube;

	//Third vertex of M1
	M1_vertices[6] = -sizeCube;
	M1_vertices[7] = sizeCube;
	M1_vertices[8] = sizeCube;

	//Fourth vertex of M1
	M1_vertices[9] = -sizeCube;
	M1_vertices[10] = sizeCube;
	M1_vertices[11] = -sizeCube;

	//Fifth vertex of M1
	M1_vertices[12] = sizeCube;
	M1_vertices[13] = -sizeCube;
	M1_vertices[14] = -sizeCube;

	//Sixth vertex of M1
	M1_vertices[15] = sizeCube;
	M1_vertices[16] = -sizeCube;
	M1_vertices[17] = sizeCube;

	//Seventh vertex of M1
	M1_vertices[18] = sizeCube;
	M1_vertices[19] = sizeCube;
	M1_vertices[20] = sizeCube;

	//Eigth vertex of M1
	M1_vertices[21] = sizeCube;
	M1_vertices[22] = sizeCube;
	M1_vertices[23] = -sizeCube;

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M1_indices.resize(3 * 2 * 6);

	//First square
	M1_indices[0] = 0;
	M1_indices[1] = 1;
	M1_indices[2] = 2;
	M1_indices[3] = 2;
	M1_indices[4] = 3;
	M1_indices[5] = 0;

	//Second square
	M1_indices[6] = 0;
	M1_indices[7] = 3;
	M1_indices[8] = 4;
	M1_indices[9] = 4;
	M1_indices[10] = 3;
	M1_indices[11] = 7;

	//Third square
	M1_indices[12] = 5;
	M1_indices[13] = 6;
	M1_indices[14] = 7;
	M1_indices[15] = 7;
	M1_indices[16] = 4;
	M1_indices[17] = 5;

	//Fourth square
	M1_indices[18] = 1;
	M1_indices[19] = 6;
	M1_indices[20] = 5;
	M1_indices[21] = 1;
	M1_indices[22] = 2;
	M1_indices[23] = 6;

	//Fifth square
	M1_indices[24] = 7;
	M1_indices[25] = 6;
	M1_indices[26] = 2;
	M1_indices[27] = 3;
	M1_indices[28] = 2;
	M1_indices[29] = 7;

	//Sixth square
	M1_indices[30] = 4;
	M1_indices[31] = 5;
	M1_indices[32] = 0;
	M1_indices[33] = 1;
	M1_indices[34] = 0;
	M1_indices[35] = 5;



	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

	// Resizes the vertices array. Replace the values with the correct number of
	// vertices components (3 * number of vertices)

	int slicesCylinder = 36;
	float radiusCylinder = 1;
	float heightCylinder = 1;
	//Center of the cylinder
	float xCylinder = 0, yCylinder = 0, zCylinder = -2;

	M2_vertices.resize(2 * ((slicesCylinder + 1) * 3));

	// Vertices definitions
	M2_vertices[0] = xCylinder;
	M2_vertices[1] = yCylinder + heightCylinder;
	M2_vertices[2] = zCylinder;

	//Vertices of the upper surface
	for (int i = 0; i < slicesCylinder; i++) {
		M2_vertices[((i + 1) * 3) + 0] = xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)); //x of the vertex
		M2_vertices[((i + 1) * 3) + 1] = yCylinder + heightCylinder; //y of the vertex
		M2_vertices[((i + 1) * 3) + 2] = zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)); //z of the vertex
	}

	M2_vertices[((slicesCylinder + 1) * 3) + 0] = xCylinder;
	M2_vertices[((slicesCylinder + 1) * 3) + 1] = yCylinder - heightCylinder;
	M2_vertices[((slicesCylinder + 1) * 3) + 2] = zCylinder;

	//Vertices of the lower surface
	for (int i = slicesCylinder + 1; i < (2 * slicesCylinder) + 1; i++) {
		M2_vertices[((i + 1) * 3) + 0] = xCylinder + radiusCylinder * cos(((float)i / slicesCylinder) * (2.0 * M_PI)); //x of the vertex
		M2_vertices[((i + 1) * 3) + 1] = yCylinder - heightCylinder; //y of the vertex
		M2_vertices[((i + 1) * 3) + 2] = zCylinder + radiusCylinder * sin(((float)i / slicesCylinder) * (2.0 * M_PI)); //z of the vertex
	}

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(3 * 2 * slicesCylinder * 2);

	int counter = 0;
	int counter2 = 0;

	//Upper surface
	for (int i = 0; i < slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = 0;
		M2_indices[(i * 3) + 1] = i + 1;
		M2_indices[(i * 3) + 2] = ((i + 1) % slicesCylinder) + 1;
	}

	counter = slicesCylinder + 1;

	//Lower surface
	for (int i = slicesCylinder; i < 2 * slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = slicesCylinder + 1;
		M2_indices[(i * 3) + 1] = counter + 1;
		if ((i + 1) == (2 * slicesCylinder)) {
			M2_indices[(i * 3) + 2] = ((counter + 1) % ((2 * slicesCylinder) + 1)) + slicesCylinder + 2;
		}
		else {
			M2_indices[(i * 3) + 2] = ((counter + 1) % ((2 * slicesCylinder) + 1)) + 1;
		}
		counter++;
	}

	counter = 0;

	//Triangles of the cylinder
	for (int i = 2 * slicesCylinder; i < 3 * slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = counter + 1;
		M2_indices[(i * 3) + 1] = ((counter + 1) % slicesCylinder) + 1;
		M2_indices[(i * 3) + 2] = (slicesCylinder + 1) + counter + 1;
		counter++;
	}

	counter = slicesCylinder + 1;

	//Triangles of the cylinder
	for (int i = 3 * slicesCylinder; i < 4 * slicesCylinder; i++) {
		M2_indices[(i * 3) + 0] = counter + 1;
		if ((i + 1) == (4 * slicesCylinder)) {
			M2_indices[(i * 3) + 1] = ((counter + 1) % ((2 * slicesCylinder) + 1)) + slicesCylinder + 2;
		}
		else {
			M2_indices[(i * 3) + 1] = ((counter + 1) % ((2 * slicesCylinder) + 1)) + 1;
		}
		M2_indices[(i * 3) + 2] = ((counter2 + 1) % slicesCylinder) + 1;
		counter2++;
		counter++;
	}




	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.
	float xCircle, yCircle, zCircle, xAndyCircle;
	float radiusCircle = 2.0f;
	float stackCountCircle = 24.0f;
	float sectorCountCircle = 72.0f;
	float sectorStepCircle = 2 * M_PI / sectorCountCircle;
	float stackStepCircle = M_PI / stackCountCircle;
	float sectorAngleCircle, stackAngleCircle;
	int valueOfArrayCircle = 0;
	int valueOfSecondArrayCircle = 0;
	int currentStackCircle, nextStackCircle;

	M3_vertices.resize(3 * stackCountCircle * sectorCountCircle * 2);

	for (int i = 0; i <= stackCountCircle; ++i)
	{
		//Starting from pi/2 to -pi/2
		stackAngleCircle = M_PI / 2 - i * stackStepCircle;
		//r * cos(theta)
		xAndyCircle = radiusCircle * cos(stackAngleCircle);
		//r * sin(theta)
		zCircle = radiusCircle * sin(stackAngleCircle);

		//Add (sectorCount + 1) vertices per stack
		//First and last vertices have the same position
		for (int j = 0; j <= sectorCountCircle; ++j)
		{
			//Starting from 0 to 2pi
			sectorAngleCircle = j * sectorStepCircle;

			//r * cos(theta) * cos(phi)
			xCircle = xAndyCircle * cos(sectorAngleCircle);
			//r * cos(theta) * sin(phi)
			yCircle = xAndyCircle * sin(sectorAngleCircle);
			M3_vertices[(valueOfArrayCircle * 3) + 0] = xCircle;
			M3_vertices[(valueOfArrayCircle * 3) + 1] = yCircle;
			M3_vertices[(valueOfArrayCircle * 3) + 2] = zCircle;
			valueOfArrayCircle++;
		}
	}

	M3_indices.resize(3 * stackCountCircle * 2 * sectorCountCircle);

	for (int i = 0; i < stackCountCircle; ++i)
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
			}

			if (i != (stackCountCircle - 1))
			{
				M3_indices[valueOfSecondArrayCircle] = currentStackCircle + 1;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = nextStackCircle;
				valueOfSecondArrayCircle++;
				M3_indices[valueOfSecondArrayCircle] = nextStackCircle + 1;
				valueOfSecondArrayCircle++;
			}
		}
	}


	//// M4 : Spring
	// Replace the code below, that creates a simple octahedron, with the one to create a spring.
	const int slices = 64;
	const int step = 3;
	float internalSpringRadius = 0.24f;
	float rounds = 3.0f;
	int valueOfArray = 0;
	int valueOfSecondArray = 0;
	float heightSpring = rounds;
	float totalSpringRadius = 0.8f;
	bool firstIteration = true;

	float roundsProgression = 0.0f;
	float uSpringValue = 0.0f;
	float vSpringValue = 0.0f;
	float intermediateValueForXY = 0.0f;

	//Add two comodity vertices
	M4_vertices.resize(3 * (slices * (rounds * 360 + step)) + 3 * 2);
	//Indices for double spring rotation plus indices for double plain surface
	M4_indices.resize((2 * 3 * ((slices * (rounds * 360 + step + slices)) / step)) + 2 * 3 * slices);

	for (int i = -slices; i <= rounds * 360 + step; i += step)
	{
		for (int j = 0; j < slices; j++)
		{
			//Progression of the rounds
			roundsProgression = float(i) / 360 + float(j) / slices * step / 360;
			roundsProgression = glm::max(0.0f, glm::min(float(rounds), roundsProgression));
			//std::cout << roundsProgression << "\n";
			//u in [0, 2*n*pi)
			uSpringValue = 2 * roundsProgression * M_PI;
			//v in [0, 2*pi)
			vSpringValue = float(j) / slices * M_PI * 2;
			//Intermediate value = R + (r * cos(v))
			intermediateValueForXY = totalSpringRadius + internalSpringRadius * cos(vSpringValue);
			//First done to iterate in order to create the first plain surface
			if (firstIteration) {
				M4_vertices[(valueOfArray * 3) + 0] = intermediateValueForXY * cos(uSpringValue);
				M4_vertices[(valueOfArray * 3) + 1] = intermediateValueForXY * sin(uSpringValue);
				//Add the height * the percentage to end the spring
				M4_vertices[(valueOfArray * 3) + 2] = internalSpringRadius * sin(vSpringValue) + heightSpring * roundsProgression / rounds;
				valueOfArray++;
				firstIteration = false;
			}
			//x(u,v) = (R + (r * cos(v))) * cos(u)
			M4_vertices[(valueOfArray * 3) + 0] = intermediateValueForXY * cos(uSpringValue);
			//y(u,v) = (R + (r * cos(v))) * sin(u)
			M4_vertices[(valueOfArray * 3) + 1] = intermediateValueForXY * sin(uSpringValue);
			//z(u,v) = (r * sin(v)) + (h * roundProgr) / rounds
			M4_vertices[(valueOfArray * 3) + 2] = internalSpringRadius * sin(vSpringValue) + heightSpring * roundsProgression / rounds;
			valueOfArray++;
		}
	}

	//Last done to iterate in order to create the second plain surface
	M4_vertices[(valueOfArray * 3) + 0] = intermediateValueForXY * cos(uSpringValue);
	M4_vertices[(valueOfArray * 3) + 1] = intermediateValueForXY * sin(uSpringValue);
	M4_vertices[(valueOfArray * 3) + 2] = internalSpringRadius * sin(vSpringValue) + heightSpring * roundsProgression / rounds;

	//First plain surface
	for (int i = 1; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = 0;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	//First part of the spring
	for (int i = 0; i < ((slices * ((rounds * 360 + step) + slices - step)) / step); ++i)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	//Second part of the spring
	for (int i = 0; i < ((slices * ((rounds * 360 + step) + slices - step)) / step); ++i)
	{
		M4_indices[valueOfSecondArray] = i + slices + 1;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}
	
	//Second plain surface
	for (int i = 1; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << "\n";
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = valueOfArray;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;
		valueOfSecondArray++;
	}
}
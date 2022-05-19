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
/*M1_vertices.resize(4);

// first vertex of M1
M1_vertices[0].pos  = glm::vec3(-1.0,-1.0,-1.0);
M1_vertices[0].norm = glm::vec3(0.0,0.0,1.0);
M1_vertices[0].UV   = glm::vec2(0.0,1.0);
//M1_vertices[0].UV = glm::vec2(1 * (0.5) / 4, 0.0);

// second vertex of M1
M1_vertices[1].pos  = glm::vec3(1.0,-1.0,-1.0);
M1_vertices[1].norm = glm::vec3(0.0,0.0,1.0);
M1_vertices[1].UV   = glm::vec2(1.0, 1.0);
//M1_vertices[1].UV = glm::vec2(2 * (0.5) / 4, 0.0);

// third vertex of M1
M1_vertices[2].pos  = glm::vec3(1.0,1.0,-1.0);
M1_vertices[2].norm = glm::vec3(0.0,0.0,1.0);
M1_vertices[2].UV   = glm::vec2(1.0,0.0);
//M1_vertices[2].UV = glm::vec2(2 * (0.5) / 4, 1 * (0.5) / 4);

// fourth vertex of M1
M1_vertices[3].pos  = glm::vec3(-1.0,1.0,-1.0);
M1_vertices[3].norm = glm::vec3(0.0,0.0,1.0);
M1_vertices[3].UV   = glm::vec2(0.0,0.0);
//M1_vertices[3].UV = glm::vec2(1 * (0.5) / 4, 1 * (0.5) / 4);


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M1_indices.resize(3 * 2);

// first triangle
M1_indices[0] = 0;
M1_indices[1] = 1;
M1_indices[2] = 2;

// second triangle
M1_indices[3] = 2;
M1_indices[4] = 3;
M1_indices[5] = 0;*/


	/*int arrayOfCube = 0;
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
	M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, 1.0f);
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
	}*/

	
int arrayOfCube = 0;
int arrayOfNorm = 0;
int startingOfNorm = 0;
M1_vertices.resize(3 * 4 * 6 * 3 * 100);

//Riguardare correttezza vettori
// Resizes the vertices array. Repalce the values with the correct number of
// vertices

// Front face (z = 1.0f)
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 1 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 1 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 0.0);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, 1.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 0.0);
arrayOfCube++;

// Top face (y = 1.0f)
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 2 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 2 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 1 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 1.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 1 * (0.5) / 4);
arrayOfCube++;

// Back face  (z = -1.0f)
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 3 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 3 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 2 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, 0.0f, -1.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 2 * (0.5) / 4);
arrayOfCube++;

// Left face (x = -1.0f)
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(0.0, 3 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 3 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 2 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, 1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(0.0, 2 * (0.5) / 4);
arrayOfCube++;

// Right face (x = 1.0f)
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 3 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(3 * (0.5) / 4, 3 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(3 * (0.5) / 4, 2 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, 1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(1.0f, 0.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 2 * (0.5) / 4);
arrayOfCube++;

// Bottom face(y = -1.0f)
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 4 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, 1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 4 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(1.0f, -1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(2 * (0.5) / 4, 3 * (0.5) / 4);
arrayOfCube++;
M1_vertices[arrayOfCube].pos = glm::vec3(-1.0f, -1.0f, -1.0f);
M1_vertices[arrayOfCube].norm = glm::vec3(0.0f, -1.0f, 0.0f);
M1_vertices[arrayOfCube].UV = glm::vec2(1 * (0.5) / 4, 3 * (0.5) / 4);
arrayOfCube++;

for (int i = 0; i < M1_vertices.size(); i++) {
	M1_vertices[i].pos = M1_vertices[i].pos * 2.0f;
}



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

// Resizes the vertices array. Repalce the values with the correct number of
// vertices
/*M2_vertices.resize(4);

// Vertices definitions
M2_vertices[0].pos  = glm::vec3(0.0,-1.0,-1.1);
M2_vertices[0].norm = glm::vec3(0.0,0.0,1.0);
M2_vertices[0].UV   = glm::vec2(0.0,1.0);

M2_vertices[1].pos  = glm::vec3(1.0,0.0,-1.1);
M2_vertices[1].norm = glm::vec3(0.0,0.0,1.0);
M2_vertices[1].UV   = glm::vec2(1.0,1.0);

M2_vertices[2].pos  = glm::vec3(0.0,1.0,-1.1);
M2_vertices[2].norm = glm::vec3(0.0,0.0,1.0);
M2_vertices[2].UV   = glm::vec2(1.0,0.0);

M2_vertices[3].pos  = glm::vec3(-1.0,0.0,-1.1);
M2_vertices[3].norm = glm::vec3(0.0,0.0,1.0);
M2_vertices[3].UV   = glm::vec2(0.0,0.0);


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M2_indices.resize(6);

// indices definitions
M2_indices[0] = 0;
M2_indices[1] = 1;
M2_indices[2] = 2;
M2_indices[3] = 2;
M2_indices[4] = 3;
M2_indices[5] = 0;*/

int NSlice = 10;
float radius = 1;
float height = 1;
//Center
float cx = 0, cy = 0, cz = -2;
float lengthInvC = 1.0f / radius;
float normCx, normCz;
float radiusUV = 1 * (0.5) / 4;

M2_vertices.resize(4 * ((NSlice + 1) * 3));

// Resizes the vertices array. Repalce the values with the correct number of
// vertices
M2_vertices[0].pos = glm::vec3(cx, cy + height, cz);
M2_vertices[0].norm = glm::vec3(0.0, 1.0, 0.0);
M2_vertices[0].UV = glm::vec2(0.5 + (1 * (0.5) / 4), 1 * (0.5) / 4);
//M2_vertices[0] = cx;
//M2_vertices[1] = cy + height;
//M2_vertices[2] = cz;

for (int i = 0; i < NSlice; i++) {
	//M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
	//M2_vertices[((i + 1) * 3) + 1] = cy + height; //y of the vertex
	//M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
	M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy + height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
	M2_vertices[(i + 1)].norm = glm::vec3(0.0, 1.0, 0.0);
	M2_vertices[(i + 1)].UV = glm::vec2(0.5 + (1 * (0.5) / 4), 0.5 / 2);
}

//M2_vertices[((NSlice + 1) * 3) + 0] = cx;
//M2_vertices[((NSlice + 1) * 3) + 1] = cy - height;
//M2_vertices[((NSlice + 1) * 3) + 2] = cz;
M2_vertices[(NSlice + 1)].pos = glm::vec3(cx, cy - height, cz);
M2_vertices[(NSlice + 1)].norm = glm::vec3(0.0, -1.0, 0.0);
M2_vertices[(NSlice + 1)].UV = glm::vec2(0.5 + (3 * (0.5) / 4), 1 * (0.5) / 4);

for (int i = NSlice + 1; i < (2 * NSlice) + 1; i++) {
	//M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
	//M2_vertices[((i + 1) * 3) + 1] = cy - height; //y of the vertex
	//M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
	M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy - height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
	M2_vertices[(i + 1)].norm = glm::vec3(0.0, -1.0, 0.0);
}


//DEVO INSERIRE UN VALORE AGGIUNTIVO
float valueUV = 0.0f;

for (int i = (2 * NSlice) + 1; i < (NSlice * 3) + 1; i++) {
	//M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
	//M2_vertices[((i + 1) * 3) + 1] = cy + height; //y of the vertex
	//M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
	M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy + height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
	normCx = radius * cos(((float)i / NSlice) * (2.0 * M_PI));
	normCz = radius * sin(((float)i / NSlice) * (2.0 * M_PI));
	M2_vertices[(i + 1)].norm = glm::vec3(normCx, 0.0, normCz);
	M2_vertices[(i + 1)].UV = glm::vec2(1.0f - float((valueUV / float(NSlice)) / 2.0f), 0.5f / 2);
	std::cout << 0.5f + float((valueUV / float(NSlice)) / 2.0f);
	std::cout << "\n";
	valueUV++;
	//M1_vertices[(i + 1)].UV = glm::vec2(1 * (0.5) / 4, 3 * (0.5) / 4);
}

valueUV = 0;

for (int i = (NSlice * 3) + 1; i < (NSlice * 4) + 1; i++) {
	//M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
	//M2_vertices[((i + 1) * 3) + 1] = cy - height; //y of the vertex
	//M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
	M2_vertices[(i + 1)].pos = glm::vec3(cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)), cy - height, cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)));
	normCx = radius * cos(((float)i / NSlice) * (2.0 * M_PI));
	normCz = radius * sin(((float)i / NSlice) * (2.0 * M_PI));
	M2_vertices[(i + 1)].norm = glm::vec3(normCx, 0.0, normCz);
	M2_vertices[(i + 1)].UV = glm::vec2(1.0f - float((valueUV / float(NSlice)) / 2.0f), 0.5f);
	std::cout << 0.5f + float((valueUV / float(NSlice)) / 2.0f);
	std::cout << "\n";
	valueUV++;
	//M1_vertices[(i + 1)].UV = glm::vec2(1 * (0.5) / 4, 3 * (0.5) / 4);
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

}
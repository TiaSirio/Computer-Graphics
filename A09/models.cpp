// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
//// M1 : Cube
// Replace the code below, that creates a simple square, with the one to create a cube.

// Resizes the vertices array. Repalce the values with the correct number of
// vertices components (3 * number of vertices)

	M1_vertices.resize(3 * 4 * 6);

	// first vertex of M1
	M1_vertices[0] = -1.0;
	M1_vertices[1] = -1.0;
	M1_vertices[2] = -1.0;

	// second vertex of M1
	M1_vertices[3] = -1.0;
	M1_vertices[4] = -1.0;
	M1_vertices[5] = 1.0;

	// third vertex of M1
	M1_vertices[6] = -1.0;
	M1_vertices[7] = 1.0;
	M1_vertices[8] = 1.0;

	// fourth vertex of M1
	M1_vertices[9] = -1.0;
	M1_vertices[10] = 1.0;
	M1_vertices[11] = -1.0;

	// fifth vertex of M1
	M1_vertices[12] = 1.0;
	M1_vertices[13] = -1.0;
	M1_vertices[14] = -1.0;

	// sixth vertex of M1
	M1_vertices[15] = 1.0;
	M1_vertices[16] = -1.0;
	M1_vertices[17] = 1.0;

	// seventh vertex of M1
	M1_vertices[18] = 1.0;
	M1_vertices[19] = 1.0;
	M1_vertices[20] = 1.0;

	// eigth vertex of M1
	M1_vertices[21] = 1.0;
	M1_vertices[22] = 1.0;
	M1_vertices[23] = -1.0;

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M1_indices.resize(3 * 2 * 6);

	// first square
	M1_indices[0] = 0;
	M1_indices[1] = 1;
	M1_indices[2] = 2;
	M1_indices[3] = 2;
	M1_indices[4] = 3;
	M1_indices[5] = 0;

	// second square
	M1_indices[6] = 0;
	M1_indices[7] = 3;
	M1_indices[8] = 4;
	M1_indices[9] = 4;
	M1_indices[10] = 3;
	M1_indices[11] = 7;

	// third square
	M1_indices[12] = 5;
	M1_indices[13] = 6;
	M1_indices[14] = 7;
	M1_indices[15] = 7;
	M1_indices[16] = 4;
	M1_indices[17] = 5;

	// fourth square
	M1_indices[18] = 1;
	M1_indices[19] = 6;
	M1_indices[20] = 5;
	M1_indices[21] = 1;
	M1_indices[22] = 2;
	M1_indices[23] = 6;

	// fifth square
	M1_indices[24] = 7;
	M1_indices[25] = 6;
	M1_indices[26] = 2;
	M1_indices[27] = 3;
	M1_indices[28] = 2;
	M1_indices[29] = 7;

	// sixth square
	M1_indices[30] = 4;
	M1_indices[31] = 5;
	M1_indices[32] = 0;
	M1_indices[33] = 1;
	M1_indices[34] = 0;
	M1_indices[35] = 5;



	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)

	int NSlice = 36;
	float radius = 1;
	float height = 1;
	//Center
	float cx = 0, cy = 0, cz = -2;

	M2_vertices.resize(2 * ((NSlice + 1) * 3));

	// Vertices definitions
	M2_vertices[0] = cx;
	M2_vertices[1] = cy + height;
	M2_vertices[2] = cz;

	for(int i = 0; i < NSlice; i++) {
		M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
		M2_vertices[((i + 1) * 3) + 1] = cy + height; //y of the vertex
		M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
	}

	M2_vertices[((NSlice + 1) * 3) + 0] = cx;
	M2_vertices[((NSlice + 1) * 3) + 1] = cy - height;
	M2_vertices[((NSlice + 1) * 3) + 2] = cz;

	for(int i = NSlice + 1; i < (2 * NSlice) + 1; i++) {
		M2_vertices[((i + 1) * 3) + 0] = cx + radius * cos(((float)i / NSlice) * (2.0 * M_PI)); //x of the vertex
		M2_vertices[((i + 1) * 3) + 1] = cy - height; //y of the vertex
		M2_vertices[((i + 1) * 3) + 2] = cz + radius * sin(((float)i / NSlice) * (2.0 * M_PI)); //z of the vertex
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

	counter = 0;

	for (int i = 2 * NSlice; i < 3 * NSlice; i++) {
		M2_indices[(i * 3) + 0] = counter + 1;
		M2_indices[(i * 3) + 1] = ((counter + 1) % NSlice) + 1;
		M2_indices[(i * 3) + 2] = (NSlice + 1) + counter + 1;
		counter++;
	}

	counter = NSlice + 1;

	for (int i = 3 * NSlice; i < 4 * NSlice; i++) {
		M2_indices[(i * 3) + 0] = counter + 1;
		if ((i + 1) == (4 * NSlice)) {
			M2_indices[(i * 3) + 1] = ((counter + 1) % ((2 * NSlice) + 1)) + NSlice + 2;
		}
		else {
			M2_indices[(i * 3) + 1] = ((counter + 1) % ((2 * NSlice) + 1)) + 1;
		}
		M2_indices[(i * 3) + 2] = ((counter2 + 1) % NSlice) + 1;
		counter2++;
		counter++;
	}




	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)

	int NSlice3 = 36;
	float radius3 = 1;
	float height3 = 1;
	int maxJ = 3;
	int modify = 1/maxJ;
	//Center
	float cx3 = 0, cy3 = 0, cz3 = -2;

	M3_vertices.resize(3 * (NSlice3 + 1) * (maxJ + 1));

	int count = 0;
	int max = 0;

	M3_vertices[0] = cx3;
	M3_vertices[1] = cy3 + height3;
	M3_vertices[2] = cz3;

	for (int j = 0; j < maxJ; j++) {
		for (int i = 0; i < NSlice3; i++) {
			M3_vertices[((i + 1) * 3) + 0] = cx3 + float(radius3 - (modify * j)) * cos(((float)i / NSlice3) * (2.0 * M_PI)); //x of the vertex
			M3_vertices[((i + 1) * 3) + 1] = cy3 + float(j/maxJ); //y of the vertex
			M3_vertices[((i + 1) * 3) + 2] = cz3 + float(radius3 - (modify * j)) * sin(((float)i / NSlice3) * (2.0 * M_PI)); //z of the vertex
		}
	}

	//M3_vertices[((NSlice3 + 1) * 3) + 0] = cx3;
	//M3_vertices[((NSlice3 + 1) * 3) + 1] = cy3 - height3;
	//M3_vertices[((NSlice3 + 1) * 3) + 2] = cz3;

	//for (int i = NSlice3 + 1; i < (2 * NSlice3) + 1; i++) {
	//	M3_vertices[((i + 1) * 3) + 0] = cx3 + radius3 * cos(((float)i / NSlice3) * (2.0 * M_PI)); //x of the vertex
	//	M3_vertices[((i + 1) * 3) + 1] = cy3; //y of the vertex
	//	M3_vertices[((i + 1) * 3) + 2] = cz3 + radius3 * sin(((float)i / NSlice3) * (2.0 * M_PI)); //z of the vertex
	//}

	M3_indices.resize(3 * NSlice3 * maxJ * 2);

	for (int j = 0; j < maxJ - 1; j++) {
		for (int i = 0; i < NSlice3; i++) {
			M3_indices[(count * 3) + 0] = i * (j + 1);
			M3_indices[(count * 3) + 1] = count + 1;
			M3_indices[(count * 3) + 2] = ((count + 1) % (NSlice3 * (j + 1))) + 1;
			count++;
		}
	}

	for (int i = 0; i < NSlice3; i++) {
		M3_indices[(count * 3) + 0] = 0;
		M3_indices[(count * 3) + 1] = count + 1;
		M3_indices[(count * 3) + 2] = ((count + 1) % (NSlice3 * maxJ)) + 1;
		count++;
	}

	//count = NSlice3 + 1;

	/*for (int i = NSlice3; i < 2 * NSlice3; i++) {
		M3_indices[(i * 3) + 0] = NSlice3 + 1;
		M3_indices[(i * 3) + 1] = count;
		M3_indices[(i * 3) + 2] = ((i + 1) % ((2 * NSlice) + 1)) + 1;
		count++;
	}*/

	//for (int j = 0; j < NSlice3; j++) {
	//	for (int i = 0; i < NSlice3; i++) {
	//		M3_vertices[((count) * 3) + 0] = cx3 + radius3 * cos(((float)i / NSlice3) * (2.0 * M_PI)); //x of the vertex
	//		M3_vertices[((count) * 3) + 1] = cy3; //y of the vertex
	//		M3_vertices[((count) * 3) + 2] = cz3 + radius3 * sin(((float)i / NSlice3) * (2.0 * M_PI)); //z of the vertex
	//		count++;
	//	}
	//	cy3 = cy3 + float(j / NSlice3);
	//}

	//cy3 = 0;

	//for (int j = 0; j < NSlice3; j++) {
	//	for (int i = 0; i < NSlice3; i++) {
	//		M3_vertices[((count) * 3) + 0] = cx3 + radius3 * cos(((float)i / NSlice3) * (2.0 * M_PI)); //x of the vertex
	//		M3_vertices[((count) * 3) + 1] = cy3; //y of the vertex
	//		M3_vertices[((count) * 3) + 2] = cz3 + radius3 * sin(((float)i / NSlice3) * (2.0 * M_PI)); //z of the vertex
	//		count++;
	//	}
	//	cy3 = cy3 - float(j / NSlice3);
	//}

	//// Resizes the indices array. Repalce the values with the correct number of
	//// indices (3 * number of triangles)
	//M3_indices.resize(3 * NSlice3^4);

	//count = 0;

	//for (int j = 0; j < NSlice3; j++) {
	//	for (int i = 0; i < NSlice3; i++) {
	//		M3_indices[(count * 3) + 0] = i;
	//		M3_indices[(count * 3) + 1] = i + 1;
	//		M3_indices[(count * 3) + 2] = i + NSlice3;
	//	}
	//	count++;
	//}

	//for (int j = 0; j < NSlice3; j++) {
	//	for (int i = 0; i < NSlice3; i++) {
	//		M3_indices[(count * 3) + 0] = i;
	//		M3_indices[(count * 3) + 1] = i + 1;
	//		M3_indices[(count * 3) + 2] = i + NSlice3;
	//	}
	//	count++;
	//}




	//// M4 : Spring
	// Replace the code below, that creates a simple octahedron, with the one to create a spring.

	const int slices = 32;
	const int step = 5;
	float thickness = 0.24f;
	float rounds = 3.0f;
	int valueOfArray = 0;
	int valueOfSecondArray = 0;
	float heightSpring = 2.0f;
	float radiusSpring = 0.8f;

	float t = 0.0f;
	float a1 = 0.0f;
	float a2 = 0.0f;
	float d = 0.0f;

	M4_vertices.resize(3 * slices * (rounds * 360 + step));
	M4_indices.resize(2 * 3 * slices * (rounds * 360 + step));

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
			//t = max_value(0.0f, min_value(float(rounds), t));
			a1 = t * M_PI * 2;
			a2 = float(j) / slices * M_PI * 2;
			d = radiusSpring + thickness * cos(a2);
			M4_vertices[(valueOfArray * 3) + 0] = d * cos(a1);
			M4_vertices[(valueOfArray * 3) + 1] = d * sin(a1);
			M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;
			valueOfArray++;
		}
	}
	for (int i = 0; i < int((3 * slices * (rounds * 360 + step))) / 3 - slices; ++i)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}
	for (int i = 0; i < int((3 * slices * (rounds * 360 + step))) / 3 - slices; ++i)
	{
		M4_indices[valueOfSecondArray] = i + slices + 1;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	// Vertices definitions
	/*M4_vertices[0] = 0.0;
	M4_vertices[1]  =  1.414;
	M4_vertices[2]  = -1.0;
	M4_vertices[3]  =  0.0;
	M4_vertices[4]  = -1.414;
	M4_vertices[5]  = -1.0;
	M4_vertices[6]  = -1.0;
	M4_vertices[7]  =  0.0;
	M4_vertices[8]  = -2.0;
	M4_vertices[9]  = -1.0;
	M4_vertices[10] =  0.0;
	M4_vertices[11] =  0.0;
	M4_vertices[12] =  1.0;
	M4_vertices[13] =  0.0;
	M4_vertices[14] =  0.0;
	M4_vertices[15] =  1.0;
	M4_vertices[16] =  0.0;
	M4_vertices[17] = -2.0;


	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M4_indices.resize(3 * 8);

	// indices definitions
	M4_indices[0]  = 0;
	M4_indices[1]  = 2;
	M4_indices[2]  = 3;
	M4_indices[3]  = 1;
	M4_indices[4]  = 3;
	M4_indices[5]  = 2;
	M4_indices[6]  = 0;
	M4_indices[7]  = 3;
	M4_indices[8]  = 4;
	M4_indices[9]  = 1;
	M4_indices[10] = 4;
	M4_indices[11] = 3;
	M4_indices[12] = 0;
	M4_indices[13] = 4;
	M4_indices[14] = 5;
	M4_indices[15] = 1;
	M4_indices[16] = 5;
	M4_indices[17] = 4;
	M4_indices[18] = 0;
	M4_indices[19] = 5;
	M4_indices[20] = 2;
	M4_indices[21] = 1;
	M4_indices[22] = 2;
	M4_indices[23] = 5;*/
}
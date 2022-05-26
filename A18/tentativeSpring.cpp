/*const int slices = 64;//32;
	const int step = 3;
	float thickness = 0.24f;
	float rounds = 3.0f;
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
	//int lastI = 0;
	int lastValueOfI;

	M4_vertices.resize(3 * slices * (rounds * 360 + step + 2));
	M4_indices.resize(2 * 3 * ((slices * (rounds * 360 + step + slices)) / step) * slices);

	for (int i = -slices; i <= rounds * 360 + step; i += step)
	{
		if (i + step > rounds * 360 + step) {
			lastValueOfI = i;
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
			//t = max_value(0.0f, min_value(float(rounds), t));
			a1 = t * M_PI * 2;
			a2 = float(j) / slices * M_PI * 2;
			d = radiusSpring + thickness * cos(a2);
			//if (firstIteration) {
				//M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
			//}
			//else if (lastIteration) {
				//M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
			//}
			//else {
				M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
				//M4_vertices[valueOfArray].norm = glm::vec3(cos(a1), sin(a1), thickness * sin(a2));
			//}
			valueOfArray++;
		}
		firstIteration = false;
		//lastI = i;
	}*/

	/*int startingCircle = valueOfArray;

	for (int j = 0; j < slices; j++)
	{
		t = float(j) / slices * step / 360;
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
		M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
		valueOfArray++;
	}

	int endingCircle = valueOfArray;

	for (int j = 0; j < slices; j++)
	{
		t = float(lastValueOfI) / 360 + float(j) / slices * step / 360;
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
		M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
		valueOfArray++;
	}*/


	//int valueSpring1, valueSpring2, valueSpring3;

	/*for (int i = 0; i <= slices; ++i)
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

	/*for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step); ++i)
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


		//std::cout << i + slices;
		//std::cout << "\n";
	}

	for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step); ++i)
	{
		M4_indices[valueOfSecondArray] = i + slices + 1;
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

		//std::cout << i + slices + 1;
		//std::cout << "\n";
	}*/

	//std::cout << valueOfArray;
	//std::cout << "\n";

	/*for (int i = 0; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << "\n";
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = valueOfArray;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;
		valueOfSecondArray++;


		valueSpring1 = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		valueSpring2 = valueOfArray;
		valueSpring3 = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = surface_normal(thirdCyl, firstCyl, secondCyl);
	}*/


	/*const int slices = 3;//64;//32;
	const int step = 3;
	float thickness = 0.24f;
	float rounds = 3.0f;
	int valueOfArray = 0;
	int valueOfSecondArray = 0;
	float heightSpring = rounds;
	float radiusSpring = 0.8f;
	bool firstIteration = true;

	float t = 0.0f;
	float a1 = 0.0f;
	float a2 = 0.0f;
	float d = 0.0f;

	M4_vertices.resize(3 * slices * (rounds * 360 + step + 2) * 2);
	M4_indices.resize(2 * 3 * ((slices * (rounds * 360 + step + slices)) / step) * slices * 2);

	for (int i = -slices; i <= rounds * 360 + step; i += step)
	{
		for (int j = 0; j < slices; j++)
		{
			t = float(i) / 360 + float(j) / slices * step / 360;
			t = glm::max(0.0f, glm::min(float(rounds), t));
			a1 = t * M_PI * 2;
			a2 = float(j) / slices * M_PI * 2;
			d = radiusSpring + thickness * cos(a2);
			if (firstIteration) {
				M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
				valueOfArray++;
				firstIteration = false;
			}
			M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
			valueOfArray++;
		}
	}

	M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);

	int valueSpring1, valueSpring2, valueSpring3;

	for (int i = 0; i <= slices; ++i)
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
	}

	//for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step); ++i)
	for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step) + slices - 1; ++i)
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

	//for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step); ++i)
	for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step) + slices - 1; ++i)
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
	std::cout << "Test \n";
	std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + slices + 1;
	//std::cout << valueOfArray;
	//std::cout << "\n";
	std::cout << "Test \n";
	std::cout << valueOfArray;

	for (int i = 0; i <= slices * 2; ++i)
	{
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << "\n";
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) - slices + i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;
		valueOfSecondArray++;

		valueSpring1 = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		valueSpring2 = ((slices * (rounds * 360 + step + slices - 1)) / step) - slices + i;
		valueSpring3 = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = surface_normal(thirdCyl, firstCyl, secondCyl);
	}*/

	/*for (int i = 0; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		//std::cout << "\n";
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = valueOfArray;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;
		valueOfSecondArray++;

		valueSpring1 = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		valueSpring2 = valueOfArray;
		valueSpring3 = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;

		firstCyl = M4_vertices[valueSpring1].pos;
		secondCyl = M4_vertices[valueSpring2].pos;
		thirdCyl = M4_vertices[valueSpring3].pos;

		M4_vertices[valueSpring1].norm = surface_normal(firstCyl, secondCyl, thirdCyl);
		M4_vertices[valueSpring2].norm = surface_normal(secondCyl, thirdCyl, firstCyl);
		M4_vertices[valueSpring3].norm = surface_normal(thirdCyl, firstCyl, secondCyl);
	}*/





	//// M4 : Spring
	// Replace the code below, that creates a simple octahedron, with the one to create a spring.
	/*const int slices = 32;
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
	M4_indices.resize(2 * 3 * ((slices * (rounds * 360 + step + slices)) / step) * slices);

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
				M4_vertices[0].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
				M4_vertices[0].norm = glm::vec3(0.0, -1.0, 0.0);
				valueOfArray++;
				firstIteration = false;
			}
			M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
			M4_vertices[valueOfArray].norm = glm::vec3(cos(a1), sin(a1), thickness * sin(a2));
			valueOfArray++;
		}
		firstIteration = false;
	}

	M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
	M4_vertices[valueOfArray].norm = glm::vec3(0.0, 1.0, 0.0);
	//M4_vertices[valueOfArray].norm = glm::vec3(0.0, -1.0, 0.0);

	for (int i = 1; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = 0;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step); ++i)
	{
		M4_indices[valueOfSecondArray] = i;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step); ++i)
	{
		M4_indices[valueOfSecondArray] = i + slices + 1;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + slices;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = i + 1;
		valueOfSecondArray++;
	}

	std::cout << valueOfArray;
	std::cout << "\n";

	for (int i = 1; i <= slices; ++i)
	{
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
		std::cout << "\n";
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = valueOfArray;
		valueOfSecondArray++;
		M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;
		valueOfSecondArray++;
	}*/

	/*t = float(lastI) / 360 + 0 / slices * step / 360;
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
	a2 = float(0.0f) / slices * M_PI * 2;
	d = radiusSpring + thickness * cos(a2);
	M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
	M4_vertices[valueOfArray].norm = glm::vec3(0.0, 1.0, 0.0);*/

	//M4_vertices[(valueOfArray * 3) + 0] = d * cos(a1);
	//M4_vertices[(valueOfArray * 3) + 1] = d * sin(a1);
	//M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;
	//M4_vertices[valueOfArray].pos = glm::vec3(d * cos(a1), d * sin(a1), thickness * sin(a2) + heightSpring * t / rounds);
	//M4_vertices[valueOfArray].norm = glm::vec3(0.0, 1.0, 0.0);



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

		// Resizes the indices array. Repalce the values with the correct number of
		// indices (3 * number of triangles)
		/*for (int i = 1; i <= slices; ++i)
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
		}*/

		/*M4_vertices.resize(3 * slices * (rounds * 360 + step + 2));
		M4_indices.resize(2 * 3 * ((slices * (rounds * 360 + step + slices)) / step) * slices);

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
				if (firstIteration) {
					M4_vertices[(valueOfArray * 3) + 0] = d * cos(a1);
					M4_vertices[(valueOfArray * 3) + 1] = d * sin(a1);
					M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;
					valueOfArray++;
					firstIteration = false;
				}
				M4_vertices[(valueOfArray * 3) + 0] = d * cos(a1);
				M4_vertices[(valueOfArray * 3) + 1] = d * sin(a1);
				M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;
				valueOfArray++;
			}
		}

		M4_vertices[(valueOfArray * 3) + 0] = d * cos(a1);
		M4_vertices[(valueOfArray * 3) + 1] = d * sin(a1);
		M4_vertices[(valueOfArray * 3) + 2] = thickness * sin(a2) + heightSpring * t / rounds;

		for (int i = 1; i <= slices; ++i)
		{
			M4_indices[valueOfSecondArray] = i;
			valueOfSecondArray++;
			M4_indices[valueOfSecondArray] = 0;
			valueOfSecondArray++;
			M4_indices[valueOfSecondArray] = i + 1;
			valueOfSecondArray++;
		}

		for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step); ++i)
		{
			M4_indices[valueOfSecondArray] = i;
			valueOfSecondArray++;
			M4_indices[valueOfSecondArray] = i + slices;
			valueOfSecondArray++;
			M4_indices[valueOfSecondArray] = i + 1;
			valueOfSecondArray++;
		}

		for (int i = 0; i < ((slices * (rounds * 360 + step + slices - 1)) / step); ++i)
		{
			M4_indices[valueOfSecondArray] = i + slices + 1;
			valueOfSecondArray++;
			M4_indices[valueOfSecondArray] = i + slices;
			valueOfSecondArray++;
			M4_indices[valueOfSecondArray] = i + 1;
			valueOfSecondArray++;
		}

		std::cout << valueOfArray;
		std::cout << "\n";

		for (int i = 1; i <= slices; ++i)
		{
			M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
			std::cout << ((slices * (rounds * 360 + step + slices - 1)) / step) + i;
			std::cout << "\n";
			valueOfSecondArray++;
			M4_indices[valueOfSecondArray] = valueOfArray;
			valueOfSecondArray++;
			M4_indices[valueOfSecondArray] = ((slices * (rounds * 360 + step + slices - 1)) / step) + i + 1;
			valueOfSecondArray++;
		}*/
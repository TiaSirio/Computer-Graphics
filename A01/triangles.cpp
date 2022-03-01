/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
 
 Using function Triangle(...) try to draw a children house, similar to the one below.
 
 First remove the two function below (given only as an example), and replace them with your own.
 Since it is a C program, you can use for loops if you think it can be helpful in your drawing.
 The for() command below that draws a sun like shape in exact center of the screen near the top,
 is an example on how you can use it: please remove it, and replace it with your own code.
 It is not necessery to use a for loop if you do not really need it: it has been put here only as
 an example to help students not familiar with C++.
***************/

//Triangle(-1,-1, 0,0, -1,1,   1,0,0);	// Draws a red triangle pointing right
//Triangle(1,-1, 0,0, 1,1,   0,1,0);	// Draws a green triangle pointing left

//Roof
Triangle(-0.04, 0.16, 0.35, -0.45, 0.74, 0.16, 1, 0, 0);

//House
Triangle(0.06, 0.16, 0.66, 0.16, 0.06, 0.8, 0, 0, 1);
Triangle(0.66, 0.16, 0.66, 0.8, 0.06, 0.8, 0, 0, 1);

//Window1
Triangle(0.16, 0.28, 0.28, 0.28, 0.28, 0.42, 1, 1, 0);
Triangle(0.16, 0.28, 0.28, 0.42, 0.16, 0.42, 1, 1, 0);

//Window2
Triangle(0.45, 0.28, 0.57, 0.28, 0.57, 0.42, 1, 1, 0);
Triangle(0.45, 0.28, 0.57, 0.42, 0.45, 0.42, 1, 1, 0);

//Door
Triangle(0.3, 0.5, 0.425, 0.5, 0.3, 0.8, 1, 1, 0);
Triangle(0.425, 0.5, 0.425, 0.8, 0.3, 0.8, 1, 1, 0);

//Grass
Triangle(-1, 0.8, 1, 1, -1, 1, 0, 1, 0);
Triangle(-1, 0.8, 1, 0.8, 1, 1, 0, 1, 0);

//Sun
int numberOfTrianglesForSun = 16;
for (int i = 0; i < numberOfTrianglesForSun; i++) {
	Triangle(0.65 + 0.05 * cos(6.28 / numberOfTrianglesForSun * (i - 5)), -0.68 + 0.05 * sin(6.28 / numberOfTrianglesForSun * (i - 5)),
		0.65 + 0.15 * cos(6.28 / numberOfTrianglesForSun * i), -0.68 + 0.15 * sin(6.28 / numberOfTrianglesForSun * i),
		0.65 + 0.05 * cos(6.28 / numberOfTrianglesForSun * (i + 5)), -0.68 + 0.05 * sin(6.28 / numberOfTrianglesForSun * (i + 5)),
		1, 0.5, 0.1);
}

int numberOfTrianglesForFlower = 32;

int numberOfTrianglesForInnerOfFlower = 16;

//StemFlower0
Triangle(-0.74, 0.8, -0.74, 0.70, -0.72, 0.70, 0, 1, 0);
Triangle(-0.74, 0.8, -0.72, 0.70, -0.72, 0.8, 0, 1, 0);

//Flower0
for (int i = 0; i < numberOfTrianglesForFlower; i++) {
	Triangle(-0.73 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i - 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i - 10)),
		-0.73 + 0.10 * cos(6.28 / numberOfTrianglesForFlower * i), 0.66 + 0.10 * sin(6.28 / numberOfTrianglesForFlower * i),
		-0.73 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i + 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i + 10)),
		0, 0.5, 1);
}

//InnerOfFlower0
for (int i = 0; i < numberOfTrianglesForInnerOfFlower; i++) {
	Triangle(-0.73 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)),
		-0.73 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * i), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * i),
		-0.73 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)),
		1, 1, 0);
}

//StemFlower1
Triangle(-0.54, 0.8, -0.54, 0.70, -0.52, 0.70, 0, 1, 0);
Triangle(-0.54, 0.8, -0.52, 0.70, -0.52, 0.8, 0, 1, 0);

//Flower1
for (int i = 0; i < numberOfTrianglesForFlower; i++) {
	Triangle(-0.53 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i - 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i - 10)),
		-0.53 + 0.10 * cos(6.28 / numberOfTrianglesForFlower * i), 0.66 + 0.10 * sin(6.28 / numberOfTrianglesForFlower * i),
		-0.53 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i + 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i + 10)),
		0.5, 0, 0.5);
}

//InnerOfFlower1
for (int i = 0; i < numberOfTrianglesForInnerOfFlower; i++) {
	Triangle(-0.53 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)),
		-0.53 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * i), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * i),
		-0.53 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)),
		1, 1, 0);
}

//StemFlower2
Triangle(-0.34, 0.8, -0.34, 0.70, -0.32, 0.70, 0, 1, 0);
Triangle(-0.34, 0.8, -0.32, 0.70, -0.32, 0.8, 0, 1, 0);

//Flower2
for (int i = 0; i < numberOfTrianglesForFlower; i++) {
	Triangle(-0.33 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i - 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i - 10)),
		-0.33 + 0.10 * cos(6.28 / numberOfTrianglesForFlower * i), 0.66 + 0.10 * sin(6.28 / numberOfTrianglesForFlower * i),
		-0.33 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i + 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i + 10)),
		1, 0.5, 0.1);
}

//InnerOfFlower2
for (int i = 0; i < numberOfTrianglesForInnerOfFlower; i++) {
	Triangle(-0.33 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)),
		-0.33 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * i), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * i),
		-0.33 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)),
		1, 1, 0);
}

//StemFlower3
Triangle(-0.14, 0.8, -0.14, 0.70, -0.12, 0.70, 0, 1, 0);
Triangle(-0.14, 0.8, -0.12, 0.70, -0.12, 0.8, 0, 1, 0);

//Flower3
for (int i = 0; i < numberOfTrianglesForFlower; i++) {
	Triangle(-0.13 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i - 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i - 10)),
		-0.13 + 0.10 * cos(6.28 / numberOfTrianglesForFlower * i), 0.66 + 0.10 * sin(6.28 / numberOfTrianglesForFlower * i),
		-0.13 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i + 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i + 10)),
		1, 0.415, 0.722);
}

//InnerOfFlower3
for (int i = 0; i < numberOfTrianglesForInnerOfFlower; i++) {
	Triangle(-0.13 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)),
		-0.13 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * i), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * i),
		-0.13 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)),
		1, 1, 0);
}

//StemFlower4
Triangle(0.77, 0.8, 0.77, 0.70, 0.79, 0.70, 0, 1, 0);
Triangle(0.77, 0.8, 0.79, 0.70, 0.79, 0.8, 0, 1, 0);

//Flower4
for (int i = 0; i < numberOfTrianglesForFlower; i++) {
	Triangle(0.78 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i - 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i - 10)),
		0.78 + 0.10 * cos(6.28 / numberOfTrianglesForFlower * i), 0.66 + 0.10 * sin(6.28 / numberOfTrianglesForFlower * i),
		0.78 + 0.05 * cos(6.28 / numberOfTrianglesForFlower * (i + 10)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForFlower * (i + 10)),
		0.5, 0, 0.5);
}

//InnerOfFlower4
for (int i = 0; i < numberOfTrianglesForInnerOfFlower; i++) {
	Triangle(0.78 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i - 5)),
		0.78 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * i), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * i),
		0.78 + 0.05 * cos(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)), 0.66 + 0.05 * sin(6.28 / numberOfTrianglesForInnerOfFlower * (i + 5)),
		1, 1, 0);
}

int trianglesForRainbow = 64;
int rainbowLeft = (trianglesForRainbow / 2) + (trianglesForRainbow / 8);
int rainbowRight = trianglesForRainbow - (trianglesForRainbow / 8);

//Rainbow1
for (int i = 0; i < trianglesForRainbow; i++) {
	if (i > rainbowLeft && i < rainbowRight) {
		Triangle(-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i - 4)), -0.00 + 0.50 * sin(6.28 / trianglesForRainbow * (i - 4)),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * i), -0.00 + 0.50 * sin(6.28 / trianglesForRainbow * i),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i + 4)), -0.00 + 0.50 * sin(6.28 / trianglesForRainbow * (i + 4)),
			1, 1, 0);
	}
}

//Rainbow2
for (int i = 0; i < trianglesForRainbow; i++) {
	if (i > rainbowLeft && i < rainbowRight) {
		Triangle(-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i - 4)), -0.04 + 0.50 * sin(6.28 / trianglesForRainbow * (i - 4)),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * i), -0.04 + 0.50 * sin(6.28 / trianglesForRainbow * i),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i + 4)), -0.04 + 0.50 * sin(6.28 / trianglesForRainbow * (i + 4)),
			0.5, 0, 0.5);
	}
}

//Rainbow3
for (int i = 0; i < trianglesForRainbow; i++) {
	if (i > rainbowLeft && i < rainbowRight) {
		Triangle(-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i - 4)), -0.08 + 0.50 * sin(6.28 / trianglesForRainbow * (i - 4)),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * i), -0.08 + 0.50 * sin(6.28 / trianglesForRainbow * i),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i + 4)), -0.08 + 0.50 * sin(6.28 / trianglesForRainbow * (i + 4)),
			1, 0.5, 0.1);
	}
}

//Rainbow4
for (int i = 0; i < trianglesForRainbow; i++) {
	if (i > rainbowLeft && i < rainbowRight) {
		Triangle(-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i - 4)), -0.12 + 0.50 * sin(6.28 / trianglesForRainbow * (i - 4)),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * i), -0.12 + 0.50 * sin(6.28 / trianglesForRainbow * i),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i + 4)), -0.12 + 0.50 * sin(6.28 / trianglesForRainbow * (i + 4)),
			1, 1, 0);
	}
}

//Rainbow5
for (int i = 0; i < trianglesForRainbow; i++) {
	if (i > rainbowLeft && i < rainbowRight) {
		Triangle(-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i - 4)), -0.16 + 0.50 * sin(6.28 / trianglesForRainbow * (i - 4)),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * i), -0.16 + 0.50 * sin(6.28 / trianglesForRainbow * i),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i + 4)), -0.16 + 0.50 * sin(6.28 / trianglesForRainbow * (i + 4)),
			0, 0.5, 1);
	}
}

//Rainbow6
for (int i = 0; i < trianglesForRainbow; i++) {
	if (i > rainbowLeft && i < rainbowRight) {
		Triangle(-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i - 4)), -0.20 + 0.50 * sin(6.28 / trianglesForRainbow * (i - 4)),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * i), -0.20 + 0.50 * sin(6.28 / trianglesForRainbow * i),
			-0.4 + 0.50 * cos(6.28 / trianglesForRainbow * (i + 4)), -0.20 + 0.50 * sin(6.28 / trianglesForRainbow * (i + 4)),
			1, 0.5, 0.1);
	}
}
	// Translate of +2 on the x axis, and -1 on the y axis
	//Last column
	const float MT1[] =  {
			   1.0f,		0.0f,		0.0f,		2.0f,
			   0.0f,		1.0f,		0.0f,	   -1.0f,
			   0.0f,		0.0f,		1.0f,		0.0f,
			   0.0f,		0.0f,		0.0f,		1.0f};
			   
	// Rotate of 45 degrees on the x axis
	//cos, -sin, sin, cos
	const float MT2[] =  {
			   1.0f,		0.0f,		0.0f,		0.0f,
			   0.0f,		float(sqrt(2) / 2),		float(-sqrt(2) / 2),		0.0f,
			   0.0f,		float(sqrt(2) / 2),		float(sqrt(2) / 2),		0.0f,
			   0.0f,		0.0f,		0.0f,		1.0f};
			   
	// Make the object 2 times smaller
	//Half principal diagonal
	const float MT3[] =  {
			   0.5f,		0.0f,		0.0f,		0.0f,
			   0.0f,		0.5f,		0.0f,		0.0f,
			   0.0f,		0.0f,		0.5f,		0.0f,
			   0.0f,		0.0f,		0.0f,		1.0f};
			   
	// Make the object 2 times longer on the z axis, and half on the other axis
	//Nearly same as before
	const float MT4[] =  {
			   0.5f,		0.0f,		0.0f,		0.0f,
			   0.0f,		0.5f,		0.0f,		0.0f,
			   0.0f,		0.0f,		2.0f,		0.0f,
			   0.0f,		0.0f,		0.0f,		1.0f};

	// Mirror over the z axis
	//- on the principal diagonal
	const float MT5[] =  {
			   -1.0f,		0.0f,		0.0f,		0.0f,
			   0.0f,		-1.0f,		0.0f,		0.0f,
			   0.0f,		0.0f,	    1.0f,		0.0f,
			   0.0f,		0.0f,		0.0f,		1.0f};
			   
	// Flatten over the z axis
	//0 on the principal diagonal
	const float MT6[] =  {
			   1.0f,		0.0f,		0.0f,		0.0f,
			   0.0f,		1.0f,		0.0f,		0.0f,
			   0.0f,		0.0f,		0.0f,		0.0f,
			   0.0f,		0.0f,		0.0f,		1.0f};

	// Make a shear along the Y axis, with a factor of 1 along the x axis
	//Second column
	const float MT7[] =  {
			   1.0f,		1.0f,		0.0f,		0.0f,
			   0.0f,		1.0f,		0.0f,		0.0f,
			   0.0f,		0.0f,		1.0f,		0.0f,
			   0.0f,		0.0f,		0.0f,		1.0f};

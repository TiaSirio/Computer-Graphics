glm::mat4 MT1, MT2, MT3, MT4;

MT1 = glm::mat4(1);
MT2 = glm::mat4(1);
MT3 = glm::mat4(1);
MT4 = glm::mat4(1);

// Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). The x-axis can be aligned to the arbitrary axis after a rotation of 30 degrees around the z-axis, and then -60 degrees around the y-axis.

//Inverse of the translation on 1, 0, -1.
MT1 = inverse(translate(glm::mat4(1), glm::vec3(1, 0, -1))) * MT1;

//Inverse of the rotation on y-axis.
MT1 = inverse(rotate(glm::mat4(1), glm::radians(-60.0f), glm::vec3(0, 1, 0))) * MT1;

//Inverse of the rotation on z-axis.
MT1 = inverse(rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0, 0, 1))) * MT1;

//Rotation on x-axis.
MT1 = rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(1, 0, 0)) * MT1;

//Rotation on z-axis.
MT1 = rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0, 0, 1)) * MT1;

//Rotation on y-axis.
MT1 = rotate(glm::mat4(1), glm::radians(-60.0f), glm::vec3(0, 1, 0)) * MT1;

//Translation on 1, 0, -1.
MT1 = translate(glm::mat4(1), glm::vec3(1, 0, -1)) * MT1;


// Half the size of an object, using as fixed point (5,0,-2).

//Inverse of the translation on 5, 0, -2.
MT2 = inverse(translate(glm::mat4(1), glm::vec3(5, 0, -2))) * MT2;

//Half the size of object.
MT2 = scale(glm::mat4(1), glm::vec3(0.5, 0.5, 0.5)) * MT2;

//Translation on 5, 0, -2.
MT2 = translate(glm::mat4(1), glm::vec3(5, 0, -2)) * MT2;


// Mirror the starship along a plane passing through (1,1,1), and obtained rotating 15 degree around the x axis the xz plane.

//Inverse of the translation on 1, 1, 1.
MT3 = inverse(translate(glm::mat4(1), glm::vec3(1, 1, 1))) * MT3;

//Inverso of rotation on x-axis.
MT3 = inverse(rotate(glm::mat4(1), glm::radians(15.0f), glm::vec3(1, 0, 0))) * MT3;

//Mirroring on plane xz.
MT3 = scale(glm::mat4(1), glm::vec3(1, -1, 1)) * MT3;

//Rotation on x-axis.
MT3 = rotate(glm::mat4(1), glm::radians(15.0f), glm::vec3(1, 0, 0)) * MT3;

//Translation on 1, 1, 1.
MT3 = translate(glm::mat4(1), glm::vec3(1, 1, 1)) * MT3;

// Apply the inverse of the following sequence of transforms: Translation of (0, 0, 5) then rotation of 30 degree around the Y axis, and finally a uniform scaling of a factor of 3.

//(A*B*C)^-1 = (C^-1)*(B^-1)*(A^-1).

//Inverse of uniform scaling of a factor of 3.
MT4 = inverse(scale(glm::mat4(1), glm::vec3(3, 3, 3))) * MT4;

//Inverse of rotation of 30 degree around the Y axis.
MT4 = inverse(rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0, 1, 0))) * MT4;

//Inverse of Translation of (0, 0, 5).
MT4 = inverse(translate(glm::mat4(1), glm::vec3(0, 0, 5))) * MT4;
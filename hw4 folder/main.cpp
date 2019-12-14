#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Problem1.h"
#include "Shader.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;

	Vector3d center;
	center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    scene.addShape(new Sphere(center, 2.0, 0.5, 0.1, 0.1));

	center[0] = -6;
	center[1] = 6;
	center[2] = 6;

	Vector3d normal;
	normal[0] = 0;
	normal[1] = 0;
	normal[2] = 5;
	scene.addShape(new Plane(center, normal, 0.1, 0.1, 0.5));
	
	/*center[0] = .5;
	center[1] = 1.25;
	center[2] = 2.75;
	scene.addShape(new Sphere(center, 0.5, 0.3, 0.6, 0.4));*/

    scene.render(im);

    im.writePNG("test.png");

    return 0;
}

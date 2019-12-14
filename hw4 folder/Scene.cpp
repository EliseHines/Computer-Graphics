#include "Scene.h"
#include "Shader.h"
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

Vector3d reflect(const Vector3d &I, const Vector3d &N)
{
	return I - 2 * I.dot(N) * N;
}

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }

    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int l) {
    HitRecord r = closestHit(ray);
	double bias = 1e-4;
	int maxrecursion = 2;
    Vector3d result;
    result[0] = result[1] = result[2] = 0;

	Vector3d L = (lightPos - r.position).normalized();

    if (r.t < numeric_limits<double>::epsilon()) return result;

	//Calculating diffuse component
    double intensity = L.dot(r.normal); //diffuse intensity
    if (intensity < 0) intensity = 0;

	//Calculating specular component
	double specStr = 0.3; 
	Vector3d viewDir = (ray.origin - r.position).normalized();
	Vector3d R = reflect(-L, r.normal);
	double spec_intensity = pow(max(0.0, viewDir.dot(R)), 20);
	double specular = specStr * spec_intensity;

	double ambient = 0.2;
	Ray oppRay;
	oppRay.direction = L;
	for (int i = 0; i < 3; i++) {
		oppRay.origin[i] = r.position[i] + bias;
	}

	for (unsigned int i = 0; i < shapes.size(); i++) {
		HitRecord r = shapes[i]->intersect(oppRay);
		if (r.t > 0.001) return result;
	}

	for (int i = 0; i < 3; i++) {
		result[i] = intensity * r.color[i] + specular + ambient;
	}

	double kS = 0.3;
	if (l < maxrecursion) {
		Ray rRay;
		for (int i = 0; i < 3; i++) {
			rRay.origin[i] = r.position[i] + bias;
		}
		rRay.direction = R;
		//result += kS * trace(rRay, l + 1);
		for (unsigned int i = 0; i < shapes.size(); i++) {
			HitRecord r = shapes[i]->intersect(rRay);
			if (r.t > 0.001) result += kS * r.color;
		}
		
	}

    return result;
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay, 0);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}

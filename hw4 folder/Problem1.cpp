#include "Problem1.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Plane::intersect(const Ray &ray) {
	//HitRecord is a struct with Eigen::Vector3 position, normal
	//and a double t
	HitRecord result;
	result.t = -1;
	Eigen::Vector3d color;
	color[0] = re;
	color[1] = gr;
	color[2] = bl;
	result.color = color;

	//math from 
	//https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html#SECTION00023400000000000000

	Eigen::Vector3d N = n; 
	Eigen::Vector3d Q = c;
	Eigen::Vector3d E = ray.origin;
	Eigen::Vector3d D = ray.direction;

	double dDotN = N.dot(D);
	if (dDotN == 0) return result;
	
	double t = N.dot(Q - E) / dDotN;

	if (t < 0) return result;
	
	//hit!

	result.t = t;
	result.position = E + result.t * D;
	result.normal = (result.position - c).normalized();
	return result;
}

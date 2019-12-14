#ifndef PROBLEM1_H
#define PROBLEM1_H

#include "Shape.h"

namespace Raytracer148 {
	class Plane : public Shape {
	public:
		Plane(Eigen::Vector3d &center, Eigen::Vector3d &normal, double red, double green, double blue) : c(center), n(normal), re(red), gr(green), bl(blue) {}

		virtual HitRecord intersect(const Ray &ray);

	private:
		Eigen::Vector3d c;
		Eigen::Vector3d n;
		double re, gr, bl;
	};
}

#endif

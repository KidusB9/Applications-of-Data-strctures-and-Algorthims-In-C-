#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

struct Vec3 {
    double x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 operator - () const { return Vec3(-x, -y, -z); }
    Vec3 operator + (const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator - (const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator * (double d) const { return Vec3(x * d, y * d, z * d); }
    Vec3 operator / (double d) const { return Vec3(x / d, y / d, z / d); }

    double dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 cross(const Vec3& v) const {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    double norm() const { return std::sqrt(x * x + y * y + z * z); }
    Vec3 normalized() const {
        double n = norm();
        return Vec3(x / n, y / n, z / n);
    }
};

struct Ray {
    Vec3 origin, direction;
    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction.normalized()) {}
};

struct Sphere {
    Vec3 center;
    double radius;
    Sphere(const Vec3& center, double radius) : center(center), radius(radius) {}

    bool intersect(const Ray& ray, double& t) const {
        const Vec3 oc = ray.origin - center;
        const double b = oc.dot(ray.direction);
        const double c = oc.dot(oc) - radius * radius;
        double delta = b * b - c;

        if (delta > 0) {
            const double sqrt_delta = std::sqrt(delta);
            const double t1 = -b - sqrt_delta;
            const double t2 = -b + sqrt_delta;

            t = (t1 < t2) ? t1 : t2;
            return true;
        }
        return false;
    }
};

Vec3 trace(const Ray& ray, const Sphere& sphere) {
    double t = 0;
    if (sphere.intersect(ray, t)) {
        Vec3 point = ray.origin + ray.direction * t;
        Vec3 normal = (point - sphere.center).normalized();
        double intensity = std::max(normal.dot(Vec3(1, -1, 1).normalized()), 0.0);
        return Vec3(1, 0, 0) * intensity;  // Red color
    }
    return Vec3(0.7, 0.6, 0.8);  // Background color
}

int main() {
    const int width = 800;
    const int height = 600;
    const Vec3 camera(0, 0, -5);
    const Sphere sphere(Vec3(0, 0, 0), 1);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            double x = (2 * (i + 0.5) / (double)width - 1) * width / (double)height;
            double y = -(2 * (j + 0.5) / (double)height - 1);
            Ray ray(camera, Vec3(x, y, 0) - camera);

            Vec3 color = trace(ray, sphere);
            std::cout << (int)(255 * color.x) << ' '
                      << (int)(255 * color.y) << ' '
                      << (int)(255 * color.z) << '\n';
        }
    }

    return 0;
}

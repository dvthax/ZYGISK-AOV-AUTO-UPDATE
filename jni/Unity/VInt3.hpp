#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

struct VInt3
{
    union
    {
        struct
        {
            int X;
            int Y;
            int Z;
        };
        int data[3];
    };


    /**
     * Constructors.
     */
    inline VInt3();
    inline VInt3(int data[]);
    inline VInt3(int value);
    inline VInt3(int x, int y);
    inline VInt3(int x, int y, int z);


    /**
     * Constants for common vectors.
     */
    static inline VInt3 Zero();
    static inline VInt3 One();
    static inline VInt3 Right();
    static inline VInt3 Left();
    static inline VInt3 Up();
    static inline VInt3 Down();
    static inline VInt3 Forward();
    static inline VInt3 Backward();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline int Angle(VInt3 a, VInt3 b);

    /**
     * Returns a vector with its magnitude clamped to maxLength.
     * @param vector: The target vector.
     * @param maxLength: The maximum length of the return vector.
     * @return: A new vector.
     */
    static inline VInt3 ClampMagnitude(VInt3 vector, int maxLength);

    /**
     * Returns the component of a in the direction of b (scalar projection).
     * @param a: The target vector.
     * @param b: The vector being compared against.
     * @return: A scalar value.
     */
    static inline int Component(VInt3 a, VInt3 b);

    /**
     * Returns the cross product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A new vector.
     */
    static inline VInt3 Cross(VInt3 lhs, VInt3 rhs);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline int Distance(VInt3 a, VInt3 b);

    static inline char ToChar(VInt3 a);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline int Dot(VInt3 lhs, VInt3 rhs);

    /**
     * Converts a spherical representation of a vector into cartesian
     * coordinates.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the XY plane from the X axis.
     * @param phi: The angle from the positive Z axis to the vector.
     * @return: A new vector.
     */
    static inline VInt3 FromSpherical(int rad, int theta, int phi);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go beyond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline VInt3 Lerp(VInt3 a, VInt3 b, int t);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline VInt3 LerpUnclamped(VInt3 a, VInt3 b, int t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline int Magnitude(VInt3 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline VInt3 Max(VInt3 a, VInt3 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline VInt3 Min(VInt3 a, VInt3 b);

    /**
     * Returns a vector "maxDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param maxDistanceDelta: The maximum distance to move.
     * @return: A new vector.
     */
    static inline VInt3 MoveTowards(VInt3 current, VInt3 target,
                                      int maxDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline VInt3 Normalized(VInt3 v);

    /**
     * Returns an arbitrary vector orthogonal to the input.
     * This vector is not normalized.
     * @param v: The input vector.
     * @return: A new vector.
     */
    static inline VInt3 Orthogonal(VInt3 v);

    /**
     * Creates a new coordinate system out of the three vectors.
     * Normalizes "normal", normalizes "tangent" and makes it orthogonal to
     * "normal" and normalizes "binormal" and makes it orthogonal to both
     * "normal" and "tangent".
     * @param normal: A reference to the first axis vector.
     * @param tangent: A reference to the second axis vector.
     * @param binormal: A reference to the third axis vector.
     */
    static inline void OrthoNormalize(VInt3 &normal, VInt3 &tangent,
                                      VInt3 &binormal);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline VInt3 Project(VInt3 a, VInt3 b);

    /**
     * Returns a vector projected onto a plane orthogonal to "planeNormal".
     * This can be visualized as the shadow of the vector onto the plane, if
     * the light source were in the direction of the plane normal.
     * @param vector: The vector to project.
     * @param planeNormal: The normal of the plane onto which to project.
     * @param: A new vector.
     */
    static inline VInt3 ProjectOnPlane(VInt3 vector, VInt3 planeNormal);

    /**
     * Returns a vector reflected off the plane orthogonal to the normal.
     * The input vector is pointed inward, at the plane, and the return vector
     * is pointed outward from the plane, like a beam of light hitting and then
     * reflecting off a mirror.
     * @param vector: The vector traveling inward at the plane.
     * @param planeNormal: The normal of the plane off of which to reflect.
     * @return: A new vector pointing outward from the plane.
     */
    static inline VInt3 Reflect(VInt3 vector, VInt3 planeNormal);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline VInt3 Reject(VInt3 a, VInt3 b);

    /**
     * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
     * This treats the vectors as directions and will linearly interpolate
     * between their magnitudes by "maxMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate away from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param maxRadiansDelta: The maximum number of radians to rotate.
     * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline VInt3 RotateTowards(VInt3 current, VInt3 target,
                                        int maxRadiansDelta,
                                        int maxMagnitudeDelta);

    /**
     * Multiplies two vectors element-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline VInt3 Scale(VInt3 a, VInt3 b);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline VInt3 Slerp(VInt3 a, VInt3 b, int t);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline VInt3 SlerpUnclamped(VInt3 a, VInt3 b, int t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the exact length
     * is not important, and much time can be saved by not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline int SqrMagnitude(VInt3 v);

    /**
     * Calculates the spherical coordinate space representation of a vector.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the XY plane from the X axis.
     * @param phi: The angle from the positive Z axis to the vector.
     */
    static inline void ToSpherical(VInt3 vector, int &rad, int &theta,
                                   int &phi);


    /**
     * Operator overloading.
     */
    inline struct VInt3& operator+=(const int rhs);
    inline struct VInt3& operator-=(const int rhs);
    inline struct VInt3& operator*=(const int rhs);
    inline struct VInt3& operator/=(const int rhs);
    inline struct VInt3& operator+=(const VInt3 rhs);
    inline struct VInt3& operator-=(const VInt3 rhs);
};

inline VInt3 operator-(VInt3 rhs);
inline VInt3 operator+(VInt3 lhs, const int rhs);
inline VInt3 operator-(VInt3 lhs, const int rhs);
inline VInt3 operator*(VInt3 lhs, const int rhs);
inline VInt3 operator/(VInt3 lhs, const int rhs);
inline VInt3 operator+(const int lhs, VInt3 rhs);
inline VInt3 operator-(const int lhs, VInt3 rhs);
inline VInt3 operator*(const int lhs, VInt3 rhs);
inline VInt3 operator/(const int lhs, VInt3 rhs);
inline VInt3 operator+(VInt3 lhs, const VInt3 rhs);
inline VInt3 operator-(VInt3 lhs, const VInt3 rhs);
inline bool operator==(const VInt3 lhs, const VInt3 rhs);
inline bool operator!=(const VInt3 lhs, const VInt3 rhs);



/*******************************************************************************
 * Implementation
 */

VInt3::VInt3() : X(0), Y(0), Z(0) {}
VInt3::VInt3(int data[]) : X(data[0]), Y(data[1]), Z(data[2]) {}
VInt3::VInt3(int value) : X(value), Y(value), Z(value) {}
VInt3::VInt3(int x, int y) : X(x), Y(y), Z(0) {}
VInt3::VInt3(int x, int y, int z) : X(x), Y(y), Z(z) {}


VInt3 VInt3::Zero() { return VInt3(0, 0, 0); }
VInt3 VInt3::One() { return VInt3(1, 1, 1); }
VInt3 VInt3::Right() { return VInt3(1, 0, 0); }
VInt3 VInt3::Left() { return VInt3(-1, 0, 0); }
VInt3 VInt3::Up() { return VInt3(0, 1, 0); }
VInt3 VInt3::Down() { return VInt3(0, -1, 0); }
VInt3 VInt3::Forward() { return VInt3(0, 0, 1); }
VInt3 VInt3::Backward() { return VInt3(0, 0, -1); }


int VInt3::Angle(VInt3 a, VInt3 b)
{
    int v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

VInt3 VInt3::ClampMagnitude(VInt3 vector, int maxLength)
{
    int length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

int VInt3::Component(VInt3 a, VInt3 b)
{
    return Dot(a, b) / Magnitude(b);
}

VInt3 VInt3::Cross(VInt3 lhs, VInt3 rhs)
{
    int x = lhs.Y * rhs.Z - lhs.Z * rhs.Y;
    int y = lhs.Z * rhs.X - lhs.X * rhs.Z;
    int z = lhs.X * rhs.Y - lhs.Y * rhs.X;
    return VInt3(x, y, z);
}

int VInt3::Distance(VInt3 a, VInt3 b)
{
    return VInt3::Magnitude(a - b);
}

int VInt3::Dot(VInt3 lhs, VInt3 rhs)
{
    return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
}

VInt3 VInt3::FromSpherical(int rad, int theta, int phi)
{
    VInt3 v;
    v.X = rad * sin(theta) * cos(phi);
    v.Y = rad * sin(theta) * sin(phi);
    v.Z = rad * cos(theta);
    return v;
}

VInt3 VInt3::Lerp(VInt3 a, VInt3 b, int t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

VInt3 VInt3::LerpUnclamped(VInt3 a, VInt3 b, int t)
{
    return (b - a) * t + a;
}

int VInt3::Magnitude(VInt3 v)
{
    return sqrt(SqrMagnitude(v));
}

VInt3 VInt3::Max(VInt3 a, VInt3 b)
{
    int x = a.X > b.X ? a.X : b.X;
    int y = a.Y > b.Y ? a.Y : b.Y;
    int z = a.Z > b.Z ? a.Z : b.Z;
    return VInt3(x, y, z);
}

VInt3 VInt3::Min(VInt3 a, VInt3 b)
{
    int x = a.X > b.X ? b.X : a.X;
    int y = a.Y > b.Y ? b.Y : a.Y;
    int z = a.Z > b.Z ? b.Z : a.Z;
    return VInt3(x, y, z);
}

VInt3 VInt3::MoveTowards(VInt3 current, VInt3 target,
                             int maxDistanceDelta)
{
    VInt3 d = target - current;
    int m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

VInt3 VInt3::Normalized(VInt3 v)
{
    int mag = Magnitude(v);
    if (mag == 0)
        return VInt3::Zero();
    return v / mag;
}

VInt3 VInt3::Orthogonal(VInt3 v)
{
    return v.Z < v.X ? VInt3(v.Y, -v.X, 0) : VInt3(0, -v.Z, v.Y);
}

void VInt3::OrthoNormalize(VInt3 &normal, VInt3 &tangent,
                             VInt3 &binormal)
{
    normal = Normalized(normal);
    tangent = ProjectOnPlane(tangent, normal);
    tangent = Normalized(tangent);
    binormal = ProjectOnPlane(binormal, tangent);
    binormal = ProjectOnPlane(binormal, normal);
    binormal = Normalized(binormal);
}

VInt3 VInt3::Project(VInt3 a, VInt3 b)
{
    int m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

VInt3 VInt3::ProjectOnPlane(VInt3 vector, VInt3 planeNormal)
{
    return Reject(vector, planeNormal);
}

VInt3 VInt3::Reflect(VInt3 vector, VInt3 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

VInt3 VInt3::Reject(VInt3 a, VInt3 b)
{
    return a - Project(a, b);
}

VInt3 VInt3::RotateTowards(VInt3 current, VInt3 target,
                               int maxRadiansDelta,
                               int maxMagnitudeDelta)
{
    int magCur = Magnitude(current);
    int magTar = Magnitude(target);
    int newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    int totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    VInt3 axis = Cross(current, target);
    int magAxis = Magnitude(axis);
    if (magAxis == 0)
        axis = Normalized(Cross(current, current + VInt3(3.95, 5.32, -4.24)));
    else
        axis /= magAxis;
    current = Normalized(current);
    VInt3 newVector = current * cos(maxRadiansDelta) +
                        Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

VInt3 VInt3::Scale(VInt3 a, VInt3 b)
{
    return VInt3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
}

VInt3 VInt3::Slerp(VInt3 a, VInt3 b, int t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

VInt3 VInt3::SlerpUnclamped(VInt3 a, VInt3 b, int t)
{
    int magA = Magnitude(a);
    int magB = Magnitude(b);
    a /= magA;
    b /= magB;
    int dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    int theta = acos(dot) * t;
    VInt3 relativeVec = Normalized(b - a * dot);
    VInt3 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

int VInt3::SqrMagnitude(VInt3 v)
{
    return v.X * v.X + v.Y * v.Y + v.Z * v.Z;
}

void VInt3::ToSpherical(VInt3 vector, int &rad, int &theta,
                          int &phi)
{
    rad = Magnitude(vector);
    int v = vector.Z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.Y, vector.X);
}


struct VInt3& VInt3::operator+=(const int rhs)
{
    X += rhs;
    Y += rhs;
    Z += rhs;
    return *this;
}

struct VInt3& VInt3::operator-=(const int rhs)
{
    X -= rhs;
    Y -= rhs;
    Z -= rhs;
    return *this;
}

struct VInt3& VInt3::operator*=(const int rhs)
{
    X *= rhs;
    Y *= rhs;
    Z *= rhs;
    return *this;
}

struct VInt3& VInt3::operator/=(const int rhs)
{
    X /= rhs;
    Y /= rhs;
    Z /= rhs;
    return *this;
}

struct VInt3& VInt3::operator+=(const VInt3 rhs)
{
    X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;
    return *this;
}

struct VInt3& VInt3::operator-=(const VInt3 rhs)
{
    X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;
    return *this;
}

char VInt3::ToChar(VInt3 a) {
    const char* x = (const char*)(int)a.X;
    const char* y = (const char*)(int)a.Y;
    const char* z = (const char*)(int)a.Z;
    char buffer[25];
    strncpy(buffer, x, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, y, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, z, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    return buffer[24];
}

VInt3 operator-(VInt3 rhs) { return rhs * -1; }
VInt3 operator+(VInt3 lhs, const int rhs) { return lhs += rhs; }
VInt3 operator-(VInt3 lhs, const int rhs) { return lhs -= rhs; }
VInt3 operator*(VInt3 lhs, const int rhs) { return lhs *= rhs; }
VInt3 operator/(VInt3 lhs, const int rhs) { return lhs /= rhs; }
VInt3 operator+(const int lhs, VInt3 rhs) { return rhs += lhs; }
VInt3 operator-(const int lhs, VInt3 rhs) { return rhs -= lhs; }
VInt3 operator*(const int lhs, VInt3 rhs) { return rhs *= lhs; }
VInt3 operator/(const int lhs, VInt3 rhs) { return rhs /= lhs; }
VInt3 operator+(VInt3 lhs, const VInt3 rhs) { return lhs += rhs; }
VInt3 operator-(VInt3 lhs, const VInt3 rhs) { return lhs -= rhs; }

bool operator==(const VInt3 lhs, const VInt3 rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
}

bool operator!=(const VInt3 lhs, const VInt3 rhs)
{
    return !(lhs == rhs);
}

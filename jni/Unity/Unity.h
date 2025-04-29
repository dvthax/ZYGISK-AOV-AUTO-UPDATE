
#include <android/log.h>
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Quaternion.hpp"
#include <ctime> // time header to support timeval structure
#include <set>   //std set (bionic linker)
#include <locale>
#include <codecvt>
#include <sstream>

typedef struct _monoString
{
    void *klass;
    void *monitor;
    int length;
    char chars[1];

    std::string get_string()
    {
        std::u16string u16_string(reinterpret_cast<const char16_t *>(chars));
        std::wstring wide_string(u16_string.begin(), u16_string.end());
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        return convert.to_bytes(wide_string);
    }

    void set(std::string str)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        std::wstring wa = convert.from_bytes(str);
        length = str.length();
        std::u16string basicString = std::u16string(wa.begin(), wa.end());
        const char16_t *cStr = basicString.c_str();
        memcpy(getChars(), cStr, getLength() * 2);
    }

    const char *get_const_char()
    {
        return get_string().c_str();
    }

    char *getChars()
    {
        return chars;
    }

    int getLength()
    {
        return length;
    }
} monoString;

float NormalizeAngle(float angle)
{
    while (angle > 360)
        angle -= 360;
    while (angle < 0)
        angle += 360;
    return angle;
}

Vector3 NormalizeAngles(Vector3 angles)
{
    angles.x = NormalizeAngle(angles.x);
    angles.y = NormalizeAngle(angles.y);
    angles.z = NormalizeAngle(angles.z);
    return angles;
}

Vector3 ToEulerRad(Quaternion q1)
{
    float sqw = q1.w * q1.w;
    float sqx = q1.x * q1.x;
    float sqy = q1.y * q1.y;
    float sqz = q1.z * q1.z;
    float unit = sqx + sqy + sqz + sqw;
    float test = q1.x * q1.w - q1.y * q1.z;
    Vector3 v;

    if (test > 0.4995 * unit)
    {
        v.y = 2.0 * atan2f(q1.y, q1.x);
        v.x = M_PI / 2.0;
        v.z = 0;
        return NormalizeAngles(v * Rad2Deg);
    }
    if (test < -0.4995 * unit)
    {
        v.y = -2.0 * atan2f(q1.y, q1.x);
        v.x = -M_PI / 2.0;
        v.z = 0;
        return NormalizeAngles(v * Rad2Deg);
    }
    Quaternion q(q1.w, q1.z, q1.x, q1.y);
    v.y = atan2f(2.0 * q.x * q.w + 2.0 * q.y * q.z, 1 - 2.0 * (q.z * q.z + q.w * q.w)); // yaw
    v.x = asinf(2.0 * (q.x * q.z - q.w * q.y));                                         // pitch
    v.z = atan2f(2.0 * q.x * q.y + 2.0 * q.z * q.w, 1 - 2.0 * (q.y * q.y + q.z * q.z)); // roll
    return NormalizeAngles(v * Rad2Deg);
}

Quaternion GetRotationToLocation(Vector3 targetLocation, float y_bias, Vector3 myLoc)
{
    return Quaternion::LookRotation((targetLocation + Vector3(0, y_bias, 0)) - myLoc, Vector3(0, 1, 0));
}

template <typename T>
struct monoArray
{
    void *klass;
    void *monitor;
    void *bounds;
    int max_length;
    void *vector[1];
    int getLength()
    {
        return max_length;
    }
    T getPointer()
    {
        return (T)vector;
    }
};

template <typename T>
struct monoList
{
    void *unk0;
    void *unk1;
    monoArray<T> *items;
    int size;
    int version;

    T getItems()
    {
        return items->getPointer();
    }

    int getSize()
    {
        return size;
    }

    int getVersion()
    {
        return version;
    }
};

template <typename K, typename V>
struct monoDictionary
{
    void *unk0;
    void *unk1;
    monoArray<K> *keys;
    monoArray<V> *values;
    int size;
};

union intfloat
{
    int i;
    float f;
};

int GetObscuredIntValue(uint64_t location)
{
    int cryptoKey = *(int *)location;
    int obfuscatedValue = *(int *)(location + 0x4);

    return obfuscatedValue ^ cryptoKey;
}

int GetObscuredBoolValue(uint64_t location)
{
    int cryptoKey = *(int *)(location + 0x8);
    int obfuscatedValue = *(int *)(location + 0xC);
    obfuscatedValue ^= cryptoKey;
    return obfuscatedValue;
}

void SetObscuredIntValue(uint64_t location, int value)
{
    int cryptoKey = *(int *)location;

    *(int *)(location + 0x4) = value ^ cryptoKey;
}

float GetObscuredFloatValue(uint64_t location)
{
    int cryptoKey = *(int *)location;
    int obfuscatedValue = *(int *)(location + 0x4);

    /* use this intfloat to set the integer representation of our parameter value, which will also set the float value */
    intfloat IF;
    IF.i = obfuscatedValue ^ cryptoKey;

    return IF.f;
}

void SetObscuredFloatValue(uint64_t location, float value)
{
    int cryptoKey = *(int *)location;

    /* use this intfloat to get the integer representation of our parameter value */
    intfloat IF;
    IF.f = value;

    /* use this intfloat to generate our hacked ObscuredFloat */
    intfloat IF2;
    IF2.i = IF.i ^ cryptoKey;

    *(float *)(location + 0x4) = IF2.f;
}

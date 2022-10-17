#include <Math/Vec4.hpp>
#include <Math/Vec3.hpp>

int main()
{
    Delta::Vec4 vec(3.0f);
    vec.normalize();
    vec += Delta::Vec4(1.0f);

    return 0;
}

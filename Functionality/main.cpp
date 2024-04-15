#include "Object3d.hpp"

int main()
{
    Object3d b("../sphere.obj");
    // std::cout << cube.getFaceCount() << std::endl;
    // cube.flip(); // mirror
    // cube.print(std::cout);
    // cube.save("flipped.obj");

    Object3d b_cut = b.cut([](float x, float y, float z) -> bool {
        return y - x +z< 0.5;
    });
    b_cut.save("./bunny_cut.obj");

    return 0;
}

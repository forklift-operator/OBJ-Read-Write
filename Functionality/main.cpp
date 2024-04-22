#include "Object3d.hpp"

int main()
{
    Object3d b("../bunny.obj");
    Object3d c;
    c.CreateCube(1);
    // std::cout << cube.getFaceCount() << std::endl;
    // cube.flip(); // mirror
    // cube.print(std::cout);
    // cube.save("flipped.obj");

    Object3d b_cut = b.cut([](float x, float y, float z) -> bool {
        return y + x < 2;
    });
    c.save("./cube.obj");

    return 0;
}

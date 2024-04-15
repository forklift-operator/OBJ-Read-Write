#include "Object3d.hpp"

int main()
{
    Object3d cube("cube.obj");
    std::cout << cube.getFaceCount() << std::endl;
    // cube.printFaces();

    return 0;
}

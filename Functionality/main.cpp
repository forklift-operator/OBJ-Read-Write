#include "Object3d.hpp"

int main()
{
    Object3d cube("../cube.obj");
    cube.printFaces();
    std::cout << cube.getFaceCount() << std::endl;
    cube.flip(); // mirror
    cube.save("flipped.obj");
    return 0;
}

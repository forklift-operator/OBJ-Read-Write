#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <cstring>

class Object3d
{
private:
    struct Vertex
    {
        double x, y, z;
    };

    std::vector<Vertex> vertices;
    std::vector<std::vector<int>> faces;

    void printVertices(std::ostream &out) const;
    void printFaces(std::ostream &out) const;

public:
    Object3d(){};
    Object3d(const std::string &filename);

    Object3d cut(std::function<bool(float x, float y, float z)> f) const;

    int getVertexCount();
    int getFaceCount();
    void save(const std::string &file);
    void print(std::ostream &);
    void flip();

    void CreateCube(double x);
    void CreateSphere(double r);
};

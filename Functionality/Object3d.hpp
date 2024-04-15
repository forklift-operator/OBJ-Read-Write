#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Object3d
{
private:
    struct Vertex
    {
        double x, y, z;
    };

    std::vector<Vertex> vertices;
    std::vector<std::vector<int>> faces;

public:
    Object3d(const std::string &filename);

    int getVertexCount();
    int getFaceCount();
    void save(const std::string &file);
    void print(std::ostream &);
    void flip();

    void printVertices() const;

    void printFaces() const;
    // Object3d cut(function<bool>(float x, float y, float z) f);
};

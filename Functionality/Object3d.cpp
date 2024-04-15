#include "Object3d.hpp"

void reverse_vector(std::vector<int> &face)
{
    int temp;
    for (size_t start = 0, end = face.size() - 1; start < end; start++, end--)
    {
        temp = face[start];
        face[start] = face[end];
        face[end] = temp;
    }
};

int Object3d::getVertexCount()
{
    return this->vertices.size();
}

int Object3d::getFaceCount()
{
    return this->faces.size();
}

void Object3d::save(const std::string &filename)
{
    std::ofstream file(filename);
    printVertices(file);
    printFaces(file);
    std::cout << "Saved in " << filename << std::endl;
    file.close();
}

void Object3d::print(std::ostream &out)
{
    printVertices(out);
    printFaces(out);
}

Object3d::Object3d(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error openning the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream line_file(line);
        std::string token;
        line_file >> token;

        if (token == "v")
        {
            Vertex vertex;
            line_file >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }

        if (token == "f")
        {
            std::vector<int> face;
            int vertexIndex;
            while (line_file >> vertexIndex)
            {
                face.push_back(vertexIndex - 1);
            }
            faces.push_back(face);
        }
    }
    file.close();
}

Object3d Object3d::cut(std::function<bool(float x, float y, float z)> f) const
{
    Object3d cut_object;
    cut_object.vertices = this->vertices;

    for (const std::vector face : this->faces)
    {
        bool includeFace = true;
        for (const int vertexIndex : face)
        {
            includeFace = f(this->vertices[vertexIndex].x, this->vertices[vertexIndex].y, this->vertices[vertexIndex].z);
            if (!includeFace)
                break;
        }
        if (includeFace)
        {
            cut_object.faces.push_back(face);
        }
    }

    return cut_object;
}

void Object3d::flip()
{
    for (size_t i = 0; i < this->faces.size(); i++)
    {
        reverse_vector(this->faces[i]);
    }
}

void Object3d::printVertices(std::ostream &out) const
{
    out << "# Vertices" << std::endl;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        out << "v " << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << std::endl;
    }
}

void Object3d::printFaces(std::ostream &out) const
{
    out << "# Faces" << std::endl;
    for (size_t i = 0; i < faces.size(); i++)
    {
        out << "f ";
        for (size_t j = 0; j < faces[i].size(); j++)
        {
            out << faces[i][j] + 1 << ' ';
        }
        out << std::endl;
    }
}

#include "Object3d.hpp"

void reverse_vector(std::vector<int>& face){
    double temp;
    for (size_t start = 0, end = face.size()-1; start < end; start++,end--)
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

void Object3d::flip()
{
    for (size_t i = 0; i <this->faces.size(); i++)
    {
        reverse_vector(this->faces[i]);
    }
    
}

void Object3d::printVertices() const
{
    std::cout << "# Vertices" << std::endl;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        std::cout << "v " << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << std::endl;
    }
}

void Object3d::printFaces() const
{
    std::cout << "# Faces" << std::endl;
    for (size_t i = 0; i < faces.size(); i++)
    {
        for (size_t j = 0; j < faces[i].size(); j++)
        {
            std::cout << faces[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

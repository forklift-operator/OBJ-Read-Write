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

void Object3d::CreateCube(double x)
{
    vertices.clear();

    Vertex vs[8] = {{0, 0, 0},
                    {x, 0, 0},
                    {x, 0, x},
                    {0, 0, x},
                    {0, x, 0},
                    {x, x, 0},
                    {x, x, x},
                    {0, x, x}};

    for (size_t i = 0; i < 8; i++)
    {
        vertices.push_back(vs[i]);
    }

    std::vector<int> face;
    for (size_t i = 0; i < 8; i++)
    {
        face.push_back(i);
        if (i == 3 || i == 7)
        {
            faces.push_back(face);
            face.clear();
        }
    }

    int i = 0;
    for (int i = 0; i < 3; ++i)
    {
        face.push_back(i);
        face.push_back((i + 1) % 8);
        face.push_back((i + 5) % 8);
        face.push_back((i + 5 - 1) % 8);
        faces.push_back(face);
        face.clear();
    }

    face.push_back(3);
    face.push_back(0);
    face.push_back(4);
    face.push_back(7);
    faces.push_back(face);
}

void Object3d::CreateSphere(double radius, int N)
{
    const double PI = M_PI;
    vertices.clear();

    // Iterate through phi, theta then convert radius,theta,phi to  XYZ
    for (double phi = 0.; phi <= 2*PI; phi += PI/5.) // Azimuth [0, 2PI]
    {
        std::vector<int> face;
        for (double theta = 0., i = 0; theta <= PI; theta += PI/5.,i++) // Elevation [0, PI]
        {
            Vertex point;
            point.x = radius * cos(phi) * sin(theta);
            point.y = radius * sin(phi) * sin(theta);
            point.z = radius            * cos(theta);
            vertices.push_back(point); 
        }
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



int main()
{
    Object3d b("../bunny.obj");
    Object3d c;
    c.CreateSphere(1,100);
    // std::cout << cube.getFaceCount() << std::endl;
    // cube.flip(); // mirror
    // cube.print(std::cout);
    // cube.save("flipped.obj");

    Object3d b_cut = b.cut([](float x, float y, float z) -> bool {
        return y - x < 2;
    });
    c.print(std::cout);
    c.save("sphere.obj");

    return 0;
}

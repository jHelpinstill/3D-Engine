#include "Mesh.h"
#include <cmath>
#include <iostream>

Mesh::Mesh()
{
	ID = num_meshes;
	num_meshes++;
}

Mesh::Mesh(std::string file_name)
{
	ID = num_meshes;
	num_meshes++;
	
	load(file_name);
}

void Mesh::load(std::string file_name)
{
	std::ifstream input;
	input.open(file_name);
	if(!input.is_open())
	{
		std::cout << "ERROR\tMesh #" << this->ID << " failed to open \"" << file_name << "\"" << std::endl;
		return;
	}
	while(!input.eof())
	{
		input >> num_tris;
		tris = new Triangle[num_tris];
		for(int tri = 0; tri < num_tris; tri++)
		{
			for(int vert = 0; vert < 3; vert++) for(int i = 0; i < 3; i++)
				input >> tris[tri].verts[vert].n[i];
		}
		break;
	}
	input.close();
}

Color Mesh::colorFunc(int x, int y)
{
	int r, g, b;
	r = x / 2;
	g = y / 2;
	b = sqrt(255 * 255 - r * r - g * g);
	return Color(((r << 16) & 0xff0000) | ((g << 8) & 0x00ff00) | (b & 0x0000ff));
}

int Mesh::num_meshes = 0;

Vec3 Triangle::normal()
{
	Vec3 a = verts[1] - verts[0];
	Vec3 b = verts[2] - verts[1];
	
	return Vec3::cross(a, b);
}
	

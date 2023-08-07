#ifndef MESH_
#define MESH_

#include <string>
#include <fstream>
#include <iostream>

#include "Vec3.h"
#include "Transform.h"
#include "Color.h"

struct Triangle
{
	Vec3 verts[3];
	Vec3 normal();
};

class Mesh
{
private:
	int ID;
	static int num_meshes;
	
public:	
	Triangle *tris;
	Color color = Color(0xff0000);
	int num_tris = 0;
	
	Vec3 pos = Vec3::zero;
	Transform transform;
	
	Mesh();
	Mesh(std::string file_name);
	void load(std::string file_name);
	
	// triangle fill function
	static Color colorFunc(int x, int y);
};

#endif

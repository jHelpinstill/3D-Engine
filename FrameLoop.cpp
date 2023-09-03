#include "Engine3D.h"

void Engine3D::frameLoop(HWND hwnd)
{
	static std::vector<Mesh*> mesh_list;
	static Camera camera(Vec3(-4, 2, 0.5));
	
	if(!Engine3D::init_box)
	{
		mesh_list.push_back(new Mesh("mesh_files/box_mesh.txt"));
		Engine3D::init_box = true;
		std::cout << "box added to mesh list." << std::endl;
	}
	
	render(Engine3D::frame, camera, Engine3D::mouse, Engine3D::keyboard, mesh_list);
	
}
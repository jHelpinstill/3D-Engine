#ifndef RENDER_
#define RENDER_

#include <vector>
#include <iostream>

#include "Canvas.h"
#include "MouseInfo.h"
#include "KeyInfo.h"
#include "Button.h"
#include "Camera.h"
#include "Mesh.h"
#include "Quat.h"

void render(Frame &frame, Camera &camera, MouseInfo &mouse, KeyInfo &keyboard, std::vector<Mesh*> &mesh_list);

#endif

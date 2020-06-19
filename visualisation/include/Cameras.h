#ifndef F9SIM_GRAPHICS_CAMERAS_H_
#define F9SIM_GRAPHICS_CAMERAS_H_
#pragma once


#include "CameraBaseState.h"

#include <chrono/core/ChVector.h>


namespace F9Sim {
namespace Graphics {


void Cameras_init();
chrono::Vector Cameras_getActivePos();
void Cameras_register(const CameraBaseState& cam, const std::string& name);
void Cameras_bind(const std::string& name);
void Cameras_setViewTransform(float aspectRatio);


} // namespace Graphics
} // namespace F9Sim


#endif // F9SIM_GRAPHICS_CAMERAS_H_


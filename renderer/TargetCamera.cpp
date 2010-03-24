/*  TargetCamera.cpp
 *
 *  camera that orbits around a central target position
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#include <iostream>
#include <cmath>

#include "TargetCamera.h"
 
using namespace std;
using namespace pdpd;
using namespace renderer;
using namespace geometry;

void TargetCamera::set_perspective()
{
    // check that window has width and height
    if(width == 0 || height == 0) return;
        
    /*  set view frustum
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(width > height)
    {
        float aspect = width / height;
        glFrustum(-aspect, aspect, -1.0, 1.0, near, far);
    }
    else 
    {
        float aspect = height / width;
        glFrustum(-1.0, 1.0, -aspect, aspect, near, far);
    }
    
    /*  calculate position vector to look at target from 
     *  current azimuth, elevation and distance
     */

    // init camera position with distance from target
    position.setValue(0.0, 0.0, 0.0);
    if(distance < near) distance = near; // camera can't cross clipping plane
    position[forward_index] = -distance;
    
    // azimuth is rotation around up axis
    Rotation3 rotation(up_axis, azimuth);
    
    // elevation is rotation around right axis
    Vector3 right_axis = up_axis.cross(forward_axis);
    Rotation3 roll(right_axis, -elevation);

    // rotate camera position by azimuth and elevation
    position = Matrix3x3(rotation) * Matrix3x3(roll) * position;
    
    // translate camera position relative to target position
    position += target;
    
    // init model matrix to look at target
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        position[0], position[1], position[2], 
        target[0], target[1], target[2],
        up_axis[0], up_axis[1], up_axis[2]);
}

Vector3 TargetCamera::get_ray_to(int x, int y) // TODO: clean this up
{
	Vector3	ray_from(position);
	Vector3 ray_forward = (target - position);
	ray_forward.normalize();
	ray_forward *= far;

	Vector3 right_offset;
	Vector3 vertical(up_axis);

	Vector3 horizontal;
	horizontal = ray_forward.cross(vertical);
	horizontal.normalize();
	vertical = horizontal.cross(ray_forward);
	vertical.normalize();

	float top = 1.f;
	float bottom = -1.f;
	float wtf = (top-bottom)*0.5f / near;
	float fov = 2.0 * atanf(wtf);
	float tan_fov = tanf(0.5f*fov);


	horizontal *= 2.f * far * tan_fov;
	vertical *= 2.f * far * tan_fov;

	btScalar aspect;
	if(width > height) 
	{
		aspect = width / (btScalar)height;
		horizontal *= aspect;
	}
	else 
	{
		aspect = height / (btScalar)width;
		vertical *= aspect;
	}

	Vector3 ray_to_center = ray_from + ray_forward;
	Vector3 dh = horizontal * 1.0 / float(width);
	Vector3 dv = vertical * 1.0 / float(height);

	Vector3 ray_to = ray_to_center - (0.5f * horizontal) + (0.5f * vertical);
	ray_to += x * dh;
	ray_to -= y * dv;
	return ray_to;
}

void TargetCamera::tilt(int dx, int dy)
{
    azimuth += static_cast<float>(dx);
    if(azimuth >= 360.0) azimuth -= 360.0;
    if(azimuth < 0.0) azimuth += 360.0;
    
    elevation += static_cast<float>(dy);
    if(elevation > 89.0) elevation = 89.0;
    if(elevation < -89.0) elevation = -89.0;
}
void TargetCamera::pan(int, int) {} // TODO
void TargetCamera::zoom(float) {} // TODO


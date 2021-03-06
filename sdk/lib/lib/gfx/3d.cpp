/*
 *  lib/gfx/3d.cpp
 */

#include <math.h>
#include "3d.h"
#include "controls_definition.h"
//#######################################################################################
void make3DPoint(_3d_points *_point, u32 Cell, double x, double y, double z)
{
	_point->x[Cell] = x;
	_point->y[Cell] = y;
	_point->z[Cell] = z;
}
 //#######################################################################################
void make2DPoint(_3d_points *_point, u32 Cell, double x, double y, double depth, double scaleFactor)
{
	_point->x[Cell] = x;
	_point->y[Cell] = y;
	_point->depth[Cell] = depth;
	_point->scaleFactor[Cell] = scaleFactor;
}
//#######################################################################################
void Transform3DPointsTo2DPoints(_3d_points *screenPoints, _3d_points *Points, axisRotations AxisRotations)
{
	double sx = sin(AxisRotations.x);
	double cx = cos(AxisRotations.x);
	double sy = sin(AxisRotations.y);
	double cy = cos(AxisRotations.y);
	double sz = sin(AxisRotations.z);
	double cz = cos(AxisRotations.z);
	volatile double x,y,z, xy,xz, yx,yz, zx,zy, scaleFactor;

	u32 i = Points->length;
	while (i--){
		x = Points->x[i];
		y = Points->y[i];
		z = Points->z[i];

		// rotation around x
		xy = cx*y - sx*z;
		xz = sx*y + cx*z;
		// rotation around y
		yz = cy*xz - sy*x;
		yx = sy*xz + cy*x;
		// rotation around z
		zx = cz*yx - sz*xy;
		zy = sz*yx + cz*xy;

		scaleFactor = Points->focalLength /(Points->focalLength + yz);
		x = (zx*scaleFactor) / Points->depthScale;
		y = (zy*scaleFactor) / Points->depthScale;
		z = yz / Points->depthScale;

		make2DPoint(screenPoints, i, x, y, -z, scaleFactor);
	}
	screenPoints->length = Points->length;
}
//#######################################################################################
//#######################################################################################
//#######################################################################################
void put_3d_triangle(GI::Display::Display *pDisplay, _3d_points *Points, s32 X_offset, s32 Y_offset, double X_Angle, double Y_Angle, double Z_Angle, u32 Color)
{
	_3d_points screenPoints;

	axisRotations cubeAxisRotations;
	cubeAxisRotations.y = Y_Angle;
	cubeAxisRotations.x = X_Angle;
	cubeAxisRotations.z = Z_Angle;
	Points->length = 4;
	Transform3DPointsTo2DPoints(&screenPoints, Points, cubeAxisRotations);

	//double triangle_median = (screenPoints.z[1] + screenPoints.z[2] + screenPoints.z[3]) / 3;
	u32 color = Color;//(controlls_change_color(Color, (-triangle_median))<<8) & 0xFFFFFF00;
	//s32 X_start;// = (s32)screenPoints.x[0];
	//s32 Y_start;// = (s32)screenPoints.y[0];
	//s32 X_end;// = (s32)screenPoints.x[1];
	//s32 Y_end;// = (s32)screenPoints.y[1];
/*	put_line(pDisplay, X_offset + X_start, Y_offset + Y_start, X_offset + X_end, Y_offset + Y_end, 1, color);

	X_start = (s32)screenPoints.x[0];
	Y_start = (s32)screenPoints.y[0];
	X_end = (s32)screenPoints.x[2];
	Y_end = (s32)screenPoints.y[2];
	put_line(pDisplay, X_offset + X_start, Y_offset + Y_start, X_offset + X_end, Y_offset + Y_end, 1, color);

	X_start = (s32)screenPoints.x[0];
	Y_start = (s32)screenPoints.y[0];
	X_end = (s32)screenPoints.x[3];
	Y_end = (s32)screenPoints.y[3];
	put_line(pDisplay, X_offset + X_start, Y_offset + Y_start, X_offset + X_end, Y_offset + Y_end, 1, color);*/

	s32 X_start = (s32)screenPoints.x[1];
	s32 Y_start = (s32)screenPoints.y[1];
	s32 X_end = (s32)screenPoints.x[2];
	s32 Y_end = (s32)screenPoints.y[2];
	put_line(pDisplay, X_offset + X_start, Y_offset + Y_start, X_offset + X_end, Y_offset + Y_end, 1, color);

	X_start = (s32)screenPoints.x[2];
	Y_start = (s32)screenPoints.y[2];
	X_end = (s32)screenPoints.x[3];
	Y_end = (s32)screenPoints.y[3];
	put_line(pDisplay, X_offset + X_start, Y_offset + Y_start, X_offset + X_end, Y_offset + Y_end, 1, color);

	X_start = (s32)screenPoints.x[3];
	Y_start = (s32)screenPoints.y[3];
	X_end = (s32)screenPoints.x[1];
	Y_end = (s32)screenPoints.y[1];
	put_line(pDisplay, X_offset + X_start, Y_offset + Y_start, X_offset + X_end, Y_offset + Y_end, 1, color);
}
//#######################################################################################
void put_3d_rectangle(GI::Display::Display *pDisplay, _3d_points *Points, s32 X_offset, s32 Y_offset, double X_Angle, double Y_Angle, double Z_Angle, u32 Color)
{
	_3d_points screenPoints;

	axisRotations cubeAxisRotations;
	cubeAxisRotations.y = Y_Angle;
	cubeAxisRotations.x = X_Angle;
	cubeAxisRotations.z = Z_Angle;
	Points->length = 8;
	Transform3DPointsTo2DPoints(&screenPoints, Points, cubeAxisRotations);
	put_line(pDisplay, (s32)screenPoints.x[0] + X_offset, (s32)screenPoints.y[0] + Y_offset, (s32)screenPoints.x[1] + X_offset, (s32)screenPoints.y[1] + Y_offset, 1, Color);
	put_line(pDisplay, (s32)screenPoints.x[0] + X_offset, (s32)screenPoints.y[0] + Y_offset, (s32)screenPoints.x[3] + X_offset, (s32)screenPoints.y[3] + Y_offset, 1, Color);
	put_line(pDisplay, (s32)screenPoints.x[0] + X_offset, (s32)screenPoints.y[0] + Y_offset, (s32)screenPoints.x[4] + X_offset, (s32)screenPoints.y[4] + Y_offset, 1, Color);

	put_line(pDisplay, (s32)screenPoints.x[2] + X_offset, (s32)screenPoints.y[2] + Y_offset, (s32)screenPoints.x[1] + X_offset, (s32)screenPoints.y[1] + Y_offset, 1, Color);
	put_line(pDisplay, (s32)screenPoints.x[2] + X_offset, (s32)screenPoints.y[2] + Y_offset, (s32)screenPoints.x[3] + X_offset, (s32)screenPoints.y[3] + Y_offset, 1, Color);
	put_line(pDisplay, (s32)screenPoints.x[2] + X_offset, (s32)screenPoints.y[2] + Y_offset, (s32)screenPoints.x[6] + X_offset, (s32)screenPoints.y[6] + Y_offset, 1, Color);

	put_line(pDisplay, (s32)screenPoints.x[5] + X_offset, (s32)screenPoints.y[5] + Y_offset, (s32)screenPoints.x[1] + X_offset, (s32)screenPoints.y[1] + Y_offset, 1, Color);
	put_line(pDisplay, (s32)screenPoints.x[5] + X_offset, (s32)screenPoints.y[5] + Y_offset, (s32)screenPoints.x[4] + X_offset, (s32)screenPoints.y[4] + Y_offset, 1, Color);
	put_line(pDisplay, (s32)screenPoints.x[5] + X_offset, (s32)screenPoints.y[5] + Y_offset, (s32)screenPoints.x[6] + X_offset, (s32)screenPoints.y[6] + Y_offset, 1, Color);

	put_line(pDisplay, (s32)screenPoints.x[7] + X_offset, (s32)screenPoints.y[7] + Y_offset, (s32)screenPoints.x[3] + X_offset, (s32)screenPoints.y[3] + Y_offset, 1, Color);
	put_line(pDisplay, (s32)screenPoints.x[7] + X_offset, (s32)screenPoints.y[7] + Y_offset, (s32)screenPoints.x[4] + X_offset, (s32)screenPoints.y[4] + Y_offset, 1, Color);
	put_line(pDisplay, (s32)screenPoints.x[7] + X_offset, (s32)screenPoints.y[7] + Y_offset, (s32)screenPoints.x[6] + X_offset, (s32)screenPoints.y[6] + Y_offset, 1, Color);
}
//#######################################################################################




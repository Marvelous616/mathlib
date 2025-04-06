#pragma once
#ifndef VOXEL_H
#define VOXEL_H
#include <math.h>
#include <stdint.h>
#include <stdlib.h> 
typedef uint32_t rgba;
typedef uint8_t channel;

#define RED_MASK   0xFF000000
#define GREEN_MASK 0x00FF0000
#define BLUE_MASK  0x0000FF00
#define ALPHA_MASK 0x000000FF

channel getRed(rgba color); 
channel getGreen(rgba color); 
channel getBlue(rgba color); 
channel getAlpha(rgba color);

typedef enum voxeltype { array, linked }voxeltype;

float getAlphaNormalized(rgba color);
typedef struct resolution {
	int x;
	int y;
}resolution;

typedef struct i3vector{
	int x;
	int y;
	int z;
}i3vector;
i3vector add(i3vector a, i3vector b);
i3vector sub(i3vector a, i3vector b);
i3vector scale(i3vector a, int b);
i3vector divide(i3vector a, int b);

typedef struct d3vector{
	float x;
	float y;
	float z;
}d3vector;
double magnitude(i3vector a);
d3vector addD(d3vector a, d3vector b);
d3vector subD(d3vector a, d3vector b);
d3vector scaleD(d3vector a, int b);
d3vector divD(d3vector a, int b);
double magnitudeD(d3vector a);

typedef struct voxel{
	rgba* space;
	i3vector dimensions;
	voxeltype voxel_type;
}voxel;

voxel* init_voxel(int x_dim, int y_dim, int z_dim);
float composite_alpha(float a, float b);
channel composite(channel a, channel b, float alpha_a, float alpha_b, float alpha_c);
rgba blend(rgba a, rgba b);
typedef struct camera {
	i3vector position;
	d3vector orientation;
	int render_distance;
	resolution render_res;//fov required
	float render_step;
	int fov_length;
	d3vector ray_origin;
	int max_bounces;
}camera;
camera* camera_init(voxel* drawSpace);
void cameraMovement(camera* cam, voxel* drawSpace);

typedef struct ray {
	rgba acc;
	d3vector pos;
	camera* camera;
	int max_bounces;
}ray;
ray* drawRay(camera* cam, resolution px);
#endif 
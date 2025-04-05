#include <math.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t rgba;
typedef uint8_t channel;

#define RED_MASK   0xFF000000
#define GREEN_MASK 0x00FF0000
#define BLUE_MASK  0x0000FF00
#define ALPHA_MASK 0x000000FF

channel getRed(rgba color) {return (color & RED_MASK) >> 24;}
channel getGreen(rgba color) {return (color & GREEN_MASK) >> 16;}
channel getBlue(rgba color) {return (color & BLUE_MASK) >> 8;}
channel getAlpha(rgba color) {return color & ALPHA_MASK;}
float getAlphaNormalized(rgba color) {
	float out = color & ALPHA_MASK;
	out /= 255;
	return out;
}

typedef enum { array, linked}voxeltype; 
typedef struct {
	int x;
	int y;
}resolution;
typedef struct {
	int x;
	int y;
	int z;
}i3vector;
i3vector add(i3vector a , i3vector b) {
	i3vector out = { a.x + b.x,a.y + b.y,a.z + b.z };
	return out;
};
i3vector sub(i3vector a, i3vector b) {
	i3vector out = {a.x-b.x,a.y-b.y,a.z-b.z};
	return out;
};
i3vector scale(i3vector a, int b) {
	i3vector out = { a.x * b,a.y * b,a.z * b };
	return out;
};
i3vector div(i3vector a, int b) {
	i3vector out = { a.x / b,a.y / b,a.z / b };
	return out;
};
double magnitude(i3vector a) {
	return (double)sqrt((a.x * a.x + a.y * a.y + a.z * a.z));
}
typedef struct {
	float x;
	float y;
	float z;
}d3vector;
d3vector addD(d3vector a, d3vector b) {
	d3vector out = { a.x + b.x,a.y + b.y,a.z + b.z };
	return out;
};
d3vector subD(d3vector a, d3vector b) {
	d3vector out = { a.x - b.x,a.y - b.y,a.z - b.z };
	return out;
};
d3vector scaleD(d3vector a, int b) {
	d3vector out = { a.x * b,a.y * b,a.z * b };
	return out;
};
d3vector divD(d3vector a, int b) {
	d3vector out = { a.x / b,a.y / b,a.z / b };
	return out;
};
double magnitudeD(d3vector a) {
	return (double)sqrt((a.x * a.x + a.y * a.y + a.z * a.z));
}

typedef struct {
	rgba* space;
	i3vector dimensions;
	voxeltype voxel_type;
}voxel;

voxel* init_voxel(int x_dim, int y_dim, int z_dim) {
	voxel* out = (voxel*)malloc(sizeof(voxel));
	out->space = (rgba*)malloc(x_dim * y_dim * z_dim);
	out->dimensions = (i3vector){x_dim,y_dim,z_dim};
	out->voxel_type = array;
};
//make da raymarcher
// ZTEP UNO
// make an orthogonal projector
float composite_alpha(float a, float b) {
	return a + b*(1 - a);
}
channel composite(channel a, channel b, float alpha_a, float alpha_b, float alpha_c) {
	float out;
	out = (float)a * alpha_a + (float)b * alpha_b * (1 - alpha_c);
	out /= alpha_c;
	return (channel)out;
}
rgba blend(rgba a, rgba b) {
	float c_alpha = composite_alpha(getAlphaNormalized(a), getAlphaNormalized(b));
	channel red = composite(getRed(a), getRed(b), getAlphaNormalized(a), getAlphaNormalized(b), c_alpha);
	channel green = composite(getGreen(a), getGreen(b), getAlphaNormalized(a), getAlphaNormalized(b), c_alpha);
	channel blue = composite(getBlue(a), getBlue(b), getAlphaNormalized(a), getAlphaNormalized(b), c_alpha);
	rgba out = 0x00000000;
	out |= ((rgba)red << 24);
	out |= ((rgba)green << 16);
	out |= ((rgba)blue << 8);
	out |= ((rgba)(c_alpha * 255)); //maybe use (channel) cast first
	return out;
}
//do da raymarcher
typedef struct {
	i3vector position;
	d3vector orientation;
	int render_distance;
	resolution render_res;//fov required
	float render_step;
	int fov_length;
	d3vector ray_origin;
	int max_bounces;
}camera;

camera* camera_init(voxel* drawSpace) {
	camera* out = (camera*)malloc(sizeof(camera));
	d3vector o = { 0,0,0 };
	out->orientation = o;
	out->render_distance = 20;
	resolution re = { 512,512 };
	out->render_res = re;
	out->render_step = 1;
	out->fov_length = 15;
	d3vector ou = { 0,0,0 };
	out->ray_origin = ou;//needs condition
	out->max_bounces=100;
}
void cameraMovement(camera* cam, voxel* drawSpace) {
	//movement script
}
//raymarcher

typedef struct {
	rgba acc;
	d3vector pos;
	camera* camera;
	int max_bounces;
}ray;

ray* drawRay(camera* cam, resolution px) {
	ray* out = (ray*)malloc(sizeof(ray));
	out->acc = 0;
	out->pos = cam->ray_origin;
	out->camera = cam;
	out->max_bounces = cam->max_bounces;
}
//marching loop

#include <math.h>
#include <stdint.h>
typedef unsigned int rgba;

typedef enum {
	array,
	linked
}voxeltype;

typedef struct {
	int x;
	int y;
	int z;
}i3vector;

typedef struct {
	rgba* space;
	i3vector dimensions;
	int pitch;
	voxeltype voxel_type;
	i3vector centre;
}voxel;

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

void sphere(int radius, voxel* drawspace, i3vector position) {
	i3vector pos = add(drawspace->centre, position);
	for (int i = 0; i < drawspace->dimensions.x; i++) {
		for (int j = 0; j < drawspace->dimensions.y; j++) {
			for (int k = 0; k < drawspace->dimensions.z; k++) {
				i3vector I = { i,j,k };
				if (magnitude(sub(pos, I)) <= radius) {
					*ptrindexVoxel(I,drawspace) = 4294967295;
				}
			}
		}
	}
};


voxel* init_voxel(int x_dim, int y_dim, int z_dim) {
	rgba* sp = (rgba*)malloc(x_dim * y_dim * z_dim * sizeof(rgba));
	voxel* out = (voxel*)malloc(sizeof(voxel));
	i3vector dim = { x_dim-1, y_dim-1, z_dim-1};
	out->space = sp;
	out->centre = div(dim,2);
	out->dimensions = (i3vector){ x_dim,y_dim,z_dim };
	out->pitch = x_dim * y_dim;
	out->voxel_type = array;
	return out;
};

rgba indexVoxel(i3vector index, voxel* drawspace) {
	i3vector ind = add(drawspace->centre, index);
	rgba* out = (rgba*)drawspace->space + (drawspace->dimensions.x * drawspace->dimensions.y * ind.z + drawspace->dimensions.x * ind.y + ind.x);
	return *out;
}

rgba* ptrindexVoxel(i3vector ind, voxel* drawspace) {
	rgba* out = (rgba*)drawspace->space + (drawspace->dimensions.x * drawspace->dimensions.y * ind.z + drawspace->dimensions.x * ind.y + ind.x);
	return out;
}
//make da raymarcher
// ZTEP UNO
// make an orthogonal projector
// accessing channels
Uint
//alpha blending alg
rgba blend(rgba a, rgba b) {

}
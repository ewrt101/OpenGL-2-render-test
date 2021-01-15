#ifndef MESHLOADER_H
#define MESHLOADER_H

#include "BUILD_ORDER.h"

class MeshLoader
{
    public:
    MeshLoader(const char* fname);
    MeshLoader(const char* fname, Color color);
    MeshLoader(const char* fname, Color* color);
    void draw();

    private:
    //void loadMeshFile(const char* fname);
    void normal(int tindx);
    void build(const char* fname);

    float *x, *y, *z;		//vertex coordinate arrays
    int *t1, *t2, *t3;		//triangles
    int nvrt, ntri;			//total number of vertices and triangles
    Color* color;
};

#endif
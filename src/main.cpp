#include "../include/tgaimage.h"
#include "../include/model.h"
#include <iostream>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

const int width  = 800;
const int height = 800;

void plotline(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color){
	
	bool steep = false;
	int change_x = std::abs(x1 - x0);
	int change_y = std::abs(y1 - y0);

	if (change_y > change_x){ // if the line is steep
		steep = true;
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dir = y0 > y1 ? -1 : 1; // if the slope is negative, decrease y value
	std::cout << (y1 - y0) << ", " << (x1 - x0) << "\n";
	float slope = (y1 - y0); // multiplied by the change in x to eliminate floating point division
	std::cout << slope;
	float error = 0.0;
	int y = y0;

	for (int x = x0; x < x1; x++){
		if (steep) image.set(y,x,color);
		else image.set(x,y, color);

		error += std::abs(slope);
		if (error >= 0.5 * (x1 - x0)){
			y += dir;
			error -= (x1 - x0);
		}
	}
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) { 
    plotline(t0, t1, image, color); 
    plotline(t1, t2, image, color); 
    plotline(t2, t0, image, color);
}

int main(int argc, char** argv) {
	TGAImage image(width, height, TGAImage::RGB);
	/*Model* model = new Model("obj/african_head.obj");
	for (int i=0; i<model->nfaces(); i++) { // parser obtained from tutorial
	    std::vector<int> face = model->face(i); 
	    for (int j=0; j<3; j++) { 
	        Vec3f v0 = model->vert(face[j]); 
	        Vec3f v1 = model->vert(face[(j+1)%3]); 
	        int x0 = (v0.x+1.)*width/2.; 
	        int y0 = (v0.y+1.)*height/2.; 
	        int x1 = (v1.x+1.)*width/2.; 
	        int y1 = (v1.y+1.)*height/2.; 
	        plotline(x0, y0, x1, y1, image, white); 
	    } 
	}
	image.flip_vertically();*/
	Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
	Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
	Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 
	triangle(t0[0], t0[1], t0[2], image, red); 
	triangle(t1[0], t1[1], t1[2], image, white); 
	triangle(t2[0], t2[1], t2[2], image, green);
	image.write_tga_file("output.tga");
	return 0;
}


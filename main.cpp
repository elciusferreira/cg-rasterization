#include "main.h"

void MyGlDraw(void)
{


Pixel pxl1(100, 300, 255, 0, 0, 0);
Pixel pxl2(200, 150, 0, 0, 255, 0);

Pixel pxl3(400, 300, 0, 255, 0, 0);
Pixel pxl4(300, 150, 0, 0, 255, 0);

Pixel pxl5(150, 450, 255, 0, 0, 0);
Pixel pxl6(350, 450, 0, 255, 0, 0);

Pixel pxl7(100, 400, 255, 0, 0, 0);
Pixel pxl8(400, 400, 0, 255, 0, 0);
Pixel pxl9(250, 150, 0, 0, 255, 0);

Pixel *pxl = new Pixel(80, 410, 255, 0, 0, 0);
PutPixel(pxl);

Pixel *pxl_2 = new Pixel(420, 410, 0, 255, 0, 0);
PutPixel(pxl_2);

Pixel *pxl_3 = new Pixel(250, 130, 0, 0, 255, 0);
PutPixel(pxl_3);

DrawLine(pxl1,pxl2);
DrawLine(pxl3,pxl4);
DrawLine(pxl5,pxl6);

DrawTriangle(pxl7, pxl8, pxl9);

}

int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();
	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

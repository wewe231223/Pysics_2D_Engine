#include "GL.h"

int main()
{
	// (title, width, height, use_full_screen, display_ix)
	GL gl("Canvas", 800, 600, false, 0);
	// make windowCanvas and run main loop;
	gl.run();
}
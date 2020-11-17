#include "GL.h"

int main()
{
	// (title, width, height, use_full_screen, display_ix(default = 0))
	GL gl("Canvas", 800, 600, false);
	// make windowCanvas and run main loop;
	gl.run();
}
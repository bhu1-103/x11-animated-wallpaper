#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    Display *dpy = XOpenDisplay(NULL);

    Window win = (Window)strtoul(argv[1], NULL, 0);

    GLint att[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
    XVisualInfo *vi = glXChooseVisual(dpy, 0, att);

    GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    while (1) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glBegin(GL_LINES);
        // now i am free to do anything
        glEnd();
        glClear(GL_COLOR_BUFFER_BIT);
        glXSwapBuffers(dpy, win);
    }

    return 0;
}

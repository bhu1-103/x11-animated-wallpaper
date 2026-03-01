#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double now_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(int argc, char *argv[]) {
    Display *dpy = XOpenDisplay(NULL);
    Window win = (Window)strtoul(argv[1], NULL, 0);

    GLint att[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
    XVisualInfo *vi = glXChooseVisual(dpy, 0, att);

    GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    typedef void (*glXSwapIntervalEXTProc)(Display*, GLXDrawable, int);
    glXSwapIntervalEXTProc glXSwapIntervalEXT =
        (glXSwapIntervalEXTProc)glXGetProcAddress(
            (const GLubyte*)"glXSwapIntervalEXT");

    if (glXSwapIntervalEXT) {
        glXSwapIntervalEXT(dpy, win, 1);
    }

    const double target_dt = 1.0 / 60.0;
    double last_time = now_seconds();

    while (1) {
        while (XPending(dpy)) {
            XEvent e;
            XNextEvent(dpy, &e);
            if (e.type == DestroyNotify) {
                glXMakeCurrent(dpy, None, NULL);
                glXDestroyContext(dpy, glc);
                XCloseDisplay(dpy);
                return 0;
            }
        }

        double frame_start = now_seconds();
        double dt = frame_start - last_time;
        double val1;
        last_time = frame_start;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glLineWidth(5.0f);
        glBegin(GL_LINES);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        if (val1>=1440) {val1=0;}
        val1++;
        glVertex3f( -(val1/360.0f), -1.0f, 0.0f);
        glVertex3f( +(val1/360.0f),  1.0f, 0.0f);
        glEnd();

        glXSwapBuffers(dpy, win);

        double frame_end = now_seconds();
        double frame_time = frame_end - frame_start;

        if (frame_time < target_dt) {
            double sleep_time = target_dt - frame_time;
            struct timespec ts;
            ts.tv_sec = (time_t)sleep_time;
            ts.tv_nsec = (sleep_time - ts.tv_sec) * 1e9;
            nanosleep(&ts, NULL);
        }

        (void)dt;
    }
}

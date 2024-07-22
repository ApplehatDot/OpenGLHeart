// OpenGL-Heart - main.c

#include <GL/glut.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>


#define M_PI 3.141592

// Zakres x
#define X_MIN -2.5
#define X_MAX 2.5

// Pozycja Y rysunku
#define POSITION_Y 0.5

// Krok rysowania
#define STEP 0.01

char AboutDescription[] = "Projekt OpenGL-Heart dla systemow rodziny GNU/Linux dystrybuowana na Licencji MIT:\n\nCopyright 2024 ApplehatDoesStuff\nPermission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ,,Software''), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED,,AS IS'', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.";

// Wartość a, którą użytkownik może zmieniać
float a = 16.0f;
char aValueString[50];  // Bufor na string reprezentujący wartość a

// Aktualny kolor
int currentColor = 1; // Domyślnie biały

// Funkcja, którą będziemy rysować
float func(float x, float a) {
    return sqrtf(fabs(x)) + 0.9f * sqrtf(3.3f - x * x) * sinf(a * M_PI * x);
}

// GTK_MessageBox("tytuł", "opis");

int global_argc;
char **global_argv;

int GTK_MessageBox(const char *TITLE, const char *TEXT)
{
    GtkWidget *dialog;

    //zanim użyjesz funkcji zdefiniuj globalne argc i argv!
    gtk_init(&global_argc, &global_argv);
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s", TEXT);
    gtk_window_set_title(GTK_WINDOW(dialog), TITLE);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);

    char buffer[50];  // Bufor na tekst
    sprintf(buffer, "float a = %.2f;", a);  // Formatowanie wartości float do stringa z dwoma miejscami po przecinku
    strcpy(aValueString, buffer);

    // Ustawienie koloru na podstawie currentColor
    switch (currentColor) {
        case 1:
            glColor3f(1.0, 1.0, 1.0); // Biały
            break;
        case 2:
            glColor3f(1.0, 0.0, 0.0); // Czerwony
            break;
        case 3:
            glColor3f(0.5, 0.5, 1.0); // Jasno niebieski
            break;
        case 4:
            glColor3f(1.0, 0.5, 0.5); // Różowy
            break;
        default:
            break;
    }

    // Rysowanie dla x >= 0
    for (float x = 0; x <= X_MAX; x += STEP) {
        float y = func(x, a);
        glVertex2f(x, y - POSITION_Y);
    }

    // Rysowanie dla x < 0
    for (float x = 0; x >= X_MIN; x -= STEP) {
        float y = func(x, a);
        glVertex2f(x, y - POSITION_Y);
    }

    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0); // Biały kolor tekstu
    glRasterPos2i(10, 10);  // Pozycja tekstu (10, 10) w oknie

    // Wyświetlenie tekstu
    for (int i = 0; aValueString[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, aValueString[i]);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(X_MIN, X_MAX, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            a += 1.0f;
            break;
        case 'd':
            a -= 1.0f;
            break;
        case '1':
            currentColor = 1; // Biały
            break;
        case '2':
            currentColor = 2; // Czerwony
            break;
        case '3':
            currentColor = 3; // Jasno niebieski
            break;
        case '4':
            currentColor = 4; // Różowy
            break;
        case 27: // Escape key
            exit(0);
            break;
        case 'v':
            GTK_MessageBox("o projekcie", AboutDescription);
            break;
    }
    glutPostRedisplay();
}

void setWindowIcon(Display *display, Window window) {
    Pixmap icon_pixmap;
    Pixmap icon_mask;
    XpmAttributes attributes;
    XpmReadFileToPixmap(display, DefaultRootWindow(display), "heart.xpm", &icon_pixmap, &icon_mask, &attributes);

    XWMHints *wm_hints = XAllocWMHints();
    wm_hints->flags = IconPixmapHint | IconMaskHint;
    wm_hints->icon_pixmap = icon_pixmap;
    wm_hints->icon_mask = icon_mask;
    XSetWMHints(display, window, wm_hints);
    XFree(wm_hints);
    XFreePixmap(display, icon_pixmap);
    XFreePixmap(display, icon_mask);
}

int main(int argc, char** argv) {

    global_argc = argc;
    global_argv = argv;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rysowanie funkcji w OpenGL");

    // Inicjalizacja OpenGL
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

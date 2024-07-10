#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include "resource.h"

// Zakres x
#define X_MIN -2.5
#define X_MAX 2.5

// Pozycja Y rysunku
#define POSITION_Y 0.5

// Krok rysowania
#define STEP 0.01

// Wartość a, którą użytkownik może zmieniać
float a = 16.0f;
char aValueString[50];  // Bufor na string reprezentujący wartość a

// Aktualny kolor
int currentColor = 1; // Domyślnie biały

// Funkcja, którą będziemy rysować
float func(float x, float a) {
    return sqrtf(fabs(x)) + 0.9f * sqrtf(3.3f - x * x) * sinf(a * M_PI * x);
    //funkcja: √x + 0.9√(3.3 - x*x)*sin(a*π*x)
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
    }
    glutPostRedisplay();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    glutInit(&__argc, __argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rysowanie funkcji w OpenGL");

    // Ustawienie ikony
    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    SendMessage(GetActiveWindow(), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    SendMessage(GetActiveWindow(), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

    // Inicjalizacja OpenGL
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

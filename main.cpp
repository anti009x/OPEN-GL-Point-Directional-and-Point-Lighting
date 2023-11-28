#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <cstdlib>

GLfloat camX = 3.3;  // Inisialisasi posisi awal kamera
GLfloat camY = 3.3;
GLfloat camZ = 3.3;

int startX, startY;  // Untuk melacak posisi awal mouse
GLfloat cubeColor[] = {0.7f, 0.7f, 0.7f, 1.0f};

void cube() {
    glPushMatrix();
    glTranslated(0.5, 0.5, 0.5);
    glScaled(1.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cubeColor);  // Menggunakan warna kubus
    glutSolidCube(1.0);
    glPopMatrix();
}

void setMaterial() {
    GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void setLighting() {
    GLfloat lightIntensity[] = {1.0f, 4.0f, 4.0f, 4.0f};
    GLfloat lightPosition[] = {2.0f, 6.0f, 3.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void setViewport() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double winHt = 1.0;
    glOrtho(-winHt * 64 / 48, winHt * 64 / 48, -winHt, winHt, 0.1, 100.0);
}

void setCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0, 0.25, 0, 0.0, 1.0, 0.0);
}

void displayObject() {
    setMaterial();
    setLighting();
    setViewport();
    setCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Tambahkan pemanggilan fungsi cube() di sini
    cube();

    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        startX = x;
        startY = y;

        // Ganti warna kubus setiap kali di-klik mouse
        cubeColor[0] = static_cast<GLfloat>(rand()) / RAND_MAX;
        cubeColor[1] = static_cast<GLfloat>(rand()) / RAND_MAX;
        cubeColor[2] = static_cast<GLfloat>(rand()) / RAND_MAX;

    }
}
void mouseMove(int x, int y) {
    int deltaX = x - startX;
    int deltaY = y - startY;

    camX += static_cast<GLfloat>(deltaX) / 100.0;
    camY -= static_cast<GLfloat>(deltaY) / 100.0;

    startX = x;
    startY = y;

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Mengganti mode ke GLUT_DOUBLE
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pencahayaan");

    glutDisplayFunc(displayObject);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);  // Menambahkan fungsi mouseMove

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glViewport(0, 0, 640, 480);
    glutMainLoop();
}

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <algorithm> // cho std::min, std::max

// Vị trí và góc xoay của robot
float robotX = 0.0f;
float robotZ = -5.0f;
float robotRotation = 0.0f;
float leftArmAngle = 0.0f;
float rightArmAngle = 0.0f;

void init() {
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void drawCube(float size) {
    float s = size / 2.0f;

    glBegin(GL_QUADS);
    // 6 mặt của cube
    glVertex3f(-s, -s, s); glVertex3f(s, -s, s); glVertex3f(s, s, s); glVertex3f(-s, s, s);  // Front
    glVertex3f(-s, -s, -s); glVertex3f(-s, s, -s); glVertex3f(s, s, -s); glVertex3f(s, -s, -s);  // Back
    glVertex3f(-s, s, -s); glVertex3f(-s, s, s); glVertex3f(s, s, s); glVertex3f(s, s, -s);  // Top
    glVertex3f(-s, -s, -s); glVertex3f(s, -s, -s); glVertex3f(s, -s, s); glVertex3f(-s, -s, s);  // Bottom
    glVertex3f(s, -s, -s); glVertex3f(s, s, -s); glVertex3f(s, s, s); glVertex3f(s, -s, s);  // Right
    glVertex3f(-s, -s, -s); glVertex3f(-s, -s, s); glVertex3f(-s, s, s); glVertex3f(-s, s, -s);  // Left
    glEnd();
}

void drawRobot() {
    glPushMatrix();
    glTranslatef(robotX, 0.0f, robotZ);
    glRotatef(robotRotation, 0.0f, 1.0f, 0.0f);

    // Thân
    glColor3f(0.0f, 0.8f, 0.8f);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(0.8f, 1.0f, 0.4f);
    drawCube(1.0f);
    glPopMatrix();

    // Đầu
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 0.0f);
    glScalef(0.6f, 0.6f, 0.6f);
    drawCube(1.0f);
    glPopMatrix();

    // Tay trái
    glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix();
    glTranslatef(-0.5f, 0.4f, 0.0f);
    glRotatef(leftArmAngle, 1.0f, 0.0f, 0.0f);
    glScalef(0.15f, 0.6f, 0.15f);
    drawCube(1.0f);
    glPopMatrix();

    // Tay phải
    glPushMatrix();
    glTranslatef(0.5f, 0.4f, 0.0f);
    glRotatef(rightArmAngle, 1.0f, 0.0f, 0.0f);
    glScalef(0.15f, 0.6f, 0.15f);
    drawCube(1.0f);
    glPopMatrix();

    // Chân trái
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(-0.2f, -0.5f, 0.0f);
    glScalef(0.2f, 1.0f, 0.2f);
    drawCube(1.0f);
    glPopMatrix();

    // Chân phải
    glPushMatrix();
    glTranslatef(0.2f, -0.5f, 0.0f);
    glScalef(0.2f, 1.0f, 0.2f);
    drawCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void drawGround() {
    glColor3f(0.3f, 0.6f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -1.0f, -10.0f);
    glVertex3f(-10.0f, -1.0f, 10.0f);
    glVertex3f(10.0f, -1.0f, 10.0f);
    glVertex3f(10.0f, -1.0f, -10.0f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 2.0f, 5.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    drawGround();
    drawRobot();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            exit(0);
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    float moveSpeed = 0.2f;
    float newX = robotX;
    float newZ = robotZ;

    switch (key) {
        case GLUT_KEY_UP:
            newX += moveSpeed * sin(robotRotation * M_PI / 180.0f);
            newZ -= moveSpeed * cos(robotRotation * M_PI / 180.0f);
            // Vung tay khi di chuyển
            leftArmAngle += 10.0f;
            rightArmAngle -= 10.0f;
            // Reset về 0 khi đạt 45 độ
            if (leftArmAngle >= 45.0f) leftArmAngle = 0.0f;
            if (rightArmAngle <= -45.0f) rightArmAngle = 0.0f;
            break;

        case GLUT_KEY_DOWN:
            newX -= moveSpeed * sin(robotRotation * M_PI / 180.0f);
            newZ += moveSpeed * cos(robotRotation * M_PI / 180.0f);
            // Vung tay khi di chuyển
            leftArmAngle += 10.0f;
            rightArmAngle -= 10.0f;
            // Reset về 0 khi đạt 45 độ
            if (leftArmAngle >= 45.0f) leftArmAngle = 0.0f;
            if (rightArmAngle <= -45.0f) rightArmAngle = 0.0f;
            break;

        case GLUT_KEY_LEFT:
            robotRotation -= 5.0f;
            break;

        case GLUT_KEY_RIGHT:
            robotRotation += 5.0f;
            break;
    }

    // Kiểm tra giới hạn di chuyển
    robotX = newX;
    robotZ = newZ;

    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Robot 3D");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}

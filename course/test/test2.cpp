#ifdef APPLE_CC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

void display()
{

    glClearColor(0.7f, 1.0f, 0.7f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // РИСОВАНИЕ ТОЧЕК
    // glPointSize(25); // задаем размера точки
    // glBegin(GL_POINTS);
    // glColor3f(0.7, 0.1, 1); // отображение каждой вершины как точки
    // glVertex2f(0.09, 0.0);  // передача вершин для отображения
    // glColor3f(1.0, 0, 0);
    // glVertex2f(-0.09, 0.0);
    // glEnd();

    // РИСОВАНИЕ ЛИНИЙ
    // glLineWidth(5);
    // glBegin(GL_LINES);
    // glColor3f(1, 1, 1);
    // glVertex2f(0.0, 0.8);
    // glVertex2f(0.0, 0.0);
    // glEnd();

    // РИСОВАНИЕ СОЕДИНЕНИЙ ЛИНИЙ, ПОСЛЕДНЯЯ И ПЕРВАЯ ТОЧКА НЕ СОЕД
    // glLineWidth(8);
    // glBegin(GL_LINE_STRIP);
    // glColor3f(0.5, 0.5, 0.5);
    // glVertex2f(-0.5, -0.5);
    // glVertex2f(-0.2, -0.2);
    // glVertex2f(-0.7, -0.4);
    // glEnd();

    // glEnable(GL_LINE_STIPPLE); // активация разоичных режимов
    // glLineStipple(1, 0x00ff);  // активация режима точечной отрисовки, 0x00ff - шаблон отрисовки, 0x - означает, чточисло записано в 16тиричном виде, 00ff само число

    // РИСОВАНИЕ СОЕДИНЕНИЙ ЛИНИЙ, ПОСЛЕДНЯЯ И ПЕРВАЯ ТОЧКА СОЕД
    // glLineWidth(6);
    // glBegin(GL_LINE_LOOP);
    // glColor3f(0.3, 0.4, 0.5);
    // glVertex2f(0.9, 0.9);
    // glVertex2f(-0.9, 0.9);
    // glVertex2f(-0.9, -0.9);
    // glVertex2f(0.9, -0.9);
    // glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.8, 0.8);
    glVertex2f(-0.8, 0.8);
    glVertex2f(-0.8, -0.8);
    glEnd();

    // glBegin(GL_TRIANGLE_FAN); //рисование триугольников. у треугольников общие сторона или стороны. для построения нового треугольника добавляем 1 точку.
    // glColor3f(0.0, 0.0, 0.0);
    // glVertex2f(0.8, 0.8);
    // glColor3f(0.0, 1.0, 0.0);
    // glVertex2f(-0.8, 0.8);
    // glColor3f(0.0, 0.0, 1.0);
    // glVertex2f(-0.8, -0.8);
    // glColor3f(0.0, 1.0, 0.0);
    // glVertex2f(0.8, -0.8);
    // glEnd();

    // glBegin(GL_TRIANGLE_STRIP); // каждый новый (после первого) треугольник строиться между новой точкой и последней вершиной последнего треугольника
    // glColor3f(0.0, 0.0, 0.0);
    // glVertex2f(0.8, 0.8);
    // glVertex2f(-0.8, 0.8);
    // glVertex2f(-0.8, -0.8);
    // glColor3f(0.0, 1.0, 0.0);
    // glVertex2f(0.8, -0.8);
    // glEnd();

    float x, y;
    float cnt = 40;
    float l = 0.5;
    float a = M_PI * 2 / cnt;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 0, 1);
    glVertex2f(0, 0);
    for (int i = -1; i < cnt; i++)
    {
        x = sin(a * i) * l;
        y = cos(a * i) * l;
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A Simple Triangle");

    glutDisplayFunc(display);

    glutMainLoop();
}
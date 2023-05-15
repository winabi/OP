#ifdef APPLE_CC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void ShowObjects()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

void display()
{

    glClearColor(0.7f, 1.0f, 0.7f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glPushMatrix();
    // glRotatef(1.0f, 0.0f, 0.0f, 1.0f);

    // glLoadIdentity(); // загружение единичной матрицы. возвращает систему координат в начальное положение

    // glTranslatef(0.5, 0, 0); // меняет матрицу преобразований. смещение системы координат на заданое значение по 3м осям
    // glRotatef(45, 0, 0, 1);  // изменяет матрицу преобразований таким образом,чтобы повернуть систему координат

    // // порядок glRotatef и glTranslatef важен.

    // // масштабирование
    // glScalef(0.3, 0.3, 1); // изменение масштаба по осям. в примере мы не исзменяем масштаб у оси "z"

    // изменяем порядок вызова функций

    glLoadIdentity();
    glScalef(0.3, 0.3, 1);
    // glRotatef(45, 0, 0, 1);
    glTranslatef(1, 1, 0);
    for (int i = 0; i < 7; i++)
    {
        // glLoadIdentity(); // Вызываем единичную матрицу. А значит ранее селанные преобразования не будут учитываться
        glPushMatrix(); // Сохраняем текущую матрицу в стек. А значит теперь будем рисовать треугольники, опираясь на масштаб, заданный ранее
        glRotatef(45 * i, 0, 0, 1);
        glTranslatef(0.5, 0, 0);
        ShowObjects();
        glPopMatrix(); // извлекает матрицу из стека и устанавливает ее в качестве текущей
    }

    // glPopMatrix();

    glFlush();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("video 3");

    glutDisplayFunc(display);

    glutMainLoop();
}
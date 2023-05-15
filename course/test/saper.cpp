#ifdef APPLE_CC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <cstring>
#include <ctime>

#define mapW 10
#define mapH 10

struct TCell
{
    bool mine;
    bool flag;
    bool open;
    int cntAround;
};

TCell map[mapW][mapH];
int mines;
int closedCell;

bool IsCellInMap(int x, int y) // функция для того, принадлежит ли наше ячейка нашему полю
{
    return (x >= 0) && (y >= 0) && (x <= mapW) && (y < mapH);
}

#include <X11/Xlib.h>
void ScreenToOpenGL(Display *display, Window window, int x, int y, float *ox, float *oy)
{
    if (!display || !window)
    {
        return;
    }

    XWindowAttributes win_attrs;
    XGetWindowAttributes(display, window, &win_attrs);

    *ox = (float)x / win_attrs.width;
    *oy = (float)y / win_attrs.height;
}

void Game_New()
{
    srand(time(NULL));
    memset(map, 0, sizeof(map));

    mines = 20;
    closedCell = mapW * mapH;
    for (int i = 0; i < mines; i++) // функция для того, сколько нам нужно поставить мин
    {
        int x = rand() % mapW; // выбор случайной координаты
        int y = rand() % mapH;

        if (map[x][y].mine)
        {
            i--; // если мина уже присутствует, ищутся новые координаты
        }
        else
        {
            map[x][y].mine = true;

            // При установлении мины, устанавливается значение мин для всех соседних полей
            for (int dx = -1; dx < 2; dx++)
            {
                for (int dy = -1; dy < 2; dy++)
                {
                    if (IsCellInMap(x + dx, y + dy))
                    {
                        map[x + dx][y + dy].cntAround += 1;
                    }
                }
            }
        }
    }
}

void Line(float x1, float y1, float x2, float y2)
{
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
}

void ShowCount(int a) // функция для показывания циферок
{
    glLineWidth(3);
    glColor3f(1, 1, 0);
    glBegin(GL_LINES); // ниже код работает по принципу семисигментного индикатора. т.е если для определенной цифры требуется сигмент, он рисуется.
    if ((a != 1) && (a != 4))
    {
        Line(0.3, 0.85, 0.7, 0.85);
    }
    if ((a != 0) && (a != 1) && (a != 7))
    {
        Line(0.3, 0.5, 0.7, 0.5);
    }
    if ((a != 1) && (a != 4) && (a != 7))
    {
        Line(0.3, 0.15, 0.7, 0.15);
    }

    if ((a != 5) && (a != 6))
    {
        Line(0.7, 0.5, 0.7, 0.85);
    }
    if (a != 2)
    {
        Line(0.7, 0.5, 0.7, 0.15);
    }

    if ((a != 1) && (a != 2) && (a != 3) && (a != 7))
    {
        Line(0.3, 0.5, 0.3, 0.85);
    }
    if ((a == 0) || (a == 2) || (a == 6) || (a == 8))
    {
        Line(0.3, 0.5, 0.3, 0.15);
    }
    glEnd();
}

void ShowMine()
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
    glVertex2f(0.3, 0.3);
    glVertex2f(0.7, 0.3);
    glVertex2f(0.7, 0.7);
    glVertex2f(0.3, 0.7);
    glEnd();
}

void ShowField() // показывает поле
{
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(0, 1);
    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(1, 1);
    glVertex2f(0, 0);
    glColor3f(0.6, 0.6, 0.6);
    glVertex2f(1, 0);
    glEnd();
}

void ShowFieldOpen() // показывает ОТКРЫТОЕ поле
{
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.3, 0.7, 0.3);
    glVertex2f(0, 1);
    glColor3f(0.3, 0.6, 0.3);
    glVertex2f(1, 1);
    glVertex2f(0, 0);
    glColor3f(0.3, 0.5, 0.3);
    glVertex2f(1, 0);
    glEnd();
}

void ShowFlag()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(0.25, 0.75);
    glVertex2f(0.85, 0.5);
    glVertex2f(0.25, 0.25);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0.25, 0.75);
    glVertex2f(0.25, 0);
    glEnd();
}

// функция для автоматического открывания пустых клеток
void OpenFields(int x, int y)
{
    if (!IsCellInMap(x, y) || map[x][y].open) // если указанное поле находится за границами карты или уже открыто
    {
        return; // выходим из процедуры
    }

    map[x][y].open = true; // открытие указанного поля

    if (map[x][y].cntAround == 0) // если нет цифры 1 и выше
    {
        for (int dx = -1; dx < 2; dx++) // открытие соседних полей
        {
            for (int dy = -1; dy < 2; dy++)
            {
                OpenFields(x + dx, y + dy);
            }
        }
    }
}

void Game_Show()
{
    glLoadIdentity();
    glScaled(2.0 / mapW, 2.0 / mapH, 1);       // изменение масштаба, дабы каждое поле рисовалось как 1 клетка карты
    glTranslatef(-mapW * 0.5, -mapH * 0.5, 0); // СМЕЩАЕМ НАЧАЛО КООРДИНАТ В ЛЕВЫЙ Нижний угол

    for (int j = 0; j < mapH; j++)
    {
        for (int i = 0; i < mapW; i++)
        {
            glPushMatrix();
            glTranslatef(i, j, 0);

            if (map[i][j].open)
            {
                ShowFieldOpen();
                if (map[j][i].mine)
                {
                    ShowMine();
                }
                else if (map[i][j].cntAround > 0)
                {
                    ShowCount(map[i][j].cntAround);
                }
            }
            else
            {
                ShowField();
                if (map[i][j].flag)
                {
                    ShowFlag();
                }
            }

            glPopMatrix();
        }
    }
}

void on_mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int i = x / (400 / mapW);
        int j = mapH - y / (300 / mapH) - 1;
        if (IsCellInMap(i, j) && !map[i][j].open && !map[i][j].flag) // если стоит флажек, то открыть нельзя ячейку
        {
            OpenFields(i, j);
            closedCell--;
            glutPostRedisplay();
        }
    }

    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        int i = x / (400 / mapW);
        int j = mapH - y / (300 / mapH) - 1;
        if (IsCellInMap(i, j))
        {
            map[i][j].flag = !map[i][j].flag;
            glutPostRedisplay();
        }
    }
}

void display()
{

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Game_Show();
    glFlush();
}

int main(int argc, char **argv)
{
    Game_New();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);     // установка размеров окна
    glutInitWindowPosition(100, 100); // установка положения окна
    glutCreateWindow("Saper");

    glutDisplayFunc(display);
    glutMouseFunc(on_mouse);

    glutMainLoop();
}

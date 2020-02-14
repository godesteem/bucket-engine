/**
 * File              : main.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 14.02.2020
 * Last Modified Date: 14.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include <iostream>
#include <GL/glut.h>


GLfloat angle = 0.0;

struct Position {
  GLint x;
  GLint y;
};

Position cur_pos = {0, 0};
const int MOVE_SPEED = 100;

void spin(void){
  angle += .1;
  glutPostRedisplay();
}


// Input
void keyboard(unsigned char key, int x, int y){
  if (key == 27){
    exit(0);
  }
  else if (key == 119){ // W
    cur_pos.x += MOVE_SPEED;
  }
  else if (key == 97){ // A
    cur_pos.y -= MOVE_SPEED;
  }
  else if (key == 115){ // S
    cur_pos.x -= MOVE_SPEED;
  }
  else if (key == 100){ // D
    cur_pos.y += MOVE_SPEED;
  }

  else {
    std::cout << "key: " << key << " pressed.\n";
  }
}
void special_keyboard(int key, int x, int y){
  std::cout << "special key: " << key << " pressed.\n";
}


// Output
void display(void){
  // glClearColor(1.0, 1.0, 1.0, 0.0);
  
  // clear screen
  glClear(GL_COLOR_BUFFER_BIT);
  
  // prepare update  
  glLoadIdentity();

  // set viewport
  glViewport(cur_pos.y, cur_pos.x, (GLsizei) 500, (GLsizei) 500);
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

  // render graphics
  glRotatef(angle, 1, 0, 0);
  glRotatef(angle, 0, 1, 0);
  glRotatef(angle, 0, 0, 1);

  //glBegin(GL_LINE_LOOP);
  //glVertex3f(-0.3, -0.3,  0.0);
  //glVertex3f( 0.0,  0.3,  0.0);
  //glVertex3f( 0.3, -0.3,  0.0);
  //glEnd();
  glutSolidCube(0.1);
  glutWireCube(1.0);
  glutWireCube(2.0);
  // flush to display
  glutSwapBuffers();
  // glFlush();
}

void reshape(int width, int height){
  glViewport(cur_pos.y, cur_pos.x, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-1,1,-1,1,-1,1);
  gluPerspective(60, (GLfloat) width/(GLfloat) height, 1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glEnable(GL_LIGHTING | GL_FOG);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Test");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special_keyboard);
  glutReshapeFunc(reshape);
  glutIdleFunc(spin);
  glutMainLoop();

  return 0;
}

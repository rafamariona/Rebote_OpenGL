//Pelota rebotando por MT14002
#include <GL/gl.h>
#include <GL/glut.h>

//Declaramos las variables a usar
float escala=0.2;
float angX=0.0f,angY=0.0f;
int ResX=800,ResY=600;
enum{EJE=2};
float aceX=0.0f,aceY=-0.001f;
float velX=0.01f,velY=0.0f;
float posX=0.0f,posY=10.0f;
//Definición del modelo de una luz
GLfloat light_Ambient [4] = { 0.2, 0.2, 0.2, 1.0};
GLfloat light_Diffuse [4] = { 1.0, 1.0, 1.0, 1.0};
GLfloat light_Position [4] = {20.0, 15.0, 10.0, 1.0};
//Definición de las caracteristicas opticas del material: coeficientes de reflexión
GLfloat material [4] = {1.0f, 0.2f, 0.2f, 1.0f };
GLfloat RedMaterial [4] = {1.0, 0.0, 0.0, 1.0 };
GLfloat GreenMaterial [4] = {0.0, 1.0, 0.0, 1.0 };
GLfloat BlueMaterial [4] = {0.0, 0.0, 1.0, 1.0 };
GLfloat WhiteMaterial [4] = {1.0, 1.0, 1.0, 1.0 };
GLfloat BlackMaterial [4] = {0.0, 0.0, 0.0, 1.0 };
GLfloat GrayMaterial [4] = {0.6, 0.6, 0.6, 1.0 };

//--------------manejo de las luces------------
void luces(void){
      glEnable (GL_LIGHTING);
      glEnable (GL_LIGHT0);
      glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ambient );
      glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Diffuse );
      glLightfv(GL_LIGHT0, GL_POSITION, light_Position );
}
//-----------dibuja la pelota------------
void pelota(){
    glNewList(EJE,GL_COMPILE);
    glPushMatrix();
    glutSolidSphere(2.0f,50,50);   //la pelota
    glPopMatrix();
    glEndList();
}
//------------dibuja la escena------------
void RenderScene(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    //AJUSTANDO LA CÁMARA
    glLoadIdentity( );
    glTranslatef(-0.9f,0.0f,-5.0f);
    glRotatef(angY,1.0f,0.0f,0.0f); //rotacion en x
    glRotatef(angX,0.0f,1.0f,0.0f); //rotacion en y
    //EJES DE REFERENCIA
    glLineWidth(5);
    glCallList(1);
    glPushMatrix();
    glScalef(escala,escala,escala);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BlueMaterial ); //el material
    glPushMatrix();
    glTranslatef(posX,posY,0.0f); //el movimiento de traslacion
    glCallList(EJE);
    glPopMatrix();
    glutSwapBuffers();
}
void teclado(unsigned char key, int x, int y){ //para manejar con teclado
      if (key =='+'){escala+=0.1f;} //aumenta el tamaño
      if (key =='-'){escala-=0.1f;} //disminuye el tamaño
      if (key ==27){exit(0);}       //salir con esc

}
//ACÁ PASA LA MAGIA
//----------controla la animacion-------------
void animacion(void){
    velY+=aceY; posY+=velY;
    velX+=aceX; posX+=velX;
    if(posY<0.0f){posY=0.0f; velY*=-0.8f;
    if(velY<0.01f){velX=0.0f; velY=0.0f;}
                }
    glutPostRedisplay();
  }

//-------funcion principal----------
int main(int a, char *b[]){
    glutInit(&a,b);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(ResX,ResY);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Pelota rebotando");
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(teclado);
    glutIdleFunc(animacion); //Se repite el llamado para crear movimiento
    //OPENGL
    glViewport( 0, 0, ResX, ResY );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-(float)ResX/ResY, (float)ResX/ResY, -1.0, 1.0, 2, 10000.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    luces();
    pelota();
    glutMainLoop();
    return 0;
}

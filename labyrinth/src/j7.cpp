// Search For 
// HERE FIXME

/* TODO 
// pause / restart
// clear predicate and message
// menu
// mouse
// fix rotation
// fix restitution
// reshape
// quit does not work if ball has gone into the hole
// Makefile cleanup
// auto lib build
// should specify objects (ball and board when it runs on the command line)
// configure
// toggle pause and resume in menu
// start and finish
*/
/* BUG 
//
// Was using convexhull for board but the wall and the floor of the board makes
// it closed cube, but the inside of it must be empty, and should not make collisions in there.
// [せっかくだから俺はプログラマの道を選ぶぜ@wiki - Bullet その３　応用形状編](http://www11.atwiki.jp/darui_program/pages/328.html)
// [btCollisionShape from CC3MeshNode? « cocos2d for iPhone](http://www.cocos2d-iphone.org/forum/topic/19508)
// cause: was using convex hull for board with wall and floor
// 
*/
/* Task
// color or texture 
// 
// added body
// apply force and fall ball in idle()
// make board as a kinematic body and support the ball (ball should not fall)
  //sub make board first rotate and let it fall with the ball
  // NOT DONE
// make board rotate
// set friction bouncing coeff and so forth
// make board rotate
  // angular velocity
  // quaranteen
*/
/* References
Bullet User Manual : constructor from triangle mesh : 32
[Box2D：４．b2Bodyで力・トルクを加える](http://flashjp.com/api/box2d_b2Body1.php)
[BtContactSolverInfo - Physics Simulation Wiki](http://bulletphysics.org/mediawiki-1.5.8/index.php/BtContactSolverInfo)
[Bullet Collision Detection & Physics Library: btBvhTriangleMeshShape Class Reference](http://bulletphysics.com/Bullet/BulletFull/classbtBvhTriangleMeshShape.html)
[Bullet Collision Detection & Physics Library: btConvexTriangleMeshShape Class Reference](http://bulletphysics.com/Bullet/BulletFull/classbtConvexTriangleMeshShape.html#_details)
[Bullet Collision Detection & Physics Library: btRigidBody Class Reference](http://bulletphysics.com/Bullet/BulletFull/classbtRigidBody.html#ac6e5f94e998150e37ca8962c851d10a8)
[Bullet Collision Detection & Physics Library: btTransform Class Reference](http://www.bulletphysics.com/Bullet/BulletFull/classbtTransform.html)
[Bullet Collision Detection & Physics Library: btTriangleMesh Class Reference](http://bulletphysics.com/Bullet/BulletFull/classbtTriangleMesh.html)
[Bullet Survival Kit – 4: Kinematics - OOgtech.org](http://www.oogtech.org/content/2011/09/07/bullet-survival-kit-4-the-motion-state/)
[Collision Callbacks and Triggers - Physics Simulation Wiki](http://bulletphysics.org/mediawiki-1.5.8/index.php/Collision_Callbacks_and_Triggers)
[せっかくだから俺はプログラマの道を選ぶぜ@wiki - Bullet その３　応用形状編](http://www11.atwiki.jp/darui_program/pages/328.html)
[Collision Shapes - Physics Simulation Wiki](http://www.bulletphysics.org/mediawiki-1.5.8/index.php/Collision_Shapes)
*/
/* To Consider/Do
// 
// Search for future extension by "FE :"
// 
// Make importer reference within OglObj ?
// Triangle should specify position_indices instead of posisions
// Program class which have shader handle and also drawing method
// Not sure centerOfMassOfTriangles() is correct
*/
/* Issues
// Vertex not yet to component of vbo
// Vertex should be another type that should be composed in vboComponent
// problem related to coordinate managements like center of mass of objects
// cannot use glm properly ; 
//
// Board is not static nor kinematic
// current implementation does not rotate board if the board is static (mass = 0)
//
// global matrices 
// 
// Using glDrawArrays instead of using IBO index buffer object
//
// Obj class assumes shader program is already uploaded and works
// 
// Colorizing things directly in fragment shader instead of using lighting and material.
// 
// Rotation problem
//
// Kinematic Object instead of dynamic 
//
// rotating board outside of physics simulation
*/ 
/* Past Problems
//
// Was using glUsePrograms for each vbo then nothing is drawn if two or more vbo's exist.
// 
// 
  Obj::data should not be a member but a temporary variable inside of the Obj private function
*/ 

#include <fstream>
#include <iostream>
#include <chrono>
#include <cmath>
#include <sstream>

// Bullet
// #include "bullet/src/btBulletDynamicsCommon.h"
#include "../bullet/src/btBulletDynamicsCommon.h"
#include "../bullet/src/BulletCollision/CollisionShapes/btTriangleShape.h"

#include <GL/glew.h> // glew must be included before the main gl libs
#include <GL/glut.h> // doing otherwise causes compiler shouting

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

// Assimp
#include "Importer.hpp"	
#include "postprocess.h"
#include "scene.h"
#include "DefaultLogger.hpp"
#include "LogStream.hpp"

#include "InitShader.cpp"

// function prototypes 
glm::mat4 getOglTransformMatrix(btRigidBody* body);

// global handels
float boardMass=1000;
float rotationAngle=0.1;



std::vector<btRigidBody*> board_rigid_bodies;
btRigidBody* ballbody;

// std::string ball_fname = "obj/ball.obj";
// std::string board_fname = "obj/board.obj";

GLuint h_program; // GLSL h_program handle
GLint h_mvp  = -1;    
GLint h_vpos = -1;
GLint h_vcolor = -1;

glm::mat4 ball_model_matrix;
glm::mat4 board_model_matrix;

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 mvp; // projection * view * model 

// other globals
// int w = 640, h = 480; // Window size
GLfloat rangle = 10;      // angle to rotate
int w = 500, h = 500;     // Window size
struct Obj;
Obj* pball=NULL;
Obj* pboard=NULL;
glm::vec3 max_coords = glm::vec3(10,10,10);
std::chrono::time_point<std::chrono::high_resolution_clock> t1,t2;

float n = 30;
// glm::vec3 look_eyepos = glm::vec3(n, 30.0, n);    // Eye Position
glm::vec3 look_eyepos = glm::vec3(0, 20.0, 0);    // Eye Position
float world_gravity= -5;
float ball_mass = 1;
float board_mass = 100;
float ball_initial_height = 5; // 0 5

// struct MyVBO;
// std::vector<MyVBO> vbos;

struct Obj;
std::vector<Obj> objs;

struct RotateHelp;

// Bullet Globals
btDiscreteDynamicsWorld* dynamicsWorld;
btRigidBody* bulletBallBody;
btRigidBody* bulletBoardBody;


float ballRadius = -1;
GLint h_projection, h_view, h_model;


// NewBelow

bool is_game_complete(btRigidBody* body) 
{
  if (body) {
    glm::mat4 m = getOglTransformMatrix(body) ;
    // std::cout << m[3][1] << std::endl;
    // std::cout << "true condition" << ( m[3][1] < -20) << std::endl;

    // this -20 should be parametrized in terms of the length of the board
    if ( m[3][1] < -1000) 
      return true ;
    else 
      return false ;
  }
  return false;
}

// game settings
bool game_done = false;
bool game_pause = false;
float grestitution = 0.9;
float gfriction = 0.3;

float rotationFactor = 0.1;
float addrotation = 0.1/180.0*M_PI;
float rotationHorizontal = 0, rotationVertical = 0;
float rotation = 0; 

struct RotateHelp {

  static int max_num_to_rotate;
  static float incremental_rotation;
  int num_to_rotate;
  int num_rotated;

  RotateHelp(int nrot) 
    : num_rotated(0)
    {
      num_to_rotate = (nrot%2==1) ? nrot+1 : nrot ; // make it even
    }

  RotateHelp& operator+=(const RotateHelp& o)
  {
    num_to_rotate += o.num_to_rotate;
    num_rotated += o.num_rotated;
    return *this;
  }

  float rotate_angle(int increments)
  {
    // Should not rotate more than specified in num_to_rotate
    int remaining = num_to_rotate - num_rotated;
    if (increments >  remaining) {
      increments = remaining;
    }
    // 
    int half = num_to_rotate/2;
    int angle = 0;
    for (int i = 0; i < increments; i++) {
      angle += (  ( num_rotated % (half) ) == num_rotated  )
        ? (num_rotated+1)*incremental_rotation
        : (  half - (num_rotated%half)  )*incremental_rotation;
        ;
    }
    std::cout << "angle: "<< angle<< std::endl; 
    return angle;
  }

};
int RotateHelp::max_num_to_rotate = 100;
float RotateHelp::incremental_rotation = 0.24 ;

void rotateBody( btRigidBody* rb, const btScalar& yaw, const btScalar& roll, const btScalar& pitch)
// yaw roll pitch in radian
{

  // current transform
  btTransform trans = rb->getCenterOfMassTransform();
  
  // rotation transform
  btTransform rotation;
  rotation.setIdentity();
  btQuaternion quat;
  quat.setEuler( yaw, roll, pitch); //or quat.setEulerZYX depending on the ordering you want
  rotation.setRotation(quat);

  // trans*=rotation;
  rotation *= trans;

  bulletBoardBody->setCenterOfMassTransform(rotation);

}

float getDT()
{
    float ret;
    t2 = std::chrono::high_resolution_clock::now();
    ret = std::chrono::duration_cast< std::chrono::duration<float> >(t2-t1).count();
    t1 = std::chrono::high_resolution_clock::now();
    return ret;
}

btVector3 aiVector3TobtVector3(const aiVector3t<float>& av)
{
  return btVector3( av.x, av.y, av.z );
}

glm::mat4 oglMatrixToGLMMatrix4x4(btScalar* m)
{
	return glm::mat4(
    m[0]  , m[1]  , m[2]  , m[3]  , 
    m[4]  , m[5]  , m[6]  , m[7]  , 
    m[8]  , m[9]  , m[10] , m[11] , 
    m[12] , m[13] , m[14] , m[15]
  ); 
}

glm::mat4 getOglTransformMatrix(btRigidBody* body)
{

  btScalar m[16]; // transform matrix
  if ( body && body->getMotionState() ) {
    btTransform trans; 
    btDefaultMotionState* motion = (btDefaultMotionState*)body->getMotionState();
    motion->m_graphicsWorldTrans.getOpenGLMatrix( m );
  }
  else {
    std::cerr << "getOglTransformMatrix() error" << std::endl; 
    exit(1);
  }
  return oglMatrixToGLMMatrix4x4(m);
}

btVector3 glmvec3_to_btVector3(const glm::vec3& v)
{
  return btVector3( v.x, v.y, v.z );
}

float distance(glm::vec3 u, glm::vec3 v)
{
  return sqrt(
    ( u.x - v.x )*( u.x - v.x )+
    ( u.y - v.y )*( u.y - v.y )+
    ( u.z - v.z )*( u.z - v.z )
  );
}

glm::vec3 centerOfMassOfSimpleClosedPolygon(const std::string& fname)
{ 
  using namespace std;

  std::ifstream t(fname.c_str());
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

  istringstream iss(str);
  string s; 
  float x,y,z;
  float a,b,c;
  int count = 0;
  x=y=z=0;
   
  while ( !iss.eof() ) {
    iss >> s;
    if (s=="v") {
      iss >> a >> b >> c;
      x += a;
      y += b;
      z += c;
      count++;
      
     // cout << "("<< a << ","<< b << ","<< c << ")"<< endl;
    }
  }

  x/=count;
  y/=count;
  z/=count;

  return glm::vec3(x,y,z);

  /*
  ifstream is;
  is.open (fname.c_str() );

  // get length of file:
  is.seekg (0, std::ios::end);
  long length = is.tellg();
  is.seekg (0, std::ios::beg);

  // allocate memory:
  char *buffer = new char [length];

  // read data as a block:
  is.read (buffer,length);

  // create string stream of memory contents
  // NOTE: this ends up copying the buffer!!!
  istringstream iss( string( buffer ) );

  // delete temporary buffer
  delete [] buffer;

  // close filestream
  is.close();

  // ==================================
  //  Use iss to access data
  string s;
  iss >> s;
  cout << s << endl;
  */

  /*
  std::ifstream file( fname.c_str() );
  if ( file ) {
    // associate buffer to the file
    std::istringstream buf;
    
    file.close();
    // 
    while ( 1 ) {
      std::string s;
      float  f;
      buf >> s;
      buf >> f;
      std::cout << s << " " << f << std::endl;
    }
  }
  else {
    std::cerr << fname << " could not be opened" << std::endl;
  }
  */

}

// Printing

void debug_print_bullet_body_transform_matrix(btRigidBody* body)
{

  // Get Transform Matrix 
  btScalar m[16]; // transform matrix
  if (body && body->getMotionState()) {
    btTransform trans; 
    btDefaultMotionState* motion = (btDefaultMotionState*)body->getMotionState();
    motion->m_graphicsWorldTrans.getOpenGLMatrix( m );
  }
  else {
    std::cout << "body* passed is null" << std::endl; 
    // obj->getWorldTransform().getOpenGLMatrix(m);
  }
  // vbos[Ball].updateModelMatrix(oglMatrixToGLMMatrix4x4(m));
  // print transform matrix 
  std::cout << "matrix: " << std::endl;
  for (size_t i = 0; i < 4 ; i++) {
    for (size_t j = 0; j < 4 ; j++) {
      std::cout << m[i*4+j] << " "; 
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& v)
{
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const aiVector3t<float>& v)
{
  os << "(" << v.x << "," << v.y << "," << v.z << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const btVector3& v)
{
  os << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const glm::mat4& m)
{
  for(size_t i=0; i < m.row_size(); i++) { 
    os << '[';
    for(size_t j=0; j<m.col_size()-1; j++) { 
      os << m[i][j] << ',';
    }
    os << m[i][m.col_size()-1];
    os << ']';
  }
  return os; 
}


// Structures ----------------------------------------------------------


enum { Ball, Board }; 

struct Point {

  // HERE can glm::vec3 be used for Faces ? glm::vec3 not floats?
  glm::vec3 vertex; 
  glm::vec3 face;
  glm::vec3 normal;
  glm::vec3 color;

  Point() {}

  Point(const glm::vec3& v, const glm::vec3& f, const glm::vec3& n) 
    // : vertex(v), face(f), normal(n)
  {
    vertex = v;
    face = f;
    normal = n;
  }

};

struct Obj {

  std::vector<Point> data; 
  btTriangleMesh bt_triangles;
  glm::mat4 model; 
  Assimp::Importer importer; 
  GLuint vbo;

  Obj(const std::string& fname, const glm::mat4& modelMatrix)
  {

    model = modelMatrix; 

    // load mesh object
    createPoints(fname);
    colorizeByVertexPosition();

    // create vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(Point), data.data(), GL_STATIC_DRAW);

  }

  void updateModelMatrix(const glm::mat4 updatemodel)
  {
    model = updatemodel;
  }

  void createPoints(const std::string& fname)
  {
    
    const aiScene* model = importer.ReadFile(fname.c_str(), 
        aiProcess_Triangulate | aiProcess_SortByPType);

    glm::vec3 vertex; 
    glm::vec3 face;
    glm::vec3 normal;
    
    //for each mesh loaded -->there could be multiple meshes in one obj file
    for(unsigned int i = 0; i < model->mNumMeshes; i ++) {
      const aiMesh* mesh = model->mMeshes[i]; //aiMesh is a struct

      /* get the vertices */
      for(unsigned int j = 0; j < mesh->mNumVertices; j ++) { 
          data.push_back(Point());
          aiVector3D temp_vertex = mesh->mVertices[j];       
          vertex.x = temp_vertex.x;
          vertex.y = temp_vertex.y;
          vertex.z = temp_vertex.z;
          data[j].vertex = vertex;
          // vertices.push_back(vertex);
      } 

      /* get the faces */
      for(unsigned int j = 0; j < mesh->mNumFaces; j ++) {
          //aiProcess_Triangulate creates triangles out of the vertices and so
          //there are 3 indices per faces -- you can check for the number of
          //indices also with "mNumIndices" - data member aiFace 
          aiFace Face = mesh->mFaces[j];  
          btVector3 i,j,k;
          i = aiVector3TobtVector3(  mesh->mVertices[ Face.mIndices[0] ]  );
          j = aiVector3TobtVector3(  mesh->mVertices[ Face.mIndices[1] ]  );
          k = aiVector3TobtVector3(  mesh->mVertices[ Face.mIndices[2] ]  );
          bt_triangles.addTriangle(i,j,k);
          // faces.push_back(face);
      } 
      /* get the faces
      for(unsigned int j = 0; j < mesh->mNumFaces; j ++) {
          //aiProcess_Triangulate creates triangles out of the vertices and so
          //there are 3 indices per faces -- you can check for the number of
          //indices also with "mNumIndices" - data member aiFace 
          aiFace Face = mesh->mFaces[j];  
          face.x = Face.mIndices[0];      
          face.y = Face.mIndices[1];
          face.z = Face.mIndices[2];
          // faces.push_back(face);
      } */

      /* normals */
      if(mesh->HasNormals()) {
        for(unsigned int j = 0; j < mesh->mNumVertices; j ++) { //each vertex has a normal
          aiVector3D temp_vertex = mesh->mNormals[j];
          normal.x = temp_vertex.x;
          normal.y = temp_vertex.y;
          normal.z = temp_vertex.z;
          data[j].normal = normal;
          // normals.push_back(normal);
        }
      }

    }

  }

  void colorizeByVertexPosition()
  {
    Point* p = &data[data.size()-1];
    glm::vec3& v = p->vertex;
    GLfloat max_x, max_y, max_z;

    typedef std::vector<Point>::iterator piter;

    // find max x y z
    max_x = v.x;
    max_y = v.y;
    max_z = v.z;
    for (piter p = data.begin()+1; p != data.end(); p++) {
      glm::vec3& v = p->vertex;
      if (max_x < v.x) max_x = v.x;
      if (max_y < v.y) max_y = v.y;
      if (max_z < v.z) max_z = v.z;
    }
    // put color normalized w.r.t max_x max_y max_z
    for (piter p = data.begin()+1; p != data.end(); p++) {
      glm::vec3& v = p->vertex;
      glm::vec3& c = p->color;
      c.x =  v.x/max_x;
      c.y =  v.y/max_y;
      c.z =  v.z/max_z;
      // std::cout << "color : " << c << std::endl; 
    }

  }

  void draw()
  {

    // glUseProgram(h_program);
    glUniformMatrix4fv(h_model, 1, GL_FALSE, glm::value_ptr(model));
    // glUniformMatrix4fv(h_view, 1, GL_FALSE, glm::value_ptr(view));
    // glUniformMatrix4fv(h_projection, 1, GL_FALSE, glm::value_ptr(projection));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(h_vpos);
    glEnableVertexAttribArray(h_vcolor);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( h_vpos,//location of attribute
                            3,//number of elements
                            GL_FLOAT,//type
                            GL_FALSE,//normalized?
                            sizeof(Point),//stride
                            0 //offset
                            );

    glVertexAttribPointer( 
        h_vcolor, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(Point), 
        (void*)offsetof(Point,color));

    // Draw
    // glDrawArrays(GL_TRIANGLES, 0, triangles.vbosize()*3);//mode, starting index, count // ORIGINAL
    // std::cerr << "numT" << numTriangles << std::endl;
    glDrawArrays(GL_TRIANGLES, 0, data.size());//mode, starting index, count // ORIGINAL

    //clean up
    glDisableVertexAttribArray(h_vpos);
    glDisableVertexAttribArray(h_vcolor);
                          
  }


};

// Function Implementations -------------------------------------------

// Callbacks
void display()
{
    //clear the screen
    // glClearColor(0.0, 0.0, 0.2, 1.0);
    glClearColor(1.0,1.0,0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //premultiply the matrix for this example
    mvp = projection * view * model;

    //enable the shader program
    glUseProgram(h_program);

    //upload the matrix to the shader
    glUniformMatrix4fv(h_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    /* Draw Objects */
    for (size_t i = 0; i < objs.size(); i++) {
      objs[i].draw();
    }

    //swap the buffers
    glutSwapBuffers();
}

void idle()
{

  // check game conditions
  game_done = is_game_complete(bulletBallBody);

  // check 
  if ( game_pause || game_done ) {
    // std::cout << "inside" << std::endl;
    return;
  }

  /* rotate */
  rotationHorizontal -= rotationHorizontal*rotationFactor;
  rotationVertical   -= rotationVertical*rotationFactor;
  rotateBody(bulletBoardBody, 0, 0, rotationHorizontal);
  rotateBody(bulletBoardBody, 0, rotationVertical, 0);

  // std::cout << "rotationHorizontal" << rotationHorizontal << std::endl; 
  // std::cout << "rotationVertical" << rotationVertical << std::endl; 

  // activate 
  // bulletBoardBody->setCollisionFlags( bulletBoardBody->getCollisionFlags() & ~(btCollisionObject::CF_KINEMATIC_OBJECT));
  // bulletBoardBody->activate(true); // or try… bulletBoardBody->forceActivationState(ACTIVE_FLAG)
  bulletBallBody->setCollisionFlags( bulletBallBody->getCollisionFlags() & ~(btCollisionObject::CF_KINEMATIC_OBJECT));
  bulletBallBody->activate(true); // or try… bulletBallBody->forceActivationState(ACTIVE_FLAG)

  // Bullet Simulation 
  // apply force to ball and board 
  bulletBallBody->applyForce ( btVector3( 0,world_gravity,0 ), btVector3(0,0,0) );
  bulletBoardBody->applyForce ( btVector3( 0,-world_gravity,0 ), btVector3(0,0,0) );
  // float t = 10, h = 100, th = 1000;
  // Do Simulation
  dynamicsWorld->stepSimulation(1.f/60.f,10);

  // update model matrices
  objs[Ball].updateModelMatrix( getOglTransformMatrix(bulletBallBody) );
  objs[Board].updateModelMatrix( getOglTransformMatrix(bulletBoardBody) );
  
  // debug
  // std::cout << "ball matrix"<< std::endl;  
  // glm::mat4 m = getOglTransformMatrix(bulletBallBody) ;
  // std::cout << m << std::endl; 


  glutPostRedisplay();

}

void reshape(int w, int h)
{ 
}

// Misc Functions
bool bind_shader_variables(GLuint h_program)
{
// FIXME make a function and use them

  glUseProgram(h_program);

  h_model  = glGetUniformLocation(h_program, const_cast<const char*>("model"));
  if (h_model == -1)
  {
    std::cerr << "[F] model not found" << std::endl;
    return false;
  }
  h_view  = glGetUniformLocation(h_program, const_cast<const char*>("view"));
  if (h_view == -1)
  {
    std::cerr << "[F] view not found" << std::endl;
    return false;
  }
  h_projection  = glGetUniformLocation(h_program, const_cast<const char*>("projection"));
  if (h_projection == -1)
  {
    std::cerr << "[F] projection not found" << std::endl;
    return false;
  }

  // h_mvp = glGetUniformLocation(h_program, const_cast<const char*>("mvpMatrix"));
  // if(h_mvp == -1)
  // {
  //     std::cerr << "[F] MVPMATRIX NOT FOUND" << std::endl;
  //     return false;
  // }
  h_vpos = glGetAttribLocation(h_program, const_cast<const char*>("v_position"));
  if(h_vpos == -1)
  {
      std::cerr << "[F] POSITION NOT FOUND" << std::endl;
      return false;
  }
  h_vcolor = glGetAttribLocation(h_program, const_cast<const char*>("v_color"));
  if(h_vcolor == -1)
  {
      std::cerr << "[F] V_COLOR NOT FOUND" << std::endl;
      return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}
void init_matrices()
{

  model = glm::mat4(1);

  view = glm::lookAt( 
    look_eyepos,
    glm::vec3(0.0, 0.0, 0.0),     // Focus point / Center
    glm::vec3(0.0, 0.0, -1.0)     // Up
  ); 
  projection = glm::perspective(90.0f, float(w)/float(h), 1.0f, 100.0f);

  glUniformMatrix4fv(h_model,       1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(h_view,        1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(h_projection,  1, GL_FALSE, glm::value_ptr(projection));

  // mvp = projection * view * model;

  // glUniformMatrix4fv(h_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
  // projection = glm::perspective( 
  //     90.0f, //the FoV typically 90 degrees is good which is what this is set to
  //     float(width)/float(height), //Aspect Ratio, so Circles stay Circular
  //     0.01f, //Distance to the near plane, normally a small value like this
  //     100.0f); //Distance to the far plane, 
}
void cleanUp()
{
}
bool initialize()
{
  return false;
}

// Keyboard Callbacks
void keyDown(unsigned char key, int x, int y)
{
  // float rotation = 10.0/180*M_PI;

  if (game_pause || game_done ) {
    return;
  }

  switch(key) {
    case 'Q' : exit(0);
    case 'q' : exit(0);
      break;

    /* rotate board with bullet directly */
    case 'h' : { // left 
      rotateBody(bulletBoardBody, 0, 0, rotation);
      std::cout << "h hit h"<< std::endl; 
      break;
    }
    case 'l' : { // right
      rotateBody(bulletBoardBody, 0, 0, -rotation);
      std::cout << "h hit h"<< std::endl; 
      break;
    }
    case 'j' : { // up 
      rotateBody(bulletBoardBody, 0, rotation, 0);
      std::cout << "j hit"<< std::endl; 
      break;
    }
    case 'k' : { // down
      rotateBody(bulletBoardBody, 0, -rotation, 0);
      std::cout << "k hit"<< std::endl; 
      break;
    } 
    default:  {
      break;
    }

  }


}
void keyUp(unsigned char key, int x, int y)
{
}
void keySpecialDown(int key, int x, int y)
{

  if (game_pause || game_done ) {
    return;
  }
  /* Rotate Board */
  switch (key) {

    /* rotate board with bullet directly */
    case GLUT_KEY_LEFT: { // translation : left 
      rotationHorizontal += addrotation;
      // rotateBody(bulletBoardBody, 0, 0, rotation);
      break;
    }
    case GLUT_KEY_RIGHT : { // translation : right
      rotationHorizontal -= addrotation;
      // rotateBody(bulletBoardBody, 0, 0, -rotation);
      break;
    }
    case GLUT_KEY_DOWN : { // translation : up 
      rotationVertical += addrotation;
      // rotateBody(bulletBoardBody, 0, rotation, 0);
      break;
    }
    case GLUT_KEY_UP : { // translation : down
      rotationVertical -= addrotation;
      // rotateBody(bulletBoardBody, 0, -rotation, 0);
      break;
    } 
    default:  {
      break;
    }
    std::cout << "rotation" << rotation << std::endl; 

  }
  
}
void keySpecialUp(int key, int x, int y)
{
}

// 
void glutStuff(int argc, const char *argv[])
{

	glutInitWindowSize(900,600);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	// glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
	glutInit(&argc, const_cast<char**>(argv));

	glutCreateWindow("J6");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
  glutKeyboardFunc(keyDown);        // key down 
  glutKeyboardUpFunc(keyUp);        // key up  
  glutSpecialFunc(keySpecialDown);  // special key down 
  glutSpecialUpFunc(keySpecialUp);  // special key up

}

GLuint initGPU(const std::string& vshader, const std::string& fshader)
{
  // h_program = InitShader("../src/shader.vert", "../src/shader.frag"); 
  h_program = InitShader(vshader.c_str(), fshader.c_str()); 
  if(!h_program) {
    std::cerr << "h_program invalid" << std::endl; 
    exit(1);
  }
  bind_shader_variables(h_program);
  return h_program;
}

// ---
enum { Quit=1, Pause, Resume };
void menu(int id){
  switch (id) {
    case Quit : {
      exit(0);
      break;
    }
    case Pause : {
      game_pause = true;
      break;
    }
    case Resume : {
      game_pause = false;
      break;
    }
  }
  glutPostRedisplay();
} 

void createMenu(void)
{     
  glutCreateMenu(menu);
  // submenu_id = glutCreateMenu(menu);
  // glutAddMenuEntry("Sphere", 1);
  // menu_id = glutCreateMenu(menu);
  glutAddMenuEntry("Pause", Pause);
  glutAddMenuEntry("Resume", Resume);
  glutAddMenuEntry("Quit", Quit);
  // glutAddSubMenu("Draw", submenu_id);
  // glutAddMenuEntry("Quit", 0);     
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Main ---------------------------------------------------------------------

int main(int argc, const char *argv[])
{

  // RotateHelp boardrot(3);
  // std::cout << "rotate angle: " << boardrot.rotate_angle(5) << std::endl;  

  glutStuff(argc, argv);
	glewInit();
  GLuint h_program = initGPU(argv[3], argv[4]); // specify vshader and fshader
  init_matrices();
  createMenu();

  // Obj ball(ball_fname, glm::mat4());
  // Obj board(board_fname, glm::mat4());
  Obj ball(argv[1], glm::mat4());
  Obj board(argv[2], glm::mat4());
  
  objs.push_back(ball);
  objs.push_back(board);

  // Bullet ---------------------------------------------------------------------
  /* Bullet Settings */
  btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
  btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
  btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
  btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
  /* Bullet World */
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,0,0));
	btContactSolverInfo& info = dynamicsWorld->getSolverInfo();

  /* Bullet Object Construction
    [Collision Shapes - Physics Simulation Wiki](http://www.bulletphysics.org/mediawiki-1.5.8/index.php/Collision_Shapes)
	*/

  /* Bullet Ball */
  { 
    // Shape Creation
    btConvexHullShape* ballShape = new btConvexHullShape();
    for (size_t i=0; i<ball.data.size();i++) {
      glm::vec3& v = ball.data[i].vertex;
      ballShape->addPoint( glmvec3_to_btVector3(v) );
    }
		btScalar mass(ball_mass);
		btVector3 localInertia(0,0,0);
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		// position and motion
		btTransform ballTransform;
		ballTransform.setIdentity();
		ballTransform.setOrigin(btVector3(0,ball_initial_height,0));
		btDefaultMotionState* bulletMotionState = new btDefaultMotionState(btTransform(ballTransform));
		// ball rigidbody info
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,bulletMotionState,ballShape,localInertia);
		// tweak rigidbody info
		rbInfo.m_restitution = grestitution;
		rbInfo.m_friction = gfriction;
    // add ball to the world
		bulletBallBody = new btRigidBody(rbInfo);
		if(!bulletBallBody) std::cout << "bulletBallBody pointer null" << std::endl; 
    dynamicsWorld->addRigidBody(bulletBallBody);
  }
   
  /* Bullet Board */
  { 
    // Shape
    btBvhTriangleMeshShape* boardShape = new btBvhTriangleMeshShape( &(board.bt_triangles), true );

		btScalar mass(board_mass);
		btVector3 localInertia(0,0,0);

    // transform : default position
		btTransform boardTransform;
		boardTransform.setIdentity();
		boardTransform.setOrigin(btVector3(0,0,0));
		btDefaultMotionState* bulletMotionState = new btDefaultMotionState(btTransform(boardTransform));
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,bulletMotionState,boardShape,localInertia);

		// tweak rigidbody properties
		rbInfo.m_restitution = grestitution;
		rbInfo.m_friction = gfriction;
		// add to the world
		bulletBoardBody = new btRigidBody(rbInfo);
		if(!bulletBoardBody) std::cout << "bulletBoardBody pointer null" << std::endl; 
    bulletBoardBody->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(bulletBoardBody);

  }


  glutMainLoop();


  return 0;
}


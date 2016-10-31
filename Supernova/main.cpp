/*
    Copyright (c) 2013 Randy Gaul http://RandyGaul.net

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:
      1. The origin of this software must not be misrepresented; you must not
         claim that you wrote the original software. If you use this software
         in a product, an acknowledgment in the product documentation would be
         appreciated but is not required.
      2. Altered source versions must be plainly marked as such, and must not be
         misrepresented as being the original software.
      3. This notice may not be removed or altered from any source distribution.
*/

#include "Precompiled.h"

#define ESC_KEY 27

Scene scene( 1.0f / 60.0f, 10 );
Clock g_Clock;
bool frameStepping = false;
bool canStep = false;

void Mouse( int button, int state, int x, int y )
{
  x /= 10.0f;
  y /= 10.0f;

  if(state == GLUT_DOWN)
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
      {
        Circle c( 8.0f );
        Body *b = scene.Add( &c, x, y );
        b->restitution = 0.9f;
        Circle c1( 4.0f );
        b = scene.Add( &c1, x, y - 13.0f );
        b->restitution = 0.9f;
        Circle c2( 2.0f );
        b = scene.Add( &c2, x, y - 13.0f - 7.0f);
        b->restitution = 0.9f;
        Circle c3( 1.0f );
        b = scene.Add( &c3, x, y - 13.0f - 7.0f - 4.0f);
        b->restitution = 0.9f;

/*
        Circle c4( 0.5f );
        b = scene.Add( &c4, x, y - 13.0f - 7.0f - 4.0f - 2.5);
        b->restitution = 0.9f;
*/

      }
      break;
    case GLUT_RIGHT_BUTTON:
      {
        Circle c( 3.0f );
        Body *b = scene.Add( &c, x, y );
        b->restitution = 0.9f;
        Circle c1( 3.0f );
        b = scene.Add( &c1, x, y - 7.0f );
        b->restitution = 0.9f;
        Circle c2( 3.0f );
        b = scene.Add( &c2, x, y - 7.0f - 7.0f);
        b->restitution = 0.9f;
        Circle c3( 3.0f );
        b = scene.Add( &c3, x, y - 7.0f - 7.0f - 7.0f);
        b->restitution = 0.9f;
      }
      break;
    }
}

void Keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
  case ESC_KEY:
    exit( 0 );
    break;
  case 's':
    {
      //Circle c( 25.0f );
      //scene.Add( &c, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
      //OBB obb;
      //real e = Random( 10.0f, 35.0f );
      //obb.extents.Set( e, e );
      //Body *b = scene.Add( &obb, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
      //b->SetOrient( PI / 4.0f );
      //b->restitution = 0.2f;
      //b->dynamicFriction = 0.2f;
      //b->staticFriction = 0.4f;
    }
    break;
  case 'd':
    {
      //Circle c( 25.0f );
      //scene.Add( &c, 420, 50 );
    }
      break;
  case 'f':
    frameStepping = frameStepping ? false : true;
      break;
  case ' ':
    canStep = true;
    break;
  }
}

void PhysicsLoop( void )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  RenderString( 1, 2, "Left click to spawn particles" );

  static double accumulator = 0;

  // Different time mechanisms for Linux and Windows
#ifdef WIN32
  accumulator += g_Clock.Elapsed( );
#else
  accumulator += g_Clock.Elapsed( ) / static_cast<double>(std::chrono::duration_cast<clock_freq>(std::chrono::seconds(1)).count());
#endif

  g_Clock.Start( );

  accumulator = Clamp( 0.0f, 0.1f, accumulator );
  while(accumulator >= dt)
  {
    if(!frameStepping)
      scene.Step( );
    else
    {
      if(canStep)
      {
        scene.Step( );
        canStep = false;
      }
    }
    accumulator -= dt;
  }

  g_Clock.Stop( );

  scene.Render( );

  glutSwapBuffers( );
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowSize( 800, 600 );
  glutCreateWindow( "PhyEngine" );
  glutDisplayFunc( PhysicsLoop );
  glutKeyboardFunc( Keyboard );
  glutMouseFunc( Mouse );
  glutIdleFunc( PhysicsLoop );

  glMatrixMode( GL_PROJECTION );
  glPushMatrix( );
  glLoadIdentity( );
  gluOrtho2D( 0, 80, 60, 0 );
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix( );
  glLoadIdentity( );

/*
  Circle c( 1.0f );
  Body *b = scene.Add( &c, 40, 40 );
  b->SetStatic( );

*/

  PolygonShape poly;
  poly.SetBox( 30.0f, 1.0f );
  Body *b = scene.Add( &poly, 40, 55 );
  b->restitution = 1.0f;
  b->SetStatic( );
  b->SetOrient( 0 );


  srand( 1 );
  glutMainLoop( );

  return 0;
}

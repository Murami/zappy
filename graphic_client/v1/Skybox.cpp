#include		"Skybox.hh"

namespace		graphic
{
  Skybox::Skybox()
  {
    _quadric = gluNewQuadric();
    gluQuadricNormals(_quadric, GLU_SMOOTH);
    gluQuadricTexture(_quadric, GL_TRUE);
    _texture = SdlGlUtils::loadTexture("./test.jpg");
  }

  void			Skybox::update(const SDL_Event&)
  {
    // FAIRE L'EVENT DE ROTATION DE LA SKYBOX ICI
  }

  void			Skybox::draw()
  {
    glEnable(GL_TEXTURE_2D);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glPushMatrix();
    glLoadIdentity();
    glRotated(-90, 1, 0, 0);
    gluSphere(_quadric, 1000, 100, 100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
  }

  Skybox::~Skybox()
  {
  }
}

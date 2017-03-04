#include "Viewer.hpp"
#include "Mesh.hpp"
#include "DGP/Graphics/RenderSystem.hpp"
#include "DGP/Graphics/Shader.hpp"

#ifdef DGP_OSX
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

Graphics::RenderSystem * Viewer::render_system = NULL;
Mesh * Viewer::mesh = NULL;
int Viewer::width = 640;
int Viewer::height = 480;
Camera Viewer::camera;
Vector3 Viewer::camera_look_at = -Vector3::unitZ();
bool Viewer::dragging = false;
int Viewer::modifier_keys = 0;
int Viewer::last_x = -1;
int Viewer::last_y = -1;
int Viewer::drag_start_x = -1;
int Viewer::drag_start_y = -1;
bool Viewer::show_bbox = false;
bool Viewer::show_edges = false;
MeshVertex const * Viewer::highlighted_vertex = NULL;

void
Viewer::setObject(Mesh * o)
{
  mesh = o;
}

void
Viewer::launch(int argc, char * argv[])
{
  // Create a GL context via a GLUT window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("A2::Viewer");

  // Create a rendersystem
  render_system = new Graphics::RenderSystem("RenderSystem");
  DGP_CONSOLE << render_system->describeSystem();

  // Set up callbacks
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyPress);
  glutMouseFunc(mousePress);
  glutMotionFunc(mouseMotion);

  // Start event processing loop
  glutMainLoop();
}


void
Viewer::fitCameraToObject()
{
  static Real const DIST = 10;
  static Real const NEAR = 1.7f;

  if (!mesh)
    return;

  Real aspect_ratio = (width / (Real)height);
  Real left, right, bottom, top;
  if (aspect_ratio > 1)
  {
    left = -aspect_ratio;
    right = aspect_ratio;
    bottom = -1;
    top = 1;
  }
  else
  {
    left = -1;
    right = 1;
    bottom = -1.0f / aspect_ratio;
    top = 1.0f / aspect_ratio;
  }

  AxisAlignedBox3 const & bbox = mesh->getAABB();
  camera_look_at = bbox.getCenter();
  Real scale = bbox.getExtent().length();
  Real camera_separation = DIST * scale;
  CoordinateFrame3 cframe = camera.getFrame();
  cframe.setTranslation(camera_look_at - camera_separation * camera.getLookDirection());

  camera.set(cframe,
             Camera::ProjectionType::PERSPECTIVE,
             (left / DIST) * scale,
             (right / DIST) * scale,
             (bottom / DIST) * scale,
             (top / DIST) * scale,
             NEAR * scale,
             camera_separation + 1000 * scale,
             Camera::ProjectedYDirection::UP);
}

bool
initMeshShader(Graphics::Shader & shader)
{
  static std::string const VERTEX_SHADER =
"varying vec3 normal;  // normal in camera space\n"
"\n"
"void main()\n"
"{\n"
"  gl_Position = ftransform();\n"
"\n"
"  normal = gl_NormalMatrix * gl_Normal;\n"
"\n"
"  gl_FrontColor = gl_Color;\n"
"  gl_BackColor = gl_Color;\n"
"}\n";

  static std::string const FRAGMENT_SHADER =
"uniform vec3 ambient_color;\n"
"uniform vec3 light_dir;  // must be specified in camera space, pointing towards object\n"
"uniform vec3 light_color;\n"
"uniform vec4 material;  // [ka, kl, <ignored>, <ignored>]\n"
"uniform float two_sided;\n"
"\n"
"varying vec3 normal;  // normal in camera space\n"
"\n"
"void main()\n"
"{\n"
"  vec3 N = normalize(normal);\n"
"  vec3 L = normalize(light_dir);\n"
"\n"
"  vec3 ambt_color = material[0] * gl_Color.rgb * ambient_color;\n"
"\n"
"  float NdL = -dot(N, L);\n"
"  vec3 lamb_color = (NdL >= -two_sided) ? material[1] * abs(NdL) * gl_Color.rgb * light_color : vec3(0.0, 0.0, 0.0);\n"
"\n"
"  gl_FragColor = vec4(ambt_color + lamb_color, gl_Color.a);\n"
"}\n";

  try
  {
    shader.attachModuleFromString(Graphics::Shader::ModuleType::VERTEX, VERTEX_SHADER.c_str());
    shader.attachModuleFromString(Graphics::Shader::ModuleType::FRAGMENT, FRAGMENT_SHADER.c_str());
  }
  DGP_STANDARD_CATCH_BLOCKS(return false;, ERROR, "%s", "Could not attach mesh shader module")

  shader.setUniform("light_dir", Vector3(-1, -1, -2));
  shader.setUniform("light_color", ColorRGB(1, 1, 1));
  shader.setUniform("ambient_color", ColorRGB(1, 1, 1));
  shader.setUniform("two_sided", 1.0f);
  shader.setUniform("material", Vector4(0.2f, 0.6f, 0.2f, 25));

  return true;
}

void
Viewer::draw()
{
  alwaysAssertM(render_system, "Rendersystem not created");

  render_system->setColorClearValue(ColorRGB(0, 0, 0));
  render_system->clear();

  if (mesh)
  {
    // Initialize the shader
    static Graphics::Shader * mesh_shader = NULL;  // Ok since Viewer fns are all static. Else should have a shader per Viewer.
    if (!mesh_shader)
    {
      mesh_shader = render_system->createShader("Mesh shader");
      if (!mesh_shader)
        return;

      if (!initMeshShader(*mesh_shader))
        return;
    }

    render_system->setMatrixMode(Graphics::RenderSystem::MatrixMode::MODELVIEW); render_system->pushMatrix();
    render_system->setMatrixMode(Graphics::RenderSystem::MatrixMode::PROJECTION); render_system->pushMatrix();

      render_system->setCamera(camera);

      render_system->pushShader();

        render_system->setShader(mesh_shader);
        render_system->setColor(ColorRGB(1, 1, 1));
        mesh->draw(*render_system, /* draw_edges = */ show_edges, /* use_vertex_data = */ false, /* send_colors = */ false);

        if (show_bbox)
        {
          render_system->setShader(NULL);
          render_system->setColor(ColorRGB(1, 1, 0));
          drawOutlineBox(mesh->getAABB());
        }

        if (highlighted_vertex)
        {
          render_system->setShader(NULL);
          render_system->setColor(ColorRGB(1, 0, 0));
          render_system->setPointSize(10);

          render_system->beginPrimitive(Graphics::RenderSystem::Primitive::POINTS);
            render_system->sendVertex(highlighted_vertex->getPosition());
          render_system->endPrimitive();
        }

      render_system->popShader();

    render_system->setMatrixMode(Graphics::RenderSystem::MatrixMode::PROJECTION); render_system->popMatrix();
    render_system->setMatrixMode(Graphics::RenderSystem::MatrixMode::MODELVIEW); render_system->popMatrix();
  }

  glutSwapBuffers();
}

void
Viewer::reshape(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, width, height);
  fitCameraToObject();

  glutPostRedisplay();
}

Matrix3
dragToRotation(int x1, int y1, int x2, int y2, int width, int height, Camera const & camera)
{
  static Real const ROT_SPEED = 5;

  // Pixel coordinates increase top to bottom, so dy is downwards in camera space
  int dx = x2 - x1;
  int dy = y2 - y1;
  if (dx == 0 && dy == 0)
    return Matrix3::identity();

  Vector3 axis = dy * camera.getRightDirection() + dx * camera.getUpDirection();

  int size = (width < height ? width : height);
  Real angle = ROT_SPEED * Vector2(dx, -dy).length() / size;

  return Matrix3::rotationAxisAngle(axis, angle);
}

Real
dragToScale(int x1, int y1, int x2, int y2, int width, int height, Camera const & camera)
{
  static Real const SCALE_INC_SPEED = 4;
  static Real const SCALE_DEC_SPEED = 2;
  static Real const MIN_SCALE = 0.25;

  // Pixel coordinates increase top to bottom, so dy is downwards in camera space
  int dy = y2 - y1;
  if (dy < 0)  // drag up => increase
    return std::max(1 - SCALE_INC_SPEED * dy / (Real)height, MIN_SCALE);
  else  // drag down => decrease
    return std::max(1 - SCALE_DEC_SPEED * dy / (Real)height, MIN_SCALE);
}

AffineTransform3
zoomTransform(Real zoom, Real camera_separation, Vector3 const & zoom_dir)
{
  static Real const MIN_ZOOM = 0.25;
  Vector3 trn = (1.0f / std::max(zoom, MIN_ZOOM) - 1) * camera_separation * zoom_dir;
  return AffineTransform3(Matrix3::identity(), trn);
}

void
Viewer::keyPress(unsigned char key, int x, int y)
{
  if (key == 27)
  {
    exit(0);
  }
  else if (key == 'b' || key == 'B')
  {
    show_bbox = !show_bbox;
    glutPostRedisplay();
  }
  else if (key == 'e' || key == 'E')
  {
    show_edges = !show_edges;
    glutPostRedisplay();
  }
  else if (key == 'f' || key == 'F')
  {
    fitCameraToObject();
    glutPostRedisplay();
  }
  else if (key == 'd' || key == 'd')
  {
    highlighted_vertex = mesh->decimateQuadricEdgeCollapse();
    glutPostRedisplay();
  }
}

void
Viewer::incrementViewTransform(AffineTransform3 const & tr)
{
  AffineTransform3 inv_vt = tr.inverse();
  CoordinateFrame3 const & old_cframe = camera.getFrame();
  camera.setFrame(CoordinateFrame3(RigidTransform3::_fromAffine(AffineTransform3(inv_vt.getLinear() * old_cframe.getRotation(),
                                                                                 inv_vt * old_cframe.getTranslation()))));

  glutPostRedisplay();
}

void
Viewer::mousePress(int button, int state, int x, int y)
{
  dragging = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
  modifier_keys = glutGetModifiers();

  last_x = x;
  last_y = y;

  if (dragging)
  {
    drag_start_x = x;
    drag_start_y = y;
  }
}

void
Viewer::mouseMotion(int x, int y)
{
  if (!dragging)
    return;

  if (modifier_keys == GLUT_ACTIVE_SHIFT)
  {
    Real zoom = dragToScale(last_x, last_y, x, y, width, height, camera);

    // Zoom in at mouse position, zoom out at screen center
    Vector3 dir;
    if (zoom > 1)
    {
      Vector2 drag_pos(2 * drag_start_x / (Real)width - 1, 1 - 2 * drag_start_y / (Real)height);
      dir = camera.computePickRay(drag_pos).getDirection().unit();
    }
    else
      dir = camera.getLookDirection();

    Real camera_separation = (camera_look_at - camera.getPosition()).length();
    incrementViewTransform(zoomTransform(zoom, camera_separation, dir));
  }
  else
  {
    Matrix3 rot = dragToRotation(last_x, last_y, x, y, width, height, camera);
    Vector3 trn = camera_look_at - rot * camera_look_at;
    incrementViewTransform(AffineTransform3(rot, trn));
  }

  last_x = x;
  last_y = y;

  glutPostRedisplay();
}

void
Viewer::drawOutlineBox(AxisAlignedBox3 const & bbox)
{
  if (!render_system)
    return;

  render_system->pushShader();
    render_system->setShader(NULL);

    render_system->beginPrimitive(Graphics::RenderSystem::Primitive::LINES);
      Vector3 p, q;
      for (int i = 0; i < 12; ++i)
      {
        bbox.getEdge(i, p, q);
        render_system->sendVertex(p);
        render_system->sendVertex(q);
      }
    render_system->endPrimitive();

  render_system->popShader();
}

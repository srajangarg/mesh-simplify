#ifndef __A2_Viewer_hpp__
#define __A2_Viewer_hpp__

#include "Common.hpp"
#include "DGP/AxisAlignedBox3.hpp"
#include "DGP/Camera.hpp"
#include "DGP/Matrix3.hpp"
#include "DGP/Graphics/RenderSystem.hpp"

// Forward declaration
class Mesh;
class MeshVertex;

/* Displays an object using OpenGL and GLUT. */
class Viewer
{
  private:
    static Graphics::RenderSystem * render_system;
    static Mesh * mesh;

    static int width;
    static int height;
    static Camera camera;
    static Vector3 camera_look_at;
    static bool dragging;
    static int modifier_keys;
    static int last_x, last_y;
    static int drag_start_x, drag_start_y;
    static bool show_bbox;
    static bool show_edges;
    static MeshVertex const * highlighted_vertex;

  public:
    /** Set the object to be displayed. The object must persist as long as the viewer does. */
    static void setObject(Mesh * o);

    /**
     * Call this function to launch the viewer. It will not return under normal circumstances, so make sure stuff is set up
     * before you call it!
     */
    static void launch(int argc, char * argv[]);

  private:
    /** Callback for drawing the object. */
    static void draw();

    /** Callback when window is resized. */
    static void reshape(int w, int h);

    /** Callback when a key is pressed. */
    static void keyPress(unsigned char key, int x, int y);

    /** Callback when a mouse button is pressed. */
    static void mousePress(int button, int state, int x, int y);

    /** Callback when the mouse moves with a button pressed. */
    static void mouseMotion(int x, int y);

    /** Draw a bounding box as an outline. */
    static void drawOutlineBox(AxisAlignedBox3 const & bbox);

    /** Position the camera to center the object and fit it in the frame, without changing orientation. */
    static void fitCameraToObject();

    /** Update the camera view by adding an additional transform. */
    static void incrementViewTransform(AffineTransform3 const & tr);

}; // class Viewer

#endif

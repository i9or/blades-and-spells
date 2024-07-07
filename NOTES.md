# Notes

## FPS mode mouse handler

Unfortunately GLUT has a very terrible mouse handling, so at this point it was
decided to fallback to old school controls with keyboard. Saving this procedure
just in case I'll change my mind.

```c
void mouseMotionHandler(int x, int y) {
  static bool justWarped = false;

  if (justWarped) {
    justWarped = false;
    return;
  }

  if (gFpsMode) {
    justWarped = true;

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    float windowPosX = (float)glutGet(GLUT_WINDOW_X);
    float windowPosY = (float)glutGet(GLUT_WINDOW_Y);

    // Moving cursor to the center of the window
    CGPoint warpPoint = CGPointMake((float)w / 2 + windowPosX, (float)h / 2 + windowPosY);
    CGWarpMouseCursorPosition(warpPoint);
    CGAssociateMouseAndMouseCursorPosition(true);

    int dx = x - (w / 2);
    int dy = (h / 2) - y;

    if (dx) {
      cameraRotateYaw(dx);
    }

    if (dy) {
      cameraRotatePitch(dy);
    }
  }

  glutPostRedisplay();
}
```

## Camera collisions

Need to decide wether camera will calculate collision with the landscape based on the interpolated values from the heightmap or real collision detection system based on geometry needs to be implemented.

Will probably go with the latter as it automatically solves the collision detection with the buildings and other objects in the scene.

To effectively implement collision detection with the geometry the ROAM technique needs to be implemented, as level is a square ortholinear grid and buildings could be positioned only on the grid, with no rotations or other translations whatsoever.

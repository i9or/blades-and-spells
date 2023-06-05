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


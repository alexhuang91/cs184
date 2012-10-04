#include "WorkingScene.h"

// This file includes the basic functions that your program must fill in.  
// Your assignment consists of filling in parts that say /* YOUR CODE HERE */

// What happens when you drag the mouse to x and y?  
// In essence, you are dragging control points on the curve.
void WorkingScene::drag(int x, int y) {
  /* YOUR CODE HERE */
  //you must figure out how to transform x and y so they make sense
  //update oldx, and oldy
  //make sure scene gets redrawn
  int diffx = x - oldx, diffy = oldy - y;
  float normx = diffx /(float)width, normy = diffy / (float)height;
  theOnlyCurve->moveActivePoint(normx, normy);
  oldx = x;
  oldy = y;
  glutPostRedisplay();
}

// Mouse motion.  You need to respond to left clicks (to add points on curve) 
// and right clicks (to delete points on curve) 
void WorkingScene::mouse(int button, int state, int x, int y) {
  float normx = x / (float)width, normy = (height-y) / (float)height;
  if (theOnlyCurve && state == GLUT_DOWN) {
    if (button == GLUT_LEFT_BUTTON) {
      /* YOUR CODE HERE */
      theOnlyCurve->addPoint(normx,normy);
    }
    if (button == GLUT_RIGHT_BUTTON) {	
      /* YOUR CODE HERE */
      theOnlyCurve->updateActivePoint(normx,normy);
      theOnlyCurve->deleteActivePoint();
    }
  }
  /* YOUR CODE HERE */
  //update oldx, and oldy
  //make sure scene gets redrawn
  oldx = x;
  oldy = y;
  glutPostRedisplay();
}



#include "Bezier.h"

// Bezier drawing function.  This is by deCasteljau or equivalent algorithm. 
// It should support Bezier curves of arbitrary degree/order.
void Bezier::draw(int levelOfDetail) {

  connectTheDots();
  int i,j,n, level;
  float u,x,y;
  Pvector *bezier = new Pvector();
  Pvector::iterator p, bez, end;

  /*YOUR CODE HERE*/
  for (j = 0; j <= levelOfDetail; j++) {      //for loop for every level of detail
    u = j/(float)levelOfDetail;              //"level of detail" = 0, 1/levelOfDetail, ..., 1
    n = points.size() - 1;                   //degree, which is # of points - 1
    Pvector pts = points;                    //there are n pts initially
    for (level = n - 1; level >= 0; level--) {   //for each point
      Pvector *newpts = new Pvector();       //Create a vector of points
      p = pts.begin();                       //initialize an iterator
      for (i = 0; i <= level; i++) {         //for every level
        x = (1-u) * (p->x) + u * ((p+1)->x); //calculate x
        y = (1-u) * (p->y) + u * ((p+1)->y); //calculate y
        (*newpts).push_back(Point(x,y));     //push Point(x,y) to newpts
        p++;                                 //increment
      }
      pts = *newpts;                         //assign newpts as pts
    }
    (*bezier).push_back(Point(x,y));         //push to bezier vector
  }
  int iter = 1;
  if (points.size() > 1) {
    for (bez = (*bezier).begin(); bez != (*bezier).end(); bez++) {
      if(iter == 0) {
        drawLine(bez->x,bez->y,(bez-1)->x, (bez-1)->y);
      }
      else {
        iter--;
      }
    }
  }
}



#include "Bspline.h"

// The B-Spline drawing routine.  
// Remember to call drawSegment (auxiliary function) for each set of 4 points.
void Bspline::draw(int levelOfDetail) {
  connectTheDots();
  /* YOUR CODE HERE */
  int i = 1;
  Pvector::iterator p1, p2, p3, p4;
  for (Pvector::iterator it = points.begin(); it != points.end(); it++) {
    //if (i > 4) {
    //drawLine(p1->x,p1->y,p2->x,p2->y);
    //}
    p1 = p2;
    p2 = p3;
    p3 = p4;
    p4 = it;
    if (i > 3) {
      drawSegment(p1, p2, p3, p4, levelOfDetail);
    }
    i++;
  }
}

void Bspline::drawSegment(Pvector::iterator p1, Pvector::iterator p2, 
    Pvector::iterator p3, Pvector::iterator p4, int levelOfDetail) {

  float u, x, y, xold, yold;
  int i;
  /* YOUR CODE HERE */
  //draw segment
  xold = (1/6.0f)*((float)((p1->x) + 4*(p2->x) + (p3->x)));
  yold = (1/6.0f)*((float)((p1->y) + 4*(p2->y) + (p3->y)));
  Point(xold,yold).draw();
  for (i = 1; i <= levelOfDetail; i++) {
    u = i/((float)levelOfDetail);
    x =  u*u*u*((1/6.0f)*((float)( -(p1->x) + 3*(p2->x) - 3*(p3->x) + (p4->x))))
        +  u*u*((1/6.0f)*((float)(3*(p1->x) - 6*(p2->x) + 3*(p3->x))))
        +    u*((1/6.0f)*((float)(-3*(p1->x) + 3*(p3->x))))
        +      ((1/6.0f)*((float)(  (p1->x) + 4*(p2->x) +   (p3->x))));
    y =  u*u*u*((1/6.0f)*((float)( -(p1->y) + 3*(p2->y) - 3*(p3->y) + (p4->y))))
        +  u*u*((1/6.0f)*((float)(3*(p1->y) - 6*(p2->y) + 3*(p3->y))))
        +    u*((1/6.0f)*((float)(-3*(p1->y) + 3*(p3->y))))
        +      ((1/6.0f)*((float)(  (p1->y) + 4*(p2->y) +   (p3->y))));
    drawLine(xold,yold,x,y);
    xold = x;
    yold = y;
  }
  //then create a Point to be drawn where the knot should be
  Point p(x, y);
  p.draw();
}

#include "Bezier2.h"

//This function is provided to aid you.
//It should be used in the spirit of recursion, though you may choose not to.
//This function takes an empty vector of points, accum
//It also takes a set of control points, pts, and fills accum with
//the control points that correspond to the next level of detail.
void accumulateNextLevel(Pvector* accum, Pvector pts) {
  if (pts.empty()) return; 
  accum->push_back(*(pts.begin()));
  if (pts.size() == 1) return;
  for (Pvector::iterator it = pts.begin(); it != pts.end() - 1; it++) {
    /* YOUR CODE HERE  (only one to three lines)*/
    *it = Point(((1/2.0f)*((it->x) + ((it+1)->x))),((1/2.0f)*((it->y) + ((it+1)->y))));
  }
  //save the last point
  Point last = *(pts.end()-1);
  pts.pop_back();
  //recursive call
  accumulateNextLevel(accum, pts);
  accum->push_back(last);
}


// The basic draw function for Bezier2.  Note that as opposed to Bezier, 
// this draws the curve by recursive subdivision.  So, levelofdetail 
// corresponds to how many times to recurse.  
void Bezier2::draw(int levelOfDetail) {
  //This is just a trick to find out if this is the top level call
  //All recursive calls will be given a negative integer, to be flipped here
  if (levelOfDetail > 0) {
    connectTheDots();
  } else {
    levelOfDetail = -levelOfDetail;
  }

  //Base case.  No more recursive calls.
  if (levelOfDetail <= 1) {
    if (points.size() >= 2) {
      for (Pvector::iterator it = points.begin(); it != points.end() - 1; it++) {
        /* YOUR CODE HERE */
        drawLine((it->x),(it->y),((it+1)->x),((it+1)->y));
      }
    }
  } else {
    Pvector* accum = new Pvector();
    Bezier2 left, right;

    //add the correct points to 'left' and 'right'.
    //You may or may not use accum as you see fit.
    /* YOUR CODE HERE */
    accumulateNextLevel(accum, points);
    Pvector::iterator it = (*accum).begin();
    int size = (*accum).size();
    for (int i = 1; i <= size; i++) {
      int half = size/2;
      if ((i <= half) || (((size % 2) == 1) && (i == (half + 1)))) {
        left.points.push_back(*it);
      }
      if (i > half) {
        right.points.push_back(*it);
      }
      it++;
    }
    left.draw(1-levelOfDetail);
    right.draw(1-levelOfDetail);
    delete accum;
  }
}

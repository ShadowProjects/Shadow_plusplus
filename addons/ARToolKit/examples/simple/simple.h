//
//  simple.h
//  ARToolKit
//
//  Created by shimonaka on 2014/04/14.
//
//

#ifndef __ARToolKit__simple__
#define __ARToolKit__simple__

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef __APPLE__
#include <GL/gl.h>
#include <GL/glut.h>
#  ifdef GL_VERSION_1_2
#    include <GL/glext.h>
#  endif
#else
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif
#include <AR/config.h>
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>
#include <AR/gsub_lite.h>
#include <math.h>
#include <time.h>

#include <iostream>

class ground
{
public:
    void draw(void);
    
#define GR      1000
    static double          mak_posx;
    static double          mak_posy;
    static int             gr_count;
    static int             gr_flg;
    static double          gr_xpos;
    static double          gr_ypos;
    static double          groot_count;
    static int             draw_flg;
    static float           copy_array_right[GR];
    static float           copy_array_left[GR];
};

class snow
{
public:
    void flow_right(void);
    void flow_left(void);

    
#define SNOW  200 // the number of snow
    static int             down_count[SNOW];
    static int             snowxpos_flg[SNOW];
    static int             snowypos_flg[SNOW];
    static float           snow_xpos[SNOW];
    static float           snow_ypos[SNOW];
    static int             snow_cou[SNOW];
    static float           fall_flg;
    static float           xflow[SNOW];
    static float           snow_noise[SNOW];
    static double          cosx_plus;
    static double          cosx_minus;
    static int             rotate_flg;
    static float           alfa; // KOKO! (BUFFALO = 2.5)(CCD = 0.5)
    static int             l;
};

class random
{
public:
    static float GetRandom(float min, float max){
        return min + (float)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
    }
    static float GetRandom_plus(float min, float max){
        return min + (float)((rand()-(rand()%10))*(max-min+1.0)/(1.0+RAND_MAX));
    }
};

class circle
{
public:
    const int PART = 100;  //time of part

    void draw(void);
    
    int i, n = PART;
    float x, y, r = 20.0;
    double rate;

    float           a, b;
};

class fan
{
public:
    void draw(void);
    circle draw_circle;
};


class root
{
public:
    void draw(void);
};


#endif /* defined(__ARToolKit__simple__) */

//
//  simple.cpp
//  ARToolKit
//
//  Created by shimonaka on 2014/04/14.
//
//

#include "simple.h"

//
// Camera configuration.
//
#ifdef _WIN32
char			*vconf = "Data\\WDM_camera_flipV.xml";
#else
char			*vconf = "";
#endif

int             xsize, ysize;
int             thresh = 80;
int             count = 0;

char           *cparam_name    = "Data/camera_para.dat";
ARParam         cparam;

char           *patt_name      = "Data/patt.hiro";
int             patt_id;
double          patt_width     = 80.0;
double          patt_center[2] = {0.0, 0.0};
double          patt_trans[3][4];

// hikaku you
double          pre_patt_trans[3];
double          mark_11 = 0;
double          mark_31 = 0;

// capture flag
static int      capFlag = 0;
// mainloop time of doing count
int             do_count = 0;
// as cording count
int             test_count = 0;
// as cording flag
int             test_flag = 0;


static void   init(void);
static void   cleanup(void);
static void   keyEvent( unsigned char key, int x, int y);
static void   mouseEvent(int button, int state, int x, int y);
static void   mainLoop(void);
static void   draw(double cosine);


double ground::mak_posx = 0;
double ground::mak_posy= 0;
int ground::gr_count = 0;
int ground::gr_flg = 0;
double ground::groot_count = 0;
int ground::draw_flg = 0;
double ground::gr_xpos = 0;
double ground::gr_ypos = 0;
float ground::copy_array_right[];
float ground::copy_array_left[];

int snow::down_count[SNOW];
int snow::snowxpos_flg[SNOW];
int snow::snowypos_flg[SNOW];
float snow::snow_xpos[SNOW];
float snow::snow_ypos[SNOW];
int snow::snow_cou[SNOW];
float snow::xflow[SNOW];
float snow::snow_noise[SNOW];
float snow::fall_flg = 0;
int snow::rotate_flg = 0;
double snow::cosx_plus = 1.0;
double snow::cosx_minus = 1.0;
float snow::alfa = 0.5;
int snow::l = 0;

void ground::draw(void)
{    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    float array_right[ground::draw_flg+1];
    float array_left[ground::draw_flg+1];
    
    for (int n = 0; n<ground::draw_flg; n++) {
        array_right[n]=ground::copy_array_right[n];
        array_left[n]=ground::copy_array_left[n];
    }
    
    array_right[ground::draw_flg]=random::GetRandom_plus(-3.0, 3.0);
    array_left[ground::draw_flg]=random::GetRandom_plus(-3.0, 3.0);
    
    for (int i =0; i<ground::draw_flg+1; i++) {
        glVertex2d(ground::gr_xpos + 12*i, (ysize - ground::gr_ypos) - (ysize / 12)+array_right[i]); // KOKO! (BUFFALO = 12)(CCD = 15)
        glVertex2d(ground::gr_xpos + 12*(i+1), (ysize - ground::gr_ypos) - (ysize / 12)+array_right[i+1]);
        glVertex2d(ground::gr_xpos + 12*(i+1), 0);
        glVertex2d(ground::gr_xpos + 12*i, 0);
        
        glVertex2d(ground::gr_xpos - 12*i, (ysize - ground::gr_ypos) - (ysize / 12)+array_left[i]); // KOKO! (BUFFALO = 12)(CCD = 15)
        glVertex2d(ground::gr_xpos - 12*(i+1), (ysize - ground::gr_ypos) - (ysize / 12)+array_left[i+1]);
        glVertex2d(ground::gr_xpos - 12*(i+1), 0);
        glVertex2d(ground::gr_xpos - 12*i, 0);
    }
    
    for (int m=0; m<ground::draw_flg+1; m++) {
        ground::copy_array_right[m]=array_right[m];
        ground::copy_array_left[m]=array_left[m];
    }
    
    glEnd();
}

void snow::flow_right(void)
{
    if (snow::cosx_plus >= 0.995 && snow::cosx_plus < 1.0) {
        snow::xflow[l] += 0;
    }
    else if (snow::cosx_plus >= 0.98 && snow::cosx_plus < 0.995) {
        snow::xflow[l] += (snow::alfa / 2);
    }
    else if (snow::cosx_plus >= 0.97 && snow::cosx_plus < 0.98) {
        snow::xflow[l] += snow::alfa;
    }
    else if (snow::cosx_plus >= 0.96 && snow::cosx_plus < 0.97) {
        snow::xflow[l] += (snow::alfa * 2);
    }
    else if (snow::cosx_plus >= 0.95 && snow::cosx_plus < 0.96) {
        snow::xflow[l] += (snow::alfa * 3);
    }
    else if (snow::cosx_plus >= 0.94 && snow::cosx_plus < 0.95) {
        snow::xflow[l] += (snow::alfa * 4);
    }
    else if (snow::cosx_plus >= 0.93 && snow::cosx_plus < 0.94) {
        snow::xflow[l] += (snow::alfa * 5);
    }
    else if (snow::cosx_plus >= 0.92 && snow::cosx_plus < 0.93) {
        snow::xflow[l] += (snow::alfa * 6);
    }
    else if (snow::cosx_plus >= 0.91 && snow::cosx_plus < 0.92) {
        snow::xflow[l] += (snow::alfa * 7);
    }
    else if (snow::cosx_plus >= 0.90 && snow::cosx_plus < 0.91) {
        snow::xflow[l] += (snow::alfa * 8);
    }
    else if (snow::cosx_plus >= 0.88 && snow::cosx_plus < 0.89) {
        snow::xflow[l] += (snow::alfa * 9);
    }
    else if (snow::cosx_plus >= 0.87 && snow::cosx_plus< 0.88) {
        snow::xflow[l] += (snow::alfa * 10);
    }
    else if (snow::cosx_plus >= 0.86 && snow::cosx_plus < 0.87) {
        snow::xflow[l] += (snow::alfa * 11);
    }
    else if (snow::cosx_plus >= 0.85 && snow::cosx_plus< 0.86) {
        snow::xflow[l] += (snow::alfa * 12);
    }
    else if (snow::cosx_plus >= 0.84 && snow::cosx_plus < 0.85) {
        snow::xflow[l] += (snow::alfa * 13);
    }
    else if (snow::cosx_plus >= 0.825 && snow::cosx_plus < 0.84) {
        snow::xflow[l] += (snow::alfa * 14);
    }
    else if (snow::cosx_plus < 0.825) {
        snow::xflow[l] += (snow::alfa * 15);
    }
    
}

void snow::flow_left(void)
{
    if (snow::cosx_minus >= 0.995 && snow::cosx_minus < 1.0) {
        snow::xflow[l] -= 0;
    }
    else if (snow::cosx_plus >= 0.98 && snow::cosx_plus < 0.995) {
        snow::xflow[l] -= (snow::alfa / 2);
    }
    else if (snow::cosx_minus >= 0.97 && snow::cosx_minus < 0.98) {
        snow::xflow[l] -= snow::alfa;
    }
    else if (snow::cosx_minus >= 0.96 && snow::cosx_minus < 0.97) {
        snow::xflow[l] -= (snow::alfa * 2);
    }
    else if (snow::cosx_minus >= 0.95 && snow::cosx_minus < 0.96) {
        snow::xflow[l] -= (snow::alfa * 3);
    }
    else if (snow::cosx_minus >= 0.94 && snow::cosx_minus < 0.95) {
        snow::xflow[l] -= (snow::alfa * 4);
    }
    else if (snow::cosx_minus >= 0.93 && snow::cosx_minus < 0.94) {
        snow::xflow[l] -= (snow::alfa * 5);
    }
    else if (snow::cosx_minus >= 0.92 && snow::cosx_minus < 0.93) {
        snow::xflow[l] -= (snow::alfa * 6);
    }
    else if (snow::cosx_minus >= 0.91 && snow::cosx_minus < 0.92) {
        snow::xflow[l] -= (snow::alfa * 7);
    }
    else if (snow::cosx_minus >= 0.90 && snow::cosx_minus < 0.91) {
        snow::xflow[l] -= (snow::alfa * 8);
    }
    else if (snow::cosx_minus >= 0.88 && snow::cosx_minus < 0.89) {
        snow::xflow[l] -= (snow::alfa * 9);
    }
    else if (snow::cosx_minus >= 0.87 && snow::cosx_minus < 0.88) {
        snow::xflow[l] -= (snow::alfa * 10);
    }
    else if (snow::cosx_minus >= 0.86 && snow::cosx_minus < 0.87) {
        snow::xflow[l] -= (snow::alfa * 11);
    }
    else if (snow::cosx_minus >= 0.85 && snow::cosx_minus < 0.86) {
        snow::xflow[l] -= (snow::alfa * 12);
    }
    else if (snow::cosx_minus >= 0.84 && snow::cosx_minus < 0.85) {
        snow::xflow[l] -= (snow::alfa * 13);
    }
    else if (snow::cosx_minus >= 0.825 && snow::cosx_minus < 0.84) {
        snow::xflow[l] -= (snow::alfa * 14);
    }
    else if (snow::cosx_minus < 0.825) {
        snow::xflow[l] -= (snow::alfa * 15);
    }
    
}

void circle::draw(void)
{
    const float PAI = 3.14159265358979;

    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        rate = (double)i / n;
        x = r * cos(2.0 * PAI * rate);
        y = r * sin(2.0 * PAI * rate);
        glVertex3f(x, y, 0.0);
    }
    glEnd();    
}

void fan::draw(void)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);  // stem
    //    glTexCoord2d(0.0, 10.0);
    glVertex3d(-2.0, -10.0, 0.0);
    //    glTexCoord2d(10.0, 10.0);
    glVertex3d(2.0, -10.0, 0.0);
    //    glTexCoord2d(10.0, 0.0);
    glVertex3d(2.0, 10.0, 0.0);
    //    glTexCoord2d(0.0, 0.0);
    glVertex3d(-2.0, 10.0, 0.0);
    glEnd();
    
    glPopMatrix();
    // circle
    glPushMatrix();
    glTranslatef(0.0, 10.0, 0.0);

    draw_circle.draw();

    glFlush();
    
    glPopMatrix();
 
}

void root::draw()
{
    // center
    glPushMatrix();
    glTranslatef(0.0, -17.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.9, -10.0, 0.0);
    glVertex3f(1.9, -10.0, 0.0);
    glVertex3f(0.0, -30.0, 0.0);
    glEnd();
    glPopMatrix();
    // left
    glPushMatrix();
    glTranslatef(0.0, -17.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0, -8.0, 0.0);
    glVertex3f(-1.0, -10.0, 0.0);
    glVertex3f(-8.0, -20.0, 0.0);
    glEnd();
    glPopMatrix();
    // right
    glPushMatrix();
    glTranslatef(0.0, -17.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(2.0, -8.0, 0.0);
    glVertex3f(1.0, -10.0, 0.0);
    glVertex3f(8.0, -20.0, 0.0);
    glEnd();
    glPopMatrix();

}

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL));
    
	glutInit(&argc, argv);
	init();
    
    arVideoCapStart();
    argMainLoop( mouseEvent, keyEvent, mainLoop );
	return (0);
}

static void   keyEvent( unsigned char key, int x, int y)
{
    /* quit if the ESC key is pressed */
    if( key == 0x1b ) {
        printf("*** %f (frame/sec)\n", (double)count/arUtilTimer());
        cleanup();
        exit(0);
    }
}

static void   mouseEvent(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON) {
            arVideoCapStop();
            capFlag = 1;
        }
        
        else if (button == GLUT_RIGHT_BUTTON) {
            capFlag = 0;
            arVideoCapStart();
        }
    }
}

/* main loop */
static void mainLoop(void)
{
    circle loop;
    loop.r = 3;
    ground gr_loop;
    snow sn_loop;
    
    ARUint8         *dataPtr;
    ARMarkerInfo    *marker_info;
    int             marker_num;
    int             j, k;
    
    // left--
    // kasou point
    double          ver_pos_l[2];
    // far
    double          far_a1_l, far_b1_l, far_a2_l, far_b2_l;
    // 2 jou
    double          far_a1_2_l, far_b1_2_l, far_a2_2_l, far_b2_2_l;
    // wa
    double          far_deno_l;
    // root
    double          far_mole_l;
    double          root_a_l;
    double          root_b_l;
    
    // right--
    // kasou point
    double          ver_pos_r[2];
    // far
    double          far_a1_r, far_b1_r, far_a2_r, far_b2_r;
    // 2 jou
    double          far_a1_2_r, far_b1_2_r, far_a2_2_r, far_b2_2_r;
    // wa
    double          far_deno_r;
    // root
    double          far_mole_r;
    double          root_a_r;
    double          root_b_r;
    
    double          cosine;
    
    
    /* not doing when stop capturing*/
    if(capFlag > 0) {
        return;
    }
    
    /* grab a vide frame */
    if( (dataPtr = (ARUint8 *)arVideoGetImage()) == NULL ) {
        arUtilSleep(2);
        return;
    }
    if( count == 0 ) arUtilTimerReset();
    count++;
    
    argDrawMode2D();
    //    argDispImage( dataPtr, 0,0 );
    glColor3f(1.0, 1.0, 1.0);
    argDispImage(0, 0, 0 );  //(pointer, draw window number, same)
    
    // draw ground-------------------------------------------------------------------------------------------------
    if (test_flag == 1 && ground::gr_flg == 0) {
        ground::gr_xpos = ground::mak_posx;
        ground::gr_ypos = ground::mak_posy;
        ground::gr_flg = 1;
    }
    if (test_flag == 1 && ground::gr_flg == 1) {
        gr_loop.draw();
        if (ground::draw_flg < 1000) {
            ground::draw_flg ++;
        }
        if (ground::gr_count < xsize) {
            ground::gr_count += 6; // KOKO! (BUFFALO = 40)(CCD = 6)
            ground::groot_count++;
        }
        glColor3f(1.0, 1.0, 1.0);
    }
    // draw ground-------------------------------------------------------------------------------------------------
    
    // draw snow---------------------------------------------------------------------------------------------------
    for (snow::l = 0; snow::l < SNOW; snow::l++) {
        if (test_flag == 1 && snow::snowxpos_flg[snow::l] == 0) {
            snow::snow_xpos[snow::l] = random::GetRandom(-500, xsize + 500);
            snow::snow_noise[snow::l] = random::GetRandom(-1.0, 1.0);
            snow::snowxpos_flg[snow::l] = 1;
        }
        if (test_flag == 1 && snow::snowypos_flg[snow::l] == 0) {
            snow::snow_ypos[snow::l] = random::GetRandom(0, ysize);
            snow::snowypos_flg[snow::l] = 1;
        }
        
        if (test_flag == 1 && snow::snowxpos_flg[snow::l] == 1) {
            glPushMatrix();
            if (snow::rotate_flg == 2) {
                sn_loop.flow_right();
            }
            if (snow::rotate_flg == 1) {
                sn_loop.flow_left();
            }
            glTranslatef(snow::snow_xpos[snow::l] - snow::xflow[snow::l], (ysize - snow::snow_ypos[snow::l]) - snow::down_count[snow::l], 0.0); // KOKO! (BUFFALO = -200)(CCD = 0)
            glColor3f(0.0, 0.0, 0.0);

            loop.draw();

            glFlush();
            glPopMatrix();
            if (((ysize - snow::snow_ypos[snow::l]) - snow::down_count[snow::l]) >= 0) { // KOKO! (BUFFALO = -200)(CCD = 0)
                snow::down_count[snow::l] = snow::down_count[snow::l] + 3 - snow::snow_noise[snow::l]; // KOKO! (BUFFALO = 20)(CCD = 3)
            }
            else if (((ysize - snow::snow_ypos[snow::l]) - snow::down_count[snow::l]) < 0) { // KOKO! (BUFFALO = -200)(CCD = 0)
                snow::down_count[snow::l] = 0;
                snow::snowxpos_flg[snow::l] = 0;
                snow::snow_ypos[snow::l] = 0;
                snow::xflow[snow::l] = 0;
                snow::snow_noise[snow::l] = 0;
            }
        }
    }
    
    glColor3f(1.0, 1.0, 1.0);
    // draw snow---------------------------------------------------------------------------------------------------
    
    /* detect the markers in the video frame */
    if( arDetectMarker(dataPtr, thresh, &marker_info, &marker_num) < 0 ) {
        cleanup();
        exit(0);
    }
    
    arVideoCapNext();
    
    /* check for object visibility */
    k = -1;
    for( j = 0; j < marker_num; j++ ) {
        if( patt_id == marker_info[j].id ) {
            if( k == -1 ) k = j;
            else if( marker_info[k].cf < marker_info[j].cf ) k = j;
        }
    }
    if( k == -1 ) {
        //        swFlag = -swFlag;
        test_count = 0;
        test_flag = 0;
        do_count = 0;
        ground::gr_count = 0;
        ground::gr_flg = 0;
        ground::groot_count = 0;
        for (snow::l = 0; snow::l < SNOW; snow::l++) {
            snow::snowxpos_flg[snow::l] = 0;
            snow::snowypos_flg[snow::l] = 0;
            snow::down_count[snow::l] = 0;
            snow::xflow[snow::l] = 0;
        }
        snow::cosx_minus = 1.0;
        snow::cosx_plus = 1.0;
        snow::rotate_flg = 0;
        mark_11 = 0;
        mark_31 = 0;
        ground::draw_flg  = 0;
        argSwapBuffers();
        return;
    }
    
    /* get the transformation between the marker and the real camera */
    arGetTransMat(&marker_info[k], patt_center, patt_width, patt_trans);
    
    if ((marker_info[k].vertex[0][0] - marker_info[k].vertex[3][0] > -10 && marker_info[k].vertex[0][0] - marker_info[k].vertex[3][0] < 10) || (marker_info[k].vertex[2][0] - marker_info[k].vertex[3][0] > -10 && marker_info[k].vertex[2][0] - marker_info[k].vertex[3][0] < 10)) {
        mark_11 = marker_info[k].vertex[1][1];
        mark_31 = marker_info[k].vertex[3][1];
    }
    
    printf("%5.2f %5.2f %5.2f\n", patt_trans[0][3], patt_trans[1][3], patt_trans[2][3]);
    //    printf("\n");
    printf("%5.2f %5.2f %5.2f\n", pre_patt_trans[0], pre_patt_trans[1], pre_patt_trans[2]);
    printf("\n");
    
    ground::mak_posx = marker_info[k].pos[0];
    ground::mak_posy = marker_info[k].pos[1];
    
    // hikaku sena...
    if (do_count > 0 && test_count < 15) {  // KOKO! (BUFFALO = 15)(CCD = 50)
        if ((0 <= (patt_trans[0][3] - pre_patt_trans[0]) && (patt_trans[0][3] - pre_patt_trans[0]) < 3) || (0 >= (patt_trans[0][3] - pre_patt_trans[0]) && (patt_trans[0][3] - pre_patt_trans[0]) > -3)) {  // KOKO! (BUFFALO = 3)(CCD = 0.5)
            // only 1 jikan start
            // now - start > 3 de tree
            test_count++;
            printf("%f\n", patt_trans[0][3] - pre_patt_trans[0]);
            printf("%d\n", test_count);
            printf("\n");
        }
        else{
            // now =
            test_count = 0;
            test_flag = 0;
            printf("%f\n", patt_trans[0][3] - pre_patt_trans[0]);
            printf("%d\n", test_count);
            printf("\n");
        }
    }
    if (test_count >= 15) { // KOKO! (BUFFALO = 15)(CCD = 50)
        test_flag = 1;
    }
    
    pre_patt_trans[0] = patt_trans[0][3];
    pre_patt_trans[1] = patt_trans[1][3];
    pre_patt_trans[2] = patt_trans[2][3];
    do_count++;
    
    
    // vertex = konoji kata
    printf("%f %f %f %f\n", marker_info[k].vertex[0][0], marker_info[k].vertex[0][1], marker_info[k].vertex[1][0], marker_info[k].vertex[1][1]);
    printf("%f %f %f %f\n", marker_info[k].vertex[2][0], marker_info[k].vertex[2][1], marker_info[k].vertex[3][0], marker_info[k].vertex[3][1]);
    printf("\n");
    // [0][0] = [3][0], [0][1] = [1][1], [1][0] = [2][0], [2][1] = [3][1]
    
    
    // left turn-----------------------------------------------
    if (marker_info[k].vertex[1][1] >= marker_info[k].vertex[3][1] && marker_info[k].vertex[0][0] >= marker_info[k].vertex[2][0]) {
        if (mark_11 >= mark_31) {
            ver_pos_l[0] = marker_info[k].vertex[1][0];
            ver_pos_l[1] = marker_info[k].vertex[0][1];
            //        printf("ver_pos = %f %f\n", ver_pos[0], ver_pos[1]);
            //        printf("\n");
            
            // far between 2 points ----------------------------------------------------------------
            // sa
            far_a1_l = marker_info[k].vertex[1][0] - marker_info[k].vertex[0][0];
            far_a2_l = marker_info[k].vertex[1][1] - marker_info[k].vertex[0][1];
            far_b1_l = ver_pos_l[0] - marker_info[k].vertex[0][0];
            far_b2_l = ver_pos_l[1] - marker_info[k].vertex[0][1];
            // 2 jou
            far_a1_2_l = far_a1_l * far_a1_l;
            far_a2_2_l = far_a2_l * far_a2_l;
            far_b1_2_l = far_b1_l * far_b1_l;
            far_b2_2_l = far_b2_l * far_b2_l;
            // bumbo
            far_mole_l = far_a1_l * far_b1_l;
            root_a_l = sqrt(far_a1_2_l + far_a2_2_l);
            root_b_l = sqrt(far_b1_2_l + far_b2_2_l);
            far_deno_l = root_a_l * root_b_l;
            // cos(theta)
            cosine = far_mole_l / far_deno_l;
            
            //        printf("root_a_l = %f\n", sqrt(far_a1_2_l +far_a2_2_l));
            //        printf("root_b_l = %f\n", sqrt(far_b1_2_l + far_b2_2_l));
            //        printf("far_mole_l = %f\n", far_mole_l);
            //        printf("far_deno_l = %f\n", far_deno_l);
            printf("cos_l = %f\n", cosine);
            //        printf("theta = %f\n", acos(far_mole_l / far_deno_l));
            printf("\n");
            
            snow::cosx_minus = cosine;
            snow::rotate_flg = 1;
        }
    }
    // left turn---------------------------------------------
    
    // right turn-----------------------------------------------
    if (marker_info[k].vertex[1][1] < marker_info[k].vertex[3][1] && marker_info[k].vertex[0][0] < marker_info[k].vertex[2][0]) {
        if (mark_11 < mark_31) {
            ver_pos_r[0] = marker_info[k].vertex[0][0];
            ver_pos_r[1] = marker_info[k].vertex[3][1];
            //        printf("ver_pos = %f %f\n", ver_pos[0], ver_pos[1]);
            //        printf("\n");
            
            // far between 2 points ----------------------------------------------------------------
            // sa
            far_a1_r = marker_info[k].vertex[0][0] - marker_info[k].vertex[3][0];
            far_a2_r = marker_info[k].vertex[0][1] - marker_info[k].vertex[3][1];
            far_b1_r = ver_pos_r[0] - marker_info[k].vertex[3][0];
            far_b2_r = ver_pos_r[1] - marker_info[k].vertex[3][1];
            // 2 jou
            far_a1_2_r = far_a1_r * far_a1_r;
            far_a2_2_r = far_a2_r * far_a2_r;
            far_b1_2_r = far_b1_r * far_b1_r;
            far_b2_2_r = far_b2_r * far_b2_r;
            // bunbo
            far_mole_r = far_a1_r * far_b1_r;
            root_a_r = sqrt(far_a1_2_r + far_a2_2_r);
            root_b_r = sqrt(far_b1_2_r + far_b2_2_r);
            far_deno_r = root_a_r * root_b_r;
            // cos(theta)
            cosine = far_mole_r / far_deno_r;
            
            //        printf("root_a_r = %f\n", sqrt(far_a1_2_r + far_a2_2_r));
            //        printf("root_b_r = %f\n", sqrt(far_b1_2_r + far_b2_2_r));
            //        printf("far_mole_r = %f\n", far_mole_r);
            //        printf("far_deno_r = %f\n", far_deno_r);
            printf("cos_r = %f\n", cosine);
            //        printf("theta = %f\n", acos(far_mole_r / far_deno_r));
            printf("\n");
            
            snow::cosx_plus = cosine;
            snow::rotate_flg = 2;
        }
    }
    // right turn---------------------------------------------
    
    draw(cosine);
    
    argSwapBuffers();
}

static void init( void )
{
    ARParam  wparam;
	
    /* open the video path */
    if( arVideoOpen( vconf ) < 0 ) exit(0);
    /* find the size of the window */
    if( arVideoInqSize(&xsize, &ysize) < 0 ) exit(0);
    printf("Image size (x,y) = (%d,%d)\n", xsize, ysize);
    
    /* set the initial camera parameters */
    if( arParamLoad(cparam_name, 1, &wparam) < 0 ) {
        printf("Camera parameter load error !!\n");
        exit(0);
    }
    arParamChangeSize( &wparam, xsize, ysize, &cparam );
    arInitCparam( &cparam );
    printf("*** Camera Parameter ***\n");
    arParamDisp( &cparam );
    
    if( (patt_id=arLoadPatt(patt_name)) < 0 ) {
        printf("pattern load error !!\n");
        exit(0);
    }
    
    /* open the graphics window */
    argInit( &cparam, 1.0, 0, 0, 0, 0 );
}

/* cleanup function called when program exits */
static void cleanup(void)
{
    arVideoCapStop();
    arVideoClose();
    argCleanup();
}

static void draw(double cosine/*int flg*/)
{
    fan draw_fan;
    circle draw_cir;
    root draw_root;
    
    double    gl_para[16];
    GLfloat   mat_ambient[]     = {1.1, 0.95, 0.95, 0.0};  // color of object
    GLfloat   mat_flash[]       = {0.0, 0.0, 1.0, 1.0};
    GLfloat   mat_flash_shiny[] = {50.0};
    //    GLfloat   light_position[]  = {100.0,-200.0,200.0,0.0};
    //    GLfloat   ambi[]            = {0.1, 0.1, 0.1, 0.1};
    //    GLfloat   lightZeroColor[]  = {0.9, 0.9, 0.9, 0.1};
    
    argDrawMode3D();
    argDraw3dCamera( 0, 0 );
    glClearDepth( 1.0 );
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    /* load the camera transformation matrix */
    argConvGlpara(patt_trans, gl_para);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd( gl_para );
    
    //    glEnable(GL_LIGHTING);
    //    glEnable(GL_LIGHT0);
    //    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //    glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
    //    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_flash);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_flash_shiny);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_TEXTURE_2D);
    
    glNormal3b(0.0, 0.0, 1.0);
    
    glPushMatrix();
    glTranslatef(0.0, -17.0, 0.0);
    
    // 15 count later
    if (test_flag > 0) {
        glColor3f(0.0, 0.0, 0.0);
        // stem
        glBegin(GL_QUADS);
        //        glColor3f(0.0, 0.0, 0.0);
        //    glTexCoord2d(0.0, 10.0);
        glVertex3d(-2.0, -10.0, 0.0);
        //    glTexCoord2d(10.0, 10.0);
        glVertex3d(2.0, -10.0, 0.0);
        //    glTexCoord2d(10.0, 0.0);
        glVertex3d(2.0, 10.0, 0.0);
        //    glTexCoord2d(0.0, 0.0);
        glVertex3d(-2.0, 10.0, 0.0);
        glEnd();
        glPopMatrix();
        
        // root-----------------------------------------
        if (ground::groot_count > 5) {
            draw_root.draw();
        }
        // root-----------------------------------------
        
        // circle
        glPushMatrix();
        glTranslatef(0.0, 20.0, 0.0);
        
        draw_cir.draw();

        glTranslatef(10.0, -20.0, 0.0);
        draw_cir.draw();

        glTranslatef(-20.0, 0.0, 0.0);
        draw_cir.draw();

        glPopMatrix();
        
        glFlush();
    }
    
    // initial
    if (test_flag == 0) {
        draw_fan.draw();
    }
    
    glDisable(GL_TEXTURE_2D);
    
    //    glDisable( GL_LIGHTING );
    
    glDisable( GL_DEPTH_TEST );
}

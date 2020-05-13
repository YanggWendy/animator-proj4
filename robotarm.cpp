// The sample robotarm model.  You should build a file
// very similar to this for when you make your model.
#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning(disable : 4786)

#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "particleSystem.h"


#include <FL/gl.h>
#include <stdlib.h>

#define M_DEFAULT 2.0f
#define M_OFFSET 3.0f
#define P_OFFSET 0.3f
#define MAX_VEL 200
#define MIN_STEP 0.1




// This is a list of the controls for the RobotArm
// We'll use these constants to access the values 
// of the controls from the user interface.
enum BirdControls
{ 
	XPOS, YPOS, ZPOS, HEADYPOS, HEADZPOS, MOUTHZPOS, NECK_LENTH, UPPER_RIGHT_LEG,
	UPPER_LEFT_LEG, LOWER_RIGHT_LEG, LOWER_LEFT_LEG, LEFT_TOES, RIGHT_TOES, RIGHT_WING,
	LEFT_WING, TAIL, DEFAULT_LIGHT_R, DEFAULT_LIGHT_G, DEFAULT_LIGHT_B, BODY_R, BODY_G, BODY_B,
    MOUTH_R, MOUTH_G, MOUTH_B, LEG_R, LEG_G, LEG_B, EYEBROW_R, EYEBROW_G, EYEBROW_B, PARTICLE_COUNT, NUMCONTROLS,
};

void draw_Head();
void draw_UpperMouth();
void draw_LowerMouth();
void draw_left_wings();
void draw_right_wings();
void draw_body();
void draw_tail();
void draw_connection();
void draw_rightupperLeg();
void draw_leftlowerLeg();
void draw_leftupperLeg();
void draw_rightlowerLeg();
void draw_righttoes();
void draw_lefttoes();
void draw_flower();
void draw_righteyebrow();
void draw_lefteyebrow();
void draw_level0();

// To make a RobotArm, we inherit off of ModelerView
class Bird : public ModelerView
{
public:
	Bird(int x, int y, int w, int h, char *label)
        : ModelerView(x,y,w,h,label) {}
    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createBird(int x, int y, int w, int h, char *label)
{ 
    return new Bird(x,y,w,h,label);
}

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))





// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out RobotArm
void Bird::draw()
{
	/* pick up the slider values */

	
	float pc = VAL( PARTICLE_COUNT );


    // This call takes care of a lot of the nasty projection 
    // matrix stuff
    ModelerView::draw();

	static GLfloat lmodel_ambient[] = {0.4,0.4,0.4,1.0};

	// define the model


    glPopMatrix();

    // draw the floor
    float R = VAL(DEFAULT_LIGHT_R) / 255;
    float G = VAL(DEFAULT_LIGHT_G) / 255;
    float B = VAL(DEFAULT_LIGHT_B) / 255;

    setAmbientColor(R, G, B);
    setDiffuseColor(0.42, 0.56, 0.14);
    glPushMatrix();
    glTranslated(-7.5, 0, -7.5);
    drawBox(15, 0.1f, 15);
    glPopMatrix();

    draw_level0();
    glPopMatrix();
	//*** DON'T FORGET TO PUT THIS IN YOUR OWN CODE **/
	endDraw();
}



int main()
{
    ModelerControl controls[NUMCONTROLS ];


	controls[XPOS] = ModelerControl("Move X", -5, 5, 1, 0);
	controls[YPOS] = ModelerControl("Move Y", 0, 5, 1, 0);
	controls[ZPOS] = ModelerControl("Move Z", -5, 5, 1, 0);

	controls[HEADYPOS] = ModelerControl("Head Y Rotate", -20, 20, 1, 0);
	controls[HEADZPOS] = ModelerControl("Head X Rotate", -20, 20, 1, 0);
	controls[MOUTHZPOS] = ModelerControl("Mouth Rotate", 0, 40, 1, 0);
	controls[NECK_LENTH] = ModelerControl("Neck Length", 1, 1.6, 0.1f, 1);

	controls[UPPER_RIGHT_LEG] = ModelerControl("upper right leg", -20, 20, 1, 0);
	controls[UPPER_LEFT_LEG] = ModelerControl("upper left leg", -20, 20, 1, 0);
	controls[LOWER_RIGHT_LEG] = ModelerControl("lower right leg", -20, 20, 1, 0);
	controls[LOWER_LEFT_LEG] = ModelerControl("lower left leg", -20, 20, 1, 0);
	controls[LEFT_TOES] = ModelerControl("left toes", -20, 20, 1, 0);
	controls[RIGHT_TOES] = ModelerControl("right toes", -20, 20, 1, 0);

	controls[RIGHT_WING] = ModelerControl("right wing", -20, 20, 1, 0);
	controls[LEFT_WING] = ModelerControl("left wing", -20, 20, 1, 0);

	controls[TAIL] = ModelerControl("tail", -20, 20, 1, 0);

    controls[DEFAULT_LIGHT_R] = ModelerControl("Default Light R", 0, 255, 1, 25.5);
    controls[DEFAULT_LIGHT_G] = ModelerControl("Default Light G", 0, 255, 1, 25.5);
    controls[DEFAULT_LIGHT_B] = ModelerControl("Default Light B", 0, 255, 1, 25.5);

    //1, 0.5, 0
    controls[BODY_R] = ModelerControl("Body R", 0, 1, 0.01, 1);
    controls[BODY_G] = ModelerControl("Body G", 0, 1, 0.01, 0.5);
    controls[BODY_B] = ModelerControl("Body B", 0, 1, 0.01, 0);

    //0.33, 0.55, 0.33
    controls[MOUTH_R] = ModelerControl("Mouth R", 0, 1, 0.01, 0.33);
    controls[MOUTH_G] = ModelerControl("Mouth G", 0, 1, 0.01, 0.55);
    controls[MOUTH_B] = ModelerControl("Mouth B", 0, 1, 0.01, 0.33);

    //0.56, 0.11, 0
    controls[LEG_R] = ModelerControl("Leg R", 0, 1, 0.01, 0.56);
    controls[LEG_G] = ModelerControl("Leg G", 0, 1, 0.01, 0.11);
    controls[LEG_B] = ModelerControl("Leg B", 0, 1, 0.01, 0.0);

    controls[EYEBROW_R] = ModelerControl("Eyebrows R", 0, 1, 0.01, 0.55);
    controls[EYEBROW_G] = ModelerControl("Eyebrows G", 0, 1, 0.01, 0.27);
    controls[EYEBROW_B] = ModelerControl("Eyebrows B", 0, 1, 0.01, 0.07);

    controls[PARTICLE_COUNT] = ModelerControl("particle count (pc)", 0.0, 5.0, 0.1, 5.0 );
    


	// You should create a ParticleSystem object ps here and then
	// call ModelerApplication::Instance()->SetParticleSystem(ps)
	// to hook it up to the animator interface.

    ModelerApplication::Instance()->Init(&createBird, controls, NUMCONTROLS);

    return ModelerApplication::Instance()->Run();
}



void draw_Head()
{

    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glScaled(1.5, 1.2, 1.2);
    //draw head
    drawSphere(1);

    //draw eyes
    setDiffuseColor(0.93, 0.91, 0.84);
    glTranslated(0, 0, 0.45);
    drawSphere(0.6);
    glTranslated(0, 0, -0.9);
    drawSphere(0.6);
    setDiffuseColor(0.11, 0.11, 0.11);

    glTranslated(0.14, 0, -0.45);
    drawSphere(0.2);

    glPushMatrix();
    glTranslated(0, 0.45, 0);
    draw_lefteyebrow();
    glPopMatrix();

    setDiffuseColor(0.11, 0.11, 0.11);
    glTranslated(0, 0, 1.8);
    drawSphere(0.2);

    glTranslated(0, 0.45, 0);
    draw_righteyebrow();


    glPopMatrix();


}

void draw_UpperMouth()
{
    glPushMatrix();
    setDiffuseColor(VAL(MOUTH_R), VAL(MOUTH_G), VAL(MOUTH_B));
    glScaled(1, 1, 2);
    drawTriangle(0, 0.3, -0.1, 0, 0.3, 0.1, 1.9, 0, 0);
    drawTriangle(0, 0.3, -0.1, 0, 0.2, -0.2, 1.9, 0, 0);
    drawTriangle(0, 0.3, 0.1, 0, 0.2, 0.2, 1.9, 0, 0);

    drawTriangle(0, 0.2, -0.2, 0, 0, -0.3, 1.9, 0, 0);
    drawTriangle(0, 0.2, 0.2, 0, 0, 0.3, 1.9, 0, 0);

    drawTriangle(0, 0.3, -0.1, 0, 0.3, 0.1, 0, 0, 0);
    drawTriangle(0, 0.3, -0.1, 0, 0.2, -0.2, 0, 0, 0);
    drawTriangle(0, 0.3, 0.1, 0, 0.2, 0.2, 0, 0, 0);

    drawTriangle(0, 0.2, -0.2, 0, 0, -0.3, 0, 0, 0);
    drawTriangle(0, 0.2, 0.2, 0, 0, 0.3, 0, 0, 0);
    glPopMatrix();
}

void draw_LowerMouth()
{
    glPushMatrix();
    setDiffuseColor(VAL(MOUTH_R), VAL(MOUTH_G), VAL(MOUTH_B));
    glScaled(1, 1, 2);
    drawTriangle(0, -0.3, -0.1, 0, -0.3, 0.1, 1.9, 0, 0);
    drawTriangle(0, -0.3, -0.1, 0, -0.2, -0.2, 1.9, 0, 0);
    drawTriangle(0, -0.3, 0.1, 0, -0.2, 0.2, 1.9, 0, 0);

    drawTriangle(0, -0.2, -0.2, 0, 0, -0.3, 1.9, 0, 0);
    drawTriangle(0, -0.2, 0.2, 0, 0, 0.3, 1.9, 0, 0);

    drawTriangle(0, -0.3, -0.1, 0, -0.3, 0.1, 0, 0, 0);
    drawTriangle(0, -0.3, -0.1, 0, -0.2, -0.2, 0, 0, 0);
    drawTriangle(0, -0.3, 0.1, 0, -0.2, 0.2, 0, 0, 0);

    drawTriangle(0, -0.2, -0.2, 0, 0, -0.3, 0, 0, 0);
    drawTriangle(0, -0.2, 0.2, 0, 0, 0.3, 0, 0, 0);
    glPopMatrix();
}




void draw_left_wings()
{
    //left wing
    //first y-axis feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glTranslated(3, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 3, 3);
    glPopMatrix();

    //second feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(10, 0, 1, 0);
    glTranslated(2.8, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2.8, 2.8);
    glPopMatrix();

    //third feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(20, 0, 1, 0);
    glTranslated(2.6, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2.6, 2.6);
    glPopMatrix();

    //4th feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(30, 0, 1, 0);
    glTranslated(2.4, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2.4, 2.4);
    glPopMatrix();

    //5th feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(40, 0, 1, 0);
    glTranslated(2.2, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2.2, 2.2);
    glPopMatrix();

    //6th feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(50, 0, 1, 0);
    glTranslated(2, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2, 2);
    glPopMatrix();


}

void draw_right_wings()
{
    //right wing
    //first y-axis feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glTranslated(-3, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 3, 3);
    glPopMatrix();

    //2nd feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(-10, 0, 1, 0);
    glTranslated(-2.8, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2.8, 2.8);
    glPopMatrix();

    //3rd feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(-20, 0, 1, 0);
    glTranslated(-2.6, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2.6, 2.6);
    glPopMatrix();

    //4th feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(-30, 0, 1, 0);
    glTranslated(-2.4, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2.4, 2.4);
    glPopMatrix();

    //5th feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(-40, 0, 1, 0);
    glTranslated(-2.2, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2.2, 2.2);
    glPopMatrix();

    //6th feather
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(-50, 0, 1, 0);
    glTranslated(-2, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.2, 2, 2);
    glPopMatrix();

}

void draw_body()
{
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(-20, 1, 0, 0);
    glScaled(1, 1, 1.2);
    drawSphere(2);
    glPopMatrix();
}


void draw_leftupperLeg()
{
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    drawCylinder(1.4, 0.2, 0.5);
    glPopMatrix();
}

void draw_rightupperLeg()
{
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    drawCylinder(1.4, 0.2, 0.5);
    glPopMatrix();
}


void draw_leftlowerLeg()
{
    glPushMatrix();
    setDiffuseColor(VAL(LEG_R), VAL(LEG_G), VAL(LEG_B));
    drawCylinder(1.3, 0.15, 0.1);
    glPopMatrix();
}

void draw_rightlowerLeg()
{
    glPushMatrix();
    setDiffuseColor(VAL(LEG_R), VAL(LEG_G), VAL(LEG_B));
    drawCylinder(1.3, 0.15, 0.1);
    glPopMatrix();
}

void draw_righttoes()
{
    glPushMatrix();
    glRotated(20 - VAL(RIGHT_TOES), 0, 1, 0);
    drawCylinder(0.9, 0.1, 0.08);
    glRotated(30, 0, 1, 0);
    drawCylinder(0.9, 0.1, 0.08);
    glRotated(30, 0, 1, 0);
    drawCylinder(0.9, 0.1, 0.08);
    glRotated(30, 0, 1, 0);
    drawCylinder(0.9, 0.1, 0.08);
    glRotated(110, 0, 1, 0);
    drawCylinder(0.5, 0.1, 0.08);

    glPopMatrix();
}

void draw_lefttoes()
{
    glPushMatrix();
    glRotated(20 - VAL(LEFT_TOES), 0, 1, 0);
    drawCylinder(0.9, 0.1, 0.08);
    glRotated(30, 0, 1, 0);
    drawCylinder(0.9, 0.1, 0.08);
    glRotated(30, 0, 1, 0);
    drawCylinder(0.9, 0.1, 0.08);
    glRotated(30, 0, 1, 0);
    drawCylinder(0.9, 0.1, 0.08);
    glRotated(110, 0, 1, 0);
    drawCylinder(0.5, 0.1, 0.08);

    glPopMatrix();
}

void draw_tail()
{
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(90 + 7, 0, 1, 0);
    glTranslated(1, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.3, 1, 1);
    glPopMatrix();

    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(90 + 20, 0, 1, 0);
    glTranslated(0.8, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.3, 0.8, 0.8);
    glPopMatrix();

    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(90 - 7, 0, 1, 0);
    glTranslated(1, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.3, 1, 1);
    glPopMatrix();

    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glRotated(90 - 20, 0, 1, 0);
    glTranslated(0.8, 0.2, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.2, 1);
    drawCylinder(0.3, 0.8, 0.8);
    glPopMatrix();
}

void draw_connection()
{
    glPushMatrix();
    glRotated(-20, 1, 0, 0);
    glTranslated(0, 0, -1.6);
    glRotated(180, 1, 0, 0);
    drawCylinder(1, 1.5, 1.1);
    glPopMatrix();

    glPushMatrix();
    glRotated(-20, 1, 0, 0);
    glTranslated(0, 0, -1.6 - 1);
    glRotated(180, 1, 0, 0);
    drawCylinder(1, 1.1, 0.6);
    glPopMatrix();

    glPushMatrix();
    glRotated(-20, 1, 0, 0);
    glTranslated(0, 0, -1.6 - 2);
    glRotated(180, 1, 0, 0);
    drawCylinder(1, 0.6, 0.2);
    glPopMatrix();
}


void draw_righteyebrow()
{
    glPushMatrix();
    setDiffuseColor(VAL(EYEBROW_R), VAL(EYEBROW_G), VAL(EYEBROW_B));
    glScaled(3, 1, 1);
    drawSphere(0.1);
    glPopMatrix();
}

void draw_lefteyebrow()
{
    glPushMatrix();
    setDiffuseColor(VAL(EYEBROW_R), VAL(EYEBROW_G), VAL(EYEBROW_B));
    glScaled(3, 1, 1);
    drawSphere(0.1);
    glPopMatrix();
}

void draw_constrain()
{


    //Neck part
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glTranslated(0, 1.5, 0.6);
    glRotated(-70, 1.0, 0.0, 0.0);
    drawCylinder(VAL(NECK_LENTH), 0.7, 0.5);
    glPopMatrix();

    //head
    glPushMatrix();
    glTranslated(0, 2.8, 1.2);
    glTranslated(0, VAL(NECK_LENTH) - 1, 0.2 * VAL(NECK_LENTH));
    glRotated(-90, 0.0, 1.0, 0.0);
    glRotated(VAL(HEADYPOS), 0.0, 1.0, 0.0);
    glRotated(VAL(HEADZPOS), 0.0, 0.0, 1.0);
    draw_Head();

    glTranslated(1.35, 0, 0);
    //upper mouth
    glPushMatrix();
    glRotated(VAL(MOUTHZPOS), 0, 0, 1);
    draw_UpperMouth();
    glPopMatrix();

    //lower mouth
    glPushMatrix();
    glRotated(-VAL(MOUTHZPOS), 0, 0, 1);
    draw_LowerMouth();
    glPopMatrix();

    glPopMatrix();


    //left wing
    glPushMatrix();
    glTranslated(1.5, 0, 0);
    glRotated(VAL(LEFT_WING), 0.0, 0.0, 1);
    draw_left_wings();
    glPopMatrix();

    //right wing
    glPushMatrix();
    glTranslated(-1.5, 0, 0);
    glRotated(VAL(RIGHT_WING), 0.0, 0.0, 1);
    draw_right_wings();
    glPopMatrix();

    //body
    glPushMatrix();
    draw_body();
    glPopMatrix();

    //connection
    glPushMatrix();
    draw_connection();
    glPopMatrix();

    //tail
    glPushMatrix();
    glRotated(-20, 1, 0, 0);
    glTranslated(0, 0, -4.5);
    drawSphere(0.2);
    glRotated(VAL(TAIL), 1.0, 0.0, 0);
    draw_tail();
    glPopMatrix();


    //rightupper leg
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glTranslated(0.9, -1.7, -0.3);
    glRotated(VAL(UPPER_RIGHT_LEG), 1.0, 0.0, 0);
    drawSphere(0.55);
    glTranslated(0, -1.5, -0.5);
    glRotated(-70, 1.0, 0.0, 0.0);
    drawSphere(0.2);
    draw_rightupperLeg();
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(VAL(LOWER_RIGHT_LEG), 1.0, 0.0, 0);
    draw_rightlowerLeg();
    glTranslated(0, -0.1, 1.1);
    glRotated(-20, 1.0, 0.0, 0.0);
    glRotated(-40, 0.0, 1.0, 0.0);
    drawSphere(0.1);
    draw_righttoes();
    glPopMatrix();

    //lefttupper leg
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glTranslated(-0.9, -1.7, -0.3);
    glRotated(VAL(UPPER_LEFT_LEG), 1.0, 0.0, 0);
    drawSphere(0.55);
    glTranslated(0, -1.5, -0.5);
    glRotated(-70, 1.0, 0.0, 0.0);
    draw_leftupperLeg();
    drawSphere(0.2);
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(VAL(LOWER_LEFT_LEG), 1.0, 0.0, 0.0);
    draw_leftlowerLeg();
    glTranslated(0, -0.1, 1.1);
    glRotated(-20, 1.0, 0.0, 0.0);
    glRotated(-40, 0.0, 1.0, 0.0);
    drawSphere(0.1);
    draw_lefttoes();
    glPopMatrix();


}

void draw_flower()
{

    glPushMatrix();
    setDiffuseColor(0, 0.55, 0.27);
    glScaled(8, 5, 5);
    drawTriangle(0, 0.2, 0.2, 0.1, 0.25, 0, 0, 0, 0);
    drawTriangle(0, 0.3, 0, 0.1, 0.25, 0, 0, 0, 0);
    drawTriangle(0, 0.3, 0, 0, 0.2, 0.2, 0, 0, 0);
    drawTriangle(0, 0.2, 0.2, 0.1, 0.25, 0, 0.3, 0.3, -0.3);
    drawTriangle(0, 0.3, 0, 0.1, 0.25, 0, 0.3, 0.3, -0.3);
    drawTriangle(0, 0.3, 0, 0, 0.2, 0.2, 0.3, 0.3, -0.3);
    glPopMatrix();

    glPushMatrix();
    setDiffuseColor(0, 0.55, 0.27);
    glTranslated(-0.6, 0, 0.3);
    glRotated(60, 0, 1, 0);
    glScaled(5, 2, 3);
    drawTriangle(0, 0.2, 0.2, 0.1, 0.25, 0, 0, 0, 0);
    drawTriangle(0, 0.3, 0, 0.1, 0.25, 0, 0, 0, 0);
    drawTriangle(0, 0.3, 0, 0, 0.2, 0.2, 0, 0, 0);
    drawTriangle(0, 0.2, 0.2, 0.1, 0.25, 0, 0.3, 0.5, -0.3);
    drawTriangle(0, 0.3, 0, 0.1, 0.25, 0, 0.3, 0.5, -0.3);
    drawTriangle(0, 0.3, 0, 0, 0.2, 0.2, 0.3, 0.5, -0.3);
    glPopMatrix();

    glPushMatrix();
    setDiffuseColor(0.8, 0.2, 0.2);
    glTranslated(0, 1, 0);
    glScaled(5, 5, 5);
    drawTriangle(0, 0.2, 0.2, 0.2, 0.2, 0, 0, 0, 0);
    drawTriangle(-0.1, 0.2, -0.1, 0.2, 0.2, 0, 0, 0, 0);
    drawTriangle(-0.1, 0.2, -0.1, 0, 0.2, 0.2, 0, 0, 0);
    drawTriangle(0, 0.2, 0.2, 0.2, 0.2, 0, 0, 0.6, 0);
    drawTriangle(-0.1, 0.2, -0.1, 0.2, 0.2, 0, 0, 0.6, 0);
    drawTriangle(-0.1, 0.2, -0.1, 0, 0.2, 0.2, 0, 0.6, 0);
    glPopMatrix();
}

void draw_level0()
{
    //draw flawor
    glPushMatrix();
    glTranslated(-3, 0, 4);
    draw_flower();
    glPopMatrix();

    glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
    glTranslated(0, 3.9, 0);

    //Neck part
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glTranslated(0, 1.5, 0.6);
    glRotated(-70, 1.0, 0.0, 0.0);
    drawCylinder(VAL(NECK_LENTH), 0.7, 0.5);
    glPopMatrix();

    //head
    glPushMatrix();
    glTranslated(0, 2.8, 1.2);
    glTranslated(0, VAL(NECK_LENTH) - 1, 0.2 * VAL(NECK_LENTH));
    glRotated(-90, 0.0, 1.0, 0.0);
    glRotated(VAL(HEADYPOS), 0.0, 1.0, 0.0);
    glRotated(VAL(HEADZPOS), 0.0, 0.0, 1.0);
    draw_Head();

    glTranslated(1.35, 0, 0);
    //upper mouth
    glPushMatrix();
    glRotated(VAL(MOUTHZPOS), 0, 0, 1);
    draw_UpperMouth();
    glPopMatrix();

    //lower mouth
    glPushMatrix();
    glRotated(-VAL(MOUTHZPOS), 0, 0, 1);
    draw_LowerMouth();
    glPopMatrix();

    glPopMatrix();


    //left wing
    glPushMatrix();
    glTranslated(1.5, 0, 0);
    glRotated(VAL(LEFT_WING), 0.0, 0.0, 1);
    draw_left_wings();
    glPopMatrix();

    //right wing
    glPushMatrix();
    glTranslated(-1.5, 0, 0);
    glRotated(VAL(RIGHT_WING), 0.0, 0.0, 1);
    draw_right_wings();
    glPopMatrix();

    //body
    glPushMatrix();
    draw_body();
    glPopMatrix();

    //connection
    glPushMatrix();
    draw_connection();
    glPopMatrix();

    //tail
    glPushMatrix();
    glRotated(-20, 1, 0, 0);
    glTranslated(0, 0, -4.5);
    drawSphere(0.2);
    glRotated(VAL(TAIL), 1.0, 0.0, 0);
    draw_tail();
    glPopMatrix();


    //rightupper leg
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glTranslated(0.9, -1.7, -0.3);
    glRotated(VAL(UPPER_RIGHT_LEG), 1.0, 0.0, 0);
    drawSphere(0.55);
    glTranslated(0, -1.5, -0.5);
    glRotated(-70, 1.0, 0.0, 0.0);
    drawSphere(0.2);
    draw_rightupperLeg();
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(VAL(LOWER_RIGHT_LEG), 1.0, 0.0, 0);
    draw_rightlowerLeg();
    glTranslated(0, -0.1, 1.1);
    glRotated(-20, 1.0, 0.0, 0.0);
    glRotated(-40, 0.0, 1.0, 0.0);
    drawSphere(0.1);
    draw_righttoes();
    glPopMatrix();

    //lefttupper leg
    glPushMatrix();
    setDiffuseColor(VAL(BODY_R), VAL(BODY_G), VAL(BODY_B));
    glTranslated(-0.9, -1.7, -0.3);
    glRotated(VAL(UPPER_LEFT_LEG), 1.0, 0.0, 0);
    drawSphere(0.55);
    glTranslated(0, -1.5, -0.5);
    glRotated(-70, 1.0, 0.0, 0.0);
    draw_leftupperLeg();
    drawSphere(0.2);
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(VAL(LOWER_LEFT_LEG), 1.0, 0.0, 0.0);
    draw_leftlowerLeg();
    glTranslated(0, -0.1, 1.1);
    glRotated(-20, 1.0, 0.0, 0.0);
    glRotated(-40, 0.0, 1.0, 0.0);
    drawSphere(0.1);
    draw_lefttoes();
    glPopMatrix();
}
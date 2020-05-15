#include "modelerview.h"
#include "camera.h"
#include "bitmap.h"
#include "modelerapp.h"
#include "particleSystem.h"

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.h>
#include <FL/gl.h>
#include <GL/glu.h>
#include <cstdio>

static const int	kMouseRotationButton = FL_LEFT_MOUSE;
static const int	kMouseTranslationButton = FL_MIDDLE_MOUSE;
static const int	kMouseZoomButton = FL_RIGHT_MOUSE;

static const char* bmp_name = NULL;

ModelerView::ModelerView(int x, int y, int w, int h, char* label)
	: Fl_Gl_Window(x, y, w, h, label), t(0), save_bmp(false)
{
	m_ctrl_camera = new Camera();
	m_curve_camera = new Camera();
	camera(CURVE_MODE);
}

ModelerView::~ModelerView()
{
	delete m_ctrl_camera;
	delete m_curve_camera;
}
int ModelerView::handle(int event)
{
	unsigned eventCoordX = Fl::event_x();
	unsigned eventCoordY = Fl::event_y();
	unsigned eventButton = Fl::event_button();
	unsigned eventState = Fl::event_state();

	switch (event)
	{
	case FL_PUSH:
	{
		switch (eventButton)
		{
		case kMouseRotationButton:
			if (!Fl::event_state(FL_ALT)) {
				m_camera->clickMouse(kActionRotate, eventCoordX, eventCoordY);
				break;
			} // ALT + LEFT = MIDDLE
		case kMouseTranslationButton:
			m_camera->clickMouse(kActionTranslate, eventCoordX, eventCoordY);
			break;
		case kMouseZoomButton:
			m_camera->clickMouse(kActionZoom, eventCoordX, eventCoordY);
			break;
		}
		// printf("push %d %d\n", eventCoordX, eventCoordY);
	}
	break;
	case FL_DRAG:
	{
		m_camera->dragMouse(eventCoordX, eventCoordY);
		//printf("drag %d %d\n", eventCoordX, eventCoordY);
	}
	break;
	case FL_RELEASE:
	{
		switch (eventButton)
		{
		case kMouseRotationButton:
		case kMouseTranslationButton:
		case kMouseZoomButton:
			m_camera->releaseMouse(eventCoordX, eventCoordY);
			break;
		}
		//  printf("release %d %d\n", eventCoordX, eventCoordY);
	}
	break;
	default:
		return Fl_Gl_Window::handle(event);
	}

	redraw();

	return 1;
}

static GLfloat lightPosition0[] = { 4, 2, -4, 0 };
static GLfloat lightDiffuse0[] = { 1,1,1,1 };
static GLfloat lightPosition1[] = { -2, 1, 5, 0 };
static GLfloat lightDiffuse1[] = { 1, 1, 1, 1 };


void ModelerView::draw()
{
	if (!valid())
	{
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_NORMALIZE);
	}

	glViewport(0, 0, w(), h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, float(w()) / float(h()), 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_camera->applyViewingTransform();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);

	// If particle system exists, draw it
	ParticleSystem* ps = ModelerApplication::Instance()->GetParticleSystem();
	if (ps != NULL) {
		ps->computeForcesAndUpdateParticles(t);
		ps->drawParticles(t);
	}
}

Mat4f ModelerView::getCameraMatrix() {
	Vec3f eye = m_camera->mPosition;
	Vec3f at = m_camera->mLookAt;
	Vec3f up = m_camera->mUpVector;

	GLdouble temp[16];
	Vec3d forward(at[0] - eye[0], at[1] - eye[1], at[2] - eye[2]);
	forward.normalize();
	Vec3d upward(up[0], up[1], up[2]);
	upward.normalize();
	Vec3d x_axis(forward[1] * upward[2] - upward[1] * forward[2], forward[2] * upward[0] - upward[2] * forward[0], forward[0] * upward[1] - upward[0] * forward[1]);
	x_axis.normalize();

	upward[0] = x_axis[1] * forward[2] - forward[1] * x_axis[2];
	upward[1] = x_axis[2] * forward[0] - forward[2] * x_axis[0];
	upward[2] = x_axis[0] * forward[1] - forward[0] * x_axis[1];


	temp[0] = x_axis[0];
	temp[4] = x_axis[1];
	temp[8] = x_axis[2];
	temp[12] = 0;

	temp[1] = upward[0];
	temp[5] = upward[1];
	temp[9] = upward[2];
	temp[13] = 0;

	temp[2] = 0 - forward[0];
	temp[6] = 0 - forward[1];
	temp[10] = 0 - forward[2];
	temp[14] = 0;

	temp[3] = 0;
	temp[7] = 0;
	temp[11] = 0;
	temp[15] = 1;

	Mat4f m(x_axis[0], x_axis[1], x_axis[2], 0,
		upward[0], upward[1], upward[2], 0,
		temp[2], temp[6], temp[10], 0,
		0, 0, 0, 1
		);
	Mat4f trans(1, 0, 0, -eye[0],
		0, 1, 0, -eye[1],
		0, 0, 1, -eye[2],
		0, 0, 0, 1
		);
	return m * trans;
}


/** Set the active camera **/
void ModelerView::camera(cam_mode_t mode)
{
	switch (mode) {
	case CTRL_MODE:
		m_camera = m_ctrl_camera;
		break;
	case CURVE_MODE:
		m_camera = m_curve_camera;
		break;
	}
}


/** Cleanup fxn for saving bitmaps **/
void ModelerView::endDraw()
{
	if ((bmp_name == NULL) || (!save_bmp)) return;
	glFinish();
	saveBMP(bmp_name);
	save_bmp = false;
}


void ModelerView::setBMP(const char* fname)
{
	save_bmp = true;
	bmp_name = fname;
}

void ModelerView::saveBMP(const char* szFileName)
{
	int xx = x();
	int yy = y();
	int ww = w();
	int hh = h();

	make_current();

	unsigned char* imageBuffer = new unsigned char[3 * ww * hh];

	glReadBuffer(GL_BACK);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, ww);

	glReadPixels(0, 0, ww, hh,
		GL_RGB, GL_UNSIGNED_BYTE,
		imageBuffer);

	writeBMP(szFileName, ww, hh, imageBuffer);

	delete[] imageBuffer;
}


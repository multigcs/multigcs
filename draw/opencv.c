
#include <all.h>

#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>

static SDL_mutex *cv_mutex = NULL;
static SDL_Surface *cv_bg = NULL;
static SDL_Surface *cv_surface = NULL;
static CvCapture *cv_capture = NULL;
static SDL_Thread *cv_thread = NULL;
static uint8_t cv_running = 0;
static int cv_camid = 0;





#ifdef OPENCV_EFFECTS
static int b_squares;
static CvSize b_size;
static CvMat *warp_matrix = NULL;
static CvPoint2D32f corners[20];
static IplImage *gray = NULL;
static CvPoint p[4];

void cvar_init (void) {
	int b_width  = 5;
	int b_height = 4;

	b_squares = 20;
	b_size = cvSize(b_width, b_height);
	warp_matrix = cvCreateMat(3, 3, CV_32FC1);

}

void cvar_run (IplImage *image) {
	int corner_count = 0;
	if (gray == NULL) {
		gray = cvCreateImage(cvGetSize(image), image->depth, 1);
	}
	int found = cvFindChessboardCorners(image, b_size, corners, &corner_count, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
	cvCvtColor(image, gray, CV_BGR2GRAY);
	cvFindCornerSubPix(gray, corners, corner_count, cvSize(11, 11), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1));
	if (corner_count == b_squares) {
		p[0].x = (int)corners[0].x;
		p[0].y = (int)corners[0].y;
		p[1].x = (int)corners[4].x;
		p[1].y = (int)corners[4].y;
		p[2].x = (int)corners[19].x;
		p[2].y = (int)corners[19].y;
		p[3].x = (int)corners[15].x;
		p[3].y = (int)corners[15].y;
		cvLine(image, p[0], p[1], CV_RGB(255, 0, 0), 2, 8, 0);
		cvLine(image, p[1], p[2], CV_RGB(0, 255, 0), 2, 8, 0);
		cvLine(image, p[2], p[3], CV_RGB(0, 0, 255), 2, 8, 0);
		cvLine(image, p[3], p[0], CV_RGB(255, 255, 0), 2, 8, 0);

//		int n = 0;
//		for (n = 0; n < 20; n++) {
//			p[0].x = (int)corners[n].x;
//			p[0].y = (int)corners[n].y;
//			cvCircle(image, p[0], 2, CV_RGB(255, 0, 0), 1, 8, 0);
//		}

	}


/*
	CvPoint2D32f src_pnt[4];
	src_pnt[0] = cvPoint2D32f (p[0].x, p[0].y);
	src_pnt[1] = cvPoint2D32f (p[1].x, p[1].y);
	src_pnt[2] = cvPoint2D32f (p[2].x, p[2].y);
	src_pnt[3] = cvPoint2D32f (p[3].x, p[3].y);
	CvPoint2D32f dst_pnt[4];
	dst_pnt[0] = cvPoint2D32f (0.0, 0.0);
	dst_pnt[1] = cvPoint2D32f (image->width, 0.0);
	dst_pnt[2] = cvPoint2D32f (image->width, image->height);
	dst_pnt[3] = cvPoint2D32f (0.0, image->height);
	CvMat *mmat = cvCreateMat(3, 3, CV_32FC1);
	mmat = cvGetPerspectiveTransform(src_pnt, dst_pnt, mmat);
	IplImage *tmp_img = NULL;
	tmp_img = cvCloneImage(image);
	cvWarpPerspective(tmp_img, image, mmat, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll(0)); 
*/
}

void cvar_exit (void) {
	if (warp_matrix != NULL) {
		cvReleaseMat(&warp_matrix);
	}
	if (gray != NULL) {
		cvReleaseImage(&gray);
		gray = NULL;
	}
}
#endif

SDL_Surface *ipl_to_surface (IplImage *opencvimg) {
//	printf("## %i %i ##\n", opencvimg->width, opencvimg->height);
	SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void*)opencvimg->imageData,
		opencvimg->width,
		opencvimg->height,
		opencvimg->depth*opencvimg->nChannels,
		opencvimg->widthStep,
		0xff0000, 0x00ff00, 0x0000ff, 0
	);
	return surface;
}

int cv_update (void *data) {
	IplImage *opencvimg = NULL;
	if ((cv_capture = cvCaptureFromCAM(cv_camid)) == NULL) {
		SDL_Log("opencv: can not open capture device: %i\n", cv_camid);
		return 0;
	}
	SDL_Log("opencv: open capture device: %i\n", cv_camid);
#ifdef OSX
	SDL_Delay(2000);
#endif
	if ((opencvimg = cvQueryFrame(cv_capture)) != NULL) {
		cv_surface = SDL_CreateRGBSurfaceFrom((void*)opencvimg->imageData,
			opencvimg->width,
			opencvimg->height,
			opencvimg->depth*opencvimg->nChannels,
			opencvimg->widthStep,
			0xff0000, 0x00ff00, 0x0000ff, 0
		);
		cv_bg = SDL_CreateRGBSurfaceFrom((void*)opencvimg->imageData,
			opencvimg->width,
			opencvimg->height,
			opencvimg->depth*opencvimg->nChannels,
			opencvimg->widthStep,
			0xff0000, 0x00ff00, 0x0000ff, 0
		);
		if (cv_surface != NULL && cv_bg != NULL) {
			SDL_Log("opencv: running thread\n");
#ifdef OPENCV_EFFECTS
			cvar_init();
#endif
			while (cv_running == 1) {
				if ((opencvimg = cvQueryFrame(cv_capture)) != NULL) {
					SDL_LockMutex(cv_mutex);
#ifdef OPENCV_EFFECTS
					cvar_run(opencvimg);
#endif
					SDL_Surface *csf = ipl_to_surface(opencvimg);
					SDL_BlitSurface(csf, NULL, cv_bg, NULL);
					SDL_UnlockMutex(cv_mutex);
					SDL_FreeSurface(csf);
				}
				SDL_Delay(10);
			}
		} else {
			SDL_Log("opencv: can not create surfaces\n");
			openvc_exit();
		}
	} else {
		SDL_Log("opencv: can not query image\n");
		openvc_exit();
	}
	return 0;
}

void openvc_init (int cam_id) {
	SDL_Log("opencv: init\n");
	cv_camid = cam_id;
	cv_running = 1;
	cv_mutex = SDL_CreateMutex();
#ifdef SDL2
	cv_thread = SDL_CreateThread(cv_update, NULL, NULL);
#else
	cv_thread = SDL_CreateThread(cv_update, NULL);
#endif
}

void openvc_exit (void) {
	cv_running = 0;
	SDL_WaitThread(cv_thread, NULL);
	if (cv_bg != NULL) {
		SDL_FreeSurface(cv_bg);
		cv_bg = NULL;
	}
	if (cv_surface != NULL) {
		SDL_FreeSurface(cv_surface);
		cv_surface = NULL;
	}
	if (cv_capture != NULL) {
		cvReleaseCapture(&cv_capture);
	}
	if (cv_mutex != NULL) {
		SDL_DestroyMutex(cv_mutex);
		cv_mutex = NULL;
	}
#ifdef OPENCV_EFFECTS
	cvar_exit();
#endif

}

SDL_Surface *openvc_get (void) {
	SDL_LockMutex(cv_mutex);
	if (cv_bg != NULL) {
		SDL_BlitSurface(cv_bg, NULL, cv_surface, NULL);
		SDL_UnlockMutex(cv_mutex);
		return cv_surface;
	}
	SDL_UnlockMutex(cv_mutex);
	return NULL;
}




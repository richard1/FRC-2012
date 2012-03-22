#include "vision/BackboardFinder.h"
#include <math.h>
#include "WPILib.h"
#include "util/Logger.h"

BackboardFinder::BackboardFinder() : VisionProcess() {
  cameraLog_ = new Logger("/cameraLog.log");
  printf("Initting camera\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  hDiff_ = 0;
  vDiff_ = 0;
  //camera.WriteResolution(AxisCameraParams::kResolution_320x240);
}

double BackboardFinder::GetX() {
  if (-1.0 <= x_ && x_ <= 1.0) {
    return x_;
  } else {
    printf("Bad x val :( %f\n", x_);
    return 0;
  }
}

double BackboardFinder::GetHDiff() {
	return hDiff_;
}
double BackboardFinder::GetVDiff() {
	return vDiff_;
}

bool BackboardFinder::SeesTarget() {
  return HasFreshTarget() && seesTarget_;
}

void BackboardFinder::LogCamera() {
  cameraLog_->Log("%f,%f,%f\n", GetX(), hDiff_, vDiff_);
}

double BackboardFinder::GetAngle() {
	//normalized x location (-1 to 1) times the pixels along
	//that one side = number of pixels off
	//47/320 = degree/pixel based on fov/horizontal resolution
	//pixels * degrees / pixels = degrees
	//printf("get: %f\n", (float) GetX());
	return GetX() * 160.0 * 47.0 / 320.0;
}

void BackboardFinder::DoVision() {
  // Get image from camera
  AxisCamera &camera = AxisCamera::GetInstance("10.2.54.11");
  ColorImage img(IMAQ_IMAGE_RGB);
  if (!camera.GetImage(&img))
    return;
  //

  // RGB Threshold -> BinaryImage
  BinaryImage* bimg = img.ThresholdRGB(0,50,0,50,80,255);

  // take out small things
  Image* image = bimg->GetImaqImage();
  if (!image)
    return;
  int pKernel[9] = {1,1,1,1,1,1,1,1,1};
  StructuringElement structElem;
  structElem.matrixCols = 3;
  structElem.matrixRows = 3;
  structElem.hexa = FALSE;
  structElem.kernel = pKernel;

  // Filters particles based on their size.
  imaqSizeFilter(image, image, TRUE, 1, IMAQ_KEEP_LARGE, &structElem);

  // Convex Hull
  imaqConvexHull(image, image, true);

  // Convex Hull Perimeter, pParamter = perimeter Paramater
  int pParameter[1] = {20};
  double pLower[1] = {0};
  double pUpper[1] = {100};
  int pCalibrated[1] = {0};
  int pExclude[1] = {0};
  
  ParticleFilterCriteria2* pParticleCriteria = NULL;
  ParticleFilterOptions pParticleFilterOptions;
  int pNumParticles;
  
  /*
  pParticleCriteria = (ParticleFilterCriteria2*)malloc(sizeof(ParticleFilterCriteria2));
  pParticleCriteria[0].parameter = (MeasurementType)pParameter[0];
  pParticleCriteria[0].lower = pLower[0];
  pParticleCriteria[0].upper = pUpper[0];
  pParticleCriteria[0].calibrated = pCalibrated[0];
  pParticleCriteria[0].exclude = pExclude[0];

  pParticleFilterOptions.rejectMatches = TRUE;
  pParticleFilterOptions.rejectBorder = 0;
  pParticleFilterOptions.connectivity8 = TRUE;
  imaqParticleFilter3(image, image, pParticleCriteria, 1, &pParticleFilterOptions, NULL, &pNumParticles);
  free(pParticleCriteria);
  
  // Filter based on squarishness, eParamter = elongationParamter
  int eParameter =  53;
  double eLower = 1.2;
  double eUpper = 2.7;
  int eCalibrated = 0;
  int eExclude = 0;
  ParticleFilterCriteria2* eParticleCriteria = NULL;
  ParticleFilterOptions eParticleFilterOptions;
  int eNumParticles;
  eParticleCriteria = (ParticleFilterCriteria2*)malloc(sizeof(ParticleFilterCriteria2));

  eParticleCriteria[0].parameter = (MeasurementType) eParameter;
  eParticleCriteria[0].lower = eLower;
  eParticleCriteria[0].upper = eUpper;
  eParticleCriteria[0].calibrated = eCalibrated;
  eParticleCriteria[0].exclude = eExclude;

  eParticleFilterOptions.rejectMatches = FALSE;
  eParticleFilterOptions.rejectBorder = 0;
  eParticleFilterOptions.connectivity8 = TRUE;
  imaqParticleFilter3(image, image, eParticleCriteria, 1, &eParticleFilterOptions, NULL, &eNumParticles);
  free(eParticleCriteria);
  */
  
  // Extract Particles (4?)
  ParticleAnalysisReport left, right, top, bottom;
  vector<ParticleAnalysisReport>* particles = bimg->GetOrderedParticleAnalysisReports();

  // Find L,R,T,B based on CoM X,Y
  int i = 0;

  switch (particles->size()) {

  case 4:
    for (i = 0; i < particles->size(); i++) {
      ParticleAnalysisReport p = (*particles)[i];
      if (i == 0) {
        left = top = right = bottom = p;
      }
      if (p.center_mass_x_normalized < left.center_mass_x_normalized) {
        left = p;
      }
      if (p.center_mass_x_normalized > right.center_mass_x_normalized) {
        right = p;
      }
      if (p.center_mass_y_normalized < top.center_mass_y_normalized) {
        top = p;
      }
      if (p.center_mass_y_normalized > bottom.center_mass_y_normalized) {
        bottom = p;
      }
    }
    break;
#define X_DELTA .05
#define Y_DELTA .1
#define IN_LINE_X(a,b)  (fabs(a.center_mass_x_normalized  - b.center_mass_x_normalized) < X_DELTA)
#define IN_LINE_Y(a,b)  (fabs(a.center_mass_y_normalized  - b.center_mass_y_normalized) < Y_DELTA)
#define HIGHEST(a,b)    ((a.center_mass_y_normalized < b.center_mass_y_normalized) ? a : b)
  case 3: 
    // Two Horizontal or two vertical targets
    if (IN_LINE_Y(particles->at(0), particles->at(1))){
      //printf("case A\n");
      top = particles->at(2);
    } else if (IN_LINE_Y(particles->at(1), particles->at(2))) {
      //printf("case B\n");
      top = particles->at(0);
    } else if (IN_LINE_Y(particles->at(0), particles->at(2))){
      //printf("case C\n");
      top = particles->at(1);
    } else if (IN_LINE_X(particles->at(0), particles->at(1))){
      //printf("case D\n");
      top = HIGHEST(particles->at(0), particles->at(1));
    } else if (IN_LINE_X(particles->at(1), particles->at(2))){
      //printf("case E\n");
      top = HIGHEST(particles->at(1), particles->at(2));
    } else if (IN_LINE_X(particles->at(0), particles->at(2))){
      //printf("case F\n");
      top = HIGHEST(particles->at(0), particles->at(2));
    } else {
      // wtf, mate?
    }
    break;
  default:
    break;
  }
#undef X_DELTA
#undef Y_DELTA
#undef IN_LINE_X
#undef IN_LINE_Y

  // Calculate distance

  // Calculate x offset from target center
  seesTarget_ = (particles->size() == 3 || particles->size() == 4);
  x_ = seesTarget_ ? top.center_mass_x_normalized : 0.0;
  //printf("x_ : %f\n", (float) x_);

  //printf("CAMERA FAKFDSAJFADSOJG \n");
  // Calculate angle on fieled based on ?
  //printf("left %f, center %f, right %f\n", left.center_mass_x_normalized, top.center_mass_x_normalized, right.center_mass_x_normalized);
  hDiff_ = right.center_mass_x_normalized - left.center_mass_x_normalized;
  vDiff_ = fabs(top.center_mass_y_normalized - bottom.center_mass_y_normalized);
  //printf("Offset: %f, Horizontal Diff: %f, Vertical Diff: %f\n", top.center_mass_x_normalized, hDiff, vDiff);
  
  delete bimg;
  static double t = 0;
  double diff = Timer::GetFPGATimestamp() - t;
  t = Timer::GetFPGATimestamp();
  
  lastUpdate_ = t;
  
  static int counts = 0;
  counts++;
  if (counts % 10 == 0) {
    for (int i = 0; i < particles->size() ; i++) {
      printf("i: %d | x: %f | y: %f\n", i,  (float) particles->at(i).center_mass_x_normalized, (float) particles->at(i).center_mass_y_normalized); 
    }
    printf("\n\n");
  }

  double middleGap = right.boundingRect.left - (left.boundingRect.left + left.boundingRect.width);

}

bool BackboardFinder::HasFreshTarget() {
  return (Timer::GetFPGATimestamp() - lastUpdate_ < .5); // 500ms
}

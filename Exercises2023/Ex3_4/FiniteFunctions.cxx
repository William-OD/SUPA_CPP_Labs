#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way
#include <random>

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

//Empty constructors
FiniteFunction::FiniteFunction(){
  m_RMin = -10.0;
  m_RMax = 10.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}
NormalFunction::NormalFunction() : FiniteFunction() {
    m_stddev = 1.0;
    m_mean = 0.0;
    this->checkPath("NormalFunction");
}
CauchyLorentzFunction::CauchyLorentzFunction() : FiniteFunction() {
    m_x0 = 0.0;
    m_gamma = 1.0;
    this->checkPath("CauchyLorentzFunction");
}
NegativeCrystalBallFunction::NegativeCrystalBallFunction() : NormalFunction() {
    m_alpha = 1.0;
    m_n = 1.0;
    this->checkPath("NegativeCrystalBallFunction");
}

//initialised constructors
FiniteFunction::FiniteFunction(double min_range, double max_range, std::string outfile){
  m_RMin = min_range;
  m_RMax = max_range;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}
NormalFunction::NormalFunction(double min_range, double max_range, std::string outfile, double stddev, double mean)
    : FiniteFunction(min_range, max_range, outfile) {
    m_stddev = stddev;
    m_mean = mean;
}
CauchyLorentzFunction::CauchyLorentzFunction(double min_range, double max_range, std::string outfile, double gamma, double x0)
    : FiniteFunction(min_range, max_range, outfile) {
    m_x0 = x0;
    m_gamma = gamma;
}
NegativeCrystalBallFunction::NegativeCrystalBallFunction(double min_range, double max_range, std::string outfile, double alpha, double n, double stddev, double mean)
    : NormalFunction(min_range, max_range, outfile, stddev, mean) {
    m_alpha = alpha;
    m_n = n;
}


//Plots are called in the destructor
//SUPACPP note: They syntax of the plotting code is not part of the course
FiniteFunction::~FiniteFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

/*
###################
//Setters
###################
*/ 
void FiniteFunction::setRangeMin(double RMin) {m_RMin = RMin;};
void FiniteFunction::setRangeMax(double RMax) {m_RMax = RMax;};
void FiniteFunction::setOutfile(std::string Outfile) {this->checkPath(Outfile);};

void NormalFunction::setStdDev(double stddev) {m_stddev = stddev;};
void NormalFunction::setMean(double mean) {m_mean = mean;};

void CauchyLorentzFunction::setX0(double x0) {m_x0 = x0;};
void CauchyLorentzFunction::setGamma(double gamma) {m_gamma = gamma;};

void NegativeCrystalBallFunction::setAlpha(double alpha) {m_alpha = alpha;};
void NegativeCrystalBallFunction::setN(double n) {m_n = n;};

/*
###################
//Getters
###################
*/ 
double FiniteFunction::rangeMin() {return m_RMin;};
double FiniteFunction::rangeMax() {return m_RMax;};

double NormalFunction::getStdDev() {return m_stddev;};
double NormalFunction::getMean() {return m_mean;};

double CauchyLorentzFunction::getX0() {return m_x0;};
double CauchyLorentzFunction::getGamma() {return m_gamma;};

double NegativeCrystalBallFunction::getAlpha() {return m_alpha;};
double NegativeCrystalBallFunction::getN() {return m_n;};


/*
###################
//Function eval
###################
*/ 
double FiniteFunction::invxsquared(double x) {return 1/(1+x*x);};

// Normal distribution function
double NormalFunction::normalDistribution(double x) {
    if (m_stddev == 0.0) {
        // Handle the error, for example, throw an exception
        throw std::invalid_argument("For normal distribution, standard deviation must be non-zero");
    }
    return 1.0 / (m_stddev * sqrt(2 * M_PI)) * exp(-0.5 * pow((x - m_mean) / m_stddev, 2));
}

// Cauchy-Lorentz distribution function
double CauchyLorentzFunction::cauchylorentzDistribution(double x) {
    if (m_gamma <= 0.0) {
        // Handle the error, for example, throw an exception
        throw std::invalid_argument("For Cauchy-Lorentz distribution, gamma must be greater than zero");
    }
    return 1.0 / (M_PI * m_gamma * (1 + pow((x - m_x0) / m_gamma, 2)));
}

double NegativeCrystalBallFunction::negativeCrystalBallFunction(double x) {
    if (m_stddev == 0.0) {
        // Handle the error, for example, throw an exception
        throw std::invalid_argument("For negative crystal ball distribution, standard deviation must be non-zero.");
    }
    if (m_n <= 1.0) {
        // Handle the error, for example, throw an exception
        throw std::invalid_argument("For negative crystal ball distribution, n must be greater than one.");
    }
    if (m_alpha <= 0.0) {
        // Handle the error, for example, throw an exception
        throw std::invalid_argument("For negative crystal ball distribution, alpha must be greater than zero.");
    }

    double A = pow(m_n / m_alpha, m_n) * exp(-0.5 * pow(m_alpha, 2));
    double B = m_n / m_alpha - m_alpha;
    double C = m_n / m_alpha * (1.0 / (m_n - 1)) * exp(-0.5 * pow(m_alpha, 2));
    double D = sqrt(M_PI / 2) * (1 + erf(m_alpha / sqrt(2)));
    double N = 1.0 / (m_stddev * (C + D));
    if ((x - m_mean)/m_stddev <= -m_alpha) {
        return N * A * pow(B - (x - m_mean) / m_stddev, -m_n);
    }
    else {
        return N * exp(-0.5 * pow((x - m_mean) / m_stddev, 2));
    }
}

// Overrides of callFunction for the different distributions
double FiniteFunction::callFunction(double x) {return this->invxsquared(x);}; 
double NormalFunction::callFunction(double x) {return this->normalDistribution(x);};
double CauchyLorentzFunction::callFunction(double x) {return this->cauchylorentzDistribution(x);};
double NegativeCrystalBallFunction::callFunction(double x) {return this->negativeCrystalBallFunction(x);};


/*
###################
Integration by hand (output needed to normalise function when plotting)
###################
*/ 
double FiniteFunction::integrate(int Ndiv){               //private
// Integration using the trapezoidal rule
  double h = (m_RMax - m_RMin) / static_cast<double>(Ndiv);
  double integral = 0.5 * (callFunction(m_RMin) + callFunction(m_RMax));

  for (int i = 1; i < Ndiv; ++i) {
      double x = m_RMin + i * h;
      integral += callFunction(x);
  }
  integral *= h;
  return integral;
}
double FiniteFunction::integral(int Ndiv) { //public
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    Ndiv = 1000;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}

/*
###################
//Helper functions 
###################
*/
// Generate paths from user defined stem
void FiniteFunction::checkPath(std::string outfile){
 path fp = outfile;
 m_FunctionName = fp.stem(); 
 m_OutData = m_FunctionName+".data";
 m_OutPng = m_FunctionName+".png";
} 

//Print (overridable)
void FiniteFunction::printInfo(){
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "--------------------------------------------------" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "--------------------------------------------------" << std::endl;
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
}
//Override the base class printInfo function
void NormalFunction::printInfo(){ //Override the base class printInfo function
  FiniteFunction::printInfo(); //Call the base class printInfo function
  std::cout << "stddev: " << m_stddev << std::endl; //add the extra info for the normal distribution
  std::cout << "mean: " << m_mean << std::endl;
  }

  //Override the base class printInfo function
void CauchyLorentzFunction::printInfo(){ //Override the base class printInfo function
  FiniteFunction::printInfo(); //Call the base class printInfo function
  std::cout << "x0 " << m_x0 << std::endl; //add the extra info for the normal distribution
  std::cout << "gamma: " << m_gamma << std::endl;
  }

void NegativeCrystalBallFunction::printInfo() {
    NormalFunction::printInfo();
    std::cout << "alpha: " << m_alpha << std::endl;
    std::cout << "n: " << m_n << std::endl;
}

/*
###################
//Plotting
###################
*/

//Hack because gnuplot-io can't read in custom functions, just scan over function and connect points with a line... 
void FiniteFunction::plotFunction(){
  m_function_scan = this->scanFunction(10000);
  m_plotfunction = true;
}

//Transform data points into a format gnuplot can use (histogram) and set flag to enable drawing of data to output plot
//set isdata to true (default) to plot data points in black, set to false to plot sample points in blue
void FiniteFunction::plotData(std::vector<double> &points, int Nbins, bool isdata){
  if (isdata){
    m_data = this->makeHist(points,Nbins);
    m_plotdatapoints = true;
  }
  else{
    m_samples = this->makeHist(points,Nbins);
    m_plotsamplepoints = true;
  }
}

/*
######################
// Metroplis Algorithm
######################
*/

// Metropolis algorithm takes the number of samples and a proposal standard deviation as arguments.
void FiniteFunction::metropolisSampling(int numSamples, float proposalStd) {
    // Step 1: Generate a random number 'xi' within the function's defined range, sampled from a uniform distribution.
    std::vector<double> sampleData; // Vector for storing the accepted sample data
    double randomX[numSamples];
    double randomY[numSamples];
    double randomT[numSamples];

    int randomNum = 1;
    std::random_device rd;
    std::mt19937 mtEngine{rd()}; // Mersenne Twister engine = random number generator. Found online and built in with <random>
    std::uniform_real_distribution<float> rndNumber{m_RMin, m_RMax};

    for (int j = 0; j < randomNum; j++) {
        // Step 1: Generate an initial random sample 'xi' from a uniform distribution
        double rndX = rndNumber(mtEngine);
        randomX[j] = rndX;
    }

    for (int i = 0; i < numSamples; i++) {
        // Step 2: Generate a second random sample 'y' from a normal distribution centered on 'xi' with the specified standard deviation.
        float centreNorm = randomX[i];
        float width = proposalStd;
        std::normal_distribution<float> normalPDF{centreNorm, width};
        double rndY = normalPDF(mtEngine);
        randomY[i] = rndY;

        // Step 3: Compute acceptance probability 'A = min(f(y) / f(xi), 1)', where 'f' is the function.
        double A;
        if (callFunction(randomY[i]) / callFunction(randomX[i]) < 1) {
            A = callFunction(randomY[i]) / callFunction(randomX[i]);
        } else {
            A = 1;
        }

        // Step 4: Generate a random number 'T' between 0 and 1. If 'T < A', then accept 'y'.
        int tMin = 0;
        int tMax = 1;
        std::uniform_real_distribution<float> rndTNumber{tMin, tMax};
        double rndT = rndTNumber(mtEngine);
        randomT[i] = rndT;

        if (randomT[i] < A) {
            // Step 5: If 'y' is accepted, set 'xi+1 = y'.
            randomX[i + 1] = randomY[i];
        } else {
            // If 'y' is not accepted, set 'xi+1 = xi'.
            randomX[i + 1] = randomX[i];
        }

        // Store the accepted sample
        sampleData.push_back(randomX[i + 1]);
        this->plotData(sampleData, 100, false); // Plot the sampled data using 100 bins
    }
}


/*
  #######################################################################################################
  ## SUPACPP Note:
  ## The three helper functions below are needed to get the correct format for plotting with gnuplot
  ## In theory you shouldn't have to touch them
  ## However it might be helpful to read through them and understand what they are doing
  #######################################################################################################
 */

//Scan over range of function using range/Nscan steps (just a hack so we can plot the function)
std::vector< std::pair<double,double> > FiniteFunction::scanFunction(int Nscan){
  std::vector< std::pair<double,double> > function_scan;
  double step = (m_RMax - m_RMin)/(double)Nscan;
  double x = m_RMin;
  //We use the integral to normalise the function points
  if (m_Integral == NULL) {
    std::cout << "Integral not set, doing it now" << std::endl;
    this->integral(Nscan);
    std::cout << "integral: " << m_Integral << ", calculated using " << Nscan << " divisions" << std::endl;
  }
    std::cout << "--------------------------------------------------" << std::endl;
  //For each scan point push back the x and y values 
  for (int i = 0; i < Nscan; i++){
    function_scan.push_back( std::make_pair(x,this->callFunction(x)/m_Integral));
    x += step;
  }
  return function_scan;
}

//Function to make histogram out of sampled x-values - use for input data and sampling
std::vector< std::pair<double,double> > FiniteFunction::makeHist(std::vector<double> &points, int Nbins){

  std::vector< std::pair<double,double> > histdata; //Plottable output shape: (midpoint,frequency)
  std::vector<int> bins(Nbins,0); //vector of Nbins ints with default value 0 
  int norm = 0;
  for (double point : points){
    //Get bin index (starting from 0) the point falls into using point value, range, and Nbins
    int bindex = static_cast<int>(floor((point-m_RMin)/((m_RMax-m_RMin)/(double)Nbins)));
    if (bindex<0 || bindex>Nbins-1){
      continue;
    }
    bins[bindex]++; //weight of 1 for each data point
    norm++; //Total number of data points
  }
  double binwidth = (m_RMax-m_RMin)/(double)Nbins;
  for (int i=0; i<Nbins; i++){
    double midpoint = m_RMin + i*binwidth + binwidth/2; //Just put markers at the midpoint rather than drawing bars
    double normdata = bins[i]/((double)norm*binwidth); //Normalise with N = 1/(Ndata*binwidth)
    histdata.push_back(std::make_pair(midpoint,normdata));
  }
  return histdata;
}

//Function which handles generating the gnuplot output, called in destructor
//If an m_plot... flag is set, the we must have filled the related data vector
//SUPACPP note: They syntax of the plotting code is not part of the course
void FiniteFunction::generatePlot(Gnuplot &gp){

  if (m_plotfunction==true && m_plotdatapoints==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotdatapoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
  }
  else if (m_plotfunction==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title 'function'\n";
    gp.send1d(m_function_scan);
  }

  else if (m_plotdatapoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_data);
  }

  else if (m_plotsamplepoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_samples);
  }
}
 
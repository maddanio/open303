#include "rosic_BiquadFilter.h"
using namespace rosic;

//-------------------------------------------------------------------------------------------------
// construction/destruction:

BiquadFilter::BiquadFilter()
{
  frequency  = 1000.0;
  gain       = 0.0;
  bandwidth  = 1.0;
  sampleRate = 44100.0;
  mode       = BYPASS;
  calcCoeffs();
  reset();    
}

//-------------------------------------------------------------------------------------------------
// parameter settings:

void BiquadFilter::setSampleRate(double newSampleRate)
{
  if( newSampleRate > 0.0 )
    sampleRate = newSampleRate;
  calcCoeffs();
}

void BiquadFilter::setMode(int newMode)
{
  mode = newMode; // 0:bypass, 1:Low Pass, 2:High Pass
  calcCoeffs();
}

void BiquadFilter::setFrequency(double newFrequency)
{
  frequency = newFrequency;
  calcCoeffs();
}

void BiquadFilter::setGain(double newGain)
{
  gain = newGain;
  calcCoeffs();
}

void BiquadFilter::setBandwidth(double newBandwidth)
{
  bandwidth = newBandwidth;
  calcCoeffs();
}

//-------------------------------------------------------------------------------------------------
//others:

void BiquadFilter::calcCoeffs()
{
  double w = 2*PI*frequency/sampleRate;
  double s, c;
  switch(mode)
  {
  case PEAK: 
    {
      // formula from Robert Bristow Johnson's biquad cookbook:
      sinCos(w, &s, &c);
      double alpha = s * sinh( 0.5*log(2.0) * bandwidth * w / s );
      double A     = dB2amp(gain);
      double scale = 1.0/(1.0+alpha/A);
      a1 = 2.0*c             * scale;
      a2 = ((alpha/A) - 1.0) * scale;
      b0 = (1.0+alpha*A)     * scale;
      b1 = -2.0*c            * scale;
      b2 = (1.0-alpha*A)     * scale;
    }
    break;
  case BANDREJECT: 
    {
      // formula from Robert Bristow Johnson's biquad cookbook:
      sinCos(w, &s, &c);

      /*
      double alpha = s * sinh( 0.5*log(2.0) * bandwidth * w / s );
      double scale = 1.0/(1.0+alpha);
      a1 = 2.0*c       * scale;
      a2 = (alpha-1.0) * scale;
      b1 = 0.0;
      b0 = 0.5*s       * scale;
      b2 = -b0;
      */

      double alpha = s * sinh( 0.5*log(2.0) * bandwidth * w / s );
      double a0Rec = 1.0/(1.0+alpha);
      a1 = 2.0*c       * a0Rec;
      a2 = (alpha-1.0) * a0Rec;
      b0 = 1.0         * a0Rec;
      b1 = -2.0*c      * a0Rec;
      b2 = 1.0         * a0Rec;
    }
    break;
  default: // bypass
    {
      b0 = 1.0;
      b1 = 0.0;
      b2 = 0.0;
      a1 = 0.0;
      a2 = 0.0;
    }break;
  }
}

void BiquadFilter::reset()
{
  x1 = 0.0;
  x2 = 0.0;
  y1 = 0.0;
  y2 = 0.0;
}

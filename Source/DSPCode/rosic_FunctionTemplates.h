#ifndef rosic_FunctionTemplates_h
#define rosic_FunctionTemplates_h

// rosic includes:
#include "GlobalDefinitions.h"
#include <algorithm>

namespace rosic
{
  // todo write functions for element-wise multiply, divide, negate, 
  // max, min, absMax, createCopy, filter, impulseResponse, impulseResponseLength, 
  // fillWith(double value = 0.0), circularShift, resample,

  // maybe introduce a range (start....end) to which the process is to be applied

  /** Returns the absolute value of the input argument for types that define the comparison 
  operators: '<', '>', the unary operator '-' and a constructor that takes an int and initializes 
  to zero when 0 is passed.  */
  template <class T>
  T absT(T x);

  /** Adds the elements of 'buffer1' and 'buffer2' - type must define operator '+'. The 'result' 
  buffer may be the same as 'buffer1' or 'buffer2'. */
  template <class T>
  void add(T *buffer1, T *buffer2, T *result, int length); 

  /** Circularly shifts the content of the buffer by 'numPositions' to the right - for leftward 
  shifts use negative values for numPositions. If the absolute value of 'numPositions' is greater
  than the length of the buffer, it will use numPositions modulo the length - so if the length is 6
  and numPositions is 8, it will whift by 2 positions. */
  template<class T>
  void circularShift(T *buffer, int length, int numPositions); 

  /** Restricts the values in the buffer to the range between min and max for types that define the
  operators '<' and '>'. */
  template <class T>
  void clipBuffer(T *buffer, int length, T min, T max); 

  /** Convolves an array x (seen as input signal) with another array h (seen as impulse response) 
  and stores the result in the array y. The type must define the operators: *, += and a constructor 
  that takes an int and initializes to zero when 0 is passed. The y array must be distinct form x 
  and h and have a length of at least xLength+hLength-1. */
  template <class T>
  void convolve(T *x, int xLength, T *h, int hLength, T *y); 

  /** Convolves x with h and stored the result in x. The xLength parameter denotes the number of 
  values in the x-array that will be considered as input signal. The actual array must be longer 
  than that (namely xLength+hLength-1) to store the appended values. */
  template <class T>
  void convolveInPlace(T *x, int xLength, T *h, int hLength); 

  /** Copies the data of one array into another one. */
  template <class T>
  void copyBuffer(T *source, T *destination, int length);

  /** Computes the cumulative sum y[n] = x[n] + y[n-1] of some signal. */
  template <class T>
  void cumulativeSum(T *buffer, int length, int order = 1, bool periodic = false);

  /** Computes the difference y[n] = x[n] - x[n-1] of some signal. The initial condition x[-1] is 
  determined from the 'periodic' parameter - if true, the signal is assumed as periodic and the 
  x[-1] sample will be assigned to he same value as the last in the buffer - otherwise, it will be 
  assigned to zero. When multiplying the result with the interval between successive samples, 
  this function can be used for numeric differentiation. If the order is greater than 1, the 
  operation will be performed iteratively on the respective result of the previous pass.  */
  template <class T>
  void difference(T *buffer, int length, int order = 1, bool periodic = false);

  /** De-interleaves a buffer of interleaved data. */
  template <class T>
  void deInterleave(T *buffer, int numFrames, int numElementsPerFrame);

  /** Fills the passed array with all zeros - the type must have a constructor that takes an int
  and initializes to the zero element when 0 is passed. */
  template <class T>
  void fillWithZeros(T *buffer, int length); 

  /** Filters the signal in input buffer x and stores the result in output buffer y. The filter 
  realizes the difference equation: 
  y[n] = b[0]*x[n] + b[1]*x[n-1] + b[2]*x[n-2] + ... + b[bOrder]*x[n-bOrder] 
                   - a[1]*y[n-1] - a[2]*y[n-2] - ... - a[aOrder]*y[n-aOrder]
  so the arrays of coefficients must have a length of their order + 1. The output buffer may have 
  a different length than the input buffer. If it is longer, it will be assumed that the missing 
  samples in the input buffer are zero. The input and output buffers may also be identical (i.e. 
  point to the same location), in which case the filtering will be done in place. */
  template <class T>
  void filter(T *x, int xLength, T *y, int yLength, T *b, int bOrder, T *a, int aOrder); 


  template <class T>
  void filterBiDirectional(T *x, int xLength, T *y, int yLength, T *b, int bOrder, T *a, 
    int aOrder, int numRingOutSamples = 10000); 

  template <class T>
  void impulseResponse(T *h, int hLength, T *b, int bOrder, T *a, int aOrder); 


  /** Interleaves a buffer of non-interleaved data. */
  template <class T>
  void interleave(T *buffer, int numFrames, int numElementsPerFrame);

  /** Finds and returns the maximum absolute value of the buffer. */
  template <class T>
  T maxAbs(T *buffer, int length);  

  /** Returns the index of maximum value of the buffer (">"-operator must be defined). */
  template <class T>
  INLINE int maxIndex(T *buffer, int length);

  /** Returns the maximum value of the buffer (">"-operator must be defined). */
  template <class T>
  INLINE T maxValue(T *buffer, int length);

  /** Returns the index of minimum value of the buffer ("<"-operator must be defined). */
  template <class T>
  INLINE int minIndex(T *buffer, int length);

  /** Returns the minimum value of the buffer ("<"-operator must be defined). */
  template <class T>
  INLINE T minValue(T *buffer, int length);

  /** Computes the mean (i.e. the DC-component) from the passed buffer. The type must define operators: 
  +=, / and a constructor which takes an int and initializes to zero when 0 is passed and a typecast 
  from int. */
  template <class T>
  T mean(T *buffer, int length);  

  /** Returns the median of the passed buffer. */
  template <class T>
  T median(T *buffer, int length); 

  /** Multiplies the elements of 'buffer1' and 'buffer2' - type must define operator '*'. The 
  'result' buffer may be the same as 'buffer1' or 'buffer2'. */
  template <class T>
  void multiply(T *buffer1, T *buffer2, T *result, int length); 

  /** Normalizes the maximum value of the passed array. The type must define: >, *=, / and a 
  constructor that takes an int and initializes to 0 when 0 is passed. Additionaly, it must be 
  suitable for absT - that additionaly requires definition of unary '-' and '<'. */
  template <class T>
  void normalize(T *buffer, int length, T maximum);  

  /** Rearranges/permutes and array of class T into bit-reversed order (in place). The 'length' 
  MUST be the 'numBits' th power of two (this is not checked for). */
  //template <class T>
  //INLINE void orderBitReversedInPlace(T* buffer, int length, int numStages);

  /** Rearranges/permutes and array of type T into bit-reversed order. The 'length' MUST be the
  'numBits' th power of two (this is not checked for). */
  template <class T>
  INLINE void orderBitReversedOutOfPlace(T *inBuffer, T *outBuffer, int length, int numBits);

  /** Returns the product of the elements in the buffer for types which define the 
  multiplication operator (the *= version thereof) and a constructor which can take an int 
  paramater as argument and initializes to the multiplicative neutral element of that class when 1 
  is passed . */
  template <class T>
  INLINE T product(T *buffer, int length);

  /** Removes mean (i.e. the DC-component) from the passed buffer. The type must define operators: 
  +=, -=, / and a constructor which takes an int and initializes to zero when 0 is passed and a 
  typecast from int. */
  template <class T>
  void removeMean(T *buffer, int length);  

  /** Reverses the order of the elements the passed array. */
  template <class T>
  void reverse(T *buffer, int length);  

  /** The maximum of two objects on which the ">"-operator is defined. */
  template <class T>
  INLINE T rmax(T in1, T in2);

  /** The maximum of four objects on which the ">"-operator is defined. */
  template <class T>
  INLINE T rmax(T in1, T in2, T in3, T in4);

  /** The minimum of two objects on which the ">"-operator is defined. */
  template <class T>
  INLINE T rmin(T in1, T in2);

  /** The minimum of four objects on which the ">"-operator is defined. */
  template <class T>
  INLINE T rmin(T in1, T in2, T in3, T in4);

  /** Scales the buffer by a constant factor. */
  template <class T>
  void scale(T *buffer, int length, T scaleFactor);  

  /** Subtracts the elements of 'buffer2' from 'buffer1' - type must define operator '-'. The 
  'result' buffer may be the same as 'buffer1' or 'buffer2'. */
  template <class T>
  void subtract(T *buffer1, T *buffer2, T *result, int length); 

  /** Returns the sum of the elements in the buffer for types which define the 
  addition operator (the += version thereof) and a constructor which can take an int 
  paramater as argument and initializes to the additive neutral element of that class when 0 
  is passed . */
  template <class T>
  INLINE T sum(T *buffer, int length);

  /** Swaps two objects of class T. */
  template <class T>
  INLINE void swap(T &in1, T &in2);

  //===============================================================================================
  // implementation:

  template <class T>
  T absT(T x)
  {
    if( x > T(0) )
      return x;
    else if( x < T(0) )
      return -x;
    else
      return T(0);
  }

  template <class T>
  void add(T *buffer1, T *buffer2, T *result, int length)
  {
    for(int i=0; i<length; i++)
      result[i] = buffer1[i] + buffer2[i];
  }

  template <class T>
  void circularShift(T *buffer, int length, int numPositions)
  {
    int na = abs(numPositions);
    while( na > length )
      na -=length;
    T *tmp = (T*) alloca(na*sizeof(T));
    if( numPositions < 0 )
    {
      memcpy(  tmp,                buffer,              na*sizeof(T));
      memmove( buffer,            &buffer[na], (length-na)*sizeof(T));
      memcpy( &buffer[length-na],  tmp,                 na*sizeof(T));
    }
    else if( numPositions > 0 )
    {
      memcpy(  tmp,        &buffer[length-na],          na*sizeof(T));
      memmove(&buffer[na],  buffer,            (length-na)*sizeof(T));   
      memcpy(  buffer,      tmp,                        na*sizeof(T));
    }
  }

  template <class T>
  void clipBuffer(T *buffer, int length, T min, T max)
  {
    for(int i=0; i<length; i++)
    {
      if( buffer[i] < min )
        buffer[i] = min;
      else if( buffer[i] > max )
        buffer[i] = max;
    }
  }

  template <class T>
  INLINE void convolve(T *x, int xLength, T *h, int hLength, T *y)
  {
    int yLength = xLength+hLength-1; // length of the resulting sequence
    int n, k;                        // indices

    // init the result-buffer with the default constructor of class T (this should create an 
    // all-zeros sequence):
    for(n=0; n<yLength; n++) 
      y[n] = T(0);

    // do the convolution:
    for(n=0; n<yLength; n++)
    {
      for(k=0; k<hLength; k++)
      {
        if( (n-k) >= 0 && (n-k) < xLength )  
          y[n] += h[k] * x[n-k];
      }
    }
  }

  template <class T>
  INLINE void convolveInPlace(T *x, int xLength, T *h, int hLength)
  {
    T *xTmp = new T[xLength];
    for(int i=0; i<xLength; i++)
      xTmp[i] = x[i];
    T *hTmp = new T[hLength];
    for(int i=0; i<hLength; i++)
      hTmp[i] = h[i];
    convolve(xTmp, xLength, hTmp, hLength, x);
    delete[] xTmp;
    delete[] hTmp;
  }

  template <class T>
  void copyBuffer(T *source, T *destination, int length)
  {
    for(int i=0; i<length; i++)
      destination[i] = source[i];
  }

  template <class T>
  void cumulativeSum(T *buffer, int length, int order, bool periodic)
  {
    T y, y1; // for temporary storage of the y, y[n-1] samples
    for(int o=1; o<=order; o++)
    {
      /*
      if( periodic == true )
      {
        y1 = T(0);
        // determine the correct intial condition by 'warming up' the filter:
        int numWarmUpSamples = 1000;
        int j = 0;
        while( j < numWarmUpSamples )
        {
          for(int n=0; n<length; n++)
          {
            y  = buffer[n] + y1;
            y1 = y;
          }
          j += length;
        }
      }
      else
        y1 = T(0);
      */
      y1 = T(0);
      for(int n=0; n<length; n++)
      {
        y         = buffer[n] + y1;
        buffer[n] = y;
        y1        = y;
      }
    }
  }

  template <class T>
  void difference(T *buffer, int length, int order, bool periodic)
  {
    T x, x1; // for temporary storage of the x, x[n-1] samples
    for(int o=1; o<=order; o++)
    {
      if( periodic == true )
      {
        x1 = buffer[length-1];
      }
      else
        x1 = T(0);
      for(int n=0; n<length; n++)
      {
        x         = buffer[n];
        buffer[n] = x - x1;    // y[n] = x[n] - x[n-1]
        x1        = x;
      }
    }
  }

  template <class T>
  void deInterleave(T *buffer, int numFrames, int numElementsPerFrame)
  {
    T *tmp = new T[numFrames*numElementsPerFrame];
    int i, j;
    for(i=0; i<numFrames*numElementsPerFrame; i++)
      tmp[i] = buffer[i];
    for(j=0; j<numElementsPerFrame; j++)
    {
      int k = numFrames*j;
      for(i=0; i<numFrames; i+=1)
        buffer[k+i] = tmp[numElementsPerFrame*i+j];
    }
    delete tmp;
  }

  template <class T>
  void fillWithZeros(T *buffer, int length)
  {
    for(int i=0; i<length; i++)
      buffer[i] = T(0);
  }

  template <class T>
  void filter(T *x, int xLength, T *y, int yLength, T *b, int bOrder, T *a, int aOrder)
  {
    // allocate and intitialize memory for the filters internal state:
    int i, n;
    T *xOld = new T[bOrder+1];
    T *yOld = new T[aOrder+1];
    for(i=0; i<=bOrder; i++) xOld[i] = T(0);
    for(i=0; i<=aOrder; i++) yOld[i] = T(0);

    // compute the part of the signal where both buffers have values:
    int length = rmin(xLength, yLength);
    T tmp;
    for(n=0; n<length; n++)
    {
      // compute y[n]:
      tmp = b[0] * x[n];
      for(i=1; i<=bOrder; i++) tmp += b[i] * xOld[i];
      for(i=1; i<=aOrder; i++) tmp -= a[i] * yOld[i];

      // update state buffers:
      for(i=bOrder; i>=2; i--) xOld[i] = xOld[i-1];
      for(i=aOrder; i>=2; i--) yOld[i] = yOld[i-1];
      xOld[1] = x[n];
      yOld[1] = tmp;

      // store y[n]:
      y[n] = tmp;
    }

    // possibly compute the tail-part of y when the y-buffer is longer than x-buffer:
    for(int n=length; n<yLength; n++)
    {
      tmp = T(0);
      for(i=1; i<=bOrder; i++) tmp += b[i] * xOld[i];
      for(i=1; i<=aOrder; i++) tmp -= a[i] * yOld[i];
      for(i=bOrder; i>=2; i--) xOld[i] = xOld[i-1];
      for(i=aOrder; i>=2; i--) yOld[i] = yOld[i-1];
      xOld[1] = T(0);
      yOld[1] = tmp;
      y[n]    = tmp;
    }

    // clean up memory:
    delete[] xOld;
    delete[] yOld;
  }

  template <class T>
  void filterBiDirectional(T *x, int xLength, T *y, int yLength, T *b, int bOrder, T *a, 
    int aOrder, int numRingOutSamples)
  {
    // allocate and intitialize memory for the filters internal state:
    int i, n;
    T tmp;
    T *xOld    = new T[bOrder+1];
    T *yOld    = new T[aOrder+1];
    T *ringOut = new T[numRingOutSamples];
    for(i=0; i<=bOrder; i++) xOld[i] = T(0);
    for(i=0; i<=aOrder; i++) yOld[i] = T(0);

    /*
    // backward pass through a portion of the x-buffer to warm up the filter:
    for(n=rmin(xLength-1, 10000); n>=0; n--)
    {
      // compute y[n]:
      tmp = b[0] * x[n];
      for(i=1; i<=bOrder; i++) tmp += b[i] * xOld[i];
      for(i=1; i<=aOrder; i++) tmp -= a[i] * yOld[i];

      // update state buffers:
      for(i=bOrder; i>=2; i--) xOld[i] = xOld[i-1];
      for(i=aOrder; i>=2; i--) yOld[i] = yOld[i-1];
      xOld[1] = x[n];
      yOld[1] = tmp;
    }
    */

    // compute the part of the signal where both buffers have values:
    int length = rmin(xLength, yLength);
    for(n=0; n<length; n++)
    {
      tmp = b[0] * x[n];
      for(i=1; i<=bOrder; i++) tmp += b[i] * xOld[i];
      for(i=1; i<=aOrder; i++) tmp -= a[i] * yOld[i];
      for(i=bOrder; i>=2; i--) xOld[i] = xOld[i-1];
      for(i=aOrder; i>=2; i--) yOld[i] = yOld[i-1];
      xOld[1] = x[n];
      yOld[1] = tmp;
      y[n]    = tmp;
    }

    // possibly compute the tail-part of y when the y-buffer is longer than x-buffer:
    for(int n=length; n<yLength; n++)
    {
      tmp = T(0);
      for(i=1; i<=bOrder; i++) tmp += b[i] * xOld[i];
      for(i=1; i<=aOrder; i++) tmp -= a[i] * yOld[i];
      for(i=bOrder; i>=2; i--) xOld[i] = xOld[i-1];
      for(i=aOrder; i>=2; i--) yOld[i] = yOld[i-1];
      xOld[1] = T(0);
      yOld[1] = tmp;
      y[n]    = tmp;
    }

    // compute the ringout tail:
    for(n=0; n<numRingOutSamples; n++)
    {
      tmp = T(0);
      for(i=1; i<=bOrder; i++) tmp += b[i] * xOld[i];
      for(i=1; i<=aOrder; i++) tmp -= a[i] * yOld[i];
      for(i=bOrder; i>=2; i--) xOld[i] = xOld[i-1];
      for(i=aOrder; i>=2; i--) yOld[i] = yOld[i-1];
      xOld[1]    = y[n];
      yOld[1]    = tmp;
      ringOut[n] = tmp;
    }

    // backward pass through the ringout tail:
    for(n=numRingOutSamples-1; n>=0; n--)
    {
      tmp = b[0] * ringOut[n];
      for(i=1; i<=bOrder; i++) tmp += b[i] * xOld[i];
      for(i=1; i<=aOrder; i++) tmp -= a[i] * yOld[i];
      for(i=bOrder; i>=2; i--) xOld[i] = xOld[i-1];
      for(i=aOrder; i>=2; i--) yOld[i] = yOld[i-1];
      xOld[1] = y[n];
      yOld[1] = tmp;
    }

    // backward pass through the y-buffer:
    for(n=yLength-1; n>=0; n--)
    {
      tmp = b[0] * y[n];
      for(i=1; i<=bOrder; i++) tmp += b[i] * xOld[i];
      for(i=1; i<=aOrder; i++) tmp -= a[i] * yOld[i];
      for(i=bOrder; i>=2; i--) xOld[i] = xOld[i-1];
      for(i=aOrder; i>=2; i--) yOld[i] = yOld[i-1];
      xOld[1] = y[n];
      yOld[1] = tmp;
      y[n]    = tmp;
    }

    // clean up memory:
    delete[] xOld;
    delete[] yOld;
    delete[] ringOut;
  }

  template <class T>
  void impulseResponse(T *h, int hLength, T *b, int bOrder, T *a, int aOrder)
  {
    T x = T(1);
    filter(&x, 1, h, hLength, b, bOrder, a, aOrder);
  }

  template <class T>
  void interleave(T *buffer, int numFrames, int numElementsPerFrame)
  {
    T *tmp = new T[numFrames*numElementsPerFrame];
    int i, j;
    for(i=0; i<numFrames*numElementsPerFrame; i++)
      tmp[i] = buffer[i];
    for(j=0; j<numElementsPerFrame; j++)
    {
      int k = numFrames*j;
      for(i=0; i<numFrames; i+=1)
        buffer[numElementsPerFrame*i+j] = tmp[k+i];
    }
    delete tmp;
  }

  template <class T>
  T maxAbs(T *buffer, int length)
  {
    T max = T(0);
    for(int i=0; i<length; i++)
    {
      if( absT(buffer[i]) > max)
        max = absT(buffer[i]);
    }
    return max;
  }

  template <class T>
  int maxIndex(T *buffer, int length)
  {
    T   value = buffer[0];
    int index = 0;
    for(int i=0; i<length; i++)
    {
      if( buffer[i] > value )
      {
        value = buffer[i];
        index = i;
      }
    }
    return index;
  }

  template <class T>
  T maxValue(T *buffer, int length)
  {
    return buffer[maxIndex(buffer, length)];
  }

  template <class T>
  int minIndex(T *buffer, int length)
  {
    T   value = buffer[0];
    int index = 0;
    for(int i=0; i<length; i++)
    {
      if( buffer[i] < value )
      {
        value = buffer[i];
        index = i;
      }
    }
    return index;
  }

  template <class T>
  T minValue(T *buffer, int length)
  {
    return buffer[minIndex(buffer, length)];
  }

  template <class T>
  T mean(T *buffer, int length)
  {
    return sum(buffer, length) / (T) length;
  }

  template <class T>
  T median(T *buffer, int length)
  {
    T* tmpBuffer = new T[length];
    copyBuffer(buffer, tmpBuffer, length);

    std::sort(tmpBuffer, &tmpBuffer[length]);
    T med;
    if( isOdd(length) )
      med = tmpBuffer[(length-1)/2];
    else
      med = (T) ( 0.5 * ( tmpBuffer[length/2] + tmpBuffer[length/2-1] ) ); 

    delete[] tmpBuffer;
    return med;
  }

  template <class T>
  void multiply(T *buffer1, T *buffer2, T *result, int length)
  {
    for(int i=0; i<length; i++)
      result[i] = buffer1[i] * buffer2[i];
  }

  template <class T>
  void normalize(T *buffer, int length, T maximum)
  {
    T max   = maxAbs(buffer, length);;
    T scale = maximum / max;
    for(int i=0; i<length; i++)
      buffer[i] *= scale;
  }

  template <class T>
  INLINE void orderBitReversedOutOfPlace(T *inBuffer, T *outBuffer, int length, int numBits)
  {
    // gather up the values from the bit-reversed positions in the input array:
    for(int n=0; n<length; n++)
      outBuffer[n] = inBuffer[bitReverse(n, numBits)];
  }

  template <class T>
  INLINE T product(T *buffer, int length)
  {
    T accu = T(1); // constructor call with 1 should initilize to multiplicative neutral element
    for(int n=0; n<length; n++)
      accu *= buffer[n];
    return accu;
  }

  template <class T>
  void removeMean(T *buffer, int length)
  {
    T m = mean(buffer, length);
    for(int i=0; i<length; i++)
      buffer[i] -= m;
  }

  template <class T>
  INLINE T rmax(T in1, T in2)
  {
    if( in1 > in2 )
      return in1;
    else
      return in2;
  }

  template <class T>
  INLINE T rmax(T in1, T in2, T in3, T in4)
  {
    return rmax(rmax(in1, in2), rmax(in3, in4));
  }

  template <class T>
  INLINE T rmin(T in1, T in2)
  {
    if( in1 < in2 )
      return in1;
    else
      return in2;
  }

  template <class T>
  INLINE T rmin(T in1, T in2, T in3, T in4)
  {
    return rmin(rmin(in1, in2), rmin(in3, in4));
  }

  template <class T>
  void reverse(T *buffer, int length)
  {
    T tmp;
    int lengthMinus1 = length-1;
    for(int i=0; i<=(length-2)/2; i++)
    {
      tmp                    = buffer[lengthMinus1-i];
      buffer[lengthMinus1-i] = buffer[i];
      buffer[i]              = tmp;
    }
  }

  template <class T>
  void scale(T *buffer, int length, T scaleFactor)
  {
    for(int n=0; n<length; n++)
      buffer[n] *= scaleFactor;
  }

  template <class T>
  void subtract(T *buffer1, T *buffer2, T *result, int length)
  {
    for(int i=0; i<length; i++)
      result[i] = buffer1[i] - buffer2[i];
  }

  template <class T>
  INLINE T sum(T *buffer, int length)
  {
    T accu = T(0); // constructor call with 0 should initilizes to additive neutral element
    for(int n=0; n<length; n++)
      accu += buffer[n];
    return accu;
  }

  template <class T>
  INLINE void swap(T &in1, T &in2)
  {
    T tmp = in1;
    in1   = in2;
    in2   = tmp;   
  }

} // end namespace rosic

#endif // #ifndef rosic_FunctionTemplates_h
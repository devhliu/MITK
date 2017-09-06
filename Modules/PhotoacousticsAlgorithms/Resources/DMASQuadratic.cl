/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

__kernel void ckDMASQuad(
  __global float* dSource, // input image
  __global float* dDest, // output buffer
  __global float* apodArray,
  unsigned short apodArraySize,
  float SpeedOfSound,
  float TimeSpacing,
  float Pitch,
  float Angle,
  unsigned short PAImage,
  unsigned short TransducerElements,
  unsigned int inputL,
  unsigned int inputS,
  unsigned int Slices,
  unsigned int outputL,
  unsigned int outputS  // parameters
)
{
  // get thread identifier
  unsigned int globalPosX = get_global_id(0);
  unsigned int globalPosY = get_global_id(1);
  unsigned int globalPosZ = get_global_id(2);

  // terminate non-valid threads
  if ( globalPosX < outputL && globalPosY < outputS && globalPosZ < Slices )
  {	
    float l_i = (float)globalPosX / outputL * inputL;
    float s_i = (float)globalPosY / outputS * inputS / 2;
	
    float part = (tan(Angle / 360 * 2 * M_PI) * TimeSpacing * SpeedOfSound / Pitch * outputL / TransducerElements) * s_i;
    if (part < 1)
      part = 1;

    short maxLine = min((l_i + part) + 1, (float)inputL);
    short minLine = max((l_i - part), 0.0f);
    short usedLines = (maxLine - minLine);
    float apod_mult = apodArraySize / (maxLine - minLine);
    
    short AddSample1 = 0;
    short AddSample2 = 0;
    
    float output = 0;
    float mult = 0;

    float delayMultiplicator = pow(1 / (TimeSpacing*SpeedOfSound) * Pitch * TransducerElements / inputL, 2) / s_i / 2;

    for (short l_s1 = minLine; l_s1 < maxLine; ++l_s1)
    {
      AddSample1 = delayMultiplicator * pow((l_s1 - l_i), 2) + s_i + (1-PAImage)*s_i;
      if (AddSample1 < inputS && AddSample1 >= 0) {
        for (short l_s2 = l_s1 + 1; l_s2 < maxLine; ++l_s2)
        {
          AddSample2 = delayMultiplicator * pow((l_s2 - l_i), 2) + s_i + (1-PAImage)*s_i;
          if (AddSample1 < inputS && AddSample1 >= 0) {
            mult = apodArray[(short)((l_s2 - minLine)*apod_mult)] * dSource[(unsigned int)(globalPosZ * inputL * inputS + AddSample2 * inputL + l_s2)]
              * apodArray[(short)((l_s1 - minLine)*apod_mult)] * dSource[(unsigned int)(globalPosZ * inputL * inputS + AddSample1 * inputL + l_s1)];
            output += sqrt(mult * ((float)(mult>0)-(float)(mult<0))) * ((mult > 0) - (mult < 0));
          
          }
        }
      }
      else
        --usedLines;
    }
	  
    dDest[ globalPosZ * outputL * outputS + globalPosY * outputL + globalPosX ] = output / (pow((float)usedLines, 2.0f) - (usedLines - 1));
  }
}
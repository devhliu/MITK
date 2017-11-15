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

#ifndef mitkGIFFirstOrderHistogramStatistics_h
#define mitkGIFFirstOrderHistogramStatistics_h

#include <mitkAbstractGlobalImageFeature.h>
#include <mitkBaseData.h>
#include <MitkCLUtilitiesExports.h>

namespace mitk
{
  class MITKCLUTILITIES_EXPORT GIFFirstOrderHistogramStatistics : public AbstractGlobalImageFeature
  {
  public:
    mitkClassMacro(GIFFirstOrderHistogramStatistics,AbstractGlobalImageFeature)
      itkFactorylessNewMacro(Self)
      itkCloneMacro(Self)

      GIFFirstOrderHistogramStatistics();

    /**
    * \brief Calculates the Cooccurence-Matrix based features for this class.
    */
    virtual FeatureListType CalculateFeatures(const Image::Pointer & image, const Image::Pointer &feature) override;

    /**
    * \brief Returns a list of the names of all features that are calculated from this class
    */
    virtual FeatureNameListType GetFeatureNames() override;

    itkGetConstMacro(Range,double);
    itkSetMacro(Range, double);
    itkGetConstMacro(HistogramSize,int);
    itkSetMacro(HistogramSize, int);
    itkGetConstMacro(UseCtRange,bool);
    itkSetMacro(UseCtRange, bool);
    itkGetConstMacro(BinSize, double);
    itkSetMacro(BinSize, double);

    virtual void CalculateFeaturesUsingParameters(const Image::Pointer & feature, const Image::Pointer &mask, const Image::Pointer &maskNoNAN, FeatureListType &featureList);
    virtual void AddArguments(mitkCommandLineParser &parser);


    struct ParameterStruct {
      int m_HistogramSize;
      bool m_UseCtRange;

      double MinimumIntensity;
      bool UseMinimumIntensity;
      double MaximumIntensity;
      bool UseMaximumIntensity;
      int Bins;
      double BinSize;
    };

  private:
    double m_Range;
    int m_HistogramSize;
    bool m_UseCtRange;
    double m_BinSize;
  };
}
#endif //mitkGIFFirstOrderHistogramStatistics_h

/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef QmitkPixelValueView_h
#define QmitkPixelValueView_h

#include <QmitkAbstractView.h>
#include <QmitkSliceNavigationListener.h>
#include <mitkIRenderWindowPartListener.h>

namespace mitk
{
  class BaseData;
  class Image;
  class TimeGeometry;
}

namespace Ui
{
  class QmitkPixelValueView;
}

class QmitkPixelValueView : public QmitkAbstractView, public mitk::IRenderWindowPartListener
{
  Q_OBJECT

public:
  static const std::string VIEW_ID;

  QmitkPixelValueView(QObject* parent = nullptr);

  ~QmitkPixelValueView() override;

  void CreateQtPartControl(QWidget* parent) override;

  void SetFocus() override;

private:
  void RenderWindowPartActivated(mitk::IRenderWindowPart* renderWindowPart) override;
  void RenderWindowPartDeactivated(mitk::IRenderWindowPart* renderWindowPart) override;
  void RenderWindowPartInputChanged(mitk::IRenderWindowPart* renderWindowPart) override;

  void OnSelectedPositionChanged(const mitk::Point3D& position);
  void OnSelectedTimePointChanged(const mitk::TimePointType& timePoint);

  void NodeChanged(const mitk::DataNode* node) override;

  void Clear();
  void ClearCoords();

  void Update();
  void UpdateCoords(const mitk::Image* image, const itk::Index<3>& index, const mitk::Point3D& position);
  void UpdateIndexCoord(const itk::Index<3>& index, unsigned int dimension = 3);
  void UpdateWorldCoord(const mitk::Point3D& position, unsigned int dimension = 3);
  void UpdateTimeStep(const mitk::TimeGeometry* geometry);
  void ShowTimeStep(bool show);

  QmitkSliceNavigationListener m_SliceNavigationListener;
  Ui::QmitkPixelValueView* m_Ui;
};

#endif

project(org_mitk_gui_qt_segmentation)

include_directories(${CTK_INCLUDE_DIRS})

mitk_create_plugin(
  EXPORT_DIRECTIVE MITK_QT_SEGMENTATION
  EXPORTED_INCLUDE_SUFFIXES src
  PCH
    berryWeakPointer.h
    mitkDataNode.h
  MODULE_DEPENDS MitkAppUtil MitkQtWidgetsExt MitkSegmentationUI
  PACKAGE_DEPENDS Qt6|OpenGL nlohmann_json
)

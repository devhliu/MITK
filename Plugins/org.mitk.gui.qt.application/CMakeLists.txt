project(org_mitk_gui_qt_application)

mitk_create_plugin(
  EXPORT_DIRECTIVE MITK_QT_APP
  EXPORTED_INCLUDE_SUFFIXES src
  PCH
    berryWeakPointer.h
    mitkBaseRenderer.h
    mitkDataNode.h
  MODULE_DEPENDS MitkQtWidgets MitkQtWidgetsExt
  PACKAGE_DEPENDS Qt6|OpenGL+Xml
  )

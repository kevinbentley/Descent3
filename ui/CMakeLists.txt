set(HEADERS UIlib.h)
set(CPPS
  UIButton.cpp
  UICombo.cpp
  UIConsole.cpp
  UIDraw.cpp
  UIEdit.cpp
  UIGadget.cpp
  UIGroup.cpp
  UIHotspot.cpp
  UIListBox.cpp
  UIObject.cpp
  UIRes.cpp
  UISlider.cpp
  UIStatic.cpp
  UISystem.cpp
  UIWindow.cpp)

add_library(ui STATIC ${HEADERS} ${CPPS})
target_link_libraries(ui PRIVATE
  ddio
  mem
  misc
)

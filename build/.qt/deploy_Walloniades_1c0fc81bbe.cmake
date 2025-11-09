include(C:/C++/Walloniades/build/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/Walloniades-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/C++/Walloniades/build/Walloniades.exe
    GENERATE_QT_CONF
)

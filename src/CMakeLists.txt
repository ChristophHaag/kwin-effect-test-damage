#######################################
# Effect

#######################################
# Config

find_package (KWinEffects REQUIRED)

find_package (Qt5 REQUIRED COMPONENTS
    Core
)

find_package (KF5 REQUIRED COMPONENTS
    Service
    WindowSystem
    GlobalAccel
    I18n
)

qt5_add_resources(TestDamage.cpp)
add_library(kwin_effect_test_damage SHARED TestDamage.cpp)

target_link_libraries(kwin_effect_test_damage
PUBLIC
    Qt5::Core
    KF5::WindowSystem
    KF5::Service
    KF5::GlobalAccel
    KF5::I18n
    KWinEffects::KWinEffects
)

kcoreaddons_desktop_to_json(kwin_effect_test_damage test_damage.desktop SERVICE_TYPES kwineffect.desktop)

install(
    TARGETS
        kwin_effect_test_damage
    DESTINATION
        ${PLUGIN_INSTALL_DIR}/kwin/effects/plugins/
)

#include "obs-text-slideshow-dock.h"
#include <obs-module.h>
#include <QCloseEvent>

/**
 * Constructor for the custom control dock panel.
 */
TextSlideshowDock::TextSlideshowDock(QWidget *parent)
    : QDockWidget(parent)
{
    // Ensure the object name matches the unique ID specified in plugin-main.cpp
    setObjectName("obs_text_slideshow_dock");
    
    // Set the window title used when the dock is pulled out into a floating window
    setWindowTitle(obs_module_text("TextSlideshowDockTitle"));

    // Set standard behavior rules for modern OBS panels (movable, floatable, closable)
    setFeatures(QDockWidget::DockWidgetMovable | 
                QDockWidget::DockWidgetFloatable | 
                QDockWidget::DockWidgetClosable);

    // Initialize the visual layout from the companion .ui file
    ui.setupUi(this);
}

/**
 * Destructor to clean up resources when the dock is deleted.
 */
TextSlideshowDock::~TextSlideshowDock()
{
    // Destructor implementation
}

/**
 * Safe capture interface event handling for closing operations.
 */
void TextSlideshowDock::closeEvent(QCloseEvent *event)
{
    QDockWidget::closeEvent(event);
}

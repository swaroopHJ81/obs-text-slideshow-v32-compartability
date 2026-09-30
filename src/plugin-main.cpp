#include <obs-module.h>
#include <obs-frontend-api.h>
#include <util/platform.h>
#include <qt-wrappers.hpp>
#include "obs-text-slideshow-dock.h"

// Tell OBS this is a valid plugin module
OBS_DECLARE_MODULE()

// Set up the default language files
OBS_MODULE_USE_DEFAULT_LOCALE("obs-text-slideshow", "en-US")

// Extern pointers to the text source definitions (defined in your other source files)
extern struct obs_source_info obs_text_freetype2_slideshow_source_info;
extern struct obs_source_info obs_text_gdiplus_slideshow_source_info;

/**
 * Creation callback function required by OBS Studio 30+.
 * This safely builds the custom Qt user interface when OBS asks for it.
 */
static QWidget *CreateTextSlideshowDock(void *data)
{
    UNUSED_PARAMETER(data);
    return new TextSlideshowDock();
}

/**
 * Called automatically by OBS when the plugin is loaded into memory.
 */
bool obs_module_load(void)
{
    // 1. Register the platform-specific slideshow text sources
#if defined(_WIN32)
    obs_register_source(&obs_text_gdiplus_slideshow_source_info);
#elif defined(__APPLE__) || defined(__linux__)
    obs_register_source(&obs_text_freetype2_slideshow_source_info);
#endif

    // 2. Register the modern custom dock UI so it appears under the Docks menu
    obs_frontend_add_custom_qdock(
        "obs_text_slideshow_dock",                         // Unique internal ID
        obs_module_text("TextSlideshowDockTitle"),         // Text shown in the menu
        CreateTextSlideshowDock,                           // The builder function above
        nullptr                                            // Extra data (not needed here)
    );

    return true;
}

/**
 * Called automatically by OBS when the plugin is being closed down.
 */
void obs_module_unload(void)
{
    // Clean up operations can go here if needed by future updates
}

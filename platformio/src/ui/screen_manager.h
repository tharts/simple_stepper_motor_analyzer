#pragma once

#include "lvgl.h"
#include "ui.h"

namespace screen_manager {

class Screen {
 public:
  // Called once after lvgl library was initialized. Screen_num ignored if zero.
  virtual void setup(uint8_t screen_num) = 0;
  // Called before becoming the active screen.
  virtual void on_load(){};
  // Called when the active screen before becoming inactive,
  // before calling the on_load() of next screen.
  virtual void on_unload(){};
  // Called periodically when this is the active screen.
  virtual void loop(){};
  // On event. Should ignore unknown events.
  virtual void on_event(ui_events::UiEventId ui_event_id) {}

  lv_obj_t* lv_scr() { return screen_.lv_screen; }
  // Used for on demand setup() to speed up app startup time.
  inline bool is_setup() { return screen_.lv_screen != nullptr; }

 protected:
  ui::Screen screen_;
  // Uses an internal temp formatting buffer that is
  // share by all screens.
  static const char* format(const char* format, ...);

 private:
};

enum ScreenId {
  SCREEN_NONE,
  SCREEN_HOME,
  SCREEN_SPEED_GAUGE,
  SCREEN_STEPS_CHART,
  SCREEN_RETRACTION_CHART,
  SCREEN_TIME_HISTOGRAM,
  SCREEN_STEPS_HISTOGRAM,
  SCREEN_OSCILOSCOPE,
  SCREEN_PHASE,
  SCREEN_CURRENT_HISTOGRAM,
  SCREEN_SETTINGS,
  SCREEN_TEST,
};

void setup();
// Called after the first screen is displayed, to setup the
// rest of the screens. This way the LV heap stats represents
// all screens being loaded.
void setup_screens_ahead();
void loop();

}  // namespace screen_manager
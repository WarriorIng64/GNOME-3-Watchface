#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_time_layer_shadow;
static TextLayer *s_date_layer_shadow;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static GFont s_time_font;
static GFont s_date_font;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_time_buffer[6];
  static char s_date_buffer[25];
  strftime(s_time_buffer, sizeof(s_time_buffer), "%H:%M", tick_time);
  strftime(s_date_buffer, sizeof(s_date_buffer), "%A, %B %d", tick_time);
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer_shadow, s_time_buffer);
  text_layer_set_text(s_date_layer_shadow, s_date_buffer);
  text_layer_set_text(s_time_layer, s_time_buffer);
  text_layer_set_text(s_date_layer, s_date_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create GBitmap
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);

  // Create BitmapLayer to display the GBitmap
  s_background_layer = bitmap_layer_create(bounds);

  // Set the bitmap onto the layer and add to the window
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));

  // Create the TextLayer with specific bounds
  s_time_layer_shadow = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(68, 67), bounds.size.w, 45));
  s_date_layer_shadow = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(99, 96), bounds.size.w, 45));
  s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(70, 66), bounds.size.w, 45));
  s_date_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(98, 95), bounds.size.w, 45));

  // Font setup
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_CANTARELL_BOLD_20));
  s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_CANTARELL_BOLD_10));

  // Render text, shadow first
  text_layer_set_background_color(s_time_layer_shadow, GColorClear);
  text_layer_set_text_color(s_time_layer_shadow, GColorBlack);
  text_layer_set_font(s_time_layer_shadow, s_time_font);
  text_layer_set_text_alignment(s_time_layer_shadow, GTextAlignmentCenter);

  text_layer_set_background_color(s_date_layer_shadow, GColorClear);
  text_layer_set_text_color(s_date_layer_shadow, GColorBlack);
  text_layer_set_font(s_date_layer_shadow, s_date_font);
  text_layer_set_text_alignment(s_date_layer_shadow, GTextAlignmentCenter);

  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_font(s_date_layer, s_date_font);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);

  // Add child layers to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer_shadow));
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer_shadow));
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
}

static void main_window_unload(Window *window) {
  // Destroy TextLayers
  text_layer_destroy(s_time_layer_shadow);
  text_layer_destroy(s_date_layer_shadow);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);

  // Destroy GBitmap
  gbitmap_destroy(s_background_bitmap);

  // Destroy BitmapLayer
  bitmap_layer_destroy(s_background_layer);

  // Destroy custom fonts
  fonts_unload_custom_font(s_time_font);
  fonts_unload_custom_font(s_date_font);
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set Window background color
  window_set_background_color(s_main_window, GColorBlack);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);


  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Make sure the time is displayed from the start
  update_time();
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

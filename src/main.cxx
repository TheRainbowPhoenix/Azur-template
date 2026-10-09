#include <cstdint>
#include <gint/config.h>
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/prof.h>
#include <fxlibc/printf.h>
#include <azur/gint/render.h>
#include <azur/azur.h>

HHK_NAME("Azur Template")
HHK_AUTHOR("ClassPadDev")

static color_t color = C_RED;

constexpr uint_fast8_t RGB5_MAX = (1 << 5) - 1;
static uint_fast8_t red = RGB5_MAX;
static uint_fast8_t green = 0;
static uint_fast8_t blue = 0;

static int update(void)
{
    for(auto ev = pollevent(); ev.type != KEYEV_NONE; ev = pollevent()) {
        if(ev.type == KEYEV_UP && ev.key == KEY_EXIT) {
            return 1;
        }
    }

    if(red == RGB5_MAX && blue == 0) {
        green++;
    }
    if(green == RGB5_MAX && blue == 0) {
        red--;
    }
    if(green == RGB5_MAX && red == 0) {
        blue++;
    }
    if(blue == RGB5_MAX && red == 0) {
        green--;
    }
    if(blue == RGB5_MAX && green == 0) {
        red++;
    }
    if(red == RGB5_MAX && green == 0) {
        if(blue > 0) {
            blue--;
        }
        else {
            green++;
        }
    }

    color = C_RGB(red, green, blue);
    return 0;
}

static uint32_t last_cmdgen = 0;

static void renderer(void)
{
    azrp_clear(0xa534);

    azrp_triangle(
        azrp_width / 2 - 200 / 2, azrp_height / 2 - 200 / 2,
        azrp_width / 2 + 200 / 2, azrp_height / 2 - 200 / 2,
        azrp_width / 2 - 200 / 2, azrp_height / 2 + 200 / 2,
        color
    );

    azrp_print(3, 10, 0x3811, "cmdgen: %.3Dms", last_cmdgen);
    azrp_print(3, 25, 0x3811, "sort: %.3Dms", prof_time(azrp_perf_sort));
    azrp_print(3, 40, 0x3811, "shaders: %.3Dms", prof_time(azrp_perf_shaders));
    azrp_print(3, 55, 0x3811, "lcd: %.3Dms", prof_time(azrp_perf_lcd));
    azrp_print(3, 70, 0x3811, "render: %.3Dms", prof_time(azrp_perf_render));

    last_cmdgen = prof_time(azrp_perf_cmdgen);
    azrp_perf_clear();
    azrp_update();
}

int main(void)
{
    prof_init();
    __printf_enable_fixed();

    azrp_config_scale(1);
    azrp_cmdq_setup(AZRP_CMDQ_DEFAULT_INDEX_SIZE, AZRP_CMDQ_DEFAULT_DATA_SIZE);
    azrp_perf_clear();

    azur_main_loop(renderer, 30, update, 30, AZUR_MAIN_LOOP_TIED);
    return 0;
}


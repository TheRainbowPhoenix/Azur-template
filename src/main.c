#include <azur/gint/render.h>
#include <gint/display.h>
#include <gint/keyboard.h>

int main(void)
{
    azrp_config_scale(1);
    azrp_cmdq_setup(AZRP_CMDQ_DEFAULT_INDEX_SIZE, AZRP_CMDQ_DEFAULT_DATA_SIZE);

    azrp_clear(C_RGB(3, 4, 8));

    azrp_rect(20, 30, 180, 70, C_RGB(5, 20, 31));
    azrp_rect(30, 42, 160, 46, C_RGB(2, 8, 18));

    azrp_triangle(
        250, 55,
        305, 150,
        190, 165,
        C_RGB(31, 23, 5)
    );

    azrp_line(0, 0, 319, 527, C_WHITE);
    azrp_line(0, 527, 319, 0, C_WHITE);

    azrp_text(20, 220, C_WHITE, "Azur render demo");
    azrp_text(20, 240, C_RGB(31, 27, 8), "RGB555 colors, 320x528 screen");

    azrp_update();

    getkey();
    return 1;
}
#include <stdio.h>
#include <wchar.h>
#include <libds4/ds4.h>

int main(void)
{
    ds4_handle *handle = ds4_make_handle();
    if (!handle) {
        fprintf(stderr, "Error: Failed to initialize DS4 handle\n");
        return 1;
    }

    ds4_state state;
    while (1) {
        state = ds4_input_poll(handle);

        printf("\033[H\033[J");
        printf("--- DualShock 4 Debug ---\n");
        printf("Battery Level: %.1f%%\n", ds4_battery_level_percentage(&state));
        printf("Controller Temperature: %d\n", ds4_get_temperature(&state));
        printf("Headphones Present: %d\n", ds4_headphones_present(&state));
        printf("D-Pad State: %d\n", state.dpad_state);
        printf("Square Pressed: %d\n", ds4_btn_state(&state));
        printf("PS Button: %d\n", state.PS_Button);
        printf("Options: %d\n", state.Option);
        printf("Share: %d\n", state.Share);

        ds4_point leftstick = ds4_left_stick(&state);
        ds4_point rightstick = ds4_right_stick(&state);
        printf("L3 Stick: X: %3d  Y: %3d\n", leftstick.x, leftstick.y);
        printf("R3 Stick: X: %3d  Y: %3d\n", rightstick.x, rightstick.y);

        printf("R2 Pressed: %d\n", state.R2);
        printf("L2 Pressed: %d\n", state.L2);
        printf("R3 Pressed: %d\n", state.R3);
        printf("TouchPad Pressed: %d\n", state.TouchPad_click);
        printf("R2 Analog: %d\n", state.r2analog);
        printf("L2 Analog: %d\n", state.l2analog);
        printf("Packet Counter: %d\n", state.packet_counter);
    }

    ds4_destroy_handle(handle);
    return 0;
}
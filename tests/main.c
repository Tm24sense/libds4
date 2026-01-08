#include <libds4/ds4.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    ds4_handle *handle = ds4_make_handle();

    while (1)
    {
        ds4_input_report input_report = ds4_read_ireport(handle);
        ds4_state state = ds4_parse_state(&input_report);

        // "\033[H\033[J" is a magic string that clears the terminal screen
        printf("\033[H\033[J");

        printf("--- DualShock 4 Debug ---\n");
        printf("Battery Level: %d/11\n", state.battery_level);
        printf("Status: %s %s\n",
               state.is_plugged ? "[WIRED]" : "[WIRELESS]",
               state.battery_level ? "(CHARGING...)" : "");
        printf("Controller temprature: %d\n", state.Temprature);
        printf("HeadPhones present: %d\n", state.headphones);
        printf("D-Pad State: %d\n", state.dpad_state);
        printf("is square pressed:     %d\n", state.faceButtons);
        printf("Ps button:  %d\n", state.PS_Button);
        printf("Options:    %d\n", state.Option);
        printf("share:      %d\n", state.Share);
        printf("L3 Stick:    X: %3d  Y: %3d\n", state.leftstickX, state.leftstickY);
        printf("R3 Stick:    X: %3d  Y: %3d\n", state.rightstickX, state.rightstickY);
        printf("R2 pressed: %d\n", state.R2);
        printf("L2 pressed: %d\n", state.L2);
        printf("R3 pressed: %d\n", state.R3);
        printf("TouchPad pressed: %d\n", state.TouchPad_click);
        printf("R2_Analog: %d\n", state.r2analog);
        printf("L2_Analog: %d\n", state.l2analog);
        printf("packet counter: %d\n", state.packet_counter);
    }

    wprintf(L"%ls\n", handle->serial_number);
}
#include <libds4/ds4.h>
#include <stdio.h>
int main()
{
    ds4_handle *device = ds4_open_device();
    ds4_state state;
    if(device == NULL)
    {
        printf("controller not found\n");
        return 0;
    }
    uint8_t combo[] = {DS_BTN_Circle, DS_BTN_Cross};
    int running = 1;
    while (running)
    {
        state = ds4_update(device);
        if(ds4_buttons_pressed(&state, combo, sizeof(combo)))
        {
            ds4_destroy_handle(device);
            running = false;
        }
        else if(ds4_button_pressed(&state, DS_BTN_Share))
        {
                printf("Share button has been pressed\n");
                ds4_destroy_handle(device);
                running = false;
        }
    }
}
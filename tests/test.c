#include <libds4/ds4.h>
#include <stdio.h>
int main()
{
    ds4_handle *device = ds4_make_handle();
    int running = 1;
    while (running)
    {

        ds4_state state = ds4_input_poll(device);
        if(ds4_btn_pressed(&state, DS_BTN_Circle))
        {
            printf("Circle button has been pressed!!!\n");
            ds4_destroy_handle(device);
            running = false;
        }
        else if(ds4_btn_pressed(&state, DS_BTN_Share))
        {
                printf("Share button has been pressed\n");
                ds4_destroy_handle(device);
                running = false;
        }
    }
}
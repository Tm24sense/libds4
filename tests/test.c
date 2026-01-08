#include <libds4/ds4.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
int main()
{
    ds4_handle *handle = ds4_make_handle();
    if (!handle) {
        fprintf(stderr, "No controller found; exiting.\n");
        return 1;
    }
    ds4_state previous_state = {0};

    while (true)
    {
        ds4_input_report input_report = ds4_read_ireport(handle);
        ds4_state current_state = ds4_parse_state(&input_report);

        // Check rising edges for buttons
        if (ds4_btn_pressed(&current_state, DS_BTN_Square) &&
            !ds4_btn_pressed(&previous_state, DS_BTN_Square))
        {
            printf("Square pressed!\n");
            break; // exit if desired
        }

        if (ds4_btn_pressed(&current_state, DS_BTN_Cross) &&
            !ds4_btn_pressed(&previous_state, DS_BTN_Cross))
        {
            printf("Cross pressed!\n");
        }
        previous_state = current_state;

    }
}
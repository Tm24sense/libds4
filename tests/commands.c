#include <libds4/ds4.h>
//vibrates controller at max strenght and change led to red and keep flashing it

int main()
{
    ds4_handle *device = ds4_make_handle();
    ds4_message message = ds4_begin_message();
    ds4_set_vibration(&message, 255, 255);
    ds4_enable_flash(&message, 255, 255, true);
    ds4_set_led(&message, 255, 0, 0);
    ds4_send_commands(device, &message);
    ds4_destroy_handle(device);
}
#include <libds4/ds4.h>
#include <stdio.h>
int main()
{
    ds4_handle *device = ds4_make_handle();
    ds4_message message = ds4_begin_message();
    int stren;
    int r, g,b;
    if(device == NULL)
    {
        printf("device not found\n");
        return -1;
    }
    printf("Device Model: %d\n", ds4_get_model(device));
    printf("enter strenght of vibration 0 weak and 255 very strong: ");
    scanf("%d", &stren);
    printf("enter color R:");
    scanf("%d", &r);
    printf("enter color G: ");
    scanf("%d", &g);
    printf("enter color B: ");
    scanf("%d", &b);

    while(1)
    {

    
    ds4_set_vibration(&message, stren, stren);
    ds4_set_led(&message, r, g, b);
    ds4_send_commands(device, &message);
    
    }
    ds4_destroy_handle(device);
}
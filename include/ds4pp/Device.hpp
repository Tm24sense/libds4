extern "C"
{
    #include <ds4/ds4.h>
}

enum class Button
{
    SQUARE = 16,
    CROSS = 32,
    CIRCLE = 64,
    TRIANGLE = 128,
    L1,
    R1,
    L2,
    R2,
    Share,
    Option,
    L3,
    R3,
    Touchpad,
    None
};


namespace DS4
{
    class DualShock4
    {
        public:
            DualShock4();
            ~DualShock4();
            bool IsButtonPressed(DS4_Buttons Button);
            void Update();
            
        private:
            ds4_handle* handle;
            ds4_state state;
    };
};
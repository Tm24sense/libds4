#include <iostream>
#include <vector>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>


extern "C" {
    #include <ds4/ds4.h>
}

int main() {
   
    if (!glfwInit()) {
        return 1;
    }

    
    GLFWwindow* window = glfwCreateWindow(1280, 720, "libds4 - ImGui Debug Menu", NULL, NULL);
    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 

    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    
    ds4_handle* handle = ds4_open_device();
    if (!handle) {
        std::cerr << "Error: Could not find DualShock 4 Controller!" << std::endl;
        
    }

    
    std::vector<float> packet_history(100, 0.0f);
    ds4_state state;

    
    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();

        // Update DS4 Data
        if (handle) {
            state = ds4_update(handle);
        }

        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        
        ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Controller Debugger");

        if (!handle) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "STATUS: Controller Disconnected");
            if (ImGui::Button("Retry Connection")) {
                handle = ds4_open_device();
            }
        } else {
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "STATUS: Connected");

            
            if (ImGui::CollapsingHeader("Power & Thermal", ImGuiTreeNodeFlags_DefaultOpen)) {
                float battery = ds4_battery_level_percentage(&state);
                ImGui::ProgressBar(battery / 100.0f, ImVec2(-1, 0), "Battery %");
                ImGui::Text("Temperature: %d", ds4_get_temperature(&state));
            }

            
            if (ImGui::CollapsingHeader("Analog Inputs", ImGuiTreeNodeFlags_DefaultOpen)) {
                ds4_point left = ds4_left_stick(&state);
                ds4_point right = ds4_right_stick(&state);

                ImGui::Columns(2, "StickCols");
                ImGui::Text("Left Stick");
                ImGui::BulletText("X: %d", left.x);
                ImGui::BulletText("Y: %d", left.y);
                ImGui::NextColumn();
                ImGui::Text("Right Stick");
                ImGui::BulletText("X: %d", right.x);
                ImGui::BulletText("Y: %d", right.y);
                ImGui::Columns(1);

                ImGui::Separator();
                int l2 = state.l2analog;
                int r2 = state.r2analog;
                ImGui::SliderInt("L2 Pressure", &l2, 0, 255);
                ImGui::SliderInt("R2 Pressure", &r2, 0, 255);
            }

            
            if (ImGui::CollapsingHeader("Communication Metrics", ImGuiTreeNodeFlags_DefaultOpen)) {
                
                if (packet_history.size() >= 100) {
                    packet_history.erase(packet_history.begin());
                }
                packet_history.push_back((float)state.packet_counter);

                ImGui::Text("Last Packet Index: %d", state.packet_counter);
                ImGui::PlotLines("##PacketGraph", packet_history.data(), (int)packet_history.size(), 
                                 0, "Packet Counter Over Time", 0.0f, 255.0f, ImVec2(-1, 100));
            }

            if (ImGui::CollapsingHeader("Digital Buttons")) {
                ImGui::Text("D-Pad: %d", state.dpad_state);
                ImGui::Checkbox("PS Button", (bool*)&state.PS_Button);
                ImGui::Checkbox("Options", (bool*)&state.Option);
                ImGui::Checkbox("Share", (bool*)&state.Share);
                ImGui::Checkbox("Touch Click", (bool*)&state.TouchPad_click);
            }
        }

        ImGui::End();
        
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.15f, 0.15f, 0.15f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    
    if (handle) ds4_destroy_handle(handle);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
﻿#include "gConsole.h"
#include "gCore.h"


void Console::DrawConsole()
{

    int w, h;
    WindowScale(window, &w, &h);

    // int panelHeight = std::max(h - 2500, 150);

    DrawPanel("Console", ImVec2(0, h / 1.651), ImVec2(w / 7, 515), [&]()
        {

            static char inputBuffer[256] = "";
            static std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-";

            const auto& logs = LOG.GetLogs();
            ImGui::BeginChild("ConsoleScrollingRegion", ImVec2(0, -ImGui::GetTextLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
            static ImVec4 textColor;
            for (const auto& log : logs) {

                switch (log.level) {
                case Logger::LogLevel::Error:
                    textColor = ImVec4(1, 0, 0, 1); // Красный для ошибок
                    ImGui::TextColored(textColor, "[ERROR] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::Warning:
                    textColor = ImVec4(1, 1, 0, 1); // Желтый для предупреждений
                    ImGui::TextColored(textColor, "[WARNING] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::Info:
                    textColor = ImVec4(0, 1, 0, 1); // Зеленый для информации
                    ImGui::TextColored(textColor, "[INFO] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::Debug:
                    textColor = ImVec4(0, 1, 1, 1); // Бирюзовый для отладочной информации
                    ImGui::TextColored(textColor, "[DEBUG] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::Input:
                    textColor = ImVec4(0.5f, 0.5f, 1, 1); // Фиолетовый для уровня INPUT
                    ImGui::TextColored(textColor, "[INPUT] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::Clear:
                    textColor = ImVec4(1, 1, 1, 1); // Белый для уровня CLEAR
                    ImGui::TextColored(textColor, "[CLEAR] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::Destroy:
                    textColor = ImVec4(0.7f, 0.7f, 0.7f, 1); // Серый для уровня DESTROY
                    ImGui::TextColored(textColor, "[DESTROY] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::Save:
                    textColor = ImVec4(0, 0.5f, 1, 1); // Синий для уровня SAVE
                    ImGui::TextColored(textColor, "[SAVE] %s", log.message.c_str());
                    break;
                case Logger::LogLevel::Load:
                    textColor = ImVec4(0.5f, 0, 0.5f, 1); // Фиолетовый для уровня LOAD
                    ImGui::TextColored(textColor, "[LOAD] %s", log.message.c_str());
                    break;
                }
            }

            ImGui::EndChild();

            ImGui::Separator();



            ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCharFilter;


            if (ImGui::InputText("Input", inputBuffer, IM_ARRAYSIZE(inputBuffer), flags,
                [](ImGuiInputTextCallbackData* data) -> int
                {
                    if (allowedChars.find(data->EventChar) != std::string::npos)
                        return 0;
                    else
                        return 0;
                }))
            {
                if (strcmp(inputBuffer, "EditorMode") == 0) {
                    EditorMode = !EditorMode;
                    LOG.Log(Logger::LogLevel::Info, "Editor mode is ", NULL);
                }
                else if (strcmp(inputBuffer, "EditorModeOn") == 0) {
                    if (!EditorMode) {
                        EditorMode = true;
                        LOG.Log(Logger::LogLevel::Info, "Editor mode is ON", NULL);
                    }
                }
                else if (strcmp(inputBuffer, "EditorModeOff") == 0) {
                    if (EditorMode) {
                        EditorMode = false;
                        LOG.Log(Logger::LogLevel::Info, "Editor mode is OFF", NULL);
                    }
                }
                else {
                    bool isNumber = true;
                    for (int i = 0; inputBuffer[i] != '\0'; i++) {
                        if (!isdigit(inputBuffer[i]) && inputBuffer[i] != '.' && inputBuffer[i] != '-') {
                            isNumber = false;
                            break;
                        }
                    }

                    if (isNumber) {
                        double inputValue = std::stod(inputBuffer);
                        LOG.Log(Logger::LogLevel::Info, "Input (number): ", inputValue);
                    }
                    else {
                        LOG.Log(Logger::LogLevel::Info, inputBuffer, NULL);
                    }
                }

                memset(inputBuffer, 0, sizeof(inputBuffer));

            }





        });
}

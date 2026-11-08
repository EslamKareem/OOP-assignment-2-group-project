// gui_main.cpp
//
// Vole Machine Simulator — Bonus GUI frontend
// Framework: Dear ImGui + SDL2 + OpenGL 3 (cross-platform: Windows / Linux)
//
// IMPORTANT: This is strictly a frontend. It instantiates our Machine object and
// only calls its public methods (machine.step(), machine.run(), machine.loadProgram(),
// machine.reset()) and observes state through the public getters. No backend logic
// is modified here.
//
// Visual direction: Nordic theme (polar-night dark background, snow-storm
// foreground, frost accents), generous spacing, clear visual hierarchy.

#include "machine.h"
#include "Programs.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>

namespace {

// ---------------------------------------------------------------------------
// Nordic color palette (https://www.nordtheme.com)
// ---------------------------------------------------------------------------
struct Nord {
    static const ImVec4 night0; // #2E3440  background
    static const ImVec4 night1; // #3B4252  panel / surface
    static const ImVec4 night2; // #434C5E  hover / input
    static const ImVec4 night3; // #4C566A  border / muted
    static const ImVec4 snow0;  // #ECEFF4  primary text
    static const ImVec4 snow1;  // #D8DEE9  secondary text
    static const ImVec4 snow2;  // #E5E9F0  bright text
    static const ImVec4 frost0; // #8FBCBB  accent (teal)
    static const ImVec4 frost1; // #88C0D0  accent (cyan) — primary
    static const ImVec4 frost2; // #81A1C1  accent (blue)
    static const ImVec4 frost3; // #5E81AC  accent (dark blue)
    static const ImVec4 auroraRed;   // #BF616A
    static const ImVec4 auroraGreen; // #A3BE8C
    static const ImVec4 auroraYellow;// #EBCB8B
};

const ImVec4 Nord::night0 = ImVec4(0.180f, 0.204f, 0.251f, 1.00f);
const ImVec4 Nord::night1 = ImVec4(0.231f, 0.259f, 0.322f, 1.00f);
const ImVec4 Nord::night2 = ImVec4(0.263f, 0.298f, 0.369f, 1.00f);
const ImVec4 Nord::night3 = ImVec4(0.298f, 0.337f, 0.416f, 1.00f);
const ImVec4 Nord::snow0  = ImVec4(0.925f, 0.937f, 0.957f, 1.00f);
const ImVec4 Nord::snow1  = ImVec4(0.847f, 0.871f, 0.914f, 1.00f);
const ImVec4 Nord::snow2  = ImVec4(0.898f, 0.914f, 0.941f, 1.00f);
const ImVec4 Nord::frost0 = ImVec4(0.561f, 0.737f, 0.733f, 1.00f);
const ImVec4 Nord::frost1 = ImVec4(0.533f, 0.753f, 0.816f, 1.00f);
const ImVec4 Nord::frost2 = ImVec4(0.506f, 0.631f, 0.757f, 1.00f);
const ImVec4 Nord::frost3 = ImVec4(0.369f, 0.506f, 0.678f, 1.00f);
const ImVec4 Nord::auroraRed = ImVec4(0.749f, 0.380f, 0.416f, 1.00f);
const ImVec4 Nord::auroraGreen = ImVec4(0.639f, 0.745f, 0.549f, 1.00f);
const ImVec4 Nord::auroraYellow = ImVec4(0.922f, 0.796f, 0.545f, 1.00f);

const char* opcodeName(Opcode o) {
    switch (o) {
        case Opcode::LOAD_MEM:  return "LOAD_MEM";
        case Opcode::LOAD_IMM:  return "LOAD_IMM";
        case Opcode::STORE:     return "STORE";
        case Opcode::MOVE:      return "MOVE";
        case Opcode::ADD_INT:   return "ADD_INT";
        case Opcode::ADD_FLOAT: return "ADD_FLOAT";
        case Opcode::OR_OP:     return "OR";
        case Opcode::AND_OP:    return "AND";
        case Opcode::XOR_OP:    return "XOR";
        case Opcode::ROTATE:    return "ROTATE";
        case Opcode::JUMP_EQ:      return "JUMP_EQ";
        case Opcode::HALT:      return "HALT";
        default:                return "UNKNOWN";
    }
}

std::string hex8(int v) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
        << (static_cast<unsigned int>(v) & 0xFFu) << std::dec;
    return oss.str();
}

std::string hex16(uint16_t v) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
        << static_cast<unsigned int>(v) << std::dec;
    return std::string(oss.str());
}

std::string bin8(int v) {
    std::ostringstream oss;
    unsigned int x = static_cast<unsigned int>(v) & 0xFFu;
    for (int b = 7; b >= 0; --b)
        oss << ((x >> b) & 1u);
    return oss.str();
}

std::string bin16(uint16_t v) {
    std::ostringstream oss;
    for (int b = 15; b >= 0; --b)
        oss << ((v >> b) & 1u);
    return oss.str();
}

char asciiChar(int v) {
    unsigned int x = static_cast<unsigned int>(v) & 0xFFu;
    if (x >= 32 && x <= 126)
        return static_cast<char>(x);
    return '.';
}

void applyNordicTheme() {
    ImGuiStyle& s = ImGui::GetStyle();
    s.WindowPadding = ImVec2(12, 12);
    s.FramePadding = ImVec2(8, 6);
    s.ItemSpacing = ImVec2(8, 8);
    s.ItemInnerSpacing = ImVec2(6, 4);
    s.TouchExtraPadding = ImVec2(0, 0);
    s.IndentSpacing = 16;
    s.ScrollbarSize = 12;
    s.ScrollbarRounding = 6;
    s.GrabMinSize = 14;
    s.WindowRounding = 10;
    s.ChildRounding = 8;
    s.FrameRounding = 6;
    s.PopupRounding = 8;
    s.TabRounding = 6;
    s.GrabRounding = 6;
    s.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    s.DisplayWindowPadding = ImVec2(20, 20);
    s.DisplaySafeAreaPadding = ImVec2(4, 4);
    s.AntiAliasedLines = true;
    s.AntiAliasedFill = true;
    s.CurveTessellationTol = 1.25f;

    ImVec4* c = s.Colors;
    c[ImGuiCol_Text]               = Nord::snow0;
    c[ImGuiCol_TextDisabled]       = Nord::night3;
    c[ImGuiCol_WindowBg]           = Nord::night0;
    c[ImGuiCol_ChildBg]            = Nord::night1;
    c[ImGuiCol_PopupBg]            = Nord::night1;
    c[ImGuiCol_Border]             = Nord::night3;
    c[ImGuiCol_BorderShadow]       = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_FrameBg]            = Nord::night1;
    c[ImGuiCol_FrameBgHovered]     = Nord::night2;
    c[ImGuiCol_FrameBgActive]      = Nord::frost3;
    c[ImGuiCol_TitleBg]            = Nord::night1;
    c[ImGuiCol_TitleBgActive]      = Nord::frost3;
    c[ImGuiCol_TitleBgCollapsed]   = Nord::night1;
    c[ImGuiCol_MenuBarBg]          = Nord::night1;
    c[ImGuiCol_ScrollbarBg]        = Nord::night1;
    c[ImGuiCol_ScrollbarGrab]      = Nord::night3;
    c[ImGuiCol_ScrollbarGrabHovered]= Nord::frost0;
    c[ImGuiCol_ScrollbarGrabActive] = Nord::frost1;
    c[ImGuiCol_CheckMark]          = Nord::frost1;
    c[ImGuiCol_SliderGrab]         = Nord::frost1;
    c[ImGuiCol_SliderGrabActive]   = Nord::frost2;
    c[ImGuiCol_Button]             = Nord::night2;
    c[ImGuiCol_ButtonHovered]      = Nord::frost1;
    c[ImGuiCol_ButtonActive]       = Nord::frost2;
    c[ImGuiCol_Header]             = Nord::night2;
    c[ImGuiCol_HeaderHovered]      = ImVec4(Nord::frost1.x, Nord::frost1.y, Nord::frost1.z, 0.25f);
    c[ImGuiCol_HeaderActive]       = ImVec4(Nord::frost1.x, Nord::frost1.y, Nord::frost1.z, 0.40f);
    c[ImGuiCol_Separator]          = Nord::night3;
    c[ImGuiCol_SeparatorHovered]   = Nord::frost0;
    c[ImGuiCol_SeparatorActive]    = Nord::frost1;
    c[ImGuiCol_ResizeGrip]         = ImVec4(Nord::frost3.x, Nord::frost3.y, Nord::frost3.z, 0.20f);
    c[ImGuiCol_ResizeGripHovered]  = ImVec4(Nord::frost3.x, Nord::frost3.y, Nord::frost3.z, 0.40f);
    c[ImGuiCol_ResizeGripActive]   = ImVec4(Nord::frost3.x, Nord::frost3.y, Nord::frost3.z, 0.60f);
    c[ImGuiCol_Tab]                = Nord::night1;
    c[ImGuiCol_TabHovered]         = Nord::night2;
    c[ImGuiCol_TabSelected]        = ImVec4(Nord::frost1.x, Nord::frost1.y, Nord::frost1.z, 0.15f);
    c[ImGuiCol_TabDimmed]          = Nord::night1;
    c[ImGuiCol_TabDimmedSelected]  = ImVec4(Nord::frost1.x, Nord::frost1.y, Nord::frost1.z, 0.10f);
    c[ImGuiCol_PlotLines]          = Nord::frost0;
    c[ImGuiCol_PlotLinesHovered]   = Nord::frost1;
    c[ImGuiCol_PlotHistogram]      = Nord::frost1;
    c[ImGuiCol_PlotHistogramHovered]= Nord::frost2;
    c[ImGuiCol_TableHeaderBg]      = Nord::night2;
    c[ImGuiCol_TableBorderStrong]  = Nord::night3;
    c[ImGuiCol_TableBorderLight]   = Nord::night3;
    c[ImGuiCol_TableRowBg]         = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_TableRowBgAlt]      = ImVec4(Nord::night3.x, Nord::night3.y, Nord::night3.z, 0.08f);
    c[ImGuiCol_TextSelectedBg]     = ImVec4(Nord::frost1.x, Nord::frost1.y, Nord::frost1.z, 0.35f);
    c[ImGuiCol_DragDropTarget]     = Nord::frost1;
    c[ImGuiCol_NavHighlight]       = ImVec4(Nord::frost1.x, Nord::frost1.y, Nord::frost1.z, 0.60f);
    c[ImGuiCol_NavWindowingHighlight] = ImVec4(Nord::frost1.x, Nord::frost1.y, Nord::frost1.z, 0.70f);
    c[ImGuiCol_NavWindowingDimBg]  = ImVec4(0.10f, 0.10f, 0.10f, 0.58f);
    c[ImGuiCol_ModalWindowDimBg]   = ImVec4(0.10f, 0.10f, 0.10f, 0.58f);
}

} // namespace

int main(int /*argc*/, char** /*argv*/) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window* window = SDL_CreateWindow("Machine Language — Vole Simulator",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1400, 800,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        SDL_Log("Failed to create SDL window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        SDL_Log("Failed to create OpenGL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    applyNordicTheme();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    Machine machine;

    bool autoRun = false;
    int stepDelayMs = 100;
    Uint32 lastStepTick = 0;
    bool halted = false;

    std::string screenText;
    size_t lastScreenCount = 0;
    bool scrollScreen = true;

    std::vector<int> lastProgram;
    bool hasProgram = false;

    // Manual memory store state (like the reference "Store in Memory" panel)
    char memAddrBuf[16] = "0";
    char memContentBuf[256] = "";

    auto clearScreenDisplay = [&]() {
        machine.getScreen().clear();
        screenText.clear();
        lastScreenCount = 0;
        scrollScreen = true;
    };

    auto refreshScreen = [&]() {
        const auto& out = machine.getScreen().getOutput();
        if (out.size() > lastScreenCount) {
            std::ostringstream oss;
            for (size_t i = lastScreenCount; i < out.size(); ++i) {
                oss << "[" << std::setw(3) << std::setfill('0') << i << "]  "
                    << hex8(out[i]) << "  '" << asciiChar(out[i]) << "'\n";
            }
            screenText += oss.str();
            lastScreenCount = out.size();
            scrollScreen = true;
        }
    };

    auto loadProgram = [&](const std::vector<int>& prog) {
        machine.reset();
        machine.loadProgram(prog);
        lastProgram = prog;
        hasProgram = true;
        clearScreenDisplay();
        refreshScreen();
        halted = machine.getCPU().isHalted();
        autoRun = false;
    };

    auto doManualStore = [&]() {
        int startAddr = 0;
        std::istringstream iss(memAddrBuf);
        iss >> startAddr;
        if (iss.fail()) startAddr = 0;
        startAddr &= 0xFF;

        std::istringstream css(memContentBuf);
        std::string token;
        int addr = startAddr;
        while (css >> token) {
            int val = 0;
            std::istringstream tiss(token);
            if (token.size() > 2 && token[0] == '0' && (token[1] == 'x' || token[1] == 'X'))
                tiss >> std::hex >> val;
            else
                tiss >> val;
            if (!tiss.fail()) {
                machine.getMemory().write(addr, val & 0xFF);
                refreshScreen();
            }
            addr = (addr + 1) & 0xFF;
            if (addr == 0) break; // don't wrap past screen
        }
        halted = machine.getCPU().isHalted();
    };

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(window))
                running = false;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // ===================================================================
        // Three-panel layout matching the reference design
        // ===================================================================
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::Begin("##main", nullptr,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_NoBringToFrontOnFocus);

        const ImVec2 winSize = io.DisplaySize;
        const float panelW = (winSize.x - 48) / 3.0f; // three equal panels with gaps
        const float gap = 16.0f;

        // ---- Panel 1: Execution (left) ----
        ImGui::BeginChild("exec_panel", ImVec2(panelW, winSize.y - 56), true);
        {
            ImGui::TextColored(Nord::frost1, "Execution");
            ImGui::Spacing();

            ImGui::TextColored(Nord::snow1, "Counter");
            ImGui::Spacing();
            ImGui::TextColored(Nord::snow2, "%s", hex8(machine.getCPU().getProgramCounter()).c_str());
            ImGui::Spacing();

            bool stepClicked = ImGui::Button("Run", ImVec2((panelW - 10) * 0.5f, 32));
            ImGui::SameLine();
            bool stopClicked = ImGui::Button("Stop", ImVec2(0, 32));
            if (stepClicked) {
                autoRun = true;
                lastStepTick = SDL_GetTicks();
            }
            if (stopClicked) {
                autoRun = false;
            }
            (void)stepClicked; // used by Run button above
            ImGui::Spacing();

            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextColored(Nord::snow1, "Load Program");
            ImGui::Spacing();
            if (ImGui::Button("Load Sample Program 1", ImVec2(-1, 32)))
                loadProgram(Programs::program1());
            ImGui::Dummy(ImVec2(0, 6));
            if (ImGui::Button("Load Sample Program 2", ImVec2(-1, 32)))
                loadProgram(Programs::program2());
            ImGui::Spacing();

            ImGui::TextColored(Nord::snow1, "Screen");
            ImGui::TextColored(Nord::snow0, "ASCII text stored in memory cell at address 00");
            ImGui::Spacing();

            ImGui::PushItemWidth(-1);
            static char screenBuf[256] = "";
            ImGui::InputText("##screen", screenBuf, IM_ARRAYSIZE(screenBuf),
                             ImGuiInputTextFlags_ReadOnly);
            ImGui::PopItemWidth();
            ImGui::Spacing();

            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextColored(Nord::snow1, "Store in Memory");
            ImGui::Spacing();

            ImGui::TextColored(Nord::snow1, "Start Address");
            ImGui::PushItemWidth(-1);
            ImGui::InputText("##memaddr", memAddrBuf, IM_ARRAYSIZE(memAddrBuf));
            ImGui::PopItemWidth();
            ImGui::Spacing();

            ImGui::TextColored(Nord::snow1, "Content");
            ImGui::PushItemWidth(-1);
            ImGui::InputText("##memcontent", memContentBuf, IM_ARRAYSIZE(memContentBuf));
            ImGui::PopItemWidth();
            ImGui::Spacing();

            if (ImGui::Button("Store", ImVec2(-1, 32))) {
                doManualStore();
            }
            ImGui::Spacing();
            if (ImGui::Button("Reset", ImVec2(-1, 32))) {
                if (hasProgram) {
                    machine.reset();
                    machine.loadProgram(lastProgram);
                    clearScreenDisplay();
                    refreshScreen();
                } else {
                    machine.reset();
                    clearScreenDisplay();
                }
                halted = machine.getCPU().isHalted();
                autoRun = false;
            }
            ImGui::Spacing();

            ImGui::Separator();
            ImGui::Spacing();

            ImVec4 statusColor = halted ? Nord::auroraRed : Nord::auroraGreen;
            const char* statusText = halted ? "HALTED" : "RUNNING";
            ImGui::TextColored(statusColor, "Status:  %s", statusText);
            ImGui::TextColored(Nord::snow1, "Program:   %s", hasProgram ? "loaded" : "none");
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            if (ImGui::Button("Exit", ImVec2(-1, 32))) {
                running = false;
            }
        }
        ImGui::EndChild();

        ImGui::SameLine(0, gap);

        // ---- Panel 2: Registers (CPU) (middle) ----
        ImGui::BeginChild("reg_panel", ImVec2(panelW, winSize.y - 56), true);
        {
            ImGui::TextColored(Nord::frost1, "Registers (CPU)");
            ImGui::Spacing();

            const CPU& cpu = machine.getCPU();
            const auto& ir = cpu.getInstructionRegister();
            int pc = machine.getCPU().getProgramCounter();

            ImGui::TextColored(Nord::snow1, "Program Counter:");
            ImGui::SameLine();
            ImGui::TextColored(Nord::snow2, "%s", hex8(pc).c_str());

            if (halted)
                ImGui::SameLine();
            {
                ImVec4 badgeColor = halted ? Nord::auroraRed : Nord::auroraGreen;
                const char* badgeText = halted ? "HALTED" : "RUNNING";
                ImGui::PushStyleColor(ImGuiCol_Text, Nord::snow0);
                ImGui::PushStyleColor(ImGuiCol_Button, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, badgeColor);
                ImGui::Button(badgeText, ImVec2(56, 20));
                ImGui::PopStyleColor(4);
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            // Instruction Register
            ImGui::TextColored(Nord::snow1, "Instruction Register:");
            ImGui::Spacing();
            if (ir.has_value()) {
                const Instruction& ins = ir.value();
                ImGui::Text("  raw  : %s", hex16(ins.getRaw()).c_str());
                ImGui::SameLine(180);
                ImGui::TextColored(Nord::frost0, "%s", bin16(ins.getRaw()).c_str());
                ImGui::Text("  op   : %s", opcodeName(ins.getOpcode()));
                ImGui::SameLine(180);
                ImGui::Text("r    : %d", ins.getR());
                ImGui::Text("  s    : %d", ins.getS());
                ImGui::SameLine(180);
                ImGui::Text("t    : %d", ins.getT());
                ImGui::Text("  xy   : %d", ins.getXY());
                ImGui::SameLine(180);
            } else {
                ImGui::TextColored(Nord::night3, "  (none)");
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            // Register file table: Address | Binary | Hexadecimal
            ImGui::TextColored(Nord::snow1, "Register File:");
            ImGui::Spacing();
            const RegisterFile& regs = machine.getRegisters();
            if (ImGui::BeginTable("registers", 3,
                                  ImGuiTableFlags_BordersInnerV |
                                      ImGuiTableFlags_RowBg |
                                      ImGuiTableFlags_SizingStretchProp |
                                      ImGuiTableFlags_NoBordersInBody)) {
                ImGui::TableSetupColumn("Address", ImGuiTableColumnFlags_WidthFixed, 60);
                ImGui::TableSetupColumn("Binary", ImGuiTableColumnFlags_WidthFixed, 96);
                ImGui::TableSetupColumn("Hexadecimal", ImGuiTableColumnFlags_WidthFixed, 96);
                ImGui::TableHeadersRow();
                for (int i = 0; i < 16; ++i) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextColored(Nord::snow1, "R%X", i);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::TextColored(Nord::frost0, "%s", bin8(regs.read(i)).c_str());
                    ImGui::TableSetColumnIndex(2);
                    ImGui::TextColored(Nord::snow0, "%s", hex8(regs.read(i)).c_str());
                }
                ImGui::EndTable();
            }
        }
        ImGui::EndChild();

        ImGui::SameLine(0, gap);

        // ---- Panel 3: Memory (right) ----
        ImGui::BeginChild("mem_panel", ImVec2(panelW, winSize.y - 56), true);
        {
            ImGui::TextColored(Nord::frost1, "Memory");
            ImGui::Spacing();

            const Memory& mem = machine.getMemory();
            ImGui::BeginChild("mem_scroll", ImVec2(0, 0), true);
            {
                if (ImGui::BeginTable("memory", 4,
                                      ImGuiTableFlags_BordersInnerV |
                                          ImGuiTableFlags_RowBg |
                                          ImGuiTableFlags_SizingFixedFit |
                                          ImGuiTableFlags_NoBordersInBody |
                                          ImGuiTableFlags_ScrollY)) {
                    ImGui::TableSetupColumn("Address", ImGuiTableColumnFlags_WidthFixed, 56);
                    ImGui::TableSetupColumn("Binary", ImGuiTableColumnFlags_WidthFixed, 96);
                    ImGui::TableSetupColumn("Hexadecimal", ImGuiTableColumnFlags_WidthFixed, 96);
                    ImGui::TableSetupColumn("ASCII", ImGuiTableColumnFlags_WidthFixed, 40);
                    ImGui::TableHeadersRow();

                    for (int row = 0; row < 32; ++row) {
                        int base = row * 8;
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);
                        bool screenAddr = (base == 0);
                        if (screenAddr)
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg,
                                                   ImGui::ColorConvertFloat4ToU32(
                                                       ImVec4(Nord::auroraGreen.x, Nord::auroraGreen.y,
                                                              Nord::auroraGreen.z, 0.15f)));
                        ImGui::TextColored(Nord::night3, "0x%02X", base);

                        for (int b = 0; b < 8; ++b) {
                            int addr = base + b;
                            uint8_t v = static_cast<uint8_t>(mem.read(addr));
                            bool isScreenAddr = (addr == 0);

                            ImGui::TableSetColumnIndex(1);
                            if (isScreenAddr)
                                ImGui::TextColored(Nord::auroraGreen, "%s", bin8(v).c_str());
                            else
                                ImGui::TextColored(Nord::snow0, "%s", bin8(v).c_str());

                            ImGui::TableSetColumnIndex(2);
                            if (isScreenAddr)
                                ImGui::TextColored(Nord::auroraGreen, "%s", hex8(v).c_str());
                            else
                                ImGui::TextColored(Nord::snow0, "%s", hex8(v).c_str());

                            ImGui::TableSetColumnIndex(3);
                            if (isScreenAddr)
                                ImGui::TextColored(Nord::auroraGreen, "%c", asciiChar(v));
                            else
                                ImGui::TextColored(Nord::night3, "%c", asciiChar(v));
                        }
                    }
                    ImGui::EndTable();
                }
            }
            ImGui::EndChild();

            ImGui::Spacing();
            ImGui::TextColored(Nord::night3,
                               "Address 0x00 (green) is memory-mapped to the Screen output device.");
        }
        ImGui::EndChild();

        ImGui::End();

        // ---- Attribution footer ----
        {
            ImGui::SetCursorPosY(winSize.y - 26);
            ImGui::Separator();
            ImGui::TextColored(Nord::night3, "Made by Islam Karim  |  Cairo University — Faculty of Computers and Artificial Intelligence  |  CS111");
        }

        // ===================== Auto-run (Step loop) =====================
        if (autoRun && !halted) {
            Uint32 now = SDL_GetTicks();
            if (now - lastStepTick >= static_cast<Uint32>(stepDelayMs)) {
                machine.step();
                refreshScreen();
                halted = machine.getCPU().isHalted();
                if (halted)
                    autoRun = false;
                lastStepTick = now;
            }
        }

        // ===================== Render =====================
        ImGui::Render();
        int display_w = 0, display_h = 0;
        SDL_GL_GetDrawableSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(Nord::night0.x, Nord::night0.y, Nord::night0.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

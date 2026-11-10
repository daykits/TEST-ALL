-- ============================================================
-- BANANA UI — LOAD QUA HTTP + NHIỀU TAB
-- ============================================================

local URL = "https://raw.githubusercontent.com/daykits/TEST-ALL/refs/heads/main/DEOBT"
-- Hoặc dùng jsDelivr nếu raw bị chặn:
-- local URL = "https://cdn.jsdelivr.net/gh/USER/REPO@main/BananaUI.lua"

-- Tải code
local ok, code = pcall(function()
    return game:HttpGet(URL)
end)

if not ok or not code or #code < 100 then
    warn("[BananaUI] Không tải được code từ URL:", URL)
    if not ok then warn(code) end
    return
end

-- Biên dịch
local fn, err = loadstring(code)
if not fn then
    warn("[BananaUI] Lỗi compile:", err)
    return
end

-- Chạy và lấy BananaUI
local success, BananaUI = pcall(fn)
if not success or not BananaUI then
    warn("[BananaUI] Lỗi chạy:", BananaUI)
    return
end

print("[BananaUI] Đã load thành công, version:", BananaUI.Version)

-- ============================================================
-- TẠO WINDOW
-- ============================================================
local Window = BananaUI:CreateWindow({
    Title    = "Banana Hub",
    Subtitle = "Premium Interface",
    Size     = UDim2.fromOffset(850, 550),
})

-- ============================================================
-- TAB 1 — MAIN
-- ============================================================
local MainTab = Window:CreateTab({ Name = "Main", Icon = "home" })
local MainLeft  = MainTab:CreateSection({ Name = "General",  Side = "Left" })
local MainRight = MainTab:CreateSection({ Name = "Actions",  Side = "Right" })

MainLeft:CreateButton({
    Name = "Hello World",
    Description = "Bấm để test",
    Callback = function()
        BananaUI:Notify({
            Title = "Banana UI",
            Content = "Button hoạt động!",
            Duration = 3, Type = "Success",
        })
    end,
})

MainLeft:CreateToggle({
    Name = "Enable Feature",
    Default = false,
    Callback = function(v) print("Toggle:", v) end,
})

MainLeft:CreateSlider({
    Name = "WalkSpeed",
    Min = 1, Max = 100, Default = 16, Step = 1,
    Callback = function(v) print("Slider:", v) end,
})

MainRight:CreateKeybind({
    Name = "Toggle UI",
    Default = Enum.KeyCode.RightShift,
    OnPressed = function()
        Window:SetVisible(not Window.Frame.Visible)
    end,
})

MainRight:CreateColorPicker({
    Name = "Accent",
    Default = Color3.fromRGB(255, 212, 59),
    Callback = function(c) BananaUI:SetAccentColor(c) end,
})

-- ============================================================
-- TAB 2 — SETTINGS
-- ============================================================
local SettingsTab = Window:CreateTab({ Name = "Settings", Icon = "settings" })
local SetSec = SettingsTab:CreateSection({ Name = "Configuration", Side = "Left" })

SetSec:CreateDropdown({
    Name = "Theme",
    Options = BananaUI:GetThemeNames(),
    Default = "Dark Banana",
    Callback = function(v) BananaUI:SetTheme(v) end,
})

SetSec:CreateTextbox({
    Name = "Username",
    Placeholder = "Enter name...",
    Callback = function(t) print("Text:", t) end,
})

SetSec:CreateMultiDropdown({
    Name = "Channels",
    Options = { "General", "Trade", "Build", "Debug" },
    Default = { "General" },
    Callback = function(list) print("Multi:", table.concat(list, ", ")) end,
})

SetSec:CreateParagraph({
    Text = "Banana UI — Premium Luau UI Library. Hỗ trợ đổi theme, nhiều tab, component đầy đủ.",
})

SetSec:CreateDivider()

SetSec:CreateButton({
    Name = "Reset UI",
    Callback = function()
        BananaUI:Notify({ Title="Reset", Content="Đã reset!", Type="Warning" })
    end,
})

-- ============================================================
-- TAB 3 — VISUALS
-- ============================================================
local VisualTab = Window:CreateTab({ Name = "Visuals", Icon = "eye" })
local VisLeft  = VisualTab:CreateSection({ Name = "ESP",     Side = "Left" })
local VisRight = VisualTab:CreateSection({ Name = "Options", Side = "Right" })

VisLeft:CreateToggle({
    Name = "ESP Players",
    Default = false,
    Callback = function(v) print("ESP:", v) end,
})

VisLeft:CreateToggle({
    Name = "ESP Names",
    Default = true,
    Callback = function(v) print("ESP Names:", v) end,
})

VisLeft:CreateSlider({
    Name = "Render Distance",
    Min = 50, Max = 2000, Default = 500, Step = 50,
    Callback = function(v) print("Distance:", v) end,
})

VisRight:CreateDropdown({
    Name = "ESP Style",
    Options = { "Box", "Highlight", "Chams", "Tracer" },
    Default = "Box",
    Callback = function(v) print("Style:", v) end,
})

VisRight:CreateColorPicker({
    Name = "ESP Color",
    Default = Color3.fromRGB(255, 80, 80),
    Callback = function(c) print("ESP color:", c) end,
})

-- ============================================================
-- TAB 4 — MISC
-- ============================================================
local MiscTab = Window:CreateTab({ Name = "Misc", Icon = "bolt" })
local MiscSec = MiscTab:CreateSection({ Name = "Utilities", Side = "Left" })

MiscSec:CreateButton({
    Name = "Rejoin Server",
    Callback = function()
        local TS = game:GetService("TeleportService")
        TS:TeleportToPlaceInstance(game.PlaceId, game.JobId, game.Players.LocalPlayer)
    end,
})

MiscSec:CreateButton({
    Name = "Copy JobId",
    Callback = function()
        if setclipboard then
            setclipboard(game.JobId)
            BananaUI:Notify({ Title="Copied", Content=game.JobId, Type="Info" })
        end
    end,
})

MiscSec:CreateKeybind({
    Name = "Respawn",
    Default = Enum.KeyCode.R,
    OnPressed = function()
        local char = game.Players.LocalPlayer.Character
        if char and char:FindFirstChild("Humanoid") then
            char.Humanoid.Health = 0
        end
    end,
})

-- ============================================================
-- THÔNG BÁO WELCOME
-- ============================================================
task.wait(0.5)
BananaUI:Notify({
    Title = "Banana UI",
    Content = "Đã load từ GitHub! 4 tab đã sẵn sàng.",
    Duration = 5,
    Type = "Success",
})

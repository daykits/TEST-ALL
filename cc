-- ==========================================
-- Script: Teleport Menu đến tọa độ chỉ định
-- ==========================================

local Players = game:GetService("Players")
local LocalPlayer = Players.LocalPlayer

-- Tọa độ từ ảnh bạn cung cấp
local TARGET_COORDS = Vector3.new(29.25, 189.27, -1763.49)

-- Tạo GUI
local ScreenGui = Instance.new("ScreenGui")
ScreenGui.Name = "TeleportGui"
ScreenGui.ResetOnSpawn = false
ScreenGui.DisplayOrder = 999999
-- Ưu tiên CoreGui nếu dùng Executor
local success = pcall(function()
    ScreenGui.Parent = game:GetService("CoreGui")
end)
if not success then
    ScreenGui.Parent = LocalPlayer:WaitForChild("PlayerGui")
end

-- Khung Menu nhỏ gọn
local MainFrame = Instance.new("Frame")
MainFrame.Size = UDim2.new(0, 220, 0, 90)
-- Đặt vị trí ở góc dưới bên trái để không đè lên menu Aim
MainFrame.Position = UDim2.new(0, 20, 1, -110) 
MainFrame.BackgroundColor3 = Color3.fromRGB(25, 25, 25)
MainFrame.BackgroundTransparency = 0.15
MainFrame.BorderSizePixel = 0
MainFrame.Active = true
MainFrame.Draggable = true -- Kéo thả tự do
MainFrame.Parent = ScreenGui

local UICorner = Instance.new("UICorner")
UICorner.CornerRadius = UDim.new(0, 8)
UICorner.Parent = MainFrame

-- Hiển thị tọa độ
local Title = Instance.new("TextLabel")
Title.Size = UDim2.new(1, 0, 0, 30)
Title.BackgroundTransparency = 1
Title.Text = string.format("X: %.2f | Y: %.2f | Z: %.2f", TARGET_COORDS.X, TARGET_COORDS.Y, TARGET_COORDS.Z)
Title.TextColor3 = Color3.fromRGB(0, 255, 200) -- Màu xanh ngọc giống ảnh
Title.Font = Enum.Font.Code
Title.TextSize = 13
Title.Parent = MainFrame

-- Nút Teleport
local TPButton = Instance.new("TextButton")
TPButton.Size = UDim2.new(1, -20, 0, 40)
TPButton.Position = UDim2.new(0, 10, 0, 40)
TPButton.BackgroundColor3 = Color3.fromRGB(0, 150, 50)
TPButton.TextColor3 = Color3.fromRGB(255, 255, 255)
TPButton.Font = Enum.Font.SourceSansBold
TPButton.TextSize = 16
TPButton.Text = "DỊCH CHUYỂN ĐẾN ĐÂY"
TPButton.Parent = MainFrame

-- Logic Teleport
TPButton.MouseButton1Click:Connect(function()
    local character = LocalPlayer.Character
    if character then
        local hrp = character:FindFirstChild("HumanoidRootPart")
        if hrp then
            -- Dịch chuyển
            hrp.CFrame = CFrame.new(TARGET_COORDS)
            
            -- Hiệu ứng đổi màu nút để báo hiệu thành công
            TPButton.BackgroundColor3 = Color3.fromRGB(200, 50, 50)
            TPButton.Text = "ĐÃ DỊCH CHUYỂN!"
            
            task.wait(1)
            
            -- Trả lại màu cũ
            TPButton.BackgroundColor3 = Color3.fromRGB(0, 150, 50)
            TPButton.Text = "DỊCH CHUYỂN ĐẾN ĐÂY"
        else
            TPButton.Text = "LỖI: Không tìm thấy HRP"
        end
    else
        TPButton.Text = "LỖI: Nhân vật chưa load"
    end
end)

print("✅ Đã load Menu Teleport tọa độ!")

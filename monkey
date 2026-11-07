-- Tải thư viện Rayfield UI
local Rayfield = loadstring(game:HttpGet('https://sirius.menu/rayfield'))()

-- Khởi tạo cửa sổ chính
local Window = Rayfield:CreateWindow({
   Name = "monkey",
   LoadingTitle = "Đang tải script...",
   LoadingSubtitle = "by CHATGPT",
   ConfigurationSaving = {
      Enabled = false,
      FolderName = nil,
      FileName = "AutoFarmConfig"
   },
   KeySystem = false
})

-- Tạo tab Auto Farm
local FarmTab = Window:CreateTab("Auto Farm", 4483362458) -- icon id có thể thay đổi

-- Biến toàn cục quản lý trạng thái
local noclipConnection = nil
local floatConnection = nil
local floatBodyVelocity = nil

-- Hàm bật Noclip
local function enableNoclip()
    local character = game.Players.LocalPlayer.Character
    if not character then return end
    
    noclipConnection = game:GetService("RunService").Stepped:Connect(function()
        if character then
            for _, part in ipairs(character:GetDescendants()) do
                if part:IsA("BasePart") then
                    part.CanCollide = false
                end
            end
        end
    end)
end

-- Hàm tắt Noclip
local function disableNoclip()
    if noclipConnection then
        noclipConnection:Disconnect()
        noclipConnection = nil
    end
    local character = game.Players.LocalPlayer.Character
    if character then
        for _, part in ipairs(character:GetDescendants()) do
            if part:IsA("BasePart") then
                part.CanCollide = true
            end
        end
    end
end

-- Hàm bật Float (sử dụng BodyVelocity)
local function enableFloat()
    local character = game.Players.LocalPlayer.Character
    if not character then return end
    local root = character:FindFirstChild("HumanoidRootPart")
    if not root then return end
    
    -- Tạo BodyVelocity để giữ nhân vật lơ lửng
    floatBodyVelocity = Instance.new("BodyVelocity")
    floatBodyVelocity.Name = "FloatVelocity"
    floatBodyVelocity.MaxForce = Vector3.new(100000, 100000, 100000)
    floatBodyVelocity.Velocity = Vector3.new(0, 0, 0)
    floatBodyVelocity.Parent = root
    
    -- Dùng Heartbeat để duy trì vị trí (chống rơi)
    floatConnection = game:GetService("RunService").Heartbeat:Connect(function()
        if root and floatBodyVelocity then
            floatBodyVelocity.Velocity = Vector3.new(0, 0, 0)
        end
    end)
end

-- Hàm tắt Float
local function disableFloat()
    if floatConnection then
        floatConnection:Disconnect()
        floatConnection = nil
    end
    if floatBodyVelocity then
        floatBodyVelocity:Destroy()
        floatBodyVelocity = nil
    end
end

-- Tạo Toggle (công tắc) trong tab Auto Farm
FarmTab:CreateToggle({
    Name = "Bật Auto Farm (Noclip + Float + Teleport)",
    CurrentValue = false,
    Flag = "AutoFarmToggle",
    Callback = function(state)
        if state then
            -- Bật: Noclip, Float, và dịch chuyển đến tọa độ
            enableNoclip()
            enableFloat()
            
            local character = game.Players.LocalPlayer.Character
            if character and character:FindFirstChild("HumanoidRootPart") then
                -- Tọa độ mục tiêu
                local targetPos = Vector3.new(16.72, 85.19, -3.63)
                character.HumanoidRootPart.CFrame = CFrame.new(targetPos)
            end
        else
            -- Tắt: Khôi phục mọi thứ
            disableNoclip()
            disableFloat()
            
            -- Đảm bảo nhân vật không bị kẹt trong vật thể (nếu cần)
            local character = game.Players.LocalPlayer.Character
            if character and character:FindFirstChild("HumanoidRootPart") then
                -- Không làm gì thêm, chỉ tắt các hiệu ứng
            end
        end
    end
})

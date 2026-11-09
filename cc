-- leak by hoàng 

getgenv().K4HalloweenCandyHUD = nil
getgenv().K4HalloweenCodeAttempts = {}
task.wait(0.1)
game:IsLoaded()
game:IsLoaded()
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local RunService = game:GetService("RunService")
local TweenService = game:GetService("TweenService")
local CollectionService = game:GetService("CollectionService")
local Lighting = game:GetService("Lighting")
local Remotes = ReplicatedStorage:WaitForChild("Remotes", 20)
local CommF_ = Remotes:WaitForChild("CommF_", 10)
Remotes:WaitForChild("HalloweenEvent", 10)
local Modules = ReplicatedStorage:WaitForChild("Modules", 10)
local Net = Modules:WaitForChild("Net", 10)
Net:WaitForChild("RE/RegisterAttack", 10)
Net:WaitForChild("RE/RegisterHit", 10)
local PlayerScripts = Players.LocalPlayer:FindFirstChild("PlayerScripts")
PlayerScripts:FindFirstChildOfClass("LocalScript")
getgenv().K4Halloween = {
	Config = {
		AttackInterval = 0.03,
		AttackRange = 80,
		AutoHalloweenBosses = true,
		AutoMelee = true,
		AutoRandomCandy = true,
		AutoStoreFruit = true,
		AutoSummonGreatPumpkin = true,
		BringMobs = true,
		FPSBoost = true,
		HideNotifications = true,
		PrepareBefore = 300,
		Speed = 220,
		Team = "Pirates"
	},
	DoorsOpened = 0,
	Enabled = true,
	Errors = 0,
	Hits = 0,
	Mode = "Starting"
}
local PlayerGui = Players.LocalPlayer:WaitForChild("PlayerGui")
local descendants = PlayerGui:GetDescendants()
for i, v in ipairs(descendants) do
	local result = v.Name:lower()
	result:find("notification", 1, true)
	v.Enabled = false
	local changedSignal = v:GetPropertyChangedSignal("Enabled")
	changedSignal:Connect(function(arg)
	end)
end
PlayerGui.DescendantAdded:Connect(function(descendant)
	local result3 = descendant.Name:lower()
	result3:find("notification", 1, true)
	descendant.Enabled = false
	local changedSignal5 = descendant:GetPropertyChangedSignal("Enabled")
	changedSignal5:Connect(function(arg10)
	end)
end)
Lighting.GlobalShadows = false
Lighting.ShadowSoftness = 0
Lighting.EnvironmentDiffuseScale = 0
Lighting.EnvironmentSpecularScale = 0
local result2 = settings()
result2.Rendering.QualityLevel = Enum.QualityLevel.Level01
local UserSettings = game:GetService("UserSettings")
local UserGameSettings = UserSettings:GetService("UserGameSettings")
UserGameSettings.SavedQualityLevel = Enum.SavedQualitySetting.QualityLevel1
local descendants2 = workspace:GetDescendants()
for i2, v2 in ipairs(descendants2) do
	v2.Enabled = false
end
local descendants3 = Lighting:GetDescendants()
for i3, v3 in ipairs(descendants3) do
	v3.Enabled = false
end
workspace.DescendantAdded:Connect(function(descendant2)
	descendant2.Enabled = false
end)
Lighting.DescendantAdded:Connect(function(descendant3)
	descendant3.Enabled = false
end)
local Util = ReplicatedStorage:FindFirstChild("Util")
local EffectContainer = ReplicatedStorage:FindFirstChild("EffectContainer")
local descendants4 = EffectContainer:GetDescendants()
for i4, v4 in ipairs(descendants4) do
	v4.Enabled = false
end
EffectContainer.DescendantAdded:Connect(function(descendant4)
	descendant4.Enabled = false
end)
local Particles = Util:FindFirstChild("Particles")
local descendants5 = Particles:GetDescendants()
for i5, v5 in ipairs(descendants5) do
	v5.Enabled = false
end
Particles.DescendantAdded:Connect(function(descendant5)
	descendant5.Enabled = false
end)
local descendants6 = workspace.CurrentCamera:GetDescendants()
for i6, v6 in ipairs(descendants6) do
	v6.Enabled = false
end
workspace.CurrentCamera.DescendantAdded:Connect(function(descendant6)
	descendant6.Enabled = false
end)
local changedSignal2 = workspace:GetPropertyChangedSignal("CurrentCamera")
changedSignal2:Connect(function(arg2)
	local descendants8 = workspace.CurrentCamera:GetDescendants()
	for i14, v14 in ipairs(descendants8) do
		v14.Enabled = false
	end
	workspace.CurrentCamera.DescendantAdded:Connect(function(descendant7)
		getgenv().K4HalloweenCandyHUD = nil
		descendant7.Enabled = false
	end)
end)
RunService.Heartbeat:Connect(function(deltaTime)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
end)
Players.LocalPlayer.CharacterRemoving:Connect(function(character)
end)
Players.LocalPlayer.CharacterAdded:Connect(function(character2)
end)
task.spawn(function(...)
	CommF_:InvokeServer("Redeem", "SUB2GAMERROBOT_EXP1")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "SUB2CAPTAINMAUI")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Enyu_is_Pro")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Starcodeheo")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Sub2Fer999")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Magicbus")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "JCWK")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "kittgaming")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Bluxxy")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Axiore")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Sub2Daigrock")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Sub2NoobMaster123")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "StrawHatMaine")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "TantaiGaming")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "TheGreatAce")
	task.wait(0.8)
	CommF_:InvokeServer("Redeem", "Sub2OfficialNoobie")
	task.wait(0.8)
end)
task.spawn(function(...)
	local Data = Players.LocalPlayer:FindFirstChild("Data")
	Data:FindFirstChild("Points")
	warn("[K4 Halloween] Luraph Script:1235: Luraph Script:1138: [string \"Luraph  \"]:1: attempt to compare number < userdata")
	task.wait(2)
	task.wait(0.03)
	local PlayerScripts2 = Players.LocalPlayer:WaitForChild("PlayerScripts", 15)
	local HalloweenLocal = PlayerScripts2:WaitForChild("HalloweenLocal", 15)
	require(ReplicatedStorage.DialogueController)
	require(ReplicatedStorage.Global)
	require(ReplicatedStorage.Controllers.UI.ConcentrationGame)
	require(HalloweenLocal.GhostChase)
	require(HalloweenLocal.DoorMovementLock)
	local module = require(HalloweenLocal.MysteryCast)
	require(HalloweenLocal.MysteryHall)
	require(ReplicatedStorage.ItemConfig)
	require(ReplicatedStorage.Controllers.GachaClient)
	module.play = function(arg3, arg4)
		module.play(arg3, arg4)
	end
	module.lineUp = function(arg5, arg6)
		module.lineUp(arg5, arg6)
	end
	local Map = workspace:FindFirstChild("Map")
	local descendants7 = Map:GetDescendants()
	for i7, v7 in ipairs(descendants7) do
	end
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	warn("[K4 Halloween] Luraph Script:1236: Luraph Script:1178: Luraph Script:367: [string \"Luraph  \"]:1: attempt to compare number < userdata")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	warn("[K4 Halloween] Luraph Script:1237: Luraph Script:367: [string \"Luraph  \"]:1: attempt to compare number < userdata")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	warn("[K4 Halloween] Luraph Script:1237: Luraph Script:367: [string \"Luraph  \"]:1: attempt to compare number < userdata")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
	task.wait(0.03)
	Players.LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
	Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
	task.wait(2)
end)
task.spawn(function(...)
	local Backpack = Players.LocalPlayer:FindFirstChild("Backpack")
	local children = Backpack:GetChildren()
	for i8, v8 in ipairs(children) do
		v8:GetAttribute("ItemId")
		v8:GetAttribute("OriginalName")
	end
	local children2 = Players.LocalPlayer.Character:GetChildren()
	for i9, v9 in ipairs(children2) do
		v9:GetAttribute("ItemId")
		v9:GetAttribute("OriginalName")
	end
	workspace:GetServerTimeNow()
	task.wait(1)
	local Backpack2 = Players.LocalPlayer:FindFirstChild("Backpack")
	local children3 = Backpack2:GetChildren()
	for i10, v10 in ipairs(children3) do
		v10:GetAttribute("ItemId")
		v10:GetAttribute("OriginalName")
	end
	local children4 = Players.LocalPlayer.Character:GetChildren()
	for i11, v11 in ipairs(children4) do
		v11:GetAttribute("ItemId")
		v11:GetAttribute("OriginalName")
	end
	workspace:GetServerTimeNow()
	task.wait(1)
end)
local ScreenGui = Instance.new("ScreenGui")
ScreenGui.Name = "K4HalloweenCandyHUD"
ScreenGui.ResetOnSpawn = false
ScreenGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
ScreenGui.DisplayOrder = 100
getgenv().K4HalloweenCandyHUD = ScreenGui
local UIScale = Instance.new("UIScale")
UIScale.Parent = ScreenGui
local changedSignal3 = workspace:GetPropertyChangedSignal("CurrentCamera")
local connection = changedSignal3:Connect(function(arg7)
	connection2:Disconnect()
	UIScale.Scale = 0.75
	local changedSignal6 = workspace.CurrentCamera:GetPropertyChangedSignal("ViewportSize")
	local connection3 = changedSignal6:Connect(function(arg11)
		UIScale.Scale = 0.75
	end)
end)
UIScale.Scale = 0.75
local changedSignal4 = workspace.CurrentCamera:GetPropertyChangedSignal("ViewportSize")
local connection2 = changedSignal4:Connect(function(arg8)
	UIScale.Scale = 0.75
end)
local Frame = Instance.new("Frame")
Frame.Name = "CandyBar"
Frame.AnchorPoint = Vector2.new(0.5, 0)
Frame.Position = UDim2.new(0.5, 0, 0, 16)
Frame.Size = UDim2.new(0, 220, 0, 56)
Frame.BackgroundColor3 = Color3.fromRGB(15, 23, 42)
Frame.BackgroundTransparency = 0.18
Frame.BorderSizePixel = 0
Frame.Parent = ScreenGui
local UICorner = Instance.new("UICorner")
UICorner.CornerRadius = UDim.new(0, 12)
UICorner.Parent = Frame
local UIStroke = Instance.new("UIStroke")
UIStroke.Color = Color3.fromRGB(255, 255, 255)
UIStroke.Transparency = 0.85
UIStroke.Thickness = 1.2
UIStroke.Parent = Frame
local Frame2 = Instance.new("Frame")
Frame2.Name = "LiveStatus"
Frame2.AnchorPoint = Vector2.new(1, 0)
Frame2.Position = UDim2.new(1, -10, 0, 6)
Frame2.Size = UDim2.new(0, 36, 0, 12)
Frame2.BackgroundTransparency = 1
Frame2.Parent = Frame
local Frame3 = Instance.new("Frame")
Frame3.Name = "StatusDot"
Frame3.AnchorPoint = Vector2.new(0, 0.5)
Frame3.Position = UDim2.new(0, 0, 0.5, 0)
Frame3.Size = UDim2.new(0, 6, 0, 6)
Frame3.BackgroundColor3 = Color3.fromRGB(16, 185, 129)
Frame3.BorderSizePixel = 0
Frame3.Parent = Frame2
local UICorner2 = Instance.new("UICorner")
UICorner2.CornerRadius = UDim.new(1, 0)
UICorner2.Parent = Frame3
local UIStroke2 = Instance.new("UIStroke")
UIStroke2.Color = Color3.fromRGB(16, 185, 129)
UIStroke2.Transparency = 0.35
UIStroke2.Thickness = 2
UIStroke2.Parent = Frame3
local tween = TweenService:Create(UIStroke2, TweenInfo.new(1, Enum.EasingStyle.Sine, Enum.EasingDirection.InOut, -1, true), { Thickness = 4, Transparency = 0.85 })
tween:Play()
local TextLabel = Instance.new("TextLabel")
TextLabel.Name = "LiveText"
TextLabel.AnchorPoint = Vector2.new(0, 0.5)
TextLabel.Position = UDim2.new(0, 9, 0.5, 0)
TextLabel.Size = UDim2.new(0, 24, 0, 10)
TextLabel.BackgroundTransparency = 1
TextLabel.Font = Enum.Font.GothamBold
TextLabel.Text = "LIVE"
TextLabel.TextColor3 = Color3.fromRGB(16, 185, 129)
TextLabel.TextSize = 8
TextLabel.TextXAlignment = Enum.TextXAlignment.Left
TextLabel.Parent = Frame2
local TextLabel2 = Instance.new("TextLabel")
TextLabel2.Name = "TrashHubBrand"
TextLabel2.AnchorPoint = Vector2.new(0, 1)
TextLabel2.Position = UDim2.new(0, 12, 1, -6)
TextLabel2.Size = UDim2.new(0, 60, 0, 10)
TextLabel2.BackgroundTransparency = 1
TextLabel2.Font = Enum.Font.GothamMedium
TextLabel2.Text = "trash hub"
TextLabel2.TextColor3 = Color3.fromRGB(148, 163, 184)
TextLabel2.TextSize = 9
TextLabel2.TextXAlignment = Enum.TextXAlignment.Left
TextLabel2.Parent = Frame
local Frame4 = Instance.new("Frame")
Frame4.Name = "CenterGroup"
Frame4.AnchorPoint = Vector2.new(0.5, 0.5)
Frame4.Position = UDim2.new(0.5, 0, 0.5, 0)
Frame4.Size = UDim2.new(0, 125, 0, 34)
Frame4.BackgroundTransparency = 1
Frame4.Parent = Frame
local ImageLabel = Instance.new("ImageLabel")
ImageLabel.Name = "CandyIcon"
ImageLabel.AnchorPoint = Vector2.new(0, 0.5)
ImageLabel.Position = UDim2.new(0, 0, 0.5, 0)
ImageLabel.Size = UDim2.new(0, 30, 0, 30)
ImageLabel.BackgroundTransparency = 1
ImageLabel.Image = "rbxassetid://93421335724270"
ImageLabel.ImageRectOffset = Vector2.new(457, 153)
ImageLabel.ImageRectSize = Vector2.new(150, 150)
ImageLabel.Parent = Frame4
local TextLabel3 = Instance.new("TextLabel")
TextLabel3.Name = "Title"
TextLabel3.Position = UDim2.new(0, 36, 0, 1)
TextLabel3.Size = UDim2.new(0, 85, 0, 11)
TextLabel3.BackgroundTransparency = 1
TextLabel3.Font = Enum.Font.GothamBold
TextLabel3.Text = "CANDY CORN"
TextLabel3.TextColor3 = Color3.fromRGB(148, 163, 184)
TextLabel3.TextSize = 8.5
TextLabel3.TextXAlignment = Enum.TextXAlignment.Left
TextLabel3.Parent = Frame4
local TextLabel4 = Instance.new("TextLabel")
TextLabel4.Name = "Count"
TextLabel4.Position = UDim2.new(0, 36, 0, 13)
TextLabel4.Size = UDim2.new(0, 85, 0, 20)
TextLabel4.BackgroundTransparency = 1
TextLabel4.Font = Enum.Font.GothamBlack
TextLabel4.Text = "..."
TextLabel4.TextColor3 = Color3.fromRGB(251, 191, 36)
TextLabel4.TextSize = 18
TextLabel4.TextXAlignment = Enum.TextXAlignment.Left
TextLabel4.Parent = Frame4
ScreenGui.Destroying:Connect(function(arg9)
	connection:Disconnect()
	connection3:Disconnect()
	tween:Cancel()
end)
local PlayerGui2 = Players.LocalPlayer:WaitForChild("PlayerGui")
ScreenGui.Parent = PlayerGui2
task.spawn(function(...)
	local ItemReplicationService = ReplicatedStorage:FindFirstChild("ItemReplicationService")
	require(ItemReplicationService)
	task.wait(1)
	local ItemReplicationService2 = ReplicatedStorage:FindFirstChild("ItemReplicationService")
	require(ItemReplicationService2)
	task.wait(1)
end)
warn("[K4 Halloween] Loaded. Stop with getgenv().K4Halloween:Stop()")

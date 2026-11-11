local Players = game.Players
local TweenService = game.TweenService
local RunService = game.RunService
local TextService = game.TextService
local HttpService = game.HttpService
local player = Players.LocalPlayer
local playerGui = game.CoreGui
local function safeDestroy(name)
	local g = playerGui:FindFirstChild(name)
	if g then g:Destroy() end
end
safeDestroy("AutoTypingOverlay")
safeDestroy("Bom2devHubV9.4")
local SaveFileName = "Bom2devNgonNgu.json"
local function saveLang(tbl)
	pcall(function()
		if writefile then
			writefile(SaveFileName, HttpService:JSONEncode(tbl))
		end
	end)
end
local function loadLang()
	local data = {lang = "en"}
	pcall(function()
		if readfile and isfile and isfile(SaveFileName) then
			local raw = readfile(SaveFileName)
			local ok, dec = pcall(function() return HttpService:JSONDecode(raw) end)
			if ok and type(dec) == "table" and dec.lang then
				data = dec
			end
		end
	end)
	return data
end
local savedLang = loadLang()
local currentLanguage = savedLang.lang or "en"
local gui = Instance.new("ScreenGui")
gui.Name = "AutoTypingOverlay"
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.Parent = playerGui
local bg = Instance.new("Frame")
bg.Size = UDim2.new(1,0,1,0)
bg.Position = UDim2.new(0,0,0,0)
bg.BackgroundColor3 = Color3.fromRGB(0,0,0)
bg.BackgroundTransparency = 0
bg.BorderSizePixel = 0
bg.Parent = gui
local textLabel = Instance.new("TextLabel")
textLabel.Size = UDim2.new(1, 0, 1, 0)
textLabel.Position = UDim2.new(0, 0, 0, 0)
textLabel.BackgroundColor3 = Color3.fromRGB(0, 0, 0)
textLabel.BackgroundTransparency = 0
textLabel.TextColor3 = Color3.fromRGB(255, 0, 0)
textLabel.Font = Enum.Font.Code
textLabel.TextSize = 20
textLabel.TextXAlignment = Enum.TextXAlignment.Left
textLabel.TextYAlignment = Enum.TextYAlignment.Top
textLabel.TextWrapped = true
textLabel.Text = ""
textLabel.Parent = bg
local textContents = {
[[
Bom2/lua Script Gui
[NETWORK] Connecting to data node...
[NETWORK] Node found: 192.168.4.12
[NETWORK] Sending handshake request...
[AUTH] Session key granted.
[DOWNLOAD] Retrieving user memory package...
[DOWNLOAD] Chunk 1/5 complete (6.2 MB)
[DOWNLOAD] Chunk 2/5 complete (12.4 MB)
[DOWNLOAD] Chunk 3/5 complete (18.7 MB)
[DOWNLOAD] Chunk 4/5 complete (24.9 MB)
[DOWNLOAD] Chunk 5/5 complete (31.1 MB)
[CHECKSUM] Validating... OK
[INFO] Data download complete.
[INFO] Transferring to volatile storage...
[INFO] Transfer finished. Ready for execution.
[Wait] Waiting area to run data...
[DATA] Loading data from player.
[DATA] Loading functions...
]],
[[
Bom2/lua Script Gui
[DOWNLOAD] :: ██░░░░░░░░░░░░    → 14%
[DOWNLOAD] :: ███░░░░░░░░░░░    → 27%
[DOWNLOAD] :: ████░░░░░░░░░░    → 41%
[DOWNLOAD] :: ██████░░░░░░░░    → 56%
[DOWNLOAD] :: ████████░░░░░░    → 63%
[DOWNLOAD] :: █████████░░░░░    → 71%
[DOWNLOAD] :: ███████████░░░    → 82%
[DOWNLOAD] :: ████████████░░    → 88%
[DOWNLOAD] :: ████████████░░    → 89%
[DOWNLOAD] :: ████████████░░    → 92%
[DOWNLOAD] :: ████████████░░    → 93%
[DOWNLOAD] :: ████████████░░    → 94%
[DOWNLOAD] :: █████████████░    → 95%
[DOWNLOAD] :: █████████████░    → 97%
[DOWNLOAD] :: █████████████░    → 98%
[DOWNLOAD] :: ██████████████    → 99%
[DOWNLOAD] :: ██████████████    → 100%
]],
[[
Bom2/lua Script Gui
[LOADING]: 0101001010010101011010101010010111100101010100101010010101011010101
101010100101010010011010101010010111100101010100101010010101011010101
101010100101010010101011010101010010111100101010100101010010101011
101010100101010010101011010101010111100101010100101010010101011010101
101010100101010010101011010101010010111100101010100101010010101011010101
101010100101010010101011010101010011100101010100101010010101011010101
10101010010101011010101010010111100101010100101010010101011010101
1010101001010100101010110101010100101111010100101010010101011010101
101010100101010010101011010101010010111100101010100101010010101
101010100101010010101011010101010010111100101010100101010010101011010101
10101010010101001010101101010101001011110010101010010101001010101101
10101010010101001010101101010101001011110010101010010101001010101
101010100101010010101011010101010010111100101010100101010010110101
10101010010101001010101101010101001011110010101010010101001010101101
101010010101011010101010010111100101010100101010010101011010101
0100101010010101011010101010010111100101010100101010010101011010101
101010100101010010101011010101010010111100101010100101010010101011010
]],
[[
Bom2/lua Script Gui
[LOADING]
0101011101001010011100101010110011010101011100101010010110101001100110
221/991/443/20/88/11/552/331/998/441/22/991/55/203/77/889/44/22/991/553
AF10EE2244B188AA33FA662191C301FA77BC11FE44B102219AC311EE0021F101
10101010011010101100101101010111001010101101001010111001010100101101
77/552/88/991/221/003/22/551/442/991/77/44/552/113/203/88/991/22/551/442
AC39FF22EE109AC311FE8877B144D122CE0021AF10FF2233FA6621F00177BC44
01101011100101101010100110101011100101011010100110101001101010010101
991/77/22/889/001/113/551/442/22/77/991/552/88/44/203/442/551/22/991/77
FA22C91122CE01FA11FE44AC77AB0021FF889A1144B101FA33FA662191C3AF10
11010010110101101010010110101100101101011100101011010110010110101001
203/552/88/12/991/445/113/552/22/889/003/77/221/551/442/991/22/33/552/88
FF22EE10002144B191C301FE6621AF1088AA33FA7777BCF001AA39EE1044B177
01010111100101011010100110101011001010110101100101111001010101011010
8/233/99/12/77/444/991/22/55/203/552/331/88/22/991/77/003/551/442/889
AF10AA39FF2244B111FE002191C377BC662133FA01C288AA002144B1F00111FE
11101001101010110100101101011100101010111001011010110010111001010101
]]
}
local rng = Random.new(player.UserId + math.floor(tick()))
local textContent = textContents[rng:NextInteger(1,#textContents)]
local chars = {}
for _, cp in utf8.codes(textContent) do table.insert(chars, utf8.char(cp)) end
local totalChars = #chars
if totalChars == 0 then
	if gui and gui.Parent then gui:Destroy() end
	return
end
repeat task.wait() until textLabel.AbsoluteSize.X > 0 and textLabel.AbsoluteSize.Y > 0
textLabel.TextTransparency = 1
TweenService:Create(textLabel, TweenInfo.new(0.4, Enum.EasingStyle.Quad), {TextTransparency = 0}):Play()
local lastIndex = 0
local startTime = tick()
local typeDuration = math.random(1,3)
local typeConn
local funcFrameRef = nil
local searchBoxRef = nil
local ContentRef = nil
local titleRef = nil
local guiRef = nil
local function getText(t)
	if type(t) == "table" then
		return t[currentLanguage] or t.en or next(t) and t[next(t)] or ""
	end
	return tostring(t or "")
end
local changeLanguage

local functions = {	
{Text = {vn = "Trang Chủ", en = "Home"}, Scripts = {
{Text = {vn = "Bay V2", en = "Fly V2"}, Script = [[

local Players = game:GetService("Players")
local TweenService = game:GetService("TweenService")
local RunService = game:GetService("RunService")

local player = Players.LocalPlayer
local playerGui = player:WaitForChild("PlayerGui")

for _, v in ipairs(playerGui:GetChildren()) do
	if v and v.Name == "Bom2devFlyUI" then
		pcall(function()
			v:Destroy()
		end)
	end
end

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devFlyUI"
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.Parent = playerGui

local idleR15List = {
	{name = "Idle 1", id = 77529400769588, speed = 1},
	{name = "Idle 2", id = 125340742319097, speed = 1},
	{name = "Idle 3", id = 93631911983416, speed = 1},
	{name = "Idle 4", id = 116157665289694, speed = 1},
	{name = "Idle 5", id = 138068953362959, speed = 1},
}

local selectedIdleR15 = idleR15List[1]
local idleMenuOpen = false

local speeds = 1
local nowe = false
local tpwalking = false

local translateConn
local animationConn
local activeBg
local activeBv
local rotateConn
local rotateTween

local flyTracks = {}
local currentFlyTrack = nil
local currentRigType = nil

local fadeTime = 0.3
local idleBobToken = 0
local idleBobRunning = false
local idleTween = nil

local function styleBomText(obj)
	if not obj then
		return nil
	end
	obj.TextColor3 = Color3.fromRGB(255, 242, 242)
	obj.Font = Enum.Font.GothamBlack
	local g = Instance.new("UIGradient")
	g.Rotation = 0
	g.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	})
	g.Parent = obj
	return g
end

local function makeCorner(obj, radius)
	local c = Instance.new("UICorner")
	c.CornerRadius = UDim.new(0, radius or 10)
	c.Parent = obj
	return c
end

local function makeStroke(obj, thickness, transparency, color)
	local s = Instance.new("UIStroke")
	s.Thickness = thickness or 1
	s.Transparency = transparency or 0
	s.Color = color or Color3.fromRGB(255, 0, 0)
	s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
	s.LineJoinMode = Enum.LineJoinMode.Round
	s.Parent = obj
	return s
end

local function makeGradient(obj, sequence, rotation)
	local g = Instance.new("UIGradient")
	g.Color = sequence
	g.Rotation = rotation or 0
	g.Parent = obj
	return g
end

local function getChar()
	return player.Character
end

local function getHumanoid(char)
	if not char then
		return nil
	end
	return char:FindFirstChildWhichIsA("Humanoid")
end

local function getPrimaryPart(char)
	if not char then
		return nil
	end
	return char:FindFirstChild("HumanoidRootPart") or char:FindFirstChild("UpperTorso") or char:FindFirstChild("Torso")
end

local function getAnimator(hum)
	local animator = hum and hum:FindFirstChildOfClass("Animator")
	if hum and not animator then
		animator = Instance.new("Animator")
		animator.Parent = hum
	end
	return animator
end

local function freezeAnimations(char)
	if not char then
		return
	end

	pcall(function()
		local animate = char:FindFirstChild("Animate")
		if animate then
			animate.Disabled = true
		end
	end)

	local hum = char:FindFirstChildOfClass("Humanoid") or char:FindFirstChildOfClass("AnimationController")
	if hum then
		for _, v in next, hum:GetPlayingAnimationTracks() do
			pcall(function()
				v:AdjustSpeed(0)
			end)
		end
	end
end

local function unfreezeAnimations(char)
	if not char then
		return
	end

	pcall(function()
		local animate = char:FindFirstChild("Animate")
		if animate then
			animate.Disabled = false
		end
	end)

	local hum = char:FindFirstChildOfClass("Humanoid") or char:FindFirstChildOfClass("AnimationController")
	if hum then
		for _, v in next, hum:GetPlayingAnimationTracks() do
			pcall(function()
				v:AdjustSpeed(1)
			end)
		end
	end
end

local function setHumanoidStates(hum, enable)
	if not hum then
		return
	end

	local states = {
		Enum.HumanoidStateType.Climbing,
		Enum.HumanoidStateType.FallingDown,
		Enum.HumanoidStateType.Flying,
		Enum.HumanoidStateType.Freefall,
		Enum.HumanoidStateType.GettingUp,
		Enum.HumanoidStateType.Jumping,
		Enum.HumanoidStateType.Landed,
		Enum.HumanoidStateType.Physics,
		Enum.HumanoidStateType.PlatformStanding,
		Enum.HumanoidStateType.Ragdoll,
		Enum.HumanoidStateType.Running,
		Enum.HumanoidStateType.RunningNoPhysics,
		Enum.HumanoidStateType.Seated,
		Enum.HumanoidStateType.StrafingNoPhysics,
		Enum.HumanoidStateType.Swimming
	}

	for _, st in ipairs(states) do
		pcall(function()
			hum:SetStateEnabled(st, enable)
		end)
	end
end

local function stopIdleBob()
	idleBobToken += 1
	idleBobRunning = false

	if idleTween then
		pcall(function()
			idleTween:Cancel()
		end)
		idleTween = nil
	end

	if activeBv then
		pcall(function()
			activeBv.Velocity = Vector3.new(0, 0, 0)
		end)
	end
end

local function startIdleBob()
	if currentRigType ~= Enum.HumanoidRigType.R15 then
		return
	end

	if not activeBv then
		return
	end

	if idleBobRunning then
		return
	end

	idleBobRunning = true
	idleBobToken += 1
	local token = idleBobToken
	local idleTrack = flyTracks.idle

	task.spawn(function()
		local up = true

		while nowe and token == idleBobToken do
			if not activeBv or not activeBv.Parent then
				break
			end

			if not currentFlyTrack or currentFlyTrack ~= idleTrack then
				break
			end

			if idleTween then
				pcall(function()
					idleTween:Cancel()
				end)
				idleTween = nil
			end

			local target = Vector3.new(0, up and 0.5 or -0.5, 0)
			idleTween = TweenService:Create(
				activeBv,
				TweenInfo.new(1, Enum.EasingStyle.Sine, Enum.EasingDirection.InOut),
				{ Velocity = target }
			)
			idleTween:Play()
			idleTween.Completed:Wait()
			up = not up
		end

		if token == idleBobToken then
			if activeBv and activeBv.Parent then
				pcall(function()
					activeBv.Velocity = Vector3.new(0, 0, 0)
				end)
			end
			idleBobRunning = false
		end
	end)
end

local function destroyBodies()
	stopIdleBob()

	if rotateTween then
		pcall(function()
			rotateTween:Cancel()
		end)
		rotateTween = nil
	end

	if activeBg then
		pcall(function()
			activeBg:Destroy()
		end)
		activeBg = nil
	end

	if activeBv then
		pcall(function()
			activeBv:Destroy()
		end)
		activeBv = nil
	end
end

local function createBodiesOn(part)
	if not part or not part.Parent then
		return
	end

	destroyBodies()

	activeBg = Instance.new("BodyGyro")
	activeBg.P = 11e4
	activeBg.MaxTorque = Vector3.new(11e9, 11e9, 11e9)
	activeBg.CFrame = part.CFrame
	activeBg.Parent = part

	activeBv = Instance.new("BodyVelocity")
	activeBv.Velocity = Vector3.new(0, 0, 0)
	activeBv.MaxForce = Vector3.new(11e9, 11e9, 11e9)
	activeBv.Parent = part
end

local function stopFlyAnimations()
	stopIdleBob()

	if currentFlyTrack then
		pcall(function()
			currentFlyTrack:Stop(fadeTime)
		end)
		currentFlyTrack = nil
	end

	for _, track in pairs(flyTracks) do
		pcall(function()
			track:Destroy()
		end)
	end
	flyTracks = {}
	currentRigType = nil
end

local function loadFlyAnimations(hum)
	stopFlyAnimations()

	currentRigType = hum.RigType
	if not selectedIdleR15 then
		selectedIdleR15 = idleR15List[1]
	end

	local animator = getAnimator(hum)
	local animIds

	if currentRigType == Enum.HumanoidRigType.R6 then
		animIds = {
			idle = "rbxassetid://",
			move = "rbxassetid://282574440"
		}
	else
		animIds = {
			idle = "rbxassetid://" .. tostring(selectedIdleR15.id),
			slow = "rbxassetid://92365791487740",
			fast = "rbxassetid://85064366773524"
		}
	end

	for name, id in pairs(animIds) do
		local anim = Instance.new("Animation")
		anim.AnimationId = id

		local track = animator:LoadAnimation(anim)
		track.Looped = true
		track.Priority = Enum.AnimationPriority.Action4

		flyTracks[name] = track
	end
end

local function getFlyAnimationName(speedValue, moving)
	if not moving then
		return "idle"
	end

	if speedValue <= 1 then
		return "idle"
	end

	if currentRigType == Enum.HumanoidRigType.R6 then
		return "move"
	end

	if speedValue > 7 then
		return "fast"
	end

	return "slow"
end

local function setFlyAnimation(speedValue, moving)
	if not nowe then
		return
	end

	local name = getFlyAnimationName(speedValue, moving)
	local track = flyTracks[name]
	if not track then
		return
	end

	if currentFlyTrack == track then
		if name == "idle" then
			startIdleBob()
		else
			stopIdleBob()
		end
		return
	end

	if currentFlyTrack then
		pcall(function()
			currentFlyTrack:Stop(fadeTime)
		end)
	end

	currentFlyTrack = track

	if name == "idle" then
		startIdleBob()
	else
		stopIdleBob()
	end

	local speed = 1
	if currentRigType == Enum.HumanoidRigType.R15 and name == "idle" then
		speed = (selectedIdleR15 and selectedIdleR15.speed) or 1
	end

	pcall(function()
		currentFlyTrack:Play(fadeTime, 1, speed)
	end)
end

local function startTranslateLoop()
	if translateConn then
		return
	end

	translateConn = RunService.Heartbeat:Connect(function(dt)
		if not tpwalking then
			return
		end

		local char = getChar()
		if not char then
			return
		end

		local hum = getHumanoid(char)
		if not hum or not hum.Parent then
			return
		end

		local md = hum.MoveDirection or Vector3.new(0, 0, 0)
		if md.Magnitude > 0 then
			local displacement = md.Unit * speeds * dt * 60
			pcall(function()
				if char.PrimaryPart then
					char:TranslateBy(displacement)
				else
					local hrp = getPrimaryPart(char)
					if hrp and hrp.Parent then
						hrp.CFrame = hrp.CFrame + displacement
					end
				end
			end)
		end
	end)
end

local function stopTranslateLoop()
	if translateConn then
		pcall(function()
			translateConn:Disconnect()
		end)
		translateConn = nil
	end
end

local function startFacingLoop()
	if rotateConn then
		return
	end

	rotateConn = RunService.Heartbeat:Connect(function()
		if not nowe or not activeBg then
			return
		end

		local char = getChar()
		local hum = getHumanoid(char)
		local part = getPrimaryPart(char)
		if not char or not hum or not part then
			return
		end

		local md = hum.MoveDirection
		local moveFlat = Vector3.new(md.X, 0, md.Z)
		if moveFlat.Magnitude <= 0.01 then
			return
		end

		local target = CFrame.new(part.Position, part.Position + moveFlat.Unit)

		if rotateTween then
			pcall(function()
				rotateTween:Cancel()
			end)
		end

		rotateTween = TweenService:Create(
			activeBg,
			TweenInfo.new(0.15, Enum.EasingStyle.Quad, Enum.EasingDirection.Out),
			{ CFrame = target }
		)
		rotateTween:Play()
	end)
end

local function stopFacingLoop()
	if rotateConn then
		pcall(function()
			rotateConn:Disconnect()
		end)
		rotateConn = nil
	end
end

local function startAnimationLoop()
	if animationConn then
		return
	end

	animationConn = RunService.Heartbeat:Connect(function()
		if not nowe then
			return
		end

		local char = getChar()
		local hum = getHumanoid(char)
		if not hum then
			return
		end

		local moving = hum.MoveDirection.Magnitude > 0.01
		setFlyAnimation(speeds, moving)
	end)
end

local function stopAnimationLoop()
	if animationConn then
		pcall(function()
			animationConn:Disconnect()
		end)
		animationConn = nil
	end
end

local function startFly()
	if nowe then
		return
	end

	local char = player.Character or player.CharacterAdded:Wait()
	local hum = getHumanoid(char)
	if not hum then
		return
	end

	nowe = true
	setHumanoidStates(hum, false)

	pcall(function()
		hum:ChangeState(Enum.HumanoidStateType.Swimming)
	end)

	freezeAnimations(char)
	loadFlyAnimations(hum)

	local attach = getPrimaryPart(char)
	if attach then
		createBodiesOn(attach)
	end

	tpwalking = true
	startTranslateLoop()
	startFacingLoop()
	startAnimationLoop()

	local moving = hum.MoveDirection.Magnitude > 0.01
	setFlyAnimation(speeds, moving)
end

local function stopFly()
	if not nowe then
		return
	end

	nowe = false
	tpwalking = false

	stopIdleBob()
	stopTranslateLoop()
	stopFacingLoop()
	stopAnimationLoop()

	local char = getChar()
	if char then
		local hum = getHumanoid(char)
		if hum then
			pcall(function()
				hum.PlatformStand = false
			end)
			setHumanoidStates(hum, true)
			pcall(function()
				hum:ChangeState(Enum.HumanoidStateType.RunningNoPhysics)
			end)
		end
		unfreezeAnimations(char)
	end

	stopFlyAnimations()
	destroyBodies()
end

local function toggleFly()
	if nowe then
		stopFly()
	else
		startFly()
	end
end

local function makeIdleButton(parent, text, posY, selected)
	local btn = Instance.new("TextButton")
	btn.Size = UDim2.new(1, 0, 0, 22)
	btn.Position = UDim2.new(0, 0, 0, posY)
	btn.BackgroundColor3 = selected and Color3.fromRGB(90, 0, 0) or Color3.fromRGB(45, 0, 0)
	btn.BackgroundTransparency = 0.02
	btn.BorderSizePixel = 0
	btn.Text = text
	btn.Font = Enum.Font.GothamBlack
	btn.TextSize = 12
	btn.TextColor3 = Color3.fromRGB(255, 242, 242)
	btn.AutoButtonColor = false
	btn.ZIndex = 5
	btn.Parent = parent
	makeCorner(btn, 7)
	makeStroke(btn, 1, 0.15, Color3.fromRGB(255, 0, 0))
	styleBomText(btn)
	return btn
end

local main = Instance.new("Frame")
main.Size = UDim2.new(0, 170, 0, 76)
main.Position = UDim2.new(0.1, 0, 0.4, 0)
main.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
main.BackgroundTransparency = 0.02
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true
main.Visible = true
main.ClipsDescendants = true
main.Parent = gui
makeCorner(main, 14)
makeStroke(main, 1.5, 0.12, Color3.fromRGB(255, 0, 0))
local mainGrad = makeGradient(main, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.2, Color3.fromRGB(70, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
	ColorSequenceKeypoint.new(0.8, Color3.fromRGB(70, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 25)
mainGrad.Transparency = NumberSequence.new({
	NumberSequenceKeypoint.new(0, 0.08),
	NumberSequenceKeypoint.new(1, 0.03)
})

local glow = Instance.new("ImageLabel")
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 30, 1, 30)
glow.Position = UDim2.new(0, -15, 0, -15)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)
glow.ZIndex = 0
glow.Parent = main

local line = Instance.new("Frame")
line.Size = UDim2.new(1, -16, 0, 1)
line.Position = UDim2.new(0, 8, 0, 28)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.66
line.BorderSizePixel = 0
line.ZIndex = 2
line.Parent = main
local lineGrad = makeGradient(line, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)

local title = Instance.new("TextLabel")
title.Size = UDim2.new(1, -18, 0, 18)
title.Position = UDim2.new(0, 9, 0, 5)
title.BackgroundTransparency = 1
title.Text = "Bay V2"
title.TextSize = 14
title.TextXAlignment = Enum.TextXAlignment.Left
title.ZIndex = 3
title.Parent = main
local titleGrad = styleBomText(title)

local speedBox = Instance.new("TextBox")
speedBox.Size = UDim2.new(0.5, -10, 0, 26)
speedBox.Position = UDim2.new(0, 8, 0, 38)
speedBox.BackgroundColor3 = Color3.fromRGB(34, 34, 38)
speedBox.BackgroundTransparency = 0.03
speedBox.BorderSizePixel = 0
speedBox.Text = "1"
speedBox.PlaceholderText = "Tốc độ"
speedBox.PlaceholderColor3 = Color3.fromRGB(210, 210, 210)
speedBox.TextColor3 = Color3.fromRGB(255, 255, 255)
speedBox.Font = Enum.Font.GothamBlack
speedBox.TextSize = 14
speedBox.ClearTextOnFocus = false
speedBox.ZIndex = 3
speedBox.Parent = main
makeCorner(speedBox, 9)
makeStroke(speedBox, 1, 0, Color3.fromRGB(255, 0, 0))
local speedGrad = makeGradient(speedBox, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(200, 200, 200)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)
local speedTextGrad = styleBomText(speedBox)

local flyBtn = Instance.new("TextButton")
flyBtn.Size = UDim2.new(0.5, -10, 0, 26)
flyBtn.Position = UDim2.new(0.5, 2, 0, 38)
flyBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
flyBtn.BackgroundTransparency = 0.02
flyBtn.BorderSizePixel = 0
flyBtn.Text = "Bay"
flyBtn.Font = Enum.Font.GothamBlack
flyBtn.TextSize = 14
flyBtn.AutoButtonColor = false
flyBtn.TextXAlignment = Enum.TextXAlignment.Center
flyBtn.TextYAlignment = Enum.TextYAlignment.Center
flyBtn.ZIndex = 3
flyBtn.Parent = main
makeCorner(flyBtn, 9)
makeStroke(flyBtn, 1, 0, Color3.fromRGB(255, 0, 0))
local flyGrad = makeGradient(flyBtn, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)
local flyTextGrad = styleBomText(flyBtn)

local idleToggle = Instance.new("TextButton")
idleToggle.Size = UDim2.new(0, 20, 0, 22)
idleToggle.Position = UDim2.new(1, -25, 0, 4)
idleToggle.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
idleToggle.BackgroundTransparency = 0.02
idleToggle.BorderSizePixel = 0
idleToggle.Text = "^"
idleToggle.Font = Enum.Font.GothamBlack
idleToggle.TextSize = 12
idleToggle.TextColor3 = Color3.fromRGB(255, 242, 242)
idleToggle.AutoButtonColor = false
idleToggle.ZIndex = 4
idleToggle.Parent = main
makeCorner(idleToggle, 7)
makeStroke(idleToggle, 1, 0.12, Color3.fromRGB(255, 0, 0))
local idleToggleGrad = styleBomText(idleToggle)

local idleMenu = Instance.new("Frame")
idleMenu.Size = UDim2.new(1, -10, 0, 0)
idleMenu.Position = UDim2.new(0, 5, 0, 72)
idleMenu.BackgroundColor3 = Color3.fromRGB(22, 22, 26)
idleMenu.BackgroundTransparency = 0.05
idleMenu.Visible = false
idleMenu.BorderSizePixel = 0
idleMenu.ClipsDescendants = true
idleMenu.ZIndex = 4
idleMenu.Parent = main
makeCorner(idleMenu, 10)
makeStroke(idleMenu, 1, 0.15, Color3.fromRGB(255, 0, 0))

local idleScroll = Instance.new("ScrollingFrame")
idleScroll.Size = UDim2.new(1, -8, 1, -8)
idleScroll.Position = UDim2.new(0, 4, 0, 4)
idleScroll.BackgroundTransparency = 1
idleScroll.BorderSizePixel = 0
idleScroll.ScrollBarThickness = 4
idleScroll.ScrollBarImageColor3 = Color3.fromRGB(255, 0, 0)
idleScroll.CanvasSize = UDim2.new(0, 0, 0, 0)
idleScroll.ZIndex = 5
idleScroll.Parent = idleMenu

local idleLayout = Instance.new("UIListLayout")
idleLayout.Padding = UDim.new(0, 4)
idleLayout.SortOrder = Enum.SortOrder.LayoutOrder
idleLayout.Parent = idleScroll

local idlePad = Instance.new("UIPadding")
idlePad.PaddingTop = UDim.new(0, 2)
idlePad.PaddingBottom = UDim.new(0, 2)
idlePad.PaddingLeft = UDim.new(0, 2)
idlePad.PaddingRight = UDim.new(0, 2)
idlePad.Parent = idleScroll

local function refreshIdleMenu()
	for _, ch in ipairs(idleScroll:GetChildren()) do
		if ch:IsA("TextButton") then
			ch:Destroy()
		end
	end

	local y = 0
	for _, info in ipairs(idleR15List) do
		local b = makeIdleButton(idleScroll, info.name, y, selectedIdleR15 and selectedIdleR15.id == info.id)
		b.MouseButton1Click:Connect(function()
			selectedIdleR15 = info
			refreshIdleMenu()

			local char = getChar()
			local hum = getHumanoid(char)
			if hum and currentRigType == Enum.HumanoidRigType.R15 then
				loadFlyAnimations(hum)
				setFlyAnimation(speeds, hum.MoveDirection.Magnitude > 0.01)
			end
		end)
		y += 26
	end

	idleScroll.CanvasSize = UDim2.new(0, 0, 0, y)
end

refreshIdleMenu()

local function setMenu(opened)
	idleMenuOpen = opened
	idleToggle.Text = opened and "v" or "^"

	local targetMainHeight = opened and 190 or 76
	local targetMenuHeight = opened and 112 or 0

	if opened then
		idleMenu.Visible = true
	end

	TweenService:Create(main, TweenInfo.new(0.25, Enum.EasingStyle.Quad, Enum.EasingDirection.Out), {
		Size = UDim2.new(0, 170, 0, targetMainHeight)
	}):Play()

	local tween = TweenService:Create(idleMenu, TweenInfo.new(0.25, Enum.EasingStyle.Quad, Enum.EasingDirection.Out), {
		Size = UDim2.new(1, -10, 0, targetMenuHeight)
	})

	tween:Play()

	if not opened then
		tween.Completed:Once(function()
			idleMenu.Visible = false
		end)
	end
end

idleToggle.MouseButton1Click:Connect(function()
	setMenu(not idleMenuOpen)
end)

flyBtn.MouseButton1Click:Connect(function()
	toggleFly()
	flyBtn.Text = nowe and "Tắt" or "Bay"
end)

speedBox.FocusLost:Connect(function()
	local n = tonumber(speedBox.Text)
	if not n or n <= 0 then
		speedBox.Text = tostring(speeds)
		return
	end

	speeds = n
	speedBox.Text = tostring(speeds)

	if nowe then
		local char = getChar()
		local hum = getHumanoid(char)
		if hum then
			setFlyAnimation(speeds, hum.MoveDirection.Magnitude > 0.01)
		end
	end
end)

RunService.Heartbeat:Connect(function()
	if not currentTrack then
		return
	end

	local _, hum = getChar()
	if not hum then
		return
	end

	if lockMode then
		if not currentTrack.IsPlaying and currentData then
			setFlyAnimation(speeds, hum.MoveDirection.Magnitude > 0.01)
		end
	else
		if hum.MoveDirection.Magnitude > 0.01 and currentTrack.IsPlaying then
			stopFlyAnimations()
		end
	end
end)

task.spawn(function()
	while gui.Parent do
		task.wait(0.05)
		local r = (tick() * 25) % 360
		titleGrad.Rotation = r
		speedTextGrad.Rotation = r
		flyTextGrad.Rotation = r
		offTextGrad.Rotation = r
		idleToggleGrad.Rotation = r
		mainGrad.Rotation = (tick() * 12) % 360
		speedGrad.Rotation = (tick() * 16) % 360
		flyGrad.Rotation = (tick() * 18) % 360
		lineGrad.Rotation = (tick() * 20) % 360
		glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
	end
end)

]]},

{Text = {vn = "Tốc Độ", en = "Speed"}, Script = [[
local Players = game.Players
local StarterGui = game.StarterGui
local HttpService = game.HttpService
local RunService = game.RunService
local player = Players.LocalPlayer
local playerGui = player:WaitForChild("PlayerGui")

local SaveFileName = "SpeedSettings.json"
local defaultSpeed = 16

local function saveData(data)
	pcall(function()
		if writefile then
			writefile(SaveFileName, HttpService:JSONEncode(data))
		end
	end)
end

local function loadData()
	local data = { SpeedValue = 16 }
	pcall(function()
		if readfile and isfile and isfile(SaveFileName) then
			data = HttpService:JSONDecode(readfile(SaveFileName))
		end
	end)
	return data
end

local savedData = loadData()
local lastSpeed = savedData.SpeedValue or 16
local currentSpeed = lastSpeed
local isSpeedOn = false

local old = playerGui:FindFirstChild("Bom2devSpeedUI")
if old then
	old:Destroy()
end

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devSpeedUI"
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.Parent = playerGui

local main = Instance.new("Frame")
main.Size = UDim2.new(0, 150, 0, 65)
main.Position = UDim2.new(0.05, 0, 0.8, 0)
main.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
main.BackgroundTransparency = 0.03
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true
main.Parent = gui

local mainCorner = Instance.new("UICorner")
mainCorner.CornerRadius = UDim.new(0, 12)
mainCorner.Parent = main

local mainStroke = Instance.new("UIStroke")
mainStroke.Thickness = 1.5
mainStroke.Transparency = 0.12
mainStroke.Color = Color3.fromRGB(255, 0, 0)
mainStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
mainStroke.LineJoinMode = Enum.LineJoinMode.Round
mainStroke.Parent = main

local mainGrad = Instance.new("UIGradient")
mainGrad.Rotation = 22
mainGrad.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.18, Color3.fromRGB(70, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
	ColorSequenceKeypoint.new(0.82, Color3.fromRGB(70, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
mainGrad.Transparency = NumberSequence.new({
	NumberSequenceKeypoint.new(0, 0.08),
	NumberSequenceKeypoint.new(1, 0.03)
})
mainGrad.Parent = main

local glow = Instance.new("ImageLabel")
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.92
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)
glow.ZIndex = 0
glow.Parent = main

local line = Instance.new("Frame")
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 27)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0
line.ZIndex = 2
line.Parent = main

local lineGrad = Instance.new("UIGradient")
lineGrad.Rotation = 0
lineGrad.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
lineGrad.Parent = line

local function styleBomText(obj)
	obj.TextColor3 = Color3.fromRGB(255, 242, 242)
	obj.Font = Enum.Font.GothamBlack

	local g = Instance.new("UIGradient")
	g.Rotation = 0
	g.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	})
	g.Parent = obj

	return g
end

local title = Instance.new("TextLabel")
title.Size = UDim2.new(1, -14, 0, 16)
title.Position = UDim2.new(0, 7, 0, 4)
title.BackgroundTransparency = 1
title.Text = "Tốc Độ"
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left
title.ZIndex = 3
title.Parent = main

local titleGrad = styleBomText(title)

local speedBox = Instance.new("TextBox")
speedBox.Size = UDim2.new(0.58, -8, 0, 25)
speedBox.Position = UDim2.new(0, 7, 0, 35)
speedBox.BackgroundColor3 = Color3.fromRGB(34, 34, 38)
speedBox.BackgroundTransparency = 0.03
speedBox.BorderSizePixel = 0
speedBox.Text = tostring(lastSpeed)
speedBox.PlaceholderText = "Tốc độ"
speedBox.PlaceholderColor3 = Color3.fromRGB(210, 210, 210)
speedBox.TextColor3 = Color3.fromRGB(255, 242, 242)
speedBox.Font = Enum.Font.GothamBlack
speedBox.TextSize = 13
speedBox.ClearTextOnFocus = false
speedBox.ZIndex = 3
speedBox.Parent = main

local speedCorner = Instance.new("UICorner")
speedCorner.CornerRadius = UDim.new(0, 8)
speedCorner.Parent = speedBox

local speedStroke = Instance.new("UIStroke")
speedStroke.Color = Color3.fromRGB(255, 0, 0)
speedStroke.Transparency = 0
speedStroke.Thickness = 1
speedStroke.Parent = speedBox

local speedGrad = Instance.new("UIGradient")
speedGrad.Rotation = 0
speedGrad.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(200, 200, 200)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
speedGrad.Parent = speedBox

local speedTextGrad = styleBomText(speedBox)

local button = Instance.new("TextButton")
button.Size = UDim2.new(0.34, 0, 0, 25)
button.Position = UDim2.new(0.66, -2, 0, 35)
button.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
button.BackgroundTransparency = 0.02
button.BorderSizePixel = 0
button.Text = "Bật"
button.Font = Enum.Font.GothamBlack
button.TextSize = 12
button.TextXAlignment = Enum.TextXAlignment.Center
button.TextYAlignment = Enum.TextYAlignment.Center
button.AutoButtonColor = false
button.ZIndex = 3
button.Parent = main

local buttonCorner = Instance.new("UICorner")
buttonCorner.CornerRadius = UDim.new(0, 8)
buttonCorner.Parent = button

local buttonStroke = Instance.new("UIStroke")
buttonStroke.Color = Color3.fromRGB(255, 0, 0)
buttonStroke.Transparency = 0
buttonStroke.Thickness = 1
buttonStroke.Parent = button

local buttonGrad = Instance.new("UIGradient")
buttonGrad.Rotation = 0
buttonGrad.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(150, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
buttonGrad.Parent = button

local buttonTextGrad = styleBomText(button)

local function getHumanoid()
	local char = player.Character
	if not char then
		return nil
	end
	return char:FindFirstChildOfClass("Humanoid")
end

local function applySpeed()
	local humanoid = getHumanoid()
	if humanoid and isSpeedOn then
		humanoid.WalkSpeed = currentSpeed
	elseif humanoid then
		humanoid.WalkSpeed = defaultSpeed
	end
end

speedBox.FocusLost:Connect(function()
	local num = tonumber(speedBox.Text)
	if not num then
		speedBox.Text = tostring(currentSpeed)
		return
	end

	currentSpeed = num
	lastSpeed = num
	saveData({ SpeedValue = num })

	if isSpeedOn then
		applySpeed()
	end
end)

button.MouseButton1Click:Connect(function()
	local humanoid = getHumanoid()
	if not humanoid then
		return
	end

	local num = tonumber(speedBox.Text)
	if num then
		currentSpeed = num
		lastSpeed = num
		saveData({ SpeedValue = num })
	end

	isSpeedOn = not isSpeedOn

	if isSpeedOn then
		humanoid.WalkSpeed = currentSpeed
		button.Text = "Tắt"
		button.BackgroundColor3 = Color3.fromRGB(120, 0, 0)
	else
		humanoid.WalkSpeed = defaultSpeed
		button.Text = "Bật"
		button.BackgroundColor3 = Color3.fromRGB(100, 0, 0)
	end
end)

player.CharacterAdded:Connect(function()
	task.wait(0.5)
	applySpeed()
end)

RunService.RenderStepped:Connect(function()
	if isSpeedOn then
		local humanoid = getHumanoid()
		if humanoid and humanoid.WalkSpeed ~= currentSpeed then
			humanoid.WalkSpeed = currentSpeed
		end
	end
end)

task.spawn(function()
	while gui.Parent do
		task.wait(0.05)

		local r = (tick() * 25) % 360
		titleGrad.Rotation = r
		speedTextGrad.Rotation = r
		buttonTextGrad.Rotation = r

		mainGrad.Rotation = (tick() * 12) % 360
		speedGrad.Rotation = (tick() * 16) % 360
		buttonGrad.Rotation = (tick() * 18) % 360
		lineGrad.Rotation = (tick() * 20) % 360
		glow.ImageTransparency = 0.92 - (math.sin(tick() * 2) * 0.02)
	end
end)

]]},

{Text = {vn = "Nhảy Cao", en = "JumpPower"}, Script = [[

local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local HttpService = game:GetService("HttpService")

local player = Players.LocalPlayer
local playerGui = player:WaitForChild("PlayerGui")

local SaveFileName = "JumpPSettings.json"
local DEFAULT_JUMP = 100

local function saveData(data)
pcall(function()
if writefile then
writefile(SaveFileName, HttpService:JSONEncode(data))
end
end)
end

local function loadData()
local data = { SpeedValue = DEFAULT_JUMP, On = false }

pcall(function()
	if readfile and isfile and isfile(SaveFileName) then
		local raw = readfile(SaveFileName)
		local ok, decoded = pcall(function()
			return HttpService:JSONDecode(raw)
		end)
		if ok and type(decoded) == "table" then
			data = decoded
		end
	end
end)

return data

end

local savedData = loadData()
local lastSpeed = tonumber(savedData.SpeedValue) or DEFAULT_JUMP
local currentSpeed = lastSpeed
local isSpeedOn = savedData.On == true

local old = playerGui:FindFirstChild("Bom2devJumpPUI")
if old then
pcall(function()
old:Destroy()
end)
end

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devJumpPUI"
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.Parent = playerGui

local main = Instance.new("Frame")
main.Size = UDim2.new(0, 150, 0, 65)
main.Position = UDim2.new(0.05, 0, 0.8, 0)
main.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
main.BackgroundTransparency = 0.03
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true
main.Parent = gui

local mainCorner = Instance.new("UICorner")
mainCorner.CornerRadius = UDim.new(0, 12)
mainCorner.Parent = main

local mainStroke = Instance.new("UIStroke")
mainStroke.Thickness = 1.5
mainStroke.Transparency = 0.12
mainStroke.Color = Color3.fromRGB(255, 0, 0)
mainStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
mainStroke.LineJoinMode = Enum.LineJoinMode.Round
mainStroke.Parent = main

local mainGrad = Instance.new("UIGradient")
mainGrad.Rotation = 22
mainGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.18, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
ColorSequenceKeypoint.new(0.82, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})
mainGrad.Parent = main

local glow = Instance.new("ImageLabel")
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.92
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)
glow.ZIndex = 0
glow.Parent = main

local line = Instance.new("Frame")
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 27)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0
line.ZIndex = 2
line.Parent = main

local lineGrad = Instance.new("UIGradient")
lineGrad.Rotation = 0
lineGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
lineGrad.Parent = line

local function styleBomText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack

local g = obj:FindFirstChildOfClass("UIGradient") or Instance.new("UIGradient")
g.Rotation = 0
g.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
g.Parent = obj
return g

end

local title = Instance.new("TextLabel")
title.Size = UDim2.new(1, -14, 0, 16)
title.Position = UDim2.new(0, 7, 0, 4)
title.BackgroundTransparency = 1
title.Text = "Nhảy cao"
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left
title.ZIndex = 3
title.Parent = main

local titleGrad = styleBomText(title)

local speedBox = Instance.new("TextBox")
speedBox.Size = UDim2.new(0.58, -8, 0, 25)
speedBox.Position = UDim2.new(0, 7, 0, 35)
speedBox.BackgroundColor3 = Color3.fromRGB(34, 34, 38)
speedBox.BackgroundTransparency = 0.03
speedBox.BorderSizePixel = 0
speedBox.Text = tostring(lastSpeed)
speedBox.PlaceholderText = "Lực"
speedBox.PlaceholderColor3 = Color3.fromRGB(210, 210, 210)
speedBox.TextColor3 = Color3.fromRGB(255, 242, 242)
speedBox.Font = Enum.Font.GothamBlack
speedBox.TextSize = 13
speedBox.ClearTextOnFocus = false
speedBox.ZIndex = 3
speedBox.Parent = main

local speedCorner = Instance.new("UICorner")
speedCorner.CornerRadius = UDim.new(0, 8)
speedCorner.Parent = speedBox

local speedStroke = Instance.new("UIStroke")
speedStroke.Color = Color3.fromRGB(255, 0, 0)
speedStroke.Transparency = 0
speedStroke.Thickness = 1
speedStroke.Parent = speedBox

local speedGrad = Instance.new("UIGradient")
speedGrad.Rotation = 0
speedGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(200, 200, 200)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
speedGrad.Parent = speedBox

local speedTextGrad = styleBomText(speedBox)

local button = Instance.new("TextButton")
button.Size = UDim2.new(0.34, 0, 0, 25)
button.Position = UDim2.new(0.66, -2, 0, 35)
button.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
button.BackgroundTransparency = 0.02
button.BorderSizePixel = 0
button.Text = "Bật"
button.Font = Enum.Font.GothamBlack
button.TextSize = 12
button.TextXAlignment = Enum.TextXAlignment.Center
button.TextYAlignment = Enum.TextYAlignment.Center
button.AutoButtonColor = false
button.ZIndex = 3
button.Parent = main

local buttonCorner = Instance.new("UICorner")
buttonCorner.CornerRadius = UDim.new(0, 8)
buttonCorner.Parent = button

local buttonStroke = Instance.new("UIStroke")
buttonStroke.Color = Color3.fromRGB(255, 0, 0)
buttonStroke.Transparency = 0
buttonStroke.Thickness = 1
buttonStroke.Parent = button

local buttonGrad = Instance.new("UIGradient")
buttonGrad.Rotation = 0
buttonGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(60, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
buttonGrad.Parent = button

local buttonTextGrad = styleBomText(button)

local function getHumanoid()
local char = player.Character
if not char then
return nil
end
return char:FindFirstChildOfClass("Humanoid")
end

local original = {}

local function applyJump()
local humanoid = getHumanoid()
if not humanoid then
return
end

if original[humanoid] == nil then
	original[humanoid] = {
		Jump = humanoid.JumpPower,
		Use = humanoid.UseJumpPower,
	}
end

humanoid.UseJumpPower = true
humanoid.JumpPower = currentSpeed

end

local function restoreJump(humanoid)
if not humanoid then
return
end

local data = original[humanoid]
if data then
	pcall(function()
		if data.Jump ~= nil then
			humanoid.JumpPower = data.Jump
		end
		if data.Use ~= nil then
			humanoid.UseJumpPower = data.Use
		end
	end)
	original[humanoid] = nil
end

end

local function refreshButton()
if isSpeedOn then
button.Text = "Tắt"
button.BackgroundColor3 = Color3.fromRGB(155, 0, 00)
else
button.Text = "Bật"
button.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end
end

if lastSpeed then
speedBox.Text = tostring(lastSpeed)
end

refreshButton()

speedBox.FocusLost:Connect(function()
local num = tonumber(speedBox.Text)
if not num then
speedBox.Text = tostring(currentSpeed)
return
end

currentSpeed = num
lastSpeed = num
saveData({ SpeedValue = num, On = isSpeedOn })

if isSpeedOn then
	applyJump()
end

end)

button.MouseButton1Click:Connect(function()
local humanoid = getHumanoid()
if not humanoid then
return
end

local num = tonumber(speedBox.Text)
if num then
	currentSpeed = num
	lastSpeed = num
	saveData({ SpeedValue = num, On = isSpeedOn })
end

isSpeedOn = not isSpeedOn

if isSpeedOn then
	applyJump()
else
	restoreJump(humanoid)
end

saveData({ SpeedValue = lastSpeed, On = isSpeedOn })
refreshButton()

end)

player.CharacterAdded:Connect(function(char)
task.wait(0.5)
local humanoid = char:FindFirstChildOfClass("Humanoid")
if humanoid and isSpeedOn then
applyJump()
end
end)

RunService.RenderStepped:Connect(function()
if not isSpeedOn then
return
end

local humanoid = getHumanoid()
if humanoid and humanoid.JumpPower ~= currentSpeed then
	humanoid.UseJumpPower = true
	humanoid.JumpPower = currentSpeed
end

end)

task.spawn(function()
while gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
titleGrad.Rotation = r
speedTextGrad.Rotation = r
buttonTextGrad.Rotation = r
mainGrad.Rotation = (tick() * 12) % 360
speedGrad.Rotation = (tick() * 16) % 360
buttonGrad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.92 - (math.sin(tick() * 2) * 0.02)
end
end)

]]},

{Text = {vn = "Nhảy Vô Hạn", en = "Infinite Jump"}, Script = [[

local StarterGui=game:GetService("StarterGui");local UserInputService=game:GetService("UserInputService");local Players=game:GetService("Players");local LocalPlayer=Players.LocalPlayer;getgenv().InfiniteJumpEnabled=not getgenv().InfiniteJumpEnabled;if getgenv().InfiniteJumpEnabled then StarterGui:SetCore("SendNotification",{Title="Nhảy Liên Tục",Text="",Duration=4});UserInputService.JumpRequest:Connect(function() if getgenv().InfiniteJumpEnabled then local char=LocalPlayer.Character;if char and char:FindFirstChildOfClass("Humanoid") then char:FindFirstChildOfClass("Humanoid"):ChangeState(Enum.HumanoidStateType.Jumping) end end end) else StarterGui:SetCore("SendNotification",{Title="Nhảy Liên Tục",Text="",Duration=4}) end


]]},

{Text = {vn = "Đi Trên Không V2", en = "Walking on Air V2"}, Script = [[

local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local UserInputService = game:GetService("UserInputService")
local TweenService = game:GetService("TweenService")

local player = Players.LocalPlayer
local playerGui = player:WaitForChild("PlayerGui")

if playerGui:FindFirstChild("DiTrenKhongGui") then
pcall(function()
playerGui.DiTrenKhongGui:Destroy()
end)
end

local platformName = "WalkOnVoidPlatform"

local function removePlatform()
local old = workspace:FindFirstChild(platformName)
if old then
old:Destroy()
end
end

if getgenv()._WalkOnVoidConn then
getgenv()._WalkOnVoidConn:Disconnect()
getgenv()._WalkOnVoidConn = nil
end

getgenv()._WalkOnVoid = false

local gui = Instance.new("ScreenGui")
gui.Name = "DiTrenKhongGui"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = playerGui

local main = Instance.new("Frame")
main.Parent = gui
main.Size = UDim2.new(0, 140, 0, 75)
main.Position = UDim2.new(0.06, 0, 0.42, 0)
main.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
main.BackgroundTransparency = 0.04
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true

local mainCorner = Instance.new("UICorner")
mainCorner.CornerRadius = UDim.new(0, 12)
mainCorner.Parent = main

local stroke = Instance.new("UIStroke")
stroke.Thickness = 1.5
stroke.Transparency = 0.12
stroke.Color = Color3.fromRGB(255, 0, 0)
stroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
stroke.LineJoinMode = Enum.LineJoinMode.Round
stroke.Parent = main

local mainGrad = Instance.new("UIGradient")
mainGrad.Rotation = 20
mainGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})
mainGrad.Parent = main

local glow = Instance.new("ImageLabel")
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)
glow.ZIndex = 0
glow.Parent = main

local function styleBomText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack

local g = Instance.new("UIGradient")
g.Rotation = 0
g.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
g.Parent = obj

return g

end

local toggleButton = Instance.new("TextButton")
toggleButton.Parent = main
toggleButton.Size = UDim2.new(0, 70, 0, 35)
toggleButton.Position = UDim2.new(0.5, -60, 0.5, -8)
toggleButton.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
toggleButton.BackgroundTransparency = 0.05
toggleButton.BorderSizePixel = 0
toggleButton.Font = Enum.Font.GothamBlack
toggleButton.TextSize = 12.5
toggleButton.Text = "BẬT"
toggleButton.TextXAlignment = Enum.TextXAlignment.Center
toggleButton.TextYAlignment = Enum.TextYAlignment.Center
toggleButton.AutoButtonColor = false
toggleButton.ZIndex = 3

local btnCorner = Instance.new("UICorner")
btnCorner.CornerRadius = UDim.new(0, 9)
btnCorner.Parent = toggleButton

local btnStroke = Instance.new("UIStroke")
btnStroke.Thickness = 1
btnStroke.Transparency = 0
btnStroke.Color = Color3.fromRGB(255, 0, 0)
btnStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
btnStroke.Parent = toggleButton

local btnGrad = Instance.new("UIGradient")
btnGrad.Rotation = 0
btnGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
btnGrad.Parent = toggleButton

local btnTextGrad = styleBomText(toggleButton)

local upBtn = Instance.new("TextButton")
upBtn.Parent = main
upBtn.Size = UDim2.new(0, 47, 0, 28)
upBtn.Position = UDim2.new(0.61, 0, 0, 10)
upBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
upBtn.BackgroundTransparency = 0.05
upBtn.BorderSizePixel = 0
upBtn.Text = "▲"
upBtn.Font = Enum.Font.GothamBlack
upBtn.TextSize = 18
upBtn.TextColor3 = Color3.fromRGB(255, 242, 242)
upBtn.AutoButtonColor = false

local upCorner = Instance.new("UICorner")
upCorner.CornerRadius = UDim.new(0, 6)
upCorner.Parent = upBtn

local upStroke = Instance.new("UIStroke")
upStroke.Thickness = 1
upStroke.Transparency = 0.12
upStroke.Color = Color3.fromRGB(255, 0, 0)
upStroke.Parent = upBtn

local upGrad = Instance.new("UIGradient")
upGrad.Rotation = 90
upGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
upGrad.Parent = upBtn

local upTextGrad = styleBomText(upBtn)

local downBtn = Instance.new("TextButton")
downBtn.Parent = main
downBtn.Size = UDim2.new(0, 47, 0, 28)
downBtn.Position = UDim2.new(0.61, 0, 0.6, -5)
downBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
downBtn.BackgroundTransparency = 0.05
downBtn.BorderSizePixel = 0
downBtn.Text = "▼"
downBtn.Font = Enum.Font.GothamBlack
downBtn.TextSize = 18
downBtn.TextColor3 = Color3.fromRGB(255, 242, 242)
downBtn.AutoButtonColor = false

local downCorner = Instance.new("UICorner")
downCorner.CornerRadius = UDim.new(0, 6)
downCorner.Parent = downBtn

local downStroke = Instance.new("UIStroke")
downStroke.Thickness = 1
downStroke.Transparency = 0.12
downStroke.Color = Color3.fromRGB(255, 0, 0)
downStroke.Parent = downBtn

local downGrad = Instance.new("UIGradient")
downGrad.Rotation = 90
downGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
downGrad.Parent = downBtn

local downTextGrad = styleBomText(downBtn)

local info = Instance.new("TextLabel")
info.Parent = main
info.Size = UDim2.new(0.6, -10, 0.2, 12)
info.Position = UDim2.new(0, 10, 0, 0)
info.BackgroundTransparency = 1
info.Font = Enum.Font.GothamBlack
info.TextScaled = true
info.Text = "Đi Trên Không V2"
info.TextColor3 = Color3.fromRGB(200, 200, 200)
info.TextXAlignment = Enum.TextXAlignment.Left

local infoGrad = styleBomText(info)

toggleButton.MouseEnter:Connect(function()
toggleButton.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

toggleButton.MouseLeave:Connect(function()
toggleButton.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

upBtn.MouseEnter:Connect(function()
upBtn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

upBtn.MouseLeave:Connect(function()
upBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

downBtn.MouseEnter:Connect(function()
downBtn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

downBtn.MouseLeave:Connect(function()
downBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

task.spawn(function()
while gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
titleGrad.Rotation = r
btnTextGrad.Rotation = r
infoGrad.Rotation = r
mainGrad.Rotation = (tick() * 12) % 360
btnGrad.Rotation = (tick() * 18) % 360
upTextGrad.Rotation = r
upGrad.Rotation = (tick() * 18) % 360
downTextGrad.Rotation = r
downGrad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
end
end)

local MOVE_SPEED = 10

local STEP = 0.1

local Y_CLAMP_MIN = -200

local Y_CLAMP_MAX = 200

local platform

local baseY = 0

local yVal

local holdUp = false

local holdDown = false

local heartbeatConn

local currentUpCoroutine

local currentDownCoroutine

local function enable()

	getgenv()._WalkOnVoid = true

	local char = player.Character or player.CharacterAdded:Wait()

	local root = char:WaitForChild("HumanoidRootPart", 5)

	if not root then

		getgenv()._WalkOnVoid = false

		return

	end

	removePlatform()

	platform = Instance.new("Part")

	platform.Name = platformName

	platform.Size = Vector3.new(1000,50,1000)

	platform.Anchored = true

	platform.Transparency = 1

	platform.CanCollide = true

	platform.Parent = workspace

	yVal = Instance.new("NumberValue")

	yVal.Name = "YOffset"

	yVal.Value = 0

	yVal.Parent = platform

	baseY = root.Position.Y - 28.5

	if heartbeatConn then heartbeatConn:Disconnect(); heartbeatConn = nil end

	heartbeatConn = RunService.RenderStepped:Connect(function()

		if not root or not root.Parent or not platform or not platform.Parent then return end

		platform.Position = Vector3.new(root.Position.X, baseY + (yVal and yVal.Value or 0), root.Position.Z)

	end)

	char:WaitForChild("Humanoid").Died:Connect(function()

		removePlatform()

		if heartbeatConn then heartbeatConn:Disconnect(); heartbeatConn = nil end

		getgenv()._WalkOnVoid = false

		toggleButton.Text = "BẬT"

		holdUp = false

		holdDown = false

		if currentUpCoroutine then currentUpCoroutine = nil end

		if currentDownCoroutine then currentDownCoroutine = nil end

	end)

	toggleButton.Text = "TẮT"

end

local function disable()

	getgenv()._WalkOnVoid = false

	holdUp = false

	holdDown = false

	if heartbeatConn then heartbeatConn:Disconnect(); heartbeatConn = nil end

	removePlatform()

	toggleButton.Text = "BẬT"

	if currentUpCoroutine then currentUpCoroutine = nil end

	if currentDownCoroutine then currentDownCoroutine = nil end

end

toggleButton.MouseButton1Click:Connect(function()

	if getgenv()._WalkOnVoid then

		disable()

	else

		enable()

	end

end)

local function startHoldUp()

	if not platform or not platform.Parent or not yVal then return end

	if holdUp then return end

	holdUp = true

	currentUpCoroutine = coroutine.create(function()

		while holdUp and platform and platform.Parent do

			local cur = yVal.Value

			local delta = MOVE_SPEED * STEP

			local new = math.clamp(cur + delta, Y_CLAMP_MIN, Y_CLAMP_MAX)

			local tw = TweenService:Create(yVal, TweenInfo.new(STEP, Enum.EasingStyle.Linear), {Value = new})

			tw:Play()

			tw.Completed:Wait()

			if not holdUp then break end

		end

		holdUp = false

	end)

	coroutine.resume(currentUpCoroutine)

end

local function stopHoldUp()

	holdUp = false

end

local function startHoldDown()

	if not platform or not platform.Parent or not yVal then return end

	if holdDown then return end

	holdDown = true

	currentDownCoroutine = coroutine.create(function()

		while holdDown and platform and platform.Parent do

			local cur = yVal.Value

			local delta = MOVE_SPEED * STEP

			local new = math.clamp(cur - delta, Y_CLAMP_MIN, Y_CLAMP_MAX)

			local tw = TweenService:Create(yVal, TweenInfo.new(STEP, Enum.EasingStyle.Linear), {Value = new})

			tw:Play()

			tw.Completed:Wait()

			if not holdDown then break end

		end

		holdDown = false

	end)

	coroutine.resume(currentDownCoroutine)

end

local function stopHoldDown()

	holdDown = false

end

upBtn.InputBegan:Connect(function(input)

	if input.UserInputType == Enum.UserInputType.MouseButton1 or input.UserInputType == Enum.UserInputType.Touch then

		startHoldUp()

	end

end)

upBtn.InputEnded:Connect(function(input)

	if input.UserInputType == Enum.UserInputType.MouseButton1 or input.UserInputType == Enum.UserInputType.Touch then

		stopHoldUp()

	end

end)

upBtn.MouseLeave:Connect(stopHoldUp)

upBtn.MouseButton1Up:Connect(stopHoldUp)

downBtn.InputBegan:Connect(function(input)

	if input.UserInputType == Enum.UserInputType.MouseButton1 or input.UserInputType == Enum.UserInputType.Touch then

		startHoldDown()

	end

end)

downBtn.InputEnded:Connect(function(input)

	if input.UserInputType == Enum.UserInputType.MouseButton1 or input.UserInputType == Enum.UserInputType.Touch then

		stopHoldDown()

	end

end)

downBtn.MouseLeave:Connect(stopHoldDown)

downBtn.MouseButton1Up:Connect(stopHoldDown)

]]},

{Text = {vn = "Tăng Tầm Xa Camera(Client)", en = "Increase Camera Range(Client)"}, Script = [[

local Players=game:GetService("Players");local player=Players.LocalPlayer;local camera=game.Workspace.CurrentCamera;game.StarterGui:SetCore("SendNotification",{Title="Bẻ Khoá Camera",Text="Đã bẻ khoá camera!",Duration=3});local function unlockCamera() player.CameraMode=Enum.CameraMode.Classic;player.CameraMaxZoomDistance=1000;player.CameraMinZoomDistance=0.5;camera.CameraType=Enum.CameraType.Custom end;unlockCamera();game:GetService("RunService").RenderStepped:Connect(function() if player.CameraMode~=Enum.CameraMode.Classic then player.CameraMode=Enum.CameraMode.Classic end;if player.CameraMaxZoomDistance<50 then player.CameraMaxZoomDistance=50 end;if player.CameraMinZoomDistance>0.5 then player.CameraMinZoomDistance=0.5 end;if camera.CameraType~=Enum.CameraType.Custom then camera.CameraType=Enum.CameraType.Custom end end)


]]},

{Text = {vn = "Xuyên Tường", en = "No clips"}, Script = [[

getgenv()._NOCLIP=not getgenv()._NOCLIP;local Players=game:GetService("Players");local RunService=game:GetService("RunService");local plr=Players.LocalPlayer;getgenv()._NC_STATES=getgenv()._NC_STATES or {};if not getgenv()._NOCLIP then if getgenv()._NC_CONN then getgenv()._NC_CONN:Disconnect();getgenv()._NC_CONN=nil end;local char=plr.Character;if char then for _,v in pairs(char:GetDescendants()) do if v:IsA("BasePart") and getgenv()._NC_STATES[v]~=nil then v.CanCollide=getgenv()._NC_STATES[v] end end end;getgenv()._NC_STATES={};return end;if getgenv()._NC_CONN then getgenv()._NC_CONN:Disconnect() end;getgenv()._NC_CONN=RunService.Stepped:Connect(function()local char=plr.Character;if not char then return end;for _,v in pairs(char:GetDescendants()) do if v:IsA("BasePart") then if getgenv()._NC_STATES[v]==nil then getgenv()._NC_STATES[v]=v.CanCollide end;v.CanCollide=false end end end)


]]},

{Text = {vn = "Nhìn Trong Bóng Tối(Client)", en = "Night Vission(Client)"}, Script = [[

getgenv()._NightVision = not getgenv()._NightVision

local Lighting = game:GetService("Lighting")

local RunService = game:GetService("RunService")

if getgenv()._NightVisionLoop then

	getgenv()._NightVisionLoop:Disconnect()	getgenv()._NightVisionLoop = nil

end

local cc = Lighting:FindFirstChild("NV_CC")

if not cc then

	cc = Instance.new("ColorCorrectionEffect")

	cc.Name = "NV_CC"

	cc.Parent = Lighting

end

if getgenv()._NightVision and not getgenv()._NV_Backup then

	getgenv()._NV_Backup = {

		FogEnd = Lighting.FogEnd,

		FogStart = Lighting.FogStart,

		FogColor = Lighting.FogColor,

		Brightness = Lighting.Brightness,

		ClockTime = Lighting.ClockTime,

		GlobalShadows = Lighting.GlobalShadows

	}

end

if getgenv()._NightVision then

	getgenv()._NightVisionLoop = RunService.RenderStepped:Connect(function()

		Lighting.FogColor = Color3.fromRGB(255,255,255)

		Lighting.FogEnd = 999999

		Lighting.FogStart = 999999

		Lighting.Brightness = 4

		Lighting.ClockTime = 14

		Lighting.GlobalShadows = false

		cc.Enabled = true

		cc.Brightness = 0.2

		cc.Contrast = 0.3

		cc.Saturation = 0.2

		cc.TintColor = Color3.fromRGB(255,255,255)

	end)

else

	cc.Enabled = false

	if getgenv()._NV_Backup then

		Lighting.FogEnd = getgenv()._NV_Backup.FogEnd

		Lighting.FogStart = getgenv()._NV_Backup.FogStart

		Lighting.FogColor = getgenv()._NV_Backup.FogColor

		Lighting.Brightness = getgenv()._NV_Backup.Brightness

		Lighting.ClockTime = getgenv()._NV_Backup.ClockTime

		Lighting.GlobalShadows = getgenv()._NV_Backup.GlobalShadows

		getgenv()._NV_Backup = nil

	end

end

]]},

{Text = {vn = "Tốc Biến", en = "Flash"}, Script = [[

local Players=game:GetService("Players")

local player=Players.LocalPlayer

local playerGui=player:WaitForChild("PlayerGui")

local mouse=player:GetMouse()

local Workspace=game:GetService("Workspace")

if playerGui:FindFirstChild("TeleportButtonGui") then

	playerGui.TeleportButtonGui:Destroy()end

local gui=Instance.new("ScreenGui")

gui.Name="TeleportButtonGui"

gui.Parent=playerGui

gui.IgnoreGuiInset=true

gui.ResetOnSpawn=false

local btn=Instance.new("TextButton")

btn.Name="TeleportBtn"

btn.Size=UDim2.new(0,50,0,50)

btn.Position=UDim2.new(1,-60,0.5,-25)

btn.AnchorPoint=Vector2.new(0,0.5)

btn.BackgroundColor3=Color3.fromRGB(30,30,30)

btn.BorderSizePixel=0

btn.Text="⚡"

btn.Font=Enum.Font.GothamBold

btn.TextSize=24

btn.TextColor3=Color3.fromRGB(0,255,200)

btn.Parent=gui

btn.Active=true

btn.Draggable=true

local corner=Instance.new("UICorner",btn)

corner.CornerRadius=UDim.new(0,25)

local stroke=Instance.new("UIStroke",btn)

stroke.Thickness=3

stroke.ApplyStrokeMode=Enum.ApplyStrokeMode.Border

task.spawn(function()

	local h=0

	while btn.Parent do

		h=(h+0.005)%1

		stroke.Color=Color3.fromHSV(h,1,1)

		task.wait(0.02)

	end

end)

local teleportActive=false

local clickConn=nil

local function disableTeleport()

	if clickConn then

		clickConn:Disconnect()

		clickConn=nil

	end

	teleportActive=false

	btn.TextColor3=Color3.fromRGB(0,255,200)

end

local function enableTeleport()

	disableTeleport()

	teleportActive=true

	btn.TextColor3=Color3.fromRGB(255,120,120)

	clickConn=mouse.Button1Down:Connect(function()

		local char=player.Character

		if not char then return end

		local hrp=char:FindFirstChild("HumanoidRootPart")

		if not hrp then return end

		hrp.CFrame=CFrame.new(mouse.Hit.Position + Vector3.new(0,3,0))

	end)

end

btn.MouseButton1Click:Connect(function()

	if teleportActive then

		disableTeleport()

	else

		enableTeleport()

	end

end)

]]},
{Text = {vn = "Nhân Đôi Tool(Client)", en = "Dupe Tool(Client)"}, Script = [[

local Players = game:GetService("Players")

local player = Players.LocalPlayer

local function cloneEquippedTool()

	local character = player.Character	if not character then return end

	local tool = character:FindFirstChildOfClass("Tool")

	if not tool then return end

	local clone = tool:Clone()

	clone.Parent = player.Backpack

end

cloneEquippedTool()

]]},
{Text = {vn = "Toạ Độ", en = "Coordinates"}, Script = [[
local Players = game.Players
local RunService = game.RunService
local CoreGui = game.CoreGui

local G = (getgenv and getgenv()) or _G
G.Bom2devCoords = G.Bom2devCoords or {active = false}

if G.Bom2devCoords.active then
	G.Bom2devCoords.active = false

	if G.Bom2devCoords.conn then
		G.Bom2devCoords.conn:Disconnect()
	end

	if G.Bom2devCoords.gui then
		G.Bom2devCoords.gui:Destroy()
	end

	G.Bom2devCoords = {active = false}
	return
end

G.Bom2devCoords.active = true

local player = Players.LocalPlayer

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devCoordsGui"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = CoreGui

local label = Instance.new("TextLabel")
label.Parent = gui
label.AnchorPoint = Vector2.new(0.5, 0)
label.Position = UDim2.new(0.5, 0, 0, 40)
label.Size = UDim2.new(0, 420, 0, 32)
label.BackgroundTransparency = 1
label.TextColor3 = Color3.fromRGB(255,255,255)
label.TextStrokeTransparency = 0
label.Font = Enum.Font.GothamBold
label.TextSize = 14
label.TextXAlignment = Enum.TextXAlignment.Center
label.Text = "X: 0 | Y: 0 | Z: 0"

local conn
conn = RunService.RenderStepped:Connect(function()
	local char = player.Character
	if not char then return end

	local root = char:FindFirstChild("HumanoidRootPart")
	if not root then return end

	local pos = root.Position

	label.Text = string.format(
		"X: %.2f | Y: %.2f | Z: %.2f",
		pos.X,
		pos.Y,
		pos.Z
	)
end)

G.Bom2devCoords.conn = conn
G.Bom2devCoords.gui = gui
]]},
{Text = {vn = "Dịch Chuyển", en = "Teleport"}, Script = [[

local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local LocalPlayer = Players.LocalPlayer
local playerGui = LocalPlayer:WaitForChild("PlayerGui")

local oldGui = playerGui:FindFirstChild("TeleportGui")
if oldGui then oldGui:Destroy() end

local gui = Instance.new("ScreenGui")
gui.Name = "TeleportGui"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = playerGui

local function corner(obj, r)
	local c = Instance.new("UICorner")
	c.CornerRadius = UDim.new(0, r or 12)
	c.Parent = obj
	return c
end

local function stroke(obj, thick, trans, color)
	local s = Instance.new("UIStroke")
	s.Thickness = thick or 1
	s.Transparency = trans or 0
	s.Color = color or Color3.fromRGB(255, 0, 0)
	s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
	s.LineJoinMode = Enum.LineJoinMode.Round
	s.Parent = obj
	return s
end

local function gradient(obj, seq, rot)
	local g = Instance.new("UIGradient")
	g.Color = seq
	g.Rotation = rot or 0
	g.Parent = obj
	return g
end

local function styleBomText(obj)
	obj.TextColor3 = Color3.fromRGB(255, 242, 242)
	obj.Font = Enum.Font.GothamBlack
	local g = Instance.new("UIGradient")
	g.Rotation = 0
	g.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	})
	g.Parent = obj
	return g
end

local main = Instance.new("Frame")
main.Size = UDim2.new(0, 190, 0, 120)
main.Position = UDim2.new(0.5, -95, 0.4, -60)
main.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
main.BackgroundTransparency = 0.5
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true
main.Parent = gui

corner(main, 12)
stroke(main, 1.35, 0.12, Color3.fromRGB(255, 0, 0))

local mainGrad = gradient(main, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.2, Color3.fromRGB(78, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
	ColorSequenceKeypoint.new(0.8, Color3.fromRGB(78, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 25)
mainGrad.Transparency = NumberSequence.new({
	NumberSequenceKeypoint.new(0, 0.08),
	NumberSequenceKeypoint.new(1, 0.03)
})

local glow = Instance.new("ImageLabel")
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)
glow.Parent = main

local line = Instance.new("Frame")
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 24)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0
line.Parent = main

local lineGrad = gradient(line, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)

local title = Instance.new("TextLabel")
title.Size = UDim2.new(1, -14, 0, 16)
title.Position = UDim2.new(0, 8, 0, 4)
title.BackgroundTransparency = 1
title.Text = "Teleport"
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left
title.Parent = main
styleBomText(title)

local speedBox = Instance.new("TextBox")
speedBox.Size = UDim2.new(0.44, 0, 0, 22)
speedBox.Position = UDim2.new(0.05, 0, 0, 30)
speedBox.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
speedBox.BackgroundTransparency = 1
speedBox.BorderSizePixel = 0
speedBox.PlaceholderText = "100"
speedBox.PlaceholderColor3 = Color3.fromRGB(180, 180, 180)
speedBox.ClearTextOnFocus = false
speedBox.Font = Enum.Font.GothamBlack
speedBox.TextSize = 12
speedBox.TextColor3 = Color3.fromRGB(255, 255, 255)
speedBox.Text = "100"
speedBox.TextXAlignment = Enum.TextXAlignment.Center
speedBox.Parent = main
corner(speedBox, 8)
stroke(speedBox, 1, 0.1, Color3.fromRGB(255, 0, 0))
gradient(speedBox, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)
styleBomText(speedBox)

local saveBtn = Instance.new("TextButton")
saveBtn.Size = UDim2.new(0.42, 0, 0, 22)
saveBtn.Position = UDim2.new(0.53, 0, 0, 30)
saveBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
saveBtn.BackgroundTransparency = 1
saveBtn.BorderSizePixel = 0
saveBtn.Text = "Lưu"
saveBtn.Font = Enum.Font.GothamBlack
saveBtn.TextSize = 12
saveBtn.TextXAlignment = Enum.TextXAlignment.Center
saveBtn.TextYAlignment = Enum.TextYAlignment.Center
saveBtn.AutoButtonColor = false
saveBtn.Parent = main
corner(saveBtn, 8)
stroke(saveBtn, 1, 0.1, Color3.fromRGB(255, 0, 0))
gradient(saveBtn, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)
styleBomText(saveBtn)

local locationDropdown = Instance.new("TextBox")
locationDropdown.Size = UDim2.new(0.8, -8, 0, 22)
locationDropdown.Position = UDim2.new(0.05, 0, 0, 58)
locationDropdown.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
locationDropdown.BackgroundTransparency = 1
locationDropdown.BorderSizePixel = 0
locationDropdown.PlaceholderText = "Địa điểm"
locationDropdown.PlaceholderColor3 = Color3.fromRGB(180, 180, 180)
locationDropdown.ClearTextOnFocus = false
locationDropdown.Font = Enum.Font.GothamBlack
locationDropdown.TextSize = 12
locationDropdown.TextColor3 = Color3.fromRGB(255, 255, 255)
locationDropdown.TextXAlignment = Enum.TextXAlignment.Center
locationDropdown.Text = ""
locationDropdown.Parent = main
corner(locationDropdown, 8)
stroke(locationDropdown, 1, 0.1, Color3.fromRGB(255, 0, 0))
gradient(locationDropdown, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)
styleBomText(locationDropdown)

local drawerBtn = Instance.new("ImageButton")
drawerBtn.Size = UDim2.new(0, 22, 0, 22)
drawerBtn.Position = UDim2.new(0.83, 0, 0, 58)
drawerBtn.BackgroundTransparency = 1
drawerBtn.BorderSizePixel = 0
drawerBtn.AutoButtonColor = false
drawerBtn.ScaleType = Enum.ScaleType.Fit
drawerBtn.Image = "rbxassetid://3926305904"
drawerBtn.ImageRectOffset = Vector2.new(325, 324)
drawerBtn.ImageRectSize = Vector2.new(36, 36)
drawerBtn.Parent = main

local modeBtn = Instance.new("TextButton")
modeBtn.Size = UDim2.new(0.44, 0, 0, 22)
modeBtn.Position = UDim2.new(0.05, 0, 0, 85)
modeBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
modeBtn.BackgroundTransparency = 1
modeBtn.BorderSizePixel = 0
modeBtn.Text = "Kéo"
modeBtn.Font = Enum.Font.GothamBlack
modeBtn.TextSize = 12
modeBtn.TextXAlignment = Enum.TextXAlignment.Center
modeBtn.TextYAlignment = Enum.TextYAlignment.Center
modeBtn.AutoButtonColor = false
modeBtn.Parent = main
corner(modeBtn, 8)
stroke(modeBtn, 1, 0.1, Color3.fromRGB(255, 0, 0))
gradient(modeBtn, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)
styleBomText(modeBtn)

modeBtn.MouseButton1Click:Connect(function()
	if modeBtn.Text == "Kéo" then
		modeBtn.Text = "Dịch Chuyển"
	else
		modeBtn.Text = "Kéo"
	end
end)

local goBtn = Instance.new("TextButton")
goBtn.Size = UDim2.new(0.42, 0, 0, 22)
goBtn.Position = UDim2.new(0.53, 0, 0, 85)
goBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
goBtn.BackgroundTransparency = 1
goBtn.BorderSizePixel = 0
goBtn.Text = "Đến"
goBtn.Font = Enum.Font.GothamBlack
goBtn.TextSize = 12
goBtn.TextXAlignment = Enum.TextXAlignment.Center
goBtn.TextYAlignment = Enum.TextYAlignment.Center
goBtn.AutoButtonColor = false
goBtn.Parent = main
corner(goBtn, 8)
stroke(goBtn, 1, 0.1, Color3.fromRGB(255, 0, 0))
gradient(goBtn, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)
styleBomText(goBtn)

local drawer = Instance.new("Frame")
drawer.Size = UDim2.new(0, 120, 0, 120)
drawer.Position = UDim2.new(1.03, 0, 0, 0)
drawer.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
drawer.BackgroundTransparency = 0.5
drawer.BorderSizePixel = 0
drawer.ClipsDescendants = true
drawer.Visible = false
drawer.Parent = main
corner(drawer, 12)
stroke(drawer, 1.35, 0.12, Color3.fromRGB(255, 0, 0))

local drawerGrad = gradient(drawer, ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
	ColorSequenceKeypoint.new(0.2, Color3.fromRGB(78, 0, 0)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
	ColorSequenceKeypoint.new(0.8, Color3.fromRGB(78, 0, 0)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 25)
drawerGrad.Transparency = NumberSequence.new({
	NumberSequenceKeypoint.new(0, 0.08),
	NumberSequenceKeypoint.new(1, 0.03)
})

local drawerScroll = Instance.new("ScrollingFrame")
drawerScroll.Size = UDim2.new(1, -10, 1, -10)
drawerScroll.Position = UDim2.new(0, 5, 0, 5)
drawerScroll.BackgroundTransparency = 1
drawerScroll.BorderSizePixel = 0
drawerScroll.ClipsDescendants = true
drawerScroll.ScrollBarThickness = 4
drawerScroll.ScrollBarImageColor3 = Color3.fromRGB(255, 0, 0)
drawerScroll.CanvasSize = UDim2.new(0, 0, 0, 0)
drawerScroll.Parent = drawer

local drawerLayout = Instance.new("UIListLayout")
drawerLayout.Padding = UDim.new(0, 4)
drawerLayout.FillDirection = Enum.FillDirection.Vertical
drawerLayout.SortOrder = Enum.SortOrder.LayoutOrder
drawerLayout.HorizontalAlignment = Enum.HorizontalAlignment.Center
drawerLayout.Parent = drawerScroll

local drawerPadding = Instance.new("UIPadding")
drawerPadding.PaddingTop = UDim.new(0, 4)
drawerPadding.PaddingBottom = UDim.new(0, 4)
drawerPadding.Parent = drawerScroll

local locations = {}
local isTeleporting = false
local currentConn = nil
local drawerOpen = false

local function updateDropdown()
	if #locations > 0 then
		local loc = locations[#locations]
		locationDropdown.Text = string.format("%.1f, %.1f, %.1f", loc.X, loc.Y, loc.Z)
	else
		locationDropdown.Text = ""
	end
	locationDropdown.PlaceholderText = (locationDropdown.Text == "" and "Địa điểm") or ""
end

local function refreshDrawer()
	for _, child in ipairs(drawerScroll:GetChildren()) do
		if child:IsA("TextButton") then child:Destroy() end
	end
	for _, loc in ipairs(locations) do
		local btn = Instance.new("TextButton")
		btn.Size = UDim2.new(0, 100, 0, 22)
		btn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
		btn.BackgroundTransparency = 1
		btn.BorderSizePixel = 0
		btn.Text = string.format("%.1f, %.1f, %.1f", loc.X, loc.Y, loc.Z)
		btn.Font = Enum.Font.GothamBlack
		btn.TextSize = 10
		btn.TextColor3 = Color3.fromRGB(255, 242, 242)
		btn.AutoButtonColor = false
		btn.Parent = drawerScroll
		corner(btn, 6)
		stroke(btn, 1, 0.1, Color3.fromRGB(255, 0, 0))
		btn.MouseButton1Click:Connect(function()
			locationDropdown.Text = btn.Text
			if drawerOpen then
				drawerOpen = false
				drawer.Size = UDim2.new(0, 0, 0, 0)
				drawer.Position = UDim2.new(1, 0, 0, 0)
				drawer.Visible = false
			end
		end)
	end
	drawerScroll.CanvasSize = UDim2.new(0, 0, 0, #locations * 28 + 10)
end

drawerBtn.MouseButton1Click:Connect(function()
	drawerOpen = not drawerOpen
	if drawerOpen then
		drawer.Visible = true
	else
		drawer.Visible = false
	end
end)

local function getPlayerPos()
	local char = LocalPlayer.Character
	if not char then return nil end
	local hrp = char:FindFirstChild("HumanoidRootPart")
	if not hrp then return nil end
	return hrp.Position
end

local function saveLocation()
	local pos = getPlayerPos()
	if not pos then return end
	for _, loc in ipairs(locations) do
		if (loc - pos).Magnitude < 0.5 then return end
	end
	table.insert(locations, pos)
	updateDropdown()
	refreshDrawer()
end

saveBtn.MouseButton1Click:Connect(saveLocation)

local function setCollision(enable)
	local char = LocalPlayer.Character
	if not char then return end
	for _, part in pairs(char:GetDescendants()) do
		if part:IsA("BasePart") then
			part.CanCollide = enable
		end
	end
end

local function stopTeleport()
	if currentConn then
		currentConn:Disconnect()
		currentConn = nil
	end
	local char = LocalPlayer.Character
	if char then
		local hrp = char:FindFirstChild("HumanoidRootPart")
		local humanoid = char:FindFirstChild("Humanoid")
		if hrp then
			if hrp:FindFirstChild("TempGyro") then hrp.TempGyro:Destroy() end
			if hrp:FindFirstChild("TempVelocity") then hrp.TempVelocity:Destroy() end
		end
		if humanoid then humanoid.PlatformStand = false end
		setCollision(true)
		local conn = char:GetAttribute("TPConnection")
		if conn then
			conn:Disconnect()
			char:SetAttribute("TPConnection", nil)
		end
	end
	isTeleporting = false
end

local function performTeleport()
	if isTeleporting then
		stopTeleport()
		return
	end

	local txt = locationDropdown.Text
	if txt == "" then return end
	local coords = {}
	for num in txt:gmatch("([%d%.]+)") do
		table.insert(coords, tonumber(num))
	end
	if #coords < 3 then return end
	local targetPos = Vector3.new(coords[1], coords[2], coords[3])
	local mode = modeBtn.Text
	local speed = tonumber(speedBox.Text) or 100
	if speed <= 0 then speed = 100 end

	local char = LocalPlayer.Character
	if not char then return end
	local hrp = char:FindFirstChild("HumanoidRootPart")
	local humanoid = char:FindFirstChild("Humanoid")
	if not hrp or not humanoid then return end

	local function stopMoving()
		if hrp:FindFirstChild("TempGyro") then hrp.TempGyro:Destroy() end
		if hrp:FindFirstChild("TempVelocity") then hrp.TempVelocity:Destroy() end
		humanoid.PlatformStand = false
		setCollision(true)
		local conn = char:GetAttribute("TPConnection")
		if conn then
			conn:Disconnect()
			char:SetAttribute("TPConnection", nil)
		end
		isTeleporting = false
	end

	local oldConn = char:GetAttribute("TPConnection")
	if oldConn then oldConn:Disconnect() end
	stopMoving()

	if mode == "Dịch Chuyển" then
		hrp.CFrame = CFrame.new(targetPos)
		return
	end

	setCollision(false)
	humanoid.PlatformStand = true

	local bg = Instance.new("BodyGyro")
	bg.P = 11e4
	bg.MaxTorque = Vector3.new(11e9, 11e9, 11e9)
	bg.CFrame = hrp.CFrame
	bg.Parent = hrp
	bg.Name = "TempGyro"

	local bv = Instance.new("BodyVelocity")
	bv.MaxForce = Vector3.new(11e9, 11e9, 11e9)
	bv.Velocity = Vector3.new(0, 0, 0)
	bv.Parent = hrp
	bv.Name = "TempVelocity"

	isTeleporting = true
	currentConn = RunService.Heartbeat:Connect(function(dt)
		if not char or not char.Parent then
			currentConn:Disconnect()
			stopMoving()
			return
		end
		local pos = hrp.Position
		local dist = (targetPos - pos).Magnitude
		if dist < 2 then
			currentConn:Disconnect()
			hrp.CFrame = CFrame.new(targetPos)
			stopMoving()
			return
		end
		local dir = (targetPos - pos).Unit
		local step = speed * dt
		if step > dist then step = dist end
		local newPos = pos + dir * step
		hrp.CFrame = CFrame.new(newPos)
		bg.CFrame = CFrame.lookAt(newPos, newPos + dir)
	end)

	char:SetAttribute("TPConnection", currentConn)
end

goBtn.MouseButton1Click:Connect(performTeleport)

LocalPlayer.CharacterAdded:Connect(function()
	if isTeleporting then
		stopTeleport()
	end
end)

task.spawn(function()
	while gui.Parent do
		task.wait(0.05)
		mainGrad.Rotation = (tick() * 12) % 360
		glow.ImageTransparency = 0.92 - (math.sin(tick() * 2) * 0.02)
	end
end)

refreshDrawer()
updateDropdown()

]]},
{Text = {vn = "Chống Fling", en = "Anti Fling"}, Script = [[
local Players = game.Players
local LocalPlayer = Players.LocalPlayer

_G.NoPlayerCollision = not _G.NoPlayerCollision
_G.NoPlayerCollisionFolder = _G.NoPlayerCollisionFolder

local function clearConstraints()
	if _G.NoPlayerCollisionFolder then
		_G.NoPlayerCollisionFolder:Destroy()
		_G.NoPlayerCollisionFolder = nil
	end
end

local function getParts(model)
	local parts = {}

	if not model then
		return parts
	end

	for _, v in ipairs(model:GetDescendants()) do
		if v:IsA("BasePart") then
			table.insert(parts, v)
		end
	end

	return parts
end

local function apply()
	clearConstraints()

	local myChar = LocalPlayer.Character
	if not myChar then
		return
	end

	local folder = Instance.new("Folder")
	folder.Name = "NoPlayerCollisionFolder"
	folder.Parent = myChar

	_G.NoPlayerCollisionFolder = folder

	local myParts = getParts(myChar)

	for _, plr in ipairs(Players:GetPlayers()) do
		if plr ~= LocalPlayer and plr.Character then
			local otherParts = getParts(plr.Character)

			for _, myPart in ipairs(myParts) do
				for _, otherPart in ipairs(otherParts) do
					local nc = Instance.new("NoCollisionConstraint")
					nc.Part0 = myPart
					nc.Part1 = otherPart
					nc.Parent = folder
				end
			end
		end
	end
end

if _G.NoPlayerCollision then

	apply()

	if _G.NoPlayerCollision_LocalConn then
		_G.NoPlayerCollision_LocalConn:Disconnect()
	end

	_G.NoPlayerCollision_LocalConn =
		LocalPlayer.CharacterAdded:Connect(function()
			task.wait(1)
			if _G.NoPlayerCollision then
				apply()
			end
		end)

	if _G.NoPlayerCollision_PlayerConn then
		_G.NoPlayerCollision_PlayerConn:Disconnect()
	end

	_G.NoPlayerCollision_PlayerConn =
		Players.PlayerAdded:Connect(function(plr)
			plr.CharacterAdded:Connect(function()
				task.wait(1)
				if _G.NoPlayerCollision then
					apply()
				end
			end)
		end)

else

	clearConstraints()

	if _G.NoPlayerCollision_LocalConn then
		_G.NoPlayerCollision_LocalConn:Disconnect()
		_G.NoPlayerCollision_LocalConn = nil
	end

	if _G.NoPlayerCollision_PlayerConn then
		_G.NoPlayerCollision_PlayerConn:Disconnect()
		_G.NoPlayerCollision_PlayerConn = nil
	end
end
]]},
{Text = {vn = "Trạng Thái Humanoid", en = "Humanoid State"}, Script = [[

local Players = game.Players
local RunService = game.RunService
local player = Players.LocalPlayer

local old = game.CoreGui:FindFirstChild("HumanoidInfoGui")
if old then
	old:Destroy()
	return
end

local gui = Instance.new("ScreenGui")
gui.Name = "HumanoidInfoGui"
gui.ResetOnSpawn = false
gui.Parent = game.CoreGui

local main = Instance.new("Frame")
main.Size = UDim2.new(0, 230, 0, 350)
main.Position = UDim2.new(0, 510, 0.5, -210)
main.BackgroundColor3 = Color3.fromRGB(20, 20, 20)
main.BackgroundTransparency = 0.3
main.BorderSizePixel = 0
main.Parent = gui

Instance.new("UICorner", main).CornerRadius = UDim.new(0, 10)

local label = Instance.new("TextLabel")
label.Size = UDim2.new(0, 350, 0, 350)
label.Position = UDim2.new(0, 0, 0, 0)
label.BackgroundTransparency = 1
label.TextColor3 = Color3.fromRGB(255, 255, 255)
label.Font = Enum.Font.Code
label.TextSize = 11.8
label.TextXAlignment = Enum.TextXAlignment.Left
label.TextYAlignment = Enum.TextYAlignment.Top
label.RichText = false
label.TextWrapped = false
label.Text = "Đang tải..."
label.Parent = main

local pad = Instance.new("UIPadding")
pad.PaddingLeft = UDim.new(0, 2)
pad.PaddingTop = UDim.new(0, 2)
pad.Parent = label

local function v(x)
	if typeof(x) == "Vector3" then
		return string.format("(%.2f, %.2f, %.2f)", x.X, x.Y, x.Z)
	elseif typeof(x) == "Vector2" then
		return string.format("(%.2f, %.2f)", x.X, x.Y)
	elseif typeof(x) == "CFrame" then
		local p = x.Position
		return string.format("CFrame(%.2f, %.2f, %.2f)", p.X, p.Y, p.Z)
	elseif typeof(x) == "EnumItem" then
		return x.Name
	else
		return tostring(x)
	end
end

local function getSafe(obj, prop)
	local ok, val = pcall(function()
		return obj[prop]
	end)
	if ok then
		return val
	end
	return "N/A"
end

local conn
local charConn

local function setup(char)
	local hum = char:WaitForChild("Humanoid")

	if conn then
		conn:Disconnect()
		conn = nil
	end

	conn = RunService.RenderStepped:Connect(function()
		if not hum.Parent then
			return
		end

		local lines = {
			"ClassName = " .. v(getSafe(hum, "ClassName")),
			"Name = " .. v(getSafe(hum, "Name")),
			"RigType = " .. v(getSafe(hum, "RigType")),
			"Health = " .. v(getSafe(hum, "Health")),
			"MaxHealth = " .. v(getSafe(hum, "MaxHealth")),
			"WalkSpeed = " .. v(getSafe(hum, "WalkSpeed")),
			"JumpPower = " .. v(getSafe(hum, "JumpPower")),
			"JumpHeight = " .. v(getSafe(hum, "JumpHeight")),
			"UseJumpPower = " .. v(getSafe(hum, "UseJumpPower")),
			"Jump = " .. v(getSafe(hum, "Jump")),
			"Sit = " .. v(getSafe(hum, "Sit")),
			"AutoRotate = " .. v(getSafe(hum, "AutoRotate")),
			"AutoJumpEnabled = " .. v(getSafe(hum, "AutoJumpEnabled")),
			"HealthDisplayType = " .. v(getSafe(hum, "HealthDisplayType")),
			"DisplayDistanceType = " .. v(getSafe(hum, "DisplayDistanceType")),
			"FloorMaterial = " .. v(getSafe(hum, "FloorMaterial")),
			"MoveDirection = " .. v(getSafe(hum, "MoveDirection")),
			"MoveToPoint = " .. v(getSafe(hum, "MoveToPoint")),
			"RootPart = " .. v((hum.RootPart and hum.RootPart.Name) or "N/A"),
			"TargetPoint = " .. v(getSafe(hum, "TargetPoint")),
			"PlatformStand = " .. v(getSafe(hum, "PlatformStand")),
			"CameraOffset = " .. v(getSafe(hum, "CameraOffset")),
			"FloorMaterial = " .. v(getSafe(hum, "FloorMaterial")),
			"State = " .. v(getSafe(hum, "GetState") and hum:GetState() or "N/A"),
			"CurrentState = " .. v(getSafe(hum, "GetState") and hum:GetState().Name or "N/A"),
			"StateEnabled Running = " .. v(pcall(function() return hum:GetStateEnabled(Enum.HumanoidStateType.Running) end)),
			"StateEnabled Jumping = " .. v(pcall(function() return hum:GetStateEnabled(Enum.HumanoidStateType.Jumping) end)),
			"StateEnabled Freefall = " .. v(pcall(function() return hum:GetStateEnabled(Enum.HumanoidStateType.Freefall) end)),
			"StateEnabled Swimming = " .. v(pcall(function() return hum:GetStateEnabled(Enum.HumanoidStateType.Swimming) end)),
			"StateEnabled Seated = " .. v(pcall(function() return hum:GetStateEnabled(Enum.HumanoidStateType.Seated) end)),
			"StateEnabled Climbing = " .. v(pcall(function() return hum:GetStateEnabled(Enum.HumanoidStateType.Climbing) end)),
		}

		local okState, stateName = pcall(function()
			return hum:GetState().Name
		end)
		if okState then
			lines[23] = "State = " .. stateName
		else
			lines[23] = "State = N/A"
		end

		local okRunning, running = pcall(function()
			return hum:GetStateEnabled(Enum.HumanoidStateType.Running)
		end)
		lines[24] = "StateEnabled Running = " .. tostring(okRunning and running or "N/A")

		local okJumping, jumping = pcall(function()
			return hum:GetStateEnabled(Enum.HumanoidStateType.Jumping)
		end)
		lines[25] = "StateEnabled Jumping = " .. tostring(okJumping and jumping or "N/A")

		local okFreefall, freefall = pcall(function()
			return hum:GetStateEnabled(Enum.HumanoidStateType.Freefall)
		end)
		lines[26] = "StateEnabled Freefall = " .. tostring(okFreefall and freefall or "N/A")

		local okSwimming, swimming = pcall(function()
			return hum:GetStateEnabled(Enum.HumanoidStateType.Swimming)
		end)
		lines[27] = "StateEnabled Swimming = " .. tostring(okSwimming and swimming or "N/A")

		local okSeated, seated = pcall(function()
			return hum:GetStateEnabled(Enum.HumanoidStateType.Seated)
		end)
		lines[28] = "StateEnabled Seated = " .. tostring(okSeated and seated or "N/A")

		local okClimbing, climbing = pcall(function()
			return hum:GetStateEnabled(Enum.HumanoidStateType.Climbing)
		end)
		lines[29] = "StateEnabled Climbing = " .. tostring(okClimbing and climbing or "N/A")

		label.Text = table.concat(lines, "\n")
	end)
end

if player.Character then
	setup(player.Character)
end

charConn = player.CharacterAdded:Connect(setup)

]]},
}},

{Text = {vn = "Bầu Trời", en = "Sky"}, Scripts = {

{Text = {vn = "Tím(Client)", en = "Purple(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Workspace=game:GetService("Workspace");if not getgenv()._KitamoraShaderBackup then getgenv()._KitamoraShaderName="Kitamora Shader";getgenv()._KitamoraShaderCurrent=nil;getgenv()._KitamoraShaderBackup={};local b=getgenv()._KitamoraShaderBackup;b.ClockTime=Lighting.ClockTime;b.Brightness=Lighting.Brightness;b.Exposure=Lighting.ExposureCompensation;b.GlobalShadows=Lighting.GlobalShadows;b.Ambient=Lighting.Ambient;b.OutdoorAmbient=Lighting.OutdoorAmbient;b.EnvironmentDiffuseScale=Lighting.EnvironmentDiffuseScale;b.EnvironmentSpecularScale=Lighting.EnvironmentSpecularScale;b.LightingChildren={};for _,c in ipairs(Lighting:GetChildren()) do if c:IsA("Atmosphere") or c:IsA("BloomEffect") or c:IsA("SunRaysEffect") or c:IsA("ColorCorrectionEffect") or c:IsA("DepthOfFieldEffect") or c:IsA("Sky") or c:IsA("BlurEffect") then pcall(function()table.insert(b.LightingChildren,c:Clone())end) end end end;local function restoreLighting()local modified=getgenv()._KitaShaderModifiedParts or {};for inst,info in pairs(modified) do if inst and inst.Parent then pcall(function()for prop,val in pairs(info) do inst[prop]=val end end) end end;getgenv()._KitaShaderModifiedParts=nil;for _,v in ipairs(Lighting:GetChildren()) do if tostring(v.Name):match("^KitamoraShader") then pcall(function()v:Destroy()end) end end;local b=getgenv()._KitamoraShaderBackup or {};for _,orig in ipairs(b.LightingChildren or {}) do pcall(function()if not Lighting:FindFirstChild(orig.Name) then orig:Clone().Parent=Lighting end end) end;Lighting.ClockTime=b.ClockTime or 12;Lighting.Brightness=b.Brightness or 2;Lighting.ExposureCompensation=b.Exposure or 0;Lighting.GlobalShadows=b.GlobalShadows;Lighting.Ambient=b.Ambient or Color3.fromRGB(127,127,127);Lighting.OutdoorAmbient=b.OutdoorAmbient or Color3.fromRGB(127,127,127);Lighting.EnvironmentDiffuseScale=b.EnvironmentDiffuseScale or Lighting.EnvironmentDiffuseScale;Lighting.EnvironmentSpecularScale=b.EnvironmentSpecularScale or Lighting.EnvironmentSpecularScale;getgenv()._KitamoraShaderCurrent=nil end;local function tintColor(c,percent)local r=c.R*(1-percent)+0.7*percent;local g=c.G*(1-percent)+0.3*percent;local b=c.B*(1-percent)+1*percent;return Color3.new(math.clamp(r,0,1),math.clamp(g,0,1),math.clamp(b,0,1)) end;local function applyPurple()if getgenv()._KitamoraShaderCurrent=="purple" then restoreLighting();return end;if getgenv()._KitamoraShaderCurrent then restoreLighting() end;local tag="KitamoraShader_purple";local atmo=Instance.new("Atmosphere");atmo.Name=tag.."_Atmosphere";atmo.Density=0.38;atmo.Offset=0.06;atmo.Color=Color3.fromRGB(210,150,255);atmo.Decay=Color3.fromRGB(140,70,200);atmo.Glare=0.35;atmo.Haze=0.8;atmo.Parent=Lighting;local bloom=Instance.new("BloomEffect");bloom.Name=tag.."_Bloom";bloom.Intensity=1.9;bloom.Size=27;bloom.Threshold=0.57;bloom.Parent=Lighting;local sun=Instance.new("SunRaysEffect");sun.Name=tag.."_SunRays";sun.Intensity=0.55;sun.Spread=0.22;sun.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name=tag.."_Color";cc.TintColor=Color3.fromRGB(235,200,255);cc.Contrast=0.07;cc.Saturation=0.1;cc.Parent=Lighting;Lighting.ClockTime=15;Lighting.Brightness=math.clamp((Lighting.Brightness or 2)+0.6,0,10);Lighting.ExposureCompensation=(Lighting.ExposureCompensation or 0)-0.05;Lighting.Ambient=Color3.fromRGB(170,140,200);Lighting.OutdoorAmbient=Color3.fromRGB(200,160,240);local reflectAdd=0.25;local modified={};for _,obj in ipairs(Workspace:GetDescendants()) do if obj:IsA("BasePart") or obj:IsA("MeshPart") or obj:IsA("UnionOperation") then local ok1,origColor=pcall(function()return obj.Color end);local ok2,origRefl=pcall(function()return obj.Reflectance end);if ok1 then modified[obj]={Color=origColor,Reflectance=origRefl or 0};pcall(function()obj.Color=tintColor(origColor,0.3);obj.Reflectance=math.clamp((origRefl or 0)+reflectAdd,0,1) end) end elseif obj:IsA("Decal") or obj:IsA("Texture") then local ok,origColor=pcall(function()return obj.Color3 end);if ok then modified[obj]={Color3=origColor};pcall(function()obj.Color3=tintColor(origColor,0.3) end) end elseif obj:IsA("SurfaceAppearance") then local ok,origColor=pcall(function()return obj.Color3 or Color3.new(1,1,1) end);if ok then modified[obj]={Color3=origColor};pcall(function()obj.Color3=tintColor(origColor,0.3) end) end elseif obj:IsA("ParticleEmitter") or obj:IsA("Trail") or obj:IsA("Beam") then local ok,orig=pcall(function()return obj.Color end);if ok and typeof(orig)=="ColorSequence" then modified[obj]={Color=orig};local keypoints={};for _,k in ipairs(orig.Keypoints) do table.insert(keypoints,ColorSequenceKeypoint.new(k.Time,tintColor(k.Value,0.3))) end;pcall(function()obj.Color=ColorSequence.new(keypoints) end) end elseif obj:IsA("Fire") or obj:IsA("Smoke") or obj:IsA("Sparkles") then local ok,origColor=pcall(function()return obj.Color end);if ok then modified[obj]={Color=origColor};pcall(function()obj.Color=tintColor(origColor,0.3) end) end end end;getgenv()._KitaShaderModifiedParts=modified;getgenv()._KitamoraShaderCurrent="purple" end;applyPurple()


]]},

{Text = {vn = "Hồng(Client)", en = "Pink(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Workspace=game:GetService("Workspace");if not getgenv()._KitamoraShaderBackup then getgenv()._KitamoraShaderName="Kitamora Shader";getgenv()._KitamoraShaderCurrent=nil;getgenv()._KitamoraShaderBackup={};local b=getgenv()._KitamoraShaderBackup;b.ClockTime=Lighting.ClockTime;b.Brightness=Lighting.Brightness;b.Exposure=Lighting.ExposureCompensation;b.GlobalShadows=Lighting.GlobalShadows;b.Ambient=Lighting.Ambient;b.OutdoorAmbient=Lighting.OutdoorAmbient;b.EnvironmentDiffuseScale=Lighting.EnvironmentDiffuseScale;b.EnvironmentSpecularScale=Lighting.EnvironmentSpecularScale;b.LightingChildren={};for _,c in ipairs(Lighting:GetChildren()) do if c:IsA("Atmosphere") or c:IsA("BloomEffect") or c:IsA("SunRaysEffect") or c:IsA("ColorCorrectionEffect") or c:IsA("DepthOfFieldEffect") or c:IsA("Sky") or c:IsA("BlurEffect") then pcall(function()table.insert(b.LightingChildren,c:Clone())end) end end end;local function restoreLighting()local modified=getgenv()._KitaShaderModifiedParts or {};for inst,info in pairs(modified) do if inst and inst.Parent then pcall(function()for prop,val in pairs(info) do inst[prop]=val end end) end end;getgenv()._KitaShaderModifiedParts=nil;for _,v in ipairs(Lighting:GetChildren()) do if tostring(v.Name):match("^KitamoraShader") then pcall(function()v:Destroy()end) end end;local b=getgenv()._KitamoraShaderBackup or {};for _,orig in ipairs(b.LightingChildren or {}) do pcall(function()if not Lighting:FindFirstChild(orig.Name) then orig:Clone().Parent=Lighting end end) end;Lighting.ClockTime=b.ClockTime or 12;Lighting.Brightness=b.Brightness or 2;Lighting.ExposureCompensation=b.Exposure or 0;Lighting.GlobalShadows=b.GlobalShadows;Lighting.Ambient=b.Ambient or Color3.fromRGB(127,127,127);Lighting.OutdoorAmbient=b.OutdoorAmbient or Color3.fromRGB(127,127,127);Lighting.EnvironmentDiffuseScale=b.EnvironmentDiffuseScale or Lighting.EnvironmentDiffuseScale;Lighting.EnvironmentSpecularScale=b.EnvironmentSpecularScale or Lighting.EnvironmentSpecularScale;getgenv()._KitamoraShaderCurrent=nil end;local function tintColor(c,percent)local r=c.R*(1-percent)+1*percent;local g=c.G*(1-percent)+0.4*percent;local b=c.B*(1-percent)+0.7*percent;return Color3.new(math.clamp(r,0,1),math.clamp(g,0,1),math.clamp(b,0,1)) end;local function applyPink()if getgenv()._KitamoraShaderCurrent=="pink" then restoreLighting();return end;if getgenv()._KitamoraShaderCurrent then restoreLighting() end;local tag="KitamoraShader_pink";local atmo=Instance.new("Atmosphere");atmo.Name=tag.."_Atmosphere";atmo.Density=0.38;atmo.Offset=0.07;atmo.Color=Color3.fromRGB(255,180,220);atmo.Decay=Color3.fromRGB(255,140,180);atmo.Glare=0.25;atmo.Haze=0.8;atmo.Parent=Lighting;local bloom=Instance.new("BloomEffect");bloom.Name=tag.."_Bloom";bloom.Intensity=1.8;bloom.Size=26;bloom.Threshold=0.58;bloom.Parent=Lighting;local sun=Instance.new("SunRaysEffect");sun.Name=tag.."_SunRays";sun.Intensity=0.55;sun.Spread=0.2;sun.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name=tag.."_Color";cc.TintColor=Color3.fromRGB(255,200,230);cc.Contrast=0.05;cc.Saturation=0.08;cc.Parent=Lighting;Lighting.ClockTime=16.5;Lighting.Brightness=math.clamp((Lighting.Brightness or 2)+0.6,0,10);Lighting.ExposureCompensation=(Lighting.ExposureCompensation or 0)-0.05;Lighting.Ambient=Color3.fromRGB(200,150,180);Lighting.OutdoorAmbient=Color3.fromRGB(255,190,210);local reflectAdd=0.25;local modified={};for _,obj in ipairs(Workspace:GetDescendants()) do if obj:IsA("BasePart") or obj:IsA("MeshPart") or obj:IsA("UnionOperation") then local ok1,origColor=pcall(function()return obj.Color end);local ok2,origRefl=pcall(function()return obj.Reflectance end);if ok1 then modified[obj]={Color=origColor,Reflectance=origRefl or 0};pcall(function()obj.Color=tintColor(origColor,0.3);obj.Reflectance=math.clamp((origRefl or 0)+reflectAdd,0,1) end) end elseif obj:IsA("Decal") or obj:IsA("Texture") then local ok,origColor=pcall(function()return obj.Color3 end);if ok then modified[obj]={Color3=origColor};pcall(function()obj.Color3=tintColor(origColor,0.3) end) end elseif obj:IsA("SurfaceAppearance") then local ok,origColor=pcall(function()return obj.Color3 or Color3.new(1,1,1) end);if ok then modified[obj]={Color3=origColor};pcall(function()obj.Color3=tintColor(origColor,0.3) end) end elseif obj:IsA("ParticleEmitter") or obj:IsA("Trail") or obj:IsA("Beam") then local ok,orig=pcall(function()return obj.Color end);if ok and typeof(orig)=="ColorSequence" then modified[obj]={Color=orig};local keypoints={};for _,k in ipairs(orig.Keypoints) do table.insert(keypoints,ColorSequenceKeypoint.new(k.Time,tintColor(k.Value,0.3))) end;pcall(function()obj.Color=ColorSequence.new(keypoints) end) end elseif obj:IsA("Fire") or obj:IsA("Smoke") or obj:IsA("Sparkles") then local ok,origColor=pcall(function()return obj.Color end);if ok then modified[obj]={Color=origColor};pcall(function()obj.Color=tintColor(origColor,0.3) end) end end end;getgenv()._KitaShaderModifiedParts=modified;getgenv()._KitamoraShaderCurrent="pink" end;applyPink()


]]},

{Text = {vn = "Đỏ(Client)", en = "Red(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Workspace=game:GetService("Workspace");if not getgenv()._KitamoraShaderBackup then getgenv()._KitamoraShaderName="Kitamora Shader";getgenv()._KitamoraShaderCurrent=nil;getgenv()._KitamoraShaderBackup={};local b=getgenv()._KitamoraShaderBackup;b.ClockTime=Lighting.ClockTime;b.Brightness=Lighting.Brightness;b.Exposure=Lighting.ExposureCompensation;b.GlobalShadows=Lighting.GlobalShadows;b.Ambient=Lighting.Ambient;b.OutdoorAmbient=Lighting.OutdoorAmbient;b.EnvironmentDiffuseScale=Lighting.EnvironmentDiffuseScale;b.EnvironmentSpecularScale=Lighting.EnvironmentSpecularScale;b.LightingChildren={};for _,c in ipairs(Lighting:GetChildren()) do if c:IsA("Atmosphere") or c:IsA("BloomEffect") or c:IsA("SunRaysEffect") or c:IsA("ColorCorrectionEffect") or c:IsA("DepthOfFieldEffect") or c:IsA("Sky") or c:IsA("BlurEffect") then pcall(function()table.insert(b.LightingChildren,c:Clone())end) end end end;local function restoreLighting()local modified=getgenv()._KitaShaderModifiedParts or {};for inst,info in pairs(modified) do if inst and inst.Parent then pcall(function()for prop,val in pairs(info) do inst[prop]=val end end) end end;getgenv()._KitaShaderModifiedParts=nil;for _,v in ipairs(Lighting:GetChildren()) do if tostring(v.Name):match("^KitamoraShader") then pcall(function()v:Destroy()end) end end;local b=getgenv()._KitamoraShaderBackup or {};for _,orig in ipairs(b.LightingChildren or {}) do pcall(function()if not Lighting:FindFirstChild(orig.Name) then orig:Clone().Parent=Lighting end end) end;Lighting.ClockTime=b.ClockTime or 12;Lighting.Brightness=b.Brightness or 2;Lighting.ExposureCompensation=b.Exposure or 0;Lighting.GlobalShadows=b.GlobalShadows;Lighting.Ambient=b.Ambient or Color3.fromRGB(127,127,127);Lighting.OutdoorAmbient=b.OutdoorAmbient or Color3.fromRGB(127,127,127);Lighting.EnvironmentDiffuseScale=b.EnvironmentDiffuseScale or Lighting.EnvironmentDiffuseScale;Lighting.EnvironmentSpecularScale=b.EnvironmentSpecularScale or Lighting.EnvironmentSpecularScale;getgenv()._KitamoraShaderCurrent=nil end;local function tintColor(c,percent)local r=c.R*(1-percent)+1*percent;local g=c.G*(1-percent)+0.2*percent;local b=c.B*(1-percent)+0.2*percent;return Color3.new(math.clamp(r,0,1),math.clamp(g,0,1),math.clamp(b,0,1)) end;local function applyRed()if getgenv()._KitamoraShaderCurrent=="red" then restoreLighting();return end;if getgenv()._KitamoraShaderCurrent then restoreLighting() end;local tag="KitamoraShader_red";local atmo=Instance.new("Atmosphere");atmo.Name=tag.."_Atmosphere";atmo.Density=0.4;atmo.Offset=0.07;atmo.Color=Color3.fromRGB(255,100,100);atmo.Decay=Color3.fromRGB(255,70,70);atmo.Glare=0.22;atmo.Haze=0.9;atmo.Parent=Lighting;local bloom=Instance.new("BloomEffect");bloom.Name=tag.."_Bloom";bloom.Intensity=1.8;bloom.Size=24;bloom.Threshold=0.58;bloom.Parent=Lighting;local sun=Instance.new("SunRaysEffect");sun.Name=tag.."_SunRays";sun.Intensity=0.6;sun.Spread=0.2;sun.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name=tag.."_Color";cc.TintColor=Color3.fromRGB(255,180,180);cc.Contrast=0.07;cc.Saturation=0.04;cc.Parent=Lighting;Lighting.ClockTime=16.5;Lighting.Brightness=math.clamp((Lighting.Brightness or 2)+0.8,0,10);Lighting.ExposureCompensation=(Lighting.ExposureCompensation or 0)-0.05;Lighting.Ambient=Color3.fromRGB(180,80,80);Lighting.OutdoorAmbient=Color3.fromRGB(120,50,50);local reflectAdd=0.25;local modified={};for _,obj in ipairs(Workspace:GetDescendants()) do if obj:IsA("BasePart") or obj:IsA("MeshPart") or obj:IsA("UnionOperation") then local ok1,origColor=pcall(function()return obj.Color end);local ok2,origRefl=pcall(function()return obj.Reflectance end);if ok1 then modified[obj]={Color=origColor,Reflectance=origRefl or 0};pcall(function()obj.Color=tintColor(origColor,0.3);obj.Reflectance=math.clamp((origRefl or 0)+reflectAdd,0,1) end) end elseif obj:IsA("Decal") or obj:IsA("Texture") then local ok,origColor=pcall(function()return obj.Color3 end);if ok then modified[obj]={Color3=origColor};pcall(function()obj.Color3=tintColor(origColor,0.3) end) end elseif obj:IsA("SurfaceAppearance") then local ok,origColor=pcall(function()return obj.Color3 or Color3.new(1,1,1) end);if ok then modified[obj]={Color3=origColor};pcall(function()obj.Color3=tintColor(origColor,0.3) end) end elseif obj:IsA("ParticleEmitter") or obj:IsA("Trail") or obj:IsA("Beam") then local ok,orig=pcall(function()return obj.Color end);if ok and typeof(orig)=="ColorSequence" then modified[obj]={Color=orig};local keypoints={};for _,k in ipairs(orig.Keypoints) do table.insert(keypoints,ColorSequenceKeypoint.new(k.Time,tintColor(k.Value,0.3))) end;pcall(function()obj.Color=ColorSequence.new(keypoints) end) end elseif obj:IsA("Fire") or obj:IsA("Smoke") or obj:IsA("Sparkles") then local ok,origColor=pcall(function()return obj.Color end);if ok then modified[obj]={Color=origColor};pcall(function()obj.Color=tintColor(origColor,0.3) end) end end end;getgenv()._KitaShaderModifiedParts=modified;getgenv()._KitamoraShaderCurrent="red" end;applyRed()

]]},

{Text = {vn = "Cam(Client)", en = "Orange(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Workspace=game:GetService("Workspace");if not getgenv()._KitamoraShaderBackup then getgenv()._KitamoraShaderName="Kitamora Shader";getgenv()._KitamoraShaderCurrent=nil;getgenv()._KitamoraShaderBackup={};local b=getgenv()._KitamoraShaderBackup;b.ClockTime=Lighting.ClockTime;b.Brightness=Lighting.Brightness;b.Exposure=Lighting.ExposureCompensation;b.GlobalShadows=Lighting.GlobalShadows;b.Ambient=Lighting.Ambient;b.OutdoorAmbient=Lighting.OutdoorAmbient;b.EnvironmentDiffuseScale=Lighting.EnvironmentDiffuseScale;b.EnvironmentSpecularScale=Lighting.EnvironmentSpecularScale;b.LightingChildren={};for _,c in ipairs(Lighting:GetChildren()) do if c:IsA("Atmosphere") or c:IsA("BloomEffect") or c:IsA("SunRaysEffect") or c:IsA("ColorCorrectionEffect") or c:IsA("DepthOfFieldEffect") or c:IsA("Sky") or c:IsA("BlurEffect") then pcall(function()table.insert(b.LightingChildren,c:Clone())end) end end end;local function restoreLighting()local modified=getgenv()._KitaShaderModifiedParts or {};for inst,info in pairs(modified) do if inst and inst.Parent then pcall(function()for prop,val in pairs(info) do inst[prop]=val end end) end end;getgenv()._KitaShaderModifiedParts=nil;for _,v in ipairs(Lighting:GetChildren()) do if tostring(v.Name):match("^KitamoraShader") then pcall(function()v:Destroy()end) end end;local b=getgenv()._KitamoraShaderBackup or {};for _,orig in ipairs(b.LightingChildren or {}) do pcall(function()if not Lighting:FindFirstChild(orig.Name) then orig:Clone().Parent=Lighting end end) end;Lighting.ClockTime=b.ClockTime or 12;Lighting.Brightness=b.Brightness or 2;Lighting.ExposureCompensation=b.Exposure or 0;Lighting.GlobalShadows=b.GlobalShadows;Lighting.Ambient=b.Ambient or Color3.fromRGB(127,127,127);Lighting.OutdoorAmbient=b.OutdoorAmbient or Color3.fromRGB(127,127,127);Lighting.EnvironmentDiffuseScale=b.EnvironmentDiffuseScale or Lighting.EnvironmentDiffuseScale;Lighting.EnvironmentSpecularScale=b.EnvironmentSpecularScale or Lighting.EnvironmentSpecularScale;getgenv()._KitamoraShaderCurrent=nil end;local function tintColor(c,percent)local r=c.R*(1-percent)+1*percent*0.9;local g=c.G*(1-percent)+0.5*percent;local b=c.B*(1-percent)+0.1*percent;return Color3.new(math.clamp(r,0,1),math.clamp(g,0,1),math.clamp(b,0,1)) end;local function applyOrange()if getgenv()._KitamoraShaderCurrent=="orange" then restoreLighting();return end;if getgenv()._KitamoraShaderCurrent then restoreLighting() end;local tag="KitamoraShader_orange";local atmo=Instance.new("Atmosphere");atmo.Name=tag.."_Atmosphere";atmo.Density=0.4;atmo.Offset=0.08;atmo.Color=Color3.fromRGB(255,180,100);atmo.Decay=Color3.fromRGB(255,130,80);atmo.Glare=0.25;atmo.Haze=1.0;atmo.Parent=Lighting;local bloom=Instance.new("BloomEffect");bloom.Name=tag.."_Bloom";bloom.Intensity=2.4;bloom.Size=28;bloom.Threshold=0.55;bloom.Parent=Lighting;local sun=Instance.new("SunRaysEffect");sun.Name=tag.."_SunRays";sun.Intensity=0.8;sun.Spread=0.25;sun.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name=tag.."_Color";cc.TintColor=Color3.fromRGB(255,200,150);cc.Contrast=0.08;cc.Saturation=0.05;cc.Parent=Lighting;Lighting.ClockTime=17;Lighting.Brightness=math.clamp((Lighting.Brightness or 2)+1.2,0,10);Lighting.ExposureCompensation=(Lighting.ExposureCompensation or 0)-0.1;Lighting.Ambient=Color3.fromRGB(180,120,80);Lighting.OutdoorAmbient=Color3.fromRGB(255,190,120);local reflectAdd=0.25;local modified={};for _,obj in ipairs(Workspace:GetDescendants()) do if obj:IsA("BasePart") or obj:IsA("MeshPart") or obj:IsA("UnionOperation") then local ok1,origColor=pcall(function()return obj.Color end);local ok2,origRefl=pcall(function()return obj.Reflectance end);if ok1 then modified[obj]={Color=origColor,Reflectance=origRefl or 0};pcall(function()obj.Color=tintColor(origColor,0.3);obj.Reflectance=math.clamp((origRefl or 0)+reflectAdd,0,1) end) end elseif obj:IsA("Decal") or obj:IsA("Texture") then local ok,origColor=pcall(function()return obj.Color3 end);if ok then modified[obj]={Color3=origColor};pcall(function()obj.Color3=tintColor(origColor,0.3) end) end elseif obj:IsA("SurfaceAppearance") then local ok,origColor=pcall(function()return obj.Color3 or Color3.new(1,1,1) end);if ok then modified[obj]={Color3=origColor};pcall(function()obj.Color3=tintColor(origColor,0.3) end) end elseif obj:IsA("ParticleEmitter") or obj:IsA("Trail") or obj:IsA("Beam") then local ok,orig=pcall(function()return obj.Color end);if ok and typeof(orig)=="ColorSequence" then modified[obj]={Color=orig};local keypoints={};for _,k in ipairs(orig.Keypoints) do table.insert(keypoints,ColorSequenceKeypoint.new(k.Time,tintColor(k.Value,0.3))) end;pcall(function()obj.Color=ColorSequence.new(keypoints) end) end elseif obj:IsA("Fire") or obj:IsA("Smoke") or obj:IsA("Sparkles") then local ok,origColor=pcall(function()return obj.Color end);if ok then modified[obj]={Color=origColor};pcall(function()obj.Color=tintColor(origColor,0.3) end) end end end;getgenv()._KitaShaderModifiedParts=modified;getgenv()._KitamoraShaderCurrent="orange" end;applyOrange()

]]},

{Text = {vn = "Trắng(Client)", en = "White(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Workspace=game:GetService("Workspace");if not getgenv()._KitamoraShaderBackup then getgenv()._KitamoraShaderName="Kitamora Shader";getgenv()._KitamoraShaderCurrent=nil;getgenv()._KitamoraShaderBackup={};local b=getgenv()._KitamoraShaderBackup;b.ClockTime=Lighting.ClockTime;b.Brightness=Lighting.Brightness;b.Exposure=Lighting.ExposureCompensation;b.GlobalShadows=Lighting.GlobalShadows;b.Ambient=Lighting.Ambient;b.OutdoorAmbient=Lighting.OutdoorAmbient;b.EnvironmentDiffuseScale=Lighting.EnvironmentDiffuseScale;b.EnvironmentSpecularScale=Lighting.EnvironmentSpecularScale;b.LightingChildren={};for _,c in ipairs(Lighting:GetChildren()) do if c:IsA("Atmosphere") or c:IsA("BloomEffect") or c:IsA("SunRaysEffect") or c:IsA("ColorCorrectionEffect") or c:IsA("DepthOfFieldEffect") or c:IsA("Sky") or c:IsA("BlurEffect") then pcall(function()table.insert(b.LightingChildren,c:Clone())end) end end end;local function restoreLighting()local modified=getgenv()._KitaShaderModifiedParts or {};for inst,info in pairs(modified) do if inst and inst.Parent then pcall(function()for prop,val in pairs(info) do inst[prop]=val end end) end end;getgenv()._KitaShaderModifiedParts=nil;for _,v in ipairs(Lighting:GetChildren()) do if tostring(v.Name):match("^KitamoraShader") then pcall(function()v:Destroy()end) end end;local b=getgenv()._KitamoraShaderBackup or {};for _,orig in ipairs(b.LightingChildren or {}) do pcall(function()if not Lighting:FindFirstChild(orig.Name) then orig:Clone().Parent=Lighting end end) end;Lighting.ClockTime=b.ClockTime or 12;Lighting.Brightness=b.Brightness or 2;Lighting.ExposureCompensation=b.Exposure or 0;Lighting.GlobalShadows=b.GlobalShadows;Lighting.Ambient=b.Ambient or Color3.fromRGB(127,127,127);Lighting.OutdoorAmbient=b.OutdoorAmbient or Color3.fromRGB(127,127,127);Lighting.EnvironmentDiffuseScale=b.EnvironmentDiffuseScale or Lighting.EnvironmentDiffuseScale;Lighting.EnvironmentSpecularScale=b.EnvironmentSpecularScale or Lighting.EnvironmentSpecularScale;getgenv()._KitamoraShaderCurrent=nil end;local function tintColor(c,p)local r=c.R*(1-p)+1*p;local g=c.G*(1-p)+1*p;local b=c.B*(1-p)+1*p;return Color3.new(math.clamp(r,0,1),math.clamp(g,0,1),math.clamp(b,0,1)) end;local function applyWhite()if getgenv()._KitamoraShaderCurrent=="white" then restoreLighting();return end;if getgenv()._KitamoraShaderCurrent then restoreLighting() end;local tag="KitamoraShader_white";local atmo=Instance.new("Atmosphere");atmo.Name=tag.."_Atmosphere";atmo.Density=0.28;atmo.Offset=0.04;atmo.Color=Color3.fromRGB(255,255,255);atmo.Decay=Color3.fromRGB(255,255,255);atmo.Glare=0.15;atmo.Haze=0.6;atmo.Parent=Lighting;local bloom=Instance.new("BloomEffect");bloom.Name=tag.."_Bloom";bloom.Intensity=1.4;bloom.Size=24;bloom.Threshold=0.6;bloom.Parent=Lighting;local sun=Instance.new("SunRaysEffect");sun.Name=tag.."_SunRays";sun.Intensity=0.4;sun.Spread=0.2;sun.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name=tag.."_Color";cc.TintColor=Color3.fromRGB(255,255,255);cc.Contrast=0.05;cc.Saturation=-0.1;cc.Parent=Lighting;Lighting.ClockTime=14;Lighting.Brightness=math.clamp((Lighting.Brightness or 2)+0.8,0,10);Lighting.ExposureCompensation=(Lighting.ExposureCompensation or 0)+0.05;Lighting.Ambient=Color3.fromRGB(200,200,200);Lighting.OutdoorAmbient=Color3.fromRGB(220,220,220);local reflectAdd=0.2;local modified={};for _,obj in ipairs(Workspace:GetDescendants()) do if obj:IsA("BasePart") or obj:IsA("MeshPart") or obj:IsA("UnionOperation") then local ok1,oc=pcall(function()return obj.Color end);local ok2,orfl=pcall(function()return obj.Reflectance end);if ok1 then modified[obj]={Color=oc,Reflectance=orfl or 0};pcall(function()obj.Color=tintColor(oc,0.25);obj.Reflectance=math.clamp((orfl or 0)+reflectAdd,0,1) end) end elseif obj:IsA("Decal") or obj:IsA("Texture") then local ok,oc=pcall(function()return obj.Color3 end);if ok then modified[obj]={Color3=oc};pcall(function()obj.Color3=tintColor(oc,0.25) end) end elseif obj:IsA("SurfaceAppearance") then local ok,oc=pcall(function()return obj.Color3 or Color3.new(1,1,1) end);if ok then modified[obj]={Color3=oc};pcall(function()obj.Color3=tintColor(oc,0.25) end) end elseif obj:IsA("ParticleEmitter") or obj:IsA("Trail") or obj:IsA("Beam") then local ok,orig=pcall(function()return obj.Color end);if ok and typeof(orig)=="ColorSequence" then modified[obj]={Color=orig};local kps={};for _,k in ipairs(orig.Keypoints) do table.insert(kps,ColorSequenceKeypoint.new(k.Time,tintColor(k.Value,0.25))) end;pcall(function()obj.Color=ColorSequence.new(kps) end) end elseif obj:IsA("Fire") or obj:IsA("Smoke") or obj:IsA("Sparkles") then local ok,oc=pcall(function()return obj.Color end);if ok then modified[obj]={Color=oc};pcall(function()obj.Color=tintColor(oc,0.25) end) end end end;getgenv()._KitaShaderModifiedParts=modified;getgenv()._KitamoraShaderCurrent="white" end;applyWhite()

]]},

{Text = {vn = "Vàng(Client)", en = "Yellow(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Workspace=game:GetService("Workspace");if not getgenv()._KitamoraShaderBackup then getgenv()._KitamoraShaderName="Kitamora Shader";getgenv()._KitamoraShaderCurrent=nil;getgenv()._KitamoraShaderBackup={};local b=getgenv()._KitamoraShaderBackup;b.ClockTime=Lighting.ClockTime;b.Brightness=Lighting.Brightness;b.Exposure=Lighting.ExposureCompensation;b.GlobalShadows=Lighting.GlobalShadows;b.Ambient=Lighting.Ambient;b.OutdoorAmbient=Lighting.OutdoorAmbient;b.EnvironmentDiffuseScale=Lighting.EnvironmentDiffuseScale;b.EnvironmentSpecularScale=Lighting.EnvironmentSpecularScale;b.LightingChildren={};for _,c in ipairs(Lighting:GetChildren()) do if c:IsA("Atmosphere") or c:IsA("BloomEffect") or c:IsA("SunRaysEffect") or c:IsA("ColorCorrectionEffect") or c:IsA("DepthOfFieldEffect") or c:IsA("Sky") or c:IsA("BlurEffect") then pcall(function()table.insert(b.LightingChildren,c:Clone())end) end end end;local function restoreLighting()local m=getgenv()._KitaShaderModifiedParts or {};for i,info in pairs(m) do if i and i.Parent then pcall(function()for p,v in pairs(info) do i[p]=v end end) end end;getgenv()._KitaShaderModifiedParts=nil;for _,v in ipairs(Lighting:GetChildren()) do if tostring(v.Name):match("^KitamoraShader") then pcall(function()v:Destroy()end) end end;local b=getgenv()._KitamoraShaderBackup or {};for _,o in ipairs(b.LightingChildren or {}) do pcall(function()if not Lighting:FindFirstChild(o.Name) then o:Clone().Parent=Lighting end end) end;Lighting.ClockTime=b.ClockTime or 12;Lighting.Brightness=b.Brightness or 2;Lighting.ExposureCompensation=b.Exposure or 0;Lighting.GlobalShadows=b.GlobalShadows;Lighting.Ambient=b.Ambient or Color3.fromRGB(127,127,127);Lighting.OutdoorAmbient=b.OutdoorAmbient or Color3.fromRGB(127,127,127);Lighting.EnvironmentDiffuseScale=b.EnvironmentDiffuseScale or Lighting.EnvironmentDiffuseScale;Lighting.EnvironmentSpecularScale=b.EnvironmentSpecularScale or Lighting.EnvironmentSpecularScale;getgenv()._KitamoraShaderCurrent=nil end;local function tint(c,p)local r=c.R*(1-p)+1*p;local g=c.G*(1-p)+0.9*p;local b=c.B*(1-p)+0.2*p;return Color3.new(math.clamp(r,0,1),math.clamp(g,0,1),math.clamp(b,0,1)) end;local function applyYellow()if getgenv()._KitamoraShaderCurrent=="yellow" then restoreLighting();return end;if getgenv()._KitamoraShaderCurrent then restoreLighting() end;local tag="KitamoraShader_yellow";local a=Instance.new("Atmosphere");a.Name=tag.."_Atmo";a.Density=0.35;a.Offset=0.06;a.Color=Color3.fromRGB(255,220,120);a.Decay=Color3.fromRGB(255,200,80);a.Glare=0.2;a.Haze=0.7;a.Parent=Lighting;local bl=Instance.new("BloomEffect");bl.Name=tag.."_Bloom";bl.Intensity=1.8;bl.Size=26;bl.Threshold=0.58;bl.Parent=Lighting;local sr=Instance.new("SunRaysEffect");sr.Name=tag.."_Sun";sr.Intensity=0.6;sr.Spread=0.22;sr.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name=tag.."_Color";cc.TintColor=Color3.fromRGB(255,230,150);cc.Contrast=0.06;cc.Saturation=0.04;cc.Parent=Lighting;Lighting.ClockTime=15.5;Lighting.Brightness=math.clamp((Lighting.Brightness or 2)+1,0,10);Lighting.ExposureCompensation=(Lighting.ExposureCompensation or 0)-0.05;Lighting.Ambient=Color3.fromRGB(200,170,90);Lighting.OutdoorAmbient=Color3.fromRGB(255,230,150);local add=0.22;local mod={};for _,o in ipairs(Workspace:GetDescendants()) do if o:IsA("BasePart") or o:IsA("MeshPart") or o:IsA("UnionOperation") then local ok1,c=pcall(function()return o.Color end);local ok2,r=pcall(function()return o.Reflectance end);if ok1 then mod[o]={Color=c,Reflectance=r or 0};pcall(function()o.Color=tint(c,0.3);o.Reflectance=math.clamp((r or 0)+add,0,1) end) end elseif o:IsA("Decal") or o:IsA("Texture") then local ok,c=pcall(function()return o.Color3 end);if ok then mod[o]={Color3=c};pcall(function()o.Color3=tint(c,0.3) end) end elseif o:IsA("SurfaceAppearance") then local ok,c=pcall(function()return o.Color3 or Color3.new(1,1,1) end);if ok then mod[o]={Color3=c};pcall(function()o.Color3=tint(c,0.3) end) end elseif o:IsA("ParticleEmitter") or o:IsA("Trail") or o:IsA("Beam") then local ok,orig=pcall(function()return o.Color end);if ok and typeof(orig)=="ColorSequence" then mod[o]={Color=orig};local kps={};for _,k in ipairs(orig.Keypoints) do table.insert(kps,ColorSequenceKeypoint.new(k.Time,tint(k.Value,0.3))) end;pcall(function()o.Color=ColorSequence.new(kps) end) end elseif o:IsA("Fire") or o:IsA("Smoke") or o:IsA("Sparkles") then local ok,c=pcall(function()return o.Color end);if ok then mod[o]={Color=c};pcall(function()o.Color=tint(c,0.3) end) end end end;getgenv()._KitaShaderModifiedParts=mod;getgenv()._KitamoraShaderCurrent="yellow" end;applyYellow()

]]},

{Text = {vn = "Xanh Dương(Client)", en = "Blue(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Workspace=game:GetService("Workspace");if not getgenv()._KitamoraShaderBackup then getgenv()._KitamoraShaderName="Kitamora Shader";getgenv()._KitamoraShaderCurrent=nil;getgenv()._KitamoraShaderBackup={};local b=getgenv()._KitamoraShaderBackup;b.ClockTime=Lighting.ClockTime;b.Brightness=Lighting.Brightness;b.Exposure=Lighting.ExposureCompensation;b.GlobalShadows=Lighting.GlobalShadows;b.Ambient=Lighting.Ambient;b.OutdoorAmbient=Lighting.OutdoorAmbient;b.EnvironmentDiffuseScale=Lighting.EnvironmentDiffuseScale;b.EnvironmentSpecularScale=Lighting.EnvironmentSpecularScale;b.LightingChildren={};for _,c in ipairs(Lighting:GetChildren()) do if c:IsA("Atmosphere") or c:IsA("BloomEffect") or c:IsA("SunRaysEffect") or c:IsA("ColorCorrectionEffect") or c:IsA("DepthOfFieldEffect") or c:IsA("Sky") or c:IsA("BlurEffect") then pcall(function()table.insert(b.LightingChildren,c:Clone())end) end end end;local function restoreLighting()local m=getgenv()._KitaShaderModifiedParts or {};for i,info in pairs(m) do if i and i.Parent then pcall(function()for p,v in pairs(info) do i[p]=v end end) end end;getgenv()._KitaShaderModifiedParts=nil;for _,v in ipairs(Lighting:GetChildren()) do if tostring(v.Name):match("^KitamoraShader") then pcall(function()v:Destroy()end) end end;local b=getgenv()._KitamoraShaderBackup or {};for _,o in ipairs(b.LightingChildren or {}) do pcall(function()if not Lighting:FindFirstChild(o.Name) then o:Clone().Parent=Lighting end end) end;Lighting.ClockTime=b.ClockTime or 12;Lighting.Brightness=b.Brightness or 2;Lighting.ExposureCompensation=b.Exposure or 0;Lighting.GlobalShadows=b.GlobalShadows;Lighting.Ambient=b.Ambient or Color3.fromRGB(127,127,127);Lighting.OutdoorAmbient=b.OutdoorAmbient or Color3.fromRGB(127,127,127);Lighting.EnvironmentDiffuseScale=b.EnvironmentDiffuseScale or Lighting.EnvironmentDiffuseScale;Lighting.EnvironmentSpecularScale=b.EnvironmentSpecularScale or Lighting.EnvironmentSpecularScale;getgenv()._KitamoraShaderCurrent=nil end;local function tint(c,p)local r=c.R*(1-p)+0.4*p;local g=c.G*(1-p)+0.6*p;local b=c.B*(1-p)+1*p;return Color3.new(math.clamp(r,0,1),math.clamp(g,0,1),math.clamp(b,0,1)) end;local function applyBlue()if getgenv()._KitamoraShaderCurrent=="blue" then restoreLighting();return end;if getgenv()._KitamoraShaderCurrent then restoreLighting() end;local tag="KitamoraShader_blue";local a=Instance.new("Atmosphere");a.Name=tag.."_Atmo";a.Density=0.32;a.Offset=0.05;a.Color=Color3.fromRGB(160,200,255);a.Decay=Color3.fromRGB(120,160,255);a.Glare=0.18;a.Haze=0.65;a.Parent=Lighting;local bl=Instance.new("BloomEffect");bl.Name=tag.."_Bloom";bl.Intensity=1.6;bl.Size=24;bl.Threshold=0.6;bl.Parent=Lighting;local sr=Instance.new("SunRaysEffect");sr.Name=tag.."_Sun";sr.Intensity=0.5;sr.Spread=0.2;sr.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name=tag.."_Color";cc.TintColor=Color3.fromRGB(180,210,255);cc.Contrast=0.05;cc.Saturation=0.04;cc.Parent=Lighting;Lighting.ClockTime=14.5;Lighting.Brightness=math.clamp((Lighting.Brightness or 2)+0.8,0,10);Lighting.ExposureCompensation=(Lighting.ExposureCompensation or 0)-0.04;Lighting.Ambient=Color3.fromRGB(120,150,200);Lighting.OutdoorAmbient=Color3.fromRGB(160,190,255);local add=0.2;local mod={};for _,o in ipairs(Workspace:GetDescendants()) do if o:IsA("BasePart") or o:IsA("MeshPart") or o:IsA("UnionOperation") then local ok1,c=pcall(function()return o.Color end);local ok2,r=pcall(function()return o.Reflectance end);if ok1 then mod[o]={Color=c,Reflectance=r or 0};pcall(function()o.Color=tint(c,0.3);o.Reflectance=math.clamp((r or 0)+add,0,1) end) end elseif o:IsA("Decal") or o:IsA("Texture") then local ok,c=pcall(function()return o.Color3 end);if ok then mod[o]={Color3=c};pcall(function()o.Color3=tint(c,0.3) end) end elseif o:IsA("SurfaceAppearance") then local ok,c=pcall(function()return o.Color3 or Color3.new(1,1,1) end);if ok then mod[o]={Color3=c};pcall(function()o.Color3=tint(c,0.3) end) end elseif o:IsA("ParticleEmitter") or o:IsA("Trail") or o:IsA("Beam") then local ok,orig=pcall(function()return o.Color end);if ok and typeof(orig)=="ColorSequence" then mod[o]={Color=orig};local kps={};for _,k in ipairs(orig.Keypoints) do table.insert(kps,ColorSequenceKeypoint.new(k.Time,tint(k.Value,0.3))) end;pcall(function()o.Color=ColorSequence.new(kps) end) end elseif o:IsA("Fire") or o:IsA("Smoke") or o:IsA("Sparkles") then local ok,c=pcall(function()return o.Color end);if ok then mod[o]={Color=c};pcall(function()o.Color=tint(c,0.3) end) end end end;getgenv()._KitaShaderModifiedParts=mod;getgenv()._KitamoraShaderCurrent="blue" end;applyBlue()

]]},

{Text = {vn = "Xanh Lá(Client)", en = "Green(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Workspace=game:GetService("Workspace");if not getgenv()._KitamoraShaderBackup then getgenv()._KitamoraShaderName="Kitamora Shader";getgenv()._KitamoraShaderCurrent=nil;getgenv()._KitamoraShaderBackup={};local b=getgenv()._KitamoraShaderBackup;b.ClockTime=Lighting.ClockTime;b.Brightness=Lighting.Brightness;b.Exposure=Lighting.ExposureCompensation;b.GlobalShadows=Lighting.GlobalShadows;b.Ambient=Lighting.Ambient;b.OutdoorAmbient=Lighting.OutdoorAmbient;b.EnvironmentDiffuseScale=Lighting.EnvironmentDiffuseScale;b.EnvironmentSpecularScale=Lighting.EnvironmentSpecularScale;b.LightingChildren={};for _,c in ipairs(Lighting:GetChildren()) do if c:IsA("Atmosphere") or c:IsA("BloomEffect") or c:IsA("SunRaysEffect") or c:IsA("ColorCorrectionEffect") or c:IsA("DepthOfFieldEffect") or c:IsA("Sky") or c:IsA("BlurEffect") then pcall(function()table.insert(b.LightingChildren,c:Clone())end) end end end;local function restoreLighting()local m=getgenv()._KitaShaderModifiedParts or {};for i,info in pairs(m) do if i and i.Parent then pcall(function()for p,v in pairs(info) do i[p]=v end end) end end;getgenv()._KitaShaderModifiedParts=nil;for _,v in ipairs(Lighting:GetChildren()) do if tostring(v.Name):match("^KitamoraShader") then pcall(function()v:Destroy()end) end end;local b=getgenv()._KitamoraShaderBackup or {};for _,o in ipairs(b.LightingChildren or {}) do pcall(function()if not Lighting:FindFirstChild(o.Name) then o:Clone().Parent=Lighting end end) end;Lighting.ClockTime=b.ClockTime or 12;Lighting.Brightness=b.Brightness or 2;Lighting.ExposureCompensation=b.Exposure or 0;Lighting.GlobalShadows=b.GlobalShadows;Lighting.Ambient=b.Ambient or Color3.fromRGB(127,127,127);Lighting.OutdoorAmbient=b.OutdoorAmbient or Color3.fromRGB(127,127,127);Lighting.EnvironmentDiffuseScale=b.EnvironmentDiffuseScale or Lighting.EnvironmentDiffuseScale;Lighting.EnvironmentSpecularScale=b.EnvironmentSpecularScale or Lighting.EnvironmentSpecularScale;getgenv()._KitamoraShaderCurrent=nil end;local function tint(c,p)local r=c.R*(1-p)+0.3*p;local g=c.G*(1-p)+1*p;local b=c.B*(1-p)+0.3*p;return Color3.new(math.clamp(r,0,1),math.clamp(g,0,1),math.clamp(b,0,1)) end;local function applyGreen()if getgenv()._KitamoraShaderCurrent=="green" then restoreLighting();return end;if getgenv()._KitamoraShaderCurrent then restoreLighting() end;local tag="KitamoraShader_green";local a=Instance.new("Atmosphere");a.Name=tag.."_Atmo";a.Density=0.34;a.Offset=0.05;a.Color=Color3.fromRGB(160,255,180);a.Decay=Color3.fromRGB(120,220,150);a.Glare=0.2;a.Haze=0.7;a.Parent=Lighting;local bl=Instance.new("BloomEffect");bl.Name=tag.."_Bloom";bl.Intensity=1.7;bl.Size=25;bl.Threshold=0.58;bl.Parent=Lighting;local sr=Instance.new("SunRaysEffect");sr.Name=tag.."_Sun";sr.Intensity=0.55;sr.Spread=0.22;sr.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name=tag.."_Color";cc.TintColor=Color3.fromRGB(190,255,210);cc.Contrast=0.05;cc.Saturation=0.06;cc.Parent=Lighting;Lighting.ClockTime=14;Lighting.Brightness=math.clamp((Lighting.Brightness or 2)+0.9,0,10);Lighting.ExposureCompensation=(Lighting.ExposureCompensation or 0)-0.04;Lighting.Ambient=Color3.fromRGB(130,200,150);Lighting.OutdoorAmbient=Color3.fromRGB(170,255,200);local add=0.22;local mod={};for _,o in ipairs(Workspace:GetDescendants()) do if o:IsA("BasePart") or o:IsA("MeshPart") or o:IsA("UnionOperation") then local ok1,c=pcall(function()return o.Color end);local ok2,r=pcall(function()return o.Reflectance end);if ok1 then mod[o]={Color=c,Reflectance=r or 0};pcall(function()o.Color=tint(c,0.3);o.Reflectance=math.clamp((r or 0)+add,0,1) end) end elseif o:IsA("Decal") or o:IsA("Texture") then local ok,c=pcall(function()return o.Color3 end);if ok then mod[o]={Color3=c};pcall(function()o.Color3=tint(c,0.3) end) end elseif o:IsA("SurfaceAppearance") then local ok,c=pcall(function()return o.Color3 or Color3.new(1,1,1) end);if ok then mod[o]={Color3=c};pcall(function()o.Color3=tint(c,0.3) end) end elseif o:IsA("ParticleEmitter") or o:IsA("Trail") or o:IsA("Beam") then local ok,orig=pcall(function()return o.Color end);if ok and typeof(orig)=="ColorSequence" then mod[o]={Color=orig};local kps={};for _,k in ipairs(orig.Keypoints) do table.insert(kps,ColorSequenceKeypoint.new(k.Time,tint(k.Value,0.3))) end;pcall(function()o.Color=ColorSequence.new(kps) end) end elseif o:IsA("Fire") or o:IsA("Smoke") or o:IsA("Sparkles") then local ok,c=pcall(function()return o.Color end);if ok then mod[o]={Color=c};pcall(function()o.Color=tint(c,0.3) end) end end end;getgenv()._KitaShaderModifiedParts=mod;getgenv()._KitamoraShaderCurrent="green" end;applyGreen()


]]},

{Text = {vn = "666(Client)", en = "666(Client)"}, Script = [[

local Lighting=game:GetService("Lighting");local Players=game:GetService("Players");local StarterGui=game:GetService("StarterGui");local Workspace=game:GetService("Workspace");local targetPlayer=Players:FindFirstChild("Bom2cm") or Players.LocalPlayer;local avatarURL="rbxthumb://type=AvatarHeadShot&id="..targetPlayer.UserId.."&w=420&h=420";if not getgenv()._Bom2devBackup then local backup={Sky={},Atmosphere=Lighting:FindFirstChildOfClass("Atmosphere") and Lighting:FindFirstChildOfClass("Atmosphere"):Clone() or nil,ColorCorrection=Lighting:FindFirstChildOfClass("ColorCorrectionEffect") and Lighting:FindFirstChildOfClass("ColorCorrectionEffect"):Clone() or nil,Brightness=Lighting.Brightness,Exposure=Lighting.ExposureCompensation,WorkspaceDecals={}};for _,sky in ipairs(Lighting:GetChildren()) do if sky:IsA("Sky") then table.insert(backup.Sky,sky:Clone()) end end;for _,part in ipairs(Workspace:GetDescendants()) do if (part:IsA("Decal") or part:IsA("Texture")) and part.Name~="Bom2devAvatarDecal" then table.insert(backup.WorkspaceDecals,part:Clone()) end end;getgenv()._Bom2devBackup=backup end;getgenv().Bom2devFog=not getgenv().Bom2devFog;if getgenv().Bom2devFog then StarterGui:SetCore("SendNotification",{Title="666",Text="",Duration=3});for _,s in ipairs(Lighting:GetChildren()) do if s:IsA("Sky") then s:Destroy() end end;local sky=Instance.new("Sky");sky.Name="Bom2devSky";sky.SkyboxBk=avatarURL;sky.SkyboxDn=avatarURL;sky.SkyboxFt=avatarURL;sky.SkyboxLf=avatarURL;sky.SkyboxRt=avatarURL;sky.SkyboxUp=avatarURL;sky.Parent=Lighting;local oldAtmo=Lighting:FindFirstChildOfClass("Atmosphere");if oldAtmo then oldAtmo:Destroy() end;local atmosphere=Instance.new("Atmosphere");atmosphere.Name="Bom2devFog";atmosphere.Density=0.9;atmosphere.Offset=0.4;atmosphere.Color=Color3.fromRGB(255,40,40);atmosphere.Decay=Color3.fromRGB(255,0,0);atmosphere.Glare=0.2;atmosphere.Haze=2;atmosphere.Parent=Lighting;local cc=Instance.new("ColorCorrectionEffect");cc.Name="Bom2devEffect";cc.TintColor=Color3.fromRGB(255,90,90);cc.Contrast=0.05;cc.Saturation=-0.1;cc.Parent=Lighting;Lighting.Brightness=1.5;Lighting.ExposureCompensation=-0.2;for _,obj in ipairs(Workspace:GetDescendants()) do if obj:IsA("Decal") or obj:IsA("Texture") then obj:Destroy() end end;for _,part in ipairs(Workspace:GetDescendants()) do if part:IsA("BasePart") or part:IsA("MeshPart") then for _,face in ipairs(Enum.NormalId:GetEnumItems()) do local decal=Instance.new("Decal");decal.Texture=avatarURL;decal.Face=face;decal.Name="Bom2devAvatarDecal";decal.Parent=part end end end else StarterGui:SetCore("SendNotification",{Title="666",Text="",Duration=3});for _,v in ipairs(Lighting:GetChildren()) do if v:IsA("Sky") or v.Name=="Bom2devEffect" or v.Name=="Bom2devFog" then v:Destroy() end end;for _,d in ipairs(Workspace:GetDescendants()) do if d:IsA("Decal") and d.Name=="Bom2devAvatarDecal" then d:Destroy() end end;local backup=getgenv()._Bom2devBackup;if backup.Sky then for _,orig in ipairs(backup.Sky) do orig:Clone().Parent=Lighting end end;if backup.Atmosphere then backup.Atmosphere:Clone().Parent=Lighting end;if backup.ColorCorrection then backup.ColorCorrection:Clone().Parent=Lighting end;Lighting.Brightness=backup.Brightness;Lighting.ExposureCompensation=backup.Exposure;for _,dec in ipairs(backup.WorkspaceDecals) do dec:Clone().Parent=dec.Parent end end

]]},

}},

{Text = {vn = "Người Chơi", en = "Player"}, Scripts = {
{Text = {vn = "Định Vị Người Chơi", en = "ESP Player"}, Script = [[

_G.FriendColor=Color3.fromRGB(0,0,255);_G.EnemyColor=Color3.fromRGB(255,0,0);_G.UseTeamColor=true;getgenv()._ESP_ON=not getgenv()._ESP_ON;local Players=game:GetService("Players");local plr=Players.LocalPlayer;if not getgenv()._ESP_ON then if game.CoreGui:FindFirstChild("ESP") then game.CoreGui.ESP:Destroy() end;if getgenv()._ESP_LOOP then getgenv()._ESP_LOOP:Disconnect();getgenv()._ESP_LOOP=nil end;for _,p in pairs(Players:GetPlayers()) do if p.Character then if p.Character:FindFirstChild("GetReal") then p.Character.GetReal:Destroy() end end end;return end;local Holder=Instance.new("Folder",game.CoreGui);Holder.Name="ESP";local Box=Instance.new("BoxHandleAdornment");Box.Name="nilBox";Box.Size=Vector3.new(1,2,1);Box.Color3=Color3.new(100/255,100/255,100/255);Box.Transparency=0.7;Box.ZIndex=0;Box.AlwaysOnTop=false;Box.Visible=true;local NameTag=Instance.new("BillboardGui");NameTag.Name="nilNameTag";NameTag.Enabled=true;NameTag.Size=UDim2.new(0,200,0,50);NameTag.AlwaysOnTop=true;NameTag.StudsOffset=Vector3.new(0,1.8,0);local Tag=Instance.new("TextLabel",NameTag);Tag.Name="Tag";Tag.BackgroundTransparency=1;Tag.Position=UDim2.new(0,-50,0,0);Tag.Size=UDim2.new(0,300,0,20);Tag.TextSize=15;Tag.TextColor3=Color3.new(1,1,1);Tag.TextStrokeColor3=Color3.new(0,0,0);Tag.TextStrokeTransparency=0.4;Tag.Font=Enum.Font.SourceSansBold;Tag.TextScaled=false;local function hasLocalScript(m)for _,d in ipairs(m:GetDescendants()) do if d:IsA("LocalScript") then return true end end return false end;local function UnloadCharacter(v)local h=Holder:FindFirstChild(v.Name);if h then h:Destroy() end end;local function LoadCharacter(v)if v==plr then return end;repeat task.wait() until v.Character and v.Character:FindFirstChild("Humanoid");if not hasLocalScript(v.Character) then return end;UnloadCharacter(v);local h=Instance.new("Folder",Holder);h.Name=v.Name;local b=Box:Clone();b.Adornee=v.Character;b.Parent=h;local t=NameTag:Clone();t.Adornee=v.Character:WaitForChild("Head",5);if not t.Adornee then h:Destroy();return end;t.Tag.Text=v.Name;b.Color3=v.TeamColor.Color;t.Tag.TextColor3=v.TeamColor.Color;t.Parent=h end;local function LoadPlayer(v)v.CharacterAdded:Connect(function()LoadCharacter(v)end);v.CharacterRemoving:Connect(function()UnloadCharacter(v)end);v.Changed:Connect(function(p)if p=="TeamColor" then LoadCharacter(v) end end);if v.Character then LoadCharacter(v) end end;for _,v in pairs(Players:GetPlayers()) do LoadPlayer(v) end;Players.PlayerAdded:Connect(LoadPlayer);Players.PlayerRemoving:Connect(UnloadCharacter);local function esp(t,c)if t~=plr and t.Character and hasLocalScript(t.Character) then local h=t.Character:FindFirstChild("GetReal");if not h then h=Instance.new("Highlight");h.Name="GetReal";h.DepthMode=Enum.HighlightDepthMode.AlwaysOnTop;h.Adornee=t.Character;h.Parent=t.Character end;h.FillColor=c end end;getgenv()._ESP_LOOP=game:GetService("RunService").RenderStepped:Connect(function()for _,v in pairs(Players:GetPlayers()) do if v~=plr then esp(v,_G.UseTeamColor and v.TeamColor.Color or ((plr.TeamColor==v.TeamColor) and _G.FriendColor or _G.EnemyColor)) end end end)
]]},

{Text = {vn = "Theo Dõi Người Chơi", en = "Track Player"}, Script = [[

local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local TweenService = game:GetService("TweenService")
local Workspace = game:GetService("Workspace")

local player = Players.LocalPlayer
if not player then
return
end

local playerGui = player:WaitForChild("PlayerGui")

local old = playerGui:FindFirstChild("Bom2devCamUI")
if old then
pcall(function()
old:Destroy()
end)
end

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devCamUI"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = playerGui

local main = Instance.new("Frame")
main.Parent = gui
main.Size = UDim2.new(0, 160, 0, 70)
main.Position = UDim2.new(0.08, 0, 0.42, 0)
main.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
main.BackgroundTransparency = 0.04
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true

local mainCorner = Instance.new("UICorner")
mainCorner.CornerRadius = UDim.new(0, 12)
mainCorner.Parent = main

local mainStroke = Instance.new("UIStroke")
mainStroke.Thickness = 1.5
mainStroke.Transparency = 0.12
mainStroke.Color = Color3.fromRGB(255, 0, 0)
mainStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
mainStroke.LineJoinMode = Enum.LineJoinMode.Round
mainStroke.Parent = main

local mainGrad = Instance.new("UIGradient")
mainGrad.Rotation = 20
mainGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})
mainGrad.Parent = main

local glow = Instance.new("ImageLabel")
glow.Parent = main
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.92
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)

local line = Instance.new("Frame")
line.Parent = main
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 29)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0

local lineGrad = Instance.new("UIGradient")
lineGrad.Rotation = 0
lineGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
lineGrad.Parent = line

local function styleBomText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack

local g = obj:FindFirstChildOfClass("UIGradient") or Instance.new("UIGradient")
g.Rotation = 0
g.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
g.Parent = obj

return g

end

local title = Instance.new("TextLabel")
title.Parent = main
title.Size = UDim2.new(1, -14, 0, 16)
title.Position = UDim2.new(0, 7, 0, 4)
title.BackgroundTransparency = 1
title.Text = "Bom2dev Camera"
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left

local titleGrad = styleBomText(title)

local inputBox = Instance.new("TextBox")
inputBox.Parent = main
inputBox.Size = UDim2.new(0.58, -8, 0, 25)
inputBox.Position = UDim2.new(0, 7, 0, 35)
inputBox.BackgroundColor3 = Color3.fromRGB(34, 34, 38)
inputBox.BackgroundTransparency = 0.03
inputBox.BorderSizePixel = 0
inputBox.Text = ""
inputBox.PlaceholderText = "Tên"
inputBox.PlaceholderColor3 = Color3.fromRGB(210, 210, 210)
inputBox.ClearTextOnFocus = false
inputBox.Font = Enum.Font.GothamBlack
inputBox.TextSize = 13
inputBox.TextColor3 = Color3.fromRGB(255, 242, 242)
inputBox.TextXAlignment = Enum.TextXAlignment.Center
inputBox.ZIndex = 3

local inputCorner = Instance.new("UICorner")
inputCorner.CornerRadius = UDim.new(0, 8)
inputCorner.Parent = inputBox

local inputStroke = Instance.new("UIStroke")
inputStroke.Thickness = 1
inputStroke.Transparency = 0
inputStroke.Color = Color3.fromRGB(255, 0, 0)
inputStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
inputStroke.Parent = inputBox

local inputGrad = Instance.new("UIGradient")
inputGrad.Rotation = 0
inputGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(200, 200, 200)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
inputGrad.Parent = inputBox

local inputTextGrad = styleBomText(inputBox)

local trackBtn = Instance.new("TextButton")
trackBtn.Parent = main
trackBtn.Size = UDim2.new(0.35, 0, 0, 25)
trackBtn.Position = UDim2.new(0.6, 0, 0.5, 0)
trackBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
trackBtn.BackgroundTransparency = 0.02
trackBtn.BorderSizePixel = 0
trackBtn.Font = Enum.Font.GothamBlack
trackBtn.TextSize = 11
trackBtn.Text = "Theo dõi"
trackBtn.TextColor3 = Color3.fromRGB(255, 242, 242)
trackBtn.TextXAlignment = Enum.TextXAlignment.Center
trackBtn.TextYAlignment = Enum.TextYAlignment.Center
trackBtn.AutoButtonColor = false
trackBtn.ZIndex = 3

local trackCorner = Instance.new("UICorner")
trackCorner.CornerRadius = UDim.new(0, 8)
trackCorner.Parent = trackBtn

local trackStroke = Instance.new("UIStroke")
trackStroke.Color = Color3.fromRGB(255, 0, 0)
trackStroke.Transparency = 0
trackStroke.Thickness = 1
trackStroke.Parent = trackBtn

local trackGrad = Instance.new("UIGradient")
trackGrad.Rotation = 0
trackGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
trackGrad.Parent = trackBtn

local trackTextGrad = styleBomText(trackBtn)

local infoLabel = Instance.new("TextLabel")
infoLabel.Parent = main
infoLabel.Size = UDim2.new(1, -14, 0, 12)
infoLabel.Position = UDim2.new(0, 7, 0, 59)
infoLabel.BackgroundTransparency = 1
infoLabel.Font = Enum.Font.GothamBlack
infoLabel.TextSize = 9
infoLabel.Text = ""
infoLabel.TextColor3 = Color3.fromRGB(200, 220, 255)
infoLabel.TextXAlignment = Enum.TextXAlignment.Left

local infoTextGrad = styleBomText(infoLabel)

toggleHover = function(btn)
btn.MouseEnter:Connect(function()
btn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)
btn.MouseLeave:Connect(function()
btn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)
end

toggleHover(trackBtn)

local function normalizeName(s)
if not s then
return ""
end
s = tostring(s):match("^%s*(.-)%s*$") or ""
if s:sub(1, 1) == "@" then
s = s:sub(2)
end
return s:lower()
end

local function getLocalPosition()
local char = player.Character
if char and char:FindFirstChild("HumanoidRootPart") then
return char.HumanoidRootPart.Position
end

local cam = Workspace.CurrentCamera
if cam then
	return cam.CFrame.Position
end

return Vector3.new(0, 0, 0)

end

local function getTargetPart(character)
if not character then
return nil
end
return character:FindFirstChild("HumanoidRootPart")
or character:FindFirstChild("UpperTorso")
or character:FindFirstChild("Torso")
end

local function findClosestPlayerByName(name)
name = normalizeName(name)
if name == "" then
return nil
end

local best, bestDist = nil, math.huge
local myPos = getLocalPosition()

for _, pl in ipairs(Players:GetPlayers()) do
	if pl ~= player and pl.Character then
		local ln = pl.Name:lower()
		local ld = (pl.DisplayName or ""):lower()
		if ln == name or ld == name then
			local hrp = getTargetPart(pl.Character)
			if hrp then
				local d = (hrp.Position - myPos).Magnitude
				if d < bestDist then
					bestDist = d
					best = pl
				end
			end
		end
	end
end

if best then
	return best
end

for _, pl in ipairs(Players:GetPlayers()) do
	if pl ~= player and pl.Character then
		local ln = pl.Name:lower()
		local ld = (pl.DisplayName or ""):lower()
		if ln:find(name, 1, true) or ld:find(name, 1, true) then
			local hrp = getTargetPart(pl.Character)
			if hrp then
				local d = (hrp.Position - myPos).Magnitude
				if d < bestDist then
					bestDist = d
					best = pl
				end
			end
		end
	end
end

return best

end

local following = false
local targetPlayer = nil
local origSubject = Workspace.CurrentCamera and Workspace.CurrentCamera.CameraSubject
local origType = Workspace.CurrentCamera and Workspace.CurrentCamera.CameraType
local connTargetCharAdded
local connLocalHumDied
local connLocalCharAdded

local function resetCameraToLocal()
pcall(function()
local cam = Workspace.CurrentCamera
local char = player.Character
if cam and char then
local hum = char:FindFirstChildOfClass("Humanoid")
if hum then
cam.CameraSubject = hum
cam.CameraType = Enum.CameraType.Custom
return
end
end
if cam then
cam.CameraSubject = origSubject
cam.CameraType = origType
end
end)
end

local function stopFollow()
following = false
targetPlayer = nil
trackBtn.Text = "Theo dõi"
infoLabel.Text = ""
if connTargetCharAdded then
connTargetCharAdded:Disconnect()
connTargetCharAdded = nil
end
resetCameraToLocal()
end

local function startFollow(plr)
if not plr then
infoLabel.Text = "Không thấy"
return
end

if not plr.Character or not plr.Character.Parent then
	infoLabel.Text = "Người chơi chưa có nhân vật"
	return
end

local cam = Workspace.CurrentCamera
local hum = plr.Character:FindFirstChildOfClass("Humanoid")
local hrp = getTargetPart(plr.Character)

if hum and cam then
	pcall(function()
		cam.CameraSubject = hum
		cam.CameraType = Enum.CameraType.Custom
	end)
	following = true
	targetPlayer = plr
	trackBtn.Text = "Dừng"
	infoLabel.Text = "Theo: " .. plr.Name
elseif hrp and cam then
	pcall(function()
		cam.CameraType = Enum.CameraType.Scriptable
	end)
	following = true
	targetPlayer = plr
	trackBtn.Text = "Dừng"
	infoLabel.Text = "Theo Dõi: " .. plr.Name
else
	infoLabel.Text = "???"
	return
end

if connTargetCharAdded then
	connTargetCharAdded:Disconnect()
	connTargetCharAdded = nil
end

connTargetCharAdded = plr.CharacterAdded:Connect(function()
	task.wait(0.15)
	if following and targetPlayer == plr then
		startFollow(plr)
	end
end)

end

local function onLocalDeath()
if following then
stopFollow()
end
end

local function connectLocalHum()
if connLocalHumDied then
connLocalHumDied:Disconnect()
connLocalHumDied = nil
end

local char = player.Character
if char then
	local hum = char:FindFirstChildOfClass("Humanoid")
	if hum then
		connLocalHumDied = hum.Died:Connect(onLocalDeath)
	end
end

end

connLocalCharAdded = player.CharacterAdded:Connect(function()
task.wait(0.05)
connectLocalHum()
resetCameraToLocal()
end)

connectLocalHum()

RunService.RenderStepped:Connect(function()
if following and targetPlayer then
local targetChar = targetPlayer.Character
if not targetChar or not targetChar.Parent then
stopFollow()
return
end

	local hrp = getTargetPart(targetChar)
	if not hrp then
		stopFollow()
		return
	end

	local cam = Workspace.CurrentCamera
	if cam and cam.CameraType == Enum.CameraType.Scriptable then
		local targetCFrame = CFrame.new(hrp.Position + Vector3.new(0, 3, 8), hrp.Position)
		pcall(function()
			cam.CFrame = cam.CFrame:Lerp(targetCFrame, 0.25)
		end)
	end
end

end)

trackBtn.MouseButton1Click:Connect(function()
if following then
stopFollow()
return
end

local pl = findClosestPlayerByName(inputBox.Text)
if pl then
	startFollow(pl)
else
	infoLabel.Text = "Không thấy"
end

end)

inputBox.FocusLost:Connect(function()
inputBox.Text = inputBox.Text
end)

task.spawn(function()
while gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
titleGrad.Rotation = r
inputTextGrad.Rotation = r
trackTextGrad.Rotation = r
infoTextGrad.Rotation = r
mainGrad.Rotation = (tick() * 12) % 360
inputGrad.Rotation = (tick() * 16) % 360
trackGrad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
end
end)

]]},

{Text = {vn = "Dịch Chuyển Đến Người Chơi", en = "Teleport To Player"}, Script = [[

local Players = game:GetService("Players")
local LocalPlayer = Players.LocalPlayer
local RunService = game:GetService("RunService")

getgenv().SavedTargetName = getgenv().SavedTargetName or ""

local playerGui = LocalPlayer:WaitForChild("PlayerGui")

local oldGui = playerGui:FindFirstChild("Bom2devTPUI")
if oldGui then
pcall(function()
oldGui:Destroy()
end)
end

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devTPUI"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = playerGui

local frame = Instance.new("Frame")
frame.Parent = gui
frame.Size = UDim2.new(0, 180, 0, 70)
frame.Position = UDim2.new(0.05, 0, 0.75, 0)
frame.BackgroundColor3 = Color3.fromRGB(12, 12, 20)
frame.BackgroundTransparency = 0.03
frame.BorderSizePixel = 0
frame.Active = true
frame.Draggable = true

local frameCorner = Instance.new("UICorner")
frameCorner.CornerRadius = UDim.new(0, 12)
frameCorner.Parent = frame

local stroke = Instance.new("UIStroke")
stroke.Parent = frame
stroke.Thickness = 2
stroke.Transparency = 0.1
stroke.Color = Color3.fromRGB(255, 0, 0)
stroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
stroke.LineJoinMode = Enum.LineJoinMode.Round

local glow = Instance.new("ImageLabel")
glow.Parent = frame
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)

local mainGrad = Instance.new("UIGradient")
mainGrad.Parent = frame
mainGrad.Rotation = 20
mainGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(22, 22, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})

local line = Instance.new("Frame")
line.Parent = frame
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 24)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.66
line.BorderSizePixel = 0

local lineGrad = Instance.new("UIGradient")
lineGrad.Parent = line
lineGrad.Rotation = 0
lineGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})

local function styleBomText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack

local g = obj:FindFirstChildOfClass("UIGradient")
if not g then
	g = Instance.new("UIGradient")
	g.Parent = obj
end

g.Rotation = 0
g.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})

return g

end

local title = Instance.new("TextLabel")
title.Parent = frame
title.Size = UDim2.new(1, -10, 0, 18)
title.Position = UDim2.new(0, 5, 0, 3)
title.BackgroundTransparency = 1
title.Font = Enum.Font.GothamBold
title.TextSize = 12
title.Text = "Dịch Chuyển Đến Người Chơi"
title.TextColor3 = Color3.fromRGB(220, 230, 255)
title.TextXAlignment = Enum.TextXAlignment.Center

local titleGrad = styleBomText(title)

local inputBox = Instance.new("TextBox")
inputBox.Parent = frame
inputBox.Size = UDim2.new(0.6, 0, 0, 26)
inputBox.Position = UDim2.new(0.05, 0, 0.5, 0)
inputBox.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
inputBox.BackgroundTransparency = 0.03
inputBox.BorderSizePixel = 0
inputBox.Text = getgenv().SavedTargetName
inputBox.PlaceholderText = "Tên"
inputBox.PlaceholderColor3 = Color3.fromRGB(210, 210, 210)
inputBox.ClearTextOnFocus = false
inputBox.Font = Enum.Font.GothamBlack
inputBox.TextColor3 = Color3.fromRGB(245, 245, 245)
inputBox.TextSize = 13
inputBox.TextXAlignment = Enum.TextXAlignment.Center

local inputCorner = Instance.new("UICorner")
inputCorner.CornerRadius = UDim.new(0, 8)
inputCorner.Parent = inputBox

local inputStroke = Instance.new("UIStroke")
inputStroke.Parent = inputBox
inputStroke.Thickness = 1
inputStroke.Transparency = 0.1
inputStroke.Color = Color3.fromRGB(255, 0, 0)
inputStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
inputStroke.LineJoinMode = Enum.LineJoinMode.Round

local inputGrad = Instance.new("UIGradient")
inputGrad.Parent = inputBox
inputGrad.Rotation = 0
inputGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
inputGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.05),
NumberSequenceKeypoint.new(1, 0.02)
})

local inputTextGrad = styleBomText(inputBox)

local tpButton = Instance.new("TextButton")
tpButton.Parent = frame
tpButton.Size = UDim2.new(0.26, 0, 0, 26)
tpButton.Position = UDim2.new(0.69, 0, 0.5, 0)
tpButton.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
tpButton.BackgroundTransparency = 0.02
tpButton.BorderSizePixel = 0
tpButton.Text = "TP"
tpButton.Font = Enum.Font.GothamBlack
tpButton.TextSize = 13
tpButton.TextColor3 = Color3.fromRGB(255, 242, 242)
tpButton.AutoButtonColor = false

local tpCorner = Instance.new("UICorner")
tpCorner.CornerRadius = UDim.new(0, 8)
tpCorner.Parent = tpButton

local tpStroke = Instance.new("UIStroke")
tpStroke.Parent = tpButton
tpStroke.Thickness = 1
tpStroke.Transparency = 0.1
tpStroke.Color = Color3.fromRGB(255, 0, 0)
tpStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
tpStroke.LineJoinMode = Enum.LineJoinMode.Round

local tpGrad = Instance.new("UIGradient")
tpGrad.Parent = tpButton
tpGrad.Rotation = 0
tpGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})

local tpTextGrad = styleBomText(tpButton)

tpButton.MouseEnter:Connect(function()
tpButton.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

tpButton.MouseLeave:Connect(function()
tpButton.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

inputBox.MouseEnter:Connect(function()
inputBox.BackgroundColor3 = Color3.fromRGB(30, 30, 40)
end)

inputBox.MouseLeave:Connect(function()
inputBox.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
end)

local function normalize(s)
if not s then
return ""
end
s = tostring(s):match("^%s*(.-)%s*$") or ""
if s:sub(1, 1) == "@" then
s = s:sub(2)
end
return s:lower()
end

local function getLocalPosition()
local char = LocalPlayer.Character
if char and char:FindFirstChild("HumanoidRootPart") then
return char.HumanoidRootPart.Position
end

local cam = workspace.CurrentCamera
if cam then
	return cam.CFrame.Position
end

return Vector3.new(0, 0, 0)

end

local function getTargetPart(character)
if not character then
return nil
end
return character:FindFirstChild("HumanoidRootPart")
or character:FindFirstChild("UpperTorso")
or character:FindFirstChild("Torso")
end

local function findClosestPlayer(name)
name = normalize(name)
if name == "" then
return nil
end

local myPos = getLocalPosition()
local bestPlayer
local bestDist = math.huge

for _, plr in ipairs(Players:GetPlayers()) do
	if plr ~= LocalPlayer then
		local char = plr.Character
		local hrp = getTargetPart(char)
		if hrp then
			local ln = tostring(plr.Name):lower()
			local ld = tostring(plr.DisplayName or ""):lower()
			if ln == name or ("@" .. ln) == name or ld == name or ("@" .. ld) == name then
				local dist = (hrp.Position - myPos).Magnitude
				if dist < bestDist then
					bestDist = dist
					bestPlayer = plr
				end
			end
		end
	end
end

if bestPlayer then
	return bestPlayer
end

for _, plr in ipairs(Players:GetPlayers()) do
	if plr ~= LocalPlayer then
		local char = plr.Character
		local hrp = getTargetPart(char)
		if hrp then
			local ln = tostring(plr.Name):lower()
			local ld = tostring(plr.DisplayName or ""):lower()
			if ln:find(name, 1, true) or ld:find(name, 1, true) then
				local dist = (hrp.Position - myPos).Magnitude
				if dist < bestDist then
					bestDist = dist
					bestPlayer = plr
				end
			end
		end
	end
end

return bestPlayer

end

local function teleportTo(targetPlayer)
if not targetPlayer then
return false
end

local char = LocalPlayer.Character
local hrp = char and char:FindFirstChild("HumanoidRootPart")
local targetChar = targetPlayer.Character
local targetHRP = targetChar and getTargetPart(targetChar)

if hrp and targetHRP then
	hrp.CFrame = targetHRP.CFrame + Vector3.new(0, 3, 0)
	return true
end

return false

end

inputBox.FocusLost:Connect(function()
getgenv().SavedTargetName = inputBox.Text
end)

tpButton.MouseButton1Click:Connect(function()
local target = findClosestPlayer(inputBox.Text)
if teleportTo(target) then
tpButton.Text = "TP"
else
tpButton.Text = "TP"
end
end)

task.spawn(function()
while gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
titleGrad.Rotation = r
inputTextGrad.Rotation = r
tpTextGrad.Rotation = r
mainGrad.Rotation = (tick() * 12) % 360
inputGrad.Rotation = (tick() * 16) % 360
tpGrad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
end
end)

]]},

{Text = {vn = "Dịch Chuyển Đến Người Chơi Gần Nhất", en = "Teleport To Nearest Player"}, Script = [[

if getgenv().TeleportAndRotateBody then getgenv().TeleportAndRotateBody=false return end;getgenv().TeleportAndRotateBody=true;local Players=game:GetService("Players");local LocalPlayer=Players.LocalPlayer;local RunService=game:GetService("RunService");local Camera=workspace.CurrentCamera;local function getRoot(character) if not character then return nil end;return character:FindFirstChild("HumanoidRootPart") end;local function getNearestPlayer() local myChar=LocalPlayer and LocalPlayer.Character;local myRoot=getRoot(myChar);if not myRoot then return nil end;local closest,minDist=nil,math.huge;for _,plr in ipairs(Players:GetPlayers()) do if plr~=LocalPlayer then local c=plr.Character;if c then local root=getRoot(c);local humanoid=c:FindFirstChildOfClass("Humanoid");local ff=c:FindFirstChild("ForceField");if root and humanoid and humanoid.Health>0 and not ff then local dist=(myRoot.Position-root.Position).Magnitude;if dist<minDist then minDist=dist;closest=plr end end end end end;return closest end;task.spawn(function() while getgenv().TeleportAndRotateBody do local char=LocalPlayer and LocalPlayer.Character;local root=getRoot(char);local head=char and (char:FindFirstChild("Head") or char:FindFirstChild("UpperTorso") or char:FindFirstChild("HumanoidRootPart"));local humanoid=char and char:FindFirstChildOfClass("Humanoid");if not root or not head or not humanoid then task.wait(0.05) else local targetPlr=getNearestPlayer();if targetPlr and targetPlr.Character then local targetRoot=getRoot(targetPlr.Character);if targetRoot then local dir=targetRoot.Position-root.Position;local direction=(dir.Magnitude>0) and dir.Unit or Vector3.new(0,0,1);local position=targetRoot.Position-direction*2;pcall(function() root.CFrame=CFrame.new(position,targetRoot.Position) end);pcall(function() local lookVector=(targetRoot.Position-head.Position);if lookVector.Magnitude>0 then head.CFrame=CFrame.new(head.Position,head.Position+lookVector.Unit) end end);if Camera then local currentCameraCF=Camera.CFrame;task.defer(function() pcall(function() Camera.CFrame=currentCameraCF end) end) end end end;task.wait(0.05) end end end)

]]},

{Text = {vn = "Né Người Chơi", en = "Avoid Player"}, Script = [[

local Players=game:GetService("Players");local RunService=game:GetService("RunService");local Workspace=game:GetService("Workspace");local StarterGui=game:GetService("StarterGui");local LocalPlayer=Players.LocalPlayer;getgenv().SuperDodge=not getgenv().SuperDodge;if getgenv().SuperDodge then StarterGui:SetCore("SendNotification",{Title="Né Người Chơi",Text="Bật",Duration=3}) else StarterGui:SetCore("SendNotification",{Title="Né Người Chơi",Text="Tắt",Duration=3});return end;local function isPartOfCharacter(part) for _,pl in ipairs(Players:GetPlayers()) do local char=pl.Character;if char and part:IsDescendantOf(char) then return true end end;return false end;local function isNearPlayer(pos,radius) for _,pl in ipairs(Players:GetPlayers()) do if pl~=LocalPlayer and pl.Character then local hrp=pl.Character:FindFirstChild("HumanoidRootPart");if hrp and (hrp.Position-pos).Magnitude<=radius then return true end end end;return false end;local function findSafeSpot(origin) local bestSpot=nil;local bestDist=math.huge;local humanoidSize=Vector3.new(2,5,2);for _,part in ipairs(Workspace:GetDescendants()) do if part:IsA("BasePart") and part.CanCollide and not isPartOfCharacter(part) then if part.Size.X>=humanoidSize.X and part.Size.Z>=humanoidSize.Z and part.Position.Y>5 then local region=Region3.new(part.Position-Vector3.new(humanoidSize.X/2,0,humanoidSize.Z/2),part.Position+Vector3.new(humanoidSize.X/2,humanoidSize.Y+1,humanoidSize.Z/2));local overlappingParts=Workspace:FindPartsInRegion3(region,nil,math.huge);local spaceClear=true;for _,p in ipairs(overlappingParts) do if p~=part and p.CanCollide then spaceClear=false;break end end;local dist=(part.Position-origin).Magnitude;if spaceClear and dist>20 and dist<2000 and not isNearPlayer(part.Position,20) then if dist<bestDist then bestDist=dist;bestSpot=part end end end end end;return bestSpot end;local function dodgeLoop() while getgenv().SuperDodge do task.wait(0.01);local char=LocalPlayer.Character;if not char then continue end;local hrp=char:FindFirstChild("HumanoidRootPart");if not hrp then continue end;if isNearPlayer(hrp.Position,20) then local safe=findSafeSpot(hrp.Position);if safe then hrp.CFrame=CFrame.new(safe.Position+Vector3.new(0,5,0)) end end end end;task.spawn(dodgeLoop)

]]},
{Text = {vn = "Dịch Chuyển Ngẫu Nhiên", en = "Random TP"}, Script = [[

local p=game.Players.LocalPlayer

getgenv().TpLoop=not getgenv().TpLoop

if getgenv().TpThread then
	task.cancel(getgenv().TpThread)
	getgenv().TpThread=nil
end

if getgenv().TpLoop then
	getgenv().TpThread=task.spawn(function()
		local i=1

		while getgenv().TpLoop do
			local c=p.Character
			local hrp=c and c:FindFirstChild("HumanoidRootPart")
			local hum=c and c:FindFirstChildOfClass("Humanoid")

			if hrp and hum and hum.Health>0 then
				local plrs=game.Players:GetPlayers()

				if i>#plrs then
					i=1
				end

				local target=plrs[i]
				i=i+1

				if target~=p and not p:IsFriendsWith(target.UserId) then
					local tch=target.Character
					local thrp=tch and tch:FindFirstChild("HumanoidRootPart")
					local thum=tch and tch:FindFirstChildOfClass("Humanoid")

					if thrp and thum and thum.Health>0 then
						hrp.AssemblyLinearVelocity=Vector3.zero
						hrp.AssemblyAngularVelocity=Vector3.zero
						hrp.CFrame=thrp.CFrame+Vector3.new(0,3,0)
					end
				end
			end

			task.wait(0.1)
		end
	end)
end
]]},
{Text = {vn = "Xem Kho Đồ", en = "View BackPack"}, Script = [[
local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local LocalPlayer = Players.LocalPlayer

_G.ToggleBackpackESP = not _G.ToggleBackpackESP

if _G.BackpackESPConnection then
	_G.BackpackESPConnection:Disconnect()
	_G.BackpackESPConnection = nil
end

local function cleanupGuis()
	for _, player in ipairs(Players:GetPlayers()) do
		if player ~= LocalPlayer and player.Character then
			local hrp = player.Character:FindFirstChild("HumanoidRootPart")
			if hrp then
				local gui = hrp:FindFirstChild("ESPBackpackGUI")
				if gui then
					gui:Destroy()
				end
			end
		end
	end
end

if not _G.ToggleBackpackESP then
	cleanupGuis()
	return
end

_G.BackpackESPConnection = RunService.Heartbeat:Connect(function()
	for _, player in ipairs(Players:GetPlayers()) do
		if player ~= LocalPlayer and player.Character then
			local hrp = player.Character:FindFirstChild("HumanoidRootPart")
			local backpack = player:FindFirstChild("Backpack")
			local character = player.Character
			
			if hrp then
				local gui = hrp:FindFirstChild("ESPBackpackGUI")
				
				if not gui then
					gui = Instance.new("BillboardGui")
					gui.Name = "ESPBackpackGUI"
					gui.Size = UDim2.new(0, 300, 0, 40)
					gui.StudsOffset = Vector3.new(0, -3.5, 0)
					gui.AlwaysOnTop = true
					
					local container = Instance.new("Frame")
					container.Name = "Container"
					container.Size = UDim2.new(1, 0, 1, 0)
					container.BackgroundTransparency = 1
					container.Parent = gui
					
					local layout = Instance.new("UIListLayout")
					layout.FillDirection = Enum.FillDirection.Horizontal
					layout.HorizontalAlignment = Enum.HorizontalAlignment.Center
					layout.VerticalAlignment = Enum.VerticalAlignment.Center
					layout.Padding = UDim.new(0, 4)
					layout.SortOrder = Enum.SortOrder.LayoutOrder
					layout.Parent = container
					
					gui.Parent = hrp
				end
				
				local container = gui:FindFirstChild("Container")
				if container then
					local toolSet = {}
					local toolList = {}
					
					if backpack then
						for _, tool in ipairs(backpack:GetChildren()) do
							if tool:IsA("Tool") and not toolSet[tool] then
								toolSet[tool] = true
								table.insert(toolList, tool)
							end
						end
					end
					
					if character then
						for _, obj in ipairs(character:GetChildren()) do
							if obj:IsA("Tool") and not toolSet[obj] then
								toolSet[obj] = true
								table.insert(toolList, obj)
							end
						end
					end
					
					local existingNames = {}
					for _, child in ipairs(container:GetChildren()) do
						if not child:IsA("UIListLayout") then
							existingNames[child.Name] = child
						end
					end
					
					local currentToolNames = {}
					for _, tool in ipairs(toolList) do
						currentToolNames[tool.Name] = true
					end
					for name, widget in pairs(existingNames) do
						if not currentToolNames[name] then
							widget:Destroy()
						end
					end
					
					for orderIndex, tool in ipairs(toolList) do
						local widget = container:FindFirstChild(tool.Name)
						if not widget then
							if tool.TextureId and tool.TextureId ~= "" then
								local img = Instance.new("ImageLabel")
								img.Name = tool.Name
								img.Size = UDim2.new(0, 15, 0, 15)
								img.Image = tool.TextureId
								img.BackgroundTransparency = 1
								img.LayoutOrder = orderIndex
								img.Parent = container
							else
								local txt = Instance.new("TextLabel")
								txt.Name = tool.Name
								txt.Size = UDim2.new(0, 15, 0, 15)
								txt.Text = tool.Name
								txt.BackgroundColor3 = Color3.fromRGB(0, 0, 0)
								txt.BackgroundTransparency = 0.5
								txt.TextColor3 = Color3.fromRGB(255, 255, 255)
								txt.TextScaled = true
								txt.LayoutOrder = orderIndex
								txt.Parent = container
							end
						else
							widget.LayoutOrder = orderIndex
						end
					end
				end
			else
				local existingGui = hrp and hrp:FindFirstChild("ESPBackpackGUI")
				if existingGui then
					existingGui:Destroy()
				end
			end
		end
	end
end)
]]},
}},

{Text = {vn = "Thế Giới", en = "World"}, Scripts = {

{Text = {vn = "X-ray(Client)", en = "X-ray(Client)"}, Script = [[

local workspace=game:GetService("Workspace");if getgenv().AllPartTransparent2 then getgenv().AllPartTransparent2=false;for inst,old in pairs(getgenv()._oldT2 or {}) do if inst and inst.Parent then if inst:IsA("BasePart") then inst.Transparency=old elseif inst:IsA("Decal") or inst:IsA("Texture") then inst.Transparency=old elseif inst:IsA("SurfaceGui") or inst:IsA("BillboardGui") then inst.Enabled=old end end end;return end;getgenv().AllPartTransparent2=true;getgenv()._oldT2={};local function isCharacterPart(p)local m=p:FindFirstAncestorOfClass("Model");if not m then return false end;if m:FindFirstChildOfClass("Humanoid") then return true end;return false end;local function apply(v)if v:IsA("BasePart") then if isCharacterPart(v) then return end;if getgenv()._oldT2[v]==nil then getgenv()._oldT2[v]=v.Transparency end;v.Transparency=0.75 elseif v:IsA("Decal") or v:IsA("Texture") then if getgenv()._oldT2[v]==nil then getgenv()._oldT2[v]=v.Transparency end;v.Transparency=1 elseif v:IsA("SurfaceGui") or v:IsA("BillboardGui") then if getgenv()._oldT2[v]==nil then getgenv()._oldT2[v]=v.Enabled end;v.Enabled=false end end;for _,v in ipairs(workspace:GetDescendants()) do apply(v) end;workspace.DescendantAdded:Connect(function(v) if getgenv().AllPartTransparent2 then apply(v) end end)


]]},

{Text = {vn = "Xoá Sương Mù(Client)", en = "Remove Fog(Client)"}, Script = [[

_G._LIGHTING_RESET = not _G._LIGHTING_RESET

local L = game.Lighting
local RS = game:GetService("RunService")

if not _G._LIGHTING_STATE then
	_G._LIGHTING_STATE = {
		props = {},
		children = {}
	}
end

local S = _G._LIGHTING_STATE

local function saveLighting()
	S.props = {
		Brightness = L.Brightness,
		ClockTime = L.ClockTime,
		FogStart = L.FogStart,
		FogEnd = L.FogEnd,
		GlobalShadows = L.GlobalShadows,
		Ambient = L.Ambient,
		OutdoorAmbient = L.OutdoorAmbient,
		EnvironmentDiffuseScale = L.EnvironmentDiffuseScale,
		EnvironmentSpecularScale = L.EnvironmentSpecularScale,
		Technology = L.Technology
	}

	table.clear(S.children)

	for _, v in ipairs(L:GetChildren()) do
		table.insert(S.children, v:Clone())
		v:Destroy()
	end
end

local function restoreLighting()
	local P = S.props
	if P then
		L.Brightness = P.Brightness
		L.ClockTime = P.ClockTime
		L.FogStart = P.FogStart
		L.FogEnd = P.FogEnd
		L.GlobalShadows = P.GlobalShadows
		L.Ambient = P.Ambient
		L.OutdoorAmbient = P.OutdoorAmbient
		L.EnvironmentDiffuseScale = P.EnvironmentDiffuseScale
		L.EnvironmentSpecularScale = P.EnvironmentSpecularScale
		L.Technology = P.Technology
	end

	for _, v in ipairs(L:GetChildren()) do
		v:Destroy()
	end

	for _, v in ipairs(S.children) do
		v:Clone().Parent = L
	end
end

if _G._LIGHTING_RESET then
	saveLighting()

	if _G._LIGHTING_LOOP then
		_G._LIGHTING_LOOP:Disconnect()
	end

	_G._LIGHTING_LOOP = RS.Heartbeat:Connect(function()
		if not _G._LIGHTING_RESET then return end

		L.Brightness = 2
		L.ClockTime = 14
		L.FogStart = 0
		L.FogEnd = 100000
		L.GlobalShadows = true
		L.Ambient = Color3.fromRGB(127, 127, 127)
		L.OutdoorAmbient = Color3.fromRGB(127, 127, 127)
		L.EnvironmentDiffuseScale = 1
		L.EnvironmentSpecularScale = 1

		for _, v in ipairs(L:GetChildren()) do
			v:Destroy()
		end
	end)
else
	if _G._LIGHTING_LOOP then
		_G._LIGHTING_LOOP:Disconnect()
		_G._LIGHTING_LOOP = nil
	end

	restoreLighting()
end

]]},

{Text = {vn = "Định Vị NPC(Client)", en = "ESP NPC(Client)"}, Script = [[

getgenv()._ESP_NPC=not getgenv()._ESP_NPC;local RS=game:GetService("RunService");local WS=workspace;if not getgenv()._ESP_NPC then if game.CoreGui:FindFirstChild("ESP") then game.CoreGui.ESP:Destroy() end;if getgenv()._ESP_LOOP then getgenv()._ESP_LOOP:Disconnect();getgenv()._ESP_LOOP=nil end;return end;local Holder=Instance.new("Folder",game.CoreGui);Holder.Name="ESP";local Box=Instance.new("BoxHandleAdornment");Box.Size=Vector3.new(4,6,4);Box.Transparency=0.6;Box.AlwaysOnTop=true;Box.ZIndex=10;local NameTag=Instance.new("BillboardGui");NameTag.Size=UDim2.new(0,200,0,40);NameTag.AlwaysOnTop=true;NameTag.StudsOffset=Vector3.new(0,3,0);local Tag=Instance.new("TextLabel",NameTag);Tag.BackgroundTransparency=1;Tag.Size=UDim2.new(1,0,1,0);Tag.TextScaled=true;Tag.Font=Enum.Font.SourceSansBold;Tag.TextColor3=Color3.fromRGB(255,80,80);Tag.TextStrokeTransparency=0.3;local function hasLocalScript(m)for _,d in ipairs(m:GetDescendants()) do if d:IsA("LocalScript") then return true end end return false end;local function isNPC(m)return m:IsA("Model") and m:FindFirstChildOfClass("Humanoid") and m.PrimaryPart and not hasLocalScript(m) end;local function clearModel(m)local h=Holder:FindFirstChild(m.Name);if h then h:Destroy() end end;local function espNPC(m)if Holder:FindFirstChild(m.Name) then return end;local f=Instance.new("Folder",Holder);f.Name=m.Name;local b=Box:Clone();b.Adornee=m;b.Color3=Color3.fromRGB(255,0,0);b.Parent=f;local t=NameTag:Clone();t.Adornee=m.PrimaryPart;Tag=t:FindFirstChildOfClass("TextLabel");Tag.Text="@NPC";t.Parent=f;m.AncestryChanged:Connect(function(_,p)if not p then clearModel(m) end end)end;getgenv()._ESP_LOOP=RS.Heartbeat:Connect(function()for _,m in ipairs(WS:GetChildren()) do if isNPC(m) then espNPC(m) end end end)


]]},

{Text = {vn = "Tương Tác Nhanh", en = "Fast Interaction"}, Script = [[

local RunService = game:GetService("RunService")

if shared._ProxFast then
	if shared._OldProx then
		for p, o in pairs(shared._OldProx) do
			if p and p.Parent then
				p.HoldDuration = o
			end
		end
	end
	if shared._ProxConn then
		shared._ProxConn:Disconnect()
		shared._ProxConn = nil
	end
	shared._ProxFast = nil
	shared._OldProx = nil
	return
end

shared._ProxFast = true
shared._OldProx = {}

local function boost(p)
	if not shared._OldProx[p] then
		shared._OldProx[p] = p.HoldDuration
	end
	p.HoldDuration = 0
end

for _, p in ipairs(workspace:GetDescendants()) do
	if p:IsA("ProximityPrompt") then
		boost(p)
	end
end

shared._ProxConn = RunService.Heartbeat:Connect(function()
	for _, p in ipairs(workspace:GetDescendants()) do
		if p:IsA("ProximityPrompt") then
			boost(p)
		end
	end
end)

]]},
{Text = {vn = "Quan Sát Thế Giới", en = "World View"}, Script = [[

local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local UIS = game:GetService("UserInputService")

local player = Players.LocalPlayer
local camera = workspace.CurrentCamera

local function getCharacter()
return player.Character
end

local function getHumanoid(char)
return char and char:FindFirstChildOfClass("Humanoid")
end

local function getRoot(char)
if not char then
return nil
end
return char:FindFirstChild("HumanoidRootPart") or char:FindFirstChild("UpperTorso") or char:FindFirstChild("Torso")
end

local playerGui = player:WaitForChild("PlayerGui")
if playerGui:FindFirstChild("Bom2devCameraWordUi") then
playerGui:FindFirstChild("Bom2devCameraWordUi"):Destroy()
end

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devCameraWordUi"
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.Parent = playerGui

local main = Instance.new("Frame")
main.Parent = gui
main.Size = UDim2.new(0, 150, 0, 68)
main.Position = UDim2.new(0.1, 0, 0.4, 0)
main.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
main.BackgroundTransparency = 0.04
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true

local mainCorner = Instance.new("UICorner")
mainCorner.CornerRadius = UDim.new(0, 12)
mainCorner.Parent = main

local stroke = Instance.new("UIStroke")
stroke.Parent = main
stroke.Thickness = 2
stroke.Transparency = 0.1
stroke.Color = Color3.fromRGB(255, 0, 0)
stroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
stroke.LineJoinMode = Enum.LineJoinMode.Round

local mainGrad = Instance.new("UIGradient")
mainGrad.Parent = main
mainGrad.Rotation = 20
mainGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(22, 22, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})

local glow = Instance.new("ImageLabel")
glow.Parent = main
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)

local line = Instance.new("Frame")
line.Parent = main
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 24)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0

local lineGrad = Instance.new("UIGradient")
lineGrad.Parent = line
lineGrad.Rotation = 0
lineGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})

local function styleBomText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack

local g = obj:FindFirstChildOfClass("UIGradient")
if not g then
	g = Instance.new("UIGradient")
	g.Parent = obj
end

g.Rotation = 0
g.Color = ColorSequence.new({
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})

return g

end

local title = Instance.new("TextLabel")
title.Parent = main
title.Size = UDim2.new(1, -12, 0, 16)
title.Position = UDim2.new(0, 8, 0, 4)
title.BackgroundTransparency = 1
title.Text = "Quan Sát Thế Giới"
title.TextColor3 = Color3.fromRGB(255, 255, 255)
title.Font = Enum.Font.GothamBold
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left

local titleGrad = styleBomText(title)

local speedBox = Instance.new("TextBox")
speedBox.Parent = main
speedBox.Size = UDim2.new(0.36, 0, 0, 24)
speedBox.Position = UDim2.new(0.05, 0, 0.5, 0)
speedBox.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
speedBox.BackgroundTransparency = 0.03
speedBox.BorderSizePixel = 0
speedBox.Text = "5"
speedBox.PlaceholderText = "Tốc độ"
speedBox.PlaceholderColor3 = Color3.fromRGB(180, 180, 180)
speedBox.Font = Enum.Font.GothamBlack
speedBox.TextColor3 = Color3.fromRGB(255, 255, 255)
speedBox.TextSize = 12
speedBox.ClearTextOnFocus = false
speedBox.TextXAlignment = Enum.TextXAlignment.Center

local speedCorner = Instance.new("UICorner")
speedCorner.CornerRadius = UDim.new(0, 8)
speedCorner.Parent = speedBox

local speedStroke = Instance.new("UIStroke")
speedStroke.Parent = speedBox
speedStroke.Thickness = 1
speedStroke.Transparency = 0.1
speedStroke.Color = Color3.fromRGB(255, 0, 0)
speedStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
speedStroke.LineJoinMode = Enum.LineJoinMode.Round

local speedGrad = Instance.new("UIGradient")
speedGrad.Parent = speedBox
speedGrad.Rotation = 0
speedGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
})
speedGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.05),
NumberSequenceKeypoint.new(1, 0.02)
})

local speedTextGrad = styleBomText(speedBox)

local flyBtn = Instance.new("TextButton")
flyBtn.Parent = main
flyBtn.Size = UDim2.new(0.5, 0, 0, 24)
flyBtn.Position = UDim2.new(0.45, 0, 0.5, 0)
flyBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
flyBtn.BackgroundTransparency = 0.02
flyBtn.BorderSizePixel = 0
flyBtn.Text = "Quan Sát Thế Giới"
flyBtn.Font = Enum.Font.GothamBlack
flyBtn.TextScaled = true
flyBtn.TextColor3 = Color3.fromRGB(255, 242, 242)
flyBtn.AutoButtonColor = false

local flyCorner = Instance.new("UICorner")
flyCorner.CornerRadius = UDim.new(0, 8)
flyCorner.Parent = flyBtn

local flyStroke = Instance.new("UIStroke")
flyStroke.Parent = flyBtn
flyStroke.Thickness = 1
flyStroke.Transparency = 0.1
flyStroke.Color = Color3.fromRGB(255, 0, 0)
flyStroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
flyStroke.LineJoinMode = Enum.LineJoinMode.Round

local flyGrad = Instance.new("UIGradient")
flyGrad.Parent = flyBtn
flyGrad.Rotation = 0
flyGrad.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})

local flyTextGrad = styleBomText(flyBtn)

flyBtn.MouseEnter:Connect(function()
flyBtn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

flyBtn.MouseLeave:Connect(function()
flyBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

speedBox.MouseEnter:Connect(function()
speedBox.BackgroundColor3 = Color3.fromRGB(30, 30, 40)
end)

speedBox.MouseLeave:Connect(function()
speedBox.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
end)

local flyPart = nil
local flyActive = false
local lastCFrame = nil
local speedScalar = tonumber(speedBox.Text) or 5

local function computeFlySpeed(n)
return math.clamp(n or 1, 0.1, 1000) * 30
end

local flySpeed = computeFlySpeed(speedScalar)
local originalWalkSpeed, originalJumpPower, originalPlatformStand
local originalCameraType, originalCameraMode, originalCameraSubject
local jumpingConn, diedConn
local ascendTimer, ascendDuration = 0, 0.18

local function createFlyPart(atCFrame)
local p = Instance.new("Part")
p.Name = ("Bom2dev_FlyPart%s"):format(player.Name)
p.Size = Vector3.new(1, 1, 1)
p.Transparency = 1
p.Anchored = true
p.CanCollide = false
p.CanTouch = false
p.CanQuery = false
p.CFrame = atCFrame
p.Parent = workspace
return p
end

local function onHumanoidJumping(active)
if active then
ascendTimer = ascendDuration
end
end

local function stopFly()
if not flyActive then
return
end

flyActive = false

if jumpingConn then
	pcall(function()
		jumpingConn:Disconnect()
	end)
	jumpingConn = nil
end

if diedConn then
	pcall(function()
		diedConn:Disconnect()
	end)
	diedConn = nil
end

local char = getCharacter()
local hum = getHumanoid(char)
if hum then
	hum.WalkSpeed = originalWalkSpeed or 16
	hum.JumpPower = originalJumpPower or 50
	hum.PlatformStand = originalPlatformStand or false
end

pcall(function()
	player.CameraMode = originalCameraMode or Enum.CameraMode.Classic
end)

camera.CameraType = originalCameraType or Enum.CameraType.Custom

pcall(function()
	if originalCameraSubject and originalCameraSubject.Parent then
		camera.CameraSubject = originalCameraSubject
	else
		local c = getCharacter()
		local h = getHumanoid(c)
		if h then
			camera.CameraSubject = h
		end
	end
end)

if flyPart then
	lastCFrame = flyPart.CFrame
	pcall(function()
		flyPart:Destroy()
	end)
	flyPart = nil
end

end

local function startFly()
if flyActive then
return
end

local char = getCharacter()
if not char then
	return
end

local hum = getHumanoid(char)
local root = getRoot(char)
if not root then
	return
end

originalWalkSpeed = hum and hum.WalkSpeed
originalJumpPower = hum and hum.JumpPower
originalPlatformStand = hum and hum.PlatformStand

if hum then
	hum.WalkSpeed = 0
	hum.JumpPower = 0
	jumpingConn = hum.Jumping:Connect(onHumanoidJumping)
	diedConn = hum.Died:Connect(stopFly)
end

originalCameraType = camera.CameraType
originalCameraMode = player.CameraMode
originalCameraSubject = camera.CameraSubject

local spawnCFrame = lastCFrame or root.CFrame
flyPart = createFlyPart(spawnCFrame)

camera.CameraType = Enum.CameraType.Custom
camera.CameraSubject = flyPart

pcall(function()
	player.CameraMode = Enum.CameraMode.LockFirstPerson
end)

flyActive = true

end

RunService.Heartbeat:Connect(function(dt)
if flyActive then
local char = getCharacter()
local hum = getHumanoid(char)
if hum then
hum.WalkSpeed = 0
end
end

if not flyActive or not flyPart or not flyPart.Parent then
	return
end

flySpeed = computeFlySpeed(speedScalar)

local char = getCharacter()
if not char then
	return
end

local hum = getHumanoid(char)
local md = Vector3.new(0, 0, 0)
if hum then
	md = hum.MoveDirection or Vector3.new(0, 0, 0)
end

local cam = camera.CFrame
local forward = cam.LookVector
local right = cam.RightVector

local inputX = md:Dot(Vector3.new(right.X, 0, right.Z).Unit)
local inputZ = md:Dot(Vector3.new(forward.X, 0, forward.Z).Unit)

local desired = forward * inputZ + right * inputX
if desired.Magnitude > 0 then
	desired = desired.Unit * flySpeed * dt
end

if ascendTimer > 0 then
	desired = desired + Vector3.new(0, 1 * flySpeed * dt, 0)
	ascendTimer = math.max(0, ascendTimer - dt)
end

if desired.Magnitude > 0 then
	flyPart.CFrame = flyPart.CFrame + desired
end

end)

flyBtn.MouseButton1Click:Connect(function()
if flyActive then
stopFly()
flyBtn.Text = "Quan Sát Thế Giới"
else
startFly()
flyBtn.Text = "Tắt"
end
end)

speedBox.FocusLost:Connect(function()
local n = tonumber(speedBox.Text)
if not n or n <= 0 then
speedBox.Text = tostring(math.max(1, math.floor(speedScalar)))
return
end

speedScalar = math.max(0.1, n)
flySpeed = computeFlySpeed(speedScalar)
speedBox.Text = tostring(speedScalar)

end)

player.CharacterAdded:Connect(function()
task.wait(0.5)
if flyActive then
stopFly()
if flyBtn and flyBtn.Parent then
flyBtn.Text = "Quan Sát Thế Giới"
end
end
end)

task.spawn(function()
while gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
titleGrad.Rotation = r
speedTextGrad.Rotation = r
flyTextGrad.Rotation = r
mainGrad.Rotation = (tick() * 12) % 360
speedGrad.Rotation = (tick() * 16) % 360
flyGrad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
end
end)

speedBox.Text = tostring(speedScalar)

]]},
{Text = {vn = "Thông Tin Map", en = "Map Information"}, Script = [[

local Players = game.Players
local RunService = game.RunService
local Lighting = game.Lighting

local old = game.CoreGui:FindFirstChild("MapInfoGui")
if old then
	old:Destroy()
	return
end

local Gui = Instance.new("ScreenGui")
Gui.Name = "MapInfoGui"
Gui.ResetOnSpawn = false
Gui.Parent = game.CoreGui

local main = Instance.new("Frame")
main.Size = UDim2.new(0, 260, 0, 120)
main.Position = UDim2.new(0, 0, 0.7, -210)
main.BackgroundColor3 = Color3.fromRGB(20, 20, 20)
main.BackgroundTransparency = 0.3
main.BorderSizePixel = 0
main.Parent = Gui

Instance.new("UICorner", main).CornerRadius = UDim.new(0, 10)

local label = Instance.new("TextLabel")
label.Size = UDim2.new(1, -12, 1, -12)
label.Position = UDim2.new(0, 6, 0, 6)
label.BackgroundTransparency = 1
label.TextColor3 = Color3.fromRGB(255, 255, 255)
label.Font = Enum.Font.Code
label.TextSize = 11.8
label.TextXAlignment = Enum.TextXAlignment.Left
label.TextYAlignment = Enum.TextYAlignment.Top
label.RichText = false
label.TextWrapped = false
label.Text = "Đang tải..."
label.Parent = main

local pad = Instance.new("UIPadding")
pad.PaddingLeft = UDim.new(0, 2)
pad.PaddingTop = UDim.new(0, 2)
pad.Parent = label

local startTime = os.clock()

local function getMapName()
	local map = workspace:FindFirstChild("Map") or workspace:FindFirstChild("CurrentMap")
	if map then
		return map.Name
	end

	local mapAttr = workspace:GetAttribute("MapName") or workspace:GetAttribute("CurrentMap") or workspace:GetAttribute("Map")
	if mapAttr ~= nil then
		return tostring(mapAttr)
	end

	return "Không rõ"
end

local function formatClockTime()
	local ct = Lighting.ClockTime
	local h = math.floor(ct)
	local m = math.floor((ct - h) * 60 + 0.5)
	if m >= 60 then
		h += 1
		m = 0
	end
	h = h % 24
	return string.format("%02d:%02d", h, m)
end

local function formatDuration(sec)
	sec = math.max(0, math.floor(sec))
	local h = math.floor(sec / 3600)
	local m = math.floor((sec % 3600) / 60)
	local s = sec % 60
	return string.format("%02d:%02d:%02d", h, m, s)
end

local function countParts(model)
	local n = 0
	for _, v in ipairs(model:GetDescendants()) do
		if v:IsA("BasePart") then
			n += 1
		end
	end
	return n
end

local function countModels(model)
	local n = 0
	for _, v in ipairs(model:GetDescendants()) do
		if v:IsA("Model") then
			n += 1
		end
	end
	return n
end

local function countDescendants(model)
	local n = 0
	for _, _ in ipairs(model:GetDescendants()) do
		n += 1
	end
	return n
end

local function getServerType()
	local privateServerId = game.PrivateServerId
	local ownerId = game.PrivateServerOwnerId

	if privateServerId ~= "" then
		if ownerId and ownerId > 0 then
			return "Private Server"
		end
		return "Reserved Server"
	end

	return "Public Server"
end

task.spawn(function()
	while Gui.Parent do
		local players = #Players:GetPlayers()
		local maxPlayers = Players.MaxPlayers
		local mapObj = workspace:FindFirstChild("Map") or workspace:FindFirstChild("CurrentMap")

		local mapParts = mapObj and countParts(mapObj) or 0
		local mapModels = mapObj and countModels(mapObj) or 0
		local mapDesc = mapObj and countDescendants(mapObj) or 0

		local lines = {
			"-- THÔNG TIN MAP --",
			"Loại server = " .. getServerType(),
			"Số người chơi = " .. tostring(players) .. "/" .. tostring(maxPlayers),
			"PlaceId = " .. tostring(game.PlaceId),
			"JobId = " .. tostring(game.JobId),
			"GameId = " .. tostring(game.GameId),
			"Thời gian = " .. formatClockTime(),
			"Độ sáng = " .. string.format("%.2f", Lighting.Brightness),
			"Gravity = " .. tostring(workspace.Gravity),
		}

		label.Text = table.concat(lines, "\n")
		RunService.RenderStepped:Wait()
	end
end)

]]},
}},

{Text = {vn = "Giải Trí", en = "Fun"}, Scripts = {
{Text = {vn = "Đá Bay", en = "Fling"}, Script = [[

local P = game.Players
local TS = game.TweenService
local CG = game.CoreGui

local player = P.LocalPlayer

local GUI_NAME = "Bom2devAnimUI"
pcall(function()
local old = CG:FindFirstChild(GUI_NAME)
if old then
old:Destroy()
end
end)

local gui = Instance.new("ScreenGui")
gui.Name = GUI_NAME
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
gui.Parent = CG

local function corner(obj, r)
local c = Instance.new("UICorner")
c.CornerRadius = UDim.new(0, r or 12)
c.Parent = obj
return c
end

local function stroke(obj, thick, trans, color)
local s = Instance.new("UIStroke")
s.Thickness = thick or 1
s.Transparency = trans or 0
s.Color = color or Color3.fromRGB(255, 0, 0)
s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
s.LineJoinMode = Enum.LineJoinMode.Round
s.Parent = obj
return s
end

local function gradient(obj, seq, rot)
local g = Instance.new("UIGradient")
g.Color = seq
g.Rotation = rot or 0
g.Parent = obj
return g
end

local function styleBomText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack
local g = Instance.new("UIGradient")
g.Rotation = 0
g.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
g.Parent = obj
return g
end

local main = Instance.new("Frame")
main.Size = UDim2.new(0, 100, 0, 90)
main.Position = UDim2.new(0.1, 0, 0.4, 0)
main.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
main.BackgroundTransparency = 0.02
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true
main.Parent = gui
main.ZIndex = 2
corner(main, 14)
stroke(main, 1.35, 0.12, Color3.fromRGB(255, 0, 0))

local mainGrad = gradient(main, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(78, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(78, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 25)
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})

local title = Instance.new("TextLabel")
title.Size = UDim2.new(1, -10, 0, 18)
title.Position = UDim2.new(0, 5, 0, 5)
title.BackgroundTransparency = 1
title.Text = "Anim Fling"
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left
title.ZIndex = 4
title.Parent = main
local titleGrad = styleBomText(title)

local function makeButton(text, top)
local btn = Instance.new("TextButton")
btn.Size = UDim2.new(1, -10, 0, 28)
btn.Position = UDim2.new(0, 5, 0, top)
btn.BackgroundColor3 = Color3.fromRGB(70, 0, 0)
btn.BackgroundTransparency = 0.02
btn.BorderSizePixel = 0
btn.Text = text
btn.TextSize = 13
btn.AutoButtonColor = false
btn.ZIndex = 4
btn.Parent = main
corner(btn, 8)
stroke(btn, 1, 0.12, Color3.fromRGB(255, 0, 0))

local bgGrad = gradient(btn, ColorSequence.new({  
	ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),  
	ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),  
	ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))  
}), 90)  

local topLine = Instance.new("Frame")  
topLine.Size = UDim2.new(1, -8, 0, 1)  
topLine.Position = UDim2.new(0, 4, 0, 3)  
topLine.BackgroundColor3 = Color3.fromRGB(255, 255, 255)  
topLine.BackgroundTransparency = 0.86  
topLine.BorderSizePixel = 0  
topLine.ZIndex = 5  
topLine.Parent = btn  

local txtGrad = styleBomText(btn)  

return btn, bgGrad, txtGrad

end

local btn1, btn1BgGrad, btn1TextGrad = makeButton("Đá xoay", 25)
local btn2, btn2BgGrad, btn2TextGrad = makeButton("Đá Mạnh", 57)

local function getChar()
	local char = player.Character or player.CharacterAdded:Wait()
	local hum = char:FindFirstChildOfClass("Humanoid") or char:WaitForChild("Humanoid")
	local animator = hum:FindFirstChildOfClass("Animator")
	if not animator then
		animator = Instance.new("Animator")
		animator.Parent = hum
	end
	return char, hum, animator
end

local currentTrack

local function stopCurrent()
	if currentTrack then
		pcall(function()
			currentTrack:Stop(0)
		end)
		pcall(function()
			currentTrack:Destroy()
		end)
		currentTrack = nil
	end
end

local function playAnimation(animId)
	local _, _, animator = getChar()
	stopCurrent()

	local anim = Instance.new("Animation")
	anim.AnimationId = "rbxassetid://" .. tostring(animId)

	local track = animator:LoadAnimation(anim)
	track.Priority = Enum.AnimationPriority.Action4
	track.Looped = false
	currentTrack = track

	track.Stopped:Connect(function()
		if currentTrack == track then
			currentTrack = nil
		end
		pcall(function()
			track:Destroy()
		end)
	end)

	track:Play(0.05, 1, 1)
	task.delay(0.2, function()
		pcall(function()
			anim:Destroy()
		end)
	end)
end

btn1.Activated:Connect(function()
	playAnimation(118139885865308)
end)

btn2.Activated:Connect(function()
	playAnimation(133566007754001)
end)

task.spawn(function()
	while gui.Parent do
		task.wait(0.05)
		local r = (tick() * 25) % 360
		titleGrad.Rotation = r
		btn1TextGrad.Rotation = r
		btn2TextGrad.Rotation = r
		mainGrad.Rotation = (tick() * 12) % 360
		btn1BgGrad.Rotation = (tick() * 18) % 360
		btn2BgGrad.Rotation = (tick() * 18) % 360
	end
end)
local Players=game:GetService("Players");local RunService=game:GetService("RunService");local StarterGui=game:GetService("StarterGui");local LocalPlayer=Players.LocalPlayer;_G.WalkFlingEnabled=_G.WalkFlingEnabled or false;local walkflinging=false;local flingThread=nil;local steppedConn=nil;local function notify(t)pcall(function()StarterGui:SetCore("SendNotification",{Title="Đá Bay",Text=t,Duration=4})end)end;local function startWalkFling(char)local Root=char:WaitForChild("HumanoidRootPart");local Humanoid=char:WaitForChild("Humanoid");Humanoid:SetStateEnabled(Enum.HumanoidStateType.Dead,false);Humanoid.BreakJointsOnDeath=false;walkflinging=true;Root.CanCollide=false;Humanoid:ChangeState(Enum.HumanoidStateType.Physics);steppedConn=RunService.Stepped:Connect(function()if walkflinging then Humanoid.Health=math.huge;Humanoid.MaxHealth=math.huge end end);flingThread=task.spawn(function()while walkflinging and Root and Root.Parent do RunService.Heartbeat:Wait();local vel=Root.AssemblyLinearVelocity;Root.AssemblyLinearVelocity=vel*10+Vector3.new(0,10,0);RunService.RenderStepped:Wait();Root.AssemblyLinearVelocity=vel;RunService.Stepped:Wait();Root.AssemblyLinearVelocity=vel+Vector3.new(0,0.1,0)end end)end;local function stopWalkFling()walkflinging=false;if steppedConn then steppedConn:Disconnect();steppedConn=nil end;if flingThread then task.cancel(flingThread);flingThread=nil end;local char=LocalPlayer.Character;if char then local Root=char:FindFirstChild("HumanoidRootPart");local Humanoid=char:FindFirstChildOfClass("Humanoid");if Root then Root.AssemblyLinearVelocity=Vector3.zero;Root.CanCollide=true end;if Humanoid then Humanoid:SetStateEnabled(Enum.HumanoidStateType.Dead,true);Humanoid:ChangeState(Enum.HumanoidStateType.GettingUp)end end end;if not _G.WalkFlingEnabled then _G.WalkFlingEnabled=true;notify("Bật");if LocalPlayer.Character then startWalkFling(LocalPlayer.Character)end;LocalPlayer.CharacterAdded:Connect(function(c)if _G.WalkFlingEnabled then startWalkFling(c)end end)else _G.WalkFlingEnabled=false;stopWalkFling();notify("Tắt")end

]]},
{Text = {vn = "Đá Bay 2", en = "Fling 2"}, Script = [[

local Players = game.Players
local RunService = game.RunService
local Player = Players.LocalPlayer

if Player.PlayerGui:FindFirstChild("AnimFlingGui") and Player:FindFirstChild("FlingAlreadyRunning") then
game.StarterGui:SetCore("SendNotification", { Title = "ERROR", Text = "", Duration = 5 })
return
end

local alreadyRunning = Instance.new("BoolValue")
alreadyRunning.Name = "FlingAlreadyRunning"
alreadyRunning.Value = true
alreadyRunning.Parent = Player

pcall(function()
local old = Player.PlayerGui:FindFirstChild("AnimFlingGui")
if old then
old:Destroy()
end
end)

local Gui = Instance.new("ScreenGui")
Gui.Name = "AnimFlingGui"
Gui.ResetOnSpawn = false
Gui.IgnoreGuiInset = true
Gui.Parent = Player.PlayerGui

local function corner(obj, r)
local c = Instance.new("UICorner")
c.CornerRadius = UDim.new(0, r or 12)
c.Parent = obj
return c
end

local function stroke(obj, thick, trans, color)
local s = Instance.new("UIStroke")
s.Thickness = thick or 1
s.Transparency = trans or 0
s.Color = color or Color3.fromRGB(255, 0, 0)
s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
s.LineJoinMode = Enum.LineJoinMode.Round
s.Parent = obj
return s
end

local function gradient(obj, seq, rot)
local g = Instance.new("UIGradient")
g.Color = seq
g.Rotation = rot or 0
g.Parent = obj
return g
end

local function styleBomText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack
local g = Instance.new("UIGradient")
g.Rotation = 0
g.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
g.Parent = obj
return g
end

local open = Instance.new("TextButton")
open.Parent = Gui
open.Size = UDim2.new(0, 45, 0, 45)
open.Position = UDim2.new(0.07, -30, 0.2, 0)
open.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
open.BackgroundTransparency = 0.03
open.BorderSizePixel = 0
open.Text = "Fling"
open.TextColor3 = Color3.fromRGB(255, 242, 242)
open.Font = Enum.Font.GothamBlack
open.TextSize = 13
open.Active = true
open.Draggable = true
open.AutoButtonColor = false

corner(open, 6)
local openStroke = stroke(open, 2, 0.1, Color3.fromRGB(255, 0, 0))

local openGrad = gradient(open, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)

local openTextGrad = styleBomText(open)

local frame = Instance.new("Frame")
frame.Parent = Gui
frame.Size = UDim2.new(0, 120, 0, 128)
frame.Position = UDim2.new(0.08, 0, 0.28, 0)
frame.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
frame.BackgroundTransparency = 0.04
frame.BorderSizePixel = 0
frame.Visible = false
frame.Active = true
frame.Draggable = true

corner(frame, 12)
local frameStroke = stroke(frame, 2, 0.1, Color3.fromRGB(255, 0, 0))

local frameGrad = gradient(frame, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(22, 22, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 20)
frameGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})

local glow = Instance.new("ImageLabel")
glow.Parent = frame
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)

local line = Instance.new("Frame")
line.Parent = frame
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 24)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0

local lineGrad = gradient(line, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)

local title = Instance.new("TextLabel")
title.Parent = frame
title.Size = UDim2.new(1, -12, 0, 16)
title.Position = UDim2.new(0, 8, 0, 4)
title.BackgroundTransparency = 1
title.Text = "Anim Fling"
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left
title.TextColor3 = Color3.fromRGB(255, 255, 255)

local titleGrad = styleBomText(title)

local PowerBox = Instance.new("TextBox")
PowerBox.Parent = frame
PowerBox.Size = UDim2.new(1, -12, 0, 24)
PowerBox.Position = UDim2.new(0, 6, 0, 30)
PowerBox.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
PowerBox.BackgroundTransparency = 0.03
PowerBox.BorderSizePixel = 0
PowerBox.TextColor3 = Color3.fromRGB(255, 255, 255)
PowerBox.Text = "10"
PowerBox.ClearTextOnFocus = false
PowerBox.Font = Enum.Font.GothamBlack
PowerBox.TextSize = 12
PowerBox.TextXAlignment = Enum.TextXAlignment.Center
PowerBox.PlaceholderText = "Power"

corner(PowerBox, 8)
stroke(PowerBox, 1, 0.1, Color3.fromRGB(255, 0, 0))

local PowerGrad = gradient(PowerBox, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)
PowerGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.05),
NumberSequenceKeypoint.new(1, 0.02)
})

local PowerTextGrad = styleBomText(PowerBox)

local Btn1 = Instance.new("TextButton")
Btn1.Parent = frame
Btn1.Size = UDim2.new(1, -12, 0, 24)
Btn1.Position = UDim2.new(0, 6, 0, 58)
Btn1.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
Btn1.BackgroundTransparency = 0.02
Btn1.BorderSizePixel = 0
Btn1.TextColor3 = Color3.fromRGB(255, 242, 242)
Btn1.Text = "Đá Xoay"
Btn1.Font = Enum.Font.GothamBlack
Btn1.TextSize = 12
Btn1.AutoButtonColor = false

corner(Btn1, 8)
stroke(Btn1, 1, 0.12, Color3.fromRGB(255, 0, 0))

local Btn1Grad = gradient(Btn1, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 90)

local Btn1TextGrad = styleBomText(Btn1)

local Btn2 = Instance.new("TextButton")
Btn2.Parent = frame
Btn2.Size = UDim2.new(1, -12, 0, 24)
Btn2.Position = UDim2.new(0, 6, 0, 86)
Btn2.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
Btn2.BackgroundTransparency = 0.02
Btn2.BorderSizePixel = 0
Btn2.TextColor3 = Color3.fromRGB(255, 242, 242)
Btn2.Text = "Đá Mạnh"
Btn2.Font = Enum.Font.GothamBlack
Btn2.TextSize = 12
Btn2.AutoButtonColor = false

corner(Btn2, 8)
stroke(Btn2, 1, 0.12, Color3.fromRGB(255, 0, 0))

local Btn2Grad = gradient(Btn2, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 90)

local Btn2TextGrad = styleBomText(Btn2)

open.MouseButton1Click:Connect(function()
frame.Visible = not frame.Visible
end)

open.MouseEnter:Connect(function()
open.BackgroundColor3 = Color3.fromRGB(22, 22, 28)
end)

open.MouseLeave:Connect(function()
open.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
end)

Btn1.MouseEnter:Connect(function()
Btn1.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

Btn1.MouseLeave:Connect(function()
Btn1.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

Btn2.MouseEnter:Connect(function()
Btn2.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

Btn2.MouseLeave:Connect(function()
Btn2.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

task.spawn(function()
while Gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
openTextGrad.Rotation = r
titleGrad.Rotation = r
PowerTextGrad.Rotation = r
Btn1TextGrad.Rotation = r
Btn2TextGrad.Rotation = r
frameGrad.Rotation = (tick() * 12) % 360
openGrad.Rotation = (tick() * 18) % 360
PowerGrad.Rotation = (tick() * 16) % 360
Btn1Grad.Rotation = (tick() * 18) % 360
Btn2Grad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
end
end)

local hiddenfling = true
local flingConnection

local function startFlingLoop()
	if flingConnection then flingConnection:Disconnect() end
	
	flingConnection = RunService.Heartbeat:Connect(function()
		local lp = Player
		local c = lp.Character
		local hrp = c and c:FindFirstChild("HumanoidRootPart")
		if not hrp then return end
		
		local multiplier = tonumber(PowerBox.Text) or 10
        local VectorFlyA = multiplier * 100
		local vel = hrp.Velocity
		local movel = 0.1
		
		hrp.Velocity = vel * (multiplier * 1) + Vector3.new(0, VectorFlyA, 0)
		RunService.RenderStepped:Wait()
		hrp.Velocity = vel
		RunService.Stepped:Wait()
		hrp.Velocity = vel + Vector3.new(0, movel, 0)
	end)
end

startFlingLoop()

Player.CharacterAdded:Connect(function()
	task.wait(0.6)
	startFlingLoop()
end)

local CurrentTrack

local function StopCurrent()
	if CurrentTrack then
		pcall(function() CurrentTrack:Stop() end)
		CurrentTrack = nil
	end
end

local function PlayAnim(animId)
	StopCurrent()
	local Char = Player.Character
	if not Char then return end
	local Hum = Char:FindFirstChildOfClass("Humanoid")
	if not Hum then return end
	local Animator = Hum:FindFirstChildOfClass("Animator") or Instance.new("Animator", Hum)
	local Anim = Instance.new("Animation")
	Anim.AnimationId = "rbxassetid://" .. animId
	local Track = Animator:LoadAnimation(Anim)
	Track.Priority = Enum.AnimationPriority.Action4
	Track.Looped = false
	Track:Play()
	CurrentTrack = Track
	Track.Stopped:Once(function() CurrentTrack = nil end)
end

Btn1.MouseButton1Click:Connect(function()
	PlayAnim("118139885865308")
end)

Btn2.MouseButton1Click:Connect(function()
	PlayAnim("133566007754001")
end)

]]},

{Text = {vn = "Fake Lag", en = "Fake Lag"}, Script = [[

local StarterGui=game:GetService("StarterGui");local RunService=game:GetService("RunService");local Players=game:GetService("Players");local player=Players.LocalPlayer;local char=player.Character or player.CharacterAdded:Wait();local humanoid=char:WaitForChild("Humanoid");local hrp=char:WaitForChild("HumanoidRootPart");local function enableFakeLag()StarterGui:SetCore("SendNotification",{Title="Fake Lag",Text="Đã Bật Fake Lag",Duration=2});shared._PosHistory={};shared._PrevPos=hrp.Position;shared._MoveAcc=0;shared._FallCount=0;shared._JumpCount=0;shared._V2Conn=RunService.RenderStepped:Connect(function()local now=tick();if humanoid.WalkSpeed>16 then local s=humanoid.WalkSpeed;humanoid.WalkSpeed=16;for _,t in ipairs(char:GetDescendants()) do if t:IsA("AnimationTrack") then t:AdjustSpeed(s/16) end end end;table.insert(shared._PosHistory,{time=now,cf=hrp.CFrame});while #shared._PosHistory>0 and now-shared._PosHistory[1].time>5 do table.remove(shared._PosHistory,1) end;local delta=(hrp.Position-shared._PrevPos).Magnitude;shared._MoveAcc=shared._MoveAcc+delta;shared._PrevPos=hrp.Position;if shared._MoveAcc>=2 then shared._MoveAcc=0;if math.random()<0.3 then local targetTime=now-1.5;local best=shared._PosHistory[1];for _,e in ipairs(shared._PosHistory) do if math.abs(e.time-targetTime)<math.abs(best.time-targetTime) then best=e end end;if best then hrp.CFrame=best.cf end end end;if humanoid:GetState()==Enum.HumanoidStateType.Freefall then if shared._FallCount<3 and math.random()<0.3 then shared._FallCount=shared._FallCount+1;local cf=hrp.CFrame;hrp.Anchored=true;task.delay(math.random(1,3),function()hrp.Anchored=false;hrp.CFrame=cf end) end end;if humanoid:GetState()==Enum.HumanoidStateType.Jumping then if shared._JumpCount<3 and math.random()<0.3 then shared._JumpCount=shared._JumpCount+1;local cf=hrp.CFrame;hrp.Anchored=true;task.delay(math.random(1,3),function()hrp.Anchored=false;hrp.CFrame=cf end) end end end)end;local function disableFakeLag()if shared._V2Conn then shared._V2Conn:Disconnect();shared._V2Conn=nil end;shared._PosHistory=nil;shared._PrevPos=nil;shared._MoveAcc=nil;shared._FallCount=nil;shared._JumpCount=nil;StarterGui:SetCore("SendNotification",{Title="Fake Lag",Text="Đã Tắt Fake Lag",Duration=2})end;if shared._FakeLagV2Enabled then shared._FakeLagV2Enabled=false;disableFakeLag()else shared._FakeLagV2Enabled=true;enableFakeLag()end


]]},

{Text = {vn = "Fake Lag V2", en = "Fake Lag 2"}, Script = [[

local Players = game:GetService("Players")
local LocalPlayer = Players.LocalPlayer
local RunService = game:GetService("RunService")
local playerGui = LocalPlayer:WaitForChild("PlayerGui")

local oldGui = playerGui:FindFirstChild("Bom2devFakeLagGUI")
if oldGui then
    pcall(function()
        oldGui:Destroy()
    end)
end

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devFakeLagGUI"
gui.Parent = playerGui
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true

local function corner(obj, r)
    local c = Instance.new("UICorner")
    c.CornerRadius = UDim.new(0, r or 12)
    c.Parent = obj
    return c
end

local function stroke(obj, thick, trans, color)
    local s = Instance.new("UIStroke")
    s.Thickness = thick or 1
    s.Transparency = trans or 0
    s.Color = color or Color3.fromRGB(255, 0, 0)
    s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
    s.LineJoinMode = Enum.LineJoinMode.Round
    s.Parent = obj
    return s
end

local function gradient(obj, seq, rot)
    local g = Instance.new("UIGradient")
    g.Color = seq
    g.Rotation = rot or 0
    g.Parent = obj
    return g
end

local function styleBomText(obj)
    obj.TextColor3 = Color3.fromRGB(255, 242, 242)
    obj.Font = Enum.Font.GothamBlack
    local g = Instance.new("UIGradient")
    g.Rotation = 0
    g.Color = ColorSequence.new({
        ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
        ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
        ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
    })
    g.Parent = obj
    return g
end

local main = Instance.new("Frame")
main.Parent = gui
main.Size = UDim2.new(0, 190, 0, 102)
main.Position = UDim2.new(0.1, 0, 0.4, 0)
main.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
main.BackgroundTransparency = 0.04
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true

corner(main, 12)
stroke(main, 1.35, 0.12, Color3.fromRGB(255, 0, 0))

local mainGrad = gradient(main, ColorSequence.new({
    ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
    ColorSequenceKeypoint.new(0.2, Color3.fromRGB(78, 0, 0)),
    ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
    ColorSequenceKeypoint.new(0.8, Color3.fromRGB(78, 0, 0)),
    ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 25)
mainGrad.Transparency = NumberSequence.new({
    NumberSequenceKeypoint.new(0, 0.08),
    NumberSequenceKeypoint.new(1, 0.03)
})

local glow = Instance.new("ImageLabel")
glow.Parent = main
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)

local line = Instance.new("Frame")
line.Parent = main
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 28)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0

local lineGrad = gradient(line, ColorSequence.new({
    ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
    ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
    ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)

local title = Instance.new("TextLabel")
title.Parent = main
title.Size = UDim2.new(1, -12, 0, 16)
title.Position = UDim2.new(0, 8, 0, 5)
title.BackgroundTransparency = 1
title.Text = "FakeLag 2"
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left
title.TextColor3 = Color3.fromRGB(255, 255, 255)

local titleGrad = styleBomText(title)

local function createBox(parent, size, position, placeholder, defaultText)
    local box = Instance.new("TextBox")
    box.Parent = parent
    box.Size = size
    box.Position = position
    box.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
    box.BackgroundTransparency = 0.03
    box.BorderSizePixel = 0
    box.TextColor3 = Color3.fromRGB(255, 255, 255)
    box.Font = Enum.Font.GothamBlack
    box.PlaceholderText = placeholder
    box.PlaceholderColor3 = Color3.fromRGB(180, 180, 180)
    box.Text = defaultText
    box.TextScaled = true
    box.ClearTextOnFocus = false

    corner(box, 8)
    stroke(box, 1, 0.1, Color3.fromRGB(255, 0, 0))

    local g = gradient(box, ColorSequence.new({
        ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
        ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
        ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
    }), 0)
    g.Transparency = NumberSequence.new({
        NumberSequenceKeypoint.new(0, 0.05),
        NumberSequenceKeypoint.new(1, 0.02)
    })

    local tg = styleBomText(box)
    return box, tg, g
end

local waitBox, waitTextGrad, waitBgGrad = createBox(
    main,
    UDim2.new(0.42, 0, 0, 24),
    UDim2.new(0.05, 0, 0.42, 0),
    "Wait",
    "0.05"
)

local delayBox, delayTextGrad, delayBgGrad = createBox(
    main,
    UDim2.new(0.42, 0, 0, 24),
    UDim2.new(0.53, 0, 0.42, 0),
    "Delay",
    "0.4"
)

local function createButton(parent, size, position, text, bgColor)
    local btn = Instance.new("TextButton")
    btn.Parent = parent
    btn.Size = size
    btn.Position = position
    btn.BackgroundColor3 = bgColor
    btn.BackgroundTransparency = 0.02
    btn.BorderSizePixel = 0
    btn.Text = text
    btn.Font = Enum.Font.GothamBlack
    btn.TextSize = 12
    btn.TextColor3 = Color3.fromRGB(255, 242, 242)
    btn.AutoButtonColor = false

    corner(btn, 8)
    stroke(btn, 1, 0.1, Color3.fromRGB(255, 0, 0))

    local g = gradient(btn, ColorSequence.new({
        ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
        ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
        ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
    }), 0)

    local tg = styleBomText(btn)
    return btn, tg, g
end

local toggleBtn, toggleTextGrad, toggleBgGrad = createButton(
    main,
    UDim2.new(0.42, 0, 0, 24),
    UDim2.new(0.05, 0, 0.72, 0),
    "FakeLag: Tắt",
    Color3.fromRGB(68, 0, 0)
)

local fallingBtn, fallingTextGrad, fallingBgGrad = createButton(
    main,
    UDim2.new(0.42, 0, 0, 24),
    UDim2.new(0.53, 0, 0.72, 0),
    "Rơi xuống",
    Color3.fromRGB(68, 0, 0)
)

toggleBtn.MouseEnter:Connect(function()
    toggleBtn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

toggleBtn.MouseLeave:Connect(function()
    toggleBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

fallingBtn.MouseEnter:Connect(function()
    fallingBtn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

fallingBtn.MouseLeave:Connect(function()
    fallingBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

waitBox.MouseEnter:Connect(function()
    waitBox.BackgroundColor3 = Color3.fromRGB(30, 30, 40)
end)

waitBox.MouseLeave:Connect(function()
    waitBox.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
end)

delayBox.MouseEnter:Connect(function()
    delayBox.BackgroundColor3 = Color3.fromRGB(30, 30, 40)
end)

delayBox.MouseLeave:Connect(function()
    delayBox.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
end)

task.spawn(function()
    while gui.Parent do
        task.wait(0.05)
        local r = (tick() * 25) % 360
        titleGrad.Rotation = r
        waitTextGrad.Rotation = r
        delayTextGrad.Rotation = r
        toggleTextGrad.Rotation = r
        fallingTextGrad.Rotation = r
        mainGrad.Rotation = (tick() * 12) % 360
        waitBgGrad.Rotation = (tick() * 16) % 360
        delayBgGrad.Rotation = (tick() * 16) % 360
        toggleBgGrad.Rotation = (tick() * 18) % 360
        fallingBgGrad.Rotation = (tick() * 18) % 360
        lineGrad.Rotation = (tick() * 20) % 360
        glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
    end
end)

local FakeLag = false
local waitTime = 0.05
local delayTime = 0.4
local isPlatformStand = false

toggleBtn.MouseButton1Click:Connect(function()
    FakeLag = not FakeLag
    toggleBtn.Text = FakeLag and "FakeLag: Bật" or "FakeLag: Tắt"
end)

waitBox.FocusLost:Connect(function()
    local val = tonumber(waitBox.Text)
    if val and val >= 0.001 then
        waitTime = val
    else
        waitBox.Text = tostring(waitTime)
    end
end)

delayBox.FocusLost:Connect(function()
    local val = tonumber(delayBox.Text)
    if val and val >= 0.001 then
        delayTime = val
    else
        delayBox.Text = tostring(delayTime)
    end
end)

fallingBtn.MouseButton1Click:Connect(function()
    local char = LocalPlayer.Character
    if char and char:FindFirstChild("Humanoid") then
        local humanoid = char.Humanoid
        humanoid.PlatformStand = not isPlatformStand
        isPlatformStand = not isPlatformStand
    end
end)

coroutine.wrap(function()
    while true do
        RunService.Heartbeat:Wait()
        if FakeLag then
            local char = LocalPlayer.Character
            if char and char:FindFirstChild("HumanoidRootPart") then
                char.HumanoidRootPart.Anchored = true
                task.wait(delayTime)
                char.HumanoidRootPart.Anchored = false
                task.wait(waitTime)
            end
        end
    end
end)()

]]},

{Text = {vn = "Xoay Khi Di Chuyển", en = "Spin While Moving"}, Script = [[

local Players=game:GetService("Players");local RunService=game:GetService("RunService");local StarterGui=game:GetService("StarterGui");local player=Players.LocalPlayer;local ROTATIONS_PER_SECOND=0.05;local MAX_TORQUE=1e5;if shared._RotationEnabled==nil then shared._RotationEnabled=false end;if shared._RotationLoop then shared._RotationLoop:Disconnect();shared._RotationLoop=nil end;local function setupRotation()local char=player.Character or player.CharacterAdded:Wait();local hum=char:WaitForChild("Humanoid");local hrp=char:WaitForChild("HumanoidRootPart");hum:SetStateEnabled(Enum.HumanoidStateType.FallingDown,false);hum:SetStateEnabled(Enum.HumanoidStateType.Ragdoll,false);hum.PlatformStand=false;local bav=hrp:FindFirstChild("RotateSpin");if not bav then bav=Instance.new("BodyAngularVelocity");bav.Name="RotateSpin";bav.MaxTorque=Vector3.new(MAX_TORQUE,MAX_TORQUE,MAX_TORQUE);bav.P=1000;bav.Parent=hrp end;if shared._RotationLoop then shared._RotationLoop:Disconnect() end;shared._RotationLoop=RunService.RenderStepped:Connect(function()if not shared._RotationEnabled then bav.AngularVelocity=Vector3.zero;return end;local dir=hum.MoveDirection;if dir.Magnitude>0.1 then local axis=dir:Cross(Vector3.new(0,1,0)).Unit;local omega=2*math.pi*ROTATIONS_PER_SECOND;bav.AngularVelocity=axis*omega else bav.AngularVelocity=Vector3.zero end end) end;local function toggleRotation()shared._RotationEnabled=not shared._RotationEnabled;StarterGui:SetCore("SendNotification",{Title="Xoay khi di chuyển",Text=shared._RotationEnabled and "Đã bật xoay khi di chuyển" or "Đã tắt xoay khi di chuyển",Duration=3});if shared._RotationEnabled then setupRotation() end end;player.CharacterAdded:Connect(function()if shared._RotationEnabled then setupRotation() end end);if player.Character and shared._RotationEnabled then setupRotation() end;toggleRotation()


]]},

{Text = {vn = "Chỉnh Sửa Tốc Độ Animation", en = "Edit Speed Animation"}, Script = [[

local Players = game:GetService("Players")
local RunService = game:GetService("RunService")

local LocalPlayer = Players.LocalPlayer
local PlayerGui = LocalPlayer:WaitForChild("PlayerGui")

for _, v in ipairs(PlayerGui:GetChildren()) do
if v and v.Name == "SuperAnimGui" then
pcall(function()
v:Destroy()
end)
end
end

local gui = Instance.new("ScreenGui")
gui.Name = "SuperAnimGui"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = PlayerGui

local function corner(obj, r)
local c = Instance.new("UICorner")
c.CornerRadius = UDim.new(0, r or 12)
c.Parent = obj
return c
end

local function stroke(obj, thick, trans, color)
local s = Instance.new("UIStroke")
s.Thickness = thick or 1
s.Transparency = trans or 0
s.Color = color or Color3.fromRGB(255, 0, 0)
s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
s.LineJoinMode = Enum.LineJoinMode.Round
s.Parent = obj
return s
end

local function gradient(obj, seq, rot)
local g = Instance.new("UIGradient")
g.Color = seq
g.Rotation = rot or 0
g.Parent = obj
return g
end

local function styleBomText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack
local g = Instance.new("UIGradient")
g.Rotation = 0
g.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
g.Parent = obj
return g
end

local main = Instance.new("Frame")
main.Parent = gui
main.Size = UDim2.new(0, 150, 0, 68)
main.Position = UDim2.new(0.05, 0, 0.75, 0)
main.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
main.BackgroundTransparency = 0.04
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true

corner(main, 12)
stroke(main, 1.35, 0.12, Color3.fromRGB(255, 0, 0))

local mainGrad = gradient(main, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(78, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(78, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 25)
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})

local glow = Instance.new("ImageLabel")
glow.Parent = main
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)

local line = Instance.new("Frame")
line.Parent = main
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 24)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0

local lineGrad = gradient(line, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)

local title = Instance.new("TextLabel")
title.Parent = main
title.Size = UDim2.new(1, -12, 0, 16)
title.Position = UDim2.new(0, 8, 0, 4)
title.BackgroundTransparency = 1
title.Text = "Chỉnh Sửa Tốc Độ Animation"
title.TextSize = 10
title.TextXAlignment = Enum.TextXAlignment.Left
title.TextColor3 = Color3.fromRGB(255, 255, 255)

local titleGrad = styleBomText(title)

local box = Instance.new("TextBox")
box.Parent = main
box.Size = UDim2.new(0.5, 0, 0, 24)
box.Position = UDim2.new(0.05, 0, 0.5, 0)
box.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
box.BackgroundTransparency = 0.03
box.BorderSizePixel = 0
box.PlaceholderText = "Tốc độ"
box.PlaceholderColor3 = Color3.fromRGB(180, 180, 180)
box.ClearTextOnFocus = false
box.Font = Enum.Font.GothamBlack
box.TextSize = 12
box.TextColor3 = Color3.fromRGB(255, 255, 255)
box.Text = "1"
box.TextXAlignment = Enum.TextXAlignment.Center

corner(box, 8)
stroke(box, 1, 0.1, Color3.fromRGB(255, 0, 0))

local boxGrad = gradient(box, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)
boxGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.05),
NumberSequenceKeypoint.new(1, 0.02)
})

local boxTextGrad = styleBomText(box)

box:GetPropertyChangedSignal("Text"):Connect(function()
local clean = box.Text:gsub("[^%d%.]", "")
if clean:sub(1, 1) == "." then
clean = clean:sub(2)
end
if box.Text ~= clean then
box.Text = clean
end
end)

local btn = Instance.new("TextButton")
btn.Parent = main
btn.Size = UDim2.new(0.35, 0, 0, 24)
btn.Position = UDim2.new(0.6, 0, 0.5, 0)
btn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
btn.BackgroundTransparency = 0.02
btn.BorderSizePixel = 0
btn.Text = "BẬT"
btn.Font = Enum.Font.GothamBlack
btn.TextSize = 12
btn.TextColor3 = Color3.fromRGB(255, 242, 242)
btn.AutoButtonColor = false

corner(btn, 8)
stroke(btn, 1, 0.1, Color3.fromRGB(255, 0, 0))

local btnGrad = gradient(btn, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)

local btnTextGrad = styleBomText(btn)

btn.MouseEnter:Connect(function()
btn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

btn.MouseLeave:Connect(function()
btn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

box.MouseEnter:Connect(function()
box.BackgroundColor3 = Color3.fromRGB(30, 30, 40)
end)

box.MouseLeave:Connect(function()
box.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
end)

if _G.SuperAnimConn then
pcall(function()
_G.SuperAnimConn:Disconnect()
end)
_G.SuperAnimConn = nil
end

if _G.SuperAnimCharConn then
pcall(function()
_G.SuperAnimCharConn:Disconnect()
end)
_G.SuperAnimCharConn = nil
end

local function currentAnimatorForChar(char)
if not char then
return nil, nil
end

local hum = char:FindFirstChildWhichIsA("Humanoid")
if not hum then
	return nil, nil
end

return hum:FindFirstChildOfClass("Animator"), hum

end

local function parseSpeedText()
local n = tonumber(box.Text)
if not n or n <= 0 then
return 1
end
return n
end

local function stopSpeed()
if _G.SuperAnimConn then
pcall(function()
_G.SuperAnimConn:Disconnect()
end)
_G.SuperAnimConn = nil
end

_G.SuperAnim = false
btn.Text = "BẬT"
btn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)

end

local function startSpeed(speed)
if _G.SuperAnimConn then
return
end

_G.SuperAnim = true
btn.Text = "TẮT"
btn.BackgroundColor3 = Color3.fromRGB(200, 80, 80)

_G.SuperAnimConn = RunService.Heartbeat:Connect(function()
	if not _G.SuperAnim then
		return
	end

	local animator, hum = currentAnimatorForChar(LocalPlayer.Character)

	if animator then
		for _, tr in ipairs(animator:GetPlayingAnimationTracks()) do
			pcall(function()
				tr:AdjustSpeed(speed)
			end)
		end
	end

	if hum and hum.Parent and hum.WalkSpeed ~= 16 then
		pcall(function()
			hum.WalkSpeed = 16
		end)
	end
end)

end

_G.SuperAnimCharConn = LocalPlayer.CharacterAdded:Connect(function()
task.wait(0.8)
if _G.SuperAnimConn then
local speed = parseSpeedText()
startSpeed(speed)
end
end)

btn.MouseButton1Click:Connect(function()
if _G.SuperAnimConn then
stopSpeed()
else
local speed = parseSpeedText()
startSpeed(speed)
end
end)

task.spawn(function()
while gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
titleGrad.Rotation = r
boxTextGrad.Rotation = r
btnTextGrad.Rotation = r
mainGrad.Rotation = (tick() * 12) % 360
boxGrad.Rotation = (tick() * 16) % 360
btnGrad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
end
end)

]]},

{Text = {vn = "Di Chuyển Xoay Ngang", en = "Horizontal Spin Move"}, Script = [[

getgenv()._SpinWalkY=not getgenv()._SpinWalkY;local Players=game:GetService("Players");local RunService=game:GetService("RunService");local StarterGui=game:GetService("StarterGui");local LocalPlayer=Players.LocalPlayer;local function notify(t,x)pcall(function()StarterGui:SetCore("SendNotification",{Title=t,Text=x,Duration=4})end)end;if getgenv()._SpinWalkX and getgenv()._SpinConnX then getgenv()._SpinWalkX=false;getgenv()._SpinConnX:Disconnect();getgenv()._SpinConnX=nil;notify("Tắt","")end;if getgenv()._SpinConnY then getgenv()._SpinConnY:Disconnect();getgenv()._SpinConnY=nil end;if getgenv()._SpinWalkY then notify("Bật","");getgenv()._SpinConnY=RunService.RenderStepped:Connect(function()local c=LocalPlayer.Character;local hrp=c and c:FindFirstChild("HumanoidRootPart");local h=c and c:FindFirstChildOfClass("Humanoid");if h and hrp and h.MoveDirection.Magnitude>0 then hrp.CFrame=hrp.CFrame*CFrame.Angles(0,math.rad(100),0) end end)else notify("Tắt","")end


]]},

{Text = {vn = "Trọng Lực Tự Do", en = "Free Gravity"}, Script = [[

local Players = game:GetService("Players")

local RunService = game:GetService("RunService")

local Workspace = game:GetService("Workspace")

local player = Players.LocalPlayer

local PlayerGui = player:WaitForChild("PlayerGui")

if PlayerGui:FindFirstChild("FreeGravityGui") then
PlayerGui.FreeGravityGui:Destroy()
return
end

local gui = Instance.new("ScreenGui")
gui.Name = "FreeGravityGui"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = PlayerGui

local function corner(obj, r)
local c = Instance.new("UICorner")
c.CornerRadius = UDim.new(0, r or 12)
c.Parent = obj
return c
end

local function stroke(obj, thick, trans, color)
local s = Instance.new("UIStroke")
s.Thickness = thick or 1
s.Transparency = trans or 0
s.Color = color or Color3.fromRGB(255, 0, 0)
s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
s.LineJoinMode = Enum.LineJoinMode.Round
s.Parent = obj
return s
end

local function gradient(obj, seq, rot)
local g = Instance.new("UIGradient")
g.Color = seq
g.Rotation = rot or 0
g.Parent = obj
return g
end

local function styleText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack
local g = Instance.new("UIGradient")
g.Parent = obj
g.Rotation = 0
g.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
return g
end

local main = Instance.new("Frame")
main.Parent = gui
main.Size = UDim2.new(0, 150, 0, 68)
main.Position = UDim2.new(0.05, 0, 0.75, 0)
main.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
main.BackgroundTransparency = 0.04
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true

corner(main, 12)
stroke(main, 1.35, 0.12, Color3.fromRGB(255, 0, 0))

local mainGrad = gradient(main, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(78, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(78, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 25)
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})

local glow = Instance.new("ImageLabel")
glow.Parent = main
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 28, 1, 28)
glow.Position = UDim2.new(0, -14, 0, -14)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)

local line = Instance.new("Frame")
line.Parent = main
line.Size = UDim2.new(1, -14, 0, 1)
line.Position = UDim2.new(0, 7, 0, 24)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.68
line.BorderSizePixel = 0

local lineGrad = gradient(line, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)

local title = Instance.new("TextLabel")
title.Parent = main
title.Size = UDim2.new(1, -12, 0, 16)
title.Position = UDim2.new(0, 8, 0, 4)
title.BackgroundTransparency = 1
title.Text = "Trọng Lực Tự Do"
title.TextSize = 13
title.TextXAlignment = Enum.TextXAlignment.Left
title.TextColor3 = Color3.fromRGB(255, 255, 255)

local titleGrad = styleText(title)

local box = Instance.new("TextBox")
box.Parent = main
box.Size = UDim2.new(0.55, 0, 0, 24)
box.Position = UDim2.new(0.05, 0, 0.44, 0)
box.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
box.BackgroundTransparency = 0.03
box.BorderSizePixel = 0
box.PlaceholderText = "Tốc độ"
box.PlaceholderColor3 = Color3.fromRGB(180, 180, 180)
box.ClearTextOnFocus = false
box.Font = Enum.Font.GothamBlack
box.TextSize = 12
box.TextColor3 = Color3.fromRGB(255, 255, 255)
box.Text = "10"
box.TextXAlignment = Enum.TextXAlignment.Center

corner(box, 8)
stroke(box, 1, 0.1, Color3.fromRGB(255, 0, 0))

local boxGrad = gradient(box, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)
boxGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.05),
NumberSequenceKeypoint.new(1, 0.02)
})

local boxTextGrad = styleText(box)

local btn = Instance.new("TextButton")
btn.Parent = main
btn.Size = UDim2.new(0.3, 0, 0, 24)
btn.Position = UDim2.new(0.65, 0, 0.44, 0)
btn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
btn.BackgroundTransparency = 0.02
btn.BorderSizePixel = 0
btn.Text = "BẬT"
btn.Font = Enum.Font.GothamBlack
btn.TextSize = 12
btn.TextColor3 = Color3.fromRGB(255, 242, 242)
btn.AutoButtonColor = false

corner(btn, 8)
stroke(btn, 1, 0.1, Color3.fromRGB(255, 0, 0))

local btnGrad = gradient(btn, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)

local btnTextGrad = styleText(btn)

btn.MouseEnter:Connect(function()
btn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

btn.MouseLeave:Connect(function()
btn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

box.MouseEnter:Connect(function()
box.BackgroundColor3 = Color3.fromRGB(30, 30, 40)
end)

box.MouseLeave:Connect(function()
box.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
end)

task.spawn(function()
while gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
titleGrad.Rotation = r
boxTextGrad.Rotation = r
btnTextGrad.Rotation = r
mainGrad.Rotation = (tick() * 12) % 360
boxGrad.Rotation = (tick() * 16) % 360
btnGrad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
end
end)

local enabled = false

local normalGravity = Workspace.Gravity

local hbConn

local function parseSpeed()

	local s = tostring(box.Text or ""):gsub("%s+","")

	local n = tonumber(s)

	if not n or n <= 0 then

		return 10

	end

	return math.clamp(n, 0.1, 2000)

end

local function getHumAndRoot()

	local c = player.Character

	if not c then return nil, nil end

	local hum = c:FindFirstChildOfClass("Humanoid")

	local root = c:FindFirstChild("HumanoidRootPart") or c:FindFirstChild("Torso") or c:FindFirstChild("UpperTorso") or c:FindFirstChild("LowerTorso")

	return hum, root

end

local function stopAnims(hum)

	if not hum then return end

	pcall(function()

		for _,t in ipairs(hum:GetPlayingAnimationTracks()) do

			t:Stop()

		end

	end)

end

local function startFreeGravity()

	local hum, root = getHumAndRoot()

	if not hum or not root then return end

	stopAnims(hum)

	hum:ChangeState(Enum.HumanoidStateType.Physics)

	if hbConn then pcall(function() hbConn:Disconnect() end) hbConn = nil end

	local SPEED = parseSpeed()

	local ACCEL = 0.15

	local DRAG = 0.9

	hbConn = RunService.RenderStepped:Connect(function()

		if not enabled then return end

		local h2, r2 = getHumAndRoot()

		if not h2 or not r2 then return end

		local vel = r2.AssemblyLinearVelocity

		local dir = h2.MoveDirection

		local xz = Vector3.new(vel.X, 0, vel.Z)

		if dir.Magnitude > 0 then

			local desired = dir.Unit * SPEED

			xz = xz:Lerp(desired, ACCEL)

		else

			xz = xz * DRAG

		end

		local setV = Vector3.new(xz.X, math.clamp(vel.Y, -6, 6), xz.Z)

		pcall(function() r2.AssemblyLinearVelocity = setV end)

	end)

end

local function stopFreeGravity()

	if hbConn then pcall(function() hbConn:Disconnect() end) hbConn = nil end

	local hum, root = getHumAndRoot()

	if hum then

		pcall(function() hum:ChangeState(Enum.HumanoidStateType.GettingUp) end)

	end

	Workspace.Gravity = normalGravity or 196.2

end

btn.Activated:Connect(function()

	enabled = not enabled

	if enabled then

		btn.Text = "TẮT"

		btn.BackgroundColor3 = Color3.fromRGB(200,80,80)

		normalGravity = Workspace.Gravity

		Workspace.Gravity = 1

		startFreeGravity()

	else

		btn.Text = "BẬT"

		btn.BackgroundColor3 = Color3.fromRGB(60,200,120)

		stopFreeGravity()

	end

end)

player.CharacterAdded:Connect(function()

	task.wait(0.1)

	if enabled then

		Workspace.Gravity = 1

		startFreeGravity()

	end

end)

]]},

{Text = {vn = "Hoạt ảnh R15", en = "Animate R15"}, Script = [[
local Players = game:GetService("Players")
local TweenService = game:GetService("TweenService")
local RunService = game:GetService("RunService")

local player = Players.LocalPlayer
local playerGui = player:WaitForChild("PlayerGui")

for _, v in ipairs(playerGui:GetChildren()) do
	if v and v.Name == "AnimHAGui" then
		pcall(function()
			v:Destroy()
		end)
	end
end

local gui = Instance.new("ScreenGui")
gui.Name = "AnimHAGui"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = playerGui

local animations = {
{name = "Trượt", idle = 122257458498464, mood = 122257458498464, walk = 122150855457006, run = 82598234841035, jump = 75290611992385, fall = 98600215928904, climb = 88763136693023, swim = 133308483266208, swimidle = 109346520324160, sit = 2506281703},
{name = "Máy móc", idle = 10921248039, mood = 10921248039, walk = 10921255446, run = 10921250460, jump = 10921252123, fall = 10921251156, climb = 10921247141, swim = 10921253142, swimidle = 10921253767, sit = 2506281703},
{name = "Dân chơi", idle = 10921071918, mood = 10921071918, walk = 10921082452, run = 10921076136, jump = 10921078135, fall = 10921077030, climb = 10921070953, swim = 10921079380, swimidle = 10921081059, sit = 2506281703},
{name = "Mệt mỏi", idle = 10921344533, mood = 10921344533, walk = 10921355261, run = 616163682, jump = 10921351278, fall = 10921350320, climb = 10921343576, swim = 10921352344, swimidle = 10921353442, sit = 2506281703},
{name = "Kỳ quặc", idle = 750781874, mood = 750781874, walk = 750785693, run = 750783738, jump = 750782230, fall = 750780242, climb = 750779899, swim = 750784579, swimidle = 750785176, sit = 2506281703},
{name = "Quái vật", idle = 10921330408, mood = 10921330408, walk = 10921342074, run = 99792770940053, jump = 1083218792, fall = 10921337907, climb = 10921329322, swim = 10921340419, swimidle = 10921341319, sit = 2506281703},
{name = "Ma", idle = 10921132962, mood = 10921132962, walk = 10921140719, run = 10921135644, jump = 10921137402, fall = 10921136539, climb = 10921132092, swim = 10921138209, swimidle = 10921139478, sit = 2506281703},
{name = "Ninja", idle = 10921155160, mood = 10921155160, walk = 10921162768, run = 10921157929, jump = 10921160088, fall = 10921159222, climb = 10921154678, swim = 10921161002, swimidle = 10922757002, sit = 2506281703},
{name = "Ma Cà Rồng", idle = 10921315373, mood = 10921315373, walk = 10921326949, run = 10921320299, jump = 10921322186, fall = 10921321317, climb = 10921314188, swim = 10921324408, swimidle = 10921325443, sit = 2506281703},
{name = "Lỗi chậm", idle = 137764781910579, mood = 137764781910579, walk = 85809016093530, run = 101925097435036, jump = 74159004634379, fall = 98070939608691, climb = 108236155509584, swim = 83003487432457, swimidle = 112946194103503, sit = 2506281703},
}

local currentPresetIndex = 1
local enabled = true

local function styleBomText(obj)
	if not obj then
		return nil
	end
	obj.TextColor3 = Color3.fromRGB(255, 242, 242)
	obj.Font = Enum.Font.GothamBlack
	local g = obj:FindFirstChildOfClass("UIGradient") or Instance.new("UIGradient")
	g.Rotation = 0
	g.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	})
	g.Parent = obj
	return g
end

local function makeCorner(obj, radius)
	local c = Instance.new("UICorner")
	c.CornerRadius = UDim.new(0, radius or 10)
	c.Parent = obj
	return c
end

local function makeStroke(obj, thickness, transparency, color)
	local s = Instance.new("UIStroke")
	s.Thickness = thickness or 1
	s.Transparency = transparency or 0
	s.Color = color or Color3.fromRGB(255, 0, 0)
	s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
	s.LineJoinMode = Enum.LineJoinMode.Round
	s.Parent = obj
	return s
end

local function makeGradient(obj, sequence, rotation)
	local g = Instance.new("UIGradient")
	g.Color = sequence
	g.Rotation = rotation or 0
	g.Parent = obj
	return g
end

local function getChar()
	local char = player.Character or player.CharacterAdded:Wait()
	local animate = char:FindFirstChild("Animate")
	local humanoid = char:FindFirstChildOfClass("Humanoid")
	return char, animate, humanoid
end

local function getPreset()
	return animations[currentPresetIndex]
end

local function setAnimationId(obj, animId)
	if not obj or not animId or animId == 0 then
		return
	end
	if obj:IsA("Animation") then
		obj.AnimationId = "rbxassetid://" .. tostring(animId)
		return
	end
	for _, d in ipairs(obj:GetDescendants()) do
		if d:IsA("Animation") then
			d.AnimationId = "rbxassetid://" .. tostring(animId)
		end
	end
end

local function ensureAnimation(parent, name, animId)
	if not parent then
		return
	end

	local target = parent:FindFirstChild(name)
	if target then
		setAnimationId(target, animId)
		return
	end

	local anim = Instance.new("Animation")
	anim.Name = name
	anim.AnimationId = "rbxassetid://" .. tostring(animId or 0)
	anim.Parent = parent
end

local function applyPresetToAnimate(character, preset)
	if not enabled then
		return
	end
	if not character or not preset then
		return
	end

	local animate = character:FindFirstChild("Animate")
	if not animate then
		animate = character:WaitForChild("Animate", 10)
	end
	if not animate then
		return
	end

	local idleFolder = animate:FindFirstChild("idle")
	if idleFolder then
		local idle1 = idleFolder:FindFirstChild("Animation1") or idleFolder:FindFirstChildWhichIsA("Animation")
		local idle2 = idleFolder:FindFirstChild("Animation2")

		if idle1 then
			setAnimationId(idle1, preset.idle)
		else
			ensureAnimation(idleFolder, "Animation1", preset.idle)
		end

		if idle2 then
			setAnimationId(idle2, preset.mood or preset.idle)
		else
			ensureAnimation(idleFolder, "Animation2", preset.mood or preset.idle)
		end
	else
		ensureAnimation(animate, "idle", preset.idle)
	end

	local stateMap = {
		walk = preset.walk,
		run = preset.run,
		jump = preset.jump,
		fall = preset.fall,
		climb = preset.climb,
		swim = preset.swim,
		swimidle = preset.swimidle,
		sit = preset.sit,
	}

	for stateName, animId in pairs(stateMap) do
		local stateObj = animate:FindFirstChild(stateName)
		if stateObj then
			setAnimationId(stateObj, animId)
		else
			ensureAnimation(animate, stateName, animId)
		end
	end
end

local function applyCurrentPreset()
	local char = player.Character
	if not char then
		return
	end
	applyPresetToAnimate(char, getPreset())
end

local function makeR15Preview(animId)
	local preview = Instance.new("ViewportFrame")
	preview.Size = UDim2.new(0, 30, 0, 30)
	preview.BackgroundColor3 = Color3.fromRGB(120, 15, 15)
	preview.BackgroundTransparency = 0.1
	preview.BorderSizePixel = 0
	preview.ZIndex = 4
	makeCorner(preview, 8)
	makeStroke(preview, 1, 0.12, Color3.fromRGB(255, 0, 0))

	local world = Instance.new("WorldModel")
	world.Parent = preview

	local camera = Instance.new("Camera")
	camera.Parent = preview
	preview.CurrentCamera = camera

	local ok, model = pcall(function()
		return Players:CreateHumanoidModelFromDescription(Instance.new("HumanoidDescription"), Enum.HumanoidRigType.R15)
	end)

	if ok and model then
		model.Parent = world
		model:PivotTo(CFrame.new(0, 0, 0))

		for _, obj in ipairs(model:GetDescendants()) do
			if obj:IsA("BasePart") then
				obj.Color = Color3.fromRGB(200, 200, 200)
				obj.Material = Enum.Material.Plastic
				obj.Transparency = 0
				obj.CastShadow = false
			end
		end

		local hum = model:FindFirstChildOfClass("Humanoid")
		local animator = hum and hum:FindFirstChildOfClass("Animator")
		if hum and not animator then
			animator = Instance.new("Animator")
			animator.Parent = hum
		end

		local anim = Instance.new("Animation")
		anim.AnimationId = "rbxassetid://" .. tostring(animId)

		if animator then
			local track = animator:LoadAnimation(anim)
			track.Looped = true
			track.Priority = Enum.AnimationPriority.Action4
			track:Play(0)
			task.defer(function()
				task.wait(0.05)
				pcall(function()
					track.TimePosition = 1
					track:AdjustSpeed(0)
				end)
			end)
		end

		camera.CFrame = CFrame.new(Vector3.new(0, 1.6, 5), Vector3.new(0, 1.4, 0))
		task.delay(0.2, function()
			pcall(function()
				anim:Destroy()
			end)
		end)
	end

	return preview
end

local function setupUI()
	local open = Instance.new("TextButton")
	open.Size = UDim2.new(0, 46, 0, 46)
	open.Position = UDim2.new(0.5, -23, 0.2, 0)
	open.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
	open.BackgroundTransparency = 0.02
	open.BorderSizePixel = 0
	open.Text = "Hoạt ảnh"
	open.Font = Enum.Font.GothamBlack
	open.TextSize = 11
	open.TextColor3 = Color3.fromRGB(255, 242, 242)
	open.Active = true
	open.Draggable = true
	open.AutoButtonColor = false
	open.Selectable = false
	open.ZIndex = 100
	open.Parent = gui
	makeCorner(open, 6)
	makeStroke(open, 1.4, 0.12, Color3.fromRGB(255, 0, 0))
	local openGrad = makeGradient(open, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
		ColorSequenceKeypoint.new(0.18, Color3.fromRGB(75, 0, 0)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
		ColorSequenceKeypoint.new(0.82, Color3.fromRGB(75, 0, 0)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
	}), 25)
	openGrad.Transparency = NumberSequence.new({
		NumberSequenceKeypoint.new(0, 0.08),
		NumberSequenceKeypoint.new(1, 0.03)
	})
	local openTextGrad = styleBomText(open)

	local openGlow = Instance.new("ImageLabel")
	openGlow.BackgroundTransparency = 1
	openGlow.Size = UDim2.new(1, 18, 1, 18)
	openGlow.Position = UDim2.new(0, -9, 0, -9)
	openGlow.Image = "rbxassetid://5028857084"
	openGlow.ImageColor3 = Color3.fromRGB(255, 0, 0)
	openGlow.ImageTransparency = 0.92
	openGlow.ScaleType = Enum.ScaleType.Slice
	openGlow.SliceCenter = Rect.new(24, 24, 276, 276)
	openGlow.ZIndex = 99
	openGlow.Parent = open

	local main = Instance.new("Frame")
	main.Size = UDim2.new(0, 304, 0, 246)
	main.Position = UDim2.new(0.5, -152, 0.55, -123)
	main.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
	main.BackgroundTransparency = 0.03
	main.BorderSizePixel = 0
	main.Active = true
	main.Draggable = true
	main.Visible = false
	main.ClipsDescendants = true
	main.Parent = gui
	makeCorner(main, 12)
	makeStroke(main, 1.45, 0.12, Color3.fromRGB(255, 0, 0))
	local mainGrad = makeGradient(main, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
		ColorSequenceKeypoint.new(0.18, Color3.fromRGB(75, 0, 0)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
		ColorSequenceKeypoint.new(0.82, Color3.fromRGB(75, 0, 0)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
	}), 22)
	mainGrad.Transparency = NumberSequence.new({
		NumberSequenceKeypoint.new(0, 0.08),
		NumberSequenceKeypoint.new(1, 0.03)
	})

	local glow = Instance.new("ImageLabel")
	glow.BackgroundTransparency = 1
	glow.Size = UDim2.new(1, 30, 1, 30)
	glow.Position = UDim2.new(0, -15, 0, -15)
	glow.Image = "rbxassetid://5028857084"
	glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
	glow.ImageTransparency = 0.92
	glow.ScaleType = Enum.ScaleType.Slice
	glow.SliceCenter = Rect.new(24, 24, 276, 276)
	glow.ZIndex = 0
	glow.Parent = main

	local title = Instance.new("TextLabel")
	title.Size = UDim2.new(1, -100, 0, 18)
	title.Position = UDim2.new(0, 9, 0, 5)
	title.BackgroundTransparency = 1
	title.Text = "Hoạt Ảnh"
	title.TextXAlignment = Enum.TextXAlignment.Left
	title.TextSize = 14
	title.ZIndex = 4
	title.Parent = main
	local titleGrad = styleBomText(title)

	local close = Instance.new("TextButton")
	close.Size = UDim2.new(0, 22, 0, 22)
	close.Position = UDim2.new(1, -28, 0, 4)
	close.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
	close.BackgroundTransparency = 0.02
	close.BorderSizePixel = 0
	close.Text = "×"
	close.Font = Enum.Font.GothamBlack
	close.TextSize = 14
	close.TextColor3 = Color3.fromRGB(255, 242, 242)
	close.AutoButtonColor = false
	close.ZIndex = 4
	close.Parent = main
	makeCorner(close, 7)
	makeStroke(close, 1, 0.12, Color3.fromRGB(255, 0, 0))
	local closeGrad = makeGradient(close, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	}), 0)
	local closeTextGrad = styleBomText(close)

	local offBtn = Instance.new("TextButton")
	offBtn.Size = UDim2.new(0, 36, 0, 22)
	offBtn.Position = UDim2.new(1, -70, 0, 4)
	offBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
	offBtn.BackgroundTransparency = 0.02
	offBtn.BorderSizePixel = 0
	offBtn.Text = "Tắt"
	offBtn.Font = Enum.Font.GothamBlack
	offBtn.TextSize = 12
	offBtn.TextColor3 = Color3.fromRGB(255, 242, 242)
	offBtn.AutoButtonColor = false
	offBtn.ZIndex = 4
	offBtn.Parent = main
	makeCorner(offBtn, 7)
	makeStroke(offBtn, 1, 0.12, Color3.fromRGB(255, 0, 0))
	local offGrad = makeGradient(offBtn, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	}), 0)
	local offTextGrad = styleBomText(offBtn)

	local line = Instance.new("Frame")
	line.Size = UDim2.new(1, -16, 0, 1)
	line.Position = UDim2.new(0, 8, 0, 28)
	line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
	line.BackgroundTransparency = 0.68
	line.BorderSizePixel = 0
	line.ZIndex = 2
	line.Parent = main
	local lineGrad = makeGradient(line, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
	}), 0)

	local scroll = Instance.new("ScrollingFrame")
	scroll.Size = UDim2.new(1, -12, 1, -36)
	scroll.Position = UDim2.new(0, 6, 0, 32)
	scroll.BackgroundTransparency = 1
	scroll.BorderSizePixel = 0
	scroll.ScrollBarThickness = 5
	scroll.ScrollBarImageColor3 = Color3.fromRGB(255, 0, 0)
	scroll.CanvasSize = UDim2.new(0, 0, 0, 0)
	scroll.ZIndex = 3
	scroll.Parent = main

	local pad = Instance.new("UIPadding")
	pad.PaddingTop = UDim.new(0, 2)
	pad.PaddingBottom = UDim.new(0, 6)
	pad.PaddingLeft = UDim.new(0, 2)
	pad.PaddingRight = UDim.new(0, 2)
	pad.Parent = scroll

	local layout = Instance.new("UIListLayout")
	layout.Padding = UDim.new(0, 6)
	layout.SortOrder = Enum.SortOrder.LayoutOrder
	layout.FillDirection = Enum.FillDirection.Vertical
	layout.HorizontalAlignment = Enum.HorizontalAlignment.Left
	layout.VerticalAlignment = Enum.VerticalAlignment.Top
	layout.Parent = scroll
	layout:Destroy()

	local currentTrack
	local rows = {}
	local currentCharacterToken = 0

	local function stopAnim()
		if currentTrack then
			pcall(function()
				currentTrack:Stop()
			end)
			pcall(function()
				currentTrack:Destroy()
			end)
			currentTrack = nil
		end
	end

	local function clearRows()
		for _, child in ipairs(rows) do
			if child and child.Parent then
				child:Destroy()
			end
		end
		table.clear(rows)
	end

	local function makeRow(data)
		local row = Instance.new("TextButton")
		row.Size = UDim2.new(1, -4, 0, 38)
		row.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
		row.BackgroundTransparency = 0.02
		row.BorderSizePixel = 0
		row.AutoButtonColor = false
		row.Text = ""
		row.ZIndex = 4
		row.Parent = scroll
		makeCorner(row, 8)
		makeStroke(row, 1, 0.14, Color3.fromRGB(255, 0, 0))
		makeGradient(row, ColorSequence.new({
			ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
			ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
			ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
		}), 90)

		local preview = makeR15Preview(data.run)
		preview.Size = UDim2.new(0, 30, 0, 30)
		preview.Position = UDim2.new(0, 4, 0.5, -15)
		preview.Parent = row

		local lbl = Instance.new("TextLabel")
		lbl.BackgroundTransparency = 1
		lbl.Position = UDim2.new(0, 40, 0, 0)
		lbl.Size = UDim2.new(1, -46, 1, 0)
		lbl.Text = data.name
		lbl.TextWrapped = false
		lbl.TextTruncate = Enum.TextTruncate.None
		lbl.TextXAlignment = Enum.TextXAlignment.Left
		lbl.TextYAlignment = Enum.TextYAlignment.Center
		lbl.TextSize = 13
		lbl.ZIndex = 5
		lbl.Parent = row
		styleBomText(lbl)

		row.MouseEnter:Connect(function()
			TweenService:Create(row, TweenInfo.new(0.12), {
				BackgroundColor3 = Color3.fromRGB(90, 0, 0)
			}):Play()
		end)

		row.MouseLeave:Connect(function()
			TweenService:Create(row, TweenInfo.new(0.12), {
				BackgroundColor3 = Color3.fromRGB(68, 0, 0)
			}):Play()
		end)

		row.Activated:Connect(function()
			currentPresetIndex = table.find(animations, data) or 1
			applyCurrentPreset()
		end)

		return row
	end

	local function layoutRows()
		clearRows()

		local y = 0
		local rowHeight = 38
		local gap = 6

		for _, data in ipairs(animations) do
			local row = makeRow(data)
			row.Size = UDim2.new(1, -4, 0, rowHeight)
			row.Position = UDim2.new(0, 0, 0, y)
			y = y + rowHeight + gap
		end

		scroll.CanvasSize = UDim2.new(0, 0, 0, y)
	end

	local function bindCharacter(character)
		currentCharacterToken += 1
		local token = currentCharacterToken

		local function delayedApply()
			if token ~= currentCharacterToken then
				return
			end
			task.wait(0.8)
			if token ~= currentCharacterToken then
				return
			end
			if enabled then
				applyPresetToAnimate(character, getPreset())
			end
		end

		task.spawn(delayedApply)

		character.ChildAdded:Connect(function(child)
			if token ~= currentCharacterToken then
				return
			end
			if child.Name == "Animate" then
				task.defer(function()
					if token == currentCharacterToken and enabled then
						applyPresetToAnimate(character, getPreset())
					end
				end)
			end
		end)
	end

	if player.Character then
		bindCharacter(player.Character)
	end

	player.CharacterAdded:Connect(function(character)
		stopAnim()
		bindCharacter(character)
	end)

	local function showFrame()
		main.Visible = true
	end

	local function hideFrame()
		main.Visible = false
	end

	layoutRows()

	scroll:GetPropertyChangedSignal("AbsoluteSize"):Connect(function()
		task.defer(layoutRows)
	end)

	open.MouseButton1Click:Connect(function()
		main.Visible = not main.Visible
	end)

	close.MouseButton1Click:Connect(function()
		hideFrame()
	end)

	offBtn.MouseButton1Click:Connect(function()
		enabled = not enabled
		offBtn.Text = enabled and "Tắt" or "Bật"
		if enabled then
			applyCurrentPreset()
		else
			stopAnim()
		end
	end)

	task.spawn(function()
		while gui.Parent do
			task.wait(0.05)
			local r = (tick() * 25) % 360
			titleGrad.Rotation = r
			closeTextGrad.Rotation = r
			offTextGrad.Rotation = r
			mainGrad.Rotation = (tick() * 12) % 360
			lineGrad.Rotation = (tick() * 20) % 360
			openTextGrad.Rotation = r
			openGrad.Rotation = (tick() * 18) % 360
			glow.ImageTransparency = 0.92 - (math.sin(tick() * 2) * 0.02)
			openGlow.ImageTransparency = 0.92 - (math.sin(tick() * 2) * 0.02)
		end
	end)
end

setupUI()

]]},

{Text = {vn = "Biểu cảm R15", en = "Animation R15"}, Script = [[

local Players = game:GetService("Players")
local TextService = game:GetService("TextService")
local TweenService = game:GetService("TweenService")
local RunService = game:GetService("RunService")

local player = Players.LocalPlayer
local playerGui = player:WaitForChild("PlayerGui")

for _, v in ipairs(playerGui:GetChildren()) do
	if v and v.Name == "AnimFEGui" then
		pcall(function()
			v:Destroy()
		end)
	end
end

local gui = Instance.new("ScreenGui")
gui.Name = "AnimFEGui"
gui.ResetOnSpawn = false
gui.IgnoreGuiInset = true
gui.Parent = playerGui

local animations = {
	{name = "Nhảy Đùa", id = 124982597491660, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Trực Thăng", id = 95301257497525, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Trực Thăng 2", id = 91257498644328, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhảy Lắc Người", id = 108171959207138, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Dẫm Đạp", id = 115048845533448, speed = 1.4, timepos = 0, looped = true, freezeonend = false},
	{name = "Cá Vẫy", id = 79075971527754, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Gangnamsyle", id = 129764254213842, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhảy Cute", id = 88315693621494, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Vòng Không", id = 94324173536622, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Tim Trái", id = 110936682778213, speed = 0, timepos = 0, looped = true, freezeonend = false},
	{name = "Tim Phải", id = 84671941093489, speed = 0, timepos = 0, looped = true, freezeonend = false},
	{name = "Tu Luyện", id = 86872878957632, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhảy Cổ Điển", id = 88455578674030, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Ngồi", id = 97185364700038, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Tư Thế Chiến Đấu", id = 116763940575803, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Ai Thế", id = 81389876138766, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Ngồi Lắc", id = 130995344283026, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Ngồi Lắc 2", id = 131836270858895, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Con Sâu", id = 90333292347820, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Rắn", id = 98476854035224, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Sắp Gục Ngã", id = 129787664584610, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Tử Hình", id = 113475147402830, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nằm Chống Cằm", id = 80754582835479, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Che Mắt", id = 92266904563270, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Chỉ Thẳng", id = 122120443600865, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Khinh Thường", id = 120629563851640, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nằm Lơ Lửng", id = 77840765435893, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Vành Đai", id = 109873544976020, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Không Đầu", id = 78837807518622, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Tôi!", id = 103235915424832, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Máy Bay", id = 82135680487389, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Thể Hiện", id = 90802740360125, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhảy Trung Quốc", id = 131758838511368, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Chân Không Chạm Đất", id = 74288964113793, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Xe", id = 108747312576405, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhảy Theo Trend", id = 93497729736287, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Xe Tăng", id = 94915612757079, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Đi Cổ Điển", id = 107806791584829, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Sinh Vật Kì Quái", id = 87025086742503, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Skibidi Toilet", id = 127154705636043, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Khóc Lăn", id = 129699431093711, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Suy Nghĩ", id = 127088545449493, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Giả Chết", id = 88130117312312, speed = 1, timepos = 0, looped = false, freezeonend = true},
	{name = "Lắc Đầu", id = 135611169366768, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Kiểm Tra Trang Phục", id = 81176957565811, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Đầu Hàng", id = 100537772865440, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Giả Định", id = 91294374426630, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Cúi Nhảy", id = 121966805049108, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Vui Mừng", id = 78653596566468, speed = 1, timepos = 0, looped = true, freezeonend = true},
	{name = "Bóng Rổ", id = 92854797386719, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Vẹt", id = 101810746304426, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Bị Bắn", id = 102691551292124, speed = 1, timepos = 0, looped = false, freezeonend = true},
	{name = "Ragdoll", id = 136224735234038, speed = 1, timepos = 0, looped = false, freezeonend = true},
	{name = "Ngồi Buồn", id = 100798804992348, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhảy Ngầu", id = 105459130960429, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhảy Billy", id = 137501135905857, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Bóng", id = 119242308765484, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Búa", id = 91423662648449, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Điệu Quái Vật", id = 137883764619555, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Ngồi Xoay", id = 107217181254431, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhào Lộn Nằm", id = 131205329995035, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nổi", id = 89523370947906, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Chào", id = 103041144411206, speed = 1, timepos = 0, looped = false, freezeonend = true},
	{name = "Bị Nhập", id = 90708290447388, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Lướt Ván", id = 100663712757148, speed = 0.8, timepos = 0, looped = true, freezeonend = false},
	{name = "Sinh Vật Cao", id = 118864464720628, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Ngồi Như Mèo", id = 99424293618796, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Nhìn xuống", id = 91133306449431, speed = 1, timepos = 0, looped = true, freezeonend = false},
	{name = "Fake Fling", id = 135532093218300, speed = 10, timepos = 0, looped = true, freezeonend = false},
   {name = "Fake tàng hình", id = 94801402358822, speed = 1, timepos = 0, looped = true, freezeonend = false},
   {name = "Liên hoàn đấm", id = 90073013818806, speed = 3, timepos = 0, looped = true, freezeonend = false},
   {name = "Cú Đấm Nhanh", id = 119121668711549, speed = 6, timepos = 2, looped = false, freezeonend = false}
}

local currentTrack = nil
local currentData = nil
local lockMode = false
local humanoid = nil
local animator = nil

local function styleBomText(obj)
	if not obj then
		return nil
	end
	obj.TextColor3 = Color3.fromRGB(255, 242, 242)
	obj.Font = Enum.Font.GothamBlack
	local g = obj:FindFirstChildOfClass("UIGradient") or Instance.new("UIGradient")
	g.Rotation = 0
	g.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	})
	g.Parent = obj
	return g
end

local function makeCorner(obj, radius)
	local c = Instance.new("UICorner")
	c.CornerRadius = UDim.new(0, radius or 10)
	c.Parent = obj
	return c
end

local function makeStroke(obj, thickness, transparency, color)
	local s = Instance.new("UIStroke")
	s.Thickness = thickness or 1
	s.Transparency = transparency or 0
	s.Color = color or Color3.fromRGB(255, 0, 0)
	s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
	s.LineJoinMode = Enum.LineJoinMode.Round
	s.Parent = obj
	return s
end

local function makeGradient(obj, sequence, rotation)
	local g = Instance.new("UIGradient")
	g.Color = sequence
	g.Rotation = rotation or 0
	g.Parent = obj
	return g
end

local function getChar()
	local char = player.Character or player.CharacterAdded:Wait()
	local hum = char:FindFirstChildOfClass("Humanoid")
	local animator = hum and hum:FindFirstChildOfClass("Animator")
	if hum and not animator then
		animator = Instance.new("Animator")
		animator.Parent = hum
	end
	return char, hum, animator
end

local function makeR15Preview(animId)
	local preview = Instance.new("ViewportFrame")
	preview.Size = UDim2.new(0, 30, 0, 30)
	preview.BackgroundColor3 = Color3.fromRGB(120, 15, 15)
	preview.BackgroundTransparency = 0.1
	preview.BorderSizePixel = 0
	preview.ZIndex = 4
	makeCorner(preview, 8)
	makeStroke(preview, 1, 0.12, Color3.fromRGB(255, 0, 0))

	local world = Instance.new("WorldModel")
	world.Parent = preview

	local camera = Instance.new("Camera")
	camera.Parent = preview
	preview.CurrentCamera = camera

	local ok, model = pcall(function()
		return Players:CreateHumanoidModelFromDescription(Instance.new("HumanoidDescription"), Enum.HumanoidRigType.R15)
	end)

	if ok and model then
		model.Parent = world
		model:PivotTo(CFrame.new(0, 0, 0))

		for _, obj in ipairs(model:GetDescendants()) do
			if obj:IsA("BasePart") then
				obj.Color = Color3.fromRGB(200, 200, 200)
				obj.Material = Enum.Material.Plastic
				obj.Transparency = 0
				obj.CastShadow = false
			end
		end

		local hum = model:FindFirstChildOfClass("Humanoid")
		local animator = hum and hum:FindFirstChildOfClass("Animator")
		if hum and not animator then
			animator = Instance.new("Animator")
			animator.Parent = hum
		end

		local anim = Instance.new("Animation")
		anim.AnimationId = "rbxassetid://" .. tostring(animId)

		if animator then
			local track = animator:LoadAnimation(anim)
			track.Looped = true
			track.Priority = Enum.AnimationPriority.Action4
			track:Play(0)
			task.defer(function()
				task.wait(0.05)
				pcall(function()
					track.TimePosition = 1
					track:AdjustSpeed(0)
				end)
			end)
		end

		camera.CFrame = CFrame.new(Vector3.new(0, 1.6, 5), Vector3.new(0, 1.4, 0))
		task.delay(0.2, function()
			pcall(function()
				anim:Destroy()
			end)
		end)
	end

	return preview
end

local function setupUI()
	local open = Instance.new("TextButton")
	open.Size = UDim2.new(0, 46, 0, 46)
	open.Position = UDim2.new(0.5, -23, 0.2, 0)
	open.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
	open.BackgroundTransparency = 0.02
	open.BorderSizePixel = 0
	open.Text = "Anim"
	open.Font = Enum.Font.GothamBlack
	open.TextSize = 14
	open.TextColor3 = Color3.fromRGB(255, 242, 242)
	open.Active = true
	open.Draggable = true
	open.AutoButtonColor = false
	open.Selectable = false
	open.ZIndex = 100
	open.Parent = gui
	makeCorner(open, 6)
	makeStroke(open, 1.4, 0.12, Color3.fromRGB(255, 0, 0))
	local openGrad = makeGradient(open, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
		ColorSequenceKeypoint.new(0.18, Color3.fromRGB(75, 0, 0)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
		ColorSequenceKeypoint.new(0.82, Color3.fromRGB(75, 0, 0)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
	}), 25)
	openGrad.Transparency = NumberSequence.new({
		NumberSequenceKeypoint.new(0, 0.08),
		NumberSequenceKeypoint.new(1, 0.03)
	})
	local openTextGrad = styleBomText(open)

	local openGlow = Instance.new("ImageLabel")
	openGlow.BackgroundTransparency = 1
	openGlow.Size = UDim2.new(1, 18, 1, 18)
	openGlow.Position = UDim2.new(0, -9, 0, -9)
	openGlow.Image = "rbxassetid://5028857084"
	openGlow.ImageColor3 = Color3.fromRGB(255, 0, 0)
	openGlow.ImageTransparency = 0.92
	openGlow.ScaleType = Enum.ScaleType.Slice
	openGlow.SliceCenter = Rect.new(24, 24, 276, 276)
	openGlow.ZIndex = 99
	openGlow.Parent = open

local main = Instance.new("Frame")
	main.Size = UDim2.new(0, 304, 0, 246)
	main.Position = UDim2.new(0.5, -152, 0.55, -123)
	main.BackgroundColor3 = Color3.fromRGB(16, 16, 18)
	main.BackgroundTransparency = 0.03
	main.BorderSizePixel = 0
	main.Active = true
	main.Draggable = true
	main.Visible = false
	main.ClipsDescendants = true
	main.Parent = gui
	makeCorner(main, 12)
	makeStroke(main, 1.45, 0.12, Color3.fromRGB(255, 0, 0))
	local mainGrad = makeGradient(main, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
		ColorSequenceKeypoint.new(0.18, Color3.fromRGB(75, 0, 0)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
		ColorSequenceKeypoint.new(0.82, Color3.fromRGB(75, 0, 0)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
	}), 22)
	mainGrad.Transparency = NumberSequence.new({
		NumberSequenceKeypoint.new(0, 0.08),
		NumberSequenceKeypoint.new(1, 0.03)
	})

	local glow = Instance.new("ImageLabel")
	glow.BackgroundTransparency = 1
	glow.Size = UDim2.new(1, 30, 1, 30)
	glow.Position = UDim2.new(0, -15, 0, -15)
	glow.Image = "rbxassetid://5028857084"
	glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
	glow.ImageTransparency = 0.92
	glow.ScaleType = Enum.ScaleType.Slice
	glow.SliceCenter = Rect.new(24, 24, 276, 276)
	glow.ZIndex = 0
	glow.Parent = main

	local title = Instance.new("TextLabel")
	title.Size = UDim2.new(1, -100, 0, 18)
	title.Position = UDim2.new(0, 9, 0, 5)
	title.BackgroundTransparency = 1
	title.Text = "Biểu cảm"
	title.TextXAlignment = Enum.TextXAlignment.Left
	title.TextSize = 14
	title.ZIndex = 4
	title.Parent = main
	local titleGrad = styleBomText(title)

	local close = Instance.new("TextButton")
	close.Size = UDim2.new(0, 22, 0, 22)
	close.Position = UDim2.new(1, -28, 0, 4)
	close.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
	close.BackgroundTransparency = 0.02
	close.BorderSizePixel = 0
	close.Text = "×"
	close.Font = Enum.Font.GothamBlack
	close.TextSize = 14
	close.TextColor3 = Color3.fromRGB(255, 242, 242)
	close.AutoButtonColor = false
	close.ZIndex = 4
	close.Parent = main
	makeCorner(close, 7)
	makeStroke(close, 1, 0.12, Color3.fromRGB(255, 0, 0))
	local closeGrad = makeGradient(close, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	}), 0)
	local closeTextGrad = styleBomText(close)

	local offBtn = Instance.new("TextButton")
	offBtn.Size = UDim2.new(0, 36, 0, 22)
	offBtn.Position = UDim2.new(1, -70, 0, 4)
	offBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
	offBtn.BackgroundTransparency = 0.02
	offBtn.BorderSizePixel = 0
	offBtn.Text = "Tắt"
	offBtn.Font = Enum.Font.GothamBlack
	offBtn.TextSize = 12
	offBtn.TextColor3 = Color3.fromRGB(255, 242, 242)
	offBtn.AutoButtonColor = false
	offBtn.ZIndex = 4
	offBtn.Parent = main
	makeCorner(offBtn, 7)
	makeStroke(offBtn, 1, 0.12, Color3.fromRGB(255, 0, 0))
	local offGrad = makeGradient(offBtn, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
	}), 0)
	local offTextGrad = styleBomText(offBtn)

	local line = Instance.new("Frame")
	line.Size = UDim2.new(1, -16, 0, 1)
	line.Position = UDim2.new(0, 8, 0, 28)
	line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
	line.BackgroundTransparency = 0.68
	line.BorderSizePixel = 0
	line.ZIndex = 2
	line.Parent = main
	local lineGrad = makeGradient(line, ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 90, 90)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
	}), 0)

	local scroll = Instance.new("ScrollingFrame")
	scroll.Size = UDim2.new(1, -12, 1, -36)
	scroll.Position = UDim2.new(0, 6, 0, 32)
	scroll.BackgroundTransparency = 1
	scroll.BorderSizePixel = 0
	scroll.ScrollBarThickness = 5
	scroll.ScrollBarImageColor3 = Color3.fromRGB(255, 0, 0)
	scroll.CanvasSize = UDim2.new(0, 0, 0, 0)
	scroll.ZIndex = 3
	scroll.Parent = main

	local pad = Instance.new("UIPadding")
	pad.PaddingTop = UDim.new(0, 2)
	pad.PaddingBottom = UDim.new(0, 6)
	pad.PaddingLeft = UDim.new(0, 2)
	pad.PaddingRight = UDim.new(0, 2)
	pad.Parent = scroll

	local layout = Instance.new("UIListLayout")
	layout.Padding = UDim.new(0, 6)
	layout.SortOrder = Enum.SortOrder.LayoutOrder
	layout.FillDirection = Enum.FillDirection.Vertical
	layout.HorizontalAlignment = Enum.HorizontalAlignment.Left
	layout.VerticalAlignment = Enum.VerticalAlignment.Top
	layout.Parent = scroll

	local rows = {}

	local function setupHumanoid()
		local _, hum, ani = getChar()
		humanoid = hum
		animator = ani
	end

	setupHumanoid()

	player.CharacterAdded:Connect(function()
		task.wait(1)
		setupHumanoid()
	end)

	local function stopAnim()
		if currentTrack then
			pcall(function()
				currentTrack:Stop()
			end)
			pcall(function()
				currentTrack:Destroy()
			end)
			currentTrack = nil
		end
	end

	local function playAnim(data)
		currentData = data

		if not animator then
			setupHumanoid()
		end
		if not animator then
			return
		end

		stopAnim()

		local anim = Instance.new("Animation")
		anim.AnimationId = "rbxassetid://" .. tostring(data.id)

		local track = animator:LoadAnimation(anim)
		track.Looped = data.looped
		track.Priority = Enum.AnimationPriority.Action4
		currentTrack = track

		track:Play()
		track:AdjustSpeed(data.speed)

		if data.timepos and data.timepos > 0 then
			track.TimePosition = data.timepos
		end

if data.name == "Cú Đấm Nhanh" then
	task.spawn(function()
		while currentTrack == track and track.IsPlaying do
			if track.TimePosition >= 3.5 then
				track.TimePosition = 2
			end
			RunService.Heartbeat:Wait()
		end
	end)
end

		if data.freezeonend then
			track.Stopped:Connect(function()
				pcall(function()
					track:AdjustSpeed(0)
				end)
			end)
		end

		task.delay(0.2, function()
			pcall(function()
				anim:Destroy()
			end)
		end)
	end

	local function clearRows()
		for _, child in ipairs(rows) do
			if child and child.Parent then
				child:Destroy()
			end
		end
		table.clear(rows)
	end

	local function createRow(data)
		local row = Instance.new("TextButton")
		row.Size = UDim2.new(1, -4, 0, 38)
		row.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
		row.BackgroundTransparency = 0.02
		row.BorderSizePixel = 0
		row.AutoButtonColor = false
		row.Text = ""
		row.ZIndex = 4
		row.Parent = scroll
		makeCorner(row, 8)
		makeStroke(row, 1, 0.14, Color3.fromRGB(255, 0, 0))
		makeGradient(row, ColorSequence.new({
			ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
			ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
			ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
		}), 90)

		local preview = makeR15Preview(data.id)
		preview.Size = UDim2.new(0, 30, 0, 30)
		preview.Position = UDim2.new(0, 4, 0.5, -15)
		preview.Parent = row

		local lbl = Instance.new("TextLabel")
		lbl.BackgroundTransparency = 1
		lbl.Position = UDim2.new(0, 40, 0, 0)
		lbl.Size = UDim2.new(1, -46, 1, 0)
		lbl.Text = data.name
		lbl.TextWrapped = false
		lbl.TextTruncate = Enum.TextTruncate.None
		lbl.TextXAlignment = Enum.TextXAlignment.Left
		lbl.TextYAlignment = Enum.TextYAlignment.Center
		lbl.TextSize = 13
		lbl.ZIndex = 5
		lbl.Parent = row
		styleBomText(lbl)

		row.MouseEnter:Connect(function()
			TweenService:Create(row, TweenInfo.new(0.12), {
				BackgroundColor3 = Color3.fromRGB(90, 0, 0)
			}):Play()
		end)

		row.MouseLeave:Connect(function()
			TweenService:Create(row, TweenInfo.new(0.12), {
				BackgroundColor3 = Color3.fromRGB(68, 0, 0)
			}):Play()
		end)

		row.Activated:Connect(function()
			playAnim(data)
		end)

		table.insert(rows, row)
	end

	local function layoutRows()
		clearRows()

		local y = 0
		local rowHeight = 38
		local gap = 6

		for _, data in ipairs(animations) do
			createRow(data)
			local row = rows[#rows]
			row.Size = UDim2.new(1, -4, 0, rowHeight)
			row.Position = UDim2.new(0, 0, 0, y)
			y = y + rowHeight + gap
		end

		scroll.CanvasSize = UDim2.new(0, 0, 0, y)
	end

	scroll:GetPropertyChangedSignal("AbsoluteSize"):Connect(function()
		task.defer(layoutRows)
	end)

	task.defer(layoutRows)

	local opened = false

	open.MouseButton1Click:Connect(function()
		opened = not opened
		main.Visible = opened
	end)

	close.MouseButton1Click:Connect(function()
		opened = false
		main.Visible = false
	end)

	offBtn.MouseButton1Click:Connect(function()
		lockMode = not lockMode
		offBtn.Text = lockMode and "Bật" or "Tắt"

		if lockMode and currentData and (not currentTrack or not currentTrack.IsPlaying) then
			playAnim(currentData)
		end
	end)

	RunService.Heartbeat:Connect(function()
		if not currentTrack then
			return
		end

		local _, hum = getChar()
		if not hum then
			return
		end

		if lockMode then
			if not currentTrack.IsPlaying and currentData then
				playAnim(currentData)
			end
		else
			if hum.MoveDirection.Magnitude > 0.01 and currentTrack.IsPlaying then
				stopAnim()
			end
		end
	end)

	task.spawn(function()
		while gui.Parent do
			task.wait(0.05)
			local r = (tick() * 25) % 360
			titleGrad.Rotation = r
			closeTextGrad.Rotation = r
			offTextGrad.Rotation = r
			mainGrad.Rotation = (tick() * 12) % 360
			lineGrad.Rotation = (tick() * 20) % 360
			openTextGrad.Rotation = r
			openGrad.Rotation = (tick() * 18) % 360
			glow.ImageTransparency = 0.92 - (math.sin(tick() * 2) * 0.02)
			openGlow.ImageTransparency = 0.92 - (math.sin(tick() * 2) * 0.02)
		end
	end)
end

setupUI()

]]},
}},

{Text = {vn = "Máy Chủ", en = "Sever"}, Scripts = {

{Text = {vn = "Chuyển Server Khác", en = "Change Server"}, Script = [[

local HttpService = game:GetService("HttpService")
local TeleportService = game:GetService("TeleportService")
local Players = game:GetService("Players")

local LocalPlayer = Players.LocalPlayer
local PlaceId = game.PlaceId
local CurrentJob = game.JobId

local servers = {}
local cursor = ""

for _ = 1,5 do
	local url = "https://games.roblox.com/v1/games/"..PlaceId.."/servers/Public?sortOrder=Asc&limit=100"
	if cursor ~= "" then
		url = url.."&cursor="..cursor
	end

	local ok,res = pcall(function()
		return HttpService:JSONDecode(game:HttpGet(url))
	end)

	if not ok or not res then
		break
	end

	for _,v in ipairs(res.data or {}) do
		if v.id ~= CurrentJob and v.playing < v.maxPlayers and v.playing > 0 then
			table.insert(servers,v.id)
		end
	end

	cursor = res.nextPageCursor
	if not cursor then
		break
	end
end

for i = #servers,2,-1 do
	local j = math.random(i)
	servers[i],servers[j] = servers[j],servers[i]
end

for _,jobId in ipairs(servers) do
	local ok = pcall(function()
		TeleportService:TeleportToPlaceInstance(PlaceId,jobId,LocalPlayer)
	end)
	if ok then
		break
	end
	task.wait(0.2)
end

]]},

{Text = {vn = "Tham Gia Lại Máy Chủ", en = "Rejoin Server"}, Script = [[

local TeleportService = game:GetService("TeleportService")
local Players = game:GetService("Players")

local LocalPlayer = Players.LocalPlayer

local ok = pcall(function()
	TeleportService:TeleportToPlaceInstance(
		game.PlaceId,
		game.JobId,
		LocalPlayer
	)
end)

if not ok then
	pcall(function()
		TeleportService:Teleport(
			game.PlaceId,
			LocalPlayer
		)
	end)
end

]]},

{Text = {vn = "Tìm Máy Chủ Ít Người", en = "Find Low Player Server"}, Script = [[

local HttpService = game:GetService("HttpService")
local TeleportService = game:GetService("TeleportService")
local Players = game:GetService("Players")

local player = Players.LocalPlayer
local placeId = game.PlaceId
local currentJob = game.JobId

local servers = {}
local cursor

repeat
	local url = "https://games.roblox.com/v1/games/"..placeId.."/servers/Public?sortOrder=Asc&limit=100"

	if cursor then
		url = url.."&cursor="..cursor
	end

	local ok,data = pcall(function()
		return HttpService:JSONDecode(game:HttpGet(url))
	end)

	if not ok then
		break
	end

	for _,v in ipairs(data.data or {}) do
		if v.id ~= currentJob and v.playing < v.maxPlayers then
			table.insert(servers,v.id)
		end
	end

	cursor = data.nextPageCursor
until not cursor or #servers >= 500

for i = #servers,2,-1 do
	local j = math.random(i)
	servers[i],servers[j] = servers[j],servers[i]
end

for _,jobId in ipairs(servers) do
	local ok = pcall(function()
		TeleportService:TeleportToPlaceInstance(placeId,jobId,player)
	end)

	if ok then
		break
	end

	task.wait(0.2)
end

]]},
{Text = {vn = "Tìm Máy Chủ Nhiều Người", en = "Find A Multiplayer Server"}, Script = [[

local HttpService = game:GetService("HttpService")
local TeleportService = game:GetService("TeleportService")
local Players = game:GetService("Players")

local player = Players.LocalPlayer
local placeId = game.PlaceId
local currentJob = game.JobId

local servers = {}
local cursor

repeat
	local url = "https://games.roblox.com/v1/games/" .. placeId .. "/servers/Public?sortOrder=Desc&limit=100"

	if cursor then
		url = url .. "&cursor=" .. cursor
	end

	local ok, data = pcall(function()
		return HttpService:JSONDecode(game:HttpGet(url))
	end)

	if not ok or not data then
		break
	end

	for _, server in ipairs(data.data or {}) do
		local free = server.maxPlayers - server.playing

		if server.id ~= currentJob and free >= 1 and free <= 3 then
			table.insert(servers, {
				id = server.id,
				free = free,
				playing = server.playing
			})
		end
	end

	cursor = data.nextPageCursor
until not cursor or #servers >= 500

table.sort(servers, function(a, b)
	if a.free == b.free then
		return a.playing > b.playing
	end
	return a.free < b.free
end)

for _, server in ipairs(servers) do
	local ok = pcall(function()
		TeleportService:TeleportToPlaceInstance(placeId, server.id, player)
	end)

	if ok then
		break
	end

	task.wait(0.2)
end

]]},
}},
{Text = {vn = "Khác", en = "Other"}, Scripts = {

{Text = {vn = "Chỉnh Sửa(Client)", en = "Edit (Client)"}, Script = [[

local Players = game:GetService("Players")
local TweenService = game:GetService("TweenService")
local StarterGui = game:GetService("StarterGui")

local player = Players.LocalPlayer
local playerGui = player:WaitForChild("PlayerGui")

pcall(function()
local old = playerGui:FindFirstChild("Bom2devEditor")
if old then
old:Destroy()
end
end)

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devEditor"
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.Parent = playerGui

local function corner(obj, r)
local c = Instance.new("UICorner")
c.CornerRadius = UDim.new(0, r or 12)
c.Parent = obj
return c
end

local function stroke(obj, thick, trans, color)
local s = Instance.new("UIStroke")
s.Thickness = thick or 1
s.Transparency = trans or 0
s.Color = color or Color3.fromRGB(255, 0, 0)
s.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
s.LineJoinMode = Enum.LineJoinMode.Round
s.Parent = obj
return s
end

local function gradient(obj, seq, rot)
local g = Instance.new("UIGradient")
g.Color = seq
g.Rotation = rot or 0
g.Parent = obj
return g
end

local function styleText(obj)
obj.TextColor3 = Color3.fromRGB(255, 242, 242)
obj.Font = Enum.Font.GothamBlack
local g = Instance.new("UIGradient")
g.Parent = obj
g.Rotation = 0
g.Color = ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 10, 10)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
})
return g
end

local main = Instance.new("Frame")
main.Parent = gui
main.Size = UDim2.new(0, 180, 0, 80)
main.Position = UDim2.new(0.06, 0, 0.45, 0)
main.BackgroundColor3 = Color3.fromRGB(12, 12, 18)
main.BackgroundTransparency = 0.04
main.BorderSizePixel = 0
main.Active = true
main.Draggable = true

corner(main, 12)
stroke(main, 2, 0.1, Color3.fromRGB(255, 0, 0))

local mainGrad = gradient(main, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.2, Color3.fromRGB(78, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(24, 24, 28)),
ColorSequenceKeypoint.new(0.8, Color3.fromRGB(78, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 20)
mainGrad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.08),
NumberSequenceKeypoint.new(1, 0.03)
})

local glow = Instance.new("ImageLabel")
glow.Parent = main
glow.BackgroundTransparency = 1
glow.Size = UDim2.new(1, 34, 1, 34)
glow.Position = UDim2.new(0, -17, 0, -17)
glow.Image = "rbxassetid://5028857084"
glow.ImageColor3 = Color3.fromRGB(255, 0, 0)
glow.ImageTransparency = 0.9
glow.ScaleType = Enum.ScaleType.Slice
glow.SliceCenter = Rect.new(24, 24, 276, 276)

local line = Instance.new("Frame")
line.Parent = main
line.Size = UDim2.new(1, -16, 0, 1)
line.Position = UDim2.new(0, 8, 0, 62)
line.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
line.BackgroundTransparency = 0.7
line.BorderSizePixel = 0

local lineGrad = gradient(line, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(255, 120, 120)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)

local title = Instance.new("TextLabel")
title.Parent = main
title.Size = UDim2.new(1, -20, 0, 24)
title.Position = UDim2.new(0, 10, 0, 1)
title.BackgroundTransparency = 1
title.Text = "Chỉnh Sửa"
title.TextColor3 = Color3.fromRGB(255, 255, 255)
title.Font = Enum.Font.GothamBold
title.TextSize = 15
title.TextXAlignment = Enum.TextXAlignment.Left

local titleGrad = styleText(title)

local input1 = Instance.new("TextBox")
input1.Parent = main
input1.Size = UDim2.new(0.63, 0, 0, 24)
input1.Position = UDim2.new(0.03, 0, 0.3, 0)
input1.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
input1.BackgroundTransparency = 0.03
input1.BorderSizePixel = 0
input1.PlaceholderText = "Nội dung cần tìm"
input1.PlaceholderColor3 = Color3.fromRGB(180, 180, 180)
input1.Text = ""
input1.ClearTextOnFocus = false
input1.Font = Enum.Font.GothamBlack
input1.TextSize = 12
input1.TextColor3 = Color3.fromRGB(255, 255, 255)
input1.TextXAlignment = Enum.TextXAlignment.Center

corner(input1, 8)
stroke(input1, 1, 0.1, Color3.fromRGB(255, 0, 0))
local input1Grad = gradient(input1, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)
input1Grad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.05),
NumberSequenceKeypoint.new(1, 0.02)
})
local input1TextGrad = styleText(input1)

local input2 = Instance.new("TextBox")
input2.Parent = main
input2.Size = UDim2.new(0.63, 0, 0, 24)
input2.Position = UDim2.new(0.03, 0, 0.65, 0)
input2.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
input2.BackgroundTransparency = 0.03
input2.BorderSizePixel = 0
input2.PlaceholderText = "Nội dung thay thế"
input2.PlaceholderColor3 = Color3.fromRGB(180, 180, 180)
input2.Text = ""
input2.ClearTextOnFocus = false
input2.Font = Enum.Font.GothamBlack
input2.TextSize = 12
input2.TextColor3 = Color3.fromRGB(255, 255, 255)
input2.TextXAlignment = Enum.TextXAlignment.Center

corner(input2, 8)
stroke(input2, 1, 0.1, Color3.fromRGB(255, 0, 0))
local input2Grad = gradient(input2, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 0, 0)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(70, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 0, 0))
}), 0)
input2Grad.Transparency = NumberSequence.new({
NumberSequenceKeypoint.new(0, 0.05),
NumberSequenceKeypoint.new(1, 0.02)
})
local input2TextGrad = styleText(input2)

local findBtn = Instance.new("TextButton")
findBtn.Parent = main
findBtn.Size = UDim2.new(0.28, 0, 0, 24)
findBtn.Position = UDim2.new(0.69, 0, 0.3, 0)
findBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
findBtn.BackgroundTransparency = 0.02
findBtn.BorderSizePixel = 0
findBtn.Text = "Tìm"
findBtn.TextColor3 = Color3.fromRGB(255, 242, 242)
findBtn.Font = Enum.Font.GothamBlack
findBtn.TextSize = 12
findBtn.AutoButtonColor = false

corner(findBtn, 8)
stroke(findBtn, 1, 0.1, Color3.fromRGB(255, 0, 0))
local findGrad = gradient(findBtn, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)
local findTextGrad = styleText(findBtn)

local changeBtn = Instance.new("TextButton")
changeBtn.Parent = main
changeBtn.Size = UDim2.new(0.28, 0, 0, 24)
changeBtn.Position = UDim2.new(0.69, 0, 0.65, 0)
changeBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
changeBtn.BackgroundTransparency = 0.02
changeBtn.BorderSizePixel = 0
changeBtn.Text = "Đổi"
changeBtn.TextColor3 = Color3.fromRGB(255, 242, 242)
changeBtn.Font = Enum.Font.GothamBlack
changeBtn.TextSize = 12
changeBtn.AutoButtonColor = false

corner(changeBtn, 8)
stroke(changeBtn, 1, 0.1, Color3.fromRGB(255, 0, 0))
local changeGrad = gradient(changeBtn, ColorSequence.new({
ColorSequenceKeypoint.new(0, Color3.fromRGB(255, 255, 255)),
ColorSequenceKeypoint.new(0.5, Color3.fromRGB(120, 0, 0)),
ColorSequenceKeypoint.new(1, Color3.fromRGB(255, 255, 255))
}), 0)
local changeTextGrad = styleText(changeBtn)

local highlighted = nil

local function clearHighlight()
if highlighted and highlighted.Parent then
for _, c in ipairs(highlighted:GetChildren()) do
if c.Name == "Bom2devHighlight" then
pcall(function()
c:Destroy()
end)
end
end
end
highlighted = nil
end

local function trim(s)
if not s then
return ""
end
return tostring(s):match("^%s*(.-)%s*$") or ""
end

local function findMatches(text)
local t = trim(text)
if t == "" then
return {}
end

local results = {}
for _, obj in ipairs(game:GetDescendants()) do
	if obj:IsA("TextLabel") or obj:IsA("TextButton") or obj:IsA("TextBox") then
		local ok, txt = pcall(function()
			return obj.Text
		end)
		if ok and txt ~= nil and trim(txt) == t then
			results[#results + 1] = obj
		end
	end
end
return results

end

local function attachHighlight(obj)
clearHighlight()
if not obj or not obj.Parent then
return
end

local ok = pcall(function()
	local hs = Instance.new("UIStroke")
	hs.Name = "Bom2devHighlight"
	hs.Thickness = 3
	hs.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
	hs.Parent = obj
	highlighted = obj

	task.spawn(function()
			hs.Color = Color3.fromHSV(255, 1, 1)
		pcall(function()
			if hs.Parent then
				hs:Destroy()
			end
		end)
	end)
end)

if not ok then
	clearHighlight()
end

end

findBtn.MouseEnter:Connect(function()
findBtn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

findBtn.MouseLeave:Connect(function()
findBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

changeBtn.MouseEnter:Connect(function()
changeBtn.BackgroundColor3 = Color3.fromRGB(90, 0, 0)
end)

changeBtn.MouseLeave:Connect(function()
changeBtn.BackgroundColor3 = Color3.fromRGB(68, 0, 0)
end)

input1.MouseEnter:Connect(function()
input1.BackgroundColor3 = Color3.fromRGB(30, 30, 40)
end)

input1.MouseLeave:Connect(function()
input1.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
end)

input2.MouseEnter:Connect(function()
input2.BackgroundColor3 = Color3.fromRGB(30, 30, 40)
end)

input2.MouseLeave:Connect(function()
input2.BackgroundColor3 = Color3.fromRGB(22, 22, 30)
end)

findBtn.MouseButton1Click:Connect(function()
clearHighlight()

local key = trim(input1.Text)
if key == "" then
	return
end

local results = findMatches(key)
if #results == 1 then
	attachHighlight(results[1])
elseif #results > 1 then
	attachHighlight(results[1])
end

end)

changeBtn.MouseButton1Click:Connect(function()
if not highlighted or not highlighted.Parent then
return
end

local replacement = input2.Text or ""
pcall(function()
	highlighted.Text = replacement
end)
clearHighlight()

end)

input1.FocusLost:Connect(function()
input1.Text = input1.Text
end)

input2.FocusLost:Connect(function()
input2.Text = input2.Text
end)

task.spawn(function()
while gui.Parent do
task.wait(0.05)
local r = (tick() * 25) % 360
titleGrad.Rotation = r
input1TextGrad.Rotation = r
input2TextGrad.Rotation = r
findTextGrad.Rotation = r
changeTextGrad.Rotation = r
mainGrad.Rotation = (tick() * 12) % 360
input1Grad.Rotation = (tick() * 16) % 360
input2Grad.Rotation = (tick() * 16) % 360
findGrad.Rotation = (tick() * 18) % 360
changeGrad.Rotation = (tick() * 18) % 360
lineGrad.Rotation = (tick() * 20) % 360
glow.ImageTransparency = 0.9 - (math.sin(tick() * 2) * 0.03)
end
end)

]]},

{Text = {vn = "Màn Hình Chờ", en = "Lock Screen"}, Script = [[
local Players = game:GetService("Players")
local TweenService = game:GetService("TweenService")
local RunService = game:GetService("RunService")
local TextService = game:GetService("TextService")

local player = Players.LocalPlayer
local playerGui = player:WaitForChild("PlayerGui")

local existing = playerGui:FindFirstChild("AutoTypingOverlay")
if existing then
	existing:Destroy()
	return
end

local function safeDestroy(name)
	local g = playerGui:FindFirstChild(name)
	if g then
		g:Destroy()
	end
end

safeDestroy("Bom2dev")

local gui = Instance.new("ScreenGui")
gui.Name = "AutoTypingOverlay"
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.Parent = playerGui

local bg = Instance.new("Frame")
bg.Size = UDim2.new(1, 0, 1, 0)
bg.BackgroundColor3 = Color3.fromRGB(0, 0, 0)
bg.BackgroundTransparency = 0
bg.BorderSizePixel = 0
bg.Parent = gui

local clickCatcher = Instance.new("TextButton")
clickCatcher.Size = UDim2.new(1, 0, 1, 0)
clickCatcher.BackgroundTransparency = 1
clickCatcher.Text = ""
clickCatcher.AutoButtonColor = false
clickCatcher.Parent = bg

local scroll = Instance.new("ScrollingFrame")
scroll.Size = UDim2.new(1, 0, 1, 0)
scroll.BackgroundTransparency = 1
scroll.BorderSizePixel = 0
scroll.ScrollBarThickness = 0
scroll.CanvasSize = UDim2.new(0, 0, 0, 0)
scroll.Parent = bg

local textLabel = Instance.new("TextLabel")
textLabel.BackgroundTransparency = 1
textLabel.Position = UDim2.new(0, 12, 0, 10)
textLabel.Size = UDim2.new(1, -24, 0, 0)
textLabel.Font = Enum.Font.Code
textLabel.TextSize = 20
textLabel.TextColor3 = Color3.fromRGB(255, 0, 0)
textLabel.TextXAlignment = Enum.TextXAlignment.Left
textLabel.TextYAlignment = Enum.TextYAlignment.Top
textLabel.TextWrapped = true
textLabel.RichText = false
textLabel.Text = ""
textLabel.Parent = scroll

local alive = true
local lines = {}
local maxLines = 17

local tags = {
	"html","body","head","main","div","section","article","header","footer","nav","aside","span","template","script","style"
}

local attrs = {
	"class","id","data-node","data-mode","role","aria-label","data-state","data-layer","data-stream","data-shell"
}

local words = {
	"cache","sync","render","decode","stream","vector","shadow","frame","module","kernel","runtime","bridge","packet","layout","state","proxy","node","shell","trace","buffer","index","query","init","target","layer","phase","signal","matrix","pipeline","token","path","resolve","object","segment","cursor","stack","patch","echo","grid","scope","Bom2dev"
}

local snippets = {
	{"<html lang=\"en\">", "</html>"},
	{"<body>", "</body>"},
	{"<head>", "</head>"},
	{"<main>", "</main>"},
	{"<section>", "</section>"},
	{"<article>", "</article>"},
	{"<header>", "</header>"},
	{"<footer>", "</footer>"},
	{"<nav>", "</nav>"},
	{"<aside>", "</aside>"},
	{"<template>", "</template>"},
	{"<script type=\"text/html\">", "</script>"},
	{"<style>", "</style>","</Bom2>"}
}

local function pick(t)
	return t[math.random(1, #t)]
end

local function joinWords(a, b)
	local out = {}
	for i = a, b do
		out[#out + 1] = pick(words)
	end
	return table.concat(out, " ")
end

local function getStamp()
	local now = tick()
	local sec = math.floor(now)
	local ms = math.floor((now - sec) * 100)
	local dt = os.date("*t", sec)
	return string.format("[%02d:%02d:%02d:%02d]", dt.hour, dt.min, dt.sec, ms)
end

local function makeHtmlLine()
	local stamp = getStamp()
	local mode = math.random(1, 8)

	if mode == 1 then
		local t1 = pick(tags)
		local t2 = pick(tags)
		local a1 = pick(attrs)
		return string.format("%s <%s %s=\"%s-%s\"> %s <%s>%s</%s> </%s>", stamp, t1, a1, pick(words), pick(words), joinWords(5, 9), t2, joinWords(2, 4), t2, t1)
	elseif mode == 2 then
		local t = pick(tags)
		local a = pick(attrs)
		return string.format("%s <%s %s=\"%s\" data-layer=\"%s\"> %s </%s>", stamp, t, a, pick(words), pick(words), joinWords(7, 12), t)
	elseif mode == 3 then
		local open = pick(snippets)
		return string.format("%s %s %s %s %s", stamp, open[1], joinWords(6, 10), open[2], pick(words))
	elseif mode == 4 then
		return string.format("%s <div class=\"%s\"> <%s>%s</%s> <%s>%s</%s> </div>", stamp, pick(words), pick(tags), joinWords(3, 6), pick(tags), pick(tags), joinWords(2, 5), pick(tags))
	elseif mode == 5 then
		return string.format("%s <!DOCTYPE html> <html><body><section data-mode=\"%s\">%s</section></body></html>", stamp, pick(words), joinWords(8, 13))
	elseif mode == 6 then
		return string.format("%s <meta charset=\"utf-8\"> <link rel=\"preload\" href=\"/%s/%s\"> <div>%s</div>", stamp, pick(words), pick(words), joinWords(6, 10))
	elseif mode == 7 then
		return string.format("%s <script type=\"text/html\" id=\"%s\"> %s </script>", stamp, pick(words), joinWords(9, 14))
	else
		return string.format("%s <style>.%s{opacity:.%d;transform:translate(%dpx,%dpx)}</style>", stamp, pick(words), math.random(4, 9), math.random(0, 30), math.random(0, 30))
	end
end

local function render()
	textLabel.Text = table.concat(lines, "\n")

	task.defer(function()
		if not gui.Parent then return end
		local size = TextService:GetTextSize(
			textLabel.Text,
			textLabel.TextSize,
			textLabel.Font,
			Vector2.new(math.max(50, scroll.AbsoluteSize.X - 24), 100000)
		)
		textLabel.Size = UDim2.new(1, -24, 0, math.max(20, size.Y + 12))
		scroll.CanvasSize = UDim2.new(0, 0, 0, math.max(scroll.AbsoluteSize.Y, size.Y + 24))
		scroll.CanvasPosition = Vector2.new(0, math.max(0, size.Y - scroll.AbsoluteSize.Y + 24))
	end)
end

local function pushLine(line)
	if #lines >= maxLines then
		table.remove(lines, 1)
	end
	lines[#lines + 1] = line
	render()
end

local clicks = {}

clickCatcher.MouseButton1Click:Connect(function()
	local t = tick()
	clicks[#clicks + 1] = t
	while #clicks > 0 and (t - clicks[1]) > 3 do
		table.remove(clicks, 1)
	end
	if #clicks >= 3 then
		alive = false
		gui:Destroy()
	end
end)

TweenService:Create(bg, TweenInfo.new(0.25, Enum.EasingStyle.Quad, Enum.EasingDirection.Out), {
	BackgroundTransparency = 0
}):Play()

TweenService:Create(textLabel, TweenInfo.new(0.25, Enum.EasingStyle.Quad, Enum.EasingDirection.Out), {
	TextTransparency = 0
}):Play()

task.spawn(function()
	while alive and gui.Parent do
		pushLine(makeHtmlLine())
		task.wait(math.random(5, 20) / 100)
	end
end)
]]},

{Text = {vn = "Tắt Nhạc Nền", en = "Turn Off Music."}, Script = [[
local Players = game.Players
local player = Players.LocalPlayer

local enabled = false
local connections = {}

local function stopLongSounds()
	for _, v in ipairs(game:GetDescendants()) do
		if v:IsA("Sound") then
			if v.TimeLength > 10 then
				v.Playing = false
			end
		end
	end
end

local function hookSound(sound)
	if not sound:IsA("Sound") then return end

	local conn = sound:GetPropertyChangedSignal("Playing"):Connect(function()
		if enabled and sound.TimeLength > 10 and sound.Playing then
			sound.Playing = false
		end
	end)

	table.insert(connections, conn)
end

local function enable()
	enabled = true

	stopLongSounds()

	for _, v in ipairs(game:GetDescendants()) do
		hookSound(v)
	end

	table.insert(connections, game.DescendantAdded:Connect(function(v)
		if enabled then
			hookSound(v)
		end
	end))

	while enabled do
		stopLongSounds()
		task.wait(1)
	end
end

local function disable()
	enabled = false

	for _, c in ipairs(connections) do
		pcall(function() c:Disconnect() end)
	end

	connections = {}
end

_G.ToggleLongSoundBlock = function()
	if enabled then
		disable()
	else
		enable()
	end
end
]]},
{Text = {vn = "OutPut", en = "OutPut"}, Script = [[
local Players = game.Players
local RunService = game.RunService
local TweenService = game.TweenService
local TextService = game.TextService
local LogService = game.LogService

local G = (getgenv and getgenv()) or _G
G.Bom2devOutputNotify = G.Bom2devOutputNotify or { active = false }

if G.Bom2devOutputNotify.active then
	G.Bom2devOutputNotify.active = false
	if G.Bom2devOutputNotify.cleanup then
		pcall(G.Bom2devOutputNotify.cleanup)
	end
	return
end

G.Bom2devOutputNotify.active = true

local player = Players.LocalPlayer
local guiParent = player:WaitForChild("PlayerGui")
local camera = workspace.CurrentCamera or workspace:WaitForChild("Camera")

local old = guiParent:FindFirstChild("Bom2devOutputNotifyGui")
if old then
	old:Destroy()
end

local gui = Instance.new("ScreenGui")
gui.Name = "Bom2devOutputNotifyGui"
gui.IgnoreGuiInset = true
gui.ResetOnSpawn = false
gui.DisplayOrder = 999
gui.Parent = guiParent

local alive = true
local notices = {}
local conns = {}

local topY = 56
local gap = 6
local keepTime = 5
local widthMin = 260
local widthMax = 520

local function colorFor(messageType)
	if messageType == Enum.MessageType.MessageWarning then
		return Color3.fromRGB(255, 80, 80)
	elseif messageType == Enum.MessageType.MessageError then
		return Color3.fromRGB(255, 60, 60)
	else
		return Color3.fromRGB(255, 232, 90)
	end
end

local function relayout()
	local y = topY
	for _, item in ipairs(notices) do
		if item.label and item.label.Parent then
			item.targetY = y
			TweenService:Create(
				item.label,
				TweenInfo.new(0.16, Enum.EasingStyle.Quad, Enum.EasingDirection.Out),
				{ Position = UDim2.new(0.5, 0, 0, y) }
			):Play()
			y += item.height + gap
		end
	end
end

local function removeNotice(item)
	if not item or item.removed then
		return
	end
	item.removed = true

	for i = #notices, 1, -1 do
		if notices[i] == item then
			table.remove(notices, i)
			break
		end
	end

	relayout()

	local label = item.label
	if label and label.Parent then
		local fade = TweenService:Create(
			label,
			TweenInfo.new(0.25, Enum.EasingStyle.Quad, Enum.EasingDirection.In),
			{
				TextTransparency = 1,
				BackgroundTransparency = 1,
				Position = UDim2.new(0.5, 0, 0, (item.targetY or topY) - 10)
			}
		)
		fade:Play()
		fade.Completed:Connect(function()
			if label and label.Parent then
				label:Destroy()
			end
		end)
	end
end

local function addNotice(message, messageType)
	if not alive then
		return
	end

	if not camera then
		camera = workspace.CurrentCamera or workspace:WaitForChild("Camera")
	end

	local text = tostring(message)
	local width = math.clamp(camera.ViewportSize.X - 40, widthMin, widthMax)
	local bounds = TextService:GetTextSize(text, 18, Enum.Font.GothamBold, Vector2.new(width - 24, 1000))
	local height = math.max(0, bounds.Y + 0)

	local label = Instance.new("TextLabel")
	label.Name = "Notice"
	label.Parent = gui
	label.AnchorPoint = Vector2.new(0.5, 0)
	label.Size = UDim2.fromOffset(width, height)
	label.Position = UDim2.new(0.5, 0, 0, topY + 12)
	label.BackgroundColor3 = Color3.fromRGB(18, 18, 24)
	label.BackgroundTransparency = 1
	label.BorderSizePixel = 0
	label.Font = Enum.Font.GothamBold
	label.TextSize = 18
	label.TextWrapped = true
	label.TextXAlignment = Enum.TextXAlignment.Center
	label.TextYAlignment = Enum.TextYAlignment.Center
	label.TextColor3 = colorFor(messageType)
	label.TextTransparency = 1
	label.Text = text

	local item = {
		label = label,
		height = height,
		targetY = topY,
		removed = false
	}

	table.insert(notices, item)
	relayout()

	TweenService:Create(
		label,
		TweenInfo.new(0.18, Enum.EasingStyle.Quad, Enum.EasingDirection.Out),
		{
			BackgroundTransparency = 1,
			TextTransparency = 0
		}
	):Play()

	task.delay(keepTime, function()
		if alive then
			removeNotice(item)
		end
	end)
end

table.insert(conns, LogService.MessageOut:Connect(function(message, messageType)
	if not alive then
		return
	end
	addNotice(message, messageType)
end))

local function cleanup()
	if not alive then
		return
	end
	alive = false

	for _, c in ipairs(conns) do
		pcall(function()
			c:Disconnect()
		end)
	end

	if gui then
		gui:Destroy()
	end

	G.Bom2devOutputNotify.active = false
	G.Bom2devOutputNotify.cleanup = nil
end

G.Bom2devOutputNotify.Notify = addNotice
G.Bom2devOutputNotify.cleanup = cleanup
]]},
{Text = {vn = "Robux +inf(Client)", en = "Robux +inf(Client)"}, Script = [==[
local C=game:GetService("CoreGui")local R=game:GetService("RunService")local S=game:GetService("StarterGui")local F='<font family="rbxasset://LuaPackages/Packages/_Index/BuilderIcons/BuilderIcons/BuilderIcons.json" weight="400">robux</font> '
if getgenv()._rc then pcall(function() getgenv()._rc:Disconnect() end) end
getgenv()._rc=R.Heartbeat:Connect(function() pcall(function() local t=C.FoundationOverlay.SafeAreaFrame.OverlayPortal.SheetContainer.Frame.Sheet.Content.Header.Content.SubContent.ModalHeader.RightSide.RobuxPrice if t and t.Parent then t.RichText=true t.Text=F.."+inf" end end) end) pcall(function() S:SetCore("SendNotification",{Title="Đã nhận!!",Text="+inf robux!",Duration=8}) end)
]==]},
}},
{Text = { vn = "Ngôn Ngữ", en = "Language" }, Scripts = {
{Text = { vn = "Tiếng Việt", en = "Vietnamese" }, Script = [[
_G.changeLanguage("vn")
]]},
{Text = { vn = "Tiếng Anh", en = "English" }, Script = [[
_G.changeLanguage("en")
]]},
}},
}

local allScripts = {}
local function regenerateAllScripts()
	allScripts = {}
	for _, f in ipairs(functions) do
		for _, s in ipairs(f.Scripts) do
			table.insert(allScripts, {Text = s.Text, Script = s.Script, ParentFunc = f.Text})
		end
	end
end
regenerateAllScripts()
local function runScriptEntry(entry)
	if type(entry) == "function" then
		pcall(entry)
		return
	end
	if type(entry) == "string" then
		if loadstring then
			local chunk = loadstring(entry)
			if chunk then
				local ok, ret = pcall(chunk)
				if ok and type(ret) == "function" then
					pcall(ret)
				end
				return
			end
			local wrapper = loadstring("return function()\n" .. entry .. "\nend")
			if wrapper then
				local ok2, f = pcall(wrapper)
				if ok2 and type(f) == "function" then
					pcall(f)
					return
				end
			end
		end
		return
	end
end
local createButtons, buildFuncButtons
createButtons = function(scripts)
	if not ContentRef then return end
	for _, child in ipairs(ContentRef:GetChildren()) do
		if child:IsA("TextButton") or child:IsA("UIStroke") or child:IsA("UICorner") then child:Destroy() end
	end
	local xOffset, yOffset = 0, 0
	local contentWidth = ContentRef.AbsoluteSize.X
	local paddingX, paddingY, spacingX, spacingY = 8, 4, 6, 6
	for _, v in ipairs(scripts) do
		local labelText = getText(v.Text)
		local textSize = TextService:GetTextSize(labelText, 18, Enum.Font.GothamBold, Vector2.new(math.huge, math.huge))
		local btnW = textSize.X + paddingX * 3
		local btnH = textSize.Y + paddingY * 2
		if xOffset + btnW > contentWidth then
			xOffset = 0
			yOffset = yOffset + btnH + spacingY
		end
		local btn = Instance.new("TextButton")
		btn.Size = UDim2.new(0, btnW, 0, btnH)
		btn.Position = UDim2.new(0, xOffset, 0, yOffset)
		btn.BackgroundColor3 = Color3.fromRGB(20, 20, 30)
		btn.BorderSizePixel = 0
		btn.Font = Enum.Font.GothamBold
		btn.TextSize = 18
		btn.Text = labelText
		btn.TextColor3 = Color3.fromRGB(255, 0, 0)
		btn.Parent = ContentRef
		Instance.new("UICorner", btn).CornerRadius = UDim.new(0, 8)
		local stroke = Instance.new("UIStroke", btn)
		stroke.Thickness = 2
		stroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
		task.spawn(function()
			local h = 0
			while btn.Parent do
				h = (h + 0.005) % 1
				stroke.Color = Color3.fromHSV(h, 1, 1)
				task.wait(0.02)
			end
		end)
		btn.Activated:Connect(function()
			pcall(function()
				if v and v.Script then
					runScriptEntry(v.Script)
				end
			end)
		end)
		xOffset = xOffset + btnW + spacingX
	end
	ContentRef.CanvasSize = UDim2.new(0, 0, 0, yOffset + 50)
end
buildFuncButtons = function()
	if not funcFrameRef then return end
	for _, child in ipairs(funcFrameRef:GetChildren()) do
		if child:IsA("TextButton") or child:IsA("UIStroke") or child:IsA("UICorner") then child:Destroy() end
	end
	for _, f in ipairs(functions) do
		local btn = Instance.new("TextButton")
		btn.Size = UDim2.new(1, 0, 0, 30)
		btn.BackgroundColor3 = Color3.fromRGB(25, 25, 35)
		btn.BorderSizePixel = 0
		btn.Font = Enum.Font.GothamBold
		btn.TextScaled = true
		btn.Text = getText(f.Text)
		btn.TextColor3 = Color3.fromRGB(255, 0, 0)
		btn.Parent = funcFrameRef
		Instance.new("UICorner", btn).CornerRadius = UDim.new(0, 6)
		btn.MouseButton1Click:Connect(function()
			if searchBoxRef then searchBoxRef.Text = "" end
			local scripts = f.Scripts or {}
			createButtons(scripts)
		end)
	end
end
local function filterScripts(query)
	if not query or query == "" then return {} end
	query = string.lower(query)
	local out = {}
	for _, v in ipairs(allScripts) do
		local txt = string.lower(getText(v.Text))
		if string.find(txt, query, 1, true) then
			table.insert(out, {Text = v.Text, Script = v.Script})
		end
	end
	return out
end
changeLanguage = function(lang)
	currentLanguage = lang or currentLanguage
	saveLang({lang = currentLanguage})
	if searchBoxRef then
		searchBoxRef.PlaceholderText = (currentLanguage == "vn") and "Tìm Script" or "Search Script"
	end
	regenerateAllScripts()
	buildFuncButtons()
	if functions[1] and functions[1].Scripts and ContentRef then
		createButtons(functions[1].Scripts)
	end
end
_G.changeLanguage = changeLanguage
local function startBom2devGUI()
	safeDestroy("Bom2devHubV9.4")
	local gui2 = Instance.new("ScreenGui")
	gui2.Name = "Bom2devHubV9.4"
	gui2.Parent = playerGui
	gui2.IgnoreGuiInset = true
	gui2.ResetOnSpawn = false
	guiRef = gui2
	local toggle = Instance.new("ImageButton")
	toggle.Size = UDim2.new(0, 50, 0, 50)
	toggle.Position = UDim2.new(0, 10, 0.5, -18)
	toggle.AnchorPoint = Vector2.new(0, 0.5)
	toggle.BackgroundTransparency = 1
	toggle.Image = "rbxassetid://113709284934365"
	toggle.Parent = gui2
	toggle.Active = true
	toggle.Draggable = true
	Instance.new("UICorner", toggle).CornerRadius = UDim.new(0, 14)
	local toggleGlow = Instance.new("UIStroke", toggle)
	toggleGlow.Thickness = 2
	toggleGlow.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
	toggleGlow.Transparency = 0.3
	task.spawn(function()
		while gui2.Parent do
			for h = 0, 1, 0.008 do
				if not gui2.Parent then
					break
				end
				toggleGlow.Color = Color3.fromHSV(h, 0.8, 1)
				task.wait(0.05)
			end
		end
	end)
	local frame = Instance.new("Frame")
	frame.Size = UDim2.new(0, 420, 0, 260)
	frame.Position = UDim2.new(0.5, -210, 0.5, -130)
	frame.BackgroundColor3 = Color3.fromRGB(20, 20, 25)
	frame.BackgroundTransparency = 0.08
	frame.BorderSizePixel = 0
	frame.Visible = false
	frame.Parent = gui2
	Instance.new("UICorner", frame).CornerRadius = UDim.new(0, 14)
	local glow = Instance.new("UIStroke", frame)
	glow.Thickness = 2.5
	glow.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
	glow.Transparency = 0.2
	task.spawn(function()
		while gui2.Parent do
			for h = 0, 1, 0.008 do
				glow.Color = Color3.fromHSV(h, 0.85, 1)
				task.wait(0.02)
			end
		end
	end)
	local header = Instance.new("Frame", frame)
	header.Size = UDim2.new(1, 0, 0, 40)
	header.BackgroundColor3 = Color3.fromRGB(0, 255, 200)
	header.BackgroundTransparency = 0.75
	header.BorderSizePixel = 0
	Instance.new("UICorner", header).CornerRadius = UDim.new(0, 14)
	local title = Instance.new("TextLabel", header)
	title.Text = "Bom2dev Hub"
	title.Font = Enum.Font.GothamBold
	title.TextScaled = true
	title.TextColor3 = Color3.fromRGB(255, 0, 0)
	title.BackgroundTransparency = 1
	title.Position = UDim2.new(0, 40, 0, 0)
	title.Size = UDim2.new(1, -280, 1, 0)
	title.TextXAlignment = Enum.TextXAlignment.Left
	titleRef = title
	local avatar = Instance.new("ImageLabel", header)
	avatar.Size = UDim2.new(0, 30, 0, 30)
	avatar.Position = UDim2.new(0, 5, 0, 5)
	avatar.BackgroundTransparency = 1
	avatar.Image = "rbxthumb://type=AvatarHeadShot&id=" .. player.UserId .. "&w=150&h=150"
	Instance.new("UICorner", avatar).CornerRadius = UDim.new(0, 15)
	local close = Instance.new("TextButton", header)
	close.Text = "×"
	close.Font = Enum.Font.GothamBold
	close.TextSize = 22
	close.TextColor3 = Color3.fromRGB(0, 255, 200)
	close.BackgroundTransparency = 1
	close.Size = UDim2.new(0, 30, 1, 0)
	close.Position = UDim2.new(1, -35, 0, 0)
	close.MouseEnter:Connect(function()
		TweenService:Create(close, TweenInfo.new(0.2), {TextColor3 = Color3.fromRGB(255, 100, 100)}):Play()
	end)
	close.MouseLeave:Connect(function()
		TweenService:Create(close, TweenInfo.new(0.2), {TextColor3 = Color3.fromRGB(0, 255, 200)}):Play()
	end)
	funcFrameRef = Instance.new("ScrollingFrame", frame)
	funcFrameRef.Size = UDim2.new(0, 70, 1, -50)
	funcFrameRef.Position = UDim2.new(0, 5, 0, 45)
	funcFrameRef.BackgroundTransparency = 1
	funcFrameRef.ScrollBarThickness = 4
	funcFrameRef.CanvasSize = UDim2.new(0, 0, 0, 0)
	local funcLayout = Instance.new("UIListLayout", funcFrameRef)
	funcLayout.Padding = UDim.new(0, 5)
	funcLayout.SortOrder = Enum.SortOrder.LayoutOrder
	searchBoxRef = Instance.new("TextBox", header)
	searchBoxRef.Size = UDim2.new(0, 200, 0, 24)
	searchBoxRef.Position = UDim2.new(1, -245, 0, 8)
	searchBoxRef.BackgroundColor3 = Color3.fromRGB(18, 18, 22)
	searchBoxRef.BackgroundTransparency = 0.5
	searchBoxRef.PlaceholderText = (currentLanguage == "vn") and "Tìm Script" or "Search Script"
	searchBoxRef.Text = ""
	searchBoxRef.ClearTextOnFocus = false
	searchBoxRef.Font = Enum.Font.Gotham
	searchBoxRef.TextSize = 14
	searchBoxRef.TextColor3 = Color3.fromRGB(200,200,200)
	searchBoxRef.ZIndex = 2
	Instance.new("UICorner", searchBoxRef).CornerRadius = UDim.new(0, 6)
	ContentRef = Instance.new("ScrollingFrame", frame)
	ContentRef.Size = UDim2.new(1, -85, 1, -50)
	ContentRef.Position = UDim2.new(0, 80, 0, 45)
	ContentRef.BackgroundTransparency = 1
	ContentRef.ScrollBarThickness = 6
	ContentRef.CanvasSize = UDim2.new(0, 0, 0, 0)
	ContentRef:GetPropertyChangedSignal("AbsoluteSize"):Connect(function()
		if functions[1] and functions[1].Scripts then
			createButtons(functions[1].Scripts)
		end
	end)
	funcLayout:GetPropertyChangedSignal("AbsoluteContentSize"):Connect(function()
		funcFrameRef.CanvasSize = UDim2.new(0, 0, 0, funcLayout.AbsoluteContentSize.Y + 10)
	end)
	searchBoxRef:GetPropertyChangedSignal("Text"):Connect(function()
		local q = searchBoxRef.Text or ""
		if q == "" then
			if functions[1] and functions[1].Scripts then
				createButtons(functions[1].Scripts)
			end
		else
			local matches = filterScripts(q)
			createButtons(matches)
		end
	end)
	buildFuncButtons()
	if functions[1] and functions[1].Scripts then
		createButtons(functions[1].Scripts)
	end
	local function showFrame()
		frame.Visible = true
		frame.Size = UDim2.new(0, 0, 0, 0)
		frame.Position = UDim2.new(0.5, 0, 0.5, 0)
		TweenService:Create(frame, TweenInfo.new(0.35, Enum.EasingStyle.Back, Enum.EasingDirection.Out), {
			Size = UDim2.new(0, 420, 0, 260),
			Position = UDim2.new(0.5, -210, 0.5, -130),
		}):Play()
	end
	local function hideFrame()
		local tween = TweenService:Create(frame, TweenInfo.new(0.25, Enum.EasingStyle.Quad, Enum.EasingDirection.In), {
			Size = UDim2.new(0, 0, 0, 0),
			Position = UDim2.new(0.5, 0, 0.5, 0),
		})
		tween:Play()
		tween.Completed:Connect(function()
			frame.Visible = false
		end)
	end
	local function openOrClose()
		if not frame.Visible then
			showFrame()
		else
			hideFrame()
		end
	end

	local UserInputService = game:GetService("UserInputService")
	local isDragging = false
	local dragStartPos = nil
	local startPos = nil
	local CLICK_THRESHOLD = 6

	toggle.InputBegan:Connect(function(input)
		if input.UserInputType == Enum.UserInputType.MouseButton1 or input.UserInputType == Enum.UserInputType.Touch then
			dragStartPos = input.Position
			startPos = toggle.Position
			isDragging = false

			local conn
			conn = input.Changed:Connect(function()
				if input.UserInputState == Enum.UserInputState.End then
					conn:Disconnect()
					if not isDragging then
						openOrClose()
					end
					dragStartPos = nil
					startPos = nil
				end
			end)
		end
	end)

	toggle.InputChanged:Connect(function(input)
		if not dragStartPos then return end
		if input.UserInputType == Enum.UserInputType.MouseMovement or input.UserInputType == Enum.UserInputType.Touch then
			local delta = input.Position - dragStartPos
			if math.abs(delta.X) > CLICK_THRESHOLD or math.abs(delta.Y) > CLICK_THRESHOLD then
				isDragging = true
				toggle.Position = UDim2.new(
					startPos.X.Scale,
					startPos.X.Offset + delta.X,
					startPos.Y.Scale,
					startPos.Y.Offset + delta.Y
				)
			end
		end
	end)

	close.Activated:Connect(hideFrame)
	close.InputBegan:Connect(function(input)
		if input.UserInputType == Enum.UserInputType.Touch or input.UserInputType == Enum.UserInputType.MouseButton1 then
			hideFrame()
		end
	end)
end
typeConn = RunService.RenderStepped:Connect(function()
	local elapsed = tick() - startTime
	local progress = math.clamp(elapsed / typeDuration, 0, 1)
	local target = math.floor(progress * totalChars)
	if target > lastIndex then
		lastIndex = target
		textLabel.Text = table.concat(chars, "", 1, target)
	end
	if progress >= 1 then
		typeConn:Disconnect()
		task.wait(math.random(100,200)/100)
		textLabel.Text = ""
		local loadingLabel = Instance.new("TextLabel")
		loadingLabel.Size = UDim2.new(0,300,0,22)
		loadingLabel.AnchorPoint = Vector2.new(0.5,1)
		loadingLabel.Position = UDim2.new(0.5,0,0.5,-18)
		loadingLabel.BackgroundTransparency = 1
		loadingLabel.TextColor3 = Color3.fromRGB(255,0,0)
		loadingLabel.Font = Enum.Font.Code
		loadingLabel.TextSize = 18
		loadingLabel.TextXAlignment = Enum.TextXAlignment.Center
		loadingLabel.TextYAlignment = Enum.TextYAlignment.Center
		loadingLabel.Text = (currentLanguage == "vn") and "Đang tải: 0%" or "Loading: 0%"
		loadingLabel.Parent = bg
		local container = Instance.new("Frame")
		container.Size = UDim2.new(0.66,0,0,12)
		container.AnchorPoint = Vector2.new(0.5,0.5)
		container.Position = UDim2.new(0.5,0,0.5,0)
		container.BackgroundTransparency = 1
      container.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
		container.Parent = bg
		local stroke = Instance.new("UIStroke")
		stroke.Parent = container
		stroke.Color = Color3.fromRGB(255, 0, 0)
		stroke.Thickness = 2
		stroke.Transparency = 0
		local fill = Instance.new("Frame")
		fill.Size = UDim2.new(0,0,1,0)
		fill.Position = UDim2.new(0,0,0,0)
		fill.AnchorPoint = Vector2.new(0,0)
      fill.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
		fill.BorderSizePixel = 0
		fill.Parent = container
		local scan = Instance.new("Frame")
		scan.Size = UDim2.new(0,2,1,0)
		scan.Position = UDim2.new(0,0,0,0)
		scan.BorderSizePixel = 0
      scan.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
		scan.Parent = container
		local percent = 0
		local pauseTimes = math.random(0,3)
		local pausePoints = {}
		for i = 1, pauseTimes do table.insert(pausePoints, math.random(10,95)) end
		table.sort(pausePoints)
		local usedPauses = 0
		local totalTime = math.random(1,3)
		local lastUpdate = tick()
		local loadingConn
		loadingConn = RunService.RenderStepped:Connect(function()
			if percent >= 100 then
				loadingConn:Disconnect()
				local tweenBg = TweenService:Create(bg, TweenInfo.new(0.6, Enum.EasingStyle.Quad), {BackgroundTransparency = 1})
				local tweenText = TweenService:Create(textLabel, TweenInfo.new(0.6, Enum.EasingStyle.Quad), {TextTransparency = 1})
				local tweenLoading = TweenService:Create(loadingLabel, TweenInfo.new(0.6, Enum.EasingStyle.Quad), {TextTransparency = 1})
				local tweenFill = TweenService:Create(fill, TweenInfo.new(0.6, Enum.EasingStyle.Quad), {BackgroundTransparency = 1})
				local tweenScan = TweenService:Create(scan, TweenInfo.new(0.6, Enum.EasingStyle.Quad), {BackgroundTransparency = 1})
				tweenBg:Play(); tweenText:Play(); tweenLoading:Play(); tweenFill:Play(); tweenScan:Play()
				tweenBg.Completed:Wait()
				if gui and gui.Parent then gui:Destroy() end
				startBom2devGUI()
				return
			end
			if usedPauses < #pausePoints and percent == pausePoints[usedPauses+1] then
				usedPauses = usedPauses + 1
				task.wait(math.random(1,2))
			end
			local now = tick()
			local delta = now - lastUpdate
			local step = math.max(1, math.ceil((delta / totalTime) * 100))
			percent = math.min(100, percent + step)
			loadingLabel.Text = ((currentLanguage == "vn") and "Đang tải: " or "Loading: ")..percent.."%"
			fill.Size = UDim2.new(percent/100, 0, 1, 0)
			scan.Position = UDim2.new(percent/100, 0, 0, 0)
			lastUpdate = now
		end)
	end
end)

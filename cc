-- discord.gg/syncrypt

while not game.Players.LocalPlayer.Character or not game.Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart") do
	game:GetService("ReplicatedStorage"):WaitForChild("Remotes"):WaitForChild("CommF_"):InvokeServer("SetTeam", "Marines")
	task.wait(1)
end

status = function(p1)
	print(p1)
end
Services = {}
setmetatable(Services, {
	__index = function(p2, p3)
		return game:GetService(p3)
	end
})
Remotes = {}
setmetatable(Remotes, {
	__index = function(p4, p5)
		if p5 == "CommF_" then
			return {
				InvokeServer = function(...)
					return Services.ReplicatedStorage.Remotes.CommF_:InvokeServer(select(2, ...))
				end
			}
		end

		return Services.ReplicatedStorage.Remotes[p5]
	end
})
TDT = {
	Backpack = {}
}

local ItemReplicationService
local module
local KEYS
local ItemConfig

local function v5()
	if module and KEYS and ItemConfig then
		return true
	end

	pcall(function()
		local ReplicatedStorage_ = game:GetService("ReplicatedStorage")

		ItemReplicationService = ItemReplicationService or ReplicatedStorage_:WaitForChild("ItemReplicationService", 10)
		module = module or ItemReplicationService and require(ItemReplicationService)
		KEYS = KEYS or ItemReplicationService and require(ItemReplicationService.KEYS)
		ItemConfig = ItemConfig or require(ReplicatedStorage_:WaitForChild("ItemConfig", 10))
	end)

	return module ~= nil and KEYS ~= nil and ItemConfig ~= nil
end
local function v7()
	local t1 = {}

	if not v5() then
		return t1
	end

	local v9 = tick() + 5

	while module.IsInitialized ~= true and tick() < v9 do
		task.wait()
	end

	local ok, result = pcall(function()
		return module:GetItems(KEYS.QUANTITY)
	end)

	if ok and result then
		for _, v in pairs(result) do
			if v.Value and v.Value > 0 then
				local ok2, result2 = pcall(function()
					return ItemConfig.match(v.ItemId):unwrap().Index.DebugLabel
				end)

				if ok2 and result2 then
					table.insert(t1, {
						Name = result2:gsub("%s*%[.-%]%s*$", ""),
						Count = v.Value,
						ItemId = v.ItemId
					})
				end
			end
		end
	end

	return t1
end

RefreshInventory = function()
	while true do
		local backpack = {}

		for _, v in ipairs(v7()) do
			backpack[v.Name] = v
		end

		TDT.Backpack = backpack
		task.wait(1)
	end
end

local function v19(p6)
	hasItem = false
	pcall(function()
		local v20 = v7()

		for _, v in pairs(v20) do
			if v.Name == p6 then
				hasItem = true

				break
			end
		end
	end)

	return hasItem
end

LocalPlayer = game.Players.LocalPlayer
GetSpawnFolder = function()
	local _WorldOrigin = workspace:FindFirstChild("_WorldOrigin")

	_WorldOrigin = _WorldOrigin and _WorldOrigin:FindFirstChild("PlayerSpawns")

	if _WorldOrigin then
		return _WorldOrigin:FindFirstChild(LocalPlayer.Team and LocalPlayer.Team.Name or "Pirates") or _WorldOrigin:FindFirstChild("Pirates") or _WorldOrigin:FindFirstChild("Marines")
	end

	return nil
end
InArea = function(p7)
	local _WorldOrigin = workspace:FindFirstChild("_WorldOrigin")

	if not _WorldOrigin or not _WorldOrigin:FindFirstChild("Locations") then
		return nil
	end

	local Position = typeof(p7) == "CFrame" and p7.Position or p7
	local children, v27 = _WorldOrigin.Locations:GetChildren()
	local n1 = 0
	local v29

	for _, v in next, children, v27 do
		if v:FindFirstChild("Mesh") and (Position - v.Position).Magnitude <= v.Mesh.Scale.X / 2 + 500 and n1 < v.Mesh.Scale.X then
			n1 = v.Mesh.Scale.X
			v29 = v
		end
	end

	return v29
end
GetSpawnPoint = function(p8)
	local v32 = GetSpawnFolder()

	if not v32 then
		return nil
	end

	local Position = typeof(p8) == "CFrame" and p8.Position or typeof(p8) == "Vector3" and p8 or p8.Position
	local children, v35 = v32:GetChildren()

	for _, v in next, children, v35 do
		if v:FindFirstChild("Part") and (v.Part.Position - Position).Magnitude <= 2500 then
			return v
		end
	end

	return nil
end
HasRelocateItem = function()
	local t2 = {
		"God's Chalice",
		"Fist of Darkness",
		"Sweet Chalice",
		"Hallow Essence",
		"Flower1"
	}
	local t3 = {
		LocalPlayer:FindFirstChild("Backpack"),
		LocalPlayer.Character
	}

	for _, v in ipairs(t3) do
		if v then
			for _, child in ipairs(v:GetChildren()) do
				if child:IsA("Tool") then
					for _, v2 in ipairs(t2) do
						if child.Name == v2 or string.find(child.Name, v2, 1, true) then
							return true
						end
					end
				end
			end
		end
	end

	return false
end
C = function(p9)
	local children, v47 = game.Players.LocalPlayer.Backpack:GetChildren()

	for _, v in next, children, v47 do
		if v:IsA("Tool") and (v.Name == p9 or string.find(v.Name, p9)) then
			return v
		end
	end

	local Character = game.Players.LocalPlayer.Character

	if Character then
		local next_ = next
		local children2, v53 = Character:GetChildren()

		for _, v in next_, children2, v53 do
			if v:IsA("Tool") and (v.Name == p9 or string.find(v.Name, p9)) then
				return v
			end
		end
	end

	return false
end
CanBypassTeleport = function(p10)
	local v56 = InArea(p10)

	if not v56 then
		return false
	end

	local Name = v56.Name

	if Name:find("Dimension") or Name:find("Submerged") or Name == "Sealed Cavern" or Name:lower():find("under") then
		return false
	end

	if HasRelocateItem() then
		return false
	end

	local Data = LocalPlayer:FindFirstChild("Data")

	Data = Data and Data:FindFirstChild("LastSpawnPoint")

	if Data and Data.Value == "SubmergedIsland" then
		return false
	end

	if LocalPlayer:GetAttribute("ExactLocation") == "Submerged Island" then
		return false
	end

	local HumanoidRootPart = LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("HumanoidRootPart")

	if not HumanoidRootPart then
		return false
	end

	if (p10 - HumanoidRootPart.Position).Magnitude <= 3500 then
		return false
	end

	return true
end
GetBypassCFrame = function(p11)
	local v60 = GetSpawnFolder()

	if not v60 then
		return nil
	end

	local HumanoidRootPart = LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("HumanoidRootPart")

	if not HumanoidRootPart then
		return nil
	end

	local v62 = GetSpawnPoint(HumanoidRootPart)
	local children, v64 = v60:GetChildren()
	local huge = math.huge
	local v66

	for _, v in next, children, v64 do
		if v:FindFirstChild("Part") then
			local Magnitude = (v.Part.Position - HumanoidRootPart.Position).Magnitude
			local Magnitude2 = (v.Part.Position - p11).Magnitude

			if (p11 - HumanoidRootPart.Position).Magnitude >= 3000 and GetSpawnPoint(v.Part) ~= v62 and Magnitude <= 10000 and Magnitude2 <= huge then
				huge = Magnitude2
				v66 = v
			end
		end
	end

	return v66
end
BypassTP = function(p12)
	if getgenv().DisableBypassTP then
		return false
	end

	local ok, result = pcall(function()
		if not CanBypassTeleport(p12) then
			return false
		end

		local v73 = GetBypassCFrame(p12)

		if not v73 then
			return false
		end

		local Humanoid = LocalPlayer.Character and LocalPlayer.Character:FindFirstChildOfClass("Humanoid")

		if not Humanoid or Humanoid.Health <= 0 then
			return false
		end

		if TweenInstance then
			pcall(function()
				TweenInstance:Cancel()
			end)
		end

		pcall(function()
			LocalPlayer.Character.LastSpawnPoint.Disabled = true
		end)
		Remotes.CommF_:InvokeServer("SetLastSpawnPoint", v73.Name)
		Remotes.CommF_:InvokeServer("SetSpawnPoint")
		LocalPlayer.Character:PivotTo(v73.Part.CFrame)
		Humanoid:ChangeState(15)

		local v75 = tick() + 10

		repeat
			task.wait()
		until tick() > v75 or LocalPlayer.Character and LocalPlayer.Character ~= LocalPlayer.Character and LocalPlayer.Character:FindFirstChildOfClass("Humanoid") and LocalPlayer.Character:FindFirstChildOfClass("Humanoid").Health > 0 and LocalPlayer.Character:FindFirstChild("HumanoidRootPart")

		return true
	end)

	return ok and result or false
end
WaitCharacter = function(p13)
	local v76 = tick() + (p13 or 10)
	local HumanoidRootPart, Humanoid, Character

	repeat
		task.wait()
		Character = LocalPlayer.Character
		HumanoidRootPart = Character and Character:FindFirstChild("HumanoidRootPart")
		Humanoid = Character and Character:FindFirstChildOfClass("Humanoid")
	until HumanoidRootPart and Humanoid and Humanoid.Health > 0 and HumanoidRootPart:IsDescendantOf(workspace) or tick() > v76

	if not (HumanoidRootPart and Humanoid) then
		return nil
	end

	local v80 = tick() + 1

	repeat
		task.wait()
	until tick() > v80 or HumanoidRootPart.AssemblyLinearVelocity.Magnitude < 5

	return Character
end
TweenTarget = nil
TweenChar = nil
TweenTo = function(p14)
	if not p14 then
		return
	end

	p14 = typeof(p14) ~= "CFrame" and ConvertTo(CFrame, p14) or p14

	local Character = LocalPlayer.Character
	local HumanoidRootPart = Character and Character:FindFirstChild("HumanoidRootPart")

	if TweenInstance and TweenInstance.PlaybackState == Enum.PlaybackState.Playing and TweenChar == Character and TweenTarget and (TweenTarget - p14.Position).Magnitude <= 20 then
		return
	end

	if TweenInstance then
		pcall(function()
			TweenInstance:Cancel()
		end)
	end

	if HumanoidRootPart and (p14.Position - HumanoidRootPart.Position).Magnitude >= 5000 and BypassTP(p14.Position) then
		Character = WaitCharacter()
		HumanoidRootPart = Character and Character:FindFirstChild("HumanoidRootPart")
	end

	if game.Players.LocalPlayer:GetAttribute("ExactLocation") and game.Players.LocalPlayer:GetAttribute("ExactLocation") == "Submerged Island" then
		game:GetService("ReplicatedStorage"):WaitForChild("Remotes"):WaitForChild("CommF_"):InvokeServer(unpack({ "TeleportToSpawn" }))
		task.wait(6)
		Character = WaitCharacter()
		HumanoidRootPart = Character and Character:FindFirstChild("HumanoidRootPart")
	end

	if not Character or not HumanoidRootPart then
		return
	end

	for _, v in Character:GetDescendants() do
		if v:IsA("BasePart") then
			v.CanCollide = false
		end
	end

	local Humanoid = Character:FindFirstChildOfClass("Humanoid")

	if Humanoid and Humanoid.FloorMaterial ~= Enum.Material.Air then
		Humanoid:ChangeState(Enum.HumanoidStateType.Jumping)
	end

	local Head = Character:WaitForChild("Head")
	local ChoNamGg = Head:FindFirstChild("cho nam gg")

	if not ChoNamGg then
		ChoNamGg = Instance.new("BodyVelocity")
		ChoNamGg.Name = "cho nam gg"
		ChoNamGg.Parent = Head
	end

	ChoNamGg.MaxForce = Vector3.new(0, math.huge, 0)
	ChoNamGg.Velocity = Vector3.zero

	local cFrame = CFrame.new(p14.Position)
	local CFrame_ = HumanoidRootPart.CFrame
	local Magnitude = (Vector3.new(CFrame_.X, 0, CFrame_.Z) - Vector3.new(cFrame.X, 0, cFrame.Z)).Magnitude
	local v91 = CaculateDistance(HumanoidRootPart.CFrame, cFrame)

	TweenTarget = cFrame.Position
	TweenChar = Character
	TweenInstance = Services.TweenService:Create(HumanoidRootPart, TweenInfo.new(v91 / 250, Enum.EasingStyle.Linear), {
		CFrame = cFrame
	})
	TweenInstance:Play()
end
RS = game:GetService("ReplicatedStorage")
ReplicatedStorage = RS
LP = LocalPlayer
ConvertTo = function(p15, p16)
	return p15.new(p16.X, p16.Y, p16.Z)
end
CaculateDistance = function(p17, p18)
	if not p17 then
		return 0
	end

	p18 = p18 or game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame

	return (ConvertTo(Vector3, p17) - ConvertTo(Vector3, p18)).magnitude
end
GetConnectionEnemies = function(p19)
	for _, child in pairs(RS:GetChildren()) do
		if child:IsA("Model") and (typeof(p19) == "table" and table.find(p19, child.Name) or child.Name == p19) and child:FindFirstChild("Humanoid") and child.Humanoid.Health > 0 then
			return child
		end
	end

	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if child:IsA("Model") and (typeof(p19) == "table" and table.find(p19, child.Name) or child.Name == p19) and child:FindFirstChild("Humanoid") and child.Humanoid.Health > 0 then
			return child
		end
	end

	return nil
end
Hop = {}
Hop.A = function(p20)
	local v96 = p20 or 8
	local ok, result = pcall(function()
		return game:GetService("HttpService"):JSONDecode(game:HttpGetAsync("https://games.roblox.com/v1/games/" .. game.PlaceId .. "/servers/Public?sortOrder=Asc&limit=100")).data
	end)

	if not ok or not result then
		return
	end

	for _, v in pairs(result) do
		if v.playing < v96 and v.id ~= game.JobId then
			pcall(function()
				game:GetService("ReplicatedStorage"):WaitForChild("__ServerBrowser"):InvokeServer("teleport", v.id)
			end)

			break
		end
	end
end
Hop.API = function(p21, p22)
	Hop.A(p22)
end
HopServer = function(p23)
	Hop.A(p23)
end
MAX_CHESTS_PER_SERVER = 30
Config = Config or {
	["Chest Farm"] = {
		Hop = true
	}
}
getgenv().KilledBosses = getgenv().KilledBosses or {}
SetText = function(p24)
	status(p24)
end
FastAttack = loadstring([[        local Modules = game.ReplicatedStorage.Modules
        local Net = Modules.Net
        local Register_Hit, Register_Attack = Net:WaitForChild('RE/RegisterHit'), Net:WaitForChild('RE/RegisterAttack')
        local Funcs = {}
        function GetAllBladeHits()
            bladehits = {}
            for _, v in pairs(workspace.Enemies:GetChildren()) do
                if v:FindFirstChild('Humanoid') and v:FindFirstChild('HumanoidRootPart') and v.Humanoid.Health > 0 
                and (v.HumanoidRootPart.Position - game.Players.LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 65 then
                    table.insert(bladehits, v)
                end
            end
            return bladehits
        end
        function Getplayerhit()
            bladehits = {}
            for _, v in pairs(workspace.Characters:GetChildren()) do
                if v.Name ~= game.Players.LocalPlayer.Name and v:FindFirstChild('Humanoid') and v:FindFirstChild('HumanoidRootPart') and v.Humanoid.Health > 0 
                and (v.HumanoidRootPart.Position - game.Players.LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 65 then
                    table.insert(bladehits, v)
                end
            end
            return bladehits
        end

        local Net = (Services.ReplicatedStorage.Modules.Net)

        local RegisterAttack = require(Net):RemoteEvent('RegisterAttack', true)
        local RegisterHit = require(Net):RemoteEvent('RegisterHit', true)

        function Funcs:Attack()
            
            
            local bladehits = {}
            for r,v in pairs(GetAllBladeHits()) do
                table.insert(bladehits, v)
        
            end
            for r,v in pairs(Getplayerhit()) do
                table.insert(bladehits, v)
            end
            
            if #bladehits == 0 then
                
                return
            end
            
            local args = {
                [1] = nil;
                [2] = {},
                [4] = '078da341'
            }
            for r, v in pairs(bladehits) do
                
                
                RegisterAttack:FireServer(0)
                if not args[1] then
                    args[1] = v.Head
                end
                table.insert(args[2], {
                    [1] = v,
                    [2] = v.HumanoidRootPart
                })
                table.insert(args[2], v)
            end
            
            
            RegisterHit:FireServer(unpack(args))
        end

        task.spawn(function() 
            while task.wait(.05) do 
                if _G.FastAttack == os.time() then 
                    pcall(function() 
                        Funcs:Attack() 
                    end)
                end 
            end
        end)

        getgenv().Attack = function(MonResult) 
            pcall(function() 
                _G.FastAttack = os.time()
            end)
        end 
        ]])
FastAttack()
task.spawn(function()
	while wait(0.2) do
		getgenv().Attack()
	end
end)

local function v101(p25)
	return (LP.Backpack:FindFirstChild(p25) or LP.Character and LP.Character:FindFirstChild(p25)) and true or false
end
local function v102(p26)
	if not LP.Character then
		return
	end

	local Tool = LP.Character:FindFirstChildOfClass("Tool")

	if Tool and Tool.ToolTip == p26 then
		return Tool
	end

	for _, child in pairs(LP.Backpack:GetChildren()) do
		if child:IsA("Tool") and child.ToolTip == p26 then
			LP.Character:FindFirstChildOfClass("Humanoid"):EquipTool(child)

			return child
		end
	end

	return nil
end

local response
local n2 = 0

if Remotes.CommF_:InvokeServer("CheckTempleDoor") then
	return
end

local response2 = game.ReplicatedStorage.Remotes.CommF_:InvokeServer("getRaceLevel")

if not (response2 < 3) then
	if response == nil or tick() - n2 > 3 then
		response = Remotes.CommF_:InvokeServer("RaceV4Progress", "Check")
		n2 = tick()
	end

	AiChoMaDiGatCan = response
	getgenv().FailedJobIds = {}
	getgenv().LastApiRefresh = 0
	HttpService = game:GetService("HttpService")
	status = function(p27)
		print("[Pull Lever] " .. p27)
	end
	getBlueGear = function()
		if not workspace.Map:FindFirstChild("MysticIsland") then
			return nil
		end

		for _, v in workspace.Map.MysticIsland:GetDescendants() do
			if v:IsA("MeshPart") and v.MeshId == "rbxassetid://10153114969" and v.Transparency ~= 1 then
				return v.CFrame
			end
		end
	end

	if response == nil or tick() - n2 > 3 then
		response = Remotes.CommF_:InvokeServer("RaceV4Progress", "Check")
		n2 = tick()
	end

	task.spawn(RefreshInventory)

	local function v111()
		if tick() - n2 > 3 then
			response = Remotes.CommF_:InvokeServer("RaceV4Progress", "Check")
			n2 = tick()
		end

		AiChoMaDiGatCan = response

		if not AiChoMaDiGatCan or AiChoMaDiGatCan == 0 then
			if not v19("Valkyrie Helm") then
				print("rip")

				if GetConnectionEnemies("rip_indra True Form") then
					KillMonster("rip_indra True Form")

					return
				end

				elites = {
					"Diablo",
					"Deandre",
					"Urban"
				}

				for _, v in ipairs(elites) do
					if GetConnectionEnemies(v) then
						KillMonster(v)

						return
					end

					if not C("God's Chalice") then
						if not GetConnectionEnemies(EliteName) and not C("God's Chalice") then
							Hop.A(12)

							return
						end

						continue
					end

					TweenTo(CFrame.new(-5563.5459, 316.06601, -2662.56396))

					local GodSChalice = LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("God's Chalice")

					if not GodSChalice then
						local GodSChalice2 = LocalPlayer:FindFirstChild("Backpack") and LocalPlayer.Backpack:FindFirstChild("God's Chalice")

						if GodSChalice2 and LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
							LocalPlayer.Character.Humanoid:EquipTool(GodSChalice2)
							task.wait(0.2)
							GodSChalice = LocalPlayer.Character:FindFirstChild("God's Chalice")
						end
					end

					if GodSChalice then
						pcall(function()
							GodSChalice:Activate()
						end)
					end

					return
				end
			elseif not v19("Mirror Fractal") and v19("Valkyrie Helm") then
				print("dough")

				if GetConnectionEnemies("Dough King") then
					KillMonster("Dough King")

					return
				end

				for _, v in {
					"Diablo",
					"Urban",
					"Deandre"
				}, nil, nil do
					if GetConnectionEnemies(v) then
						KillMonster(v)

						return
					end

					if not C("God's Chalice") then
						if not GetConnectionEnemies(v) and not C("God's Chalice") then
							Hop.A(12)

							return
						end

						continue
					end

					local v118 = tonumber(string.match(tostring(game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("CakePrinceSpawner")), "%d+")) or 0
					local conjuredCocoa = TDT.Backpack["Conjured Cocoa"]

					conjuredCocoa = conjuredCocoa and conjuredCocoa.Count or 0

					if not (v118 < 500) then
						Remotes.CommF_:InvokeServer("SweetChaliceNpc")
						task.wait(1)
						Remotes.CommF_:InvokeServer("CakePrinceSpawner")

						return
					end

					local v120 = conjuredCocoa < 10 and {
						"Chocolate Bar Battler",
						"Cocoa Warrior"
					} or {
						"Cookie Crafter",
						"Cake Guard",
						"Baking Staff",
						"Head Baker"
					}

					for _, v2 in v120, nil, nil do
						if GetConnectionEnemies(v2) then
							KillMonster(v2)

							return
						end
					end
				end
			elseif v19("Valkyrie Helm") and v19("Mirror Fractal") then
				status("Get Pull Lever")

				local cFrame = CFrame.new(3032, 2280, -7325)

				TweenTo(cFrame)

				if CaculateDistance(cFrame) < 30 then
					PullLeverQuestDebounce = tick()

					if not game.Workspace.Map:FindFirstChild("Temple of Time") then
						game.ReplicatedStorage.MapStash["Temple of Time"].Parent = workspace.Map
					end

					Remotes.CommF_:InvokeServer("RaceV4Progress", "Begin")
					game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("RaceV4Progress", "Check")
					game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("RaceV4Progress", "Teleport")
					task.wait(2)
					TweenTo(CFrame.new(28613, 14896, 106))
					game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("RaceV4Progress", "Check")
					game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("RaceV4Progress", "TeleportBack")
					AiChoMaDiGatCan = Remotes.CommF_:InvokeServer("RaceV4Progress", "Check")
					Hop.A()

					return
				end
			else
				local MysticIsland = workspace.Map:FindFirstChild("MysticIsland")

				if MysticIsland then
					if math.floor(game.Lighting.ClockTime) >= 12 or math.floor(game.Lighting.ClockTime) < 5 then
						local v125 = getBlueGear()

						print("Blue GEar", v125)

						if v125 then
							print("THAY R BO OI ")
							TweenTo(v125)
							task.spawn(function()
								task.wait(2)

								while TweenInstance and TweenInstance.PlaybackState == Enum.PlaybackState.Playing do
									if workspace.Map:FindFirstChild("MysticIsland") then
										task.wait(1)

										continue
									end

									status("Mirage Island disappeared during tween, hopping...")
									Hop.API("Mirage", 12, 5)

									if TweenInstance then
										pcall(function()
											TweenInstance:Cancel()
										end)
									end

									return
								end
							end)

							return
						end

						status("Tween to Mirage Island")

						local u126 = true

						task.spawn(function()
							local Health = LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") and LocalPlayer.Character.Humanoid.Health or 0

							while u126 do
								task.wait(0.5)

								if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
									local Health2 = LocalPlayer.Character.Humanoid.Health

									if Health > 0 and Health2 > Health + 50 then
										status("returning to Mirage Island...")
										task.wait(2)

										if workspace.Map:FindFirstChild("MysticIsland") then
											TweenTo(workspace.Map.MysticIsland:GetModelCFrame() + Vector3.new(0, 300, 0))
											Health = Health2
										else
											Health = Health2
										end
									else
										Health = Health2
									end
								end
							end
						end)
						TweenTo(MysticIsland:GetModelCFrame() + Vector3.new(0, 300, 0))
						task.spawn(function()
							task.wait(2)

							while TweenInstance and TweenInstance.PlaybackState == Enum.PlaybackState.Playing do
								if workspace.Map:FindFirstChild("MysticIsland") then
									task.wait(1)

									continue
								end

								status("hopping...")

								if TweenInstance then
									pcall(function()
										TweenInstance:Cancel()
									end)
								end

								u126 = false
								Hop.API("Mirage", 12, 5)

								return
							end
						end)

						if CaculateDistance(MysticIsland:GetModelCFrame() + Vector3.new(0, 300, 0)) < 20 then
							LocalPlayer.CameraMaxZoomDistance = 0.5
							LocalPlayer.CameraMaxZoomDistance = 200
							workspace.CurrentCamera.CFrame = CFrame.new(workspace.CurrentCamera.CFrame.Position, game.Lighting:GetMoonDirection() + workspace.CurrentCamera.CFrame.Position)
							game.ReplicatedStorage.Remotes.CommE:FireServer("ActivateAbility")
						end

						return
					end

					print("Hop for Mirage Island | Night")
					Hop.API("Mirage", 12, 5)
				else
					print("Hop for Mirage Island")
					Hop.API("Mirage", 12, 5)
				end
			end
		end
	end

	while task.wait(1) do
		local ok, result = pcall(v111)

		if not ok then
			warn("[Pull Lever] " .. tostring(result))
		end
	end

	return
end

status("Race level " .. tostring(response2) .. " < 3, đang up V3...")

local ReplicatedStorage_ = game:GetService("ReplicatedStorage")
local LocalPlayer_ = game.Players.LocalPlayer

game:GetService("TweenService")

local VirtualInputManager = game:GetService("VirtualInputManager")

local function v134()
	local ok, result = pcall(function()
		return LocalPlayer_.Data.Race.Value
	end)

	return ok and result or nil
end

local t4 = {
	Human = "Human",
	Mink = "Rabbit",
	Fishman = "Shark",
	Skypiea = "Angel",
	Ghoul = "Ghoul",
	Cyborg = "Cyborg"
}

local function v138(p28)
	local ok, result = pcall(function()
		return ReplicatedStorage_.Remotes.CommF_:InvokeServer("getTitles")
	end)

	if not ok or not result or typeof(result) ~= "table" then
		return false
	end

	local v141 = t4[p28]

	if not v141 then
		return false
	end

	for _, v in pairs(result) do
		if v.Unlocked and v.Description and v.Description:find("V3") and v.Description:find(v141) then
			return true
		end
	end

	return false
end
local function v144(p29)
	VirtualInputManager:SendKeyEvent(true, p29, false, game)
	task.wait(0.05)
	VirtualInputManager:SendKeyEvent(false, p29, false, game)
	task.wait(0.3)
end
local function v145(p30)
	for _, child in pairs(LocalPlayer_.Backpack:GetChildren()) do
		if child:IsA("Tool") and child.ToolTip == p30 then
			local Humanoid = LocalPlayer_.Character and LocalPlayer_.Character:FindFirstChildOfClass("Humanoid")

			if Humanoid then
				Humanoid:EquipTool(child)

				return child.Name
			end
		end
	end

	if LocalPlayer_.Character then
		for _, child in pairs(LocalPlayer_.Character:GetChildren()) do
			if child:IsA("Tool") and child.ToolTip == p30 then
				return child.Name
			end
		end
	end

	return nil
end
local function v151(p31)
	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if child:IsA("Model") and child.Name == p31 and child:FindFirstChild("Humanoid") and child.Humanoid.Health > 0 and child:FindFirstChild("HumanoidRootPart") then
			return child
		end
	end

	for _, child in pairs(ReplicatedStorage_:GetChildren()) do
		if child:IsA("Model") and child.Name == p31 and child:FindFirstChild("Humanoid") and child.Humanoid.Health > 0 and child:FindFirstChild("HumanoidRootPart") then
			return child
		end
	end

	return nil
end

KillMonster = function(p32)
	xpcall(function()
		local children, v157 = workspace.Enemies:GetChildren()

		for _, v in next, children, v157 do
			local Humanoid = v:FindFirstChildWhichIsA("Humanoid")
			local HumanoidRootPart = v:FindFirstChild("HumanoidRootPart")

			if Humanoid and Humanoid.Health > 0 and HumanoidRootPart and (typeof(p32) == "table" and table.find(p32, v.Name) or v.Name == p32) then
				if not (game.Players.LocalPlayer.Character and game.Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart") and game.Players.LocalPlayer.Character.HumanoidRootPart.Position) then
					return
				end

				TweenTo(HumanoidRootPart.Position + Vector3.new(0, 35, 0))
				v102("Melee")

				return
			end
		end

		local children2, v163 = Services.ReplicatedStorage:GetChildren()

		for _, v in next, children2, v163 do
			local HumanoidRootPart = v:FindFirstChild("HumanoidRootPart")

			if v:IsA("Model") and HumanoidRootPart and (typeof(p32) == "table" and table.find(p32, v.Name) or v.Name == p32) then
				TweenTo(HumanoidRootPart.Position + Vector3.new(0, 35, 0))

				return
			end
		end
	end, function(p33)
		warn("KillMonster ERROR:", p33)
	end)
end
task.spawn(function()
	task.wait(6)

	if LocalPlayer.Character:FindFirstChild("HasBuso") then
		return
	end

	Remotes.CommF_:InvokeServer("Buso")
end)

local function v167(p34)
	pcall(function()
		sethiddenproperty(LocalPlayer_, "SimulationRadius", math.huge)
	end)

	if not LocalPlayer_.Character or not LocalPlayer_.Character:FindFirstChild("HumanoidRootPart") then
		return
	end

	local Position = LocalPlayer_.Character.HumanoidRootPart.Position

	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if (not p34 or child.Name == p34) and child:FindFirstChild("Humanoid") and child:FindFirstChild("HumanoidRootPart") and child.Humanoid.Health > 0 and (child.HumanoidRootPart.Position - Position).Magnitude <= 350 then
			child.HumanoidRootPart.CFrame = CFrame.new(Position + Vector3.new(0, 0, 5))
			child.HumanoidRootPart.CanCollide = false
			child.Humanoid.WalkSpeed = 0
			child.Humanoid.JumpPower = 0
		end
	end
end
local function v171(p35)
	if not LocalPlayer_.Character or not LocalPlayer_.Character:FindFirstChild("HumanoidRootPart") then
		return
	end

	local ChestModels = workspace:WaitForChild("ChestModels")
	local t5 = {}
	local Position = LocalPlayer_.Character.HumanoidRootPart.Position

	for _, child in ipairs(ChestModels:GetChildren()) do
		if child:IsA("Model") then
			local PrimaryPart = child.PrimaryPart or child:FindFirstChild("RootPart", true)

			if PrimaryPart then
				table.insert(t5, {
					Model = child,
					Root = PrimaryPart,
					Dist = (PrimaryPart.Position - Position).Magnitude
				})
			end
		end
	end

	table.sort(t5, function(p36, p37)
		return p36.Dist < p37.Dist
	end)

	if #t5 == 0 then
		SetText("Not Found Chest => Hop")
		HopServer(5)

		return
	end

	local n3 = 0

	for _, v in ipairs(t5) do
		if getgenv().StopV3 then
			break
		end

		if v101("Fist of Darkness") then
			SetText("Đã có Fist of Darkness!")

			return "FOD"
		end

		if MAX_CHESTS_PER_SERVER <= n3 then
			SetText("Đủ " .. MAX_CHESTS_PER_SERVER .. " chest => Hop")

			if p35 ~= "Mink" then
				HopServer(5)
			end

			return
		end

		local Model = v.Model

		if not Model or not Model.Parent or not Model:IsDescendantOf(ChestModels) then
			continue
		end

		for _, descendant in ipairs(LocalPlayer_.Character:GetDescendants()) do
			if descendant:IsA("BasePart") then
				descendant.CanCollide = false
			end
		end

		local n4 = 0
		local exitTo

		while true do
			n4 += 1

			if not LocalPlayer_.Character or not LocalPlayer_.Character:FindFirstChild("HumanoidRootPart") then
				exitTo = 1

				break
			end

			if not Model or not Model.Parent or not Model:IsDescendantOf(ChestModels) then
				exitTo = 1

				break
			end

			if not v101("Fist of Darkness") then
				LocalPlayer_.Character.HumanoidRootPart.CFrame = v.Root.CFrame + Vector3.new(0, 2, 0)
				task.wait(0.1)

				if not Model.Parent or not Model:IsDescendantOf(ChestModels) or n4 >= 20 then
					exitTo = 1

					break
				end

				continue
			end

			break
		end

		if exitTo ~= 1 then
			return "FOD"
		end

		if not Model.Parent or not Model:IsDescendantOf(ChestModels) then
			n3 += 1
			SetText(("Chest | %d/%d"):format(n3, MAX_CHESTS_PER_SERVER))
		end

		if n3 > 0 and n3 % 10 == 0 then
			SetText("Reset Character")

			local Humanoid = LocalPlayer_.Character:FindFirstChildOfClass("Humanoid")

			if Humanoid then
				Humanoid.Health = 0

				repeat
					task.wait(0.5)
				until LocalPlayer_.Character and LocalPlayer_.Character:FindFirstChild("HumanoidRootPart") and LocalPlayer_.Character:FindFirstChildOfClass("Humanoid") and LocalPlayer_.Character:FindFirstChildOfClass("Humanoid").Health > 0
			end
		end
	end

	SetText("Hết Chest ")

	if Config["Chest Farm"].Hop and p35 == "Mink" or p35 ~= "Mink" then
		HopServer(5)
	end
end
local function v187()
	if not workspace:FindFirstChild("SeaBeasts") then
		return nil
	end

	for _, child in pairs(workspace.SeaBeasts:GetChildren()) do
		if child:FindFirstChild("HumanoidRootPart") and child:FindFirstChild("Health") and child.Health.Value > 0 then
			return child
		end
	end

	return nil
end
local function v190(p38)
	if not p38 then
		return false
	end

	while true do
		task.wait(0.3)

		if p38 and p38.Parent then
			if p38:FindFirstChild("Health") and not (p38.Health.Value <= 0) and p38:FindFirstChild("HumanoidRootPart") then
				if LocalPlayer_.Character and LocalPlayer_.Character:FindFirstChild("HumanoidRootPart") then
					local Position = p38.HumanoidRootPart.Position
					local WaterBasePlane = workspace.Map:FindFirstChild("WaterBase-Plane")

					TweenTo(CFrame.new(Position.X, WaterBasePlane and WaterBasePlane.Position.Y + 200 or 200, Position.Z))
					status("Fishman V3 | Sea Beast HP: " .. math.floor(p38.Health.Value))
					v145("Blox Fruit")
					v144("Z")
					v144("X")
					v144("C")
					v145("Melee")
					v144("Z")
					v144("X")
					v144("C")
					v145("Sword")
					v144("Z")
					v144("X")
					v145("Gun")
					v144("Z")
					v144("X")

					if p38 and p38.Parent and p38:FindFirstChild("Health") and not (p38.Health.Value <= 0) then
						continue
					end
				end
			end
		end

		break
	end

	return p38:FindFirstChild("Health") and p38.Health.Value <= 0
end
local function v193()
	local v194 = v187()

	if v194 then
		if LocalPlayer_.Character.Humanoid.Sit then
			LocalPlayer_.Character.Humanoid.Sit = false
			task.wait(1)
		end

		v190(v194)

		return
	end

	local v195

	for _, child in pairs(workspace.Boats:GetChildren()) do
		if child:FindFirstChild("Owner") and tostring(child.Owner.Value) == LocalPlayer_.Name then
			v195 = child

			break
		end

		v195 = nil
	end

	if not v195 then
		status("Fishman V3 | Mua thuyền")
		TweenTo(CFrame.new(-110.271713, 9.76438141, 2956.36841))
		task.wait(2)

		if LocalPlayer_.Character and (CFrame.new(-110.271713, 9.76438141, 2956.36841).Position - LocalPlayer_.Character.HumanoidRootPart.Position).Magnitude <= 15 then
			ReplicatedStorage_.Remotes.CommF_:InvokeServer("BuyBoat", "MarineBrigade")
			task.wait(2)
		end

		return
	end

	if not LocalPlayer_.Character.Humanoid.Sit then
		status("Fishman V3 | Lên thuyền")
		TweenTo(v195.VehicleSeat.CFrame * CFrame.new(0, 1, 0))
		task.wait(2)

		return
	end

	local v198 = v187()

	if v198 then
		LocalPlayer_.Character.Humanoid.Sit = false
		task.wait(1)
		v190(v198)
	else
		status("Fishman V3 | Lái thuyền tìm Sea Beast")
		TweenTo(CFrame.new(-10000000, 31, 37016.25) * CFrame.new(0, 50, 0))
	end
end
local function v199()
	local t6 = {}
	local Players = game:GetService("Players")

	for _, player in pairs(Players:GetPlayers()) do
		if player ~= LocalPlayer_ and player.Character and player.Character:FindFirstChild("HumanoidRootPart") and player.Character:FindFirstChild("Humanoid") and player.Character.Humanoid.Health > 0 then
			table.insert(t6, player)
		end
	end

	return t6
end
local function v204(p39)
	local ok, result = pcall(function()
		return p39.Data.Level.Value
	end)

	return ok and math.abs((LocalPlayer_.Data and LocalPlayer_.Data.Level.Value or 0) - result) <= 200
end
local function v207()
	local ok, result = pcall(function()
		return not LocalPlayer_.PlayerGui.Main.PvpDisabled.Visible
	end)

	return ok and result
end
local function v210()
	local v211

	for _, v in pairs(v199()) do
		local ok, result = pcall(function()
			return v.Data.Race.Value
		end)

		if ok and result == "Skypiea" and v204(v) then
			v211 = v

			break
		end

		v211 = nil
	end

	if not v211 then
		status("Skypiea V3 | Không tìm thấy target → Hop")
		Hop.A(10)

		return
	end

	if not v207() then
		pcall(function()
			ReplicatedStorage_.Remotes.CommF_:InvokeServer("EnablePvp")
		end)
	end

	local Character = v211.Character
	local Humanoid = Character:FindFirstChild("Humanoid")

	Character:FindFirstChild("HumanoidRootPart")
	status("Skypiea V3 | Attack: " .. v211.Name)

	while true do
		task.wait(0.1)

		if Character and Humanoid and not (Humanoid.Health <= 0) then
			local HumanoidRootPart = Character:FindFirstChild("HumanoidRootPart")

			if HumanoidRootPart then
				TweenTo(HumanoidRootPart.CFrame * CFrame.new(0, 5, 2))

				if (LocalPlayer_.Character and LocalPlayer_.Character:FindFirstChild("HumanoidRootPart") and (LocalPlayer_.Character.HumanoidRootPart.Position - HumanoidRootPart.Position).Magnitude or 999) < 40 then
					v145("Melee")
					game:GetService("VirtualUser"):ClickButton1(Vector2.new())
					v144("Z")
					v144("X")
					v144("C")
				end

				if Humanoid and not (Humanoid.Health <= 0) then
					continue
				end
			end
		end

		break
	end
end
local function v219()
	while task.wait(0.5) do
		local response3 = ReplicatedStorage_.Remotes.CommF_:InvokeServer("Alchemist", "1")

		if response3 == 0 then
			status("V2 | Get quest")
			ReplicatedStorage_.Remotes.CommF_:InvokeServer("Alchemist", "2")
		elseif response3 == 1 then
			local function v221(p40)
				return LocalPlayer_.Backpack:FindFirstChild(p40) or LocalPlayer_.Character and LocalPlayer_.Character:FindFirstChild(p40)
			end

			if not v221("Flower 1") then
				status("V2 | Flower 1")
				TweenTo(workspace.Flower1.CFrame)
			elseif not v221("Flower 2") then
				status("V2 | Flower 2")
				TweenTo(workspace.Flower2.CFrame)
			elseif not v221("Flower 3") then
				status("V2 | Kill Swan Pirate")

				if v151("Swan Pirate") then
					v167("Swan Pirate")
					KillMonster("Swan Pirate")
				else
					TweenTo(CFrame.new(980.099, 121.331, 1287.209))
				end
			end
		elseif response3 == 2 then
			status("V2 | Nộp quest")
			ReplicatedStorage_.Remotes.CommF_:InvokeServer("Alchemist", "3")
			task.wait(1)
		elseif response3 == -2 then
			status("V2 Done!")

			break
		end
	end
end
local function v222()
	local v223 = v134()

	if not v223 then
		status("Không lấy được race")

		return
	end

	status("Up V3 cho: " .. v223)

	local response3 = ReplicatedStorage_.Remotes.CommF_:InvokeServer("getRaceLevel")

	if response3 == 1 then
		status(v223 .. " | Up V2 trước...")
		v219()
		task.wait(2)
		response3 = ReplicatedStorage_.Remotes.CommF_:InvokeServer("getRaceLevel")
	end

	if response3 ~= 2 then
		return
	end

	local v225, v226, v227

	while not v138(v223) and not getgenv().StopV3 do
		local response4 = ReplicatedStorage_.Remotes.CommF_:InvokeServer("Wenlocktoad", "1")

		if response4 == 0 then
			status(v223 .. " V3 | Nhận quest")
			ReplicatedStorage_.Remotes.CommF_:InvokeServer("Wenlocktoad", "2")
			task.wait(1)
		elseif response4 == 1 then
			if v223 == "Human" then
				local t7 = {
					{
						name = "Orbitus",
						pos = CFrame.new(-2172, 103, -4015)
					},
					{
						name = "Jeremy",
						pos = CFrame.new(2099.88159, 448.931, 648.997375)
					},
					{
						name = "Diamond",
						pos = CFrame.new(-1576, 198, 13)
					}
				}
				local v230 = false
				local exitTo

				for i, v in ipairs(t7) do
					if getgenv().StopV3 then
						break
					end

					if getgenv().KilledBosses[v.name] then
						continue
					end

					v225 = GetConnectionEnemies(v.name)

					if v225 then
						v226 = i
						v227 = v
						exitTo = 1

						break
					end

					Hop.A(10)
				end

				if exitTo == 1 then
					local HumanoidRootPart = v225:FindFirstChild("HumanoidRootPart")

					if HumanoidRootPart then
						TweenTo(HumanoidRootPart.Position + Vector3.new(0, 25, 0))
					end

					repeat
						task.wait(0.3)
						SetText("Human V3 | Boss " .. v226 .. ": " .. v227.name .. " | " .. math.floor(v225.Humanoid.Health / v225.Humanoid.MaxHealth * 100) .. "%")
						v102("Melee")

						local HumanoidRootPart2 = v225:FindFirstChild("HumanoidRootPart")

						if not HumanoidRootPart2 then
							break
						end

						if (LocalPlayer_.Character.HumanoidRootPart.Position - HumanoidRootPart2.Position).Magnitude > 80 then
							TweenTo(HumanoidRootPart2.Position + Vector3.new(0, 25, 0))
						end
					until not v225.Parent or v225.Humanoid.Health <= 0 or getgenv().StopV3

					getgenv().KilledBosses[v227.name] = true
					v230 = true
				end

				if not v230 then
					for _, v in ipairs(t7) do
						if not getgenv().KilledBosses[v.name] then
							SetText("Human V3 | Chờ " .. v.name)
							TweenTo(v.pos)

							break
						end
					end
				end
			elseif v223 == "Mink" then
				status("Mink V3 | Farm Chest")
				v171("Mink")
			elseif v223 == "Fishman" then
				v193()
			elseif v223 == "Skypiea" then
				v210()
			else
				status(v223 .. " V3 | Quest đang làm...")
			end

			task.wait(1)
		elseif response4 == 2 then
			status(v223 .. " V3 | Nộp quest")
			ReplicatedStorage_.Remotes.CommF_:InvokeServer("Wenlocktoad", "3")
			getgenv().KilledBossesV3 = {}
			task.wait(1)
			task.wait(1)
		elseif response4 == -2 then
			status(v223 .. " V3 DONE!")
			getgenv().KilledBossesV3 = {}

			break
		else
			task.wait(1)
		end
	end
end

v222()

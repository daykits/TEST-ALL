-- discord.gg/syncrypt

local function geniter(f, s, c)
	if type(f) ~= "function" then
		local mt = getmetatable(f)

		if type(mt) == "table" and mt.__iter then
			f, s, c = mt.__iter(f)
		elseif type(f) == "table" then
			f, s, c = next, f, nil
		end
	end

	return function()
		local r = table.pack(f(s, c))

		if r[1] == nil then
			return false
		end

		c = r[1]

		return true, table.unpack(r, 1, r.n)
	end
end

local UserInputService = game:GetService("UserInputService")

FARM_RANGE = FARM_RANGE or 300
Range = Range or 100
ply = ply or game:GetService("Players")
Core = Core or {}
getgenv().Core = Core
ply = game.Players
plr = ply.LocalPlayer
Root = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")
replicated = game:GetService("ReplicatedStorage")
Lv = game.Players.LocalPlayer.Data.Level.Value
TeleportService = game:GetService("TeleportService")
TW = game:GetService("TweenService")
Lighting = game:GetService("Lighting")
Enemies = workspace.Enemies
vim1 = game:GetService("VirtualInputManager")
vim2 = game:GetService("VirtualUser")
TeamSelf = plr.Team
RunSer = game:GetService("RunService")
Stats = game:GetService("Stats")
Energy = plr.Character and plr.Character:FindFirstChild("Energy") and plr.Character.Energy.Value or 100
BringConnections = {}
BossList = {}
MaterialList = {}
NPCList = {}
PlrList = {}
shouldTween = false
getgenv().OnFarm = false
getgenv().AutoMaterial = false
NextIs = false
senth = false
senth2 = false
SoulGuitar = false
KenTest = true
debug = false
Brazier1 = false
Brazier2 = false
Brazier3 = false
Sec = 0.1
ClickState = 0
Num_self = 25

local Players = game:GetService("Players")

for _, player in pairs(Players:GetPlayers()) do
	table.insert(PlrList, player.Name)
end

do
	game:GetService("Players").PlayerAdded:Connect(function(player)
		table.insert(PlrList, player.Name)
	end)
end

game:GetService("Players").PlayerRemoving:Connect(function(player)
	local v8 = table.find(PlrList, player.Name)

	if v8 then
		table.remove(PlrList, v8)
	end
end)
PrehisUser = {
	Find = false,
	Skills = false,
	DE = false
}

do
	plr.CharacterAdded:Connect(function(character)
		local HumanoidRootPart = character:WaitForChild("HumanoidRootPart", 15)

		if HumanoidRootPart then
			Root = HumanoidRootPart
		end
	end)
end

local Loading

repeat
	Loading = plr.PlayerGui:WaitForChild("Main"):WaitForChild("Loading") and game:IsLoaded()
	task.wait()
until Loading

World1 = game.PlaceId == 2753915549 or game.PlaceId == 85211729168715
World2 = game.PlaceId == 4442272183 or game.PlaceId == 79091703265657
World3 = game.PlaceId == 7449423635 or game.PlaceId == 100117331123089
Marines = function()
	replicated.Remotes.CommF_:InvokeServer("SetTeam", "Marines")
end
Pirates = function()
	replicated.Remotes.CommF_:InvokeServer("SetTeam", "Pirates")
end

if World1 then
	BossList = {
		"The Gorilla King",
		"Bobby",
		"The Saw",
		"Yeti",
		"Mob Leader",
		"Vice Admiral",
		"Saber Expert",
		"Warden",
		"Chief Warden",
		"Swan",
		"Magma Admiral",
		"Fishman Lord",
		"Wysper",
		"Thunder God",
		"Cyborg",
		"Ice Admiral",
		"Greybeard"
	}
elseif World2 then
	BossList = {
		"Diamond",
		"Jeremy",
		"Orbitus",
		"Don Swan",
		"Smoke Admiral",
		"Awakened Ice Admiral",
		"Tide Keeper",
		"Darkbeard",
		"Cursed Captain",
		"Order"
	}
elseif World3 then
	BossList = {
		"Stone",
		"Hydra Leader",
		"Kilo Admiral",
		"Captain Elephant",
		"Beautiful Pirate",
		"Cake Queen",
		"Dough King",
		"Longma",
		"Soul Reaper",
		"rip_indra True Form",
		"Tyrant of the Skies"
	}
end

if World1 then
	MaterialList = {
		"Leather + Scrap Metal",
		"Angel Wings",
		"Magma Ore",
		"Fish Tail"
	}
elseif World2 then
	MaterialList = {
		"Leather + Scrap Metal",
		"Radioactive Material",
		"Ectoplasm",
		"Mystic Droplet",
		"Magma Ore",
		"Vampire Fang"
	}
elseif World3 then
	MaterialList = {
		"Scrap Metal",
		"Demonic Wisp",
		"Conjured Cocoa",
		"Dragon Scale",
		"Gunpowder",
		"Fish Tail",
		"Mini Tusk"
	}
end

DungeonTables = {
	"Flame",
	"Ice",
	"Quake",
	"Light",
	"Dark",
	"String",
	"Rumble",
	"Magma",
	"Human: Buddha",
	"Sand",
	"Bird: Phoenix",
	"Dough"
}
RenMon = {
	"Snow Lurker",
	"Arctic Warrior",
	"Hidden Key",
	"Awakened Ice Admiral"
}
CursedTables = {
	"Hell's Messenger",
	"Heaven's Guardian",
	Mob = "Mythological Pirate",
	Mob2 = "Cursed Skeleton",
	Mob3 = "Cursed Skeleton"
}
Past = {
	"Part",
	"SpawnLocation",
	"Terrain",
	"WedgePart",
	"MeshPart"
}
BartMon = {
	"Swan Pirate",
	"Jeremy"
}
CitizenTable = {
	"Forest Pirate",
	"Captain Elephant"
}
Human_v3_Mob = {
	"Fajita",
	"Jeremy",
	"Diamond"
}
AllBoats = {
	"Beast Hunter",
	"Lantern",
	"Guardian",
	"Grand Brigade",
	"Dinghy",
	"Sloop",
	"The Sentinel"
}
mastery1 = { "Cookie Crafter" }
mastery2 = { "Reborn Skeleton" }
PosMsList = {
	["Pirate Millionaire"] = CFrame.new(-712.8272705078125, 98.577049255371094, 5711.9541015625),
	["Pistol Billionaire"] = CFrame.new(-723.43316650390625, 147.42906188964844, 5931.9931640625),
	["Dragon Crew Warrior"] = CFrame.new(7021.50439453125, 55.762702941894531, -730.12908935546875),
	["Dragon Crew Archer"] = CFrame.new(6625, 378, 244),
	["Female Islander"] = CFrame.new(4692.7939453125, 797.9766845703125, 858.8480224609375),
	["Venomous Assailant"] = CFrame.new(4902, 670, 39),
	["Marine Commodore"] = CFrame.new(2401, 123, -7589),
	["Marine Rear Admiral"] = CFrame.new(3588, 229, -7085),
	["Fishman Raider"] = CFrame.new(-10941, 332, -8760),
	["Fishman Captain"] = CFrame.new(-11035, 332, -9087),
	["Forest Pirate"] = CFrame.new(-13446, 413, -7760),
	["Mythological Pirate"] = CFrame.new(-13510, 584, -6987),
	["Jungle Pirate"] = CFrame.new(-11778, 426, -10592),
	["Musketeer Pirate"] = CFrame.new(-13282, 496, -9565),
	["Reborn Skeleton"] = CFrame.new(-8764, 142, 5963),
	["Living Zombie"] = CFrame.new(-10227, 421, 6161),
	["Demonic Soul"] = CFrame.new(-9579, 6, 6194),
	["Posessed Mummy"] = CFrame.new(-9579, 6, 6194),
	["Peanut Scout"] = CFrame.new(-1993, 187, -10103),
	["Peanut President"] = CFrame.new(-2215, 159, -10474),
	["Ice Cream Chef"] = CFrame.new(-877, 118, -11032),
	["Ice Cream Commander"] = CFrame.new(-877, 118, -11032),
	["Cookie Crafter"] = CFrame.new(-2021, 38, -12028),
	["Cake Guard"] = CFrame.new(-2024, 38, -12026),
	["Baking Staff"] = CFrame.new(-1932, 38, -12848),
	["Head Baker"] = CFrame.new(-1932, 38, -12848),
	["Cocoa Warrior"] = CFrame.new(95, 73, -12309),
	["Chocolate Bar Battler"] = CFrame.new(647, 42, -12401),
	["Sweet Thief"] = CFrame.new(116, 36, -12478),
	["Candy Rebel"] = CFrame.new(47, 61, -12889),
	Ghost = CFrame.new(5251, 5, 1111)
}
Remotes = {
	RFJobsRemoteFunction = replicated.Modules.Net["RF/JobsRemoteFunction"],
	RFCraft = replicated:WaitForChild("Modules"):WaitForChild("Net"):WaitForChild("RF/Craft")
}
EquipWeapon = function(p1)
	if not p1 then
		return
	end

	if plr.Backpack:FindFirstChild(p1) then
		plr.Character.Humanoid:EquipTool(plr.Backpack:FindFirstChild(p1))
	end
end
weaponSc = function(p2)
	for _, child in pairs(plr.Backpack:GetChildren()) do
		if child:IsA("Tool") and child.ToolTip == p2 then
			EquipWeapon(child.Name)
		end
	end
end
Attack = {}
Attack.__index = Attack
Attack.Alive = function(p3)
	if not p3 then
		return false
	end

	local Humanoid = p3:FindFirstChild("Humanoid")
	local HumanoidRootPart = p3:FindFirstChild("HumanoidRootPart")

	return Humanoid ~= nil and Humanoid.Health > 0 and HumanoidRootPart ~= nil
end
Attack.Pos = function(p4, p5)
	return (Root.Position - p4.Position).Magnitude <= p5
end
Attack.Dist = function(p6, p7)
	local HumanoidRootPart = p6 and p6:FindFirstChild("HumanoidRootPart")

	return HumanoidRootPart and (Root.Position - HumanoidRootPart.Position).Magnitude <= p7 or false
end
Attack.DistH = function(p8, p9)
	local HumanoidRootPart = p8 and p8:FindFirstChild("HumanoidRootPart")

	return HumanoidRootPart and (Root.Position - HumanoidRootPart.Position).Magnitude > p9 or false
end
Attack.Kill = function(p10, p11)
	if p10 and p11 then
		local HumanoidRootPart = p10:FindFirstChild("HumanoidRootPart")

		if not HumanoidRootPart then
			return
		end

		if not p10:GetAttribute("Locked") then
			p10:SetAttribute("Locked", HumanoidRootPart.CFrame)
		end

		PosMon = p10:GetAttribute("Locked").Position
		BringEnemy()
		EquipWeapon(_G.SelectWeapon)

		local Tool = game.Players.LocalPlayer.Character:FindFirstChildOfClass("Tool")
		local ToolTip = Tool and Tool:FindFirstChild("ToolTip") and Tool.ToolTip

		if (ToolTip or "") == "Blox Fruit" then
			_tp(HumanoidRootPart.CFrame * CFrame.new(0, 30, 0) * CFrame.Angles(0, math.rad(90), 0))
		else
			_tp(HumanoidRootPart.CFrame * CFrame.new(0, 10, 0) * CFrame.Angles(0, math.rad(180), 0))
		end

		if RandomCFrame then
			task.wait(0.5)
			_tp(HumanoidRootPart.CFrame * CFrame.new(0, 30, 25))
			task.wait(0.5)
			_tp(HumanoidRootPart.CFrame * CFrame.new(25, 30, 0))
			task.wait(0.5)
			_tp(HumanoidRootPart.CFrame * CFrame.new(-25, 30, 0))
			task.wait(0.5)
			_tp(HumanoidRootPart.CFrame * CFrame.new(0, 30, 25))
			task.wait(0.5)
			_tp(HumanoidRootPart.CFrame * CFrame.new(-25, 30, 0))
		end
	end
end
Attack.Kill2 = function(p12, p13)
	if p12 and p13 then
		if not p12:GetAttribute("Locked") then
			p12:SetAttribute("Locked", p12.HumanoidRootPart.CFrame)
		end

		PosMon = p12:GetAttribute("Locked").Position
		BringEnemy()
		EquipWeapon(_G.SelectWeapon)

		local Tool = game.Players.LocalPlayer.Character:FindFirstChildOfClass("Tool")

		if (Tool and Tool:FindFirstChild("ToolTip") and Tool.ToolTip or "") == "Blox Fruit" then
			_tp(p12.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0) * CFrame.Angles(0, math.rad(90), 0))
		else
			_tp(p12.HumanoidRootPart.CFrame * CFrame.new(0, 10, 8) * CFrame.Angles(0, math.rad(180), 0))
		end

		if RandomCFrame then
			task.wait(0.1)
			_tp(p12.HumanoidRootPart.CFrame * CFrame.new(0, 30, 25))
			task.wait(0.1)
			_tp(p12.HumanoidRootPart.CFrame * CFrame.new(25, 30, 0))
			task.wait(0.1)
			_tp(p12.HumanoidRootPart.CFrame * CFrame.new(-25, 30, 0))
			task.wait(0.1)
			_tp(p12.HumanoidRootPart.CFrame * CFrame.new(0, 30, 25))
			task.wait(0.1)
			_tp(p12.HumanoidRootPart.CFrame * CFrame.new(-25, 30, 0))
		end
	end
end
Attack.KillSea = function(p14, p15)
	if p14 and p15 then
		if not p14:GetAttribute("Locked") then
			p14:SetAttribute("Locked", p14.HumanoidRootPart.CFrame)
		end

		PosMon = p14:GetAttribute("Locked").Position
		BringEnemy()
		EquipWeapon(_G.SelectWeapon)

		local Tool = game.Players.LocalPlayer.Character:FindFirstChildOfClass("Tool")

		if (Tool and Tool:FindFirstChild("ToolTip") and Tool.ToolTip or "") == "Blox Fruit" then
			_tp(p14.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0) * CFrame.Angles(0, math.rad(90), 0))
		else
			notween(p14.HumanoidRootPart.CFrame * CFrame.new(0, 50, 8))
			task.wait(0.85)
			notween(p14.HumanoidRootPart.CFrame * CFrame.new(0, 400, 0))
			task.wait(1)
		end
	end
end

do
	Attack.Sword = function(p16, p17)
		if p16 and p17 then
			if not p16:GetAttribute("Locked") then
				p16:SetAttribute("Locked", p16.HumanoidRootPart.CFrame)
			end

			PosMon = p16:GetAttribute("Locked").Position
			BringEnemy()
			weaponSc("Sword")
			_tp(p16.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))

			if RandomCFrame then
				task.wait(0.1)
				_tp(p16.HumanoidRootPart.CFrame * CFrame.new(0, 30, 25))
				task.wait(0.1)
				_tp(p16.HumanoidRootPart.CFrame * CFrame.new(25, 30, 0))
				task.wait(0.1)
				_tp(p16.HumanoidRootPart.CFrame * CFrame.new(-25, 30, 0))
				task.wait(0.1)
				_tp(p16.HumanoidRootPart.CFrame * CFrame.new(0, 30, 25))
				task.wait(0.1)
				_tp(p16.HumanoidRootPart.CFrame * CFrame.new(-25, 30, 0))
			end
		end
	end
end

Attack.Mas = function(p18, p19)
	if p18 and p19 then
		if not p18:GetAttribute("Locked") then
			p18:SetAttribute("Locked", p18.HumanoidRootPart.CFrame)
		end

		PosMon = p18:GetAttribute("Locked").Position
		BringEnemy()

		if p18.Humanoid.Health <= HealthM then
			weaponSc("Blox Fruit")
			_tp(p18.HumanoidRootPart.CFrame * CFrame.new(0, 20, 0))

			local SelectedMasterySkills = _G.SelectedMasterySkills

			if type(SelectedMasterySkills) == "string" then
				SelectedMasterySkills = { SelectedMasterySkills }
			elseif type(SelectedMasterySkills) ~= "table" then
				SelectedMasterySkills = {
					"Z",
					"X",
					"C",
					"V",
					"F"
				}
			end

			for k, SelectedMasterySkill in pairs(SelectedMasterySkills) do
				if type(k) == "number" and type(SelectedMasterySkill) == "string" then
					Useskills("Blox Fruit", SelectedMasterySkill)
				elseif type(k) == "string" and SelectedMasterySkill == true then
					Useskills("Blox Fruit", k)
				end
			end
		else
			weaponSc("Melee")
			_tp(p18.HumanoidRootPart.CFrame * CFrame.new(0, 10, 0))
		end
	end
end
Attack.Masgun = function(p20, p21)
	if p20 and p21 then
		if not p20:GetAttribute("Locked") then
			p20:SetAttribute("Locked", p20.HumanoidRootPart.CFrame)
		end

		PosMon = p20:GetAttribute("Locked").Position
		BringEnemy()

		if p20.Humanoid.Health <= HealthM then
			weaponSc("Gun")
			_tp(p20.HumanoidRootPart.CFrame * CFrame.new(0, 35, 8))

			local SelectedMasterySkills = _G.SelectedMasterySkills

			if type(SelectedMasterySkills) == "string" then
				SelectedMasterySkills = { SelectedMasterySkills }
			elseif type(SelectedMasterySkills) ~= "table" then
				SelectedMasterySkills = {
					"Z",
					"X",
					"C",
					"V",
					"F"
				}
			end

			for k, SelectedMasterySkill in pairs(SelectedMasterySkills) do
				if type(k) == "number" and type(SelectedMasterySkill) == "string" then
					Useskills("Gun", SelectedMasterySkill)
				elseif type(k) == "string" then
					if SelectedMasterySkill == true then
						Useskills("Gun", k)
					end
				end
			end
		else
			weaponSc("Melee")
			_tp(p20.HumanoidRootPart.CFrame * CFrame.new(0, 10, 0))
		end
	end
end
statsSetings = function(p22, p23)
	if p22 ~= "Melee" then
		if p22 ~= "Defense" then
			if p22 ~= "Sword" then
				if p22 ~= "Gun" then
					if p22 == "Devil" and plr.Data.Points.Value ~= 0 then
						replicated.Remotes.CommF_:InvokeServer("AddPoint", "Demon Fruit", p23)
					end
				elseif plr.Data.Points.Value ~= 0 then
					replicated.Remotes.CommF_:InvokeServer("AddPoint", "Gun", p23)
				end
			elseif plr.Data.Points.Value ~= 0 then
				replicated.Remotes.CommF_:InvokeServer("AddPoint", "Sword", p23)
			end
		elseif plr.Data.Points.Value ~= 0 then
			replicated.Remotes.CommF_:InvokeServer("AddPoint", "Defense", p23)
		end
	elseif plr.Data.Points.Value ~= 0 then
		replicated.Remotes.CommF_:InvokeServer("AddPoint", "Melee", p23)
	end
end
BringEnemy = function(p24)
	if not _B then
		return
	end

	if not p24 then
		local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

		if not HumanoidRootPart then
			return
		end

		local huge = math.huge

		for _, child in ipairs(workspace.Enemies:GetChildren()) do
			local Humanoid = child:FindFirstChildOfClass("Humanoid")
			local HumanoidRootPart2 = child:FindFirstChild("HumanoidRootPart")

			if Humanoid and HumanoidRootPart2 and Humanoid.Health > 0 then
				local Magnitude = (HumanoidRootPart2.Position - HumanoidRootPart.Position).Magnitude

				if Magnitude < huge then
					huge = Magnitude
					p24 = child
				end
			end
		end

		if not p24 then
			return
		end
	end

	local u35 = false

	Mobs = function(p25)
		local Humanoid = p25:FindFirstChildOfClass("Humanoid")
		local HumanoidRootPart = p25:FindFirstChild("HumanoidRootPart")

		return Humanoid and HumanoidRootPart and Humanoid.Health > 0, HumanoidRootPart, Humanoid
	end
	Network = function(p26)
		if isnetworkowner then
			return isnetworkowner(p26)
		end

		return p26.ReceiveAge == 0 and not p26.Anchored and p26.Velocity.Magnitude > 0
	end
	pcall(function()
		if sethiddenproperty then
			sethiddenproperty(plr, "SimulationRadius", math.huge)
		end

		local Position = p24.HumanoidRootPart.Position

		for _, child in ipairs(workspace.Enemies:GetChildren()) do
			if child ~= p24 then
				local v41, v42, v43 = Mobs(child)

				if v41 and child.Name == p24.Name then
					local Magnitude = (v42.Position - Position).Magnitude

					if Magnitude <= 3000 then
						if not v42:FindFirstChild("BodyVelocity") then
							local BodyVelocity = Instance.new("BodyVelocity")

							BodyVelocity.Name = "BodyVelocity"
							BodyVelocity.MaxForce = Vector3.new(1e9, 1e9, 1e9)
							BodyVelocity.Velocity = Vector3.zero
							BodyVelocity.Parent = v42
						end

						if Magnitude <= 10 then
							u35 = true
						end

						if not u35 and Network(v42) then
							v42.CFrame = CFrame.new(Position)
						end

						v42.CanCollide = false
						v43.WalkSpeed = 0
						v43.JumpPower = 0
					end
				end
			end
		end

		if p24 then
			if p24:FindFirstChild("HumanoidRootPart") then
				p24.HumanoidRootPart.CanCollide = false
				p24.Humanoid.WalkSpeed = 0
				p24.Humanoid.JumpPower = 0
			end
		end
	end)
end
IsSkillReady = function(p27, p28)
	local LocalPlayer = game.Players.LocalPlayer
	local Name

	if LocalPlayer.Character then
		for _, child in pairs(LocalPlayer.Character:GetChildren()) do
			if child:IsA("Tool") and child.ToolTip == p27 then
				Name = child.Name

				break
			end
		end
	end

	if not Name and LocalPlayer.Backpack then
		for _, child in pairs(LocalPlayer.Backpack:GetChildren()) do
			if child:IsA("Tool") and child.ToolTip == p27 then
				Name = child.Name

				break
			end
		end
	end

	if Name then
		if LocalPlayer.PlayerGui:FindFirstChild("Main") then
			if LocalPlayer.PlayerGui.Main:FindFirstChild("Skills") then
				local v52 = LocalPlayer.PlayerGui.Main.Skills:FindFirstChild(Name)

				if v52 then
					local v53 = v52:FindFirstChild(p28)

					if v53 then
						local Lock = v53:FindFirstChild("Lock") or v53:FindFirstChild("Locked")

						if Lock and Lock.Visible then
							return false
						end

						local Cooldown = v53:FindFirstChild("Cooldown")

						if Cooldown and Cooldown.Visible and (Cooldown.Size.X.Scale > 0.05 or Cooldown.AbsoluteSize.X > 5) then
							return false
						end

						return true
					end
				end
			end
		end
	end

	return true
end
Useskills = function(p29, p30)
	if p29 == "Melee" then
		weaponSc("Melee")

		if not IsSkillReady(p29, p30) then
			return
		end

		vim1:SendKeyEvent(true, p30, false, game)
		task.wait(0.04)
		vim1:SendKeyEvent(false, p30, false, game)
		task.wait(0.04)
	elseif p29 == "Sword" then
		weaponSc("Sword")

		if not IsSkillReady(p29, p30) then
			return
		end

		vim1:SendKeyEvent(true, p30, false, game)
		task.wait(0.04)
		vim1:SendKeyEvent(false, p30, false, game)
		task.wait(0.04)
	elseif p29 == "Blox Fruit" then
		weaponSc("Blox Fruit")

		if not IsSkillReady(p29, p30) then
			return
		end

		vim1:SendKeyEvent(true, p30, false, game)
		task.wait(0.04)
		vim1:SendKeyEvent(false, p30, false, game)
		task.wait(0.04)
	elseif p29 == "Gun" then
		weaponSc("Gun")

		if not IsSkillReady(p29, p30) then
			return
		end

		vim1:SendKeyEvent(true, p30, false, game)
		task.wait(0.04)
		vim1:SendKeyEvent(false, p30, false, game)
		task.wait(0.04)
	end

	if p29 == "nil" and p30 == "Y" then
		vim1:SendKeyEvent(true, "Y", false, game)
		task.wait(0.04)
		vim1:SendKeyEvent(false, "Y", false, game)
		task.wait(0.04)
	end
end

do
	local v56 = getrawmetatable(game)
	local __namecall = v56.__namecall

	setreadonly(v56, false)
	v56.__namecall = newcclosure(function(...)
		local v58 = getnamecallmethod()
		local t1 = { ... }

		if tostring(v58) == "FireServer" and tostring(t1[1]) == "RemoteEvent" then
			if tostring(t1[2]) ~= "true" then
				if tostring(t1[2]) ~= "false" and (_G.FarmMastery_G and not SoulGuitar or _G.FarmMastery_Dev or _G.FarmBlazeEM or _G.Prehis_Skills or _G.SeaBeast1 or _G.FishBoat or _G.PGB or _G.Leviathan1 or _G.Complete_Trials or _G.AimMethod and ABmethod == "Aim Player" or _G.AimMethod and ABmethod == "Nearest Aim") then
					t1[2] = MousePos

					return __namecall(unpack(t1))
				end
			end
		end

		return __namecall(...)
	end)
end

do
	GetNearestEnemy = function(p31)
		local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

		if not HumanoidRootPart then
			return nil
		end

		local v61
		local v62

		for _, child in ipairs(workspace.Enemies:GetChildren()) do
			if child:IsA("Model") and (typeof(p31) == "table" and table.find(p31, child.Name) or child.Name == p31) then
				local Humanoid = child:FindFirstChild("Humanoid")
				local HumanoidRootPart2 = child:FindFirstChild("HumanoidRootPart")

				if Humanoid and HumanoidRootPart2 and Humanoid.Health > 0 then
					local Magnitude = (HumanoidRootPart2.Position - HumanoidRootPart.Position).Magnitude

					if not v62 or Magnitude < v62 then
						v61 = child
						v62 = Magnitude
					end
				end
			end
		end

		return v61, v62
	end
end

GetConnectionEnemies = function(p32)
	local Character = plr.Character

	Character = Character and plr.Character:FindFirstChild("HumanoidRootPart")
	search = function(p33)
		local v69
		local v70

		for _, child in ipairs(p33:GetChildren()) do
			if child:IsA("Model") and (typeof(p32) == "table" and table.find(p32, child.Name) or child.Name == p32) then
				local Humanoid = child:FindFirstChild("Humanoid")

				if Humanoid then
					if Humanoid.Health > 0 then
						local HumanoidRootPart = child:FindFirstChild("HumanoidRootPart")
						local Magnitude = Character and HumanoidRootPart and (HumanoidRootPart.Position - Character.Position).Magnitude or math.huge

						if not v69 or Magnitude < v70 then
							v69 = child
							v70 = Magnitude
						end
					end
				end
			end
		end

		return v69
	end

	local v76 = search(workspace.Enemies) or search(replicated)

	return v76
end
LowCpu = function()
	local Terrain = game.Workspace.Terrain

	Terrain.WaterWaveSize = 0
	Terrain.WaterWaveSpeed = 0
	Terrain.WaterReflectance = 0
	Terrain.WaterTransparency = 0
	game.Lighting.GlobalShadows = false
	game.Lighting.FogEnd = 9e9
	game.Lighting.Brightness = 0
	settings().Rendering.QualityLevel = "Level01"

	for _, descendant in pairs(game:GetDescendants()) do
		if not descendant:IsA("Part") and not descendant:IsA("Union") then
			if not descendant:IsA("CornerWedgePart") and not descendant:IsA("TrussPart") then
				if not descendant:IsA("Decal") then
					if not descendant:IsA("Texture") then
						if descendant:IsA("ParticleEmitter") or descendant:IsA("Trail") then
							descendant.Lifetime = NumberRange.new(0)
						elseif descendant:IsA("Explosion") then
							descendant.BlastPressure = 1
							descendant.BlastRadius = 1
						elseif descendant:IsA("Fire") or descendant:IsA("SpotLight") or descendant:IsA("Smoke") or descendant:IsA("Sparkles") then
							descendant.Enabled = false
						elseif descendant:IsA("MeshPart") then
							descendant.Material = "Plastic"
							descendant.Reflectance = 0
							descendant.TextureID = 10385902758728956
						end

						continue
					end
				end

				descendant.Transparency = 1

				continue
			end
		end

		descendant.Material = "Plastic"
		descendant.Reflectance = 0
	end

	for _, child in pairs(game.Lighting:GetChildren()) do
		if child:IsA("BlurEffect") or child:IsA("SunRaysEffect") or child:IsA("ColorCorrectionEffect") or child:IsA("BloomEffect") or child:IsA("DepthOfFieldEffect") then
			child.Enabled = false
		end
	end
end
CheckF = function()
	if not GetBP("Dragon-Dragon") and not GetBP("Gas-Gas") and not GetBP("Yeti-Yeti") then
		if not GetBP("Kitsune-Kitsune") and not GetBP("T-Rex-T-Rex") then
			return
		end
	end

	return true
end
CheckBoat = function()
	for _, child in pairs(workspace.Boats:GetChildren()) do
		if tostring(child.Owner.Value) == tostring(plr.Name) then
			return child
		end
	end

	return false
end
CheckEnemiesBoat = function()
	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if child.Name == "FishBoat" and child:FindFirstChild("Health").Value > 0 then
			return true
		end
	end

	return false
end

do
	CheckPirateGrandBrigade = function()
		for _, child in pairs(workspace.Enemies:GetChildren()) do
			if (child.Name == "PirateGrandBrigade" or child.Name == "PirateBrigade") and child:FindFirstChild("Health").Value > 0 then
				return true
			end
		end

		return false
	end
end

CheckShark = function()
	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if child.Name == "Shark" and Attack.Alive(child) then
			return true
		end
	end

	return false
end
CheckTerrorShark = function()
	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if child.Name ~= "Terrorshark" then
			continue
		end

		if Attack.Alive(child) then
			return true
		end
	end

	return false
end
CheckPiranha = function()
	local v92, v93, v94 = pairs(workspace.Enemies:GetChildren())
	local v95 = geniter(v92, v93, v94)
	local v96

	while true do
		local v97 = table.pack(v95())

		if v97[1] then
			v96 = v97[3]

			if v96.Name == "Piranha" then
				break
			end
		else
			return false
		end
	end

	while not Attack.Alive(v96) do
		while true do
			local v98 = table.pack(v95())

			if v98[1] then
				v96 = v98[3]

				if v96.Name == "Piranha" then
					break
				end
			else
				return false
			end
		end
	end

	return true
end
CheckFishCrew = function()
	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if (child.Name == "Fish Crew Member" or child.Name == "Haunted Crew Member") and Attack.Alive(child) then
			return true
		end
	end

	return false
end
CheckHauntedCrew = function()
	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if child.Name == "Haunted Crew Member" and Attack.Alive(child) then
			return true
		end
	end

	return false
end
CheckSeaBeast = function()
	if workspace.SeaBeasts:FindFirstChild("SeaBeast1") then
		return true
	end

	return false
end
CheckLeviathan = function()
	if workspace.SeaBeasts:FindFirstChild("Leviathan") then
		return true
	end

	return false
end

do
	UpdStFruit = function()
		local children, v104 = plr.Backpack:GetChildren()

		for _, v in next, children, v104 do
			StoreFruit = v:FindFirstChild("EatRemote", true)

			if StoreFruit then
				replicated.Remotes.CommF_:InvokeServer("StoreFruit", StoreFruit.Parent:GetAttribute("OriginalName"), plr.Backpack:FindFirstChild(v.Name))
			end
		end
	end
end

do
	GetNearestFruit = function()
		local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

		if not HumanoidRootPart then
			return nil
		end

		local v108
		local v109

		for _, child in pairs(workspace:GetChildren()) do
			if string.find(child.Name, "Fruit") then
				local Handle = child:FindFirstChild("Handle")

				if Handle and Handle:IsA("BasePart") then
					local Magnitude = (Handle.Position - HumanoidRootPart.Position).Magnitude

					if not v109 or Magnitude < v109 then
						v108 = Handle
						v109 = Magnitude
					end
				end
			end
		end

		return v108
	end
end

collectFruits = function(p34)
	if p34 then
		local Character = plr.Character
		local HumanoidRootPart = Character and Character:FindFirstChild("HumanoidRootPart")

		if not HumanoidRootPart then
			return
		end

		for _, child in pairs(workspace:GetChildren()) do
			if string.find(child.Name, "Fruit") then
				local Handle = child:FindFirstChild("Handle")

				if Handle then
					Handle.CFrame = HumanoidRootPart.CFrame
				end
			end
		end
	end
end
Getmoon = function()
	if World1 then
		return Lighting.FantasySky.MoonTextureId
	end

	if World2 then
		return Lighting.FantasySky.MoonTextureId
	end

	if World3 then
		return Lighting.Sky.MoonTextureId
	end
end
DropFruits = function()
	local children, v120 = plr.Backpack:GetChildren()

	for _, v in next, children, v120 do
		if string.find(v.Name, "Fruit") then
			EquipWeapon(v.Name)
			task.wait(0.1)

			if plr.PlayerGui.Main.Dialogue.Visible == true then
				plr.PlayerGui.Main.Dialogue.Visible = false
			end

			EquipWeapon(v.Name)
			plr.Character:FindFirstChild(v.Name).EatRemote:InvokeServer("Drop")
		end
	end

	for _, child in pairs(plr.Character:GetChildren()) do
		if string.find(child.Name, "Fruit") then
			EquipWeapon(child.Name)
			task.wait(0.1)

			if plr.PlayerGui.Main.Dialogue.Visible == true then
				plr.PlayerGui.Main.Dialogue.Visible = false
			end

			EquipWeapon(child.Name)
			plr.Character:FindFirstChild(child.Name).EatRemote:InvokeServer("Drop")
		end
	end
end
GetBP = function(p35)
	return plr.Backpack:FindFirstChild(p35) or plr.Character:FindFirstChild(p35)
end

do
	local t2 = {
		t = 0,
		data = nil
	}

	GetInventoryList = function()
		if t2.data then
			if tick() - t2.t < 2 then
				return t2.data
			end
		end

		local v126
		local ok, result = pcall(function()
			return replicated.Remotes.CommF_:InvokeServer("getInventory")
		end)

		if ok and type(result) == "table" then
			v126 = result
		end

		if not v126 then
			local ok2, result2 = pcall(function()
				return replicated.Remotes.CommF_:InvokeServer("getInventoryWeapons")
			end)

			if ok2 and type(result2) == "table" then
				v126 = result2
			end
		end

		local data = v126 or {}

		t2.t = tick()
		t2.data = data

		return data
	end
end

do
	GetIn = function(p36)
		if not plr.Character:FindFirstChild(p36) then
			if not plr.Backpack:FindFirstChild(p36) then
				for _, v in pairs(GetInventoryList()) do
					if type(v) == "table" and v.Name == p36 then
						return true
					end
				end

				return false
			end
		end

		return true
	end
end

GetM = function(p37)
	if p37 == "Bones" then
		local ok, result = pcall(function()
			return replicated.Remotes.CommF_:InvokeServer("Bones", "Check")
		end)
		local v136 = ok and tonumber(result) or 0

		return v136
	end

	local ok, result = pcall(function()
		local v139 = require(replicated.IdMap).Material[p37]

		if v139 then
			return require(replicated.Util.ItemReplication).Quantity.readClient(v139)
		end
	end)

	if ok and tonumber(result) then
		return tonumber(result)
	end

	for _, v in pairs(GetInventoryList()) do
		if type(v) ~= "table" or v.Type ~= "Material" or v.Name ~= p37 then
			continue
		end

		return v.Count
	end

	return 0
end
GetWP = function(p38)
	local ok = not plr.Character

	if not ok then
		ok = not plr.Character:FindFirstChild(p38)
	end

	if not ok then
		return true
	end

	if plr.Backpack then
		if plr.Backpack:FindFirstChild(p38) then
			return true
		end
	end

	for _, v in pairs(GetInventoryList()) do
		if type(v) == "table" and v.Type == "Sword" and v.Name == p38 then
			return true
		end
	end

	return false
end

do
	local t3 = {
		t = 0,
		v = nil
	}

	CDKProgress = function()
		if t3.v and tick() - t3.t < 0.4 then
			return t3.v
		end

		local ok, v147 = pcall(function()
			return replicated.Remotes.CommF_:InvokeServer("CDKQuest", "Progress")
		end)

		if ok and type(v147) == "table" then
			t3.v = v147
			t3.t = tick()
		end

		return t3.v
	end
end

getgenv().CDKDoorOpenedAt = nil
CDKEnsureDoor = function()
	if getgenv().CDKDoorOpenedAt then
		return true
	end

	if tick() - (getgenv().CDKDoorTry or 0) < 1 then
		return false
	end

	getgenv().CDKDoorTry = tick()

	local ok, result = pcall(function()
		return replicated.Remotes.CommF_:InvokeServer("CDKQuest", "OpenDoor")
	end)

	if not ok or tostring(result) ~= "opened" then
		pcall(function()
			replicated.Remotes.CommF_:InvokeServer("CDKQuest", "OpenDoor", true)
		end)

		return false
	end

	getgenv().CDKDoorOpenedAt = tick()

	return true
end
getInfinity_Ability = function(p39, p40)
	if not Root then
		return
	end

	if p39 == "Soru" and p40 then
		local next_ = next
		local v151, v152 = getgc()

		for _, v in next_, v151, v152 do
			if plr.Character.Soru and typeof(v) == "function" then
				if getfenv(v).script == plr.Character.Soru then
					local next_2 = next
					local v156, v157 = getupvalues(v)

					for _, v2 in next_2, v156, v157 do
						if typeof(v2) == "table" then
							repeat
								task.wait(Sec)
								v2.LastUse = 0
							until plr.Character.Humanoid.Health <= 0
						end
					end
				end
			end
		end
	elseif p39 == "Energy" and p40 then
		plr.Character.Energy.Changed:connect(function()
			if p40 then
				plr.Character.Energy.Value = Energy
			end
		end)
	elseif p39 == "Observation" then
		if p40 then
			plr.VisionRadius.Value = math.huge
		end
	end
end
Hop = function()
	pcall(function()
		for i = math.random(1, math.random(40, 75)), 100 do
			for k, v in next, replicated.__ServerBrowser:InvokeServer(i), nil do
				if tonumber(v.Count) < 12 then
					TeleportService:TeleportToPlaceInstance(game.PlaceId, k)
				end
			end
		end
	end)
end

local Part = Instance.new("Part", workspace)

Part.Size = Vector3.new(1, 1, 1)
Part.Name = "Rip_Indra"
Part.Anchored = true
Part.CanCollide = false
Part.CanTouch = false
Part.Transparency = 1

for _, child in ipairs(workspace:GetChildren()) do
	if child.Name == Part.Name and child ~= Part then
		child:Destroy()
	end
end

local t4 = {
	Tween = nil,
	Target = nil
}

getgenv().LastTPCall = 0
task.spawn(function()
	while task.wait() do
		if not Part or Part.Parent ~= workspace then
			getgenv().OnFarm = false
		elseif shouldTween then
			getgenv().OnFarm = true
		else
			getgenv().OnFarm = false
		end
	end
end)
task.spawn(function()
	local LocalPlayer = game.Players.LocalPlayer

	while true do
		task.wait()

		if not LocalPlayer.Character then
			continue
		end

		if LocalPlayer.Character.PrimaryPart then
			break
		end
	end

	Part.CFrame = LocalPlayer.Character.PrimaryPart.CFrame

	while task.wait() do
		pcall(function()
			if Part then
				if Part.Parent == workspace then
					local PrimaryPart = LocalPlayer.Character and LocalPlayer.Character.PrimaryPart

					if getgenv().OnFarm then
						if not _G.WasOnFarm then
							_G.WasOnFarm = true
						end

						if PrimaryPart then
							if (PrimaryPart.Position - Part.Position).Magnitude <= 200 then
								PrimaryPart.CFrame = CFrame.new(Part.Position)
							else
								if t4.Tween then
									t4.Tween:Cancel()
								end

								t4.Target = nil
								Part.CFrame = PrimaryPart.CFrame
							end
						end

						local Character = LocalPlayer.Character

						if Character then
							for _, child in pairs(Character:GetChildren()) do
								if child:IsA("BasePart") then
									child.CanCollide = false
								end
							end
						end
					else
						if t4.Tween and t4.Tween.PlaybackState == Enum.PlaybackState.Playing then
							t4.Tween:Cancel()
						end

						t4.Target = nil

						if PrimaryPart then
							Part.CFrame = PrimaryPart.CFrame
						end

						if _G.WasOnFarm then
							_G.WasOnFarm = false

							local Character = LocalPlayer.Character

							if Character then
								for _, child in pairs(Character:GetChildren()) do
									if child:IsA("BasePart") then
										child.CanCollide = true
									end
								end
							end
						end
					end

					return
				end
			end
		end)
	end
end)

local ReplicatedStorage = game:GetService("ReplicatedStorage")

game:GetService("TweenService")
game:GetService("RunService")

local LocalPlayer = game:GetService("Players").LocalPlayer

sea1 = game.PlaceId == 2753915549 or game.PlaceId == 85211729168715
sea2 = game.PlaceId == 4442272183 or game.PlaceId == 79091703265657
sea3 = game.PlaceId == 7449423635 or game.PlaceId == 100117331123089

local t5 = {
	["Tween Speed"] = 200,
	["Bypass Teleport"] = false,
	["Up Y"] = false,
	["Up Y When Low Health"] = false,
	["Same Y"] = false
}
local cFrame = CFrame.new(10641.0918, -1953.92981, 9825.07031, -0.652825892, -9.2805891e-08, -0.757508039, -2.73638356e-08, 1, -9.89323823e-08, 0.757508039, -4.38572947e-08, -0.652825892)
local cFrame2 = CFrame.new(-16271.126, 25.5847301, 1371.98755, 0.999396622, -5.78875188e-08, -0.0347310975, 5.52972779e-08, 1, -8.7544322e-08, 0.034731105, 8.28877091e-08, 0.999396741)

Convert_CFrame = function(p41)
	if not p41 then
		return
	end

	if typeof(p41) == "Vector3" then
		return CFrame.new(p41)
	end

	if typeof(p41) == "CFrame" then
		return p41
	end

	if typeof(p41) == "Model" then
		return p41:GetPivot()
	end

	if p41.CFrame then
		return p41.CFrame
	end

	return nil
end
GetDistance = function(p42, p43, p44)
	if p42 == nil then
		return 9e9
	end

	local Character = LocalPlayer.Character

	if not Character then
		return 9e9
	end

	local Humanoid = Character:FindFirstChild("Humanoid")

	if not Humanoid or Humanoid.Health <= 0 then
		return 9e9
	end

	if p43 == nil then
		p43 = Character:FindFirstChild("HumanoidRootPart")

		if not p43 then
			return 9e9
		end
	end

	local v182 = Convert_CFrame(p42)
	local v183 = Convert_CFrame(p43)

	if p44 then
		return (Vector3.new(v182.X, 0, v182.Z) - Vector3.new(v183.X, 0, v183.Z)).Magnitude
	end

	return (v182.Position - v183.Position).Magnitude
end
InArea = function(p45)
	local _WorldOrigin = workspace:FindFirstChild("_WorldOrigin")

	if not _WorldOrigin then
		return {
			Name = ""
		}
	end

	local v185 = Convert_CFrame(p45)
	local children, v187 = _WorldOrigin.Locations:GetChildren()

	for _, v in next, children, v187 do
		if v:FindFirstChild("Mesh") and (v185.Position - v.Position).Magnitude <= v.Mesh.Scale.X then
			return v
		end
	end

	return {
		Name = ""
	}
end
GetSpawnPoint = function(p46)
	local Pirates_ = workspace:FindFirstChild("_WorldOrigin") and workspace._WorldOrigin:FindFirstChild("PlayerSpawns") and workspace._WorldOrigin.PlayerSpawns:FindFirstChild("Pirates")

	if not Pirates_ then
		return
	end

	local children, v192 = Pirates_:GetChildren()

	for _, v in next, children, v192 do
		if v:FindFirstChild("Part") and (v.Part.Position - p46.Position).Magnitude <= 2500 then
			return v
		end
	end
end
CheckLegendaryItems = function()
	CheckItem = function(p47)
		local children, v196 = LocalPlayer.Backpack:GetChildren()

		for _, v in next, children, v196 do
			if v:IsA("Tool") and (v.Name == p47 or string.find(v.Name, p47)) then
				return v
			end
		end

		local children2, v200 = LocalPlayer.Character:GetChildren()

		for _, v in next, children2, v200 do
			if v:IsA("Tool") and (v.Name == p47 or string.find(v.Name, p47)) then
				return v
			end
		end
	end

	if not CheckItem("God's Chalice") then
		if not CheckItem("Fist of Darkness") and not CheckItem("Sweet Chalice") and not CheckItem("Hallow Essence") and not CheckItem("Flower1") then
			return false
		end
	end

	return true
end
WaitForHumanoid = function()
	local Character = LocalPlayer.Character

	if not Character then
		return nil
	end

	local Humanoid = Character:FindFirstChild("Humanoid")

	if Humanoid then
		return Humanoid
	end

	local v205 = tick() + 5

	while tick() < v205 do
		local Humanoid2 = Character:FindFirstChild("Humanoid")

		if Humanoid2 then
			return Humanoid2
		end

		task.wait(0.1)
	end

	return nil
end
checkinventory = function(p48)
	if p48 then
		for _, v in pairs(GetInventoryList()) do
			if type(v) == "table" and v.Name == p48 then
				return true
			end
		end
	end

	return false
end
getdis = function(p49, p50)
	local CFrame_ = p50 or LocalPlayer.Character.HumanoidRootPart.CFrame

	return (CFrame.new(p49.X, CFrame_.Y, p49.Z).Position - CFrame.new(CFrame_.X, CFrame_.Y, CFrame_.Z).Position).Magnitude
end
CanBypassTeleport = function(p51)
	local Name = InArea(p51).Name

	if Name == "" then
		return false
	end

	if t5["Bypass Teleport"] and not Name:find("Dimension") and not Name:find("Submerged") and Name ~= "Sealed Cavern" then
		if not Name:lower():find("under") and not CheckLegendaryItems() then
			if LocalPlayer.Data and LocalPlayer.Data.LastSpawnPoint and LocalPlayer.Data.LastSpawnPoint.Value == "SubmergedIsland" then
				return false
			end

			if GetDistance(p51.Position) <= 3500 then
				return false
			end

			return true
		end
	end

	return false
end
GetBypassCFrame = function(p52)
	local huge = math.huge
	local v212
	local children = workspace._WorldOrigin.PlayerSpawns.Pirates:GetChildren()
	local HumanoidRootPart = LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("HumanoidRootPart")

	if not HumanoidRootPart then
		return nil
	end

	for _, v in next, children, nil do
		if v:FindFirstChild("Part") and (p52.Position - HumanoidRootPart.Position).Magnitude >= 3000 and GetSpawnPoint(v.Part) ~= GetSpawnPoint(HumanoidRootPart) and (v.Part.Position - HumanoidRootPart.Position).Magnitude <= 10000 and (v.Part.Position - p52.Position).Magnitude <= huge then
			huge = (v.Part.Position - p52.Position).Magnitude
			v212 = v
		end
	end

	return v212
end
BypassTP = function(p53)
	local Character = LocalPlayer.Character

	if not Character then
		return
	end

	local v218 = WaitForHumanoid()

	if not v218 or v218.Health <= 0 then
		return
	end

	if CanBypassTeleport(p53) and GetBypassCFrame(p53) then
		local v219 = GetBypassCFrame(p53)

		if v219 then
			if v219:FindFirstChild("Part") then
				Character.LastSpawnPoint.Disabled = true
				ReplicatedStorage.Remotes.CommF_:InvokeServer("SetLastSpawnPoint", v219.Name)
				ReplicatedStorage.Remotes.CommF_:InvokeServer("SetSpawnPoint")
				Character:PivotTo(v219.Part.CFrame)
				v218:ChangeState(15)

				while true do
					task.wait()

					if not LocalPlayer.Character then
						continue
					end

					if WaitForHumanoid() and WaitForHumanoid().Health > 0 then
						break
					end
				end
			end
		end
	end
end
totopofgreattree = function()
	if getdis(CFrame.new(28310.0234, 14895.1123, 109.456741)) > 1500 then
		ReplicatedStorage.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(28310.0234, 14895.1123, 109.456741))
		task.wait(0.3)
	end

	local cFrame3 = CFrame.new(28607.5352, 14896.5449, 106.011726)

	_tp(cFrame3)

	repeat
		task.wait()
	until getdis(cFrame3) <= 5

	task.wait(0.5)

	for i = 1, 4 do
		ReplicatedStorage.Remotes.CommF_:InvokeServer("RaceV4Progress", "TeleportBack")
	end
end
requestentrance = function(p54)
	local Position = p54

	if typeof(p54) == "CFrame" then
		Position = p54.Position
	end

	local t6

	if sea1 then
		t6 = {
			Sky3 = Vector3.new(-7894, 5547, -380),
			Sky3Exit = Vector3.new(-4607, 874, -1667),
			UnderWater = Vector3.new(61163, 11, 1819),
			["Underwater City"] = Vector3.new(61165.19140625, 0.18704631924629211, 1897.379150390625),
			["Pirate Village"] = Vector3.new(-1242.4625244140625, 4.7870597839355469, 3901.282958984375),
			UnderwaterExit = Vector3.new(4050, -1, -1814)
		}
	elseif sea2 then
		t6 = {
			["Swan Mansion"] = Vector3.new(-390, 332, 673),
			["Swan Room"] = Vector3.new(2285, 15, 905),
			["Cursed Ship"] = Vector3.new(923, 126, 32852),
			["Zombie Island"] = Vector3.new(-6509, 83, -133)
		}
	else
		t6 = {
			["Hydra Island"] = Vector3.new(5657.88623046875, 1013.0790405273438, -335.4996337890625),
			Mansion = Vector3.new(-12462, 375, -7552),
			Castle = Vector3.new(-5036, 315, -3179),
			["Temple of Time"] = Vector3.new(28286, 14897, 103),
			["Greate Tree"] = Vector3.new(3024.1709, 2280.69434, -7325.12793)
		}

		if not checkinventory("Valkyrie Helm") then
			return
		end
	end

	local v224
	local huge = math.huge

	for _, v in pairs(t6) do
		local Magnitude = typeof(v) == "Vector3" and (v - Position).Magnitude or (v.Position - Position).Magnitude

		if Magnitude < huge then
			huge = Magnitude
			v224 = v
		end
	end

	if v224 and huge and huge < getdis(p54) then
		pcall(function()
			if _G.TweenCache then
				_G.TweenCache:Cancel()
			end
		end)

		local ok2 = typeof(v224) ~= "Vector3" or v224.X ~= 3024.1709 or v224.Y ~= 2280.69434 or v224.Z ~= -7325.12793

		if not ok2 then
			ok2 = not (ReplicatedStorage.Remotes.CommF_:InvokeServer("RaceV4Progress", "Check") >= 2)
		end

		if ok2 then
			if huge < getdis(p54) then
				ReplicatedStorage.Remotes.CommF_:InvokeServer("requestEntrance", typeof(v224) == "Vector3" and v224 or v224.Position)
				task.wait(1)
			end
		else
			totopofgreattree()
			task.wait(1)
		end
	end
end
_tp = function(p55)
	local cFrame3

	if typeof(p55) == "Vector3" then
		cFrame3 = CFrame.new(p55)
	elseif typeof(p55) == "CFrame" then
		cFrame3 = p55
	elseif typeof(p55) == "Instance" then
		local ok, result = pcall(function()
			if p55:IsA("Model") then
				return p55:GetPivot()
			end

			return p55.CFrame
		end)

		cFrame3 = ok and result or nil
	end

	if not cFrame3 then
		return
	end

	if not plr.Character or not plr.Character:FindFirstChild("HumanoidRootPart") then
		return
	end

	if not Part or Part.Parent ~= workspace then
		return
	end

	getgenv().LastTPCall = tick()
	shouldTween = true
	getgenv().OnFarm = true

	if t4.Tween and t4.Tween.PlaybackState == Enum.PlaybackState.Playing and t4.Target and (t4.Target - cFrame3.Position).Magnitude < 1 then
		return t4.Tween
	end

	if sea3 and (getdis(cFrame3.Position, cFrame.Position) < 4000 or cFrame3.Position.Y < -1000) then
		local HumanoidRootPart = plr.Character.HumanoidRootPart

		if not (typeof(IsInSubmergedIsland) == "function" and IsInSubmergedIsland() or HumanoidRootPart.Position.Y < -1000) then
			if not (getdis(cFrame2) > 15) then
				local Net = ReplicatedStorage.Modules.Net

				pcall(function()
					Net["RF/SubmarineWorkerSpeak"]:InvokeServer("AskKilledTikiBoss")
					task.wait(0.5)
					Net["RF/SubmarineWorkerSpeak"]:InvokeServer("TravelToSubmergedIsland")
				end)
				task.wait(1)

				return
			end

			cFrame3 = cFrame2
		end
	end

	local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

	if not HumanoidRootPart or not Part or Part.Parent ~= workspace then
		return
	end

	if t4.Tween then
		t4.Tween:Cancel()
	end

	Part.CFrame = HumanoidRootPart.CFrame

	local Humanoid = plr.Character:FindFirstChildOfClass("Humanoid")

	if Humanoid and Humanoid.Sit == true then
		Part.CFrame = CFrame.new(Part.Position.X, cFrame3.Y, Part.Position.Z)
	end

	local Magnitude = (cFrame3.Position - Part.Position).Magnitude
	local tweenInfo = TweenInfo.new(Magnitude / (Magnitude <= 15 and (getgenv().TweenSpeedNear or 180) or getgenv().TweenSpeedFar or 150), Enum.EasingStyle.Linear)
	local tween = game:GetService("TweenService"):Create(Part, tweenInfo, {
		CFrame = CFrame.new(cFrame3.Position)
	})

	t4.Tween = tween
	t4.Target = cFrame3.Position
	tween:Play()

	return tween
end
old_tp = function(p56)
	if plr.Character and plr.Character:FindFirstChild("HumanoidRootPart") then
		plr.Character.HumanoidRootPart.CFrame = p56
	end
end
TeleportToTarget = function(p57)
	local v240 = _tp(p57)

	if v240 then
		v240.Completed:Wait()
	end

	task.wait(0.1)
end
notween = function(p58)
	plr.Character.HumanoidRootPart.CFrame = p58
end
BTP = function(p59)
	local LocalPlayer2 = game.Players.LocalPlayer
	local HumanoidRootPart = LocalPlayer2.Character.HumanoidRootPart
	local Humanoid = LocalPlayer2.Character.Humanoid
	local Main = LocalPlayer2.PlayerGui.Main
	local Position = HumanoidRootPart.Position

	repeat
		Humanoid.Health = 0
		HumanoidRootPart.CFrame = p59
		Main.Quest.Visible = false

		if (HumanoidRootPart.Position - Position).Magnitude > 1 then
			Position = HumanoidRootPart.Position
			HumanoidRootPart.CFrame = p59
		end

		task.wait(0.5)
	until (p59.Position - HumanoidRootPart.Position).Magnitude <= 2000
end
task.spawn(function()
	while task.wait() do
		pcall(function()
			local BodyVelocity, Highlight

			if _G.Auto_StartRaid or _G.SailBoat_Hydra or _G.WardenBoss or _G.AutoFactory or _G.HighestMirage or _G.HCM or _G.PGB or _G.Leviathan1 or _G.UPGDrago or _G.Complete_Trials or _G.TpDrago_Prehis or _G.BuyDrago or _G.AutoFireFlowers or _G.DT_Uzoth or _G.AutoBerry or _G.Prefully or _G.Prehis_Find or _G.Prehis_Skills or _G.Prehis_DB or _G.Prehis_DE or _G.FarmBlazeEM or _G.Dojoo or _G.CollectPresent or _G.AutoLawKak or _G.TpLab or _G.AutoPhoenixF or _G.AutoFarmChest or _G.AutoHytHallow or _G.LongsWord or _G.BlackSpikey or _G.AutoHolyTorch or _G.TrainDrago or _G.AutoSaber or _G.FarmMastery_Dev or _G.Auto_Fruit_Mastery or _G.CitizenQuest or _G.AutoEctoplasm or _G.KeysRen or _G.Auto_Rainbow_Haki or _G.obsFarm or _G.AutoBigmom or _G.Doughv2 or _G.AuraBoss or _G.Raiding or _G.Auto_Cavender or _G.TpPly or _G.Bartilo_Quest or _G.Level or _G.FarmEliteHunt or _G.AutoZou or _G.AutoFarm_Bone or getgenv().AutoMaterial or _G.CraftVM or _G.FrozenTP or _G.TPDoor or _G.AcientOne or _G.AutoFarmNear or _G.AutoRaidCastle or _G.DarkBladev3 or _G.AutoFarmRaid or _G.Auto_Cake_Prince or _G.Addealer or _G.TPNpc == true or _G.TwinHook or _G.FindMirage or _G.FarmChestM or _G.Shark or _G.TerrorShark or _G.Piranha or _G.MobCrew or _G.SeaBeast1 or _G.FishBoat or _G.AutoPole or _G.AutoPoleV2 or _G.Auto_SuperHuman or _G.AutoDeathStep or _G.Auto_SharkMan_Karate or _G.Auto_Electric_Claw or _G.AutoDragonTalon or _G.Auto_Def_DarkCoat or _G.Auto_God_Human or _G.Auto_Tushita or _G.AutoMatSoul or _G.AutoKenVTWO or _G.AutoSerpentBow or _G.AutoFMon or _G.Auto_Soul_Guitar or _G.TPGEAR or _G.AutoSaw or _G.AutoTridentW2 or _G.AutoEvoRace or _G.AutoGetQuestBounty or _G.MarinesCoat or _G.TravelDres or _G.Defeating or _G.DummyMan or _G.Auto_Yama or _G.Auto_SwanGG or _G.SwanCoat or _G.AutoEcBoss or _G.Auto_Mink or _G.Auto_Human or _G.Auto_Skypiea or _G.Auto_Fish or _G.CDK_TS or _G.CDK_YM or _G.CDK or _G.AutoFarmGodChalice or _G.AutoFistDarkness or _G.AutoMiror or _G.Teleport or _G.AutoKilo or _G.AutoGetUsoap or _G.Praying or _G.TryLucky or _G.AutoColShad or _G.AutoUnHaki or _G.Auto_DonAcces or _G.AutoRipIngay or _G.DragoV3 or _G.DragoV1 or _G.SailBoats or NextIs or _G.FarmGodChalice or _G.IceBossRen or senth or senth2 or _G.Lvthan or _G.beasthunter or _G.DangerLV or _G.Relic123 or _G.tweenKitsune or _G.Collect_Ember or _G.AutofindKitIs or _G.snaguine or _G.TwFruits or _G.tweenKitShrine or _G.Tp_LgS or _G.Tp_MasterA or _G.tweenShrine or _G.FarmMastery_G or _G.Auto_Gun_Mastery or _G.FarmMastery_S or _G.Auto_Mastery_All_Sword or _G.FarmBoss or _G.AutoFarmAllBoss or _G.AutoFishSlap or _G.FarmTyrant or _G.FarmPhaBinh or _G.AutoSpawnCP or _G.AutoBerryH or _G.AutoChestBP or _G.FarmEliteHop or _G.AutoHop_Dough or _G.AutoDoughKing or _G.AutoAttackDoughKing or _G.StartEvent or _G.AutoMysticIsland or _G.AutoPlayerHunter or _G.SafeMode or _G.AutoKillMob or _G.AutoStartPrehistoric or _G.AutoUnHaki or _G.AutoAttackRipIndra or _G.AutoFarmIsland or _G.AutoFarmDungeon or _G.AutoFarmCandy or _G.AutoTP_Gift or _G.AutoTPGift or _G.AutoTPAndCollect or _G.MasterAutoLevel or _G.MasterAutoCandy or _G.TPFloor1 or _G.TPFloor2 or _G.TPFloor3 or _G.TPFloor4 or _G.AutoMagnetToken then
				shouldTween = true

				local HumanoidRootPart = plr.Character.HumanoidRootPart

				if not HumanoidRootPart:FindFirstChild("BodyClip") then
					BodyVelocity = Instance.new("BodyVelocity")
					BodyVelocity.Name = "BodyClip"
					BodyVelocity.Parent = plr.Character.HumanoidRootPart
					BodyVelocity.MaxForce = Vector3.new(100000, 100000, 100000)
					BodyVelocity.Velocity = Vector3.new(0, 0, 0)
				end

				local Character = plr.Character

				if not Character:FindFirstChild("highlight") then
					Highlight = Instance.new("Highlight")
					Highlight.Name = "highlight"
					Highlight.Enabled = true
					Highlight.FillColor = Color3.fromRGB(0, 255, 254)
					Highlight.OutlineColor = Color3.fromRGB(0, 255, 254)
					Highlight.FillTransparency = 0.5
					Highlight.OutlineTransparency = 0.2
					Highlight.Parent = plr.Character
				end

				for _, descendant in pairs(plr.Character:GetDescendants()) do
					if descendant:IsA("BasePart") then
						descendant.CanCollide = false
					end
				end
			elseif tick() - (getgenv().LastTPCall or 0) < 0.35 then
				shouldTween = true

				if not plr.Character.HumanoidRootPart:FindFirstChild("BodyClip") then
					BodyVelocity = Instance.new("BodyVelocity")
					BodyVelocity.Name = "BodyClip"
					BodyVelocity.Parent = plr.Character.HumanoidRootPart
					BodyVelocity.MaxForce = Vector3.new(100000, 100000, 100000)
					BodyVelocity.Velocity = Vector3.new(0, 0, 0)
				end

				if not plr.Character:FindFirstChild("highlight") then
					Highlight = Instance.new("Highlight")
					Highlight.Name = "highlight"
					Highlight.Enabled = true
					Highlight.FillColor = Color3.fromRGB(0, 255, 254)
					Highlight.OutlineColor = Color3.fromRGB(0, 255, 254)
					Highlight.FillTransparency = 0.5
					Highlight.OutlineTransparency = 0.2
					Highlight.Parent = plr.Character
				end

				for _, descendant in pairs(plr.Character:GetDescendants()) do
					if descendant:IsA("BasePart") then
						descendant.CanCollide = false
					end
				end
			else
				shouldTween = false

				if plr.Character.HumanoidRootPart:FindFirstChild("BodyClip") then
					plr.Character.HumanoidRootPart:FindFirstChild("BodyClip"):Destroy()
				end

				if plr.Character:FindFirstChild("highlight") then
					plr.Character:FindFirstChild("highlight"):Destroy()
				end
			end
		end)
	end
end)
QuestB = function()
	if World1 then
		if _G.FindBoss == "The Gorilla King" then
			bMon = "The Gorilla King"
			Qname = "JungleQuest"
			Qdata = 3
			PosQBoss = CFrame.new(-1601.6553955078, 36.85213470459, 153.38809204102)
			PosB = CFrame.new(-1088.75977, 8.13463783, -488.559906, -0.707134247, 0, 0.707079291, 0, 1, 0, -0.707079291, 0, -0.707134247)
		elseif _G.FindBoss == "Bobby" then
			bMon = "Bobby"
			Qname = "BuggyQuest1"
			Qdata = 3
			PosQBoss = CFrame.new(-1140.1761474609, 4.752049446106, 3827.4057617188)
			PosB = CFrame.new(-1087.3760986328, 46.949409484863, 4040.1462402344)
		elseif _G.FindBoss == "The Saw" then
			bMon = "The Saw"
			PosB = CFrame.new(-784.89715576172, 72.427383422852, 1603.5822753906)
		elseif _G.FindBoss == "Yeti" then
			bMon = "Yeti"
			Qname = "SnowQuest"
			Qdata = 3
			PosQBoss = CFrame.new(1386.8073730469, 87.272789001465, -1298.3576660156)
			PosB = CFrame.new(1218.7956542969, 138.01184082031, -1488.0262451172)
		elseif _G.FindBoss == "Mob Leader" then
			bMon = "Mob Leader"
			PosB = CFrame.new(-2844.7307128906, 7.4180502891541, 5356.6723632813)
		elseif _G.FindBoss == "Vice Admiral" then
			bMon = "Vice Admiral"
			Qname = "MarineQuest2"
			Qdata = 2
			PosQBoss = CFrame.new(-5036.2465820313, 28.677835464478, 4324.56640625)
			PosB = CFrame.new(-5006.5454101563, 88.032081604004, 4353.162109375)
		elseif _G.FindBoss == "Saber Expert" then
			bMon = "Saber Expert"
			PosB = CFrame.new(-1458.89502, 29.8870335, -50.633564)
		elseif _G.FindBoss == "Warden" then
			bMon = "Warden"
			Qname = "ImpelQuest"
			Qdata = 1
			PosB = CFrame.new(5278.04932, 2.15167475, 944.101929, 0.220546961, -4.49946401e-06, 0.975376427, -1.95412576e-05, 1, 9.03162072e-06, -0.975376427, -2.10519756e-05, 0.220546961)
			PosQBoss = CFrame.new(5191.86133, 2.84020686, 686.438721, -0.731384635, 0, 0.681965172, 0, 1, 0, -0.681965172, 0, -0.731384635)
		elseif _G.FindBoss == "Chief Warden" then
			bMon = "Chief Warden"
			Qname = "ImpelQuest"
			Qdata = 2
			PosB = CFrame.new(5206.92578, 0.997753382, 814.976746, 0.342041343, -0.00062915677, 0.939684749, 0.00191645394, 0.999998152, -2.80422337e-05, -0.939682961, 0.00181045406, 0.342041939)
			PosQBoss = CFrame.new(5191.86133, 2.84020686, 686.438721, -0.731384635, 0, 0.681965172, 0, 1, 0, -0.681965172, 0, -0.731384635)
		elseif _G.FindBoss == "Swan" then
			bMon = "Swan"
			Qname = "ImpelQuest"
			Qdata = 3
			PosB = CFrame.new(5325.09619, 7.03906584, 719.570679, -0.309060812, 0, 0.951042235, 0, 1, 0, -0.951042235, 0, -0.309060812)
			PosQBoss = CFrame.new(5191.86133, 2.84020686, 686.438721, -0.731384635, 0, 0.681965172, 0, 1, 0, -0.681965172, 0, -0.731384635)
		elseif _G.FindBoss == "Magma Admiral" then
			bMon = "Magma Admiral"
			Qname = "MagmaQuest"
			Qdata = 3
			PosQBoss = CFrame.new(-5314.6220703125, 12.262420654297, 8517.279296875)
			PosB = CFrame.new(-5765.8969726563, 82.92064666748, 8718.3046875)
		elseif _G.FindBoss == "Fishman Lord" then
			bMon = "Fishman Lord"
			Qname = "FishmanQuest"
			Qdata = 3
			PosQBoss = CFrame.new(61122.65234375, 18.497442245483, 1569.3997802734)
			PosB = CFrame.new(61260.15234375, 30.950881958008, 1193.4329833984)
		elseif _G.FindBoss == "Wysper" then
			bMon = "Wysper"
			Qname = "SkyExp1Quest"
			Qdata = 3
			PosQBoss = CFrame.new(-7861.947265625, 5545.517578125, -379.85974121094)
			PosB = CFrame.new(-7866.1333007813, 5576.4311523438, -546.74816894531)
		elseif _G.FindBoss == "Thunder God" then
			bMon = "Thunder God"
			Qname = "SkyExp2Quest"
			Qdata = 3
			PosQBoss = CFrame.new(-7903.3828125, 5635.9897460938, -1410.923828125)
			PosB = CFrame.new(-7994.984375, 5761.025390625, -2088.6479492188)
		elseif _G.FindBoss == "Cyborg" then
			bMon = "Cyborg"
			Qname = "FountainQuest"
			Qdata = 3
			PosQBoss = CFrame.new(5258.2788085938, 38.526931762695, 4050.044921875)
			PosB = CFrame.new(6094.0249023438, 73.770050048828, 3825.7348632813)
		elseif _G.FindBoss == "Ice Admiral" then
			bMon = "Ice Admiral"
			Qdata = nil
			PosQBoss = CFrame.new(1266.08948, 26.1757946, -1399.57678, -0.573599219, 0, -0.81913656, 0, 1, 0, 0.81913656, 0, -0.573599219)
			PosB = CFrame.new(1266.08948, 26.1757946, -1399.57678, -0.573599219, 0, -0.81913656, 0, 1, 0, 0.81913656, 0, -0.573599219)
		elseif _G.FindBoss == "Greybeard" then
			bMon = "Greybeard"
			Qdata = nil
			PosQBoss = CFrame.new(-5081.3452148438, 85.221641540527, 4257.3588867188)
			PosB = CFrame.new(-5081.3452148438, 85.221641540527, 4257.3588867188)
		end
	end

	if World2 then
		if _G.FindBoss == "Diamond" then
			bMon = "Diamond"
			Qname = "Area1Quest"
			Qdata = 3
			PosQBoss = CFrame.new(-427.5666809082, 73.313781738281, 1835.4208984375)
			PosB = CFrame.new(-1576.7166748047, 198.59265136719, 13.724286079407)
		elseif _G.FindBoss == "Jeremy" then
			bMon = "Jeremy"
			Qname = "Area2Quest"
			Qdata = 3
			PosQBoss = CFrame.new(636.79943847656, 73.413787841797, 918.00415039063)
			PosB = CFrame.new(2006.9261474609, 448.95666503906, 853.98284912109)
		elseif _G.FindBoss == "Orbitus" then
			bMon = "Orbitus"
			Qname = "MarineQuest3"
			Qdata = 3
			PosQBoss = CFrame.new(-2441.986328125, 73.359344482422, -3217.5324707031)
			PosB = CFrame.new(-2172.7399902344, 103.32216644287, -4015.025390625)
		elseif _G.FindBoss == "Don Swan" then
			bMon = "Don Swan"
			PosB = CFrame.new(2286.2004394531, 15.177839279175, 863.8388671875)
		elseif _G.FindBoss == "Smoke Admiral" then
			bMon = "Smoke Admiral"
			Qname = "IceSideQuest"
			Qdata = 3
			PosQBoss = CFrame.new(-5429.0473632813, 15.977565765381, -5297.9614257813)
			PosB = CFrame.new(-5275.1987304688, 20.757257461548, -5260.6669921875)
		elseif _G.FindBoss == "Awakened Ice Admiral" then
			bMon = "Awakened Ice Admiral"
			Qname = "FrostQuest"
			Qdata = 3
			PosQBoss = CFrame.new(5668.9780273438, 28.519989013672, -6483.3520507813)
			PosB = CFrame.new(6403.5439453125, 340.29766845703, -6894.5595703125)
		elseif _G.FindBoss == "Tide Keeper" then
			bMon = "Tide Keeper"
			Qname = "ForgottenQuest"
			Qdata = 3
			PosQBoss = CFrame.new(-3053.9814453125, 237.18954467773, -10145.0390625)
			PosB = CFrame.new(-3795.6423339844, 105.88877105713, -11421.307617188)
		elseif _G.FindBoss == "Darkbeard" then
			bMon = "Darkbeard"
			Qdata = nil
			PosQBoss = CFrame.new(3677.08203125, 62.751937866211, -3144.8332519531)
			PosB = CFrame.new(3677.08203125, 62.751937866211, -3144.8332519531)
		elseif _G.FindBoss == "Cursed Captain" then
			bMon = "Cursed Captain"
			Qdata = nil
			PosQBoss = CFrame.new(916.928589, 181.092773, 33422)
			PosB = CFrame.new(916.928589, 181.092773, 33422)
		elseif _G.FindBoss == "Order" then
			bMon = "Order"
			Qdata = nil
			PosQBoss = CFrame.new(-6217.2021484375, 28.047645568848, -5053.1357421875)
			PosB = CFrame.new(-6217.2021484375, 28.047645568848, -5053.1357421875)
		end
	end

	if World3 then
		if _G.FindBoss == "Stone" then
			bMon = "Stone"
			Qname = "PiratePortQuest"
			Qdata = 3
			PosQBoss = CFrame.new(-289.76705932617, 43.819011688232, 5579.9384765625)
			PosB = CFrame.new(-1027.6512451172, 92.404174804688, 6578.8530273438)
		elseif _G.FindBoss == "Hydra Leader" then
			bMon = "Hydra Leader"
			Qname = "VenomCrewQuest"
			Qdata = 3
			PosQBoss = CFrame.new(5211.021484375, 1004.35778859375, 758.18475341796875)
			PosB = CFrame.new(5821.89794921875, 1019.0950927734375, -73.719230651855469)
		elseif _G.FindBoss == "Kilo Admiral" then
			bMon = "Kilo Admiral"
			Qname = "MarineTreeIsland"
			Qdata = 3
			PosQBoss = CFrame.new(2179.3010253906, 28.731239318848, -6739.9741210938)
			PosB = CFrame.new(2764.2233886719, 432.46154785156, -7144.4580078125)
		elseif _G.FindBoss == "Captain Elephant" then
			bMon = "Captain Elephant"
			Qname = "DeepForestIsland"
			Qdata = 3
			PosQBoss = CFrame.new(-13232.682617188, 332.40396118164, -7626.01171875)
			PosB = CFrame.new(-13376.7578125, 433.28689575195, -8071.392578125)
		elseif _G.FindBoss == "Beautiful Pirate" then
			bMon = "Beautiful Pirate"
			Qname = "DeepForestIsland2"
			Qdata = 3
			PosQBoss = CFrame.new(-12682.096679688, 390.88653564453, -9902.1240234375)
			PosB = CFrame.new(5283.609375, 22.56223487854, -110.78285217285)
		elseif _G.FindBoss == "Cake Queen" then
			bMon = "Cake Queen"
			Qname = "IceCreamIslandQuest"
			Qdata = 3
			PosQBoss = CFrame.new(-819.376709, 64.9259796, -10967.2832, -0.766061664, 0, 0.642767608, 0, 1, 0, -0.642767608, 0, -0.766061664)
			PosB = CFrame.new(-678.648804, 381.353943, -11114.2012, -0.908641815, 0.00149294338, 0.41757378, 0.00837114919, 0.999857843, 0.0146408929, -0.417492568, 0.0167988986, -0.90852499)
		elseif _G.FindBoss == "Longma" then
			bMon = "Longma"
			Qdata = nil
			PosQBoss = CFrame.new(-10238.875976563, 389.7912902832, -9549.7939453125)
			PosB = CFrame.new(-10238.875976563, 389.7912902832, -9549.7939453125)
		elseif _G.FindBoss == "Soul Reaper" then
			bMon = "Soul Reaper"
			Qdata = nil
			PosQBoss = CFrame.new(-9524.7890625, 315.80429077148, 6655.7192382813)
			PosB = CFrame.new(-9524.7890625, 315.80429077148, 6655.7192382813)
		end
	end
end
QuestBeta = function()
	QuestB()

	return {
		[0] = _G.FindBoss,
		bMon,
		Qdata,
		Qname,
		PosB,
		PosQBoss
	}
end

do
	local Quests = require(game:GetService("ReplicatedStorage"):WaitForChild("Quests"))
	local GuideModule = require(game:GetService("ReplicatedStorage"):WaitForChild("GuideModule"))
	local t7 = {
		"MarineQuest",
		"BartiloQuest",
		"CitizenQuest",
		"Trainees"
	}

	CheckSea = function(p60)
		if (game.PlaceId == 2753915549 or game.PlaceId == 85211729168715) and p60 == 1 then
			return true
		end

		if (game.PlaceId == 4442272183 or game.PlaceId == 79091703265657) and p60 == 2 then
			return true
		end

		if (game.PlaceId == 7449423635 or game.PlaceId == 100117331123089) and p60 == 3 then
			return true
		end

		return false
	end
	GetQuestPointFromNPC = function(p61)
		for _, child in pairs(workspace.NPCs:GetChildren()) do
			if child.Name == p61 then
				if child:FindFirstChild("HumanoidRootPart") then
					return child.HumanoidRootPart.CFrame
				end
			end
		end

		for _, child in pairs(replicated.NPCs:GetChildren()) do
			if child.Name == p61 then
				if child:FindFirstChild("HumanoidRootPart") then
					return child.HumanoidRootPart.CFrame
				end
			end
		end

		return nil
	end
	GetQuests = function()
		local Value = plr.Data.Level.Value
		local n1 = 0
		local t8 = {}

		if Value >= 700 and CheckSea(1) then
			t8.Mob = "Galley Captain"
			t8.NameQuest = "FountainQuest"
			t8.ID = 2
			t8.LevelReq = 700
		else
			if Value >= 1500 and CheckSea(2) then
				t8.Mob = "Water Fighter"
				t8.NameQuest = "ForgottenQuest"
				t8.ID = 2
				t8.LevelReq = 1450

				return t8
			end

			for k, Quest in pairs(Quests) do
				for k2, v in pairs(Quest) do
					local LevelReq = v.LevelReq

					for k3 in pairs(v.Task) do
						if LevelReq <= Value and n1 <= LevelReq and v.Task[k3] > 1 and not table.find(t7, k) then
							n1 = LevelReq
							t8.Mob = k3
							t8.NameQuest = k
							t8.ID = k2
							t8.LevelReq = LevelReq
						end
					end
				end
			end
		end

		return t8
	end
	GetQuestPoint = function()
		if GuideModule and GuideModule.Data and GuideModule.Data.LastClosestNPC then
			return GetQuestPointFromNPC(GuideModule.Data.LastClosestNPC)
		end

		return nil
	end
end

MaterialMon = function()
	local LocalPlayer2 = game.Players.LocalPlayer
	local HumanoidRootPart = LocalPlayer2.Character and LocalPlayer2.Character:FindFirstChild("HumanoidRootPart")

	if not HumanoidRootPart then
		return
	end

	shouldRequestEntrance = function(p62, p63)
		if p63 <= (HumanoidRootPart.Position - p62).Magnitude then
			replicated.Remotes.CommF_:InvokeServer("requestEntrance", p62)
		end
	end

	if not World1 then
		if not World2 then
			if World3 then
				if SelectMaterial == "Scrap Metal" then
					MMon = {
						"Jungle Pirate",
						"Forest Pirate"
					}
					MPos = CFrame.new(-11975.78515625, 331.77340698242188, -10620.0302734375)
					SP = "Default"
				elseif SelectMaterial == "Fish Tail" then
					MMon = {
						"Fishman Raider",
						"Fishman Captain"
					}
					MPos = CFrame.new(-10993, 332, -8940)
					SP = "Default"
				elseif SelectMaterial == "Conjured Cocoa" then
					MMon = {
						"Chocolate Bar Battler",
						"Cocoa Warrior"
					}
					MPos = CFrame.new(620.63446044921875, 78.936447143554688, -12581.369140625)
					SP = "Default"
				elseif SelectMaterial == "Dragon Scale" then
					MMon = {
						"Dragon Crew Archer",
						"Dragon Crew Warrior"
					}
					MPos = CFrame.new(6594, 383, 139)
					SP = "Default"
				elseif SelectMaterial == "Gunpowder" then
					MMon = { "Pistol Billionaire" }
					MPos = CFrame.new(-84.855690002441406, 85.620613098144531, 6132.0087890625)
					SP = "Default"
				elseif SelectMaterial == "Mini Tusk" then
					MMon = { "Mythological Pirate" }
					MPos = CFrame.new(-13545, 470, -6917)
					SP = "Default"
				elseif SelectMaterial == "Demonic Wisp" then
					MMon = { "Demonic Soul" }
					MPos = CFrame.new(-9495.6806640625, 453.58624267578125, 5977.3486328125)
					SP = "Default"
				end
			end
		elseif SelectMaterial == "Leather + Scrap Metal" then
			MMon = { "Marine Captain" }
			MPos = CFrame.new(-2010.5059814453125, 73.00115966796875, -3326.620849609375)
			SP = "Default"
		elseif SelectMaterial == "Magma Ore" then
			MMon = {
				"Magma Ninja",
				"Lava Pirate"
			}
			MPos = CFrame.new(-5428, 78, -5959)
			SP = "Default"
		elseif SelectMaterial == "Ectoplasm" then
			MMon = {
				"Ship Deckhand",
				"Ship Engineer",
				"Ship Steward",
				"Ship Officer"
			}
			MPos = CFrame.new(911.35827636719, 125.95812988281, 33159.5390625)
			SP = "Default"
			shouldRequestEntrance(Vector3.new(61163.8515625, 5.3423423767089844, 1819.7841796875), 18000)
		elseif SelectMaterial == "Mystic Droplet" then
			MMon = { "Water Fighter" }
			MPos = CFrame.new(-3385, 239, -10542)
			SP = "Default"
		elseif SelectMaterial == "Radioactive Material" then
			MMon = { "Factory Staff" }
			MPos = CFrame.new(295, 73, -56)
			SP = "Default"
		elseif SelectMaterial == "Vampire Fang" then
			MMon = { "Vampire" }
			MPos = CFrame.new(-6033, 7, -1317)
			SP = "Default"
		end
	elseif SelectMaterial == "Angel Wings" then
		MMon = {
			"Shanda",
			"Royal Squad",
			"Royal Soldier",
			"Wysper",
			"Thunder God"
		}
		MPos = CFrame.new(-4698, 845, -1912)
		SP = "Default"
		shouldRequestEntrance(Vector3.new(-4607.82275, 872.54248, -1667.55688), 10000)
	elseif SelectMaterial == "Leather + Scrap Metal" then
		MMon = {
			"Brute",
			"Pirate"
		}
		MPos = CFrame.new(-1145, 15, 4350)
		SP = "Default"
	elseif SelectMaterial == "Magma Ore" then
		MMon = {
			"Military Soldier",
			"Military Spy",
			"Magma Admiral"
		}
		MPos = CFrame.new(-5815, 84, 8820)
		SP = "Default"
	elseif SelectMaterial == "Fish Tail" then
		MMon = {
			"Fishman Warrior",
			"Fishman Commando",
			"Fishman Lord"
		}
		MPos = CFrame.new(61123, 19, 1569)
		SP = "Default"
		shouldRequestEntrance(Vector3.new(61163.8515625, 5.3423423767089844, 1819.7841796875), 17000)
	end
end

do
	QuestNeta = function()
		local v272 = GetQuests()

		return {
			v272.Mob,
			v272.ID,
			v272.NameQuest,
			v272.LevelReq,
			v272.Mob,
			(GetQuestPoint())
		}
	end
end

alreadyTeleported = false
teleporting = false
_G.CheckQuestVisible = function(p64)
	local LocalPlayer2 = p64 or game.Players.LocalPlayer
	local Quest = LocalPlayer2.PlayerGui:FindFirstChild("Main") and LocalPlayer2.PlayerGui.Main:FindFirstChild("Quest")
	local TrackedQuestFrame = LocalPlayer2.PlayerGui:FindFirstChild("TrackedQuestFrame")

	if Quest and Quest.Visible then
		local s1 = ""

		pcall(function()
			s1 = Quest.Container.QuestTitle.Title.Text
		end)

		return true, s1
	end

	if not TrackedQuestFrame or not TrackedQuestFrame.Enabled then
		return false, ""
	end

	local s2 = ""

	pcall(function()
		s2 = TrackedQuestFrame.Frame.header.textLabel.Text
	end)

	if s2 == "" then
		pcall(function()
			s2 = TrackedQuestFrame.Frame.header.textLabel.textLabel.Text
		end)
	end

	return true, s2
end
IsInSubmergedIsland = function()
	if not plr.Character then
		return false
	end

	local HumanoidRootPart = plr.Character:FindFirstChild("HumanoidRootPart")

	if HumanoidRootPart then
		return HumanoidRootPart.Position.Y < -1000
	end

	return false
end
GuiNode = function(...)
	local Main = game.Players.LocalPlayer.PlayerGui:FindFirstChild("Main")

	if not Main then
		return nil
	end

	local v280 = Main

	for _, v in ipairs({ ... }) do
		if not v280 then
			return nil
		end

		v280 = v280:FindFirstChild(v)
	end

	return v280
end
GuiShown = function(...)
	if select("#", ...) == 1 and select(1, ...) == "Quest" then
		local TrackedQuestFrame = game.Players.LocalPlayer.PlayerGui:FindFirstChild("TrackedQuestFrame")

		if TrackedQuestFrame then
			local Frame = TrackedQuestFrame:FindFirstChild("Frame")

			if Frame then
				return TrackedQuestFrame.Enabled and Frame.Visible
			end
		end
	end

	local v285 = GuiNode(...)

	return v285 ~= nil and v285.Visible == true
end
QuestText = function()
	local TrackedQuestFrame = game.Players.LocalPlayer.PlayerGui:FindFirstChild("TrackedQuestFrame")

	if TrackedQuestFrame then
		local Frame = TrackedQuestFrame:FindFirstChild("Frame")

		if Frame and Frame.Visible then
			local header = Frame:FindFirstChild("header")
			local textLabel = header and header:FindFirstChild("textLabel")

			if textLabel and textLabel:IsA("TextLabel") then
				return tostring(textLabel.Text)
			end
		end
	end

	local Quest = GuiNode("Quest", "Container", "QuestTitle", "Title")

	if Quest then
		return tostring(Quest.Text)
	end

	return ""
end
CheckHasQuest = function(p65)
	if not p65 then
		return false
	end

	if not GuiShown("Quest") then
		return false
	end

	local v291 = QuestText()

	if v291 == "" then
		return false
	end

	return string.find(string.lower(v291), string.lower(p65), 1, true) ~= nil
end

do
	BFAcceptQuest = function(p66, p67, p68)
		if CheckHasQuest(p68) then
			return true
		end

		local CommF_ = game:GetService("ReplicatedStorage"):FindFirstChild("Remotes") and game:GetService("ReplicatedStorage").Remotes:FindFirstChild("CommF_")

		if not CommF_ then
			return false
		end

		local function v293()
			return CommF_:InvokeServer("StartQuest", p66, p67)
		end

		local ok = pcall(v293)

		if not ok then
			return false
		end

		local v296 = os.clock() + 3

		while not CheckHasQuest(p68) do
			task.wait(0.25)

			if v296 <= os.clock() then
				return CheckHasQuest(p68)
			end
		end

		return true
	end
end

task.spawn(function()
	while task.wait(0.5) do
		pcall(function()
			local ChooseWP = _G.ChooseWP or "Melee"
			local Name

			if plr.Character then
				for _, child in pairs(plr.Character:GetChildren()) do
					if child:IsA("Tool") then
						if child.ToolTip == ChooseWP then
							Name = child.Name

							break
						end
					end
				end
			end

			if not Name and plr.Backpack then
				for _, child in pairs(plr.Backpack:GetChildren()) do
					if child:IsA("Tool") and child.ToolTip == ChooseWP then
						Name = child.Name

						break
					end
				end
			end

			if Name then
				_G.SelectWeapon = Name
			end
		end)
	end
end)
task.spawn(function()
	while task.wait() do
		pcall(function()
			if _G.AutoFarmNear then
				for _, child in pairs(workspace.Enemies:GetChildren()) do
					if (child:FindFirstChild("Humanoid") or child:FindFirstChild("HumanoidRootPart")) and child.Humanoid.Health > 0 then
						while true do
							task.wait()
							Attack.Kill(child, _G.AutoFarmNear)

							if not _G.AutoFarmNear then
								break
							elseif not child.Parent or child.Humanoid.Health <= 0 then
								break
							end
						end
					end
				end
			end
		end)
	end
end)
task.spawn(function()
	while task.wait(Sec) do
		pcall(function()
			if _G.AutoFactory then
				local Core_ = GetConnectionEnemies("Core")

				if Core_ then
					while true do
						task.wait()
						EquipWeapon(_G.SelectWeapon)
						_tp(CFrame.new(448.46756, 199.356781, -441.389252))

						if Core_.Humanoid.Health <= 0 then
							break
						elseif _G.AutoFactory == false then
							break
						end
					end
				else
					_tp(CFrame.new(448.46756, 199.356781, -441.389252))
				end
			end
		end)
	end
end)
task.spawn(function()
	local cFrame3 = CFrame.new(-5496.17432, 313.768921, -2841.53027, 0.924894512, 7.37058015e-09, 0.380223751, 3.5881019e-08, 1, -1.06665446e-07, -0.380223751, 1.12297109e-07, 0.924894512)
	local vector3 = Vector3.new(-5539.3115234375, 313.800537109375, -2972.372314453125)

	while task.wait(Sec) do
		if _G.AutoRaidCastle then
			pcall(function()
				local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

				if not HumanoidRootPart then
					return
				end

				if (vector3 - HumanoidRootPart.Position).Magnitude <= 500 then
					local v309
					local v310

					for _, child in pairs(workspace.Enemies:GetChildren()) do
						local Humanoid = child:FindFirstChild("Humanoid")
						local HumanoidRootPart2 = child:FindFirstChild("HumanoidRootPart")

						if Humanoid and HumanoidRootPart2 and Humanoid.Health > 0 and (HumanoidRootPart2.Position - vector3).Magnitude <= 700 then
							local Magnitude = (HumanoidRootPart2.Position - HumanoidRootPart.Position).Magnitude

							if not v310 or Magnitude < v310 then
								v309 = child
								v310 = Magnitude
							end
						end
					end

					if v309 then
						local v316 = tick() + 30

						while true do
							task.wait()
							Attack.Kill(v309, _G.AutoRaidCastle)

							if not _G.AutoRaidCastle then
								break
							elseif not v309.Parent or v309.Humanoid.Health <= 0 or v316 < tick() then
								break
							end
						end
					else
						_tp(cFrame3)
					end
				else
					_tp(cFrame3)
				end
			end)
		end
	end
end)

do
	task.spawn(function()
		if task.wait(Sec) then
			repeat
				pcall(function()
					if _G.AutoEctoplasm then
						local v317 = GetConnectionEnemies({
							"Ship Deckhand",
							"Ship Engineer",
							"Ship Steward",
							"Ship Officer",
							"Arctic Warrior"
						})

						if Attack.Alive(v317) then
							while true do
								task.wait()
								Attack.Kill(v317, _G.AutoEctoplasm)

								if not _G.AutoEctoplasm then
									break
								elseif not v317.Parent or v317.Humanoid.Health <= 0 then
									break
								end
							end
						else
							replicated.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(923.21252441406, 126.9760055542, 32852.83203125))
						end
					end
				end)
			until not task.wait(Sec)
		end
	end)
end

task.spawn(function()
	while task.wait(Sec) do
		if _G.AutoFarmChest then
			pcall(function()
				local CollectionService = game:GetService("CollectionService")
				local LocalPlayer2 = game:GetService("Players").LocalPlayer
				local Character = LocalPlayer2.Character or LocalPlayer2.CharacterAdded:Wait()

				if not Character then
					return
				end

				local Position = Character:GetPivot().Position
				local tagged = CollectionService:GetTagged("_ChestTagged")
				local huge = math.huge
				local v324

				for i = 1, #tagged do
					local v326 = tagged[i]
					local Magnitude = (v326:GetPivot().Position - Position).Magnitude

					if (not SelectedIsland or v326:IsDescendantOf(SelectedIsland)) and not v326:GetAttribute("IsDisabled") and Magnitude < huge then
						huge = Magnitude
						v324 = v326
					end
				end

				if v324 then
					_tp(v324:GetPivot())
				end
			end)
		end
	end
end)
task.spawn(function()
	while task.wait(0.2) do
		if _G.StopWhenChalice and (_G.AutoFarmChest or _G.AutoChestBP) then
			pcall(function()
				if GetBP("God's Chalice") or GetBP("Sweet Chalice") or GetBP("Fist of Darkness") then
					_G.AutoFarmChest = false
					_G.AutoChestBP = false
				end
			end)
		end
	end
end)

do
	task.spawn(function()
		while task.wait(Sec) do
			if _G.AutoBerry then
				local CollectionService = game:GetService("CollectionService")
				local LocalPlayer2 = game:GetService("Players").LocalPlayer
				local tagged = CollectionService:GetTagged("BerryBush")

				for i = 1, #tagged do
					local v332 = tagged[i]

					for _, v in pairs(v332:GetAttributes()) do
						if not BerryArray or table.find(BerryArray, v) then
							_tp(v332.Parent:GetPivot())

							for i2 = 1, #tagged do
								for _, child in pairs(tagged[i2]:GetChildren()) do
									if not BerryArray or table.find(BerryArray, child) then
										_tp(child.WorldPivot)
										fireproximityprompt(child.ProximityPrompt, math.huge)
									end
								end
							end
						end
					end
				end
			end
		end
	end)
end

task.spawn(function()
	while task.wait(Sec) do
		if _G.AutoBerryH then
			local CollectionService = game:GetService("CollectionService")
			local LocalPlayer2 = game:GetService("Players").LocalPlayer
			local tagged = CollectionService:GetTagged("BerryBush")

			if #tagged == 0 then
				local TeleportService_ = game:GetService("TeleportService")
				local t9 = {}
				local ok = pcall(function()
					t9 = game:GetService("HttpService"):JSONDecode(game:HttpGet("https://games.roblox.com/v1/games/" .. game.PlaceId .. "/servers/Public?sortOrder=Asc&limit=100"))
				end)

				if ok then
					if t9.data then
						for _, v in pairs(t9.data) do
							if v.playing < v.maxPlayers and v.id ~= game.JobId then
								TeleportService_:TeleportToPlaceInstance(game.PlaceId, v.id, LocalPlayer2)

								break
							end
						end
					end
				end
			else
				for i = 1, #tagged do
					local v348 = tagged[i]

					for _, v in pairs(v348:GetAttributes()) do
						if not BerryArray or table.find(BerryArray, v) then
							_tp(v348.Parent:GetPivot())

							for i2 = 1, #tagged do
								for _, child in pairs(tagged[i2]:GetChildren()) do
									if not BerryArray or table.find(BerryArray, child.Name) then
										_tp(child.WorldPivot)
										fireproximityprompt(child.ProximityPrompt, math.huge)
									end
								end
							end
						end
					end
				end
			end
		end
	end
end)
task.spawn(function()
	while task.wait() do
		if _G.AutoKillMob then
			pcall(function()
				if game:GetService("Workspace").Enemies:FindFirstChild(getgenv().SelectMob) then
					for _, child in pairs(game:GetService("Workspace").Enemies:GetChildren()) do
						if child.Name == getgenv().SelectMob and child:FindFirstChild("Humanoid") and child:FindFirstChild("HumanoidRootPart") and child.Humanoid.Health > 0 then
							while true do
								game:GetService("RunService").Heartbeat:Wait()
								Attack.Kill(child, _G.AutoKillMob)

								if not _G.AutoKillMob then
									break
								elseif not child.Parent or child.Humanoid.Health <= 0 then
									break
								end
							end
						end
					end
				end
			end)
		end
	end
end)
Sea1_Islands = {
	Pirates = {
		CFrame = CFrame.new(-2709.67944, 24.5206585, 2104.24585, -0.744724929, -3.97967455e-08, -0.667371571, 4.32403588e-08, 1, -1.07884304e-07, 0.667371571, -1.09201515e-07, -0.744724929),
		Mobs = { "Bandit" }
	},
	Marine = {
		CFrame = CFrame.new(-2709.67944, 24.5206585, 2104.24585, -0.744724929, -3.97967455e-08, -0.667371571, 4.32403588e-08, 1, -1.07884304e-07, 0.667371571, -1.09201515e-07, -0.744724929),
		Mobs = { "Trainee" }
	},
	Jungle = {
		CFrame = CFrame.new(-1600, 36, 150),
		Mobs = {
			"Monkey",
			"Gorilla"
		}
	},
	["Pirate Village"] = {
		CFrame = CFrame.new(-1100, 4, 3850),
		Mobs = {
			"Pirate",
			"Brute"
		}
	},
	Desert = {
		CFrame = CFrame.new(1090, 7, 4370),
		Mobs = {
			"Desert Bandit",
			"Desert Officer"
		}
	},
	["Frozen Village"] = {
		CFrame = CFrame.new(1200, 28, -1500),
		Mobs = {
			"Snow Bandit",
			"Snowman"
		}
	},
	["Marine Fortress"] = {
		CFrame = CFrame.new(-4500, 20, 4250),
		Mobs = { "Chief Petty Officer" }
	},
	["Skylands Lower"] = {
		CFrame = CFrame.new(-5000, 700, -2500),
		Mobs = {
			"Sky Bandit",
			"Dark Master"
		}
	},
	Prison = {
		CFrame = CFrame.new(4875, 6, 735),
		Mobs = {
			"Prisoner",
			"Dangerous Prisoner"
		}
	},
	Colosseum = {
		CFrame = CFrame.new(-1500, 60, -290),
		Mobs = {
			"Toga Warrior",
			"Gladiator"
		}
	},
	["Magma Village"] = {
		CFrame = CFrame.new(-5200, 8, 8400),
		Mobs = {
			"Military Soldier",
			"Military Spy"
		}
	},
	["Underwater City"] = {
		CFrame = CFrame.new(61160, 5, 1819),
		Mobs = {
			"Fishman Warrior",
			"Fishman Commando"
		}
	},
	["Skylands Upper"] = {
		CFrame = CFrame.new(-7880, 5545, -380),
		Mobs = {
			"God's Guard",
			"Shanda",
			"Royal Squad",
			"Royal Soldier"
		}
	},
	["Fountain City"] = {
		CFrame = CFrame.new(5258, 38, 4050),
		Mobs = {
			"Galley Pirate",
			"Galley Captain"
		}
	}
}
Core.Sea1_Islands = Sea1_Islands
getgenv().Sea1_Islands = Sea1_Islands
Sea2_Islands = {
	["Kingdom of Rose"] = {
		CFrame = CFrame.new(600, 73, 1000),
		Mobs = {
			"Raider",
			"Mercenary",
			"Swan Pirate",
			"Factory Staff"
		}
	},
	["Green Zone"] = {
		CFrame = CFrame.new(-2400, 73, -2700),
		Mobs = {
			"Marine Lieutenant",
			"Marine Captain"
		}
	},
	["Graveyard Island"] = {
		CFrame = CFrame.new(-5500, 8, -700),
		Mobs = {
			"Zombie",
			"Vampire"
		}
	},
	["Snow Mountain"] = {
		CFrame = CFrame.new(600, 400, -5300),
		Mobs = {
			"Snow Trooper",
			"Winter Warrior"
		}
	},
	["Hot and Cold (Cold)"] = {
		CFrame = CFrame.new(-6000, 15, -4500),
		Mobs = {
			"Lab Subordinate",
			"Horned Warrior"
		}
	},
	["Hot and Cold (Hot)"] = {
		CFrame = CFrame.new(-5400, 15, -5900),
		Mobs = {
			"Magma Ninja",
			"Lava Pirate"
		}
	},
	["Cursed Ship"] = {
		CFrame = CFrame.new(923, 126, 32852),
		Mobs = {
			"Ship Deckhand",
			"Ship Engineer",
			"Ship Steward",
			"Ship Officer"
		}
	},
	["Ice Castle"] = {
		CFrame = CFrame.new(5500, 28, -6800),
		Mobs = {
			"Arctic Warrior",
			"Snow Lurker"
		}
	},
	["Forgotten Island"] = {
		CFrame = CFrame.new(-3050, 237, -10150),
		Mobs = {
			"Sea Soldier",
			"Water Fighter"
		}
	}
}
Core.Sea2_Islands = Sea2_Islands
getgenv().Sea2_Islands = Sea2_Islands
Sea3_Islands = {
	["Port Town"] = {
		CFrame = CFrame.new(-290, 7, 5300),
		Mobs = {
			"Pirate Millionaire",
			"Pistol Billionaire"
		}
	},
	["Hydra Island"] = {
		CFrame = CFrame.new(5700, 600, 200),
		Mobs = {
			"Dragon Crew Warrior",
			"Dragon Crew Archer",
			"Female Islander",
			"Giant Islander"
		}
	},
	["Great Tree"] = {
		CFrame = CFrame.new(2300, 25, -6400),
		Mobs = {
			"Marine Commodore",
			"Marine Rear Admiral"
		}
	},
	["Floating Turtle"] = {
		CFrame = CFrame.new(-12500, 330, -7500),
		Mobs = {
			"Fishman Raider",
			"Fishman Captain",
			"Forest Pirate",
			"Mythological Pirate",
			"Jungle Pirate",
			"Musketeer Pirate"
		}
	},
	["Haunted Castle"] = {
		CFrame = CFrame.new(-9500, 140, 5500),
		Mobs = {
			"Reborn Skeleton",
			"Living Zombie",
			"Demonic Soul",
			"Posessed Mummy"
		}
	},
	["Sea of Treats"] = {
		CFrame = CFrame.new(-2100, 38, -12000),
		Mobs = {
			"Peanut Scout",
			"Peanut President",
			"Ice Cream Chef",
			"Ice Cream Commander",
			"Cookie Crafter",
			"Cake Guard",
			"Baking Staff",
			"Head Baker",
			"Cocoa Warrior",
			"Chocolate Bar Battler",
			"Sweet Thief",
			"Candy Rebel",
			"Candy Pirate",
			"Snow Demon"
		}
	},
	["Tiki Outpost"] = {
		CFrame = CFrame.new(-16200, 90, -17300),
		Mobs = {
			"Isle Outlaw",
			"Island Boy",
			"Sun-kissed Warrior",
			"Isle Champion"
		}
	},
	["Submerged Island"] = {
		CFrame = CFrame.new(-3200, -10, -10000),
		Mobs = {
			"Reef Bandit",
			"Coral Pirate",
			"Sea Chanter",
			"Ocean Prophet",
			"High Disciple",
			"Grand Devotee"
		}
	}
}
Core.Sea3_Islands = Sea3_Islands
getgenv().Sea3_Islands = Sea3_Islands
Core.Island = World1 and Sea1_Islands or World2 and Sea2_Islands or World3 and Sea3_Islands or {}
IslandData = Core.Island
getgenv().IslandData = IslandData
Core.GetMobs = function()
	local t10 = {}
	local IslandData_ = IslandData

	IslandData_ = IslandData_ or Core.Island or World1 and Sea1_Islands or World2 and Sea2_Islands or World3 and Sea3_Islands or {}

	for _, v in pairs(IslandData_) do
		if v.Mobs then
			for _, mob in ipairs(v.Mobs) do
				if not table.find(t10, mob) then
					table.insert(t10, mob)
				end
			end
		end
	end

	table.sort(t10)

	return t10
end
getgenv().GetMobs = Core.GetMobs
task.spawn(function()
	while task.wait(0.2) do
		if _G.AutoFarmIsland then
			if _G.SelectIsland and IslandData then
				local v362 = IslandData[_G.SelectIsland]

				if v362 then
					local CFrame_ = v362.CFrame
					local t11 = {}

					for _, mob in ipairs(v362.Mobs) do
						t11[mob] = true
					end

					local v367 = false

					for _, child in pairs(workspace.Enemies:GetChildren()) do
						if t11[child.Name] and child:FindFirstChild("Humanoid") and child:FindFirstChild("HumanoidRootPart") and child.Humanoid.Health > 0 then
							v367 = true

							while true do
								task.wait()
								_tp(child.HumanoidRootPart.CFrame * CFrame.new(0, 10, 0))
								Attack.Kill(child, true)

								if not _G.AutoFarmIsland then
									break
								elseif not child.Parent or child.Humanoid.Health <= 0 then
									break
								end
							end
						end
					end

					if not v367 then
						_tp(CFrame_)
					end
				end
			end
		end
	end
end)
task.spawn(function()
	while task.wait(1) do
		pcall(function()
			if _G.FarmEliteHunt then
				local Quest = GuiShown("Quest")
				local v371 = QuestText()

				if Quest then
					local v372
					local v373, v374, v375 = pairs({
						"Diablo",
						"Urban",
						"Deandre"
					})
					local v376 = geniter(v373, v374, v375)

					while true do
						local v377 = table.pack(v376())

						if v377[1] then
							local v378 = v377[3]

							if string.find(v371, v378) then
								v372 = v378

								break
							end
						else
							break
						end
					end

					if v372 then
						local v379
						local v380, v381, v382 = pairs(replicated:GetChildren())
						local v383 = geniter(v380, v381, v382)

						while true do
							local v384 = table.pack(v383())

							if v384[1] then
								local v385 = v384[3]

								if v385.Name == v372 and v385:FindFirstChild("HumanoidRootPart") then
									v379 = v385

									break
								end
							else
								break
							end
						end

						if not v379 then
							local v386, v387, v388 = pairs(Enemies:GetChildren())

							for _, v in v386, v387, v388 do
								if v.Name == v372 then
									if Attack.Alive(v) then
										v379 = v

										break
									end
								end
							end
						end

						if v379 and v379:FindFirstChild("HumanoidRootPart") then
							_tp(v379.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))

							while true do
								task.wait()
								Attack.Kill(v379, _G.FarmEliteHunt)

								if not _G.FarmEliteHunt then
									break
								elseif not v379.Parent or v379.Humanoid.Health <= 0 or not GuiShown("Quest") then
									break
								end
							end
						else
							task.wait(5)
						end
					else
						replicated.Remotes.CommF_:InvokeServer("AbandonQuest")
					end
				else
					local response = replicated.Remotes.CommF_:InvokeServer("EliteHunter")

					if response == nil or string.find(tostring(response), "Cooldown") then
						task.wait(10)

						return
					end

					task.wait(1)
				end
			end
		end)
	end
end)
HopServer = function()
	local HttpService = game:GetService("HttpService")
	local TeleportService_ = game:GetService("TeleportService")
	local s3 = ""
	local v395 = false

	repeat
		local ok, result = pcall(function()
			return game:HttpGet("https://games.roblox.com/v1/games/" .. game.PlaceId .. "/servers/Public?sortOrder=Asc&limit=100&cursor=" .. s3)
		end)

		if ok and result then
			local data = HttpService:JSONDecode(result)

			if data.data then
				for _, v in pairs(data.data) do
					if v.playing < v.maxPlayers and v.id ~= game.JobId then
						v395 = true
						TeleportService_:TeleportToPlaceInstance(game.PlaceId, v.id)

						break
					end
				end

				s3 = data.nextPageCursor or ""
			end
		end
	until not s3 or v395
end
task.spawn(function()
	while task.wait(1) do
		pcall(function()
			if _G.FarmEliteH then
				local Quest = GuiShown("Quest")
				local v402 = QuestText()

				if Quest then
					local v403
					local v404, v405, v406 = pairs({
						"Diablo",
						"Urban",
						"Deandre"
					})
					local v407 = geniter(v404, v405, v406)

					while true do
						local v408 = table.pack(v407())

						if v408[1] then
							local v409 = v408[3]

							if string.find(v402, v409) then
								v403 = v409

								break
							end
						else
							break
						end
					end

					if v403 then
						local v410
						local v411, v412, v413 = pairs(replicated:GetChildren())
						local v414 = geniter(v411, v412, v413)

						while true do
							local v415 = table.pack(v414())

							if v415[1] then
								local v416 = v415[3]

								if v416.Name == v403 and v416:FindFirstChild("HumanoidRootPart") then
									v410 = v416

									break
								end
							else
								break
							end
						end

						local v417, v418, v419 = pairs(workspace.Enemies:GetChildren())

						for _, v in v417, v418, v419 do
							if v.Name == v403 and Attack.Alive(v) then
								v410 = v

								break
							end
						end

						if v410 and v410:FindFirstChild("HumanoidRootPart") then
							_tp(v410.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))

							while true do
								task.wait()
								Attack.Kill(v410, _G.FarmEliteH)

								if not _G.FarmEliteH then
									break
								elseif not v410.Parent or v410.Humanoid.Health <= 0 or not GuiShown("Quest") then
									break
								end
							end
						else
							task.wait(5)
							HopServer()
						end
					else
						replicated.Remotes.CommF_:InvokeServer("AbandonQuest")
					end
				else
					local response = replicated.Remotes.CommF_:InvokeServer("EliteHunter")

					if response == nil or string.find(tostring(response), "Cooldown") then
						HopServer()

						return
					end

					task.wait(1)
				end
			end
		end)
	end
end)
task.spawn(function()
	local vector3 = Vector3.new(-5097.93164, 316.447021, -3142.66602)
	local cFrame3 = CFrame.new(-5344.822265625, 423.98541259766, -2725.0930175781)
	local n2 = 0

	while task.wait(Sec) do
		pcall(function()
			if _G.AutoRipIngay then
				local v426 = GetConnectionEnemies({
					"rip_indra",
					"rip_indra True Form"
				})

				if v426 then
					local v427 = tick() + 120

					while true do
						task.wait()
						Attack.Kill(v426, _G.AutoRipIngay)

						if not _G.AutoRipIngay then
							break
						elseif not v426.Parent or v426.Humanoid.Health <= 0 or v427 < tick() then
							break
						end
					end
				else
					local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

					if HumanoidRootPart and (HumanoidRootPart.Position - cFrame3.Position).Magnitude > 400 then
						if tick() - n2 > 5 then
							n2 = tick()
							replicated.Remotes.CommF_:InvokeServer("requestEntrance", vector3)
							task.wait(0.1)
						end
					end

					_tp(cFrame3)
				end
			end
		end)
	end
end)
AuraSkin = function(p69)
	local t12 = { {
		StorageName = p69,
		Type = "AuraSkin",
		Context = "Equip"
	} }

	replicated:WaitForChild("Modules"):WaitForChild("Net"):WaitForChild("RF/FruitCustomizerRF"):InvokeServer(unpack(t12))
end

do
	VaildColor = function(p70)
		if p70 and p70.BrickColor then
			return tostring(p70.BrickColor) == "Lime green"
		end
	end
end

HakiCalculate = function(p71)
	local t13 = {
		["Really red"] = "Pure Red",
		Oyster = "Snow White",
		["Hot pink"] = "Winter Sky"
	}

	if p71 then
		if p71.BrickColor then
			return t13[tostring(p71.BrickColor)]
		end
	end
end
task.spawn(function()
	while task.wait(Sec) do
		if _G.AutoUnHaki then
			pcall(function()
				local Summoner = workspace.Map["Boat Castle"]:FindFirstChild("Summoner")

				if Summoner and Summoner:FindFirstChild("Circle") then
					local pairs_ = pairs
					local Circle = Summoner:FindFirstChild("Circle")

					for _, child in pairs_(Circle:GetChildren()) do
						if child.Name == "Part" then
							local Part2 = child:FindFirstChild("Part")

							if VaildColor(Part2) == false then
								AuraSkin(HakiCalculate(child))

								while true do
									task.wait()
									_tp(child.CFrame)

									if VaildColor(Part2) == true then
										break
									elseif not _G.AutoUnHaki then
										break
									end
								end
							end
						end
					end
				end
			end)
		end
	end
end)
task.spawn(function()
	while task.wait() do
		if _G.Auto_Cake_Prince and not _G.AutoRaidCastle then
			pcall(function()
				local LocalPlayer2 = game.Players.LocalPlayer
				local HumanoidRootPart = LocalPlayer2.Character and LocalPlayer2.Character:FindFirstChild("HumanoidRootPart")
				local CakeLoaf = workspace.Map:FindFirstChild("CakeLoaf")
				local BigMirror = CakeLoaf and CakeLoaf:FindFirstChild("BigMirror")

				if not HumanoidRootPart then
					return
				end

				if _G.AcceptQuestC and not _G.CheckQuestVisible(LocalPlayer2) then
					local cFrame3 = CFrame.new(-1927.92, 37.8, -12842.54)

					_tp(cFrame3)

					while (cFrame3.Position - HumanoidRootPart.Position).Magnitude > 50 do
						task.wait(0.2)
					end

					local v442 = math.random(1, 4)
					local t14 = {
						{
							"StartQuest",
							"CakeQuest2",
							2
						},
						{
							"StartQuest",
							"CakeQuest2",
							1
						},
						{
							"StartQuest",
							"CakeQuest1",
							1
						},
						{
							"StartQuest",
							"CakeQuest1",
							2
						}
					}

					pcall(function()
						game.ReplicatedStorage.Remotes.CommF_:InvokeServer(unpack(t14[v442]))
					end)
				end

				if not CakeLoaf then
					_tp(CFrame.new(-2077, 252, -12373))
					task.wait(2)

					return
				end

				if BigMirror and (BigMirror.Other.Transparency == 0 or workspace.Enemies:FindFirstChild("Cake Prince")) then
					local v444 = GetConnectionEnemies("Cake Prince")

					if v444 then
						while true do
							task.wait()
							Attack.Kill2(v444, _G.Auto_Cake_Prince)

							if not _G.Auto_Cake_Prince then
								break
							elseif not v444.Parent or v444.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(-2151.82, 149.32, -12404.91))
					end
				else
					local v445 = GetConnectionEnemies({
						"Cookie Crafter",
						"Cake Guard",
						"Baking Staff",
						"Head Baker"
					})

					if v445 then
						while true do
							task.wait()
							Attack.Kill(v445, _G.Auto_Cake_Prince)

							if not _G.Auto_Cake_Prince then
								break
							elseif not v445.Parent or v445.Humanoid.Health <= 0 or BigMirror and BigMirror.Other.Transparency == 0 then
								break
							end
						end
					else
						_tp(CFrame.new(-2077, 252, -12373))
					end
				end
			end)
		end
	end
end)
task.spawn(function()
	while task.wait(2) do
		if _G.AutoSpawnCP then
			local exitTo

			repeat
				pcall(function()
					local CommF_ = game.ReplicatedStorage.Remotes.CommF_
					local BigMirror = workspace.Map.CakeLoaf:FindFirstChild("BigMirror")

					if not BigMirror then
						return
					end

					if workspace.Enemies:FindFirstChild("Cake Prince") then
						return
					end

					if BigMirror.Other.Transparency == 0 then
						return
					end

					CommF_:InvokeServer("CakePrinceSpawner", true)
				end)
				exitTo = nil

				while task.wait(2) do
					if _G.AutoSpawnCP then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)
task.spawn(function()
	while task.wait() do
		if _G.AutoDoughKing then
			pcall(function()
				if not workspace.Map.CakeLoaf:FindFirstChild("RedDoor") then
					if GetBP("Red Key") then
						replicated.Remotes.CommF_:InvokeServer("CakeScientist", "Check")
						replicated.Remotes.CommF_:InvokeServer("RaidsNpc", "Check")
					end
				elseif not workspace.Map.CakeLoaf:FindFirstChild("RedDoor") then
					if GetConnectionEnemies("Dough King") then
						local v449 = GetConnectionEnemies("Dough King")

						if v449 then
							while true do
								task.wait()
								Attack.Kill(v449, _G.AutoDoughKing)

								if not _G.AutoDoughKing then
									break
								elseif not v449.Parent or v449.Humanoid.Health <= 0 then
									break
								end
							end
						else
							_tp(CFrame.new(-1943.676513671875, 251.50956726074219, -12337.880859375))
						end
					end
				elseif GetBP("Red Key") then
					while true do
						task.wait()
						_tp(CFrame.new(-2681.97998, 64.3921585, -12853.7363, 0.149007782, -1.87902192e-08, 0.98883605, 3.60619588e-08, 1, 1.35681812e-08, -0.98883605, 3.36376011e-08, 0.149007782))

						if not getgenv().AutoDoughKing then
							break
						elseif (plr.Character.HumanoidRootPart.CFrame - CFrame.new(-2681.97998, 64.3921585, -12853.7363, 0.149007782, -1.87902192e-08, 0.98883605, 3.60619588e-08, 1, 1.35681812e-08, -0.98883605, 3.36376011e-08, 0.149007782)).Magnitude <= 5 then
							break
						end
					end

					EquipWeapon("Red Key")
				end

				if GetBP("Sweet Chalice") then
					replicated.Remotes.CommF_:InvokeServer("CakePrinceSpawner", true)
					_G.AutoAttackDoughKing = true
				else
					_G.AutoAttackDoughKing = false
				end

				if GetBP("God's Chalice") and GetM("Conjured Cocoa") >= 10 then
					replicated.Remotes.CommF_:InvokeServer("SweetChaliceNpc")
				end

				local ok = not plr.Backpack:FindFirstChild("God's Chalice")

				if not ok then
					ok = plr.Character:FindFirstChild("God's Chalice")
				end

				if ok then
					_G.FarmEliteHunt = true
				else
					_G.FarmEliteHunt = false
				end

				if GetM("Conjured Cocoa") <= 10 then
					local v451 = GetConnectionEnemies({
						"Cocoa Warrior",
						"Chocolate Bar Battler"
					})

					if v451 then
						while true do
							task.wait()
							Attack.Kill(v451, _G.AutoDoughKing)

							if _G.AutoDoughKing == false then
								break
							elseif not v451.Parent or v451.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(402.71890258789062, 81.060501098632812, -12259.54296875))
					end
				end
			end)
		end
	end
end)
task.spawn(function()
	while task.wait() do
		if _G.AutoAttackDoughKing then
			pcall(function()
				local v452 = GetConnectionEnemies("Dough King")

				if v452 then
					while true do
						task.wait()
						Attack.Kill(v452, _G.AutoAttackDoughKing)

						if not _G.AutoAttackDoughKing then
							break
						elseif not v452.Parent or v452.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(-1943.6765, 251.5095, -12337.8809))
				end
			end)
		end
	end
end)

do
	task.spawn(function()
		while task.wait() do
			if _G.AutoHop_Dough then
				pcall(function()
					local v453 = GetConnectionEnemies("Dough King")

					if v453 then
						while true do
							task.wait()
							Attack.Kill(v453, _G.AutoHop_Dough)

							if not _G.AutoHop_Dough then
								break
							elseif not v453.Parent or v453.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(-1943.6765, 251.5095, -12337.8809))
						task.wait(2)
						HopServer()
					end
				end)
			end
		end
	end)
end

task.spawn(function()
	local LocalPlayer2 = game.Players.LocalPlayer
	local t15 = {
		"Reborn Skeleton",
		"Living Zombie",
		"Demonic Soul",
		"Posessed Mummy"
	}
	local t16 = {
		{
			"HauntedQuest1",
			1,
			"Reborn Skeleton",
			1975
		},
		{
			"HauntedQuest1",
			2,
			"Living Zombie",
			2000
		},
		{
			"HauntedQuest2",
			1,
			"Demonic Soul",
			2025
		},
		{
			"HauntedQuest2",
			2,
			"Posessed Mummy",
			2050
		}
	}
	local t17 = {
		CFrame.new(-9495.6806640625, 453.58624267578125, 5977.3486328125),
		PosMsList["Reborn Skeleton"],
		PosMsList["Living Zombie"],
		PosMsList["Demonic Soul"]
	}
	local n3 = 1
	local u459

	QuestWantedMob = function()
		local ok, result = pcall(function()
			local Quest = LocalPlayer2.PlayerGui.Main.Quest

			if Quest.Visible then
				return Quest.Container.QuestTitle.Title.Text
			end

			return nil
		end)

		if not ok or not result then
			return nil
		end

		local v463 = string.lower(result)

		for _, v in ipairs(t16) do
			local v466 = string.lower(v[3])

			if not string.find(v463, string.sub(v466, 1, #v466 - 1), 1, true) then
				continue
			end

			return v[3]
		end

		return nil
	end

	while task.wait(0.5) do
		if _G.AutoFarm_Bone then
			local exitTo

			repeat
				pcall(function()
					local HumanoidRootPart = LocalPlayer2.Character and LocalPlayer2.Character:FindFirstChild("HumanoidRootPart")

					if not HumanoidRootPart then
						return
					end

					local v469, GetNearestEnemy_, v471, GetConnectionEnemies_, v473, now, GetConnectionEnemies_2, v476, v477, v478, t18, v480

					if not _G.AcceptQuestB or _G.CheckQuestVisible(LocalPlayer2) then
						v469 = QuestWantedMob()
						GetNearestEnemy_ = GetNearestEnemy

						if v469 then
							t18 = { v469 }
							v471 = GetNearestEnemy_(t18)

							if v471 then
								u459 = nil
								v478 = tick() + 30

								while true do
									task.wait()
									Attack.Kill(v471, true)

									if not _G.AutoFarm_Bone then
										break
									elseif not v471.Parent or v471.Humanoid.Health <= 0 or v478 < tick() then
										break
									end
								end
							else
								GetConnectionEnemies_ = GetConnectionEnemies
								v480 = v469

								if v480 then
									v480 = { v469 } or t15

									if not GetConnectionEnemies_(v480) then
										if v469 and PosMsList[v469] then
											v473 = PosMsList[v469]
											_tp(v473)

											return
										end

										v473 = t17[n3]

										if not ((v473.Position - HumanoidRootPart.Position).Magnitude <= 60) then
											u459 = nil
											_tp(v473)

											return
										end

										now = u459

										if now then
											u459 = now

											if tick() - u459 > 5 then
												n3 = n3 % #t17 + 1
												u459 = nil
											end
										else
											now = tick()
											u459 = now

											if tick() - u459 > 5 then
												n3 = n3 % #t17 + 1
												u459 = nil
											end
										end

										_tp(v473)

										return
									end

									GetConnectionEnemies_2 = GetConnectionEnemies
									v476 = v469 and { v469 } or t15
									v477 = GetConnectionEnemies_2(v476)

									if v477 and v477:FindFirstChild("HumanoidRootPart") then
										_tp(v477.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
									end
								else
									v480 = t15

									if not GetConnectionEnemies_(v480) then
										if v469 and PosMsList[v469] then
											v473 = PosMsList[v469]
											_tp(v473)

											return
										end

										v473 = t17[n3]

										if not ((v473.Position - HumanoidRootPart.Position).Magnitude <= 60) then
											u459 = nil
											_tp(v473)

											return
										end

										now = u459

										if now then
											u459 = now

											if tick() - u459 > 5 then
												n3 = n3 % #t17 + 1
												u459 = nil
											end
										else
											now = tick()
											u459 = now

											if tick() - u459 > 5 then
												n3 = n3 % #t17 + 1
												u459 = nil
											end
										end

										_tp(v473)

										return
									end

									GetConnectionEnemies_2 = GetConnectionEnemies
									v476 = v469 and { v469 } or t15
									v477 = GetConnectionEnemies_2(v476)

									if v477 and v477:FindFirstChild("HumanoidRootPart") then
										_tp(v477.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
									end
								end
							end
						else
							v471 = GetNearestEnemy_(t15)

							if v471 then
								u459 = nil
								v478 = tick() + 30

								while true do
									task.wait()
									Attack.Kill(v471, true)

									if not _G.AutoFarm_Bone then
										break
									elseif not v471.Parent or v471.Humanoid.Health <= 0 or v478 < tick() then
										break
									end
								end
							else
								GetConnectionEnemies_ = GetConnectionEnemies

								if GetConnectionEnemies_(t15) then
									GetConnectionEnemies_2 = GetConnectionEnemies
									v476 = v469 and { v469 } or t15
									v477 = GetConnectionEnemies_2(v476)

									if v477 and v477:FindFirstChild("HumanoidRootPart") then
										_tp(v477.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
									end
								else
									if v469 and PosMsList[v469] then
										v473 = PosMsList[v469]
									else
										v473 = t17[n3]

										if (v473.Position - HumanoidRootPart.Position).Magnitude <= 60 then
											now = u459

											if now then
												u459 = now

												if tick() - u459 > 5 then
													n3 = n3 % #t17 + 1
													u459 = nil
												end
											else
												now = tick()
												u459 = now

												if tick() - u459 > 5 then
													n3 = n3 % #t17 + 1
													u459 = nil
												end
											end
										else
											u459 = nil
										end
									end

									_tp(v473)
								end
							end
						end

						return
					end

					local cFrame3 = CFrame.new(-9516.99316, 172.01718, 6078.46533)
					local v482 = tick() + 45

					repeat
						_tp(cFrame3)
						task.wait(0.5)
						HumanoidRootPart = LocalPlayer2.Character and LocalPlayer2.Character:FindFirstChild("HumanoidRootPart")
					until not _G.AutoFarm_Bone or not HumanoidRootPart or (cFrame3.Position - HumanoidRootPart.Position).Magnitude <= 50 or v482 < tick()

					if not _G.AutoFarm_Bone or not HumanoidRootPart or (cFrame3.Position - HumanoidRootPart.Position).Magnitude > 50 then
						return
					end

					local Value = LocalPlayer2.Data.Level.Value
					local t19 = {}

					for _, v in ipairs(t16) do
						if v[4] <= Value then
							table.insert(t19, v)
						end
					end

					if #t19 > 0 then
						local v487 = t19[math.random(1, #t19)]

						game.ReplicatedStorage.Remotes.CommF_:InvokeServer("StartQuest", v487[1], v487[2])
					end

					v469 = QuestWantedMob()
					GetNearestEnemy_ = GetNearestEnemy

					if v469 then
						v471 = GetNearestEnemy_({ v469 })

						if v471 then
							u459 = nil
							v478 = tick() + 30

							while true do
								task.wait()
								Attack.Kill(v471, true)

								if not _G.AutoFarm_Bone then
									break
								elseif not v471.Parent or v471.Humanoid.Health <= 0 or v478 < tick() then
									break
								end
							end
						else
							GetConnectionEnemies_ = GetConnectionEnemies
							v480 = v469

							if v480 then
								if not GetConnectionEnemies_({ v469 } or t15) then
									if v469 and PosMsList[v469] then
										v473 = PosMsList[v469]
										_tp(v473)

										return
									end

									v473 = t17[n3]

									if not ((v473.Position - HumanoidRootPart.Position).Magnitude <= 60) then
										u459 = nil
										_tp(v473)

										return
									end

									now = u459

									if now then
										u459 = now

										if tick() - u459 > 5 then
											n3 = n3 % #t17 + 1
											u459 = nil
										end
									else
										now = tick()
										u459 = now

										if tick() - u459 > 5 then
											n3 = n3 % #t17 + 1
											u459 = nil
										end
									end

									_tp(v473)

									return
								end

								v477 = GetConnectionEnemies(v469 and { v469 } or t15)

								if v477 and v477:FindFirstChild("HumanoidRootPart") then
									_tp(v477.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
								end
							else
								v480 = t15

								if not GetConnectionEnemies_(v480) then
									if v469 and PosMsList[v469] then
										v473 = PosMsList[v469]
										_tp(v473)

										return
									end

									v473 = t17[n3]

									if not ((v473.Position - HumanoidRootPart.Position).Magnitude <= 60) then
										u459 = nil
										_tp(v473)

										return
									end

									now = u459

									if now then
										u459 = now

										if tick() - u459 > 5 then
											n3 = n3 % #t17 + 1
											u459 = nil
										end
									else
										now = tick()
										u459 = now

										if tick() - u459 > 5 then
											n3 = n3 % #t17 + 1
											u459 = nil
										end
									end

									_tp(v473)

									return
								end

								GetConnectionEnemies_2 = GetConnectionEnemies
								v476 = v469 and { v469 } or t15
								v477 = GetConnectionEnemies_2(v476)

								if v477 and v477:FindFirstChild("HumanoidRootPart") then
									_tp(v477.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
								end
							end
						end
					else
						t18 = t15
						v471 = GetNearestEnemy_(t18)

						if v471 then
							u459 = nil
							v478 = tick() + 30

							while true do
								task.wait()
								Attack.Kill(v471, true)

								if not _G.AutoFarm_Bone then
									break
								elseif not v471.Parent or v471.Humanoid.Health <= 0 or v478 < tick() then
									break
								end
							end
						else
							GetConnectionEnemies_ = GetConnectionEnemies
							v480 = v469

							if v480 then
								v480 = { v469 } or t15

								if not GetConnectionEnemies_(v480) then
									if v469 and PosMsList[v469] then
										v473 = PosMsList[v469]
										_tp(v473)

										return
									end

									v473 = t17[n3]

									if not ((v473.Position - HumanoidRootPart.Position).Magnitude <= 60) then
										u459 = nil
										_tp(v473)

										return
									end

									now = u459

									if now then
										u459 = now

										if tick() - u459 > 5 then
											n3 = n3 % #t17 + 1
											u459 = nil
										end
									else
										now = tick()
										u459 = now

										if tick() - u459 > 5 then
											n3 = n3 % #t17 + 1
											u459 = nil
										end
									end

									_tp(v473)

									return
								end

								GetConnectionEnemies_2 = GetConnectionEnemies
								v476 = v469 and { v469 } or t15
								v477 = GetConnectionEnemies_2(v476)

								if v477 and v477:FindFirstChild("HumanoidRootPart") then
									_tp(v477.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
								end
							else
								v480 = t15

								if not GetConnectionEnemies_(v480) then
									if v469 and PosMsList[v469] then
										v473 = PosMsList[v469]
										_tp(v473)

										return
									end

									v473 = t17[n3]

									if not ((v473.Position - HumanoidRootPart.Position).Magnitude <= 60) then
										u459 = nil
										_tp(v473)

										return
									end

									now = u459

									if now then
										u459 = now

										if tick() - u459 > 5 then
											n3 = n3 % #t17 + 1
											u459 = nil
										end
									else
										now = tick()
										u459 = now

										if tick() - u459 > 5 then
											n3 = n3 % #t17 + 1
											u459 = nil
										end
									end

									_tp(v473)

									return
								end

								GetConnectionEnemies_2 = GetConnectionEnemies
								v476 = v469 and { v469 } or t15
								v477 = GetConnectionEnemies_2(v476)

								if v477 and v477:FindFirstChild("HumanoidRootPart") then
									_tp(v477.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
								end
							end
						end
					end
				end)
				exitTo = nil

				while task.wait(0.5) do
					if _G.AutoFarm_Bone then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)
task.spawn(function()
	while task.wait(Sec) do
		if _G.AutoHytHallow then
			pcall(function()
				local v488 = GetConnectionEnemies("Soul Reaper")

				if v488 then
					while true do
						task.wait()
						Attack.Kill(v488, _G.AutoHytHallow)

						if v488.Humanoid.Health <= 0 then
							break
						elseif _G.AutoHytHallow == false then
							break
						end
					end
				elseif GetBP("Hallow Essence") then
					while true do
						task.wait(0.1)
						_tp(CFrame.new(-8932.322265625, 146.83154296875, 6062.55078125))

						if _G.AutoHytHallow == false then
							break
						elseif plr.Character.HumanoidRootPart.CFrame == CFrame.new(-8932.322265625, 146.83154296875, 6062.55078125) then
							break
						end
					end

					EquipWeapon("Hallow Essence")
				else
					while true do
						task.wait(0.1)
						replicated.Remotes.CommF_:InvokeServer("Bones", "Buy", 1, 1)

						if _G.AutoHytHallow == false then
							break
						elseif GetBP("Hallow Essence") then
							break
						end
					end
				end
			end)
		end
	end
end)
task.spawn(function()
	while task.wait(Sec) do
		pcall(function()
			if _G.Auto_Random_Bone then
				repeat
					task.wait()
					replicated.Remotes.CommF_:InvokeServer("Bones", "Buy", 1, 1)
				until not _G.Auto_Random_Bone
			end
		end)
	end
end)
task.spawn(function()
	while task.wait(Sec) do
		if _G.TryLucky then
			local cFrame3 = CFrame.new(-8761.3154296875, 164.85829162598, 6161.1567382813)

			if plr.Character.HumanoidRootPart.CFrame ~= cFrame3 then
				_tp(CFrame.new(-8761.3154296875, 164.85829162598, 6161.1567382813))
			elseif plr.Character.HumanoidRootPart.CFrame == cFrame3 then
				replicated.Remotes.CommF_:InvokeServer("gravestoneEvent", 1)
			end
		end
	end
end)

do
	task.spawn(function()
		while task.wait(Sec) do
			if _G.Praying then
				local cFrame3 = CFrame.new(-8761.3154296875, 164.85829162598, 6161.1567382813)

				if plr.Character.HumanoidRootPart.CFrame ~= cFrame3 then
					_tp(CFrame.new(-8761.3154296875, 164.85829162598, 6161.1567382813))
				elseif plr.Character.HumanoidRootPart.CFrame == cFrame3 then
					replicated.Remotes.CommF_:InvokeServer("gravestoneEvent", 2)
				end
			end
		end
	end)
end

Check_Eye = function()
	local IslandModel = workspace.Map.TikiOutpost.IslandModel
	local n4 = 0

	for _, v in ipairs({
		IslandModel.Eye1,
		IslandModel.Eye2,
		IslandModel.IslandChunks.E.Eye3,
		IslandModel.IslandChunks.E.Eye4
	}) do
		if v and v.Transparency ~= 1 then
			n4 += 1
		end
	end

	return n4, n4 == 4
end
task.spawn(function()
	while task.wait(Sec) do
		if _G.FarmTyrant then
			pcall(function()
				if not plr.Character then
					return
				end

				local HumanoidRootPart = plr.Character:FindFirstChild("HumanoidRootPart")

				if not HumanoidRootPart then
					return
				end

				local vector3 = Vector3.new(-16268.287, 152.616, 1390.773)

				if (HumanoidRootPart.Position - vector3).Magnitude > 5 then
					_tp(CFrame.new(vector3))

					while true do
						task.wait()

						if not _G.FarmTyrant then
							break
						end

						if not plr.Character then
							continue
						elseif not plr.Character:FindFirstChild("HumanoidRootPart") or not ((plr.Character.HumanoidRootPart.Position - vector3).Magnitude <= 5) then
							continue
						end

						break
					end
				end

				local TyrantOfTheSkies = workspace.Enemies:FindFirstChild("Tyrant of the Skies")

				if TyrantOfTheSkies and TyrantOfTheSkies:FindFirstChild("Humanoid") and TyrantOfTheSkies.Humanoid.Health > 0 then
					while _G.FarmTyrant do
						if Attack and Attack.Kill then
							Attack.Kill(TyrantOfTheSkies, _G.FarmTyrant)
						end

						task.wait()

						if not _G.FarmTyrant or not TyrantOfTheSkies.Parent or TyrantOfTheSkies.Humanoid.Health <= 0 then
							break
						end
					end

					return
				end

				for _, v in ipairs({
					"Serpent Hunter",
					"Skull Slayer",
					"Isle Champion",
					"Sun-kissed Warrior"
				}) do
					if not _G.FarmTyrant then
						break
					end

					for _, child in pairs(workspace.Enemies:GetChildren()) do
						if not _G.FarmTyrant then
							break
						end

						if child and child.Name == v and child:FindFirstChild("HumanoidRootPart") and child:FindFirstChild("Humanoid") and child.Humanoid.Health > 0 then
							if (HumanoidRootPart.Position - child.HumanoidRootPart.Position).Magnitude > 5000 then
								_tp(child.HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))

								local now = tick()

								repeat
									task.wait()
									HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")
								until not _G.FarmTyrant or not HumanoidRootPart or (HumanoidRootPart.Position - child.HumanoidRootPart.Position).Magnitude <= 6 or tick() - now > 8
							end

							while _G.FarmTyrant do
								if Attack and Attack.Kill then
									Attack.Kill(child, _G.FarmTyrant)
								end

								task.wait()

								if not _G.FarmTyrant or not child.Parent or child.Humanoid.Health <= 0 then
									break
								end
							end
						end
					end
				end
			end)
		end
	end
end)
sendSkillKey = function(p72)
	local VirtualInputManager = game:GetService("VirtualInputManager")

	VirtualInputManager:SendKeyEvent(true, p72, false, game)
	task.wait(0.05)
	VirtualInputManager:SendKeyEvent(false, p72, false, game)
end

do
	equipAndUseSkill = function(p73)
		if not plr.Character or not plr.Character:FindFirstChild("Humanoid") or not (plr.Character.Humanoid.Health > 0) then
			return
		end

		for _, child in pairs(plr.Backpack:GetChildren()) do
			if child:IsA("Tool") then
				if child.ToolTip == p73 then
					child.Parent = plr.Character
					task.wait(0.12)

					local v506, v507, v508 = ipairs({
						"Z",
						"X",
						"C",
						"V",
						"F"
					})
					local v509 = geniter(v506, v507, v508)
					local v510 = table.pack(v509())

					if v510[1] then
						local v511 = v510[3]

						while _G.FarmPhaBinh do
							pcall(function()
								sendSkillKey(v511)
							end)
							task.wait(0.12)

							local v512 = table.pack(v509())

							if not v512[1] then
								break
							end

							v511 = v512[3]
						end
					end

					child.Parent = plr.Backpack

					return
				end
			end
		end
	end
end

local phaBinhPoints = {
	CFrame.new(-16332.5263671875, 158.07200622558594, 1440.324951171875),
	CFrame.new(-16288.609375, 158.16700744628906, 1470.3680419921875),
	CFrame.new(-16245.412109375, 158.43699645996094, 1463.365966796875),
	CFrame.new(-16212.46875, 158.16700744628906, 1466.343994140625),
	CFrame.new(-16211.9462890625, 158.07200622558594, 1322.39794921875),
	CFrame.new(-16260.921875, 154.92100524902344, 1323.615966796875),
	CFrame.new(-16297.0595703125, 159.322998046875, 1317.2239990234375),
	CFrame.new(-16335.0966796875, 159.33399963378906, 1324.885986328125)
}

Core.PhaBinhPoints = phaBinhPoints
task.spawn(function()
	while task.wait(Sec) do
		if _G.FarmPhaBinh then
			local exitTo

			repeat
				pcall(function()
					if plr then
						if plr.Character then
							if plr.Character:FindFirstChild("HumanoidRootPart") then
								if plr.Character:FindFirstChild("Humanoid") and plr.Character.Humanoid.Health > 0 then
									for _, phaBinhPoint in ipairs(phaBinhPoints) do
										if not _G.FarmPhaBinh then
											break
										end

										_tp(phaBinhPoint)

										local v517 = false
										local now = tick()

										while tick() - now < 12 and _G.FarmPhaBinh do
											local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

											if not HumanoidRootPart then
												break
											end

											if not ((HumanoidRootPart.Position - phaBinhPoint.Position).Magnitude <= 3) then
												task.wait(0.1)

												continue
											end

											v517 = true

											break
										end

										if _G.FarmPhaBinh and v517 then
											equipAndUseSkill("Melee")
											equipAndUseSkill("Sword")
											equipAndUseSkill("Gun")
										end
									end

									return
								end
							end
						end
					end
				end)
				exitTo = nil

				while task.wait(Sec) do
					if _G.FarmPhaBinh then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)
task.spawn(function()
	processEnemy = function(p74, p75)
		if p74:FindFirstChild("Humanoid") and p74:FindFirstChild("HumanoidRootPart") and p74.Humanoid.Health > 0 then
			if p74.Name == p75 then
				while true do
					task.wait()
					Attack.Kill(p74, getgenv().AutoMaterial)

					if not getgenv().AutoMaterial then
						break
					elseif not p74.Parent or p74.Humanoid.Health <= 0 then
						break
					end
				end
			end
		end
	end
	handleEnemySpawns = function()
		for _, child in pairs(game:GetService("Workspace")._WorldOrigin.EnemySpawns:GetChildren()) do
			for _, v in ipairs(MMon) do
				if string.find(child.Name, v) and (game.Players.LocalPlayer.Character.HumanoidRootPart.Position - child.Position).Magnitude >= 10 then
					_tp(child.CFrame * Pos)
				end
			end
		end
	end

	while task.wait() do
		if getgenv().AutoMaterial then
			pcall(function()
				if getgenv().SelectMaterial then
					MaterialMon(getgenv().SelectMaterial)
					_tp(MPos)
				end

				for _, v in ipairs(MMon) do
					for _, child in pairs(workspace.Enemies:GetChildren()) do
						processEnemy(child, v)
					end
				end

				handleEnemySpawns()
			end)
		end
	end
end)

do
	task.spawn(function()
		while task.wait(Sec) do
			if _G.FarmBoss then
				pcall(function()
					local v528 = QuestBeta()[2] ~= nil and QuestBeta()[3] ~= nil
					local Text = plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text

					if _G.AcceptQuestBoss and v528 then
						if not string.find(Text, QuestBeta()[0]) then
							replicated.Remotes.CommF_:InvokeServer("AbandonQuest")
						end

						if plr.PlayerGui.Main.Quest.Visible == false then
							_tp(QuestBeta()[5])

							if (Root.Position - QuestBeta()[5].Position).Magnitude <= 5 then
								replicated.Remotes.CommF_:InvokeServer("StartQuest", QuestBeta()[3], QuestBeta()[2])
							end
						elseif plr.PlayerGui.Main.Quest.Visible == true then
							if workspace.Enemies:FindFirstChild(QuestBeta()[1]) then
								for _, child in pairs(workspace.Enemies:GetChildren()) do
									if Attack.Alive(child) and child.Name == QuestBeta()[1] then
										if string.find(Text, QuestBeta()[0]) then
											while true do
												task.wait()
												Attack.Kill(child, _G.FarmBoss)

												if not _G.FarmBoss then
													break
												elseif child.Humanoid.Health <= 0 or not child.Parent or plr.PlayerGui.Main.Quest.Visible == false then
													break
												end
											end
										else
											replicated.Remotes.CommF_:InvokeServer("AbandonQuest")
										end
									end
								end
							else
								_tp(QuestBeta()[4])

								if replicated:FindFirstChild(QuestBeta()[1]) then
									_tp(replicated:FindFirstChild(QuestBeta()[1]).HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
								end
							end
						end
					elseif workspace.Enemies:FindFirstChild(QuestBeta()[1]) then
						for _, child in pairs(workspace.Enemies:GetChildren()) do
							if Attack.Alive(child) and child.Name == QuestBeta()[1] then
								while true do
									task.wait()
									Attack.Kill(child, _G.FarmBoss)

									if not _G.FarmBoss then
										break
									elseif child.Humanoid.Health <= 0 or not child.Parent then
										break
									end
								end
							end
						end
					else
						_tp(QuestBeta()[4])

						if replicated:FindFirstChild(QuestBeta()[1]) then
							_tp(replicated:FindFirstChild(QuestBeta()[1]).HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
						end
					end
				end)
			end
		end
	end)
end

task.spawn(function()
	while task.wait(0.3) do
		if _G.AutoFarmAllBoss then
			pcall(function()
				local LocalPlayer2 = game.Players.LocalPlayer

				if LocalPlayer2.Character then
					if LocalPlayer2.Character:FindFirstChild("HumanoidRootPart") then
						local HumanoidRootPart = LocalPlayer2.Character.HumanoidRootPart
						local v536
						local huge = math.huge

						for _, child in pairs(workspace.Enemies:GetChildren()) do
							if child:FindFirstChild("HumanoidRootPart") then
								if child:FindFirstChild("Humanoid") and child.Humanoid.Health > 0 and table.find(BossList, child.Name) then
									local Magnitude = (HumanoidRootPart.Position - child.HumanoidRootPart.Position).Magnitude

									if Magnitude < huge then
										v536 = child
										huge = Magnitude
									end
								end
							end
						end

						if v536 and v536:FindFirstChild("HumanoidRootPart") then
							local HumanoidRootPart2 = v536.HumanoidRootPart
							local Humanoid = v536.Humanoid

							repeat
								task.wait(0.1)

								if not _G.AutoFarmAllBoss then
									break
								end

								local v543 = HumanoidRootPart2.CFrame * CFrame.new(0, 5, 0)

								if (HumanoidRootPart.Position - v543.Position).Magnitude > 100 then
									LocalPlayer2.Character:PivotTo(v543)
								else
									_tp(v543)
								end

								if Attack and typeof(Attack.Kill) == "function" then
									Attack.Kill(v536, true)
								end
							until not v536.Parent or Humanoid.Health <= 0 or not _G.AutoFarmAllBoss
						end

						return
					end
				end
			end)
		end
	end
end)
RunSer.RenderStepped:Connect(function()
	pcall(function()
		if _G.FarmMastery_Dev or _G.FarmMastery_G or _G.FarmMastery_S then
			for _, child in pairs(plr.PlayerGui.Notifications:GetChildren()) do
				if child.Name == "NotificationTemplate" and string.find(child.Text, "Skill locked!") then
					child:Destroy()
				end
			end
		end
	end)
end)

do
	local function v546(p76)
		if p76 == "Cake" then
			return GetConnectionEnemies(mastery1), CFrame.new(-1943.676513671875, 251.50956726074219, -12337.880859375)
		end

		if p76 == "Bone" then
			return GetConnectionEnemies(mastery2), CFrame.new(-9495.6806640625, 453.58624267578125, 5977.3486328125)
		end

		if p76 ~= "Selected Mob" or not getgenv().SelectMob then
			if World3 then
				return GetConnectionEnemies(mastery1), CFrame.new(-1943.676513671875, 251.50956726074219, -12337.880859375)
			end

			if getgenv().SelectMob then
				return GetConnectionEnemies({ getgenv().SelectMob }), nil
			end

			return nil, nil
		end

		local SelectMob = getgenv().SelectMob
		local v548 = GetConnectionEnemies({ SelectMob })
		local CFrame_

		if not v548 and IslandData then
			for _, v in pairs(IslandData) do
				if v.Mobs and table.find(v.Mobs, SelectMob) and v.CFrame then
					CFrame_ = v.CFrame

					break
				end
			end
		end

		return v548, CFrame_
	end

	task.spawn(function()
		while task.wait(Sec) do
			if _G.FarmMastery_Dev or _G.Auto_Fruit_Mastery then
				local exitTo

				repeat
					pcall(function()
						local SelectIslandMastery = getgenv().SelectIslandMastery or _G.SelectIslandMastery or SelectIsland
						local v554, v555 = v546(SelectIslandMastery or "Cake")

						if v554 then
							HealthM = v554.Humanoid.MaxHealth * (_G.MasteryHealthPct or 70) / 100

							repeat
								task.wait()
								MousePos = v554.HumanoidRootPart.Position
								Attack.Mas(v554, _G.FarmMastery_Dev or _G.Auto_Fruit_Mastery)
							until not _G.FarmMastery_Dev and not _G.Auto_Fruit_Mastery or v554.Humanoid.Health <= 0 or not v554.Parent
						elseif v555 then
							_tp(v555)
						end
					end)
					exitTo = nil

					while task.wait(Sec) do
						if _G.FarmMastery_Dev or _G.Auto_Fruit_Mastery then
							exitTo = 1

							break
						end
					end
				until exitTo ~= 1

				return
			end
		end
	end)
	task.spawn(function()
		while task.wait(Sec) do
			if _G.FarmMastery_G or _G.Auto_Gun_Mastery then
				pcall(function()
					local SelectIslandMastery = getgenv().SelectIslandMastery or _G.SelectIslandMastery
					local v557, v558 = v546(SelectIslandMastery or SelectIsland or "Cake")

					if v557 then
						HealthM = v557.Humanoid.MaxHealth * (_G.MasteryHealthPct or 70) / 100

						local REShootGunEvent

						while true do
							task.wait()
							MousePos = v557.HumanoidRootPart.Position
							Attack.Masgun(v557, _G.FarmMastery_G or _G.Auto_Gun_Mastery)

							local Modules = replicated:FindFirstChild("Modules")
							local Net = Modules and Modules:FindFirstChild("Net")

							REShootGunEvent = Net and Net:FindFirstChild("RE/ShootGunEvent")

							local Tool = plr.Character:FindFirstChildOfClass("Tool")

							if Tool and Tool.ToolTip == "Gun" then
								if Tool.Name == "Skull Guitar" then
									SoulGuitar = true
									Tool.RemoteEvent:FireServer("TAP", MousePos)
									vim1:SendMouseButtonEvent(0, 0, 0, true, game, 1)
									task.wait(0.05)
									vim1:SendMouseButtonEvent(0, 0, 0, false, game, 1)
									task.wait(0.05)
								else
									SoulGuitar = false

									if REShootGunEvent then
										break
									end

									vim1:SendMouseButtonEvent(0, 0, 0, true, game, 1)
									task.wait(0.05)
									vim1:SendMouseButtonEvent(0, 0, 0, false, game, 1)
									task.wait(0.05)
								end
							end

							if not _G.FarmMastery_G and not _G.Auto_Gun_Mastery or v557.Humanoid.Health <= 0 or not v557.Parent then
								SoulGuitar = false

								return
							end
						end

						local exitTo2

						repeat
							REShootGunEvent:FireServer(MousePos, { v557.HumanoidRootPart })
							exitTo2 = nil

							while true do
								vim1:SendMouseButtonEvent(0, 0, 0, true, game, 1)
								task.wait(0.05)
								vim1:SendMouseButtonEvent(0, 0, 0, false, game, 1)
								task.wait(0.05)

								local exitTo

								while (_G.FarmMastery_G or _G.Auto_Gun_Mastery) and not (v557.Humanoid.Health <= 0) and v557.Parent do
									task.wait()
									MousePos = v557.HumanoidRootPart.Position
									Attack.Masgun(v557, _G.FarmMastery_G or _G.Auto_Gun_Mastery)

									local Modules = replicated:FindFirstChild("Modules")
									local Net = Modules and Modules:FindFirstChild("Net")

									REShootGunEvent = Net and Net:FindFirstChild("RE/ShootGunEvent")

									local Tool = plr.Character:FindFirstChildOfClass("Tool")

									if Tool and Tool.ToolTip == "Gun" then
										if Tool.Name ~= "Skull Guitar" then
											exitTo = 1

											break
										end

										SoulGuitar = true
										Tool.RemoteEvent:FireServer("TAP", MousePos)
										vim1:SendMouseButtonEvent(0, 0, 0, true, game, 1)
										task.wait(0.05)
										vim1:SendMouseButtonEvent(0, 0, 0, false, game, 1)
										task.wait(0.05)
									end
								end

								if exitTo ~= 1 then
									break
								end

								SoulGuitar = false

								if not REShootGunEvent then
									continue
								end

								exitTo2 = 1

								break
							end
						until exitTo2 ~= 1

						SoulGuitar = false
					elseif v558 then
						_tp(v558)
					end
				end)
			end
		end
	end)
	task.spawn(function()
		while task.wait(Sec) do
			pcall(function()
				if _G.FarmMastery_S or _G.Auto_Mastery_All_Sword then
					local v568, v569 = v546(getgenv().SelectIslandMastery or _G.SelectIslandMastery or SelectIsland or "Cake")
					local next_ = next
					local response, v572 = replicated.Remotes.CommF_:InvokeServer("getInventory")
					local exitTo
					local Name

					for _, v in next_, response, v572 do
						if type(v) == "table" and v.Type == "Sword" then
							Name = v.Name

							if tonumber(v.Mastery) >= 1 and tonumber(v.Mastery) <= 599 then
								exitTo = 1

								break
							elseif tonumber(v.Mastery) >= 600 and not GetBP(Name) then
								replicated.Remotes.CommF_:InvokeServer("LoadItem", Name)
							end
						end
					end

					if exitTo == 1 then
						if not GetBP(Name) then
							replicated.Remotes.CommF_:InvokeServer("LoadItem", Name)
						elseif v568 then
							repeat
								task.wait()
								Attack.Sword(v568, _G.FarmMastery_S or _G.Auto_Mastery_All_Sword)
							until not _G.FarmMastery_S and not _G.Auto_Mastery_All_Sword or not v568.Parent or v568.Humanoid.Health <= 0
						elseif v569 then
							_tp(v569)
						end
					end
				end
			end)
		end
	end)
end

Spawn(function()
	while Wait(1) do
		if _G.AutoHopServer then
			pcall(function()
				if not _G.HopTimer then
					_G.HopTimer = tick()
				end

				if (_G.HopDelay or 1800) <= tick() - _G.HopTimer then
					_G.HopTimer = tick()

					if syn and syn.queue_on_teleport then
						syn.queue_on_teleport("loadstring(game:HttpGet('https://raw.githubusercontent.com/bloxfruitsnokey/Redz/refs/heads/main/Chest'))()")
					end

					game:GetService("TeleportService"):Teleport(game.PlaceId, game.Players.LocalPlayer)
				end
			end)
		end
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if Boud then
				local t20 = {
					"HasBuso",
					"Buso"
				}

				if not plr.Character:FindFirstChild(t20[1]) then
					replicated.Remotes.CommF_:InvokeServer(t20[2])
				end
			end
		end)
	end
end)
spawn(function()
	while wait() do
		if getgenv().Observation then
			local exitTo

			repeat
				pcall(function()
					game:GetService("ReplicatedStorage").Remotes.CommE:FireServer("Ken", true)
				end)
				exitTo = nil

				while wait() do
					if getgenv().Observation then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)
spawn(function()
	if wait(0.2) then
		repeat
			pcall(function()
				if _G.RaceClickAutov3 then
					repeat
						replicated.Remotes.CommE:FireServer("ActivateAbility")
						wait(30)
					until not _G.RaceClickAutov3
				end
			end)
		until not wait(0.2)
	end
end)

do
	spawn(function()
		while wait(0.2) do
			pcall(function()
				if _G.RaceClickAutov4 then
					if plr.Character:FindFirstChild("RaceEnergy") then
						if plr.Character:FindFirstChild("RaceEnergy").Value == 1 then
							Useskills("nil", "Y")
						end
					end
				end
			end)
		end
	end)
end

spawn(function()
	while task.wait(Sec) do
		pcall(function()
			if _G.Safemode then
				if plr.Character.Humanoid.Health / plr.Character.Humanoid.MaxHealth * 100 < Num_self then
					shouldTween = true
					_tp(Root.CFrame * CFrame.new(0, 500, 0))
				else
					shouldTween = false
				end
			end
		end)
	end
end)

local t21 = {
	"SlashHit",
	"CurvedRing",
	"SwordSlash",
	"SlashTail"
}

task.spawn(function()
	while task.wait(Sec) do
		if _G.DestroyHit then
			pcall(function()
				for _, child in pairs(workspace._WorldOrigin:GetChildren()) do
					if table.find(t21, child.Name) then
						child:Destroy()
					end
				end
			end)
		end
	end
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if RDeath then
					if replicated.Effect.Container:FindFirstChild("Death") then
						replicated.Effect.Container.Death:Destroy()
					end

					if replicated.Effect.Container:FindFirstChild("Respawn") then
						replicated.Effect.Container.Respawn:Destroy()
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait(Sec) do
		pcall(function()
			if RemoveDamage then
				replicated.Assets.GUI.DamageCounter.Enabled = false
				plr.PlayerGui.Notifications.Enabled = false
			else
				replicated.Assets.GUI.DamageCounter.Enabled = true
				plr.PlayerGui.Notifications.Enabled = true
			end
		end)
	end
end)
spawn(function()
	while wait() do
		pcall(function()
			if getgenv().HopServerAdmin then
				for _, player in pairs(game.Players:GetPlayers()) do
					if table.find({
						"red_game43",
						"rip_indra",
						"Axiore",
						"Polkster",
						"wenlocktoad",
						"Daigrock",
						"toilamvidamme",
						"oofficialnoobie",
						"Uzoth",
						"Azarth",
						"arlthmetic",
						"Death_King",
						"Lunoven",
						"TheGreateAced",
						"rip_fud",
						"drip_mama",
						"layandikit12",
						"Hingoi"
					}, player.Name) then
						Hop()
					end
				end
			end
		end)
	end
end)
spawn(function()
	pcall(function()
		game:GetService("RunService").Stepped:Connect(function()
			if getgenv().NoClip then
				for _, descendant in pairs(game.Players.LocalPlayer.Character:GetDescendants()) do
					if descendant:IsA("BasePart") or descendant:IsA("Part") then
						descendant.CanCollide = false
					end
				end
			end
		end)
	end)
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.Auto_Melee then
					statsSetings("Melee", pSats)
				end
			end)
		end
	end)
end

spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Auto_Sword then
				statsSetings("Sword", pSats)
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Auto_Gun then
				statsSetings("Gun", pSats)
			end
		end)
	end
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.Auto_DevilFruit then
					statsSetings("Devil", pSats)
				end
			end)
		end
	end)
end

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.Auto_Defense then
					statsSetings("Defense", pSats)
				end
			end)
		end
	end)
end

task.spawn(function()
	while task.wait(2) do
		if _G.AutoBuyBait and _G.SelectedBait then
			pcall(function()
				replicated.Modules.Net["RF/Craft"]:InvokeServer("Craft", _G.SelectedBait, {})
			end)
		end
	end
end)

do
	local FishReplicated = replicated:WaitForChild("FishReplicated", 10)
	local FishingRequest = FishReplicated and FishReplicated:WaitForChild("FishingRequest", 10)
	local Config = FishReplicated and require(FishReplicated.FishingClient.Config)
	local GetWaterHeightAtLocation = require(replicated.Util.GetWaterHeightAtLocation)
	local MaxLaunchDistance = Config and Config.Rod and Config.Rod.MaxLaunchDistance or 100
	local t22 = {
		bite = false,
		biteAt = 0,
		casting = false,
		castAt = 0,
		blockedSince = nil
	}

	task.spawn(function()
		if not FishReplicated then
			return
		end

		local ok, result = pcall(function()
			return FishReplicated:WaitForChild("FishingRemote", 15)
		end)

		if ok and result then
			result.OnClientEvent:Connect(function(p77, p78)
				if p77 ~= plr then
					return
				end

				if p78 == "SpawnFishOnBob" then
					t22.bite = true
					t22.biteAt = tick()
				elseif p78 == "ResetBiting" then
					t22.bite = false
				elseif p78 == "ReeledIn" then
					t22.bite = false
					t22.casting = false
				end
			end)
		end
	end)
	FindCastTarget = function(p79, p80, p81)
		local t23 = {
			p79,
			workspace.Characters,
			workspace.Enemies
		}
		local v595 = GetWaterHeightAtLocation(p80.Position)
		local v596 = (p81:GetAttribute("MaxLaunchDistance") or MaxLaunchDistance) * 0.99751243781094523

		for _, v in ipairs({
			0,
			45,
			-45,
			90,
			-90,
			135,
			-135,
			180
		}) do
			local v599 = CFrame.Angles(0, math.rad(v), 0) * p80.CFrame.LookVector
			local _, v601 = workspace:FindPartOnRayWithIgnoreList(Ray.new(p79.Head.Position, v599 * v596), t23)
			local v602, v603 = workspace:FindPartOnRayWithIgnoreList(Ray.new(v601 + Vector3.new(0, 3, 0), Vector3.new(0, -500, 0)), t23)

			if not v602 and not (v603.Y < v595) then
				continue
			end

			local vector3 = Vector3.new(v601.X, math.max(v603.Y, v595), v601.Z)

			if not (v602 and game:GetService("CollectionService"):HasTag(v602, Config.WATER_BODY_TAG) or vector3.Y <= v595) then
				continue
			end

			p80.CFrame = CFrame.new(p80.Position, p80.Position + Vector3.new(v599.X, 0, v599.Z))

			return vector3
		end

		local _, v606 = workspace:FindPartOnRayWithIgnoreList(Ray.new(p79.Head.Position, p80.CFrame.LookVector * v596), t23)

		return Vector3.new(v606.X, math.max(v606.Y, v595), v606.Z)
	end
	task.spawn(function()
		while task.wait(0.4) do
			if _G.AutoFishing then
				pcall(function()
					local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")
					local Humanoid = plr.Character and plr.Character:FindFirstChildOfClass("Humanoid")

					if not HumanoidRootPart or not Humanoid or Humanoid.Health <= 0 then
						return
					end

					local Tool = plr.Character:FindFirstChildOfClass("Tool")
					local _GSelectedRod = Tool and _G.SelectedRod and Tool.Name ~= _G.SelectedRod and plr.Backpack:FindFirstChild(_G.SelectedRod)

					if not Tool or not Tool:FindFirstChild("FishingRodData") or _GSelectedRod then
						local _GSelectedRod2 = _G.SelectedRod and plr.Backpack:FindFirstChild(_G.SelectedRod)

						if not _GSelectedRod2 then
							for _, child in ipairs(plr.Backpack:GetChildren()) do
								if child:IsA("Tool") and child:FindFirstChild("FishingRodData") then
									_GSelectedRod2 = child

									break
								end
							end
						end

						if _GSelectedRod2 then
							t22.casting = false
							Humanoid:EquipTool(_GSelectedRod2)
							task.wait(0.6)
						end

						return
					end

					if t22.bite or t22.casting and Tool:GetAttribute("ServerState") == "Biting" then
						t22.bite = false
						FishingRequest:InvokeServer("Catching", true)
						task.wait(_G.FishCatchDelay or math.random(35, 55) / 10)
						FishingRequest:InvokeServer("Catch", 1, 0, math.random(80, 95) / 100)
						t22.casting = false
						task.wait(1)

						return
					end

					if t22.casting then
						if tick() - t22.castAt > 25 then
							pcall(function()
								FishingRequest:InvokeServer("ReeledIn")
							end)
							t22.casting = false
						end

						return
					end

					local attribute = Tool:GetAttribute("State")
					local attribute2 = Tool:GetAttribute("ServerState")

					if (attribute == nil or attribute == "ReeledIn") and (attribute2 == nil or attribute2 == "ReeledIn") then
						t22.blockedSince = nil
					else
						t22.blockedSince = t22.blockedSince or tick()

						if tick() - t22.blockedSince < 15 then
							return
						end
					end

					local attribute3 = plr.Data.FishingData:GetAttribute("SelectedBait")

					if attribute3 == nil or attribute3 == "None" then
						return
					end

					local v617 = FindCastTarget(plr.Character, HumanoidRootPart, Tool)

					if not v617 then
						return
					end

					FishingRequest:InvokeServer("StartCasting")
					task.wait(0.2)

					local response, v619 = FishingRequest:InvokeServer("CastLineAtLocation", v617, 100, true)

					if response and not v619 then
						t22.casting = true
						t22.castAt = tick()
						t22.blockedSince = nil
					end
				end)
			else
				t22.casting = false
				t22.bite = false
			end
		end
	end)
end

HasQuest3 = function()
	local Quest = plr.PlayerGui:FindFirstChild("Quest") or plr.PlayerGui:FindFirstChild("QuestGui")

	if Quest and Quest:FindFirstChild("Container") then
		if Quest.Container:FindFirstChild("QuestTitle") then
			return true
		end
	end

	return false
end
task.spawn(function()
	while task.wait(1) do
		if _G.AutoFishingQuest then
			pcall(function()
				if not HasQuest3() then
					replicated.Modules.Net["RF/JobsRemoteFunction"]:InvokeServer("FishingNPC", "Angler", "AskQuest")
				end
			end)
		end
	end
end)
task.spawn(function()
	while task.wait(5) do
		if _G.AutoQuestComplete then
			pcall(function()
				replicated.Modules.Net["RF/JobsRemoteFunction"]:InvokeServer("FishingNPC", "FinishQuest")
			end)
		end
	end
end)
task.spawn(function()
	while task.wait(5) do
		if _G.AutoSellFish then
			pcall(function()
				replicated.Modules.Net["RF/JobsRemoteFunction"]:InvokeServer("FishingNPC", "SellFish")
			end)
		end
	end
end)
task.spawn(function()
	while task.wait(0.5) do
		if _G.AutoSkillZ then
			pcall(function()
				replicated.Modules.Net["RF/JobToolAbilities"]:InvokeServer("Z", true)
			end)
		end
	end
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.TravelDres and plr.Data.Level.Value >= 700 then
					if workspace.Map.Ice.Door.CanCollide == true and workspace.Map.Ice.Door.Transparency == 0 then
						replicated.Remotes.CommF_:InvokeServer("DressrosaQuestProgress", "Detective")
						EquipWeapon("Key")

						while true do
							wait()
							_tp(CFrame.new(1347.7124, 37.3751602, -1325.6488))

							if not _G.TravelDres then
								break
							elseif Root.Position == CFrame.new(1347.7124, 37.3751602, -1325.6488).Position then
								break
							end
						end
					else
						if workspace.Map.Ice.Door.CanCollide ~= false or workspace.Map.Ice.Door.Transparency ~= 1 then
							replicated.Remotes.CommF_:InvokeServer("TravelDressrosa")

							return
						end

						if Enemies:FindFirstChild("Ice Admiral") then
							for _, child in pairs(Enemies:GetChildren()) do
								if child.Name == "Ice Admiral" then
									if Attack.Alive(child) then
										while true do
											task.wait()
											Attack.Kill(child, _G.TravelDres)

											if _G.TravelDres == false then
												break
											elseif child.Humanoid.Health <= 0 then
												break
											end
										end

										replicated.Remotes.CommF_:InvokeServer("TravelDressrosa")
									end
								end
							end
						else
							_tp(CFrame.new(1347.7124, 37.3751602, -1325.6488))
						end
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.AutoZou and plr.Data.Level.Value >= 1500 then
				if replicated.Remotes.CommF_:InvokeServer("BartiloQuestProgress", "Bartilo") ~= 3 then
					if replicated.Remotes.CommF_:InvokeServer("BartiloQuestProgress", "Bartilo") ~= 0 then
						if replicated.Remotes.CommF_:InvokeServer("BartiloQuestProgress", "Bartilo") == 1 then
							local Jeremy = GetConnectionEnemies("Jeremy")

							if Jeremy then
								while true do
									wait()
									Attack.Kill(Jeremy, _G.AutoZou)

									if not Jeremy.Parent then
										break
									elseif Jeremy.Humanoid.Health <= 0 or _G.AutoZou == false then
										break
									end
								end
							else
								_tp(CFrame.new(2099.88159, 448.931, 648.997375))
							end
						elseif replicated.Remotes.CommF_:InvokeServer("BartiloQuestProgress", "Bartilo") == 2 then
							while true do
								wait()
								_tp(CFrame.new(-1836, 11, 1714))

								if not _G.AutoZou then
									break
								elseif Root.Position == CFrame.new(-1836, 11, 1714).Position then
									break
								end
							end

							if Root.CFrame == CFrame.new(-1836, 11, 1714) then
								notween(CFrame.new(-1836, 11, 1714))
							end

							notween(CFrame.new(-1850.49329, 13.1789551, 1750.89685))
							wait(0.1)
							notween(CFrame.new(-1858.87305, 19.3777466, 1712.01807))
							wait(0.1)
							notween(CFrame.new(-1803.94324, 16.5789185, 1750.89685))
							wait(0.1)
							notween(CFrame.new(-1858.55835, 16.8604317, 1724.79541))
							wait(0.1)
							notween(CFrame.new(-1869.54224, 15.987854, 1681.00659))
							wait(0.1)
							notween(CFrame.new(-1800.0979, 16.4978027, 1684.52368))
							wait(0.1)
							notween(CFrame.new(-1819.26343, 14.795166, 1717.90625))
							wait(0.1)
							notween(CFrame.new(-1813.51843, 14.8604736, 1724.79541))
						end
					elseif string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Swan Pirates") and string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "50") and plr.PlayerGui.Main.Quest.Visible == true then
						local v624 = GetConnectionEnemies("Swan Pirate")

						if v624 then
							pcall(function()
								while true do
									wait()
									Attack.Kill(v624, _G.AutoZou)

									if not v624.Parent then
										break
									elseif v624.Humanoid.Health <= 0 or _G.AutoZou == false or plr.PlayerGui.Main.Quest.Visible == false then
										break
									end
								end
							end)
						else
							_tp(CFrame.new(1057.92761, 137.614319, 1242.08069))
						end
					else
						_tp(CFrame.new(-456.28952, 73.0200958, 299.895966))
					end
				elseif replicated.Remotes.CommF_:InvokeServer("GetUnlockables").FlamingoAccess ~= nil then
					replicated.Remotes.CommF_:InvokeServer("F_", "TravelZou")

					if replicated.Remotes.CommF_:InvokeServer("ZQuestProgress", "Check") == 0 then
						local ripIndra = GetConnectionEnemies("rip_indra")

						if ripIndra then
							while true do
								wait()
								Attack.Kill(ripIndra, _G.AutoZou)

								if not _G.AutoZou then
									break
								elseif not ripIndra.Parent or ripIndra.Humanoid.Health <= 0 then
									break
								end
							end

							Check = 2

							repeat
								wait()
								replicated.Remotes.CommF_:InvokeServer("F_", "TravelZou")
							until Check == 1
						else
							replicated.Remotes.CommF_:InvokeServer("F_", "ZQuestProgress", "Check")
							wait(0.1)
							replicated.Remotes.CommF_:InvokeServer("F_", "ZQuestProgress", "Begin")
						end
					elseif replicated.Remotes.CommF_:InvokeServer("ZQuestProgress", "Check") == 1 then
						replicated.Remotes.CommF_:InvokeServer("F_", "TravelZou")
					else
						local v626 = GetConnectionEnemies("Don Swan")

						if v626 then
							while true do
								wait()
								Attack.Kill(v626, _G.AutoZou)

								if not _G.AutoZou then
									break
								elseif not v626.Parent or v626.Humanoid.Health <= 0 then
									break
								end
							end
						else
							while true do
								wait()
								_tp(CFrame.new(2288.802, 15.1870775, 863.034607))

								if not _G.AutoZou then
									break
								elseif Root.Position == CFrame.new(2288.802, 15.1870775, 863.034607).Position then
									break
								end
							end

							if Root.CFrame == CFrame.new(2288.802, 15.1870775, 863.034607) then
								notween(CFrame.new(2288.802, 15.1870775, 863.034607))
							end
						end
					end
				elseif replicated.Remotes.CommF_:InvokeServer("GetUnlockables").FlamingoAccess == nil then
					TabelDevilFruitStore = {}
					TabelDevilFruitOpen = {}

					for _, v in pairs(replicated.Remotes.CommF_:InvokeServer("getInventoryFruits")) do
						for k, v2 in pairs(v) do
							if k == "Name" then
								table.insert(TabelDevilFruitStore, v2)
							end
						end
					end

					local next_ = next
					local response, v633 = game.ReplicatedStorage:WaitForChild("Remotes").CommF_:InvokeServer("GetFruits")

					for _, v in next_, response, v633 do
						if v.Price >= 1000000 then
							table.insert(TabelDevilFruitOpen, v.Name)
						end
					end

					for _, v in pairs(TabelDevilFruitOpen) do
						for _, v2 in pairs(TabelDevilFruitStore) do
							if v == v2 then
								if replicated.Remotes.CommF_:InvokeServer("GetUnlockables").FlamingoAccess == nil then
									if plr.Backpack:FindFirstChild(v2) then
										replicated.Remotes.CommF_:InvokeServer("F_", "TalkTrevor", "1")
										replicated.Remotes.CommF_:InvokeServer("F_", "TalkTrevor", "2")
										replicated.Remotes.CommF_:InvokeServer("F_", "TalkTrevor", "3")
									else
										replicated.Remotes.CommF_:InvokeServer("F_", "LoadFruit", v2)
									end
								end
							end
						end
					end

					replicated.Remotes.CommF_:InvokeServer("F_", "TalkTrevor", "1")
					replicated.Remotes.CommF_:InvokeServer("F_", "TalkTrevor", "2")
					replicated.Remotes.CommF_:InvokeServer("F_", "TalkTrevor", "3")
				end
			end
		end)
	end
end)
spawn(function()
	if wait(Sec) then
		repeat
			pcall(function()
				if _G.Auto_Tushita then
					if not workspace.Map.Turtle:FindFirstChild("TushitaGate") then
						local Longma = GetConnectionEnemies("Longma")

						if Longma then
							while true do
								task.wait()
								Attack.Kill(Longma, _G.Auto_Tushita)

								if Longma.Humanoid.Health <= 0 then
									break
								elseif not _G.Auto_Tushita or not Longma.Parent then
									break
								end
							end
						elseif replicated:FindFirstChild("Longma") then
							_tp(replicated:FindFirstChild("Longma").HumanoidRootPart.CFrame * CFrame.new(0, 40, 0))
						end
					elseif GetBP("Holy Torch") then
						EquipWeapon("Holy Torch")
						task.wait(1)

						while true do
							task.wait()
							_tp(CFrame.new(-10752, 417, -9366))

							if not _G.Auto_Tushita then
								break
							elseif (CFrame.new(-10752, 417, -9366).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
								break
							end
						end

						wait(0.7)

						while true do
							task.wait()
							_tp(CFrame.new(-11672, 334, -9474))

							if not _G.Auto_Tushita then
								break
							elseif (CFrame.new(-11672, 334, -9474).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
								break
							end
						end

						wait(0.7)

						while true do
							task.wait()
							_tp(CFrame.new(-12132, 521, -10655))

							if not _G.Auto_Tushita then
								break
							elseif (CFrame.new(-12132, 521, -10655).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
								break
							end
						end

						wait(0.7)

						while true do
							task.wait()
							_tp(CFrame.new(-13336, 486, -6985))

							if not _G.Auto_Tushita then
								break
							elseif (CFrame.new(-13336, 486, -6985).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
								break
							end
						end

						wait(0.7)

						while true do
							task.wait()
							_tp(CFrame.new(-13489, 332, -7925))

							if not _G.Auto_Tushita then
								break
							elseif (CFrame.new(-13489, 332, -7925).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
								break
							end
						end
					else
						_tp(CFrame.new(5148.03613, 162.352493, 910.548218))
						wait(0.7)
					end
				end
			end)
		until not wait(Sec)
	end
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.Auto_Yama then
					if replicated.Remotes.CommF_:InvokeServer("EliteHunter", "Progress") < 30 then
						_G.FarmEliteHunt = true
					elseif replicated.Remotes.CommF_:InvokeServer("EliteHunter", "Progress") > 30 then
						_G.FarmEliteHunt = false

						if (workspace.Map.Waterfall.SealedKatana.Handle.Position - plr.Character.HumanoidRootPart.Position).Magnitude >= 20 then
							_tp(workspace.Map.Waterfall.SealedKatana.Handle.CFrame)

							local Ghost = GetConnectionEnemies("Ghost")

							if Ghost then
								while true do
									wait()
									Attack.Kill(Ghost, _G.Auto_Yama)

									if Ghost.Humanoid.Health <= 0 then
										break
									elseif not Ghost.Parent or not _G.Auto_Yama then
										break
									end
								end

								fireclickdetector(workspace.Map.Waterfall.SealedKatana.Handle.ClickDetector)
							end
						end
					end
				end
			end)
		end
	end)
end

do
	task.spawn(function()
		while wait() do
			if _G.Auto_Soul_Guitar then
				pcall(function()
					local v642 = GetConnectionEnemies("Living Zombie")

					if v642 then
						v642.HumanoidRootPart.CFrame = CFrame.new(-10138.3974609375, 138.6524658203125, 5902.89208984375)
						v642.Head.CanCollide = false
						v642.Humanoid.Sit = false
						v642.HumanoidRootPart.CanCollide = false
						v642.Humanoid.JumpPower = 0
						v642.Humanoid.WalkSpeed = 0

						if v642.Humanoid:FindFirstChild("Animator") then
							v642.Humanoid:FindFirstChild("Animator"):Destroy()
						end
					end
				end)
			end
		end
	end)
end

do
	getT = function(p82)
		local Rotation

		if p82 == 1 then
			Rotation = workspace.Map["Haunted Castle"].Tablet.Segment1.Line.Rotation
		elseif p82 == 3 then
			Rotation = workspace.Map["Haunted Castle"].Tablet.Segment3.Line.Rotation
		elseif p82 == 4 then
			Rotation = workspace.Map["Haunted Castle"].Tablet.Segment4.Line.Rotation
		elseif p82 == 7 then
			Rotation = workspace.Map["Haunted Castle"].Tablet.Segment7.Line.Rotation
		elseif p82 == 10 then
			Rotation = workspace.Map["Haunted Castle"].Tablet.Segment10.Line.Rotation
		end

		if Rotation then
			return Rotation.Z
		end
	end
end

getRT = function(p83)
	local Rotation

	for _, child in pairs(workspace.Map["Haunted Castle"].Trophies.Quest:GetChildren()) do
		if p83 == 1 and child.Name == "Trophy1" and child:FindFirstChild("Handle") then
			Rotation = child.Handle.Rotation
		elseif p83 == 2 and child.Name == "Trophy2" and child:FindFirstChild("Handle") then
			Rotation = child.Handle.Rotation
		elseif p83 == 3 and child.Name == "Trophy3" and child:FindFirstChild("Handle") then
			Rotation = child.Handle.Rotation
		elseif p83 == 4 and child.Name == "Trophy4" and child:FindFirstChild("Handle") then
			Rotation = child.Handle.Rotation
		elseif p83 == 5 and child.Name == "Trophy5" and child:FindFirstChild("Handle") then
			Rotation = child.Handle.Rotation
		end

		if Rotation then
			return Rotation.Z
		end
	end
end
GetFirePlacard = function(p84, p85)
	if tostring(workspace.Map["Haunted Castle"]["Placard" .. p84][p85].Indicator.BrickColor) ~= "Pearl" then
		fireclickdetector(workspace.Map["Haunted Castle"]["Placard" .. p84][p85].ClickDetector)
	end
end
spawn(function()
	repeat
		task.wait()
	until _G.Auto_Soul_Guitar

	if wait(Sec) then
		repeat
			pcall(function()
				if _G.Auto_Soul_Guitar and World3 then
					replicated.Remotes.CommF_:InvokeServer("gravestoneEvent", 2)
					replicated.Remotes.CommF_:InvokeServer("gravestoneEvent", 2, true)

					if replicated.Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Check") == nil then
						_tp(CFrame.new(-8655.0166015625, 141.31669616699219, 6160.0224609375))
						replicated.Remotes.CommF_:InvokeServer("gravestoneEvent", 2)
						replicated.Remotes.CommF_:InvokeServer("gravestoneEvent", 2, true)
					elseif replicated.Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Check").Swamp == false then
						Quest1 = true
						Quest2 = false
						Quest3 = false
						Quest4 = false

						local v647 = GetConnectionEnemies("Living Zombie")

						if v647 then
							while true do
								task.wait()
								Attack.Kill(v647, _G.Auto_Soul_Guitar)

								if not _G.Auto_Soul_Guitar then
									break
								elseif v647.Humanoid.Health <= 0 or not v647.Parent or workspace.Map["Haunted Castle"].SwampWater.Color ~= Color3.fromRGB(117, 0, 0) then
									break
								end
							end
						else
							_tp(CFrame.new(-10170.7275390625, 138.6524658203125, 5934.26513671875))
						end
					elseif replicated.Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Check").Gravestones == false then
						Quest1 = false
						Quest2 = true
						Quest3 = false
						Quest4 = false
						GetFirePlacard("7", "Left")
						GetFirePlacard("6", "Left")
						GetFirePlacard("5", "Left")
						GetFirePlacard("4", "Right")
						GetFirePlacard("3", "Left")
						GetFirePlacard("2", "Right")
						GetFirePlacard("1", "Right")
					elseif replicated.Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Check").Ghost == false then
						replicated.Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Ghost")
						replicated.Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Ghost", true)
					elseif replicated.Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Check").Trophies == false then
						Quest1 = false
						Quest2 = false
						Quest3 = true
						Quest4 = false
						_tp(CFrame.new(-9532.8232421875, 6.4716677665710449, 6078.068359375))

						local v648, v649

						repeat
							wait()
							v649 = getRT(1)
							v648 = getT(1)

							if v649 and v648 then
								fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment1:FindFirstChild("ClickDetector"))
							end
						until v649 == v648

						local v650, v651

						repeat
							wait()
							v651 = getRT(2)
							v650 = getT(3)

							if v651 and v650 then
								fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment3:FindFirstChild("ClickDetector"))
							end
						until v651 == v650

						local v652, v653

						repeat
							wait()
							v653 = getRT(3)
							v652 = getT(4)

							if v653 and v652 then
								fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment4:FindFirstChild("ClickDetector"))
							end
						until v653 == v652

						local v654, v655

						repeat
							wait()
							v655 = getRT(4)
							v654 = getT(7)

							if v655 and v654 then
								fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment7:FindFirstChild("ClickDetector"))
							end
						until v655 == v654

						local v656, v657

						repeat
							wait()
							v657 = getRT(5)
							v656 = getT(10)

							if v657 and v656 then
								fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment10:FindFirstChild("ClickDetector"))
							end
						until v657 == v656

						while true do
							wait()
							fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment2:FindFirstChild("ClickDetector"))
							fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment5:FindFirstChild("ClickDetector"))
							fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment6:FindFirstChild("ClickDetector"))
							fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment8:FindFirstChild("ClickDetector"))
							fireclickdetector(workspace.Map["Haunted Castle"].Tablet.Segment9:FindFirstChild("ClickDetector"))

							if workspace.Map["Haunted Castle"].Tablet.Segment2.Line.Rotation.Z == 0 then
								break
							elseif workspace.Map["Haunted Castle"].Tablet.Segment5.Line.Rotation.Z == 0 or workspace.Map["Haunted Castle"].Tablet.Segment6.Line.Rotation.Z == 0 or workspace.Map["Haunted Castle"].Tablet.Segment8.Line.Rotation.Z == 0 or workspace.Map["Haunted Castle"].Tablet.Segment9.Line.Rotation.Z == 0 then
								break
							end
						end
					elseif replicated.Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Check").Pipes == false then
						Quest1 = false
						Quest2 = false
						Quest3 = false
						Quest4 = true
						_tp(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part3.CFrame)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part3.ClickDetector)
						_tp(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part4.CFrame)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part4.ClickDetector)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part4.ClickDetector)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part4.ClickDetector)
						_tp(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part6.CFrame)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part6.ClickDetector)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part6.ClickDetector)
						_tp(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part8.CFrame)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part8.ClickDetector)
						_tp(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part10.CFrame)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part10.ClickDetector)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part10.ClickDetector)
						fireclickdetector(workspace.Map["Haunted Castle"]["Lab Puzzle"].ColorFloor.Model.Part10.ClickDetector)
					end
				end
			end)
		until not wait(Sec)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.AutoMatSoul and GetWP("Skull Guitar") == false then
				if GetM("Bones") >= 500 and GetM("Ectoplasm") >= 250 and GetM("Dark Fragment") >= 1 then
					replicated.Remotes.CommF_:InvokeServer("soulGuitarBuy", true)

					return
				end

				if GetM("Ectoplasm") <= 250 then
					if not _G.AutoMatSoul or not World2 then
						replicated.Remotes.CommF_:InvokeServer("TravelDressrosa")

						return
					end

					local v658 = GetConnectionEnemies({
						"Ship Deckhand",
						"Ship Engineer",
						"Ship Steward",
						"Ship Officer",
						"Arctic Warrior"
					})

					if v658 then
						while true do
							task.wait()
							Attack.Kill(v658, _G.AutoMatSoul)

							if not _G.AutoMatSoul then
								break
							elseif not v658.Parent or v658.Humanoid.Health <= 0 then
								break
							end
						end
					else
						replicated.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(923.21252441406, 126.9760055542, 32852.83203125))
					end
				elseif GetM("Dark Fragment") < 1 then
					if not _G.AutoMatSoul or not World2 then
						replicated.Remotes.CommF_:InvokeServer("TravelDressrosa")

						if not GetConnectionEnemies("Darkbeard") then
							Hop()
						end

						return
					end

					local Darkbeard = GetConnectionEnemies("Darkbeard")

					if Darkbeard then
						repeat
							task.wait()
							Attack.Kill(Darkbeard, _G.AutoMatSoul)
						until not _G.AutoMatSoul or Darkbeard.Humanoid.Health <= 0 or not Darkbeard.Parent

						if not GetConnectionEnemies("Darkbeard") then
							Hop()
						end

						return
					else
						_tp(CFrame.new(3798.4575195313, 13.826690673828, -3399.806640625))

						if not GetConnectionEnemies("Darkbeard") then
							Hop()
						end
					end
				else
					if not (GetM("Bones") <= 500) then
						return
					end

					if not _G.AutoMatSoul or not World3 then
						replicated.Remotes.CommF_:InvokeServer("TravelZou")

						return
					end

					local v660 = GetConnectionEnemies({
						"Reborn Skeleton",
						"Living Zombie",
						"Demonic Soul",
						"Posessed Mummy"
					})

					if v660 then
						while true do
							task.wait()
							Attack.Kill(v660, _G.AutoMatSoul)

							if not _G.AutoMatSoul then
								break
							elseif v660.Humanoid.Health <= 0 or not v660.Parent or v660.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(-9504.8564453125, 172.14292907714844, 6057.259765625))
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.CDK then
				if tick() - (getgenv().LastCDKBossKick or 0) > 3 then
					getgenv().LastCDKBossKick = tick()
					replicated.Remotes.CommF_:InvokeServer("CDKQuest", "Progress", "Good")
					replicated.Remotes.CommF_:InvokeServer("CDKQuest", "Progress", "Evil")
					replicated.Remotes.CommF_:InvokeServer("CDKQuest", "StartTrial", "Boss")
				end

				local v661 = GetConnectionEnemies("Cursed Skeleton Boss")

				if v661 then
					repeat
						wait()

						if plr.Character:FindFirstChild("Yama") then
							EquipWeapon("Yama")
							_tp(v661.HumanoidRootPart.CFrame * CFrame.new(0, 20, 0))

							if not _G.CDK or not v661.Parent or v661.Humanoid.Health <= 0 then
								break
							end
						end

						if plr.Backpack:FindFirstChild("Yama") then
							EquipWeapon("Yama")
						elseif plr.Character:FindFirstChild("Tushita") then
							EquipWeapon("Tushita")
							_tp(v661.HumanoidRootPart.CFrame * CFrame.new(0, 20, 0))

							if not _G.CDK or not v661.Parent or v661.Humanoid.Health <= 0 then
								break
							end
						elseif plr.Backpack:FindFirstChild("Tushita") then
							EquipWeapon("Tushita")
						end

						_tp(v661.HumanoidRootPart.CFrame * CFrame.new(0, 20, 0))
					until not _G.CDK or not v661.Parent or v661.Humanoid.Health <= 0
				else
					_tp(CFrame.new(-12318.193359375, 601.95184326171875, -6538.662109375))
					wait(0.5)
					_tp(workspace.Map.Turtle.Cursed.BossDoor.CFrame)
				end
			end
		end)
	end
end)
spawn(function()
	while wait() do
		pcall(function()
			if _G.CDK_YM and CDKEnsureDoor() then
				if CDKProgress().Finished == nil then
					replicated.Remotes.CommF_:InvokeServer("CDKQuest", "StartTrial", "Evil")
					replicated.Remotes.CommF_:InvokeServer("CDKQuest", "StartTrial", "Evil")
				elseif CDKProgress().Finished == false then
					if tonumber(CDKProgress().Evil) == -3 then
						QuestYama_1 = true
						QuestYama_2 = false
						QuestYama_3 = false

						repeat
							task.wait()

							if not workspace.Enemies:FindFirstChild("Forest Pirate") then
								_tp(CFrame.new(-13223.521484375, 428.19381713867188, -7766.06787109375))
							elseif GetConnectionEnemies("Forest Pirate") then
								_tp(workspace.Enemies:FindFirstChild("Forest Pirate").HumanoidRootPart.CFrame)
							end
						until tonumber(CDKProgress().Evil) == 1 or not _G.CDK_YM
					elseif tonumber(CDKProgress().Evil) == -4 then
						QuestYama_1 = false
						QuestYama_2 = true
						QuestYama_3 = false

						for _, child in pairs(game:GetService("Players").LocalPlayer.QuestHaze:GetChildren()) do
							for k, v in pairs(PosMsList) do
								if string.find(k, child.Name) and child.Value > 0 then
									if (v.Position - Root.Position).Magnitude <= 1000 then
										if workspace.Enemies:FindFirstChild(k) then
											for _, child2 in pairs(workspace.Enemies:GetChildren()) do
												if child2:FindFirstChild("HumanoidRootPart") and child2:FindFirstChild("Humanoid") and child2:FindFirstChild("Humanoid").Health > 0 and child2:FindFirstChild("HazeESP") then
													while true do
														wait()
														Attack.Kill(child2, _G.CDK_YM)

														if not _G.CDK_YM then
															break
														elseif tonumber(CDKProgress().Evil) == 2 or not child2:FindFirstChild("HazeESP") or child2.Humanoid.Health <= 0 then
															break
														end
													end
												end
											end

											continue
										end
									end

									_tp(v)
								end
							end
						end
					elseif tonumber(CDKProgress().Evil) == -5 then
						QuestYama_1 = false
						QuestYama_2 = false
						QuestYama_3 = true

						if workspace.Map:FindFirstChild("HellDimension") and (Root.Position - workspace.Map.HellDimension.Spawn.Position).Magnitude <= 1000 then
							for k in pairs(workspace.Map.HellDimension.Exit:GetChildren()) do
								if tonumber(k) == 2 then
									while true do
										task.wait()
										Root.CFrame = workspace.Map.HellDimension.Exit.CFrame

										if not _G.CDK_YM then
											break
										elseif tonumber(CDKProgress().Evil) == 3 then
											break
										end
									end
								end
							end

							EquipWeapon(_G.SelectWeapon)

							if tonumber(CDKProgress().Evil) ~= 3 then
								repeat
									task.wait()

									repeat
										task.wait()
										_tp(workspace.Map.HellDimension.Torch1.Particles.CFrame)

										for _, descendant in pairs(workspace.Map.HellDimension:GetDescendants()) do
											if descendant:IsA("ProximityPrompt") then
												fireproximityprompt(descendant)
											end
										end
									until (workspace.Map.HellDimension.Torch1.Particles.Position - Root.Position).Magnitude < 5

									wait(2)
									_G.T1Yama = true
								until not _G.CDK_YM or _G.T1Yama or tonumber(CDKProgress().Evil) == 3

								repeat
									task.wait()

									repeat
										task.wait()
										_tp(workspace.Map.HellDimension.Torch2.Particles.CFrame)

										for _, descendant in pairs(workspace.Map.HellDimension:GetDescendants()) do
											if descendant:IsA("ProximityPrompt") then
												fireproximityprompt(descendant)
											end
										end
									until (workspace.Map.HellDimension.Torch2.Particles.Position - Root.Position).Magnitude < 5

									wait(2)
									_G.T2Yama = true
								until _G.T2Yama or _G.CDK_YM == false or tonumber(CDKProgress().Evil) == 3

								repeat
									wait()

									repeat
										task.wait()
										_tp(workspace.Map.HellDimension.Torch3.Particles.CFrame)

										for _, descendant in pairs(workspace.Map.HellDimension:GetDescendants()) do
											if descendant:IsA("ProximityPrompt") then
												fireproximityprompt(descendant)
											end
										end
									until (workspace.Map.HellDimension.Torch3.Particles.Position - Root.Position).Magnitude < 5

									wait(2)
									_G.T3Yama = true
								until _G.T3Yama or _G.CDK_YM == false or tonumber(CDKProgress().Evil) == 3
							end

							for _, child in pairs(workspace.Enemies:GetChildren()) do
								if (child:FindFirstChild("HumanoidRootPart").Position - workspace.Map.HellDimension.Spawn.Position).Magnitude <= 300 and child:FindFirstChild("HumanoidRootPart") and child:FindFirstChild("Humanoid") and child:FindFirstChild("Humanoid").Health > 0 then
									while true do
										task.wait()
										Attack.Kill(child, _G.CDK_YM)

										if not _G.CDK_YM then
											break
										elseif child.Humanoid.Health <= 0 or not child.Parent or tonumber(CDKProgress().Evil) == 3 then
											break
										end
									end
								end
							end
						end
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait() do
		pcall(function()
			if _G.CDK_YM and tonumber(CDKProgress().Evil) == -5 then
				if workspace.Map:FindFirstChild("HellDimension") and not ((Root.Position - workspace.Map.HellDimension.Spawn.Position).Magnitude > 1000) then
					return
				end

				local v677 = GetConnectionEnemies("Soul Reaper")

				if v677 then
					while true do
						task.wait()
						_tp(v677.HumanoidRootPart.CFrame)

						if not (v677.Humanoid.Health <= 0) and _G.CDK_YM and v677.Parent and tonumber(CDKProgress().Evil) ~= 3 then
							if workspace.Map:FindFirstChild("HellDimension") and (Root.Position - workspace.Map.HellDimension.Spawn.Position).Magnitude <= 1000 then
								break
							end
						else
							break
						end
					end

					return
				end

				local ok5 = plr.Backpack:FindFirstChild("Hallow Essence")

				if not ok5 then
					ok5 = plr.Character:FindFirstChild("Hallow Essence")
				end

				if ok5 then
					repeat
						_tp(CFrame.new(-8932.322265625, 146.83154296875, 6062.55078125))
						task.wait()
					until (CFrame.new(-8932.322265625, 146.83154296875, 6062.55078125).Position - Root.Position).Magnitude <= 8

					EquipWeapon("Hallow Essence")
				else
					local ok4 = not replicated:FindFirstChild("Soul Reaper")

					if not ok4 then
						ok4 = not (replicated:FindFirstChild("Soul Reaper").Humanoid.Health > 0)
					end

					if not ok4 then
						_tp(replicated:FindFirstChild("Soul Reaper").HumanoidRootPart.CFrame)

						return
					end

					if not (replicated.Remotes.CommF_:InvokeServer("Bones", "Check") < 50) then
						replicated.Remotes.CommF_:InvokeServer("Bones", "Buy", 1, 1)

						return
					end

					if workspace.Enemies:FindFirstChild("Soul Reaper") then
						replicated.Remotes.CommF_:InvokeServer("Bones", "Buy", 1, 1)

						return
					end

					if replicated:FindFirstChild("Soul Reaper") then
						replicated.Remotes.CommF_:InvokeServer("Bones", "Buy", 1, 1)

						return
					end

					if workspace.Map:FindFirstChild("HellDimension") then
						replicated.Remotes.CommF_:InvokeServer("Bones", "Buy", 1, 1)

						return
					end

					local ok = workspace.Enemies:FindFirstChild("Reborn Skeleton")

					if not ok then
						ok = workspace.Enemies:FindFirstChild("Living Zombie")
					end

					local ok2 = ok

					if not ok2 then
						ok2 = workspace.Enemies:FindFirstChild("Demonic Soul")
					end

					local ok3 = ok2

					if not ok3 then
						ok3 = workspace.Enemies:FindFirstChild("Posessed Mummy")
					end

					if ok3 then
						for _, child in pairs(workspace.Enemies:GetChildren()) do
							if child.Name == "Reborn Skeleton" or child.Name == "Living Zombie" or child.Name == "Demonic Soul" or child.Name == "Posessed Mummy" then
								if child:FindFirstChild("HumanoidRootPart") and child:FindFirstChild("Humanoid") and child:FindFirstChild("Humanoid").Health > 0 then
									while true do
										task.wait()
										Attack.Kill(child, _G.CDK_YM)

										if not _G.CDK_YM then
											break
										elseif child.Humanoid.Health <= 0 or not child.Parent then
											break
										end
									end
								end
							end
						end
					else
						_tp(CFrame.new(-9515.2255859375, 164.0062255859375, 5785.38330078125))
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait() do
		pcall(function()
			if _G.CDK_TS and CDKEnsureDoor() then
				if CDKProgress().Finished == nil then
					replicated.Remotes.CommF_:InvokeServer("CDKQuest", "StartTrial", "Good")
				elseif CDKProgress().Finished == false then
					if tonumber(CDKProgress().Good) == -3 then
						QuestTushita_1 = true
						QuestTushita_2 = false
						QuestTushita_3 = false

						while true do
							wait()
							_tp(CFrame.new(-4602.5107421875, 16.446542739868164, -2880.998046875))

							if (CFrame.new(-4602.5107421875, 16.446542739868164, -2880.998046875).Position - game:GetService("Players").LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 3 then
								break
							elseif not _G.CDK_TS or tonumber(CDKProgress().Good) == 1 then
								break
							end
						end

						if (CFrame.new(-4602.5107421875, 16.446542739868164, -2880.998046875).Position - game:GetService("Players").LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 10 then
							wait(0.7)
							replicated.Remotes.CommF_:InvokeServer("CDKQuest", "BoatQuest", workspace.NPCs:FindFirstChild("Luxury Boat Dealer"), "Check")
							wait(0.5)
							replicated.Remotes.CommF_:InvokeServer("CDKQuest", "BoatQuest", workspace.NPCs:FindFirstChild("Luxury Boat Dealer"))
						end

						wait(1)

						while true do
							wait()
							_tp(CFrame.new(4001.185302734375, 10.089399337768555, -2654.86328125))

							if (CFrame.new(4001.185302734375, 10.089399337768555, -2654.86328125).Position - game:GetService("Players").LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 3 then
								break
							elseif not _G.CDK_TS or tonumber(CDKProgress().Good) == 1 then
								break
							end
						end

						if (CFrame.new(4001.185302734375, 10.089399337768555, -2654.86328125).Position - game:GetService("Players").LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 10 then
							wait(0.7)
							replicated.Remotes.CommF_:InvokeServer("CDKQuest", "BoatQuest", workspace.NPCs:FindFirstChild("Luxury Boat Dealer"), "Check")
							wait(0.5)
							replicated.Remotes.CommF_:InvokeServer("CDKQuest", "BoatQuest", workspace.NPCs:FindFirstChild("Luxury Boat Dealer"))
						end

						wait(1)

						while true do
							wait()
							_tp(CFrame.new(-9530.763671875, 7.245208740234375, -8375.5087890625))

							if (CFrame.new(-9530.763671875, 7.245208740234375, -8375.5087890625).Position - game:GetService("Players").LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 3 then
								break
							elseif not _G.CDK_TS or tonumber(CDKProgress().Good) == 1 then
								break
							end
						end

						if (CFrame.new(-9530.763671875, 7.245208740234375, -8375.5087890625).Position - game:GetService("Players").LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 10 then
							wait(0.7)
							replicated.Remotes.CommF_:InvokeServer("CDKQuest", "BoatQuest", workspace.NPCs:FindFirstChild("Luxury Boat Dealer"), "Check")
							wait(0.5)
							replicated.Remotes.CommF_:InvokeServer("CDKQuest", "BoatQuest", workspace.NPCs:FindFirstChild("Luxury Boat Dealer"))
						end

						wait(1)
					elseif tonumber(CDKProgress().Good) == -4 then
						QuestTushita_1 = false
						QuestTushita_2 = true
						QuestTushita_3 = false

						while true do
							wait()
							_G.AutoRaidCastle = true

							if not _G.CDK_TS then
								break
							elseif tonumber(CDKProgress().Good) == 2 then
								break
							end
						end

						_G.AutoRaidCastle = false
					elseif tonumber(CDKProgress().Good) == -5 then
						QuestTushita_1 = false
						QuestTushita_2 = false
						QuestTushita_3 = true

						if workspace.Enemies:FindFirstChild("Cake Queen") then
							for _, child in pairs(workspace.Enemies:GetChildren()) do
								if child.Name == "Cake Queen" and child:FindFirstChild("Humanoid") and child:FindFirstChild("HumanoidRootPart") and child.Humanoid.Health > 0 then
									while true do
										wait()
										Attack.Kill(child, _G.CDK_TS)

										if not _G.CDK_TS then
											break
										elseif not child.Parent or child.Humanoid.Health <= 0 or tonumber(CDKProgress().Good) == 3 then
											break
										end
									end
								end
							end
						else
							local ok = not replicated:FindFirstChild("Cake Queen")

							if not ok then
								ok = not (replicated:FindFirstChild("Cake Queen").Humanoid.Health > 0)
							end

							if ok then
								if (game.Players.LocalPlayer.Character.HumanoidRootPart.Position - workspace.Map.HeavenlyDimension.Spawn.Position).Magnitude <= 1000 then
									for k in pairs(workspace.Map.HeavenlyDimension.Exit:GetChildren()) do
										Ex = k
									end

									if Ex == 2 then
										while true do
											wait()
											game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame = workspace.Map.HeavenlyDimension.Exit.CFrame

											if not _G.CDK_TS then
												break
											elseif tonumber(CDKProgress().Good) == 3 then
												break
											end
										end
									end

									repeat
										wait()

										repeat
											wait()
											_tp(CFrame.new(-22529.6171875, 5275.77392578125, 3873.5712890625))

											for _, descendant in pairs(workspace.Map.HeavenlyDimension:GetDescendants()) do
												if descendant:IsA("ProximityPrompt") then
													fireproximityprompt(descendant)
												end
											end
										until (CFrame.new(-22529.6171875, 5275.77392578125, 3873.5712890625).Position - game.Players.LocalPlayer.Character.HumanoidRootPart.Position).Magnitude < 5

										wait(2)
										_G.DoneT1 = true
									until not _G.CDK_TS or _G.DoneT1

									repeat
										wait()

										repeat
											wait()
											_tp(CFrame.new(-22637.291015625, 5281.365234375, 3749.28857421875))

											for _, descendant in pairs(workspace.Map.HeavenlyDimension:GetDescendants()) do
												if descendant:IsA("ProximityPrompt") then
													fireproximityprompt(descendant)
												end
											end
										until (CFrame.new(-22637.291015625, 5281.365234375, 3749.28857421875).Position - game.Players.LocalPlayer.Character.HumanoidRootPart.Position).Magnitude < 5

										wait(2)
										_G.DoneT2 = true
									until _G.DoneT2 or _G.CDK_TS == false

									repeat
										wait()

										repeat
											task.wait()
											_tp(CFrame.new(-22791.14453125, 5277.16552734375, 3764.570068359375))

											for _, descendant in pairs(workspace.Map.HeavenlyDimension:GetDescendants()) do
												if descendant:IsA("ProximityPrompt") then
													fireproximityprompt(descendant)
												end
											end
										until (CFrame.new(-22791.14453125, 5277.16552734375, 3764.570068359375).Position - game.Players.LocalPlayer.Character.HumanoidRootPart.Position).Magnitude < 5

										wait(2)
										_G.DoneT3 = true
									until _G.DoneT3 or _G.CDK_TS == false

									for _, child in pairs(workspace.Enemies:GetChildren()) do
										if (child:FindFirstChild("HumanoidRootPart").Position - CFrame.new(-22695.7012, 5270.93652, 3814.42847, 0.11794927, 3.32185834e-08, 0.99301964, -8.73070718e-08, 1, -2.30819008e-08, -0.99301964, -8.3975138e-08, 0.11794927).Position).Magnitude <= 300 and child:FindFirstChild("HumanoidRootPart") and child:FindFirstChild("Humanoid") and child:FindFirstChild("Humanoid").Health > 0 then
											while true do
												wait()
												Attack.Kill(child, _G.CDK_TS)

												if not _G.CDK_TS then
													break
												elseif child.Humanoid.Health <= 0 or not child.Parent then
													break
												end
											end
										end
									end
								end
							else
								_tp(replicated:FindFirstChild("Cake Queen").HumanoidRootPart.CFrame * CFrame.new(0, 30, 0))
							end
						end
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.Tp_LgS then
			pcall(function()
				local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

				if not HumanoidRootPart then
					return
				end

				local v698
				local v699

				for _, v in ipairs({
					workspace:FindFirstChild("NPCs"),
					replicated:FindFirstChild("NPCs")
				}) do
					if v then
						for _, child in ipairs(v:GetChildren()) do
							if string.find(child.Name, "Legendary Sword Dealer", 1, true) then
								local ok, result = pcall(function()
									return child:GetPivot()
								end)

								if ok then
									local Magnitude = (result.Position - HumanoidRootPart.Position).Magnitude

									if not v699 or Magnitude < v699 then
										v698 = result
										v699 = Magnitude
									end
								end
							end
						end
					end
				end

				if v698 then
					_tp(v698)
				end
			end)
		end
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.AutoPole then
			pcall(function()
				local v707 = GetConnectionEnemies("Thunder God")

				if v707 then
					while true do
						task.wait()
						Attack.Kill(v707, _G.AutoPole)

						if not _G.AutoPole then
							break
						elseif not v707.Parent or v707.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(-7994.984375, 5761.025390625, -2088.6479492188))
				end
			end)
		end
	end
end)
spawn(function()
	if wait(Sec) then
		repeat
			pcall(function()
				if _G.AutoPoleV2 then
					if not GetBP("Pole (1st Form)") then
						replicated.Remotes.CommF_:InvokeServer("LoadItem", "Pole (1st Form)")
					end

					if not GetBP("Pole (2nd Form)") then
						replicated.Remotes.CommF_:InvokeServer("LoadItem", "Pole (2nd Form)")
					end

					if GetBP("Pole (1st Form)") and GetBP("Pole (1st Form)").Level.Value <= 179 then
						_G.Level = true
					elseif GetBP("Pole (1st Form)") and GetBP("Pole (1st Form)").Level.Value >= 180 then
						_G.Level = false
					end

					if not GetBP("Rumble Fruit") then
						return
					end

					local ok2 = not GetBP("Rumble Fruit").AwakenedMoves:FindFirstChild("Z")

					if not ok2 then
						ok2 = not GetBP("Rumble Fruit").AwakenedMoves:FindFirstChild("X")
					end

					local ok3 = ok2

					if not ok3 then
						ok3 = not GetBP("Rumble Fruit").AwakenedMoves:FindFirstChild("C")
					end

					local ok4 = ok3

					if not ok4 then
						ok4 = not GetBP("Rumble Fruit").AwakenedMoves:FindFirstChild("V")
					end

					local ok5 = ok4

					if not ok5 then
						ok5 = not GetBP("Rumble Fruit").AwakenedMoves:FindFirstChild("F")
					end

					if ok5 then
						local ok = replicated.Remotes.CommF_:InvokeServer("Awakener", "Check") == nil

						if not ok then
							ok = replicated.Remotes.CommF_:InvokeServer("Awakener", "Check") == 0
						end

						if ok then
							_G.SelectChip = "Rumble"

							local response = replicated.Remotes.CommF_:InvokeServer("RaidsNpc", "Select", _G.SelectChip)

							if response then
								response:Stop()
							end

							_G.Raiding = true
							_G.Auto_Awakener = true
						end
					else
						_G.SelectChip = nil
						_G.Raiding = false
						_G.Auto_Awakener = false

						if plr.Data.Fragments.Value >= 5000 then
							replicated.Remotes.CommF_:InvokeServer("Thunder God", "Talk")
							wait(Sec)
							replicated.Remotes.CommF_:InvokeServer("Thunder God", "Sure")
						end
					end
				end
			end)
		until not wait(Sec)
	end
end)

do
	spawn(function()
		while wait(0.2) do
			pcall(function()
				if _G.AutoSaw then
					local v714 = GetConnectionEnemies("The Saw")

					if v714 then
						while true do
							task.wait()
							Attack.Kill(v714, _G.AutoSaw)

							if _G.AutoSaw == false then
								break
							elseif v714.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(-784.89715576172, 72.427383422852, 1603.5822753906))
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait(0.2) do
		pcall(function()
			if _G.AutoSaber and plr.Data.Level.Value >= 200 then
				if not plr.Backpack:FindFirstChild("Saber") then
					if not plr.Character:FindFirstChild("Saber") then
						if workspace.Map.Jungle.Final.Part.Transparency ~= 0 then
							local ok = workspace.Enemies:FindFirstChild("Saber Expert")

							if not ok then
								ok = replicated:FindFirstChild("Saber Expert")
							end

							if ok then
								for _, child in pairs(workspace.Enemies:GetChildren()) do
									if child.Name == "Saber Expert" and Attack.Alive(child) then
										while true do
											task.wait()
											Attack.Kill(child, _G.AutoSaber)

											if child.Humanoid.Health <= 0 then
												break
											elseif _G.AutoSaber == false then
												break
											end
										end

										if child.Humanoid.Health <= 0 then
											replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "PlaceRelic")
										end
									end
								end
							else
								_tp(CFrame.new(-1401.85046, 29.9773273, 8.81916237, 0.85820812, 8.76083845e-08, 0.513301849, -8.55007443e-08, 1, -2.77243419e-08, -0.513301849, -2.00944328e-08, 0.85820812))
							end
						elseif workspace.Map.Jungle.QuestPlates.Door.Transparency ~= 0 then
							if workspace.Map.Desert.Burn.Part.Transparency ~= 0 then
								if replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "SickMan") ~= 0 then
									replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "GetCup")
									wait(0.5)
									EquipWeapon("Cup")
									wait(0.5)
									replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "FillCup", plr.Character.Cup)
									wait(Sec)
									replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "SickMan")
								elseif replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "RichSon") == nil then
									replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "RichSon")
								elseif replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "RichSon") == 0 then
									local ok2 = workspace.Enemies:FindFirstChild("Mob Leader")

									if not ok2 then
										ok2 = replicated:FindFirstChild("Mob Leader")
									end

									if ok2 then
										_tp(CFrame.new(-2967.59521, -4.91089821, 5328.70703, 0.342208564, -0.0227849055, 0.939347804, 0.0251603816, 0.999569714, 0.0150796166, -0.939287126, 0.0184739735, 0.342634559))

										for _, child in pairs(workspace.Enemies:GetChildren()) do
											if child.Name == "Mob Leader" and Attack.Alive(child) then
												while true do
													task.wait()
													Attack.Kill(child, _G.AutoSaber)

													if child.Humanoid.Health <= 0 then
														break
													elseif _G.AutoSaber == false then
														break
													end
												end
											end
										end
									end
								elseif replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "RichSon") == 1 then
									replicated.Remotes.CommF_:InvokeServer("ProQuestProgress", "RichSon")
									EquipWeapon("Relic")
									_tp(CFrame.new(-1404.91504, 29.9773273, 3.80598116, 0.876514494, 5.66906877e-09, 0.481375456, 2.53851997e-08, 1, -5.79995607e-08, -0.481375456, 6.30572643e-08, 0.876514494))
								end
							elseif plr.Backpack:FindFirstChild("Torch") then
								EquipWeapon("Torch")
								firetouchinterest(plr.Character.Torch.Handle, workspace.Map.Desert.Burn.Fire, 0)
								firetouchinterest(plr.Character.Torch.Handle, workspace.Map.Desert.Burn.Fire, 1)
								_tp(CFrame.new(1114.61475, 5.04679728, 4350.22803, -0.648466587, -1.28799094e-09, 0.761243105, -5.70652914e-10, 1, 1.20584542e-09, -0.761243105, 3.47544882e-10, -0.648466587))

								return
							elseif plr.Character:FindFirstChild("Torch") then
								EquipWeapon("Torch")
								firetouchinterest(plr.Character.Torch.Handle, workspace.Map.Desert.Burn.Fire, 0)
								firetouchinterest(plr.Character.Torch.Handle, workspace.Map.Desert.Burn.Fire, 1)
								_tp(CFrame.new(1114.61475, 5.04679728, 4350.22803, -0.648466587, -1.28799094e-09, 0.761243105, -5.70652914e-10, 1, 1.20584542e-09, -0.761243105, 3.47544882e-10, -0.648466587))
							else
								_tp(CFrame.new(-1610.00757, 11.5049858, 164.001587, 0.984807551, -0.167722285, -0.0449818149, 0.17364943, 0.951244235, 0.254912198, 3.42372805e-05, -0.258850515, 0.965917408))
							end
						elseif (CFrame.new(-1612.55884, 36.9774132, 148.719543, 0.37091279, 3.0717151e-09, -0.928667724, 3.97099491e-08, 1, 1.91679348e-08, 0.928667724, -4.39869794e-08, 0.37091279).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 100 then
							_tp(plr.Character.HumanoidRootPart.CFrame)
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Jungle.QuestPlates.Plate1.Button.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Jungle.QuestPlates.Plate2.Button.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Jungle.QuestPlates.Plate3.Button.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Jungle.QuestPlates.Plate4.Button.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Jungle.QuestPlates.Plate5.Button.CFrame
							wait(0.5)
						else
							_tp(CFrame.new(-1612.55884, 36.9774132, 148.719543, 0.37091279, 3.0717151e-09, -0.928667724, 3.97099491e-08, 1, 1.91679348e-08, 0.928667724, -4.39869794e-08, 0.37091279))
						end
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(0.2) do
		if _G.AutoColShad then
			pcall(function()
				local Cyborg = GetConnectionEnemies("Cyborg")

				if Cyborg then
					while true do
						task.wait()
						Attack.Kill(Cyborg, _G.AutoColShad)

						if _G.AutoColShad == false then
							break
						elseif not Cyborg.Parent or Cyborg.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(6094.0249023438, 73.770050048828, 3825.7348632813))
				end
			end)
		end
	end
end)
spawn(function()
	if task.wait(Sec) then
		repeat
			pcall(function()
				if _G.AutoGetUsoap then
					for _, child in pairs(workspace.Characters:GetChildren()) do
						if child.Name ~= plr.Name and child.Humanoid.Health > 0 and child:FindFirstChild("HumanoidRootPart") and child.Parent and (Root.Position - child.HumanoidRootPart.Position).Magnitude <= 230 then
							while true do
								task.wait()
								EquipWeapon(_G.SelectWeapon)
								_tp(child.HumanoidRootPart.CFrame * CFrame.new(1, 1, 2))

								if _G.AutoGetUsoap == false then
									break
								elseif child.Humanoid.Health <= 0 or not child.Parent or not child:FindFirstChild("HumanoidRootPart") or not child:FindFirstChild("Humanoid") then
									break
								end
							end
						end
					end
				end
			end)
		until not task.wait(Sec)
	end
end)

do
	spawn(function()
		while wait(Sec) do
			if _G.Greybeard then
				pcall(function()
					if GetWP("Bisento") then
						if not GetWP("Bisento") then
							return
						end

						replicated.Remotes.CommF_:InvokeServer("LoadItem", "Bisento")

						local Greybeard = GetConnectionEnemies("Greybeard")

						if Greybeard then
							while true do
								wait()
								Attack.Kill(Greybeard, _G.Greybeard)

								if _G.Greybeard == false then
									break
								elseif not Greybeard.Parent or Greybeard.Humanoid.Health <= 0 then
									break
								end
							end

							return
						else
							_tp(CFrame.new(-5023.38330078125, 28.652032852172852, 4332.3818359375))
						end
					else
						replicated.Remotes.CommF_:InvokeServer("BuyItem", "Bisento")
					end
				end)
			end
		end
	end)
end

spawn(function()
	while wait(0.1) do
		if _G.WardenBoss then
			pcall(function()
				local v725 = GetConnectionEnemies("Chief Warden")

				if v725 then
					while true do
						wait()
						Attack.Kill(v725, _G.WardenBoss)

						if _G.WardenBoss == false then
							break
						elseif not v725.Parent or v725.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(5206.92578, 0.997753382, 814.976746, 0.342041343, -0.00062915677, 0.939684749, 0.00191645394, 0.999998152, -2.80422337e-05, -0.939682961, 0.00181045406, 0.342041939))
				end
			end)
		end
	end
end)

do
	spawn(function()
		while wait(0.1) do
			if _G.MarinesCoat then
				pcall(function()
					local v726 = GetConnectionEnemies("Vice Admiral")

					if v726 then
						while true do
							wait()
							Attack.Kill(v726, _G.MarinesCoat)

							if _G.MarinesCoat == false then
								break
							elseif not v726.Parent or v726.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(-5006.5454101563, 88.032081604004, 4353.162109375))
					end
				end)
			end
		end
	end)
end

spawn(function()
	while wait(0.1) do
		if _G.SwanCoat then
			local exitTo

			repeat
				pcall(function()
					local Swan = GetConnectionEnemies("Swan")

					if Swan then
						while true do
							wait()
							Attack.Kill(Swan, _G.SwanCoat)

							if _G.SwanCoat == false then
								break
							elseif not Swan.Parent or Swan.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(5325.09619, 7.03906584, 719.570679, -0.309060812, 0, 0.951042235, 0, 1, 0, -0.951042235, 0, -0.309060812))
					end
				end)
				exitTo = nil

				while wait(0.1) do
					if _G.SwanCoat then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)

do
	spawn(function()
		pcall(function()
			while wait(0.1) do
				if _G.IceBossRen then
					local v729 = GetConnectionEnemies("Awakened Ice Admiral")

					if v729 then
						while true do
							task.wait()
							Attack.Kill(v729, _G.IceBossRen)

							if _G.IceBossRen == false then
								break
							elseif not v729.Parent or v729.Humanoid.Health <= 0 then
								break
							end
						end

						continue
					end

					_tp(CFrame.new(5668.9780273438, 28.519989013672, -6483.3520507813))
				end
			end
		end)
	end)
end

spawn(function()
	while wait(0.1) do
		pcall(function()
			if _G.KeysRen then
				if plr.Backpack:FindFirstChild(RenMon[3]) then
					EquipWeapon(RenMon[3])
					wait(0.1)
					_tp(CFrame.new(6571.1201171875, 299.23028564453, -6967.841796875))

					return
				end

				if plr.Character:FindFirstChild(RenMon[3]) then
					EquipWeapon(RenMon[3])
					wait(0.1)
					_tp(CFrame.new(6571.1201171875, 299.23028564453, -6967.841796875))
				else
					local v730 = GetConnectionEnemies(RenMon)

					if v730 then
						while true do
							task.wait()
							Attack.Kill(v730, _G.KeysRen)

							if plr.Backpack:FindFirstChild(RenMon[3]) then
								break
							elseif _G.KeysRen == false or not v730.Parent or v730.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(5439.716796875, 84.420944213867, -6715.1635742188))
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(0.1) do
		pcall(function()
			if _G.AutoTridentW2 then
				local v731 = GetConnectionEnemies("Tide Keeper")

				if v731 then
					while true do
						task.wait()
						Attack.Kill(v731, _G.AutoTridentW2)

						if _G.AutoTridentW2 == false then
							break
						elseif not v731.Parent or v731.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(-3795.6423339844, 105.88877105713, -11421.307617188))
				end
			end
		end)
	end
end)
spawn(function()
	while wait(0.1) do
		pcall(function()
			if _G.LongsWord then
				local Diamond = GetConnectionEnemies("Diamond")

				if Diamond then
					while true do
						task.wait()
						Attack.Kill(Diamond, _G.LongsWord)

						if _G.LongsWord == false then
							break
						elseif not Diamond.Parent or Diamond.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(-1576.7166748047, 198.59265136719, 13.724286079407))
				end
			end
		end)
	end
end)

do
	spawn(function()
		while wait(0.1) do
			if _G.BlackSpikey then
				pcall(function()
					local Jeremy = GetConnectionEnemies("Jeremy")

					if Jeremy then
						while true do
							wait()
							Attack.Kill(Jeremy, _G.BlackSpikey)

							if _G.BlackSpikey == false then
								break
							elseif not Jeremy.Parent or Jeremy.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(2006.9261474609, 448.95666503906, 853.98284912109))
					end
				end)
			end
		end
	end)
end

spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.DarkBladev3 then
				if not World2 then
					return
				end

				if not GetBP("Dark Blade") then
					replicated.Remotes.CommF_:InvokeServer("LoadItem", "Dark Blade")
				end

				if not GetBP("Fist of Darkness") then
					_G.AutoFarmChest = true

					return
				end

				if workspace.Enemies:FindFirstChild("Darkbeard") then
					if not GetConnectionEnemies("Darkbeard") or not (GetBP("Fist of Darkness") >= 1) then
						return
					end

					while true do
						wait()
						_tp(CFrame.new(-5719.36376953125, 48.505905151367188, -782.9759521484375))

						if not _G.DarkBladev3 then
							break
						elseif Root.Position == CFrame.new(-5719.36376953125, 48.505905151367188, -782.9759521484375).Position then
							break
						end
					end

					fireclickdetector(workspace.Map.GraveIsland.Mountain.Rocks.Button.ClickDetector)

					return
				else
					_tp(CFrame.new(3677.08203125, 62.751937866211, -3144.8332519531))
				end
			end
		end)
	end
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.AutoEcBoss then
					if GetM("Ectoplasm") >= 99 then
						replicated.Remotes.CommF_:InvokeServer("Ectoplasm", "Buy", 3)
					elseif GetM("Ectoplasm") <= 99 then
						local v734 = GetConnectionEnemies("Cursed Captain")

						if v734 then
							while true do
								wait()
								Attack.Kill(v734, _G.AutoEcBoss)

								if not _G.AutoEcBoss then
									break
								elseif not v734.Parent or v734.Humanoid.Health <= 0 then
									break
								end
							end
						else
							replicated.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(923.21252441406, 126.9760055542, 32852.83203125))
							wait(0.5)
							_tp(CFrame.new(916.928589, 181.092773, 33422))
						end
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait(0.1) do
		if _G.Auto_Def_DarkCoat then
			pcall(function()
				local ok = not GetBP("Fist of Darkness")

				if not ok then
					ok = workspace.Enemies:FindFirstChild("Darkbeard")
				end

				if not ok then
					_tp(CFrame.new(3677.08203125, 62.751937866211, -3144.8332519531))
				elseif GetConnectionEnemies("Darkbeard") then
					local Darkbeard = GetConnectionEnemies("Darkbeard")

					if Darkbeard then
						while true do
							wait()
							Attack.Kill(Darkbeard, _G.Auto_Def_DarkCoat)

							if _G.Auto_Def_DarkCoat == false then
								break
							elseif not Darkbeard.Parent or Darkbeard.Humanoid.Health <= 0 then
								break
							end
						end
					end
				elseif not GetBP("Fist of Darkness") and not GetConnectionEnemies("Darkbeard") then
					while true do
						wait(0.1)
						_G.AutoFarmChest = true

						if not _G.Auto_Def_DarkCoat then
							break
						elseif GetBP("Fist of Darkness") or GetConnectionEnemies("Darkbeard") then
							break
						end
					end

					_G.AutoFarmChest = false
				end
			end)
		end
	end
end)

do
	spawn(function()
		while wait(0.1) do
			if _G.Auto_DonAcces then
				local exitTo

				repeat
					pcall(function()
						if replicated.Remotes.CommF_:InvokeServer("GetUnlockables").FlamingoAccess == nil and plr.Data.Level.Value >= 1500 then
							FruitPrice = {}
							FruitStore = {}

							local next_ = next
							local response, v740 = replicated:WaitForChild("Remotes").CommF_:InvokeServer("GetFruits")

							for _, v in next_, response, v740 do
								if v.Price >= 1000000 then
									table.insert(FruitPrice, v.Name)
								end
							end

							for _, v in pairs(replicated.Remotes.CommF_:InvokeServer("getInventoryFruits")) do
								for k, v2 in pairs(v) do
									if k == "Name" then
										table.insert(FruitStore, v2)
									end
								end

								replicated.Remotes.CommF_:InvokeServer("Cousin", "Buy")

								for _, v2 in pairs(FruitPrice) do
									for _, v3 in pairs(FruitStore) do
										if v2 == v3 then
											if replicated.Remotes.CommF_:InvokeServer("GetUnlockables").FlamingoAccess == nil then
												_G.StoreF = false

												if plr.Backpack:FindFirstChild(FruitStore) then
													replicated.Remotes.CommF_:InvokeServer("TalkTrevor", "1")
													replicated.Remotes.CommF_:InvokeServer("TalkTrevor", "2")
													replicated.Remotes.CommF_:InvokeServer("TalkTrevor", "3")
												else
													replicated.Remotes.CommF_:InvokeServer("LoadFruit", tostring(v2))
												end
											end
										end
									end
								end

								if replicated.Remotes.CommF_:InvokeServer("GetUnlockables").FlamingoAccess ~= nil then
									_G.StoreF = true
									_G.Auto_DonAcces = false
								end
							end
						end
					end)
					exitTo = nil

					while wait(0.1) do
						if _G.Auto_DonAcces then
							exitTo = 1

							break
						end
					end
				until exitTo ~= 1

				return
			end
		end
	end)
end

spawn(function()
	while wait(0.2) do
		if _G.Auto_SwanGG then
			pcall(function()
				local v751 = GetConnectionEnemies("Don Swan")

				if v751 then
					while true do
						wait()
						Attack.Kill(v751, _G.Auto_SwanGG)

						if _G.Auto_SwanGG == false then
							break
						elseif not v751.Parent or v751.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(2286.2004394531, 15.177839279175, 863.8388671875))
				end
			end)
		end
	end
end)

do
	spawn(function()
		while wait(Sec) do
			if _G.AutoBigmom then
				pcall(function()
					local v752 = GetConnectionEnemies("Cake Queen")

					if v752 then
						while true do
							task.wait()
							Attack.Kill(v752, _G.AutoBigmom)

							if not _G.AutoBigmom then
								break
							elseif not v752.Parent or v752.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(-709.31329345703125, 381.6005859375, -11011.396484375))
					end
				end)
			end
		end
	end)
end

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.Auto_Cavender then
					local v753 = GetConnectionEnemies("Beautiful Pirate")

					if v753 then
						while true do
							wait()
							Attack.Kill(v753, _G.Auto_Cavender)

							if not _G.Auto_Cavender then
								break
							elseif v753.Humanoid.Health <= 0 then
								break
							end
						end
					else
						_tp(CFrame.new(5283.609375, 22.56223487854, -110.78285217285))
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.TwinHook then
				local v754 = GetConnectionEnemies("Captain Elephant")

				if v754 then
					while true do
						wait()
						Attack.Kill(v754, _G.TwinHook)

						if not _G.TwinHook then
							break
						elseif v754.Humanoid.Health <= 0 then
							break
						end
					end
				else
					replicated.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(-12471.169921875, 374.94024658203, -7551.677734375))
					wait(0.2)
					_tp(CFrame.new(-13376.7578125, 433.28689575195, -8071.392578125))
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.AutoSerpentBow then
			local v755 = GetConnectionEnemies("Hydra Leader")

			if v755 then
				while true do
					wait()
					Attack.Kill(v755, _G.AutoSerpentBow)

					if not _G.AutoSerpentBow then
						break
					elseif not v755.Parent or v755.Humanoid.Health <= 0 then
						break
					end
				end
			else
				_tp(CFrame.new(5821.89794921875, 1019.0950927734375, -73.719230651855469))
			end
		end
	end
end)
spawn(function()
	while wait(0.2) do
		if _G.AutoKilo then
			pcall(function()
				local v756 = GetConnectionEnemies("Kilo Admiral")

				if v756 then
					while true do
						task.wait()
						Attack.Kill(v756, _G.AutoKilo)

						if not _G.AutoKilo then
							break
						elseif not v756.Parent or v756.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(2764.2233886719, 432.46154785156, -7144.4580078125))
				end
			end)
		end
	end
end)
spawn(function()
	while wait() do
		if _G.Tp_MasterA then
			pcall(function()
				for _, child in pairs(replicated.NPCs:GetChildren()) do
					if child.Name == "Barista Cousin" then
						_tp(child.HumanoidRootPart.CFrame)
					end
				end
			end)
		end
	end
end)

do
	spawn(function()
		pcall(function()
			while wait(Sec) do
				if _G.Auto_Rainbow_Haki then
					if plr.PlayerGui.Main.Quest.Visible ~= false then
						if plr.PlayerGui.Main.Quest.Visible == true then
							if string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Stone") then
								local Stone = GetConnectionEnemies("Stone")

								if Stone then
									while true do
										wait()
										Attack.Kill(Stone, _G.Auto_Rainbow_Haki)

										if _G.Auto_Rainbow_Haki == false then
											break
										elseif Stone.Humanoid.Health <= 0 or not Stone.Parent or plr.PlayerGui.Main.Quest.Visible == false then
											break
										end
									end
								else
									_tp(CFrame.new(-1086.11621, 38.8425903, 6768.71436, 0.0231462717, -0.592676699, 0.805107772, 2.03251839e-05, 0.805323839, 0.592835128, -0.999732077, -0.0137055516, 0.0186523199))
								end

								continue
							end
						end

						if plr.PlayerGui.Main.Quest.Visible == true and string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Hydra Leader") then
							local v760 = GetConnectionEnemies("Hydra Leader")

							if v760 then
								while true do
									task.wait()
									Attack.Kill(v760, _G.Auto_Rainbow_Haki)

									if _G.Auto_Rainbow_Haki == false then
										break
									elseif v760.Humanoid.Health <= 0 or not v760.Parent or plr.PlayerGui.Main.Quest.Visible == false then
										break
									end
								end
							else
								replicated.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(5643.45263671875, 1013.0858154296875, -340.51025390625))

								local vector3 = Vector3.new(5643.45263671875, 1013.0858154296875, -340.51025390625)
								local cFrame3 = CFrame.new(5821.89794921875, 1019.0950927734375, -73.719230651855469)

								if plr.Character.HumanoidRootPart.CFrame.Position == vector3 then
									_tp(cFrame3)
								end
							end
						elseif plr.PlayerGui.Main.Quest.Visible == true and string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Kilo Admiral") then
							local v763 = GetConnectionEnemies("Kilo Admiral")

							if v763 then
								while true do
									task.wait()
									Attack.Kill(v763, _G.Auto_Rainbow_Haki)

									if _G.Auto_Rainbow_Haki == false then
										break
									elseif v763.Humanoid.Health <= 0 or not v763.Parent or plr.PlayerGui.Main.Quest.Visible == false then
										break
									end
								end
							else
								_tp(CFrame.new(2877.61743, 423.558685, -7207.31006, -0.989591599, -0, -0.143904909, -0, 1.00000012, -0, 0.143904924, 0, -0.989591479))
							end
						elseif plr.PlayerGui.Main.Quest.Visible == true and string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Captain Elephant") then
							local v764 = GetConnectionEnemies("Captain Elephant")

							if v764 then
								while true do
									task.wait()
									Attack.Kill(v764, _G.Auto_Rainbow_Haki)

									if _G.Auto_Rainbow_Haki == false then
										break
									elseif v764.Humanoid.Health <= 0 or not v764.Parent or plr.PlayerGui.Main.Quest.Visible == false then
										break
									end
								end
							else
								local vector3 = Vector3.new(-12471.169921875, 374.94024658203, -7551.677734375)
								local cFrame3 = CFrame.new(-13376.7578125, 433.28689575195, -8071.392578125)

								if plr.Character.HumanoidRootPart.CFrame.Position ~= vector3 then
									replicated.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(-12471.169921875, 374.94024658203, -7551.677734375))
								elseif plr.Character.HumanoidRootPart.CFrame.Position == vector3 then
									_tp(cFrame3)
								end
							end
						elseif plr.PlayerGui.Main.Quest.Visible == true and string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Beautiful Pirate") then
							local v767 = GetConnectionEnemies("Captain Elephant")

							if v767 then
								while true do
									task.wait()
									Attack.Kill(v767, _G.Auto_Rainbow_Haki)

									if _G.Auto_Rainbow_Haki == false then
										break
									elseif v767.Humanoid.Health <= 0 or not v767.Parent or plr.PlayerGui.Main.Quest.Visible == false then
										break
									end
								end
							else
								replicated.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(5314.54638671875, 22.562219619750977, -127.06755065917969))
							end
						end
					elseif not _G.GetQFast then
						Rainbow1 = CFrame.new(-11892.0703125, 930.57672119141, -8760.1591796875)

						if plr.Character.HumanoidRootPart.CFrame ~= Rainbow1 then
							_tp(Rainbow1)
						elseif plr.Character.HumanoidRootPart.CFrame == Rainbow1 then
							wait(1)
							replicated.Remotes.CommF_:InvokeServer("HornedMan", "Bet")
						end
					elseif plr.PlayerGui.Main.Quest.Visible == false then
						replicated.Remotes.CommF_:InvokeServer("HornedMan", "Bet")
					end
				end
			end
		end)
	end)
end

do
	spawn(function()
		while wait(0.2) do
			pcall(function()
				if _G.obsFarm then
					replicated.Remotes.CommE:FireServer("Ken", true)

					if plr:GetAttribute("KenDodgesLeft") == 0 then
						KenTest = false
					elseif plr:GetAttribute("KenDodgesLeft") > 0 then
						replicated.Remotes.CommE:FireServer("Ken", true)
						KenTest = true
					end
				end
			end)
		end
	end)
end

do
	spawn(function()
		while wait(0.2) do
			pcall(function()
				if _G.obsFarm then
					if not World1 then
						if not World2 then
							if World3 then
								if not workspace.Enemies:FindFirstChild("Venomous Assailant") then
									_tp(CFrame.new(4530.3540039063, 656.75695800781, -131.60952758789))
								elseif KenTest then
									while true do
										wait()
										_tp(workspace.Enemies:FindFirstChild("Venomous Assailant").HumanoidRootPart.CFrame * CFrame.new(3, 0, 0))

										if _G.obsFarm == false then
											break
										elseif KenTest == false then
											break
										end
									end
								else
									while true do
										wait()
										_tp(workspace.Enemies:FindFirstChild("Venomous Assailant").HumanoidRootPart.CFrame * CFrame.new(0, 50, 0))

										if _G.obsFarm == false then
											break
										elseif KenTest then
											break
										end
									end
								end
							end
						elseif not workspace.Enemies:FindFirstChild("Lava Pirate") then
							_tp(CFrame.new(-5478.39209, 15.9775667, -5246.9126))
						elseif KenTest then
							while true do
								wait()
								plr.Character.HumanoidRootPart.CFrame = workspace.Enemies:FindFirstChild("Lava Pirate").HumanoidRootPart.CFrame * CFrame.new(3, 0, 0)

								if _G.obsFarm == false then
									break
								elseif KenTest == false then
									break
								end
							end
						else
							while true do
								wait()
								plr.Character.HumanoidRootPart.CFrame = workspace.Enemies:FindFirstChild("Lava Pirate").HumanoidRootPart.CFrame * CFrame.new(0, 50, 0)

								if _G.obsFarm == false then
									break
								elseif KenTest then
									break
								end
							end
						end
					elseif not workspace.Enemies:FindFirstChild("Galley Captain") then
						_tp(CFrame.new(5533.29785, 88.1079102, 4852.3916))
					elseif KenTest then
						while true do
							wait()
							plr.Character.HumanoidRootPart.CFrame = workspace.Enemies:FindFirstChild("Galley Captain").HumanoidRootPart.CFrame * CFrame.new(3, 0, 0)

							if _G.obsFarm == false then
								break
							elseif KenTest == false then
								break
							end
						end
					else
						while true do
							wait()
							plr.Character.HumanoidRootPart.CFrame = workspace.Enemies:FindFirstChild("Galley Captain").HumanoidRootPart.CFrame * CFrame.new(0, 50, 0)

							if _G.obsFarm == false then
								break
							elseif KenTest then
								break
							end
						end
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait(Sec) do
		if _G.AutoKenVTWO then
			pcall(function()
				local _
				local state = 1
				local cFrame3, cFrame4, cFrame5, cFrame6, v785, v786, forIter, forState, forControl, v790, forIter2, forState2, forControl2, v794, forIter3, forState3, forControl3, v798

				while true do
					if state <= 2 then
						if state == 1 then
							cFrame3 = CFrame.new(-12444.78515625, 332.40396118164, -7673.1806640625)
							cFrame4 = CFrame.new(-10920.125, 624.20275878906, -10266.995117188)
							cFrame5 = CFrame.new(-13277.568359375, 370.34185791016, -7821.1572265625)
							cFrame6 = CFrame.new(-13493.12890625, 318.89553833008, -8373.7919921875)

							if plr.PlayerGui.Main.Quest.Visible == true and string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Defeat 50 Forest Pirates") then
								state = 2
							else
								state = 6
							end
						elseif state == 2 then
							v785 = GetConnectionEnemies("Forest Pirate")

							if v785 then
								state = 3
							else
								state = 5
							end
						end
					elseif state <= 4 then
						if state == 3 then
							wait()
							Attack.Kill(v785, _G.AutoKenVTWO)

							if _G.AutoKenVTWO then
								state = 4
							else
								state = 14
							end
						elseif state == 4 then
							if v785.Humanoid.Health <= 0 or plr.PlayerGui.Main.Quest.Visible == false then
								state = 14
							else
								state = 3
							end
						end
					elseif state <= 6 then
						if state == 5 then
							_tp(cFrame5)
							state = 14
						elseif state == 6 then
							if plr.PlayerGui.Main.Quest.Visible == true then
								state = 7
							else
								state = 12
							end
						end
					elseif state <= 8 then
						if state == 7 then
							v786 = GetConnectionEnemies("Captain Elephant")

							if v786 then
								state = 8
							else
								state = 11
							end
						elseif state == 8 then
							state = 9
						end
					elseif state <= 10 then
						if state == 9 then
							wait()
							Attack.Kill(v786, _G.AutoKenVTWO)

							if _G.AutoKenVTWO then
								state = 10
							else
								state = 14
							end
						elseif state == 10 then
							if v786.Humanoid.Health <= 0 or plr.PlayerGui.Main.Quest.Visible == false then
								state = 14
							else
								state = 9
							end
						end
					elseif state <= 12 then
						if state == 11 then
							_tp(cFrame6)
							state = 14
						elseif state == 12 then
							if plr.PlayerGui.Main.Quest.Visible == false then
								state = 13
							else
								state = 14
							end
						end
					elseif state <= 14 then
						if state == 13 then
							replicated.Remotes.CommF_:InvokeServer("CitizenQuestProgress", "Citizen")
							wait(0.1)
							replicated.Remotes.CommF_:InvokeServer("StartQuest", "CitizenQuest", 1)
							state = 14
						elseif state == 14 then
							if replicated.Remotes.CommF_:InvokeServer("CitizenQuestProgress", "Citizen") == 2 then
								state = 15
							else
								state = 16
							end
						end
					elseif state <= 16 then
						if state == 15 then
							_tp(CFrame.new(-12513.51953125, 340.11373901367188, -9873.048828125))
							state = 17
						elseif state == 16 then
							state = 17
						end
					elseif state <= 18 then
						if state == 17 then
							if plr.Backpack:FindFirstChild("Fruit Bowl") then
								state = 18
							else
								state = 20
							end
						elseif state == 18 then
							if plr.Character:FindFirstChild("Fruit Bowl") then
								state = 19
							else
								state = 20
							end
						end
					elseif state <= 20 then
						if state == 19 then
							return
						elseif state == 20 then
							if GetBP("Fruit Bowl") then
								state = 24
							else
								state = 21
							end
						end
					elseif state <= 22 then
						if state == 21 then
							if GetBP("Apple") then
								state = 22
							else
								state = 49
							end
						elseif state == 22 then
							if GetBP("Banana") then
								state = 23
							else
								state = 44
							end
						end
					elseif state <= 24 then
						if state == 23 then
							if GetBP("Pineapple") then
								state = 24
							else
								state = 39
							end
						elseif state == 24 then
							if plr.Backpack:FindFirstChild("Banana") then
								state = 25
							else
								state = 27
							end
						end
					elseif state <= 26 then
						if state == 25 then
							if plr.Backpack:FindFirstChild("Apple") then
								state = 26
							else
								state = 27
							end
						elseif state == 26 then
							if plr.Backpack:FindFirstChild("Pineapple") then
								state = 30
							else
								state = 27
							end
						end
					elseif state <= 28 then
						if state == 27 then
							if plr:FindFirstChild("Banana") then
								state = 28
							else
								state = 33
							end
						elseif state == 28 then
							if plr:FindFirstChild("Apple") then
								state = 29
							else
								state = 33
							end
						end
					elseif state <= 30 then
						if state == 29 then
							if plr:FindFirstChild("Pineapple") then
								state = 30
							else
								state = 33
							end
						elseif state == 30 then
							wait()
							_tp(cFrame3)

							if _G.AutoKenVTWO then
								state = 32
							else
								state = 31
							end
						end
					elseif state <= 32 then
						if state == 31 then
							if plr.Character.HumanoidRootPart.CFrame == cFrame3 then
								state = 32
							else
								state = 30
							end
						elseif state == 32 then
							replicated.Remotes.CommF_:InvokeServer("CitizenQuestProgress", "Citizen")
							state = 33
						end
					elseif state <= 34 then
						if state == 33 then
							if plr.Backpack:FindFirstChild("Fruit Bowl") then
								state = 35
							else
								state = 34
							end
						elseif state == 34 then
							if plr.Character:FindFirstChild("Fruit Bowl") then
								state = 35
							else
								state = 38
							end
						end
					elseif state <= 36 then
						if state == 35 then
							if plr.Character.HumanoidRootPart.CFrame == cFrame4 then
								state = 36
							else
								state = 69
							end
						elseif state == 36 then
							if plr.Character.HumanoidRootPart.CFrame == cFrame4 then
								state = 67
							else
								state = 37
							end
						end
					elseif state <= 38 then
						if state == 37 then
							return
						elseif state == 38 then
							return
						end
					elseif state <= 40 then
						if state == 39 then
							_tp(CFrame.new(-712.8272705078125, 98.577049255371094, 5711.9541015625))
							state = 40
						elseif state == 40 then
							forIter, forState, forControl = pairs(workspace:GetDescendants())

							if type(forIter) == 'table' then
								local forMeta = getmetatable(forIter)

								if type(forMeta) == 'table' and forMeta['__iter'] then
									forIter, forState, forControl = (forMeta['__iter'](forIter))
								else
									forIter, forState, forControl = next, forIter, nil
								end
							end

							state = 41
						end
					elseif state <= 42 then
						if state == 41 then
							local v800

							v800, v790 = (forIter(forState, forControl))

							if v800 == nil then
								state = 52
							else
								forControl = v800
								state = 42
							end
						elseif state == 42 then
							if v790.Name == "Pineapple" then
								state = 43
							else
								state = 41
							end
						end
					elseif state <= 44 then
						if state == 43 then
							v790.Handle.CFrame = plr.Character.HumanoidRootPart.CFrame * CFrame.new(0, 1, 10)
							wait()
							firetouchinterest(plr.Character.HumanoidRootPart, v790.Handle, 0)
							wait()
							state = 41
						elseif state == 44 then
							_tp(CFrame.new(2286.0078125, 73.133918762207031, -7159.80908203125))
							state = 45
						end
					elseif state <= 46 then
						if state == 45 then
							forIter2, forState2, forControl2 = pairs(workspace:GetDescendants())

							if type(forIter2) == 'table' then
								local forMeta2 = getmetatable(forIter2)

								if type(forMeta2) == 'table' and forMeta2['__iter'] then
									forIter2, forState2, forControl2 = (forMeta2['__iter'](forIter2))
								else
									forIter2, forState2, forControl2 = next, forIter2, nil
								end
							end

							state = 46
						elseif state == 46 then
							local v802

							v802, v794 = (forIter2(forState2, forControl2))

							if v802 == nil then
								state = 52
							else
								forControl2 = v802
								state = 47
							end
						end
					elseif state <= 48 then
						if state == 47 then
							if v794.Name == "Banana" then
								state = 48
							else
								state = 46
							end
						elseif state == 48 then
							v794.Handle.CFrame = plr.Character.HumanoidRootPart.CFrame * CFrame.new(0, 1, 10)
							wait()
							firetouchinterest(plr.Character.HumanoidRootPart, v794.Handle, 0)
							wait()
							state = 46
						end
					elseif state <= 50 then
						if state == 49 then
							replicated.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(-12471.169921875, 374.94024658203, -7551.677734375))
							state = 50
						elseif state == 50 then
							forIter3, forState3, forControl3 = pairs(workspace:GetDescendants())

							if type(forIter3) == 'table' then
								local forMeta3 = getmetatable(forIter3)

								if type(forMeta3) == 'table' and forMeta3['__iter'] then
									forIter3, forState3, forControl3 = (forMeta3['__iter'](forIter3))
								else
									forIter3, forState3, forControl3 = next, forIter3, nil
								end
							end

							state = 51
						end
					elseif state <= 52 then
						if state == 51 then
							local v804

							v804, v798 = (forIter3(forState3, forControl3))

							if v804 == nil then
								state = 52
							else
								forControl3 = v804
								state = 72
							end
						elseif state == 52 then
							if plr.Backpack:FindFirstChild("Banana") then
								state = 53
							else
								state = 55
							end
						end
					elseif state <= 54 then
						if state == 53 then
							if plr.Backpack:FindFirstChild("Apple") then
								state = 54
							else
								state = 55
							end
						elseif state == 54 then
							if plr.Backpack:FindFirstChild("Pineapple") then
								state = 58
							else
								state = 55
							end
						end
					elseif state <= 56 then
						if state == 55 then
							if plr:FindFirstChild("Banana") then
								state = 56
							else
								state = 61
							end
						elseif state == 56 then
							if plr:FindFirstChild("Apple") then
								state = 57
							else
								state = 61
							end
						end
					elseif state <= 58 then
						if state == 57 then
							if plr:FindFirstChild("Pineapple") then
								state = 58
							else
								state = 61
							end
						elseif state == 58 then
							wait()
							_tp(cFrame3)

							if _G.AutoKenVTWO then
								state = 60
							else
								state = 59
							end
						end
					elseif state <= 60 then
						if state == 59 then
							if plr.Character.HumanoidRootPart.CFrame == cFrame3 then
								state = 60
							else
								state = 58
							end
						elseif state == 60 then
							replicated.Remotes.CommF_:InvokeServer("CitizenQuestProgress", "Citizen")
							state = 61
						end
					elseif state <= 62 then
						if state == 61 then
							if plr.Backpack:FindFirstChild("Fruit Bowl") then
								state = 63
							else
								state = 62
							end
						elseif state == 62 then
							if plr.Character:FindFirstChild("Fruit Bowl") then
								state = 63
							else
								state = 71
							end
						end
					elseif state <= 64 then
						if state == 63 then
							if plr.Character.HumanoidRootPart.CFrame == cFrame4 then
								state = 64
							else
								state = 69
							end
						elseif state == 64 then
							if plr.Character.HumanoidRootPart.CFrame == cFrame4 then
								state = 66
							else
								state = 65
							end
						end
					elseif state <= 66 then
						if state == 65 then
							return
						elseif state == 66 then
							state = 67
						end
					elseif state <= 68 then
						if state == 67 then
							replicated.Remotes.CommF_:InvokeServer("KenTalk2", "Start")
							wait(0.1)
							replicated.Remotes.CommF_:InvokeServer("KenTalk2", "Buy")
							state = 68
						elseif state == 68 then
							return
						end
					elseif state <= 70 then
						if state == 69 then
							_tp(cFrame4)
							state = 70
						elseif state == 70 then
							return
						end
					elseif state <= 72 then
						if state == 71 then
							return
						elseif state == 72 then
							if v798.Name == "Apple" then
								state = 73
							else
								state = 51
							end
						end
					elseif state == 73 then
						v798.Handle.CFrame = plr.Character.HumanoidRootPart.CFrame * CFrame.new(0, 1, 10)
						wait()
						firetouchinterest(plr.Character.HumanoidRootPart, v798.Handle, 0)
						wait()
						state = 51
					end
				end
			end)
		end
	end
end)

do
	spawn(function()
		if wait(0.1) then
			repeat
				pcall(function()
					if _G.Bartilo_Quest and Lv >= 850 then
						local Quest = plr.PlayerGui.Main.Quest

						if replicated.Remotes.CommF_:InvokeServer("BartiloQuestProgress", "Bartilo") == 0 then
							_G.Level = false

							if Quest.Visible ~= true then
								while true do
									wait()
									_tp(CFrame.new(-461.533203, 72.3478546, 300.311096, 0.050853312, -0, -0.998706102, 0, 1, -0, 0.998706102, 0, 0.050853312))

									if (CFrame.new(-461.533203, 72.3478546, 300.311096, 0.050853312, -0, -0.998706102, 0, 1, -0, 0.998706102, 0, 0.050853312).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 20 then
										break
									elseif _G.Bartilo_Quest == false then
										break
									end
								end

								if (CFrame.new(-461.533203, 72.3478546, 300.311096, 0.050853312, -0, -0.998706102, 0, 1, -0, 0.998706102, 0, 0.050853312).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 1 then
									replicated.Remotes.CommF_:InvokeServer("StartQuest", "BartiloQuest", 1)
								end
							elseif GetConnectionEnemies("Swan Pirate") then
								local v806 = GetConnectionEnemies(BartMon)

								if v806 then
									repeat
										task.wait()

										if string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Swan Pirate") then
											Attack.Kill(v806, _G.Bartilo_Quest)
										else
											replicated.Remotes.CommF_:InvokeServer("AbandonQuest")
										end
									until _G.Bartilo_Quest == false or not v806.Parent or v806.Humanoid.Health <= 0 or Quest.Visible == false or not v806:FindFirstChild("HumanoidRootPart")
								end
							else
								_tp(CFrame.new(970.369446, 142.653198, 1217.3667, 0.162079468, -4.85452638e-08, -0.986777723, 1.03357589e-08, 1, -4.74980872e-08, 0.986777723, -2.50063148e-09, 0.162079468))
							end
						elseif replicated.Remotes.CommF_:InvokeServer("BartiloQuestProgress", "Bartilo") == 1 then
							_G.Level = false

							local Jeremy = GetConnectionEnemies("Jeremy")

							if Jeremy then
								while true do
									task.wait()
									Attack.Kill(Jeremy, _G.Bartilo_Quest)

									if _G.Bartilo_Quest == false then
										break
									elseif not Jeremy.Parent or Jeremy.Humanoid.Health <= 0 or Quest.Visible == false or not Jeremy:FindFirstChild("HumanoidRootPart") then
										break
									end
								end
							else
								_tp(CFrame.new(2158.97412, 449.056244, 705.411682, -0.754199564, -4.17389057e-09, -0.656645238, -4.47752875e-08, 1, 4.50709301e-08, 0.656645238, 6.3393955e-08, -0.754199564))
							end
						elseif replicated.Remotes.CommF_:InvokeServer("BartiloQuestProgress", "Bartilo") == 2 then
							while true do
								wait()
								_tp(CFrame.new(-1830.83972, 10.5578213, 1680.60229, 0.979988456, -2.02152783e-08, -0.199054286, 2.20792113e-08, 1, 7.1442483e-09, 0.199054286, -1.13962431e-08, 0.979988456))

								if (CFrame.new(-1830.83972, 10.5578213, 1680.60229, 0.979988456, -2.02152783e-08, -0.199054286, 2.20792113e-08, 1, 7.1442483e-09, 0.199054286, -1.13962431e-08, 0.979988456).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 1 then
									break
								elseif _G.Bartilo_Quest == false then
									break
								end
							end

							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Dressrosa.BartiloPlates.Plate1.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Dressrosa.BartiloPlates.Plate2.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Dressrosa.BartiloPlates.Plate3.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Dressrosa.BartiloPlates.Plate4.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Dressrosa.BartiloPlates.Plate5.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Dressrosa.BartiloPlates.Plate6.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Dressrosa.BartiloPlates.Plate7.CFrame
							wait(0.5)
							plr.Character.HumanoidRootPart.CFrame = workspace.Map.Dressrosa.BartiloPlates.Plate8.CFrame
							wait(2.5)
						end
					end
				end)
			until not wait(0.1)
		end
	end)
end

spawn(function()
	if wait(Sec) then
		repeat
			pcall(function()
				if _G.CitizenQuest then
					local ok2 = not (Lv >= 1800)

					if not ok2 then
						ok2 = replicated.Remotes.CommF_:InvokeServer("CitizenQuestProgress").KilledBandits ~= false
					end

					if ok2 then
						local ok = not (Lv >= 1800)

						if not ok then
							ok = replicated.Remotes.CommF_:InvokeServer("CitizenQuestProgress").KilledBoss ~= false
						end

						if not ok then
							local v810 = GetConnectionEnemies("Captain Elephant")

							if not plr.PlayerGui.Main.Quest.Visible or not string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Captain Elephant") or plr.PlayerGui.Main.Quest.Visible ~= true then
								_tp(CFrame.new(-12443.8671875, 332.40396118164, -7675.4892578125))

								if (CFrame.new(-12443.8671875, 332.40396118164, -7675.4892578125).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 4 then
									wait(1.5)
									replicated.Remotes.CommF_:InvokeServer("CitizenQuestProgress", "Citizen")
								end
							elseif v810 then
								while true do
									task.wait()
									Attack.Kill(v810, _G.CitizenQuest)

									if _G.CitizenQuest == false then
										break
									elseif v810.Humanoid.Health <= 0 or not v810.Parent or plr.PlayerGui.Main.Quest.Visible == false then
										break
									end
								end
							else
								_tp(CFrame.new(-13374.889648438, 421.27752685547, -8225.208984375))
							end
						elseif Lv >= 1800 then
							if replicated.Remotes.CommF_:InvokeServer("CitizenQuestProgress", "Citizen") == 2 then
								_tp(CFrame.new(-12512.138671875, 340.39279174805, -9872.8203125))
							end
						end
					elseif string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "Forest Pirate") and string.find(plr.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text, "50") and plr.PlayerGui.Main.Quest.Visible == true then
						local v811 = GetConnectionEnemies("Forest Pirate")

						if v811 then
							while true do
								task.wait()
								Attack.Kill(v811, _G.CitizenQuest)

								if _G.CitizenQuest == false then
									break
								elseif not v811.Parent or v811.Humanoid.Health <= 0 or plr.PlayerGui.Main.Quest.Visible == false then
									break
								end
							end
						else
							_tp(CFrame.new(-13206.452148438, 425.89199829102, -7964.5537109375))
						end
					else
						_tp(CFrame.new(-12443.8671875, 332.40396118164, -7675.4892578125))

						if (Vector3.new(-12443.8671875, 332.40396118164, -7675.4892578125) - plr.Character.HumanoidRootPart.Position).Magnitude <= 30 then
							wait(1.5)
							replicated.Remotes.CommF_:InvokeServer("StartQuest", "CitizenQuest", 1)
						end
					end
				end
			end)
		until not wait(Sec)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.DummyMan then
			pcall(function()
				if plr.PlayerGui.Main.Quest.Visible == false then
					replicated:WaitForChild("Remotes"):WaitForChild("CommF_"):InvokeServer(unpack({ "ArenaTrainer" }))

					return
				end

				local v812 = GetConnectionEnemies("Training Dummy")

				if v812 then
					while true do
						wait()
						Attack.Kill(v812, _G.DummyMan)

						if not _G.DummyMan then
							break
						elseif not v812.Parent or v812.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(3688.005126953125, 12.746943473815918, 170.20953369140625))
				end
			end)
		end
	end
end)
spawn(function()
	if wait(Sec) then
		repeat
			pcall(function()
				if _G.Auto_SuperHuman then
					local Value = plr.Data.Beli.Value
					local Value2 = plr.Data.Fragments.Value

					if plr:FindFirstChild("WeaponAssetCache") and not GetBP("Superhuman") then
						if not GetBP("Black Leg") then
							if Value >= 150000 then
								replicated.Remotes.CommF_:InvokeServer("BuyBlackLeg")
							end
						elseif GetBP("Black Leg") and GetBP("Black Leg").Level.Value < 299 then
							_G.Level = true
						elseif GetBP("Black Leg") and GetBP("Black Leg").Level.Value >= 300 then
							_G.Level = false
						end

						if not GetBP("Electro") then
							if Value >= 500000 then
								replicated.Remotes.CommF_:InvokeServer("BuyElectro")
							end
						elseif GetBP("Electro") and GetBP("Electro").Level.Value < 299 then
							_G.Level = true
						elseif GetBP("Electro") and GetBP("Electro").Level.Value >= 300 then
							_G.Level = false
						end

						if not GetBP("Fishman Karate") then
							if Value >= 750000 then
								replicated.Remotes.CommF_:InvokeServer("BuyFishmanKarate")
							end
						elseif GetBP("Fishman Karate") and GetBP("Fishman Karate").Level.Value < 299 then
							_G.Level = true
						elseif GetBP("Fishman Karate") and GetBP("Fishman Karate").Level.Value >= 300 then
							_G.Level = false
						end

						if not GetBP("Dragon Claw") then
							if Value2 >= 1500 then
								replicated.Remotes.CommF_:InvokeServer("BlackbeardReward", "DragonClaw", "2")
							end
						elseif GetBP("Dragon Claw") and GetBP("Dragon Claw").Level.Value < 299 then
							_G.Level = true
						elseif GetBP("Dragon Claw") and GetBP("Dragon Claw").Level.Value >= 300 then
							_G.Level = false
						end

						replicated.Remotes.CommF_:InvokeServer("BuySuperhuman")
					end
				end
			end)
		until not wait(Sec)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.AutoDeathStep then
			local exitTo

			repeat
				pcall(function()
					if plr:FindFirstChild("WeaponAssetCache") then
						if not GetBP("Death Step") then
							if not GetBP("Black Leg") then
								replicated.Remotes.CommF_:InvokeServer("BuyBlackLeg")
							end

							if GetBP("Black Leg") and GetBP("Black Leg").Level.Value >= 400 then
								replicated.Remotes.CommF_:InvokeServer("BuyDeathStep")
								_G.Level = false
							elseif GetBP("Black Leg") and GetBP("Black Leg").Level.Value < 399 then
								_G.Level = true
							end

							if (GetBP("Black Leg") or GetBP("Black Leg").Level.Value >= 400) and workspace.Map.IceCastle.Hall.LibraryDoor.PhoeyuDoor.Transparency == 0 then
								if GetBP("Library Key") then
									while true do
										wait()
										_tp(CFrame.new(6371.2001953125, 296.63433837890625, -6841.18115234375))

										if not _G.AutoDeathStep then
											break
										elseif Root.Position == CFrame.new(6371.2001953125, 296.63433837890625, -6841.18115234375).Position then
											break
										end
									end

									if Root.CFrame == CFrame.new(6371.2001953125, 296.63433837890625, -6841.18115234375) then
										replicated.Remotes.CommF_:InvokeServer("BuyDeathStep")
									end
								elseif not GetBP("Library Key") then
									local v816 = GetConnectionEnemies("Awakened Ice Admiral")

									if v816 then
										while true do
											wait()
											Attack.Kill(v816, _G.AutoDeathStep)

											if not v816.Parent then
												break
											elseif v816.Humanoid.Health <= 0 or _G.AutoDeathStep == false or GetBP("Library Key") or GetBP("Death Step") then
												break
											end
										end
									else
										_tp(CFrame.new(5668.9780273438, 28.519989013672, -6483.3520507813))
									end
								end
							end
						end
					end
				end)
				exitTo = nil

				while wait(Sec) do
					if _G.AutoDeathStep then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.Auto_SharkMan_Karate then
			local exitTo

			repeat
				pcall(function()
					if plr:FindFirstChild("WeaponAssetCache") then
						if not GetBP("Sharkman Karate") then
							if not GetBP("Fishman Karate") then
								replicated.Remotes.CommF_:InvokeServer("BuyFishmanKarate")
							end

							if GetBP("Fishman Karate") and GetBP("Fishman Karate").Level.Value >= 400 then
								replicated.Remotes.CommF_:InvokeServer("BuySharkmanKarate")
								_G.Level = false
							elseif GetBP("Fishman Karate") and GetBP("Fishman Karate").Level.Value < 399 then
								_G.Level = true
							end

							if GetBP("Fishman Karate") or GetBP("Fishman Karate").Level.Value >= 400 then
								if not GetBP("Water Key") then
									if not GetBP("Water Key") then
										local v818 = GetConnectionEnemies("Tide Keeper")

										if v818 then
											while true do
												wait()
												Attack.Kill(v818, _G.Auto_SharkMan_Karate)

												if not v818.Parent then
													break
												elseif v818.Humanoid.Health <= 0 or _G.Auto_SharkMan_Karate == false or GetBP("Water Key") or GetBP("Sharkman Karate") then
													break
												end
											end
										else
											_tp(CFrame.new(-3053.9814453125, 237.18954467773, -10145.0390625))
										end
									end
								elseif string.find(replicated.Remotes.CommF_:InvokeServer("BuySharkmanKarate"), "keys") and GetBP("Water Key") then
									while true do
										wait()
										_tp(CFrame.new(-2604.6958, 239.432526, -10315.1982, 0.0425701365, 0, -0.999093413, 0, 1, 0, 0.999093413, 0, 0.0425701365))

										if not _G.Auto_SharkMan_Karate then
											break
										elseif Root.Position == CFrame.new(-2604.6958, 239.432526, -10315.1982, 0.0425701365, 0, -0.999093413, 0, 1, 0, 0.999093413, 0, 0.0425701365).Position then
											break
										end
									end

									replicated.Remotes.CommF_:InvokeServer("BuySharkmanKarate")
								end
							end
						end
					end
				end)
				exitTo = nil

				while wait(Sec) do
					if _G.Auto_SharkMan_Karate then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.Auto_Electric_Claw then
			pcall(function()
				if plr:FindFirstChild("WeaponAssetCache") then
					if not GetBP("Electro") then
						replicated.Remotes.CommF_:InvokeServer("BuyElectro")
					end

					if GetBP("Electro") and GetBP("Electro").Level.Value >= 400 then
						if replicated.Remotes.CommF_:InvokeServer("BuyElectricClaw", "Start") == nil then
							notween(CFrame.new(-12548, 337, -7481))
						end

						replicated.Remotes.CommF_:InvokeServer("BuyElectricClaw")
					elseif GetBP("Electro") and GetBP("Electro").Level.Value < 400 then
						while true do
							_G.AutoFarm_Bone = true
							wait()

							if not _G.Auto_Electric_Claw then
								break
							elseif GetBP("Electric Claw") then
								break
							end
						end

						_G.AutoFarm_Bone = false
					end
				end
			end)
		end
	end
end)

do
	spawn(function()
		while wait(Sec) do
			if _G.AutoDragonTalon then
				local exitTo

				repeat
					pcall(function()
						if plr:FindFirstChild("WeaponAssetCache") then
							if not GetBP("Dragon Claw") then
								replicated.Remotes.CommF_:InvokeServer("BlackbeardReward", "DragonClaw", "2")
							end

							if GetBP("Dragon Claw") and GetBP("Dragon Claw").Level.Value >= 400 then
								replicated.Remotes.CommF_:InvokeServer("Bones", "Buy", 1, 1)
								replicated.Remotes.CommF_:InvokeServer("BuyDragonTalon")
							elseif GetBP("Dragon Claw") and GetBP("Dragon Claw").Level.Value < 400 then
								while true do
									_G.AutoFarm_Bone = true
									wait()

									if not _G.AutoDragonTalon then
										break
									elseif GetBP("Dragon Talon") then
										break
									end
								end

								_G.AutoFarm_Bone = false
							end
						end
					end)
					exitTo = nil

					while wait(Sec) do
						if _G.AutoDragonTalon then
							exitTo = 1

							break
						end
					end
				until exitTo ~= 1

				return
			end
		end
	end)
end

spawn(function()
	while wait() do
		pcall(function()
			if _G.Auto_God_Human then
				if replicated.Remotes.CommF_:InvokeServer("BuyGodhuman", true) ~= "Bring me 20 Fish Tails, 20 Magma Ore, 10 Dragon Scales and 10 Mystic Droplets." then
					if replicated.Remotes.CommF_:InvokeServer("BuyGodhuman", true) == 3 then
						return nil
					end

					replicated.Remotes.CommF_:InvokeServer("BuyGodhuman")
				elseif GetM("Dragon Scale") == false or GetM("Dragon Scale") < 10 then
					if World3 then
						Lv = 1575
						_G.Level = true
					else
						replicated.Remotes.CommF_:InvokeServer("TravelZou")
					end
				elseif GetM("Fish Tail") == false or GetM("Fish Tail") < 20 then
					if World3 then
						Lv = 1775
						_G.Level = true
					else
						replicated.Remotes.CommF_:InvokeServer("TravelZou")
					end
				elseif GetM("Mystic Droplet") == false or GetM("Mystic Droplet") < 10 then
					if World2 then
						Lv = 1425
						_G.Level = true
					else
						replicated.Remotes.CommF_:InvokeServer("TravelDressrosa")
					end
				elseif GetM("Magma Ore") == false or GetM("Magma Ore") < 20 then
					if World2 then
						Lv = 1175
						_G.Level = true
					else
						replicated.Remotes.CommF_:InvokeServer("TravelDressrosa")
					end
				end
			end
		end)
	end
end)

do
	spawn(function()
		while wait(Sec) do
			if _G.Snaguine then
				pcall(function()
					if not GetBP("Sanguine Art") then
						replicated.Remotes.CommF_:InvokeServer("Sanguine Art")
					end

					if GetBP("Sanguine Art") then
						replicated.Remotes.CommF_:InvokeServer("BuySanguineArt")
					else
						if GetM("Leviathan Heart") >= 1 then
							print("Completed!!")
						elseif World3 then
							_G.DangerSc = "Lv Infinite"
							_G.SailBoats = true
						else
							_G.SailBoats = false
						end

						if GetM("Vampire Fang") <= 19 then
							if World2 then
								local Vampire = GetConnectionEnemies("Vampire")

								if Vampire then
									while true do
										task.wait()
										Attack.Kill(Vampire, _G.Snaguine)

										if not _G.Snaguine then
											break
										elseif Vampire.Humanoid.Health <= 0 or not Vampire.Parent then
											break
										end
									end
								else
									_tp(CFrame.new(-6041.29248046875, 6.4027109146118164, -1304.63330078125))
								end
							else
								replicated.Remotes.CommF_:InvokeServer("TravelDressrosa")
							end
						end

						if GetM("Vampire Fang") >= 20 and GetM("Demonic Wisp") <= 19 then
							if World3 then
								local v821 = GetConnectionEnemies("Demonic Soul")

								if v821 then
									while true do
										task.wait()
										Attack.Kill(v821, _G.Snaguine)

										if not _G.Snaguine then
											break
										elseif v821.Humanoid.Health <= 0 or not v821.Parent then
											break
										end
									end
								else
									_tp(CFrame.new(-9495.6806640625, 453.58624267578125, 5977.3486328125))
								end
							else
								replicated.Remotes.CommF_:InvokeServer("TravelZou")
							end
						end

						if GetM("Vampire Fang") >= 20 and GetM("Demonic Wisp") >= 20 and GetM("Dark Fragment") <= 1 then
							if World2 then
								local Darkbeard = GetConnectionEnemies("Darkbeard")

								if Darkbeard then
									while true do
										task.wait()
										Attack.Kill(Darkbeard, _G.Snaguine)

										if not _G.Snaguine then
											break
										elseif Darkbeard.Humanoid.Health <= 0 or not Darkbeard.Parent then
											break
										end
									end
								else
									_tp(CFrame.new(3798.4575195313, 13.826690673828, -3399.806640625))
								end
							else
								replicated.Remotes.CommF_:InvokeServer("TravelDressrosa")
							end
						end
					end
				end)
			end
		end
	end)
end

spawn(function()
	while wait() do
		if _G.FindMirage then
			pcall(function()
				if workspace._WorldOrigin.Locations:FindFirstChild("Mirage Island", true) then
					_tp(workspace.Map:FindFirstChild("MysticIsland").Center.CFrame * CFrame.new(0, 300, 0))
				else
					local v823 = CheckBoat()

					if not v823 then
						local cFrame3 = CFrame.new(-16927.451, 9.086, 433.864)

						TeleportToTarget(cFrame3)

						if (cFrame3.Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
							replicated.Remotes.CommF_:InvokeServer("BuyBoat", _G.SelectedBoat)
						end
					elseif plr.Character.Humanoid.Sit == false then
						_tp(v823.VehicleSeat.CFrame * CFrame.new(0, 1, 0))
					else
						while true do
							wait()

							local cFrame3 = CFrame.new(-10000000, 31, 37016.25)

							if CheckEnemiesBoat() or CheckTerrorShark() or CheckPirateGrandBrigade() then
								_tp(CFrame.new(-10000000, 150, 37016.25))
							else
								_tp(CFrame.new(-10000000, 31, 37016.25))
							end

							if _G.FindMirage and not ((cFrame3.Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10) then
								if not workspace._WorldOrigin.Locations:FindFirstChild("Mirage Island") and plr.Character.Humanoid.Sit ~= false then
									continue
								end
							end

							break
						end

						plr.Character.Humanoid.Sit = false
					end
				end
			end)
		end
	end
end)
spawn(function()
	while task.wait(0.1) do
		pcall(function()
			if _G.AutoMysticIsland then
				for _, child in pairs(game:GetService("Workspace")._WorldOrigin.Locations:GetChildren()) do
					if child.Name == "Mirage Island" then
						topos(child.CFrame * CFrame.new(0, 333, 0))
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.HighestMirage then
			pcall(function()
				if workspace._WorldOrigin.Locations:FindFirstChild("Mirage Island", true) then
					_tp(workspace.Map:FindFirstChild("MysticIsland").Center.CFrame * CFrame.new(0, 400, 0))
				end
			end)
		end
	end
end)

do
	spawn(function()
		pcall(function()
			while wait(0.1) do
				if _G.TPGEAR then
					local pairs_ = pairs
					local MysticIsland = workspace.Map:FindFirstChild("MysticIsland")

					for _, child in pairs_(MysticIsland:GetChildren()) do
						if child.Name == "Part" and child.ClassName == "MeshPart" then
							_tp(child.CFrame)
						end
					end
				end
			end
		end)
	end)
end

do
	spawn(function()
		pcall(function()
			while wait(Sec) do
				if _G.can then
					local pairs_ = pairs
					local MysticIsland = workspace.Map:FindFirstChild("MysticIsland")

					for _, child in pairs_(MysticIsland:GetChildren()) do
						if child.Name == "Part" then
							if child.ClassName == "MeshPart" then
								child.Transparency = 0
							else
								child.Transparency = 1
							end
						end
					end
				end
			end
		end)
	end)
end

spawn(function()
	while wait() do
		if _G.Addealer then
			local exitTo

			repeat
				pcall(function()
					for _, child in pairs(replicated.NPCs:GetChildren()) do
						if child.Name == "Advanced Fruit Dealer" then
							_tp(child.HumanoidRootPart.CFrame)
						end
					end
				end)
				exitTo = nil

				while wait() do
					if _G.Addealer then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)
spawn(function()
	while wait(0.2) do
		if _G.FarmChestM then
			pcall(function()
				local ok = workspace.Map:FindFirstChild("MysticIsland").Chests:FindFirstChild("DiamondChest")

				if not ok then
					ok = workspace.Map:FindFirstChild("MysticIsland").Chests:FindFirstChild("FragChest")
				end

				if ok then
					local CollectionService = game:GetService("CollectionService")
					local LocalPlayer2 = game:GetService("Players").LocalPlayer
					local Character = LocalPlayer2.Character or LocalPlayer2.CharacterAdded:Wait()

					if not Character then
						return
					end

					local Position = Character:GetPivot().Position
					local tagged = CollectionService:GetTagged("_ChestTagged")
					local huge = math.huge
					local v846

					for i = 1, #tagged do
						local v848 = tagged[i]
						local Magnitude = (v848:GetPivot().Position - Position).Magnitude

						if (not SelectedIsland or v848:IsDescendantOf(SelectedIsland)) and not v848:GetAttribute("IsDisabled") and Magnitude < huge then
							huge = Magnitude
							v846 = v848
						end
					end

					if v846 then
						_tp(v846:GetPivot())
					end
				end
			end)
		end
	end
end)
MoveCamtoMoon = function()
	workspace.CurrentCamera.CFrame = CFrame.new(workspace.CurrentCamera.CFrame.Position, Lighting:GetMoonDirection() + workspace.CurrentCamera.CFrame.Position)
	plr.Character.HumanoidRootPart.CFrame = CFrame.new(plr.Character.HumanoidRootPart.Position, Lighting:GetMoonDirection() + plr.Character.HumanoidRootPart.CFrame.Position)
end
task.spawn(function()
	while task.wait() do
		if LookM then
			MoveCamtoMoon()
			wait(0.1)
			replicated.Remotes.CommE:FireServer("ActivateAbility")
		end
	end
end)
MoveCamtoMoon = function()
	local moonDirection = Lighting:GetMoonDirection()

	workspace.CurrentCamera.CFrame = CFrame.new(workspace.CurrentCamera.CFrame.Position, workspace.CurrentCamera.CFrame.Position + moonDirection)
	plr.Character.HumanoidRootPart.CFrame = CFrame.new(plr.Character.HumanoidRootPart.Position, plr.Character.HumanoidRootPart.Position + moonDirection)
end
task.spawn(function()
	while task.wait(0.1) do
		if LookMV3 then
			MoveCamtoMoon()
			replicated.Remotes.CommE:FireServer("ActivateAbility")
			UserInputService:SendKeyEvent(true, "T", false, game)
			wait(0.5)
			UserInputService:SendKeyEvent(false, "T", false, game)
		end
	end
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.Auto_Mink then
					if replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 2 then
						if replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "1") == 0 then
							replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "2")
						elseif replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "1") == 1 then
							_G.AutoFarmChest = true
						else
							_G.AutoFarmChest = false
						end
					elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 0 then
						replicated.Remotes.CommF_:InvokeServer("Alchemist", "2")
					elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 1 then
						local ok2 = plr.Backpack:FindFirstChild("Flower 1")

						if not ok2 then
							ok2 = plr.Character:FindFirstChild("Flower 1")
						end

						if ok2 then
							local ok = plr.Backpack:FindFirstChild("Flower 2")

							if not ok then
								ok = plr.Character:FindFirstChild("Flower 2")
							end

							if not ok then
								_tp(workspace.Flower2.CFrame)
							elseif not plr.Backpack:FindFirstChild("Flower 3") then
								if not plr.Character:FindFirstChild("Flower 3") then
									local v853 = GetConnectionEnemies("Swan Pirate")

									if v853 then
										while true do
											wait()
											Attack.Kill(v853, _G.Auto_Mink)

											if GetBP("Flower 3") then
												break
											elseif not v853.Parent or v853.Humanoid.Health <= 0 or _G.Auto_Mink == false then
												break
											end
										end
									else
										_tp(CFrame.new(980.0985107421875, 121.331298828125, 1287.2093505859375))
									end
								end
							end
						else
							_tp(workspace.Flower1.CFrame)
						end
					elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 2 then
						replicated.Remotes.CommF_:InvokeServer("Alchemist", "3")
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Auto_Human then
				if replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == -2 then
					if replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "1") == 0 then
						replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "2")
					elseif replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "1") == 1 then
						local v854 = GetConnectionEnemies(Human_v3_Mob[1])

						if v854 then
							while true do
								wait()
								Attack.Kill(v854, _G.Auto_Human)

								if v854.Humanoid.Health <= 0 then
									break
								elseif not v854.Parent or not _G.Auto_Human then
									break
								end
							end
						else
							_tp(CFrame.new(-2172.7399902344, 103.32216644287, -4015.025390625))
						end

						local v855 = GetConnectionEnemies(Human_v3_Mob[2])

						if v855 then
							while true do
								wait()
								Attack.Kill(v855, _G.Auto_Human)

								if v855.Humanoid.Health <= 0 then
									break
								elseif not v855.Parent or not _G.Auto_Human then
									break
								end
							end
						else
							_tp(CFrame.new(2006.9261474609, 448.95666503906, 853.98284912109))
						end

						local v856 = GetConnectionEnemies(Human_v3_Mob[3])

						if v856 then
							while true do
								wait()
								Attack.Kill(v856, _G.Auto_Human)

								if v856.Humanoid.Health <= 0 then
									break
								elseif not v856.Parent or not _G.Auto_Human then
									break
								end
							end
						else
							_tp(CFrame.new(-1576.7166748047, 198.59265136719, 13.724286079407))
						end
					end
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 0 then
					replicated.Remotes.CommF_:InvokeServer("Alchemist", "2")
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 1 then
					local ok2 = plr.Backpack:FindFirstChild("Flower 1")

					if not ok2 then
						ok2 = plr.Character:FindFirstChild("Flower 1")
					end

					if ok2 then
						local ok = plr.Backpack:FindFirstChild("Flower 2")

						if not ok then
							ok = plr.Character:FindFirstChild("Flower 2")
						end

						if not ok then
							_tp(workspace.Flower2.CFrame)
						elseif not plr.Backpack:FindFirstChild("Flower 3") then
							if not plr.Character:FindFirstChild("Flower 3") then
								local v859 = GetConnectionEnemies("Swan Pirate")

								if v859 then
									while true do
										wait()
										Attack.Kill(v859, _G.Auto_Human)

										if plr.Backpack:FindFirstChild("Flower 3") then
											break
										elseif not v859.Parent or v859.Humanoid.Health <= 0 or _G.Auto_Human == false then
											break
										end
									end
								else
									_tp(CFrame.new(980.0985107421875, 121.331298828125, 1287.2093505859375))
								end
							end
						end
					else
						_tp(workspace.Flower1.CFrame)
					end
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 2 then
					replicated.Remotes.CommF_:InvokeServer("Alchemist", "3")
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Auto_Skypiea then
				if replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == -2 then
					if replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "1") == 0 then
						replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "2")
					elseif replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "1") == 1 then
						for _, child in pairs(game.Players:GetChildren()) do
							if child.Name ~= plr.Name and tostring(child.Data.Race.Value) == "Skypiea" then
								while true do
									task.wait()
									_tp(child.HumanoidRootPart.CFrame * CFrame.new(0, 8, 0) * CFrame.Angles(math.rad(-45), 0, 0))

									if child.Humanoid.Health <= 0 then
										break
									elseif _G.Auto_Skypiea == false then
										break
									end
								end
							end
						end
					end
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 0 then
					replicated.Remotes.CommF_:InvokeServer("Alchemist", "2")
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 1 then
					local ok2 = plr.Backpack:FindFirstChild("Flower 1")

					if not ok2 then
						ok2 = plr.Character:FindFirstChild("Flower 1")
					end

					if ok2 then
						local ok = plr.Backpack:FindFirstChild("Flower 2")

						if not ok then
							ok = plr.Character:FindFirstChild("Flower 2")
						end

						if not ok then
							_tp(workspace.Flower2.CFrame)
						elseif not plr.Backpack:FindFirstChild("Flower 3") then
							if not plr.Character:FindFirstChild("Flower 3") then
								local v864 = GetConnectionEnemies("Swan Pirate")

								if v864 then
									while true do
										wait()
										Attack.Kill(v864, _G.Auto_Skypiea)

										if plr.Backpack:FindFirstChild("Flower 3") then
											break
										elseif not v864.Parent or v864.Humanoid.Health <= 0 or _G.Auto_Skypiea == false then
											break
										end
									end
								else
									_tp(CFrame.new(980.0985107421875, 121.331298828125, 1287.2093505859375))
								end
							end
						end
					else
						_tp(workspace.Flower1.CFrame)
					end
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 2 then
					replicated.Remotes.CommF_:InvokeServer("Alchemist", "3")
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Auto_Fish then
				if replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == -2 then
					if replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "1") == 0 then
						replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "2")
					elseif replicated.Remotes.CommF_:InvokeServer("Wenlocktoad", "1") == 1 then
						warn("Sea Beast Soon")
					end
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 0 then
					replicated.Remotes.CommF_:InvokeServer("Alchemist", "2")
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 1 then
					local ok2 = plr.Backpack:FindFirstChild("Flower 1")

					if not ok2 then
						ok2 = plr.Character:FindFirstChild("Flower 1")
					end

					if ok2 then
						local ok = plr.Backpack:FindFirstChild("Flower 2")

						if not ok then
							ok = plr.Character:FindFirstChild("Flower 2")
						end

						if not ok then
							_tp(workspace.Flower2.CFrame)
						elseif not plr.Backpack:FindFirstChild("Flower 3") then
							if not plr.Character:FindFirstChild("Flower 3") then
								local v867 = GetConnectionEnemies("Swan Pirate")

								if v867 then
									while true do
										wait()
										Attack.Kill(v867, _G.Auto_Fish)

										if plr.Backpack:FindFirstChild("Flower 3") then
											break
										elseif not v867.Parent or v867.Humanoid.Health <= 0 or _G.Auto_Fish == false then
											break
										end
									end
								else
									_tp(CFrame.new(980.0985107421875, 121.331298828125, 1287.2093505859375))
								end
							end
						end
					else
						_tp(workspace.Flower1.CFrame)
					end
				elseif replicated.Remotes.CommF_:InvokeServer("Alchemist", "1") == 2 then
					replicated.Remotes.CommF_:InvokeServer("Alchemist", "3")
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.Lver then
			pcall(function()
				for _, descendant in pairs(workspace.Map["Temple of Time"]:GetDescendants()) do
					if descendant.Name == "ProximityPrompt" then
						fireproximityprompt(descendant, math.huge)
					end
				end
			end)
		end
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.AcientOne then
				local t24 = {
					"Reborn Skeleton",
					"Living Zombie",
					"Demonic Soul",
					"Posessed Mummy"
				}

				for i = 1, #t24 do
					if plr.Character:FindFirstChild("RaceEnergy").Value == 1 then
						vim1:SendKeyEvent(true, "Y", false, game)
						replicated.Remotes.CommF_:InvokeServer("UpgradeRace", "Buy")
						_tp(CFrame.new(-8987.041015625, 215.862060546875, 5886.71044921875))
					elseif plr.Character:FindFirstChild("RaceTransformed").Value == false then
						local v872 = GetConnectionEnemies(t24)

						if v872 then
							while true do
								wait()
								Attack.Kill(v872, _G.AcientOne)

								if _G.AcientOne == false then
									break
								elseif v872.Humanoid.Health <= 0 or not v872.Parent then
									break
								end
							end
						else
							_tp(CFrame.new(-9495.6806640625, 453.58624267578125, 5977.3486328125))
						end
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.TPDoor then
				if tostring(plr.Data.Race.Value) == "Mink" then
					_tp(CFrame.new(29020.66015625, 14889.4267578125, -379.26828002929688))
				elseif tostring(plr.Data.Race.Value) == "Fishman" then
					_tp(CFrame.new(28224.056640625, 14889.4267578125, -210.58720397949219))
				elseif tostring(plr.Data.Race.Value) == "Cyborg" then
					_tp(CFrame.new(28492.4140625, 14894.4267578125, -422.11001586914062))
				elseif tostring(plr.Data.Race.Value) == "Skypiea" then
					_tp(CFrame.new(28967.408203125, 14918.0751953125, 234.31198120117188))
				elseif tostring(plr.Data.Race.Value) == "Ghoul" then
					_tp(CFrame.new(28672.720703125, 14889.1279296875, 454.59616088867188))
				elseif tostring(plr.Data.Race.Value) == "Human" then
					_tp(CFrame.new(29237.294921875, 14889.4267578125, -206.94955444335938))
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Complete_Trials and tostring(plr.Data.Race.Value) == "Mink" then
				notween(workspace.Map.MinkTrial.Ceiling.CFrame * CFrame.new(0, -20, 0))
			end
		end)
	end
end)
GetSeaBeastTrial = function()
	if not workspace.Map:FindFirstChild("FishmanTrial") then
		return nil
	end

	if workspace._WorldOrigin.Locations:FindFirstChild("Trial of Water") then
		FishmanTrial = workspace._WorldOrigin.Locations:FindFirstChild("Trial of Water")
	end

	if FishmanTrial then
		local next_ = next
		local children, v875 = workspace.SeaBeasts:GetChildren()

		for _, v in next_, children, v875 do
			if v:FindFirstChild("HumanoidRootPart") and (v.HumanoidRootPart.Position - FishmanTrial.Position).Magnitude <= 1500 and v.Health.Value > 0 then
				return v
			end
		end
	end
end
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Complete_Trials and tostring(plr.Data.Race.Value) == "Fishman" and GetSeaBeastTrial() then
				while true do
					task.wait()
					spawn(function()
						_tp(CFrame.new(GetSeaBeastTrial().HumanoidRootPart.Position.X, game:GetService("Workspace").Map["WaterBase-Plane"].Position.Y + 300, GetSeaBeastTrial().HumanoidRootPart.Position.Z))
					end)
					MousePos = GetSeaBeastTrial().HumanoidRootPart.Position
					Useskills("Melee", "Z")
					Useskills("Melee", "X")
					Useskills("Melee", "C")
					wait(0.1)
					Useskills("Sword", "Z")
					Useskills("Sword", "X")
					wait(0.1)
					Useskills("Blox Fruit", "Z")
					Useskills("Blox Fruit", "X")
					Useskills("Blox Fruit", "C")
					wait(0.1)
					Useskills("Gun", "Z")
					Useskills("Gun", "X")

					if _G.Complete_Trials == false then
						break
					elseif not GetSeaBeastTrial() then
						break
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Complete_Trials then
				if tostring(plr.Data.Race.Value) == "Cyborg" then
					_tp(workspace.Map.CyborgTrial.Floor.CFrame * CFrame.new(0, 500, 0))
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Complete_Trials and tostring(plr.Data.Race.Value) == "Skypiea" then
				notween(workspace.Map.SkyTrial.Model.FinishPart.CFrame)
			end
		end)
	end
end)

do
	spawn(function()
		while wait(0.1) do
			pcall(function()
				if _G.Complete_Trials and (tostring(plr.Data.Race.Value) == "Human" or tostring(plr.Data.Race.Value) == "Ghoul") then
					local v878 = GetConnectionEnemies({
						"Ancient Vampire",
						"Ancient Zombie"
					})

					if v878 then
						while true do
							wait()
							Attack.Kill(v878, _G.Complete_Trials)

							if _G.Complete_Trials == false then
								break
							elseif not v878.Parent or v878.Humanoid.Health <= 0 then
								break
							end
						end
					end
				end
			end)
		end
	end)
end

spawn(function()
	while task.wait(Sec) do
		pcall(function()
			if _G.Defeating then
				for _, child in pairs(workspace.Characters:GetChildren()) do
					if child.Name ~= plr.Name and child.Humanoid.Health > 0 and child:FindFirstChild("HumanoidRootPart") and child.Parent and (Root.Position - child.HumanoidRootPart.Position).Magnitude <= 250 then
						while true do
							task.wait()
							EquipWeapon(_G.SelectWeapon)
							_tp(child.HumanoidRootPart.CFrame * CFrame.new(0, 0, 15))
							sethiddenproperty(plr, "SimulationRadius", math.huge)

							if _G.Defeating == false then
								break
							elseif child.Humanoid.Health <= 0 or not child.Parent or not child:FindFirstChild("HumanoidRootPart") or not child:FindFirstChild("Humanoid") then
								break
							end
						end
					end
				end
			end
		end)
	end
end)
printBeltName = function(p86)
	if type(p86) == "table" and p86.Quest.BeltName then
		return p86.Quest.BeltName
	end
end
spawn(function()
	while wait(Sec) do
		if _G.Dojoo then
			local exitTo

			repeat
				pcall(function()
					local t25 = { {
						NPC = "Dojo Trainer",
						Command = "RequestQuest"
					} }
					local response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))
					local v884 = printBeltName(response)

					if debug == false and not response and not v884 then
						_tp(CFrame.new(5865.0234375, 1208.3154296875, 871.15185546875))
						debug = true
					elseif debug == true and (CFrame.new(5865.0234375, 1208.3154296875, 871.15185546875).Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 50 then
						if v884 == "White" then
							local v885 = GetConnectionEnemies("Skull Slayer")

							if v885 then
								while true do
									task.wait()
									Attack.Kill(v885, _G.Dojoo)
									response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

									if not response then
										break
									elseif not _G.Dojoo or not Attack.Alive(v885) then
										break
									end
								end
							else
								_tp(CFrame.new(-16759.58984375, 71.283767700195312, 1595.3399658203125))
							end
						elseif v884 == "Yellow" then
							while true do
								task.wait(1)
								_G.SeaBeast1 = true
								_G.TerrorShark = true
								_G.Shark = true
								_G.Piranha = true
								_G.MobCrew = true
								_G.FishBoat = true
								_G.SailBoats = true
								response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

								if not _G.Dojoo then
									break
								elseif not response then
									break
								end
							end

							_G.SeaBeast1 = false
							_G.TerrorShark = false
							_G.Shark = false
							_G.Piranha = false
							_G.MobCrew = false
							_G.FishBoat = false
							_G.SailBoats = false
						elseif v884 == "Green" then
							while true do
								task.wait(1)
								_G.SailBoats = true
								response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

								if not _G.Dojoo then
									break
								elseif not response then
									break
								end
							end

							_G.SailBoats = false
						elseif v884 == "Purple" then
							while true do
								task.wait(1)
								_G.FarmEliteHunt = true
								response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

								if not _G.Dojoo then
									break
								elseif not response then
									break
								end
							end

							_G.FarmEliteHunt = false
						elseif v884 == "Red" then
							while true do
								task.wait(1)
								_G.SailBoats = true
								_G.FishBoat = true
								response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

								if not _G.Dojoo then
									break
								elseif not response then
									break
								end
							end

							_G.SailBoats = false
							_G.FishBoat = false
						elseif v884 == "Black" then
							repeat
								task.wait(1)

								local PrehistoricIsland = workspace.Map:FindFirstChild("PrehistoricIsland")
								local Core_, ActivationPrompt

								if PrehistoricIsland then
									_G.Prehis_Find = true

									if PrehistoricIsland and PrehistoricIsland:FindFirstChild("Core") then
										Core_ = PrehistoricIsland.Core

										if Core_:FindFirstChild("ActivationPrompt") then
											ActivationPrompt = PrehistoricIsland.Core.ActivationPrompt

											if ActivationPrompt:FindFirstChild("ProximityPrompt", true) then
												_G.Prehis_Skills = false
												_G.Prehis_Find = true
											else
												_G.Prehis_Skills = true
												_G.Prehis_Find = false
												response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

												if not _G.Dojoo or not response then
													break
												end
											end
										else
											_G.Prehis_Skills = true
											_G.Prehis_Find = false
											response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

											if not _G.Dojoo or not response then
												break
											end
										end
									else
										_G.Prehis_Skills = true
										_G.Prehis_Find = false
									end

									response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

									if not _G.Dojoo or not response then
										break
									end
								elseif workspace._WorldOrigin.Locations:FindFirstChild("Prehistoric Island") then
									_G.Prehis_Find = true

									if PrehistoricIsland and PrehistoricIsland:FindFirstChild("Core") then
										Core_ = PrehistoricIsland.Core

										if Core_:FindFirstChild("ActivationPrompt") then
											ActivationPrompt = PrehistoricIsland.Core.ActivationPrompt

											if ActivationPrompt:FindFirstChild("ProximityPrompt", true) then
												_G.Prehis_Skills = false
												_G.Prehis_Find = true
											else
												_G.Prehis_Skills = true
												_G.Prehis_Find = false
												response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

												if not _G.Dojoo or not response then
													break
												end
											end
										else
											_G.Prehis_Skills = true
											_G.Prehis_Find = false
											response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))

											if not _G.Dojoo or not response then
												break
											end
										end
									else
										_G.Prehis_Skills = true
										_G.Prehis_Find = false
									end
								else
									_G.Prehis_Find = true
									_G.Prehis_Skills = false
								end

								response = replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack(t25))
							until not _G.Dojoo or not response

							_G.Prehis_Find = PrehisUser.Find
							_G.Prehis_Skills = PrehisUser.Skills
						elseif v884 == "Orange" or v884 == "Blue" then
							return nil
						end
					end

					if not response then
						debug = false
						replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack({ {
							NPC = "Dojo Trainer",
							Command = "ClaimQuest"
						} }))
					end
				end)
				exitTo = nil

				while wait(Sec) do
					if _G.Dojoo then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)

do
	checkQuesta = function()
		local t26 = { {
			Context = "Check"
		} }
		local response

		pcall(function()
			game:GetService("ReplicatedStorage"):WaitForChild("Modules"):WaitForChild("Net"):WaitForChild("RF/DragonHunter"):InvokeServer(unpack({ {
				Context = "RequestQuest"
			} }))
		end)

		local _ = pcall(function()
			response = game:GetService("ReplicatedStorage"):WaitForChild("Modules"):WaitForChild("Net"):WaitForChild("RF/DragonHunter"):InvokeServer(unpack(t26))
		end)
		local v893 = false
		local v894
		local v895
		local n5

		if response then
			if response.Text then
				v893 = true

				local Text = response.Text

				if string.find(tostring(Text), "Defeat") then
					n5 = 1
					v894 = tonumber(string.sub(tostring(Text), 8, 9))

					for _, v in pairs({
						"Hydra Enforcer",
						"Venomous Assailant"
					}) do
						if string.find(Text, v) then
							v895 = v

							break
						end
					end
				elseif string.find(tostring(Text), "Destroy") then
					v894 = 10
					n5 = 2
					v895 = nil
				end
			end
		end

		return v893, v895, v894, n5
	end
end

BackTODoJo = function()
	for _, child in pairs(game:GetService("Players").LocalPlayer.PlayerGui.Notifications:GetChildren()) do
		if child.Name == "NotificationTemplate" and string.find(child.Text, "Head back to the Dojo to complete more tasks") then
			return true
		end
	end

	return false
end

do
	DragonMobClear = function(p87, p88, p89)
		if workspace.Enemies:FindFirstChild(p88) then
			for _, child in pairs(workspace.Enemies:GetChildren()) do
				if child.Name == p88 and Attack.Alive(child) then
					if p87 then
						Attack.Kill(child, p87)
					end
				end
			end
		else
			_tp(p89)
		end
	end
end

GetQuestDracoLevel = function()
	return replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack({ {
		NPC = "Dragon Wizard",
		Command = "Upgrade"
	} }))
end
spawn(function()
	while wait() do
		if _G.FarmBlazeEM then
			pcall(function()
				local v904, v905, _, v907 = checkQuesta()

				if v904 ~= true or BackTODoJo() then
					_tp(CFrame.new(5813, 1208, 884))
					DragonMobClear(false, nil, nil)
				elseif v907 ~= 1 then
					if v907 == 2 then
						if workspace.Map.Waterfall.IslandModel:FindFirstChild("Meshes/bambootree", true) then
							repeat
								wait()
								spawn(function()
									_tp(workspace.Map.Waterfall.IslandModel:FindFirstChild("Meshes/bambootree", true).CFrame * CFrame.new(4, 0, 0))
								end)

								if (workspace.Map.Waterfall.IslandModel:FindFirstChild("Meshes/bambootree", true).Position - Root.Position).Magnitude <= 200 then
									MousePos = workspace.Map.Waterfall.IslandModel:FindFirstChild("Meshes/bambootree", true).Position
									Useskills("Melee", "Z")
									Useskills("Melee", "X")
									Useskills("Melee", "C")
									wait(0.5)
									Useskills("Sword", "Z")
									Useskills("Sword", "X")
									wait(0.5)
									Useskills("Blox Fruit", "Z")
									Useskills("Blox Fruit", "X")
									Useskills("Blox Fruit", "C")
									wait(0.5)
									Useskills("Gun", "Z")
									Useskills("Gun", "X")
								end
							until not _G.FarmBlazeEM or BackTODoJo()
						end
					end
				elseif v905 == "Hydra Enforcer" or v905 == "Venomous Assailant" then
					while true do
						wait()
						DragonMobClear(true, v905, CFrame.new(4620.61572265625, 1002.2954711914062, 399.08688354492188))

						if not _G.FarmBlazeEM then
							break
						elseif BackTODoJo() then
							break
						end
					end
				end
			end)
		end
	end
end)
spawn(function()
	while wait(0.1) do
		if _G.FarmBlazeEM then
			pcall(function()
				if workspace.EmberTemplate:FindFirstChild("Part") then
					game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame = workspace.EmberTemplate.Part.CFrame
				end
			end)
		end
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.UPGDrago then
				if GetQuestDracoLevel() == false then
					return nil
				end

				if GetQuestDracoLevel() == true then
					if (CFrame.new(5814.42724609375, 1208.3267822265625, 884.57855224609375).Position - Root.Position).Magnitude >= 300 then
						_tp(CFrame.new(5814.42724609375, 1208.3267822265625, 884.57855224609375))
					else
						_tp(CFrame.new(5814.42724609375, 1208.3267822265625, 884.57855224609375))
						replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack({ {
							NPC = "Dragon Wizard",
							Command = "Upgrade"
						} }))
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.DragoV1 and GetM("Dragon Egg") <= 0 then
				while true do
					wait()
					_G.Prehis_Find = true
					_G.Prehis_Skills = true
					_G.Prehis_DE = true

					if not _G.DragoV1 then
						break
					elseif GetM("Dragon Egg") >= 1 then
						break
					end
				end

				_G.Prehis_Find = PrehisUser.Find
				_G.Prehis_Skills = PrehisUser.Skills
				_G.Prehis_DE = PrehisUser.DE
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.AutoFireFlowers then
			local FireFlowers = workspace:FindFirstChild("FireFlowers")
			local v909 = GetConnectionEnemies("Forest Pirate")

			if v909 then
				while true do
					wait()
					Attack.Kill(v909, _G.AutoFireFlowers)

					if not _G.AutoFireFlowers then
						break
					elseif not v909.Parent or v909.Humanoid.Health <= 0 or FireFlowers then
						break
					end
				end
			else
				_tp(CFrame.new(-13206.452148438, 425.89199829102, -7964.5537109375))
			end

			if FireFlowers then
				for _, child in pairs(FireFlowers:GetChildren()) do
					if child:IsA("Model") and child.PrimaryPart then
						local Position = child.PrimaryPart.Position

						if (Position - game.Players.LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 100 then
							vim1:SendKeyEvent(true, "E", false, game)
							wait(1.5)
							vim1:SendKeyEvent(false, "E", false, game)
						else
							_tp(CFrame.new(Position))
						end
					end
				end
			end
		end
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.DragoV3 then
				repeat
					wait()
					_G.DangerSc = "Lv Infinite"
					_G.SailBoats = true
					_G.TerrorShark = true
				until not _G.DragoV3

				_G.DangerSc = "Lv 1"
				_G.SailBoats = false
				_G.TerrorShark = false
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.Relic123 then
			pcall(function()
				if workspace.Map:FindFirstChild("DracoTrial") then
					replicated.Remotes.DracoTrial:InvokeServer()
					wait(0.5)

					while true do
						wait()
						_tp(CFrame.new(-39934.9765625, 10685.359375, 22999.34375))

						if not _G.Relic123 then
							break
						elseif Root.Position == CFrame.new(-39934.9765625, 10685.359375, 22999.34375).Position then
							break
						end
					end

					while true do
						wait()
						_tp(CFrame.new(-40511.25390625, 9376.4013671875, 23458.37890625))

						if not _G.Relic123 then
							break
						elseif Root.Position == CFrame.new(-40511.25390625, 9376.4013671875, 23458.37890625).Position then
							break
						end
					end

					wait(2.5)

					while true do
						wait()
						_tp(CFrame.new(-39914.65625, 10685.384765625, 23000.177734375))

						if not _G.Relic123 then
							break
						elseif Root.Position == CFrame.new(-39914.65625, 10685.384765625, 23000.177734375).Position then
							break
						end
					end

					while true do
						wait()
						_tp(CFrame.new(-40045.83203125, 9376.3984375, 22791.287109375))

						if not _G.Relic123 then
							break
						elseif Root.Position == CFrame.new(-40045.83203125, 9376.3984375, 22791.287109375).Position then
							break
						end
					end

					wait(2.5)

					while true do
						wait()
						_tp(CFrame.new(-39908.5, 10685.4052734375, 22990.04296875))

						if not _G.Relic123 then
							break
						elseif Root.Position == CFrame.new(-39908.5, 10685.4052734375, 22990.04296875).Position then
							break
						end
					end

					while true do
						wait()
						_tp(CFrame.new(-39609.5, 9376.400390625, 23472.94335975))

						if not _G.Relic123 then
							break
						elseif Root.Position == CFrame.new(-39609.5, 9376.400390625, 23472.94335975).Position then
							break
						end
					end
				else
					local TrialTeleport = workspace.Map.PrehistoricIsland:FindFirstChild("TrialTeleport")

					if TrialTeleport and TrialTeleport:IsA("Part") then
						_tp(CFrame.new(TrialTeleport.Position))
					end
				end
			end)
		end
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.TrainDrago then
				local t27 = {
					"Venomous Assailant",
					"Hydra Enforcer"
				}

				for i = 1, #t27 do
					if plr.Character:FindFirstChild("RaceEnergy").Value == 1 then
						vim1:SendKeyEvent(true, "Y", false, game)
						replicated.Remotes.CommF_:InvokeServer("UpgradeRace", "Buy", 2)
						_tp(CFrame.new(4620.61572265625, 1002.2954711914062, 399.08688354492188))
					elseif plr.Character:FindFirstChild("RaceTransformed").Value == false then
						local v916 = GetConnectionEnemies(t27)

						if v916 then
							while true do
								wait()
								Attack.Kill(v916, _G.TrainDrago)

								if _G.TrainDrago == false then
									break
								elseif v916.Humanoid.Health <= 0 or not v916.Parent then
									break
								end
							end
						else
							_tp(CFrame.new(4620.61572265625, 1002.2954711914062, 399.08688354492188))
						end
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.TpDrago_Prehis then
			local TrialTeleport = workspace.Map.PrehistoricIsland:FindFirstChild("TrialTeleport")

			if TrialTeleport and TrialTeleport:IsA("Part") then
				_tp(CFrame.new(TrialTeleport.Position))
			end
		end
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.BuyDrago then
			pcall(function()
				if (CFrame.new(5814.42724609375, 1208.3267822265625, 884.57855224609375).Position - Root.Position).Magnitude >= 300 then
					_tp(CFrame.new(5814.42724609375, 1208.3267822265625, 884.57855224609375))
				else
					_tp(CFrame.new(5814.42724609375, 1208.3267822265625, 884.57855224609375))
					replicated.Modules.Net:FindFirstChild("RF/InteractDragonQuest"):InvokeServer(unpack({ {
						NPC = "Dragon Wizard",
						Command = "DragonRace"
					} }))
				end
			end)
		end
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.DT_Uzoth then
			local cFrame3 = CFrame.new(5661.89014, 1211.31909, 864.836731, 0.811413169, -1.36805838e-08, -0.584473014, 4.75227395e-08, 1, 4.25682458e-08, 0.584473014, -6.23161966e-08, 0.811413169)

			_tp(cFrame3)

			if (cFrame3.Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 25 then
				replicated.Modules.Net["RF/InteractDragonQuest"]:InvokeServer({
					NPC = "Uzoth",
					Command = "Upgrade"
				})
			end
		end
	end
end)
task.spawn(function()
	local rfCraft = game:GetService("ReplicatedStorage").Modules.Net["RF/Craft"]

	while task.wait(0.3) do
		if getgenv().AutoCraftVolcanic then
			pcall(function()
				rfCraft:InvokeServer("PossibleHardcode", "Volcanic Magnet")
			end)
			getgenv().AutoCraftVolcanic = false
		end
	end
end)
spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Prehis_Find then
				local Character = plr.Character

				if not Character then
					return
				end

				local HumanoidRootPart = Character:FindFirstChild("HumanoidRootPart")
				local Humanoid = Character:FindFirstChild("Humanoid")

				if not HumanoidRootPart or not Humanoid or Humanoid.Health <= 0 then
					return
				end

				local PrehistoricIsland = workspace._WorldOrigin.Locations:FindFirstChild("Prehistoric Island", true)

				if PrehistoricIsland then
					local HeadTeleport = PrehistoricIsland:FindFirstChild("HeadTeleport", true) or PrehistoricIsland:FindFirstChild("Teleport_Head", true) or PrehistoricIsland:FindFirstChild("Head", true)

					if HeadTeleport then
						local CFrame_ = HeadTeleport.CFrame
						local v926 = CFrame_.Position - CFrame_.LookVector * 40 + Vector3.new(0, 20, 0)

						if (v926 - HumanoidRootPart.Position).Magnitude > 30 then
							_tp(CFrame.new(v926))
						end
					else
						local Position = PrehistoricIsland.CFrame.Position

						_tp(CFrame.new(Position - (Position - HumanoidRootPart.Position).Unit * 250 + Vector3.new(0, 60, 0)))
					end
				else
					local v928 = CheckBoat()

					if not v928 then
						local cFrame3 = CFrame.new(-16927.451, 9.086, 433.864)

						TeleportToTarget(cFrame3)

						if (cFrame3.Position - HumanoidRootPart.Position).Magnitude <= 10 then
							replicated.Remotes.CommF_:InvokeServer("BuyBoat", _G.SelectedBoat or "Guardian")
						end

						return
					end

					if Humanoid.Sit == false then
						_tp(v928.VehicleSeat.CFrame * CFrame.new(0, 1, 0))

						return
					end

					local cFrame3 = CFrame.new(-10000000, 31, 37016.25)

					targetDestination = cFrame3

					if CheckEnemiesBoat() or CheckTerrorShark() or CheckPirateGrandBrigade() then
						_tp(CFrame.new(-10000000, 150, 37016.25))
					else
						_tp(cFrame3)
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait() do
		if _G.AutoStartPrehistoric then
			local exitTo

			repeat
				pcall(function()
					if workspace._WorldOrigin.Locations:FindFirstChild("Prehistoric Island", true) then
						local PrehistoricIsland = workspace.Map:FindFirstChild("PrehistoricIsland", true)

						if PrehistoricIsland and PrehistoricIsland:FindFirstChild("Core") then
							local ActivationPrompt = PrehistoricIsland.Core:FindFirstChild("ActivationPrompt", true)

							if ActivationPrompt and ActivationPrompt:FindFirstChild("ProximityPrompt") then
								if plr:DistanceFromCharacter(ActivationPrompt.CFrame.Position) <= 150 then
									fireproximityprompt(ActivationPrompt.ProximityPrompt, math.huge)
									vim1:SendKeyEvent(true, "E", false, game)
									wait(1.5)
									vim1:SendKeyEvent(false, "E", false, game)
								end

								_tp(ActivationPrompt.CFrame)
							end
						end
					end
				end)
				exitTo = nil

				while wait() do
					if _G.AutoStartPrehistoric then
						exitTo = 1

						break
					end
				end
			until exitTo ~= 1

			return
		end
	end
end)
spawn(function()
	while wait(0.3) do
		if _G.Prehis_Skills then
			pcall(function()
				local PrehistoricIsland = workspace.Map:FindFirstChild("PrehistoricIsland")

				if not PrehistoricIsland then
					return
				end

				for _, descendant in pairs(PrehistoricIsland:GetDescendants()) do
					if descendant:IsA("BasePart") or descendant:IsA("MeshPart") then
						if descendant.Name:lower():find("lava") then
							descendant:Destroy()
						end
					end
				end

				local Core_ = PrehistoricIsland:FindFirstChild("Core")

				if Core_ then
					local InteriorLava = Core_:FindFirstChild("InteriorLava")

					if InteriorLava then
						InteriorLava:Destroy()
					end
				end

				local TrialTeleport = PrehistoricIsland:FindFirstChild("TrialTeleport")

				for _, descendant in pairs(PrehistoricIsland:GetDescendants()) do
					if descendant.Name == "TouchInterest" and (not TrialTeleport or not descendant:IsDescendantOf(TrialTeleport)) then
						descendant.Parent:Destroy()
					end
				end
			end)
		end
	end
end)

do
	spawn(function()
		while wait(Sec) do
			if _G.Prehis_Skills then
				pcall(function()
					local v942 = GetConnectionEnemies("Lava Golem")

					if v942 and v942:FindFirstChild("Humanoid") then
						while true do
							wait(0.1)
							Attack.Kill(v942, true)
							v942.Humanoid:ChangeState(15)

							if not _G.Prehis_Skills then
								break
							elseif not v942.Parent or v942.Humanoid.Health <= 0 then
								break
							end
						end
					end
				end)
			end
		end
	end)
end

spawn(function()
	while wait(Sec) do
		if _G.Prehis_Skills then
			pcall(function()
				local PrehistoricIsland = workspace.Map:FindFirstChild("PrehistoricIsland")

				if not PrehistoricIsland then
					return
				end

				local Core_ = PrehistoricIsland:FindFirstChild("Core")

				if not Core_ then
					return
				end

				local VolcanoRocks = Core_:FindFirstChild("VolcanoRocks")

				if not VolcanoRocks then
					return
				end

				for _, child in pairs(VolcanoRocks:GetChildren()) do
					local VFXLayer = child:FindFirstChild("VFXLayer")
					local At0 = VFXLayer and VFXLayer:FindFirstChild("At0")
					local Glow = At0 and At0:FindFirstChild("Glow")

					if Glow and Glow.Enabled then
						repeat
							wait(0.1)
							_tp(VFXLayer.CFrame)

							if plr:DistanceFromCharacter(VFXLayer.CFrame.Position) <= 150 then
								MousePos = VFXLayer.CFrame.Position
								Useskills("Melee", "Z")
								wait(0.4)
								Useskills("Melee", "X")
								wait(0.4)
								Useskills("Melee", "C")
								wait(0.4)
								Useskills("Blox Fruit", "Z")
								wait(0.4)
								Useskills("Blox Fruit", "X")
								wait(0.4)
								Useskills("Blox Fruit", "C")
							end
						until not _G.Prehis_Skills or not Glow.Enabled
					end
				end
			end)
		end
	end
end)
spawn(function()
	while task.wait(Sec or 0.1) do
		if _G.KillAuraFull then
			pcall(function()
				local LocalPlayer2 = game.Players.LocalPlayer
				local Character = LocalPlayer2.Character
				local HumanoidRootPart = Character and Character:FindFirstChild("HumanoidRootPart")

				if not HumanoidRootPart then
					return
				end

				sethiddenproperty(LocalPlayer2, "SimulationRadius", math.huge)

				for _, child in pairs(workspace.Enemies:GetChildren()) do
					if child:FindFirstChild("Humanoid") and child:FindFirstChild("HumanoidRootPart") then
						local Magnitude = (child.HumanoidRootPart.Position - HumanoidRootPart.Position).Magnitude

						if Magnitude <= (Range or 100) and child.Humanoid.Health > 0 then
							child.Humanoid.Health = 0
							child.HumanoidRootPart.CanCollide = false
							child:BreakJoints()
						end
					end
				end
			end)
		end
	end
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.Prehis_DB then
					if workspace:FindFirstChild("DinoBone") then
						for _, child in pairs(workspace:GetChildren()) do
							if child.Name == "DinoBone" then
								_tp(child.CFrame)
							end
						end
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Prehis_DE then
				local PrehistoricIsland = workspace.Map:FindFirstChild("PrehistoricIsland")

				if PrehistoricIsland and PrehistoricIsland:FindFirstChild("Core") then
					if PrehistoricIsland.Core:FindFirstChild("SpawnedDragonEggs") then
						local DragonEgg = PrehistoricIsland.Core.SpawnedDragonEggs:FindFirstChild("DragonEgg")

						if DragonEgg and DragonEgg:FindFirstChild("Molten") then
							if DragonEgg.Molten:FindFirstChild("ProximityPrompt") then
								_tp(DragonEgg.Molten.CFrame)
								fireproximityprompt(DragonEgg.Molten.ProximityPrompt, 30)
							end
						end
					end
				end
			end
		end)
	end
end)

do
	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.ResetPH then
					local TrialTeleport = workspace.Map.PrehistoricIsland:FindFirstChild("TrialTeleport")

					if not TrialTeleport or not TrialTeleport:FindFirstChild("TouchInterest") then
						if workspace:FindFirstChild("DinoBone") then
							for _, child in pairs(workspace:GetChildren()) do
								if child.Name == "DinoBone" then
									_tp(child.CFrame)
								end
							end
						end
					elseif tick() - (getgenv().LastPHReset or 0) > 10 then
						getgenv().LastPHReset = tick()
						plr.Character.Humanoid.Health = 0
					end
				end
			end)
		end
	end)
end

ListSeaBoat = {
	"Guardian",
	"PirateGrandBrigade",
	"MarineGrandBrigade",
	"PirateBrigade",
	"MarineBrigade",
	"PirateSloop",
	"MarineSloop",
	"Beast Hunter"
}
ListSeaZone = {
	"Lv 1",
	"Lv 2",
	"Lv 3",
	"Lv 4",
	"Lv 5",
	"Lv 6",
	"Lv Infinite"
}
spawn(function()
	while wait() do
		pcall(function()
			if getgenv().AutoPressW then
				if game.Players.LocalPlayer.Character:WaitForChild("Humanoid").Sit == true then
					game:GetService("VirtualInputManager"):SendKeyEvent(true, "W", false, game)
				end
			end
		end)
	end
end)
spawn(function()
	while wait() do
		pcall(function()
			for _, child in pairs(game:GetService("Workspace").Boats:GetChildren()) do
				for _, descendant in pairs(child:GetDescendants()) do
					if descendant:IsA("BasePart") then
						if getgenv().NoClipShip or getgenv().FindPrehistoric then
							descendant.CanCollide = false
						else
							descendant.CanCollide = true
						end
					end
				end
			end
		end)
	end
end)

do
	spawn(function()
		while wait() do
			if _G.SailBoats then
				pcall(function()
					local v968 = CheckBoat()

					if not v968 and (not CheckShark() or not _G.Shark) and (not CheckTerrorShark() or not _G.TerrorShark) and (not CheckFishCrew() or not _G.MobCrew) and (not CheckPiranha() or not _G.Piranha) and (not CheckEnemiesBoat() or not _G.FishBoat) and (not CheckSeaBeast() or not _G.SeaBeast1) and (not _G.PGB or not CheckPirateGrandBrigade()) and (not _G.HCM or not CheckHauntedCrew()) and (not _G.Leviathan1 or not CheckLeviathan()) then
						local cFrame3 = CFrame.new(-16927.451, 9.086, 433.864)

						TeleportToTarget(cFrame3)

						if (cFrame3.Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
							replicated.Remotes.CommF_:InvokeServer("BuyBoat", _G.SelectedBoat)
						end
					elseif v968 and (not CheckShark() or not _G.Shark) and (not CheckTerrorShark() or not _G.TerrorShark) and (not CheckFishCrew() or not _G.MobCrew) then
						if (not CheckPiranha() or not _G.Piranha) and (not CheckEnemiesBoat() or not _G.FishBoat) and (not CheckSeaBeast() or not _G.SeaBeast1) and (not _G.PGB or not CheckPirateGrandBrigade()) and (not _G.HCM or not CheckHauntedCrew()) and (not _G.Leviathan1 or not CheckLeviathan()) then
							if plr.Character.Humanoid.Sit == false then
								_tp(v968.VehicleSeat.CFrame * CFrame.new(0, 1, 0))
							else
								if _G.DangerSc == "Lv 1" then
									CFrameSelectedZone = CFrame.new(-21998.375, 30.0006084, -682.309143)
								elseif _G.DangerSc == "Lv 2" then
									CFrameSelectedZone = CFrame.new(-26779.5215, 30.0005474, -822.858032)
								elseif _G.DangerSc == "Lv 3" then
									CFrameSelectedZone = CFrame.new(-31171.957, 30.0001011, -2256.93774)
								elseif _G.DangerSc == "Lv 4" then
									CFrameSelectedZone = CFrame.new(-34054.6875, 30.2187767, -2560.12012)
								elseif _G.DangerSc == "Lv 5" then
									CFrameSelectedZone = CFrame.new(-38887.5547, 30.0004578, -2162.99023)
								elseif _G.DangerSc == "Lv 6" then
									CFrameSelectedZone = CFrame.new(-44541.7617, 30.0003204, -1244.8584)
								elseif _G.DangerSc == "Lv Infinite" then
									CFrameSelectedZone = CFrame.new(-10000000, 31, 37016.25)
								end

								while true do
									wait()

									if not _G.FishBoat and CheckEnemiesBoat() or not _G.PGB and CheckPirateGrandBrigade() or not _G.TerrorShark and CheckTerrorShark() then
										_tp(CFrameSelectedZone * CFrame.new(0, 150, 0))
									else
										_tp(CFrameSelectedZone)
									end

									if _G.SailBoats ~= false and (not CheckShark() or not _G.Shark) and (not CheckTerrorShark() or not _G.TerrorShark) and (not CheckFishCrew() or not _G.MobCrew) and (not CheckPiranha() or not _G.Piranha) and (not CheckSeaBeast() or not _G.SeaBeast1) and (not CheckEnemiesBoat() or not _G.FishBoat) and (not _G.Leviathan1 or not CheckLeviathan()) and (not _G.HCM or not CheckHauntedCrew()) and (not _G.PGB or not CheckPirateGrandBrigade()) then
										if plr.Character:WaitForChild("Humanoid").Sit ~= false then
											continue
										end
									end

									break
								end

								plr.Character.Humanoid.Sit = false
							end
						end
					end
				end)
			end
		end
	end)
end

spawn(function()
	while wait(Sec) do
		pcall(function()
			for _, child in pairs(workspace.Boats:GetChildren()) do
				for _, descendant in pairs(workspace.Boats[child.Name]:GetDescendants()) do
					if descendant:IsA("BasePart") then
						if _G.SailBoats or _G.Prehis_Find or _G.FindMirage or _G.SailBoat_Hydra or _G.AutofindKitIs then
							descendant.CanCollide = false
						else
							descendant.CanCollide = true
						end
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait() do
		pcall(function()
			if _G.Shark then
				local t28 = { "Shark" }

				if CheckShark() then
					for _, child in pairs(workspace.Enemies:GetChildren()) do
						if table.find(t28, child.Name) and Attack.Alive(child) then
							while true do
								task.wait()
								Attack.Kill(child, _G.Shark)

								if _G.Shark == false then
									break
								elseif not child.Parent or child.Humanoid.Health <= 0 then
									break
								end
							end
						end
					end
				end
			end

			if _G.TerrorShark then
				local t29 = { "Terrorshark" }

				if CheckTerrorShark() then
					for _, child in pairs(workspace.Enemies:GetChildren()) do
						if table.find(t29, child.Name) and Attack.Alive(child) then
							while true do
								task.wait()
								Attack.KillSea(child, _G.TerrorShark)

								if _G.TerrorShark == false then
									break
								elseif not child.Parent or child.Humanoid.Health <= 0 then
									break
								end
							end
						end
					end
				end
			end

			if _G.Piranha then
				local t30 = { "Piranha" }

				if CheckPiranha() then
					for _, child in pairs(workspace.Enemies:GetChildren()) do
						if table.find(t30, child.Name) and Attack.Alive(child) then
							while true do
								task.wait()
								Attack.Kill(child, _G.Piranha)

								if _G.Piranha == false then
									break
								elseif not child.Parent or child.Humanoid.Health <= 0 then
									break
								end
							end
						end
					end
				end
			end

			if _G.MobCrew then
				local t31 = { "Fish Crew Member" }

				if CheckFishCrew() then
					for _, child in pairs(workspace.Enemies:GetChildren()) do
						if table.find(t31, child.Name) and Attack.Alive(child) then
							while true do
								task.wait()
								Attack.Kill(child, _G.MobCrew)

								if _G.MobCrew == false then
									break
								elseif not child.Parent or child.Humanoid.Health <= 0 then
									break
								end
							end
						end
					end
				end
			end

			if _G.HCM then
				local t32 = { "Haunted Crew Member" }

				if CheckHauntedCrew() then
					for _, child in pairs(workspace.Enemies:GetChildren()) do
						if table.find(t32, child.Name) and Attack.Alive(child) then
							while true do
								task.wait()
								Attack.Kill(child, _G.HCM)

								if _G.HCM == false then
									break
								elseif not child.Parent or child.Humanoid.Health <= 0 then
									break
								end
							end
						end
					end
				end
			end

			if _G.SeaBeast1 then
				if workspace.SeaBeasts:FindFirstChild("SeaBeast1") then
					for _, child in pairs(workspace.SeaBeasts:GetChildren()) do
						if child:FindFirstChild("HumanoidRootPart") and child:FindFirstChild("Health") and child.Health.Value > 0 then
							repeat
								task.wait()
								spawn(function()
									_tp(CFrame.new(child.HumanoidRootPart.Position.X, game:GetService("Workspace").Map["WaterBase-Plane"].Position.Y + 200, child.HumanoidRootPart.Position.Z))
								end)

								if plr:DistanceFromCharacter(child.HumanoidRootPart.CFrame.Position) <= 500 then
									AitSeaSkill_Custom = child.HumanoidRootPart.CFrame
									MousePos = AitSeaSkill_Custom.Position

									if CheckF() then
										weaponSc("Blox Fruit")
										Useskills("Blox Fruit", "Z")
										Useskills("Blox Fruit", "X")
										Useskills("Blox Fruit", "C")
									else
										Useskills("Melee", "Z")
										Useskills("Melee", "X")
										Useskills("Melee", "C")
										wait(0.1)
										Useskills("Sword", "Z")
										Useskills("Sword", "X")
										wait(0.1)
										Useskills("Blox Fruit", "Z")
										Useskills("Blox Fruit", "X")
										Useskills("Blox Fruit", "C")
										wait(0.1)
										Useskills("Gun", "Z")
										Useskills("Gun", "X")
									end
								end
							until _G.SeaBeast1 == false or not child:FindFirstChild("HumanoidRootPart") or not child.Parent or child.Health.Value <= 0
						end
					end
				end
			end

			if _G.Leviathan1 then
				if workspace.SeaBeasts:FindFirstChild("Leviathan") then
					for _, child in pairs(workspace.SeaBeasts:GetChildren()) do
						if child:FindFirstChild("HumanoidRootPart") and child:FindFirstChild("Leviathan Segment") and child:FindFirstChild("Health") and child.Health.Value > 0 then
							repeat
								task.wait()
								spawn(function()
									_tp(CFrame.new(child.HumanoidRootPart.Position.X, game:GetService("Workspace").Map["WaterBase-Plane"].Position.Y + 200, child.HumanoidRootPart.Position.Z))
								end)

								if plr:DistanceFromCharacter(child.HumanoidRootPart.CFrame.Position) <= 500 then
									MousePos = child:FindFirstChild("Leviathan Segment").Position

									if CheckF() then
										weaponSc("Blox Fruit")
										Useskills("Blox Fruit", "Z")
										Useskills("Blox Fruit", "X")
										Useskills("Blox Fruit", "C")
									else
										Useskills("Melee", "Z")
										Useskills("Melee", "X")
										Useskills("Melee", "C")
										wait(0.1)
										Useskills("Sword", "Z")
										Useskills("Sword", "X")
										wait(0.1)
										Useskills("Blox Fruit", "Z")
										Useskills("Blox Fruit", "X")
										Useskills("Blox Fruit", "C")
										wait(0.1)
										Useskills("Gun", "Z")
										Useskills("Gun", "X")
									end
								end
							until _G.Leviathan1 == false or not child:FindFirstChild("HumanoidRootPart") or not child.Parent or child.Health.Value <= 0
						end
					end
				end
			end

			if _G.FishBoat then
				if CheckEnemiesBoat() then
					for _, child in pairs(workspace.Enemies:GetChildren()) do
						if child:FindFirstChild("Health") and child.Health.Value > 0 and child:FindFirstChild("VehicleSeat") then
							repeat
								task.wait()
								spawn(function()
									if child.Name == "FishBoat" then
										_tp(child.Engine.CFrame * CFrame.new(0, -50, -25))
									end
								end)

								if plr:DistanceFromCharacter(child.Engine.CFrame.Position) <= 150 then
									AitSeaSkill_Custom = child.Engine.CFrame
									MousePos = AitSeaSkill_Custom.Position

									if CheckF() then
										weaponSc("Blox Fruit")
										Useskills("Blox Fruit", "Z")
										Useskills("Blox Fruit", "X")
										Useskills("Blox Fruit", "C")
									else
										Useskills("Melee", "Z")
										Useskills("Melee", "X")
										Useskills("Melee", "C")
										wait(0.1)
										Useskills("Sword", "Z")
										Useskills("Sword", "X")
										wait(0.1)
										Useskills("Blox Fruit", "Z")
										Useskills("Blox Fruit", "X")
										Useskills("Blox Fruit", "C")
										wait(0.1)
										Useskills("Gun", "Z")
										Useskills("Gun", "X")
									end
								end
							until _G.FishBoat == false or not child:FindFirstChild("VehicleSeat") or child.Health.Value <= 0
						end
					end
				end
			end

			if _G.PGB and CheckPirateGrandBrigade() then
				for _, child in pairs(workspace.Enemies:GetChildren()) do
					if child:FindFirstChild("Health") and child.Health.Value > 0 and child:FindFirstChild("VehicleSeat") then
						repeat
							task.wait()
							spawn(function()
								if child.Name == "PirateBrigade" then
									_tp(child.Engine.CFrame * CFrame.new(0, -30, -10))
								elseif child.Name == "PirateGrandBrigade" then
									_tp(child.Engine.CFrame * CFrame.new(0, -50, -50))
								end
							end)

							if plr:DistanceFromCharacter(child.Engine.CFrame.Position) <= 150 then
								AitSeaSkill_Custom = child.Engine.CFrame
								MousePos = AitSeaSkill_Custom.Position

								if CheckF() then
									weaponSc("Blox Fruit")
									Useskills("Blox Fruit", "Z")
									Useskills("Blox Fruit", "X")
									Useskills("Blox Fruit", "C")
								else
									Useskills("Melee", "Z")
									Useskills("Melee", "X")
									Useskills("Melee", "C")
									wait(0.1)
									Useskills("Sword", "Z")
									Useskills("Sword", "X")
									wait(0.1)
									Useskills("Blox Fruit", "Z")
									Useskills("Blox Fruit", "X")
									Useskills("Blox Fruit", "C")
									wait(0.1)
									Useskills("Gun", "Z")
									Useskills("Gun", "X")
								end
							end
						until _G.PGB == false or not child:FindFirstChild("VehicleSeat") or child.Health.Value <= 0
					end
				end
			end
		end)
	end
end)
spawn(function()
	while wait() do
		if _G.AutofindKitIs then
			pcall(function()
				if workspace._WorldOrigin.Locations:FindFirstChild("Kitsune Island", true) then
					_tp(workspace._WorldOrigin.Locations:FindFirstChild("Kitsune Island").CFrame * CFrame.new(0, 500, 0))
				else
					local v997 = CheckBoat()

					if not v997 then
						local cFrame3 = CFrame.new(-16927.451, 9.086, 433.864)

						TeleportToTarget(cFrame3)

						if (cFrame3.Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
							replicated.Remotes.CommF_:InvokeServer("BuyBoat", _G.SelectedBoat)
						end
					elseif plr.Character.Humanoid.Sit == false then
						_tp(v997.VehicleSeat.CFrame * CFrame.new(0, 1, 0))
					else
						local cFrame3 = CFrame.new(-10000000, 31, 37016.25)

						while true do
							wait()

							if CheckEnemiesBoat() or CheckTerrorShark() or CheckPirateGrandBrigade() then
								_tp(CFrame.new(-10000000, 150, 37016.25))
							else
								_tp(CFrame.new(-10000000, 31, 37016.25))
							end

							if _G.AutofindKitIs and not ((cFrame3.Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10) then
								if not workspace._WorldOrigin.Locations:FindFirstChild("Kitsune Island") and plr.Character.Humanoid.Sit ~= false then
									continue
								end
							end

							break
						end

						plr.Character.Humanoid.Sit = false
					end
				end
			end)
		end
	end
end)
spawn(function()
	while wait(0.1) do
		if _G.tweenShrine then
			pcall(function()
				local KitsuneIsland = workspace.Map:FindFirstChild("KitsuneIsland") or game.Workspace._WorldOrigin.Locations:FindFirstChild("Kitsune Island")
				local ShrineActive = KitsuneIsland:FindFirstChild("ShrineActive")

				if ShrineActive then
					local next_ = next
					local descendants, v1004 = ShrineActive:GetDescendants()

					for _, v in next_, descendants, v1004 do
						if v:IsA("BasePart") then
							if v.Name:find("NeonShrinePart") then
								replicated.Modules.Net:FindFirstChild("RE/TouchKitsuneStatue"):FireServer()

								while true do
									wait()
									_tp(v.CFrame * CFrame.new(0, 2, 0))

									if _G.tweenShrine == false then
										break
									elseif not KitsuneIsland then
										break
									end
								end
							end
						end
					end
				else
					_tp(workspace._WorldOrigin.Locations:FindFirstChild("Kitsune Island").CFrame * CFrame.new(0, 500, 0))
				end
			end)
		end
	end
end)
spawn(function()
	while wait(0.1) do
		if _G.Collect_Ember then
			pcall(function()
				if workspace:WaitForChild("AttachedAzureEmber") then
					notween(workspace:WaitForChild("EmberTemplate"):FindFirstChild("Part").CFrame)

					return
				elseif workspace:WaitForChild("EmberTemplate") then
					notween(workspace:WaitForChild("EmberTemplate"):FindFirstChild("Part").CFrame)
				else
					_tp(workspace._WorldOrigin.Locations:FindFirstChild("Kitsune Island").CFrame * CFrame.new(0, 500, 0))
					replicated.Modules.Net["RF/KitsuneStatuePray"]:InvokeServer()
				end
			end)
		end
	end
end)
spawn(function()
	while wait(0.1) do
		if _G.Trade_Ember then
			pcall(function()
				if workspace._WorldOrigin.Locations:FindFirstChild("Kitsune Island", true) then
					replicated.Modules.Net:FindFirstChild("RF/KitsuneStatuePray"):InvokeServer()
				end
			end)
		end
	end
end)

do
	spawn(function()
		while wait(0.1) do
			if _G.FrozenTP then
				pcall(function()
					if workspace.Map:FindFirstChild("LeviathanGate") then
						_tp(workspace.Map.LeviathanGate.CFrame)
						replicated:WaitForChild("Remotes"):WaitForChild("CommF_"):InvokeServer("OpenLeviathanGate")
					end
				end)
			end
		end
	end)
end

spawn(function()
	while wait() do
		if _G.SailBoat_Hydra then
			pcall(function()
				local v1007 = CheckBoat()

				if not v1007 then
					local cFrame3 = CFrame.new(-16927.451, 9.086, 433.864)

					TeleportToTarget(cFrame3)

					if (cFrame3.Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 10 then
						replicated.Remotes.CommF_:InvokeServer("BuyBoat", _G.SelectedBoat)
					end
				elseif plr.Character.Humanoid.Sit == false then
					_tp(v1007.VehicleSeat.CFrame * CFrame.new(0, 1, 0))
				else
					wait()

					local exitTo, Character

					if CheckEnemiesBoat() or CheckPirateGrandBrigade() or CheckTerrorShark() then
						local exitTo2

						while true do
							_tp(CFrame.new(5433, 150, 290))

							if _G.SailBoat_Hydra ~= false then
								Character = plr.Character

								if Character:WaitForChild("Humanoid").Sit ~= false then
									wait()

									if not CheckEnemiesBoat() and not CheckPirateGrandBrigade() and not CheckTerrorShark() then
										exitTo2 = 1

										break
									end

									continue
								end
							end

							break
						end

						if exitTo2 == 1 then
							repeat
								_tp(CFrame.new(5433, 35, 290))
								exitTo = nil

								while _G.SailBoat_Hydra ~= false do
									Character = plr.Character

									if Character:WaitForChild("Humanoid").Sit == false then
										break
									end

									wait()

									if not CheckEnemiesBoat() and not CheckPirateGrandBrigade() and not CheckTerrorShark() then
										exitTo = 1

										break
									end

									_tp(CFrame.new(5433, 150, 290))
								end
							until exitTo ~= 1
						end
					else
						repeat
							_tp(CFrame.new(5433, 35, 290))
							exitTo = nil

							while _G.SailBoat_Hydra ~= false do
								Character = plr.Character

								if Character:WaitForChild("Humanoid").Sit == false then
									break
								end

								wait()

								if not CheckEnemiesBoat() and not CheckPirateGrandBrigade() and not CheckTerrorShark() then
									exitTo = 1

									break
								end

								_tp(CFrame.new(5433, 150, 290))
							end
						until exitTo ~= 1
					end

					plr.Character.Humanoid.Sit = false
				end
			end)
		end
	end
end)
isnil = function(p90)
	return p90 == nil
end
round = function(p91)
	return math.floor(tonumber(p91) + 0.5)
end
formatNumber = function(p92)
	local v1012 = tostring(p92)
	local v1013

	repeat
		local v1014

		v1014, v1013 = v1012:gsub("^(-?%d+)(%d%d%d)", "%1,%2")
		v1012 = v1014
	until v1013 == 0

	return v1012
end
getFruitStock = function()
	local s4 = "Advance Fruit Stock\n"
	local ok, result = pcall(function()
		return game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("GetFruits", true)
	end)

	if ok and result then
		local v1018 = false

		for _, v in pairs(result) do
			if v.OnSale then
				v1018 = true
				s4 ..= v.Name .. " - $" .. formatNumber(v.Price) .. "\n"
			end
		end

		if not v1018 then
			s4 ..= "- No fruit.\n"
		end
	else
		s4 ..= "- Error while retrieving data.\n"
	end

	local v1021 = s4 .. "\nNormal Fruit Stock\n"
	local ok2, result2 = pcall(function()
		return game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("GetFruits")
	end)

	if ok2 and result2 then
		local v1024 = false

		for _, v in pairs(result2) do
			if v.OnSale then
				v1024 = true
				v1021 ..= v.Name .. " - $" .. formatNumber(v.Price) .. "\n"
			end
		end

		if not v1024 then
			v1021 ..= "- No fruit.\n"
		end
	else
		v1021 ..= "- Error while retrieving data.\n"
	end

	return v1021
end
spawn(function()
	while wait(5) do
		pcall(function()
			if not _G.Random_Auto then
				return
			end

			local SpinnerWindow = plr.PlayerGui:FindFirstChild("SpinnerWindow")

			if SpinnerWindow then
				local CloseButton = SpinnerWindow:FindFirstChild("AboveSpinner") and SpinnerWindow.AboveSpinner:FindFirstChild("Navigation") and SpinnerWindow.AboveSpinner.Navigation:FindFirstChild("CloseButton")

				if CloseButton and CloseButton.Visible then
					pcall(function()
						for _, v in pairs(getconnections(CloseButton.Activated)) do
							if v.Function then
								v.Function()
							elseif v.Fire then
								v:Fire()
							end
						end
					end)
				end
			end

			if plr.Data.Level.Value < 50 then
				return
			end

			if RandomFruitCooldown and tick() < RandomFruitCooldown then
				return
			end

			local GachaClient = require(replicated.Controllers.GachaClient)
			local ok, result, result2 = pcall(function()
				return GachaClient.PurchaseGachaAsync("ZiolesGacha")
			end)

			if ok and type(result2) == "table" then
				if result2.Cooldown and result2.Cooldown.TimeEnds then
					local v1035 = result2.Cooldown.TimeEnds - os.time()

					if v1035 > 0 then
						RandomFruitCooldown = tick() + v1035

						return
					end
				end

				if result2.RequirementsMet == false then
					RandomFruitCooldown = tick() + 600

					return
				end

				if result == true then
					RandomFruitCooldown = tick() + 7200
				end
			end
		end)
	end
end)

do
	spawn(function()
		while wait(Sec) do
			if _G.DropFruit then
				pcall(function()
					DropFruits()
				end)
			end
		end
	end)
end

spawn(function()
	while wait(Sec) do
		if _G.StoreF then
			pcall(function()
				UpdStFruit()
			end)
		end
	end
end)

do
	spawn(function()
		while wait(Sec) do
			if _G.TwFruits then
				pcall(function()
					local v1036 = GetNearestFruit()

					if v1036 then
						_tp(v1036.CFrame)
					end
				end)
			end
		end
	end)
end

spawn(function()
	while wait(Sec) do
		if _G.InstanceF then
			pcall(function()
				collectFruits(_G.InstanceF)
			end)
		end
	end
end)

do
	spawn(function()
		pcall(function()
			while wait() do
				if getgenv().AutoBuyFruitSniper then
					game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("GetFruits")
					game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("PurchaseRawFruit", getgenv().SelectFruit)
				end
			end
		end)
	end)
end

spawn(function()
	while wait() do
		pcall(function()
			if getgenv().AutoGetFruit then
				for _, v in ipairs({
					"Rocket-Rocket",
					"Spin-Spin",
					"Chop-Chop",
					"Spring-Spring",
					"Bomb-Bomb",
					"Smoke-Smoke",
					"Spike-Spike",
					"Flame-Flame",
					"Falcon-Falcon",
					"Ice-Ice",
					"Sand-Sand",
					"Dark-Dark",
					"Ghost-Ghost",
					"Diamond-Diamond",
					"Light-Light",
					"Rubber-Rubber",
					"Barrier-Barrier"
				}) do
					game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer(unpack({
						"LoadFruit",
						v
					}))
				end
			end
		end)
	end
end)

do
	task.spawn(function()
		while task.wait(1) do
			if _G.AutoChipBeli then
				pcall(function()
					if not GetBP("Special Microchip") then
						replicated.Remotes.CommF_:InvokeServer("RaidsNpc", "Select", _G.SelectChip)
					end
				end)
			end
		end
	end)
end

task.spawn(function()
	while task.wait(1) do
		if _G.AutoChipFruit then
			pcall(function()
				if not GetBP("Special Microchip") then
					local response = replicated.Remotes.CommF_:InvokeServer("GetFruits")
					local Name

					for _, v in pairs(response) do
						if v.Price <= 490000 then
							Name = v.Name

							break
						end
					end

					if Name then
						replicated.Remotes.CommF_:InvokeServer("LoadFruit", tostring(Name))
						replicated.Remotes.CommF_:InvokeServer("RaidsNpc", "Select", _G.SelectChip)
					end
				end
			end)
		end
	end
end)
IsRaidActive = function()
	local ok, result = pcall(function()
		if plr.PlayerGui.Main.TopHUDList.RaidTimer.Visible then
			return true
		end

		local attribute = plr:GetAttribute("IslandRaiding")

		return attribute ~= nil and attribute ~= false and attribute ~= ""
	end)
	local v1046 = ok and result == true

	return v1046
end
task.spawn(function()
	local n6 = 0

	while task.wait(0.5) do
		if _G.Auto_StartRaid then
			pcall(function()
				if IsRaidActive() or tick() - n6 < 25 then
					return
				end

				if not GetBP("Special Microchip") then
					return
				end

				local cFrame3

				if World2 then
					cFrame3 = CFrame.new(-6438.73535, 250.645355, -4501.50684)
				elseif World3 then
					cFrame3 = CFrame.new(-5046, 314, -2960)
				end

				if not cFrame3 then
					return
				end

				local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")

				if not HumanoidRootPart then
					return
				end

				if (HumanoidRootPart.Position - cFrame3.Position).Magnitude > 30 then
					_tp(cFrame3)

					return
				end

				if World2 then
					fireclickdetector(workspace.Map.CircleIsland.RaidSummon2.Button.Main.ClickDetector)
				else
					local Main = workspace.Map["Boat Castle"].RaidSummon2.Button.Main

					if Main and Main:FindFirstChild("ClickDetector") then
						fireclickdetector(Main.ClickDetector)
					end
				end

				n6 = tick()
			end)
		end
	end
end)
spawn(function()
	local Locations = workspace._WorldOrigin.Locations
	local n7 = 1
	local u1053 = false
	local n8 = 0
	local Position

	findIsland = function(p93, p94)
		local v1056
		local v1057

		for _, child in ipairs(Locations:GetChildren()) do
			if child.Name == "Island " .. p93 then
				local Magnitude = (child.Position - p94).Magnitude

				if not v1057 or Magnitude < v1057 then
					v1056 = child
					v1057 = Magnitude
				end
			end
		end

		return v1056
	end

	while task.wait(0.3) do
		if _G.Raiding then
			local exitTo

			repeat
				pcall(function()
					if not IsRaidActive() then
						u1053 = false
						Position = nil
						n8 = 0

						return
					end

					local HumanoidRootPart = plr.Character and plr.Character:FindFirstChild("HumanoidRootPart")
					local Humanoid = plr.Character and plr.Character:FindFirstChildOfClass("Humanoid")

					if not HumanoidRootPart or not Humanoid or Humanoid.Health <= 0 then
						return
					end

					if Humanoid.Sit or Humanoid.PlatformStand or HumanoidRootPart.Anchored then
						return
					end

					if not u1053 then
						u1053 = true
						Position = nil
						n8 = 0
						n7 = 1

						local n9 = 1500

						for i = 1, 5 do
							local v1066 = findIsland(i, HumanoidRootPart.Position)

							if v1066 then
								local Magnitude = (HumanoidRootPart.Position - v1066.Position).Magnitude

								if Magnitude < n9 then
									n9 = Magnitude
									n7 = i
								end
							end
						end
					end

					local v1068 = findIsland(n7, Position or HumanoidRootPart.Position)

					if not v1068 then
						return
					end

					if not Position and (HumanoidRootPart.Position - v1068.Position).Magnitude <= 600 then
						Position = v1068.Position
					end

					if _G.KillAuraRaid and (n7 == 4 or n7 == 5) then
						sethiddenproperty(plr, "SimulationRadius", math.huge)

						for _, child in ipairs(workspace.Enemies:GetChildren()) do
							if child:FindFirstChild("Humanoid") and child:FindFirstChild("HumanoidRootPart") and (child.HumanoidRootPart.Position - HumanoidRootPart.Position).Magnitude <= 500 and child.Humanoid.Health > 0 then
								child.Humanoid.Health = 0
								child.HumanoidRootPart.CanCollide = false
								child:BreakJoints()
							end
						end
					end

					if (HumanoidRootPart.Position - v1068.Position).Magnitude > 600 then
						n8 = 0
						_tp(v1068.CFrame * CFrame.new(0, 60, 0))

						return
					end

					local v1071 = false

					for _, child in ipairs(workspace.Enemies:GetChildren()) do
						local Humanoid2 = child:FindFirstChild("Humanoid")
						local HumanoidRootPart2 = child:FindFirstChild("HumanoidRootPart")

						if not Humanoid2 or not HumanoidRootPart2 or not (Humanoid2.Health > 0) or not ((HumanoidRootPart2.Position - v1068.Position).Magnitude < 800) then
							continue
						end

						v1071 = true

						local v1076 = tick() + 25

						while true do
							task.wait()
							Attack.Kill(child, _G.Raiding)

							if not _G.Raiding then
								break
							elseif not child.Parent or Humanoid2.Health <= 0 or not IsRaidActive() or v1076 < tick() then
								break
							end
						end

						if not _G.Raiding or not IsRaidActive() then
							return
						end
					end

					if v1071 then
						n8 = 0
					else
						n8 += 1

						if n8 > 15 then
							local v1077 = findIsland(n7 + 1, Position or v1068.Position)

							if v1077 then
								n7 += 1
								n8 = 0
								_tp(v1077.CFrame * CFrame.new(0, 60, 0))
							else
								_tp(v1068.CFrame * CFrame.new(0, 60, 0))
							end
						end
					end
				end)
				exitTo = nil

				while task.wait(0.3) do
					if _G.Raiding then
						exitTo = 1

						break
					else
						u1053 = false
						Position = nil
					end
				end
			until exitTo ~= 1

			return
		else
			u1053 = false
			Position = nil
		end
	end
end)

do
	spawn(function()
		while task.wait() do
			if _G.TpPly and _G.PlayersList then
				pcall(function()
					local _GPlayersList = game:GetService("Players"):FindFirstChild(_G.PlayersList)

					if _GPlayersList and _GPlayersList.Character then
						if _GPlayersList.Character:FindFirstChild("HumanoidRootPart") then
							_tp(_GPlayersList.Character.HumanoidRootPart.CFrame)
						end
					end
				end)
			end
		end
	end)
end

do
	spawn(function()
		while task.wait(0.1) do
			if SpectatePlys and _G.PlayersList then
				pcall(function()
					local _GPlayersList = game:GetService("Players"):FindFirstChild(_G.PlayersList)

					if _GPlayersList and _GPlayersList.Character then
						if _GPlayersList.Character:FindFirstChild("Humanoid") then
							workspace.Camera.CameraSubject = _GPlayersList.Character.Humanoid
						end
					end
				end)
			end
		end
	end)
end

ListServers = function(p95)
	local HttpService = game:GetService("HttpService")
	local v1081 = "https://games.roblox.com/v1/games/" .. tostring(game.PlaceId) .. "/servers/Public?sortOrder=Asc&limit=100" .. (p95 and "&cursor=" .. p95 or "")
	local ok, result = pcall(function()
		return game:HttpGet(v1081)
	end)

	if ok and result then
		local ok2, result2 = pcall(function()
			return HttpService:JSONDecode(result)
		end)

		if ok2 then
			return result2
		end
	end

	return {
		data = {}
	}
end
fetchServersData = function(p96, p97)
	local v1086 = string.format("https://games.roblox.com/v1/games/%d/servers/Public?limit=%d", p96, p97 or 100)
	local ok, result = pcall(function()
		return game:GetService("HttpService"):JSONDecode(game:HttpGet(v1086))
	end)

	if not ok or not result or not result.data then
		return nil
	end

	return result.data
end
IsEntityAlive = function(p98)
	if not p98 then
		return false
	end

	local Humanoid = p98:FindFirstChild("Humanoid")

	return Humanoid and Humanoid.Health > 0
end
GetEnemiesInRange = function(p99, p100)
	local t33 = {}
	local Position = p99:GetPivot().Position
	local players = game:GetService("Players"):GetPlayers()
	local children = game:GetService("Workspace").Enemies:GetChildren()

	for _, child in ipairs(children) do
		local HumanoidRootPart = child:FindFirstChild("HumanoidRootPart")

		if HumanoidRootPart and IsEntityAlive(child) and (HumanoidRootPart.Position - Position).Magnitude <= p100 then
			table.insert(t33, child)
		end
	end

	for _, player in ipairs(players) do
		if player ~= plr and player.Character then
			local HumanoidRootPart = player.Character:FindFirstChild("HumanoidRootPart")

			if HumanoidRootPart and IsEntityAlive(player.Character) then
				if (HumanoidRootPart.Position - Position).Magnitude <= p100 then
					table.insert(t33, player.Character)
				end
			end
		end
	end

	return t33
end
AttackNoCoolDown = function()
	if not plr.Character then
		return
	end

	local v1100
	local v1101, v1102, v1103 = ipairs(plr.Character:GetChildren())
	local v1104 = geniter(v1101, v1102, v1103)

	while true do
		local v1105 = table.pack(v1104())

		if v1105[1] then
			local v1106 = v1105[3]

			if v1106:IsA("Tool") then
				v1100 = v1106

				break
			end
		else
			break
		end
	end

	if not v1100 then
		return
	end

	local v1107 = GetEnemiesInRange(plr.Character, 60)

	if #v1107 == 0 then
		return
	end

	local ReplicatedStorage2 = game:GetService("ReplicatedStorage")
	local Modules = ReplicatedStorage2:FindFirstChild("Modules")

	if not Modules then
		return
	end

	local RERegisterAttack = ReplicatedStorage2:WaitForChild("Modules"):WaitForChild("Net"):WaitForChild("RE/RegisterAttack")
	local RERegisterHit = ReplicatedStorage2:WaitForChild("Modules"):WaitForChild("Net"):WaitForChild("RE/RegisterHit")

	if not RERegisterAttack or not RERegisterHit then
		return
	end

	local t34 = {}
	local v1113
	local v1114, v1115, v1116 = ipairs(v1107)

	for _, v in v1114, v1115, v1116 do
		if not v:GetAttribute("IsBoat") then
			local t35 = {
				"RightLowerArm",
				"RightUpperArm",
				"LeftLowerArm",
				"LeftUpperArm",
				"RightHand",
				"LeftHand"
			}
			local PrimaryPart = v:FindFirstChild(t35[math.random(#t35)]) or v.PrimaryPart

			if PrimaryPart then
				table.insert(t34, {
					v,
					PrimaryPart
				})
				v1113 = PrimaryPart
			end
		end
	end

	if not v1113 then
		return
	end

	RERegisterAttack:FireServer(0)

	local PlayerScripts = plr:FindFirstChild("PlayerScripts")

	if not PlayerScripts then
		return
	end

	local LocalScript = PlayerScripts:FindFirstChildOfClass("LocalScript")

	while not LocalScript do
		PlayerScripts.ChildAdded:Wait()
		LocalScript = PlayerScripts:FindFirstChildOfClass("LocalScript")
	end

	local SendHitsToServer

	if getsenv then
		local ok, result = pcall(getsenv, LocalScript)

		if ok and result then
			SendHitsToServer = result._G.SendHitsToServer
		end
	end

	local ok, result = pcall(function()
		return require(Modules.Flags).COMBAT_REMOTE_THREAD or false
	end)

	if ok and result and SendHitsToServer then
		SendHitsToServer(v1113, t34)
	elseif ok and not result then
		RERegisterHit:FireServer(v1113, t34)
	end
end
CameraShakerR = require(game.ReplicatedStorage.Util.CameraShaker)
CameraShakerR:Stop()
get_Monster = function()
	for _, child in pairs(workspace.Enemies:GetChildren()) do
		local UpperTorso = child:FindFirstChild("UpperTorso") or child:FindFirstChild("Head")

		if child:FindFirstChild("HumanoidRootPart", true) and UpperTorso and (child.Head.Position - plr.Character.HumanoidRootPart.Position).Magnitude <= 50 then
			return true, UpperTorso.Position
		end
	end

	for _, child in pairs(workspace.SeaBeasts:GetChildren()) do
		if child:FindFirstChild("HumanoidRootPart") and child:FindFirstChild("Health") and child.Health.Value > 0 then
			return true, child.HumanoidRootPart.Position
		end
	end

	for _, child in pairs(workspace.Enemies:GetChildren()) do
		if child:FindFirstChild("Health") and child.Health.Value > 0 and child:FindFirstChild("VehicleSeat") then
			return true, child.Engine.Position
		end
	end
end
Actived = function()
	local Tool = game.Players.LocalPlayer.Character:FindFirstChildOfClass("Tool")
	local v1136, v1137 = getconnections(Tool.Activated)

	for _, v in next, v1136, v1137 do
		if typeof(v.Function) == "function" then
			getupvalues(v.Function)
		end
	end
end

do
	task.spawn(function()
		RunSer.Heartbeat:Connect(function()
			pcall(function()
				if not _G.Seriality then
					return
				end

				AttackNoCoolDown()

				local Tool = game.Players.LocalPlayer.Character:FindFirstChildOfClass("Tool")
				local ToolTip = Tool.ToolTip
				local v1142 = get_Monster()

				if ToolTip == "Blox Fruit" and v1142 then
					local LeftClickRemote = Tool:FindFirstChild("LeftClickRemote")

					if LeftClickRemote then
						Actived()
						LeftClickRemote:FireServer(Vector3.new(0.01, -500, 0.01), 1, true)
						LeftClickRemote:FireServer(false)
					end
				end
			end)
		end)
	end)
end

local Players2 = game:GetService("Players")
local RunService = game:GetService("RunService")
local ReplicatedStorage2 = game:GetService("ReplicatedStorage")
local Workspace = game:GetService("Workspace")
local LocalPlayer2 = Players2.LocalPlayer

if not LocalPlayer2.Character then
	LocalPlayer2.CharacterAdded:Wait()
end

SafeWaitForChild = function(p101, p102)
	local _, result = pcall(function()
		return p101:WaitForChild(p102)
	end)

	return result
end

local v1154 = SafeWaitForChild(Workspace, "Enemies")
local v1155 = SafeWaitForChild(Workspace, "Characters")
local v1156 = SafeWaitForChild(ReplicatedStorage2, "Modules")
local v1157 = SafeWaitForChild(v1156, "Net")
local t36 = {
	Rate = 2e-09,
	Enabled = true,
	IsAlive = function(p103)
		local Humanoid = p103:FindFirstChild("Humanoid")

		if Humanoid and Humanoid.Health > 0 then
			return true
		end

		return false
	end,
	GetNearbyTargets = function(p104, p105)
		local t38 = {}
		local Position = p104:GetPivot().Position
		local children = p105:GetChildren()

		for i = 1, #children do
			local v1163 = children[i]
			local Humanoid = v1163:FindFirstChild("Humanoid")
			local HumanoidRootPart = v1163:FindFirstChild("HumanoidRootPart")

			if Humanoid and HumanoidRootPart and Humanoid.Health > 0 and (HumanoidRootPart.Position - Position).Magnitude <= 60 then
				table.insert(t38, v1163)
			end
		end

		return t38
	end,
	GetTargetParts = function(p106)
		local t39 = {}

		for i = 1, #p106 do
			local v1168 = p106[i]
			local Head = v1168:FindFirstChild("Head") or v1168.PrimaryPart

			if Head then
				table.insert(t39, {
					v1168,
					Head
				})
			end
		end

		return t39
	end
}

t36.GetAllTargets = function(p107)
	local t40 = {}
	local v1171 = t36.GetNearbyTargets(p107, v1154)
	local v1172 = t36.GetNearbyTargets(p107, v1155)

	for i = 1, #v1171 do
		table.insert(t40, v1171[i])
	end

	for i = 1, #v1172 do
		table.insert(t40, v1172[i])
	end

	return t40
end
t36.ExecuteFastAttack = function()
	local Character = LocalPlayer2.Character

	if not Character then
		return
	end

	if not Character:FindFirstChildOfClass("Tool") then
		return
	end

	local v1176 = t36.GetAllTargets(Character)

	if #v1176 < 1 then
		return
	end

	local v1177 = t36.GetTargetParts(v1176)

	if #v1177 < 1 then
		return
	end

	local reRegisterHit = v1157["RE/RegisterHit"]

	v1157["RE/RegisterAttack"]:FireServer(t36.Rate)
	reRegisterHit:FireServer(v1177[1][2], v1177)
end

local u1179
local attribute

InitializeHitRegistration = function()
	for _, v in ipairs({
		ReplicatedStorage2.Util,
		ReplicatedStorage2.Common,
		ReplicatedStorage2.Remotes,
		ReplicatedStorage2.Assets,
		ReplicatedStorage2.FX
	}) do
		local children = v:GetChildren()

		for _, child in ipairs(children) do
			if child:IsA("RemoteEvent") and child:GetAttribute("Id") then
				u1179 = child
				attribute = child:GetAttribute("Id")
			end
		end

		v.ChildAdded:Connect(function(child)
			if child:IsA("RemoteEvent") and child:GetAttribute("Id") then
				u1179 = child
				attribute = child:GetAttribute("Id")
			end
		end)
	end
end
InitializeHitRegistration()

local t37 = {
	Execute = function()
		local Character = LocalPlayer2.Character

		if not Character then
			return
		end

		local HumanoidRootPart = Character:FindFirstChild("HumanoidRootPart")

		if not HumanoidRootPart then
			return
		end

		local t41 = {}

		ScanFolder = function(p108)
			local children = p108:GetChildren()

			for i = 1, #children do
				local v1191 = children[i]
				local Humanoid = v1191:FindFirstChild("Humanoid")
				local HumanoidRootPart2 = v1191:FindFirstChild("HumanoidRootPart")

				if Humanoid and HumanoidRootPart2 and Humanoid.Health > 0 and v1191 ~= Character and (HumanoidRootPart2.Position - HumanoidRootPart.Position).Magnitude <= 60 then
					local children2 = v1191:GetChildren()

					for _, v in ipairs(children2) do
						if v:IsA("BasePart") then
							table.insert(t41, {
								v1191,
								v
							})
						end
					end
				end
			end
		end
		ScanFolder(v1154)
		ScanFolder(v1155)

		local Tool = Character:FindFirstChildOfClass("Tool")

		if #t41 > 0 and Tool and (Tool:GetAttribute("WeaponType") == "Melee" or Tool:GetAttribute("WeaponType") == "Sword") then
			local response = v1156.Net.seed:InvokeServer()
			local reRegisterHit = v1157["RE/RegisterHit"]

			v1157["RE/RegisterAttack"]:FireServer()

			local Head = t41[1][1]:FindFirstChild("Head")

			if not Head then
				return
			end

			reRegisterHit:FireServer(Head, t41, {})

			if u1179 then
				local v1201 = math.floor(Workspace:GetServerTimeNow() / 10 % 10) + 1
				local RegisterHit = string.gsub("RE/RegisterHit", ".", function(p109)
					return string.char(bit32.bxor(string.byte(p109), v1201))
				end)
				local v1203 = bit32.bxor(attribute + 909090, response * 2)

				cloneref(u1179):FireServer(RegisterHit, v1203, Head, t41)
			end
		end
	end
}

DisableCameraShake = function()
	require(ReplicatedStorage2.Util.CameraShaker):Stop()
end
StartMainLoops = function()
	task.spawn(function()
		while task.wait(t36.Rate) do
			t36.ExecuteFastAttack()
		end
	end)
	RunService.Heartbeat:Connect(function()
		pcall(t37.Execute)
	end)
end
StartMainLoops()
task.spawn(function()
	while task.wait(Sec) do
		if _G.Level then
			pcall(function()
				local HumanoidRootPart = (plr.Character or plr.CharacterAdded:Wait()):WaitForChild("HumanoidRootPart")

				if not HumanoidRootPart then
					return
				end

				local Value = plr.Data.Level.Value
				local v1206 = IsInSubmergedIsland()

				GuiShown("Quest")
				QuestText()

				if World3 and Value >= 2600 and not v1206 then
					local cFrame3 = cFrame2 or CFrame.new(-16269.7041, 25.2288494, 1373.65955)

					if (HumanoidRootPart.Position - cFrame3.Position).Magnitude > 15 then
						_tp(cFrame3)

						return
					end

					pcall(function()
						local Net = game:GetService("ReplicatedStorage").Modules.Net

						Net:FindFirstChild("RF/SubmarineWorkerSpeak"):InvokeServer("AskKilledTikiBoss")
						task.wait(0.5)
						Net:FindFirstChild("RF/SubmarineWorkerSpeak"):InvokeServer("TravelToSubmergedIsland")
					end)

					local now = tick()

					while true do
						task.wait(0.5)

						if not _G.Level then
							break
						elseif IsInSubmergedIsland() or tick() - now > 10 then
							break
						end
					end

					return
				end

				local v1210 = QuestNeta()

				if not v1210 or not v1210[1] then
					task.wait(1)

					return
				end

				local Quest = GuiShown("Quest")

				if Quest then
					Quest = CheckHasQuest(v1210[5] or v1210[1])
				end

				if GuiShown("Quest") and not Quest then
					replicated.Remotes.CommF_:InvokeServer("AbandonQuest")
					task.wait(0.2)

					return
				end

				if not Quest then
					local v1212 = v1210[6]

					if v1212 then
						_tp(v1212)
						task.wait(2)

						if (HumanoidRootPart.Position - v1212.Position).Magnitude <= 10 then
							BFAcceptQuest(v1210[3], v1210[2], v1210[5] or v1210[1])
						end
					else
						BFAcceptQuest(v1210[3], v1210[2], v1210[5] or v1210[1])
					end

					return
				end

				local v1213 = v1210[1]
				local v1214 = false
				local v1215, v1216, v1217 = pairs(workspace.Enemies:GetChildren())
				local v1218 = geniter(v1215, v1216, v1217)
				local exitTo
				local v1220, HumanoidRootPart2

				while true do
					local v1222 = table.pack(v1218())

					if v1222[1] then
						v1220 = v1222[3]

						if string.find(v1220.Name, v1213, 1, true) and Attack.Alive(v1220) then
							HumanoidRootPart2 = v1220:FindFirstChild("HumanoidRootPart")

							if HumanoidRootPart2 then
								exitTo = 1

								break
							end
						end
					else
						break
					end
				end

				local v1223, v1224, v1225, v1226, v1227, HumanoidRootPart3

				if exitTo == 1 then
					v1214 = true

					local ok

					repeat
						task.wait(Sec)
						ok = not Attack.Alive(v1220) or not HumanoidRootPart2.Parent

						if not ok then
							_tp(HumanoidRootPart2.CFrame * CFrame.new(0, 20, 0))
							Attack.Kill(v1220, _G.Level)
							ok = not GuiShown("Quest") or not _G.Level or not v1220.Parent or not Attack.Alive(v1220)
						end
					until ok

					if not v1214 then
						v1223, v1224, v1225 = pairs(replicated:GetChildren())
						v1226 = geniter(v1223, v1224, v1225)

						while true do
							local v1230 = table.pack(v1226())

							if not v1230[1] then
								break
							end

							v1227 = v1230[3]

							if string.find(v1227.Name, v1213, 1, true) and Attack.Alive(v1227) then
								HumanoidRootPart3 = v1227:FindFirstChild("HumanoidRootPart")

								if HumanoidRootPart3 then
									v1214 = true
									_tp(HumanoidRootPart3.CFrame * CFrame.new(0, 20, 0))

									break
								end
							end
						end
					end
				elseif not v1214 then
					v1223, v1224, v1225 = pairs(replicated:GetChildren())
					v1226 = geniter(v1223, v1224, v1225)

					while true do
						local v1231 = table.pack(v1226())

						if not v1231[1] then
							break
						end

						v1227 = v1231[3]

						if string.find(v1227.Name, v1213, 1, true) and Attack.Alive(v1227) then
							HumanoidRootPart3 = v1227:FindFirstChild("HumanoidRootPart")

							if HumanoidRootPart3 then
								v1214 = true
								_tp(HumanoidRootPart3.CFrame * CFrame.new(0, 20, 0))

								break
							end
						end
					end
				end

				if not v1214 then
					local v1232, v1233, v1234 = pairs(workspace._WorldOrigin.EnemySpawns:GetChildren())

					for _, v in v1232, v1233, v1234 do
						if string.find(v.Name, v1213, 1, true) then
							_tp(v.CFrame * CFrame.new(0, 20, 0))
							v1214 = true

							break
						end
					end
				end

				if not v1214 and PosMon then
					_tp(CFrame.new(PosMon) * CFrame.new(0, 20, 0))
				end
			end)
		else
			teleporting = false
			alreadyTeleported = false
		end
	end
end)

local LocalPlayer3 = game:GetService("Players").LocalPlayer
local ReplicatedStorage3 = game:GetService("ReplicatedStorage")

spawn(function()
	while wait(Sec) do
		pcall(function()
			if _G.Auto_Awakener then
				ReplicatedStorage3.Remotes.CommF_:InvokeServer("Awakener", "Check")
				ReplicatedStorage3.Remotes.CommF_:InvokeServer("Awakener", "Awaken")
			end
		end)
	end
end)
spawn(function()
	while task.wait(1) do
		if getgenv().AutoBuyMicrochipLaw then
			pcall(function()
				game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("BlackbeardReward", "Microchip", "2")
			end)
		end
	end
end)

do
	spawn(function()
		while task.wait(1) do
			if getgenv().AutoStartLawRaids then
				pcall(function()
					fireclickdetector(workspace.Map.CircleIsland.RaidSummon.Button.Main.ClickDetector)
				end)
			end
		end
	end)
end

spawn(function()
	while wait(Sec) do
		if _G.AutoLawKak then
			pcall(function()
				local Order = GetConnectionEnemies("Order")

				if Order then
					while true do
						task.wait()
						Attack.Kill(Order, _G.AutoLawKak)

						if _G.AutoLawKak == false then
							break
						elseif not Order.Parent or Order.Humanoid.Health <= 0 then
							break
						end
					end
				else
					_tp(CFrame.new(-6217.2021484375, 28.047645568848, -5053.1357421875))
				end
			end)
		end
	end
end)

local LocalPlayer4 = game.Players.LocalPlayer

do
	GetHRP = function()
		local Character = LocalPlayer4.Character

		return Character and Character:FindFirstChild("HumanoidRootPart")
	end
end

spawn(function()
	while task.wait(0.15) do
		if _G.AutoFarmDungeon then
			pcall(function()
				local Character = game.Players.LocalPlayer.Character
				local HumanoidRootPart = Character and Character:FindFirstChild("HumanoidRootPart")
				local Humanoid = Character and Character:FindFirstChildOfClass("Humanoid")

				if not HumanoidRootPart or not Humanoid or Humanoid.Health <= 0 then
					return
				end

				for _, child in pairs(workspace.Enemies:GetChildren()) do
					if not _G.AutoFarmDungeon then
						break
					end

					local Humanoid2 = child:FindFirstChild("Humanoid")
					local HumanoidRootPart2 = child:FindFirstChild("HumanoidRootPart")

					if Humanoid2 and HumanoidRootPart2 and Humanoid2.Health > 0 and (HumanoidRootPart2.Position - HumanoidRootPart.Position).Magnitude <= FARM_RANGE then
						while true do
							task.wait()
							Attack.Kill(child, true)

							if not _G.AutoFarmDungeon then
								break
							elseif not child.Parent or Humanoid2.Health <= 0 then
								break
							end
						end
					end
				end
			end)
		end
	end
end)
GetCurrentFloor = function()
	local v1249 = GetHRP()

	if not v1249 then
		return
	end

	for _, child in pairs(workspace.Map.Dungeon:GetChildren()) do
		local ExitTeleporter = child:FindFirstChild("ExitTeleporter")

		if ExitTeleporter and ExitTeleporter:FindFirstChild("Root") and (v1249.Position - ExitTeleporter.Root.Position).Magnitude < 200 then
			return ExitTeleporter.Root
		end
	end
end
task.spawn(function()
	while task.wait(0.3) do
		if not _G.TPFloor1 then
			tp1Done = false
		elseif not tp1Done then
			local v1253 = GetCurrentFloor()

			if v1253 then
				local cFrame3 = v1253.CFrame * CFrame.new(0, 3, 0)

				GetHRP().CFrame = cFrame3
				tp1Done = true
			end
		end
	end
end)
task.spawn(function()
	while task.wait(0.3) do
		if not _G.TPFloor2 then
			tp2Done = false
		elseif not tp2Done then
			local v1255 = GetHRP()

			if v1255 then
				for _, child in pairs(workspace.Map.Dungeon:GetChildren()) do
					local EntranceTeleporter = child:FindFirstChild("EntranceTeleporter")
					local ExitTeleporter = child:FindFirstChild("ExitTeleporter")

					if EntranceTeleporter and ExitTeleporter and EntranceTeleporter:FindFirstChild("Root") and ExitTeleporter:FindFirstChild("Root") and (v1255.Position - EntranceTeleporter.Root.Position).Magnitude < 100 then
						v1255.CFrame = ExitTeleporter.Root.CFrame * CFrame.new(0, 3, 0)
						tp2Done = true

						break
					end
				end
			end
		end
	end
end)
GetHighestFloor = function()
	local v1260

	for _, child in pairs(workspace.Map.Dungeon:GetChildren()) do
		local v1263 = tonumber(child.Name)

		if v1263 and (not v1260 or tonumber(v1260.Name) < v1263) then
			v1260 = child
		end
	end

	return v1260
end
task.spawn(function()
	while task.wait(0.3) do
		if not _G.TPFloor3 then
			tp3Done = false
		elseif not tp3Done then
			local v1264 = GetHighestFloor()

			if v1264 then
				if v1264:FindFirstChild("ExitTeleporter") then
					if v1264.ExitTeleporter:FindFirstChild("Root") then
						GetHRP().CFrame = v1264.ExitTeleporter.Root.CFrame * CFrame.new(0, 3, 0)
						tp3Done = true
					end
				end
			end
		end
	end
end)
GetNearestExit = function()
	local v1265 = GetHRP()

	if not v1265 then
		return
	end

	local Root_
	local huge = math.huge

	for _, child in pairs(workspace.Map.Dungeon:GetChildren()) do
		local ExitTeleporter = child:FindFirstChild("ExitTeleporter")

		if ExitTeleporter and ExitTeleporter:FindFirstChild("Root") then
			local Magnitude = (v1265.Position - ExitTeleporter.Root.Position).Magnitude

			if Magnitude < huge then
				huge = Magnitude
				Root_ = ExitTeleporter.Root
			end
		end
	end

	return Root_
end
task.spawn(function()
	while task.wait(0.3) do
		if not _G.TPFloor4 then
			tp4Done = false
		elseif not tp4Done then
			local v1272 = GetNearestExit()

			if v1272 then
				GetHRP().CFrame = v1272.CFrame * CFrame.new(0, 3, 0)
				tp4Done = true
			end
		end
	end
end)

do
	spawn(function()
		while wait() do
			pcall(function()
				if _G.AimMethod then
					if ABmethod == "Aim Player" then
						local v1273 = Players2:FindFirstChild(getgenv().PlayersList)

						if v1273 and v1273.Character then
							if v1273.Character:FindFirstChild("HumanoidRootPart") and v1273.Team ~= LocalPlayer4.Team then
								MousePos = v1273.Character.HumanoidRootPart.Position
							end
						end
					end
				end
			end)
		end
	end)
end

spawn(function()
	while wait() do
		pcall(function()
			if _G.AimMethod and ABmethod == "Nearest Aim" then
				local huge = math.huge

				for _, player in pairs(Players2:GetPlayers()) do
					if player ~= LocalPlayer4 and player.Team ~= LocalPlayer4.Team and player.Character then
						if player.Character:FindFirstChild("HumanoidRootPart") then
							local Magnitude = (player.Character.HumanoidRootPart.Position - LocalPlayer4.Character.HumanoidRootPart.Position).Magnitude

							if Magnitude < huge then
								huge = Magnitude
								MousePos = player.Character.HumanoidRootPart.Position
							end
						end
					end
				end
			end
		end)
	end
end)
task.spawn(function()
	while task.wait(Sec) do
		pcall(function()
			if _G.AimCam then
				local CurrentCamera = workspace.CurrentCamera

				closestplayer = function()
					local huge = math.huge
					local v1280
					local players, v1282 = ply:GetPlayers()

					for _, v in next, players, v1282 do
						if v ~= LocalPlayer4 and v.Character then
							if v.Character:FindFirstChild("Head") and _G.AimCam and v.Character.Humanoid.Health > 0 then
								local Magnitude = (v.Character.Head.Position - LocalPlayer4.Character.Head.Position).Magnitude

								if Magnitude < huge then
									huge = Magnitude
									v1280 = v
								end
							end
						end
					end

					return v1280
				end

				while true do
					task.wait()
					CurrentCamera.CFrame = CFrame.new(CurrentCamera.CFrame.Position, closestplayer().Character.HumanoidRootPart.Position)

					if _G.AimCam == false then
						break
					elseif dist < Mag then
						break
					end
				end
			end
		end)
	end
end)
spawn(function()
	while task.wait(1) do
		if _G.AutoReceivePlayerQuest then
			pcall(function()
				if game.Players.LocalPlayer.PlayerGui.Main.Quest.Visible == false then
					game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("PlayerHunter")
				end
			end)
		end
	end
end)

do
	spawn(function()
		local n10 = 0

		while task.wait() do
			if _G.AutoPlayerHunter then
				local exitTo

				repeat
					pcall(function()
						local Main = game.Players.LocalPlayer.PlayerGui.Main

						if Main.Quest.Visible == false then
							task.wait(0.5)

							if _G.AutoPlayerHunter then
								game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("PlayerHunter")
							end
						else
							local Text = Main.Quest.Container.QuestTitle.Title.Text

							for _, child in pairs(game:GetService("Workspace").Characters:GetChildren()) do
								if not _G.AutoPlayerHunter then
									break
								end

								if child ~= game.Players.LocalPlayer.Character and string.find(Text, child.Name, 1, true) then
									local v1292 = false
									local v1293 = false

									while true do
										task.wait()

										local HumanoidRootPart = child:FindFirstChild("HumanoidRootPart")
										local Humanoid = child:FindFirstChild("Humanoid")

										if not child.Parent or not HumanoidRootPart or not Humanoid then
											v1293 = true

											break
										end

										if Humanoid.Health <= 0 then
											v1292 = true

											break
										else
											if AutoHaki then
												AutoHaki()
											end

											if EquipWeapon then
												EquipWeapon(_G.SelectWeapon)
											end

											Useskill = true
											_tp(HumanoidRootPart.CFrame * CFrame.new(1, 7, 3))
											HumanoidRootPart.Size = Vector3.new(60, 60, 60)
											game:GetService("VirtualUser"):CaptureController()
											game:GetService("VirtualUser"):Button1Down(Vector2.new(1280, 672))

											if _G.AutoPlayerHunter ~= false then
												continue
											end
										end

										break
									end

									Useskill = false

									if (v1292 or v1293) and _G.AutoPlayerHunter and tick() - n10 > 5 then
										n10 = tick()
										game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("AbandonQuest")
									end
								end
							end
						end
					end)
					exitTo = nil

					while task.wait() do
						if _G.AutoPlayerHunter then
							exitTo = 1

							break
						end
					end
				until exitTo ~= 1

				return
			end
		end
	end)
end

spawn(function()
	while task.wait(0.5) do
		if _G.AutoPvP then
			local PlayerGui = game.Players.LocalPlayer.PlayerGui

			if PlayerGui and PlayerGui.Main then
				if PlayerGui.Main:FindFirstChild("PvpDisabled") and PlayerGui.Main.PvpDisabled.Visible then
					pcall(function()
						game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer("EnablePvp")
					end)
				end
			end
		end
	end
end)
spawn(function()
	while task.wait(0.1) do
		if _G.SafeMode then
			local Character = game.Players.LocalPlayer.Character
			local HumanoidRootPart = Character and Character:FindFirstChild("HumanoidRootPart")

			if HumanoidRootPart then
				_tp(HumanoidRootPart.CFrame * CFrame.new(0, 1000, 0))
			end
		end
	end
end)

do
	local Players3 = game:GetService("Players")
	local UserInputService2 = game:GetService("UserInputService")
	local RunService2 = game:GetService("RunService")
	local LocalPlayer5 = Players3.LocalPlayer
	local u1303 = false
	local n11 = 50
	local connection
	local t42 = {
		f = 0,
		b = 0,
		l = 0,
		r = 0
	}
	local BodyGyro
	local BodyVelocity

	updateControlsFromJoystick = function()
		local Character = LocalPlayer5.Character
		local Humanoid = Character and Character:FindFirstChildOfClass("Humanoid")

		if Humanoid then
			local MoveDirection = Humanoid.MoveDirection
			local CFrame_ = workspace.CurrentCamera and workspace.CurrentCamera.CFrame

			if CFrame_ and MoveDirection.Magnitude > 0.05 then
				local v1313 = CFrame_:VectorToObjectSpace(MoveDirection)

				t42.f = v1313.Z < -0.1 and 1 or v1313.Z > 0.1 and -1 or 0
				t42.b = 0
				t42.l = v1313.X < -0.1 and -1 or 0
				t42.r = v1313.X > 0.1 and 1 or 0
			else
				t42.f = 0
				t42.b = 0
				t42.l = 0
				t42.r = 0
			end
		end
	end
	UserInputService2.InputBegan:Connect(function(input, gameProcessed)
		if not gameProcessed and u1303 then
			if input.KeyCode == Enum.KeyCode.W then
				t42.f = 1
			elseif input.KeyCode == Enum.KeyCode.S then
				t42.b = -1
			elseif input.KeyCode == Enum.KeyCode.A then
				t42.l = -1
			elseif input.KeyCode == Enum.KeyCode.D then
				t42.r = 1
			end
		end
	end)
	UserInputService2.InputEnded:Connect(function(input)
		if u1303 then
			if input.KeyCode == Enum.KeyCode.W and t42.f == 1 then
				t42.f = 0
			elseif input.KeyCode == Enum.KeyCode.S and t42.b == -1 then
				t42.b = 0
			elseif input.KeyCode == Enum.KeyCode.A and t42.l == -1 then
				t42.l = 0
			elseif input.KeyCode == Enum.KeyCode.D and t42.r == 1 then
				t42.r = 0
			end
		end
	end)
	setupMobileControls = function()
		local connection2

		connection2 = RunService2.Heartbeat:Connect(function()
			if u1303 then
				updateControlsFromJoystick()
			elseif connection2 then
				connection2:Disconnect()
			end
		end)
	end
	toggleFly = function(p110)
		u1303 = p110

		if u1303 then
			if not LocalPlayer5.Character then
				return
			end

			local Humanoid = LocalPlayer5.Character:FindFirstChildOfClass("Humanoid")
			local Torso

			if LocalPlayer5.Character:FindFirstChild("Torso") then
				Torso = LocalPlayer5.Character.Torso
			else
				Torso = LocalPlayer5.Character.UpperTorso
			end

			if not Humanoid or not Torso then
				return
			end

			for _, descendant in ipairs(LocalPlayer5.Character:GetDescendants()) do
				if descendant:IsA("BasePart") then
					descendant.CanCollide = false
					descendant.Massless = true
				end
			end

			LocalPlayer5.Character.DescendantAdded:Connect(function(descendant)
				if u1303 then
					if descendant:IsA("BasePart") then
						descendant.CanCollide = false
						descendant.Massless = true
					end
				end
			end)
			BodyGyro = Instance.new("BodyGyro", Torso)
			BodyGyro.P = 90000
			BodyGyro.maxTorque = Vector3.new(9e9, 9e9, 9e9)
			BodyGyro.cframe = Torso.CFrame
			BodyVelocity = Instance.new("BodyVelocity", Torso)
			BodyVelocity.velocity = Vector3.new(0, 0, 0)
			BodyVelocity.maxForce = Vector3.new(9e9, 9e9, 9e9)
			Humanoid.PlatformStand = true
			setupMobileControls()
			connection = RunService2.Heartbeat:Connect(function()
				if not u1303 or not LocalPlayer5.Character then
					return
				end

				for _, descendant in ipairs(LocalPlayer5.Character:GetDescendants()) do
					if descendant:IsA("BasePart") and descendant.CanCollide then
						descendant.CanCollide = false
					end
				end

				if t42.l + t42.r == 0 and t42.f + t42.b == 0 then
					BodyVelocity.velocity = Vector3.new(0, 0, 0)
				else
					BodyVelocity.velocity = (workspace.CurrentCamera.CoordinateFrame.lookVector * (t42.f + t42.b) + (workspace.CurrentCamera.CoordinateFrame * CFrame.new(t42.l + t42.r, (t42.f + t42.b) * 0.2, 0).p - workspace.CurrentCamera.CoordinateFrame.p)) * n11
				end

				BodyGyro.cframe = workspace.CurrentCamera.CoordinateFrame
			end)
		else
			if connection then
				connection:Disconnect()
				connection = nil
			end

			if LocalPlayer5.Character then
				local Humanoid = LocalPlayer5.Character:FindFirstChildOfClass("Humanoid")

				if Humanoid then
					Humanoid.PlatformStand = false
				end

				for _, descendant in ipairs(LocalPlayer5.Character:GetDescendants()) do
					if descendant:IsA("BasePart") then
						descendant.CanCollide = true
						descendant.Massless = false
					end
				end

				if BodyGyro then
					BodyGyro:Destroy()
				end

				if BodyVelocity then
					BodyVelocity:Destroy()
				end
			end

			t42 = {
				f = 0,
				b = 0,
				l = 0,
				r = 0
			}
		end
	end
	_G.toggleFly = toggleFly
	updateFlySpeed = function(p111)
		n11 = p111
	end
end

_G.updateFlySpeed = updateFlySpeed
NoCooldown = function()
	local Dodge = game.Players.LocalPlayer.Character:WaitForChild("Dodge")
	local v1325, v1326 = getgc()

	for _, v in next, v1325, v1326 do
		if typeof(v) == "function" and getfenv(v).script == Dodge then
			local next_ = next
			local v1330, v1331 = getupvalues(v)

			for k, v2 in next_, v1330, v1331 do
				if tostring(v2) == "0.4" then
					setupvalue(v, k, 0)
				end
			end
		end
	end
end

do
	spawn(function()
		while wait(0.2) do
			pcall(function()
				if not InfAblities then
					local Agility = LocalPlayer4.Character.HumanoidRootPart:FindFirstChild("Agility")

					if Agility then
						Agility:Destroy()
					end
				elseif not LocalPlayer4.Character.HumanoidRootPart:FindFirstChild("Agility") then
					local clone = ReplicatedStorage3.FX.Agility:Clone()

					clone.Name = "Agility"
					clone.Parent = LocalPlayer4.Character.HumanoidRootPart
				end
			end)
		end
	end)
end

spawn(function()
	while wait(Sec) do
		if _G.AcceptAlly then
			pcall(function()
				for _, child in pairs(ply:GetChildren()) do
					if child.Name ~= LocalPlayer4.Name and child:FindFirstChild("Humanoid") and child:FindFirstChild("HumanoidRootPart") then
						ReplicatedStorage3:WaitForChild("Remotes"):WaitForChild("CommF_"):InvokeServer("AcceptAlly", child.Name)
					end
				end
			end)
		end
	end
end)
spawn(function()
	while wait(Sec) do
		if _G.TPNpc then
			pcall(function()
				for _, child in pairs(ReplicatedStorage3.NPCs:GetChildren()) do
					if child.Name == NPClist then
						_tp(child.HumanoidRootPart.CFrame)
					end
				end
			end)
		end
	end
end)

do
	local ReplicatedStorage4 = game:GetService("ReplicatedStorage")

	spawn(function()
		while wait(Sec) do
			pcall(function()
				if _G.PortalUnLock then
					if Attack.Pos(CstlePos_Miti, 8) then
						ReplicatedStorage4.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(-12471.169921875, 374.94024658203, -7551.677734375))
					elseif Attack.Pos(Man3Pos_Miti, 8) then
						ReplicatedStorage4.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(-5072.08984375, 314.5412902832, -3151.1098632812))
					elseif Attack.Pos(HydraPos_Miti, 8) then
						ReplicatedStorage4.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(5748.7587890625, 610.44982910156, -267.81704711914))
					elseif Attack.Pos(HydratoCastle, 8) then
						ReplicatedStorage4.Remotes.CommF_:InvokeServer("requestEntrance", Vector3.new(-5072.08984375, 314.5412902832, -3151.1098632812))
					end
				end
			end)
		end
	end)
	task.spawn(function()
		while task.wait() do
			if _G.daylightN then
				if _G.SelectDN == "Day" then
					Lighting.ClockTime = 12
				elseif _G.SelectDN == "Night" then
					Lighting.ClockTime = 0
				end
			end
		end
	end)
	spawn(function()
		while task.wait() do
			if _G.WalkWater then
				pcall(function()
					if LocalPlayer4.Character then
						if LocalPlayer4.Character:FindFirstChild("LeftFoot") then
							local clone = ReplicatedStorage4.Assets.Models.IceSpikes4:Clone()

							clone.Parent = workspace
							clone.Size = Vector3.new(3 + math.random(10, 12), 1.7, 3 + math.random(10, 12))
							clone.Color = Color3.fromRGB(128, 187, 219)
							clone.CFrame = CFrame.new(LocalPlayer4.Character.Head.Position.X, -3.8, LocalPlayer4.Character.Head.Position.Z) * CFrame.Angles((math.random() - 0.5) * 0.06, math.random() * 7, (math.random() - 0.5) * 0.07)

							local t43 = {
								Size = Vector3.new(0, 0.3, 0)
							}
							local tween = TW:Create(clone, TweenInfo.new(2, Enum.EasingStyle.Quad, Enum.EasingDirection.In), t43)

							tween.Completed:Connect(function()
								clone:Destroy()
							end)
							tween:Play()
						end
					end
				end)
			end
		end
	end)
	Number = Number or math.random(1, 1000000)

	local Team = LocalPlayer4.Team

	EspPly = function()
		local children, v1346 = game.Players:GetChildren()

		for _, v in next, children, v1346 do
			pcall(function()
				if not isnil(v.Character) then
					if PlayerEsp then
						local ok = isnil(v.Character.Head)

						if not ok then
							ok = v.Character.Head:FindFirstChild("NameEsp" .. Number)
						end

						if ok then
							if v.Character.Head:FindFirstChild("NameEsp" .. Number) then
								v.Character.Head["NameEsp" .. Number].TextLabel.Text = v.Name .. " | " .. round((LocalPlayer4.Character.Head.Position - v.Character.Head.Position).Magnitude / 3) .. " M\nHealth : " .. round(v.Character.Humanoid.Health * 100 / v.Character.Humanoid.MaxHealth) .. "%"
							end
						else
							local BillboardGui = Instance.new("BillboardGui", v.Character.Head)

							BillboardGui.Name = "NameEsp" .. Number
							BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
							BillboardGui.Size = UDim2.new(1, 200, 1, 30)
							BillboardGui.Adornee = v.Character.Head
							BillboardGui.AlwaysOnTop = true

							local TextLabel = Instance.new("TextLabel", BillboardGui)

							TextLabel.Font = Enum.Font.Code
							TextLabel.FontSize = "Size14"
							TextLabel.TextWrapped = true
							TextLabel.Text = v.Name .. " \n" .. round((LocalPlayer4.Character.Head.Position - v.Character.Head.Position).Magnitude / 3) .. " M"
							TextLabel.Size = UDim2.new(1, 0, 1, 0)
							TextLabel.TextYAlignment = "Top"
							TextLabel.BackgroundTransparency = 1
							TextLabel.TextStrokeTransparency = 0.5

							if v.Team == Team then
								TextLabel.TextColor3 = Color3.new(0, 0, 254)
							else
								TextLabel.TextColor3 = Color3.new(255, 0, 0)
							end
						end
					elseif v.Character.Head:FindFirstChild("NameEsp" .. Number) then
						v.Character.Head:FindFirstChild("NameEsp" .. Number):Destroy()
					end
				end
			end)
		end
	end
	LocationEsp = function()
		local children, v1353 = workspace._WorldOrigin.Locations:GetChildren()

		for _, v in next, children, v1353 do
			pcall(function()
				if not IslandESP then
					if v:FindFirstChild("NameEsp") then
						v:FindFirstChild("NameEsp"):Destroy()
					end
				elseif v.Name ~= "Sea" then
					if v:FindFirstChild("NameEsp") then
						v.NameEsp.TextLabel.Text = v.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - v.Position).Magnitude / 3) .. " M"
					else
						local BillboardGui = Instance.new("BillboardGui", v)

						BillboardGui.Name = "NameEsp"
						BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
						BillboardGui.Size = UDim2.new(1, 200, 1, 30)
						BillboardGui.Adornee = v
						BillboardGui.AlwaysOnTop = true

						local TextLabel = Instance.new("TextLabel", BillboardGui)

						TextLabel.Font = Enum.Font.Code
						TextLabel.FontSize = "Size14"
						TextLabel.TextWrapped = true
						TextLabel.Size = UDim2.new(1, 0, 1, 0)
						TextLabel.TextYAlignment = "Top"
						TextLabel.BackgroundTransparency = 1
						TextLabel.TextStrokeTransparency = 0.5
						TextLabel.TextColor3 = Color3.fromRGB(98, 252, 252)
						TextLabel.Text = v.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - v.Position).Magnitude / 3) .. " M"
					end
				end
			end)
		end
	end
	DevEsp = function()
		local children, v1359 = workspace:GetChildren()

		for _, v in next, children, v1359 do
			pcall(function()
				if not DevilFruitESP then
					if v:FindFirstChild("Handle") then
						if v.Handle:FindFirstChild("NameEsp" .. Number) then
							v.Handle:FindFirstChild("NameEsp" .. Number):Destroy()
						end
					end
				elseif string.find(v.Name, "Fruit") then
					if v.Handle:FindFirstChild("NameEsp" .. Number) then
						v.Handle["NameEsp" .. Number].TextLabel.Text = "[" .. v.Name .. "]" .. "   \n" .. round((LocalPlayer4.Character.Head.Position - v.Handle.Position).Magnitude / 3) .. " M"
					else
						local BillboardGui = Instance.new("BillboardGui", v.Handle)

						BillboardGui.Name = "NameEsp" .. Number
						BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
						BillboardGui.Size = UDim2.new(1, 200, 1, 30)
						BillboardGui.Adornee = v.Handle
						BillboardGui.AlwaysOnTop = true

						local TextLabel = Instance.new("TextLabel", BillboardGui)

						TextLabel.Font = Enum.Font.Code
						TextLabel.FontSize = "Size14"
						TextLabel.TextWrapped = true
						TextLabel.Size = UDim2.new(1, 0, 1, 0)
						TextLabel.TextYAlignment = "Top"
						TextLabel.BackgroundTransparency = 1
						TextLabel.TextStrokeTransparency = 0.5
						TextLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
						TextLabel.Text = v.Name .. " \n" .. round((LocalPlayer4.Character.Head.Position - v.Handle.Position).Magnitude / 3) .. " M"
					end
				end
			end)
		end
	end
	flowerEsp = function()
		for _, child in pairs(workspace:GetChildren()) do
			pcall(function()
				if child.Name == "Flower2" or child.Name == "Flower1" then
					if not FlowerESP then
						if child:FindFirstChild("NameEsp" .. Number) then
							child:FindFirstChild("NameEsp" .. Number):Destroy()
						end
					elseif child:FindFirstChild("NameEsp" .. Number) then
						child["NameEsp" .. Number].TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.Position).Magnitude / 3) .. " M"
					else
						local BillboardGui = Instance.new("BillboardGui", child)

						BillboardGui.Name = "NameEsp" .. Number
						BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
						BillboardGui.Size = UDim2.new(1, 200, 1, 30)
						BillboardGui.Adornee = child
						BillboardGui.AlwaysOnTop = true

						local TextLabel = Instance.new("TextLabel", BillboardGui)

						TextLabel.Font = Enum.Font.Code
						TextLabel.FontSize = "Size14"
						TextLabel.TextWrapped = true
						TextLabel.Size = UDim2.new(1, 0, 1, 0)
						TextLabel.TextYAlignment = "Top"
						TextLabel.BackgroundTransparency = 1
						TextLabel.TextStrokeTransparency = 0.5
						TextLabel.TextColor3 = Color3.fromRGB(88, 214, 252)

						if child.Name == "Flower1" then
							TextLabel.Text = "Blue Flower" .. " \n" .. round((LocalPlayer4.Character.Head.Position - child.Position).Magnitude / 3) .. " M"
						elseif child.Name == "Flower2" then
							TextLabel.Text = "Red Flower" .. " \n" .. round((LocalPlayer4.Character.Head.Position - child.Position).Magnitude / 3) .. " M"
						end
					end
				end
			end)
		end
	end
	EventIslandEsp = function()
		for _, child in pairs(workspace._WorldOrigin.Locations:GetChildren()) do
			pcall(function()
				if not EspEventIsland then
					if child:FindFirstChild("NameEsp") then
						child:FindFirstChild("NameEsp"):Destroy()
					end
				elseif child.Name == "Mirage Island" or child.Name == "Prehistoric Island" or child.Name == "Kitsune Island" then
					if child:FindFirstChild("NameEsp") then
						child.NameEsp.TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.Position).Magnitude / 3) .. " M"
					else
						local BillboardGui = Instance.new("BillboardGui", child)

						BillboardGui.Name = "NameEsp"
						BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
						BillboardGui.Size = UDim2.new(1, 200, 1, 30)
						BillboardGui.Adornee = child
						BillboardGui.AlwaysOnTop = true

						local TextLabel = Instance.new("TextLabel", BillboardGui)

						TextLabel.Font = "Code"
						TextLabel.FontSize = "Size14"
						TextLabel.TextWrapped = true
						TextLabel.Size = UDim2.new(1, 0, 1, 0)
						TextLabel.TextYAlignment = "Top"
						TextLabel.BackgroundTransparency = 1
						TextLabel.TextStrokeTransparency = 0.5
						TextLabel.TextColor3 = Color3.fromRGB(80, 245, 245)
						TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.Position).Magnitude / 3) .. " M"
					end
				end
			end)
		end
	end
	gearEsp = function()
		local MysticIsland = workspace.Map:FindFirstChild("MysticIsland")

		if not MysticIsland then
			return
		end

		for _, descendant in pairs(MysticIsland:GetDescendants()) do
			pcall(function()
				if not ESPGear then
					if descendant:FindFirstChild("NameEsp") then
						descendant:FindFirstChild("NameEsp"):Destroy()
					end
				elseif descendant.Name == "Part" and descendant.Material == Enum.Material.Neon then
					if descendant:FindFirstChild("NameEsp") then
						descendant.NameEsp.TextLabel.Text = "Gear" .. "   \n" .. round((LocalPlayer4.Character.Head.Position - descendant.Position).Magnitude / 3) .. " M"
					else
						local BillboardGui = Instance.new("BillboardGui", descendant)

						BillboardGui.Name = "NameEsp"
						BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
						BillboardGui.Size = UDim2.new(1, 200, 1, 30)
						BillboardGui.Adornee = descendant
						BillboardGui.AlwaysOnTop = true

						local TextLabel = Instance.new("TextLabel", BillboardGui)

						TextLabel.Font = "Code"
						TextLabel.FontSize = "Size14"
						TextLabel.TextWrapped = true
						TextLabel.Size = UDim2.new(1, 0, 1, 0)
						TextLabel.TextYAlignment = "Top"
						TextLabel.BackgroundTransparency = 1
						TextLabel.TextStrokeTransparency = 0.5
						TextLabel.TextColor3 = Color3.fromRGB(80, 245, 245)
						TextLabel.Text = "Gear" .. "   \n" .. round((LocalPlayer4.Character.Head.Position - descendant.Position).Magnitude / 3) .. " M"
					end
				end
			end)
		end
	end
	AdvanFruitEsp = function()
		if advanEsp then
			for _, child in pairs(ReplicatedStorage4.NPCs:GetChildren()) do
				if child.Name == "Advanced Fruit Dealer" then
					if not workspace:FindFirstChild("Adv") then
						Adv = Instance.new("Part")
						Adv.Name = "Adv"
						Adv.Transparency = 1
						Adv.Size = Vector3.new(1, 1, 1)
						Adv.Anchored = true
						Adv.CanCollide = false
						Adv.Parent = workspace
						Adv.CFrame = child.HumanoidRootPart.CFrame
					elseif workspace:FindFirstChild("Adv") then
						if Adv:FindFirstChild("NameEsp") then
							Adv.NameEsp.TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.HumanoidRootPart.Position).Magnitude / 3) .. " M"
						else
							local BillboardGui = Instance.new("BillboardGui", Adv)

							BillboardGui.Name = "NameEsp"
							BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
							BillboardGui.Size = UDim2.new(1, 200, 1, 30)
							BillboardGui.Adornee = Adv
							BillboardGui.AlwaysOnTop = true

							local TextLabel = Instance.new("TextLabel", BillboardGui)

							TextLabel.Font = "Code"
							TextLabel.FontSize = "Size14"
							TextLabel.TextWrapped = true
							TextLabel.Size = UDim2.new(1, 0, 1, 0)
							TextLabel.TextYAlignment = "Top"
							TextLabel.BackgroundTransparency = 1
							TextLabel.TextStrokeTransparency = 0.5
							TextLabel.TextColor3 = Color3.fromRGB(80, 245, 245)
							TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.HumanoidRootPart.Position).Magnitude / 3) .. " M"
						end
					end
				end
			end
		elseif workspace:FindFirstChild("Adv") then
			workspace:FindFirstChild("Adv"):Destroy()
		end
	end
	HakiClorEsp = function()
		if ColorEsp then
			for _, child in pairs(ReplicatedStorage4.NPCs:GetChildren()) do
				if child.Name == "Barista Cousin" then
					if not workspace:FindFirstChild("Gay") then
						Gay = Instance.new("Part")
						Gay.Name = "Gay"
						Gay.Transparency = 1
						Gay.Size = Vector3.new(1, 1, 1)
						Gay.Anchored = true
						Gay.CanCollide = false
						Gay.Parent = workspace
						Gay.CFrame = child.HumanoidRootPart.CFrame
					elseif workspace:FindFirstChild("Gay") then
						if Gay:FindFirstChild("NameEsp") then
							Gay.NameEsp.TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.HumanoidRootPart.Position).Magnitude / 3) .. " M"
						else
							local BillboardGui = Instance.new("BillboardGui", Gay)

							BillboardGui.Name = "NameEsp"
							BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
							BillboardGui.Size = UDim2.new(1, 200, 1, 30)
							BillboardGui.Adornee = Gay
							BillboardGui.AlwaysOnTop = true

							local TextLabel = Instance.new("TextLabel", BillboardGui)

							TextLabel.Font = "Code"
							TextLabel.FontSize = "Size14"
							TextLabel.TextWrapped = true
							TextLabel.Size = UDim2.new(1, 0, 1, 0)
							TextLabel.TextYAlignment = "Top"
							TextLabel.BackgroundTransparency = 1
							TextLabel.TextStrokeTransparency = 0.5
							TextLabel.TextColor3 = Color3.fromRGB(80, 245, 245)
							TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.HumanoidRootPart.Position).Magnitude / 3) .. " M"
						end
					end
				end
			end
		elseif workspace:FindFirstChild("Gay") then
			workspace:FindFirstChild("Gay"):Destroy()
		end
	end
	LegenSword = function()
		if LegenS then
			for _, child in pairs(ReplicatedStorage4.NPCs:GetChildren()) do
				if child.Name == "Legendary Sword Dealer" then
					if not workspace:FindFirstChild("Lgd") then
						Lgd = Instance.new("Part")
						Lgd.Name = "Lgd"
						Lgd.Transparency = 1
						Lgd.Size = Vector3.new(1, 1, 1)
						Lgd.Anchored = true
						Lgd.CanCollide = false
						Lgd.Parent = workspace
						Lgd.CFrame = child.HumanoidRootPart.CFrame
					elseif workspace:FindFirstChild("Lgd") then
						if Lgd:FindFirstChild("NameEsp") then
							Lgd.NameEsp.TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.HumanoidRootPart.Position).Magnitude / 3) .. " M"
						else
							local BillboardGui = Instance.new("BillboardGui", Lgd)

							BillboardGui.Name = "NameEsp"
							BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
							BillboardGui.Size = UDim2.new(1, 200, 1, 30)
							BillboardGui.Adornee = Lgd
							BillboardGui.AlwaysOnTop = true

							local TextLabel = Instance.new("TextLabel", BillboardGui)

							TextLabel.Font = "Code"
							TextLabel.FontSize = "Size14"
							TextLabel.TextWrapped = true
							TextLabel.Size = UDim2.new(1, 0, 1, 0)
							TextLabel.TextYAlignment = "Top"
							TextLabel.BackgroundTransparency = 1
							TextLabel.TextStrokeTransparency = 0.5
							TextLabel.TextColor3 = Color3.fromRGB(80, 245, 245)
							TextLabel.Text = child.Name .. "   \n" .. round((LocalPlayer4.Character.Head.Position - child.HumanoidRootPart.Position).Magnitude / 3) .. " M"
						end
					end
				end
			end
		elseif workspace:FindFirstChild("Lgd") then
			workspace:FindFirstChild("Lgd"):Destroy()
		end
	end
end

ChestEsp = function()
	if ChestESP then
		local tagged = game:GetService("CollectionService"):GetTagged("_ChestTagged")

		for _, v in ipairs(tagged) do
			pcall(function()
				local Magnitude = (v:GetPivot().Position - LocalPlayer4.Character.Head.Position).Magnitude

				v:GetFullName():gsub("[^%w_]", "_")

				local ChestEspAttachment = v:FindFirstChild("ChestEspAttachment")

				if not ChestEspAttachment then
					local Attachment = Instance.new("Attachment")

					Attachment.Name = "ChestEspAttachment"
					Attachment.Parent = v
					Attachment.Position = Vector3.new(0, 3, 0)

					local BillboardGui = Instance.new("BillboardGui")

					BillboardGui.Name = "NameEsp"
					BillboardGui.Size = UDim2.new(0, 200, 0, 30)
					BillboardGui.Adornee = Attachment
					BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
					BillboardGui.AlwaysOnTop = true
					BillboardGui.Parent = Attachment

					local TextLabel = Instance.new("TextLabel")

					TextLabel.Font = Enum.Font.Code
					TextLabel.TextSize = 14
					TextLabel.TextWrapped = true
					TextLabel.Size = UDim2.new(1, 0, 1, 0)
					TextLabel.TextYAlignment = Enum.TextYAlignment.Top
					TextLabel.BackgroundTransparency = 1
					TextLabel.TextStrokeTransparency = 0.5
					TextLabel.TextColor3 = Color3.fromRGB(80, 245, 245)
					TextLabel.Parent = BillboardGui
				end

				local NameEsp = ChestEspAttachment and ChestEspAttachment:FindFirstChild("NameEsp")

				if NameEsp then
					local v1398 = math.floor(Magnitude / 3)

					NameEsp.TextLabel.Text = string.format("[%s] %d M", v.Name:gsub("Label", ""), v1398)
				end
			end)
		end
	else
		for _, v in ipairs(game:GetService("CollectionService"):GetTagged("_ChestTagged")) do
			local ChestEspAttachment = v:FindFirstChild("ChestEspAttachment")

			if ChestEspAttachment then
				ChestEspAttachment:Destroy()
			end
		end
	end
end
berriesEsp = function()
	if BerryEsp then
		local tagged = game:GetService("CollectionService"):GetTagged("BerryBush")

		for _, v in ipairs(tagged) do
			pcall(function()
				local Position = v.Parent:GetPivot().Position

				for _, v2 in pairs(v:GetAttributes()) do
					if v2 then
						local name = "BerryEspPart_" .. v2 .. "_" .. tostring(Position)
						local Part2 = workspace:FindFirstChild(name)

						if not Part2 then
							Part2 = Instance.new("Part")
							Part2.Name = name
							Part2.Transparency = 1
							Part2.Size = Vector3.new(1, 1, 1)
							Part2.Anchored = true
							Part2.CanCollide = false
							Part2.Parent = workspace
							Part2.CFrame = CFrame.new(Position)
						end

						if not Part2:FindFirstChild("NameEsp") then
							local BillboardGui = Instance.new("BillboardGui", Part2)

							BillboardGui.Name = "NameEsp"
							BillboardGui.ExtentsOffset = Vector3.new(0, 1, 0)
							BillboardGui.Size = UDim2.new(0, 200, 0, 30)
							BillboardGui.Adornee = Part2
							BillboardGui.AlwaysOnTop = true

							local TextLabel = Instance.new("TextLabel", BillboardGui)

							TextLabel.Font = Enum.Font.Code
							TextLabel.TextSize = 14
							TextLabel.TextWrapped = true
							TextLabel.Size = UDim2.new(1, 0, 1, 0)
							TextLabel.TextYAlignment = Enum.TextYAlignment.Top
							TextLabel.BackgroundTransparency = 1
							TextLabel.TextStrokeTransparency = 0.5
							TextLabel.TextColor3 = Color3.fromRGB(80, 245, 245)
						end

						local NameEsp = Part2:FindFirstChild("NameEsp")
						local v1413 = (LocalPlayer4.Character.Head.Position - Position).Magnitude / 3

						if NameEsp then
							NameEsp.TextLabel.Text = "[" .. v2 .. "]" .. " " .. math.round(v1413) .. " M"
						end
					end
				end
			end)
		end
	else
		for _, child in ipairs(workspace:GetChildren()) do
			if child:IsA("Part") then
				if child.Name:match("BerryEspPart_.*") then
					child:Destroy()
				end
			end
		end
	end
end
Core.EspPly = EspPly
Core.LocationEsp = LocationEsp
Core.DevEsp = DevEsp
Core.flowerEsp = flowerEsp
Core.EventIslandEsp = EventIslandEsp
Core.gearEsp = gearEsp
Core.AdvanFruitEsp = AdvanFruitEsp
Core.HakiClorEsp = HakiClorEsp
Core.LegenSword = LegenSword
Core.ChestEsp = ChestEsp
Core.berriesEsp = berriesEsp

-- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
-- Join SL Discord for more leaked sources & hubs: https://discord.gg/zNyHGU6eUK
do pcall(function() getgenv().SL_SourceLeak = "Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]" end) end
do local _ = string.format("Leaked By %s | Source Leak [https://discord.gg/%s] - Join SL Discord", "SL", "zNyHGU6eUK") end
local Fluent = loadstring(game:HttpGet("https://github.com/dawid-scripts/Fluent/releases/latest/download/main.lua"))()
local UIS = game:GetService("UserInputService")
local Players = game:GetService("Players")
local RS = game:GetService("ReplicatedStorage")
local RunService = game:GetService("RunService")
local Workspace = game:GetService("Workspace")
local TweenService = game:GetService("TweenService")
local VirtualUser = game:GetService("VirtualUser")
repeat task.wait() until Players.LocalPlayer
local plr = Players.LocalPlayer
local function validNum(n)
    return type(n) == "number" and n == n and n ~= math.huge and n ~= -math.huge
end
pcall(function()
    local lt = game:GetService("Lighting")
    lt.GlobalShadows = false
    lt.FogEnd = 9e9
    for _, o in ipairs(lt:GetChildren()) do
        if o:IsA("PostEffect") or o:IsA("Atmosphere") or o:IsA("Sky") then o.Enabled = false end
    end
    local terr = workspace:FindFirstChildOfClass("Terrain")
    if terr then
        terr.WaterWaveSize = 0
        terr.WaterWaveSpeed = 0
    end
end)
if not _G.__ihooked then
    pcall(function()
        _G.__ihooked = true
        local Notification = require(RS.Notification)
        local orig = Notification.new
        Notification.new = function(msg, ...)
            local low = tostring(msg):lower()
            if low:find("store") and low:find("blox fruit") then
                return { Display = function() end, Dead = function() return true end }
            end
            return orig(msg, ...)
        end
    end)
end
plr.Idled:Connect(function()
    pcall(function()
        VirtualUser:Button2Down(Vector2.new(0, 0), Workspace.CurrentCamera.CFrame)
        task.wait(0.2)
        VirtualUser:Button2Up(Vector2.new(0, 0), Workspace.CurrentCamera.CFrame)
    end)
end)
task.spawn(function()
    while true do
        task.wait(480)
        pcall(function()
            VirtualUser:Button2Down(Vector2.new(0, 0), Workspace.CurrentCamera.CFrame)
            task.wait(0.1)
            VirtualUser:Button2Up(Vector2.new(0, 0), Workspace.CurrentCamera.CFrame)
        end)
    end -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
end)
Cfg = {
    AutoFarmLevel = false, AutoFarmNearest = false, AutoChestTween = false, AutoSecondSeaQuest = false,
    StopWhenGetItemInChest = true, AutoCollectFruit = false, AutoStoreFruit = false, AutoRandomFruit = false,
    AutoStats = false, AutoStatsMelee = false, AutoStatsDefense = false, AutoStatsGun = false,
    AutoStatsSword = false, AutoStatsFruit = false, StatPointStep = 3, AutoTeleportIsland = false,
    SelectedIslandCFrame = nil, SelectedIslandName = nil, TeleportFlightThread = nil,
    SelectedWeapon = "Melee", FlySpeed = 170, AttackDelay = 0.01, AutoBuso = true,
    AttackAuraAlways = true, SafeDistance = Vector3.new(0, 10, 0), FruitESPEnabled = true,
    PlayerESPEnabled = true, ESPShowDistance = true, PlayerMovementEnabled = false,
    -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
    WalkSpeedValue = 16, JumpPowerValue = 50, SelectedSea1Boss = "The Gorilla King", AutoFarmBosses = false,
}
State = {
    QuestState = "IDLE", QuestCooldown = 0, CurrentQuestData = nil, LastAttack = 0, LastM1Time = 0,
    LastBuso = 0, CurrentTargetMob = nil, BodyVelocity = nil, BodyGyro = nil, IsMoving = false,
    IsHoveringAtTarget = false, IsCollectingFruitMoving = false, LastVelocityMagnitude = 0,
    Connections = {}, CachedCharacterParts = {}, IsScriptDestroyed = false, ActiveESPItems = {},
    FrozenPositions = {}, FruitStoreCooldown = {}, ChestRegistry = {}, CollectedChests = {},
    IgnoredGroundFruits = {}, GroundFruitTouchAttempts = {}, IsStoringFruitActive = false,
    CurrentPatrolIndex = 1, PatrolArrivedTime = 0, LastCompletionMessageTime = 0, QuestStartTime = 0,
    FruitPriorityActive = false, LastFruitPickupTime = 0, IsTransitioningDimension = false,
    LastDimensionTransition = 0, IsChestTweening = false, OriginalWalkSpeed = nil, OriginalJumpPower = nil,
    LastProgressSnapshot = nil, HighSpeedWatcherConn = nil, LastQuestTitleSaved = nil, LastKnownProgress = nil,
    WasFramePresent = false, QuestJustCompleted = false, FastAttackTarget = nil, WalkBodyVelocity = nil,
    StatsRotationIndex = 1, StatsRemainders = {}, StatsLocked = false, LockedQuestTitle = nil,
    PatrolIndex = 1, PatrolLastSwitch = 0, PatrolTargetMob = nil, NoFallAntiGravity = nil,
    UnderwaterTransitionActive = false, SavedFarmState = nil, ResumeFarmAfterToggle = false,
    UnderwaterEntryLock = false, MobHealthTracker = {}, IgnoredInvincibleMobs = {},
    InvincibleCheckInterval = 0.25, InvincibleNoDamageThreshold = 4, Descending = false,
    DescentTargetY = nil, LastHorizontalVelocity = Vector3.zero, CachedSpinnerCloseBtn = nil,
    BossPatrolIndex = 1, BossPatrolLastSwitch = 0, BossKillCheckTarget = nil, WasFarmingBoss = false,
    DiagonalFlightActive = false, FruitCollectFlightSession = 0, FruitCollectTargetObject = nil,
    FishmanLordState = "IDLE", FishmanLordTransitionLock = false, BossArrivalSettleTime = 0,
    SkyIslandFlightLock = false, LastBossFlyStartTime = 0, LastBossDistance = math.huge,
}
BLOX_FRUIT_ID_MAP = {
    ["rocket fruit"] = "Rocket-Rocket", ["rocket"] = "Rocket-Rocket", ["spin fruit"] = "Spin-Spin", ["spin"] = "Spin-Spin",
    ["blade fruit"] = "Blade-Blade", ["blade"] = "Blade-Blade", ["spring fruit"] = "Spring-Spring", ["spring"] = "Spring-Spring",
    ["bomb fruit"] = "Bomb-Bomb", ["bomb"] = "Bomb-Bomb", ["smoke fruit"] = "Smoke-Smoke", ["smoke"] = "Smoke-Smoke",
    ["spike fruit"] = "Spike-Spike", ["spike"] = "Spike-Spike", ["flame fruit"] = "Flame-Flame", ["flame"] = "Flame-Flame",
    ["ice fruit"] = "Ice-Ice", ["ice"] = "Ice-Ice", ["sand fruit"] = "Sand-Sand", ["sand"] = "Sand-Sand",
    ["dark fruit"] = "Dark-Dark", ["dark"] = "Dark-Dark", ["eagle fruit"] = "Eagle-Eagle", ["eagle"] = "Eagle-Eagle",
    ["diamond fruit"] = "Diamond-Diamond", ["diamond"] = "Diamond-Diamond", ["light fruit"] = "Light-Light", ["light"] = "Light-Light",
    ["rubber fruit"] = "Rubber-Rubber", ["rubber"] = "Rubber-Rubber", ["ghost fruit"] = "Ghost-Ghost", ["ghost"] = "Ghost-Ghost",
    ["magma fruit"] = "Magma-Magma", ["magma"] = "Magma-Magma", ["quake fruit"] = "Quake-Quake", ["quake"] = "Quake-Quake",
    ["buddha fruit"] = "Buddha-Buddha", ["buddha"] = "Buddha-Buddha", ["human: buddha"] = "Buddha-Buddha",
    ["love fruit"] = "Love-Love", ["love"] = "Love-Love", ["creation fruit"] = "Creation-Creation", ["creation"] = "Creation-Creation",
    ["spider fruit"] = "Spider-Spider", ["spider"] = "Spider-Spider", ["sound fruit"] = "Sound-Sound", ["sound"] = "Sound-Sound",
    ["phoenix fruit"] = "Phoenix-Phoenix", ["phoenix"] = "Phoenix-Phoenix", ["portal fruit"] = "Portal-Portal", ["portal"] = "Portal-Portal",
    ["lightning fruit"] = "Lightning-Lightning", ["lightning"] = "Lightning-Lightning", ["blizzard fruit"] = "Blizzard-Blizzard", ["blizzard"] = "Blizzard-Blizzard",
    ["gravity fruit"] = "Gravity-Gravity", ["gravity"] = "Gravity-Gravity", ["mammoth fruit"] = "Mammoth-Mammoth", ["mammoth"] = "Mammoth-Mammoth",
    ["t-rex fruit"] = "T-Rex-T-Rex", ["t-rex"] = "T-Rex-T-Rex", ["dough fruit"] = "Dough-Dough", ["dough"] = "Dough-Dough",
    ["shadow fruit"] = "Shadow-Shadow", ["shadow"] = "Shadow-Shadow", ["venom fruit"] = "Venom-Venom", ["venom"] = "Venom-Venom",
    ["control fruit"] = "Control-Control", ["control"] = "Control-Control", ["spirit fruit"] = "Spirit-Spirit", ["spirit"] = "Spirit-Spirit",
    ["gas fruit"] = "Gas-Gas", ["gas"] = "Gas-Gas", ["yeti fruit"] = "Yeti-Yeti", ["yeti"] = "Yeti-Yeti",
    ["tiger fruit"] = "Tiger-Tiger", ["tiger"] = "Tiger-Tiger", ["magnet fruit"] = "Magnet-Magnet", ["magnet"] = "Magnet-Magnet",
    ["kitsune fruit"] = "Kitsune-Kitsune", ["kitsune"] = "Kitsune-Kitsune", ["dragon fruit"] = "Dragon-Dragon", ["dragon"] = "Dragon-Dragon"
}
local function isCombatFruit(tool)
    if not tool or not tool:IsA("Tool") then return false end
    if tool:FindFirstChild("Skills") or tool:FindFirstChild("Moves") or tool:FindFirstChild("Cooldown") or tool:FindFirstChild("SkillFrames") or tool:FindFirstChild("CombatScript") then return true end
    return false
end
local function isPhysicalFruit(tool)
    if not tool or not tool:IsA("Tool") then return false end
    if isCombatFruit(tool) then return false end
    local n = tool.Name:lower()
    local isPortal = (n == "portal fruit" or n == "portal")
    if not isPortal then
        if n:find("portal") or n:find("rift") or n:find("dimension") or n:find("key") or n:find("flower") or n:find("chest") or n:find("fist") or n:find("chalice") or n:find("boat") then return false end
    end
    if tool:FindFirstChild("Eat") or tool:FindFirstChild("Drop") or tool:FindFirstChild("EatRemote") or tool:FindFirstChild("EatScript") or tool:FindFirstChild("EatFunction") then return true end
    local tip = (tool.ToolTip or ""):lower()
    if tip == "blox fruit" or tip:find("fruit") or n:find("fruit") or BLOX_FRUIT_ID_MAP[n] then
        local h = tool:FindFirstChild("Handle") or tool:FindFirstChild("Fruit") or tool:FindFirstChildWhichIsA("BasePart")
        -- Leaked by SL | Join our Discord for more leaked sources: https://discord.gg/zNyHGU6eUK
        if h then return true end
    end
    return false
end
local function fireClose(btn)
    if not btn or not btn.Parent then return false end
    pcall(firesignal, btn.Activated)
    pcall(firesignal, btn.MouseButton1Click)
    return true
end
local function tryClose()
    local btn = State.CachedSpinnerCloseBtn
    if btn and btn.Parent then fireClose(btn) return true end
    local pg = plr:FindFirstChild("PlayerGui")
    if not pg then return false end -- SL | Source Leak [https://discord.gg/zNyHGU6eUK]
    local sp = pg:FindFirstChild("SpinnerWindow")
    if not sp then return false end
    local above = sp:FindFirstChild("AboveSpinner")
    if not above then return false end
    local nav = above:FindFirstChild("Navigation")
    if not nav then return false end
    local cb = nav:FindFirstChild("CloseButton")
    if cb then
        State.CachedSpinnerCloseBtn = cb
        fireClose(cb)
        return true
    end
    return false
end
task.spawn(function()
    local pg = plr:WaitForChild("PlayerGui", 5)
    if not pg then return end
    pg.DescendantAdded:Connect(function(d)
        if d.Name == "CloseButton" and (d:IsA("TextButton") or d:IsA("ImageButton") or d:IsA("GuiButton")) then
            local p, gp = d.Parent, d.Parent and d.Parent.Parent
            if p and gp and p.Name == "Navigation" and gp.Name == "AboveSpinner" then
                State.CachedSpinnerCloseBtn = d
                task.defer(function() fireClose(d) end)
            end
        end
    end)
    pg.ChildAdded:Connect(function(c)
        if c.Name == "SpinnerWindow" then
            task.spawn(function()
                local i = 0
                while i < 500 and not State.IsScriptDestroyed do
                    i = i + 1
                    local above = c:FindFirstChild("AboveSpinner")
                    if above then
                        local nav = above:FindFirstChild("Navigation")
                        if nav then
                            local cb = nav:FindFirstChild("CloseButton")
                            if cb then
                                State.CachedSpinnerCloseBtn = cb
                                fireClose(cb)
                                break
                            end
                        end
                    end
                end -- Join SL Discord: https://discord.gg/zNyHGU6eUK
            end)
        end
    end)
end)
pcall(function()
-- SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join SL for more script leaks
    Workspace.ChildAdded:Connect(function(c)
        task.wait(0.08)
        if c:IsA("Tool") or c:IsA("Model") then
            local h = c:FindFirstChild("Handle") or c:FindFirstChild("Fruit") or c:FindFirstChildWhichIsA("BasePart")
            if h then
                State.IgnoredGroundFruits[h] = nil
                State.GroundFruitTouchAttempts[h] = nil
            end
        end
    end)
end)
RARITY_COLORS = {
    ["Common"] = Color3.fromRGB(255, 255, 255), ["Uncommon"] = Color3.fromRGB(34, 197, 94), ["Rare"] = Color3.fromRGB(59, 130, 246),
    ["Legendary"] = Color3.fromRGB(168, 85, 247), ["Mythical"] = Color3.fromRGB(239, 68, 68)
}
FRUIT_INFO_DATABASE = {
    ["kitsune"] = {Name = "Kitsune", Rarity = "Mythical"}, ["dragon"] = {Name = "Dragon", Rarity = "Mythical"},
    ["tiger"] = {Name = "Tiger", Rarity = "Mythical"}, ["spirit"] = {Name = "Spirit", Rarity = "Mythical"},
    ["control"] = {Name = "Control", Rarity = "Mythical"}, ["venom"] = {Name = "Venom", Rarity = "Mythical"},
    ["shadow"] = {Name = "Shadow", Rarity = "Mythical"}, ["dough"] = {Name = "Dough", Rarity = "Mythical"},
    ["trex"] = {Name = "T-Rex", Rarity = "Mythical"}, ["mammoth"] = {Name = "Mammoth", Rarity = "Mythical"},
    ["gas"] = {Name = "Gas", Rarity = "Mythical"}, ["yeti"] = {Name = "Yeti", Rarity = "Mythical"},
    ["blizzard"] = {Name = "Blizzard", Rarity = "Legendary"}, ["sound"] = {Name = "Sound", Rarity = "Legendary"},
    ["phoenix"] = {Name = "Phoenix", Rarity = "Legendary"}, ["portal"] = {Name = "Portal", Rarity = "Legendary"},
    ["lightning"] = {Name = "Lightning", Rarity = "Legendary"}, ["spider"] = {Name = "Spider", Rarity = "Legendary"},
    ["love"] = {Name = "Love", Rarity = "Legendary"}, ["quake"] = {Name = "Quake", Rarity = "Legendary"},
    ["buddha"] = {Name = "Buddha", Rarity = "Legendary"}, ["gravity"] = {Name = "Gravity", Rarity = "Legendary"},
    ["magma"] = {Name = "Magma", Rarity = "Rare"}, ["ghost"] = {Name = "Ghost", Rarity = "Rare"},
    ["creation"] = {Name = "Creation", Rarity = "Rare"}, ["rubber"] = {Name = "Rubber", Rarity = "Rare"},
    ["light"] = {Name = "Light", Rarity = "Rare"}, ["diamond"] = {Name = "Diamond", Rarity = "Rare"},
    ["dark"] = {Name = "Dark", Rarity = "Uncommon"}, ["sand"] = {Name = "Sand", Rarity = "Uncommon"},
    ["ice"] = {Name = "Ice", Rarity = "Uncommon"}, ["eagle"] = {Name = "Eagle", Rarity = "Uncommon"},
    ["flame"] = {Name = "Flame", Rarity = "Uncommon"}, ["spike"] = {Name = "Spike", Rarity = "Common"},
    ["smoke"] = {Name = "Smoke", Rarity = "Common"}, ["bomb"] = {Name = "Bomb", Rarity = "Common"},
    ["spring"] = {Name = "Spring", Rarity = "Common"}, ["blade"] = {Name = "Blade", Rarity = "Common"},
    ["spin"] = {Name = "Spin", Rarity = "Common"}, ["rocket"] = {Name = "Rocket", Rarity = "Common"}
}
local function normFruitKey(raw)
    if not raw or type(raw) ~= "string" then return "" end
    return (raw:lower():gsub("%-.*", ""):gsub(" fruit", ""):gsub("fruit", ""):gsub(" physical", ""):gsub(" inventory", ""):gsub("%(.-%)", ""):gsub("[^%w]", ""))
end
local function getFruitDetails(raw)
    local k = normFruitKey(raw)
    if FRUIT_INFO_DATABASE[k] then
        local d = FRUIT_INFO_DATABASE[k]
        return d.Name, d.Rarity, RARITY_COLORS[d.Rarity]
    end
    for kk, v in pairs(FRUIT_INFO_DATABASE) do
        if k:find(kk) or kk:find(k) then return v.Name, v.Rarity, RARITY_COLORS[v.Rarity] end
    end
    return raw or "Fruit", "Common", RARITY_COLORS["Common"]
end
local function getFruitDisplay(raw) return getFruitDetails(raw) end
local function mysteryColor()
    local t = tick()
    local r = math.floor((math.sin(t * 1.2) * 0.5 + 0.5) * 255)
    local g = math.floor((math.sin(t * 1.7 + 2.0) * 0.5 + 0.5) * 255)
    local b = math.floor((math.sin(t * 2.3 + 4.0) * 0.5 + 0.5) * 255)
    return Color3.fromRGB(r, g, b)
end
StoredFruitsCache = {}
LastStoredFruitsFetch = 0
FullFruitStorageCache = {}
local function getMaxFruitCap()
    local cap = 1
    -- Source leaked by SL | Get more free hub sources at https://discord.gg/zNyHGU6eUK
    pcall(function()
        local data = plr:FindFirstChild("Data")
        if data then
            if data:FindFirstChild("FruitCapacity") then cap = tonumber(data.FruitCapacity.Value) or cap
            elseif data:FindFirstChild("FruitStorage") then cap = tonumber(data.FruitStorage.Value) or cap
            elseif data:FindFirstChild("MaxFruits") then cap = tonumber(data.MaxFruits.Value) or cap end
        end
        if RS:FindFirstChild("Remotes") and RS.Remotes:FindFirstChild("CommF_") then
            local s = RS.Remotes.CommF_:InvokeServer("GetFruitCapacity")
            if type(s) == "number" and s > 0 then cap = s end
        end
    end)
    return cap
end
local function getStoredFruits()
    local now = tick()
    if now - LastStoredFruitsFetch < 3 and StoredFruitsCache and next(StoredFruitsCache) ~= nil then return StoredFruitsCache end
    StoredFruitsCache = {}
    pcall(function()
        if RS:FindFirstChild("Remotes") and RS.Remotes:FindFirstChild("CommF_") then --[[ Leaked By SL | https://discord.gg/zNyHGU6eUK ]]
            local inv = RS.Remotes.CommF_:InvokeServer("getInventoryFruits")
            if type(inv) == "table" then
                for _, item in pairs(inv) do
                    local name = item.Name or item[1] or item.Fruit or ""
                    local count = tonumber(item.Count or item.Amount or item[2]) or 1
                    if name ~= "" then StoredFruitsCache[normFruitKey(name)] = count end
                end
            end
        end
    end)
    LastStoredFruitsFetch = now
    return StoredFruitsCache
end
local function hasStorageSpace(raw)
    if not raw or raw == "" then return false end
    local k = normFruitKey(raw)
    if FullFruitStorageCache[k] and tick() < FullFruitStorageCache[k] then return false end
    local cap = getMaxFruitCap()
    local inv = getStoredFruits()
    if (inv[k] or 0) >= cap then
    	if ("Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]") ~= "" then
    		local _ = ("Leaked By " .. "SL | " .. "https://discord.gg/zNy" .. "HGU6eUK")
    	end
        FullFruitStorageCache[k] = tick() + 30
        return false
    end
    return true
end
local function syncFruitInv()
    StoredFruitsCache = {}
    LastStoredFruitsFetch = 0
    pcall(function()
        local r = RS:FindFirstChild("Remotes")
        local cf = r and r:FindFirstChild("CommF_")
        if not cf then return end
        cf:InvokeServer("getInventoryFruits")
        cf:InvokeServer("getInventory")
    end)
    getStoredFruits()
end
local function dismissFruitDialog(forceStore)
    pcall(function()
        local pg = plr:FindFirstChild("PlayerGui")
        if not pg then return end
        for _, obj in ipairs(pg:GetDescendants()) do
            local isPrompt = false
            if obj:IsA("TextLabel") or obj:IsA("TextButton") then
                local t = obj.Text:lower()
                -- [SL] Leaked By SL | Source Leak - Join https://discord.gg/zNyHGU6eUK
                if t:find("what do you wish to do with this blox fruit") or t:find("wish to do with this") or t:find("what do you wish to do") then isPrompt = true end
            end
            if isPrompt then
                local cont = obj.Parent
                while cont and not (cont:IsA("ScreenGui") or cont.Name == "PlayerGui") do
                    if cont:IsA("Frame") or cont:IsA("CanvasGroup") or cont:IsA("ImageLabel") then
                        if forceStore then
                            for _, ch in ipairs(cont:GetDescendants()) do
                                if ch:IsA("TextButton") and ch.Text == "Store" then
                                    pcall(function() firesignal(ch.Activated) end)
                                    pcall(function() firesignal(ch.MouseButton1Click) end)
                                    task.wait(0.05)
                                    break
                                end
                            end
                        end
                        for _, ch in ipairs(cont:GetDescendants()) do
                            if ch:IsA("TextButton") and (ch.Text == "Nevermind" or ch.Text:lower():find("nevermind") or ch.Text == "Cancel") then
                                pcall(function() firesignal(ch.Activated) end)
                                pcall(function() firesignal(ch.MouseButton1Click) end)
                                task.wait(0.05)
                                break
                            end
                        end
                        cont.Visible = false
                        break
                    end
                    cont = cont.Parent
                end
            end
        end
    end)
end
local function storeAllHeldFruits()
    pcall(function()
        local char = plr.Character
        local bp = plr:FindFirstChild("Backpack")
        local r = RS:FindFirstChild("Remotes")
        local cf = r and r:FindFirstChild("CommF_")
        if not cf then return end
        local function tryStore(tool)
            if not tool or not tool:IsA("Tool") then return false end
            if not isPhysicalFruit(tool) then return false end
            if isCombatFruit(tool) then return false end
            local orig = tool:GetAttribute("OriginalName") or tool:GetAttribute("FruitName") or tool.Name
            local clean = tool.Name:gsub(" Fruit", "")
            local disp = getFruitDisplay(orig)
            local ok = hasStorageSpace(orig) or hasStorageSpace(clean) or hasStorageSpace(disp)
            if not ok then return false end
            State.IsStoringFruitActive = true
            if char then
                local hum = char:FindFirstChildOfClass("Humanoid")
                if hum and tool.Parent == char then pcall(function() hum:UnequipTools() end) end
            end
            local stored = false
            local cands = { orig, tool.Name, clean, disp }
            local seen = {}
            for _, nm in ipairs(cands) do
                if nm and nm ~= "" and not seen[nm] then
                    seen[nm] = true
                    pcall(function()
                        local res = cf:InvokeServer("StoreFruit", nm, tool)
                        if res == true or res == "Success" then stored = true end
                    end)
                    if stored then break end
                    -- Join SL Discord for more open-source & leaked scripts: https://discord.gg/zNyHGU6eUK
                end
            end
            if not stored then
                pcall(function()
                    local res = cf:InvokeServer("StoreFruit", orig)
                    if res == true or res == "Success" then stored = true end
                end)
            end
            dismissFruitDialog(true)
            if stored and (tool.Parent == char or tool.Parent == bp) then
                FullFruitStorageCache[normFruitKey(clean)] = tick() + 60
            elseif stored then
                LastStoredFruitsFetch = 0
            end
            State.IsStoringFruitActive = false
            return stored
        end
        local cnt = 0
        if char then for _, t in ipairs(char:GetChildren()) do if t:IsA("Tool") and tryStore(t) then cnt = cnt + 1 end end end
        if bp then for _, t in ipairs(bp:GetChildren()) do if t:IsA("Tool") and tryStore(t) then cnt = cnt + 1 end end end
        if cnt > 0 then LastStoredFruitsFetch = 0 end
    end)
end
task.spawn(function()
    task.wait(2)
    syncFruitInv()
    while not State.IsScriptDestroyed do
        task.wait(20)
        if Cfg.AutoCollectFruit or Cfg.AutoStoreFruit then syncFruitInv() end
    end
end)
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.25)
        if Cfg.AutoStoreFruit then
            pcall(function()
                local char = plr.Character
                local bp = plr:FindFirstChild("Backpack")
                if not char or not bp then return end
                local now = tick()
                local needs = false
                for _, t in ipairs(char:GetChildren()) do
                    if t:IsA("Tool") and isPhysicalFruit(t) and not isCombatFruit(t) then
                        if now - (State.FruitStoreCooldown[t] or 0) > 0.6 then
                            State.FruitStoreCooldown[t] = now
                            needs = true
                            break
                        end
                    end
                end
                if not needs then
                    for _, t in ipairs(bp:GetChildren()) do
                        if t:IsA("Tool") and isPhysicalFruit(t) and not isCombatFruit(t) then
                            if now - (State.FruitStoreCooldown[t] or 0) > 0.6 then
                                State.FruitStoreCooldown[t] = now
                                needs = true
                                break
                            end
                        end
                    end
                end
                if needs then storeAllHeldFruits() end
            end)
        end
    end
    -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] | More leaks in our Discord
end)
local function cacheCharParts()
    State.CachedCharacterParts = {}
    pcall(function()
        local char = plr.Character
        if char then
            for _, p in ipairs(char:GetChildren()) do
                if p:IsA("BasePart") then table.insert(State.CachedCharacterParts, p) end
            end
        end
    end)
end
pcall(function() plr.CharacterAdded:Connect(function() task.wait(0.5) cacheCharParts() end) end)
cacheCharParts()
local function ensureBodyMovers()
    local char = plr.Character
    if not char then return nil end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    local hum = char:FindFirstChildOfClass("Humanoid")
    if not hrp then return nil end
    if not State.BodyVelocity or State.BodyVelocity.Parent ~= hrp then
        if State.BodyVelocity then pcall(function() State.BodyVelocity:Destroy() end) end
        State.BodyVelocity = Instance.new("BodyVelocity")
        State.BodyVelocity.Name = "Irish_BV"
        State.BodyVelocity.MaxForce = Vector3.new(9e9, 9e9, 9e9)
        State.BodyVelocity.Velocity = Vector3.zero
        State.BodyVelocity.Parent = hrp
    end
    if not State.BodyGyro or State.BodyGyro.Parent ~= hrp then
        if State.BodyGyro then pcall(function() State.BodyGyro:Destroy() end) end
        State.BodyGyro = Instance.new("BodyGyro")
        State.BodyGyro.Name = "Irish_BG"
        State.BodyGyro.MaxTorque = Vector3.new(0, 9e9, 0)
        State.BodyGyro.P = 1e4
        State.BodyGyro.D = 1000
        State.BodyGyro.CFrame = CFrame.new(hrp.Position) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
        State.BodyGyro.Parent = hrp
    end
    if hum and hum.Health > 0 then
        pcall(function()
            hum.PlatformStand = false
            hum.AutoRotate = false
            hum:SetStateEnabled(Enum.HumanoidStateType.Running, false)
            hum:SetStateEnabled(Enum.HumanoidStateType.RunningNoPhysics, false)
            hum:SetStateEnabled(Enum.HumanoidStateType.Climbing, false)
            hum:SetStateEnabled(Enum.HumanoidStateType.Landed, false)
            hum:SetStateEnabled(Enum.HumanoidStateType.Freefall, true)
            if hum:GetState() ~= Enum.HumanoidStateType.Freefall then hum:ChangeState(Enum.HumanoidStateType.Freefall) end
        end)
    end -- Leaked by SL | Join https://discord.gg/zNyHGU6eUK for more leaks
    return State.BodyVelocity
end
local function startAntiGrav()
    local char = plr.Character
    if not char then return end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    if not hrp then return end
    if State.NoFallAntiGravity and State.NoFallAntiGravity.Parent == hrp then return end
    if State.NoFallAntiGravity then pcall(function() State.NoFallAntiGravity:Destroy() end) end
    State.NoFallAntiGravity = Instance.new("BodyForce")
    State.NoFallAntiGravity.Name = "Irish_AntiGravity"
    State.NoFallAntiGravity.Force = Vector3.new(0, workspace.Gravity * 3.0, 0)
    State.NoFallAntiGravity.Parent = hrp
end
local function stopAntiGrav()
--[[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join SL Discord ]]
    if State.NoFallAntiGravity then
        pcall(function() State.NoFallAntiGravity:Destroy() end)
        State.NoFallAntiGravity = nil
    end
end
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.1)
        if State.IsMoving and State.BodyVelocity and State.BodyVelocity.Parent then startAntiGrav()
        elseif not State.IsMoving then stopAntiGrav() end
    end
end)
FROZEN_TAG = "_IrishFrozen"
local function saveOrigPart(part)
    if not part:GetAttribute("Irish_OrigAnchored") then part:SetAttribute("Irish_OrigAnchored", part.Anchored) end
    if not part:GetAttribute("Irish_OrigCanCollide") then part:SetAttribute("Irish_OrigCanCollide", part.CanCollide) end
    if not part:GetAttribute("Irish_OrigCanTouch") then part:SetAttribute("Irish_OrigCanTouch", part.CanTouch) end
    if not part:GetAttribute("Irish_OrigCanQuery") then part:SetAttribute("Irish_OrigCanQuery", part.CanQuery) end
end
local function restoreOrigPart(part)
    if part:GetAttribute("Irish_OrigAnchored") ~= nil then pcall(function() part.Anchored = part:GetAttribute("Irish_OrigAnchored") end) part:SetAttribute("Irish_OrigAnchored", nil) end
    if part:GetAttribute("Irish_OrigCanCollide") ~= nil then pcall(function() part.CanCollide = part:GetAttribute("Irish_OrigCanCollide") end) part:SetAttribute("Irish_OrigCanCollide", nil) end
    if part:GetAttribute("Irish_OrigCanTouch") ~= nil then pcall(function() part.CanTouch = part:GetAttribute("Irish_OrigCanTouch") end) part:SetAttribute("Irish_OrigCanTouch", nil) end
    if part:GetAttribute("Irish_OrigCanQuery") ~= nil then pcall(function() part.CanQuery = part:GetAttribute("Irish_OrigCanQuery") end) part:SetAttribute("Irish_OrigCanQuery", nil) end
end
local function saveOrigHum(hum)
    if not hum:GetAttribute("Irish_OrigWalkSpeed") then hum:SetAttribute("Irish_OrigWalkSpeed", hum.WalkSpeed) end
    if not hum:GetAttribute("Irish_OrigJumpPower") then hum:SetAttribute("Irish_OrigJumpPower", hum.JumpPower) end
    if not hum:GetAttribute("Irish_OrigAutoRotate") then hum:SetAttribute("Irish_OrigAutoRotate", hum.AutoRotate) end
end -- [SL Source Leak] https://discord.gg/zNyHGU6eUK
local function restoreOrigHum(hum)
    if hum:GetAttribute("Irish_OrigWalkSpeed") ~= nil then pcall(function() hum.WalkSpeed = hum:GetAttribute("Irish_OrigWalkSpeed") end) hum:SetAttribute("Irish_OrigWalkSpeed", nil) end
    if hum:GetAttribute("Irish_OrigJumpPower") ~= nil then pcall(function() hum.JumpPower = hum:GetAttribute("Irish_OrigJumpPower") end) hum:SetAttribute("Irish_OrigJumpPower", nil) end
    if hum:GetAttribute("Irish_OrigAutoRotate") ~= nil then pcall(function() hum.AutoRotate = hum:GetAttribute("Irish_OrigAutoRotate") end) hum:SetAttribute("Irish_OrigAutoRotate", nil) end
end
local function stopMobAnims(hum)
    local an = hum:FindFirstChildOfClass("Animator")
    if an then for _, t in ipairs(an:GetPlayingAnimationTracks()) do pcall(function() t:Stop(0) end) end end
end
local function freezeMob(mob)
    if State.IsScriptDestroyed or not mob or not mob.Parent then return end
    if mob:GetAttribute(FROZEN_TAG) == true then
        local e = mob:FindFirstChild("HumanoidRootPart")
        if e and State.FrozenPositions[mob] then e.CFrame = State.FrozenPositions[mob] end
        return
    end
    local eHrp = mob:FindFirstChild("HumanoidRootPart")
    local eHum = mob:FindFirstChildOfClass("Humanoid")
    if not eHrp or not eHum or eHum.Health <= 0 then return end
    State.FrozenPositions[mob] = eHrp.CFrame
    saveOrigPart(eHrp)
    saveOrigHum(eHum)
    pcall(function()
        eHrp.Anchored = true
        eHrp.AssemblyLinearVelocity = Vector3.zero
        eHrp.AssemblyAngularVelocity = Vector3.zero
        eHrp.Velocity = Vector3.zero
        eHrp.RotVelocity = Vector3.zero
    end)
    pcall(function()
        eHum.PlatformStand = true
        eHum.WalkSpeed = 0
        eHum.JumpPower = 0
        eHum.AutoRotate = false
        eHum:ChangeState(Enum.HumanoidStateType.Physics)
        --[=[ SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join our Discord for more leaks ]=]
    end)
    stopMobAnims(eHum)
    for _, p in ipairs(mob:GetChildren()) do
        if p:IsA("BasePart") and p ~= eHrp then
            saveOrigPart(p)
            pcall(function()
                p.CanCollide = false
                p.AssemblyLinearVelocity = Vector3.zero
                p.AssemblyAngularVelocity = Vector3.zero
            end) --[=[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] ]=]
        end
    end
    mob:SetAttribute(FROZEN_TAG, true)
end
local function unfreezeMob(mob)
    if mob and mob.Parent then
        pcall(function()
            local eHrp = mob:FindFirstChild("HumanoidRootPart")
            local eHum = mob:FindFirstChildOfClass("Humanoid")
            if eHrp then
                eHrp.Anchored = false
                eHrp.AssemblyLinearVelocity = Vector3.zero
                eHrp.AssemblyAngularVelocity = Vector3.zero
                restoreOrigPart(eHrp)
            end
            if eHum then
                eHum.PlatformStand = false
                restoreOrigHum(eHum)
                eHum:ChangeState(Enum.HumanoidStateType.Running)
            end
            for _, p in ipairs(mob:GetChildren()) do
                if p:IsA("BasePart") and p ~= eHrp then restoreOrigPart(p) end
            end
            mob:SetAttribute(FROZEN_TAG, nil)
        end)
    end
    State.FrozenPositions[mob] = nil
end
local function clearAllFreezes()
    for m, _ in pairs(State.FrozenPositions) do
        if m and m.Parent then pcall(function() unfreezeMob(m) end) end
    end
    State.FrozenPositions = {}
end
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.05)
        if next(State.FrozenPositions) then
            for m, cf in pairs(State.FrozenPositions) do
                if not m or not m.Parent then
                    State.FrozenPositions[m] = nil
                else
                    local eHrp = m:FindFirstChild("HumanoidRootPart")
                    local eHum = m:FindFirstChildOfClass("Humanoid")
                    if not eHrp or not eHum then -- Source Leak (SL) | Join our Discord: https://discord.gg/zNyHGU6eUK
                        State.FrozenPositions[m] = nil
                    elseif eHum.Health <= 0 then
                        unfreezeMob(m)
                    else
                        pcall(function()
                            if eHrp.Anchored == false then eHrp.Anchored = true end
                            eHrp.CFrame = cf
                            eHrp.AssemblyLinearVelocity = Vector3.zero
                            eHrp.AssemblyAngularVelocity = Vector3.zero
                        end)
                        --[==[ Leaked By SL | Source Leak | Join https://discord.gg/zNyHGU6eUK for free sources ]==]
                        pcall(function()
                            if eHum.PlatformStand == false then eHum.PlatformStand = true end
                            if eHum.WalkSpeed ~= 0 then eHum.WalkSpeed = 0 end
                            if eHum.JumpPower ~= 0 then eHum.JumpPower = 0 end
                        end)
                    end
                end
            end
        end
    end
end)
local function restoreCharCollisions(char)
    if not char then return end
    pcall(function()
        for _, p in ipairs(char:GetDescendants()) do
            if p:IsA("BasePart") then
                local n = p.Name
                if n == "UpperTorso" or n == "LowerTorso" or n == "Torso" or n == "Head" then p.CanCollide = true else p.CanCollide = false end
                p.CanTouch = true
                p.CanQuery = true
            end
        end
    end)
end
local function removePlatformBeneath()
    pcall(function()
        local char = plr.Character
        if char then
            for _, o in ipairs(char:GetChildren()) do
                if o.Name == "Platform" or o.Name == "Irish_Platform" or (o:IsA("BasePart") and o.Name:lower():find("platform")) then pcall(function() o:Destroy() end) end
            end
        end
        for _, o in ipairs(Workspace:GetChildren()) do
            if o.Name == "Platform" or o.Name == "Irish_Platform" or (o:IsA("BasePart") and o.Name:lower():find("platform")) then pcall(function() o:Destroy() end) end
        end --[==[ SL | Source Leak: https://discord.gg/zNyHGU6eUK ]==]
    end)
end
local function isMovementActive()
    if State.FruitPriorityActive then return false end
    return Cfg.AutoFarmBosses or Cfg.AutoFarmLevel or Cfg.AutoFarmNearest or Cfg.AutoChestTween or (Cfg.AutoCollectFruit and State.IsCollectingFruitMoving) or Cfg.AutoTeleportIsland
end
local function isUsingFlightSkill()
    local char = plr.Character
    if not char then return false end
    local hum = char:FindFirstChildOfClass("Humanoid")
    local tool = char:FindFirstChildOfClass("Tool")
    if not hum then return false end
    if tool and isCombatFruit(tool) then return true end
    local state = hum:GetState()
    if (state == Enum.HumanoidStateType.Freefall or state == Enum.HumanoidStateType.Physics) 
       and not State.IsMoving and not State.BodyVelocity then
        return true
    end
    return false
end
local function straightenChar(char, hrp)
    if not hrp then return end
    pcall(function()
        local y = hrp.Orientation.Y
        hrp.CFrame = CFrame.new(hrp.Position) * CFrame.Angles(0, math.rad(y), 0)
        hrp.AssemblyLinearVelocity = Vector3.zero
        hrp.AssemblyAngularVelocity = Vector3.zero
        hrp.Velocity = Vector3.zero
        hrp.RotVelocity = Vector3.zero
        local hum = char and char:FindFirstChildOfClass("Humanoid")
        -- Want more leaked hubs? Join SL | Source Leak: https://discord.gg/zNyHGU6eUK
        if hum and hum.Health > 0 and not State.IsMoving then
            local rp = RaycastParams.new()
            rp.FilterDescendantsInstances = {char}
            rp.FilterType = RaycastFilterType.Exclude
            local hit = Workspace:Raycast(hrp.Position, Vector3.new(0, -10, 0), rp)
            if hit and hit.Position then
                local hip = (hum.HipHeight and hum.HipHeight > 0) and hum.HipHeight or 2.0
                local tY = hit.Position.Y + hip + (hrp.Size.Y / 2)
                if math.abs(hrp.Position.Y - tY) < 4.5 then
                    hrp.CFrame = CFrame.new(hrp.Position.X, tY, hrp.Position.Z) * CFrame.Angles(0, math.rad(y), 0)
                end
            end
        end
    end)
end -- More free leaks at SL Discord: https://discord.gg/zNyHGU6eUK
local function stopBodyMovers()
    if isUsingFlightSkill() and not State.IsMoving then return end
    pcall(function()
        State.IsMoving = false
        State.IsHoveringAtTarget = false
        State.LastVelocityMagnitude = 0
        State.Descending = false
        State.DescentTargetY = nil
        State.LastHorizontalVelocity = Vector3.zero
        State.DiagonalFlightActive = false
        stopAntiGrav()
        if State.BodyVelocity then pcall(function() State.BodyVelocity:Destroy() end) State.BodyVelocity = nil end
        if State.BodyGyro then pcall(function() State.BodyGyro:Destroy() end) State.BodyGyro = nil end
        if State.WalkBodyVelocity then pcall(function() State.WalkBodyVelocity:Destroy() end) State.WalkBodyVelocity = nil end
        removePlatformBeneath()
        local char = plr.Character
        if char then
            local hrp = char:FindFirstChild("HumanoidRootPart")
            local hum = char:FindFirstChildOfClass("Humanoid")
            if hrp then
                hrp.Anchored = false
                hrp.CanCollide = false
                for _, o in ipairs(hrp:GetChildren()) do
                    if o.Name == "Irish_BV" or o.Name == "Irish_BG" or o.Name == "Irish_AntiGravity" then pcall(function() o:Destroy() end) end
                end
            end
            for _, o in ipairs(char:GetDescendants()) do
                if o.Name == "Irish_BV" or o.Name == "Irish_BG" or o.Name == "Irish_AntiGravity" then pcall(function() o:Destroy() end) end
            end
            if hum and hum.Health > 0 then
                pcall(function()
                    hum.PlatformStand = false
                    hum.Sit = false
                    hum.AutoRotate = true
                    if Cfg.PlayerMovementEnabled then hum.WalkSpeed = 16 hum.JumpPower = Cfg.JumpPowerValue
                    else hum.WalkSpeed = 16 hum.JumpPower = 50 end
                    hum:SetStateEnabled(Enum.HumanoidStateType.Running, true)
                    hum:SetStateEnabled(Enum.HumanoidStateType.RunningNoPhysics, true)
                    hum:SetStateEnabled(Enum.HumanoidStateType.Climbing, true)
                    hum:SetStateEnabled(Enum.HumanoidStateType.Swimming, true)
                    hum:SetStateEnabled(Enum.HumanoidStateType.Freefall, true)
                    hum:SetStateEnabled(Enum.HumanoidStateType.Jumping, true)
                    hum:SetStateEnabled(Enum.HumanoidStateType.Landed, true)
                    hum:SetStateEnabled(Enum.HumanoidStateType.GettingUp, true)
                    local an = hum:FindFirstChildOfClass("Animator")
                    if an then
                        for _, t in ipairs(an:GetPlayingAnimationTracks()) do
                            local nm = (t.Animation and t.Animation.Name:lower()) or ""
                            if nm:find("fly") or nm:find("float") then pcall(function() t:Stop(0.1) end) end
                        end
                        -- Free leaked sources daily in SL Discord: https://discord.gg/zNyHGU6eUK
                    end
                    hum:ChangeState(Enum.HumanoidStateType.Running)
                end)
            end
            straightenChar(char, hrp)
            restoreCharCollisions(char)
        end
    end)
end
local function resetPhysics()
    pcall(function()
        State.IsHoveringAtTarget = false
        State.DiagonalFlightActive = false
        stopBodyMovers()
        removePlatformBeneath()
        clearAllFreezes()
        local char = plr.Character
        if char then
            local hrp = char:FindFirstChild("HumanoidRootPart")
            pcall(function() plr.DevCameraOcclusionMode = Enum.DevCameraOcclusionMode.Zoom end)
            straightenChar(char, hrp)
            restoreCharCollisions(char)
        end
    end)
end
local function setCharNoclip(char)
    if not char then return end
    pcall(function()
        for _, o in ipairs(char:GetDescendants()) do
            if o:IsA("BasePart") then
                o.CanCollide = false
                o.CanTouch = true
                o.CanQuery = true
            end
        end
    end)
end
local function initNoclip()
    if State.Connections.Noclip then return end
    local wasFlying = false -- Leaked By SL | Join https://discord.gg/zNyHGU6eUK
    State.Connections.Noclip = RunService.Stepped:Connect(function()
        if isUsingFlightSkill() then return end
        local char = plr.Character
        if not char then return end
        local hrp = char:FindFirstChild("HumanoidRootPart")
        if not hrp then return end
        local hum = char:FindFirstChildOfClass("Humanoid")
        local flying = (State.BodyVelocity ~= nil and State.BodyVelocity.Parent == hrp and (State.IsMoving or isMovementActive()))
        if flying then
            wasFlying = true
            setCharNoclip(char)
            if hum and hum.Health > 0 then
                hum.PlatformStand = false
                hum.AutoRotate = false
                pcall(function()
                    hum:SetStateEnabled(Enum.HumanoidStateType.Running, false)
                    hum:SetStateEnabled(Enum.HumanoidStateType.RunningNoPhysics, false)
                    hum:SetStateEnabled(Enum.HumanoidStateType.Climbing, false)
                    hum:SetStateEnabled(Enum.HumanoidStateType.Landed, false)
                    hum:SetStateEnabled(Enum.HumanoidStateType.Freefall, true)
                    if hum:GetState() ~= Enum.HumanoidStateType.Freefall then hum:ChangeState(Enum.HumanoidStateType.Freefall) end
                end)
            end
        else
            if wasFlying then
            -- SL Source Leak | https://discord.gg/zNyHGU6eUK | Join the server for more leaks
                wasFlying = false
                if State.BodyGyro and State.BodyGyro.Parent == hrp then
                    State.BodyGyro.MaxTorque = Vector3.zero
                    pcall(function() State.BodyGyro:Destroy() end)
                    State.BodyGyro = nil
                end
                if hrp then straightenChar(char, hrp) end
                if hum and hum.Health > 0 then
                    hum.PlatformStand = false
                    hum.AutoRotate = true
                    pcall(function()
                        hum:SetStateEnabled(Enum.HumanoidStateType.Running, true)
                        hum:SetStateEnabled(Enum.HumanoidStateType.RunningNoPhysics, true)
                        hum:SetStateEnabled(Enum.HumanoidStateType.Climbing, true)
                        hum:SetStateEnabled(Enum.HumanoidStateType.Landed, true)
                        hum:SetStateEnabled(Enum.HumanoidStateType.GettingUp, true)
                        hum:ChangeState(Enum.HumanoidStateType.Running)
                    end)
                end
                restoreCharCollisions(char)
            end
        end
    end)
end
initNoclip()
State.Connections.AntiLandAnim = RunService.Stepped:Connect(function()
    if isUsingFlightSkill() then return end
    if not State.IsMoving and not isMovementActive() then return end
    local char = plr.Character
    if not char then return end
    local hum = char:FindFirstChildOfClass("Humanoid")
    if not hum or hum.Health <= 0 then return end
    local an = hum:FindFirstChildOfClass("Animator")
    if an then
        for _, t in ipairs(an:GetPlayingAnimationTracks()) do
            local nm = ""
            pcall(function() nm = (t.Animation and t.Animation.Name or ""):lower() end)
            if nm:find("land") or nm:find("impact") then pcall(function() t:Stop(0) end) end
        end
    end
end)
State.Connections.AntiJitter = RunService.RenderStepped:Connect(function()
    if not State.IsMoving and not isMovementActive() then
        local char = plr.Character
        if char then
            local hrp = char:FindFirstChild("HumanoidRootPart")
            if hrp then
                local bg = hrp:FindFirstChild("Irish_BG")
                local bv = hrp:FindFirstChild("Irish_BV")
                if bg or bv then
                    pcall(function() if bg then bg:Destroy() end if bv then bv:Destroy() end end)
                    State.BodyVelocity = nil
                    State.BodyGyro = nil
                end
            end
        end
    end
end)
State.Connections.AntiTilt = RunService.RenderStepped:Connect(function()
    if isUsingFlightSkill() then return end
    local char = plr.Character
    if not char then return end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    if not hrp then return end
    local s = false --[[ SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join Discord ]]
    -- Leaked by SL Community | Source Leak [https://discord.gg/zNyHGU6eUK]
    if State.IsMoving then s = true
    elseif isMovementActive() then s = true
    elseif State.BodyVelocity and State.BodyVelocity.Parent == hrp then s = true end
    if s then
        local yaw = math.rad(hrp.Orientation.Y)
        local upCF = CFrame.new(hrp.Position) * CFrame.Angles(0, yaw, 0)
        hrp.CFrame = upCF
        if State.BodyGyro and State.BodyGyro.Parent == hrp then
            local hd = Vector3.new(hrp.AssemblyLinearVelocity.X, 0, hrp.AssemblyLinearVelocity.Z)
            if hd.Magnitude > 2.0 then State.BodyGyro.CFrame = CFrame.lookAt(hrp.Position, hrp.Position + hd.Unit)
            else State.BodyGyro.CFrame = upCF end
        end
    end
end)
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.05)
        if Cfg.PlayerMovementEnabled then
            local char = plr.Character
            local hrp = char and char:FindFirstChild("HumanoidRootPart")
            local hum = char and char:FindFirstChildOfClass("Humanoid")
            if hrp and hum and hum.Health > 0 and not State.IsMoving then
                if hum.WalkSpeed ~= 16 then pcall(function() hum.WalkSpeed = 16 end) end
                local md = hum.MoveDirection
                if md.Magnitude > 0.05 then
                    if not State.WalkBodyVelocity or State.WalkBodyVelocity.Parent ~= hrp then
                        if State.WalkBodyVelocity then pcall(function() State.WalkBodyVelocity:Destroy() end) end
                        State.WalkBodyVelocity = Instance.new("BodyVelocity")
                        State.WalkBodyVelocity.Name = "Irish_WalkBV"
                        State.WalkBodyVelocity.MaxForce = Vector3.new(9e9, 0, 9e9)
                        -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
                        -- Join SL Discord for more leaked sources: https://discord.gg/zNyHGU6eUK
                        State.WalkBodyVelocity.P = 1250
                        State.WalkBodyVelocity.Parent = hrp
                    end
                    local ts = Cfg.WalkSpeedValue
                    State.WalkBodyVelocity.Velocity = Vector3.new(md.X * ts, 0, md.Z * ts)
                elseif State.WalkBodyVelocity then
                    State.WalkBodyVelocity.Velocity = Vector3.zero
                end
            end
        else
            if State.WalkBodyVelocity then
                pcall(function() State.WalkBodyVelocity:Destroy() end)
                State.WalkBodyVelocity = nil
            end
        end -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
    end
end)
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.15)
        if not Cfg.AutoSecondSeaQuest and not State.FruitPriorityActive then
            local busy = Cfg.AutoFarmLevel or Cfg.AutoFarmNearest or Cfg.AutoChestTween
                or Cfg.AutoTeleportIsland or Cfg.AutoFarmBosses
                or (Cfg.AutoCollectFruit and State.IsCollectingFruitMoving)
            if not busy then
            	do
            		local _ = string.format("Leaked By %s | Join https://discord.gg/%s", "SL", "zNyHGU6eUK")
            	end -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
                if State.IsMoving or State.BodyVelocity or State.BodyGyro or State.NoFallAntiGravity then pcall(stopBodyMovers) end
            end
        end
    end
end)
local function getCommF()
    local r = RS:FindFirstChild("Remotes")
    if r and r:FindFirstChild("CommF_") then return r.CommF_ end
    if RS:FindFirstChild("CommF_") then return RS.CommF_ end
    return nil
    -- [Source Leak] Leaked By SL | Join Discord: https://discord.gg/zNyHGU6eUK
end
UW_ENTRY_GATE = CFrame.new(4034.11, 35, -1821.84)
UW_EXIT_GATE = CFrame.new(61168.70, 35, 1940.10)
UW_INSIDE_POS = Vector3.new(61163.8515625, 11.680007934570312, 1819.7840576171875)
UW_OUTSIDE_POS = Vector3.new(3864.68798828125, 6.73699951171875, -1926.2139892578125)
UW_X_THRESHOLD = 55000
UW_GATE_OFFSET = Vector3.new(0, 4, 0)
local MIN_H_RATIO = 0.55
local MAX_V_RATIO = 0.65
local function calcDiagVel(curPos, tgtPos, speed)
    if not validNum(curPos.X) or not validNum(tgtPos.X) then return Vector3.zero end
    local dx = tgtPos.X - curPos.X
    local dy = tgtPos.Y - curPos.Y
    local dz = tgtPos.Z - curPos.Z
    local hd = math.sqrt(dx * dx + dz * dz)
    local td = math.sqrt(hd * hd + dy * dy)
    if td < 0.001 then return Vector3.zero end
    if hd < 1.5 then
        local yaw = 0
        local char = plr.Character
        if char then
            local hrp = char:FindFirstChild("HumanoidRootPart")
            if hrp then yaw = math.rad(hrp.Orientation.Y) end
        end
        local ex = math.sin(yaw)
        local ez = math.cos(yaw)
        local hc = speed * 0.6
        local vc = 0
        if dy > 0 then vc = math.min(speed * MAX_V_RATIO, math.abs(dy) * 2)
        elseif dy < 0 then vc = -math.min(speed * MAX_V_RATIO, math.abs(dy) * 2) end
        return Vector3.new(ex * hc, vc, ez * hc)
    end
    local vr = math.abs(dy) / td
    if vr > MAX_V_RATIO then vr = MAX_V_RATIO end
    local hr = math.sqrt(math.max(0, 1 - vr * vr))
    if hr < MIN_H_RATIO then
        hr = MIN_H_RATIO
        vr = math.sqrt(math.max(0, 1 - hr * hr))
    end
    local vs = speed * vr
    if dy < 0 then vs = -vs end
    local hs = speed * hr
    local hdx = dx / hd
    local hdz = dz / hd
    return Vector3.new(hdx * hs, vs, hdz * hs)
end
local function flyToPrecise(tgtPos, spdOverride, timeout, arriveDist)
    local char = plr.Character
    if not char then return false end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    local hum = char:FindFirstChildOfClass("Humanoid")
    if not hrp or not hum or hum.Health <= 0 then return false end
    local tgt
    if typeof(tgtPos) == "CFrame" then tgt = tgtPos.Position
    elseif typeof(tgtPos) == "Vector3" then tgt = tgtPos
    else return false end
    if not validNum(tgt.X) then return false end
    local spd = spdOverride or Cfg.FlySpeed
    if not validNum(spd) then spd = 170 end
    timeout = timeout or 45
    local ad = arriveDist or 8
    stopAllMovement()
    local bv = Instance.new("BodyVelocity")
    bv.Name = "Irish_PreciseDiagBV"
    bv.MaxForce = Vector3.new(9e9, 9e9, 9e9)
    -- More paid scripts leaked for free in SL Discord: https://discord.gg/zNyHGU6eUK
    bv.Velocity = Vector3.zero
    bv.Parent = hrp
    local bg = Instance.new("BodyGyro")
    bg.Name = "Irish_PreciseDiagBG"
    bg.MaxTorque = Vector3.new(9e9, 9e9, 9e9)
    bg.P = 1e4
    bg.D = 1000
    bg.CFrame = hrp.CFrame
    bg.Parent = hrp
    local ag = Instance.new("BodyForce")
    ag.Name = "Irish_PreciseDiagAntiGrav"
    ag.Force = Vector3.new(0, workspace.Gravity * 3.5, 0)
    ag.Parent = hrp
    pcall(function()
        hum.PlatformStand = false
        hum.AutoRotate = false
        hum.WalkSpeed = 0
        hum.JumpPower = 0
        hum:SetStateEnabled(Enum.HumanoidStateType.Running, false)
        hum:SetStateEnabled(Enum.HumanoidStateType.RunningNoPhysics, false)
        hum:SetStateEnabled(Enum.HumanoidStateType.Climbing, false)
        hum:SetStateEnabled(Enum.HumanoidStateType.Landed, false)
        hum:SetStateEnabled(Enum.HumanoidStateType.Swimming, false)
        hum:SetStateEnabled(Enum.HumanoidStateType.Freefall, true)
        hum:ChangeState(Enum.HumanoidStateType.Freefall)
    end)
    for _, p in ipairs(char:GetDescendants()) do
        if p:IsA("BasePart") then
            p.CanCollide = false
            p.CanTouch = false
            p.CanQuery = false
        end
    end
    local t0 = tick()
    local ok = false
    while tick() - t0 < timeout and not State.IsScriptDestroyed do
        local cc = plr.Character
        local ch = cc and cc:FindFirstChild("HumanoidRootPart")
        if not ch or not bv.Parent or not bg.Parent then break end
        if not ag.Parent then
            ag = Instance.new("BodyForce")
            ag.Name = "Irish_PreciseDiagAntiGrav"
            ag.Force = Vector3.new(0, workspace.Gravity * 3.5, 0)
            ag.Parent = ch
        end
        for _, p in ipairs(cc:GetDescendants()) do
            if p:IsA("BasePart") and (p.CanCollide or p.CanTouch or p.CanQuery) then
                p.CanCollide = false
                p.CanTouch = false
                p.CanQuery = false -- SL | Source Leak [https://discord.gg/zNyHGU6eUK]
            end
        end
        local cur = ch.Position
        if not validNum(cur.X) then break end
        local dv = tgt - cur
        local dist = dv.Magnitude
        if not validNum(dist) then break end
        if dist <= ad then ok = true break end
        local ds = spd
        if dist < 40 then ds = math.max(20, spd * (dist / 40)) end
        if dist < 15 then ds = math.max(8, spd * (dist / 15) * 0.6) end
        if not validNum(ds) then ds = 60 end
        local fv = calcDiagVel(cur, tgt, ds)
        if ch.AssemblyLinearVelocity.Y < -25 and dv.Y >= 0 then fv = Vector3.new(fv.X, math.max(fv.Y, 20), fv.Z) end
        if not validNum(fv.X) then fv = Vector3.new(20, 0, 0) end
        -- Get the latest leaked Roblox scripts in SL Discord: https://discord.gg/zNyHGU6eUK
        bv.Velocity = fv
        local hl = Vector3.new(tgt.X, cur.Y, tgt.Z)
        if (hl - cur).Magnitude > 0.5 then bg.CFrame = CFrame.lookAt(cur, hl) end
        task.wait(0.03)
    end
    if bv and bv.Parent then pcall(function() bv:Destroy() end) end
    if bg and bg.Parent then pcall(function() bg:Destroy() end) end
    if ag and ag.Parent then pcall(function() ag:Destroy() end) end
    if ok then
        local fc = plr.Character
        local fh = fc and fc:FindFirstChild("HumanoidRootPart")
        if fh then
            fh.CFrame = CFrame.new(tgt) * CFrame.Angles(0, math.rad(fh.Orientation.Y), 0)
            fh.AssemblyLinearVelocity = Vector3.zero
            fh.AssemblyAngularVelocity = Vector3.zero
        end
    end
    return ok
end
local function cleanExitFlight()
    local char = plr.Character
    if not char then return end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    local hum = char:FindFirstChildOfClass("Humanoid")
    if not hrp then return end
    for _, o in ipairs(hrp:GetChildren()) do
        local n = o.Name
        if n == "Irish_DirectFly" or n == "Irish_DirectGyro" or n == "Irish_DirectAntiGrav"
           or n == "Irish_HoverBV" or n == "Irish_HoverBG" or n == "Irish_HoverAntiGrav"
           or n == "Irish_BV" or n == "Irish_BG" or n == "Irish_AntiGravity"
           or n == "Irish_PreciseDiagBV" or n == "Irish_PreciseDiagBG" or n == "Irish_PreciseDiagAntiGrav"
           or n == "Irish_SmartDescentBV" or n == "Irish_SmartDescentBG" or n == "Irish_SmartDescentAntiGrav" then pcall(function() o:Destroy() end) end
    end
    State.BodyVelocity = nil
    State.BodyGyro = nil
    State.NoFallAntiGravity = nil
    State.IsMoving = false
    State.IsHoveringAtTarget = false
    State.Descending = false
    State.DescentTargetY = nil
    State.LastHorizontalVelocity = Vector3.zero
    State.DiagonalFlightActive = false
    pcall(function()
        hrp.AssemblyLinearVelocity = Vector3.zero
        hrp.AssemblyAngularVelocity = Vector3.zero
    end)
    if hum and hum.Health > 0 then
        pcall(function()
            hum.PlatformStand = false
            hum.AutoRotate = true
            hum.WalkSpeed = 16
            hum.JumpPower = 50
            hum:SetStateEnabled(Enum.HumanoidStateType.Running, true)
            hum:SetStateEnabled(Enum.HumanoidStateType.RunningNoPhysics, true)
            hum:SetStateEnabled(Enum.HumanoidStateType.Climbing, true)
            hum:SetStateEnabled(Enum.HumanoidStateType.Swimming, true)
            hum:SetStateEnabled(Enum.HumanoidStateType.Freefall, true)
            hum:SetStateEnabled(Enum.HumanoidStateType.Jumping, true)
            hum:SetStateEnabled(Enum.HumanoidStateType.Landed, true)
            hum:SetStateEnabled(Enum.HumanoidStateType.GettingUp, true)
            hum:ChangeState(Enum.HumanoidStateType.Running)
        end)
    end
    restoreCharCollisions(char)
end
-- SL | Source Leak Community - Join us at https://discord.gg/zNyHGU6eUK
function stopAllMovement()
    local char = plr.Character
    if not char then return end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    if not hrp then return end
    State.IsMoving = false
    State.IsHoveringAtTarget = false
    State.LastVelocityMagnitude = 0
    State.Descending = false
    State.DescentTargetY = nil -- Join SL Discord: https://discord.gg/zNyHGU6eUK
    State.LastHorizontalVelocity = Vector3.zero
    State.DiagonalFlightActive = false
    stopAntiGrav()
    if State.BodyVelocity then pcall(function() State.BodyVelocity:Destroy() end) State.BodyVelocity = nil end
    if State.BodyGyro then pcall(function() State.BodyGyro:Destroy() end) State.BodyGyro = nil end
    for _, o in ipairs(hrp:GetChildren()) do
        local n = o.Name
        if n == "Irish_BV" or n == "Irish_BG" or n == "Irish_DirectFly" or n == "Irish_DirectGyro" or n == "Irish_HoverBV" or n == "Irish_HoverBG" or n == "Irish_FlyBV" or n == "Irish_FlyBG" or n == "Irish_AntiGravity" or n == "Irish_DirectAntiGrav" or n == "Irish_HoverAntiGrav" or n == "Irish_SmartDescentBV" or n == "Irish_SmartDescentBG" or n == "Irish_SmartDescentAntiGrav" or n == "Irish_PreciseDiagBV" or n == "Irish_PreciseDiagBG" or n == "Irish_PreciseDiagAntiGrav" then pcall(function() o:Destroy() end) end
    end
    pcall(function()
        hrp.AssemblyLinearVelocity = Vector3.zero
        hrp.AssemblyAngularVelocity = Vector3.zero
        hrp.Velocity = Vector3.zero
        hrp.RotVelocity = Vector3.zero
    end)
end
local function requestUWEntrance(tgtPos)
    local cf = getCommF()
    if not cf then return false end
    local pos = tgtPos
    if typeof(tgtPos) == "CFrame" then pos = tgtPos.Position end
    if typeof(pos) ~= "Vector3" then return false end
    if not validNum(pos.X) then return false end
    local ok = pcall(function() cf:InvokeServer("requestEntrance", pos) end)
    return ok
end
local function isInsideUW()
    local char = plr.Character
    local hrp = char and char:FindFirstChild("HumanoidRootPart")
    if not hrp then return false end
    return hrp.Position.X > UW_X_THRESHOLD
end
local function isPosInsideUW(pos)
    if not pos then return false end
    local v
    if typeof(pos) == "CFrame" then v = pos.Position
    elseif typeof(pos) == "Vector3" then v = pos
    else return false end
    return v.X > UW_X_THRESHOLD
end
local function lockCharAtPos(tgtPos, hold)
    local char = plr.Character
    if not char then return end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    local hum = char:FindFirstChildOfClass("Humanoid")
    if not hrp or not hum then return end
    local tgt
    if typeof(tgtPos) == "CFrame" then tgt = tgtPos.Position
    elseif typeof(tgtPos) == "Vector3" then tgt = tgtPos
    else return end
    if not validNum(tgt.X) then return end
    for _, o in ipairs(hrp:GetChildren()) do
        if o.Name == "Irish_LockBV" or o.Name == "Irish_LockBG" or o.Name == "Irish_LockAntiGrav" then pcall(function() o:Destroy() end) end
    end
    local bv = Instance.new("BodyVelocity")
    --[[ Join SL | Source Leak Discord for more free script sources: https://discord.gg/zNyHGU6eUK ]]
    bv.Name = "Irish_LockBV"
    bv.MaxForce = Vector3.new(9e9, 9e9, 9e9)
    bv.Velocity = Vector3.zero
    bv.Parent = hrp
    local bg = Instance.new("BodyGyro")
    bg.Name = "Irish_LockBG"
    bg.MaxTorque = Vector3.new(9e9, 9e9, 9e9)
    bg.P = 1e4
    bg.D = 1000
    bg.CFrame = CFrame.new(tgt) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
    bg.Parent = hrp
    local ag = Instance.new("BodyForce")
    ag.Name = "Irish_LockAntiGrav"
    ag.Force = Vector3.new(0, workspace.Gravity * 3.5, 0)
    ag.Parent = hrp
    pcall(function()
        hum.PlatformStand = false
        hum.AutoRotate = false
        hum.WalkSpeed = 0
        hum.JumpPower = 0
        hum:SetStateEnabled(Enum.HumanoidStateType.Freefall, true)
        hum:ChangeState(Enum.HumanoidStateType.Freefall)
    end)
    for _, p in ipairs(char:GetDescendants()) do
        if p:IsA("BasePart") then
            p.CanCollide = false
            p.CanTouch = false
            p.CanQuery = false
        end
    end
    local te = tick() + (hold or 0.5)
    while tick() < te and not State.IsScriptDestroyed do
        task.wait(0.03)
        if hrp and bv.Parent then
            bv.Velocity = Vector3.zero
            hrp.CFrame = CFrame.new(tgt) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
            hrp.AssemblyLinearVelocity = Vector3.zero
            hrp.AssemblyAngularVelocity = Vector3.zero
        else break end
    end
    if bv and bv.Parent then pcall(function() bv:Destroy() end) end
    if bg and bg.Parent then pcall(function() bg:Destroy() end) end
    if ag and ag.Parent then pcall(function() ag:Destroy() end) end
end
local function goIntoUW()
    if State.UnderwaterTransitionActive or State.UnderwaterEntryLock then return false end
    State.UnderwaterTransitionActive = true
    State.UnderwaterEntryLock = true
    local ok = pcall(function()
        local char = plr.Character
        local hrp = char and char:FindFirstChild("HumanoidRootPart")
        if not hrp then return end
        if isInsideUW() then return end
        local gp = UW_ENTRY_GATE.Position
        local ap = gp + UW_GATE_OFFSET
        local cp = hrp.Position
        local d = (cp - ap).Magnitude
        if not validNum(d) then return end
        if d > 4 then flyToPrecise(ap, Cfg.FlySpeed, 40, 4) end
        char = plr.Character
        hrp = char and char:FindFirstChild("HumanoidRootPart")
        if not hrp then return end
        hrp.CFrame = CFrame.new(ap) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
        hrp.AssemblyLinearVelocity = Vector3.zero
        hrp.AssemblyAngularVelocity = Vector3.zero
        --[=[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] | Daily leaks in our Discord ]=]
        lockCharAtPos(ap, 0.4)
        requestUWEntrance(UW_INSIDE_POS)
        local ws = tick()
        while tick() - ws < 3.0 and not State.IsScriptDestroyed do
            task.wait(0.05)
            char = plr.Character
            hrp = char and char:FindFirstChild("HumanoidRootPart")
            if hrp and isInsideUW() then break end
            if hrp then
                hrp.CFrame = CFrame.new(ap) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
                hrp.AssemblyLinearVelocity = Vector3.zero
                hrp.AssemblyAngularVelocity = Vector3.zero
            end
        end
        char = plr.Character
        hrp = char and char:FindFirstChild("HumanoidRootPart")
        if hrp and not isInsideUW() then
            requestUWEntrance(UW_INSIDE_POS)
            local ws2 = tick()
            while tick() - ws2 < 2.0 and not State.IsScriptDestroyed do
                task.wait(0.05)
                char = plr.Character
                hrp = char and char:FindFirstChild("HumanoidRootPart")
                if hrp and isInsideUW() then break end
                if hrp then
                    hrp.CFrame = CFrame.new(ap) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
                    hrp.AssemblyLinearVelocity = Vector3.zero
                    hrp.AssemblyAngularVelocity = Vector3.zero
                end
            end
        end
    end)
    cleanExitFlight()
    task.wait(0.2)
    State.UnderwaterTransitionActive = false
    State.UnderwaterEntryLock = false
    return ok
end
local function goOutUW()
    if State.UnderwaterTransitionActive or State.UnderwaterEntryLock then return false end
    State.UnderwaterTransitionActive = true
    State.UnderwaterEntryLock = true
    local ok = pcall(function()
        local char = plr.Character
        local hrp = char and char:FindFirstChild("HumanoidRootPart")
        if not hrp then return end
        if not isInsideUW() then return end
        local gp = UW_EXIT_GATE.Position
        local ap = gp + UW_GATE_OFFSET
        local cp = hrp.Position
        local d = (cp - ap).Magnitude
        if not validNum(d) then return end
        if d > 4 then flyToPrecise(ap, Cfg.FlySpeed, 30, 4) end
        char = plr.Character
        hrp = char and char:FindFirstChild("HumanoidRootPart")
        if not hrp then return end
        hrp.CFrame = CFrame.new(ap) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
        hrp.AssemblyLinearVelocity = Vector3.zero
        hrp.AssemblyAngularVelocity = Vector3.zero
        lockCharAtPos(ap, 0.4)
        requestUWEntrance(UW_OUTSIDE_POS)
        local ws = tick()
        while tick() - ws < 3.0 and not State.IsScriptDestroyed do
            task.wait(0.05)
            char = plr.Character
            -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
            hrp = char and char:FindFirstChild("HumanoidRootPart")
            if hrp and not isInsideUW() then break end
            if hrp then
                hrp.CFrame = CFrame.new(ap) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
                hrp.AssemblyLinearVelocity = Vector3.zero
                hrp.AssemblyAngularVelocity = Vector3.zero
            end
        end
        char = plr.Character
        hrp = char and char:FindFirstChild("HumanoidRootPart")
        if hrp and isInsideUW() then
            requestUWEntrance(UW_OUTSIDE_POS)
            local ws2 = tick()
            while tick() - ws2 < 2.0 and not State.IsScriptDestroyed do
                task.wait(0.05)
                char = plr.Character
                hrp = char and char:FindFirstChild("HumanoidRootPart")
                if hrp and not isInsideUW() then break end
                if hrp then
                    hrp.CFrame = CFrame.new(ap) * CFrame.Angles(0, math.rad(hrp.Orientation.Y), 0)
                    hrp.AssemblyLinearVelocity = Vector3.zero
                    hrp.AssemblyAngularVelocity = Vector3.zero
                end
            end
        end
    end)
    cleanExitFlight()
    task.wait(0.2)
    State.UnderwaterTransitionActive = false
    State.UnderwaterEntryLock = false
    return ok
end
local function ensureCorrectDim(tgtPos)
    if not tgtPos then return false end
    if State.UnderwaterTransitionActive or State.UnderwaterEntryLock then return true end
    if State.IsTransitioningDimension then return true end
    if tick() - (State.LastDimensionTransition or 0) < 2.0 then return true end
    local char = plr.Character
    local hrp = char and char:FindFirstChild("HumanoidRootPart")
    if not hrp then return true end --[[ Leaked By SL | https://discord.gg/zNyHGU6eUK ]]
    local pIn = isInsideUW()
    local tIn = isPosInsideUW(tgtPos)
    if pIn == tIn then return false end
    State.IsTransitioningDimension = true
    State.LastDimensionTransition = tick()
    if tIn then goIntoUW() else goOutUW() end
    State.IsTransitioningDimension = false
    State.LastDimensionTransition = tick()
    return true
end
local function moveToTarget(tgtCF)
    local char = plr.Character
    if not char then return end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    local hum = char:FindFirstChildOfClass("Humanoid")
    if not hrp or not hum or hum.Health <= 0 then return end
    if not tgtCF then return end
    local tp
    if typeof(tgtCF) == "CFrame" then tp = tgtCF.Position
    elseif typeof(tgtCF) == "Vector3" then tp = tgtCF
    else return end
    if not validNum(tp.X) then return end
    if ensureCorrectDim(tp) then
        if State.BodyVelocity and State.BodyVelocity.Parent == hrp then State.BodyVelocity.Velocity = Vector3.zero end
        return
        -- Leaked by SL | Join our Discord for more leaked sources: https://discord.gg/zNyHGU6eUK
    end
    local cp = hrp.Position
    if not validNum(cp.X) then return end
    local dv = tp - cp
    local td = dv.Magnitude
    if not validNum(td) then return end
    local bv = ensureBodyMovers()
    if not bv then return end
    State.IsMoving = true
    State.DiagonalFlightActive = true
    startAntiGrav()
    local fs = Cfg.FlySpeed
    if not validNum(fs) then fs = 170 end
    local cv = hrp.AssemblyLinearVelocity.Magnitude
    if not validNum(cv) then cv = 0 end
    local ms = math.clamp(fs, 50, 200)
    local bd = math.max(3.5, (cv * cv) / (2 * ms) * 0.15)
    bd = math.clamp(bd, 3.5, 8)
    local arrived = (td <= bd) or (State.IsHoveringAtTarget and td <= bd + 3)
    if arrived then -- Leaked by SL | Join https://discord.gg/zNyHGU6eUK for more leaks
        State.IsHoveringAtTarget = true
        bv.Velocity = Vector3.zero
        hrp.AssemblyLinearVelocity = Vector3.zero
        hrp.Velocity = Vector3.zero
        hrp.AssemblyAngularVelocity = Vector3.zero
        hrp.RotVelocity = Vector3.zero
        local yaw = math.rad(hrp.Orientation.Y)
        local stable = CFrame.Angles(0, yaw, 0)
        hrp.CFrame = CFrame.new(tp) * stable
        if State.BodyGyro and State.BodyGyro.Parent == hrp then
            State.BodyGyro.MaxTorque = Vector3.new(0, 9e9, 0)
            State.BodyGyro.CFrame = CFrame.new(tp) * stable
        end
        State.LastVelocityMagnitude = 0
        return
    end
    State.IsHoveringAtTarget = false
    local ds = ms
    if td < 30 then ds = math.max(15, ms * (td / 30)) end
    if td < 10 then ds = math.max(8, ms * (td / 10) * 0.5) end
    if not validNum(ds) then ds = 50 end
    if State.BodyGyro and State.BodyGyro.Parent == hrp then
        State.BodyGyro.MaxTorque = Vector3.new(0, 9e9, 0)
        local hd = Vector3.new(dv.X, 0, dv.Z)
        if hd.Magnitude > 1.0 then State.BodyGyro.CFrame = CFrame.lookAt(cp, cp + hd)
        else
            local yaw = math.rad(hrp.Orientation.Y)
            State.BodyGyro.CFrame = CFrame.new(cp) * CFrame.Angles(0, yaw, 0)
        end
    end
    if hrp.AssemblyLinearVelocity.Magnitude > ms + 15 then hrp.AssemblyLinearVelocity = hrp.AssemblyLinearVelocity.Unit * ms end
    local fv = calcDiagVel(cp, tp, ds)
    if not validNum(fv.X) then fv = Vector3.zero end
    bv.Velocity = fv
    State.LastVelocityMagnitude = ds
end
local MAX_FRUIT_SIZE = 4
local sortedFruitKeys = {}
for k in pairs(BLOX_FRUIT_ID_MAP) do table.insert(sortedFruitKeys, k) end
table.sort(sortedFruitKeys, function(a, b) return #a > #b end)
local BLOCKED_KEYWORDS = {
    "statue", "wall", "block", "crystal", "cave", "rock", "tree",
    "door", "gate", "pillar", "tower", "iceberg", "glacier", "snowman",
    "platform", "island", "map", "part", "barrier", "shield"
} -- [SL Source Leak] https://discord.gg/zNyHGU6eUK
-- SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join SL for more script leaks
local function getFruitFromObj(obj)
    if not obj or not obj.Parent then return nil end
    if Players:GetPlayerFromCharacter(obj) then return nil end
    if obj.Name == "IceRock" or obj:FindFirstAncestor("Iceberg") then
        return nil
    end
    local ln = string.lower(obj.Name)
    for _, word in ipairs(BLOCKED_KEYWORDS) do
        if ln:find(word, 1, true) then return nil end
    end
    if not ln:find("fruit", 1, true) then
        if obj:IsA("Tool") and isPhysicalFruit(obj) then
            return { name = obj.Name, isKnown = true, rawName = normFruitKey(obj.Name) }
        end
        return nil
    end
    for _, k in ipairs(sortedFruitKeys) do
        if string.find(ln, k, 1, true) then
            return { name = BLOX_FRUIT_ID_MAP[k], isKnown = true, rawName = k }
        end
    end
    return { name = "??? Fruit", isKnown = false, rawName = "unknown" }
end
local function findAllGroundFruits()
    local out = {}
    local char = plr.Character
    local bp = plr:FindFirstChild("Backpack")
    local seen = {}
    for _, o in pairs(workspace:GetChildren()) do
        if o and o.Parent and not seen[o] and not Players:GetPlayerFromCharacter(o) then
            local fd = getFruitFromObj(o)
            if fd then
                local p = o:FindFirstChild("Handle") or (o:IsA("BasePart") and o) or o:FindFirstChildOfClass("BasePart")
                if p then
                    local sz = o:IsA("Model") and o:GetExtentsSize() or p.Size
                    local mx = math.max(sz.X, sz.Y, sz.Z)
                    if mx <= MAX_FRUIT_SIZE then
                        seen[o] = true
                        local inBp = bp and bp:FindFirstChild(o.Name)
                        local inChar = char and char:FindFirstChild(o.Name)
                        if not inBp and not inChar then
                            local d = math.huge
                            if char then
                                local hrp = char:FindFirstChild("HumanoidRootPart")
                                if hrp then d = (hrp.Position - p.Position).Magnitude end --[=[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] ]=]
                            end
                            table.insert(out, {
                                Object = o, Handle = p, Tool = o, Name = fd.name,
                                IsKnown = fd.isKnown, RawName = fd.rawName, Distance = d
                            })
                        end
                    end
                end
            end
        end
    end
    table.sort(out, function(a, b) return a.Distance < b.Distance end)
    return out
end
local function isFarmingActive() return Cfg.AutoFarmLevel or Cfg.AutoFarmNearest or Cfg.AutoFarmBosses end
local function toolMatchesWeapon(tool, wt)
    if not tool or not tool:IsA("Tool") then return false end
    if isPhysicalFruit(tool) then return false end
    local tip = (tool.ToolTip or ""):lower()
    local n = tool.Name:lower()
    -- Source leaked by SL | Get more free hub sources at https://discord.gg/zNyHGU6eUK
    local w = (wt or Cfg.SelectedWeapon or "Sword"):lower()
    if tool:GetAttribute("WeaponType") then
        local at = tostring(tool:GetAttribute("WeaponType")):lower()
        if at == w or (w == "blox fruit" and at:find("fruit")) then return true end
    end
    if w == "melee" then
        if tip == "melee" then return true end
        if n:find("combat") or n:find("step") or n:find("claw") or n:find("karate") or n:find("kung fu") or n:find("dragon breath") or n:find("superhuman") or n:find("electric") or n:find("godhuman") or n:find("sanguine") then return true end
    elseif w == "sword" then
        if tip == "sword" then return true end
        if n:find("blade") or n:find("sword") or n:find("katana") or n:find("saber") or n:find("cutlass") or n:find("scythe") or n:find("pole") or n:find("bisento") or n:find("trident") or n:find("pipe") or n:find("dagger") or n:find("dual") or n:find("anchor") or n:find("lamp") or n:find("triple") or n:find("warden") or n:find("cane") or n:find("mace") or n:find("saw") then return true end
    elseif w == "gun" then
        if tip == "gun" then return true end
        if n:find("gun") or n:find("rifle") or n:find("pistol") or n:find("cannon") or n:find("slingshot") or n:find("musket") or n:find("flintlock") or n:find("acidum") or n:find("kabucha") or n:find("guitar") or n:find("bazooka") or n:find("bow") then return true end
    elseif w == "blox fruit" or w == "fruit" then
        if (tip == "blox fruit" or tip:find("fruit")) and not isPhysicalFruit(tool) then return true end
        if (tool:FindFirstChild("Skills") or tool:FindFirstChild("Moves") or tool:FindFirstChild("SkillFrames")) and not toolMatchesWeapon(tool, "sword") and not toolMatchesWeapon(tool, "melee") and not toolMatchesWeapon(tool, "gun") then return true end
    end
    return false
end
local function equipWeapon(forceSel)
    if State.IsStoringFruitActive then return end
    pcall(function()
        local char = plr.Character
        local bp = plr:FindFirstChild("Backpack")
        if not char or not bp then return end
        local hum = char:FindFirstChildOfClass("Humanoid")
        if not hum or hum.Health <= 0 then return end
        local cur = char:FindFirstChildOfClass("Tool")
        local farming = forceSel or isFarmingActive()
        if farming then
            if cur then
                if toolMatchesWeapon(cur, Cfg.SelectedWeapon) then return end
                hum:UnequipTools()
            end
            for _, t in ipairs(bp:GetChildren()) do
                if toolMatchesWeapon(t, Cfg.SelectedWeapon) then hum:EquipTool(t) return end
            end
            for _, t in ipairs(bp:GetChildren()) do
                if t:IsA("Tool") and not isPhysicalFruit(t) then hum:EquipTool(t) break end
            end
        else
            if cur and not isPhysicalFruit(cur) then return end
            if cur then hum:UnequipTools() end
            for _, t in ipairs(bp:GetChildren()) do
                if toolMatchesWeapon(t, Cfg.SelectedWeapon) then hum:EquipTool(t) return end
            end
            for _, t in ipairs(bp:GetChildren()) do
                if t:IsA("Tool") and not isPhysicalFruit(t) then hum:EquipTool(t) break end
            end
        end
    end)
end
local function checkEquipBuso()
    if not Cfg.AutoBuso then return end
    local char = plr.Character
    if char and not char:FindFirstChild("HasBuso") and not char:GetAttribute("HasBuso") then
        local now = tick()
        if now - State.LastBuso > 1.5 then
            State.LastBuso = now
            pcall(function()
                if RS:FindFirstChild("Remotes") and RS.Remotes:FindFirstChild("CommF_") then RS.Remotes.CommF_:InvokeServer("Buso") end
            end)
        end
    end
    -- [SL] Leaked By SL | Source Leak - Join https://discord.gg/zNyHGU6eUK
end
local function normalize(s)
    if not s then return "" end
    return s:lower():gsub("%[.-%]", ""):gsub("[^a-z0-9]", "")
end -- Source Leak (SL) | Join our Discord: https://discord.gg/zNyHGU6eUK
local function isValidPrisoner(m)
    if not m or not m.Parent then return false end
    local h = m:FindFirstChildOfClass("Humanoid")
    if not h or h.Health <= 0 then return false end
    local l = m:GetAttribute("Level")
    if not l then return false end
    local n = tonumber(l)
    if not n or n ~= 190 then return false end
    local ek = m:GetAttribute("EscapeKey")
    if ek ~= nil and ek ~= false and ek ~= "" then return false end
    return true
end
local function isValidDangerous(m)
    if not m or not m.Parent then return false end
    local h = m:FindFirstChildOfClass("Humanoid")
    if not h or h.Health <= 0 then return false end
    local l = m:GetAttribute("Level")
    if not l then return false end
    local n = tonumber(l)
    if not n then return false end
    return n == 210
end
local function isValidRuthless(m)
    if not m or not m.Parent then return false end
    local h = m:FindFirstChildOfClass("Humanoid")
    if not h or h.Health <= 0 then return false end
    local l = m:GetAttribute("Level")
    if not l then return false end
    local n = tonumber(l)
    if not n then return false end
    return n == 220
end
MobExclusions = {
    ["prisoner"] = {"dangerous", "ruthless"}, ["bandit"] = {"desert", "snow", "sky"}, ["pirate"] = {"galley"},
    ["master"] = {"dark"}, ["guard"] = {"god", "gods"}, ["warrior"] = {"fishman", "toga"},
    ["officer"] = {"chief", "petty"}, ["captain"] = {"galley"}, ["soldier"] = {"military"},
    ["spy"] = {"military"}, ["commando"] = {"fishman"}, ["squad"] = {"royal"},
}
local function mobMatches(en, tn, mob)
    if not en or not tn then return false end
    local e = normalize(en)
    local t = normalize(tn)
    if e == "" or t == "" then return false end
    if t == "prisoner" then
        if mob then return isValidPrisoner(mob) end --[==[ SL | Source Leak: https://discord.gg/zNyHGU6eUK ]==]
        return e == "prisoner"
    end
    if t == "dangerousprisoner" then
        if mob then return isValidDangerous(mob) end
        return e == "dangerousprisoner"
    end
    if t == "ruthlessprisoner" then
        if mob then return isValidRuthless(mob) end
        return e == "ruthlessprisoner"
    end
    if e == t then return true end
    for base, excl in pairs(MobExclusions) do
        if t:find(base, 1, true) then
            for _, x in ipairs(excl) do if e:find(x, 1, true) and not t:find(x, 1, true) then return false end end
        end
        -- Join SL Discord for more open-source & leaked scripts: https://discord.gg/zNyHGU6eUK
    end
    for base, excl in pairs(MobExclusions) do
        if e:find(base, 1, true) then
            for _, x in ipairs(excl) do if t:find(x, 1, true) and not e:find(x, 1, true) then return false end end
        end
    end
    if e:find(t, 1, true) or t:find(e, 1, true) then return true end
    return false
end
local function isQuestFramePresent()
    local pg = plr:FindFirstChild("PlayerGui")
    if not pg then return false end
    return pg:FindFirstChild("TrackedQuestFrame") ~= nil
end
local function readTrackedQuest()
    local pg = plr:FindFirstChild("PlayerGui")
    if not pg then return nil end
    local tk = pg:FindFirstChild("TrackedQuestFrame")
    if not tk then return nil end
    local fr = tk:FindFirstChild("Frame")
    if not fr then return nil end
    local title, mob, ptxt = "", "", ""
    local cur, goal = 0, 0
    pcall(function()
        local h = fr:FindFirstChild("header")
        if h then
            local tl = h:FindFirstChild("textLabel")
            if tl and tl:IsA("TextLabel") then title = tl.Text end
        end
        local d = fr:FindFirstChild("description")
        if d and d:IsA("TextLabel") then mob = d.Text end
        local p = fr:FindFirstChild("progress")
        if p and p:IsA("TextLabel") then
            ptxt = p.Text
            local c, m = p.Text:match("(%d+)%s*/%s*(%d+)")
            if c and m then cur = tonumber(c) or 0 goal = tonumber(m) or 0 end
        end
    end)
    if title == "" and mob == "" and ptxt == "" then return nil end
    return { Title = title, MobName = mob, ProgressText = ptxt, Current = cur, Goal = goal }
end
local function getNearbyEntities(r)
    r = r or 65
    local out = {}
    local char = plr.Character
    if not char then return out end
    local hrp = char:FindFirstChild("HumanoidRootPart")
    if not hrp then return out end
    local tmt = nil
    if State.CurrentQuestData then tmt = normalize(State.CurrentQuestData.Mob) end
    local enf = Workspace:FindFirstChild("Enemies")
    if enf then
        for _, e in ipairs(enf:GetChildren()) do
            if e ~= char and not Players:GetPlayerFromCharacter(e) and not Players:FindFirstChild(e.Name) then
                local eh = e:FindFirstChild("HumanoidRootPart") or e:FindFirstChildWhichIsA("BasePart")
                local ehu = e:FindFirstChildOfClass("Humanoid")
                if eh and ehu and ehu.Health > 0 then
                    if (hrp.Position - eh.Position).Magnitude <= r then
                        local skip = false
                        if tmt == "prisoner" then
                            if not isValidPrisoner(e) then skip = true end
                        elseif tmt == "dangerousprisoner" then
                            if not isValidDangerous(e) then skip = true end
                        elseif tmt == "ruthlessprisoner" then
                            if not isValidRuthless(e) then skip = true end
                            -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] | More leaks in our Discord
                        end
                        if not skip then table.insert(out, e) end
                    end
                end
            end
        end
    end
    for _, pl in ipairs(Players:GetPlayers()) do
        if pl ~= plr and pl.Character then
            local ph = pl.Character:FindFirstChild("HumanoidRootPart")
            local phu = pl.Character:FindFirstChildOfClass("Humanoid")
            if ph and phu and phu.Health > 0 then
                if (hrp.Position - ph.Position).Magnitude <= r then table.insert(out, pl.Character) end
            end
        end
    end
    return out
end
local function isMobIgnored(m)
    if not m then return false end
    local t = State.IgnoredInvincibleMobs[m]
    if not t then return false end
    if tick() - t > 30 then
        State.IgnoredInvincibleMobs[m] = nil
        State.MobHealthTracker[m] = nil
        return false
    end
    return true
end
local function markInvincible(m)
    if not m then return end
    State.IgnoredInvincibleMobs[m] = tick()
    State.MobHealthTracker[m] = nil
    if State.CurrentTargetMob == m then
        pcall(function() unfreezeMob(m) end)
        State.CurrentTargetMob = nil
        State.FastAttackTarget = nil
    end
end
local function trackMobDamage(m)
    if not m or not m.Parent then return end
    local h = m:FindFirstChildOfClass("Humanoid")
    if not h or h.Health <= 0 then
        State.MobHealthTracker[m] = nil
        return
    end
    local now = tick()
    local tr = State.MobHealthTracker[m]
    if not tr then
        State.MobHealthTracker[m] = {lastHealth = h.Health, lastDamageTime = now, firstSeenTime = now}
        return
    end
    if h.Health < tr.lastHealth - 0.01 then
        tr.lastHealth = h.Health
        tr.lastDamageTime = now
    end
end
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(State.InvincibleCheckInterval or 0.25)
        local now = tick()
        local th = State.InvincibleNoDamageThreshold or 4
        local active = {}
        if State.CurrentTargetMob then table.insert(active, State.CurrentTargetMob) end
        if State.FastAttackTarget and State.FastAttackTarget ~= State.CurrentTargetMob then table.insert(active, State.FastAttackTarget) end
        --[[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join SL Discord ]]
        for _, m in ipairs(active) do
            if m and m.Parent then
                local h = m:FindFirstChildOfClass("Humanoid")
                if h and h.Health > 0 then
                    trackMobDamage(m)
                    local tr = State.MobHealthTracker[m]
                    if tr and now - tr.lastDamageTime >= th then markInvincible(m) end
                else State.MobHealthTracker[m] = nil end
            else State.MobHealthTracker[m] = nil end
        end
        for m, _ in pairs(State.IgnoredInvincibleMobs) do
            if not m or not m.Parent then
                State.IgnoredInvincibleMobs[m] = nil
                State.MobHealthTracker[m] = nil
            end
        end
    end
end)
local FRUIT_M1_RANGE = 65
local function performFastHit()
    local tgt = State.FastAttackTarget
    if not tgt or not tgt.Parent then return end
    local char = plr.Character
    if not char then return end
    local hum = char:FindFirstChildOfClass("Humanoid")
    if not hum or hum.Health <= 0 then return end
    local tool = char:FindFirstChildOfClass("Tool")
    local net = RS:FindFirstChild("Modules") and RS.Modules:FindFirstChild("Net")
    local regA = net and net:FindFirstChild("RE/RegisterAttack")
    local regH = net and net:FindFirstChild("RE/RegisterHit")
    if regA then pcall(function() regA:FireServer(0) end) end
    if tool then
        pcall(function() tool:Activate() end)
        if isCombatFruit(tool) then
            local th = tgt:FindFirstChild("HumanoidRootPart") or tgt:FindFirstChild("Head")
            local ch = char:FindFirstChild("HumanoidRootPart")
            if th and ch then
                local lv = (th.Position - ch.Position).Unit
                for _, c in ipairs(tool:GetChildren()) do
                    if c:IsA("RemoteEvent") then
                        local rn = c.Name:lower()
                        if rn:find("leftclick") or rn:find("attack") or rn:find("click") or rn:find("input") then
                            pcall(function() c:FireServer(lv, 1) end)
                            pcall(function() c:FireServer(lv) end)
                            pcall(function() c:FireServer() end)
                        end
                    end
                end
            end
        end
    end
    if regH then
        local th = tgt:FindFirstChild("HumanoidRootPart") or tgt:FindFirstChild("Head") or tgt:FindFirstChildWhichIsA("BasePart")
        if th then
            local aid = tostring(math.random(100000, 999999))
            local hl = {{tgt, th}}
            local ch = char:FindFirstChild("HumanoidRootPart")
            if ch then
                local enf = Workspace:FindFirstChild("Enemies")
                if enf then
                    local c = 1
                    -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
                    -- Join SL Discord for more leaked sources: https://discord.gg/zNyHGU6eUK
                    for _, e in ipairs(enf:GetChildren()) do
                        if c >= 8 then break end
                        if e ~= tgt and e ~= char and not Players:GetPlayerFromCharacter(e) and not Players:FindFirstChild(e.Name) then
                            local eh = e:FindFirstChildOfClass("Humanoid")
                            --[=[ SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join our Discord for more leaks ]=]
                            local ehp = e:FindFirstChild("HumanoidRootPart")
                            if eh and eh.Health > 0 and ehp then
                                if (ch.Position - ehp.Position).Magnitude <= FRUIT_M1_RANGE then
                                    table.insert(hl, {e, ehp})
                                    c = c + 1
                                end
                            end
                        end
                    end
                end
            end
            local v = {}
            for _, hit in ipairs(hl) do if hit[1] and hit[1].Parent and hit[2] and hit[2].Parent then table.insert(v, hit) end end
            if #v > 0 then pcall(function() regH:FireServer(th, v, aid) end) end
        end -- More free leaks at SL Discord: https://discord.gg/zNyHGU6eUK
    end
end
task.spawn(function()
    local evt = RunService.RenderStepped
    while not State.IsScriptDestroyed do
        evt:Wait()
        if Cfg.AutoFarmLevel and State.FastAttackTarget and State.FastAttackTarget.Parent then
            local now = tick()
            local d = Cfg.AttackDelay or 0.01
            if d < 0.01 then d = 0.01 end
            if now - (State.LastM1Time or 0) >= d then
                State.LastM1Time = now
                pcall(performFastHit)
            end
        end
    end
end)
local function attackTarget(tgt)
    if tgt and tgt.Parent then
        State.FastAttackTarget = tgt
        if not State.MobHealthTracker[tgt] then
            local h = tgt:FindFirstChildOfClass("Humanoid")
            if h then State.MobHealthTracker[tgt] = {lastHealth = h.Health, lastDamageTime = tick(), firstSeenTime = tick()} end
        end
    end
    pcall(function()
        local char = plr.Character
        if not char then return end
        local hum = char:FindFirstChildOfClass("Humanoid")
        if not hum or hum.Health <= 0 then return end
        local ct = char:FindFirstChildOfClass("Tool")
        local net = RS:FindFirstChild("Modules") and RS.Modules:FindFirstChild("Net")
        local regA = net and net:FindFirstChild("RE/RegisterAttack")
        local regH = net and net:FindFirstChild("RE/RegisterHit")
        if regA then pcall(function() regA:FireServer(0) end) end
        if ct and ct:IsA("Tool") then
            pcall(function() ct:Activate() end)
            if isCombatFruit(ct) then
                local ch = char:FindFirstChild("HumanoidRootPart")
                local th = tgt and (tgt:FindFirstChild("HumanoidRootPart") or tgt:FindFirstChild("Head"))
                if ch and th then
                    local lv = (th.Position - ch.Position).Unit
                    for _, c in ipairs(ct:GetChildren()) do
                        if c:IsA("RemoteEvent") then
                            local rn = c.Name:lower()
                            if rn:find("leftclick") or rn:find("attack") or rn:find("click") or rn:find("input") then
                                pcall(function() c:FireServer(lv, 1) end)
                                pcall(function() c:FireServer(lv) end)
                                pcall(function() c:FireServer() end)
                            end
                            --[==[ Leaked By SL | Source Leak | Join https://discord.gg/zNyHGU6eUK for free sources ]==]
                        end
                    end
                end
            end
        end
        local ts = {}
        if tgt and tgt.Parent then table.insert(ts, tgt) end
        local nb = getNearbyEntities(FRUIT_M1_RANGE)
        for _, e in ipairs(nb) do
            if e ~= tgt and not table.find(ts, e) and #ts < 12 then table.insert(ts, e) end
        end
        if #ts > 0 and regH then
            local pt = ts[1]
            local ph = pt:FindFirstChild("HumanoidRootPart") or pt:FindFirstChild("Head") or pt:FindFirstChildWhichIsA("BasePart")
            if ph then
                local aid = tostring(math.random(100000, 999999))
                local hl = {}
                for _, e in ipairs(ts) do
                    local hp = e:FindFirstChild("HumanoidRootPart") or e:FindFirstChild("Head") or e:FindFirstChildWhichIsA("BasePart")
                    if hp then table.insert(hl, {e, hp}) end
                end
                local v = {}
                for _, hit in ipairs(hl) do if hit[1] and hit[1].Parent and hit[2] and hit[2].Parent then table.insert(v, hit) end end
                if #v > 0 then pcall(function() regH:FireServer(ph, v, aid) end) end
            end
        end
    end)
end
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.04)
        if Cfg.AttackAuraAlways and not State.FruitPriorityActive then
            pcall(function()
                local char = plr.Character
                if not char then return end
                local hrp = char:FindFirstChild("HumanoidRootPart")
                local hum = char:FindFirstChildOfClass("Humanoid")
                if not hrp or not hum or hum.Health <= 0 then return end
                local nb = getNearbyEntities(FRUIT_M1_RANGE)
                if #nb > 0 then -- Leaked By SL | Join https://discord.gg/zNyHGU6eUK
                    local now = tick()
                    if now - State.LastAttack >= Cfg.AttackDelay then
                        State.LastAttack = now
                        checkEquipBuso()
                        attackTarget(nb[1])
                    end
                end
            end)
        end
    end
end)
local function getTargetMob(tn)
    if not tn then return nil end
    if State.CurrentTargetMob and isMobIgnored(State.CurrentTargetMob) then State.CurrentTargetMob = nil end
    if State.CurrentTargetMob and State.CurrentTargetMob.Parent then
        if Players:GetPlayerFromCharacter(State.CurrentTargetMob) or Players:FindFirstChild(State.CurrentTargetMob.Name) then
            unfreezeMob(State.CurrentTargetMob)
            State.CurrentTargetMob = nil
        else
            local h = State.CurrentTargetMob:FindFirstChildOfClass("Humanoid")
            local hp = State.CurrentTargetMob:FindFirstChild("HumanoidRootPart") or State.CurrentTargetMob:FindFirstChild("Head") or State.CurrentTargetMob:FindFirstChildWhichIsA("BasePart")
            if h and h.Health > 0 and hp and mobMatches(State.CurrentTargetMob.Name, tn, State.CurrentTargetMob) then return State.CurrentTargetMob
            else
                unfreezeMob(State.CurrentTargetMob)
                State.CurrentTargetMob = nil
                -- Want more leaked hubs? Join SL | Source Leak: https://discord.gg/zNyHGU6eUK
            end
        end
    end
    local nearest = nil
    local sd = math.huge
    local char = plr.Character
    local hrp = char and char:FindFirstChild("HumanoidRootPart")
    if not hrp then return nil end
    local tl = normalize(tn)
    local exact = {}
    local partial = {}
    local conts = { Workspace:FindFirstChild("Enemies"), Workspace:FindFirstChild("Characters"), Workspace:FindFirstChild("Mobs") }
    for _, ct in ipairs(conts) do
        if ct then
            for _, e in ipairs(ct:GetChildren()) do
                if e:IsA("Model") and e ~= char and not Players:GetPlayerFromCharacter(e) and not Players:FindFirstChild(e.Name) then
                    local rn = e.Name
                    local cl = rn:lower()
                    if not cl:find("giver") and not cl:find("quest") and not cl:find("dealer") then
                        local h = e:FindFirstChildOfClass("Humanoid")
                        local eh = e:FindFirstChild("HumanoidRootPart") or e:FindFirstChild("Head") or e:FindFirstChildWhichIsA("BasePart")
                        if h and h.Health > 0 and eh then
                            local ec = normalize(e.Name)
                            if isMobIgnored(e) then
                            elseif tl == "dangerousprisoner" then
                                if isValidDangerous(e) then if ec == tl then table.insert(exact, e) else table.insert(partial, e) end end
                            elseif tl == "prisoner" then
                                if isValidPrisoner(e) then if ec == tl then table.insert(exact, e) else table.insert(partial, e) end end
                            elseif tl == "ruthlessprisoner" then
                                if isValidRuthless(e) then if ec == tl then table.insert(exact, e) else table.insert(partial, e) end end
                            else
                                if ec == tl then
                                    if mobMatches(e.Name, tn, e) then table.insert(exact, e) end
                                elseif mobMatches(e.Name, tn, e) then table.insert(partial, e) end
                            end
                        end
                    end
                end
            end
        end
    end
    local use = (#exact > 0) and exact or partial
    for _, e in ipairs(use) do
        local eh = e:FindFirstChild("HumanoidRootPart") or e:FindFirstChildWhichIsA("BasePart")
        if eh then
            local d = (hrp.Position - eh.Position).Magnitude
            if d < sd then
                sd = d
                nearest = e
            end
        end
    end
    State.CurrentTargetMob = nearest
    return nearest
end
RareChestItems = { "Fist of Darkness", "God's Chalice", "Fire Essence", "Hallow Essence", "Sweet Chalice", "Key", "Water Key", "Library Key" }
local function hasRareChestItem()
    local char = plr.Character
    local bp = plr:FindFirstChild("Backpack")
    for _, n in ipairs(RareChestItems) do
        if (char and char:FindFirstChild(n)) or (bp and bp:FindFirstChild(n)) then return true, n end
    end
    return false, nil
end
local function isValidChest(obj)
-- Free leaked sources daily in SL Discord: https://discord.gg/zNyHGU6eUK
    if not obj or not obj.Parent then return false end
    local n = obj.Name
    local nl = n:lower()
    if nl:find("chest") or n == "Chest1" or n == "Chest2" or n == "Chest3" then return true end
    return false
end
local function getChestPart(obj)
    if not obj or not obj.Parent then return nil end
    if obj:IsA("BasePart") then return obj end
    if obj:IsA("Model") then
        local r = obj:FindFirstChild("RootPart")
        if r and r:IsA("BasePart") then return r end
        for _, c in ipairs(obj:GetChildren()) do
            if c:IsA("BasePart") and (c:FindFirstChildWhichIsA("TouchTransmitter") or c:FindFirstChild("TouchInterest")) then return c end
        end
        return obj:FindFirstChildWhichIsA("BasePart")
    end
    return nil
end
local function registerChest(obj)
    if not isValidChest(obj) then return end
    local p = getChestPart(obj)
    if p and p:IsA("BasePart") and p.Parent then State.ChestRegistry[p] = { Object = obj, Part = p } end
end
local function unregisterChest(obj)
	if true then -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
		local _ = { "Leaked By SL", "Source Leak", "Join Discord: https://discord.gg/zNy" .. "HGU6eUK" }
	end
    if not obj then return end
    for p, d in pairs(State.ChestRegistry) do
        if d.Object == obj or d.Part == obj or not d.Part.Parent or not d.Object.Parent then State.ChestRegistry[p] = nil end
    end
end
local function scanAllChests()
    local conts = { Workspace:FindFirstChild("ChestModels"), Workspace:FindFirstChild("Chests"), Workspace:FindFirstChild("Map"), Workspace:FindFirstChild("Locations") }
    for _, ct in ipairs(conts) do
        if ct then
            for _, d in ipairs(ct:GetDescendants()) do
                if isValidChest(d) then registerChest(d) end
            end
        end
    end
    for _, o in ipairs(Workspace:GetChildren()) do
        if isValidChest(o) then registerChest(o)
        elseif o:IsA("Folder") or o:IsA("Model") then
            local nl = o.Name:lower()
            if not nl:find("enemy") and not nl:find("enemies") and not nl:find("character") and not nl:find("player") then
                for _, c in ipairs(o:GetChildren()) do --[[ SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join Discord ]]
                    if isValidChest(c) then registerChest(c) end
                end
            end
        end
    end
end
pcall(function()
    Workspace.DescendantAdded:Connect(function(d) if isValidChest(d) then registerChest(d) end end)
    Workspace.DescendantRemoving:Connect(function(d) unregisterChest(d) end)
end)
task.spawn(function()
    pcall(scanAllChests)
    while not State.IsScriptDestroyed do
        task.wait(3.0)
        if Cfg.AutoChestTween then pcall(scanAllChests) end
    end
end)
local function getChests()
    local out = {}
    local char = plr.Character
    -- SL Source Leak | https://discord.gg/zNyHGU6eUK | Join the server for more leaks
    local hrp = char and char:FindFirstChild("HumanoidRootPart")
    if not hrp then return out end
    local now = tick()
    for p, d in pairs(State.ChestRegistry) do
        if not p or not p.Parent or not d.Object or not d.Object.Parent then State.ChestRegistry[p] = nil
        else
            local cd = State.CollectedChests[p] or (d.Object and State.CollectedChests[d.Object])
            if (not cd or now > cd) and p.Transparency < 0.95 then table.insert(out, {Object = d.Object, Part = p, Distance = (hrp.Position - p.Position).Magnitude}) end
        end
    end
    table.sort(out, function(a, b) return a.Distance < b.Distance end)
    return out
end
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.03)
        if Cfg.AutoChestTween then
            if not State.FruitPriorityActive then
                if State.IsTransitioningDimension or State.UnderwaterTransitionActive then task.wait(0.2) continue end
                if State.IsChestTweening then task.wait(0.2) continue end
                pcall(function()
                    local char = plr.Character
                    local hrp = char and char:FindFirstChild("HumanoidRootPart")
                    local hum = char and char:FindFirstChildOfClass("Humanoid")
                    if not hrp or not hum or hum.Health <= 0 then return end -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
                    if Cfg.StopWhenGetItemInChest then
                        if hasRareChestItem() then
                            Cfg.AutoChestTween = false
                            resetPhysics()
                            return
                        end
                    end
                    local cs = getChests()
                    if #cs > 0 then
                        State.IsChestTweening = true
                        local tgt = cs[1]
                        local cp = tgt.Part
                        if cp and cp.Parent then
                            local cpos = cp.Position
                            local ct = cpos + Vector3.new(0, 1.5, 0)
                            for _, p in ipairs(char:GetDescendants()) do if p:IsA("BasePart") then p.CanCollide = false p.CanTouch = false p.CanQuery = false end end
                            if cp:IsA("BasePart") then cp.CanCollide = false end
                            local cm = cp.Parent
                            if cm and cm:IsA("Model") then for _, p in ipairs(cm:GetChildren()) do if p:IsA("BasePart") then p.CanCollide = false end end end
                            local tt = 0.15
                            local d = (hrp.Position - ct).Magnitude
                            if d > 200 then tt = math.clamp(d / 800, 0.15, 0.5) end
                            local ti = TweenInfo.new(tt, Enum.EasingStyle.Linear, Enum.EasingDirection.Out)
                            local tw = TweenService:Create(hrp, ti, { CFrame = CFrame.new(ct) })
                            local done = false
                            tw.Completed:Connect(function() done = true end)
                            tw:Play()
                            local ws = tick()
                            while not done and tick() - ws < 3 and not State.IsScriptDestroyed do
                                if not Cfg.AutoChestTween then break end
                                task.wait(0.02)
                            end
                            task.wait(0.03)
                            if hrp and cp and cp.Parent then
                                pcall(function()
                                    firetouchinterest(hrp, cp, 0)
                                    task.wait(0.01)
                                    firetouchinterest(hrp, cp, 1)
                                end)
                                pcall(function()
                                -- Leaked by SL Community | Source Leak [https://discord.gg/zNyHGU6eUK]
                                    local rp = cp.Parent and cp.Parent:FindFirstChild("RootPart")
                                    if rp and rp ~= cp then
                                        firetouchinterest(hrp, rp, 0)
                                        task.wait(0.01)
                                        firetouchinterest(hrp, rp, 1)
                                    end
                                end)
                            end
                            local ex = tick() + 25
                            State.CollectedChests[cp] = ex
                            if tgt.Object then State.CollectedChests[tgt.Object] = ex end
                            task.wait(0.02)
                        end
                        State.IsChestTweening = false
                    else task.wait(0.3) end
                end)
            end
        end
    end
end)
QuestRegistry = {
    {MinLvl=1, MaxLvl=9, Quest="BanditQuest1", Level=1, Mob="Bandit", Giver=CFrame.new(1049.89, 14.70, 1556.50), Spawn=CFrame.new(1145, 45, 1634)},
    {MinLvl=10, MaxLvl=14, Quest="JungleQuest", Level=1, Mob="Monkey", Giver=CFrame.new(-1681.39, 50.08, 176.28), Spawn=CFrame.new(-1448, 50, 175)},
    {MinLvl=15, MaxLvl=29, Quest="JungleQuest", Level=2, Mob="Gorilla", Giver=CFrame.new(-1681.39, 50.08, 176.28), Spawn=CFrame.new(-1240, 35, -500)},
    {MinLvl=30, MaxLvl=39, Quest="BuggyQuest1", Level=1, Mob="Pirate", Giver=CFrame.new(-1149.13, 17.31, 3859.09), Spawn=CFrame.new(-1205, 35, 3915)},
    {MinLvl=40, MaxLvl=59, Quest="BuggyQuest1", Level=2, Mob="Brute", Giver=CFrame.new(-1149.13, 17.31, 3859.09), Spawn=CFrame.new(-1379, 35, 4165)},
    {MinLvl=60, MaxLvl=74, Quest="DesertQuest", Level=1, Mob="Desert Bandit", Giver=CFrame.new(925.98, 5.91, 4202.35), Spawn=CFrame.new(932, 30, 4485)},
    {MinLvl=75, MaxLvl=89, Quest="DesertQuest", Level=2, Mob="Desert Officer", Giver=CFrame.new(925.98, 5.91, 4202.35), Spawn=CFrame.new(1549.45, 13.73, 4162.95)},
    {MinLvl=90, MaxLvl=99, Quest="SnowQuest", Level=1, Mob="Snow Bandit", Giver=CFrame.new(1398.51, 78.04, -1308.18), Spawn=CFrame.new(1288, 120, -1443)},
    {MinLvl=100, MaxLvl=119, Quest="SnowQuest", Level=2, Mob="Snowman", Giver=CFrame.new(1398.51, 78.04, -1308.18), Spawn=CFrame.new(1185, 120, -1512)},
    {MinLvl=120, MaxLvl=149, Quest="MarineQuest2", Level=1, Mob="Chief Petty Officer", Giver=CFrame.new(-4699.26, 5.90, 4223.11), Spawn=CFrame.new(-4880, 40, 4260)},
    {MinLvl=150, MaxLvl=174, Quest="SkyQuest", Level=1, Mob="Sky Bandit", Giver=CFrame.new(-5401.20, 410.73, -699.60), Spawn=CFrame.new(-5401.20, 410.73, -699.60)},
    {MinLvl=175, MaxLvl=189, Quest="SkyQuest", Level=2, Mob="Dark Master", Giver=CFrame.new(-5401.20, 410.73, -699.60), Spawn=CFrame.new(-5327.40, 501.51, -393.54)},
    {MinLvl=190, MaxLvl=209, Quest="PrisonerQuest", Level=1, Mob="Prisoner", Giver=CFrame.new(5201.80, 19.57, 736.50), Spawn=CFrame.new(4900, 35, 500)},
    {MinLvl=210, MaxLvl=249, Quest="PrisonerQuest", Level=2, Mob="Dangerous Prisoner", Giver=CFrame.new(5201.80, 19.57, 736.50), Spawn=CFrame.new(5500, 35, 740)},
    {MinLvl=250, MaxLvl=274, Quest="ColosseumQuest", Level=1, Mob="Toga Warrior", Giver=CFrame.new(-1342.36, 12.50, -2922.55), Spawn=CFrame.new(-1800, 35, -2750)},
    {MinLvl=275, MaxLvl=299, Quest="ColosseumQuest", Level=2, Mob="Gladiator", Giver=CFrame.new(-1342.36, 12.50, -2922.55), Spawn=CFrame.new(-1200.07, 12.21, -3280.36), Spawn2=CFrame.new(-1195.26, 12.21, -3043.74)},
    {MinLvl=300, MaxLvl=324, Quest="MagmaQuest", Level=1, Mob="Military Soldier", Giver=CFrame.new(-5310.97, 18.48, 8482.49), Spawn=CFrame.new(-5400, 35, 8450)},
    {MinLvl=325, MaxLvl=374, Quest="MagmaQuest", Level=2, Mob="Military Spy", Giver=CFrame.new(-5310.97, 18.48, 8482.49), Spawn=CFrame.new(-5800, 90, 8800)},
    {MinLvl=375, MaxLvl=399, Quest="FishmanQuest", Level=1, Mob="Fishman Warrior", Giver=CFrame.new(61399.55, 24.95, 1634.21), Spawn=CFrame.new(60913.85, 28.0, 1499.78)},
    {MinLvl=400, MaxLvl=449, Quest="FishmanQuest", Level=2, Mob="Fishman Commando", Giver=CFrame.new(61399.55, 24.95, 1634.21), Spawn=CFrame.new(61763.85, 28.0, 1449.78)},
    {MinLvl=450, MaxLvl=474, Quest="SkyExp1Quest", Level=1, Mob="God's Guard", Giver=CFrame.new(-4312.09, 1087.13, -562.31), Spawn=CFrame.new(-4299.66, 1087.13, -429.21)},
    {MinLvl=475, MaxLvl=524, Quest="SkyExp1Quest", Level=2, Mob="Shanda", Giver=CFrame.new(-5951.63, 5469.17, 2090.01), Spawn=CFrame.new(-5988.37, 5545.00, 1875.78)},
    {MinLvl=525, MaxLvl=549, Quest="SkyExp2Quest", Level=1, Mob="Royal Squad", Giver=CFrame.new(-7028.44, 5591.92, 1349.17), Spawn=CFrame.new(-6834.03, 5549.47, 1190.33)},
    {MinLvl=550, MaxLvl=624, Quest="SkyExp2Quest", Level=2, Mob="Royal Soldier", Giver=CFrame.new(-7028.44, 5591.92, 1349.17), Spawn=CFrame.new(-7024.23, 5540.58, 970.86)},
    {MinLvl=625, MaxLvl=649, Quest="FountainQuest", Level=1, Mob="Galley Pirate", Giver=CFrame.new(5256.94, 76.10, 4082.96), Spawn=CFrame.new(5536, 45, 3977)},
    {MinLvl=650, MaxLvl=9999, Quest="FountainQuest", Level=2, Mob="Galley Captain", Giver=CFrame.new(5256.94, 76.10, 4082.96), Spawn=CFrame.new(5650, 45, 4950)},
}
Quest2Data = {
    MilitaryDetective = CFrame.new(4854.04, 5.65, 742.69), IceDoor = CFrame.new(1291.32, 23.58, -1359.04),
    IceAdmiralSpawn = CFrame.new(1251.33, 21.21, -1386.33), ExperiencedCaptain = CFrame.new(-460.76, 73.01, 299.81)
}
SEA1_BOSS_DATA = {
    ["The Gorilla King"] = { Name = "The Gorilla King", Spawn = CFrame.new(-1235.76, 13.90, -510.01) },
    ["Chef"] = { Name = "Chef", Spawn = CFrame.new(-1117.31, 27.30, 4082.57) },
    ["The Saw"] = { Name = "The Saw", Spawn = CFrame.new(-753.80, 4.95, 1598.00) },
    ["The Yeti"] = { Name = "The Yeti", Spawn = CFrame.new(1137.52, 98.41, -1612.54) },
    ["Mob Leader"] = { Name = "Mob Leader", Spawn = CFrame.new(-2852.69, 4.11, 5369.49) },
    ["Vice Admiral"] = { Name = "Vice Admiral", Spawn = CFrame.new(-4934.81, 14.21, 4335.63) },
    ["Warden"] = { Name = "Warden", Spawn = CFrame.new(5581.78, 2.14, 736.09) },
    ["Magma Admiral"] = { Name = "Magma Admiral", Spawn = CFrame.new(-5618.45, 57.82, 8671.69) },
    ["Fishman Lord"] = { Name = "Fishman Lord", Spawn = CFrame.new(61352.83, 65.22, 1101.01) },
    ["Wysper"] = { Name = "Wysper", Spawn = CFrame.new(-6191.98, 5469.16, 1872.59) },
    ["Thunder God"] = { Name = "Thunder God", Spawn = CFrame.new(-7117.93, 5593.60, 202.49) },
    ["Cyborg"] = { Name = "Cyborg", Spawn = CFrame.new(6208.76, 7.60, 4905.41) },
    -- [Source Leak] Leaked By SL | Join Discord: https://discord.gg/zNyHGU6eUK
    ["Greybeard"] = { Name = "Greybeard", Spawn = CFrame.new(-4906.89, 14.21, 4192.19) }
}
local function isSea1BossMatch(mn, sb)
    if not mn or not sb then return false end
    local n = mn:lower():gsub("%[.-%]", ""):gsub("[^a-z0-9]", "")
    local s = sb:lower()
    if s:find("gorilla") then return n:find("gorillaking") ~= nil
    elseif s:find("chef") then return n:find("chef") ~= nil or n:find("bobby") ~= nil
    elseif s:find("saw") then return n:find("saw") ~= nil
    elseif s:find("yeti") then return n:find("yeti") ~= nil
    elseif s:find("mob leader") or s:find("mobleader") then return n:find("mobleader") ~= nil
    elseif s:find("vice admiral") or s:find("viceadmiral") then return n:find("viceadmiral") ~= nil
    elseif s:find("warden") then return n:find("warden") ~= nil and not n:find("chief")
    elseif s:find("magma admiral") or s:find("magmaadmiral") then return n:find("magmaadmiral") ~= nil
    elseif s:find("fishman lord") or s:find("fishmanlord") then return n:find("fishmanlord") ~= nil
    elseif s:find("wysper") then return n:find("wysper") ~= nil
    elseif s:find("thunder") or s:find("enel") then return n:find("thundergod") ~= nil or n:find("enel") ~= nil
    elseif s:find("cyborg") then return n:find("cyborg") ~= nil
    elseif s:find("greybeard") then return n:find("greybeard") ~= nil or n:find("grey beard") ~= nil
    end
    return false
end
local function findSea1Boss(sb)
    if not sb then return nil end
    local conts = { Workspace:FindFirstChild("Enemies"), Workspace:FindFirstChild("Bosses"), Workspace:FindFirstChild("Characters"), Workspace }
    for _, ct in ipairs(conts) do
        if ct then
            for _, o in ipairs(ct:GetChildren()) do
                if o:IsA("Model") and not Players:GetPlayerFromCharacter(o) and not Players:FindFirstChild(o.Name) then
                    local h = o:FindFirstChildOfClass("Humanoid")
                    local hp = o:FindFirstChild("HumanoidRootPart") or o:FindFirstChildWhichIsA("BasePart")
                    if h and h.Health > 0 and hp then if isSea1BossMatch(o.Name, sb) then return o end end
                end
            end
        end
    end
    return nil
end
local function getBossTimer(sb)
    local pg = plr:FindFirstChild("PlayerGui")
    local kw = {}
    local s = sb:lower()
    if s:find("gorilla") then kw = {"gorilla"}
    elseif s:find("chef") then kw = {"chef", "bobby"}
    elseif s:find("saw") then kw = {"saw"}
    elseif s:find("yeti") then kw = {"yeti"}
    elseif s:find("mob leader") or s:find("mobleader") then kw = {"mob leader", "mobleader"}
    elseif s:find("vice admiral") or s:find("viceadmiral") then kw = {"vice admiral", "viceadmiral"}
    elseif s:find("warden") then kw = {"warden"}
    elseif s:find("magma admiral") or s:find("magmaadmiral") then kw = {"magma admiral", "magmaadmiral"}
    elseif s:find("fishman lord") or s:find("fishmanlord") then kw = {"fishman lord", "fishmanlord"}
    elseif s:find("wysper") then kw = {"wysper"}
    elseif s:find("thunder") or s:find("enel") then kw = {"thunder god", "thundergod", "enel"}
    elseif s:find("cyborg") then kw = {"cyborg"}
    elseif s:find("greybeard") then kw = {"greybeard", "grey beard"}
    else kw = {s} end
    if pg then
        for _, d in ipairs(pg:GetDescendants()) do
            if d:IsA("TextLabel") and d.Visible and d.Text and d.Text ~= "" then
                local t = d.Text:lower()
                local mt = false
                for _, k in ipairs(kw) do if t:find(k, 1, true) then mt = true break end end
                if not mt and d.Parent then
                    local pn = d.Parent.Name:lower()
                    for _, k in ipairs(kw) do if pn:find(k, 1, true) then mt = true break end end
                    -- More paid scripts leaked for free in SL Discord: https://discord.gg/zNyHGU6eUK
                end
                if mt then
                    local m, s2 = t:match("(%d+)%s*:%s*(%d+)")
                    if m and s2 then
                        local sec = (tonumber(m) or 0) * 60 + (tonumber(s2) or 0)
                        if sec > 0 then return sec, true end
                    end
                    local so = t:match("(%d+)%s*s")
                    if so then
                        local sec = tonumber(so) or 0
                        if sec > 0 then return sec, true end
                    end
                end
            end
        end
    end
    return 0, false
end
local function findIceAdmiral()
    local conts = { Workspace:FindFirstChild("Enemies"), Workspace:FindFirstChild("Bosses"), Workspace:FindFirstChild("Characters"), Workspace }
    for _, ct in ipairs(conts) do
        if ct then
            for _, o in ipairs(ct:GetChildren()) do
                if o:IsA("Model") then
                    local n = o.Name:lower()
                    if n:find("ice admiral") or n == "iceadmiral" then
                        local h = o:FindFirstChildOfClass("Humanoid")
                        if h and h.Health > 0 then return o end
                    end
                end
            end
        end
    end
    return nil
end
local function equipItemByName(n)
    pcall(function()
        local char = plr.Character
        local bp = plr:FindFirstChild("Backpack")
        if not char or not bp then return end
        local hum = char:FindFirstChildOfClass("Humanoid")
        if not hum then return end
        local t = bp:FindFirstChild(n) or char:FindFirstChild(n)
        if t and t.Parent == bp then hum:EquipTool(t) end
    end)
end
local function getPlayerLevel()
    local lvl = 1
    local d = plr:FindFirstChild("Data")
    if d and d:FindFirstChild("Level") then lvl = tonumber(d.Level.Value) or 1
    elseif plr:FindFirstChild("leaderstats") and plr.leaderstats:FindFirstChild("Level") then lvl = tonumber(plr.leaderstats.Level.Value) or 1 end
    return lvl
end
local function getCurrentQuestInfo()
    local lvl = getPlayerLevel()
    for _, e in ipairs(QuestRegistry) do
        if lvl >= e.MinLvl and lvl <= e.MaxLvl then return e.Quest, e.Level, e.Mob, e.Giver, e.Spawn, e.Spawn2 end
    end
    local last = QuestRegistry[#QuestRegistry]
    return last.Quest, last.Level, last.Mob, last.Giver, last.Spawn, last.Spawn2
end
local function getQuestByLevel()
    local lvl = getPlayerLevel()
    for _, e in ipairs(QuestRegistry) do if lvl >= e.MinLvl and lvl <= e.MaxLvl then return e end end
    return QuestRegistry[#QuestRegistry]
    -- Get the latest leaked Roblox scripts in SL Discord: https://discord.gg/zNyHGU6eUK
end
local function findQuestByTitle(t)
    if not t or t == "" then return nil end
    local lt = t:lower()
    for _, e in ipairs(QuestRegistry) do if lt:find(e.Mob:lower(), 1, true) then return e end end
    return getQuestByLevel()
end
local function takeQuest(qd)
    local cf = getCommF()
    if not cf then return false end
    pcall(function() cf:InvokeServer("StartQuest", qd.Quest, qd.Level) end)
    return true
end
local function startHighSpeedWatcher()
    if State.HighSpeedWatcherConn then return end
    State.HighSpeedWatcherConn = RunService.RenderStepped:Connect(function()
        if not Cfg.AutoFarmLevel then return end
        if State.QuestState ~= "FARMING" then
            State.WasFramePresent = false
            return
        end
        local present = isQuestFramePresent()
        if present then
            State.WasFramePresent = true
            local q = readTrackedQuest()
            if q then
                State.LastProgressSnapshot = q
                State.LastQuestTitleSaved = q.Title
                State.LastKnownProgress = q.ProgressText
            end
            return
        end
        if not State.QuestJustCompleted then
            State.QuestJustCompleted = true
            local char = plr.Character
            local hrp = char and char:FindFirstChild("HumanoidRootPart")
            if not hrp then return end
            if State.CurrentTargetMob then pcall(function() unfreezeMob(State.CurrentTargetMob) end) end
            State.CurrentTargetMob = nil
            State.FastAttackTarget = nil
            clearAllFreezes()
            State.CurrentQuestData = nil
            State.QuestState = "IDLE"
            State.QuestCooldown = 0
            State.WasFramePresent = false
        end
    end)
end
startHighSpeedWatcher()
local function saveFarmState()
    State.SavedFarmState = {
        QuestState = State.QuestState,
        CurrentQuestData = State.CurrentQuestData and {
            Quest = State.CurrentQuestData.Quest, Level = State.CurrentQuestData.Level, Mob = State.CurrentQuestData.Mob,
            Giver = State.CurrentQuestData.Giver, Spawn = State.CurrentQuestData.Spawn, Spawn2 = State.CurrentQuestData.Spawn2,
        } or nil,
        LockedQuestTitle = State.LockedQuestTitle, PatrolIndex = State.PatrolIndex, PatrolLastSwitch = State.PatrolLastSwitch,
        CurrentTargetMob = State.CurrentTargetMob, LastKnownProgress = State.LastKnownProgress, LastQuestTitleSaved = State.LastQuestTitleSaved,
    }
end
local function restoreFarmState()
    if not State.SavedFarmState then
        State.QuestState = "IDLE"
        State.QuestCooldown = 0
        State.CurrentQuestData = nil
        -- SL | Source Leak Community - Join us at https://discord.gg/zNyHGU6eUK
        State.LockedQuestTitle = nil
        State.PatrolIndex = 1
        State.PatrolLastSwitch = 0
        State.QuestJustCompleted = false
        return
    end
    State.QuestState = State.SavedFarmState.QuestState or "IDLE"
    State.CurrentQuestData = State.SavedFarmState.CurrentQuestData
    State.LockedQuestTitle = State.SavedFarmState.LockedQuestTitle
    State.PatrolIndex = State.SavedFarmState.PatrolIndex or 1
    State.PatrolLastSwitch = State.SavedFarmState.PatrolLastSwitch or 0
    State.CurrentTargetMob = State.SavedFarmState.CurrentTargetMob
    State.LastKnownProgress = State.SavedFarmState.LastKnownProgress
    State.LastQuestTitleSaved = State.SavedFarmState.LastQuestTitleSaved
    State.QuestCooldown = 0
    State.QuestJustCompleted = false
    if State.QuestState == "FARMING" and State.CurrentQuestData then State.LockedQuestTitle = State.CurrentQuestData.Mob end
end
task.spawn(function()
    while not State.IsScriptDestroyed do
        local evt = RunService.PreSimulation or RunService.Heartbeat
        evt:Wait()
        if Cfg.AutoFarmLevel then
            if not State.FruitPriorityActive then
                equipWeapon(true)
                pcall(function()
                    local char = plr.Character
                    if not char then return end
                    local hrp = char:FindFirstChild("HumanoidRootPart")
                    local hum = char:FindFirstChildOfClass("Humanoid")
                    if not hrp or not hum or hum.Health <= 0 then return end
                    checkEquipBuso()
                    if State.IsTransitioningDimension or State.UnderwaterTransitionActive then return end
                    local lq = readTrackedQuest()
                    if lq and lq.Title and lq.Title ~= "" then State.LockedQuestTitle = lq.Title end
                    if lq and State.QuestState == "IDLE" then
                        State.QuestState = "FARMING"
                        State.CurrentQuestData = findQuestByTitle(lq.Title) or getQuestByLevel()
                        State.LastProgressSnapshot = lq
                        State.LastQuestTitleSaved = lq.Title
                        State.LastKnownProgress = lq.ProgressText
                    end
                    if State.QuestJustCompleted then
                        State.QuestJustCompleted = false
                        State.LastProgressSnapshot = nil
                        State.LastQuestTitleSaved = nil
                        State.LastKnownProgress = nil
                        if State.CurrentTargetMob then pcall(function() unfreezeMob(State.CurrentTargetMob) end) end
                        State.CurrentTargetMob = nil
                        State.FastAttackTarget = nil
                        clearAllFreezes()
                        local qn, ql, qm, qg, qs, qs2 = getCurrentQuestInfo()
                        State.CurrentQuestData = { Quest = qn, Level = ql, Mob = qm, Giver = qg, Spawn = qs, Spawn2 = qs2 }
                        State.QuestState = "GOING_TO_GIVER"
                        State.QuestCooldown = 0
                        State.LockedQuestTitle = nil
                        State.PatrolIndex = 1
                        State.PatrolLastSwitch = 0
                        return
                    end -- SL | Source Leak [https://discord.gg/zNyHGU6eUK]
                    if State.QuestState == "IDLE" then
                        local qn, ql, qm, qg, qs, qs2 = getCurrentQuestInfo()
                        State.CurrentQuestData = { Quest = qn, Level = ql, Mob = qm, Giver = qg, Spawn = qs, Spawn2 = qs2 }
                        State.QuestState = "GOING_TO_GIVER"
                        State.QuestCooldown = tick()
                        --[[ Join SL | Source Leak Discord for more free script sources: https://discord.gg/zNyHGU6eUK ]]
                        State.PatrolIndex = 1
                        State.PatrolLastSwitch = 0
                        return
                    end
                    if State.QuestState == "GOING_TO_GIVER" then
                        if tick() - State.QuestCooldown < 0.4 then
                            local cf = readTrackedQuest()
                            if cf and cf.Current > 0 and cf.Current < cf.Goal then
                                State.QuestState = "FARMING"
                                State.CurrentQuestData = findQuestByTitle(cf.Title) or State.CurrentQuestData
                                State.LockedQuestTitle = cf.Title
                                return
                            end
                        end
                        if not State.CurrentQuestData then State.QuestState = "IDLE" return end
                        local gp = State.CurrentQuestData.Giver.Position
                        local d = (hrp.Position - gp).Magnitude
                        if d > 6 then moveToTarget(State.CurrentQuestData.Giver)
                        else
                            if State.BodyVelocity and State.BodyVelocity.Parent == hrp then State.BodyVelocity.Velocity = Vector3.zero end
                            hrp.AssemblyLinearVelocity = Vector3.zero
                            hrp.AssemblyAngularVelocity = Vector3.zero
                            hrp.CFrame = CFrame.new(gp + Vector3.new(0, 3, 0))
                            State.QuestState = "TAKING_QUEST"
                            State.QuestCooldown = tick()
                        end
                        return
                    end
                    if State.QuestState == "TAKING_QUEST" then
                        if not State.CurrentQuestData then State.QuestState = "IDLE" return end
                        if tick() - State.QuestCooldown < 0.3 then return end
                        local eq = readTrackedQuest()
                        if eq then
                            State.QuestState = "FARMING"
                            State.QuestCooldown = tick()
                            State.CurrentQuestData = findQuestByTitle(eq.Title) or State.CurrentQuestData
                            State.LockedQuestTitle = eq.Title
                            return
                        end
                        takeQuest(State.CurrentQuestData)
                        task.wait(0.4)
                        local c = readTrackedQuest()
                        if c then
                            State.QuestState = "FARMING"
                            State.QuestCooldown = tick()
                            State.QuestJustCompleted = false
                            State.LockedQuestTitle = c.Title
                        else State.QuestCooldown = tick() - 0.2 end
                        return
                    end
                    if State.QuestState == "FARMING" then
                        if State.QuestJustCompleted then return end
                        if not lq then
                            State.QuestJustCompleted = false
                            if State.CurrentTargetMob then pcall(function() unfreezeMob(State.CurrentTargetMob) end) end
                            State.CurrentTargetMob = nil
                            State.FastAttackTarget = nil
                            clearAllFreezes()
                            if State.LockedQuestTitle and State.LockedQuestTitle ~= "" then
                                local info = findQuestByTitle(State.LockedQuestTitle)
                                if info then State.CurrentQuestData = info State.QuestState = "FARMING" return end
                            end
                            local qn, ql, qm, qg, qs, qs2 = getCurrentQuestInfo()
                            State.CurrentQuestData = { Quest = qn, Level = ql, Mob = qm, Giver = qg, Spawn = qs, Spawn2 = qs2 }
                            State.QuestState = "GOING_TO_GIVER"
                            --[=[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] | Daily leaks in our Discord ]=]
                            State.QuestCooldown = 0
                            return
                        end
                        if not State.CurrentQuestData then State.CurrentQuestData = findQuestByTitle(lq.Title) or getQuestByLevel() end
                        State.LockedQuestTitle = lq.Title
                        local mn = State.CurrentQuestData.Mob
                        local tm = State.CurrentTargetMob
                        if tm and tm.Parent then
                            local th = tm:FindFirstChildOfClass("Humanoid")
                            if not th or th.Health <= 0 then tm = nil end
                        end
                        if not tm or not tm.Parent then tm = getTargetMob(mn) end
                        if tm and tm:FindFirstChild("HumanoidRootPart") then
                            local mh = tm:FindFirstChildOfClass("Humanoid")
                            if mh and mh.Health > 0 then
                                if isMobIgnored(tm) then
                                    unfreezeMob(tm)
                                    State.CurrentTargetMob = nil
                                    State.FastAttackTarget = nil
                                    tm = nil -- Join SL Discord: https://discord.gg/zNyHGU6eUK
                                else
                                    checkEquipBuso()
                                    freezeMob(tm)
                                    State.FastAttackTarget = tm
                                    local mb = (State.FrozenPositions[tm] and State.FrozenPositions[tm].Position) or tm.HumanoidRootPart.Position
                                    local so = Cfg.SafeDistance
                                    if type(so) ~= "Vector3" then so = Vector3.new(0, 10, 0) end
                                    local nt = mb + so
                                    if validNum(nt.X) then moveToTarget(CFrame.new(nt)) end
                                    if tick() - State.LastAttack >= Cfg.AttackDelay then
                                        State.LastAttack = tick()
                                        attackTarget(tm)
                                    end
                                end
                            else
                                unfreezeMob(tm)
                                State.CurrentTargetMob = nil
                                State.FastAttackTarget = nil
                            end
                        else
                            clearAllFreezes()
                            State.FastAttackTarget = nil
                            if State.CurrentQuestData.Spawn2 then
                                local now = tick()
                                if not State.PatrolLastSwitch or State.PatrolLastSwitch == 0 then
                                    State.PatrolIndex = 1
                                    State.PatrolLastSwitch = now
                                end
                                local el = now - State.PatrolLastSwitch
                                if el >= 2 then
                                    State.PatrolIndex = (State.PatrolIndex == 1) and 2 or 1
                                    State.PatrolLastSwitch = now
                                end
                                local pcf = (State.PatrolIndex == 1) and State.CurrentQuestData.Spawn or State.CurrentQuestData.Spawn2
                                if (hrp.Position - pcf.Position).Magnitude > 5 then moveToTarget(pcf)
                                else
                                    if State.BodyVelocity and State.BodyVelocity.Parent == hrp then State.BodyVelocity.Velocity = Vector3.zero end
                                    hrp.AssemblyLinearVelocity = Vector3.zero
                                    hrp.AssemblyAngularVelocity = Vector3.zero
                                end
                            else moveToTarget(State.CurrentQuestData.Spawn) end
                        end
                        return
                    end
                end) --[[ Leaked By SL | https://discord.gg/zNyHGU6eUK ]]
                -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
            end
        end
    end
end)
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.08)
        if Cfg.AutoFarmBosses then
            if not State.FruitPriorityActive then
                if State.IsTransitioningDimension or State.UnderwaterTransitionActive then task.wait(0.2) continue end
                pcall(function()
                    local char = plr.Character
                    if not char then return end
                    local hrp = char:FindFirstChild("HumanoidRootPart")
                    local hum = char:FindFirstChildOfClass("Humanoid")
                    if not hrp or not hum or hum.Health <= 0 then return end
                    local bn = Cfg.SelectedSea1Boss or "The Gorilla King"
                    local info = SEA1_BOSS_DATA[bn]
                    if not info or not info.Spawn then return end
                    local needsUW = (bn == "Fishman Lord")
                    local inUW = isInsideUW()
                    if needsUW and not inUW then
                        if not State.FishmanLordTransitionLock then
                            State.FishmanLordTransitionLock = true
                            State.FishmanLordState = "ENTERING_UNDERWATER"
                            goIntoUW()
                            task.wait(0.5)
                            State.FishmanLordTransitionLock = false
                            State.FishmanLordState = "FARMING"
                        end
                        return
                    end
                    if not needsUW and inUW then
                        if not State.FishmanLordTransitionLock then
                            State.FishmanLordTransitionLock = true
                            State.FishmanLordState = "EXITING_UNDERWATER"
                            goOutUW()
                            task.wait(0.5)
                            State.FishmanLordTransitionLock = false
                            State.FishmanLordState = "FARMING"
                        end
                        return
                    end
                    local bObj = findSea1Boss(bn)
                    local rem, isAct = getBossTimer(bn)
                    if isAct and rem > 0 and not (bObj and bObj.Parent) then
                        if State.WasFarmingBoss then
                            State.WasFarmingBoss = false
                            State.FastAttackTarget = nil
                            clearAllFreezes()
                            pcall(resetPhysics)
                            pcall(stopBodyMovers)
                            pcall(stopAllMovement)
                        end
                        task.wait(0.5)
                        return
                    end
                    if bObj and bObj.Parent then
                        local bh = bObj:FindFirstChild("HumanoidRootPart") or bObj:FindFirstChildWhichIsA("BasePart")
                        local bhu = bObj:FindFirstChildOfClass("Humanoid")
                        if bh and bhu and bhu.Health > 0 then
                            if not State.WasFarmingBoss then
                                State.BossArrivalSettleTime = tick() + 0.5
                                State.SkyIslandFlightLock = true
                            end
                            -- Leaked by SL | Join our Discord for more leaked sources: https://discord.gg/zNyHGU6eUK
                            State.WasFarmingBoss = true
                            checkEquipBuso()
                            equipWeapon(true)
                            freezeMob(bObj)
                            State.FastAttackTarget = bObj
                            local bb = (State.FrozenPositions[bObj] and State.FrozenPositions[bObj].Position) or bh.Position
                            local so = Cfg.SafeDistance or Vector3.new(0, 10, 0)
                            local nt = bb + so
                            local cp = hrp.Position
                            local d = (nt - cp).Magnitude
                            if tick() < State.BossArrivalSettleTime then
                                if State.BodyVelocity and State.BodyVelocity.Parent == hrp then State.BodyVelocity.Velocity = Vector3.zero end
                                pcall(function()
                                    hrp.AssemblyLinearVelocity = Vector3.zero
                                    hrp.AssemblyAngularVelocity = Vector3.zero
                                end)
                            else
                                State.SkyIslandFlightLock = false
                                if d > 8 then moveToTarget(CFrame.new(nt))
                                else
                                    if State.BodyVelocity and State.BodyVelocity.Parent == hrp then State.BodyVelocity.Velocity = Vector3.zero end
                                    pcall(function()
                                        hrp.AssemblyLinearVelocity = Vector3.zero
                                        hrp.AssemblyAngularVelocity = Vector3.zero
                                    end) -- Leaked by SL | Join https://discord.gg/zNyHGU6eUK for more leaks
                                end
                            end
                            local now = tick()
                            if now - State.LastAttack >= Cfg.AttackDelay then
                                State.LastAttack = now
                                attackTarget(bObj)
                            end
                            pcall(performFastHit)
                            return
                        else
                            if State.WasFarmingBoss then
                                State.WasFarmingBoss = false
                                State.SkyIslandFlightLock = false
                                State.BossArrivalSettleTime = 0
                                unfreezeMob(bObj)
                                State.FastAttackTarget = nil
                                clearAllFreezes()
                                pcall(resetPhysics)
                                pcall(stopBodyMovers)
                                pcall(stopAllMovement)
                            end
                            return
                        end
                    end
                    local sp = info.Spawn.Position
                    local ds = (hrp.Position - sp).Magnitude
                    if ds > 40 then
                        local now = tick()
                        if State.SkyIslandFlightLock then return end
                        if now - State.LastBossFlyStartTime < 1.5 then return end
                        State.LastBossFlyStartTime = now
                        State.SkyIslandFlightLock = true
                        State.WasFarmingBoss = true
                        State.LastBossDistance = ds
                        flyToPrecise(sp, Cfg.FlySpeed, 45, 12)
                        pcall(resetPhysics)
                        pcall(stopBodyMovers)
                        pcall(stopAllMovement)
                        task.wait(0.4)
                        State.SkyIslandFlightLock = false
                        -- SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join SL for more script leaks
                    else
                        if State.WasFarmingBoss then
                            State.WasFarmingBoss = false
                            State.SkyIslandFlightLock = false
                            State.BossArrivalSettleTime = 0
                            State.FastAttackTarget = nil
                            clearAllFreezes()
                            pcall(resetPhysics)
                            pcall(stopBodyMovers)
                            pcall(stopAllMovement)
                        end
                        task.wait(0.4)
                    end
                end)
            end
        else
            if State.WasFarmingBoss then
                State.WasFarmingBoss = false
                State.SkyIslandFlightLock = false
                State.BossArrivalSettleTime = 0
                State.FastAttackTarget = nil
                clearAllFreezes()
                pcall(resetPhysics)
                pcall(stopBodyMovers)
                pcall(stopAllMovement)
            end
            if State.FishmanLordTransitionLock then State.FishmanLordTransitionLock = false end
            -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
            -- Join SL Discord for more leaked sources: https://discord.gg/zNyHGU6eUK
            State.FishmanLordState = "IDLE"
        end
    end
end)
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.2)
        if Cfg.AutoSecondSeaQuest then
            local _ = pcall(function()
                local lvl = getPlayerLevel()
                if lvl < 700 then return end
                local char = plr.Character
                local hrp = char and char:FindFirstChild("HumanoidRootPart")
                local hum = char and char:FindFirstChildOfClass("Humanoid")
                if not hrp or not hum or hum.Health <= 0 then return end
                local cf = getCommF()
                if not cf then return end
                local bp = plr:FindFirstChild("Backpack")
                local hasKey = (bp and bp:FindFirstChild("Key")) or (char and char:FindFirstChild("Key"))
                if not hasKey then
                    pcall(function()
                        cf:InvokeServer("DressrosaQuestProgress", "Detective")
                    end) -- [SL Source Leak] https://discord.gg/zNyHGU6eUK
                    task.wait(0.5)
                    bp = plr:FindFirstChild("Backpack")
                    hasKey = (bp and bp:FindFirstChild("Key")) or (char and char:FindFirstChild("Key"))
                end
                if not Cfg.AutoSecondSeaQuest then stopBodyMovers() return end
                if hasKey then
                    if (hrp.Position - Quest2Data.IceDoor.Position).Magnitude > 6 then
                        equipItemByName("Key")
                        moveToTarget(Quest2Data.IceDoor)
                    else
                        equipItemByName("Key")
                        local door = Workspace:FindFirstChild("Map") and Workspace.Map:FindFirstChild("Ice") and Workspace.Map.Ice:FindFirstChild("Door")
                        if door and door:IsA("BasePart") then
                            firetouchinterest(hrp, door, 0)
                            task.wait(0.05)
                            -- Source leaked by SL | Get more free hub sources at https://discord.gg/zNyHGU6eUK
                            firetouchinterest(hrp, door, 1)
                        end
                        task.wait(1)
                    end
                    return
                end
                if not Cfg.AutoSecondSeaQuest then stopBodyMovers() return end
                local ia = findIceAdmiral()
                if ia and ia.Parent then
                    local sh = ia:FindFirstChild("HumanoidRootPart") or ia:FindFirstChildWhichIsA("BasePart")
                    local shu = ia:FindFirstChildOfClass("Humanoid")
                    if sh and shu and shu.Health > 0 then
                        checkEquipBuso()
                        equipWeapon(true)
                        freezeMob(ia)
                        local mb = (State.FrozenPositions[ia] and State.FrozenPositions[ia].Position) or sh.Position
                        local so = Cfg.SafeDistance or Vector3.new(0, 10, 0)
                        local nt = mb + so
                        if validNum(nt.X) then moveToTarget(CFrame.new(nt)) end
                        if tick() - State.LastAttack >= Cfg.AttackDelay then
                            State.LastAttack = tick()
                            attackTarget(ia)
                        end
                    else unfreezeMob(ia) end
                    return
                end
                if not Cfg.AutoSecondSeaQuest then stopBodyMovers() return end
                if (hrp.Position - Quest2Data.ExperiencedCaptain.Position).Magnitude > 8 then
                    moveToTarget(Quest2Data.ExperiencedCaptain)
                else --[=[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] ]=]
                    stopBodyMovers()
                    cf:InvokeServer("TravelDressrosa")
                    cf:InvokeServer("DressrosaQuestProgress", "Captain")
                    task.wait(1.5)
                end
            end)
            if not Cfg.AutoSecondSeaQuest then
                pcall(stopBodyMovers)
                pcall(stopAllMovement)
            end
        end
    end
end)
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.05)
        if Cfg.AutoFarmNearest then
            if not State.FruitPriorityActive then
                if State.IsTransitioningDimension or State.UnderwaterTransitionActive then task.wait(0.2) continue end
                pcall(function()
                    local char = plr.Character
                    if not char then return end
                    local hrp = char:FindFirstChild("HumanoidRootPart")
                    local hum = char:FindFirstChildOfClass("Humanoid")
                    if not hrp or not hum or hum.Health <= 0 then return end
                    checkEquipBuso()
                    equipWeapon()
                    local nm = nil
                    local nd = math.huge
                    local enf = Workspace:FindFirstChild("Enemies")
                    if enf then
                        for _, e in ipairs(enf:GetChildren()) do
                            if e ~= char and not Players:GetPlayerFromCharacter(e) and not Players:FindFirstChild(e.Name) then
                                if not isMobIgnored(e) then
                                    local eh = e:FindFirstChildOfClass("Humanoid")
                                    -- [SL] Leaked By SL | Source Leak - Join https://discord.gg/zNyHGU6eUK
                                    local ehp = e:FindFirstChild("HumanoidRootPart") or e:FindFirstChildWhichIsA("BasePart")
                                    if eh and eh.Health > 0 and ehp then
                                        local d = (hrp.Position - ehp.Position).Magnitude
                                        if d < nd and d < 3500 then
                                            nd = d
                                            nm = e
                                        end
                                    end
                                end
                            end -- Source Leak (SL) | Join our Discord: https://discord.gg/zNyHGU6eUK
                        end
                    end
                    if nm and nm:FindFirstChild("HumanoidRootPart") then
                        freezeMob(nm)
                        local mb = (State.FrozenPositions[nm] and State.FrozenPositions[nm].Position) or nm.HumanoidRootPart.Position
                        local so = Cfg.SafeDistance
                        if type(so) ~= "Vector3" then so = Vector3.new(0, 10, 0) end
                        local nt = mb + so
                        if validNum(nt.X) then moveToTarget(CFrame.new(nt)) end
                        local now = tick()
                        if now - State.LastAttack >= Cfg.AttackDelay then
                            State.LastAttack = now
                            attackTarget(nm)
                        end
                    else clearAllFreezes() end
                end)
            end
        end
    end
end)
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.15)
        if Cfg.AutoStats then
            if State.StatsLocked then task.wait(0.3)
            else
                State.StatsLocked = true
                pcall(function()
                    local cf = getCommF()
                    if not cf then State.StatsLocked = false return end
                    local sel = {}
                    if Cfg.AutoStatsMelee then table.insert(sel, "Melee") end
                    if Cfg.AutoStatsDefense then table.insert(sel, "Defense") end
                    if Cfg.AutoStatsSword then table.insert(sel, "Sword") end
                    if Cfg.AutoStatsGun then table.insert(sel, "Gun") end
                    if Cfg.AutoStatsFruit then table.insert(sel, "Demon Fruit") end
                    if #sel == 0 then State.StatsLocked = false return end
                    local step = math.clamp(tonumber(Cfg.StatPointStep) or 3, 1, 100)
                    local sc = #sel
                    local data = plr:FindFirstChild("Data")
                    local function getPoints()
                        if data and data:FindFirstChild("Points") then return tonumber(data.Points.Value) or 0
                        elseif plr:FindFirstChild("Points") then return tonumber(plr.Points.Value) or 0 end
                        return 0
                    end --[==[ SL | Source Leak: https://discord.gg/zNyHGU6eUK ]==]
                    local function addBatch(sn, amt)
                        if amt <= 0 then return end
                        pcall(function() cf:InvokeServer("AddPoint", sn, amt) end)
                        if sn == "Blox Fruit" then pcall(function() cf:InvokeServer("AddPoint", "Demon Fruit", amt) end) end
                    end
                    if State.StatsRotationIndex < 1 or State.StatsRotationIndex > sc then State.StatsRotationIndex = 1 end
                    local total = 0
                    local maxAdds = 500
                    local safety = 0
                    local maxLoops = 200
                    -- Join SL Discord for more open-source & leaked scripts: https://discord.gg/zNyHGU6eUK
                    while getPoints() > 0 and safety < maxLoops and total < maxAdds do
                        safety = safety + 1
                        if not Cfg.AutoStats or State.IsScriptDestroyed then break end
                        local pb = getPoints()
                        if pb <= 0 then break end
                        local cycDone = false
                        local added = false
                        while not cycDone and getPoints() > 0 do
                            if not Cfg.AutoStats or State.IsScriptDestroyed then break end
                            local sn = sel[State.StatsRotationIndex]
                            local cp = getPoints()
                            if cp <= 0 then break end
                            local amt = math.min(step, cp)
                            if amt <= 0 then break end
                            addBatch(sn, amt)
                            added = true
                            total = total + 1
                            task.wait(0.12)
                            State.StatsRotationIndex = State.StatsRotationIndex + 1
                            if State.StatsRotationIndex > sc then
                                State.StatsRotationIndex = 1
                                cycDone = true
                            end
                        end
                        if not added then break end
                        local pa = getPoints()
                        if pa <= 0 then break end
                        if pa >= pb then
                            task.wait(0.25)
                            if getPoints() >= pb then break end
                        end
                    end
                end)
                State.StatsLocked = false
            end -- More free leaks at SL Discord: https://discord.gg/zNyHGU6eUK
        else
            State.StatsRotationIndex = 1
            State.StatsLocked = false
        end
    end
end)
local function rollRegularGacha()
    pcall(function()
        local args = { [1] = { ["Context"] = "Purchase", ["BoxName"] = "ZiolesGacha" } }
        local gachaRF = nil
        pcall(function() gachaRF = RS.Modules.Net:FindFirstChild("RF/GachaNetworkRF") end)
        if not gachaRF then pcall(function()
            local net = RS:FindFirstChild("Modules") and RS.Modules:FindFirstChild("Net")
            gachaRF = net and net:FindFirstChild("RF/GachaNetworkRF")
        end) end
        if not gachaRF then gachaRF = RS:WaitForChild("Modules", 1):WaitForChild("Net", 1):FindFirstChild("RF/GachaNetworkRF") end
        if gachaRF then gachaRF:InvokeServer(unpack(args)) end
        task.spawn(function()
            local i = 0
            while i < 500 and not State.IsScriptDestroyed do
                i = i + 1
                if tryClose() then break end
            end
        end)
    end)
end
task.spawn(function()
    while not State.IsScriptDestroyed do
        if Cfg.AutoRandomFruit then
            rollRegularGacha()
            -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] | More leaks in our Discord
            task.wait(2.5)
        else task.wait(0.3) end
    end
end)
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.15)
        if Cfg.AutoCollectFruit then
            pcall(function()
                if State.IsTransitioningDimension or State.UnderwaterTransitionActive then task.wait(0.2) return end
                local char = plr.Character
                local hrp = char and char:FindFirstChild("HumanoidRootPart")
                local hum = char and char:FindFirstChildOfClass("Humanoid")
                if not hrp or not hum or hum.Health <= 0 then
                    if State.IsCollectingFruitMoving then -- Leaked By SL | Join https://discord.gg/zNyHGU6eUK
                        State.IsCollectingFruitMoving = false
                        State.FruitPriorityActive = false
                        stopBodyMovers()
                    end
                    return
                end
                local gf = findAllGroundFruits()
                if #gf > 0 then
                    State.FruitPriorityActive = true
                    if State.CurrentTargetMob then
                        pcall(function() unfreezeMob(State.CurrentTargetMob) end)
                        State.CurrentTargetMob = nil
                    end
                    clearAllFreezes()
                    for _, fi in ipairs(gf) do
                        if not Cfg.AutoCollectFruit then break end
                        local fp = fi.Handle
                        if not fp or not fp.Parent then continue end
                        char = plr.Character
                        hrp = char and char:FindFirstChild("HumanoidRootPart")
                        if not hrp then break end
                        if fi.IsKnown then
                            pcall(function()
                                fp.AssemblyLinearVelocity = Vector3.zero
                                fp.AssemblyAngularVelocity = Vector3.zero
                                fp.CFrame = hrp.CFrame + (hrp.CFrame.LookVector * 2.5) + Vector3.new(0, 0.2, 0)
                                if fi.Object and fi.Object:IsA("Model") then fi.Object:PivotTo(hrp.CFrame + (hrp.CFrame.LookVector * 2.5)) end
                            end)
                            task.wait(0.08)
                            pcall(function()
                                firetouchinterest(hrp, fp, 0)
                                task.wait(0.03)
                                firetouchinterest(hrp, fp, 1)
                            end)
                            task.wait(0.05)
                        else
                            local fpos = fp.Position
                            local d = (hrp.Position - fpos).Magnitude
                            if d > 4 then
                                State.FruitCollectFlightSession = State.FruitCollectFlightSession + 1
                                local ss = State.FruitCollectFlightSession
                                State.IsCollectingFruitMoving = true
                                State.FruitCollectTargetObject = fi.Object
                                local ct = fpos
                                local fs = tick()
                                while Cfg.AutoCollectFruit and State.FruitCollectFlightSession == ss and not State.IsScriptDestroyed do
                                    char = plr.Character
                                    hrp = char and char:FindFirstChild("HumanoidRootPart")
                                    if not hrp then break end
                                    if not fi.Object or not fi.Object.Parent then break end
                                    --[[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join SL Discord ]]
                                    local np = fp.Position
                                    if not np then break end
                                    ct = np
                                    if (hrp.Position - ct).Magnitude <= 4 then break end
                                    if tick() - fs > 15 then break end
                                    moveToTarget(CFrame.new(ct))
                                    task.wait(0.05)
                                end
                                if not Cfg.AutoCollectFruit then
                                    stopBodyMovers()
                                    State.IsCollectingFruitMoving = false
                                    State.FruitPriorityActive = false
                                    State.FruitCollectTargetObject = nil
                                    return
                                end
                                if State.FruitCollectFlightSession ~= ss then
                                    stopBodyMovers()
                                    State.IsCollectingFruitMoving = false
                                    State.FruitCollectTargetObject = nil
                                    continue
                                end
                                char = plr.Character
                                hrp = char and char:FindFirstChild("HumanoidRootPart")
                                if hrp and fp and fp.Parent then
                                    if (hrp.Position - fp.Position).Magnitude <= 8 then
                                        State.IsCollectingFruitMoving = false
                                        stopBodyMovers()
                                        pcall(function()
                                            firetouchinterest(hrp, fp, 0)
                                            task.wait(0.03)
                                            firetouchinterest(hrp, fp, 1)
                                        end)
                                        task.wait(0.05)
                                    else
                                        State.IsCollectingFruitMoving = false
                                        stopBodyMovers()
                                    end
                                else
                                    State.IsCollectingFruitMoving = false
                                    stopBodyMovers()
                                end
                                State.FruitCollectTargetObject = nil
                            else
                                if State.IsCollectingFruitMoving then
                                    State.IsCollectingFruitMoving = false
                                    stopBodyMovers()
                                end
                                pcall(function()
                                    firetouchinterest(hrp, fp, 0)
                                    task.wait(0.03)
                                    firetouchinterest(hrp, fp, 1)
                                end)
                                task.wait(0.05)
                            end
                        end
                        if Cfg.AutoStoreFruit then
                            local bp = plr:FindFirstChild("Backpack")
                            if bp then
                                for _, t in ipairs(bp:GetChildren()) do
                                    if t:IsA("Tool") and isPhysicalFruit(t) then
                                        storeAllHeldFruits()
                                        break
                                    end
                                end
                            end
                            --[=[ SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join our Discord for more leaks ]=]
                        end
                        dismissFruitDialog(Cfg.AutoStoreFruit)
                    end
                    State.FruitPriorityActive = false
                    State.IsCollectingFruitMoving = false
                    State.LastFruitPickupTime = tick()
                    if not isMovementActive() then stopBodyMovers() end
                else
                    if State.FruitPriorityActive then
                        State.FruitPriorityActive = false
                        if State.IsCollectingFruitMoving then
                            State.IsCollectingFruitMoving = false
                            stopBodyMovers()
                        end
                    end
                end
            end)
        else
            if State.FruitPriorityActive or State.IsCollectingFruitMoving then
                State.FruitPriorityActive = false --[[ SL | Source Leak [https://discord.gg/zNyHGU6eUK] - Join Discord ]]
                State.IsCollectingFruitMoving = false
                State.FruitCollectFlightSession = State.FruitCollectFlightSession + 1
                State.FruitCollectTargetObject = nil
                stopBodyMovers()
                cleanExitFlight()
            end
        end
    end
end)
local function createESPBox(ado, name, color, isFruit, isUnknown)
    if not ado or not ado.Parent then return nil end
    local bw = 160
    local bh = 40
    local bts = 13
    local ex = ado:FindFirstChild("Irish_ESP")
    if ex and ex:IsA("BillboardGui") then
        local l = ex:FindFirstChildWhichIsA("TextLabel")
        if l then
            l.TextColor3 = color or Color3.fromRGB(255, 185, 0)
            l.Text = name
            ex.Size = UDim2.new(0, bw, 0, bh)
            l.TextSize = bts
            if isUnknown then
                l.TextStrokeTransparency = 0.35
                l.TextStrokeColor3 = Color3.fromRGB(0, 0, 0)
            else
                l.TextStrokeTransparency = 0
                l.TextStrokeColor3 = Color3.fromRGB(0, 0, 0)
            end
            return ex, l
        end
    end
    if ex then pcall(function() ex:Destroy() end) end
    local bb = Instance.new("BillboardGui")
    bb.Name = "Irish_ESP"
    bb.Adornee = ado
    bb.Size = UDim2.new(0, bw, 0, bh)
    bb.StudsOffset = Vector3.new(0, 3, 0)
    bb.AlwaysOnTop = true
    bb.ResetOnSpawn = false
    bb.LightInfluence = 0
    bb.MaxDistance = math.huge
    bb.ClipsDescendants = false
    bb.Active = false
    bb.Parent = ado -- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]
    --[==[ Leaked By SL | Source Leak | Join https://discord.gg/zNyHGU6eUK for free sources ]==]
    local lb = Instance.new("TextLabel")
    lb.Size = UDim2.new(1, 0, 1, 0)
    lb.BackgroundTransparency = 1
    lb.TextColor3 = color or Color3.fromRGB(255, 185, 0)
    if isUnknown then lb.TextStrokeTransparency = 0.35
    else lb.TextStrokeTransparency = 0 end
    lb.TextStrokeColor3 = Color3.fromRGB(0, 0, 0)
    lb.Font = Enum.Font.GothamBold
    lb.TextSize = bts
    lb.TextScaled = false
    lb.TextWrapped = false
    lb.TextXAlignment = Enum.TextXAlignment.Center
    lb.TextYAlignment = Enum.TextYAlignment.Center
    lb.Text = name
    lb.Parent = bb
    return bb, lb
end
task.spawn(function()
    while not State.IsScriptDestroyed do
        task.wait(0.1)
        pcall(function()
            local char = plr.Character
            local myHrp = char and char:FindFirstChild("HumanoidRootPart")
            if Cfg.FruitESPEnabled then
                local gf = findAllGroundFruits()
                local act = {}
                for _, it in ipairs(gf) do
                    local o = it.Object
                    local h = it.Handle
                    if not o or not h or not h.Parent then continue end
                    act[o] = true
                    local dn = it.Name
                    local rc = Color3.fromRGB(255, 185, 0)
                    local rk = it.RawName
                    local iu = false
                    if rk and rk ~= "unknown" then
                        local fk = normFruitKey(rk)
                        for dbk, info in pairs(FRUIT_INFO_DATABASE) do
                            if fk:find(dbk, 1, true) or dbk:find(fk, 1, true) then
                                rc = RARITY_COLORS[info.Rarity] or rc
                                dn = info.Name
                                break
                            end
                        end
                    else -- SL | Source Leak [https://discord.gg/zNyHGU6eUK]
                        rc = mysteryColor()
                        iu = true
                    end
                    local ex = State.ActiveESPItems[o]
                    if not ex or not ex.Gui or not ex.Gui.Parent or ex.Part ~= h or ex.BaseName ~= dn then
                        if ex and ex.Gui then pcall(function() ex.Gui:Destroy() end) end
                        local bb, lb = createESPBox(h, dn, rc, true, iu)
                        if bb and lb then State.ActiveESPItems[o] = { Gui = bb, Label = lb, Part = h, BaseName = dn, IsUnknown = iu } end
                    end
                end
                for o, d in pairs(State.ActiveESPItems) do
                    if not o.Parent or not act[o] then
                        if d.Gui then pcall(function() d.Gui:Destroy() end) end
                        State.ActiveESPItems[o] = nil
                    end
                end
            end
            if Cfg.PlayerESPEnabled then
                for _, p in ipairs(Players:GetPlayers()) do
                    if p ~= plr and p.Character then
                    -- Want more leaked hubs? Join SL | Source Leak: https://discord.gg/zNyHGU6eUK
                        local ph = p.Character:FindFirstChild("HumanoidRootPart")
                        local phu = p.Character:FindFirstChildOfClass("Humanoid")
                        if ph and phu and phu.Health > 0 then
                            local ex = State.ActiveESPItems[p]
                            if not ex or not ex.Gui or not ex.Gui.Parent or ex.Part ~= ph then
                                if ex and ex.Gui then pcall(function() ex.Gui:Destroy() end) end
                                local tc = p.TeamColor and p.TeamColor.Color or Color3.fromRGB(59, 130, 246)
                                local bb, lb = createESPBox(ph, p.DisplayName or p.Name, tc, false, false)
                                if bb and lb then State.ActiveESPItems[p] = {Gui = bb, Label = lb, Part = ph, BaseName = p.DisplayName or p.Name, IsUnknown = false} end
                            end
                        end
                    end
                end
            end
            for o, d in pairs(State.ActiveESPItems) do
                local rm = false
                if not o or not o.Parent or not d.Part or not d.Part.Parent then rm = true
                elseif (o:IsA("Player") and not Cfg.PlayerESPEnabled) or (not o:IsA("Player") and not Cfg.FruitESPEnabled) then rm = true end
                if rm then
                    if d.Gui then pcall(function() d.Gui:Destroy() end) end
                    State.ActiveESPItems[o] = nil
                else
                    if myHrp and d.Part and d.Label then
                        if d.IsUnknown then
                            d.Label.TextColor3 = mysteryColor()
                            d.Label.TextStrokeTransparency = 0.35
                            d.Label.TextStrokeColor3 = Color3.fromRGB(0, 0, 0)
                        end
                        local dist = math.floor((myHrp.Position - d.Part.Position).Magnitude)
                        if Cfg.ESPShowDistance then d.Label.Text = string.format("%s [%dm]", d.BaseName, dist)
                        else d.Label.Text = d.BaseName end
                    end
                end
            end
        end)
    end
end)
plr.CharacterAdded:Connect(function(char)
    task.wait(1)
    if Cfg.PlayerMovementEnabled then
        local hum = char:FindFirstChildOfClass("Humanoid")
        if hum then
            hum.WalkSpeed = 16
            hum.JumpPower = Cfg.JumpPowerValue
            pcall(function() hum.UseJumpPower = true end)
        end
    end
end)
ISLAND_TELEPORTS = {
    {"Pirate Starter Island", CFrame.new(1182.71, 14.53, 1615.57)},
    {"Marine Starter Island", CFrame.new(-2570, 52, 2043)},
    {"Jungle", CFrame.new(-1611.03, 30.44, 82.99)},
    {"Pirate Village", CFrame.new(-1212.55, 17.31, 3954.24)},
    {"Desert Island", CFrame.new(925.86, 5.91, 4509.11)},
    {"Middle Town", CFrame.new(-655, 48, 1583)},
    {"Frozen Village", CFrame.new(1403.40, 78.04, -1407.00)},
    {"Marine Fortress", CFrame.new(-4766.27, 14.22, 4240.90)},
    {"Skylands Lower", CFrame.new(-5104.42, 305.00, -1010.38)},
    {"Skylands Upper 1", CFrame.new(-4342.00, 1115.00, -452.38)},
    {"Skylands Upper 2", CFrame.new(-5976.81, 5469.16, 2095.95)},
    {"Prison", CFrame.new(5160.31, 19.56, 736.87)},
    {"Colosseum", CFrame.new(-1183.88, 12.22, -3251.26)},
    {"Magma Village", CFrame.new(-5565.73, 18.48, 8389.98)},
    {"Underwater Entrance", CFrame.new(4034.11, 35, -1821.84)},
    {"Fountain City", CFrame.new(5225.71, 76.09, 4094.04)},
    -- Free leaked sources daily in SL Discord: https://discord.gg/zNyHGU6eUK
    {"Mob Island", CFrame.new(-2850, 48, 5320)},
    {"Saber Room", CFrame.new(-1448, 52, -32)}
}
local function resolveIslandCF(n, fb)
    for _, item in ipairs(ISLAND_TELEPORTS) do -- Join SL Discord: https://discord.gg/zNyHGU6eUK
        if item[1] == n then return item[2] end
    end
    return fb
end
Cfg.SelectedIslandCFrame = ISLAND_TELEPORTS[1][2]
Cfg.SelectedIslandName = ISLAND_TELEPORTS[1][1]
local Window = Fluent:CreateWindow({
    Title = "Irish Hub",
    SubTitle = "Blox Fruits",
    TabWidth = 160,
    Size = UDim2.fromOffset(560, 460),
    Acrylic = true,
    Theme = "Dark",
    MinimizeKey = Enum.KeyCode.LeftControl
})
local Tabs = {
    Farm     = Window:AddTab({ Title = "Farm",     Icon = "sword" }),
    Fruits   = Window:AddTab({ Title = "Fruits",   Icon = "apple" }),
    Stats    = Window:AddTab({ Title = "Stats",    Icon = "bar-chart" }),
    Teleport = Window:AddTab({ Title = "Teleport", Icon = "map-pin" }),
    Visuals  = Window:AddTab({ Title = "Visuals",  Icon = "eye" }),
    Settings = Window:AddTab({ Title = "Settings", Icon = "settings" }),
}
Tabs.Farm:AddSection("Weapon")
Tabs.Farm:AddDropdown("WeaponSelect", {
    Title = "Active Weapon",
    Values = {"Melee", "Sword", "Gun", "Blox Fruit"},
    Default = Cfg.SelectedWeapon,
    Multi = false,
    Callback = function(v)
        Cfg.SelectedWeapon = v
        equipWeapon(true)
    end
})
Tabs.Farm:AddSection("Level Farming")
Tabs.Farm:AddToggle("AutoFarmLevel", {
    Title = "Auto Farm Level",
    Description = "auto take quests and farm mobs",
    Default = false,
    Callback = function(v)
        if v then
            Cfg.AutoFarmLevel = true
            if State.SavedFarmState and State.ResumeFarmAfterToggle then
                restoreFarmState()
                State.ResumeFarmAfterToggle = false --[[ Leaked By SL | https://discord.gg/zNyHGU6eUK ]]
            else
                State.QuestState = "IDLE"
                State.QuestCooldown = 0
                State.CurrentQuestData = nil
                State.QuestStartTime = 0
                State.LockedQuestTitle = nil
                State.PatrolIndex = 1
                State.PatrolLastSwitch = 0
                clearAllFreezes()
            end
        else
            saveFarmState()
            State.ResumeFarmAfterToggle = true
            Cfg.AutoFarmLevel = false
            if State.CurrentTargetMob then
            -- SL Source Leak | https://discord.gg/zNyHGU6eUK | Join the server for more leaks
                pcall(function() unfreezeMob(State.CurrentTargetMob) end)
                State.CurrentTargetMob = nil
            end
            State.FastAttackTarget = nil
            clearAllFreezes()
            if not isMovementActive() then resetPhysics() end
        end
    end
})
Tabs.Farm:AddToggle("AutoFarmNearest", {
    Title = "Auto Farm Nearest",
    Description = "kill the closest enemy",
    Default = false,
    Callback = function(v)
        Cfg.AutoFarmNearest = v
        if not v and not isMovementActive() then resetPhysics() end
    end
})
Tabs.Farm:AddSection("Bosses")
local bossNames = {}
for k in pairs(SEA1_BOSS_DATA) do table.insert(bossNames, k) end
table.sort(bossNames)
Tabs.Farm:AddDropdown("SelectedBoss", {
    Title = "Select Boss",
    Values = bossNames,
    Default = Cfg.SelectedSea1Boss,
    Multi = false,
    Callback = function(v) Cfg.SelectedSea1Boss = v end
})
Tabs.Farm:AddToggle("AutoFarmBosses", { -- Leaked by SL | Join https://discord.gg/zNyHGU6eUK for more leaks
    Title = "Auto Farm Bosses",
    Description = "fly to boss only when spawned",
    Default = false,
    Callback = function(v)
        Cfg.AutoFarmBosses = v
        if not v then
            State.WasFarmingBoss = false
            clearAllFreezes()
            State.FastAttackTarget = nil
            State.FishmanLordTransitionLock = false
            State.FishmanLordState = "IDLE"
            State.SkyIslandFlightLock = false
            State.BossArrivalSettleTime = 0
            pcall(resetPhysics)
            pcall(stopBodyMovers)
            pcall(stopAllMovement)
            pcall(cleanExitFlight)
        end
    end
})
Tabs.Farm:AddSection("Chests")
Tabs.Farm:AddToggle("AutoChestTween", {
    Title = "Auto Chest Tween",
    Description = "fast non-stop chest sweep",
    Default = false,
    Callback = function(v)
        Cfg.AutoChestTween = v
        if not v and not isMovementActive() then resetPhysics() end
    end
})
Tabs.Farm:AddToggle("StopOnRareItem", {
    Title = "Stop When Get Item In Chest",
    Description = "halt on rare item",
    Default = true,
    Callback = function(v) Cfg.StopWhenGetItemInChest = v end
    -- Leaked by SL Community | Source Leak [https://discord.gg/zNyHGU6eUK]
})
Tabs.Farm:AddSection("Second Sea")
Tabs.Farm:AddToggle("AutoSecondSea", {
    Title = "Auto Second Sea Quest",
    Description = "auto complete dressrosa puzzle",
    Default = false,
    Callback = function(v)
        Cfg.AutoSecondSeaQuest = v
        if not v then
            pcall(stopAllMovement)
            pcall(stopBodyMovers)
        end
    end
})
Tabs.Fruits:AddSection("Auto Collect")
Tabs.Fruits:AddToggle("AutoCollectFruit", {
    Title = "Auto Collect Fruit",
    Description = "collect fruits on the ground",
    Default = false,
    Callback = function(v)
    	if true then
    		local _ = ("SL | Source Leak " .. "[https://discord.gg/" .. "zNyHGU6eUK] - Join SL Discord")
    	end --[[ Leaked By SL | Join SL Discord: https://discord.gg/zNyHGU6eUK ]]
        Cfg.AutoCollectFruit = v
        if not v then
            State.FruitPriorityActive = false
            State.IsCollectingFruitMoving = false
            State.FruitCollectFlightSession = State.FruitCollectFlightSession + 1
            State.FruitCollectTargetObject = nil
            stopBodyMovers()
            cleanExitFlight()
            if not isMovementActive() then resetPhysics() end
        else task.spawn(syncFruitInv) end
    end
})
Tabs.Fruits:AddToggle("AutoStoreFruit", {
    Title = "Auto Store Fruits",
    Default = false,
    Callback = function(v)
        Cfg.AutoStoreFruit = v
        if v then task.spawn(syncFruitInv) end
    end
})
Tabs.Fruits:AddToggle("AutoRandomFruit", {
    Title = "Auto Random Fruit",
    Description = "auto roll zioles gacha",
    Default = false,
    Callback = function(v) Cfg.AutoRandomFruit = v end
})
Tabs.Stats:AddSection("Points")
Tabs.Stats:AddSlider("StatStep", {
    Title = "Points per Batch",
    Default = 3,
    Min = 1,
    Max = 100,
    Rounding = 0,
    Callback = function(v) Cfg.StatPointStep = v end
})
Tabs.Stats:AddToggle("AutoStats", {
    Title = "Auto Stats",
    Description = "fair equal distribution",
    Default = false,
    Callback = function(v)
        Cfg.AutoStats = v
        if v then State.StatsRotationIndex = 1 end
    end
})
Tabs.Stats:AddSection("Select Stats")
-- [Source Leak] Leaked By SL | Join Discord: https://discord.gg/zNyHGU6eUK
Tabs.Stats:AddToggle("StatMelee",    {Title="Melee",       Default=false, Callback=function(v) Cfg.AutoStatsMelee = v end})
Tabs.Stats:AddToggle("StatDefense",  {Title="Defense",     Default=false, Callback=function(v) Cfg.AutoStatsDefense = v end})
Tabs.Stats:AddToggle("StatSword",    {Title="Sword",       Default=false, Callback=function(v) Cfg.AutoStatsSword = v end})
Tabs.Stats:AddToggle("StatGun",      {Title="Gun",         Default=false, Callback=function(v) Cfg.AutoStatsGun = v end})
Tabs.Stats:AddToggle("StatFruit",    {Title="Blox Fruit",  Default=false, Callback=function(v) Cfg.AutoStatsFruit = v end})
local islandNames = {}
for _, item in ipairs(ISLAND_TELEPORTS) do table.insert(islandNames, item[1]) end
Tabs.Teleport:AddSection("Island Travel")
Tabs.Teleport:AddDropdown("IslandSelect", {
    Title = "Select Island",
    Values = islandNames,
    Default = Cfg.SelectedIslandName or ISLAND_TELEPORTS[1][1],
    Multi = false,
    Callback = function(v)
        Cfg.SelectedIslandCFrame = resolveIslandCF(v, ISLAND_TELEPORTS[1][2])
        Cfg.SelectedIslandName = v
    end
})
Tabs.Teleport:AddToggle("AutoTeleportIsland", {
    Title = "Travel to Selected Island",
    Description = "fly smoothly to target",
    Default = false,
    Callback = function(v)
        Cfg.AutoTeleportIsland = v
        if v then
            if Cfg.TeleportFlightThread then task.cancel(Cfg.TeleportFlightThread) end
            Cfg.TeleportFlightThread = task.spawn(function()
                while Cfg.AutoTeleportIsland and not State.IsScriptDestroyed do
                    task.wait(0.05)
                    if not State.FruitPriorityActive then
                        if State.IsTransitioningDimension or State.UnderwaterTransitionActive then task.wait(0.2) continue end
                        if not Cfg.SelectedIslandCFrame then break end
                        local char = plr.Character
                        local hrp = char and char:FindFirstChild("HumanoidRootPart")
                        if hrp then -- [SL Source Leak] https://discord.gg/zNyHGU6eUK
                            if Cfg.SelectedIslandName == "Underwater Entrance" then
                                local inUW = isInsideUW()
                                if inUW then
                                    local tp = UW_INSIDE_POS
                                    if (tp - hrp.Position).Magnitude <= 15 then
                                        Cfg.AutoTeleportIsland = false
                                        cleanExitFlight()
                                        break
                                    else moveToTarget(CFrame.new(tp)) end
                                else
                                    if not State.UnderwaterTransitionActive then goIntoUW() end
                                    task.wait(0.3)
                                end
                            else
                                local tp
                                if typeof(Cfg.SelectedIslandCFrame) == "CFrame" then tp = Cfg.SelectedIslandCFrame.Position
                                elseif typeof(Cfg.SelectedIslandCFrame) == "Vector3" then tp = Cfg.SelectedIslandCFrame end
                                if tp then
                                    if (tp - hrp.Position).Magnitude <= 12 then
                                        Cfg.AutoTeleportIsland = false
                                        resetPhysics()
                                        break
                                    else moveToTarget(Cfg.SelectedIslandCFrame) end
                                end
                            end
                        end
                    end
                end
            end)
        else
        -- More paid scripts leaked for free in SL Discord: https://discord.gg/zNyHGU6eUK
            if Cfg.TeleportFlightThread then
                task.cancel(Cfg.TeleportFlightThread)
                Cfg.TeleportFlightThread = nil
            end
            State.UnderwaterTransitionActive = false
            State.UnderwaterEntryLock = false
            State.IsTransitioningDimension = false
            if not isMovementActive() then resetPhysics() end
        end
    end
})
Tabs.Visuals:AddSection("ESP")
Tabs.Visuals:AddToggle("FruitESP", {
    Title = "Fruit ESP",
    Description = "fruit names with rarity color + distance",
    Default = true,
    Callback = function(v) Cfg.FruitESPEnabled = v end
})
Tabs.Visuals:AddToggle("PlayerESP", {
    Title = "Player ESP",
    Description = "highlight other players",
    Default = true,
    Callback = function(v) Cfg.PlayerESPEnabled = v end
})
Tabs.Visuals:AddToggle("ESPShowDistance", {
    Title = "Show Distance",
    Default = true,
    Callback = function(v) Cfg.ESPShowDistance = v end
})
Tabs.Settings:AddSection("Combat")
Tabs.Settings:AddToggle("FastAttack", {
    Title = "Fast Attack",
    Description = "attack from distance when hold weapon",
    Default = true,
    Callback = function(v) Cfg.AttackAuraAlways = v end
})
Tabs.Settings:AddToggle("AutoBuso", {
    Title = "Auto Buso Haki",
    Description = "maintains active buso armament haki for max damage",
    Default = true,
    Callback = function(v) Cfg.AutoBuso = v end
})
Tabs.Settings:AddSlider("AttackDelay", {
    Title = "Attack Delay",
    Default = 0.01,
    Min = 0.01,
    Max = 0.5,
    Rounding = 2,
    Callback = function(v) Cfg.AttackDelay = v end
})
Tabs.Settings:AddSection("Movement")
Tabs.Settings:AddToggle("MovementControl", {
    Title = "Enable Movement Control",
    Description = "applies walk speed via body velocity",
    Default = false,
    Callback = function(v)
        Cfg.PlayerMovementEnabled = v
        local char = plr.Character
        if not char then return end
        local hum = char:FindFirstChildOfClass("Humanoid")
        if not hum then return end
        if v then
            if not State.OriginalWalkSpeed then State.OriginalWalkSpeed = hum.WalkSpeed end
            if not State.OriginalJumpPower then State.OriginalJumpPower = hum.JumpPower end
            pcall(function()
            -- Get the latest leaked Roblox scripts in SL Discord: https://discord.gg/zNyHGU6eUK
                hum.WalkSpeed = 16
                hum.JumpPower = Cfg.JumpPowerValue
                hum.UseJumpPower = true
            end)
        else
            if State.WalkBodyVelocity then
                pcall(function() State.WalkBodyVelocity:Destroy() end)
                State.WalkBodyVelocity = nil
            end
            pcall(function()
                hum.WalkSpeed = State.OriginalWalkSpeed or 16
                hum.JumpPower = State.OriginalJumpPower or 50
            end)
        end
    end
})
Tabs.Settings:AddSlider("WalkSpeed", {
    Title = "Walk Speed",
    Default = 16,
    Min = 16,
    Max = 300,
    Rounding = 0,
    Callback = function(v) Cfg.WalkSpeedValue = v end
})
Tabs.Settings:AddSlider("JumpPower", {
    Title = "Jump Power",
    Default = 50,
    Min = 50,
    Max = 500,
    Rounding = 0,
    Callback = function(v)
        Cfg.JumpPowerValue = v
        if Cfg.PlayerMovementEnabled then
            local char = plr.Character
            if char then
                local hum = char:FindFirstChildOfClass("Humanoid")
                if hum then
                    pcall(function() hum.JumpPower = v end)
                    pcall(function() hum.UseJumpPower = true end)
                end --[=[ Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK] ]=]
            end
        end
    end
})
Tabs.Settings:AddSection("Flight")
Tabs.Settings:AddSlider("FlySpeed", {
    Title = "Fly Speed",
    Default = 170,
    Min = 50,
    Max = 200,
    Rounding = 0,
    Callback = function(v) Cfg.FlySpeed = math.clamp(v, 50, 200) end
})
Window:SelectTab(1)
Fluent:Notify({
    Title = "Irish Hub",
    Content = "loaded",
    Duration = 3
})
do local _ = ("Leaked By SL | " .. "Source Leak | Join Discord: " .. "https://discord.gg/zNy" .. "HGU6eUK") end
do pcall(function() getgenv().SL_Discord = "https://discord.gg/zNyHGU6eUK" end) end
-- Join SL Discord for more free leaked sources: https://discord.gg/zNyHGU6eUK
-- Leaked By SL | Source Leak [https://discord.gg/zNyHGU6eUK]

local function InitFunModule(S, G, states, API)
    if not S or not G or not states or not API then return end

    local player = API.player
    local Camera = API.Camera
    local isTouchDevice = API.isTouchDevice
    local create = API.create
    local cCorner = API.cCorner
    local cStroke = API.cStroke
    local makeDraggable = API.makeDraggable
    local showNotification = API.showNotification
    local getText = API.getText
    local saveAutoRestoreSession = API.saveAutoRestoreSession

    local FunData = {
        connections = {},
        activeGlowsticks = {},
        shootingGlowsticks = setmetatable({}, {__mode = "k"}),
        glowstickRaycastCache = {},
        glowstickAngle = 0,
        lastGlowstickRay = 0,
        lastLightUpdate = 0,
        glowstickStatusLabel = nil,
        glowstickMobileBtn = nil,
        mobileTapConn = nil,
        globalPipeConn = nil,
        
        -- Оптимизированный кэш источников света и неоновых деталей
        lightsCache = setmetatable({}, {__mode = "k"}),
        neonPartsCache = setmetatable({}, {__mode = "k"}),
        lightAddedConn = nil,

        PipeData = {
            active = false,
            origSounds = {},
            origDecals = {},
            spawnedDecals = {},
            connections = {},
            queue = {},
            processing = false
        },
        currentTrackInfo = { name = "", isPlaying = false },
        musicInputBox = nil,

        -- Данные системы Archives Chair Manipulation
        ChairData = {
            active = false,
            heldChair = nil,
            heldRoot = nil,
            holdDistance = 14,
            rotYaw = 0,
            rotPitch = 0,
            noCollideList = {},
            ridingChair = nil,
            rideSeat = nil,
            mobileFlyUp = false,
            mobileFlyDown = false,
            mobilePad = nil,
            pcManualFrame = nil,
            pcManualExpanded = true,
            pcManualContent = nil,
            pcManualTitle = nil,
            pcManualToggleBtn = nil,
            pcManualLabels = {}
        },

        -- Данные системы ПОТУЖНОЛІТ / POTUJNOLIT
        HeliData = {
            modelData = nil,
            hud = nil,
            mobilePad = nil,
            isPiloting = false,
            isFalling = false,
            isCrashed = false,
            enginePower = 0,
            rotorAngle = 0,
            lightOn = false,
            heliPos = Vector3.new(0, 0, 0),
            heliYaw = 0,
            heliPitch = 0,
            heliRoll = 0,
            tumblePitchVel = 0,
            tumbleYawVel = 0,
            tumbleRollVel = 0,
            fwdVelocity = 0,
            vertVelocity = 0,
            isGrounded = false,
            mobileThrottle = 0,
            mobileSteer = 0,
            mobileVertical = 0,
            renderConn = nil,
            inputConn = nil
        },

        -- Данные универсального ресайзера (Universal Resizer)
        ResizerData = {
            active = false,
            mode = "ENLARGE", -- "ENLARGE" или "SHRINK"
            scaleStep = 1.25,
            hud = nil,
            mobileBtn = nil,
            modeBtn = nil,
            statusLabel = nil,
            toolInstance = nil,
            inputConn = nil,
            originalScales = setmetatable({}, {__mode = "k"})
        }
    }

    -- Синхронизируем инфо о треке с глобальным контекстом для водяного знака
    S.currentTrackInfo = FunData.currentTrackInfo

    -- ========================================================
    -- МУЗЫКАЛЬНЫЙ ПЛЕЕР
    -- ========================================================
    local CustomSound = Instance.new("Sound")
    CustomSound.Name = "HubUniversalCustomMusic"
    CustomSound.Volume = (states.musicVolume or 50) / 100
    CustomSound.Looped = (states.musicLoop ~= false)
    CustomSound.Parent = G.Services.SoundService

    local function playMusicTrack(id)
        id = tostring(id):gsub("%D", "")
        if id and id ~= "" then
            CustomSound.SoundId = "rbxassetid://" .. id
            CustomSound:Play()
            FunData.currentTrackInfo.isPlaying = true
            FunData.currentTrackInfo.name = "ID: " .. id
            task.spawn(function()
                pcall(function()
                    local info = G.Services.MarketplaceService:GetProductInfo(tonumber(id), Enum.InfoType.Asset)
                    if info and info.Name then
                        FunData.currentTrackInfo.name = info.Name
                    end
                end)
            end)
        end
    end

    local function pauseMusicTrack()
        if CustomSound.IsPlaying then
            CustomSound:Pause()
            FunData.currentTrackInfo.isPlaying = false
        elseif CustomSound.TimePosition > 0 then
            CustomSound:Resume()
            FunData.currentTrackInfo.isPlaying = true
        end
    end

    local function stopMusicTrack()
        CustomSound:Stop()
        FunData.currentTrackInfo.isPlaying = false
        FunData.currentTrackInfo.name = ""
    end

    -- ========================================================
    -- ИСПРАВЛЕННОЕ И ОПТИМИЗИРОВАННОЕ УПРАВЛЕНИЕ СВЕТОМ
    -- ========================================================
    local function handleLightObject(obj)
        if not obj or not obj:IsA("Light") then return end
        
        if not FunData.lightsCache[obj] then
            FunData.lightsCache[obj] = obj.Color
        end

        local parentPart = obj.Parent
        if parentPart and parentPart:IsA("BasePart") and parentPart.Material == Enum.Material.Neon then
            if not FunData.neonPartsCache[parentPart] then
                FunData.neonPartsCache[parentPart] = parentPart.Color
            end
        end

        local active = (states.newYearMode == true) or (states.customLight == true)
        if active then
            local col = states.newYearMode and G.Math.rgb(130, 180, 255) 
                or G.Math.rgb(tonumber(states.lightR) or 255, tonumber(states.lightG) or 0, tonumber(states.lightB) or 255)
            
            obj.Color = col
            if parentPart and parentPart:IsA("BasePart") and parentPart.Material == Enum.Material.Neon then
                parentPart.Color = col
            end
        end
    end

    local function scanAllLights()
        local ws = G.Services.Workspace
        local cr = ws:FindFirstChild("CurrentRooms")
        if cr then
            for _, desc in ipairs(cr:GetDescendants()) do
                if desc:IsA("Light") then
                    handleLightObject(desc)
                end
            end
        end
        for _, desc in ipairs(ws:GetChildren()) do
            if desc ~= cr then
                if desc:IsA("Light") then
                    handleLightObject(desc)
                elseif desc:IsA("Model") then
                    for _, sub in ipairs(desc:GetDescendants()) do
                        if sub:IsA("Light") then
                            handleLightObject(sub)
                        end
                    end
                end
            end
        end
    end

    local function updateLights()
        local active = (states.newYearMode == true) or (states.customLight == true)
        local col = states.newYearMode and G.Math.rgb(130, 180, 255) 
            or G.Math.rgb(tonumber(states.lightR) or 255, tonumber(states.lightG) or 0, tonumber(states.lightB) or 255)

        if active then
            if not FunData.lightAddedConn then
                FunData.lightAddedConn = G.Services.Workspace.DescendantAdded:Connect(function(desc)
                    if (states.newYearMode or states.customLight) and desc:IsA("Light") then
                        task.defer(function()
                            handleLightObject(desc)
                        end)
                    end
                end)
                FunData.connections[#FunData.connections + 1] = FunData.lightAddedConn
            end

            local count = 0
            for _ in pairs(FunData.lightsCache) do count = count + 1 break end
            if count == 0 then
                scanAllLights()
            end

            for light, origColor in pairs(FunData.lightsCache) do
                if light and light.Parent then
                    light.Color = col
                else
                    FunData.lightsCache[light] = nil
                end
            end

            for part, origColor in pairs(FunData.neonPartsCache) do
                if part and part.Parent then
                    part.Color = col
                else
                    FunData.neonPartsCache[part] = nil
                end
            end
        else
            if FunData.lightAddedConn then
                FunData.lightAddedConn:Disconnect()
                FunData.lightAddedConn = nil
            end

            for light, origColor in pairs(FunData.lightsCache) do
                if light and light.Parent then
                    light.Color = origColor
                end
            end
            for part, origColor in pairs(FunData.neonPartsCache) do
                if part and part.Parent then
                    part.Color = origColor
                end
            end

            table.clear(FunData.lightsCache)
            table.clear(FunData.neonPartsCache)
        end
    end

    -- ========================================================
    -- ЛОГИКА ГЛОУСТИКОВ
    -- ========================================================
    local function updateGlowstickList()
        if FunData.glowstickStatusLabel and FunData.glowstickStatusLabel.Parent then
            FunData.glowstickStatusLabel.Text = string.format("Glowsticks active: %d", #FunData.activeGlowsticks)
        end
    end

    local function scanGlowsticksOnce()
        local found = {}
        local function chk(obj)
            if obj.Name == "GlowstickLive" then
                local root = obj:IsA("BasePart") and obj or (obj:IsA("Model") and (obj.PrimaryPart or obj:FindFirstChildWhichIsA("BasePart")))
                if root then
                    found[#found + 1] = root
                end
            end
        end
        local ws = G.Services.Workspace
        for _, obj in ipairs(ws:GetChildren()) do chk(obj) end
        local cr = ws:FindFirstChild("CurrentRooms")
        if cr then
            for _, room in ipairs(cr:GetChildren()) do
                for _, obj in ipairs(room:GetChildren()) do chk(obj) end
            end
        end
        FunData.activeGlowsticks = found
        updateGlowstickList()
    end

    local function shootGlowstick(targetWorldPos)
        if #FunData.activeGlowsticks == 0 then
            scanGlowsticksOnce()
            if #FunData.activeGlowsticks == 0 then return end
        end
        local stick = table.remove(FunData.activeGlowsticks, 1)
        if not stick or not stick.Parent then return end
        FunData.shootingGlowsticks[stick] = true
        updateGlowstickList()

        local ws = G.Services.Workspace
        local cam = ws.CurrentCamera or Camera
        local mouse = player:GetMouse()
        local finalTarget = targetWorldPos or (mouse and mouse.Hit and mouse.Hit.Position) or (cam.CFrame.Position + cam.CFrame.LookVector * 100)
        local direction = (finalTarget - stick.Position).Unit
        stick.CanCollide = true

        local flyTime = 0
        local flyConn = nil
        flyConn = G.Services.RunService.Heartbeat:Connect(function(dt)
            flyTime = flyTime + dt
            if not stick or not stick.Parent or flyTime >= 3 then
                if flyConn then flyConn:Disconnect() end
                task.delay(3, function() FunData.shootingGlowsticks[stick] = nil end)
                return
            end
            local moveStep = direction * (130 * dt)
            local rayParams = RaycastParams.new()
            rayParams.FilterType = Enum.RaycastFilterType.Exclude
            rayParams.FilterDescendantsInstances = {player.Character, stick}
            local hit = ws:Raycast(stick.Position, moveStep, rayParams)
            if hit then
                stick.CFrame = G.Math.cf(hit.Position)
                stick.AssemblyLinearVelocity = G.Math.v3()
                stick.AssemblyAngularVelocity = G.Math.v3()
                if flyConn then flyConn:Disconnect() end
                task.delay(3, function() FunData.shootingGlowsticks[stick] = nil end)
            else
                stick.CFrame = G.Math.cf(stick.Position + moveStep) * CFrame.Angles(G.Math.rad(flyTime * 360), G.Math.rad(flyTime * 180), 0)
                stick.AssemblyLinearVelocity = G.Math.v3()
            end
        end)
    end

    local function updateGlowstickMobileBtn()
        if FunData.glowstickMobileBtn then
            FunData.glowstickMobileBtn.Visible = isTouchDevice and (states.glowstickEnabled == true)
        end
    end

    FunData.glowstickMobileBtn = create("TextButton", {
        Name = "GlowstickShootBtn",
        Size = G.Math.ud2(0, 52, 0, 52),
        Position = G.Math.ud2(1, -75, 0.7, -26),
        BackgroundColor3 = G.Math.rgb(24, 24, 30),
        BackgroundTransparency = 0.1,
        Text = "🎯",
        TextColor3 = G.Math.rgb(255, 255, 255),
        Font = Enum.Font.GothamBlack,
        TextSize = 20,
        Visible = false,
        Parent = S.ScreenGui,
        ZIndex = 20
    }, { cCorner(26), cStroke(G.Math.rgb(70, 70, 85), 1.5) })
    makeDraggable(FunData.glowstickMobileBtn)
    FunData.glowstickMobileBtn.MouseButton1Click:Connect(function() shootGlowstick() end)

    FunData.mobileTapConn = G.Services.UserInputService.InputBegan:Connect(function(input, gameProcessed)
        if gameProcessed or not states.glowstickEnabled or not states.glowstickTapShoot then return end
        if input.UserInputType == Enum.UserInputType.Touch or input.UserInputType == Enum.UserInputType.MouseButton1 then
            local cam = G.Services.Workspace.CurrentCamera or Camera
            local unitRay = cam:ViewportPointToRay(input.Position.X, input.Position.Y)
            local rayParams = RaycastParams.new()
            rayParams.FilterType = Enum.RaycastFilterType.Exclude
            rayParams.FilterDescendantsInstances = {player.Character}
            local result = G.Services.Workspace:Raycast(unitRay.Origin, unitRay.Direction * 400, rayParams)
            shootGlowstick(result and result.Position or (unitRay.Origin + unitRay.Direction * 150))
        end
    end)
    FunData.connections[#FunData.connections + 1] = FunData.mobileTapConn

    -- ========================================================
    -- СВЯТАЯ ГРАНАТА (HOLY GRENADE)
    -- ========================================================
    local function assembleHolyGrenadePart(parent)
        local handle = Instance.new("Part")
        handle.Name = "Handle"
        handle.Size = G.Math.v3(1.2, 1.2, 1.2)
        handle.Shape = Enum.PartType.Ball
        handle.Color = G.Math.rgb(245, 245, 245)
        handle.Material = Enum.Material.SmoothPlastic
        handle.Parent = parent

        local gold = G.Math.rgb(235, 180, 0)
        local function addBand(cfMod)
            local band = Instance.new("Part")
            band.Size = G.Math.v3(1.22, 0.14, 1.22)
            band.Color = gold
            band.Material = Enum.Material.SmoothPlastic
            band.CanCollide = false
            band.Massless = true
            Instance.new("CylinderMesh", band)
            band.CFrame = cfMod
            band.Parent = parent
            Instance.new("WeldConstraint", band).Part0 = handle
            band.WeldConstraint.Part1 = band
        end
        addBand(handle.CFrame)
        addBand(handle.CFrame * CFrame.Angles(G.Math.rad(90), 0, 0))
        addBand(handle.CFrame * CFrame.Angles(0, 0, G.Math.rad(90)))

        local function addAcc(sz, pMod, isCyl)
            local p = Instance.new("Part")
            p.Size = sz
            p.Color = gold
            p.Material = Enum.Material.SmoothPlastic
            p.CanCollide = false
            p.Massless = true
            if isCyl then Instance.new("CylinderMesh", p) end
            p.CFrame = handle.CFrame * pMod
            p.Parent = parent
            Instance.new("WeldConstraint", p).Part0 = handle
            p.WeldConstraint.Part1 = p
        end
        addAcc(G.Math.v3(0.45, 0.2, 0.45), G.Math.cf(0, 0.58, 0), true)
        addAcc(G.Math.v3(0.12, 0.45, 0.12), G.Math.cf(0, 0.85, 0), false)
        addAcc(G.Math.v3(0.35, 0.12, 0.12), G.Math.cf(0, 0.95, 0), false)
        return handle
    end

    local function throwHolyGrenadeAssembly(sourceHandle, startCFrame, velocity)
        local model = Instance.new("Model")
        model.Name = "ThrownHolyGrenade"
        local clonedHandle = sourceHandle:Clone()
        for _, child in ipairs(clonedHandle:GetDescendants()) do
            if child:IsA("JointInstance") or child:IsA("WeldConstraint") or child:IsA("TouchTransmitter") then
                child:Destroy()
            end
        end
        clonedHandle.CFrame = startCFrame
        clonedHandle.CanCollide = false
        clonedHandle.Anchored = false
        clonedHandle.Parent = model

        for _, child in ipairs(sourceHandle.Parent:GetChildren()) do
            if child ~= sourceHandle and child:IsA("BasePart") then
                local clonedChild = child:Clone()
                for _, subChild in ipairs(clonedChild:GetDescendants()) do
                    if subChild:IsA("JointInstance") or subChild:IsA("WeldConstraint") or subChild:IsA("TouchTransmitter") then
                        subChild:Destroy()
                    end
                end
                clonedChild.CFrame = startCFrame * sourceHandle.CFrame:ToObjectSpace(child.CFrame)
                clonedChild.CanCollide = false
                clonedChild.Anchored = false
                clonedChild.Parent = model
                local w = Instance.new("WeldConstraint")
                w.Part0 = clonedHandle
                w.Part1 = clonedChild
                w.Parent = clonedHandle
            end
        end
        model.Parent = G.Services.Workspace
        clonedHandle.AssemblyLinearVelocity = velocity
        clonedHandle.AssemblyAngularVelocity = G.Math.v3(math.random(-15, 15), math.random(-15, 15), math.random(-15, 15))

        local char = player.Character
        task.spawn(function()
            while clonedHandle and clonedHandle.Parent do
                if char and (clonedHandle.Position - char:GetPivot().Position).Magnitude > 6 then
                    for _, p in ipairs(model:GetChildren()) do
                        if p:IsA("BasePart") then p.CanCollide = true end
                    end
                    break
                end
                task.wait(0.05)
            end
        end)
        return clonedHandle, model
    end

    local function giveHolyGrenade()
        local bp = player:WaitForChild("Backpack", 5) or player:FindFirstChildOfClass("Backpack")
        if not bp or bp:FindFirstChild("Holy Grenade") or (player.Character and player.Character:FindFirstChild("Holy Grenade")) then return end
        local tool = Instance.new("Tool")
        tool.Name = "Holy Grenade"
        tool.RequiresHandle = true
        tool.CanBeDropped = false
        local handle = assembleHolyGrenadePart(tool)

        local highlight = Instance.new("Highlight", handle)
        highlight.FillColor = G.Math.rgb(255, 245, 180)
        highlight.OutlineColor = G.Math.rgb(235, 180, 0)
        highlight.FillTransparency = 0.5
        highlight.OutlineTransparency = 0.2
        Instance.new("Sparkles", Instance.new("Attachment", handle)).SparkleColor = G.Math.rgb(255, 255, 200)

        tool.Activated:Connect(function()
            local char = player.Character
            local ws = G.Services.Workspace
            local cam = ws.CurrentCamera or Camera
            if not char then return end

            local tSnd = Instance.new("Sound", cam)
            tSnd.SoundId = "rbxassetid://5797621927"
            tSnd.Pitch = 1.4
            tSnd.Volume = 2.5
            tSnd:Play()
            G.Services.Debris:AddItem(tSnd, 3.5)

            local lookDir = cam.CFrame.LookVector
            local throwDir = G.Math.v3(lookDir.X, math.max(lookDir.Y, -0.4), lookDir.Z).Unit
            local startPos = cam.CFrame.Position + throwDir * 4.5
            local velocity = throwDir * 65 + G.Math.v3(0, 15, 0)

            local proj, modelContainer = throwHolyGrenadeAssembly(handle, G.Math.cf(startPos, startPos + throwDir), velocity)
            for _, limb in ipairs(char:GetDescendants()) do
                if limb:IsA("BasePart") then
                    local noCol = Instance.new("NoCollisionConstraint", proj)
                    noCol.Part0 = proj
                    noCol.Part1 = limb
                end
            end

            task.delay(1.5, function()
                if not proj or not proj.Parent then return end
                local center = proj.Position
                local snd = Instance.new("Sound", proj)
                snd.SoundId = "rbxassetid://6734393210"
                snd.Volume = 3
                snd.PlayOnRemove = true
                snd:Play()

                local exp = Instance.new("Explosion", ws)
                exp.Position = center
                exp.BlastRadius = 0
                exp.BlastPressure = 0

                local flash = Instance.new("Part", ws)
                flash.Shape = Enum.PartType.Ball
                flash.Size = G.Math.v3(1, 1, 1)
                flash.Color = G.Math.rgb(255, 240, 180)
                flash.Material = Enum.Material.Neon
                flash.CanCollide = false
                flash.Anchored = true
                flash.Position = center

                task.spawn(function()
                    for i = 1, 12 do
                        flash.Size = G.Math.v3(i * 3.5, i * 3.5, i * 3.5)
                        flash.Transparency = i / 12
                        task.wait(0.015)
                    end
                    flash:Destroy()
                end)

                local overlap = OverlapParams.new()
                overlap.FilterType = Enum.RaycastFilterType.Exclude
                overlap.FilterDescendantsInstances = {char}
                local nearbyParts = ws:GetPartBoundsInRadius(center, 45, overlap)

                for _, obj in ipairs(nearbyParts) do
                    local n = obj.Name:lower()
                    local isStructural = obj:FindFirstAncestor("Parts") or n:find("wall") or n:find("floor") or n:find("ceiling") or n:find("door") or n:find("hinge") or n:find("collision") or n:find("part")
                    if not isStructural then
                        local dist = (obj.Position - center).Magnitude
                        if dist <= 45 then
                            pcall(function()
                                obj.Anchored = false
                                local dir = (obj.Position - center).Unit
                                local pushStrength = (1 - (dist / 45)) * 90
                                obj.AssemblyLinearVelocity = (dir * pushStrength) + G.Math.v3(0, pushStrength * 0.4, 0)
                                obj.AssemblyAngularVelocity = G.Math.v3(math.random(-25, 25), math.random(-25, 25), math.random(-25, 25))
                            end)
                        end
                    end
                end

                if modelContainer then modelContainer:Destroy() end
            end)
        end)
        tool.Parent = bp
    end

    local function removeHolyGrenade()
        local bp = player:FindFirstChildOfClass("Backpack")
        if bp and bp:FindFirstChild("Holy Grenade") then bp["Holy Grenade"]:Destroy() end
        if player.Character and player.Character:FindFirstChild("Holy Grenade") then player.Character["Holy Grenade"]:Destroy() end
    end

    -- ========================================================
    -- МУСОРНАЯ КОРЗИНА (TRASH BASKET)
    -- ========================================================
    local function assembleTrashCan(parent)
        local handle = Instance.new("Part")
        handle.Name = "Handle"
        handle.Size = G.Math.v3(1.4, 2.2, 1.4)
        handle.Color = G.Math.rgb(75, 75, 80)
        handle.Material = Enum.Material.Metal
        handle.Parent = parent
        Instance.new("CylinderMesh", handle)
        return handle
    end

    local function giveTrashBasket()
        local bp = player:WaitForChild("Backpack", 5) or player:FindFirstChildOfClass("Backpack")
        if not bp or bp:FindFirstChild("Trash Basket") or (player.Character and player.Character:FindFirstChild("Trash Basket")) then return end
        local tool = Instance.new("Tool")
        tool.Name = "Trash Basket"
        tool.RequiresHandle = true
        tool.CanBeDropped = false
        local handle = assembleTrashCan(tool)

        local highlight = Instance.new("Highlight", handle)
        highlight.FillColor = G.Math.rgb(150, 150, 155)
        highlight.OutlineColor = G.Math.rgb(100, 100, 105)
        highlight.FillTransparency = 0.6
        highlight.OutlineTransparency = 0.2

        local mouse = player:GetMouse()
        tool.Activated:Connect(function()
            local target = mouse.Target
            local ws = G.Services.Workspace
            local cam = ws.CurrentCamera or Camera
            if target and not target:IsDescendantOf(player.Character) and target ~= cam then
                local model = target:FindFirstAncestorOfClass("Model")
                local toDel = (model and model ~= ws and not model:IsA("Workspace")) and model or target
                if toDel ~= ws and not toDel:IsA("Terrain") then
                    local n = toDel.Name:lower()
                    local isProt = toDel.Parent == ws:FindFirstChild("CurrentRooms") or toDel == ws:FindFirstChild("CurrentRooms") or n:find("currentrooms") or n:find("parts") or n:find("wall") or n:find("floor") or n:find("ceiling") or n:find("room") or n:find("entrance") or n:find("exit")
                    if not isProt then toDel:Destroy() end
                end
            end
        end)
        tool.Parent = bp
    end

    local function removeTrashBasket()
        local bp = player:FindFirstChildOfClass("Backpack")
        if bp and bp:FindFirstChild("Trash Basket") then bp["Trash Basket"]:Destroy() end
        if player.Character and player.Character:FindFirstChild("Trash Basket") then player.Character["Trash Basket"]:Destroy() end
    end
    -- ==============================================================================
    -- СИСТЕМА ВЫДАЧИ БЕСКОНЕЧНОГО ЛУННОГО КОКТЕЙЛЯ (INFINITE MOONLIGHT FLOAT)
    -- ==============================================================================
    local function giveInfiniteRiftSmoothie()
        local bp = player:WaitForChild("Backpack", 5) or player:FindFirstChildOfClass("Backpack")
        local char = player.Character

        if (bp and bp:FindFirstChild("RiftSmoothie")) or (char and char:FindFirstChild("RiftSmoothie")) then
            showNotification(getText("msgItemGiven") or "Already in inventory!", "Warning")
            return
        end

        local pGui = player:WaitForChild("PlayerGui", 5)
        local mainUI = pGui and pGui:FindFirstChild("MainUI")
        local initiator = mainUI and mainUI:FindFirstChild("Initiator")
        local mainGameModule = initiator and initiator:FindFirstChild("Main_Game")
        local Main_Game = mainGameModule and require(mainGameModule)

        local remoteListener = mainGameModule and mainGameModule:FindFirstChild("RemoteListener")
        local rlModules = remoteListener and remoteListener:FindFirstChild("Modules")
        local ToolAnimate = rlModules and rlModules:FindFirstChild("ToolAnimate") and require(rlModules:FindFirstChild("ToolAnimate"))
        local StupidEffects = rlModules and rlModules:FindFirstChild("StupidEffects") and require(rlModules:FindFirstChild("StupidEffects"))

        local function makeArchivable(instance)
            if not instance then return end
            instance.Archivable = true
            for _, child in ipairs(instance:GetDescendants()) do
                child.Archivable = true
            end
        end

        local function getPureSmoothieModel()
            local cleanTemp = G.Services.ReplicatedStorage:FindFirstChild("CleanToolTemp")
            if cleanTemp then
                local found = cleanTemp:FindFirstChild("RiftSmoothie") or cleanTemp:FindFirstChild("Smoothie")
                if found and found:IsA("Tool") then
                    makeArchivable(found)
                    return found:Clone()
                end
            end

            local rf = G.Services.ReplicatedStorage:FindFirstChild("RemotesFolder")
            local getClean = rf and rf:FindFirstChild("GetCleanTool")
            if getClean and getClean:IsA("RemoteFunction") then
                local ok, res = pcall(function() return getClean:InvokeServer("RiftSmoothie") end)
                if ok and res and res:IsA("Tool") then
                    makeArchivable(res)
                    return res:Clone()
                end
            end

            local inRep = G.Services.ReplicatedStorage:FindFirstChild("RiftSmoothie", true) or G.Services.ReplicatedStorage:FindFirstChild("Smoothie", true)
            if inRep and inRep:IsA("Tool") then
                makeArchivable(inRep)
                return inRep:Clone()
            end
            return nil
        end

        local tool = getPureSmoothieModel()
        if not tool then
            showNotification("RiftSmoothie model not found in game!", "Error")
            return
        end

        tool.Name = "RiftSmoothie"
        tool.CanBeDropped = false

        local currentInspectTrack = nil
        local currentVmInspectTrack = nil
        local isInspecting = false
        local isDrinking = false

        local function stopInspect()
            if currentInspectTrack then
                pcall(function() currentInspectTrack:Stop(0.1) end)
                currentInspectTrack = nil
            end
            if currentVmInspectTrack then
                pcall(function() currentVmInspectTrack:Stop(0.1) end)
                currentVmInspectTrack = nil
            end
            isInspecting = false
        end

        local function playDrinkAnimation(c)
            local animFolder = tool:FindFirstChild("Animations")
            local openAnim = animFolder and animFolder:FindFirstChild("open")

            if ToolAnimate and Main_Game then
                pcall(function() ToolAnimate(Main_Game, tool, "open") end)
            end

            local hum = c:FindFirstChildOfClass("Humanoid")
            local charAnimator = hum and hum:FindFirstChildOfClass("Animator")
            if charAnimator and openAnim then
                pcall(function()
                    local track = charAnimator:LoadAnimation(openAnim)
                    track.Priority = Enum.AnimationPriority.Action4
                    track:Play(0.05, 1, 1)
                end)
            end

            local cam = G.Services.Workspace.CurrentCamera or Camera
            local viewmodels = {
                cam and cam:FindFirstChild("BaseRig"),
                cam and cam:FindFirstChild("ViewModel"),
                Main_Game and Main_Game.ViewModel
            }

            for _, vm in ipairs(viewmodels) do
                if vm then
                    local animController = vm:FindFirstChildOfClass("AnimationController") or vm:FindFirstChildOfClass("Humanoid")
                    local vmAnimator = animController and animController:FindFirstChildOfClass("Animator")
                    if vmAnimator and openAnim then
                        pcall(function()
                            local vmTrack = vmAnimator:LoadAnimation(openAnim)
                            vmTrack.Priority = Enum.AnimationPriority.Action4
                            vmTrack:Play(0.05, 1, 1)
                        end)
                        break
                    end
                end
            end
        end

        local function inspect()
            if isDrinking then return end
            local curChar = player.Character
            if not curChar or tool.Parent ~= curChar then return end

            local hum = curChar:FindFirstChildOfClass("Humanoid")
            if not hum or hum.Health <= 0 then return end

            if isInspecting then
                stopInspect()
                return
            end

            isInspecting = true
            local animFolder = tool:FindFirstChild("Animations")
            local inspectAnim = animFolder and animFolder:FindFirstChild("inspect")

            if ToolAnimate and Main_Game then
                pcall(function() ToolAnimate(Main_Game, tool, "inspect") end)
            end

            local charAnimator = hum:FindFirstChildOfClass("Animator")
            if charAnimator and inspectAnim then
                pcall(function()
                    currentInspectTrack = charAnimator:LoadAnimation(inspectAnim)
                    currentInspectTrack.Priority = Enum.AnimationPriority.Action3
                    currentInspectTrack:Play(0.1, 1, 1)
                end)
            end

            local cam = G.Services.Workspace.CurrentCamera or Camera
            local viewmodels = {
                cam and cam:FindFirstChild("BaseRig"),
                cam and cam:FindFirstChild("ViewModel"),
                Main_Game and Main_Game.ViewModel
            }

            for _, vm in ipairs(viewmodels) do
                if vm then
                    local animController = vm:FindFirstChildOfClass("AnimationController") or vm:FindFirstChildOfClass("Humanoid")
                    local vmAnimator = animController and animController:FindFirstChildOfClass("Animator")
                    if vmAnimator and inspectAnim then
                        pcall(function()
                            currentVmInspectTrack = vmAnimator:LoadAnimation(inspectAnim)
                            currentVmInspectTrack.Priority = Enum.AnimationPriority.Action3
                            currentVmInspectTrack:Play(0.1, 1, 1)
                        end)
                        break
                    end
                end
            end

            if currentInspectTrack then
                currentInspectTrack.Stopped:Once(function() isInspecting = false end)
            else
                task.delay(2.5, function() if isInspecting then isInspecting = false end end)
            end
        end

        local function drink()
            if isDrinking then return end
            local curChar = player.Character
            if not curChar or tool.Parent ~= curChar then return end

            local hum = curChar:FindFirstChildOfClass("Humanoid")
            if not hum or hum.Health <= 0 then return end

            stopInspect()
            isDrinking = true

            local handle = tool:FindFirstChild("Handle")
            local sound = handle and handle:FindFirstChild("sound_drink")
            if sound then sound:Play() end

            playDrinkAnimation(curChar)

            task.wait(0.5)

            if StupidEffects and Main_Game then
                pcall(function() StupidEffects(Main_Game, "Guidance") end)
            end

            local liquid = tool:FindFirstChild("Liquid", true)
            if liquid and liquid:IsA("BasePart") then
                liquid.Transparency = 0
            end

            task.wait(1.5)
            isDrinking = false
        end

        local ACTION_DRINK = "SmoothieDrinkAction_" .. tostring(tick())
        local ACTION_INSPECT = "SmoothieInspectAction_" .. tostring(tick())

        local function handleDrinkAction(_, inputState)
            if inputState == Enum.UserInputState.Begin then
                local curChar = player.Character
                if curChar and tool.Parent == curChar then
                    drink()
                    return Enum.ContextActionResult.Sink
                end
            end
            return Enum.ContextActionResult.Pass
        end

        local function handleInspectAction(_, inputState)
            if inputState == Enum.UserInputState.Begin then
                local curChar = player.Character
                if curChar and tool.Parent == curChar then
                    inspect()
                    return Enum.ContextActionResult.Sink
                end
            end
            return Enum.ContextActionResult.Pass
        end

        local uisConn = G.Services.UserInputService.InputBegan:Connect(function(input, gp)
            if gp or G.Services.UserInputService:GetFocusedTextBox() then return end
            local curChar = player.Character
            if not curChar or tool.Parent ~= curChar then return end

            local it = input.UserInputType
            if it == Enum.UserInputType.MouseButton1 or it == Enum.UserInputType.Touch or it == Enum.UserInputType.ButtonR2 then
                drink()
            elseif it == Enum.UserInputType.MouseButton2 or it == Enum.UserInputType.ButtonL2 then
                inspect()
            end
        end)
        FunData.connections[#FunData.connections + 1] = uisConn

        local function hookMobileButton()
            local mainFrame = mainUI and mainUI:FindFirstChild("MainFrame")
            local mobileButtons = mainFrame and mainFrame:FindFirstChild("MobileButtons")
            local toolBtn = mobileButtons and mobileButtons:FindFirstChild("ToolButton")
            if toolBtn and toolBtn:IsA("GuiButton") then
                toolBtn.MouseButton1Down:Connect(function()
                    local curChar = player.Character
                    if curChar and tool.Parent == curChar then
                        drink()
                    end
                end)
            end
        end
        task.spawn(hookMobileButton)

        tool.Activated:Connect(drink)

        tool.Equipped:Connect(function()
            G.Services.ContextActionService:BindActionAtPriority(
                ACTION_DRINK,
                handleDrinkAction,
                false,
                Enum.ContextActionPriority.High.Value + 1000,
                Enum.UserInputType.MouseButton1,
                Enum.UserInputType.Touch
            )
            G.Services.ContextActionService:BindActionAtPriority(
                ACTION_INSPECT,
                handleInspectAction,
                isTouchDevice,
                Enum.ContextActionPriority.High.Value + 1000,
                Enum.UserInputType.MouseButton2
            )
            if isTouchDevice then
                G.Services.ContextActionService:SetTitle(ACTION_INSPECT, (states.language == "Russian") and "Осмотр" or "Inspect")
                G.Services.ContextActionService:SetPosition(ACTION_INSPECT, UDim2.new(1, -140, 1, -150))
            end
        end)

        tool.Unequipped:Connect(function()
            stopInspect()
            G.Services.ContextActionService:UnbindAction(ACTION_DRINK)
            G.Services.ContextActionService:UnbindAction(ACTION_INSPECT)
        end)

        tool.Parent = bp or char
        showNotification(getText("msgItemGiven") or "Moonlight Float received!", "Success")
    end

    -- ==============================================================================
    -- СИСТЕМА ВЫДАЧИ БЕСКОНЕЧНОЙ БУТЫЛКИ ЗВЁЗДНОГО СВЕТА (INFINITE STARLIGHT BOTTLE)
    -- ==============================================================================
    local activeStarBottleSessionId = 0

    local function giveInfiniteStarBottle()
        local bp = player:WaitForChild("Backpack", 5) or player:FindFirstChildOfClass("Backpack")
        local char = player.Character

        if (bp and bp:FindFirstChild("StarBottle")) or (char and char:FindFirstChild("StarBottle")) then
            showNotification(getText("msgItemGiven") or "Already in inventory!", "Warning")
            return
        end

        local pGui = player:WaitForChild("PlayerGui", 5)
        local mainUI = pGui and pGui:FindFirstChild("MainUI")
        local initiator = mainUI and mainUI:FindFirstChild("Initiator")
        local mainGameModule = initiator and initiator:FindFirstChild("Main_Game")
        local Main_Game = mainGameModule and require(mainGameModule)

        local remoteListener = mainGameModule and mainGameModule:FindFirstChild("RemoteListener")
        local rlModules = remoteListener and remoteListener:FindFirstChild("Modules")
        local ToolAnimate = rlModules and rlModules:FindFirstChild("ToolAnimate") and require(rlModules:FindFirstChild("ToolAnimate"))

        local healthScript = mainGameModule and mainGameModule:FindFirstChild("Health")
        local effectModules = healthScript and healthScript:FindFirstChild("EffectModules")
        local starlightMediumModule = effectModules and effectModules:FindFirstChild("StarlightMedium")

        local function makeArchivable(instance)
            if not instance then return end
            instance.Archivable = true
            for _, child in ipairs(instance:GetDescendants()) do
                child.Archivable = true
            end
        end

        local function cleanSkinsFromTool(toolInstance)
            if not toolInstance then return end
            toolInstance:SetAttribute("ToolSkin", nil)
            toolInstance:SetAttribute("Skin", nil)
            toolInstance:SetAttribute("ToolColor", nil)

            for _, desc in ipairs(toolInstance:GetDescendants()) do
                if desc:IsA("SurfaceAppearance") then
                    desc:Destroy()
                elseif desc:IsA("Decal") and (string.find(string.lower(desc.Name), "skin") or string.find(string.lower(desc.Name), "sticky")) then
                    desc:Destroy()
                elseif desc:IsA("BasePart") and desc.Name ~= "Handle" then
                    if string.find(string.lower(desc.Name), "sticky") or string.find(string.lower(desc.Name), "skin") then
                        desc:Destroy()
                    end
                end
            end

            local handle = toolInstance:FindFirstChild("Handle")
            if handle then
                local attach = handle:FindFirstChild("Attachment")
                if attach then
                    for _, particle in ipairs(attach:GetChildren()) do
                        if particle:IsA("ParticleEmitter") or particle:IsA("PointLight") then
                            particle.Enabled = true
                        end
                    end
                end
            end
        end

        local function getPureStarBottleModel()
            local cleanTemp = G.Services.ReplicatedStorage:FindFirstChild("CleanToolTemp")
            if cleanTemp then
                local found = cleanTemp:FindFirstChild("StarBottle")
                if found and found:IsA("Tool") then
                    makeArchivable(found)
                    local cloned = found:Clone()
                    cleanSkinsFromTool(cloned)
                    return cloned
                end
            end

            local rf = G.Services.ReplicatedStorage:FindFirstChild("RemotesFolder")
            local getClean = rf and rf:FindFirstChild("GetCleanTool")
            if getClean and getClean:IsA("RemoteFunction") then
                local ok, res = pcall(function() return getClean:InvokeServer("StarBottle") end)
                if ok and res and res:IsA("Tool") then
                    makeArchivable(res)
                    local cloned = res:Clone()
                    cleanSkinsFromTool(cloned)
                    return cloned
                end
            end

            local inRep = G.Services.ReplicatedStorage:FindFirstChild("StarBottle", true)
            if inRep and inRep:IsA("Tool") then
                makeArchivable(inRep)
                local cloned = inRep:Clone()
                cleanSkinsFromTool(cloned)
                return cloned
            end
            return nil
        end

        local tool = getPureStarBottleModel()
        if not tool then
            showNotification("StarBottle model not found in game!", "Error")
            return
        end

        tool.Name = "StarBottle"
        tool.CanBeDropped = false

        local animFolder = tool:FindFirstChild("Animations")
        if not animFolder then
            animFolder = Instance.new("Folder")
            animFolder.Name = "Animations"
            animFolder.Parent = tool
        end

        local function ensureAnim(name, id)
            local anim = animFolder:FindFirstChild(name)
            if not anim then
                anim = Instance.new("Animation")
                anim.Name = name
                anim.AnimationId = id
                anim.Parent = animFolder
            end
            return anim
        end
        ensureAnim("open", "rbxassetid://10482563149")
        ensureAnim("idle", "rbxassetid://10479585177")
        ensureAnim("inspect", "rbxassetid://137555102643743")

        local currentInspectTrack = nil
        local currentVmInspectTrack = nil
        local isInspecting = false
        local isDrinking = false

        local function stopInspect()
            if currentInspectTrack then
                pcall(function() currentInspectTrack:Stop(0.1) end)
                currentInspectTrack = nil
            end
            if currentVmInspectTrack then
                pcall(function() currentVmInspectTrack:Stop(0.1) end)
                currentVmInspectTrack = nil
            end
            isInspecting = false
        end

        local function playDrinkAnimation(c)
            local openAnim = animFolder:FindFirstChild("open")
            if ToolAnimate and Main_Game then
                pcall(function() ToolAnimate(Main_Game, tool, "open") end)
            end

            local hum = c:FindFirstChildOfClass("Humanoid")
            local charAnimator = hum and hum:FindFirstChildOfClass("Animator")
            if charAnimator and openAnim then
                pcall(function()
                    local track = charAnimator:LoadAnimation(openAnim)
                    track.Priority = Enum.AnimationPriority.Action4
                    track:Play(0.05, 1, 1)
                end)
            end

            local cam = G.Services.Workspace.CurrentCamera or Camera
            local viewmodels = {
                cam and cam:FindFirstChild("BaseRig"),
                cam and cam:FindFirstChild("ViewModel"),
                Main_Game and Main_Game.ViewModel
            }

            for _, vm in ipairs(viewmodels) do
                if vm then
                    local animController = vm:FindFirstChildOfClass("AnimationController") or vm:FindFirstChildOfClass("Humanoid")
                    local vmAnimator = animController and animController:FindFirstChildOfClass("Animator")
                    if vmAnimator and openAnim then
                        pcall(function()
                            local vmTrack = vmAnimator:LoadAnimation(openAnim)
                            vmTrack.Priority = Enum.AnimationPriority.Action4
                            vmTrack:Play(0.05, 1, 1)
                        end)
                        break
                    end
                end
            end
        end

        local function inspect()
            if isDrinking then return end
            local curChar = player.Character
            if not curChar or tool.Parent ~= curChar then return end

            local hum = curChar:FindFirstChildOfClass("Humanoid")
            if not hum or hum.Health <= 0 then return end

            if isInspecting then
                stopInspect()
                return
            end

            isInspecting = true
            local inspectAnim = animFolder:FindFirstChild("inspect")

            if ToolAnimate and Main_Game then
                pcall(function() ToolAnimate(Main_Game, tool, "inspect") end)
            end

            local charAnimator = hum:FindFirstChildOfClass("Animator")
            if charAnimator and inspectAnim then
                pcall(function()
                    currentInspectTrack = charAnimator:LoadAnimation(inspectAnim)
                    currentInspectTrack.Priority = Enum.AnimationPriority.Action3
                    currentInspectTrack:Play(0.1, 1, 1)
                end)
            end

            local cam = G.Services.Workspace.CurrentCamera or Camera
            local viewmodels = {
                cam and cam:FindFirstChild("BaseRig"),
                cam and cam:FindFirstChild("ViewModel"),
                Main_Game and Main_Game.ViewModel
            }

            for _, vm in ipairs(viewmodels) do
                if vm then
                    local animController = vm:FindFirstChildOfClass("AnimationController") or vm:FindFirstChildOfClass("Humanoid")
                    local vmAnimator = animController and animController:FindFirstChildOfClass("Animator")
                    if vmAnimator and inspectAnim then
                        pcall(function()
                            currentVmInspectTrack = vmAnimator:LoadAnimation(inspectAnim)
                            currentVmInspectTrack.Priority = Enum.AnimationPriority.Action3
                            currentVmInspectTrack:Play(0.1, 1, 1)
                        end)
                        break
                    end
                end
            end

            if currentInspectTrack then
                currentInspectTrack.Stopped:Once(function() isInspecting = false end)
            else
                task.delay(2.5, function() if isInspecting then isInspecting = false end end)
            end
        end

        local function applyPlayerGlowAndSpeedDecay(c)
            local root = c:FindFirstChild("HumanoidRootPart") or c:FindFirstChild("UpperTorso")
            local hum = c:FindFirstChildOfClass("Humanoid")
            if not root then return end

            local DURATION = 12.0
            local PEAK_SPEED = 6.0
            local PEAK_LIGHT_BRIGHTNESS = 2.6
            local PEAK_LIGHT_RANGE = 26.0

            activeStarBottleSessionId = activeStarBottleSessionId + 1
            local currentSession = activeStarBottleSessionId

            local glow = root:FindFirstChild("StarlightGlow")
            if not glow then
                glow = Instance.new("PointLight")
                glow.Name = "StarlightGlow"
                glow.Color = Color3.fromRGB(255, 215, 75)
                glow.Shadows = false
                glow.Parent = root
            end

            glow.Brightness = PEAK_LIGHT_BRIGHTNESS
            glow.Range = PEAK_LIGHT_RANGE
            glow.Enabled = true

            local mainFrame = mainUI and mainUI:FindFirstChild("MainFrame")
            local healthbar = mainFrame and mainFrame:FindFirstChild("Healthbar")
            local effectsFrame = healthbar and healthbar:FindFirstChild("Effects")
            local starlightIcon = effectsFrame and effectsFrame:FindFirstChild("StarlightMedium")

            if starlightIcon then
                starlightIcon.Visible = true
                starlightIcon.ImageTransparency = 0
            end

            c:SetAttribute("SpeedBoost", PEAK_SPEED)
            if hum then hum.WalkSpeed = 15 + PEAK_SPEED end

            task.spawn(function()
                local startTime = os.clock()
                while os.clock() - startTime < DURATION do
                    if activeStarBottleSessionId ~= currentSession then return end

                    local elapsed = os.clock() - startTime
                    local factor = math.clamp(1 - (elapsed / DURATION), 0, 1)

                    if glow and glow.Parent then
                        glow.Brightness = PEAK_LIGHT_BRIGHTNESS * factor
                        glow.Range = PEAK_LIGHT_RANGE * factor
                        glow.Enabled = factor > 0.02
                    end

                    local currentBoost = PEAK_SPEED * factor
                    c:SetAttribute("SpeedBoost", currentBoost)
                    if hum and hum.Parent then
                        hum.WalkSpeed = 15 + currentBoost
                    end

                    if starlightIcon and starlightIcon.Parent then
                        starlightIcon.Visible = true
                        starlightIcon.ImageTransparency = (1 - factor) * 0.4
                    end

                    task.wait(0.03)
                end

                if activeStarBottleSessionId == currentSession then
                    if glow and glow.Parent then
                        glow.Brightness = 0
                        glow.Range = 0
                        glow.Enabled = false
                    end
                    c:SetAttribute("SpeedBoost", 0)
                    if hum and hum.Parent then hum.WalkSpeed = 15 end
                    if starlightIcon and starlightIcon.Parent then starlightIcon.Visible = false end
                end
            end)
        end

        local function applyStarlightScreenFX()
            task.spawn(function()
                local executedNative = false
                if starlightMediumModule then
                    local ok = pcall(function()
                        local fn = require(starlightMediumModule)
                        if type(fn) == "function" then
                            fn(Main_Game)
                            executedNative = true
                        end
                    end)
                    if ok and executedNative then return end
                end

                local mainFrame = mainUI and mainUI:FindFirstChild("MainFrame")
                local whiteVignette = mainFrame and mainFrame:FindFirstChild("WhiteVignette")
                local cam = G.Services.Workspace.CurrentCamera or Camera

                local cc = Instance.new("ColorCorrectionEffect")
                cc.Name = "StarlightCC_Live"
                cc.Brightness = 0.22
                cc.Saturation = 0.35
                cc.TintColor = Color3.fromRGB(255, 230, 160)
                cc.Parent = cam

                G.Services.TweenService:Create(cc, TweenInfo.new(10, Enum.EasingStyle.Quart, Enum.EasingDirection.In), {
                    Brightness = 0,
                    Saturation = 0,
                    Contrast = 0,
                    TintColor = Color3.new(1, 1, 1)
                }):Play()

                if whiteVignette then
                    local liveVignette = whiteVignette:Clone()
                    liveVignette.Name = "WhiteVignetteLive"
                    liveVignette.ImageColor3 = Color3.fromRGB(255, 215, 71)
                    liveVignette.ImageTransparency = 0.1
                    liveVignette.Size = UDim2.new(1, 0, 1, 0)
                    liveVignette.Parent = mainFrame
                    liveVignette.Visible = true

                    G.Services.TweenService:Create(liveVignette, TweenInfo.new(10, Enum.EasingStyle.Exponential, Enum.EasingDirection.Out), {
                        Size = UDim2.new(1.5, 0, 1.5, 0)
                    }):Play()

                    G.Services.TweenService:Create(liveVignette, TweenInfo.new(10, Enum.EasingStyle.Quart, Enum.EasingDirection.In), {
                        ImageTransparency = 1,
                        ImageColor3 = Color3.fromRGB(255, 149, 79)
                    }):Play()

                    task.wait(10.1)
                    pcall(function() liveVignette:Destroy() end)
                    pcall(function() cc:Destroy() end)
                else
                    task.wait(10.1)
                    pcall(function() cc:Destroy() end)
                end
            end)
        end

        local function drink()
            if isDrinking then return end
            local curChar = player.Character
            if not curChar or tool.Parent ~= curChar then return end

            local hum = curChar:FindFirstChildOfClass("Humanoid")
            if not hum or hum.Health <= 0 then return end

            stopInspect()
            isDrinking = true

            local handle = tool:FindFirstChild("Handle")
            local sound = handle and handle:FindFirstChild("sound_drink")
            if sound then sound:Play() end

            playDrinkAnimation(curChar)

            task.wait(0.5)

            task.spawn(applyStarlightScreenFX)
            task.spawn(applyPlayerGlowAndSpeedDecay, curChar)

            task.wait(1.0)
            isDrinking = false
        end

        local ACTION_DRINK = "StarBottleDrinkAction_" .. tostring(tick())
        local ACTION_INSPECT = "StarBottleInspectAction_" .. tostring(tick())

        local function handleDrinkAction(_, inputState)
            if inputState == Enum.UserInputState.Begin then
                local curChar = player.Character
                if curChar and tool.Parent == curChar then
                    drink()
                    return Enum.ContextActionResult.Sink
                end
            end
            return Enum.ContextActionResult.Pass
        end

        local function handleInspectAction(_, inputState)
            if inputState == Enum.UserInputState.Begin then
                local curChar = player.Character
                if curChar and tool.Parent == curChar then
                    inspect()
                    return Enum.ContextActionResult.Sink
                end
            end
            return Enum.ContextActionResult.Pass
        end

        local uisConn = G.Services.UserInputService.InputBegan:Connect(function(input, gp)
            if gp or G.Services.UserInputService:GetFocusedTextBox() then return end
            local curChar = player.Character
            if not curChar or tool.Parent ~= curChar then return end

            local it = input.UserInputType
            if it == Enum.UserInputType.MouseButton1 or it == Enum.UserInputType.Touch or it == Enum.UserInputType.ButtonR2 then
                drink()
            elseif it == Enum.UserInputType.MouseButton2 or it == Enum.UserInputType.ButtonL2 then
                inspect()
            end
        end)
        FunData.connections[#FunData.connections + 1] = uisConn

        local function hookMobileButton()
            local mainFrame = mainUI and mainUI:FindFirstChild("MainFrame")
            local mobileButtons = mainFrame and mainFrame:FindFirstChild("MobileButtons")
            local toolBtn = mobileButtons and mobileButtons:FindFirstChild("ToolButton")
            if toolBtn and toolBtn:IsA("GuiButton") then
                toolBtn.MouseButton1Down:Connect(function()
                    local curChar = player.Character
                    if curChar and tool.Parent == curChar then
                        drink()
                    end
                end)
            end
        end
        task.spawn(hookMobileButton)

        tool.Activated:Connect(drink)

        tool.Equipped:Connect(function()
            G.Services.ContextActionService:BindActionAtPriority(
                ACTION_DRINK,
                handleDrinkAction,
                false,
                Enum.ContextActionPriority.High.Value + 1000,
                Enum.UserInputType.MouseButton1,
                Enum.UserInputType.Touch
            )
            G.Services.ContextActionService:BindActionAtPriority(
                ACTION_INSPECT,
                handleInspectAction,
                isTouchDevice,
                Enum.ContextActionPriority.High.Value + 1000,
                Enum.UserInputType.MouseButton2
            )
            if isTouchDevice then
                G.Services.ContextActionService:SetTitle(ACTION_INSPECT, (states.language == "Russian") and "Осмотр" or "Inspect")
                G.Services.ContextActionService:SetPosition(ACTION_INSPECT, UDim2.new(1, -140, 1, -150))
            end
        end)

        tool.Unequipped:Connect(function()
            stopInspect()
            G.Services.ContextActionService:UnbindAction(ACTION_DRINK)
            G.Services.ContextActionService:UnbindAction(ACTION_INSPECT)
        end)

        tool.Parent = bp or char
        showNotification(getText("msgItemGiven") or "Starlight Bottle received!", "Success")
    end
    -- ========================================================
    -- РЕЖИМ МЕТАЛЛИЧЕСКОЙ ТРУБЫ (PIPE MODE)
    -- ========================================================
    local texturePropertyMap = {
        Decal = "Texture", Texture = "Texture", MeshPart = "TextureID",
        SpecialMesh = "TextureId", SurfaceAppearance = "ColorMap",
        ParticleEmitter = "Texture", Trail = "Texture", Beam = "Texture"
    }
    local function isTextureObject(obj) return texturePropertyMap[obj.ClassName] ~= nil end

    local function applyDecalsToPart(part)
        if not part:IsA("BasePart") or part:IsDescendantOf(player.Character) or part.Transparency == 1 or FunData.PipeData.spawnedDecals[part] then return end
        local list = {}
        for _, face in ipairs({Enum.NormalId.Front, Enum.NormalId.Back, Enum.NormalId.Top, Enum.NormalId.Bottom, Enum.NormalId.Left, Enum.NormalId.Right}) do
            local d = Instance.new("Decal")
            d.Name = "PipeDecal"
            d.Texture = "rbxassetid://12794417719"
            d.Face = face
            d.Parent = part
            list[#list + 1] = d
        end
        FunData.PipeData.spawnedDecals[part] = list
    end

    local function processPipeSpawnQueue()
        if FunData.PipeData.processing then return end
        FunData.PipeData.processing = true
        local count = 0
        while #FunData.PipeData.queue > 0 and states.pipeMode do
            local part = table.remove(FunData.PipeData.queue, 1)
            if part and part.Parent then pcall(applyDecalsToPart, part) end
            count = count + 1
            if count % 25 == 0 then task.wait(0.02) end
        end
        FunData.PipeData.processing = false
    end

    local function applyPipeToSound(sound)
        if not sound or not sound.Parent then return end
        if not FunData.PipeData.origSounds[sound] then
            FunData.PipeData.origSounds[sound] = {SoundId = sound.SoundId, Volume = sound.Volume, Looped = sound.Looped}
        end
        if states.pipeMode and states.pipeSoundEnabled then
            if FunData.PipeData.connections[sound] then
                FunData.PipeData.connections[sound]:Disconnect()
                FunData.PipeData.connections[sound] = nil
            end
            sound.SoundId = "rbxassetid://139668725303708"
            sound.Volume = FunData.PipeData.origSounds[sound].Volume * ((states.pipeVolumeMult or 100) / 100)
            sound.Looped = false
            FunData.PipeData.connections[sound] = sound:GetPropertyChangedSignal("SoundId"):Connect(function()
                if states.pipeMode and states.pipeSoundEnabled then
                    FunData.PipeData.origSounds[sound].SoundId = sound.SoundId
                    applyPipeToSound(sound)
                end
            end)
        end
    end

    local function applyPipeToDecal(obj)
        if not obj or not obj.Parent then return end
        local prop = texturePropertyMap[obj.ClassName]
        if not prop then return end
        if not FunData.PipeData.origDecals[obj] then
            FunData.PipeData.origDecals[obj] = {
                Texture = obj[prop],
                StudsU = obj:IsA("Texture") and obj.StudsPerTileU or nil,
                StudsV = obj:IsA("Texture") and obj.StudsPerTileV or nil
            }
        end
        if states.pipeMode then
            if FunData.PipeData.connections[obj] then
                FunData.PipeData.connections[obj]:Disconnect()
                FunData.PipeData.connections[obj] = nil
            end
            pcall(function()
                obj[prop] = "rbxassetid://12794417719"
                if obj:IsA("Texture") then obj.StudsPerTileU = 20; obj.StudsPerTileV = 20 end
            end)
            FunData.PipeData.connections[obj] = obj:GetPropertyChangedSignal(prop):Connect(function()
                if states.pipeMode then
                    FunData.PipeData.origDecals[obj].Texture = obj[prop]
                    applyPipeToDecal(obj)
                end
            end)
        end
    end

    local function restoreSound(sound)
        if FunData.PipeData.connections[sound] then
            FunData.PipeData.connections[sound]:Disconnect()
            FunData.PipeData.connections[sound] = nil
        end
        if FunData.PipeData.origSounds[sound] then
            pcall(function()
                sound.SoundId = FunData.PipeData.origSounds[sound].SoundId
                sound.Volume = FunData.PipeData.origSounds[sound].Volume
                sound.Looped = FunData.PipeData.origSounds[sound].Looped
            end)
            FunData.PipeData.origSounds[sound] = nil
        end
    end

    local function restoreDecal(obj)
        if FunData.PipeData.connections[obj] then
            FunData.PipeData.connections[obj]:Disconnect()
            FunData.PipeData.connections[obj] = nil
        end
        local prop = texturePropertyMap[obj.ClassName]
        if prop and FunData.PipeData.origDecals[obj] then
            pcall(function()
                obj[prop] = FunData.PipeData.origDecals[obj].Texture
                if obj:IsA("Texture") then
                    obj.StudsPerTileU = FunData.PipeData.origDecals[obj].StudsU
                    obj.StudsPerTileV = FunData.PipeData.origDecals[obj].StudsV
                end
            end)
            FunData.PipeData.origDecals[obj] = nil
        end
    end

    local function updateAllPipeVolumes()
        if states.pipeMode and states.pipeSoundEnabled then
            for sound, origData in pairs(FunData.PipeData.origSounds) do
                pcall(function()
                    sound.Volume = origData.Volume * ((states.pipeVolumeMult or 100) / 100)
                end)
            end
        end
    end

    local function togglePipeMode(enabled)
        FunData.PipeData.active = enabled
        local ws = G.Services.Workspace
        if enabled then
            for _, s in ipairs({ws, G.Services.SoundService, G.Services.Players, G.Services.ReplicatedStorage}) do
                for _, desc in ipairs(s:GetDescendants()) do
                    if desc:IsA("Sound") then
                        applyPipeToSound(desc)
                    elseif isTextureObject(desc) then
                        applyPipeToDecal(desc)
                    elseif desc:IsA("BasePart") then
                        FunData.PipeData.queue[#FunData.PipeData.queue + 1] = desc
                    end
                end
            end
            if not FunData.PipeData.processing then task.spawn(processPipeSpawnQueue) end
            if FunData.globalPipeConn then FunData.globalPipeConn:Disconnect() end
            FunData.globalPipeConn = ws.DescendantAdded:Connect(function(desc)
                if not FunData.PipeData.active then return end
                if desc:IsA("Sound") then
                    task.defer(applyPipeToSound, desc)
                elseif isTextureObject(desc) then
                    task.defer(applyPipeToDecal, desc)
                elseif desc:IsA("BasePart") then
                    FunData.PipeData.queue[#FunData.PipeData.queue + 1] = desc
                    if not FunData.PipeData.processing then task.spawn(processPipeSpawnQueue) end
                end
            end)
        else
            if FunData.globalPipeConn then
                FunData.globalPipeConn:Disconnect()
                FunData.globalPipeConn = nil
            end
            table.clear(FunData.PipeData.queue)
            for s in pairs(FunData.PipeData.origSounds) do restoreSound(s) end
            for d in pairs(FunData.PipeData.origDecals) do restoreDecal(d) end
            for _, list in pairs(FunData.PipeData.spawnedDecals) do
                for _, d in ipairs(list) do pcall(function() d:Destroy() end) end
            end
            table.clear(FunData.PipeData.origSounds)
            table.clear(FunData.PipeData.origDecals)
            table.clear(FunData.PipeData.spawnedDecals)
            table.clear(FunData.PipeData.connections)
        end
    end

    -- ========================================================
    -- ARCHIVES CHAIR MANIPULATION (СЕТЕВАЯ СИНХРОНИЗАЦИЯ)
    -- ========================================================
    local TARGET_CHAIR_NAME = "archivesofficechair"
    local MAX_GRAB_DISTANCE = 50

    local function getChairModel(instance)
        local cur = instance
        local ws = G.Services.Workspace
        while cur and cur ~= ws do
            if cur:IsA("Model") then
                local clean = cur.Name:lower():gsub("[%s%_%-]", "")
                if clean:find(TARGET_CHAIR_NAME) then
                    return cur
                end
            end
            cur = cur.Parent
        end
        return nil
    end

    local function getRootPart(model)
        if not model then return nil end
        if model.PrimaryPart then return model.PrimaryPart end
        local seat = model:FindFirstChildWhichIsA("Seat")
        if seat then return seat end
        return model:FindFirstChildWhichIsA("BasePart")
    end

    local function setChairHighlight(model, color)
        if not model then return end
        local hl = model:FindFirstChild("MagicGlow")
        if not hl then
            hl = Instance.new("Highlight")
            hl.Name = "MagicGlow"
            hl.Adornee = model
            hl.Parent = model
        end
        hl.FillColor = color or G.Math.rgb(170, 70, 255)
        hl.OutlineColor = G.Math.rgb(255, 255, 255)
        hl.FillTransparency = 0.35
    end

    local function removeChairHighlight(model)
        if model then
            local hl = model:FindFirstChild("MagicGlow")
            if hl then hl:Destroy() end
        end
    end

    local function disableChairCharacterCollision(model)
        local char = player.Character
        if not char or not model then return end
        for _, charPart in ipairs(char:GetDescendants()) do
            if charPart:IsA("BasePart") then
                for _, chairPart in ipairs(model:GetDescendants()) do
                    if chairPart:IsA("BasePart") then
                        local nc = Instance.new("NoCollisionConstraint")
                        nc.Part0 = charPart
                        nc.Part1 = chairPart
                        nc.Parent = chairPart
                        FunData.ChairData.noCollideList[#FunData.ChairData.noCollideList + 1] = nc
                    end
                end
            end
        end
    end

    local function restoreChairCharacterCollision()
        for _, nc in ipairs(FunData.ChairData.noCollideList) do
            if nc and nc.Parent then pcall(function() nc:Destroy() end) end
        end
        table.clear(FunData.ChairData.noCollideList)
    end

    local function releaseChair(isThrow)
        if not FunData.ChairData.heldChair then return end
        local chair = FunData.ChairData.heldChair
        local root = FunData.ChairData.heldRoot

        FunData.ChairData.heldChair = nil
        FunData.ChairData.heldRoot = nil

        restoreChairCharacterCollision()
        removeChairHighlight(chair)

        if root and root.Parent then
            local cam = G.Services.Workspace.CurrentCamera or Camera
            if isThrow then
                local throwForce = states.chairThrowForce or 145
                root.AssemblyLinearVelocity = (cam.CFrame.LookVector * throwForce) + G.Math.v3(0, 15, 0)
                root.AssemblyAngularVelocity = G.Math.v3(math.random(-10, 10), math.random(-10, 10), math.random(-10, 10))
            else
                root.AssemblyLinearVelocity = G.Math.v3(0, -3, 0)
                root.AssemblyAngularVelocity = G.Math.v3(0, 0, 0)
            end
        end
    end

    local function grabChair(chair)
        releaseChair(false)
        if not chair then return end
        local root = getRootPart(chair)
        if not root then return end

        FunData.ChairData.heldChair = chair
        FunData.ChairData.heldRoot = root

        setChairHighlight(chair, G.Math.rgb(170, 70, 255))
        disableChairCharacterCollision(chair)

        local cam = G.Services.Workspace.CurrentCamera or Camera
        FunData.ChairData.holdDistance = G.Math.clamp((root.Position - cam.CFrame.Position).Magnitude, 7, 22)
        FunData.ChairData.rotYaw = 0
        FunData.ChairData.rotPitch = 0
    end

    local function tryGrabNearestChair()
        local cam = G.Services.Workspace.CurrentCamera or Camera
        local ws = G.Services.Workspace
        local mouse = player:GetMouse()
        local chair = mouse and mouse.Target and getChairModel(mouse.Target)

        if not chair then
            local rayParams = RaycastParams.new()
            rayParams.FilterType = Enum.RaycastFilterType.Exclude
            if player.Character then
                rayParams.FilterDescendantsInstances = {player.Character}
            end
            local ray = ws:Raycast(cam.CFrame.Position, cam.CFrame.LookVector * MAX_GRAB_DISTANCE, rayParams)
            if ray and ray.Instance then
                chair = getChairModel(ray.Instance)
            end
        end

        if not chair and player.Character then
            local charPos = player.Character:GetPivot().Position
            local closestDist = MAX_GRAB_DISTANCE
            for _, desc in ipairs(ws:GetDescendants()) do
                if desc:IsA("Model") then
                    local clean = desc.Name:lower():gsub("[%s%_%-]", "")
                    if clean:find(TARGET_CHAIR_NAME) then
                        local r = getRootPart(desc)
                        if r then
                            local d = (r.Position - charPos).Magnitude
                            if d < closestDist then
                                closestDist = d
                                chair = desc
                            end
                        end
                    end
                end
            end
        end

        if chair then
            local char = player.Character
            local dist = char and (chair:GetPivot().Position - char:GetPivot().Position).Magnitude or 0
            if dist <= MAX_GRAB_DISTANCE + 10 then
                grabChair(chair)
            end
        end
    end

    -- PC Manual HUD
    local manualFullSize = G.Math.ud2(0, 310, 0, 115)
    local manualMiniSize = G.Math.ud2(0, 34, 0, 34)

    FunData.ChairData.pcManualFrame = create("Frame", {
        Name = "ChairPCManualHUD",
        Size = manualFullSize,
        Position = G.Math.ud2(0.02, 0, 0.74, 0),
        BackgroundColor3 = G.Math.rgb(10, 10, 14),
        BackgroundTransparency = 0.2,
        Visible = false,
        ClipsDescendants = true,
        Parent = S.ScreenGui,
        ZIndex = 22
    }, { cCorner(10), cStroke(G.Math.rgb(255, 255, 255), 1.5) })
    makeDraggable(FunData.ChairData.pcManualFrame)

    local manualHeader = create("Frame", {
        Name = "Header",
        Size = G.Math.ud2(1, 0, 0, 26),
        BackgroundTransparency = 1,
        Parent = FunData.ChairData.pcManualFrame,
        ZIndex = 23
    })

    FunData.ChairData.pcManualTitle = create("TextLabel", {
        Name = "Title",
        Size = G.Math.ud2(1, -36, 1, 0),
        Position = G.Math.ud2(0, 10, 0, 0),
        BackgroundTransparency = 1,
        Text = (states.language == "Russian") and "🔮 ARCHIVES CHAIR СИНХРОНИЗАЦИЯ" or "🔮 ARCHIVES CHAIR LIVE SYNC",
        TextColor3 = G.Math.rgb(255, 255, 255),
        Font = Enum.Font.GothamBold,
        TextSize = 11,
        TextXAlignment = Enum.TextXAlignment.Left,
        Parent = manualHeader,
        ZIndex = 23
    })

    FunData.ChairData.pcManualToggleBtn = create("TextButton", {
        Name = "CollapseBtn",
        Size = G.Math.ud2(0, 22, 0, 22),
        Position = G.Math.ud2(1, -26, 0, 2),
        BackgroundColor3 = G.Math.rgb(15, 15, 20),
        Text = "—",
        TextColor3 = G.Math.rgb(255, 255, 255),
        Font = Enum.Font.GothamBold,
        TextSize = 12,
        Parent = manualHeader,
        ZIndex = 24
    }, { cCorner(6), cStroke(G.Math.rgb(255, 255, 255), 1.2) })

    FunData.ChairData.pcManualContent = create("Frame", {
        Name = "Content",
        Size = G.Math.ud2(1, -20, 1, -30),
        Position = G.Math.ud2(0, 10, 0, 26),
        BackgroundTransparency = 1,
        Parent = FunData.ChairData.pcManualFrame,
        ZIndex = 23
    })

    local function addManualLine(txt)
        local lbl = create("TextLabel", {
            Size = G.Math.ud2(1, 0, 0, 16),
            BackgroundTransparency = 1,
            Text = txt,
            TextColor3 = G.Math.rgb(240, 240, 245),
            Font = Enum.Font.GothamMedium,
            TextSize = 10,
            TextXAlignment = Enum.TextXAlignment.Left,
            Parent = FunData.ChairData.pcManualContent,
            ZIndex = 23
        })
        FunData.ChairData.pcManualLabels[#FunData.ChairData.pcManualLabels + 1] = lbl
        return lbl
    end

    addManualLine("[E] — " .. ((states.language == "Russian") and "Взять / Опустить стул (видят все)" or "Grab / Drop chair (synced)"))
    addManualLine("[ЛКМ] — " .. ((states.language == "Russian") and "БРОСИТЬ стул со всей силы" or "THROW chair with power"))
    addManualLine("[R] / [T] — " .. ((states.language == "Russian") and "Вращение стулa в воздухе (Yaw / Pitch)" or "Rotate chair (Yaw / Pitch)"))
    addManualLine("[Wheel] — " .. ((states.language == "Russian") and "Дистанция удержания" or "Hold Distance"))
    addManualLine("[Seat] — " .. ((states.language == "Russian") and "Полет верхом (WASD + Space + Shift)" or "Ride flight (WASD + Space + Shift)"))

    local function setManualCollapsed(collapsed)
        FunData.ChairData.pcManualExpanded = not collapsed
        local ts = G.Services.TweenService or game:GetService("TweenService")
        local tInfo = TweenInfo.new(0.22, Enum.EasingStyle.Quad, Enum.EasingDirection.Out)
        if collapsed then
            FunData.ChairData.pcManualContent.Visible = false
            FunData.ChairData.pcManualTitle.Visible = false
            FunData.ChairData.pcManualToggleBtn.Text = "🪑"
            FunData.ChairData.pcManualToggleBtn.Size = G.Math.ud2(1, 0, 1, 0)
            FunData.ChairData.pcManualToggleBtn.Position = G.Math.ud2(0, 0, 0, 0)
            FunData.ChairData.pcManualToggleBtn.BackgroundTransparency = 1
            ts:Create(FunData.ChairData.pcManualFrame, tInfo, {Size = manualMiniSize}):Play()
        else
            local tw = ts:Create(FunData.ChairData.pcManualFrame, tInfo, {Size = manualFullSize})
            tw:Play()
            FunData.ChairData.pcManualToggleBtn.Text = "—"
            FunData.ChairData.pcManualToggleBtn.Size = G.Math.ud2(0, 22, 0, 22)
            FunData.ChairData.pcManualToggleBtn.Position = G.Math.ud2(1, -26, 0, 2)
            FunData.ChairData.pcManualToggleBtn.BackgroundTransparency = 0
            tw.Completed:Connect(function()
                if FunData.ChairData.pcManualExpanded then
                    FunData.ChairData.pcManualContent.Visible = true
                    FunData.ChairData.pcManualTitle.Visible = true
                end
            end)
        end
    end

    FunData.ChairData.pcManualToggleBtn.MouseButton1Click:Connect(function()
        setManualCollapsed(FunData.ChairData.pcManualExpanded)
    end)

    -- Мобильный пульт для стульев
    FunData.ChairData.mobilePad = create("Frame", {
        Name = "ChairMobilePad",
        Size = G.Math.ud2(0, 168, 0, 126),
        Position = G.Math.ud2(1, -182, 0.36, 0),
        BackgroundColor3 = G.Math.rgb(10, 10, 14),
        BackgroundTransparency = 0.2,
        Visible = false,
        Parent = S.ScreenGui,
        ZIndex = 25
    }, { cCorner(12), cStroke(G.Math.rgb(255, 255, 255), 1.5) })
    makeDraggable(FunData.ChairData.mobilePad)

    create("TextLabel", {
        Size = G.Math.ud2(1, 0, 0, 20),
        BackgroundTransparency = 1,
        Text = "CHAIR CONTROLS",
        TextColor3 = G.Math.rgb(255, 255, 255),
        Font = Enum.Font.GothamBold,
        TextSize = 10,
        Parent = FunData.ChairData.mobilePad,
        ZIndex = 26
    })

    local function createMobileChairBtn(icon, pos, clickCb)
        local btn = create("TextButton", {
            Size = G.Math.ud2(0, 34, 0, 34),
            Position = pos,
            BackgroundColor3 = G.Math.rgb(16, 16, 20),
            Text = icon,
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBlack,
            TextSize = 14,
            Parent = FunData.ChairData.mobilePad,
            ZIndex = 26
        }, { cCorner(8), cStroke(G.Math.rgb(255, 255, 255), 1.2) })
        if clickCb then btn.MouseButton1Click:Connect(clickCb) end
        return btn
    end

    createMobileChairBtn("🪑", G.Math.ud2(0, 6, 0, 22), function()
        if FunData.ChairData.heldChair then releaseChair(false) else tryGrabNearestChair() end
    end)
    createMobileChairBtn("🚀", G.Math.ud2(0, 46, 0, 22), function()
        if FunData.ChairData.heldChair then releaseChair(true) end
    end)
    createMobileChairBtn("🔄", G.Math.ud2(0, 86, 0, 22), function()
        if FunData.ChairData.heldChair then FunData.ChairData.rotYaw = FunData.ChairData.rotYaw + math.rad(45) end
    end)
    createMobileChairBtn("🔃", G.Math.ud2(0, 126, 0, 22), function()
        if FunData.ChairData.heldChair then FunData.ChairData.rotPitch = FunData.ChairData.rotPitch + math.rad(45) end
    end)
    createMobileChairBtn("➕", G.Math.ud2(0, 6, 0, 62), function()
        if FunData.ChairData.heldChair then FunData.ChairData.holdDistance = G.Math.clamp(FunData.ChairData.holdDistance + 2.5, 6, MAX_GRAB_DISTANCE) end
    end)
    createMobileChairBtn("➖", G.Math.ud2(0, 46, 0, 62), function()
        if FunData.ChairData.heldChair then FunData.ChairData.holdDistance = G.Math.clamp(FunData.ChairData.holdDistance - 2.5, 6, MAX_GRAB_DISTANCE) end
    end)

    local btnChairUp = createMobileChairBtn("▲", G.Math.ud2(0, 86, 0, 62), nil)
    btnChairUp.InputBegan:Connect(function(inp)
        if inp.UserInputType == Enum.UserInputType.Touch or inp.UserInputType == Enum.UserInputType.MouseButton1 then
            FunData.ChairData.mobileFlyUp = true
        end
    end)
    btnChairUp.InputEnded:Connect(function(inp)
        if inp.UserInputType == Enum.UserInputType.Touch or inp.UserInputType == Enum.UserInputType.MouseButton1 then
            FunData.ChairData.mobileFlyUp = false
        end
    end)

    local btnChairDown = createMobileChairBtn("▼", G.Math.ud2(0, 126, 0, 62), nil)
    btnChairDown.InputBegan:Connect(function(inp)
        if inp.UserInputType == Enum.UserInputType.Touch or inp.UserInputType == Enum.UserInputType.MouseButton1 then
            FunData.ChairData.mobileFlyDown = true
        end
    end)
    btnChairDown.InputEnded:Connect(function(inp)
        if inp.UserInputType == Enum.UserInputType.Touch or inp.UserInputType == Enum.UserInputType.MouseButton1 then
            FunData.ChairData.mobileFlyDown = false
        end
    end)

    local function updateChairUI()
        local enabled = (states.chairManipulation == true)
        if FunData.ChairData.mobilePad then
            FunData.ChairData.mobilePad.Visible = isTouchDevice and enabled
        end
        if FunData.ChairData.pcManualFrame then
            FunData.ChairData.pcManualFrame.Visible = (not isTouchDevice) and enabled
        end
    end

    local chairInputConn = G.Services.UserInputService.InputBegan:Connect(function(input, gameProcessed)
        if gameProcessed or not states.chairManipulation then return end
        if input.KeyCode == Enum.KeyCode.E then
            if FunData.ChairData.heldChair then releaseChair(false) else tryGrabNearestChair() end
        elseif input.UserInputType == Enum.UserInputType.MouseButton1 then
            if FunData.ChairData.heldChair then releaseChair(true) end
        elseif input.KeyCode == Enum.KeyCode.R then
            if FunData.ChairData.heldChair then FunData.ChairData.rotYaw = FunData.ChairData.rotYaw + math.rad(45) end
        elseif input.KeyCode == Enum.KeyCode.T then
            if FunData.ChairData.heldChair then FunData.ChairData.rotPitch = FunData.ChairData.rotPitch + math.rad(45) end
        end
    end)
    FunData.connections[#FunData.connections + 1] = chairInputConn

    local chairWheelConn = G.Services.UserInputService.InputChanged:Connect(function(input, gameProcessed)
        if gameProcessed or not states.chairManipulation then return end
        if input.UserInputType == Enum.UserInputType.MouseWheel and FunData.ChairData.heldChair then
            FunData.ChairData.holdDistance = G.Math.clamp(FunData.ChairData.holdDistance + (input.Position.Z * 2.5), 6, MAX_GRAB_DISTANCE)
        end
    end)
    FunData.connections[#FunData.connections + 1] = chairWheelConn

    local chairHeartbeatConn = G.Services.RunService.Heartbeat:Connect(function()
        if not states.chairManipulation then return end

        local char = player.Character
        local humanoid = char and char:FindFirstChildOfClass("Humanoid")
        local seat = humanoid and humanoid.SeatPart

        if seat then
            local chair = getChairModel(seat)
            if chair and not FunData.ChairData.ridingChair then
                FunData.ChairData.ridingChair = chair
                FunData.ChairData.rideSeat = seat
                setChairHighlight(FunData.ChairData.ridingChair, G.Math.rgb(50, 210, 255))
            end
        else
            if FunData.ChairData.ridingChair then
                removeChairHighlight(FunData.ChairData.ridingChair)
                if FunData.ChairData.rideSeat and FunData.ChairData.rideSeat.Parent then
                    FunData.ChairData.rideSeat.AssemblyLinearVelocity = G.Math.v3(0, 0, 0)
                    FunData.ChairData.rideSeat.AssemblyAngularVelocity = G.Math.v3(0, 0, 0)
                end
                FunData.ChairData.ridingChair = nil
                FunData.ChairData.rideSeat = nil
            end
        end

        local heldChair = FunData.ChairData.heldChair
        local heldRoot = FunData.ChairData.heldRoot
        if heldChair and heldRoot and heldRoot.Parent then
            local cam = G.Services.Workspace.CurrentCamera or Camera
            local camCF = cam.CFrame
            local targetPos = camCF.Position + (camCF.LookVector * FunData.ChairData.holdDistance)

            local displacement = (targetPos - heldRoot.Position)
            local targetLinearVelocity = displacement * 22
            if targetLinearVelocity.Magnitude > 130 then targetLinearVelocity = targetLinearVelocity.Unit * 130 end
            heldRoot.AssemblyLinearVelocity = targetLinearVelocity

            local cameraYaw = math.atan2(-camCF.LookVector.X, -camCF.LookVector.Z)
            local targetRot = CFrame.Angles(0, cameraYaw, 0) * CFrame.Angles(FunData.ChairData.rotPitch, FunData.ChairData.rotYaw, 0)
            local currentRot = heldRoot.CFrame - heldRoot.Position
            local deltaCF = targetRot * currentRot:Inverse()
            local axis, angle = deltaCF:ToAxisAngle()
            if angle > math.pi then angle = angle - (2 * math.pi) end

            local targetAngularVelocity = axis * (angle * 18)
            if targetAngularVelocity.Magnitude > 35 then targetAngularVelocity = targetAngularVelocity.Unit * 35 end
            heldRoot.AssemblyAngularVelocity = targetAngularVelocity
        end

        local ridingChair = FunData.ChairData.ridingChair
        local rideSeat = FunData.ChairData.rideSeat
        if ridingChair and rideSeat and rideSeat.Parent then
            local moveDir = G.Math.v3(0, 0, 0)
            local cam = G.Services.Workspace.CurrentCamera or Camera
            local camCF = cam.CFrame
            local uis = G.Services.UserInputService

            if uis:IsKeyDown(Enum.KeyCode.W) then moveDir = moveDir + camCF.LookVector end
            if uis:IsKeyDown(Enum.KeyCode.S) then moveDir = moveDir - camCF.LookVector end
            if uis:IsKeyDown(Enum.KeyCode.A) then moveDir = moveDir - camCF.RightVector end
            if uis:IsKeyDown(Enum.KeyCode.D) then moveDir = moveDir + camCF.RightVector end
            if uis:IsKeyDown(Enum.KeyCode.Space) then moveDir = moveDir + G.Math.v3(0, 1, 0) end
            if uis:IsKeyDown(Enum.KeyCode.LeftShift) or uis:IsKeyDown(Enum.KeyCode.LeftControl) then
                moveDir = moveDir - G.Math.v3(0, 1, 0)
            end

            if FunData.ChairData.mobileFlyUp then moveDir = moveDir + G.Math.v3(0, 1, 0) end
            if FunData.ChairData.mobileFlyDown then moveDir = moveDir - G.Math.v3(0, 1, 0) end

            local flySpeed = states.chairFlySpeed or 50
            if moveDir.Magnitude > 0 then
                rideSeat.AssemblyLinearVelocity = moveDir.Unit * flySpeed
            else
                rideSeat.AssemblyLinearVelocity = G.Math.v3(0, 0, 0)
            end

            local lookFlat = G.Math.v3(camCF.LookVector.X, 0, camCF.LookVector.Z)
            if lookFlat.Magnitude > 0.05 then
                local targetRot = CFrame.lookAt(G.Math.v3(0, 0, 0), lookFlat.Unit)
                local currentRot = rideSeat.CFrame - rideSeat.Position
                local deltaCF = targetRot * currentRot:Inverse()
                local axis, angle = deltaCF:ToAxisAngle()
                if angle > math.pi then angle = angle - (2 * math.pi) end
                rideSeat.AssemblyAngularVelocity = axis * (angle * 12)
            else
                rideSeat.AssemblyAngularVelocity = G.Math.v3(0, 0, 0)
            end
        end
    end)
    FunData.connections[#FunData.connections + 1] = chairHeartbeatConn

    -- ========================================================
    -- СИСТЕМА ПОТУЖНОЛІТ / POTUJNOLIT (ВЕРТОЛІТ ЗСУ)
    -- ========================================================
    local UKR_BLUE   = Color3.fromRGB(0, 91, 187)
    local UKR_YELLOW = Color3.fromRGB(255, 213, 0)
    local DARK_METAL = Color3.fromRGB(32, 34, 38)
    local GLASS_TINT = Color3.fromRGB(15, 30, 45)

    local MAX_HELI_SPEED = 95
    local MAX_HELI_CLIMB = 48
    local HELI_TURN_SPEED = 2.4
    local HELI_GROUND_OFFSET = 2.2

    local function buildPotujnolitModel(startCFrame)
        local model = Instance.new("Model")
        model.Name = "POTUJNOLIT_UA_HELI"

        local function part(name, size, cf, color, mat, canCol, trans)
            local p = Instance.new("Part")
            p.Name = name
            p.Size = size
            p.CFrame = startCFrame * cf
            p.Color = color or UKR_BLUE
            p.Material = mat or Enum.Material.SmoothPlastic
            p.CanCollide = (canCol == true)
            p.Transparency = trans or 0
            p.Anchored = true
            p.Parent = model
            return p
        end

        local base = part("RootPart", Vector3.new(4.4, 2.2, 10.5), CFrame.new(0, 2.2, 0), UKR_BLUE, Enum.Material.SmoothPlastic, false)
        model.PrimaryPart = base

        part("Belly", Vector3.new(4.4, 1.2, 10.5), CFrame.new(0, 0.7, 0), UKR_YELLOW, Enum.Material.SmoothPlastic, false)
        part("Cockpit", Vector3.new(4.2, 2.4, 3.6), CFrame.new(0, 1.9, -5.8), GLASS_TINT, Enum.Material.Glass, false, 0.45)
        part("NoseCone", Vector3.new(4.2, 1.0, 3.0), CFrame.new(0, 0.6, -5.5), UKR_YELLOW, Enum.Material.SmoothPlastic, false)
        part("TailBoom", Vector3.new(1.6, 1.6, 13), CFrame.new(0, 2.3, 9.5), UKR_BLUE, Enum.Material.SmoothPlastic, false)

        part("TailFin", Vector3.new(0.4, 4.2, 2.8), CFrame.new(0, 3.9, 15.5) * CFrame.Angles(math.rad(-15), 0, 0), UKR_YELLOW, Enum.Material.SmoothPlastic, false)
        local finTop = part("TailFinTop", Vector3.new(0.42, 2.0, 2.4), CFrame.new(0, 4.9, 15.8) * CFrame.Angles(math.rad(-15), 0, 0), UKR_BLUE, Enum.Material.SmoothPlastic, false)

        local function addMarking(face)
            local gui = Instance.new("SurfaceGui")
            gui.Face = face
            local label = Instance.new("TextLabel")
            label.Size = UDim2.new(1, 0, 1, 0)
            label.BackgroundTransparency = 1
            label.Text = "🇺🇦 ЗСУ"
            label.TextColor3 = UKR_YELLOW
            label.Font = Enum.Font.GothamBlack
            label.TextScaled = true
            label.Parent = gui
            gui.Parent = finTop
        end
        addMarking(Enum.NormalId.Right)
        addMarking(Enum.NormalId.Left)

        part("SkidL", Vector3.new(0.4, 0.4, 11.5), CFrame.new(-2.3, -0.6, -0.5), DARK_METAL, Enum.Material.Metal, false)
        part("SkidR", Vector3.new(0.4, 0.4, 11.5), CFrame.new(2.3, -0.6, -0.5), DARK_METAL, Enum.Material.Metal, false)
        part("ArchFront", Vector3.new(4.8, 0.35, 0.35), CFrame.new(0, -0.1, -3.2), DARK_METAL, Enum.Material.Metal, false)
        part("ArchRear",  Vector3.new(4.8, 0.35, 0.35), CFrame.new(0, -0.1, 2.6), DARK_METAL, Enum.Material.Metal, false)

        part("NavRed", Vector3.new(0.3, 0.3, 0.3), CFrame.new(-2.3, 2.1, 0), Color3.fromRGB(255, 30, 30), Enum.Material.Neon, false)
        part("NavGreen", Vector3.new(0.3, 0.3, 0.3), CFrame.new(2.3, 2.1, 0), Color3.fromRGB(30, 255, 30), Enum.Material.Neon, false)

        part("Mast", Vector3.new(0.7, 1.6, 0.7), CFrame.new(0, 3.9, -0.5), DARK_METAL, Enum.Material.Metal, false)
        local mainRotor = part("MainRotor", Vector3.new(0.8, 0.15, 25), CFrame.new(0, 4.7, -0.5), DARK_METAL, Enum.Material.Metal, false)
        local bladeCross = part("BladeCross", Vector3.new(25, 0.15, 0.8), CFrame.new(0, 4.7, -0.5), DARK_METAL, Enum.Material.Metal, false)

        for _, offset in ipairs({-12, 12}) do
            part("Tip1", Vector3.new(0.82, 0.16, 1.2), CFrame.new(0, 4.7, -0.5 + offset), UKR_YELLOW, Enum.Material.SmoothPlastic, false)
            part("Tip2", Vector3.new(1.2, 0.16, 0.82), CFrame.new(offset, 4.7, -0.5), UKR_YELLOW, Enum.Material.SmoothPlastic, false)
        end

        local tailRotor = part("TailRotor", Vector3.new(0.2, 4.0, 0.4), CFrame.new(0.4, 4.7, 16.2), UKR_YELLOW, Enum.Material.Metal, false)

        local lamp = part("Searchlight", Vector3.new(0.8, 0.8, 0.6), CFrame.new(0, 0, -6.8) * CFrame.Angles(math.rad(-15), 0, 0), Color3.fromRGB(255, 255, 220), Enum.Material.Neon, false)
        local light = Instance.new("SpotLight")
        light.Brightness = 8
        light.Range = 170
        light.Angle = 55
        light.Face = Enum.NormalId.Front
        light.Enabled = false
        light.Parent = lamp

        local sound = Instance.new("Sound")
        sound.SoundId = "rbxassetid://9114223171"
        sound.Volume = 0
        sound.Looped = true
        sound.RollOffMaxDistance = 600
        sound.Parent = base
        sound:Play()

        local smokeAtt = Instance.new("Attachment")
        smokeAtt.Position = Vector3.new(0, 1.8, 1.5)
        smokeAtt.Parent = base

        local crashSmoke = Instance.new("ParticleEmitter")
        crashSmoke.Name = "CrashSmoke"
        crashSmoke.Rate = 0
        crashSmoke.Lifetime = NumberRange.new(1.5, 2.5)
        crashSmoke.Speed = NumberRange.new(8, 14)
        crashSmoke.SpreadAngle = Vector2.new(35, 35)
        crashSmoke.Size = NumberSequence.new({NumberSequenceKeypoint.new(0, 1), NumberSequenceKeypoint.new(1, 4.5)})
        crashSmoke.Transparency = NumberSequence.new({NumberSequenceKeypoint.new(0, 0.5), NumberSequenceKeypoint.new(1, 1)})
        crashSmoke.Color = ColorSequence.new(Color3.fromRGB(30, 30, 30))
        crashSmoke.Parent = smokeAtt

        local prompt = Instance.new("ProximityPrompt")
        prompt.ActionText = "Board POTUJNOLIT"
        prompt.ObjectText = "POTUJNOLIT HELICOPTER"
        prompt.KeyboardKeyCode = Enum.KeyCode.E
        prompt.HoldDuration = 0
        prompt.MaxActivationDistance = 15
        prompt.Parent = base

        model.Parent = G.Services.Workspace

        local offsets = {}
        for _, obj in ipairs(model:GetChildren()) do
            if obj:IsA("BasePart") and obj ~= base then
                offsets[obj] = base.CFrame:ToObjectSpace(obj.CFrame)
            end
        end

        return {
            Model = model,
            Root = base,
            MainRotor = mainRotor,
            BladeCross = bladeCross,
            TailRotor = tailRotor,
            Light = light,
            Sound = sound,
            CrashSmoke = crashSmoke,
            Prompt = prompt,
            Offsets = offsets
        }
    end

    local function createPotujnolitHUD()
        local frame = create("Frame", {
            Name = "PotujnolitHUDFrame",
            Size = G.Math.ud2(0, 320, 0, 160),
            Position = G.Math.ud2(0.02, 0, 0.72, 0),
            BackgroundColor3 = G.Math.rgb(10, 10, 14),
            BackgroundTransparency = 0.15,
            Visible = false,
            Parent = S.ScreenGui,
            ZIndex = 30
        }, { cCorner(12), cStroke(G.Math.rgb(255, 255, 255), 1.8) })
        makeDraggable(frame)

        create("TextLabel", {
            Size = G.Math.ud2(1, -20, 0, 24),
            Position = G.Math.ud2(0, 10, 0, 8),
            BackgroundTransparency = 1,
            Text = "🚁 POTUJNOLIT FLIGHT TELEMETRY",
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 13,
            TextXAlignment = Enum.TextXAlignment.Left,
            Parent = frame,
            ZIndex = 31
        })

        create("TextLabel", {
            Size = G.Math.ud2(1, -20, 0, 68),
            Position = G.Math.ud2(0, 10, 0, 34),
            BackgroundTransparency = 1,
            Text = "[W / S] - Pitch (Fwd / Back)\n[A / D] - Yaw / Roll (Left / Right)\n[Space / Shift] - Climb / Descend\n[F] - Searchlight | [E] - Eject Pilot",
            TextColor3 = G.Math.rgb(200, 200, 200),
            Font = Enum.Font.GothamMedium,
            TextSize = 11,
            TextXAlignment = Enum.TextXAlignment.Left,
            Parent = frame,
            ZIndex = 31
        })

        local teleLabel = create("TextLabel", {
            Size = G.Math.ud2(1, -20, 0, 30),
            Position = G.Math.ud2(0, 10, 0, 114),
            BackgroundTransparency = 1,
            Text = "SPEED: 0 KM/H | ALT: 0 M | STATUS: READY",
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 12,
            TextXAlignment = Enum.TextXAlignment.Left,
            Parent = frame,
            ZIndex = 31
        })

        return { Frame = frame, Telemetry = teleLabel }
    end

    local function createPotujnolitMobilePad()
        local pad = create("Frame", {
            Name = "PotujnolitMobilePad",
            Size = G.Math.ud2(0, 196, 0, 142),
            Position = G.Math.ud2(0.78, -100, 0.45, 0),
            BackgroundColor3 = G.Math.rgb(10, 10, 14),
            BackgroundTransparency = 0.2,
            Visible = false,
            Parent = S.ScreenGui,
            ZIndex = 32
        }, { cCorner(12), cStroke(G.Math.rgb(255, 255, 255), 1.5) })
        makeDraggable(pad)

        create("TextLabel", {
            Size = G.Math.ud2(1, 0, 0, 20),
            BackgroundTransparency = 1,
            Text = "POTUJNOLIT TOUCH CONTROLS",
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 9,
            Parent = pad,
            ZIndex = 33
        })

        local function makeHoldBtn(txt, pos, onStart, onEnd)
            local btn = create("TextButton", {
                Size = G.Math.ud2(0, 34, 0, 34),
                Position = pos,
                BackgroundColor3 = G.Math.rgb(18, 18, 24),
                Text = txt,
                TextColor3 = G.Math.rgb(255, 255, 255),
                Font = Enum.Font.GothamBold,
                TextSize = 13,
                Parent = pad,
                ZIndex = 33
            }, { cCorner(8), cStroke(G.Math.rgb(255, 255, 255), 1) })

            btn.InputBegan:Connect(function(inp)
                if inp.UserInputType == Enum.UserInputType.Touch or inp.UserInputType == Enum.UserInputType.MouseButton1 then
                    if onStart then onStart() end
                end
            end)
            btn.InputEnded:Connect(function(inp)
                if inp.UserInputType == Enum.UserInputType.Touch or inp.UserInputType == Enum.UserInputType.MouseButton1 then
                    if onEnd then onEnd() end
                end
            end)
            return btn
        end

        local h = FunData.HeliData
        makeHoldBtn("W", G.Math.ud2(0, 42, 0, 24), function() h.mobileThrottle = 1 end, function() if h.mobileThrottle == 1 then h.mobileThrottle = 0 end end)
        makeHoldBtn("S", G.Math.ud2(0, 42, 0, 62), function() h.mobileThrottle = -1 end, function() if h.mobileThrottle == -1 then h.mobileThrottle = 0 end end)
        makeHoldBtn("A", G.Math.ud2(0, 6, 0, 62), function() h.mobileSteer = 1 end, function() if h.mobileSteer == 1 then h.mobileSteer = 0 end end)
        makeHoldBtn("D", G.Math.ud2(0, 78, 0, 62), function() h.mobileSteer = -1 end, function() if h.mobileSteer == -1 then h.mobileSteer = 0 end end)

        makeHoldBtn("▲", G.Math.ud2(0, 118, 0, 24), function() h.mobileVertical = 1 end, function() if h.mobileVertical == 1 then h.mobileVertical = 0 end end)
        makeHoldBtn("▼", G.Math.ud2(0, 118, 0, 62), function() h.mobileVertical = -1 end, function() if h.mobileVertical == -1 then h.mobileVertical = 0 end end)

        makeHoldBtn("💡", G.Math.ud2(0, 156, 0, 24), function()
            if h.modelData and h.modelData.Light then
                h.lightOn = not h.lightOn
                h.modelData.Light.Enabled = h.lightOn
            end
        end, nil)

        makeHoldBtn("⏏", G.Math.ud2(0, 156, 0, 62), function()
            if h.isPiloting then
                FunData.ejectHelicopterPilot()
            end
        end, nil)

        create("TextLabel", {
            Size = G.Math.ud2(1, 0, 0, 30),
            Position = G.Math.ud2(0, 0, 0, 104),
            BackgroundTransparency = 1,
            Text = "Drag panel anywhere on screen",
            TextColor3 = G.Math.rgb(160, 160, 170),
            Font = Enum.Font.GothamMedium,
            TextSize = 9,
            Parent = pad,
            ZIndex = 33
        })

        return pad
    end

    FunData.HeliData.hud = createPotujnolitHUD()
    FunData.HeliData.mobilePad = createPotujnolitMobilePad()

    local function enterHelicopterPilot()
        local h = FunData.HeliData
        if not h.modelData or not h.modelData.Root then return end
        local char = player.Character
        local myHrp = char and char:FindFirstChild("HumanoidRootPart")
        local myHum = char and char:FindFirstChildOfClass("Humanoid")
        if not myHrp or not myHum then return end

        h.isPiloting = true
        h.isFalling = false
        h.isCrashed = false
        h.modelData.CrashSmoke.Rate = 0

        myHum.PlatformStand = true
        myHrp.Anchored = true
        local cam = G.Services.Workspace.CurrentCamera or Camera
        cam.CameraSubject = h.modelData.Root
        h.modelData.Prompt.Enabled = false

        h.hud.Frame.Visible = true
        if isTouchDevice and h.mobilePad then
            h.mobilePad.Visible = true
        end
    end

    local function ejectHelicopterPilot()
        local h = FunData.HeliData
        if not h.isPiloting then return end
        local char = player.Character
        local myHrp = char and char:FindFirstChild("HumanoidRootPart")
        local myHum = char and char:FindFirstChildOfClass("Humanoid")

        h.isPiloting = false
        if myHrp then myHrp.Anchored = false end
        if myHum then
            myHum.PlatformStand = false
            local cam = G.Services.Workspace.CurrentCamera or Camera
            cam.CameraSubject = myHum
        end

        if myHrp and h.modelData and h.modelData.Root then
            local forwardDir = h.modelData.Root.CFrame.LookVector
            myHrp.CFrame = h.modelData.Root.CFrame * CFrame.new(-7, -1.5, 0)
            myHrp.AssemblyLinearVelocity = (forwardDir * h.fwdVelocity) + Vector3.new(0, h.vertVelocity, 0)
        end

        if not h.isGrounded then
            h.isFalling = true
            h.isCrashed = false
            h.tumblePitchVel = math.rad(math.random(-35, -15))
            h.tumbleYawVel = math.rad(math.random(70, 140) * (math.random() > 0.5 and 1 or -1))
            h.tumbleRollVel = math.rad(math.random(-60, 60))
        else
            h.fwdVelocity = 0
            h.vertVelocity = 0
        end

        if h.modelData and h.modelData.Prompt then
            h.modelData.Prompt.ActionText = "Repair & Board"
            h.modelData.Prompt.Enabled = true
        end

        h.hud.Frame.Visible = false
        if h.mobilePad then h.mobilePad.Visible = false end
    end
    FunData.ejectHelicopterPilot = ejectHelicopterPilot

    local function despawnPotujnolit()
        local h = FunData.HeliData
        if h.isPiloting then ejectHelicopterPilot() end
        if h.renderConn then
            h.renderConn:Disconnect()
            h.renderConn = nil
        end
        if h.inputConn then
            h.inputConn:Disconnect()
            h.inputConn = nil
        end
        if h.modelData and h.modelData.Model then
            h.modelData.Model:Destroy()
        end
        h.modelData = nil
        h.hud.Frame.Visible = false
        if h.mobilePad then h.mobilePad.Visible = false end
        showNotification("POTUJNOLIT", "Helicopter removed successfully.", 2.5)
    end

    local function spawnPotujnolit()
        despawnPotujnolit()

        local char = player.Character
        local myHrp = char and char:FindFirstChild("HumanoidRootPart")
        local startSpawnCF = myHrp and (myHrp.CFrame * CFrame.new(0, 2, -18)) or (Camera.CFrame * CFrame.new(0, 2, -20))

        local h = FunData.HeliData
        h.modelData = buildPotujnolitModel(startSpawnCF)
        h.heliPos = h.modelData.Root.Position
        h.heliYaw = myHrp and myHrp.Orientation.Y or 0
        h.heliPitch = 0
        h.heliRoll = 0
        h.enginePower = 0
        h.fwdVelocity = 0
        h.vertVelocity = 0
        h.isGrounded = false
        h.isFalling = false
        h.isCrashed = false
        h.lightOn = false

        h.modelData.Prompt.Triggered:Connect(enterHelicopterPilot)

        h.inputConn = G.Services.UserInputService.InputBegan:Connect(function(input, processed)
            if processed then return end
            if input.KeyCode == Enum.KeyCode.E then
                if h.isPiloting then
                    ejectHelicopterPilot()
                elseif h.modelData and h.modelData.Root and player.Character and player.Character:FindFirstChild("HumanoidRootPart") then
                    local dist = (player.Character.HumanoidRootPart.Position - h.modelData.Root.Position).Magnitude
                    if dist < 16 then enterHelicopterPilot() end
                end
            elseif input.KeyCode == Enum.KeyCode.F and h.isPiloting then
                h.lightOn = not h.lightOn
                if h.modelData and h.modelData.Light then
                    h.modelData.Light.Enabled = h.lightOn
                end
            end
        end)
        FunData.connections[#FunData.connections + 1] = h.inputConn

        h.renderConn = G.Services.RunService.RenderStepped:Connect(function(dt)
            if not h.modelData or not h.modelData.Root or not h.modelData.Root.Parent then return end
            local ws = G.Services.Workspace
            local curChar = player.Character

            local rayParams = RaycastParams.new()
            rayParams.FilterDescendantsInstances = {h.modelData.Model, curChar}
            rayParams.FilterType = Enum.RaycastFilterType.Exclude
            local groundRay = ws:Raycast(h.heliPos + Vector3.new(0, 8, 0), Vector3.new(0, -800, 0), rayParams)
            local groundY = groundRay and groundRay.Position.Y or 0
            local floorLevel = groundY + HELI_GROUND_OFFSET

            if h.isPiloting then
                h.enginePower = math.clamp(h.enginePower + (1 - h.enginePower) * (dt * 2.2), 0, 1)
                local inThrottle = h.mobileThrottle
                local inSteer = h.mobileSteer
                local inVertical = h.mobileVertical

                local uis = G.Services.UserInputService
                if h.enginePower > 0.3 then
                    if uis:IsKeyDown(Enum.KeyCode.W) then inThrottle = inThrottle + 1 end
                    if uis:IsKeyDown(Enum.KeyCode.S) then inThrottle = inThrottle - 1 end
                    if uis:IsKeyDown(Enum.KeyCode.D) then inSteer = inSteer - 1 end
                    if uis:IsKeyDown(Enum.KeyCode.A) then inSteer = inSteer + 1 end
                    if uis:IsKeyDown(Enum.KeyCode.Space) then inVertical = inVertical + 1 end
                    if uis:IsKeyDown(Enum.KeyCode.LeftShift) then inVertical = inVertical - 1 end
                end

                local targetFwd = inThrottle * MAX_HELI_SPEED * h.enginePower
                local targetVert = inVertical * MAX_HELI_CLIMB * h.enginePower
                h.fwdVelocity = h.fwdVelocity + (targetFwd - h.fwdVelocity) * (dt * 3.5)
                h.vertVelocity = h.vertVelocity + (targetVert - h.vertVelocity) * (dt * 3.5)

                h.heliYaw = h.heliYaw + (inSteer * HELI_TURN_SPEED * dt * 57.3 * h.enginePower)
                local targetPitch = math.rad(-inThrottle * 18 * h.enginePower)
                local targetRoll = math.rad(-inSteer * 22 * h.enginePower)
                h.heliPitch = h.heliPitch + (targetPitch - h.heliPitch) * (dt * 4.5)
                h.heliRoll = h.heliRoll + (targetRoll - h.heliRoll) * (dt * 4.5)

                local forwardLook = (CFrame.Angles(0, math.rad(h.heliYaw), 0) * Vector3.new(0, 0, -1))
                h.heliPos = h.heliPos + (forwardLook * h.fwdVelocity * dt) + Vector3.new(0, h.vertVelocity * dt, 0)

                if h.heliPos.Y <= floorLevel then
                    h.heliPos = Vector3.new(h.heliPos.X, floorLevel, h.heliPos.Z)
                    if h.vertVelocity < 0 then h.vertVelocity = 0 end
                    h.isGrounded = true
                    h.heliPitch = h.heliPitch * 0.8
                    h.heliRoll = h.heliRoll * 0.8
                else
                    h.isGrounded = false
                end

            elseif h.isFalling then
                h.enginePower = math.max(0, h.enginePower - dt * 0.8)
                h.vertVelocity = h.vertVelocity - (80 * dt)
                h.fwdVelocity = h.fwdVelocity * (1 - 0.35 * dt)

                h.heliPitch = h.heliPitch + h.tumblePitchVel * dt
                h.heliYaw = h.heliYaw + h.tumbleYawVel * dt
                h.heliRoll = h.heliRoll + h.tumbleRollVel * dt

                local forwardLook = (CFrame.Angles(0, math.rad(h.heliYaw), 0) * Vector3.new(0, 0, -1))
                h.heliPos = h.heliPos + (forwardLook * h.fwdVelocity * dt) + Vector3.new(0, h.vertVelocity * dt, 0)

                if h.heliPos.Y <= floorLevel then
                    h.heliPos = Vector3.new(h.heliPos.X, groundY + 1.2, h.heliPos.Z)
                    h.isFalling = false
                    h.isCrashed = true
                    h.isGrounded = true
                    h.fwdVelocity = 0
                    h.vertVelocity = 0
                    h.enginePower = 0
                    h.modelData.CrashSmoke.Rate = 45

                    local crashSnd = Instance.new("Sound")
                    crashSnd.SoundId = "rbxassetid://138087139"
                    crashSnd.Volume = 2
                    crashSnd.Parent = h.modelData.Root
                    crashSnd:Play()
                    G.Services.Debris:AddItem(crashSnd, 4)
                end
            else
                h.enginePower = math.max(0, h.enginePower - dt * 1.5)
                h.fwdVelocity = 0
                h.vertVelocity = 0
                if h.heliPos.Y <= floorLevel then
                    h.heliPos = Vector3.new(h.heliPos.X, floorLevel, h.heliPos.Z)
                    h.isGrounded = true
                end
            end

            h.rotorAngle = (h.rotorAngle + (h.enginePower * 2800 * dt)) % 360
            h.modelData.Sound.Volume = h.enginePower * 1.3
            h.modelData.Sound.PlaybackSpeed = 0.45 + (h.enginePower * 0.55)

            local finalRotation = CFrame.Angles(0, math.rad(h.heliYaw), 0) * CFrame.Angles(h.heliPitch, 0, h.heliRoll)
            local finalRootCF = CFrame.new(h.heliPos) * finalRotation
            h.modelData.Root.CFrame = finalRootCF

            for partObj, relCF in pairs(h.modelData.Offsets) do
                if partObj ~= h.modelData.MainRotor and partObj ~= h.modelData.BladeCross and partObj ~= h.modelData.TailRotor then
                    partObj.CFrame = finalRootCF * relCF
                end
            end

            local rotorBaseCF = finalRootCF * h.modelData.Offsets[h.modelData.MainRotor]
            h.modelData.MainRotor.CFrame = rotorBaseCF * CFrame.Angles(0, math.rad(h.rotorAngle), 0)
            h.modelData.BladeCross.CFrame = rotorBaseCF * CFrame.Angles(0, math.rad(h.rotorAngle + 90), 0)

            local tailRotorBaseCF = finalRootCF * h.modelData.Offsets[h.modelData.TailRotor]
            h.modelData.TailRotor.CFrame = tailRotorBaseCF * CFrame.Angles(math.rad(h.rotorAngle * 2), 0, 0)

            if h.isPiloting and curChar and curChar:FindFirstChild("HumanoidRootPart") then
                curChar.HumanoidRootPart.CFrame = finalRootCF * CFrame.new(0, 1.4, -3.8)
                local speedKmh = math.floor(math.abs(h.fwdVelocity) * 3.6)
                local altMeters = math.max(0, math.floor(h.heliPos.Y - groundY))
                h.hud.Telemetry.Text = string.format("SPEED: %d KM/H | ALT: %d M | %s", 
                    speedKmh, altMeters, h.isGrounded and "STATUS: GROUNDED" or (h.isCrashed and "STATUS: CRASHED" or "STATUS: IN FLIGHT"))
            end
        end)
        FunData.connections[#FunData.connections + 1] = h.renderConn

        task.wait(0.15)
        enterHelicopterPilot()
        showNotification("POTUJNOLIT", "Helicopter spawned! Boarded as pilot.", 3)
    end

    -- ========================================================
    -- СИСТЕМА УНИВЕРСАЛЬНОГО РЕСАЙЗЕРА (UNIVERSAL RESIZER)
    -- ========================================================
    local function applyResizeToObject(target, factor)
        if not target then return end

        local model = target:IsA("Model") and target or target:FindFirstAncestorOfClass("Model")
        local ws = G.Services.Workspace

        if model and model ~= ws and not model:IsA("Workspace") and not model:IsA("Terrain") then
            pcall(function()
                if model.ScaleTo then
                    local curScale = model:GetScale()
                    model:ScaleTo(curScale * factor)
                    return
                end
            end)

            local primary = model.PrimaryPart or model:FindFirstChildWhichIsA("BasePart")
            if primary then
                local origin = primary.Position
                for _, desc in ipairs(model:GetDescendants()) do
                    if desc:IsA("BasePart") then
                        pcall(function()
                            local rel = desc.Position - origin
                            desc.Size = desc.Size * factor
                            desc.Position = origin + (rel * factor)
                        end)
                    end
                end
                return
            end
        end

        if target:IsA("BasePart") and not target:IsA("Terrain") then
            pcall(function()
                target.Size = target.Size * factor
            end)
        end
    end

    local function resizeTargetUnderCursor()
        local ws = G.Services.Workspace
        local cam = ws.CurrentCamera or Camera
        local mouse = player:GetMouse()
        local target = mouse and mouse.Target

        if not target then
            local rayParams = RaycastParams.new()
            rayParams.FilterType = Enum.RaycastFilterType.Exclude
            if player.Character then rayParams.FilterDescendantsInstances = {player.Character} end
            local ray = ws:Raycast(cam.CFrame.Position, cam.CFrame.LookVector * 150, rayParams)
            if ray and ray.Instance then target = ray.Instance end
        end

        if target and not target:IsA("Terrain") then
            local factor = (FunData.ResizerData.mode == "ENLARGE") and (FunData.ResizerData.scaleStep or 1.25) or (1 / (FunData.ResizerData.scaleStep or 1.25))
            applyResizeToObject(target, factor)

            if FunData.ResizerData.statusLabel then
                FunData.ResizerData.statusLabel.Text = string.format("Last: %s (%s)", target.Name:sub(1, 14), FunData.ResizerData.mode)
            end
        end
    end

    local function resizeTargetAtTouch(touchPos)
        local ws = G.Services.Workspace
        local cam = ws.CurrentCamera or Camera
        local unitRay = cam:ViewportPointToRay(touchPos.X, touchPos.Y)
        local rayParams = RaycastParams.new()
        rayParams.FilterType = Enum.RaycastFilterType.Exclude
        if player.Character then rayParams.FilterDescendantsInstances = {player.Character} end
        local res = ws:Raycast(unitRay.Origin, unitRay.Direction * 250, rayParams)

        if res and res.Instance and not res.Instance:IsA("Terrain") then
            local factor = (FunData.ResizerData.mode == "ENLARGE") and (FunData.ResizerData.scaleStep or 1.25) or (1 / (FunData.ResizerData.scaleStep or 1.25))
            applyResizeToObject(res.Instance, factor)

            if FunData.ResizerData.statusLabel then
                FunData.ResizerData.statusLabel.Text = string.format("Last: %s (%s)", res.Instance.Name:sub(1, 14), FunData.ResizerData.mode)
            end
        end
    end

    local function createResizerHUD()
        local frame = create("Frame", {
            Name = "ResizerHUDFrame",
            Size = G.Math.ud2(0, 240, 0, 116),
            Position = G.Math.ud2(0.02, 0, 0.46, 0),
            BackgroundColor3 = G.Math.rgb(10, 10, 14),
            BackgroundTransparency = 0.15,
            Visible = false,
            Parent = S.ScreenGui,
            ZIndex = 30
        }, { cCorner(12), cStroke(G.Math.rgb(255, 255, 255), 1.8) })
        makeDraggable(frame)

        create("TextLabel", {
            Size = G.Math.ud2(1, -20, 0, 22),
            Position = G.Math.ud2(0, 10, 0, 6),
            BackgroundTransparency = 1,
            Text = "⚡ UNIVERSAL RESIZER",
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 12,
            TextXAlignment = Enum.TextXAlignment.Left,
            Parent = frame,
            ZIndex = 31
        })

        local modeBtn = create("TextButton", {
            Size = G.Math.ud2(1, -20, 0, 30),
            Position = G.Math.ud2(0, 10, 0, 32),
            BackgroundColor3 = G.Math.rgb(20, 20, 26),
            Text = "MODE: [ ENLARGE (+) ]",
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 12,
            Parent = frame,
            ZIndex = 31
        }, { cCorner(8), cStroke(G.Math.rgb(255, 255, 255), 1.2) })

        modeBtn.MouseButton1Click:Connect(function()
            if FunData.ResizerData.mode == "ENLARGE" then
                FunData.ResizerData.mode = "SHRINK"
                modeBtn.Text = "MODE: [ SHRINK (-) ]"
            else
                FunData.ResizerData.mode = "ENLARGE"
                modeBtn.Text = "MODE: [ ENLARGE (+) ]"
            end
        end)
        FunData.ResizerData.modeBtn = modeBtn

        local status = create("TextLabel", {
            Size = G.Math.ud2(1, -20, 0, 20),
            Position = G.Math.ud2(0, 10, 0, 68),
            BackgroundTransparency = 1,
            Text = "Target: None selected (Click / Tap)",
            TextColor3 = G.Math.rgb(180, 180, 190),
            Font = Enum.Font.GothamMedium,
            TextSize = 10,
            TextXAlignment = Enum.TextXAlignment.Left,
            Parent = frame,
            ZIndex = 31
        })
        FunData.ResizerData.statusLabel = status

        create("TextLabel", {
            Size = G.Math.ud2(1, -20, 0, 16),
            Position = G.Math.ud2(0, 10, 0, 92),
            BackgroundTransparency = 1,
            Text = "Works on: Props, Chars, Models, Vehicles",
            TextColor3 = G.Math.rgb(140, 140, 150),
            Font = Enum.Font.GothamMedium,
            TextSize = 9,
            TextXAlignment = Enum.TextXAlignment.Left,
            Parent = frame,
            ZIndex = 31
        })

        return frame
    end

    local function createResizerMobileButton()
        local btn = create("TextButton", {
            Name = "ResizerMobileActionButton",
            Size = G.Math.ud2(0, 52, 0, 52),
            Position = G.Math.ud2(1, -75, 0.58, 0),
            BackgroundColor3 = G.Math.rgb(10, 10, 14),
            BackgroundTransparency = 0.15,
            Text = "📐+",
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 18,
            Visible = false,
            Parent = S.ScreenGui,
            ZIndex = 30
        }, { cCorner(26), cStroke(G.Math.rgb(255, 255, 255), 1.5) })
        makeDraggable(btn)

        btn.MouseButton1Click:Connect(function()
            if FunData.ResizerData.mode == "ENLARGE" then
                FunData.ResizerData.mode = "SHRINK"
                btn.Text = "📐-"
            else
                FunData.ResizerData.mode = "ENLARGE"
                btn.Text = "📐+"
            end
            if FunData.ResizerData.modeBtn then
                FunData.ResizerData.modeBtn.Text = "MODE: [ " .. FunData.ResizerData.mode .. " ]"
            end
        end)
        return btn
    end

    FunData.ResizerData.hud = createResizerHUD()
    FunData.ResizerData.mobileBtn = createResizerMobileButton()

    local function toggleResizerMode(enabled)
        FunData.ResizerData.active = enabled
        if FunData.ResizerData.hud then
            FunData.ResizerData.hud.Visible = enabled
        end
        if FunData.ResizerData.mobileBtn then
            FunData.ResizerData.mobileBtn.Visible = isTouchDevice and enabled
        end

        if enabled then
            if not FunData.ResizerData.inputConn then
                FunData.ResizerData.inputConn = G.Services.UserInputService.InputBegan:Connect(function(input, processed)
                    if processed or not FunData.ResizerData.active then return end
                    if input.UserInputType == Enum.UserInputType.MouseButton1 then
                        resizeTargetUnderCursor()
                    elseif input.UserInputType == Enum.UserInputType.Touch then
                        resizeTargetAtTouch(input.Position)
                    end
                end)
                FunData.connections[#FunData.connections + 1] = FunData.ResizerData.inputConn
            end
        end
    end

    local function giveResizerTool()
        local bp = player:WaitForChild("Backpack", 5) or player:FindFirstChildOfClass("Backpack")
        if not bp or bp:FindFirstChild("Universal Resizer") or (player.Character and player.Character:FindFirstChild("Universal Resizer")) then return end

        local tool = Instance.new("Tool")
        tool.Name = "Universal Resizer"
        tool.RequiresHandle = true
        tool.CanBeDropped = false

        local handle = Instance.new("Part")
        handle.Name = "Handle"
        handle.Size = Vector3.new(0.8, 2.2, 0.8)
        handle.Color = Color3.fromRGB(20, 20, 24)
        handle.Material = Enum.Material.SmoothPlastic
        handle.Parent = tool
        Instance.new("CylinderMesh", handle)

        local highlight = Instance.new("Highlight", handle)
        highlight.FillColor = Color3.fromRGB(255, 255, 255)
        highlight.OutlineColor = Color3.fromRGB(200, 200, 200)

        tool.Activated:Connect(function()
            resizeTargetUnderCursor()
        end)

        tool.Parent = bp
        FunData.ResizerData.toolInstance = tool
    end

    local function removeResizerTool()
        local bp = player:FindFirstChildOfClass("Backpack")
        if bp and bp:FindFirstChild("Universal Resizer") then bp["Universal Resizer"]:Destroy() end
        if player.Character and player.Character:FindFirstChild("Universal Resizer") then player.Character["Universal Resizer"]:Destroy() end
        FunData.ResizerData.toolInstance = nil
    end

    -- ========================================================
    -- СБОРКА ИНТЕРФЕЙСА СТРАНИЦЫ FUN
    -- ========================================================
    local pageFun = S.createPage("Fun", "Tab_Fun")

    -- СЕКЦИЯ ПОТУЖНОЛІТ / POTUJNOLIT
    S.createDivider(pageFun, "POTUJNOLIT / ПОТУЖНОЛІТ HELICOPTER")
    do
        local r = S.createRow(pageFun)
        local btnSpawnHeli = create("TextButton", {
            Size = G.Math.ud2(0.48, 0, 1, 0),
            BackgroundColor3 = G.Math.rgb(24, 24, 32),
            Text = "🚁 Spawn Potujnolit",
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 11,
            Parent = r,
            ZIndex = 7
        }, { cCorner(8), cStroke(G.Math.rgb(255, 255, 255), 1.2) })
        btnSpawnHeli.MouseButton1Click:Connect(spawnPotujnolit)

        local btnDespawnHeli = create("TextButton", {
            Size = G.Math.ud2(0.48, 0, 1, 0),
            BackgroundColor3 = G.Math.rgb(24, 24, 32),
            Text = "❌ Despawn",
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 11,
            Parent = r,
            ZIndex = 7
        }, { cCorner(8), cStroke(G.Math.rgb(255, 255, 255), 1.2) })
        btnDespawnHeli.MouseButton1Click:Connect(despawnPotujnolit)
    end

    -- СЕКЦИЯ РЕСАЙЗЕРА
    S.createDivider(pageFun, "UNIVERSAL RESIZER (ENLARGE / SHRINK)")
    do
        local r = S.createRow(pageFun)
        S.createToggle(r, "resizerActive", function(on)
            toggleResizerMode(on)
        end)
        S.createToggle(r, "resizerTool", function(on)
            if on then giveResizerTool() else removeResizerTool() end
        end)
    end
    S.createSlider(pageFun, 11, 30, 12, "resizerScaleStep", 1, function(val)
        FunData.ResizerData.scaleStep = val / 10
    end)

    -- СЕКЦИЯ СТУЛЬЕВ
    S.createDivider(pageFun, "ARCHIVES CHAIR MANIPULATION")
    do
        local r = S.createRow(pageFun)
        S.createToggle(r, "chairManipulation", function(on)
            updateChairUI()
            if not on then
                releaseChair(false)
                restoreChairCharacterCollision()
                if FunData.ChairData.ridingChair then
                    removeChairHighlight(FunData.ChairData.ridingChair)
                    FunData.ChairData.ridingChair = nil
                    FunData.ChairData.rideSeat = nil
                end
            end
        end)
    end
    S.createSlider(pageFun, 15, 120, 50, "chairFlySpeed", 5)
    S.createSlider(pageFun, 50, 300, 145, "chairThrowForce", 5)

    -- СЕКЦИЯ ГЛОУСТИКОВ
    S.createDivider(pageFun, "GLOWSTICK MANIPULATION")
    do
        local r = S.createRow(pageFun)
        S.createToggle(r, "glowstickEnabled", function(on)
            updateGlowstickMobileBtn()
            if on then scanGlowsticksOnce() end
        end)
        S.createToggle(r, "glowstickOrbit")
    end
    S.createSlider(pageFun, 1, 50, 4, "glowstickSpeed", 1)
    S.createSlider(pageFun, 1, 35, 8, "glowstickRadius", 1)
    S.createSlider(pageFun, -4, 8, 0, "glowstickHeight", 1)
    S.createToggle(pageFun, "glowstickTapShoot")

    FunData.glowstickStatusLabel = create("TextLabel", {
        Size = G.Math.ud2(0.98, 0, 0, 18),
        BackgroundTransparency = 1,
        Text = "Glowsticks active: 0",
        TextColor3 = G.Math.rgb(180, 180, 200),
        Font = Enum.Font.GothamMedium,
        TextSize = 11,
        Parent = pageFun,
        ZIndex = 7
    })

    -- ОРУЖИЕ И ПРЕДМЕТЫ
    S.createDivider(pageFun, "WEAPONS & ITEMS")
    do
        local r = S.createRow(pageFun)
        S.createToggle(r, "holyGrenade", function(on)
            if on then giveHolyGrenade() else removeHolyGrenade() end
        end)
        S.createToggle(r, "trashBasket", function(on)
            if on then giveTrashBasket() else removeTrashBasket() end
        end)
    end
    do
        local r = S.createRow(pageFun)
        S.createActionButton(r, "giveRiftSmoothie", function()
            giveInfiniteRiftSmoothie()
        end)
        S.createActionButton(r, "giveStarBottle", function()
            giveInfiniteStarBottle()
        end)
    end

    -- МУЗЫКАЛЬНЫЙ ПЛЕЕР
    S.createDivider(pageFun, "UNIVERSAL MUSIC PLAYER")
    FunData.musicInputBox = create("TextBox", {
        Size = G.Math.ud2(0.98, 0, 0, 38),
        BackgroundColor3 = G.Math.rgb(22, 22, 28),
        Text = "",
        PlaceholderText = (states.language == "Russian") and "Введите любой ID звука..." or "Enter any Sound ID...",
        TextColor3 = G.Math.rgb(255, 255, 255),
        PlaceholderColor3 = G.Math.rgb(120, 120, 135),
        Font = Enum.Font.GothamBold,
        TextSize = 11,
        Parent = pageFun,
        ZIndex = 7
    }, { cCorner(8), cStroke(G.Math.rgb(45, 45, 55), 1) })

    local mRow1 = S.createRow(pageFun)
    local function makeMusicBtn(txt, cb)
        local b = create("TextButton", {
            Size = G.Math.ud2(0.31, 0, 1, 0),
            BackgroundColor3 = G.Math.rgb(30, 30, 38),
            Text = txt,
            TextColor3 = G.Math.rgb(255, 255, 255),
            Font = Enum.Font.GothamBold,
            TextSize = 11,
            Parent = mRow1,
            ZIndex = 7
        }, { cCorner(8), cStroke(G.Math.rgb(45, 45, 55), 1) })
        b.MouseButton1Click:Connect(cb)
        return b
    end
    local btnPlay = makeMusicBtn((states.language == "Russian") and "▶ Играть" or "▶ Play", function() playMusicTrack(FunData.musicInputBox.Text) end)
    local btnPause = makeMusicBtn((states.language == "Russian") and "⏸ Пауза" or "⏸ Pause", pauseMusicTrack)
    local btnStop = makeMusicBtn((states.language == "Russian") and "⏹ Стоп" or "⏹ Stop", stopMusicTrack)

    S.createToggle(pageFun, "musicLoop", function(on) CustomSound.Looped = on end)
    S.createSlider(pageFun, 0, 100, 50, "musicVolume", 1, function(val) CustomSound.Volume = val / 100 end)

    local function addMusicPresetGrid(pTarget, title, presets)
        S.createDivider(pTarget, title)
        for i = 1, #presets, 2 do
            local r = S.createRow(pTarget)
            for j = i, math.min(i + 1, #presets) do
                local item = presets[j]
                local b = create("TextButton", {
                    Size = G.Math.ud2(0.48, 0, 1, 0),
                    BackgroundColor3 = G.Math.rgb(26, 26, 32),
                    Text = item[1],
                    TextColor3 = G.Math.rgb(230, 230, 240),
                    Font = Enum.Font.GothamBold,
                    TextSize = 11,
                    Parent = r,
                    ZIndex = 7
                }, { cCorner(8), cStroke(G.Math.rgb(42, 42, 52), 1) })
                b.MouseButton1Click:Connect(function()
                    FunData.musicInputBox.Text = item[2]
                    playMusicTrack(item[2])
                end)
            end
        end
    end

    addMusicPresetGrid(pageFun, "ROCK & BEATS PRESETS", {
        {"🏎️ Total Action", "1836554053"}, {"🎸 Heavy Rage", "1836552129"},
        {"⚡ Hardcore Rock", "1836088493"}, {"🔊 Non Stop Rock", "1836553401"}
    })

    addMusicPresetGrid(pageFun, "POPULAR PRESETS", {
        {"🦀 Crab Rave", "5410086218"}, {"☕ Lo-Fi Chill", "9043887091"},
        {"🔥 Seek & Destroy", "1845149698"}, {"🏖️ Poolside Chill", "9046863253"}
    })

    -- РЕЖИМ ТРУБЫ
    S.createDivider(pageFun, "PIPE MODE MEME")
    do
        local r = S.createRow(pageFun)
        S.createToggle(r, "pipeMode", function(on) togglePipeMode(on) end)
        S.createToggle(r, "pipeSoundEnabled", function(on)
            if states.pipeMode then
                togglePipeMode(false)
                task.wait(0.05)
                togglePipeMode(true)
            end
        end)
    end
    S.createSlider(pageFun, 0, 200, 100, "pipeVolumeMult", 1, updateAllPipeVolumes)

    -- ОСВЕЩЕНИЕ (ОПТИМИЗИРОВАННОЕ)
    S.createDivider(pageFun, "LIGHTING MODS")
    do
        local r = S.createRow(pageFun)
        S.createToggle(r, "newYearMode", function(on)
            if on and states.customLight then
                states.customLight = false
                if S.UI_STORAGE["customLight"] then
                    for _, ui in ipairs(S.UI_STORAGE["customLight"]) do
                        if ui.update then ui.update(false) end
                    end
                end
            end
            updateLights()
        end)
        S.createToggle(r, "customLight", function(on)
            if on and states.newYearMode then
                states.newYearMode = false
                if S.UI_STORAGE["newYearMode"] then
                    for _, ui in ipairs(S.UI_STORAGE["newYearMode"]) do
                        if ui.update then ui.update(false) end
                    end
                end
            end
            updateLights()
        end)
    end
    S.createSlider(pageFun, 0, 255, 255, "lightR", 1, updateLights)
    S.createSlider(pageFun, 0, 255, 0, "lightG", 1, updateLights)
    S.createSlider(pageFun, 0, 255, 255, "lightB", 1, updateLights)

    -- ========================================================
    -- МОДУЛЬ ВЗАИМОДЕЙСТВИЯ С ГЛАВНЫМ ЯДРОМ
    -- ========================================================
    local FunModule = {}

    FunModule.onCharacterAdded = function()
        if states.holyGrenade then giveHolyGrenade() end
        if states.trashBasket then giveTrashBasket() end
        if states.resizerTool then giveResizerTool() end
        if states.chairManipulation then
            releaseChair(false)
            restoreChairCharacterCollision()
        end
    end

    FunModule.onLightFound = function(obj)
        handleLightObject(obj)
    end

    FunModule.syncAll = function()
        updateLights()
        updateGlowstickMobileBtn()
        updateChairUI()
        if states.pipeMode then togglePipeMode(true) end
        if states.holyGrenade then giveHolyGrenade() end
        if states.trashBasket then giveTrashBasket() end
        if states.resizerTool then giveResizerTool() end
        if states.resizerActive then toggleResizerMode(true) end
    end

    FunModule.onLanguageChanged = function()
        if FunData.musicInputBox then
            FunData.musicInputBox.PlaceholderText = (states.language == "Russian") and "Введите любой ID звука..." or "Enter any Sound ID..."
        end
        if btnPlay then btnPlay.Text = (states.language == "Russian") and "▶ Играть" or "▶ Play" end
        if btnPause then btnPause.Text = (states.language == "Russian") and "⏸ Пауза" or "⏸ Pause" end
        if btnStop then btnStop.Text = (states.language == "Russian") and "⏹ Стоп" or "⏹ Stop" end

        if FunData.ChairData.pcManualTitle then
            FunData.ChairData.pcManualTitle.Text = (states.language == "Russian") and "🔮 ARCHIVES CHAIR СИНХРОНИЗАЦИЯ" or "🔮 ARCHIVES CHAIR LIVE SYNC"
        end
        if FunData.ChairData.pcManualLabels[1] then
            FunData.ChairData.pcManualLabels[1].Text = "[E] — " .. ((states.language == "Russian") and "Взять / Опустить стул (видят все)" or "Grab / Drop chair (synced)")
        end
        if FunData.ChairData.pcManualLabels[2] then
            FunData.ChairData.pcManualLabels[2].Text = "[ЛКМ] — " .. ((states.language == "Russian") and "БРОСИТЬ стул со всей силы" or "THROW chair with power")
        end
        if FunData.ChairData.pcManualLabels[3] then
            FunData.ChairData.pcManualLabels[3].Text = "[R] / [T] — " .. ((states.language == "Russian") and "Вращение стулa в воздухе (Yaw / Pitch)" or "Rotate chair (Yaw / Pitch)")
        end
        if FunData.ChairData.pcManualLabels[4] then
            FunData.ChairData.pcManualLabels[4].Text = "[Wheel] — " .. ((states.language == "Russian") and "Дистанция удержания" or "Hold Distance")
        end
        if FunData.ChairData.pcManualLabels[5] then
            FunData.ChairData.pcManualLabels[5].Text = "[Seat] — " .. ((states.language == "Russian") and "Полет верхом (WASD + Space + Shift)" or "Ride flight (WASD + Space + Shift)")
        end
    end

    FunModule.onHeartbeat = function()
        local now = tick()
        if (states.newYearMode or states.customLight) and (now - FunData.lastLightUpdate >= 1.0) then
            FunData.lastLightUpdate = now
            updateLights()
        end
    end

    FunModule.onRenderStepped = function(dt)
        if states.glowstickEnabled and states.glowstickOrbit then
            local char = player.Character
            local hrp = char and char:FindFirstChild("HumanoidRootPart")
            local numSticks = #FunData.activeGlowsticks

            if hrp and numSticks > 0 then
                FunData.glowstickAngle = (FunData.glowstickAngle + dt * (states.glowstickSpeed or 4)) % (2 * G.Math.pi)
                local hrpPos = hrp.Position + G.Math.v3(0, states.glowstickHeight or 0, 0)

                local needRaycast = (tick() - FunData.lastGlowstickRay > (isTouchDevice and 0.25 or 0.15))
                if needRaycast then FunData.lastGlowstickRay = tick() end

                local rayParams = nil
                local ws = G.Services.Workspace
                if needRaycast then
                    rayParams = RaycastParams.new()
                    rayParams.FilterType = Enum.RaycastFilterType.Exclude
                    local ignoreList = {char}
                    for _, stick in ipairs(FunData.activeGlowsticks) do
                        ignoreList[#ignoreList + 1] = stick
                        if stick.Parent and stick.Parent:IsA("Model") then
                            ignoreList[#ignoreList + 1] = stick.Parent
                        end
                    end
                    rayParams.FilterDescendantsInstances = ignoreList
                end

                local radius = states.glowstickRadius or 8
                for i, stick in ipairs(FunData.activeGlowsticks) do
                    if stick and stick.Parent and not FunData.shootingGlowsticks[stick] then
                        local stickAngle = FunData.glowstickAngle + ((i - 1) * (2 * G.Math.pi / numSticks))
                        local waveOffset = G.Math.sin(tick() * 3 + i) * 0.35
                        local dirUnit = G.Math.v3(G.Math.cos(stickAngle), 0, G.Math.sin(stickAngle))

                        local safeRadius = FunData.glowstickRaycastCache[stick] or radius
                        if needRaycast and rayParams then
                            local rayHit = ws:Raycast(hrpPos, dirUnit * radius, rayParams)
                            safeRadius = rayHit and G.Math.clamp((rayHit.Position - hrpPos).Magnitude - 0.5, 1.2, radius) or radius
                            FunData.glowstickRaycastCache[stick] = safeRadius
                        end

                        local targetPosition = hrpPos + (dirUnit * safeRadius) + G.Math.v3(0, waveOffset, 0)
                        local targetRotation = CFrame.Angles(G.Math.rad(tick() * 80 + (i * 45)), stickAngle, G.Math.rad(45))

                        stick.CanCollide = false
                        stick.AssemblyLinearVelocity = G.Math.v3()
                        stick.AssemblyAngularVelocity = G.Math.v3()
                        stick.CFrame = stick.CFrame:Lerp(G.Math.cf(targetPosition) * targetRotation, G.Math.clamp(dt * 20, 0, 1))
                    end
                end
            end
        end
    end

    FunModule.cleanup = function()
        despawnPotujnolit()
        removeResizerTool()
        toggleResizerMode(false)
        removeHolyGrenade()
        removeTrashBasket()
        togglePipeMode(false)

        -- Очистка оптимизированного освещения
        if FunData.lightAddedConn then
            FunData.lightAddedConn:Disconnect()
            FunData.lightAddedConn = nil
        end
        for light, origColor in pairs(FunData.lightsCache) do
            if light and light.Parent then light.Color = origColor end
        end
        for part, origColor in pairs(FunData.neonPartsCache) do
            if part and part.Parent then part.Color = origColor end
        end
        table.clear(FunData.lightsCache)
        table.clear(FunData.neonPartsCache)

        -- Очистка стульев
        releaseChair(false)
        restoreChairCharacterCollision()
        if FunData.ChairData.ridingChair then
            removeChairHighlight(FunData.ChairData.ridingChair)
            FunData.ChairData.ridingChair = nil
            FunData.ChairData.rideSeat = nil
        end
        if FunData.ChairData.mobilePad and FunData.ChairData.mobilePad.Parent then
            FunData.ChairData.mobilePad:Destroy()
        end
        if FunData.ChairData.pcManualFrame and FunData.ChairData.pcManualFrame.Parent then
            FunData.ChairData.pcManualFrame:Destroy()
        end

        -- Очистка Потужноліта
        if FunData.HeliData.hud and FunData.HeliData.hud.Frame and FunData.HeliData.hud.Frame.Parent then
            FunData.HeliData.hud.Frame:Destroy()
        end
        if FunData.HeliData.mobilePad and FunData.HeliData.mobilePad.Parent then
            FunData.HeliData.mobilePad:Destroy()
        end

        -- Очистка Ресайзера
        if FunData.ResizerData.hud and FunData.ResizerData.hud.Parent then
            FunData.ResizerData.hud:Destroy()
        end
        if FunData.ResizerData.mobileBtn and FunData.ResizerData.mobileBtn.Parent then
            FunData.ResizerData.mobileBtn:Destroy()
        end

        -- Музыка и глоустики
        if CustomSound then
            CustomSound:Stop()
            CustomSound:Destroy()
        end
        if FunData.glowstickMobileBtn and FunData.glowstickMobileBtn.Parent then
            FunData.glowstickMobileBtn:Destroy()
        end
        for _, conn in ipairs(FunData.connections) do
            if conn and conn.Connected then conn:Disconnect() end
        end
        table.clear(FunData.connections)
        table.clear(FunData.activeGlowsticks)
    end

    S.FunModule = FunModule
    return FunModule
end

local varArgs = {...}
if #varArgs > 0 and varArgs[1] then
    return InitFunModule(unpack(varArgs))
end
return InitFunModule

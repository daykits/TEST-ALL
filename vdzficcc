repeat task.wait() until game:IsLoaded()
getgenv().Premium = false
getgenv().Hide_UI = false
getgenv().Team = "Marines"
getgenv().Studio = {
    ["Blox Fruit"] = {
        ["Sub"] = {
            ["Pull Lever"] = true,
            ["Sniper Fruit"] = {
                ["Enabled"] = false,
                ["Fruit"] = { "Tiger-Tiger", "Kitsune-Kitsune", "Dragon-Dragon", "Yeti-Yeti", "Gas-Gas" },
            },
            ["Setting Player"] = {
                ["Lock Fps"] = {
                    ["Enabled"] = false,
                    ["FPS"] = 20,
                },
                ["Hop When Idle"] = true,
                ["Hop"] = {
                    ["Enable"] = false,
                    ["Delay"] = 5,
                },
                ["Select Hop"] = {                   -- 70% will have it / Paid
                    ["Hop Find Full Moon"] = true,   -- Done Paid / Free
                    ["Hop Find Rip Indra"] = true,   -- Done Paid / Soon
                    ["Hop Find Dough King"] = false, -- Done Paid / Free
                    ["Hop Find Cake Queen"] = true,  -- Done Paid / Free
                    ["Hop Find Soul Reaper"] = true, -- Done Paid / Free
                    ["Hop Find Darkbeard"] = true,   -- Done Paid / Free
                    ["Hop Find Raid Castle"] = true,
                }
            }
        },
        ["Items"] = {
            ["Material"] = {
                ["Dark Fragments"] = true,
                ["Mirror Fractal"] = true,
            },
            ["Melee"] = {
                ["Fighting Style"] = true,
            },
            ["Sword"] = {
                ["Saber"] = true,
                ["Cursed Dual Katana"] = true
            },
            ["Gun"] = {
                ["Skull Guitar"] = true,
            },
        },
        ["Webhook"] = {
            ["Url"] =
            "https://discord.com/api/webhooks/1455563179487657986/jKkWXzNwoCJX0IMK2RvrVah-Rx_xlF90Kq9dTMU5R567WgqWIRfUacUiy1n6cTThQ21D",
            ["Delay"] = 60,
            ["Ping Notify"] = "",
        },
    }
}

repeat
    task.wait()
    if game.Players.LocalPlayer.Team == nil then
        game.ReplicatedStorage.Remotes.CommF_:InvokeServer("SetTeam", getgenv().Team)
    end
until game.Players.LocalPlayer.Character

function _nguoitinhcuae()
    if getgenv()._vxeze_running then return end
    getgenv()._vxeze_running = true
    timeee = os.time()
    task.spawn(function()
        while true do
            if getfpscap() > getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Lock Fps"]["FPS"] then
                setfpscap(getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Lock Fps"]["FPS"] or 60)
            end
            task.wait(1)
        end
    end)

    function Price(x)
        local v = tostring(x)
        while true do
            v, k = v:gsub("^(-?%d+)(%d%d%d)", '%1,%2')
            if k == 0 then break end
        end
        return v
    end

    local HttpService = game:GetService("HttpService")

    local Hop = function(minPlayers, region)
        if type(minPlayers) == "string" then
            region = minPlayers
            minPlayers = nil
        end

        local ok, result = pcall(function()
            return HttpService:JSONDecode(game:HttpGet(
                "https://games.roblox.com/v1/games/" .. game.PlaceId .. "/servers/Public?sortOrder=Asc&limit=100"))
        end)

        if not ok or not result or type(result.data) ~= "table" then
            return
        end

        for _, v in ipairs(result.data) do
            if type(v) == "table" and v.playing and v.maxPlayers and v.id then
                local regionMatch = not region or v.region == region
                local playerCountMatch = not minPlayers or v.playing <= minPlayers

                if v.playing < v.maxPlayers and regionMatch and playerCountMatch and v.id ~= game.JobId then
                    pcall(function()
                        game:GetService("ReplicatedStorage").__ServerBrowser:InvokeServer("teleport", v.id)
                    end)
                    task.wait(5)
                    return
                end
            end
        end
    end

    local LowHop = function(region)
        region = region or "Singapore"
        local allServers = {}
        local cursor = ""

        for _ = 1, 5 do
            local url = "https://games.roblox.com/v1/games/" .. game.PlaceId .. "/servers/Public?sortOrder=Asc&limit=100"
            if cursor and cursor ~= "" then url = url .. "&cursor=" .. cursor end
            local ok, result = pcall(function()
                return HttpService:JSONDecode(game:HttpGet(url))
            end)
            if not ok or not result or type(result.data) ~= "table" then break end
            for _, v in ipairs(result.data) do
                table.insert(allServers, v)
            end
            cursor = result.nextPageCursor
            if not cursor then break end
        end

        for _, v in ipairs(allServers) do
            if type(v) == "table" and v.playing and v.maxPlayers and v.id then
                if v.playing < v.maxPlayers and v.playing <= 10 and v.region == region and v.id ~= game.JobId then
                    pcall(function()
                        game:GetService("ReplicatedStorage").__ServerBrowser:InvokeServer("teleport", v.id)
                    end)
                    task.wait(5)
                    return
                end
            end
        end

        for _, v in ipairs(allServers) do
            if type(v) == "table" and v.playing and v.maxPlayers and v.id then
                if v.playing < v.maxPlayers and v.playing <= 10 and v.id ~= game.JobId then
                    pcall(function()
                        game:GetService("ReplicatedStorage").__ServerBrowser:InvokeServer("teleport", v.id)
                    end)
                    task.wait(5)
                    return
                end
            end
        end
    end

    -- This external fetch/loadstring was unguarded - if the URL is briefly unreachable or rate
    -- limited, loadstring(...) returns nil and calling nil() as a function throws immediately,
    -- silently killing the ENTIRE rest of script init (nothing after this point ever ran on
    -- those runs: no FunctionsHandler, no UI, no TasksOrder loop). Decoder is already checked
    -- with `if Decoder and Decoder.decode then ...` everywhere it's used, so nil is safe here.
    local Decoder = select(2, pcall(function()
        return loadstring(game:HttpGet(
            "https://raw.githubusercontent.com/Dex-Bear/VxezeHubTrollKick/refs/heads/main/ngu.lua"))()
    end))
    if type(Decoder) ~= "table" then Decoder = nil end
    local TeleportService = game:GetService("TeleportService")
    local Players = game:GetService("Players")

    local loz = {
        EmGke1 = { [2753915549] = true, [85211729168715] = true },
        EmGke2 = { [4442272183] = true, [79091703265657] = true },
        EmGke3 = { [7449423635] = true, [100117331123089] = true },
        EmGkedacbiet = { [73902483975735] = true }
    }

    local okmngu = game.PlaceId
    local locplaceid = {}
    for _, bucu in pairs(loz) do
        if bucu[okmngu] then
            locplaceid = bucu
            break
        end
    end
    if not next(locplaceid) then
        locplaceid = { [okmngu] = true }
    end

    local DumaInFlight = false
    local DumaImpl
    local Duma = function(cailoz)
        if not cailoz then return false end
        -- 6 different quest states (Raid Castle, Cake Queen, Soul Reaper, Darkbeard, Rip Indra,
        -- Full Moon) can each independently task.spawn a Duma() hop with no shared cooldown -
        -- since the condition that triggers one usually stays true for several RefreshTasksData
        -- ticks in a row (the async HTTP lookup + teleport takes longer than 0.15s), multiple
        -- hops could get spawned back to back, stacking teleports and causing rapid, erratic
        -- server-jumping. Only allow one Duma hop in flight at a time.
        if DumaInFlight then return false end
        DumaInFlight = true
        local ok, result = pcall(function() return DumaImpl(cailoz) end)
        DumaInFlight = false
        return ok and result
    end
    local DumaRecentlyFailed = {}
    DumaImpl = function(cailoz)
        local concac = cailoz:gsub(" ", "%%20")
        local djt = "https://raw.banana-hub.xyz/api/data/recent?name=" .. concac .. "&limit=1000"
        local suc, res = pcall(function()
            return request({
                Url = djt,
                Method = "GET",
                Headers = { ["User-Agent"] = "BananaHub-Ngu", ["Content-Type"] = "application/json" }
            })
        end)
        if not suc or not res.Success then return false end
        local data = game:GetService("HttpService"):JSONDecode(res.Body)
        for _, v in pairs(data.data) do
            if v.Players and v.Players >= 2 and locplaceid[v.placeid] then
                local decoded_jobid = v.jobid
                if Decoder and Decoder.decode then
                    pcall(function()
                        decoded_jobid = Decoder.decode(v.jobid)
                        SetStatus("Decode JobId | " .. decoded_jobid)
                        print("Decode JobID: " .. decoded_jobid)
                    end)
                end
                -- The API result list doesn't refresh every tick, so blindly always picking the
                -- FIRST candidate meant a full server (Teleport Failed: Server is full) got
                -- retried again and again every single time this ran, doing nothing but
                -- spamming failed teleport attempts. Skip anything tried in the last 60s and
                -- fall through to the next candidate in the list instead.
                if decoded_jobid and decoded_jobid ~= "" and decoded_jobid ~= game.JobId
                    and (os.time() - (DumaRecentlyFailed[decoded_jobid] or 0)) > 60 then
                    DumaRecentlyFailed[decoded_jobid] = os.time()
                    pcall(function()
                        game:GetService("ReplicatedStorage").__ServerBrowser:InvokeServer("teleport", decoded_jobid)
                    end)
                    task.wait(3)
                    return true
                end
            end
        end
        return false
    end

    -- Duma()'s Server Browser teleports (Soul Reaper hop, Darkbeard/Rip Indra/Full Moon/Raid
    -- Castle/Cake Queen/Dough King hunts) hit a real Roblox "Teleport Failed - Server is full"
    -- system popup whenever the candidate server filled up between the API lookup and the actual
    -- teleport attempt - live-confirmed this blocks the whole game (nothing else visibly
    -- responds) until it's manually dismissed, and since these hops can retry repeatedly, the
    -- popup can reappear right after being closed. Auto-dismiss any CoreGui popup on sight
    -- instead of relying on a human (or a future script run) to click through it.
    task.spawn(function()
        while task.wait(1) do
            pcall(function()
                local popup = game.CoreGui:FindFirstChild("RobloxGui") and
                    game.CoreGui.RobloxGui:FindFirstChild("PopupFrame")
                local ok = popup and popup:FindFirstChild("PopupOKButton")
                if ok and popup.Visible then
                    firesignal(ok.MouseButton1Click)
                end
            end)
        end
    end)

    getgenv().NoClip = true
    game:GetService("RunService").Stepped:Connect(function()
        pcall(function()
            if not (game.Players.LocalPlayer.Character and game.Players.LocalPlayer.Character:FindFirstChild("Head") and game.Players.LocalPlayer.Character:FindFirstChild("HumanoidRootPart")) then return end
            -- BodyClip holds the character at zero velocity with infinite force every frame -
            -- while seated (e.g. VehicleSeat on a boat being driven by TweenBoat), that fights
            -- the seat's Weld trying to drag the character along with it, and that tug-of-war
            -- is what force-ejects the character from the seat. Skip the clip entirely while
            -- seated in anything, regardless of the NoClip toggle.
            local hum = game.Players.LocalPlayer.Character:FindFirstChildWhichIsA("Humanoid")
            local seated = hum and hum.SeatPart ~= nil
            if getgenv().NoClip and not seated then
                if not game.Players.LocalPlayer.Character.Head:FindFirstChild("BodyClip") then
                    local bv = Instance.new("BodyVelocity")
                    bv.Name = "BodyClip"
                    bv.Velocity = Vector3.new(0, 0, 0)
                    bv.MaxForce = Vector3.new(math.huge, math.huge, math.huge)
                    bv.P = 15000
                    bv.Parent = game.Players.LocalPlayer.Character.Head
                end
                for _, v in ipairs(game.Players.LocalPlayer.Character:GetDescendants()) do
                    if v:IsA("BasePart") then
                        v.CanCollide = false
                    end
                end
            else
                local clip = game.Players.LocalPlayer.Character.Head:FindFirstChild("BodyClip")
                if clip then clip:Destroy() end
                for _, v in ipairs(game.Players.LocalPlayer.Character:GetDescendants()) do
                    if v:IsA("BasePart") then
                        v.CanCollide = true
                    end
                end
            end
        end)
    end)

    local function WriteData(filename, content)
        if not isfolder('VxezeHub') then makefolder('VxezeHub') end
        writefile('VxezeHub/' .. filename, content)
    end

    -- Separate persisted-state folder (as opposed to VxezeHub/'s human-readable text dumps) -
    -- Melee_Data stores real state (JSON) that's read back on startup so mastery for melees
    -- you're not currently holding isn't lost on every script restart.
    local function WriteMeleeData(data)
        if not isfolder('Data_VxezeHub') then makefolder('Data_VxezeHub') end
        local ok, encoded = pcall(function() return game:GetService("HttpService"):JSONEncode(data) end)
        if ok then writefile('Data_VxezeHub/Melee_Data.json', encoded) end
    end

    local function ReadMeleeData()
        if not isfile('Data_VxezeHub/Melee_Data.json') then return {} end
        local ok, data = pcall(function()
            return game:GetService("HttpService"):JSONDecode(readfile('Data_VxezeHub/Melee_Data.json'))
        end)
        return (ok and type(data) == 'table') and data or {}
    end

    local _lblMainTask, _lblSubTask, _lblCurrencies, _lblMelees

    if not getgenv().Hide_UI then
        local TweenService = game:GetService("TweenService")
        local Lighting = game:GetService("Lighting")
        local player = game.Players.LocalPlayer
        local blur = Instance.new("BlurEffect", Lighting)
        blur.Size = 0
        TweenService:Create(blur, TweenInfo.new(0.5), { Size = 40 }):Play()
        task.delay(2, function() if blur then blur:Destroy() end end)

        local screenGui = Instance.new("ScreenGui", player:WaitForChild("PlayerGui"))
        screenGui.Name = "VxezeLoader"
        screenGui.ResetOnSpawn = false
        screenGui.IgnoreGuiInset = true

        local frame = Instance.new("Frame", screenGui)
        frame.Size = UDim2.new(1, 0, 1, 0)
        frame.BackgroundTransparency = 1

        local bg = Instance.new("Frame", frame)
        bg.Size = UDim2.new(1, 0, 1, 0)
        bg.BackgroundColor3 = Color3.fromRGB(5, 5, 10)
        bg.BackgroundTransparency = 1
        TweenService:Create(bg, TweenInfo.new(0.5), { BackgroundTransparency = 0.2 }):Play()

        local getTitleScale = function()
            local s = workspace.CurrentCamera.ViewportSize
            return math.clamp(math.min(s.X, s.Y) / 600, 0.3, 0.5)
        end

        local gradColor = ColorSequence.new({
            ColorSequenceKeypoint.new(0, Color3.fromRGB(0, 191, 255)),
            ColorSequenceKeypoint.new(0.5, Color3.fromRGB(100, 200, 255)),
            ColorSequenceKeypoint.new(1, Color3.fromRGB(200, 200, 200)),
        })

        local statusGradColor = ColorSequence.new({
            ColorSequenceKeypoint.new(0, Color3.fromRGB(160, 180, 220)),
            ColorSequenceKeypoint.new(0.5, Color3.fromRGB(190, 200, 230)),
            ColorSequenceKeypoint.new(1, Color3.fromRGB(210, 210, 220)),
        })

        local makeLabel = function(parent, pos, size)
            local t = Instance.new("TextLabel", parent)
            t.Font = Enum.Font.FredokaOne
            t.TextColor3 = Color3.fromRGB(255, 255, 255)
            t.TextStrokeColor3 = Color3.fromRGB(0, 100, 150)
            t.TextStrokeTransparency = 0.3
            t.TextTransparency = 1
            t.BackgroundTransparency = 1
            t.Position = pos
            t.Size = size
            t.TextScaled = true
            local g = Instance.new("UIGradient", t)
            g.Color = gradColor
            g.Rotation = 90
            return t
        end

        local makeStatusLabel = function(parent, pos, size)
            local t = Instance.new("TextLabel", parent)
            t.Font = Enum.Font.FredokaOne
            t.TextColor3 = Color3.fromRGB(230, 230, 250)
            t.TextTransparency = 1
            t.BackgroundTransparency = 1
            t.Position = pos
            t.Size = size
            t.TextScaled = true
            t.TextXAlignment = Enum.TextXAlignment.Center
            t.TextYAlignment = Enum.TextYAlignment.Center
            local g = Instance.new("UIGradient", t)
            g.Color = statusGradColor
            g.Rotation = 90
            return t
        end

        local logo = Instance.new("ImageLabel", frame)
        logo.Image = "rbxassetid://104363488394469"
        logo.BackgroundTransparency = 1
        logo.AnchorPoint = Vector2.new(0.5, 0.5)
        logo.Position = UDim2.new(0.5, 0, 0.3, 0)
        logo.Size = UDim2.new(getTitleScale(), 0, getTitleScale(), 0)
        logo.ImageTransparency = 1
        Instance.new("UIAspectRatioConstraint", logo).AspectRatio = 1
        TweenService:Create(logo, TweenInfo.new(0.6, Enum.EasingStyle.Quad, Enum.EasingDirection.Out),
            { ImageTransparency = 0 }):Play()

        local titleText = makeLabel(frame, UDim2.new(0.5, 0, 0.48, 0), UDim2.new(0.48, 0, 0.08, 0))
        titleText.Text = "Vxeze Hub"
        titleText.AnchorPoint = Vector2.new(0.5, 0.5)
        TweenService:Create(titleText, TweenInfo.new(0.6, Enum.EasingStyle.Quad, Enum.EasingDirection.Out),
            { TextTransparency = 0 }):Play()

        local statusText = makeStatusLabel(frame, UDim2.new(0.5, 0, 0.60, 0), UDim2.new(0.52, 0, 0.038, 0))
        statusText.Text = "Loading..."
        statusText.AnchorPoint = Vector2.new(0.5, 0.5)
        statusText.TextTransparency = 1
        _lblMainTask = statusText

        local subTaskText = makeStatusLabel(frame, UDim2.new(0.5, 0, 0.69, 0), UDim2.new(0.50, 0, 0.034, 0))
        subTaskText.Text = ""
        subTaskText.AnchorPoint = Vector2.new(0.5, 0.5)
        subTaskText.TextTransparency = 1
        _lblSubTask = subTaskText

        local currencyLabel = Instance.new("TextLabel", frame)
        currencyLabel.Font = Enum.Font.FredokaOne
        currencyLabel.TextColor3 = Color3.fromRGB(220, 220, 240)
        currencyLabel.TextTransparency = 0.1
        currencyLabel.BackgroundTransparency = 1
        currencyLabel.AnchorPoint = Vector2.new(0.5, 0.5)
        currencyLabel.Position = UDim2.new(0.5, 0, 0.79, 0)
        currencyLabel.Size = UDim2.new(0.78, 0, 0.034, 0)
        currencyLabel.TextXAlignment = Enum.TextXAlignment.Center
        currencyLabel.TextScaled = true
        currencyLabel.RichText = true
        currencyLabel.Text = ""
        _lblCurrencies = currencyLabel

        local meleeLabel = Instance.new("TextLabel", frame)
        meleeLabel.Font = Enum.Font.FredokaOne
        meleeLabel.TextColor3 = Color3.fromRGB(200, 180, 255)
        meleeLabel.TextTransparency = 0.1
        meleeLabel.BackgroundTransparency = 1
        meleeLabel.AnchorPoint = Vector2.new(0.5, 0.5)
        meleeLabel.Position = UDim2.new(0.5, 0, 0.88, 0)
        meleeLabel.Size = UDim2.new(0.70, 0, 0.034, 0)
        meleeLabel.TextXAlignment = Enum.TextXAlignment.Center
        meleeLabel.TextScaled = true
        meleeLabel.RichText = true
        meleeLabel.Text = ""
        _lblMelees = meleeLabel

        SetStatus = function(newStatus)
            if not newStatus or newStatus == "" then
                statusText.Text = ""
                return
            end
            if statusText.Text == newStatus then return end
            statusText.Text = newStatus
            if statusText.TextTransparency == 0 then
                local fadeOut = TweenService:Create(statusText, TweenInfo.new(0.15), { TextTransparency = 1 })
                fadeOut:Play()
                fadeOut.Completed:Wait()
            end
            TweenService:Create(statusText, TweenInfo.new(0.3, Enum.EasingStyle.Quad, Enum.EasingDirection.Out),
                { TextTransparency = 0 }):Play()
        end

        task.wait(0.2)
        TweenService:Create(statusText, TweenInfo.new(0.5, Enum.EasingStyle.Quad, Enum.EasingDirection.Out),
            { TextTransparency = 0 }):Play()

        local discordText = Instance.new("TextLabel", frame)
        discordText.Text = "dsc.gg/vxezehub"
        discordText.Font = Enum.Font.GothamMedium
        discordText.TextColor3 = Color3.fromRGB(150, 150, 170)
        discordText.TextSize = 14
        discordText.TextTransparency = 0.3
        discordText.BackgroundTransparency = 1
        discordText.AnchorPoint = Vector2.new(0, 1)
        discordText.Position = UDim2.new(0.02, 0, 0.98, 0)
        discordText.Size = UDim2.new(0.3, 0, 0.05, 0)
        discordText.TextXAlignment = Enum.TextXAlignment.Left
        discordText.TextScaled = true
        task.wait(0.8)
        TweenService:Create(discordText, TweenInfo.new(0.5, Enum.EasingStyle.Quad, Enum.EasingDirection.Out),
            { TextTransparency = 0 }):Play()

        if setclipboard then
            setclipboard("dsc.gg/vxezehub")
        elseif toclipboard then
            toclipboard("dsc.gg/vxezehub")
        end
    else
        SetStatus = function() end
    end

    function SetText(key, text)
        task.spawn(function()
            local lbl
            if key == 'Task1' or key == 'MainTextLabel' then
                if SetStatus then SetStatus(text) end
                lbl = _lblMainTask
            elseif key == 'Task2' then
                lbl = _lblSubTask
            elseif key == 'Currencies' then
                lbl = _lblCurrencies
            elseif key == 'Melees' then
                lbl = _lblMelees
            end
            if not lbl then return end
            if lbl.Text == text then return end
            local ts = game:GetService("TweenService")
            local info = TweenInfo.new(0.2, Enum.EasingStyle.Quad, Enum.EasingDirection.Out)
            ts:Create(lbl, info, { TextTransparency = 1 }):Play()
            task.wait(0.25)
            lbl.Text = text
            ts:Create(lbl, info, { TextTransparency = 0 }):Play()
        end)
    end

    local W = { Interface = {}, SetText = SetText, ToggleUI = function() end, BlurManager = {} }
    ScriptStorage = ScriptStorage or {}
    ScriptStorage.Interface = W

    if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Lock Fps"]["Enabled"] then
        task.spawn(function()
            loadstring([[
                local g = game
                local l = g:GetService("Lighting")
                -- QualityLevel = Level01 directly shrinks Roblox's own StreamingEnabled load
                -- radius, so most of the map (islands, mobs, NPCs) simply never streams in -
                -- every FindFirstChild("...") check throughout this script against workspace.Map
                -- then fails as if the map were deleted. Dropped that (and the destructive
                -- Decal/Texture :Destroy() below, which permanently removed those instances
                -- instead of just hiding them) - the rest of this block is purely cosmetic and
                -- doesn't remove or unload anything.
                g.DescendantAdded:Connect(function(o)
                    local c = o.ClassName
                    if c == "ParticleEmitter" or c == "Trail" then
                        o.Enabled = false
                    elseif c == "Explosion" then
                        o.BlastPressure = 0; o.BlastRadius = 0
                    elseif c == "Decal" or c == "Texture" then
                        o.Transparency = 1
                    end
                end)
                l.GlobalShadows = false; l.FogEnd = 9e9
                l.Brightness = 0; l.EnvironmentDiffuseScale = 0; l.EnvironmentSpecularScale = 0
                for _, v in ipairs(l:GetChildren()) do if v:IsA("PostEffect") then v.Enabled = false end end
                workspace.ClientAnimatorThrottling = Enum.ClientAnimatorThrottlingMode.Enabled
                workspace.InterpolationThrottling = Enum.InterpolationThrottlingMode.Enabled
                for i, v in pairs(g:GetDescendants()) do
                    if v:IsA("Part") or v:IsA("Union") or v:IsA("CornerWedgePart") or v:IsA("TrussPart") then
                        v.Material = "Plastic"; v.Reflectance = 0
                    elseif v:IsA("Decal") or v:IsA("Texture") then
                        v.Transparency = 1
                    elseif v:IsA("ParticleEmitter") then
                        v.Lifetime = NumberRange.new(0, 0)
                    elseif v:IsA("Trail") then
                        v.Enabled = false
                    elseif v:IsA("Fire") or v:IsA("SpotLight") or v:IsA("Smoke") then
                        v.Enabled = false
                    end
                end
                pcall(function() g.Lighting.LightingLayers:Destroy() end)
                pcall(function() g.Lighting.Sky:Destroy() end)
                g.Lighting.FogEnd = 9e9
            ]])()
        end)
    end

    if not isfile("fluent.lua") then
        writefile('fluent.lua', game:HttpGet("https://github.com/dawid-scripts/Fluent/releases/latest/download/main.lua"))
    end
    local _fluentLib = loadstring(readfile('fluent.lua'))()
    K = Instance.new('Animation')
    K.AnimationId = 'http://www.roblox.com/asset/?id=1elutruahuabuahd'
    getgenv().alert = function(a, h)
        pcall(function() _fluentLib:Notify({ Title = a or '', Content = h or '', Duration = 5 }) end)
    end
    function Report(msg)
        warn("[Report] " .. tostring(msg))
        pcall(function() alert("Report", tostring(msg)) end)
    end

    function LockAimPositionTo(pos)
        pcall(function()
            if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("HumanoidRootPart") then
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.lookAt(
                    LocalPlayer.Character.HumanoidRootPart.Position, pos)
            end
        end)
    end

    alert("_nguoitinhcuae Notify", "Endpoint reached")
    OldSessionTime = isfile('.tdif-' .. game.Players.LocalPlayer.Name) and
        tonumber(readfile(".tdif-" .. game.Players.LocalPlayer.Name)) or 0
    alert("Team Choose " .. getgenv().Team)
    repeat task.wait() until game.Players.LocalPlayer.Character
    task.spawn(function()
        game:GetService("Players").LocalPlayer.PlayerScripts:WaitForChild('NewIslandLOD', 9999):Destroy()
        game:GetService("Players")
            .LocalPlayer.PlayerScripts:WaitForChild('IslandLOD', 9999):Destroy()
    end)
    alert('WAIT LOAD KAITUN 1', 'ok')
    local J = { 'RawConstants', "Utilly", "QuestManager", 'SpawnRegionLoader', 'TweenController', "AttackController",
        'CombatController', 'FunctionsHandler', "Hooks", "Debug", "Hop", "Storage" }
    StartTick = tick()
    repeat
        task.wait()
    until SetText
    alert('WAIT LOAD KAITUN 2')
    SetText('MainTextLabel', 'Initalizing Script..')
    local J = "Rua_Hub/Blox_Fruit/Assets/"
    ScriptStorage = {
        IsInitalized = false,
        PlayerData = {},
        -- Pre-populated from disk so mastery for melees you aren't currently holding survives
        -- a script restart instead of resetting to empty (live tracking only ever sees the
        -- Tool you have equipped right now).
        Melees = ReadMeleeData(),
        CurrentMeleeData = {},
        Enemies = {},
        Tools = {},
        Backpack = {},
        IgnoreStoreFruits = {},
        Connections = { LocalPlayer = {} },
        Task = {},
        Tracebacks = {},
        TaskController = {},
        TracebackUpdater = {},
        Interface =
            W,
        NPCs = {},
        Map = {}
    }
    Players = game.Players
    LocalPlayer = Players.LocalPlayer
    Character = Players.LocalPlayer.Character
    Humanoid = Character:WaitForChild('Humanoid')
    HumanoidRootPart = Character:WaitForChild("HumanoidRootPart")
    PlayerGui = LocalPlayer:WaitForChild('PlayerGui', 10)
    Lighting = game:GetService('Lighting')
    Services = {}
    setmetatable(Services, { __index = function(J, J) return game:GetService(J) end })
    setmetatable(ScriptStorage.Enemies,
        {
            __index = function(J, J)
                return Services.Workspace.Enemies:FindFirstChild(J) or
                    Services.ReplicatedStorage:FindFirstChild(J)
            end
        })
    setmetatable(ScriptStorage.Map,
        {
            __index = function(J, J)
                return Services.Workspace.Map:FindFirstChild(J) or
                    Services.Workspace:FindFirstChild(J)
            end
        })
    setmetatable(ScriptStorage.Tools,
        {
            __index = function(J, J)
                return LocalPlayer.Character:FindFirstChild(J) or
                    LocalPlayer.Backpack:FindFirstChild(J)
            end
        })
    setmetatable(ScriptStorage.NPCs,
        {
            __index = function(J, J)
                if not J then return end; return workspace.NPCs:FindFirstChild(J) or
                    game.ReplicatedStorage.NPCs:FindFirstChild(J)
            end
        })
    function CreateTraceback(J, W)
        table.insert(ScriptStorage.Tracebacks,
            (GetCurrentDateTime() .. ' ( ' .. DispTime(os.time() - os.time(), true) .. ' ) after execution | ' .. J .. " | " .. W))
    end

    _whLastSent = 0
    _whLastTask = ""

    function SetTask(J, W)
        if ScriptStorage.Task[J] == W then return end
        local a = { MainTask = "Task1", SubTask = 'Task2' }
        if a[J] then if SetText then SetText(a[J], J .. ' : ' .. W) end end
        ScriptStorage.Task[J] = W
        ScriptStorage.Task[J .. '-d'] = os.time()
        if J == "MainTask" and W ~= _whLastTask and os.time() - _whLastSent > 180 then
            _whLastTask = W
            _whLastSent = os.time()
            if SendWebhook then task.spawn(function() SendWebhook(W) end) end
        end
    end

    Remotes = {}
    BindedMeleeNPCNames = {
        BlackLeg = 'Dark Step Teacher',
        Electro = "Mad Scientist",
        FishmanKarate =
        "Water Kung-fu Teacher",
        DeathStep = "Phoeyu, the Reformed",
        SharkmanKarate = 'Sharkman Teacher',
        DragonTalon =
        "Uzoth",
        ElectricClaw = 'Previous Hero',
        Godhuman = "Ancient Monk"
    }
    local J = {}
    setmetatable(Remotes, {
        __index = function(W, W)
            if W ~= 'CommF_' then
                return Services.ReplicatedStorage.Remotes[W]
            end
            local W = {
                InvokeServer = function(a, ...)
                    local a, h = ...
                    if string.find(a, "Buy") == 1 and not h then
                        local h = string.gsub(a, 'Buy', "")
                        if BindedMeleeNPCNames then
                            if table.find(J, h) then
                                local a = ScriptStorage.NPCs[BindedMeleeNPCNames[h]]
                                if a then
                                    local h = a.WorldPivot
                                    if CaculateDistance(h) > 10 then
                                        repeat
                                            task.wait(1)
                                            TweenController.Create(h.Position)
                                        until CaculateDistance(h) < 10
                                        task.wait(3)
                                        Services.ReplicatedStorage.Remotes.CommF_:InvokeServer(...)
                                    end
                                end
                            end
                        end
                    end
                    return Services.ReplicatedStorage.Remotes.CommF_:InvokeServer(...)
                end
            }
            return W
        end
    })
    Tasks = {}
    function AwaitUntilPlayerLoaded(W, a)
        repeat task.wait() until W.Character
        W.Character:WaitForChild('Humanoid')
        repeat task.wait() until W.Character.Humanoid.Health > 0
    end

    function AddPoint()
        local W = {}
        local a
        for h, h in LocalPlayer.Data.Stats:GetChildren() do
            if h and h:FindFirstChild('Level') then W[h.Name] = h.Level.Value end
        end
        if W.Defense < MaxLevel and (W.Defense < (ScriptStorage.PlayerData.Level / 80) or MaxLevel - W.Melee < 100) then
            a = 'Defense'
        elseif W.Melee < MaxLevel then
            a = "Melee"
        else
            a = 'Sword'
        end
        Remotes.CommF_:InvokeServer("AddPoint", a, 999)
    end

    local W = { Currencies = { Level = "#00FF48", Beli = "#FF7800", Fragments = "#6C00FF" }, Races = {} }
    function RefreshPlayerData()
        -- "RaceLevel" is deliberately excluded here: the raw Data.RaceLevel field is not the
        -- authoritative race-evolution stage (it's just 0 for everyone) - RefreshRace() computes
        -- the real V1-V4 stage via the Alchemist/Wenlocktoad remotes and RaceTransformed check.
        -- Copying the raw field every 1.5s here was clobbering that computed value back to 0
        -- almost immediately after every RefreshRace() call, so EvoRace's "RaceLevel ~= 1" gate
        -- basically never saw a stable value and race evolution never actually progressed.
        for a, a in LocalPlayer.Data:GetChildren() do
            if a.Name ~= "RaceLevel" then
                pcall(function() ScriptStorage.PlayerData[a.Name] = a.Value end)
            end
        end

        local level     = Price(ScriptStorage.PlayerData.Level or 0)
        local beli      = Price(ScriptStorage.PlayerData.Beli or 0)
        local frags     = Price(ScriptStorage.PlayerData.Fragments or 0)

        local fruitName = tostring(ScriptStorage.PlayerData.DevilFruit)
        fruitName       = (type(fruitName) == "string" and fruitName ~= "" and fruitName ~= "None") and fruitName or
            "None"
        local raceName  = tostring(ScriptStorage.PlayerData.Race or "None")
        local raceLevel = ScriptStorage.PlayerData.RaceLevel or 1

        local a         = string.format(
            '<font color="#7DDFC3">Level: %s</font> | <font color="#A8C8F0">Beli: %s</font> | <font color="#C4AAFF">Fragments: %s</font> | <font color="#7EC8E3">Fruits: %s</font> | <font color="#F0B8D0">Race: %s (V%d)</font>',
            level, beli, frags, fruitName, raceName, raceLevel
        )
        if ScriptStorage.Interface then SetText('Currencies', a) end

        WriteData('player.txt', string.format(
            "Level=%s\nBeli=%s\nFragments=%s\nFruits=%s\nRace=%s\nRaceLevel=V%d\n",
            tostring(ScriptStorage.PlayerData.Level or 0),
            tostring(ScriptStorage.PlayerData.Beli or 0),
            tostring(ScriptStorage.PlayerData.Fragments or 0),
            fruitName, raceName, raceLevel
        ))
    end

    function RefreshRace()
        local W, a = Remotes.CommF_:InvokeServer('Alchemist', "1"), Remotes.CommF_:InvokeServer("Wenlocktoad", "1")
        ScriptStorage.PlayerData.RaceLevel = 1
        if LocalPlayer.Character:FindFirstChild("RaceTransformed") then
            ScriptStorage.PlayerData.RaceLevel = 4
        elseif a == -2.0 then
            ScriptStorage.PlayerData.RaceLevel = 3
        elseif W == -2.0 then
            ScriptStorage.PlayerData.RaceLevel = 2
        end
    end

    function RefreshInventory()
        ScriptStorage.Backpack2 = {}
        for W, W in Remotes.CommF_:InvokeServer('getInventory') do ScriptStorage.Backpack2[W.Name] = W end
        ScriptStorage.Backpack = ScriptStorage.Backpack2
        local _idump = ''
        for k, _ in pairs(ScriptStorage.Backpack) do _idump = _idump .. k .. '\n' end
        WriteData('inventory.txt', _idump)
    end

    function ResearchMoves(W)
        if W and tostring(W) == 'V' then
            if ScriptStorage.Connections.BurstCheck then
                ScriptStorage.Connections.BurstCheck:Disconnect()
                task.wait(1)
            end
            ScriptStorage.Connections.BurstCheck = W.Cooldown:GetPropertyChangedSignal("AbsoluteSize"):Connect(function()
                if EnablingBurstDebounce and os.time() - EnablingBurstDebounce < 10 then return end
                local a = W.Cooldown.AbsoluteSize.X
                if a < 3 then
                    EnablingBurstDebounce = os.time()
                    task.wait(5)
                    SendKey('V', 0)
                end
            end)
        end
    end

    function CheckMeleeBurstMove(W)
        if W.Name == "Black Leg" or W.Name == "Death Step" then
            local a = PlayerGui.Main.Skills:WaitForChild(W.Name, 9)
            ResearchMoves(a:WaitForChild("V"))
        end
    end

    function RefreshMelees(W)
        local a = ''
        for h, X in ScriptStorage.Melees do a = a .. h .. ": " .. X .. " " end
        a = a == '' and '[0]' or a
        if W then return a end
        if ScriptStorage.Interface then SetText('Melees', a) end
        -- Only persist when there's actually a Melee to report - matches the guard the rest
        -- of the hub uses before calling WriteData (see player.txt/inventory.txt above).
        if a ~= '[0]' then
            WriteData('melee.txt', a)
            WriteMeleeData(ScriptStorage.Melees)
        end
    end

    -- Real field for mastery is the Tool's "Level" IntValue (confirmed live via Dex/getInventory
    -- probe - melees never surface through getInventory, "Mastery" isn't a real property name).
    function AlertMeleeMastery(W, a)
        alert(W, "Mastery: " .. tostring(a))
    end

    function MeleeCheck(W)
        if W and typeof(W) == "Instance" and W:IsA("Tool") then
            if W.ToolTip == "Melee" then
                if ScriptStorage.Connections.Melees then ScriptStorage.Connections.Melees:Disconnect() end
                ScriptStorage.CurrentMeleeData.Name = W.Name
                pcall(function() ScriptStorage.Connections.Melees:Destroy() end)
                local levelObj = W:FindFirstChild("Level")
                if not levelObj then
                    task.spawn(function()
                        levelObj = W:WaitForChild("Level", 5)
                        if not levelObj then return end
                        ScriptStorage.Connections.Melees = levelObj.Changed:Connect(function(a)
                            ScriptStorage.Melees[W.Name] = a
                            RefreshMelees()
                        end)
                        ScriptStorage.Melees[W.Name] = levelObj.Value
                        RefreshMelees()
                        AlertMeleeMastery(W.Name, levelObj.Value)
                    end)
                else
                    ScriptStorage.Connections.Melees = levelObj.Changed:Connect(function(a)
                        ScriptStorage.Melees[W.Name] = a
                        RefreshMelees()
                    end)
                    ScriptStorage.Melees[W.Name] = levelObj.Value
                    RefreshMelees()
                    AlertMeleeMastery(W.Name, levelObj.Value)
                end
            elseif string.find(tostring(W), "Fruit") then
                task.spawn(function()
                    if table.find(ScriptStorage.IgnoreStoreFruits, W:GetAttribute('OriginalName')) then return end
                    local a = Remotes.CommF_:InvokeServer("StoreFruit", W:GetAttribute("OriginalName"), W)
                end)
            end
        end
    end

    SetText('MainTextLabel', 'Refreshing Player Data')
    MeleeCheck(LocalPlayer.Character:FindFirstChildOfClass('Tool'))
    RefreshPlayerData()
    function RegisterLocalPlayerEventsConnection()
        task.spawn(function()
            task.wait(6)
            if LocalPlayer.Character:FindFirstChild('HasBuso') then return end
            Remotes.CommF_:InvokeServer("Buso")
        end)
        for W, W in ScriptStorage.Connections.LocalPlayer do pcall(function() W:Disconnect() end) end
        AwaitUntilPlayerLoaded(LocalPlayer)
        LocalPlayer:SetAttribute("IsAvailable", true)
        ScriptStorage.Connections.LocalPlayer["HealthCheck"] = LocalPlayer.Character:WaitForChild("Humanoid")
            :GetPropertyChangedSignal("Health"):Connect(function()
                local W = LocalPlayer.Character.Humanoid.Health
                LocalPlayer:SetAttribute("IsAvailable", W > 10)
                ScriptStorage.LocalPlayerHealth = W
            end)
        ScriptStorage.Connections.LocalPlayer['Melee'] = LocalPlayer.Character.ChildAdded:Connect(MeleeCheck)
        ScriptStorage.Connections.LocalPlayer['Fruit'] = LocalPlayer.Backpack.ChildAdded:Connect(MeleeCheck)
        table.foreach(LocalPlayer.Backpack:GetChildren(), function(W, W) MeleeCheck(W) end)
        LastIdleCheck = os.time()
        ScriptStorage.Connections.LocalPlayer.PositionChecker = LocalPlayer.Character.HumanoidRootPart
            :GetPropertyChangedSignal('CFrame'):Connect(function()
                if os.time() == LastIdleCheck then return end
                LastIdleCheck = os.time()
                if oldPos then
                    if (LocalPlayer.Character.HumanoidRootPart.CFrame.p - oldPos).magnitude < 2 then return end
                end
                oldPos = (LocalPlayer.Character.HumanoidRootPart.CFrame.p)
                LastIdling = os.time()
            end)
        local W = LocalPlayer.Data:WaitForChild('Points')
        ScriptStorage.Connections.LocalPlayer.PointConnection = W:GetPropertyChangedSignal('Value'):Connect(function()
            local W = LocalPlayer.Data:WaitForChild('Points')
            if OldPointValue == W then return end
            OldPointValue = W
            AddPoint()
        end)
    end

    RegisterLocalPlayerEventsConnection(LocalPlayer)
    game.Players.LocalPlayer.CharacterAdded:Connect(function(W)
        RegisterLocalPlayerEventsConnection(LocalPlayer)
    end)
    task.spawn(function()
        task.wait(3)
        if LocalPlayer.Character:FindFirstChild("HasBuso") then return end
        Remotes.CommF_:InvokeServer("Buso")
    end)
    -- Internal names/ids here (Black Leg/BlackLeg, Electro, Fishman Karate/FishmanKarate,
    -- Dragon Claw/DragonClaw) are what the game's actual remotes still use even though the
    -- in-game DISPLAY names were renamed to Dark Step/Electric/Water Kung Fu/Dragon Breath
    -- (confirmed via decompile: InvokeServer("BuyBlackLeg"/"BuyElectro"/"BuyFishmanKarate") and
    -- InvokeServer("BlackbeardReward", "DragonClaw", ...)) - order requested: all 4 V1 styles,
    -- then Death Step + Sharkman Karate, then Superhuman, then the rest of V2, then Godhuman.
    MeleesTable = { "Black Leg", 'Electro', "Fishman Karate", "Dragon Claw", 'Death Step', "Sharkman Karate",
        "Superhuman", 'Electric Claw', 'Dragon Talon', "Godhuman", "SanguineArt" }
    MeleesId = { 'BlackLeg', "Electro", 'FishmanKarate', "DragonClaw", 'DeathStep', "SharkmanKarate",
        "Superhuman", "ElectricClaw", 'DragonTalon', 'Godhuman', "SanguineArt" }
    MeleePrices = {
        ["Black Leg"] = {
            Price = { Beli = 150000 },
            Id = "BlackLeg",
            NextLevelRequirement = 400,
            position = CFrame.new(),
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee("BlackLeg", W, 'Dark Step Teacher')
            end
        },
        ['Electro'] = {
            Price = { Beli = 500000 },
            Id = 'Electro',
            NextLevelRequirement = 400,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee('Electro', W, "Mad Scientist")
            end
        },
        ['Fishman Karate'] = {
            Price = { Beli = 750000 },
            NextLevelRequirement = 400,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee('FishmanKarate', W, 'Water Kung-fu Teacher')
            end
        },
        ['Dragon Claw'] = {
            Price = { Fragments = 1500 },
            NextLevelRequirement = 400,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee("DragonClaw", W, "Sabi")
            end
        },
        ["Superhuman"] = {
            Price = { Beli = 3000000 },
            NextLevelRequirement = 400,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee("Superhuman", W, "Martial Arts Master")
            end
        },
        ["Death Step"] = {
            Price = { Beli = 2500000, Fragments = 5000 },
            NextLevelRequirement = 400,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee("DeathStep", W, "Phoeyu, the Reformed")
            end
        },
        ['Sharkman Karate'] = {
            Price = { Beli = 2500000, Fragments = 5000 },
            NextLevelRequirement = 400,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee('SharkmanKarate', W, 'Sharkman Teacher')
            end
        },
        ['Electric Claw'] = {
            Price = { Beli = 2500000, Fragments = 5000 },
            NextLevelRequirement = 400,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee("ElectricClaw", W, 'Previous Hero')
            end
        },
        ['Dragon Talon'] = {
            Price = { Beli = 2500000, Fragments = 5000 },
            NextLevelRequirement = 400,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee("DragonTalon", W, 'Uzoth')
            end
        },
        ["Godhuman"] = {
            Price = { Beli = 5000000, Fragments = 5000 },
            NextLevelRequirement = 350,
            Requirements = function() return true end,
            Buy = function(
                W)
                return BuyMelee("Godhuman", W, 'Ancient Monk')
            end
        }
    }
    DropItemData = {
        ['Buddy Sword'] = { Sea = 3, Level = 1500, Boss = "Cake Queen" },
        ['Canvander'] = { Sea = 3, Level = 1500, Boss = "Beautiful Pirate" },
        ['Twin Hooks'] = { Sea = 3, Level = 1500, Boss = 'Captain Elephant' },
        ["Venom Bow"] = { Sea = 3, Level = 1500, Boss = "Hydra Leader" }
    }
    GodhumanMaterials = {
        ['Fish Tail'] = { 20, 3, { "Fishman Raider", "Fishman Captain" }, { 'DeepForestIsland3', 1, 1775, 'Turtle Adventure Quest Giver' } },
        ['Dragon Scale'] = { 10, 3, { "Dragon Crew Warrior", "Dragon Crew Archer" }, { 'DragonCrewQuest', 1, 1575, 'Dragon Crew Quest Giver' } },
        ["Magma Ore"] = { 20, 2, { 'Magma Ninja' }, { "FireSideQuest", 1, 1100, "Fire Quest Giver" } },
        ["Mystic Droplet"] = { 10, 2, { 'Sea Soldier', 'Water Fighter' }, { 'ForgottenQuest', 2, 1425, 'Forgotten Quest Giver' } }
    }
    SeaIndexes = { "Main", "Dressrosa", "Zou" }
    -- Ordered by dependency/urgency:
    -- 1) cheap opportunistic actions that never conflict with anything (fruit dealer window,
    --    exp/drops already on the ground - single fireproximityprompt calls, not sustained
    --    grinding, and vanish/rotate if ignored, so they always go first);
    -- 2) time-limited events (a raid's kill window is short and CursedDualKatana's own Good
    --    trial 2 depends on catching one - BossesTask/CollectBerries sitting above this could
    --    eat the whole window before the raid tasks ever got a turn);
    -- 3) the one-time story/quest chain in its natural unlock order (Sea progression -> Sea1
    --    swords -> Sea2/Sea3 puzzles -> Yama/Tushita mastery -> CDK, which needs both -> Soul
    --    Guitar -> Race Evolution V1->V2->V3, which needs Colosseum's Warrior Helmet first);
    -- 4) open-ended grinding filler (berries, generic/special bosses, melee mastery/leveling)
    --    last - farming is always available later with no downside to delaying it, so it
    --    should yield to anything above it rather than block it. CollectBerries specifically
    --    sits right after SoulGuitar per an explicit ask: it was previously ranked above CDK/
    --    SoulGuitar and kept winning priority over them whenever a berry was nearby, stalling
    --    quest progress - now CDK/SoulGuitar always get first pick, berries only get picked up
    --    once neither has anything left to do this tick.
    TasksOrder = {
        "SniperFruit",
        "ExpRedeem",
        "CollectDrops",
        "UtillyItemsActivitation",
        "PirateRaid",
        "RaidController",
        "SeaTravel",
        "Pole",
        "Saber",
        "SecondSeaPuzzle",
        "ColosseumPuzzle",
        "Trevor",
        "ThirdSeaPuzzle",
        "Yama",
        "Tushita",
        "CursedDualKatana",
        "SoulGuitar",
        "CollectBerries",
        "EvoRace",
        "Wenlocktoad",
        "BossesTask",
        "SpecialBossesTask",
        "LevelFarm"
    }
    MaxLevel = 2800
    placeId = game.PlaceId
    if placeId == 85211729168715 or placeId == 2753915549 then
        Sea = 'Main'
        SeaIndex = 1
    elseif placeId == 79091703265657 or placeId == 4442272183 then
        Sea = "Dressrosa"
        SeaIndex = 2
    elseif placeId == 100117331123089 or placeId == 7449423635 then
        Sea = "Zou"
        SeaIndex = 3
    end
    -- Was a static "Portals = (...)[SeaIndex]" snapshot taken ONCE at script init - never
    -- updated again after any later sea travel, and Sea 3's entry was just {} (empty), so
    -- GetPortal had zero usable portals there even when it should have run. Now a proper
    -- per-sea table (PortalsBySea[SeaIndex]) looked up fresh on every GetPortal call instead.
    -- Sea 3 coordinates ported from the same data set already used successfully in
    -- DracoKaitun.lua's own getPortal for this same place (7449423635).
    PortalsBySea = {
        { Vector3.new(-7894.6201171875, 5545.49169921875, -380.246346191406), Vector3.new(-4607.82275390625, 872.5422973632812, -1667.556884765625), Vector3.new(61163.8515625, 11.759522438049316, 1819.7841796875), Vector3.new(3876.280517578125, 35.10614013671875, -1939.3201904296875) },
        { Vector3.new(-288.46246337890625, 306.130615234375, 597.9988403320312), Vector3.new(2284.912109375, 15.152046203613281, 905.48291015625), Vector3.new(923.21252441406, 126.9760055542, 32852.83203125), Vector3.new(-6508.5581054688, 89.034996032715, -132.83953857422) },
        { Vector3.new(-5058.7, 314.5, -3155.8), Vector3.new(5756.8, 610.4, -253.9), Vector3.new(-12463.8, 374.9, -7523.7), Vector3.new(28282.5, 14896.8, 105.1), Vector3.new(-11993.5, 334.7, -8844.1), Vector3.new(5314.5, 25.4, -125.9) }
    }
    BossesOrder = { "Awakened Ice Admiral", "Tide Keeper", 'Deandre', "Urban", "Diablo", 'Soul Reaper', 'Cake Prince' }
    BossesOrderLevel = {
        ['Awakened Ice Admiral'] = 700,
        ['Tide Keeper'] = 700,
        ['Deandre'] = 1500,
        ['Urban'] = 1500,
        ['Diablo'] = 1500,
        ["Cake Prince"] = 1500,
        ['Soul Reaper'] = 1500
    }
    BossesOrderWL = {
        ["Deandre"] = 1500,
        ["Urban"] = 1500,
        ["Diablo"] = 1500,
        ['Cake Prince'] = 1500,
        ['Don Swan'] = 1100,
        ["Awakened Ice Admiral"] = 700,
        ['Tide Keeper'] = 700
    }
    SpecialBossesOrder = { ["Core"] = 700, ['Darkbeard'] = 700 }
    BlankTablets = { "Segment6", 'Segment2', 'Segment8', "Segment9", 'Segment5' }
    Trophy = {
        ["Segment1"] = "Trophy1",
        ["Segment3"] = "Trophy2",
        ['Segment4'] = "Trophy3",
        ['Segment7'] = "Trophy4",
        ["Segment10"] = "Trophy5"
    }
    Pipes = {
        ['Part1'] = 'Really black',
        ['Part2'] = 'Really black',
        ["Part3"] = "Dusty Rose",
        ['Part4'] = "Storm blue",
        ['Part5'] = 'Really black',
        ['Part6'] = "Parsley green",
        ["Part7"] = 'Really black',
        ["Part8"] = "Dusty Rose",
        ["Part9"] = 'Really black',
        ['Part10'] = 'Storm blue'
    }
    function GenerateUUID()
        local W = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'
        return string.gsub("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx", '[xy]', function(W)
            local W = (Idx == 'x') and math.random(0, 0xf) or math.random(8, 0xb)
            return string.format('%x', W)
        end)
    end

    function CheckIsPlayerAlive(W)
        W = W or LocalPlayer; return W and W.Character and W.Character.Humanoid and W.Character.HumanoidRootPart and
            W.Character.Head and W.Character.Humanoid.Health > 0
    end

    function ConvertTo(W, a) return W.new(a.X, a.Y, a.Z) end

    function CaculateDistance(W, a)
        if not W then return 0 end
        a = a or game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame
        local h, X = ConvertTo(Vector3, W), ConvertTo(Vector3, a)
        return (h - X).magnitude
    end

    -- CollectionService:GetTagged("_ChestTagged") includes both real, streamed-in chests
    -- (under Workspace.Map) AND unstreamed template chests sitting in
    -- ReplicatedStorage.Unloaded.Details waiting to be cloned in when a region loads - those
    -- templates sit at a meaningless default CFrame and were getting picked as "0 studs away",
    -- causing the tween to target nothing. IsDescendantOf(workspace) filters those out. No
    -- distance cap here on purpose - farm chests server-wide instead of idling when the
    -- closest real one just happens to be far away.
    function GetNearestChest()
        local w, D = nil, math.huge
        local h = game:GetService("CollectionService"):GetTagged("_ChestTagged")
        for k = 1, #h do
            local X = h[k]
            if X and X:IsDescendantOf(workspace) and not X:GetAttribute("IsDisabled") then
                local y = CaculateDistance(X:GetPivot())
                if y < D then D, w = y, X end
            end
        end
        return w, D
    end

    -- "Brigade" boat id differs by team - PirateBrigade for Pirates, MarineBrigade for
    -- Marines - and the spawned Workspace.Boats model is named to match, so every boat lookup
    -- (buy id, VehicleSeat.Parent.Name check, TweenBoat target) must resolve this dynamically
    -- instead of assuming one faction.
    function GetMyBoatName()
        local W = LocalPlayer.Team
        return (W and W.Name == "Pirates") and "PirateBrigade" or "MarineBrigade"
    end

    -- Originally ported from the user's "Function TweenBoat.lua" reference as a hidden anchored
    -- "Root" proxy part, synced onto the real (unanchored, physically simulated) VehicleSeat's
    -- CFrame every frame by a background loop. Live-confirmed that pattern reliably ejects the
    -- seated humanoid within a second or two of the cruise starting - hard-setting CFrame on an
    -- unanchored physics part every frame fights the seat weld's own physics resolution and pops
    -- it loose, regardless of how smooth the underlying Tween driving the proxy is. Anchoring the
    -- VehicleSeat itself and Tweening it directly instead makes the whole ride fully kinematic -
    -- no physics contention, so a seated humanoid's weld just rides along with it - and removes
    -- the need for the proxy part/background sync loop entirely.
    function TweenBoat(D)
        local w = {}
        local X = workspace.Boats:FindFirstChild(GetMyBoatName())
        local h = X and X:FindFirstChild("VehicleSeat")
        if not h then return w end
        h.Anchored = true
        local cruiseD = CFrame.new(D.Position.X, 150, D.Position.Z)
        local L = (h.Position - cruiseD.Position).Magnitude
        local cruiseTween = Services.TweenService:Create(h, TweenInfo.new(L / 300, Enum.EasingStyle.Linear),
            { CFrame = cruiseD })
        local landTween
        local conn
        conn = cruiseTween.Completed:Connect(function()
            landTween = Services.TweenService:Create(h, TweenInfo.new(1, Enum.EasingStyle.Linear), { CFrame = D })
            landTween:Play()
        end)
        cruiseTween:Play()
        w.Stop = function()
            if conn then conn:Disconnect() end
            pcall(function() cruiseTween:Cancel() end)
            pcall(function() if landTween then landTween:Cancel() end end)
            -- Deliberately left Anchored=true here - un-anchoring let the boat drift off with the
            -- waves the moment a Sea Beast was spotted (Stop() fires immediately on sighting, see
            -- the Shark/Fishman beast-found branch near line 2083), so by the time the beast
            -- despawned/died to someone else, the boat had wandered far from the patrol point and
            -- the whole sail had to start over. Parking it exactly where it stopped makes
            -- reboarding after a fight trivial instead.
        end
        return w
    end

    function DispTime(W, a)
        W = tonumber(W)
        if not W then return "[err]" end
        local h = math.floor(W / 86400)
        local X = math.floor(math.fmod(W, 86400) / 3600)
        local w = math.floor(math.fmod(W, 3600) / 60)
        local D = math.floor(math.fmod(W, 60))
        if a then return (h .. "day, " .. X .. "hrs, " .. w .. "min, " .. D .. 'sec.') end
        return (h .. 'day, ' .. X .. "hrs.")
    end

    function GetCurrentDateTime()
        local W = os.date("*t")
        local a = W.hour
        local h = W.min
        local X = W.day
        local w = W.month
        local D = W.year
        local y = W.wday
        local W = string.format('%02d:%02d ', a, h)
        local a = { 'Sun', "Mon", 'Tue', "Wed", 'Thu', "Fri", 'Sat' }
        local h = a[y]
        local a = { "Jan", "Feb", "Mar", 'Apr', "May", 'Jun', "Jul", 'Aug', 'Sep', "Oct", 'Nov', "Dec" }
        local y = a[w]
        local a = string.format('%s, %s %d %d', h, y, X, D)
        return W .. a
    end

    function RandomArguments(...)
        local W = { ... }; return W[math.random(0, #W)]
    end

    function RoundVector3Down(W)
        return Vector3.new(math.floor(W.X / 10) * 10, math.floor(W.Y / 10) * 10,
            math.floor(W.Z / 10) * 10)
    end

    local circleAngle = 0
    CaculateCircreDirection = function(a)
        circleAngle = (circleAngle + 20) % 360
        local radius = 40
        local radian = math.rad(circleAngle)
        local x = math.cos(radian) * radius
        local z = math.sin(radian) * radius
        local h = a + Vector3.new(x, 0, z)
        return CFrame.new(RoundVector3Down(h.Position))
    end
    function GetMonAsSortedRange()
        local W = {}
        table.foreach(Services.Workspace.Enemies:GetChildren(), function(a, a)
            if a and a:FindFirstChild('Humanoid') and a.Humanoid:IsA("Humanoid") and a:FindFirstChild("HumanoidRootPart") and a.Humanoid.Health > 0 then
                table.insert(W, a)
            end
        end)
        -- Sea Beasts spawn into their own Workspace.SeaBeasts folder, not Workspace.Enemies -
        -- without this they're simply invisible to CombatController.Attack no matter what name
        -- is searched for.
        local SeaBeasts = Services.Workspace:FindFirstChild("SeaBeasts")
        if SeaBeasts then
            table.foreach(SeaBeasts:GetChildren(), function(a, a)
                if a and a:FindFirstChild('Humanoid') and a.Humanoid:IsA("Humanoid") and a:FindFirstChild("HumanoidRootPart") and a.Humanoid.Health > 0 then
                    table.insert(W, a)
                end
            end)
        end
        table.foreach(game.ReplicatedStorage:GetChildren(), function(a, a)
            if a and a:FindFirstChild('Humanoid') and a.Humanoid:IsA("Humanoid") and a:FindFirstChild("HumanoidRootPart") and a.Humanoid.Health > 0 then
                table.insert(W, a)
            end
        end)
        table.sort(W,
            function(a, h)
                return CaculateDistance(a.HumanoidRootPart.CFrame) <
                    CaculateDistance(h.HumanoidRootPart.CFrame)
            end)
        return W
    end

    function GetMeleeIdByName(W) for a, h in MeleesTable do if h == W then return MeleesId[a] end end end

    function getpos(W)
        for a, a in game:GetService("ReplicatedStorage").NPCs:GetChildren() do
            if a.Name == W then
                return a
                    .HumanoidRootPart.CFrame
            end
        end
        for a, a in workspace.NPCs:GetChildren() do if a.Name == W then return a.HumanoidRootPart.CFrame end end
    end

    function BuyMelee(W, a)
        if W == "DragonClaw" and workspace.NPCs:FindFirstChild('Sabi') then
            if a then
                if type(Remotes.CommF_:InvokeServer("BlackbeardReward", 'DragonClaw', '1') == 1) == "number" and Remotes.CommF_:InvokeServer('BlackbeardReward', 'DragonClaw', '1') == 1 == 1 and not table.find(J, W) then
                    table.insert(J, W)
                end
                return Remotes.CommF_:InvokeServer("BlackbeardReward", "DragonClaw", "1")
            end
            return Remotes.CommF_:InvokeServer('BlackbeardReward', "DragonClaw", '2')
        end
        if a then
            local a = Remotes.CommF_:InvokeServer('Buy' .. W, true)
            if type(a) == 'number' and not table.find(J, W) then table.insert(J, W) end
            return a == 1
        end
        return Remotes.CommF_:InvokeServer("Buy" .. W)
    end

    function SendKey(J, W)
        (function()
            game:GetService("VirtualInputManager"):SendKeyEvent(true, J, false, game)
            task.wait(W)
            game:GetService('VirtualInputManager'):SendKeyEvent(false, J, false, game)
        end)()
    end

    function FruitIdToName(J)
        local W = string.match(J, "((%u)[^%-]+)$")
        return W .. ' Fruit'
    end

    function Split(J, W)
        if W == nil then W = "%s" end
        local a = {}
        for h in string.gmatch(J, '([^' .. W .. ']+)') do table.insert(a, h) end
        return a
    end

    function FruitNameToId(J)
        local W = Split(J)[1]
        return W .. '-' .. W
    end

    local J = { CurrentLevel = 3, DoubleQuest = true, TripleQuest = true, CurrentQuests = {}, BlacklistedQuestIds = { BartiloQuest = 1, CitizenQuest = 1, Trainees = 1, MarineQuest = 1, ImpelQuest = 1 } }
    local W = require(game.ReplicatedStorage.GuideModule).Data.NPCList
    repeat task.wait() until game.Players.LocalPlayer.DataLoaded and ScriptStorage
    J.Quests = require(game.ReplicatedStorage.Quests)
    function J.Set(W, a, h) W[a] = h end

    function J.RefreshQuest(W)
        while not ScriptStorage.PlayerData.Level do
            task.wait(1)
        end
        local a = 0
        local h
        for X, w in J.Quests do
            if not J.BlacklistedQuestIds[X] then
                if (w[1].LevelReq >= a and w[1].LevelReq <= ScriptStorage.PlayerData.Level) then
                    a = w[1].LevelReq
                    h = w
                    W.CurrentQuestId = X
                    if ScriptStorage.PlayerData.Level >= 1500 and SeaIndex == 2 and X == 'ForgottenQuest' then break end
                end
            end
        end
        local a = h[#h]
        for X, X in a.Task do if X == 1 then table.remove(h, #h) end end
        for a, X in require(game.ReplicatedStorage.GuideModule).Data.NPCList do
            for w, w in X.Levels do if w == h[#h].LevelReq then W.CurrentNpc = a.CFrame end end
        end
        W.CurrentQuests = h
    end

    function J.GetCurrentQuest(W)
        local a = W.CurrentQuests[W.CurrentLevel] and
            W.CurrentQuests[W.CurrentLevel].LevelReq <= ScriptStorage.PlayerData.Level and W.CurrentLevel or 1
        for h in W.CurrentQuests[a].Task do return h, W.CurrentNpc, W.CurrentQuestId, a, W.CurrentQuests[a].Name end
    end

    -- Was a Double Quest (1<->2) toggle. GetCurrentQuest already falls back to slot 1 if a
    -- quest chain doesn't have a 3rd stage, so cycling through 3 slots here is safe even for
    -- chains that only have 1-2 stages.
    function J.MarkAsCompleted(W)
        if W.TripleQuest then
            W.CurrentLevel = W.CurrentLevel % 3 + 1
        else
            W.CurrentLevel = W.CurrentLevel == 2 and 1 or 2
        end
    end

    function J.AbandonQuest()
        Remotes.CommF_:InvokeServer("AbandonQuest")
    end

    function J.GetCurrentClaimQuest(W, h)
        return GetCurrentClaimQuest(h)
    end

    function J.StartQuest(W, a)
        game:GetService("ReplicatedStorage").Remotes.CommF_:InvokeServer('ColorsDealer', "2")
        return Remotes.CommF_:InvokeServer("StartQuest", W, a)
    end

    ScriptStorage.MobRegions = {}
    for W, W in game:GetService("ReplicatedStorage").FortBuilderReplicatedSpawnPositionsFolder:GetChildren() do
        ScriptStorage.MobRegions[tostring(W)] = ScriptStorage.MobRegions[tostring(W)] or {}
        table.insert(ScriptStorage.MobRegions[tostring(W)], W.CFrame)
    end
    TweenController = {}
    local W = 0
    local W = {}
    for a, a in game.ReplicatedStorage.NPCs:GetChildren() do
        if a.Name == 'Set Home Point' then
            table.insert(W,
                a:GetModelCFrame())
        end
    end
    function TweenController.Update()
        local a = game.Players.LocalPlayer.Character.HumanoidRootPart
        HumanoidRootPart = game.Players.LocalPlayer.Character:WaitForChild("HumanoidRootPart")
        if CaculateDistance(a.CFrame) > 250 then
            pcall(function() TweenInstance:Cancel() end)
            TweenDebounce = true
            a.CFrame = HumanoidRootPart.CFrame
            TweenDebounce = false
        end
        HumanoidRootPart.CFrame = a.CFrame + Vector3.new(0, 3, 0)
    end

    function GetPortal(a)
        local h, X = 9e9, nil
        for w, w in (PortalsBySea[SeaIndex] or {}) do
            local D = CaculateDistance(w, a)
            -- Picking purely by raw 3D distance to the target let this select a portal whose
            -- exit sits at a wildly different altitude than the target - Third Sea's own
            -- PortalsBySea entry (28282.5, 14896.8, 105.1) is a sky-high entrance, and it got
            -- picked as "nearest" to a ground-level CDK/Yama trial target (Soul Reaper), stranding
            -- the character up there over 13000 studs away with no way to actually reach the
            -- target - the trial silently never progressed. A portal only makes sense as a
            -- shortcut if it's roughly on the same vertical level as where we're actually trying
            -- to end up.
            if D < (CaculateDistance(a) - 300) and D < h and math.abs(w.Y - a.Y) < 1000 then
                h = D
                X = w
            end
        end
        if X then
            Remotes.CommF_:InvokeServer("requestEntrance", X)
            return task.wait(1)
        end
    end

    function GetEntries(a)
        local h, X = 9e9, nil
        for w, w in W do
            local W = CaculateDistance(w, a)
            if W < (CaculateDistance(a) - 700) and W < h then
                h = W
                X = w
            end
        end
        if X then if os.time() - 0 > 30 then for W = 1, 10, 1 do task.wait() end end end
    end

    function TweenController.Tween2(W, a)
        TweenInstance2 = Services.TweenService:Create(W,
            TweenInfo.new(CaculateDistance(W.CFrame, a) / 50, Enum.EasingStyle.Linear),
            { CFrame = ConvertTo(CFrame, a) - Vector3.new(0, 0, 0) })
        TweenInstance2:Play()
    end

    function TweenController.Create(W)
        if not W or TweenDebounce then return end
        local a = typeof(W) ~= 'CFrame' and ConvertTo(CFrame, W) or W
        if TweenInstance then pcall(function() TweenInstance:Cancel() end) end
        if tick() - (getgenv()._ccDb or 0) > 4 then
            getgenv()._ccDb = tick()
            pcall(function()
                for _, v in ipairs(game.Players.LocalPlayer.Character:GetDescendants()) do
                    if v:IsA("BasePart") then v.CanCollide = false end
                end
            end)
        end
        local W = game.Players.LocalPlayer.Character:WaitForChild("Head")
        if not W:FindFirstChild("eltrul") then
            local h = Instance.new('BodyVelocity')
            h.Name = "eltrul"
            h.MaxForce = Vector3.new(0, math.huge, 0)
            h.Velocity = Vector3.zero
            h.Parent = W
        end
        if CaculateDistance(a) > 500 then
            -- Portals work freely in Sea 1/2; in Sea 3 they need Valkyrie Helm equipped.
            -- The old "elseif SeaIndex ~= 3" branch never covered "Sea 3 WITH the Helm" -
            -- neither condition matched that case, so GetPortal silently never ran there
            -- even once the Helm was owned.
            if SeaIndex ~= 3 or ScriptStorage.Backpack['Valkyrie Helm'] then
                GetPortal(a)
            end
        end
        if CaculateDistance(Vector3.new(11256, -2138.0, 9888), a) < (CaculateDistance(a) - 700) and SeaIndex == 3 then
            local W = CFrame.new(-16269.0, 23, 1371)
            if CaculateDistance(W) > 60 then return TweenController.Create(W) and task.wait(1) end
            local W = require(game.ReplicatedStorage.Modules.Net)
            W:RemoteFunction('SubmarineWorkerSpeak'):InvokeServer('TravelToSubmergedIsland')
            task.wait(4)
        end
        a = CFrame.new(a.Position)
        local W = CaculateDistance(game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame, a)
        local h = game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame
        game.Players.LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(h.x, a.y, h.z)
        TweenInstance = Services.TweenService:Create(game.Players.LocalPlayer.Character.HumanoidRootPart,
            TweenInfo.new(W / (W < 18 and 25 or 350), Enum.EasingStyle.Linear), { CFrame = a })
        TweenInstance:Play()
    end

    local W = {}
    local a = game:GetService('Players')
    local h = game:GetService("RunService")
    local h = game:GetService('ReplicatedStorage')
    local X = game:GetService("Workspace")
    local X = game:GetService("VirtualInputManager")
    local X = a.LocalPlayer
    local X = h:WaitForChild('Modules')
    local w = X:WaitForChild("Net")
    local X = w:WaitForChild("RE/RegisterAttack")
    local X = w:WaitForChild('RE/RegisterHit')
    local X = w:WaitForChild('RE/ShootGunEvent')
    local X = h:WaitForChild("Remotes"):WaitForChild('Validator2')
    local h = game.ReplicatedStorage.Modules
    local X = h.Net
    local h, h = X:WaitForChild("RE/RegisterHit"), X:WaitForChild('RE/RegisterAttack')
    local h = {}
    function GetAllBladeHits()
        bladehits = {}
        for X, X in pairs(workspace.Enemies:GetChildren()) do
            if X:FindFirstChild('Humanoid') and X:FindFirstChild('HumanoidRootPart') and X.Humanoid.Health > 0 and (X.HumanoidRootPart.Position - game.Players.LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 65 then
                table.insert(bladehits, X)
            end
        end
        return bladehits
    end

    function Getplayerhit()
        bladehits = {}
        for X, X in pairs(workspace.Characters:GetChildren()) do
            if X.Name ~= game.Players.LocalPlayer.Name and X:FindFirstChild('Humanoid') and X:FindFirstChild('HumanoidRootPart') and X.Humanoid.Health > 0 and (X.HumanoidRootPart.Position - game.Players.LocalPlayer.Character.HumanoidRootPart.Position).Magnitude <= 65 then
                table.insert(bladehits, X)
            end
        end
        return bladehits
    end

    local _xNet = require(Services.ReplicatedStorage.Modules.Net)
    local w = _xNet:RemoteEvent("RegisterAttack", true)
    local D = _xNet:RemoteEvent("RegisterHit", true)
    local _atkTargets = {}
    local _atkCallTime = 0

    local function _buildHitTable(targets)
        local y = { [1] = nil, [2] = {}, [4] = "078da5141" }
        for _, L in pairs(targets) do
            pcall(function()
                if not y[1] then y[1] = L.Head end
                table.insert(y[2], { [1] = L, [2] = L.HumanoidRootPart })
                table.insert(y[2], L)
            end)
        end
        return y
    end

    task.spawn(function()
        while task.wait(0.15) do
            local t = {}
            pcall(function()
                for _, y in pairs(GetAllBladeHits()) do table.insert(t, y) end
                for _, y in pairs(Getplayerhit()) do table.insert(t, y) end
            end)
            _atkTargets = t
        end
    end)

    game:GetService("RunService").Heartbeat:Connect(function()
        -- Client bypass: zero out tapCooldown gate (CombatUtil.CanAttack)
        _G.tapCooldown = 0
        local now = tick()
        if now - _atkCallTime > 0.3 then return end
        if #_atkTargets == 0 then return end
        pcall(function()
            local y = _buildHitTable(_atkTargets)
            if not y[1] then return end
            -- Server bypass: send minimum animation duration (0.01s)
            -- Server enforces cooldown = animLength, so 0.01s = ~100 attacks/s
            -- vs normal 0.35s = ~3 attacks/s  =>  ~33x speed increase
            w:FireServer(0.01)
            D:FireServer(unpack(y))
            w:FireServer(0.01)
            D:FireServer(unpack(y))
            w:FireServer(0.01)
            D:FireServer(unpack(y))
            w:FireServer(0.01)
            D:FireServer(unpack(y))
        end)
    end)

    function h:Attack() end

    function W.Attack(_) _atkCallTime = tick() end

    CombatController = { GRAB = true, GRAB_DISTANCE = SeaIndex == 1 and 250 or 350, MAX_ATTACK_DURATION = 5, MAX_ATTACK_DURATION_2 = 60, LEVITATE_TIME = 0, CurrentIndex = 1 }
    LastFound = os.time()
    function CombatController.Grab(h)
        pcall(sethiddenproperty, game.Players.LocalPlayer, 'SimulationRadius', math.huge)
        if not CombatController.GRAB or GrabDebounce == os.time() then end
        GrabDebounce = os.time()
        local X, w = Vector3.zero, 0
        ForcePosition = nil
        local D = {}
        for y, y in Services.Workspace.Enemies:GetChildren() do
            if y.Name == h then
                if y:FindFirstChild('Humanoid') and y:FindFirstChild("HumanoidRootPart") and y.Humanoid.Health > 0 then
                    local h = y.HumanoidRootPart.Position
                    if h then
                        if not ForcePosition or CaculateDistance(h, ForcePosition) < CombatController.GRAB_DISTANCE then
                            w = w + 1
                            y:SetAttribute("OldPosition", y:GetAttribute('OldPosition') or h)
                            X = X + h
                            ForcePosition = ForcePosition or h
                            table.insert(D, y)
                        end
                    end
                end
            end
        end
        if w == 0 then return end
        X = CFrame.new(X / w)
        table.foreach(D, function(h, h)
            (function()
                if h:GetAttribute("IgnoreGrab") then return end
                if (h:GetAttribute("FailureCount") or 0) > 12 then return end
                local w = h:FindFirstChild("HumanoidRootPart")
                local D = w:FindFirstChild('FarmingVelocity')
                if not D then
                    D = Instance.new('BodyVelocity')
                    D.Name = 'FarmingVelocity'
                    D.MaxForce = Vector3.new(4000, 4000, 4000)
                    D.Parent = w
                end
                D.Velocity = Vector3.new(0, 0, 0)
                local D = w:FindFirstChild("FarmingPosition")
                if not D then
                    D = Instance.new("BodyPosition")
                    D.Name = 'FarmingPosition'
                    D.MaxForce = Vector3.new(4000, 4000, 4000)
                    D.P = 4.12
                    D.D = 1000
                    D.Parent = w
                end
                h:SetAttribute('IsGrabbed', true)
                pcall(function() h.HumanoidRootPart.CFrame = X end)
                h:SetAttribute("MidPoint", X)
            end)()
        end)
    end

    function Sort1(h)
        return h and h:FindFirstChild("HumanoidRootPart") and
            math.floor(CaculateDistance(h.HumanoidRootPart.CFrame))
    end

    function CombatController.Search(h)
        local X = {}
        local w = false
        for D, D in GetMonAsSortedRange() do
            if table.find(h, D.Name) and D:FindFirstChild("Humanoid") and D.Humanoid.Health > 0 then
                if (D:GetAttribute('FailureCount') or 0) < 10 then
                    w = true
                    table.insert(X, D)
                end
            end
        end
        table.sort(X, function(D, y) return Sort1(D) < Sort1(y) end)
        if w then
            local w = X[1]
            return w
        end
        for X, X in h do
            local h = game.ReplicatedStorage:FindFirstChild(X)
            if h then return h end
        end
    end

    function CombatController.Attack(h, X, w, D)
        if ScriptStorage.Tools["Sweet Chalice"] and getsenv(game.ReplicatedStorage.GuideModule)["_G"]['InCombat'] then
            TweenController.Create(Vector3.new(0, 0, 0))
            return
        end
        sethiddenproperty(game.Players.LocalPlayer, 'SimulationRadius', math.huge)
        h = type(h) == "string" and { h } or (h or {})
        for y, L in (h) do
            local b = tostring(L)
            if b == 'Deandre' or b == "Urban" or b == "Diablo" and (os.time() - (LastFire12 or 0)) > 180 then
                LastFire12 = os.time()
                Remotes.CommF_:InvokeServer("EliteHunter")
            end
            if X then
                local b = GetMonAsSortedRange()[1]
                local C = b and b:FindFirstChild('HumanoidRootPart') and b.HumanoidRootPart.Position
                if C and CaculateDistance(C) < w then MonResult = b end
            else
                MonResult = CombatController.Search(h)
            end
            if MonResult then
                LastFound = os.time()
                local h, w = 0, os.time()
                local w, b = 0, os.time()
                while task.wait(0.05) do
                    if _G.Stop then return end
                    if ScriptStorage.Tools["Sweet Chalice"] and getsenv(game.ReplicatedStorage.GuideModule)["_G"]["InCombat"] then
                        TweenController.Create(Vector3.new(0, 0, 0))
                        return
                    end
                    local C = MonResult:FindFirstChild('Humanoid')
                    local p = MonResult:FindFirstChild('HumanoidRootPart')
                    -- Target can vanish from workspace (killed by someone else, despawn) without
                    -- Health ever hitting 0 on our stale reference - only checking Health <= 0 let
                    -- this loop spin forever on a dead instance (tween/attack against a destroyed
                    -- part throws "cannot resume dead coroutine", player stands frozen).
                    if not C or C.Health <= 0 or not p or not MonResult.Parent then
                        if MonResult.Name == "Don Swan" then Storage:Set("SwanDefeated", true) end
                        break
                    end
                    TweenController.Create(CaculateCircreDirection(p.CFrame) + Vector3.new(0, 35, 0))
                    if CaculateDistance(p.Position + Vector3.new(0, 35, 0)) < 150 then
                        y = D and D()
                        CombatController.Grab(L or '')
                        if MonResult.Name ~= "Core" then
                            if ScriptStorage.PlayerData.Level > 100 and w >= CombatController.MAX_ATTACK_DURATION_2 and C.Health - C.MaxHealth == 0 then
                                SetTask('SubTask',
                                    'Hop Server - Mob Health Unchanged ( ' .. C.Health .. ' / ' .. C.MaxHealth .. ')')
                                alert("stuck", "Mob health unchanged")
                                _G.Stop = true
                                getgenv()._vxeze_running = nil
                                LowHop("Singapore")
                            end
                            if h >= CombatController.MAX_ATTACK_DURATION and C.Health - C.MaxHealth == 0 then
                                h = 0
                                local D = MonResult:GetAttribute('OldPosition')
                                if D then
                                    MonResult:SetPrimaryPartCFrame(CFrame.new(D))
                                    MonResult:SetAttribute('IgnoreGrab', true)
                                    MonResult:SetAttribute('FailureCount',
                                        (MonResult:GetAttribute("FailureCount") or 0) + 1)
                                    alert('Failed to attack',
                                        "Returning to the old posiiton ( #" ..
                                        MonResult:GetAttribute("FailureCount") .. " )")
                                    MonResult.HumanoidRootPart.CFrame = (CFrame.new(D))
                                    task.wait()
                                    return
                                end
                            end
                        end
                        if (FarmFruitMastery or math.huge) - os.time() < 3 and math.floor(MonResult.Humanoid.Health / MonResult.Humanoid.MaxHealth * 100) < 30 and not FunctionsHandler.RaidController.Methods.GetCurrentRaidIsland:Call() then
                            TweenController.Create((p.CFrame) + Vector3.new(0, 25, 0))
                            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Blox Fruit')
                            LockAimPositionTo(MonResult.HumanoidRootPart.CFrame.p)
                            local D = { 'Z', 'X', "C", 'V' }
                            local y = D[math.random(1, #D)]
                            SendKey(y, .31)
                        else
                            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call(ScriptStorage.ForceToUseSword and
                                'Sword' or "Melee")
                        end
                        W:Attack(MonResult)
                        if os.time() ~= b then
                            b = os.time()
                            h = h + 1
                            w = w + 1
                        end
                        if h > 30 and MonResult.Name ~= "Core" then
                            alert("Take more than 30s to attack, canceling")
                            break
                        end
                    end
                end
            elseif not X then
                if (os.time() - LastFound) > 200 then
                    alert('W SCRIPT HUB', 'Error while farming, rejoin')
                    getgenv()._vxeze_running = nil
                    LowHop("Singapore")
                    return
                end
                local h = ScriptStorage.MobRegions[L]
                if not h then
                    local X = Services.Workspace.Enemies:FindFirstChild(L) or game.ReplicatedStorage:FindFirstChild(L)
                    h = X and { X:GetPrimaryPartCFrame().p }
                end
                if not h then
                    Report('[ Game data error ] Mob with name ' .. tostring(L) .. ' have no spawn region datas')
                    Hop("Singapore")
                    return
                end
                local X
                if not h[CombatController.CurrentIndex] then CombatController.CurrentIndex = 1 end
                X = h[CombatController.CurrentIndex]
                local h = os.time()
                TweenController.Create(X + Vector3.new(0, 35, 35))
                if CaculateDistance(X + Vector3.new(0, 35, 35)) < 15 then
                    CombatController.CurrentIndex =
                        CombatController.CurrentIndex + 1
                end
            end
        end
    end

    LevelFarmTTL = 0
    LastTravel = os.time()
    FunctionsHandler = { Initalized = false }
    setmetatable(FunctionsHandler, {
        __index = function(h, X)
            QueryResult = rawget(h, X)
            if not QueryResult then
                return {
                    Register = function(w)
                        if w == false then return end
                        Result = { CacheListener = {}, RealCache = {}, Methods = {}, Constants = {}, Events = {}, Initalized = true }
                        function Result.RegisterMethod(w, D, y)
                            w.Methods[D] = { Name = D, Callback = y, Call = function(w, ...) return w.Callback(...) end, Events = {} }
                            return true
                        end

                        setmetatable(Result.Constants,
                            { __newindex = function() assert(false, 'cannot change constant value!') end })
                        if h.Constants[Key] then
                            function Result.SaveConstant(w, w, w) return assert(false, 'constant name was used before!') end

                            rawset(h.Constants, Key, Value)
                        end
                        function Result.Set(h, w, D)
                            h.CacheListener[w] = D
                            return D
                        end

                        function Result.Get(h, w) return h.Constants[w] or h.RealCache[w] end

                        function Result.AddVariableChangeListener(h, w, D) h.Events[w] = D end

                        Result.CacheListener.__parent = Result
                        setmetatable(Result.CacheListener, {
                            __newindex = function(h, w, D)
                                if h.__parent and h.__parent.Events and h.__parent.Events[w] then
                                    h.__parent.Events[w](w, D)
                                end
                                if h.__parent then h.__parent.RealCache[w] = D end
                            end
                        })
                        FunctionsHandler[X] = Result
                    end,
                    Initalized = false
                }
            end
            return QueryResult
        end
    })
    function FunctionsHandler.SynchorizeUntilModuleLoaded(h, X)
        local w = os.time()
        while not h.Initalized do
            task.wait()
            local h = os.time() - w
            assert(not (X and h > X), "timed out")
        end
    end

    function GetCurrentClaimQuest(h)
        local h = game.Players.LocalPlayer.PlayerGui.Main.Quest.Visible and
            game.Players.LocalPlayer.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text:gsub(
                "%s*Defeat%s*(%d*)%s*(.-)%s*%b()", "%2")
        return (type(h) == "string" and string.gsub(h, "Military ", "Mil. ") or h),
            game.Players.LocalPlayer.PlayerGui.Main.Quest.Container.QuestTitle.Title.Text
    end

    function SpawnDarkbeard()
        SetTask("MainTask", "Dark Fragments | Preparing")
        if ScriptStorage.Tools['Fist of Darkness'] then
            repeat
                task.wait()
                TweenController.Create(CFrame.new(3777.63, 14.97, -3499.05))
            until CaculateDistance(CFrame.new(3777.63, 14.97, -3499.05)) <= 20
            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call("Fist of Darkness")
        else
            local farmed = 0
            local maxC = 30
            while farmed < maxC do
                local Nearest = GetNearestChest()
                if Nearest then
                    -- Chests open on physical touch (ClientChest.Touched), not a ProximityPrompt
                    -- or keypress - confirmed via decompile. Moving onto the chest is the whole
                    -- interaction. A single TweenController.Create call only reliably covers
                    -- short hops, so re-issue it every frame toward the same chest until
                    -- actually close instead of firing once and stalling partway on far chests.
                    local y = 0
                    while Nearest and not Nearest:GetAttribute("IsDisabled") and CaculateDistance(Nearest:GetPivot()) > 8 and y < 200 do
                        TweenController.Create(Nearest:GetPivot())
                        task.wait()
                        y = y + 1
                    end
                    farmed = farmed + 1
                else
                    break
                end
            end
            -- The loop only ever exits by hitting maxC or running out of real chests
            -- server-wide (farmed anywhere from 0 up to maxC-1) - both mean there's nothing
            -- more to farm here, so hop either way instead of only checking farmed==0.
            Hop("Singapore")
        end
    end

    FunctionsHandler.SniperFruit:Register()
    FunctionsHandler.LocalPlayerController.Register()
    FunctionsHandler.ExpRedeem:Register()
    FunctionsHandler.LevelFarm:Register()
    FunctionsHandler.Saber:Register()
    FunctionsHandler.Pole:Register()
    FunctionsHandler.Rengoku:Register()
    FunctionsHandler.Yama:Register()
    FunctionsHandler.Tushita:Register()
    FunctionsHandler.SpikeyTrident:Register()
    FunctionsHandler.SharkAchor:Register()
    FunctionsHandler.FoxLamp:Register()
    FunctionsHandler.DarkDagger:Register()
    FunctionsHandler.Canvander:Register()
    FunctionsHandler.BuddySword:Register()
    FunctionsHandler.HallowScythe:Register()
    FunctionsHandler.CursedDualKatana:Register()
    FunctionsHandler.AcidumRifle:Register()
    FunctionsHandler.Kabucha:Register()
    FunctionsHandler.VenomBow:Register()
    FunctionsHandler.SoulGuitar:Register()
    FunctionsHandler.DragonStorm:Register()
    FunctionsHandler.InsictV2:Register()
    FunctionsHandler.RainbowSaviour:Register()
    FunctionsHandler.DarkBladeV2:Register()
    FunctionsHandler.SecondSeaPuzzle:Register()
    FunctionsHandler.ColosseumPuzzle:Register()
    FunctionsHandler.Trevor:Register()
    FunctionsHandler.EvoRace:Register()
    FunctionsHandler.Wenlocktoad:Register()
    -- Status codes for Remotes.CommF_:InvokeServer("Wenlocktoad", "1") confirmed via decompile
    -- (ReplicatedStorage.DialoguesList, Arowe's V3 dialogue function f29): -2 = already V3,
    -- -1 = under $2,000,000, 0 = quest not accepted yet (need "2" to accept), 1 = quest accepted -
    -- go do the race-specific objective, 2 = objective done, ready to pay via "3". The objective
    -- itself is per race per the wiki: Human = kill Diamond/Jeremy/Orbitus, Shark = kill a wild
    -- Sea Beast, Rabbit/Mink = open 30 chests. Angel/Ghoul/Cyborg's objectives (PvP kills / show
    -- a Fruit after a long unlock chain) are not automated here.
    -- Real in-game cost is still $2,000,000 (server-side), but only attempt with 2,500,000+
    -- banked as a safety margin, and require Level Max (RaceLevel==2 already implies Colosseum
    -- Quest/Warrior Helmet done, since that's required to reach V2 in the first place).
    FunctionsHandler.Wenlocktoad:RegisterMethod("Refresh", function()
        if not getgenv().Studio["Blox Fruit"]["Sub"]["Pull Lever"] then return end
        if ScriptStorage.PlayerData.Level < MaxLevel or ScriptStorage.PlayerData.RaceLevel ~= 2 or ScriptStorage.PlayerData.Beli < 2500000 then return end
        return true
    end)
    FunctionsHandler.Wenlocktoad:RegisterMethod('Start', function()
        -- V2->V3's quest NPC only lives in Sea 2 - same as EvoRace, hop back to Dressrosa
        -- first if a farming task already pushed us to Sea 1/3.
        if SeaIndex ~= 2 then
            SetTask('MainTask', 'Auto Race V3 - Teleporting to Sea 2')
            Remotes.CommF_:InvokeServer("TravelDressrosa")
            task.wait(3)
            return
        end
        local v = Remotes.CommF_:InvokeServer("Wenlocktoad", "1")
        -- Cached (not re-fetched) by RefreshTasksData's priority override below, so it knows
        -- whether a V3 objective is actively in progress without spamming this remote itself.
        WenlocktoadState = v
        if v == -1 then
            SetTask('MainTask', 'Auto Race V3 - Needs 2,000,000 Beli')
            return
        elseif v == 0 then
            SetTask('MainTask', 'Auto Race V3 - Accepting Quest')
            Remotes.CommF_:InvokeServer('Wenlocktoad', '2')
            return
        elseif v == 2 then
            SetTask('MainTask', "Auto Race V3 - Finalizing")
            Remotes.CommF_:InvokeServer("Wenlocktoad", "3")
            RefreshRace()
            return
        end
        -- v == 1: quest accepted, do the race-specific objective
        local a = ScriptStorage.PlayerData.Race
        if a == "Human" then
            local D = { "Diamond", "Jeremy", "Orbitus" }
            local w
            for k = 1, #D do
                if ScriptStorage.Enemies[D[k]] then w = D[k] end
            end
            if w then
                SetTask('MainTask', "Auto Race V3 - Defeating " .. w)
                CombatController.Attack(w)
                return
            end
        elseif a == "Shark" or a == "Fishman" then
            -- Objective confirmed straight from the live quest dialogue (ReplicatedStorage.
            -- DialoguesList's f29, the same function this Wenlocktoad NPC uses in-game): calling
            -- Remotes.CommF_:InvokeServer("Wenlocktoad", "info") while v==1 returns "You haven't
            -- completed my order yet. Talk to me again once you defeat a Sea Beast." - a plain
            -- wild Sea Beast kill, no "Summon Sea Beast" item involved (that tool name only
            -- showed up in the reference script's EquipAllWeapon exclusion list, unrelated to
            -- this quest). Per the wiki and the user's own confirmation, Sea Beasts are a luck-
            -- based random spawn that only happens while actually out sailing a boat - NOT
            -- something server-hopping helps with, and NOT something a plain HumanoidRootPart
            -- teleport out to open water triggers either (confirmed live: camping the open-sea
            -- coordinate below via TweenController for several minutes with no boat left
            -- workspace.SeaBeasts empty the whole time). The user's EvoRacev3.lua reference
            -- (BuyBoat/CheckBoat/TweenBoat loop around its line 10767) always buys and actually
            -- sails a boat out before one ever appears - so that's the actual dependency here,
            -- not a data-lookup or streaming-radius quirk.
            -- Sea Beasts spawn into their own workspace.SeaBeasts folder, not workspace.Enemies,
            -- so unlike the Human branch above they never resolve through the
            -- ScriptStorage.Enemies[name] proxy (its __index only checks workspace.Enemies/
            -- ReplicatedStorage - see the setmetatable near line 642). They also don't use a real
            -- Humanoid rig at all - live-inspected a spawned "SeaBeast1": its "Humanoid" child is
            -- actually an AnimationController (IsA("Humanoid") is false), and health lives in a
            -- separate IntValue named "Health" instead of Humanoid.Health. That means
            -- GetMonAsSortedRange()'s own SeaBeasts loop (which checks a.Humanoid:IsA("Humanoid"))
            -- silently never matches them either, so CombatController.Attack(beast.Name) can never
            -- find one via CombatController.Search - it was reading v.Humanoid.Health, which threw
            -- ("Health is not a valid member of AnimationController") and got swallowed by
            -- RefreshTasksData's outer xpcall every single tick, so the beast was detected as
            -- existing but the whole Start() call silently aborted before ever attacking it.
            -- Read the real Health IntValue directly and drive the fight manually with the same
            -- low-level TweenController + W:Attack() melee trigger the Skypiea PvP branch above
            -- already uses successfully for non-CombatController targets.
            local SeaBeasts = Services.Workspace:FindFirstChild("SeaBeasts")
            local beast, beastHealth, beastRoot
            if SeaBeasts then
                for _, v in SeaBeasts:GetChildren() do
                    local h, rp = v:FindFirstChild("Health"), v:FindFirstChild("HumanoidRootPart")
                    if h and h:IsA("IntValue") and h.Value > 0 and rp then
                        beast, beastHealth, beastRoot = v, h, rp
                        break
                    end
                end
            end
            if beast then
                if SeaBeastBoatTween and SeaBeastBoatTween.Stop then SeaBeastBoatTween.Stop() end
                SeaBeastBoatTween = nil
                SeaBeastSailStart = nil
                local hum = LocalPlayer.Character:FindFirstChild("Humanoid")
                -- Sit=false alone was live-observed to sometimes leave the SeatWeld in place a
                -- moment too long (TweenController.Create fighting it below, character stuck near
                -- the seat instead of actually closing on the beast) - pairing it with the same
                -- ChangeState(Jumping) call the idle-jump safety net near line 4423 already uses
                -- to reliably eject seated humanoids makes leaving the boat here just as solid.
                if hum then
                    hum.Sit = false
                    hum:ChangeState(Enum.HumanoidStateType.Jumping)
                end
                if not SeaBeastFoundNotified then
                    SeaBeastFoundNotified = true
                    alert("Sea Beast Found", "Engaging " .. beast.Name .. " for Race V3.")
                end
                SetTask('MainTask', "Auto Race V3 - Defeating " .. beast.Name)
                SetTask('SubTask', 'HP ' .. beastHealth.Value)
                TweenController.Create(beastRoot.CFrame + Vector3.new(0, 5, 0))
                if CaculateDistance(beastRoot.CFrame) < 150 then
                    FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Melee')
                    W:Attack()
                end
                return
            end
            SeaBeastFoundNotified = false
            -- No boat yet - buy one at the dealer first (coordinate ported from the reference's
            -- BuyBoatCFrame). GetMyBoatName() resolves Pirates/Marines dynamically the same way
            -- every other boat lookup in this file already does (see its own comment near line
            -- 1218), instead of the reference's hardcoded "MarineBrigade".
            local myBoat = Services.Workspace.Boats:FindFirstChild(GetMyBoatName())
            if not myBoat then
                -- Boat gone (sunk/despawned/never bought) - clear any stale tween tracking so a
                -- freshly bought boat always gets a real TweenBoat call below instead of skipping
                -- it because SeaBeastBoatTween still held a handle from a boat that no longer
                -- exists.
                SeaBeastBoatTween = nil
                SeaBeastSailStart = nil
                local DealerPos = Vector3.new(-1936.93213, 6.6355958, -2568.47974)
                SetTask('MainTask', "Auto Race V3 - Buying a Boat")
                SetTask('SubTask', 'Distance: ' .. math.floor(CaculateDistance(DealerPos)) .. ' studs')
                TweenController.Create(CFrame.new(DealerPos))
                if CaculateDistance(DealerPos) < 15 then
                    Remotes.CommF_:InvokeServer("BuyBoat", GetMyBoatName())
                    alert("Race V3", "Boat purchased - boarding next.")
                    task.wait(1)
                end
                return
            end
            local seat = myBoat:FindFirstChild("VehicleSeat")
            local hum = LocalPlayer.Character:FindFirstChild("Humanoid")
            -- A Root left over on the seat from an earlier script run's cruise (before a
            -- rejoin/character reset dropped the player without ever cleaning it up) means the
            -- background sync loop below is still hard-driving the seat's CFrame every single
            -- frame with nobody aboard. Sit() would appear to work for a frame and then get
            -- immediately kicked back out by that same forced CFrame set - live-observed as the
            -- character repeatedly sitting down and instantly popping back out. Clear that stray
            -- Root first (halting the loop's effect on this seat) before attempting to board.
            if seat and not (hum and hum.SeatPart == seat) and seat:FindFirstChild("Root") then
                SetTask('MainTask', "Auto Race V3 - Resetting Boat")
                SetTask('SubTask', 'Clearing stale boat state')
                seat.Root:Destroy()
                return
            end
            -- Have a boat but not sitting in it yet - Seat:Sit() is a direct, reliable way to
            -- board it (rather than relying on touch-based auto-seating from a teleported
            -- HumanoidRootPart, which doesn't always register).
            if seat and hum and hum.SeatPart ~= seat then
                SetTask('MainTask', "Auto Race V3 - Boarding Boat")
                SetTask('SubTask', 'Distance: ' .. math.floor(CaculateDistance(seat.CFrame)) .. ' studs')
                TweenController.Create(seat.CFrame + Vector3.new(0, 5, 0))
                if CaculateDistance(seat.CFrame) < 15 then
                    seat:Sit(hum)
                end
                return
            end
            -- Seated and sailing - TweenBoat (ported earlier from the user's own "Function
            -- TweenBoat.lua" reference, previously unused - see its definition/comment near line
            -- 1227) drives the actual VehicleSeat out to the open-sea patrol point and the
            -- background loop right after it keeps syncing the seat to the tween every frame.
            -- Re-issuing this every tick would fight its own Tween, but blindly trusting
            -- SeaBeastBoatTween forever isn't safe either - it stays a non-nil handle across a
            -- character respawn (the variable itself is never reset by that), across TweenBoat
            -- silently no-op'ing if the seat momentarily wasn't found the instant it was called,
            -- and across the seat getting reset by the stray-Root cleanup above - all cases
            -- live-observed leaving the boat parked wherever it happened to be, forever "Sailing"
            -- without ever actually moving. Re-verify the seat's REAL position against the patrol
            -- point periodically (not every tick, so an in-progress cruise isn't interrupted) and
            -- restart the tween if it's neither arrived nor been (re)started recently.
            -- Y=0 (as originally given) sits below the real sea surface here - the reference/
            -- original patrol coordinate's Y (~9) is the actual water-line height a
            -- PirateBrigade/MarineBrigade-sized boat's VehicleSeat rests at (live-confirmed: a
            -- Y=0 landing target let the boat visibly sink/dive under the water instead of
            -- floating on it). Keep the user's requested X/Z, correct only the Y.
            local PatrolPoint = Vector3.new(5209, 9, -745)
            local atPatrol = seat and (seat.Position - PatrolPoint).Magnitude < 30
            if not atPatrol and (not SeaBeastBoatTween or not SeaBeastSailStart or os.time() - SeaBeastSailStart > 60) then
                if SeaBeastBoatTween and SeaBeastBoatTween.Stop then SeaBeastBoatTween.Stop() end
                SeaBeastSailStart = os.time()
                SeaBeastBoatTween = TweenBoat(CFrame.new(PatrolPoint))
                alert("Race V3", "Sailing out to patrol for a Sea Beast.")
            end
            -- Sitting still on an anchored boat for minutes at a time otherwise reads as AFK to
            -- the position-based idle tracker near line 4602 (LastIdling only updates when
            -- HumanoidRootPart.CFrame moves >2 studs - see its own comment near line 925) and
            -- that idle-hop loop force-rejoined the server mid-camp, throwing away the whole
            -- sail. Keep marking this as active every tick while legitimately parked here.
            LastIdling = os.time()
            SetTask('MainTask', "Auto Race V3 - Sailing for a Sea Beast")
            SetTask('SubTask', 'Distance to patrol point: ' .. math.floor(CaculateDistance(PatrolPoint)) .. ' studs')
            return
        elseif a == "Rabbit" or a == "Mink" then
            -- Both confirmed via wiki as "collect 30 chests" - same _ChestTagged/touch
            -- mechanic already used for Dark Fragment farming.
            local w = GetNearestChest()
            if w then
                -- A single TweenController.Create call only reliably covers short hops - for a
                -- far chest it can stall partway and just sit there. Re-issue it every frame
                -- toward the SAME chest (same pattern EvoRace's flower loop above already uses)
                -- until actually close, instead of firing once and hoping.
                SetTask('MainTask', "Auto Race V3 - Opening Chest")
                local y = 0
                while w and not w:GetAttribute("IsDisabled") and CaculateDistance(w:GetPivot()) > 8 and y < 200 do
                    TweenController.Create(w:GetPivot())
                    task.wait()
                    y = y + 1
                end
                return
            end
        elseif a == "Skypiea" then
            -- Wiki-confirmed: Skypiea's V3 objective is a PvP one, unlike every other race's
            -- PvE target - defeat another player who ALSO has the Skypiea race. Other players'
            -- race is readable off their own replicated Data.Race (confirmed live), so scan
            -- for a match and fight them with the same low-level W:Attack() melee trigger
            -- CombatController itself uses (its hit-detection loop already covers player
            -- targets via Getplayerhit(), not just NPCs).
            -- Live-confirmed bug: the server rejects attacks on same-team players outright
            -- ("Cannot attack players on the same team!") - Marines can't hit Marines, Pirates
            -- can't hit Pirates, regardless of race match. Only consider opposite-team players.
            -- Safe Zone / Raid-zone / PvP-toggle checks ported from the user's own reference
            -- file (Vxeze Hub/CheckSkypiea.lua): real Safe Zones are
            -- workspace._WorldOrigin.SafeZones (each a sized region, not a name list), "Island
            -- 1" is the open-sea Raid zone where PvP is allowed even if otherwise near a safe
            -- zone, and each player's own PvpDisabled attribute is the actual opt-out toggle.
            local function InRaidZone(pos)
                local loc = workspace._WorldOrigin.Locations:FindFirstChild("Island 1")
                return loc and CaculateDistance(loc.CFrame, pos) < 3000
            end
            local function InSafeZone(pos)
                local zones = workspace._WorldOrigin:FindFirstChild("SafeZones")
                if not zones then return false end
                for _, v in zones:GetChildren() do
                    if v:FindFirstChild("Mesh") and CaculateDistance(v.CFrame, pos) < (v.Mesh.Scale.Magnitude / 2) then
                        return true
                    end
                end
                return false
            end
            local target
            for _, p in game.Players:GetPlayers() do
                if p ~= LocalPlayer and p.Character and p.Team ~= LocalPlayer.Team and not p:GetAttribute("PvpDisabled") then
                    local race = p:FindFirstChild("Data") and p.Data:FindFirstChild("Race")
                    local hum = p.Character:FindFirstChild("Humanoid")
                    local hrp = p.Character:FindFirstChild("HumanoidRootPart")
                    if race and race.Value == "Skypiea" and hum and hum.Health > 0 and hrp
                        and (InRaidZone(hrp.Position) or not InSafeZone(hrp.Position)) then
                        target = p
                        break
                    end
                end
            end
            local hrp = target and target.Character:FindFirstChild("HumanoidRootPart")
            if hrp then
                SetTask('MainTask', "Auto Race V3 - Fighting " .. target.Name .. " (same race)")
                TweenController.Create(hrp.CFrame)
                if CaculateDistance(hrp.CFrame) < 150 then
                    FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Melee')
                    W:Attack()
                end
                return
            else
                -- No Skypiea player on this server right now - hop looking for one instead of
                -- sitting idle waiting for someone to wander in.
                SetTask('MainTask', "Auto Race V3 - No Skypiea player here, hopping...")
                LowHop("Singapore")
                return
            end
        end
        -- No farmable target found this tick (nothing to kill/no chest nearby, or race is
        -- Angel/Ghoul/Cyborg) - just wait, the objective is server-tracked and "1" will flip
        -- to 2 on its own once it's done.
        SetTask('MainTask', "Auto Race V3 - Waiting ( " .. tostring(a) .. " )")
    end)
    FunctionsHandler.DarkBladeV3:Register()
    FunctionsHandler.ThirdSeaPuzzle:Register()
    FunctionsHandler.DojoQuest:Register()
    FunctionsHandler.RaceAwakening:Register()
    FunctionsHandler.PirateRaid:Register()
    FunctionsHandler.RaidController:Register()
    FunctionsHandler.MeleesController:Register()
    FunctionsHandler.Superhuman:Register()
    FunctionsHandler.DeathStep:Register()
    FunctionsHandler.SharkmanKarate:Register()
    FunctionsHandler.ElectricClaw:Register()
    FunctionsHandler.DragonTalon:Register()
    FunctionsHandler.Godhuman:Register()
    FunctionsHandler.BossesTask:Register()
    FunctionsHandler.SpecialBossesTask:Register()
    FunctionsHandler.CollectDrops:Register()
    FunctionsHandler.CollectBerries:Register()
    FunctionsHandler.UtillyItemsActivitation:Register()
    FunctionsHandler.SeaTravel:Register()
    -- Extracted out of LevelFarm:Start, where it used to be unreachable dead code whenever
    -- GodHumanFlag was true (LevelFarm:Start returns early inside its Godhuman-farming branch
    -- and never reached this) - Dark Fragments farming and the Sea 2 -> Sea 3 TravelZou call
    -- could get stuck behind an unrelated Godhuman purchase attempt forever. Now its own task,
    -- reachable regardless of what LevelFarm is doing.
    FunctionsHandler.SeaTravel:RegisterMethod("Refresh", function()
        if os.time() - LastTravel < 60 then return end
        local X = ScriptStorage.PlayerData.Level
        if X >= 1500 and SeaIndex == 2 then
            -- SeaTravel outranks EvoRace/Wenlocktoad in TasksOrder, and both of their quest
            -- NPCs only live in Sea 2 - without this check, SeaTravel just won priority over
            -- them every 60s once Level/Beli were high enough and yanked the player to Third
            -- Sea mid Race Evolution (V1->V2/V2->V3), abandoning quest progress. Mirror their
            -- own Refresh gates (Level Max + 2,500,000 Beli + Warrior Helmet, RaceLevel 1 or 2)
            -- here so SeaTravel only fires once neither of them actually has work to do.
            local raceReady = X >= MaxLevel and ScriptStorage.PlayerData.Beli >= 2500000 and
                ScriptStorage.Backpack['Warrior Helmet']
            local raceLevel = ScriptStorage.PlayerData.RaceLevel
            if raceReady and (raceLevel == 1 or raceLevel == 2) then return end
            return true
        end
        if X >= 700 and SeaIndex == 1 then
            return true
        end
    end)
    FunctionsHandler.SeaTravel:RegisterMethod('Start', function()
        LastTravel = os.time()
        local X = ScriptStorage.PlayerData.Level
        if X >= 1500 and SeaIndex == 2 then
            -- Dark Fragment is ONLY needed for Skull Guitar (see SoulGuitar task), not for
            -- traveling to Third Sea at all - gating the trip on it here blocked Sea 3
            -- progression indefinitely for anyone not already sitting on a Dark Fragment.
            if not Services.Workspace.Map.IceCastle.Hall.LibraryDoor:FindFirstChild('PhoeyuDoor') then
                SetTask('MainTask', 'Sea Travel | Teleporting to Third Sea')
                Remotes.CommF_:InvokeServer("TravelZou")
                task.wait(3)
            end
        elseif X >= 700 and SeaIndex == 1 then
            SetTask('MainTask', 'Sea Travel | Teleporting to Second Sea')
            Remotes.CommF_:InvokeServer("TravelDressrosa")
            task.wait(3)
        end
    end)
    FunctionsHandler.ExpRedeem:RegisterMethod("Refresh", function()
        local Env = getsenv(game.ReplicatedStorage.GuideModule)
        local ExpBoost = 0

        pcall(function()
            ExpBoost = Env._G.ServerData.ExpBoost or 0
        end)

        return ScriptStorage.PlayerData.Level < MaxLevel
            and ExpBoost == 0
            and not Storage.Get(Storage, "IsCodesRanOut")
    end)
    FunctionsHandler.ExpRedeem:RegisterMethod("Start", function()
        local h = {
            'BANEXPLOIT', 'NOMOREHACKS', 'WildDares', 'BossBuild', 'GetPranked', 'EARN_FRUITS',
            'Sub2UncleKizaru', 'FIGHT4FRUIT', 'kittgaming', 'TRIPLEABUSE', 'Sub2CaptainMaui',
            'Sub2Fer999', 'Enyu_is_Pro', 'Magicbus', 'JCWK', 'Starcodeheo', 'Bluxxy',
            'SUB2GAMERROBOT_EXP1', 'Sub2NoobMaster123', 'Sub2Daigrock', 'Axiore',
            'TantaiGaming', 'StrawHatMaine', 'Sub2OfficialNoobie', 'TheGreatAce',
            'SEATROLLIN', '24NOADMIN', 'ADMIN_TROLL', 'NEWTROLL', 'SECRET_ADMIN',
            'staffbattle', 'NOEXPLOIT', 'NOOB2ADMIN', 'CODESLIDE', 'fruitconcepts'
        }
        for X, X in h do
            SetTask("MainTask", 'Code Redemption | ' .. X .. ' | Redeeming...')
            local h = (Remotes.Redeem:InvokeServer(X))
            task.wait()
            SetTask('MainTask', 'Code Redemption | ' .. X .. " | " .. (h or "Failed"))
            local ExpBoost = 0
            pcall(function()
                ExpBoost = getsenv(game.ReplicatedStorage.GuideModule)._G.ServerData.ExpBoost or 0
            end)

            if ExpBoost == 0 then
                if h and string.find(h, 'SUCC') then
                    return SetTask('MainTask', 'Code Redemption | X2 Exp Boost Activated!') and task.wait(1)
                end
            else
                return
            end
        end
        Storage:Set("IsCodesRanOut", 1)
        Storage:Save()
    end)
    FunctionsHandler.SniperFruit:RegisterMethod("Refresh", function()
        if not getgenv().Studio["Blox Fruit"]["Sub"]["Sniper Fruit"]["Enabled"] or ScriptStorage.PlayerData.DevilFruit ~= '' then return end

        local W = getgenv().Studio["Blox Fruit"]["Sub"]["Sniper Fruit"]["Fruit"]
        if not W or #W == 0 then return end

        -- RefreshTasksData runs every ~0.15s and SniperFruit is first in TasksOrder, so without
        -- a debounce this fired 2 InvokeServer("GetFruits") calls every single tick, forever.
        if os.time() - (FunctionsHandler.SniperFruit:Get('LastCheck') or 0) < 3 then return end
        FunctionsHandler.SniperFruit:Set('LastCheck', os.time())

        local a = Remotes.CommF_:InvokeServer("GetFruits", true)
        for h, X in pairs(a) do
            if X["OnSale"] == true then
                for w, D in pairs(W) do
                    if X["Name"] == D and ScriptStorage.PlayerData.Beli >= X["Price"] then
                        return { fruit = X, stockType = "Mirage" }
                    end
                end
            end
        end

        local h = Remotes.CommF_:InvokeServer("GetFruits", false)
        for y, L in pairs(h) do
            if L["OnSale"] == true then
                for b, C in pairs(W) do
                    if L["Name"] == C and ScriptStorage.PlayerData.Beli >= L["Price"] then
                        return { fruit = L, stockType = "Basic" }
                    end
                end
            end
        end

        return nil
    end)
    FunctionsHandler.SniperFruit:RegisterMethod("Start", function(W)
        if not getgenv().Studio["Blox Fruit"]["Sub"]["Sniper Fruit"]["Enabled"] or ScriptStorage.PlayerData.DevilFruit ~= '' then return end
        if not W or not W.fruit then return end

        local a = W.fruit
        local h = W.stockType

        SetTask("SubTask", "Sniper Fruit - Buying " .. a["Name"] .. " (" .. h .. " Stock)")

        local X = Remotes.CommF_:InvokeServer("PurchaseRawFruit", a["Name"])

        if X then
            alert("Sniper Fruit", "Bought " .. a["Name"] .. " for " .. Price(a["Price"]) .. " Beli")
            RefreshPlayerData()
            RefreshInventory()
        end
    end)
    FunctionsHandler.LevelFarm:RegisterMethod("Refresh", function()
        -- Once Godhuman is obtained, step aside for CursedDualKatana/SoulGuitar (Skull Guitar) -
        -- they're earlier in TasksOrder already, but LevelFarm's Refresh always returned
        -- something (never nil), so it kept winning ties whenever those two had nothing to do
        -- for that specific tick. Only resume LevelFarm once BOTH are already owned too (nothing
        -- else left to chase).
        if ScriptStorage.Melees.Godhuman and not (ScriptStorage.Backpack['Cursed Dual Katana'] and ScriptStorage.Backpack['Skull Guitar']) then
            return
        end
        -- J's quest-follower (state 4 below) reads the game's real ReplicatedStorage.Quests
        -- data, which already has entries from Level 0 (BanditQuest1, JungleQuest @10,
        -- BuggyQuest1 @30, DesertQuest @60, SnowQuest @90, ...) - it picks the right chain for
        -- whatever level the account is at on its own. The old h<50/h<70 branches instead sent
        -- fresh accounts to fight Sky Bandit (a Level ~150 enemy) and God's Guard (Level ~450)
        -- respectively - both far above what a Level 1-69 character can survive, and neither
        -- is an actual early-game farm spot. State 4 covers every level correctly, so it's the
        -- only branch needed now.
        return 4
    end)
    FunctionsHandler.LevelFarm:RegisterMethod("Start", function(h)
        if SeaIndex == 3 then
            if (ScriptStorage.Backpack.Bones or { Count = 0 }).Count >= 50 then
                if os.time() > (BonesCooldown or 0) then
                    local X, X, X, w = Remotes.CommF_:InvokeServer("Bones", 'Check')
                    if tonumber(X or 1) == 0 then
                        local X = Split(w, ":")
                        local w = ((tonumber(X[1]) * 60) + tonumber(X[2])) * 60
                        BonesCooldown = os.time() + w
                    else
                        Remotes.CommF_:InvokeServer('Bones', 'Buy', 1, 1)
                    end
                end
            end
        end
        local X = ScriptStorage.PlayerData.Level
        if GodHumanFlag then
            local w, D = (function()
                getgenv()[" mphm ><<3"] = {}
                for y, L in GodhumanMaterials do
                    if (ScriptStorage.Backpack[y] or { Count = 0 }).Count < L[1] then
                        getgenv()[' mphm >< <3'] = { y, L }
                    end
                end
                return unpack(getgenv()[" mphm >< <3"])
            end)()
            if w then
                if SeaIndex ~= D[2] then
                    alert('Material - ' .. w, "Travelling sea " .. D[2])
                    SetTask("MainTask", 'Sea Travel | Godhuman Materials | Travelling to Sea ' .. D[2])
                    Remotes.CommF_:InvokeServer("Travel" .. SeaIndexes[D[2]])
                    task.wait(3)
                    return
                end
                SetTask("MainTask", "Material Farming | Godhuman | " .. w .. " | In Progres")
                if X >= D[4][3] then
                    local w, y = GetCurrentClaimQuest()
                    if w then
                        if not string.find(y, D[3][1]) and not string.find(y, D[3][2]) then
                            J.AbandonQuest()
                        else
                            CombatController.Attack(D[3]); return
                        end
                    else
                        local w = ScriptStorage.NPCs[D[4][4]]
                        w = w and w:GetModelCFrame()
                        if w then
                            TweenController.Create(w + Vector3.new(0, 5, 3))
                            if CaculateDistance(w) < 10 then
                                task.wait(1)
                            else
                                return
                            end
                        else
                            Report("NPC HauntedQuest2 not found")
                        end
                        J.StartQuest(D[4][1], D[4][2])
                        return
                    end
                end
                CombatController.Attack(D[3])
            end
            Remotes.CommF_:InvokeServer("BuyGodhuman", true)
            Remotes.CommF_:InvokeServer("BuyGodhuman")
            GodHumanFlag = false
            return true
        end
        if getgenv().Studio["Blox Fruit"]["Items"]["Material"]["Mirror Fractal"] then
            if ScriptStorage.Tools['God\'s Chalice'] and not ScriptStorage.Tools['Mirror Fractal'] then
                if (ScriptStorage.Backpack["Conjured Cocoa"] or { Count = 0 }).Count < 10 then
                    SetTask("MainTask", "Material Farming | Conjured Cocoa | Need 10x | Farming...")
                    CombatController.Attack({ "Cocoa Warrior", "Chocolate Bar Battler" })
                    return
                end
                Remotes.CommF_:InvokeServer("SweetChaliceNpc")
            end
            if ScriptStorage.Tools['Sweet Chalice'] or (X == MaxLevel and (ScriptStorage.Backpack.Bones or { Count = 0 }).Count >= 500) then
                SetTask("MainTask", "Fragments Farming | Cake Prince | Dough King")
                if (ScriptStorage.Tools["Sweet Chalice"]) and (not SpawnReflect or os.time() - SpawnReflect > 10) then
                    task.spawn(function()
                        while not ScriptStorage.Enemies['Dough King'] and task.wait() and ScriptStorage.Tools["Sweet Chalice"] do
                            SpawnReflect = os.time()
                            Remotes.CommF_:InvokeServer("CakePrinceSpawner")
                        end
                    end)
                end

                if ScriptStorage.Enemies['Dough King'] then
                    CombatController.Attack({ "Dough King" })
                else
                    if getgenv().Premium then
                        if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Select Hop"]["Hop Find Dough King"] then
                            SetTask("MainTask", "Mirror Fractal | Hopping for Dough King...")
                            alert("Mirror Fractal", "Không tìm thấy Dough King → Hopping...")
                            task.spawn(function()
                                Duma("Dough King")
                            end)
                        end
                    else
                        CombatController.Attack({ "Head Baker", 'Baking Staff', 'Cookie Crafter', "Cake Guard" })
                    end
                end

                if X >= 2200 then
                    local w, D = GetCurrentClaimQuest()
                    if w then
                        if not string.find(D, "Cookie") then
                            J.AbandonQuest()
                        else
                            Remotes.CommF_:InvokeServer('CakePrinceSpawner'); return
                        end
                    else
                        local w = ScriptStorage.NPCs["Cake Quest Giver 1"]
                        w = w and w:GetModelCFrame()
                        if w then
                            TweenController.Create(w + Vector3.new(0, 5, 3))
                            if CaculateDistance(w) < 10 then
                                task.wait(1)
                            else
                                return
                            end
                        else
                            Report("NPC HauntedQuest2 not found")
                        end
                        J.StartQuest("CakeQuest1", 1)
                        return
                    end
                end
                return
            end
        end
        if X >= 2025 and (getsenv(game.ReplicatedStorage.GuideModule)._G.ServerData.ExpBoost == 0 or X <= MaxLevel) and (ScriptStorage.Backpack.Bones or { Count = 0 }).Count < 500 then
            SetTask('MainTask', "Resource Farming | Bones | For X2 Mastery/Beli")
            CurrentClaimQuest3 = GetCurrentClaimQuest(true)
            if CurrentClaimQuest3 then
                if not string.find(CurrentClaimQuest3, 'Demonic') then
                    J.AbandonQuest(); return
                else
                    CombatController.Attack({ 'Reborn Skeleton', "Living Zombie", "Demonic Soul", 'Posessed Mummy' }); return
                end
            else
                local X = ScriptStorage.NPCs["Haunted Castle Quest Giver 2"]
                X = X and X:GetModelCFrame()
                if X then
                    TweenController.Create(X + Vector3.new(0, 5, 3))
                    if CaculateDistance(X) < 20 then
                        task.wait(1)
                    else
                        return
                    end
                else
                    Report("NPC HauntedQuest2 not found")
                end
                J.StartQuest('HauntedQuest2', 1)
                return
            end
        end
        if h == 4 then
            local h, X, w, D, y = J:GetCurrentQuest()
            CurrentClaimQuest1 = GetCurrentClaimQuest()
            SetTask('MainTask', 'Level Farming | Level ' .. tostring(ScriptStorage.PlayerData.Level) .. ' | ' .. tostring(h))
            if CurrentClaimQuest1 then
                if CurrentClaimQuest1 ~= y and CurrentClaimQuest1 ~= (y .. "s") then
                    SetTask('SubTask', 'Wrong quest active - abandoning')
                    return J.AbandonQuest()
                end
            else
                if not X then return J:RefreshQuest() and Report("failed to get npc position quest 528") end
                TweenController.Create(X + Vector3.new(0, 5, 3))
                SetTask("SubTask", "Claiming Quest")
                if CaculateDistance(X) > 10 then return end
                task.wait(2)
                LevelFarmTTL = 0
                J.StartQuest(w, D)
                task.wait(1)
            end
            SetTask('SubTask', "Defeating " .. tostring(h))
            local X = os.time()
            CombatController.Attack(h)
            LevelFarmTTL = LevelFarmTTL + os.time() - X
            if LevelFarmTTL > 160 then end
        end
    end)
    FunctionsHandler.LocalPlayerController:RegisterMethod("EquipTool", function(h)
        if not Humanoid then return end
        for X, X in LocalPlayer.Backpack:GetChildren() do
            if X:IsA('Tool') and X.Name ~= "Tool" and (X.Name == tostring(h) or X.ToolTip == h) then
                LocalPlayer.Character:WaitForChild('Humanoid'):EquipTool(X)
            end
        end
    end)
    FunctionsHandler.LocalPlayerController:RegisterMethod('ToggleAbilities', function(h, X)
        if h == 'Buso' then
            if LocalPlayer:HasTag('Buso') and not X or X then Remotes.CommF_:InvokeServer('Buso') end
        elseif h == "Observation" then
        end
    end)
    FunctionsHandler.LocalPlayerController:RegisterMethod('ConfigurationAbilitiesToggle', function()
        FunctionsHandler.LocalPlayerController.Methods.ToggleAbilities:Call('Buso', SCRIPT_CONFIG.BUSO)
        FunctionsHandler.LocalPlayerController.Methods.ToggleAbilities:Call('Observation', SCRIPT_CONFIG.OBSERVATION)
    end)
    FunctionsHandler.Saber:RegisterMethod('Refresh', function()
        if SeaIndex ~= 1 then return end
        if not getgenv().Studio["Blox Fruit"]["Items"]["Sword"]["Saber"] then return end
        local h
        if ScriptStorage.Backpack.Saber then return end
        if ScriptStorage.PlayerData.Level < 200 then return end
        local X = Remotes.CommF_:InvokeServer('ProQuestProgress')
        for w, w in X.Plates do if w == false then h = 1 end end
        if not h then
            if not X.UsedTorch then
                h = 2
            elseif not X.UsedCup then
                h = 3
            elseif not X.TalkedSon then
                h = 4
            elseif not X.KilledMob then
                h = 5
            elseif not X.UsedRelic then
                h = 6
            elseif not X.KilledShanks and ScriptStorage.Enemies["Saber Expert"] then
                h = 7
            end
        end
        FunctionsHandler.Saber:Set("CurrentProgressLevel", h)
        FunctionsHandler.Saber:Set('LastestRefreshSenque', os.time())
        return h
    end)
    FunctionsHandler.Saber:RegisterMethod('GetQuestplates', function()
        local h = FunctionsHandler.Saber:Get("QuestplatesCache")
        if h then return h end
        local h = Services.Workspace.Map.Jungle
        local X = {}
        table.foreach(h.QuestPlates:GetChildren(),
            function(h, w) h = w:FindFirstChild("Button") and table.insert(X, w) end)
        FunctionsHandler.Saber:Get('QuestplatesCache', X)
        return X
    end)
    FunctionsHandler.Saber:RegisterMethod('Start', function()
        local h, X = FunctionsHandler.Saber:Get("CurrentProgressLevel"),
            FunctionsHandler.Saber:Get('LastestRefreshSenque')
        if not h then
            FunctionsHandler.Saber.Methods.Refresh:Call()
            return FunctionsHandler.Saber.Methods.Start:Call()
        elseif h == 0 then
        elseif os.time() - X > 60 then
            FunctionsHandler.Saber.Methods.Refresh:Call()
            return FunctionsHandler.Saber.Methods.Start:Call()
        else
            if h == 1 then
                local X = FunctionsHandler.Saber.Methods.GetQuestplates:Call()
                for w, D in X do
                    SetTask('MainTask', "Saber Quest | Quest Plates | Touching " .. w .. "/5")
                    while CaculateDistance(D.Button.CFrame) > 20 do
                        task.wait()
                        TweenController.Create(D.Button.CFrame)
                    end
                    task.wait(1)
                end
            elseif h == 2 then
                SetTask('MainTask', 'Saber Quest | Torch Puzzle | Using Torch')
                Remotes.CommF_:InvokeServer("ProQuestProgress", 'GetTorch')
                task.wait(1)
                Remotes.CommF_:InvokeServer('ProQuestProgress', "DestroyTorch")
            elseif h == 3 then
                SetTask('MainTask', "Saber Quest | Sick Man | Helping with Cup")
                Remotes.CommF_:InvokeServer('ProQuestProgress', "GetCup")
                if ScriptStorage.Tools.Cup then
                    FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Cup')
                    task.wait(1)
                    Remotes.CommF_:InvokeServer("ProQuestProgress", 'FillCup', LocalPlayer.Character.Cup)
                end
                Remotes.CommF_:InvokeServer("ProQuestProgress", 'SickMan')
            elseif h == 4 then
                SetTask('MainTask', 'Saber Quest | Rich Son | Getting Information')
                Remotes.CommF_:InvokeServer('ProQuestProgress', 'RichSon')
            elseif h == 5 then
                SetTask("MainTask", "Saber Quest | Mob Leader | Defeating Boss")
                CombatController.Attack('Mob Leader')
            elseif h == 6 then
                SetTask("MainTask", 'Saber Quest | Relic | Placing at Location')
                Remotes.CommF_:InvokeServer('ProQuestProgress', 'RichSon')
                Remotes.CommF_:InvokeServer("ProQuestProgress", "PlaceRelic")
            elseif h == 7 then
                SetTask('MainTask', "Saber Quest | Saber Expert | Final Battle")
                CombatController.Attack("Saber Expert")
            end
        end
    end)
    Remotes.RefreshQuestPro.OnClientEvent:Connect(FunctionsHandler.Saber.Methods.Refresh.Callback)
    -- If Thunder God isn't up right now, don't hop hunting for it - just skip this tick and let
    -- whatever else is actually ready (Saber, SecondSeaPuzzle, farming, ...) run instead. Only
    -- act on Pole opportunistically when the boss already happens to be present.
    FunctionsHandler.Pole:RegisterMethod('Refresh', function()
        if SeaIndex ~= 1 then return end
        if ScriptStorage.Backpack["Pole (1st Form)"] then return end
        if ScriptStorage.PlayerData.Level < 500 then return end
        if not ScriptStorage.Enemies["Thunder God"] then return end

        FunctionsHandler.Pole:Set('LastestRefreshSenque', os.time())
        return true
    end)

    FunctionsHandler.Pole:RegisterMethod('Start', function()
        SetTask('MainTask', "Pole Quest | Defeating Thunder God")
        CombatController.Attack("Thunder God")
    end)
    MeleeLastCursor = 1
    FirstCall = true
    CanPurchase = {}
    FunctionsHandler.MeleesController:RegisterMethod('Start', function()
        for h, X in MeleesTable do
            if X ~= "SanguineArt" then
                if not getgenv().Studio["Blox Fruit"]["Items"]["Melee"]["Fighting Style"] then break end
                Data = MeleePrices[X]
                if not Data then
                    break
                end
                -- This pre-check ran Data.Buy(1) - a REAL purchase attempt, not a dry-run -
                -- unconditionally every tick for whichever melee the loop was on, even ones
                -- already fully mastered. For Dragon Claw specifically, Buy() only uses the
                -- correct BlackbeardReward remote when standing right next to the Sabi NPC;
                -- otherwise it silently falls back to a nonexistent "BuyDragonClaw" remote,
                -- which always fails, so CanPurchase[X] never cached true and this call kept
                -- firing every single tick forever even with Dragon Claw already at 400+
                -- mastery. Skip this whole pre-check once the melee is already complete.
                local alreadyMastered = ScriptStorage.Melees[X] and ScriptStorage.Melees[X] >= Data.NextLevelRequirement
                local w = CanPurchase[X]
                if not w and not alreadyMastered then
                    CanPurchase[X] = Data.Buy(1)
                end
                local w = CanPurchase[X]
                if X == "Dragon Talon" then
                    IsFireEssenceGave = (function()
                        if IsFireEssenceGave ~= nil then return IsFireEssenceGave end
                        local D = Remotes.CommF_:InvokeServer('BuyDragonTalon', true)
                        alert('Dragon Talon Purchased', tostring(typeof(D) ~= "string"))
                        return typeof(D) ~= 'string' and true or false
                    end)()
                    if not IsFireEssenceGave then
                        break
                    end
                end
                if X == 'Godhuman' and not GodHumanFlag then
                    if (ScriptStorage.Melees['Dragon Talon'] or 0) > 399 then
                        if not ScriptStorage.Melees.Godhuman then
                            Remotes.CommF_:InvokeServer("BuyGodhuman", true)
                            Remotes.CommF_:InvokeServer('BuyGodhuman')
                            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Melee')
                            if not ScriptStorage.Melees.Godhuman then
                                GodHumanFlag = true
                                return
                            end
                        end
                    end
                end
                if not ScriptStorage.Melees[X] or (ScriptStorage.Melees[X] or 0) < Data.NextLevelRequirement then
                    local D = GetMeleeIdByName(X)
                    local y = ScriptStorage.PlayerData
                    local L = true
                    if not D then return end
                    MSet = false
                    if not w then
                        for w, D in Data.Price do
                            if y[w] < D and not FirstCall then
                                L = false
                                if not ScriptStorage.Melees[X] then
                                    MSet = true
                                    SetTask('SubTask', "Farming Until Enough " .. w .. " ( " .. D .. ' ) For ' .. X)
                                end
                                return
                            end
                        end
                    end
                    if not MSet and ScriptStorage.Melees[X] and ScriptStorage.Melees[X] < Data.NextLevelRequirement then
                        SetTask('SubTask',
                            "Farming Until Enough Mastery For " ..
                            X .. ' ( ' .. ScriptStorage.Melees[X] .. ' / ' .. Data.NextLevelRequirement .. " )")
                        if not ScriptStorage.Tools[X] then
                            Data.Buy()
                        end
                        return
                    end
                    if not FirstCall then
                        if L and Data.Requirements() and not ScriptStorage.Tools[X] then
                            if X == "Dragon Talon" and not IsFireEssenceGave then
                                alert('IsFireEssenceGave', tostring(IsFireEssenceGave))
                                return SetTask("SubTask", 'Waiting until have fire essence for dragon talon.')
                            end
                            Data.Buy()
                            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Melee')
                            if not ScriptStorage.Tools[X] then
                                task.wait()
                                if not ScriptStorage.Tools[X] then
                                    -- Both Death Step (Phoeyu, the Reformed) and Sharkman Karate
                                    -- (Sharkman Teacher) have their teacher NPC in EITHER sea -
                                    -- Second Sea's Ice Castle/Forgotten Island AND Third Sea's
                                    -- Castle on the Sea (confirmed via wiki). Forcing a travel
                                    -- back to Second Sea here was wrong and fought SeaTravel's
                                    -- push toward Third Sea, causing the two to fight each other
                                    -- back and forth. Just let the normal retry cycle handle it.
                                else
                                    MeleeLastCursor = h + 1
                                    return
                                end
                            else
                                MeleeLastCursor = h + 1
                                return
                            end
                        end
                    elseif not FirstCall then
                        MeleeLastCursor = h + 1
                    end
                end
            end
        end
        if FirstCall then
            FirstCall = false
            return
        end
        FarmingItem = nil
        for h, h in ScriptStorage.Backpack do
            if h.Type == "Sword" then
                if h.Name == 'Yama' or h.Name == "Tushita" then
                    MasteryRequirement = 350
                else
                    for X, X in h.MasteryRequirements do MasteryRequirement = X end
                end
                if h.Mastery < MasteryRequirement then
                    if h.Name == "Yama" or h.Name == "Tushita" then
                        FarmingItem = { h.Name, h.Mastery, MasteryRequirement }
                        break
                    end
                end
            end
        end
        if FarmingItem then
            SetTask("SubTask",
                "Farming mastery for " .. FarmingItem[1] .. " ( " .. FarmingItem[2] .. " / " .. FarmingItem[3] .. " )")
            if not ScriptStorage.Tools[FarmingItem[1]] then Remotes.CommF_:InvokeServer("LoadItem", FarmingItem[1]) end
            ScriptStorage.ForceToUseSword = FarmingItem
        end
    end)
    FunctionsHandler.SecondSeaPuzzle:RegisterMethod('Refresh', function()
        if SeaIndex ~= 1 then return end
        if ScriptStorage.PlayerData.Level < 700 then return end
        if ScriptStorage.Backpack['Warrior Helmet'] then
            FunctionsHandler.SecondSeaPuzzle:Set("IsCompleted", true)
            return
        end

        local progress = Remotes.CommF_:InvokeServer("DressrosaQuestProgress")
        if not progress then return end

        local state = 1
        if progress.UsedKey == true and progress.KilledIceBoss == false then
            state = 2
        elseif progress.KilledIceBoss == true then
            state = 3
        end

        FunctionsHandler.SecondSeaPuzzle:Set("CurrentProgressLevel", state)
        FunctionsHandler.SecondSeaPuzzle:Set("QuestProgress", progress)
        FunctionsHandler.SecondSeaPuzzle:Set('LastestRefreshSenque', os.time())

        return state
    end)

    FunctionsHandler.SecondSeaPuzzle:RegisterMethod('Start', function()
        local state = FunctionsHandler.SecondSeaPuzzle:Get("CurrentProgressLevel")
        local progress = FunctionsHandler.SecondSeaPuzzle:Get("QuestProgress") or {}

        if not state then
            FunctionsHandler.SecondSeaPuzzle.Methods.Refresh:Call()
            return
        end

        if state == 1 then
            SetTask("MainTask", "Auto Second Sea | Talking to Detective")
            Remotes.CommF_:InvokeServer("DressrosaQuestProgress", "Detective")

            task.wait(1)

            if not ScriptStorage.Tools["Key"] and not ScriptStorage.Backpack["Key"] then
                SetTask("SubTask", "Getting Key...")
                TweenController.Create(CFrame.new(4852.2895507813, 5.651451587677, 718.53070068359))
            else
                SetTask("SubTask", "Using Key...")
                FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call("Key")

                TweenController.Create(game.Workspace.Map.Ice.Door.CFrame)
                task.wait(2)
                Remotes.CommF_:InvokeServer("DressrosaQuestProgress", "Detective")
            end
        elseif state == 2 then
            SetTask("MainTask", "Auto Second Sea | Defeating Ice Admiral")

            local iceAdmiral = workspace.Enemies:FindFirstChild("Ice Admiral") or
                game.ReplicatedStorage:FindFirstChild("Ice Admiral")

            if iceAdmiral then
                CombatController.Attack("Ice Admiral")
            else
                TweenController.Create(CFrame.new(4852.2895507813, 5.651451587677, 718.53070068359))
            end
        elseif state == 3 then
            SetTask("MainTask", "Auto Second Sea | Completing Quest & Traveling...")

            Remotes.CommF_:InvokeServer("DressrosaQuestProgress", "Detective")
            task.wait(1.5)

            Remotes.CommF_:InvokeServer("TravelDressrosa")
            task.wait(3)

            FunctionsHandler.SecondSeaPuzzle:Set("IsCompleted", true)
            alert("Second Sea", "Đã chuyển sang Second Sea thành công!")
        end
    end)
    FunctionsHandler.ColosseumPuzzle:RegisterMethod("Refresh", function()
        if SeaIndex ~= 2 then return end
        if ScriptStorage.PlayerData.Level < 850 or ScriptStorage.Backpack['Warrior Helmet'] then return end
        -- Same fix as SniperFruit: don't hit the server every ~0.15s tick while waiting on this.
        if os.time() - (FunctionsHandler.ColosseumPuzzle:Get('LastCheck') or 0) < 3 then return end
        FunctionsHandler.ColosseumPuzzle:Set('LastCheck', os.time())
        local k = Remotes.CommF_:InvokeServer("BartiloQuestProgress")
        if not k.KilledBandits then
            Result = 1
        elseif not k.KilledSpring then
            if ScriptStorage.Enemies.Jeremy then Result = 2 end
        elseif not k.DidPlates then
            Result = 3
        end
        FunctionsHandler.ColosseumPuzzle:Set("CurrentProgressLevel", Result)
        FunctionsHandler.ColosseumPuzzle:Set("LastestRefreshSenque", os.time())
        return Result
    end)
    FunctionsHandler.ColosseumPuzzle:RegisterMethod('Start', function()
        local k, h = FunctionsHandler.ColosseumPuzzle:Get("CurrentProgressLevel"),
            FunctionsHandler.ColosseumPuzzle:Get("LastestRefreshSenque")
        FunctionsHandler.ColosseumPuzzle:Set("CurrentProgressLevel", nil)
        if not k then
            FunctionsHandler.ColosseumPuzzle.Methods.Refresh:Call()
            return FunctionsHandler.ColosseumPuzzle.Methods.Start:Call()
        elseif k == 1 then
            SetTask("MainTask", 'Auto Bartilo Quest - Defeating 50x Swan Pirate')
            local h, X = J:GetCurrentClaimQuest()
            if h then
                if not string.find(X, '50') then
                    J.AbandonQuest()
                else
                    CombatController.Attack("Swan Pirate")
                end
            else
                J.StartQuest('BartiloQuest', 1)
            end
        elseif k == 2 then
            SetTask('MainTask', "Auto Bartilo Quest - Defeating Jeremy")
            CombatController.Attack("Jeremy")
        elseif k == 3 then
            SetTask("MainTask", 'Auto Bartilo Quest - Doing Puzzle')
            if CaculateDistance(CFrame.new(-1837.46155, 44.2921753, 1656.1987, 0.999881566, -1.03885048e-22, -0.0153914848, 1.07805858e-22, 1, 2.53909284e-22, 0.0153914848, -2.55538502e-22, 0.999881566)) > 10 then
                alert("tween to")
                TweenController.Create(CFrame.new(-1837.46155, 44.2921753, 1656.1987, 0.999881566, -1.03885048e-22,
                    -0.0153914848, 1.07805858e-22, 1, 2.53909284e-22, 0.0153914848, -2.55538502e-22, 0.999881566))
            else
                LocalPlayer = game.Players.LocalPlayer
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1836.0, 11, 1714)
                alert("1")
                task.wait(.5)
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1850.49329, 13.1789551, 1750.89685)
                alert('2')
                task.wait(1)
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1858.87305, 19.3777466, 1712.01807)
                alert("3")
                task.wait(1)
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1803.94324, 16.5789185, 1750.89685)
                task.wait(1)
                alert("4")
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1858.55835, 16.8604317, 1724.79541)
                task.wait(1)
                alert('5')
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1869.54224, 15.987854, 1681.00659)
                task.wait(1)
                alert("6")
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1800.0979, 16.4978027, 1684.52368)
                task.wait(1)
                alert("7")
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1819.26343, 14.795166, 1717.90625)
                task.wait(1)
                alert("8")
                LocalPlayer.Character.HumanoidRootPart.CFrame = CFrame.new(-1813.51843, 14.8604736, 1724.79541)
            end
        end
    end)
    -- Status codes for Remotes.CommF_:InvokeServer("Alchemist", "1") confirmed via decompile
    -- (ReplicatedStorage.DialoguesList, Arowe's V2 dialogue function f28): -2 = already V2,
    -- -1 = under $500,000, 0 = quest not accepted yet (need "2" to accept), 1 = quest accepted -
    -- go get the 3 flowers, 2 = flowers turned in, ready to pay via "3". Real in-game cost is
    -- still $500,000 (server-side), but only attempt with 2,500,000+ banked as a safety margin
    -- per user request, and require Level Max + Colosseum Quest done (Warrior Helmet - the
    -- actual unlock gate for talking to Alchemist at all, confirmed via wiki) rather than the
    -- old Lv.900 floor.
    FunctionsHandler.EvoRace:RegisterMethod("Refresh", function()
        if not getgenv().Studio["Blox Fruit"]["Sub"]["Pull Lever"] then return end
        if getsenv(game.ReplicatedStorage.GuideModule)._G.ServerData.ExpBoost ~= 0 or ScriptStorage.PlayerData.Level < MaxLevel or ScriptStorage.PlayerData.Beli < 2500000 or not ScriptStorage.Backpack['Warrior Helmet'] or ScriptStorage.PlayerData.RaceLevel ~= 1 then return end
        return true
    end)
    FunctionsHandler.EvoRace:RegisterMethod('Start', function()
        -- Alchemist (V1->V2) only lives in Sea 2 - if a farming task already pushed us to
        -- Sea 1/3, hop back to Dressrosa first instead of sitting there doing nothing.
        if SeaIndex ~= 2 then
            SetTask('MainTask', 'Auto Race V2 - Teleporting to Sea 2')
            Remotes.CommF_:InvokeServer("TravelDressrosa")
            task.wait(3)
            return
        end
        -- Blue Flower only spawns at night and despawns at day - hop for a night server
        -- BEFORE farming instead of sitting stuck waiting for it to appear in daytime.
        if not (ScriptStorage.Tools["Flower 1"] and ScriptStorage.Tools["Flower 2"]) and not CheckNight() then
            SetTask('MainTask', 'Auto Race V2 - Hopping for Night ( Blue Flower )')
            LowHop("Singapore")
            return
        end
        local v = Remotes.CommF_:InvokeServer('Alchemist', "1")
        if v == -1 then
            SetTask('MainTask', 'Auto Race V2 - Needs 500,000 Beli')
            return
        elseif v == 0 then
            SetTask('MainTask', 'Auto Race V2 - Accepting Quest')
            Remotes.CommF_:InvokeServer('Alchemist', '2')
            return
        elseif v == 2 then
            SetTask("MainTask", 'Auto Race V2 - Idling')
            if LocalPlayer.Character.HumanoidRootPart.CFrame.Y < 50000 then
                TweenController.Create(LocalPlayer.Character.HumanoidRootPart.CFrame + Vector3.new(0, 50, 0))
            end
            Remotes.CommF_:InvokeServer("Alchemist", "3")
            RefreshRace()
            return
        end
        -- v == 1: quest accepted, go collect the 3 flowers
        for k = 1, 2, 1 do
            local h = ScriptStorage.Tools["Flower " .. k]
            local X = Services.Workspace:FindFirstChild('Flower' .. k)
            if not h then
                if X and X.Transparency == 0 then
                    SetTask('MainTask', 'Auto Race V2 - Collecting Flower ' .. k)
                    while not ScriptStorage.Tools["Flower " .. k] do
                        task.wait()
                        TweenController.Create(X.CFrame + Vector3.new(0, math.random(-1.0, 2), 0))
                    end
                end
            end
        end
        if not ScriptStorage.Tools['Flower 3'] then
            SetTask('MainTask', 'Auto Race V2 - Collecting Flower ' .. 3)
            CombatController.Attack('Swan Pirate')
        end
    end)
    FunctionsHandler.BossesTask:RegisterMethod("Refresh", function()
        local k
        for h, h in BossesOrder do
            local X = BossesOrderLevel[h]
            if ScriptStorage.PlayerData.Level >= X then
                local X = ScriptStorage.Enemies[h]
                if X and X:FindFirstChild("Humanoid") and X.Humanoid.Health > 0 then k = X end
            end
        end
        if k and (CaculateDistance(k.HumanoidRootPart.CFrame) < (SeaIndex == 2 and 3000 or 5000) or BossesOrderWL[tostring(k)] or ScriptStorage.PlayerData.Level == MaxLevel) then
            return k
        end
    end)
    FunctionsHandler.BossesTask:RegisterMethod('Start', function(k)
        if k then
            SetTask("MainTask", "Auto Farm Boss - Defeating " .. k.Name)
            CombatController.Attack(tostring(k), null, null, function() SpecialItems = nil end)
            SpecialItems = nil
        end
    end)
    FunctionsHandler.SpecialBossesTask:RegisterMethod('Refresh', function()
        local k
        for h, X in SpecialBossesOrder do
            if ScriptStorage.PlayerData.Level >= X then
                local X = ScriptStorage.Enemies[h]
                if X and X:FindFirstChild('Humanoid') and X.Humanoid.Health > 0 then k = X end
            end
        end
        return k
    end)
    FunctionsHandler.SpecialBossesTask:RegisterMethod('Start', function(k)
        if FunctionsHandler.RaidController.Methods.GetCurrentRaidIsland:Call() then
            pcall(function() LocalPlayer.Character.Humanoid.Health = 0 end)
        end
        if k then
            SetTask('MainTask', "Auto Farm Boss - Defeating " .. k.Name)
            CombatController.Attack(tostring(k))
        end
    end)
    FunctionsHandler.RaidController:RegisterMethod('RefreshRaidType', function()
        for k, k in require(game.ReplicatedStorage.Raids).raids do
            if string.find(ScriptStorage.PlayerData.DevilFruit, k) then
                FunctionsHandler.RaidController:Set('CurrentChip', k)
                return
            end
        end
        FunctionsHandler.RaidController:Set('CurrentChip', 'Flame')
    end)
    FunctionsHandler.RaidController:RegisterMethod('GetRaidableFruit', function()
        -- ScriptStorage.Backpack only ever holds stored/spare fruits (the one currently
        -- equipped isn't "in storage"), so every candidate here is already Fruit Du - just
        -- need to pick deterministically. Iterating a hash-keyed table gives an arbitrary
        -- order, so returning on first match picked a seemingly-random <=1M fruit each time;
        -- pick the CHEAPEST eligible one instead so the same, most-sensible fruit gets loaded.
        local w, D = nil, math.huge
        for k, k in ScriptStorage.Backpack do
            if string.find(FruitIdToName(k.Name), " Fruit") and k.Value and k.Value <= 1000000 and k.Value < D then
                w, D = k, k.Value
            end
        end
        return w
    end)
    FunctionsHandler.RaidController:RegisterMethod("GetCurrentRaidIsland", function()
        PlayerPosition = LocalPlayer.Character.HumanoidRootPart.CFrame
        IslandsList = { {}, {}, {}, {}, {} }
        for k, k in workspace['_WorldOrigin'].Locations:GetChildren() do
            if string.find(k.Name, 'Island ') and CaculateDistance(k.Position, Vector3.new(0, 0, 0)) > 7000 then
                (function()
                    local h = string.gsub(k.Name, "Island ", "")
                    local X = tonumber(h)
                    if X and IslandsList[X] then
                        table.insert(IslandsList[X], k)
                    end
                end)()
            end
        end
        do
            for k = 5, 1, -1.0 do
                for h, h in IslandsList[k] do if CaculateDistance(h.Position) < 2000 then return h end end
            end
        end
    end)
    function CheckSpecialMicrochip()
        for _, items in { LocalPlayer.Character:GetChildren(), LocalPlayer.Backpack:GetChildren() } do
            for _, item in items do
                if item.Name == "Special Microchip" then return item end
            end
        end
    end

    FunctionsHandler.RaidController:RegisterMethod("Refresh", function()
        local k = ScriptStorage.PlayerData.Level
        local h = ScriptStorage.PlayerData.Fragments
        if k < 1300 or SeaIndex == 1 then return end
        if k < 1500 and h > 2000 then return end
        if k < MaxLevel then
            if h > 5000 then return end
        else
            if h > 10000 then return end
        end
        local k = FunctionsHandler.RaidController.Methods.GetRaidableFruit:Call()
        if k then FunctionsHandler.RaidController:Set("CurrentProgressLevel", k) end
        return k or FunctionsHandler.RaidController.Methods.GetCurrentRaidIsland:Call() or CheckSpecialMicrochip()
    end)
    FunctionsHandler.RaidController:RegisterMethod("Start", function()
        if not FunctionsHandler.RaidController:Get('CurrentChip') then
            FunctionsHandler.RaidController.Methods
                .RefreshRaidType:Call()
        end
        local k = FunctionsHandler.RaidController.Methods.GetCurrentRaidIsland:Call()
        RefreshInventory()
        FunctionsHandler.RaidController:Set("CurrentProgressLevel", nil)
        if not k then
            SetTask('MainTask', 'Auto Raid - Buying Chip - ' .. FunctionsHandler.RaidController:Get("CurrentChip"))
            if not ScriptStorage.Tools['Special Microchip'] then
                local X = FunctionsHandler.RaidController.Methods.GetRaidableFruit:Call()
                if not X then
                    SetTask('MainTask', 'Auto Raid - No Raidable Fruit Available')
                    return
                end
                table.insert(ScriptStorage.IgnoreStoreFruits, X.Name)
                alert('Load Fruit', X.Name)
                Remotes.CommF_:InvokeServer('LoadFruit', X.Name)
                Remotes.CommF_:InvokeServer("RaidsNpc", 'Select', FunctionsHandler.RaidController:Get('CurrentChip'))
                task.wait(2)
            end
            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Special Microchip')
            -- FindFirstChild instead of dot-indexing: "Boat Castle"/CircleIsland/RaidSummon2
            -- only stream in once close, and direct .Name indexing throws "not a valid member"
            -- when they haven't loaded yet - that error retried every single tick forever and
            -- froze the character in place (never got a chance to move) until the idle-hop
            -- watchdog kicked in.
            if SeaIndex == 2 then
                local w = workspace.Map:FindFirstChild('CircleIsland')
                w = w and w:FindFirstChild('RaidSummon2')
                if w then fireclickdetector(w.Button.Main.ClickDetector) end
            elseif SeaIndex == 3 then
                TweenController.Create(CFrame.new(-5034, 315, -2950))
                local w = workspace.Map:FindFirstChild('Boat Castle')
                w = w and w:FindFirstChild('RaidSummon2')
                if w then fireclickdetector(w.Button.Main.ClickDetector) end
            end
            local h = os.time()
            SetTask("MainTask", "Auto Raid - Waiting Until Raid Is Started")
            repeat task.wait() until os.time() - (LastRaidAlert2 or 0) < 20 or os.time() - h > 30
            TweenController.Create(LocalPlayer.Character.HumanoidRootPart.CFrame)
            repeat task.wait() until os.time() - (LastRaidAlert or 0) < 20 or os.time() - h > 30
            alert('cac', "Tween Paused")
            task.wait(.5)
            if os.time() - h > 30 then
                LowHop("Singapore")
                SetTask('MainTask', "Auto Raid - Raid Is Not Stared?")
                Report('[ Raid Error ] Time Limit Reached')
            end
            LastRaidAlert = 0
        else
            SetTask('MainTask', "Auto Raid - " .. k.Name .. " /5")
            local h = false
            for X, X in GetMonAsSortedRange() do
                local w = os.time()
                while X and X:FindFirstChild("HumanoidRootPart") and X.Humanoid.Health > 0 and CaculateDistance(X.HumanoidRootPart.Position) < 1000 and os.time() - w < 60 and task.wait(.05) do
                    h = true
                    if string.find(X.Name, "Master") or true then
                        CombatController.Attack(X.Name)
                    else
                        pcall(sethiddenproperty, LocalPlayer, 'SimulationRadius', math.huge)
                        pcall(function()
                            X.HumanoidRootPart.CanCollide = false
                            X.Humanoid.Health = 0
                            X:BreakJoints()
                        end)
                    end
                end
            end
            if not h then TweenController.Create(k.Position + Vector3.new(0, 100, 0)) end
        end
    end)
    FunctionsHandler.CollectDrops:RegisterMethod("Refresh", function()
        local k = {}
        for h in ScriptStorage.Backpack do k[FruitIdToName(h)] = h end
        for h, h in workspace:GetChildren() do
            if string.find(h.Name, 'Fruit') and not LocalPlayer.Backpack:FindFirstChild(h.Name) and h:FindFirstChild("Handle") and not k[tostring(h)] and not ScriptStorage.Backpack[FruitNameToId(tostring(h))] then
                FunctionsHandler.CollectDrops:Set('CurrentProgressLevel', h)
                return h
            end
        end
    end)
    FunctionsHandler.CollectDrops:RegisterMethod('Start', function()
        local k = FunctionsHandler.CollectDrops:Get('CurrentProgressLevel')
        FunctionsHandler.CollectDrops:Set('CurrentProgressLevel', nil)
        if k then
            SetTask("MainTask", "Auto Collect Drop Items - " .. tostring(k))
            TweenController.Create(k:GetModelCFrame())
        end
    end)

    -- Berry bushes are tagged "BerryBush"; once a bush is close enough its berries stream in
    -- as Model children with their own ProximityPrompt (used to craft Haki). See BerryBushClient.
    -- Refresh/Start must stay non-blocking (no task.wait loops) - RefreshTasksData runs the whole
    -- TasksOrder synchronously, so a multi-second wait here would freeze every other task/movement.
    -- Instead we lean on the ~0.15s task loop to naturally re-check on the next tick, matching how
    -- the reference "Collect Berry.lua" script just keeps rescanning every frame.
    FunctionsHandler.CollectBerries:RegisterMethod("Refresh", function()
        -- CDK's own Refresh already outranks CollectBerries in TasksOrder, but CDK spends most
        -- ticks mid-combat/mid-tween with a blocking Start call, or momentarily returning nil
        -- between steps (e.g. while walking toward Castle on the Sea before hopping) - during
        -- those gaps CollectBerries could still grab a turn and pull the character away from
        -- whatever CDK trial position it was walking to. Hard-block berries entirely whenever
        -- CDK has real unfinished work (Level/Sea/Tushita/Yama all met, no Cursed Dual Katana
        -- yet) so it never competes with CDK regardless of scheduler timing.
        if ScriptStorage.PlayerData.Level >= 2200 and not ScriptStorage.Backpack['Cursed Dual Katana']
            and ScriptStorage.Backpack.Tushita and ScriptStorage.Backpack.Tushita.Mastery >= 350
            and ScriptStorage.Backpack.Yama and ScriptStorage.Backpack.Yama.Mastery >= 350 then
            return
        end
        for _, k in Services.CollectionService:GetTagged("BerryBush") do
            for _, h in k:GetChildren() do
                if h:FindFirstChildOfClass("ProximityPrompt") then
                    FunctionsHandler.CollectBerries:Set('CurrentProgressLevel', h)
                    return h
                end
            end
            for h, w in pairs(k:GetAttributes()) do
                if h:sub(1, 12) == "_BerryCFrame" and w then
                    FunctionsHandler.CollectBerries:Set('CurrentProgressLevel', k)
                    return k
                end
            end
        end
    end)
    FunctionsHandler.CollectBerries:RegisterMethod('Start', function()
        local k = FunctionsHandler.CollectBerries:Get('CurrentProgressLevel')
        FunctionsHandler.CollectBerries:Set('CurrentProgressLevel', nil)
        if not (k and k.Parent) then return end
        local h = k:FindFirstChildOfClass("ProximityPrompt")
        if h then
            -- k is already the berry Model itself (its own prompt found above).
            SetTask('MainTask', "Auto Collect Berries - " .. tostring(h.ActionText))
            TweenController.Create(k:GetPivot())
            if h.Enabled and k.Parent then
                fireproximityprompt(h, math.huge)
            end
        else
            -- k is the bush's tagged Configuration - only attribute data exists so far,
            -- move closer and let a later Refresh pick up the berry once it streams in.
            SetTask('MainTask', "Auto Collect Berries - Moving To Bush")
            TweenController.Create(k.Parent:GetPivot())
        end
    end)

    FunctionsHandler.UtillyItemsActivitation:RegisterMethod('Refresh', function()
        if os.time() - timeee < 20 then return end
        if not SpecialItems then
            SpecialItems = {}
            local k = {}
            IceAdmiralPassed = true
            if not ScriptStorage.Backpack.Rengoku then
                table.insert(SpecialItems, "Hidden Key")
                IceAdmiralPassed = false
            end
            if SeaIndex == 2 and Services.Workspace.Map.IceCastle.Hall.LibraryDoor:FindFirstChild("PhoeyuDoor") then
                table.insert(SpecialItems, 'Library Key')
                IceAdmiralPassed = false
            end
            if IceAdmiralPassed then table.insert(k, 'Awakened Ice Admiral') end
            local h = not ScriptStorage.Melees['Sharkman Karate'] and
                Remotes.CommF_:InvokeServer("BuySharkmanKarate", true)
            SharkmanPassed = typeof(h) == 'string'
            if typeof(h) == "string" then
                table.insert(SpecialItems, 'Water Key')
            else
                TidePassed = true
                table.insert(k, 'Tide Keeper')
            end
            if ScriptStorage.Backpack.Yama then
                table.insert(k, "Deandre")
                table.insert(k, 'Urban')
                table.insert(k, 'Diablo')
            end
            local function h()
                local X = {}
                for w, w in BossesOrder do
                    local D = true
                    for y, y in k do if y == w then D = false end end
                    if D then table.insert(X, w) end
                end
                local k = #X
                for w = 1, k - 1 do
                    for D = 1, k - w do
                        local k = key and tostring(X[D][key]):lower() or tostring(X[D]):lower()
                        local w = key and tostring(X[D + 1][key]):lower() or tostring(X[D + 1]):lower()
                        if k > w then X[D], X[D + 1] = X[D + 1], X[D] end
                    end
                end
                return X
            end
            BossesOrder = h()
            for k, h in DropItemData do
                if not ScriptStorage.Backpack[k] and SeaIndex == h.Sea then
                    if ScriptStorage.PlayerData.Level >= h.Level then
                        BossesOrderLevel[h.Boss] = h.Level
                        table.insert(BossesOrder, h.Boss)
                    end
                end
            end
            if FunctionsHandler.Trevor:Get("IsCompleted") and not Storage:Get('SwanDefeated') then
                BossesOrderLevel["Don Swan"] = 1100
                -- Don Swan is now just another entry in BossesOrder, farmed opportunistically
                -- by BossesTask when present - no more hopping servers just to hunt it down.
                table.insert(BossesOrder, 'Don Swan')
            end
        end
        for k, k in SpecialItems do
            if ScriptStorage.Tools[k] then
                FunctionsHandler.UtillyItemsActivitation:Set('CurrentProgressLevel', k)
                return k
            end
        end
        if SeaIndex == 3 and (ScriptStorage.Melees["Death Step"] or 0) >= 400 and (ScriptStorage.Melees["Black Leg"] or 0) >= 400 and ScriptStorage.PlayerData.Beli >= 2500000 and ScriptStorage.PlayerData.Fragments >= 5000 and not ScriptStorage.Melees['Electric Claw'] then
            FunctionsHandler.UtillyItemsActivitation:Set('CurrentProgressLevel', "Previous Hero")
            return 'Previous Hero'
        end
        if ScriptStorage.Tools["Red Key"] then
            FunctionsHandler.UtillyItemsActivitation:Set("CurrentProgressLevel", "Red Key")
            return 'Red Key'
        end
        if ScriptStorage.Tools['Hallow Essence'] then
            FunctionsHandler.UtillyItemsActivitation:Set("CurrentProgressLevel", 'Soul Reaper Spawner')
            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call("Fire Essence")
            return "Soul Reaper Spawner"
        end
        if ScriptStorage.Tools['Fire Essence'] then
            FunctionsHandler.UtillyItemsActivitation:Set('CurrentProgressLevel', "Uzoth")
            return 'Uzoth'
        end
    end)
    FunctionsHandler.UtillyItemsActivitation:RegisterMethod('Start', function()
        local k = FunctionsHandler.UtillyItemsActivitation:Get("CurrentProgressLevel")
        if k == 'Hidden Key' then
            Remotes.CommF_:InvokeServer("OpenRengoku")
        elseif k == 'Water Key' then
            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call("Water Key")
            Remotes.CommF_:InvokeServer("BuySharkmanKarate", true)
            Remotes.CommF_:InvokeServer("BuySharkmanKarate")
        elseif k == "Library Key" then
            Remotes.CommF_:InvokeServer("OpenLibrary")
            Services.Workspace.Map.IceCastle.Hall.LibraryDoor:FindFirstChild("PhoeyuDoor"):Destroy()
        elseif k == "Red Key" then
            alert('Red Key', "Submitting red key to the scienctist.")
            Remotes.CommF_:InvokeServer('CakeScientist', "Check")
            ScriptStorage.Tools["Red Key"]:Destroy()
        elseif k == 'Previous Hero' then
            Remotes.CommF_:InvokeServer('BuyElectricClaw', "Start")
            task.wait(3)
            repeat
                task.wait()
                TweenController.Create(CFrame.new(-12548.0, 332.378 + math.random(-2.0, 2), -7617.0))
            until CaculateDistance(CFrame.new(-12548.0, 332.378, -7617.0)) < 30
            Data = MeleePrices["Electric Claw"]
            Data.Buy(1)
            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Melee')
        elseif k == "Uzoth" then
            Remotes.CommF_:InvokeServer("BuyDragonTalon", true)
            Remotes.CommF_:InvokeServer('BuyDragonTalon')
            IsFireEssenceGave = true
            Report("Fire Essence Used")
        elseif k == "Soul Reaper Spawner" then
            if CaculateDistance(workspace.Map["Haunted Castle"].Summoner.Detection.CFrame) < 100 then SpecialItems = nil end
            TweenController.Create(workspace.Map["Haunted Castle"].Summoner.Detection.CFrame)
        end
    end)
    FunctionsHandler.Trevor:RegisterMethod('GetFruit', function()
        for k, k in ScriptStorage.Backpack do
            if string.find(FruitIdToName(k.Name), " Fruit") then
                if k.Value and k.Value > 1000000 and k.Value < 2500000 then return k end
            end
        end
    end)
    FunctionsHandler.Trevor:RegisterMethod('Refresh', function()
        if FunctionsHandler.Trevor:Get('IsCompleted') or os.time() - timeee < 1 then return end
        if ScriptStorage.PlayerData.Level < 1100 then return end
        local k = FunctionsHandler.Trevor.Methods.GetFruit:Call()
        if k then FunctionsHandler.Trevor:Set('Fruit', k) end
        TrevorDebounce = os.time()
        if not FunctionsHandler.Trevor:Get('IsCompleted') then
            FunctionsHandler.Trevor:Set('IsCompleted', (Remotes.CommF_:InvokeServer("TalkTrevor", "1") == 0))
        end
        return not FunctionsHandler.Trevor:Get("IsCompleted") and k
    end)
    FunctionsHandler.Trevor:RegisterMethod("Start", function()
        alert('[ cac ]', "Pulling fruit for trevor...")
        local k = FunctionsHandler.Trevor:Get("Fruit")
        FunctionsHandler.Trevor:Set('Fruit', nil)
        table.insert(ScriptStorage.IgnoreStoreFruits, k.Name)
        Remotes.CommF_:InvokeServer('LoadFruit', k.Name)
        task.wait()
        FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call(FruitIdToName(k.Name))
        Remotes.CommF_:InvokeServer('TalkTrevor', '1')
        Remotes.CommF_:InvokeServer('TalkTrevor', "2")
        Remotes.CommF_:InvokeServer("TalkTrevor", "3")
        task.wait(1)
        FunctionsHandler.Trevor:Set('IsCompleted', true)
    end)
    -- Per the wiki (King Red Head -> rip_indra -> Mr. Captain quest chain at Lv.1500), the
    -- "ZQuestProgress" remote's Check action reports 0 while the quest is still outstanding
    -- and non-zero once it's done - matches the wiki's own account of the milestone check.
    FunctionsHandler.ThirdSeaPuzzle:RegisterMethod("Refresh", function()
        if ScriptStorage.PlayerData.Level < 1500 or SeaIndex ~= 2 then return end
        if FunctionsHandler.ThirdSeaPuzzle:Get('IsCompleted') then return end
        local progress = Remotes.CommF_:InvokeServer("ZQuestProgress", 'Check')
        if progress ~= 0 then
            FunctionsHandler.ThirdSeaPuzzle:Set('IsCompleted', true)
            return
        end
        return true
    end)
    FunctionsHandler.ThirdSeaPuzzle:RegisterMethod('Start', function()
        SetTask('MainTask', "Auto Third Sea | Talking to King Red Head")
        Remotes.CommF_:InvokeServer("ZQuestProgress", "Begin")
        task.wait(2)

        -- Wiki: lower rip_indra to 50% HP to trigger the cutscene - bounded to 2 minutes so a
        -- missing/unreachable NPC can't hang this task forever (the old code looped and force
        -- Kick()'d the player after 30s no matter what, even mid-fight - removed that entirely).
        SetTask('SubTask', "Fighting Rip Indra to 50% HP")
        local w = os.time()
        local k
        repeat
            CombatController.Attack("rip_indra")
            task.wait(.5)
            k = Remotes.CommF_:InvokeServer("ZQuestProgress", "Check")
        until k ~= 0 or os.time() - w > 120

        if k == 0 then
            SetTask('MainTask', "Auto Third Sea | Rip Indra Fight Timed Out")
            return
        end

        SetTask('MainTask', "Auto Third Sea | Milestone Complete")
        alert("Third Sea", "Rip Indra defeated to 50% - talk to Mr. Captain to finish unlocking Third Sea")
        FunctionsHandler.ThirdSeaPuzzle:Set('IsCompleted', true)
    end)
    FunctionsHandler.Yama:RegisterMethod('Refresh', function()
        if SeaIndex ~= 3 then return end
        if ScriptStorage.Backpack.Yama then return end
        -- EliteCount grows over time as Deandre/Urban/Diablo get killed elsewhere (BossesTask),
        -- but this only fetched it once ever and cached whatever it got forever (0 counts as
        -- "already set" in Lua) - a fresh/early call before the account fully synced could
        -- permanently stick this below 30 even once the real count passed it, freezing this
        -- task (and CDK behind it, which needs Yama) with nothing else left to fall back to
        -- once LevelFarm steps aside for Godhuman. Re-check every 5s instead of once.
        if os.time() - (FunctionsHandler.Yama:Get("EliteCountCheckedAt") or 0) > 5 then
            FunctionsHandler.Yama:Set("EliteCountCheckedAt", os.time())
            FunctionsHandler.Yama:Set("EliteCount", Remotes.CommF_:InvokeServer("EliteHunter", "Progress"))
        end
        if (FunctionsHandler.Yama:Get('EliteCount') or 0) >= 30 then return true end
    end)
    FunctionsHandler.Yama:RegisterMethod("Start", function()
        repeat
            task.wait()
            TweenController.Create(game:GetService("ReplicatedStorage").FakeIslands.Waterfall:GetModelCFrame())
        until workspace.Map:FindFirstChild("Waterfall") and workspace.Map.Waterfall:FindFirstChild("SealedKatana")
        fireclickdetector(workspace.Map.Waterfall.SealedKatana.Hitbox.ClickDetector)
    end)
    FunctionsHandler.PirateRaid:RegisterMethod("Refresh", function()
        local k = FunctionsHandler.PirateRaid:Get('Senque')
        return k and os.time() - k < 500
    end)
    FunctionsHandler.PirateRaid:RegisterMethod("Start", function()
        local k = GetMonAsSortedRange()
        local h = Vector3.new(-5543.5327148438, 313.80062866211, -2964.2585449219)
        if k[1] then
            local X, w = k[1]:FindFirstChild("Humanoid"), k[1]:FindFirstChild("HumanoidRootPart")
            if w and X and X.Health > 0 and CaculateDistance(w.CFrame, h) < 500 then
                CombatController.Attack(k[1].Name)
                return
            end
        end
        TweenController.Create(h)
    end)
    function CheckFullMoon(k)
        if Lighting.Sky.MoonTextureId ~= 'http://www.roblox.com/asset/?id=970914431' then return end
        if k then return true end
        return Lighting.ClockTime > 18 or Lighting.ClockTime < 5
    end

    -- Blue Flower (Race V2 quest, EvoRace) only spawns at night and despawns at day -
    -- reuse CheckFullMoon's night window, just without the moon-phase requirement.
    function CheckNight()
        return Lighting.ClockTime > 18 or Lighting.ClockTime < 5
    end

    function SpawnSoulReaper()
        if ScriptStorage.Tools['Hallow Essence'] then
            repeat
                task.wait(0.1)
                TweenController.Create(-8932.322265625, 146.83154296875, 6062.55078125)
            until CaculateDistance(Vector3.new(-8932.322265625, 146.83154296875, 6062.55078125)) <= 8
            -- Equipping alone never consumed the essence or summoned anything - this looped
            -- forever re-equipping every tick while standing at the circle with the item still
            -- in the backpack ("đứng im lỗi"). Tool.Activated is a real Signal that replicates
            -- to the server the same as an actual click when fired, so use it to actually
            -- trigger the ritual instead of just holding the item.
            local Essence = ScriptStorage.Tools['Hallow Essence']
            FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call("Hallow Essence")
            task.wait(0.5)
            pcall(function()
                if Essence and Essence:FindFirstChild("Handle") then
                    Essence.Activated:Fire()
                end
            end)
            task.wait(1)
            StartReroll = false
        else
            SetTask('MainTask', "Resource Farming | Bones | For Hallow Essence")
            CurrentClaimQuest4 = GetCurrentClaimQuest(true)
            if CurrentClaimQuest4 then
                if not string.find(CurrentClaimQuest4, 'Demonic') then
                    J.AbandonQuest()
                    return
                else
                    CombatController.Attack({
                        'Reborn Skeleton',
                        "Living Zombie",
                        "Demonic Soul",
                        'Posessed Mummy'
                    })
                    return
                end
            else
                local X = ScriptStorage.NPCs["Haunted Castle Quest Giver 2"]
                X = X and X:GetModelCFrame()
                if X then
                    TweenController.Create(X + Vector3.new(0, 5, 3))

                    if CaculateDistance(X) < 20 then
                        task.wait(1)
                    else
                        return
                    end
                else
                    Report("NPC HauntedQuest2 not found")
                end
                J.StartQuest('HauntedQuest2', 1)
                return
            end
        end
    end

    task.spawn(function()
        while task.wait(1) do
            if SeaIndex == 3 and StartReroll then
                if (ScriptStorage.Backpack.Bones or { Count = 0 }).Count >= 50 then
                    if os.time() > (BonesCooldown or 0) then
                        local X, X, X, w = Remotes.CommF_:InvokeServer("Bones", 'Check')
                        if tonumber(X or 1) == 0 then
                            local X = Split(w, ":")
                            local w = ((tonumber(X[1]) * 60) + tonumber(X[2])) * 60
                            BonesCooldown = os.time() + w
                        else
                            Remotes.CommF_:InvokeServer('Bones', 'Buy', 1, 1)
                        end
                    end
                end
            end
        end
    end)

    FunctionsHandler.SoulGuitar:RegisterMethod("Refresh", function()
        if not getgenv().Studio["Blox Fruit"]["Items"]["Gun"]["Skull Guitar"] then return end
        if ScriptStorage.Backpack['Skull Guitar'] then return end
        -- Per user request: Skull Guitar's whole process only starts once Cursed Dual Katana is
        -- already in hand - CursedDualKatana is earlier in TasksOrder and would normally win
        -- priority naturally, but this makes the dependency explicit instead of relying on
        -- ordering alone (e.g. if the toggle for it is off, or it's somehow skipped).
        if not ScriptStorage.Backpack['Cursed Dual Katana'] then return end
        if ScriptStorage.PlayerData.Level < 2300 then return end
        -- Dark Fragment is only needed here, for Skull Guitar's craft materials - farm it as
        -- part of this task instead of a different, unrelated task (SeaTravel) blocking on it.
        -- Gated on Max Level specifically (not the 2300 floor the rest of this quest uses).
        if not ScriptStorage.Backpack['Dark Fragment'] then
            if ScriptStorage.PlayerData.Level < MaxLevel then return end
            return 0
        end
        local k = (ScriptStorage.Backpack['Ectoplasm'] or { Count = 0 })["Count"]
        local h = (ScriptStorage.Backpack["Bones"] or { Count = 0 })['Count']
        if k < 250 then return 1 end
        if SeaIndex ~= 3 then return end
        SoulGuitarProcess = Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", 'Check')
        if not SoulGuitarProcess then
            Remotes.CommF_:InvokeServer("gravestoneEvent", 2)
            if not CheckFullMoon() then
                SetTask('MainTask', 'Hopping for full moon ( soul guitar )')
                if getgenv().Premium then
                    if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Select Hop"]["Hop Find Rip Indra"] then
                        SetTask("MainTask", "Tushita | Hopping for Rip Indra True Form...")
                        alert("Tushita", "Không tìm thấy Rip Indra → Hopping...")
                        task.spawn(function()
                            Duma("FullMoon")
                        end)
                    end
                else
                    LowHop("Singapore")
                end
            end
            return 7
        end
        if not SoulGuitarProcess.Swamp then
            return 2
        elseif not SoulGuitarProcess.Gravestones then
            return 3
        elseif not SoulGuitarProcess.Ghost then
            return 4
        elseif not SoulGuitarProcess.Trophies then
            return 5
        elseif not SoulGuitarProcess.Pipes then
            return 6
        elseif h < 500 then
            -- Nothing else in this state machine ever farms Bones - once the puzzle steps
            -- are all done but Bones is short, this fell through to nil forever, and since
            -- LevelFarm also steps aside once Godhuman+CDK are done but Skull Guitar isn't,
            -- the whole task loop could go idle with nothing selected. Farm it here.
            return 9
        elseif not ScriptStorage.Backpack["Skull Guitar"] then
            return 8
        end
    end)
    FunctionsHandler.SoulGuitar:RegisterMethod('Start', function(k)
        if k == 0 then
            -- Dark Fragment (Fist of Darkness chests + Darkbeard/Dark Arena) is Second Sea
            -- only per wiki - every other SoulGuitar state needs Sea 3, so without this check
            -- the chest/Darkbeard farming below just ran wherever the player already happened
            -- to be (often Sea 3), farming the wrong sea's chests and never finding Darkbeard.
            if SeaIndex ~= 2 then
                SetTask('MainTask', 'Skull Guitar | Teleporting to Sea 2 for Dark Fragment')
                Remotes.CommF_:InvokeServer("TravelDressrosa")
                task.wait(3)
                return
            end
            SetTask('MainTask', 'Skull Guitar | Farming Dark Fragment')
            if ScriptStorage.Enemies['Darkbeard'] then
                CombatController.Attack({ "Darkbeard" })
            else
                if getgenv().Premium then
                    if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Select Hop"]["Hop Find Darkbeard"] then
                        SetTask("MainTask", "Dark Fragments | Hopping for Darkbeard...")
                        alert("Dark Fragments", "Không tìm thấy Darkbeard → Hopping...")
                        task.spawn(function()
                            Duma("Darkbeard")
                        end)
                    end
                else
                    SpawnDarkbeard()
                end
            end
        elseif k == 7 then
            while CaculateDistance(CFrame.new(-8654.0, 140, 6167)) > 5 do
                task.wait()
                TweenController.Create(CFrame.new(-8654.0, 140, 6167))
            end
            SoulGuitarProcess = Remotes.CommF_:InvokeServer("gravestoneEvent", 2, true)
        elseif k == 1 then
            if SeaIndex ~= 2 then
                SetTask("MainTask", 'Teleport to second sea to farm ectoplasm')
                return Remotes.CommF_:InvokeServer("TravelDressrosa")
            else
                SetTask("MainTask", "Farming ectoplasms for soul guitar")
                CombatController.Attack({ "Ship Deckhand", "Ship Engineer", 'Ship Steward', "Ship Officer" })
                return
            end
        elseif k == 2 then
            TTL9 = TTL9 or 0
            if os.time() ~= LastestTime1 then
                TTL9 = TTL9 + 1
                LastestTime1 = os.time()
            end
            if TTL9 > 60 then return LowHop("Singapore") end
            local h = {}
            for X, X in Services.Workspace.Enemies:GetChildren() do
                if X.name == "Living Zombie" then table.insert(h, X) end
            end
            if #h < 6 then
                SetTask('MainTask', 'Soul Guitar task 1 / 5: waiting until entity spawn')
                TweenController.Create(ScriptStorage.MobRegions["Living Zombie"][1] + Vector3.new(0, 30, 0))
            else
                local X = os.time()
                for w, D in h do
                    while task.wait() and D.Humanoid.Health > 7000 do
                        SetTask('MainTask', 'Soul Guitar task 1 / 5: Hit mob ' .. w .. " / 6")
                        FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Melee')
                        if os.time() - X > 60 then LowHop("Singapore") end
                        TweenController.Create(D.HumanoidRootPart.CFrame + Vector3.new(0, 50, 0))
                        W:Attack()
                    end
                end
                SetTask("MainTask", 'Soul Guitar task 1 / 5: Attack')
                while workspace.Enemies:FindFirstChild("Living Zombie") and task.wait() do
                    if os.time() - X > 60 then LowHop("Singapore") end
                    CombatController.Attack('Living Zombie')
                end
            end
        elseif k == 3 then
            local W = workspace.Map["Haunted Castle"]
            while CaculateDistance(CFrame.new(-8800.0, 178, 6033)) > 10 do
                task.wait()
                SetTask("MainTask", "Soul Guitar task 2 / 5: completing placards")
                TweenController.Create(CFrame.new(-8800.0, 178, 6033))
            end
            for h, X in { Placard1 = "Right", Placard2 = "Right", Placard3 = "Left", Placard4 = 'Right', Placard5 = 'Left', Placard6 = 'Left', Placard7 = "Left" } do
                fireclickdetector(W[h][X].ClickDetector)
            end
        elseif k == 4 then
            Remotes.CommF_:InvokeServer("GuitarPuzzleProgress", "Ghost")
        elseif k == 5 then
            if CaculateDistance(CFrame.new(-9530.0126953125, 6.104853630065918, 6054.83349609375)) > 30 then
                TweenController.Create(CFrame.new(-9530.0126953125, 6.104853630065918, 6054.83349609375))
            else
                local W = workspace.Map['Haunted Castle'].Tablet
                for h, h in pairs(BlankTablets) do
                    local X = W[h]
                    if X.Line.Rotation.Z ~= 0 then
                        repeat
                            task.wait()
                            fireclickdetector(X.ClickDetector)
                        until X.Line.Rotation.Z == 0
                    end
                end
                for h, X in pairs(Trophy) do
                    local w = workspace.Map["Haunted Castle"].Trophies.Quest[X].Handle.CFrame
                    w = tostring(w)
                    w = w:split(", ")[4]
                    local X = "180"
                    if w == "1" or w == "-1" then X = "90" end
                    if not string.find(tostring(W[h].Line.Rotation.Z), X) then
                        repeat
                            task.wait()
                            fireclickdetector(W[h].ClickDetector)
                        until string.find(tostring(W[h].Line.Rotation.Z), X)
                    end
                end
            end
        elseif k == 6 then
            for W, h in pairs(Pipes) do
                pcall(function()
                    local X = workspace.Map['Haunted Castle']['Lab Puzzle'].ColorFloor.Model[W]
                    if X.BrickColor.Name ~= h then
                        repeat
                            task.wait()
                            fireclickdetector(X.ClickDetector)
                        until X.BrickColor.Name == h
                    end
                end)
            end
            Remotes.CommF_:InvokeServer('soulGuitarBuy')
        elseif k == 8 then
            Remotes.CommF_:InvokeServer('soulGuitarBuy')
        elseif k == 9 then
            SetTask('MainTask', 'Skull Guitar | Farming Bones')
            CombatController.Attack({ 'Reborn Skeleton', "Living Zombie", "Demonic Soul", 'Posessed Mummy', 'Soul Reaper' })
        end
    end)
    FunctionsHandler.Tushita:RegisterMethod("Refresh", function()
        if ScriptStorage.Backpack.Tushita then return end
        if ScriptStorage.PlayerData.Level < 2000 then return end
        if SeaIndex ~= 3 then return end

        TushitaProgress = TushitaProgress or Remotes.CommF_:InvokeServer("TushitaProgress")
        if not TushitaProgress.OpenedDoor then
            if ScriptStorage.Enemies["rip_indra True Form"] then
                TushitaProgress = nil
                return 1
            else
                if getgenv().Premium then
                    if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Select Hop"]["Hop Find Rip Indra"] then
                        SetTask("MainTask", "Tushita | Hopping for Rip Indra True Form...")
                        alert("Tushita", "Không tìm thấy Rip Indra → Hopping...")
                        task.spawn(function()
                            Duma("Rip Indra")
                        end)
                    end
                else
                    -- SpawnRipIndra()
                end
            end
        else
            if ScriptStorage.Enemies['Longma'] then
                TushitaProgress = nil
                return 2
            else
                SetTask("MainTask", "Tushita | Hopping for Longma...")
                alert("Tushita", "Không tìm thấy Longma → Hopping...")
                task.spawn(function()
                    LowHop("Singapore")
                end)
                return nil
            end
        end
    end)

    FunctionsHandler.Tushita:RegisterMethod('Start', function(k)
        if k == 1 then
            alert('Auto Tushita', 'Placing torches...')
            TweenController.Create(CFrame.new(5714, math.random(19, 21), 256))
            if ScriptStorage.Tools["Holy Torch"] then
                for W = 1, 5 do
                    Remotes.CommF_:InvokeServer("TushitaProgress", "Torch", W)
                end
                return true
            end
        elseif k == 2 then
            alert("Auto Tushita", "Defeating Longma")
            CombatController.Attack("Longma")
        end
    end)

    FunctionsHandler.CursedDualKatana:RegisterMethod("Refresh", function()
        if not getgenv().Studio["Blox Fruit"]["Items"]["Sword"]["Cursed Dual Katana"] then return end
        local k = ScriptStorage.Backpack
        if ScriptStorage.PlayerData.Level < 2200 then return end
        if k["Cursed Dual Katana"] or not k.Tushita or k.Tushita.Mastery < 350 or not k.Yama or k.Yama.Mastery < 350 then return end
        if SeaIndex ~= 3 then return end

        local k = CdkProgess or Remotes.CommF_:InvokeServer("CDKQuest", 'Progress') or 'uwu'
        if not k or k == 'uwu' then return end

        -- Turtle island (Third Sea's Map.Turtle) isn't always streamed in just because SeaIndex
        -- is 3 - the player can be anywhere on that sea (e.g. off collecting berries), and
        -- StreamingEnabled only loads nearby parts. Dot-indexing .Turtle.Cursed threw a hard
        -- error every single RefreshTasksData tick (~7x/sec) whenever the island wasn't loaded,
        -- silently eating every CDK Refresh call via the outer xpcall the whole time. Walk it
        -- safely with FindFirstChild and just treat "not loaded yet" as "no door visible now".
        local TurtleFolder = workspace.Map:FindFirstChild("Turtle")
        local CursedArea = TurtleFolder and TurtleFolder:FindFirstChild("Cursed")
        if CursedArea and CursedArea:FindFirstChild("Breakable") then
            alert('Cursed Dual Katana', 'Open Door')
            return { "break" }
        end

        local W = { Good = 'Tushita', Evil = 'Yama' }

        if k.Good >= 4 and k.Evil >= 4 then
            return { 'burn 2' }
        end
        if k.Good == 3 or k.Evil == 3 then
            return { "burn" }
        end

        -- Real CDKQuest 'Progress' response has no 'Opened' field (confirmed via live
        -- InvokeServer probe - it only ever returns Good/Evil/Finished), so the old
        -- k.Opened-gated loop below never fired and trials never auto-started from a cold
        -- state. Each side is instead a single number: -1 = locked, -2 = blank/not
        -- unlocked, -3/-4/-5 = trial (v+2)*-1 already started (resume via cache), 0/1/2 =
        -- trial v+1 not started yet (call StartTrial), >=3 = side done (burn above).
        local Resuming = false
        for _, h in { "Good", "Evil" } do
            local X = k[h]
            if X and X <= -3 and X >= -5 then
                -- Trial already started - just point CdkCache at it and fall through to the
                -- live per-trial combat logic below (don't return here - that used to hand
                -- Start() this raw {Good=,Evil=} table instead of {side, trial}, so Start's
                -- k[1]/k[2] checks never matched anything and the task silently did nothing).
                ScriptStorage.CdkCache = { h, (X + 2) * -1 }
                Resuming = true
                break
            end
        end
        if not Resuming then
            for _, h in { "Good", "Evil" } do
                local X = k[h]
                if X and X >= 0 and X < 3 then
                    if not ScriptStorage.Tools[W[h]] then Remotes.CommF_:InvokeServer('LoadItem', W[h]) end
                    alert("Cursed Dual Katana", "Start " .. tostring(W[h]) .. ' trial ' .. tostring(X + 1))
                    Remotes.CommF_:InvokeServer('CDKQuest', 'StartTrial', h)
                    ScriptStorage.CdkCache = { h, X + 1 }
                    SetTask("MainTask", "Cursed Dual Katana - " .. tostring(W[h]) .. ' trial ' .. tostring(X + 1))
                    return false
                end
            end
        end

        local k = ScriptStorage.CdkCache
        if not k then return end
        local W, h = k[1], k[2]

        if W == "Evil" and h == 3 then
            if not ScriptStorage.Enemies['Soul Reaper'] then
                if getgenv().Premium then
                    if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Select Hop"]["Hop Find Soul Reaper"] then
                        SetTask("MainTask", "CDK Quest | Hopping for Soul Reaper...")
                        alert("CDK Quest", "Không tìm thấy Soul Reaper → Hopping...")
                        task.spawn(function()
                            Duma("Soul Reaper")
                        end)
                    end
                else
                    StartReroll = true
                    SpawnSoulReaper()
                end
                return
            end
        elseif W == 'Good' then
            if h == 2 then
                -- Wiki-confirmed: this trial just needs ONE pirate kill during an active Pirate
                -- Raid at Castle on the Sea. Two separate detection paths for "is a raid active
                -- right now": (a) Senque, set reactively from the server's own "been spotted
                -- approaching" chat message - but that message only fires ONCE when the raid
                -- starts, so hopping into a server where a raid was ALREADY in progress means
                -- we never saw that message and Senque stays nil, missing a raid that's right
                -- there; (b) a live check for actual pirates near the Castle position, which
                -- works regardless of whether we caught the announcement. Checking both means a
                -- Duma hop landing mid-raid gets recognized immediately instead of wasting it.
                local RaidPos = Vector3.new(-5543.5327148438, 313.80062866211, -2964.2585449219)
                local Senque = FunctionsHandler.PirateRaid:Get('Senque')
                local AnnouncedRecently = Senque and os.time() - Senque < 500
                -- k[1] from GetMonAsSortedRange() is only the mob NEAREST TO THE PLAYER, not
                -- nearest to Castle on the Sea - if the player is standing near some other mob
                -- (or just slightly off from the exact raid spot) while a raid is genuinely
                -- active, k[1] can easily be a non-pirate or a pirate too far from RaidPos,
                -- making this falsely report "no raid" even with one right there. Scan the
                -- whole list for ANY live mob within range of RaidPos instead of only k[1].
                local NearbyPirate
                for _, mon in GetMonAsSortedRange() do
                    local hum, hrp = mon:FindFirstChild("Humanoid"), mon:FindFirstChild("HumanoidRootPart")
                    if hum and hrp and hum.Health > 0 and CaculateDistance(hrp.CFrame, RaidPos) < 500 then
                        NearbyPirate = mon
                        break
                    end
                end

                if AnnouncedRecently or NearbyPirate then
                    SetTask("MainTask", "CDK Quest | Killing Pirate for Raid Castle Trial")
                    if NearbyPirate then
                        CombatController.Attack(NearbyPirate.Name)
                        return
                    end
                    TweenController.Create(RaidPos)
                    return
                end

                if getgenv().Premium then
                    if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Select Hop"]["Hop Find Raid Castle"] then
                        -- Be physically at Castle on the Sea BEFORE hopping, not just anywhere
                        -- on the sea - the new server keeps/streams us in near our last position
                        -- (same idea as SpawnPoint/LastSpawnPoint), so if the server we land on
                        -- happens to already have a raid up, we're right there to fight instead
                        -- of needing to travel there first after arriving.
                        if CaculateDistance(RaidPos) > 50 then
                            SetTask("MainTask", "CDK Quest | Moving to Castle on the Sea before hopping...")
                            TweenController.Create(RaidPos)
                            return
                        end
                        SetTask("MainTask", "CDK Quest | Hopping for Raid Castle...")
                        alert("CDK Quest", "Không tìm thấy Raid Castle → Hopping...")
                        task.spawn(function()
                            Duma("Raid Castle")
                        end)
                    end
                else
                    -- No raid up and not Premium (can't hop-search) - farm the Bones mob set
                    -- (same Haunted Castle mobs used elsewhere for mastery/Beli) instead of
                    -- standing still for however long the next raid takes to start on its own.
                    SetTask("MainTask", 'CDK Quest / Waiting until pirate raid started')
                    CombatController.Attack({ 'Reborn Skeleton', "Living Zombie", "Demonic Soul", 'Posessed Mummy' })
                end
                return
            elseif h == 3 and not ScriptStorage.Enemies["Cake Queen"] then
                if getgenv().Premium then
                    if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Select Hop"]["Hop Find Cake Queen"] then
                        SetTask("MainTask", "CDK Quest | Hopping for Cake Queen...")
                        alert("CDK Quest", "Không tìm thấy Cake Queen → Hopping...")
                        task.spawn(function()
                            Duma("Cake Queen")
                        end)
                    end
                else
                    LowHop("Singapore")
                end
                return
            end
        end
        return k
    end)
    FunctionsHandler.CursedDualKatana:RegisterMethod("GetHazeMon", function()
        local k = {}
        for W, W in LocalPlayer.QuestHaze:GetChildren() do if W.Value > 0 then table.insert(k, W) end end
        table.sort(k,
            function(W, h)
                return CaculateDistance(W:GetAttribute('Position')) <
                    CaculateDistance(h:GetAttribute('Position'))
            end)
        return tostring(k[1])
    end)
    FunctionsHandler.CursedDualKatana:RegisterMethod("DoDimension", function(k)
        local W = string.gsub(k, ' ', "")
        local k = os.time()
        repeat
            task.wait()
            TweenController.Create(LocalPlayer.Character.HumanoidRootPart.CFrame)
            if os.time() - k > 60 then return end
        until os.time() - TorchEnabledTime < 10
        repeat
            task.wait()
            local k = workspace.Map:WaitForChild(W, 10)
            if k then
                for h, h in k:GetChildren() do
                    if h and string.find(h.Name, "Torch") and h:FindFirstChild('ProximityPrompt') and h.ProximityPrompt.Enabled then
                        LocalPlayer.Character.HumanoidRootPart.CFrame = h.CFrame
                        h.ProximityPrompt.HoldDuration = 0
                        task.wait(1)
                        SendKey("E", 0.1)
                        fireproximityprompt(workspace.Map:WaitForChild(W, 10):FindFirstChild(tostring(h))
                            .ProximityPrompt)
                    end
                    for W, W in workspace.Enemies:GetChildren() do
                        local h = W:FindFirstChild("HumanoidRootPart")
                        local X = W:FindFirstChild("Humanoid")
                        if h and X and CaculateDistance(h.CFrame) < 1000 then CombatController.Attack(W.Name) end
                    end
                end
                ExitDoor = k:FindFirstChild("Exit")
                if ExitDoor then
                    PortalBrick = tostring(ExitDoor.BrickColor)
                end
            else
            end
        until PortalBrick == 'Olive' or PortalBrick == "Cloudy grey"
        if os.time() - DoneCdkTick > 15 then
            TweenController.Create(ExitDoor.CFrame + Vector3.new(0, math.random(1, 5), 0))
            task.wait()
        end
        LowHop("Singapore")
    end)
    FunctionsHandler.CursedDualKatana:RegisterMethod("Start", function(k)
        local W = workspace.Map.Turtle.Cursed
        if k[1] == 'break' then
            TweenController.Create(workspace.Map.Turtle.Cursed.Breakable.CFrame)
            Remotes.CommF_:InvokeServer('CDKQuest', "OpenDoor")
            Remotes.CommF_:InvokeServer("CDKQuest", "OpenDoor", true)
            workspace.Map.Turtle.Cursed.Breakable:Destroy()
            CdkProgess = nil
            return
        end
        if k[1] == "burn 2" then
            if workspace.Map.Turtle.Cursed.Pedestal3.ProximityPrompt.Enabled then
                fireproximityprompt(workspace.Map.Turtle.Cursed.Pedestal3.ProximityPrompt)
                task.wait(1)
                pcall(function() LocalPlayer.Character.Humanoid.Health = 0 end)
                task.wait(10)
            else
                CDKAttempts = (CDKAttempts or 0) + 1
                TweenController.Create(CFrame.new(-12341.66796875, 603.3455810546875, -6550.6064453125))
                task.wait(5)
                pcall(function() LocalPlayer.Character.Humanoid.Health = 0 end)
                task.wait(5)
                if CDKAttempts > 5 then LowHop("Singapore") end
                CdkProgess = nil
            end
        elseif k[1] == "burn" then
            for W = 1, 3, 1 do
                local h = workspace.Map.Turtle.Cursed:FindFirstChild("Pedestal" .. W)
                if workspace.Map.Turtle.Cursed:FindFirstChild('Pedestal' .. W).ProximityPrompt.Enabled then
                    repeat
                        task.wait()
                        TweenController.Create(workspace.Map.Turtle.Cursed:FindFirstChild('Pedestal' .. W).CFrame)
                    until CaculateDistance(workspace.Map.Turtle.Cursed:FindFirstChild("Pedestal" .. W).CFrame) < 5
                    fireproximityprompt(workspace.Map.Turtle.Cursed:FindFirstChild("Pedestal" .. W).ProximityPrompt)
                    task.wait(3)
                    pcall(function() LocalPlayer.Character.Humanoid.Health = 0 end)
                end
                CdkProgess = nil
            end
        elseif k[1] == 'Evil' then
            if k[2] == 1 then
                -- Wiki (confirmed across multiple guides): "Pain and Suffering" needs
                -- 8,000-10,000 cumulative damage taken while holding Yama, by standing near a
                -- hostile NPC and letting it hit you - NOT fighting back (attacking risks
                -- killing it before enough damage racks up; the trial only cares about damage
                -- taken, not dealt). "Forest Pirate" specifically is gated behind accepting a
                -- separate, blacklisted "CitizenQuest" from an NPC (decompile: DialoguesList's
                -- Citizen entry, "Will you help defeat 50 of them?") - that NPC's spawn point
                -- isn't exposed anywhere in the game's own quest-location data this script can
                -- read, so hunting "Forest Pirate" directly waited forever with nothing to ever
                -- spawn. The wiki doesn't require Forest Pirate specifically, just "an enemy
                -- NPC" - reuse the same always-available Haunted Castle mobs used elsewhere in
                -- this quest, standing near whichever is closest instead of attacking it.
                if not ScriptStorage.Tools['Yama'] then Remotes.CommF_:InvokeServer('LoadItem', 'Yama') end
                FunctionsHandler.LocalPlayerController.Methods.EquipTool:Call('Yama')
                -- Forest Pirate spawns at the Mansion (Workspace._WorldOrigin.Locations.Mansion
                -- = -12547.71, 290.14, -7487.06, confirmed live). If it's not currently up,
                -- tween there and wait instead of hunting it from wherever the character
                -- happens to be - MobRegions never had a usable entry for it.
                local MansionPos = Vector3.new(-12547.7099609375, 290.1390075683594, -7487.06494140625)
                local W = ScriptStorage.Enemies["Forest Pirate"]
                if W and W:FindFirstChild("HumanoidRootPart") then
                    local hum = LocalPlayer.Character:FindFirstChild("Humanoid")
                    -- Health dropped from full to ~12% (and the character likely died) between
                    -- one check and the next at an earlier 15% threshold - a single hit can
                    -- easily be several thousand damage at this level, so 15% left far too
                    -- little margin to react before death. Retreat early (50%) and far (60
                    -- studs, well outside attack range) instead of a token 20-stud step.
                    if hum and hum.Health < hum.MaxHealth * 0.5 then
                        TweenController.Create(LocalPlayer.Character.HumanoidRootPart.CFrame - W.HumanoidRootPart.CFrame.LookVector * 60)
                    else
                        TweenController.Create(W.HumanoidRootPart.CFrame)
                    end
                else
                    TweenController.Create(MansionPos)
                end
                CdkProgess = nil
            elseif k[2] == 2 then
                CombatController.Attack(FunctionsHandler.CursedDualKatana.Methods.GetHazeMon:Call())
                CdkProgess = nil
            elseif k[2] == 3 then
                -- "Fear the Reaper" needs the Soul Reaper to KILL the player (not be
                -- defeated). Manually zeroing Health worked for the scripted break/burn/burn 2
                -- deaths elsewhere in this quest, but here it doesn't actually count as being
                -- killed BY the Soul Reaper - the trial never progressed, and the trial state
                -- got stuck. Just stay in its attack range and let its own hits kill the
                -- character for real instead of faking the death.
                -- TweenController.Create(W:GetModelCFrame()) here used to route through
                -- GetPortal for any target over 500 studs away (almost always true right after
                -- respawning somewhere unrelated) - GetPortal picked whichever Third Sea portal
                -- was numerically nearest the TARGET by raw distance with no regard for altitude,
                -- and PortalsBySea[3] includes one at (28282.5, 14896.8, 105.1) - a sky-high
                -- entrance. Live-confirmed this routed the character up there and left it
                -- stranded, Y in the thousands, over 13000 studs from the Soul Reaper, for the
                -- rest of the 100s window every time - the trial never actually progressed
                -- ("đứng im lỗi"). Fixed at the source in GetPortal (near line 1510) instead of
                -- bypassing TweenController.Create here, so every other long-distance tween in
                -- this file benefits from the same fix.
                -- The real completion signal is the character actually dying, not whether
                -- ScriptStorage.Enemies["Soul Reaper"] still holds a reference - that table can
                -- lose the entry right after the kill lands (respawn drops tracked mobs out of
                -- render range) or for unrelated reasons before any hit ever lands, and the old
                -- `if not ...Enemies["Soul Reaper"] then return end` treated both cases the same
                -- as "never got killed", silently skipping DoDimension even on a real kill. Watch
                -- Humanoid.Died directly instead - same idea as the Cake Queen branch below,
                -- which only calls DoDimension once its kill condition is actually confirmed.
                Report("found cdk yama 3")
                local W = LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid")
                local h = false
                local X = W and W.Died:Connect(function() h = true end)
                local k2 = os.time()
                while not h and os.time() - k2 < 100 do
                    task.wait()
                    local rk = ScriptStorage.Enemies["Soul Reaper"]
                    local rp = rk and rk:FindFirstChild("HumanoidRootPart")
                    -- Guard against (0,0,0) - a model that JUST got added to ScriptStorage.Enemies
                    -- can still have its HumanoidRootPart at the world origin for a frame or two
                    -- before the server's first real CFrame replicates in. Tweening there instead
                    -- of to the Soul Reaper's actual position leaves the character nowhere near
                    -- it, so it can never actually land a hit and kill the player.
                    if rp and rp.Position.Magnitude > 1 then
                        TweenController.Create(rp.CFrame + Vector3.new(0, 1, 0))
                    end
                end
                if X then X:Disconnect() end
                if not h then return end
                Report('Soul Reaper')
                FunctionsHandler.CursedDualKatana.Methods.DoDimension.Callback("Hell Dimension")
                CdkProgess = nil
            end
        else
            if k[2] == 1 then
                -- "Dock Legend" needs 3 DIFFERENT Boat Dealers on 3 DIFFERENT islands.
                -- ReplicatedStorage.NPCs only holds one template per unique name, so the
                -- old loop only ever visited a single dealer regardless of how many real
                -- islands have one. workspace.NPCs holds every actually-spawned per-island
                -- instance - walk all of them, skipping ones already checked off server-side.
                for _, h in workspace.NPCs:GetChildren() do
                    if h.Name == "Luxury Boat Dealer" and h:FindFirstChild("HumanoidRootPart") then
                        local Done = Remotes.CommF_:InvokeServer("CDKQuest", "BoatQuest", h, "Check")
                        if not Done then
                            repeat
                                task.wait()
                                if os.time() - DoneCdkTick < 15 then return end
                                TweenController.Create(h.HumanoidRootPart.CFrame)
                            until CaculateDistance(h.HumanoidRootPart.CFrame) < 5
                            Remotes.CommF_:InvokeServer("CDKQuest", "BoatQuest", h)
                            task.wait(1)
                        end
                    end
                end
                CdkProgess = nil
            elseif k[2] == 3 then
                repeat
                    task.wait()
                    CombatController.Attack("Cake Queen")
                until os.time() - TorchEnabledTime < 10 or not ScriptStorage.Enemies['Cake Queen']
                TweenController.Create(LocalPlayer.Character.HumanoidRootPart.CFrame)
                Report('Cake Queen')
                FunctionsHandler.CursedDualKatana.Methods.DoDimension.Callback("Heavenly Dimension")
                CdkProgess = nil
            end
        end
    end)
    local k = { Listeners = {} }
    TorchEnabledTime = 0
    DoneCdkTick = 0
    getgenv().NotificationCallBack = (function(W)
        for h, X in k.Listeners do
            if string.find(string.lower(W), string.lower(h)) then X(W) end
        end
    end)
    function k:RegisterNotifyListener(W, h) k.Listeners[W] = h end

    k:RegisterNotifyListener('go!', function() LastRaidAlert = os.time() end)
    k:RegisterNotifyListener('raid', function() LastRaidAlert2 = os.time() end)
    k:RegisterNotifyListener("been spotted approaching",
        function() FunctionsHandler.PirateRaid:Set('Senque', os.time()) end)
    k:RegisterNotifyListener('job', function() FunctionsHandler.PirateRaid:Set('Senque', 0) end)
    k:RegisterNotifyListener("level", function() AddPoint() end)
    k:RegisterNotifyListener("torch", function() TorchEnabledTime = os.time() end)
    k:RegisterNotifyListener("scroll reacts", function() DoneCdkTick = os.time() end)
    k:RegisterNotifyListener("elite", function()
        FunctionsHandler.Yama:Set('EliteCount', Remotes.CommF_:InvokeServer("EliteHunter", "Progress"))
        alert("[ARYA ] ", "Elite defeated: " .. tostring(FunctionsHandler.Yama:Get("EliteCount") or 'n/a'))
    end)
    k:RegisterNotifyListener('the raid with', function()
        if ScriptStorage.PlayerData.Level < MaxLevel then return end
        Remotes.CommF_:InvokeServer('Awakener', "Awaken")
    end)
    k:RegisterNotifyListener('quest completed', function()
        J:RefreshQuest()
        task.wait()
        if not J:GetCurrentClaimQuest() then J:MarkAsCompleted() end
    end)
    local k
    k = hookfunction(require(game.ReplicatedStorage.Notification).new, function(W, h)
        v21 = tostring(tostring(W or '') .. tostring(h or "")) or ""
        getgenv().NotificationCallBack(v21)
        return k(W, h)
    end)
    if SeaIndex ~= 1 then end
    function IfTableHaveIndex(k) for W in k do return true end end

    function GetServers()
        if LastServersDataPulled then
            if os.time() - LastServersDataPulled < 60 then return CachedServers end
        end
        for k = 1, 100, 1 do
            local W = game:GetService("ReplicatedStorage"):WaitForChild("__ServerBrowser"):InvokeServer(k)
            if IfTableHaveIndex(W) then
                LastServersDataPulled = os.time()
                CachedServers = W
                return W
            end
        end
    end

    task.spawn(function()
        GetServers()
        while task.wait(180) do GetServers() end
    end)
    Storage = { WRITE_DELAY = .5, Data = {} }
    Services = {}
    setmetatable(Services, { __index = function(k, k) return game:GetService(k) end })
    LocalPlayer = game.Players.LocalPlayer
    local k = ".storage_u_" .. tostring(LocalPlayer)
    function Decode(W) return Services.HttpService:JSONDecode(W) end

    function Encode(W) return Services.HttpService:JSONEncode(W) end

    function Storage.Set(W, h, X) W.Data[h] = X end

    function Storage.Get(W, h) return W.Data[h] end

    function Storage.Save(W) writefile(k, Encode(W.Data)) end

    if not isfile(k) then
        writefile(k, "{}")
        task.wait(1)
    end
    Storage.Data = {}
    pcall(function() Storage.Data = Decode(readfile(k) or '{}') end)
    task.spawn(function() while task.wait(Storage.WRITE_DELAY) do Storage:Save() end end)
    CreateTraceback('Initalize', "Initalizing script..")
    local k = {}
    SetTask("MainTask", 'n/a')
    SetTask("SubTask", 'n/a')
    ParsingTimes = 0
    function RefreshTasksData()
        if _G.Stop then return end
        -- CDK's "Raid Castle" trial only counts a kill while a raid is actively running (limited
        -- window), but CollectBerries/BossesTask/etc normally outrank CursedDualKatana in
        -- TasksOrder and can eat the whole raid window before CDK ever gets a turn. When a raid
        -- is up AND the account is mid Good/Tushita trial 2, jump CDK to the front for this tick
        -- only - throttled to one remote check every 3s so it doesn't spam CDKQuest/Progress.
        do
            local Senque = FunctionsHandler.PirateRaid:Get('Senque')
            local RaidUp = Senque and os.time() - Senque < 500
            if RaidUp and ScriptStorage.PlayerData.Level >= 2200 and SeaIndex == 3
                and not ScriptStorage.Backpack['Cursed Dual Katana']
                and ScriptStorage.Backpack.Tushita and ScriptStorage.Backpack.Tushita.Mastery >= 350
                and ScriptStorage.Backpack.Yama and ScriptStorage.Backpack.Yama.Mastery >= 350
                and os.time() - (CdkRaidPeekTime or 0) > 3 then
                CdkRaidPeekTime = os.time()
                local ok, prog = pcall(function() return Remotes.CommF_:InvokeServer("CDKQuest", 'Progress') end)
                CdkRaidPriority = ok and prog and prog.Good and prog.Good <= -3 and prog.Good >= -5
                    and (prog.Good + 2) * -1 == 2
            elseif not RaidUp then
                CdkRaidPriority = false
            end
            local CDK = FunctionsHandler.CursedDualKatana
            if CdkRaidPriority and CDK and CDK.Initalized then
                local h = CDK.Methods.Refresh:Call(ParsingTimes < 100)
                ParsingTimes = ParsingTimes + 1
                if h and ParsingTimes > 100 then
                    CurrentTask = "CursedDualKatana"
                    ScriptStorage.Interface.SetText('DebugLine', "CursedDualKatana")
                    CDK.Methods.Start:Call(h)
                    return
                end
            end
            -- CursedDualKatana sits above EvoRace/Wenlocktoad in TasksOrder, so once its own
            -- Refresh has anything to do it kept preempting a Race V3 objective that was
            -- already accepted and mid-progress, flipping MainTask back and forth between the
            -- two instead of finishing one before starting the other. WenlocktoadState==1
            -- (cached from Wenlocktoad's own last Start call, not re-fetched here) means the
            -- V3 quest is accepted and actively being worked - let it finish first.
            local WT = FunctionsHandler.Wenlocktoad
            if WenlocktoadState == 1 and WT and WT.Initalized then
                local h = WT.Methods.Refresh:Call(ParsingTimes < 100)
                ParsingTimes = ParsingTimes + 1
                if h and ParsingTimes > 100 then
                    CurrentTask = "Wenlocktoad"
                    ScriptStorage.Interface.SetText('DebugLine', "Wenlocktoad")
                    WT.Methods.Start:Call(h)
                    return
                end
            end
        end
        for W, W in TasksOrder do
            local h = FunctionsHandler[W]
            if not h.Initalized then
                if not k[W] then
                    k[W] = true
                end
            else
                local k = h.Methods.Refresh
                local X = h.Methods.Start
                if k then
                    local h = k:Call(ParsingTimes < 100)
                    ParsingTimes = ParsingTimes + 1
                    if h and ParsingTimes > 100 then
                        CurrentTask = CurrentTask ~= W
                        CurrentTask = W
                        ScriptStorage.Interface.SetText('DebugLine', W)
                        X:Call(h)
                        return
                    end
                end
            end
        end
    end

    SetText('MainTextLabel', "Refreshing Player Items..")
    AddPoint()
    J:RefreshQuest()
    RefreshInventory()
    Remotes.CommE.OnClientEvent:Connect(function(...)
        local J = { ... }
        if string.find(J[1], 'Item') then RefreshInventory() end
    end)
    RefreshRace()
    a.LocalPlayer.Idled:Connect(function()
        Services.VirtualUser:CaptureController()
        Services.VirtualUser:ClickButton2(Vector2.new())
    end)
    SetText("MainTextLabel", 'Loaded In ' .. tick() - StartTick .. 'ms!')
    QueueList = {}
    function NearbyHopHandler()
        do return end
        if NearbyHopHandlerDebounce and os.time() - NearbyHopHandlerDebounce < 10 then return end
        NearbyHopHandlerDebounce = os.time()
        for J, J in a:GetPlayers() do
            local k = J and J.Character and J.Character:FindFirstChild("HumanoidRootPart") and
                J.Character.HumanoidRootPart.Position
            if k then
                local W = QueueList[J.Name]
                if not W then
                    QueueList[J.Name] = os.time()
                else
                    if os.time() - W > 30 then
                        if CaculateDistance(k) < 100 then
                            Hop('nearby plr')
                            task.wait(5)
                        else
                            QueueList[J.Name] = nil
                        end
                    end
                end
            end
        end
    end

    task.spawn(function()
        while task.wait(1.5) do
            if not _G.Stop then
                NearbyHopHandler()
                -- Force-jumping off any seat is a safety net for accidentally auto-sitting on
                -- some random NPC bench/chair while TweenController moves the player around the
                -- map. It was unconditional though, so it also force-ejected the player every
                -- ~1.5s while intentionally riding the Wenlocktoad V3 Shark/Fishman boat (see
                -- TweenBoat's Sea Beast sailing near line 2160) - live-confirmed as the
                -- Boarding Boat / Sailing for a Sea Beast tasks flickering back and forth forever
                -- since the humanoid never stayed seated long enough for the quest boat ride to
                -- progress. Skip the eject when the seat is our own boat's VehicleSeat.
                local hum = LocalPlayer.Character:FindFirstChild('Humanoid')
                if hum and hum.Sit then
                    local onOwnBoat = false
                    if hum.SeatPart then
                        local myBoat = Services.Workspace.Boats:FindFirstChild(GetMyBoatName())
                        onOwnBoat = myBoat and hum.SeatPart == myBoat:FindFirstChild("VehicleSeat")
                    end
                    if not onOwnBoat then
                        hum:ChangeState(Enum.HumanoidStateType.Jumping)
                    end
                end
                do
                    pcall(RefreshPlayerData)
                    if os.time() - (LastRaceRefresh or 0) > 10 then
                        LastRaceRefresh = os.time()
                        pcall(RefreshRace)
                    end
                    local J = os.time() - StartTick
                    local currentSession = J + OldSessionTime
                    writefile(".tdif-" .. game.Players.LocalPlayer.Name, tostring(currentSession))
                    if ScriptStorage.Interface then
                        SetText('LiveTime',
                            "Total Elapsed Time: " ..
                            DispTime(currentSession, true) .. ' Elapsed Time: ' .. DispTime(J, true))
                    end
                    RefreshDebounce = os.time()
                end
            end
        end
    end)

    local Logo =
    'https://cdn.discordapp.com/attachments/1452263532489080924/1475940850105319495/EAAB692B-49F8-4132-972F-9BF3C1195E1C.png?ex=69f10d88&is=69efbc08&hm=a64ca084d9f7eecfabdea324f89419d3f1b0a3411a55f621f55e12c2a13f7e85&'

    local function GetRaceGrade()
        local ok, result = pcall(function()
            local bp = game.Players.LocalPlayer.Backpack
            local ch = game.Players.LocalPlayer.Character
            local function has(n) return (bp and bp:FindFirstChild(n)) or (ch and ch:FindFirstChild(n)) end
            if has("Awakening") then
                return "V4"
            elseif has("Last Resort") or has("Agility") or has("Water Body") or has("Heavenly Blood")
                or has("Heightened Senses") or has("Energy Core") or has("Primordial Reign") then
                return "V3"
            elseif game.Players.LocalPlayer.Data.Race:FindFirstChild("Evolved") then
                return "V2"
            else
                return "V1"
            end
        end)
        return ok and result or "V1"
    end


    function SendWebhook(taskLabel)
        local url = getgenv().Studio["Blox Fruit"]["Webhook"]["Url"]
        if not url or url == "" then return end

        local pd = ScriptStorage.PlayerData or {}
        local function safeStr(v) return tostring(v or "N/A") end

        local MeleeList = {}
        for Name, Lvl in pairs(ScriptStorage.Melees or {}) do
            if type(Lvl) == "number" and Lvl > 0 then
                table.insert(MeleeList, Name .. ": Lv." .. Lvl)
            end
        end

        local SwordList, GunList, AccList, FruitList, MaterialList = {}, {}, {}, {}, {}
        pcall(function()
            local inv = Remotes.CommF_:InvokeServer("getInventory")
            if type(inv) ~= "table" then return end
            for _, Item in pairs(inv) do
                if type(Item) == "table" and Item.Name then
                    local mas = " (Mas:" .. tostring(Item.Mastery or 0) .. ")"
                    if Item.Type == "Sword" then
                        table.insert(SwordList, Item.Name .. mas)
                    elseif Item.Type == "Gun" then
                        table.insert(GunList, Item.Name .. mas)
                    elseif Item.Type == "Wear" then
                        table.insert(AccList, Item.Name)
                    elseif Item.Type == "Blox Fruit" then
                        local dname = Item.DisplayName or Item.Name
                        local val = Item.Value and Price(Item.Value) or "?"
                        table.insert(FruitList, dname .. " (" .. val .. ")")
                    elseif Item.Type == "Material" then
                        table.insert(MaterialList, Item.Name .. " x" .. tostring(Item.Count or 1))
                    end
                end
            end
        end)

        local function listOrNone(t) return #t > 0 and table.concat(t, "\n") or "None" end

        local fruit = pd.DevilFruit
        fruit = (type(fruit) == "string" and fruit ~= "" and fruit ~= "None") and fruit or "None"

        local accountData = string.format(
            "Level     : %s\nRace      : %s (%s)\nFruit     : %s\nBeli      : %s\nFragments : %s\nTask      : %s",
            safeStr(pd.Level),
            safeStr(pd.Race),
            GetRaceGrade(),
            fruit,
            Price(pd.Beli or 0),
            Price(pd.Fragments or 0),
            safeStr(ScriptStorage.Task and ScriptStorage.Task.MainTask)
        )

        local data = {
            content = tostring(getgenv().Studio["Blox Fruit"]["Webhook"]["Ping Notify"] or ""),
            username = "Vxeze Hub",
            avatar_url = Logo,
            embeds = {
                {
                    title = "Blox Fruit - Kaitun Completed!",
                    description = "**Character:** ||" .. game.Players.LocalPlayer.Name .. "||",
                    color = 11400703,
                    fields = {
                        { name = "Account Data", value = "```\n" .. accountData .. "\n```",              inline = false },
                        { name = "Melee",        value = "```\n" .. listOrNone(MeleeList) .. "\n```",    inline = false },
                        { name = "Sword",        value = "```\n" .. listOrNone(SwordList) .. "\n```",    inline = false },
                        { name = "Gun",          value = "```\n" .. listOrNone(GunList) .. "\n```",      inline = false },
                        { name = "Fruits",       value = "```\n" .. listOrNone(FruitList) .. "\n```",    inline = false },
                        { name = "Accessories",  value = "```\n" .. listOrNone(AccList) .. "\n```",      inline = false },
                        { name = "Materials",    value = "```\n" .. listOrNone(MaterialList) .. "\n```", inline = false },
                    },
                    thumbnail = { url = Logo },
                    footer = { text = "- Vxeze Hub : BF Kaitun | " .. os.date("%H:%M:%S"), icon_url = Logo }
                }
            }
        }

        pcall(function()
            request({
                Url = url,
                Method = "POST",
                Headers = { ["Content-Type"] = "application/json" },
                Body = game:GetService("HttpService"):JSONEncode(data)
            })
        end)
    end

    task.spawn(function()
        local delay = math.max(60, (getgenv().Studio["Blox Fruit"]["Webhook"]["Delay"] or 60) * 60)
        while task.wait(delay) do
            task.spawn(function() SendWebhook(ScriptStorage.Task and ScriptStorage.Task.MainTask) end)
        end
    end)

    -- Was: game.NetworkClient.ChildRemoved:Connect(function() ... teleport to game.JobId ... end)
    -- NetworkClient.ChildRemoved fires constantly during completely normal play (other players'
    -- replication objects churning, not just actual disconnects), and each firing force-rejoined
    -- the current server AND reset the run-guard - this was almost certainly the real cause of
    -- the near-constant server-hopping/reconnect churn seen throughout testing, not an
    -- unrelated connector/network flakiness. Roblox's own client already handles real
    -- disconnects/reconnects; removed this instead of trying to narrow the trigger.

    task.delay(5, function()
        task.spawn(function() SendWebhook("Script Started | " .. game.Players.LocalPlayer.Name) end)
    end)

    AddPoint()
    Remotes.CommF_:InvokeServer("Cousin", 'Buy')
    task.spawn(function()
        task.wait(getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Hop"]["Delay"])
        if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Hop"]["Enable"] then Hop("Singapore") end
    end)
    while task.wait(0.15) do
        if getgenv().Studio["Blox Fruit"]["Sub"]["Setting Player"]["Hop When Idle"] and LastIdling and os.time() - LastIdling > 300.0 then
            SetTask('MainTask', "Rejoinjng due idle in 10 min!")
            task.wait(1)
            while task.wait() do Hop("Singapore") end
        end
        if not AnimationDelay or os.time() - AnimationDelay > 60 then
            AnimationDelay = os.time()
            pcall(function() LocalPlayer.Character:WaitForChild('Humanoid'):LoadAnimation(K):Play() end)
        end
        FunctionsHandler.MeleesController.Methods.Start:Call()
        local J, r = xpcall(RefreshTasksData, debug.traceback)
        if not J then
            warn(r)
        end
    end
end

_nguoitinhcuae()

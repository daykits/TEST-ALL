-- ============================================================
-- NEBULA-STYLED LIBRARY — Adapter cho Prince Hub
-- API: giữ nguyên Linoria (CreateWindow, AddTab, AddLeftGroupbox, AddToggle, ...)
-- Skin: Nebula (Dark Purple + Cyan, rounded, gradient, smooth tween)
-- ============================================================
local Library = (function()
    local InputService   = game:GetService('UserInputService')
    local TextService    = game:GetService('TextService')
    local CoreGui        = game:GetService('CoreGui')
    local Teams          = game:GetService('Teams')
    local Players        = game:GetService('Players')
    local RunService     = game:GetService('RunService')
    local TweenService   = game:GetService('TweenService')
    local RenderStepped  = RunService.RenderStepped
    local LocalPlayer    = Players.LocalPlayer
    local Mouse          = LocalPlayer:GetMouse()

    local ProtectGui = protectgui or (syn and syn.protect_gui) or (function() end)

    local ScreenGui = Instance.new('ScreenGui')
    ProtectGui(ScreenGui)
    ScreenGui.Name = 'NebulaHub'
    ScreenGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
    ScreenGui.DisplayOrder = 30
    ScreenGui.ResetOnSpawn = false
    pcall(function() ScreenGui.Parent = CoreGui end)
    if not ScreenGui.Parent then ScreenGui.Parent = LocalPlayer:WaitForChild('PlayerGui') end

    local Toggles = {}
    local Options = {}
    getgenv().Toggles = Toggles
    getgenv().Options = Options

    -- ==== NEBULA THEME ====
    local Theme = {
        Background = Color3.fromRGB(18, 19, 28),
        Panel      = Color3.fromRGB(28, 29, 42),
        Surface    = Color3.fromRGB(35, 36, 52),
        Accent     = Color3.fromRGB(138, 75, 235),
        Accent2    = Color3.fromRGB(0, 191, 255),
        Text       = Color3.fromRGB(242, 243, 250),
        Muted      = Color3.fromRGB(157, 160, 180),
        Danger     = Color3.fromRGB(255, 83, 105),
        Off        = Color3.fromRGB(65, 67, 86),
        Risk       = Color3.fromRGB(255, 83, 105),
    }

    local Library = {
        Registry      = {},
        RegistryMap   = {},
        HudRegistry   = {},
        FontColor     = Theme.Text,
        MainColor     = Theme.Panel,
        BackgroundColor = Theme.Background,
        AccentColor   = Theme.Accent,
        OutlineColor  = Theme.Off,
        RiskColor     = Theme.Risk,
        Black         = Color3.new(0,0,0),
        Font          = Enum.Font.GothamMedium,
        OpenedFrames  = {},
        DependencyBoxes = {},
        Signals       = {},
        ScreenGui     = ScreenGui,
        Theme         = Theme,
    }
    Library.AccentColorDark = Theme.Accent

    -- ==== UTILS ====
    local function create(className, props, parent)
        local obj = Instance.new(className)
        for k, v in pairs(props or {}) do obj[k] = v end
        if parent then obj.Parent = parent end
        return obj
    end
    Library.create = create

    local function corner(parent, r)
        return create('UICorner', { CornerRadius = UDim.new(0, r or 8) }, parent)
    end
    local function stroke(parent, color, thickness, transparency)
        return create('UIStroke', {
            Color = color or Theme.Off,
            Thickness = thickness or 1,
            Transparency = transparency or 0,
        }, parent)
    end
    Library.corner = corner
    Library.stroke = stroke

    local function tween(obj, dur, props, style, dir)
        TweenService:Create(
            obj,
            TweenInfo.new(dur or 0.2, style or Enum.EasingStyle.Quint, dir or Enum.EasingDirection.Out),
            props
        ):Play()
    end
    Library.tween = tween

    function Library:Create(Class, Properties)
        local _Instance = Class
        if type(Class) == 'string' then _Instance = Instance.new(Class) end
        for p, v in next, Properties do _Instance[p] = v end
        return _Instance
    end

    function Library:ApplyTextStroke(Inst)
        Inst.TextStrokeTransparency = 1
        Library:Create('UIStroke', {
            Color = Color3.new(0,0,0),
            Thickness = 1,
            LineJoinMode = Enum.LineJoinMode.Miter,
            Parent = Inst,
        })
    end

    function Library:GetTextBounds(Text, Font, Size, Resolution)
        local B = TextService:GetTextSize(Text, Size, Font, Resolution or Vector2.new(1920,1080))
        return B.X, B.Y
    end

    function Library:GetDarkerColor(Color)
        local H, S, V = Color3.toHSV(Color)
        return Color3.fromHSV(H, S, V / 1.5)
    end

    function Library:MapValue(Value, MinA, MaxA, MinB, MaxB)
        return (1 - ((Value - MinA) / (MaxA - MinA))) * MinB + ((Value - MinA) / (MaxA - MinA)) * MaxB
    end

    function Library:SafeCallback(f, ...)
        if not f then return end
        if not Library.NotifyOnError then return f(...) end
        local ok, err = pcall(f, ...)
        if not ok then Library:Notify(tostring(err), 3) end
    end

    function Library:AttemptSave()
        if Library.SaveManager then Library.SaveManager:Save() end
    end

    function Library:GiveSignal(S)
        table.insert(Library.Signals, S)
    end

    function Library:OnUnload(cb) Library.OnUnload = cb end

    function Library:Unload()
        for i = #Library.Signals, 1, -1 do
            pcall(function() Library.Signals[i]:Disconnect() end)
        end
        if Library.OnUnload then pcall(Library.OnUnload) end
        ScreenGui:Destroy()
    end

    function Library:AddToRegistry(Instance, Properties, IsHud)
        local Idx = #Library.Registry + 1
        local Data = { Instance = Instance, Properties = Properties, Idx = Idx }
        table.insert(Library.Registry, Data)
        Library.RegistryMap[Instance] = Data
        if IsHud then table.insert(Library.HudRegistry, Data) end
    end

    function Library:RemoveFromRegistry(Instance)
        local Data = Library.RegistryMap[Instance]
        if not Data then return end
        for i = #Library.Registry, 1, -1 do
            if Library.Registry[i] == Data then table.remove(Library.Registry, i) end
        end
        for i = #Library.HudRegistry, 1, -1 do
            if Library.HudRegistry[i] == Data then table.remove(Library.HudRegistry, i) end
        end
        Library.RegistryMap[Instance] = nil
    end

    function Library:UpdateColorsUsingRegistry()
        for _, Object in next, Library.Registry do
            for Property, ColorIdx in next, Object.Properties do
                if type(ColorIdx) == 'string' then
                    Object.Instance[Property] = Library[ColorIdx]
                elseif type(ColorIdx) == 'function' then
                    Object.Instance[Property] = ColorIdx()
                end
            end
        end
    end

    function Library:MouseIsOverOpenedFrame()
        for Frame in next, Library.OpenedFrames do
            local AbsPos, AbsSize = Frame.AbsolutePosition, Frame.AbsoluteSize
            if Mouse.X >= AbsPos.X and Mouse.X <= AbsPos.X + AbsSize.X
                and Mouse.Y >= AbsPos.Y and Mouse.Y <= AbsPos.Y + AbsSize.Y then
                return true
            end
        end
    end

    function Library:IsMouseOverFrame(Frame)
        local AbsPos, AbsSize = Frame.AbsolutePosition, Frame.AbsoluteSize
        return Mouse.X >= AbsPos.X and Mouse.X <= AbsPos.X + AbsSize.X
            and Mouse.Y >= AbsPos.Y and Mouse.Y <= AbsPos.Y + AbsSize.Y
    end

    function Library:UpdateDependencyBoxes()
        for _, D in next, Library.DependencyBoxes do D:Update() end
    end

    -- ==== LABEL (Nebula style) ====
    function Library:CreateLabel(Properties, IsHud)
        local _Instance = Library:Create('TextLabel', {
            BackgroundTransparency = 1,
            Font = Library.Font,
            TextColor3 = Theme.Text,
            TextSize = 12,
            TextStrokeTransparency = 1,
        })
        Library:AddToRegistry(_Instance, { TextColor3 = 'FontColor' }, IsHud)
        for k, v in pairs(Properties or {}) do _Instance[k] = v end
        return _Instance
    end

    -- ==== DRAGGABLE ====
    function Library:MakeDraggable(Instance, Cutoff)
        Instance.Active = true
        Instance.InputBegan:Connect(function(Input)
            if Input.UserInputType == Enum.UserInputType.MouseButton1
                or Input.UserInputType == Enum.UserInputType.Touch then
                local ObjPos = Vector2.new(
                    Mouse.X - Instance.AbsolutePosition.X,
                    Mouse.Y - Instance.AbsolutePosition.Y
                )
                if ObjPos.Y > (Cutoff or 40) then return end
                while InputService:IsMouseButtonPressed(Enum.UserInputType.MouseButton1) do
                    Instance.Position = UDim2.new(
                        0, Mouse.X - ObjPos.X + (Instance.Size.X.Offset * Instance.AnchorPoint.X),
                        0, Mouse.Y - ObjPos.Y + (Instance.Size.Y.Offset * Instance.AnchorPoint.Y)
                    )
                    RenderStepped:Wait()
                end
            end
        end)
    end

    -- ==== TOOLTIP ====
    function Library:AddToolTip(InfoStr, HoverInstance)
        local X, Y = Library:GetTextBounds(InfoStr, Library.Font, 12)
        local Tooltip = Library:Create('Frame', {
            BackgroundColor3 = Theme.Surface,
            Size = UDim2.fromOffset(X + 12, Y + 8),
            ZIndex = 200,
            Visible = false,
            Parent = ScreenGui,
        })
        corner(Tooltip, 6)
        stroke(Tooltip, Theme.Accent, 1, 0.3)
        local Label = Library:CreateLabel({
            Position = UDim2.fromOffset(6, 4),
            Size = UDim2.fromOffset(X, Y),
            TextSize = 12,
            Text = InfoStr,
            TextColor3 = Theme.Text,
            TextXAlignment = Enum.TextXAlignment.Left,
            ZIndex = 201,
            Parent = Tooltip,
        })
        local hovering = false
        HoverInstance.MouseEnter:Connect(function()
            hovering = true
            Tooltip.Position = UDim2.fromOffset(Mouse.X + 15, Mouse.Y + 12)
            Tooltip.Visible = true
            task.spawn(function()
                while hovering do
                    Tooltip.Position = UDim2.fromOffset(Mouse.X + 15, Mouse.Y + 12)
                    RunService.Heartbeat:Wait()
                end
            end)
        end)
        HoverInstance.MouseLeave:Connect(function()
            hovering = false
            Tooltip.Visible = false
        end)
    end

    function Library:OnHighlight(HighlightInstance, Instance, Properties, PropertiesDefault)
        HighlightInstance.MouseEnter:Connect(function()
            local Reg = Library.RegistryMap[Instance]
            for Property, ColorIdx in next, Properties do
                Instance[Property] = Library[ColorIdx] or ColorIdx
                if Reg and Reg.Properties[Property] then Reg.Properties[Property] = ColorIdx end
            end
        end)
        HighlightInstance.MouseLeave:Connect(function()
            local Reg = Library.RegistryMap[Instance]
            for Property, ColorIdx in next, PropertiesDefault do
                Instance[Property] = Library[ColorIdx] or ColorIdx
                if Reg and Reg.Properties[Property] then Reg.Properties[Property] = ColorIdx end
            end
        end)
    end

    -- ==== NOTIFY (Nebula style toast) ====
    Library.NotificationArea = Library:Create('Frame', {
        BackgroundTransparency = 1,
        Position = UDim2.new(0, 0, 0, 40),
        Size = UDim2.new(0, 320, 0, 220),
        ZIndex = 500,
        Parent = ScreenGui,
    })
    create('UIListLayout', {
        Padding = UDim.new(0, 6),
        FillDirection = Enum.FillDirection.Vertical,
        SortOrder = Enum.SortOrder.LayoutOrder,
        Parent = Library.NotificationArea,
    })

    function Library:Notify(Text, Time)
        Time = Time or 5
        local XSize, YSize = Library:GetTextBounds(Text, Library.Font, 12)
        YSize = YSize + 16
        local Outer = Library:Create('Frame', {
            BackgroundColor3 = Theme.Surface,
            Size = UDim2.fromOffset(0, YSize),
            ClipsDescendants = true,
            ZIndex = 500,
            Parent = Library.NotificationArea,
        })
        corner(Outer, 8)
        stroke(Outer, Theme.Accent, 1, 0.2)
        local AccentBar = Library:Create('Frame', {
            BackgroundColor3 = Theme.Accent,
            BorderSizePixel = 0,
            Position = UDim2.new(0, 0, 0, 0),
            Size = UDim2.new(0, 4, 1, 0),
            ZIndex = 501,
            Parent = Outer,
        })
        corner(AccentBar, 8)
        Library:CreateLabel({
            Position = UDim2.fromOffset(12, 0),
            Size = UDim2.new(1, -16, 1, 0),
            Text = Text,
            TextSize = 12,
            TextColor3 = Theme.Text,
            TextXAlignment = Enum.TextXAlignment.Left,
            ZIndex = 502,
            Parent = Outer,
        })
        tween(Outer, 0.35, { Size = UDim2.fromOffset(XSize + 24, YSize) }, Enum.EasingStyle.Quint)
        task.spawn(function()
            task.wait(Time)
            tween(Outer, 0.3, { Size = UDim2.fromOffset(0, YSize) })
            task.wait(0.35)
            Outer:Destroy()
        end)
    end

    -- ==== WINDOW (Nebula style) ====
    function Library:CreateWindow(...)
        local Args = {...}
        local Config = { AnchorPoint = Vector2.zero }
        if type(...) == 'table' then Config = ... else
            Config.Title = Args[1]
            Config.AutoShow = Args[2] or false
        end
        Config.Title = Config.Title or 'Nebula Hub'
        Config.TabPadding = Config.TabPadding or 6
        Config.MenuFadeTime = Config.MenuFadeTime or 0.2
        Config.Position = Config.Position or UDim2.fromScale(0.5, 0.5)
        Config.Size = Config.Size or UDim2.fromOffset(620, 440)
        if Config.Center then
            Config.AnchorPoint = Vector2.new(0.5, 0.5)
            Config.Position = UDim2.fromScale(0.5, 0.5)
        end

        local Window = { Tabs = {} }

        local Outer = Library:Create('Frame', {
            AnchorPoint = Config.AnchorPoint,
            BackgroundColor3 = Theme.Background,
            BorderSizePixel = 0,
            Position = Config.Position,
            Size = Config.Size,
            Visible = false,
            ZIndex = 1,
            ClipsDescendants = true,
            Parent = ScreenGui,
        })
        corner(Outer, 14)
        stroke(Outer, Theme.Accent, 1.5, 0.15)
        Library:MakeDraggable(Outer, 54)

        -- ==== HEADER ====
        local Header = Library:Create('Frame', {
            BackgroundColor3 = Theme.Panel,
            BorderSizePixel = 0,
            Size = UDim2.new(1, 0, 0, 54),
            ZIndex = 2,
            Parent = Outer,
        })
        corner(Header, 14)
        local HeaderGradient = create('UIGradient', {
            Color = ColorSequence.new(Theme.Accent, Theme.Accent2),
            Rotation = 0,
            Parent = Header,
        })
        -- Mask header bottom to be square
        create('Frame', {
            BackgroundColor3 = Theme.Panel,
            BorderSizePixel = 0,
            Position = UDim2.new(0, 0, 1, -12),
            Size = UDim2.new(1, 0, 0, 12),
            ZIndex = 2,
            Parent = Header,
        })

        Library:CreateLabel({
            Position = UDim2.fromOffset(16, 0),
            Size = UDim2.fromOffset(34, 54),
            Font = Enum.Font.GothamBold,
            Text = '✦',
            TextColor3 = Theme.Text,
            TextSize = 24,
            ZIndex = 3,
            Parent = Header,
        })
        local WindowLabel = Library:CreateLabel({
            Position = UDim2.fromOffset(54, 8),
            Size = UDim2.new(1, -120, 0, 22),
            Font = Enum.Font.GothamBold,
            Text = Config.Title,
            TextColor3 = Theme.Text,
            TextSize = 15,
            TextXAlignment = Enum.TextXAlignment.Left,
            ZIndex = 3,
            Parent = Header,
        })
        Library:CreateLabel({
            Position = UDim2.fromOffset(55, 29),
            Size = UDim2.new(1, -130, 0, 16),
            Font = Enum.Font.Gotham,
            Text = 'Nebula styled · static theme',
            TextColor3 = Theme.Muted,
            TextSize = 10,
            TextXAlignment = Enum.TextXAlignment.Left,
            ZIndex = 3,
            Parent = Header,
        })

        local MinimizeBtn = Library:Create('TextButton', {
            Name = 'Minimize',
            AnchorPoint = Vector2.new(1, 0.5),
            Position = UDim2.new(1, -48, 0.5, 0),
            Size = UDim2.fromOffset(30, 30),
            BackgroundColor3 = Theme.Surface,
            Text = '—',
            TextColor3 = Theme.Text,
            Font = Enum.Font.GothamBold,
            TextSize = 16,
            AutoButtonColor = false,
            ZIndex = 4,
            Parent = Header,
        })
        corner(MinimizeBtn, 8)
        local CloseBtn = Library:Create('TextButton', {
            Name = 'Close',
            AnchorPoint = Vector2.new(1, 0.5),
            Position = UDim2.new(1, -10, 0.5, 0),
            Size = UDim2.fromOffset(30, 30),
            BackgroundColor3 = Theme.Danger,
            BackgroundTransparency = 0.25,
            Text = '×',
            TextColor3 = Theme.Text,
            Font = Enum.Font.GothamBold,
            TextSize = 18,
            AutoButtonColor = false,
            ZIndex = 4,
            Parent = Header,
        })
        corner(CloseBtn, 8)
        CloseBtn.Activated:Connect(function() Library:Toggle() end)

        -- ==== SIDEBAR ====
        local Sidebar = Library:Create('Frame', {
            Position = UDim2.fromOffset(10, 64),
            Size = UDim2.new(0, 158, 1, -74),
            BackgroundColor3 = Theme.Panel,
            BorderSizePixel = 0,
            ZIndex = 2,
            Parent = Outer,
        })
        corner(Sidebar, 10)
        create('UIPadding', {
            PaddingTop = UDim.new(0, 10),
            PaddingLeft = UDim.new(0, 8),
            PaddingRight = UDim.new(0, 8),
            PaddingBottom = UDim.new(0, 10),
            Parent = Sidebar,
        })
        create('UIListLayout', {
            Padding = UDim.new(0, 7),
            SortOrder = Enum.SortOrder.LayoutOrder,
            Parent = Sidebar,
        })

        -- ==== CONTENT ====
        local Content = Library:Create('Frame', {
            Position = UDim2.fromOffset(178, 64),
            Size = UDim2.new(1, -188, 1, -74),
            BackgroundColor3 = Theme.Panel,
            BorderSizePixel = 0,
            ZIndex = 2,
            Parent = Outer,
        })
        corner(Content, 10)

        -- ==== TAB SYSTEM ====
        local ActiveTab = nil
        local TabButtons = {}

        function Window:SetWindowTitle(t)
            WindowLabel.Text = t
        end

        function Window:AddTab(Name)
            local Tab = { Groupboxes = {}, Tabboxes = {}, Name = Name }
            local iconSymbol = '•'

            local TabButton = Library:Create('TextButton', {
                Size = UDim2.new(1, 0, 0, 39),
                BackgroundColor3 = Theme.Surface,
                BackgroundTransparency = 0.65,
                Text = '',
                AutoButtonColor = false,
                ZIndex = 3,
                Parent = Sidebar,
            })
            corner(TabButton, 8)

            local Icon = Library:CreateLabel({
                Position = UDim2.fromOffset(8, 0),
                Size = UDim2.fromOffset(25, 39),
                Font = Enum.Font.GothamBold,
                Text = iconSymbol,
                TextColor3 = Theme.Muted,
                TextSize = 16,
                ZIndex = 4,
                Parent = TabButton,
            })
            local TabButtonLabel = Library:CreateLabel({
                Position = UDim2.fromOffset(35, 0),
                Size = UDim2.new(1, -40, 1, 0),
                Font = Enum.Font.GothamMedium,
                Text = Name,
                TextColor3 = Theme.Muted,
                TextSize = 12,
                TextXAlignment = Enum.TextXAlignment.Left,
                ZIndex = 4,
                Parent = TabButton,
            })

            local TabPage = Library:Create('ScrollingFrame', {
                Name = Name .. 'Page',
                Position = UDim2.fromOffset(10, 10),
                Size = UDim2.new(1, -20, 1, -20),
                BackgroundTransparency = 1,
                BorderSizePixel = 0,
                ScrollBarThickness = 3,
                ScrollBarImageColor3 = Theme.Accent,
                CanvasSize = UDim2.new(),
                AutomaticCanvasSize = Enum.AutomaticSize.Y,
                Visible = false,
                ZIndex = 3,
                Parent = Content,
            })
            create('UIPadding', {
                PaddingRight = UDim.new(0, 5),
                PaddingBottom = UDim.new(0, 6),
                Parent = TabPage,
            })
            create('UIListLayout', {
                Padding = UDim.new(0, 8),
                SortOrder = Enum.SortOrder.LayoutOrder,
                Parent = TabPage,
            })

            table.insert(TabButtons, { Button = TabButton, Icon = Icon, Label = TabButtonLabel, Page = TabPage })

            TabButton.Activated:Connect(function()
                if ActiveTab == Tab then return end
                for _, tb in ipairs(TabButtons) do
                    tb.Page.Visible = false
                    tween(tb.Button, 0.16, { BackgroundColor3 = Theme.Surface, BackgroundTransparency = 0.65 })
                    tb.Icon.TextColor3 = Theme.Muted
                    tb.Label.TextColor3 = Theme.Muted
                end
                TabPage.Visible = true
                tween(TabButton, 0.18, { BackgroundColor3 = Theme.Accent, BackgroundTransparency = 0 })
                Icon.TextColor3 = Theme.Text
                TabButtonLabel.TextColor3 = Theme.Text
                ActiveTab = Tab
            end)

            -- Show first tab by default
            if #TabButtons == 1 then
                TabPage.Visible = true
                TabButton.BackgroundColor3 = Theme.Accent
                TabButton.BackgroundTransparency = 0
                Icon.TextColor3 = Theme.Text
                TabButtonLabel.TextColor3 = Theme.Text
                ActiveTab = Tab
            end

            function Tab:ShowTab()
                TabButton.Activated:Fire()
                TabPage.Visible = true
            end
            function Tab:HideTab() TabPage.Visible = false end
            function Tab:SetLayoutOrder(n) TabButton.LayoutOrder = n end

            function Tab:AddGroupbox(Info)
                local Groupbox = {}
                local BoxOuter = Library:Create('Frame', {
                    BackgroundColor3 = Theme.Surface,
                    BackgroundTransparency = 0.2,
                    BorderSizePixel = 0,
                    Size = UDim2.new(1, 0, 0, 0),
                    ZIndex = 3,
                    Parent = TabPage,
                })
                corner(BoxOuter, 10)
                stroke(BoxOuter, Theme.Off, 1, 0.4)

                local Highlight = Library:Create('Frame', {
                    BackgroundColor3 = Theme.Accent,
                    BorderSizePixel = 0,
                    Position = UDim2.new(0, 10, 0, 0),
                    Size = UDim2.new(0, 26, 0, 3),
                    ZIndex = 5,
                    Parent = BoxOuter,
                })
                corner(Highlight, 2)

                local GroupboxLabel = Library:CreateLabel({
                    Size = UDim2.new(1, -16, 0, 22),
                    Position = UDim2.new(0, 8, 0, 6),
                    TextSize = 11,
                    Font = Enum.Font.GothamBold,
                    Text = string.upper(Info.Name or ''),
                    TextColor3 = Theme.Muted,
                    TextXAlignment = Enum.TextXAlignment.Left,
                    ZIndex = 5,
                    Parent = BoxOuter,
                })

                local Container = Library:Create('Frame', {
                    BackgroundTransparency = 1,
                    Position = UDim2.new(0, 8, 0, 30),
                    Size = UDim2.new(1, -16, 0, 0),
                    ZIndex = 4,
                    Parent = BoxOuter,
                })
                create('UIListLayout', {
                    FillDirection = Enum.FillDirection.Vertical,
                    SortOrder = Enum.SortOrder.LayoutOrder,
                    Padding = UDim.new(0, 6),
                    Parent = Container,
                })

                function Groupbox:Resize()
                    local Layout = Container:FindFirstChildOfClass('UIListLayout')
                    if Layout then
                        BoxOuter.Size = UDim2.new(1, 0, 0, Layout.AbsoluteContentSize.Y + 38)
                    end
                end
                Layout = Container:FindFirstChildOfClass('UIListLayout')
                Layout:GetPropertyChangedSignal('AbsoluteContentSize'):Connect(function()
                    BoxOuter.Size = UDim2.new(1, 0, 0, Layout.AbsoluteContentSize.Y + 38)
                end)

                Groupbox.Container = Container
                setmetatable(Groupbox, BaseGroupbox)
                Tab.Groupboxes[Info.Name] = Groupbox
                return Groupbox
            end

            function Tab:AddLeftGroupbox(Name) return Tab:AddGroupbox({ Name = Name }) end
            function Tab:AddRightGroupbox(Name) return Tab:AddGroupbox({ Name = Name }) end

            Window.Tabs[Name] = Tab
            return Tab
        end

        Window.Holder = Outer

        -- ==== MENU TOGGLE (fade) ====
        local MenuToggled = false
        local Fading = false
        function Library:Toggle()
            if Fading then return end
            Fading = true
            MenuToggled = not MenuToggled
            local ft = Config.MenuFadeTime
            if MenuToggled then
                Outer.Visible = true
                tween(Outer, ft, { BackgroundTransparency = 0 })
            else
                tween(Outer, ft, { BackgroundTransparency = 1 })
                task.wait(ft)
                Outer.Visible = false
            end
            Fading = false
        end
        Library.ToggleKeybind = nil

        Library:GiveSignal(InputService.InputBegan:Connect(function(Input, Processed)
            if type(Library.ToggleKeybind) == 'table' and Library.ToggleKeybind.Type == 'KeyPicker' then
                if Input.UserInputType == Enum.UserInputType.Keyboard
                    and Input.KeyCode.Name == Library.ToggleKeybind.Value then
                    task.spawn(Library.Toggle)
                end
            elseif Input.KeyCode == Enum.KeyCode.RightShift and not Processed then
                task.spawn(Library.Toggle)
            end
        end))

        if Config.AutoShow then task.spawn(Library.Toggle) end

        return Window
    end

    -- ==== BASE COMPONENT BUILDERS ====

    -- Helper: create a "row" (Surface box) with label + optional right slot
    local function createRow(parent, height, text, risky)
        local Row = Library:Create('Frame', {
            BackgroundColor3 = Theme.Surface,
            BackgroundTransparency = 0.2,
            BorderSizePixel = 0,
            Size = UDim2.new(1, 0, 0, height),
            ZIndex = 4,
            Parent = parent,
        })
        corner(Row, 8)
        local RowLabel = Library:CreateLabel({
            Position = UDim2.fromOffset(11, 0),
            Size = UDim2.new(1, -90, 1, 0),
            Font = Enum.Font.GothamMedium,
            Text = text or '',
            TextColor3 = risky and Theme.Risk or Theme.Text,
            TextSize = 12,
            TextXAlignment = Enum.TextXAlignment.Left,
            ZIndex = 5,
            Parent = Row,
        })
        Library:AddToRegistry(RowLabel, { TextColor3 = risky and 'RiskColor' or 'FontColor' })
        return Row, RowLabel
    end

    -- ===== BASE ADDONS (ColorPicker + KeyPicker) =====
    local BaseAddons = {}
    do
        local Funcs = {}

        function Funcs:AddColorPicker(Idx, Info)
            local ToggleLabel = self.TextLabel
            Info = Info or {}
            Info.Default = Info.Default or Color3.fromRGB(138, 75, 235)
            Info.Title = Info.Title or 'Color picker'

            local ColorPicker = {
                Value = Info.Default,
                Transparency = Info.Transparency or 0,
                Type = 'ColorPicker',
                Title = Info.Title,
                Callback = Info.Callback or function() end,
            }
            function ColorPicker:SetHSVFromRGB(Color)
                local H, S, V = Color3.toHSV(Color)
                ColorPicker.Hue, ColorPicker.Sat, ColorPicker.Vib = H, S, V
            end
            ColorPicker:SetHSVFromRGB(ColorPicker.Value)

            local DisplayFrame = Library:Create('Frame', {
                BackgroundColor3 = ColorPicker.Value,
                BorderSizePixel = 0,
                Size = UDim2.fromOffset(28, 14),
                ZIndex = 6,
                Parent = ToggleLabel,
            })
            corner(DisplayFrame, 4)
            stroke(DisplayFrame, Theme.Off, 1, 0.2)

            local PickerFrameOuter = Library:Create('Frame', {
                Name = 'Color',
                BackgroundColor3 = Theme.Panel,
                BorderSizePixel = 0,
                Position = UDim2.fromOffset(0, 0),
                Size = UDim2.fromOffset(230, Info.Transparency and 271 or 253),
                Visible = false,
                ZIndex = 300,
                Parent = ScreenGui,
            })
            corner(PickerFrameOuter, 10)
            stroke(PickerFrameOuter, Theme.Accent, 1, 0.2)
            DisplayFrame:GetPropertyChangedSignal('AbsolutePosition'):Connect(function()
                PickerFrameOuter.Position = UDim2.fromOffset(
                    DisplayFrame.AbsolutePosition.X,
                    DisplayFrame.AbsolutePosition.Y + 18
                )
            end)

            local PickerFrameInner = Library:Create('Frame', {
                BackgroundColor3 = Theme.Background,
                BorderSizePixel = 0,
                Size = UDim2.new(1, -8, 1, -8),
                Position = UDim2.fromOffset(4, 4),
                ZIndex = 301,
                Parent = PickerFrameOuter,
            })
            corner(PickerFrameInner, 8)

            local SatVibMap = Library:Create('ImageLabel', {
                BorderSizePixel = 0,
                Position = UDim2.fromOffset(6, 28),
                Size = UDim2.new(1, -36, 0, 200),
                Image = 'rbxassetid://4155801252',
                ZIndex = 302,
                Parent = PickerFrameInner,
            })
            local Cursor = Library:Create('ImageLabel', {
                AnchorPoint = Vector2.new(0.5, 0.5),
                Size = UDim2.fromOffset(8, 8),
                BackgroundTransparency = 1,
                Image = 'rbxassetid://9619665977',
                ImageColor3 = Color3.new(0,0,0),
                ZIndex = 303,
                Parent = SatVibMap,
            })

            local HueSelector = Library:Create('Frame', {
                BorderSizePixel = 0,
                Position = UDim2.new(1, -26, 0, 28),
                Size = UDim2.new(0, 18, 0, 200),
                ZIndex = 302,
                Parent = PickerFrameInner,
            })
            corner(HueSelector, 4)
            local Seq = {}
            for h = 0, 1, 0.1 do
                table.insert(Seq, ColorSequenceKeypoint.new(h, Color3.fromHSV(h, 1, 1)))
            end
            create('UIGradient', {
                Color = ColorSequence.new(Seq),
                Rotation = 90,
                Parent = HueSelector,
            })
            local HueCursor = Library:Create('Frame', {
                BackgroundColor3 = Color3.new(1,1,1),
                AnchorPoint = Vector2.new(0, 0.5),
                BorderSizePixel = 0,
                Size = UDim2.new(1, 0, 0, 2),
                ZIndex = 303,
                Parent = HueSelector,
            })

            local HueBox = Library:Create('TextBox', {
                BackgroundColor3 = Theme.Surface,
                BorderSizePixel = 0,
                Position = UDim2.new(0, 6, 0, 234),
                Size = UDim2.new(0.5, -8, 0, 20),
                Font = Library.Font,
                PlaceholderColor3 = Theme.Muted,
                PlaceholderText = 'Hex',
                Text = '#' .. ColorPicker.Value:ToHex(),
                TextColor3 = Theme.Text,
                TextSize = 11,
                ZIndex = 303,
                Parent = PickerFrameInner,
            })
            corner(HueBox, 6)

            local RgbBox = Library:Create('TextBox', {
                BackgroundColor3 = Theme.Surface,
                BorderSizePixel = 0,
                Position = UDim2.new(0.5, 2, 0, 234),
                Size = UDim2.new(0.5, -8, 0, 20),
                Font = Library.Font,
                PlaceholderColor3 = Theme.Muted,
                PlaceholderText = 'RGB',
                Text = string.format('%d, %d, %d',
                    math.floor(ColorPicker.Value.R*255),
                    math.floor(ColorPicker.Value.G*255),
                    math.floor(ColorPicker.Value.B*255)),
                TextColor3 = Theme.Text,
                TextSize = 11,
                ZIndex = 303,
                Parent = PickerFrameInner,
            })
            corner(RgbBox, 6)

            local DisplayLabel = Library:CreateLabel({
                Position = UDim2.fromOffset(8, 6),
                Size = UDim2.new(1, -16, 0, 16),
                TextSize = 11,
                Font = Enum.Font.GothamBold,
                Text = ColorPicker.Title,
                TextColor3 = Theme.Text,
                TextXAlignment = Enum.TextXAlignment.Left,
                ZIndex = 303,
                Parent = PickerFrameInner,
            })

            function ColorPicker:Display()
                ColorPicker.Value = Color3.fromHSV(ColorPicker.Hue, ColorPicker.Sat, ColorPicker.Vib)
                SatVibMap.BackgroundColor3 = Color3.fromHSV(ColorPicker.Hue, 1, 1)
                DisplayFrame.BackgroundColor3 = ColorPicker.Value
                DisplayFrame.BackgroundTransparency = ColorPicker.Transparency
                Cursor.Position = UDim2.new(ColorPicker.Sat, 0, 1 - ColorPicker.Vib, 0)
                HueCursor.Position = UDim2.new(0, 0, ColorPicker.Hue, 0)
                HueBox.Text = '#' .. ColorPicker.Value:ToHex()
                RgbBox.Text = string.format('%d, %d, %d',
                    math.floor(ColorPicker.Value.R*255),
                    math.floor(ColorPicker.Value.G*255),
                    math.floor(ColorPicker.Value.B*255))
                Library:SafeCallback(ColorPicker.Callback, ColorPicker.Value)
                Library:SafeCallback(ColorPicker.Changed, ColorPicker.Value)
            end

            function ColorPicker:OnChanged(f)
                ColorPicker.Changed = f
                f(ColorPicker.Value)
            end
            function ColorPicker:Show()
                for Frame in next, Library.OpenedFrames do
                    if Frame.Name == 'Color' then Frame.Visible = false; Library.OpenedFrames[Frame] = nil end
                end
                PickerFrameOuter.Visible = true
                Library.OpenedFrames[PickerFrameOuter] = true
            end
            function ColorPicker:Hide()
                PickerFrameOuter.Visible = false
                Library.OpenedFrames[PickerFrameOuter] = nil
            end
            function ColorPicker:SetValueRGB(Color, T)
                ColorPicker.Transparency = T or 0
                ColorPicker:SetHSVFromRGB(Color)
                ColorPicker:Display()
            end
            function ColorPicker:SetValue(HSV, T)
                ColorPicker:SetValueRGB(Color3.fromHSV(HSV[1], HSV[2], HSV[3]), T)
            end

            SatVibMap.InputBegan:Connect(function(Input)
                if Input.UserInputType == Enum.UserInputType.MouseButton1 or Input.UserInputType == Enum.UserInputType.Touch then
                    while InputService:IsMouseButtonPressed(Enum.UserInputType.MouseButton1) do
                        local MinX = SatVibMap.AbsolutePosition.X
                        local MaxX = MinX + SatVibMap.AbsoluteSize.X
                        local MinY = SatVibMap.AbsolutePosition.Y
                        local MaxY = MinY + SatVibMap.AbsoluteSize.Y
                        local MX = math.clamp(Mouse.X, MinX, MaxX)
                        local MY = math.clamp(Mouse.Y, MinY, MaxY)
                        ColorPicker.Sat = (MX - MinX) / (MaxX - MinX)
                        ColorPicker.Vib = 1 - ((MY - MinY) / (MaxY - MinY))
                        ColorPicker:Display()
                        RenderStepped:Wait()
                    end
                    Library:AttemptSave()
                end
            end)
            HueSelector.InputBegan:Connect(function(Input)
                if Input.UserInputType == Enum.UserInputType.MouseButton1 or Input.UserInputType == Enum.UserInputType.Touch then
                    while InputService:IsMouseButtonPressed(Enum.UserInputType.MouseButton1) do
                        local MinY = HueSelector.AbsolutePosition.Y
                        local MaxY = MinY + HueSelector.AbsoluteSize.Y
                        local MY = math.clamp(Mouse.Y, MinY, MaxY)
                        ColorPicker.Hue = (MY - MinY) / (MaxY - MinY)
                        ColorPicker:Display()
                        RenderStepped:Wait()
                    end
                    Library:AttemptSave()
                end
            end)
            DisplayFrame.InputBegan:Connect(function(Input)
                if Input.UserInputType == Enum.UserInputType.MouseButton1 or Input.UserInputType == Enum.UserInputType.Touch then
                    if PickerFrameOuter.Visible then ColorPicker:Hide() else ColorPicker:Show() end
                end
            end)

            ColorPicker:Display()
            Options[Idx] = ColorPicker
            return self
        end

        function Funcs:AddKeyPicker(Idx, Info)
            local ParentObj = self
            local ToggleLabel = self.TextLabel
            Info = Info or {}
            Info.Default = Info.Default or 'None'
            Info.Text = Info.Text or 'Keybind'

            local KeyPicker = {
                Value = Info.Default,
                Toggled = false,
                Mode = Info.Mode or 'Toggle',
                Type = 'KeyPicker',
                Callback = Info.Callback or function() end,
                ChangedCallback = Info.ChangedCallback or function() end,
                SyncToggleState = Info.SyncToggleState or false,
            }
            if KeyPicker.SyncToggleState then
                Info.Modes = { 'Toggle' }
                Info.Mode = 'Toggle'
            end

            local PickOuter = Library:Create('Frame', {
                BackgroundColor3 = Theme.Surface,
                BorderSizePixel = 0,
                Size = UDim2.fromOffset(44, 18),
                ZIndex = 6,
                Parent = ToggleLabel,
            })
            corner(PickOuter, 6)
            local DisplayLabel = Library:CreateLabel({
                Size = UDim2.new(1, 0, 1, 0),
                TextSize = 11,
                Font = Enum.Font.GothamBold,
                Text = Info.Default,
                TextColor3 = Theme.Text,
                TextWrapped = true,
                ZIndex = 7,
                Parent = PickOuter,
            })

            local Picking = false
            PickOuter.InputBegan:Connect(function(Input)
                if Input.UserInputType == Enum.UserInputType.MouseButton1 or Input.UserInputType == Enum.UserInputType.Touch then
                    Picking = true
                    DisplayLabel.Text = '...'
                    local ev
                    ev = InputService.InputBegan:Connect(function(I)
                        local Key
                        if I.UserInputType == Enum.UserInputType.Keyboard then Key = I.KeyCode.Name
                        elseif I.UserInputType == Enum.UserInputType.MouseButton1 then Key = 'MB1'
                        elseif I.UserInputType == Enum.UserInputType.MouseButton2 then Key = 'MB2' end
                        if Key then
                            Picking = false
                            DisplayLabel.Text = Key
                            KeyPicker.Value = Key
                            Library:SafeCallback(KeyPicker.ChangedCallback, I.KeyCode or I.UserInputType)
                            Library:AttemptSave()
                            ev:Disconnect()
                        end
                    end)
                end
            end)

            Library:GiveSignal(InputService.InputBegan:Connect(function(Input)
                if Picking then return end
                if KeyPicker.Mode == 'Toggle' then
                    local Key = KeyPicker.Value
                    if Key == 'MB1' and Input.UserInputType == Enum.UserInputType.MouseButton1
                        or Key == 'MB2' and Input.UserInputType == Enum.UserInputType.MouseButton2
                        or Input.UserInputType == Enum.UserInputType.Keyboard and Input.KeyCode.Name == Key then
                        KeyPicker.Toggled = not KeyPicker.Toggled
                        if ParentObj.Type == 'Toggle' and KeyPicker.SyncToggleState then
                            ParentObj:SetValue(not ParentObj.Value)
                        end
                        Library:SafeCallback(KeyPicker.Callback, KeyPicker.Toggled)
                    end
                end
            end))

            function KeyPicker:GetState()
                if KeyPicker.Mode == 'Always' then return true
                elseif KeyPicker.Mode == 'Hold' then
                    if KeyPicker.Value == 'None' then return false end
                    if KeyPicker.Value == 'MB1' then return InputService:IsMouseButtonPressed(Enum.UserInputType.MouseButton1) end
                    if KeyPicker.Value == 'MB2' then return InputService:IsMouseButtonPressed(Enum.UserInputType.MouseButton2) end
                    return InputService:IsKeyDown(Enum.KeyCode[KeyPicker.Value])
                else
                    return KeyPicker.Toggled
                end
            end
            function KeyPicker:SetValue(Data)
                DisplayLabel.Text = Data[1]
                KeyPicker.Value = Data[1]
            end
            function KeyPicker:OnClick(cb) KeyPicker.Clicked = cb end
            function KeyPicker:OnChanged(cb) KeyPicker.Changed = cb; cb(KeyPicker.Value) end

            if ParentObj.Addons then table.insert(ParentObj.Addons, KeyPicker) end
            Options[Idx] = KeyPicker
            return self
        end

        BaseAddons.__index = Funcs
        BaseAddons.__namecall = function(t, k, ...) return Funcs[k](...) end
    end

    -- ===== BASE GROUPBOX (component builders) =====
    local BaseGroupbox = {}
    do
        local Funcs = {}

        function Funcs:AddBlank(Size)
            Library:Create('Frame', {
                BackgroundTransparency = 1,
                Size = UDim2.new(1, 0, 0, Size),
                ZIndex = 1,
                Parent = self.Container,
            })
        end

        function Funcs:AddLabel(Text, DoesWrap)
            local Label = {}
            local TextLabel = Library:CreateLabel({
                Size = UDim2.new(1, 0, 0, 16),
                TextSize = 12,
                Font = Enum.Font.GothamMedium,
                Text = Text,
                TextWrapped = DoesWrap or false,
                TextColor3 = Theme.Muted,
                TextXAlignment = Enum.TextXAlignment.Left,
                ZIndex = 5,
                Parent = self.Container,
            })
            Label.TextLabel = TextLabel
            Label.Container = self.Container
            function Label:SetText(t) TextLabel.Text = t end
            if not DoesWrap then setmetatable(Label, BaseAddons) end
            return Label
        end

        function Funcs:AddButton(...)
            local Button = {}
            local function Process(_, ...)
                local P = select(1, ...)
                if type(P) == 'table' then
                    Button.Text = P.Text
                    Button.Func = P.Func
                    Button.Tooltip = P.Tooltip
                else
                    Button.Text = select(1, ...)
                    Button.Func = select(2, ...)
                end
                Button.Func = Button.Func or function() end
            end
            Process('Button', ...)

            local Parent = self
            local Btn = Library:Create('TextButton', {
                BackgroundColor3 = Theme.Accent,
                BorderSizePixel = 0,
                Size = UDim2.new(1, 0, 0, 34),
                Text = Button.Text or '',
                TextColor3 = Theme.Text,
                Font = Enum.Font.GothamBold,
                TextSize = 12,
                AutoButtonColor = false,
                ZIndex = 5,
                Parent = Parent.Container,
            })
            corner(Btn, 8)
            create('UIGradient', {
                Color = ColorSequence.new(Theme.Accent, Theme.Accent2),
                Rotation = 0,
                Parent = Btn,
            })
            Btn.MouseEnter:Connect(function() tween(Btn, 0.15, { BackgroundTransparency = 0.12 }) end)
            Btn.MouseLeave:Connect(function() tween(Btn, 0.15, { BackgroundTransparency = 0 }) end)
            Btn.Activated:Connect(function()
                tween(Btn, 0.08, { BackgroundTransparency = 0.25 })
                task.delay(0.09, function()
                    if Btn.Parent then tween(Btn, 0.12, { BackgroundTransparency = 0 }) end
                end)
                Library:SafeCallback(Button.Func)
            end)

            if type(Button.Tooltip) == 'string' then
                Library:AddToolTip(Button.Tooltip, Btn)
            end

            function Button:AddTooltip(t)
                if type(t) == 'string' then Library:AddToolTip(t, Btn) end
                return self
            end
            function Button:AddButton(...)
                -- nested buttons not supported in Nebula layout; fallback no-op
                return self
            end
            return Button
        end

        function Funcs:AddDivider()
            local Div = Library:Create('Frame', {
                BackgroundColor3 = Theme.Off,
                BackgroundTransparency = 0.5,
                BorderSizePixel = 0,
                Size = UDim2.new(1, 0, 0, 1),
                ZIndex = 4,
                Parent = self.Container,
            })
        end

        function Funcs:AddInput(Idx, Info)
            Info = Info or {}
            Info.Text = Info.Text or ''
            Info.Default = Info.Default or ''
            local Textbox = {
                Value = Info.Default,
                Numeric = Info.Numeric or false,
                Finished = Info.Finished or false,
                Type = 'Input',
                Callback = Info.Callback or function() end,
            }
            local Row, RowLabel = createRow(self.Container, 20, Info.Text)
            Row.Size = UDim2.new(1, 0, 0, 20)
            Row.BackgroundTransparency = 1
            RowLabel.Size = UDim2.new(1, 0, 1, 0)
            RowLabel.TextColor3 = Theme.Muted
            Library:Create('UIPadding', {
                PaddingTop = UDim.new(0, 2),
                Parent = Row,
            })
            local Box = Library:Create('TextBox', {
                BackgroundColor3 = Theme.Surface,
                BorderSizePixel = 0,
                Position = UDim2.new(0, 0, 0, 22),
                Size = UDim2.new(1, 0, 0, 30),
                Font = Library.Font,
                PlaceholderColor3 = Theme.Muted,
                PlaceholderText = Info.Placeholder or '',
                Text = Info.Default,
                TextColor3 = Theme.Text,
                TextSize = 12,
                TextXAlignment = Enum.TextXAlignment.Left,
                ZIndex = 6,
                Parent = self.Container,
            })
            corner(Box, 8)
            create('UIPadding', { PaddingLeft = UDim.new(0, 10), Parent = Box })

            -- Reparent label above the box; adjust container padding
            RowLabel.Parent = self.Container
            RowLabel.LayoutOrder = -1

            function Textbox:SetValue(t)
                if Info.MaxLength and #t > Info.MaxLength then t = t:sub(1, Info.MaxLength) end
                if Textbox.Numeric and not tonumber(t) and #t > 0 then t = Textbox.Value end
                Textbox.Value = t
                Box.Text = t
                Library:SafeCallback(Textbox.Callback, Textbox.Value)
                Library:SafeCallback(Textbox.Changed, Textbox.Value)
            end
            function Textbox:OnChanged(f)
                Textbox.Changed = f
                f(Textbox.Value)
            end

            if Textbox.Finished then
                Box.FocusLost:Connect(function(enter)
                    if not enter then return end
                    Textbox:SetValue(Box.Text)
                    Library:AttemptSave()
                end)
            else
                Box:GetPropertyChangedSignal('Text'):Connect(function()
                    Textbox:SetValue(Box.Text)
                    Library:AttemptSave()
                end)
            end

            Options[Idx] = Textbox
            return Textbox
        end

        function Funcs:AddToggle(Idx, Info)
            Info = Info or {}
            Info.Text = Info.Text or ''
            local Toggle = {
                Value = Info.Default or false,
                Type = 'Toggle',
                Callback = Info.Callback or function() end,
                Addons = {},
                Risky = Info.Risky,
            }
            local Row, RowLabel = createRow(self.Container, 39, Info.Text, Toggle.Risky)
            Row.BackgroundTransparency = 0.2
            local Switch = Library:Create('Frame', {
                AnchorPoint = Vector2.new(1, 0.5),
                Position = UDim2.new(1, -10, 0.5, 0),
                Size = UDim2.fromOffset(42, 22),
                BackgroundColor3 = Toggle.Value and Theme.Accent or Theme.Off,
                BorderSizePixel = 0,
                ZIndex = 6,
                Parent = Row,
            })
            corner(Switch, 11)
            local Knob = Library:Create('Frame', {
                Position = Toggle.Value and UDim2.new(1, -19, 0.5, -8) or UDim2.new(0, 3, 0.5, -8),
                Size = UDim2.fromOffset(16, 16),
                BackgroundColor3 = Theme.Text,
                BorderSizePixel = 0,
                ZIndex = 7,
                Parent = Switch,
            })
            corner(Knob, 8)
            local Hitbox = Library:Create('TextButton', {
                Size = UDim2.fromScale(1, 1),
                BackgroundTransparency = 1,
                Text = '',
                AutoButtonColor = false,
                ZIndex = 8,
                Parent = Row,
            })
            function Toggle:Display()
                tween(Switch, 0.16, {
                    BackgroundColor3 = Toggle.Value and Theme.Accent or Theme.Off,
                })
                tween(Knob, 0.18, {
                    Position = Toggle.Value and UDim2.new(1, -19, 0.5, -8) or UDim2.new(0, 3, 0.5, -8),
                })
            end
            function Toggle:SetValue(b)
                b = not not b
                Toggle.Value = b
                Toggle:Display()
                for _, A in next, Toggle.Addons do
                    if A.Type == 'KeyPicker' and A.SyncToggleState then
                        A.Toggled = b
                    end
                end
                Library:SafeCallback(Toggle.Callback, Toggle.Value)
                Library:SafeCallback(Toggle.Changed, Toggle.Value)
                Library:UpdateDependencyBoxes()
            end
            function Toggle:OnChanged(f)
                Toggle.Changed = f
                f(Toggle.Value)
            end
            function Toggle:UpdateColors() Toggle:Display() end

            Hitbox.Activated:Connect(function()
                Toggle:SetValue(not Toggle.Value)
                Library:AttemptSave()
            end)

            if type(Info.Tooltip) == 'string' then
                Library:AddToolTip(Info.Tooltip, Hitbox)
            end

            Toggle.TextLabel = RowLabel
            Toggle.Container = self.Container
            setmetatable(Toggle, BaseAddons)
            Toggles[Idx] = Toggle
            return Toggle
        end

        function Funcs:AddSlider(Idx, Info)
            Info = Info or {}
            Info.Default = Info.Default or 0
            Info.Min = Info.Min or 0
            Info.Max = Info.Max or 100
            Info.Rounding = Info.Rounding or 0
            Info.Text = Info.Text or ''
            local Slider = {
                Value = Info.Default,
                Min = Info.Min,
                Max = Info.Max,
                Rounding = Info.Rounding,
                MaxSize = 220,
                Type = 'Slider',
                Callback = Info.Callback or function() end,
            }
            local Frame = Library:Create('Frame', {
                BackgroundColor3 = Theme.Surface,
                BackgroundTransparency = 0.2,
                BorderSizePixel = 0,
                Size = UDim2.new(1, 0, 0, 58),
                ZIndex = 4,
                Parent = self.Container,
            })
            corner(Frame, 8)
            local SliderLabel = Library:CreateLabel({
                Position = UDim2.fromOffset(11, 6),
                Size = UDim2.new(1, -90, 0, 20),
                Font = Enum.Font.GothamMedium,
                Text = Info.Text,
                TextColor3 = Theme.Text,
                TextSize = 12,
                TextXAlignment = Enum.TextXAlignment.Left,
                ZIndex = 5,
                Parent = Frame,
            })
            local ValueLabel = Library:CreateLabel({
                Position = UDim2.new(1, -70, 0, 6),
                Size = UDim2.fromOffset(58, 20),
                Font = Enum.Font.GothamBold,
                Text = tostring(Slider.Value),
                TextColor3 = Theme.Accent2,
                TextSize = 12,
                TextXAlignment = Enum.TextXAlignment.Right,
                ZIndex = 5,
                Parent = Frame,
            })
            local Bar = Library:Create('Frame', {
                Position = UDim2.new(0, 11, 0, 37),
                Size = UDim2.new(1, -22, 0, 6),
                BackgroundColor3 = Theme.Off,
                BorderSizePixel = 0,
                ZIndex = 5,
                Parent = Frame,
            })
            corner(Bar, 3)
            local ratio = (Slider.Value - Slider.Min) / (Slider.Max - Slider.Min)
            local Fill = Library:Create('Frame', {
                Size = UDim2.new(ratio, 0, 1, 0),
                BackgroundColor3 = Theme.Accent,
                BorderSizePixel = 0,
                ZIndex = 6,
                Parent = Bar,
            })
            corner(Fill, 3)
            local Knob = Library:Create('Frame', {
                AnchorPoint = Vector2.new(0.5, 0.5),
                Position = UDim2.new(ratio, 0, 0.5, 0),
                Size = UDim2.fromOffset(14, 14),
                BackgroundColor3 = Theme.Text,
                BorderSizePixel = 0,
                ZIndex = 7,
                Parent = Bar,
            })
            corner(Knob, 7)

            local function round(v)
                if Slider.Rounding == 0 then return math.floor(v) end
                return tonumber(string.format('%.' .. Slider.Rounding .. 'f', v))
            end
            function Slider:Display()
                ValueLabel.Text = tostring(Slider.Value)
                local a = (Slider.Value - Slider.Min) / (Slider.Max - Slider.Min)
                Fill.Size = UDim2.new(a, 0, 1, 0)
                Knob.Position = UDim2.new(a, 0, 0.5, 0)
            end
            function Slider:SetValue(v)
                local n = tonumber(v)
                if not n then return end
                Slider.Value = round(math.clamp(n, Slider.Min, Slider.Max))
                Slider:Display()
                Library:SafeCallback(Slider.Callback, Slider.Value)
                Library:SafeCallback(Slider.Changed, Slider.Value)
            end
            function Slider:OnChanged(f)
                Slider.Changed = f
                f(Slider.Value)
            end
            function Slider:UpdateColors() end

            local dragging = false
            local function setFromX(x)
                local w = math.max(Bar.AbsoluteSize.X, 1)
                local a = math.clamp((x - Bar.AbsolutePosition.X) / w, 0, 1)
                Slider.Value = round(Slider.Min + (Slider.Max - Slider.Min) * a)
                Slider:Display()
                Library:SafeCallback(Slider.Callback, Slider.Value)
                Library:SafeCallback(Slider.Changed, Slider.Value)
            end
            Bar.InputBegan:Connect(function(input)
                if input.UserInputType == Enum.UserInputType.MouseButton1
                    or input.UserInputType == Enum.UserInputType.Touch then
                    dragging = true
                    setFromX(input.Position.X)
                end
            end)
            InputService.InputChanged:Connect(function(input)
                if dragging and (input.UserInputType == Enum.UserInputType.MouseMovement
                    or input.UserInputType == Enum.UserInputType.Touch) then
                    setFromX(input.Position.X)
                end
            end)
            InputService.InputEnded:Connect(function(input)
                if input.UserInputType == Enum.UserInputType.MouseButton1
                    or input.UserInputType == Enum.UserInputType.Touch then
                    if dragging then
                        dragging = false
                        Library:AttemptSave()
                    end
                end
            end)

            Options[Idx] = Slider
            return Slider
        end

        function Funcs:AddDropdown(Idx, Info)
            Info = Info or {}
            Info.Values = Info.Values or {}
            Info.Multi = Info.Multi or false
            Info.AllowNull = Info.AllowNull or false
            local Dropdown = {
                Values = Info.Values,
                Value = Info.Multi and {} or nil,
                Multi = Info.Multi,
                Type = 'Dropdown',
                Callback = Info.Callback or function() end,
            }

            local Frame = Library:Create('Frame', {
                BackgroundColor3 = Theme.Surface,
                BackgroundTransparency = 0.2,
                BorderSizePixel = 0,
                Size = UDim2.new(1, 0, 0, 39),
                ZIndex = 4,
                Parent = self.Container,
            })
            corner(Frame, 8)
            local Label = Library:CreateLabel({
                Position = UDim2.fromOffset(11, 0),
                Size = UDim2.new(0.5, -16, 1, 0),
                Font = Enum.Font.GothamMedium,
                Text = Info.Text or '--',
                TextColor3 = Theme.Muted,
                TextSize = 12,
                TextXAlignment = Enum.TextXAlignment.Left,
                ZIndex = 5,
                Parent = Frame,
            })
            local ItemList = Library:CreateLabel({
                Position = UDim2.new(0.5, 0, 0, 0),
                Size = UDim2.new(0.5, -30, 1, 0),
                Font = Enum.Font.GothamBold,
                Text = '--',
                TextColor3 = Theme.Accent2,
                TextSize = 12,
                TextXAlignment = Enum.TextXAlignment.Right,
                ZIndex = 5,
                Parent = Frame,
            })
            local Arrow = Library:CreateLabel({
                Position = UDim2.new(1, -22, 0, 0),
                Size = UDim2.fromOffset(18, 39),
                Font = Enum.Font.GothamBold,
                Text = '▾',
                TextColor3 = Theme.Muted,
                TextSize = 14,
                ZIndex = 5,
                Parent = Frame,
            })

            local ListOuter = Library:Create('Frame', {
                BackgroundColor3 = Theme.Panel,
                BorderSizePixel = 0,
                Size = UDim2.fromOffset(Frame.AbsoluteSize.X, 0),
                Visible = false,
                ZIndex = 300,
                Parent = ScreenGui,
            })
            corner(ListOuter, 8)
            stroke(ListOuter, Theme.Accent, 1, 0.2)
            local ListScroll = Library:Create('ScrollingFrame', {
                BackgroundTransparency = 1,
                BorderSizePixel = 0,
                Size = UDim2.new(1, -8, 1, -8),
                Position = UDim2.fromOffset(4, 4),
                CanvasSize = UDim2.new(),
                AutomaticCanvasSize = Enum.AutomaticSize.Y,
                ScrollBarThickness = 3,
                ScrollBarImageColor3 = Theme.Accent,
                ZIndex = 301,
                Parent = ListOuter,
            })
            create('UIListLayout', {
                FillDirection = Enum.FillDirection.Vertical,
                SortOrder = Enum.SortOrder.LayoutOrder,
                Padding = UDim.new(0, 2),
                Parent = ListScroll,
            })

            local buttons = {}

            function Dropdown:Display()
                if Dropdown.Multi then
                    local str = ''
                    for v, b in pairs(Dropdown.Value) do
                        if b then str = str .. v .. ', ' end
                    end
                    str = str:sub(1, #str - 2)
                    ItemList.Text = str == '' and '--' or str
                else
                    ItemList.Text = Dropdown.Value or '--'
                end
            end

            function Dropdown:BuildList()
                for _, c in ipairs(ListScroll:GetChildren()) do
                    if not c:IsA('UIListLayout') then c:Destroy() end
                end
                buttons = {}
                local count = 0
                for _, v in ipairs(Dropdown.Values) do
                    count = count + 1
                    local Btn = Library:Create('TextButton', {
                        BackgroundColor3 = Theme.Surface,
                        BackgroundTransparency = 0.3,
                        BorderSizePixel = 0,
                        Size = UDim2.new(1, 0, 0, 26),
                        Text = '',
                        AutoButtonColor = false,
                        ZIndex = 302,
                        Parent = ListScroll,
                    })
                    corner(Btn, 6)
                    local Lbl = Library:CreateLabel({
                        Position = UDim2.fromOffset(8, 0),
                        Size = UDim2.new(1, -16, 1, 0),
                        Font = Enum.Font.GothamMedium,
                        Text = v,
                        TextColor3 = Theme.Text,
                        TextSize = 12,
                        TextXAlignment = Enum.TextXAlignment.Left,
                        ZIndex = 303,
                        Parent = Btn,
                    })
                    local function update()
                        local sel = Info.Multi and Dropdown.Value[v] or Dropdown.Value == v
                        Lbl.TextColor3 = sel and Theme.Accent2 or Theme.Text
                    end
                    update()
                    Btn.Activated:Connect(function()
                        if Info.Multi then
                            Dropdown.Value[v] = not Dropdown.Value[v] or nil
                        else
                            Dropdown.Value = (Dropdown.Value == v) and nil or v
                            for _, b in pairs(buttons) do b() end
                        end
                        update()
                        Dropdown:Display()
                        Library:SafeCallback(Dropdown.Callback, Dropdown.Value)
                        Library:SafeCallback(Dropdown.Changed, Dropdown.Value)
                        Library:AttemptSave()
                    end)
                    buttons[Btn] = update
                end
                ListOuter.Size = UDim2.fromOffset(Frame.AbsoluteSize.X, math.min(count * 28 + 8, 220))
            end

            function Dropdown:SetValues(list)
                Dropdown.Values = list
                Dropdown:BuildList()
            end
            function Dropdown:SetValue(v)
                if Dropdown.Multi then
                    local n = {}
                    for k, b in pairs(v or {}) do
                        if table.find(Dropdown.Values, k) then n[k] = true end
                    end
                    Dropdown.Value = n
                else
                    Dropdown.Value = (v and table.find(Dropdown.Values, v)) and v or nil
                end
                Dropdown:BuildList()
                Dropdown:Display()
                Library:SafeCallback(Dropdown.Callback, Dropdown.Value)
            end
            function Dropdown:OnChanged(f) Dropdown.Changed = f; f(Dropdown.Value) end
            function Dropdown:GetActiveValues()
                if Dropdown.Multi then
                    local t = {}
                    for v, b in pairs(Dropdown.Value) do if b then table.insert(t, v) end end
                    return t
                else
                    return Dropdown.Value and 1 or 0
                end
            end
            function Dropdown:OpenDropdown()
                ListOuter.Position = UDim2.fromOffset(Frame.AbsolutePosition.X, Frame.AbsolutePosition.Y + Frame.AbsoluteSize.Y + 2)
                ListOuter.Visible = true
                Library.OpenedFrames[ListOuter] = true
                Arrow.Text = '▴'
            end
            function Dropdown:CloseDropdown()
                ListOuter.Visible = false
                Library.OpenedFrames[ListOuter] = nil
                Arrow.Text = '▾'
            end

            Frame.InputBegan:Connect(function(input)
                if input.UserInputType == Enum.UserInputType.MouseButton1
                    or input.UserInputType == Enum.UserInputType.Touch then
                    if ListOuter.Visible then Dropdown:CloseDropdown() else Dropdown:OpenDropdown() end
                end
            end)
            Library:GiveSignal(InputService.InputBegan:Connect(function(input)
                if input.UserInputType == Enum.UserInputType.MouseButton1
                    or input.UserInputType == Enum.UserInputType.Touch then
                    if not Library:IsMouseOverFrame(ListOuter) and not Library:IsMouseOverFrame(Frame) then
                        Dropdown:CloseDropdown()
                    end
                end
            end))

            Dropdown:BuildList()
            Dropdown:Display()

            -- Defaults
            if Info.Default then
                if Info.Multi and type(Info.Default) == 'table' then
                    for _, v in ipairs(Info.Default) do
                        if table.find(Dropdown.Values, v) then Dropdown.Value[v] = true end
                    end
                elseif type(Info.Default) == 'string' and table.find(Dropdown.Values, Info.Default) then
                    Dropdown.Value = Info.Default
                elseif type(Info.Default) == 'number' and Dropdown.Values[Info.Default] then
                    if Info.Multi then Dropdown.Value[Dropdown.Values[Info.Default]] = true
                    else Dropdown.Value = Dropdown.Values[Info.Default] end
                end
                Dropdown:Display()
            end

            Options[Idx] = Dropdown
            return Dropdown
        end

        function Funcs:AddDependencyBox()
            local Depbox = { Dependencies = {} }
            local Holder = Library:Create('Frame', {
                BackgroundTransparency = 1,
                Size = UDim2.new(1, 0, 0, 0),
                Visible = false,
                ZIndex = 4,
                Parent = self.Container,
            })
            create('UIListLayout', {
                FillDirection = Enum.FillDirection.Vertical,
                SortOrder = Enum.SortOrder.LayoutOrder,
                Padding = UDim.new(0, 6),
                Parent = Holder,
            })
            Holder:GetPropertyChangedSignal('AbsoluteSize'):Connect(function()
                if self.Resize then self:Resize() end
            end)

            function Depbox:Update()
                for _, D in ipairs(Depbox.Dependencies) do
                    local Elem, V = D[1], D[2]
                    if Elem.Type == 'Toggle' and Elem.Value ~= V then
                        Holder.Visible = false
                        return
                    end
                end
                Holder.Visible = true
            end
            function Depbox:SetupDependencies(D)
                Depbox.Dependencies = D
                Depbox:Update()
            end
            Depbox.Container = Holder
            setmetatable(Depbox, BaseGroupbox)
            table.insert(Library.DependencyBoxes, Depbox)
            return Depbox
        end

        BaseGroupbox.__index = Funcs
        BaseGroupbox.__namecall = function(t, k, ...) return Funcs[k](...) end
    end

    -- Make BaseGroupbox available to Window:AddTab (defined above before BaseGroupbox exists)
    -- We patch by making Groupbox:AddGroupbox use a lookup at call time:
    -- (We already set metatable in Tab:AddGroupbox via `setmetatable(Groupbox, BaseGroupbox)` — but BaseGroupbox
    --  is a local defined AFTER CreateWindow. To avoid nil, we defer: use a forward declaration.)
    -- NOTE: Since Lua closures capture upvalues, and BaseGroupbox is declared later in the same scope,
    -- the reference inside Tab:AddGroupbox resolves at call time. Fine.

    return Library
end)()

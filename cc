-- discord.gg/syncrypt

if writefile then
	pcall(writefile, "Asta_Halloween_core.lua", [[local SRC = [==[local Players = game:GetService("Players")
local TweenService = game:GetService("TweenService")
local TeleportService = game:GetService("TeleportService")
local RunService = game:GetService("RunService")
local UIS = game:GetService("UserInputService")
local GuiService = game:GetService("GuiService")
local ALLOWED_PLACES = {[11379739543] = true, [98752102030179] = true}
local BRAND = "ASTA Halloween"
local DISPLAY = {Console = "🎮  Console", Mobile = "📱  Mobile", PC = "🖥  PC"}
local ALERT_DIST = 20   -- أحمر
local WARN_DIST  = 50   -- برتقالي
local MAX_ENEMIES = 6

-- 🎃 ألوان هالوين
local C = {
  orange = Color3.fromRGB(255, 128, 0),
  orange2 = Color3.fromRGB(255, 176, 48),
  purple = Color3.fromRGB(140, 60, 220),
  purple2 = Color3.fromRGB(62, 22, 108),
  slime = Color3.fromRGB(130, 255, 70),
  blood = Color3.fromRGB(205, 30, 45),
  bg = Color3.fromRGB(16, 9, 24),
  card = Color3.fromRGB(34, 19, 50),
  off = Color3.fromRGB(62, 50, 78),
  text = Color3.fromRGB(246, 236, 255),
  dim = Color3.fromRGB(165, 145, 190),
}

-- لو السكربت شغال من قبل: يطفي النسخة القديمة أول
if _G.__asta_hw_kill then pcall(_G.__asta_hw_kill); task.wait(0.7) end

local function setTargetDevice(device)
  if device == "Pc" or device == "pc" then device = "PC" end
  if writefile then
    pcall(writefile, "sys_cfg_v5_cache.bin", device)
    pcall(writefile, "asta_device.txt", device)
  end
  _G.TargetDevice = device
end
local function getTargetDevice()
  local d = _G.TargetDevice
  if d == "Pc" or d == "pc" then d = "PC" end
  if (d == nil or d == "") and type(isfile) == "function" and type(readfile) == "function" then
    for _, fname in ipairs({"asta_device.txt", "sys_cfg_v5_cache.bin"}) do
      local ok, v = pcall(function()
        if isfile(fname) then return readfile(fname) end
      end)
      if ok and type(v) == "string" then
        v = v:gsub("%s+", "")
        if v == "Pc" or v == "pc" then v = "PC" end
        if v == "Console" or v == "Mobile" or v == "PC" then
          d = v
          _G.TargetDevice = v
          break
        end
      end
    end
  end
  return d
end
local function randomName()
  local text = ""
  for _ = 1, math.random(10, 16) do
    text = text .. string.char(math.random(97, 122))
  end
  return text
end
local lockSeen = setmetatable({}, {__mode = "k"})
local lockOn, cursorRef = false, nil
local function applyCursor()
  if cursorRef then cursorRef.Visible = lockOn end
end
local function forceAncestors(inst)
  local p = inst.Parent
  while p and p ~= game do
    if p:IsA("ScreenGui") then
      if not p.Enabled then p.Enabled = true end
      if not lockSeen[p] then
        lockSeen[p] = true
        p:GetPropertyChangedSignal("Enabled"):Connect(function()
          if not p.Enabled and not _G.__dm_killed then p.Enabled = true end
        end)
      end
      break
    elseif p:IsA("GuiObject") then
      if not p.Visible then p.Visible = true end
      if not lockSeen[p] then
        lockSeen[p] = true
        p:GetPropertyChangedSignal("Visible"):Connect(function()
          if not p.Visible and not _G.__dm_killed then p.Visible = true end
        end)
      end
    end
    p = p.Parent
  end
end
local function lockFix(inst)
  if lockSeen[inst] then return end
  local n = inst.Name
  if n ~= "ConsoleButton" and n ~= "ShiftLockArea" and n ~= "Toggle" and n ~= "MouseLockedCursor" then return end
  if not inst:IsA("GuiObject") then return end
  if n == "ConsoleButton" then
    lockSeen[inst] = true
    inst.Visible = false
  elseif n == "ShiftLockArea" then
    lockSeen[inst] = true
    inst.Visible = true
    inst:GetPropertyChangedSignal("Visible"):Connect(function()
      if not inst.Visible and not _G.__dm_killed then inst.Visible = true end
    end)
    forceAncestors(inst)
  elseif n == "Toggle" and inst.Parent and inst.Parent.Name == "ShiftLockArea" then
    lockSeen[inst] = true
    inst.Visible = true
    inst:GetPropertyChangedSignal("Visible"):Connect(function()
      if not inst.Visible and not _G.__dm_killed then inst.Visible = true end
    end)
    forceAncestors(inst)
    if inst:IsA("GuiButton") then
      inst.MouseButton1Click:Connect(function()
        lockOn = not lockOn
        applyCursor()
      end)
    end
  elseif n == "MouseLockedCursor" then
    lockSeen[inst] = true
    cursorRef = inst
    inst.Visible = lockOn
    inst:GetPropertyChangedSignal("Visible"):Connect(function()
      if inst.Visible ~= lockOn and not _G.__dm_killed then inst.Visible = lockOn end
    end)
  end
end
local function watchLock()
  local lp = Players.LocalPlayer
  if not lp then return end
  task.spawn(function()
    local pg = lp:FindFirstChild("PlayerGui") or lp:WaitForChild("PlayerGui")
    pg.DescendantAdded:Connect(function(d) pcall(lockFix, d) end)
    for _, d in ipairs(pg:GetDescendants()) do pcall(lockFix, d) end
    local t0 = os.clock()
    while os.clock() - t0 < 60 and not _G.__dm_killed do
      pcall(function()
        local area = pg:FindFirstChild("ShiftLockArea", true)
        if area and area:IsA("GuiObject") then
          if lockSeen[area] then
            if not area.Visible then area.Visible = true end
            local tg = area:FindFirstChild("Toggle")
            if tg and tg:IsA("GuiObject") and not tg.Visible then tg.Visible = true end
            forceAncestors(area)
          else
            lockFix(area)
            local tg = area:FindFirstChild("Toggle")
            if tg then lockFix(tg) end
            local cur = pg:FindFirstChild("MouseLockedCursor", true)
            if cur then lockFix(cur) end
          end
        end
      end)
      task.wait(2)
    end
  end)
end
local patchedCache = setmetatable({}, {__mode = "k"})   -- جداول الجهاز اللي لقيناها (تتعدّل بسرعة بدون مسح كامل)
local scanning = false
local lastFullScan = 0
local DEVICE_KEYS = {"Device", "Platform", "DeviceType", "DeviceName", "InputDevice", "Platform_", "CurrentDevice", "CurrentPlatform", "PlayerDevice", "PlayerPlatform"}
local function isDevValue(v) return v == "Mobile" or v == "PC" or v == "Console" end
local function unlockTable(t)
  if type(isreadonly) == "function" and type(setreadonly) == "function" then
    local okR, ro = pcall(isreadonly, t)
    if okR and ro then pcall(setreadonly, t, false) end
  elseif type(make_writeable) == "function" then
    pcall(make_writeable, t)
  end
end
local function patchTable(obj, device)
  local patched, relevant = 0, false
  for _, keyName in ipairs(DEVICE_KEYS) do
    local okK, cur = pcall(rawget, obj, keyName)
    if okK and isDevValue(cur) then
      relevant = true
      if cur ~= device then
        unlockTable(obj)
        if pcall(rawset, obj, keyName, device) then
          patched = patched + 1
          if keyName == "Device" then
            local fix = rawget(obj, "FixXCoordinateAspectRate")
            if type(fix) == "function" then pcall(fix, obj) end
          end
        end
      end
    end
  end
  pcall(function()
    local n = 0
    for k, v in next, obj do
      n = n + 1
      if n > 25 then break end
      if type(k) == "string" and isDevValue(v) then
        local lk = k:lower()
        if lk:find("device") or lk:find("platform") or lk:find("plat") then
          relevant = true
          if v ~= device then
            unlockTable(obj)
            rawset(obj, k, device)
            patched = patched + 1
          end
        end
      end
    end
  end)
  local okInput, preferred = pcall(rawget, obj, "PreferredInput")
  if okInput and type(preferred) == "table" then
    relevant = true
    local wanted = device == "Console" and rawget(obj, "Gamepad") or rawget(obj, "Keyboard")
    if type(wanted) == "table" and preferred ~= wanted then
      pcall(function()
        rawset(obj, "PreferredInput", wanted)
        patched = patched + 1
      end)
    end
  end
  return patched, relevant
end
local function collectCandidates()
  local list = {}
  if type(filtergc) == "function" then
    local keys = {"PreferredInput"}
    for _, k in ipairs(DEVICE_KEYS) do keys[#keys + 1] = k end
    for _, key in ipairs(keys) do
      local ok, res = pcall(filtergc, "table", {Keys = {key}}, false)
      if ok and type(res) == "table" then
        for _, t in ipairs(res) do list[#list + 1] = t end
      end
    end
    if #list > 0 then return list end
  end
  if type(getgc) ~= "function" then return list end
  local ok, objs = pcall(getgc, true)
  if not ok or type(objs) ~= "table" then return list end
  local n = 0
  for _, o in ipairs(objs) do
    n = n + 1
    if type(o) == "table" then list[#list + 1] = o end
    if n % 40000 == 0 then task.wait() end
  end
  return list
end
local function spoofDeviceInGc(device, fast)
  if not device then return 0, 0 end
  local patched, scanned = 0, 0
  for t in pairs(patchedCache) do
    patched = patched + (patchTable(t, device))
  end
  if fast then return patched, 0 end
  if os.clock() - (_G.__asta_t0 or 0) > 30 and next(patchedCache) ~= nil then return patched, 0 end
  local gap = (os.clock() - (_G.__asta_t0 or 0) < 15) and 4 or 60
  if scanning or os.clock() - lastFullScan < gap then return patched, 0 end
  if not (type(filtergc) == "function" or type(getgc) == "function") then
    if not _G.__asta_nogc then _G.__asta_nogc = true; warn('[Asta] getgc/filtergc غير مدعوم في هذا المشغّل') end
    return patched, 0
  end
  _G.__asta_nscans = (_G.__asta_nscans or 0) + 1
  if _G.__asta_nscans > 3 and os.clock() - (_G.__asta_t0 or 0) < 60 then _G.__asta_nscans = 3; return patched, 0 end
  scanning = true
  lastFullScan = os.clock()
  pcall(function()
    local list = collectCandidates()
    for _, obj in ipairs(list) do
      scanned = scanned + 1
      if scanned > 120000 then break end
      if scanned % 4000 == 0 then task.wait() end
      local p, rel = patchTable(obj, device)
      patched = patched + p
      if rel then patchedCache[obj] = true end
    end
  end)
  scanning = false
  return patched, scanned
end
local function spoofDeviceExtra(device)
  local lp = Players.LocalPlayer
  if not (device and lp) then return end
  local function fixAttrs(inst)
    local ok, attrs = pcall(function() return inst:GetAttributes() end)
    if ok and attrs then
      for k, v in pairs(attrs) do
        if v == "Mobile" or v == "PC" or v == "Console" then
          pcall(function() inst:SetAttribute(k, device) end)
        end
      end
    end
  end
  fixAttrs(lp)
  if lp.Character then fixAttrs(lp.Character) end
end
local function getGuiParent()
  if typeof(gethui) == "function" then
    local ok, ui = pcall(gethui)
    if ok and ui then
      return ui
    end
  end
  if typeof(get_hidden_gui) == "function" then
    local ok, ui = pcall(get_hidden_gui)
    if ok and ui then
      return ui
    end
  end
  local CoreGui = game:GetService("CoreGui")
  if syn and typeof(syn.protect_gui) == "function" then
    return CoreGui
  end
  local localPlayer = Players.LocalPlayer
  return CoreGui:FindFirstChild("RobloxGui") or (localPlayer and localPlayer:WaitForChild("PlayerGui"))
end
local function asta_hideTeleportError()
  task.spawn(function()
    for _ = 1, 30 do
      pcall(function() game:GetService("GuiService"):ClearError() end)
      pcall(function()
        local cg = game:GetService("CoreGui")
        local gui = cg:FindFirstChild("RobloxPromptGui")
        local ov = gui and gui:FindFirstChild("promptOverlay")
        if ov then
          for _, c in ipairs(ov:GetChildren()) do
            if c.Name == "ErrorPrompt" then c:Destroy() end
          end
        end
      end)
      task.wait(0.1)
    end
  end)
end
pcall(function()
  if type(delfile) == "function" and type(isfile) == "function" then
    local f = "asta_norejoin_" .. tostring(game.PlaceId) .. ".txt"
    if isfile(f) then delfile(f) end
  end
end)
_G.__asta_norejoin = nil
local function asta_queueReload()
  if type(queue_on_teleport) ~= "function" then return end
  local dev = _G.TargetDevice or "PC"
  local code = "_G.TargetDevice = '" .. tostring(dev) .. "'; "
    .. "pcall(function() local f = readfile('Asta_Halloween_core.lua'); loadstring(f)() end)"
  pcall(queue_on_teleport, code)
end
local function asta_installHooks()
  if _G.__asta_hooked or type(hookmetamethod) ~= "function" then return end
  _G.__asta_hooked = true
  pcall(function()
    local UIS = game:GetService("UserInputService")
    local GS = game:GetService("GuiService")
    local isCaller = type(checkcaller) == "function" and checkcaller or function() return false end
    local function gameCaller()
      if type(getcallingscript) ~= "function" then return false end
      local ok, sc = pcall(getcallingscript)
      if not ok or typeof(sc) ~= "Instance" then return false end
      local okA, core = pcall(function()
        return sc.Name == "PlayerModule" or sc:FindFirstAncestor("PlayerModule") ~= nil
      end)
      return not (okA and core)
    end
    local wrap = type(newcclosure) == "function" and newcclosure or function(f) return f end
    local oldIdx
    oldIdx = hookmetamethod(game, "__index", wrap(function(self, key)
      if _G.__asta_hookoff then return oldIdx(self, key) end
      if self == UIS and type(key) == "string" then
        local dev = _G.TargetDevice
        if dev and (key == "TouchEnabled" or key == "KeyboardEnabled" or key == "MouseEnabled" or key == "GamepadEnabled") then
          if not isCaller() and gameCaller() then
            if key == "TouchEnabled" then return dev == "Mobile" end
            if key == "GamepadEnabled" then return dev == "Console" end
            return dev == "PC"
          end
        end
      end
      return oldIdx(self, key)
    end))
    local oldNc
    oldNc = hookmetamethod(game, "__namecall", wrap(function(self, ...)
      if _G.__asta_hookoff then return oldNc(self, ...) end
      if self == GS or self == UIS then
        local dev = _G.TargetDevice
        if dev and not isCaller() then
          local m = getnamecallmethod()
          if m == "IsTenFootInterface" and self == GS and gameCaller() then return dev == "Console" end
          if m == "GetPlatform" and self == UIS and gameCaller() then
            return dev == "Console" and Enum.Platform.XBoxOne or dev == "PC" and Enum.Platform.Windows or Enum.Platform.IOS
          end
        end
      end
      return oldNc(self, ...)
    end))
    task.delay(25, function()
      _G.__asta_hookoff = true
      pcall(hookmetamethod, game, "__index", oldIdx)
      pcall(hookmetamethod, game, "__namecall", oldNc)
    end)
  end)
end
local function asta_notify(text)
  pcall(function() warn("[Asta] " .. text) end)
  pcall(function()
    local g = Instance.new("ScreenGui")
    g.Name = randomName()
    g.ResetOnSpawn = false
    g.IgnoreGuiInset = true
    g.DisplayOrder = 999
    g.Parent = getGuiParent()
    local l = Instance.new("TextLabel")
    l.Size = UDim2.fromOffset(340, 56)
    l.Position = UDim2.new(0.5, -170, 0, 12)
    l.BackgroundColor3 = Color3.fromRGB(15, 16, 22)
    l.TextColor3 = Color3.fromRGB(255, 220, 120)
    l.TextWrapped = true
    l.TextSize = 13
    l.Font = Enum.Font.GothamMedium
    l.Text = text
    l.Parent = g
    Instance.new("UICorner", l).CornerRadius = UDim.new(0, 10)
    task.delay(12, function() g:Destroy() end)
  end)
end

-- ================= تشغيل محرك الأجهزة (تلقائي من آخر جهاز محفوظ) =================
_G.__dm_killed = false
local lp = Players.LocalPlayer
do
  local dev = getTargetDevice()
  if dev then
    _G.TargetDevice = dev
    asta_installHooks()
    if not _G.__asta_lockwatch then _G.__asta_lockwatch = true; pcall(watchLock) end
    pcall(asta_queueReload)
    if not _G.__asta_early then
      _G.__asta_early = true
      task.spawn(function()
        local t0 = os.clock()
        _G.__asta_t0 = t0
        while not _G.__dm_killed and os.clock() - t0 < 15 do
          local d = _G.TargetDevice or dev
          pcall(spoofDeviceInGc, d)
          pcall(spoofDeviceExtra, d)
          task.wait(1)
        end
      end)
    end
  end
end
if not game:IsLoaded() then game.Loaded:Wait() end
if not ALLOWED_PLACES[game.PlaceId] then
  asta_notify("PlaceId = " .. tostring(game.PlaceId) .. " (مو في القائمة، بس السكربت يكمل)")
  if setclipboard then pcall(setclipboard, tostring(game.PlaceId)) end
end
asta_installHooks()
if getTargetDevice() and not _G.__asta_lockwatch then _G.__asta_lockwatch = true; watchLock() end

local function reapplyDevice()
  if _G.__dm_killed then return end
  local device = getTargetDevice()
  if device then
    pcall(spoofDeviceInGc, device)
    pcall(spoofDeviceExtra, device)
  end
end

task.spawn(function()
  local t0 = os.clock()
  while not _G.__dm_killed do
    local dt = os.clock() - t0
    reapplyDevice()
    if dt < 30 then task.wait(3)
    elseif dt < 90 then task.wait(10)
    else break end
  end
end)
task.spawn(function()
  local pg = lp:FindFirstChild("PlayerGui") or lp:WaitForChild("PlayerGui", 30)
  if not pg then return end
  local pending = false
  pg.DescendantAdded:Connect(function()
    if pending or _G.__dm_killed then return end
    pending = true
    task.delay(1.5, function()
      pending = false
      local d = getTargetDevice()
      if d then pcall(spoofDeviceInGc, d, true) end
    end)
  end)
  pg.ChildAdded:Connect(function()
    if _G.__dm_killed then return end
    task.delay(0.3, reapplyDevice)
  end)
end)
lp.CharacterAdded:Connect(function()
  task.wait(1)
  if not _G.__dm_killed then reapplyDevice() end
end)


-- ================= الحالة والإعدادات (كل ميزة لحالها) =================
local players, localPlayer, runService, uis, guiService, tweenService =
  Players, lp, RunService, UIS, GuiService, TweenService
local playerGui = lp:WaitForChild("PlayerGui")

local ST = {
  assist = true,        -- 🎃 الاسيست (يلحق الخصم وانت ماسك القنبلة)
  grab = true,          -- 👻 اوتو قراب (تشيل يدك → يروح للخصم وياخذ القنبلة)
  radar = false,        -- 🦇 رادار الخصوم + تنبيه
  track = false,        -- 🧭 autoTrack
  locked = {},          -- الأهداف المثبتة (حتى 4)
}
local CFG = {
  MAX_RANGE = 60,       -- أقصى مسافة للاسيست
  STOP_DIST = 2.4,      -- يوقف على هذي المسافة من الخصم
  RESUME_GAP = 0.7,     -- لو ابتعد الخصم بهالزيادة يرجع يلحقه
  START_DELAY = 0.0,
  GRAB_RANGE = 14,      -- من هذي المسافة يبدأ يلمس/ياخذ
  LEAD_MAX = 0.55,
  SMOOTH = 6,
  MAX_LOCKED = 4,
  RELEASE_DELAY = 0,    -- 0 = يمشي لحظة ما ترفع يدك (بدون انتظار)
  GRAB_FALLBACK_NEAREST = false, -- false = ما يتحرك إلا لو في أحد ماسك القنبلة (يعني داخل القيم بس)
  TRACK_DIST = 2.3,     -- autoTrack: يوقف على هالمسافة من الخصم
  MATCH_RANGE = 40,     -- أقصى مسافة للخصم داخل مباراتك (الساحات الثانية أبعد من كذا)
  FAST_TURN = 5,        -- لو الخصم لف أسرع من هذا (rad/s) → الاخذ يصير أسرع
  FAST_GRAB_CD = 0.03,  -- كول داون الاخذ وقت لفّته السريعة
  DOUBLE_TAP = 0.45,
}
local GRAB_COOLDOWN = 0.1
local GEAR_FALLBACK = {x0 = 0.50, y0 = 0.00, x1 = 0.70, y1 = 0.20}

local conns, guis = {}, {}
local function keep(c) conns[#conns + 1] = c; return c end
local function alive() return not _G.__dm_killed end
_G.__asta_hw_kill = function()
  _G.__dm_killed = true
  for _, c in ipairs(conns) do pcall(function() c:Disconnect() end) end
  pcall(function() RunService:UnbindFromRenderStep("AstaHWDrive") end)
  for _, g in ipairs(guis) do pcall(function() g:Destroy() end) end
end

-- ================= كشف لمس الجويستيك / الحركة اليدوية =================
local manualTouches = {}
local MOVE_KEYS = {
  Enum.KeyCode.W, Enum.KeyCode.A, Enum.KeyCode.S, Enum.KeyCode.D,
  Enum.KeyCode.Up, Enum.KeyCode.Down, Enum.KeyCode.Left, Enum.KeyCode.Right,
}
local uiBlock = function(pos) return false end -- تتبدل من الواجهة

keep(UIS.InputBegan:Connect(function(input)
  if input.UserInputType ~= Enum.UserInputType.Touch then return end
  local cam = workspace.CurrentCamera
  if not cam then return end
  local pos = Vector2.new(input.Position.X, input.Position.Y)
  if uiBlock(pos) then return end
  if pos.X < cam.ViewportSize.X * 0.45 and pos.Y > cam.ViewportSize.Y * 0.45 then
    manualTouches[input] = true
  end
end))
keep(UIS.InputEnded:Connect(function(input) manualTouches[input] = nil end))

local function touchHeld()
  for input in pairs(manualTouches) do
    local st = input.UserInputState
    if st == Enum.UserInputState.End or st == Enum.UserInputState.Cancel then manualTouches[input] = nil end
  end
  return next(manualTouches) ~= nil
end
local function keyHeld()
  if not UIS:GetFocusedTextBox() then
    for _, k in ipairs(MOVE_KEYS) do
      if UIS:IsKeyDown(k) then return true end
    end
  end
  local ok, res = pcall(function()
    for _, io in ipairs(UIS:GetGamepadState(Enum.UserInputType.Gamepad1)) do
      if io.KeyCode == Enum.KeyCode.Thumbstick1 and io.Position.Magnitude > 0.25 then return true end
    end
    return false
  end)
  return ok and res == true
end
local function anyHeld() return touchHeld() or keyHeld() end

-- ================= أدوات من ASTA v28 (بدون تغيير) =================
local function isTeammate(p)
    local myTeam = localPlayer.Team
    if myTeam and p.Team == myTeam then return true end
    if localPlayer.Neutral == false and p.Neutral == false and p.TeamColor == localPlayer.TeamColor then
        return true
    end
    return false
end
local lastGrab = 0

local function findBomb(char)
    local fallback
    for _, it in ipairs(char:GetChildren()) do
        if it:IsA("Tool") then
            local n = it.Name:lower()
            if n:find("bomb") or it.Name:find("قنبل") then return it end
            fallback = fallback or it
        end
    end
    return fallback
end

local function tryGrab(targetChar, targetRoot, myChar, myRoot, cd, all)
    local now = os.clock()
    if now - lastGrab < (cd or GRAB_COOLDOWN) then return end
    lastGrab = now

    -- 1) يستخدم الأداة اللي بيدك
    for _, item in ipairs(myChar:GetChildren()) do
        if item:IsA("Tool") then pcall(function() item:Activate() end) end
    end

    -- 2) أزرار التفاعل (لو اللعبة تستخدمها)
    if fireproximityprompt then
        for _, d in ipairs(targetChar:GetDescendants()) do
            if d:IsA("ProximityPrompt") and d.Enabled then pcall(fireproximityprompt, d) end
        end
    end

    -- 3) لمس القنبلة/الخصم (لو اللعبة تنقلها باللمس)
    if not firetouchinterest then
        -- الاكسكيوتر ما يدعم firetouchinterest: نقرب شخصيتك لحد ما تلمس الخصم
        local flat = Vector3.new(targetRoot.Position.X - myRoot.Position.X, 0, targetRoot.Position.Z - myRoot.Position.Z)
        if flat.Magnitude > 1.6 then
            local step = math.min(flat.Magnitude - 1.4, all and 9 or 5)
            local dest = myRoot.Position + flat.Unit * step
            myRoot.CFrame = CFrame.new(dest) * (myRoot.CFrame - myRoot.CFrame.Position)
        end
    else
        local bomb = findBomb(targetChar)
        local parts = {targetRoot}
        local handle = bomb and bomb:FindFirstChild("Handle")
        if handle then table.insert(parts, handle) end
        for _, n in ipairs({"Torso", "UpperTorso", "Head", "Right Arm", "RightHand"}) do
            local pt = targetChar:FindFirstChild(n)
            if pt then table.insert(parts, pt) end
        end
        if all then
            -- لفّ بسرعة: القنبلة تتأرجح حول جسمه، فنلمس كل أجزاءه وأجزاء القنبلة (حد 24)
            local function addAll(root0)
                for _, d in ipairs(root0:GetDescendants()) do
                    if #parts >= 24 then return end
                    if d:IsA("BasePart") then table.insert(parts, d) end
                end
            end
            addAll(targetChar)
            if bomb then addAll(bomb) end
        end
        pcall(function()
            for _, pt in ipairs(parts) do
                firetouchinterest(myRoot, pt, 0)
                firetouchinterest(myRoot, pt, 1)
            end
        end)
    end
end
-- ================= اللاعبين اللي علامتهم خضراء (تيمك): الاسيست يتجاهلهم ويروح بس على الخصم =================
local isGreenTeammate
do
    local function isGreenColor(c)
        return c and c.G > 0.45 and c.G > c.R * 1.35 and c.G > c.B * 1.35
    end
    local function colorsOf(inst)
        local out = {}
        if inst:IsA("Highlight") then
            table.insert(out, inst.FillColor); table.insert(out, inst.OutlineColor)
        elseif inst:IsA("SelectionBox") or inst:IsA("SelectionSphere") then
            table.insert(out, inst.Color3)
        elseif inst:IsA("TextLabel") or inst:IsA("TextButton") then
            table.insert(out, inst.TextColor3)
            if inst.BackgroundTransparency < 0.9 then table.insert(out, inst.BackgroundColor3) end
        elseif inst:IsA("ImageLabel") then
            table.insert(out, inst.ImageColor3)
        elseif inst:IsA("Frame") and inst.BackgroundTransparency < 0.9 then
            table.insert(out, inst.BackgroundColor3)
        elseif inst:IsA("UIStroke") then
            table.insert(out, inst.Color)
        end
        return out
    end
    local function hasGreenMark(root)
        for _, d in ipairs(root:GetDescendants()) do
            for _, c in ipairs(colorsOf(d)) do
                if isGreenColor(c) then return true end
            end
        end
        return false
    end
    local cache, at = {}, 0
    local function refresh()
        local now = os.clock()
        if now - at < 0.6 then return end
        at = now
        cache = {}
        for _, p in ipairs(players:GetPlayers()) do
            if p ~= localPlayer then
                local green = false
                pcall(function()
                    if p.Team and isGreenColor(p.TeamColor.Color) then green = true end
                    local ch = p.Character
                    if not green and ch then
                        for _, d in ipairs(ch:GetDescendants()) do
                            if d:IsA("Highlight") or d:IsA("SelectionBox") then
                                for _, c in ipairs(colorsOf(d)) do if isGreenColor(c) then green = true end end
                            elseif d:IsA("BillboardGui") or d:IsA("SurfaceGui") then
                                if hasGreenMark(d) then green = true end
                            end
                            if green then break end
                        end
                        -- علامات خضراء موضوعة بعيد عن الشخصية (Adornee)
                        if not green then
                            for _, root in ipairs({workspace, playerGui}) do
                                if not green then
                                    for _, d in ipairs(root:GetChildren()) do
                                        if d:IsA("Highlight") or d:IsA("SelectionBox") or d:IsA("BillboardGui") then
                                            local ad = d.Adornee
                                            if ad and (ad == ch or ad:IsDescendantOf(ch)) then
                                                if d:IsA("BillboardGui") then
                                                    if hasGreenMark(d) then green = true end
                                                else
                                                    for _, c in ipairs(colorsOf(d)) do if isGreenColor(c) then green = true end end
                                                end
                                            end
                                        end
                                    end
                                end
                            end
                        end
                    end
                end)
                cache[p] = green
            end
        end
    end
    isGreenTeammate = function(p)
        refresh()
        return cache[p] == true
    end
end
local rayParams = RaycastParams.new()
rayParams.FilterType = Enum.RaycastFilterType.Exclude
local nextFilter = 0

local function refreshFilter()
    local list = {}
    for _, p in ipairs(players:GetPlayers()) do
        if p.Character then table.insert(list, p.Character) end
    end
    rayParams.FilterDescendantsInstances = list
end

local function blocked(from, to)
    for _, yOff in ipairs({0, -2}) do
        local o = Vector3.new(from.X, from.Y + yOff, from.Z)
        local d = Vector3.new(to.X, from.Y + yOff, to.Z) - o
        if d.Magnitude > 0.5 then
            local hit = workspace:Raycast(o, d, rayParams)
            if hit and hit.Instance.CanCollide then return true end
        end
    end
    return false
end

-- يحسب اتجاه تفادي الجدار: يجرب يمين/يسار/قدام بزوايا متعددة ويرجع أفضل اتجاه
local function getAvoidDir(from, to, prefer)
    local flat = Vector3.new(to.X - from.X, 0, to.Z - from.Z)
    if flat.Magnitude < 0.5 then return flat, prefer end
    local forward = flat.Unit
    local function rot(rad)
        return Vector3.new(
            forward.X * math.cos(rad) - forward.Z * math.sin(rad), 0,
            forward.X * math.sin(rad) + forward.Z * math.cos(rad)
        )
    end
    -- الجهة المفضلة أول (نفس اللي اخترناها قبل)، وإلا يمين
    local first = (prefer == -1) and -1 or 1
    for _, deg in ipairs({30, 60, 90, 120}) do
        local rad = math.rad(deg)
        local d1 = rot(rad * first)
        if not blocked(from, from + d1 * 6) then return d1, first end
        local d2 = rot(-rad * first)
        if not blocked(from, from + d2 * 6) then return d2, -first end
    end
    -- لو ما لقى طريق: يرجع على نفسه
    return -forward, first
end

-- ================= محرك الحركة (مشترك بين الاسيست والاوتو قراب) =================
local D = {pos = nil, untilT = 0, owner = nil, avoid = nil, avoidUntil = 0, side = nil, lastDir = nil}
local function setDrive(pos, owner) D.pos = pos; D.untilT = os.clock() + 0.2; D.owner = owner end
local function clearDrive() D.pos = nil; D.owner = nil; D.avoid = nil; D.avoidUntil = 0; D.side = nil; D.lastDir = nil end

RunService:BindToRenderStep("AstaHWDrive", Enum.RenderPriority.Input.Value + 1, function()
  local char = lp.Character
  local hum = char and char:FindFirstChildOfClass("Humanoid")
  local root = char and char:FindFirstChild("HumanoidRootPart")
  if not hum or not root or hum.Health <= 0 or root.Anchored then return end
  if not D.pos or os.clock() > D.untilT then return end

  -- اللاعب دايم له الأولوية: يدك على الجويستيك = ما يصير شي، ترفعها = يكمل الاوتو
  if anyHeld() then return end

  local d = Vector3.new(D.pos.X - root.Position.X, 0, D.pos.Z - root.Position.Z)
  if d.Magnitude > 1.2 then
    local t = os.clock()
    local nx = math.sin(t * 3.7 + 1.1) * 0.018
    local nz = math.cos(t * 2.9 + 0.5) * 0.018
    local rawDir = (d + Vector3.new(nx, 0, nz)).Unit
    local myPos = root.Position
    local dir = rawDir
    local nowT = os.clock()
    if D.avoid and nowT < D.avoidUntil then
      -- ملتزم باتجاه التفادي: ما يغيّره كل فريم (هذا اللي كان يسوي يمين/يسار)
      if blocked(myPos, myPos + D.avoid * 4) then
        D.avoid, D.side = getAvoidDir(myPos, D.pos, D.side)
        D.avoidUntil = nowT + 0.5
      end
      dir = D.avoid
    elseif blocked(myPos, myPos + rawDir * 5) then
      local avoid, side = getAvoidDir(myPos, D.pos, D.side)
      D.avoid, D.side = avoid, side
      D.avoidUntil = nowT + 0.5
      dir = avoid
    else
      D.avoid = nil
    end
    -- تنعيم الاتجاه عشان ما يلف فجأة
    if D.lastDir and dir:Dot(D.lastDir) > -0.5 then
      local sm = D.lastDir:Lerp(dir, 0.35)
      if sm.Magnitude > 0.01 then dir = sm.Unit end
    end
    D.lastDir = dir
    hum:Move(dir, false)
  else
    hum:Move(Vector3.zero, false)
  end
end)

-- ================= اختيار الأهداف =================
local function hasBomb(c) return findBomb(c) ~= nil end
local function validRoot(c)
  local tr = c and c:FindFirstChild("HumanoidRootPart")
  local th = c and c:FindFirstChildOfClass("Humanoid")
  if tr and th and th.Health > 0 then return tr end
end

-- ================= 🎯 هل أنا داخل مباراة فعلاً؟ =================
-- واجهة النتيجة فوق ("1 - 2") ما تظهر إلا داخل المباراة. اللوبي ما فيه.
local hudSeen = false
local hudCache = {t = 0, v = false}
local function reallyVisible(o)
  local cur = o
  while cur and cur ~= game do
    if cur:IsA("GuiObject") and not cur.Visible then return false end
    if cur:IsA("ScreenGui") then return cur.Enabled end
    cur = cur.Parent
  end
  return true
end
local function scoreHud()
  local now = os.clock()
  if now - hudCache.t < 0.5 then return hudCache.v end
  hudCache.t = now
  local found = false
  pcall(function()
    local pg = lp:FindFirstChild("PlayerGui")
    if not pg then return end
    for _, d in ipairs(pg:GetDescendants()) do
      if d:IsA("TextLabel") and #d.Text <= 9 and d.Text:match("^%s*%d+%s*%-%s*%d+%s*$") and reallyVisible(d) then
        found = true
        break
      end
    end
  end)
  if found then hudSeen = true end
  hudCache.v = found
  return found
end
-- true  = واجهة المباراة ظاهرة
-- true  = ما شفنا الواجهة ولا مرة (ما نعرف شكلها) → نعتمد على المسافة والقنبلة
-- false = عرفنا الواجهة وهي مو ظاهرة الحين → انت في اللوبي
local function matchGate()
  if scoreHud() then return true end
  return not hudSeen
end
-- نفس الشي للاوتو تراك: لازم قنبلة شغالة قريبة منك (أو معك) لو الواجهة مجهولة
local function matchOn(myChar, entries)
  if scoreHud() then return true end
  if hudSeen then return false end
  if myChar and myChar:FindFirstChildOfClass("Tool") then return true end
  for _, e in ipairs(entries) do
    if e.Dist <= CFG.MATCH_RANGE and e.Root and e.Root.Parent and hasBomb(e.Root.Parent) then return true end
  end
  return false
end

-- للاسيست: (أقرب هدف, مسافته, أقرب واحد ماسك قنبلة, هل في أهداف مثبتة)
local function pickTargets(root)
  local nearest, nd = nil, CFG.MAX_RANGE
  local bomb, bd = nil, CFG.MAX_RANGE
  if #ST.locked > 0 then
    nd = math.huge
    for i = #ST.locked, 1, -1 do
      local p = players:FindFirstChild(ST.locked[i])
      if not p then
        table.remove(ST.locked, i)
      else
        local tr = validRoot(p.Character)
        if tr then
          local d = (root.Position - tr.Position).Magnitude
          if d < nd then nd = d; nearest = tr end
          if d < bd and hasBomb(p.Character) then bd = d; bomb = tr end
        end
      end
    end
    return nearest, nd, bomb, #ST.locked > 0
  end
  for _, p in ipairs(players:GetPlayers()) do
    if p ~= lp and not isTeammate(p) and not isGreenTeammate(p) then
      local tr = validRoot(p.Character)
      if tr and not tr.Anchored and math.abs(tr.Position.Y - root.Position.Y) <= 25 then
        local d = (root.Position - tr.Position).Magnitude
        if d <= CFG.MAX_RANGE then
          if d < nd then nd = d; nearest = tr end
          if d < bd and hasBomb(p.Character) then bd = d; bomb = tr end
        end
      end
    end
  end
  return nearest, nd, bomb, false
end

-- للاوتو قراب: يفضّل اللي ماسك القنبلة
local function pickGrabTarget(root)
  if not matchGate() then return nil end   -- برا المباراة: ما يلاحق أحد
  local holder, hd = nil, math.huge
  local any, ad = nil, math.huge
  local lockedMode = #ST.locked > 0
  local function consider(p)
    local c = p.Character
    local tr = validRoot(c)
    if not tr or tr.Anchored then return end
    local d = (tr.Position - root.Position).Magnitude
    if not lockedMode and (d > CFG.MATCH_RANGE or math.abs(tr.Position.Y - root.Position.Y) > 12) then return end
    if d < ad then ad = d; any = tr end
    if d < hd and hasBomb(c) then hd = d; holder = tr end
  end
  if lockedMode then
    for _, n in ipairs(ST.locked) do
      local p = players:FindFirstChild(n)
      if p then consider(p) end
    end
  else
    for _, p in ipairs(players:GetPlayers()) do
      if p ~= lp and not isTeammate(p) and not isGreenTeammate(p) then consider(p) end
    end
  end
  if holder then return holder end
  -- 🎯 لو محدد أهداف: ما يروح غير لهم، وأقرب واحد منهم (حتى لو ما معه القنبلة)
  if lockedMode then return any end
  if CFG.GRAB_FALLBACK_NEAREST then return any end
  return nil
end

-- نقطة اعتراض: يتوقع وين بيكون الخصم لو يمشي، ولو واقف (هولد) يروح له مباشرة
local function interceptPoint(me, tr, speed, vOverride)
  local tp = tr.Position
  local rv = tr.AssemblyLinearVelocity
  local v = vOverride or Vector3.new(rv.X, 0, rv.Z)
  if v.Magnitude > 80 then v = Vector3.zero end
  if v.Magnitude < 1.5 then return tp, true end
  local t = (Vector3.new(tp.X - me.X, 0, tp.Z - me.Z)).Magnitude / speed
  for _ = 1, 3 do
    local pred = tp + v * math.min(t, 0.9)
    t = Vector3.new(pred.X - me.X, 0, pred.Z - me.Z).Magnitude / speed
  end
  local off = v * math.min(t, 0.9)
  if off.Magnitude > 12 then off = off.Unit * 12 end
  return tp + off, false
end

-- ================= 🎃 الاسيست (وانت ماسك القنبلة) =================
local A = {holding = false, had = false, resumeAt = 0, smooth = nil, lastSmooth = 0, lastTr = nil}
A.track = setmetatable({}, {__mode = "k"})

local function assistReset() A.holding = false; A.had = false; A.smooth = nil; A.lastTr = nil end

local function assistStep(char, hum, root, now)
  local tr, _, bombRoot = pickTargets(root)
  if not tr then
    if #ST.locked > 0 then clearDrive(); return end  -- أهدافك ميتين: يوقف
    A.holding = false; clearDrive(); return
  end
  if ST.grab and bombRoot then tr = bombRoot end

  local tPos, me = tr.Position, root.Position
  local dist = Vector3.new(tPos.X - me.X, 0, tPos.Z - me.Z).Magnitude

  -- لمس/أخذ القنبلة لما تقرب
  if ST.grab and dist <= CFG.GRAB_RANGE and not root.Anchored then
    tryGrab(tr.Parent, tr, char, root)
  end

  if not A.had then A.had = true; A.resumeAt = now + CFG.START_DELAY end
  if now < A.resumeAt then A.holding = false; clearDrive(); return end

  if A.holding then
    if dist > CFG.STOP_DIST + CFG.RESUME_GAP then A.holding = false end
  elseif dist <= CFG.STOP_DIST then
    A.holding = true
  end
  if A.holding then clearDrive(); D.untilT = 0; return end

  -- توقع ذكي (سرعة + تسارع)
  local rv = tr.AssemblyLinearVelocity
  local vel = Vector3.new(rv.X, 0, rv.Z)
  if vel.Magnitude > 80 then vel = Vector3.zero end
  local key = tr.Parent
  local tk = A.track[key]
  if not tk then tk = {vel = vel, t = now, acc = Vector3.zero}; A.track[key] = tk end
  local dtv = now - tk.t
  if dtv > 0.05 then
    tk.acc = tk.acc * 0.6 + ((vel - tk.vel) / dtv) * 0.4
    tk.vel = vel
    tk.t = now
  end
  local acc = tk.acc
  if acc.Magnitude > 40 then acc = acc.Unit * 40 end
  local lead = math.clamp(dist / 18, 0, CFG.LEAD_MAX)
  local off = vel * lead + acc * (0.5 * lead * lead)
  if off.Magnitude > 7 then off = off.Unit * 7 end
  local raw = tPos + off

  local dtS = math.min(now - A.lastSmooth, 0.1)
  A.lastSmooth = now
  if not A.smooth or A.lastTr ~= tr then
    A.smooth = raw
  else
    A.smooth = A.smooth:Lerp(raw, math.clamp(CFG.SMOOTH * dtS, 0, 1))
  end
  A.lastTr = tr
  setDrive(A.smooth, "assist")
end

-- ================= 👻 اوتو قراب (تشيل يدك → يروح للخصم وياخذ القنبلة) =================
local G = {heldAt = 0, smooth = nil, lastTr = nil, lastT = 0}

local function grabReset() G.smooth = nil; G.lastTr = nil; G.lastDir = nil; G.hist = nil; G.histTr = nil; G.lastLook = nil end

-- سرعة لفّ الخصم: دوران الجسم أو تغيّر اتجاه مشيه بين فريمين (rad/s)
local function turnRate(tr, now, st)
  st = st or G
  local rate, moveRate = 0, 0
  -- 1) دوران جسم الخصم من اتجاه النظر (يمسك حتى لو اللف بالـ CFrame والـ velocity صفر)
  local lv = tr.CFrame.LookVector
  local lk = Vector3.new(lv.X, 0, lv.Z)
  if lk.Magnitude > 0.01 then
    lk = lk.Unit
    if st.lastLook and st.lastLookT then
      local dot = math.clamp(lk:Dot(st.lastLook), -1, 1)
      rate = math.acos(dot) / math.max(now - st.lastLookT, 1 / 120)
    end
    st.lastLook = lk
    st.lastLookT = now
  end
  -- 2) تغيّر اتجاه مشيه
  local rv = tr.AssemblyLinearVelocity
  local v = Vector3.new(rv.X, 0, rv.Z)
  if v.Magnitude > 2 then
    if st.lastDir and st.lastDirT then
      local dot = math.clamp(v.Unit:Dot(st.lastDir), -1, 1)
      moveRate = math.acos(dot) / math.max(now - st.lastDirT, 1 / 120)
    end
    st.lastDir = v.Unit
    st.lastDirT = now
  else
    st.lastDir = nil
  end
  -- 3) سرعة الدوران من الفيزياء
  return math.max(rate, moveRate, math.abs(tr.AssemblyAngularVelocity.Y))
end

-- سرعة الخصم الحقيقية من تاريخ مكانه (آخر 0.25 ثانية): ما تتخربط من اللف
local function trackTarget(tr, now, st)
  st = st or G
  if st.histTr ~= tr or not st.hist then st.hist = {}; st.histTr = tr end
  local h = st.hist
  h[#h + 1] = {t = now, p = tr.Position}
  while #h > 2 and now - h[1].t > 0.25 do table.remove(h, 1) end
  local first, last = h[1], h[#h]
  local dtv = last.t - first.t
  if dtv < 0.04 then return Vector3.zero end
  local v = (last.p - first.p) / dtv
  return Vector3.new(v.X, 0, v.Z)
end

local function grabStep(char, hum, root, now)
  -- لو يدك على الجويستيك: انت تلعب، وهو يستنى
  if anyHeld() then G.heldAt = now; grabReset(); clearDrive(); return end
  -- ترفع يدك = يمشي فوراً
  if CFG.RELEASE_DELAY > 0 and now - G.heldAt < CFG.RELEASE_DELAY then clearDrive(); return end

  local tr = pickGrabTarget(root)
  if not tr then grabReset(); clearDrive(); return end

  local me, tp = root.Position, tr.Position
  local dist = Vector3.new(tp.X - me.X, 0, tp.Z - me.Z).Magnitude
  local vel = trackTarget(tr, now)
  local fast = turnRate(tr, now) > CFG.FAST_TURN   -- لف بسرعة → ياخذها أسرع
  if dist <= CFG.GRAB_RANGE + (fast and 4 or 0) then
    tryGrab(tr.Parent, tr, char, root, fast and CFG.FAST_GRAB_CD or nil, fast)
  end
  if dist <= 1.3 then clearDrive(); return end -- وصل

  local pt, still = interceptPoint(me, tr, math.max(hum.WalkSpeed, 10), vel)
  local dt = math.min(now - G.lastT, 0.1)
  G.lastT = now
  if fast or still or not G.smooth or G.lastTr ~= tr then
    G.smooth = pt                         -- لف بسرعة / واقف / هدف جديد: مباشرة بدون تنعيم
  else
    G.smooth = G.smooth:Lerp(pt, math.clamp(9 * dt, 0, 1)) -- يتحرك: تتبع ناعم ما يبين أوتو
  end
  G.lastTr = tr
  setDrive(G.smooth, "grab")
end

-- ================= 🧭 autoTrack (نفس محرك الاوتو قراب، بس يلحق أقرب خصم ويوقف على TRACK_DIST) =================
local T = {smooth = nil, lastTr = nil, lastT = 0, holding = false}
local function trackReset()
  T.smooth = nil; T.lastTr = nil; T.holding = false
  T.hist = nil; T.histTr = nil; T.lastDir = nil; T.lastLook = nil
  T.prevVel = nil; T.prevT = nil; T.acc = nil
end
local function dropTrack() if D.owner == "track" then clearDrive() end end

local function trackEntries(root)
  local list = {}
  for _, p in ipairs(players:GetPlayers()) do
    if p ~= lp and not isTeammate(p) then
      local tr = validRoot(p.Character)
      if tr then list[#list + 1] = {Dist = (tr.Position - root.Position).Magnitude, Root = tr} end
    end
  end
  return list
end

local function pickTrackTarget(root)
  local lockedMode = #ST.locked > 0
  local best, bd = nil, lockedMode and math.huge or CFG.MATCH_RANGE
  local function consider(p)
    local tr = validRoot(p.Character)
    if not tr or tr.Anchored then return end
    if not lockedMode and math.abs(tr.Position.Y - root.Position.Y) > 12 then return end
    local d = (tr.Position - root.Position).Magnitude
    if d < bd then bd = d; best = tr end
  end
  if lockedMode then
    for _, n in ipairs(ST.locked) do
      local p = players:FindFirstChild(n)
      if p then consider(p) end
    end
  else
    for _, p in ipairs(players:GetPlayers()) do
      if p ~= lp and not isTeammate(p) and not isGreenTeammate(p) then consider(p) end
    end
  end
  return best
end

local function trackStep(char, hum, root, now)
  -- يدك على الجويستيك: انت تلعب
  if anyHeld() then trackReset(); dropTrack(); return end

  local tr = pickTrackTarget(root)
  if not tr then trackReset(); dropTrack(); return end

  local me, tp = root.Position, tr.Position
  local dist = Vector3.new(tp.X - me.X, 0, tp.Z - me.Z).Magnitude
  local vel = trackTarget(tr, now, T)                       -- سرعته الحقيقية من تاريخ مكانه (ما تتخربط من اللف)
  if vel.Magnitude > 80 then vel = Vector3.zero end
  local fast = turnRate(tr, now, T) > CFG.FAST_TURN         -- يلف بسرعة؟

  -- 🎁 يعطيه القنبلة: يحاول من أول ما يدخل المدى، وأسرع لو يلف
  if dist <= CFG.GRAB_RANGE + (fast and 4 or 0) and not root.Anchored then
    tryGrab(tr.Parent, tr, char, root, fast and CFG.FAST_GRAB_CD or nil, fast)
  end

  -- يوقف على TRACK_DIST (2.3) ويرجع يلحقه لو ابتعد، بدون رفرفة
  if T.holding then
    if dist > CFG.TRACK_DIST + CFG.RESUME_GAP then T.holding = false end
  elseif dist <= CFG.TRACK_DIST then
    T.holding = true
  end
  if T.holding then dropTrack(); return end

  -- تسارع الخصم (لما يغير اتجاهه أو سرعته) من فرق السرعتين
  local dtA = now - (T.prevT or now)
  if not T.prevVel or T.lastTr ~= tr or dtA > 0.5 then
    T.acc = Vector3.zero; T.prevVel = vel; T.prevT = now
  elseif dtA > 0.05 then
    T.acc = (T.acc or Vector3.zero) * 0.5 + ((vel - T.prevVel) / dtA) * 0.5
    T.prevVel = vel; T.prevT = now
  end
  local acc = T.acc or Vector3.zero
  if acc.Magnitude > 40 then acc = acc.Unit * 40 end

  -- توقع: وقت وصولي الحقيقي (المسافة ÷ سرعتي) بدل رقم ثابت، مع التسارع
  local speed = math.max(hum.WalkSpeed, 10)
  local lead = math.clamp(dist / speed, 0, CFG.LEAD_MAX * 1.5)
  local off = vel * lead + acc * (0.5 * lead * lead)
  if off.Magnitude > 9 then off = off.Unit * 9 end
  local blend = math.clamp((dist - 3) / 8, 0, 1)            -- قريب: يتجه لمكانه الحالي، بعيد: يعترضه
  local aim = tp + off * blend

  local dt = math.min(now - T.lastT, 0.1)
  T.lastT = now
  local still = vel.Magnitude < 1.5
  if fast or still or not T.smooth or T.lastTr ~= tr then
    T.smooth = aim                                          -- لف / واقف / هدف جديد: مباشرة بدون تنعيم
  else
    T.smooth = T.smooth:Lerp(aim, math.clamp(14 * dt, 0, 1)) -- أسرع من الاسيست (6) عشان يلحق اللفّات
  end
  T.lastTr = tr
  setDrive(T.smooth, "track")
end

-- ================= الحلقة الرئيسية =================
local nextFilterAt = 0
keep(RunService.Heartbeat:Connect(function()
  if not alive() then return end
  local now = os.clock()
  local char = lp.Character
  local hum = char and char:FindFirstChildOfClass("Humanoid")
  local root = char and char:FindFirstChild("HumanoidRootPart")
  if not hum or not root or hum.Health <= 0 then clearDrive(); return end
  if root.Anchored then clearDrive(); assistReset(); grabReset(); return end -- برا القيم

  if now >= nextFilterAt then nextFilterAt = now + 1; pcall(refreshFilter) end

  local hasTool = false
  for _, it in ipairs(char:GetChildren()) do
    if it:IsA("Tool") then hasTool = true; break end
  end

  if hasTool then
    grabReset()
    if ST.track then
      -- 🧭 autoTrack: ماسك القنبلة → يلحق الخصم ويعطيه إياها (أحسن من الاسيست)
      assistReset()
      trackStep(char, hum, root, now)
    elseif ST.assist then
      trackReset()
      assistStep(char, hum, root, now)   -- التوقف عند اللمس يتحكم فيه محرك الحركة
    else
      assistReset(); trackReset(); clearDrive()
    end
  else
    assistReset(); trackReset()
    if ST.grab then
      grabStep(char, hum, root, now)
    else
      clearDrive()
    end
  end
end))


-- ================= 🎃 الواجهة (هالوين) =================
local UI = {}
do
  local function mk(class, props, parent)
    local o = Instance.new(class)
    for k, v in pairs(props) do o[k] = v end
    if parent then o.Parent = parent end
    return o
  end
  local function corner(o, r) return mk("UICorner", {CornerRadius = UDim.new(0, r)}, o) end
  local function stroke(o, col, th, tr) return mk("UIStroke", {Color = col, Thickness = th, Transparency = tr}, o) end
  local function tw(o, t, props) TweenService:Create(o, TweenInfo.new(t), props):Play() end

  local gui = mk("ScreenGui", {Name = randomName(), ResetOnSpawn = false, IgnoreGuiInset = true,
    ZIndexBehavior = Enum.ZIndexBehavior.Sibling, DisplayOrder = 100})
  if syn and typeof(syn.protect_gui) == "function" then pcall(syn.protect_gui, gui) end
  gui.Parent = getGuiParent()
  guis[#guis + 1] = gui

  -- زر القرعة العايم
  local pump = mk("TextButton", {Name = randomName(), Size = UDim2.fromOffset(46, 46),
    Position = UDim2.new(0, 12, 0.3, 0), BackgroundColor3 = C.bg, BackgroundTransparency = 0.05,
    Text = "🎃", TextSize = 26, Font = Enum.Font.GothamBold, AutoButtonColor = false,
    Active = true, Draggable = true}, gui)
  corner(pump, 23)
  local pumpStroke = stroke(pump, C.orange, 2, 0.1)

  local W, H = 300, 448
  local panel = mk("Frame", {Name = randomName(), Size = UDim2.fromOffset(W, H),
    Position = UDim2.new(0.5, -W / 2, 0.5, -H / 2), BackgroundColor3 = C.bg, BorderSizePixel = 0,
    Visible = false, ClipsDescendants = true, Active = true, Draggable = true}, gui)
  corner(panel, 16)
  local panelStroke = stroke(panel, C.orange, 2, 0.35)
  mk("UIGradient", {Rotation = 90, Color = ColorSequence.new({
    ColorSequenceKeypoint.new(0, C.purple2), ColorSequenceKeypoint.new(0.4, C.bg),
    ColorSequenceKeypoint.new(1, Color3.fromRGB(6, 3, 10))})}, panel)

  -- ── الزينة ──
  local decor = mk("Frame", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, ZIndex = 1, ClipsDescendants = true}, panel)
  local function dtext(txt, size, x, y, tr)
    return mk("TextLabel", {BackgroundTransparency = 1, Text = txt, TextSize = size, Font = Enum.Font.GothamBold,
      AnchorPoint = Vector2.new(0.5, 0.5), Position = UDim2.fromScale(x, y),
      Size = UDim2.fromOffset(size + 8, size + 8), TextTransparency = tr or 0, ZIndex = 1}, decor)
  end
  local moon = mk("Frame", {AnchorPoint = Vector2.new(0.5, 0.5), Size = UDim2.fromOffset(56, 56),
    Position = UDim2.fromScale(0.83, 0.2), BackgroundColor3 = Color3.fromRGB(255, 222, 150),
    BackgroundTransparency = 0.35, BorderSizePixel = 0, ZIndex = 1}, decor)
  corner(moon, 28); stroke(moon, C.orange, 4, 0.65)
  for _, cr in ipairs({{0.3, 0.35, 14}, {0.65, 0.6, 10}, {0.4, 0.72, 8}}) do
    local c = mk("Frame", {AnchorPoint = Vector2.new(0.5, 0.5), Size = UDim2.fromOffset(cr[3], cr[3]),
      Position = UDim2.fromScale(cr[1], cr[2]), BackgroundColor3 = Color3.fromRGB(235, 190, 110),
      BackgroundTransparency = 0.5, BorderSizePixel = 0, ZIndex = 1}, moon)
    corner(c, cr[3] / 2)
  end
  local bats = {}
  for i = 1, 3 do
    bats[i] = {o = dtext("🦇", 16 + i * 3, 0, 0.1, 0.2), sp = 0.05 + i * 0.02, ph = i * 0.37, y = 0.07 + i * 0.06}
  end
  dtext("🕸", 46, 0.07, 0.05, 0.3)
  local thread = mk("Frame", {BackgroundColor3 = C.dim, BackgroundTransparency = 0.4, BorderSizePixel = 0,
    Size = UDim2.fromOffset(1, 40), Position = UDim2.new(0.62, 0, 0, 0), ZIndex = 1}, decor)
  local spider = dtext("🕷", 20, 0.62, 0, 0)
  local ghosts = {dtext("👻", 26, 0.12, 0.92, 0.35), dtext("👻", 20, 0.9, 0.84, 0.5)}
  local candy = {dtext("🍬", 18, 0.93, 0.5, 0.35), dtext("🍭", 18, 0.05, 0.55, 0.35)}
  local pumpkins = {dtext("🎃", 22, 0.9, 0.965, 0.4), dtext("🎃", 16, 0.42, 0.968, 0.55)}
  local titleGrad

  -- 🩸 دم ينقط من فوق
  local drips = {}
  for i = 1, 7 do
    local d = mk("Frame", {BackgroundColor3 = C.blood, BackgroundTransparency = 0.12, BorderSizePixel = 0, ZIndex = 1,
      Size = UDim2.fromOffset(4, 10), Position = UDim2.new(0.06 + (i - 1) * 0.145, 0, 0, 0)}, decor)
    corner(d, 2)
    local tip = mk("Frame", {AnchorPoint = Vector2.new(0.5, 0), BackgroundColor3 = C.blood, BackgroundTransparency = 0.12,
      BorderSizePixel = 0, ZIndex = 1, Size = UDim2.fromOffset(8, 8), Position = UDim2.new(0.5, 0, 1, -3)}, d)
    corner(tip, 4)
    drips[i] = {o = d, base = 6 + (i * 7) % 14, ph = i * 0.9, sp = 0.5 + (i % 3) * 0.22}
  end

  -- 🌫 ضباب يمشي تحت
  local fog = {}
  for i = 1, 2 do
    local f = mk("Frame", {AnchorPoint = Vector2.new(0, 0.5), Size = UDim2.fromScale(0.9, 0.14),
      Position = UDim2.fromScale(-0.4, 0.8 + i * 0.07), BackgroundColor3 = Color3.fromRGB(190, 160, 235),
      BackgroundTransparency = 0.88, BorderSizePixel = 0, ZIndex = 1}, decor)
    corner(f, 40)
    mk("UIGradient", {Transparency = NumberSequence.new({NumberSequenceKeypoint.new(0, 1),
      NumberSequenceKeypoint.new(0.5, 0.25), NumberSequenceKeypoint.new(1, 1)})}, f)
    fog[i] = {o = f, sp = 0.02 + i * 0.012, ph = i * 0.5, y = 0.8 + i * 0.07}
  end

  -- ⚡ برق خفيف كل كم ثانية
  local flash = mk("Frame", {Size = UDim2.fromScale(1, 1), BackgroundColor3 = Color3.fromRGB(225, 200, 255),
    BackgroundTransparency = 1, BorderSizePixel = 0, ZIndex = 20, Active = false}, panel)
  corner(flash, 16)
  local nextFlash = os.clock() + 6

  task.spawn(function()
    while alive() and gui.Parent do
      local t = os.clock()
      pumpStroke.Transparency = 0.25 + 0.25 * math.sin(t * 3)
      pump.Rotation = math.sin(t * 2) * 7
      if panel.Visible then
        panelStroke.Transparency = 0.3 + 0.2 * math.sin(t * 2.2)
        for i, b in ipairs(bats) do
          b.o.Position = UDim2.new(((t * b.sp + b.ph) % 1.3) - 0.15, 0, b.y + 0.02 * math.sin(t * 4 + i), 0)
          b.o.Rotation = math.sin(t * 9 + i) * 12
        end
        local L = 34 + 18 * math.sin(t * 1.4)
        thread.Size = UDim2.fromOffset(1, L)
        spider.Position = UDim2.new(0.62, 0, 0, L + 8)
        for i, g in ipairs(ghosts) do
          g.Position = UDim2.new(g.Position.X.Scale, 0, 0.9 - 0.04 * i + 0.02 * math.sin(t * 1.6 + i), 0)
          g.TextTransparency = 0.4 + 0.2 * math.sin(t * 2 + i)
        end
        for i, c in ipairs(candy) do c.Rotation = math.sin(t * 1.3 + i) * 14 end
        for i, pk in ipairs(pumpkins) do
          pk.Rotation = math.sin(t * 1.8 + i * 2) * 10
          pk.Position = UDim2.new(pk.Position.X.Scale, 0, 0.965 + 0.006 * math.sin(t * 2.4 + i), 0)
        end
        for _, d in ipairs(drips) do
          d.o.Size = UDim2.fromOffset(4, d.base + 9 * (0.5 + 0.5 * math.sin(t * d.sp + d.ph)))
        end
        for i, f in ipairs(fog) do
          f.o.Position = UDim2.new(((t * f.sp + f.ph) % 1.5) - 0.5, 0, f.y, 0)
        end
        if titleGrad then titleGrad.Offset = Vector2.new(math.sin(t * 1.6) * 0.35, 0) end
        if t >= nextFlash then
          nextFlash = t + math.random(7, 15)
          task.spawn(function()
            for _ = 1, 2 do
              flash.BackgroundTransparency = 0.8
              task.wait(0.05)
              flash.BackgroundTransparency = 1
              task.wait(0.08)
            end
          end)
        end
      end
      task.wait(0.04)
    end
  end)

  -- ── المحتوى ──
  local top = mk("Frame", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, ZIndex = 2}, panel)
  local title = mk("TextLabel", {Size = UDim2.new(1, -50, 0, 22), Position = UDim2.fromOffset(14, 6),
    BackgroundTransparency = 1, Text = "🎃 ASTA  HALLOWEEN", TextColor3 = Color3.new(1, 1, 1), TextSize = 17,
    Font = Enum.Font.GothamBlack, TextXAlignment = Enum.TextXAlignment.Left}, top)
  titleGrad = mk("UIGradient", {Color = ColorSequence.new(C.orange2, C.purple)}, title)
  mk("TextLabel", {Size = UDim2.new(1, -50, 0, 12), Position = UDim2.fromOffset(14, 27), BackgroundTransparency = 1,
    Text = "Devices  •  Features   v7", TextColor3 = C.dim, TextSize = 10, Font = Enum.Font.Gotham,
    TextXAlignment = Enum.TextXAlignment.Left}, top)
  local closeBtn = mk("TextButton", {Size = UDim2.fromOffset(28, 28), Position = UDim2.new(1, -34, 0, 6),
    BackgroundTransparency = 1, Text = "×", TextColor3 = C.text, TextSize = 22, Font = Enum.Font.GothamMedium}, top)

  local tabBar = mk("Frame", {Size = UDim2.new(1, -24, 0, 30), Position = UDim2.fromOffset(12, 48), BackgroundTransparency = 1}, top)
  mk("UIListLayout", {FillDirection = Enum.FillDirection.Horizontal, Padding = UDim.new(0, 6), SortOrder = Enum.SortOrder.LayoutOrder}, tabBar)
  local function makeTab(txt, order)
    local b = mk("TextButton", {Size = UDim2.new(0.5, -3, 1, 0), BackgroundColor3 = C.card, BackgroundTransparency = 0.2,
      Text = txt, TextColor3 = C.dim, TextSize = 13, Font = Enum.Font.GothamBold, AutoButtonColor = false, LayoutOrder = order}, tabBar)
    corner(b, 9)
    return b
  end
  local tabDev = makeTab("📱  الأجهزة", 1)
  local tabFeat = makeTab("🎃  المميزات", 2)

  local content = mk("Frame", {Position = UDim2.fromOffset(12, 86), Size = UDim2.new(1, -24, 1, -118), BackgroundTransparency = 1}, top)
  mk("TextLabel", {Size = UDim2.new(1, -24, 0, 16), Position = UDim2.new(0, 12, 1, -26), BackgroundTransparency = 1,
    Text = BRAND .. "  •  🕸 Happy Halloween 🕸", TextColor3 = C.dim, TextSize = 10, Font = Enum.Font.Gotham}, top)

  local devPage = mk("Frame", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, Visible = false}, content)
  local feat = mk("ScrollingFrame", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, BorderSizePixel = 0,
    ScrollBarThickness = 3, ScrollBarImageColor3 = C.orange, CanvasSize = UDim2.new(),
    AutomaticCanvasSize = Enum.AutomaticSize.Y, Visible = true}, content)
  mk("UIListLayout", {Padding = UDim.new(0, 6), SortOrder = Enum.SortOrder.LayoutOrder,
    HorizontalAlignment = Enum.HorizontalAlignment.Right}, feat)

  local function setTab(name)
    local f = name == "Feat"
    devPage.Visible = not f
    feat.Visible = f
    tw(tabFeat, 0.12, {BackgroundColor3 = f and C.orange or C.card, TextColor3 = f and Color3.fromRGB(25, 10, 0) or C.dim})
    tw(tabDev, 0.12, {BackgroundColor3 = (not f) and C.orange or C.card, TextColor3 = (not f) and Color3.fromRGB(25, 10, 0) or C.dim})
  end
  tabDev.MouseButton1Click:Connect(function() setTab("Dev") end)
  tabFeat.MouseButton1Click:Connect(function() setTab("Feat") end)
  setTab("Feat")

  -- ── صف تفعيل (سويتش) ──
  local onChangeHooks = {}
  local function toggleRow(order, title, sub, key, indent)
    local h = indent and 44 or 54
    local row = mk("TextButton", {Size = UDim2.new(1, -8 - (indent and 18 or 0), 0, h), BackgroundColor3 = C.card,
      BackgroundTransparency = 0.15, Text = "", AutoButtonColor = false, LayoutOrder = order}, feat)
    corner(row, 10)
    local rs = stroke(row, C.orange, 1.2, 0.8)
    mk("TextLabel", {Size = UDim2.new(1, -64, 0, 18), Position = UDim2.fromOffset(10, indent and 5 or 7), BackgroundTransparency = 1,
      Text = title, TextColor3 = C.text, TextSize = indent and 12 or 14, Font = Enum.Font.GothamBold,
      TextXAlignment = Enum.TextXAlignment.Left, TextTruncate = Enum.TextTruncate.AtEnd}, row)
    mk("TextLabel", {Size = UDim2.new(1, -64, 0, 14), Position = UDim2.fromOffset(10, indent and 24 or 28), BackgroundTransparency = 1,
      Text = sub, TextColor3 = C.dim, TextSize = 10, Font = Enum.Font.Gotham,
      TextXAlignment = Enum.TextXAlignment.Left, TextTruncate = Enum.TextTruncate.AtEnd}, row)
    local pill = mk("Frame", {Size = UDim2.fromOffset(42, 22), Position = UDim2.new(1, -52, 0.5, -11), BackgroundColor3 = C.off, BorderSizePixel = 0}, row)
    corner(pill, 11)
    local knob = mk("TextLabel", {Size = UDim2.fromOffset(20, 20), Position = UDim2.new(0, 1, 0.5, -10), BackgroundTransparency = 1,
      Text = "💀", TextSize = 15, Font = Enum.Font.GothamBold, ZIndex = 3}, pill)
    local function render()
      local on = ST[key]
      knob.Text = on and "🎃" or "💀"
      tw(pill, 0.14, {BackgroundColor3 = on and C.orange or C.off})
      tw(knob, 0.14, {Position = on and UDim2.new(1, -21, 0.5, -10) or UDim2.new(0, 1, 0.5, -10)})
      tw(rs, 0.14, {Transparency = on and 0.25 or 0.8})
    end
    row.MouseButton1Click:Connect(function()
      ST[key] = not ST[key]
      render()
      if onChangeHooks[key] then pcall(onChangeHooks[key], ST[key]) end
    end)
    render()
  end

  toggleRow(1, "🎃  الاسيست", "يلحق الخصم وانت ماسك القنبلة ويوقف قريب منه", "assist", false)
  toggleRow(2, "👻  اوتو قراب", "داخل القيم بس: تشيل يدك → يروح للماسك وياخذ القنبلة", "grab", false)
  toggleRow(3, "🦇  رادار الخصوم", "قائمة المسافات + تنبيه لو عدو قريب", "radar", false)
  toggleRow(4, "🧭  autoTrack", "ماسك القنبلة: يلحق الخصم ويعطيه إياها ويوقف على 2.3 studs (أحسن من الاسيست)", "track", false)

  local function sectionLabel(order, txt)
    return mk("TextLabel", {Size = UDim2.new(1, -8, 0, 20), BackgroundTransparency = 1, Text = txt, TextColor3 = C.orange2,
      TextSize = 13, Font = Enum.Font.GothamBold, TextXAlignment = Enum.TextXAlignment.Left, LayoutOrder = order}, feat)
  end
  local radarTitle = sectionLabel(10, "🦇 الرادار")
  radarTitle.Visible = false
  local radarHolder = mk("Frame", {Size = UDim2.new(1, -8, 0, 0), AutomaticSize = Enum.AutomaticSize.Y,
    BackgroundTransparency = 1, LayoutOrder = 11, Visible = false}, feat)
  mk("UIListLayout", {Padding = UDim.new(0, 3), SortOrder = Enum.SortOrder.LayoutOrder}, radarHolder)
  sectionLabel(20, "🎯 اختار الهدف  (حتى " .. CFG.MAX_LOCKED .. ")")
  local targetHolder = mk("Frame", {Size = UDim2.new(1, -8, 0, 0), AutomaticSize = Enum.AutomaticSize.Y,
    BackgroundTransparency = 1, LayoutOrder = 21}, feat)
  mk("UIListLayout", {Padding = UDim.new(0, 4), SortOrder = Enum.SortOrder.LayoutOrder}, targetHolder)

  onChangeHooks.radar = function(on)
    radarTitle.Visible = on
    radarHolder.Visible = on
    if not on then UI.setAlert(math.huge) end
  end

  -- ── الرادار + التنبيه ──
  local rrows = {}
  for i = 1, MAX_ENEMIES do
    local f = mk("Frame", {Size = UDim2.new(1, 0, 0, 28), BackgroundColor3 = C.card, BackgroundTransparency = 0.25,
      BorderSizePixel = 0, LayoutOrder = i, Visible = false}, radarHolder)
    corner(f, 8)
    local n = mk("TextLabel", {Size = UDim2.new(0.65, 0, 1, 0), Position = UDim2.fromOffset(10, 0), BackgroundTransparency = 1,
      TextColor3 = C.text, TextSize = 12, Font = Enum.Font.GothamMedium, TextXAlignment = Enum.TextXAlignment.Left,
      TextTruncate = Enum.TextTruncate.AtEnd, Text = ""}, f)
    local d = mk("TextLabel", {Size = UDim2.new(0.35, -10, 1, 0), Position = UDim2.new(0.65, 0, 0, 0), BackgroundTransparency = 1,
      TextColor3 = C.orange2, TextSize = 12, Font = Enum.Font.GothamBold, TextXAlignment = Enum.TextXAlignment.Right, Text = ""}, f)
    rrows[i] = {f = f, n = n, d = d}
  end
  function UI.setRadar(entries)
    for i = 1, MAX_ENEMIES do
      local r, e = rrows[i], entries[i]
      if e then
        local dd = math.floor(e.Dist)
        r.f.Visible = true
        r.n.Text = e.Name
        r.d.Text = dd .. " 🎯"
        if dd < ALERT_DIST then
          r.f.BackgroundColor3 = Color3.fromRGB(120, 18, 28); r.d.TextColor3 = Color3.fromRGB(255, 90, 90)
        elseif dd < WARN_DIST then
          r.f.BackgroundColor3 = Color3.fromRGB(100, 55, 10); r.d.TextColor3 = C.orange2
        else
          r.f.BackgroundColor3 = C.card; r.d.TextColor3 = C.slime
        end
      else
        r.f.Visible = false
      end
    end
  end
  local alertF = mk("Frame", {Size = UDim2.new(1, 0, 0, 40), BackgroundColor3 = C.blood, BackgroundTransparency = 0.2,
    BorderSizePixel = 0, Visible = false, ZIndex = 50}, gui)
  local alertT = mk("TextLabel", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, TextColor3 = Color3.new(1, 1, 1),
    TextSize = 14, Font = Enum.Font.GothamBold, Text = "", ZIndex = 51}, alertF)
  function UI.setAlert(closest)
    if ST.radar and closest < ALERT_DIST then
      alertT.Text = "☠ عدو قريب — " .. math.floor(closest) .. " studs"
      alertF.Visible = true
    else
      alertF.Visible = false
    end
  end

  -- ── قائمة الأهداف ──
  local btns, lastSig = {}, ""
  -- 🔴 علامة العدو (هايلايت/بوكس أحمر) — احتياط بس
  local function isRedColor(c) return c ~= nil and c.R > 0.6 and c.R > c.G * 1.8 and c.R > c.B * 1.8 end
  local function hasRedMark(p)
    local red = false
    pcall(function()
      local ch = p.Character
      if not ch then return end
      for _, d in ipairs(ch:GetDescendants()) do
        if d:IsA("Highlight") then
          if isRedColor(d.FillColor) or isRedColor(d.OutlineColor) then red = true; break end
        elseif d:IsA("SelectionBox") or d:IsA("SelectionSphere") then
          if isRedColor(d.Color3) then red = true; break end
        end
      end
    end)
    return red
  end
  local function isMate(p)
    local ok, res = pcall(function()
      if isTeammate(p) then return true end
      if isGreenTeammate and isGreenTeammate(p) then return true end
      return false
    end)
    return ok and res or false
  end
  local function distTo(p)
    local ok, d = pcall(function()
      local a = lp.Character and lp.Character:FindFirstChild("HumanoidRootPart")
      local b = p.Character and p.Character:FindFirstChild("HumanoidRootPart")
      if a and b then return (a.Position - b.Position).Magnitude end
      return math.huge
    end)
    return ok and d or math.huge
  end

  -- 🧩 نقرا لاعبين القيم من الواجهة اللي فوق (صور اللاعبين يمين ويسار الـ "0 - 0")
  local function playerFromGui(d)
    local function tryStr(str)
      if type(str) ~= "string" or str == "" then return nil end
      for num in str:gmatch("%d+") do
        if #num >= 4 then
          local ok, p = pcall(function() return players:GetPlayerByUserId(tonumber(num)) end)
          if ok and p then return p end
        end
      end
      local p = players:FindFirstChild(str)
      if p and p:IsA("Player") then return p end
    end
    local cur = d
    for _ = 1, 3 do
      if not cur then break end
      local p
      if cur:IsA("ImageLabel") or cur:IsA("ImageButton") then p = tryStr(cur.Image) end
      p = p or tryStr(cur.Name)
      if p then return p end
      cur = cur.Parent
    end
  end
  local hudGroups, hudAt = nil, 0
  local function parseMatchHud()
    local now = os.clock()
    if now - hudAt < 1 then return hudGroups end
    hudAt = now
    hudGroups = nil
    pcall(function()
      local pg = lp:FindFirstChild("PlayerGui")
      if not pg then return end
      local score
      for _, d in ipairs(pg:GetDescendants()) do
        if d:IsA("TextLabel") and #d.Text <= 9 and d.Text:match("^%s*%d+%s*%-%s*%d+%s*$") and reallyVisible(d) then score = d; break end
      end
      if not score then return end
      local cx = score.AbsolutePosition.X + score.AbsoluteSize.X / 2
      local cont, left, right = score.Parent, {}, {}
      for _ = 1, 6 do
        if not cont or cont == pg then break end
        left, right = {}, {}
        for _, d in ipairs(cont:GetDescendants()) do
          if d:IsA("ImageLabel") or d:IsA("ImageButton") then
            local p = playerFromGui(d)
            if p then
              local x = d.AbsolutePosition.X + d.AbsoluteSize.X / 2
              if x < cx then left[p] = true else right[p] = true end
            end
          end
        end
        if next(left) and next(right) then break end
        cont = cont.Parent
      end
      if not (next(left) and next(right)) then return end
      local mine, enemy
      if left[lp] then mine, enemy = left, right
      elseif right[lp] then mine, enemy = right, left
      else
        -- انا مو بالصور: اللي فيهم أخضر (تيمي) هم جهتي
        local lm, rm = 0, 0
        for p in pairs(left) do if isMate(p) then lm = lm + 1 end end
        for p in pairs(right) do if isMate(p) then rm = rm + 1 end end
        if lm >= rm then mine, enemy = left, right else mine, enemy = right, left end
      end
      hudGroups = {mine = mine, enemy = enemy}
    end)
    return hudGroups
  end

  -- يرجع (الأعداء، فريقي، باقي اللاعبين اللي مو في القيم)
  local function splitPlayers()
    local en, mates, others = {}, {}, {}
    local g = parseMatchHud()
    local inHud = scoreHud()
    for _, p in ipairs(players:GetPlayers()) do
      if p ~= lp then
        if g then
          if g.enemy[p] then en[#en + 1] = p
          elseif g.mine[p] then mates[#mates + 1] = p
          else others[#others + 1] = p end
        elseif inHud then
          -- ما قدرنا نقرا الصور: احتياط (علامة حمراء + قريب منك)
          local near = distTo(p) <= (CFG.MATCH_RANGE or 150)
          if near and isMate(p) then mates[#mates + 1] = p
          elseif near and hasRedMark(p) then en[#en + 1] = p
          else others[#others + 1] = p end
        else
          others[#others + 1] = p                        -- لوبي: الكل بالقائمة العادية
        end
      end
    end
    local byName = function(a, b) return a.Name:lower() < b.Name:lower() end
    table.sort(en, byName); table.sort(mates, byName); table.sort(others, byName)
    return en, mates, others
  end
  local function signature()
    local en, mates, others = splitPlayers()
    local t = {}
    for _, p in ipairs(en) do t[#t + 1] = "E:" .. p.Name end
    for _, p in ipairs(mates) do t[#t + 1] = "M:" .. p.Name end
    for _, p in ipairs(others) do t[#t + 1] = "O:" .. p.Name end
    return table.concat(t, ",") .. "|" .. table.concat(ST.locked, ",")
  end
  function UI.rebuild(force)
    local s = signature()
    if s == lastSig and not force then return end
    lastSig = s
    for _, b in ipairs(btns) do b:Destroy() end
    btns = {}
    local order, count = 0, #ST.locked
    local en, mates, others = splitPlayers()
    local function header(txt, color)
      order = order + 1
      local h = mk("TextLabel", {Size = UDim2.new(1, 0, 0, 22), LayoutOrder = order, BackgroundTransparency = 1,
        TextColor3 = color, TextSize = 12, Font = Enum.Font.GothamBold, TextXAlignment = Enum.TextXAlignment.Left,
        Text = txt}, targetHolder)
      btns[#btns + 1] = h
    end
    local allB = mk("TextButton", {Size = UDim2.new(1, 0, 0, 32), LayoutOrder = order, BorderSizePixel = 0, AutoButtonColor = false,
      BackgroundColor3 = count == 0 and C.purple or C.card, TextColor3 = C.text, TextSize = 13, Font = Enum.Font.GothamBold,
      Text = count == 0 and "🌐 الكل (أقرب)" or ("🌐 الكل  |  مختار: " .. count .. "/" .. CFG.MAX_LOCKED)}, targetHolder)
    corner(allB, 8)
    btns[#btns + 1] = allB
    allB.MouseButton1Click:Connect(function() table.clear(ST.locked); UI.rebuild(true) end)

    -- kind: "enemy" أحمر | "mate" أصفر (داخلين معك القيم) | "other" عادي
    local function addPlayer(p, kind)
      order = order + 1
      local idx
      for i, n in ipairs(ST.locked) do if n == p.Name then idx = i; break end end
      local atMax = #ST.locked >= CFG.MAX_LOCKED
      local nm = "@" .. p.Name .. (p.DisplayName ~= p.Name and ("  (" .. p.DisplayName .. ")") or "")
      local base = kind == "enemy" and Color3.fromRGB(150, 28, 40)
        or kind == "mate" and Color3.fromRGB(150, 118, 12)
        or Color3.fromRGB(58, 34, 92)
      local icon = kind == "enemy" and "☠ " or kind == "mate" and "🟡 " or "🎯 "
      local b = mk("TextButton", {Size = UDim2.new(1, 0, 0, 32), LayoutOrder = order, BorderSizePixel = 0, AutoButtonColor = false,
        BackgroundColor3 = idx and C.blood or (atMax and Color3.fromRGB(48, 40, 60) or base),
        TextColor3 = C.text, TextSize = 13, Font = Enum.Font.GothamBold, TextTruncate = Enum.TextTruncate.AtEnd,
        Text = (idx and ("🔒" .. idx .. " ") or icon) .. nm}, targetHolder)
      corner(b, 8)
      btns[#btns + 1] = b
      local pName = p.Name
      b.MouseButton1Click:Connect(function()
        local at
        for i, n in ipairs(ST.locked) do if n == pName then at = i; break end end
        if at then table.remove(ST.locked, at)
        elseif #ST.locked < CFG.MAX_LOCKED then table.insert(ST.locked, pName) end
        UI.rebuild(true)
      end)
    end

    if #en > 0 then
      header("⚔️ الفريق الي ضدك (" .. #en .. ")", Color3.fromRGB(255, 90, 90))
      for _, p in ipairs(en) do addPlayer(p, "enemy") end
    end
    if #mates > 0 then
      header("🟡 فريقك — داخلين معك القيم (" .. #mates .. ")", Color3.fromRGB(255, 214, 64))
      for _, p in ipairs(mates) do addPlayer(p, "mate") end
    end
    if #others > 0 then
      header(((#en + #mates) > 0 and "👥 باقي اللاعبين (مو في القيم) (" or "👥 اللاعبين (") .. #others .. ")", C.dim)
      for _, p in ipairs(others) do addPlayer(p, "other") end
    end
  end
  keep(Players.PlayerAdded:Connect(function() task.defer(UI.rebuild) end))
  keep(Players.PlayerRemoving:Connect(function() task.defer(UI.rebuild) end))
  task.spawn(function()
    while alive() and gui.Parent do
      if panel.Visible then pcall(UI.rebuild) end
      task.wait(1)
    end
  end)

  -- ── تبويب الأجهزة ──
  local targetDevice, pendingDevice = getTargetDevice(), nil
  local rows = {}
  mk("UIListLayout", {Padding = UDim.new(0, 8), SortOrder = Enum.SortOrder.LayoutOrder}, devPage)
  local function refreshButtons()
    for name, r in pairs(rows) do
      if name == pendingDevice then
        tw(r.Btn, 0.15, {BackgroundColor3 = Color3.fromRGB(210, 100, 20)})
        r.Text.Text = "متأكد؟ اضغط مرة ثانية (يعيد الدخول)"
        r.Text.TextColor3 = Color3.new(1, 1, 1)
        tw(r.Stroke, 0.15, {Color = C.orange2, Transparency = 0.05})
      elseif name == targetDevice then
        tw(r.Btn, 0.15, {BackgroundColor3 = Color3.fromRGB(95, 45, 150)})
        r.Text.Text = (DISPLAY[name] or name) .. "   ✓ Active"
        r.Text.TextColor3 = Color3.fromRGB(235, 215, 255)
        tw(r.Stroke, 0.15, {Color = C.orange, Transparency = 0.05})
      else
        tw(r.Btn, 0.15, {BackgroundColor3 = C.card})
        r.Text.Text = DISPLAY[name] or name
        r.Text.TextColor3 = C.text
        tw(r.Stroke, 0.15, {Color = Color3.new(1, 1, 1), Transparency = 0.88})
      end
    end
  end

  local function rejoinAndApply(deviceName, label)
    targetDevice = deviceName
    setTargetDevice(deviceName)
    pendingDevice = nil
    label.Text = "Rejoining..."
    refreshButtons()
    label.Text = "Rejoining..."
    reapplyDevice()
    asta_queueReload()
    local finished, stage, conn = false, 1, nil
    local function applyInPlace()
      if finished then return end
      finished = true
      asta_hideTeleportError()
      label.Text = "Applied ✓"
      for i = 1, 10 do task.delay((i - 1) * 0.6, reapplyDevice) end
      task.delay(1.5, refreshButtons)
    end
    local function finish(result, msg)
      if conn then conn:Disconnect(); conn = nil end
      if result ~= nil or msg ~= nil then
        asta_notify("Rejoin failed: " .. tostring(result) .. " | " .. tostring(msg))
      end
      applyInPlace()
    end
    local function tryAsync()
      return pcall(function()
        local opts = Instance.new("TeleportOptions")
        opts.ServerInstanceId = game.JobId
        TeleportService:TeleportAsync(game.PlaceId, {lp}, opts)
      end)
    end
    conn = TeleportService.TeleportInitFailed:Connect(function(_, result, msg)
      if finished then return end
      asta_hideTeleportError()
      if stage == 1 then
        stage = 2
        task.spawn(function() if not tryAsync() then finish(result, msg) end end)
      else
        finish(result, msg)
      end
    end)
    local okTp = pcall(function() TeleportService:TeleportToPlaceInstance(game.PlaceId, game.JobId, lp) end)
    if not okTp then
      stage = 2
      task.spawn(function() if not tryAsync() then finish("pcall", "teleport api error") end end)
    end
    task.delay(10, function() if not finished then finish() end end)
  end

  for order, name in ipairs({"Console", "Mobile", "PC"}) do
    local btn = mk("TextButton", {Size = UDim2.new(1, 0, 0, 50), BackgroundColor3 = C.card, BackgroundTransparency = 0.15,
      Text = "", AutoButtonColor = false, LayoutOrder = order}, devPage)
    corner(btn, 10)
    local st = stroke(btn, Color3.new(1, 1, 1), 1.4, 0.88)
    local label = mk("TextLabel", {Size = UDim2.new(1, -20, 1, 0), Position = UDim2.fromOffset(12, 0), BackgroundTransparency = 1,
      Text = DISPLAY[name], TextColor3 = C.text, TextSize = 14, Font = Enum.Font.GothamBold,
      TextXAlignment = Enum.TextXAlignment.Left}, btn)
    rows[name] = {Btn = btn, Stroke = st, Text = label}
    btn.MouseButton1Click:Connect(function()
      if targetDevice == name then return end
      if pendingDevice == name then
        rejoinAndApply(name, label)
      else
        pendingDevice = name
        refreshButtons()
      end
    end)
  end
  mk("TextLabel", {Size = UDim2.new(1, 0, 0, 40), LayoutOrder = 10, BackgroundTransparency = 1, TextWrapped = true,
    Text = "🕸 اضغط على الجهاز مرتين للتأكيد — اللعبة تعيد الدخول وتطبّق الجهاز تلقائي كل مرة تدخل.",
    TextColor3 = C.dim, TextSize = 11, Font = Enum.Font.Gotham}, devPage)
  refreshButtons()

  -- ── فتح/إغلاق + ضغطتين على التُرس ──
  local scale = mk("UIScale", {Scale = 1}, panel)
  local panelOpen = false
  local function openPanel()
    panelOpen = true
    scale.Scale = 0.9
    panel.Visible = true
    TweenService:Create(scale, TweenInfo.new(0.18, Enum.EasingStyle.Back, Enum.EasingDirection.Out), {Scale = 1}):Play()
    pcall(UI.rebuild, true)
  end
  local function closePanel()
    panelOpen = false
    pendingDevice = nil
    refreshButtons()
    local t = TweenService:Create(scale, TweenInfo.new(0.12), {Scale = 0.9})
    t:Play()
    t.Completed:Once(function() if not panelOpen then panel.Visible = false end end)
  end
  pump.MouseButton1Click:Connect(function() if panelOpen then closePanel() else openPanel() end end)
  closeBtn.MouseButton1Click:Connect(closePanel)

  local function inFrame(pos, fr)
    if not (fr and fr.Parent and fr.Visible) then return false end
    local inset = guiService:GetGuiInset()
    local p, s = fr.AbsolutePosition, fr.AbsoluteSize
    for _, q in ipairs({pos, pos + inset}) do
      if q.X >= p.X and q.X <= p.X + s.X and q.Y >= p.Y and q.Y <= p.Y + s.Y then return true end
    end
    return false
  end
  local function findGear()
    for _, d in ipairs(playerGui:GetDescendants()) do
      if d:IsA("GuiButton") and d.Visible and d.AbsoluteSize.X > 0 and not d:IsDescendantOf(gui) then
        local n = d.Name:lower()
        if n:find("setting") or n:find("gear") then return d end
      end
    end
  end
  local function inGearArea(pos)
    local gear = findGear()
    if gear then return inFrame(pos, gear) end
    local v = workspace.CurrentCamera.ViewportSize
    local g = GEAR_FALLBACK
    return pos.X >= v.X * g.x0 and pos.X <= v.X * g.x1 and pos.Y >= v.Y * g.y0 and pos.Y <= v.Y * g.y1
  end
  uiBlock = function(pos) return inFrame(pos, panel) or inFrame(pos, pump) or inGearArea(pos) end

  local lastTap = 0
  keep(UIS.InputBegan:Connect(function(input)
    if input.UserInputType ~= Enum.UserInputType.Touch and input.UserInputType ~= Enum.UserInputType.MouseButton1 then return end
    local pos = Vector2.new(input.Position.X, input.Position.Y)
    if not inGearArea(pos) then return end
    local now = os.clock()
    if now - lastTap <= CFG.DOUBLE_TAP then
      lastTap = 0
      if panelOpen then closePanel() else openPanel() end
    else
      lastTap = now
    end
  end))

  pcall(UI.rebuild, true)
  task.delay(0.5, function()
    asta_notify("🎃 ASTA Halloween جاهز — اضغط القرعة 🎃")
  end)
end

-- ================= 🦇 رادار + 🧭 autoTrack =================
task.spawn(function()
  local lastTrack = 0
  while alive() do
    task.wait(0.5)
    local char = lp.Character
    local myRoot = char and char:FindFirstChild("HumanoidRootPart")
    if not myRoot or not ST.radar then
      if not ST.radar then UI.setAlert(math.huge) end
      continue
    end
    local entries = {}
    for _, p in ipairs(players:GetPlayers()) do
      if p ~= lp and not isTeammate(p) then
        local r = p.Character and p.Character:FindFirstChild("HumanoidRootPart")
        if r then
          entries[#entries + 1] = {Name = p.DisplayName, Dist = (r.Position - myRoot.Position).Magnitude, Root = r}
        end
      end
    end
    table.sort(entries, function(a, b) return a.Dist < b.Dist end)

    if ST.radar then
      UI.setRadar(entries)
      UI.setAlert(entries[1] and entries[1].Dist or math.huge)
    end

  end
end)
]==] loadstring(SRC)()]])
	pcall(function()
		if makefolder and isfolder and not isfolder("autoexec") then
			pcall(makefolder, "autoexec")
		end

		writefile("autoexec/Asta_Halloween_core.lua", "pcall(function() loadstring(readfile('Asta_Halloween_core.lua'))() end)")
	end)
end

local chunk, v2 = loadstring([[local Players = game:GetService("Players")
local TweenService = game:GetService("TweenService")
local TeleportService = game:GetService("TeleportService")
local RunService = game:GetService("RunService")
local UIS = game:GetService("UserInputService")
local GuiService = game:GetService("GuiService")
local ALLOWED_PLACES = {[11379739543] = true, [98752102030179] = true}
local BRAND = "ASTA Halloween"
local DISPLAY = {Console = "🎮  Console", Mobile = "📱  Mobile", PC = "🖥  PC"}
local ALERT_DIST = 20   -- أحمر
local WARN_DIST  = 50   -- برتقالي
local MAX_ENEMIES = 6

-- 🎃 ألوان هالوين
local C = {
  orange = Color3.fromRGB(255, 128, 0),
  orange2 = Color3.fromRGB(255, 176, 48),
  purple = Color3.fromRGB(140, 60, 220),
  purple2 = Color3.fromRGB(62, 22, 108),
  slime = Color3.fromRGB(130, 255, 70),
  blood = Color3.fromRGB(205, 30, 45),
  bg = Color3.fromRGB(16, 9, 24),
  card = Color3.fromRGB(34, 19, 50),
  off = Color3.fromRGB(62, 50, 78),
  text = Color3.fromRGB(246, 236, 255),
  dim = Color3.fromRGB(165, 145, 190),
}

-- لو السكربت شغال من قبل: يطفي النسخة القديمة أول
if _G.__asta_hw_kill then pcall(_G.__asta_hw_kill); task.wait(0.7) end

local function setTargetDevice(device)
  if device == "Pc" or device == "pc" then device = "PC" end
  if writefile then
    pcall(writefile, "sys_cfg_v5_cache.bin", device)
    pcall(writefile, "asta_device.txt", device)
  end
  _G.TargetDevice = device
end
local function getTargetDevice()
  local d = _G.TargetDevice
  if d == "Pc" or d == "pc" then d = "PC" end
  if (d == nil or d == "") and type(isfile) == "function" and type(readfile) == "function" then
    for _, fname in ipairs({"asta_device.txt", "sys_cfg_v5_cache.bin"}) do
      local ok, v = pcall(function()
        if isfile(fname) then return readfile(fname) end
      end)
      if ok and type(v) == "string" then
        v = v:gsub("%s+", "")
        if v == "Pc" or v == "pc" then v = "PC" end
        if v == "Console" or v == "Mobile" or v == "PC" then
          d = v
          _G.TargetDevice = v
          break
        end
      end
    end
  end
  return d
end
local function randomName()
  local text = ""
  for _ = 1, math.random(10, 16) do
    text = text .. string.char(math.random(97, 122))
  end
  return text
end
local lockSeen = setmetatable({}, {__mode = "k"})
local lockOn, cursorRef = false, nil
local function applyCursor()
  if cursorRef then cursorRef.Visible = lockOn end
end
local function forceAncestors(inst)
  local p = inst.Parent
  while p and p ~= game do
    if p:IsA("ScreenGui") then
      if not p.Enabled then p.Enabled = true end
      if not lockSeen[p] then
        lockSeen[p] = true
        p:GetPropertyChangedSignal("Enabled"):Connect(function()
          if not p.Enabled and not _G.__dm_killed then p.Enabled = true end
        end)
      end
      break
    elseif p:IsA("GuiObject") then
      if not p.Visible then p.Visible = true end
      if not lockSeen[p] then
        lockSeen[p] = true
        p:GetPropertyChangedSignal("Visible"):Connect(function()
          if not p.Visible and not _G.__dm_killed then p.Visible = true end
        end)
      end
    end
    p = p.Parent
  end
end
local function lockFix(inst)
  if lockSeen[inst] then return end
  local n = inst.Name
  if n ~= "ConsoleButton" and n ~= "ShiftLockArea" and n ~= "Toggle" and n ~= "MouseLockedCursor" then return end
  if not inst:IsA("GuiObject") then return end
  if n == "ConsoleButton" then
    lockSeen[inst] = true
    inst.Visible = false
  elseif n == "ShiftLockArea" then
    lockSeen[inst] = true
    inst.Visible = true
    inst:GetPropertyChangedSignal("Visible"):Connect(function()
      if not inst.Visible and not _G.__dm_killed then inst.Visible = true end
    end)
    forceAncestors(inst)
  elseif n == "Toggle" and inst.Parent and inst.Parent.Name == "ShiftLockArea" then
    lockSeen[inst] = true
    inst.Visible = true
    inst:GetPropertyChangedSignal("Visible"):Connect(function()
      if not inst.Visible and not _G.__dm_killed then inst.Visible = true end
    end)
    forceAncestors(inst)
    if inst:IsA("GuiButton") then
      inst.MouseButton1Click:Connect(function()
        lockOn = not lockOn
        applyCursor()
      end)
    end
  elseif n == "MouseLockedCursor" then
    lockSeen[inst] = true
    cursorRef = inst
    inst.Visible = lockOn
    inst:GetPropertyChangedSignal("Visible"):Connect(function()
      if inst.Visible ~= lockOn and not _G.__dm_killed then inst.Visible = lockOn end
    end)
  end
end
local function watchLock()
  local lp = Players.LocalPlayer
  if not lp then return end
  task.spawn(function()
    local pg = lp:FindFirstChild("PlayerGui") or lp:WaitForChild("PlayerGui")
    pg.DescendantAdded:Connect(function(d) pcall(lockFix, d) end)
    for _, d in ipairs(pg:GetDescendants()) do pcall(lockFix, d) end
    local t0 = os.clock()
    while os.clock() - t0 < 60 and not _G.__dm_killed do
      pcall(function()
        local area = pg:FindFirstChild("ShiftLockArea", true)
        if area and area:IsA("GuiObject") then
          if lockSeen[area] then
            if not area.Visible then area.Visible = true end
            local tg = area:FindFirstChild("Toggle")
            if tg and tg:IsA("GuiObject") and not tg.Visible then tg.Visible = true end
            forceAncestors(area)
          else
            lockFix(area)
            local tg = area:FindFirstChild("Toggle")
            if tg then lockFix(tg) end
            local cur = pg:FindFirstChild("MouseLockedCursor", true)
            if cur then lockFix(cur) end
          end
        end
      end)
      task.wait(2)
    end
  end)
end
local patchedCache = setmetatable({}, {__mode = "k"})   -- جداول الجهاز اللي لقيناها (تتعدّل بسرعة بدون مسح كامل)
local scanning = false
local lastFullScan = 0
local DEVICE_KEYS = {"Device", "Platform", "DeviceType", "DeviceName", "InputDevice", "Platform_", "CurrentDevice", "CurrentPlatform", "PlayerDevice", "PlayerPlatform"}
local function isDevValue(v) return v == "Mobile" or v == "PC" or v == "Console" end
local function unlockTable(t)
  if type(isreadonly) == "function" and type(setreadonly) == "function" then
    local okR, ro = pcall(isreadonly, t)
    if okR and ro then pcall(setreadonly, t, false) end
  elseif type(make_writeable) == "function" then
    pcall(make_writeable, t)
  end
end
local function patchTable(obj, device)
  local patched, relevant = 0, false
  for _, keyName in ipairs(DEVICE_KEYS) do
    local okK, cur = pcall(rawget, obj, keyName)
    if okK and isDevValue(cur) then
      relevant = true
      if cur ~= device then
        unlockTable(obj)
        if pcall(rawset, obj, keyName, device) then
          patched = patched + 1
          if keyName == "Device" then
            local fix = rawget(obj, "FixXCoordinateAspectRate")
            if type(fix) == "function" then pcall(fix, obj) end
          end
        end
      end
    end
  end
  pcall(function()
    local n = 0
    for k, v in next, obj do
      n = n + 1
      if n > 25 then break end
      if type(k) == "string" and isDevValue(v) then
        local lk = k:lower()
        if lk:find("device") or lk:find("platform") or lk:find("plat") then
          relevant = true
          if v ~= device then
            unlockTable(obj)
            rawset(obj, k, device)
            patched = patched + 1
          end
        end
      end
    end
  end)
  local okInput, preferred = pcall(rawget, obj, "PreferredInput")
  if okInput and type(preferred) == "table" then
    relevant = true
    local wanted = device == "Console" and rawget(obj, "Gamepad") or rawget(obj, "Keyboard")
    if type(wanted) == "table" and preferred ~= wanted then
      pcall(function()
        rawset(obj, "PreferredInput", wanted)
        patched = patched + 1
      end)
    end
  end
  return patched, relevant
end
local function collectCandidates()
  local list = {}
  if type(filtergc) == "function" then
    local keys = {"PreferredInput"}
    for _, k in ipairs(DEVICE_KEYS) do keys[#keys + 1] = k end
    for _, key in ipairs(keys) do
      local ok, res = pcall(filtergc, "table", {Keys = {key}}, false)
      if ok and type(res) == "table" then
        for _, t in ipairs(res) do list[#list + 1] = t end
      end
    end
    if #list > 0 then return list end
  end
  if type(getgc) ~= "function" then return list end
  local ok, objs = pcall(getgc, true)
  if not ok or type(objs) ~= "table" then return list end
  local n = 0
  for _, o in ipairs(objs) do
    n = n + 1
    if type(o) == "table" then list[#list + 1] = o end
    if n % 40000 == 0 then task.wait() end
  end
  return list
end
local function spoofDeviceInGc(device, fast)
  if not device then return 0, 0 end
  local patched, scanned = 0, 0
  for t in pairs(patchedCache) do
    patched = patched + (patchTable(t, device))
  end
  if fast then return patched, 0 end
  if os.clock() - (_G.__asta_t0 or 0) > 30 and next(patchedCache) ~= nil then return patched, 0 end
  local gap = (os.clock() - (_G.__asta_t0 or 0) < 15) and 4 or 60
  if scanning or os.clock() - lastFullScan < gap then return patched, 0 end
  if not (type(filtergc) == "function" or type(getgc) == "function") then
    if not _G.__asta_nogc then _G.__asta_nogc = true; warn('[Asta] getgc/filtergc غير مدعوم في هذا المشغّل') end
    return patched, 0
  end
  _G.__asta_nscans = (_G.__asta_nscans or 0) + 1
  if _G.__asta_nscans > 3 and os.clock() - (_G.__asta_t0 or 0) < 60 then _G.__asta_nscans = 3; return patched, 0 end
  scanning = true
  lastFullScan = os.clock()
  pcall(function()
    local list = collectCandidates()
    for _, obj in ipairs(list) do
      scanned = scanned + 1
      if scanned > 120000 then break end
      if scanned % 4000 == 0 then task.wait() end
      local p, rel = patchTable(obj, device)
      patched = patched + p
      if rel then patchedCache[obj] = true end
    end
  end)
  scanning = false
  return patched, scanned
end
local function spoofDeviceExtra(device)
  local lp = Players.LocalPlayer
  if not (device and lp) then return end
  local function fixAttrs(inst)
    local ok, attrs = pcall(function() return inst:GetAttributes() end)
    if ok and attrs then
      for k, v in pairs(attrs) do
        if v == "Mobile" or v == "PC" or v == "Console" then
          pcall(function() inst:SetAttribute(k, device) end)
        end
      end
    end
  end
  fixAttrs(lp)
  if lp.Character then fixAttrs(lp.Character) end
end
local function getGuiParent()
  if typeof(gethui) == "function" then
    local ok, ui = pcall(gethui)
    if ok and ui then
      return ui
    end
  end
  if typeof(get_hidden_gui) == "function" then
    local ok, ui = pcall(get_hidden_gui)
    if ok and ui then
      return ui
    end
  end
  local CoreGui = game:GetService("CoreGui")
  if syn and typeof(syn.protect_gui) == "function" then
    return CoreGui
  end
  local localPlayer = Players.LocalPlayer
  return CoreGui:FindFirstChild("RobloxGui") or (localPlayer and localPlayer:WaitForChild("PlayerGui"))
end
local function asta_hideTeleportError()
  task.spawn(function()
    for _ = 1, 30 do
      pcall(function() game:GetService("GuiService"):ClearError() end)
      pcall(function()
        local cg = game:GetService("CoreGui")
        local gui = cg:FindFirstChild("RobloxPromptGui")
        local ov = gui and gui:FindFirstChild("promptOverlay")
        if ov then
          for _, c in ipairs(ov:GetChildren()) do
            if c.Name == "ErrorPrompt" then c:Destroy() end
          end
        end
      end)
      task.wait(0.1)
    end
  end)
end
pcall(function()
  if type(delfile) == "function" and type(isfile) == "function" then
    local f = "asta_norejoin_" .. tostring(game.PlaceId) .. ".txt"
    if isfile(f) then delfile(f) end
  end
end)
_G.__asta_norejoin = nil
local function asta_queueReload()
  if type(queue_on_teleport) ~= "function" then return end
  local dev = _G.TargetDevice or "PC"
  local code = "_G.TargetDevice = '" .. tostring(dev) .. "'; "
    .. "pcall(function() local f = readfile('Asta_Halloween_core.lua'); loadstring(f)() end)"
  pcall(queue_on_teleport, code)
end
local function asta_installHooks()
  if _G.__asta_hooked or type(hookmetamethod) ~= "function" then return end
  _G.__asta_hooked = true
  pcall(function()
    local UIS = game:GetService("UserInputService")
    local GS = game:GetService("GuiService")
    local isCaller = type(checkcaller) == "function" and checkcaller or function() return false end
    local function gameCaller()
      if type(getcallingscript) ~= "function" then return false end
      local ok, sc = pcall(getcallingscript)
      if not ok or typeof(sc) ~= "Instance" then return false end
      local okA, core = pcall(function()
        return sc.Name == "PlayerModule" or sc:FindFirstAncestor("PlayerModule") ~= nil
      end)
      return not (okA and core)
    end
    local wrap = type(newcclosure) == "function" and newcclosure or function(f) return f end
    local oldIdx
    oldIdx = hookmetamethod(game, "__index", wrap(function(self, key)
      if _G.__asta_hookoff then return oldIdx(self, key) end
      if self == UIS and type(key) == "string" then
        local dev = _G.TargetDevice
        if dev and (key == "TouchEnabled" or key == "KeyboardEnabled" or key == "MouseEnabled" or key == "GamepadEnabled") then
          if not isCaller() and gameCaller() then
            if key == "TouchEnabled" then return dev == "Mobile" end
            if key == "GamepadEnabled" then return dev == "Console" end
            return dev == "PC"
          end
        end
      end
      return oldIdx(self, key)
    end))
    local oldNc
    oldNc = hookmetamethod(game, "__namecall", wrap(function(self, ...)
      if _G.__asta_hookoff then return oldNc(self, ...) end
      if self == GS or self == UIS then
        local dev = _G.TargetDevice
        if dev and not isCaller() then
          local m = getnamecallmethod()
          if m == "IsTenFootInterface" and self == GS and gameCaller() then return dev == "Console" end
          if m == "GetPlatform" and self == UIS and gameCaller() then
            return dev == "Console" and Enum.Platform.XBoxOne or dev == "PC" and Enum.Platform.Windows or Enum.Platform.IOS
          end
        end
      end
      return oldNc(self, ...)
    end))
    task.delay(25, function()
      _G.__asta_hookoff = true
      pcall(hookmetamethod, game, "__index", oldIdx)
      pcall(hookmetamethod, game, "__namecall", oldNc)
    end)
  end)
end
local function asta_notify(text)
  pcall(function() warn("[Asta] " .. text) end)
  pcall(function()
    local g = Instance.new("ScreenGui")
    g.Name = randomName()
    g.ResetOnSpawn = false
    g.IgnoreGuiInset = true
    g.DisplayOrder = 999
    g.Parent = getGuiParent()
    local l = Instance.new("TextLabel")
    l.Size = UDim2.fromOffset(340, 56)
    l.Position = UDim2.new(0.5, -170, 0, 12)
    l.BackgroundColor3 = Color3.fromRGB(15, 16, 22)
    l.TextColor3 = Color3.fromRGB(255, 220, 120)
    l.TextWrapped = true
    l.TextSize = 13
    l.Font = Enum.Font.GothamMedium
    l.Text = text
    l.Parent = g
    Instance.new("UICorner", l).CornerRadius = UDim.new(0, 10)
    task.delay(12, function() g:Destroy() end)
  end)
end

-- ================= تشغيل محرك الأجهزة (تلقائي من آخر جهاز محفوظ) =================
_G.__dm_killed = false
local lp = Players.LocalPlayer
do
  local dev = getTargetDevice()
  if dev then
    _G.TargetDevice = dev
    asta_installHooks()
    if not _G.__asta_lockwatch then _G.__asta_lockwatch = true; pcall(watchLock) end
    pcall(asta_queueReload)
    if not _G.__asta_early then
      _G.__asta_early = true
      task.spawn(function()
        local t0 = os.clock()
        _G.__asta_t0 = t0
        while not _G.__dm_killed and os.clock() - t0 < 15 do
          local d = _G.TargetDevice or dev
          pcall(spoofDeviceInGc, d)
          pcall(spoofDeviceExtra, d)
          task.wait(1)
        end
      end)
    end
  end
end
if not game:IsLoaded() then game.Loaded:Wait() end
if not ALLOWED_PLACES[game.PlaceId] then
  asta_notify("PlaceId = " .. tostring(game.PlaceId) .. " (مو في القائمة، بس السكربت يكمل)")
  if setclipboard then pcall(setclipboard, tostring(game.PlaceId)) end
end
asta_installHooks()
if getTargetDevice() and not _G.__asta_lockwatch then _G.__asta_lockwatch = true; watchLock() end

local function reapplyDevice()
  if _G.__dm_killed then return end
  local device = getTargetDevice()
  if device then
    pcall(spoofDeviceInGc, device)
    pcall(spoofDeviceExtra, device)
  end
end

task.spawn(function()
  local t0 = os.clock()
  while not _G.__dm_killed do
    local dt = os.clock() - t0
    reapplyDevice()
    if dt < 30 then task.wait(3)
    elseif dt < 90 then task.wait(10)
    else break end
  end
end)
task.spawn(function()
  local pg = lp:FindFirstChild("PlayerGui") or lp:WaitForChild("PlayerGui", 30)
  if not pg then return end
  local pending = false
  pg.DescendantAdded:Connect(function()
    if pending or _G.__dm_killed then return end
    pending = true
    task.delay(1.5, function()
      pending = false
      local d = getTargetDevice()
      if d then pcall(spoofDeviceInGc, d, true) end
    end)
  end)
  pg.ChildAdded:Connect(function()
    if _G.__dm_killed then return end
    task.delay(0.3, reapplyDevice)
  end)
end)
lp.CharacterAdded:Connect(function()
  task.wait(1)
  if not _G.__dm_killed then reapplyDevice() end
end)


-- ================= الحالة والإعدادات (كل ميزة لحالها) =================
local players, localPlayer, runService, uis, guiService, tweenService =
  Players, lp, RunService, UIS, GuiService, TweenService
local playerGui = lp:WaitForChild("PlayerGui")

local ST = {
  assist = true,        -- 🎃 الاسيست (يلحق الخصم وانت ماسك القنبلة)
  grab = true,          -- 👻 اوتو قراب (تشيل يدك → يروح للخصم وياخذ القنبلة)
  radar = false,        -- 🦇 رادار الخصوم + تنبيه
  track = false,        -- 🧭 autoTrack
  locked = {},          -- الأهداف المثبتة (حتى 4)
}
local CFG = {
  MAX_RANGE = 60,       -- أقصى مسافة للاسيست
  STOP_DIST = 2.4,      -- يوقف على هذي المسافة من الخصم
  RESUME_GAP = 0.7,     -- لو ابتعد الخصم بهالزيادة يرجع يلحقه
  START_DELAY = 0.0,
  GRAB_RANGE = 14,      -- من هذي المسافة يبدأ يلمس/ياخذ
  LEAD_MAX = 0.55,
  SMOOTH = 6,
  MAX_LOCKED = 4,
  RELEASE_DELAY = 0,    -- 0 = يمشي لحظة ما ترفع يدك (بدون انتظار)
  GRAB_FALLBACK_NEAREST = false, -- false = ما يتحرك إلا لو في أحد ماسك القنبلة (يعني داخل القيم بس)
  TRACK_DIST = 2.3,     -- autoTrack: يوقف على هالمسافة من الخصم
  MATCH_RANGE = 40,     -- أقصى مسافة للخصم داخل مباراتك (الساحات الثانية أبعد من كذا)
  FAST_TURN = 5,        -- لو الخصم لف أسرع من هذا (rad/s) → الاخذ يصير أسرع
  FAST_GRAB_CD = 0.03,  -- كول داون الاخذ وقت لفّته السريعة
  DOUBLE_TAP = 0.45,
}
local GRAB_COOLDOWN = 0.1
local GEAR_FALLBACK = {x0 = 0.50, y0 = 0.00, x1 = 0.70, y1 = 0.20}

local conns, guis = {}, {}
local function keep(c) conns[#conns + 1] = c; return c end
local function alive() return not _G.__dm_killed end
_G.__asta_hw_kill = function()
  _G.__dm_killed = true
  for _, c in ipairs(conns) do pcall(function() c:Disconnect() end) end
  pcall(function() RunService:UnbindFromRenderStep("AstaHWDrive") end)
  for _, g in ipairs(guis) do pcall(function() g:Destroy() end) end
end

-- ================= كشف لمس الجويستيك / الحركة اليدوية =================
local manualTouches = {}
local MOVE_KEYS = {
  Enum.KeyCode.W, Enum.KeyCode.A, Enum.KeyCode.S, Enum.KeyCode.D,
  Enum.KeyCode.Up, Enum.KeyCode.Down, Enum.KeyCode.Left, Enum.KeyCode.Right,
}
local uiBlock = function(pos) return false end -- تتبدل من الواجهة

keep(UIS.InputBegan:Connect(function(input)
  if input.UserInputType ~= Enum.UserInputType.Touch then return end
  local cam = workspace.CurrentCamera
  if not cam then return end
  local pos = Vector2.new(input.Position.X, input.Position.Y)
  if uiBlock(pos) then return end
  if pos.X < cam.ViewportSize.X * 0.45 and pos.Y > cam.ViewportSize.Y * 0.45 then
    manualTouches[input] = true
  end
end))
keep(UIS.InputEnded:Connect(function(input) manualTouches[input] = nil end))

local function touchHeld()
  for input in pairs(manualTouches) do
    local st = input.UserInputState
    if st == Enum.UserInputState.End or st == Enum.UserInputState.Cancel then manualTouches[input] = nil end
  end
  return next(manualTouches) ~= nil
end
local function keyHeld()
  if not UIS:GetFocusedTextBox() then
    for _, k in ipairs(MOVE_KEYS) do
      if UIS:IsKeyDown(k) then return true end
    end
  end
  local ok, res = pcall(function()
    for _, io in ipairs(UIS:GetGamepadState(Enum.UserInputType.Gamepad1)) do
      if io.KeyCode == Enum.KeyCode.Thumbstick1 and io.Position.Magnitude > 0.25 then return true end
    end
    return false
  end)
  return ok and res == true
end
local function anyHeld() return touchHeld() or keyHeld() end

-- ================= أدوات من ASTA v28 (بدون تغيير) =================
local function isTeammate(p)
    local myTeam = localPlayer.Team
    if myTeam and p.Team == myTeam then return true end
    if localPlayer.Neutral == false and p.Neutral == false and p.TeamColor == localPlayer.TeamColor then
        return true
    end
    return false
end
local lastGrab = 0

local function findBomb(char)
    local fallback
    for _, it in ipairs(char:GetChildren()) do
        if it:IsA("Tool") then
            local n = it.Name:lower()
            if n:find("bomb") or it.Name:find("قنبل") then return it end
            fallback = fallback or it
        end
    end
    return fallback
end

local function tryGrab(targetChar, targetRoot, myChar, myRoot, cd, all)
    local now = os.clock()
    if now - lastGrab < (cd or GRAB_COOLDOWN) then return end
    lastGrab = now

    -- 1) يستخدم الأداة اللي بيدك
    for _, item in ipairs(myChar:GetChildren()) do
        if item:IsA("Tool") then pcall(function() item:Activate() end) end
    end

    -- 2) أزرار التفاعل (لو اللعبة تستخدمها)
    if fireproximityprompt then
        for _, d in ipairs(targetChar:GetDescendants()) do
            if d:IsA("ProximityPrompt") and d.Enabled then pcall(fireproximityprompt, d) end
        end
    end

    -- 3) لمس القنبلة/الخصم (لو اللعبة تنقلها باللمس)
    if not firetouchinterest then
        -- الاكسكيوتر ما يدعم firetouchinterest: نقرب شخصيتك لحد ما تلمس الخصم
        local flat = Vector3.new(targetRoot.Position.X - myRoot.Position.X, 0, targetRoot.Position.Z - myRoot.Position.Z)
        if flat.Magnitude > 1.6 then
            local step = math.min(flat.Magnitude - 1.4, all and 9 or 5)
            local dest = myRoot.Position + flat.Unit * step
            myRoot.CFrame = CFrame.new(dest) * (myRoot.CFrame - myRoot.CFrame.Position)
        end
    else
        local bomb = findBomb(targetChar)
        local parts = {targetRoot}
        local handle = bomb and bomb:FindFirstChild("Handle")
        if handle then table.insert(parts, handle) end
        for _, n in ipairs({"Torso", "UpperTorso", "Head", "Right Arm", "RightHand"}) do
            local pt = targetChar:FindFirstChild(n)
            if pt then table.insert(parts, pt) end
        end
        if all then
            -- لفّ بسرعة: القنبلة تتأرجح حول جسمه، فنلمس كل أجزاءه وأجزاء القنبلة (حد 24)
            local function addAll(root0)
                for _, d in ipairs(root0:GetDescendants()) do
                    if #parts >= 24 then return end
                    if d:IsA("BasePart") then table.insert(parts, d) end
                end
            end
            addAll(targetChar)
            if bomb then addAll(bomb) end
        end
        pcall(function()
            for _, pt in ipairs(parts) do
                firetouchinterest(myRoot, pt, 0)
                firetouchinterest(myRoot, pt, 1)
            end
        end)
    end
end
-- ================= اللاعبين اللي علامتهم خضراء (تيمك): الاسيست يتجاهلهم ويروح بس على الخصم =================
local isGreenTeammate
do
    local function isGreenColor(c)
        return c and c.G > 0.45 and c.G > c.R * 1.35 and c.G > c.B * 1.35
    end
    local function colorsOf(inst)
        local out = {}
        if inst:IsA("Highlight") then
            table.insert(out, inst.FillColor); table.insert(out, inst.OutlineColor)
        elseif inst:IsA("SelectionBox") or inst:IsA("SelectionSphere") then
            table.insert(out, inst.Color3)
        elseif inst:IsA("TextLabel") or inst:IsA("TextButton") then
            table.insert(out, inst.TextColor3)
            if inst.BackgroundTransparency < 0.9 then table.insert(out, inst.BackgroundColor3) end
        elseif inst:IsA("ImageLabel") then
            table.insert(out, inst.ImageColor3)
        elseif inst:IsA("Frame") and inst.BackgroundTransparency < 0.9 then
            table.insert(out, inst.BackgroundColor3)
        elseif inst:IsA("UIStroke") then
            table.insert(out, inst.Color)
        end
        return out
    end
    local function hasGreenMark(root)
        for _, d in ipairs(root:GetDescendants()) do
            for _, c in ipairs(colorsOf(d)) do
                if isGreenColor(c) then return true end
            end
        end
        return false
    end
    local cache, at = {}, 0
    local function refresh()
        local now = os.clock()
        if now - at < 0.6 then return end
        at = now
        cache = {}
        for _, p in ipairs(players:GetPlayers()) do
            if p ~= localPlayer then
                local green = false
                pcall(function()
                    if p.Team and isGreenColor(p.TeamColor.Color) then green = true end
                    local ch = p.Character
                    if not green and ch then
                        for _, d in ipairs(ch:GetDescendants()) do
                            if d:IsA("Highlight") or d:IsA("SelectionBox") then
                                for _, c in ipairs(colorsOf(d)) do if isGreenColor(c) then green = true end end
                            elseif d:IsA("BillboardGui") or d:IsA("SurfaceGui") then
                                if hasGreenMark(d) then green = true end
                            end
                            if green then break end
                        end
                        -- علامات خضراء موضوعة بعيد عن الشخصية (Adornee)
                        if not green then
                            for _, root in ipairs({workspace, playerGui}) do
                                if not green then
                                    for _, d in ipairs(root:GetChildren()) do
                                        if d:IsA("Highlight") or d:IsA("SelectionBox") or d:IsA("BillboardGui") then
                                            local ad = d.Adornee
                                            if ad and (ad == ch or ad:IsDescendantOf(ch)) then
                                                if d:IsA("BillboardGui") then
                                                    if hasGreenMark(d) then green = true end
                                                else
                                                    for _, c in ipairs(colorsOf(d)) do if isGreenColor(c) then green = true end end
                                                end
                                            end
                                        end
                                    end
                                end
                            end
                        end
                    end
                end)
                cache[p] = green
            end
        end
    end
    isGreenTeammate = function(p)
        refresh()
        return cache[p] == true
    end
end
local rayParams = RaycastParams.new()
rayParams.FilterType = Enum.RaycastFilterType.Exclude
local nextFilter = 0

local function refreshFilter()
    local list = {}
    for _, p in ipairs(players:GetPlayers()) do
        if p.Character then table.insert(list, p.Character) end
    end
    rayParams.FilterDescendantsInstances = list
end

local function blocked(from, to)
    for _, yOff in ipairs({0, -2}) do
        local o = Vector3.new(from.X, from.Y + yOff, from.Z)
        local d = Vector3.new(to.X, from.Y + yOff, to.Z) - o
        if d.Magnitude > 0.5 then
            local hit = workspace:Raycast(o, d, rayParams)
            if hit and hit.Instance.CanCollide then return true end
        end
    end
    return false
end

-- يحسب اتجاه تفادي الجدار: يجرب يمين/يسار/قدام بزوايا متعددة ويرجع أفضل اتجاه
local function getAvoidDir(from, to, prefer)
    local flat = Vector3.new(to.X - from.X, 0, to.Z - from.Z)
    if flat.Magnitude < 0.5 then return flat, prefer end
    local forward = flat.Unit
    local function rot(rad)
        return Vector3.new(
            forward.X * math.cos(rad) - forward.Z * math.sin(rad), 0,
            forward.X * math.sin(rad) + forward.Z * math.cos(rad)
        )
    end
    -- الجهة المفضلة أول (نفس اللي اخترناها قبل)، وإلا يمين
    local first = (prefer == -1) and -1 or 1
    for _, deg in ipairs({30, 60, 90, 120}) do
        local rad = math.rad(deg)
        local d1 = rot(rad * first)
        if not blocked(from, from + d1 * 6) then return d1, first end
        local d2 = rot(-rad * first)
        if not blocked(from, from + d2 * 6) then return d2, -first end
    end
    -- لو ما لقى طريق: يرجع على نفسه
    return -forward, first
end

-- ================= محرك الحركة (مشترك بين الاسيست والاوتو قراب) =================
local D = {pos = nil, untilT = 0, owner = nil, avoid = nil, avoidUntil = 0, side = nil, lastDir = nil}
local function setDrive(pos, owner) D.pos = pos; D.untilT = os.clock() + 0.2; D.owner = owner end
local function clearDrive() D.pos = nil; D.owner = nil; D.avoid = nil; D.avoidUntil = 0; D.side = nil; D.lastDir = nil end

RunService:BindToRenderStep("AstaHWDrive", Enum.RenderPriority.Input.Value + 1, function()
  local char = lp.Character
  local hum = char and char:FindFirstChildOfClass("Humanoid")
  local root = char and char:FindFirstChild("HumanoidRootPart")
  if not hum or not root or hum.Health <= 0 or root.Anchored then return end
  if not D.pos or os.clock() > D.untilT then return end

  -- اللاعب دايم له الأولوية: يدك على الجويستيك = ما يصير شي، ترفعها = يكمل الاوتو
  if anyHeld() then return end

  local d = Vector3.new(D.pos.X - root.Position.X, 0, D.pos.Z - root.Position.Z)
  if d.Magnitude > 1.2 then
    local t = os.clock()
    local nx = math.sin(t * 3.7 + 1.1) * 0.018
    local nz = math.cos(t * 2.9 + 0.5) * 0.018
    local rawDir = (d + Vector3.new(nx, 0, nz)).Unit
    local myPos = root.Position
    local dir = rawDir
    local nowT = os.clock()
    if D.avoid and nowT < D.avoidUntil then
      -- ملتزم باتجاه التفادي: ما يغيّره كل فريم (هذا اللي كان يسوي يمين/يسار)
      if blocked(myPos, myPos + D.avoid * 4) then
        D.avoid, D.side = getAvoidDir(myPos, D.pos, D.side)
        D.avoidUntil = nowT + 0.5
      end
      dir = D.avoid
    elseif blocked(myPos, myPos + rawDir * 5) then
      local avoid, side = getAvoidDir(myPos, D.pos, D.side)
      D.avoid, D.side = avoid, side
      D.avoidUntil = nowT + 0.5
      dir = avoid
    else
      D.avoid = nil
    end
    -- تنعيم الاتجاه عشان ما يلف فجأة
    if D.lastDir and dir:Dot(D.lastDir) > -0.5 then
      local sm = D.lastDir:Lerp(dir, 0.35)
      if sm.Magnitude > 0.01 then dir = sm.Unit end
    end
    D.lastDir = dir
    hum:Move(dir, false)
  else
    hum:Move(Vector3.zero, false)
  end
end)

-- ================= اختيار الأهداف =================
local function hasBomb(c) return findBomb(c) ~= nil end
local function validRoot(c)
  local tr = c and c:FindFirstChild("HumanoidRootPart")
  local th = c and c:FindFirstChildOfClass("Humanoid")
  if tr and th and th.Health > 0 then return tr end
end

-- ================= 🎯 هل أنا داخل مباراة فعلاً؟ =================
-- واجهة النتيجة فوق ("1 - 2") ما تظهر إلا داخل المباراة. اللوبي ما فيه.
local hudSeen = false
local hudCache = {t = 0, v = false}
local function reallyVisible(o)
  local cur = o
  while cur and cur ~= game do
    if cur:IsA("GuiObject") and not cur.Visible then return false end
    if cur:IsA("ScreenGui") then return cur.Enabled end
    cur = cur.Parent
  end
  return true
end
local function scoreHud()
  local now = os.clock()
  if now - hudCache.t < 0.5 then return hudCache.v end
  hudCache.t = now
  local found = false
  pcall(function()
    local pg = lp:FindFirstChild("PlayerGui")
    if not pg then return end
    for _, d in ipairs(pg:GetDescendants()) do
      if d:IsA("TextLabel") and #d.Text <= 9 and d.Text:match("^%s*%d+%s*%-%s*%d+%s*$") and reallyVisible(d) then
        found = true
        break
      end
    end
  end)
  if found then hudSeen = true end
  hudCache.v = found
  return found
end
-- true  = واجهة المباراة ظاهرة
-- true  = ما شفنا الواجهة ولا مرة (ما نعرف شكلها) → نعتمد على المسافة والقنبلة
-- false = عرفنا الواجهة وهي مو ظاهرة الحين → انت في اللوبي
local function matchGate()
  if scoreHud() then return true end
  return not hudSeen
end
-- نفس الشي للاوتو تراك: لازم قنبلة شغالة قريبة منك (أو معك) لو الواجهة مجهولة
local function matchOn(myChar, entries)
  if scoreHud() then return true end
  if hudSeen then return false end
  if myChar and myChar:FindFirstChildOfClass("Tool") then return true end
  for _, e in ipairs(entries) do
    if e.Dist <= CFG.MATCH_RANGE and e.Root and e.Root.Parent and hasBomb(e.Root.Parent) then return true end
  end
  return false
end

-- للاسيست: (أقرب هدف, مسافته, أقرب واحد ماسك قنبلة, هل في أهداف مثبتة)
local function pickTargets(root)
  local nearest, nd = nil, CFG.MAX_RANGE
  local bomb, bd = nil, CFG.MAX_RANGE
  if #ST.locked > 0 then
    nd = math.huge
    for i = #ST.locked, 1, -1 do
      local p = players:FindFirstChild(ST.locked[i])
      if not p then
        table.remove(ST.locked, i)
      else
        local tr = validRoot(p.Character)
        if tr then
          local d = (root.Position - tr.Position).Magnitude
          if d < nd then nd = d; nearest = tr end
          if d < bd and hasBomb(p.Character) then bd = d; bomb = tr end
        end
      end
    end
    return nearest, nd, bomb, #ST.locked > 0
  end
  for _, p in ipairs(players:GetPlayers()) do
    if p ~= lp and not isTeammate(p) and not isGreenTeammate(p) then
      local tr = validRoot(p.Character)
      if tr and not tr.Anchored and math.abs(tr.Position.Y - root.Position.Y) <= 25 then
        local d = (root.Position - tr.Position).Magnitude
        if d <= CFG.MAX_RANGE then
          if d < nd then nd = d; nearest = tr end
          if d < bd and hasBomb(p.Character) then bd = d; bomb = tr end
        end
      end
    end
  end
  return nearest, nd, bomb, false
end

-- للاوتو قراب: يفضّل اللي ماسك القنبلة
local function pickGrabTarget(root)
  if not matchGate() then return nil end   -- برا المباراة: ما يلاحق أحد
  local holder, hd = nil, math.huge
  local any, ad = nil, math.huge
  local lockedMode = #ST.locked > 0
  local function consider(p)
    local c = p.Character
    local tr = validRoot(c)
    if not tr or tr.Anchored then return end
    local d = (tr.Position - root.Position).Magnitude
    if not lockedMode and (d > CFG.MATCH_RANGE or math.abs(tr.Position.Y - root.Position.Y) > 12) then return end
    if d < ad then ad = d; any = tr end
    if d < hd and hasBomb(c) then hd = d; holder = tr end
  end
  if lockedMode then
    for _, n in ipairs(ST.locked) do
      local p = players:FindFirstChild(n)
      if p then consider(p) end
    end
  else
    for _, p in ipairs(players:GetPlayers()) do
      if p ~= lp and not isTeammate(p) and not isGreenTeammate(p) then consider(p) end
    end
  end
  if holder then return holder end
  -- 🎯 لو محدد أهداف: ما يروح غير لهم، وأقرب واحد منهم (حتى لو ما معه القنبلة)
  if lockedMode then return any end
  if CFG.GRAB_FALLBACK_NEAREST then return any end
  return nil
end

-- نقطة اعتراض: يتوقع وين بيكون الخصم لو يمشي، ولو واقف (هولد) يروح له مباشرة
local function interceptPoint(me, tr, speed, vOverride)
  local tp = tr.Position
  local rv = tr.AssemblyLinearVelocity
  local v = vOverride or Vector3.new(rv.X, 0, rv.Z)
  if v.Magnitude > 80 then v = Vector3.zero end
  if v.Magnitude < 1.5 then return tp, true end
  local t = (Vector3.new(tp.X - me.X, 0, tp.Z - me.Z)).Magnitude / speed
  for _ = 1, 3 do
    local pred = tp + v * math.min(t, 0.9)
    t = Vector3.new(pred.X - me.X, 0, pred.Z - me.Z).Magnitude / speed
  end
  local off = v * math.min(t, 0.9)
  if off.Magnitude > 12 then off = off.Unit * 12 end
  return tp + off, false
end

-- ================= 🎃 الاسيست (وانت ماسك القنبلة) =================
local A = {holding = false, had = false, resumeAt = 0, smooth = nil, lastSmooth = 0, lastTr = nil}
A.track = setmetatable({}, {__mode = "k"})

local function assistReset() A.holding = false; A.had = false; A.smooth = nil; A.lastTr = nil end

local function assistStep(char, hum, root, now)
  local tr, _, bombRoot = pickTargets(root)
  if not tr then
    if #ST.locked > 0 then clearDrive(); return end  -- أهدافك ميتين: يوقف
    A.holding = false; clearDrive(); return
  end
  if ST.grab and bombRoot then tr = bombRoot end

  local tPos, me = tr.Position, root.Position
  local dist = Vector3.new(tPos.X - me.X, 0, tPos.Z - me.Z).Magnitude

  -- لمس/أخذ القنبلة لما تقرب
  if ST.grab and dist <= CFG.GRAB_RANGE and not root.Anchored then
    tryGrab(tr.Parent, tr, char, root)
  end

  if not A.had then A.had = true; A.resumeAt = now + CFG.START_DELAY end
  if now < A.resumeAt then A.holding = false; clearDrive(); return end

  if A.holding then
    if dist > CFG.STOP_DIST + CFG.RESUME_GAP then A.holding = false end
  elseif dist <= CFG.STOP_DIST then
    A.holding = true
  end
  if A.holding then clearDrive(); D.untilT = 0; return end

  -- توقع ذكي (سرعة + تسارع)
  local rv = tr.AssemblyLinearVelocity
  local vel = Vector3.new(rv.X, 0, rv.Z)
  if vel.Magnitude > 80 then vel = Vector3.zero end
  local key = tr.Parent
  local tk = A.track[key]
  if not tk then tk = {vel = vel, t = now, acc = Vector3.zero}; A.track[key] = tk end
  local dtv = now - tk.t
  if dtv > 0.05 then
    tk.acc = tk.acc * 0.6 + ((vel - tk.vel) / dtv) * 0.4
    tk.vel = vel
    tk.t = now
  end
  local acc = tk.acc
  if acc.Magnitude > 40 then acc = acc.Unit * 40 end
  local lead = math.clamp(dist / 18, 0, CFG.LEAD_MAX)
  local off = vel * lead + acc * (0.5 * lead * lead)
  if off.Magnitude > 7 then off = off.Unit * 7 end
  local raw = tPos + off

  local dtS = math.min(now - A.lastSmooth, 0.1)
  A.lastSmooth = now
  if not A.smooth or A.lastTr ~= tr then
    A.smooth = raw
  else
    A.smooth = A.smooth:Lerp(raw, math.clamp(CFG.SMOOTH * dtS, 0, 1))
  end
  A.lastTr = tr
  setDrive(A.smooth, "assist")
end

-- ================= 👻 اوتو قراب (تشيل يدك → يروح للخصم وياخذ القنبلة) =================
local G = {heldAt = 0, smooth = nil, lastTr = nil, lastT = 0}

local function grabReset() G.smooth = nil; G.lastTr = nil; G.lastDir = nil; G.hist = nil; G.histTr = nil; G.lastLook = nil end

-- سرعة لفّ الخصم: دوران الجسم أو تغيّر اتجاه مشيه بين فريمين (rad/s)
local function turnRate(tr, now, st)
  st = st or G
  local rate, moveRate = 0, 0
  -- 1) دوران جسم الخصم من اتجاه النظر (يمسك حتى لو اللف بالـ CFrame والـ velocity صفر)
  local lv = tr.CFrame.LookVector
  local lk = Vector3.new(lv.X, 0, lv.Z)
  if lk.Magnitude > 0.01 then
    lk = lk.Unit
    if st.lastLook and st.lastLookT then
      local dot = math.clamp(lk:Dot(st.lastLook), -1, 1)
      rate = math.acos(dot) / math.max(now - st.lastLookT, 1 / 120)
    end
    st.lastLook = lk
    st.lastLookT = now
  end
  -- 2) تغيّر اتجاه مشيه
  local rv = tr.AssemblyLinearVelocity
  local v = Vector3.new(rv.X, 0, rv.Z)
  if v.Magnitude > 2 then
    if st.lastDir and st.lastDirT then
      local dot = math.clamp(v.Unit:Dot(st.lastDir), -1, 1)
      moveRate = math.acos(dot) / math.max(now - st.lastDirT, 1 / 120)
    end
    st.lastDir = v.Unit
    st.lastDirT = now
  else
    st.lastDir = nil
  end
  -- 3) سرعة الدوران من الفيزياء
  return math.max(rate, moveRate, math.abs(tr.AssemblyAngularVelocity.Y))
end

-- سرعة الخصم الحقيقية من تاريخ مكانه (آخر 0.25 ثانية): ما تتخربط من اللف
local function trackTarget(tr, now, st)
  st = st or G
  if st.histTr ~= tr or not st.hist then st.hist = {}; st.histTr = tr end
  local h = st.hist
  h[#h + 1] = {t = now, p = tr.Position}
  while #h > 2 and now - h[1].t > 0.25 do table.remove(h, 1) end
  local first, last = h[1], h[#h]
  local dtv = last.t - first.t
  if dtv < 0.04 then return Vector3.zero end
  local v = (last.p - first.p) / dtv
  return Vector3.new(v.X, 0, v.Z)
end

local function grabStep(char, hum, root, now)
  -- لو يدك على الجويستيك: انت تلعب، وهو يستنى
  if anyHeld() then G.heldAt = now; grabReset(); clearDrive(); return end
  -- ترفع يدك = يمشي فوراً
  if CFG.RELEASE_DELAY > 0 and now - G.heldAt < CFG.RELEASE_DELAY then clearDrive(); return end

  local tr = pickGrabTarget(root)
  if not tr then grabReset(); clearDrive(); return end

  local me, tp = root.Position, tr.Position
  local dist = Vector3.new(tp.X - me.X, 0, tp.Z - me.Z).Magnitude
  local vel = trackTarget(tr, now)
  local fast = turnRate(tr, now) > CFG.FAST_TURN   -- لف بسرعة → ياخذها أسرع
  if dist <= CFG.GRAB_RANGE + (fast and 4 or 0) then
    tryGrab(tr.Parent, tr, char, root, fast and CFG.FAST_GRAB_CD or nil, fast)
  end
  if dist <= 1.3 then clearDrive(); return end -- وصل

  local pt, still = interceptPoint(me, tr, math.max(hum.WalkSpeed, 10), vel)
  local dt = math.min(now - G.lastT, 0.1)
  G.lastT = now
  if fast or still or not G.smooth or G.lastTr ~= tr then
    G.smooth = pt                         -- لف بسرعة / واقف / هدف جديد: مباشرة بدون تنعيم
  else
    G.smooth = G.smooth:Lerp(pt, math.clamp(9 * dt, 0, 1)) -- يتحرك: تتبع ناعم ما يبين أوتو
  end
  G.lastTr = tr
  setDrive(G.smooth, "grab")
end

-- ================= 🧭 autoTrack (نفس محرك الاوتو قراب، بس يلحق أقرب خصم ويوقف على TRACK_DIST) =================
local T = {smooth = nil, lastTr = nil, lastT = 0, holding = false}
local function trackReset()
  T.smooth = nil; T.lastTr = nil; T.holding = false
  T.hist = nil; T.histTr = nil; T.lastDir = nil; T.lastLook = nil
  T.prevVel = nil; T.prevT = nil; T.acc = nil
end
local function dropTrack() if D.owner == "track" then clearDrive() end end

local function trackEntries(root)
  local list = {}
  for _, p in ipairs(players:GetPlayers()) do
    if p ~= lp and not isTeammate(p) then
      local tr = validRoot(p.Character)
      if tr then list[#list + 1] = {Dist = (tr.Position - root.Position).Magnitude, Root = tr} end
    end
  end
  return list
end

local function pickTrackTarget(root)
  local lockedMode = #ST.locked > 0
  local best, bd = nil, lockedMode and math.huge or CFG.MATCH_RANGE
  local function consider(p)
    local tr = validRoot(p.Character)
    if not tr or tr.Anchored then return end
    if not lockedMode and math.abs(tr.Position.Y - root.Position.Y) > 12 then return end
    local d = (tr.Position - root.Position).Magnitude
    if d < bd then bd = d; best = tr end
  end
  if lockedMode then
    for _, n in ipairs(ST.locked) do
      local p = players:FindFirstChild(n)
      if p then consider(p) end
    end
  else
    for _, p in ipairs(players:GetPlayers()) do
      if p ~= lp and not isTeammate(p) and not isGreenTeammate(p) then consider(p) end
    end
  end
  return best
end

local function trackStep(char, hum, root, now)
  -- يدك على الجويستيك: انت تلعب
  if anyHeld() then trackReset(); dropTrack(); return end

  local tr = pickTrackTarget(root)
  if not tr then trackReset(); dropTrack(); return end

  local me, tp = root.Position, tr.Position
  local dist = Vector3.new(tp.X - me.X, 0, tp.Z - me.Z).Magnitude
  local vel = trackTarget(tr, now, T)                       -- سرعته الحقيقية من تاريخ مكانه (ما تتخربط من اللف)
  if vel.Magnitude > 80 then vel = Vector3.zero end
  local fast = turnRate(tr, now, T) > CFG.FAST_TURN         -- يلف بسرعة؟

  -- 🎁 يعطيه القنبلة: يحاول من أول ما يدخل المدى، وأسرع لو يلف
  if dist <= CFG.GRAB_RANGE + (fast and 4 or 0) and not root.Anchored then
    tryGrab(tr.Parent, tr, char, root, fast and CFG.FAST_GRAB_CD or nil, fast)
  end

  -- يوقف على TRACK_DIST (2.3) ويرجع يلحقه لو ابتعد، بدون رفرفة
  if T.holding then
    if dist > CFG.TRACK_DIST + CFG.RESUME_GAP then T.holding = false end
  elseif dist <= CFG.TRACK_DIST then
    T.holding = true
  end
  if T.holding then dropTrack(); return end

  -- تسارع الخصم (لما يغير اتجاهه أو سرعته) من فرق السرعتين
  local dtA = now - (T.prevT or now)
  if not T.prevVel or T.lastTr ~= tr or dtA > 0.5 then
    T.acc = Vector3.zero; T.prevVel = vel; T.prevT = now
  elseif dtA > 0.05 then
    T.acc = (T.acc or Vector3.zero) * 0.5 + ((vel - T.prevVel) / dtA) * 0.5
    T.prevVel = vel; T.prevT = now
  end
  local acc = T.acc or Vector3.zero
  if acc.Magnitude > 40 then acc = acc.Unit * 40 end

  -- توقع: وقت وصولي الحقيقي (المسافة ÷ سرعتي) بدل رقم ثابت، مع التسارع
  local speed = math.max(hum.WalkSpeed, 10)
  local lead = math.clamp(dist / speed, 0, CFG.LEAD_MAX * 1.5)
  local off = vel * lead + acc * (0.5 * lead * lead)
  if off.Magnitude > 9 then off = off.Unit * 9 end
  local blend = math.clamp((dist - 3) / 8, 0, 1)            -- قريب: يتجه لمكانه الحالي، بعيد: يعترضه
  local aim = tp + off * blend

  local dt = math.min(now - T.lastT, 0.1)
  T.lastT = now
  local still = vel.Magnitude < 1.5
  if fast or still or not T.smooth or T.lastTr ~= tr then
    T.smooth = aim                                          -- لف / واقف / هدف جديد: مباشرة بدون تنعيم
  else
    T.smooth = T.smooth:Lerp(aim, math.clamp(14 * dt, 0, 1)) -- أسرع من الاسيست (6) عشان يلحق اللفّات
  end
  T.lastTr = tr
  setDrive(T.smooth, "track")
end

-- ================= الحلقة الرئيسية =================
local nextFilterAt = 0
keep(RunService.Heartbeat:Connect(function()
  if not alive() then return end
  local now = os.clock()
  local char = lp.Character
  local hum = char and char:FindFirstChildOfClass("Humanoid")
  local root = char and char:FindFirstChild("HumanoidRootPart")
  if not hum or not root or hum.Health <= 0 then clearDrive(); return end
  if root.Anchored then clearDrive(); assistReset(); grabReset(); return end -- برا القيم

  if now >= nextFilterAt then nextFilterAt = now + 1; pcall(refreshFilter) end

  local hasTool = false
  for _, it in ipairs(char:GetChildren()) do
    if it:IsA("Tool") then hasTool = true; break end
  end

  if hasTool then
    grabReset()
    if ST.track then
      -- 🧭 autoTrack: ماسك القنبلة → يلحق الخصم ويعطيه إياها (أحسن من الاسيست)
      assistReset()
      trackStep(char, hum, root, now)
    elseif ST.assist then
      trackReset()
      assistStep(char, hum, root, now)   -- التوقف عند اللمس يتحكم فيه محرك الحركة
    else
      assistReset(); trackReset(); clearDrive()
    end
  else
    assistReset(); trackReset()
    if ST.grab then
      grabStep(char, hum, root, now)
    else
      clearDrive()
    end
  end
end))


-- ================= 🎃 الواجهة (هالوين) =================
local UI = {}
do
  local function mk(class, props, parent)
    local o = Instance.new(class)
    for k, v in pairs(props) do o[k] = v end
    if parent then o.Parent = parent end
    return o
  end
  local function corner(o, r) return mk("UICorner", {CornerRadius = UDim.new(0, r)}, o) end
  local function stroke(o, col, th, tr) return mk("UIStroke", {Color = col, Thickness = th, Transparency = tr}, o) end
  local function tw(o, t, props) TweenService:Create(o, TweenInfo.new(t), props):Play() end

  local gui = mk("ScreenGui", {Name = randomName(), ResetOnSpawn = false, IgnoreGuiInset = true,
    ZIndexBehavior = Enum.ZIndexBehavior.Sibling, DisplayOrder = 100})
  if syn and typeof(syn.protect_gui) == "function" then pcall(syn.protect_gui, gui) end
  gui.Parent = getGuiParent()
  guis[#guis + 1] = gui

  -- زر القرعة العايم
  local pump = mk("TextButton", {Name = randomName(), Size = UDim2.fromOffset(46, 46),
    Position = UDim2.new(0, 12, 0.3, 0), BackgroundColor3 = C.bg, BackgroundTransparency = 0.05,
    Text = "🎃", TextSize = 26, Font = Enum.Font.GothamBold, AutoButtonColor = false,
    Active = true, Draggable = true}, gui)
  corner(pump, 23)
  local pumpStroke = stroke(pump, C.orange, 2, 0.1)

  local W, H = 300, 448
  local panel = mk("Frame", {Name = randomName(), Size = UDim2.fromOffset(W, H),
    Position = UDim2.new(0.5, -W / 2, 0.5, -H / 2), BackgroundColor3 = C.bg, BorderSizePixel = 0,
    Visible = false, ClipsDescendants = true, Active = true, Draggable = true}, gui)
  corner(panel, 16)
  local panelStroke = stroke(panel, C.orange, 2, 0.35)
  mk("UIGradient", {Rotation = 90, Color = ColorSequence.new({
    ColorSequenceKeypoint.new(0, C.purple2), ColorSequenceKeypoint.new(0.4, C.bg),
    ColorSequenceKeypoint.new(1, Color3.fromRGB(6, 3, 10))})}, panel)

  -- ── الزينة ──
  local decor = mk("Frame", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, ZIndex = 1, ClipsDescendants = true}, panel)
  local function dtext(txt, size, x, y, tr)
    return mk("TextLabel", {BackgroundTransparency = 1, Text = txt, TextSize = size, Font = Enum.Font.GothamBold,
      AnchorPoint = Vector2.new(0.5, 0.5), Position = UDim2.fromScale(x, y),
      Size = UDim2.fromOffset(size + 8, size + 8), TextTransparency = tr or 0, ZIndex = 1}, decor)
  end
  local moon = mk("Frame", {AnchorPoint = Vector2.new(0.5, 0.5), Size = UDim2.fromOffset(56, 56),
    Position = UDim2.fromScale(0.83, 0.2), BackgroundColor3 = Color3.fromRGB(255, 222, 150),
    BackgroundTransparency = 0.35, BorderSizePixel = 0, ZIndex = 1}, decor)
  corner(moon, 28); stroke(moon, C.orange, 4, 0.65)
  for _, cr in ipairs({{0.3, 0.35, 14}, {0.65, 0.6, 10}, {0.4, 0.72, 8}}) do
    local c = mk("Frame", {AnchorPoint = Vector2.new(0.5, 0.5), Size = UDim2.fromOffset(cr[3], cr[3]),
      Position = UDim2.fromScale(cr[1], cr[2]), BackgroundColor3 = Color3.fromRGB(235, 190, 110),
      BackgroundTransparency = 0.5, BorderSizePixel = 0, ZIndex = 1}, moon)
    corner(c, cr[3] / 2)
  end
  local bats = {}
  for i = 1, 3 do
    bats[i] = {o = dtext("🦇", 16 + i * 3, 0, 0.1, 0.2), sp = 0.05 + i * 0.02, ph = i * 0.37, y = 0.07 + i * 0.06}
  end
  dtext("🕸", 46, 0.07, 0.05, 0.3)
  local thread = mk("Frame", {BackgroundColor3 = C.dim, BackgroundTransparency = 0.4, BorderSizePixel = 0,
    Size = UDim2.fromOffset(1, 40), Position = UDim2.new(0.62, 0, 0, 0), ZIndex = 1}, decor)
  local spider = dtext("🕷", 20, 0.62, 0, 0)
  local ghosts = {dtext("👻", 26, 0.12, 0.92, 0.35), dtext("👻", 20, 0.9, 0.84, 0.5)}
  local candy = {dtext("🍬", 18, 0.93, 0.5, 0.35), dtext("🍭", 18, 0.05, 0.55, 0.35)}
  local pumpkins = {dtext("🎃", 22, 0.9, 0.965, 0.4), dtext("🎃", 16, 0.42, 0.968, 0.55)}
  local titleGrad

  -- 🩸 دم ينقط من فوق
  local drips = {}
  for i = 1, 7 do
    local d = mk("Frame", {BackgroundColor3 = C.blood, BackgroundTransparency = 0.12, BorderSizePixel = 0, ZIndex = 1,
      Size = UDim2.fromOffset(4, 10), Position = UDim2.new(0.06 + (i - 1) * 0.145, 0, 0, 0)}, decor)
    corner(d, 2)
    local tip = mk("Frame", {AnchorPoint = Vector2.new(0.5, 0), BackgroundColor3 = C.blood, BackgroundTransparency = 0.12,
      BorderSizePixel = 0, ZIndex = 1, Size = UDim2.fromOffset(8, 8), Position = UDim2.new(0.5, 0, 1, -3)}, d)
    corner(tip, 4)
    drips[i] = {o = d, base = 6 + (i * 7) % 14, ph = i * 0.9, sp = 0.5 + (i % 3) * 0.22}
  end

  -- 🌫 ضباب يمشي تحت
  local fog = {}
  for i = 1, 2 do
    local f = mk("Frame", {AnchorPoint = Vector2.new(0, 0.5), Size = UDim2.fromScale(0.9, 0.14),
      Position = UDim2.fromScale(-0.4, 0.8 + i * 0.07), BackgroundColor3 = Color3.fromRGB(190, 160, 235),
      BackgroundTransparency = 0.88, BorderSizePixel = 0, ZIndex = 1}, decor)
    corner(f, 40)
    mk("UIGradient", {Transparency = NumberSequence.new({NumberSequenceKeypoint.new(0, 1),
      NumberSequenceKeypoint.new(0.5, 0.25), NumberSequenceKeypoint.new(1, 1)})}, f)
    fog[i] = {o = f, sp = 0.02 + i * 0.012, ph = i * 0.5, y = 0.8 + i * 0.07}
  end

  -- ⚡ برق خفيف كل كم ثانية
  local flash = mk("Frame", {Size = UDim2.fromScale(1, 1), BackgroundColor3 = Color3.fromRGB(225, 200, 255),
    BackgroundTransparency = 1, BorderSizePixel = 0, ZIndex = 20, Active = false}, panel)
  corner(flash, 16)
  local nextFlash = os.clock() + 6

  task.spawn(function()
    while alive() and gui.Parent do
      local t = os.clock()
      pumpStroke.Transparency = 0.25 + 0.25 * math.sin(t * 3)
      pump.Rotation = math.sin(t * 2) * 7
      if panel.Visible then
        panelStroke.Transparency = 0.3 + 0.2 * math.sin(t * 2.2)
        for i, b in ipairs(bats) do
          b.o.Position = UDim2.new(((t * b.sp + b.ph) % 1.3) - 0.15, 0, b.y + 0.02 * math.sin(t * 4 + i), 0)
          b.o.Rotation = math.sin(t * 9 + i) * 12
        end
        local L = 34 + 18 * math.sin(t * 1.4)
        thread.Size = UDim2.fromOffset(1, L)
        spider.Position = UDim2.new(0.62, 0, 0, L + 8)
        for i, g in ipairs(ghosts) do
          g.Position = UDim2.new(g.Position.X.Scale, 0, 0.9 - 0.04 * i + 0.02 * math.sin(t * 1.6 + i), 0)
          g.TextTransparency = 0.4 + 0.2 * math.sin(t * 2 + i)
        end
        for i, c in ipairs(candy) do c.Rotation = math.sin(t * 1.3 + i) * 14 end
        for i, pk in ipairs(pumpkins) do
          pk.Rotation = math.sin(t * 1.8 + i * 2) * 10
          pk.Position = UDim2.new(pk.Position.X.Scale, 0, 0.965 + 0.006 * math.sin(t * 2.4 + i), 0)
        end
        for _, d in ipairs(drips) do
          d.o.Size = UDim2.fromOffset(4, d.base + 9 * (0.5 + 0.5 * math.sin(t * d.sp + d.ph)))
        end
        for i, f in ipairs(fog) do
          f.o.Position = UDim2.new(((t * f.sp + f.ph) % 1.5) - 0.5, 0, f.y, 0)
        end
        if titleGrad then titleGrad.Offset = Vector2.new(math.sin(t * 1.6) * 0.35, 0) end
        if t >= nextFlash then
          nextFlash = t + math.random(7, 15)
          task.spawn(function()
            for _ = 1, 2 do
              flash.BackgroundTransparency = 0.8
              task.wait(0.05)
              flash.BackgroundTransparency = 1
              task.wait(0.08)
            end
          end)
        end
      end
      task.wait(0.04)
    end
  end)

  -- ── المحتوى ──
  local top = mk("Frame", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, ZIndex = 2}, panel)
  local title = mk("TextLabel", {Size = UDim2.new(1, -50, 0, 22), Position = UDim2.fromOffset(14, 6),
    BackgroundTransparency = 1, Text = "🎃 ASTA  HALLOWEEN", TextColor3 = Color3.new(1, 1, 1), TextSize = 17,
    Font = Enum.Font.GothamBlack, TextXAlignment = Enum.TextXAlignment.Left}, top)
  titleGrad = mk("UIGradient", {Color = ColorSequence.new(C.orange2, C.purple)}, title)
  mk("TextLabel", {Size = UDim2.new(1, -50, 0, 12), Position = UDim2.fromOffset(14, 27), BackgroundTransparency = 1,
    Text = "Devices  •  Features   v7", TextColor3 = C.dim, TextSize = 10, Font = Enum.Font.Gotham,
    TextXAlignment = Enum.TextXAlignment.Left}, top)
  local closeBtn = mk("TextButton", {Size = UDim2.fromOffset(28, 28), Position = UDim2.new(1, -34, 0, 6),
    BackgroundTransparency = 1, Text = "×", TextColor3 = C.text, TextSize = 22, Font = Enum.Font.GothamMedium}, top)

  local tabBar = mk("Frame", {Size = UDim2.new(1, -24, 0, 30), Position = UDim2.fromOffset(12, 48), BackgroundTransparency = 1}, top)
  mk("UIListLayout", {FillDirection = Enum.FillDirection.Horizontal, Padding = UDim.new(0, 6), SortOrder = Enum.SortOrder.LayoutOrder}, tabBar)
  local function makeTab(txt, order)
    local b = mk("TextButton", {Size = UDim2.new(0.5, -3, 1, 0), BackgroundColor3 = C.card, BackgroundTransparency = 0.2,
      Text = txt, TextColor3 = C.dim, TextSize = 13, Font = Enum.Font.GothamBold, AutoButtonColor = false, LayoutOrder = order}, tabBar)
    corner(b, 9)
    return b
  end
  local tabDev = makeTab("📱  الأجهزة", 1)
  local tabFeat = makeTab("🎃  المميزات", 2)

  local content = mk("Frame", {Position = UDim2.fromOffset(12, 86), Size = UDim2.new(1, -24, 1, -118), BackgroundTransparency = 1}, top)
  mk("TextLabel", {Size = UDim2.new(1, -24, 0, 16), Position = UDim2.new(0, 12, 1, -26), BackgroundTransparency = 1,
    Text = BRAND .. "  •  🕸 Happy Halloween 🕸", TextColor3 = C.dim, TextSize = 10, Font = Enum.Font.Gotham}, top)

  local devPage = mk("Frame", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, Visible = false}, content)
  local feat = mk("ScrollingFrame", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, BorderSizePixel = 0,
    ScrollBarThickness = 3, ScrollBarImageColor3 = C.orange, CanvasSize = UDim2.new(),
    AutomaticCanvasSize = Enum.AutomaticSize.Y, Visible = true}, content)
  mk("UIListLayout", {Padding = UDim.new(0, 6), SortOrder = Enum.SortOrder.LayoutOrder,
    HorizontalAlignment = Enum.HorizontalAlignment.Right}, feat)

  local function setTab(name)
    local f = name == "Feat"
    devPage.Visible = not f
    feat.Visible = f
    tw(tabFeat, 0.12, {BackgroundColor3 = f and C.orange or C.card, TextColor3 = f and Color3.fromRGB(25, 10, 0) or C.dim})
    tw(tabDev, 0.12, {BackgroundColor3 = (not f) and C.orange or C.card, TextColor3 = (not f) and Color3.fromRGB(25, 10, 0) or C.dim})
  end
  tabDev.MouseButton1Click:Connect(function() setTab("Dev") end)
  tabFeat.MouseButton1Click:Connect(function() setTab("Feat") end)
  setTab("Feat")

  -- ── صف تفعيل (سويتش) ──
  local onChangeHooks = {}
  local function toggleRow(order, title, sub, key, indent)
    local h = indent and 44 or 54
    local row = mk("TextButton", {Size = UDim2.new(1, -8 - (indent and 18 or 0), 0, h), BackgroundColor3 = C.card,
      BackgroundTransparency = 0.15, Text = "", AutoButtonColor = false, LayoutOrder = order}, feat)
    corner(row, 10)
    local rs = stroke(row, C.orange, 1.2, 0.8)
    mk("TextLabel", {Size = UDim2.new(1, -64, 0, 18), Position = UDim2.fromOffset(10, indent and 5 or 7), BackgroundTransparency = 1,
      Text = title, TextColor3 = C.text, TextSize = indent and 12 or 14, Font = Enum.Font.GothamBold,
      TextXAlignment = Enum.TextXAlignment.Left, TextTruncate = Enum.TextTruncate.AtEnd}, row)
    mk("TextLabel", {Size = UDim2.new(1, -64, 0, 14), Position = UDim2.fromOffset(10, indent and 24 or 28), BackgroundTransparency = 1,
      Text = sub, TextColor3 = C.dim, TextSize = 10, Font = Enum.Font.Gotham,
      TextXAlignment = Enum.TextXAlignment.Left, TextTruncate = Enum.TextTruncate.AtEnd}, row)
    local pill = mk("Frame", {Size = UDim2.fromOffset(42, 22), Position = UDim2.new(1, -52, 0.5, -11), BackgroundColor3 = C.off, BorderSizePixel = 0}, row)
    corner(pill, 11)
    local knob = mk("TextLabel", {Size = UDim2.fromOffset(20, 20), Position = UDim2.new(0, 1, 0.5, -10), BackgroundTransparency = 1,
      Text = "💀", TextSize = 15, Font = Enum.Font.GothamBold, ZIndex = 3}, pill)
    local function render()
      local on = ST[key]
      knob.Text = on and "🎃" or "💀"
      tw(pill, 0.14, {BackgroundColor3 = on and C.orange or C.off})
      tw(knob, 0.14, {Position = on and UDim2.new(1, -21, 0.5, -10) or UDim2.new(0, 1, 0.5, -10)})
      tw(rs, 0.14, {Transparency = on and 0.25 or 0.8})
    end
    row.MouseButton1Click:Connect(function()
      ST[key] = not ST[key]
      render()
      if onChangeHooks[key] then pcall(onChangeHooks[key], ST[key]) end
    end)
    render()
  end

  toggleRow(1, "🎃  الاسيست", "يلحق الخصم وانت ماسك القنبلة ويوقف قريب منه", "assist", false)
  toggleRow(2, "👻  اوتو قراب", "داخل القيم بس: تشيل يدك → يروح للماسك وياخذ القنبلة", "grab", false)
  toggleRow(3, "🦇  رادار الخصوم", "قائمة المسافات + تنبيه لو عدو قريب", "radar", false)
  toggleRow(4, "🧭  autoTrack", "ماسك القنبلة: يلحق الخصم ويعطيه إياها ويوقف على 2.3 studs (أحسن من الاسيست)", "track", false)

  local function sectionLabel(order, txt)
    return mk("TextLabel", {Size = UDim2.new(1, -8, 0, 20), BackgroundTransparency = 1, Text = txt, TextColor3 = C.orange2,
      TextSize = 13, Font = Enum.Font.GothamBold, TextXAlignment = Enum.TextXAlignment.Left, LayoutOrder = order}, feat)
  end
  local radarTitle = sectionLabel(10, "🦇 الرادار")
  radarTitle.Visible = false
  local radarHolder = mk("Frame", {Size = UDim2.new(1, -8, 0, 0), AutomaticSize = Enum.AutomaticSize.Y,
    BackgroundTransparency = 1, LayoutOrder = 11, Visible = false}, feat)
  mk("UIListLayout", {Padding = UDim.new(0, 3), SortOrder = Enum.SortOrder.LayoutOrder}, radarHolder)
  sectionLabel(20, "🎯 اختار الهدف  (حتى " .. CFG.MAX_LOCKED .. ")")
  local targetHolder = mk("Frame", {Size = UDim2.new(1, -8, 0, 0), AutomaticSize = Enum.AutomaticSize.Y,
    BackgroundTransparency = 1, LayoutOrder = 21}, feat)
  mk("UIListLayout", {Padding = UDim.new(0, 4), SortOrder = Enum.SortOrder.LayoutOrder}, targetHolder)

  onChangeHooks.radar = function(on)
    radarTitle.Visible = on
    radarHolder.Visible = on
    if not on then UI.setAlert(math.huge) end
  end

  -- ── الرادار + التنبيه ──
  local rrows = {}
  for i = 1, MAX_ENEMIES do
    local f = mk("Frame", {Size = UDim2.new(1, 0, 0, 28), BackgroundColor3 = C.card, BackgroundTransparency = 0.25,
      BorderSizePixel = 0, LayoutOrder = i, Visible = false}, radarHolder)
    corner(f, 8)
    local n = mk("TextLabel", {Size = UDim2.new(0.65, 0, 1, 0), Position = UDim2.fromOffset(10, 0), BackgroundTransparency = 1,
      TextColor3 = C.text, TextSize = 12, Font = Enum.Font.GothamMedium, TextXAlignment = Enum.TextXAlignment.Left,
      TextTruncate = Enum.TextTruncate.AtEnd, Text = ""}, f)
    local d = mk("TextLabel", {Size = UDim2.new(0.35, -10, 1, 0), Position = UDim2.new(0.65, 0, 0, 0), BackgroundTransparency = 1,
      TextColor3 = C.orange2, TextSize = 12, Font = Enum.Font.GothamBold, TextXAlignment = Enum.TextXAlignment.Right, Text = ""}, f)
    rrows[i] = {f = f, n = n, d = d}
  end
  function UI.setRadar(entries)
    for i = 1, MAX_ENEMIES do
      local r, e = rrows[i], entries[i]
      if e then
        local dd = math.floor(e.Dist)
        r.f.Visible = true
        r.n.Text = e.Name
        r.d.Text = dd .. " 🎯"
        if dd < ALERT_DIST then
          r.f.BackgroundColor3 = Color3.fromRGB(120, 18, 28); r.d.TextColor3 = Color3.fromRGB(255, 90, 90)
        elseif dd < WARN_DIST then
          r.f.BackgroundColor3 = Color3.fromRGB(100, 55, 10); r.d.TextColor3 = C.orange2
        else
          r.f.BackgroundColor3 = C.card; r.d.TextColor3 = C.slime
        end
      else
        r.f.Visible = false
      end
    end
  end
  local alertF = mk("Frame", {Size = UDim2.new(1, 0, 0, 40), BackgroundColor3 = C.blood, BackgroundTransparency = 0.2,
    BorderSizePixel = 0, Visible = false, ZIndex = 50}, gui)
  local alertT = mk("TextLabel", {Size = UDim2.fromScale(1, 1), BackgroundTransparency = 1, TextColor3 = Color3.new(1, 1, 1),
    TextSize = 14, Font = Enum.Font.GothamBold, Text = "", ZIndex = 51}, alertF)
  function UI.setAlert(closest)
    if ST.radar and closest < ALERT_DIST then
      alertT.Text = "☠ عدو قريب — " .. math.floor(closest) .. " studs"
      alertF.Visible = true
    else
      alertF.Visible = false
    end
  end

  -- ── قائمة الأهداف ──
  local btns, lastSig = {}, ""
  -- 🔴 علامة العدو (هايلايت/بوكس أحمر) — احتياط بس
  local function isRedColor(c) return c ~= nil and c.R > 0.6 and c.R > c.G * 1.8 and c.R > c.B * 1.8 end
  local function hasRedMark(p)
    local red = false
    pcall(function()
      local ch = p.Character
      if not ch then return end
      for _, d in ipairs(ch:GetDescendants()) do
        if d:IsA("Highlight") then
          if isRedColor(d.FillColor) or isRedColor(d.OutlineColor) then red = true; break end
        elseif d:IsA("SelectionBox") or d:IsA("SelectionSphere") then
          if isRedColor(d.Color3) then red = true; break end
        end
      end
    end)
    return red
  end
  local function isMate(p)
    local ok, res = pcall(function()
      if isTeammate(p) then return true end
      if isGreenTeammate and isGreenTeammate(p) then return true end
      return false
    end)
    return ok and res or false
  end
  local function distTo(p)
    local ok, d = pcall(function()
      local a = lp.Character and lp.Character:FindFirstChild("HumanoidRootPart")
      local b = p.Character and p.Character:FindFirstChild("HumanoidRootPart")
      if a and b then return (a.Position - b.Position).Magnitude end
      return math.huge
    end)
    return ok and d or math.huge
  end

  -- 🧩 نقرا لاعبين القيم من الواجهة اللي فوق (صور اللاعبين يمين ويسار الـ "0 - 0")
  local function playerFromGui(d)
    local function tryStr(str)
      if type(str) ~= "string" or str == "" then return nil end
      for num in str:gmatch("%d+") do
        if #num >= 4 then
          local ok, p = pcall(function() return players:GetPlayerByUserId(tonumber(num)) end)
          if ok and p then return p end
        end
      end
      local p = players:FindFirstChild(str)
      if p and p:IsA("Player") then return p end
    end
    local cur = d
    for _ = 1, 3 do
      if not cur then break end
      local p
      if cur:IsA("ImageLabel") or cur:IsA("ImageButton") then p = tryStr(cur.Image) end
      p = p or tryStr(cur.Name)
      if p then return p end
      cur = cur.Parent
    end
  end
  local hudGroups, hudAt = nil, 0
  local function parseMatchHud()
    local now = os.clock()
    if now - hudAt < 1 then return hudGroups end
    hudAt = now
    hudGroups = nil
    pcall(function()
      local pg = lp:FindFirstChild("PlayerGui")
      if not pg then return end
      local score
      for _, d in ipairs(pg:GetDescendants()) do
        if d:IsA("TextLabel") and #d.Text <= 9 and d.Text:match("^%s*%d+%s*%-%s*%d+%s*$") and reallyVisible(d) then score = d; break end
      end
      if not score then return end
      local cx = score.AbsolutePosition.X + score.AbsoluteSize.X / 2
      local cont, left, right = score.Parent, {}, {}
      for _ = 1, 6 do
        if not cont or cont == pg then break end
        left, right = {}, {}
        for _, d in ipairs(cont:GetDescendants()) do
          if d:IsA("ImageLabel") or d:IsA("ImageButton") then
            local p = playerFromGui(d)
            if p then
              local x = d.AbsolutePosition.X + d.AbsoluteSize.X / 2
              if x < cx then left[p] = true else right[p] = true end
            end
          end
        end
        if next(left) and next(right) then break end
        cont = cont.Parent
      end
      if not (next(left) and next(right)) then return end
      local mine, enemy
      if left[lp] then mine, enemy = left, right
      elseif right[lp] then mine, enemy = right, left
      else
        -- انا مو بالصور: اللي فيهم أخضر (تيمي) هم جهتي
        local lm, rm = 0, 0
        for p in pairs(left) do if isMate(p) then lm = lm + 1 end end
        for p in pairs(right) do if isMate(p) then rm = rm + 1 end end
        if lm >= rm then mine, enemy = left, right else mine, enemy = right, left end
      end
      hudGroups = {mine = mine, enemy = enemy}
    end)
    return hudGroups
  end

  -- يرجع (الأعداء، فريقي، باقي اللاعبين اللي مو في القيم)
  local function splitPlayers()
    local en, mates, others = {}, {}, {}
    local g = parseMatchHud()
    local inHud = scoreHud()
    for _, p in ipairs(players:GetPlayers()) do
      if p ~= lp then
        if g then
          if g.enemy[p] then en[#en + 1] = p
          elseif g.mine[p] then mates[#mates + 1] = p
          else others[#others + 1] = p end
        elseif inHud then
          -- ما قدرنا نقرا الصور: احتياط (علامة حمراء + قريب منك)
          local near = distTo(p) <= (CFG.MATCH_RANGE or 150)
          if near and isMate(p) then mates[#mates + 1] = p
          elseif near and hasRedMark(p) then en[#en + 1] = p
          else others[#others + 1] = p end
        else
          others[#others + 1] = p                        -- لوبي: الكل بالقائمة العادية
        end
      end
    end
    local byName = function(a, b) return a.Name:lower() < b.Name:lower() end
    table.sort(en, byName); table.sort(mates, byName); table.sort(others, byName)
    return en, mates, others
  end
  local function signature()
    local en, mates, others = splitPlayers()
    local t = {}
    for _, p in ipairs(en) do t[#t + 1] = "E:" .. p.Name end
    for _, p in ipairs(mates) do t[#t + 1] = "M:" .. p.Name end
    for _, p in ipairs(others) do t[#t + 1] = "O:" .. p.Name end
    return table.concat(t, ",") .. "|" .. table.concat(ST.locked, ",")
  end
  function UI.rebuild(force)
    local s = signature()
    if s == lastSig and not force then return end
    lastSig = s
    for _, b in ipairs(btns) do b:Destroy() end
    btns = {}
    local order, count = 0, #ST.locked
    local en, mates, others = splitPlayers()
    local function header(txt, color)
      order = order + 1
      local h = mk("TextLabel", {Size = UDim2.new(1, 0, 0, 22), LayoutOrder = order, BackgroundTransparency = 1,
        TextColor3 = color, TextSize = 12, Font = Enum.Font.GothamBold, TextXAlignment = Enum.TextXAlignment.Left,
        Text = txt}, targetHolder)
      btns[#btns + 1] = h
    end
    local allB = mk("TextButton", {Size = UDim2.new(1, 0, 0, 32), LayoutOrder = order, BorderSizePixel = 0, AutoButtonColor = false,
      BackgroundColor3 = count == 0 and C.purple or C.card, TextColor3 = C.text, TextSize = 13, Font = Enum.Font.GothamBold,
      Text = count == 0 and "🌐 الكل (أقرب)" or ("🌐 الكل  |  مختار: " .. count .. "/" .. CFG.MAX_LOCKED)}, targetHolder)
    corner(allB, 8)
    btns[#btns + 1] = allB
    allB.MouseButton1Click:Connect(function() table.clear(ST.locked); UI.rebuild(true) end)

    -- kind: "enemy" أحمر | "mate" أصفر (داخلين معك القيم) | "other" عادي
    local function addPlayer(p, kind)
      order = order + 1
      local idx
      for i, n in ipairs(ST.locked) do if n == p.Name then idx = i; break end end
      local atMax = #ST.locked >= CFG.MAX_LOCKED
      local nm = "@" .. p.Name .. (p.DisplayName ~= p.Name and ("  (" .. p.DisplayName .. ")") or "")
      local base = kind == "enemy" and Color3.fromRGB(150, 28, 40)
        or kind == "mate" and Color3.fromRGB(150, 118, 12)
        or Color3.fromRGB(58, 34, 92)
      local icon = kind == "enemy" and "☠ " or kind == "mate" and "🟡 " or "🎯 "
      local b = mk("TextButton", {Size = UDim2.new(1, 0, 0, 32), LayoutOrder = order, BorderSizePixel = 0, AutoButtonColor = false,
        BackgroundColor3 = idx and C.blood or (atMax and Color3.fromRGB(48, 40, 60) or base),
        TextColor3 = C.text, TextSize = 13, Font = Enum.Font.GothamBold, TextTruncate = Enum.TextTruncate.AtEnd,
        Text = (idx and ("🔒" .. idx .. " ") or icon) .. nm}, targetHolder)
      corner(b, 8)
      btns[#btns + 1] = b
      local pName = p.Name
      b.MouseButton1Click:Connect(function()
        local at
        for i, n in ipairs(ST.locked) do if n == pName then at = i; break end end
        if at then table.remove(ST.locked, at)
        elseif #ST.locked < CFG.MAX_LOCKED then table.insert(ST.locked, pName) end
        UI.rebuild(true)
      end)
    end

    if #en > 0 then
      header("⚔️ الفريق الي ضدك (" .. #en .. ")", Color3.fromRGB(255, 90, 90))
      for _, p in ipairs(en) do addPlayer(p, "enemy") end
    end
    if #mates > 0 then
      header("🟡 فريقك — داخلين معك القيم (" .. #mates .. ")", Color3.fromRGB(255, 214, 64))
      for _, p in ipairs(mates) do addPlayer(p, "mate") end
    end
    if #others > 0 then
      header(((#en + #mates) > 0 and "👥 باقي اللاعبين (مو في القيم) (" or "👥 اللاعبين (") .. #others .. ")", C.dim)
      for _, p in ipairs(others) do addPlayer(p, "other") end
    end
  end
  keep(Players.PlayerAdded:Connect(function() task.defer(UI.rebuild) end))
  keep(Players.PlayerRemoving:Connect(function() task.defer(UI.rebuild) end))
  task.spawn(function()
    while alive() and gui.Parent do
      if panel.Visible then pcall(UI.rebuild) end
      task.wait(1)
    end
  end)

  -- ── تبويب الأجهزة ──
  local targetDevice, pendingDevice = getTargetDevice(), nil
  local rows = {}
  mk("UIListLayout", {Padding = UDim.new(0, 8), SortOrder = Enum.SortOrder.LayoutOrder}, devPage)
  local function refreshButtons()
    for name, r in pairs(rows) do
      if name == pendingDevice then
        tw(r.Btn, 0.15, {BackgroundColor3 = Color3.fromRGB(210, 100, 20)})
        r.Text.Text = "متأكد؟ اضغط مرة ثانية (يعيد الدخول)"
        r.Text.TextColor3 = Color3.new(1, 1, 1)
        tw(r.Stroke, 0.15, {Color = C.orange2, Transparency = 0.05})
      elseif name == targetDevice then
        tw(r.Btn, 0.15, {BackgroundColor3 = Color3.fromRGB(95, 45, 150)})
        r.Text.Text = (DISPLAY[name] or name) .. "   ✓ Active"
        r.Text.TextColor3 = Color3.fromRGB(235, 215, 255)
        tw(r.Stroke, 0.15, {Color = C.orange, Transparency = 0.05})
      else
        tw(r.Btn, 0.15, {BackgroundColor3 = C.card})
        r.Text.Text = DISPLAY[name] or name
        r.Text.TextColor3 = C.text
        tw(r.Stroke, 0.15, {Color = Color3.new(1, 1, 1), Transparency = 0.88})
      end
    end
  end

  local function rejoinAndApply(deviceName, label)
    targetDevice = deviceName
    setTargetDevice(deviceName)
    pendingDevice = nil
    label.Text = "Rejoining..."
    refreshButtons()
    label.Text = "Rejoining..."
    reapplyDevice()
    asta_queueReload()
    local finished, stage, conn = false, 1, nil
    local function applyInPlace()
      if finished then return end
      finished = true
      asta_hideTeleportError()
      label.Text = "Applied ✓"
      for i = 1, 10 do task.delay((i - 1) * 0.6, reapplyDevice) end
      task.delay(1.5, refreshButtons)
    end
    local function finish(result, msg)
      if conn then conn:Disconnect(); conn = nil end
      if result ~= nil or msg ~= nil then
        asta_notify("Rejoin failed: " .. tostring(result) .. " | " .. tostring(msg))
      end
      applyInPlace()
    end
    local function tryAsync()
      return pcall(function()
        local opts = Instance.new("TeleportOptions")
        opts.ServerInstanceId = game.JobId
        TeleportService:TeleportAsync(game.PlaceId, {lp}, opts)
      end)
    end
    conn = TeleportService.TeleportInitFailed:Connect(function(_, result, msg)
      if finished then return end
      asta_hideTeleportError()
      if stage == 1 then
        stage = 2
        task.spawn(function() if not tryAsync() then finish(result, msg) end end)
      else
        finish(result, msg)
      end
    end)
    local okTp = pcall(function() TeleportService:TeleportToPlaceInstance(game.PlaceId, game.JobId, lp) end)
    if not okTp then
      stage = 2
      task.spawn(function() if not tryAsync() then finish("pcall", "teleport api error") end end)
    end
    task.delay(10, function() if not finished then finish() end end)
  end

  for order, name in ipairs({"Console", "Mobile", "PC"}) do
    local btn = mk("TextButton", {Size = UDim2.new(1, 0, 0, 50), BackgroundColor3 = C.card, BackgroundTransparency = 0.15,
      Text = "", AutoButtonColor = false, LayoutOrder = order}, devPage)
    corner(btn, 10)
    local st = stroke(btn, Color3.new(1, 1, 1), 1.4, 0.88)
    local label = mk("TextLabel", {Size = UDim2.new(1, -20, 1, 0), Position = UDim2.fromOffset(12, 0), BackgroundTransparency = 1,
      Text = DISPLAY[name], TextColor3 = C.text, TextSize = 14, Font = Enum.Font.GothamBold,
      TextXAlignment = Enum.TextXAlignment.Left}, btn)
    rows[name] = {Btn = btn, Stroke = st, Text = label}
    btn.MouseButton1Click:Connect(function()
      if targetDevice == name then return end
      if pendingDevice == name then
        rejoinAndApply(name, label)
      else
        pendingDevice = name
        refreshButtons()
      end
    end)
  end
  mk("TextLabel", {Size = UDim2.new(1, 0, 0, 40), LayoutOrder = 10, BackgroundTransparency = 1, TextWrapped = true,
    Text = "🕸 اضغط على الجهاز مرتين للتأكيد — اللعبة تعيد الدخول وتطبّق الجهاز تلقائي كل مرة تدخل.",
    TextColor3 = C.dim, TextSize = 11, Font = Enum.Font.Gotham}, devPage)
  refreshButtons()

  -- ── فتح/إغلاق + ضغطتين على التُرس ──
  local scale = mk("UIScale", {Scale = 1}, panel)
  local panelOpen = false
  local function openPanel()
    panelOpen = true
    scale.Scale = 0.9
    panel.Visible = true
    TweenService:Create(scale, TweenInfo.new(0.18, Enum.EasingStyle.Back, Enum.EasingDirection.Out), {Scale = 1}):Play()
    pcall(UI.rebuild, true)
  end
  local function closePanel()
    panelOpen = false
    pendingDevice = nil
    refreshButtons()
    local t = TweenService:Create(scale, TweenInfo.new(0.12), {Scale = 0.9})
    t:Play()
    t.Completed:Once(function() if not panelOpen then panel.Visible = false end end)
  end
  pump.MouseButton1Click:Connect(function() if panelOpen then closePanel() else openPanel() end end)
  closeBtn.MouseButton1Click:Connect(closePanel)

  local function inFrame(pos, fr)
    if not (fr and fr.Parent and fr.Visible) then return false end
    local inset = guiService:GetGuiInset()
    local p, s = fr.AbsolutePosition, fr.AbsoluteSize
    for _, q in ipairs({pos, pos + inset}) do
      if q.X >= p.X and q.X <= p.X + s.X and q.Y >= p.Y and q.Y <= p.Y + s.Y then return true end
    end
    return false
  end
  local function findGear()
    for _, d in ipairs(playerGui:GetDescendants()) do
      if d:IsA("GuiButton") and d.Visible and d.AbsoluteSize.X > 0 and not d:IsDescendantOf(gui) then
        local n = d.Name:lower()
        if n:find("setting") or n:find("gear") then return d end
      end
    end
  end
  local function inGearArea(pos)
    local gear = findGear()
    if gear then return inFrame(pos, gear) end
    local v = workspace.CurrentCamera.ViewportSize
    local g = GEAR_FALLBACK
    return pos.X >= v.X * g.x0 and pos.X <= v.X * g.x1 and pos.Y >= v.Y * g.y0 and pos.Y <= v.Y * g.y1
  end
  uiBlock = function(pos) return inFrame(pos, panel) or inFrame(pos, pump) or inGearArea(pos) end

  local lastTap = 0
  keep(UIS.InputBegan:Connect(function(input)
    if input.UserInputType ~= Enum.UserInputType.Touch and input.UserInputType ~= Enum.UserInputType.MouseButton1 then return end
    local pos = Vector2.new(input.Position.X, input.Position.Y)
    if not inGearArea(pos) then return end
    local now = os.clock()
    if now - lastTap <= CFG.DOUBLE_TAP then
      lastTap = 0
      if panelOpen then closePanel() else openPanel() end
    else
      lastTap = now
    end
  end))

  pcall(UI.rebuild, true)
  task.delay(0.5, function()
    asta_notify("🎃 ASTA Halloween جاهز — اضغط القرعة 🎃")
  end)
end

-- ================= 🦇 رادار + 🧭 autoTrack =================
task.spawn(function()
  local lastTrack = 0
  while alive() do
    task.wait(0.5)
    local char = lp.Character
    local myRoot = char and char:FindFirstChild("HumanoidRootPart")
    if not myRoot or not ST.radar then
      if not ST.radar then UI.setAlert(math.huge) end
      continue
    end
    local entries = {}
    for _, p in ipairs(players:GetPlayers()) do
      if p ~= lp and not isTeammate(p) then
        local r = p.Character and p.Character:FindFirstChild("HumanoidRootPart")
        if r then
          entries[#entries + 1] = {Name = p.DisplayName, Dist = (r.Position - myRoot.Position).Magnitude, Root = r}
        end
      end
    end
    table.sort(entries, function(a, b) return a.Dist < b.Dist end)

    if ST.radar then
      UI.setRadar(entries)
      UI.setAlert(entries[1] and entries[1].Dist or math.huge)
    end

  end
end)
]])

if chunk then
	chunk()

	return
end

warn("[Asta] " .. tostring(v2))

--!nonstrict
--[[============================================================================
    NatAov Hub — Auto Bounty (MODULE)
    ----------------------------------------------------------------------------
    Phiên bản module hóa & tối ưu:
      * Cấu trúc: Services / Executor / Config / Utils / State / World / UI /
        Notify / Move / Buff / Combat / Hunt / Hop / Webhook / Lifecycle
      * Lazy-cache service + remote, bỏ biến global tràn lan
      * Đa executor Mobile + PC (yếu → mạnh): Synapse X, Script-Ware, Fluxus,
        Electron, Wave, Delta, Krnl, Codex, Solara, Celery, Arceus X, Vega X,
        Hydrogen, X8... Tự nhận diện + kiểm tra năng lực thực tế.
      * FULL FEATURES cho cả Mobile & PC: aimbot dùng hook __namecall nếu có,
        dùng aim assist (xoay người về mục tiêu) nếu không hook được; combat
        luôn đầy đủ skill; webhook fallback PostAsync
      * Hitbox boost: mở rộng hitbox người chơi khác (Head/Torso/tay/chân)
        để dễ trúng, kết hợp aimbot → server xác nhận đòn hợp lệ; bọc pcall
      * Anti-Stun: chống choáng / ngã / khóa di chuyển (Ragdoll, FallingDown,
        PlatformStanding, Seated), tự chạy lại khi hồi sinh, bọc pcall
      * Safe Mode: máu dưới % → bay lên trời chờ hồi, máu đủ → bay xuống đánh
        tiếp (SafeHealth: Percent / HealPercent / FlyHeight)
      * FPS Boost triệt để: setfflag, đổi workspace thành đá xám, xóa effect/
        decal/light, tối ưu Lighting + ngoại hình nhân vật (bọc pcall)
      * Visual: Hide Map (transparency = 1, giữ người chơi hiện rõ, tự ẩn vật
        mới sinh, kể cả nil instances) + Black/White Screen overlay (bọc pcall)
      * Aim Prediction: tính vận tốc mục tiêu -> dự đoán vị trí tương lai
      * Spam Skill: Random / Sequence / LowHealth (bấm skill tự động)
      * Bypass TP thông minh (chỉ khi địch ở xa, không PvP, không hop)
      * Auto hunt thông minh: scoring ưu tiên mục tiêu (bounty/khoảng cách/
        cân bằng + máu thấp), cooldown chống spam, retarget nhanh khi mục tiêu
        chết, loại sớm mục tiêu safe-zone, tự hop sau N lần quét trống
      * Hết mục tiêu: bay lên cao liên tục, chờ hết in combat rồi mới hop
      * API: AutoBounty:Start() / AutoBounty:Stop() / AutoBounty:SetConfig(t)
             AutoBounty:GetState()
      * Theme xanh dương sáng — Brand: NatAov Hub

    Cách dùng trong executor:
        local AutoBounty = loadstring(game:HttpGet("URL_MODULE"))()
        AutoBounty:SetConfig({ Team = "Pirates", ... })
        AutoBounty:Start()
==============================================================================]]

local AutoBounty = {}
AutoBounty.Version = "1.0"

-- ============================================================================
-- 1) SERVICES — lazy cache tất cả GetService (tối ưu: chỉ GetService 1 lần)
-- ============================================================================
local Services = setmetatable({}, {
	__index = function(self, name)
		local ok, svc = pcall(function()
			return game:GetService(name)
		end)
		if ok and svc then
			self[name] = svc
			return svc
		end
		return nil
	end,
})

local Players = Services.Players
local RunService = Services.RunService
local TweenService = Services.TweenService
local UserInputService = Services.UserInputService
local HttpService = Services.HttpService
local TeleportService = Services.TeleportService
local CoreGui = Services.CoreGui
local Lighting = Services.Lighting
local VirtualUser = Services.VirtualUser
local ReplicatedStorage = Services.ReplicatedStorage

local Player = Players.LocalPlayer
local Camera = workspace.CurrentCamera

local Remotes = ReplicatedStorage:FindFirstChild("Remotes")
local CommF = Remotes and Remotes:FindFirstChild("CommF_")
local CommE = Remotes and Remotes:FindFirstChild("CommE")

-- 1b) EXECUTOR — hỗ trợ đa executor (Mobile + PC, từ yếu đến mạnh)
-- ============================================================================
local Executor = {
	Name = "Unknown",
	Platform = "PC",
	Strength = 0,
}

local EXECUTOR_DB = {
	["Synapse X"] = { strength = 100, platform = "PC" },
	["Script-Ware"] = { strength = 100, platform = "PC" },
	["ScriptWare"] = { strength = 100, platform = "PC" },
	["Fluxus"] = { strength = 90, platform = "PC" },
	["Fluxus Mobile"] = { strength = 70, platform = "Mobile" },
	["Electron"] = { strength = 90, platform = "PC" },
	["Wave"] = { strength = 90, platform = "PC" },
	["Wave Mobile"] = { strength = 55, platform = "Mobile" },
	["Delta"] = { strength = 90, platform = "PC" },
	["Delta Mobile"] = { strength = 70, platform = "Mobile" },
	["Krnl"] = { strength = 80, platform = "PC" },
	["Krnl Mobile"] = { strength = 55, platform = "Mobile" },
	["Codex"] = { strength = 80, platform = "PC" },
	["Codex Mobile"] = { strength = 55, platform = "Mobile" },
	["Solara"] = { strength = 80, platform = "PC" },
	["Celery"] = { strength = 80, platform = "PC" },
	["Oxygen U"] = { strength = 80, platform = "PC" },
	["Swift"] = { strength = 70, platform = "PC" },
	["Euler"] = { strength = 70, platform = "PC" },
	["Arceus X"] = { strength = 75, platform = "Mobile" },
	["Arceus X Neo"] = { strength = 80, platform = "Mobile" },
	["Vega X"] = { strength = 60, platform = "Mobile" },
	["Hydrogen"] = { strength = 50, platform = "Mobile" },
	["Hydrogen Mobile"] = { strength = 50, platform = "Mobile" },
	["X8"] = { strength = 50, platform = "Mobile" },
	["Nihon"] = { strength = 55, platform = "Mobile" },
	["Xeno"] = { strength = 40, platform = "PC" },
	["Rubeno"] = { strength = 40, platform = "PC" },
	["Mirage"] = { strength = 40, platform = "PC" },
	["Nebula"] = { strength = 40, platform = "PC" },
	["Sparx"] = { strength = 50, platform = "Mobile" },
	["Evon"] = { strength = 60, platform = "PC" },
	["Evon Mobile"] = { strength = 50, platform = "Mobile" },
	["Zophix"] = { strength = 60, platform = "PC" },
	["Aqua"] = { strength = 55, platform = "PC" },
	["Cryptic"] = { strength = 65, platform = "PC" },
	["Pluton"] = { strength = 60, platform = "PC" },
	["Redz"] = { strength = 60, platform = "PC" },
}

do
	pcall(function()
		if identifyexecutor then
			Executor.Name = tostring(identifyexecutor())
		end
	end)
	if Executor.Name == "Unknown" then
		local nameByGlobal = {
			syn = "Synapse X",
			fluxus = "Fluxus",
			delta = "Delta",
			hydrogen = "Hydrogen",
			krnl = "Krnl",
			scriptware = "Script-Ware",
			electron = "Electron",
			solara = "Solara",
			celery = "Celery",
			codex = "Codex",
			swift = "Swift",
			oxygenu = "Oxygen U",
			xeno = "Xeno",
			rubeno = "Rubeno",
			euler = "Euler",
			vega = "Vega X",
			x8 = "X8",
			nihon = "Nihon",
			sparx = "Sparx",
			evon = "Evon",
			zophix = "Zophix",
			aqua = "Aqua",
			cryptic = "Cryptic",
			pluton = "Pluton",
			redz = "Redz",
			wave = "Wave",
		}
		for gname, pretty in pairs(nameByGlobal) do
			if _G[gname] then
				Executor.Name = pretty
				break
			end
		end
		if Executor.Name == "Unknown" and script and script.Name:find("Arceus") then
			Executor.Name = "Arceus X"
		end
	end

	local db = EXECUTOR_DB[Executor.Name]
	if db then
		Executor.Strength = db.strength
		Executor.Platform = db.platform
	end

	local rawReqFn = nil
	pcall(function()
		rawReqFn = (syn and syn.request)
			or (http and http.request)
			or (fluxus and fluxus.request)
			or (krnl and krnl.request)
			or (typeof(request) == "function" and request)
			or (typeof(http_request) == "function" and http_request)
			or (getgenv and typeof(getgenv().request) == "function" and getgenv().request)
			or (getgenv and typeof(getgenv().http_request) == "function" and getgenv().http_request)
			or (getgenv and getgenv().syn and typeof(getgenv().syn.request) == "function" and getgenv().syn.request)
			or (getgenv and getgenv().http and typeof(getgenv().http.request) == "function" and getgenv().http.request)
			or (getgenv and getgenv().fluxus and typeof(getgenv().fluxus.request) == "function" and getgenv().fluxus.request)
	end)

	Executor.HasGetgenv = (getgenv ~= nil)
	Executor.HasRequest = (rawReqFn ~= nil)
	Executor.HasRawMetatable = (getrawmetatable ~= nil)
	Executor.HasNewCClosure = (newcclosure ~= nil)
	Executor.HasSetReadonly = (setreadonly ~= nil)
	Executor.HasGetNamecallMethod = (getnamecallmethod ~= nil)
	Executor.HasGetUpvalues = (getupvalues ~= nil or (debug and debug.getupvalues ~= nil))
	Executor.HasHookFunction = (hookfunction ~= nil)

	Executor.CanHookNamecall = Executor.HasRawMetatable and Executor.HasGetNamecallMethod
	Executor.CanReadUpvalues = Executor.HasGetUpvalues

	if not getgenv then
		_G.getgenv = function()
			return _G
		end
		Executor.HasGetgenv = true
	end

	Executor.Request = function(opts)
		if not opts then
			return { StatusCode = 0, Body = "No options provided" }
		end

		local fn = rawReqFn
		if not fn then
			pcall(function()
				fn = (syn and syn.request)
					or (http and http.request)
					or (fluxus and fluxus.request)
					or (krnl and krnl.request)
					or (typeof(request) == "function" and request)
					or (typeof(http_request) == "function" and http_request)
					or (getgenv and typeof(getgenv().request) == "function" and getgenv().request)
					or (getgenv and typeof(getgenv().http_request) == "function" and getgenv().http_request)
			end)
		end

		if fn then
			local reqData = {
				Url = opts.Url or opts.url,
				url = opts.Url or opts.url,
				Method = opts.Method or opts.method or "POST",
				method = opts.Method or opts.method or "POST",
				Headers = opts.Headers or opts.headers or { ["Content-Type"] = "application/json" },
			headers = opts.Headers or opts.headers or { ["Content-Type"] = "application/json" },
				Body = opts.Body or opts.body or "",
			body = opts.Body or opts.body or "",
			}
			local reqOk, res = pcall(fn, reqData)
			if reqOk and type(res) == "table" then
				return res
			elseif reqOk then
				return { StatusCode = 200, Body = tostring(res) }
			else
				return { StatusCode = 0, Body = tostring(res) }
			end
		end

		warn("[NatAovHub] Executor hiện tại không hỗ trợ hàm request() để gửi Webhook!")
		return { StatusCode = 0, Body = "No request function found" }
	end
	Executor.RawMetatable = getrawmetatable
	if not Executor.RawMetatable then
		Executor.RawMetatable = function(obj)
			if debug and debug.getmetatable then
				return debug.getmetatable(obj)
			end
			return nil
		end
	end

	Executor.NewCClosure = newcclosure or function(fn)
		return fn
	end

	Executor.SetReadOnly = setreadonly
	if not Executor.SetReadOnly then
		Executor.SetReadOnly = function()
		end
	end

	Executor.GetNamecallMethod = getnamecallmethod or function()
		return nil
	end

	Executor.GetUpvalues = getupvalues
		or function(fn)
			if debug and debug.getupvalues then
				return debug.getupvalues(fn)
			end
			return {}
		end

	Executor.SetFFlag = setfflag
	if not Executor.SetFFlag then
		Executor.SetFFlag = function()
		end
	end

	Executor.GetNilInstances = getnilinstances
	if not Executor.GetNilInstances then
		Executor.GetNilInstances = function()
			return {}
		end
	end
end

-- ============================================================================
-- 2) CONFIG — bảng cấu hình hiện đại + hệ thống cài đặt nội bộ
-- ============================================================================
local Defaults = {
	["Team"] = "Pirates",
	["Hunt"] = {
		["Min"] = 0,
		["Max"] = 1e9,
		["Max Distance"] = 30000,
		["Priority"] = "Balanced", -- "Distance" | "Bounty" | "Balanced"
		["Prefer Low Health"] = false, -- cộng điểm cho mục tiêu máu thấp	
	},
	["Skip"] = {
		["Fruit"] = false,
		["Fruit List"] = { "Portal-Portal", "Buddha-Buddha", "Kitsune-Kitsune", "Dragon-Dragon", "Yeti-Yeti" },
		["No PvP"] = true,
		["Skip Race V4"] = false, -- thêm vào đây luôn
	},
	["Melee"] = {  
		["Enable"] = true,  
		["Delay"] = 0.1,  
		["Skill Z"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },  
		["Skill X"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },  
		["Skill C"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },  
	},
	["Sword"] = {
		["Enable"] = true,
		["Delay"] = 0.1,
		["Skill Z"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },
		["Skill X"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },
	},
	["Gun"] = {
		["Enable"] = true,
		["Gun Mode"] = true,
		["Delay"] = 0.1,
		["Skill Z"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },
		["Skill X"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },
	},
	["Fruit"] = {
		["Enable"] = true,
		["Delay"] = 0.1,
		["Skill Z"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },
		["Skill X"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },
		["Skill C"] = { ["Enable"] = true, ["Hold Time"] = 0.1 },
		["Skill V"] = { ["Enable"] = false, ["Hold Time"] = 0.1 },
		["Skill F"] = { ["Enable"] = false, ["Hold Time"] = 0.1 },
	},
	["Aim Prediction"] = {
		["Enable"] = true, -- dự đoán vị trí tương lai của mục tiêu (aim trước)
		["Look Ahead"] = 0.25, -- giây nhìn trước (độ trễ đòn càng cao càng cần lớn)
		["Max Distance"] = 300, -- chỉ dự đoán khi mục tiêu trong tầm này
	},
	["Skill Spam Method"] = {
		["Mode"] = "None", -- "None" | "Random" | "Sequence" | "LowHealth"
		["Interval"] = 0.35, -- giây giữa các lần bấm skill
		["Low Health Percent"] = 30, -- mục tiêu dưới % này thì mới spam (chế độ LowHealth)
		["Keys"] = { "Z", "X", "C", "V", "F" }, -- danh sách phím spam
	},
	["Safe Health"] = {
		["Health"] = 50, -- ngưỡng máu tuyệt đối (dùng khi UsePercent = false)
		["Use Percent"] = true, -- dùng phần trăm thay vì tuyệt đối
		["Percent"] = 30, -- máu dưới % này → bay lên trời chờ hồi
		["Heal Percent"] = 60, -- hồi tới % này → bay xuống đánh tiếp
		["Fly Height"] = 10000, -- độ cao bay chờ hồi máu
	},
	["Another"] = {  
		["Auto Random Fruit"] = true,  
		["Bypass TP"] = true,  
		["Tween Speed"] = 267, -- tốc độ tween player (10-350, 200 an toàn không bị tp back)  
		["Force Anchored Y"] = true, -- KHÔNG ép Y theo đích (tránh bị tp back khi địch ở quá cao)  
		["Auto Random Bone"] = false,  
		["Auto Store Fruit"] = false,  
		["Auto Observation"] = true,  
		["Race V3"] = true,  
		["Race V4"] = false,  
		["FPS Boots"] = false,  
		["Hide Map"] = { ["Enable"] = false, ["Keep Players"] = true },
		["Black Screen"] = false, -- phủ màn hình đen toàn màn hình  
		["White Screen"] = false, -- phủ màn hình trắng toàn màn hình  
		["ESP Player"] = true, -- hiển thị box + tên + HP + khoảng cách người chơi (đỏ=địch)  
	},
	["Webhook"] = {
		["Enabled"] = true,
		["Url"] = "https://discord.com/api/webhooks/1527531328860454994/ZR9HdVgjko-w2EacyoON5W50e6U-697faD-RC7HvDpFxI3zR8YyxR5fgODMJMfxdKUzk",
	},
}

-- Cài đặt nội bộ riêng trong code
local Internal = {
	FindCooldown = 1.0, -- giây giữa 2 lần quét tìm (chống lag/spam)
	MaxNoTargetRetries = 4, -- số lần quét trống liên tiếp rồi mới hop
	FlyUpOnNoTarget = true, -- hết mục tiêu: bay lên cao chờ rồi mới hop
	FlyUpHeight = 5000, -- độ cao tối đa khi bay chờ hop
	CombatWaitMax = 60, -- giây tối đa chờ hết in combat trước khi hop
	Combat = {
		Hitbox = {
			Enable = true, -- mở rộng hitbox người chơi khác cho dễ trúng
			Multiplier = 2, -- tỷ lệ phóng to (1-5, khuyến nghị 1.5-3)
			AllPlayers = true, -- true = scale mọi người, false = chỉ mục tiêu đang săn
			IncludeRoot = true, -- có scale cả HumanoidRootPart (rủi ro cao hơn)
		},
		AntiStun = {
			Enable = true, -- chống choáng / ngã / ngồi (khóa di chuyển)
		},
		Orbit = {
			Enable = true, -- bay vòng tròn quanh kẻ địch + xả skill
			Radius = 12, -- bán kính vòng tròn (studs)
			AngleSpeed = 6, -- độ quay mỗi tick (~50 độ/giây)
			Height = 2, -- độ cao bay so với mục tiêu
		},
		SkillSpam = {
			Mode = "None",
			Interval = 0.35,
			LowHealthPercent = 30,
			Keys = { "Z", "X", "C", "V", "F" },
		},
	},
	CheckCombatBeforeHop = true,
	Water = true, -- đi trên nước (dâng mặt nước lên)
	HopMinPlayers = 8, -- ưu tiên hop tới server có ít nhất N người
	HopMaxPlayers = 11, -- và nhiều nhất M người (đông vừa đủ để săn)
	HopCountdown = 3, -- giây đếm ngược trước khi hop (nhanh hơn)
}

local THUMBNAIL_IMAGE = "https://cdn.discordapp.com/embed/avatars/0.png"

local function DeepMerge(base, patch)
	patch = patch or {}
	local out = {}
	for k, v in pairs(base) do
		if type(v) == "table" and type(patch[k]) == "table" then
			out[k] = DeepMerge(v, patch[k])
		elseif patch[k] ~= nil then
			out[k] = patch[k]
		else
			out[k] = v
		end
	end
	for k, v in pairs(patch) do
		if out[k] == nil then
			out[k] = v
		end
	end
	return out
end

local function NormalizeConfig(data)
	data = data or {}

	data.Team = data.Team or "Pirates"

	data.Hunt = data.Hunt or {}
	data.Hunt.Min = data.Hunt.Min or 0
	data.Hunt.Max = data.Hunt.Max or 1e9
	data.Hunt.MaxDistance = tonumber(data.Hunt["Max Distance"] or data.Hunt.MaxDistance or 30000)
	data.Hunt["Max Distance"] = data.Hunt.MaxDistance
	data.Hunt.Priority = data.Hunt.Priority or "Balanced"
	if data.Hunt["Prefer Low Health"] ~= nil then
		data.Hunt.PreferLowHealth = (data.Hunt["Prefer Low Health"] == true)
	else
		data.Hunt.PreferLowHealth = (data.Hunt.PreferLowHealth == true)
	end
	data.Hunt["Prefer Low Health"] = data.Hunt.PreferLowHealth
	data.Hunt.FindCooldown = data.Hunt.FindCooldown or Internal.FindCooldown
	data.Hunt.MaxNoTargetRetries = data.Hunt.MaxNoTargetRetries or Internal.MaxNoTargetRetries
	if data.Hunt.FlyUpOnNoTarget == nil then
		data.Hunt.FlyUpOnNoTarget = Internal.FlyUpOnNoTarget
	end
	data.Hunt.FlyUpHeight = data.Hunt.FlyUpHeight or Internal.FlyUpHeight
	data.Hunt.CombatWaitMax = data.Hunt.CombatWaitMax or Internal.CombatWaitMax

	data.Skip = data.Skip or {}
	data.Skip.Fruit = (data.Skip.Fruit == true)
	data.Skip.FruitList = data.Skip["Fruit List"] or data.Skip.FruitList or { "Portal-Portal", "Buddha-Buddha", "Kitsune-Kitsune", "Dragon-Dragon", "Yeti-Yeti" }
	data.Skip["Fruit List"] = data.Skip.FruitList
	data.Skip.NoPvP = (data.Skip["No PvP"] ~= nil and data.Skip["No PvP"] == true) or (data.Skip.NoPvP ~= false)
	data.Skip["No PvP"] = data.Skip.NoPvP
	data["Skip Race V4"] = (data.Skip["Skip Race V4"] ~= nil and data.Skip["Skip Race V4"] == true) or (data["Skip Race V4"] == true)
	data.Skip["Skip Race V4"] = data["Skip Race V4"]

	local function normalizeWeapon(w, def)
		def = def or {}
		w = w or {}
		w.Enable = (w.Enable ~= false)
		w.Delay = tonumber(w.Delay) or 0.1
		for _, k in ipairs({ "Z", "X", "C", "V", "F" }) do
			local skillData = w["Skill " .. k] or w[k] or (def and (def["Skill " .. k] or def[k]))
			if type(skillData) == "table" then
				local en = (skillData.Enable == true)
				local ht = tonumber(skillData["Hold Time"] or skillData.HoldTime) or 0.1
				w[k] = { Enable = en, HoldTime = ht }
				w["Skill " .. k] = w[k]
			end
		end
		if w["Gun Mode"] ~= nil then
			w.GunMode = (w["Gun Mode"] == true)
		elseif w.GunMode ~= nil then
			w["Gun Mode"] = (w.GunMode == true)
		end
		return w
	end

	data.Melee = normalizeWeapon(data.Melee, Defaults.Melee)
	data.Sword = normalizeWeapon(data.Sword, Defaults.Sword)
	data.Gun = normalizeWeapon(data.Gun, Defaults.Gun)
	data.Fruit = normalizeWeapon(data.Fruit, Defaults.Fruit)

	local aim = data["Aim Prediction"] or data.AimPrediction or Defaults["Aim Prediction"]
	data["Aim Prediction"] = {
		Enable = (aim.Enable ~= false),
		LookAhead = tonumber(aim["Look Ahead"] or aim.LookAhead) or 0.25,
		MaxDistance = tonumber(aim["Max Distance"] or aim.MaxDistance) or 300,
	}
	data["Aim Prediction"]["Look Ahead"] = data["Aim Prediction"].LookAhead
	data["Aim Prediction"]["Max Distance"] = data["Aim Prediction"].MaxDistance
	data.AimPrediction = data["Aim Prediction"]

	local spam = data["Skill Spam Method"] or (data.Combat and data.Combat.SkillSpam) or data.SkillSpam or Defaults["Skill Spam Method"]
	data["Skill Spam Method"] = {
		Mode = spam.Mode or "None",
		Interval = tonumber(spam.Interval) or 0.35,
		LowHealthPercent = tonumber(spam["Low Health Percent"] or spam.LowHealthPercent) or 30,
		Keys = (type(spam.Keys) == "table" and spam.Keys) or { "Z", "X", "C", "V", "F" },
	}
	data["Skill Spam Method"]["Low Health Percent"] = data["Skill Spam Method"].LowHealthPercent
	data.SkillSpam = data["Skill Spam Method"]
	data.Combat = data.Combat or {}
	data.Combat.SkillSpam = data["Skill Spam Method"]

	local sh = data["Safe Health"] or data.SafeHealth or Defaults["Safe Health"]
	data["Safe Health"] = {
		Health = tonumber(sh.Health) or 50,
		UsePercent = (sh["Use Percent"] ~= nil and sh["Use Percent"] == true) or (sh.UsePercent ~= false),
		Percent = tonumber(sh.Percent) or 40,
		HealPercent = tonumber(sh["Heal Percent"] or sh.HealPercent) or 65,
		FlyHeight = tonumber(sh["Fly Height"] or sh.FlyHeight) or 10000,
	}
	data["Safe Health"]["Use Percent"] = data["Safe Health"].UsePercent
	data["Safe Health"]["Heal Percent"] = data["Safe Health"].HealPercent
	data["Safe Health"]["Fly Height"] = data["Safe Health"].FlyHeight
	data.SafeHealth = data["Safe Health"]

	local an = data.Another or Defaults.Another
	data.Another = {
		AutoRandomFruitOnJoin = (an["Auto Random Fruit"] ~= nil and an["Auto Random Fruit"] == true) or (an.AutoRandomFruitOnJoin == true),
		BypassTP = (an["Bypass TP"] ~= nil and an["Bypass TP"] == true) or (an.BypassTP ~= false),
		TweenSpeed = tonumber(an["Tween Speed"] or an.TweenSpeed) or 250,
		ForceAnchoredY = (an["Force Anchored Y"] ~= nil and an["Force Anchored Y"] == true) or (an.ForceAnchoredY == true),
		AutoRandomBoneOnJoin = (an["Auto Random Bone"] ~= nil and an["Auto Random Bone"] == true) or (an.AutoRandomBoneOnJoin == true),
		AutoStoreFruit = (an["Auto Store Fruit"] ~= nil and an["Auto Store Fruit"] == true) or (an.AutoStoreFruit == true),
		AutoObservation = (an["Auto Observation"] ~= nil and an["Auto Observation"] == true) or (an.AutoObservation ~= false),
		V3 = (an["Race V3"] ~= nil and an["Race V3"] == true) or (an.V3 ~= false) or (an["V3"] == true),
		V4 = (an["Race V4"] ~= nil and an["Race V4"] == true) or (an.V4 == true) or (an["V4"] == true),
		FPSBoots = (an["FPS Boots"] ~= nil and an["FPS Boots"] == true) or (an.FPSBoots == true),
		CheckCombatBeforeHop = (an.CheckCombatBeforeHop ~= nil and an.CheckCombatBeforeHop) or Internal.CheckCombatBeforeHop,
		Water = (an.Water ~= nil and an.Water) or Internal.Water,
		HopMinPlayers = tonumber(an.HopMinPlayers) or Internal.HopMinPlayers,
		HopMaxPlayers = tonumber(an.HopMaxPlayers) or Internal.HopMaxPlayers,
		HopCountdown = tonumber(an.HopCountdown) or Internal.HopCountdown,
	}
	data.Another["Auto Random Fruit"] = data.Another.AutoRandomFruitOnJoin
	data.Another["Bypass TP"] = data.Another.BypassTP
	data.Another["Tween Speed"] = data.Another.TweenSpeed
	data.Another["Force Anchored Y"] = data.Another.ForceAnchoredY
	data.Another["Auto Random Bone"] = data.Another.AutoRandomBoneOnJoin
	data.Another["Auto Store Fruit"] = data.Another.AutoStoreFruit
	data.Another["Auto Observation"] = data.Another.AutoObservation
	data.Another["Race V3"] = data.Another.V3
	data.Another["Race V4"] = data.Another.V4
	data.Another["FPS Boots"] = data.Another.FPSBoots

	local hideMap = an["Hide Map"] or (data.Visual and data.Visual.HideMap) or { Enable = false, KeepPlayers = true }
	data.Visual = {
		HideMap = {
			Enable = (hideMap.Enable == true),
			KeepPlayers = (hideMap["Keep Players"] ~= nil and hideMap["Keep Players"] == true) or (hideMap.KeepPlayers ~= false),
		},
		BlackScreen = (an["Black Screen"] ~= nil and an["Black Screen"] == true) or (data.Visual and data.Visual.BlackScreen == true),
		WhiteScreen = (an["White Screen"] ~= nil and an["White Screen"] == true) or (data.Visual and data.Visual.WhiteScreen == true),
		ESPPlayer = (an["ESP Player"] ~= nil and an["ESP Player"] == true) or (data.Visual and data.Visual.ESPPlayer ~= false),
	}
	data.Another["Hide Map"] = data.Visual.HideMap
	data.Another["Black Screen"] = data.Visual.BlackScreen
	data.Another["White Screen"] = data.Visual.WhiteScreen
	data.Another["ESP Player"] = data.Visual.ESPPlayer

	data.Combat = data.Combat or {}
	data.Combat.Hitbox = data.Combat.Hitbox or Internal.Combat.Hitbox
	data.Combat.AntiStun = data.Combat.AntiStun or Internal.Combat.AntiStun
	data.Combat.Orbit = data.Combat.Orbit or Internal.Combat.Orbit
	data.Combat.SkillSpam = data.Combat.SkillSpam or Internal.Combat.SkillSpam
	data.Combat.AimPrediction = data["Aim Prediction"]

	data.Webhook = data.Webhook or Defaults.Webhook

	return data
end

local Config = {}
Config.Data = NormalizeConfig(DeepMerge(Defaults, getgenv().Setting))
getgenv().Setting = Config.Data

function AutoBounty:SetConfig(user)
	Config.Data = NormalizeConfig(DeepMerge(Defaults, user or getgenv().Setting))
	getgenv().Setting = Config.Data
	return Config.Data
end

-- ============================================================================
-- 3) STATE — trạng thái nội bộ, đồng bộ getgenv() để tương thích thư viện
-- ============================================================================
local State = {
	weapon = nil,
	target = nil,
	killed = nil,
	checked = {},
	killCount = 0,
	isHopping = false,
}

local function SetState(key, value)
	State[key] = value
	getgenv()[key] = value
end

local function GetState(key)
	local v = State[key]
	if v == nil then
		local g = getgenv()[key]
		if g ~= nil then
			State[key] = g
		end
		return g
	end
	return v
end

-- ============================================================================
-- 4) UTILS
-- ============================================================================
local Utils = {}

function Utils.FormatNum(n)
	if n >= 1e9 then
		return string.format("%.1fB", n / 1e9)
	elseif n >= 1e6 then
		return string.format("%.1fM", n / 1e6)
	elseif n >= 1e3 then
		return string.format("%.1fK", n / 1e3)
	else
		return tostring(n)
	end
end

function Utils.Contains(array, value)
	if not array then
		return false
	end
	for _, v in ipairs(array) do
		if v == value then
			return true
		end
	end
	return false
end

function Utils.IsMobile()
	local vp = Camera and Camera.ViewportSize or Vector2.new(800, 600)
	if UserInputService.TouchEnabled then
		return true
	end
	if vp.X <= 900 or vp.Y <= 600 then
		return true
	end
	return false
end

-- ============================================================================
-- 5) WORLD — phát hiện thế giới + bảng đảo + khoảng cách bypass
-- ============================================================================
local World = {}
World.Current = "Unknown"
World.Islands = {}
World.bypassDist = 1500

local PLACE_TO_WORLD = {
	[2753915549] = "World1",
	[85211729168715] = "World1",
	[4442272183] = "World2",
	[79091703265657] = "World2",
	[7449423635] = "World3",
	[100117331123089] = "World3",
}

function World.Init()
	World.Current = PLACE_TO_WORLD[game.PlaceId] or "Unknown"

	if World.Current == "World3" then
		World.bypassDist = 5000
		World.Islands = {
			["Port Town"] = CFrame.new(-290.7376708984375, 6.729952812194824, 5343.5537109375),
			["Hydra Island"] = CFrame.new(5749.7861328125 + 50, 611.9736938476562, -276.2497863769531),
			["Mansion"] = CFrame.new(-12471.169921875 + 50, 374.94024658203, -7551.677734375),
			["Castle On The Sea"] = CFrame.new(-5085.23681640625 + 50, 316.5072021484375, -3156.202880859375),
			["Haunted Island"] = CFrame.new(-9547.5703125, 141.0137481689453, 5535.16162109375),
			["Great Tree"] = CFrame.new(2681.2736816406, 1682.8092041016, -7190.9853515625),
			["Candy Island"] = CFrame.new(-1106.076416015625, 13.016114234924316, -14231.9990234375),
			["Cake Island"] = CFrame.new(-1903.6856689453125, 36.70722579956055, -11857.265625),
			["Loaf Island"] = CFrame.new(-889.8325805664062, 64.72842407226562, -10895.8876953125),
			["Peanut Island"] = CFrame.new(-1943.59716796875, 37.012996673583984, -10288.01171875),
			["Cocoa Island"] = CFrame.new(147.35205078125, 23.642955780029297, -12030.5498046875),
			["Tiki Outpost"] = CFrame.new(-16234, 9, 416),
			["Submerged Island"] = CFrame.new(10880.5, -2086.5, 10033.5),
		}
	elseif World.Current == "World2" then
		World.bypassDist = 3500
		World.Islands = {
			a = CFrame.new(753.14288330078, 408.23559570313, -5274.6147460938),
			b = CFrame.new(-5622.033203125, 492.19604492188, -781.78552246094),
			c = CFrame.new(-11.311455726624, 29.276733398438, 2771.5224609375),
			d = CFrame.new(-2448.5300292969, 73.016105651855, -3210.6306152344),
			e = CFrame.new(-380.47927856445, 77.220390319824, 255.82550048828),
			f = CFrame.new(-3032.7641601563, 317.89672851563, -10075.373046875),
			g = CFrame.new(6148.4116210938, 294.38687133789, -6741.1166992188),
			h = CFrame.new(923.40197753906, 125.05712890625, 32885.875),
			i = CFrame.new(-6127.654296875, 15.951762199402, -5040.2861328125),
		}
	elseif World.Current == "World1" then
		World.bypassDist = 1500
		World.Islands = {
			a = CFrame.new(979.79895019531, 16.516613006592, 1429.0466308594),
			b = CFrame.new(-2566.4296875, 6.8556680679321, 2045.2561035156),
			c = CFrame.new(944.15789794922, 20.919729232788, 4373.3002929688),
			d = CFrame.new(-1181.3093261719, 4.7514905929565, 3803.5456542969),
			e = CFrame.new(-1612.7957763672, 36.852081298828, 149.12843322754),
			f = CFrame.new(-690.33081054688, 15.09425163269, 1582.2380371094),
			g = CFrame.new(-4607.82275, 872.54248, -1667.55688),
			h = CFrame.new(-7952.31006, 5545.52832, -320.704956),
			i = CFrame.new(-4914.8212890625, 50.963626861572, 4281.0278320313),
			j = CFrame.new(-1427.6203613281, 7.2881078720093, -2792.7722167969),
			k = CFrame.new(1347.8067626953, 104.66806030273, -1319.7370605469),
			l = CFrame.new(5127.1284179688, 59.501365661621, 4105.4458007813),
			m = CFrame.new(61163.8515625, 11.6796875, 1819.7841796875),
			n = CFrame.new(-5247.7163085938, 12.883934020996, 8504.96875),
			o = CFrame.new(4875.330078125, 5.6519818305969, 734.85021972656),
			p = CFrame.new(-4813.0249, 903.708557, -1912.69055),
			q = CFrame.new(-4970.21875, 717.707275, -2622.35449),
		}
	end
end

-- ============================================================================
-- 6) RUNTIME — biến dùng chung giữa các module (không phải global)
-- ============================================================================
local isHopping = false
local hopRequested = false
local stopBypass = false
local hopInProgress = false
local hopRetryQueued = false

local SafeHop
local SkipPlayer
local HopServers
local activeTween
local chosenRegion
local gunModeEnabled
local combatFramework
local isAiming = false
local aimCFrame
local aimTargetPos
local aimPredictData = {}
local setHopping
local isRunning = false
local HasActivePvpTag
local HasActivePvpTagRisk
local HasActivePvpTagNormal

-- ============================================================================
-- 7) UI — giao diện xanh dương NatAov Hub
-- ============================================================================
local UI = {}
UI.Refs = {}
UI.Icons = {
	["coins"] = "rbxassetid://10709811110",
	["clock"] = "rbxassetid://10709805144",
	["heart"] = "rbxassetid://10723406885",
	["shield"] = "rbxassetid://10734951847",
	["star"] = "rbxassetid://10734966248",
	["user"] = "rbxassetid://10747373176",
	["target"] = "rbxassetid://10734977012",
	["ruler"] = "rbxassetid://10734941018",
	["sword"] = "rbxassetid://10734975486",
	["swords"] = "rbxassetid://10734975692",
	["server"] = "rbxassetid://10734949856",
	["trophy"] = "rbxassetid://10747363809",
	["search"] = "rbxassetid://10734943674",
	["flame"] = "rbxassetid://10723376114",
	["cherry"] = "rbxassetid://10709790875",
	["crosshair"] = "rbxassetid://10709818534",
	["activity"] = "rbxassetid://10709752035",
}

function UI.Build()
	local refs = UI.Refs
	local Icons = UI.Icons
	local DEFAULT_UI_POSITION = UDim2.new(0.5, 0, 0.5, 0)
	local lastUIPosition = DEFAULT_UI_POSITION
	local guiVisible = true
	local _animating = false
	local BASE_W, BASE_H = 560, 355
	local PILL_W, PILL_H = 280, 48
	local CX, CY, CW, CH, GAP = 168, 110, 183, 60, 8

	local function calcUISize()
		local vp = Camera.ViewportSize
		local sw, sh = vp.X, vp.Y
		local w, h, pillW, pillH

		if Utils.IsMobile() then
			w = math.clamp(sw * 0.92, 320, 500)
			h = math.clamp(sh * 0.65, 248, 300)
			pillW = math.clamp(sw * 0.68, 200, 280)
			pillH = 44
		else
			local scaleX = math.min(sw / (BASE_W + 40), 1)
			local scaleY = math.min(sh / (BASE_H + 40), 1)
			local scale = math.max(math.min(scaleX, scaleY), 0.55)
			w = math.floor(BASE_W * scale)
			h = math.floor(BASE_H * scale)
			pillW = math.floor(PILL_W * math.max(scale, 0.75))
			pillH = math.floor(PILL_H * math.max(scale, 0.85))
		end
		return math.floor(w), math.floor(h), math.floor(pillW), math.floor(pillH)
	end

	local function ApplyToggleLayout()
		if not refs.ToggleContainer then
			return
		end
		local _, h, pillW, pillH = calcUISize()
		local mobile = Utils.IsMobile()

		if mobile and guiVisible then
			local vp = Camera.ViewportSize
			local uiW, uiH = calcUISize()
			local top = math.floor((vp.Y - uiH) / 2)
			local left = math.floor((vp.X - uiW) / 2)

			refs.ToggleContainer.AnchorPoint = Vector2.new(1, 0)
			refs.ToggleContainer.Position = UDim2.new(0, left + uiW - 6, 0, math.max(top + 6, 6))
			refs.ToggleContainer.Size = UDim2.new(0, 34, 0, 34)

			if refs.toggleAvatar then
				refs.toggleAvatar.Visible = false
			end
			if refs.toggleTitle then
				refs.toggleTitle.Visible = false
			end
			if refs.toggleSub then
				refs.toggleSub.Visible = false
			end
			if refs.toggleIconFrame then
				refs.toggleIconFrame.AnchorPoint = Vector2.new(0.5, 0.5)
				refs.toggleIconFrame.Position = UDim2.new(0.5, 0, 0.5, 0)
				refs.toggleIconFrame.Size = UDim2.new(0, 20, 0, 20)
			end
			if refs.toggleIconLbl then
				refs.toggleIconLbl.TextSize = 8
			end
		else
			refs.ToggleContainer.AnchorPoint = Vector2.new(0.5, 0)
			refs.ToggleContainer.Position = UDim2.new(0.5, 0, 0, 6)
			refs.ToggleContainer.Size = UDim2.new(0, pillW, 0, pillH)

			if refs.toggleAvatar then
				refs.toggleAvatar.Visible = true
				local tRatio = pillH / 48
				local avatarSize = math.floor(38 * tRatio)
				refs.toggleAvatar.Position = UDim2.new(0, 6, 0.5, 0)
				refs.toggleAvatar.Size = UDim2.new(0, avatarSize, 0, avatarSize)
			end
			if refs.toggleTitle then
				refs.toggleTitle.Visible = true
				refs.toggleTitle.TextSize = math.max(math.floor(12 * (pillH / 48)), 8)
				refs.toggleTitle.Position = UDim2.new(0, 52, 0, 6)
				refs.toggleTitle.Size = UDim2.new(1, -86, 0, 20)
			end
			if refs.toggleSub then
				refs.toggleSub.Visible = true
				refs.toggleSub.TextSize = math.max(math.floor(10 * (pillH / 48)), 7)
				refs.toggleSub.Position = UDim2.new(0, 52, 0, 26)
				refs.toggleSub.Size = UDim2.new(1, -86, 0, 14)
			end
			if refs.toggleIconFrame then
				local iconSize = math.floor(28 * (pillH / 48))
				refs.toggleIconFrame.AnchorPoint = Vector2.new(1, 0.5)
				refs.toggleIconFrame.Position = UDim2.new(1, -8, 0.5, 0)
				refs.toggleIconFrame.Size = UDim2.new(0, iconSize, 0, iconSize)
			end
			if refs.toggleIconLbl then
				refs.toggleIconLbl.TextSize = math.max(math.floor(12 * (pillH / 48)), 8)
			end
		end
	end

	local function ApplyResponsive()
		local w, h, pillW, pillH = calcUISize()
		local mobile = Utils.IsMobile()
		refs.DropShadowHolder.Size = UDim2.new(0, w, 0, h)
		refs.DropShadowHolder.Position = lastUIPosition or DEFAULT_UI_POSITION

		local scale = w / BASE_W
		local textScale = scale * 1.1

		ApplyToggleLayout()

		if refs.HubTitle then
			refs.HubTitle.TextSize = mobile and 13 or math.max(math.floor(17 * textScale), 12)
		end
		if refs.HubSub then
			refs.HubSub.TextSize = mobile and 9 or math.max(math.floor(10 * textScale), 8)
		end
		if refs.AvatarLabel then
			refs.AvatarLabel.TextSize = mobile and 14 or math.max(math.floor(26 * textScale), 16)
		end

		if refs.AvatarCircle then
			if mobile then
				refs.AvatarCircle.Position = UDim2.new(0, 10, 0, 22)
				refs.AvatarCircle.Size = UDim2.new(0, 28, 0, 28)
			else
				refs.AvatarCircle.Position = UDim2.new(0, 16, 0, 50)
				refs.AvatarCircle.Size = UDim2.new(0, 62, 0, 62)
			end
		end

		if refs.HubTitle then
			if mobile then
				refs.HubTitle.Position = UDim2.new(0, 44, 0, 10)
				refs.HubTitle.Size = UDim2.new(1, -84, 0, 20)
			else
				refs.HubTitle.Position = UDim2.new(0, 92, 0, 20)
				refs.HubTitle.Size = UDim2.new(0, 340, 0, 26)
			end
		end

		if refs.HubSub then
			refs.HubSub.Visible = true
			if mobile then
				refs.HubSub.Position = UDim2.new(0, 44, 0, 30)
				refs.HubSub.Size = UDim2.new(1, -84, 0, 18)
			else
				refs.HubSub.Position = UDim2.new(0, 92, 0, 48)
				refs.HubSub.Size = UDim2.new(0.62, 0, 0, 30)
			end
		end

		if refs.HDivider then
			refs.HDivider.Position = mobile and UDim2.new(0, 0, 0, 66) or UDim2.new(0, 0, 0, 96)
		end

		if refs.StatusDot then
			refs.StatusDot.Position = mobile and UDim2.new(0, 44, 0, 54) or UDim2.new(0, 92, 0, 80)
			refs.StatusDot.Size = mobile and UDim2.new(0, 7, 0, 7) or UDim2.new(0, 8, 0, 8)
		end

		if refs.StatusLbl then
			refs.StatusLbl.Position = mobile and UDim2.new(0, 55, 0, 49) or UDim2.new(0, 106, 0, 78)
			refs.StatusLbl.Size = mobile and UDim2.new(0, 110, 0, 14) or UDim2.new(0, 120, 0, 16)
			refs.StatusLbl.TextSize = mobile and 9 or math.max(math.floor(10 * textScale), 8)
		end

		if refs.InfoTitle then
			refs.InfoTitle.TextSize = mobile and 9 or math.max(math.floor(12 * textScale), 10)
		end

		if refs.InfoPanel then
			if mobile then
				refs.InfoPanel.Position = UDim2.new(0, 6, 0, 72)
				refs.InfoPanel.Size = UDim2.new(0, 108, 0, 196)
			else
				refs.InfoPanel.Position = UDim2.new(0, 10, 0, 110)
				refs.InfoPanel.Size = UDim2.new(0, 148, 0, 198)
			end
		end

		if refs.InfoTitle then
			if mobile then
				refs.InfoTitle.Position = UDim2.new(0, 8, 0, 6)
				refs.InfoTitle.Size = UDim2.new(1, -8, 0, 14)
			else
				refs.InfoTitle.Position = UDim2.new(0, 10, 0, 7)
				refs.InfoTitle.Size = UDim2.new(1, -10, 0, 16)
			end
		end

		if mobile then
			local infoRows = {
				{ label = refs.InfoBounty, y = 24 },
				{ label = refs.InfoRace, y = 48 },
				{ label = refs.InfoLevel, y = 72 },
				{ label = refs.InfoHealth, y = 96 },
				{ label = refs.InfoMelee, y = 122 },
				{ label = refs.InfoFPS, y = 146 },
				{ label = refs.InfoKill, y = 170 },
			}
			for _, rowData in ipairs(infoRows) do
				local row = rowData.label
				if row and row.Parent then
					row.Parent.Position = UDim2.new(0, 8, 0, rowData.y)
					row.Parent.Size = UDim2.new(1, -8, 0, 20)
					row.Position = UDim2.new(0, 18, 0, 0)
					row.Size = UDim2.new(1, -18, 1, 0)
					row.TextSize = 9
					local icon = row.Parent:FindFirstChildOfClass("ImageLabel")
					if icon then
						icon.Position = UDim2.new(0, 0, 0, 4)
						icon.Size = UDim2.new(0, 14, 0, 14)
					end
				end
			end
			if refs.InfoDivider then
				refs.InfoDivider.Position = UDim2.new(0, 8, 0, 116)
				refs.InfoDivider.Size = UDim2.new(1, -16, 0, 1)
			end
		else
			local infoRows = {
				{ label = refs.InfoBounty, y = 28 },
				{ label = refs.InfoRace, y = 52 },
				{ label = refs.InfoLevel, y = 76 },
				{ label = refs.InfoHealth, y = 100 },
				{ label = refs.InfoMelee, y = 128 },
				{ label = refs.InfoFPS, y = 150 },
				{ label = refs.InfoKill, y = 172 },
			}
			for _, rowData in ipairs(infoRows) do
				local row = rowData.label
				if row and row.Parent then
					row.Parent.Position = UDim2.new(0, 10, 0, rowData.y)
					row.Parent.Size = UDim2.new(1, -10, 0, 20)
					row.Position = UDim2.new(0, 20, 0, 0)
					row.Size = UDim2.new(1, -20, 1, 0)
					row.TextSize = 11
					local icon = row.Parent:FindFirstChildOfClass("ImageLabel")
					if icon then
						icon.Position = UDim2.new(0, 0, 0, 2)
						icon.Size = UDim2.new(0, 16, 0, 16)
					end
				end
			end
			if refs.InfoDivider then
				refs.InfoDivider.Position = UDim2.new(0, 8, 0, 122)
				refs.InfoDivider.Size = UDim2.new(1, -16, 0, 1)
			end
		end

		local cardScale = scale * 1.05
		if refs.CardBountyVal then
			refs.CardBountyVal.TextSize = mobile and 14 or math.max(math.floor(16 * cardScale), 12)
		end
		if refs.CardTimeVal then
			refs.CardTimeVal.TextSize = mobile and 14 or math.max(math.floor(16 * cardScale), 12)
		end

		if mobile and refs.BountyCard and refs.TimeCard then
			local infoW = 108
			local layoutGap = 5
			local rightX = infoW + 14
			local availableW = math.max(w - rightX - 8, 150)
			local cardW = math.floor((availableW - layoutGap) / 2)
			local cardH = 70
			local topY = 72
			refs.BountyCard.Position = UDim2.new(0, rightX, 0, topY)
			refs.BountyCard.Size = UDim2.new(0, cardW, 0, cardH)
			refs.TimeCard.Position = UDim2.new(0, rightX + cardW + layoutGap, 0, topY)
			refs.TimeCard.Size = UDim2.new(0, cardW, 0, cardH)
		elseif refs.BountyCard and refs.TimeCard then
			refs.BountyCard.Position = UDim2.new(0, CX, 0, CY)
			refs.BountyCard.Size = UDim2.new(0, CW, 0, CH)
			refs.TimeCard.Position = UDim2.new(0, CX + CW + GAP, 0, CY)
			refs.TimeCard.Size = UDim2.new(0, CW, 0, CH)
		end

		for _, card in ipairs({ refs.BountyCard, refs.TimeCard }) do
			if card then
				local icon = card:FindFirstChild("CardIcon")
				local titleLabel = card:FindFirstChild("CardTitle")
				local valueLabel = card:FindFirstChild("CardValue")
				if mobile then
					if icon then
						icon.Position = UDim2.new(0, 8, 0, 8)
						icon.Size = UDim2.new(0, 12, 0, 12)
					end
					if titleLabel then
						titleLabel.Position = UDim2.new(0, 24, 0, 8)
						titleLabel.Size = UDim2.new(1, -28, 0, 12)
						titleLabel.TextSize = 9
						titleLabel.TextXAlignment = Enum.TextXAlignment.Left
					end
					if valueLabel then
						valueLabel.Position = UDim2.new(0, 8, 0, 28)
						valueLabel.Size = UDim2.new(1, -12, 0, 20)
						valueLabel.TextSize = 12
						valueLabel.TextXAlignment = Enum.TextXAlignment.Left
					end
				else
					if icon then
						icon.Position = UDim2.new(0, 10, 0, 8)
						icon.Size = UDim2.new(0, 20, 0, 20)
					end
					if titleLabel then
						titleLabel.Position = UDim2.new(0, 34, 0, 8)
						titleLabel.Size = UDim2.new(1, -38, 0, 18)
						titleLabel.TextSize = 11
					end
					if valueLabel then
						valueLabel.Position = UDim2.new(0, 10, 0, 30)
						valueLabel.Size = UDim2.new(1, -14, 0, 24)
						valueLabel.TextSize = 16
					end
				end
			end
		end

		if refs.TargetInfoCard then
			local newCardW = math.floor(CW * 2 + GAP)
			local newCardH = math.floor(132 * scale)

			if mobile then
				local infoW = 108
				local layoutGap = 5
				local rightX = infoW + 14
				local availableW = math.max(w - rightX - 8, 150)
				newCardW = availableW
				newCardH = 104
				local mobileCardTopY = 72
				local mobileCardH = 70
				refs.TargetInfoCard.Position = UDim2.new(0, rightX, 0, mobileCardTopY + mobileCardH + 6)
			else
				refs.TargetInfoCard.Position = UDim2.new(0, CX, 0, CY + CH + GAP)
			end
			refs.TargetInfoCard.Size = UDim2.new(0, newCardW, 0, newCardH)

			local targetHeaderIcon = refs.TargetInfoCard:FindFirstChild("TargetHeaderIcon")
			if targetHeaderIcon then
				if mobile then
					targetHeaderIcon.Position = UDim2.new(0, 6, 0, 8)
					targetHeaderIcon.Size = UDim2.new(0, 12, 0, 12)
				else
					targetHeaderIcon.Position = UDim2.new(0, 10, 0, 8)
					targetHeaderIcon.Size = UDim2.new(0, 20, 0, 20)
				end
			end

			if refs.TargetTitle then
				if mobile then
					refs.TargetTitle.Position = UDim2.new(0, 22, 0, 8)
					refs.TargetTitle.Size = UDim2.new(1, -26, 0, 13)
				else
					refs.TargetTitle.Position = UDim2.new(0, 34, 0, 8)
					refs.TargetTitle.Size = UDim2.new(1, -38, 0, 18)
				end
				refs.TargetTitle.TextSize = mobile and 9 or math.max(math.floor(11 * textScale), 9)
			end

			local infoTextSize = mobile and 9 or math.max(math.floor(10 * textScale), 8)
			if refs.TargetName then
				refs.TargetName.TextSize = infoTextSize
			end
			if refs.TargetLevel then
				refs.TargetLevel.TextSize = infoTextSize
			end
			if refs.TargetHealth then
				refs.TargetHealth.TextSize = infoTextSize
			end
			if refs.TargetDistance then
				refs.TargetDistance.TextSize = infoTextSize
			end

			if mobile then
				if refs.TargetNameIco then
					refs.TargetNameIco.Position = UDim2.new(0, 8, 0, 28)
					refs.TargetNameIco.Size = UDim2.new(0, 10, 0, 10)
				end
				if refs.TargetName then
					refs.TargetName.Position = UDim2.new(0, 21, 0, 26)
					refs.TargetName.Size = UDim2.new(0.5, -23, 0, 14)
				end
				if refs.TargetLevelIco then
					refs.TargetLevelIco.Position = UDim2.new(0.5, 2, 0, 28)
					refs.TargetLevelIco.Size = UDim2.new(0, 10, 0, 10)
				end
				if refs.TargetLevel then
					refs.TargetLevel.Position = UDim2.new(0.5, 15, 0, 26)
					refs.TargetLevel.Size = UDim2.new(0.5, -18, 0, 14)
				end
				if refs.TargetHealthIco then
					refs.TargetHealthIco.Position = UDim2.new(0, 8, 0, 48)
					refs.TargetHealthIco.Size = UDim2.new(0, 10, 0, 10)
				end
				if refs.TargetHealth then
					refs.TargetHealth.Position = UDim2.new(0, 21, 0, 46)
					refs.TargetHealth.Size = UDim2.new(0.5, -23, 0, 14)
				end
				if refs.TargetDistanceIco then
					refs.TargetDistanceIco.Position = UDim2.new(0.5, 2, 0, 48)
					refs.TargetDistanceIco.Size = UDim2.new(0, 10, 0, 10)
				end
				if refs.TargetDistance then
					refs.TargetDistance.Position = UDim2.new(0.5, 15, 0, 46)
					refs.TargetDistance.Size = UDim2.new(0.5, -18, 0, 14)
				end
			else
				if refs.TargetNameIco then
					refs.TargetNameIco.Size = UDim2.new(0, 13, 0, 13)
				end
				if refs.TargetLevelIco then
					refs.TargetLevelIco.Size = UDim2.new(0, 13, 0, 13)
				end
				if refs.TargetHealthIco then
					refs.TargetHealthIco.Size = UDim2.new(0, 13, 0, 13)
				end
				if refs.TargetDistanceIco then
					refs.TargetDistanceIco.Size = UDim2.new(0, 13, 0, 13)
				end
				if refs.TargetName then
					refs.TargetName.Size = UDim2.new(0.5, -28, 0, 18)
				end
				if refs.TargetLevel then
					refs.TargetLevel.Size = UDim2.new(0.5, -28, 0, 18)
				end
				if refs.TargetHealth then
					refs.TargetHealth.Size = UDim2.new(0.5, -28, 0, 18)
				end
				if refs.TargetDistance then
					refs.TargetDistance.Size = UDim2.new(0.5, -28, 0, 18)
				end
			end

			if refs.TargetBtnDivider then
				refs.TargetBtnDivider.Position = UDim2.new(0, 8, 0, mobile and 66 or math.floor(76 * scale))
			end
			if refs.SkipBtn then
				local newBtnY = mobile and 72 or math.floor(82 * scale)
				local newBtnH = mobile and 18 or math.max(math.floor(26 * scale), 20)
				refs.SkipBtn.Position = UDim2.new(0, 8, 0, newBtnY)
				refs.SkipBtn.Size = UDim2.new(0, newCardW / 2 - 12, 0, newBtnH)
				refs.SkipBtn.TextSize = mobile and 8 or math.max(math.floor(11 * textScale), 9)
			end
			if refs.HopBtn then
				local newBtnY = mobile and 72 or math.floor(82 * scale)
				local newBtnH = mobile and 18 or math.max(math.floor(26 * scale), 20)
				refs.HopBtn.Position = UDim2.new(0, newCardW / 2 + 4, 0, newBtnY)
				refs.HopBtn.Size = UDim2.new(0, newCardW / 2 - 12, 0, newBtnH)
				refs.HopBtn.TextSize = mobile and 8 or math.max(math.floor(11 * textScale), 9)
			end
		end

		if refs.ExecStatusLbl then
			refs.ExecStatusLbl.TextSize = mobile and 9 or math.max(math.floor(9 * textScale), 7)
		end
		if refs.CreditLbl then
			refs.CreditLbl.TextSize = mobile and 10 or math.max(math.floor(10 * textScale), 8)
		end

		if refs.BotDivider then
			local bottomY = mobile and 204 or 314
			refs.BotDivider.Visible = not mobile
			refs.BotDivider.Position = UDim2.new(0, 0, 0, bottomY)
			if refs.ExecIcon then
				refs.ExecIcon.Visible = true
				refs.ExecIcon.Position = mobile and UDim2.new(0, 122, 0, 257) or UDim2.new(0, 12, 0, bottomY + 4)
				refs.ExecIcon.Size = mobile and UDim2.new(0, 10, 0, 10) or UDim2.new(0, 14, 0, 14)
			end
			if refs.ExecStatusLbl then
				refs.ExecStatusLbl.Visible = true
				refs.ExecStatusLbl.Position = mobile and UDim2.new(0, 134, 0, 256) or UDim2.new(0, 34, 0, bottomY + 4)
				refs.ExecStatusLbl.Size = mobile and UDim2.new(0, 70, 0, 12) or UDim2.new(0.56, 0, 0, 14)
			end
			if refs.CreditLbl then
				refs.CreditLbl.Position = mobile and UDim2.new(0, 0, 0, 256) or UDim2.new(0, 0, 0, bottomY + 4)
				refs.CreditLbl.Size = mobile and UDim2.new(1, -10, 0, 12) or UDim2.new(1, -12, 0, 14)
			end
		end
	end

	local ScreenGui = Instance.new("ScreenGui")
	ScreenGui.Name = "NatAovHub_AutoBounty"
	ScreenGui.Parent = CoreGui
	ScreenGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
	ScreenGui.ResetOnSpawn = false
	ScreenGui.DisplayOrder = 20
	refs.ScreenGui = ScreenGui

	local DropShadowHolder = Instance.new("Frame")
	DropShadowHolder.AnchorPoint = Vector2.new(0.5, 0.5)
	DropShadowHolder.BackgroundTransparency = 1
	DropShadowHolder.Name = "DropShadowHolder"
	DropShadowHolder.Parent = ScreenGui
	DropShadowHolder.Position = UDim2.new(0.5, 0, 0.5, 0)
	DropShadowHolder.Size = UDim2.new(0, 560, 0, 355)
	DropShadowHolder.ZIndex = 1
	refs.DropShadowHolder = DropShadowHolder

	local MainFrame = Instance.new("Frame")
	MainFrame.AnchorPoint = Vector2.new(0.5, 0.5)
	MainFrame.BackgroundColor3 = Color3.fromRGB(0, 90, 180)
	MainFrame.BackgroundTransparency = 0
	MainFrame.Name = "Main"
	MainFrame.Parent = DropShadowHolder
	MainFrame.Position = UDim2.new(0.5, 0, 0.5, 0)
	MainFrame.Size = UDim2.new(1, 0, 1, 0)
	MainFrame.ClipsDescendants = true
	refs.MainFrame = MainFrame

	Instance.new("UICorner", MainFrame).CornerRadius = UDim.new(0, 14)
	local MainStroke = Instance.new("UIStroke", MainFrame)
	MainStroke.Color = Color3.fromRGB(0, 140, 240)
	MainStroke.Thickness = 1.2
	local MainGradient = Instance.new("UIGradient", MainFrame)
	MainGradient.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(0, 60, 130)),
		ColorSequenceKeypoint.new(0.55, Color3.fromRGB(0, 110, 210)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(0, 160, 255)),
	})
	MainGradient.Rotation = 135

	local ToggleContainer = Instance.new("Frame", ScreenGui)
	ToggleContainer.Name = "ToggleUI"
	ToggleContainer.AnchorPoint = Vector2.new(0.5, 0)
	ToggleContainer.Position = UDim2.new(0.5, 0, 0, 6)
	ToggleContainer.Size = UDim2.new(0, 280, 0, 48)
	ToggleContainer.BackgroundColor3 = Color3.fromRGB(0, 80, 165)
	ToggleContainer.BackgroundTransparency = 0.2
	ToggleContainer.BorderSizePixel = 0
	ToggleContainer.ZIndex = 200
	ToggleContainer.ClipsDescendants = false
	refs.ToggleContainer = ToggleContainer

	Instance.new("UICorner", ToggleContainer).CornerRadius = UDim.new(0, 10)
	local toggleStroke = Instance.new("UIStroke", ToggleContainer)
	toggleStroke.Color = Color3.fromRGB(0, 150, 255)
	toggleStroke.Thickness = 1
	refs.toggleStroke = toggleStroke

	local toggleAvatar = Instance.new("Frame", ToggleContainer)
	toggleAvatar.AnchorPoint = Vector2.new(0, 0.5)
	toggleAvatar.Position = UDim2.new(0, 8, 0.5, 0)
	toggleAvatar.Size = UDim2.new(0, 32, 0, 32)
	toggleAvatar.BackgroundTransparency = 1
	toggleAvatar.BorderSizePixel = 0
	toggleAvatar.ZIndex = 201
	refs.toggleAvatar = toggleAvatar

	local avatarStroke = Instance.new("UIStroke", toggleAvatar)
	avatarStroke.Enabled = false
	refs.avatarStroke = avatarStroke

	local avatarLbl = Instance.new("ImageLabel", toggleAvatar)
	avatarLbl.Size = UDim2.new(1, 0, 1, 0)
	avatarLbl.BackgroundTransparency = 1
	avatarLbl.Image = "rbxassetid://120488231660846"
	avatarLbl.ScaleType = Enum.ScaleType.Fit
	avatarLbl.ZIndex = 202

	local toggleTitle = Instance.new("TextLabel", ToggleContainer)
	toggleTitle.BackgroundTransparency = 1
	toggleTitle.Position = UDim2.new(0, 48, 0, 6)
	toggleTitle.Size = UDim2.new(1, -80, 0, 20)
	toggleTitle.Text = "NatAov Hub Auto Bounty"
	toggleTitle.TextColor3 = Color3.fromRGB(255, 255, 255)
	toggleTitle.Font = Enum.Font.GothamBold
	toggleTitle.TextSize = 12
	toggleTitle.TextXAlignment = Enum.TextXAlignment.Left
	toggleTitle.ZIndex = 201
	refs.toggleTitle = toggleTitle

	local toggleSub = Instance.new("TextLabel", ToggleContainer)
	toggleSub.BackgroundTransparency = 1
	toggleSub.Position = UDim2.new(0, 48, 0, 26)
	toggleSub.Size = UDim2.new(1, -80, 0, 14)
	toggleSub.Text = "Click to hide UI | Running"
	toggleSub.TextColor3 = Color3.fromRGB(150, 205, 255)
	toggleSub.Font = Enum.Font.Gotham
	toggleSub.TextSize = 10
	toggleSub.TextXAlignment = Enum.TextXAlignment.Left
	toggleSub.ZIndex = 201
	refs.toggleSub = toggleSub

	local toggleIconFrame = Instance.new("Frame", ToggleContainer)
	toggleIconFrame.AnchorPoint = Vector2.new(1, 0.5)
	toggleIconFrame.Position = UDim2.new(1, -8, 0.5, 0)
	toggleIconFrame.Size = UDim2.new(0, 28, 0, 28)
	toggleIconFrame.BackgroundColor3 = Color3.fromRGB(0, 100, 190)
	toggleIconFrame.BorderSizePixel = 0
	toggleIconFrame.ZIndex = 201
	refs.toggleIconFrame = toggleIconFrame

	Instance.new("UICorner", toggleIconFrame).CornerRadius = UDim.new(0, 6)
	local toggleIconLbl = Instance.new("TextLabel", toggleIconFrame)
	toggleIconLbl.Size = UDim2.new(1, 0, 1, 0)
	toggleIconLbl.BackgroundTransparency = 1
	toggleIconLbl.Text = "▼"
	toggleIconLbl.TextColor3 = Color3.fromRGB(0, 200, 255)
	toggleIconLbl.Font = Enum.Font.GothamBold
	toggleIconLbl.TextSize = 12
	toggleIconLbl.ZIndex = 202
	refs.toggleIconLbl = toggleIconLbl

	local ToggleBtn = Instance.new("TextButton", ToggleContainer)
	ToggleBtn.Size = UDim2.new(1, 0, 1, 0)
	ToggleBtn.BackgroundTransparency = 1
	ToggleBtn.Text = ""
	ToggleBtn.ZIndex = 203

	local openTweenInfo = TweenInfo.new(0.35, Enum.EasingStyle.Back, Enum.EasingDirection.Out)
	local closeTweenInfo = TweenInfo.new(0.25, Enum.EasingStyle.Back, Enum.EasingDirection.In)

	local function OpenUI()
		if _animating then
			return
		end
		_animating = true
		guiVisible = true
		if Utils.IsMobile() then
			lastUIPosition = DEFAULT_UI_POSITION
		end
		DropShadowHolder.Visible = true
		DropShadowHolder.Position = lastUIPosition or DEFAULT_UI_POSITION
		local fullW, fullH = calcUISize()
		ApplyResponsive()
		DropShadowHolder.Size = UDim2.new(0, 1, 0, 1)
		local openTween = TweenService:Create(DropShadowHolder, openTweenInfo, { Size = UDim2.new(0, fullW, 0, fullH) })
		openTween:Play()
		openTween.Completed:Connect(function()
			ApplyResponsive()
			ApplyToggleLayout()
			DropShadowHolder.Position = lastUIPosition or DEFAULT_UI_POSITION
			_animating = false
		end)
		toggleSub.Text = "Click to hide UI | Running"
		toggleSub.TextColor3 = Color3.fromRGB(150, 205, 255)
		toggleIconLbl.Text = "▼"
		toggleIconLbl.TextColor3 = Color3.fromRGB(0, 200, 255)
		avatarStroke.Color = Color3.fromRGB(0, 185, 255)
	end

	local function CloseUI()
		if _animating then
			return
		end
		_animating = true
		guiVisible = false
		local closeTween = TweenService:Create(DropShadowHolder, closeTweenInfo, { Size = UDim2.new(0, 1, 0, 1) })
		closeTween:Play()
		closeTween.Completed:Connect(function()
			if not guiVisible then
				DropShadowHolder.Visible = false
				local fullW, fullH = calcUISize()
				if Utils.IsMobile() then
					lastUIPosition = DEFAULT_UI_POSITION
					DropShadowHolder.Position = DEFAULT_UI_POSITION
				end
				DropShadowHolder.Size = UDim2.new(0, fullW, 0, fullH)
				ApplyResponsive()
				ApplyToggleLayout()
			end
			_animating = false
		end)
		toggleSub.Text = "Click to show UI | Hidden"
		toggleSub.TextColor3 = Color3.fromRGB(130, 180, 255)
		toggleIconLbl.Text = "▲"
		toggleIconLbl.TextColor3 = Color3.fromRGB(140, 190, 255)
		avatarStroke.Color = Color3.fromRGB(120, 170, 255)
	end

	ToggleBtn.MouseButton1Click:Connect(function()
		if guiVisible then
			CloseUI()
		else
			OpenUI()
		end
	end)
	ToggleBtn.MouseEnter:Connect(function()
		TweenService:Create(ToggleContainer, TweenInfo.new(0.15), {
			BackgroundColor3 = Color3.fromRGB(0, 110, 200),
			BackgroundTransparency = 0.1,
		}):Play()
		TweenService:Create(toggleStroke, TweenInfo.new(0.15), {
			Color = Color3.fromRGB(0, 175, 255),
		}):Play()
	end)
	ToggleBtn.MouseLeave:Connect(function()
		TweenService:Create(ToggleContainer, TweenInfo.new(0.15), {
			BackgroundColor3 = Color3.fromRGB(0, 80, 165),
			BackgroundTransparency = 0.2,
		}):Play()
		TweenService:Create(toggleStroke, TweenInfo.new(0.15), {
			Color = Color3.fromRGB(0, 150, 255),
		}):Play()
	end)

	ApplyResponsive()
	ApplyToggleLayout()

	Camera:GetPropertyChangedSignal("ViewportSize"):Connect(function()
		local newW, newH = calcUISize()
		if guiVisible and not _animating then
			TweenService:Create(DropShadowHolder, TweenInfo.new(0.35, Enum.EasingStyle.Quint), {
				Size = UDim2.new(0, newW, 0, newH),
			}):Play()
			DropShadowHolder.Position = lastUIPosition or DEFAULT_UI_POSITION
		end
		ApplyResponsive()
		ApplyToggleLayout()
	end)

	local AvatarCircle = Instance.new("Frame", MainFrame)
	AvatarCircle.AnchorPoint = Vector2.new(0, 0.5)
	AvatarCircle.Position = UDim2.new(0, 16, 0, 54)
	AvatarCircle.Size = UDim2.new(0, 62, 0, 62)
	AvatarCircle.BackgroundColor3 = Color3.fromRGB(0, 95, 190)
	refs.AvatarCircle = AvatarCircle

	Instance.new("UICorner", AvatarCircle).CornerRadius = UDim.new(1, 0)
	local AvatarStroke = Instance.new("UIStroke", AvatarCircle)
	AvatarStroke.Color = Color3.fromRGB(230, 240, 255)
	AvatarStroke.Thickness = 2

	local HoloGradient = Instance.new("UIGradient", AvatarCircle)
	HoloGradient.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(0, 95, 190)),
		ColorSequenceKeypoint.new(0.5, Color3.fromRGB(0, 140, 240)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(0, 95, 190)),
	})
	HoloGradient.Rotation = 45

	local AvatarLabel = Instance.new("TextLabel", AvatarCircle)
	AvatarLabel.Size = UDim2.new(1, 0, 1, 0)
	AvatarLabel.BackgroundTransparency = 1
	AvatarLabel.Text = "NA"
	AvatarLabel.TextColor3 = Color3.fromRGB(0, 200, 255)
	AvatarLabel.Font = Enum.Font.GothamBold
	AvatarLabel.TextSize = 26
	refs.AvatarLabel = AvatarLabel

	local HubTitle = Instance.new("TextLabel", MainFrame)
	HubTitle.AnchorPoint = Vector2.new(0, 0)
	HubTitle.Position = UDim2.new(0, 92, 0, 20)
	HubTitle.Size = UDim2.new(0, 340, 0, 26)
	HubTitle.BackgroundTransparency = 1
	HubTitle.Text = "NatAov Hub Auto Bounty"
	HubTitle.TextColor3 = Color3.fromRGB(255, 255, 255)
	HubTitle.Font = Enum.Font.GothamBold
	HubTitle.TextSize = 17
	HubTitle.TextXAlignment = Enum.TextXAlignment.Left
	refs.HubTitle = HubTitle

	local HubSub = Instance.new("TextLabel", MainFrame)
	HubSub.AnchorPoint = Vector2.new(0, 0)
	HubSub.Position = UDim2.new(0, 92, 0, 48)
	HubSub.Size = UDim2.new(0.62, 0, 0, 30)
	HubSub.BackgroundTransparency = 1
	HubSub.Text = "NatAov Hub - Auto Farm Bounty. Auto hunt bounty, skip bad targets, hop server when needed."
	HubSub.TextColor3 = Color3.fromRGB(160, 215, 255)
	HubSub.Font = Enum.Font.Gotham
	HubSub.TextSize = 10
	HubSub.TextXAlignment = Enum.TextXAlignment.Left
	HubSub.TextYAlignment = Enum.TextYAlignment.Top
	HubSub.TextWrapped = true
	refs.HubSub = HubSub

	local HDivider = Instance.new("Frame", MainFrame)
	HDivider.BackgroundColor3 = Color3.fromRGB(0, 130, 240)
	HDivider.BorderSizePixel = 0
	HDivider.Position = UDim2.new(0, 0, 0, 96)
	HDivider.Size = UDim2.new(1, 0, 0, 1)
	refs.HDivider = HDivider

	local StatusDot = Instance.new("Frame", MainFrame)
	StatusDot.Size = UDim2.new(0, 8, 0, 8)
	StatusDot.Position = UDim2.new(0, 92, 0, 80)
	StatusDot.BackgroundColor3 = Color3.fromRGB(0, 195, 255)
	StatusDot.BorderSizePixel = 0
	refs.StatusDot = StatusDot

	Instance.new("UICorner", StatusDot).CornerRadius = UDim.new(1, 0)
	local StatusLbl = Instance.new("TextLabel", MainFrame)
	StatusLbl.Position = UDim2.new(0, 106, 0, 78)
	StatusLbl.Size = UDim2.new(0, 120, 0, 16)
	StatusLbl.BackgroundTransparency = 1
	StatusLbl.Text = "RUNNING"
	StatusLbl.TextColor3 = Color3.fromRGB(0, 195, 255)
	StatusLbl.Font = Enum.Font.GothamBold
	StatusLbl.TextSize = 10
	StatusLbl.TextXAlignment = Enum.TextXAlignment.Left
	refs.StatusLbl = StatusLbl

	local InfoPanel = Instance.new("Frame", MainFrame)
	InfoPanel.BackgroundColor3 = Color3.fromRGB(0, 85, 175)
	InfoPanel.BorderSizePixel = 0
	InfoPanel.Position = UDim2.new(0, 10, 0, 110)
	InfoPanel.Size = UDim2.new(0, 148, 0, 175)
	refs.InfoPanel = InfoPanel

	Instance.new("UICorner", InfoPanel).CornerRadius = UDim.new(0, 8)
	local InfoTitle = Instance.new("TextLabel", InfoPanel)
	InfoTitle.BackgroundTransparency = 1
	InfoTitle.Position = UDim2.new(0, 10, 0, 7)
	InfoTitle.Size = UDim2.new(1, -10, 0, 16)
	InfoTitle.Text = "Player Info"
	InfoTitle.TextColor3 = Color3.fromRGB(255, 255, 255)
	InfoTitle.Font = Enum.Font.GothamBold
	InfoTitle.TextSize = 12
	InfoTitle.TextXAlignment = Enum.TextXAlignment.Left
	refs.InfoTitle = InfoTitle

	local function MakeInfoRow(parent, yOff, label, color, iconName)
		local frame = Instance.new("Frame", parent)
		frame.BackgroundTransparency = 1
		frame.Position = UDim2.new(0, 10, 0, yOff)
		frame.Size = UDim2.new(1, -10, 0, 20)

		if iconName and Icons[iconName] then
			local icon = Instance.new("ImageLabel", frame)
			icon.BackgroundTransparency = 1
			icon.Position = UDim2.new(0, 0, 0, 2)
			icon.Size = UDim2.new(0, 16, 0, 16)
			icon.Image = Icons[iconName]
			icon.ImageColor3 = color or Color3.fromRGB(0, 200, 255)
		end

		local row = Instance.new("TextLabel", frame)
		row.BackgroundTransparency = 1
		row.Position = UDim2.new(0, iconName and 20 or 0, 0, 0)
		row.Size = UDim2.new(1, iconName and -20 or 0, 1, 0)
		row.Text = label
		row.TextColor3 = color or Color3.fromRGB(0, 200, 255)
		row.Font = Enum.Font.GothamBold
		row.TextSize = 11
		row.TextXAlignment = Enum.TextXAlignment.Left
		row.TextYAlignment = Enum.TextYAlignment.Center
		return row
	end

	refs.InfoBounty = MakeInfoRow(InfoPanel, 28, "Bounty: --", Color3.fromRGB(0, 185, 255), "coins")
	refs.InfoRace = MakeInfoRow(InfoPanel, 52, "Race: --", Color3.fromRGB(0, 200, 255), "user")
	refs.InfoLevel = MakeInfoRow(InfoPanel, 76, "Level: --", Color3.fromRGB(255, 255, 255), "star")
	refs.InfoHealth = MakeInfoRow(InfoPanel, 100, "Health: 100%", Color3.fromRGB(0, 175, 255), "heart")

	local InfoDivider = Instance.new("Frame", InfoPanel)
	InfoDivider.BackgroundColor3 = Color3.fromRGB(0, 130, 240)
	InfoDivider.BorderSizePixel = 0
	InfoDivider.Position = UDim2.new(0, 8, 0, 122)
	InfoDivider.Size = UDim2.new(1, -16, 0, 1)
	refs.InfoDivider = InfoDivider

	refs.InfoMelee = MakeInfoRow(InfoPanel, 128, "Ping: --", Color3.fromRGB(0, 190, 255), "activity")
	refs.InfoFPS = MakeInfoRow(InfoPanel, 150, "FPS: --", Color3.fromRGB(0, 200, 255), "crosshair")
	refs.InfoKill = MakeInfoRow(InfoPanel, 172, "Kills: 0", Color3.fromRGB(0, 180, 255), "swords")

	InfoPanel.Size = UDim2.new(0, 148, 0, 198)

	local function MakeCard(parent, x, y, w, h, accentColor, iconName, titleText, valueText)
		local card = Instance.new("Frame", parent)
		card.BackgroundColor3 = Color3.fromRGB(0, 85, 175)
		card.BorderSizePixel = 0
		card.Position = UDim2.new(0, x, 0, y)
		card.Size = UDim2.new(0, w, 0, h)
		Instance.new("UICorner", card).CornerRadius = UDim.new(0, 8)

		local iconLbl = Instance.new("ImageLabel", card)
		iconLbl.Name = "CardIcon"
		iconLbl.BackgroundTransparency = 1
		iconLbl.Position = UDim2.new(0, 10, 0, 8)
		iconLbl.Size = UDim2.new(0, 20, 0, 20)
		iconLbl.Image = Icons[iconName] or "rbxassetid://0"
		iconLbl.ImageColor3 = accentColor

		local titleLbl = Instance.new("TextLabel", card)
		titleLbl.Name = "CardTitle"
		titleLbl.BackgroundTransparency = 1
		titleLbl.Position = UDim2.new(0, 34, 0, 8)
		titleLbl.Size = UDim2.new(1, -38, 0, 18)
		titleLbl.Text = titleText
		titleLbl.TextColor3 = accentColor
		titleLbl.Font = Enum.Font.GothamBold
		titleLbl.TextSize = 11
		titleLbl.TextXAlignment = Enum.TextXAlignment.Left

		local valueLbl = Instance.new("TextLabel", card)
		valueLbl.Name = "CardValue"
		valueLbl.BackgroundTransparency = 1
		valueLbl.Position = UDim2.new(0, 10, 0, 30)
		valueLbl.Size = UDim2.new(1, -14, 0, 24)
		valueLbl.Text = valueText
		valueLbl.TextColor3 = Color3.fromRGB(255, 255, 255)
		valueLbl.Font = Enum.Font.GothamBold
		valueLbl.TextSize = 16
		valueLbl.TextXAlignment = Enum.TextXAlignment.Left

		return card, valueLbl
	end

	refs.BountyCard, refs.CardBountyVal =
		MakeCard(MainFrame, CX, CY, CW, CH, Color3.fromRGB(0, 185, 255), "coins", "Bounty Earned", "0")
	refs.TimeCard, refs.CardTimeVal =
		MakeCard(MainFrame, CX + CW + GAP, CY, CW, CH, Color3.fromRGB(0, 190, 255), "clock", "Time Elapsed", "0H 0M 0S")

	local TargetInfoCard = Instance.new("Frame", MainFrame)
	TargetInfoCard.BackgroundColor3 = Color3.fromRGB(0, 85, 175)
	TargetInfoCard.BorderSizePixel = 0
	TargetInfoCard.Position = UDim2.new(0, CX, 0, CY + CH + GAP)
	TargetInfoCard.Size = UDim2.new(0, CW * 2 + GAP, 0, 132)
	refs.TargetInfoCard = TargetInfoCard

	Instance.new("UICorner", TargetInfoCard).CornerRadius = UDim.new(0, 8)
	local TargetIcon = Instance.new("ImageLabel", TargetInfoCard)
	TargetIcon.Name = "TargetHeaderIcon"
	TargetIcon.BackgroundTransparency = 1
	TargetIcon.Position = UDim2.new(0, 10, 0, 8)
	TargetIcon.Size = UDim2.new(0, 20, 0, 20)
	TargetIcon.Image = Icons["target"]
	TargetIcon.ImageColor3 = Color3.fromRGB(0, 170, 255)

	local TargetTitle = Instance.new("TextLabel", TargetInfoCard)
	TargetTitle.BackgroundTransparency = 1
	TargetTitle.Position = UDim2.new(0, 34, 0, 8)
	TargetTitle.Size = UDim2.new(1, -38, 0, 18)
	TargetTitle.Text = "Target Info"
	TargetTitle.TextColor3 = Color3.fromRGB(0, 170, 255)
	TargetTitle.Font = Enum.Font.GothamBold
	TargetTitle.TextSize = 11
	TargetTitle.TextXAlignment = Enum.TextXAlignment.Left
	refs.TargetTitle = TargetTitle

	local TargetNameIco = Instance.new("ImageLabel", TargetInfoCard)
	TargetNameIco.BackgroundTransparency = 1
	TargetNameIco.Position = UDim2.new(0, 10, 0, 32)
	TargetNameIco.Size = UDim2.new(0, 13, 0, 13)
	TargetNameIco.Image = Icons["user"]
	TargetNameIco.ImageColor3 = Color3.fromRGB(0, 200, 255)
	TargetNameIco.Active = false
	refs.TargetNameIco = TargetNameIco

	refs.TargetName = Instance.new("TextLabel", TargetInfoCard)
	refs.TargetName.BackgroundTransparency = 1
	refs.TargetName.Position = UDim2.new(0, 26, 0, 30)
	refs.TargetName.Size = UDim2.new(0.5, -28, 0, 18)
	refs.TargetName.Text = "Name: --"
	refs.TargetName.TextColor3 = Color3.fromRGB(215, 235, 255)
	refs.TargetName.Font = Enum.Font.GothamBold
	refs.TargetName.TextSize = 10
	refs.TargetName.TextXAlignment = Enum.TextXAlignment.Left

	local TargetLevelIco = Instance.new("ImageLabel", TargetInfoCard)
	TargetLevelIco.BackgroundTransparency = 1
	TargetLevelIco.Position = UDim2.new(0.5, 2, 0, 32)
	TargetLevelIco.Size = UDim2.new(0, 13, 0, 13)
	TargetLevelIco.Image = Icons["star"]
	TargetLevelIco.ImageColor3 = Color3.fromRGB(0, 200, 255)
	TargetLevelIco.Active = false
	refs.TargetLevelIco = TargetLevelIco

	refs.TargetLevel = Instance.new("TextLabel", TargetInfoCard)
	refs.TargetLevel.BackgroundTransparency = 1
	refs.TargetLevel.Position = UDim2.new(0.5, 18, 0, 30)
	refs.TargetLevel.Size = UDim2.new(0.5, -28, 0, 18)
	refs.TargetLevel.Text = "Level: --"
	refs.TargetLevel.TextColor3 = Color3.fromRGB(190, 230, 255)
	refs.TargetLevel.Font = Enum.Font.GothamBold
	refs.TargetLevel.TextSize = 10
	refs.TargetLevel.TextXAlignment = Enum.TextXAlignment.Left

	local TargetHealthIco = Instance.new("ImageLabel", TargetInfoCard)
	TargetHealthIco.BackgroundTransparency = 1
	TargetHealthIco.Position = UDim2.new(0, 10, 0, 52)
	TargetHealthIco.Size = UDim2.new(0, 13, 0, 13)
	TargetHealthIco.Image = Icons["heart"]
	TargetHealthIco.ImageColor3 = Color3.fromRGB(0, 175, 255)
	TargetHealthIco.Active = false
	refs.TargetHealthIco = TargetHealthIco

	refs.TargetHealth = Instance.new("TextLabel", TargetInfoCard)
	refs.TargetHealth.BackgroundTransparency = 1
	refs.TargetHealth.Position = UDim2.new(0, 26, 0, 50)
	refs.TargetHealth.Size = UDim2.new(0.5, -28, 0, 18)
	refs.TargetHealth.Text = "Health: --"
	refs.TargetHealth.TextColor3 = Color3.fromRGB(180, 225, 255)
	refs.TargetHealth.Font = Enum.Font.GothamBold
	refs.TargetHealth.TextSize = 10
	refs.TargetHealth.TextXAlignment = Enum.TextXAlignment.Left

	local TargetDistanceIco = Instance.new("ImageLabel", TargetInfoCard)
	TargetDistanceIco.BackgroundTransparency = 1
	TargetDistanceIco.Position = UDim2.new(0.5, 2, 0, 52)
	TargetDistanceIco.Size = UDim2.new(0, 13, 0, 13)
	TargetDistanceIco.Image = Icons["ruler"]
	TargetDistanceIco.ImageColor3 = Color3.fromRGB(155, 205, 255)
	TargetDistanceIco.Active = false
	refs.TargetDistanceIco = TargetDistanceIco

	refs.TargetDistance = Instance.new("TextLabel", TargetInfoCard)
	refs.TargetDistance.BackgroundTransparency = 1
	refs.TargetDistance.Position = UDim2.new(0.5, 18, 0, 50)
	refs.TargetDistance.Size = UDim2.new(0.5, -28, 0, 18)
	refs.TargetDistance.Text = "Distance: --"
	refs.TargetDistance.TextColor3 = Color3.fromRGB(175, 220, 255)
	refs.TargetDistance.Font = Enum.Font.GothamBold
	refs.TargetDistance.TextSize = 10
	refs.TargetDistance.TextXAlignment = Enum.TextXAlignment.Left

	local BotDivider = Instance.new("Frame", MainFrame)
	BotDivider.BackgroundColor3 = Color3.fromRGB(0, 130, 240)
	BotDivider.BorderSizePixel = 0
	BotDivider.Position = UDim2.new(0, 0, 0, 314)
	BotDivider.Size = UDim2.new(1, 0, 0, 1)
	refs.BotDivider = BotDivider

	refs.ExecIcon = Instance.new("ImageLabel", MainFrame)
	refs.ExecIcon.BackgroundTransparency = 1
	refs.ExecIcon.Position = UDim2.new(0, 12, 0, 318)
	refs.ExecIcon.Size = UDim2.new(0, 14, 0, 14)
	refs.ExecIcon.Image = Icons["activity"]
	refs.ExecIcon.ImageColor3 = Color3.fromRGB(0, 190, 255)

	refs.ExecStatusLbl = Instance.new("TextLabel", MainFrame)
	refs.ExecStatusLbl.BackgroundTransparency = 1
	refs.ExecStatusLbl.Position = UDim2.new(0, 34, 0, 318)
	refs.ExecStatusLbl.Size = UDim2.new(0.56, 0, 0, 14)
	refs.ExecStatusLbl.Text = "Executor: Loading..."
	refs.ExecStatusLbl.TextColor3 = Color3.fromRGB(140, 195, 255)
	refs.ExecStatusLbl.Font = Enum.Font.Gotham
	refs.ExecStatusLbl.TextSize = 9
	refs.ExecStatusLbl.TextXAlignment = Enum.TextXAlignment.Left

	refs.CreditLbl = Instance.new("TextLabel", MainFrame)
	refs.CreditLbl.BackgroundTransparency = 1
	refs.CreditLbl.Position = UDim2.new(0, 0, 0, 318)
	refs.CreditLbl.Size = UDim2.new(1, -12, 0, 14)
	refs.CreditLbl.Text = "NatAov Hub"
	refs.CreditLbl.TextColor3 = Color3.fromRGB(0, 210, 255)
	refs.CreditLbl.Font = Enum.Font.Gotham
	refs.CreditLbl.TextSize = 10
	refs.CreditLbl.TextXAlignment = Enum.TextXAlignment.Right

	local CreditStroke = Instance.new("UIStroke", refs.CreditLbl)
	CreditStroke.Color = Color3.fromRGB(0, 200, 255)
	CreditStroke.Thickness = 0.5

	local function MakeBtn(parent, x, y, w, text, bgColor)
		local btn = Instance.new("TextButton", parent)
		btn.BackgroundColor3 = bgColor or Color3.fromRGB(0, 70, 150)
		btn.BorderSizePixel = 0
		btn.Position = UDim2.new(0, x, 0, y)
		btn.Size = UDim2.new(0, w, 0, 28)
		btn.Text = text
		btn.TextColor3 = Color3.fromRGB(255, 255, 255)
		btn.Font = Enum.Font.GothamBold
		btn.TextSize = 11
		Instance.new("UICorner", btn).CornerRadius = UDim.new(0, 6)
		return btn
	end

	refs.TargetBtnDivider = Instance.new("Frame", TargetInfoCard)
	refs.TargetBtnDivider.BackgroundColor3 = Color3.fromRGB(0, 130, 240)
	refs.TargetBtnDivider.BorderSizePixel = 0
	refs.TargetBtnDivider.Position = UDim2.new(0, 8, 0, 88)
	refs.TargetBtnDivider.Size = UDim2.new(1, -16, 0, 1)

	refs.SkipBtn = MakeBtn(TargetInfoCard, 8, 96, (CW * 2 + GAP) / 2 - 12, "   SKIP PLAYER", Color3.fromRGB(0, 80, 170))
	refs.HopBtn = MakeBtn(
		TargetInfoCard,
		(CW * 2 + GAP) / 2 + 4,
		96,
		(CW * 2 + GAP) / 2 - 12,
		"   HOP SERVER",
		Color3.fromRGB(0, 60, 140)
	)

	local SkipBtnIcon = Instance.new("ImageLabel", refs.SkipBtn)
	SkipBtnIcon.BackgroundTransparency = 1
	SkipBtnIcon.Position = UDim2.new(0, 8, 0.5, -8)
	SkipBtnIcon.Size = UDim2.new(0, 16, 0, 16)
	SkipBtnIcon.Image = "rbxassetid://10734961809"
	SkipBtnIcon.ImageColor3 = Color3.fromRGB(0, 200, 255)
	SkipBtnIcon.ZIndex = refs.SkipBtn.ZIndex + 1
	SkipBtnIcon.Active = false

	local HopBtnIcon = Instance.new("ImageLabel", refs.HopBtn)
	HopBtnIcon.BackgroundTransparency = 1
	HopBtnIcon.Position = UDim2.new(0, 8, 0.5, -8)
	HopBtnIcon.Size = UDim2.new(0, 16, 0, 16)
	HopBtnIcon.Image = "rbxassetid://10734953451"
	HopBtnIcon.ImageColor3 = Color3.fromRGB(0, 150, 255)
	HopBtnIcon.ZIndex = refs.HopBtn.ZIndex + 1
	HopBtnIcon.Active = false

	local function AddBtnStroke(btn, color)
		local s = Instance.new("UIStroke", btn)
		s.Color = color
		s.Thickness = 1.2
	end
	AddBtnStroke(refs.SkipBtn, Color3.fromRGB(0, 200, 255))
	AddBtnStroke(refs.HopBtn, Color3.fromRGB(0, 140, 255))

	ApplyResponsive()
	ApplyToggleLayout()

	local dragging, dragInput, dragStart, startPos
	local function update(input)
		if Utils.IsMobile() then
			return
		end
		local delta = input.Position - dragStart
		DropShadowHolder.Position =
			UDim2.new(startPos.X.Scale, startPos.X.Offset + delta.X, startPos.Y.Scale, startPos.Y.Offset + delta.Y)
		lastUIPosition = DropShadowHolder.Position
	end

	MainFrame.InputBegan:Connect(function(input)
		if Utils.IsMobile() then
			return
		end
		if input.UserInputType == Enum.UserInputType.MouseButton1 then
			dragging = true
			dragStart = input.Position
			startPos = DropShadowHolder.Position
			input.Changed:Connect(function()
				if input.UserInputState == Enum.UserInputState.End then
					dragging = false
				end
			end)
		end
	end)
	MainFrame.InputChanged:Connect(function(input)
		if Utils.IsMobile() then
			return
		end
		if input.UserInputType == Enum.UserInputType.MouseMovement then
			dragInput = input
		end
	end)
	UserInputService.InputChanged:Connect(function(input)
		if Utils.IsMobile() then
			return
		end
		if input == dragInput and dragging then
			update(input)
		end
	end)

	refs.HopBtn.MouseButton1Click:Connect(function()
		if isHopping then
			return
		end
		refs.HopBtn.Text = "   HOPPING..."
		setHopping(true)
		stopBypass = true
		SafeHop()
		task.spawn(function()
			while isHopping do
				task.wait(0.2)
			end
			refs.HopBtn.Text = "   HOP SERVER"
		end)
	end)

	local skipBtnCooldown = false
	refs.SkipBtn.MouseButton1Click:Connect(function()
		if skipBtnCooldown then
			return
		end
		skipBtnCooldown = true
		refs.SkipBtn.Text = "   SKIPPING..."
		if SkipPlayer then
			SkipPlayer()
		end
		task.delay(1, function()
			refs.SkipBtn.Text = "   SKIP PLAYER"
			skipBtnCooldown = false
		end)
	end)
end

local Notify, Move, Buff, Combat, Hunt, Hop, Webhook

local Bounty = {
	startTime = os.time(),
	initial = nil,
	last = nil,
	earned = 0,
}

-- ============================================================================
-- 8) NOTIFY — thông báo hop server / server trống
-- ============================================================================
Notify = {}
Notify.Refs = {}

function Notify.Init()
	local parent = UI.Refs.ScreenGui or CoreGui
	local refs = Notify.Refs

	local HopNotifyFrame = Instance.new("Frame", parent)
	HopNotifyFrame.Name = "HopNotify"
	HopNotifyFrame.AnchorPoint = Vector2.new(1, 1)
	HopNotifyFrame.Position = UDim2.new(1, 20, 1, -16)
	HopNotifyFrame.Size = UDim2.new(0, 300, 0, 80)
	HopNotifyFrame.BackgroundColor3 = Color3.fromRGB(0, 90, 180)
	HopNotifyFrame.BorderSizePixel = 0
	HopNotifyFrame.ZIndex = 50
	HopNotifyFrame.Visible = false
	refs.HopNotifyFrame = HopNotifyFrame

	Instance.new("UICorner", HopNotifyFrame).CornerRadius = UDim.new(0, 12)
	local HopNotifyStroke = Instance.new("UIStroke", HopNotifyFrame)
	HopNotifyStroke.Color = Color3.fromRGB(0, 140, 255)
	HopNotifyStroke.Thickness = 1.8

	local HopNotifyGrad = Instance.new("UIGradient", HopNotifyFrame)
	HopNotifyGrad.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(0, 70, 150)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(0, 90, 180)),
	})
	HopNotifyGrad.Rotation = 90

	local HopNotifyIcon = Instance.new("ImageLabel", HopNotifyFrame)
	HopNotifyIcon.BackgroundTransparency = 1
	HopNotifyIcon.Position = UDim2.new(0, 14, 0.5, -14)
	HopNotifyIcon.Size = UDim2.new(0, 28, 0, 28)
	HopNotifyIcon.Image = "rbxassetid://10734953451"
	HopNotifyIcon.ImageColor3 = Color3.fromRGB(0, 150, 255)
	HopNotifyIcon.ZIndex = 51

	local HopNotifyTitle = Instance.new("TextLabel", HopNotifyFrame)
	HopNotifyTitle.BackgroundTransparency = 1
	HopNotifyTitle.Position = UDim2.new(0, 52, 0, 10)
	HopNotifyTitle.Size = UDim2.new(1, -100, 0, 22)
	HopNotifyTitle.Text = "HOPPING SERVER"
	HopNotifyTitle.TextColor3 = Color3.fromRGB(150, 210, 255)
	HopNotifyTitle.Font = Enum.Font.GothamBold
	HopNotifyTitle.TextSize = 13
	HopNotifyTitle.TextXAlignment = Enum.TextXAlignment.Left
	HopNotifyTitle.ZIndex = 51
	refs.HopNotifyTitle = HopNotifyTitle

	local HopNotifySub = Instance.new("TextLabel", HopNotifyFrame)
	HopNotifySub.BackgroundTransparency = 1
	HopNotifySub.Position = UDim2.new(0, 52, 0, 32)
	HopNotifySub.Size = UDim2.new(1, -60, 0, 16)
	HopNotifySub.Text = "Finding better server..."
	HopNotifySub.TextColor3 = Color3.fromRGB(160, 210, 255)
	HopNotifySub.Font = Enum.Font.Gotham
	HopNotifySub.TextSize = 10
	HopNotifySub.TextXAlignment = Enum.TextXAlignment.Left
	HopNotifySub.ZIndex = 51
	refs.HopNotifySub = HopNotifySub

	local HopCountBadge = Instance.new("Frame", HopNotifyFrame)
	HopCountBadge.BackgroundColor3 = Color3.fromRGB(0, 140, 255)
	HopCountBadge.BorderSizePixel = 0
	HopCountBadge.Position = UDim2.new(1, -52, 0.5, -16)
	HopCountBadge.Size = UDim2.new(0, 38, 0, 32)
	HopCountBadge.ZIndex = 51
	refs.HopCountBadge = HopCountBadge

	Instance.new("UICorner", HopCountBadge).CornerRadius = UDim.new(0, 8)
	local HopCountLbl = Instance.new("TextLabel", HopCountBadge)
	HopCountLbl.BackgroundTransparency = 1
	HopCountLbl.Size = UDim2.new(1, 0, 1, 0)
	HopCountLbl.Text = "3"
	HopCountLbl.TextColor3 = Color3.fromRGB(255, 255, 255)
	HopCountLbl.Font = Enum.Font.GothamBold
	HopCountLbl.TextSize = 16
	HopCountLbl.ZIndex = 52
	refs.HopCountLbl = HopCountLbl

	local HopProgressBg = Instance.new("Frame", HopNotifyFrame)
	HopProgressBg.BackgroundColor3 = Color3.fromRGB(0, 70, 150)
	HopProgressBg.BorderSizePixel = 0
	HopProgressBg.Position = UDim2.new(0, 14, 1, -10)
	HopProgressBg.Size = UDim2.new(1, -28, 0, 4)
	HopProgressBg.ZIndex = 51
	refs.HopProgressBg = HopProgressBg

	Instance.new("UICorner", HopProgressBg).CornerRadius = UDim.new(1, 0)
	local HopProgressBar = Instance.new("Frame", HopProgressBg)
	HopProgressBar.BackgroundColor3 = Color3.fromRGB(0, 150, 255)
	HopProgressBar.BorderSizePixel = 0
	HopProgressBar.Position = UDim2.new(0, 0, 0, 0)
	HopProgressBar.Size = UDim2.new(1, 0, 1, 0)
	HopProgressBar.ZIndex = 52
	refs.HopProgressBar = HopProgressBar

	Instance.new("UICorner", HopProgressBar).CornerRadius = UDim.new(1, 0)

	local EmptyNotifyFrame = Instance.new("Frame", parent)
	EmptyNotifyFrame.Name = "EmptyServerNotify"
	EmptyNotifyFrame.AnchorPoint = Vector2.new(0.5, 1)
	EmptyNotifyFrame.Position = UDim2.new(0.5, 0, 1.2, 0)
	EmptyNotifyFrame.Size = UDim2.new(0, 320, 0, 72)
	EmptyNotifyFrame.BackgroundColor3 = Color3.fromRGB(0, 90, 180)
	EmptyNotifyFrame.BorderSizePixel = 0
	EmptyNotifyFrame.ZIndex = 60
	EmptyNotifyFrame.Visible = false
	refs.EmptyNotifyFrame = EmptyNotifyFrame

	Instance.new("UICorner", EmptyNotifyFrame).CornerRadius = UDim.new(0, 12)
	local emptyStroke = Instance.new("UIStroke", EmptyNotifyFrame)
	emptyStroke.Color = Color3.fromRGB(0, 185, 255)
	emptyStroke.Thickness = 1.8

	local emptyGrad = Instance.new("UIGradient", EmptyNotifyFrame)
	emptyGrad.Color = ColorSequence.new({
		ColorSequenceKeypoint.new(0, Color3.fromRGB(0, 80, 160)),
		ColorSequenceKeypoint.new(1, Color3.fromRGB(0, 90, 180)),
	})
	emptyGrad.Rotation = 90

	local emptyIcon = Instance.new("TextLabel", EmptyNotifyFrame)
	emptyIcon.BackgroundTransparency = 1
	emptyIcon.Position = UDim2.new(0, 12, 0.5, -16)
	emptyIcon.Size = UDim2.new(0, 32, 0, 32)
	emptyIcon.Text = "!"
	emptyIcon.TextScaled = true
	emptyIcon.ZIndex = 61

	local emptyTitle = Instance.new("TextLabel", EmptyNotifyFrame)
	emptyTitle.BackgroundTransparency = 1
	emptyTitle.Position = UDim2.new(0, 52, 0, 8)
	emptyTitle.Size = UDim2.new(1, -60, 0, 22)
	emptyTitle.Text = "SERVER EMPTY"
	emptyTitle.TextColor3 = Color3.fromRGB(0, 190, 255)
	emptyTitle.Font = Enum.Font.GothamBold
	emptyTitle.TextSize = 13
	emptyTitle.TextXAlignment = Enum.TextXAlignment.Left
	emptyTitle.ZIndex = 61

	local emptySub = Instance.new("TextLabel", EmptyNotifyFrame)
	emptySub.BackgroundTransparency = 1
	emptySub.Position = UDim2.new(0, 52, 0, 32)
	emptySub.Size = UDim2.new(1, -60, 0, 16)
	emptySub.Text = "Switching server..."
	emptySub.TextColor3 = Color3.fromRGB(180, 215, 255)
	emptySub.Font = Enum.Font.Gotham
	emptySub.TextSize = 10
	emptySub.TextXAlignment = Enum.TextXAlignment.Left
	emptySub.ZIndex = 61
	refs.emptySub = emptySub

	local emptyPingBg = Instance.new("Frame", EmptyNotifyFrame)
	emptyPingBg.BackgroundColor3 = Color3.fromRGB(0, 80, 160)
	emptyPingBg.BorderSizePixel = 0
	emptyPingBg.Position = UDim2.new(0, 12, 1, -8)
	emptyPingBg.Size = UDim2.new(1, -24, 0, 4)
	emptyPingBg.ZIndex = 61

	Instance.new("UICorner", emptyPingBg).CornerRadius = UDim.new(1, 0)
	local emptyBar = Instance.new("Frame", emptyPingBg)
	emptyBar.BackgroundColor3 = Color3.fromRGB(0, 185, 255)
	emptyBar.BorderSizePixel = 0
	emptyBar.Position = UDim2.new(0, 0, 0, 0)
	emptyBar.Size = UDim2.new(1, 0, 1, 0)
	emptyBar.ZIndex = 62
	refs.emptyBar = emptyBar

	Instance.new("UICorner", emptyBar).CornerRadius = UDim.new(1, 0)
end

local hopNotifyThread = nil
local hopNotifyToken = 0
local emptyNotifyShowing = false

function Notify.ResolveTitle(reason, providedTitle)
	if providedTitle and providedTitle ~= "" then
		return providedTitle
	end
	local lowered = string.lower(tostring(reason or ""))
	if lowered:find("pvp") or lowered:find("combat") then
		return "WAITING FOR PVP"
	end
	if lowered:find("teleport failed") or lowered:find("retry") then
		return "RETRYING HOP"
	end
	if lowered:find("no target") or lowered:find("no valid") then
		return "NO TARGETS FOUND"
	end
	return "HOPPING SERVER"
end

function Notify.HideHop(immediate)
	local refs = Notify.Refs
	if not refs.HopNotifyFrame then
		return
	end
	hopNotifyToken = hopNotifyToken + 1
	if hopNotifyThread then
		task.cancel(hopNotifyThread)
		hopNotifyThread = nil
	end
	refs.HopCountBadge.BackgroundColor3 = Color3.fromRGB(0, 140, 255)
	refs.HopProgressBar.Size = UDim2.new(1, 0, 1, 0)

	if immediate or not refs.HopNotifyFrame.Visible then
		refs.HopNotifyFrame.Visible = false
		refs.HopNotifyFrame.Position = UDim2.new(1, 20, 1, -16)
		return
	end

	local token = hopNotifyToken
	TweenService:Create(refs.HopNotifyFrame, TweenInfo.new(0.25, Enum.EasingStyle.Quad, Enum.EasingDirection.In), {
		Position = UDim2.new(1, 20, 1, -16),
	}):Play()

	hopNotifyThread = task.spawn(function()
		task.wait(0.3)
		if token ~= hopNotifyToken then
			return
		end
		refs.HopNotifyFrame.Visible = false
		hopNotifyThread = nil
	end)
end

function Notify.ShowHop(reason, countdown, options)
	local refs = Notify.Refs
	if not refs.HopNotifyFrame then
		return
	end
	options = options or {}
	reason = reason or "Finding better server..."
	countdown = tonumber(countdown)

	local token = hopNotifyToken + 1
	hopNotifyToken = token
	if hopNotifyThread then
		task.cancel(hopNotifyThread)
		hopNotifyThread = nil
	end

	refs.HopNotifyTitle.Text = Notify.ResolveTitle(reason, options.title)
	refs.HopNotifySub.Text = reason
	refs.HopCountBadge.BackgroundColor3 = Color3.fromRGB(0, 140, 255)
	refs.HopProgressBar.Size = UDim2.new(1, 0, 1, 0)
	refs.HopNotifyFrame.Visible = true
	refs.HopNotifyFrame.Position = UDim2.new(1, 20, 1, -16)
	TweenService:Create(refs.HopNotifyFrame, TweenInfo.new(0.35, Enum.EasingStyle.Back, Enum.EasingDirection.Out), {
		Position = UDim2.new(1, -16, 1, -16),
	}):Play()

	if not countdown or countdown <= 0 or options.persist then
		refs.HopCountLbl.Text = "..."
		return
	end

	refs.HopCountLbl.Text = tostring(countdown)
	hopNotifyThread = task.spawn(function()
		local total = math.max(countdown, 1)
		for i = countdown, 1, -1 do
			if token ~= hopNotifyToken then
				return
			end
			refs.HopCountLbl.Text = tostring(i)
			TweenService:Create(refs.HopProgressBar, TweenInfo.new(1, Enum.EasingStyle.Linear), {
				Size = UDim2.new((i - 1) / total, 0, 1, 0),
			}):Play()
			TweenService
				:Create(
					refs.HopCountBadge,
					TweenInfo.new(0.15, Enum.EasingStyle.Quad, Enum.EasingDirection.Out, 0, true),
					{
						BackgroundColor3 = Color3.fromRGB(0, 165, 255),
					}
				)
				:Play()
			task.wait(1)
		end
		if token ~= hopNotifyToken then
			return
		end
		refs.HopCountLbl.Text = "GO!"
		refs.HopCountBadge.BackgroundColor3 = Color3.fromRGB(0, 195, 255)
		task.wait(0.5)
		if token ~= hopNotifyToken then
			return
		end
		Notify.HideHop()
	end)
end

function Notify.ShowEmpty(reason, countdown)
	local refs = Notify.Refs
	if not refs.EmptyNotifyFrame then
		return
	end
	if emptyNotifyShowing then
		return
	end
	emptyNotifyShowing = true
	reason = reason or "Switching server..."
	countdown = countdown or 5
	refs.emptySub.Text = reason
	refs.emptyBar.Size = UDim2.new(1, 0, 1, 0)
	refs.EmptyNotifyFrame.Visible = true
	refs.EmptyNotifyFrame.Position = UDim2.new(0.5, 0, 1.2, 0)
	TweenService:Create(refs.EmptyNotifyFrame, TweenInfo.new(0.4, Enum.EasingStyle.Back, Enum.EasingDirection.Out), {
		Position = UDim2.new(0.5, 0, 0.96, 0),
	}):Play()
	task.spawn(function()
		for i = countdown, 1, -1 do
			refs.emptySub.Text = reason .. " (" .. i .. "s)"
			TweenService:Create(refs.emptyBar, TweenInfo.new(1, Enum.EasingStyle.Linear), {
				Size = UDim2.new((i - 1) / countdown, 0, 1, 0),
			}):Play()
			task.wait(1)
		end
		TweenService
			:Create(refs.EmptyNotifyFrame, TweenInfo.new(0.3, Enum.EasingStyle.Quad, Enum.EasingDirection.In), {
				Position = UDim2.new(0.5, 0, 1.2, 0),
			})
			:Play()
		task.wait(0.35)
		refs.EmptyNotifyFrame.Visible = false
		emptyNotifyShowing = false
	end)
end

-- ============================================================================
-- ============================================================================
local connections = {}
local threads = {}
local pvpWatchers = {}

local function TrackConnect(sig, fn)
	local c = sig:Connect(fn)
	table.insert(connections, c)
	return c
end

local function TrackSpawn(fn)
	local th = task.spawn(fn)
	table.insert(threads, th)
	return th
end

-- ============================================================================
-- 9) UI.CONNECT — cập nhật HUD + tracker bounty
-- ============================================================================
function UI.Connect()
	local refs = UI.Refs

	task.delay(3, function()
		if not isRunning then
			return
		end
		if refs.ExecStatusLbl then
			local exInfo = Executor.Name .. " [" .. Executor.Platform .. "]"
			if Executor.Strength > 0 then
				exInfo = exInfo .. " ★" .. tostring(Executor.Strength)
			end
			if not Executor.CanHookNamecall then
				exInfo = exInfo .. " | Aimbot: Assist"
			end
			refs.ExecStatusLbl.Text = "Executor: " .. exInfo
		end
	end)

	TrackSpawn(function()
		local function bindBountyTracker()
			local leaderstats = Player:FindFirstChild("leaderstats")
			local bountyStat = leaderstats and leaderstats:FindFirstChild("Bounty/Honor")
			if not bountyStat then
				return false
			end
			Bounty.initial = Bounty.initial or bountyStat.Value
			Bounty.last = bountyStat.Value
			Bounty.earned = math.max(0, bountyStat.Value - (Bounty.initial or bountyStat.Value))

			local trackerConn = bountyStat:GetPropertyChangedSignal("Value"):Connect(function()
				local newValue = bountyStat.Value
				local oldValue = Bounty.last
				local earnedNow = Bounty.initial and math.max(0, newValue - Bounty.initial) or 0
				local earnedDelta = earnedNow - (Bounty.earned or 0)

				if oldValue ~= nil and newValue > oldValue and earnedDelta > 0 then
					State.killCount = (State.killCount or 0) + 1
					getgenv().killCount = State.killCount
					local targetName = "Unknown"
					pcall(function()
						local t = GetState("targ")
						if t and t.Name then
							targetName = t.Name
						else
							local k = GetState("killed")
							if k and k.Name then
								targetName = k.Name
							end
						end
					end)
					print(
						"Bounty earned increased: +"
							.. tostring(earnedDelta)
							.. " | Total Kills: "
							.. tostring(State.killCount)
					)
					if Webhook then
						Webhook.SendKill(targetName, earnedDelta, newValue)
					end
				end
				Bounty.last = newValue
				Bounty.earned = earnedNow
			end)
			table.insert(connections, trackerConn)
			return true
		end
		while not bindBountyTracker() do
			task.wait(1)
		end
	end)

	TrackConnect(RunService.RenderStepped, function(dt)
		pcall(function()
			if Bounty.initial and Player:FindFirstChild("leaderstats") then
				local bountyStat = Player.leaderstats:FindFirstChild("Bounty/Honor")
				if bountyStat then
					refs.CardBountyVal.Text = Utils.FormatNum(math.max(0, bountyStat.Value - Bounty.initial))
				end
			end

			local diff = os.time() - Bounty.startTime
			local hh = math.floor(diff / 3600)
			local mm = math.floor((diff % 3600) / 60)
			local ss = diff % 60
			refs.CardTimeVal.Text = string.format("%dH %dM %dS", hh, mm, ss)

			if Player.Character then
				local char = Player.Character
				local leaderstats = Player:FindFirstChild("leaderstats")
				local bountyStat = leaderstats and leaderstats:FindFirstChild("Bounty/Honor")
				if bountyStat then
					refs.InfoBounty.Text = "Bounty: " .. Utils.FormatNum(bountyStat.Value)
				end

				local data = Player:FindFirstChild("Data")
				if data then
					if data:FindFirstChild("Race") then
						refs.InfoRace.Text = "Race: " .. tostring(data.Race.Value)
					end
					if data:FindFirstChild("Level") then
						refs.InfoLevel.Text = "Level: " .. tostring(data.Level.Value) .. " (Max)"
					end
				end

				if char:FindFirstChild("Humanoid") then
					local hp = math.floor(char.Humanoid.Health / char.Humanoid.MaxHealth * 100)
					refs.InfoHealth.Text = "Health: " .. hp .. "%"
				end

				local pingInt = 0
				pcall(function()
					pingInt = math.floor(Services.Stats.Network.ServerStatsItem["Data Ping"]:GetValue())
				end)
				refs.InfoMelee.Text = "Ping: " .. tostring(pingInt) .. "ms"

				local fps = dt > 0 and math.floor(1 / dt + 0.5) or 0
				refs.InfoFPS.Text = "FPS: " .. tostring(fps)
				refs.InfoKill.Text = "Kills: " .. tostring(State.killCount or 0)
			end

			local target = GetState("targ")
			if target and target.Character and target.Character:FindFirstChild("HumanoidRootPart") then
				local targHP = ""
				local targLevel = "--"
				if target.Character:FindFirstChild("Humanoid") then
					targHP = math.floor(target.Character.Humanoid.Health) .. "hp"
				end
				if target:FindFirstChild("Data") and target.Data:FindFirstChild("Level") then
					targLevel = tostring(target.Data.Level.Value)
				end
				refs.TargetName.Text = "Name: " .. target.Name
				refs.TargetLevel.Text = "Level: " .. targLevel
				refs.TargetHealth.Text = "Health: " .. targHP
				refs.TargetDistance.Text = "Distance: --"
				local myRoot = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
				if myRoot then
					local dist = math.floor((myRoot.Position - target.Character.HumanoidRootPart.Position).Magnitude)
					refs.TargetDistance.Text = "Distance: " .. dist .. " m"
					refs.TargetDistance.TextColor3 = dist < 50 and Color3.fromRGB(0, 220, 100)
						or Color3.fromRGB(175, 220, 255)
				end
			else
				refs.TargetName.Text = "Name: --"
				refs.TargetLevel.Text = "Level: --"
				refs.TargetHealth.Text = "Health: --"
				refs.TargetDistance.Text = "Distance: --"
				refs.TargetDistance.TextColor3 = Color3.fromRGB(175, 220, 255)
			end

			if isHopping then
				refs.StatusDot.BackgroundColor3 = Color3.fromRGB(0, 185, 255)
				refs.StatusLbl.Text = "HOPPING"
				refs.StatusLbl.TextColor3 = Color3.fromRGB(0, 185, 255)
			else
				refs.StatusDot.BackgroundColor3 = Color3.fromRGB(0, 195, 255)
				refs.StatusLbl.Text = "RUNNING"
				refs.StatusLbl.TextColor3 = Color3.fromRGB(0, 195, 255)
			end
		end)
	end)
end

-- ============================================================================
-- 10) MOVE — di chuyển & bypass
-- ============================================================================
Move = {}
Buff = {}

function Move.Bypass(dest)
	if not Player.Character then
		return
	end
	local char = Player.Character
	if
		not char:FindFirstChild("Head")
		or not char:FindFirstChild("HumanoidRootPart")
		or not char:FindFirstChild("Humanoid")
	then
		return
	end
	for _, island in pairs(World.Islands) do
		if island == dest then
			if island == CFrame.new(5749.7861328125 + 50, 611.9736938476562, -276.2497863769531) then
				if activeTween then
					pcall(function()
						activeTween:Cancel()
					end)
				end
				repeat
					task.wait()
					if Player.Character and Player.Character:FindFirstChild("HumanoidRootPart") then
						Player.Character.HumanoidRootPart.CFrame = island
					else
						break
					end
				until Player.Character
					and Player.Character.PrimaryPart
					and Player.Character.PrimaryPart.CFrame == island
				task.wait(0.1)
				if CommF then
					pcall(function()
						CommF:InvokeServer("SetSpawnPoint")
					end)
				end
			elseif not stopBypass then
				if activeTween then
					pcall(function()
						activeTween:Cancel()
					end)
				end
				repeat
					task.wait()
					if Player.Character and Player.Character:FindFirstChild("HumanoidRootPart") then
						Player.Character.HumanoidRootPart.CFrame = island
					else
						break
					end
				until Player.Character
					and Player.Character.PrimaryPart
					and Player.Character.PrimaryPart.CFrame == island
				pcall(function()
					Player.Character:WaitForChild("Humanoid", 5):ChangeState(15)
					Player.Character:SetPrimaryPartCFrame(island)
					wait(0.1)
					if Player.Character and Player.Character:FindFirstChild("Head") then
						Player.Character.Head:Destroy()
					end
					wait(0.5)
					repeat
						task.wait()
						if Player.Character and Player.Character:FindFirstChild("PrimaryPart") then
							Player.Character.PrimaryPart.CFrame = island
						else
							break
						end
					until Player.Character
						and Player.Character:FindFirstChild("Humanoid")
						and Player.Character.Humanoid.Health > 0
					task.wait(0.5)
				end)
			end
		end
	end
end

function Move.SubmergedBypass(targetPos)
	pcall(function()
		local char = Player.Character
		if
			not char
			or not char:FindFirstChild("Head")
			or not char:FindFirstChild("HumanoidRootPart")
			or not char:FindFirstChild("Humanoid")
		then
			return
		end
		local npcPos = CFrame.new(-16269.7041, 25.2288494, 1373.65955)
		local destPos = targetPos or CFrame.new(10880.5, -2086.5, 10033.5)
		local distance = (destPos.Position - char.HumanoidRootPart.Position).Magnitude

		if distance > World.bypassDist then
			print("Flying to Submarine Worker NPC...")
			Move.To(npcPos)
			repeat
				task.wait(0.1)
			until Player.Character
				and Player.Character.PrimaryPart
				and (Player.Character.PrimaryPart.Position - npcPos.Position).Magnitude < 20

			task.wait(0.5)
			print("Reached NPC, calling TravelToSubmergedIsland...")
			local ok = pcall(function()
				local net = ReplicatedStorage:FindFirstChild("Modules")
					and ReplicatedStorage.Modules:FindFirstChild("Net")
				if net then
					local rf = net:FindFirstChild("RF/SubmarineWorkerSpeak")
					if rf then
						rf:InvokeServer("TravelToSubmergedIsland")
					end
				end
			end)
			if ok then
				task.wait(2.5)
				print("Entered Submerged Island, moving to safe zone...")
				Move.To(destPos)
				repeat
					task.wait(0.1)
				until Player.Character
					and Player.Character.PrimaryPart
					and (Player.Character.PrimaryPart.Position - destPos.Position).Magnitude < 15
				task.wait(0.5)
				print("Entered Submerged Island!")
			else
				print("Failed to call TravelToSubmergedIsland")
			end
		end
	end)
end

function Move.To(dest)
	Move.DoTopos(dest, false)
end

-- 10b) TWEEN + BYPASS TP + REQUEST ENTRANCE QUA CỔNG (MainQuantum-style)
-- ============================================================================
local moveState = {
	CurrentFlag = nil,
	ActiveTween = false,
	ActiveTweenTarget = nil,
}

local function Move_IsAlive()
	local char = Player.Character
	local hrp = char and char:FindFirstChild("HumanoidRootPart")
	local hum = char and char:FindFirstChild("Humanoid")
	return hrp and hrp.Parent and hum and hum.Parent and hum.Health > 0
end

local function Move_ConvertCFrame(x)
	if not x then
		return nil
	end
	local t = typeof(x)
	if t == "Vector3" then
		return CFrame.new(x)
	elseif t == "CFrame" then
		return x
	elseif t == "Instance" then
		if x:IsA("Model") then
			return x:GetPivot()
		end
		if x.CFrame then
			return x.CFrame
		end
	end
	return nil
end

local function Move_InArea(posCF)
	local worldOrigin = workspace:FindFirstChild("_WorldOrigin")
	local locations = worldOrigin and worldOrigin:FindFirstChild("Locations")
	if not locations then
		return { Name = "" }
	end
	local pos = Move_ConvertCFrame(posCF)
	if not pos then
		return { Name = "" }
	end
	for _, v in pairs(locations:GetChildren()) do
		if v:FindFirstChild("Mesh") and (pos.Position - v.Position).Magnitude <= v.Mesh.Scale.X then
			return v
		elseif v:IsA("BasePart") and (pos.Position - v.Position).Magnitude <= 1000 then
			if v.Name:find("Temple of Time") or v.Name:find("Submerged") then
				return v
			end
		end
	end
	return { Name = "" }
end

local InArea = Move_InArea
Move.InArea = Move_InArea

local function IsInTemple(posCF)
	if not posCF then
		return false
	end
	local isSea3 = (World.Current == "World3" or game.PlaceId == 7449423635 or game.PlaceId == 100117331123089)
	local pos = Move_ConvertCFrame(posCF)
	if not pos then
		return false
	end
	local areaName = Move_InArea(pos).Name or ""
	if (isSea3 and areaName:find("Temple of Time")) or areaName:find("Temple of Time") then
		return true
	end
	return false
end
Move.IsInTemple = IsInTemple

local function Move_GetSpawn(x)
	local worldOrigin = workspace:FindFirstChild("_WorldOrigin")
	local spawns = worldOrigin and worldOrigin:FindFirstChild("PlayerSpawns")
	spawns = spawns and spawns:FindFirstChild("Pirates")
	if not spawns then
		return nil
	end
	local pos = Move_ConvertCFrame(x)
	if not pos then
		return nil
	end
	for _, v in pairs(spawns:GetChildren()) do
		local part = v:FindFirstChild("Part")
		if part and (part.Position - pos.Position).Magnitude <= 2500 then
			return v
		end
	end
	return nil
end

-- [1] KIỂM TRA CÓ THỂ BYPASS TP KHÔNG (đích cách xa > 3500, không vùng cấm)
local function Move_CanBypass(x)
	local name = Move_InArea(x).Name
	if name == "" then
		return false
	end
	if
		name:find("Dimension")
		or name:find("Cursed")
		or name:find("Submerged")
		or name:find("Temple of Time")
		or name == "Sealed Cavern"
		or name:lower():find("under")
	then
		return false
	end
	local lastSpawn = nil
	pcall(function()
		if Player.Data and Player.Data.LastSpawnPoint then
			lastSpawn = Player.Data.LastSpawnPoint.Value
		end
	end)
	if lastSpawn == "SubmergedIsland" then
		return false
	end
	local pos = Move_ConvertCFrame(x)
	local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
	if not pos or not hrp then
		return false
	end
	return (pos.Position - hrp.Position).Magnitude > 3500
end

local function Move_GetBypassTarget(x)
	local worldOrigin = workspace:FindFirstChild("_WorldOrigin")
	local spawns = worldOrigin and worldOrigin:FindFirstChild("PlayerSpawns")
	spawns = spawns and spawns:FindFirstChild("Pirates")
	if not spawns then
		return nil
	end
	local pos = Move_ConvertCFrame(x)
	local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
	if not pos or not hrp then
		return nil
	end

	local bestDist = math.huge
	local bestSpawn = nil
	local toMe = (pos.Position - hrp.Position).Magnitude
	local currentSpawn = Move_GetSpawn(hrp)
	for _, v in pairs(spawns:GetChildren()) do
		local part = v:FindFirstChild("Part")
		if part then
			local dt = (part.Position - pos.Position).Magnitude
			local dm = (part.Position - hrp.Position).Magnitude
			if toMe >= 3000 and Move_GetSpawn(part) ~= currentSpawn and dm <= 10200 and dt <= bestDist then
				bestDist = dt
				bestSpawn = v
			end
		end
	end
	return bestSpawn
end

local function Move_HandleBypassTP(finishCF)
	pcall(function()
		if isHopping or stopBypass then return end
		if HasActivePvpTagRisk and HasActivePvpTagRisk() then return end
		local maxLoops = 10
		local loops = 0
		repeat
			loops = loops + 1
			if loops > maxLoops then
				break
			end
			local targetSpawn = Move_GetBypassTarget(finishCF)
			if not targetSpawn then
				break
			end
			for _ = 1, 3 do
				if CommF then
					pcall(function()
						CommF:InvokeServer("SetLastSpawnPoint", targetSpawn.Name)
					end)
					pcall(function()
						CommF:InvokeServer("SetSpawnPoint")
					end)
				end
				local char = Player.Character
				if char then
					pcall(function()
						char:PivotTo(targetSpawn.Part.CFrame)
					end)
					local hum = char:FindFirstChild("Humanoid")
					if hum then
						hum.Health = 0
					end
				end
			end
			task.wait(0.1)
			local timeoutT = tick()
			repeat
				task.wait(0.1)
			until
				(Player.Character
					and Player.Character:FindFirstChild("Humanoid")
					and Player.Character:FindFirstChild("HumanoidRootPart")
					and Player.Character:FindFirstChild("Humanoid").Health > 0)
				or tick() - timeoutT > 6
		until not Move_CanBypass(finishCF) or not Move_GetBypassTarget(finishCF)
	end)
end

-- [3] CỔNG (PORTAL) — tìm cổng gần đích + requestEntrance
local function Move_CheckPortal(portal)
	local portalPos = portal.Position
	local minimum = math.huge
	local destination = nil
	pcall(function()
		for _, v in pairs(World.Islands) do
			local d = (v.Position - portalPos).Magnitude
			if d < minimum then
				minimum = d
				destination = v
			end
		end
	end)
	local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
	if not hrp then
		return nil
	end
	return minimum <= (portalPos - hrp.Position).Magnitude and destination or nil
end

local function Move_RequestEntrance(portal)
	pcall(function()
		local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
		if not hrp then
			return
		end
		if (hrp.Position - portal).Magnitude > 300 then
			if CommF then
				pcall(function()
					CommF:InvokeServer("requestEntrance", portal)
				end)
			end
			hrp.CFrame = hrp.CFrame + Vector3.new(0, 40)
			task.wait(0.5)
		end
	end)
end

local function Move_HandlePortal(finishCF)
	local portal = Move_CheckPortal(finishCF)
	if portal then
		Move_RequestEntrance(portal)
		task.wait(1)
	end
end

-- [2] TWEEN PLAYER: lerp CFrame + BodyVelocity "PartVelocuty" + khóa Parent
local function Move_DoMove(finishCF)
	pcall(function()
		if not Move_IsAlive() then
			return
		end
		local char = Player.Character
		local hrp = char.HumanoidRootPart
		local hum = char.Humanoid
		local flag = moveState.CurrentFlag or { stop = false }
		local startCF = hrp.CFrame
		local totalDist = (finishCF.Position - startCF.Position).Magnitude
		if totalDist <= 1 then
			return
		end

		moveState.ActiveTween = true
		moveState.ActiveTweenTarget = finishCF

		local bodyVel = hrp:FindFirstChild("PartVelocuty")
		if not bodyVel then
			bodyVel = Instance.new("BodyVelocity")
			bodyVel.Name = "PartVelocuty"
			bodyVel.MaxForce = Vector3.new(math.huge, math.huge, math.huge)
			bodyVel.Velocity = Vector3.zero
			bodyVel.P = 1e5
			bodyVel.Parent = hrp
		end

		local currentCF = startCF
		local lockConn
		lockConn = hrp:GetPropertyChangedSignal("Parent"):Connect(function()
			if flag.stop or hum.Health <= 0 then
				pcall(function()
					lockConn:Disconnect()
				end)
				return
			end
			hrp.CFrame = currentCF
		end)

		local traveled = 0
		while not flag.stop and hum.Health > 0 do
			if
				Config.Data.Another.BypassTP
				and not isHopping
				and not stopBypass
				and (not HasActivePvpTagRisk or not HasActivePvpTagRisk())
				and Move_CanBypass(finishCF)
			then
				pcall(function() lockConn:Disconnect() end)
				pcall(function() bodyVel:Destroy() end)
				moveState.ActiveTween = nil
				moveState.ActiveTweenTarget = nil
				Move_HandleBypassTP(finishCF)
				if not Move_IsAlive() then return end
				char = Player.Character
				hrp = char.HumanoidRootPart
				hum = char.Humanoid
				flag = moveState.CurrentFlag or { stop = false }
				startCF = hrp.CFrame
				totalDist = (finishCF.Position - startCF.Position).Magnitude
				traveled = 0
				currentCF = startCF
				if totalDist <= 1 then
					hrp.CFrame = finishCF
					break
				end
				bodyVel = hrp:FindFirstChild("PartVelocuty")
				if not bodyVel then
					bodyVel = Instance.new("BodyVelocity")
					bodyVel.Name = "PartVelocuty"
					bodyVel.MaxForce = Vector3.new(math.huge, math.huge, math.huge)
					bodyVel.Velocity = Vector3.zero
					bodyVel.P = 1e5
					bodyVel.Parent = hrp
				end
				lockConn = hrp:GetPropertyChangedSignal("Parent"):Connect(function()
					if flag.stop or hum.Health <= 0 then
						pcall(function() lockConn:Disconnect() end)
						return
					end
					hrp.CFrame = currentCF
				end)
			end
			local speed = math.max(tonumber(Config.Data.Another.TweenSpeed) or 200, 0.1)
			local dt = task.wait()
			traveled = traveled + speed * dt
			local alpha = math.clamp(traveled / totalDist, 0, 1)
			currentCF = startCF:Lerp(finishCF, alpha)
			hrp.CFrame = currentCF
			bodyVel.Velocity = (finishCF.Position - currentCF.Position).Unit * speed
			if (finishCF.Position - hrp.Position).Magnitude <= 20 or alpha >= 1 then
				hrp.CFrame = finishCF
				bodyVel.Velocity = Vector3.zero
				break
			end
		end
		pcall(function()
			lockConn:Disconnect()
		end)
		moveState.ActiveTween = nil
		moveState.ActiveTweenTarget = nil
	end)
end

local function Move_DoTopos(cframe, keepVel)
	pcall(function()
		if moveState.CurrentFlag then
			moveState.CurrentFlag.stop = true
			moveState.CurrentFlag = nil
		end
		moveState.ActiveTween = nil
		moveState.ActiveTweenTarget = nil

		if not Player.Character or not Move_IsAlive() then
			return
		end

		local finishCF = Move_ConvertCFrame(cframe)
		if not finishCF then
			return
		end

		if IsInTemple(finishCF) then
			return
		end

		if Config.Data.Another.BypassTP and Move_CanBypass(finishCF) then
			Move_HandleBypassTP(finishCF)
			if not Move_IsAlive() then
				return
			end
		else
			Move_HandlePortal(finishCF)
		end

		if Config.Data.Another.ForceAnchoredY then
			pcall(function()
				local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
				if hrp and math.abs(hrp.Position.Y - finishCF.Position.Y) < 1000 then
					hrp.CFrame = CFrame.new(hrp.Position.X, finishCF.Position.Y, hrp.Position.Z)
				end
			end)
		end

		moveState.CurrentFlag = { stop = false }
		Move_DoMove(finishCF)

		pcall(function()
			local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
			local vel = hrp and hrp:FindFirstChild("PartVelocuty")
			if vel and not keepVel then
				vel:Destroy()
			end
		end)
	end)
end

	-- ===== BAY LÊN CAO (tween) + GIỮ ĐỘ CAO (AntiFall) =====
	local flyTween = nil

	local function Move_ManageAntiFall(rootPart)
		local bv = rootPart:FindFirstChild("AntiFallVelocity")
		if bv and bv.Parent ~= rootPart then
			pcall(function() bv:Destroy() end)
			bv = nil
		end
		if not bv then
			bv = Instance.new("BodyVelocity")
			bv.Name = "AntiFallVelocity"
			bv.Velocity = Vector3.new(0, 0, 0)
			bv.MaxForce = Vector3.new(9e9, 9e9, 9e9)
			pcall(function() bv.Parent = rootPart end)
		end
	end

	local function Move_RemoveAntiFall(rootPart)
		local bv = rootPart and rootPart:FindFirstChild("AntiFallVelocity")
		if bv then pcall(function() bv:Destroy() end) end
		if flyTween then
			pcall(function() flyTween:Cancel() end)
			flyTween = nil
		end
	end

	local function Move_FlyUpTo(flyHeight)
		pcall(function()
			local char = Player.Character
			local hrp = char and char:FindFirstChild("HumanoidRootPart")
			if not hrp then return end
			if flyTween then return end
			local target = CFrame.new(hrp.Position.X, flyHeight, hrp.Position.Z)
			local dist = (target.Position - hrp.Position).Magnitude
			if dist <= 1 then
				Move_ManageAntiFall(hrp)
				return
			end
			Move_ManageAntiFall(hrp)
			local speed = math.max(tonumber(Config.Data.Another.TweenSpeed) or 200, 0.1)
			flyTween = TweenService:Create(hrp, TweenInfo.new(dist / speed, Enum.EasingStyle.Linear), { CFrame = target })
			flyTween.Completed:Connect(function()
				flyTween = nil
			end)
			flyTween:Play()
		end)
	end

	local function Move_FlyDownTo(targetPos)
		pcall(function()
			local char = Player.Character
			local hrp = char and char:FindFirstChild("HumanoidRootPart")
			if not hrp then return end
			Move_RemoveAntiFall(hrp)
			local target = Move_ConvertCFrame(targetPos)
			if not target then return end
			local dist = (target.Position - hrp.Position).Magnitude
			if dist <= 1 then
				hrp.CFrame = target
				return
			end
			local speed = math.max(tonumber(Config.Data.Another.TweenSpeed) or 200, 0.1)
			flyTween = TweenService:Create(hrp, TweenInfo.new(dist / speed, Enum.EasingStyle.Linear), { CFrame = target })
			flyTween.Completed:Connect(function()
				flyTween = nil
			end)
			flyTween:Play()
		end)
	end

-- PUBLIC API
function Move.StopTween()
	pcall(function()
		if moveState.CurrentFlag then
			moveState.CurrentFlag.stop = true
			moveState.CurrentFlag = nil
		end
		moveState.ActiveTween = nil
		moveState.ActiveTweenTarget = nil
		local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
		local vel = hrp and hrp:FindFirstChild("PartVelocuty")
		if vel then
			vel:Destroy()
		end
	end)
end

function Move.DoTopos(cframe, keepVel)
	Move_DoTopos(cframe, keepVel)
end

function Move.CanBypassTP(x)
	return Move_CanBypass(x)
end

function Move.GetBypassTarget(x)
	return Move_GetBypassTarget(x)
end

function Move.BypassTP(dest)
	if isHopping or stopBypass then
		return
	end
	if HasActivePvpTagRisk and HasActivePvpTagRisk() then
		return
	end
	Move_HandleBypassTP(dest)
end

function Move.RequestEntrance(portal)
	Move_RequestEntrance(portal)
end

function Move.FlyUpTo(flyHeight)
	Move_FlyUpTo(flyHeight)
end

function Move.FlyDownTo(targetPos)
	Move_FlyDownTo(targetPos)
end

function Move.RemoveAntiFall()
	pcall(function()
		local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
		Move_RemoveAntiFall(hrp)
	end)
end

-- 11) BUFF — buso / ken / equip / phím
-- ============================================================================
function Buff.Buso()
	if Player.Character and not Player.Character:FindFirstChild("HasBuso") then
		if CommF then
			pcall(function()
				CommF:InvokeServer("Buso")
			end)
		end
	end
end

function Buff.Ken()
	if
		Player:FindFirstChild("PlayerGui")
		and Player.PlayerGui:FindFirstChild("ScreenGui")
		and Player.PlayerGui.ScreenGui:FindFirstChild("ImageLabel")
	then
		return true
	end
	VirtualUser:CaptureController()
	VirtualUser:SetKeyDown("0x65")
	VirtualUser:SetKeyUp("0x65")
	return false
end

function Buff.Down(key, hold)
	pcall(function()
		local keyStr = tostring(key or "")
		local kc = (typeof(key) == "EnumItem" and key) or (keyStr ~= "" and Enum.KeyCode[string.upper(keyStr)])
		if not kc then return end

		local vim = Services.VirtualInputManager
		if vim then
			vim:SendKeyEvent(true, kc, false, game)
			task.wait(hold or 0.1)
			vim:SendKeyEvent(false, kc, false, game)
		elseif keypress and keyrelease then
			pcall(function()
				keypress(kc.Value)
				task.wait(hold or 0.1)
				keyrelease(kc.Value)
			end)
		end
	end)
end

function Buff.Equip(tooltip)
	local ok, result = pcall(function()
		local char = Player.Character or Player.CharacterAdded:Wait()
		for _, item in pairs(Player.Backpack:GetChildren()) do
			if item:IsA("Tool") and item.ToolTip == tooltip then
				local humanoid = char:FindFirstChildOfClass("Humanoid")
				if humanoid and not humanoid:IsDescendantOf(item) then
					char.Humanoid:EquipTool(item)
					return true
				end
			end
		end
		return false
	end)
	if ok then
		return result
	end
	return false
end

function Buff.EquipWeapon(toolName)
	pcall(function()
		local tool = Player.Backpack:FindFirstChild(toolName)
		if tool then
			tool.Parent = Player.Character
		end
	end)
end

-- ============================================================================
-- 12) COMBAT — skill, aimbot, vũ khí, buff theo cấu hình
-- ============================================================================
Combat = {}

-- ============================================================================
-- 12b) HITBOX — mở rộng hitbox người chơi khác để dễ đánh trúng
-- ============================================================================
local HITBOX_PARTS = { "Head", "Torso", "Left Arm", "Right Arm", "Left Leg", "Right Leg" }
local hitboxOrigSizes = setmetatable({}, { __mode = "k" })

function Combat.BoostHitbox()
	TrackSpawn(function()
		while task.wait(0.1) do
			if not isRunning then
				break
			end
			pcall(function()
				local hitboxCfg = Config.Data.Combat.Hitbox
				local multiplier = tonumber(hitboxCfg.Multiplier) or 2
				multiplier = math.max(1, math.min(5, multiplier))
				if multiplier <= 1 then
					return
				end

				local characters = {}
				if hitboxCfg.AllPlayers then
					for _, plr in pairs(Players:GetPlayers()) do
						if plr ~= Player and plr.Character then
							table.insert(characters, plr.Character)
						end
					end
				else
					local target = GetState("targ")
					if target and target.Character then
						table.insert(characters, target.Character)
					end
				end

				for _, character in ipairs(characters) do
					if character:IsA("Model") then
						for _, partName in ipairs(HITBOX_PARTS) do
							local part = character:FindFirstChild(partName)
							if part and part:IsA("BasePart") then
								local base = hitboxOrigSizes[part]
								if not base then
									base = part.Size
									hitboxOrigSizes[part] = base
								end
								part.Size = base * multiplier
								part.CanCollide = false
							end
						end
						if hitboxCfg.IncludeRoot then
							local root = character:FindFirstChild("HumanoidRootPart")
							if root then
								local base = hitboxOrigSizes[root]
								if not base then
									base = root.Size
									hitboxOrigSizes[root] = base
								end
								root.Size = base * multiplier
								root.CanCollide = false
							end
						end
					end
				end
			end)
		end
	end)
end

-- ============================================================================
-- 12c) ANTI-STUN — chống choáng / ngã / khóa di chuyển
-- ============================================================================
local antiStunConnections = {}

local function AntiStunCleanup()
	for _, conn in ipairs(antiStunConnections) do
		pcall(function()
			conn:Disconnect()
		end)
	end
	antiStunConnections = {}
end

local function HandleBadState(humanoid, character, newState)
	if not Config.Data.Combat.AntiStun.Enable then
		return
	end
	pcall(function()
		if
			newState == Enum.HumanoidStateType.Ragdoll
			or newState == Enum.HumanoidStateType.FallingDown
			or newState == Enum.HumanoidStateType.PlatformStanding
			or newState == Enum.HumanoidStateType.Seated
		then
			humanoid.Sit = false
			humanoid.PlatformStand = false
			humanoid:ChangeState(Enum.HumanoidStateType.GettingUp)

			local rootPart = character:FindFirstChild("HumanoidRootPart")
			if rootPart then
				rootPart.Anchored = false
			end
		end
	end)
end

local function SetupAntiStunCharacter(character)
	pcall(function()
		AntiStunCleanup()
		local humanoid = character:WaitForChild("Humanoid", 10)
		if not humanoid then
			return
		end

		local stateConn = humanoid.StateChanged:Connect(function(_, newState)
			HandleBadState(humanoid, character, newState)
		end)
		table.insert(antiStunConnections, stateConn)

		local sitConn = humanoid:GetPropertyChangedSignal("Sit"):Connect(function()
			if Config.Data.Combat.AntiStun.Enable and humanoid.Sit then
				task.wait(0.04)
				pcall(function()
					humanoid.Sit = false
					humanoid:ChangeState(Enum.HumanoidStateType.GettingUp)
				end)
			end
		end)
		table.insert(antiStunConnections, sitConn)

		local diedConn = humanoid.Died:Connect(function()
			AntiStunCleanup()
		end)
		table.insert(antiStunConnections, diedConn)

		HandleBadState(humanoid, character, humanoid:GetState())
	end)
end

function Combat.InitAntiStun()
	pcall(function()
		if not Config.Data.Combat.AntiStun.Enable then
			return
		end
		if Player.Character then
			SetupAntiStunCharacter(Player.Character)
		end
		TrackConnect(Player.CharacterAdded, function(character)
			SetupAntiStunCharacter(character)
		end)
		print("[Anti-Stun] Đã kích hoạt thành công!")
	end)
end

local originalNamecall

local FPS_FLAGS = {
	FFlagDebugDisableTextures = "True",
	DFFlagTextureQualityOverrideEnabled = "True",
	DFIntTextureQualityOverride = "0",
	FIntMaxTextureSize = "1",
	FFlagRenderShadow = "False",
	FFlagDebugTextureManagerSkipMips = "9999",
	FFlagEnableTextureStreaming = "False",
	FFlagDisableMaterials = "True",
	FFlagDisableLighting = "True",
	FFlagDisableParticles = "True",
	FFlagDisablePostFx = "True",
	FFlagDebugSkyGray = "True",
	DFIntTaskSchedulerTargetFps = "60",
	DFIntDebugFRMQualityLevelOverride = "0",
	FFlagDebugDisableTelemetryEphemeralCounter = "True",
	FFlagDebugDisableTelemetryEphemeralStat = "True",
	FFlagDebugDisableTelemetryEventIngest = "True",
	FFlagDebugDisableTelemetryPoint = "True",
	FFlagDebugDisableTelemetryV2Counter = "True",
	FFlagDebugDisableTelemetryV2Event = "True",
	FFlagDebugDisableTelemetryV2Stat = "True",
	FIntFRMMinGrassDistance = "0",
	FIntFRMMaxGrassDistance = "0",
	FIntRenderGrassDetailStrands = "0",
	FIntRenderGrassHeightScaler = "0",
	DFIntMaxFrameBufferSize = "1",
	FIntRobloxGuiBlurIntensity = "0",
	FFlagDebugDisableDynamicAmbient = "True",
	FFlagDebugDisableDecals = "True",
	FFlagDebugDisableMicroprofiler = "True",
	DFIntGcFrequency = "60",
	DFIntScriptTimeout = "30",
	FFlagEnableTextureQualityOverride = "True",
	FFlagDebugRenderSkipLighting = "True",
	FFlagDebugRenderSkipMaterials = "True",
	FFlagDebugRenderSkipParticles = "True",
	FFlagDebugRenderSkipPostEffects = "True",
	FFlagDebugRenderSkipShadows = "True",
	FFlagDebugRenderSkipSky = "True",
	FFlagDebugRenderSkipTerrain = "True",
	FFlagDebugRenderSkipWater = "True",
	FFlagRenderFog = "False",
	FFlagRenderLensFlare = "False",
	FFlagRenderMotionBlur = "False",
	FFlagRenderScreenSpaceReflections = "False",
	FFlagRenderSSAO = "False",
	FFlagRenderVolumetricLighting = "False",
	FFlagNetworkOptimizeUnreliable = "True",
	FFlagNetworkPacketSpamProtection = "False",
	DFIntConnectionMTUSize = "1400",
	DFIntNetworkReceiveBufferSize = "65536",
	DFIntNetworkSendBufferSize = "65536",
	FFlagHttpCacheEnabled = "True",
	FFlagHttpDebugDisableCertPinning = "False",
}

local function CanChangeColor(obj)
	return obj:IsA("BasePart")
		and obj:IsDescendantOf(workspace)
		and not (Player.Character and obj:IsDescendantOf(Player.Character))
end

local function MakeStone(obj)
	pcall(function()
		if CanChangeColor(obj) then
			obj.Color = Color3.fromRGB(115, 115, 115)
			obj.Material = Enum.Material.SmoothPlastic
			obj.Reflectance = 0
			obj.CastShadow = false
		end
	end)
end

local function RemoveUnnecessaryEffects(obj)
	pcall(function()
		if
			obj:IsA("ParticleEmitter")
			or obj:IsA("Beam")
			or obj:IsA("Trail")
			or obj:IsA("Fire")
			or obj:IsA("Smoke")
			or obj:IsA("Sparkles")
			or obj:IsA("Explosion")
			or obj:IsA("Highlight")
			or obj:IsA("Decal")
			or obj:IsA("Texture")
			or obj:IsA("PointLight")
			or obj:IsA("SurfaceLight")
			or obj:IsA("SpotLight")
		then
			obj:Destroy()
		end
	end)
end

local function ResetCharacterAppearance(character)
	pcall(function()
		if not character then
			return
		end
		for _, obj in pairs(character:GetChildren()) do
			if obj:IsA("Shirt") or obj:IsA("Pants") or obj:IsA("ShirtGraphic") or obj:IsA("BodyColors") then
				obj:Destroy()
			end
		end
		for _, part in pairs(character:GetChildren()) do
			if part:IsA("BasePart") then
				part.Color = Color3.fromRGB(163, 162, 165)
			end
		end
	end)
end

-- ============================================================================
-- 12e) FPS BOOST — tối ưu hiệu suất triệt để (setfflag + đá xám + xóa effect)
-- ============================================================================
local function ApplyFpsBoost()
	for flagName, flagValue in pairs(FPS_FLAGS) do
		pcall(function()
			Executor.SetFFlag(flagName, flagValue)
		end)
	end
	task.wait(0.5)

	pcall(function()
		for _, obj in pairs(workspace:GetDescendants()) do
			MakeStone(obj)
			RemoveUnnecessaryEffects(obj)
		end
	end)
	TrackConnect(workspace.DescendantAdded, function(obj)
		task.wait(0.1)
		MakeStone(obj)
		RemoveUnnecessaryEffects(obj)
	end)

	pcall(function()
		Lighting.GlobalShadows = false
		Lighting.Brightness = 2
		Lighting.Ambient = Color3.new(1, 1, 1)
		Lighting.OutdoorAmbient = Color3.new(1, 1, 1)
		Lighting.FogEnd = 1000000
		Lighting.Technology = Enum.Technology.Compatibility
		for _, effect in pairs(Lighting:GetChildren()) do
			if
				effect:IsA("Sky")
				or effect:IsA("BlurEffect")
				or effect:IsA("SunRaysEffect")
				or effect:IsA("ColorCorrectionEffect")
				or effect:IsA("BloomEffect")
				or effect:IsA("DepthOfFieldEffect")
			then
				pcall(function()
					effect:Destroy()
				end)
			end
		end
	end)

	pcall(function()
		local terrain = workspace.Terrain
		terrain.WaterWaveSize = 0
		terrain.WaterWaveSpeed = 0
		terrain.WaterReflectance = 0
		terrain.WaterTransparency = 0
	end)

	pcall(function()
		settings().Rendering.QualityLevel = Enum.QualityLevel.Level01
	end)

	if Player.Character then
		ResetCharacterAppearance(Player.Character)
	end
	TrackConnect(Player.CharacterAdded, function(character)
		task.wait(1)
		ResetCharacterAppearance(character)
	end)
end

-- ============================================================================
-- 12f) VISUAL — hide map + màn hình đen/trắng
-- ============================================================================
local Visual = {}
local hideMapConn = nil
local screenOverlayGui = nil
local screenOverlayFrame = nil

local function IsPlayerPart(obj)
	for _, plr in pairs(Players:GetPlayers()) do
		if plr.Character and obj:IsDescendantOf(plr.Character) then
			return true
		end
	end
	return false
end

local function HideAllTransparency()
	pcall(function()
		local keepPlayers = Config.Data.Visual.HideMap.KeepPlayers
		for _, obj in pairs(workspace:GetDescendants()) do
			pcall(function()
				if not (keepPlayers and IsPlayerPart(obj)) then
					obj.Transparency = 1
				end
			end)
		end
		for _, obj in pairs(Executor.GetNilInstances()) do
			pcall(function()
				obj.Transparency = 1
				for _, child in pairs(obj:GetDescendants()) do
					pcall(function()
						child.Transparency = 1
					end)
				end
			end)
		end
	end)
end

local function SetScreenOverlay(color)
	pcall(function()
		if not screenOverlayGui then
			screenOverlayGui = Instance.new("ScreenGui")
			screenOverlayGui.Name = "NatAovHub_ScreenOverlay"
			screenOverlayGui.ResetOnSpawn = false
			screenOverlayGui.DisplayOrder = 999
			screenOverlayGui.IgnoreGuiInset = true
			screenOverlayGui.Parent = CoreGui

			screenOverlayFrame = Instance.new("Frame", screenOverlayGui)
			screenOverlayFrame.Name = "Overlay"
			screenOverlayFrame.Size = UDim2.new(1, 0, 1, 0)
			screenOverlayFrame.BackgroundTransparency = 0
			screenOverlayFrame.BorderSizePixel = 0
			screenOverlayFrame.ZIndex = 999
		end
		screenOverlayFrame.Visible = color ~= nil
		screenOverlayFrame.BackgroundColor3 = color or Color3.new(0, 0, 0)
	end)
end

-- ===== ESP PLAYER (box + ten + HP + khoang cach) =====
local function GetHeadshotImage(userId)
	return "rbxthumb://type=AvatarHeadShot&id=" .. tostring(userId) .. "&w=420&h=420"
end

local function AddESP(part, espColor, getTextFunc, getImageFunc)
	pcall(function()
		if not part or part:FindFirstChild("ESPTuanNguyenDz") then
			return
		end
		local folder = Instance.new("Folder", part)
		folder.Name = "ESPTuanNguyenDz"
		local box = Instance.new("BoxHandleAdornment", folder)
		box.Name = "Box"
		box.Adornee = part
		box.Size = part.Size
		box.AlwaysOnTop = true
		box.ZIndex = 10
		box.Transparency = 0.7
		box.Color3 = espColor or Color3.new(1, 1, 0)
		local bbg = Instance.new("BillboardGui", folder)
		bbg.Adornee = part
		bbg.Size = UDim2.new(0, 200, 0, 50)
		bbg.StudsOffset = Vector3.new(0, 3, 0)
		bbg.AlwaysOnTop = true
		local icon = Instance.new("ImageLabel", bbg)
		icon.BackgroundTransparency = 1
		icon.Size = UDim2.new(0, 36, 0, 36)
		icon.Position = UDim2.new(0, 0, 0.5, -18)
		icon.Image = "rbxassetid://0"
		local label = Instance.new("TextLabel", bbg)
		label.BackgroundTransparency = 1
		label.Size = UDim2.new(1, -40, 1, 0)
		label.Position = UDim2.new(0, 40, 0, 0)
		label.TextSize = 14
		label.Font = Enum.Font.SourceSansBold
		label.TextStrokeTransparency = 0.3
		label.TextColor3 = espColor or Color3.new(1, 1, 1)
		label.TextYAlignment = Enum.TextYAlignment.Center
		label.TextWrapped = true
		label.RichText = true
		task.spawn(function()
			while task.wait(0.1) do
				if not label or not label.Parent or not part or not part.Parent then
					break
				end
				pcall(function()
					if getTextFunc then
						label.Text = getTextFunc()
					end
					if getImageFunc then
						icon.Image = getImageFunc()
					end
				end)
			end
		end)
	end)
end

local function PlayerESP()
	for _, plr in pairs(Players:GetPlayers()) do
		task.spawn(function()
			pcall(function()
				if plr == Player then
					return
				end
				if not (plr.Character and plr.Character:FindFirstChild("Head") and plr.Character:FindFirstChild("Humanoid")) then
					return
				end
				local head = plr.Character.Head
				local existing = head:FindFirstChild("ESPTuanNguyenDz")
				if Config.Data.Visual.ESPPlayer then
					if not existing then
						local espColor = Color3.fromRGB(255, 60, 60) -- Toàn bộ là Enemy (đỏ)
						local teamRelation = "Enemy"
						AddESP(head, espColor, function()
							local myChar = Player.Character
							local myHead = myChar and myChar:FindFirstChild("Head")
							if not myHead then
								return ""
							end
							local dist = math.floor((myHead.Position - head.Position).Magnitude / 3)
							local hp = math.floor(plr.Character.Humanoid.Health)
							local maxHp = math.floor(plr.Character.Humanoid.MaxHealth)
							return string.format("[ %s | %d Studs | %s ]\n[ HP: %d / %d ]", plr.Name, dist, teamRelation, hp, maxHp)
						end, function()
							return GetHeadshotImage(plr.UserId)
						end)
					end
				elseif existing then
					existing:Destroy()
				end
			end)
		end)
	end
end

function Visual.Init()
	pcall(function()
		if Config.Data.Visual.HideMap.Enable then
			HideAllTransparency()
			if not hideMapConn then
				hideMapConn = TrackConnect(workspace.DescendantAdded, function(obj)
					task.wait(0.1)
					pcall(function()
						if not (Config.Data.Visual.HideMap.KeepPlayers and IsPlayerPart(obj)) then
							obj.Transparency = 1
						end
					end)
				end)
			end
			print("[Visual] Hide Map đã bật")
		end

		local overlayColor = nil
		if Config.Data.Visual.BlackScreen then
			overlayColor = Color3.new(0, 0, 0)
		elseif Config.Data.Visual.WhiteScreen then
			overlayColor = Color3.new(1, 1, 1)
		end
		SetScreenOverlay(overlayColor)
		if overlayColor then
			print("[Visual] Screen overlay đã bật")
		end
		-- Di tren nuoc: dang mat nuoc thanh mat phang di duoc
		if Config.Data.Another.Water then
			TrackSpawn(function()
				local waterPlane = nil
				while isRunning do
					pcall(function()
						if not waterPlane then
							local map = workspace:FindFirstChild("Map")
							if map then waterPlane = map:FindFirstChild("WaterBase-Plane") end
						end
						if waterPlane and waterPlane:IsA("BasePart") then waterPlane.Size = Vector3.new(1000, 113, 1000) end
					end)
					task.wait(0.1)
				end
				pcall(function()
					if waterPlane and waterPlane:IsA("BasePart") then waterPlane.Size = Vector3.new(1000, 80, 1000) end
				end)
			end)
		end

		-- ESP player loop
		TrackSpawn(function()
			while isRunning do
				task.wait(0.5)
				pcall(function() PlayerESP() end)
			end
		end)
	end)
end

function Visual.Cleanup()
	pcall(function()
		if hideMapConn then
			hideMapConn:Disconnect()
			hideMapConn = nil
		end
	end)
	pcall(function()
		if screenOverlayGui then
			screenOverlayGui:Destroy()
			screenOverlayGui = nil
			screenOverlayFrame = nil
		end
		pcall(function()
			for _, plr in pairs(Players:GetPlayers()) do
				local head = plr.Character and plr.Character:FindFirstChild("Head")
				local esp = head and head:FindFirstChild("ESPTuanNguyenDz")
				if esp then esp:Destroy() end
			end
		end)
		pcall(function() Move.RemoveAntiFall() end)
	end)
end

-- ============================================================================
-- 12g) SPAM SKILL — tự bấm skill theo chế độ
-- ============================================================================
local skillSpamIndex = 1

local function GetSkillKeys()
	local keys = Config.Data.Combat.SkillSpam.Keys
	if type(keys) ~= "table" or #keys == 0 then
		return { "Z", "X", "C", "V", "F" }
	end
	return keys
end

local function IsTargetLowHealth()
	local target = GetState("targ")
	if not target or not target.Character then
		return false
	end
	local hum = target.Character:FindFirstChild("Humanoid")
	if not hum or hum.MaxHealth <= 0 then
		return false
	end
	local percent = hum.Health / hum.MaxHealth * 100
	return percent <= (tonumber(Config.Data.Combat.SkillSpam.LowHealthPercent) or 30)
end

function Combat.InitSkillSpam()
	pcall(function()
		local spamCfg = Config.Data.Combat.SkillSpam
		if spamCfg.Mode == "None" or spamCfg.Mode == nil or spamCfg.Mode == "" then
			return
		end
		if not Player.Character then
			return
		end

		local interval = tonumber(spamCfg.Interval) or 0.35
		interval = math.max(0.1, math.min(2, interval))

		TrackSpawn(function()
			while isRunning do
				task.wait(interval)
				pcall(function()
					if not Config.Data.Combat.SkillSpam or Config.Data.Combat.SkillSpam.Mode == "None" then
						return
					end
					local mode = Config.Data.Combat.SkillSpam.Mode

					local target = GetState("targ")
					if
						not target
						or not target.Character
						or not target.Character:FindFirstChild("HumanoidRootPart")
						or not Player.Character
						or not Player.Character:FindFirstChild("HumanoidRootPart")
					then
						return
					end
					local dist = (
						target.Character.HumanoidRootPart.CFrame.Position
						- Player.Character.HumanoidRootPart.CFrame.Position
					).Magnitude
					if dist > 40 then
						return
					end

					if mode == "LowHealth" and not IsTargetLowHealth() then
						return
					end

					local keys = GetSkillKeys()
					local key = nil
					if mode == "Random" then
						key = keys[math.random(1, #keys)]
					else
						key = keys[skillSpamIndex]
						skillSpamIndex = skillSpamIndex % #keys + 1
					end

					if key then
						Buff.Down(key, 0.08)
					end
				end)
			end
		end)
		print("[SkillSpam] Đã kích hoạt chế độ: " .. tostring(spamCfg.Mode))
	end)
end

function Combat.Init()
	TrackSpawn(function()
		while RunService.Stepped:Wait() do
			pcall(function()
				if Player.Character then
					for _, v in pairs(Player.Character:GetChildren()) do
						if v:IsA("BasePart") then
							v.CanCollide = false
						end
					end
				end
			end)
		end
	end)

	if Config.Data.Another.FPSBoots then
		ApplyFpsBoost()
	end
	RunService:Set3dRenderingEnabled(true)

	if Config.Data.Combat.Hitbox.Enable then
		Combat.BoostHitbox()
	end

	Combat.InitAntiStun()

	Visual.Init()

	Combat.InitSkillSpam()

	pcall(function()
		if not Executor.CanReadUpvalues then
			return
		end
		if Player:FindFirstChild("PlayerScripts") then
			local combatFrameworkScript = Player.PlayerScripts:FindFirstChild("CombatFramework")
			if combatFrameworkScript then
				local ok, result = pcall(function()
					return require(combatFrameworkScript)
				end)
				if ok and result then
					local upvalues = Executor.GetUpvalues(result)
					local getCombatFrameworkR = upvalues and upvalues[2]
					combatFramework = getCombatFrameworkR
				end
			end
		end
	end)

	TrackSpawn(function()
		TrackConnect(RunService.RenderStepped, function()
			if combatFramework and typeof(combatFramework) == "table" then
				pcall(function()
					if combatFramework.activeController then
						combatFramework.activeController.hitboxMagnitude = 60
						combatFramework.activeController.active = false
						combatFramework.activeController.timeToNextBlock = 0
						combatFramework.activeController.focusStart = 1655503339.0980349
						combatFramework.activeController.increment = 1
						combatFramework.activeController.blocking = false
						combatFramework.activeController.attacking = false
						if combatFramework.activeController.humanoid then
							combatFramework.activeController.humanoid.AutoRotate = true
						end
					end
				end)
			end
		end)
	end)

	TrackSpawn(function()
		while task.wait() do
			pcall(function()
				local target = GetState("targ")
				if
					target
					and target.Character
					and target.Character:FindFirstChild("HumanoidRootPart")
					and Player.Character
					and Player.Character:FindFirstChild("HumanoidRootPart")
				then
					if
						(
							target.Character.HumanoidRootPart.CFrame.Position
							- Player.Character.HumanoidRootPart.CFrame.Position
						).Magnitude < 40
					then
						if not gunModeEnabled then
							if Config.Data.Melee.Enable then
								SetState("weapon", "Melee")
								task.wait(Config.Data.Melee.Delay or 0.1)
							end
							if Config.Data.Fruit.Enable then
								SetState("weapon", "Blox Fruit")
								task.wait(Config.Data.Fruit.Delay or 0.1)
							end
							if Config.Data.Sword.Enable then
								SetState("weapon", "Sword")
								task.wait(Config.Data.Sword.Delay or 0.1)
							end
							if Config.Data.Gun.Enable then
								SetState("weapon", "Gun")
								task.wait(Config.Data.Gun.Delay or 0.1)
							end
						else
							pcall(function()
								Buff.EquipWeapon("Melee")
								Buff.EquipWeapon("Gun")
							end)
						end
					end
				end
			end)
		end
	end)

	TrackSpawn(function()
		while task.wait(0.5) do
			pcall(function()
				if Config.Data.Another.V3 then
					pcall(function()
						if CommE then
							CommE:FireServer("ActivateAbility")
						end
					end)
					task.wait(30)
				end
			end)
		end
	end)

	TrackSpawn(function()
		while task.wait(0.2) do
			pcall(function()
				if Config.Data.Another.V4 and Player.Character then
					local raceEnergy = Player.Character:FindFirstChild("RaceEnergy")
					if raceEnergy and raceEnergy.Value == 1 then
						local vim = Services.VirtualInputManager
						if vim then
							vim:SendKeyEvent(true, Enum.KeyCode.Y, false, game)
							task.wait(0.05)
							vim:SendKeyEvent(false, Enum.KeyCode.Y, false, game)
						elseif keypress and keyrelease then
							pcall(function()
								keypress(Enum.KeyCode.Y.Value)
								task.wait(0.05)
								keyrelease(Enum.KeyCode.Y.Value)
							end)
						end
					end
				end
			end)
		end
	end)

	TrackSpawn(function()
		while task.wait(0.5) do
			pcall(function()
				if
					Player.PlayerGui:FindFirstChild("Main")
					and Player.PlayerGui.Main:FindFirstChild("PvpDisabled")
					and Player.PlayerGui.Main.PvpDisabled.Visible == true
				then
					if CommF then
						pcall(function()
							CommF:InvokeServer("EnablePvp")
						end)
					end
				end
				local target = GetState("targ")
				if
					target
					and target.Character
					and Player.Character
					and Player.Character:FindFirstChild("HumanoidRootPart")
					and target.Character:FindFirstChild("HumanoidRootPart")
					and (
							target.Character.HumanoidRootPart.CFrame.Position
							- Player.Character.HumanoidRootPart.CFrame.Position
						).Magnitude
						< 50
				then
					Buff.Buso()
				end
			end)
		end
	end)

	TrackSpawn(function()
		while task.wait() do
			pcall(function()
				local target = GetState("targ")
				if target and target.Character and Player.Character then
					if
						(
							target.Character.HumanoidRootPart.CFrame.Position
							- Player.Character.HumanoidRootPart.CFrame.Position
						).Magnitude < 40
					then
						Buff.Ken()
					end
				end
			end)
		end
	end)

	TrackSpawn(function()
		while task.wait(0.5) do
			pcall(function()
				if Config.Data.Another.AutoObservation then
					Buff.Ken()
				end
			end)
		end
	end)

	TrackSpawn(function()
		while task.wait() do
			local target = GetState("targ")
			if
				target
				and target.Character
				and Player.Character
				and Player.Character:FindFirstChild("HumanoidRootPart")
				and target.Character:FindFirstChild("HumanoidRootPart")
				and (
						target.Character.HumanoidRootPart.CFrame.Position
						- Player.Character.HumanoidRootPart.CFrame.Position
					).Magnitude
					< 40
			then
				isAiming = true

				local predictedPos = target.Character.HumanoidRootPart.Position
				pcall(function()
					local aimCfg = Config.Data.Combat.AimPrediction
					if aimCfg.Enable then
						local now = tick()
						local track = aimPredictData[target]
						if not track then
							track = { lastPos = predictedPos, lastTime = now, velocity = Vector3.new(0, 0, 0) }
							aimPredictData[target] = track
						else
							local dt = now - track.lastTime
							if dt > 0.03 then
								track.velocity = (predictedPos - track.lastPos) / dt
								track.lastPos = predictedPos
								track.lastTime = now
							end
						end
						local dist = (predictedPos - Player.Character.HumanoidRootPart.Position).Magnitude
						if dist <= (tonumber(aimCfg.MaxDistance) or 300) then
							predictedPos = predictedPos + track.velocity * (tonumber(aimCfg.LookAhead) or 0.25)
						end
					end
				end)

				if Config.Data.Gun.Enable and Config.Data.Gun.GunMode then
					aimCFrame =
						CFrame.new(predictedPos + target.Character.HumanoidRootPart.CFrame.LookVector * 2, predictedPos)
				else
					aimCFrame =
						CFrame.new(predictedPos + target.Character.HumanoidRootPart.CFrame.LookVector * 5, predictedPos)
				end
				aimTargetPos = predictedPos
			else
				isAiming = false
				aimTargetPos = nil
				aimPredictData = {}
			end
		end
	end)

	TrackSpawn(function()
		TrackConnect(RunService.RenderStepped, function()
			if not Executor.CanHookNamecall and isAiming and aimTargetPos and Player.Character then
				pcall(function()
					local hrp = Player.Character:FindFirstChild("HumanoidRootPart")
					local hum = Player.Character:FindFirstChild("Humanoid")
					if hrp and hum and hum.Health > 0 then
						local look = aimTargetPos - hrp.Position
						if look.Magnitude > 0.5 then
							hrp.CFrame =
								CFrame.lookAt(hrp.Position, Vector3.new(aimTargetPos.X, hrp.Position.Y, aimTargetPos.Z))
						end
					end
				end)
			end
		end)
	end)

	pcall(function()
		if not Executor.CanHookNamecall then
			return
		end
		local rawMeta = Executor.RawMetatable(game)
		if not rawMeta then
			return
		end
		local oldNamecall = rawMeta.__namecall
		Executor.SetReadOnly(rawMeta, false)
		originalNamecall = oldNamecall
		rawMeta.__namecall = Executor.NewCClosure(function(...)
			local method = Executor.GetNamecallMethod()
			local args = { ... }
			if tostring(method) == "FireServer" then
				if tostring(args[1]) == "RemoteEvent" then
					if tostring(args[2]) ~= "true" and tostring(args[2]) ~= "false" then
						if isAiming and aimCFrame then
							args[2] = aimCFrame.Position
							return oldNamecall(unpack(args))
						end
					end
				end
			end
			return oldNamecall(...)
		end)
	end)

	task.delay(6, function()
		if not isRunning then
			return
		end
		pcall(function()
			if Config.Data.Another.AutoRandomFruitOnJoin and CommF then
				local result = CommF:InvokeServer("Cousin", "DLCBoxData")
				print("Auto Random Fruit on join: " .. tostring(result or "Requested"))
			end
		end)
		pcall(function()
			if World.Current == "World3" and Config.Data.Another.AutoRandomBoneOnJoin and CommF then
				local result = CommF:InvokeServer("Bones", "Buy", 1, 1)
				print("Auto Random Bone on join: " .. tostring(result or "Requested"))
			end
		end)
	end)

	task.delay(8, function()
		if not isRunning then
			return
		end
		TrackSpawn(function()
			while task.wait(2) do
				if not isRunning then
					break
				end
				pcall(function()
					if Config.Data.Another.AutoStoreFruit then
						for _, tool in ipairs(Player.Backpack:GetChildren()) do
							local eatRemote = tool:FindFirstChild("EatRemote", true)
							if eatRemote then
								local originalName = eatRemote.Parent and eatRemote.Parent:GetAttribute("OriginalName")
								if originalName and CommF then
									pcall(function()
										CommF:InvokeServer("StoreFruit", originalName, tool)
										print("Auto stored fruit: " .. tostring(originalName))
									end)
								end
							end
						end
					end
				end)
			end
		end)
	end)
end

-- ============================================================================
-- 13) HUNT — tìm mục tiêu, skip, di chuyển, combat
-- ============================================================================
Hunt = {}

local function CheckSafeZone(position)
	local result = false
	pcall(function()
		local pos = position
		if typeof(pos) == "Instance" and pos:IsA("BasePart") then
			pos = pos.Position
		elseif typeof(pos) == "CFrame" then
			pos = pos.Position
		end
		if typeof(pos) ~= "Vector3" then return end

		local worldOrigin = workspace:FindFirstChild("_WorldOrigin")
		local safeZones = worldOrigin and worldOrigin:FindFirstChild("SafeZones")
		if safeZones then
			for _, v in pairs(safeZones:GetChildren()) do
				if v and v:IsA("BasePart") and (v.Position - pos).Magnitude <= 400 then
					result = true
					return
				end
			end
		end
	end)
	return result
end

local HuntState = {
	lastFind = 0,
	noTargetStreak = 0,
	waitingForHop = false,
}

local function GetTargetScore(v, dist)
	local cfg = Config.Data.Hunt
	local priority = cfg.Priority
	if priority ~= "Bounty" and priority ~= "Distance" then
		priority = "Balanced"
	end

	local bounty = 0
	pcall(function()
		if v.leaderstats and v.leaderstats["Bounty/Honor"] then
			bounty = v.leaderstats["Bounty/Honor"].Value
		end
	end)

	local score
	if priority == "Bounty" then
		score = bounty
	elseif priority == "Distance" then
		score = -dist
	else
		score = bounty / (1 + dist / 1000)
	end

	if cfg.PreferLowHealth then
		local hum = v.Character and v.Character:FindFirstChild("Humanoid")
		if hum and hum.MaxHealth > 0 then
			score = score + (1 - hum.Health / hum.MaxHealth) * 1000
		end
	end
	return score
end

function Hunt.Find(force)
	if HuntState.waitingForHop or isHopping or hopRequested or hopInProgress then
		return
	end
	if not force and tick() - HuntState.lastFind < (Config.Data.Hunt.FindCooldown or 1) then
		return
	end
	HuntState.lastFind = tick()

	pcall(function()
		if isHopping then
			return
		end

		local maxTargetDistance = tonumber(Config.Data.Hunt.MaxDistance) or 30000
		local bestScore = -math.huge
		local bestTarget = nil
		local myRoot = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
		if not myRoot then
			return
		end

		for _, candidate in pairs(Players:GetPlayers()) do
			local canAttack = false
			if tostring(Player.Team) == "Marines" then
				canAttack = tostring(candidate.Team) == "Pirates"
			elseif tostring(Player.Team) == "Pirates" then
				canAttack = tostring(candidate.Team) == "Marines" or tostring(candidate.Team) == "Pirates"
			end

			if candidate.Team ~= nil and canAttack and candidate ~= Player then
				local targetChar = candidate.Character
				local targetRoot = targetChar and targetChar:FindFirstChild("HumanoidRootPart")
				local targetHumanoid = targetChar and targetChar:FindFirstChild("Humanoid")

				if
					candidate:FindFirstChild("Data")
					and targetRoot
					and targetHumanoid
					and targetHumanoid.Health > 0
					and (
						(
							Config.Data.Skip.Fruit
							and Utils.Contains(Config.Data.Skip.FruitList, candidate.Data.DevilFruit.Value) == false
						) or not Config.Data.Skip.Fruit
					)
				then
					local targetPvpDisabled = candidate:GetAttribute("PvpDisabled") == true
					if Config.Data.Skip.NoPvP and targetPvpDisabled then
					else
						local dist = (targetRoot.CFrame.Position - myRoot.CFrame.Position).Magnitude
						local inTemple = IsInTemple(targetRoot)
						if
							dist <= maxTargetDistance
							and targetRoot.CFrame.Y <= 12000
							and targetRoot.CFrame.Y >= -1500 -- bo qua dich o Submerged Island
							and not inTemple -- bo qua dich o Temple of Time
							and not Utils.Contains(State.checked, candidate)
						then
							if targetHumanoid.Sit then
							elseif CheckSafeZone(targetRoot) or inTemple then
							else
								local levelOk = false
								pcall(function()
									levelOk = (tonumber(Player.Data.Level.Value) - 250) < candidate.Data.Level.Value
								end)
								if levelOk then
									local bountyOk = false
									pcall(function()
										local bountyStat = candidate.leaderstats
											and candidate.leaderstats["Bounty/Honor"]
										bountyOk = bountyStat
											and bountyStat.Value >= Config.Data.Hunt.Min
											and bountyStat.Value <= Config.Data.Hunt.Max
									end)
									if bountyOk then
										local raceOk = not (
											Config.Data["Skip Race V4"] and targetChar:FindFirstChild("RaceTransformed")
										)
										if raceOk then
											local score = GetTargetScore(candidate, dist)
											if score > bestScore then
												bestScore = score
												bestTarget = candidate
											end
										end
									end
								end
							end
						end
					end
				end
			end
		end

		if bestTarget == nil then
			State.checked = {}
			HuntState.noTargetStreak = HuntState.noTargetStreak + 1
			local maxRetries = tonumber(Config.Data.Hunt.MaxNoTargetRetries) or 3
			if HuntState.noTargetStreak >= maxRetries then
				HuntState.noTargetStreak = 0
				if not Config.Data.Hunt.FlyUpOnNoTarget then
					print("[Hunt] No targets after " .. tostring(maxRetries) .. " scans, hopping...")
					Notify.ShowHop("No targets found in this server.", 3, { title = "NO TARGETS FOUND" })
					task.wait(3)
					SafeHop()
				elseif not HuntState.waitingForHop then
					HuntState.waitingForHop = true
					print("[Hunt] No targets, flying up & waiting for combat to clear then hop...")
					task.spawn(function()
						local combatWaitMax = tonumber(Config.Data.Hunt.CombatWaitMax) or 60
						local combatWaitT = 0
						while
							HuntState.waitingForHop
							and HasActivePvpTag
							and HasActivePvpTag()
							and combatWaitT < combatWaitMax
						do
							task.wait(1)
							combatWaitT = combatWaitT + 1
						end
						task.wait(2)
						HuntState.waitingForHop = false
						Notify.ShowHop("No targets found in this server.", 3, { title = "NO TARGETS FOUND" })
						task.wait(3)
						if not isHopping then
							SafeHop()
						end
					end)
				end
			else
				print(
					"[Hunt] No targets ("
						.. tostring(HuntState.noTargetStreak)
						.. "/"
						.. tostring(maxRetries)
						.. "), retrying..."
				)
			end
		else
			HuntState.noTargetStreak = 0
			print("Found target: " .. bestTarget.Name, "success")
		end
		SetState("targ", bestTarget)
	end)
end

local skipDebounce = false
function Hunt.SkipPlayer()
	if skipDebounce then
		return
	end
	skipDebounce = true
	task.delay(0.5, function()
		skipDebounce = false
	end)

	local target = GetState("targ")
	if target then
		if not Utils.Contains(State.checked, target) then
			table.insert(State.checked, target)
		end
		SetState("killed", target)
	end
	SetState("targ", nil)
	print("None")

	local remainingValid = 0
	pcall(function()
		for _, v in pairs(Players:GetPlayers()) do
			if v ~= Player and not Utils.Contains(State.checked, v) then
				remainingValid = remainingValid + 1
			end
		end
	end)

	if remainingValid == 0 then
		State.checked = {}
		print("Skipped all targets in server, reset checked then hop")
		Notify.ShowHop("No valid targets left in this server.", 3, { title = "NO TARGETS FOUND" })
		task.spawn(function()
			task.wait(3)
			setHopping(true)
			stopBypass = true
			SafeHop()
		end)
	else
		Hunt.Find(true)
	end
end
SkipPlayer = Hunt.SkipPlayer

local function watchPvpAttribute(plr)
	local conn = plr.AttributeChanged:Connect(function(attrName)
		if attrName == "PvpDisabled" then
			local status = plr:GetAttribute("PvpDisabled")
			if status == true then
				print("[PvpCheck] " .. plr.Name .. ": PvP Disabled")
				if Config.Data.Skip.NoPvP and GetState("targ") == plr then
					print("[PvpCheck] Skip target " .. plr.Name .. " because PvP is disabled")
					SkipPlayer()
				end
			else
				print("[PvpCheck] " .. plr.Name .. ": PvP Enabled")
			end
		end
	end)
	pvpWatchers[plr] = conn
	return conn
end

-- Kiểm tra notification liên quan đến mục tiêu không thể tấn công.
-- Dùng câu cụ thể thay vì các từ quá rộng như "player", "không thể", "tấn công".
local SKIP_NOTIFICATION_PHRASES = {
	"cannot attack",
	"can not attack",
	"can't attack",
	"unable to attack",
	"player died recently",
	"safe zone",
	"pvp is disabled",
	"pvp disabled",
	"combat is disabled",
	"không thể tấn công",
	"không tấn công được",
	"không thể đánh",
	"vùng an toàn",
}

local function CleanNotificationText(text)
	local clean = tostring(text or "")

	-- Decode entity trước rồi mới xóa RichText; xử lý được cả &amp;lt;font&amp;gt;.
	clean = clean:gsub("&amp;", "&")
	clean = clean:gsub("&lt;", "<"):gsub("&gt;", ">")
	clean = clean:gsub("&quot;", '"'):gsub("&#39;", "'")
	clean = clean:gsub("<[^>]->", "")
	clean = clean:gsub("%s+", " "):match("^%s*(.-)%s*$") or ""

	return clean
end

local function IsAttackBlockedNotification(text)
	local clean = CleanNotificationText(text)
	local textLow = string.lower(clean)

	for _, phrase in ipairs(SKIP_NOTIFICATION_PHRASES) do
		if string.find(textLow, phrase, 1, true) then
			return true, clean
		end
	end

	return false, clean
end

local function CheckAttackBlockedNotifications()
	local playerGui = Player:FindFirstChild("PlayerGui")
	local notifications = playerGui and playerGui:FindFirstChild("Notifications")
	if not notifications then
		return false
	end

	-- GetDescendants để vẫn đọc được TextLabel nằm bên trong Frame.
	for _, item in ipairs(notifications:GetDescendants()) do
		if item:IsA("TextLabel") then
			local shouldSkip, cleanText = IsAttackBlockedNotification(item.Text)
			if shouldSkip then
				print("AUTO-SKIP: " .. string.sub(cleanText, 1, 80))

				-- Xóa thông báo trước để vòng kiểm tra không skip nhầm mục tiêu kế tiếp.
				pcall(function()
					item:Destroy()
				end)
				SkipPlayer()
				return true
			end
		end
	end

	return false
end

function Hunt.Init()
	for _, plr in pairs(Players:GetPlayers()) do
		if plr ~= Player then
			watchPvpAttribute(plr)
		end
	end
	TrackConnect(Players.PlayerAdded, function(plr)
		watchPvpAttribute(plr)
	end)

	TrackConnect(Players.PlayerRemoving, function(removedPlayer)
		task.wait(1)
		pcall(function()
			local otherCount = 0
			for _, v in pairs(Players:GetPlayers()) do
				if v ~= Player then
					otherCount = otherCount + 1
				end
			end
			if otherCount == 0 then
				Notify.ShowEmpty("No players left, switching server...", 4)
				task.wait(4)
				pcall(function()
					State.checked = {}
					setHopping(true)
					SafeHop()
				end)
			end
		end)
	end)

	local combatLoopActive = false
	TrackSpawn(function()
		while task.wait() do
			if not isHopping and not hopRequested and not hopInProgress then
				local target = GetState("targ")

				if target and not Players:FindFirstChild(target.Name) then
					SetState("targ", nil)
					target = nil
				end

				if
					target
					and target.Character
					and target.Character:FindFirstChild("HumanoidRootPart")
				then
					if target.Character.HumanoidRootPart.CFrame.Y < -1500 then
						print("[Hunt] Bo qua " .. target.Name .. " (Submerged Island)")
						SkipPlayer()
					elseif IsInTemple(target.Character.HumanoidRootPart) then
						print("[Hunt] Bo qua " .. target.Name .. " (Temple of Time)")
						SkipPlayer()
					end
				end

				if
					target
					and target.Character
					and target.Character:FindFirstChild("Humanoid")
					and target.Character.Humanoid.Health <= 0
				then
					print("[Hunt] Target dead, switching...")
					SkipPlayer()
				end

				local currentTarget = GetState("targ")
				if
					not isHopping
					and not HuntState.waitingForHop
					and (
						not currentTarget
						or not currentTarget.Character
						or not currentTarget.Character:FindFirstChild("HumanoidRootPart")
					)
				then
					Hunt.Find()
				end
			end
			pcall(function()
				if combatLoopActive then return end
				local target = GetState("targ")
				if
					target
					and target.Character
					and target.Character:FindFirstChild("HumanoidRootPart")
					and Player.Character
					and Player.Character:FindFirstChild("HumanoidRootPart")
				then
					if
						(
							target.Character.HumanoidRootPart.CFrame.Position
							- Player.Character.HumanoidRootPart.CFrame.Position
						).Magnitude < 40
					then
						task.spawn(function()
							pcall(function()
								if not gunModeEnabled then
									pcall(function()
										Buff.EquipWeapon("Summon Sea Beast")
									end)
									Buff.Equip(GetState("weapon"))

									for _, v in pairs(Player.Character:GetChildren()) do
										if v:IsA("Tool") then
											if v.ToolTip == "Melee" then
												if Config.Data.Melee.Enable then
													if
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("Z")
														and Player.PlayerGui.Main.Skills[v.Name].Z.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Melee.Z.Enable
													then
														Buff.Down("Z", Config.Data.Melee.Z.HoldTime)
													elseif
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("X")
														and Player.PlayerGui.Main.Skills[v.Name].X.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Melee.X.Enable
													then
														Buff.Down("X", Config.Data.Melee.X.HoldTime)
													elseif
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("C")
														and Player.PlayerGui.Main.Skills[v.Name].C.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Melee.C.Enable
													then
														Buff.Down("C", Config.Data.Melee.C.HoldTime)
													elseif
														Config.Data.Melee.V.Enable
														and Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("V")
														and Player.PlayerGui.Main.Skills[v.Name].V.Cooldown.AbsoluteSize.X
															<= 0
													then
														Buff.Down("V", Config.Data.Melee.V.HoldTime)
													end
												end
											elseif v.ToolTip == "Gun" then
												if Config.Data.Gun.Enable then
													if
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("Z")
														and Player.PlayerGui.Main.Skills[v.Name].Z.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Gun.Z.Enable
													then
														Buff.Down("Z", Config.Data.Gun.Z.HoldTime)
													elseif
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("X")
														and Player.PlayerGui.Main.Skills[v.Name].X.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Gun.X.Enable
													then
														Buff.Down("X", Config.Data.Gun.X.HoldTime)
													end
												end
											elseif v.ToolTip == "Sword" then
												if Config.Data.Sword.Enable then
													if
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("Z")
														and Player.PlayerGui.Main.Skills[v.Name].Z.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Sword.Z.Enable
													then
														Buff.Down("Z", Config.Data.Sword.Z.HoldTime)
													elseif
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("X")
														and Player.PlayerGui.Main.Skills[v.Name].X.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Sword.X.Enable
													then
														Buff.Down("X", Config.Data.Sword.X.HoldTime)
													end
												end
											elseif v.ToolTip == "Blox Fruit" then
												if Config.Data.Fruit.Enable then
													if
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("Z")
														and Player.PlayerGui.Main.Skills[v.Name].Z.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Fruit.Z.Enable
													then
														Buff.Down("Z", Config.Data.Fruit.Z.HoldTime)
													elseif
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("X")
														and Player.PlayerGui.Main.Skills[v.Name].X.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Fruit.X.Enable
													then
														Buff.Down("X", Config.Data.Fruit.X.HoldTime)
													elseif
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("C")
														and Player.PlayerGui.Main.Skills[v.Name].C.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Fruit.C.Enable
													then
														Buff.Down("C", Config.Data.Fruit.C.HoldTime)
													elseif
														Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("V")
														and Player.PlayerGui.Main.Skills[v.Name].V.Cooldown.AbsoluteSize.X <= 0
														and Config.Data.Fruit.V.Enable
													then
														Buff.Down("V", Config.Data.Fruit.V.HoldTime)
													elseif
														Config.Data.Fruit.F.Enable
														and Player.PlayerGui.Main.Skills[v.Name]:FindFirstChild("F")
														and Player.PlayerGui.Main.Skills[v.Name].F.Cooldown.AbsoluteSize.X
															<= 0
													then
														Buff.Down("F", Config.Data.Fruit.F.HoldTime)
													end
												end
											end
										end
									end
								else
									if Config.Data.Melee.Enable then
										if Config.Data.Melee.Z.Enable then
											Buff.Down("Z", Config.Data.Melee.Z.HoldTime)
										elseif Config.Data.Melee.X.Enable then
											Buff.Down("X", Config.Data.Melee.X.HoldTime)
										elseif Config.Data.Melee.C.Enable then
											Buff.Down("C", Config.Data.Melee.C.HoldTime)
										elseif Config.Data.Melee.V.Enable then
											Buff.Down("V", Config.Data.Melee.V.HoldTime)
										end
									end
								end

								if
									CheckSafeZone(target.Character.HumanoidRootPart)
									or IsInTemple(target.Character.HumanoidRootPart)
									or (Player.PlayerGui:FindFirstChild("Main") and Player.PlayerGui.Main:FindFirstChild(
										"[OLD]SafeZone"
									) and Player.PlayerGui.Main["[OLD]SafeZone"].Visible == true)
									or target.Character.Humanoid.Sit == true
								then
									SkipPlayer()
								end

								CheckAttackBlockedNotifications()
							end)
						end)
					end
				end
			end)
		end
	end)

	local function GetToolSkills(weaponName)
		local keys = {}
		if weaponName == "Melee" then
			if Config.Data.Melee.Z.Enable then table.insert(keys, "Z") end
			if Config.Data.Melee.X.Enable then table.insert(keys, "X") end
			if Config.Data.Melee.C.Enable then table.insert(keys, "C") end
		elseif weaponName == "Sword" then
			if Config.Data.Sword.Z.Enable then table.insert(keys, "Z") end
			if Config.Data.Sword.X.Enable then table.insert(keys, "X") end
		elseif weaponName == "Gun" then
			if Config.Data.Gun.Z.Enable then table.insert(keys, "Z") end
			if Config.Data.Gun.X.Enable then table.insert(keys, "X") end
		elseif weaponName == "Blox Fruit" then
			if Config.Data.Fruit.Z.Enable then table.insert(keys, "Z") end
			if Config.Data.Fruit.X.Enable then table.insert(keys, "X") end
			if Config.Data.Fruit.C.Enable then table.insert(keys, "C") end
			if Config.Data.Fruit.V.Enable then table.insert(keys, "V") end
			if Config.Data.Fruit.F.Enable then table.insert(keys, "F") end
		end
		return keys
	end

	local function GetSkillHold(weaponName, key)
		local cfg = Config.Data.Melee
		if weaponName == "Sword" then cfg = Config.Data.Sword
		elseif weaponName == "Gun" then cfg = Config.Data.Gun
		elseif weaponName == "Blox Fruit" then cfg = Config.Data.Fruit end
		local sk = cfg[key]
		return (sk and sk.HoldTime) or 0.1
	end

	TrackSpawn(function()
		combatLoopActive = true
		local weaponOrder = {}
		local function rebuildWeaponOrder()
			weaponOrder = {}
			if Config.Data.Melee.Enable then table.insert(weaponOrder, "Melee") end
			if Config.Data.Sword.Enable then table.insert(weaponOrder, "Sword") end
			if Config.Data.Fruit.Enable then table.insert(weaponOrder, "Blox Fruit") end
			if Config.Data.Gun.Enable then table.insert(weaponOrder, "Gun") end
			if #weaponOrder == 0 then table.insert(weaponOrder, "Melee") end
		end
		rebuildWeaponOrder()
		local weaponIdx = 1
		local skillIdx = 1
		local orbitAngle = 0
		while isRunning do
			task.wait(0.12)
			pcall(function()
				if isHopping or hopRequested then return end
				local myHum = Player.Character and Player.Character:FindFirstChild("Humanoid")
				if myHum and myHum.MaxHealth > 0 and Config.Data.SafeHealth.UsePercent then
					if myHum.Health / myHum.MaxHealth * 100 <= (tonumber(Config.Data.SafeHealth.Percent) or 40) then
						return
					end
				end
				local target = GetState("targ")
				if not target or not target.Character then return end
				local hum = target.Character:FindFirstChild("Humanoid")
				local hrp = target.Character:FindFirstChild("HumanoidRootPart")
				local myRoot = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
				if not hrp or not myRoot then return end
				if hum and hum.Health <= 0 then return end
				if (hrp.CFrame.Position - myRoot.CFrame.Position).Magnitude > 45 then return end

				if Config.Data.Combat.Orbit.Enable then
					orbitAngle = (orbitAngle + (tonumber(Config.Data.Combat.Orbit.AngleSpeed) or 6)) % 360
					local radius = tonumber(Config.Data.Combat.Orbit.Radius) or 12
					local height = tonumber(Config.Data.Combat.Orbit.Height) or 2
					local targetPos = hrp.Position
					local rad = math.rad(orbitAngle)
					local orbitPos = targetPos + Vector3.new(math.cos(rad) * radius, height, math.sin(rad) * radius)
					myRoot.CFrame = CFrame.lookAt(orbitPos, targetPos)
				end

				local weaponName = weaponOrder[weaponIdx]
				Buff.Equip(weaponName)

				local skills = GetToolSkills(weaponName)
				if #skills > 0 then
					local key = skills[skillIdx] or skills[1]
					Buff.Down(key, GetSkillHold(weaponName, key))
					skillIdx = skillIdx + 1
					if skillIdx > #skills then
						skillIdx = 1
						weaponIdx = weaponIdx % #weaponOrder + 1
					end
				else
					weaponIdx = weaponIdx % #weaponOrder + 1
				end
			end)
		end
	end)

	TrackSpawn(function()
		local targetHigh = false
		local lastBypassTime = 0
		local safeModeActive = false
		local waitingForRiskClear = false -- đang chờ Risk tag tắt để reset

		local function ResetForFullHP()
			pcall(function()
				local char = Player.Character
				local hum = char and char:FindFirstChild("Humanoid")
				if hum then hum.Health = 0 end -- tự sát -> respawn full máu, không mất bounty (chỉ khi không Risk)
			end)
		end

		while task.wait(0.05) do

			-- Chuẩn bị hop: dừng săn, bay lên chờ (tránh đuổi địch giữa chừng)
			if (isHopping or hopRequested or hopInProgress) and not HuntState.waitingForHop then
				pcall(function()
					local hrp = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
					if hrp then Move.FlyUpTo(tonumber(Config.Data.Hunt.FlyUpHeight) or 3000) end
				end)
			end

			if HuntState.waitingForHop then
				pcall(function()
					local char = Player.Character
					local hrp = char and char:FindFirstChild("HumanoidRootPart")
					local hum = char and char:FindFirstChild("Humanoid")
					if hrp and hum and hum.Health > 0 then
						Move.FlyUpTo(tonumber(Config.Data.Hunt.FlyUpHeight) or 3000) -- tween bay lên chờ hop
					end
				end)
			end

			local pvpDisabledFrame = Player.PlayerGui:FindFirstChild("Main")
				and Player.PlayerGui.Main:FindFirstChild("BottomHUDList")
				and Player.PlayerGui.Main.BottomHUDList:FindFirstChild("PvpDisabled")
			if not HuntState.waitingForHop and pvpDisabledFrame and not pvpDisabledFrame.Visible then
				pcall(function()
					local target = GetState("targ")
					if
						target
						and target.Character
						and target.Character:FindFirstChild("HumanoidRootPart")
						and Player.Character
						and Player.Character:FindFirstChild("HumanoidRootPart")
						and Player.Character:FindFirstChild("Humanoid")
					then
						local maxTargetDistance = tonumber(Config.Data.Hunt.MaxDistance) or 30000
						local currentDistance = (
							target.Character.HumanoidRootPart.CFrame.Position
							- Player.Character.HumanoidRootPart.CFrame.Position
						).Magnitude

						if currentDistance > maxTargetDistance then
							print(
								"Skip target "
									.. target.Name
									.. " because distance is over "
									.. tostring(maxTargetDistance)
									.. "m"
							)
							SkipPlayer()
							return
						end

						if tick() - lastBypassTime > 3 and currentDistance > 3000 then
							lastBypassTime = tick()
							if not isHopping and not stopBypass and (not HasActivePvpTagRisk or not HasActivePvpTagRisk()) then
								Move.BypassTP(target.Character.HumanoidRootPart)
							end
						end

						local healthPercent = 100
						pcall(function()
							healthPercent = Player.Character.Humanoid.Health / Player.Character.Humanoid.MaxHealth * 100
						end)
						local lowHp = false
						if Config.Data.SafeHealth.UsePercent then
							lowHp = healthPercent <= (tonumber(Config.Data.SafeHealth.Percent) or 40)
						else
							lowHp = Player.Character.Humanoid.Health <= (tonumber(Config.Data.SafeHealth.Health) or 50)
						end

						if lowHp then
							safeModeActive = true
							pcall(function()
								Move.StopTween()
								local root = Player.Character:FindFirstChild("HumanoidRootPart")
								if root then
									pcall(function()
										local vel = root:FindFirstChild("Hold") or root:FindFirstChild("PartVelocuty")
										if vel then vel:Destroy() end
									end)
									local flyHeight = tonumber(Config.Data.SafeHealth.FlyHeight) or 10000
									Move.FlyUpTo(flyHeight) -- bay lên an toàn
								end
							end)
							-- Reset nhanh: không Risk tag -> tự sát respawn full máu (không mất bounty)
							if not HasActivePvpTagRisk() then
								safeModeActive = false
								ResetForFullHP()
							else
								-- có Risk -> chờ tắt Risk rồi reset
								waitingForRiskClear = true
							end
						elseif safeModeActive then
							if waitingForRiskClear then
								-- đang chờ Risk tắt -> tắt rồi reset luôn
								if not HasActivePvpTagRisk() then
									waitingForRiskClear = false
									safeModeActive = false
									ResetForFullHP()
								end
							elseif healthPercent >= (tonumber(Config.Data.SafeHealth.HealPercent) or 65) then
								-- fallback: máu tự hồi đủ -> bay xuống đánh tiếp
								safeModeActive = false
								print("[SafeMode] Máu hồi lại, bay xuống đánh tiếp...")
								pcall(function()
									local root = Player.Character:FindFirstChild("HumanoidRootPart")
									if root and target and target.Character and target.Character:FindFirstChild("HumanoidRootPart") then
										Move.FlyDownTo(target.Character.HumanoidRootPart.CFrame * CFrame.new(0, 5, 5))
									end
								end)
							else
								-- AntiFall giữ độ cao, chờ
							end
						else
							pcall(function()
								local targetY = target.Character.HumanoidRootPart.Position.Y
								if targetY < -1500 then
									-- Địch ở Submerged Island → bỏ qua luôn (không lặn xuống đánh)
									SkipPlayer()
								elseif IsInTemple(target.Character.HumanoidRootPart) then
									-- Địch ở Temple of Time → bỏ qua luôn
									SkipPlayer()
								elseif
									not (
										workspace:FindFirstChild("_WorldOrigin")
										and workspace._WorldOrigin:FindFirstChild("Locations")
										and workspace._WorldOrigin.Locations:FindFirstChild("Island 1")
										and target:DistanceFromCharacter(
												workspace._WorldOrigin.Locations["Island 1"].Position
											)
											< 10000
									)
								then
									if
										(
											target.Character.HumanoidRootPart.CFrame.Position
											- Player.Character.HumanoidRootPart.CFrame.Position
										).Magnitude < 40
									then
										if
											Player.PlayerGui:FindFirstChild("Main")
											and Player.PlayerGui.Main:FindFirstChild("SafeZone")
											and Player.PlayerGui.Main.SafeZone.Visible == true
										then
											SkipPlayer()
										end
										if target.Character.Humanoid.Health > 0 then
											Move.To(
												target.Character.HumanoidRootPart.CFrame
													* CFrame.new(0, targetHigh and 8 or 5, targetHigh and 0 or 5)
											)
										else
											SkipPlayer()
										end
									else
										if target.Character.Humanoid.Health > 0 then
											Move.To(target.Character.HumanoidRootPart.CFrame * CFrame.new(0, 5, 5))
										else
											SkipPlayer()
										end
									end
								else
									SkipPlayer()
								end
							end)
							targetHigh = target.Character.HumanoidRootPart.CFrame.Y >= 10
						end
					end
				end)
			elseif not HuntState.waitingForHop then
				if CommF then
					pcall(function()
						CommF:InvokeServer("EnablePvp")
					end)
				end
			end
		end
	end)

	TrackSpawn(function()
		local lastKilledPlayer = nil
		while task.wait(1) do
			pcall(function()
				local target = GetState("targ")
				if target and target.Character then
					local character = target.Character
					if character:FindFirstChild("Humanoid") and character.Humanoid.Health <= 0 then
						if lastKilledPlayer ~= target.Name then
							lastKilledPlayer = target.Name
							task.wait(1)
							local confirmedDead = false
							pcall(function()
								if character and character:FindFirstChild("Humanoid") then
									confirmedDead = character.Humanoid.Health <= 0
								else
									confirmedDead = true
								end
							end)
							if confirmedDead then
								print("ELIMINATED: " .. target.Name)
								State._killCount = (State._killCount or 0) + 1
								getgenv()._killCount = State._killCount
								pcall(function()
									local earned = 0
									local currentBounty = 0
									local ls = Player:FindFirstChild("leaderstats")
									local bs = ls and ls:FindFirstChild("Bounty/Honor")
									if bs then
										currentBounty = bs.Value
									end
									if Bounty.initial then
										earned = math.max(0, currentBounty - Bounty.initial)
									end
									if Webhook then
										Webhook.SendKill(target.Name, earned, currentBounty)
									end
								end)
							end
							task.wait(2)
							SkipPlayer()
						end
					end
				end
			end)
		end
	end)

	TrackSpawn(function()
		while task.wait(0.5) do
			pcall(CheckAttackBlockedNotifications)
		end
	end)
end

-- ============================================================================
-- 14) HOP — đổi server an toàn
-- ============================================================================
Hop = {}

setHopping = function(val)
	isHopping = val
	getgenv().hopserver = val
end

HasActivePvpTagNormal = function()
	local ok, result = pcall(function()
		local mainGui = Player.PlayerGui:FindFirstChild("Main")
		local bottomHud = mainGui and mainGui:FindFirstChild("BottomHUDList")
		local inCombatFrame = bottomHud and bottomHud:FindFirstChild("InCombat")
		if inCombatFrame and inCombatFrame.Visible then
			local txt = string.lower(tostring(inCombatFrame.Text or ""))
			return string.find(txt, "combat", 1, true) ~= nil
				or string.find(txt, "in combat", 1, true) ~= nil
		end
		return false
	end)
	return ok and result == true
end

HasActivePvpTagRisk = function()
	local ok, result = pcall(function()
		local mainGui = Player.PlayerGui:FindFirstChild("Main")
		local bottomHud = mainGui and mainGui:FindFirstChild("BottomHUDList")
		local inCombatFrame = bottomHud and bottomHud:FindFirstChild("InCombat")
		if inCombatFrame and inCombatFrame.Visible then
			local txt = string.lower(tostring(inCombatFrame.Text or ""))
			return string.find(txt, "at risk", 1, true) ~= nil
				or string.find(txt, "bounty", 1, true) ~= nil
				or string.find(txt, "honor", 1, true) ~= nil
		end
		return false
	end)
	return ok and result == true
end

HasActivePvpTag = function()
	local risk, normal = false, false
	if HasActivePvpTagRisk then risk = HasActivePvpTagRisk() end
	if HasActivePvpTagNormal then normal = HasActivePvpTagNormal() end
	return risk or normal
end

function Hop.Init()
	TrackSpawn(function()
		while task.wait() do
			if isHopping then
				stopBypass = true
				hopRequested = true
			end
		end
	end)
	TrackSpawn(function()
		while task.wait() do
			if hopRequested and not hopInProgress then
				SafeHop()
			end
		end
	end)

	pcall(function()
		local promptOverlay = CoreGui:FindFirstChild("RobloxPromptGui")
			and CoreGui.RobloxPromptGui:FindFirstChild("promptOverlay")
		if promptOverlay then
			TrackConnect(promptOverlay.ChildAdded, function(child)
				if
					not isHopping
					and child.Name == "ErrorPrompt"
					and child:FindFirstChild("MessageArea")
					and child.MessageArea:FindFirstChild("ErrorFrame")
				then
					TeleportService:Teleport(game.PlaceId)
				end
			end)
		end
	end)
end

function Hop.Safe()
	if hopInProgress then
		return
	end
	HuntState.waitingForHop = false
	setHopping(true)
	stopBypass = true
	hopRequested = true
	TrackSpawn(function()
		hopInProgress = true
		pcall(function()
			if Config.Data.Another.CheckCombatBeforeHop and HasActivePvpTag() then
				print("In PvP tag, waiting until it clears before hop...")
				if UI.Refs.TargetTitle then
					UI.Refs.TargetTitle.Text = "Target Info [PvP]"
				end
				Notify.ShowHop("PvP tag is active. Waiting before hopping...", nil, {
					title = "WAITING FOR PVP",
					persist = true,
				})
				while isHopping and HasActivePvpTag() do
					if Player.Character and Player.Character:FindFirstChild("HumanoidRootPart") then
						pcall(function()
							local root = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
							if root then
								root.CFrame = root.CFrame * CFrame.new(0, math.random(500, 3000), 0)
							end
						end)
					end
					task.wait(1)
				end
				if UI.Refs.TargetTitle then
					UI.Refs.TargetTitle.Text = "Target Info"
				end
				if not isHopping then
					Notify.HideHop(true)
					return
				end
				print("PvP tag cleared, hopping now")
			else
				local countdown = tonumber(Config.Data.Another.HopCountdown) or 3
				Notify.ShowHop("Searching for a better server...", countdown, { title = "HOPPING SERVER" })
				task.wait(countdown)
			end
			hopRequested = false
			if Player.Character and Player.Character:FindFirstChild("HumanoidRootPart") then
				pcall(function()
					local root = Player.Character and Player.Character:FindFirstChild("HumanoidRootPart")
					if root then
						root.CFrame = CFrame.new(root.Position.X, 10000, root.Position.Z)
					end
				end)
			end
			Hop.Servers()
		end)
		hopRequested = false
		hopInProgress = false
	end)
end
SafeHop = Hop.Safe

function Hop.Servers(maxPlayers)
	local dontHop = false
	pcall(function()
		local limit = maxPlayers or (tonumber(Config.Data.Another.HopMaxPlayers) or 12)
		local minPlayers = tonumber(Config.Data.Another.HopMinPlayers) or 9
		local startTick = tick()
		repeat
			task.wait()
		until tick() - startTick >= 0.2

		local function DoHop()
			for page = 1, math.huge, 1 do
				if chosenRegion == nil or chosenRegion == "" then
					chosenRegion = "Singapore"
				else
					pcall(function()
						local serverBrowserUI = Player.PlayerGui:FindFirstChild("ServerBrowser")
						local regionBox = serverBrowserUI and serverBrowserUI.Frame.Filters.SearchRegion.TextBox
						if regionBox then
							regionBox.Text = chosenRegion
						end
					end)
				end
				local serverBrowser = ReplicatedStorage:FindFirstChild("__ServerBrowser")
				local servers = serverBrowser and serverBrowser:InvokeServer(page)
				if not servers then
					break
				end
				local bestServer = nil
				local fallbackServer = nil
				for jobId, info in pairs(servers) do
					if jobId ~= game.JobId then
						local count = tonumber(info.Count) or 0
						if count >= minPlayers and count <= limit then
							bestServer = { id = jobId, info = info }
							break
						elseif count > 0 and count < minPlayers and not fallbackServer then
							fallbackServer = { id = jobId, info = info }
						end
					end
				end
				local pick = bestServer or fallbackServer
				if pick then
					local jobId = pick.id
					local info = pick.info
						if dontHop then
							return
						end
						print("Hopping to server: " .. tostring(jobId) .. " (" .. tostring(info.Count) .. " players)")
						State.checked = {}
						SetState("targ", nil)
						stopBypass = false
						hopRequested = false
						Notify.ShowHop("Joining server with " .. tostring(info.Count) .. " players...", nil, {
							title = "JOINING SERVER",
							persist = true,
						})
						serverBrowser:InvokeServer("teleport", jobId)
						return true
					end
			end
			return false
		end

		if not getgenv().HopLoaded then
			local function checkPrompt(v)
				if v.Name == "ErrorPrompt" then
					if v.Visible then
						local errorTitle = v:FindFirstChild("TitleFrame") and v.TitleFrame:FindFirstChild("ErrorTitle")
						if errorTitle and errorTitle.Text == "Teleport Failed" then
							if not hopRetryQueued then
								hopRetryQueued = true
								dontHop = true
								setHopping(true)
								Notify.ShowHop(
									"Teleport failed. Retrying another server...",
									3,
									{ title = "RETRYING HOP" }
								)
								task.spawn(function()
									task.wait(3)
									hopRetryQueued = false
									if isHopping then
										Hop.Servers(maxPlayers)
									end
								end)
							end
							v.Visible = false
						end
					end
					v:GetPropertyChangedSignal("Visible"):Connect(function()
						if v.Visible then
							local errorTitle = v:FindFirstChild("TitleFrame")
								and v.TitleFrame:FindFirstChild("ErrorTitle")
							if errorTitle and errorTitle.Text == "Teleport Failed" then
								if not hopRetryQueued then
									hopRetryQueued = true
									dontHop = true
									setHopping(true)
									Notify.ShowHop(
										"Teleport failed. Retrying another server...",
										3,
										{ title = "RETRYING HOP" }
									)
									task.spawn(function()
										task.wait(3)
										hopRetryQueued = false
										if isHopping then
											Hop.Servers(maxPlayers)
										end
									end)
								end
								v.Visible = false
							end
						end
					end)
				end
			end
			local overlay = CoreGui:FindFirstChild("RobloxPromptGui")
				and CoreGui.RobloxPromptGui:FindFirstChild("promptOverlay")
			if overlay then
				for _, v in pairs(overlay:GetChildren()) do
					checkPrompt(v)
				end
				overlay.ChildAdded:Connect(checkPrompt)
			end
			getgenv().HopLoaded = true
		end

		while task.wait(0.1) do
			if dontHop then
				break
			end
			if DoHop() then
				break
			end
		end
	end)
end
HopServers = Hop.Servers

-- ============================================================================
-- 15) WEBHOOK — gửi thông báo Discord
-- ============================================================================
Webhook = {}

local AvatarCache = {}

local function GetWebhookConfig()
	local cfg = Config.Data or {}
	local enabled = true
	local url = ""

	if type(cfg.Webhook) == "table" then
		if cfg.Webhook.Enabled ~= nil then
			enabled = (cfg.Webhook.Enabled == true)
		elseif cfg.Webhook.Enable ~= nil then
			enabled = (cfg.Webhook.Enable == true)
		end
		url = cfg.Webhook.Url or cfg.Webhook.URL or cfg.Webhook.url or cfg.Webhook.Link or cfg.Webhook.link or cfg.Webhook.WebhookUrl or ""
	elseif type(cfg.Webhook) == "string" then
		url = cfg.Webhook
		enabled = (url ~= "")
	end

	if (not url or url == "") and type(cfg.WebhookUrl) == "string" then
		url = cfg.WebhookUrl
		enabled = true
	end
	if (not url or url == "") and type(cfg.DiscordWebhook) == "string" then
		url = cfg.DiscordWebhook
		enabled = true
	end

	if type(url) == "string" then
		url = url:match("^%s*(.-)%s*$")
	else
		url = ""
	end

	return enabled, url
end

local function formatBounty(bounty)
	bounty = tonumber(bounty) or 0
	if bounty >= 1000000 then
		return string.format("%.2fM", bounty / 1000000)
	elseif bounty >= 1000 then
		return string.format("%.1fK", bounty / 1000)
	else
		return tostring(math.floor(bounty))
	end
end

local function FindPlayerByName(name)
	for _, plr in pairs(Players:GetPlayers()) do
		if plr.Name == name then
			return plr
		end
	end
	return nil
end

local function GetPlayerAvatar(userId)
	if not userId or not tonumber(userId) or tonumber(userId) <= 0 then
		return THUMBNAIL_IMAGE
	end
	userId = tonumber(userId)
	if AvatarCache[userId] then
		return AvatarCache[userId]
	end

	local avatarUrl = THUMBNAIL_IMAGE
	pcall(function()
		local api = "https://thumbnails.roblox.com/v1/users/avatar-headshot?userIds="
			.. tostring(userId)
			.. "&size=420x420&format=Png&isCircular=false"
		local raw = nil
		if game and game.HttpGet then
			local getOk, res = pcall(function()
				return game:HttpGet(api)
			end)
		if getOk and res then
				raw = res
			end
		end
		if not raw and Executor.Request then
			local res = Executor.Request({
				Url = api,
				Method = "GET",
			})
			if res and (res.StatusCode == 200 or res.status_code == 200) then
				raw = res.Body or res.body
			end
		end

		if raw then
			local decoded = HttpService:JSONDecode(raw)
			if decoded and decoded.data and decoded.data[1] and decoded.data[1].imageUrl then
				avatarUrl = decoded.data[1].imageUrl
			end
		end
	end)

	AvatarCache[userId] = avatarUrl
	return avatarUrl
end

local function Send(url, data)
	if not url or url == "" then
		return false, "Webhook URL trống"
	end
	if not url:match("^https?://") then
		return false, "Webhook URL không hợp lệ: " .. tostring(url)
	end

	local encodeOk, jsonData = pcall(function()
		return HttpService:JSONEncode(data)
	end)
	if not encodeOk or not jsonData then
		return false, "Lỗi JSON Encode: " .. tostring(jsonData)
	end

	local reqOk, response = pcall(function()
		return Executor.Request({
			Url = url,
			Method = "POST",
			Headers = {
				["Content-Type"] = "application/json",
			},
			Body = jsonData,
		})
	end)

	if not reqOk then
		return false, "Lỗi gửi request: " .. tostring(response)
	end

	if type(response) == "table" then
		local statusCode = tonumber(response.StatusCode or response.status_code or response.Status)
		if statusCode then
			if statusCode >= 200 and statusCode < 300 then
				return true, response
			else
				local bodyText = tostring(response.Body or response.body or "")
				return false, "HTTP " .. tostring(statusCode) .. " - " .. bodyText
			end
		end
	end

	return true, response
end

function Webhook.SendKill(targetName, bountyEarned, currentBounty)
	local enabled, url = GetWebhookConfig()
	if not enabled or url == "" then
		return
	end

	task.spawn(function()
		pcall(function()
			targetName = tostring(targetName or "Unknown")
			local earned = tonumber(bountyEarned) or 0
			local curBounty = tonumber(currentBounty) or 0

			local myLevel = "?"
			pcall(function()
				if Player:FindFirstChild("Data") and Player.Data:FindFirstChild("Level") then
					myLevel = tostring(Player.Data.Level.Value)
				end
			end)

			-- Thông tin nạn nhân
			local victim = FindPlayerByName(targetName)
			local victimAvatar = GetPlayerAvatar(victim and victim.UserId)
			local victimTeam = victim and tostring(victim.Team) or "?"
			local victimLevel = "?"
			local victimFruit = "?"
			pcall(function()
				if victim and victim:FindFirstChild("Data") then
					if victim.Data:FindFirstChild("Level") then
						victimLevel = tostring(victim.Data.Level.Value)
					end
					if victim.Data:FindFirstChild("DevilFruit") then
						victimFruit = tostring(victim.Data.DevilFruit.Value)
					end
				end
			end)

			local myAvatar = GetPlayerAvatar(Player.UserId)

			-- Màu embed động theo số bounty ăn được
			local color = 0x00c8ff -- xanh dương mặc định
			if earned >= 1000000 then
				color = 0xffd700 -- vàng kim
			elseif earned >= 100000 then
				color = 0xff8c00 -- cam
			elseif earned >= 10000 then
				color = 0x00e676 -- xanh lá
			end

			local embed = {
				["title"] = "⚔️ BOUNTY HUNTER NOTIFICATION",
				["description"] = "🎯 Đã hạ gục **" .. targetName .. "**",
				["color"] = color,
				["fields"] = {
					{ ["name"] = "🎯 Target", ["value"] = "```" .. targetName .. "```", ["inline"] = true },
					{ ["name"] = "💀 Level", ["value"] = "```" .. victimLevel .. "```", ["inline"] = true },
					{ ["name"] = "🏴 Team", ["value"] = "```" .. victimTeam .. "```", ["inline"] = true },
					{ ["name"] = "🍎 Devil Fruit", ["value"] = "```" .. victimFruit .. "```", ["inline"] = true },
					{ ["name"] = "💰 Bounty Earned", ["value"] = "```+" .. formatBounty(earned) .. "```", ["inline"] = true },
					{ ["name"] = "💎 Current Bounty", ["value"] = "```" .. formatBounty(curBounty) .. "```", ["inline"] = true },
					{ ["name"] = "🦸 Hunter", ["value"] = "```" .. Player.Name .. "```", ["inline"] = true },
					{ ["name"] = "📊 Hunter Level", ["value"] = "```" .. tostring(myLevel) .. "```", ["inline"] = true },
					{ ["name"] = "🕐 Time", ["value"] = "```" .. os.date("%H:%M:%S %d/%m/%Y") .. "```", ["inline"] = true },
				},
				["author"] = {
					["name"] = Player.Name .. " (Hunter)",
				},
				["footer"] = {
					["text"] = "NatAov Hub Auto Bounty",
				},
				["timestamp"] = os.date("!%Y-%m-%dT%H:%M:%SZ"),
			}

			if victimAvatar and victimAvatar:match("^https?://") then
				embed["thumbnail"] = { ["url"] = victimAvatar }
			end
			if myAvatar and myAvatar:match("^https?://") then
				embed["author"]["icon_url"] = myAvatar
				embed["footer"]["icon_url"] = myAvatar
			end

			local data = {
				["embeds"] = { embed },
			}

			local ok, response = Send(url, data)
			if ok then
				print("[NatAovHub Webhook] Gửi webhook diệt địch thành công: " .. targetName)
			else
				warn("[NatAovHub Webhook] Lỗi gửi webhook diệt địch: " .. tostring(response))
			end
		end)
	end)
end

function Webhook.SendStartup()
	local enabled, url = GetWebhookConfig()
	if not enabled or url == "" then
		return
	end

	task.spawn(function()
		pcall(function()
			local currentBounty = 0
			pcall(function()
				local ls = Player:FindFirstChild("leaderstats")
				if ls then
					local b = ls:FindFirstChild("Bounty/Honor") or ls:FindFirstChild("Bounty / Honor") or ls:FindFirstChild("Bounty")
					if b then
						currentBounty = b.Value
					end
				end
			end)

			local myLevel = "?"
			pcall(function()
				if Player:FindFirstChild("Data") and Player.Data:FindFirstChild("Level") then
					myLevel = tostring(Player.Data.Level.Value)
				end
			end)

			local myAvatar = GetPlayerAvatar(Player.UserId)
			local teamStr = tostring(Config.Data.Team or (Player.Team and Player.Team.Name) or "Pirates")
			local worldStr = tostring(World.Current or "Unknown")

			local embed = {
				["title"] = "🚀 NatAov Hub - Auto Bounty Started",
				["description"] = "**Bounty Hunter** đang trực chiến! ⚔️",
				["color"] = 0x00c8ff,
				["fields"] = {
					{ ["name"] = "🦸 User Name", ["value"] = "```" .. Player.Name .. "```", ["inline"] = true },
					{ ["name"] = "📊 Level", ["value"] = "```" .. tostring(myLevel) .. "```", ["inline"] = true },
					{ ["name"] = "💎 Current Bounty", ["value"] = "```" .. formatBounty(currentBounty) .. "```", ["inline"] = true },
					{ ["name"] = "🏴 Team", ["value"] = "```" .. teamStr .. "```", ["inline"] = true },
					{ ["name"] = "🌍 World", ["value"] = "```" .. worldStr .. "```", ["inline"] = true },
					{ ["name"] = "📱 Executor", ["value"] = "```" .. tostring(Executor.Name) .. "```", ["inline"] = true },
				},
				["author"] = {
					["name"] = Player.Name,
				},
				["footer"] = {
					["text"] = "NatAov Hub Auto Bounty",
				},
				["timestamp"] = os.date("!%Y-%m-%dT%H:%M:%SZ"),
			}

			if myAvatar and myAvatar:match("^https?://") then
				embed["thumbnail"] = { ["url"] = myAvatar }
				embed["author"]["icon_url"] = myAvatar
				embed["footer"]["icon_url"] = myAvatar
			end

			local data = {
				["embeds"] = { embed },
			}

			local ok, response = Send(url, data)
			if ok then
				print("[NatAovHub Webhook] Gửi webhook khởi động thành công")
			else
				warn("[NatAovHub Webhook] Lỗi gửi webhook khởi động: " .. tostring(response))
			end
		end)
	end)
end
-- 16) LIFECYCLE — Start / Stop
-- ============================================================================
local function WaitRemotes()
	local remotesFolder = ReplicatedStorage:WaitForChild("Remotes", 15)
	if remotesFolder then
		Remotes = remotesFolder
		CommF = remotesFolder:WaitForChild("CommF_", 15)
		CommE = remotesFolder:FindFirstChild("CommE")
	end
end

function AutoBounty:Start()
	local self = self or AutoBounty
	if isRunning then
		warn("[NatAovHub] AutoBounty đã chạy rồi, bỏ qua Start")
		return self
	end
	isRunning = true
	connections = {}
	threads = {}

	SetState("weapon", nil)
	SetState("targ", nil)
	SetState("killed", nil)
	SetState("checked", {})
	SetState("killCount", 0)
	setHopping(false)

	WaitRemotes()
	pcall(function()
		local waitElapsed = 0
		repeat
			task.wait(0.1)
			waitElapsed = waitElapsed + 0.1
		until (game:IsLoaded() and Player:FindFirstChild("DataLoaded")) or waitElapsed >= 10

		if Player.PlayerGui:FindFirstChild("Main (minimal)") then
			if not getgenv().Team or getgenv().Team == "" then
				getgenv().Team = Config.Data.Team or "Pirates"
			end
			local targetTeam = Config.Data.Team or getgenv().Team or "Pirates"
			local TeamGui = Player.PlayerGui["Main (minimal)"]
			local chooseTeam = TeamGui:WaitForChild("ChooseTeam", 5)
			local Container = chooseTeam and chooseTeam:WaitForChild("Container", 5)
			local TeamButton = nil
			if Container then
				if targetTeam == "Pirates" and Container:FindFirstChild("Pirates") then
					TeamButton = Container.Pirates:WaitForChild("Frame", 5) and Container.Pirates.Frame:WaitForChild("TextButton", 5)
				elseif targetTeam == "Marines" and Container:FindFirstChild("Marines") then
					TeamButton = Container.Marines:WaitForChild("Frame", 5) and Container.Marines.Frame:WaitForChild("TextButton", 5)
				end
			end

			if TeamButton then
				local loopElapsed = 0
				repeat
					task.wait(0.1)
					loopElapsed = loopElapsed + 0.1
					pcall(function()
						if firesignal then
							if TeamButton:FindFirstChild("Activated") then
								firesignal(TeamButton.Activated)
							else
								firesignal(TeamButton.MouseButton1Click)
							end
						end
					end)
					if CommF then
						pcall(function()
							CommF:InvokeServer("SetTeam", targetTeam)
						end)
					end
				until not Player.PlayerGui:FindFirstChild("Main (minimal)") or loopElapsed >= 8
			end
		end

		if CommF then
			CommF:InvokeServer("SetTeam", Config.Data.Team or "Pirates")
		end
	end)

	local charLoaded = false
	local charAddedConn = Player.CharacterAdded:Connect(function()
		charLoaded = true
	end)
	local elapsed = 0
	repeat
		task.wait(0.1)
		elapsed = elapsed + 0.1
	until charLoaded or elapsed >= 5
	charAddedConn:Disconnect()

	local character = Player.Character or Player.CharacterAdded:Wait()
	repeat
		task.wait(0.1)
	until character:FindFirstChild("HumanoidRootPart") and character:FindFirstChild("Humanoid")
	print("Character loaded after team switch")

	local loadOk = pcall(function()
		loadstring(game:HttpGet("https://raw.githubusercontent.com/Dev-AnhTuanSiTinkk/Module/refs/heads/main/BloxFruitsModule/hunt.lua"))()
	end)
	if not loadOk then
		warn("[NatAovHub] Không thể load thư viện test.lua - chạy chế độ dự phòng")
	end
	elapsed = 0
	repeat
		task.wait(0.1)
		elapsed = elapsed + 0.1
	until not loadOk or Player.PlayerGui:FindFirstChild("Main") or elapsed >= 15

	World.Init()
	gunModeEnabled = Config.Data.Gun.GunMode

	UI.Build()
	Notify.Init()
	UI.Connect()

	Combat.Init()
	Hop.Init()
	Hunt.Init()

	getgenv().HopServers = HopServers
	getgenv().SkipPlayer = SkipPlayer

	task.delay(8, function()
		if isRunning then
			Webhook.SendStartup()
		end
	end)

	print("[NatAovHub] Auto Bounty started v" .. AutoBounty.Version)
	return self
end

function AutoBounty:Stop()
	local self = self or AutoBounty
	if not isRunning then
		return self
	end
	isRunning = false

	for _, c in ipairs(connections) do
		pcall(function()
			c:Disconnect()
		end)
	end
	connections = {}

	for plr, conn in pairs(pvpWatchers) do
		pcall(function()
			conn:Disconnect()
		end)
	end
	pvpWatchers = {}

	for _, th in ipairs(threads) do
		pcall(function()
			task.cancel(th)
		end)
	end
	threads = {}

	AntiStunCleanup()

	Visual.Cleanup()

	pcall(function()
		if originalNamecall then
			local rawMeta = Executor.RawMetatable(game)
			if rawMeta then
				Executor.SetReadOnly(rawMeta, false)
				rawMeta.__namecall = originalNamecall
				originalNamecall = nil
			end
		end
	end)

	pcall(function()
		if UI.Refs.ScreenGui then
			UI.Refs.ScreenGui:Destroy()
			UI.Refs.ScreenGui = nil
		end
	end)

	setHopping(false)
	stopBypass = false
	hopRequested = false
	hopInProgress = false
	HuntState.waitingForHop = false
	emptyNotifyShowing = false
	if hopNotifyThread then
		pcall(function()
			task.cancel(hopNotifyThread)
		end)
		hopNotifyThread = nil
	end

	print("[NatAovHub] Auto Bounty stopped")
	return self
end

function AutoBounty:GetState()
	local self = self or AutoBounty
	return State
end

return AutoBounty

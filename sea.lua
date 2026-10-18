-- Luraph runtime function (from the VM object, not part of the script: not lifted).
-- LPH_ENCFUNC decrypts a function this way: (key, encrypted buffer, ...) -> function.
local function luraph_runtime1(...)
	error("Luraph runtime function, not devirtualized")
end

local v = table.pack(...)

if not ce_like_loadstring_fn then
	if not l_fastload_enabled or not is_from_loader then
		game:GetService("Players").LocalPlayer:Kick("[Luarmor]: Use the loadstring, do not run this directly")
		wait(5)

		while true do
		end
	end
end

local str = "?"
loadstring = ce_like_loadstring_fn or loadstring
local flag = false

pcall(function()
	flag = true
	local UserGameSettings = UserSettings():GetService("UserGameSettings")

	if not UserGameSettings:GetTutorialState("nil  nil  ") then
		str = ""
		local n = ({ wait() })[1] * 1000000

		local function fn(arg)
			local n2 = 1103515245
			local n3 = 12345
			local n4 = 99999999
			local n5 = arg % 2147483648
			local n6 = 1

			return function(arg2, arg3)
				local v2 = n4
				local n7 = n2 * n5 + n3
				local n8 = n7 % v2 + n6
				n6 += 1
				n5 = n8
				n3 = n7 % 4858 * v2 % 5782
				return arg2 + n8 % arg3 - arg2 + 1
			end
		end

		local v2 = fn(n - n % 1)
		UserGameSettings:SetTutorialState("nil  nil  ", true)
		local n2 = 0

		for i = 1, 16 do
			local n3 = 0
			local n4 = 1

			for i2 = 1, 5 do
				local flag2 = v2(10, 20) > 15
				UserGameSettings:SetTutorialState("nil  nil  " .. n2, flag2)
				n3 += (flag2 and 1 or 0) * n4
				n4 *= 2
				n2 += 1
			end

			str ..= ("qwertyuiopasdfghjklzxcvbnm098765"):sub(n3 + 1, n3 + 1)
		end
	else
		str = ""
		local n = 0

		for i = 1, 16 do
			local n2 = 0
			local n3 = 1

			for i2 = 1, 5 do
				n2 += (UserGameSettings:GetTutorialState("nil  nil  " .. n) and 1 or 0) * n3
				n3 *= 2
				n += 1
			end

			str ..= ("qwertyuiopasdfghjklzxcvbnm098765"):sub(n2 + 1, n2 + 1)
		end
	end
end)

while not flag do
end

local now = os.clock()

if devsignature_sig then
	print([[        Luarmor - Lua whitelist service
        This is a signature - If you are seeing this, you know what not to do :3
        Have a good day!
        https://luarmor.net/
    ]])
end

local flag2 = nil
local flag3 = nil
local v2 = ({ table.unpack(v, 1, v.n) })[3]

if v2 and v2[1] then
end

local floor = math.floor
local random = math.random
local remove = table.remove
local char = string.char
local n = 0
local n2 = 2
local tbl = {}
local tbl2 = {}

for i = 1, 256 do
	tbl2[i] = i
end

repeat
	local v3 = random(1, #tbl2)
	local v4 = remove(tbl2, v3)
	tbl[v4] = char(v4 - 1)
until #tbl2 == 0

local tbl3 = {}

local function fn()
	if #tbl3 == 0 then
		n = (n * 149 + 744125792949) % 35184372088832

		repeat
			n2 = n2 * 43 % 257
		until n2 ~= 1

		local n3 = n2 % 32
		local n4 = floor(n / 2 ^ (13 - (n2 - n3) / 32)) % 4294967296 / 2 ^ n3
		local n5 = floor(n4 % 1 * 4294967296) + floor(n4)
		local n6 = n5 % 65536
		local n7 = (n5 - n6) / 65536
		local n8 = n6 % 256
		local n9 = n7 % 256
		tbl3 = { n8, (n6 - n8) / 256, n9, (n7 - n9) / 256 }
	end

	return table.remove(tbl3)
end

local tbl4 = {}
local v3 = tbl4

local function fn2(arg, arg2)
	local v4 = tbl4

	if not v4[arg2] then
		tbl3 = {}
		local v5 = tbl
		n = arg2 % 35184372088832
		n2 = arg2 % 255 + 2
		v4[arg2] = ""
		local n3 = 233

		for i = 1, #arg do
			n3 = (string.byte(arg, i) + fn() + n3) % 256
			v4[arg2] = v4[arg2] .. v5[n3 + 1]
		end
	end

	return arg2
end

local v4 = LUARMOR_SkipAntidebugDevMode
local v5 = LUARMOR_AllowKeyCheckSkip
local flag4 = ff97f23b97f93792992999 and ff97f23b97f93792992999() == v3[fn2("\28", 25249809554395)] or false
local v6 = v3[fn2("i\188\179R\145$\138\138\230\234=7Zwv\251\245\247\17\149D\\hg.st", 5102576865936)]
local v7 = USE_NON_SSL_NODE
local v8 = l_fastload_enabled
local n3 = os[v3[fn2("c\17\192\134", 34962100748080)]](os[v3[fn2("\246\230\tf", 19868051294279)]](v3[fn2("\25N", 16652096388244)])) - os[v3[fn2("S\177\150\214", 16392242936738)]](os[v3[fn2("k\249\251\239", 2889527429763)]](v3[fn2("\2111\128", 24725807553011)]))
local n4

if n3 < 0 then
	n4 = (86400 + -(-n3 % 86400)) % 86400
else
	n4 = n3 % 86400
end

local n5 = n4 / 3600

if n5 >= 21 or n5 < 5 then
	local tbl5 = {}
	local v9 = v3[fn2("\\\182|Gn\254G\2351\136\177{\1475\246\140\129\189\185\157ܐl\238Ƅ\20", 6285876467422)]
	local v10 = v3[fn2("\140\173\221:B\244r\133\163\15E\183!\228\16\25\148}|\0249\4\214\219\198\247'", 23623041046)]
	tbl5[1] = v9
	tbl5[2] = v10
	v6 = tbl5[math[v3[fn2("\146\14\"\6\142P", 17439173164913)]](1, 2)]
elseif n5 >= 5 and n5 < 15 then
	local tbl5 = {}
	local v9 = v3[fn2("\185$_ \253\31b\155\5E\168\223\241&\222\201\253\216\209\7%ی\29\243\175\16", 17467091304331)]
	local v10 = v3[fn2("m^\168\145J\220\253\208o2kr\23G\159q\184\8ˍ\3)\18\1475\211)", 15168139900718)]
	local v11 = v3[fn2("\143?\205S\254\165f\14\175\0\147)d\229\253\253G\211\194\237$\26\213\nw\221G", 4706354041119)]
	local v12 = v3[fn2("?&\166\0\4\151qG\192O\234\0\179u\254ر\255\135/\r_g\15\135\243\237", 1839375877809)]
	local v13 = v3[fn2("ͪm'd\r\3\15LR'պ\237\230\181\"\6\241\177\181\197r v\23\231", 2741346535929)]
	local v14 = v3[fn2("\131\136\217\225\241QJ\212\0283\182\251顬U(\130\254e%\19\194~\241\2\17", 20227765782934)]
	local v15 = v3[fn2("\172\23\30~i#\133V}UZڛ\218Ɩ\255j\30\213\0208\200i\221\251V", 3867736083986)]
	local v16 = v3[fn2("\151mʬ\241\211K\183\27z5[\255F3\195V\131\196\12\21\157\151ZS\162S", 24075100149653)]
	local v17 = v3[fn2("\178\231/\228\14G\132\175b\219\228#\218A\16\29\128@:\179\222\252H\5\197\15\254", 5319479333722)]
	local v18 = v3[fn2("t,\189\1337\159\236۪-G\181\163!\205mT\247+\179\245u\2114[V\195", 17471386402703)]
	local v19 = v3[fn2("\247\170\254#\184\140\219B\20\210%ٽ\153C\184\159\0190\128\144l\211\246\141\3\22", 27240587649817)]
	tbl5[1] = v9
	tbl5[2] = v10
	tbl5[3] = v11
	tbl5[4] = v12
	tbl5[5] = v13
	tbl5[6] = v14
	tbl5[7] = v15
	tbl5[8] = v16
	tbl5[9] = v17
	tbl5[10] = v18
	tbl5[11] = v19
	v6 = tbl5[math[v3[fn2("\163X@\235\251\134", 29665170680811)]](1, 11)]
elseif n5 >= 15 and n5 < 21 then
	local tbl5 = {}
	local v9 = v3[fn2("D\\-\235\231\1379\146\8\173\159\209^\25'\27\251\1866!\28v\205(\171\178d", 31701047309139)]
	local v10 = v3[fn2("\29\"\224=Q\130i\205Ɏ\136\141\182\3\162\181\217\219i\"`\244\179\151\212\245N", 18405570298613)]
	local v11 = v3[fn2("6\28G\139fN4\171\216\227\7\232\255\30\245\181\6B}3X\206M1 b\217", 47246082092)]
	tbl5[1] = v9
	tbl5[2] = v10
	tbl5[3] = v11
	v6 = tbl5[math[v3[fn2(",\137OC\20\12", 29448268213025)]](1, 2)]
else
	game:GetService(v3[fn2("\153p\142\19232\142", 3753915977128)])[v3[fn2("9I\159\145\136\245\181&\177\7f", 24828889913939)]]:Kick(v3[fn2("\29\177WB\247%\210`\158d\157p\130\199\0\238⌭\252\130\247d\131\182\183\17\142τ\177\246F\246kln\180\147\147\251\195)\11wV\135sq\189\2450\0Q\210\218E}\237y\2\19\157[", 34151400930365)])
end

pcall(function()
	if game:GetService(v3[fn2("\236\245\tg\135\232\191\220\235~Z\n\232o\190/\233\151\12", 22175592894636)]):GetCountryRegionForPlayerAsync(game:GetService(v3[fn2("_\212\229t4\166%", 30523116580618)])[v3[fn2("\185\226\159އ\135\207;\186\rS", 9450290192993)]]) == v3[fn2("\150\249", 33178561149107)] then
		local tbl5 = {}
		local v9 = v3[fn2("\166\139\23\184\166\243\158v\158\251\147\25\172\131\228\221%\213J.\158M*\194}\209\249", 4854534934953)]
		local v10 = v3[fn2("\1865\224<\249\134\205\202\198xkgd=S\160\243q,\253\17\248\208\217\253\133\136", 29740334902321)]
		local v11 = v3[fn2("\138\203▛ȢpҺ\208\22}\171ƹoH\184\235\167=^\22l\132\155", 17810699174091)]
		local v12 = v3[fn2("\201u`\187\to\153Õ\163\185\243}\162\12ԇBIt\20\\\163#\197\0\149", 24492798466330)]
		local v13 = v3[fn2("\26\154\4;\16\8V\31\186\1ݯc\28Δ9͝\158\22\6#\141\153\252\213", 19178688005573)]
		tbl5[1] = v9
		tbl5[2] = v10
		tbl5[3] = v11
		tbl5[4] = v12
		tbl5[5] = v13
		v6 = tbl5[math[v3[fn2("\154,6\21\155e", 15164918576939)]](1, 5)]
	end
end)

local tbl5 = { [v3[fn2("l\227\11\179\225n\252", 31942646592564)]] = v3[fn2("\137\145&", 9647864718105)] }
tbl5[v3[fn2("\243\225,t", 24012821223259)]] = flag4 and LT_R_RRT_H or v3[fn2("\182,\28\11ly*S", 26101312806644)] .. v6
tbl5[v3[fn2("Ì\192\239\173d(z", 27895590151547)]] = "f7fb20d3bbdf4ef86ef18caebae5b838"
tbl5[v3[fn2("\232\208\203w\147\240\162\231-\23<\135\27", 7323142724260)]] = "0013"
tbl5[v3[fn2("\246\214\214~", 34872977456861)]] = "main"

if v7 then
	tbl5[v3[fn2("\230\11\18\201", 30037770464582)]] = v3[fn2("\15\179\200J\18R\251\249w\150mt\174\29\22\142 \245\202_\26؋\198lR\185", 8312089124413)]
	v6 = v3[fn2("-ם\250\\H\172\7\n\1989Fޡ\192\193\170}\186\155", 30359902842482)]
end

local flag5 = type(({ table.unpack(v, 1, v.n) })[1]) ~= v3[fn2("\2202\170-\230", 3699153472885)]
local fn3 = nil
local n6 = nil
local tbl6 = nil
local tbl7 = nil
local flag6 = nil
local v9 = nil
local tbl8 = nil
local v10 = print
local v11 = next
local v12 = string[v3[fn2("FM\144\149", 6238630385330)]]
local v13 = identifyexecutor
local v14 = game
local v15 = pcall
local v16 = string[v3[fn2("|\224s\254\149\221", 19958248360091)]]
local v17 = debug[v3[fn2("gh\167\183XX'\183n", 2390222244018)]]
local v18 = tonumber
local v19 = setmetatable
local v20 = rawget
local v21 = wait
local v22 = debug[v3[fn2("\228\239\219\238\248\152\159", 20594996693740)]]
local v23 = loadstring
local v24 = os[v3[fn2("P\251\141\5", 13452248101104)]]
local v25 = string[v3[fn2("\194\242\141\159", 7762316532797)]]
local v26 = string[v3[fn2("\221\27\146", 24183551383546)]]
local v27 = spawn
local v28 = game:GetService(v3[fn2("\19\tN\216~A9Z\167\142", 29354849823434)])[v3[fn2("\172\18\163{Aс\1980", 27338301137780)]]
local v29 = os[v3[fn2("\226x\210\210Z", 7857882471574)]]
local v30 = math[v3[fn2("(-G\14", 10033349796992)]]
local v31 = tostring
local v32 = pairs
local v33 = string[v3[fn2("\254\159F-", 25494630161599)]]
local v34 = getgenv
local flag7 = false

local function fn4(arg, arg2)
	v23(v3[fn2("\204h\133\201/\160ܐ?z\25\218?\237I27\133P\240\253ڱGR4\160\203d\240$\3\219Ǟ\154\220#\n\149\15\1755g+]3g\30\221џ\150\2137\208\26\21\252Q`Seq\26\t\12\r\250\12\141\130C\171\157\217ސ\8B\210\193\136\15\253\153\236.\253Ə\193\182˔\4&\193\162ڢ|11\23lef@\214QJ5\207 \0193\181\246\171N\226(ӭ\255\12\155vt\135\229Ӏ\177qU\206\251\245-<K\210\233D@\131\161u\134\243ݍG\137A-X\217\229\6\252\227\241\239!\148%\188\160\3\178m\u{F54A}\19\209m&\134\24\184\155\244w@:y\180@\190\171f\7B\31]t.\242\231\254\215n\166㫸\225/\29\181B?܅6Lw\223\25Q\254^5\174\27N\250j\227\178\11\241\12\156&\250\236Am\135\179\156+\220\217&^\225\244\140,A\2514\212\7#\237\1\216\236H?~<AF\242\3_\162\0\206}\129.T\208\1\171@\245ޮ]\r\145\149\2蝺m\127u\169\2419\214U\233 \229\225;\187\28G\156\157\229\251v}\12\19\231\7\170\249\127\1828\26\142\201#\220\221\250\225\30\222Q`\144v\223\t\188_X\138\5\143", 19311836055105)])(arg, arg2)

	while v21() do
	end
end

local v35 = script_key or v3[fn2("Pݕ\173", 27215890834178)]
local n7 = 0
local flag8 = false

v27(function()
	flag8 = true

	while not flag6 do
		n7 += 1
		v28:Wait()
	end
end)

while not flag8 do
	v28:Wait()
end

local function fn5()
	local v36 = n7

	while n7 == v36 do
		v28:Wait()
	end
end

local function fn6(arg)
	if arg then
		error("devirt: for loop without back edge")
	end

	while v21() do
	end
end

local function fn7(arg)
	for i = 1, 2 do
		local n8 = arg % 9915 + 4
		local n9 = nil
		local n10 = nil

		for i2 = 1, 3 do
			n9 = arg % 4155 + 3

			if i2 % 2 == 1 then
				n9 += 522
			end

			n10 = arg % 9996 + 1

			if n10 % 2 ~= 1 then
				n10 *= 3
			end
		end

		local n11 = arg % 9999995 + 1 + 2790
		local n12 = arg % 1000
		local n13 = fn3((arg - n12) / 1000) % 1000
		local n14 = arg % (n8 * n9 + 9999) + 2790
		arg = (n12 * n13 + n11 + arg % (419824125 - n11 + n12) + (n14 + n12 * n9 + n13) % 999999 * (n11 + n14 % n10)) % 99999999999
	end

	return arg
end

local n8 = 1
local v36 = syn and syn[v3[fn2("\186\\mٕ\138K", 16095881149070)]] or request or http_request

if v13 and ({ v13() })[1] == v3[fn2("v\228\23\235/\218V", 20664792042285)] then
	n8 = 9
elseif v13 and ({ v13() })[1] == v3[fn2("\205a\217  @o\162\30C", 27341522461559)] then
	if ({ v13() })[2] == v3[fn2("\158Q\31", 20984776870999)] then
		n8 = 5
	else
		n8 = 2
	end
elseif FLUXUS_LOADED or EVON_LOADED or WRD_LOADED or COMET_LOADED or OZONE_LOADED or TRIGON_LOADED then
	n8 = 4
elseif KRNL_LOADED then
	n8 = 3
elseif Electron_Loaded then
	n8 = 6
elseif v13 and ({ v13() })[1] == v3[fn2("\191\127\180+\163\159\14", 3281455156208)] then
	n8 = 7
elseif v13 and ({ v13() })[1] == v3[fn2("\28\182aBS\4", 30834511212588)] then
	n8 = 11
elseif v13 and ({ v13() })[1] == v3[fn2("\157\20.\20\250\144!P\196", 27855860491606)] then
	n8 = 11
elseif v13 and ({ v13() })[1] == v3[fn2("\1660", 17434878066541)] then
	n8 = 11
elseif v13 and ({ v13() })[1] == v3[fn2("\166\22\165\6", 28269263709911)] then
	n8 = 11
elseif v13 and ({ v13() })[1] == v3[fn2("\221Z\4}=", 28654748788798)] then
	n8 = 11
elseif v13 and ({ v13() })[1] == v3[fn2("\243\16\193\253\23", 31622661763850)] then
	n8 = 15
end

if v13() == v3[fn2("\191ק\127", 1049077777361)] then
	n8 = 11
end

local function fn8(arg, arg2)
	tbl7 = {}
	tbl6 = {}

	for i = 0, arg do
		local v37 = v12(i)
		tbl6[i] = v37
		tbl6[v37] = i
	end

	for i = 1, #arg2 do
		local v37 = arg2[i]
		tbl7[i - 1] = v37
		tbl7[v37] = i - 1
	end
end

local tbl9 = {}
local v37 = v3[fn2("\247", 27328637166443)]
local v38 = v3[fn2("y", 25973533630077)]
local v39 = v3[fn2("2", 30949405094039)]
local v40 = v3[fn2("p", 34504672771462)]
local v41 = v3[fn2("\245", 27891295053175)]
local v42 = v3[fn2("\r", 15420476930073)]
local v43 = v3[fn2("j", 16699342470336)]
local v44 = v3[fn2("\236", 10262063785301)]
local v45 = v3[fn2("P", 942774092654)]
local v46 = v3[fn2("\158", 30592911929163)]
local v47 = v3[fn2("\189", 30830216114216)]
local v48 = v3[fn2("v", 25122030377828)]
local v49 = v3[fn2("\227", 26024001035948)]
local v50 = v3[fn2("\160", 7296298359435)]
local v51 = v3[fn2("\29", 6518885554103)]
local v52 = v3[fn2("\239", 19802551044106)]
tbl9[1] = v37
tbl9[2] = v38
tbl9[3] = v39
tbl9[4] = v40
tbl9[5] = v41
tbl9[6] = v42
tbl9[7] = v43
tbl9[8] = v44
tbl9[9] = v45
tbl9[10] = v46
tbl9[11] = v47
tbl9[12] = v48
tbl9[13] = v49
tbl9[14] = v50
tbl9[15] = v51
tbl9[16] = v52
fn8(255, tbl9)

fn3 = function(arg)
	return arg - arg % 1
end

local function fn9(arg)
	local n9 = 1103515245
	local n10 = 12345
	local n11 = 99999999
	local n12 = arg % 2147483648
	local n13 = 1

	return function(arg2, arg3)
		local v53 = n11
		local n14 = n9 * n12 + n10
		local n15 = n14 % v53 + n13
		n13 += 1
		n12 = n15
		n10 = n14 % 4859 * v53 % 5781
		return arg2 + n15 % arg3 - arg2 + 1
	end
end

local function fn10(arg)
	for i = 1, 2 do
		local n9 = arg % 9915 + 4
		local n10 = nil
		local n11 = nil

		for i2 = 1, 3 do
			n10 = arg % 4155 + 3

			if i2 % 2 == 1 then
				n10 += 522
			end

			n11 = arg % 9996 + 1

			if n11 % 2 ~= 1 then
				n11 *= 3
			end
		end

		local n12 = arg % 9999995 + 1 + 2790
		local n13 = arg % 1000
		local n14 = fn3((arg - n13) / 1000) % 1000
		local n15 = arg % (n9 * n10 + 9999) + 2790
		arg = (n13 * n14 + n12 + arg % (419824125 - n12 + n13) + (n15 + n13 * n10 + n14) % 999999 * (n12 + n15 % n11)) % 99999999999
	end

	return arg
end

local function fn11()
end

local function fn12(arg)
	local tbl10 = {}
	local tbl11 = {}
	local tbl12 = {}

	for i = 1, 13 do
		local tbl13 = {}
		local tbl14 = {}
		tbl10[tbl13] = tbl14
		tbl11[tbl14] = i
		tbl12[tbl13] = tbl14
	end

	if arg then
		tbl10 = arg[1]
		tbl11 = arg[2]
		tbl12 = arg[3]
	end

	local n9 = 0
	local n10 = 0
	local n11 = 0

	for k, v53 in v11, tbl10, nil do
		local v54 = tbl11[v53]

		if tbl12[k] == v53 then
			n9 += 1
		end

		n10 += 1
		n11 = n10 % 2 == 0 and n11 * v54 or n11 + v54 + n10
	end

	if n9 ~= 13 then
		n6 = -1
	end

	tbl8 = { tbl10, tbl11, tbl12 }
	n6 = n11
	return false
end

local function fn13(arg)
	for i = 1, 2 do
		local n9 = arg % 9915 + 4
		local n10 = nil
		local n11 = nil

		for i2 = 1, 3 do
			n10 = arg % 4155 + 3

			if i2 % 2 == 1 then
				n10 += 522
			end

			n11 = arg % 9996 + 1

			if n11 % 2 ~= 1 then
				n11 *= 3
			end
		end

		local n12 = arg % 9999995 + 1 + 2790
		local n13 = arg % 1000
		local n14 = fn3((arg - n13) / 1000) % 1000
		local n15 = arg % (n9 * n10 + 9999) + 2790
		arg = (n13 * n14 + n12 + arg % (419824125 - n12 + n13) + (n15 + n13 * n10 + n14) % 999999 * (n12 + n15 % n11)) % 99999999999
	end

	return arg
end

local function fn14(arg)
	for i = 1, 2 do
		local n9 = arg % 9915 + 4
		local n10 = nil
		local n11 = nil

		for i2 = 1, 3 do
			n10 = arg % 4155 + 3

			if i2 % 2 == 1 then
				n10 += 522
			end

			n11 = arg % 9996 + 1

			if n11 % 2 ~= 1 then
				n11 *= 3
			end
		end

		local n12 = arg % 9999995 + 1 + 2790
		local n13 = arg % 1000
		local n14 = fn3((arg - n13) / 1000) % 1000
		local n15 = arg % (n9 * n10 + 9999) + 2790
		arg = (n13 * n14 + n12 + arg % (419824125 - n12 + n13) + (n15 + n13 * n10 + n14) % 999999 * (n12 + n15 % n11)) % 99999999999
	end

	return arg
end

local function fn15(arg)
	local n9 = 1103515245
	local n10 = 12345
	local n11 = 99999999
	local n12 = arg % 2147483648
	local n13 = 1

	return function(arg2, arg3)
		local v53 = n11
		local n14 = n9 * n12 + n10
		local n15 = n14 % v53 + n13
		n13 += 1
		n12 = n15
		n10 = n14 % 4859 * v53 % 5781
		return arg2 + n15 % arg3 - arg2 + 1
	end
end

local n9 = 68
fn11(67, v3[fn2("L", 13426477510872)], v3[fn2("\152\18\1646\165\234\196u\130 \1736(8@\157\r\161h\2496^}\184H\1650[", 27850491618641)])
n6 = -1
fn12()

while n6 == -1 do
end

local v53 = fn15(n7 + n6)

if n8 == 9 or n8 == 15 then
	local n10 = 0

	v15(function()
		local function fn16(arg)
			v31(arg[1])
		end

		fn16(v19({}, { [v3[fn2("ŉ\168\23\244\181\15", 3991220162181)]] = function()
			local fn17 = nil

			fn17 = function()
				n10 += 1
				return fn17()
			end

			fn17()
		end }))
	end)

	local n11 = 0

	v15(function()
		v36(v19({}, { [v3[fn2("Sp\195=\29\220g", 3642243419456)]] = function()
			local fn16 = nil

			fn16 = function()
				n11 += 1
				return fn16()
			end

			fn16()
		end }))
	end)

	if n11 + n10 < 20000 then
		n9 = 19
	elseif n11 - n10 ~= 0 then
		n9 = 189
	end
end

local function fn16(arg, arg2, arg3)
	local v54 = v3
	local tbl10 = { [v3[fn2(".\n\163ռ\161", 32844617250684)]] = v54[fn2("\212n\202", 19019769365809)] }

	if arg2 then
		tbl10 = v19(tbl10, { [v3[fn2("\252JM\152 \168\163", 15324910991296)]] = function(arg4, arg5)
			if arg5 == v3[fn2("\19&N", 2813289433660)] then
				local v55 = v3
				local v56 = v16(v17(), v55[fn2("\179\216]\142\12\173lJ}\1.", 7904054779073)])
				local v57 = v56()
				local v58 = v56()
				local n10 = 1

				v15(function()
					n10 = v18(v58) - v18(v57)
				end)

				if (n8 == 9 or n8 == 15) and (n10 ~= 0 or v57 ~= v58) then
					n9 = 121

					while arg3 do
					end
				end

				return arg
			end

			return v20(tbl10, arg5)
		end })
	else
		tbl10[v3[fn2("\187\154\151", 30226754792950)]] = arg
	end

	local v55 = v36(tbl10)

	if v55[v3[fn2("\202*\172\152\3\239\212\19\167Z", 12094997015552)]] == 0 then
		if flag7 then
			warn(v3[fn2("\151/X\27\177\221m\242\241\196\198w\189J8\241\16\22</\20\135!q\167^\23h\231\151ĽfT\146\254;D1\243\161\255l\190\250\19\0217\140\14T\0202v/6\132)p\147\173m\205ỡ \161YE\136\4.ۂ\166k\2141\227~I\251fw\250\194E\231?", 15689994352916)])
		end

		local v56 = v3
		writefile(v3[fn2("\26\2278~lh|\u{EACE}\30\198\\\135\193a\215\212\248\177V", 28497977698220)], v56[fn2("b\191\135\226\194fU\223\222\248,\149\4\rT\171x\1\19\246v\161T\222\202\26g>\171g\7\236\1362@\162;\\\166\251\19\195?\16\172@\29\19\215ƈ\21\249\0p\175\129\240\179\163\240\143wGC/I\1!\14\215\25Z\135\237X \3\153(66W\152\244>\215@ٱ", 6626263013403)])
	end

	return v55[v3[fn2("'\211\220\233", 24497093564702)]], v55[v3[fn2("I\247\208\240\20\157g", 20429635406418)]]
end

fn5()

local function fn17(arg)
	if v34()[8753563] == 22044 and n8 ~= 11 then
		if flag7 then
			warn(v3[fn2("\30\246oＫ(\159G\239\1808S1o\244\163c\201G\14V\6\188\218<\226,\29;\139\236\194oW\218\207Qj\247?\31\245WqpR\213\228l\6|\t\247R\28\169\\\138\210O\2275\255T[\150b4\14\223\213*\209\30\rhƽ\255\250\235\170y\155\219\14\253\173m\143\231kc%\242\129ql\23\178\196\t\167\230\182\25\128u\31^[_\2402\213B2y\28\153\131\189B\1\8\160\191R\25*\185s\168\240\253i\254\176\137j*5\131\228\168p\142\8\216D\209\u{7B4}_*\24K\202u\202\249\176-dc\249ܩ\204\19\133\251\246\214\18\140\17'X\225\227]\194<_\"\156\131 \171\133!\146\143\215\196\\\157͢", 2624305105292)])
		end

		v27(function()
			v21(5)
			v34()[8753563] = nil
		end)

		fn6()
	end

	v34()[8753563] = 22044
	local flag9 = false
	local tbl10 = { v22, v19, v31 }

	tbl10[-1] = n8 == 3 and function()
	end or v36

	local v54 = v26
	local v55 = v25
	local v56 = v24
	local v57 = v23
	local v58 = v15
	tbl10[4] = v12
	tbl10[5] = v54
	tbl10[6] = v55
	tbl10[7] = v56
	tbl10[8] = v57
	tbl10[9] = v58

	local function fn18()
		flag9 = true
		return v3[fn2("\134", 18259536953965)]:rep(16777215)
	end

	local v59 = v19({}, { [v3[fn2("f\138\r\15#0;o\243\235", 3421045853298)]] = function()
		flag9 = true
		return v3[fn2("\210", 31637694608152)]:rep(16777215)
	end })

	for k, v60 in v11, tbl10, nil do
		if k ~= -1 then
			local flag10 = n8 ~= 11

			if flag10 then
				local v61 = v3
				flag10 = v22(v60)[v61[fn2("Z\147\159\228", 20054888073461)]] == v3[fn2("$\155\205", 26973217776160)]
			end

			if flag10 then
				flag9 = true
			end
		end

		if v60 ~= v10 and v60 ~= v31 then
			local v61 = v10
			local v62 = v31
			local v63 = error
			local env = getfenv()
			env[v3[fn2("\221\194(\142[\234\176\127", 25788844400081)]] = fn18
			env[v3[fn2(",d߫\226", 4076048355028)]] = fn18
			env[v3[fn2("\19\248=\240R", 27063414841972)]] = fn18

			if k == -1 then
				if n8 ~= 5 then
					v15(v60, v3[fn2("", 33754104330955)])
				end
			else
				v15(v60, v59)
			end

			env[v3[fn2("\133\208A\235\231\156\250+", 27092406755983)]] = v62
			env[v3[fn2("͙\1313x", 7037518682522)]] = v61
			env[v3[fn2("\190\172\160;\162", 28420665927524)]] = v63
		end
	end

	if flag9 and n8 ~= 11 then
		n9 = 85

		if arg then
			fn6(true)
		end
	end

	v34()[8753563] = nil
end

local v54 = n7
local v55 = nil
local flag9 = nil

while true do
	local v56 = v15(function()
		local v56 = fn16
		local v57 = v3
		v55 = v56(tbl5[v3[fn2("\177\153-\186", 20435004279383)]] .. v57[fn2("\136\29\133\158\152|\183", 27607818560623)], n8 == 9 or n8 == 15)
		local data = v14:GetService(v3[fn2("\18+\218z\19R\150\132\151\204\\", 24806340647486)]):JSONDecode(v55)

		if not data[v3[fn2("\170ktʥs", 20678751111994)]] then
			warn(data[v3[fn2("\222?ۤ\132\195I", 27760294552829)]])
			fn6()
		end

		if not data[v3[fn2("ր\178C\148E:\131", 27969680598464)]][tbl5[v3[fn2("\223hF\178}\182\195", 9183994093929)]]] then
			warn(v3[fn2(";p\232\194O\137O\170J\176\178c8ǿ\230*\141x\2140\127o\219o\1\250gU\226\237\229|m\158s\r\139x\132x\136椯\"\173X\\\232\162)\3\228", 5848850208071)])
			fn6()
		end

		tbl5[v3[fn2("\135\22T\225", 32883273136032)]] = flag4 and LT_R_RRT_H or v7 and v3[fn2("\7\192\16VM\203\7\233\219\217*w'\241\171\207\247\236\0\195\2\154S]\167\147\203", 12416055618859)] or v3[fn2("\165-Kͫ\216)\134", 31736481870708)] .. v6
		local v58 = tbl5
		local v59 = v3
		v9 = data[v3[fn2("ʛ\135Y\192\183d\185", 14786949920203)]][v58[v59[fn2("\202R\200#\227\26\246", 4772928065885)]]]
	end)

	fn5()

	if not v56 then
		if flag9 then
			break
		end
		fn11(69, v3[fn2("\25", 31670981620535)], v3[fn2("\143\229\31#\3\127\186\25R\236\2377\167\158\134\30\242\\\rU_\180\15\30\151\16\151\201", 16353587051390)])
		v6 = v3[fn2("ge1\165\149mj\234\165\193\248\11N\170\186\240\7㙊\1285\207)\218en", 19540550043414)]
		tbl5[v3[fn2("y01\134", 15793076713844)]] = flag4 and LT_R_RRT_H or v3[fn2("Yz\179\216]Z\169'\26\156\175\162\1l\196u\247\205n\249G\138ds\149Q\153\"xe\143!\129\15<", 7585143724952)]
		flag9 = true
	end

	if not v56 then
		continue
	end

	local function fn18(arg)
		local n10 = 1103515245
		local n11 = 12345
		local n12 = 99999999
		local n13 = arg % 2147483648
		local n14 = 1

		return function(arg2, arg3)
			local v57 = n12
			local n15 = n10 * n13 + n11
			local n16 = n15 % v57 + n14
			n14 += 1
			n13 = n16
			n11 = n15 % 4859 * v57 % 5781
			return arg2 + n16 % arg3 - arg2 + 1
		end
	end

	local n10 = n7 % 8585 * v54 % 9910
	fn17()

	if flag5 then
		n9 = 146
	end

	fn11(85, v3[fn2("\24", 21972649496559)], v3[fn2("\187i\181\209XW\149\167\254\\Ѧ\228\148z\20\27\26\150\3\8\145x$\141", 24700036962779)])
	local v57 = fn18(n10 + v53(2, 4096))
	local v58 = v53(1111, 32768)
	local n11 = 12000 + ((1398563873 * ((1398563873 * (1361 + n10 + n6 % 1000 + n6) % 1610612736 + 22491) % 95716599 + 1) + 22491) % 95716599 + 1) % 120000 - 12000 + 1
	local tbl10 = { n11 + v57(100000, 1000000), v58, n11 + v53(3333, 15625) + n7, (v57(10000, 1000000)) }
	n6 = -1
	fn12()
	local flag10 = false

	if n6 == -1 then
		n6 = 100
		flag10 = true
	end

	local n12 = 0
	local n13 = 0
	local n14 = 0
	local n15 = 1
	local tbl11 = { [0] = 0 }

	local function fn19(arg, arg2, arg3)
		arg2 = arg2 and arg or tbl6[arg]

		if not arg3 then
			arg2 = (arg2 + 4096 - tbl11[n12]) % 256
			n14 += arg2
			n12 = (n12 + 1) % n15
		end

		local n16 = arg2 % 16
		return tbl7[(arg2 - n16) / 16] .. tbl7[n16]
	end

	local function fn20(arg)
		local n16 = 0

		for i = 1, #arg do
			n16 += v25(arg, i)
		end

		return n16
	end

	local function fn21(arg, arg2)
		local v59 = tbl7
		local n16 = (tbl7[v26(arg, 1, 1)] * 16 + v59[v26(arg, 2, 2)] + tbl11[n13]) % 256
		n13 = (n13 + 1) % n15
		if arg2 then
			return n16
		end
		return tbl6[n16]
	end

	local function fn22(arg)
		local tbl12 = {}
		n13 = 0
		local n16 = 1

		while true do
			local v59 = fn21(v26(arg, n16, n16 + 1), true)
			n16 += 2
			local v60 = v3[fn2("", 2271033264195)]

			for i = 1, v59 do
				v60 ..= fn21(v26(arg, n16, n16 + 1))
				n16 += 2
			end

			tbl12[#tbl12 + 1] = v60
			if not (n16 > #arg) then
				continue
			end
			break
		end

		return tbl12
	end

	local function fn23(arg, arg2)
		local v59 = fn19(#arg, true, arg2)

		for i = 1, #arg do
			v59 ..= fn19(v26(arg, i, i), false, arg2)
		end

		return v59
	end

	local function fn24(arg, arg2, arg3)
		if arg == 1 then
			tbl11 = arg2
			n15 = arg3
		elseif arg == 2 then
			n12 = 0
			n14 = 0
		elseif arg == 3 then
			return n14
		end
	end

	local v59 = fn15(v53(2, 32768 + v24() % 2000) + n6 % 4096)
	local v60 = fn9(v57(1, 32768) + n7 + v24() % 1000)
	local v61 = v59(111111, 999999)
	local tbl12 = {}

	for i = 1, v61 % 30 + 1 do
		local fn25

		if i == 2 then
			fn25 = v31
		elseif i == 8 then
			fn25 = v10
		elseif i == 17 then
			fn25 = v26
		else
			fn25 = function()
			end
		end

		tbl12[i] = fn25
	end

	local n16 = v60(111111, 999999) + 3639
	local n17 = v59(1, 1234) * v60(2, 1235) + n6 % 80000
	local n18 = 10000 + ((1445613873 * ((1445613873 * (n11 + n6) % 1627389952 + 23515) % 94716599 + 1) + 23515) % 94716599 + 1) % 100000 - 10000 + 1
	local tbl13 = { n18 + v59(100000, 1000000), n18 + v60(100000, 1000000), (v59(100000, 1000000)) }
	v4 = v4 or v5

	if v4 then
		n9 = 218
	end

	if flag10 then
		n9 = 250
	end

	local v62 = tbl13[1]
	local n19 = 8988 + tbl10[4]
	local n20 = tbl10[2] + 3639
	local n21 = 9934 + tbl10[1]
	local str2 = ((((((fn23(v3[fn2("", 9937783858215)] .. n16) .. fn23(v3[fn2("", 6043203409404)] .. fn13(9934 + v61) .. fn10(n9 + n17) .. fn7(n16 - 3639))) .. fn23(n17 .. v3[fn2("", 5877842122082)]) .. fn23(v3[fn2("", 1146791265324)] .. v61)) .. fn23(tbl10[3] + 11145 .. v3[fn2("", 30184877583823)])) .. fn23(v3[fn2("", 24209321973778)] .. v62) .. fn23(v3[fn2("", 2249557772335)] .. n19)) .. fn23(tbl13[3] .. v3[fn2("", 17002146905562)]) .. fn23(v3[fn2("", 22752209851077)] .. n20)) .. fn23(tbl13[2] .. v3[fn2("", 7266232670831)]) .. fn23(v3[fn2("", 12423572041010)] .. n21)) .. fn23(str or v3[fn2("\158", 10995451832320)])
	local str3 = fn23(fn14(fn24(3) + 12847) .. v3[fn2("", 7759095209018)], true) .. str2
	local tbl14 = {}
	local v63 = v60(111111, 999999)
	local v64 = n6
	getfenv()[tbl14] = v63
	local v65, v66 = fn16(tbl5[v3[fn2("oL\140\148", 27792507790619)]] .. v3[fn2("-", 11376641812835)] .. v9 .. v3[fn2("x\t{\235r\133", 24176034961395)] .. tbl5[v3[fn2("al\251%6\223\236\184", 17950289871181)]] .. v3[fn2("\224\0169\166g\224c\n", 14999557289617)] .. str3 .. v3[fn2("#h\186", 22395716686201)] .. tbl5[v3[fn2("\183\133\1682\157\180\161o\254ň\143\133", 10056972838038)]] .. v3[fn2("\239\1815", 18680456594421)] .. v35, n8 == 9 or n8 == 15)
	n6 = -1
	fn12(tbl8)

	while n6 == -1 do
	end

	while tbl10[2] ~= v58 do
	end

	local n22 = 0

	for k, v67 in v32(tbl12) do
		if k == 2 and v67 ~= v31 then
			n9 = 147
		end

		if k == 8 and v67 ~= v10 then
			n9 = 147
		end

		if k == 17 and v67 ~= v26 then
			n9 = 147
		end

		n22 = k
	end

	if n22 ~= v61 % 30 + 1 then
		n9 = 147
	end

	local flag11 = false

	if n9 == 147 then
		flag11 = true
	end

	if n6 ~= v64 then
		n9 = 100
		flag11 = true
	end

	if v65 == v3[fn2("\223:\197", 18608513696690)] then
		while true do
		end
	else
		if v33(v65, v3[fn2("{\160\"\190\168\237\187\246\18R\189\15\tP\226\229H\27\197=\146\140\150\210]\193>\170\241\31{Rs\220Kb\28\251\16W|", 23368556467459)]) then
			if v8 then
				v8(v3[fn2("\178\163$M\196", 20828005780421)])
				return
			end
		end

		if v26(v65, 1, 1) == v3[fn2("\229", 26748798886223)] then
			local v67 = v3[fn2(")\23v\14\140\1973\133\12g+z|\131;", 1500063106421)]
			local v68

			if string[v3[fn2("\8_J\173", 14335964591143)]](v65, v3[fn2("\23\12\20\30\251\t\137<\0\128C\243\214H\178\153\175", 16030380898897)]) then
				v67 = v3[fn2("\164\17 \168h\190A\26;\185\127y\239o\165\246j\163w", 1651465324034)]
				v68 = v26(v65, 2, #v65 - 17)
			else
				v68 = v26(v65, 2, #v65)
			end

			fn11(100, v3[fn2("6\27\168\191\145\174<\153i|+\163\241\134", 2631821527443)], v3[fn2("\208\21(9kʥ\246\22@4\134\235ݽ\192\145\24\176|\157U\177\127\28\167", 2031581529956)], Color3[v3[fn2("ƒ\179", 34935256383255)]](1, 0, 0), v3[fn2(">ׅ\226\243", 27616408757367)])
			fn4(v67, v68)
			fn6()
		end

		if v66 then
			if not v66[v3[fn2("\2223\184\148Uk6\172\rG", 12945426493208)]] then
				local v67 = v66[v3[fn2("<-<G\17\166D\154=\200", 34741976956515)]]
			end
		end

		local n23 = tbl10[4] % 256
		local tbl15 = { [0] = tbl10[1] % 256, tbl10[2] % 256, tbl10[3] % 256, n23 }
		fn5()

		local function fn25(arg)
			local n24 = 1103515245
			local n25 = 12345
			local n26 = 99999999
			local n27 = arg % 2147483648
			local n28 = 1

			return function(arg2, arg3)
				local v67 = n26
				local n29 = n24 * n27 + n25
				local n30 = n29 % v67 + n28
				n28 += 1
				n27 = n30
				n25 = n29 % 4859 * v67 % 5781
				return arg2 + n30 % arg3 - arg2 + 1
			end
		end

		if getfenv()[tbl14] ~= v63 then
			n9 = 100
			flag11 = true
		end

		local n24 = 1

		for i = 1, 30 do
			local v67 = v31({})
			local n25

			if v31({}) < v67 then
				n25 = n24 + 1
			else
				n25 = n24 * 2
			end

			n24 = n25 % 10000
		end

		fn24(1, tbl15, 4)
		local v67 = fn22(v65)
		local n25 = v67[1] - n16
		local n26 = v67[4] - v61

		while n23 ~= tbl15[3] do
		end

		fn17()
		local v68 = tbl15[3]

		local tbl16 = {
			[0] = tbl15[0],
			[2] = tbl15[1],
			[4] = tbl15[2],
			[6] = v68,
			v67[9],
			[3] = v67[7],
			[5] = v67[2],
			[7] = v67[6],
		}

		fn24(1, tbl16, 8)
		local n27 = v67[8] - tbl13[1]
		local n28 = v67[3] - tbl13[2]
		local n29 = v67[5] - tbl13[3]
		local str4 = v3[fn2("", 27674392585389)] .. fn14(tbl13[3] + 9287) .. fn13(tbl13[1] + 31) .. fn10(tbl13[2] + 4178)

		if v67[11] == str4 and ({ [str4] = true })[v67[11]] then
			flag2 = true
		else
			local str5 = v3[fn2("", 22060699013185)] .. fn7(tbl13[3] + 9287) .. fn10(tbl13[1] + 69) .. fn13(tbl13[2] + 4178)

			if v67[11] == str5 and ({ [str5] = true })[v67[11]] then
				flag2 = true
			end
		end

		if flag2 then
			local flag12 = v18(v67[14] and v67[14] or v3[fn2("\177\149", 9173256347999)]) == -1
			v18(v67[15] and v67[15] or v3[fn2("\180", 27737745286376)])
		end

		n6 = -1
		fn12()

		if n6 == -1 then
			n9 = 250
			n6 = 100
		end

		local n30 = n7 + v59(111111, 999999) + v60(1234, 5678) + n6 % 99915 + n24
		tbl13[4] = n7 + n6 % 9951
		v59(100000, 1000000 + n6 % 1000)
		tbl13[5] = n6 % 8005 + n24 + v60(100000, 1000000 + n6 % 5000)
		tbl13[6] = v59(100000, 1000000)
		fn24(2)
		local v69 = tbl13[6]
		local v70 = tbl13[4]
		local str5 = fn23(v3[fn2("", 25929508871764)] .. fn10(v67[13] + 6421) .. fn14(n30 + n9) .. fn13(v67[10] + v61)) .. fn23(tbl13[5] .. v3[fn2("", 12067078876134)]) .. fn23(v3[fn2("", 18656833553375)] .. n30) .. fn23(v3[fn2("", 13013074292567)] .. v69) .. fn23(v70 .. v3[fn2("", 31459448025714)])
		local str6 = fn23(fn10(fn24(3) + 12847) .. v3[fn2("", 33406201362823)], true) .. str5
		local v71 = v67[12]
		local response = v14:HttpGet(tbl5[v3[fn2("\8+U\3", 4475492503624)]] .. v3[fn2("1", 13323395149944)] .. v9 .. v3[fn2("\15\18\169o1\189b\236\236\167\4U", 11342281025859)] .. v71 .. v3[fn2("\174\160x", 26048697851587)] .. str6)

		while v68 ~= tbl16[6] do
		end

		if response == v3[fn2("-\211b", 7369315031759)] then
			while true do
			end
		else
			if v26(response, 1, 1) == v3[fn2("\149", 25417318390903)] then
				v14:GetService(v3[fn2("\181\r\140\17ę\180", 23033538794443)])[v3[fn2("\2221\178\26\128\249U\30>i\229", 8753410482136)]]:Kick(response)
				fn6()
			end

			local v72 = fn22(response)
			fn25(1 + v59(100, 1000 + n24) + v60(500, 5000 + n24) + n7 % 10000)
			local flag12 = false
			local flag13 = false
			local v73 = nil

			for i = 1, 3 do
				local v74 = v72[3]
				local str7 = fn10(tbl13[5] + 3639) .. fn10(tbl13[4] + fn20(flag12 and v3[fn2("\192", 13406075793605)] or v14[v3[fn2("gl\2\139+", 16818531450159)]])) .. fn10(tbl13[6] + tbl13[2])

				if v74 == str7 and ({ [str7] = true })[v74] then
					flag3 = true

					if not (v72[8] and v72[8] ~= v3[fn2("\160", 17333943254799)] and v72[8]) then
						local v75 = v3[fn2("U\153\242C\21\244\223", 23652032960011)]
					end

					if not (v72[9] and v72[9]) then
						local v75 = v3[fn2("\162\12i\232\16\188\127", 19086343390575)]
					end

					v73 = v72[6]
					local n31 = v72[1] - tbl13[4]
					local n32 = v72[7] - tbl13[5]
					local n33 = v72[5] - tbl13[6]
					local v75 = n27
					local v76 = n28
					local v77 = n29

					n27 = function(arg)
						return v75 * arg % n31 + arg * 3
					end

					n28 = function(arg)
						return v76 * arg % 10000 + arg * n32 % 4
					end

					n29 = function(arg)
						return (arg + n33) % 100 * arg % (v77 % 100 + 1)
					end

					flag13 = true
					break
				elseif i == 3 then
					flag13 = false
					v73 = nil
				else
					flag12 = true
					flag13 = false
					v73 = nil
				end
			end

			if not flag13 then
				while true do
				end
			else
				if not flag11 then
					local v74, tbl17, tbl18, tbl19, tbl20, tbl21, fn26, fn27, stealAnEgg, fn28
					local fn29, fn30, fn31, fn32, fn33, fn34, fn35, fn36, fn37, fn38
					local fn39, fn40, fn41, fn42, fn43, fn44

					do
						do
							local fn45, fn46, fn47

							do
								do
									local tbl22, v75, fn48, fn49, fn50

									do
										do
											local fn51, v76, v77, flag14, flag15

											do
												do
													flag6 = true
													fn11(95, v3[fn2("a", 33990334741415)], v3[fn2("W\226\131\208e\30\142=\244M\236\19\174'H", 10862303782788)])
													fn11(100, v3[fn2("\247\221\3\0124\219/kh\203\209H#C\184", 27844048971083)], v3[fn2("\140\5\158\157\\\134\8\n\255Y\239\2\181-7ʿan\28", 9090575704338)] .. v29() - now .. v3[fn2("\183", 9583438242525)], Color3[v3[fn2("\247\0\245", 214754918600)]](0, 1, 0), v3[fn2("\183\194wc", 32179950777617)])
													v74 = nil

													do
														local tbl23 = {
															[5] = 104,
															[2] = 0,
															[3] = 110,
															[17] = 8,
															[12] = 211,
															[18] = 170,
															[13] = 12,
															[10] = 5,
															[6] = 35,
															[15] = 96,
															[7] = 156,
															[11] = 57,
															247,
															[14] = 252,
															[8] = 150,
															[16] = 191,
															[4] = 89,
															[9] = 28,
														}

														luraph_runtime1(v73, buffer.fromstring("\212\30\137\\\151\141\169\205\4\nm\137\rHpƿ}k2!\177~\131\236\15\17/\195\214`\1546\175ag\178\171W8\153\t\199\r~\24&\16\247\185\204\251\2014\28\8@k\137\5UH\191\131\163%\24\247J\24\6\227%\141\202A\0_\149\236\225\240\rT\128x.uu\218\209ÅFДm\168\169\2469\1695\135\136H`\139\198Se\231H\190\253\27\155B\27\206B`\166:E\7y\1372\11\253q\u{F1B2}\30\232\"\127q\27\154G\194/\243f\200v\140\140\192\138t,6\251f\241\n\1457W\159`g\7\22\157\170'\5\174j\2541\214\6\1736Ί{6\172\203\22\180X0\193Φ\207\223\215^M\24\221$\242\145N\18\211\254B\208\24\12v\161T4Y\195z8\251\251\202\245\n\247(\152jץ\227\1796\n4i=\154\190yA\1968Q\249U\220\5\169M1\213\0-\132\29,\157\t\241H\137\6\247\182s\28\141\243\237\135v\147\150\11\248\211Fm\174\173K\198]E\174\164\151\149~J(zx\246\243d黊\31WM\229\138\233\145\24\248(\224p\172\156Ȼ\184L\191i5\8\159śHݧ\146\1542\31Kd\143ц\185}\226[xݲ\0\170\19*Lʹ;x\221\6\169B\16\159\7J&d\170\168\186U\128\141\226\137#\r\188\245a[j\172\255x,s$\172\243ϭ\206,\25d\19\149\166\r\197\2\6+\186U\27\159\235\198\16|\244\191\131a\141\223Z\7\130bBk\208Tx\234\238OM\250\246\153\159\1\168#\2\0\146\217\0143\217\235N\202\226\24\214\21 B\26\5\196\198F\241Sr\252\231\227\241\164b\177c}\166\168[\1689\161\11\220,=q\2017\211\255\129]?Qq=;g5\245\189\1383j\196\4\166@\185l\135\17\199I\5\249\18\177\159\156\162\7\228\19\236R\242\253}#n\185:\185\229C\7\181\4KwFQ\129̓\202Yں\162O\16c\139\237\166\154\2\239\r\16\245M\2303\185\26LJ\4`\247]\254'\240m\190B\160\230\168\15\18k%岰]\212\214\245u\184m\30\231\202\240\190\8\183 \132\153\151\255\6\tX\0\1318\255\171\192\20F\238͵\238\162\200\19'|\238B\221w\195\225\ng\251\127U0\240\212t\164\178 \177#\229z \6uٴ\155\169\179%\241\184\228!\225\236\177ne\207;L\201,0\254\1542[F\254nS\254Z\205K\6\r\128\154\237\132V\150V\137Ύ\245\248\1589\224݆\4\224J\253\6*\176d5\196C\208\27\214כ\241\241\7,\177\n\239\192<cB<*\179U\1550\219I\188\207V\153zF\226ɳ~\215˿\130\163\2ηM[\148tp\2\12\r\137\7\31\0276\255()\229\213m\15\7:\161\131\19\223\27\221\7@5\30\148t?\228\204\232\1468\183b:\133=\192\29\140\4q\160K\t*R}¤\252\203\18\\\230\205h\15(4St\236W\182\174#\140\7q\131\204\218`,\188vQg\231\156\213\243c,\240|w\180둋[ΒM\141x\251\3\169?\1892\211\192\131\180\229? \232\177\231\151\198HIX\0312\250\130\2337V\23\24\219\18 ,x\251\rm\22\143\152P\171f\134P\194\127\167.\235\11\197\227N\171,r:{{\181\160\154қ8\n\25\193\227\248\173\227\5\235\1411Z\186\254\16kc\141\170l\158\156\239FԮ\152\188]\15R\228\28\240\21\234\n\223\195\239\163x\140\2\247\214\252\248\158\168i\164\145\172h\211\255`\8\2199\141\151- K\144\222\248\194\249\135\161\196\208_\173\141OL\158\210\30t\145뎣\245\201ñ\155\185\173\140\145\168%\141)\30\251\23W\235\140P,(\160\131l\129{\243\236w\168\1497E\8J4\132\158\168\23P\130\2336𩯶(e\1luF\213\246\204'lV\n\173=\155P*\249\7\165\n3\6<L\241f\178+}o-u3\200\218*\0237\212\217\20\25?q\207ޓ+\161\185\232\30-\137\6\3\217ݜ\145\198y؟S\3\245%}\161)ں\145PKۆ\148\186$\201\243^{\241ۀ\199\11\244\12A\190\136Sϕ*\255\216\23?\136y\6W]\0L\199\14\177\190\152\194 F{\238W?>e]\141y\203!\16\130s{|;\128O\253V&\232\180\231H\251/VP\214Hb3\146\252\235\"\213\229\28<\1523\129R\127\172\0166\252\165\196[Rѥ\130/\227\16a\2363\20\154\154\149\157\236\148h:.8\159\184.\203\249X\225\228Lh,mI7\140\138F\163S\146\16\129\11\r\161\198!!\224\154\145y2\226\235,\223Sb̆\142\154VpH\165\19\246m=˭\27\197Vb|;r\171\236\207_̪\14 \236>\143r\192+\243\132\134\12\239\248\132\197\30\26dX\250\247\158\177\6\137\175\190\1\159\228\tZ\146\148e\166\204\11)? +\232pr:;\139>\129\5\173\208\2025\171\145\180\184$+\203k\177c\181[\212|\1\215\194`v\31y\189p \230\184\23[\"\248ù\150\176\171⨧\165\17H\172\188ơhP\1854\247\203na2]\191\169[\204b\180M\183\136\191\219Id\190<X\8X\240\246\191\21\144\151\3J\193\246Rj\226ob\183\178\178\208\t\195_\162IHG]\136ܱ\182\194.\216\6\135Sj-\224dY\164g\250\186\214\228\231\28\240\159|\"g\211\203M\"\138^\205\209\27U\206r\243\139G\248\137\132\19\176\\\12UZR\148\16\\\212e\140B\29\241\200Nb}\148\220\230y\241ӓ\146\2308\239\194\29\174\14\rej\138\149\225\7\139\149\232\t\222ņVq7W\179\248\167\221\17/[\148>\138\224\194>E\"\253pt\1891\173\166,\150\165\8ѡ\229\210V\243\15h\210<Ԗ\145\174s\173\197\2085\220g\2\242=\2022\133\146C\"\4\131\1\201_\141\169\234\175\28t\222dk\238\234\184R\159^\160\188\159ɬ]*\246\226aj\253t0\245\223iJA\194(q{\182\255FAj\253\163h\1954\17:k@\190\252\237\129!\u{1085AD}\151dF\254\167\15\253u\1917%C\31`ν \139\249\250\248\229\138\r$LBNU\222\1>\234*\143ˉj!4\176\178\229\"\235\155EYfE\234\151\214;#jB\238\251\155\178\246*\142ft,\253\15\240\15.!)\227\251)\241\241\195\223}\7\127\130\249\252F\222o\192H4h\253\221\29E\157p\4p\154\2322\198\28,N-0\170\189\181\177\221Q\134\250\\\u{5CB}\149b \12\2358ey\183\169\175BԂ\245\188\163k\224\31eK\3\163\246\173\2553\23ǵ\170\31b\157\152\142\202ܒ\183\2267\140Y\26\177\199\235E\23\230\174qb\243}\227\205\254\233h\186-\164X\165p\1\26\143\231\5\25\2\22\t|\1653\245\22\232\0057\1\145i\170\200L\139\n\26o\183+\141\25q_\212<\213\7\17\150 \191\151\1522\1599\15\28\217{\143͝\231\176([8Q\172\244\8\179\138,\18_\219\227;\243\18\190:\190\11\154zW\163\199\18\235z&F\t\219\203ު{\244\199\253\1297Ϊ\221}\249%1\22\21\188MP\191\130\161z3\7\169N\165}\197=\n\226\157\16\242\234z\172\151w\243\244\25\235POs\162ɓ\244d\28\131@.\157\162Js\22O~/\227(\190\254\246\203\8;\137\178z\3\11ɔ\157\153Bp\203Z\149W\142\133xz\31b\217\0\0\136#b\214d/\".ҹ \194\11\253\185\167\130\150\t\228Q#\253\29\21~\236\14\193]X6;\140Bv\179͇u38\195Bg=Ӯ)\229/\172C\156\31a\134\r\248\170\160\155\230\193\173\238\19\249\148ڑ\181\192\156\236\190!p\221Z\182\161\140\251q\0\242\192\20Y\235\16&b\205%\209\2\15\7\135\238\156K\29\212z$X\254\131\166\200U\11\220W₋3\146\225>\230\168\2ו8\158>\160\236\178\225\158\205\1'&I1\244=\174\239\0\200\248\22\241#\23\209NXZ\252\186\157\4\161:\155\\$\243\243;\181C{+\186\254\133\206\215\239\222߱\193 A\155\191\24\153\234n\158\2226ٝ\208\31\189\181\175\134:\186hj\1469\27\0111W`T{\188\0296\27\245\174sV\171\127\30g\242\184\27\183\144\\~\25AH\169\152\253U\168Ea%\180\133\23BmT\245\138\133\r\145U\23\2216c\161%\196\232\209Ϸ\163\239\8b\162\179T\160\205}I\245[55 \163\192\229\249\24\155\127\n\189\226\180_x\18:\235K=\167\246\191\145\141\166\7Fa\217\11gW\28'r]\16\167.\177\214\253V\146\250\18+\206\7\149\166_\127 \183\12\137\153P\240\232^e2\155\185\177\248\138`fx\166\234j\187\231\182*\187f<\157\144W%\194o\150.\235L\174\156p\129\166QV\3\213\21Oe/\237\t\236\144]\207\243i\131\248\165\216\213\222+\243}\31\159\n+s\177=\2340\127϶\150}\165\16\156Q8\194Qr\215\230\218k\0<\152\164\135Ņ~\245VQ\133\254\137\136\255\139q\1409;\142\143\201\0292\139/+:y\139ޓ\138p\204Cۍ\231\244\245\143ۍ\173\130@(\179\170\137l&\218n_\245\244i:X \205}\24\134Y\18\240\248\255.\227\234U\251\221W\163\255\136/{\254rom\1838B\16%\128\17r\152\188\2084\131\228\206\219s,~\1753\29\232\6\225έ\0\143\201\237\139\4\246\131t?\133\168\173\19ͅW\255R\222\224\132\250\241i\201\12\161O\174\16\15\169PS\27;5\7\197\26\\\128b\154\12\237b\192\1423\154N\244\225\196ɽqͷ\142\235\253\221\28\228\186L\1=\136\172\228\199\215j\206\12\169\7}\206\20\197caPw\180QGJ2\26\147~۪\215V\194\254\245\141\152\135\157D\11C\238\233\31t\233Jr\169asߡ\244$\166\t\178-\2323\241D\225\r\203L\142\210C/~d\25\137\"Ե\255\194U^\193\224\162O\r\163\153\192\128\183\204z\145\233\232\21\253f\29\227w\139T\205\217\243͕W\222\240\11\240\224C4\245\160\200'\169ʃb`\167\11\243\182\196\237\152\227\213\194ov\166\235\3\223K\21\196\237\140,:\30Nƅ\21\17\236\203\217\250`3\142أ\191WتD\214ո\180\2397Tmd\148>u\163\139\168\142\t|\219\241\25\252|^\156\17`\212\241\206\195H\225\206\0202\130\218b1-7ֈ\127!\0G\218K$\172\154\170\174\0\164\157\210Gc\176\223\236\16\254\130\251\4%)X\130\242\156\23\129\239\189l&\16\14\154\188\204NM\127\206k\173ڃ\254\235.\5\244`!\150\255\188R)\241\163\234\132\236:^\195Z\170ŪVk\155\183a^\248\231K\19\\\141\29\195RFE\139\184LǪj\228e\193\174S\172\2333\243\155\192\160\142\"oG\192p\148\236N\229\133r\141\205\6\242\\\157k\"6\2369\251\n\1739\186&\178\241\25\8\217\5\182fM}_\24h\30\219\217\239\170ۍdV\170r\213\244\235H\227h\176\139\241\214J\233\8\215'\143\198t\0061\167\nR\158\139uH\153\152\1608ZN6\130la\"\187\178\142\146\29\255kk'\254~\158\22\191\134?y\"\30\134d\128ַb'\249:\21%\211DI\143a\191T \252\\\24\141\160\157\215\231Q\19\186\168P\134\248\229:m\129'\1476\235k\165>\23\217.<\0\224\180\194\0\20%\142\238j,qr\201`\23\172\181\228\129\8\t\1s\198\198k]I\145\228)\213\1943\206[?\189\240t\226\191\205\200\242iD7\162<\159`\130\192\152\170\nbR\200rG\208\198і\152\151]3\251\189ͺ-g\6\1428\198|\4z\180\24\t\167O\159\164\248c3t\21\1689\202d\1\27\28\255&\168\187\157\254ʷ\228\242\0298$\1595\254\16\20cfT!\23d\28\186\1759\239\144\t\1921\140\17}\200,o:\200\192\217\30H\237\158\227\3\182(\26\186\"\167\227\6\164\242)\154 \231q\190ږ<\181\203p\8\189\t\162L&\231ҋ\255\\\253a4\168\1752\234\181\204\16GM\6F\166\176\0\145Zڎ\137ܛ\222\29ݻH\179\249\205@'pnc\155\242x\128\16\230\151>"), tbl23, 209)()
													end
												end

												do
													repeat
														task.wait()
													until game:IsLoaded()

													tbl17 = {}
													tbl18 = {}
													tbl19 = {}
													tbl20 = {}
													tbl21 = {}
													task.wait(2)
													tbl17.RS = game:GetService("ReplicatedStorage")
													tbl17.Net = tbl17.RS:WaitForChild("Packages"):WaitForChild("Networking")

													do
														local localPlayer = game:GetService("Players").LocalPlayer

														tbl22 = {
															killed = false,
															bacInstalled = v74[155],
															perFrameHooked = v74[155],
															hooks = {},
															envHookfunction = nil,
															envNewcclosure = nil,
														}

														fn51 = function()
															if tbl22.killed then
																return
															end
															tbl22.killed = true
															_G.__StealAnEggSecurityKill = true

															task.defer(function()
																local v78 = v74[75]

																if n27(2937) <= v78 then
																	pcall(function()
																		localPlayer:Kick()
																	end)

																	if not flag3 then
																		return
																	end
																	return
																end

																while true do
																end
															end)

															while v74[29] do
																task.wait(1e9)
															end
														end
													end
												end

												v76 = hookfunction
												v75 = newcclosure
												v77 = getgenv
												flag14 = typeof(isfunctionhooked) == "function" and isfunctionhooked or nil

												do
													local v78 = v74[22]
													flag15 = typeof(gethookfunction) == v78 and gethookfunction or nil
												end
											end

											do
												local flag16 = typeof(restorefunction) == "function" and restorefunction or nil

												local function fn52(arg)
													for _, hook in pairs(tbl22.hooks) do
														if arg == hook.target or arg == hook.replacement or arg == hook.previous then
															return v74[29]
														end
													end

													return false
												end

												tbl22.secureHook = function(arg, arg2)
													if tbl22.killed then
														return arg
													end
													local v78 = v74[22]

													if type(arg) ~= v78 then
														fn51()
													end

													local v79 = v76(arg, arg2)
													tbl22.hooks[arg] = { target = arg, replacement = arg2, previous = v79 }
													return v79
												end

												fn48 = function()
													if tbl22.killed then
														return
													end
													local v78 = v77()

													if v78.hookfunction ~= tbl22.envHookfunction then
														fn51()
													end

													if v75 and v78.newcclosure and v78.newcclosure ~= tbl22.envNewcclosure then
														fn51()
													end

													if rawget(_G, "hookfunction") and _G.hookfunction ~= tbl22.envHookfunction then
														fn51()
													end

													for k, hook in pairs(tbl22.hooks) do
														if flag14 and flag15 and flag14(k) then
															local v79 = flag15(k)

															if v79 and v79 ~= hook.replacement then
																fn51()
															end
														end

														if flag16 and flag14 and flag14(hook.replacement) then
															fn51()
														end
													end
												end

												tbl22.envHookfunction = v75(function(arg, arg2)
													if tbl22.killed then
														return arg
													end

													if fn52(arg) or fn52(arg2) then
														if n29(3043) <= 865 then
															fn51()
														else
															while v74[29] do
															end
														end
													end

													return tbl22.secureHook(arg, arg2)
												end)
											end

											do
												if v75 then
													tbl22.envNewcclosure = v75(function(arg)
														if not flag3 then
															return
														end
														return v75(arg)
													end)
												end

												do
													local v78 = v77()
													v78.hookfunction = tbl22.envHookfunction

													if v75 then
														v78.newcclosure = tbl22.envNewcclosure
													end
												end
											end
										end

										if shared then
											shared.hookfunction = tbl22.envHookfunction

											if v75 then
												shared.newcclosure = tbl22.envNewcclosure
											end
										end

										if getrenv then
											pcall(function()
												local v76 = getrenv()
												v76.hookfunction = tbl22.envHookfunction

												if v75 then
													v76.newcclosure = tbl22.envNewcclosure
												end
											end)
										end

										task.spawn(function()
											while not tbl22.killed do
												fn48()
												task.wait(1.5)
											end
										end)

										do
											local function fn51(arg, arg2)
												if not arg or not arg2 or not arg2.Parent then
													return
												end
												local v76 = v74[63]
												local cFrame = rawget(getgenv(), v76)
												cFrame = cFrame and cFrame.ForceStealPosition

												if typeof(cFrame) == "Vector3" then
													cFrame = CFrame.new(cFrame)
												elseif typeof(cFrame) ~= "CFrame" then
													cFrame = arg2.CFrame
												end

												arg.Position = cFrame.Position
												arg.CFrame = cFrame
												arg.LinearVelocity = Vector3.zero
												arg.AngularVelocity = Vector3.zero
												arg.IsSupported = true
												arg.Timestamp = workspace:GetServerTimeNow()
											end

											fn49 = function(arg)
												if not arg then
													if not flag2 then
														return
													end

													if n28(2231) <= 3991 then
														return
													end

													while v74[29] do
													end
												end

												local rootPart = arg.RootPart

												if not (not rootPart or not rootPart.Parent) then
													if arg.Evidence then
														arg.Evidence.Speed = 0
														arg.Evidence.Flight = 0
														arg.Evidence.Teleport = 0
													end

													arg.TamperScore = 0
													arg.ThreatLevel = "Trusted"
													arg.KickQueued = false
													arg.InvalidHeartbeatCount = 0
													arg.CoreGuiScore = v74[78]
													return
												end

												if not (n25 >= 1786) then
													return
												end

												while true do
												end
											end

											fn50 = function(arg)
												if not arg then
													return
												end
												local rootPart = arg.RootPart
												if not rootPart or not rootPart.Parent then
													return
												end
												fn51(arg.LastSample, rootPart)
												fn51(arg.LastGoodSample, rootPart)
												fn51(arg.LastValidatedSample, rootPart)
												fn51(arg.LastValidatedGroundedSample, rootPart)
												fn51(arg.LastGameplayTrustedSample, rootPart)
												fn51(arg.LastConfirmedGroundSample, rootPart)
												fn51(arg.LastObservedSample, rootPart)
												fn51(arg.CandidateGroundedSample, rootPart)

												if arg.SampleHistory then
													for _, v76 in pairs(arg.SampleHistory) do
														fn51(v76, rootPart)
													end
												end

												if arg.SafeGroundCheckpoints then
													for _, safeGroundCheckpoint in pairs(arg.SafeGroundCheckpoints) do
														fn51(safeGroundCheckpoint, rootPart)
													end
												end

												if arg.HorizontalDebug then
													for _, v76 in pairs(arg.HorizontalDebug) do
														if type(v76) == "table" then
															v76.HorizontalExcess = 0
															v76.NetHorizontalDisplacement = v74[78]
															v76.AdjustedPathDistance = 0
															v76.NetMovementRatio = 0
															v76.PathMovementRatio = v74[78]
														end
													end
												end

												if arg.LastVerticalSegmentDecision then
													arg.LastVerticalSegmentDecision.Excess = v74[78]
													arg.LastVerticalSegmentDecision.Displacement = 0
													arg.LastVerticalSegmentDecision.Ratio = 0
													arg.LastVerticalSegmentDecision.CorrectionStarted = v74[155]
													arg.LastVerticalSegmentDecision.Decision = v74[24]
												end

												if arg.LastVerticalTrajectoryDecision then
													arg.LastVerticalTrajectoryDecision.Active = v74[155]
													arg.LastVerticalTrajectoryDecision.Evidence = 0
													arg.LastVerticalTrajectoryDecision.CorrectionStarted = false
													arg.LastVerticalTrajectoryDecision.ConsecutiveInvalidWindows = 0
												end

												if not (n26 <= v74[127]) then
													arg.IsSupportedNow = true
													arg.MovementMode = "Grounded"
													arg.HighestYSinceGround = rootPart.CFrame.Position.Y
													return
												end

												while true do
												end
											end
										end
									end

									do
										local fn51

										do
											local fn52, fn53

											do
												fn52 = function(arg)
													tbl22.perFrameOld = tbl22.secureHook(arg, function(...)
														local v76 = table.pack(...)
														local v77 = ({ ... })[1]
														local value = rawget(getgenv(), "StealAnEgg")
														value = value and value.ForceStealPosition

														if v77 and typeof(value) == "Vector3" then
															local rootPart = v77.RootPart

															if rootPart and rootPart.Parent then
																rootPart.CFrame = CFrame.new(value)
																rootPart.AssemblyLinearVelocity = Vector3.zero
																rootPart.AssemblyAngularVelocity = Vector3.zero
															end
														end

														fn50(v77)
														local tbl23 = { tbl22.perFrameOld(table.unpack(v76, 1, v76.n)) }
														fn49(v77)

														if v77 and typeof(value) == "Vector3" then
															local rootPart = v77.RootPart

															if rootPart and rootPart.Parent then
																rootPart.CFrame = CFrame.new(value)
															end

															if v77.Evidence then
																v77.Evidence.Teleport = 0
																v77.Evidence.Speed = 0
																v77.Evidence.Flight = 0
															end
														end

														return unpack(tbl23)
													end)
												end

												do
													local function fn54(arg, arg2)
														local tbl23 = {}

														for i = 1, #arg do
															local v76 = string.byte(arg, i)
															local char2 = string.char
															local bxor = bit32.bxor
															local v77 = string.byte(arg2, (i - 1) % #arg2 + v74[137])
															tbl23[i] = char2(bxor(v76, v77))
														end

														return table.concat(tbl23)
													end

													fn53 = function()
														local jobId = game.JobId

														tbl22.bypassFireServerOld = tbl22.secureHook(Instance.new("RemoteEvent").FireServer, v75(function(arg)
															local v76 = fn54("X-" .. tostring(os.time()), jobId)
															local v77 = nil

															if math.random(1, 2) == 2 then
																local n31 = math.random(1, v74[144])
																v77 = fn54(tostring(n31), jobId)
															end

															return tbl22.bypassFireServerOld(arg, v76, v77)
														end))

														tbl22.bacInstalled = v74[29]
													end
												end
											end

											do
												local tbl23 = {
													"Trusted",
													v74[113],
													v74[81],
													"Anti-cheat rejected a non-finite character movement sample",
													"Anti-cheat correction lifecycle trace",
													"POST_CORRECTION_HANDOFF_SAMPLE",
												}

												local function fn54(arg, arg2)
													local ok, result = pcall(getconstants, arg)
													if not ok or typeof(result) ~= "table" then
														return false
													end
													local tbl24 = {}

													for _, v76 in pairs(result) do
														if typeof(v76) == "string" then
															tbl24[v76] = true
														end
													end

													for _, v76 in ipairs(arg2) do
														if not tbl24[v76] then
															return false
														end
													end

													return true
												end

												fn51 = function()
													if tbl22.perFrameHooked then
														return true
													end
													local flag14 = typeof(getgc) ~= "function"

													if not flag14 then
														local v76 = v74[22]
														flag14 = typeof(islclosure) ~= v76
													end

													if flag14 then
														return v74[155]
													end

													for _, v76 in pairs(getgc(true)) do
														if typeof(v76) == "function" and islclosure(v76) then
															if fn54(v76, tbl23) then
																local ok, result = pcall(getinfo, v76)

																if ok and result and result.source == "=ReplicatedFirst.UGI.ContentCatalog.Playback" then
																	fn52(v76)
																	tbl22.perFrameHooked = true
																	return true
																end
															end
														end
													end

													return v74[155]
												end
											end

											fn53()
										end

										fn51()

										tbl22.bypassOld1 = hookmetamethod(game, "__namecall", v75(function(arg, ...)
											local v76 = table.pack(...)
											local v77 = getnamecallmethod()

											if not checkcaller() and (v77 == "FireServer" or v77 == "InvokeServer") then
												local name = arg.Name

												if name == "RE/Telemetry/SubmitIdleState" and v77 == "FireServer" then
													if select(1, ...) == true then
														return
													end
													return tbl22.bypassOld1(arg, table.unpack(v76, 1, v76.n))
												end

												if v77 == "InvokeServer" and (name == "RF/Telemetry/AskIdleHopFlush" or name == "RF/Telemetry/SubmitIdleHop") then
													return
												end
											end

											return tbl22.bypassOld1(arg, ...)
										end))

										fn48()
										local n31 = os.clock() + 30

										while not (tbl22.bacInstalled and tbl22.perFrameHooked) do
											fn51()
											task.wait(0.5)
										end
									end

									do
										print("done")

										fn26 = function()
											if tbl22.killed or _G.__StealAnEggSecurityKill then
												while v74[29] do
													task.wait(1e9)
												end
											end

											fn48()
										end

										do
											local function fn51(...)
												local v76 = table.pack(...)
												local rs = tbl17.RS

												for i = 1, select("#", ...) do
													rs = rs:WaitForChild(select(i, table.unpack(v76, 1, v76.n)))
												end

												return require(rs)
											end

											fn45 = function(arg)
												return tbl17.Net:WaitForChild(arg)
											end

											fn27 = function(arg)
												if type(arg) ~= "table" then
													return {}
												end

												if type(arg.Directory) == "table" then
													return arg.Directory
												end
												return arg
											end

											local function fn52(arg)
												if arg.Name == "GUI" then
													return true
												end
												local fullName = arg:GetFullName()
												if fullName:find("Client%.GUI", 1, true) or fullName:find("Client%.UI", 1, true) then
													return true
												end
												return false
											end

											local function fn53(arg, arg2)
												if type(arg) ~= "table" then
													return false
												end
												local value = rawget(arg, arg2)
												if value ~= nil then
													local v76 = v74[22]
													return typeof(value) == v76
												end

												local ok, result = pcall(function()
													if n27(4558) <= 22578 then
														return arg[arg2]
													end

													while true do
													end
												end)

												return ok and typeof(result) == "function"
											end

											fn46 = function(arg, arg2)
												if type(arg) ~= "table" then
													return nil
												end
												local value = rawget(arg, arg2)
												if typeof(value) == "function" then
													return value
												end

												local ok, result = pcall(function()
													if n27(3585) >= 14502 then
														return arg[arg2]
													end

													while true do
													end
												end)

												if ok and typeof(result) == "function" then
													return result
												end
												return nil
											end

											fn47 = function(arg, arg2)
												for _, v76 in ipairs(arg2) do
													if v76 then
														for _, descendant in ipairs(v76:GetDescendants()) do
															if descendant:IsA("ModuleScript") and not fn52(descendant) then
																local ok, result = pcall(require, descendant)
																if ok and fn53(result, arg) then
																	return result, descendant
																end
															end
														end
													end
												end

												return nil
											end

											tbl18.Constants = fn51("Shared", "Globals", "Constants")
											tbl18.Save = fn51(v74[132], "Save")
											tbl18.TrailsDir = fn51("Data", "Trails")
											tbl18.TreadmillsDir = fn51("Data", "Treadmills")
											tbl18.AssetsDir = fn51(v74[74], "Assets")
											tbl18.AreasDir = fn51("Data", "Areas")
											tbl18.EggState = fn51("Client", "EggState")
											tbl18.BaseUpgrade = fn51("Client", "BaseUpgrade")
											tbl18.PlacedEggRenderer = fn51("Shared", v74[97], "PlacedEggRenderer")
											tbl18.EggToolDisplay = fn51("Shared", "Eggs", "EggToolDisplay")
											tbl18.AreaEggSlotIdentity = fn51(v74[132], "Util", v74[153])
											tbl18.AreaEggCycle = fn51("Shared", "Util", "AreaEggCycle")
											tbl18.TreadmillUtil = fn51("Shared", "Util", "TreadmillUtil")
											tbl18.SettingsCmds = fn51("Shared", v74[104])
											tbl18.EggGrowth = fn51(v74[132], v74[97], "PlacedEggGrowthPresentationPolicy")
											tbl18.SpeedGainPopup = fn51("Client", "UI", v74[151], "SpeedGainPopup")
											tbl18.TreadmillVideoController = fn51("Shared", "TreadmillVideoController")
										end
									end
								end

								tbl18.EggAreaNameByCategory = {}

								do
									local v75 = pairs
									local v76 = fn27(tbl18.AreasDir)

									for k, v77 in v75(v76) do
										if type(v77) == "table" then
											local v78 = ipairs
											local dropTable = v77.DropTable or {}

											for _, v79 in v78(dropTable) do
												local flag14 = type(v79) == "table" and v79[1] or nil
												local v80 = v74[34]

												if typeof(flag14) == v80 then
													local str7 = tostring(k)

													if str7:sub(-v74[32]):lower() ~= " egg" then
														str7 ..= " Egg"
													end

													tbl18.EggAreaNameByCategory[flag14] = str7
												end
											end
										end
									end
								end
							end

							do
								do
									local value, value2, deserializeSavedEgg, v75

									do
										local value3

										do
											tbl18.EggItemUtil = {}

											do
												local tbl22 = { tbl17.RS.Shared, tbl17.RS.Data }
												local value4 = select(1, fn47("DeserializeSavedEgg", tbl22))
												value3 = select(v74[137], fn47("GetDisplayName", tbl22))
												value2 = select(1, fn47("GetWeightKg", tbl22))
												value = select(1, fn47("GetWeightKgForScale", tbl22))
												deserializeSavedEgg = value4 and fn46(value4, "DeserializeSavedEgg")
											end
										end

										v75 = value3 and fn46(value3, v74[92])
									end

									local getWeightKg = value2 and fn46(value2, "GetWeightKg")
									local getWeightKgForScale = value and fn46(value, "GetWeightKgForScale")

									if deserializeSavedEgg then
										tbl18.EggItemUtil.DeserializeSavedEgg = deserializeSavedEgg
									end

									if v75 then
										tbl18.EggItemUtil.GetDisplayName = v75
									end

									if getWeightKg then
										tbl18.EggItemUtil.GetWeightKg = getWeightKg
									end

									if getWeightKgForScale then
										tbl18.EggItemUtil.GetWeightKgForScale = getWeightKgForScale
									end
								end

								do
									local fn48

									do
										do
											if tbl18.EggGrowth then
												tbl18.EggItemUtil.GetGrowthAlpha = tbl18.EggGrowth.GetGrowthAlpha
												tbl18.EggItemUtil.IsReady = tbl18.EggGrowth.IsReady
											end

											if tbl18.AreaEggCycle and tbl18.AreaEggCycle.NightGrowthCreditAt then
												tbl18.EggItemUtil.GetCurrentNightGrowthCreditSeconds = function(arg, arg2, arg3)
													local ok, result = pcall(tbl18.AreaEggCycle.NightGrowthCreditAt, arg2)

													if ok then
														local v75 = v74[6]
														ok = typeof(result) == v75
													end

													if ok then
														if n25 <= 1757 then
															while v74[29] do
															end
														end

														return result
													end

													local ok2, result2 = pcall(tbl18.AreaEggCycle.NightGrowthCreditAt, arg, arg2, arg3)

													if ok2 then
														local v75 = v74[6]
														ok2 = typeof(result2) == v75
													end

													if ok2 then
														return result2
													end
													return 0
												end

												if not flag3 then
													return
												end
											end

											tbl18.PlotCmds = {}
											tbl17.TweenService = game:GetService("TweenService")
											tbl17.RunService = game:GetService(v74[128])
											tbl17.HttpService = game:GetService("HttpService")
											tbl19.AskBaseTierRaise = fn45("RE/Homestead/AskBaseTierRaise")
											tbl19.AskHomesteadState = fn45("RF/Homestead/AskState")
											tbl19.AskTreadmillTierRaise = fn45("RF/Treadmill/AskTierRaise")
											tbl19.SellPet = fn45("RE/PetSatchel/SellPet")
											tbl19.AskPlaceEgg = fn45("RF/EggWorld/AskPlaceEgg")
											tbl19.AskRedeemAll = fn45("RF/Codex/AskRedeemAll")
											tbl19.AskFieldEggCarry = fn45("RF/EggWorld/AskFieldEggCarry")
											tbl19.AskFieldEggSnapshot = fn45("RF/EggWorld/AskFieldEggSnapshot")
											tbl19.AskCollectAway = fn45("RF/AwayEarnings/AskCollect")
											tbl19.AwayPendingCheck = fn45("RF/AwayEarnings/PendingCheck")
											tbl19.AwayFetchSummary = fn45("RF/AwayEarnings/FetchSummary")
											tbl19.AskTrailPurchase = fn45("RF/Trailwear/AskPurchase")
											tbl19.AskTrailChoose = fn45("RF/Trailwear/AskChoose")
											tbl19.AskWearStill = fn45("RF/Treadmill/AskWearStill")
											tbl19.AskDoffTreadmill = fn45("RF/Treadmill/AskDoff")
											tbl19.AssignedBeltShifted = fn45("RE/Treadmill/AssignedBeltShifted")
											tbl19.SubmitIdleState = fn45("RE/Telemetry/SubmitIdleState")
											tbl19.ProbeSatchel = fn45("RE/RigSync/ProbeSatchel")
											tbl19.RequestBaseUpgrade = tbl19.AskBaseTierRaise
											tbl19.RequestTreadmillUpgrade = tbl19.AskTreadmillTierRaise
											tbl19.SellAssetEvent = tbl19.SellPet
											tbl19.RequestPlaceEgg = tbl19.AskPlaceEgg
											tbl19.RequestClaimAllIndex = tbl19.AskRedeemAll
											tbl19.RequestAreaEggCarry = tbl19.AskFieldEggCarry
											tbl19.OfflineAssetsRedeem = tbl19.AskCollectAway
											tbl17.Players = game:GetService("Players")
											tbl17.Workspace = game:GetService("Workspace")
											tbl17.Lighting = game:GetService("Lighting")
											tbl17.CoreGui = game:GetService(v74[51])
											tbl17.StarterGui = game:GetService(v74[76])
											tbl17.GuiService = game:GetService("GuiService")
											tbl17.LocalPlayer = tbl17.Players.LocalPlayer

											tbl18.PlotCmds.GetPlotData = function()
												local ok, result = pcall(function()
													return tbl19.AskHomesteadState:InvokeServer()
												end)

												if not ok or type(result) ~= "table" then
													warn("[PlotData] AskState failed", result)
													return nil
												end
												local v75 = pairs
												local ownersBySlot = result.OwnersBySlot or {}
												local v76 = nil

												for k, v77 in v75(ownersBySlot) do
													if v77 == tbl17.LocalPlayer.UserId then
														v76 = k
														break
													else
														v76 = nil
													end
												end

												if v76 == nil then
													warn("[PlotData] local player has no assigned slot")
													return nil
												end
												local v77 = tbl17.Workspace:FindFirstChild(v74[143])
												v77 = v77 and v77:FindFirstChild(tostring(v76))
												local v78 = v77 and (v77:FindFirstChild(v74[30]) or v77)
												local centerPoint = v78 and v78:FindFirstChild("CenterPoint")
												v78 = v78 and v78:FindFirstChild(v74[31])
												if not v77 or not centerPoint or not v78 then
													warn("[PlotData] missing plot parts for slot", v76)
													return nil
												end
												return { Model = v77, Slot = v76, CenterPoint = centerPoint, PetArea = v78 }
											end

											tbl18.EggCmds = {
												RequestAreaEggSnapshot = function()
													pcall(function()
														if tbl18.EggState.SyncFieldEggs then
															tbl18.EggState.SyncFieldEggs()
															if not flag2 then
																return
															end
														end
													end)

													if typeof(tbl18.EggState.ReadFieldEggs) == "function" then
														local ok, result = pcall(tbl18.EggState.ReadFieldEggs)

														if ok and type(result) == "table" then
															if result.Records then
																return result
															end
															local tbl22 = {}

															if #result > 0 then
																tbl22 = result
															else
																for _, v75 in pairs(result) do
																	if type(v75) == "table" and (v75.Uid or v75.AssetCategory) then
																		table.insert(tbl22, v75)
																	end
																end
															end

															return { Records = tbl22 }
														end
													end

													local ok, result = pcall(function()
														return tbl19.AskFieldEggSnapshot:InvokeServer()
													end)

													if ok and type(result) == "table" then
														if result.Records then
															return result
														end

														if not flag3 then
															return
														end
														return { Records = result }
													end

													return { Records = {} }
												end,
												RequestCarryAreaEgg = function(arg, arg2)
													if typeof(tbl18.EggState.CarryFieldEgg) == "function" then
														return tbl18.EggState.CarryFieldEgg(arg, arg2)
													end
													return tbl19.AskFieldEggCarry:InvokeServer({ Uid = arg, FirstAreaSlotKey = arg2 })
												end,
												RequestWearEggTool = function(arg)
													if typeof(tbl18.EggState.WearEggTool) == "function" then
														return tbl18.EggState.WearEggTool(arg)
													end
													return false, v74[73]
												end,
												RequestPlaceEgg = function(arg, arg2)
													local v75 = v74[22]
													if typeof(tbl18.EggState.PlantEgg) == v75 then
														return tbl18.EggState.PlantEgg(arg, arg2)
													end
													return tbl19.AskPlaceEgg:InvokeServer({ Uid = arg, LocalCFrame = arg2 })
												end,
												RequestCompleteHatchEgg = function(arg)
													if typeof(tbl18.EggState.FinishHatch) == "function" then
														return tbl18.EggState.FinishHatch(arg)
													end
													return false, "FinishHatch missing"
												end,
												GetOwnerRuntimeRecords = function(arg)
													if v74[27] < n27(3472) then
														if typeof(tbl18.EggState.ReadOwnerEggs) == "function" then
															local ok, result = pcall(tbl18.EggState.ReadOwnerEggs, arg)
															if ok then
																return result
															end
														end

														if typeof(tbl18.EggState.ReadOwnedEggs) == "function" then
															local ok, result = pcall(tbl18.EggState.ReadOwnedEggs)
															if ok then
																return result
															end
														end

														return nil
													end

													while true do
													end
												end,
											}

											if not tbl18.Save.IsLocalDataLoaded() then
												tbl18.Save.LoadedStats:Wait()
											end

											getgenv().StealAnEgg = getgenv().StealAnEgg or {}
											stealAnEgg = getgenv().StealAnEgg
											stealAnEgg.MaxPlotLevel = stealAnEgg.MaxPlotLevel or v74[152]
											stealAnEgg.MaxTreadmillLevel = stealAnEgg.MaxTreadmillLevel or v74[95]
											stealAnEgg.SellPets = stealAnEgg.SellPets or {}
											stealAnEgg.PlaceEggs = stealAnEgg.PlaceEggs or {}
											stealAnEgg.StealEggs = stealAnEgg.StealEggs or {}
											stealAnEgg.PlaceEggSpacing = stealAnEgg.PlaceEggSpacing or 4
											stealAnEgg.PlaceEggMaxTriesPerEgg = stealAnEgg.PlaceEggMaxTriesPerEgg or 12
											stealAnEgg.DiscordId = stealAnEgg.DiscordId or ""

											do
												local showPingInGlobalWebhook

												if stealAnEgg.ShowPingInGlobalWebhook == nil then
													showPingInGlobalWebhook = false
												else
													showPingInGlobalWebhook = stealAnEgg.ShowPingInGlobalWebhook
												end

												stealAnEgg.ShowPingInGlobalWebhook = showPingInGlobalWebhook
											end
										end

										stealAnEgg.PrivateHatchWebhookUrl = stealAnEgg.PrivateHatchWebhookUrl or ""
										stealAnEgg.PrivateHatchWebhookRarities = stealAnEgg.PrivateHatchWebhookRarities or {}
										tbl20.HatchWebhookUsername = "Steal An Egg"
										tbl20.DisablePetRender = v74[29]
										tbl20.ApplyOptimizationSettings = true
										tbl20.Optimization1 = v74[29]
										tbl20.StealFlySpeed = 350
										tbl20.StealHeightOffset = 60
										tbl20.StealLandOffset = 5
										tbl20.StealReturnPosition = Vector3.new(538.90673828125, v74[57], -364.62646484375)
										tbl20.StealMinSecondsUntilCycle = v74[111]
										tbl20.StealAfterCycleMaxWait = v74[19]
										tbl20.StealReplicateWait = v74[2]
										tbl20.StealClimbHoriz = v74[40]
										tbl20.Debug = { Steal = false, Treadmill = false }
										tbl20.AutoTreadmill = true
										tbl20.TreadmillLockCamera = true
										tbl20.MainLoopWait = 2
										tbl20.AutoClaimOffline = true
										tbl20.GlobalHatchWebhookUrl = ""
										tbl20.NumberSuffixes = { "K", v74[126], "B", "T", "Q" }

										tbl21.ui = {
											StartingTime = os.time(),
											CurrentTask = "Starting...",
											Mode = "Steal An Egg",
										}

										fn28 = function(arg, text)
											if arg and arg.Text ~= text then
												arg.Text = text
											end
										end

										fn29 = function(currentTask)
											tbl21.ui.CurrentTask = currentTask or ""

											if tbl21.ui.UI then
												fn28(tbl21.ui.UI.LastTask, "Task: " .. tbl21.ui.CurrentTask)
											end
										end

										fn30 = function(mode)
											tbl21.ui.Mode = mode or "Steal An Egg"

											if tbl21.ui.UI then
												fn28(tbl21.ui.UI.CurrentZone, tbl21.ui.Mode)
											end
										end

										fn31 = function(arg)
											if type(arg) ~= "number" or arg <= 0 then
												return "0"
											end
											local v75 = math.round(arg)
											local n31 = math.floor(math.log(v75, v74[66]))
											local n32 = v74[95] ^ (n31 * 3)
											if not n32 or n32 == 0 then
												return tostring(v75)
											end
											return ("%.2f"):format(v75 / n32):gsub("%.?0+$", "") .. (tbl20.NumberSuffixes[n31] or "")
										end

										fn32 = function(arg)
											local n31 = math.max(math.floor(tonumber(arg) or v74[78]), v74[78])
											local n32 = math.floor(n31 / 86400)
											local n33 = n31 % 86400
											local n34 = math.floor(n33 / 3600)
											local n35 = n33 % 3600
											local n36 = math.floor(n35 / 60)
											local n37 = n35 % 60
											local str7 = ""

											if v74[78] < n32 then
												str7 = "" .. n32 .. "d "
											end

											if n34 > v74[78] then
												str7 ..= n34 .. v74[46]
											end

											if n36 > 0 then
												str7 ..= n36 .. "m "
											end

											return str7 .. n37 .. v74[158]
										end

										fn33 = function()
											local function fn49(arg, name, parent, arg2)
												local instance = Instance.new(arg)
												instance.Name = name
												local v75 = pairs
												arg2 = arg2 or {}

												for k, v76 in v75(arg2) do
													instance[k] = v76
												end

												instance.Parent = parent
												return instance
											end

											local ScreenGui = fn49("ScreenGui", "Hikko", tbl17.LocalPlayer.PlayerGui, {
												ZIndexBehavior = Enum.ZIndexBehavior.Sibling,
												DisplayOrder = 999,
												IgnoreGuiInset = v74[29],
												Enabled = true,
												ResetOnSpawn = false,
											})

											local Frame = fn49("Frame", v74[59], ScreenGui, {
												AnchorPoint = Vector2.new(v74[84], 0.5),
												BackgroundColor3 = Color3.fromRGB(10, 10, 11),
												BorderColor3 = Color3.new(0.992157, 0.27451, 0.27451),
												BorderSizePixel = 3,
												Position = UDim2.new(v74[84], 0, 0.5, 0),
												Size = UDim2.new(1, v74[78], 1, 0),
											})

											local Frame2 = fn49("Frame", "Logo", Frame, {
												AnchorPoint = Vector2.new(0.5, 0.5),
												BackgroundTransparency = 1,
												BorderSizePixel = v74[78],
												Position = UDim2.new(0.499991536, 0, 0.0707971379, 0),
												Size = UDim2.new(0.17320314, 0, 0.0850019157, 0),
											})

											fn49(v74[124], "Title", Frame2, {
												AnchorPoint = Vector2.new(v74[84], 0.5),
												BackgroundTransparency = v74[137],
												BorderSizePixel = 0,
												Position = UDim2.new(v74[84], 0, v74[123], 0),
												Size = UDim2.new(2, 0, 2.2, v74[78]),
												ZIndex = 2,
												Font = Enum.Font.FredokaOne,
												Text = v74[37],
												TextColor3 = Color3.new(0.878431, 0.011765, 0.011765),
												TextScaled = true,
												TextSize = v74[106],
												TextWrapped = true,
											})

											fn49("UIAspectRatioConstraint", "UIAspectRatioConstraint", Frame2, { AspectRatio = v74[114] })

											local TextLabel = fn49("TextLabel", "SessionTime", Frame, {
												AnchorPoint = Vector2.new(0.5, 0.5),
												BackgroundTransparency = 1,
												BorderSizePixel = 0,
												Position = UDim2.new(v74[84], 0, 0.270000011, 0),
												Size = UDim2.new(0.781448126, v74[78], 0.116130508, 0),
												ZIndex = 2,
												Font = Enum.Font.Cartoon,
												Text = "Session Time: Loading",
												TextColor3 = Color3.fromRGB(222, v74[60], 222),
												TextScaled = true,
												TextSize = 100,
												TextWrapped = true,
											})

											local TextLabel2 = fn49("TextLabel", "Current Zone", Frame, {
												AnchorPoint = Vector2.new(0.5, 0.5),
												BackgroundTransparency = 1,
												BorderSizePixel = v74[78],
												Position = UDim2.new(0.500426173, v74[78], 0.376230229, 0),
												Size = UDim2.new(v74[100], v74[78], 0.116130508, v74[78]),
												ZIndex = 2,
												Font = Enum.Font.Cartoon,
												Text = tbl21.ui.Mode,
												TextColor3 = Color3.fromRGB(222, 222, v74[60]),
												TextScaled = true,
												TextSize = v74[107],
												TextWrapped = true,
											})

											local TextLabel3 = fn49("TextLabel", v74[135], Frame, {
												AnchorPoint = Vector2.new(0.5, 0.5),
												BackgroundTransparency = 1,
												BorderSizePixel = 0,
												Position = UDim2.new(0.496443689, 0, 0.578424335, 0),
												Size = UDim2.new(0.783493757, v74[78], v74[23], v74[78]),
												ZIndex = v74[109],
												Font = Enum.Font.Cartoon,
												Text = v74[131],
												TextYAlignment = Enum.TextYAlignment.Top,
												TextColor3 = Color3.fromRGB(222, 222, 222),
												TextScaled = true,
												TextSize = 100,
												TextWrapped = true,
											})

											local TextLabel4 = fn49("TextLabel", "LastTask", Frame, {
												AnchorPoint = Vector2.new(0.5, 0.5),
												BackgroundTransparency = 1,
												BorderSizePixel = 0,
												Position = UDim2.new(v74[149], v74[78], 0.707352996, v74[78]),
												Size = UDim2.new(0.783707261, 0, 0.110473886, 0),
												ZIndex = 2,
												Font = Enum.Font.Cartoon,
												Text = "Task: " .. tbl21.ui.CurrentTask,
												TextColor3 = Color3.fromRGB(222, 222, 222),
												TextScaled = true,
												TextSize = v74[20],
												TextWrapped = v74[29],
												TextYAlignment = Enum.TextYAlignment.Top,
											})

											fn49(v74[156], "Username", Frame, {
												AnchorPoint = Vector2.new(0.5, 0.5),
												BackgroundTransparency = 1,
												BorderSizePixel = v74[78],
												Position = UDim2.new(0.502401173, 0, 0.947248161, v74[78]),
												Size = UDim2.new(v74[91], 0, v74[36], 0),
												Font = Enum.Font.SourceSans,
												Text = tbl17.LocalPlayer.Name,
												TextColor3 = Color3.fromRGB(222, 222, 222),
												TextScaled = v74[29],
												TextSize = 14,
												TextWrapped = true,
											})

											tbl21.ui.UI = { Gui = ScreenGui, Whole = Frame, Info = TextLabel3, LastTask = TextLabel4, SessionTime = TextLabel, CurrentZone = TextLabel2 }
										end

										tbl21.petRenderDisabled = false
										tbl21.renderedFolderConn = nil

										do
											local function fn49(arg)
												if not arg then
													return
												end

												for _, descendant in ipairs(arg:GetDescendants()) do
													if descendant:IsA("BasePart") then
														descendant.Transparency = 1
														descendant.CanCollide = false
														descendant.CastShadow = v74[155]
													elseif descendant:IsA("ParticleEmitter") or descendant:IsA("Trail") or descendant:IsA("Beam") then
														descendant.Enabled = v74[155]
													elseif descendant:IsA("BillboardGui") or descendant:IsA(v74[65]) then
														descendant.Enabled = false
													end
												end
											end

											local function fn50()
												local v75 = tbl17.Workspace:FindFirstChild(v74[58])

												if v75 then
													for _, child in ipairs(v75:GetChildren()) do
														fn49(child)
													end

													return
												end

												if not (n26 >= 1655) then
													return
												end

												while true do
												end
											end

											local function fn51()
												if n29(4114) <= 172 then
													local clientRenderedAssets = tbl17.Workspace:WaitForChild("ClientRenderedAssets")
													if tbl21.renderedFolderConn then
														return
													end

													tbl21.renderedFolderConn = clientRenderedAssets.ChildAdded:Connect(function(child)
														if not tbl21.petRenderDisabled then
															return
														end

														task.defer(function()
															if n29(3089) > 165 then
																fn49(child)
																return
															end

															while true do
															end
														end)
													end)

													fn50()
												else
													while v74[29] do
													end
												end
											end

											fn48 = function()
												if tbl21.petRenderDisabled then
													fn50()
													return
												end
												tbl21.petRenderDisabled = true
												fn51()
												fn50()
												warn("[Optimize] pet render disabled (visual hide only)")
											end
										end
									end

									do
										local function fn49()
											for k, v75 in pairs({ DisableVideos = true, HideOtherPets = true, Music = false, SFX = v74[155] }) do
												pcall(function()
													tbl18.SettingsCmds.Set(k, v75)
												end)
											end

											warn("[Optimize] settings applied")
										end

										local function fn50()
											local playerScripts = tbl17.LocalPlayer:FindFirstChild("PlayerScripts")

											if playerScripts then
												local tbl22 = {}

												for _, descendant in ipairs(playerScripts:GetDescendants()) do
													if descendant:IsA("LocalScript") and not tbl22[descendant.Name] then
														descendant.Disabled = true
													end
												end
											end

											local terrain = tbl17.Workspace:FindFirstChildOfClass("Terrain")

											pcall(function()
												local level01 = Enum.GraphicsQualityLevel.Level01
												UserSettings():GetService("UserGameSettings").GraphicsQualityLevel = level01
												UserSettings():GetService(v74[77]).SavedQualityLevel = Enum.SavedQualitySetting.QualityLevel1
												UserSettings():GetService("UserGameSettings").MasterVolume = v74[78]
												local level012 = Enum.QualityLevel.Level01
												settings().Rendering.QualityLevel = level012
												local level04 = Enum.MeshPartDetailLevel.Level04
												settings().Rendering.MeshPartDetailLevel = level04

												if terrain then
													sethiddenproperty(terrain, "Decoration", v74[155])
												end

												sethiddenproperty(tbl17.Lighting, "Technology", v74[109])
											end)

											for _, child in ipairs(tbl17.Lighting:GetChildren()) do
												child:Destroy()
											end

											pcall(function()
												tbl17.Lighting.GlobalShadows = false
												tbl17.Lighting.ShadowSoftness = v74[137]
												tbl17.Lighting.Brightness = v74[78]
												tbl17.Lighting.Ambient = Color3.new(0, v74[78], v74[78])
												tbl17.Lighting.FogEnd = 0
												tbl17.Lighting.FogStart = 0
												tbl17.Lighting.Technology = Enum.Technology.Voxel
												if not flag2 then
													return
												end
											end)

											if terrain then
												terrain.WaterWaveSize = 0
												terrain.WaterWaveSpeed = 0
												terrain.WaterReflectance = 0
												terrain.WaterTransparency = 1
											end

											local function fn51(arg)
												if arg.Name == v74[69] then
													return
												end

												if arg:IsA("Workspace") then
													if arg:FindFirstChildOfClass("Terrain") then
														arg.Terrain.WaterWaveSize = v74[78]
														arg.Terrain.WaterWaveSpeed = 0
														arg.Terrain.Elasticity = 0
														arg.Terrain.WaterReflectance = 0
														arg.Terrain.WaterTransparency = v74[137]
													end

													pcall(function()
														sethiddenproperty(arg, v74[87], 64)
														sethiddenproperty(arg, v74[9], Enum.StreamingPauseMode.PauseAll)

														if arg:FindFirstChildOfClass("Terrain") then
															sethiddenproperty(arg.Terrain, "Decoration", false)
														end
													end)
												elseif arg:IsA("Model") then
													pcall(function()
														if n28(1843) < 693 then
															sethiddenproperty(arg, v74[11], 1)
														else
															while v74[29] do
															end
														end
													end)
												elseif arg:IsA("TextButton") or arg:IsA(v74[124]) and arg.Name ~= v74[8] or arg:IsA("ImageLabel") then
													arg.Visible = false
												elseif arg:IsA("BasePart") then
													arg.Material = Enum.Material.Plastic
													arg.Reflectance = 0
													arg.Transparency = 1
													if not flag2 then
														return
													end
												elseif arg:IsA("MeshPart") then
													arg.Transparency = 0
													arg.CanCollide = false
												elseif arg:IsA(v74[5]) or arg:IsA("Decal") then
													arg.Texture = ""
													arg.Transparency = 1
												elseif arg:IsA("SpecialMesh") then
													arg.TextureId = ""
												elseif arg:IsA("ShirtGraphic") then
													arg.Graphic = ""
												elseif arg:IsA("Lighting") then
													arg.GlobalShadows = false
													arg.FogEnd = 0
													arg.Brightness = 0
												elseif arg:IsA(v74[119]) or arg:IsA("Pants") then
													arg[arg.ClassName .. "Template"] = ""
												elseif arg:IsA("ParticleEmitter") or arg:IsA(v74[62]) then
													arg.Enabled = false
												elseif arg:IsA("BlurEffect") or arg:IsA("SunRaysEffect") or arg:IsA("ColorCorrectionEffect") or arg:IsA("BloomEffect") or arg:IsA("DepthOfFieldEffect") or arg:IsA("UIGradient") or arg:IsA("UIStroke") or arg:IsA("PointLight") or arg:IsA("Fire") or arg:IsA("SpotLight") or arg:IsA(v74[82]) or arg:IsA("Sparkles") or arg:IsA("Beam") or arg:IsA("BillboardGui") or arg:IsA("SurfaceGui") or arg:IsA("ScreenGui") then
													arg.Enabled = false
												elseif arg:IsA(v74[90]) then
													if n25 > 1788 then
														while true do
														end
													else
														arg.OutlineTransparency = 1
														arg.FillTransparency = v74[137]
													end
												elseif arg:IsA("Explosion") then
													arg.BlastPressure = 0
													arg.BlastRadius = 0
													arg.Position = Vector3.new(0, 0, 0)
												elseif arg:IsA("Sound") then
													arg.Playing = v74[155]
													arg.Volume = 0
												elseif arg:IsA("CharacterMesh") then
													arg.BaseTextureId = ""
													arg.MeshId = ""
													arg.OverlayTextureId = ""
												end
											end

											local v75 = v74[78]

											for _, descendant in ipairs(tbl17.Workspace:GetDescendants()) do
												fn51(descendant)
												v75 += 1

												if v75 % 1000 == v74[78] then
													task.wait(v74[33])
												end
											end

											for _, child in ipairs(tbl17.Players:GetChildren()) do
												if child ~= tbl17.LocalPlayer then
													fn51(child)
													v75 += 1

													if v75 % 1000 == 0 then
														task.wait(0.01)
													end
												end
											end

											for _, descendant in ipairs(tbl17.RS:GetDescendants()) do
												fn51(descendant)
												v75 += 1

												if v75 % 1000 == 0 then
													task.wait(0.01)
												end
											end

											for _, descendant in ipairs(tbl17.LocalPlayer.PlayerGui:GetDescendants()) do
												fn51(descendant)
												v75 += 1

												if v75 % v74[66] == v74[78] then
													task.wait(0.01)
												end
											end

											for _, child in ipairs(tbl17.LocalPlayer.PlayerGui:GetChildren()) do
												if child.Name ~= v74[69] and child.ClassName == "ScreenGui" then
													child.Enabled = false
												end
											end

											pcall(function()
												for _, child in ipairs(tbl17.CoreGui:GetChildren()) do
													if child.Name ~= "DevConsoleMaster" and child:IsA("ScreenGui") then
														child.Enabled = false
													end
												end
											end)

											for _, child in ipairs(tbl17.CoreGui:GetChildren()) do
												if child.Name ~= v74[85] then
													child:Destroy()
												end
											end

											tbl17.Lighting.GlobalShadows = v74[155]
											tbl17.Lighting.FogEnd = v74[150]
											tbl17.Lighting.ShadowSoftness = 0
											tbl17.StarterGui:SetCoreGuiEnabled(Enum.CoreGuiType.All, false)
											tbl17.GuiService.TouchControlsEnabled = false
											tbl17.RunService:Set3dRenderingEnabled(false)
											local n31 = 0

											for _, descendant in ipairs(tbl17.LocalPlayer.PlayerGui:GetDescendants()) do
												if descendant:IsA("Frame") then
													descendant.Visible = false
													n31 += 1

													if n31 % 100 == 0 then
														task.wait(0.01)
													end
												end
											end

											if getrendersteppedlist then
												pcall(function()
													for _, v76 in ipairs(getrendersteppedlist()) do
														tbl17.RunService:UnbindFromRenderStep(v76.Name)
													end
												end)
											end

											local n32 = 0

											for _, v76 in { v74[101], "RenderStepped", "Stepped", "PreSimulation", "PostSimulation", "PreRender" }, nil, nil do
												for _, v77 in getconnections(tbl17.RunService[v76]) do
													local function_ = v77.Function

													if function_ then
														local ok, result = pcall(getinfo, function_, "s")
														if ok and result and string.find(getinfo(function_).source, "=ReplicatedFirst.UGI.ContentCatalog") then
															continue
														end
													end

													v77:Disconnect()
													n32 += v74[137]

													if n32 % 200 == 0 then
														task.wait()
													end
												end
											end

											warn("[Optimize] optimization1 complete")
										end

										fn34 = function()
											if n27(4159) <= 14474 then
												fn26()

												if tbl20.ApplyOptimizationSettings then
													fn49()
												end

												if tbl20.DisablePetRender then
													fn48()
												end

												if tbl20.Optimization1 then
													if n25 < 1749 then
														while true do
														end
													else
														fn50()
													end
												end

												return
											end

											while true do
											end
										end
									end
								end
							end
						end

						do
							local fn45, fn46

							do
								do
									do
										fn35 = function()
											if v74[112] <= n28(225) then
												local v75 = tbl18.Save.Get()
												assert(v75, v74[120])
												local n31 = -1
												local alreadyEquipped = nil

												for k in pairs(v75.TrailInventory) do
													local v76 = fn27(tbl18.TrailsDir)[k]

													if v76 and v76.Price > n31 then
														n31 = v76.Price
														alreadyEquipped = k
													end
												end

												if not alreadyEquipped then
													local v76 = v74[68]
													if n28(4342) < v76 then
														return false, "No trails owned"
													end

													while true do
													end
												else
													if v75.EquippedTrail == alreadyEquipped then
														return true, "Already equipped: " .. alreadyEquipped
													end

													if not (v74[147] < n25) then
														local response2, v76 = tbl19.AskTrailChoose:InvokeServer(alreadyEquipped)
														if not response2 then
															return false, v76 or "Equip failed"
														end
														return v74[29], "Equipped: " .. alreadyEquipped
													end

													while true do
													end
												end
											else
												while true do
												end
											end
										end

										do
											local function fn47()
												local v75 = tbl18.Save.Get()
												assert(v75, "Expected local save data")
												if v75.BaseUpgradeLevel >= stealAnEgg.MaxPlotLevel then
													return v74[155], ("Max level: %d/%d"):format(v75.BaseUpgradeLevel, stealAnEgg.MaxPlotLevel)
												end

												if typeof(tbl18.BaseUpgrade.PurchaseNextTier) == "function" then
													local v76, v77 = tbl18.BaseUpgrade.PurchaseNextTier()
													if not v76 then
														return false, v77 or "Upgrade failed"
													end
													return true
												end

												tbl19.AskBaseTierRaise:FireServer()
												return true
											end

											fn36 = function()
												local n31 = 0
												local v75

												while true do
													local v76 = tbl18.Save.Get()
													assert(v76, "Expected local save data")

													if stealAnEgg.MaxPlotLevel <= v76.BaseUpgradeLevel then
														if not (n26 >= 1659) then
															return n31, ("Done, level: %d"):format(tbl18.Save.Get().BaseUpgradeLevel)
														end

														while true do
														end
													else
														local v77
														v77, v75 = fn47()
														if not v77 then
															break
														end
														n31 += 1
														task.wait(0.2)
													end
												end

												return n31, v75
											end
										end
									end

									tbl21.sortedTreadmills = {}

									do
										local v75 = pairs
										local v76 = fn27(tbl18.TreadmillsDir)

										for k, v77 in v75(v76) do
											table.insert(tbl21.sortedTreadmills, { Name = k, Price = v77.Price })
										end
									end
								end

								do
									table.sort(tbl21.sortedTreadmills, function(arg, arg2)
										return arg.Price < arg2.Price
									end)

									do
										local function fn47()
											return tbl21.sortedTreadmills[tbl18.Save.Get().TreadmillUpgradeLevel + 1]
										end

										local function fn48()
											local v75 = tbl18.Save.Get()
											assert(v75, "Expected local save data")

											if stealAnEgg.MaxTreadmillLevel <= v75.TreadmillUpgradeLevel then
												if n29(3388) <= 145 then
													return false, ("Max level: %d/%d"):format(v75.TreadmillUpgradeLevel, stealAnEgg.MaxTreadmillLevel)
												end

												while v74[29] do
												end
											end

											local v76 = fn47()
											if not v76 then
												return v74[155], "No more treadmills to upgrade"
											end

											if v75.Money < v76.Price then
												return false, ("Not enough money for %s: need %d, have %d"):format(v76.Name, v76.Price, v75.Money)
											end
											local response2, v77 = tbl19.AskTreadmillTierRaise:InvokeServer(v76.Name)
											if not response2 then
												return v74[155], v77 or "Treadmill upgrade failed"
											end
											return true, "Upgraded to: " .. v76.Name
										end

										fn37 = function()
											local n31 = 0
											local v75

											while true do
												local v76 = tbl18.Save.Get()
												assert(v76, "Expected local save data")

												if stealAnEgg.MaxTreadmillLevel <= v76.TreadmillUpgradeLevel then
													return n31, ("Done, level: %d"):format(tbl18.Save.Get().TreadmillUpgradeLevel)
												else
													if not fn47() then
														return n31, ("Done, level: %d"):format(tbl18.Save.Get().TreadmillUpgradeLevel)
													end
													local v77
													v77, v75 = fn48()
													if not v77 then
														break
													end
													n31 += 1
													task.wait(0.2)
												end
											end

											return n31, v75
										end
									end
								end

								fn45 = function()
									local character = tbl17.LocalPlayer.Character
									if not character then
										return nil, nil
									end
									local humanoid = character:FindFirstChildWhichIsA("Humanoid")
									if not humanoid or humanoid.Health <= 0 then
										return nil, nil
									end
									return humanoid, character
								end

								do
									local function fn47(arg)
										if not arg or not arg:IsA(v74[79]) then
											return nil
										end

										local ok, result = pcall(function()
											return tbl18.EggToolDisplay.GetToolUid(arg)
										end)

										if ok and result ~= nil then
											return result
										end

										for _, v75 in ipairs({ v74[45], "Uid", v74[145], "AssetUid", "Id" }) do
											local attribute = arg:GetAttribute(v75)
											if attribute ~= nil then
												return attribute
											end
										end

										return nil
									end

									local function fn48(arg)
										warn("[Tools]", arg)

										local function fn49(arg2)
											if not arg2 then
												return
											end

											for _, child in ipairs(arg2:GetChildren()) do
												if child:IsA("Tool") then
													local tbl22 = {}

													for k, v75 in pairs(child:GetAttributes()) do
														tbl22[#tbl22 + 1] = tostring(k) .. "=" .. tostring(v75)
													end

													local concat = table.concat
													warn(" ", arg2.Name, child.Name, "uid=", fn47(child), concat(tbl22, ", "))
												end
											end
										end

										fn49(tbl17.LocalPlayer:FindFirstChild("Backpack"))
										fn49(tbl17.LocalPlayer.Character)
									end

									fn46 = function(arg)
										if n28(2135) >= 353 then
											local v75, v76 = fn45()
											if not v76 then
												return nil
											end

											local function fn49(arg2)
												if not arg2 then
													return nil
												end

												for _, child in ipairs(arg2:GetChildren()) do
													if child:IsA(v74[79]) and fn47(child) == arg then
														return child
													end
												end

												return nil
											end

											return fn49(tbl17.LocalPlayer:FindFirstChild("Backpack")) or fn49(v76)
										end

										while v74[29] do
										end
									end

									fn38 = function(arg)
										local value = select(1, fn45())
										if not value then
											return v74[155], "No humanoid"
										end
										local v75 = nil

										for i = 1, 25 do
											v75 = fn46(arg)
											if not v75 then
												task.wait(v74[71])
												continue
											end
											break
										end

										if not v75 then
											fn48("missing uid " .. tostring(arg))
											return v74[155], "Tool not found for uid: " .. tostring(arg)
										end
										value:UnequipTools()
										task.wait(v74[159])
										value:EquipTool(v75)
										task.wait(0.1)
										local v76, v77 = fn45()
										v77 = v77 and v77:FindFirstChildWhichIsA(v74[79])
										if not v77 or fn47(v77) ~= arg then
											return false, v74[1]
										end
										return true, v75
									end
								end
							end

							do
								local fn47

								do
									do
										local function fn48(arg, arg2)
											if arg.BaseMutation == arg2 then
												return true
											end

											if arg.Mutations then
												for _, mutation in pairs(arg.Mutations) do
													if mutation == arg2 then
														return true
													end
												end
											end

											return false
										end

										local function fn49(arg)
											if arg.BaseMutation then
												return false
											end

											if arg.Mutations then
												for _, mutation in pairs(arg.Mutations) do
													if mutation then
														return false
													end
												end
											end

											return true
										end

										fn47 = function(arg, arg2)
											if arg.Category ~= arg2.Name then
												return false
											end

											if arg2.Mutation ~= v74[88] then
												if arg2.Mutation == v74[44] then
													if not fn49(arg) then
														if not flag3 then
															return
														end
														return false
													end
												elseif not fn48(arg, arg2.Mutation) then
													return false
												end
											end

											if arg2.MaxKG and arg2.MaxKG > 0 then
												if arg2.MaxKG < (arg.Scale or v74[78]) then
													return false
												end
											end

											return true
										end
									end
								end

								do
									local function fn48(arg, arg2, arg3)
										if not arg3[arg] then
											if arg2.InFuse then
												return v74[155]
											end

											if arg2.IsFavorite == true then
												return v74[155]
											end

											for _, sellPet in ipairs(stealAnEgg.SellPets) do
												if fn47(arg2, sellPet) then
													return true
												end
											end

											if n25 >= 1790 then
												while v74[29] do
												end
											end

											return false
										end

										if not (v74[94] <= n25) then
											return false
										end

										while true do
										end
									end

									fn39 = function()
										if #stealAnEgg.SellPets == v74[78] then
											return 0, "No categories configured"
										end
										local n31 = 0

										while true do
											local v75 = tbl18.Save.Get()
											assert(v75, "Expected local save data")
											local v76, v77 = fn45()

											if not v76 then
												return n31, "No character/humanoid"
											else
												local tbl22 = {}

												if v75.EquippedAssets then
													for _, equippedAsset in ipairs(v75.EquippedAssets) do
														tbl22[equippedAsset] = true
													end
												end

												local toolNotFoundForUid = nil

												for k, v78 in pairs(v75.Inventory) do
													if fn48(k, v78, tbl22) then
														toolNotFoundForUid = k
														break
													else
														toolNotFoundForUid = nil
													end
												end

												if not toolNotFoundForUid then
													return n31, ("Sold %d pets"):format(n31)
												end
												local v78 = fn46(toolNotFoundForUid)

												if not v78 then
													task.wait(0.3)
													v78 = fn46(toolNotFoundForUid)
													if not v78 then
														return n31, "Tool not found for uid: " .. toolNotFoundForUid
													end
												end

												v76:UnequipTools()
												task.wait(0.1)
												v76:EquipTool(v78)
												task.wait(v74[16])
												local tool = v77:FindFirstChildWhichIsA("Tool")
												if not tool or tool:GetAttribute(v74[45]) ~= toolNotFoundForUid then
													break
												end
												tbl19.SellPet:FireServer({ toolNotFoundForUid })
												n31 += 1
												task.wait(v74[123])
											end
										end

										return n31, "Failed to equip tool"
									end
								end
							end
						end

						do
							fn40 = function(arg)
								local ok, result = pcall(function()
									if not (v74[154] < n26) then
										local v75 = tbl18.EggItemUtil.DeserializeSavedEgg(arg)
										return tbl18.EggItemUtil.GetDisplayName(v75)
									end

									while true do
									end
								end)

								if ok then
									return result
								end
								return arg.AreaId and arg.AreaId .. " Egg" or arg.AssetCategory
							end

							do
								local function fn45(arg)
									local ok, result = pcall(function()
										if tbl18.EggItemUtil.GetWeightKgForScale then
											return tbl18.EggItemUtil.GetWeightKgForScale(arg.AssetCategory, arg.AssetScale)
										end
										local v75 = tbl18.EggItemUtil.DeserializeSavedEgg(arg)
										if tbl18.EggItemUtil.GetWeightKg then
											return tbl18.EggItemUtil.GetWeightKg(v75)
										end
										return nil
									end)

									if ok and typeof(result) == "number" then
										return result
									end
									return arg.AssetScale or 0
								end

								local function fn46(arg)
									if not (n25 > 1786) then
										local assetCategory = arg.AssetCategory
										local v75 = fn27(tbl18.AssetsDir)[assetCategory]
										if not v75 or not v75.Rarity then
											return nil
										end
										return v75.Rarity.DisplayName or v75.Rarity._id
									end

									while true do
									end
								end

								local function fn47(arg)
									if typeof(arg.BottomCFrame) == "CFrame" then
										return arg.BottomCFrame.Position
									end

									if typeof(arg.BoundsCFrame) == "CFrame" then
										return arg.BoundsCFrame.Position
									end
									return nil
								end

								fn41 = function()
									local v75 = tbl18.EggCmds.RequestAreaEggSnapshot()
									if not v75 or not v75.Records then
										return {}
									end
									local tbl22 = {}

									for _, record in ipairs(v75.Records) do
										if record.State == "Slot" or record.State == "Dropped" then
											table.insert(tbl22, {
												Uid = record.Uid,
												AssetCategory = record.AssetCategory,
												AreaId = record.AreaId,
												NestId = record.NestId,
												AssetScale = record.AssetScale,
												State = record.State,
												Name = fn40(record),
												WeightKg = fn45(record),
												Rarity = fn46(record),
												Position = fn47(record),
												Record = record,
											})
										end
									end

									return tbl22
								end
							end
						end

						fn42 = function()
							local serverTimeNow = tbl17.Workspace:GetServerTimeNow()

							for _, v75 in ipairs({ "SecondsUntilPhaseEnd", "SecondsUntilReset", "GetPhaseTimeLeft", "GetTimeLeft" }) do
								local v76 = tbl18.AreaEggCycle[v75]
								if typeof(v76) ~= "function" then
									continue
								end
								local ok, result = pcall(v76, serverTimeNow)
								local flag14 = not ok

								if not flag14 then
									local v77 = v74[6]
									flag14 = typeof(result) ~= v77
								end

								if flag14 then
									ok, result = pcall(v76)
								end

								if ok and typeof(result) == "number" then
									return result, v75
								end
							end

							for _, v75 in ipairs({ "NextResetTime", v74[61], "GetNextResetAt", "GetNightTransitionStartsAt", "GetNextNightAt" }) do
								local v76 = tbl18.AreaEggCycle[v75]
								if typeof(v76) ~= "function" then
									continue
								end
								local ok, result = pcall(v76, serverTimeNow)

								if not ok or typeof(result) ~= "number" then
									ok, result = pcall(v76)
								end

								if ok and typeof(result) == "number" then
									return math.max(result - serverTimeNow, 0), v75
								end
							end

							return nil, nil
						end

						fn43 = function()
							local v75, v76 = fn42()
							if v75 == nil then
								warn("[StealEggs] could not resolve cycle time left")
								return v74[29], nil
							end

							if v75 < tbl20.StealMinSecondsUntilCycle then
								return false, ("Cycle change too soon: %.1fs via %s"):format(v75, v76)
							end
							return v74[29], v75
						end

						do
							local function fn45(arg)
								if typeof(arg) ~= "string" then
									return ""
								end
								local str7 = string.lower(arg):gsub("%s+", v74[103]):gsub("^%s+", ""):gsub("%s+$", "")

								if str7:sub(-4) == " egg" then
									str7 = str7:sub(1, -5)
								end

								return str7
							end

							fn44 = function(arg, arg2)
								if arg.Name == arg2 then
									return true
								end

								if arg.AreaId == arg2 then
									return v74[29]
								end
								return fn45(arg.Name) == fn45(arg2) or fn45(arg.AreaId) == fn45(arg2)
							end
						end
					end

					local fn45, fn46, fn47, fn48, fn49, fn50, fn51, fn52, fn53, fn54

					do
						do
							local fn55, fn56, fn57, fn58

							do
								do
									fn55 = function(arg)
										for _, stealEgg in ipairs(stealAnEgg.StealEggs) do
											if fn44(arg, stealEgg.Name) then
												local minKG = stealEgg.MinKG or 0
												local flag14 = minKG <= 0

												if not flag14 then
													flag14 = (arg.WeightKg or 0) >= minKG
												end

												if flag14 and (not stealEgg.Rarity or stealEgg.Rarity == "All" or arg.Rarity == stealEgg.Rarity) then
													return v74[29]
												end
											end
										end

										return false
									end

									fn56 = function(...)
										if tbl20.Debug.Steal then
											warn("[StealEggs]", ...)
										end
									end

									do
										local function fn59(arg, arg2)
											if not fn44(arg, arg2.Name) then
												local v75 = tostring
												local name = arg2.Name
												return ("name mismatch: egg=%q area=%q cfg=%q"):format(tostring(arg.Name), tostring(arg.AreaId), v75(name))
											end

											local minKG = arg2.MinKG or 0
											local flag14 = minKG <= 0

											if not flag14 then
												flag14 = (arg.WeightKg or 0) >= minKG
											end

											if not flag14 then
												if n26 > 1657 then
													while v74[29] do
													end
												end

												return ("weight too low: %.3f < MinKG %d"):format(arg.WeightKg or v74[78], minKG)
											end

											if not (not arg2.Rarity or arg2.Rarity == "All" or arg.Rarity == arg2.Rarity) then
												local v75 = tostring
												local rarity = arg2.Rarity
												return ("rarity mismatch: egg=%q cfg=%q"):format(tostring(arg.Rarity), v75(rarity))
											end

											if not arg.Position then
												return "matched config but no Position"
											end
											return v74[56]
										end

										fn57 = function(arg, arg2)
											if not tbl20.Debug.Steal then
												return
											end
											local records = tbl18.EggCmds.RequestAreaEggSnapshot()
											records = records and records.Records or {}
											arg2 = arg2 or fn41()
											fn56(("=== zone eggs debug (%s) ==="):format(arg or "?"))
											fn56("snapshot records", #records, v74[13], #arg2)
											if #records == v74[78] then
												fn56("no records in snapshot")
												return
											end
											local tbl22 = {}

											for _, record in ipairs(records) do
												local str7 = tostring(record.State)
												tbl22[str7] = (tbl22[str7] or 0) + 1
											end

											fn56("states", tbl22)

											if #arg2 == 0 then
												fn56("no Slot/Dropped eggs in snapshot")

												for i, record in ipairs(records) do
													if i <= 8 then
														fn56(v74[96], i, v74[122], record.State, "AreaId", record.AreaId, "AssetCategory", record.AssetCategory, "UiName", fn40(record))
													end
												end

												return
											end

											for i, v75 in ipairs(arg2) do
												local str7 = v75.Position and tostring(v75.Position) or "nil"
												local name = v75.Name
												local rarity = v75.Rarity
												local weightKg = v75.WeightKg
												local state = v75.State
												local areaId = v75.AreaId
												local nestId = v75.NestId
												local assetCategory = v75.AssetCategory
												fn56(("egg[%d]"):format(i), "Name", name, "Rarity", rarity, "KG", weightKg, "State", state, "Area", areaId, "Nest", nestId, "Category", assetCategory, "Pos", str7)
												local flag14 = v74[155]

												for i2, stealEgg in ipairs(stealAnEgg.StealEggs) do
													local v76 = fn59(v75, stealEgg)
													fn56(("  cfg[%d]"):format(i2), stealEgg.Name, stealEgg.Rarity or "All", v74[52], stealEgg.MinKG or v74[78], "->", v76)

													if v76 == "MATCH" then
														flag14 = true
													end
												end

												if not flag14 then
													fn56("  => no StealEggs rule matched")
												end
											end

											fn56("configured StealEggs:")

											for i, stealEgg in ipairs(stealAnEgg.StealEggs) do
												fn56(("  rule[%d]"):format(i), "Name", stealEgg.Name, "Rarity", stealEgg.Rarity or v74[88], "MinKG", stealEgg.MinKG or 0)
											end
										end
									end
								end

								do
									local fn59, fn60

									do
										fn45 = function()
											if #stealAnEgg.StealEggs == 0 then
												return false
											end
											local v75 = fn41()

											for _, v76 in ipairs(v75) do
												if fn55(v76) and v76.Position then
													return true
												end
											end

											fn57("hasMatchingStealTarget=false", v75)
											return false
										end

										fn46 = function()
											local n31 = 0

											for _, v75 in ipairs(fn41()) do
												if fn55(v75) and v75.Position then
													n31 += 1
												end
											end

											return n31
										end

										fn47 = function()
											local character = tbl17.LocalPlayer.Character
											if not character then
												return nil
											end
											return character:FindFirstChild(v74[55])
										end

										do
											local function fn61()
												local character = tbl17.LocalPlayer.Character
												if not character then
													return nil
												end
												return character:FindFirstChildWhichIsA("Humanoid")
											end

											fn48 = function(arg)
												if not arg then
													return
												end

												pcall(function()
													arg.AssemblyLinearVelocity = Vector3.zero
													if not flag2 then
														return
													end
													arg.AssemblyAngularVelocity = Vector3.zero
												end)
											end

											fn49 = function(platformStand)
												local v75 = fn47()
												local v76 = fn61()

												if v75 then
													v75.Anchored = v74[155]
													fn48(v75)
												end

												if v76 then
													pcall(function()
														v76.PlatformStand = platformStand

														if platformStand then
															v76:ChangeState(Enum.HumanoidStateType.Physics)
														elseif n25 >= 1779 then
															while true do
															end
														else
															v76:ChangeState(Enum.HumanoidStateType.Running)
														end
													end)
												end
											end

											fn50 = function(forceStealPosition)
												local v75 = fn47()
												if not v75 then
													return v74[155], "No HumanoidRootPart"
												end
												v75.Anchored = v74[155]
												fn48(v75)
												local position = v75.Position
												local n31 = math.max((position - forceStealPosition).Magnitude / math.max(tbl20.StealFlySpeed, 1), 0.05)
												local now2 = os.clock()

												while true do
													local v76 = fn47()
													if not v76 or not v76.Parent then
														return false, "Root lost during tween"
													end
													local n32 = math.min((os.clock() - now2) / n31, 1)
													local v77 = position:Lerp(forceStealPosition, n32)
													v76.CFrame = CFrame.new(v77)
													fn48(v76)
													stealAnEgg.ForceStealPosition = v77
													if n32 >= 1 then
														break
													end
													task.wait()
												end

												local v76 = fn47()

												if v76 then
													v76.CFrame = CFrame.new(forceStealPosition)
													fn48(v76)
													stealAnEgg.ForceStealPosition = forceStealPosition
												end

												return v74[29]
											end

											fn59 = function(forceStealPosition, arg)
												local n31 = os.clock() + arg

												while os.clock() < n31 do
													local v75 = fn47()

													if v75 then
														v75.Anchored = v74[155]
														v75.CFrame = CFrame.new(forceStealPosition)
														fn48(v75)
													end

													stealAnEgg.ForceStealPosition = forceStealPosition
													task.wait()
												end
											end

											fn60 = function()
												local v75 = fn61()

												if v75 then
													pcall(function()
														v75.PlatformStand = v74[155]
														v75.Sit = v74[155]

														if v75.Health <= 0 then
															v75.Health = v75.MaxHealth
														end

														v75:ChangeState(Enum.HumanoidStateType.Running)
													end)

													return v75.Health > 0
												end

												if not (n26 > 1661) then
													return v74[155]
												end

												while true do
												end
											end
										end
									end

									do
										local function fn61(arg)
											local tbl22 = { Uid = arg.Uid }
											local ok

											if tbl18.AreaEggSlotIdentity.IsFirstAreaUid then
												local result
												ok, result = pcall(tbl18.AreaEggSlotIdentity.IsFirstAreaUid, arg.Uid)
												ok = ok and result == true
											else
												local v75 = v74[34]
												ok = typeof(arg.Uid) == v75 and string.find(arg.Uid, "FirstAreaEgg_", v74[137], true) ~= nil
											end

											if ok and arg.AreaId and arg.NestId then
												if n28(1725) <= 8148 then
													local firstAreaSlotKey = nil

													if tbl18.AreaEggSlotIdentity.BuildSlotKey then
														local ok2
														ok2, firstAreaSlotKey = pcall(tbl18.AreaEggSlotIdentity.BuildSlotKey, arg.AreaId, arg.NestId)
														local v75 = nil

														if not ok2 then
															firstAreaSlotKey = v75
														end
													end

													tbl22.FirstAreaSlotKey = firstAreaSlotKey or arg.AreaId .. ":" .. arg.NestId
												else
													while true do
													end
												end
											end

											if tbl18.EggCmds.RequestCarryAreaEgg then
												return tbl18.EggCmds.RequestCarryAreaEgg(arg.Uid, tbl22.FirstAreaSlotKey)
											end
											return tbl19.RequestAreaEggCarry:InvokeServer(tbl22)
										end

										fn58 = function(arg, arg2)
											for i = 1, 3 do
												fn60()
												fn59(arg2, tbl20.StealReplicateWait + (i - 1) * v74[84])
												local v75 = fn47()
												fn56("pre-carry", i, v75 and v75.Position, "force", stealAnEgg.ForceStealPosition)
												local v76, v77 = fn61(arg)
												fn56("carry result", i, v76, v77, "pos now", fn47() and fn47().Position)
												if v76 then
													return true
												end
												local str7 = tostring(v77 or "")
												if str7:find(v74[129], 1, true) or str7:find(v74[28], 1, true) or str7:find("closer", 1, true) then
													task.wait(0.35)
													continue
												end
												return v74[155], v77
											end

											return v74[155], "Carry failed after retries"
										end
									end
								end
							end

							do
								local function fn59(arg)
									return fn38(arg)
								end

								local function fn60(arg)
									if not arg.Position then
										return false, v74[47]
									end
									fn29(("Stealing: %s (%.1f kg)"):format(arg.Name, arg.WeightKg or 0))
									local v75, v76 = fn43()
									fn56("cycle check", v75, v76)
									if not v75 then
										return false, v76
									end
									local v77 = fn47()
									if not v77 then
										return false, "No HumanoidRootPart"
									end
									local stealReturnPosition = tbl20.StealReturnPosition
									local position = arg.Position
									local stealHeightOffset = tbl20.StealHeightOffset
									local n31 = position + Vector3.new(v74[78], tbl20.StealLandOffset, 0)
									local n32 = v77.Position + Vector3.new(0, stealHeightOffset, v74[78])
									local n33 = position + Vector3.new(0, stealHeightOffset, 0)
									fn56("target", arg.Name, arg.Uid, v74[41], arg.AreaId, v74[134], arg.NestId)
									fn56(v74[136], arg.WeightKg, "eggPos", position, "landPos", n31)
									fn56("from", v77.Position, v74[18], stealReturnPosition)
									local n34 = v77.Position + Vector3.new(v74[78], stealHeightOffset, v74[78])
									local n35 = stealReturnPosition + Vector3.new(0, stealHeightOffset, v74[78])
									fn49(true)
									fn56("flight ON (no anchor, PlatformStand)")

									local function fn61(arg2)
										stealAnEgg.ForceStealPosition = nil
										fn49(false)
										return false, arg2
									end

									local v78, v79 = fn50(n34)
									fn56("tween highHere", v78, v79, fn47() and fn47().Position)
									if not v78 then
										local v80, v81 = fn61(v79)
										return v80, v81
									end
									local v80, v81 = fn50(n35)
									fn56("tween highReturn", v80, v81, fn47() and fn47().Position)
									if not v80 then
										local v82, v83 = fn61(v81)
										return v82, v83
									end
									local v82, v83 = fn50(stealReturnPosition)
									fn56("tween returnPos (pre)", v82, v83, fn47() and fn47().Position)

									if v82 then
										local v84, v85 = fn50(n35)
										fn56("tween highReturn2", v84, v85, fn47() and fn47().Position)
										if not v84 then
											local v86, v87 = fn61(v85)
											return v86, v87
										end
										local v86, v87 = fn50(n33)
										fn56("tween highEgg", v86, v87, fn47() and fn47().Position)
										if not v86 then
											local v88, v89 = fn61(v87)
											return v88, v89
										end
										local v88, v89 = fn50(n31)
										fn56("tween landPos", v88, v89, fn47() and fn47().Position)
										if not v88 then
											local v90, v91 = fn61(v89)
											return v90, v91
										end
										fn49(v74[155])
										local v90, v91 = fn58(arg, n31)
										if not v90 then
											return false, v91 or "Carry failed"
										end
										fn49(v74[29])
										local v92 = fn47()
										if not v92 then
											fn49(v74[155])
											return false, v74[10]
										end
										local position2 = v92.Position
										local n36 = position2.Y + stealHeightOffset
										local vector = Vector3.new(stealReturnPosition.X - position2.X, 0, stealReturnPosition.Z - position2.Z)
										local magnitude = vector.Magnitude
										local unit = magnitude > 0.001 and vector.Unit or Vector3.new(0, 0, -1)
										local n37 = math.min(tbl20.StealClimbHoriz, math.max(magnitude * 0.2, 20))

										if magnitude < n37 then
											n37 = magnitude
										end

										local vector2 = Vector3.new(position2.X + unit.X * n37, n36, position2.Z + unit.Z * n37)
										local vector3 = Vector3.new(stealReturnPosition.X, n36, stealReturnPosition.Z)
										fn56("return climb", vector2, "cruise", vector3, "from", position2, v74[14], magnitude)
										local v93, v94 = fn50(vector2)
										fn56("tween climbPos", v93, v94, fn47() and fn47().Position)
										if not v93 then
											fn49(v74[155])
											return false, v94
										end

										if (vector2 - vector3).Magnitude > v74[137] then
											local v95, v96 = fn50(vector3)
											fn56("tween cruisePos", v95, v96, fn47() and fn47().Position)
											if not v95 then
												fn49(false)
												return false, v96
											end
										end

										local v95, v96 = fn50(stealReturnPosition)
										fn56("tween returnPos", v95, v96, fn47() and fn47().Position)
										if not v95 then
											fn49(false)
											return false, v96
										end
										fn49(false)
										fn56(v74[133], arg.Uid)
										local v97, v98 = fn59(arg.Uid)
										fn56("equip result", v97, v98)
										return true, arg.Name
									end

									if n27(2698) <= 13619 then
										local v84, v85 = fn61(v83)
										return v84, v85
									end

									while true do
									end
								end

								fn51 = function()
									if #stealAnEgg.StealEggs == 0 then
										return 0, "No StealEggs configured"
									end
									fn30(v74[105])
									fn29("Scanning steal targets...")
									fn57("autoStealEggs start")
									local v75 = v74[78]
									local v76

									while true do
										local v77, v78 = fn43()

										if not v77 then
											fn56("cycle blocked steal", v78)
											fn57(v74[141])
											return v75, v78
										else
											local v79 = nil

											for _, v80 in ipairs(fn41()) do
												if fn55(v80) and v80.Position then
													v79 = v80
													break
												else
													v79 = nil
												end
											end

											if not v79 then
												if v75 == 0 then
													fn57("autoStealEggs no target")
												end

												return v75, ("Stolen %d eggs"):format(v75)
											end

											local v80
											v80, v76 = fn60(v79)
											if not v80 then
												break
											end
											v75 += 1
											task.wait(0.3)
										end
									end

									return v75, v76
								end
							end
						end

						do
							local fn55, fn56, fn57, fn58, fn59, fn60, fn61

							do
								do
									fn55 = function(arg)
										if arg.Placement == nil then
											return false
										end
										local serverTimeNow = tbl17.Workspace:GetServerTimeNow()
										local readyAt = arg.Placement.ReadyAt

										if typeof(readyAt) == "number" then
											if not flag2 then
												return
											end
											return serverTimeNow >= readyAt
										end

										if typeof(tbl18.EggGrowth.IsReady) == "function" then
											local ok, result = pcall(tbl18.EggGrowth.IsReady, arg)
											if ok and typeof(result) == "boolean" then
												return result
											end
										end

										local v75 = v74[78]
										local result

										if typeof(tbl18.EggItemUtil.GetCurrentNightGrowthCreditSeconds) == "function" then
											local ok
											ok, result = pcall(tbl18.EggItemUtil.GetCurrentNightGrowthCreditSeconds, arg, serverTimeNow, arg.GrowthSpeedMultiplier)

											if not (ok and typeof(result) == "number") then
												result = v75
											end
										else
											result = v75
										end

										if typeof(tbl18.EggItemUtil.GetGrowthAlpha) == "function" then
											local ok, result2 = pcall(tbl18.EggItemUtil.GetGrowthAlpha, arg, serverTimeNow, arg.GrowthSpeedMultiplier, result, tbl17.LocalPlayer)
											if ok and typeof(result2) == "number" then
												return result2 >= 1
											end
										end

										return false
									end

									tbl21.hatchWebhookHooked = false

									fn56 = function(arg)
										local request_ = syn and syn.request or http_request or request or http and http.request or fluxus and fluxus.request
										if typeof(request_) == "function" then
											return request_(arg)
										end
										return tbl17.HttpService:RequestAsync({ Url = arg.Url, Method = arg.Method or "POST", Headers = arg.Headers, Body = arg.Body })
									end

									fn57 = function(arg)
										if not arg then
											return "None"
										end
										local v75 = v74[34]
										if typeof(arg.BaseMutation) == v75 and arg.BaseMutation ~= "" then
											return arg.BaseMutation
										end
										local mutations = arg.Mutations
										if typeof(mutations) ~= "table" then
											return v74[44]
										end
										local tbl22 = {}

										for k, mutation in pairs(mutations) do
											if typeof(mutation) == "string" then
												table.insert(tbl22, mutation)
											elseif typeof(k) == "string" and mutation == true then
												table.insert(tbl22, k)
											end
										end

										if #tbl22 == 0 then
											return v74[44]
										end
										table.sort(tbl22)
										return table.concat(tbl22, ", ")
									end

									fn58 = function(arg)
										local v75 = v74[148]

										if n29(2224) < v75 then
											local v76 = fn27(tbl18.AssetsDir)[arg]
											if not v76 or not v76.Rarity then
												return nil, 5763719
											end
											local rarity = v76.Rarity
											local displayName = rarity.DisplayName or rarity._id or "Unknown"
											local n31 = 5763719

											if rarity.Color then
												local color = rarity.Color
												local v77 = v74[157]
												n31 = math.floor(color.R * 255 + 0.5) * v77 + math.floor(color.G * v74[110] + 0.5) * 256 + math.floor(color.B * v74[110] + 0.5)
											end

											return displayName, n31
										end

										while true do
										end
									end

									do
										local function fn62(arg)
											if typeof(arg) ~= "string" then
												return ""
											end
											local lower = string.lower
											local str7 = arg:gsub("%s+", "")
											return lower(str7)
										end

										local function fn63(arg, arg2)
											local v75 = fn62(arg)
											if v75 == "" then
												return false
											end
											return arg2[v75] == true
										end

										local function fn64(arg)
											local tbl22 = {}
											local v75 = v74[102]
											if typeof(arg) ~= v75 then
												return tbl22
											end

											for _, v76 in ipairs(arg) do
												local v77 = fn62(v76)

												if v77 ~= "" then
													tbl22[v77] = true
												end
											end

											return tbl22
										end

										tbl20.PrivateHatchRaritySet = fn64(stealAnEgg.PrivateHatchWebhookRarities)
										tbl20.GlobalHatchWebhookRarities = fn64({ "Secret", "Eternal", "Divine" })

										fn59 = function(arg)
											if arg then
												arg = arg.Category or arg.AssetCategory
											end

											if not arg then
												return v74[155]
											end
											local privateHatchRaritySet = tbl20.PrivateHatchRaritySet
											return fn63(fn58(arg), privateHatchRaritySet)
										end

										fn60 = function(arg)
											local category = arg and (arg.Category or arg.AssetCategory)
											if not category then
												return false
											end
											local globalHatchWebhookRarities = tbl20.GlobalHatchWebhookRarities
											return fn63(fn58(category), globalHatchWebhookRarities)
										end
									end
								end

								tbl21.petImgCache = {}

								do
									local function fn62(arg)
										if not arg or arg == "" then
											return ""
										end
										local str7 = "https://thumbnails.roblox.com/v1/assets?assetIds=" .. tostring(arg) .. "&size=150x150&format=Png&isCircular=false"
										local v75 = request or http_request
										local request_

										if v75 then
											request_ = v75
										else
											request_ = syn and syn.request
										end

										if not request_ then
											return ""
										end

										local ok, result = pcall(function()
											return request_({ Url = str7, Method = "GET" })
										end)

										if not ok or not result or not result.Body then
											return ""
										end
										local ok2, result2 = pcall(tbl17.HttpService.JSONDecode, tbl17.HttpService, result.Body)
										if not ok2 or not result2 or not result2.data or not result2.data[v74[137]] then
											return ""
										end
										return result2.data[v74[137]].imageUrl or ""
									end

									local function fn63(arg)
										if tbl21.petImgCache[arg] ~= nil then
											return tbl21.petImgCache[arg]
										end
										local v75 = fn27(tbl18.AssetsDir)[arg]
										local icon = v75 and v75.Icon
										local str7 = ""

										if icon then
											if v74[72] <= n27(3017) then
												str7 = tostring(v75.Icon):gsub("rbxassetid://", "")
											else
												while true do
												end
											end
										end

										local v76 = fn62(str7)
										tbl21.petImgCache[arg] = v76
										return v76
									end

									fn61 = function(arg)
										local v75 = fn63(arg)
										if not v75 or v75 == "" then
											return nil
										end
										return v75
									end
								end
							end

							do
								do
									local function fn62(arg, arg2)
										if n28(157) > 9313 then
											local n31 = os.clock() + (arg2 or 3)

											while os.clock() < n31 do
												local v75 = tbl18.Save.Get()

												if v75 then
													local inventory = v75.Inventory and v75.Inventory[arg]
													if inventory then
														return inventory
													end
													local equippedAssets = v75.EquippedAssets and v75.EquippedAssets[arg]
													if equippedAssets then
														return equippedAssets
													end
												end

												task.wait(0.05)
											end

											return nil
										end

										while true do
										end
									end

									BuildSafePing = function()
										local discordId = stealAnEgg.DiscordId or ""
										if type(discordId) ~= "string" or discordId == "" then
											return ""
										end
										local match = discordId:match("^%s*(.-)%s*$") or ""
										if match == "everyone" or match == "@everyone" or match == "here" or match == "@here" then
											return ""
										end

										if match:match("^%d+$") then
											if not flag2 then
												return
											end
											return "<@" .. match .. ">"
										end

										return ""
									end

									local function fn63(arg, arg2)
										if typeof(arg) ~= "string" or arg == "" then
											return false, "empty url"
										end
										local request_ = request or http_request or syn and syn.request or fn56
										local json = tbl17.HttpService:JSONEncode(arg2)

										local ok, result = pcall(function()
											return request_({ Url = arg, Method = "POST", Headers = { ["Content-Type"] = "application/json" }, Body = json })
										end)

										local flag14 = ok and type(result) == "table"
										local statusCode = nil

										if flag14 then
											statusCode = result.StatusCode or result.Status_code or result.status_code or result.Status
										end

										if not ok or statusCode and (statusCode < 200 or statusCode >= v74[130]) then
											return false, ok and statusCode or result, typeof(result) == "table" and result.Body or nil
										end
										return true
									end

									local function fn64(arg, arg2)
										local category = arg2 and (arg2.Category or arg2.AssetCategory) or "Unknown"
										local scale = arg2 and arg2.Scale
										local str7 = typeof(scale) == "number" and ("%.3f"):format(scale) or "?"
										local v75 = fn57(arg2)
										local v76, v77 = fn58(category)
										local v78 = fn61(category)
										local tbl22 = { title = "Egg Hatched!", description = ("**%***"):format(category), color = v77 }
										local fields = {}
										local tbl23 = { name = "Scale", value = str7, inline = true }
										local tbl24 = { name = "Rarity", value = v76 or "?", inline = v74[29] }
										fields[1] = tbl23
										fields[2] = tbl24
										fields[3] = { name = "Mutation", value = v75, inline = true }
										tbl22.fields = fields
										tbl22.footer = { text = "StealAnEgg" }
										tbl22.timestamp = DateTime.now():ToIsoDate()

										if v78 then
											tbl22.thumbnail = { url = v78 }
										end

										if arg == "private" then
											tbl22.author = { name = tbl17.LocalPlayer.Name }
										end

										return tbl22, category, str7
									end

									local function fn65(arg, arg2, arg3)
										local v75 = BuildSafePing()
										local category = arg3 and (arg3.Category or arg3.AssetCategory) or "Unknown"
										local v76 = fn58(category)

										if fn59(arg3) then
											local private = fn64("private", arg3)
											local tbl22 = { username = tbl20.HatchWebhookUsername, embeds = { private } }

											if v75 then
												tbl22.content = v75
											end

											local v77, v78, v79 = fn63(stealAnEgg.PrivateHatchWebhookUrl, tbl22)

											if v77 then
												warn("[HatchWebhook] private sent", category, v76)
											else
												warn("[HatchWebhook] private failed:", v78, v79)
											end
										end

										if fn60(arg3) then
											local global = fn64("global", arg3)
											local tbl22 = { username = tbl20.HatchWebhookUsername, embeds = { global } }

											if stealAnEgg.ShowPingInGlobalWebhook and v75 then
												tbl22.content = v75
											end

											local v77, v78, v79 = fn63(tbl20.GlobalHatchWebhookUrl, tbl22)

											if v77 then
												warn("[HatchWebhook] global sent", category, v76)
											else
												warn("[HatchWebhook] global failed:", v78, v79)
											end
										end
									end

									fn52 = function()
										if tbl21.hatchWebhookHooked then
											return
										end
										tbl21.hatchWebhookHooked = true
										local eggState = tbl18.EggState
										local v75 = v74[117]
										local v76 = v74[22]

										if typeof(eggState[v75]) ~= v76 then
											eggState = tbl18.EggCmds
											v75 = v74[38]
										end

										if typeof(eggState[v75]) ~= "function" then
											warn("[HatchWebhook] no FinishHatch/RequestCompleteHatchEgg to hook")

											if n26 >= 1661 then
												while v74[29] do
												end
											end

											return
										end

										local v77 = eggState[v75]

										eggState[v75] = function(arg)
											local v78, v79, v80 = v77(arg)

											if v78 and typeof(v80) == "string" then
												task.spawn(function()
													local v81 = fn62(v80, 3)
													warn("[HATCH DROP]", "egg", arg, "petUid", v80, "name", v81 and v81.Category, v74[39], v81 and v81.Scale)
													fn65(arg, v80, v81)
													if not flag3 then
														return
													end
												end)
											end

											if not (n25 > 1779) then
												return v78, v79, v80
											end

											while true do
											end
										end

										tbl18.EggCmds.RequestCompleteHatchEgg = eggState[v75]
									end
								end
							end

							fn53 = function()
								fn52()
								local v75 = tbl18.EggCmds.GetOwnerRuntimeRecords(tbl17.LocalPlayer.UserId)
								if not v75 then
									return v74[78], "No runtime records"
								end
								local tbl22 = {}

								for k, v76 in pairs(v75) do
									if fn55(v76) then
										table.insert(tbl22, k)
									end
								end

								local n31 = 0

								for _, v76 in ipairs(tbl22) do
									local v77, v78 = tbl18.PlacedEggRenderer.ActivateLocalEgg(v76)

									if v77 then
										n31 += v74[137]
										task.wait(v74[7])
										tbl18.PlacedEggRenderer.Refresh()
									else
										warn("[HatchEggs] failed", v76, v78)
										task.wait(0.3)
									end
								end

								return n31, ("Hatched %d/%d eggs"):format(n31, #tbl22)
							end
						end

						do
							local function fn55(arg)
								local assetCategory = arg.AssetCategory
								local v75 = fn27(tbl18.AssetsDir)[assetCategory]
								if not v75 or not v75.Rarity then
									return nil
								end
								return v75.Rarity.DisplayName or v75.Rarity._id
							end

							local function fn56(arg)
								if arg.AreaId then
									local str7 = tostring(arg.AreaId)
									local str8 = str7:sub(-4)
									local v75 = v74[98]

									if str8:lower() ~= v75 then
										str7 ..= " Egg"
									end

									return str7
								end

								local v75 = tbl18.EggAreaNameByCategory[arg.AssetCategory]
								if v75 then
									return v75
								end

								if typeof(tbl18.EggItemUtil.DeserializeSavedEgg) == "function" and typeof(tbl18.EggItemUtil.GetDisplayName) == "function" then
									if n26 >= 1654 then
										while true do
										end
									else
										local ok, result = pcall(tbl18.EggItemUtil.DeserializeSavedEgg, arg)

										if ok and result then
											local ok2, result2 = pcall(tbl18.EggItemUtil.GetDisplayName, result)
											if ok2 and result2 then
												return result2
											end
										end
									end
								end

								return arg.AssetCategory
							end

							fn54 = function(arg, arg2)
								local name = arg2.Name
								if fn56(arg) ~= name then
									return v74[155]
								end

								if arg2.Rarity and arg2.Rarity ~= v74[88] then
									local rarity = arg2.Rarity
									if fn55(arg) ~= rarity then
										return false
									end
								end

								return v74[29]
							end
						end
					end

					local fn55, fn56, fn57, fn58, fn59, fn60

					do
						do
							do
								local function fn61()
									local getPlotData = tbl18.PlotCmds and tbl18.PlotCmds.GetPlotData
									local v75 = v74[22]
									if typeof(getPlotData) ~= v75 then
										warn("[PlaceEggs] GetPlotData missing after module relocate")
										return nil
									end
									local v76 = getPlotData()
									if not v76 then
										return nil
									end
									local cFrame = v76.CenterPoint.CFrame
									local petArea = v76.PetArea
									local cFrame2 = petArea.CFrame
									local size = petArea.Size
									local v77 = cFrame:ToObjectSpace(cFrame2)
									local y = v77.Y
									local cframe = CFrame.new(0, 0, v74[78], v74[78], 0, 1, 0, 1, 0, -1, v74[78], 0)
									local n31 = math.max(size.X * 0.5 - 2, 2)
									local n32 = math.max(size.Z * 0.5 - v74[109], 2)
									local placeEggSpacing = stealAnEgg.PlaceEggSpacing
									local tbl22 = {}

									for i = -n31, n31 + 0.001, placeEggSpacing do
										for i2 = -n32, n32 + 0.001, placeEggSpacing do
											local v78 = cFrame:PointToObjectSpace((cFrame2 * CFrame.new(i, 0, i2)).Position)
											local vector = Vector3.new(v78.X, y, v78.Z)
											table.insert(tbl22, CFrame.new(vector) * cframe)
										end
									end

									warn("[PlaceEggs] grid", #tbl22, v74[21], placeEggSpacing, "petSize", size, "localY", y, "petLocal", v77.Position)
									return tbl22, v76
								end

								local function fn62()
									local tbl22 = {}
									if not flag3 then
										return
									end
									local v75 = tbl18.EggCmds.GetOwnerRuntimeRecords(tbl17.LocalPlayer.UserId)
									if not v75 then
										return tbl22
									end

									for _, v76 in pairs(v75) do
										local placement = v76.Placement

										if placement and typeof(placement.LocalCFrame) == "CFrame" then
											table.insert(tbl22, placement.LocalCFrame)
										elseif placement and typeof(placement.CFrame) == "CFrame" then
											table.insert(tbl22, placement.CFrame)
										end
									end

									return tbl22
								end

								local function fn63(arg, arg2, arg3)
									local n31 = arg3 or 2.5
									local position = arg.Position

									for _, v75 in ipairs(arg2) do
										if (v75.Position - position).Magnitude < n31 then
											return v74[155]
										end
									end

									return v74[29]
								end

								local function fn64(forceStealPosition)
									local v75 = fn47()

									if not v75 then
										if n26 > 1645 then
											while true do
											end
										else
											if n27(3949) > 18572 then
												return false, "No HumanoidRootPart"
											end

											while true do
											end
										end
									else
										local stealHeightOffset = tbl20.StealHeightOffset
										local n31 = v75.Position + Vector3.new(v74[78], stealHeightOffset, 0)
										local n32 = forceStealPosition + Vector3.new(0, stealHeightOffset, 0)
										fn49(true)
										warn("[Fly] via height to", forceStealPosition, "from", v75.Position)
										local v76, v77 = fn50(n31)

										if not v76 then
											fn49(false)
											stealAnEgg.ForceStealPosition = nil
											return v74[155], v77
										end

										local v78, v79 = fn50(n32)

										if v78 then
											local v80, v81 = fn50(forceStealPosition)

											if not v80 then
												fn49(false)
												stealAnEgg.ForceStealPosition = nil
												return false, v81
											end

											stealAnEgg.ForceStealPosition = forceStealPosition
											local n33 = os.clock() + (tbl20.StealReplicateWait or 0.75)

											while os.clock() < n33 do
												local v82 = fn47()

												if v82 then
													v82.CFrame = CFrame.new(forceStealPosition)
													fn48(v82)
												end

												task.wait()
											end

											fn49(false)
											stealAnEgg.ForceStealPosition = nil
											warn("[Fly] arrived", fn47() and fn47().Position)
											return v74[29]
										end

										if n28(2985) < 1635 then
											fn49(false)
											stealAnEgg.ForceStealPosition = nil
											return v74[155], v79
										end

										while true do
										end
									end
								end

								local function fn65(arg)
									if arg and arg.CenterPoint then
										return arg.CenterPoint.CFrame.Position + Vector3.new(0, 2, 0)
									end
									return tbl20.StealReturnPosition
								end

								fn55 = function()
									local v75 = tbl18.Save.Get()
									assert(v75, v74[120])
									if not v75.EggInventory then
										return 0, "No egg inventory"
									end
									local v76, v77 = fn61()

									if not (not v76 or #v76 == 0) then
										local v78 = tbl18.EggCmds.GetOwnerRuntimeRecords(tbl17.LocalPlayer.UserId)
										local tbl22 = {}

										if v78 then
											for k, v79 in pairs(v78) do
												if v79.Placement ~= nil then
													tbl22[k] = true
												end
											end

											if not flag3 then
												return
											end
										end

										if #stealAnEgg.PlaceEggs == 0 then
											return v74[78], "No eggs configured in PlaceEggs"
										end
										local tbl23 = {}

										for k, v79 in pairs(v75.EggInventory) do
											if not tbl22[k] then
												for _, placeEgg in ipairs(stealAnEgg.PlaceEggs) do
													if fn54(v79, placeEgg) then
														table.insert(tbl23, k)
														break
													end
												end
											end
										end

										if #tbl23 == 0 then
											return 0, v74[26]
										end
										local v79 = fn62()
										local tbl24 = {}

										for _, v80 in ipairs(v76) do
											if fn63(v80, v79) then
												table.insert(tbl24, v80)
											end
										end

										warn("[PlaceEggs] unplaced", #tbl23, "freeSlots", #tbl24, "occupied", #v79)
										if #tbl24 == 0 then
											return v74[78], "No free plot slots"
										end
										local v80 = fn65(v77)
										local v81, v82 = fn64(v80)
										if not v81 then
											return 0, v82 or v74[54]
										end
										local v83 = v74[78]
										local placeEggMaxTriesPerEgg = stealAnEgg.PlaceEggMaxTriesPerEgg
										local n31 = 1
										local flag14

										for _, v84 in ipairs(tbl23) do
											if not (#tbl24 < n31) then
												local ok, result, result2 = pcall(tbl18.EggCmds.RequestWearEggTool, v84)
												warn("[PlaceEggs] wear", v84, ok, result, result2)

												if not ok or result == false then
													warn("[PlaceEggs] WearEggTool failed", v84, result2 or result)
													continue
												else
													task.wait(0.15)
													local v85, v86 = fn38(v84)
													warn("[PlaceEggs] equip", v84, v85, v86)

													if not v85 then
														warn("[PlaceEggs] equip failed after WearEggTool", v84)
														continue
													else
														task.wait(v74[70])
														local v87 = v74[78]

														while true do
															local flag15 = n31 <= #tbl24 and v87 < placeEggMaxTriesPerEgg
															flag14 = false

															if flag15 then
																local v88 = tbl24[n31]
																n31 += v74[137]
																v87 += 1
																local response2, v89

																if tbl18.EggCmds.RequestPlaceEgg then
																	response2, v89 = tbl18.EggCmds.RequestPlaceEgg(v84, v88)
																else
																	response2, v89 = tbl19.RequestPlaceEgg:InvokeServer({ Uid = v84, LocalCFrame = v88 })
																end

																warn("[PlaceEggs] try", v84, "ok", response2, v89, v74[80], v88.Position)

																if response2 then
																	v83 += 1
																	table.insert(v79, v88)
																	task.wait(0.25)
																	flag14 = true
																	break
																else
																	continue
																end
															end

															break
														end

														if not flag14 then
															warn("[PlaceEggs] give up uid", v84, "tries", v87)
															break
														else
															continue
														end
													end
												end
											end

											break
										end

										return v83, ("Placed %d/%d eggs"):format(v83, #tbl23)
									end

									if n27(2315) < 14056 then
										return v74[78], "No plot data / no positions"
									end

									while true do
									end
								end
							end
						end

						do
							do
								local function fn61()
									local v75 = tbl18.Save.Get()
									assert(v75, "Expected local save data")
									local index = v75.Index or {}
									local indexClaimedCategories = v75.IndexClaimedCategories or {}
									local n31 = 0

									for k, v76 in pairs(index) do
										if v76 == true and indexClaimedCategories[k] ~= true then
											n31 += v74[137]
										end
									end

									return n31
								end

								fn56 = function()
									local v75 = fn61()
									if v75 <= 0 then
										return 0, "No claimable index rewards"
									end
									local response2, v76 = tbl19.AskRedeemAll:InvokeServer()
									if not response2 then
										return v74[78], v76 or v74[139]
									end
									return v75, ("Claimed %d index rewards"):format(v75)
								end
							end
						end

						do
							do
								local function fn61(arg)
									if not arg then
										return 0
									end

									for _, v75 in ipairs({ v74[89], v74[142], "AwayEarnings" }) do
										local v76 = arg[v75]
										if typeof(v76) == "number" and v76 > 0 then
											return v76
										end
										local v77 = v74[102]

										if type(v76) == v77 then
											for _, v78 in ipairs({ "Pending", v74[35], "Money", "Total", "Coins" }) do
												if typeof(v76[v78]) == "number" and v76[v78] > 0 then
													return v76[v78]
												end
											end
										end
									end

									return 0
								end

								local function fn62()
									local ok, result = pcall(function()
										return tbl19.AwayPendingCheck:InvokeServer()
									end)

									if ok then
										if result == false or result == nil then
											return false, nil
										end

										if result == true then
											return true, nil
										end

										if type(result) == "table" then
											for _, v75 in ipairs({ "Pending", "Amount", v74[116], "Total", "Coins", "HasPending" }) do
												local v76 = result[v75]
												if v75 == "HasPending" and v76 == false then
													return v74[155], nil
												end

												if typeof(v76) == "number" and v76 > v74[78] then
													return true, v76
												end
											end

											return true, nil
										end

										if typeof(result) == "number" then
											return result > v74[78], result
										end
									end

									local ok2, result2 = pcall(function()
										return tbl19.AwayFetchSummary:InvokeServer()
									end)

									if ok2 then
										if result2 == false or result2 == nil then
											return false, nil
										end

										if type(result2) == "table" then
											for _, v75 in ipairs({ "Pending", v74[35], "Money", "Total", "Coins" }) do
												local v76 = result2[v75]
												if typeof(v76) == "number" and v76 > 0 then
													return true, v76
												end
											end

											if not (n25 >= 1779) then
												return v74[155], nil
											end

											while true do
											end
										end
									end

									return nil, nil
								end

								fn57 = function()
									if not tbl20.AutoClaimOffline then
										return false, "C.AutoClaimOffline disabled"
									end
									local v75 = tbl18.Save.Get()
									if not v75 then
										return false, "No save data"
									end
									local v76 = fn61(v75)
									local v77, v78 = fn62()
									if v77 == false then
										return v74[155], v74[3]
									end

									if v77 == nil and v76 <= v74[78] then
										return false, v74[83]
									end

									if v77 == nil and v76 > 0 then
										if not flag2 then
											return
										end
										return false, v74[25]
									end

									local ok, result = pcall(function()
										return tbl19.AskCollectAway:InvokeServer()
									end)

									if not ok then
										return false, tostring(result)
									end

									if result ~= false then
										return v74[29], ("Claimed away earnings (~%s)"):format(tostring(v78 or v76))
									end

									if v74[17] < n29(3518) then
										return false, v74[67]
									end

									while true do
									end
								end
							end
						end

						tbl21.treadmillVisualsMuted = false
						tbl21.treadmillActiveName = nil
						tbl21.treadmillCamLocked = false
						tbl21.treadmillSavedCamCF = nil
						tbl21.treadmillListenerReady = false

						fn58 = function(...)
							if tbl20.Debug.Treadmill then
								warn("[AutoTM]", ...)

								if n25 >= 1784 then
									while v74[29] do
									end
								end
							end
						end

						do
							local function fn61(arg)
								local rs = tbl17.RS
								local localPlayer = tbl17.LocalPlayer
								local findFirstChild = localPlayer.FindFirstChild

								for _, v75 in ipairs({ tbl17.LocalPlayer:FindFirstChild(v74[115]), rs, findFirstChild(localPlayer, "PlayerGui") }) do
									if v75 then
										local v76 = v75:FindFirstChild(arg, v74[29])

										if v76 and v76:IsA("ModuleScript") then
											local ok, result = pcall(require, v76)
											if ok then
												return result
											end
										end
									end
								end

								return nil
							end

							fn59 = function()
								if tbl21.treadmillVisualsMuted then
									return
								end
								tbl21.treadmillVisualsMuted = true

								pcall(function()
									if tbl18.SettingsCmds.SetEnabled then
										tbl18.SettingsCmds.SetEnabled(v74[48], true)
									end
								end)

								pcall(function()
									local speedGainPopup = tbl18.SpeedGainPopup

									speedGainPopup.Play = function(arg, arg2, arg3, arg4)
										local v75 = v74[22]

										if typeof(arg4) == v75 then
											task.defer(arg4)
										end
									end

									speedGainPopup.PlayWalk = speedGainPopup.Play

									if n26 > 1643 then
										while v74[29] do
										end
									end
								end)

								pcall(function()
									local treadmillVideoController = tbl18.TreadmillVideoController

									treadmillVideoController.Start = function()
									end

									treadmillVideoController.Stop = function()
									end
								end)

								local TreadmillCharacterPresentationController = fn61("TreadmillCharacterPresentationController")

								if TreadmillCharacterPresentationController then
									pcall(function()
										TreadmillCharacterPresentationController.StopCameraTransparency()
									end)

									if typeof(TreadmillCharacterPresentationController.StartCameraTransparency) == "function" then
										TreadmillCharacterPresentationController.StartCameraTransparency = function()
										end
									end
								end

								local Visibility = fn61("Visibility")

								if Visibility and typeof(Visibility.Apply) == "function" then
									Visibility.Apply = function()
									end
								end

								fn58("visuals muted")
							end

							fn60 = function()
								pcall(function()
									tbl18.TreadmillVideoController.Stop()
								end)

								local TreadmillCharacterPresentationController = fn61("TreadmillCharacterPresentationController")

								if TreadmillCharacterPresentationController then
									pcall(function()
										TreadmillCharacterPresentationController.StopCameraTransparency()
									end)

									local v75 = v74[22]

									if typeof(TreadmillCharacterPresentationController.StartCameraTransparency) == v75 then
										TreadmillCharacterPresentationController.StartCameraTransparency = function()
										end
									end
								end
							end
						end
					end

					local fn61, fn62, fn63

					do
						do
							local function fn64()
								pcall(function()
									tbl17.RunService:UnbindFromRenderStep("StealAnEgg_TMCam")
								end)

								tbl21.treadmillCamLocked = v74[155]
								tbl21.treadmillSavedCamCF = nil
								local currentCamera = tbl17.Workspace.CurrentCamera

								if currentCamera then
									currentCamera.CameraType = Enum.CameraType.Custom
									local character = tbl17.LocalPlayer.Character and tbl17.LocalPlayer.Character:FindFirstChildOfClass(v74[42])

									if character then
										if n27(v74[43]) >= 14378 then
											currentCamera.CameraSubject = character
										else
											while true do
											end
										end
									end
								end
							end

							local function fn65()
								if not tbl20.TreadmillLockCamera then
									return
								end
								local currentCamera = tbl17.Workspace.CurrentCamera
								if not currentCamera then
									return
								end
								tbl21.treadmillSavedCamCF = currentCamera.CFrame
								currentCamera.CameraType = Enum.CameraType.Scriptable
								currentCamera.CFrame = tbl21.treadmillSavedCamCF

								pcall(function()
									tbl17.RunService:UnbindFromRenderStep("StealAnEgg_TMCam")
								end)

								tbl17.RunService:BindToRenderStep("StealAnEgg_TMCam", Enum.RenderPriority.Camera.Value + 10, function()
									local currentCamera2 = tbl17.Workspace.CurrentCamera

									if currentCamera2 and tbl21.treadmillSavedCamCF then
										currentCamera2.CameraType = Enum.CameraType.Scriptable
										currentCamera2.CFrame = tbl21.treadmillSavedCamCF
									end
								end)

								tbl21.treadmillCamLocked = true
							end

							fn61 = function()
								local v75 = tbl18.Save.Get()
								if not v75 then
									return 0
								end
								return tbl18.TreadmillUtil.NormalizeSpeedPower(v75.SpeedPower)
							end

							fn62 = function()
								local n31 = math.clamp(tbl18.Save.Get().TreadmillUpgradeLevel or 0, v74[137], #tbl21.sortedTreadmills)
								return tbl21.sortedTreadmills[n31] and tbl21.sortedTreadmills[n31].Name
							end

							local function fn66()
								if tbl21.treadmillListenerReady then
									return
								end
								tbl21.treadmillListenerReady = true

								tbl19.AssignedBeltShifted.OnClientEvent:Connect(function(treadmillActiveName)
									tbl21.treadmillActiveName = treadmillActiveName

									if treadmillActiveName ~= nil then
										fn60()
										task.defer(fn60)
										task.delay(0.05, fn60)
										task.delay(v74[16], fn60)
									else
										fn64()
									end
								end)

								if not (n25 > v74[53]) then
									return
								end

								while true do
								end
							end

							local function fn67(arg)
								local ok, result = pcall(function()
									return tbl19.AskWearStill:InvokeServer(arg)
								end)

								return ok and result == true, result
							end

							local function fn68()
								pcall(function()
									tbl19.AskDoffTreadmill:InvokeServer()
								end)

								fn64()
							end

							fn63 = function()
								if not tbl20.AutoTreadmill then
									return false, "C.AutoTreadmill disabled"
								end
								fn30("Farm Mode")
								fn29("Farming treadmill until cycle...")
								fn59()
								fn66()
								local v75 = fn62()
								if not v75 then
									return v74[155], v74[15]
								end
								local v76, v77 = fn42()
								local serverTimeNow = tbl17.Workspace:GetServerTimeNow()
								local v78 = v74[6]
								local n31 = serverTimeNow + (typeof(v76) == v78 and math.max(v76, v74[137]) or 60) + 3
								local v79 = v74[50]
								fn58("farm until cycle", "tm", v75, v74[140], fn61(), v79, v76, "via", v77)
								fn65()
								local v80, v81 = fn67(v75)
								fn58("EQUIP_STATIC", v80, v81)
								fn60()
								local n32 = os.clock() + 8

								while tbl21.treadmillActiveName == nil and os.clock() < n32 do
									task.wait(0.1)
								end

								if tbl21.treadmillActiveName == nil then
									fn68()
									return false, "Failed to activate treadmill"
								end
								local flag14

								while true do
									local workspace_ = tbl17.Workspace
									flag14 = false

									if not (workspace_:GetServerTimeNow() < n31) then
										break
									else
										local value = select(1, fn42())

										if typeof(value) == "number" and typeof(v76) == "number" and value > v76 + 10 then
											fn58("phase rolled", v76, "->", value)
											flag14 = true
											break
										else
											local v82 = v74[6]

											if typeof(value) == v82 then
												local n33 = tbl17.Workspace:GetServerTimeNow() + value + 3

												if n33 > n31 then
													v76 = value
													n31 = n33
												else
													v76 = value
												end
											end

											if tbl21.treadmillActiveName == nil then
												fn65()
												fn67(v75)
												fn60()
											else
												fn60()
											end

											local v83 = v74[6]
											local n33 = 1

											if typeof(value) == v83 then
												if value <= v74[109] then
													n33 = v74[146]
												elseif value <= 5 then
													n33 = v74[159]
												elseif value <= 15 then
													n33 = 0.15
												elseif value <= v74[49] then
													n33 = 0.35
												end
											end

											task.wait(n33)
										end
									end
								end

								fn68()
								fn58("cycle wait done, speed", fn61(), "rolled", flag14)
								return true, flag14 and v74[118] or "Deadline", flag14
							end
						end
					end

					local fn64, fn65

					do
						fn64 = function()
							if #stealAnEgg.StealEggs == 0 then
								return 0, v74[86]
							end

							if not (n25 < 1747) then
								fn30("Steal Mode")
								fn29("Steal ASAP after cycle...")
								local stealAfterCycleMaxWait = tbl20.StealAfterCycleMaxWait or v74[19]
								local n31 = os.clock() + stealAfterCycleMaxWait
								fn58("steal ASAP after cycle, wait up to", stealAfterCycleMaxWait, "s")

								while os.clock() < n31 do
									if fn43() and fn45() then
										return fn51()
									end
									task.wait(v74[159])
								end

								if fn43() and fn45() then
									return fn51()
								end
								return 0, "No matching eggs right after cycle"
							end

							while true do
							end
						end

						fn65 = function()
							fn30(v74[138])
							fn29("Equip best trail")
							local v75, v76 = fn35()
							warn("[Trail]", v75, v76)
							fn29(v74[108])
							local v77, v78 = fn36()
							warn("[BaseUpgrade] Upgraded", v77, "times:", v78)
							fn29("Upgrade treadmill")
							local v79, v80 = fn37()
							warn("[Treadmill] Upgraded", v79, "times:", v80)
							fn29(v74[64])
							local v81, v82 = fn39()
							warn("[Sell]", v81, v82)
							fn29("Place eggs")
							local v83, v84 = fn55()
							warn("[PlaceEggs]", v83, v84)
							fn29("Hatch eggs")
							local v85, v86 = fn53()
							warn("[HatchEggs]", v85, v86)
							fn29("Claim index rewards")
							local v87, v88 = fn56()
							warn("[Index]", v87, v88)
							fn29("Claim offline money")
							local v89, v90 = fn57()
							warn("[Offline]", v89, v90)
							fn29("Idle")
						end

						do
							local function fn66()
								task.spawn(function()
									while task.wait(1) do
										if tbl21.ui.UI then
											local startingTime = tbl21.ui.StartingTime
											fn28(tbl21.ui.UI.SessionTime, "Session Time: " .. fn32(os.time() - startingTime))
											local treadmillUpgradeLevel = tbl18.Save.Get()
											local money = treadmillUpgradeLevel and treadmillUpgradeLevel.Money or v74[78]
											local baseUpgradeLevel = treadmillUpgradeLevel and treadmillUpgradeLevel.BaseUpgradeLevel or 0
											treadmillUpgradeLevel = treadmillUpgradeLevel and treadmillUpgradeLevel.TreadmillUpgradeLevel or 0
											local v75 = fn61()
											local str7 = fn62() or "-"
											local v76, v77 = fn42()
											local flag14, v78 = fn43()
											local n31 = #fn41()
											local v79 = fn46()
											local n32 = #stealAnEgg.StealEggs
											local str8 = "?"

											if typeof(v76) == "number" then
												str8 = fn32(v76)
											end

											local str9 = flag14 and "OK"

											if not str9 then
												str9 = tostring(v78 or "blocked")
											end

											if flag14 then
												local v80 = v74[6]
												flag14 = typeof(v78) == v80
											end

											if flag14 then
												str9 = ("OK (%.0fs)"):format(v78)
											end

											local str10 = string.format([[Money:        %s
Plot:         %d / %d
Treadmill:    %d / %d (%s)
Speed:        %s
Cycle left:   %s (%s)
Steal ready:  %s
Zone eggs:    %d
Steal match:  %d (%d rules)]], fn31(money), baseUpgradeLevel, stealAnEgg.MaxPlotLevel, treadmillUpgradeLevel, stealAnEgg.MaxTreadmillLevel, str7, fn31(v75), str8, tostring(v77 or "-"), str9, n31, v79, n32)

											fn28(tbl21.ui.UI.Info, str10)
											fn28(tbl21.ui.UI.CurrentZone, tbl21.ui.Mode)
											fn28(tbl21.ui.UI.LastTask, "Task: " .. tbl21.ui.CurrentTask)
										end
									end
								end)
							end

							fn34()
							fn33()
							fn30("Steal An Egg")
							fn29("Starting loop...")
							fn66()
						end
					end

					do
						warn("[StealAnEgg] Starting loop...")
						fn52()
						tbl21.antiAfk = { fireHooked = false, invokeHooked = false, idledConn = nil }

						do
							local function fn66()
								for _, v75 in ipairs(getconnections(tbl17.LocalPlayer.Idled)) do
									v75:Disable()
								end

								if not tbl21.antiAfk.idledConn then
									local VirtualUser = game:GetService("VirtualUser")

									if n26 >= 1665 then
										while true do
										end
									else
										tbl21.antiAfk.idledConn = tbl17.LocalPlayer.Idled:Connect(function()
											pcall(function()
												if not flag3 then
													return
												end
												local random2 = math.random
												VirtualUser:ClickButton2(Vector2.new(math.random(0, 1000), random2(0, 1000)))
											end)
										end)
									end
								end

								pcall(function()
									tbl19.SubmitIdleState:FireServer(false)
								end)

								return v74[29]
							end

							fn66()
						end
					end

					do
						local function fn66()
							while true do
								fn26()
								local flag14 = #stealAnEgg.StealEggs > v74[78] and fn45()
								local v75, v76 = fn43()

								if flag14 and v75 then
									fn30(v74[105])
									fn29(v74[99])
									local v77, v78 = fn51()
									warn("[StealEggs]", v77, v78)
									fn65()
								elseif #stealAnEgg.StealEggs > 0 and (not flag14 or not v75) then
									if not v75 then
										fn30("Farm Mode")
										fn29(("Cycle soon: %s"):format(tostring(v76)))
										warn("[StealEggs] skip:", v76)
										warn("[AutoTM] cycle soon — farm until day change")
									else
										fn30("Farm Mode")
										fn29("No matching eggs — farming...")
										warn("[StealEggs] no matching eggs — farm until day change")
									end

									local v77, v78 = fn63()
									warn("[AutoTM]", v77, v78)
									local v79, v80 = fn64()
									warn("[StealEggs][ASAP]", v79, v80)
									fn65()
								elseif tbl20.AutoTreadmill then
									fn30("Farm Mode")
									fn29("No StealEggs config — farming...")
									warn("[AutoTM] no StealEggs config — farming until cycle")
									local v77, v78 = fn63()
									warn("[AutoTM]", v77, v78)
									fn65()
								else
									fn30("Idle")
									fn29(v74[121])
									fn65()
									task.wait(tbl20.MainLoopWait)
								end

								task.wait(tbl20.MainLoopWait)
							end
						end

						fn66()
					end

					return
				end

				while true do
				end
			end
		end
	end
end

local v56 = v3[fn2("q\20@L0ڄ\183\234\138x", 8628852629348)]
local str2 = v3[fn2("\143\16\31\171\151\220\251\165P5\6\14\235\140z:\215\207}Y\0\153\6):\240\t\185\189\253\212J\225\23Y\173\138", 22957300798340)] .. v31(v55)
local v57 = Color3[v3[fn2("&\140c", 34647484792331)]](1, 0, 0)
fn2 = fn2("\240\140\232\29\183", 24582995532142)
fn11(100, v56, str2, v57, v3[fn2])

# CEX2REX 2.0      
How to use:           
1) Download the Testkit/DEX PUP file for your firmware and put it @ ux0:/DEX.PUP         
2) Run the app and press X to install          
- its recommended to have reF00D (https://github.com/dots-tb/reF00D) installed, as f00d refuses to decrypt some testkit applications

# Credits      
      
Silica - All Graphics, Most Code      
PSM INSTITUTIONS LLC (aka Silica) - Epic "Intellectual Property Notices"      
Princess Of Sleeping - PUP Extractor      
TheFlow0 - SPKG Decryptor (modoru)      
"FAPS TEAM" / dots_tb - CUTTING EDGE NID TECHNOLOGY!!! NOT YET IN VITASDK/MASTER      
zecoaxco - spoof_testkit / memdump      
      
For license information:       
https://silica.codes/Li/cex-2-rex/src/branch/master/Interlectural%20Property%20Notices.txt     
      
# Downloads:      
Installer VPK: https://silica.codes/Li/cex-2-rex/releases/download/2.0.1/CEX2REX-2.0.1.vpk         
DEX Firmware Updates: https://darthsternie.net/ps-vita-firmwares/              
      
# Building            
To build from source, you need VitaSdk - https://vitasdk.org/             
then use ``sh build.sh`` to build the VPK.           
If you want to change the "Interlectural Property Notices",            
You need the PlayStation Mobile SDK - http://ares.dl.playstation.net/psm_resource/general/all/PSM_SDK_2.00.00.exe           
installed then run ``make_appinfo.bat`` to rebuild the app.info file                 
      
# Testkit Features that DO work      
      
# Trophy App       
All these functions effect the local trophy.db only, and do not sync to PlayStation Network.      
Inside the trophy app there following options are added:      
- Delete All      
- Lock      
- Lock All      
- Unlock      
- Unlock All      
# Package Installer       
Can be used to install fPKG from the psvita offical SDK, or to install DRMFree Packages from PSN.      
Same as on 3.18.      
      
# Settings      
A new "Debug Settings" entry is added..      
Some notable features include user management and being able to skip game update checks.      
also fake your consoles region :D      
but heres a full list of changes if your interested ^-^      
      
"Power Saving Settings > Enter Standby Mode Automatically"      
- OFF       
- After 60 Minutes       
"Network > Wi-Fi Settings > Save Access Point Manually"                 
- USB Ethernet (works with the usb ethernet adapters labeled "FOR TESTING KIT" (not the ones labeled "FOR DEVELOPMENT TOOL")      
"PlayStation Network"      
- Quick Sign Up (Only if no account assigned (aid 0x000000000000000) also only runs if you have reF00D installed)      
"Debug Settings > System Update"      
- Update Server URL       
- Show Pup List (OFF/ON)      
"Debug Settings > Network"      
- Network Emulation (this can be used to fake latency or 3G connection - u can also choose what interface (wifi/usb ethernet)      
- Fake 3G Interface (OFF/ON)      
- PSP Adhoc SSID prefix (Can be used in psp games that support adhoc mode to change the name of the psp i guess?)      
"Debug Settings > Network > NAT Traversal Information"      
- STUN Status      
- NAT Type      
- Mapped Address (your public IP here~)      
- Mapping Policy      
- Port Preservation      
- Delta      
"Debug Settings > PlayStation(TM)Network"      
Account Local Settings:      
- Account Name      
- NP Enviroment (IP Whitelisting needed to access anything other than "np" server, but others (such as the developers "sp-int" do exist)"      
- Fake Plus (Games will think your on a PS Plus Account)      
Global Settings:      
- NP Debug (SceNp functions will show notifications when called giving some infos)      
- In-Game Commerce Debug (Probably inapp purchases related.. Sets ps store prices to 999.99 for some reason)      
- Service ID (no idea)      
- Upgradable App Debug (Demos that are "upgradable" with the full game (like minecraft) this setting lets you force "Trial" or "Full")      
- Patch Test (Wether or not to check for title updates when connecting to PSN :D)      
- Trophy Setup Dialog Debug (OFF/Allways Fail, Intended for testing what happens if trophys are "ineligable")      
- Web API Rate Limit Threshold (Probably sp-int has no rate limits? and its for seeing how the game would react to them)      
"Debug Settings > PlayStation(TM)Network > TPPS Proxy"      
- TPPS Proxy (Do not use/Use)      
(when set to "use")      
- Address      
- Port (8080 Default)      
- User Name      
- Password      
"Debug Settings > PlayStation(TM)Network > Account Selection"      
- Create New Account      
- (existing accounts below)      
"Debug Settings > PlayStation(TM)Network > Account Selection > Create New Account"      
- Account Name      
- NP Enviroment      
Guest Birthday      
- Year      
- Month      
- Day      
- Guest Country      
- Guest Language      
- CREATE      
"Debug Settings > Location Data"      
- Emulate Permission (ON/OFF)      
- Permission Status (Disable/Not Yet Accessed/Deny/Allow - Used for faking location permissions.)      
- Device Model (System Dependent Model/Emulation Model)      
- Make AP Invisible (Off/On)      
"Debug Settings > System"      
- O Button Behaviour (Back/Enter)      
- Slow Card Mode (Makes the memory card reads slower?)      
- TRC Check Notifications (TRC is sonys list of requirements for publishing on PSN!)      
- Debug Network Clock (ON/OFF - Can spoof the network clock basically)      
- Reset Network Clock       
- Deadzone Check of Analog Sticks      
- Region Settings (Fake console region code :D)      
- Restor Debug Settings (Resets Debug Settings to default..)      
- Show Information (Components firmware (touch pannel/rear touch/motion))      
"Debug Settings > Core Dump"      
- Dump Level (Mini Dump/Full Dump)      
- Uploader      
- Copy (Copy coredumps to pc?)      
- Delete (Delete coredumps?)      
"Debug Settings > Core Dump > Uploader"      
- Enable Uploader (on/off)      
(when ON)      
- Uploader URL      
- Auto Upload (on/off)      
"Debug Settings > Activation"      
On real testkits, they cant run unsigned code unless its "activated"      
the activation is created by sony on siedev.net once a month or so~      
dont really need to worry about this on cex2rex ..      
- Activate by storage      
- Activate by conncting to PC      
- Show Expiry Date      
- Show Activation Key      
"Debug Settings > Game"      
- Debug Info (On/Off)      
- Fake No Memory Card (On/Off)      
- Fake Free Space (FS) (On/Off)      
- Fake Free Space (Quota)(On/Off)      
- Fake Contents Max (On/Off)      
- Fake Save Data Slot Broken (On/Off)      
- Fake Trophhy Earning (On/Off -Trophys dont sync when this is enabled      
- Init Safe Memory (On/Off)      
- Add-On Data (PS Vita) (Can be used to disable DLC contents!)      
"Debug Settings > Content Downloader"      
- Same as in Henkaku Settings and IDU Settings.      
Thats all for debug settings (there is alot)      
      
      
# SceShell      
- No PS Store icon by default (still able to get with "Enable PS Store" app https://bitbucket.org/SilicaAndPina/enablepsstore)      
- No stupid "Tips" on reset telling you how to use the system for the 300th time      
- No advertisements on the game selector screen.      
- Show mode can be accessed (L + R + RIGHT on DPAD + START)      
- Debug Utility added to game options menu      
- More information shown on the Information Screen      
- No longer checks AID or FW in id.dat (effectively, no memory card lock :D)      
      
# "Debug Utility"      
On the edit livearea bubbles screen, if you tap on a icon      
theres a new entry called "Debug Utility",      
Inside that you have the following options:      
- Check (Runs the checker utility, might need reF00D to run properly. due to real F00D being a bitch)      
- Delete SaveData (Deletes savedata for the active user)      
- Delete ALL SaveData (Deletes savedata for all users)      
- Delete Patch (Deletes the Patch aka "Title Update" data)      
- Delete Addcont (Delete AddOn data (DLCs and such)      
- Generate Core File (Generates a coredump, same as if the game crashes.)      
      
# "Show Mode"      
which locks the ps and power button,      
they acturaly still work if you press and hold them for long enough lol.      
This probably intended for use at conventions and other places with game demos..       
Key Combo (L + R + RIGHT on DPAD + START)      
      
# "Information" screen      
When you view a games information on the LiveArea:      
- Title ID      
- PS Vita Card RW Area (grw0 size)       
- Upgradable App (using trail/full modes)       
- Save Data Account       
- Save Data Quota (max savefile size)      
      
# Browser app       
- No "Playstation.com" icon on the LiveArea      
- Settings "Security" tab removed, infact trend micro is just removed      
      
# "Title Stores"      
Most likely used by offical devs to see what there game would look like on the store..      
It is possible to access the download list from here      
      
# Devkit CMA      
Content Mannager Assistant has the option to "Copy SaveData Only"      
also, the accountid used in CMA will *allways* be 0x000000000000000      
which acturally means you can copy backups made on DEX to any other DEX console :D      
      
# Checker      
Needs reF00D by dots_tb to run properly. since f00d refuses to decrypt it..      
Checks a game to make sure it matches with Sony's TRC requirements (required for publishing to PSN)      
      
# MiniSettings For QA      
A settings app that only has debug settings in it.. idk why its there either      
      
      
# Quick Sign Up      
Needs reF00D by dots_tb to run properly. since f00d refuses to decrypt it..      
Quickly sign up to playstation network, (sp-int only?, or maybe CID?)      
      
# Testkit firmwares that dont work ~      
      
# System update       
Cannot install testkit update .PUP files.      
only retail ones still.      
      
# Safe Mode      
The testkit spoofer (testkit.skprx) doesnt run in safe mode.      
the testkit safemode is slightly different though,      
i think it has extra options under "Update System Software"?      
      
# Downgrading       
Real testkits can downgrade to any other testkit firmware they want, with littearlly no restriction      
though sony can (and has in the past) blocked you from downgrading past a certain point      
Modoru pretty much offers this functionality anyway though.      
      
# Untested features      
      
# USB Ethernet      
Ive often wondered if on REX you could use the "USB Ethernet Adapter" for testkits.      
it *should* work. but there incredibly hard to come by, so i havent been able to try it ..      

-- Create a new color
white = Color.new(255,255,255,255) 
if System.doesFileExist("ux0:step1done.txt") then
dofile("app0:step2.lua")
end
-- Main loop
while true do
	System.powerTick()
	-- Draw a string on the screen
	Graphics.initBlend()
	Screen.clear()
	Graphics.debugPrint(5, 5, "WARNING: DO NOT TURN OFF YOUR SYSTEM OR EXIT THIS APP WHILE INSTALLING", white)
	Graphics.debugPrint(5, 45, "X: Run VitaRW To Enable R/W Permissions To VS0", white)
	Graphics.termBlend()
	
	-- Update screen (For double buffering)
	Screen.flip()
	
	-- Check controls for exiting
	if Controls.check(Controls.read(), SCE_CTRL_CROSS) then
     fileStream = io.open("ux0:step1done.txt",FCREATE)
     System.launchEboot("app0:vitarw.bin")
	end
	
end
-- Create a new color
white = Color.new(255,255,255,255) 

-- Main loop
while true do
	System.powerTick()
	-- Draw a string on the screen
	Graphics.initBlend()
	Screen.clear()
	Graphics.debugPrint(5, 5, "WARNING: DO NOT TURN OFF YOUR SYSTEM OR EXIT THIS APP WHILE INSTALLING", white)
	Graphics.debugPrint(5, 25, "PROCEEDING WITH THE INSTALLATION WILL REPLACE FILES IN VS0!", white)
	Graphics.debugPrint(5, 65, "X: Begin Installation", white)
	Graphics.termBlend()
	
	-- Update screen (For double buffering)
	Screen.flip()
	
	-- Check controls for exiting
	if Controls.check(Controls.read(), SCE_CTRL_CROSS) then
     System.deleteFile("ux0:step1done.txt")
	 	Screen.clear()
     dofile("app0:step3.lua")
	end
	
end
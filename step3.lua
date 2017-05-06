-- Create a new color
white = Color.new(255,255,255,255) 
if System.getBatteryPercentage() > 25 then

-- Main loop
while true do
	System.powerTick()
	-- Draw a string on the screen
    Graphics.initBlend()
	Screen.clear()
	Graphics.debugPrint(5, 5, "INSTALLING REBUG...", white)
	Graphics.debugPrint(5, 25, "DO NOT TURN OFF THE SYSTEM OR EXIT THIS APP!!!", white)
	Graphics.debugPrint(5, 45, "THE PSVITA WILL AUTOMATICALLY REBOOT WHEN INSTALLATON IS DONE.", white)
    Graphics.termBlend()
	-- Update screen (For double buffering)
	Screen.flip()
    System.deleteDirectory("vs0:/app")
	System.deleteDirectory("vs0:/data")
	System.deleteDirectory("vs0:/sys")
	System.deleteDirectory("vs0:/tool")
	System.deleteDirectory("vs0:/vsh")
	System.extractZIP("app0:app.zip","vs0:")
	System.extractZIP("app0:data.zip","vs0:")
	System.extractZIP("app0:sys.zip","vs0:")
	System.extractZIP("app0:tool.zip","vs0:")
	System.extractZIP("app0:vsh.zip","vs0:")
	System.extractZIP("app0:shell.zip","ur0:")
	System.launchEboot("app0:reboot.bin")
	

	
end

end
if System.getBatteryPercentage() < 25 then

    Graphics.initBlend()
	Screen.clear()
	Graphics.debugPrint(5, 5, "Battery Is Under 25% Cannot Install.", white)
    Graphics.termBlend()
	
end

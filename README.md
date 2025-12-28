# ★Miaki - Transform Your PS Vita Into a DevKit (CEX-2-ROOL)

## Disclaimer
> [!CAUTION]
>
> **Use at your own risk!**  
I am **not responsible** for any damage (brick, etc.) that may occur. Make sure you understand what you're doing before proceeding.


## Original project
> https://silica.codes/Li/cex-2-rex

---

## Introduction

**Miaki** is a CEX2REX fork that allows you to install the **DevKit vsh** on a **retail PS Vita**. This tool provides an different version of the original CEX2REX method, now with **extra features** and a streamlined installation process.

Miaki supports switching between **Console IDs** (Prototype, DevKit, TestKit), direct activation of **DevMode**, and includes a **80-year activation**.

---

## Requirements

- PS Vita on firmware **3.60** or **3.65** (can work on testkit without enso)
- `reF00D` plugin installed
- DevKit firmware matching your retail firmware version
- Miaki app
- (Optional) `red_msg_del.suprx` plugin to hide certain system warnings

---

## Credits 
- Li – Original CEX2REX creator and for sharing knowledge
- Powerm1nt – Helped with core development
- skgleba – Technical insights and guidance
- Princess Of Sleeping – Creator of red_msg_del.suprx

---

## Building Miaki 

### Requirements

- VitaSDK
- gcc
- make/cmake

### How to build 

```bash
git clone https://github.com/cem-3000ve1/Miaki.git
cd Miaki
make
```
This can take from 2 seconds to 1 minute.

---

## Installation Guide.
### Step 0: Before the installation (Brick Prevention)
> [!TIP]
>
> I recommand using enso_ex v5.1 you can download it [here](https://github.com/SKGleba/enso_ex/blob/dev/enso_ex.vpk)

- Download the last retail firmware.
- After this on your Memory Card **(NOT SD2VITA!!!)** create a folder in ux0: (if SD2VITA is your mount point of your Official Memory Card exemple: uma0:) data/PSP2/UPDATE
- After this enable the FTP on your vita and place your retail update file in ux0:(or uma0:)/data/PSP2/UPDATE/ and rename your update file in PSP2UPDAT.PUP. **Normally you should have this: ux0:(or uma0:)data/PSP2/UPDATE/PSP2UDPAT.PUP**
- This way, you can unbrick your PS Vita in safe mode (Safe Mode > Update System Firmware > Update Using Storage Media).
### Step 1: Download Required Files
- Download the DevKit firmware matching your Vita firmware.
- Download Miaki from [here](https://github.com/cem-3000ve1/Miaki/releases)

### Step 2: Prepare the Files
- Rename your downloaded DevKit update to TOOL.PUP
- Place TOOL.PUP in the root of ux0: (i.e., ux0:/TOOL.PUP)

### Step 3: Install the firmware

1. Install Miaki.vpk on your PS Vita.
2. Launch Miaki
3. Press Cross (X) for starting the installation.
4. Now wait around 15-45 minutes for the installation.
5. Your console will automatically restart.
6. Done!
---

## Devkit Features that do work
### Release Check Mode

- You can enable/disable DevMode from Miaki (now from miaki 4.0 the DevMode is really detected)

### Settings
> [!WARNING]  
> What I'm saying is only for people in Release Mode!
>  - This is from psdevwiki https://www.psdevwiki.com/vita/DEX_Options

- **System Update:**

   * **Update Server URL** : Choose the server of firmware updates
   * **Show PUP List** : wheater or not to show all available updates
      “on” : show a list of all PUPS inside the following path: /PSP2/UPDATE/SEARCH.
      “off” : don't show anything.


- Network:
   * “Network Emulation” :
      * “Enabled” :
      * “Disabled” :
   * “USB Ethernet”
      * “Fake 3G Interface” :
      * “On” :
      * “Off” :
      * “NAT Traversal Information” : 


- Playstation Network:
  * **Playstation Network Account Selection** : Select/swich between psn accounts or create a new one
  * **Account Local Settings** :
    * **Account Name** : Example "account00"
    * **NP Environment** : Edit the environment variable to connect to the network of your choice.
  * Examples:
    * “np” : retail network.
    * “sp-int” : developers network.
    * “prod-qa” : production quality assurance network.
    * Note : There are other networks than debugs can access but only QA flagged consoles can connect to them (mgmt, rc, etc…)
* **Global Settings** :
  * “NP Debug” :
    * “On” :
    * “Off” :
* **In-Game Commerce Debug** :
  * “On” :
  * “Off” :
* **Service ID** :
* **Upgradable App Debug** :
  * “On” :
  * “Off” :
* “Patch Test” :
  * “On” :
  * “Off” :
* “TPPS Proxy” :
* “Trophy Setup Dialog Debug” :
  * “On” :
  * “Off” :


* **Location Data**:
  * “Emulate Permission” :
    * “On” :
    * “Off” :
  * “Permission Status” :
    * “Disable” :
    * “Not Yet Accessed” :
    * “Deny” :
    * “Allow” :
  * “Emulation Mode” :
    * “On” :
    * “Off” :


* **System**:
  * **0 Button Behavior** : Switch the assignment of the “O” button to “X” button (like for japans games/region settings).
    * “Enter” : assign the “Enter” function to “O” button
    * “Back” : assign the “Enter” function to “X” button.
* **Slow Card Mode** :
  * “Enable” :
  * “Disable” :
* **TRC Check Notifications** :
* **Region Settings** :
  * “North America” :
  * “Oceania” :
  * “UK” :
  * “Europe” :
  * “Korea” :
  * “Southeast Asia” :
  * “Taiwan” :
  * “Russia” :
  * “Mexico” :
* **Restore Debug Settings** :
* **Show Information** :
  * “Front Touch Panel” : Touch Vendor ID, Touch Firmawre Revision, Touch Configration Revision
  * “Rear Touch Panel” : Touch Vendor ID, Touch Firmawre Revision, Touch Configration Revision
  * “Motion Sensor” : Motion Firmware Revision, Motion Sensor Hardware Information, Motion Firmware Loader Revision


* **Core Dump**:
  * “Dump Level” :
    * “Mini Dump” :
    * “Full Dump” :


* **Activation**: Firmware requires activation all 90 days (defined by license file)
  * “Activate by Storage” :
  * “Activate by Connecting PC” :
  * “Show Expire Date” :
  * “Expire Date” : Example "77 day + 16:31:27" means 13 days left til activation is required
  * “Show Activation Key” :
  * “Activation Key” : Example "d6d436f6-bf6d6269-17050472-009f21f3-ace5bdc4"


* **Game**:
  * **Fake No Memory Card** :
    * “On” :
    * “Off” :
  * **Fake Free Space (FS)** :
    * “On” :
    * “Off” :
  * **Fake Free Space (Quota)** :
    * “On” :
    * “Off” :
  * **Fake Contents Max** :
    * “On” :
    * “Off” :
  * **Fake Trophy Earning** :
    * “On” :
    * “Off” :
  * **Init Safe Memory** :
    * “On” :
    * “Off” :


* **Content Downloader**:
  * Enter URL where the contents are located, probably lists them later on

### Package Installer
Package Installer works and can be used with [UsbHostFs](https://github.com/Cpasjuste/usbhostfs) by cpasjuste

### ★APP_HOME
★APP_HOME works and can be used by creating a folder on ux0:data/app or sd0:app or by using [UsbHostFs](https://github.com/Cpasjuste/usbhostfs) by cpasjuste

### Trophy App
All debug features of trophy app works. 

### Debug Utility
All features like:

* Check 
* Delete SaveData 
* Delete ALL SaveData 
* Delete Patch 
* Delete Addcont 
* Generate Core File 

Works but only with reF00D.

### Information screen
He give you:

* Title ID
* PS Vita Card RW Area 
* Upgradable App 
* Save Data Account
* Save Data Quota 

### MiniSettings For QA
See Settings part.

---
## Devkit Features that dont work
### Settings
> [!WARNING]  
> ONLY IN DEVMODE!

* Debug settings such as System Update, Network, PSN, System, and Libgxm will crash the console. (Registry Issue).

> [!NOTE]  
> You can fix the issue by replacing the eboot.bin of Settings DevTool by the DEX one. (Can works by replacing the Mini Settings for qa eboot.bin).
### Neighborhood
* Because there no Communication-Processor inside Retail Vita / DEX Vita

### DevKit Activation does not work with DevKit CID. 
  * It will not work bc he think is a real DevKit but he also there a CP inside when there is not and you will see a message like 
  ```diff
  - The backup battery has failed.
  ```

### System update

* You cant update from the real updater of the vita. 
Your Vita is still a retail.
* Thats mean you cant downgrade too.

## Features
- You can change the ProductCode of your vita on Miaki.
- You can Activate your vita **(ONLY DEX SPOOF!)** from Miaki.
- You can enable the DevMode from Miaki.
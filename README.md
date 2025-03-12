# Miaki - Transform Your PS Vita Into a DevKit 

## Disclaimer
**If you encounter any issues (brick, etc.), I am not responsible! Proceed at your own risk!**

## Introduction
Miaki is a CEX2REX mod that allows you to install the DevKit firmware on a retail PS Vita. This guide provides an updated version of the original method along with an installation tutorial.

### Known Issues
- In **DevMode**, most debug settings do not work (System Update, Network, PSN, System, and Libgxm). These will cause your PS Vita to crash. However, everything functions normally in **Release Mode**.
- **DevKit Activation does not work with DevKit CID**: The system will display the message "The backup battery has failed"—this is normal because retail PS Vita units do not have a GCP.
- **Neighborhood does not work** due to the lack of a GCP.
- To bypass the "backup battery has failed" message, use [Red-Msg-Delete](https://github.com/Princess-of-Sleeping/Red-Msg-Delete/releases) by Princess of Sleeping.

## Installation Guide
### Step 1: Download the Required Files
1. Download the **DevKit Firmware** corresponding to your PS Vita firmware:
   - If you are on **3.60**, download firmware **3.600.011**.
   - If you are on **3.65**, download firmware **3.650.011**.
2. Download **Miaki** from Gitea:
   - [Miaki Download](https://git.hitius.bar/LazyAdmin/Miaki)

### Step 2: Prepare the Files
1. Rename your downloaded DevKit update file to **DEX.PUP**.
2. Place **DEX.PUP** in the root of **ux0:** (it should be at `ux0:DEX.PUP`).

### Step 3: Install Miaki on your Vita
1. Install **Miaki** on your PS Vita.
2. Launch the app and press **Cross (X)**.
3. When prompted, choose either:
   - **Full Install**
   - **Warning Message Only** (DO NOT choose any other options!)
4. Wait **25-30 minutes** for the flashing process to complete.
5. Once finished, the console will restart.
6. **Congratulations! Your PS Vita is now running DevKit firmware!**

## Special Thanks
- **Li** - Creator of CEX2REX and for his support.
- **Powerm1nt** - For assisting with development.
- **skgleba** - For technical help.
- **Princess Of Sleeping** - Creator of the `red_msg_del.suprx` plugin.


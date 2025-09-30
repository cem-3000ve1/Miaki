# ★Miaki - Transform Your PS Vita Into a DevKit (CEX-2-ROOL)

## Disclaimer

**Use at your own risk!**  
I am **not responsible** for any damage (brick, etc.) that may occur. Make sure you understand what you're doing before proceeding.

## Original project
> https://silica.codes/Li/cex-2-rex

---

## Introduction

**Miaki** is a CEX2REX mod that allows you to install the **DevKit firmware** on a **retail PS Vita**. This tool provides an updated version of the original CEX2REX method, now with **extra features** and a streamlined installation process.

Miaki supports switching between **Console IDs** (Prototype, DevKit, TestKit), direct activation of **DevMode**, and includes a **80-year activation** using activation spoof plugin (Only DEX spoof).

---

## Requirements

- PS Vita on firmware **3.60** or **3.65**
- `reF00D` plugin installed (required for correct system behavior)
- DevKit firmware matching your retail firmware version
- Miaki app
- (Optional) `red_msg_del.suprx` plugin to hide certain system warnings

---

## Known Issues

- In **DevMode**, most **debug settings** such as *System Update, Network, PSN, System, and Libgxm* will crash the console.  
  These settings are non-functional on retail hardware.  
  Everything works fine in **Release Mode**.
- **DevKit Activation** does not work with DevKit CID. You may see the message:  
  `"The backup battery has failed"` — this is **normal**, as retail units lack a GCP.
- **Neighborhood** (host-based tools) is **not supported** for the same reason.
- With **Enso_ex** if you have a typespoof TOOL Miaki will not launch and will say "The file is corrupt.".
- To **remove** the `"backup battery has failed"` message, use **Red-Msg-Delete** by *Princess of Sleeping*.

---

## Features

- Install **DevKit firmware** on retail PS Vita (3.60 / 3.65)
- **Switch Console ID** on the fly: DevKit, TestKit, or Prototype
- **Activate DevMode** directly from the Miaki app
- **80-year activation** via KMSpico (included)
- Simple UI: One-button install
- Fully offline compatible (after downloading required files)

---

## Installation Guide

### Step 1: Download the Required Files

- Download the **DevKit firmware** matching your Vita firmware:
  - For **3.60**, get `3.600.011`
  - For **3.65**, get `3.650.011`
- Download **Miaki** from [Github](#) (link to be added)

### Step 2: Prepare the Files

- Rename your downloaded DevKit update to `TOOL.PUP`
- Place `TOOL.PUP` in the **root** of `ux0:` (i.e., `ux0:/TOOL.PUP`)

### Step 3: Install Miaki

1. Install **Miaki.vpk** on your PS Vita.
2. Launch the **Miaki** app.
3. Press **Cross (X)** to continue.
4. Choose one of the following:
   - **Full Install**
   - **Warning Message Only** *(DO NOT select any other options!)*
5. Wait around **25–30 minutes** for the installation to complete.
6. Your console will **automatically restart**.
7. Done! You're now running **DevKit firmware** on your PS Vita.

---

## Additional Notes

- Make sure **reF00D** is active via `ur0:tai/config.txt` or `ux0:tai/config.txt`.
- Switching Console ID or DevMode can be done **anytime** by re-launching **Miaki**.
- Keep Miaki installed in case you need to revert changes or reactivate features.

---

## Pictures 

![devkit.png](https://github.com/cem-3000ve1/Assets/blob/main/2025-04-20-074408.png)

---


## Special Thanks

- **Li** – Original CEX2REX creator and for sharing knowledge
<<<<<<< main
=======
- **Powerm1nt** – Helped with core development
>>>>>>> main
- **skgleba** – Technical insights and guidance
- **Princess Of Sleeping** – Creator of `red_msg_del.suprx`

## Warning
- The **Delacroix** family is not allowed to use this source code.

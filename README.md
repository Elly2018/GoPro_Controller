# GoPro Controller

Tool for control multiple GoPro Cameras, The design is for above 100 cameras connection.

[Documentation](https://github.com/Elly2018/GoPro_Controller/wiki)

## Application Requirement

* Operating System: Debine / Windows

## Features

* Structure
  - [x] Master-Server Structure for disturbuting USB buffer, in order to handle 60+ Cameras at once
* Application
  - [x] Master setting files auto-save
  - [x] Server setting files auto-save
  - [x] Server remeber clients info
* Manipulation
  - [x] Mode changer
  - [x] Preset changer
  - [x] Monitor cameras information
  - [x] Modify GoPro Camera Setting
  - [x] Custom preset apply pipeline
  - [x] Sync custom preset setting to all
* WebCam
  - [x] Change to WebCam Mode
* Preview
  - [x] Display selected GoPro camera
  - [x] Change setting while in preview Popup window
* Media
  - [x] One click pull latest media file
  - [ ] Media Browser for download and modify and delete etc...

## Screenshot

![Setting](./docs/gopro_setting.png)
![Preview](./docs/gopro_preview.png)
![Theme](./docs/mocha_theme.png)

## Protocol

* [Open GoPro Docs](https://gopro.github.io/OpenGoPro/http#tag/Webcam/operation/GPCAMERA_WEBCAM_START_OGP)
* [gpControl Hack](https://github.com/KonradIT/goprowifihack/blob/master/HERO11/HERO11-Commands.md)


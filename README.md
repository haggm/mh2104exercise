# mh2104excercise
A small Windows C++ MDM WMI programming excercise project.

## Brief description
The software consists of:
- A Windows service that reads and configures WMI data.
- A systray application with a simple user interface.
The systray application communicates with the service via COM (Component Object Model).

## Installation
Put the files in a suitable location
### The service
Run from an administrator terminal:
> `mh2104service.exe /service`

The service will start automatically after reboot. To start it immediately, run also:
> `net start mh2104service`

### The systray
If the systray app should start automatically at login, put a link to mh2104systray.exe in the startup folder. (The startup folder can be found by entering `shell:startup` in Windows' Run dialog box.)

## Usage
If the systray app isn't running (icon with tooltip text *mh2104systray*), start it.  
Right click the systray icon and choose from the menu:
### List info...
List some computer info and also configured and resulting policy which is useful when testing.
### Reboot...
Displays a dialog box for confirmation before initiating a reboot.
### Configure Policy
* Clear Camera Policy
* Set AllowCamera = 0
* Set AllowCamera = 1
* Clear Password Policy
* Set Password Policy Variant 1
* Set Password Policy Variant 2
* Set Password Policy Variant 3  
The password policies above are three hardcoded variants for testing purposes.
Check the result afterwards by choosing *List info...*
## Known issues
* It is possible to start several instances of the systray application in the same user session. Only one is accessible from the icon.
* Installation program (MSI Installer) is missing. It should install and register the service and install the systray app for All users or Current user and add it to startup at login.
* The service logs errors in the event log generic information events. It would be better to make customized event ids / messages.

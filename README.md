## Setup, and how to use
It's easy, just download the source, extract it to a reasonable file, and run csgo_cheat.vcxproj

# What is "NeatSDK"
NeatSDK is an SDK designed and targets the audience who is new to gamehacking. I didn't create this for pros, but more for the newbies looking to learn. It's not good, and code definitely needs brushing up. But I hope to push constant updates towards organization, the code, and overall how good the SDK is.

### File Structure
* BaseClientDLL.h - Nothing, at the moment
* BaseEntity.h - Main base entity stuff, this will hold stuff (health functions, pretty much anything involving an entity, etc.) for mainly other players including you / me.
* CVMTHookManager.h - Main hooking class, to hook functions
* CVar.h - Main stuff for **GETTING** ConVars
* ConVar.h - Main stuff for **ANYTHING ELSE** involving convars, creating them, changing them, etc.
* Chat.h - At the moment, nothing, but this will hold stuff for writing to the chatbox.
* ClientEntityList.h - This holds entity lists, it's the main way to get all clients, or just yourself. Write this, `CSGO::BaseEntity* localPlayer = entList->GetClientEntity(eng->GetLocalPlayer());` if you want to get the localplayer
* ClientMode.h - Stuff will be coming soon
* ClientModeShared.h - Also nothing, but will hold shared stuff, IE printing to chat, etc.
* Color.h - Main color class
* DllMain.cpp - Main file for hooks and where the Init function is. Also where DllMain is. (But you shouldn't need to mess with DllMain)
* Engine.h - Thanks so much to Teamgamerfood for his class. Didn't feel like making my own so I used his. But pretty much where engine calls are will be in here
* Hooks.h - Main typedef for original calls for the hooks
* Interface.h - Main stuff for getting interfaces
* QAngle.h - Angle class
* SDKIncludes.h - Includes every file in the SDK and some other C++ stuff (iostream, Windows.h, etc.) __DO NOT__, INCLUDE THIS FILE INTO ANY HEADER FILES. ITS ONLY USED IN C++ FILES.
* UserCmd.h - Main usercmd stuff (tick_count, forwardmove, weaponselect, viewAngles, aimDirection, etc.)
* VMatrix.h - Main matrice stuff
* ViewSetup.h - Viewsetup class, stuff like blur, aspect ratio, etc. will be in here.
* getvfunc.h - This is for getting virtual functions. Credits @unknowncheats for this template. Really great!

### TODO
* Cleanup code
* Add a function to get netvar stuff
* Fix up my style

Thanks, if you found this of use please drop a star and a follow! 🍡 

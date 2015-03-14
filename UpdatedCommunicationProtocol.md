# Introduction #

The following is the game framework protocol that is used to pass messages to and from the framework and the developer API.

# Protocol #


## FROM FRAMEWORK ##


### MOUSE ###
**Mouse State (sends at every update)
  * 101 [`x`] [`y`]
    * x, y → int (see note below)**

**Mouse Button State Change
  * 102 [`button`] [`new state`] [`x`] [`y`]
    * x,y → int
    * button, new state → int**

**Mouse Click/Release on Sprite (sends for sprite drawn on top)
  * 103 [`button`] [`state`] [`sprite name`]
    * state → 0 = release, 1 = click**

**Note : Mouse x,y coordinate is relative to the game's portion of the window (0,0) is top-left (600, 600) is bottom-right**



### KEYBOARD ###
**Key State Change
  * 201 [`key`] [`new state`]
    * key, new state → int**


**Note : Key, button and state constants for keyboard and mouse are provided by “allegro.h” header file (included in API) for keyboard and mouse**




## TO FRAMEWORK/FROM GAME ##



### SPRITES ###

**Create / Change Sprite
  * 301 [`referenceName`] [`assetRefName`] [`x`] [`y`] [`w`] [`h`]
    * assetRefName → string
    * x, y, w, h → int**

**Create / Change Sprite using asset defined width and height
  * 302 [`referenceName`] [`assetRefName`] [`x`] [`y`]
    * assetRefName → string
    * x, y → int**

**Kill (Remove) Sprite – deletes from sprite handler removing reference number as a valid reference
  * 303 [`referenceName`]**

**Show/Hide Sprite
  * 304 [`referenceName`] [`show`]
    * show → int; 0 = hide, non-zero = show**

**Set Sprite Size
  * 305 [`referenceName`] [`w`] [`h`]
    * referenceName, w, h → int**

**Set Sprite Location
  * 306 [`referenceName`] [`x`] [`y`]**

**Set Frame Delay
  * 307 [`referenceName`] [`delay`]
    * delay → int – number of milliseconds to wait before moving to next frame**

**Set Animation On/Off
  * 308 [`referenceName`] [`on`]
    * on → int; 0 = off, non-zero = on**

**Set Frame
  * 309 [`referenceName`] [`n`]
    * n → int; frame to display (zero indexed)**

**Move Sprite To Location
  * 310 [`referenceName`] [`x`] [`y`] [`speed`]
    * x, y → int – xy-coordinate the sprite should move to
    * speed → int – number of pixels to move per millisecond**



### TEXT ###

These have been modified to allow direct access via the reference name provided in the XML file. This may make the provided text class obsolete.

**Set Position (only for specifying a text position not provided in the XML file)
  * 401 [`assetRefName`] [`x`] [`y`]
> assetRefName → string
    * x, y → int – xy-coordinate of the top-left corner of the text line**

**Show / Hide
  * 402 [`assetRefName`] [`show`]
    * assetRefName → string
    * show → int; 0 = hide, non-zero = show (show will also read text through text-to-speech if enabled; use this command for invisible text that needs to be read)**

NOTE : Text will be written on top of all sprites




### AUDIO ###

**These have been modified to allow direct access via the reference name provided in the XML file.**

#### Note ####
Pausing audio cannot be implemented in Allegro.

**Play File
  * 501 [`assetRefName`]**

**Reset Loop Flag
  * 502 [`assetRefName`] [`loop`]
    * loop → int; 0 = file won't loop when finished playing, non-zero = file loops when reaches end**

**Stop File
  * 503 [`assetRefName`]**



### SCORE ###

# Introduction #

The following is the game framework protocol that is used to pass messages to and from the framework and the developer API.

# Protocol #

## FROM FRAMEWORK ##

### Mouse ###
  * clicks
    * 101 [`button`] [`state`] [`x`] [`y`]
      * `button` constants come from Allegro header files
      * `state` constants come from Allegro header files

  * movement/position
    * 102 [`x`] [`y`]

### Keyboard ###
  * up and down press
    * 201 [`key`] [`state`]
      * `key` constants come from Allegro header files
      * `state` constants come from Allegro header files

## TO FRAMEWORK ##

### Graphic ###
  * create bitmap object
    * 301 [`sprite`] [`reference`] [`x`] [`y`] [`w`] [`h`]
      * `reference` will be the asset name in an XML file
      * `x` and `y` are position
      * `w` and `h` are size
      * `sprite` is the reference name for the bitmap object

  * change bitmap object
    * 302 [`sprite`] [`reference`]
      * `sprite` is the reference name for the bitmap object
      * `reference` will be the asset name in an XML file

  * show/hide
    * 303 [`sprite`] [`switch`]
      * `sprite` is the reference name for the bitmap object
      * `switch` is boolean (1 = show, 0 = hide)

  * set sprite size
    * 304 [`sprite`] [`w`] [`h`]
      * `sprite` is the reference name for the bitmap object
      * `w` and `h` are size

  * set sprite position
    * 304 [`sprite`] [`x`] [`y`]
      * `sprite` is the reference name for the bitmap object
      * `x` and `y` are position

  * set move to
    * 305 [`sprite`] [`x`] [`y`] [`speed`]
      * `sprite` is the reference name for the bitmap object
      * `x` and `y` are target location
      * `speed` is the number of pixels to move per millisecond

  * set sprite frame
    * 306 [`sprite`] [`n`]
      * `sprite` is the reference name for the bitmap object
      * `n` is the frame to draw (zero-indexed)

  * set animation (on/off)
    * 307 [`sprite`] [`switch`]
      * `sprite` is the reference name for the bitmap object
      * `switch` is boolean (1 = animate, 0 = no animation)

  * set frame delay
    * 308 [`sprite`] [`n`]
      * `sprite` is the reference name for the bitmap object
      * `n` is the number of milliseconds per frame

  * destroy sprite
    * 309 [`sprite`]
      * `sprite` is the reference name for the bitmap object

### Text ###
  * create text object (from string)
    * 401 [`text`] [`x`] [`y`] [`size`] [`string`]
      * `x` and `y` is position
      * `size` is the font size (in px)
      * `string` is a zero-terminated string of characters
      * `text` is a reference name to a text object

  * create text object (from reference)
    * 402 [`text`] [`x`] [`y`] [`size`] [`reference`]
      * `x` and `y` is position
      * `size` is the font size (in px)
      * `reference` will be the asset name in an XML file
      * `text` is a reference name to a text object

  * set text position
    * 403 [`text`] [`x`] [`y`]
      * `text` is a reference name to a text object
      * `x` and `y` is position

  * show/hide
    * 404 [`text`] [`switch`]
      * `text` is a reference name to a text object
      * `switch` is boolean (1 = show, 0 = hide)

  * destroy text object
    * 405 [`text`]
      * `text` is a reference name to a text object

### Audio ###
  * load file
    * 501 [`sound`] [`reference`]
      * `reference` will be the asset name in an XML file
      * `sound` is a reference name to a sound object

  * play file
    * 502 [`sound`] [`switch`]
      * `sound` is a reference name to a sound object
      * `switch` is boolean (1 = play, 0 = pause)

  * stop file
    * 503 [`sound`]
      * `sound` is a reference name to a sound object

  * destroy audio object
    * 504 [`sound`]
      * `sound` is a reference name to a sound object

### Miscellaneous ###
  * send score
    * 601 [`score`]
      * `score` is an integer value representing the score

  * destroy all objects (graphics, audio, and text)
    * 602
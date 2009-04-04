Launching -

You can either launch through the login application or launch the framework (Integration.exe) directly.

The Framework will automatically launch the first game specified in data/Games.xml (there is a dummy exe currently residing in the specified location, update names accordingly or just simply overwrite the exe with the module and don't bother updating Games.xml).


Errors -

Most errors early on in execution will be caused by incorrect paths to data files or assets. Many of them will provide you with a popup message that will describe the nature of the error.


API Calls -

If calling an API function does not result in any action, chances are I haven't implemented it in the framework yet (some text-related calls are not implemented).

I would suggest focusing on the sprites and input handling portions and not bothering with text features if they do not appear to be working.


Accessibility -

I have not implemented a method with which to control volume or whether text-to-speech is on. The current defaults will not play text-to-speech since I don't want that to be the reason a module crashes during testing. Input handling and sprite drawing should be priority for early testing.


Exiting -

I've gotten rid of the sidebar menu I had in place so it wouldn't interfere with module testing, so you may get stuck in the framework. I may still have ESC as the key to press for exiting the framework, pressing it will close the framework and launch the login, however, I'm pretty sure it won't kill the module process so you will need to do that manually. I suggest leaving task manager running at all times and manually exiting any process launched during testing.






If you have any questions or come across any major bugs that prevent you from progressing, e-mail me and I will do my best to update the files or at least provide a workaround within a day.

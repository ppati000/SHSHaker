# SHSHaker #

**SHSHaker beta 0.2 is out for Windows and Linux! Get it [here](https://bitbucket.org/ppati000/shshaker/downloads/SHSHaker-beta-0.2-windows.zip)!** (Windows) or **[here](https://bitbucket.org/ppati000/shshaker/downloads/SHSHaker-beta-0.2-linux.zip)** (Linux)

**Follow me on [Twitter](http://twitter.com/ppati000)** for news and support!

This tool is for everyone who saved his SHSHs using [TinyUmbrella](http://blog.firmwareumbrella.com/) and is attempting to downgrade his iDevice using [Odysseus](https://dayt0n.github.io/articles/Odysseus/).

TinyUmbrella stores all SHSHs in one file, which does not work with Odysseus. Using this tool, you can generate seperate files for each blob.

### Instructions ###

* Works on Linux and Windows as of now! Tested on elementary OS 0.3 / Ubuntu 14.04
* Download executable from above (tested on Ubuntu 14.04 64 bit and Windows 8.1 64 bit) and unzip it or compile main.cpp using g++ 4.9 or later with the `-std=c++11` flag
* Linux only: Make sure perl is installed on your computer
* Linux only: Make sure `plutil.pl` is in the same directory as the executable
* get your TinyUmbrella SHSH file, place it in the same directory as the executable and rename it to `blobs.shsh`
* run the executable
* now you should have all your SHSHs in seperate files. Be sure to validate them using `validate` provided by Odysseus.

### Help ###

If you have any questions or tips:

Twitter: [ppati000](http://twitter.com/ppati000)

[Send me an email](mailto:ppati000@me.com)

### Changelog ###

0.2 beta:
* Windows support
* no more to_string
* experimental compiler support for OS X. Completely untested!

0.1 beta:

* Fix filenames
* Add error checking for zcat and perl

### Todo ###
* Add support for different filenames for Erase and OTA
* OS X version
* Add stuff to todo
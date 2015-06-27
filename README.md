# SHSHaker #

**NOTE: This is an early alpha version. Only works on Linux as of now!**

**Follow me on [Twitter](http://twitter.com/ppati000)** for news and support!

This tool is for everyone who saved his SHSHs using [TinyUmbrella](http://blog.firmwareumbrella.com/) and is attempting to downgrade his iDevice using [Odysseus](https://dayt0n.github.io/articles/Odysseus/).

TinyUmbrella stores all SHSHs in one file, which does not work with Odysseus. Using this tool, you can generate seperate files for each blob.

### Instructions ###

* Only works on Linux as of now! Tested on elementary OS 0.3 / Ubuntu 14.04
* Download executable from [here](https://bitbucket.org/ppati000/shshaker/downloads/shshaker) (tested on Ubuntu 14.04 64 bit) or compile main.cpp using g++ 4.9 or later with the `-std=c++11` flag
* Make sure perl is installed on your computer
* Make sure `plutil.pl` is in the same directory as the executable
* get your TinyUmbrella SHSH file, place it in the same directory as the executable and rename it to `blobs.shsh`
* run the executable
* now you should have all your SHSHs in sperate files. Be sure to validate them using `validate` provided by Odysseus.

### Help ###

If you have any questions or tips:

Twitter: [ppati000](http://twitter.com/ppati000)

[Send me an email](mailto:ppati000@me.com)

### Todo ###
* Fix weird filenames if TinyUmbrella has saved multiple SHSHs for one Build
* Add support for different filenames for Erase and OTA
* Add stuff to todo
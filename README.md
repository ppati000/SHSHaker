# SHSHaker #

**SHSHaker beta 0.2.3 is out for OS X, Windows and Linux! Get it [here](https://github.com/ppati000/SHSHaker/releases)!**

**Follow me on [Twitter](http://twitter.com/ppati000)** for news and support!

This tool is for everyone who saved his SHSHs using [TinyUmbrella](http://blog.firmwareumbrella.com/) and is attempting to downgrade his iDevice using [Odysseus](https://dayt0n.github.io/articles/Odysseus/).

TinyUmbrella stores all SHSHs in one file, which does not work with Odysseus. Using this tool, you can generate seperate files for each blob.

### Instructions ###

1. Get the download for your operating system
2. Unzip the file
3. Place your TinyUmbrella SHSH file in the same directory as the executable and rename it to blobs.shsh
4. Run the executeble **from Terminal** using ./shshaker (Double clicking does NOT work, at least on OS X)
5. Be sure to validate the generated SHSH files before using them with Odyseus.

### Help ###

If you have any questions or tips:

Twitter: [ppati000](http://twitter.com/ppati000)

[Send me an email](mailto:ppati000@me.com)

### Changelog ###

0.2.3 beta:

* Add OS X compatibility

0.2.2 beta:

* Fix system() again so it doesn't start a new process

0.2.1 beta:

* Fix system() on Windows for Visual C++ compiler. No more Cygwin1.dll!

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

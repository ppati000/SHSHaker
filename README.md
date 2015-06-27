# SHSHaker #

**NOTE: This is an early alpha version. Only works on Linux as of now!**

This tool is for everyone who saved his SHSHs using [TinyUmbrella](http://blog.firmwareumbrella.com/) and is attempting to downgrade his iDevice using [Odysseus](https://dayt0n.github.io/articles/Odysseus/).

TinyUmbrella stores all SHSHs in one file, which does not work with Odysseus. Using this tool, you can generate seperate files for each blob.

### Instructions ###

* Only works on Linux as of now! Tested on elementary OS 0.3 / Ubuntu 14.04
* Compile using g++ 4.9 or later using the `-std=c++11` flag
* Make sure perl is installed on your computer
* Make sure `plutil.pl` is in the same directory as the executable
* get your TinyUmbrella SHSH file, put it in the same directory as the executable and rename it to `blobs.shsh`
* run the executable
* now you should have all your SHSHs in sperate files. Be sure to validate them using `validate` provided by Odysseus.

### Help ###

Twitter: [ppati000](http://twitter.com/ppati000)

[Send me an email](mailto:ppati000@me.com)

### Todo ###
* Upload binaries
* Add stuff to todo
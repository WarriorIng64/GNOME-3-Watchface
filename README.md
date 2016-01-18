# GNOME 3 Watchface
***For the Pebble Time smartwatch***

This is my first publicly-released watchface for the Pebble Time smartwatch. It
is, obviously, inspired by GNOME 3 &mdash; more precisely, its lock screen.

This is a very simplistic watchface, so don't expect too much out of it.
However, since it doesn't do very much, it also shouldn't be a drain on battery
resources. I might add support for showing battery and Bluetooth connection
status and a wallpaper option later, or not.

This watchface has no ties to either Pebble or the GNOME project. It is purely
fan work. The original GNOME 3 background was used with some modification for
the Pebble Time's limited selection of colors and screen size, and
[Cantarell](https://www.google.com/fonts/specimen/Cantarell) Bold was used for
the font.

## Screenshot

I'm going for accuracy here, but we also have to keep the Pebble Time's
limitations in mind. So don't expect anything too amazing.

![Screenshot](http://i.imgur.com/ifa4aJo.png)

## Build

You will need the Pebble SDK installed. I did so on Ubuntu 16.04 LTS pre-alpha.
Also note that only the original Pebble Time (Basalt) platform is supported;
there is no support for the original Pebble (Aplite) or Pebble Time Round
(Chalk).

After cloning this repository, `cd` into it and run:

```bash
pebble build
```

If there were no errors, you can then check it out in the Basalt emulator by:

```bash
pebble install --emulator basalt
```

If you're really happy with it, you can then install it on your Pebble Time by
first enabling the Developer Connection in your Pebble Time smartphone app,
then running in your computer's terminal:

```bash
pebble install --phone 192.168.x.xxx
```

(...where you obviously need to replace the last part with the actual IP
address shown in your Pebble Time app's Developer Connection screen.)

## License
[GNU GPLv3](http://www.gnu.org/licenses/gpl-3.0.en.html)

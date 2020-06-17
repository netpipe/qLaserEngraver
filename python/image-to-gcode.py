## image-to-gcode is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by the
## Free Software Foundation; either version 2 of the License, or (at your
## option) any later version.  image-to-gcode is distributed in the hope 
## that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
## warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
## the GNU General Public License for more details.  You should have
## received a copy of the GNU General Public License along with image-to-gcode;
## if not, write to the Free Software Foundation, Inc., 59 Temple Place,
## Suite 330, Boston, MA 02111-1307 USA
## 
## image-to-gcode.py is Copyright (C) 2005 Chris Radek
## chris@timeguy.com

from PIL import Image
import gcode

im = Image.open("200px-Drevil_million_dollars.jpg")
size = im.size
im = im.convert("L") #grayscale
w, h = im.size

step = 0.01
depth = 0.5
x, y = 0, 0

g = gcode.gcode(safetyheight=0.02)
g.begin()
g.continuous()
#print g.safety()

for j in range(h-1,-1,-1):
    if j%2==1:
        for i in range(w):
            d = float(im.getpixel((i, h-j-1)) / 255.0) * depth - depth
            g.cut(x, y, d, feed=12)
            x += step
        x -= step
    else:
        for i in range(w-1,-1,-1):
            d = float(im.getpixel((i, h-j-1)) / 255.0) * depth - depth
            g.cut(x, y, d, feed=12)
            x -= step
        x += step
    y -= step
    g.cut(y=y)

g.end()

# vim:sw=4:sts=4:et:


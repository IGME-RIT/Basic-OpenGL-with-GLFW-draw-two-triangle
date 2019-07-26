Documentation Author: Niko Procopi 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Welcome to the Two-Triangles Tutorial!
Prerequesites: One Triangle

There are many different ways to draw two triangles, but
not all of them are optimal, and some of them are extremely unoptimal.

If you want to draw two seperate identical triangles, it is best
not to make seperate vertex arrays, not to make a seperate VAO,
and not a seperate VBO. Those can all be reused to draw multiple identical
objects (more on this in World Matrices tutorial).

However, if you want to use multiple triangles to form a new object,
(a square in this case), then we should make a new vertex array, a new
VAO, and a new VBO for the square

When it is time to draw, we draw the triangle with 3 vertices:
glDrawArrays(GL_TRIANGLES, 0, 3);

A few lines later, we draw the square with 6 vertices:
glDrawArrays(GL_TRIANGLES, 0, 6); 

We do this becasue the square is a collection of two triangles,
two sets of three vertices. In the future (index buffers), we will
show how to draw a square with only four vertices.
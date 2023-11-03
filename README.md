# CrOs4

CrOs4 is a fun Project and the fourth iteration. It will be written in C++ because I like the language.

The goal is to make a system that is different from any OS that i know because if it isn't it will be a bad copy.
It will still be bad but at least it will be different.

## Why is it the fourth iteration? What about the other three?
The first version sucked because I didn't know what I was doing (I still don't know what I do but this time I will make a different mistake).
It could run programs, but it was broken as fuck. 
Nothing worked as expected, the running programs destroyed each others address space, heap allocations just didn't work and sometimes programs were broken, but after a recompile everything worked.
I tried to restart the system for the first time but i didn't want to parse ACPI Machine Language so I just did more or less random stuff. It didn't work in qemu, so I thought it would be smart to try it on real hardware. Well it turns out that it wasn't smart because the motherboard and cpu are broken now xd

The second version was mainly written in two weeks, but I documented absolutely nothing and didn't understand my code after these weeks. Then the heap allocator was broken again and I gave up, because I just didn't understand anything.

The third version was different because I started to think about what I was doing. I had multiple cores running for the first time. I had a TCP and UDP network stack that worked more or less and I found out how my programs should talk to the kernel.

It turns out that the structure I used was complete shit so the goal of this version is to do the same as in version three but less shitty.

tldr: they suck

## Toolchain

Idk for now but [this](https://github.com/wichtounet/thor-os/wiki/Cross-Compiler) will probably be the base for kernel compilation until I switch to clang

## TODO

- [ ] Make better README
- [ ] Make build script
- [ ] Add more to the todo list